
#include "FirstHeader.h"
#include "System/Channel/cLocalChannel.h"
#include "System/Objects/cDataChange.h"
#include "System/Objects/cJobEntry.h"
#include "System/Objects/cJobSpec.h"
#include "System/Objects/cAlarm.h"
#include "System/Objects/cInfo.h"
#include "System/Objects/cProgress.h"
#include "Client/Adapters/cEventAdapter.h"
#include "base/eb_thread.hpp"
#include "base/eb_queue.hpp"
#include "base/semaphore.h"
#include "base/message.h"
#include "System/Structs/cExtendedObjectRing.h"
#include "System/Memory/cMemPool.h"
#include "System/Memory/cGarbageCollector.h"
#include "System/Sys/cexceptionhnd.h"

#define VERY_LONG_TEXT_LENGTH 0xFFFF
static char * _veryLongText = NULL;
static char * veryLongText()
{
   if (_veryLongText == NULL) {
      _veryLongText = (char*)calloc(1, VERY_LONG_TEXT_LENGTH);
      int i = 0;
      for (i=0; i<VERY_LONG_TEXT_LENGTH-1; i++) {
         char c = (i%255);
         if (c < 30 || c > 128) {
            c = 'p';
         }
         _veryLongText[i] = c;
      }
   }
   return _veryLongText;
}

static bool _emulateMosaic = false;
static bool _cyclicTest = false;
static bool _log = false;

#define SAFE_OBJECT_MANAGEMENT_
#ifdef SAFE_OBJECT_MANAGEMENT

#include "altring.h"
#include "altchannel.h"
#define IS_NULL_OBJECT(ptr) (false)
typedef cAlternateObjectRing ObjectRing;
typedef cAlternateChannel Channel;
typedef cAlternateAdapter Adapter;
static void Release(TransientObjectPtr object)
{
}
static void AddRef(TransientObjectPtr object)
{
}

#else

#define IS_NULL_OBJECT(ptr) (ptr == NULL)
typedef cTransientObject * TransientObjectPtr;
typedef cExtendedObjectRing ObjectRing;
typedef cLocalChannel Channel;
typedef cEventAdapter Adapter;
static void Release(TransientObjectPtr object)
{
   object->Release();
}
static void AddRef(TransientObjectPtr object)
{
   object->AddRef();
}

#endif

static char _LogFileName[0x255] = {0};
static char _Text[0x2000] = {0};
static void LogPrintf(const char * fmt_str, ...)
{
   va_list ap;
   va_start(ap, fmt_str);
   try {
      vsprintf(_Text, fmt_str, ap);
      printf("%s", _Text);
      if (strlen(_LogFileName) > 0) {
         FILE * stream = fopen(_LogFileName, "a");
         if (stream != NULL) {
            fprintf(stream, "%s", _Text);
            fclose(stream);
         }
      }
   } catch (...) {
   }
   va_end(ap);
}



#define _Printf LogPrintf
//#define _Printf printf
//#define _Printf InfoPrintf
//#define RING_BUF_SIZE 0x2000
#define RING_SIZE       10
#define RING_BUF_SIZE   ((FLAT_OBJECT_HEADER_SIZE + (RING_SIZE * 4)) + (2 * sizeof(cRingBase::RING)))

static bool _hold = false;

#if defined(_WIN32)

// Ctrl + x handler
BOOL WINAPI CtrlHandler(DWORD dwCtrlType)
{
   switch (dwCtrlType) {
   case CTRL_C_EVENT:
      if (_hold) {
         _hold = false;
      } else {
         _hold = true;
      }
      break;
   case CTRL_BREAK_EVENT:
      _Printf("CTRL+BREAK\n");
      break;
   case CTRL_CLOSE_EVENT:
      _Printf("CTRL+CLOSE\n");
      break;
   case CTRL_LOGOFF_EVENT:
      _Printf("CTRL+LOGOFF\n");
      break;
   case CTRL_SHUTDOWN_EVENT:
      _Printf("CTRL+SHUTDOWN\n");
      break;
   }
   return true;
}

#endif

void SynchronizationError(cTransientObject * object)
{
   int dummy = 0;
}

static TransientObjectPtr newJobEntry()
{
   cJobEntry * job_entry = new cJobEntry;
   char propertyName[0x255] = {0};
   char propertyValue[0x255] = {0};
   int i = 0;
   for (i=0; i<10; i++) {
      sprintf(propertyName, "heinz_%d", i);
      sprintf(propertyValue, "%d", rand());
      job_entry->AddPropertyValue(propertyName, propertyValue);
   }
   return TransientObjectPtr(job_entry);
}

static TransientObjectPtr _Singleton = NULL;
static cMutexSem _StatisticMutex;
static TransientObjectPtr newObject()
{
   if (_cyclicTest) {
      static int _generated_objects = 0;
      int generated_objects = __ECL_ATOMIC_GET__(_generated_objects);
      __ECL_ATOMIC_INCREMENT__(_generated_objects);
      if (_Singleton != NULL) {
         if (generated_objects > 0) {
            _Singleton = NULL;
         }
      } else {
         if (_Singleton == NULL && generated_objects == 0) {
            _Singleton = newJobEntry();
         }
      }
      return _Singleton;
   } else if (_emulateMosaic) {
      return newJobEntry();
   } else {
      int x = rand();
      if (x % 5 == 0) {
         cInfo * info = new cInfo;
         return TransientObjectPtr(info);
      } else if (x % 6 == 0) {
         cAlarm * alarm = new cAlarm;
         return TransientObjectPtr(alarm);
      } else if (x % 8 == 0) {
         cJobSpec * job_spec = new cJobSpec;
         return TransientObjectPtr(job_spec);
      } else if (x % 9 == 0) {
         cProgress * progress = new cProgress;
         return TransientObjectPtr(progress);
      } else {
         return newJobEntry();
      }
   }
}

class cWorkerThread : public cThread
{
public:
   cWorkerThread(Channel * channel, ObjectRing * ring)
      : _produce(false), _Channel(channel), _Ring(ring)
   {
   };
   virtual ~cWorkerThread()
   {
   };
   virtual int onMain (void *extra)
   {
      static bool p = _produce;
      while (true) {
         if (_hold) {
            cSystemUtils::Suspend(10);
         } else {
            cObjectLock __lock__(&_WorkerMutex);
            ATOMIC_T objectCount = cTransientObject::get_ObjectCount();
            if (!_produce && objectCount == 0) {
               _produce = true;
            }
            if (_produce && objectCount == 10000) {
               _produce = false;
            }
            if (p != _produce) {
               p = _produce;
               if (_produce) {
                  _Printf("started producing\n");
               } else {
                  _Printf("stopped producing\n");
               }
            }
            if (!_produce) {
               cSystemUtils::Suspend(10);
            } else {
               TransientObjectPtr object = newObject();
               if (_log) {
                  InfoPrintf("created object %p\n", object);
                  ErrorPrintf("created object %p\n", object);
                  InfoPrintf("text %s\n", veryLongText());
                  ErrorPrintf("text %s\n", veryLongText());
               }
               if (object != NULL) {
                  if (_Channel != NULL) {
                     _Channel->Send(object);
                     Release(object);
                  }
               }
               if (rand() % 1234 == 0) {
                  cSystemUtils::Suspend(rand() % 10);
               }
            }
         }
      }
   };
   bool Producing() const {return _produce;};
private:
   bool _produce;
   Channel * _Channel;
   cMutexSem _WorkerMutex;
   ObjectRing * _Ring;
};

static Channel * root_channel = NULL;
static ULONG_T _sent = 0;
class cLogger : public Adapter
{
public:
   cLogger(ObjectRing * ring)
   {
      _RingUsed = 0;
      _StatisticsQueue = new cQueue<struct StatisticElement*>(10);
      _Ring = ring;
   };
   ~cLogger()
   {
   };
   virtual void Object(TransientObjectPtr object)
   {
      static const char * ptr = NULL;
      if (_Ring == NULL) {
         ATOMIC_T objectCount = object->get_ObjectCount();
         ATOMIC_T objectNo = object->get_ObjectNo();
         ATOMIC_T objectIdent = object->get_ObjectIdent();
         object->set_ObjectIdent(objectIdent);
      } else {
         if (_emulateMosaic) {
#ifndef SAFE_OBJECT_MANAGEMENT
            cObjectLock __lock1__(_Ring->RingMutex());
            ULONG_T ringUsedCount = _Ring->Used();
            ULONG_T ringTotalCount = _Ring->Count();
            ULONG_T queueUsedCount = _StatisticsQueue->getUsed();
            ULONG_T queueFreeCount = _StatisticsQueue->getFree();
            ULONG_T queueTotalCount = _StatisticsQueue->getCount();
            TransientObjectPtr to = _Singleton;
            if (IS_NULL_OBJECT(object)) {
               printf("NULL!\n");
               int dummy = 0;
            } else {
               cJobEntry * _NewJobEntry = NULL;
               cJobEntry * _RemovedJobEntry = NULL;
               if (_Ring->Used() == _Ring->Count()) {
                  _RemovedJobEntry =  (cJobEntry*)(_Ring->GetFirstObject());
               } else {
                  _RemovedJobEntry  = NULL;
               }
               _Ring->AddObject(TransientObjectPtr(object));
               _NewJobEntry =  (cJobEntry*)_Ring->GetLastObject();
               _RingUsed = _Ring->Used();
               if (_StatisticsQueue->isFull()) {
                  // wenn die queue voll ist, darf hier nicht geblockt
                  // werden, weil der put-Aufruf dann auch blockt,
                  // und es in der Folge zu einem deadlock kommen kann
                  struct StatisticElement * element = (struct StatisticElement*)cSystemUtils::Alloc(sizeof(struct StatisticElement));
                  element->new_object = _NewJobEntry;
                  element->removed_object = _RemovedJobEntry;
                  _StatisticsQueue->put(element);
               } else {
                  cObjectLock __lock__(&_StatisticsQueueMutex);
                  struct StatisticElement * element = (struct StatisticElement*)cSystemUtils::Alloc(sizeof(struct StatisticElement));
                  element->new_object = _NewJobEntry;
                  element->removed_object = _RemovedJobEntry;
                  _StatisticsQueue->put(element);
               }
            }
#endif
         } else if (_cyclicTest) {
#ifndef SAFE_OBJECT_MANAGEMENT
            DOUBLE_T AvgSum = 0;
            DOUBLE_T Avg = 0;
            cJobEntry * je = dynamic_cast<cJobEntry*>(object);
            if (je == NULL) {
               int dummy = 0;
            } else {
               ULONG_T entries = je->Properties();
               ULONG_T values = 33;
               for (ULONG_T i=0; i<entries; i++) {
                  STRING_T propertyName = je->Property(i);
                  STRING_T propertyValue = je->PropertyValue(propertyName.c_str());
                  int v = atoi(propertyValue.c_str());
                  AvgSum += ((i+1)*v);
               }
               Avg = AvgSum / factorial(entries);
               char new_value[0x255] = {0};
               sprintf(new_value, "%f", Avg);
               je->AddPropertyValue("avg", new_value);
            }
            ATOMIC_T ref_count = object->get_RefCount();
            if (root_channel != NULL) {
               if (ref_count < 0xf000000) {
                  _sent++;
                  root_channel->Send(object);
               } else {
                  int dummy = 0;
               }
            } else {
               int dummy = 0;
            }
#endif
         } else {
            _Ring->AddObject(object);
           if (_log) {
               InfoPrintf("added object %p to ring\n", object);
               ErrorPrintf("added object %p to ring\n", object);
               InfoPrintf("text %s\n", veryLongText());
               ErrorPrintf("text %s\n", veryLongText());
           }
            cObjectLock __lock__(_Ring->RingMutex());
            ULONG_T used = _Ring->Used();
            for (unsigned int i=0; i<used; ++i) {
               TransientObjectPtr o = _Ring->GetObject(i);
               if (o == NULL) {
                  int dummy = 0;
               } else {
                  ATOMIC_T refc = o->get_RefCount();
                  ATOMIC_T id = o->get_ObjectIdent();
                  o->set_UserName("sepp");
                  STRING_T s = o->get_UserName();
                  if (o == object) {
                  }
                  Release(o);
               }
            }
         }
      }
   };
   inline DOUBLE_T factorial(int n)
   {
      DOUBLE_T f = 0;
      int i = 0;
      for (i=0; i<n; i++) {
         f += i;
      }
      return f;
   };
   void Cycle()
   {
#ifndef SAFE_OBJECT_MANAGEMENT
cObjectLock __lock__(&_StatisticsQueueMutex);
      int used = _StatisticsQueue->getUsed();
      while (!_StatisticsQueue->isEmpty()) {
         struct StatisticElement * element = _StatisticsQueue->get();
         cJobEntry * new_object = element->new_object;
         cJobEntry * removed_object = element->removed_object;
         UpdateStatisticValues(new_object, removed_object);
         if (new_object != NULL) {
            Release(new_object);
         }
         if (removed_object != NULL) {
            Release(removed_object);
         }
         cSystemUtils::Free(element);
      }
#endif
   };
   void UpdateStatisticValues(cJobEntry * new_object, cJobEntry * removed_object)
   {
      DOUBLE_T AvgSum = 0;
      DOUBLE_T Avg = 0;
      if (new_object == NULL) {
         return;
      } else {
         ULONG_T entries = new_object->Properties();
         ULONG_T values = _RingUsed;
         ULONG_T sortedvalues = values;
         for (ULONG_T i=0; i<entries; i++) {
            STRING_T propertyName = new_object->Property(i);
            STRING_T propertyValue = new_object->PropertyValue(propertyName.c_str());
            int v = atoi(propertyValue.c_str());
            AvgSum += ((i+1)*v);
         }
         Avg = AvgSum / factorial(entries);
         char new_value[0x255] = {0};
         sprintf(new_value, "%f", Avg);
         new_object->AddPropertyValue("avg", new_value);
         int dummy = 0;
      }
   };
private:
   ObjectRing * _Ring;
   ULONG_T _RingUsed;
   struct StatisticElement {cJobEntry * new_object; cJobEntry * removed_object;};
   cQueue<struct StatisticElement*> * _StatisticsQueue;
   cMutexSem _StatisticsQueueMutex;
};

int main(int argc, char ** argv)
{
   cResources resources(argc, argv);
   cExceptionHnd _ExceptionHandler;
   int threads = 1;
   int arg = 0;
   for (arg=1; arg<argc; arg++) {
      if (stricmp(argv[arg], "em") == 0) {
         _emulateMosaic = true;
      } else if (stricmp(argv[arg], "ct") == 0) {
         _cyclicTest = true;
      } else if (stricmp(argv[arg], "log") == 0) {
         _log = true;
      } else {
         int v = atoi(argv[arg]);
         if (v > 0) {
            threads = v;
         }
      }
   }
   sprintf(_LogFileName, "thread_log_%d%s%s.log", threads, _cyclicTest ? "_ct" : "", _emulateMosaic ? "_em" : "");
   remove(_LogFileName);
#if defined(_WIN32)
   SetConsoleCtrlHandler(CtrlHandler, true);
#endif
//   cSystemUtils::SetArchitectureFlags(RESTRICT_TO_SINGLE_CPU);
   cMemPool * pool = NULL;
//   pool = new cMemPool;
   cTransientObject::InitializeObjectManagement(pool);
   cGarbageCollector * collector = NULL;
   collector = new cGarbageCollector;
   cTransientObject::InitializeObjectManagement(collector);
   cTransientObject::SetSynchronizationError(SynchronizationError);
   int max_concurrent_threads = threads * 4;
   _Printf("starting %d threads concurrent access %d...\n", threads, max_concurrent_threads);
//   cQueueRaw::setMaxConcurrentAccess(max_concurrent_threads);
   UCHAR_T * buffer = NULL;
   ObjectRing * ring = NULL;
   buffer = (UCHAR_T*)cSystemUtils::Alloc(RING_BUF_SIZE);
   ring = new ObjectRing(buffer, RING_BUF_SIZE);
   root_channel = new Channel("root_channel");
   root_channel->Start();
   cLogger * logger = new cLogger(ring);
   for (int i=0; i<threads; i++) {
      char channel_name[0x100] = {0};
      sprintf(channel_name, "channel_1_%d", i);
      Channel * channel1 = new Channel(channel_name);
      channel1->Start();
      sprintf(channel_name, "channel_0_%d", i);
      Channel * channel0 = new Channel(channel_name);
      channel0->Start();

      root_channel->Connect(channel0);
      channel0->Connect(channel1);
      root_channel->Connect(logger);

//      root_channel->Connect(channel0);
//      channel0->Connect(logger);

//      root_channel->Connect(channel0);
//      channel0->Connect(channel1);
//      channel1->Connect(logger);

   }
   cWorkerThread * worker_thread = NULL;
   worker_thread = new cWorkerThread(root_channel, ring);
   worker_thread->start();
   long prev_object_no = 0;
   static long prev_object_count = 0;
   static ULONG_T lastPrint = 0;
   while (true) {
      if (_emulateMosaic) {
         logger->Cycle();
      }
      ULONG_T t = cSystemUtils::RealtimeOffset();
      if ((t - lastPrint) > 3000) {
         static int first = false;
         long object_count = cTransientObject::get_ObjectCount();
         long object_no = cTransientObject::get_ObjectNo();
         long diff_object_no = object_no - prev_object_no;
         long diff_object_count = object_count - prev_object_count;
         ULONG_T rc_fill = root_channel->Fill();
         prev_object_count = object_count;
         prev_object_no = object_no;
         if (object_count == -1) {
            if (first) {
               first = false;
               _Printf("%d objects current %d diff (%d,%d),(%d,%d)\n", object_count, object_no, diff_object_no, diff_object_count, _sent, rc_fill);
            }
         } else {
            _Printf("%d objects current %d diff (%d,%d),(%d,%d)\n", object_count, object_no, diff_object_no, diff_object_count, _sent, rc_fill);
         }
         lastPrint = t;
      }
      if (!worker_thread->Producing()) {
         ring->Clear();
         cObjectLock __lock1__(ring->RingMutex());
         ULONG_T used = ring->Used();
         for (unsigned int i=0; i<used; ++i) {
            TransientObjectPtr o = ring->GetObject(i);
            if (o == NULL) {
               int dummy = 0;
            } else {
               ATOMIC_T refc = o->get_RefCount();
               Release(o);
            }
         }
         cTransientObject::ClearGarbage();
      }
      cSystemUtils::Suspend(10);
   }
   return 0;
}

