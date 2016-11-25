
#ifndef cReliance_h
#define cReliance_h

#include "cPath.h"

class cReliance {
public:
   cReliance(const char * name);
   virtual ~cReliance();
   void Add(cPath * path);
   void DependentFiles(STRING_LIST_T & files, const char * base_directory);
private:
private:
   STRING_T _Name;
   PATH_LIST_T _DependentFiles;
};

typedef std::map<STRING_T,cReliance*> RELIANCE_MAP_T;

class cReliances {
public:
   cReliances();
   virtual ~cReliances();
   void Add(const char * name, cReliance * reliance);
   cReliance * Reliance(const char * name);
private:
private:
   RELIANCE_MAP_T _Reliances;
};

#endif
