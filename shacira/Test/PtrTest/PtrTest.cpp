
#include "FirstHeader.h"
#include "base/eb_thread.hpp"
#include "System/Memory/cPtrList.h"
#include "System/Objects/cObjectLock.h"


static cPtrList * _PtrList = NULL;
static unsigned long _Deref = 0;

class cWorkerThread : public cThread
{
public:
   cWorkerThread()
   {
   };
   virtual ~cWorkerThread()
   {
   };
#define PTR_COUNT 1000
   virtual int onMain (void *extra)
   {
      while (true) {
         unsigned long count = rand() % (PTR_COUNT - 2);
         unsigned long i = 0;
         for (i=0; i<count; i++) {
            _PtrList->Remove((void*)i);
         }
         for (i=0; i<count; i++) {
            _PtrList->Add((void*)i);
         }
         cPtrList::cConstIterator p = _PtrList->Begin();
         if (p.First()) {
            do {
               void * ptr = (void*)p.Ptr();
_Deref++;
            } while (p.Next());
         }
      }
   };
};

int main(int argc, char ** argv)
{
   _PtrList = new cPtrList;
   cWorkerThread * thread1 = new cWorkerThread();
   cWorkerThread * thread2 = new cWorkerThread();
   cWorkerThread * thread3 = new cWorkerThread();
   cWorkerThread * thread4 = new cWorkerThread();
   cWorkerThread * thread5 = new cWorkerThread();
   cWorkerThread * thread6 = new cWorkerThread();
   cWorkerThread * thread7 = new cWorkerThread();
   cWorkerThread * thread8 = new cWorkerThread();
   thread1->start();
   thread2->start();
   thread3->start();
   thread4->start();
   thread5->start();
   thread6->start();
   thread7->start();
   thread8->start();
   while (true) {
      Sleep(1000);
      printf("%d derefs\n", _Deref);
   }
   return 0;
}

