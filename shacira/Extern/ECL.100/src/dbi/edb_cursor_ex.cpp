// ===========================================================================
// edb_cursor_ex.cpp                                            ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cdbCursor                -
//         |
//         +--cdbCursorEx          -
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */

#include "dbi/edb_cursor_ex.hpp"
#include "base/eb_array.hpp"
#include "store/es_var.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_store.hpp"
#include "dbi/edb_cursor.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition cdbCursorEx
// ---------------------------------------------------------------------------
//
// cBase
//  +--cdbCursor
//      +--cdbCursorEx
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbCursorEx : public cdbCursor {

public:
   cdbCursorEx(cdbDatabase& db, int prefetch_count = 1);
   cdbCursorEx(const cdbCursor& cursor, int prefetch_count = -1);
   cdbCursorEx(const cdbCursorEx& other, int prefetch_count = -1);
   ~cdbCursorEx();


   // Ausfuehrungskontrolle
   // =====================

   // SQL-Anweisung ausfuehren (nach dem Binden von Variablen)
   void exec();
   // SQL-Anweisung direkt ausfuehren (ohne gebundene Variablen)
   void exec(SQL::STMT sql_str);


   // Feld- (=Spalten-) beschreibung
   // ==============================
   // Diese Eigenschaften stehen fruehestens nach dem Aufruf
   // von exec() zur Verfuegung.

   // Ermittelt die Anzahl der Felder im Datensatz
   int getFieldCount() const;

   // Ermittelt den Typ eines Feldes
   csStorage::TYPE getFieldType(int fld) const;
   // Ermittelt die maximale Groesse eines Feldes
   int getFieldBufferSize(int fld) const;
   // Label des Feldes erfragen
   cString getFieldLabel(int fld) const;
   // Ermittelt den Namen eines Feldes
   cString getFieldName(int fld) const;
   // Ermittelt den Namen des Feldes in der Basistabelle
   cString getFieldBaseName(int fld) const;
   // Ermittelt den Namen der Basistabelle
   cString getFieldBaseTableName(int fld) const;

   // Maximale Feldbreite [Zeichen]
   int getFieldWidth(int fld) const;
   // Anzahl Nachkommastellen [Zeichen]
   int getFieldPrec(int fld) const;

   // Titel der Spalte
   cString getTitleText(int fld) const;


   // Erfragefunktionen fuer aktuellen Datensatz
   // ==========================================

   // Ermittelt den NULL-Wert des Feldes
   bool isNull(int fld) const;

   // Ermittelt den int-Wert eines Feldes
   bool get(int fld, int& buf) const;
   // Ermittelt den double-Wert eines Feldes
   bool get(int fld, double& buf) const;
   // Ermittelt den cTime-Wert eines Feldes
   bool get(int fld, cTime& buf) const;
   // Ermittelt den cDate-Wert eines Feldes
   bool get(int fld, cDate& buf) const;
   // Ermittelt den cDateTime-Wert eines Feldes
   bool get(int fld, cDateTime& buf) const;
   // Ermittelt den char-Wert eines Feldes
   bool get(int fld, char& buf) const;
   // Ermittelt den cString-Wert eines Feldes
   bool get(int fld, cString& buf) const;


private:
   void *vars;
   void redefineVars();

};

#endif /*__INTERFACE__*/


// Implementierung cdbCursorEx
// ===========================================================================

class VAR {
public:
   VAR() { var = 0; }
   ~VAR() { delete var; }
   csVar *var;
};

typedef cArray<VAR,const VAR&> VAR_ARRAY;


// Konstruktoren
// =============

cdbCursorEx::cdbCursorEx(cdbDatabase& db, int prefetch_count) :
   cdbCursor(db, prefetch_count)
{
   vars = new0 VAR_ARRAY;
}

cdbCursorEx::cdbCursorEx(const cdbCursor& cursor, int prefetch_count) :
   cdbCursor(cursor, prefetch_count)
{
   vars = new0 VAR_ARRAY;
}

cdbCursorEx::cdbCursorEx(const cdbCursorEx& other, int prefetch_count) :
   cdbCursor(other, prefetch_count)
{
   vars = new0 VAR_ARRAY;
}

cdbCursorEx::~cdbCursorEx()
{
   // Wichtig: Der Cast sorgt fuer das Aufrufen der Destruktoren
   // der einzelnen VAR-Elemente!!!
   delete (VAR_ARRAY*)vars;
}


// Ausfuehrungskontrolle
// =====================

void cdbCursorEx::exec()
{
   cdbCursor::exec();
   redefineVars();
}

void cdbCursorEx::exec(SQL::STMT sql_str)
{
   cdbCursor::exec(sql_str);
   redefineVars();
}


// Ergebnisvariablen binden
// ========================

static void redefineVarInt(cdbCursorEx *cu, int n, VAR& var)
{
   int width = cu->getFieldSize(n);

   if ( var.var == 0 || var.var->getType() != csVar::tInt
     || var.var->getWidth() != width )
   {
      delete var.var;
      var.var = new0 csVarInt(0, width);
   }

   cu->define(n, *var.var);
}

static void redefineVarDouble(cdbCursorEx *cu, int n, VAR& var)
{
   // Darstellungsinformationen aus Datenbank ermitteln.

   // Achtung: Die Anzeige des Tausender-Separators wird davon abhaengig
   // gemacht, ob Nachkommastellen angezeigt werden oder nicht. Das muss
   // nicht unbedingt immer gewuenscht sein!

   int width = cu->getFieldSize(n);
   int prec = cu->getFieldDigits(n);
   int flags = prec > 0 ? csVar::fThousandSep : 0;

   if ( var.var == 0 || var.var->getType() != csVar::tDouble
     || var.var->getWidth() != width || var.var->getPrec() != prec
     || var.var->getFlags(csVar::fThousandSep) != flags )
   {
      delete var.var;
      var.var = new0 csVarDouble(0.0, width, prec, flags);
   }

   cu->define(n, *var.var);
}

static void redefineVarChar(cdbCursorEx *cu, int n, VAR& var)
{
   if ( var.var == 0 || var.var->getType() != csVar::tChar ) {
      delete var.var;
      var.var = new0 csVarChar();
   }

   cu->define(n, *var.var);
}

static void redefineVarString(cdbCursorEx *cu, int n, VAR& var)
{
   int buffer_size = cu->getFieldSize(n);

   if ( buffer_size > 4096 )
      buffer_size = 4096;

   if ( var.var == 0 || var.var->getType() != csVar::tChar
     || var.var->getBufferSize() != buffer_size )
   {
      delete var.var;
      var.var = new0 csVarString(buffer_size + 1);
   }

   cu->define(n, *var.var);
}

static void redefineVarDate(cdbCursorEx *cu, int n, VAR& var)
{
   if ( var.var == 0 || var.var->getType() != csVar::tDate ) {
      delete var.var;
      var.var = new0 csVarDate();
   }

   cu->define(n, *var.var);
}

static void redefineVarDateTime(cdbCursorEx *cu, int n, VAR& var)
{
   if ( var.var == 0 || var.var->getType() != csVar::tDateTime ) {
      delete var.var;
      var.var = new0 csVarDateTime();
   }

   cu->define(n, *var.var);
}

static void redefineVarTime(cdbCursorEx *cu, int n, VAR& var)
{
   if ( var.var == 0 || var.var->getType() != csVar::tTime ) {
      delete var.var;
      var.var = new0 csVarTime();
   }

   cu->define(n, *var.var);
}

static void redefineVarDummy(cdbCursorEx *cu, int n, VAR& var)
{
   delete var.var;
   var.var = 0;
   cu->define(n);
}

void cdbCursorEx::redefineVars()
{
   int count = cdbCursor::getFieldCount();
   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   vars.setSize(count);

   for ( int n = 0 ; n < count ; n++ ) {

      switch ( cdbCursor::getFieldType(n) ) {
      case cdbCursor::tShort:       redefineVarInt(this, n, vars[n]);      break;
      case cdbCursor::tLong:        redefineVarInt(this, n, vars[n]);      break;
      case cdbCursor::tFloat:       redefineVarDouble(this, n, vars[n]);   break;
      case cdbCursor::tDouble:      redefineVarDouble(this, n, vars[n]);   break;
      case cdbCursor::tChar:        redefineVarChar(this, n, vars[n]);     break;
      case cdbCursor::tString:      redefineVarString(this, n, vars[n]);   break;
      case cdbCursor::tRowid:       redefineVarDummy(this, n, vars[n]);    break;
      case cdbCursor::tDate:        redefineVarDate(this, n, vars[n]);     break;
      case cdbCursor::tTime:        redefineVarTime(this, n, vars[n]);     break;
      case cdbCursor::tTimeStamp:   redefineVarDateTime(this, n, vars[n]); break;
      default:                      redefineVarDummy(this, n, vars[n]);    break;
      }

   }
}


// Feld- (=Spalten-) beschreibung
// ==============================

int cdbCursorEx::getFieldCount() const
{
   return cdbCursor::getFieldCount();
}

csStorage::TYPE cdbCursorEx::getFieldType(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 )
         return csStorage::tString;
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   switch ( cdbCursor::getFieldType(fld) ) {
   case cdbCursor::tShort:       return csStorage::tInt;
   case cdbCursor::tLong:        return csStorage::tInt;
   case cdbCursor::tFloat:       return csStorage::tDouble;
   case cdbCursor::tDouble:      return csStorage::tDouble;
   case cdbCursor::tChar:        return csStorage::tChar;
   case cdbCursor::tString:      return csStorage::tString;
   case cdbCursor::tRowid:       return csStorage::tNone;      // ????
   case cdbCursor::tDate:        return csStorage::tDate;
   case cdbCursor::tTime:        return csStorage::tTime;
   case cdbCursor::tTimeStamp:   return csStorage::tDateTime;
   }

   return csStorage::tNone;
}

int cdbCursorEx::getFieldBufferSize(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 ) {
         int size = 0;
         for ( int i = 0 ; i < getKeyCount() ; i++ )
            size += getFieldBufferSize(getKeyField(i)) + 1;
         return size;
      }
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->getBufferSize();
   }

   return 0;
}

cString cdbCursorEx::getFieldLabel(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() == 1 )
         fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   if ( fld < 0 ) {
      return getFieldName(fld);
   } else {
      return cdbCursor::getFieldName(fld);
   }
}

cString cdbCursorEx::getFieldName(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 ) {
         cString names;
         for ( int i = 0 ; i < getKeyCount() ; i++ ) {
            if ( !names.isEmpty() )
               names += ",";
            names += getFieldName(getKeyField(i));
         }
         return names;
      }
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   return cdbCursor::getFieldName(fld);
}

cString cdbCursorEx::getFieldBaseName(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 ) {
         cString names;
         for ( int i = 0 ; i < getKeyCount() ; i++ ) {
            if ( !names.isEmpty() )
               names += ",";
            names += getFieldBaseName(getKeyField(i));
         }
         return names;
      }
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   return cdbCursor::getFieldBaseColumn(fld);
}

cString cdbCursorEx::getFieldBaseTableName(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 ) {
         cString names;
         for ( int i = 0 ; i < getKeyCount() ; i++ ) {
            if ( !names.isEmpty() )
               names += ",";
            names += getFieldBaseTable(getKeyField(i));
         }
         return names;
      }
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   return cdbCursor::getFieldBaseTable(fld);
}

int cdbCursorEx::getFieldWidth(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 ) {
         int width = 0;
         for ( int i = 0 ; i < getKeyCount() ; i++ )
            width += getFieldWidth(getKeyField(i)) + 1;
         return width;
      }
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   return cdbCursor::getFieldSize(fld);
}

int cdbCursorEx::getFieldPrec(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 )
         return 0;
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   return cdbCursor::getFieldDigits(fld);
}

cString cdbCursorEx::getTitleText(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 ) {
         cString label;
         for ( int i = 0 ; i < getKeyCount() ; i++ ) {
            if ( !label.isEmpty() )
               label += ",";
            label += getTitleText(getKeyField(i));
         }
         return label;
      }
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   return cdbCursor::getFieldLabel(fld);
}


// Erfragefunktionen fuer aktuellen Datensatz
// ==========================================

bool cdbCursorEx::isNull(int fld) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      return false;
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->isNull();
   }

   return true;
}

bool cdbCursorEx::get(int fld, int& buf) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 )
         return false;
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->get(buf);
   }

   return false;
}

bool cdbCursorEx::get(int fld, double& buf) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 )
         return false;
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->get(buf);
   }

   return false;
}

bool cdbCursorEx::get(int fld, cTime& buf) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 )
         return false;
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->get(buf);
   }

   return false;
}

bool cdbCursorEx::get(int fld, cDate& buf) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 )
         return false;
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->get(buf);
   }

   return false;
}

bool cdbCursorEx::get(int fld, cDateTime& buf) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 )
         return false;
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->get(buf);
   }

   return false;
}

bool cdbCursorEx::get(int fld, char& buf) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 )
         return false;
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->get(buf);
   }

   return false;
}

bool cdbCursorEx::get(int fld, cString& buf) const
{
   if ( fld == -1 /*KEY_FIELD*/ ) {
      if ( getKeyCount() > 1 ) {
         buf.clear();
         for ( int i = 0 ; i < getKeyCount() ; i++ ) {
            if ( !buf.isEmpty() )
               buf += ",";
            cString value;
            if ( !get(getKeyField(i), value) )
               return false;
            buf += value;
         }
         return true;
      }
      fld = getKeyField(0);
   } else if ( fld == -2 /*KEY_NAME*/ ) {
      fld = getNameField();
   } else if ( fld == -3 /*KEY_DESCR*/ ) {
      fld = getDescrField();
   }

   VAR_ARRAY& vars = *(VAR_ARRAY *)cdbCursorEx::vars;

   if ( fld >= 0 && fld < vars.getSize() ) {
      if ( vars[fld].var )
         return vars[fld].var->get(buf);
   }

   return false;
}


