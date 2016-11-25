// ===========================================================================
// edb_dictionary.cpp                           ETCL (ET's Tiny Class Library)
// ---------------------------------------------------------------------------
//
// Das Dictionary der Datenbank wird bei Bedarf und nur soweit wie noetig
// eingelesen und bis zum Programmende nicht mehr geloescht. Es wird davon
// ausgegangen, dass sich das DB-Dictionary waehrend eines Programmlaufes
// nicht aendern kann.
//
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdbDictionary                -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#define __DUMMY__

#include "dbi/edb_dictionary.hpp"
#include "dbi/edb_cursor.hpp"
#include "base/eb_array.hpp"
#include "base/eb_sema.hpp"

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
#include "dbi/edb_cursor.hpp"

#endif /*__INTERFACE__*/




// ===========================================================================
// Lokale Klasse cDictBase
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDictBase
//
// ===========================================================================

class cDictBase : public cBase {

public:
   cDictBase();
   virtual ~cDictBase();

   // Referenzzaehler erhoehen
   void attach();
   // Referenzzaehler erniedrigen; beim Nulldurchgang delete this
   void detach();

   bool open(cdbDatabase& db, cString schema);
   bool close();

   cdbDatabase *getDatabase() const
      { return db; }

   cString getSchemaName();

   cString getTableName(int idx);
   int findTable(cString name);
   int getTableCount();

   cString getFieldName(int table_idx, int idx);
   int findField(int table_idx, cString name);
   int getFieldCount(int table_idx);

   cdbDictTable::TABLE_TYPE getTableType(int table_idx);
   cdbCursor::VARTYPE getFieldDataType(int table_idx, int field_idx);
   cString getFieldDefaultValue(int table_idx, int field_idx);
   int getFieldSize(int table_idx, int field_idx);
   int getFieldBufferSize(int table_idx, int field_idx);
   int getFieldDigits(int table_idx, int field_idx);
   bool isFieldNullable(int table_idx, int field_idx);
   bool isFieldPrimaryKey(int table_idx, int field_idx);

protected:
   int dbase_idx;
   int schema_idx;
   cdbDatabase *db;


   // Dictionary-Strukturen (im Speicher)
   // ===================================

   struct FIELD {
      FIELD() { flags = 0; }
      enum {                        // Moegliche Flags:
         fIsNullable    = (1 << 0), //  - NULL-Werte erlaubt
         fIsPrimary     = (1 << 1)  //  - Bestandteil des Primary Keys
      };
      int flags;                    // Flags
      cString name;                 // Name des Feldes
      cString def_value;            // Defaultwert
      cdbCursor::VARTYPE type;      // Datentyp
      int buffer_size;              // Puffergroesse in Bytes
      int field_size;               // Feldgroesse in Zeichen (Anzeigenbreite)
      int digits;                   // Anzahl Nachkommastellen
   };
   typedef cArray<FIELD, const FIELD&> FIELD_ARRAY;
   typedef cArray<int, int> PKEY_ARRAY;

   struct TABLE {
      TABLE() { flags = 0; }
      enum {                        // Moegliche Flags:
         tFieldsLoaded  = (1 << 0), //  - Feldinfos bereits geladen
         tIsTable       = (1 << 1), //  - Typ "Tabelle"
         tIsView        = (1 << 2)  //  - Typ "View"
      };
      int flags;                    // Flags
      cString name;                 // Name der Tabelle
      FIELD_ARRAY fields;           // Zugeordnete Felder
      cString pkey_name;            // Name des Primaerschluessels (PK)
      PKEY_ARRAY pkeys;             // Indizes der PK-Elemente in 'fields'
   };
   typedef cArray<TABLE, const TABLE&> TABLE_ARRAY;

   struct SCHEMA {
      SCHEMA() { flags = 0; }
      enum {                        // Moegliche Flags:
         sTablesLoaded  = (1 << 0), //  - Tabelleninfos bereits geladen
      };
      int flags;                    // Flags
      cString name;                 // Name des Schemas
      TABLE_ARRAY tables;           // Zugeordnete Tabellen
   };
   typedef cArray<SCHEMA, const SCHEMA&> SCHEMA_ARRAY;

   struct DBASE {
      cString name;                 // Name der Datenbank
      SCHEMA_ARRAY schemas;         // Zugeordnete Schemas
   };
   typedef cArray<DBASE, const DBASE&> DBASE_ARRAY;


   // Zugriff auf Dictionary-Strukturen (im Speicher)
   // ===============================================

   int findTable(const SCHEMA& schema, cString table_name);
   int findField(const TABLE& table, cString field_name);

   DBASE& getDbase()
      { return dbases[dbase_idx]; }
   SCHEMA& getSchema()
      { return getDbase().schemas[schema_idx]; }
   TABLE& getTable(int table_idx)
      { return getSchema().tables[table_idx]; }
   FIELD& getField(int table_idx, int field_idx)
      { return getTable(table_idx).fields[field_idx]; }

   void add(SCHEMA& schema, const TABLE& table);
   void add(TABLE& table, const FIELD& field, int at_pos = -1);


   // Events
   // ======

   virtual bool onOpen(cdbDatabase& db) = 0;
   virtual bool onClose() = 0;

   virtual cString onMakeDbName(cdbDatabase& db) = 0;

   virtual void onLoadTables(SCHEMA& schema) = 0;
   virtual void onLoadFields(TABLE& table) = 0;

private:
   int reference_counter;
   int protect_counter;
   static cMutexSem protect_sema;
   static DBASE_ARRAY dbases;

   // In geschuetzten Bereich eintreten (schachtelbar)
   void begin();
   // Geschuetzten Bereich wieder verlassen
   void end();

   // Laden der Tabelleninformationen
   void loadTables();
   // Laden der Feldinformationen fuer Tabelle 'table_idx'
   void loadFields(int table_idx);

};


// Implementierung cDictBase
// ===========================================================================

cMutexSem cDictBase::protect_sema;
cDictBase::DBASE_ARRAY cDictBase::dbases;

cDictBase::cDictBase()
{
   cDictBase::db = NULL;
   cDictBase::dbase_idx = -1;
   cDictBase::schema_idx = -1;
   cDictBase::protect_counter = 0;
   cDictBase::reference_counter = 0;
}

cDictBase::~cDictBase()
{
   // ...
}


void cDictBase::attach()
{
   reference_counter++;
}

void cDictBase::detach()
{
   if ( --reference_counter <= 0 )
      delete this;
}


bool cDictBase::open(cdbDatabase& db, cString schema_name)
{
   bool rc = false;

   begin();

      try {

         cDictBase::db = &db;
         cString dbase_name = onMakeDbName(db);

         for ( dbase_idx = 0 ; dbase_idx < dbases.getSize() ; dbase_idx++ ) {
            if ( dbases[dbase_idx].name.compareNoCase(dbase_name) == 0 )
               break;
         }

         if ( dbase_idx >= dbases.getSize() ) {
            dbases.setSize(dbase_idx + 1);
            dbases[dbase_idx].name = dbase_name;
         }

         DBASE& dbase = dbases[dbase_idx];
         SCHEMA_ARRAY& schemas = dbase.schemas;

         for ( schema_idx = 0 ; schema_idx < schemas.getSize() ; schema_idx++ ) {
            if ( schemas[schema_idx].name.compareNoCase(schema_name) == 0 )
               break;
         }

         if ( schema_idx >= schemas.getSize() ) {
            schemas.setSize(schema_idx + 1);
            schemas[schema_idx].name = schema_name;
         }

         rc = onOpen(db);

      } catch ( ... ) {
         end(); throw;
      }

   end();

   return rc;
}

bool cDictBase::close()
{
   bool rc = false;

   begin();

      try {
         rc = onClose();
      } catch ( ... ) {
         end(); throw;
      }

   end();

   return rc;
}

cString cDictBase::getSchemaName()
{
   cString name;

   begin();
      name = getSchema().name;
   end();

   return name;
}

cString cDictBase::getTableName(int idx)
{
   cString name;

   loadTables();

   begin();

      TABLE_ARRAY& tables = getSchema().tables;

      if ( idx >= 0 && idx < tables.getSize() )
         name = tables[idx].name;

   end();

   return name;
}

int cDictBase::findTable(cString name)
{
   int table_idx = -1;

   loadTables();

   begin();
      table_idx = findTable(getSchema(), name);
/*
      TABLE_ARRAY& tables = getSchema().tables;

      for ( int idx = 0 ; idx < tables.GetSize() ; idx++ ) {
         if ( tables[idx].name == name ) {
            table_idx = idx;
            break;
         }
      }
*/
   end();

   return table_idx;
}

int cDictBase::getTableCount()
{
   int count = 0;

   loadTables();

   begin();
      count = getSchema().tables.getSize();
   end();

   return count;
}

cString cDictBase::getFieldName(int table_idx, int idx)
{
   cString name;

   loadFields(table_idx);

   begin();

      FIELD_ARRAY& fields = getTable(table_idx).fields;

      if ( idx >= 0 && idx < fields.getSize() )
         name = fields[idx].name;

   end();

   return name;
}

int cDictBase::findField(int table_idx, cString name)
{
   int field_idx = -1;

   loadFields(table_idx);

   begin();
      field_idx = findField(getTable(table_idx), name);
/*
      FIELD_ARRAY& fields = getTable(table_idx).fields;

      for ( int idx = 0 ; idx < fields.GetSize() ; idx++ ) {
         if ( fields[idx].name == name ) {
            field_idx = idx;
            break;
         }
      }
*/
   end();

   return field_idx;
}

int cDictBase::getFieldCount(int table_idx)
{
   int count = 0;

   loadFields(table_idx);

   begin();
      count = getTable(table_idx).fields.getSize();
   end();

   return count;
}

cdbDictTable::TABLE_TYPE cDictBase::getTableType(int table_idx)
{
   cdbDictTable::TABLE_TYPE type = cdbDictTable::ttNone;

   begin();

      if ( table_idx >= 0 && table_idx < getSchema().tables.getSize() ) {

         int flags = getTable(table_idx).flags;

         if ( flags & TABLE::tIsTable ) {
            type = cdbDictTable::ttTable;
         } else if ( flags & TABLE::tIsView ) {
            type = cdbDictTable::ttView;
         }

      }

   end();

   return type;
}

cdbCursor::VARTYPE cDictBase::getFieldDataType(int table_idx, int field_idx)
{
   cdbCursor::VARTYPE type = cdbCursor::tString;

   begin();
      type = getField(table_idx, field_idx).type;
   end();

   return type;
}

cString cDictBase::getFieldDefaultValue(int table_idx, int field_idx)
{
   cString value;

   begin();
      value = getField(table_idx, field_idx).def_value;
   end();

   return value;
}

int cDictBase::getFieldSize(int table_idx, int field_idx)
{
   int size = 0;

   begin();
      size = getField(table_idx, field_idx).field_size;
   end();

   return size;
}

int cDictBase::getFieldBufferSize(int table_idx, int field_idx)
{
   int size = 0;

   begin();
      size = getField(table_idx, field_idx).buffer_size;
   end();

   return size;
}

int cDictBase::getFieldDigits(int table_idx, int field_idx)
{
   int digits = 0;

   begin();
      digits = getField(table_idx, field_idx).digits;
   end();

   return digits;
}

bool cDictBase::isFieldNullable(int table_idx, int field_idx)
{
   bool rc = false;

   begin();
      rc = !!(getField(table_idx, field_idx).flags & FIELD::fIsNullable);
   end();

   return rc;
}

bool cDictBase::isFieldPrimaryKey(int table_idx, int field_idx)
{
   bool rc = false;

   begin();
      rc = !!(getField(table_idx, field_idx).flags & FIELD::fIsPrimary);
   end();

   return rc;
}

void cDictBase::begin()
{
   if ( protect_counter++ == 0 && !protect_sema.request(2500) )
      throw cErrBase(cErrBase::errTimeout, "cDictBase::loadTables()");
}

void cDictBase::end()
{
   if ( --protect_counter == 0 )
      protect_sema.release();
}

void cDictBase::loadTables()
{
   begin();

      try {
         SCHEMA& schema = getSchema();
         if ( !(schema.flags & SCHEMA::sTablesLoaded) ) {
            onLoadTables(schema);
            schema.flags |= SCHEMA::sTablesLoaded;
         }
      } catch ( ... ) {
         end(); throw;
      }

   end();
}

void cDictBase::loadFields(int table_idx)
{
   begin();

      try {
         TABLE& table = getTable(table_idx);
         if ( !(table.flags & TABLE::tFieldsLoaded) ) {
            onLoadFields(table);
            table.flags |= TABLE::tFieldsLoaded;
         }
      } catch ( ... ) {
         end(); throw;
      }

   end();
}

int cDictBase::findTable(const SCHEMA& schema, cString table_name)
{
   // Interne Funktion, Kein Semaphorenschutz noetig!
   const TABLE_ARRAY& tables = schema.tables;

   for ( int idx = 0 ; idx < tables.getSize() ; idx++ ) {
      if ( tables[idx].name.compareNoCase(table_name) == 0 )
         return idx;
   }

   return -1;
}

int cDictBase::findField(const TABLE& table, cString field_name)
{
   // Interne Funktion, Kein Semaphorenschutz noetig!
   const FIELD_ARRAY& fields = table.fields;

   for ( int idx = 0 ; idx < fields.getSize() ; idx++ ) {
      if ( fields[idx].name.compareNoCase(field_name) == 0 )
         return idx;
   }

   return -1;
}

void cDictBase::add(SCHEMA& schema, const TABLE& table)
{
   // Interne Funktion, Kein Semaphorenschutz noetig!
   int idx = schema.tables.getSize();
   schema.tables.setSize(idx + 1);
   schema.tables[idx] = table;
}

void cDictBase::add(TABLE& table, const FIELD& field, int at_pos)
{
   // Interne Funktion, Kein Semaphorenschutz noetig!
   int idx = 0, size = table.fields.getSize();

   if ( at_pos < 0 ) {
      table.fields.setSize(size + 1);
      idx = size;
   } else if ( at_pos >= size ) {
      table.fields.setSize(at_pos + 1);
      idx = at_pos;
   }

   table.fields[idx] = field;
}




#if defined(__DUMMY__)

// ===========================================================================
// Definition cDictDummy
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDictBase
//      +--cDictDummy
//
// ===========================================================================

class cDictDummy : public cDictBase {

public:
   cDictDummy()
      { }
   ~cDictDummy()
      { }

protected:
   bool onOpen(cdbDatabase& db);
   bool onClose();

   cString onMakeDbName(cdbDatabase& db);

   void onLoadTables(SCHEMA& schema);
   void onLoadFields(TABLE& table);

};


// Implementierung cDictDummy
// ===========================================================================

bool cDictDummy::onOpen(cdbDatabase& /*db*/)
{
   DbgDb("Dummy: Open");
   return true;
}

bool cDictDummy::onClose()
{
   DbgDb("Dummy: Close");
   return true;
}

cString cDictDummy::onMakeDbName(cdbDatabase& db)
{
   return ":Dummy:" + db.getDSN();
}

void cDictDummy::onLoadTables(SCHEMA& /*schema*/)
{
   DbgDb("Dummy: LoadTables()");
}

void cDictDummy::onLoadFields(TABLE& /*table*/)
{
   DbgDb("Dummy: LoadFields()");
}

#endif /*__DUMMY__*/




#if defined(__OCI__)

// ===========================================================================
// Definition cDictOCI
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDictBase
//      +--cDictOCI
//
// ===========================================================================

class cDictOCI : public cDictBase {

public:
   cDictOCI();
   ~cDictOCI();

protected:
   bool onOpen(cdbDatabase& db);
   bool onClose();

   cString onMakeDbName(cdbDatabase& db);

   void onLoadTables(SCHEMA& schema);
   void onLoadFields(TABLE& table);

};


// Implementierung cDictOCI
// ===========================================================================

cDictOCI::cDictOCI()
{
}

cDictOCI::~cDictOCI()
{
}

bool cDictOCI::onOpen(cdbDatabase& db)
{
   DbgDb("OCI: Open()");
   return true;
}

bool cDictOCI::onClose()
{
   DbgDb("OCI: Close()");
   return true;
}

cString cDictOCI::onMakeDbName(cdbDatabase& db)
{
   return ":OCI:" + db.getDSN();
}

void cDictOCI::onLoadTables(SCHEMA& schema)
{
   DbgDb("OCI: LoadTables()");
}

void cDictOCI::onLoadFields(TABLE& table)
{
   DbgDb("OCI: LoadFields()");
}

#endif /*__OCI__*/




#if defined(__BTI__)

// ===========================================================================
// Definition cDictBTI
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDictBase
//      +--cDictBTI
//
// ===========================================================================

class cDictBTI : public cDictBase {

public:
   cDictBTI();
   ~cDictBTI();

protected:
   bool onOpen(cdbDatabase& db);
   bool onClose();

   cString onMakeDbName(cdbDatabase& db);

   void onLoadTables(SCHEMA& schema);
   void onLoadFields(TABLE& table);

};


// Implementierung cDictBTI
// ===========================================================================

cDictBTI::cDictBTI()
{
}

cDictBTI::~cDictBTI()
{
}

bool cDictBTI::onOpen(cdbDatabase& db)
{
   DbgDb("BTI: Open()");
   return true;
}

bool cDictBTI::onClose()
{
   DbgDb("BTI: Close()");
   return true;
}

cString cDictBTI::onMakeDbName(cdbDatabase& db)
{
   return ":BTI:" + db.getDSN();
}

void cDictBTI::onLoadTables(SCHEMA& schema)
{
   DbgDb("BTI: LoadTables()");
}

void cDictBTI::onLoadFields(TABLE& table)
{
   DbgDb("BTI: LoadFields()");
}

#endif /*__BTI__*/




#if defined(__ODBC__)

// ===========================================================================
// Definition cDictODBC
// ---------------------------------------------------------------------------
//
// cBase
//  +--cDictBase
//      +--cDictODBC
//
// ===========================================================================

class cDictODBC : public cDictBase {

public:
   cDictODBC();
   ~cDictODBC();

protected:
   bool onOpen(cdbDatabase& db);
   bool onClose();

   cString onMakeDbName(cdbDatabase& db);

   void onLoadTables(SCHEMA& schema);
   void onLoadFields(TABLE& table);

private:
   cdbCursor::VARTYPE convType(int sql_type, int size, int prec);
   int convBufferSize(cdbCursor::VARTYPE type, int buf_size);
   bool loadPKsUsingSQLPrimaryKeys(TABLE& table);
   bool loadPKsUsingSQLSpecialColumns(TABLE& table);

};


// Implementierung cDictODBC
// ===========================================================================

cDictODBC::cDictODBC()
{
}

cDictODBC::~cDictODBC()
{
}

bool cDictODBC::onOpen(cdbDatabase& /*db*/)
{
   DbgDb("ODBC: Open()");
   return true;
}

bool cDictODBC::onClose()
{
   DbgDb("ODBC: Close()");
   return true;
}

cString cDictODBC::onMakeDbName(cdbDatabase& db)
{
   return ":ODBC:" + db.getDSN();
}

void cDictODBC::onLoadTables(SCHEMA& schema)
{
   DbgDb("ODBC: LoadTables()");

   cString sql_names[2];
   sql_names[0] = schema.name;

   csVarString table_name(128), table_type(128);

   cdbCursor cu(*db);
   cu.executeDriverCode(3 /*SQLTables*/, (void *)sql_names);
   cu.define(3-1, table_name);
   cu.define(4-1, table_type);
   cu.exec();

   while ( cu.fetch() ) {
      TABLE table;
      table.name = table_name;
      // DbgDb("cDictODBC: Table %s, type %s", (const char *)table_name, (const char *)table_type);
      if ( strcmp(table_type, "TABLE") == 0 ) {
         table.flags = TABLE::tIsTable;
      } else if ( strcmp(table_type, "VIEW") == 0 ) {
         table.flags = TABLE::tIsView;
      }
      add(schema, table);
   }
}

void cDictODBC::onLoadFields(TABLE& table)
{
   DbgDb("ODBC: LoadFields()");

   cString sql_names[3];
   sql_names[0] = getSchema().name;
   sql_names[1] = table.name;

   csVarInt ordinal_pos, data_type, column_size, buffer_length, decimal_digits, nullable;
   csVarString column_name(128), column_def(128);

   cdbCursor cu(*db);
   cu.executeDriverCode(1 /*SQLColumns*/, (void *)sql_names);
   cu.define(4-1, column_name);
   cu.define(5-1, data_type);
   cu.define(7-1, column_size);
   cu.define(8-1, buffer_length);
   cu.define(9-1, decimal_digits);
   cu.define(11-1, nullable);
   cu.define(13-1, column_def);
   cu.define(17-1, ordinal_pos);
   cu.exec();

   while ( cu.fetch() ) {
      FIELD field;
      field.name = column_name;
      field.def_value = column_def;
      field.type = convType(data_type, column_size, decimal_digits);
      field.buffer_size = convBufferSize(field.type, buffer_length);
      field.field_size = column_size;
      field.digits = decimal_digits;
      if ( int(nullable) == SQL_NULLABLE ) {
         field.flags = FIELD::fIsNullable;
      }
      add(table, field, ordinal_pos - 1);
   }

   if ( !loadPKsUsingSQLPrimaryKeys(table) ) {
      loadPKsUsingSQLSpecialColumns(table);
   }
}

cdbCursor::VARTYPE cDictODBC::convType(int sql_type, int size, int prec)
{
   cdbCursor::VARTYPE ct = cdbCursor::tString;

   switch ( sql_type ) {
   case SQL_VARCHAR:                      ct = cdbCursor::tString; break;     // VARCHAR(n)
   case SQL_LONGVARCHAR:                  break;                              // LONG VARCHAR
   case SQL_WCHAR:                        break;                              // WCHAR(n)
   case SQL_WVARCHAR:                     break;                              // VARWCHAR(n)
   case SQL_WLONGVARCHAR:                 break;                              // LONGWVARCHAR
   case SQL_SMALLINT:                     ct = cdbCursor::tShort; break;      // SMALLINT
   case SQL_INTEGER:                      ct = cdbCursor::tLong; break;       // INTEGER
   case SQL_FLOAT:                        ct = cdbCursor::tFloat; break;      // FLOAT(p)
   case SQL_REAL:                         ct = cdbCursor::tDouble; break;     // REAL
   case SQL_DOUBLE:                       ct = cdbCursor::tDouble; break;     // DOUBLE PRECISION
   case SQL_BIT:                          break;                              // BIT
   case SQL_TINYINT:                      ct = cdbCursor::tChar; break;       // TINYINT
   case SQL_BIGINT:                       break;                              // BIGINT
   case SQL_BINARY:                       break;                              // BINARY(n)
   case SQL_VARBINARY:                    break;                              // VARBINARY(n)
   case SQL_LONGVARBINARY:                break;                              // LONG VARBINARY
   case SQL_INTERVAL_MONTH:               break;                              // INTERVAL MONTH(p)
   case SQL_INTERVAL_YEAR:                break;                              // INTERVAL YEAR(p)
   case SQL_INTERVAL_YEAR_TO_MONTH:       break;                              // INTERVAL YEAR(p) TO MONTH
   case SQL_INTERVAL_DAY:                 break;                              // INTERVAL DAY(p)
   case SQL_INTERVAL_HOUR:                break;                              // INTERVAL HOUR(p)
   case SQL_INTERVAL_MINUTE:              break;                              // INTERVAL MINUTE(p)
   case SQL_INTERVAL_SECOND:              break;                              // INTERVAL SECOND(p,q)
   case SQL_INTERVAL_DAY_TO_HOUR:         break;                              // INTERVAL DAY(p) TO HOUR
   case SQL_INTERVAL_DAY_TO_MINUTE:       break;                              // INTERVAL DAY(p) TO MINUTE
   case SQL_INTERVAL_DAY_TO_SECOND:       break;                              // INTERVAL DAY(p) TO SECOND(q)
   case SQL_INTERVAL_HOUR_TO_MINUTE:      break;                              // INTERVAL HOUR(p) TO MINUTE
   case SQL_INTERVAL_HOUR_TO_SECOND:      break;                              // INTERVAL HOUR(p) TO SECOND(q)
   case SQL_INTERVAL_MINUTE_TO_SECOND:    break;                              // INTERVAL MINUTE(p) TO SECOND(q)
#if ODBCVER > 0x0250
   case SQL_TYPE_DATE:                    ct = cdbCursor::tDate; break;       // DATE
   case SQL_TYPE_TIME:                    ct = cdbCursor::tTime; break;       // TIME(p)
   case SQL_TYPE_TIMESTAMP:               ct = cdbCursor::tTimeStamp; break;  // TIMESTAMP(p)
   case SQL_GUID:                         break;                              // GUID
#else
   case SQL_DATE:                         ct = cdbCursor::tDate; break;       // DATE
   case SQL_TIME:                         ct = cdbCursor::tTime; break;       // TIME(p)
   case SQL_TIMESTAMP:                    ct = cdbCursor::tTimeStamp; break;  // TIMESTAMP(p)
#endif
   case SQL_CHAR:                                                             // CHAR(n)
      if ( size > 1 ) {
         ct = cdbCursor::tString;
      } else {
         ct = cdbCursor::tChar;
      };
      break;
   case SQL_DECIMAL:                                                          // DECIMAL(p,s)
   case SQL_NUMERIC:                                                          // NUMERIC(p,s)
      if ( prec > 0 || size > 9 ) {
         ct = cdbCursor::tDouble;
      } else if ( size > 4 ) {
         ct = cdbCursor::tLong;
      } else {
         ct = cdbCursor::tShort;
      }
      break;
   }

   #define __Compatibility_With_ECL_store__
   #ifdef __Compatibility_With_ECL_store__
      // Force compatibility of datatypes with ECL/store
      // (No short and float types available)
      switch ( ct ) {
      case cdbCursor::tShort: ct = cdbCursor::tLong; break;
      case cdbCursor::tFloat: ct = cdbCursor::tDouble; break;
      }
   #endif

   return ct;
}

int cDictODBC::convBufferSize(cdbCursor::VARTYPE type, int buf_size)
{
   switch ( type ) {
   case cdbCursor::tShort:       return sizeof(short);
   case cdbCursor::tLong:        return sizeof(long);
   case cdbCursor::tFloat:       return sizeof(float);
   case cdbCursor::tDouble:      return sizeof(double);
   case cdbCursor::tChar:        return sizeof(char);
   case cdbCursor::tString:      return buf_size;
   case cdbCursor::tRowid:       return 15; // ??? TBD: ???
   case cdbCursor::tDate:        return sizeof(cDate);
   case cdbCursor::tTime:        return sizeof(cTime);
   case cdbCursor::tTimeStamp:   return sizeof(cDateTime);
   }

   return buf_size;
}

bool cDictODBC::loadPKsUsingSQLPrimaryKeys(TABLE& table)
{
   cString sql_names[2];
   sql_names[0] = getSchema().name;
   sql_names[1] = table.name;

   csVarInt key_seq;
   csVarString column_name(128), pk_name(128);
   bool pk_found = false;

   try {

      cdbCursor cu(*db);
      cu.executeDriverCode(5 /*SQLPrimaryKeys*/, (void *)sql_names);
      cu.define(4-1, column_name);
      cu.define(5-1, key_seq);
      cu.define(6-1, pk_name);
      cu.exec();

      for ( int i = 0 ; cu.fetch() ; ) {
         int idx = findField(table, cString(column_name));
         if ( idx >= 0 ) {
            table.pkeys.setSize(i+1);
            table.pkeys[i++] = idx;
            table.fields[idx].flags |= FIELD::fIsPrimary;
         }
      }

      table.pkey_name = pk_name;
      pk_found = true;

   } catch ( ... ) {

      pk_found = false;

   }

   return pk_found;
}

bool cDictODBC::loadPKsUsingSQLSpecialColumns(TABLE& table)
{
   cString sql_names[5];
   sql_names[0] = getSchema().name;
   sql_names[1] = table.name;
   sql_names[2] = "BEST_ROWID";
   sql_names[3] = "CURROW";
   sql_names[4] = "NULLABLE";

   csVarInt pseudo_column;
   csVarString column_name(128);
   bool pk_found = false;

   try {

      cdbCursor cu(*db);
      cu.executeDriverCode(7 /*SQLSpecialColumns*/, (void *)sql_names);
      cu.define(2-1, column_name);
      cu.define(8-1, pseudo_column);
      cu.exec();

      for ( int i = 0 ; cu.fetch() ; ) {
         int idx = findField(table, cString(column_name));
         if ( idx >= 0 && (int)pseudo_column == SQL_PC_NOT_PSEUDO ) {
            table.pkeys.setSize(i+1);
            table.pkeys[i++] = idx;
            table.fields[idx].flags |= FIELD::fIsPrimary;
         }
      }

      pk_found = true;

   } catch ( ... ) {
      pk_found = false;
   }

   return pk_found;
}

#endif /*__ODBC__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbDictField
// ---------------------------------------------------------------------------
//
// cBase
//  +--cdbDictField
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbDictField : public cBase {
   friend class cdbDictTable;

public:

   // Default-Konstruktor
   cdbDictField();
   // Copy-Konstruktor
   cdbDictField(const cdbDictField& other);
   // Destruktor
   ~cdbDictField();

   // Zuweisungsoperator
   cdbDictField& operator=(const cdbDictField& other);


   // Allgemeines
   // ===========

   cString getSchemaName() const;
   cString getTableName() const;
   cString getFieldName() const;

   cdbCursor::VARTYPE getDataType() const;
   int getFieldSize() const;
   int getBufferSize() const;
   int getDigits() const;
   cString getDefaultValue() const;

   bool isNullable() const;
   bool isPrimaryKey() const;


private:

   // Privater Konstruktor (nur fuer cdbDictTable)
   cdbDictField(void *dc_base, int table_idx, int field_idx);

   void *dc_base;
   int table_idx;
   int field_idx;

};

#endif /*__INTERFACE__*/


// Implementierung cdbDictField
// ===========================================================================

cdbDictField::cdbDictField()
{
   cdbDictField::dc_base = 0;
   cdbDictField::table_idx = 0;
   cdbDictField::field_idx = 0;
}

cdbDictField::cdbDictField(void *dc_base, int table_idx, int field_idx)
{
   cdbDictField::dc_base = dc_base;
   cdbDictField::table_idx = table_idx;
   cdbDictField::field_idx = field_idx;
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) base->attach();
}

cdbDictField::cdbDictField(const cdbDictField& other)
{
   cdbDictField::dc_base = other.dc_base;
   cdbDictField::table_idx = other.table_idx;
   cdbDictField::field_idx = other.field_idx;
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) base->attach();
}

cdbDictField::~cdbDictField()
{
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) base->detach();
}

cdbDictField& cdbDictField::operator=(const cdbDictField& other)
{
   cDictBase *old_base = (cDictBase *)dc_base;
   if ( old_base ) old_base->detach();

   cdbDictField::dc_base = other.dc_base;
   cdbDictField::table_idx = other.table_idx;
   cdbDictField::field_idx = other.field_idx;
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) base->attach();

   return *this;
}


// Allgemeines
// ===========

cString cdbDictField::getSchemaName() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getSchemaName() : cString();
}

cString cdbDictField::getTableName() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getTableName(table_idx) : cString();
}

cString cdbDictField::getFieldName() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getFieldName(table_idx, field_idx) : cString();
}

cdbCursor::VARTYPE cdbDictField::getDataType() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getFieldDataType(table_idx, field_idx) : cdbCursor::tString;
}

int cdbDictField::getFieldSize() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getFieldSize(table_idx, field_idx) : 0;
}

int cdbDictField::getBufferSize() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getFieldBufferSize(table_idx, field_idx) : 0;
}

int cdbDictField::getDigits() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getFieldDigits(table_idx, field_idx) : 0;
}

cString cdbDictField::getDefaultValue() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getFieldDefaultValue(table_idx, field_idx) : cString();
}

bool cdbDictField::isNullable() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->isFieldNullable(table_idx, field_idx) : false;
}

bool cdbDictField::isPrimaryKey() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->isFieldPrimaryKey(table_idx, field_idx) : false;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbDictTable
// ---------------------------------------------------------------------------
//
// cBase
//  +--cdbDictTable
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbDictTable : public cBase {
   friend class cdbDictionary;

public:

   // Default-Konstruktor
   cdbDictTable();
   // Copy-Konstruktor
   cdbDictTable(const cdbDictTable& other);
   // Destruktor
   ~cdbDictTable();

   // Zuweisungsoperator
   cdbDictTable& operator=(const cdbDictTable& other);


   // Allgemeines
   // ===========

   enum TABLE_TYPE { ttNone, ttTable, ttView };

   // Typ der Tabelle ermitteln
   TABLE_TYPE getType() const;

   // Name des Schemas ermitteln
   cString getSchemaName() const;
   // Name der Tabelle ermitteln
   cString getTableName() const;


   // Zugeordnete Felder
   // ==================

   // Feldeintrag ueber Namen suchen
   int findField(cString field_name) const;

   // Anzahl Feldeintraege ermitteln
   int getFieldCount() const;
   // Feldname ueber Index ermitteln
   cString getFieldName(int idx) const;
   // Feldeintrag ueber Index ermitteln
   cdbDictField getField(int idx) const;


private:

   // Privater Konstruktor (nur fuer cdbDictionary)
   cdbDictTable(void *dc_base, int table_idx);

   void *dc_base;
   int table_idx;

};

#endif /*__INTERFACE__*/


// Implementierung cdbDictTable
// ===========================================================================

cdbDictTable::cdbDictTable()
{
   cdbDictTable::dc_base = 0;
   cdbDictTable::table_idx = 0;
}

cdbDictTable::cdbDictTable(void *dc_base, int table_idx)
{
   cdbDictTable::dc_base = dc_base;
   cdbDictTable::table_idx = table_idx;
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) base->attach();
}

cdbDictTable::cdbDictTable(const cdbDictTable& other)
{
   cdbDictTable::dc_base = other.dc_base;
   cdbDictTable::table_idx = other.table_idx;
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) base->attach();
}

cdbDictTable::~cdbDictTable()
{
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) base->detach();
}

cdbDictTable& cdbDictTable::operator=(const cdbDictTable& other)
{
   cDictBase *old_base = (cDictBase *)dc_base;
   if ( old_base ) old_base->detach();

   cdbDictTable::dc_base = other.dc_base;
   cdbDictTable::table_idx = other.table_idx;
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) base->attach();

   return *this;
}


// Allgemeines
// ===========

cdbDictTable::TABLE_TYPE cdbDictTable::getType() const
{
   DbgTrcDb("Dictionary: %s.%s.getType()",
      Nvl(getSchemaName(),""), Nvl(getTableName(),""));
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getTableType(table_idx) : ttNone;
}

cString cdbDictTable::getSchemaName() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getSchemaName() : cString();
}

cString cdbDictTable::getTableName() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getTableName(table_idx) : cString();
}


// Zugeordnete Felder
// ==================

int cdbDictTable::findField(cString field_name) const
{
   DbgTrcDb("Dictionary: %s.%s.findField(%s)",
      Nvl(getSchemaName(),""), Nvl(getTableName(),""), Nvl(field_name,""));
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->findField(table_idx, field_name) : -1;
}

int cdbDictTable::getFieldCount() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getFieldCount(table_idx) : 0;
}

cString cdbDictTable::getFieldName(int idx) const
{
   DbgTrcDb("Dictionary: %s.%s.getFieldName(%d)",
      Nvl(getSchemaName(),""), Nvl(getTableName(),""), idx);
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getFieldName(table_idx, idx) : cString();
}

cdbDictField cdbDictTable::getField(int idx) const
{
   DbgTrcDb("Dictionary: %s.%s.getField(%d)",
      Nvl(getSchemaName(),""), Nvl(getTableName(),""), idx);
   if ( idx < 0 || idx >= getFieldCount() )
      throw cErrBase(cdbErr::errInvParam, "cdbDictTable::getField()");
   return cdbDictField(dc_base, table_idx, idx);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbDictionary
// ---------------------------------------------------------------------------
//
// cBase
//  +--cdbDictionary
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbDictionary : public cBase {

public:

   // Konstruktor ueber Datenbank und Schema-Name
   cdbDictionary(cdbDatabase& db, cString schema = cString());
   // Copy-Konstruktor
   cdbDictionary(const cdbDictionary& other);
   // Destruktor
   ~cdbDictionary();


   // Allgemeines
   // ===========

   // Name des Schemas ermitteln
   cString getSchemaName() const;


   // Zugeordnete Tabellen
   // ====================

   // Tabelleneintrag ueber Namen suchen
   int findTable(cString table_name) const;

   // Anzahl Tabelleneintraege ermitteln
   int getTableCount() const;
   // Tabellenname ueber Index ermitteln
   cString getTableName(int idx) const;
   // Tabelleneintrag ueber Index ermitteln
   cdbDictTable getTable(int idx) const;


private:
   void *dc_base;

};

#endif /*__INTERFACE__*/


// Implementierung cdbDictionary
// ===========================================================================

cdbDictionary::cdbDictionary(cdbDatabase& db, cString schema)
{
   cDictBase *base = NULL;

   switch ( db.getType() ) {
      #if defined(__DUMMY__)
         case cdbDatabase::DUMMY: base = new0 cDictDummy(); break;
      #endif
      #if defined(__OCI__)
         case cdbDatabase::OCI:   base = new0 cDictOCI(); break;
      #endif
      #if defined(__BTI__)
         case cdbDatabase::BTI:   base = new0 cDictBTI(); break;
      #endif
      #if defined(__ODBC__)
         case cdbDatabase::ODBC:  base = new0 cDictODBC(); break;
      #endif
   }

   if ( !base )
      throw cdbErr(cdbErr::errDbTypeNotSupported);

   base->attach();
   base->open(db, schema);
   dc_base = base;
}

cdbDictionary::cdbDictionary(const cdbDictionary& other)
{
   cDictBase *base = NULL;
   cDictBase *other_base = (cDictBase *)other.dc_base;

   if ( other_base && other_base->getDatabase() ) {
      switch ( other_base->getDatabase()->getType() ) {
         #if defined(__DUMMY__)
            case cdbDatabase::DUMMY: base = new0 cDictDummy(); break;
         #endif
         #if defined(__OCI__)
            case cdbDatabase::OCI:   base = new0 cDictOCI(); break;
         #endif
         #if defined(__BTI__)
            case cdbDatabase::BTI:   base = new0 cDictBTI(); break;
         #endif
         #if defined(__ODBC__)
            case cdbDatabase::ODBC:  base = new0 cDictODBC(); break;
         #endif
      }
   }

   if ( !base )
      throw cdbErr(cdbErr::errDbTypeNotSupported);

   base->attach();
   base->open(*other_base->getDatabase(), *other_base->getSchemaName());
   dc_base = base;
}

cdbDictionary::~cdbDictionary()
{
   cDictBase *base = (cDictBase *)dc_base;
   if ( base ) {
      base->close();
      base->detach();
   }
}


// Allgemeines
// ===========

cString cdbDictionary::getSchemaName() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getSchemaName() : cString();
}


// Zugeordnete Tabellen
// ====================

int cdbDictionary::findTable(cString table_name) const
{
   DbgTrcDb("Dictionary: %s.findTable(%s)",
      Nvl(getSchemaName(),""), Nvl(table_name,""));
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->findTable(table_name) : -1;
}

int cdbDictionary::getTableCount() const
{
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getTableCount() : 0;
}

cString cdbDictionary::getTableName(int idx) const
{
   DbgTrcDb("Dictionary: %s.getTableName(%d)",
      Nvl(getSchemaName(),""), idx);
   cDictBase *base = (cDictBase *)dc_base;
   return base ? base->getTableName(idx) : cString();
}

cdbDictTable cdbDictionary::getTable(int idx) const
{
   DbgTrcDb("Dictionary: %s.getTable(%d)",
      Nvl(getSchemaName(),""), idx);
   if ( idx < 0 || idx >= getTableCount() )
      throw cErrBase(cdbErr::errInvParam, "cdbDictionary::getTable()");
   return cdbDictTable(dc_base, idx);
}


