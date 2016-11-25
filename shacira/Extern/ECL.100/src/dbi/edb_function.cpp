// ===========================================================================
// edb_function.cpp                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//  cdbTAObject
//   |
//   +--cdbFunction     -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "dbi/edb_function.hpp"
#include "dbi/edb_cursor_ex.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "dbi/edb_cursor.hpp"
#include "dbi/edb_transaction.hpp"
#include "base/eb_sema.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cdbFunction
// ---------------------------------------------------------------------------
//
// cdbTAObject
//  +--cdbFunction
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbFunction : public cdbTAObject {

public:

   // Konstruktor ueber TA-Zeiger
   cdbFunction(cdbTransaction *ta);
   // Konstruktor ueber TA-Referenz
   cdbFunction(cdbTransaction& ta);


   // Ausfuehren von SELECTs
   // ======================

   // SELECT mit int-Ergebnis
   int selectInt(SQL::SELECT sql);
   // SELECT mit double-Ergebnis
   double selectDbl(SQL::SELECT sql);
   // SELECT mit String-Ergebnis
   cString selectStr(SQL::SELECT sql);


protected:

   // Events
   // ======

   // Wird aufgerufen, um die Aktion 'func' auszufuehren
   void onExecAction(cdbDatabase *db, int func);
   // Wird aufgerufen, um den Abbruch der aktuellen Aktion anzufordern
   void onStopAction();
   // Wird aufgerufen, um eine textuelle Signatur der Aktion zu ermitteln
   cString onGetSignature();


private:

   SQL::SELECT sql;           // Auszufuehrendes SQL-Statement (nur SELECT moeglich)

   cdbCursor *current_cu;     // Zeiger auf aktuellen Cursor (oder 0)
   cMutexSem protect_cu_ptr;  // Personenschutz fuer diesen Zeiger
   cErrBase last_error;       // Zuletzt aufgetretener Fehler

   int res_int;               // Result-Variable fuer int-Ergebnisse
   double res_dbl;            // Result-Variable fuer double-Ergebnisse
   cString res_str;           // Result-Variable fuer cString-Ergebnisse

   // current_cu setzen (semaphorengeschuetzt)
   void setCurrentCursor(cdbCursor *cu);

};

#endif /*__INTERFACE__*/


// Implementierung cdbFunctions
// ===========================================================================

cdbFunction::cdbFunction(cdbTransaction *ta) :
   cdbTAObject(ta), last_error(cErrBase::errNoError)
{
   res_int = 0;
   res_dbl = 0.0;
   current_cu = 0;
}

cdbFunction::cdbFunction(cdbTransaction& ta) :
   cdbTAObject(ta), last_error(cErrBase::errNoError)
{
   res_int = 0;
   res_dbl = 0.0;
   current_cu = 0;
}

// Funktionsnummern: 0 = int, 1 = double, 2 = string

int cdbFunction::selectInt(SQL::SELECT sql)
{
   cdbFunction::sql = sql;
   last_error = cErrBase(cErrBase::errNoError);
   res_int = 0;

   bool ok = callAction(0);

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return ok ? res_int : 0;
}

double cdbFunction::selectDbl(SQL::SELECT sql)
{
   cdbFunction::sql = sql;
   last_error = cErrBase(cErrBase::errNoError);
   res_dbl = 0.0;

   bool ok = callAction(1);

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return ok ? res_dbl : 0.0;
}

cString cdbFunction::selectStr(SQL::SELECT sql)
{
   cdbFunction::sql = sql;
   last_error = cErrBase(cErrBase::errNoError);
   res_str.clear();

   bool ok = callAction(2);

   if ( cErrBase::ERR_TYPE(last_error) != cErrBase::errNoError )
      throw last_error;

   return ok ? res_str : cString();
}


// Events
// ======

void cdbFunction::onExecAction(cdbDatabase *db, int func)
{
   try {

      if ( cString(sql).compareNoCase("SELECT", 6) != 0 )
         throw cdbErr(cdbErr::errCompileFailed, cString(sql));

      cdbCursorEx cu(*db);
      setCurrentCursor(&cu);

      cu.compile(sql);
      cu.exec();

      if ( cu.fetch() ) {
         switch ( func ) {
         case 0:  cu.get(0, res_int); break;
         case 1:  cu.get(0, res_dbl); break;
         case 2:  cu.get(0, res_str); break;
         }
      } else {
         throw cdbErr(cdbErr::errNoDataFound, cu);
      }

   } catch ( const cErrBase& err ) {
      last_error = err;
   }

   setCurrentCursor(0);
}

void cdbFunction::onStopAction()
{
   protect_cu_ptr.request();
   current_cu->halt();
   protect_cu_ptr.release();
}

cString cdbFunction::onGetSignature()
{
   return sql;
}

void cdbFunction::setCurrentCursor(cdbCursor *cu)
{
   protect_cu_ptr.request();
   current_cu = cu;
   protect_cu_ptr.release();
}

