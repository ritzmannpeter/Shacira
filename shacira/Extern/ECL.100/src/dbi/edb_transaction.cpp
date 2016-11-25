// ===========================================================================
// edb_transaction.cpp                          ETCL (ET's Tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdbTransaction      -
//
//    cdbTAObject             -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "dbi/edb_transaction.hpp"
#include "base/eb_thread.hpp"
#include "base/eb_msg.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_event.hpp"
#include "base/eb_sema.hpp"
#include "dbi/edb_database.hpp"

class cWorker;

#endif /*__INTERFACE__*/




// ===========================================================================
// Lokale Klasse cWorker
// ---------------------------------------------------------------------------
//
// Uebernimmt Arbeitsauftraege der Transaktion vom Typ cdbTAObject. Diese
// Klasse verwaltet ein fest zugeordnetes cdbDatabase-Objekt in einem eigenen
// Worker-Thread. Die Kommunikation mit diesem Thread wird ueber ein cMsgBox-
// Objekt abgewickelt.
//
// cBase
//  +--cWorker
//
// ===========================================================================

#define TIMEOUT 7500 /* msec */

class cWorker : public cThread, public cEventSource {

public:
   // Konstruktion ueber Datenbank-Anmeldeparameter
   cWorker(cdbTransaction *ta, cdbDatabase::DB_TYPE type, cString dsn, cString uid, cString pwd);
   // Konstruktion ueber anderes TA-Objekt (Copy-Konstruktor)
   cWorker(cdbTransaction *ta, const cdbTransaction& other);
   // Konstruktion ueber bestehendes Datenbankobjekt
   cWorker(cdbTransaction *ta, const cdbDatabase& db);
   // Destruktor
   ~cWorker();


   // Allgemeines
   // ===========

   cdbDatabase * getDB()
      { return db; }
   const cdbDatabase * getDB() const
      { return db; }


   // Msg-IDs fuer Replies
   // ====================

   enum REPLY_IDS {
      rmOk,                // Operation normal beendet
      rmError              // Fehler aufgetreten
   };


   // Transaktionskontrolle
   // =====================

   // Savepoint 'level' setzen
   void setSavepoint(int level, const cEventTarget::EVENT& event)
      { call(wmSetSavepoint, level, event, TIMEOUT); }
   // Transaktion speichern
   bool commit(const cEventTarget::EVENT& event)
      { return call(wmCommit, event, TIMEOUT).getMsgId() == rmOk; }
   // Rollback zum Savepoint 'level'
   bool rollbackTo(int level, const cEventTarget::EVENT& event)
      { return call(wmRollbackTo, level, event, TIMEOUT).getMsgId() == rmOk; }
   // COMMIT ausfuehren und auf Savepoint 'level' zurueck
   bool saveAll(int level, const cEventTarget::EVENT& event)
      { return call(wmSaveAll, level, event, TIMEOUT).getMsgId() == rmOk; }


   // Ausfuehren von Transaktionsobjekten
   // ===================================

   // Asynchrones Ausfuehren der Funktion 'func' des TA-Objektes 'ta_obj'
   void start(cdbTAObject *ta_obj, int func, const cEventTarget::EVENT& event)
      { send(wmStartObj, ta_obj, func, event); }
   // Synchrones Ausfuehren der Funktion 'func' des TA-Objektes 'ta_obj'
   cMsg call(cdbTAObject *ta_obj, int func, const cEventTarget::EVENT& event, int timeout = TIMEOUT)
      { return call(wmStartObj, ta_obj, func, event, timeout); }
   // Aktuelle Aktion anhalten und Eingangsqueue verwerfen
   void stop(const cEventTarget::EVENT& event, int timeout = TIMEOUT)
      { call(wmStop, event, timeout);
        stop_flag = true;
        abortCurrent(); }


   // Beenden des Worker-Threads
   // ==========================

   // Aktuelle Aktion anhalten, Eingangsqueue verwerfen und Thread beenden
   void exit(const cEventTarget::EVENT& event, int timeout = TIMEOUT)
      { call(wmStop, cEventTarget::EVENT(), timeout);
        call(wmExit, event, timeout);
        stop_flag = true;
        abortCurrent(); }


protected:

   // Thread-Events
   // =============

   // Parameter fuer onEnter()
   struct ENTER {
      ENTER() { type = cdbDatabase::DUMMY; other_db = 0; }
      cdbDatabase::DB_TYPE type;    // Typ der Datenbank
      cString dsn, uid, pwd;        // Anmeldeparameter (falls kein DB-Objekt)
      const cdbDatabase *other_db;  // Zeiger auf Template-DB-Objekt
   };

   // Wird aufgerufen, wenn der Thread gestartet wird
   bool onEnter(void *extra);
   // Wird aufgerufen, um die Hauptschleife des Threads auszufuehren
   int onMain(void *extra);
   // Wird aufgerufen, wenn der Thread beendet wird
   void onLeave(int rc);

private:
   cMsgBox msg_box;        // MessageBox zur Kommunikation mit Worker-Thread
   cdbDatabase *db;        // Datenbank (wird im Worker-Thread verwaltet)
   cdbTransaction *ta;     // Zugeordnetes cdbTransaction-Objekt
   cdbTAObject *cur_obj;   // Zeiger auf aktuelles cdbTAObject-Objekt
   bool stop_flag;         // Signalisiert den STOP-Wunsch

   enum MSG_IDS {
      wmSetSavepoint,      // SAVEPOINT 'value'
      wmCommit,            // COMMIT durchfuehren
      wmRollbackTo,        // ROLLBACK TO 'value'
      wmSaveAll,           // COMMIT; SAVEPOINT {0..'value')
      wmStartObj,          // Objekt asynchron ausfuehren
      wmStop,              // cur_obj anhalten und MsgBox leeren
      wmExit               // cur_obj anhalten, MsgBox leeren und Thread beenden
   };

   struct MSG_DATA {       // Datenstruktur in der Messagequeue
      MSG_DATA(cdbTAObject *obj, int value, const cEventTarget::EVENT& event)
         { MSG_DATA::obj = obj; MSG_DATA::value = value; MSG_DATA::event = event; }
      cdbTAObject *obj;          // Zeiger auf cdbTAObject-Objekt
      int value;                 // Zusaetzlicher int-Wert
      cEventTarget::EVENT event; // EVENT fuer Rueckmeldung
   };

   // Asynchrone Meldung (id, event)
   void send(MSG_IDS msg_id, const cEventTarget::EVENT& event)
      { MSG_DATA data(0, 0, event);
        sendMsg(cMsg(msg_id, sizeof(MSG_DATA), &data)); }
   // Asynchrone Meldung (id, value, event)
   void send(MSG_IDS msg_id, int value, const cEventTarget::EVENT& event)
      { MSG_DATA data(0, value, event);
        sendMsg(cMsg(msg_id, sizeof(MSG_DATA), &data)); }
   // Asynchrone Meldung (id, obj, value, event)
   void send(MSG_IDS msg_id, cdbTAObject *obj, int value, const cEventTarget::EVENT& event)
      { MSG_DATA data(obj, value, event);
        sendMsg(cMsg(msg_id, sizeof(MSG_DATA), &data)); }

   // Synchrone Meldung (id, event, timeout)
   cMsg call(MSG_IDS msg_id, const cEventTarget::EVENT& event, int timeout)
      { MSG_DATA data(0, 0, event);
        return callMsg(cMsg(msg_id, sizeof(MSG_DATA), &data), timeout); }
   // Synchrone Meldung (id, value, event, timeout)
   cMsg call(MSG_IDS msg_id, int value, const cEventTarget::EVENT& event, int timeout)
      { MSG_DATA data(0, value, event);
        return callMsg(cMsg(msg_id, sizeof(MSG_DATA), &data), timeout); }
   // Synchrone Meldung (id, obj, value, event, timeout)
   cMsg call(MSG_IDS msg_id, cdbTAObject *obj, int value, const cEventTarget::EVENT& event, int timeout)
      { MSG_DATA data(obj, value, event);
        return callMsg(cMsg(msg_id, sizeof(MSG_DATA), &data), timeout); }


   // Hilfsfunktionen
   // ===============

   // Asynchrone Meldung senden
   void sendMsg(const cMsg& msg);
   // Synchrone Meldung senden
   cMsg callMsg(const cMsg& msg, int timeout);

   // Ausfuehrung der aktuellen Aktion unterbrechen
   void abortCurrent();
   // Eingangsqueue verwerfen, bis einschliesslich wmStop-Meldung
   cMsg clearQueueTilStop();

   // Pruefen, ob der Aufrufer im aktuellen cWorker-Thread laeuft
   bool isCallerInSameThread() const;


   // Worker-Funktionen
   // =================

   cMsg doDispatchMsg(cMsg msg);

   void doSetSavepoint(int level);
   void doCommit();
   void doRollbackTo(int level);
   void doSaveAll(int level);
   void doStartObj(cdbTAObject *obj, int func);
   void doStop();
   void doExit();

};

// Implementierung cWorker
// ===========================================================================

#define THREAD_STACK_SIZE  32768
#define MSG_BOX_ENTRIES    32

// Anmerkung: Die Konstruktoren kehren erst dann zum Aufrufer zurueck,
// wenn der Worker-Thread gestartet und das cdbDatabase-Objekt konstruiert ist.

cWorker::cWorker(cdbTransaction *ta, cdbDatabase::DB_TYPE type, cString dsn, cString uid, cString pwd) :
   cThread(THREAD_STACK_SIZE),
   msg_box(MSG_BOX_ENTRIES, sizeof(MSG_DATA))
{
   cWorker::ta = ta;
   cWorker::db = 0;
   cWorker::cur_obj = 0;
   cWorker::stop_flag = false;

   ENTER enter; enter.type = type;
   enter.dsn = dsn; enter.uid = uid; enter.pwd = pwd;
   cThread::start(&enter, teStart);
}

cWorker::cWorker(cdbTransaction *ta, const cdbTransaction& other) :
   cThread(THREAD_STACK_SIZE),
   msg_box(MSG_BOX_ENTRIES, sizeof(MSG_DATA))
{
   cWorker::ta = ta;
   cWorker::db = 0;
   cWorker::cur_obj = 0;
   cWorker::stop_flag = false;

   ENTER enter; enter.other_db = other.getDB();
   cThread::start(&enter, teStart);
}

cWorker::cWorker(cdbTransaction *ta, const cdbDatabase& db) :
   cThread(THREAD_STACK_SIZE),
   msg_box(MSG_BOX_ENTRIES, sizeof(MSG_DATA))
{
   cWorker::ta = ta;
   cWorker::db = 0;
   cWorker::cur_obj = 0;
   cWorker::stop_flag = false;

   ENTER enter; enter.other_db = &db;
   cThread::start(&enter, teStart);
}

cWorker::~cWorker()
{
#ifdef __Das_Macht_ja_ganz_schoen_Probleme___
   if ( db != 0 ) // Sicherheitshalber...
      delete db; // (falls onLeave() nicht aufgerufen wurde)
#endif
}


// Thread-Events
// =============

bool cWorker::onEnter(void *extra)
{
   DbgTrcWin("TA: Worker: thread started");

   // Prioritaet etwas erhoehen gegenueber Normal
   setPriority(plAboveNormal);

   bool rc = true;
   ENTER *enter = (ENTER *)extra;

   try {
      if ( enter->other_db != 0 ) {
         db = new0 cdbDatabase(*enter->other_db);
      } else {
         db = new0 cdbDatabase(enter->type, enter->dsn, enter->uid, enter->pwd);
      }
   } catch ( const cErrBase& err ) {
      char msg[1024]; err.getString(msg, sizeof msg);
      DbgError("Could not create database for cdbTransaction, cause:");
      DbgError("%s", msg);
      rc = false;
   }

   return rc;
}

int cWorker::onMain(void * /*extra*/)
{
   DbgTrcWin("TA: Worker: entering main loop");
   cMsg msg;

   do {

      if ( stop_flag ) {
         msg = clearQueueTilStop();
         stop_flag = false;
      } else {
         msg = msg_box.receive();
      }

      cMsg reply_msg = doDispatchMsg(msg);

      if ( msg_box.mustReply(msg) )
         msg_box.reply(msg, reply_msg);

   } while ( msg.getMsgId() != wmExit );

   DbgTrcWin("TA: Worker: leaving main loop");
   return 0;
}

void cWorker::onLeave(int /*rc*/)
{
   delete db;
   db = 0;

   DbgTrcWin("TA: Worker: thread terminated");
}


// Hilfsfunktionen
// ===============

void cWorker::sendMsg(const cMsg& msg)
{
   if ( isCallerInSameThread() ) {
      DbgOut(0, ">>>> SEND: CALLER IN SAME THREAD <<<<");
      doDispatchMsg(msg);
   } else {
      msg_box.send(msg);
   }
}

cMsg cWorker::callMsg(const cMsg& msg, int timeout)
{
   if ( isCallerInSameThread() ) {
      DbgOut(0, ">>>> CALL: CALLER IN SAME THREAD <<<<");
      return doDispatchMsg(msg);
   } else {
      return msg_box.call(msg, timeout);
   }
}

void cWorker::abortCurrent()
{
   if ( cur_obj != 0 ) {
      cur_obj->onStopAction();
   }
}

cMsg cWorker::clearQueueTilStop()
{
   bool saved_wait_flag = msg_box.getWait();
   msg_box.setWait(false);
   cMsg msg;

   do {
      msg = msg_box.receive();
   } while ( !msg.isEmpty() && msg.getMsgId() != wmStop );

   msg_box.setWait(saved_wait_flag);
   return msg;
}

bool cWorker::isCallerInSameThread() const
{
   return getThreadId() == cThread::getCurrentThreadId();
}


// Worker-Funktionen
// =================

cMsg cWorker::doDispatchMsg(cMsg msg)
{
   cMsg reply_msg = cMsg(rmOk);
   MSG_DATA *md = (MSG_DATA *)msg.getData();

   try {

      switch ( msg.getMsgId() ) {
      case wmSetSavepoint: doSetSavepoint(md->value); break;
      case wmCommit:       doCommit(); break;
      case wmRollbackTo:   doRollbackTo(md->value); break;
      case wmSaveAll:      doSaveAll(md->value); break;
      case wmStartObj:     doStartObj(md->obj, md->value); break;
      case wmStop:         doStop(); break;
      case wmExit:         doExit(); break;
      }

      // Operation ohne Fehler abgeschlossen
      cErrBase no_error(cErrBase::errNoError);
      callEvent(md->event, (void *)&no_error);

   } catch ( const cErrBase& err ) {

      char msg[1024]; err.getString(msg, sizeof msg);
      DbgError("Error in worker thread of cdbTransaction, cause:");
      DbgError("%s", msg);

      // Operation mit Fehler abgeschlossen
      callEvent(md->event, (void *)&err);
      reply_msg = cMsg(rmError);

   }

   return reply_msg;
}

void cWorker::doSetSavepoint(int level)
{
   db->setSavepoint(level); // Fehlerbehandlung in onMain
}

void cWorker::doCommit()
{
   db->commit(); // Fehlerbehandlung in onMain
}

void cWorker::doRollbackTo(int level)
{
   db->rollback(level); // Fehlerbehandlung in onMain
}

void cWorker::doSaveAll(int level)
{
   db->commit();
   for ( int sp = 0 ; sp < level ; sp++ )
      db->setSavepoint(sp);
}

void cWorker::doStartObj(cdbTAObject *obj, int func)
{
   obj->onExecAction(db, func);
}

void cWorker::doStop()
{
}

void cWorker::doExit()
{
}




#ifdef __INTERFACE__

// ===========================================================================
// cdbTAObject
// ---------------------------------------------------------------------------
//
// cdbTAObject
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbTAObject {
   friend class cdbTransaction;
   friend class cWorker;

public:

   // Allgemeines
   // ===========

   // Zeiger auf zugehoerige cdbTransaction ermitteln
   cdbTransaction *getTA()
      { return ta; }
   // const-Zeiger auf zugehoerige cdbTransaction ermitteln
   const cdbTransaction *getTA() const
      { return ta; }

   // Zeiger auf zugehoerige cdbDatabase ermitteln
   cdbDatabase * getDB();
   // const-Zeiger auf zugehoerige cdbDatabase ermitteln
   const cdbDatabase * getDB() const;


protected:

   // Konstruktor
   // ===========

   // Konstruktor (nur protected), da virtuelle Basisklasse
   cdbTAObject(cdbTransaction *ta);
   // Konstruktor (nur protected), da virtuelle Basisklasse
   cdbTAObject(cdbTransaction& ta);
   // Konstruktor (nur protected), da virtuelle Basisklasse
   cdbTAObject(const cdbTAObject& other);


   // Ausfuehrungskontrolle
   // =====================

   // Asynchrones Starten von Funktion 'func' der Aktion
   void startAction(int func, const cEventTarget::EVENT& event = cEventTarget::EVENT());
   // Synchrones Starten von Funktion 'func' der Aktion
   bool callAction(int func, const cEventTarget::EVENT& event = cEventTarget::EVENT());


   // Events
   // ======

   // Wird aufgerufen, um die Aktion 'func' auszufuehren
   virtual void onExecAction(cdbDatabase *db, int func) = 0;
   // Wird aufgerufen, um den Abbruch der aktuellen Aktion anzufordern
   virtual void onStopAction() = 0;
   // Wird aufgerufen, um eine textuelle Signatur der Aktion zu ermitteln
   virtual cString onGetSignature() = 0;


private:
   cdbTransaction *ta;

};

#endif /*__INTERFACE__*/


// Implementierung cdbTAObject
// ===========================================================================

cdbTAObject::cdbTAObject(cdbTransaction *ta)
{
   __ECL_ASSERT1__(ta != 0);
   cdbTAObject::ta = ta;
}

cdbTAObject::cdbTAObject(cdbTransaction& ta)
{
   cdbTAObject::ta = &ta;
}

cdbTAObject::cdbTAObject(const cdbTAObject& other)
{
   __ECL_ASSERT1__(other.ta != 0);
   cdbTAObject::ta = other.ta;
}


// Allgemeines
// ===========

cdbDatabase * cdbTAObject::getDB()
{
   return ta->getDB();
}

const cdbDatabase * cdbTAObject::getDB() const
{
   return ta->getDB();
}


// Ausfuehrungskontrolle
// =====================

void cdbTAObject::startAction(int func, const cEventTarget::EVENT& event)
{
   ta->startAction(this, func, event);
}

bool cdbTAObject::callAction(int func, const cEventTarget::EVENT& event)
{
   return ta->callAction(this, func, event);
}




#ifdef __INTERFACE__

// ===========================================================================
// cdbTransaction
// ---------------------------------------------------------------------------
//
// Ein Objekt der cdbTransaction-Klasse kann als eine Art erweitertes,
// asynchron ablaufendes cdbDatabase-Objekt verstanden werden. Dem
// cdbTransaction-Objekt koennen Meldungen der Form "Fuehre Query aus" oder
// "Bearbeite Datensatz" geschickt werden, die ueber das tatsaechlich in
// einem zweiten (secondary) Thread liegende cdbDatabase-Objekt bearbeitet
// werden.
//
// Das Ende jeder Operation kann durch einen Event signalisiert werden. Dabei
// wird als Parameter der Zeiger auf ein temporaeres Fehlerobjekt uebergeben
// (im Normalfall wird dieses Objekt mit errNoError konstruiert). Der Prototyp
// der Event-Funktion ist:
//
//    void (cEventTarget::*EVFUNC_P)(void *err);
//
// cBase
//  +--cdbTransaction
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbTransaction : public cBase, public cEventSource {
   friend class cdbTAObject;

public:

   // Konstruktion ueber Datenbank-Anmeldeparameter
   cdbTransaction(cdbDatabase::DB_TYPE type, cString dsn, cString uid, cString pwd);
   // Konstruktion ueber anderes TA-Objekt (Copy-Konstruktor)
   cdbTransaction(const cdbTransaction& other);
   // Konstruktion ueber bestehendes Datenbankobjekt
   cdbTransaction(const cdbDatabase& db);
   // Destruktor
   virtual ~cdbTransaction();


   // Allgemeines
   // ===========

   // Prueft, ob aktive Datenbank-Verbindung vorhanden
   bool isConnected() const;
   // Liefert einen Zeiger auf die benutzte Datenbank
   cdbDatabase *getDB();
   // Liefert einen const-Zeiger auf die benutzte Datenbank
   const cdbDatabase *getDB() const;
   // Transaktionsebene (Anzahl aktiver Begin-/End-Paare)
   int getLevel() const
      { return ta_level; }


   // Transaktionskontrolle
   // =====================
   // Jede Transaktion muss mit einem Begin/End-Paar geklammert werden. Normaler-
   // weise wird durch die End-Methode ein COMMIT ausgefuehrt, dieses Verhalten
   // kann jedoch durch den Parameter teRollback in ein ROLLBACK geaendert werden.
   // Bei geschachtelten Transaktionen wird kein COMMIT bzw. ein ROLLBACK TO
   // SAVEPOINT ausgefuehrt. Die Terminate-Eventfunktion erhaelt im ersten Parameter
   // ein OK-Flag (BOOL), bei COMMIT bzw. ROLLBACK zusaetzlich im zweiten Parameter
   // die Nummer des Savepoints.

   enum TBEGIN {        // Modi fuer begin():
      tbReadWrite,      //  - Normale Schreib-/Lese-Transaktion
      tbReadOnly,       //  - Transaktion ohne Schreibzugriffe (nicht implementiert)
      tbShort           //  - Besonders kurze Transaktion (nicht implementiert)
   };

   enum TEND {          // Modi fuer end():
      teCommit,         //  - Speichern, falls letzte geschachtelte Transaktion
      teRollback,       //  - Verwerfen bis zum vorigen Begin() der gesch. TA
      teIgnore          //  - Optimierung: TA ohne Commit oder Rollback beenden
   };

   // Markiert den Beginn einer Transaktion
   void begin(TBEGIN tb = tbReadWrite, const EVENT& event = EVENT());
   // Markiert das Ende einer Transaktion
   void end(TEND te = teCommit, const EVENT& event = EVENT());


   // Daten sichern
   // -------------
   // In manchen Faellen kann es sinnvoll sein, geaenderte Daten bereits vor dem
   // eigentlichen Transaktionsende zu sichern. Die Save-Methode fuehrt unabhaengig
   // von der aktuellen Begin-/End-Verschachtelung ein COMMIT aus und fuehrt an-
   // schliessend wieder soviele SAVEPOINTs aus wie noetig.

   // Bisherige Aenderungen speichern
   void saveAll(const EVENT& event = EVENT());


protected:

   // Ausfuehrungskontrolle
   // =====================

   // Asynchrones Starten einer Aktion
   void startAction(cdbTAObject *ta_obj, int func, const EVENT& event);
   // Synchrones Starten einer Aktion
   bool callAction(cdbTAObject *ta_obj, int func, const EVENT& event);


private:

   cWorker *worker;        // Zeiger auf ausfuehrendes Thread-Objekt
   int ta_level;           // Aktueller Transaktionslevel

};

#endif /*__INTERFACE__*/


// Implementierung cdbTransaction
// ===========================================================================

cdbTransaction::cdbTransaction(cdbDatabase::DB_TYPE type, cString dsn, cString uid, cString pwd)
{
   DbgTrcDb("TA: creating transaction object");

   ta_level = 0;
   worker = new0 cWorker(this, type, dsn, uid, pwd);
}

cdbTransaction::cdbTransaction(const cdbTransaction& other)
{
   DbgTrcDb("TA: creating transaction object");

   ta_level = 0;
   worker = new0 cWorker(this, other);
}

cdbTransaction::cdbTransaction(const cdbDatabase& db)
{
   DbgTrcDb("TA: creating transaction object");

   ta_level = 0;
   worker = new0 cWorker(this, db);
}

cdbTransaction::~cdbTransaction()
{
   worker->exit(EVENT());
   worker->waitFor(cThread::teEnd);
   delete worker;

   DbgTrcDb("TA: deleting transaction object");
}


// Allgemeines
// ===========

bool cdbTransaction::isConnected() const
{
   cdbDatabase *db = worker->getDB();
   return db != 0 ? db->isConnected() : false;
}

cdbDatabase * cdbTransaction::getDB()
{
   return worker->getDB();
}

const cdbDatabase * cdbTransaction::getDB() const
{
   return worker->getDB();
}


// Transaktionskontrolle
// =====================

void cdbTransaction::begin(TBEGIN tb, const EVENT& event)
{
   static const char *tb_str[] = { "ReadWrite", "ReadOnly", "Short" };
   DbgTrcDb("TA: begin(%s)", tb_str[tb]);
   worker->setSavepoint(ta_level++, event);
}

void cdbTransaction::end(TEND te, const EVENT& event)
{
   static const char *te_str[] = { "Commit", "Rollback", "Ignore" };
   DbgTrcWin("TA: end(%s)", te_str[te]);
   cErrBase no_error(cErrBase::errNoError);

   switch ( te ) {

    case teCommit:
      if ( --ta_level == 0 ) {
         if ( !worker->commit(event) ) {
            // TBD: Fehlerbehandlung...
         }
      } else {
         callEvent(event, (void *)&no_error);
      }
      break;

    case teRollback:
      if ( --ta_level >= 0 ) {
         if ( !worker->rollbackTo(ta_level, event) ) {
            // TBD: Fehlerbehandlung...
         }
      } else {
         callEvent(event, (void *)&no_error);
      }
      break;

    case teIgnore:
      if ( ta_level > 0 )
         ta_level--;
      callEvent(event, (void *)&no_error);
      break;

   }

   if ( ta_level < 0 )
      ta_level = 0;
}

void cdbTransaction::saveAll(const EVENT& event)
{
   DbgTrcWin("TA: saveAll()");
   if ( !worker->saveAll(ta_level, event) ) {
      // TBD: Fehlerbehandlung...
   }
}


// Ausfuehrungskontrolle
// =====================

void cdbTransaction::startAction(cdbTAObject *ta_obj, int func, const EVENT& event)
{
   DbgTrcWin("TA: start(%s)", (const char *)ta_obj->onGetSignature());
   worker->start(ta_obj, func, event);
}

bool cdbTransaction::callAction(cdbTAObject *ta_obj, int func, const EVENT& event)
{
   DbgTrcWin("TA: call(%s)", (const char *)ta_obj->onGetSignature());
   return worker->call(ta_obj, func, event).getMsgId() == cWorker::rmOk;
}

