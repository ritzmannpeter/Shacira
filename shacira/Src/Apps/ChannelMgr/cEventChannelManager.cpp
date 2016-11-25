//## begin module%3C502485009A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C502485009A.cm

//## begin module%3C502485009A.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3C502485009A.cp

//## Module: cEventChannelManager%3C502485009A; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Apps\ChannelMgr\cEventChannelManager.cpp

//## begin module%3C502485009A.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C502485009A.additionalIncludes

//## begin module%3C502485009A.includes preserve=yes
//## end module%3C502485009A.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cProxySender
#include "System/Comm/cProxySender.h"
// cChannelProxy
#include "System/Channel/cChannelProxy.h"
// cBroker
#include "Orb/cBroker.h"
// cEventChannelWrapper
#include "Apps/ChannelMgr/cEventChannelWrapper.h"
// cEventChannelManager
#include "Apps/ChannelMgr/cEventChannelManager.h"
// cWrapperFactory
#include "Apps/ChannelMgr/cWrapperFactory.h"
//## begin module%3C502485009A.additionalDeclarations preserve=yes
//## end module%3C502485009A.additionalDeclarations


// Class cEventChannelManager 


cEventChannelManager::cEventChannelManager()
  //## begin cEventChannelManager::cEventChannelManager%.hasinit preserve=no
  //## end cEventChannelManager::cEventChannelManager%.hasinit
  //## begin cEventChannelManager::cEventChannelManager%.initialization preserve=yes
  //## end cEventChannelManager::cEventChannelManager%.initialization
{
  //## begin cEventChannelManager::cEventChannelManager%.body preserve=yes
  //## end cEventChannelManager::cEventChannelManager%.body
}

cEventChannelManager::cEventChannelManager(const cEventChannelManager &right)
  //## begin cEventChannelManager::cEventChannelManager%copy.hasinit preserve=no
  //## end cEventChannelManager::cEventChannelManager%copy.hasinit
  //## begin cEventChannelManager::cEventChannelManager%copy.initialization preserve=yes
  //## end cEventChannelManager::cEventChannelManager%copy.initialization
{
  //## begin cEventChannelManager::cEventChannelManager%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEventChannelManager::cEventChannelManager%copy.body
}

cEventChannelManager::cEventChannelManager (cConfigurationObject *config_obj)
  //## begin cEventChannelManager::cEventChannelManager%1011885582.hasinit preserve=no
  //## end cEventChannelManager::cEventChannelManager%1011885582.hasinit
  //## begin cEventChannelManager::cEventChannelManager%1011885582.initialization preserve=yes
  : cSHProcess(config_obj)
  //## end cEventChannelManager::cEventChannelManager%1011885582.initialization
{
  //## begin cEventChannelManager::cEventChannelManager%1011885582.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   CONFOBJ_VECTOR_T event_channels;
   int size = config_obj->PropertyValue("EventChannels", event_channels);
   for (int i=0; i<size; i++) {
      cConfigurationObject * channel_obj = event_channels[i];
      cEventChannelWrapper * wrapper = cWrapperFactory::CreateWrapper(this, channel_obj);
      _Wrappers[wrapper->get_ThreadName().c_str()] = wrapper;
   }
  //## end cEventChannelManager::cEventChannelManager%1011885582.body
}


cEventChannelManager::~cEventChannelManager()
{
  //## begin cEventChannelManager::~cEventChannelManager%.body preserve=yes
   ShutDown();
   std::map<STRING_T,cEventChannelWrapper*>::const_iterator i = _Wrappers.begin();
   while (i != _Wrappers.end()) {
      cEventChannelWrapper * wrapper = (*i).second;
      DELETE_OBJECT(cEventChannelWrapper, wrapper)
      i++;
   }
  //## end cEventChannelManager::~cEventChannelManager%.body
}



//## Other Operations (implementation)
void cEventChannelManager::OnStartUp ()
{
  //## begin cEventChannelManager::OnStartUp%1037369514.body preserve=yes
   std::map<STRING_T,cEventChannelWrapper*>::const_iterator i = _Wrappers.begin();
   while (i != _Wrappers.end()) {
      cEventChannelWrapper * wrapper = (*i).second;
      wrapper->StartUp();
      i++;
   }
  //## end cEventChannelManager::OnStartUp%1037369514.body
}

void cEventChannelManager::OnShutDown ()
{
  //## begin cEventChannelManager::OnShutDown%1037369516.body preserve=yes
   std::map<STRING_T,cEventChannelWrapper*>::const_iterator i = _Wrappers.begin();
   while (i != _Wrappers.end()) {
      cEventChannelWrapper * wrapper = (*i).second;
      wrapper->ShutDown();
      i++;
   }
  //## end cEventChannelManager::OnShutDown%1037369516.body
}

// Additional Declarations
  //## begin cEventChannelManager%3C502485009A.declarations preserve=yes
  //## end cEventChannelManager%3C502485009A.declarations

//## begin module%3C502485009A.epilog preserve=yes
//## end module%3C502485009A.epilog
