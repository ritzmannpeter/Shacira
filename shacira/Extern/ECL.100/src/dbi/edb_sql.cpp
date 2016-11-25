// ===========================================================================
// edb_sql.cpp                                                  ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung
// (Dies ist kein Ableitungs-, sondern ein Abhaengigkeitsbaum):
//
//    SELECT
//     |
//     +--FIELDS
//     |   |
//     |   +-FIELD
//     |
//     +--FROM
//     |   |
//     |   +-TABLE
//     |
//     +--WHERE
//     |   |
//     |   +-COND
//     |
//     +--ORDERBY
//     |   |
//     |   +-FIELD
//     |
//     +--GROUPBY
//         |
//         +-FIELD
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "dbi/edb_sql.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"


// Utility Functions
// ===========================================================================

inline cString Concat(cString s1, cString sep, cString s2)
   { return s1.isEmpty() ? s2
          : s2.isEmpty() ? s1
          : s1 + sep + s2; }

#endif /*__INTERFACE__*/




/*.SP.*/
namespace SQL {
/*.EP.*/



// Lokale Variablen
// ===========================================================================

static const char *TxtRelOps[] = {
   "",
   "NOT ", "EXISTS ",
   ">=", "<=", ">", "<", "=", "<>",
   " LIKE ", " IS ", " IN "
};




// Lokale Funktionen
// ===========================================================================

static const char * FindNext(const char *p, char c)
{
   for ( ; *p ; p++ ) {
      if ( *p == c )
         return p;
   }

   return p;
}

static const char * FindMatching(const char *p, char c)
{
   for ( ; *p ; p++ ) {
      if ( *p == c ) {
         return p;
      } else {
         switch ( *p ) {
         case '\'':  p = FindNext(p+1, '\''); break;
         case '"':   p = FindNext(p+1, '"'); break;
         case '(':   p = FindMatching(p+1, ')'); break;
         case '{':   p = FindMatching(p+1, '}'); break;
         }
      }
   }

   return p;
}

static int PosNoCase(const char *str, const char *substr)
{
   // - Sucht substr in str (unabhaengig von Gross-/Kleinschreibung
   // - Liefert Position wie cString.Pos()
   // - Ueberspringt Strings und geklammerte Bereiche

   if ( str == 0 || substr == 0 )
      return -1;

   const char *p;
   int first_ch = toupper(*substr);
   int len = strlen(substr);

   for ( p = str ; *p ; p++ ) {
      if ( toupper(*p) == first_ch && strnicmp(p, substr, len) == 0 ) {
         return p - str;
      } else {
         switch ( *p ) {
         case '\'':  p = FindNext(p+1, '\''); break;
         case '"':   p = FindNext(p+1, '"'); break;
         case '(':   p = FindMatching(p+1, ')'); break;
         case '{':   p = FindMatching(p+1, '}'); break;
         }
      }
   }

   return -1;
}

static int PosNoCase(const char *str, const char *substr[], int& count)
{
   const char *p;

   if ( str == 0 || substr == 0 || count <= 0 )
      return -1;

   for ( p = str ; *p ; p++ ) {
      for ( int i = 0 ; i < count ; i++ ) {
         if ( strnicmp(p, substr[i], strlen(substr[i])) == 0 ) {
            count = i;
            return p - str;
         }
      }
      switch ( *p ) {
      case '\'':  p = FindNext(p+1, '\''); break;
      case '"':   p = FindNext(p+1, '"'); break;
      case '(':   p = FindMatching(p+1, ')'); break;
      case '{':   p = FindMatching(p+1, '}'); break;
      }
   }

   count = 0;
   return -1;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition COND
// --------------------------------------------------------------------------
//
// COND
//
// ===========================================================================

enum REL_OP {
   REL_NONE,
   REL_NOT, REL_EXISTS,
   REL_GE, REL_LE, REL_GT, REL_LT, REL_EQ, REL_NE,
   REL_LIKE, REL_IS, REL_IN
};

class __ECL_DLLEXPORT__ COND {
   cString cond;

public:
   COND()
      { }
   COND(cString sql)
      { cond = sql.trim(); }
   COND(const char *sql)
      { cond = cString(sql).trim(); }

   COND(REL_OP op, cString expr);
   COND(cString left_expr, REL_OP op, cString right_expr);

   operator cString() const
      { return cond; }


   REL_OP getRelOp() const;
   int getExprCount() const;
   cString getLeftExpr() const;
   cString getRightExpr() const;

};

#endif /*__INTERFACE__*/


// Implementierung COND
// ===========================================================================

COND::COND(REL_OP op, cString expr)
{
   cond = TxtRelOps[op] + expr.trim();
}

COND::COND(cString left_expr, REL_OP op, cString right_expr)
{
   cond = left_expr.trim() + TxtRelOps[op] + right_expr.trim();
}

static REL_OP GetRelOp(const char *str, int& last_pos, int& next_pos)
{
   int num = sizeof TxtRelOps / sizeof TxtRelOps[0] - 1;
   int pos = PosNoCase(str, &TxtRelOps[1], num);

   last_pos = pos >= 0 ? pos - 1 : -1;
   next_pos = pos >= 0 ? pos + strlen(TxtRelOps[num+1]) : -1;
   return pos < 0 ? REL_NONE : REL_OP(num+1);
}

REL_OP COND::getRelOp() const
{
   int last_pos, next_pos;
   return GetRelOp(cond, last_pos, next_pos);
}

int COND::getExprCount() const
{
   REL_OP rel_op = getRelOp();
   return rel_op < REL_GE ? 1 : 2;
}

cString COND::getLeftExpr() const
{
   int last_pos, next_pos;
   GetRelOp(cond, last_pos, next_pos);

   return last_pos >= 0 ?
      cond.getLeft(last_pos+1)
    : cString();
}

cString COND::getRightExpr() const
{
   int last_pos, next_pos;
   GetRelOp(cond, last_pos, next_pos);

   return cond.getMid(next_pos);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition WHERE
// ---------------------------------------------------------------------------
//
// WHERE
//
// ===========================================================================

class __ECL_DLLEXPORT__ WHERE {
   cString conds;

public:
   WHERE()
      { }
   WHERE(cString sql)
      { conds = sql.trim(); }
   WHERE(const char *sql)
      { conds = cString(sql).trim(); }

   operator cString() const
      { return conds; }

   inline friend WHERE operator&(const COND& f1, const COND& f2)
      { return WHERE(Concat(f1, " AND ", f2)); }
   inline friend WHERE operator&(const COND& f1, const WHERE& fs2)
      { return WHERE(Concat(f1, " AND ", fs2)); }
   inline friend WHERE operator&(const WHERE& fs1, const COND& f2)
      { return WHERE(Concat(fs1, " AND ", f2)); }
   inline friend WHERE operator&(const WHERE& fs1, const WHERE& fs2)
      { return WHERE(Concat(fs1, " AND ", fs2)); }

   inline friend WHERE operator|(const COND& f1, const COND& f2)
      { return WHERE(Concat(f1, " OR ", f2)); }
   inline friend WHERE operator|(const COND& f1, const WHERE& fs2)
      { return WHERE(Concat(f1, " OR ", fs2)); }
   inline friend WHERE operator|(const WHERE& fs1, const COND& f2)
      { return WHERE(Concat(fs1, " OR ", f2)); }
   inline friend WHERE operator|(const WHERE& fs1, const WHERE& fs2)
      { return WHERE(Concat(fs1, " OR ", fs2)); }

   int getCondCount() const;
   COND getCond(int n) const;

};

#endif /*__INTERFACE__*/


// Implementierung WHERE
// ===========================================================================

int WHERE::getCondCount() const
{
   if ( conds.isEmpty() )
      return 0;

   int count = 1;
   static const char *stop_tok[] = { " AND ", " OR " };

   for ( const char *p = conds ; *p ; p++ ) {
      int num = sizeof stop_tok / sizeof stop_tok[0];
      int pos = PosNoCase(p, stop_tok, num);
      if ( pos < 0 )
         break;
      p += pos;
      count++;
   }

   return count;
}

COND WHERE::getCond(int n) const
{
   if ( conds.isEmpty() )
      return COND();

   const char *p, *last;
   static const char *stop_tok[] = { " AND ", " OR " };

   for ( p = last = conds; *p ; p++ ) {
      int count = 2;
      int pos = PosNoCase(p, stop_tok, count);
      p += pos < 0 ? strlen(p) : pos;
      if ( n-- == 0 )
         break;
      last = p + strlen(stop_tok[count]);
   }

   return COND(cString(last, p - last));
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition ASSIGN
// --------------------------------------------------------------------------
//
// ASSIGN
//
// ===========================================================================

class __ECL_DLLEXPORT__ ASSIGN {
   cString assign;

public:
   ASSIGN()
      { }
   ASSIGN(cString sql)
      { assign = sql.trim(); }
   ASSIGN(const char *sql)
      { assign = cString(sql).trim(); }

   operator cString() const
      { return assign; }

   cString getField() const;
   cString getExpr() const;

};

#endif /*__INTERFACE__*/


// Implementierung ASSIGN
// ===========================================================================

static bool GetEqOp(const char *str, int& last_pos, int& next_pos)
{
   int pos = PosNoCase(str, "=");

   last_pos = pos >= 0 ? pos - 1 : -1;
   next_pos = pos >= 0 ? pos + 1 : -1;
   return pos >= 0;
}

cString ASSIGN::getField() const
{
   int last_pos, next_pos;
   GetEqOp(assign, last_pos, next_pos);

   return last_pos >= 0 ?
      assign.getLeft(last_pos+1)
    : cString();
}

cString ASSIGN::getExpr() const
{
   int last_pos, next_pos;
   GetEqOp(assign, last_pos, next_pos);

   return assign.getMid(next_pos);
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition SET
// ---------------------------------------------------------------------------
//
// SET
//
// ===========================================================================

class __ECL_DLLEXPORT__ SET {
   cString assigns;

public:
   SET()
      { }
   SET(cString sql)
      { assigns = sql.trim(); }
   SET(const char *sql)
      { assigns = cString(sql).trim(); }

   operator cString() const
      { return assigns; }

   inline friend SET operator+(const ASSIGN& f1, const ASSIGN& f2)
      { return SET(Concat(f1, ",", f2)); }
   inline friend SET operator+(const ASSIGN& f1, const SET& fs2)
      { return SET(Concat(f1, ",", fs2)); }
   inline friend SET operator+(const SET& fs1, const ASSIGN& f2)
      { return SET(Concat(fs1, ",", f2)); }
   inline friend SET operator+(const SET& fs1, const SET& fs2)
      { return SET(Concat(fs1, ",", fs2)); }

   int getAssignCount() const;
   ASSIGN getAssign(int n) const;

};

#endif /*__INTERFACE__*/


// Implementierung SET
// ===========================================================================

int SET::getAssignCount() const
{
   if ( assigns.isEmpty() )
      return 0;

   int count = 1;

   for ( const char *p = assigns ; *p ; p++ ) {
      int pos = PosNoCase(p, ",");
      if ( pos < 0 )
         break;
      p += pos;
      count++;
   }

   return count;
}

ASSIGN SET::getAssign(int n) const
{
   if ( assigns.isEmpty() )
      return ASSIGN();

   const char *p, *last;

   for ( p = last = assigns; *p ; p++ ) {
      int pos = PosNoCase(p, ",");
      p += pos < 0 ? strlen(p) : pos;
      if ( n-- == 0 )
         break;
      last = p + 1;
   }

   return ASSIGN(cString(last, p - last));
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition TABLE
// ---------------------------------------------------------------------------
//
// TABLE
//
// ===========================================================================

class __ECL_DLLEXPORT__ TABLE {
   cString table;

public:
   TABLE()
      { }
   TABLE(cString sql)
      { table = sql; }
   TABLE(const char *sql)
      { table = cString(sql).trim(); }

   operator cString() const
      { return table; }

   cString getTableName(bool include_schema = true) const;
   cString getTableAlias() const;

};

#endif /*__INTERFACE__*/


// Implementierung TABLE
// ===========================================================================

cString TABLE::getTableName(bool include_schema) const
{
   int pos = PosNoCase(table, " ");
   cString table_name = pos > 0 ?
      table.getLeft(pos)
    : table;
   if ( !include_schema ) {
      pos = PosNoCase(table_name, ".");
      if ( pos > 0 )
         return table_name.del(0, pos+1);
   }
   return table_name;
}

cString TABLE::getTableAlias() const
{
   int pos = PosNoCase(table, " ");
   if ( pos > 0 ) {
      return table.getRight(table.getLength() - pos).trim();
   } else {
      return cString();
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition JOIN
// ---------------------------------------------------------------------------
//
// <join>          ::= $JOIN( <table> <join_type> <table_or_join> ON <cond> )
// <join_type>     ::= INNER JOIN
//                   | LEFT OUTER JOIN
//                   | RIGHT OUTER JOIN
//                   | FULL OUTER JOIN
//
// ===========================================================================

enum JOIN_TYPE {
   JOIN_INNER, // Inner join
   JOIN_OUTER_LEFT, JOIN_OUTER_RIGHT, JOIN_OUTER_FULL // Outer joins
};

class __ECL_DLLEXPORT__ JOIN {
   cString join;

public:
   JOIN();
   JOIN(cString sql);
   JOIN(const char *sql);
   JOIN(JOIN_TYPE type,
        const TABLE& table,
        const TABLE& joined_table,
        const WHERE& cond = WHERE());
   JOIN(JOIN_TYPE type,
        const TABLE& table,
        const JOIN& joined_join,
        const WHERE& cond);

   operator cString() const
      { return "$JOIN(" + join + ")"; }

   // Ermittelt den Typ des JOINs
   JOIN_TYPE getJoinType() const;
   // Ermittelt die Haupttabelle des JOINs
   TABLE getJoinTable() const;
   // Ermittelt die Bedingung des JOINs
   WHERE getJoinOn() const;

   // Wird eine Tabelle verknuepft?
   bool isJoinedTable() const;
   // Ermittelt die verknuepfte Tabelle
   TABLE getJoinedTable() const;

   // Wird ein weiterer JOIN verknuepft?
   bool isJoinedJoin() const;
   // Ermittelt die untergeordnete Verknuepfung
   JOIN getJoinedJoin() const;

};

#endif /*__INTERFACE__*/


// Implementierung JOIN
// ===========================================================================

static const char *JoinTypes[] = {
   "INNER JOIN",
   "LEFT OUTER JOIN",
   "RIGHT OUTER JOIN",
   "FULL OUTER JOIN"
};

JOIN::JOIN()
{
}

JOIN::JOIN(cString sql)
{
   if ( sql.compareNoCase("$JOIN", 5) == 0 ) {
      join = sql.getSubstr(6, sql.getLastPos(")") - 1).trim();
   } else {
      join = sql.trim();
   }
}

JOIN::JOIN(const char *sql)
{
   if ( cString(sql).compareNoCase("$JOIN", 5) == 0 ) {
      join = cString(sql).getSubstr(6, cString(sql).getLastPos(")") - 1).trim();
   } else {
      join = cString(sql).trim();
   }
}

JOIN::JOIN(JOIN_TYPE type, const TABLE& table, const TABLE& joined_table, const WHERE& cond)
{
   join = cString(table) + " " + JoinTypes[type] + " " + cString(joined_table);
   if ( !cString(cond).isEmpty() )
      join += " ON " + cString(cond);
}

JOIN::JOIN(JOIN_TYPE type, const TABLE& table, const JOIN& joined_join, const WHERE& cond)
{
   join = cString(table) + " " + JoinTypes[type] + " " + cString(joined_join);
   if ( !cString(cond).isEmpty() )
      join += " ON " + cString(cond);
}

JOIN_TYPE JOIN::getJoinType() const
{
   const char *search[] = { " INNER ", " LEFT ", " RIGHT ", " FULL ", " OUTER ", " JOIN " };
   int count = 6, pos = PosNoCase(join, search, count);

   if ( pos <= 0 || count > 4 ) {
      return JOIN_INNER;
   } else if ( count == 4 ) {
      return JOIN_OUTER_LEFT;
   } else {
      return JOIN_TYPE(count);
   }
}

TABLE JOIN::getJoinTable() const
{
   const char *search[] = { " INNER ", " LEFT ", " RIGHT ", " FULL ", " OUTER ", " JOIN " };
   int count = 6, pos = PosNoCase(join, search, count);

   if ( pos < 0 ) {
      return TABLE(join.trim());
   } else {
      return TABLE(join.getLeft(pos).trim());
   }
}

WHERE JOIN::getJoinOn() const
{
   cString arg = join.getSubstr(6, join.getLastPos(")") - 1);

   int prev_pos = PosNoCase(arg, " ON ");

   return prev_pos >= 0 ?
      WHERE(arg.getMid(prev_pos + 4).trim())
    : WHERE();
}

bool JOIN::isJoinedTable() const
{
   cString table = getJoinedTable();
   return !table.isEmpty() && table.compareNoCase("$JOIN", 5) != 0;
}

bool JOIN::isJoinedJoin() const
{
   cString elem = getJoinedTable();
   return elem.compareNoCase("$JOIN", 5) == 0;
}

TABLE JOIN::getJoinedTable() const
{
   int prev_pos = PosNoCase(join, " JOIN ");
   int next_pos = PosNoCase(join, " ON ");

   if ( prev_pos < 0 ) {
      return TABLE();
   } else {
      prev_pos += 6;
   }

   if ( next_pos < 0 ) {
      return TABLE(join.getRight(join.getLength() - prev_pos).trim());
   } else {
      return TABLE(join.getMid(prev_pos, next_pos - prev_pos).trim());
   }
}

JOIN JOIN::getJoinedJoin() const
{
   int prev_pos = PosNoCase(join, " JOIN ");
   int next_pos = PosNoCase(join, " ON ");

   if ( prev_pos < 0 ) {
      return JOIN();
   } else {
      prev_pos += 6;
   }

   if ( next_pos < 0 ) {
      return JOIN(join.getRight(join.getLength() - prev_pos).trim());
   } else {
      return JOIN(join.getMid(prev_pos, next_pos - prev_pos).trim());
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition FROM
// ---------------------------------------------------------------------------
//
// <from>          ::= FROM <table_or_join> { , <table_or_join> }
// <table_or_join> ::= <table> | <join>
//
// ===========================================================================

class __ECL_DLLEXPORT__ FROM {
   cString tables;

public:
   FROM()
      { }
   FROM(cString sql)
      { tables = sql.trim(); }
   FROM(const char *sql)
      { tables = cString(sql).trim(); }

   operator cString() const
      { return tables; }

   inline friend FROM operator+(const TABLE& f1, const TABLE& f2)
      { return FROM(Concat(f1, ",", f2)); }
   inline friend FROM operator+(const TABLE& f1, const FROM& fs2)
      { return FROM(Concat(f1, ",", fs2)); }
   inline friend FROM operator+(const FROM& fs1, const TABLE& f2)
      { return FROM(Concat(fs1, ",", f2)); }
   inline friend FROM operator+(const FROM& fs1, const FROM& fs2)
      { return FROM(Concat(fs1, ",", fs2)); }

   // Liefert die Anzahl Tabellen bzw. JOINs auf oberster Ebene
   int getTableCount() const;
   // Liefert die Basistabelle (gleichgueltig ob innerhalb JOIN oder nicht)
   TABLE getBaseTable() const;

   // Ist das n-te Listenelement eine Tabelle?
   bool isTable(int n) const;
   // Liefert die Tabelle an n-ter Position der Liste
   TABLE getTable(int n) const;

   // Ist das n-te Listenelement ein JOIN
   bool isJoin(int n) const;
   // Liefert den JOIN an n-ter Position der Liste
   JOIN getJoin(int n) const;

};

#endif /*__INTERFACE__*/


// Implementierung FROM
// ===========================================================================

int FROM::getTableCount() const
{
   if ( tables.isEmpty() )
      return 0;

   int count = 1;

   for ( const char *p = tables ; *p ; p++ ) {
      switch ( *p ) {
      case ',':   count++; break;
      case '\'':  p = FindNext(p+1, '\''); break;
      case '(':   p = FindMatching(p+1, ')'); break;
      }
   }

   return count;
}

TABLE FROM::getBaseTable() const
{
   return isJoin(0) ?
      getJoin(0).getJoinTable()
    : getTable(0);
}

bool FROM::isTable(int n) const
{
   cString elem = getTable(n);
   return !elem.isEmpty() && elem.compareNoCase("$JOIN", 5) != 0;
}

bool FROM::isJoin(int n) const
{
   cString elem = getTable(n);
   if ( elem.compareNoCase("$JOIN", 5) == 0 )
      return true;
   if ( elem.getPos(" JOIN ") > 0 )
      return true;
   return false;
}

TABLE FROM::getTable(int n) const
{
   if ( tables.isEmpty() )
      return TABLE();

   const char *p, *last;

   for ( p = last = tables; *p ; p++ ) {
      if ( *p == ',' ) {
         if ( n-- == 0 )
            break;
         last = p + 1;
      } else {
         switch ( *p ) {
         case '\'':  p = FindNext(p+1, '\''); break;
         case '(':   p = FindMatching(p+1, ')'); break;
         }
      }
   }

   return TABLE(cString(last, p - last));
}

JOIN FROM::getJoin(int n) const
{
   if ( tables.isEmpty() )
      return JOIN();

   const char *p, *last;

   for ( p = last = tables; *p ; p++ ) {
      if ( *p == ',' ) {
         if ( n-- == 0 )
            break;
         last = p + 1;
      } else {
         switch ( *p ) {
         case '\'':  p = FindNext(p+1, '\''); break;
         case '(':   p = FindMatching(p+1, ')'); break;
         }
      }
   }

   return JOIN(cString(last, p - last));
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition FIELD
// ---------------------------------------------------------------------------
//
// FIELD
//
// ===========================================================================

class __ECL_DLLEXPORT__ FIELD {
   cString field;

public:
   FIELD()
      { }
   FIELD(cString sql)
      { field = sql.trim(); }
   FIELD(const char *sql)
      { field = cString(sql).trim(); }

   operator cString() const
      { return field; }

   cString getFieldName(bool include_table = true) const;
   cString getFieldAlias() const;
   cString getTableName() const;

};

#endif /*__INTERFACE__*/


// Implementierung FIELD
// ===========================================================================

cString FIELD::getFieldName(bool include_table) const
{
   int pos = PosNoCase(field, " ");
   cString field_name = pos > 0 ?
      field.getLeft(pos)
    : field;
   if ( !include_table ) {
      pos = PosNoCase(field_name, ".");
      if ( pos > 0 )
         return field_name.del(0, pos+1);
   }
   return field_name;
}

cString FIELD::getFieldAlias() const
{
   int pos = PosNoCase(field, " ");
   if ( pos > 0 ) {
      return field.getRight(field.getLength() - pos).trim();
   } else {
      return cString();
   }
}

cString FIELD::getTableName() const
{
   int pos = PosNoCase(field, ".");
   // TBD: ... viiieel zu einfach ...
   if ( pos > 0 ) {
      return field.getLeft(pos - 1);
   } else {
      return cString();
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition FIELDS
// ---------------------------------------------------------------------------
//
// FIELDS
//
// ===========================================================================

class __ECL_DLLEXPORT__ FIELDS {
   cString fields;

public:
   FIELDS()
      { }
   FIELDS(cString sql)
      { fields = sql.trim(); }
   FIELDS(const char *sql)
      { fields = cString(sql).trim(); }

   operator cString() const
      { return fields; }

   inline friend FIELDS operator+(const FIELD& f1, const FIELD& f2)
      { return FIELDS(Concat(f1, ",", f2)); }
   inline friend FIELDS operator+(const FIELD& f1, const FIELDS& fs2)
      { return FIELDS(Concat(f1, ",", fs2)); }
   inline friend FIELDS operator+(const FIELDS& fs1, const FIELD& f2)
      { return FIELDS(Concat(fs1, ",", f2)); }
   inline friend FIELDS operator+(const FIELDS& fs1, const FIELDS& fs2)
      { return FIELDS(Concat(fs1, ",", fs2)); }

   int getFieldCount() const;
   FIELD getField(int n) const;
   FIELDS getFieldsFrom(const TABLE& t) const;

   int findField(const FIELD& field, bool no_case = true) const;
   bool hasField(const FIELD& field, bool no_case = true) const;

   void setField(int n, const FIELD& field);

};

#endif /*__INTERFACE__*/


// Implementierung FIELDS
// ===========================================================================

int FIELDS::getFieldCount() const
{
   if ( fields.isEmpty() )
      return 0;

   int count = 1;

   for ( const char *p = fields ; *p ; p++ ) {
      switch ( *p ) {
      case ',':   count++; break;
      case '\'':  p = FindNext(p+1, '\''); break;
      case '(':   p = FindMatching(p+1, ')'); break;
      }
   }

   return count;
}

FIELD FIELDS::getField(int n) const
{
   if ( fields.isEmpty() )
      return FIELD();

   const char *p, *last;

   for ( p = last = fields ; *p ; p++ ) {
      if ( *p == ',' ) {
         if ( n-- == 0 )
            break;
         last = p + 1;
      } else {
         switch ( *p ) {
         case '\'':  p = FindNext(p+1, '\''); break;
         case '(':   p = FindMatching(p+1, ')'); break;
         }
      }
   }

   return FIELD(cString(last, p - last));
}

FIELDS FIELDS::getFieldsFrom(const TABLE& t) const
{
   FIELDS fields;
   cString table_name = t.getTableName();
   cString table_alias = t.getTableAlias();

   for ( int i = getFieldCount() ; i > 0 ; i-- ) {
      FIELD field = getField(i);
      cString ftn = field.getTableName();
      if ( ftn == table_name || ftn == table_alias )
         fields = fields + field;
   }

   return fields;
}

int FIELDS::findField(const FIELD& field, bool no_case) const
{
   int field_count = getFieldCount();
   cString field_to_find = field;

   for ( int i = 0 ; i < field_count ; i++ ) {
      if ( no_case ) {
         if ( field_to_find.compareNoCase(getField(i)) == 0 )
            return i;
      } else {
         if ( field_to_find.compare(getField(i)) == 0 )
            return i;
      }
   }

   return -1;
}

bool FIELDS::hasField(const FIELD& field, bool no_case) const
{
   return findField(field, no_case) >= 0;
}

void FIELDS::setField(int n, const FIELD& field)
{
   FIELDS new_fields;
   int field_count = getFieldCount();

   for ( int i = 0 ; i < max(field_count,n+1) ; i++ ) {
      if ( i == n ) {
         new_fields = new_fields + field;
      } else if ( i >= field_count ) {
         new_fields = new_fields + FIELD("NULL");
      } else {
         new_fields = new_fields + getField(i);
      }
   }

   fields = new_fields;
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition VALUE
// ---------------------------------------------------------------------------
//
// VALUE
//
// ===========================================================================

class __ECL_DLLEXPORT__ VALUE {
   cString value;

public:
   VALUE()
      { }
   VALUE(cString sql)
      { value = sql.trim(); }
   VALUE(const char *sql)
      { value = cString(sql).trim(); }

   operator cString() const
      { return value; }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition VALUES
// ---------------------------------------------------------------------------
//
// VALUES
//
// ===========================================================================

class __ECL_DLLEXPORT__ VALUES {
   cString values;

public:
   VALUES()
      { }
   VALUES(cString sql)
      { values = sql.trim(); }
   VALUES(const char *sql)
      { values = cString(sql).trim(); }

   operator cString() const
      { return values; }

   inline friend VALUES operator+(const VALUE& v1, const VALUE& v2)
      { return VALUES(Concat(v1, ",", v2)); }
   inline friend VALUES operator+(const VALUE& v1, const VALUES& vs2)
      { return VALUES(Concat(v1, ",", vs2)); }
   inline friend VALUES operator+(const VALUES& vs1, const VALUE& v2)
      { return VALUES(Concat(vs1, ",", v2)); }
   inline friend VALUES operator+(const VALUES& vs1, const VALUES& vs2)
      { return VALUES(Concat(vs1, ",", vs2)); }

   int getValueCount() const;
   VALUE getValue(int n) const;

};

#endif /*__INTERFACE__*/


// Implementierung VALUES
// ===========================================================================

int VALUES::getValueCount() const
{
   if ( values.isEmpty() )
      return 0;

   int count = 1;

   for ( const char *p = values ; *p ; p++ ) {
      switch ( *p ) {
      case ',':   count++; break;
      case '\'':  p = FindNext(p+1, '\''); break;
      case '(':   p = FindMatching(p+1, ')'); break;
      }
   }

   return count;
}

VALUE VALUES::getValue(int n) const
{
   if ( values.isEmpty() )
      return VALUE();

   const char *p, *last;

   for ( p = last = values ; *p ; p++ ) {
      if ( *p == ',' ) {
         if ( n-- == 0 )
            break;
         last = p + 1;
      } else {
         switch ( *p ) {
         case '\'':  p = FindNext(p+1, '\''); break;
         case '(':   p = FindMatching(p+1, ')'); break;
         }
      }
   }

   return VALUE(cString(last, p - last));
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition GROUPBY
// ---------------------------------------------------------------------------
//
// GROUPBY
//
// ===========================================================================

class __ECL_DLLEXPORT__ GROUPBY : public FIELDS {

public:
   GROUPBY()
      { }
   GROUPBY(cString sql) : FIELDS(sql)
      { }
   GROUPBY(const char *sql) : FIELDS(sql)
      { }

   inline friend GROUPBY operator+(const FIELD& f1, const GROUPBY& fs2)
      { return GROUPBY(Concat(f1, ",", fs2)); }
   inline friend GROUPBY operator+(const GROUPBY& fs1, const FIELD& f2)
      { return GROUPBY(Concat(fs1, ",", f2)); }
   inline friend GROUPBY operator+(const GROUPBY& fs1, const GROUPBY& fs2)
      { return GROUPBY(Concat(fs1, ",", fs2)); }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition ORDERBY
// ---------------------------------------------------------------------------
//
// ORDERBY
//
// ===========================================================================

class __ECL_DLLEXPORT__ ORDERBY : public FIELDS {

public:
   ORDERBY()
      { }
   ORDERBY(cString sql) : FIELDS(sql)
      { }
   ORDERBY(const char *sql) : FIELDS(sql)
      { }

   inline friend ORDERBY operator+(const FIELD& f1, const ORDERBY& fs2)
      { return ORDERBY(Concat(f1, ",", fs2)); }
   inline friend ORDERBY operator+(const ORDERBY& fs1, const FIELD& f2)
      { return ORDERBY(Concat(fs1, ",", f2)); }
   inline friend ORDERBY operator+(const ORDERBY& fs1, const ORDERBY& fs2)
      { return ORDERBY(Concat(fs1, ",", fs2)); }

};

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition HINT
// ---------------------------------------------------------------------------
//
// HINT
//
// ===========================================================================

class __ECL_DLLEXPORT__ HINT {
   cString hint;

public:
   HINT()
      { }
   HINT(cString sql)
      { hint = sql; }
   HINT(const char *sql)
      { hint = cString(sql).trim(); }

   operator cString() const
      { return hint; }

   cString getName() const;
   cString getValue() const;

};

#endif /*__INTERFACE__*/


// Implementierung HINT
// ===========================================================================

cString HINT::getName() const
{
   int pos = PosNoCase(hint, "=");
   if ( pos > 0 ) {
      return hint.getLeft(pos);
   } else {
      return hint;
   }
}

cString HINT::getValue() const
{
   int pos = PosNoCase(hint, "=");
   if ( pos > 0 ) {
      return hint.getMid(pos + 1);
   } else {
      return cString();
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition HINTS
// ---------------------------------------------------------------------------
//
// HINTS
//
// ===========================================================================

class __ECL_DLLEXPORT__ HINTS {
   cString hints;

public:
   HINTS()
      { }
   HINTS(cString sql)
      { hints = sql.trim(); }
   HINTS(const char *sql)
      { hints = cString(sql).trim(); }

   operator cString() const
      { return hints; }

   inline friend HINTS operator+(const HINT& f1, const HINT& f2)
      { return HINTS(Concat(f1, ",", f2)); }
   inline friend HINTS operator+(const HINT& f1, const HINTS& fs2)
      { return HINTS(Concat(f1, ",", fs2)); }
   inline friend HINTS operator+(const HINTS& fs1, const HINT& f2)
      { return HINTS(Concat(fs1, ",", f2)); }
   inline friend HINTS operator+(const HINTS& fs1, const HINTS& fs2)
      { return HINTS(Concat(fs1, ",", fs2)); }

   int getHintCount() const;
   HINT getHint(int n) const;
   HINT getHint(cString hint_name) const;

};

#endif /*__INTERFACE__*/


// Implementierung HINTS
// ===========================================================================

int HINTS::getHintCount() const
{
   if ( hints.isEmpty() )
      return 0;

   int count = 1;

   for ( const char *p = hints ; *p ; p++ ) {
      switch ( *p ) {
      case ',':   count++; break;
      case '\'':  p = FindNext(p+1, '\''); break;
      case '(':   p = FindMatching(p+1, ')'); break;
      }
   }

   return count;
}

HINT HINTS::getHint(int n) const
{
   if ( hints.isEmpty() )
      return HINT();

   const char *p, *last;

   for ( p = last = hints ; *p ; p++ ) {
      if ( *p == ',' ) {
         if ( n-- == 0 )
            break;
         last = p + 1;
      } else {
         switch ( *p ) {
         case '\'':  p = FindNext(p+1, '\''); break;
         case '(':   p = FindMatching(p+1, ')'); break;
         }
      }
   }

   return HINT(cString(last, p - last));
}

HINT HINTS::getHint(cString hint_name) const
{
   for ( int i = 0 ; i < getHintCount() ; i++ ) {
      HINT hint = getHint(i);
      if ( hint.getName().compareNoCase(hint_name) == 0 )
         return hint;
   }

   return HINT();
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition SELECT
// ---------------------------------------------------------------------------
//
// SELECT [ALL|DISTINCT]
//    fields
//    FROM tables
//    [WHERE condition]
//    [ORDER BY fields]
//    [GROUP BY fields]
//
// ===========================================================================

enum SELECT_STYLE { STYLE_NONE, STYLE_ALL, STYLE_DISTINCT };

class __ECL_DLLEXPORT__ SELECT {
   cString select;

public:
   SELECT()
      { }
   SELECT(cString sql)
      { select = sql.trim(); }
   SELECT(const char *sql)
      { select = cString(sql).trim(); }
   SELECT(SELECT_STYLE style,
          const HINTS& hints,
          const FIELDS& fields,
          const FROM& tables,
          const WHERE& conds = WHERE(),
          const GROUPBY& groups = GROUPBY(),
          const ORDERBY& orders = ORDERBY());
   SELECT(SELECT_STYLE style,
          const FIELDS& fields,
          const FROM& tables,
          const WHERE& conds = WHERE(),
          const GROUPBY& groups = GROUPBY(),
          const ORDERBY& orders = ORDERBY());
   SELECT(const HINTS& hints,
          const FIELDS& fields,
          const FROM& tables,
          const WHERE& conds = WHERE(),
          const GROUPBY& groups = GROUPBY(),
          const ORDERBY& orders = ORDERBY());
   SELECT(const FIELDS& fields,
          const FROM& tables,
          const WHERE& conds = WHERE(),
          const GROUPBY& groups = GROUPBY(),
          const ORDERBY& orders = ORDERBY());

   operator cString() const
      { return select; }

   inline friend SELECT operator+(const SELECT& s, const HINT& h)
      { SELECT sn(s); sn.setHints(sn.getHints() + h); return sn; }
   inline friend SELECT operator+(const SELECT& s, const FIELD& f)
      { SELECT sn(s); sn.setFields(sn.getFields() + f); return sn; }
   inline friend SELECT operator+(const SELECT& s, const FROM& f)
      { SELECT sn(s); sn.setFrom(sn.getFrom() + f); return sn; }
   inline friend SELECT operator+(const SELECT& s, const GROUPBY& o)
      { SELECT sn(s); sn.setGroupBy(sn.getGroupBy() + o); return sn; }
   inline friend SELECT operator+(const SELECT& s, const ORDERBY& o)
      { SELECT sn(s); sn.setOrderBy(sn.getOrderBy() + o); return sn; }

   inline friend SELECT operator&(const SELECT& s, const WHERE& w)
      { SELECT sn(s); sn.setWhere(sn.getWhere() & w); return sn; }
   inline friend SELECT operator|(const SELECT& s, const WHERE& w)
      { SELECT sn(s); sn.setWhere(sn.getWhere() | w); return sn; }

   SELECT_STYLE getStyle() const;
   HINTS getHints() const;
   FIELDS getFields() const;
   FROM getFrom() const;
   WHERE getWhere() const;
   GROUPBY getGroupBy() const;
   ORDERBY getOrderBy() const;

   void setStyle(SELECT_STYLE style);
   void setHints(const HINTS& hints);
   void setFields(const FIELDS& fields);
   void setFrom(const FROM& from);
   void setWhere(const WHERE& where);
   void setGroupBy(const GROUPBY& groupby);
   void setOrderBy(const ORDERBY& orderby);

private:
   void init(SELECT_STYLE style,
             const HINTS& hints,
             const FIELDS& fields,
             const FROM& tables,
             const WHERE& conds,
             const GROUPBY& groups,
             const ORDERBY& orders);

};

#endif /*__INTERFACE__*/


// Implementierung SELECT
// ===========================================================================

SELECT::SELECT(SELECT_STYLE style, const HINTS& hints, const FIELDS& fields, const FROM& tables,
   const WHERE& conds, const GROUPBY& groups, const ORDERBY& orders)
{
   init(style, hints, fields, tables, conds, groups, orders);
}

SELECT::SELECT(SELECT_STYLE style, const FIELDS& fields, const FROM& tables, const WHERE& conds,
   const GROUPBY& groups, const ORDERBY& orders)
{
   init(style, HINTS(), fields, tables, conds, groups, orders);
}

SELECT::SELECT(const HINTS& hints, const FIELDS& fields, const FROM& tables, const WHERE& conds,
   const GROUPBY& groups, const ORDERBY& orders)
{
   init(STYLE_NONE, hints, fields, tables, conds, groups, orders);
}

SELECT::SELECT(const FIELDS& fields, const FROM& tables, const WHERE& conds,
   const GROUPBY& groups, const ORDERBY& orders)
{
   init(STYLE_NONE, HINTS(), fields, tables, conds, groups, orders);
}

void SELECT::init(SELECT_STYLE style, const HINTS& hints, const FIELDS& fields,
   const FROM& tables, const WHERE& conds, const GROUPBY& groups, const ORDERBY& orders)
{
   static const char *styles[] = { "", "ALL", "DISTINCT" };

   select = "SELECT ";

   if ( hints.getHintCount() > 0 )
      select += "{" + cString(hints) + "} ";

   if ( style != STYLE_NONE )
      select += cString(styles[style]) + " ";

   select += cString(fields) + " FROM " + cString(tables);

   if ( conds.getCondCount() > 0 )
      select += " WHERE " + cString(conds);
   if ( groups.getFieldCount() > 0 )
      select += " GROUP BY " + cString(groups);
   if ( orders.getFieldCount() > 0 )
      select += " ORDER BY " + cString(orders);
}

SELECT_STYLE SELECT::getStyle() const
{
   if ( PosNoCase(select, " ALL ") >= 0 )
      return STYLE_ALL;
   if ( PosNoCase(select, " DISTINCT ") >= 0 )
      return STYLE_DISTINCT;
   return STYLE_NONE;
}

HINTS SELECT::getHints() const
{
   cString hints;
   int from_pos = PosNoCase(select, " FROM");

   if ( from_pos > 0 ) {
      hints = select.getLeft(from_pos);
   } else {
      hints = select;
   }

   if ( hints.compareNoCase("SELECT ", 7) == 0 )
      hints = hints.del(0,6).trim();

   if ( hints[0] == '{' && hints.getMid(1,2) != "fn" ) {
      hints = hints.del(0,1).trim();
      int hint_end = PosNoCase(hints, "}");
      return hints.getMid(0, hint_end).trim();
   }

   return cString();
}

FIELDS SELECT::getFields() const
{
   cString fields;
   int from_pos = PosNoCase(select, " FROM");

   if ( from_pos > 0 ) {
      fields = select.getLeft(from_pos);
   } else {
      fields = select;
   }

   if ( fields.compareNoCase("SELECT ", 7) == 0 )
      fields = fields.del(0,6).trim();

   if ( fields[0] == '{' && fields.getMid(1,2) != "fn" ) {
      fields = fields.del(0,1).trim();
      int hint_end = PosNoCase(fields, "}");
      if ( hint_end >= 0 ) {
         fields = fields.getMid(hint_end+1).trim();
      } else {
         fields.clear();
      }
   }

   if ( fields.compareNoCase("ALL ", 4) == 0 )
      fields = fields.del(0,3).trim();

   if ( fields.compareNoCase("DISTINCT ", 9) == 0 )
      fields = fields.del(0,8).trim();

   return fields;
}

FROM SELECT::getFrom() const
{
   int prev_pos = PosNoCase(select, " FROM ");
   int next_pos = PosNoCase(select, " WHERE ");

   if ( prev_pos < 0 ) {
      return FROM();
   } else {
      prev_pos += 6;
   }

   if ( next_pos < 0 )
      next_pos = PosNoCase(select, " ORDER BY ");
   if ( next_pos < 0 )
      next_pos = PosNoCase(select, " GROUP BY ");

   if ( next_pos < 0 ) {
      return select.getRight(select.getLength() - prev_pos);
   } else {
      return select.getMid(prev_pos, next_pos - prev_pos);
   }
}

WHERE SELECT::getWhere() const
{
   int prev_pos = PosNoCase(select, " WHERE ");
   int next_pos = PosNoCase(select, " GROUP BY ");

   if ( prev_pos < 0 ) {
      return WHERE();
   } else {
      prev_pos += 7;
   }

   if ( next_pos < 0 )
      next_pos = PosNoCase(select, " ORDER BY ");

   if ( next_pos < 0 ) {
      return select.getRight(select.getLength() - prev_pos);
   } else {
      return select.getMid(prev_pos, next_pos - prev_pos);
   }
}

GROUPBY SELECT::getGroupBy() const
{
   int prev_pos = PosNoCase(select, " GROUP BY ");
   int next_pos = PosNoCase(select, " ORDER BY ");

   if ( prev_pos < 0 ) {
      return GROUPBY();
   } else {
      prev_pos += 9;
   }

   if ( next_pos < 0 ) {
      return select.getRight(select.getLength() - prev_pos);
   } else {
      return select.getMid(prev_pos, next_pos - prev_pos);
   }
}

ORDERBY SELECT::getOrderBy() const
{
   int prev_pos = PosNoCase(select, " ORDER BY ");

   if ( prev_pos < 0 ) {
      return ORDERBY();
   } else {
      prev_pos += 9;
   }

   return select.getRight(select.getLength() - prev_pos);
}

void SELECT::setStyle(SELECT_STYLE style)
   { select = SQL::SELECT(style, getHints(), getFields(), getFrom(), getWhere(), getGroupBy(), getOrderBy()); }

void SELECT::setHints(const HINTS& hints)
   { select = SQL::SELECT(getStyle(), hints, getFields(), getFrom(), getWhere(), getGroupBy(), getOrderBy()); }

void SELECT::setFields(const FIELDS& fields)
   { select = SQL::SELECT(getStyle(), getHints(), fields, getFrom(), getWhere(), getGroupBy(), getOrderBy()); }

void SELECT::setFrom(const FROM& from)
   { select = SQL::SELECT(getStyle(), getHints(), getFields(), from, getWhere(), getGroupBy(), getOrderBy()); }

void SELECT::setWhere(const WHERE& where)
   { select = SQL::SELECT(getStyle(), getHints(), getFields(), getFrom(), where, getGroupBy(), getOrderBy()); }

void SELECT::setGroupBy(const GROUPBY& groupby)
   { select = SQL::SELECT(getStyle(), getHints(), getFields(), getFrom(), getWhere(), groupby, getOrderBy()); }

void SELECT::setOrderBy(const ORDERBY& orderby)
   { select = SQL::SELECT(getStyle(), getHints(), getFields(), getFrom(), getWhere(), getGroupBy(), orderby); }




#ifdef __INTERFACE__

// ===========================================================================
// Definition INSERT
// ---------------------------------------------------------------------------
//
// INSERT INTO table [(fields)]
//    [VALUES (values) | SELECT ...]
//
// ===========================================================================

class __ECL_DLLEXPORT__ INSERT {
   cString insert;

public:
   INSERT()
      { }
   INSERT(cString sql)
      { insert = sql.trim(); }
   INSERT(const char *sql)
      { insert = cString(sql).trim(); }
   INSERT(const TABLE& table,
          const FIELDS& fields,
          const VALUES& values);
   INSERT(const TABLE& hints,
          const FIELDS& fields,
          const SELECT& select);
   INSERT(const TABLE& table,
          const VALUES& values);
   INSERT(const TABLE& hints,
          const SELECT& select);

   operator cString() const
      { return insert; }

   inline friend INSERT operator+(const INSERT& i, const FIELD& f)
      { INSERT in(i); in.setFields(in.getFields() + f); return in; }
   inline friend INSERT operator+(const INSERT& i, const VALUE& v)
      { INSERT in(i); in.setValues(in.getValues() + v); return in; }

   TABLE getTable() const;
   FIELDS getFields() const;
   VALUES getValues() const;
   SELECT getSelect() const;

   void setTable(TABLE table);
   void setFields(const FIELDS& fields);
   void setValues(const VALUES& values);
   void setSelect(const SELECT& select);

private:
   void init(const TABLE& table,
             const FIELDS& fields,
             const VALUES& values,
             const SELECT& select);

   INSERT(const TABLE& table,
          const FIELDS& fields,
          const VALUES& values,
          const SELECT& select);

};

#endif /*__INTERFACE__*/


// Implementierung INSERT
// ===========================================================================

INSERT::INSERT(const TABLE& table, const FIELDS& fields,
   const VALUES& values, const SELECT& select)
{
   init(table, fields, values, select);
}

INSERT::INSERT(const TABLE& table, const FIELDS& fields, const VALUES& values)
{
   init(table, fields, values, SELECT());
}

INSERT::INSERT(const TABLE& table, const FIELDS& fields, const SELECT& select)
{
   init(table, fields, VALUES(), select);
}

INSERT::INSERT(const TABLE& table, const VALUES& values)
{
   init(table, FIELDS(), values, SELECT());
}

INSERT::INSERT(const TABLE& table, const SELECT& select)
{
   init(table, FIELDS(), VALUES(), select);
}

void INSERT::init(const TABLE& table, const FIELDS& fields,
   const VALUES& values, const SELECT& select)
{
   insert = "INSERT INTO " + cString(table);

   if ( fields.getFieldCount() > 0 )
      insert += "(" + cString(fields) + ")";
   if ( values.getValueCount() > 0 )
      insert += " VALUES(" + cString(values) + ")";
   if ( !cString(select).isEmpty() )
      insert += " " + cString(select);
}

TABLE INSERT::getTable() const
{
   int prev_pos = PosNoCase(insert, " INTO");

   if ( prev_pos < 0 ) {
      return TABLE();
   } else {
      prev_pos += 5;
   }

   const char *search[] = { "(", " VALUES", " SELECT " };
   int count = 3;
   int next_pos = PosNoCase((const char *)insert + prev_pos, search, count);

   if ( next_pos < 0 ) {
      return insert.getRight(insert.getLength() - prev_pos).trim();
   } else {
      return insert.getMid(prev_pos, next_pos).trim();
   }
}

FIELDS INSERT::getFields() const
{
   const char *search[] = { "(", " VALUES", " SELECT " };
   int count = 3;
   int prev_pos = PosNoCase(insert, search, count);

   if ( prev_pos < 0 || insert[prev_pos] != '(' ) {
      return FIELDS();
   } else {
      prev_pos += 1;
   }

   int next_pos = PosNoCase((const char *)insert + prev_pos, ")");

   if ( next_pos < 0 ) {
      return insert.getRight(insert.getLength() - prev_pos).trim();
   } else {
      return insert.getMid(prev_pos, next_pos).trim();
   }
}

VALUES INSERT::getValues() const
{
   int prev_pos = PosNoCase(insert, " VALUES");

   if ( prev_pos < 0 ) {
      return VALUES();
   } else {
      prev_pos += 7;
   }

   while ( insert[prev_pos] == ' ' )
      prev_pos++;

   if ( insert[prev_pos] != '(' ) {
      return VALUES();
   } else {
      prev_pos += 1;
   }

   int next_pos = PosNoCase((const char *)insert + prev_pos, ")");

   if ( next_pos < 0 ) {
      return insert.getRight(insert.getLength() - prev_pos).trim();
   } else {
      return insert.getMid(prev_pos, next_pos).trim();
   }
}

SELECT INSERT::getSelect() const
{
   int prev_pos = PosNoCase(insert, " SELECT ");

   if ( prev_pos < 0 ) {
      return SELECT();
   } else {
      prev_pos += 1; // Beginn von SELECT-Schluesselwort
   }

   return insert.getRight(insert.getLength() - prev_pos).trim();
}

void INSERT::setTable(TABLE table)
   { insert = SQL::INSERT(table, getFields(), getValues(), getSelect()); }

void INSERT::setFields(const FIELDS& fields)
   { insert = SQL::INSERT(getTable(), fields, getValues(), getSelect()); }

void INSERT::setValues(const VALUES& values)
   { insert = SQL::INSERT(getTable(), getFields(), values, getSelect()); }

void INSERT::setSelect(const SELECT& select)
   { insert = SQL::INSERT(getTable(), getFields(), getValues(), select); }




#ifdef __INTERFACE__

// ===========================================================================
// Definition UPDATE
// ---------------------------------------------------------------------------
//
// UPDATE table
//    SET field=value {,field=value}
//    [WHERE where]
//
// ===========================================================================

class __ECL_DLLEXPORT__ UPDATE {
   cString update;

public:
   UPDATE()
      { }
   UPDATE(cString sql)
      { update = sql.trim(); }
   UPDATE(const char *sql)
      { update = cString(sql).trim(); }
   UPDATE(const TABLE& table,
          const SET& set,
          const WHERE& where = WHERE());

   operator cString() const
      { return update; }

   inline friend UPDATE operator+(const UPDATE& u, const SET& s)
      { UPDATE un(u); un.setSet(un.getSet() + s); return un; }

   inline friend UPDATE operator&(const UPDATE& u, const WHERE& w)
      { UPDATE un(u); un.setWhere(un.getWhere() & w); return un; }
   inline friend UPDATE operator|(const UPDATE& u, const WHERE& w)
      { UPDATE un(u); un.setWhere(un.getWhere() | w); return un; }

   TABLE getTable() const;
   SET getSet() const;
   WHERE getWhere() const;

   void setTable(TABLE table);
   void setSet(const SET& set);
   void setWhere(const WHERE& where);

private:
   void init(const TABLE& table,
             const SET& set,
             const WHERE& where);

};

#endif /*__INTERFACE__*/


// Implementierung UPDATE
// ===========================================================================

UPDATE::UPDATE(const TABLE& table, const SET& set, const WHERE& where)
{
   init(table, set, where);
}

void UPDATE::init(const TABLE& table, const SET& set, const WHERE& where)
{
   update = "UPDATE " + table.getTableName() + " SET " + cString(set);

   // Problemfall: In TABLE oder WHERE-Bedingung tauchen Aliasnamen auf.
   // Oracle hat damit kein Problem, aber SQL-Server meckert rum. Daher
   // versuchen, wenigstens die Standardfaelle abzufangen und die Aliase
   // zu entfernen.

   if ( where.getCondCount() > 0 ) {
      cString alias = table.getTableAlias();
      if ( alias.isEmpty() ) {
         update += " WHERE " + cString(where);
      } else {
         cString cond = where, prefix = alias + ".";
         for ( int pos ; (pos = cond.getPosNoCase(prefix, "'\"{")) >= 0 ; )
            cond = cond.getLeft(pos) + cond.getMid(pos + prefix.getLength());
         update += " WHERE " + cond;
      }
   }
}

TABLE UPDATE::getTable() const
{
   int prev_pos = PosNoCase(update, "UPDATE ");

   if ( prev_pos < 0 ) {
      return TABLE();
   } else {
      prev_pos += 7;
   }

   int next_pos = PosNoCase(update, " SET ");

   if ( next_pos < 0 ) {
      return update.getRight(update.getLength() - prev_pos).trim();
   } else {
      return update.getMid(prev_pos, next_pos - prev_pos).trim();
   }
}

SET UPDATE::getSet() const
{
   int prev_pos = PosNoCase(update, " SET ");

   if ( prev_pos < 0 ) {
      return SET();
   } else {
      prev_pos += 5;
   }

   int next_pos = PosNoCase(update, " WHERE ");

   if ( next_pos < 0 ) {
      return update.getRight(update.getLength() - prev_pos).trim();
   } else {
      return update.getMid(prev_pos, next_pos - prev_pos).trim();
   }
}

WHERE UPDATE::getWhere() const
{
   int prev_pos = PosNoCase(update, " WHERE ");

   if ( prev_pos < 0 ) {
      return WHERE();
   } else {
      prev_pos += 7;
   }

   return update.getRight(update.getLength() - prev_pos).trim();
}

void UPDATE::setTable(TABLE table)
   { update = SQL::UPDATE(table, getSet(), getWhere()); }

void UPDATE::setSet(const SET& set)
   { update = SQL::UPDATE(getTable(), set, getWhere()); }

void UPDATE::setWhere(const WHERE& where)
   { update = SQL::UPDATE(getTable(), getSet(), where); }




#ifdef __INTERFACE__

// ===========================================================================
// Definition DELETE
// ---------------------------------------------------------------------------
//
// DELETE FROM table
//    [WHERE where]
//
// ===========================================================================

class __ECL_DLLEXPORT__ DELETE {
   cString delstr;

public:
   DELETE()
      { }
   DELETE(cString sql)
      { delstr = sql.trim(); }
   DELETE(const char *sql)
      { delstr = cString(sql).trim(); }
   DELETE(const TABLE& table,
          const WHERE& where = WHERE());

   operator cString() const
      { return delstr; }

   inline friend DELETE operator&(const DELETE& d, const WHERE& w)
      { DELETE dn(d); dn.setWhere(dn.getWhere() & w); return dn; }
   inline friend DELETE operator|(const DELETE& d, const WHERE& w)
      { DELETE dn(d); dn.setWhere(dn.getWhere() | w); return dn; }

   TABLE getTable() const;
   WHERE getWhere() const;

   void setTable(TABLE table);
   void setWhere(const WHERE& where);

private:
   void init(const TABLE& table,
             const WHERE& where);

};

#endif /*__INTERFACE__*/


// Implementierung DELETE
// ===========================================================================

DELETE::DELETE(const TABLE& table, const WHERE& where)
{
   init(table, where);
}

void DELETE::init(const TABLE& table, const WHERE& where)
{
   delstr = "DELETE FROM " + table.getTableName();

   // Problemfall: In TABLE oder WHERE-Bedingung tauchen Aliasnamen auf.
   // Oracle hat damit kein Problem, aber SQL-Server meckert rum. Daher
   // versuchen, wenigstens die Standardfaelle abzufangen und die Aliase
   // zu entfernen.

   if ( where.getCondCount() > 0 ) {
      cString alias = table.getTableAlias();
      if ( alias.isEmpty() ) {
         delstr += " WHERE " + cString(where);
      } else {
         cString cond = where, prefix = alias + ".";
         for ( int pos ; (pos = cond.getPosNoCase(prefix, "'\"{")) >= 0 ; )
            cond = cond.getLeft(pos) + cond.getMid(pos + prefix.getLength());
         delstr += " WHERE " + cond;
      }
   }
}

TABLE DELETE::getTable() const
{
   int prev_pos = PosNoCase(delstr, " FROM ");

   if ( prev_pos < 0 ) {
      return TABLE();
   } else {
      prev_pos += 6;
   }

   int next_pos = PosNoCase(delstr, " WHERE ");

   if ( next_pos < 0 ) {
      return delstr.getRight(delstr.getLength() - prev_pos).trim();
   } else {
      return delstr.getMid(prev_pos, next_pos - prev_pos).trim();
   }
}

WHERE DELETE::getWhere() const
{
   int prev_pos = PosNoCase(delstr, " WHERE ");

   if ( prev_pos < 0 ) {
      return WHERE();
   } else {
      prev_pos += 7;
   }

   return delstr.getRight(delstr.getLength() - prev_pos).trim();
}

void DELETE::setTable(TABLE table)
   { delstr = SQL::DELETE(table, getWhere()); }

void DELETE::setWhere(const WHERE& where)
   { delstr = SQL::DELETE(getTable(), where); }




#ifdef __INTERFACE__

// ===========================================================================
// Definition STMT
// ---------------------------------------------------------------------------
//
// STMT
//
// ===========================================================================

enum STMT_TYPE { STMT_NONE, STMT_SELECT, STMT_INSERT, STMT_UPDATE, STMT_DELETE };

class __ECL_DLLEXPORT__ STMT {
   cString stmt;

public:
   STMT()
      { }
   STMT(const cString& sql)
      { stmt = sql.trim(); }
   STMT(const char *sql)
      { stmt = cString(sql).trim(); }
   STMT(const SELECT& sql)
      { stmt = cString(sql).trim(); }
   STMT(const INSERT& sql)
      { stmt = cString(sql).trim(); }
   STMT(const UPDATE& sql)
      { stmt = cString(sql).trim(); }
   STMT(const DELETE& sql)
      { stmt = cString(sql).trim(); }

   operator cString() const
      { return stmt; }

   STMT_TYPE getType() const;
   HINTS getHints() const;
   WHERE getWhere() const;

   void setHints(const HINTS& hints);
   void setWhere(const WHERE& where);

};

#endif /*__INTERFACE__*/


// Implementierung STMT
// ===========================================================================

STMT_TYPE STMT::getType() const
{
   if ( stmt.compareNoCase("SELECT ", 7) == 0 )
      return STMT_SELECT;
   if ( stmt.compareNoCase("INSERT ", 7) == 0 )
      return STMT_INSERT;
   if ( stmt.compareNoCase("UPDATE ", 7) == 0 )
      return STMT_UPDATE;
   if ( stmt.compareNoCase("DELETE ", 7) == 0 )
      return STMT_DELETE;
   return STMT_NONE;
}

HINTS STMT::getHints() const
{
   switch ( getType() ) {
   case STMT_SELECT:
      return SELECT(stmt).getHints();
   case STMT_INSERT:
      return HINTS();
   case STMT_UPDATE:
      return HINTS();
   case STMT_DELETE:
      return HINTS();
   default:
      return HINTS();
   }
}

WHERE STMT::getWhere() const
{
   switch ( getType() ) {
   case STMT_SELECT:
      return SELECT(stmt).getWhere();
   case STMT_INSERT:
      return WHERE();
   case STMT_UPDATE:
      return WHERE();
   case STMT_DELETE:
      return WHERE();
   default:
      return WHERE();
   }
}

void STMT::setHints(const HINTS& hints)
{
   switch ( getType() ) {
   case STMT_SELECT:
      { SELECT sn = SELECT(stmt); sn.setHints(hints); stmt = sn; }
      break;
   case STMT_INSERT:
      break;
   case STMT_UPDATE:
      break;
   case STMT_DELETE:
      break;
   }
}

void STMT::setWhere(const WHERE& where)
{
   switch ( getType() ) {
   case STMT_SELECT:
      { SELECT sn = SELECT(stmt); sn.setWhere(where); stmt = sn; }
      break;
   case STMT_INSERT:
      break;
   case STMT_UPDATE:
      break;
   case STMT_DELETE:
      break;
   }
}




/*.SP.*/
}; /* namespace SQL*/
/*.EP.*/

