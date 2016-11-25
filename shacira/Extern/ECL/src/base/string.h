// ===========================================================================
// base/string.h                                                ______ /  ECL
// Autoren: Udo Pfrengle, Markus Wuertz, Thomas Epting         /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cString - dynamische Stringverwaltung.
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

#ifndef __ecl_string__
#define __ecl_string__


// Standard headers
#include <cwchar>
#include <cstring>
#include <iostream>

// Other ECL headers
#include "base/base.h"


// Utility Functions
// ===========================================================================

inline size_t strxlen(const char *str)
   { return str ? strlen(str) : 0; }
inline size_t strxlen(const wchar_t *str)
   { return str ? wcslen(str) : 0; }

inline char * strxcpy(char *s1, const char *s2, size_t len)
   { strncpy(s1, s2, len); s1[len-1] = '\0'; return s1; }
inline wchar_t * strxcpy(wchar_t *s1, const wchar_t *s2, size_t len)
   { wcsncpy(s1, s2, len); s1[len-1] = '\0'; return s1; }


namespace ecl {


// ===========================================================================
// Definition cString
// ---------------------------------------------------------------------------
//
//! Verwaltet dynamische String-Objekte.
//! @ingroup string
//!
//! Diese Klasse ist mit Unicode-Strings kompatibel, kann sie aber (noch)
//! nicht verwalten. Statt dessen werden Unicode-Strings intern stets in
//! ANSI-Strings umgewandelt.
//
// cString
//
// ===========================================================================

class cString;
__ECL_EXP1__ cString __ECL_EXP2__ cStringf(const char *fmt, ...);

class __ECL_DLLEXPORT__ cString {
   friend __ECL_EXP1__ cString __ECL_EXP2__ cStringf(const char *fmt, ...);

private:
   // Verwaltungseinheit fuer einen String
   struct xstr {
      int len;      // aktuelle Laenge
      int size;     // allokierte Groesse
      int refc;     // Referenzzaehler
      wchar_t *ws;  // Unicode-String
      char s[1];    // Ansi-String (Groesse dynamisch)
   } *str;

// ------------------------------------
// Construction/Destruction/Copying
// ------------------------------------
public:

   //! Defaultkonstruktor "uninitialisiert"
   cString()
      { str=0; }
   //! Konstruktor ueber Stringlaenge
   cString(int l)
      { if (l>0) alloc(l); else str=0; }
   //! Konstruktor ueber const char * und optional Stringlaenge (ANSI)
   cString(const char *s, int l = -1)
      { if (s) init(s, l<0 ? strlen(s) : l); else str=0; }
   //! Konstruktor ueber const wchar_t * und optional Stringlaenge (Unicode)
   cString(const wchar_t *ws, int l = -1)
      { if (ws) init(ws, l<0 ? strxlen(ws) : l); else str=0; }
   //! Konstruktor ueber anderen cString
   cString(const cString& other)
      { str = other.str; if ( str ) ++str->refc; }

   //! Konstruktor ueber formatierte double-Zahl
   cString(double d, int prec, char decimal_sep = '\0', char thousand_sep = '\0');
   private:
      //! Der Konstruktor ueber sich wiederholende Zeichenfolgen kann duch einen
      //! "externen" Benutzer leicht falsch verstanden werden. Intern wird er aber
      //! an verschiedenen Stellen benoetigt, deswegen ist er private um zu sehen,
      //! ob er ueberhaupt "von aussen" benutzt wird ...
      cString(int n, const cString& s);
   public:

   //! Destruktor
   ~cString()
      { dealloc(str); }


// ------------------------------------
// String functions
// ------------------------------------
public:

   //! Freigeben der Resourcen
   void clear()
      { dealloc(str); }

   //! Ist der String uninitialisiert?
   inline bool isNull() const
      { return !str; }
   //! Enthaelt der String keine Zeichen?
   inline bool isEmpty() const
      { return !str || !str->len; }
   //! Ermittle die aktuelle Zeichenzahl im String
   inline int getLength() const
      { return str ? str->len : 0; }
   //! Ermittle die aktuelle Puffergroesse des Strings
   inline int getSize() const
      { return str ? str->size : 0; }

   // Stringpuffer mit size Bytes fuer direkten Zugriff anfordern, bis zum
   // unlockBuffer darf der cString *NUR* ueber den Puffer benutzt werden!
   char *lockBuffer(int size);
   // String nach direktem Zugriff wieder validieren
   void unlockBuffer();

   //! @name Konkatenation und Zuweisung
   //@{
   //! Zuweisung: const char *
   cString& operator=(const char *other)
      { return assign(other, strxlen(other)); }
   //! Zuweisung: const wchar_t *
   cString& operator=(const wchar_t *other)
      { return assign(other, strxlen(other)); }
   //! Zuweisung: cString
   cString& operator=(const cString& other);

   // TBD: Wenn die Operatoren += neuen Speicher allokieren muessen, dann wird
   // exakt soviel belegt, wie der neue String benoetigt. Ab dann fuehrt JEDES
   // += zu Neuallokation&Copy. Verbesserungen: 1) mit strMinSize() auf Vorrat
   // Platz belegen. 2) da sowieso malloc&free (statt new&delete) verwendet
   // werden, warum nicht realloc einsetzen? TIEFGREIFENDE AENDERUNG !!!

   //! Konkatenation und Zuweisung (cString += cString)
   cString& operator+=(const cString& other)
      { return other.str ? concat( other.str->s, other.str->len) : *this; }
   //! Konkatenation und Zuweisung (cString << cString)
   //! \deprecated Der << Operator wird nicht laenger unterstuetzt, += benutzen!
   cString& operator<<(const cString& other);
   //! Konkatenation und Zuweisung (cString += const char *)
   cString& operator+=(const char * other)
      { return concat( other, strxlen(other) ); }
   //! Konkatenation und Zuweisung (cString += const wchar_t *)
   cString& operator+=(const wchar_t * other)
      { return concat( other, strxlen(other) ); }
   //! Konkatenation und Zuweisung (cString << const char *)
   //! \deprecated Der << Operator wird nicht laenger unterstuetzt, += benutzen!
   cString& operator<<(const char * other);
   //! Konkatenation und Zuweisung (cString += char)
   cString& operator+=(char ch)
      { return *this+=cStringf("%c", ch); }
   //! Konkatenation und Zuweisung (cString += double)
   cString& operator+=(double f)
      { return *this+=cStringf("%g", f); }
   //! Konkatenation und Zuweisung (cString << double)
   //! \deprecated Der << Operator wird nicht laenger unterstuetzt, += benutzen!
   cString& operator<<(double f);
   //@}

   //! @name Konkatenation
   //@{
   //! Konkatenation (ccp mit cString)
   friend __ECL_OPEXP__ cString  operator+(const char *s1, const cString& s2);
   //! Konkatenation (cString mit cpp)
   friend __ECL_OPEXP__ cString  operator+(const cString& s1, const char *s2);
   //! Konkatenation (wccp mit cString)
   friend __ECL_OPEXP__ cString  operator+(const wchar_t *s1, const cString& s2);
   //! Konkatenation (cString mit cpp)
   friend __ECL_OPEXP__ cString  operator+(const cString& s1, const wchar_t *s2);
   //! Konkatenation (cString mit cString)
   friend __ECL_OPEXP__ cString  operator+(const cString& s1, const cString& s2);
   
   // The following declarations will cause warnings with __ECL_GNUC__.
   // Seems to be an obsolete workaround need for an older (and in the
   // meantime unsupported) compiler (OS/2? VC5?).
   //
   // Konkatenation (string literal mit cString)
   // friend __ECL_OPEXP__ cString  operator+(const char s1[], const cString& s2);
   // Konkatenation (cString mit string literal)
   // friend __ECL_OPEXP__ cString  operator+(const cString& s1, const char s2[]);
   // Konkatenation (string literal mit cString)
   // friend __ECL_OPEXP__ cString  operator+(const wchar_t s1[], const cString& s2);
   // Konkatenation (cString mit string literal)
   // friend __ECL_OPEXP__ cString  operator+(const cString& s1, const wchar_t s2[]);
   
   //@}

   //! @name Vergleichsoperationen
   //@{
   //! Vergleiche zwei Strings (beachte Gross-/Kleinschreibung). Mit @a max_chars
   //! kann der Vergleich auf die ersten Zeichen beschränkt werden (-1 vergleicht
   //! bis zum Stringende). Der Funktionwert ist
   //! - < 0 falls *this < @a other
   //! - = 0 falls *this == @a other
   //! - > 0 falls *this > @a other
   //! 
   int compare(const cString& other, int max_chars = -1) const;
   //! Vergleiche cString mit const char * (beachte Gross-/Kleinschreibung)
   int compare(const char *other, int max_chars = -1) const;
   //! Vergleiche cString mit const char * (beachte Gross-/Kleinschreibung)
   int compare(const wchar_t *other, int max_chars = -1) const;
   //! Vergleiche zwei Strings (ignoriere Gross-/Kleinschreibung)
   int compareNoCase(const cString& other, int max_chars = -1) const;
   //! Vergleiche cString mit const char * (ignoriere Gross-/Kleinschreibung)
   int compareNoCase(const char *other, int max_chars = -1) const;
   //! Vergleiche cString mit const wchar_t * (ignoriere Gross-/Kleinschreibung)
   int compareNoCase(const wchar_t *other, int max_chars = -1) const;

   //! Vergleichsoperatoren auf cString
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

   //! Vergleichsoperatoren auf const char *
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

   //! Vergleichsoperatoren auf const wchar_t *
   bool operator==(const wchar_t *other) const
      { return compare(other) == 0; }
   bool operator!=(const wchar_t *other) const
      { return compare(other) != 0; }
   bool operator<(const wchar_t *other) const
      { return compare(other) <  0; }
   bool operator>(const wchar_t *other) const
      { return compare(other) >  0; }
   bool operator<=(const wchar_t *other) const
      { return compare(other) <= 0; }
   bool operator>=(const wchar_t *other) const
      { return compare(other) >= 0; }
   //@}

   // TEST/TBD: Operatoren mit const char * auf der linken Seite?
   // friend __ECL_OPEXP__ bool operator==(const char *s1, const cString& s2);

   /// @name Umwandlungsoperationen
   //@{
   //! Cast-Umwandlung nach const char *
   operator const char *() const
      { return str ? str->s : 0; }
   //! Umwandlung nach const char *
   const char *ccp() const
      { return str ? str->s : 0; }
   //! Cast-Umwandlung nach const wchar_t *
   operator const wchar_t *() const;
   //! Cast-Umwandlung nach const wchar_t *
   const wchar_t *wccp() const;
   //! Umwandlung nach long (durch Interpretation)
   long getLong() const;
   //! Umwandlung nach double (durch Interpretation)
   double getDouble() const;
   //@}

   //! Generieren eines Hash-Codes aus dem String
   unsigned int generateHash() const;

   //! Zeichen extrahieren (const Variante, nur lesen)
   char operator[](int i) const;
   //! Zeichen extrahieren (by Reference Variante, aendern moeglich)
   char &operator[](int i);

   //! Teilstring von links her extrahieren
   cString getLeft(int len) const;
   //! Teilstring von rechts her extrahieren
   cString getRight(int len) const;
   //! Teilstring der Laenge len ab Startposition extrahieren
   cString getMid(int from, int len = -1) const;
   //! Teilstring von Startposition bis Zielposition extrahieren
   cString getSubstr(int from, int to) const
      { return to < from ? cString() : getMid(from, to - from + 1); }

   //! Liefert den 'n'-ten Teilstring in einem durch 'sep' separierten String
   cString getPart(int n, const cString& sep = ",") const;
   //! Liefert den 'n'-ten Teilstring (wie getPart(n,sep), jedoch Klammern und Anfuehrungszeichen parsen)
   cString getPart(int n, const cString& delims, const cString& sep) const;
   //! Liefert alles ab dem 'n'-ten Teilstring in einem durch 'sep' separierten String
   cString getTail(int n, const cString& sep = ",") const;
   //! Liefert alles ab dem 'n'-ten Teilstring (wie getPart(n,s), jedoch Klammern und Anfuehrungszeichen parsen)
   cString getTail(int n, const cString& delims, const cString& sep) const;

   //! Teilstring suchen.
   int getPos(const cString& substr, int from = 0) const;
   //! Teilstring suchen, Klammern und Anfuehrungszeichen parsen.
   int getPos(const cString& substr, const cString& delims, int from = 0) const;
   //! Teilstring suchen, Gross-/Kleinschreibung ignorieren.
   int getPosNoCase(const cString& substr, int from = 0) const;
   //! Teilstring suchen, Klammern und Anfuehrungszeichen parsen, Gross-/Kleinschreibung ignorieren.
   int getPosNoCase(const cString& substr, const cString& delims, int from = 0) const;
   //! Letztes Auftauchen von Teilstring suchen (liefert -1 falls nicht gefunden)
   int getLastPos(const cString& substr, int from = 0) const;

   //! Liefert true, wenn der String mit \a substr beginnt
   bool startsWith(const cString& substr) const
      { return getLeft(substr.getLength()).compare(substr) == 0; }
   //! Liefert true, wenn der String mit \a substr beginnt, Gross-/Kleinschreibung ignorieren
   bool startsWithNoCase(const cString& substr) const
      { return getLeft(substr.getLength()).compareNoCase(substr) == 0; }
   //! Liefert true, wenn der String mit \a substr endet
   bool endsWith(const cString& substr) const
      { return getRight(substr.getLength()).compare(substr) == 0; }
   //! Liefert true, wenn der String mit \a substr endet, Gross-/Kleinschreibung ignorieren
   bool endsWithNoCase(const cString& substr) const
      { return getRight(substr.getLength()).compareNoCase(substr) == 0; }
   //! Liefert true, wenn der String \a substr enthaelt
   bool contains(const cString& substr) const
      { return getPos(substr) >= 0; }
   //! Liefert true, wenn der String \a substr enthaelt, Klammern und Anfuehrungszeichen parsen
   bool contains(const cString& substr, const cString& delims) const
      { return getPos(substr, delims) >= 0; }
   //! Liefert true, wenn der String \a substr enthaelt, Gross-/Kleinschreibung ignorieren
   bool containsNoCase(const cString& substr) const
      { return getPosNoCase(substr) >= 0; }
   //! Liefert true, wenn der String \a substr enthaelt, Klammern und Anfuehrungszeichen parsen, Gross-/Kleinschreibung ignorieren
   bool containsNoCase(const cString& substr, const cString& delims) const
      { return getPosNoCase(substr, delims) >= 0; }

   //! Leerzeichen bzw. Zeichen aus set links entfernen
   cString trimLeft(const cString& set = 0) const;
   //! Leerzeichen bzw. Zeichen aus set rechts entfernen
   cString trimRight(const cString& set = 0) const;
   //! Leerzeichen bzw. Zeichen aus set links und rechts entfernen
   cString trim(const cString& set = 0) const;

   //! Rechts mit fill auffuellen bis die Feldbreite width erreicht ist.
   cString padRight(int width, const cString &fill = " ");
   //! Links mit fill auffuellen bis die Feldbreite width erreicht ist.
   cString padLeft(int width, const cString &fill = " ");

   //! String in GROSSBUCHSTABEN umwandeln
   cString getUpcase() const;
   //! String in kleinbuchstaben umwandeln
   cString getLocase() const;

   //! Teilstring der Laenge len ab Startposition loeschen
   cString del(int from, int len) const;
   //! Teilstring der Laenge len von links her loeschen
   cString delLeft(int len) const;
   //! Teilstring der Laenge len von rechts her loeschen
   cString delRight(int len) const;

   //! Teilketten ersetzen
   cString replace(const cString& from, const cString& to) const;
   //! Teilstring ersetzen, bei der Suche Gross-/Kleinschreibung ignorieren.
   cString replaceNoCase(const cString &from, const cString &to) const;
   //! Alle Tabulatoren \\t ersetzen
   cString replaceTab(int width=8, const cString& by=" ") const;
   //! Einzelnen Tabulator \\t ersetzen
   cString replaceTab(int nullpos, int width, const cString& by=" ") const;
   //! Escapesequenzen ersetzen
   cString replaceEsc() const;
   //! Teilkette an bestimmter Position ersetzen
   cString replace(int from, int len, const cString& by) const;
   //! String an bestimmter Position einfuegen (Teilstring mit len=0 ersetzen)
   cString insert(int pos, const cString& str) const;

   //! String in Quoted-Printable kodieren
   cString encodeQuotedPrintable(int width=76, bool encode_all = false) const;
   //! Quoted-Printable in String dekodieren
   cString decodeQuotedPrintable() const;

   //! Argumente der Form "%<digit>" ersetzen
   cString arg(const cString& to) const;
   //! Dito, aber mit integer Zahl
   cString arg(int n) const
      { return arg(cStringf("%d",n)); }
   //! Dito, aber mit doubler Zahl
   cString arg(double d) const
      { return arg(cStringf("%g",d)); }
   //! Dito, aber mit formatierter double Zahl
   cString arg(double d, int prec, char decimal_sep = '\0', char thousand_sep = '\0') const
      { return arg(cString(d,prec,decimal_sep,thousand_sep)); }

   // TBD: als Ersatz für cStringf(const char *fmt, ...); (dynamisch ohne Zwischenpuffer)
   cString &sprintf(const char *fmt, ...);
   cString &vsprintf(const char *fmt, va_list argptr);
   
   //! write string to ostream @a os
   friend __ECL_OPEXP__ std::ostream& operator<<(std::ostream& os, const cString& s)
      { return os << (s.str ? s.str->s : "(NULL)"); }
   //! read string (word or line) from istream @a is
   friend __ECL_OPEXP__ std::istream& operator>>(std::istream& is, cString& s);
   //! read line from istream @a is
   cString &getLine(std::istream &is);

   //! Formatierte Zahl in double wandeln
   static bool convStr2Dbl(const char *buffer, double& result, char decimal_sep = '\0', char thousand_sep = '\0');
   //! double in formatierte Zahl wandeln
   static void convDbl2Str(char *buffer, double val, int prec, char decimal_sep = '\0', char thousand_sep = '\0');
   
   // Utility Functions
   // Einige praktische, compilerspezifische Funktionen die z.B. vom
   // Visual-C bereitgestellt werden aber NICHT zum Standard gehoeren
   // werden bei Bedarf (z.B. fuer GnuC) kompatibel nachimplementiert.
   #ifndef __ECL_VCPP__
      static int _stricmp(const char *str1, const char *str2);
      static int _strnicmp(const char *str1, const char *str2, size_t count);
      static char *_strlwr(char *str);
      static char *_strupr(char *str);
   #else
      static inline int _stricmp(const char *str1, const char *str2) {
         return ::_stricmp(str1, str2); }
      static inline int _strnicmp(const char *str1, const char *str2, size_t count) {
         return ::_strnicmp(str1, str2, count); }
      static inline char *_strlwr(char *str) {
         return ::_strlwr(str); }
      static inline char *_strupr(char *str) {
         return ::_strupr(str); }
   #endif
   

// ------------------------------------
// Helper functions
// ------------------------------------
protected:

   void alloc(size_t l);
   void dealloc(xstr *&str);

   // Referenzzaehler fuer Komponententest durch Ableitung transparent machen
   int getRefc() const { return str ? str->refc : 0; }

   // "Sicherer" const char *, der bei isNull() NICHT 0 wird
   const char *safeCcp() const { return str ? str->s : ""; }

   // Allokiere Platz fuer 'len' Bytes und initialisiere mit Zeichenkette s
   void init(const char *s, size_t len);
   void init(const wchar_t *s, size_t len);

   cString& concat(const char *second, size_t slen);
   cString& concat(const wchar_t *second, size_t slen);

   cString& assign(const char *s, size_t slen);
   cString& assign(const wchar_t *s, size_t slen);

   // minimale Stringlaenge
   static void setMinStrSize(int m);

   static void initFormatOptions();
};

//! @relates cString
//! EclHashKey fuer cString ermitteln
inline unsigned int EclHashKey(cString key)
   { return key.generateHash(); }

//! @relates cString
//! Typumwandlung char -> cString
inline cString Str(char ch)
   { return cStringf("%c", ch); }

//! @relates cString
//! Typumwandlung int -> cString
inline cString Str(int n)
   { return cStringf("%d", n); }

//! @relates cString
//! Typumwandlung double -> cString
inline cString Str(double f)
   { return cStringf("%g", f); }

__ECL_OPEXP__ cString   operator+(const char *s1, const cString& s2);
//__ECL_OPEXP__ cString   operator+(const char s1[], const cString& s2);
__ECL_OPEXP__ cString   operator+(const cString& s1, const char *s2);
//__ECL_OPEXP__ cString   operator+(const cString& s1, const char s2[]);
__ECL_OPEXP__ cString   operator+(const cString& s1, const cString& s2);

__ECL_OPEXP__ std::ostream&  operator<<(std::ostream& os, const cString& s);

__ECL_EXP1__ cString __ECL_EXP2__ cStringf( const char *fmt, ...);

// TEST/TBD: Operatoren mit const char * auf der linken Seite?
// __ECL_OPEXP__ bool operator==(const char *s1, const cString& s2) { return s2 == s1; }


}; // namespace ecl


#endif // __ecl_string__

