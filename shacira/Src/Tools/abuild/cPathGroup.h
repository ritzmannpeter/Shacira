
#ifndef _cPathGroup_h
#define _cPathGroup_h 	1

#include "abuild.h"

class cPath;
typedef std::list<cPath*> PATH_LIST_T;

class cPathGroup {
public:
   cPathGroup();
   virtual ~cPathGroup();
   void Add(cPath * path);
   void List(PATH_LIST_T & paths);
private:
private:
   PATH_LIST_T _PathList;
};

#endif

