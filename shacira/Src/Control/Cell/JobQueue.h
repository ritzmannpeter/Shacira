
#ifndef JobQueue_h
#define JobQueue_h 1

#include "base/eb_queue.hpp"
#include "System/Objects/cObjectLock.h"

#define JOB_QUEUE_SIZE     0x500

class JobQueue 
{
public:
   JobQueue() : _Queue(JOB_QUEUE_SIZE, cQueueBase::putOverwrite) {};
   virtual ~JobQueue() {};
   void AddJob(CONST_STRING_T job)
   {
      cObjectLock __lock__(&_QueueMutex);
      _Queue.put(job);
   };
   BOOL_T GetJob(STRING_T & job)
   {
      cObjectLock __lock__(&_QueueMutex);
      if (_Queue.isEmpty()) {
         return false;
      } else {
         job = _Queue.get();
         return true;
      }
   };
private:
   cMutexSem _QueueMutex;
   cQueue<STRING_T> _Queue;
};

#endif
