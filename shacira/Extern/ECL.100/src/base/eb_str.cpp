// ===========================================================================
// eb_str.cpp                                                   ______ /  ECL
// Autoren: Udo Pfrengle, Markus Wuertz, Thomas Epting         /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cString          - Udos dynamische Stringverwaltung.
//
// Ausserhalb aller Klassen sind folgende GLOBALE (uaergs) FUNKTIONEN (blaeh)
// verfuegbar:
//
//    cString cStringf(const char *fmt, ...);
//    cString EclHashKey(cString key);
//    cString Str(char ch);
//    cString Str(int n);
//    cString Str(double d);
//
// ===========================================================================

#include "base/eb_str.hpp"


#ifdef __DEBUG_ALLOC__
   #include <new.h>
#endif

#if defined __ECL_OS2__
   #define INCL_WINSHELLDATA
   #include <os2.h>
#elif defined __ECL_W32__
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"

int inline strxlen(const char *str)
   { return str ? strlen(str) : 0; }

#endif /*__INTERFACE__*/


#include <stdarg.h>
#include <math.h>

#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <stdio.h>



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




#ifdef __INTERFACE__

// ===========================================================================
// Definition cString
// ---------------------------------------------------------------------------
//
// cBase
//  +--cString
//
// ===========================================================================


class __ECL_DLLEXPORT__ cString /*: public cBase*/ {
   friend __ECL_EXP1__ cString __ECL_EXP2__ cStringf(const char *fmt, ...);

private:
   // Verwaltungseinheit fuer einen String
   struct xstr {
      int len;    // aktuelle Laenge
      int size;   // allokierte Groesse
      int refc;   // Referenzzaehler
      char s[1];  // Groesse dynamisch
   } *str;

public:
   // Defaultkonstruktor "uninitialisiert"
   cString()
      { str=0; }
   // Konstruktor ueber Stringlaenge
   cString(int l)
      { if (l) alloc(l); else str=0; }
   // Konstruktor ueber const char * und optional Stringlaenge
   cString(const char *s, int l = -1)
      { if (s) init(s, l<0 ? strlen(s) : l); else str=0; }
   // Konstruktor ueber anderen cString
   cString(const cString& other)
      { str = other.str; if ( str ) ++str->refc; }
   // Konstruktor ueber formatierte double-Zahl
   cString(double d, int prec, char sep1 = '\0', char sep2 = '\0');
   // Konstruktor ueber sich wiederholende Zeichenfolgen
   cString(int n, const char *s);

   // Destruktor
   ~cString()
      { dealloc(str); }

   // Freigeben der Resourcen
   void clear()
      { dealloc(str); }

   // Ist der String uninitialisiert?
   inline bool isNull() const
      { return !str; }
   // Enthaelt der String keine Zeichen?
   inline bool isEmpty() const
      { return !str || !str->len; }
   // Ermittle die aktuelle Zeichenzahl im String
   inline int getLength() const
      { return str ? str->len : 0; }
   // Ermittle die aktuelle Puffergroesse des Strings
   inline int getSize() const
      { return str ? str->size : 0; }

   // Stringpuffer mit size Bytes fuer direkten Zugriff anfordern, bis zum
   // unlockBuffer darf der cString *NUR* ueber den Puffer benutzt werden!
   char *lockBuffer(int size);
   // String nach direktem Zugriff wieder validieren
   void unlockBuffer();

   // Zuweisung: const char *
   cString& operator=(const char* other)
      { return assign(other, strxlen(other)); }
   // Zuweisung: cString
   cString& operator=(const cString& other);
   // Zuweisung: long (???? ist das ueberhaupt brauchbar ????)
   cString& operator=(const long& i);
   // Zuweisung: double (???? ist das ueberhaupt brauchbar ????)
   cString& operator=(const double& i);

   // Vergleiche zwei Strings (beachte Gross-/Kleinschreibung)
   int compare(const cString& other, int max_chars = -1) const;
   // Vergleiche cString mit const char * (beachte Gross-/Kleinschreibung)
   int compare(const char *other, int max_chars = -1) const;
   // Vergleiche zwei Strings (ignoriere Gross-/Kleinschreibung)
   int compareNoCase(const cString& other, int max_chars = -1) const;
   // Vergleiche cString mit const char * (ignoriere Gross-/Kleinschreibung)
   int compareNoCase(const char *other, int max_chars = -1) const;

   // Vergleichsoperatoren auf cString
   bool operator==(const cString& other) const
      { return compare(other) == 0; }
   bool operator!=(const cString& other) const
      { return compare(other) != 0; }
   bool operator<(const cString& other) const
      { return compare(other) <  0; }
   bool operator>(const cString& other) const
      { return compare(other) >  0; }
   bool operator<=(const cString& other) const
      { return compare(other) <= 0; }
   bool operator>=(const cString& other) const
      { return compare(other) >= 0; }

   // Vergleichsoperatoren auf const char *
   bool operator==(const char *other) const
      { return compare(other) == 0; }
   bool operator!=(const char *other) const
      { return compare(other) != 0; }
   bool operator<(const char *other) const
      { return compare(other) <  0; }
   bool operator>(const char *other) const
      { return compare(other) >  0; }
   bool operator<=(const char *other) const
      { return compare(other) <= 0; }
   bool operator>=(const char *other) const
      { return compare(other) >= 0; }

   // Cast-Umwandlung nach const char *
   operator const char *() const
      { return str ? str->s : 0; }
   // Umwandlung nach const char *
   const char *ccp() const
      { return str ? str->s : 0; }
   // Umwandlung nach long (durch Interpretation)
   long getLong() const
      { return str ? strtol(str->s, 0, 0) : 0; }
   // Umwandlung nach double (durch Interpretation)
   double getDouble() const
      { return str ? strtod(str->s, 0) : 0.0; }

   // Generieren eines Hash-Codes aus dem String
   unsigned int generateHash() const;

   // Konkatenation
   friend __ECL_OPEXP__ cString  operator+(const char *s1, const cString s2);
   friend __ECL_OPEXP__ cString  operator+(const cString s1, const char *s2);
   friend __ECL_OPEXP__ cString  operator+(const cString s1, const cString s2);

   // Konkatenation und Zuweisung
   cString& operator+=(const cString& other)
      { return other.str ? concat( other.str->s, other.str->len) : *this; }
   cString& operator<<(const cString& other)
      { return other.str ? concat( other.str->s, other.str->len) : *this; }
   cString& operator+=(const char * other)
      { return concat( other, strxlen(other) ); }
   cString& operator<<(const char * other)
      { return concat( other, strxlen(other) ); }
   cString& operator<<(double f)
      { return *this<<cStringf("%g", f); }
   cString& operator+=(double f)
      { return *this+=cStringf("%g", f); }

   // Zeichen extrahieren
   #if __ECL_DEBUG__ > 0
      char& operator[](int i);
   #else
      char& operator[](int i) { return str->s[i]; }
   #endif

   // Teilstring von links her extrahieren
   cString getLeft(int len) const;
   // Teilstring von rechts her extrahieren
   cString getRight(int len) const;
   // Teilstring der Laenge len ab Startposition extrahieren
   cString getMid(int from, int len = -1) const;
   // Teilstring von Startposition bis Zielposition extrahieren
   cString getSubstr(int from, int to) const
      { return to < from ? cString() : getMid(from, to - from + 1); }

   // Liefert den 'n'-ten Teilstring in einem durch 'sep' separierten String
   cString getPart(int n, const char *sep = ",") const;
   // Liefert den 'n'-ten Teilstring (wie getPart(n,s), jedoch Klammern und Anfuehrungszeichen parsen)
   cString getPart(int n, const char *delims, const char *sep) const;

   // Teilstring suchen (liefert -1 falls nicht gefunden)
   int getPos(const char *substr, int from = 0) const;
   // Teilstring suchen (wie getPos(s,f), jedoch Klammern und Anfuehrungszeichen parsen)
   int getPos(const char *substr, const char *delims, int from = 0) const;
   // Teilstring suchen, (wie getPos(s,f), jedoch Gross-/Kleinschreibung ignorieren)
   int getPosNoCase(const char *substr, int from = 0) const;
   // Teilstring suchen, (wie getPos(s,d,f), jedoch Gross-/Kleinschreibung ignorieren)
   int getPosNoCase(const char *substr, const char *delims, int from = 0) const;
   // Letztes Auftauchen von Teilstring suchen (liefert -1 falls nicht gefunden)
   int getLastPos(const char *substr, int from = 0) const;

   // Leerzeichen bzw. Zeichen aus set links entfernen
   cString trimLeft(const char *set = 0) const;
   // Leerzeichen bzw. Zeichen aus set rechts entfernen
   cString trimRight(const char *set = 0) const;
   // Leerzeichen bzw. Zeichen aus set links und rechts entfernen
   cString trim(const char *set = 0) const;

   // String in GROSSBUCHSTABEN umwandeln
   cString getUpcase() const;
   // String in kleinbuchstaben umwandeln
   cString getLocase() const;

   // Teilstring der Laenge len ab Startposition loeschen
   cString del(int from, int len) const;
   // Teilketten ersetzen
   cString replace(const char *from, const char *to) const;
   // alle Tabulatoren '\t' ersetzen
   cString replaceTab(int width=8, const char *by=" ") const;
   // einzelnen Tabulator '\t' ersetzen
   cString replaceTab(int nullpos, int width, const char *by=" ") const;

   // Hilfe fuer 'dirty-Tricks'
   // void setLength(int len)
   //    { __ECL_ASSERT2__(0,("Don't use dirty Tricks!"));
   //      if ( str ) str->s[str->len = len] = '\0'; }
   // void setLength()
   //    { __ECL_ASSERT2__(0,("Don't use dirty Tricks!"));
   //      if ( str ) str->s[str->len = strlen(str->s)] = '\0'; }

   // Ausgabe auf ostream
   friend __ECL_OPEXP__ ostream& operator<<(ostream& os, const cString& s)
      { return os << (s.str ? s.str->s : "(NULL)"); }

   // Formatierung
   static bool convStr2Dbl(const char *buffer, double& result, char decimal_sep = '\0', char thousand_sep = '\0');
   static void convDbl2Str(char *buffer, double val, int prec, char decimal_sep = '\0', char thousand_sep = '\0');

   // Diagnosehilfen
   void showDebugInfo();

protected:
   void alloc(int l);
   void dealloc(xstr *&str);

   // Allokiere Platz fuer 'len' Bytes und initialisiere mit Zeichenkette s
   void init(const char *s, int len);

   cString& concat(const char *second, int slen);
   cString& assign(const char *s, int slen);

   // Diagnosehilfen
   static void setDebug(int d);
   static void showDiagnostic();

   // minimale Stringlaenge
   static void setMinStrSize(int m);

   static void initFormatOptions();
};

// EclHashKey fuer cString ermitteln
inline unsigned int EclHashKey(cString key)
   { return key.generateHash(); }

// Typumwandlung char -> cString
inline cString Str(char ch)
   { return cStringf("%c", ch); }

// Typumwandlung int -> cString
inline cString Str(int n)
   { return cStringf("%d", n); }

// Typumwandlung double -> cString
inline cString Str(double f)
   { return cStringf("%g", f); }

__ECL_OPEXP__ cString   operator+(const char *s1, const cString s2);
__ECL_OPEXP__ cString   operator+(const cString s1, const char *s2);
__ECL_OPEXP__ cString   operator+(const cString s1, const cString s2);
__ECL_OPEXP__ ostream&  operator<<(ostream& os, const cString& s);

#endif /* __INTERFACE__ */


// Diagnosehilfen
// ---------------------------------------------------------------------------

// __ECL_DEBUG__ >= 2 ermoeglicht die Fehlersuche in cString selbst!

#if __ECL_DEBUG__ > 1

   #define DBG(stmt) stmt;
   #define IFDBG(stmt) if ( debug ) { stmt; }

   static int debug = 0;
   static int livin_strings = 0;
   static int allocated = 0;

   void cString::setDebug(int d) { debug = d; }

   void cString::showDiagnostic()
   {
      cBase::DbgInfo("%d active strings consuming %d bytes of memory", livin_strings, allocated );
   }

#else

   #define DBG(stmt)
   #define IFDBG(stmt)

   void cString::setDebug(int /*d*/)
   {
      cBase::DbgInfo("cString::setDebug() - Debug deactivated");
   }

   void cString::showDiagnostic()
   {
      cBase::DbgInfo("cString::showDiagnostics() - Debug deactivated");
   }

#endif

void cString::showDebugInfo()
{
   if (str) cBase::DbgInfo("cString(%p) refc=%d, size=%d, len=%d, '%s'", str, str->refc, str->size, str->len, str->s);
   else cBase::DbgInfo("cString(NULL)");
}


// Modullokale Variablen und statische Funktionen
// ---------------------------------------------------------------------------

// minimale Stringlaenge
static unsigned min_str_size = 80;
void cString::setMinStrSize(int m) { min_str_size = m; }

// Fehlertoleranz beim Operator []
#if __ECL_DEBUG__ > 0
   static char null_char = '\0';

   char& cString::operator[](int i)
   {
      if (str && i >= 0 && i <= str->len) return str->s[i];
         else return (null_char = '\0');
   }
#endif



// Implementierung cString - Kernfunktionen
// ===========================================================================

void cString::alloc(int l)
{
   if (l<(int)min_str_size) l=min_str_size;
   str=(xstr*)malloc(sizeof *str + l);
   str->size = l;
   str->refc = str->len = 0;
   str->s[0] = '\0';

   IFDBG(DbgInfo("cString::alloc(%d) -> %p", l, str))
   DBG(++livin_strings)
   DBG(allocated += l)
}

void cString::dealloc( xstr *&str )
{
   if (str) {
      if (__ECL_ASSERT2__(str->refc >= 0,("cString: attempt to free already freed",str->s))) {
         IFDBG(DbgInfo( str->refc==0 ? "cString(%p)::dealloc and free '%s'" : "cString(%p)::dealloc '%s'", str, str->s))
         if (str->refc-- == 0) {
            DBG(--livin_strings)
            DBG(allocated -= str->size)
            free(str);
         }
      }
      str = NULL;
   }
}

void cString::init( const char *s, int len )
{
   alloc(len);
   if (s) {
      strncpy(str->s, s, len);
      str->s[len] = '\0';
      str->len = strlen(str->s);
   }
   IFDBG(DbgInfo( s ? "cString(%p)::init(%s)" : "cString(%p)::init(NULL)", str, str->s))
}

cString& cString::assign(const char *other, int l)
{
   if (!str || str->refc || str->size < l) {
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

cString& cString::concat(const char *other, int l)
{
   if (str) {
      l += str->len;
      assign( str->s, l );
      if (other) strcat(str->s, other);
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

// Implementierung cString - weitere Konstruktoren
// ===========================================================================

cString::cString(int n, const char *s)
{
   if (n<0 || s==0) {
      str = 0;
   } else {
      int len = strlen(s);
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


// Implementierung cString - Methoden und Operatoren
// ===========================================================================

int cString::compare(const cString& other, int max_chars) const
{
   if ( str && other.str ) {
      return max_chars > 0 ?
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
      return max_chars > 0 ?
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

int cString::compareNoCase(const cString& other, int max_chars) const
{
   if ( str && other.str ) {
      return max_chars > 0 ?
         strnicmp(str->s, other.str->s, max_chars)
       : stricmp(str->s, other.str->s);
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
      return max_chars > 0 ?
         strnicmp(str->s, other, max_chars)
       : stricmp(str->s, other);
   } else if ( str ) {
      return 1;
   } else if ( other ) {
      return -1;
   } else {
      return 0;
   }
}

__ECL_EXP1__ cString __ECL_EXP2__ operator+(const char *s1, const cString s2)
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

__ECL_EXP1__ cString __ECL_EXP2__ operator+(const cString s1, const char *s2)
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

__ECL_EXP1__ cString __ECL_EXP2__ operator+(const cString s1, const cString s2)
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

cString& cString::operator=(const long& i)
{
   char buffer[30];
   sprintf(buffer, "%ld", i);
   return assign(buffer, strlen(buffer) );
}

cString& cString::operator=(const double& f)
{
   char buffer[30];
   sprintf(buffer, "%g", f);
   return assign(buffer, strlen(buffer) );
}

unsigned int cString::generateHash() const
{
   unsigned int hash = 0;
   for ( const char *key = str->s ; key && *key ; key++ )
      hash = (hash<<5) + hash + *key;
   return hash;
}


cString cString::getMid(int from, int len) const
{
   if (str && __ECL_ASSERT1__(from >= 0)) {
      if (!__ECL_ASSERT1__(from <= str->len)) from = str->len;
         else if (!__ECL_ASSERT1__(from >= 0)) from = 0;
      if ( len < 0 ) len = str->len - from;
      return cString(str->s+from, len);
   } else return cString();
}

cString cString::getLeft(int len) const
{
   if (str && __ECL_ASSERT1__(len >= 0)) {
      if (len >= str->len) return *this;
      return cString(str->s, len);
   } else return cString();
}

cString cString::getRight(int len) const
{
   if (str && __ECL_ASSERT1__(len >= 0)) {
      int from = str->len - len;
      if ( from >= str->len ) return cString();
      if ( from <= 0 ) return *this;
      return cString(str->s + from);
   } else return cString();
}

cString cString::getPart(int n, const char *sep) const
{
   if ( str && __ECL_ASSERT1__(n >= 0) ) {
      int pos_from = 0;
      while ( n-- > 0 ) {
         pos_from = getPos(sep, pos_from) + 1;
         // 10.01.2002 -TE- Existiert kein n-ter Teilstring, wird nicht
         // länger der erste Teilstring, sondern ein Leerstring geliefert:
         if ( pos_from <= 0 ) return 0;
      }
      int pos_to = getPos(sep, pos_from);
      return pos_to < 0 ?
         getMid(pos_from)
       : getMid(pos_from, pos_to - pos_from);
   }

   return 0;
}

cString cString::getPart(int n, const char *delims, const char *sep) const
{
   if ( str && __ECL_ASSERT1__(n >= 0) ) {
      int pos_from = 0;
      while ( n-- > 0 ) {
         pos_from = getPos(sep, delims, pos_from) + 1;
         // 10.01.2002 -TE- Existiert kein n-ter Teilstring, wird nicht
         // länger der erste Teilstring, sondern ein Leerstring geliefert:
         if ( pos_from <= 0 ) return 0;
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
         return part;
      }
   }

   return 0;
}

cString cString::del(int from, int len) const
{
   if (str && __ECL_ASSERT1__(from >= 0 && len >= 0)) {
      if (from + len >= str->len) {
         return getLeft(from);
      } else {
         return getLeft(from) + getMid(from+len);
      }
   } else return *this;
}

int cString::getPos(const char *substr, int from) const
{
   if (str && __ECL_ASSERT1__(from >= 0)) {
      if ( from > str->len ) from = str->len;
      const char *pos = strstr(str->s + from, substr);
      return pos ? pos - str->s : -1;
   } else return -1;
}

int cString::getPos(const char *substr, const char *delims, int from) const
{
   // 'delims' kann entweder 0 sein, oder ein String
   // mit einem oder mehreren der folgenden Zeichen:
   //
   //  ' = Strings in einfachem Anfuehrungszeichen werden ueberlesen
   //  " = Strings in doppelten Anfuehrungszeichen werden ueberlesen
   //  ( = Ausdruecke in runden Klammern werden ueberlesen
   //  { = Ausdruecke in geschweiften Klammern werden ueberlesen
   //  [ = Ausdruecke in eckigen Klammern werden ueberlesen

   if ( str == 0 || substr == 0 || from < 0 )
      return -1;
   if ( delims == 0 )
      delims = "";

   const char *p;
   int first_ch = *substr;
   int len = strlen(substr);

   for ( p = str->s + from ; *p ; p++ ) {
      if ( *p == first_ch && strncmp(p, substr, len) == 0 ) {
         return p - str->s;
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

   return -1;
}

int cString::getPosNoCase(const char *substr, int from) const
{
   return getPosNoCase(substr, 0, from);
}

int cString::getPosNoCase(const char *substr, const char *delims, int from) const
{
   // Bedeutung des 'delims'-Parameters siehe getPos(s,f)

   if ( str == 0 || substr == 0 || from < 0 )
      return -1;
   if ( delims == 0 )
      delims = "";

   const char *p;
   int first_ch = toupper(*substr);
   int len = strlen(substr);

   for ( p = str->s ; *p ; p++ ) {
      if ( toupper(*p) == first_ch && strnicmp(p, substr, len) == 0 ) {
         return p - str->s;
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

   return -1;
}

int cString::getLastPos(const char *substr, int from) const
{
   if (str && __ECL_ASSERT1__(from >= 0)) {
      if ( from > str->len ) from = str->len;
      const char *ptr = str->s + from; int pos = -1;
      while ( (ptr = strstr(ptr, substr)) != 0 ) pos = ptr++ - str->s;
      return pos;
   } else return -1;
}

cString cString::trimLeft(const char *set) const
{
   if (str) {
      if (set) {
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

cString cString::trimRight(const char *set) const
{
   if (str) {
      if (set) {
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

cString cString::trim(const char *set) const
{
   if (str) {
      if (set) {
         int i = 0;
         while ( strchr(set, str->s[i]) ) ++i;
         int j = str->len-1;
         while ( j >= i && strchr(set, str->s[j]) ) --j;
         return (i == 0) && (j = str->len-1) != 0 ? *this : cString(str->s+i, j-i+1);
      } else {
         int i = 0;
         while ( isspace(str->s[i]) ) ++i;
         int j = str->len-1;
         while ( j >= i && isspace(str->s[j]) ) --j;
         return (i == 0) && (j = str->len-1) != 0 ? *this : cString(str->s+i, j-i+1);
      }
   } else return *this;
}

cString cString::getUpcase() const
{
   if ( str && str->s ) {
      cString upper(str->s, str->len);
      strupr(upper.str->s);
      return upper;
   } else {
      return *this;
   }
}

cString cString::getLocase() const
{
   if ( str && str->s ) {
      cString lower(str->s, str->len);
      strlwr(lower.str->s);
      return lower;
   } else {
      return *this;
   }
}

cString cString::replace(const char *from, const char *to) const
{
   int pos,start=0;
   int lenfrom = strlen(from);
   int lento = strlen(to);

   cString neu(*this);
   while ((pos = neu.getPos(from,start)) >= 0) {
      neu = neu.getLeft(pos)+to+neu.getMid(pos+lenfrom);
      start = pos+lento;
   }
   return neu;
}

cString cString::replaceTab(int width, const char *by) const
{
   int pos,start=0;

   cString neu(*this);
   while ((pos = neu.getPos("\t",start)) >= 0) {
      int spc = ((int)(pos/width)+1)*width - pos;
      neu = neu.getLeft(pos)+cString(spc, by)+neu.getMid(pos+1);
      start = pos + spc;
   }
   return neu;
}

cString cString::replaceTab(int nullpos, int width, const char *by) const
{
   int pos;

   cString neu(*this);
   if ((pos = neu.getPos("\t")) >= 0) {
      int spc = ((int)((pos-nullpos)/width)+1)*width - (pos-nullpos);
      neu = neu.getLeft(pos)+cString(spc, by)+neu.getMid(pos+1);
   }
   return neu;
}


// ===========================================================================
// cstring = cStringf(fmt, ...)
// ---------------------------------------------------------------------------
//
// ===========================================================================

GLOBAL __ECL_EXP1__ cString __ECL_EXP2__ cStringf(const char *fmt, ...)
{
   /* kurze Testphase fuer die lock/unlockBuffer:
   cString buffer;

   va_list ap;
   va_start(ap, fmt);
   vsprintf(buffer.lockBuffer(1024), fmt, ap);
   buffer.unlockBuffer();
   va_end(ap);

   return buffer;
   //*/

   //*
   char buffer[1024];

   va_list ap;
   va_start(ap, fmt);
   vsprintf(buffer, fmt, ap);
   va_end(ap);

   return cString(buffer);
   //*/
}


// double-Konvertierungen und andere Auslauffunktionalitaeten
// ---------------------------------------------------------------------------

// Formatierungs-Informationen
static char def_decimal_sep  = ',';  // Separator fuer Dezimalstellen ("1,00")
static char def_thousand_sep = '.';  // Separator fuer Tausender-Stellen ("1.000")
static char def_date_sep     = ':';  // Datumstrenner (01.04.1999)
static char def_time_sep     = ':';  // Zeittrenner (13:00:00)
static int  def_date_format  = 0;    // Datumsformat (0=TT.MM.YYYY, 1=MM.DD.YYYY)

cString::cString(double d, int prec, char sep1, char sep2)
{
   alloc(40);
   convDbl2Str(str->s, d, prec, sep1, sep2);
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
      sprintf( buffer, "%ld%c%03ld%c%03d", vk/1000000L, thousand_sep, (vk/1000)%1000, thousand_sep, (int)(vk % 1000) );
   } else if ( thousand_sep && vk >= 1000) {
      sprintf( buffer, "%ld%c%03d", vk/1000, thousand_sep, (int)(vk % 1000) );
   } else {
      sprintf( buffer, "%ld", vk );
   }

   char *bp = buffer+strlen(buffer)-1;
   char save = *bp;
   if (prec > 0) {
      sprintf( bp, "%.*f", prec, val > vk ? val-vk : 0.0);
      *bp++ = save;
      *bp = decimal_sep;
   } else if ( prec < 0 && val > vk ) {
      sprintf( bp, "%g", val-vk );
      *bp++ = save;
      *bp = decimal_sep;
   }
}


