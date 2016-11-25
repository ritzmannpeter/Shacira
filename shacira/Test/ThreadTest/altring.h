
#ifndef _altring_h_
#define _altring_h_ 1

#include "System/Objects/cTransientObject.h"
#include "base/semaphore.h"
#include <vector>
#include <memory>

typedef std::shared_ptr<cTransientObject> TransientObjectPtr;
typedef std::vector<std::shared_ptr<cTransientObject>> TransientObjectVector;
typedef std::vector<int> IndexVector;

class cAlternateObjectRing
{
public:
   cAlternateObjectRing(unsigned char * buffer, int capacity);
   virtual ~cAlternateObjectRing();
   void AddObject(TransientObjectPtr object);
   TransientObjectPtr GetNext();
   TransientObjectPtr GetObject(int index);
   TransientObjectPtr GetFirstObject();
   TransientObjectPtr GetLastObject();
   void Load();
   void Save();
   void Clear();
   ULONG_T Used() const;
   ULONG_T Count() const;
   cMutexSem * RingMutex() const {return _RingMutex;};
protected:
   inline int NextFreeIndex()
   {
      int current_index = __ECL_ATOMIC_GET__(_CurrentIndex);
      if (current_index == _Capacity - 1) {
         current_index = 0;
      } else {
         current_index++;
      }
      __ECL_ATOMIC_SET__(_CurrentIndex, current_index);
      return current_index;
   };
protected:
   int _Capacity;
   cMutexSem * _RingMutex;
   cEventSem * _Event;
   TransientObjectVector _ObjectVector;
   IndexVector _IndexVector;
   int _CurrentIndex;
};

#endif
