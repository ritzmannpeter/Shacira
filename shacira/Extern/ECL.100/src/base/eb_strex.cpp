// ===========================================================================
// eb_strex.cpp                                                 ______ /  ECL
// Autor. Markus Wuertz                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +--cString
//         |
//         +--cStrFile    - Dateinamenbezogene Stringfunktionen
//         |
//         +--cStrEnv     - Umgebungsvariablenbezogene Stringfunktionen
//
// ToDo:
// - cStrDir - Verzeichnisnamebezogene Funktionen
//   -- Aufloesung von . und .. Automatisch oder explizit?
//   -- getTail(), getBase(), getPart(n)
//   -- Trennzeichen mit char *set="/\\" konfigurierbar, set[0] ist default.
// - cStrEnv - get & put, assign("a=b")
// ===========================================================================

#include "base/eb_strex.hpp"




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_str.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/




// ---------------------------------------------------------------------------
// Implementierung cStrFile
// ---------------------------------------------------------------------------

void cStrFile::splitFileSpec(cString &path, cString &name, cString &ext) const
{
   cString norm = normalize(*this);

   int slash = norm.getLastPos("\\");
   int dot = norm.getLastPos(".", slash+1);

   if (slash >= 0) {
      path = norm.getLeft(slash+1);
   } else {
      path = cString();
   }

   if (dot >= 0) {
      name = norm.getSubstr(slash+1,dot-1);
      ext = norm.getMid(dot);
   } else {
      name = norm.getMid(slash+1);
      ext = cString();
   }
}

cString cStrFile::getPath() const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   return path;
}

cString cStrFile::getName() const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   return name;
}

cString cStrFile::getFullName() const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   return name+ext;
}

cString cStrFile::getExt() const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   return ext;
}

cString cStrFile::replacePath(const cString &path) const
{
   cString trash, name, ext;
   splitFileSpec(trash, name, ext);
   return makePath(path)+name+ext;
}

cString cStrFile::replaceName(const cString &name) const
{
   cString path, trash, ext;
   splitFileSpec(path, trash, ext);
   return path+name+ext;
}

cString cStrFile::replaceExt(const cString &ext) const
{
   cString path, name, trash;
   splitFileSpec(path, name, trash);
   return path+name+makeExt(ext);
}

cString cStrFile::defaultPath(const cString &defpath) const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   if (path.isEmpty()) path = makePath(defpath);
   return path+name+ext;
}

cString cStrFile::defaultExt(const cString &defext) const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   if (ext.isEmpty()) ext = makeExt(defext);
   return path+name+ext;
}

cString cStrFile::defaultPathExt(const cString &defpath, const cString &defext) const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   if (path.isEmpty()) path = makePath(defpath);
   if (ext.isEmpty()) ext = makeExt(defext);
   return path+name+ext;
}

cString cStrFile::defaultFullName(const cString &fullname) const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   if (name.isEmpty() && ext.isEmpty()) {
      return path+fullname;
   } else {
      return *this;
   }
}




#ifdef __INTERFACE__

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

#endif /*__INTERFACE__*/




// ---------------------------------------------------------------------------
// Implementierung cStrEnv
// ---------------------------------------------------------------------------

void cStrEnv::set(const cString &value) {
   if (isEmpty()) {
      return;
   } else if (value.isEmpty()) {
      putenv(*this+"=");
   } else {
      putenv(*this+"="+value);
   }
}

void cStrEnv::assign() 
{
   if (isEmpty()) {
      return;
   } else {
      putenv(*this);
   }
}

cString cStrEnv::get()
{
   return getenv(*this);
}

cString cStrEnv::replace()
{
   int startenv,endenv,start = 0;

   cString neu(*this);
   while ((startenv = neu.getPos("%",start)) >= 0 &&
          (endenv = neu.getPos("%",startenv+1)) >= 0) {
      const char *env = getenv(neu.getSubstr(startenv+1,endenv-1));
      if (env != 0) {
         neu = neu.getLeft(startenv)+cString(env)+neu.getMid(endenv+1);
         start = startenv + strlen(env);
      } else {
         start = endenv+1;
      }
   }
   return neu;
}
