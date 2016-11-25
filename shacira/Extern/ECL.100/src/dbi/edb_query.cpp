// ===========================================================================
// edb_query.cpp                                                ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csQuery
//           |
//           +-cdbQuery        - Abfragen von Daten aus Datenbanken
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <ctype.h>

#include "dbi/edb_query.hpp"
#include "dbi/edb_function.hpp"
#include "dbi/edb_row.hpp" /* nur wg. makeCondExact() */
#include "base/eb_osver.hpp"
#include "base/eb_array.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_query.hpp"
#include "dbi/edb_cursor_ex.hpp"
#include "dbi/edb_transaction.hpp"
#include "base/eb_sema.hpp"

#endif /*__INTERFACE__*/




// Lokale Daten
// ===========================================================================

enum ACTIONS {
   ACTION_START,     // Ausfuehren der Aktionen von onStart()
   ACTION_START1,    // Ausfuehren der Aktionen von onStart1()
   ACTION_OPEN,      // Ausfuehren der Aktionen von onOpen()
   ACTION_CLOSE,     // Ausfuehren der Aktionen von onClose()
   ACTION_REWIND,    // Ausfuehren der Aktionen von onRewind()
   ACTION_FETCH      // Ausfuehren der Aktionen von onFetch()
};




// Lokale Funktionen
// ===========================================================================

static void ShowError(const cErrBase& err)
{
   char msg[2048]; err.getString(msg, sizeof msg);
   cBase::DbgError("cdbQuery: caught error: %s", msg);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbQuery
// ---------------------------------------------------------------------------
//
// Erweitert die csQuery-Klasse zur echten Datenbank-Abfrage. Die eigentliche
// Abfrage erfolgt unter Verwendung eines cTable-Objektes in einem Hintergrund-
// Thread (via cdbTransaction-Objekt).
//
// cBase
//  +--cBaseStorage
//      +--csQuery
//          +--cdbQuery
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbQuery : public csQuery, public cdbTAObject {
   ECL_DECLARE(cdbQuery,csQuery)

public:

   // Konstruktor fuer "einfache" Datenbankabfrage
   cdbQuery(cdbTransaction *ta, int flags, SQL::SELECT select);
   // Konstruktor fuer hierarchische Datenbankabfrage
   cdbQuery(cdbTransaction *ta, int flags, SQL::SELECT select,
            SQL::WHERE connect_by, SQL::WHERE start_with);
   // Modify-Copy-Konstruktor
   cdbQuery(const cdbQuery& other, int flags = 0,
            SQL::WHERE add_where = SQL::WHERE());
   // Destruktor
   ~cdbQuery();


   // Parametervariablen
   // ==================

   // Binden von Parametervariablen
   void bind(int n, csStorage& var);
   // Bindung an Variable entfernen
   void bind(int n);
   // Gebundene Parametervariable ermitteln
   csStorage *getBoundVar(int n) const;


   // Sonstiges
   // =========

   // SQL-SELECT-Anweisung erfragen
   inline SQL::SELECT getSQL() const
      { return select; }
   // SQL-SELECT-Anweisung setzen
   inline void setSQL(SQL::SELECT sql)
      { select = sql; }

   // Defaultwert von Feld 'fld' erfragen (fuer neuen Datensatz)
   inline cString getNewRowDefValue(int fld, cString suggested_value = cString()) const
      { return onGetNewRowDefValue(fld, suggested_value); }
   // Zusaetzliches Einfuege-Statement erfragen (fuer neuen Datensatz)
   inline cString getNewRowAddStmt(int stmt) const
      { return onGetNewRowAddStmt(stmt); }


protected:

   // Events
   // ======

   // Ereignisgesteuerte Abfragesteuerung
   // -----------------------------------

   // Wird aufgerufen, um ereignisgesteuerte Abfrage zu starten
   bool onStart(const EVENT& event);
   // Wird aufgerufen, um Ereignisgesteuerte Einzelabfrage zu starten
   bool onStart1(const EVENT& event, cString key);
   // Wird aufgerufen zum vorzeitigen Beenden der Abfrage
   bool onStop();
   // Wird aufgerufen, um die Hauptschleife der Abfrage zu realisieren
   bool onLoop(const EVENT& event);


   // Sequentielle Abfragesteuerung
   // -----------------------------

   // Wird aufgerufen, um sequentielle Abfrage zu starten
   bool onOpen();
   // Wird aufgerufen, um sequentielle Abfrage zu beenden
   void onClose();
   // Wird aufgerufen, um an die Position vor dem ersten Datensatz zu springen
   bool onRewind();
   // Wird aufgerufen, um zum naechsten Datensatz zu gehen und diesen laden
   bool onFetch();


   // Verfuegbarkeit von Informationen
   // --------------------------------

   // Wird aufgerufen, um die aktuelle Verfuegbarkeit zu pruefen
   bool onCheckAvailability(QUERY_INFOS qci) const;


   // Einfuegen neuer Datensaetze
   // ---------------------------

   // Wird aufgerufen, um den Schluesselwert eines neuen Datensatzes zu ermitteln
   virtual cString onGetNewRowKey() const;
   // Wird aufgerufen, um den Defaultwert des 'fld'-ten Feldes zu ermitteln
   virtual cString onGetNewRowDefValue(int fld, cString suggested_value) const;
   // Wird aufgerufen, um die zusaetzlichen Einfuege-Statements zu erfragen
   virtual cString onGetNewRowAddStmt(int stmt) const;


   // Sortierung
   // ----------

   // Wird aufgerufen, um die Sortierreihenfolge der Abfrage festzulegen
   void onSetOrder(int *fld, int *dir, int count);


   // Ausfuehrung (aus cdbTAObject)
   // -----------------------------

   // Wird aufgerufen, um die Aktion 'func' auszufuehren
   void onExecAction(cdbDatabase *db, int func);
   // Wird aufgerufen, um den Abbruch der aktuellen Aktion anzufordern
   void onStopAction();
   // Wird aufgerufen, um eine textuelle Signatur der Aktion zu ermitteln
   cString onGetSignature();


   // Beschreibung
   // ------------

   // Wird aufgerufen, um die Gesamtbeschreibung der Abfrage zu ermitteln (QUERY_STYLE)
   int onGetQueryStyle() const;
   // Wird aufgerufen, um die Anzahl Felder im Datensatz zu ermitteln
   int onGetQueryFieldCount() const;
   // Wird aufgerufen, um den Wert des Schluesselfeldes 'key_name' zu ermitteln
   cString onGetKeyValue(cString key_name) const;

   // Wird aufgerufen, um die Beschreibung einer Spalte zu ermitteln (FIELD_STYLE)
   int onGetFieldStyle(int fld) const;
   // Wird aufgerufen, um den Typ eines Feldes zu ermitteln
   TYPE onGetFieldType(int fld) const;

   // Wird aufgerufen, um den Namen eines Feldes zu ermitteln
   cString onGetFieldName(int fld) const;
   // Wird aufgerufen, um den Titel der Spalte zu ermitteln
   cString onGetTitleText(int fld) const;

   // Wird aufgerufen, um den Tabellennamen eines Feldes zu ermitteln
   cString onGetRecordBaseName(int fld) const;
   // Wird aufgerufen, um den Basisnamen eines Feldes zu ermitteln
   cString onGetRecordBaseFieldName(int fld) const;

   // Wird aufgerufen, um die maximale Groesse eines Feldes zu ermitteln
   int onGetFieldBufferSize(int fld) const;
   // Wird aufgerufen, um die guenstigste Anzeigebreite zu ermitteln
   int onGetFieldViewSize(int fld) const;
   // Wird aufgerufen, um die maximale Feldbreite zu ermitteln
   int onGetFieldWidth(int fld) const;
   // Wird aufgerufen, um die Anzahl Nachkommastellen zu ermitteln
   int onGetFieldPrec(int fld) const;


   // Werte erfragen
   // --------------

   // Wird aufgerufen, um den NULL-Zustand des Feldes zu ermitteln
   bool onGetNull(int fld) const;

   // Wird aufgerufen, um einen int-Wert aus Feld 'fld' zu lesen
   bool onGetInt(int fld, int& buf) const;
   // Wird aufgerufen, um einen double-Wert aus Feld 'fld' zu lesen
   bool onGetDouble(int fld, double& buf) const;
   // Wird aufgerufen, um einen cTime-Wert aus Feld 'fld' zu lesen
   bool onGetTime(int fld, cTime& buf) const;
   // Wird aufgerufen, um einen cDate-Wert aus Feld 'fld' zu lesen
   bool onGetDate(int fld, cDate& buf) const;
   // Wird aufgerufen, um einen cDateTime-Wert aus Feld 'fld' zu lesen
   bool onGetDateTime(int fld, cDateTime& buf) const;
   // Wird aufgerufen, um einen char-Wert aus Feld 'fld' zu lesen
   bool onGetChar(int fld, char& buf) const;
   // Wird aufgerufen, um einen cString-Wert aus Feld 'fld' zu lesen
   bool onGetString(int fld, cString& buf) const;


private:

   struct QUERY_DATA;         // Deklaration des Datentyps fuer interne Daten
   QUERY_DATA *qd;            // Zeiger auf interne Daten

   SQL::SELECT select;        // SQL-SELECT-String
   SQL::WHERE connect_by;     // Link-Bedingung fuer hierarchische Abfrage
   SQL::WHERE start_with;     // Top-Bedingung fuer hierarchische Abfrage

   // Ausfuehren der Aktionen bei onStart()
   void execStart(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onStart1()
   void execStart1(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onOpen()
   void execOpen(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onClose()
   void execClose(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onRewind()
   void execRewind(cdbDatabase *db);
   // Ausfuehren der Aktionen bei onFetch()
   void execFetch(cdbDatabase *db);

   // Link-Bedingung aus 'connect_by', 'start_with' und getParentKeys() erzeugen
   SQL::WHERE makeLinkCond() const;
   // Wird aufgerufen, um den Wert des Schluesselfeldes 'key_name' zu ermitteln
   cString getKeyValue2(cString key_name) const;

   // Query-Data erzeugen, falls noch nicht vorhanden
   void makeQueryData();

};

#endif /*__INTERFACE__*/


// Implementierung cdbQuery
// ===========================================================================

struct VAR {
   VAR() { var = 0; }
   csStorage *var;
};

typedef cArray<VAR, const VAR&> VAR_ARRAY;
typedef cArray<csQuery::TYPE, csQuery::TYPE> TYPE_ARRAY;

struct cdbQuery::QUERY_DATA {

   QUERY_DATA() : last_error(cErrBase::errNoError)
   {
      current_cu = 0; //>>> wait_action = 0;
      field_count = fetch_count = 0;
   }

   ~QUERY_DATA()
   {
      delete current_cu;
      //>>> delete wait_action;
   }

   EVENT current_ev;             // Aktueller Event
   cdbCursorEx *current_cu;      // Zeiger auf aktuellen Cursor (oder 0)
   static cMutexSem protect_cu;  // Personenschutz fuer den Cursor
   //>>> cEventSem *wait_action;       // Warten auf Beendigung einer Aktion

   int fetch_count;              // Anzahl gelesener Datensaetze
   int field_count;              // Anzahl Felder in der Ergebnismenge
   bool last_fetch;              // Ergebnis der letzten fetch()-Operation
   cErrBase last_error;          // Zuletzt aufgetretener Fehler

   SQL::FIELDS key_values;       // Wert von 'key' bei onStart1()
   SQL::FIELDS key_fields;       // Schluesselfelder beim letzten exec()

   VAR_ARRAY bind_vars;          // cArray mit csStorage-Zeigern
   TYPE_ARRAY field_types;       // cArray mit gepspeicherten Feldtypen

};

cMutexSem cdbQuery::QUERY_DATA::protect_cu;


// Konstruktoren
// =============

cdbQuery::cdbQuery(cdbTransaction *ta, int flags, SQL::SELECT select) :
   csQuery(flags), cdbTAObject(ta)
{
   cdbQuery::qd = 0;
   cdbQuery::select = select;
}

cdbQuery::cdbQuery(cdbTransaction *ta, int flags, SQL::SELECT select,
                   SQL::WHERE connect_by, SQL::WHERE start_with) :
   csQuery(flags), cdbTAObject(ta)
{
   cdbQuery::qd = 0;
   cdbQuery::select = select;
   cdbQuery::connect_by = connect_by;
   cdbQuery::start_with = start_with;
}

cdbQuery::cdbQuery(const cdbQuery& other, int flags,
                   SQL::WHERE add_where) :
   csQuery(other), cdbTAObject(other)
{
   setFlags(flags);

   // Permanent-Flag ruecksetzen, wenn in 'other' gesetzt,
   // aber nicht in 'flags'
   if ( other.getFlags(fPermanent) && !(flags & fPermanent) )
      setFlags(fPermanent, false);

   cdbQuery::qd = 0;
   cdbQuery::select = other.select & add_where;
}

cdbQuery::~cdbQuery()
{
   delete qd;
}


// Parametervariablen
// ==================

void cdbQuery::bind(int n, csStorage& var)
{
   makeQueryData();

   if ( n >= qd->bind_vars.getSize() )
      qd->bind_vars.setSize(n + 1);

   qd->bind_vars[n].var = &var;
}

void cdbQuery::bind(int n)
{
   makeQueryData();

   if ( n >= qd->bind_vars.getSize() )
      qd->bind_vars.setSize(n + 1);

   qd->bind_vars[n].var = 0;
}

csStorage * cdbQuery::getBoundVar(int n) const
{
   return qd != 0 && __ECL_ASSERT1__(n >= 0 && n < qd->bind_vars.getSize()) ?
      qd->bind_vars[n].var
    : 0;
}


// Events
// ======

// Ereignisgesteuerte Abfragesteuerung
// -----------------------------------

bool cdbQuery::onStart(const EVENT& event)
{
   makeQueryData();
   qd->current_ev = event;
   qd->key_values = cString();
   setFlags(fStopReq, false);

   if ( cOsVersion::isW32() ) {
      // Win32: Make it the single-thread way
      if ( open() ) {
         onQueryStart(event);
         while ( fetch() ) {
            if ( !signalDataReady(event) || getFlags(fStopReq) )
               break;
         }
         close();
      }
      onQueryEnd(event);
   } else {
      // Other OS: Make it the multi-thread way
      cdbTAObject::startAction(ACTION_START);
   }

   return true;
}

bool cdbQuery::onStart1(const EVENT& event, cString key)
{
   makeQueryData();
   qd->current_ev = event;
   qd->key_values = key;
   setFlags(fStopReq, false);

   if ( key.isEmpty() )
      key = "<NULL>";

   if ( cOsVersion::isW32() ) {
      // Win32: Make it the single-thread way
      if ( open() ) {
         onQueryStart(event);
         if ( fetch() )
            signalDataReady(event);
         close();
      }
      onQueryEnd(event);
   } else {
      // Other OS: Make it the multi-thread way
      cdbTAObject::startAction(ACTION_START1);
   }

   return true;
}

bool cdbQuery::onStop()
{
   setFlags(fStopReq);
   return true;
}

bool cdbQuery::onLoop(const EVENT& event)
{
   makeQueryData();
   qd->fetch_count = 0;

   if ( getFlags(fStopReq) ) {

      /*TBD:*/cBase::DbgOut(0, "STOP request before first fetch");

   } else {

      while ( qd->current_cu->fetch() ) {
         if ( getFlags(fStopReq) ) {
            /*TBD:*/cBase::DbgOut(0, "STOP request after fetch_count = %d", qd->fetch_count);
            break;
         }
         if ( !signalDataReady(event) )
            return false;
         qd->fetch_count++;
      }

   }

   return true;
}


// Sequentielle Abfragesteuerung
// -----------------------------

bool cdbQuery::onOpen()
{
   makeQueryData();
   qd->last_error = cErrBase(cErrBase::errNoError);
   //>>> qd->wait_action.reset();
   cdbTAObject::callAction(ACTION_OPEN);
   //>>> if ( !qd->wait_action.wait(ACTION_TIMEOUT) )
   //>>>    throw cErrBase(cErrBase::errTimeout);
   if ( cErrBase::ERR_TYPE(qd->last_error) != cErrBase::errNoError ) {
      ShowError(qd->last_error);
      throw qd->last_error;
   }
   return true;
}

void cdbQuery::onClose()
{
   makeQueryData();
   qd->last_error = cErrBase(cErrBase::errNoError);
   //>>> qd->wait_action.reset();
   cdbTAObject::callAction(ACTION_CLOSE);
   //>>> qd->wait_action.wait(ACTION_TIMEOUT);
   //>>> if ( !qd->wait_action.wait(ACTION_TIMEOUT) )
   //>>>    throw cErrBase(cErrBase::errTimeout);
   if ( cErrBase::ERR_TYPE(qd->last_error) != cErrBase::errNoError ) {
      ShowError(qd->last_error);
      throw qd->last_error;
   }
}

bool cdbQuery::onRewind()
{
   makeQueryData();
   qd->last_error = cErrBase(cErrBase::errNoError);
   //>>> qd->wait_action.reset();
   cdbTAObject::callAction(ACTION_REWIND);
   //>>> qd->wait_action.wait(ACTION_TIMEOUT);
   //>>> if ( !qd->wait_action.wait(ACTION_TIMEOUT) )
   //>>>    throw cErrBase(cErrBase::errTimeout);
   if ( cErrBase::ERR_TYPE(qd->last_error) != cErrBase::errNoError ) {
      ShowError(qd->last_error);
      throw qd->last_error;
   }
   return true;
}

bool cdbQuery::onFetch()
{
   makeQueryData();
   qd->last_error = cErrBase(cErrBase::errNoError);
   //>>> qd->wait_action.reset();
   cdbTAObject::callAction(ACTION_FETCH);
   //>>> qd->wait_action.wait(ACTION_TIMEOUT);
   //>>> if ( !qd->wait_action.wait(ACTION_TIMEOUT) )
   //>>>    throw cErrBase(cErrBase::errTimeout);
   if ( cErrBase::ERR_TYPE(qd->last_error) != cErrBase::errNoError ) {
      ShowError(qd->last_error);
      throw qd->last_error;
   }
   return qd->last_fetch;
}


// Verfuegbarkeit von Informationen
// --------------------------------

bool cdbQuery::onCheckAvailability(QUERY_INFOS qci) const
{
   return qd != 0 ?
      csQuery::onCheckAvailability(qci)
    : false;
}


// Einfuegen neuer Datensaetze
// ---------------------------

cString cdbQuery::onGetNewRowKey() const
{
   cdbTransaction *ta = (cdbTransaction*)(void*)getTA();

   // Aktuellen Wert fuer key_values lesen (falls spaeter nicht ermittelbar)
   cString buf;

   if ( hasData() )
      get(fldKey, buf);

   SQL::FIELDS key_values = SQL::FIELDS(buf);
   SQL::FIELDS key_fields = SQL::FIELDS(getFieldName(cdbQuery::fldKey));

   int key_field_count = key_fields.getFieldCount();
   int key_values_count = key_values.getFieldCount();

   if ( key_field_count != key_values_count ) {
      for ( int i = key_values_count ; i < key_field_count ; i++ ) {
         key_values.setField(i, "NULL");
      }
   }

   if ( key_field_count > 0 ) {

      #define __Get_Key_Values_Experimental__
      #ifdef __Get_Key_Values_Experimental__
         // key_values aus der WHERE-Bedingung extrahieren (wenn moeglich)
         SQL::WHERE where = getSQL().getWhere();
         for ( int cnd = 0 ; cnd < where.getCondCount() ; cnd++ ) {
            SQL::COND cond = where.getCond(cnd);
            if ( cond.getRelOp() == SQL::REL_EQ ) {
               cString key = SQL::FIELD(cond.getLeftExpr()).getFieldName(false);
               cString value = cond.getRightExpr();
               if ( isdigit(value[0]) || value[0] == '\'' || value[0] == '$' ) {
                  for ( int kfld = 0 ; kfld < key_field_count ; kfld++ ) {
                     if ( key.compareNoCase(cString(key_fields.getField(kfld))) == 0 ) {
                        key_values.setField(kfld, SQL::FIELD(value));
                     }
                  }
               }
            }
         }
      #endif

      for ( int fld = 0 ; fld < key_field_count ; fld++ ) {

         // Gewuenschten Wert fuer Spalte 'fld' erfragen
         cString new_value = onGetNewRowDefValue(fld, key_values.getField(fld));

         if ( !new_value.isEmpty() ) {

            key_values.setField(fld, new_value);

         } else if ( fld == key_field_count - 1 ) {

            if ( 0 /*... == tString*/ ) {
               // SELECT MAX(TO_NUMBER(SUBSTR(field,2))) FROM table WHERE where AND SUBSTR(field,1,1)='N';
               // Erzeugt Primaerschluessel der Form 'N0', 'N1', 'N2', ...
            } else {
               SQL::FIELD  key_fld = key_fields.getField(fld);
               SQL::FIELDS fields  = SQL::FIELDS("MAX(" + cString(key_fld) + ")");
               SQL::FROM   from    = select.getFrom();
               SQL::WHERE  where   = select.getWhere();
               cdbFunction func(ta);
               int key_val = func.selectInt(SQL::SELECT(fields, from, where)) + 1;
               key_values.setField(fld, SQL::FIELD(Str(key_val)));
            }

         }

      }

   }

   return cString(key_values);
}

cString cdbQuery::onGetNewRowDefValue(int /*fld*/, cString /*fld_value*/) const
{
   // 'fld_value' gibt den Vorschlagswert fuer Feld 'fld' an. Wird ein
   // leerer String zurueckgegeben, hat das Feld keinen Defaultwert.
   // Ansonsten kann ein konstanter Wert zurueckgegeben werden, der
   // in das INSERT-Statement aufgenommen wird.

   return cString();
}

cString cdbQuery::onGetNewRowAddStmt(int /*stmt*/) const
{
   // Es koennen beliebig viele zusaetzliche SQL-Strings zurueckgegeben werden.
   // Der Aufrufer fraegt diese nacheinander an, beginnend mit 'stmt'==0.
   // Wird ein leerer String zurueckgegeben, ist dies das Kennzeichen fuer
   // das letzte zusaetzliche Statement. Dabei wird der spezielle Marker $**0
   // mit dem Wert des ersten Schluesselbestandteils ersetzt, $**1 mit dem
   // Wert des zweiten Schluesselbestandteils, usw. (max $**9).
   //
   // -TE- 25.11.2001: Die Marker gelten jetzt fuer die gesamte Werteliste
   // des INSERT-Statements. Es koennen jedoch nur die ersten 10 Werte dieser
   // Liste eingebunden werden.

   return cString();
}


// Sortierung
// ----------

void cdbQuery::onSetOrder(int *fld, int *dir, int count)
{
   SQL::ORDERBY orderby;

   for ( int i = 0 ; i < count ; i++ ) {
      cString fld_name = getFieldName(fld[i]);

      // Kein Feldname verfuegbar? Spaltennummer benutzen!
      if ( fld_name.isEmpty() && fld[i] >= 0 )
         fld_name = Str(fld[i]);

      // Sortierrichtung einarbeiten
      if ( dir[i] < 0 ) {
         orderby = orderby + SQL::FIELD(getFieldName(fld[i])+ " DESC");
      } else {
         orderby = orderby + SQL::FIELD(getFieldName(fld[i])+ " ASC");
      }
   }

   select.setOrderBy(orderby);
}


// Ausfuehrung (aus cdbTAObject)
// -----------------------------

void cdbQuery::onExecAction(cdbDatabase *db, int func)
{
   switch ( func ) {
   case ACTION_START:   execStart(db); break;
   case ACTION_START1:  execStart1(db); break;
   case ACTION_OPEN:    execOpen(db); break;
   case ACTION_CLOSE:   execClose(db); break;
   case ACTION_REWIND:  execRewind(db); break;
   case ACTION_FETCH:   execFetch(db); break;
   }
}

void cdbQuery::execStart(cdbDatabase *db)
{
   makeQueryData();

   try {

      qd->protect_cu.request();
      delete qd->current_cu;
      qd->current_cu = new0 cdbCursorEx(*db, 1/*TBD:100*/);
      qd->protect_cu.release();

      SQL::SELECT do_select = select & makeLinkCond();
      qd->current_cu->compile(do_select);

      VAR_ARRAY& vars = qd->bind_vars;

      for ( int i = 0 ; i < vars.getSize() ; i++ ) {
         if ( vars[i].var != 0 ) {
            qd->current_cu->bind(i, vars[i].var);
         } else {
            qd->current_cu->bind(i);
         }
      }

      qd->current_cu->exec();
      qd->key_fields = qd->current_cu->getFieldName(fldKey); // save for later use...

      installFilter(getFieldCount());

      qd->field_types.removeAll();
      qd->field_count = qd->current_cu->getFieldCount();
      qd->fetch_count = 0;

      onQueryStart(qd->current_ev);

   } catch ( ... ) {
      onQueryEnd(qd->current_ev);
      deinstallFilter();
      delete qd->current_cu;
      qd->current_cu = 0;
      throw;
   }

   try {
      onLoop(qd->current_ev);
   } catch ( ... ) {
      onQueryEnd(qd->current_ev);
      deinstallFilter();
      delete qd->current_cu;
      qd->current_cu = 0;
      throw;
   }

   onQueryEnd(qd->current_ev);
   deinstallFilter();

   delete qd->current_cu;
   qd->current_cu = 0;
}

void cdbQuery::execStart1(cdbDatabase *db)
{
   makeQueryData();

   try {

      qd->protect_cu.request();
      delete qd->current_cu;
      qd->current_cu = new0 cdbCursorEx(*db, 1);
      qd->protect_cu.release();

      // Aktuelles SELECT kompilieren, damit Feldinformationen verfuegbar
      qd->current_cu->compile(select);

      SQL::WHERE where;
      if ( cString(qd->key_values) == "<NULL>" ) {
         where = "IS NULL";
      } else {
         SQL::FIELDS key_fields = SQL::FIELDS(getFieldName(fldKey));
         where = where & cdbRow::makeCondExact(key_fields, qd->key_values, this);
      }

      SQL::SELECT do_select = select & where;
      qd->current_cu->compile(do_select);

      VAR_ARRAY& vars = qd->bind_vars;

      for ( int i = 0 ; i < vars.getSize() ; i++ ) {
         if ( vars[i].var != 0 ) {
            qd->current_cu->bind(i, vars[i].var);
         } else {
            qd->current_cu->bind(i);
         }
      }

      qd->current_cu->exec();
      qd->key_fields = qd->current_cu->getFieldName(fldKey); // save for later use...

      installFilter(getFieldCount());

      qd->field_types.removeAll();
      qd->field_count = qd->current_cu->getFieldCount();
      qd->fetch_count = 0;

      onQueryStart(qd->current_ev);

   } catch ( ... ) {
      onQueryEnd(qd->current_ev);
      deinstallFilter();
      delete qd->current_cu;
      qd->current_cu = 0;
      throw;
   }

   try {
      onLoop(qd->current_ev);
   } catch ( ... ) {
      onQueryEnd(qd->current_ev);
      deinstallFilter();
      delete qd->current_cu;
      qd->current_cu = 0;
      throw;
   }

   onQueryEnd(qd->current_ev);
   deinstallFilter();

   delete qd->current_cu;
   qd->current_cu = 0;
}

void cdbQuery::execOpen(cdbDatabase *db)
{
   makeQueryData();

   try {

      qd->protect_cu.request();
      delete qd->current_cu;
      qd->current_cu = new0 cdbCursorEx(*db, 1/*TBD:100*/);
      qd->protect_cu.release();

      if ( cString(qd->key_values).isEmpty() ) {
         // "Normales" Open

         SQL::SELECT do_select = select & makeLinkCond();
         qd->current_cu->compile(do_select);

      } else {
         // Open ueber "start1()"

         // Aktuelles SELECT kompilieren, damit Feldinformationen verfuegbar
         qd->current_cu->compile(select);

         SQL::WHERE where;
         if ( cString(qd->key_values) == "<NULL>" ) {
            where = "IS NULL";
         } else {
            SQL::FIELDS key_fields = SQL::FIELDS(getFieldName(fldKey));
            where = where & cdbRow::makeCondExact(key_fields, qd->key_values, this);
         }

         SQL::SELECT do_select = select & where;
         qd->current_cu->compile(do_select);
      }

   } catch ( const cErrBase& err ) {
      qd->last_error = err;
      //>>> qd->wait_action.set();
      return;
   }

   qd->key_values = cString();
   execRewind(db);
}

void cdbQuery::execClose(cdbDatabase * /*db*/)
{
   makeQueryData();
   deinstallFilter();
   //>>> qd->wait_action.set();

   delete qd->current_cu;
   qd->current_cu = 0;
}

void cdbQuery::execRewind(cdbDatabase * /*db*/)
{
   makeQueryData();
   deinstallFilter();

   try {

      VAR_ARRAY& vars = qd->bind_vars;

      for ( int i = 0 ; i < vars.getSize() ; i++ ) {
         if ( vars[i].var != 0 ) {
            qd->current_cu->bind(i, vars[i].var);
         } else {
            qd->current_cu->bind(i);
         }
      }

      qd->current_cu->exec();
      qd->key_fields = qd->current_cu->getFieldName(fldKey); // save for later use...

      installFilter(getFieldCount());

      qd->field_types.removeAll();
      qd->field_count = qd->current_cu->getFieldCount();
      qd->fetch_count = 0;

   } catch ( const cErrBase& err ) {
      qd->fetch_count = 0;
      qd->field_count = 0;
      qd->last_error = err;
   }

   //>>> qd->wait_action.set();
}

void cdbQuery::execFetch(cdbDatabase * /*db*/)
{
   makeQueryData();

   try {
      qd->last_fetch = qd->current_cu->fetch();
      if ( qd->last_fetch ) qd->fetch_count++;
   } catch ( const cErrBase& err ) {
      qd->last_error = err;
   }

   //>>> qd->wait_action.set();
}

void cdbQuery::onStopAction()
{
   // TBD: ...
}

cString cdbQuery::onGetSignature()
{
   return "QUERY FROM " + cString(select.getFrom());
}


// Beschreibung
// ------------

int cdbQuery::onGetQueryStyle() const
{
   if ( !cString(connect_by).isEmpty() ) {
      return qstIsStructured | csQuery::onGetQueryStyle();
   } else {
      return csQuery::onGetQueryStyle();
   }
}

int cdbQuery::onGetQueryFieldCount() const
{
   return __ECL_ASSERT1__(qd && qd->current_cu) ?
      qd->current_cu->getFieldCount()
    : 0;
}

cString cdbQuery::getKeyValue2(cString key_name) const
{
   SQL::WHERE where = getSQL().getWhere();
   int qm_count = 0; // Zaehlt die Anzahl Fragezeichen im WHERE-Teil

   for ( int i = 0 ; i < where.getCondCount() ; i++ ) {
      SQL::COND cond = where.getCond(i);
      cString expr = cond.getRightExpr();
      if ( cond.getRelOp() == SQL::REL_EQ && !expr.isEmpty() ) {
         cString field = SQL::FIELD(cond.getLeftExpr()).getFieldName(false);
         if ( field.compareNoCase(key_name) == 0 ) {
            if ( expr == "?" ) {
               // Wert der gebundenen Variablen ermitteln
               csStorage *store = getBoundVar(qm_count);
               return store == 0 || !store->get(expr) ? 0 : expr;
            } else if ( expr.getLeft(3) == "$##" ) {
               // Wert der statisch gebundenen Variablen ermitteln
               int n = expr.getMid(3).getLong();
               return cdbCursor::getStaticBound(n);
            } else if ( isdigit(expr[0]) || expr[0] == '\'' ) {
               // Wert der Konstanten ermitteln
               return expr;
            }
         } else {
            // Zaehle die Anzahl Fragezeichen, um spaeter evtl. die korrekte
            // Binde-Nummer der Parametervariablen zu erhalten
            for ( int pos = 0 ; (pos = expr.getPos("?", pos) + 1) > 0 ; )
               qm_count++;
         }
      }
   }

   return 0;
}

cString cdbQuery::onGetKeyValue(cString key_name) const
{
   cString value = getKeyValue2(key_name);

   // Nichts gefunden? Dann mit umgekehrter Quotierung nochmal probieren!

   if ( value.isEmpty() ) {
      if ( key_name.getLeft(1) == "[" ) {
         return getKeyValue2(key_name.getMid(1, key_name.getLength() - 2));
      } else {
         return getKeyValue2("[" + key_name + "]");
      }
   }

   return value;
}

int cdbQuery::onGetFieldStyle(int fld) const
{
   if ( fld >= 0 ) {
      return fstVisible | fstReadOnly;
   }

   return csQuery::onGetFieldStyle(fld);
}

csQuery::TYPE cdbQuery::onGetFieldType(int fld) const
{
   if ( fld >= fldDescr ) {
      if ( __ECL_ASSERT1__(qd != 0) ) {
         if ( qd->current_cu != 0 ) {
            TYPE ft = qd->current_cu->getFieldType(fld);
            qd->field_types.setAtGrow(fld - fldDescr, ft);
            return ft;
         } else if ( qd->field_types.getSize() > fld - fldDescr ) {
            // Aufruf ausserhalb der Fetch-Zeit zulaessig;
            // liefert gespeicherten Feldtyp!
            return qd->field_types[fld - fldDescr];
         }
      }
      __ECL_ASSERT2__(0, ("cdbQuery::onGetFieldType: no type info for field %d", fld));
      return tNone;
   }

   return csQuery::onGetFieldType(fld);
}

cString cdbQuery::onGetFieldName(int fld) const
{
   if ( fld == fldKey && qd && !cString(qd->key_fields).isEmpty() )
      return qd->key_fields; // return key_fields remembered at 'exec()' time

   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->getFieldName(fld)
       : cString();
   }

   return csQuery::onGetFieldName(fld);
}

cString cdbQuery::onGetTitleText(int fld) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->getFieldLabel(fld)
       : cString();
   }

   return csQuery::onGetTitleText(fld);
}

cString cdbQuery::onGetRecordBaseName(int fld) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->getFieldBaseTableName(fld)
       : cString();
   }

   return csQuery::onGetRecordBaseName(fld);
}

cString cdbQuery::onGetRecordBaseFieldName(int fld) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->getFieldBaseName(fld)
       : cString();
   }

   return csQuery::onGetRecordBaseFieldName(fld);
}

int cdbQuery::onGetFieldBufferSize(int fld) const
{
   if ( fld >= fldDescr && __ECL_ASSERT1__(qd && qd->current_cu) ) {
      return getFilteredBufferSize(fld, qd->current_cu->getFieldBufferSize(fld));
   }

   return csQuery::onGetFieldBufferSize(fld);
}

int cdbQuery::onGetFieldViewSize(int fld) const
{
   if ( fld >= fldDescr ) {
      // TBD: Besserer Algorithmus
      return onGetFieldWidth(fld);
   }

   return csQuery::onGetFieldViewSize(fld);
}

int cdbQuery::onGetFieldWidth(int fld) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->getFieldWidth(fld)
       : 0;
   }

   return csQuery::onGetFieldWidth(fld);
}

int cdbQuery::onGetFieldPrec(int fld) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->getFieldPrec(fld)
       : 0;
   }

   return csQuery::onGetFieldPrec(fld);
}


// Werte erfragen
// --------------

bool cdbQuery::onGetNull(int fld) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->isNull(fld)
       : true;
   }

   return csQuery::onGetNull(fld);
}

bool cdbQuery::onGetInt(int fld, int& buf) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->get(fld, buf)
       : false;
   }

   return csQuery::onGetInt(fld, buf);
}

bool cdbQuery::onGetDouble(int fld, double& buf) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->get(fld, buf)
       : false;
   }

   return csQuery::onGetDouble(fld, buf);
}

bool cdbQuery::onGetTime(int fld, cTime& buf) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->get(fld, buf)
       : false;
   }

   return csQuery::onGetTime(fld, buf);
}

bool cdbQuery::onGetDate(int fld, cDate& buf) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->get(fld, buf)
       : false;
   }

   return csQuery::onGetDate(fld, buf);
}

bool cdbQuery::onGetDateTime(int fld, cDateTime& buf) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->get(fld, buf)
       : false;
   }

   return csQuery::onGetDateTime(fld, buf);
}

bool cdbQuery::onGetChar(int fld, char& buf) const
{
   if ( fld >= fldDescr ) {
      return __ECL_ASSERT1__(qd && qd->current_cu) ?
         qd->current_cu->get(fld, buf)
       : false;
   }

   return csQuery::onGetChar(fld, buf);
}

bool cdbQuery::onGetString(int fld, cString& buf) const
{
   if ( fld >= fldDescr ) {
      if ( __ECL_ASSERT1__(qd && qd->current_cu) && qd->current_cu->get(fld, buf) ) {
         callFilter(fld, buf);
         return true;
      }
      return false;
   }

   return false;
}


// Sonstiges
// =========

SQL::WHERE cdbQuery::makeLinkCond() const
{
   SQL::WHERE link_cond;

   if ( isStructured() ) {
      SQL::FIELDS parent_keys = getParentKey();

      if ( parent_keys.getFieldCount() == 0 ) {
         // Top-Level-Abfrage

         link_cond = start_with;

      } else {
         // Sub-Level-Abfrage

         int cond_count = connect_by.getCondCount();
         int parent_idx = 0;

         for ( int i = 0 ; i < cond_count ; i++ ) {
            SQL::COND cond = connect_by.getCond(i);
            if ( cond.getRightExpr() == "?" ) {
               cond = SQL::COND(
                  cond.getLeftExpr(),
                  cond.getRelOp(),
                  parent_keys.getField(parent_idx++)
               );
            }
            // TBD: Andere Bedingungen als AND erlauben:
            link_cond = link_cond & cond;
         }

      }

   }

   return link_cond;
}

void cdbQuery::makeQueryData()
{
   if ( qd == 0 )
      qd = new0 QUERY_DATA;
}

