//
// Alle Beispiele benoetigen die Nordwind-Datenbank aus MS-Office 2000.
// Es muss ein ODBC-Alias "NWIND" eingerichtet sein!
//

#include <iostream.h>

#include "dbi/edb_cursor.hpp"
#include "dbi/edb_cursor_ex.hpp"
#include "dbi/edb_dictionary.hpp"
#include "dbi/edb_transaction.hpp"
#include "dbi/edb_function.hpp"
#include "dbi/edb_query.hpp"
#include "dbi/edb_row.hpp"
#include "dbi/edb_field.hpp"

static const char *VarTypeStr[] = {
   "tShort", "tLong", "tFloat", "tDouble", "tChar", "tString", "tRowid",
   "tDate", "tTime", "tTimeStamp"
};

#define PREFETCH_COUNT 10

void TestArtikel(cdbDatabase& db)
{
   cdbCursor cu(db, PREFETCH_COUNT);

   csVarInt artk_nr;
   csVarString artk_name(256);

   cu.compile(SQL::STMT("SELECT ArtikelNr,ArtikelName FROM Artikel"));
   cu.define(0, artk_nr);
   cu.define(1, artk_name);
   cu.exec();

   while ( cu.fetch() ) {
      cerr << artk_nr << "=" << artk_name << endl;
   }
}

void TestArtikelBetween(cdbDatabase& db, int val1, int val2)
{
   cdbCursor cu(db, PREFETCH_COUNT);

   csVarInt artk_nr;
   csVarString artk_name(256);

   cu.compile(SQL::STMT("SELECT ArtikelNr,ArtikelName FROM Artikel WHERE ArtikelNr BETWEEN ? AND ?"));
   cu.bind(0, val1);
   cu.bind(1, val2);
   cu.define(0, artk_nr);
   cu.define(1, artk_name);
   cu.exec();

   while ( cu.fetch() ) {
      cerr << artk_nr << "=" << artk_name << endl;
   }
}

void TestArtikelLike(cdbDatabase& db, cString pat)
{
   cdbCursor cu(db, PREFETCH_COUNT);

   csVarInt artk_nr;
   csVarString artk_name(256);
   csVarString pattern(pat);

   cu.compile(SQL::STMT("SELECT ArtikelNr,ArtikelName FROM Artikel WHERE ArtikelName LIKE ?"));
   cu.bind(0, pattern);
   cu.define(0, artk_nr);
   cu.define(1, artk_name);
   cu.exec();

   while ( cu.fetch() ) {
      cerr << artk_nr << "=" << artk_name << endl;
   }
}

void TestLieferanten(cdbDatabase& db)
{
   cdbCursor cu(db, PREFETCH_COUNT);

   csVarString ort(256);
   csVarString region(256);
   cu.compile(SQL::STMT("SELECT Ort,Region FROM Lieferanten"));
   cu.define(0, ort);
   cu.define(1, region);
   cu.exec();

   while ( cu.fetch() ) {
      cerr << ort << "(" << (region.isNull() ? "<>" : region) << ")" << endl;
   }
}

void TestFieldInfo(cdbDatabase& db, cString table_name)
{
   cdbCursor cu(db, PREFETCH_COUNT);

   cu.compile("SELECT * FROM " + table_name);
   cu.exec();

   for ( int n = 0 ; n < cu.getFieldCount() ; n++ ) {
      cerr << "FIELD " << n << ": "
           << cu.getFieldName(n) << " "
           << "[" << cu.getFieldLabel(n) << "] "
           << "(" << cu.getFieldSize(n) << "," << cu.getFieldDigits(n) << "); "
           << "TYPE=" << cu.getFieldType(n) << "; "
           << (cu.getFieldNullable(n) ? "ALLOWS NULLS" : "NOT NULL")
           << endl;
   }
}

void TestFieldInfo2(cdbDatabase& db, cString table_name)
{
   cdbCursor cu(db, PREFETCH_COUNT);

   cu.compile("SELECT * FROM " + table_name);
   cu.exec();

   for ( int n = 0 ; n < cu.getFieldCount() ; n++ ) {
      cerr << "FIELD " << n << ": "
           << cu.getFieldName(n) << " "
           << "[" << cu.getFieldLabel(n) << "] "
           << "(" << cu.getFieldSize(n) << "," << cu.getFieldDigits(n) << "); "
           << "TYPE=" << cu.getFieldType(n) << "; "
           << (cu.getFieldNullable(n) ? "ALLOWS NULLS" : "NOT NULL")
           << endl;
      cerr << "   based on "
           << cu.getFieldBaseSchema(n)
           << "/" << cu.getFieldBaseTable(n)
           << "." << cu.getFieldBaseColumn(n)
           << endl;
   }
}

void TestDictionary(cdbDatabase& db)
{
   cdbDictionary dc(db, PREFETCH_COUNT);

   for ( int idx = 0 ; idx < dc.getTableCount() ; idx++ ) {
      cdbDictTable table = dc.getTable(idx);
      cerr << (table.getType() == cdbDictTable::ttTable ? "TABLE " : "VIEW ")
           << table.getTableName() << endl;
      for ( int idx2 = 0 ; idx2 < table.getFieldCount() ; idx2++ ) {
         cdbDictField field = table.getField(idx2);
         cerr << "  " << field.getFieldName()
              << " " << VarTypeStr[field.getDataType()]
              << "(" << field.getFieldSize() << "," << field.getDigits() << ")";
         if ( !field.getDefaultValue().isEmpty() )
            cerr << " DEFAULT " << field.getDefaultValue();
         if ( !field.isNullable() )
            cerr << " NOT NULL";
         if ( field.isPrimaryKey() )
            cerr << " PRIMARY KEY";
         cerr << endl;
      }
   }
}

void TestCursorEx(cdbDatabase& db, cString table_name)
{
   cdbCursorEx cu(db, PREFETCH_COUNT);

   cu.compile("SELECT {PK=3} * FROM " + table_name);
   cu.exec();

   while ( cu.fetch() ) {

      cString line;

      for ( int n = -1 ; n < cu.getFieldCount() ; n++ ) {
         cString val; cu.get(n, val);
         if ( !line.isEmpty() )
            line << ";";
         line << val;
      }

      cerr << line << endl;

   }
}

void TestTransaction(cdbDatabase& db)
{
   cBase::setDebugMask(0xffff);
   cdbTransaction ta(db);
   cBase::setDebugMask(cBase::dbgError);
}

void TestFunction(cdbDatabase& db)
{
   cdbTransaction ta(db);
   cdbFunction func(&ta);

   cerr << "COUNT(*) = "
        << func.selectInt(SQL::SELECT("SELECT COUNT(*) FROM Artikel")) << endl;
   cerr << "COUNT(*) WHERE Auslaufartikel = "
        << func.selectInt(SQL::SELECT("SELECT COUNT(*) FROM Artikel WHERE Auslaufartikel=TRUE")) << endl;
   cerr << "MAX(ArtikelNr) = "
        << func.selectInt(SQL::SELECT("SELECT MAX(ArtikelNr) FROM Artikel")) << endl;
   cerr << "MAX(Einzelpreis) = "
        << func.selectDbl(SQL::SELECT("SELECT MAX(Einzelpreis) FROM Artikel")) << endl;
   cerr << "Artikelname WHERE ArtikelNr=42 = "
        << func.selectStr(SQL::SELECT("SELECT Artikelname FROM Artikel WHERE ArtikelNr=42")) << endl;
   cerr << "**ERROR** = "
        << func.selectDbl(SQL::SELECT("SELECT MAX(Rmpfl) FROM Bllllrb")) << endl;
}

void ShowQueryData(csQuery *query)
{
   cString line;

   for ( int n = 0 ; n < query->getFieldCount() ; n++ ) {
      cString val; query->get(n, val);
      if ( n > 0 )
         line << ";";
      line << val;
   }

   cerr << line << endl;
}

void FetchAndShowQueryData(csQuery *query)
{
   while ( query->fetch() )
      ShowQueryData(query);
}

void TestDbQuery(cdbDatabase& db)
{
   cdbTransaction ta(db);
   cdbQuery query(&ta, 0,
      SQL::SELECT(
         SQL::STYLE_DISTINCT,
         SQL::FIELDS("Lieferanten.Firma,Artikel.ArtikelNr"),
       //SQL::FROM("{oj Lieferanten OUTER JOIN Artikel ON Lieferanten.LieferantenNr=Artikel.LieferantenNr}")
         SQL::FROM("Artikel,Lieferanten")
       //SQL::FROM("Artikel INNER JOIN Lieferanten ON Artikel.LieferanenNr=Lieferanten.LieferantenNr")
      ));

   class QT : public cEventTarget {
   public:
      cEventSem sema;
      int onData(void *p1, int p2)
      {
         csQuery *query = (csQuery*)p1;
         csQuery::STATE state = (csQuery::STATE)p2;
         switch ( state ) {
          case csQuery::qsStart:   cerr << "qsStart" << endl; break;
          case csQuery::qsData:    ShowQueryData(query); break;
          case csQuery::qsEnd:     cerr << "qsEnd" << endl; sema.set(); break;
         }
         return (int)true;  // false fuer Abbruch
      }
   } qt;

   query.start(cdbQuery::EVENT(&qt, (cdbQuery::EVFUNC_RPI)qt.onData));
   qt.sema.wait();
}

void TestQueryOrder(cdbDatabase& db)
{
   cdbTransaction ta(db);
   cdbQuery query(&ta, 0, SQL::SELECT("SELECT PersonalNr,Vorname,Nachname,Position FROM Personal"));

   cerr << "--- DEFAULT SORT ---" << endl;
   cerr << query.getSQL() << endl;
   if ( query.open() && query.rewind() )
      FetchAndShowQueryData(&query);
   query.close();

   cerr << "--- SORT BY COLUMN 2 ---" << endl;
   query.orderBy(2);
   cerr << query.getSQL() << endl;
   if ( query.open() && query.rewind() )
      FetchAndShowQueryData(&query);
   query.close();

   cerr << "--- SORT BY COLUMN 3(+),1(-) ---" << endl;
   int fld[] = { 3, 1 }, dir[] = { 1, -1 };
   query.setOrder(fld, dir, 2);
   cerr << query.getSQL() << endl;
   if ( query.open() && query.rewind() )
      FetchAndShowQueryData(&query);
   query.close();
}

void TestRow(cdbDatabase& db)
{
   cdbTransaction ta(db);
   cdbQuery query(&ta, 0, SQL::SELECT("SELECT PersonalNr,Vorname,Nachname,Position FROM Personal"));
   query.open(); query.rewind();

   while ( query.fetch() ) {
      cdbRow row(&query);

      cdbField *fld_vorname  = new cdbField(&row, "Vorname");
      cdbField *fld_nachname = new cdbField(&row, "Nachname");
      cdbField *fld_position = new cdbField(&row, "Position");

      row.fetch();
      cString vorname, nachname, position;
      fld_vorname->get(vorname);
      fld_nachname->get(nachname);
      fld_position->get(position);

      cerr << vorname << ", " << nachname << ", " << position << endl;

      // Test EDIT
      row.edit();
      cString str;
      if ( fld_vorname->get(str) )
         fld_vorname->put(str + "$");
      row.save();
   }

   cdbRow new_row(&query);
   cdbField *fld_vorname  = new cdbField(&new_row, "Vorname");
   cdbField *fld_nachname = new cdbField(&new_row, "Nachname");
   cdbField *fld_position = new cdbField(&new_row, "Position");
   cdbField *fld_gebdatum = new cdbField(&new_row, "Geburtsdatum");
   cdbField *fld_einstell = new cdbField(&new_row, "Einstellung");

   // Test ADD
   new_row.add();
   fld_vorname->put("Heinz");
   fld_nachname->put("Hüllhorst");
   fld_position->put("Betriebstrottel");
   fld_gebdatum->put(cDate(1979,3,31));
   fld_einstell->put(cDate(1999,4,1));
   new_row.save();

   query.close();
}

int main()
{
   //cBase::setDebugMask(0xffff);
   cBase::setDebugMask("SQL");
   cdbDatabase db(cdbDatabase::ODBC, "NWIND", "admin");

   if ( PREFETCH_COUNT > 1 ) {
      cerr << "<<< Multi-Fetch >>>" << endl;
   } else {
      cerr << "<<< Single-Fetch >>>" << endl;
   }

   try {
      TestArtikel(db);
      TestArtikelBetween(db, 42, 60);
      TestArtikelLike(db, "L%");
      TestLieferanten(db);
      TestFieldInfo(db, "Artikel");
      TestFieldInfo2(db, "ArtikelLieferanten");
      TestDictionary(db);
      TestCursorEx(db, "Artikel");
      //TestCursorEx(db, "Tab1");
      //TestTransaction(db);
      //TestFunction(db);
      //TestDbQuery(db);
      TestQueryOrder(db);
      TestRow(db);
   } catch ( const cdbErr& err ) {
      cerr << err << endl;
   }

   return 0;
}

