// ===========================================================================
// edb_var.cpp                                                  ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csVar
//           |
//           +-cdbVar         -
//
// ===========================================================================

#include "dbi/edb_var.hpp"
#include "base/eb_array.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_sema.hpp"
#include "store/es_var.hpp"
#include "dbi/edb_sql.hpp"
#include "dbi/edb_transaction.hpp"
#include "dbi/edb_cursor_ex.hpp"

#endif /*__INTERFACE__*/




// Lokale Daten
// ===========================================================================

#ifdef __ECL_DEBUG__
   #define ACTION_TIMEOUT   -1   /* endless */
#else
   #define ACTION_TIMEOUT 7500   /* msec */
#endif

enum ACTIONS {
   ACTION_REFETCH,   // Ausfuehren der Aktionen von refetch()
};




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbVar
// ---------------------------------------------------------------------------
//
// Ermoeglicht das Binden einer Read-Only-Storage an einen SQL-SELECT-
// Befehl. Dieser muss so formuliert sein, dass genau ein Datensatz mit
// einer Ergebnisvariablen geliefert wird. Werden Parametervariablen an
// die cdbVar gebunden, aktualisiert sich diese automatisch bei Aenderung
// einer der Parametervariablen.
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--cdbVar
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbVar : public csVar, public cdbTAObject {
   ECL_DECLARE(cdbVar,csVar)

public:

   // Default-Konstruktor
   cdbVar(cdbTransaction *ta, SQL::SELECT select, int flags = 0);
   // Default-Konstruktor
   cdbVar(cdbTransaction *ta, SQL::SELECT select, int width, int prec, int flags = 0);
   // Default-Konstruktor
   cdbVar(cdbTransaction *ta, SQL::SELECT select, TYPE type, int flags = 0);
   // Default-Konstruktor
   cdbVar(cdbTransaction *ta, SQL::SELECT select, TYPE type, int width, int prec, int flags = 0);
   // Destruktor
   ~cdbVar();


   // Flags
   // =====

   enum FLAGS { fStart = csVar::fUser,
      fWasFetched = fStart << 0,  // Variablenwert bereits geladen
      fUser       = fStart << 1   // Benutzerdefinierte Flags
   };


   // Parametervariablen
   // ==================

   // Binden einer Parametervariablen
   void bind(int n, csStorage *store);
   // Anzahl gebundener Parametervariablen erfragen
   int getBindCount() const;


   // Sonstiges
   // =========

   // Auszufuehrendes SELECT-Statement erfragen
   inline SQL::SELECT getSQL() const
      { return select; }


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den Wert evtl. neu zu laden
   bool onRefetch();
   // Wird aufgerufen, um zu pruefen, ob das Feld Read-Only ist
   bool onCheckReadOnly() const;

   // Wird aufgerufen, um die Aktion 'func' auszufuehren
   void onExecAction(cdbDatabase *db, int func);
   // Wird aufgerufen, um den Abbruch der aktuellen Aktion anzufordern
   void onStopAction();
   // Wird aufgerufen, um eine textuelle Signatur der Aktion zu ermitteln
   cString onGetSignature();


private:

   SQL::SELECT select;        // Auszufuehrendes SELECT-Statement
   cEventSem wait_action;     // Warten auf Beendigung einer Aktion
   cErrBase last_error;       // Zuletzt aufgetretener Fehler
   bool last_rc;              // Ergebnis der letzten DB-Operation

   struct VARS;
   VARS *bind_vars;           // Zeiger auf Feld mit Parametervariablen

   // Intern: Ausfuehren der Aktionen bei refetch()
   void execRefetch(cdbDatabase *db);
   // Intern: Wird aufgerufen, wenn sich eine der gebundenen Variablen aendert
   void onEvtBindVarModified();

};

#endif /*__INTERFACE__*/


// Implementierung cdbVar
// ===========================================================================

struct cdbVar::VARS {
   cArray<csStorage*,csStorage*> array;
};

cdbVar::cdbVar(cdbTransaction *ta, SQL::SELECT select, int flags) :
   csVar(0, 0, -1, flags, tNone), cdbTAObject(ta),
   last_error(cErrBase::errNoError)
{
   cdbVar::select = select;
   cdbVar::bind_vars = 0;
}

cdbVar::cdbVar(cdbTransaction *ta, SQL::SELECT select, int width, int prec, int flags) :
   csVar(0, width, prec, flags, tNone), cdbTAObject(ta),
   last_error(cErrBase::errNoError)
{
   cdbVar::select = select;
   cdbVar::bind_vars = 0;
}

cdbVar::cdbVar(cdbTransaction *ta, SQL::SELECT select, TYPE type, int flags) :
   csVar(0, 0, -1, flags, type), cdbTAObject(ta),
   last_error(cErrBase::errNoError)
{
   cdbVar::select = select;
   cdbVar::bind_vars = 0;
}

cdbVar::cdbVar(cdbTransaction *ta, SQL::SELECT select, TYPE type, int width, int prec, int flags) :
   csVar(0, width, prec, flags, type), cdbTAObject(ta),
   last_error(cErrBase::errNoError)
{
   cdbVar::select = select;
   cdbVar::bind_vars = 0;
}

cdbVar::~cdbVar()
{
   delete bind_vars;
}


// Parametervariablen
// ==================

void cdbVar::bind(int n, csStorage *store)
{
   if ( __ECL_ASSERT1__(n >= 0 && store != 0) ) {
      if ( bind_vars == 0 )
         bind_vars = new0 VARS;
      if ( bind_vars->array.getSize() <= n )
         bind_vars->array.setSize(n + 1);
      bind_vars->array[n] = store;
      // Benachrichtigung beim Modify der Bind-Variablen:
      store->addEvent(evtValueModified, this, (EVFUNC)onEvtBindVarModified);
   }
}

int cdbVar::getBindCount() const
{
   return bind_vars != 0 ?
      bind_vars->array.getSize()
    : 0;
}


// Refetch
// =======

bool cdbVar::onRefetch()
{
   if ( !getFlags(fWasFetched) ) {
      setFlags(fWasFetched, true);

      last_error = cErrBase(cErrBase::errNoError);
      wait_action.reset();

      cdbTAObject::startAction(ACTION_REFETCH);

      if ( !wait_action.wait(ACTION_TIMEOUT) ) {
         setNull();
         throw cErrBase(cErrBase::errTimeout);
      }
      if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError ) {
         setNull();
         throw last_error;
      }

      signalModify();
      return last_rc;
   }

   return true;
}

void cdbVar::execRefetch(cdbDatabase *db)
{
   try {

      cdbCursorEx cu(*db);
      cu.compile(select);

      if ( bind_vars != 0 ) {
         for ( int i = 0 ; i < bind_vars->array.getSize() ; i++ ) {
            if ( bind_vars->array[i] != 0 )
               cu.bind(i, bind_vars->array[i]);
         }
      }

      cu.exec();
      __ECL_ASSERT1__(cu.getFieldCount() == 1);

      TYPE demand_type = csVar::onGetType();
      int demand_width = csVar::onGetWidth();
      int demand_prec = csVar::onGetPrec();

      if ( cu.fetch() ) {

         TYPE new_type = demand_type == tNone ? cu.getFieldType(0) : demand_type;
         int new_width = demand_width <= 0 ? cu.getFieldWidth(0) : demand_width;
         int new_prec = demand_prec < 0 ? cu.getFieldPrec(0) : demand_prec;

         setType(new_type);
         setWidth(new_width);
         setPrec(new_prec);
         setFlags(fThousandSep, false);

         switch ( new_type ) {
         case csStorage::tInt:
            {
               int value;
               newBuffer(sizeof value);
               initFrom(&value, sizeof value, !cu.get(0, value));
            }
            break;
         case csStorage::tDouble:
            {
               double value;
               newBuffer(sizeof value);
               initFrom(&value, sizeof value, !cu.get(0, value));
               setFlags(fThousandSep, true);
            }
            break;
         case csStorage::tTime:
            {
               cTime value;
               newBuffer(sizeof value);
               initFrom(&value, sizeof value, !cu.get(0, value));
            }
            break;
         case csStorage::tDate:
            {
               cDate value;
               newBuffer(sizeof value);
               initFrom(&value, sizeof value, !cu.get(0, value));
            }
            break;
         case csStorage::tDateTime:
            {
               cDateTime value;
               newBuffer(sizeof value);
               initFrom(&value, sizeof value, !cu.get(0, value));
            }
            break;
         case csStorage::tChar:
            {
               char value;
               newBuffer(sizeof value);
               initFrom(&value, sizeof value, !cu.get(0, value));
            }
            break;
         case csStorage::tString:
            {
               cString value;
               int buffer_size = cu.getFieldSize(0) + 1;
               newBuffer(buffer_size);
               bool ok = cu.get(0, value);
               initFrom((const char *)value, value.getLength() + 1, !ok);
            }
            break;
         }

      } else {

         initFrom(0, 0, true);

      }

      last_rc = true;

   } catch ( const cErrBase& err ) {
      last_rc = false;
      last_error = err;
   }

   wait_action.set();
}

bool cdbVar::onCheckReadOnly() const
{
   return true;
}

void cdbVar::onEvtBindVarModified()
{
   setFlags(fWasFetched, false);
   onRefetch();
}


// Ueberschriebene Events
// ======================

void cdbVar::onExecAction(cdbDatabase *db, int func)
{
   switch ( func ) {
   case ACTION_REFETCH: execRefetch(db); break;
   }
}

void cdbVar::onStopAction()
{
}

cString cdbVar::onGetSignature()
{
   return "VAR FROM " + cString(getSQL());
}

