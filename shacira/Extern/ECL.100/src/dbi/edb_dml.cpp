// ===========================================================================
// edb_dml.cpp                                  ETCL (ET's Tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//  cdbTAObject
//   |
//   +--cdbDML          -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "dbi/edb_dml.hpp"
#include "base/eb_array.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "dbi/edb_cursor.hpp"
#include "dbi/edb_transaction.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cdbDML
// ---------------------------------------------------------------------------
//
// Ausfuehren eines Befehls zur Datenmanipulation (DML-Befehl). Dies sind
// insbesondere die SQL-Befehle SELECT, INSERT, DELETE und UPDATE, koennen
// jedoch auch spezielle Anweisungen wie Aufrufe von Stored Procedures o.ae.
// sein. Die Abarbeitung der DML-Befehle erfolgt in einem Hintergrund-Thread
// durch Benutzung eines cdbTransaction-Objektes.
//
// cBase
//  +--csBaseStorage
//      +--cdbDML
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbDML : public csBaseStorage, public cdbTAObject {
   ECL_DECLARE(cdbDML,csBaseStorage)

public:

   // Konstruktor ueber TA-Zeiger
   cdbDML(cdbTransaction *ta, SQL::STMT stmt = SQL::STMT(), int flags = 0);
   // Konstruktor ueber TA-Referenz
   cdbDML(cdbTransaction& ta, SQL::STMT stmt = SQL::STMT(), int flags = 0);
   // Destruktor
   ~cdbDML();


   // Parameter- und Ergebnisvariablen
   // ================================

   // Binden einer Ergebnisvariablen
   void define(int n, csStorage *store);
   // Binden einer Parametervariablen
   void bind(int n, csStorage *store);


   // Ausfuehrungskontrolle
   // =====================

   // Asynchrones Starten der Datenmanipulation
   void start(const cEventTarget::EVENT& event = cEventTarget::EVENT());
   // Synchrones Starten der Datenmanipulation
   bool call(const cEventTarget::EVENT& event = cEventTarget::EVENT());


   // Sonstiges
   // =========

   // Auszufuehrendes SQL-Statement erfragen
   inline SQL::STMT getSQL() const
      { return stmt; }

   // Anzahl gebundener Ergebnisvariablen erfragen
   int getDefineCount() const;
   // Anzahl gebundener Parametervariablen erfragen
   int getBindCount() const;


protected:

   // Hinzugefuegte Events
   // ====================

   // Waehrend der Bearbeitung des DML-Befehls werden die folgenden
   // Event-Methoden aufgerufen:
   //
   //  - onEnter: Nach Kompilation des SQL-Statements besteht hier die
   //    Moeglichkeit, Variablenbindungen vorzunehmen oder andere Aktionen
   //    mit dem cdbCursor-Objekt durchzufuehren. Die onEnter()-Methode
   //    der Basisklasse fuehrt die Bindung der ueber die define()- bzw.
   //    bind()-Methoden angegebenen Variablen durch.
   //
   //  - onExec: Diese Methode wird aufgerufen, um die Bearbeitung des
   //    DML-Befehls durchzufuehren. Die onExec()-Methode der Basisklasse
   //    fuehrt ein cdbCursor-Exec aus sowie, sofern mindestens eine
   //    Ergebnisvariable gebunden wurde, einen einmaligen cdbCursor-Fetch.
   //    Diese Verarbeitung duerfte fuer die meisten Anwendungsfaelle aus-
   //    reichen, bei denen lediglich ein einzelner Datensatz abgefragt
   //    werden oder ein INSERT, DELETE und UPDATE ausgefuehrt werden soll.
   //
   //  - onLeave: Hier besteht die Moeglichkeit, Aktionen nach Beendigung
   //    des DML-Befehls auszufuehren. Die onLeave()-Methode der Basisklasse
   //    liefert einfach nur true zurueck.

   // Wird aufgerufen, um Parameter- oder Ergebnisvariablen zu binden
   virtual bool onEnter(cdbCursor& cu);
   // Wird aufgerufen, um das SQL-Statement auszufuehren
   virtual bool onExec(cdbCursor& cu);
   // Wird aufgerufen, um die Verarbeitung abzuschliessen
   virtual bool onLeave(cdbCursor& cu);


   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die Aktion 'func' auszufuehren
   void onExecAction(cdbDatabase *db, int func);
   // Wird aufgerufen, um den Abbruch der aktuellen Aktion anzufordern
   void onStopAction();
   // Wird aufgerufen, um eine textuelle Signatur der Aktion zu ermitteln
   cString onGetSignature();


private:

   SQL::STMT stmt;            // Auszufuehrendes SQL-Statement
   cdbCursor *current_cu;     // Zeiger auf aktuellen Cursor (oder 0)
   cErrBase last_error;       // Zuletzt aufgetretener Fehler
   bool last_rc;              // Letzter Rueckgabestatus

   struct VARS;
   VARS *define_vars;         // Zeiger auf Feld mit Ergebnisvariablen
   VARS *bind_vars;           // Zeiger auf Feld mit Parametervariablen

};

#endif /*__INTERFACE__*/


// Implementierung cdbDML
// ===========================================================================

struct cdbDML::VARS {
   cArray<csStorage*,csStorage*> array;
};

cdbDML::cdbDML(cdbTransaction *ta, SQL::STMT stmt, int flags) :
   csBaseStorage(flags), cdbTAObject(ta),
   last_error(cErrBase::errNoError)
{
   cdbDML::stmt = stmt;
   cdbDML::last_rc = false;
   cdbDML::current_cu = 0;
   cdbDML::define_vars = 0;
   cdbDML::bind_vars = 0;
}

cdbDML::cdbDML(cdbTransaction& ta, SQL::STMT stmt, int flags) :
   csBaseStorage(flags), cdbTAObject(ta),
   last_error(cErrBase::errNoError)
{
   cdbDML::stmt = cString(stmt);
   cdbDML::last_rc = false;
   cdbDML::current_cu = 0;
   cdbDML::define_vars = 0;
   cdbDML::bind_vars = 0;
}

cdbDML::~cdbDML()
{
   delete define_vars;
   delete bind_vars;
}


// Parameter- und Ergebnisvariablen
// ================================

void cdbDML::define(int n, csStorage *store)
{
   if ( __ECL_ASSERT1__(n >= 0 && store != 0) ) {
      if ( define_vars == 0 )
         define_vars = new0 VARS;
      if ( define_vars->array.getSize() <= n )
         define_vars->array.setSize(n + 1);
      define_vars->array[n] = store;
   }
}

void cdbDML::bind(int n, csStorage *store)
{
   if ( __ECL_ASSERT1__(n >= 0 && store != 0) ) {
      if ( bind_vars == 0 )
         bind_vars = new0 VARS;
      if ( bind_vars->array.getSize() <= n )
         bind_vars->array.setSize(n + 1);
      bind_vars->array[n] = store;
   }
}


// Ausfuehrungskontrolle
// =====================

void cdbDML::start(const cEventTarget::EVENT& event)
{
   last_rc = false;
   last_error = cErrBase(cErrBase::errNoError);
   cdbTAObject::startAction(0, event);
}

bool cdbDML::call(const cEventTarget::EVENT& event)
{
   last_rc = false;
   last_error = cErrBase(cErrBase::errNoError);
   bool rc = cdbTAObject::callAction(0, event);
   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError ) {
      char msg[512]; last_error.getString(msg, sizeof msg);
      cBase::DbgError(msg);
      throw last_error;
   }

   // 17.01.2002 -TE- Liefert jetzt den Rueckgabestatus der onXxx-Funktionen 
   // zurueck, dies ist insbesondere der fetch-Status bei einem Standard-
   // SELECT-DML
   return rc && last_rc;
}


// Sonstiges
// =========

int cdbDML::getDefineCount() const
{
   return define_vars != 0 ?
      define_vars->array.getSize()
    : 0;
}

int cdbDML::getBindCount() const
{
   return bind_vars != 0 ?
      bind_vars->array.getSize()
    : 0;
}


// Hinzugefuegte Events
// ====================

bool cdbDML::onEnter(cdbCursor& cu)
{
   if ( define_vars != 0 ) {
      for ( int i = 0 ; i < define_vars->array.getSize() ; i++ ) {
         if ( define_vars->array[i] != 0 )
            cu.define(i, define_vars->array[i]);
      }
   }

   if ( bind_vars != 0 ) {
      for ( int i = 0 ; i < bind_vars->array.getSize() ; i++ ) {
         if ( bind_vars->array[i] != 0 )
            cu.bind(i, bind_vars->array[i]);
      }
   }

   return true;
}

bool cdbDML::onExec(cdbCursor& cu)
{
   cu.exec();

   if ( getDefineCount() > 0 && !cu.fetch() ) {
      cBase::DbgError("cdbDML: fetch data failed");
      return false;
   }

   return true;
}

bool cdbDML::onLeave(cdbCursor& /*cu*/)
{
   return true;
}


// Ueberschriebene Events
// ======================

#define PREFETCH_COUNT 1

void cdbDML::onExecAction(cdbDatabase *db, int /*func*/)
{
   cdbCursor cu(*db, PREFETCH_COUNT);
   current_cu = &cu;

   try {

      if ( stmt.getType() != SQL::STMT_NONE )
         cu.compile(stmt);

      last_rc = onEnter(cu) && onExec(cu) && onLeave(cu);

      if ( !last_rc )
         cBase::DbgError("cdbDML: exec failed");

   } catch ( const cErrBase& err ) {
      last_error = err;
      last_rc = false;
   }

   current_cu = 0;
}

void cdbDML::onStopAction()
{
   current_cu->halt();
}

cString cdbDML::onGetSignature()
{
   return "DML " + cString(getSQL());
}


