
#ifndef _cPath_h
#define _cPath_h 	1

#include "global_defs.h"
#include "cdirectoryutils.h"

class cPath;
typedef std::map<STRING_T,cPath*> PATH_MAP_T;
typedef std::list<cPath*> PATH_LIST_T;

class cPath {
public:
   cPath(const char * path_spec);
   virtual ~cPath();
   bool Exists();
   STRING_T RelativePath(const char * directory);
   STRING_T RelativeDirectory(const char * path);
   bool inline IsDirectory() {return _IsDirectory;};
   STRING_T inline Path() {return _Path;};
   STRING_T inline AbsolutePath() {return _AbsolutePath;};
   STRING_T inline BaseName() {return _BaseName;};
   STRING_T inline Name() {return _Name;};
   STRING_T inline Extension() {return _Extension;};
   STRING_T inline AbsoluteDirectory() {return _AbsoluteDirectory;};
   static STRING_T Normalize(const char * path);
   static STRING_T ResolveSymbols(const char * str);
private:
private:
   bool _IsDirectory;
   STRING_T _Path;
   STRING_T _AbsolutePath;
   STRING_T _AbsoluteDirectory;
   STRING_T _BaseName;
   STRING_T _Name;
   STRING_T _Extension;
};

#endif

