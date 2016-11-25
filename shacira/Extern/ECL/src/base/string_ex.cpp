// ===========================================================================
// base/string_ex.cpp                                           ______ /  ECL
// Autor: Markus Wuertz                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Aenderungen/Erweiterungen in cStrFile von -TE-:
// - Dateinamen werden bereits beim Konstruieren "normalisiert"
// - getDirName: Wahlweise das anhaengige Backslash anfuegen oder entfernen
// - getParentDirName: Name des Parent-Verzeichnisses ermitteln
//
// ===========================================================================


// Interface header
#include "base/string_ex.h"

// Standard headers
#include <cctype>
#include <cstdlib>




namespace ecl {




// ---------------------------------------------------------------------------
// Implementierung cStrFile
// ---------------------------------------------------------------------------

//! @class cStrFile
//! @todo class cStrDir - Verzeichnisnamen spezifische Funktionen
//! - Aufloesung von . und .. Automatisch oder explizit?
//! - getTail(), getBase(), getPart(n)
//! - Trennzeichen mit char *set="/\\" konfigurierbar, set[0] ist default.

cStrFile cStrFile::getDirName(bool incl_trail_sep) const
{
   if ( incl_trail_sep ) {
      // GnuC meckert bei der folgenden Zeile, darum ein Workaround:
      // return getRight(1) == "\\" ? *this : *this + "\\";
      if (getRight(1) == "\\") {
         return *this;
      } else {
         return *this + "\\";
      }
   } else {
      // GnuC meckert bei der folgenden Zeile, darum ein Workaround:
      // return getRight(1) == "\\" ? delRight(1) : *this;
      if (getRight(1) == "\\") {
         return delRight(1);
      } else {
         return *this;
      }
   }
}

cStrFile cStrFile::getParentDirName(bool incl_trail_sep) const
{
   if ( getRight(1) == "\\" ) {
      return cStrFile(delRight(1)).getParentDirName(incl_trail_sep);
   } else {
      int pos = getLastPos("\\");
      if ( pos >= 0 )
         return cStrFile(getLeft(pos)).getDirName(incl_trail_sep);
   }

   return cString();
}

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
      name = (slash+1 == dot) ? cString() : norm.getSubstr(slash+1,dot-1);
      ext = norm.getMid(dot);
   } else {
      name = (slash+1 == getLength()) ? cString() : norm.getMid(slash+1);
      ext = cString();
   }
}

cString cStrFile::getPath() const
{
   cString path, name, ext;
   splitFileSpec(path, name, ext);
   return path;
}

//cString cStrFile::getDrive() const
//{
//   if (getLength() >= 2 && isalpha(*this[0]) && *this[1] == ':') {
//      return getLeft(2)+"\\";
//   } else {
//      return cString();
//   }
//}

//cString cStrFile::getPathOnly() const
//{
//   cString path, name, ext;
//   splitFileSpec(path, name, ext);
//   if (path.getLength() >= 3 && isalpha(path[0]) && path[1]==':' && path[2]=='\\') {
//      return path.getMid(3);
//   } else {
//      return path;
//   }
//}

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

//cString cStrFile::defaultPathExt(const cString &defpath, const cString &defext) const
//{
//   cString path, name, ext;
//   splitFileSpec(path, name, ext);
//   if (path.isEmpty()) path = makePath(defpath);
//   if (ext.isEmpty()) ext = makeExt(defext);
//   return path+name+ext;
//}

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

// Lightweight and simple pattern matching function.
// Source: http://www.codeproject.com/
// Author: Jack Handy
//
// int wildcmp(char *wild, char *string)
// {
//    char *cp, *mp;
//
//    while ((*string) && (*wild != '*')) {
//       if ((*wild != *string) && (*wild != '?')) {
//          return 0;
//       }
//       wild++;
//       string++;
//    }
//
//    while (*string) {
//       if (*wild == '*') {
//          if (!*++wild) {
//             return 1;
//          }
//          mp = wild;
//          cp = string+1;
//       } else if ((*wild == *string) || (*wild == '?')) {
//          wild++;
//          string++;
//       } else {
//          wild = mp;
//          string = cp++;
//       }
//    }
//
//    while (*wild == '*') {
//       wild++;
//    }
//
//    return !*wild;
// }

/*
bool cStrFile::matchWildcard(const cString &wildcard)
{
   const char *string = ccp();
   const char *wild = wildcard.ccp();

   const char *cp=0, *mp=0;

   while ((*string) && (*wild != '*')) {
      if ((*wild != *string) && (*wild != '?')) {
         return false;
      }
      wild++;
      string++;
   }

   while (*string) {
      if (*wild == '*') {
         if (!*++wild) {
            return true;
         }
         mp = wild;
         cp = string+1;
      } else if ((*wild == *string) || (*wild == '?')) {
         wild++;
         string++;
      } else {
         wild = mp;
         string = cp++;
      }
   }

   while (*wild == '*') {
      wild++;
   }

   return !*wild;
}
*/

bool cStrFile::matchWildcard(const cString &wildcard) const
{
   return compareWildcard(wildcard) == 0;
}

int cStrFile::compareWildcard(const cString &wildcard) const
{
   const char *string = ccp();
   const char *wild = wildcard.ccp();

   const char *cp=0, *mp=0;

   while ((*string) && (*wild != '*')) {
      if ((*wild != *string) && (*wild != '?')) {
         return *string - *wild;
      }
      wild++;
      string++;
   }

   while (*string) {
      if (*wild == '*') {
         if (!*++wild) {
            return 0;
         }
         mp = wild;
         cp = string+1;
      } else if ((*wild == *string) || (*wild == '?')) {
         wild++;
         string++;
      } else {
         wild = mp;
         string = cp++;
      }
   }

   while (*wild == '*') {
      wild++;
   }

   return *wild ? -1 : 0;
}




// ---------------------------------------------------------------------------
// Implementierung cStrEnv
// ---------------------------------------------------------------------------

//! @class cStrEnv
//! @todo get & put, assign("a=b")

void cStrEnv::set(const cString &value) {
   if (isEmpty()) {
      return;
   } else if (value.isEmpty()) {
      // GnuC hat putenv(char*) statt putenv(const char *)
      // TBD: ist putenv() überhaupt Standard-C ???
      _putenv((char*)(*this+"=").ccp());
   } else {
      // s.o.
      _putenv((char*)(*this+"="+value).ccp());
   }
}

void cStrEnv::assign()
{
   if (isEmpty()) {
      return;
   } else {
      // s.o.
      _putenv((char*)(*this).ccp());
   }
}

cString cStrEnv::get()
{
   // 2004-11-15 -MW- GnuC kann mit getenv(0) nicht umgehen
   return isEmpty() ? cString() : getenv(*this);
}

cString cStrEnv::replace()
{
   int startenv,endenv = 0,start = 0;

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




}; // namespace ecl


