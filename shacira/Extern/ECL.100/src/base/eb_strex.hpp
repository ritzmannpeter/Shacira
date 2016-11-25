/*.SH.*/

/*
 *  Headerfile for module eb_strex
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  eb_strex.cpp on Saturday March 23 2002  08:39:14
 */

#ifndef __eb_strex__
#define __eb_strex__


// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"


// ===========================================================================
// Definition cStrFile
// ---------------------------------------------------------------------------
//
//    cBase
//     +--cString
//         +--cStrFile - Dateinamenbezogene Stringfunktionen
//
// ===========================================================================

class __ECL_DLLEXPORT__ cStrFile : public cString {
   // Erweiterungsideen:
   // - cString normalize() -> '/' zu '\' konvertieren. Sonst noch was?
   // - splitFileSpec(...) koennte auch mit '/' funktionieren ...

public:
   // Defaultkonstruktor "uninitialisiert"
   cStrFile() : cString() {}
   // Konstruktor ueber const char * und optional Stringlaenge
   cStrFile(const char *s, int l = -1) : cString(s, l) { }
   // Konstruktor ueber cString
   cStrFile(const cString &s) : cString(s) {}

   // cStrFile(const cStrFile &fn) -> Defaultimplementierung
   // cStrFile& operator=(const cStrFile& other) -> Defaultimplementierung

   // falls noetig: Backslash an Pfad haengen
   cString getDirName() const {
      return (getRight(1) == "\\") ? *this : *this + "\\";
   }

   // Dateibezeichnung in Pfad\, Dateiname und .Erweiterung zerlegen
   void splitFileSpec(cString &path, cString &name, cString &ext) const;

   // Pfad ermitteln
   cString getPath() const;
   // Dateiname ermitteln
   cString getName() const;
   // Dateiname & Erweiterung ermitteln
   cString getFullName() const;
   // Erweiterung ermitteln
   cString getExt() const;

   // Pfad ersetzen
   cString replacePath(const cString &path) const;
   // Dateiname ersetzen
   cString replaceName(const cString &name) const;
   // Erweiterung ersetzen
   cString replaceExt(const cString &ext) const;

   // Fehlenden Pfad durch Default ersetzen
   cString defaultPath(const cString &path) const;
   // Fehlende Erweiterung durch Default ersetzen
   cString defaultExt(const cString &ext) const;
   // Fehlenden Pfad/Erweiterung durch Default ersetzen
   cString defaultPathExt(const cString &path, const cString &ext) const;
   // Fehlenden Dateiname & Erweiterung durch Default ersetzen
   cString defaultFullName(const cString &full) const;

   // Umwandlung nach const char *
   //operator const char *() const
   //   { return str ? str->s : 0; }
   //friend __ECL_OPEXP__ cFileName& operator()(const cString& s)
   //   { return cFileName(); }

private:
   // Pfad rechts mit '\' ergaenzen (falls nicht angegeben)
   static cString makePath(cString path) {
      path = normalize(path);
      return (path.isEmpty() || path.getRight(1) == "\\") ? path : path+"\\";
   }
   // Erweiterung links mit '.' ergaenzen (falls nicht angegeben)
   static cString makeExt(const cString &ext) {
      return (ext.isEmpty() || ext.getLeft(1) == ".") ? ext : "."+ext;
   }
   // Normalisieren der Pfadseparatoren
   static cString normalize(const cString &filespec) {
      return filespec.replace("/","\\");
   }
};


// ===========================================================================
// Definition cStrEnv
// ---------------------------------------------------------------------------
//
//    cBase
//     +--cString
//         +--cStrEnv - Umgebungsvariablenbezogene Stringfunktionen
//
// ===========================================================================

class __ECL_DLLEXPORT__ cStrEnv : public cString {
public:
   // Defaultkonstruktor "uninitialisiert"
   cStrEnv() : cString() {}
   // Konstruktor ueber const char * und optional Stringlaenge
   cStrEnv(const char *s, int l = -1) : cString(s, l) { }
   // Konstruktor ueber cString
   cStrEnv(const cString &s) : cString(s) {}

   // cStrEnv(const cStrEnv &fn) -> Defaultimplementierung
   // cStrEnv& operator=(const cStrEnv& other) -> Defaultimplementierung

   // Wert setzen, ggf. loeschen
   void set(const cString &value=0);
   // Wert ermitteln (oder 0 falls undefiniert)
   cString get();

   // Wert "<var>=<val>" zuweisen
   void assign();
   // (definierte) Umgebungsvariablen "%<env>%" ersetzen
   cString replace();
};


#endif

/*.EH.*/
