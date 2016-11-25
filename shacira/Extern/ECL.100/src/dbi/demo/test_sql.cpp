
#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "dbi/edb_sql.hpp"


static const char *TxtRelOps[] = {
   "",
   "NOT ", "EXISTS ",
   ">=", "<=", ">", "<", "=", "<>",
   " LIKE ", " IS ", " IN "
};


// ===========================================================================
//                    T  E  S  T  P  R  O  G  R  A  M  M
// ===========================================================================

void TestSelect()
{
   int i;

   #define __SELECT_VARIANT__ 2
   #if __SELECT_VARIANT__ == 1
      SQL::SELECT select =
         SQL::SELECT(
            SQL::HINTS("PK=1,X='999',y"),
            SQL::FIELDS("[a],[b]") + SQL::FIELD("[c]"),
            SQL::FROM("Tabelle1") + SQL::TABLE("Tabelle2"),
            SQL::WHERE("[c]=50 AND [d]=60"),
            SQL::GROUPBY(""),
            SQL::ORDERBY("[a]")
         );
   #elif __SELECT_VARIANT__ == 2
      SQL::SELECT select = "SELECT t.a,NVL(x.b,c),DECODE(a,b,NVL(c,d)) FROM Tabelle1 t LEFT OUTER JOIN Tabelle2 u ON t.x=u.x WHERE c=50 AND d=60 ORDER BY a";
      select =
         SQL::SELECT(
            select.getFields(),
            select.getFrom() + SQL::TABLE("Tabelle3 x"),
            select.getWhere(),
            select.getGroupBy(),
            select.getOrderBy()
         );
   #elif __SELECT_VARIANT__ == 3
      SQL::SELECT select =
         SQL::SELECT(
            SQL::FIELDS("b.prog,SUBSTR(b.info,1,42),z.mprog,m.info,z.zkuerz "),
            SQL::FROM("$##1.MaSt_BearbProg b,$##1.MaSt_BeaPDef z,$##1.MaSt_MProgWA m"),
            SQL::WHERE("b.mnr=$##0 AND z.mnr(+)=$##0 AND m.mnr(+)=$##0 "
                       "AND z.profil(+)=" + Str(42) + " "
                       "AND z.prog(+)=b.prog "
                       "AND m.mprog(+)=z.mprog"),
            SQL::ORDERBY("b.prog")
         );
   #elif __SELECT_VARIANT__ == 4
      SQL::SELECT select =
         "SELECT {} a.artknr,a.info FROM $##1.Artk_Tab a "
         "WHERE a.mnr=$##0 AND EXISTS (SELECT * FROM $##1.Artk_ProdGrp p WHERE p.artknr=a.artknr AND p.pgrp=:1 AND p.mnr=$##0) "
         "ORDER BY a.artknr";
   #elif __SELECT_VARIANT__ == 5
      SQL::SELECT select =
         "SELECT i.anzahl,v.me_text,i.artknr,i.info,i.pnr,i.laenge,i.breite,i.hoehe,i.preis,LTRIM(TO_CHAR(i.anzahl*i.preis*NVL(a.kubfakt,1),'9G999G990D99')) "
         "FROM $##1.Artk_InventList i,$##1.Artk_Tab a,$##1.Stdt_VerEinh v "
         "WHERE i.mnr=$##0 AND i.inr=42 AND i.kst=42 AND a.artknr(+)=i.artknr AND a.mnr(+)=$##0 AND v.ve=i.ve AND v.mnr=$##0 "
         "ORDER BY i.artknr";
   #elif __SELECT_VARIANT__ == 6
      SQL::SELECT select =
         "SELECT i.anzahl,v.me_text,i.[artknr],i.info,i.pnr,i.laenge,i.breite,i.hoehe,i.preis,LTRIM(TO_CHAR(i.anzahl*i.preis*NVL(a.kubfakt,1),'9G999G990D99')) "
         "FROM $##1.Artk_InventList i,$##1.Artk_Tab a,$##1.Stdt_VerEinh v "
         "WHERE i.mnr=$##0 AND i.inr=42 AND i.kst=42 AND a.[artknr](+)=i.[artknr] AND a.mnr(+)=$##0 AND v.ve=i.ve AND v.mnr=$##0 "
         "ORDER BY i.[artknr] ASC,i.info DESC,4,5";
   #endif

   cerr << "SELECT:   '" << select << "'" << endl << endl;

   SQL::HINTS hints = select.getHints();
   cerr << "HINTS:    '" << hints << "' "
        << "(" << hints.getHintCount() << ")" << endl;
   for ( i = 0 ; i < hints.getHintCount() ; i++ ) {
      SQL::HINT hint = hints.getHint(i);
      cerr << "          HINT " << i << ": " << hint.getName() << " = '" << hint.getValue() << "'" << endl;
   }

   SQL::FIELDS fields = select.getFields();
   cerr << "FIELDS:   '" << fields << "' "
        << "(" << fields.getFieldCount() << ")" << endl;
   for ( i = 0 ; i < fields.getFieldCount() ; i++ ) {
      cerr << "          FIELD " << i << ": '" << fields.getField(i) << "'" << endl;
   }

   SQL::FROM from = select.getFrom();
   cerr << "FROM:     '" << from << "' "
        << "(count = " << from.getTableCount() << ", "
        << "base = " << from.getBaseTable() << ")" << endl;
   for ( i = 0 ; i < from.getTableCount() ; i++ ) {
      if ( from.isJoin(i) ) {
         static const char *JoinTypes[] = {
            "INNER JOIN",
            "LEFT OUTER JOIN",
            "RIGHT OUTER JOIN",
            "FULL OUTER JOIN"
         };
         cerr << "          JOIN  " << i << ": '" << from.getJoin(i) << endl;
         cerr << "                   "  << JoinTypes[from.getJoin(i).getJoinType()]
              <<            " "         << from.getJoin(i).getJoinTable()
              <<            " WITH "    << from.getJoin(i).getJoinedTable()
              <<            " ON "      << from.getJoin(i).getJoinOn();
      } else {
         cerr << "          TABLE " << i << ": '" << from.getTable(i).getTableName() << "'";
         if ( !from.getTable(i).getTableAlias().isEmpty() )
            cerr << " (" << from.getTable(i).getTableAlias() << ")";
      }
      cerr << endl;
   }

   SQL::WHERE where = select.getWhere();
   cerr << "WHERE:    '" << where << "' "
        << "(" << where.getCondCount() << ")" << endl;
   for ( i = 0 ; i < where.getCondCount() ; i++ ) {
      SQL::COND cond = where.getCond(i);
      cerr << "          COND " << i << ": '" << cond << "'" << endl;
      cerr << "               '" << cond.getLeftExpr() << "'" << TxtRelOps[cond.getRelOp()] << "'" << cond.getRightExpr() << "'" << endl;
   }

   SQL::ORDERBY orderby = select.getOrderBy();
   cerr << "ORDER BY: '" << orderby << "' "
        << "(" << orderby.getFieldCount() << ")" << endl;
   for ( i = 0 ; i < orderby.getFieldCount() ; i++ ) {
      cerr << "          ORDER " << i << ": '" << orderby.getField(i) << "'" << endl;
   }

   SQL::ORDERBY groupby = select.getGroupBy();
   cerr << "GROUP BY: '" << groupby << "' "
        << "(" << groupby.getFieldCount() << ")" << endl;
   for ( i = 0 ; i < groupby.getFieldCount() ; i++ ) {
      cerr << "          GROUP " << i << ": '" << groupby.getField(i) << "'" << endl;
   }
}

void TestInsert()
{
   int i;

   #define __INSERT_VARIANT__ 2
   #if __INSERT_VARIANT__ == 1
      SQL::INSERT insert =
         SQL::INSERT("INSERT INTO Tabelle(a,b,c) VALUES ((2*(3+4)),'String',3*(4+5))");
   #elif __INSERT_VARIANT__ == 2
      SQL::INSERT insert =
         SQL::INSERT(
         SQL::TABLE("Tabelle"),
         SQL::VALUES("(2*(3+4)),'String',3*(4+5)"));
   #endif

   cerr << "INSERT:   '" << insert << "'" << endl << endl;

   SQL::TABLE table = insert.getTable();
   cerr << "TABLE:    '" << table << "'" << endl;

   SQL::FIELDS fields = insert.getFields();
   cerr << "FIELDS:   '" << fields << "' "
        << "(" << fields.getFieldCount() << ")" << endl;
   for ( i = 0 ; i < fields.getFieldCount() ; i++ ) {
      cerr << "          FIELD " << i << ": '" << fields.getField(i) << "'" << endl;
   }

   SQL::VALUES values = insert.getValues();
   cerr << "VALUES:   '" << values << "' "
        << "(" << values.getValueCount() << ")" << endl;
   for ( i = 0 ; i < values.getValueCount() ; i++ ) {
      cerr << "          VALUE " << i << ": '" << values.getValue(i) << "'" << endl;
   }

   SQL::SELECT select = insert.getSelect();
   cerr << "SELECT:    '" << select << "'" << endl;
}

void TestUpdate()
{
   int i;

   #define __UPDATE_VARIANT__ 1
   #if __UPDATE_VARIANT__ == 1
      SQL::UPDATE update =
         SQL::UPDATE("UPDATE Tabelle SET a=(2*(3+4)),b='String',c=3*(4+5)");
   #endif

   cerr << "UPDATE:   '" << update << "'" << endl << endl;

   SQL::TABLE table = update.getTable();
   cerr << "TABLE:    '" << table << "'" << endl;

   SQL::SET set = update.getSet();
   cerr << "SET:      '" << set << "' "
        << "(" << set.getAssignCount() << ")" << endl;
   for ( i = 0 ; i < set.getAssignCount() ; i++ ) {
      cerr << "          ASSIGN " << i << ": '" << set.getAssign(i).getField() << "'"
           << " = '" << set.getAssign(i).getExpr() + "'" << endl;
   }

   SQL::WHERE where = update.getWhere();
   cerr << "WHERE:     '" << where << "'" << endl;
}

int main()
{
   TestSelect();
   //TestInsert();
   //TestUpdate();

   __ECL_SHOW_LEAKS__();
   return 0;
}
