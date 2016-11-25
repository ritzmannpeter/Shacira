// ===========================================================================
// edb_cursor.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdbCursor                -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#define __DUMMY__

#include "dbi/edb_cursor.hpp"
#include "base/eb_array.hpp"

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

#include <time.h>
#include "dbi/edb_sql.hpp"
#include "dbi/edb_database.hpp"
#include "store/es_var.hpp"

#endif /*__INTERFACE__*/




// Lokale Daten
// ===========================================================================

static const char *VarTypeStr[] = {
   "tShort", "tLong", "tFloat", "tDouble", "tChar", "tString", "tRowid",
   "tDate", "tTime", "tTimeStamp"
};




// ===========================================================================
// Lokale Klasse cCuVars
// ---------------------------------------------------------------------------
//
// cCuVars
//
// Wichtig: Array fester Groesse hier notwendig, da Zeiger in dieses Array
// an die Datenbank uebergeben werden!!!
//
// ===========================================================================

class cCuVars {

public:

   // Konstruktor
   cCuVars(cdbCursor *cu);

   // Maximale Anzahl moeglicher Variablen erfragen
   inline int getMaxVars() const
      { return CURSOR_MAX_VARS; }
   // Aktuelle Anzahl eingetragener Variablen erfragen
   inline int getVarCount() const
      { return count; }

   // Zaehler zuruecksetzen
   void reset();

   // Storage an naechster freier Position eintragen
   cdbCursor::check *setStorage(csStorage *store);
   // Variable an Position 'n' eintragen
   cdbCursor::check *setStorage(int n, csStorage *store);

   // Definition von Position 'n' entfernen
   void removeVar(int n);

   // Puffergroesse der Variable an Position 'n' erfragen
   int getBufferSize(int n) const;
   // Pufferadresse der Variable an Position 'n' erfragen
   void *getBuffer(int n) const;
   // Variablentyp der Variable an Position 'n' erfragen
   cdbCursor::VARTYPE getType(int n) const;


protected:

   // Variablen-Typ erfragen: Sind es Parametervariablen?
   virtual bool isBindVars() const { return false; }
   // Variablen-Typ erfragen: Sind es Ergebnisvariablen?
   virtual bool isDefineVars() const { return false; }

   struct VAR {

      // Konstruktor
      VAR();
      // Destruktor
      ~VAR();
      // Variable mit Storage 'store' initialisieren (an Position 'n')
      void init(int n, csStorage *store);
      // Evtl. allokierte Resourcen wieder freigeben
      void clean();

      cdbCursor::VARTYPE type;   // Datenbank-Typ der Variablen
      cdbCursor::check ind;      // Datenbank-NULL-Indikator
      bool own_buffer;           // Hat VAR einen eigenen Puffer?
      void *buffer;              // Zeiger auf Puffer
      int buffer_size;           // Groesse des Puffers
      csStorage *var;            // Zeiger auf Storage-Objekt

   };

   enum { CURSOR_MAX_VARS = 96 };

   VAR vars[CURSOR_MAX_VARS];
   cdbCursor *cu;
   int count;

};


// Implementierung cCuVars
// ===========================================================================

cCuVars::cCuVars(cdbCursor *cu)
{
   cCuVars::cu = cu;
   count = 0;
}

cCuVars::VAR::VAR()
{
   var = 0;
   buffer = 0;
   buffer_size = 0;
   own_buffer = false;
}

cCuVars::VAR::~VAR()
{
   if ( own_buffer && buffer != 0 )
      free(buffer);
}

void cCuVars::VAR::init(int /*n*/, csStorage *store)
{
   bool use_own_buffer;
   int new_buffer_size;
   cdbCursor::VARTYPE new_type;

   switch ( store->getType() ) {
   case csStorage::tInt:
      use_own_buffer = !store->isBufferCompatible();
      new_buffer_size = sizeof(long);
      new_type = cdbCursor::tLong;
      break;
   case csStorage::tDouble:
      use_own_buffer = !store->isBufferCompatible();
      new_buffer_size = store->getBufferSize();
      new_type = cdbCursor::tDouble;
      break;
   case csStorage::tTime:
      use_own_buffer = true;
      new_buffer_size = sizeof(cdbCursor::time);
      new_type = cdbCursor::tTime;
      break;
   case csStorage::tDate:
   case csStorage::tWeek:
      use_own_buffer = true;
      new_buffer_size = sizeof(cdbCursor::date);
      new_type = cdbCursor::tDate;
      break;
   case csStorage::tDateTime:
      use_own_buffer = true;
      new_buffer_size = sizeof(cdbCursor::timestamp);
      new_type = cdbCursor::tTimeStamp;
      break;
   case csStorage::tChar:
      use_own_buffer = true;
      #define __tChar_has_2_bytes__
      #ifdef __tChar_has_2_bytes__
         new_buffer_size = 2; // Problem: CHAR(1) wird als "c\0" geliefert!
      #else
         new_buffer_size = 1;
      #endif
      new_type = cdbCursor::tChar;
      break;
   case csStorage::tString:
      use_own_buffer = !store->isBufferCompatible();
      if ( store->getFlags(csStorage::fStoreFixLen) )
         use_own_buffer = true;
      new_buffer_size = store->getBufferSize();
      new_type = cdbCursor::tString;
      break;
   default:
      use_own_buffer = true;
      new_buffer_size = sizeof(long);
      new_type = cdbCursor::tLong;
      break;
   }

   if ( use_own_buffer ) {
      if ( new_buffer_size > buffer_size || !own_buffer) {
         clean();
         VAR::buffer = malloc(new_buffer_size);
      }
   } else {
      clean();
      VAR::buffer = store->getBuffer();
   }

   VAR::type = new_type;
   VAR::buffer_size = new_buffer_size;
   VAR::own_buffer = use_own_buffer;
   VAR::var = store;
}

void cCuVars::VAR::clean()
{
   var = 0;

   if ( own_buffer ) {
      if ( buffer != 0 )
         free(buffer);
      buffer = 0;
      own_buffer = false;
   }
}

void cCuVars::reset()
{
   count = 0;
}

cdbCursor::check * cCuVars::setStorage(csStorage *store)
{
   if ( __ECL_ASSERT1__(count >= 0 && count < CURSOR_MAX_VARS) ) {
      vars[count].init(count, store);
      return &vars[count++].ind;
   } else {
      return 0;
   }
}

cdbCursor::check * cCuVars::setStorage(int n, csStorage *store)
{
   if ( __ECL_ASSERT1__(n >= 0 && n < CURSOR_MAX_VARS) ) {
      count = max(count, n+1);
      vars[n].init(n, store);
      return &vars[n].ind;
   } else {
      return 0;
   }
}

void cCuVars::removeVar(int n)
{
   if ( __ECL_ASSERT1__(n >= 0 && n < CURSOR_MAX_VARS) )
      vars[n].clean();
}

int cCuVars::getBufferSize(int n) const
{
   if ( __ECL_ASSERT1__(n >= 0 && n < CURSOR_MAX_VARS && vars[n].var != 0) ) {
      return vars[n].buffer_size;
   } else {
      return sizeof(long);
   }
}

void * cCuVars::getBuffer(int n) const
{
   if ( __ECL_ASSERT1__(n >= 0 && n < CURSOR_MAX_VARS && vars[n].var != 0) ) {
      return vars[n].buffer;
   } else {
      static long dummy_buffer;
      return &dummy_buffer;
   }
}

cdbCursor::VARTYPE cCuVars::getType(int n) const
{
   if ( __ECL_ASSERT1__(n >= 0 && n < CURSOR_MAX_VARS && vars[n].var != 0) ) {
      return vars[n].type;
   } else {
      return cdbCursor::tLong;
   }
}




// ===========================================================================
// Lokale Klasse cCuBindVars
// ---------------------------------------------------------------------------
//
// cCuVars
//  +--cCuBindVars
//
// ===========================================================================

class cCuBindVars : public cCuVars {

public:
   // Konstruktor
   cCuBindVars(cdbCursor *cu) : cCuVars(cu) { }
   // Bindung an Parametervariablen durchfuehren
   void doBindVars();
   // Bindung an String fester Laenge durchfuehren
   void doBindFixLenString(VAR& var);
   // Variablen-Typ erfragen: Sind es Parametervariablen?
   bool isBindVars() const { return true; }

};


// Implementierung cCuBindVars
// ===========================================================================

void cCuBindVars::doBindVars()
{
   for ( int i=0 ; i<count ; i++ ) {
      VAR& var = vars[i];
      if ( var.var != 0 ) {
         if ( var.var->isNull() ) {
            cu->setNull(var.ind);
         } else if ( var.type == cdbCursor::tString ) {
            if ( var.var->getFlags(csStorage::fStoreFixLen) ) {
               cu->setSize(var.ind, var.buffer_size - 1); // String fester Laenge
            } else {
               cu->setSize(var.ind, -2); // nullterminierter String
            }
         } else {
            cu->setSize(var.ind, var.buffer_size);
         }
         if ( var.own_buffer ) {
            switch ( var.type ) {
            case cdbCursor::tLong:
               if ( !var.var->get(*((int*)var.buffer)) )
                  cu->setNull(var.ind);
               break;
            case cdbCursor::tDouble:
               if ( !var.var->get(*((double*)var.buffer)) )
                  cu->setNull(var.ind);
               break;
            case cdbCursor::tChar:
               #ifdef __tChar_has_2_bytes__
                  cu->setSize(var.ind, 1); // Wichtig!!
               #endif
               if ( !var.var->get(*((char*)var.buffer)) )
                  cu->setNull(var.ind);
               break;
            case cdbCursor::tTime:
               {
                  cTime buf;
                  if ( var.var->get(buf) ) {
                     cu->set(*((cdbCursor::time*)var.buffer), buf);
                  } else {
                     cu->setNull(var.ind);
                  }
               }
               break;
            case cdbCursor::tDate:
               {
                  cDate buf;
                  if ( var.var->get(buf) ) {
                     cu->set(*((cdbCursor::date*)var.buffer), buf);
                  } else {
                     cu->setNull(var.ind);
                  }
               }
               break;
            case cdbCursor::tTimeStamp:
               {
                  cDateTime buf;
                  if ( var.var->get(buf) ) {
                     cu->set(*((cdbCursor::timestamp*)var.buffer), buf);
                  } else {
                     cu->setNull(var.ind);
                  }
               }
               break;
            case cdbCursor::tString:
               {
                  cString buf;
                  if ( var.var->get(buf) ) {
                     strxcpy((char*)var.buffer, buf, var.buffer_size);
                     if ( var.var->getFlags(csStorage::fStoreFixLen) )
                        doBindFixLenString(var);
                  } else {
                     cu->setNull(var.ind);
                  }
               }
               break;
            }
         } else {
            switch ( var.type ) {
            case cdbCursor::tString:
               {
                  cString buf;
                  if ( var.var->get(buf) ) {
                     strxcpy((char*)var.buffer, buf, var.buffer_size);
                     if ( var.var->getFlags(csStorage::fStoreFixLen) )
                        doBindFixLenString(var);
                  } else {
                     cu->setNull(var.ind);
                  }
               }
               break;
            }
         }
      }
   }
}

void cCuBindVars::doBindFixLenString(VAR& var)
{
   // String rechts mit Leerzeichen anfuellen, bis 'buffer_size' - 1,
   // anschliessend ein 0-Terminator. Dann sind genau die Anzahl in
   // der DB definierter Zeichen belegt.

   char *str = (char *)var.buffer;
   int pos = strlen(str);

   //cBase::DbgOut(0, "+++ FIXED LENGTH STRING: '%s', buffer size = %d", str, var.buffer_size);
   while ( pos < var.buffer_size - 1 )
      str[pos++] = ' ';

   str[pos] = '\0';
   //cBase::DbgOut(0, "+++     MODIFIED STRING: '%s'", (const char *)var.buffer);
}




// ===========================================================================
// Lokale Klasse cCuDefineVars
// ---------------------------------------------------------------------------
//
// cCuVars
//  +--cCuDefineVars
//
// ===========================================================================

class cCuDefineVars : public cCuVars {

public:
   // Konstruktor
   cCuDefineVars(cdbCursor *cu) : cCuVars(cu) { }
   // Bindung an Ergebnisvariablen durchfuehren
   void doDefineVars();
   // Variablen-Typ erfragen: Sind es Ergebnisvariablen?
   bool isDefineVars() const { return true; }

};


// Implementierung cCuDefineVars
// ===========================================================================

void cCuDefineVars::doDefineVars()
{
   for ( int i = 0 ; i < count ; i++ ) {
      VAR& var = vars[i];
      if ( var.var != 0 ) {
         if ( cu->isNull(var.ind) ) {
            var.var->setNull(true);
         } else {
            var.var->setNull(false);
            if ( var.own_buffer ) {
               switch ( var.type ) {
               case cdbCursor::tLong:      var.var->put(int(*((long*)var.buffer))); break;
               case cdbCursor::tDouble:    var.var->put(*((double*)var.buffer)); break;
               case cdbCursor::tTime:      var.var->put(cu->get(*(cdbCursor::time*)var.buffer)); break;
               case cdbCursor::tDate:      var.var->put(cu->get(*(cdbCursor::date*)var.buffer)); break;
               case cdbCursor::tTimeStamp: var.var->put(cu->get(*(cdbCursor::timestamp*)var.buffer)); break;
               case cdbCursor::tChar:      var.var->put(*((char*)var.buffer)); break;
               case cdbCursor::tString:    var.var->put((const char*)var.buffer); break;
               }
            }
         }
         // Leerstellen rechts eleminieren (rtrim)
         if ( var.type == cdbCursor::tString && var.buffer != 0 ) {
            int len = strlen((char*)var.buffer);
            char *p = (char*)var.buffer + len - 1;
            while ( len-- > 0 && *p == ' ' )
               *p-- = '\0';
         }
      }
   }
}




// ===========================================================================
// Lokale Klasse cCuBase
// ---------------------------------------------------------------------------
//
// cBase
//  +--cCuBase
//
// ===========================================================================

class cCuBase : public cBase {

public:
   cCuBase(cdbCursor& cu);
   virtual ~cCuBase();

   bool open(cdbDatabase& db, int prefetch_count);
   bool close();

   cdbDatabase *getDatabase() const
      { return db; }
   cdbCursor *getCursor() const
      { return cu; }

   int getSize(const cdbCursor::check& ind) const
      { return onGetSize(ind); }
   bool isNull(const cdbCursor::check& ind) const
      { return onIsNull(ind); }
   short getDate(const cdbCursor::date& var, cdbCursor::DTFIELD field) const
      { return onGetDate(var, field); }
   short getTime(const cdbCursor::time& var, cdbCursor::DTFIELD field) const
      { return onGetTime(var, field); }
   short getTimeStamp(const cdbCursor::timestamp& var, cdbCursor::DTFIELD field) const
      { return onGetTimeStamp(var, field); }

   void setSize(cdbCursor::check& ind, int size) const
      { onSetSize(ind, size); }
   void setNull(cdbCursor::check& ind) const
      { onSetNull(ind); }
   void setDate(cdbCursor::date& var, cdbCursor::DTFIELD field, short value) const
      { onSetDate(var, field, value); }
   void setTime(cdbCursor::time& var, cdbCursor::DTFIELD field, short value) const
      { onSetTime(var, field, value); }
   void setTimeStamp(cdbCursor::timestamp& var, cdbCursor::DTFIELD field, short value) const
      { onSetTimeStamp(var, field, value); }


   // Binden von Parametern
   // =====================

   struct DEF_PAR {
      cdbCursor::VARTYPE type;
      cdbCursor::check *ind;
      void *buf;
      size_t len;
   };

   // Ergebnisparameter in Spalte n binden
   void define(int n, const DEF_PAR& par);
   // Ergebnisparameter in Spalte n an csStorage-Objekt binden
   void define(int n, csStorage *var);
   // Bindung an Ergebnisparameter aufheben
   void define(int n);
   // Uebergabeparameter in Spalte n binden
   void bind(int n, const DEF_PAR& par);
   // Uebergabeparameter in Spalte n an csVar-Objekt binden
   void bind(int n, csStorage *var);
   // Bindung fuer Uebergabeparameter aufheben
   void bind(int n);
   // Uebergabeparameter mit Namen name binden
   void bind(cString name, const DEF_PAR& par);
   // Uebergabeparameter mit Namen name an csVar-Objekt binden
   void bind(cString name, csStorage *var);
   // Statischen Parameter binden
   static void bindStatic(int n, const char *buf);
   // Statisch gebundenen Parameter ermitteln
   static const char *getStaticBound(int n);


   // Ausfuehren
   // ==========

   // Locking-Modus setzen
   void setLockMode(cdbCursor::CONCURRENCY concur);
   // Vorbereiten
   void compile(SQL::STMT sql_str);
   // Ausfuehren
   void exec(SQL::STMT sql_str);
   // Ergebniszeile laden
   bool fetch();
   // Ausfuehrung anhalten
   void halt();
   // Verarbeitung (u.U. vorzeitig) beenden
   void closeCursor();

   // SQL-Statement ermitteln
   SQL::STMT getSQL() const
      { return orig_sql_str; }

   //OLD:void exec(int n);
   //OLD:bool fetch(int n);


   // Schluesselfelder
   // ================

   // Ermittelt die Anzahl Ergebnisspalten, die einen eindeutigen Schluessel bilden
   int getKeyCount() const;
   // Ermittelt die Feldnummer der n-ten Schluesselspalte
   int getKeyField(int n) const;
   // Ermittelt die Feldnummer der Namensspalte
   int getNameField() const;
   // Ermittelt die Feldnummer der Beschreibungsspalte
   int getDescrField() const;


   // Eigenschaften der Ergebnisspalten
   // =================================

   // Anzahl Ergebnisspalten (= Felder) erfragen
   int getFieldCount();
   // Feldname erfragen
   cString getFieldName(int n);
   // Label des Feldes erfragen
   cString getFieldLabel(int n);
   // Name des Schemas der Basistabelle erfragen
   cString getFieldBaseSchema(int n);
   // Name der Basistabelle erfragen
   cString getFieldBaseTable(int n);
   // Name des Feldes in der Basistabelle erfragen
   cString getFieldBaseColumn(int n);
   // Variablentyp erfragen
   cdbCursor::VARTYPE getFieldType(int n);
   // Maximale Spaltenbreite erfragen
   int getFieldSize(int n);
   // Anzahl Nachkommastellen erfragen
   int getFieldDigits(int n);
   // Erfragen, ob die Spalte NULL-Werte enthalten darf
   bool getFieldNullable(int n);
   // Erfragen, ob die Spalte einen Wert fester Laenge enthaelt
   bool getFieldFixedLength(int n);


   // Eigenschaften der Parameter
   // ===========================

   // Anzahl Parameter erfragen
   int getParamCount();
   // Variablentyp erfragen
   cdbCursor::VARTYPE getParamType(int n);
   // Maximale Spaltenbreite erfragen
   int getParamSize(int n);
   // Anzahl Nachkommastellen erfragen
   int getParamDigits(int n);
   // Erfragen, ob der Parameter NULL-Werte enthalten darf
   bool getParamNullable(int n);
   // Erfragen, ob der Parameter einen Wert fester Laenge enthaelt
   bool getParamFixedLength(int n);


   bool getDescr(int n, char *name, short *db_size, cdbCursor::VARTYPE *type, short *width);
   long getRowCount();

   virtual cString getLastErrorMsg() const = 0;
   cString getLastCmd() const;
   cString getLastParams() const;


   // Prefetching
   // ===========

   bool mustPrefetch() const
      { return prefetch_count > 1; }
   int getPrefetchCount() const
      { return prefetch_count; }


   // Treiber-Internas
   // ================

   // Treiberspezifische Informationen ermitteln
   long getDriverInfo(int code) const;
   // Treiberspezifische Routinen ausfuehren
   int executeDriverCode(int code, void *data);


protected:

   cdbDatabase *db;
   cdbCursor *cu;


   // Binden von csVar-Objekten
   // =========================

   cCuBindVars bind_vars;
   cCuDefineVars define_vars;


   // Events
   // ======

   virtual bool onOpen(cdbDatabase& db) = 0;
   virtual bool onClose() = 0;

   virtual int onGetSize(const cdbCursor::check& ind) const = 0;
   virtual bool onIsNull(const cdbCursor::check& ind) const = 0;
   virtual short onGetDate(const cdbCursor::date& var, cdbCursor::DTFIELD field) const = 0;
   virtual short onGetTime(const cdbCursor::time& var, cdbCursor::DTFIELD field) const = 0;
   virtual short onGetTimeStamp(const cdbCursor::timestamp& var, cdbCursor::DTFIELD field) const = 0;

   virtual void onSetSize(cdbCursor::check& ind, int size) const = 0;
   virtual void onSetNull(cdbCursor::check& ind) const = 0;
   virtual void onSetDate(cdbCursor::date& var, cdbCursor::DTFIELD field, short value) const = 0;
   virtual void onSetTime(cdbCursor::time& var, cdbCursor::DTFIELD field, short value) const = 0;
   virtual void onSetTimeStamp(cdbCursor::timestamp& var, cdbCursor::DTFIELD field, short value) const = 0;

   virtual void onDefineColumn(int n, const DEF_PAR& par) = 0;
   virtual void onBindColumn(int n, const DEF_PAR& par) = 0;
   virtual void onBindName(cString name, const DEF_PAR& par) = 0;
   virtual void onUndefineColumn(int n) = 0;
   virtual void onUnbindColumn(int n) = 0;

   virtual void onSetLockMode(cdbCursor::CONCURRENCY concur) = 0;
   virtual void onCompile(SQL::STMT sql_str, SQL::STMT sql_new) = 0;
   virtual void onExec(SQL::STMT sql_str, SQL::STMT sql_new) = 0;
   virtual bool onFetch() = 0;
   virtual void onHalt() = 0;
   virtual void onCloseCursor() = 0;

   virtual int onGetKeyCount() const = 0;
   virtual int onGetKeyField(int n) const = 0;
   virtual int onGetNameField() const = 0;
   virtual int onGetDescrField() const = 0;

   //virtual void onExecMulti(int count) = 0;
   //virtual bool onFetchMulti(int count) = 0;

   virtual bool onGetDescr(int n, char *name, short *db_size, cdbCursor::VARTYPE *type, short *width) = 0;
   virtual long onGetRowCount() = 0;


   // Eigenschaften der Ergebnisspalten
   // =================================

   enum FIELD_FLAGS {
      ffValidName       = (1 << 0),
      ffValidLabel      = (1 << 1),
      ffValidBaseSchema = (1 << 2),
      ffValidBaseTable  = (1 << 3),
      ffValidBaseColumn = (1 << 4),
      ffValidType       = (1 << 5),
      ffValidSize       = (1 << 6),
      ffValidDigits     = (1 << 7),
      ffValidNullable   = (1 << 8),
      ffValidFixedLen   = (1 << 9),
      // erweiterbar
      ffIsNullable      = (1 << 16),
      ffIsFixedLength   = (1 << 17)
   };

   struct FIELD_INFO {
      FIELD_INFO() { flags = 0; }
      int flags;
      cString name;
      cString label;
      cString base_schema;
      cString base_table;
      cString base_column;
      cdbCursor::VARTYPE type;
      int size;
      short digits;
   };

   int field_count;
   typedef cArray<FIELD_INFO, const FIELD_INFO&> FIELD_ARRAY;
   FIELD_ARRAY field_info;

   // Anzahl Ergebnisspalten (= Felder) erfragen
   virtual int onGetFieldCount() = 0;
   // Feldname erfragen
   virtual cString onGetFieldName(int n) = 0;
   // Label des Feldes erfragen
   virtual cString onGetFieldLabel(int n) = 0;
   // Name des Schemas der Basistabelle erfragen
   virtual cString onGetFieldBaseSchema(int n) = 0;
   // Name der Basistabelle erfragen
   virtual cString onGetFieldBaseTable(int n) = 0;
   // Name des Feldes in der Basistabelle erfragen
   virtual cString onGetFieldBaseColumn(int n) = 0;
   // Variablentyp erfragen
   virtual cdbCursor::VARTYPE onGetFieldType(int n) = 0;
   // Maximale Spaltenbreite erfragen
   virtual int onGetFieldSize(int n) = 0;
   // Anzahl Nachkommastellen erfragen
   virtual int onGetFieldDigits(int n) = 0;
   // Erfragen, ob die Spalte NULL-Werte enthalten darf
   virtual bool onGetFieldNullable(int n) = 0;
   // Erfragen, ob die Spalte einen Wert fester Laenge enthaelt
   virtual bool onGetFieldFixedLength(int n) = 0;


   // Eigenschaften der Parameter
   // ===========================

   enum PARAM_FLAGS {
      pfValidType       = (1 << 0),
      pfValidSize       = (1 << 1),
      pfValidDigits     = (1 << 2),
      pfValidNullable   = (1 << 3),
      pfValidFixedLen   = (1 << 4),
      // erweiterbar
      pfIsNullable      = (1 << 16),
      pfIsFixedLength   = (1 << 17)
   };

   struct PARAM_INFO {
      PARAM_INFO() { flags = 0; }
      int flags;
      cdbCursor::VARTYPE type;
      int size;
      short digits;
   };

   int param_count;
   typedef cArray<PARAM_INFO, const PARAM_INFO&> PARAM_ARRAY;
   PARAM_ARRAY param_info;

   // Anzahl Parameter erfragen
   virtual int onGetParamCount() = 0;
   // Variablentyp erfragen
   virtual cdbCursor::VARTYPE onGetParamType(int n) = 0;
   // Maximale Spaltenbreite erfragen
   virtual int onGetParamSize(int n) = 0;
   // Anzahl Nachkommastellen erfragen
   virtual int onGetParamDigits(int n) = 0;
   // Erfragen, ob der Parameter NULL-Werte enthalten darf
   virtual bool onGetParamNullable(int n) = 0;
   // Erfragen, ob der Parameter einen Wert fester Laenge enthaelt
   virtual bool onGetParamFixedLength(int n) = 0;


   // Treiber-Internas
   // ================

   // Treiberspezifische Informationen ermitteln
   virtual long onGetDriverInfo(int code) const = 0;
   // Treiberspezifische Routinen ausfuehren
   virtual int onExecuteDriverCode(int code, void *data) = 0;


private:
   int prefetch_count;
   int key_count;
   int name_field;
   int descr_field;

   static int open_cursors;
   static int max_open_cursors;
   static char var_static[10][32];

   SQL::STMT orig_sql_str, actual_sql_str;
   typedef cArray<DEF_PAR, const DEF_PAR&> PAR_ARRAY;
   PAR_ARRAY actual_params;

   SQL::STMT applyStatics(SQL::STMT sql_str);
   int calcKeyCount(SQL::STMT sql_str);

   void checkFieldInfo(int n);
   void checkParamInfo(int n);
   void invalidateCache();

};


// Implementierung cCuBase
// ===========================================================================

int cCuBase::open_cursors = 0;
int cCuBase::max_open_cursors = 0;
char cCuBase::var_static[10][32] = { '\0' };

cCuBase::cCuBase(cdbCursor& cu) :
   define_vars(&cu), bind_vars(&cu)
{
   cCuBase::cu = &cu;
   cCuBase::db = NULL;
   cCuBase::prefetch_count = 1;
   cCuBase::key_count = -1;
   cCuBase::name_field = -1;
   cCuBase::descr_field = -1;
   invalidateCache();
}

cCuBase::~cCuBase()
{
   // ...
}


void cCuBase::invalidateCache()
{
   field_count = -1;
   param_count = -1;

   for ( int i = 0 ; i < field_info.getSize() ; i++ )
      field_info[i].flags = 0;
   for ( int j = 0 ; j < param_info.getSize() ; j++ )
      param_info[j].flags = 0;
}

bool cCuBase::open(cdbDatabase& db, int prefetch_count)
{
   cCuBase::db = &db;
   cCuBase::prefetch_count = prefetch_count;
   invalidateCache();

   if ( ++open_cursors > max_open_cursors )
      max_open_cursors = open_cursors;

   return onOpen(db);
}

bool cCuBase::close()
{
   if ( onClose() ) {
      --open_cursors;
      return true;
   }

   return false;
}

void cCuBase::define(int n, const DEF_PAR& par)
{
   if ( n < 0 || n >= define_vars.getMaxVars() )
      throw cdbErr(cdbErr::errDefineColFailed, *cu);

   if ( !par.buf || par.len == 0 )
      throw cdbErr(cdbErr::errInvParam, *cu);

   define_vars.removeVar(n);
   onDefineColumn(n, par);
}

void cCuBase::define(int n, csStorage *var)
{
   if ( n < 0 || n >= define_vars.getMaxVars() )
      throw cdbErr(cdbErr::errDefineColFailed, *cu);

   DEF_PAR par;
   par.ind  = define_vars.setStorage(n, var);
   par.buf  = define_vars.getBuffer(n);
   par.len  = define_vars.getBufferSize(n);
   par.type = define_vars.getType(n);

   if ( !par.buf || par.len == 0 )
      throw cdbErr(cdbErr::errInvParam, *cu);

   onDefineColumn(n, par);
}

void cCuBase::define(int n)
{
   if ( n < 0 || n >= define_vars.getMaxVars() )
      throw cdbErr(cdbErr::errDefineColFailed, *cu);

   define_vars.removeVar(n);
   onUndefineColumn(n);
}

void cCuBase::bind(int n, const DEF_PAR& par)
{
   if ( n < 0 || n >= bind_vars.getMaxVars() )
      throw cdbErr(cdbErr::errBindParamFailed, *cu);

   if ( !par.buf /*|| par.len == 0*/ )
      throw cdbErr(cdbErr::errInvParam, *cu);

   if ( n >= actual_params.getSize() )
      actual_params.setSize(n+1);

   bind_vars.removeVar(n);

   actual_params[n] = par;
   onBindColumn(n, par);
}

void cCuBase::bind(int n, csStorage *var)
{
   if ( n < 0 || n >= bind_vars.getMaxVars() )
      throw cdbErr(cdbErr::errBindParamFailed, *cu);

   DEF_PAR par;
   par.ind  = bind_vars.setStorage(n, var);
   par.buf  = bind_vars.getBuffer(n);
   par.len  = bind_vars.getBufferSize(n);
   par.type = bind_vars.getType(n);

   if ( n >= actual_params.getSize() )
      actual_params.setSize(n+1);

   actual_params[n] = par;
   onBindColumn(n, par);
}

void cCuBase::bind(int n)
{
   if ( n < 0 || n >= bind_vars.getMaxVars() )
      throw cdbErr(cdbErr::errBindParamFailed, *cu);

   bind_vars.removeVar(n);
   onUnbindColumn(n);
}

void cCuBase::bind(cString name, const DEF_PAR& par)
{
   if ( name.isEmpty() )
      throw cdbErr(cdbErr::errBindParamFailed, *cu);

   if ( !par.buf /*|| par.len == 0*/ )
      throw cdbErr(cdbErr::errInvParam, *cu);

   onBindName(name, par);
}

void cCuBase::bind(cString name, csStorage *var)
{
   if ( name.isEmpty() )
      throw cdbErr(cdbErr::errBindParamFailed, *cu);

   DEF_PAR par;
   par.ind  = bind_vars.setStorage(var);
   par.buf  = bind_vars.getBuffer(bind_vars.getVarCount() - 1);
   par.len  = bind_vars.getBufferSize(bind_vars.getVarCount() - 1);
   par.type = bind_vars.getType(bind_vars.getVarCount() - 1);

   bind(name, par);
}

void cCuBase::bindStatic(int n, const char *buf)
{
   if ( n < 0 || n > 9 )
      throw cdbErr(cdbErr::errBindStaticFailed);

   if ( !buf )
      throw cdbErr(cdbErr::errInvParam);

   strxcpy(var_static[n], buf, 32);
}

const char * cCuBase::getStaticBound(int n)
{
   if ( n < 0 || n > 9 )
      throw cdbErr(cdbErr::errBindStaticFailed);

   return var_static[n];
}

int cCuBase::calcKeyCount(SQL::STMT sql_str)
{
   int count = 1;
   int field_count = 0;

   if ( sql_str.getType() == SQL::STMT_SELECT ) {
      SQL::SELECT select = cString(sql_str);
      field_count = select.getFields().getFieldCount();
   }

   SQL::HINTS hints = sql_str.getHints();
   SQL::HINT hint = hints.getHint("PK");
   if ( !hint.getValue().isEmpty() )
      count = atoi(hint.getValue());

   name_field = max(min(field_count-1, count), 0);
   descr_field = max(min(field_count-1, count /* + 1*/), 0);

   hint = hints.getHint("NAME");
   if ( !hint.getValue().isEmpty() )
      name_field = atoi(hint.getValue());

   hint = hints.getHint("DESCR");
   if ( !hint.getValue().isEmpty() )
      descr_field = atoi(hint.getValue());

   return count;
}

SQL::STMT cCuBase::applyStatics(SQL::STMT sql_str)
{
   cString sql_orig = sql_str, sql_new;
   int pos = 0, last_pos = 0;

   while ( (pos = sql_orig.getPos("$##", pos)) >= 0 ) {
      if ( sql_orig.getLength() > pos + 3 && isdigit(sql_orig[pos+3]) ) {
         sql_new << sql_orig.getMid(last_pos, pos - last_pos)
                 << var_static[sql_orig[pos+3] - '0'];
         last_pos = (pos += 4);
      } else if ( sql_orig.getLength() > pos + 3 && sql_orig[pos+3] == '.' ) {
         sql_new << sql_orig.getMid(last_pos, pos - last_pos);
         last_pos = (pos += 4);
      } else {
         pos += 3;
      }
   }

   sql_new << sql_orig.getRight(sql_orig.getLength() - last_pos);

   return sql_new;
}

void cCuBase::setLockMode(cdbCursor::CONCURRENCY concur)
{
   onSetLockMode(concur);
}

void cCuBase::compile(SQL::STMT sql_str)
{
   if ( cString(sql_str).isEmpty() )
      throw cdbErr(cdbErr::errInvParam, *cu);

   bind_vars.reset();
   define_vars.reset();

   orig_sql_str = sql_str;
   key_count = calcKeyCount(sql_str);
   actual_sql_str = applyStatics(sql_str);
   actual_sql_str.setHints(SQL::HINTS());
   onCompile(sql_str, actual_sql_str);
}

void cCuBase::exec(SQL::STMT sql_str)
{
   invalidateCache();

   if ( cString(sql_str).isEmpty() ) {
      onExec(cString(), cString());
   } else {
      // 20.03.2002 -TE- Voelliger Unfug! Variablen _muessen_ in diesem Fall
      // ja gerade VOR dem Aufruf von exec gebunden werden! (Und nicht danach!)
      // bind_vars.reset();
      // define_vars.reset();
      orig_sql_str = sql_str;
      key_count = calcKeyCount(sql_str);
      actual_sql_str = applyStatics(sql_str);
      actual_sql_str.setHints(SQL::HINTS());
      onExec(sql_str, actual_sql_str);
   }
}

bool cCuBase::fetch()
{
   return onFetch();
}

void cCuBase::halt()
{
   onHalt();
}

void cCuBase::closeCursor()
{
   onCloseCursor();
}

// void cCuBase::exec(int n)
// {
//    invalidateCache();
//
//    if ( n <= 0 )
//       throw cErrBase(cErrBase::errInvParam);
//
//    onExecMulti(n);
// }
//
// bool cCuBase::fetch(int n)
// {
//    if ( n <= 0 )
//       throw cErrBase(cErrBase::errInvParam);
//
//    return onFetchMulti(n);
// }


// Schluesselfelder
// ================

int cCuBase::getKeyCount() const
{
   int count = onGetKeyCount();
   return count >= 0 ? count : key_count;
}

int cCuBase::getKeyField(int n) const
{
   // Diese Funktion darf NIEMALS einen Wert < 0 liefern!
   // (Sonst Endlosrekursion in cursor_ex moeglich!!)

   if ( __ECL_ASSERT1__(n >= 0) ) {
      int field = onGetKeyField(n);
      return field >= 0 ? field : n;
   }

   return 0;
}

int cCuBase::getNameField() const
{
   int field = onGetNameField();
   return field >= 0 ? field : name_field;
}

int cCuBase::getDescrField() const
{
   int field = onGetDescrField();
   return field >= 0 ? field : descr_field;
}


// Eigenschaften der Ergebnisspalten
// =================================

void cCuBase::checkFieldInfo(int n)
{
   if ( field_info.getSize() < n+1 )
      field_info.setSize(n+1);
}

int cCuBase::getFieldCount()
{
   if ( field_count < 0 )
      field_count = onGetFieldCount();
   return field_count;
}

cString cCuBase::getFieldName(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidName) ) {
      field_info[n].name = onGetFieldName(n);
      field_info[n].flags |= ffValidName;
   }

   return field_info[n].name;
}

cString cCuBase::getFieldLabel(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidLabel) ) {
      field_info[n].label = onGetFieldLabel(n);
      field_info[n].flags |= ffValidLabel;
   }

   return field_info[n].label;
}

cString cCuBase::getFieldBaseSchema(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidBaseSchema) ) {
      field_info[n].base_schema = onGetFieldBaseSchema(n);
      field_info[n].flags |= ffValidBaseSchema;
   }

   return field_info[n].base_schema;
}

cString cCuBase::getFieldBaseTable(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidBaseTable) ) {
      field_info[n].base_table = onGetFieldBaseTable(n);
      if ( field_info[n].base_table.isEmpty() && actual_sql_str.getType() == SQL::STMT_SELECT ) {
         // TBD: Workaround, Treiber kann Basistabelle nicht finden:
         field_info[n].base_table = SQL::SELECT(actual_sql_str).getFrom().getBaseTable();
      }
      field_info[n].flags |= ffValidBaseTable;
   }

   return field_info[n].base_table;
}

cString cCuBase::getFieldBaseColumn(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidBaseColumn) ) {
      field_info[n].base_column = onGetFieldBaseColumn(n);
      field_info[n].flags |= ffValidBaseColumn;
   }

   return field_info[n].base_column;
}


cdbCursor::VARTYPE cCuBase::getFieldType(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidType) ) {
      field_info[n].type = onGetFieldType(n);
      field_info[n].flags |= ffValidType;
   }

   return field_info[n].type;
}

int cCuBase::getFieldSize(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidSize) ) {
      field_info[n].size = onGetFieldSize(n);
      field_info[n].flags |= ffValidSize;
   }

   return field_info[n].size;
}

int cCuBase::getFieldDigits(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidDigits) ) {
      field_info[n].digits = short(onGetFieldDigits(n));
      field_info[n].flags |= ffValidDigits;
   }

   return field_info[n].digits;
}

bool cCuBase::getFieldNullable(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidNullable) ) {
      if ( onGetFieldNullable(n) ) {
         field_info[n].flags |= ffIsNullable;
      } else {
         field_info[n].flags &= ~ffIsNullable;
      }
      field_info[n].flags |= ffValidNullable;
   }

   return !!(field_info[n].flags & ffIsNullable);
}

bool cCuBase::getFieldFixedLength(int n)
{
   checkFieldInfo(n);

   if ( !(field_info[n].flags & ffValidFixedLen) ) {
      if ( onGetFieldFixedLength(n) ) {
         field_info[n].flags |= ffIsFixedLength;
      } else {
         field_info[n].flags &= ~ffIsFixedLength;
      }
      field_info[n].flags |= ffValidFixedLen;
   }

   return !!(field_info[n].flags & ffIsFixedLength);
}


// Eigenschaften der Parameter
// ===========================

void cCuBase::checkParamInfo(int n)
{
   if ( param_info.getSize() < n+1 )
      param_info.setSize(n+1);
}

int cCuBase::getParamCount()
{
   if ( param_count < 0 )
      param_count = onGetParamCount();
   return param_count;
}

cdbCursor::VARTYPE cCuBase::getParamType(int n)
{
   checkParamInfo(n);

   if ( !(param_info[n].flags & pfValidType) ) {
      param_info[n].type = onGetParamType(n);
      param_info[n].flags |= pfValidType;
   }

   return param_info[n].type;
}

int cCuBase::getParamSize(int n)
{
   checkParamInfo(n);

   if ( !(param_info[n].flags & pfValidSize) ) {
      param_info[n].size = onGetParamSize(n);
      param_info[n].flags |= pfValidSize;
   }

   return param_info[n].size;
}

int cCuBase::getParamDigits(int n)
{
   checkParamInfo(n);

   if ( !(param_info[n].flags & pfValidDigits) ) {
      param_info[n].digits = short(onGetParamDigits(n));
      param_info[n].flags |= pfValidDigits;
   }

   return param_info[n].digits;
}

bool cCuBase::getParamNullable(int n)
{
   checkParamInfo(n);

   if ( !(param_info[n].flags & pfValidNullable) ) {
      if ( onGetParamNullable(n) ) {
         param_info[n].flags |= pfIsNullable;
      } else {
         param_info[n].flags &= ~pfIsNullable;
      }
      param_info[n].flags |= pfValidNullable;
   }

   return !!(param_info[n].flags & pfIsNullable);
}

bool cCuBase::getParamFixedLength(int n)
{
   checkParamInfo(n);

   if ( !(param_info[n].flags & pfValidFixedLen) ) {
      if ( onGetParamFixedLength(n) ) {
         param_info[n].flags |= pfIsFixedLength;
      } else {
         param_info[n].flags &= ~pfIsFixedLength;
      }
      param_info[n].flags |= pfValidFixedLen;
   }

   return !!(param_info[n].flags & pfIsFixedLength);
}

// ---

bool cCuBase::getDescr(int n, char *name, short *db_size, cdbCursor::VARTYPE *type, short *width)
{
   if ( n < 0 || n > 64 )
      throw cdbErr(cdbErr::errBindParamFailed, *cu);

   return onGetDescr(n, name, db_size, type, width);
}

long cCuBase::getRowCount()
{
   return onGetRowCount();
}

cString cCuBase::getLastCmd() const
{
   cString last_cmd = "[" + actual_sql_str;
   cString last_params = getLastParams();

   if ( !last_params.isEmpty() )
      last_cmd += "; " + last_params;

   return last_cmd += "]";
}

cString cCuBase::getLastParams() const
{
   cString last_cmd;

   for ( int i = 0 ; i < actual_params.getSize() ; i++ ) {

      if ( actual_params[i].buf ) {

         bool incl_len = false;
         DEF_PAR const & p = actual_params[i];
         if ( !last_cmd.isEmpty() )
            last_cmd += "; ";
         last_cmd += "P" + Str(i+1) + "=";

         switch ( p.type ) {
         case cdbCursor::tShort:       last_cmd += Str(*((short*)p.buf)); break;
         case cdbCursor::tLong:        last_cmd += Str(*((long*)p.buf)); break;
         case cdbCursor::tFloat:       last_cmd += Str((double)*((float*)p.buf)); break;
         case cdbCursor::tDouble:      last_cmd += Str(*((double*)p.buf)); break;
         case cdbCursor::tChar:        last_cmd += "'" + Str(*((char *)p.buf)) + "'"; incl_len = true; break;
         case cdbCursor::tString:      last_cmd += "'" + cString((const char *)p.buf) + "'"; incl_len = true; break;
         case cdbCursor::tRowid:       last_cmd += "ROWID"; break;
         case cdbCursor::tDate:        last_cmd += "DATE(" + cu->get(*((cdbCursor::date*)p.buf)).getStr() + ")"; break;
         case cdbCursor::tTime:        last_cmd += "TIME(" + cu->get(*((cdbCursor::time*)p.buf)).getStr() + ")"; break;
         case cdbCursor::tTimeStamp:   last_cmd += "TIMESTAMP(" + cu->get(*((cdbCursor::timestamp*)p.buf)).getStr() + ")"; break;
         default:                      last_cmd += "<unknown_type>"; break;
         }

         if ( incl_len )
            last_cmd += cStringf("(%d)", p.len);
      }

   }

   return last_cmd;
}


// Treiber-Internas
// ================

long cCuBase::getDriverInfo(int code) const
{
   return onGetDriverInfo(code);
}

int cCuBase::executeDriverCode(int code, void *data)
{
   return onExecuteDriverCode(code, data);
}




#if defined(__DUMMY__)

// ===========================================================================
// Definition cCuDummy
// ---------------------------------------------------------------------------
//
// cBase
//  +--cCuBase
//      +--cCuDummy
//
// ===========================================================================

class cCuDummy : public cCuBase {

public:
   cCuDummy(cdbCursor& cu);
   ~cCuDummy();

   cString getLastErrorMsg() const;

protected:
   bool onOpen(cdbDatabase& db);
   bool onClose();

   int onGetSize(const cdbCursor::check&) const { return 0; }
   bool onIsNull(const cdbCursor::check&) const { return false; }
   short onGetDate(const cdbCursor::date&, cdbCursor::DTFIELD) const { return 1; }
   short onGetTime(const cdbCursor::time&, cdbCursor::DTFIELD) const { return 1; }
   short onGetTimeStamp(const cdbCursor::timestamp&, cdbCursor::DTFIELD) const { return 1; }

   void onSetSize(cdbCursor::check&, int) const { }
   void onSetNull(cdbCursor::check&) const { }
   void onSetDate(cdbCursor::date&, cdbCursor::DTFIELD, short) const { }
   void onSetTime(cdbCursor::time&, cdbCursor::DTFIELD, short) const { }
   void onSetTimeStamp(cdbCursor::timestamp&, cdbCursor::DTFIELD, short) const { }

   void onDefineColumn(int n, const DEF_PAR& par);
   void onBindColumn(int n, const DEF_PAR& par);
   void onBindName(cString name, const DEF_PAR& par);
   void onUndefineColumn(int n);
   void onUnbindColumn(int n);

   void onSetLockMode(cdbCursor::CONCURRENCY concur);
   void onCompile(SQL::STMT sql_str, SQL::STMT sql_new);
   void onExec(SQL::STMT sql_str, SQL::STMT sql_new);
   bool onFetch();
   void onHalt();
   void onCloseCursor();

   int onGetKeyCount() const { return -1; }
   int onGetKeyField(int) const { return -1; }
   int onGetNameField() const { return -1; }
   int onGetDescrField() const { return -1; }

   //void onExecMulti(int count);
   //bool onFetchMulti(int count);

   bool onGetDescr(int n, char *name, short *db_size, cdbCursor::VARTYPE *type, short *width);
   long onGetRowCount();

   int onGetFieldCount();
   cString onGetFieldName(int) { return cString(); }
   cString onGetFieldLabel(int) { return cString(); }
   cString onGetFieldBaseSchema(int) { return cString(); }
   cString onGetFieldBaseTable(int) { return cString(); }
   cString onGetFieldBaseColumn(int) { return cString(); }
   cdbCursor::VARTYPE onGetFieldType(int) { return cdbCursor::tString; }
   int onGetFieldSize(int) { return 0; }
   int onGetFieldDigits(int) { return 0; }
   bool onGetFieldNullable(int) { return false; }
   bool onGetFieldFixedLength(int) { return false; }

   int onGetParamCount() { return -1; }
   cdbCursor::VARTYPE onGetParamType(int) { return cdbCursor::tString; }
   int onGetParamSize(int) { return 0; }
   int onGetParamDigits(int) { return 0; }
   bool onGetParamNullable(int) { return false; }
   bool onGetParamFixedLength(int) { return false; }

   int VarTypeC(cdbCursor::VARTYPE t);
   int VarTypeSQL(cdbCursor::VARTYPE t);

   long onGetDriverInfo(int code) const;
   int onExecuteDriverCode(int code, void *data);

};


// Implementierung cCuDummy
// ===========================================================================

cCuDummy::cCuDummy(cdbCursor& cu) :
   cCuBase(cu)
{
   // ...
}

cCuDummy::~cCuDummy()
{
   // ...
}

bool cCuDummy::onOpen(cdbDatabase& /*db*/)
{
   DbgDb("Dummy: Open");
   return true;
}

bool cCuDummy::onClose()
{
   DbgDb("Dummy: Close");
   return true;
}

void cCuDummy::onDefineColumn(int n, const DEF_PAR& /*par*/)
{
   DbgDb("Dummy: DefineColumn(%d)", n);
}

void cCuDummy::onBindColumn(int n, const DEF_PAR& /*par*/)
{
   DbgDb("Dummy: BindColumn(%d)", n);
}

void cCuDummy::onBindName(cString name, const DEF_PAR& /*par*/)
{
   DbgDb("Dummy: BindName(%s)", (const char *)name);
}

void cCuDummy::onUndefineColumn(int n)
{
   DbgDb("Dummy: UndefineColumn(%d)", n);
}

void cCuDummy::onUnbindColumn(int n)
{
   DbgDb("Dummy: UnbindColumn(%d)", n);
}

void cCuDummy::onSetLockMode(cdbCursor::CONCURRENCY concur)
{
   DbgDb("Dummy: SetLockMode(%s)", concur == cdbCursor::cLocked ? "LOCKED" : "READONLY");
}

void cCuDummy::onCompile(SQL::STMT /*sql_str*/, SQL::STMT sql_new)
{
   DbgDb("Dummy: Compile(%s)", Nvl(cString(sql_new), "<NONE>"));
}

void cCuDummy::onExec(SQL::STMT /*sql_str*/, SQL::STMT sql_new)
{
   DbgDb("Dummy: Exec(%s)", Nvl(cString(sql_new), "<NONE>"));
}

bool cCuDummy::onFetch()
{
   DbgDb("Dummy: Fetch");
   return false;
}

void cCuDummy::onHalt()
{
   DbgDb("Dummy: Break");
}

void cCuDummy::onCloseCursor()
{
   DbgDb("Dummy: CloseCursor");
}

// void cCuDummy::onExecMulti(int n)
// {
//    DbgDb("Dummy: ExecMulti(%d)", n);
// }
//
// bool cCuDummy::onFetchMulti(int n)
// {
//    DbgDb("Dummy: FetchMulti(%d)", n);
//    return false;
// }

bool cCuDummy::onGetDescr(int n, char * /*name*/, short * /*db_size*/, cdbCursor::VARTYPE * /*type*/, short * /*width*/)
{
   DbgDb("Dummy: GetDescr(%d)", n);
   return false;
}

int cCuDummy::onGetFieldCount()
{
   DbgDb("Dummy: GetFieldCount");
   return -1;
}

long cCuDummy::onGetRowCount()
{
   DbgDb("Dummy: GetRowCount");
   return 0;
}

int cCuDummy::VarTypeC(cdbCursor::VARTYPE /*t*/)
{
   return 0;
}

int cCuDummy::VarTypeSQL(cdbCursor::VARTYPE /*t*/)
{
   return 0;
}

cString cCuDummy::getLastErrorMsg() const
{
   return "no error";
}

long cCuDummy::onGetDriverInfo(int code) const
{
   DbgDb("Dummy: GetDriverInfo(%d)", code);
   return 0;
}

int cCuDummy::onExecuteDriverCode(int code, void *)
{
   DbgDb("Dummy: ExecuteDriverCode(%d)", code);
   return 0;
}

#endif /*__DUMMY__*/




#if defined(__OCI__)

// ===========================================================================
// Definition cCuOCI
// ---------------------------------------------------------------------------
//
// Folgende Codes sind fuer getDriverInfo() definiert:
//
//    -
//
// Folgende Codes sind fuer executeDriverCode() definiert:
//
//    -
//
// cBase
//  +--cCuBase
//      +--cCuOCI
//
// ===========================================================================

class cCuOCI : public cCuBase {

public:
   cCuOCI(cdbCursor& cu);
   ~cCuOCI();

   cString getLastErrorMsg() const;

protected:
   bool onOpen(cdbDatabase& db);
   bool onClose();

   int onGetSize(const cdbCursor::check& ind) const;
   bool onIsNull(const cdbCursor::check& ind) const;
   short onGetDate(const cdbCursor::date& var, cdbCursor::DTFIELD field) const;
   short onGetTime(const cdbCursor::time& var, cdbCursor::DTFIELD field) const;
   short onGetTimeStamp(const cdbCursor::timestamp& var, cdbCursor::DTFIELD field) const;

   void onSetSize(cdbCursor::check& ind, int size) const;
   void onSetNull(cdbCursor::check& ind) const;
   void onSetDate(cdbCursor::date& var, cdbCursor::DTFIELD field, short value) const;
   void onSetTime(cdbCursor::time& var, cdbCursor::DTFIELD field, short value) const;
   void onSetTimeStamp(cdbCursor::timestamp& var, cdbCursor::DTFIELD field, short value) const;

   void onDefineColumn(int n, const DEF_PAR& par);
   void onBindColumn(int n, const DEF_PAR& par);
   void onBindName(cString name, const DEF_PAR& par);
   void onUndefineColumn(int n);
   void onUnbindColumn(int n);

   void onSetLockMode(cdbCursor::CONCURRENCY concur);
   void onCompile(SQL::STMT sql_str, SQL::STMT sql_new);
   void onExec(SQL::STMT sql_str, SQL::STMT sql_new);
   bool onFetch();
   void onHalt();
   void onCloseCursor();

   int onGetKeyCount() const { return -1; }
   int onGetKeyField(int n) const { return -n; }
   int onGetNameField() const { return -1; }
   int onGetDescrField() const { return -1; }

   //void onExecMulti(int count);
   //bool onFetchMulti(int count);

   bool onGetDescr(int n, char *name, short *db_size, cdbCursor::VARTYPE *type, short *width);
   long onGetRowCount();

   int onGetFieldCount();
   cString onGetFieldName(int n);
   cString onGetFieldLabel(int n);
   cString onGetFieldBaseSchema(int n);
   cString onGetFieldBaseTable(int n);
   cString onGetFieldBaseColumn(int n);
   cdbCursor::VARTYPE onGetFieldType(int n);
   int onGetFieldSize(int n);
   int onGetFieldDigits(int n);
   bool onGetFieldNullable(int n);
   bool onGetFieldFixedLength(int n);

   int onGetParamCount();
   cdbCursor::VARTYPE onGetParamType(int n);
   int onGetParamSize(int n);
   int onGetParamDigits(int n);
   bool onGetParamNullable(int n);
   bool onGetParamFixedLength(int n);

   int VarTypeC(cdbCursor::VARTYPE t);
   int VarTypeSQL(cdbCursor::VARTYPE t);

   long onGetDriverInfo(int code) const;
   int onExecuteDriverCode(int code, void *data);

private:
   int tid;
   Cda_Def cda;

};


// Implementierung cCuOCI
// ===========================================================================

cCuOCI::cCuOCI(cdbCursor& cu) :
   cCuBase(cu)
{
   tid = -1;
}

cCuOCI::~cCuOCI()
{
   // ...
}

bool cCuOCI::onOpen(cdbDatabase& db)
{
   tid = -1;

   if ( oopen(&cda, &db->lda, NULL, -1, /*area_size = */-1, NULL, 0) )
      throw cdbErr(cda.rc);

   return true;
}

bool cCuOCI::onClose()
{
   return !oclose(&cda);
}

void cCuOCI::onDefineColumn(int n, const DEF_PAR& par)
{
   bool err = !odefin(&cda, n+1, (ub1*)par.buf, len, VarTypeC(par.type),
      -1, *((short *)par.ind), NULL, -1, -1, NULL, (ub2*)NULL);
   if ( err )
      throw cdbErr(cdbErr::errDefineColFailed, cda.rc);
}

void cCuOCI::onBindColumn(int n, const DEF_PAR& par)
{
   bool err = !obndrn(&cda, n+1, par.buf, par.len, VarTypeC(par.type),
      -1, *((short *)par.ind), NULL, -1, -1);
   if ( err )
      throw cdbErr(cdbErr::errBindParamFailed, cda.rc);
}

void cCuOCI::onBindName(cString name, const DEF_PAR& par)
{
   bool err = obndrv(&cda, (text*)name,-1, par.buf, par.len, VarTypeC(par.type),
      -1, ORASHIT, NULL, -1, -1);
   if ( err )
      throw cdbErr(cdbErr::errBindParamFailed, cda.rc);
}

void cCuOCI::onUndefineColumn(int n)
{
   // ?????
}

void cCuOCI::onUnbindColumn(int n)
{
   // ?????
}

void cCuOCI::onSetLockMode(cdbCursor::CONCURRENCY concur)
{
   // ?????
}

void cCuOCI::onCompile(SQL::STMT sql_str, SQL::STMT sql_new)
{
   if ( osql3( &cda, (text*)sql_new, -1) ) {
      char buffer[100];
      int start = max(0,cda.peo-40);
      cdbErr(cda.rc).String(buffer);
      fprintf(stderr, "cursor::Compile: %s\n", buffer);
      fprintf(stderr, "%.80s\n", sql_new+start);
      fprintf(stderr, "%*s^^\n", cda.peo-start, "");
   }
}

void cCuOCI::onExec(SQL::STMT sql_str, SQL::STMT sql_new)
{
   if ( !sql_str.isEmpty() && !sql_new.isEmpty() )
      onCompile(sql_str, sql_new);

   bool err = oexec(&cda) && tid;

   if ( !tid )
      throw cdbErr(cdbErr::errResourceTimeout, cda.rc);

   if ( err )
      throw cdbErr(cdbErr::errGeneralDbError, cda.rc);
}

bool cCuOCI::onFetch()
{
   bool err = ofetch(&cda) && tid;

   if ( !tid )
      throw cdbErr(cdbErr::errResourceTimeout, cda.rc);

   if ( err ) {
      throw cdbErr(cdbErr::errGeneralDbError, cda.rc);

   return !err;
}

void cCuOCI::onHalt()
{
   #ifdef __OS2__
      DosEnterCritSec();
   #endif

   bool must_break = tid > 0;
   tid = 0; // Zeigt Timeout an

   #ifdef __OS2__
      DosExitCritSec();
   #endif

   if ( must_break )
      obreak(&db_ptr->lda);
}

void cCuOCI::onCloseCursor()
{
}

// void cCuOCI::onExecMulti(int n)
// {
//    bool err = oexn(&cda,n,0) && tid;
//
//    if ( !tid )
//       throw cdbErr(cdbErr::errResourceTimeout, cda.rc);
//
//    if ( err ) {
//       throw cdbErr(cdbErr::errGeneralDbError, cda.rc);
// }
//
// bool cCuOCI::onFetchMulti(int n)
// {
//    bool err = ofen(&cda,n) && tid;
//
//    if ( !tid )
//       throw cdbErr(cdbErr::errResourceTimeout, cda.rc);
//
//    if ( err ) {
//       throw cdbErr(cdbErr::errGeneralDbError, cda.rc);
//
//    return !err;
// }

bool cCuOCI::onGetDescr(int n, char *name, short *db_size, cdbCursor::VARTYPE *type, short *width)
{
   short nl = 30;
   short my_db_type;

   if ( !db_type )
      db_type = &my_db_type;

   if (odsc(&cda, n+1, db_size, NULL, NULL, db_type, name, &nl, width)) {
      Raise(cda.rc);
      return false;
   } else {
      if (name) name[nl]='\0';
      if (db_size) {
         if (nl > *db_size) *db_size = nl;
      }
      return true;
   }

   return false;
}

int cCuOCI::onGetFieldCount()
{
   int field_count = 0;

   for ( ; onGetDescr(field_count, NULL, NULL, NULL, NULL) ; ++field_count )
      ;

   return field_count;
}

cString cCuOCI::onGetFieldName(int n)
{
   // ???
   return cString();
}

cString cCuOCI::onGetFieldLabel(int n)
{
   // ???
   return cString();
}

cString cCuOCI::onGetFieldBaseSchema(int n)
{
   // ???
   return cString();
}

cString cCuOCI::onGetFieldBaseTable(int n)
{
   // ???
   return cString();
}

cString cCuOCI::onGetFieldBaseColumn(int n)
{
   // ???
   return cString();
}

cdbCursor::VARTYPE cCuOCI::onGetFieldType(int n)
{
   // ???
   return cdbCursor::tString;
}

int cCuOCI::onGetFieldSize(int n)
{
   // ???
   return 0;
}

int cCuOCI::onGetFieldDigits(int n)
{
   // ???
   return 0;
}

bool cCuOCI::onGetFieldNullable(int n)
{
   // ???
   return false;
}

bool cCuOCI::onGetFieldFixedLength(int n)
{
   // ???
   return false;
}

int cCuOCI::onGetParamCount()
{
   // ???
   return 0;
}

cdbCursor::VARTYPE cCuOCI::onGetParamType(int n)
{
   // ???
   return cdbCursor::tString;
}

int cCuOCI::onGetParamSize(int n)
{
   // ???
   return 0;
}

int cCuOCI::onGetParamDigits(int n)
{
   // ???
   return 0;
}

bool cCuOCI::onGetParamNullable(int n)
{
   // ???
   return false;
}

bool cCuOCI::onGetParamFixedLength(int n)
{
   // ???
   return false;
}


long cCuOCI::onGetRowCount()
{
   return cda.rpc;
}

int cCuOCI::VarTypeC(cdbCursor::VARTYPE t)
{
   switch ( t ) {
    case cdbCursor::tShort:  return SQLT_INT;
    case cdbCursor::tLong:   return SQLT_INT;
    case cdbCursor::tFloat:  return SQLT_FLT;
    case cdbCursor::tDouble: return SQLT_FLT;
    case cdbCursor::tChar:   return SQLT_STR;
    case cdbCursor::tString: return SQLT_STR;
   }

   return 0;
}

int cCuOCI::VarTypeSQL(cdbCursor::VARTYPE t)
{
   return VarTypeC(t);
}

int cCuOCI::onGetSize(const cdbCursor::check& ind) const
{
   // ...
}

void cCuOCI::onSetSize(cdbCursor::check& ind, int size) const
{
   // ...
}

bool cCuOCI::onIsNull(const cdbCursor::check& ind) const
{
   // ...
}

void cCuOCI::onSetNull(cdbCursor::check& ind) const
{
   // ...
}

short cCuOCI::onGetDate(const cdbCursor::date& var, cdbCursor::DTFIELD field) const
{
   // ...
}

short cCuOCI::onGetTime(const cdbCursor::time& var, cdbCursor::DTFIELD field) const
{
   // ...
}

short cCuOCI::onGetTimeStamp(const cdbCursor::timestamp& var, cdbCursor::DTFIELD field) const
{
   // ...
}

void cCuOCI::onSetDate(cdbCursor::date& var, cdbCursor::DTFIELD field, short value) const
{
   // ...
}

void cCuOCI::onSetTime(cdbCursor::time& var, cdbCursor::DTFIELD field, short value) const
{
   // ...
}

void cCuOCI::onSetTimeStamp(cdbCursor::timestamp& var, cdbCursor::DTFIELD field, short value) const
{
   // ...
}

char *cCuOCI::getLastErrorMsg(char *buffer, int buf_size) const
{
   char buffer[512];
   oerhms((Lda_Def*)&lda, last_err, (text*)buffer, sizeof buffer);
   return buffer;
}

long cCuOCI::onGetDriverInfo(int code) const
{
   // ???
   return 0;
}

int cCuOCI::onExecuteDriverCode(int code, void *data)
{
   // ???
   return 0;
}

#endif /*__OCI__*/




#if defined(__ODBC__)

// ===========================================================================
// Definition cCuODBC
// ---------------------------------------------------------------------------
//
// Folgende Codes sind fuer getDriverInfo() definiert:
//
//    1 = Statement-Handle (hstmt)
//
// Folgende Codes sind fuer executeDriverCode() definiert:
//
//    1 = Vorbereiten einer Dictionary-Abfrage ueber SQLColumns
//        data zeigt auf ein Array aus 3 cString's
//          data[0] = Name des Schemas (leer = aktuelles Schema)
//          data[1] = Pattern fuer Tabellenname (leer = alle Tabellen, "%")
//          data[2] = Pattern fuer Spaltenname (leer = alle Spalten, "%")
//    2 = Vorbereiten einer Dictionary-Abfrage ueber SQLColumnPrivileges
//          (nicht implementiert)
//    3 = Vorbereiten einer Dictionary-Abfrage ueber SQLTables
//        data zeigt auf ein Array aus 2 cString's
//          data[0] = Name des Schemas (leer = aktuelles Schema)
//          data[1] = Pattern fuer Tabellenname (leer = alle Tabellen, "%")
//    4 = Vorbereiten einer Dictionary-Abfrage ueber SQLTablePrivileges
//          (nicht implementiert)
//    5 = Vorbereiten einer Dictionary-Abfrage ueber SQLPrimaryKeys
//        data zeigt auf ein Array aus 2 cString's
//          data[0] = Name des Schemas (leer = aktuelles Schema)
//          data[1] = Name der Tabelle (Kein Pattern erlaubt!)
//    6 = Vorbereiten einer Dictionary-Abfrage ueber SQLForeignKeys
//          (nicht implementiert)
//    7 = Vorbereiten einer Dictionary-Abfrage ueber SQLSpecialColumns
//        data zeigt auf ein Array aus 5 cString's
//          data[0] = Name des Schemas (leer = aktuelles Schema)
//          data[1] = Name der Tabelle (Kein Pattern erlaubt!)
//          data[2] = Spaltentyp ("BEST_ROWID" oder "ROWVER")
//          data[3] = Scope ("CURROW" oder "TRANSACTION" oder "SESSION")
//          data[4] = Nullable ("NO_NULLS" oder "NULLABLE")
//
// cBase
//  +--cCuBase
//      +--cCuODBC
//
// ===========================================================================

class cCuODBC : public cCuBase {

public:
   cCuODBC(cdbCursor& cu);
   ~cCuODBC();

   cString getLastErrorMsg() const;

protected:
   bool onOpen(cdbDatabase& db);
   bool onClose();

   int onGetSize(const cdbCursor::check& ind) const;
   bool onIsNull(const cdbCursor::check& ind) const;
   short onGetDate(const cdbCursor::date& var, cdbCursor::DTFIELD field) const;
   short onGetTime(const cdbCursor::time& var, cdbCursor::DTFIELD field) const;
   short onGetTimeStamp(const cdbCursor::timestamp& var, cdbCursor::DTFIELD field) const;

   void onSetSize(cdbCursor::check& ind, int size) const;
   void onSetNull(cdbCursor::check& ind) const;
   void onSetDate(cdbCursor::date& var, cdbCursor::DTFIELD field, short value) const;
   void onSetTime(cdbCursor::time& var, cdbCursor::DTFIELD field, short value) const;
   void onSetTimeStamp(cdbCursor::timestamp& var, cdbCursor::DTFIELD field, short value) const;

   void onDefineColumn(int n, const DEF_PAR& par);
   void onBindColumn(int n, const DEF_PAR& par);
   void onBindName(cString name, const DEF_PAR& par);
   void onUndefineColumn(int n);
   void onUnbindColumn(int n);

   void onSetLockMode(cdbCursor::CONCURRENCY concur);
   void onCompile(SQL::STMT sql_str, SQL::STMT sql_new);
   void onExec(SQL::STMT sql_str, SQL::STMT sql_new);
   bool onFetch();
   void onHalt();
   void onCloseCursor();

   int onGetKeyCount() const { return -1; }
   int onGetKeyField(int n) const { return -n; }
   int onGetNameField() const { return -1; }
   int onGetDescrField() const { return -1; }

   // void onExecMulti(int count);
   // bool onFetchMulti(int count);

   bool onGetDescr(int n, char *name, short *db_size, cdbCursor::VARTYPE *type, short *width);
   long onGetRowCount();

   int onGetFieldCount();
   cString onGetFieldName(int n);
   cString onGetFieldLabel(int n);
   cString onGetFieldBaseSchema(int n);
   cString onGetFieldBaseTable(int n);
   cString onGetFieldBaseColumn(int n);
   cdbCursor::VARTYPE onGetFieldType(int n);
   int onGetFieldSize(int n);
   int onGetFieldDigits(int n);
   bool onGetFieldNullable(int n);
   bool onGetFieldFixedLength(int n);

   int onGetParamCount();
   cdbCursor::VARTYPE onGetParamType(int n);
   int onGetParamSize(int n);
   int onGetParamDigits(int n);
   bool onGetParamNullable(int n);
   bool onGetParamFixedLength(int n);

   SWORD VarTypeC(cdbCursor::VARTYPE t);
   SWORD VarTypeSQL(cdbCursor::VARTYPE t);

   long onGetDriverInfo(int code) const;
   int onExecuteDriverCode(int code, void *data);

private:
   HSTMT hstmt;
   cdbCursor::CONCURRENCY lock_mode;
   enum STATE { notPrepared, selectPrepared, selectRunning, otherPrepared } state;
   void DbgSqlDb(const char *func, const char *sql, HSTMT hstmt, RETCODE rc);

   void queryFieldInfo(int n);
   void queryParamInfo(int n);
   cString queryFieldAttribute(int n, int attr);


   // Multi-Fetch
   // ===========

   struct COLUMN {
      COLUMN() { max_elem_size = 0; odbc_buf_adr = 0; odbc_ind_adr = 0; }
      ~COLUMN() { delete[] odbc_buf_adr; delete[] odbc_ind_adr; }
      void *appl_buf_adr;        // Zeiger auf Datenpuffer der Applikation
      SQLINTEGER *appl_ind_adr;  // Zeiger auf Indikator-Element der Applikation
      SQLPOINTER odbc_buf_adr;   // Zeiger auf ODBC-Multi-Datenpuffer
      SQLINTEGER *odbc_ind_adr;  // Zeiger auf Multi-Puffer mit ODBC-Indikatoren
      size_t max_elem_size;      // Maximale Groesse eines Elementes im ODBC-Datenpuffer
      size_t act_elem_size;      // Aktuelle Groesse eines Elementes im ODBC-Datenpuffer
   };

   typedef cArray<COLUMN, const COLUMN&> COLUMN_ARRAY;
   COLUMN_ARRAY multi_columns;
   SQLUINTEGER num_rows_fetched, row_fetch_idx;
   SQLUSMALLINT *row_status_array;


   // Treiberspezifische Befehle
   // ==========================

   bool special_exec;
   bool execSQLColumns(cString names[3]);
   bool execSQLTables(cString names[2]);
   bool execSQLPrimaryKeys(cString names[2]);
   bool execSQLSpecialColumns(cString names[5]);

   // Aufloesen gequoteter Bezeichner im SQL-String
   SQL::STMT adaptSqlString(SQL::STMT stmt);

};


// Implementierung cCuODBC
// ===========================================================================

cCuODBC::cCuODBC(cdbCursor& cu) :
   cCuBase(cu)
{
   hstmt = SQL_NULL_HSTMT;
   state = notPrepared;
   row_status_array = 0;
   special_exec = false;
   lock_mode = cdbCursor::cReadOnly;
}

cCuODBC::~cCuODBC()
{
   delete[] row_status_array;
}

bool cCuODBC::onOpen(cdbDatabase& db)
{
   state = notPrepared;

   SQLRETURN rc = SQLAllocStmt((HDBC)db.getDriverInfo(2), (HSTMT FAR *)&hstmt);
   DbgDb("ODBC: AllocStmt(%08lx), status = %d", hstmt, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errAllocCursorFailed, *cu);

   if ( mustPrefetch() ) {
      delete[] row_status_array;
      row_status_array = new0 SQLUSMALLINT[getPrefetchCount()];
      #if ODBCVER > 0x0250
         SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN, SQL_IS_UINTEGER);
         SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_ARRAY_SIZE, (void *)getPrefetchCount(), SQL_IS_UINTEGER);
         SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_STATUS_PTR, row_status_array, SQL_IS_POINTER);
         SQLSetStmtAttr(hstmt, SQL_ATTR_ROWS_FETCHED_PTR, &num_rows_fetched, SQL_IS_POINTER);
      #else
         SQLSetStmtOption(hstmt, SQL_BIND_TYPE, SQL_BIND_BY_COLUMN);
         SQLSetStmtOption(hstmt, SQL_ROWSET_SIZE, getPrefetchCount());
      #endif
   }

   return true;
}

bool cCuODBC::onClose()
{
   SQLRETURN rc = SQLFreeStmt(hstmt, SQL_DROP);
   DbgDb("ODBC: FreeStmt(%08lx, SQL_DROP), status = %d", hstmt, rc);

   hstmt = SQL_NULL_HSTMT;
   return true;
}

void cCuODBC::onDefineColumn(int n, const DEF_PAR& par)
{
   SQLPOINTER buf_adr;
   SQLINTEGER *ind_adr;

   if ( mustPrefetch() ) {

      if ( n >= multi_columns.getSize() )
         multi_columns.setSize(n + 1);

      COLUMN& act_col = multi_columns[n];

      if ( act_col.max_elem_size < par.len ) {
         delete[] act_col.odbc_buf_adr;
         delete[] act_col.odbc_ind_adr;
         act_col.odbc_buf_adr = new0 char[getPrefetchCount() * par.len];
         act_col.odbc_ind_adr = new0 SQLINTEGER[getPrefetchCount()];
         act_col.max_elem_size = par.len;
      }

      buf_adr = act_col.odbc_buf_adr;
      ind_adr = act_col.odbc_ind_adr;

      act_col.appl_buf_adr = par.buf;
      act_col.appl_ind_adr = (SQLINTEGER*)par.ind;
      act_col.act_elem_size = par.len;

   } else {

      buf_adr = par.buf;
      ind_adr = (SQLINTEGER*)par.ind;

   }

   SQLRETURN rc = SQLBindCol(hstmt, SQLUSMALLINT(n+1), VarTypeC(par.type),
      buf_adr, par.len, ind_adr);
   DbgDb("ODBC: BindCol(%08lx, %d, %d, %08lx, %d, %08lx), status = %d",
      hstmt, n+1, VarTypeC(par.type), buf_adr, par.len, ind_adr, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errDefineColFailed, *cu);
}

void cCuODBC::onBindColumn(int n, const DEF_PAR& par)
{
   int len = par.len;

   // Bei String-Typen darf nicht die Pufferlaenge uebergeben werden,
   // sondern die Nutzdatenlaenge (und die ist 1 weniger als par.len!!!)
   // Oracle faellt sonst (manchmal) auf die Schnauze. (SQL-Server nicht!?!)

   if ( par.type == cdbCursor::tChar || par.type == cdbCursor::tString )
      len--;

   SQLRETURN rc = SQLSetParam(hstmt, SQLUSMALLINT(n+1), VarTypeC(par.type),
      VarTypeSQL(par.type), len, 0, par.buf, (SQLINTEGER *)par.ind);
   DbgDb("ODBC: SetParam(%08lx, %d, %d, %d, %d, 0, %08lx, %08lx), status = %d",
      hstmt, n+1, VarTypeC(par.type), VarTypeSQL(par.type), len, par.buf, par.ind, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errBindParamFailed, *cu);
}

void cCuODBC::onBindName(cString name, const DEF_PAR& /*par*/)
{
   if ( !__ECL_ASSERT1__(name.isEmpty()) ) {
      DbgError("Bind parameter '%s' not possible in ODBC", (const char *)name);
      throw cdbErr(cdbErr::errBindParamFailed);
   }
}

void cCuODBC::onUndefineColumn(int n)
{
   if ( mustPrefetch() ) {
      if ( n < multi_columns.getSize() ) {
         COLUMN& act_col = multi_columns[n];
         delete[] act_col.odbc_buf_adr; act_col.odbc_buf_adr = 0;
         delete[] act_col.odbc_ind_adr; act_col.odbc_ind_adr = 0;
         act_col.appl_buf_adr = 0;
         act_col.appl_ind_adr = 0;
         act_col.max_elem_size = 0;
         act_col.act_elem_size = 0;
      }
   }

   SQLRETURN rc = SQLBindCol(hstmt, SQLUSMALLINT(n+1), 0, NULL, 0, NULL);
   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errDefineColFailed, *cu);
}

void cCuODBC::onUnbindColumn(int n)
{
   SQLRETURN rc = SQLSetParam(hstmt, SQLUSMALLINT(n+1), 0, 0, 0, 0, NULL, NULL);
   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errBindParamFailed, *cu);
}

void cCuODBC::onSetLockMode(cdbCursor::CONCURRENCY concur)
{
   SQLRETURN rc;
   SQLUINTEGER odbc_concur = concur == cdbCursor::cLocked ? SQL_CONCUR_LOCK : SQL_CONCUR_READ_ONLY;

   #if ODBCVER > 0x0250
      rc = SQLSetStmtAttr(hstmt, SQL_ATTR_CONCURRENCY, (SQLPOINTER)odbc_concur , SQL_IS_UINTEGER);
   #else
      rc = SQLSetStmtOption(hstmt, SQL_CONCURRENCY, odbc_concur);
   #endif

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errSetLockModeFailed, *cu);

   lock_mode = concur;
}

void cCuODBC::onCompile(SQL::STMT /*sql_str*/, SQL::STMT sql_new)
{
   SQLRETURN rc;
   special_exec = false;

   if ( state != notPrepared ) {
      rc = SQLFreeStmt(hstmt, SQL_CLOSE);
      DbgDb("ODBC: FreeStmt(%08lx, SQL_CLOSE), status = %d", hstmt, rc);
      state = notPrepared;
   }

   // Syntaktische Anpassungen fuer Positioned Update/Delete:

   cString sql_stmt = sql_new;

   if ( lock_mode == cdbCursor::cLocked ) {
      if ( sql_new.getType() == SQL::STMT_SELECT ) {
         SQL::SELECT select = SQL::SELECT(sql_new);
         SQL::FIELDS columns = SQL::SELECT(sql_new).getFields();
         sql_stmt += " FOR UPDATE OF " + cString(columns);
         if ( db->getName() == "Oracle" )
            sql_stmt += " NOWAIT";
      }
   }

   sql_stmt = adaptSqlString(sql_stmt);
   DbgSql(sql_stmt);

   if ( getDebugMask() & dbgSqlRaw ) {
      char native[1024];
      SQLINTEGER len;

      rc = SQLNativeSql((HDBC)getDatabase()->getDriverInfo(2),
         (SQLCHAR*)(const char *)sql_stmt, SQL_NTS,
         (SQLCHAR*)native, sizeof native, &len);

      if ( rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO )
         DbgSqlRaw(native);
   }

   rc = SQLPrepare(hstmt, (SQLCHAR *)(const char *)sql_stmt, SQL_NTS);
   DbgSqlDb("Prepare", sql_stmt, hstmt, rc);

   if ( rc == SQL_ERROR || rc == SQL_SUCCESS_WITH_INFO ) {
      // Fehleraufbereitung, evtl. Anzeige der Fehlerposition
      // DbgError("cdbCursor::Compile: Error");
   }

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errCompileFailed, *cu);

   state = cString(sql_new).compareNoCase("SELECT", 6) == 0 ?
      selectPrepared : otherPrepared;
}

void cCuODBC::onExec(SQL::STMT sql_str, SQL::STMT sql_new)
{
   SQLRETURN rc = SQL_SUCCESS;

   // Indikatoren aus NULL-Werten setzen, wo noetig
   bind_vars.doBindVars();

   if ( !cString(sql_new).isEmpty() ) {
      sql_new = adaptSqlString(sql_new);
      DbgSql(cString(sql_new));
      if ( getDebugMask() & dbgSqlRaw ) {
         char native[1024];
         SQLINTEGER len;
         rc = SQLNativeSql((HDBC)getDatabase()->getDriverInfo(2),
            (SQLCHAR*)(const char *)cString(sql_new), SQL_NTS,
            (SQLCHAR*)native, sizeof native, &len);
         if ( rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO )
            DbgSqlRaw(native);
      }
   }

   if ( getDebugMask() & (dbgSql|dbgSqlRaw) ) {
      cString params = getLastParams();
      if ( !params.isEmpty() )
         cBase::DbgOut(0, "   PARAMETER(S): %s", (const char *)params);
   }

   if ( state == selectRunning || !cString(sql_new).isEmpty() && state != notPrepared ) {
      rc = SQLFreeStmt(hstmt, SQL_CLOSE);
      DbgDb("ODBC: FreeStmt(%08lx, SQL_CLOSE), status = %d", hstmt, rc);
      state = state == selectRunning ?
         selectPrepared : notPrepared;
   }

   if ( lock_mode == cdbCursor::cLocked ) {
      #if ODBCVER > 0x0250
         rc = SQLSetStmtAttr(hstmt, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)20, SQL_IS_UINTEGER);
      #else
         rc = SQLSetStmtOption(hstmt, SQL_QUERY_TIMEOUT, 20);
      #endif
   }

   if ( !cString(sql_new).isEmpty() ) {
      special_exec = false;
      rc = SQLExecDirect(hstmt, (SQLCHAR *)(const char *)cString(sql_new), SQL_NTS);
      DbgSqlDb("ExecDirect", cString(sql_new), hstmt, rc);
      state = cString(sql_new).compareNoCase("SELECT", 6) == 0 ?
         selectPrepared : otherPrepared;
   } else if ( !special_exec ) {
      rc = SQLExecute(hstmt);
      DbgDb("ODBC: Exec(%08lx), status = %d", hstmt, rc);
   }

   if ( rc == SQL_ERROR || rc == SQL_SUCCESS_WITH_INFO ) {
      // Fehleraufbereitung, evtl. Anzeige der Fehlerposition
      // DbgError("cdbCursor::Compile: Error");
   }

   if ( rc == SQL_NEED_DATA )
      throw cdbErr(cdbErr::errBindParamMissing, *cu);
   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errExecFailed, *cu);

   if ( state == selectPrepared )
      state = selectRunning;

   num_rows_fetched = row_fetch_idx = 0;
}

bool cCuODBC::onFetch()
{
   SQLRETURN rc = SQL_SUCCESS;

   if ( mustPrefetch() ) {

      for ( bool success = false ; !success ; ) {

         if ( num_rows_fetched == row_fetch_idx ) {

            num_rows_fetched = 0;

            #if ODBCVER > 0x0250
               rc = SQLFetch(hstmt);
            #else
               rc = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 1, &num_rows_fetched, row_status_array);
            #endif
            DbgDb("ODBC: Fetch(%08lx), status = %d", hstmt, rc);
            //rc = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 0);
            //DbgDb("ODBC: FetchScroll(%08lx,NEXT,0), status = %d", hstmt, rc);

            if ( rc == SQL_NO_DATA_FOUND )
               return false;
            if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
               throw cdbErr(cdbErr::errFetchFailed, *cu);

            row_fetch_idx = 0;

         }

#if ODBCVER > 0x0250
         if ( row_status_array[row_fetch_idx] == SQL_ROW_SUCCESS
           || row_status_array[row_fetch_idx] == SQL_ROW_SUCCESS_WITH_INFO )
#else
         if ( row_status_array[row_fetch_idx] != SQL_ROW_DELETED
           && row_status_array[row_fetch_idx] != SQL_ROW_ERROR )
#endif
         {
            for ( int n = 0 ; n < multi_columns.getSize() ; n++ ) {
               COLUMN& act_col = multi_columns[n];
               if ( act_col.max_elem_size > 0 ) {
                  *act_col.appl_ind_adr = act_col.odbc_ind_adr[row_fetch_idx];
                  memcpy(act_col.appl_buf_adr,
                         ((char *)act_col.odbc_buf_adr) + row_fetch_idx * act_col.act_elem_size,
                         act_col.act_elem_size);
               }
            }
            success = true;
         }

         row_fetch_idx++;
      }

   } else {

      rc = SQLFetch(hstmt);
      DbgDb("ODBC: Fetch(%08lx), status = %d", hstmt, rc);

      if ( rc == SQL_NO_DATA_FOUND )
         return false;
      if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
         throw cdbErr(cdbErr::errFetchFailed, *cu);

   }

   // NULL-Werte aus Indikatoren setzen, wo noetig
   define_vars.doDefineVars();

   return true;
}

void cCuODBC::onHalt()
{
   SQLRETURN rc = SQLCancel(hstmt);
   DbgDb("ODBC: Cancel(%08lx), status = %d", hstmt, rc);
}

void cCuODBC::onCloseCursor()
{
   SQLRETURN rc = SQLFreeStmt(hstmt, SQL_CLOSE);
   DbgDb("ODBC: FreeStmt(%08lx, SQL_CLOSE), status = %d", hstmt, rc);
}

// void cCuODBC::onExecMulti(int /*n*/)
// {
//    DbgError("ExecMulti not yet implemented");
// }
//
// bool cCuODBC::onFetchMulti(int /*n*/)
// {
//    DbgError("FetchMulti not yet implemented");
//    return false;
// }

bool cCuODBC::onGetDescr(int /*n*/, char * /*name*/, short * /*db_size*/, cdbCursor::VARTYPE * /*type*/, short * /*width*/)
{
   DbgError("GetDescr not yet implemented");
   return false;
}


// Eigenschaften der Ergebnisspalten
// =================================

void cCuODBC::queryFieldInfo(int n)
{
   char name[64] = "";
   SQLSMALLINT name_len = 0, type = 0, digits = 0, nullable = 0;
   SQLUINTEGER size = 0;

   SQLRETURN rc = SQLDescribeCol(hstmt, SQLUSMALLINT(n+1), (SQLCHAR*)name, sizeof name,
      &name_len, &type, &size, &digits, &nullable);
   DbgDb("ODBC: FieldInfo(%08lx) = %s, type = %d, size = %d, digits = %d, status = %d",
      hstmt, name, type, size, digits, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   cdbCursor::VARTYPE field_type = cdbCursor::tString;
   field_info[n].flags |= ffIsFixedLength;

   switch ( type ) {
   case SQL_SMALLINT:   field_type = cdbCursor::tShort;       break;
   case SQL_INTEGER:    field_type = cdbCursor::tLong;        break;
   case SQL_BIGINT:     field_type = cdbCursor::tRowid;       break;
   case SQL_DATE:       field_type = cdbCursor::tDate;        break;
   case SQL_TIME:       field_type = cdbCursor::tTime;        break;
   case SQL_TIMESTAMP:  field_type = cdbCursor::tTimeStamp;   break;
   case SQL_BIT:        field_type = cdbCursor::tChar;        break;
   case SQL_FLOAT:
      field_type = cdbCursor::tFloat;
      if ( digits == 0 )
         digits = -1;
      break;
   case SQL_REAL:
   case SQL_DOUBLE:
      field_type = cdbCursor::tDouble;
      if ( digits == 0 )
         digits = -1;
      break;
   case SQL_VARCHAR:
      field_type = cdbCursor::tString;
      field_info[n].flags &= ~ffIsFixedLength;
      break;
   case SQL_CHAR:
      if ( size > 1 ) {
         field_type = cdbCursor::tString;
      } else {
         field_type = cdbCursor::tChar;
      }
      break;
   case SQL_DECIMAL:
   case SQL_NUMERIC:
      if ( digits > 0 || size > 9 ) {
         field_type = cdbCursor::tDouble;
      } else if ( size > 4 ) {
         field_type = cdbCursor::tLong;
      } else {
         field_type = cdbCursor::tShort;
      }
      break;
   default:
      __ECL_ASSERT2__(0, ("cCuODBC: Unexpected ODBC data type %d", type));
      break;
   }

   #define __No_Objects_Greater_4096__
   #ifdef __No_Objects_Greater_4096__
      // Large DB objects (like MEMO or BLOB) not yet supported!
      // Workaround: Cut down the size of these fields!
      if ( size > 4096 )
         size = 4096;
   #endif

   #define __Compatibility_With_ECL_store__
   #ifdef __Compatibility_With_ECL_store__
      // Force compatibility of datatypes with ECL/store
      // (No short and float types available)
      switch ( field_type ) {
      case cdbCursor::tShort: field_type = cdbCursor::tLong; break;
      case cdbCursor::tFloat: field_type = cdbCursor::tDouble; break;
      }
   #endif

   field_info[n].name = name;
   field_info[n].type = field_type;
   field_info[n].size = size;
   field_info[n].digits = digits;

   if ( nullable == SQL_NULLABLE ) {
      field_info[n].flags |= ffIsNullable;
   } else {
      field_info[n].flags &= ~ffIsNullable;
   }

   field_info[n].flags |=
      ffValidName | ffValidType | ffValidSize
    | ffValidDigits | ffValidNullable;
}

cString cCuODBC::queryFieldAttribute(int n, int attr)
{
   char value[256];
   SQLSMALLINT value_len;

   #if ODBCVER > 0x0250
      SQLRETURN rc = SQLColAttribute(hstmt, SQLSMALLINT(n+1), SQLSMALLINT(attr),
         value, sizeof value, &value_len, 0);
   #else
      SQLRETURN rc = SQLColAttributes(hstmt, SQLSMALLINT(n+1), SQLSMALLINT(attr),
         value, sizeof value, &value_len, 0);
   #endif
   DbgDb("ODBC: FieldAttribute(%08lx, %d) = '%s', status = %d", hstmt, attr, value, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   return value;
}

int cCuODBC::onGetFieldCount()
{
   SQLSMALLINT count = 0;
   SQLRETURN rc = SQLNumResultCols(hstmt, &count);
   DbgDb("ODBC: FieldCount(%08lx) = %d, status = %d", hstmt, count, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   return count;
}

cString cCuODBC::onGetFieldName(int n)
{
   queryFieldInfo(n);
   return field_info[n].name;
}

cString cCuODBC::onGetFieldLabel(int n)
{
   #if ODBCVER > 0x0250
      return queryFieldAttribute(n, SQL_DESC_LABEL);
   #else
      return queryFieldAttribute(n, SQL_COLUMN_LABEL);
   #endif
}

cString cCuODBC::onGetFieldBaseSchema(int n)
{
   #if ODBCVER > 0x0250
      return queryFieldAttribute(n, SQL_DESC_SCHEMA_NAME);
   #else
      return queryFieldAttribute(n, SQL_COLUMN_OWNER_NAME);
   #endif
}

cString cCuODBC::onGetFieldBaseTable(int n)
{
   #if ODBCVER > 0x0250
      return queryFieldAttribute(n, SQL_DESC_TABLE_NAME /*SQL_DESC_BASE_TABLE_NAME*/);
   #else
      return queryFieldAttribute(n, SQL_COLUMN_TABLE_NAME);
   #endif
}

cString cCuODBC::onGetFieldBaseColumn(int n)
{
   #if ODBCVER > 0x0250
      return queryFieldAttribute(n, SQL_DESC_BASE_COLUMN_NAME);
   #else
      return queryFieldAttribute(n, SQL_COLUMN_NAME);
   #endif
}

cdbCursor::VARTYPE cCuODBC::onGetFieldType(int n)
{
   queryFieldInfo(n);
   return field_info[n].type;
}

int cCuODBC::onGetFieldSize(int n)
{
   queryFieldInfo(n);
   return field_info[n].size;
}

int cCuODBC::onGetFieldDigits(int n)
{
   queryFieldInfo(n);
   return field_info[n].digits;
}

bool cCuODBC::onGetFieldNullable(int n)
{
   queryFieldInfo(n);
   return !!(field_info[n].flags & ffIsNullable);
}

bool cCuODBC::onGetFieldFixedLength(int n)
{
   queryFieldInfo(n);
   return !!(field_info[n].flags & ffIsFixedLength);
}


// Eigenschaften der Parameter
// ===========================

void cCuODBC::queryParamInfo(int n)
{
   SQLSMALLINT type = 0, digits = 0, nullable = 0;
   SQLUINTEGER size = 0;

   SQLRETURN rc = SQLDescribeParam(hstmt, SQLUSMALLINT(n+1),
      &type, &size, &digits, &nullable);
   DbgDb("ODBC: ParamInfo(%08lx) = %d, type = %d, size = %d, digits = %d, status = %d",
      hstmt, n+1, type, size, digits, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   cdbCursor::VARTYPE param_type = cdbCursor::tString;
   param_info[n].flags |= pfIsFixedLength;

   switch ( type ) {
   case SQL_SMALLINT:   param_type = cdbCursor::tShort;       break;
   case SQL_INTEGER:    param_type = cdbCursor::tLong;        break;
   case SQL_FLOAT:      param_type = cdbCursor::tFloat;       break;
   case SQL_REAL:       param_type = cdbCursor::tDouble;      break;
   case SQL_DOUBLE:     param_type = cdbCursor::tDouble;      break;
   case SQL_BIGINT:     param_type = cdbCursor::tRowid;       break;
   case SQL_DATE:       param_type = cdbCursor::tDate;        break;
   case SQL_TIME:       param_type = cdbCursor::tTime;        break;
   case SQL_TIMESTAMP:  param_type = cdbCursor::tTimeStamp;   break;
   case SQL_BIT:        param_type = cdbCursor::tChar;        break;
   case SQL_VARCHAR:
      param_type = cdbCursor::tString;
      param_info[n].flags &= ~pfIsFixedLength;
      break;
   case SQL_CHAR:
      if ( size > 1 ) {
         param_type = cdbCursor::tString;
      } else {
         param_type = cdbCursor::tChar;
      }
      break;
   case SQL_DECIMAL:
   case SQL_NUMERIC:
      if ( digits > 0 || size > 9 ) {
         param_type = cdbCursor::tDouble;
      } else if ( size > 4 ) {
         param_type = cdbCursor::tLong;
      } else {
         param_type = cdbCursor::tShort;
      }
      break;
   default:
      __ECL_ASSERT2__(0, ("cCuODBC: Unexpected ODBC data type %d", type));
      break;
   }

   #define __No_Objects_Greater_4096__
   #ifdef __No_Objects_Greater_4096__
      // Large DB objects (like MEMO or BLOB) not yet supported!
      // Workaround: Cut down the size of these params!
      if ( size > 4096 )
         size = 4096;
   #endif

   #define __Compatibility_With_ECL_store__
   #ifdef __Compatibility_With_ECL_store__
      // Force compatibility of datatypes with ECL/store
      // (No short and float types available)
      switch ( param_type ) {
      case cdbCursor::tShort: param_type = cdbCursor::tLong; break;
      case cdbCursor::tFloat: param_type = cdbCursor::tDouble; break;
      }
   #endif

   param_info[n].type = param_type;
   param_info[n].size = size;
   param_info[n].digits = digits;

   if ( nullable == SQL_NULLABLE ) {
      param_info[n].flags |= pfIsNullable;
   } else {
      param_info[n].flags &= ~pfIsNullable;
   }

   param_info[n].flags |=
      pfValidType | pfValidSize
    | pfValidDigits | pfValidNullable;
}

int cCuODBC::onGetParamCount()
{
   SQLSMALLINT count = 0;
   SQLRETURN rc = SQLNumParams(hstmt, &count);
   DbgDb("ODBC: ParamCount(%08lx) = %d, status = %d", hstmt, count, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   return count;
}

cdbCursor::VARTYPE cCuODBC::onGetParamType(int n)
{
   queryParamInfo(n);
   return param_info[n].type;
}

int cCuODBC::onGetParamSize(int n)
{
   queryParamInfo(n);
   return param_info[n].size;
}

int cCuODBC::onGetParamDigits(int n)
{
   queryParamInfo(n);
   return param_info[n].digits;
}

bool cCuODBC::onGetParamNullable(int n)
{
   queryParamInfo(n);
   return !!(param_info[n].flags & pfIsNullable);
}

bool cCuODBC::onGetParamFixedLength(int n)
{
   queryParamInfo(n);
   return !!(param_info[n].flags & pfIsFixedLength);
}

long cCuODBC::onGetRowCount()
{
   SDWORD count = 0;
   SQLRETURN rc = SQLRowCount(hstmt, &count);
   DbgDb("ODBC: RowCount(%08lx) = %ld, status = %d", hstmt, count, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   return (long)count;
}

SWORD cCuODBC::VarTypeC(cdbCursor::VARTYPE t)
{
   switch ( t ) {
   case cdbCursor::tShort:     return SQL_C_SHORT;
   case cdbCursor::tLong:      return SQL_C_LONG;
   case cdbCursor::tFloat:     return SQL_C_FLOAT;
   case cdbCursor::tDouble:    return SQL_C_DOUBLE;
   case cdbCursor::tChar:      return SQL_C_CHAR;
   case cdbCursor::tString:    return SQL_C_CHAR;
   case cdbCursor::tRowid:     return SQL_C_ULONG;
   case cdbCursor::tDate:      return SQL_C_DATE;
   case cdbCursor::tTime:      return SQL_C_TIME;
   case cdbCursor::tTimeStamp: return SQL_C_TIMESTAMP;
   }

   return 0;
}

SWORD cCuODBC::VarTypeSQL(cdbCursor::VARTYPE t)
{
   switch ( t ) {
   case cdbCursor::tShort:     return SQL_SMALLINT;
   case cdbCursor::tLong:      return SQL_INTEGER;
   case cdbCursor::tFloat:     return SQL_FLOAT;
   case cdbCursor::tDouble:    return SQL_DOUBLE;
   case cdbCursor::tChar:      return SQL_CHAR;
   case cdbCursor::tString:    return SQL_VARCHAR;
   case cdbCursor::tRowid:     return SQL_BIGINT;
   case cdbCursor::tDate:      return SQL_DATE;
   case cdbCursor::tTime:      return SQL_TIME;
   case cdbCursor::tTimeStamp: return SQL_TIMESTAMP;
   }

   return SQL_CHAR;
}

int cCuODBC::onGetSize(const cdbCursor::check& ind) const
{
   SQLINTEGER sql_size = *((SQLINTEGER *)(void *)&ind);

   switch ( sql_size ) {
   case SQL_NTS:        return -2;
   case SQL_NULL_DATA:  return -1;
   }

   return sql_size;
}

void cCuODBC::onSetSize(cdbCursor::check& ind, int size) const
{
   SQLINTEGER sql_size = size;

   switch ( size ) {
   case -2:    sql_size = SQL_NTS; break;
   case -1:    sql_size = SQL_NULL_DATA; break;
   }

   *((SQLINTEGER *)(void *)&ind) = sql_size;
}

bool cCuODBC::onIsNull(const cdbCursor::check& ind) const
{
   return *((SDWORD *)(void *)&ind) == SQL_NULL_DATA;
}

void cCuODBC::onSetNull(cdbCursor::check& ind) const
{
   *((SDWORD *)(void *)&ind) = SQL_NULL_DATA;
}

short cCuODBC::onGetDate(const cdbCursor::date& var, cdbCursor::DTFIELD field) const
{
   switch ( field ) {
    case cdbCursor::fYear:   return ((DATE_STRUCT *)(void *)&var)->year;
    case cdbCursor::fMonth:  return ((DATE_STRUCT *)(void *)&var)->month;
    case cdbCursor::fDay:    return ((DATE_STRUCT *)(void *)&var)->day;
   }

   return -1;
}

short cCuODBC::onGetTime(const cdbCursor::time& var, cdbCursor::DTFIELD field) const
{
   switch ( field ) {
    case cdbCursor::fHour:   return ((TIME_STRUCT *)(void *)&var)->hour;
    case cdbCursor::fMinute: return ((TIME_STRUCT *)(void *)&var)->minute;
    case cdbCursor::fSecond: return ((TIME_STRUCT *)(void *)&var)->second;
   }

   return -1;
}

short cCuODBC::onGetTimeStamp(const cdbCursor::timestamp& var, cdbCursor::DTFIELD field) const
{
   switch ( field ) {
    case cdbCursor::fYear:   return ((TIMESTAMP_STRUCT *)(void *)&var)->year;
    case cdbCursor::fMonth:  return ((TIMESTAMP_STRUCT *)(void *)&var)->month;
    case cdbCursor::fDay:    return ((TIMESTAMP_STRUCT *)(void *)&var)->day;
    case cdbCursor::fHour:   return ((TIMESTAMP_STRUCT *)(void *)&var)->hour;
    case cdbCursor::fMinute: return ((TIMESTAMP_STRUCT *)(void *)&var)->minute;
    case cdbCursor::fSecond: return ((TIMESTAMP_STRUCT *)(void *)&var)->second;
   }

   return -1;
}

void cCuODBC::onSetDate(cdbCursor::date& var, cdbCursor::DTFIELD field, short value) const
{
   switch ( field ) {
    case cdbCursor::fYear:   ((DATE_STRUCT *)(void *)&var)->year = value; break;
    case cdbCursor::fMonth:  ((DATE_STRUCT *)(void *)&var)->month = value; break;
    case cdbCursor::fDay:    ((DATE_STRUCT *)(void *)&var)->day = value; break;
   }
}

void cCuODBC::onSetTime(cdbCursor::time& var, cdbCursor::DTFIELD field, short value) const
{
   switch ( field ) {
    case cdbCursor::fHour:   ((TIME_STRUCT *)(void *)&var)->hour = value; break;
    case cdbCursor::fMinute: ((TIME_STRUCT *)(void *)&var)->minute = value; break;
    case cdbCursor::fSecond: ((TIME_STRUCT *)(void *)&var)->second = value; break;
   }
}

void cCuODBC::onSetTimeStamp(cdbCursor::timestamp& var, cdbCursor::DTFIELD field, short value) const
{
   switch ( field ) {
    case cdbCursor::fYear:   ((TIMESTAMP_STRUCT *)(void *)&var)->year = value; break;
    case cdbCursor::fMonth:  ((TIMESTAMP_STRUCT *)(void *)&var)->month = value; break;
    case cdbCursor::fDay:    ((TIMESTAMP_STRUCT *)(void *)&var)->day = value; break;
    case cdbCursor::fHour:   ((TIMESTAMP_STRUCT *)(void *)&var)->hour = value; break;
    case cdbCursor::fMinute: ((TIMESTAMP_STRUCT *)(void *)&var)->minute = value; break;
    case cdbCursor::fSecond: ((TIMESTAMP_STRUCT *)(void *)&var)->second = value; break;
   }

   // Wichtig! 'fraction'-Feld auf definierten Wert setzen, damit Vergleiche
   // innerhalb der Datenbank moeglich sind.
   ((TIMESTAMP_STRUCT *)(void *)&var)->fraction = 0;
}

cString cCuODBC::getLastErrorMsg() const
{
   cString buffer;
   UCHAR stat[SQL_SQLSTATE_SIZE+1];
   UCHAR msg[SQL_MAX_MESSAGE_LENGTH+1];
   bool abort = false;
   SDWORD native_error = 0;

   do {

      *stat = *msg = '\0';

      SWORD msg_len = SQL_MAX_MESSAGE_LENGTH - 1;
      SQLRETURN rc = SQLError(NULL, NULL, hstmt,
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
      case SQL_INVALID_HANDLE:      buffer += "Invalid handle in SQLError"; abort = true; break;
      }

   } while ( !abort );

   return buffer;
}

void cCuODBC::DbgSqlDb(const char *func, const char *sql, HSTMT hstmt, RETCODE rc)
{
   if ( getDebugMask() & dbgDb ) {
      char buf[32]; strxcpy(buf, sql, sizeof buf);
      DbgDb("ODBC: %s(%08lx,'%s%s'), status = %d",
         func, hstmt, buf, strlen(sql)>strlen(buf) ? "..." : "", rc);
   }
}

long cCuODBC::onGetDriverInfo(int code) const
{
   switch ( code ) {
   case 1: return (long)hstmt;
   }
   return -1;
}

int cCuODBC::onExecuteDriverCode(int code, void *data)
{
   switch ( code ) {
   case 1:  return (int)execSQLColumns((cString*)data);
   case 2:  return 0;
   case 3:  return (int)execSQLTables((cString*)data);
   case 4:  return 0;
   case 5:  return (int)execSQLPrimaryKeys((cString*)data);
   case 6:  return 0;
   case 7:  return (int)execSQLSpecialColumns((cString *)data);
   }
   return 0;
}

bool cCuODBC::execSQLColumns(cString names[3])
{
   SQLRETURN rc;
   cString schemas = names[0];
   cString tables = names[1].isEmpty() ? "%" : names[1];
   cString fields = names[2].isEmpty() ? "%" : names[2];

   if ( state != notPrepared ) {
      rc = SQLFreeStmt(hstmt, SQL_CLOSE);
      DbgDb("ODBC: FreeStmt(%08lx, SQL_CLOSE), status = %d", hstmt, rc);
      state = notPrepared;
   }

   rc = SQLColumns(hstmt, NULL, 0,
      schemas.isEmpty() ? NULL : (SQLCHAR *)(const char *)schemas, SQLSMALLINT(schemas.getLength()),
      (SQLCHAR *)(const char *)tables, SQLSMALLINT(tables.getLength()),
      (SQLCHAR *)(const char *)fields, SQLSMALLINT(fields.getLength()));
   DbgDb("ODBC: Columns(%08lx,'%s','%s','%s'), status = %d", hstmt,
      Nvl(schemas,""), Nvl(tables,""), Nvl(fields,""), rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   special_exec = true;
   state = selectPrepared;

   return true;
}

bool cCuODBC::execSQLTables(cString names[2])
{
   SQLRETURN rc;
   cString schemas = names[0];
   cString tables = names[1].isEmpty() ? "%" : names[1];
   cString types = "TABLE,VIEW";

   if ( state != notPrepared ) {
      rc = SQLFreeStmt(hstmt, SQL_CLOSE);
      DbgDb("ODBC: FreeStmt(%08lx, SQL_CLOSE), status = %d", hstmt, rc);
      state = notPrepared;
   }

   rc = SQLTables(hstmt, NULL, 0,
      schemas.isEmpty() ? NULL : (SQLCHAR *)(const char *)schemas, SQLSMALLINT(schemas.getLength()),
      (SQLCHAR *)(const char *)tables, SQLSMALLINT(tables.getLength()),
      (SQLCHAR *)(const char *)types, SQLSMALLINT(types.getLength()));
   DbgDb("ODBC: Tables(%08lx,'%s','%s','%s'), status = %d", hstmt,
      Nvl(schemas,""), Nvl(tables,""), Nvl(types,""), rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   special_exec = true;
   state = selectPrepared;

   return true;
}

bool cCuODBC::execSQLPrimaryKeys(cString names[2])
{
   SQLRETURN rc;
   cString schema = names[0];
   cString table = names[1];

   if ( state != notPrepared ) {
      rc = SQLFreeStmt(hstmt, SQL_CLOSE);
      DbgDb("ODBC: FreeStmt(%08lx, SQL_CLOSE), status = %d", hstmt, rc);
      state = notPrepared;
   }

   rc = SQLPrimaryKeys(hstmt, NULL, 0,
      schema.isEmpty() ? NULL : (SQLCHAR *)(const char *)schema, SQLSMALLINT(schema.getLength()),
      (SQLCHAR *)(const char *)table, SQLSMALLINT(table.getLength()));
   DbgDb("ODBC: PrimaryKeys(%08lx,'%s','%s'), status = %d", hstmt,
      Nvl(schema,""), Nvl(table,""), rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   special_exec = true;
   state = selectPrepared;

   return true;
}

bool cCuODBC::execSQLSpecialColumns(cString names[5])
{
   SQLRETURN rc;
   cString schema = names[0];
   cString table = names[1];
   SQLSMALLINT id_type =  SQLSMALLINT((names[2] == "ROWVER") ? SQL_ROWVER : SQL_BEST_ROWID);
   SQLSMALLINT scope =    SQLSMALLINT((names[3] == "CURROW") ? SQL_SCOPE_CURROW :
                                      (names[3] == "SESSION") ? SQL_SCOPE_SESSION : SQL_SCOPE_TRANSACTION);
   SQLSMALLINT nullable = SQLSMALLINT((names[4] == "NO_NULLS") ? SQL_NO_NULLS : SQL_NULLABLE);

   if ( state != notPrepared ) {
      rc = SQLFreeStmt(hstmt, SQL_CLOSE);
      DbgDb("ODBC: FreeStmt(%08lx, SQL_CLOSE), status = %d", hstmt, rc);
      state = notPrepared;
   }

   rc = SQLSpecialColumns(hstmt, id_type, NULL, 0,
      schema.isEmpty() ? NULL : (SQLCHAR *)(const char *)schema, SQLSMALLINT(schema.getLength()),
      (SQLCHAR *)(const char *)table, SQLSMALLINT(table.getLength()),
      scope, nullable);
   DbgDb("ODBC: SpecialColumns(%08lx,%d,'%s','%s',%d,%d), status = %d", hstmt, id_type,
      Nvl(schema,""), Nvl(table,""), scope, nullable, rc);

   if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
      throw cdbErr(cdbErr::errGeneralDbError, *cu);

   special_exec = true;
   state = selectPrepared;

   return true;
}

static void ReplaceFunc(cString& str, const char *func_name, const char *prefix, const char *suffix)
{
   int pos;

   while ( (pos = str.getPosNoCase(func_name)) >= 0 ) {
      int pos2 = str.getPos("(", pos);
      int pos3 = str.getPos(")", "'\"({", pos2 + 1);
      str = str.getLeft(pos)
          + prefix + str.getSubstr(pos2+1, pos3-1) + suffix
          + str.getMid(pos3 + 1);
   }
}

static void ReplaceOracleFunc(cString& str, const cString& func_name, const char *prefix, const char *suffix)
{
   int pos;

   while ( (pos = str.getPosNoCase(func_name)) >= 0 ) {
      int pos2 = str.getPos("(", pos);
      int pos3 = str.getPos(")", "'\"({", pos2 + 1);
      cString arg = str.getSubstr(pos2+1, pos3-1);
      if ( func_name.compareNoCase("$CAST") == 0 ) {
         cString exp = arg.getPart(0, "'\"({", ",");
         cString typ = arg.getPart(1, "'\"({", ",");
         if ( typ.compareNoCase("CHAR", 4) == 0
           || typ.compareNoCase("VARCHAR", 7) == 0 )
         {
            arg = "TO_CHAR(" + exp + ")";
         } else {
            arg = "###UNKNOWN_CAST_TYPE='" + typ + "'###";
         }
      } else {
         arg = "{UNKNOWN_ORACLE_FUNCTION='" + func_name + "'}";
      }
      str = str.getLeft(pos)
          + prefix + arg + suffix
          + str.getMid(pos3 + 1);
   }
}

static void ReplaceSQL92Func(cString& str, const cString& func_name, const char *prefix, const char *suffix)
{
   int pos;

   while ( (pos = str.getPosNoCase(func_name)) >= 0 ) {
      int pos2 = str.getPos("(", pos);
      int pos3 = str.getPos(")", "'\"({", pos2 + 1);
      cString arg = str.getSubstr(pos2+1, pos3-1);
      if ( func_name.compareNoCase("$CAST") == 0 ) {
         cString exp = arg.getPart(0, "'\"({", ",");
         cString typ = arg.getPart(1, "'\"({", ",");
         arg = exp + " AS " + typ;
      } else {
         arg = "{UNKNOWN_ORACLE_FUNCTION='" + func_name + "'}";
      }
      str = str.getLeft(pos)
          + prefix + arg + suffix
          + str.getMid(pos3 + 1);
   }
}

SQL::STMT cCuODBC::adaptSqlString(SQL::STMT stmt)
{
   cString str = stmt;
   int pos = 0;

   while ( (pos = str.getPos("[", "'\"", pos)) >= 0 ) {
      int pos2 = str.getPos("]", "'\"", pos);
      if ( pos2 < 0 )
         return str;
      str[pos] = str[pos2] = char(db->getDriverInfo(3));
      pos = pos2 + 1;
   }

   // Joins
   ReplaceFunc(str, "$JOIN",    "{oj ",         "}");
   // System functions
   ReplaceFunc(str, "$NVL",     "{fn IFNULL(",  ")}");
   // String functions
   ReplaceFunc(str, "$CONCAT",  "{fn CONCAT(",  ")}");
   ReplaceFunc(str, "$RTRIM",   "{fn RTRIM(",   ")}");
   ReplaceFunc(str, "$LEFT",    "{fn LEFT(",    ")}");
   ReplaceFunc(str, "$UCASE",   "{fn UCASE(",   ")}");
   // Math functions
   ReplaceFunc(str, "$ROUND",   "{fn ROUND(",   ")}");
   // Date functions
   ReplaceFunc(str, "$YEAR",    "{fn YEAR(",    ")}");
   ReplaceFunc(str, "$MONTH",   "{fn MONTH(",   ")}");
   ReplaceFunc(str, "$CURDATE", "{fn CURDATE(", ")}");

   // Database Specific

   if ( db->getName() == "Oracle" ) {
      ReplaceOracleFunc(str, "$CAST", "", "");
   } else {
      ReplaceSQL92Func(str, "$CAST", "CAST(", ")");
   }

   return str;
}

#endif /*__ODBC__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbCursor
// ---------------------------------------------------------------------------
//
// Anmerkung zu den Datentypen:
//
//  - Die Groesse der C-Typen 'check', 'rowid', 'date', 'time' und 'timestamp'
//    ist so gewaehlt, dass ausreichend Platz fuer alle unterstuetzten
//    Datenbanken zur Verfuegung steht.
//
//  - Auf den Inhalt des 'check'-Typs kann nur ueber getSize(), setSize(),
//    isNull() und setNull() zugegriffen werden.
//
//  - Auf den Inhalt der 'date', 'time' und 'timestamp'-Typen kann nur ueber
//    die get()- und set()-Methoden zugegriffen werden.
//
//  - Auf den Inhalt des 'rowid'-Typs kann nicht zugegriffen werden, da ihm
//    keine datenbankunabhaengige Bedeutung zugeordnet werden kann.
//
// cBase
//  +--cdbCursor
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbCursor : public cBase {
   friend class cdbErr;

public:
   cdbCursor(cdbDatabase& db, int prefetch_count = 1);
   cdbCursor(const cdbCursor& other, int prefetch_count = -1);
   ~cdbCursor();


   // Cursor-Typen
   // ============

   struct check { long unspecific; };
   struct rowid { char unspecific[18]; };
   struct date { char unspecific[6]; };
   struct time { char unspecific[6]; };
   struct timestamp { char unspecific[16]; };

   enum VARTYPE {       // C-Typen:
      tShort,           // short
      tLong,            // long
      tFloat,           // float
      tDouble,          // double
      tChar,            // char
      tString,          // char[]
      tRowid,           // cdbCursor::rowid
      tDate,            // cdbCursor::date
      tTime,            // cdbCursor::time
      tTimeStamp        // cdbCursor::timestamp
   };

   enum DTFIELD {
      fYear,            // Jahr (0..9999)
      fMonth,           // Monat (1..12)
      fDay,             // Tag (1..31)
      fHour,            // Stunde (0..23)
      fMinute,          // Minute (0..59)
      fSecond           // Sekunde (0..59)
   };

   // Groesseninformation aus check-Variable ermitteln
   // (Sonderwerte: -1 = NULL, -2 = nullterminierter String)
   int getSize(const check& ind) const;
   // Groessenformation in check-Variable setzen
   // (Sonderwerte: -1 = NULL, -2 = nullterminierter String)
   void setSize(check& ind, int size) const;

   // NULL-Zustand aus check-Variable ermitteln
   bool isNull(const check& ind) const;
   // NULL-Zustand in check-Variable setzen
   void setNull(check& ind) const;

   // Komponente aus date-Struktur einzeln abfragen
   short get(const date& var, DTFIELD field) const;
   // Komponente aus time-Struktur einzeln abfragen
   short get(const time& var, DTFIELD field) const;
   // Komponente aus timestamp-Struktur einzeln abfragen
   short get(const timestamp& var, DTFIELD field) const;
   // date-Struktur im time_t-Format abfragen
   time_t get(const date& var, time_t& time) const;
   // time-Struktur im time_t-Format abfragen
   time_t get(const time& var, time_t& time) const;
   // timestamp-Struktur im time_t-Format abfragen
   time_t get(const timestamp& var, time_t& time) const;
   // date-Struktur im cDate-Format abfragen
   cDate get(const date& var) const;
   // time-Struktur im cTime-Format abfragen
   cTime get(const time& var) const;
   // timestamp-Struktur im cDateTime-Format abfragen
   cDateTime get(const timestamp& var) const;

   // Komponente in date-Struktur einzeln setzen
   void set(date& var, DTFIELD field, short value) const;
   // Komponente in time-Struktur einzeln setzen
   void set(time& var, DTFIELD field, short value) const;
   // Komponente in timestamp-Struktur einzeln setzen
   void set(timestamp& var, DTFIELD field, short value) const;
   // date-Struktur ueber time_t-Variable setzen
   void set(date& var, time_t time) const;
   // time-Struktur ueber time_t-Variable setzen
   void set(time& var, time_t time) const;
   // timestamp-Struktur ueber time_t-Variable setzen
   void set(timestamp& var, time_t time) const;
   // date-Struktur ueber cDate-Variable setzen
   void set(date& var, cDate date) const;
   // time-Struktur ueber cTime-Variable setzen
   void set(time& var, cTime time) const;
   // timestamp-Struktur ueber cDateTime-Variable setzen
   void set(timestamp& var, cDateTime datetime) const;


   // Ausfuehrungskontrolle
   // =====================

   enum CONCURRENCY {
      cReadOnly,        // Nur lesen (default)
      cLocked           // Sperren
   };

   // Locking-Modus setzen
   void setLockMode(CONCURRENCY concur);
   // SQL-Anweisung vorbereiten (vor dem Binden von Variablen)
   void compile(SQL::STMT sql_str);
   // SQL-Anweisung ausfuehren (nach dem Binden von Variablen)
   void exec();
   // SQL-Anweisung direkt ausfuehren (ohne gebundene Variablen)
   void exec(SQL::STMT sql_str);
   // (Naechste) Zeile der Ergebnismenge abfragen
   bool fetch();
   // Ausfuehrung der SQL-Anweisung unterbrechen
   void halt();
   // Aktuelle Verarbeitung (u.U. vorzeitig) beenden
   void close();

   // Zugrundeliegende Datenbank ermitteln
   cdbDatabase *getDB() const;
   // Zugrundeliegende SQL-Anweisung ermitteln
   SQL::STMT getSQL() const;


   // Schluesselfelder
   // ================
   // Mit Hilfe dieser Funktionen kann erfragt werden, welche Kombination
   // von Ergebnisspalten einen eindeutigen Schluessel bildet. Kann diese
   // Eigenschaft nicht von der Datenbank erfragt werden, gibt das System
   // die ersten N Ergebnisspalten als Schluessel zurueck, wobei N
   // folgendermassen bestimmt wird:
   //
   //  - Enthaelt das SQL::STMT keinen PK-Hint, wird N = 1
   //  - Enthaelt das SQL::STMT einen "PK=<x>"-Hint, wird N=<x>
   //
   // Zudem koennen zwei spezifische Spalten fuer Bedeutungen "Name" und
   // "Beschreibung" erfragt werden

   // Ermittelt die Anzahl Ergebnisspalten, die einen eindeutigen Schluessel bilden
   int getKeyCount() const;
   // Ermittelt die Feldnummer der n-ten Schluesselspalte
   int getKeyField(int n) const;
   // Ermittelt die Feldnummer der Namensspalte
   int getNameField() const;
   // Ermittelt die Feldnummer der Beschreibungsspalte
   int getDescrField() const;


   // Eigenschaften der Ergebnisspalten
   // =================================
   // Diese Eigenschaften stehen fruehestens nach dem Aufruf von exec()
   // zur Verfuegung. Die Ergebnisse werden bis zum naechsten Aufruf von
   // exec() gecached, koennen also ohne Zusatzaufwand beliebig oft
   // abgefragt werden.

   // Anzahl Ergebnisspalten (= Felder) erfragen
   int getFieldCount() const;
   // Feldname erfragen
   cString getFieldName(int n) const;
   // Label des Feldes erfragen
   cString getFieldLabel(int n) const;
   // Name des Schemas der Basistabelle erfragen
   cString getFieldBaseSchema(int n) const;
   // Name der Basistabelle erfragen
   cString getFieldBaseTable(int n) const;
   // Name des Feldes in der Basistabelle erfragen
   cString getFieldBaseColumn(int n) const;
   // Variablentyp erfragen
   VARTYPE getFieldType(int n) const;
   // Maximale Spaltenbreite erfragen
   int getFieldSize(int n) const;
   // Anzahl Nachkommastellen erfragen
   int getFieldDigits(int n) const;
   // Erfragen, ob die Spalte NULL-Werte enthalten darf
   bool getFieldNullable(int n) const;
   // Erfragen, ob die Spalte Werte fester Laenge enthaelt
   bool getFieldFixedLength(int n) const;


   // Eigenschaften der Parameter
   // ===========================
   // Diese Eigenschaften stehen fruehestens nach dem Aufruf von exec()
   // zur Verfuegung. Die Ergebnisse werden bis zum naechsten Aufruf von
   // exec() gecached, koennen also ohne Zusatzaufwand beliebig oft
   // abgefragt werden.

   // Anzahl Parameter erfragen
   int getParamCount() const;
   // Variablentyp erfragen
   cdbCursor::VARTYPE getParamType(int n) const;
   // Maximale Spaltenbreite erfragen
   int getParamSize(int n) const;
   // Anzahl Nachkommastellen erfragen
   int getParamDigits(int n) const;
   // Erfragen, ob der Parameter NULL-Werte enthalten darf
   bool getParamNullable(int n) const;
   // Erfragen, ob der Parameter einen Wert fester Laenge enthaelt
   bool getParamFixedLength(int n) const;


   long getRowCount();  // RowCount bei letztem INSERT, UPDATE oder DELETE, oder -1
   bool getDescr(int n, char *name, short *db_size, VARTYPE *db_type, short *width = NULL); // Uraltversion, sterben lassen

   cString getLastErrorMsg() const;
   cString getLastCmd() const;


   // Ergebnisvariablen binden
   // ========================

   // Ergebnisvariable an csVar-Objekt binden
   void define(int n, csVar& var);
   // Ergebnisvariable an csStorage-Objekt binden
   void define(int n, csStorage *var);
   // Ergebnisvariable an herkoemmliche C-Variable binden
   void define(int n, VARTYPE type, void *buf, size_t len, check *ind = NULL);
   // Bindung an Ergebnisvariable aufheben
   void define(int n);

   void define(int n, short& var) { define(n, tShort, &var, sizeof var); }
   void define(int n, long& var) { define(n, tLong, &var, sizeof var); }
   void define(int n, float& var) { define(n, tFloat, &var, sizeof var); }
   void define(int n, double& var) { define(n, tDouble, &var, sizeof var); }
   void define(int n, char *var, size_t len) { define(n, tString, var, len); }
   void define(int n, rowid& var) { define(n, tRowid, &var, sizeof var); }
   void define(int n, date& var) { define(n, tDate, &var, sizeof var); }
   void define(int n, time& var) { define(n, tTime, &var, sizeof var); }
   void define(int n, timestamp& var) { define(n, tTimeStamp, &var, sizeof var); }

   void define(int n, short& var, check& ind) { define(n, tShort, &var, sizeof var, &ind); }
   void define(int n, long& var, check& ind) { define(n, tLong, &var, sizeof var, &ind); }
   void define(int n, float& var, check& ind) { define(n, tFloat, &var, sizeof var, &ind); }
   void define(int n, double& var, check& ind) { define(n, tDouble, &var, sizeof var, &ind); }
   void define(int n, char *var, size_t len, check& ind) { define(n, tString, var, len, &ind); }
   void define(int n, rowid& var, check& ind) { define(n, tRowid, &var, sizeof var, &ind); }
   void define(int n, date& var, check& ind) { define(n, tDate, &var, sizeof var, &ind); }
   void define(int n, time& var, check& ind) { define(n, tTime, &var, sizeof var, &ind); }
   void define(int n, timestamp& var, check& ind) { define(n, tTimeStamp, &var, sizeof var, &ind); }


   // Numerische Parametervariablen binden
   // ====================================

   // Parameter ueber Index an csVar-Objekt binden
   void bind(int n, csVar& var);
   // Parameter ueber Index an csStorage-Objekt binden
   void bind(int n, csStorage *var);
   // Parameter ueber Index an herkoemmliche C-Variable binden
   void bind(int n, VARTYPE type, void *buf, size_t len, check *ind = NULL);
   // Bindung an Index-Parameter aufheben
   void bind(int n);

   void bind(int n, short& var) { bind(n, tShort, &var, sizeof var); }
   void bind(int n, int& var) { bind(n, tLong, &var, sizeof var); }
   void bind(int n, long& var) { bind(n, tLong, &var, sizeof var); }
   void bind(int n, float& var) { bind(n, tFloat, &var, sizeof var); }
   void bind(int n, double& var) { bind(n, tDouble, &var, sizeof var); }
   void bind(int n, char *var, int len) { bind(n, tString, var, len-1); }
   void bind(int n, rowid& var) { bind(n, tRowid, &var, sizeof var); }
   void bind(int n, date& var) { bind(n, tDate, &var, sizeof var); }
   void bind(int n, time& var) { bind(n, tTime, &var, sizeof var); }
   void bind(int n, timestamp& var) { bind(n, tTimeStamp, &var, sizeof var); }

   void bind(int n, short& var, check& ind) { bind(n, tShort, &var, sizeof var, &ind); }
   void bind(int n, int& var, check& ind) { bind(n, tLong, &var, sizeof var, &ind); }
   void bind(int n, long& var, check& ind) { bind(n, tLong, &var, sizeof var, &ind); }
   void bind(int n, float& var, check& ind) { bind(n, tFloat, &var, sizeof var, &ind); }
   void bind(int n, double& var, check& ind) { bind(n, tDouble, &var, sizeof var, &ind); }
   void bind(int n, char *var, int len, check& ind) { bind(n, tString, var, len-1, &ind); }
   void bind(int n, rowid& var, check& ind) { bind(n, tRowid, &var, sizeof var, &ind); }
   void bind(int n, date& var, check& ind) { bind(n, tDate, &var, sizeof var, &ind); }
   void bind(int n, time& var, check& ind) { bind(n, tTime, &var, sizeof var, &ind); }
   void bind(int n, timestamp& var, check& ind) { bind(n, tTimeStamp, &var, sizeof var, &ind); }


   // Symbolische Parametervariablen binden
   // =====================================
   // Sollen Parametervariablen sowohl numerisch als auch per Namen an den
   // selben Cursor gebunden werden, muessen ERST ALLE numerischen Bindungen
   // und DANN die Bindungen per Namen ausgefuehrt werden!!

   // Parameter ueber Name an csVar-Objekt binden
   void bind(cString name, csVar& var);
   // Parameter ueber Name an csStorage-Objekt binden
   void bind(cString name, csStorage *var);
   // Parameter ueber Name an herkoemmliche C-Variable binden
   void bind(cString name, VARTYPE type, void *buf, size_t len, check *ind = NULL);

   void bind(cString name, short& var) { bind(name, tShort, &var, sizeof var); }
   void bind(cString name, int& var) { bind(name, tLong, &var, sizeof var); }
   void bind(cString name, long& var) { bind(name, tLong, &var, sizeof var); }
   void bind(cString name, float& var) { bind(name, tFloat, &var, sizeof var); }
   void bind(cString name, double& var) { bind(name, tDouble, &var, sizeof var); }
   void bind(cString name, char *var, int len) { bind(name, tString, var, len); }
   void bind(cString name, rowid& rid) { bind(name, tRowid, &rid, sizeof rid); }
   void bind(cString name, date& rid) { bind(name, tDate, &rid, sizeof rid); }
   void bind(cString name, time& rid) { bind(name, tTime, &rid, sizeof rid); }
   void bind(cString name, timestamp& rid) { bind(name, tTimeStamp, &rid, sizeof rid); }


   // Statische Parametervariablen binden
   // ===================================

   // Statische Parametervariable binden (ansprechbar ueber $##X, wobei 0 <= X <= 9)
   static void bindStatic(int n, const char *buf);
   // Wert einer statisch gebundenen Parametervariablen ermitteln
   static const char *getStaticBound(int n);


   // Treiber-Internas
   // ================

   // Treiberspezifische Informationen ermitteln
   long getDriverInfo(int code) const;
   // Treiberspezifische Routinen ausfuehren
   int executeDriverCode(int code, void *data) const;


private:
   void *cu_base;

};

#endif /*__INTERFACE__*/


// Implementierung cdbCursor
// ===========================================================================

cdbCursor::cdbCursor(cdbDatabase& db, int prefetch_count)
{
   cCuBase *base = NULL;

   switch ( db.getType() ) {
      #if defined(__DUMMY__)
         case cdbDatabase::DUMMY: base = new0 cCuDummy(*this); break;
      #endif
      #if defined(__OCI__)
         case cdbDatabase::OCI:   base = new0 cCuOCI(*this); break;
      #endif
      #if defined(__BTI__)
         case cdbDatabase::BTI:   /* not supported */ break;
      #endif
      #if defined(__ODBC__)
         case cdbDatabase::ODBC:  base = new0 cCuODBC(*this); break;
      #endif
   }

   if ( !base )
      throw cdbErr(cdbErr::errDbTypeNotSupported);

   base->open(db, prefetch_count);
   cu_base = base;
}

cdbCursor::cdbCursor(const cdbCursor& other, int prefetch_count)
{
   cCuBase *base = NULL;
   cCuBase *other_base = (cCuBase *)other.cu_base;

   if ( other_base && other_base->getDatabase() ) {
      switch ( other_base->getDatabase()->getType() ) {
         #if defined(__DUMMY__)
            case cdbDatabase::DUMMY: base = new0 cCuDummy(*this); break;
         #endif
         #if defined(__OCI__)
            case cdbDatabase::OCI:   base = new0 cCuOCI(*this); break;
         #endif
         #if defined(__BTI__)
            case cdbDatabase::BTI:   /* not supported */ break;
         #endif
         #if defined(__ODBC__)
            case cdbDatabase::ODBC:  base = new0 cCuODBC(*this); break;
         #endif
      }
   }

   if ( !base )
      throw cdbErr(cdbErr::errDbTypeNotSupported);

   base->open(*other_base->getDatabase(),
      prefetch_count > 0 ? prefetch_count : other_base->getPrefetchCount());
   cu_base = base;
}

cdbCursor::~cdbCursor()
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->close();
   delete base;
}


// Cursor-Typen
// ============

int cdbCursor::getSize(const check& ind) const
{
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getSize(ind) : -1;
}

void cdbCursor::setSize(check& ind, int size) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->setSize(ind, size);
}

bool cdbCursor::isNull(const check& ind) const
{
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->isNull(ind) : false;
}

void cdbCursor::setNull(check& ind) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->setNull(ind);
}

short cdbCursor::get(const date& var, DTFIELD field) const
{
   cCuBase *base = (cCuBase *)cu_base;
   return short(base ? base->getDate(var, field) : -1);
}

short cdbCursor::get(const time& var, DTFIELD field) const
{
   cCuBase *base = (cCuBase *)cu_base;
   return short(base ? base->getTime(var, field) : -1);
}

short cdbCursor::get(const timestamp& var, DTFIELD field) const
{
   cCuBase *base = (cCuBase *)cu_base;
   return short(base ? base->getTimeStamp(var, field) : -1);
}

time_t cdbCursor::get(const date& var, time_t& time) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return time = 0;

   struct tm ts;
   ts.tm_sec = ts.tm_min = ts.tm_hour = 0;
   ts.tm_isdst = -1;
   ts.tm_mday = base->getDate(var, cdbCursor::fDay);
   ts.tm_mon  = base->getDate(var, cdbCursor::fMonth) - 1;
   ts.tm_year = base->getDate(var, cdbCursor::fYear) - 1900;
   return time = mktime(&ts);
}

time_t cdbCursor::get(const time& var, time_t& time) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return time = 0;

   struct tm ts;
   ts.tm_mday = ts.tm_mon = ts.tm_year = 0;
   ts.tm_isdst = -1;
   ts.tm_sec  = base->getTime(var, cdbCursor::fSecond);
   ts.tm_min  = base->getTime(var, cdbCursor::fMinute);
   ts.tm_hour = base->getTime(var, cdbCursor::fHour);
   return time = mktime(&ts);
}

time_t cdbCursor::get(const timestamp& var, time_t& time) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return time = 0;

   struct tm ts;
   ts.tm_isdst = -1;
   ts.tm_mday = base->getTimeStamp(var, cdbCursor::fDay);
   ts.tm_mon  = base->getTimeStamp(var, cdbCursor::fMonth) - 1;
   ts.tm_year = base->getTimeStamp(var, cdbCursor::fYear) - 1900;
   ts.tm_sec  = base->getTimeStamp(var, cdbCursor::fSecond);
   ts.tm_min  = base->getTimeStamp(var, cdbCursor::fMinute);
   ts.tm_hour = base->getTimeStamp(var, cdbCursor::fHour);
   return time = mktime(&ts);
}

cDate cdbCursor::get(const date& var) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return cDate();

   return cDate(
      base->getDate(var, cdbCursor::fYear),
      base->getDate(var, cdbCursor::fMonth),
      base->getDate(var, cdbCursor::fDay));
}

cTime cdbCursor::get(const time& var) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return cTime();

   return cTime(
      base->getTime(var, cdbCursor::fHour),
      base->getTime(var, cdbCursor::fMinute),
      base->getTime(var, cdbCursor::fSecond));
}

cDateTime cdbCursor::get(const timestamp& var) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return cDateTime();

   return cDateTime(
      base->getTimeStamp(var, cdbCursor::fYear),
      base->getTimeStamp(var, cdbCursor::fMonth),
      base->getTimeStamp(var, cdbCursor::fDay),
      base->getTimeStamp(var, cdbCursor::fHour),
      base->getTimeStamp(var, cdbCursor::fMinute),
      base->getTimeStamp(var, cdbCursor::fSecond));
}

void cdbCursor::set(date& var, DTFIELD field, short value) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->setDate(var, field, value);
}

void cdbCursor::set(time& var, DTFIELD field, short value) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->setTime(var, field, value);
}

void cdbCursor::set(timestamp& var, DTFIELD field, short value) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->setTimeStamp(var, field, value);
}

void cdbCursor::set(date& var, time_t time) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return;

   struct tm *ts = localtime(&time);
   base->setDate(var, cdbCursor::fDay,   short(ts->tm_mday));
   base->setDate(var, cdbCursor::fMonth, short(ts->tm_mon + 1));
   base->setDate(var, cdbCursor::fYear,  short(ts->tm_year + 1900));
}

void cdbCursor::set(time& var, time_t time) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return;

   struct tm *ts = localtime(&time);
   base->setTime(var, cdbCursor::fSecond, short(ts->tm_sec));
   base->setTime(var, cdbCursor::fMinute, short(ts->tm_min));
   base->setTime(var, cdbCursor::fHour,   short(ts->tm_hour));
}

void cdbCursor::set(timestamp& var, time_t time) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return;

   struct tm *ts = localtime(&time);
   base->setTimeStamp(var, cdbCursor::fDay,    short(ts->tm_mday));
   base->setTimeStamp(var, cdbCursor::fMonth,  short(ts->tm_mon + 1));
   base->setTimeStamp(var, cdbCursor::fYear,   short(ts->tm_year + 1900));
   base->setTimeStamp(var, cdbCursor::fSecond, short(ts->tm_sec));
   base->setTimeStamp(var, cdbCursor::fMinute, short(ts->tm_min));
   base->setTimeStamp(var, cdbCursor::fHour,   short(ts->tm_hour));
}

void cdbCursor::set(date& var, cDate date) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return;

   base->setDate(var, cdbCursor::fDay,   short(date.getDay()));
   base->setDate(var, cdbCursor::fMonth, short(date.getMonth()));
   base->setDate(var, cdbCursor::fYear,  short(date.getYear()));
}

void cdbCursor::set(time& var, cTime time) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return;

   base->setTime(var, cdbCursor::fSecond, short(time.getSec()));
   base->setTime(var, cdbCursor::fMinute, short(time.getMin()));
   base->setTime(var, cdbCursor::fHour,   short(time.getHour()));
}

void cdbCursor::set(timestamp& var, cDateTime datetime) const
{
   cCuBase *base = (cCuBase *)cu_base;
   if ( !base ) return;

   base->setTimeStamp(var, cdbCursor::fDay,    short(datetime.getDay()));
   base->setTimeStamp(var, cdbCursor::fMonth,  short(datetime.getMonth()));
   base->setTimeStamp(var, cdbCursor::fYear,   short(datetime.getYear()));
   base->setTimeStamp(var, cdbCursor::fSecond, short(datetime.getSec()));
   base->setTimeStamp(var, cdbCursor::fMinute, short(datetime.getMin()));
   base->setTimeStamp(var, cdbCursor::fHour,   short(datetime.getHour()));
}


// Ergebnisvariablen binden
// ========================

void cdbCursor::define(int n, csVar& var)
{
   define(n, &var);
}

void cdbCursor::define(int n, csStorage *var)
{
   DbgTrcDb("Cursor: define(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->define(n, var);
}

void cdbCursor::define(int n, VARTYPE type, void *buf, size_t len, check *ind)
{
   DbgTrcDb("Cursor: define(%d, %s, %08lx, %d, %08lx)", n, VarTypeStr[type], buf, len, ind);
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) {
      cCuBase::DEF_PAR par;
      par.type = type;
      par.buf = buf;
      par.len = len;
      par.ind = ind;
      base->define(n, par);
   }
}

void cdbCursor::define(int n)
{
   DbgTrcDb("Cursor: define(%d) - remove", n);
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->define(n);
}


// Numerische Parametervariablen binden
// ====================================

void cdbCursor::bind(int n, csVar& var)
{
   bind(n, &var);
}

void cdbCursor::bind(int n, csStorage *var)
{
   DbgTrcDb("Cursor: bind(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->bind(n, var);
}

void cdbCursor::bind(int n, VARTYPE type, void *buf, size_t len, check *ind)
{
   DbgTrcDb("Cursor: bind(%d, %s, %08lx, %d, %08lx)", n, VarTypeStr[type], buf, len, ind);
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) {
      cCuBase::DEF_PAR par;
      par.type = type;
      par.buf = buf;
      par.len = len;
      par.ind = ind;
      base->bind(n, par);
   }
}

void cdbCursor::bind(int n)
{
   DbgTrcDb("Cursor: bind(%d) - remove", n);
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->bind(n);
}


// Symbolische Parametervariablen binden
// =====================================

void cdbCursor::bind(cString name, csVar& var)
{
   bind(name, &var);
}

void cdbCursor::bind(cString name, csStorage *var)
{
   DbgTrcDb("Cursor: bind(%s)", Nvl(name, "<EMPTY>"));
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->bind(name, var);
}

void cdbCursor::bind(cString name, VARTYPE type, void *buf, size_t len, check *ind)
{
   DbgTrcDb("Cursor: bind(%s, %s, %08lx, %d, %08lx)", Nvl(name, "<EMPTY>"), VarTypeStr[type], buf, len, ind);
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) {
      cCuBase::DEF_PAR par;
      par.type = type;
      par.buf = buf;
      par.len = len;
      par.ind = ind;
      base->bind(name, par);
   }
}


// Statische Parametervariablen binden
// ===================================

void cdbCursor::bindStatic(int n, const char *buf)
{
   DbgTrcDb("Cursor: bindStatic(%d, %s)", n, Nvl(buf, "<NULL>"));
   cCuBase::bindStatic(n, buf);
}

const char * cdbCursor::getStaticBound(int n)
{
   DbgTrcDb("Cursor: getStaticBound(%d)", n);
   return cCuBase::getStaticBound(n);
}


// Ausfuehrungskontrolle
// =====================

void cdbCursor::setLockMode(CONCURRENCY concur)
{
   DbgTrcDb("Cursor: setLockMode(%s)", concur == cLocked ? "LOCKED" : "READONLY");
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->setLockMode(concur);
}

void cdbCursor::compile(SQL::STMT stmt)
{
   cString sql_str = cString(stmt);
   DbgTrcDb("Cursor: compile(%s)", Nvl(sql_str, ""));
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->compile(stmt);
}

void cdbCursor::exec()
{
   DbgTrcDb("Cursor: exec()");
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->exec(cString());
}

void cdbCursor::exec(SQL::STMT sql_str)
{
   DbgTrcDb("Cursor: exec(%s)", Nvl(cString(sql_str), ""));
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->exec(sql_str);
}

bool cdbCursor::fetch()
{
   DbgTrcDb("Cursor: fetch()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->fetch() : false;
}

void cdbCursor::halt()
{
   DbgTrcDb("Cursor: halt()");
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->halt();
}

void cdbCursor::close()
{
   DbgTrcDb("Cursor: close()");
   cCuBase *base = (cCuBase *)cu_base;
   if ( base ) base->closeCursor();
}

cdbDatabase * cdbCursor::getDB() const
{
   DbgTrcDb("Cursor: getDB()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getDatabase() : 0;
}

SQL::STMT cdbCursor::getSQL() const
{
   DbgTrcDb("Cursor: getSQL()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getSQL() : cString();
}

bool cdbCursor::getDescr(int n, char *name, short *db_size, VARTYPE *db_type, short *width)
{
   DbgTrcDb("Cursor: getDescr(%d,%08lx,%08lx,%08lx,%08lx)", n, name, db_size, db_type, width);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getDescr(n, name, db_size, db_type, width) : false;
}

long cdbCursor::getRowCount()
{
   DbgTrcDb("Cursor: getRowCount()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getRowCount() : false;
}


// Schluesselfelder
// ================

int cdbCursor::getKeyCount() const
{
   DbgTrcDb("Cursor: getKeyCount()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getKeyCount() : 0;
}

int cdbCursor::getKeyField(int n) const
{
   DbgTrcDb("Cursor: getKeyField()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getKeyField(n) : 0;
}

int cdbCursor::getNameField() const
{
   DbgTrcDb("Cursor: getNameField()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getNameField() : 0;
}

int cdbCursor::getDescrField() const
{
   DbgTrcDb("Cursor: getDescrField()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getDescrField() : 0;
}


// Eigenschaften der Ergebnisspalten
// =================================

int cdbCursor::getFieldCount() const
{
   DbgTrcDb("Cursor: getFieldCount()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldCount() : 0;
}

cString cdbCursor::getFieldName(int n) const
{
   DbgTrcDb("Cursor: getFieldName(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldName(n) : cString();
}

cString cdbCursor::getFieldLabel(int n) const
{
   DbgTrcDb("Cursor: getFieldLabel(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldLabel(n) : cString();
}

cString cdbCursor::getFieldBaseSchema(int n) const
{
   DbgTrcDb("Cursor: getFieldBaseSchema(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldBaseSchema(n) : cString();
}

cString cdbCursor::getFieldBaseTable(int n) const
{
   DbgTrcDb("Cursor: getFieldBaseTable(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldBaseTable(n) : cString();
}

cString cdbCursor::getFieldBaseColumn(int n) const
{
   DbgTrcDb("Cursor: getFieldBaseColumn(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldBaseColumn(n) : cString();
}

cdbCursor::VARTYPE cdbCursor::getFieldType(int n) const
{
   DbgTrcDb("Cursor: getFieldType(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldType(n) : tString;
}

int cdbCursor::getFieldSize(int n) const
{
   DbgTrcDb("Cursor: getFieldSize(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldSize(n) : 0;
}

int cdbCursor::getFieldDigits(int n) const
{
   DbgTrcDb("Cursor: getFieldDigits(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldDigits(n) : 0;
}

bool cdbCursor::getFieldNullable(int n) const
{
   DbgTrcDb("Cursor: getFieldNullable(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldNullable(n) : false;
}

bool cdbCursor::getFieldFixedLength(int n) const
{
   DbgTrcDb("Cursor: getFieldFixedLength(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getFieldFixedLength(n) : false;
}

// Eigenschaften der Parameter
// ===========================

int cdbCursor::getParamCount() const
{
   DbgTrcDb("Cursor: getParamCount()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getParamCount() : 0;
}

cdbCursor::VARTYPE cdbCursor::getParamType(int n) const
{
   DbgTrcDb("Cursor: getParamType(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getParamType(n) : tString;
}

int cdbCursor::getParamSize(int n) const
{
   DbgTrcDb("Cursor: getParamSize(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getParamSize(n) : 0;
}

int cdbCursor::getParamDigits(int n) const
{
   DbgTrcDb("Cursor: getParamDigits(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getParamDigits(n) : 0;
}

bool cdbCursor::getParamNullable(int n) const
{
   DbgTrcDb("Cursor: getParamNullable(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getParamNullable(n) : false;
}

bool cdbCursor::getParamFixedLength(int n) const
{
   DbgTrcDb("Cursor: getParamFixedLength(%d)", n);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getParamFixedLength(n) : false;
}

// ---

cString cdbCursor::getLastErrorMsg() const
{
   DbgTrcDb("Cursor: getLastErrorMsg()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getLastErrorMsg() : cString();
}

cString cdbCursor::getLastCmd() const
{
   DbgTrcDb("Cursor: getLastCmd()");
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getLastCmd() : cString();
}


// Treiber-Internas
// ================

long cdbCursor::getDriverInfo(int code) const
{
   DbgTrcDb("Cursor: getDriverInfo(%d)", code);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->getDriverInfo(code) : 0;
}

int cdbCursor::executeDriverCode(int code, void *data) const
{
   DbgTrcDb("Cursor: executeDriverCode(%d)", code);
   cCuBase *base = (cCuBase *)cu_base;
   return base ? base->executeDriverCode(code, data) : 0;
}


