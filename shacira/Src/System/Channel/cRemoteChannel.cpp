//## begin module%3FFE7F5901E4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FFE7F5901E4.cm

//## begin module%3FFE7F5901E4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FFE7F5901E4.cp

//## Module: cRemoteChannel%3FFE7F5901E4; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cRemoteChannel.cpp

//## begin module%3FFE7F5901E4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FFE7F5901E4.additionalIncludes

//## begin module%3FFE7F5901E4.includes preserve=yes
//## end module%3FFE7F5901E4.includes

// cRemoteChannel
#include "System/Channel/cRemoteChannel.h"
// cChannelProxy
#include "System/Channel/cChannelProxy.h"
//## begin module%3FFE7F5901E4.additionalDeclarations preserve=yes
//## end module%3FFE7F5901E4.additionalDeclarations


// Class cRemoteChannel 


cRemoteChannel::cRemoteChannel()
  //## begin cRemoteChannel::cRemoteChannel%.hasinit preserve=no
      : _Proxy(NULL)
  //## end cRemoteChannel::cRemoteChannel%.hasinit
  //## begin cRemoteChannel::cRemoteChannel%.initialization preserve=yes
  //## end cRemoteChannel::cRemoteChannel%.initialization
{
  //## begin cRemoteChannel::cRemoteChannel%.body preserve=yes
_ASSERT_UNCOND
  //## end cRemoteChannel::cRemoteChannel%.body
}

cRemoteChannel::cRemoteChannel(const cRemoteChannel &right)
  //## begin cRemoteChannel::cRemoteChannel%copy.hasinit preserve=no
      : _Proxy(NULL)
  //## end cRemoteChannel::cRemoteChannel%copy.hasinit
  //## begin cRemoteChannel::cRemoteChannel%copy.initialization preserve=yes
  //## end cRemoteChannel::cRemoteChannel%copy.initialization
{
  //## begin cRemoteChannel::cRemoteChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cRemoteChannel::cRemoteChannel%copy.body
}

cRemoteChannel::cRemoteChannel (CONST_STRING_T channel_name, cChannelProxy *proxy)
  //## begin cRemoteChannel::cRemoteChannel%1073642249.hasinit preserve=no
      : _Proxy(NULL)
  //## end cRemoteChannel::cRemoteChannel%1073642249.hasinit
  //## begin cRemoteChannel::cRemoteChannel%1073642249.initialization preserve=yes
  , cChannel(channel_name)
  //## end cRemoteChannel::cRemoteChannel%1073642249.initialization
{
  //## begin cRemoteChannel::cRemoteChannel%1073642249.body preserve=yes
   _Proxy = proxy;
  //## end cRemoteChannel::cRemoteChannel%1073642249.body
}


cRemoteChannel::~cRemoteChannel()
{
  //## begin cRemoteChannel::~cRemoteChannel%.body preserve=yes
  //## end cRemoteChannel::~cRemoteChannel%.body
}


// Additional Declarations
  //## begin cRemoteChannel%3FFE7F5901E4.declarations preserve=yes
  //## end cRemoteChannel%3FFE7F5901E4.declarations

//## begin module%3FFE7F5901E4.epilog preserve=yes
//## end module%3FFE7F5901E4.epilog
