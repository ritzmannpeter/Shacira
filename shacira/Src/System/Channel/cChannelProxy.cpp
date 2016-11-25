//## begin module%3AF294560295.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AF294560295.cm

//## begin module%3AF294560295.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AF294560295.cp

//## Module: cChannelProxy%3AF294560295; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cChannelProxy.cpp

//## begin module%3AF294560295.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AF294560295.additionalIncludes

//## begin module%3AF294560295.includes preserve=yes
//## end module%3AF294560295.includes

// eb_sema
#include "base/eb_sema.hpp"
// cChannelProxy
#include "System/Channel/cChannelProxy.h"
//## begin module%3AF294560295.additionalDeclarations preserve=yes
//## end module%3AF294560295.additionalDeclarations


// Class cChannelProxy 




cChannelProxy::cChannelProxy()
  //## begin cChannelProxy::cChannelProxy%.hasinit preserve=no
  //## end cChannelProxy::cChannelProxy%.hasinit
  //## begin cChannelProxy::cChannelProxy%.initialization preserve=yes
  //## end cChannelProxy::cChannelProxy%.initialization
{
  //## begin cChannelProxy::cChannelProxy%.body preserve=yes
  //## end cChannelProxy::cChannelProxy%.body
}

cChannelProxy::cChannelProxy(const cChannelProxy &right)
  //## begin cChannelProxy::cChannelProxy%copy.hasinit preserve=no
  //## end cChannelProxy::cChannelProxy%copy.hasinit
  //## begin cChannelProxy::cChannelProxy%copy.initialization preserve=yes
  //## end cChannelProxy::cChannelProxy%copy.initialization
{
  //## begin cChannelProxy::cChannelProxy%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cChannelProxy::cChannelProxy%copy.body
}


cChannelProxy::~cChannelProxy()
{
  //## begin cChannelProxy::~cChannelProxy%.body preserve=yes
  //## end cChannelProxy::~cChannelProxy%.body
}



//## Other Operations (implementation)
void cChannelProxy::Object (cTransientObject *object)
{
  //## begin cChannelProxy::Object%1054547845.body preserve=yes
   cPtrList::cConstIterator i = _Channels.Begin();
   if (i.First()) {
      do {
         cChannel * channel = (cChannel*)i.Ptr();
         if (channel != NULL) {
            channel->Object(object);
         }
      } while (i.Next());
   }
  //## end cChannelProxy::Object%1054547845.body
}

void cChannelProxy::RegisterChannel (cChannel *channel)
{
  //## begin cChannelProxy::RegisterChannel%1065773702.body preserve=yes
   _Channels.Add(channel);
  //## end cChannelProxy::RegisterChannel%1065773702.body
}

// Additional Declarations
  //## begin cChannelProxy%3AF294560295.declarations preserve=yes
  //## end cChannelProxy%3AF294560295.declarations

//## begin module%3AF294560295.epilog preserve=yes
//## end module%3AF294560295.epilog
