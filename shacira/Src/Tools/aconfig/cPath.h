
#ifndef _cPath_h
#define _cPath_h 	1

#include "cConfigUtils.h"

class cPath;
typedef std::map<STRING_T,cPath*> PATH_MAP_T;
typedef std::list<cPath*> PATH_LIST_T;

class cPath {
public:
   cPath(CONST_STRING_T file, BOOL_T is_directory = false);
   virtual ~cPath();
   static void SetBaseDirectory(CONST_STRING_T directory);
   static void Print();
   void SetBase(CONST_STRING_T directory);
   STRING_T Path();
   STRING_T File();
   STRING_T FileName();
   STRING_T BaseName();
   STRING_T Extension();
   STRING_T AbsPathx();
   STRING_T RelPath();
   STRING_T PathSpec();
   STRING_T BaseDirectory();
public:
   static BOOL_T _RelativePaths;
   static BOOL_T _AbsolutePaths;
   static BOOL_T _OriginalPaths;
private:
   STRING_T _File;
   STRING_T _FileName;
   STRING_T _BaseName;
   STRING_T _Extension;
   STRING_T _Path;
   STRING_T _AbsPath;
   STRING_T _RelPath;
   BOOL_T _IsDirectory;
   STRING_T _BaseDirectory;
   static PATH_MAP_T _PathMap;
   static PATH_LIST_T _PathList;
private:
   void Store(cPath * path);
};

#endif

