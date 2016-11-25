//## begin module%3DCAA0A700C9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DCAA0A700C9.cm

//## begin module%3DCAA0A700C9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DCAA0A700C9.cp

//## Module: cCosEventChannelProxy%3DCAA0A700C9; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Orb\cCosEventChannelProxy.cpp

//## begin module%3DCAA0A700C9.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DCAA0A700C9.additionalIncludes

//## begin module%3DCAA0A700C9.includes preserve=yes
//## end module%3DCAA0A700C9.includes

// cCosEventChannelProxy
#include "Orb/cCosEventChannelProxy.h"
// cBroker
#include "Orb/cBroker.h"
//## begin module%3DCAA0A700C9.additionalDeclarations preserve=yes

#include "System/cStringUtils.h"

class PushSupplierImpl : virtual public CosEventComm::_sk_PushSupplier
{
public:
   PushSupplierImpl(cCosEventChannelProxy * channel, const char* objName=NULL)
   {
      _alive = 1;
      _ChannelProxy = channel;
   }
   void disconnect_push_supplier()
   {
      ErrorPrintf("push supplier disconnect\n");
      _alive = 0;
   }
   CORBA::Boolean Alive()
   {
      return _alive;
   }
private:
   cCosEventChannelProxy * _ChannelProxy;
   CORBA::Boolean _alive;
};

class PushConsumerImpl : virtual public CosEventComm::_sk_PushConsumer
{
public:
   PushConsumerImpl(cCosEventChannelProxy * channel, const char* objName=NULL)
   {
      _ChannelProxy = channel;
   }
   void push(const CORBA::Any& any)
   {
      _ChannelProxy->PushEvent(any);
   }
   void disconnect_push_consumer()
   {
      ErrorPrintf("push consumer disconnect\n");
   }
private:
   cCosEventChannelProxy * _ChannelProxy;
};

//## end module%3DCAA0A700C9.additionalDeclarations


// Class cCosEventChannelProxy 

cCosEventChannelProxy::cCosEventChannelProxy()
  //## begin cCosEventChannelProxy::cCosEventChannelProxy%.hasinit preserve=no
  //## end cCosEventChannelProxy::cCosEventChannelProxy%.hasinit
  //## begin cCosEventChannelProxy::cCosEventChannelProxy%.initialization preserve=yes
   : _Channel(NULL), _Supplier(NULL), _Consumer(NULL)
  //## end cCosEventChannelProxy::cCosEventChannelProxy%.initialization
{
  //## begin cCosEventChannelProxy::cCosEventChannelProxy%.body preserve=yes
   _Type = OT_COS_EVENTCHANNEL_PROXY;
  //## end cCosEventChannelProxy::cCosEventChannelProxy%.body
}

cCosEventChannelProxy::cCosEventChannelProxy(const cCosEventChannelProxy &right)
  //## begin cCosEventChannelProxy::cCosEventChannelProxy%copy.hasinit preserve=no
  //## end cCosEventChannelProxy::cCosEventChannelProxy%copy.hasinit
  //## begin cCosEventChannelProxy::cCosEventChannelProxy%copy.initialization preserve=yes
   : _Channel(NULL), _Supplier(NULL), _Consumer(NULL)
  //## end cCosEventChannelProxy::cCosEventChannelProxy%copy.initialization
{
  //## begin cCosEventChannelProxy::cCosEventChannelProxy%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCosEventChannelProxy::cCosEventChannelProxy%copy.body
}


cCosEventChannelProxy::~cCosEventChannelProxy()
{
  //## begin cCosEventChannelProxy::~cCosEventChannelProxy%.body preserve=yes
	ReleaseItf();
  //## end cCosEventChannelProxy::~cCosEventChannelProxy%.body
}



//## Other Operations (implementation)
void cCosEventChannelProxy::Update (cProxy *proxy)
{
  //## begin cCosEventChannelProxy::Update%1054547851.body preserve=yes
   if (_Type != proxy->get_Type()) return; 
   if (_ProxyName != proxy->get_ProxyName()) return; 
   if (_IOR == proxy->get_IOR()) return; 
   _Computer = proxy->get_Computer();
   _IPAddress = proxy->get_IPAddress();
   _CellName = proxy->get_CellName();
   _Object = proxy->get_Object();
   _ProcessId = proxy->get_ProcessId();
   _ProcessName = proxy->get_ProcessName();
   _IOR = proxy->get_IOR();
   SetItf();
   if (_Supplier != NULL) {
      Use();
   }
   if (_Consumer != 0) {
      Listen();
   }
  //## end cCosEventChannelProxy::Update%1054547851.body
}

BOOL_T cCosEventChannelProxy::Send (cTransientObject *object)
{
  //## begin cCosEventChannelProxy::Send%1054547844.body preserve=yes
   cObjectLock __lock__(&_ProxyMutex);
   if (_Supplier == NULL) Use();
   try {
      if (_Supplier == NULL) {
         ErrorPrintf("No supplier on channel %s available\n", _ProxyName.c_str());
         return false;
      }
      if (_Channel == NULL) {
         ErrorPrintf("No event channel %s available\n", _ProxyName.c_str());
         return false;
      }
      if (_ProxyPushConsumer == NULL) {
         ErrorPrintf("No push consumer proxy for channel %s available\n", _ProxyName.c_str());
         return false;
      }
      if (!_Supplier->Alive()) {
         ErrorPrintf("Supplier on channel %s dead\n", _ProxyName.c_str());
         return false;
      }
      STRING_T serialized_obj = object->Serialize();
      CORBA::Any any;
      any <<= serialized_obj.c_str();
      CORBA_ITF_PROLOG("CosEventChannelAdmin::ProxyPushConsumer::push", _ProxyPushConsumer)
//InfoPrintf("sending: %s\n", serialized_obj.c_str());
      _ProxyPushConsumer->push(any);
      CORBA_ITF_EPILOG
      return true;
   } catch (cError & e) {
      ErrorPrintf("%s\n", (const char *)e);
      return false;
   } catch (...) {
      ErrorPrintf("Unhandled exception in cCosEventChannelProxy::Send\n");
      return false;
   }
  //## end cCosEventChannelProxy::Send%1054547844.body
}

BOOL_T cCosEventChannelProxy::Listen ()
{
  //## begin cCosEventChannelProxy::Listen%1054632833.body preserve=yes
   if (_Channel == NULL) SetItf();
   if (_Channel == NULL) throw cError(EVENT_CHANNEL_NO_CHANNEL, 0, _ProxyName.c_str());
   _Consumer = new PushConsumerImpl(this);
const char * msg = "basic object adapter is no more supported activation via portable adapter is required";
#pragma message(__LOC__ "basic object adapter is no more supported activation via portable adapter is required")
ErrorPrintf("%s\n", msg);
//   _Consumer->_obj_is_ready(cBroker::Boa());
   _ForConsumer = (*_Channel)->for_consumers();
   _ProxyPushSupplier = _ForConsumer->obtain_push_supplier();
   _ProxyPushSupplier->connect_push_consumer(_Consumer->_this());
   InfoPrintf("Listening to %s\n", _ProxyName.c_str());
   return true;
  //## end cCosEventChannelProxy::Listen%1054632833.body
}

void cCosEventChannelProxy::PushEvent (const CORBA::Any  &any)
{
  //## begin cCosEventChannelProxy::PushEvent%1054632841.body preserve=yes
   try {
      CORBA::StringValue * corba_string;
      if (any >>= corba_string) {
         STRING_T obj_header;
         STRING_T obj_data;
         cTransientObject * object = cTransientObject::Parse(corba_string->_value());
         if (object != NULL) {
            Object(object);
            RELEASE_OBJECT(object)
         } else {
            char msg[512] = {0};
            memcpy(msg, corba_string->_value(), _MIN_(strlen(corba_string->_value()), sizeof(msg)-1));
            ErrorPrintf("Unable to construct proxy %s in cCosEventChannelProxy::PushEvent\n", msg);
         }
      }
   } catch (cError & e) {
      ErrorPrintf("%s\n", (const char *)e);
   } catch (...) {
      ErrorPrintf("Unhandled exception in cCosEventChannelProxy::PushEvent\n");
   }
  //## end cCosEventChannelProxy::PushEvent%1054632841.body
}

BOOL_T cCosEventChannelProxy::Use ()
{
  //## begin cCosEventChannelProxy::Use%1054632843.body preserve=yes
   if (_Channel == NULL) SetItf();
   if (_Channel == NULL) throw cError(EVENT_CHANNEL_NO_CHANNEL, 0, _ProxyName.c_str());
   _Supplier = new PushSupplierImpl(this);
const char * msg = "basic object adapter is no more supported activation via portable adapter is required";
#pragma message(__LOC__ "basic object adapter is no more supported activation via portable adapter is required")
ErrorPrintf("%s\n", msg);
//   _Supplier->_obj_is_ready(cBroker::Boa());
   _ForSupplier = (*_Channel)->for_suppliers();
   _ProxyPushConsumer = _ForSupplier->obtain_push_consumer();
   _ProxyPushConsumer->connect_push_supplier(_Supplier->_this());
   InfoPrintf("Using %s\n", _ProxyName.c_str());
   return true;
  //## end cCosEventChannelProxy::Use%1054632843.body
}

void cCosEventChannelProxy::SetItf ()
{
  //## begin cCosEventChannelProxy::SetItf%1054632837.body preserve=yes
   cObjectLock __lock__(&_ProxyMutex);
CORBA_BIND_PROLOG("iEventChannel", _IOR.c_str())
   CORBA::Object_var obj = cBroker::Orb()->string_to_object(_IOR.c_str());
   _Channel = new CosEventChannelAdmin::EventChannel_var;
   *_Channel = CosEventChannelAdmin::EventChannel::_narrow(obj);
CORBA_BIND_EPILOG
   InfoPrintf("New interface to %s\n", _ProxyName.c_str());
  //## end cCosEventChannelProxy::SetItf%1054632837.body
}

void cCosEventChannelProxy::ReleaseItf ()
{
  //## begin cCosEventChannelProxy::ReleaseItf%1054632838.body preserve=yes
   cObjectLock __lock__(&_ProxyMutex);
   if (_Supplier != NULL) {
      InfoPrintf("Releasing supplier of %s\n", _ProxyName.c_str());
//      _ForSupplier->_release();
      _ForSupplier = NULL;
//      _ProxyPushConsumer->_release();
      _ProxyPushConsumer = NULL;
const char * msg = "basic object adapter is no more supported activation via portable adapter is required";
#pragma message(__LOC__ "basic object adapter is no more supported activation via portable adapter is required")
ErrorPrintf("%s\n", msg);
//      cBroker::Boa()->deactivate_obj((CORBA::Object*)_Supplier);
	  _Supplier->_dispose();
      _Supplier = NULL;
      InfoPrintf("Supplier of %s released\n", _ProxyName.c_str());
   }
   if (_Consumer != NULL) {
      InfoPrintf("Releasing consumer of %s\n", _ProxyName.c_str());
//      _ForConsumer->_release();
      _ForConsumer = NULL;
//      _ProxyPushSupplier->_release();
      _ProxyPushSupplier = NULL;
const char * msg = "basic object adapter is no more supported activation via portable adapter is required";
#pragma message(__LOC__ "basic object adapter is no more supported activation via portable adapter is required")
ErrorPrintf("%s\n", msg);
//      cBroker::Boa()->deactivate_obj((CORBA::Object*)_Consumer);
	  _Consumer->_dispose();
      _Consumer = NULL;
      InfoPrintf("Consumer of %s released\n", _ProxyName.c_str());
   }
   if (_Channel != NULL) {
      InfoPrintf("Releasing channel %s\n", _ProxyName.c_str());
      _Channel = NULL;
      InfoPrintf("Channel %s released\n", _ProxyName.c_str());
   }
  //## end cCosEventChannelProxy::ReleaseItf%1054632838.body
}

// Additional Declarations
  //## begin cCosEventChannelProxy%3DCAA0A700C9.declarations preserve=yes
  //## end cCosEventChannelProxy%3DCAA0A700C9.declarations

//## begin module%3DCAA0A700C9.epilog preserve=yes
//## end module%3DCAA0A700C9.epilog
