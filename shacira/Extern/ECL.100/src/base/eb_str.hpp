// ---------------------------------------------------------------------------
//
//  Headerfile for cpp module eb_str
//
//  Generated by C-Head Version 1.4
//  (c) 1993-2002 by 2i Industrial Informatics GmbH
//
//  This file has been extracted from the source file
//  eb_str.cpp on Monday April 08 2002  19:25:04
//
// ---------------------------------------------------------------------------

#ifndef __eb_str__
#define __eb_str__


// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"

int inline strxlen(const char *str)
   { return str ? strlen(str) : 0; }


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

__ECL_EXP1__ cString __ECL_EXP2__ cStringf( const char *fmt, ...);

#endif

