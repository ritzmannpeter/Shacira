
#include "cReliance.h"

cReliance::cReliance(const char * name)
{
   _Name = name;
}

cReliance::~cReliance()
{
}

void cReliance::Add(cPath * path)
{
   STRING_T key = path->Name();
   _DependentFiles[key.c_str()] = path;
}

void cReliance::DependentFiles(STRING_LIST_T & files, const char * base_directory)
{
   PATH_MAP_T::const_iterator i = _DependentFiles.begin();
   while (i != _DependentFiles.end()) {
      cPath * path = (*i).second;
      files.push_back(path->RelativePath(base_directory));
      i++;
   }
}


cReliances::cReliances()
{
}

cReliances::~cReliances()
{
}

void cReliances::Add(const char * name, cReliance * reliance)
{
   _Reliances[name] = reliance;
}

cReliance * cReliances::Reliance(const char * name)
{
   RELIANCE_MAP_T::const_iterator i = _Reliances.find(name);
   if (i == _Reliances.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
}

void cReliances::Reliances(RELIANCE_MAP_T & reliances)
{
   reliances = _Reliances;
}






