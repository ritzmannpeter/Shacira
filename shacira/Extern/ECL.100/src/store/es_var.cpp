// ===========================================================================
// es_var.cpp                                                   ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-csBaseStorage
//        |
//        +-csStorage            - Beschreibung eines Speicherortes.
//           |
//           +-csVar             - Speicherort Hauptspeicher.
//              |
//              +--csVarString   - String-Variable im Hauptspeicher.
//              |
//              +--csVarInt      - "C" int-Variable im Hauptspeicher.
//              |
//              +--csVarDouble   - "C" double-Variable im Hauptspeicher.
//              |
//              +--csVarChar     - "C" char-Variable im Hauptspeicher.
//              |
//              +--csVarTime     - cTime-Variable im Hauptspeicher.
//              |
//              +--csVarDate     - cDate-Variable im Hauptspeicher.
//              |
//              +--csVarDateTime - cDateTime-Variable im Hauptspeicher.
//
// ===========================================================================

#include <stdio.h>                               /* Standard I/O functions */
#include <stdlib.h>                              /* Misc. functions        */
#include <string.h>                              /* String functions       */
#include <limits.h>

#include "base/eb_str.hpp"
#include "store/es_var.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "store/es_store.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// Definition csVar
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//
// ===========================================================================

class __ECL_DLLEXPORT__ csVar : public csStorage {
   ECL_DECLARE(csVar,csStorage)

public:

   // Initialisierung als int-Variable
   csVar(int& _buf, int _width = 11, int _flags = 0);
   // Initialisierung als double-Variable
   csVar(double& _buf, int _width = 21, int _prec = -1, int _flags = fThousandSep);
   // Initialisierung als cTime-Variable
   csVar(cTime& _buf, int _flags = 0);
   // Initialisierung als cDate-Variable
   csVar(cDate& _buf, int _flags = 0);
   // Initialisierung als cDateTime-Variable
   csVar(cDateTime& _buf, int _flags = 0);
   // Initialisierung als char-Variable
   csVar(char& _buf, int _flags = 0);
   // Initialisierung als String-Variable
   csVar(char *_buf, int _size, int _flags = 0);
   // Initialisierung als beliebige Variable; Puffer wird automatisch allokiert
   csVar(TYPE _type, int _size, int _width = 0, int _prec = 0, int _flags = 0);
   // Kopie einer anderen Variable
   csVar(const csVar& other);
   // Destruktor
   ~csVar();


   // Flags
   // =====

   enum FLAGS { fStart = csStorage::fUser,
      fIsNull      = fStart << 0,  // Objekt ist NULL
      fUser        = fStart << 1   // Benutzerdefinierte Flags
   };


protected:

   // Ueberschriebene Events
   // ======================

   // Werte erfragen
   // --------------

   // Variable als int abfragen
   bool onGetInt(int& _buf) const;
   // Variable als double abfragen
   bool onGetDouble(double& _buf) const;
   // Variable als cTime abfragen
   bool onGetTime(cTime& _buf) const;
   // Variable als cDate abfragen
   bool onGetDate(cDate& _buf) const;
   // Variable als cDateTime abfragen
   bool onGetDateTime(cDateTime& _buf) const;
   // Variable als char abfragen
   bool onGetChar(char& _buf) const;
   // Variable als String abfragen
   bool onGetString(cString& _buf) const;


   // Werte setzen
   // ------------

   // Variable ueber int setzen
   bool onPutInt(int _buf);
   // Variable ueber double setzen
   bool onPutDouble(double _buf);
   // Variable ueber cTime setzen
   bool onPutTime(cTime _buf);
   // Variable ueber cDate setzen
   bool onPutDate(cDate _buf);
   // Variable ueber cDateTime setzen
   bool onPutDateTime(cDateTime _buf);
   // Variable ueber char setzen
   bool onPutChar(char _buf);
   // Variable ueber String setzen
   bool onPutString(cString _buf);


   // Pufferspeicher
   // --------------

   // Wird aufgerufen, um die Adresse des Pufferspeichers zu ermitteln
   void *onGetBuffer();
   // Wird aufgerufen, um Puffergroesse (Bytes) ermitteln
   int onGetBufferSize() const;
   // Pruefen, ob der Pufferspeicher kompatibel zum Uebergabetyp ist
   int onGetBufferStyle() const;


   // Sonstiges
   // ---------

   // Sinnvolle maximale Groesse eines Eingabefeldes ermitteln
   int onGetMaskLength() const;

   // Ist die Variable NULL?
   bool onCheckNull() const
      { return !!getFlags(fIsNull); }
   // NULL-Zustand der Variablen setzen
   void onSetNull(bool null = true);


protected:

   // Intern: Konstruktor (fuer cVarXxxx-Klassen)
   csVar(int size, int width, int prec, int flags, TYPE type);
   // Intern: SetBuffer-Methode (fuer cVarXxxx-Klassen)
   void setBuffer(void *new_buf, int new_size = -1, bool auto_del = false);
   // Intern: Neuen Puffer der Groesse 'new_size' allokieren
   void *newBuffer(int new_size);
   // Intern: Kopieren aller Attribute von 'other'
   void copyFrom(const csVar& other);
   // Intern: Setzen des Puffers und des NULL-Zustandes
   void initFrom(const void *data, int size, bool null);


private:

   void *buf;     // Adresse des Puffers
   int size;      // Allokierte Groesse des Puffers

};

#endif /*__INTERFACE__*/


// Implementierung csVar
// ===========================================================================

csVar::csVar(int& _buf, int _width, int _flags) :
   csStorage(tInt, _width, 0, _flags)
{
   buf = &_buf; size = sizeof _buf;
}

csVar::csVar(double& _buf, int _width, int _prec, int _flags) :
   csStorage(tDouble, _width, _prec, _flags)
{
   buf = &_buf; size = sizeof _buf;
}

csVar::csVar(cTime& _buf, int _flags) :
   csStorage(tTime, _flags)
{
   buf = &_buf; size = sizeof _buf;
}

csVar::csVar(cDate& _buf, int _flags) :
   csStorage((_flags & fIsWeek) ? tWeek : tDate, _flags)
{
   buf = &_buf; size = sizeof _buf;
}

csVar::csVar(cDateTime& _buf, int _flags) :
   csStorage(tDateTime, _flags)
{
   buf = &_buf; size = sizeof _buf;
}

csVar::csVar(char& _buf, int _flags) :
   csStorage(tChar, _flags)
{
   buf = &_buf; size = sizeof _buf; setFlags(fIsNull, !_buf);
}

csVar::csVar(char *_buf, int _size, int _flags) :
   csStorage(tString, _flags)
{
   buf = _buf; size = _size; setFlags(fIsNull, !_buf || !*_buf);
}

csVar::csVar(TYPE _type, int _size, int _width, int _prec, int _flags) :
   csStorage(_type, _width, _prec, _flags | fDeleteBuf)
{
   buf = NULL; size = _size;
   if ( _size > 0 )
      buf = (void *)(new0 (char[_size]));
   if ( buf )
      memset(buf, 0, _size);
}

csVar::csVar(int size, int width, int prec, int flags, TYPE type) :
   csStorage(type, width, prec, flags)
{
   buf = NULL;
   csVar::size = size;
}

csVar::csVar(const csVar& other) :
   csStorage(other)
{
   buf = other.buf;
   size = other.size;
}

csVar::~csVar()
{
   if ( getFlags(fDeleteBuf) )
      delete[] ((char*)buf);
}


// Allgemeines
// ===========

void csVar::setBuffer(void *new_buf, int new_size, bool auto_del)
{
   if ( buf != 0 && getFlags(fDeleteBuf) )
      delete[] ((char*)buf);

   if ( new_size >= 0 )
      size = new_size;

   buf = new_buf;
   setFlags(fDeleteBuf, auto_del);
}

void * csVar::newBuffer(int new_size)
{
   if ( new_size > size ) {
      if ( buf != 0 && getFlags(fDeleteBuf) )
         delete[] ((char*)buf);
      buf = new0 char[new_size];
      memset(buf, 0, new_size);
      setFlags(fDeleteBuf);
   }

   size = new_size;
   return buf;
}

void csVar::copyFrom(const csVar& other)
{
   csStorage::copyFrom(other);
   size = other.size;
}

void csVar::initFrom(const void *data, int size, bool null)
{
   // Es werden Rohdaten kopiert, d.h. 'data' muss kompatibel
   // zum aktuellen Typ des csVar-Objektes sein. Die Initialisierung
   // und das Setzen des Null-Flags werden NICHT signalisiert!

   if ( buf != 0 && data != 0 && size > 0 )
      memcpy(buf, data, min(csVar::size, size));
   setFlags(fIsNull, null);
}


// Ueberschriebene Events
// ======================

// Werte erfragen
// --------------

bool csVar::onGetInt(int& _buf) const
{
   if ( !isNull() && __ECL_ASSERT1__(buf != 0) ) {
      switch ( getType() ) {
       case tInt:     _buf = *((int *)buf); return true;
       case tDouble:  _buf = int(*((double *)buf)); return true;
       case tChar:    _buf = int(*((char *)buf)); return true;
       case tString:  _buf = atoi((const char *)buf); return true;
      }
   }

   return csStorage::onGetInt(_buf);
}

bool csVar::onGetDouble(double& _buf) const
{
   if ( !isNull() && __ECL_ASSERT1__(buf != 0) ) {
      switch ( getType() ) {
       case tInt:     _buf = double(*((int *)buf)); return true;
       case tDouble:  _buf = *((double *)buf); return true;
       case tString:  _buf = atof((const char *)buf); return true;
      }
   }

   return csStorage::onGetDouble(_buf);
}

bool csVar::onGetTime(cTime& _buf) const
{
   if ( !isNull() && __ECL_ASSERT1__(buf != 0) ) {
      switch ( getType() ) {
       case tTime:    _buf = *((cTime *)buf); return true;
       case tString:  _buf = cTime((const char *)buf); return true;
      }
   }

   return csStorage::onGetTime(_buf);
}

bool csVar::onGetDate(cDate& _buf) const
{
   if ( !isNull() && __ECL_ASSERT1__(buf != 0) ) {
      switch ( getType() ) {
       case tDate:    _buf = *((cDate *)buf); return true;
       case tString:  _buf = cDate((const char *)buf, !!getFlags(fIsWeek)); return true;
      }
   }

   return csStorage::onGetDate(_buf);
}

bool csVar::onGetDateTime(cDateTime& _buf) const
{
   if ( !isNull() && __ECL_ASSERT1__(buf != 0) ) {
      switch ( getType() ) {
       case tDateTime: _buf = *((cDateTime *)buf); return true;
       case tString:   _buf = cDateTime((const char *)buf); return true;
      }
   }

   return csStorage::onGetDateTime(_buf);
}

bool csVar::onGetChar(char& _buf) const
{
   if ( !isNull() && __ECL_ASSERT1__(buf != 0) ) {
      switch ( getType() ) {
       case tInt:     _buf = char(*((int *)buf)); return true;
       case tChar:    _buf = *((char *)buf); return true;
       case tString:  _buf = *((char *)buf); return true;
      }
   }

   return csStorage::onGetChar(_buf);
}

bool csVar::onGetString(cString& _buf) const
{
   // Um zur cTable-Klasse kompatibel zu sein, wird
   // bei NULL-Elementen der Puffer geloescht

   if ( isNull() || !__ECL_ASSERT1__(buf != 0) ) {
      _buf.clear();
      return false;
   }

   char temp[128];

   TYPE type = getType();
   if ( type == tDate && getFlags(fIsWeek) )
      type = tWeek;

   switch ( type ) {

    case tInt:
      formatValue(temp, *((int *)buf), getWidth(), getPrec(), hasThousandSep(), isLeftPadded());
      break;

    case tDouble:
      formatValue(temp, *((double *)buf), getWidth(), getPrec(), hasThousandSep(), isLeftPadded());
      break;

    case tTime:
      _buf = ((cTime *)buf)->getStr();
      return true;

    case tDate:
      _buf = ((cDate *)buf)->getStr();
      return true;

    case tDateTime:
      _buf = ((cDateTime *)buf)->getStr();
      return true;

    case tWeek:
      _buf = ((cDate *)buf)->getWeekStr();
      return true;

    case tChar:
      _buf = Str(*((char *)buf));
      return true;

    case tString:
      _buf = (const char *)buf;
      return true;

    default:
      return false;

   }

   _buf = temp;
   return true;
}


// Werte setzen
// ------------

bool csVar::onPutInt(int _buf)
{
   bool rc = true;
   char temp[128];

   if ( !__ECL_ASSERT1__(buf != 0) )
      return false;

   switch ( getType() ) {

   case tInt:
      *((int *)buf) = _buf;
      break;

   case tDouble:
      *((double *)buf) = double(_buf);
      break;

   case tChar:
      if ( _buf <= CHAR_MAX && _buf >= CHAR_MIN ) {
         *((char *)buf) = char(_buf);
      } else {
         rc = false;
      }
      break;

   case tString:
      formatValue(temp, _buf, getWidth(), getPrec(), hasThousandSep(), isLeftPadded());
      strxcpy((char *)buf, temp, size);
      break;

   default:
      rc = false;
      break;

   }

   setNull(!rc);
   return rc;
}

bool csVar::onPutDouble(double _buf)
{
   bool rc = true;
   char temp[128];

   if ( !__ECL_ASSERT1__(buf != 0) )
      return false;

   switch ( getType() ) {

   case tInt:
      if ( _buf <= INT_MAX && _buf >= INT_MIN ) {
         *((int *)buf) = int(_buf);
      } else {
         rc = false;
      }
      break;

   case tDouble:
      *((double *)buf) = _buf;
      break;

   case tChar:
      if ( _buf <= CHAR_MAX && _buf >= CHAR_MIN ) {
         *((char *)buf) = char(_buf);
      } else {
         rc = false;
      }
      break;

   case tString:
      formatValue(temp, _buf, getWidth(), getPrec(), hasThousandSep(), isLeftPadded());
      strxcpy((char *)buf, temp, size);
      break;

   default:
      rc = false;
      break;

   }

   setNull(!rc);
   return rc;
}

bool csVar::onPutChar(char _buf)
{
   bool rc = true;
   char temp[2];

   if ( !__ECL_ASSERT1__(buf != 0) )
      return false;

   switch ( getType() ) {

   case tInt:
      *((int *)buf) = _buf;
      break;

   case tDouble:
      *((double *)buf) = _buf;
      break;

   case tChar:
      *((char *)buf) = _buf;
      break;

   case tString:
       temp[0] = _buf;
       temp[1] = '\0';
       strxcpy((char *)buf, temp, size);
       break;

   default:
      rc = false;
      break;

   }

   setNull(!rc);
   return rc;
}

bool csVar::onPutTime(cTime _buf)
{
   bool rc = true;

   if ( !__ECL_ASSERT1__(buf != 0) )
      return false;

   switch ( getType() ) {
   case tTime:    *((cTime *)buf) = _buf; break;
   case tString:  strxcpy((char *)buf, _buf.getStr(), size); break;
   default:       rc = false; break;
   }

   setNull(!rc);
   return rc;
}

bool csVar::onPutDate(cDate _buf)
{
   bool rc = true;

   if ( !__ECL_ASSERT1__(buf != 0) )
      return false;

   switch ( getType() ) {
   case tDate:    *((cDate *)buf) = _buf; break;
   case tString:  strxcpy((char *)buf, _buf.getStr(), size); break;
   default:       rc = false; break;
   }

   setNull(!rc);
   return rc;
}

bool csVar::onPutDateTime(cDateTime _buf)
{
   bool rc = true;

   if ( !__ECL_ASSERT1__(buf != 0) )
      return false;

   switch ( getType() ) {
   case tDateTime: *((cDateTime *)buf) = _buf; break;
   case tString:   strxcpy((char *)buf, _buf.getStr(), size); break;
   default:        rc = false; break;
   }

   setNull(!rc);
   return rc;
}

bool csVar::onPutString(cString _buf)
{
   if ( !__ECL_ASSERT1__(buf != 0) )
      return false;

   // null-Flag setzen, wenn _buf NULL oder ein Leerstring ist. Dieses
   // Verhalten scheint zwar nicht unbedingt korrekt, ist aber notwendig,
   // da auch die cTable-Klasse so arbeitet.

   if ( _buf.isEmpty() ) {
      setNull(true);
      return true;
   }

   bool rc = true;
   double temp = 0.0;

   TYPE type = getType();
   if ( type == tDate && getFlags(fIsWeek) )
      type = tWeek;

   switch ( type ) {

   case tInt:
      if ( cString::convStr2Dbl(_buf, temp) ) {
         *((int *)buf) = (int)temp;
      } else {
         rc = false;
      }
      break;

   case tDouble:
      if ( cString::convStr2Dbl(_buf, temp) ) {
         *((double *)buf) = temp;
      } else {
         rc = false;
      }
      break;

   case tTime:
      *((cTime *)buf) = cTime(_buf);
      break;

   case tDate:
      *((cDate *)buf) = cDate(_buf);
      break;

   case tDateTime:
      *((cDateTime *)buf) = cDateTime(_buf);
      break;

   case tWeek:
      *((cDate *)buf) = cDate(_buf, true);
      break;

   case tChar:
      *((char *)buf) = _buf[0];
      break;

   case tString:
      strxcpy((char *)buf, _buf, size);
      break;

   default:
      rc = false;
      break;

   }

   setNull(!rc);
   return rc;
}


// Pufferspeicher
// --------------

void * csVar::onGetBuffer()
{
   return buf;
}

int csVar::onGetBufferSize() const
{
   return getType() != tString ?
      csStorage::onGetBufferSize()
    : size;
}

int csVar::onGetBufferStyle() const
{
   return buf == 0 ? 0 : bstPresent | bstCompatible;
}


// Sonstiges
// ---------

int csVar::onGetMaskLength() const
{
   switch ( getType() ) {
    case tString:  return size - 1;
   }

   return csStorage::onGetMaskLength();
}

void csVar::onSetNull(bool null)
{
   setFlags(fIsNull, null);

   // Wird das Feld geNULLt, sicherheitshalber noch den Puffer mit
   // einem Defaultwert initialisieren...

   if ( null ) {
      switch ( getType() ) {
       case tInt:      *((int *)buf) = 0; break;
       case tDouble:   *((double *)buf) = 0.0; break;
       case tTime:     *((cTime *)buf) = cTime(); break;
       case tDate:     *((cDate *)buf) = cDate(); break;
       case tDateTime: *((cDateTime *)buf) = cDateTime(); break;
       case tWeek:     *((cDate *)buf) = cDate(); break;
       case tChar:     *((char *)buf) = '\0'; break;
       case tString:   *((char *)buf) = '\0'; break;
      }
   }
}




#ifdef __INTERFACE__

// ===========================================================================
// Definition csVarString
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--csVarString
//
// ===========================================================================

class __ECL_DLLEXPORT__ csVarString : public csVar {
   ECL_DECLARE(csVarString,csVar)
   char *v;
public:
   csVarString(int size, int flags = fIsNull) :
      csVar(size, 0, 0, flags | fPermanent, tString)
      { v = new0 char[size]; *v = '\0'; setBuffer(v); }
   csVarString(const csVarString& other) : csVar(other)
      { v = new0 char[getBufferSize()]; setBuffer(v);
        strxcpy(v, other.v, getBufferSize()); }
   csVarString(const cString& s) :
      csVar(s.getSize(), 0, 0, fPermanent, tString)
      { v = new0 char[s.getSize()]; setBuffer(v);
        if ( !s.isEmpty() ) strxcpy(v, s, getBufferSize());
        setNull(s.isEmpty()); }
   ~csVarString()
      { delete[] v; }

   csVarString& operator=(const csVarString& other)
      { copyFrom(other);
        delete[] v; v = new0 char[getBufferSize()]; setBuffer(v);
        strxcpy(v, other.v, getBufferSize()); setNull(other.isNull());
        return *this; }
   csVarString& operator=(const char *s)
      { if ( s ) strxcpy(v, s, getBufferSize());
        setNull(s ? !*s : false);
        return *this; }
   csVarString& operator=(const cString& s)
      { if ( !s.isEmpty() ) strxcpy(v, s, getBufferSize());
        setNull(s.isEmpty());
        return *this; }

   int operator==(const csVarString& other)
      { if ( !isNull() && !other.isNull() ) return strcmp(v, other.v);
        return isNull() && other.isNull() ? 0 : 1; }
   int operator!=(const csVarString& other)
      { return !(*this == other); }

   operator const char *() const
      { return v; }
   operator char *()
      { return v; }
};


// ===========================================================================
// Definition csVarInt
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--csVarInt
//
// ===========================================================================

class __ECL_DLLEXPORT__ csVarInt : public csVar {
   ECL_DECLARE(csVarInt,csVar)
   int v;

public:
   csVarInt() :
      csVar(sizeof(int), 11, 0, fIsNull | (int)fPermanent, tInt)
      { v = 0; setBuffer(&v); }
   csVarInt(int def_val, int width = 11, int flags = 0) :
      csVar(sizeof(int), width, 0, flags | fPermanent, tInt)
      { v = def_val; setBuffer(&v); }
   csVarInt(const csVarInt& other) : csVar(other)
      { v = other.v; setBuffer(&v); }

   csVarInt& operator=(const csVarInt& other)
      { copyFrom(other); v = other.v;
        setNull(other.isNull());
        return *this; }
   int& operator=(int other)
      { v = other; setNull(false); return v; }

   int operator==(const csVarInt& other)
      { if ( !isNull() && !other.isNull() ) return v == other.v;
        return isNull() && other.isNull(); }
   int operator!=(const csVarInt& other)
      { return !(*this == other); }

   operator int () const
      { return v; }
};


// ===========================================================================
// Definition csVarDouble
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--csVarDouble
//
// ===========================================================================

class __ECL_DLLEXPORT__ csVarDouble : public csVar {
   ECL_DECLARE(csVarDouble,csVar)
   double v;

public:
   csVarDouble() :
      csVar(sizeof(double), 21, -1, fIsNull | (int)fPermanent | (int)fThousandSep, tDouble)
      { v = 0.0; setBuffer(&v); }
   csVarDouble(double def_val, int width = 21, int prec = -1, int flags = fThousandSep) :
      csVar(sizeof(double), width, prec, flags | fPermanent, tDouble)
      { v = def_val; setBuffer(&v); }
   csVarDouble(const csVarDouble& other) : csVar(other)
      { v = other.v; setBuffer(&v); }

   csVarDouble& operator=(const csVarDouble& other)
      { copyFrom(other); v = other.v;
        setNull(other.isNull());
        return *this; }
   double& operator=(double other)
      { v = other; setNull(false); return v; }

   int operator==(const csVarDouble& other)
      { if ( !isNull() && !other.isNull() ) return v == other.v;
        return isNull() && other.isNull(); }
   int operator!=(const csVarDouble& other)
      { return !(*this == other); }

   operator double () const
      { return v; }
};


// ===========================================================================
// Definition csVarChar
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--csVarChar
//
// ===========================================================================

class __ECL_DLLEXPORT__ csVarChar : public csVar {
   ECL_DECLARE(csVarChar,csVar)
   char v;

public:
   csVarChar() :
      csVar(sizeof(char), 1, 0, fIsNull | (int)fPermanent, tChar)
      { v = '\0'; setBuffer(&v); }
   csVarChar(char def_val, int flags = 0) :
      csVar(sizeof(char), 1, 0, flags | fPermanent, tChar)
      { v = def_val; setBuffer(&v); }
   csVarChar(const csVarChar& other) : csVar(other)
      { v = other.v; setBuffer(&v); }

   csVarChar& operator=(const csVarChar& other)
      { copyFrom(other); v = other.v;
        setNull(other.isNull());
        return *this; }
   char& operator=(char other)
      { v = other; setNull(false); return v; }

   int operator==(const csVarChar& other)
      { if ( !isNull() && !other.isNull() ) return v == other.v;
        return isNull() && other.isNull(); }
   int operator!=(const csVarChar& other)
      { return !(*this == other); }

   operator char () const
      { return v; }
};


// ===========================================================================
// Definition csVarTime
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--csVarTime
//
// ===========================================================================

class __ECL_DLLEXPORT__ csVarTime : public csVar {
   ECL_DECLARE(csVarTime,csVar)
   cTime v;

public:
   csVarTime() :
      csVar(sizeof(cTime), 0, 0, fIsNull | (int)fPermanent, tTime)
      { setBuffer(&v); }
   csVarTime(const cTime& def_val, int flags = 0) :
      csVar(sizeof(cTime), 0, 0, flags | fPermanent, tTime)
      { v = def_val; setBuffer(&v); }
   csVarTime(const csVarTime& other) : csVar(other)
      { v = other.v; setBuffer(&v); }

   csVarTime& operator=(const csVarTime& other)
      { copyFrom(other); v = other.v;
        setNull(other.isNull());
        return *this; }
   cTime& operator=(const cTime& other)
      { v = other; setNull(false); return v; }

   int operator==(const csVarTime& other)
      { if ( !isNull() && !other.isNull() ) return v == other.v;
        return isNull() && other.isNull(); }
   int operator!=(const csVarTime& other)
      { return !(*this == other); }

   operator cTime () const
      { return v; }
};


// ===========================================================================
// Definition csVarDate
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--csVarDate
//
// ===========================================================================

class __ECL_DLLEXPORT__ csVarDate : public csVar {
   ECL_DECLARE(csVarDate,csVar)
   cDate v;

public:
   csVarDate() :
      csVar(sizeof(cDate), 0, 0, fIsNull | (int)fPermanent, tDate)
      { setBuffer(&v); }
   csVarDate(const cDate& def_val, int flags = 0) :
      csVar(sizeof(cDate), 0, 0, flags | fPermanent, tDate)
      { v = def_val; setBuffer(&v); }
   csVarDate(const csVarDate& other) : csVar(other)
      { v = other.v; setBuffer(&v); }

   csVarDate& operator=(const csVarDate& other)
      { copyFrom(other); v = other.v;
        setNull(other.isNull());
        return *this; }
   cDate& operator=(const cDate& other)
      { v = other; setNull(false); return v; }

   int operator==(const csVarDate& other)
      { if ( !isNull() && !other.isNull() ) return v == other.v;
        return isNull() && other.isNull(); }
   int operator!=(const csVarDate& other)
      { return !(*this == other); }

   operator cDate () const
      { return v; }
};


// ===========================================================================
// Definition csVarDateTime
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--csVarDateTime
//
// ===========================================================================

class __ECL_DLLEXPORT__ csVarDateTime : public csVar {
   ECL_DECLARE(csVarDateTime,csVar)
   cDateTime v;

public:
   csVarDateTime() :
      csVar(sizeof(cDateTime), 0, 0, fIsNull | (int)fPermanent, tDateTime)
      { setBuffer(&v); }
   csVarDateTime(const cDateTime& def_val, int flags = 0) :
      csVar(sizeof(cDateTime), 0, 0, flags | fPermanent, tDateTime)
      { v = def_val; setBuffer(&v); }
   csVarDateTime(const csVarDateTime& other) : csVar(other)
      { v = other.v; setBuffer(&v); }

   csVarDateTime& operator=(const csVarDateTime& other)
      { copyFrom(other); v = other.v;
        setNull(other.isNull());
        return *this; }
   cDateTime& operator=(const cDateTime& other)
      { v = other; setNull(false); return v; }

   int operator==(const csVarDateTime& other)
      { if ( !isNull() && !other.isNull() ) return v == other.v;
        return isNull() && other.isNull(); }
   int operator!=(const csVarDateTime& other)
      { return !(*this == other); }

   operator cDateTime () const
      { return v; }
};

#endif /*__INTERFACE__*/


