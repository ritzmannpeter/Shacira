
#ifndef _cfileenumerator_h
#define _cfileenumerator_h 	1

#include "global_defs.h"

class cFileEnumerator
{
public:
   cFileEnumerator(const char * path, bool recursive = false)
   {
      _Path = path;
      _Recursive = recursive;
   };
   virtual ~cFileEnumerator()
   {
   };
   virtual void Process();
   virtual void File(STRING_T file) = 0;
protected:
   bool _Recursive;
   STRING_T _Path;
};

#endif

