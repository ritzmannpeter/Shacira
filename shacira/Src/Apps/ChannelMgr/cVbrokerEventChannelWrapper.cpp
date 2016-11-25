//## begin module%3DCAB8D30302.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DCAB8D30302.cm

//## begin module%3DCAB8D30302.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DCAB8D30302.cp

//## Module: cVbrokerEventChannelWrapper%3DCAB8D30302; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Apps\ChannelMgr\cVbrokerEventChannelWrapper.cpp

//## begin module%3DCAB8D30302.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DCAB8D30302.additionalIncludes

//## begin module%3DCAB8D30302.includes preserve=yes

#include "Orb/CorbaDefinitions.h"

//## end module%3DCAB8D30302.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cCosEventChannelProxy
#include "Orb/cCosEventChannelProxy.h"
// cBroker
#include "Orb/cBroker.h"
// cEventChannelManager
#include "Apps/ChannelMgr/cEventChannelManager.h"
// cVbrokerEventChannelWrapper
#include "Apps/ChannelMgr/cVbrokerEventChannelWrapper.h"
//## begin module%3DCAB8D30302.additionalDeclarations preserve=yes
//## end module%3DCAB8D30302.additionalDeclarations


// Class cVbrokerEventChannelWrapper 

cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper()
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%.hasinit preserve=no
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%.hasinit
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%.initialization preserve=yes
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%.initialization
{
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%.body preserve=yes
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%.body
}

cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper(const cVbrokerEventChannelWrapper &right)
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%copy.hasinit preserve=no
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%copy.hasinit
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%copy.initialization preserve=yes
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%copy.initialization
{
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%copy.body
}

cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper (cEventChannelManager *process, cConfigurationObject *config_obj)
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%1036694775.hasinit preserve=no
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%1036694775.hasinit
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%1036694775.initialization preserve=yes
  : cEventChannelWrapper(process, config_obj)
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%1036694775.initialization
{
  //## begin cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%1036694775.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   if (_ChannelType == COS_EVENT_COMM_VISIBROKER) {
      if (_ProcessName.size() == 0) _ProcessName = "channel.exe";
      _ProcessArgs = _ThreadName.c_str();
   }
  //## end cVbrokerEventChannelWrapper::cVbrokerEventChannelWrapper%1036694775.body
}


cVbrokerEventChannelWrapper::~cVbrokerEventChannelWrapper()
{
  //## begin cVbrokerEventChannelWrapper::~cVbrokerEventChannelWrapper%.body preserve=yes
   StopProcess();
  //## end cVbrokerEventChannelWrapper::~cVbrokerEventChannelWrapper%.body
}



//## Other Operations (implementation)
INT_T cVbrokerEventChannelWrapper::MainFunc (void *extra)
{
  //## begin cVbrokerEventChannelWrapper::MainFunc%1037640488.body preserve=yes
MAINFUNC_PROLOG(_ThreadName.c_str())
   // Corba-Interface-Object
   StartChannel();
   while (!_Terminated) {
MAINFUNC_LOOP_PROLOG(_ThreadName.c_str())
      if (!_Terminated) cSystemUtils::Suspend(_IdleTime);
MAINFUNC_LOOP_EPILOG
   }
   StopChannel();
   return 0;
MAINFUNC_EPILOG
  //## end cVbrokerEventChannelWrapper::MainFunc%1037640488.body
}

void cVbrokerEventChannelWrapper::AddServices ()
{
  //## begin cVbrokerEventChannelWrapper::AddServices%1047632192.body preserve=yes
   cCosEventChannelProxy proxy;
   proxy.set_ProxyName(_ChannelName.c_str());
	proxy.set_Computer(cSystemUtils::ComputerName());
	proxy.set_IPAddress(cSystemUtils::IPAddress());
	proxy.set_ProcessId(cSystemUtils::ProcessId());
   proxy.set_IOR(_IOR);
	STRING_T serialized_proxy = proxy.Serialize();
	_Process->AddService(serialized_proxy.c_str());
  //## end cVbrokerEventChannelWrapper::AddServices%1047632192.body
}

void cVbrokerEventChannelWrapper::StartChannel ()
{
  //## begin cVbrokerEventChannelWrapper::StartChannel%1047632193.body preserve=yes
   StartProcess();
   BOOL_T success = false;
#ifdef __VISIBROKER__
   CosEventChannelAdmin::EventChannel_var channel;
   while (success == false && !_Terminated) {
      try {
         cSystemUtils::Suspend(1000);
         InfoPrintf("Trying to contact event channel %s ...\n", _ThreadName.c_str());
         channel = CosEventChannelAdmin::EventChannel::_bind(_ThreadName.c_str());
         success = true;
      } catch (CORBA::Exception & e) {
         success = false;
      } catch (...) {
         success = false;
      }
   }
#elif defined (__OMNIORB__)
   CosEventChannelAdmin::EventChannel_var channel;
   while (success == false && !_Terminated) {
      try {
         cSystemUtils::Suspend(1000);
         InfoPrintf("Trying to contact event channel %s ...\n", _Name.c_str());
         CORBA::Object_var obj = cBroker::Orb()->resolve_initial_references(_ChannelName.c_str());
         channel = CosEventChannelAdmin::EventChannel::_narrow(obj);
         


//         channel = CosEventChannelAdmin::EventChannel::_bind(_Name.c_str());
         success = true;
      } catch (CORBA::Exception & e) {
         success = false;
      } catch (...) {
         success = false;
      }
   }
#endif
   if (success) {
#ifdef __VISIBROKER__
      IOP::IOR * ior = VISUtil::to_ior(channel);
      STRING_T iors = VISUtil::to_string(*ior);
      _IOR = iors.c_str();
#elif defined(__OMNIORB__)
#endif
      _Active = true;
   } else {
      if (!_Terminated) {
         StopProcess();
         throw cError(CHANNEL_WRAPPER_NO_CONTACT, 0, _ThreadName.c_str());
      }
   }
   AddServices();
  //## end cVbrokerEventChannelWrapper::StartChannel%1047632193.body
}

void cVbrokerEventChannelWrapper::StopChannel ()
{
  //## begin cVbrokerEventChannelWrapper::StopChannel%1047632194.body preserve=yes
   _IOR = "";
   _Active = false;
   StopProcess();
  //## end cVbrokerEventChannelWrapper::StopChannel%1047632194.body
}

// Additional Declarations
  //## begin cVbrokerEventChannelWrapper%3DCAB8D30302.declarations preserve=yes
  //## end cVbrokerEventChannelWrapper%3DCAB8D30302.declarations

//## begin module%3DCAB8D30302.epilog preserve=yes
//## end module%3DCAB8D30302.epilog
