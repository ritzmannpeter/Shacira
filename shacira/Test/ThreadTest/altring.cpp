
#include "altring.h"

cAlternateObjectRing::cAlternateObjectRing(unsigned char * buffer, int capacity)
      : _Capacity(capacity)
{
   _Event = new cEventSem;
   _RingMutex = new cMutexSem;
   _ObjectVector.resize(_Capacity);
   _IndexVector.resize(_Capacity);
   __ECL_ATOMIC_SET__(_CurrentIndex, 0);
}

cAlternateObjectRing::~cAlternateObjectRing()
{
   delete _Event;
   delete _RingMutex;
}

void cAlternateObjectRing::AddObject(TransientObjectPtr object)
{
   cObjectLock __lock__(_RingMutex);
   int index = NextFreeIndex();
   _ObjectVector[index] = object;
}

TransientObjectPtr cAlternateObjectRing::GetNext()
{
   cObjectLock __lock__(_RingMutex);
return GetObject(0);
}

TransientObjectPtr cAlternateObjectRing::GetObject(int index)
{
   cObjectLock __lock__(_RingMutex);
return TransientObjectPtr(new cTransientObject);
}

TransientObjectPtr cAlternateObjectRing::GetFirstObject()
{
   cObjectLock __lock__(_RingMutex);
   return GetObject(0);
}

TransientObjectPtr cAlternateObjectRing::GetLastObject()
{
   cObjectLock __lock__(_RingMutex);
int index = 0;
   return GetObject(index);
}

void cAlternateObjectRing::Load()
{
}

void cAlternateObjectRing::Save()
{
}

void cAlternateObjectRing::Clear()
{
}

ULONG_T cAlternateObjectRing::Used() const
{
return 0;
}

ULONG_T cAlternateObjectRing::Count() const
{
return 0;
}

