
#include "cGarbageCollector.h"
#include "System/Objects/cTransientObject.h"

cGarbageCollector::cGarbageCollector()
{
}

cGarbageCollector::~cGarbageCollector()
{
}

void cGarbageCollector::AddObject(cTransientObject * object)
{
   GarbageLock __lock__(&_GarbageMutex);
   std::map<cTransientObject*,int>::iterator i = _GarbageMap.find(object);
   if (i == _GarbageMap.end()) {
      _GarbageMap[object] = 1;
   } else {
      (*i).second++;
   }
}

void cGarbageCollector::Clear()
{
   GarbageLock __lock__(&_GarbageMutex);
   std::map<cTransientObject*,int>::iterator i = _GarbageMap.begin();
   while (i != _GarbageMap.end()) {
      cTransientObject * object = (*i).first;
      int count = (*i).second;
      delete object;
      i++;
   }
   _GarbageMap.clear();
}

