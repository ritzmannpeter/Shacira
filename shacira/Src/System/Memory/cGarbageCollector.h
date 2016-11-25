
#ifndef _cGarbageCollector_h_
#define _cGarbageCollector_h_ 1

#include <stddef.h>
#include <malloc.h>
#include <string>
#include <list>
#include <map>
#include <map>
#include "base/eb_sema.hpp"

class cTransientObject;

class GarbageLock
{
public:
   GarbageLock(cMutexSem * mutex)
     : _Mutex(mutex)
   {
      _Mutex->request();
   };
   ~GarbageLock()
   {
      _Mutex->release();
   };
private:
   cMutexSem * _Mutex;
};

class cGarbageCollector {
public:
   friend class cTransientObject;
public:
   cGarbageCollector();
   virtual ~cGarbageCollector();
   void AddObject(cTransientObject * object);
   void Clear();
protected:
   cMutexSem _GarbageMutex;
   std::map<cTransientObject*,int> _GarbageMap;
};

#endif // _cGarbageCollector_h_
