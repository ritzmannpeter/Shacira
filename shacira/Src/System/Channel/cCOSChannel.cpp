//## begin module%3F85593E00AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F85593E00AB.cm

//## begin module%3F85593E00AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F85593E00AB.cp

//## Module: cCOSChannel%3F85593E00AB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cCOSChannel.cpp

//## begin module%3F85593E00AB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F85593E00AB.additionalIncludes

//## begin module%3F85593E00AB.includes preserve=yes
//## end module%3F85593E00AB.includes

// cCOSChannel
#include "System/Channel/cCOSChannel.h"
//## begin module%3F85593E00AB.additionalDeclarations preserve=yes
//## end module%3F85593E00AB.additionalDeclarations


// Class cCOSChannel 

cCOSChannel::cCOSChannel()
  //## begin cCOSChannel::cCOSChannel%.hasinit preserve=no
  //## end cCOSChannel::cCOSChannel%.hasinit
  //## begin cCOSChannel::cCOSChannel%.initialization preserve=yes
  //## end cCOSChannel::cCOSChannel%.initialization
{
  //## begin cCOSChannel::cCOSChannel%.body preserve=yes
_ASSERT_UNCOND
  //## end cCOSChannel::cCOSChannel%.body
}

cCOSChannel::cCOSChannel(const cCOSChannel &right)
  //## begin cCOSChannel::cCOSChannel%copy.hasinit preserve=no
  //## end cCOSChannel::cCOSChannel%copy.hasinit
  //## begin cCOSChannel::cCOSChannel%copy.initialization preserve=yes
  //## end cCOSChannel::cCOSChannel%copy.initialization
{
  //## begin cCOSChannel::cCOSChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCOSChannel::cCOSChannel%copy.body
}

cCOSChannel::cCOSChannel (CONST_STRING_T channel_name, cCosEventChannelProxy *proxy)
  //## begin cCOSChannel::cCOSChannel%1065703992.hasinit preserve=no
  //## end cCOSChannel::cCOSChannel%1065703992.hasinit
  //## begin cCOSChannel::cCOSChannel%1065703992.initialization preserve=yes
  : cRemoteChannel(channel_name, proxy)
  //## end cCOSChannel::cCOSChannel%1065703992.initialization
{
  //## begin cCOSChannel::cCOSChannel%1065703992.body preserve=yes
   _Type = "COSChannel";
  //## end cCOSChannel::cCOSChannel%1065703992.body
}


cCOSChannel::~cCOSChannel()
{
  //## begin cCOSChannel::~cCOSChannel%.body preserve=yes
  //## end cCOSChannel::~cCOSChannel%.body
}



//## Other Operations (implementation)
void cCOSChannel::Listen ()
{
  //## begin cCOSChannel::Listen%1065703997.body preserve=yes
   if (!_Listening) {
      if (_Proxy->Listen())  {
         _Proxy->RegisterChannel(this);
         _Listening = true;
      } else {
         InfoPrintf("Unable to listen to proxy for event channel %s\n", _Name.c_str());
      }
   }
  //## end cCOSChannel::Listen%1065703997.body
}

void cCOSChannel::StopListen ()
{
  //## begin cCOSChannel::StopListen%1065703998.body preserve=yes
  //## end cCOSChannel::StopListen%1065703998.body
}

void cCOSChannel::Send (cTransientObject *object)
{
  //## begin cCOSChannel::Send%1065703993.body preserve=yes
   _Proxy->Send(object);
  //## end cCOSChannel::Send%1065703993.body
}

// Additional Declarations
  //## begin cCOSChannel%3F85593E00AB.declarations preserve=yes
  //## end cCOSChannel%3F85593E00AB.declarations

//## begin module%3F85593E00AB.epilog preserve=yes
//## end module%3F85593E00AB.epilog
