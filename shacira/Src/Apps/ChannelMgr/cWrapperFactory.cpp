//## begin module%3DD8DFED0147.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD8DFED0147.cm

//## begin module%3DD8DFED0147.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3DD8DFED0147.cp

//## Module: cWrapperFactory%3DD8DFED0147; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Apps\ChannelMgr\cWrapperFactory.cpp

//## begin module%3DD8DFED0147.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DD8DFED0147.additionalIncludes

//## begin module%3DD8DFED0147.includes preserve=yes
//## end module%3DD8DFED0147.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cEventChannelWrapper
#include "Apps/ChannelMgr/cEventChannelWrapper.h"
// cEventChannelManager
#include "Apps/ChannelMgr/cEventChannelManager.h"
// cVbrokerEventChannelWrapper
#include "Apps/ChannelMgr/cVbrokerEventChannelWrapper.h"
// cWrapperFactory
#include "Apps/ChannelMgr/cWrapperFactory.h"
//## begin module%3DD8DFED0147.additionalDeclarations preserve=yes
//## end module%3DD8DFED0147.additionalDeclarations


// Class cWrapperFactory 

cWrapperFactory::cWrapperFactory()
  //## begin cWrapperFactory::cWrapperFactory%.hasinit preserve=no
  //## end cWrapperFactory::cWrapperFactory%.hasinit
  //## begin cWrapperFactory::cWrapperFactory%.initialization preserve=yes
  //## end cWrapperFactory::cWrapperFactory%.initialization
{
  //## begin cWrapperFactory::cWrapperFactory%.body preserve=yes
  //## end cWrapperFactory::cWrapperFactory%.body
}

cWrapperFactory::cWrapperFactory(const cWrapperFactory &right)
  //## begin cWrapperFactory::cWrapperFactory%copy.hasinit preserve=no
  //## end cWrapperFactory::cWrapperFactory%copy.hasinit
  //## begin cWrapperFactory::cWrapperFactory%copy.initialization preserve=yes
  //## end cWrapperFactory::cWrapperFactory%copy.initialization
{
  //## begin cWrapperFactory::cWrapperFactory%copy.body preserve=yes
  //## end cWrapperFactory::cWrapperFactory%copy.body
}


cWrapperFactory::~cWrapperFactory()
{
  //## begin cWrapperFactory::~cWrapperFactory%.body preserve=yes
  //## end cWrapperFactory::~cWrapperFactory%.body
}



//## Other Operations (implementation)
cEventChannelWrapper * cWrapperFactory::CreateWrapper (cEventChannelManager *process, cConfigurationObject *config_obj)
{
  //## begin cWrapperFactory::CreateWrapper%1037621190.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   cEventChannelWrapper * wrapper = NULL;
   STRING_T event_channel_type = config_obj->PropertyValue("ChannelType", "", true);
   if (IDENTIFIER_EQUAL(event_channel_type.c_str(), "COS_EVENT_COMM_VISIBROKER")) {
      wrapper = new cVbrokerEventChannelWrapper(process, config_obj);
   } else {
      throw cError(FACTORY_INVALID_VALUE, 0, event_channel_type.c_str(), "cEventChannelWrapper");
   }
   return wrapper;
  //## end cWrapperFactory::CreateWrapper%1037621190.body
}

// Additional Declarations
  //## begin cWrapperFactory%3DD8DFED0147.declarations preserve=yes
  //## end cWrapperFactory%3DD8DFED0147.declarations

//## begin module%3DD8DFED0147.epilog preserve=yes
//## end module%3DD8DFED0147.epilog
