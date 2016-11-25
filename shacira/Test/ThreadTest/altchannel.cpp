
#include "altchannel.h"
#include "base/base_ex.h"

cAlternateChannel::cAlternateChannel(const char * name)
   : _Fill(0)
{
}

cAlternateChannel::~cAlternateChannel()
{
}

void cAlternateChannel::Start()
{
   cControlThread::Start();
}

void cAlternateChannel::Send(TransientObjectPtr object)
{
   cObjectLock __lock__(&_SendMutex);
   _ObjectList.push_back(object);
   _Fill = _ObjectList.size();
}

void cAlternateChannel::Connect(cAlternateAdapter * adapter)
{
   cObjectLock __lock__(&_SendMutex);
   _Adapters[adapter] = adapter;
}

void cAlternateChannel::Connect(cAlternateChannel * channel)
{
   cObjectLock __lock__(&_SendMutex);
   _Channels[channel] = channel;
}

unsigned long cAlternateChannel::Fill()
{
   unsigned long fill = __ECL_ATOMIC_GET__(_Fill);
   return fill;
}

int cAlternateChannel::MainFunc (void *extra)
{
   while (true) {
      if (_ObjectList.size() > 0) {
         cObjectLock __lock__(&_SendMutex);
         TransientObjectPtr object = _ObjectList.back();
         Emit(object);
         _ObjectList.pop_back();
      } else {
         cSystemUtils::Suspend(0);
      }
   }
   return 0;
}

void cAlternateChannel::Emit(TransientObjectPtr object)
{
   std::map<cAlternateChannel*,cAlternateChannel*>::const_iterator c = _Channels.begin();
   while (c != _Channels.end()) {
      cAlternateChannel * channel = (*c).second;
      channel->Send(object);
      c++;
   }
   std::map<cAlternateAdapter*,cAlternateAdapter*>::const_iterator a = _Adapters.begin();
   while (a != _Adapters.end()) {
      cAlternateAdapter * adapter = (*a).second;
      adapter->Object(object);
      a++;
   }
}

void cAlternateChannel::Propagate(TransientObjectPtr object)
{
   std::map<cAlternateChannel*,cAlternateChannel*>::const_iterator c = _Channels.begin();
   while (c != _Channels.end()) {
      cAlternateChannel * channel = (*c).second;
      channel->Send(object);
      c++;
   }
   std::map<cAlternateAdapter*,cAlternateAdapter*>::const_iterator a = _Adapters.begin();
   while (a != _Adapters.end()) {
      cAlternateAdapter * adapter = (*a).second;
      adapter->Object(object);
      a++;
   }
}

cAlternateAdapter::cAlternateAdapter()
{
}

cAlternateAdapter::~cAlternateAdapter()
{
}

void cAlternateAdapter::Object(TransientObjectPtr object)
{
}

