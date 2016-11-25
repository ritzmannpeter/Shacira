//## begin module%3F82F311037A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F82F311037A.cm

//## begin module%3F82F311037A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F82F311037A.cp

//## Module: cChannel%3F82F311037A; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cChannel.cpp

//## begin module%3F82F311037A.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F82F311037A.additionalIncludes

//## begin module%3F82F311037A.includes preserve=yes
//## end module%3F82F311037A.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cConnector
#include "System/Channel/cConnector.h"
// cChannel
#include "System/Channel/cChannel.h"
//## begin module%3F82F311037A.additionalDeclarations preserve=yes
//## end module%3F82F311037A.additionalDeclarations


// Class cChannel 






//## begin cChannel::ChannelVectorMutex%42F4830F02BF.attr preserve=no  protected: static cMutexSem {U} 
cMutexSem cChannel::_ChannelVectorMutex;
//## end cChannel::ChannelVectorMutex%42F4830F02BF.attr

//## begin cChannel::ChannelVectorIndex%42F4837601E4.attr preserve=no  protected: static ULONG_T {U} 0
ULONG_T cChannel::_ChannelVectorIndex = 0;
//## end cChannel::ChannelVectorIndex%42F4837601E4.attr

//## begin cChannel::ChannelVector%42F4837601D4.attr preserve=no  public: static CHANNEL_VECTOR_T {U} 
CHANNEL_VECTOR_T cChannel::_ChannelVector;
//## end cChannel::ChannelVector%42F4837601D4.attr




cChannel::cChannel()
  //## begin cChannel::cChannel%.hasinit preserve=no
      : _Bridge(NULL), _Listening(false), _Fill(0)
  //## end cChannel::cChannel%.hasinit
  //## begin cChannel::cChannel%.initialization preserve=yes
  //## end cChannel::cChannel%.initialization
{
  //## begin cChannel::cChannel%.body preserve=yes
_ASSERT_UNCOND
  //## end cChannel::cChannel%.body
}

cChannel::cChannel(const cChannel &right)
  //## begin cChannel::cChannel%copy.hasinit preserve=no
      : _Bridge(NULL), _Listening(false), _Fill(0)
  //## end cChannel::cChannel%copy.hasinit
  //## begin cChannel::cChannel%copy.initialization preserve=yes
  //## end cChannel::cChannel%copy.initialization
{
  //## begin cChannel::cChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cChannel::cChannel%copy.body
}

cChannel::cChannel (CONST_STRING_T channel_name)
  //## begin cChannel::cChannel%1065547488.hasinit preserve=no
      : _Bridge(NULL), _Listening(false), _Fill(0)
  //## end cChannel::cChannel%1065547488.hasinit
  //## begin cChannel::cChannel%1065547488.initialization preserve=yes
  //## end cChannel::cChannel%1065547488.initialization
{
  //## begin cChannel::cChannel%1065547488.body preserve=yes
   _Class = "Channel";
   _Type = "Channel";
   _Name = channel_name;
   if (_ChannelVector == NULL) {
      _ChannelVector = (cChannel**)cSystemUtils::Alloc(sizeof(cChannel*) * CHANNEL_VECTOR_SIZE);
   }
   AddChannel();
  //## end cChannel::cChannel%1065547488.body
}


cChannel::~cChannel()
{
  //## begin cChannel::~cChannel%.body preserve=yes
   Stop();
  //## end cChannel::~cChannel%.body
}



//## Other Operations (implementation)
void cChannel::Start ()
{
  //## begin cChannel::Start%1072782024.body preserve=yes
   cControlThread::Start();
  //## end cChannel::Start%1072782024.body
}

void cChannel::Stop ()
{
  //## begin cChannel::Stop%1072782025.body preserve=yes
   cControlThread::Stop();
  //## end cChannel::Stop%1072782025.body
}

void cChannel::Connect (cAdapter *adapter)
{
  //## begin cChannel::Connect%1065547480.body preserve=yes
   if (!_Listening) Listen();
   _Adapters.Add(adapter);
   InfoPrintf("%s -> %s\n",
              get_Name().c_str(),
              adapter->get_Name().c_str());
  //## end cChannel::Connect%1065547480.body
}

void cChannel::Connect (cChannel *channel)
{
  //## begin cChannel::Connect%1065687232.body preserve=yes
   _Channels.Add(channel);
   InfoPrintf("%s -> %s\n",
              get_Name().c_str(),
              channel->get_Name().c_str());
  //## end cChannel::Connect%1065687232.body
}

void cChannel::Disconnect (cAdapter *adapter)
{
  //## begin cChannel::Disconnect%1065547481.body preserve=yes
   _Adapters.Remove(adapter);
   InfoPrintf("disconnected adapter %s from channel %s\n",
              adapter->get_Name().c_str(),
              get_Name().c_str());
  //## end cChannel::Disconnect%1065547481.body
}

void cChannel::Disconnect (cChannel *channel)
{
  //## begin cChannel::Disconnect%1073642244.body preserve=yes
   _Channels.Remove(channel);
   InfoPrintf("disconnected channel %s from channel %s\n",
              channel->get_Name().c_str(),
              get_Name().c_str());
  //## end cChannel::Disconnect%1073642244.body
}

void cChannel::Listen ()
{
  //## begin cChannel::Listen%1073642247.body preserve=yes
  //## end cChannel::Listen%1073642247.body
}

void cChannel::StopListen ()
{
  //## begin cChannel::StopListen%1073642248.body preserve=yes
  //## end cChannel::StopListen%1073642248.body
}

void cChannel::Object (cTransientObject *object)
{
  //## begin cChannel::Object%1065547485.body preserve=yes
   Emit(object);
  //## end cChannel::Object%1065547485.body
}

void cChannel::Emit (cTransientObject *object)
{
  //## begin cChannel::Emit%1069152409.body preserve=yes
   cPtrList::cConstIterator a = _Adapters.Begin();
   if (a.First()) {
      do {
         cAdapter * adapter = (cAdapter*)a.Ptr();
         if (adapter != NULL) {
            adapter->Object(object);
         }
      } while (a.Next());
   }
   cPtrList::cConstIterator c = _Channels.Begin();
   if (c.First()) {
      do {
         cChannel * channel = (cChannel*)c.Ptr();
         if (channel != NULL) {
            channel->Send(object);
         }
      } while (c.Next());
   }
  //## end cChannel::Emit%1069152409.body
}

ULONG_T cChannel::Size ()
{
  //## begin cChannel::Size%1124211834.body preserve=yes
   return ULONG_MAX;
  //## end cChannel::Size%1124211834.body
}

ULONG_T cChannel::Fill ()
{
  //## begin cChannel::Fill%1124211835.body preserve=yes
   return _Fill;
  //## end cChannel::Fill%1124211835.body
}

void cChannel::PrintChannels ()
{
  //## begin cChannel::PrintChannels%1123319920.body preserve=yes
   cObjectLock __lock__(&_ChannelVectorMutex);
   InfoPrintf("%d channels\n", _ChannelVectorIndex);
   for (ULONG_T i=0; i<_ChannelVectorIndex; i++) {
      cChannel * channel = _ChannelVector[i];
      if (channel != NULL) {
         STRING_T channel_name = channel->get_Name();
         ULONG_T fill = channel->get_Fill();
         InfoPrintf("channel %d: %s: %d\n", i, channel_name.c_str(), fill);
      }
   }
  //## end cChannel::PrintChannels%1123319920.body
}

cChannel * cChannel::GetChannel (ULONG_T index)
{
  //## begin cChannel::GetChannel%1124212412.body preserve=yes
   if (index < _ChannelVectorIndex) {
      return _ChannelVector[index];
   } else {
      return 0;
   }
  //## end cChannel::GetChannel%1124212412.body
}

ULONG_T cChannel::GetChannelCount ()
{
  //## begin cChannel::GetChannelCount%1124212413.body preserve=yes
   return _ChannelVectorIndex;
  //## end cChannel::GetChannelCount%1124212413.body
}

void cChannel::AddChannel ()
{
  //## begin cChannel::AddChannel%1123319921.body preserve=yes
   cObjectLock __lock__(&_ChannelVectorMutex);
   if (_ChannelVectorIndex < CHANNEL_VECTOR_SIZE) {
      _ChannelVector[_ChannelVectorIndex] = this; 
      _ChannelVectorIndex++;
   }
  //## end cChannel::AddChannel%1123319921.body
}

//## Get and Set Operations for Class Attributes (implementation)

cChannel * cChannel::get_Bridge () const
{
  //## begin cChannel::get_Bridge%3FF9710F0167.get preserve=no
  return _Bridge;
  //## end cChannel::get_Bridge%3FF9710F0167.get
}

void cChannel::set_Bridge (cChannel * value)
{
  //## begin cChannel::set_Bridge%3FF9710F0167.set preserve=no
  _Bridge = value;
  //## end cChannel::set_Bridge%3FF9710F0167.set
}

ULONG_T cChannel::get_Fill () const
{
  //## begin cChannel::get_Fill%42F485D7030D.get preserve=no
  return _Fill;
  //## end cChannel::get_Fill%42F485D7030D.get
}

void cChannel::set_Fill (ULONG_T value)
{
  //## begin cChannel::set_Fill%42F485D7030D.set preserve=no
  _Fill = value;
  //## end cChannel::set_Fill%42F485D7030D.set
}

// Additional Declarations
  //## begin cChannel%3F82F311037A.declarations preserve=yes
  //## end cChannel%3F82F311037A.declarations

//## begin module%3F82F311037A.epilog preserve=yes
//## end module%3F82F311037A.epilog
