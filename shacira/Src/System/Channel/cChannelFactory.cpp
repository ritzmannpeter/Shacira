//## begin module%3FBA3CF100DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FBA3CF100DA.cm

//## begin module%3FBA3CF100DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FBA3CF100DA.cp

//## Module: cChannelFactory%3FBA3CF100DA; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cChannelFactory.cpp

//## begin module%3FBA3CF100DA.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FBA3CF100DA.additionalIncludes

//## begin module%3FBA3CF100DA.includes preserve=yes
//## end module%3FBA3CF100DA.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cChannel
#include "System/Channel/cChannel.h"
// cChannelFactory
#include "System/Channel/cChannelFactory.h"
// cRemoteBridge
#include "System/Channel/cRemoteBridge.h"
// cCOSChannel
#include "System/Channel/cCOSChannel.h"
// cLocalChannel
#include "System/Channel/cLocalChannel.h"
//## begin module%3FBA3CF100DA.additionalDeclarations preserve=yes
//## end module%3FBA3CF100DA.additionalDeclarations


// Class cChannelFactory 

cChannelFactory::cChannelFactory()
  //## begin cChannelFactory::cChannelFactory%.hasinit preserve=no
  //## end cChannelFactory::cChannelFactory%.hasinit
  //## begin cChannelFactory::cChannelFactory%.initialization preserve=yes
  //## end cChannelFactory::cChannelFactory%.initialization
{
  //## begin cChannelFactory::cChannelFactory%.body preserve=yes
  //## end cChannelFactory::cChannelFactory%.body
}

cChannelFactory::cChannelFactory(const cChannelFactory &right)
  //## begin cChannelFactory::cChannelFactory%copy.hasinit preserve=no
  //## end cChannelFactory::cChannelFactory%copy.hasinit
  //## begin cChannelFactory::cChannelFactory%copy.initialization preserve=yes
  //## end cChannelFactory::cChannelFactory%copy.initialization
{
  //## begin cChannelFactory::cChannelFactory%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cChannelFactory::cChannelFactory%copy.body
}


cChannelFactory::~cChannelFactory()
{
  //## begin cChannelFactory::~cChannelFactory%.body preserve=yes
  //## end cChannelFactory::~cChannelFactory%.body
}



//## Other Operations (implementation)
cChannel * cChannelFactory::CreateChannel (cConfigurationObject *config_obj, cSHProcess *process, CONST_STRING_T channel_name)
{
  //## begin cChannelFactory::CreateChannel%1069152411.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   STRING_T type_name = config_obj->PropertyValue("ChannelType", "", true);
   STRING_T _channel_name = channel_name;
   cChannel * channel = NULL;
   if (IDENTIFIER_EQUAL(type_name.c_str(), "LocalChannel")) {
      channel = new cLocalChannel(channel_name);
   } else if (IDENTIFIER_EQUAL(type_name.c_str(), "RemoteBridge")) {
      _channel_name = config_obj->PropertyValue("RemoteChannelName", channel_name);
      channel = new cRemoteBridge(_channel_name.c_str(), process);
   } else {
      channel = CreateExternal(type_name.c_str(), config_obj, process);
   }
   return channel;
  //## end cChannelFactory::CreateChannel%1069152411.body
}

cChannel * cChannelFactory::CreateExternal (CONST_STRING_T source, cConfigurationObject *config_obj, cStaticObject *related_object)
{
  //## begin cChannelFactory::CreateExternal%1074705361.body preserve=yes
_ASSERT_UNCOND
   return NULL;
#ifdef lassma
   cChannel * channel = (cChannel*)cObjectFactory::CreateObject(source, config_obj, related_object);
   return channel;
#endif
  //## end cChannelFactory::CreateExternal%1074705361.body
}

// Additional Declarations
  //## begin cChannelFactory%3FBA3CF100DA.declarations preserve=yes
  //## end cChannelFactory%3FBA3CF100DA.declarations

//## begin module%3FBA3CF100DA.epilog preserve=yes
//## end module%3FBA3CF100DA.epilog
