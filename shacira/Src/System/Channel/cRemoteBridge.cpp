//## begin module%3F867D4403B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F867D4403B9.cm

//## begin module%3F867D4403B9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F867D4403B9.cp

//## Module: cRemoteBridge%3F867D4403B9; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cRemoteBridge.cpp

//## begin module%3F867D4403B9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F867D4403B9.additionalIncludes

//## begin module%3F867D4403B9.includes preserve=yes
//## end module%3F867D4403B9.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cRemoteBridge
#include "System/Channel/cRemoteBridge.h"
//## begin module%3F867D4403B9.additionalDeclarations preserve=yes
//## end module%3F867D4403B9.additionalDeclarations


// Class cRemoteBridge 





cRemoteBridge::cRemoteBridge()
  //## begin cRemoteBridge::cRemoteBridge%.hasinit preserve=no
      : _RemoteChannel(NULL), _Process(NULL)
  //## end cRemoteBridge::cRemoteBridge%.hasinit
  //## begin cRemoteBridge::cRemoteBridge%.initialization preserve=yes
  //## end cRemoteBridge::cRemoteBridge%.initialization
{
  //## begin cRemoteBridge::cRemoteBridge%.body preserve=yes
_ASSERT_UNCOND
  //## end cRemoteBridge::cRemoteBridge%.body
}

cRemoteBridge::cRemoteBridge(const cRemoteBridge &right)
  //## begin cRemoteBridge::cRemoteBridge%copy.hasinit preserve=no
      : _RemoteChannel(NULL), _Process(NULL)
  //## end cRemoteBridge::cRemoteBridge%copy.hasinit
  //## begin cRemoteBridge::cRemoteBridge%copy.initialization preserve=yes
  //## end cRemoteBridge::cRemoteBridge%copy.initialization
{
  //## begin cRemoteBridge::cRemoteBridge%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cRemoteBridge::cRemoteBridge%copy.body
}

cRemoteBridge::cRemoteBridge (CONST_STRING_T channel_name, cSHProcess *process, CONST_STRING_T remote_channel_name)
  //## begin cRemoteBridge::cRemoteBridge%1065778440.hasinit preserve=no
      : _RemoteChannel(NULL), _Process(NULL)
  //## end cRemoteBridge::cRemoteBridge%1065778440.hasinit
  //## begin cRemoteBridge::cRemoteBridge%1065778440.initialization preserve=yes
  , cChannel(channel_name)
  //## end cRemoteBridge::cRemoteBridge%1065778440.initialization
{
  //## begin cRemoteBridge::cRemoteBridge%1065778440.body preserve=yes
   _Process = process;
   _Name = channel_name;
   if (remote_channel_name != NULL) {
      _RemoteChannelName = remote_channel_name;
   } else {
      _RemoteChannelName = _Name;
   }
  //## end cRemoteBridge::cRemoteBridge%1065778440.body
}


cRemoteBridge::~cRemoteBridge()
{
  //## begin cRemoteBridge::~cRemoteBridge%.body preserve=yes
  //## end cRemoteBridge::~cRemoteBridge%.body
}



//## Other Operations (implementation)
void cRemoteBridge::Connect (cAdapter *adapter)
{
  //## begin cRemoteBridge::Connect%1065778449.body preserve=yes
   if (_RemoteChannel == NULL) {
      InfoPrintf("ro remote channel named %s: unable to connect\n", _RemoteChannelName.c_str());
      if (!_Listening) Listen();
      _PendingAdapters.Add(adapter);
   } else {
      _RemoteChannel->Connect(adapter);
   }
  //## end cRemoteBridge::Connect%1065778449.body
}

INT_T cRemoteBridge::MainFunc (void *extra)
{
  //## begin cRemoteBridge::MainFunc%1065778448.body preserve=yes
MAINFUNC_PROLOG(_Name.c_str())
   while (Active()) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      if (_RemoteChannel == NULL) {
         _RemoteChannel = _Process->Channel(_RemoteChannelName.c_str());
         if (_RemoteChannel != NULL) {
            ConnectPending();
            if (_Listening) Listen();
         }
      }
      if (_RemoteChannel == NULL) {
         InfoPrintf("no remote channel named %s\n", _RemoteChannelName.c_str());
      }
      cSystemUtils::Suspend(1000);
MAINFUNC_LOOP_EPILOG
   }
   return 0;
MAINFUNC_EPILOG
  //## end cRemoteBridge::MainFunc%1065778448.body
}

void cRemoteBridge::Listen ()
{
  //## begin cRemoteBridge::Listen%1065778442.body preserve=yes
   _Listening = true;
   if (_RemoteChannel == NULL) {
      ErrorPrintf("No remote channel named %s: unable to listen\n", _RemoteChannelName.c_str());
   } else {
      _RemoteChannel->Listen();
   }
  //## end cRemoteBridge::Listen%1065778442.body
}

void cRemoteBridge::StopListen ()
{
  //## begin cRemoteBridge::StopListen%1065778443.body preserve=yes
   if (_RemoteChannel == NULL) {
      ErrorPrintf("No remote channel named %s: unable to listen\n", _RemoteChannelName.c_str());
   } else {
      _RemoteChannel->StopListen();
   }
  //## end cRemoteBridge::StopListen%1065778443.body
}

void cRemoteBridge::Send (cTransientObject *object)
{
  //## begin cRemoteBridge::Send%1065778444.body preserve=yes
   if (_RemoteChannel == NULL) {
      ErrorPrintf("No remote channel named %s: unable to send\n", _RemoteChannelName.c_str());
      cSystemUtils::Suspend(100);
   } else {
      _RemoteChannel->Send(object);
   }
  //## end cRemoteBridge::Send%1065778444.body
}

void cRemoteBridge::ConnectPending ()
{
  //## begin cRemoteBridge::ConnectPending%1065778450.body preserve=yes
   cPtrList::cConstIterator i = _PendingAdapters.Begin();
   if (i.First()) {
      do {
         cAdapter * adapter = (cAdapter*)i.Ptr();
         if (adapter != NULL) {
            Connect(adapter);
         }
      } while (i.Next());
   }
   _PendingAdapters.Clear();
  //## end cRemoteBridge::ConnectPending%1065778450.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cRemoteBridge::get_RemoteChannelName () const
{
  //## begin cRemoteBridge::get_RemoteChannelName%3F8693B70128.get preserve=no
  return _RemoteChannelName;
  //## end cRemoteBridge::get_RemoteChannelName%3F8693B70128.get
}

// Additional Declarations
  //## begin cRemoteBridge%3F867D4403B9.declarations preserve=yes
  //## end cRemoteBridge%3F867D4403B9.declarations

//## begin module%3F867D4403B9.epilog preserve=yes
//## end module%3F867D4403B9.epilog
