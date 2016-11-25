// ===========================================================================
// edb_record.cpp                               ETCL (ET's Tiny Class Library)
// ---------------------------------------------------------------------------
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdbRecord                -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "dbi/edb_record.hpp"

#if defined __ECL_OS2__
   #define INCL_DOSDATETIME
   #define INCL_DOSPROCESS
   #define INCL_WINPOINTERS
   #include <os2.h>
#elif defined __ECL_W16__ || defined __ECL_W32__
   #include <windows.h>
#endif

#if defined __OCI__
   #include "ociapr.h"
   #define ORASHIT NULL
#endif
#if defined __BTI__
   #include "btrievew.h"
#endif
#if defined __ODBC__
   //#define ODBCVER 0x0250
   #include "sql.h"
   #include "sqlext.h"
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "dbi/edb_database.hpp"

#endif /*__INTERFACE__*/




// Lokale Daten
// ===========================================================================

static const char *OpenModeString[] = {
   "r/w", "r/o"
};

static const char *ActionString[] = {
   "first", "last", "next", "prev", "direct", "pos",
   "equal", "gt", "ge", "lt", "le"
};




// ===========================================================================
// Lokale Klasse cRecBase
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRecBase
//
// ===========================================================================

class cRecBase : public cBase {

public:
   cRecBase(cdbRecord& rec);
   virtual ~cRecBase();

   bool open(cdbDatabase& db, cString name, cdbRecord::OPEN_MODE mode, int rec_len);
   bool close();

   bool insert(int idx, void *key, const void *data, bool lock);
   bool update(int idx, void *key, const void *data, bool lock);
   bool remove(int idx, void *key, const void *data, bool lock);

   bool step(cdbRecord::ACTION action, void *data, bool lock);
   bool get(cdbRecord::ACTION action, int idx, void *key, void *data, bool lock);

   bool unlock(int idx, const void *data);

   virtual cString getLastErrorMsg() const = 0;

protected:
   cdbDatabase *db;
   cdbRecord *rec;
   int rec_len;

   virtual bool onOpen(cString name, cdbRecord::OPEN_MODE mode) = 0;
   virtual bool onClose() = 0;

   virtual bool onInsert(int idx, void *key, const void *data, bool lock) = 0;
   virtual bool onUpdate(int idx, void *key, const void *data, bool lock) = 0;
   virtual bool onRemove(int idx, void *key, const void *data, bool lock) = 0;

   virtual bool onStep(cdbRecord::ACTION action, void *data, bool lock) = 0;
   virtual bool onGet(cdbRecord::ACTION action, int idx, void *key, void *data, bool lock) = 0;

   virtual bool onUnlock(int idx, const void *data) = 0;

private:
   static int open_recs;
   static int max_open_recs;

};


// Implementierung cRecBase
// ===========================================================================

int cRecBase::open_recs = 0;
int cRecBase::max_open_recs = 0;

cRecBase::cRecBase(cdbRecord& _rec)
{
   rec = &_rec;
   db = NULL;
   rec_len = 0;
}

cRecBase::~cRecBase()
{
   // ...
}

bool cRecBase::open(cdbDatabase& db, cString name, cdbRecord::OPEN_MODE mode, int rec_len)
{
   cRecBase::db = &db;
   cRecBase::rec_len = rec_len;

   if ( ++open_recs > max_open_recs )
      max_open_recs = open_recs;

   return onOpen(name, mode);
}

bool cRecBase::close()
{
   if ( onClose() ) {
      --open_recs;
      return true;
   }

   return false;
}

bool cRecBase::insert(int idx, void *key, const void *data, bool lock)
{
   return onInsert(idx, key, data, lock);
}

bool cRecBase::update(int idx, void *key, const void *data, bool lock)
{
   return onUpdate(idx, key, data, lock);
}

bool cRecBase::remove(int idx, void *key, const void *data, bool lock)
{
   return onRemove(idx, key, data, lock);
}

bool cRecBase::step(cdbRecord::ACTION action, void *data, bool lock)
{
   return onStep(action, data, lock);
}

bool cRecBase::get(cdbRecord::ACTION action, int idx, void *key, void *data, bool lock)
{
   return onGet(action, idx, key, data, lock);
}

bool cRecBase::unlock(int idx, const void *data)
{
   return onUnlock(idx, data);
}




#if defined(__DUMMY__)

// ===========================================================================
// Definition cRecDummy
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRecBase
//      +--cRecDummy
//
// ===========================================================================

class cRecDummy : public cRecBase {

public:
   cRecDummy(cdbRecord& _cu);
  ~cRecDummy();

   cString getLastErrorMsg() const;

protected:
   bool onOpen(cString name, cdbRecord::OPEN_MODE _mode);
   bool onClose();

   bool onInsert(int idx, void *key, const void *data, bool lock);
   bool onUpdate(int idx, void *key, const void *data, bool lock);
   bool onRemove(int idx, void *key, const void *data, bool lock);

   bool onStep(cdbRecord::ACTION action, void *data, bool lock);
   bool onGet(cdbRecord::ACTION action, int idx, void *key, void *data, bool lock);

   bool onUnlock(int idx, const void *data);

private:
   cString db_file;

};


// Implementierung cRecDummy
// ===========================================================================

cRecDummy::cRecDummy(cdbRecord& _rec) :
   cRecBase(_rec)
{
}

cRecDummy::~cRecDummy()
{
}

bool cRecDummy::onOpen(cString name, cdbRecord::OPEN_MODE mode)
{
   db_file = name;
   DbgDb("Dummy: Open table '%s' %s (rec_len=%d)", Nvl(db_file, "<EMPTY>"), OpenModeString[mode], rec_len);
   return true;
}

bool cRecDummy::onClose()
{
   DbgDb("Dummy: Close table '%s'", Nvl(db_file, "<EMPTY>"));
   return true;
}

bool cRecDummy::onInsert(int idx, void * /*key*/, const void * /*data*/, bool /*lock*/)
{
   DbgDb("Dummy: Insert into table '%s' (idx=%d)", Nvl(db_file, "<EMPTY>"), idx);
   return true;
}

bool cRecDummy::onUpdate(int idx, void * /*key*/, const void * /*data*/, bool /*lock*/)
{
   DbgDb("Dummy: Update table '%s' (idx=%d)", Nvl(db_file, "<EMPTY>"), idx);
   return true;
}

bool cRecDummy::onRemove(int idx, void * /*key*/, const void * /*data*/, bool /*lock*/)
{
   DbgDb("Dummy: Delete from table '%s' (idx=%d)", Nvl(db_file, "<EMPTY>"), idx);
   return true;
}

bool cRecDummy::onStep(cdbRecord::ACTION action, void * /*data*/, bool /*lock*/)
{
   DbgDb("Dummy: Step %s in table '%s'", ActionString[action], Nvl(db_file, "<EMPTY>"));
   return false;
}

bool cRecDummy::onGet(cdbRecord::ACTION action, int idx, void * /*key*/, void * /*data*/, bool /*lock*/)
{
   DbgDb("Dummy: Get %s from table '%s' (idx=%d)", ActionString[action], Nvl(db_file, "<EMPTY>"), idx);
   return false;
}

bool cRecDummy::onUnlock(int idx, const void * /*data*/)
{
   DbgDb("Dummy: Unlock in table '%s' (idx=%d)", Nvl(db_file, "<EMPTY>"), idx);
   return true;
}

cString cRecDummy::getLastErrorMsg() const
{
   return "no error";
}

#endif /*__DUMMY__*/




#if defined(__BTI__)

// ===========================================================================
// Definition cRecBTI
// ---------------------------------------------------------------------------
//
// cBase
//  +--cRecBase
//      +--cRecBTI
//
// ===========================================================================

class cRecBTI : public cRecBase {

public:
   cRecBTI(cdbRecord& _cu);
  ~cRecBTI();

   cString getLastErrorMsg() const;

protected:
   bool onOpen(cString name, cdbRecord::OPEN_MODE _mode);
   bool onClose();

   bool onInsert(int idx, void *key, const void *data, bool lock);
   bool onUpdate(int idx, void *key, const void *data, bool lock);
   bool onRemove(int idx, void *key, const void *data, bool lock);

   bool onStep(cdbRecord::ACTION action, void *data, bool lock);
   bool onGet(cdbRecord::ACTION action, int idx, void *key, void *data, bool lock);

   bool onUnlock(int idx, const void *data);

private:
   int status;
   HANDLE hbtr;
   cString db_file;

   enum DO_CMD { doNone, doClose, doInsert, doUpdate, doDelete, doStep, doGet, doUnlock };
   DO_CMD last_cmd;

   void DebugOutput(int idx, const void *data, cdbRecord::ACTION action);

};


// Implementierung cRecBTI
// ===========================================================================

cRecBTI::cRecBTI(cdbRecord& _rec) :
   cRecBase(_rec)
{
   status = 0;
   last_cmd = doNone;
   hbtr = NULL;
}

cRecBTI::~cRecBTI()
{
   // ...
}

bool cRecBTI::onOpen(cString name, cdbRecord::OPEN_MODE mode)
{
   char *db_path = (char *)db->getDriverInfo(1);
   char *db_ext = (char *)db->getDriverInfo(2);

   if ( name.getPos(".") < 0 ) {
      db_file = name + "." + (const char *)db_ext;
   } else {
      db_file += name;
   }

   switch ( mode ) {
    case cdbRecord::RO:
      hbtr = b_open_read_only(db_path, (char *)(const char *)db_file, &status, rec_len);
      break;
    case cdbRecord::RW:
      hbtr = b_open(db_path, (char *)(const char *)db_file, &status, rec_len);
      break;
   }

   DbgDb("Btrieve: Opening table '%s' %s (rec_len=%d): Status = %d",
      Nvl(db_file, "<EMPTY>"), OpenModeString[mode], rec_len, status);

   if ( status )
      DbgError("Btrieve: Opening table '%s' %s failed: Status = %d",
         Nvl(db_file, "<EMPTY>"), OpenModeString[mode], status);

   return !status;
}

bool cRecBTI::onClose()
{
   last_cmd = doClose;
   status = b_close(hbtr);
   DebugOutput(0, NULL, cdbRecord::equal);
   if ( status ) throw cdbErr(cdbErr::errGeneralDbError, *rec);
   return !status;
}

bool cRecBTI::onInsert(int idx, void *key, const void *data, bool lock)
{
   last_cmd = doInsert;
   status = b_insert(hbtr, idx, (LPSTR)key, (void FAR *)data, lock);
   DebugOutput(idx, data, cdbRecord::equal);
   if ( status ) {
      if ( status == 84 ) // The Record is Locked
         throw cdbErr(cdbErr::errResourceBusy, *rec);
      throw cdbErr(cdbErr::errGeneralDbError, *rec);
   }
   return !status;
}

bool cRecBTI::onUpdate(int idx, void *key, const void *data, bool lock)
{
   last_cmd = doUpdate;
   status = b_update(hbtr, idx, (LPSTR)key, (void FAR *)data, lock);
   DebugOutput(idx, data, cdbRecord::equal);
   if ( status ) {
      if ( status == 80 ) // The Record has been changed
         throw cdbErr(cdbErr::errAccessViolation, *rec);
      if ( status == 84 ) // The Record is Locked
         throw cdbErr(cdbErr::errResourceBusy, *rec);
      throw cdbErr(cdbErr::errGeneralDbError, *rec);
   }
   return !status;
}

bool cRecBTI::onRemove(int idx, void *key, const void *data, bool lock)
{
   last_cmd = doDelete;
   status = b_delete(hbtr, idx, (LPSTR)key, (void FAR *)data, lock);
   DebugOutput(idx, data, cdbRecord::equal);
   if ( status ) {
      if ( status == 80 ) // The Record has been changed
         throw cdbErr(cdbErr::errAccessViolation, *rec);
      if ( status == 84 ) // The Record is Locked
         throw cdbErr(cdbErr::errResourceBusy, *rec);
      throw cdbErr(cdbErr::errGeneralDbError, *rec);
   }
   return !status;
}

bool cRecBTI::onStep(cdbRecord::ACTION action, void *data, bool lock)
{
   last_cmd = doStep;

   switch ( action ) {
    case cdbRecord::first:   status = b_stepFirst(hbtr, 0, NULL, (void FAR *)data, lock); break;
    case cdbRecord::last:    status = b_stepLast(hbtr, 0, NULL, (void FAR *)data, lock); break;
    case cdbRecord::next:    status = b_stepNext(hbtr, 0, NULL, (void FAR *)data, lock); break;
    case cdbRecord::prev:    status = b_stepPrev(hbtr, 0, NULL, (void FAR *)data, lock); break;
    default:               throw cErrBase(cErrBase::errInvParam);
   }

   DebugOutput(-1, data, action);

   if ( status ) {
      if ( status != 9 /*EOF*/ )
         throw cdbErr(cdbErr::errGeneralDbError, *rec);
      return false;
   }

   return true;
}

bool cRecBTI::onGet(cdbRecord::ACTION action, int idx, void *key, void *data, bool lock)
{
   last_cmd = doGet;

   switch ( action ) {
    case cdbRecord::first:   status = b_getFirst(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::last:    status = b_getLast(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::next:    status = b_getNext(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::prev:    status = b_getPrev(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::direct:  status = b_getDirect(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::pos:     status = b_getPosition(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::equal:   status = b_getEqual(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::gt:      status = b_getGreater(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::ge:      status = b_getGreaterEqual(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::lt:      status = b_getLess(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    case cdbRecord::le:      status = b_getLessEqual(hbtr, idx, (LPSTR)key, (void FAR *)data, lock); break;
    default:               throw cErrBase(cErrBase::errInvParam);
   }

   DebugOutput(idx, data, action);

   if ( status ) {
      if ( status != 9 /*EOF*/
        && status != 4 /*KEY_NOT_FOUND*/
        && status != 82 /*LOST_POSITION*/ )
         throw cdbErr(cdbErr::errGeneralDbError, *rec);
      return false;
   }

   return true;
}

bool cRecBTI::onUnlock(int idx, const void *data)
{
   last_cmd = doUnlock;
   status = b_unlock(hbtr, idx, NULL, (void FAR *)data, false);
   DebugOutput(idx, data, cdbRecord::equal);
   if ( status ) throw cdbErr(cdbErr::errGeneralDbError, *rec);
   return !status;
}

static const char *DoCmdStr[] = {
   "<?>", "Close", "Insert", "Update",
   "Delete", "Step", "Get", "Unlock"
};

cString cRecBTI::getLastErrorMsg() const
{
   return cStringf("Btrieve-Fehler %d bei '%s'-Operation auf '%s'",
      status, DoCmdStr[last_cmd], db_file);
}

void cRecBTI::DebugOutput(int idx, const void *data, cdbRecord::ACTION action)
{
   if ( getDebugMask() & dbgDb ) {

      char buf[40] = "";
      int buf_len = rec_len > sizeof buf - 1 ? sizeof buf - 1 : rec_len;

      if ( data ) {
         memcpy(buf, data, buf_len);
         for ( int i = 0 ; i < buf_len ; i++ )
            if ( buf[i] < ' ' || buf[i] > 127 )
               buf[i] = '.';
         buf[buf_len] = '\0';
      }

      const char *cmd = "-?-", *subcmd = "";
      static const char *actions[] = {
         "Fst", "Lst", "Nxt", "Prv", "Dir", "Pos",
         "Equ", "GTh", "GEq", "LTh", "LEq"
      };

      switch ( last_cmd ) {
       case doClose:
       case doInsert:
       case doUpdate:
       case doDelete:
       case doUnlock:   cmd = DoCmdStr[last_cmd]; break;
       case doStep:     cmd = "Stp"; subcmd = actions[action]; break;
       case doGet:      cmd = "Get"; subcmd = actions[action]; break;
      }

      DbgDb("Btrieve: %s(%d): %s%s=%d %s", Nvl(db_file, "<EMPTY>"), idx, cmd, subcmd, status, buf);

   }
}

#endif /*__BTI__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbRecord
// ---------------------------------------------------------------------------
//
// cBase
//  +--cdbRecord
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbRecord : public cBase {
   friend class cdbErr;

public:
   enum OPEN_MODE { RW, RO };
   enum ACTION { first, last, next, prev, direct, pos, equal, gt, ge, lt, le };

   cdbRecord(cdbDatabase& db, cString name, OPEN_MODE mode, int rec_len);
  ~cdbRecord();

   bool insert(int idx, void *key, const void *data, bool lock = false);
   bool update(int idx, void *key, const void *data, bool lock = false);
   bool remove(int idx, void *key, const void *data, bool lock = false);

   bool step(ACTION action, void *data, bool lock = false);
   bool get(ACTION action, int idx, void *key, void *data, bool lock = false);

   bool unlock(int idx, const void *data);
   cString getLastErrorMsg() const;

private:
   void *rec_base;

};

#endif /*__INTERFACE__*/


// Implementierung cdbRecord
// ===========================================================================

cdbRecord::cdbRecord(cdbDatabase& db, cString name, OPEN_MODE mode, int rec_len)
{
   cRecBase *base = NULL;
   rec_base = NULL;

   switch ( db.getType() ) {
      #if defined(__DUMMY__)
         case cdbDatabase::DUMMY: base = new0 cRecDummy(*this); break;
      #endif
      #if defined(__OCI__)
         case cdbDatabase::OCI:   /* not supported */ break;
      #endif
      #if defined(__BTI__)
         case cdbDatabase::BTI:   base = new0 cRecBTI(*this); break;
      #endif
      #if defined(__ODBC__)
         case cdbDatabase::ODBC:  /* not supported */ break;
      #endif
   }

   if ( !base )
      throw cdbErr(cdbErr::errDbTypeNotSupported);

   if ( !base->open(db, name, mode, rec_len) )
      throw cdbErr(cdbErr::errOpenTableFailed);

   rec_base = base;
}

cdbRecord::~cdbRecord()
{
   cRecBase *base = (cRecBase *)rec_base;
   if ( base ) base->close();
   delete base;
}

bool cdbRecord::insert(int idx, void *key, const void *data, bool lock)
{
   DbgTrcDb("Record: insert(%d, %08lx, %08lx, %d)", idx, key, data, lock);
   cRecBase *base = (cRecBase *)rec_base;
   return base ? base->insert(idx, key, data, lock) : false;
}

bool cdbRecord::update(int idx, void *key, const void *data, bool lock)
{
   DbgTrcDb("Record: update(%d, %08lx, %08lx, %d)", idx, key, data, lock);
   cRecBase *base = (cRecBase *)rec_base;
   return base ? base->update(idx, key, data, lock) : false;
}

bool cdbRecord::remove(int idx, void *key, const void *data, bool lock)
{
   DbgTrcDb("Record: remove(%d, %08lx, %08lx, %d)", idx, key, data, lock);
   cRecBase *base = (cRecBase *)rec_base;
   return base ? base->remove(idx, key, data, lock) : false;
}

bool cdbRecord::step(ACTION action, void *data, bool lock)
{
   DbgTrcDb("Record: step(%s, %08lx, %d)", ActionString[action], data, lock);
   cRecBase *base = (cRecBase *)rec_base;
   return base ? base->step(action, data, lock) : false;
}

bool cdbRecord::get(ACTION action, int idx, void *key, void *data, bool lock)
{
   DbgTrcDb("Record: get(%s, %d, %08lx, %08lx, %d)", ActionString[action], idx, key, data, lock);
   cRecBase *base = (cRecBase *)rec_base;
   return base ? base->get(action, idx, key, data, lock) : false;
}

bool cdbRecord::unlock(int idx, const void *data)
{
   DbgTrcDb("Record: unlock(%d, %08lx)", idx, data);
   cRecBase *base = (cRecBase *)rec_base;
   return base ? base->unlock(idx, data) : false;
}

cString cdbRecord::getLastErrorMsg() const
{
   DbgTrcDb("Record: getLastErrorMsg()");
   cRecBase *base = (cRecBase *)rec_base;
   return base ? base->getLastErrorMsg() : cString();
}

