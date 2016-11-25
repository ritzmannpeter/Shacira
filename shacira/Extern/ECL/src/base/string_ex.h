// ===========================================================================
// base/string_ex.h                                             ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cString
//     |
//     +--cStrFile    - Dateinamenbezogene Stringfunktionen
//     |
//     +--cStrEnv     - Umgebungsvariablenbezogene Stringfunktionen
//
// ===========================================================================

#ifndef __ecl_string_ex__
#define __ecl_string_ex__


// Other ECL headers
#include "base/string.h"

      
namespace ecl {


// ===========================================================================
// Definition cStrFile
// ---------------------------------------------------------------------------
//
//! Dateinamenbezogene Stringfunktionen
//! @ingroup string
//
//  cString
//   +--cStrFile
//
// ===========================================================================

class __ECL_DLLEXPORT__ cStrFile : public cString {

public:
   //! Defaultkonstruktor "uninitialisiert"
   cStrFile() : cString() {}
   //! Konstruktor ueber const char * und optional Stringlaenge
   cStrFile(const char *s, int l = -1) : cString(s, l) { normthis(); }
   //! Konstruktor ueber cString
   cStrFile(const cString &s) : cString(s) { normthis(); }

   // cStrFile(const cStrFile &fn) -> Defaultimplementierung
   // cStrFile& operator=(const cStrFile& other) -> Defaultimplementierung


   // Verzeichnisnamen-Funktionen
   // ===========================
   // Voraussetzung: Das cStrFile-Objekt enthaelt einen Verzeichnisnamen

   //! Verzeichnisnamen ermitteln (incl_trail_sep == true: falls noetig, Backslash anhaengen)
   cStrFile getDirName(bool incl_trail_sep = true) const;
   //! Namen des Parent-Verzeichnisses ermitteln (incl_trail_sep wie bei getDirName)
   cStrFile getParentDirName(bool incl_trail_sep = true) const;


   // Dateinamen-Funktionen
   // =====================
   // Voraussetzung: Das cStrFile-Objekt enthaelt einen Dateinamen

   //! Dateibezeichnung in Pfad\, Dateiname und .Erweiterung zerlegen
   void splitFileSpec(cString &path, cString &name, cString &ext) const;

   //! Pfad ermitteln
   cString getPath() const;
   //! Pfad ohne Laufwerksangabe ermitteln
   //cString getPathOnly() const;
   //! Dateiname ermitteln
   cString getName() const;
   //! Dateiname & Erweiterung ermitteln
   cString getFullName() const;
   //! Erweiterung ermitteln
   cString getExt() const;

   //! Pfad ersetzen
   cString replacePath(const cString &path) const;
   //! Dateiname ersetzen
   cString replaceName(const cString &name) const;
   //! Erweiterung ersetzen
   cString replaceExt(const cString &ext) const;

   //! Fehlenden Pfad durch Default ersetzen
   cString defaultPath(const cString &path) const;
   //! Fehlende Erweiterung durch Default ersetzen
   cString defaultExt(const cString &ext) const;
   //! Fehlenden Pfad/Erweiterung durch Default ersetzen
   //cString defaultPathExt(const cString &path, const cString &ext) const;
   //! Fehlenden Dateiname & Erweiterung durch Default ersetzen
   cString defaultFullName(const cString &full) const;

   //! Vergleich gegen Wildcard mit '*' und '?', true wenn wildcard passt
   bool matchWildcard(const cString &wildcard) const;
   //! Vergleich gegen Wildcard mit '*' und '?', =0 gleich, <0 kleiner, >0 groesser
   int compareWildcard(const cString &wildcard) const;

   // Umwandlung nach const char *
   //operator const char *() const
   //   { return str ? str->s : 0; }
   //friend __ECL_OPEXP__ cFileName& operator()(const cString& s)
   //   { return cFileName(); }

private:
   //! Pfad rechts mit '\' ergaenzen (falls nicht angegeben)
   static cString makePath(cString path) {
      path = normalize(path);
      return (path.isEmpty() || path.getRight(1) == "\\") ? path : path+"\\";
   }
   //! Erweiterung links mit '.' ergaenzen (falls nicht angegeben)
   static cString makeExt(const cString &ext) {
      return (ext.isEmpty() || ext.getLeft(1) == ".") ? ext : "."+ext;
   }
   //! Normalisieren der Pfadseparatoren
   static cString normalize(const cString &filespec) {
      return filespec.replace("/","\\");
   }
   //! Normalisieren der Pfadseparatoren im Konstruktor
   void normthis() {
      char *p = (char*)ccp();
      while (p && *p) { if (*p == '/') *p = '\\'; p++; }
   }
};


// ===========================================================================
// Definition cStrEnv
// ---------------------------------------------------------------------------
//
//! Umgebungsvariablenbezogene Stringfunktionen
//! @ingroup string
//
//  cString
//   +--cStrEnv
//
// ===========================================================================

class __ECL_DLLEXPORT__ cStrEnv : public cString {
public:
   //! Defaultkonstruktor "uninitialisiert"
   cStrEnv() : cString() {}
   //! Konstruktor ueber const char * und optional Stringlaenge
   cStrEnv(const char *s, int l = -1) : cString(s, l) { }
   //! Konstruktor ueber cString
   cStrEnv(const cString &s) : cString(s) {}

   // cStrEnv(const cStrEnv &fn) -> Defaultimplementierung
   // cStrEnv& operator=(const cStrEnv& other) -> Defaultimplementierung

   //! Wert setzen, ggf. loeschen
   void set(const cString &value=0);
   //! Wert ermitteln (oder 0 falls undefiniert)
   cString get();

   //! Wert "<var>=<val>" zuweisen
   void assign();

   //! (definierte) Umgebungsvariablen "%<env>%" ersetzen
   cString replace();
   //! (definierte) Umgebungsvariablen "%<env>%" ersetzen
   static cString replace(const cString &str) { return cStrEnv(str).replace(); }
};


}; // namespace ecl


#endif // __ecl_string_ex__

