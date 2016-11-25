
#ifndef _altchannel_h_
#define _altchannel_h_ 1

#include "altring.h"
#include "System/Threads/cControlThread.h"
class cAlternateAdapter;

class cAlternateChannel : public cControlThread 
{
public:
   cAlternateChannel(const char * name);
   virtual ~cAlternateChannel();
   void Start();
   void Send(TransientObjectPtr object);
   void Connect(cAlternateAdapter * adapter);
   void Connect (cAlternateChannel * channel);
   unsigned long Fill();
protected:
   virtual int MainFunc(void *extra);
private:
   void Emit(TransientObjectPtr object);
   void Propagate(TransientObjectPtr object);
private:
   std::map<cAlternateChannel*,cAlternateChannel*> _Channels;
   std::map<cAlternateAdapter*,cAlternateAdapter*> _Adapters;
   std::list<TransientObjectPtr> _ObjectList;
   ULONG_T _Fill;
   cMutexSem _SendMutex;
};

class cAlternateAdapter
{
public:
   cAlternateAdapter();
   virtual ~cAlternateAdapter();
   virtual void Object(TransientObjectPtr object);
};

#endif
