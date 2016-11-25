
#ifndef _GRABBER_H_
#define _GRABBER_H_

#include "FirstHeader.h"
#include "System/Threads/cControlThread.h"
#include "Control/Device/cDevice.h"
#include "Control/LocalDatabase/cLocalVariable.h"
#include "base/eb_sema.hpp"

#define IMAGE_SIZE   2000000
#define IMAGE_COUNT  4

class Grabber : public cControlThread
{
public:
   Grabber(cMutexSem * sync, int idle_time = 100);
   virtual ~Grabber() {};
   void Start();
   void Stop();
   BUF_T Buffer(int index);
   void SetDevice(cDevice * device, int index);
   void Save(int index);
protected:
   virtual int ControlFunc ();
private:
   void Grab();
private:
   BOOL_T _Active;
   BUF_T _Buffers[IMAGE_COUNT];
   cDevice * _Devices[IMAGE_COUNT];
   cMutexSem * _Sync;
};

#endif
