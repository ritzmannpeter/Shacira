// ===========================================================================
// base/string.cpp                                              ______ /  ECL
// Autoren: Udo Pfrengle, Markus Wuertz, Thomas Epting         /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/string.h"

// ??? 
#ifdef __DEBUG_ALLOC__
   #if __ECL_VCPP__ >= 1310
      #include <new>
   #else
      #include <new.h>
   #endif
#endif

#if defined __ECL_OS2__
   #define INCL_WINSHELLDATA
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif

// Standard headers
#include <cstdarg>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <iomanip>


/**
* @defgroup string String Manipulation
* @ingroup baseclass
*/


namespace ecl {


// Ein leerer String fuer alle leeren Strings (und alle fuer einen)
static const cString __ECL_EmptyString__("");

// Konstanten der Masken fuer __ECL_ASSERT__ (identifizieren cString-Modul)
const unsigned long STR_ERROR = cBase::dbgError | cBase::dbgBase | cBase::dbgAssert;
const unsigned long STR_WARN  = cBase::dbgWarn  | cBase::dbgBase;
const char *TEXT_WCHAR_SUPPORT = "wchar_t support incomplete";




// ===========================================================================
// Local functions
// ===========================================================================

static const char * FindNext(const char *p, char c)
{
   for ( ; *p ; p++ ) {
      if ( *p == c )
         return p;
   }

   return p;
}

static const char * FindMatching(const char *p, const char *delims, char c)
{
   for ( ; *p ; p++ ) {
      if ( *p == c ) {
         return p;
      } else {
         switch ( *p ) {
         case '\'':  if ( strchr(delims, '\'') != 0 ) p = FindNext(p+1, '\''); break;
         case '"':   if ( strchr(delims, '"')  != 0 ) p = FindNext(p+1, '"'); break;
         case '(':   if ( strchr(delims, '(')  != 0 ) p = FindMatching(p+1, delims, ')'); break;
         case '{':   if ( strchr(delims, '{')  != 0 ) p = FindMatching(p+1, delims, '}'); break;
         case '[':   if ( strchr(delims, '[')  != 0 ) p = FindMatching(p+1, delims, ']'); break;
         }
      }
   }

   return p;
}

// Converts from ANSI to Unicode, 'ws' has a size of 'size' chars
static wchar_t * AnsiToUnicode(wchar_t *ws, const char *s, size_t size)
{
   #ifdef __ECL_W32__
      if ( s != 0 && ws != 0 ) {
         ws[0] = '\0';
         if ( MultiByteToWideChar(CP_ACP, 0, s, -1, ws, size) != 0 ) {
            return ws;
         }
      }
   #else
   #endif

   return 0;
}

// Converts from Unicode to ANSI, 's' has a size of 'size' chars
static char * UnicodeToAnsi(char *s, const wchar_t *ws, size_t size)
{
   #ifdef __ECL_W32__
      if ( s != 0 && ws != 0 ) {
         s[0] = '\0';
         if ( WideCharToMultiByte(CP_ACP, 0, ws, -1, s, size, 0, 0) != 0 ) {
            return s;
         }
      }
   #else
   #endif

   return 0;
}

// replace C-style escape sequences in a string by their characters. e.g.
// "\\t" (2 bytes)   -> "\t" (1 byte)
// "\\123" (4 bytes) -> "\123" (1 byte)
// "\\xFF" (4 bytes) -> "\xFF" (1 byte)
static char *replaceEscape(char *str)
{
   const char *esc = "ntvbrfa\\?'\"";
   const char *asc = "\n\t\v\b\r\f\a\\?'\"";

   char *from = str;
   char *to = str;

   while (*from) {
      if (*from != '\\') {
         *to++ = *from++;
      } else {
         const char *chr = strchr(esc, *++from);
         if (chr != 0) {
            *to++ = asc[chr-esc];
            from++;
         } else if (*from >= '0' && *from <= '7') {
            int val = *from++ - '0';
            if (*from >= '0' && *from <= '7') {
               val = (val<<3) + *from++ - '0';
               if (*from >= '0' && *from <= '7') {
                  val = (val<<3) + *from++ - '0';
               }
            }
            *to++ = (char)val;
         } else if (*from == 'x') {
            char *endp;
            long val = strtoul(++from, &endp, 16);
            if (from < endp) *to++ = (char)val;
            from = endp;
         } else {
            *to++ = *from++;
         }
      }
   }
   
   *to = *from;
   return str;
}




// ===========================================================================
// More local functions and data
// ===========================================================================


// Modullokale Variablen und statische Funktionen
// ---------------------------------------------------------------------------

// minimale Stringlaenge
static unsigned min_str_size = 80;
void cString::setMinStrSize(int m) { min_str_size = m; }

// ===========================================================================
// Helper functions
// ===========================================================================

/*! \example cppunit/string_test.cpp
 *  Beispiel fuer die Benutzung der cString-Klasse.
 */

void cString::alloc(size_t l)
{
   if (l<(int)min_str_size) l=min_str_size;
   str=(xstr*)malloc(sizeof *str + l);
   str->size = l;
   str->refc = str->len = 0;
   str->ws = 0;
   str->s[0] = '\0';
}

void cString::dealloc( xstr *&str )
{
   if (str) {
      if (__ECL_ASSERT_PRINTF__(str->refc >= 0, STR_ERROR, ("cString: attempt to free already freed",str->s))) {
         if (str->refc-- == 0) {
            if ( str->ws != 0 )
               free(str->ws);
            free(str);
         }
      }
      str = 0;
   }
}

void cString::init(const char *s, size_t len)
{
   alloc(len);
   if (s) {
      strncpy(str->s, s, len);
      str->s[len] = '\0';
      str->len = strlen(str->s);
   }
}

void cString::init(const wchar_t *ws, size_t len)
{
   alloc(len);
   if (ws) {
      UnicodeToAnsi(str->s, ws, str->size);
      str->len = strlen(str->s);
   }
}

cString& cString::assign(const char *other, size_t l)
{
   if (!str || str->refc || str->size < int(l)) {
      xstr *old = str;
      init( other, l );
      dealloc( old ); /* this */
   } else {
      if (other) {
         strcpy(str->s, other);
      } else {
         str->s[0] = '\0';
      }
      str->len = l;
   }
   return *this;
}

cString& cString::assign(const wchar_t *other, size_t l)
{
   if (!str || str->refc || str->size < int(l)) {
      xstr *old = str;
      init( other, l );
      dealloc( old ); /* this */
   } else {
      if (other) {
         UnicodeToAnsi(str->s, other, str->size);
      } else {
         str->s[0] = '\0';
      }
      str->len = l;
   }
   return *this;
}

cString& cString::concat(const char *other, size_t l)
{
   if (str) {
      assign( str->s, str->len+l );
      // 29.03.2004 -MW- altes strcat(str->s, other) knallt wenn str->s == other
      if (other) strncat(str->s, other, l);
      str->len = strlen(str->s); // oder aber auch: str->len += l;
   } else {
      init(other, l);
   }
   return *this;
}

cString& cString::concat(const wchar_t *other, size_t l)
{
   if (str) {
      int other_len = l;
      int old_len = str->len;
      l += old_len;
      assign( str->s, l );
      if (other)
         UnicodeToAnsi(str->s + old_len, other, other_len+1);
      str->len = strlen(str->s); // oder aber auch: str->len = l;
   } else {
      init(other, l);
   }
   return *this;
}

char *cString::lockBuffer(int size)
{
   if (!str || str->refc || str->size < size) {
      xstr *old = str;
      alloc(size);
      dealloc(old);
   }
   str->len = size;
   //?? memset(str->s, 0, str->size+1);
   return str->s;
}

void cString::unlockBuffer()
{
   str->s[str->size] = '\0';
   str->len = strlen(str->s);
}




// ===========================================================================
// Utility functions
// ===========================================================================

#ifndef __ECL_VCPP__
   int cString::stricmp(const char *str1, const char *str2)
   {
      int left,right;
      do {
         left = tolower(*str1++);
         right = tolower(*str2++);
      } while (left && left == right);
      return(left - right);
   }

   int cString::strnicmp(const char *str1, const char *str2, size_t count)
   {
      int left,right;
      int result = 0;

      if (count) {
         do {
            left = tolower(*str1++);
            right = tolower(*str2++);
         } while (--count && left && right && left == right);
         result = left - right;
      }
      return result;
   }

   char *cString::strlwr(char *str)
   {
      while (*str)
      {
         if ('A' <= *str && *str <= 'Z')
            *str += 'a' - 'A';
         str++;
      }
      return str;
   }

   char *cString::strupr(char *str)
   {
      while (*str)
      {
         if ('a' <= *str && *str <= 'z')
            *str += 'A' - 'a';
         str++;
      }
      return str;
   }
#endif // __ECL_VCPP__



// ===========================================================================
// Construction/Destruction/Copying
// ===========================================================================

cString::cString(int n, const cString& s)
{
   if (n<0 || s.isEmpty()) {
      str = 0;
   } else {
      int len = s.getLength();
      alloc(n);
      str->len = n;
      char *to = str->s;
      while (n > 0) {
         strncpy(to, s, n);
         to += len; n -= len;
      }
      str->s[str->len] = '\0';
   }
}


// ===========================================================================
// Deprecated functions
// ===========================================================================

cString& cString::operator<<(const cString& other)
{ 
   __ECL_DEBUG_TEXT__(STR_WARN, "<< deprecated, use +="); 
   return other.str ? concat( other.str->s, other.str->len) : *this; 
}

cString& cString::operator<<(const char * other)
{ 
   __ECL_DEBUG_TEXT__(STR_WARN, "<< deprecated, use +="); 
   return concat( other, strxlen(other) ); 
}

cString& cString::operator<<(double f)
{ 
   __ECL_DEBUG_TEXT__(STR_WARN, "<< deprecated, use +="); 
   return *this+=cStringf("%g", f); 
}




// ===========================================================================
// String functions
// ===========================================================================

char cString::operator[] (int i) const
{
   if (__ECL_ASSERT__(str && i >= 0 && i <= str->len, STR_WARN)) {
      return str->s[i];
   } else {
      return '\0';
   }
}

/**
 * Ein Zugriff jenseits der Stringlänge ist nicht erlaubt:
 * - i < len:  Schreiben & lesen normal möglich.
 * - i == len: @c \\0 kann gelesen werden, schreiben wird ignoriert.
 * - i > len:  Bewirkt eine Assertion in der Debug-Version, es wird immer
 *             @c \\0 gelesen und schreiben wird ignoriert.
 * Der Zugriff auf die Zeichenkette mit diesem Operator ist demnach immer
 * sicher. Es sollte dennoch @b niemals eine @c \\0 in die Zeichenkette geschrieben
 * werden, da so eine inkonsistente Laenge <tt>strlen(s.ccp()) < s.getLength()</tt>
 * entstehen kann, die aber sonst keine Auswirkungen haben dürfte.
 */
char &cString::operator[] (int i)
{
   static char dummy;
   if (__ECL_ASSERT__(str && i >= 0, STR_WARN) && i < str->len) {
      if (str->refc) {
         // 2006-02-02 -MW- Seiteneffekt behoben: die nicht-const-Version von []
         // darf nur auf einmalig referenzierte Strings angewendet werden, da sonst
         // unbeabsichtigt die anderen Referenzen mitgeaendert werden koennten !!!
         *this = cString(str->s);
      }
      return str->s[i];
   } else {
      __ECL_ASSERT__(str && i == str->len, STR_WARN);
      dummy = '\0';
      return dummy;
   }
}


int cString::compare(const cString& other, int max_chars) const
{
   if ( str && other.str ) {
      // 2004-04-01 -MW- 0 muss auch ueber strncmp() laufen, sonst stimmt z.B. cString("a").compare("b",0) nicht
      return max_chars >= 0 ?
         strncmp(str->s, other.str->s, max_chars)
       : strcmp(str->s, other.str->s);
   } else if ( str ) {
      return 1;
   } else if ( other.str ) {
      return -1;
   } else {
      return 0;
   }
}

int cString::compare(const char *other, int max_chars) const
{
   if ( str && other ) {
      // 2004-04-01 -MW- 0 muss auch ueber strncmp() laufen, s.o.
      return max_chars >= 0 ?
         strncmp(str->s, other, max_chars)
       : strcmp(str->s, other);
   } else if ( str ) {
      return 1;
   } else if ( other ) {
      return -1;
   } else {
      return 0;
   }
}

int cString::compare(const wchar_t *other, int max_chars) const
{
   other; max_chars; // dummy to avoid compiler warning
   __ECL_DEBUG_TEXT__(STR_ERROR, TEXT_WCHAR_SUPPORT); 
   return 0;
//   if ( str && other ) {
//      return max_chars > 0 ?
//         _strncmp(str->s, other, max_chars)
//       : _strcmp(str->s, other);
//   } else if ( str ) {
//      return 1;
//   } else if ( other ) {
//      return -1;
//   } else {
//      return 0;
//   }
}

int cString::compareNoCase(const cString& other, int max_chars) const
{
   if ( str && other.str ) {
      // 2004-04-01 -MW- 0 muss auch ueber strncmp() laufen, s.o.
      return max_chars >= 0 ?
         _strnicmp(str->s, other.str->s, max_chars)
       : _stricmp(str->s, other.str->s);
   } else if ( str ) {
      return 1;
   } else if ( other.str ) {
      return -1;
   } else {
      return 0;
   }
}

int cString::compareNoCase(const char *other, int max_chars) const
{
   if ( str && other ) {
      // 2004-04-01 -MW- 0 muss auch ueber strncmp() laufen, s.o.
      return max_chars >= 0 ?
         _strnicmp(str->s, other, max_chars)
       : _stricmp(str->s, other);
   } else if ( str ) {
      return 1;
   } else if ( other ) {
      return -1;
   } else {
      return 0;
   }
}

int cString::compareNoCase(const wchar_t *other, int max_chars) const
{
   other; max_chars; // dummy to avoid compiler warning
   __ECL_DEBUG_TEXT__(STR_ERROR, TEXT_WCHAR_SUPPORT); 
   return 0;
//   if ( str && other ) {
//      return max_chars > 0 ?
//         strnicmp(str->s, other, max_chars)
//       : stricmp(str->s, other);
//   } else if ( str ) {
//      return 1;
//   } else if ( other ) {
//      return -1;
//   } else {
//      return 0;
//   }
}

__ECL_EXP1__ cString __ECL_EXP2__ operator+(const char *s1, const cString& s2)
{
   if (!s1) {
      return s2;
   } else if (!s2.str || !s2.str->len) {
      return cString(s1);
   } else {
      int l = s2.str->len + strlen(s1);
      cString neu( l );
      strcat(strcpy(neu.str->s, s1), s2.str->s);
      neu.str->len = l;
      return neu;
   }
}

__ECL_EXP1__ cString __ECL_EXP2__ operator+(const cString& s1, const char *s2)
{
   if (!s2) {
      return s1;
   } else if (!s1.str || !s1.str->len) {
      return cString(s2);
   } else {
      int l = s1.str->len + strlen(s2);
      cString neu( l );
      strcat(strcpy(neu.str->s, s1.str->s), s2);
      neu.str->len = l;
      return neu;
   }
}

__ECL_EXP1__ cString __ECL_EXP2__ operator+(const cString& s1, const cString& s2)
{
   if (!s1.str || !s1.str->len) {
      return s2;
   } else if (!s2.str || !s2.str->len) {
      return s1;
   } else {
      int l = s1.str->len + s2.str->len;
      cString neu( l );
      strcat(strcpy(neu.str->s, s1.str->s), s2.str->s);
      neu.str->len = l;
      return neu;
   }
}

cString& cString::operator=(const cString& other)
{
   if ( &other != this ) {
      dealloc(str);
      str = other.str;
      if ( str ) ++str->refc;
   }
   return *this;
}

long cString::getLong() const
{ 
   return str ? strtol(str->s, 0, 0) : 0; 
}

double cString::getDouble() const
{ 
   return str ? strtod(str->s, 0) : 0.0; 
}

cString::operator const wchar_t *() const
{
   return wccp();
}

const wchar_t * cString::wccp() const
{
   if ( str != 0 ) {
      if ( str->ws != 0 )
         free(str->ws);
      str->ws = (wchar_t*)malloc((str->len + 1) * 2);
      AnsiToUnicode(str->ws, str->s, str->len + 1);
      return str->ws;
   }

   return 0;
}

unsigned int cString::generateHash() const
{
   unsigned int hash = 0;
   // 2004-04-30 -MW- unchecked str->s changed to ccp() to avoid crash with 0-strings
   for ( const char *key = ccp() ; key && *key ; key++ )
      hash = (hash<<5) + hash + *key;
   return hash;
}


cString cString::getMid(int from, int len) const
{
   if (str && __ECL_ASSERT__(from >= 0, STR_WARN)) {
      if (!__ECL_ASSERT__(from <= str->len, STR_WARN)) from = str->len;
      // 2004-04-30 -MW- redundancy removed -> else if (!__ECL_ASSERT1__(from >= 0)) from = 0;
      if ( len < 0 ) len = str->len - from;
      return cString(str->s+from, len);
   } else return 0;
}

cString cString::getLeft(int len) const
{
   if (str && __ECL_ASSERT__(len >= 0, STR_WARN)) {
      if (len >= str->len) return *this;
      return cString(str->s, len);
   } else return 0;
}

cString cString::getRight(int len) const
{
   if (str && __ECL_ASSERT__(len >= 0, STR_WARN)) {
      int from = str->len - len;
      if ( from <= 0 ) return *this;
      return cString(str->s + from);
   } else return 0;
}

cString cString::getPart(int n, const cString& sep) const
{
   if ( str && __ECL_ASSERT__(n >= 0 && !sep.isEmpty(), STR_WARN) ) {
      int pos_from = 0;
      while ( n-- > 0 ) {
         pos_from = getPos(sep, pos_from);
         // 10.01.2002 -TE- Existiert kein n-ter Teilstring, wird nicht
         // länger der erste Teilstring, sondern ein Leerstring geliefert:
         if ( pos_from < 0 ) return 0;
         // 2004-05-04 -MW- adjust pos_from with sep.getLength()
         pos_from += sep.getLength();
      }
      int pos_to = getPos(sep, pos_from);
      return pos_to < 0 ?
         getMid(pos_from)
       : getMid(pos_from, pos_to - pos_from);
   }

   return 0;
}

cString cString::getPart(int n, const cString& delims, const cString& sep) const
{
   if ( str && __ECL_ASSERT__(n >= 0 && !sep.isEmpty(), STR_WARN) ) {
      int pos_from = 0;
      while ( n-- > 0 ) {
         pos_from = getPos(sep, delims, pos_from);
         // 10.01.2002 -TE- Existiert kein n-ter Teilstring, wird nicht
         // länger der erste Teilstring, sondern ein Leerstring geliefert:
         if ( pos_from < 0 ) return 0;
         // 2004-05-04 -MW- adjust pos_from with sep.getLength()
         pos_from += sep.getLength();
      }
      int pos_to = getPos(sep, delims, pos_from);
      cString part = pos_to < 0 ?
         getMid(pos_from)
       : getMid(pos_from, pos_to - pos_from);
      if ( !part.isEmpty() ) {
         switch ( part[0] ) {
         case '\'':
            if ( strchr(delims, '\'') != 0 ) {
               return part.getRight(1) == "'" ?
                  part.getSubstr(1, part.getLength()-2)
                : part.getMid(1);
            }
            break;
         case '"':
            if ( strchr(delims, '"') != 0 ) {
               return part.getRight(1) == "\"" ?
                  part.getSubstr(1, part.getLength()-2)
                : part.getMid(1);
            }
            break;
         }
      }
      // 2004-05-04 -MW- empty must not be converted to null
      return part;
   }

   return 0;
}

// 08.05.2002 -MW- Die getTail()-Funktionen sind durch Copy&Paste aus den
// getPart()-Funktionen entstanden und unterscheiden sich nur minimalst von
// diesen. Ein Flag mit Defaultwert hätte es auch getan, aber waere nicht
// wirklich schöner gewesen: faellt mir keine Loesung ein ...

cString cString::getTail(int n, const cString& sep) const
{
   if ( str && __ECL_ASSERT__(n >= 0 && !sep.isEmpty(), STR_WARN) ) {
      int pos_from = 0;
      while ( n-- > 0 ) {
         pos_from = getPos(sep, pos_from);
         if ( pos_from < 0 ) return 0;
         // 2004-05-04 -MW- adjust pos_from with sep.getLength()
         pos_from += sep.getLength();
      }
      return getMid(pos_from);
   }

   return 0;
}

cString cString::getTail(int n, const cString& delims, const cString& sep) const
{
   if ( str && __ECL_ASSERT__(n >= 0 && !sep.isEmpty(), STR_WARN) ) {
      int pos_from = 0;
      while ( n-- > 0 ) {
         pos_from = getPos(sep, delims, pos_from);
         if ( pos_from < 0 ) return 0;
         // 2004-05-04 -MW- adjust pos_from with sep.getLength()
         pos_from += sep.getLength();
      }
      cString part = getMid(pos_from);
      if ( !part.isEmpty() ) {
         switch ( part[0] ) {
         case '\'':
            if ( strchr(delims, '\'') != 0 ) {
               return part.getRight(1) == "'" ?
                  part.getSubstr(1, part.getLength()-2)
                : part.getMid(1);
            }
            break;
         case '"':
            if ( strchr(delims, '"') != 0 ) {
               return part.getRight(1) == "\"" ?
                  part.getSubstr(1, part.getLength()-2)
                : part.getMid(1);
            }
            break;
         }
      }
      // 2004-05-04 -MW- empty must not be converted to null
      return part;
   }

   return 0;
}


cString cString::del(int from, int len) const
{
   if ( str && __ECL_ASSERT__(from >= 0 && len >= 0, STR_WARN) ) {
      if (from + len >= str->len) {
         return getLeft(from);
      } else {
         return getLeft(from) + getMid(from+len);
      }
   } else return *this;
}

cString cString::delLeft(int len) const
{
   if ( str && __ECL_ASSERT__(len >= 0, STR_WARN) ) {
      if ( (len = str->len - len) >= str->len )
         return *this;
      if ( len >= 0 )
         return cString(str->s + str->len - len);
   } 
   
   return 0;
}

cString cString::delRight(int len) const
{
   if ( str && __ECL_ASSERT__(len >= 0, STR_WARN) ) {
      if ( (len = str->len - len) >= str->len )
         return *this;
      if ( len >= 0 )
         return cString(str->s, len);
   } 
   
   return 0;
}

/**
 * @brief Teilstring suchen.
 *
 * @param substr Zu suchender Teilstring
 * @param from   Startposition der Suche (ab 0)
 * @return Index der Fundstelle (oder -1 falls nicht gefunden)
 */
int cString::getPos(const cString& substr, int from) const
{
   // 2004-04-30 -MW- substr.isNull() caused crash
   if (str && substr.str && __ECL_ASSERT__(from >= 0, STR_WARN)) {
      if ( from > str->len ) from = str->len;
      const char *pos = strstr(str->s + from, substr);
      return pos ? pos - str->s : -1;
   } else return -1;
}

/**
 * @brief Teilstring suchen, Klammern und Anfuehrungszeichen parsen.
 *
 * Bestimmte Bereiche koennen von der Suche ausgeschlossen werden. Dazu
 * erhaelt @a delims einen String mit einem oder mehreren der folgenden
 * Zeichen:
 *
 * - @c ' = Strings in einfachem Anfuehrungszeichen werden ueberlesen
 * - @c " = Strings in doppelten Anfuehrungszeichen werden ueberlesen
 * - @c ( = Ausdruecke in runden Klammern werden ueberlesen
 * - @c { = Ausdruecke in geschweiften Klammern werden ueberlesen
 * - @c [ = Ausdruecke in eckigen Klammern werden ueberlesen
 *
 * @param substr Zu suchender Teilstring
 * @param delims Von der suche auszuschliessende Bereiche
 * @param from   Startposition der Suche (ab 0)
 * @return Index der Fundstelle (oder -1 falls nicht gefunden)
 */
int cString::getPos(const cString& substr, const cString& delims, int from) const
{
   if ( str == 0 || substr.isEmpty() || from < 0 )
      return -1;

   // 2004-04-30 -MW- unsafe parameters fixed
   if ( from > str->len )
      from = str->len;
   const char *sbs = substr.safeCcp();
   const char *dlm = delims.safeCcp();

   const char *p;
   int first_ch = *sbs;
   int len = strlen(sbs);

   // 2004-04-30 -MW- startposition was missing
   for ( p = str->s + from ; *p ; p++ ) {
      if ( *p == first_ch && strncmp(p, sbs, len) == 0 ) {
         return p - str->s;
      } else {
         switch ( *p ) {
         case '\'':  if ( strchr(dlm, '\'') != 0 ) p = FindNext(p+1, '\''); break;
         case '"':   if ( strchr(dlm, '"')  != 0 ) p = FindNext(p+1, '"'); break;
         case '(':   if ( strchr(dlm, '(')  != 0 ) p = FindMatching(p+1, dlm, ')'); break;
         case '{':   if ( strchr(dlm, '{')  != 0 ) p = FindMatching(p+1, dlm, '}'); break;
         case '[':   if ( strchr(dlm, '[')  != 0 ) p = FindMatching(p+1, dlm, ']'); break;
         }
      }
   }

   return -1;
}

/**
 * @brief Teilstring suchen, Gross-/Kleinschreibung ignorieren.
 *
 * @param substr Zu suchender Teilstring
 * @param from   Startposition der Suche (ab 0)
 * @return Index der Fundstelle (oder -1 falls nicht gefunden)
 */
int cString::getPosNoCase(const cString& substr, int from) const
{
   return getPosNoCase(substr, 0, from);
}

/**
 * @brief Teilstring suchen, Klammern und Anfuehrungszeichen parsen,
 *        Gross-/Kleinschreibung ignorieren.
 *
 * @param substr Zu suchender Teilstring
 * @param delims Von der suche auszuschliessende Bereiche, siehe getPos(const char*,const char*,int)
 * @param from   Startposition der Suche (ab 0)
 * @return Index der Fundstelle (oder -1 falls nicht gefunden)
 */
int cString::getPosNoCase(const cString& substr, const cString& delims, int from) const
{
   if ( str == 0 || substr.isEmpty() || from < 0 )
      return -1;
   if ( from > str->len )
      from = str->len;

   const char *sbs = substr.safeCcp();
   const char *dlm = delims.safeCcp();

   const char *p;
   int first_ch = toupper(*sbs);
   int len = strlen(sbs);

   for ( p = str->s + from; *p ; p++ ) {
      if ( toupper(*p) == first_ch && _strnicmp(p, sbs, len) == 0 ) {
         return p - str->s;
      } else {
         switch ( *p ) {
         case '\'':  if ( strchr(dlm, '\'') != 0 ) p = FindNext(p+1, '\''); break;
         case '"':   if ( strchr(dlm, '"')  != 0 ) p = FindNext(p+1, '"'); break;
         case '(':   if ( strchr(dlm, '(')  != 0 ) p = FindMatching(p+1, dlm, ')'); break;
         case '{':   if ( strchr(dlm, '{')  != 0 ) p = FindMatching(p+1, dlm, '}'); break;
         case '[':   if ( strchr(dlm, '[')  != 0 ) p = FindMatching(p+1, dlm, ']'); break;
         }
      }
   }

   return -1;
}

/**
 * @brief Letztes Auftauchen von Teilstring suchen.
 *
 * @param substr Zu suchender Teilstring
 * @param from   Startposition der Suche (ab 0)
 * @return Index der Fundstelle (oder -1 falls nicht gefunden)
 */
int cString::getLastPos(const cString& substr, int from) const
{
   if (str && __ECL_ASSERT__(from >= 0, STR_WARN)) {
      if ( from > str->len ) from = str->len;
      const char *ptr = str->s + from; int pos = -1;
      while ( (ptr = strstr(ptr, substr)) != 0 ) pos = ptr++ - str->s;
      return pos;
   } else return -1;
}

cString cString::trimLeft(const cString& set) const
{
   if (str) {
      if (!set.isEmpty()) {
         const char *cp = str->s;
         while ( strchr(set, *cp) ) ++cp;
         return cp == str->s ? *this : cString(cp);
      } else {
         const char *cp = str->s;
         while ( isspace(*cp) ) ++cp;
         return cp == str->s ? *this : cString(cp);
      }
   } else return *this;
}

cString cString::trimRight(const cString& set) const
{
   if (str) {
      if (!set.isEmpty()) {
         int j = str->len-1;
         while ( j >= 0 &&  strchr(set, str->s[j]) ) --j;
         return j == str->len-1 ? *this : cString(str->s, j+1);
      } else {
         int j = str->len-1;
         while ( j >= 0 &&  isspace(str->s[j]) ) --j;
         return j == str->len-1 ? *this : cString(str->s, j+1);
      }
   } else return *this;
}

cString cString::trim(const cString& set) const
{
   if (str) {
      if (!set.isEmpty()) {
         int i = 0;
         while ( strchr(set, str->s[i]) ) ++i;
         int j = str->len-1;
         while ( j >= i && strchr(set, str->s[j]) ) --j;
         return (i == 0) && (j == str->len-1) != 0 ? *this : cString(str->s+i, j-i+1);
      } else {
         int i = 0;
         while ( isspace(str->s[i]) ) ++i;
         int j = str->len-1;
         while ( j >= i && isspace(str->s[j]) ) --j;
         return (i == 0) && (j == str->len-1) != 0 ? *this : cString(str->s+i, j-i+1);
      }
   } else return *this;
}

cString cString::padRight(int width, const cString &fill)
{
   return *this + cString(width-getLength(),fill);
}

cString cString::padLeft(int width, const cString &fill)
{
   return cString(width-getLength(),fill) + *this;
}

cString cString::getUpcase() const
{
   if ( str && str->s ) {
      cString upper(str->s, str->len);
      _strupr(upper.str->s);
      return upper;
   } else {
      return *this;
   }
}

cString cString::getLocase() const
{
   if ( str && str->s ) {
      cString lower(str->s, str->len);
      _strlwr(lower.str->s);
      return lower;
   } else {
      return *this;
   }
}

cString cString::replace(const cString& from, const cString& to) const
{
   // 2004-04-30 -MW- unsafe parameters fixed
   int pos,start=0;
   int lenfrom = from.getLength();
   int lento = to.getLength();

   cString neu(*this);
   if (lenfrom) {
      while ((pos = neu.getPos(from,start)) >= 0) {
         neu = neu.getLeft(pos)+to+neu.getMid(pos+lenfrom);
         start = pos+lento;
      }
   }
   return neu;
}

cString cString::replace(int from, int len, const cString& by) const
{
   if ( str && __ECL_ASSERT__(from >= 0 && len >= 0, STR_WARN) ) {
      if (from + len >= str->len) {
         return getLeft(from) + by;
      } else {
         return getLeft(from) + by + getMid(from+len);
      }
   } else return *this;
}

cString cString::insert(int pos, const cString& s) const
{
   if (str == 0 || pos <= 0) {
      return s + *this;
   } else if (pos >= str->len) {
      return *this + s;
   } else {
      return getLeft(pos) + s + getMid(pos);
   }
}


/**
*  Encode the string to quoted-printable format.
*  Generally non printable characters below 0x20 (' ') and above 0x7E ('~')
*  are replaced by '=' followed by two hex digits. The character '=' itself
*  is encoded in consequence as "=3D". Only CR, LF and TAB are not encoded.
*  (Note: This coding is described in RFC 2045 and used in e-mails to transfer
*  strings with any characters in a widely compatible ascii format).
*
*  @param width Column where to insert soft breaks. RFC 2045 requires that
*     encoded text lines must not be longer than 76 characters. So special
*     marked newlines '\n' must be inserted into longer strings which are
*     removed by the decoder. You can change @a width or set it to 0, to 
*     turn soft breaks completely off.
*  @param encode_all If true, in contrast to RFC 2045 all control
*     characters including TAB, CR and LF are encoded.
*/
cString cString::encodeQuotedPrintable(int width, bool encode_all) const
{
   int col = 0;
   cString result;
   if (width == 0) {
      width = INT_MAX;
   }

   for (int i = 0; str && i < str->len; i++) {
      unsigned char c = str->s[i];
      bool encode = false;
      if ( c > 32 && c < 127 && c != '=') {
         // printable characters except '='
         encode = false;
      } else {
         switch (c) {
         case 9:
            // encode TAB at the end of the line or if encode_all selected
            encode = (encode_all || str->s[i+1] == '\r' || str->s[i+1] == '\n');
            break;
         case 10:
         case 13:
            // encode CR and LF if encode_all selected
            encode = encode_all;
            break;
         case 32:
            // encode SPACE only at the end of the line
            encode = (str->s[i+1] == '\r' || str->s[i+1] == '\n');
            break;
         default:
            // all other will be encoded
            encode = true;
            break;
         }
      }

      if (encode) {
         if (col+3 >= width) {
            result += "=\n";
            col = 0;
         }
         char hex[4];
         ::sprintf(hex, "=%02X", c);
         result += hex;
         col += 3;
      } else {
         if (col+1 >= width) {
            result += "=\n";
            col = 0;
         }
         result += (char)c;
         col++;
      }
   }

   return result;
}


/**
*  If the encoded string contains "=00" this will tuncate the decoded string.
*/
cString cString::decodeQuotedPrintable() const
{
   cString result;

   char hex[3];
   hex[2] = 0;

   for (int i = 0; str && i < str->len; i++) {
      if (str->s[i] == '=') {
         if (str->s[i+1] == '\r' && str->s[i+2] == '\n') {
            // remove soft break CRLF
            i += 2;
         } else if (str->s[i+1] == '\n' || str->s[i+1] == '\r') {
            // remove soft breaks CR *or* LF. This is more flexible
            // than the canonical form described in RFC 2045.
            i += 1;
         } else if (isxdigit(str->s[i+1]) && isxdigit(str->s[i+2])) {
            // decode "=HH", lowercase digits are allowed
            hex[0] = str->s[i+1];
            hex[1] = str->s[i+2];
            int c = strtol(hex,0,16);
            if (c) {
               result += (char)c;
               i += 2;
            } else {
               return result;
            }
         } 
      } else {
         result += str->s[i];
      }
   }
   return result;
}




/**
*  Search the string for appearences of "%0", "%1" ... "%9" and replace
*  all of them with the @e lowest digit by @a to. Example: arg("X") applied
*  to "%1-%2-%1" becomes "X-%2-X".
*/
cString cString::arg(const cString& to) const
{
   char from[3] = "%?";
   const char *pos = (str ? str->s : 0);

   while (pos && (pos = strchr(pos,*from)) != 0) {
      if (isdigit(pos[1]) && pos[1] < from[1]) {
         from[1] = pos[1];
         pos += 2;
      } else
         pos++;
   }

   return isdigit(from[1]) ? replace(from, to) : *this;
}

/**
 * Es werden die in C üblichen Konstanten ersetzt: @c \\n, @c \\t, @c \\v, @c \\b, @c \\r,
 * @c \\f, @c \\a, @c \\\\, @c \\?, @c \\', @c \\", @c \\ooo (oktal) und @c \\xhh (hexadezimal). Besonderheit:
 * @c \\0 (NUL) verkürzt gegebenenfalls den die Zeichenkette!
 */
cString cString::replaceEsc() const
{
   cString tmp = ">" + *this;
   return replaceEscape( (char*)(tmp.ccp()+1) );
}


cString cString::replaceNoCase(const cString &from, const cString &to) const
{
   // 2004-04-30 -MW- parameters changed to cString, unsafe parameters fixed
   int pos,start=0;
   int lenfrom = from.getLength();
   int lento = to.getLength();

   cString neu(*this);
   if (lenfrom) {
      while ((pos = neu.getPosNoCase(from,start)) >= 0) {
         neu = neu.getLeft(pos)+to+neu.getMid(pos+lenfrom);
         start = pos+lento;
      }
   }
   return neu;
}

cString cString::replaceTab(int width, const cString& by) const
{
   return replaceTab(0, width, by);
}

cString cString::replaceTab(int nullpos, int width, const cString& by) const
{
   cString result = isNull() ? 0 : "";
   int tab = nullpos;
   for (int i=0; i<getLength(); i++) {
      char ch = str->s[i];
      if (ch == '\t') {
         int new_tab = (((int)(tab/width))+1)*width;
         result += cString(new_tab-tab,by);
         tab = new_tab;
      } else {
         result += ch;
         if (ch == '\n') {
            tab = nullpos;
         } else if (isprint(ch)) {
            tab++;
         }
      }
   }
   return result;
}


/**
*  Usually the next word delimited by whitespaces is read from @a istream. This is the same
*  behaviour known from @a std::string. The following standard manipulators
*  of <iostream> can be used to modify the behaviour:
*  -  @c std::skipws and @c std::noskipws (flag @c std::ios::skipws) can turn
*     on and off skipping leading whitespaces in the stream. Defaults to on.
*     This is the same behaviour you know from @c std::string.
*  -  @c setw(n) [with n >= 0] restricts the length of the following input words to @c n-1 chars
*     (n encloses the terminating @c \0 char). In contrast to @c ostream where
*     @c setw(n) only affects the next output item, this setting persist on
*     @c istream until the next @c setw(n). @c setw(0) turns the length
*     restriction off. This is the same behaviour you know from @c ste::string.
*  -  @c setw(n) [with n < 0] activates line-by-line input. Whitespaces are
*     not skipped (@c std::skipws and @c std::noskipws has no effect). All
*     chars up to (and excluding) the next '\n' (or std::endl) are read.
*     <b>This is a special feature of cString class that std::string does not offer!</b>
*     (or I don't know the trick how to do ...)
*/
std::istream& operator>>(std::istream& is, cString& s)
{
   // Implementierung von operator>> von Jennifer Harmuth, 2004-11-04
   if(is.good()==false) {
      return is;
   }
   char z;
   if((is.flags() & std::ios::skipws) && is.width() >= 0) { 
      while(is.get(z) && isspace(z)) {}
      is.putback(z);
   }
   cString word = "";
   int w = is.width();
   if(w == 0) {
      while(is.get(z) && !isspace(z)) {
         word = word + cStringf("%c", z);
      }
   } else if(w > 0) {
      while((w-- > 1) && (is.get(z)) && (!isspace(z))) {
         word = word + Str(z);
      }
   } else {
      while(is.get(z) && z != '\n') {
         word = word + Str(z);
      }
//      if(is.eof() && word.getLength() > 0) {
//         is.clear(ios::goodbit);
//      }
   }
   s = word; // + (is.good()?"(+)":"(-)");
   return is;
}


cString& cString::getLine(std::istream &is)
{
   if (!is) {
      *this = cString();
   } else {
      *this = "";
      int endchar;
      char buffer[128];
      while ((buffer[0]=0,is) && (endchar = is.get(buffer, sizeof(buffer)).get()) != '\n') {
         *this += buffer;
         is.putback((char)endchar);
      }
      *this += buffer;
   }
   return *this;
}




// ===========================================================================
// cString = cStringf(const char *fmt, ...)
// ---------------------------------------------------------------------------
//
// ===========================================================================

#define ALLOW_BUILT_IN 1

#if ALLOW_BUILT_IN && defined(__ECL_VCPP__)
   // Use built in function:
   // int _vsnprintf( char *buffer, size_t count, const char *format, va_list argptr );
   #define VSNPRINTF _vsnprintf
#else
   // The currently known problem is "%g" formatting :-(
   // If built in vsnprintf is available, use an old, unsecure sprintf as workaround.
// PR GNUC
//   #error portalble snprintf not yet completly tested!
   #warning portable snprintf not yet completly tested!
// PR GNUC
   
   #define HAVE_SNPRINTF
   #define PREFER_PORTABLE_SNPRINTF
   #include <stdlib.h>

   extern "C" {
      #include "driver/snprintf/snprintf.c"
   }

   #define VSNPRINTF portable_vsnprintf
#endif


cString &cString::sprintf(const char* fmt, ...)
{
   int size = 1024;
   char *buffer = new char[size];
   if (fmt == 0) {
      fmt = (const char *)*this;
   }

   while (size) {
      va_list ap;
      va_start( ap, fmt );
      int used = VSNPRINTF(buffer, size, fmt, ap);
      va_end( ap );
      
      if ((used > -1) && (used < size)) {
         size = 0;
      } else {
         size = (used > -1) ? used + 1 : size * 2;
         delete[] buffer;
         buffer = new char[size];
      }
   }
   *this = cString(buffer);
   delete[] buffer;

   return *this;
}


cString &cString::vsprintf(const char *fmt, va_list argptr)
{
   int size = 1024;
   char *buffer = new char[size];
   if (fmt == 0) {
      fmt = (const char*)*this;
   }

   while(size) {
      int used = VSNPRINTF(buffer, size, fmt, argptr);
      
      if((used > -1) && (used < size)) {
         size = 0;
      } else {
         size = (used > -1) ? used + 1 : size * 2;
         delete[] buffer;
         buffer = new char[size];
      }
   }
   *this = cString(buffer);
   delete[] buffer;

   return *this;
}


__ECL_EXP1__ cString __ECL_EXP2__ cStringf(const char *fmt, ...)
{
#if 0
   if (fmt == 0) {
      return cString();
   } else {
      va_list ap;
      va_start( ap, fmt );
      cString result;
      result.vsprintf(fmt, ap);
      va_end( ap );
      return result;
   }
#else
   // TBD: Dieser Puffer mit fester Laenge ist keine gute & sichere Loesung !!!
   const int buffer_size = 1000;
   const int max_message_length = 24;
   char buffer[buffer_size + max_message_length];
   
   va_list ap;
   va_start(ap, fmt);
   int used_buffer = vsprintf(buffer, fmt, ap);
   va_end(ap);
   
   if (!__ECL_ASSERT_PRINTF__(used_buffer < buffer_size, STR_ERROR, ("internal cStringf buffer overflow") ) ) {
      strcpy(buffer+buffer_size, "*cStringf overflow*");
   }
   return cString(buffer);
#endif
}


// double-Konvertierungen und andere Auslauffunktionalitaeten
// ---------------------------------------------------------------------------

// Formatierungs-Informationen
static char def_decimal_sep  = ',';  // Separator fuer Dezimalstellen ("1,00")
static char def_thousand_sep = '.';  // Separator fuer Tausender-Stellen ("1.000")
static char def_date_sep     = '.';  // Datumstrenner (01.04.1999)
static char def_time_sep     = ':';  // Zeittrenner (13:00:00)
static int  def_date_format  = 0;    // Datumsformat (0=TT.MM.YYYY, 1=MM.DD.YYYY)

cString::cString(double d, int prec, char decimal_sep, char thousand_sep)
{
   alloc(40);
   convDbl2Str(str->s, d, prec, decimal_sep, thousand_sep);
   str->len = strlen(str->s);
}

void cString::initFormatOptions()
{
   static bool init = false;

   if ( !init ) {
      init = true;

      #ifdef __OS2__
         char buffer[20];
         static char pmn[] = "PM_National";
         PrfQueryProfileString(HINI_PROFILE, pmn, "sDecimal", "?", buffer, sizeof buffer - 1);
         def_decimal_sep = buffer[0];
         PrfQueryProfileString(HINI_PROFILE, pmn, "sThousand", "?", buffer, sizeof buffer - 1);
         def_thousand_sep = buffer[0];
         PrfQueryProfileString(HINI_PROFILE, pmn, "sDate", "?", buffer, sizeof buffer - 1);
         def_date_sep = buffer[0];
         PrfQueryProfileString(HINI_PROFILE, pmn, "sTime", "?", buffer, sizeof buffer - 1);
         def_time_sep = buffer[0];
         def_date_format = PrfQueryProfileInt(HINI_PROFILE, pmn, "iDate", 0);
      #else
         // ...
      #endif
   }
}

bool cString::convStr2Dbl(const char *buffer, double& result, char decimal_sep, char thousand_sep)
{
   double d=0;
   bool minus = false;
   bool digit_seen = false;
   bool sep_seen = true;

   while(isspace(*buffer)) ++buffer;
   switch (*buffer) {
    case '-': minus = true;
    case '+': ++buffer;
    default:  break;
   }

   if (! decimal_sep ) decimal_sep = def_decimal_sep;
   if (! thousand_sep ) thousand_sep = def_thousand_sep;

   /* Vorkammastellen */
   while( *buffer && *buffer != decimal_sep ) {
      if (thousand_sep == *buffer && !sep_seen) {
         sep_seen = true;
         /* Ignorieren */
      } else if (isdigit( *buffer )) {
         digit_seen = true;
         d = 10.0*d + *buffer-'0';
         sep_seen = false;
      } else {
         break;
      }
      ++buffer;
   }

   if (*buffer==decimal_sep) {
      /* Nachkommastellen */
      double pot = 1.0;
      ++buffer;
      while (isdigit(*buffer))  {
         digit_seen = true;
         pot /= 10.0;
         d += (*buffer++ - '0') * pot;
      }
      while(isspace(*buffer)) ++buffer;
   }
   while (isspace( *buffer )) ++buffer;

   if (digit_seen) result = minus ? -d : d;
   return digit_seen && !*buffer;
}

void cString::convDbl2Str(char *buffer, double val, int prec, char decimal_sep, char thousand_sep)
{
   long vk;
   if (! decimal_sep ) decimal_sep = def_decimal_sep;
   if (! thousand_sep ) thousand_sep = def_thousand_sep;

   if (!prec) thousand_sep = '\0';
   if (val < 0) *buffer++ = '-', val = -val;
   *buffer = '\0';
   if (prec>0) {
      vk = (long)( val+pow( 10.0, -prec ) / 2.0); /* runden */
   } else {
      vk = (long)val;
   }
   if (thousand_sep && vk >= 1000000) {
      ::sprintf( buffer, "%ld%c%03ld%c%03d", vk/1000000L, thousand_sep, (vk/1000)%1000, thousand_sep, (int)(vk % 1000) );
   } else if ( thousand_sep && vk >= 1000) {
      ::sprintf( buffer, "%ld%c%03d", vk/1000, thousand_sep, (int)(vk % 1000) );
   } else {
      ::sprintf( buffer, "%ld", vk );
   }

   char *bp = buffer+strlen(buffer)-1;
   char save = *bp;
   if (prec > 0) {
      ::sprintf( bp, "%.*f", prec, val > vk ? val-vk : 0.0);
      *bp++ = save;
      *bp = decimal_sep;
   } else if ( prec < 0 && val > vk ) {
      ::sprintf( bp, "%g", val-vk );
      *bp++ = save;
      *bp = decimal_sep;
   }
}


}; // namespace ecl

