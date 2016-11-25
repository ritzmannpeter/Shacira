
#ifndef _cPath_h
#define _cPath_h 	1

#include "abuild.h"
#include "cDirectoryUtils.h"

class cPath;
typedef std::map<STRING_T,cPath*> PATH_MAP_T;
typedef std::list<cPath*> PATH_LIST_T;

class cPath {
public:
   cPath(const char * path_spec);
   virtual ~cPath();
   bool Exists();
   STRING_T RelativePath(const char * directory);
   bool inline IsDirectory() {return _IsDirectory;};
   STRING_T inline Path() {return _Path;};
   STRING_T inline AbsolutePath() {return _AbsolutePath;};
   STRING_T inline BaseName() {return _BaseName;};
   STRING_T inline Name() {return _Name;};
   STRING_T inline Extension() {return _Extension;};
   static STRING_T Normalize(const char * path);
   static STRING_T ResolveSymbols(const char * str);
private:
private:
   bool _IsDirectory;
   STRING_T _Path;
   STRING_T _AbsolutePath;
   STRING_T _BaseName;
   STRING_T _Name;
   STRING_T _Extension;
};

#endif

