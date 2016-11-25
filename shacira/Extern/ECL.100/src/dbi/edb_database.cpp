// ===========================================================================
// edb_database.cpp                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Beschreibung:
//
// Dieses Modul stellt die Basisklasse zur Datenbankunterstuetzung cdbDatabase
// zur Verfuegung. Ueber die folgenden Praeprozessor-Konstanten kann fest-
// gelegt werden, welche der moeglichen Datenbanken parallel betrieben werden
// koennen:
//
//    Konstante | Support                    | Zus. Libraries
//   -----------+----------------------------+----------------
//    __DUMMY__ | Dummy Interface            | -
//    __OCI__   | Oracle Call Interface      | ???.obj
//    __BTI__   | Btrieve ISAM               | wbtrcall.lib
//    __ODBC__  | Open Database Connectivity | odbc.lib
//
// Alle zur Anbindung an die jeweilige Datenbank benoetigten Datentypen,
// Konstanten usw. werden in diesem Modul verborgen, d.h. sind an der Export-
// Schnittstelle nicht notwendig.
//
//    cBase
//     |
//     +--cdbErr                -
//     |
//     +--cdbDatabase             -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#define __DUMMY__

#include "dbi/edb_database.hpp"
#include "dbi/edb_cursor.hpp"
#include "dbi/edb_record.hpp"

#if defined __ECL_OS2__
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

#include "base/eb_base.hpp"
#include "base/eb_err.hpp"
#include "base/eb_str.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbErr
// ---------------------------------------------------------------------------
//
// cBase
//  +--cErrBase
//      +--cdbErr
//
// ===========================================================================

class cdbDatabase;
class cdbCursor;
class cdbRecord;

class __ECL_DLLEXPORT__ cdbErr : public cErrBase {

public:
   cdbErr(ERR_TYPE err, int db = 0);
   cdbErr(ERR_TYPE err, const char *msg);
   cdbErr(ERR_TYPE err, cdbDatabase& db);
   cdbErr(ERR_TYPE err, cdbCursor& cu);
   cdbErr(ERR_TYPE err, cdbRecord& rec);

   enum ERR_CODE { errBase = ERR_PREFIX('D','B','I'),

      // Fehler
      errGeneralDbError   = errBase + errError +  0, // (X) Allgemeiner Datenbankfehler
      errDbTypeNotSupported                        , // (X) Datenbanktyp nicht unterstuetzt
      errLoginFailed                               , // (X) Fehler beim LOGIN an Datenbank
      errResourceTimeout                           , // (X) Timeout beim Zugriff auf eine Resource
      //
      errOpenTableFailed  = errBase + errError +  5, // (X) Fehler beim Oeffnen einer Tabelle (RECORD)
      errResourceBusy                              , // (X) Resource momentan nicht bereit (RECORD)
      errAccessViolation                           , // (X) Datensatz seit letztem Zugriff geaendert (RECORD)
      //
      errAllocEnvFailed   = errBase + errError + 10, // (X) Anforderung einer Umgebung fehlgeschlagen (SQL)
      errAllocConnectFailed                        , // (X) Anforderung einer Verbindung fehlgeschlagen (SQL)
      errAllocCursorFailed                         , // (X) Anforderung eines Cursors fehlgeschlagen (SQL)
      //
      errDefineColFailed  = errBase + errError + 20, // (X) Fehler beim Definieren von Ergebnisspalten
      errBindParamFailed                           , // (X) Fehler beim Binden von Parametervariablen
      errBindParamMissing                          , // (X) Benoetigte Parametervariable nicht gebunden
      errBindStaticFailed                          , // (X) Fehler beim Binden einer statischen Parametervariable
      errSetLockModeFailed                         , // (X) Fehler beim Setzen des Zugriffsmodes
      errCompileFailed                             , // (X) Fehler bei der Analyse einer SQL-Anweisung
      errExecFailed                                , // (X) Fehler beim Ausführen einer SQL-Anweisung
      errFetchFailed                               , // (X) Fehler beim Lesen von der Datenbank
      //
      errNoDataFound      = errBase + errError + 30, // (X)
      //
      errDuplicateKey     = errBase + errError + 40, // ( )
      errBindType                                  , // ( )
      errFetchOutOfSeq                             , // ( )
      errVarNotInList                              , // ( )
      errColumnNull                                , // ( )
      errColumnTooLarge                            , // ( )
      errNullFetched                               , // ( )
      errColumnTrunc                               , // ( )
      errColumnUpdNull                             , // ( )
      errRowidInvalid                              , // ( )
      errValueTooLarge                             , // ( )
      errRowidUnavail                              , // ( )
      errRowidUnavail2                             , // ( )
      errRealOverflow                              , // ( )
      errCheckConstraint                           , // ( )
      errNoParentRecord                            , // ( )
      errChildRecords                              , // ( )
      errNoTrunc                                   , // ( ) IsTruncated() nicht moeglich
      errNoRetcValue                               , // ( ) retc-Code nicht moeglich
      errAutoCommitFailed                          , // ( )

   };

};

#endif /*__INTERFACE__*/


// Implementierung cdbErr
// ===========================================================================

cdbErr::cdbErr(ERR_TYPE err, int db) :
   cErrBase(err)
{
   char msg[128];
   sprintf(msg, "Datenbank-Fehlercode %d", db);
   setParam(0, msg);
}

cdbErr::cdbErr(ERR_TYPE err, const char *msg) :
   cErrBase(err)
{
   setParam(0, msg);
}

cdbErr::cdbErr(ERR_TYPE err, cdbDatabase& db) :
   cErrBase(err)
{
   setParam(0, db.getLastErrorMsg());
}

cdbErr::cdbErr(ERR_TYPE err, cdbCursor& cu) :
   cErrBase(err)
{
   setParam(0, cu.getLastErrorMsg());
   setParam(1, cu.getLastCmd());
}

cdbErr::cdbErr(ERR_TYPE err, cdbRecord& rec) :
   cErrBase(err)
{
   setParam(0, rec.getLastErrorMsg());
}




// ===========================================================================
// Lokale Klasse cDbBase
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDbBase
//
// ===========================================================================

class cDbBase : public cBase {

public:
   cDbBase(cdbDatabase& db);
   virtual ~cDbBase();

   bool login(cString dsn, cString uid, cString pwd);
   bool login(const cDbBase& other);
   bool logout();

   bool setAutoCommit(bool yeah);
   bool setSavepoint(int num);
   bool rollback(int to_num);
   bool commit();

   bool isConnected() const
      { return logged_in; }
   bool isAutoCommit() const
      { return auto_commit; }

   bool supportsCursors() const
      { return !!(onGetSupportInfo() & siCursors); }
   bool supportsRecords() const
      { return !!(onGetSupportInfo() & siRecords); }
   bool supportsDictionary() const
      { return !!(onGetSupportInfo() & siDictionary); }

   cString getDSN() const
      { return dsn; }
   cString getUID() const
      { return uid; }

   long getDriverInfo(int code) const
      { return onGetDriverInfo(code); }
   cString getLastErrorMsg() const
      { return onGetLastErrorMsg(); }
   cString getDatabaseName() const
      { return db_name; }

protected:
   cdbDatabase *db;

   enum SUPPORT_INFO {
      siCursors,     // Datenbank unterstuetzt das Cursor-Konzept
      siRecords,     // Datenbank unterstuetzt das Record-Konzept
      siDictionary   // Datenbank unterstuetzt das Dictionary-Konzept
   };

   virtual bool onLogin(cString dsn, cString uid, cString pwd) = 0;
   virtual bool onLogout() = 0;

   virtual bool onSetAutoCommit(bool yeah) = 0;
   virtual bool onSetSavepoint(int num) = 0;
   virtual bool onRollback(int to_num) = 0;
   virtual bool onCommit() = 0;

   virtual int onGetSupportInfo() const = 0;
   virtual long onGetDriverInfo(int code) const = 0;
   virtual cString onGetLastErrorMsg() const = 0;
   virtual cString onGetDatabaseName() const = 0;

private:
   bool logged_in;
   bool auto_commit;
   cString dsn, uid, pwd;
   cString db_name;

};


// Implementierung cDbBase
// ===========================================================================

cDbBase::cDbBase(cdbDatabase& db)
{
   cDbBase::db = &db;
   logged_in = auto_commit = false;
}

cDbBase::~cDbBase()
{
   // ...
}

bool cDbBase::login(cString dsn, cString uid, cString pwd)
{
   char sql_str[132];
   sprintf(sql_str, "LOGIN dsn=%s uid=%s", Nvl(dsn, "<none>"), Nvl(uid, "<none>"));
   DbgSql(sql_str);

   if ( logged_in )
      logout();

   logged_in = onLogin(dsn, uid, pwd);

   if ( logged_in ) {

      cDbBase::dsn = dsn;
      cDbBase::uid = uid;
      cDbBase::pwd = pwd;

      try {
         setAutoCommit(auto_commit);
      } catch ( cdbErr err ) {
         // Fehler an dieser Stelle ignorieren...
      }

      cDbBase::db_name = onGetDatabaseName();

   }

   return logged_in;
}

bool cDbBase::login(const cDbBase& other)
{
   auto_commit = other.auto_commit;
   return login(other.dsn, other.uid, other.pwd);
}

bool cDbBase::logout()
{
   char sql_str[132];
   sprintf(sql_str, "LOGOUT dsn=%s uid=%s", Nvl(dsn, "<none>"), Nvl(uid, "<none>"));
   DbgSql(sql_str);

   if ( logged_in ) {
      // 20.04.2001 -TE- Auto-Rollback vor Logout, wenn Auto-Commit nicht aktiv.
      // Z.B. hat der Oracle-ODBC-Treiber 8.01.07.00 Probleme ohne dieses "Feature"
      if ( !auto_commit )
         rollback(0);
      logged_in = !onLogout();
   }

   return !logged_in;
}

bool cDbBase::setAutoCommit(bool yeah)
{
   char sql_str[132];
   sprintf(sql_str, "AUTOCOMMIT %s", yeah ? "ON" : "OFF");
   DbgSql(sql_str);

   if ( onSetAutoCommit(yeah) ) {
      auto_commit = !!yeah;
      return true;
   }

   return false;
}

bool cDbBase::setSavepoint(int num)
{
   char sql_str[132];
   sprintf(sql_str, "SAVEPOINT SP%d", num);
   DbgSql(sql_str);
   return onSetSavepoint(num);
}

bool cDbBase::rollback(int to_num)
{
   char sql_str[132];
   sprintf(sql_str, "ROLLBACK TO SP%d", to_num);
   DbgSql(sql_str);
   return onRollback(to_num);
}

bool cDbBase::commit()
{
   DbgSql("COMMIT");
   return onCommit();
}




#if defined(__DUMMY__)

// ===========================================================================
// Lokale Klasse cDbDummy
// ---------------------------------------------------------------------------
//
// Folgende Codes sind fuer getDriverInfo() definiert:
//
// cBase
//  +--cDbBase
//      +--cDbDummy
//
// ===========================================================================

class cDbDummy : public cDbBase {

public:
   cDbDummy(cdbDatabase& db);
   ~cDbDummy();

protected:
   bool onLogin(cString dsn, cString uid, cString pwd);
   bool onLogout();

   bool onSetAutoCommit(bool yeah);
   bool onSetSavepoint(int num);
   bool onRollback(int to_num);
   bool onCommit();

   int onGetSupportInfo() const
      { return siCursors | siRecords | siDictionary; }
   long onGetDriverInfo(int /*code*/) const
      { return -1; }
   cString onGetLastErrorMsg() const
      { return "no error"; }
   cString onGetDatabaseName() const
      { return "DUMMY"; }

};


// Implementierung cDbDummy
// ===========================================================================

cDbDummy::cDbDummy(cdbDatabase& db) :
   cDbBase(db)
{
   // ...
}

cDbDummy::~cDbDummy()
{
   // ...
}

bool cDbDummy::onLogin(cString dsn, cString uid, cString pwd)
{
   DbgDb("Dummy: Login(%s,%s,%s)", Nvl(dsn,""), Nvl(uid,""), Nvl(pwd,""));
   return true;
}

bool cDbDummy::onLogout()
{
   DbgDb("Dummy: Logout()");
   return true;
}

bool cDbDummy::onSetAutoCommit(bool yeah)
{
   DbgDb("Dummy: SetAutoCommit(%d)", yeah);
   return true;
}

bool cDbDummy::onSetSavepoint(int num)
{
   DbgDb("Dummy: SetSavepoint(%d)", num);
   return true;
}

bool cDbDummy::onRollback(int to_num)
{
   DbgDb("Dummy: Rollback(%d)", to_num);
   return true;
}

bool cDbDummy::onCommit()
{
   DbgDb("Dummy: Commit()");
   return true;
}

#endif /*__DUMMY__*/




#if defined(__OCI__)

// ===========================================================================
// Lokale Klasse cDbOCI
// ---------------------------------------------------------------------------
//
// Folgende Codes sind fuer getDriverInfo() definiert:
//
//    0 = Code des zuletzt aufgetretenen Fehlers
//    1 = Adresse der hda
//    2 = Adresse der lda
//
// cBase
//  +--cDbBase
//      +--cDbOCI
//
// ===========================================================================

class cDbOCI : public cDbBase {

public:
   cDbOCI(cdbDatabase& db);
   ~cDbOCI();

protected:
   bool onLogin(cString dsn, cString uid, cString pwd);
   bool onLogout();

   bool onSetAutoCommit(bool yeah);
   bool onSetSavepoint(int num);
   bool onRollback(int to_num);
   bool onCommit();

   int onGetSupportInfo() const;
   long onGetDriverInfo(int code) const;
   cString onGetLastErrorMsg() const;
   cString onGetDatabaseName() const;

private:
   UCHAR hda[256];
   Lda_Def lda;
   int last_err;

   void setError();

};


// Implementierung cDbOCI
// ===========================================================================

cDbOCI::cDbOCI(cdbDatabase& db) :
   cDbBase(db)
{
   last_err = 0;
}

cDbOCI::~cDbOCI()
{
   // ...
}

bool cDbOCI::onLogin(cString dsn, cString uid, cString pwd)
{
   DbgDb("OCI: Login(%s,%s,%s)", Nvl(dsn,""), Nvl(uid,""), Nvl(pwd,""));
   return
      !orlon(&lda, hda, (text*)uid, -1, (text*)pwd, -1, -1);
}

bool cDbOCI::onLogout()
{
   DbgDb("OCI: Logout()");
   ologof(&lda);
   return true;
}

bool cDbOCI::onSetAutoCommit(bool yeah)
{
   DbgDb("OCI: SetAutoCommit(%d)", yeah);
   bool ok = yeah ? ocon(&lda) : ocof(&lda);
   if ( !ok ) setError();
   return ok;
}

bool cDbOCI::onSetSavepoint(int num)
{
   DbgDb("OCI: SetSavepoint(%d)", num);
   return true;
}

bool cDbOCI::onRollback(int to_num)
{
   DbgDb("OCI: Rollback(%d)", to_num);
   return
      orol(&lda)? (setError(),false) : true;
}

bool cDbOCI::onCommit()
{
   DbgDb("OCI: Commit()");
   return
      ocom(&lda)? (setError(),false) : true;
}

void cDbOCI::setError()
{
   last_err = lda.rc;
}

int cDbOCI::onGetSupportInfo() const
{
   return siCursors | siDictionary;
}

long cDbOCI::onGetDriverInfo(int code) const
{
   switch ( code ) {
    case 0: return (long)last_err;
    case 1: return (long)hda;
    case 2: return (long)&lda;
   }
   return -1;
}

cString cDbOCI::onGetLastErrorMsg() const
{
   char buffer[512];
   oerhms((Lda_Def*)&lda, last_err, (text*)buffer, sizeof buffer);
   return buffer;
}

cString cDbOCI::onGetDatabaseName() const
{
   return "ORACLE";
}

#endif /*__OCI__*/




#if defined(__BTI__)

// ===========================================================================
// Lokale Klasse cDbBTI
// ---------------------------------------------------------------------------
//
// Folgende Codes sind fuer getDriverInfo() definiert:
//
//    0 = Code des zuletzt aufgetretenen Fehlers
//    1 = Zeiger auf String mit Datenbank-Pfad
//    2 = Zeiger auf String mit Default-Extension
//
// cBase
//  +--cDbBase
//      +--cDbBTI
//
// ===========================================================================

class cDbBTI : public cDbBase {

public:
   cDbBTI(cdbDatabase& db);
   ~cDbBTI();

protected:
   bool onLogin(cString dsn, cString uid, cString pwd);
   bool onLogout();

   bool onSetAutoCommit(bool yeah);
   bool onSetSavepoint(int num);
   bool onRollback(int to_num);
   bool onCommit();

   int onGetSupportInfo() const;
   long onGetDriverInfo(int code) const;
   cString onGetLastErrorMsg() const;
   cString onGetDatabaseName() const;

private:
   int last_stat;

};


// Implementierung cDbBTI
// ===========================================================================

cDbBTI::cDbBTI(cdbDatabase& db) :
   cDbBase(db)
{
   last_stat = 0;
}

cDbBTI::~cDbBTI()
{
   // ...
}

bool cDbBTI::onLogin(cString /*dsn*/, cString /*uid*/, cString /*pwd*/)
{
   last_stat = b_begin((char *)(void *)""/*options*/);
   DbgDb("Btrieve: Startup status = %d", last_stat);
   return !last_stat;
}

bool cDbBTI::onLogout()
{
   last_stat = b_end();
   DbgDb("Btrieve: Shutdown status = %d", last_stat);
   return !last_stat;
}

bool cDbBTI::onSetAutoCommit(bool /*yeah*/)
{
   DbgDb("Btrieve: auto-commit not supported");
   return true;
}

bool cDbBTI::onSetSavepoint(int /*num*/)
{
   DbgDb("Btrieve: Begin transaction");
   b_beginTransaction(NULL, NULL, NULL, NULL, NULL);
   return true;
}

bool cDbBTI::onRollback(int /*to_num*/)
{
   DbgDb("Btrieve: Abort transaction");
   b_abortTransaction(NULL, NULL, NULL, NULL, NULL);
   return true;
}

bool cDbBTI::onCommit()
{
   DbgDb("Btrieve: End transaction");
   b_endTransaction(NULL, NULL, NULL, NULL, NULL);
   return true;
}

int cDbBTI::onGetSupportInfo() const
{
   return siRecords | siDictionary;
}

long cDbBTI::onGetDriverInfo(int code) const
{
   char *bti_path = getenv("ETCL_BTIPATH");
   char *bti_ext = getenv("ETCL_BTIEXT");

   switch ( code ) {
    case 0: return (long)last_stat;
    case 1: return (long)(bti_path ? bti_path : ".\\");
    case 2: return (long)(bti_ext ? bti_ext : "dbf");
   }
   return -1;
}

cString cDbBTI::onGetLastErrorMsg() const
{
   char error_str[80];
   sprintf(error_str, "Btrieve status code %d", last_stat);
   return error_str;
}

cString cDbBTI::onGetDatabaseName() const
{
   return "BTRIEVE";
}

#endif /*__BTI__*/




#if defined(__ODBC__)

// ===========================================================================
// Lokale Klasse cDbODBC
// ---------------------------------------------------------------------------
//
// Folgende Codes sind fuer getDriverInfo() definiert:
//
//    1 = Environment-Handle (henv)
//    2 = Connection-Handle (hdbc)
//    3 = Identifier-quote-char
//
// cBase
//  +--cDbBase
//      +--cDbODBC
//
// ===========================================================================

class cDbODBC : public cDbBase {

public:
   cDbODBC(cdbDatabase& db);
   ~cDbODBC();

protected:
   bool onLogin(cString dsn, cString uid, cString pwd);
   bool onLogout();

   bool onSetAutoCommit(bool yeah);
   bool onSetSavepoint(int num);
   bool onRollback(int to_num);
   bool onCommit();

   int onGetSupportInfo() const;
   long onGetDriverInfo(int code) const;
   cString onGetLastErrorMsg() const;
   cString onGetDatabaseName() const;

private:
   static HENV henv;
   static int connect_count;
   HDBC hdbc;
   char quote_char;

};


// Implementierung cDbODBC
// ===========================================================================

HENV cDbODBC::henv = NULL;
int cDbODBC::connect_count = 0;

cDbODBC::cDbODBC(cdbDatabase& db) :
   cDbBase(db)
{
   quote_char = '\"';
}

cDbODBC::~cDbODBC()
{
   // ...
}

bool cDbODBC::onLogin(cString dsn, cString uid, cString pwd)
{
   if ( !henv && SQLAllocEnv((HENV FAR *)&henv) != SQL_SUCCESS ) {
      henv = NULL;
      throw cdbErr(cdbErr::errAllocEnvFailed, *db);
   }

   DbgDb("ODBC: AllocEnv(), henv = %08lx", henv);

   if ( henv && SQLAllocConnect(henv, (HDBC FAR *)&hdbc) != SQL_SUCCESS ) {
      hdbc = NULL;
      throw cdbErr(cdbErr::errAllocConnectFailed, *db);
   } else {
      connect_count++;
   }

   DbgDb("ODBC: AllocConnect(%08lx), hdbc = %08lx", henv, hdbc);

   if ( hdbc ) {
      #ifdef USE_SQLCONNECT
         SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 5);
         RETCODE rc = SQLConnect(hdbc,
            (UCHAR FAR *)dsn, SQL_NTS,
            (UCHAR FAR *)uid, SQL_NTS,
            (UCHAR FAR *)pwd, SQL_NTS);
      #else
         char in_buf[255] = "", out_buf[255] = "";
         SWORD out_buf_len = sizeof out_buf;
         if ( !dsn.isEmpty() )
            sprintf(in_buf+0, "DSN=%s;", (const char *)dsn);
         if ( !uid.isEmpty() )
            sprintf(in_buf+strlen(in_buf), "UID=%s;", (const char *)uid);
         if ( !pwd.isEmpty() )
            sprintf(in_buf+strlen(in_buf), "PWD=%s;", (const char *)pwd);
         #if ODBCVER >= 0x0300
            SQLSetConnectAttr(hdbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)60, SQL_IS_UINTEGER);
            SQLSetConnectAttr(hdbc, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)20, SQL_IS_UINTEGER);
            //ORADB-LOCK-TEST: SQLSetConnectAttr(hdbc, SQL_ATTR_CONNECTION_TIMEOUT, (void*)1, 0);
         #else
            SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 60);
            SQLSetConnectOption(hdbc, SQL_QUERY_TIMEOUT, 20);
         #endif
         RETCODE rc = SQLDriverConnect(hdbc, NULL,
            (UCHAR FAR *)in_buf, SQL_NTS,
            (UCHAR FAR *)out_buf, sizeof out_buf,
            (SWORD FAR *)&out_buf_len,
            SQL_DRIVER_COMPLETE);
         DbgDb("ODBC: DriverConnect(%08lx, '%s'), out_buf = '%s', status = %d", hdbc, in_buf, out_buf, rc);
      #endif
      if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO ) {
         DbgError(getLastErrorMsg());
         throw cdbErr(cdbErr::errLoginFailed);
      }

      char value[32]; SQLSMALLINT len;
      rc = SQLGetInfo(hdbc, SQL_IDENTIFIER_QUOTE_CHAR, &value, sizeof value, &len);
      DbgDb("ODBC: SQLGetInfo(%08lx, SQL_IDENTIFIER_QUOTE_CHAR) = '%s', status = %d", hdbc, value, rc);
      quote_char = rc == SQL_SUCCESS && *value ? *value : ' ';

      rc = SQLGetInfo(hdbc, SQL_DBMS_NAME, &value, sizeof value, &len);
      DbgDb("ODBC: SQLGetInfo(%08lx, SQL_DBMS_NAME) = '%s', status = %d", hdbc, value, rc);
      if ( rc == SQL_SUCCESS && strcmp(value, "Oracle") == 0 ) quote_char = ' '; // Oracle kann's nicht...

      return true;
   }

   return false;
}

bool cDbODBC::onLogout()
{
   if ( henv ) {
      if ( connect_count > 0 ) {
         DbgDb("ODBC: Disconnect()");
         SQLDisconnect(hdbc);
         SQLFreeConnect(hdbc);
         connect_count--;
         hdbc = NULL;
      }
      if ( connect_count == 0 ) {
         DbgDb("ODBC: FreeEnv()");
         SQLFreeEnv(henv);
         henv = NULL;
      }
   }

   return true;
}

bool cDbODBC::onSetAutoCommit(bool yeah)
{
   RETCODE rc = SQLSetConnectOption(hdbc, SQL_AUTOCOMMIT, yeah);
   DbgDb("ODBC: SetConnectOption(%08lx, AUTOCOMMIT=%d), status = %d", hdbc, yeah, rc);
   return rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO;
}

bool cDbODBC::onSetSavepoint(int num)
{
   DbgDb("ODBC: SetSavepoint not implemented", num);
   return true;
}

bool cDbODBC::onRollback(int /*to_num*/)
{
   RETCODE rc = SQLTransact(henv, hdbc, SQL_ROLLBACK);
   DbgDb("ODBC: Transact(%08lx, ROLLBACK), status = %d", hdbc, rc);
   return rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO;
}

bool cDbODBC::onCommit()
{
   RETCODE rc = SQLTransact(henv, hdbc, SQL_COMMIT);
   DbgDb("ODBC: Transact(%08lx, COMMIT), status = %d", hdbc, rc);
   return rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO;
}

int cDbODBC::onGetSupportInfo() const
{
   return siCursors | siDictionary;
}

long cDbODBC::onGetDriverInfo(int code) const
{
   switch ( code ) {
   case 1: return (long)henv;
   case 2: return (long)hdbc;
   case 3: return (long)quote_char;
   }
   return -1;
}

cString cDbODBC::onGetLastErrorMsg() const
{
   cString buffer;
   UCHAR stat[SQL_SQLSTATE_SIZE+1];
   UCHAR msg[SQL_MAX_MESSAGE_LENGTH+1];
   RETCODE abort = false;
   SDWORD native_error = 0;

   do {

      *stat = *msg = '\0';

      SWORD msg_len = SQL_MAX_MESSAGE_LENGTH - 1;
      RETCODE rc = SQLError(henv, hdbc, NULL,
         (UCHAR FAR *)stat,
         (SDWORD FAR *)&native_error,
         (UCHAR FAR *)msg,
         SQL_MAX_MESSAGE_LENGTH - 1,
         (SWORD FAR *)&msg_len);

      switch ( rc ) {
      case SQL_SUCCESS:
      case SQL_SUCCESS_WITH_INFO:   buffer += cStringf("%s: %s", stat, msg); break;
      case SQL_NO_DATA_FOUND:       abort = true; break;
      case SQL_ERROR:               buffer += "Error during SQLError"; abort = true; break;
      case SQL_INVALID_HANDLE:      buffer += "Error during SQLError"; abort = true; break;
      }

   } while ( !abort );

   return buffer;
}

cString cDbODBC::onGetDatabaseName() const
{
   char name[128]; SQLSMALLINT len;
   RETCODE rc = SQLGetInfo(hdbc, SQL_DBMS_NAME, &name, sizeof name, &len);
   DbgDb("ODBC: SQLGetInfo(%08lx, SQL_DBMS_NAME) = '%s', status = %d", hdbc, name, rc);
   return rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO ? name : 0;
}

#endif /*__ODBC__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbDatabase
// ---------------------------------------------------------------------------
//
// Diese Klasse repraesentiert eine Verbindung zu einer Datenbank. Im Kon-
// struktor kann zwischen folgenden Datenbanktypen gewaehlt werden:
//
//    - DUMMY - Dummy Interface (ohne Funktionalitaet)
//    - OCI - Oracle Call Interface
//    - BTI - Btrieve ISAM
//    - ODBC - Open Database Connectivity
//
// cBase
//  +--cdbDatabase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbDatabase : public cBase {

public:
   enum DB_TYPE {
      DUMMY,         // Dummy Interface
      OCI,           // Oracle Call Interface
      BTI,           // Btrieve ISAM
      ODBC           // Open Database Connectivity
   };

   cdbDatabase(DB_TYPE type, cString dsn, cString uid, cString pwd = NULL);
   cdbDatabase(const cdbDatabase& other);
   ~cdbDatabase();

   bool isConnected() const;
   bool isAutoCommit() const;

   DB_TYPE getType() const { return type; }
   cString getName() const;

   bool supportsCursors() const;
   bool supportsRecords() const;
   bool supportsDictionary() const;

   bool login(cString dsn, cString uid, cString pwd = cString());
   bool logout();

   bool setAutoCommit(bool yeah = false);
   bool setSavepoint(int num = 0);
   bool rollback(int to_num = 0);
   bool commit();

   cString getDSN() const;
   cString getUID() const;

   long getDriverInfo(int code) const;
   cString getLastErrorMsg() const;

private:
   DB_TYPE type;
   void *db_base;

};

#endif /*__INTERFACE__*/


// Implementierung cdbDatabase
// ===========================================================================

cdbDatabase::cdbDatabase(DB_TYPE type, cString dsn, cString uid, cString pwd)
{
   cDbBase *db = NULL;
   cdbDatabase::type = type;
   db_base = 0;

   switch ( type ) {
      #if defined(__DUMMY__)
         case DUMMY: db = new0 cDbDummy(*this); break;
      #endif
      #if defined(__OCI__)
         case OCI:   db = new0 cDbOCI(*this); break;
      #endif
      #if defined(__BTI__)
         case BTI:   db = new0 cDbBTI(*this); break;
      #endif
      #if defined(__ODBC__)
         case ODBC:  db = new0 cDbODBC(*this); break;
      #endif
   }

   if ( db ) {

      // Hier eventuelle cdbErr-Fehler abfangen, da bei throw cdbErr mit der
      // Variante ueber db-Konstruktor das cdbDatabase-Objekt bereits geloescht ist,
      // wenn cdbErr versucht, die Fehlermeldung auszulesen.

      try { db->login(dsn, uid, pwd);
      } catch ( cdbErr err ) {
         DbgError("Anmelden an Datenbank %s fehlgeschlagen", Nvl(dsn, "<Ohne Namen>"));
         throw cdbErr(cdbErr::errLoginFailed);
      }

   }

   db_base = db;
}

cdbDatabase::cdbDatabase(const cdbDatabase& other)
{
   cDbBase *db = NULL;
   cDbBase *other_base = (cDbBase *)other.db_base;
   db_base = 0;

   if ( other_base ) {
      switch ( other.type ) {
         #if defined(__DUMMY__)
            case DUMMY: db = new0 cDbDummy(*this); break;
         #endif
         #if defined(__OCI__)
            case OCI:   db = new0 cDbOCI(*this); break;
         #endif
         #if defined(__BTI__)
            case BTI:   db = new0 cDbBTI(*this); break;
         #endif
         #if defined(__ODBC__)
            case ODBC:  db = new0 cDbODBC(*this); break;
         #endif
      }
      if ( db )
         db->login(*other_base);
   }

   type = other.type;
   db_base = db;
}

cdbDatabase::~cdbDatabase()
{
   cDbBase *base = (cDbBase *)db_base;
   if ( base ) base->logout();
   delete base;
}

bool cdbDatabase::isConnected() const
{
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->isConnected() : false;
}

bool cdbDatabase::isAutoCommit() const
{
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->isAutoCommit() : false;
}

bool cdbDatabase::login(cString dsn, cString uid, cString pwd)
{
   DbgTrcDb("Database: login(%s,%s,%s)", Nvl(dsn,""), Nvl(uid,""), Nvl(pwd,""));
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->login(dsn, uid, pwd) : false;
}

bool cdbDatabase::logout()
{
   DbgTrcDb("Database: logout()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->logout() : false;
}

bool cdbDatabase::setAutoCommit(bool yeah)
{
   DbgTrcDb("Database: setAutoCommit(%s)", yeah ? "on" : "off");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->setAutoCommit(yeah) : false;
}

bool cdbDatabase::setSavepoint(int num)
{
   DbgTrcDb("Database: savepoint(%d)", num);
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->setSavepoint(num) : false;
}

bool cdbDatabase::rollback(int to_num)
{
   DbgTrcDb("Database: rollback(%d)", to_num);
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->rollback(to_num) : false;
}

bool cdbDatabase::commit()
{
   DbgTrcDb("Database: commit()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->commit() : false;
}

cString cdbDatabase::getName() const
{
   DbgTrcDb("Database: getName()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->getDatabaseName() : 0;
}

bool cdbDatabase::supportsCursors() const
{
   DbgTrcDb("Database: supportsCursors()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->supportsCursors() : false;
}

bool cdbDatabase::supportsRecords() const
{
   DbgTrcDb("Database: supportsRecords()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->supportsRecords() : false;
}

bool cdbDatabase::supportsDictionary() const
{
   DbgTrcDb("Database: supportsDictionary()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->supportsDictionary() : false;
}

cString cdbDatabase::getDSN() const
{
   DbgTrcDb("Database: getDSN()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->getDSN() : cString();
}

cString cdbDatabase::getUID() const
{
   DbgTrcDb("Database: getUID()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->getUID() : cString();
}

long cdbDatabase::getDriverInfo(int code) const
{
   DbgTrcDb("Database: getDriverInfo(%d)", code);
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->getDriverInfo(code) : -1;
}

cString cdbDatabase::getLastErrorMsg() const
{
   DbgTrcDb("Database: getLastErrorMsg()");
   cDbBase *base = (cDbBase *)db_base;
   return base ? base->getLastErrorMsg() : cString();
}


