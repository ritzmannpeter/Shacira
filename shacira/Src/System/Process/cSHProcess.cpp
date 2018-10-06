//## begin module%3C46E64A0182.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C46E64A0182.cm

//## begin module%3C46E64A0182.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C46E64A0182.cp

//## Module: cSHProcess%3C46E64A0182; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cSHProcess.cpp

//## begin module%3C46E64A0182.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C46E64A0182.additionalIncludes

//## begin module%3C46E64A0182.includes preserve=yes
//## end module%3C46E64A0182.includes

// cIniFile
#include "System/cIniFile.h"
// cShutDownControl
#include "System/Process/cShutDownControl.h"
// cSHProcess
#include "System/Process/cSHProcess.h"
// cRequestHandler
#include "System/Process/cRequestHandler.h"
// cTransientObject
#include "System/Objects/cTransientObject.h"
// cProxy
#include "System/Objects/cProxy.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cProxyRequester
#include "System/Comm/cProxyRequester.h"
// cProxySender
#include "System/Comm/cProxySender.h"
// cProxyReceiver
#include "System/Comm/cProxyReceiver.h"
// cContext
#include "System/Database/cContext.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cSystemUtils
#include "System/Sys/cSystemUtils.h"
// cCOSChannel
#include "System/Channel/cCOSChannel.h"
// cLocalChannel
#include "System/Channel/cLocalChannel.h"
// cChannel
#include "System/Channel/cChannel.h"
// cLocalContext
#include "Control/LocalDatabase/cLocalContext.h"
// cCorbaCellProxy
#include "Orb/cCorbaCellProxy.h"
// cRemoteContext
#include "Client/RemoteDatabase/cRemoteContext.h"
// cClients
#include "Client/ClientData/cClients.h"
//## begin module%3C46E64A0182.additionalDeclarations preserve=yes

#include "Orb/cBroker.h"
#include "System/Objects/cInfo.h"
#define WAIT_INTERVAL   200

//## end module%3C46E64A0182.additionalDeclarations


// Class cSHProcess 



























cSHProcess::cSHProcess()
  //## begin cSHProcess::cSHProcess%.hasinit preserve=no
      : _ProcessId(0), _IFType(IF_PROPRIETARY), _IsClient(true), _ShutDownControl(NULL), _EventChannel(NULL), _ProxyRequester(NULL)
  //## end cSHProcess::cSHProcess%.hasinit
  //## begin cSHProcess::cSHProcess%.initialization preserve=yes
  //## end cSHProcess::cSHProcess%.initialization
{
  //## begin cSHProcess::cSHProcess%.body preserve=yes
   _ProcessId = cSystemUtils::ProcessId();
   _Computer = cSystemUtils::ComputerName();
   _EventChannel = new cLocalChannel("Process.EventChannel");
   char name[0x100] = {0};
   SafePrintf (name, sizeof(name), "%s.%08.8d", _Computer.c_str(), _ProcessId);
   _Name = name;
  //## end cSHProcess::cSHProcess%.body
}

cSHProcess::cSHProcess(const cSHProcess &right)
  //## begin cSHProcess::cSHProcess%copy.hasinit preserve=no
      : _ProcessId(0), _IFType(IF_PROPRIETARY), _IsClient(true), _ShutDownControl(NULL), _EventChannel(NULL), _ProxyRequester(NULL)
  //## end cSHProcess::cSHProcess%copy.hasinit
  //## begin cSHProcess::cSHProcess%copy.initialization preserve=yes
  //## end cSHProcess::cSHProcess%copy.initialization
{
  //## begin cSHProcess::cSHProcess%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSHProcess::cSHProcess%copy.body
}

cSHProcess::cSHProcess (cConfigurationObject *config_obj, BOOL_T is_client)
  //## begin cSHProcess::cSHProcess%1011276236.hasinit preserve=no
      : _ProcessId(0), _IFType(IF_PROPRIETARY), _IsClient(true), _ShutDownControl(NULL), _EventChannel(NULL), _ProxyRequester(NULL)
  //## end cSHProcess::cSHProcess%1011276236.hasinit
  //## begin cSHProcess::cSHProcess%1011276236.initialization preserve=yes
  //## end cSHProcess::cSHProcess%1011276236.initialization
{
  //## begin cSHProcess::cSHProcess%1011276236.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   _IsClient = is_client;
   _Name = config_obj->get_Name();
   _IdleTime = config_obj->PropertyValue("IdleTime", _IdleTime);
   _ProcessId = cSystemUtils::ProcessId();
   _Computer = cSystemUtils::ComputerName();
   int i = 0;
#define OBSOLETE_CONNECTION_INFOS
#ifdef OBSOLETE_CONNECTION_INFOS
   int size = 0;
   CONFOBJ_VECTOR_T proxy_receiver_objs;
   size = config_obj->PropertyValue("ProxyReceiver", proxy_receiver_objs);
   for (i=0; i<size; i++) {
      cConfigurationObject * proxy_receiver_obj = proxy_receiver_objs[i];
_ASSERT_COND(proxy_receiver_obj != NULL)
      cProxyReceiver * proxy_receiver = new cProxyReceiver(proxy_receiver_obj, this);
      STRING_T name = proxy_receiver->get_Name();
      AddProxyReceiver(name.c_str(), proxy_receiver);
   }
   CONFOBJ_VECTOR_T proxy_sender_objs;
   size = config_obj->PropertyValue("ProxySender", proxy_sender_objs);
   for (i=0; i<size; i++) {
      cConfigurationObject * proxy_sender_obj = proxy_sender_objs[i];
_ASSERT_COND(proxy_sender_obj != NULL)
      cProxySender * proxy_sender = new cProxySender(proxy_sender_obj);
      STRING_T name = proxy_sender->get_Name();
      AddProxySender(name.c_str(), proxy_sender);
   }
#endif
   NUMERIC_VECTOR_T standard_ports;
   int standard_port_count = config_obj->PropertyValue("NameServiceStandardPorts", standard_ports);
   NUMERIC_VECTOR_T requester_ports;
   int requester_port_count = config_obj->PropertyValue("NameServiceRequesterPorts", requester_ports);
   if (requester_port_count > 0) {
      if (_ProxyRequester == NULL) {
         _ProxyRequester = new cProxyRequester(this, _IsClient);
         _ProxyRequester->Start();
      }
      for (i=0; i<requester_port_count; i++) {
         USHORT_T port = (USHORT_T)requester_ports[i];
         AddProxyRequest(port);
      }
   }
   if (_IsClient) {
      USHORT_T port = 0;
      for (int j=0; j<standard_port_count; j++) {
         port = (USHORT_T)standard_ports[j];
         AddRequestedPort(port);
      }
      if (_ProxyRequester != NULL) {
         STRING_VECTOR_T server_list;
         int server_count = config_obj->PropertyValue("NameServiceServers", server_list);
         STRING_T server;
         for (i=0; i<server_count; i++) {
            server = server_list[i];
            AddProxyRequest(server.c_str());
         }
      }
   } else {
      STRING_VECTOR_T standard_ips;
      int standard_ip_count = config_obj->PropertyValue("NameServiceStandardIPs", standard_ips);
      USHORT_T port = 0; STRING_T addr;
      for (i=0; i<standard_ip_count; i++) {
         addr = standard_ips[i];
         for (int j=0; j<standard_port_count; j++) {
            AddProxySender(addr.c_str(), port);
         }
      }
   }

   CONFOBJ_VECTOR_T client_context_vec;
   config_obj->PropertyValue("ClientContexts", client_context_vec);
   ULONG_T len = client_context_vec.size();
   for (ULONG_T j=0; j<len; j++) {
      cConfigurationObject * client_context_object = (cConfigurationObject*)client_context_vec[j];
      STRING_T context_name = client_context_object->get_Name();
      cLocalContext * client_context = new cLocalContext(this, client_context_object, true);
      context_name = client_context->get_Name();
      client_context->Create();
      AddContext(context_name.c_str(), client_context);
   }
   _EventChannel = new cLocalChannel("Process.EventChannel");
   _IORDirectory = config_obj->PropertyValue("IORDirectory", _IORDirectory.c_str());
   _IORDirectory = cFileSystemUtils::FullPath(_IORDirectory.c_str());
   _IORFile = cFileSystemUtils::AppendPath(_IORDirectory.c_str(), "iors.dat");
   ReadIORFile();
   if (_ProxyRequester != NULL &&
       _IsClient) {
      _ProxyRequester->Start();
   }
  //## end cSHProcess::cSHProcess%1011276236.body
}

cSHProcess::~cSHProcess()
{
  //## begin cSHProcess::~cSHProcess%.body preserve=yes
   Stop();
   PROXY_SENDER_MAP_T::const_iterator i = _ProxySenderMap.cbegin();
   while (i != _ProxySenderMap.cend()) {
      cProxySender * sender = (*i).second;
      DELETE_OBJECT(cProxySender, sender)
      i++;
   }
   PROXY_RECEIVER_MAP_T::const_iterator k = _ProxyReceiverMap.cbegin();
   while (k != _ProxyReceiverMap.cend()) {
      cProxyReceiver * proxy_receiver = (*k).second;
      DELETE_OBJECT(cProxyReceiver, proxy_receiver)
      k++;
   }
   DELETE_OBJECT(cLocalChannel, _EventChannel)
  //## end cSHProcess::~cSHProcess%.body
}



//## Other Operations (implementation)
void cSHProcess::Start ()
{
  //## begin cSHProcess::Start%1123228418.body preserve=yes
   if (_ProxyRequester != NULL &&
       !_IsClient) {
      _ProxyRequester->Start();
   }
   CONTEXT_MAP_T::const_iterator i = _LocalContexts.cbegin();
   while (i != _LocalContexts.cend()) {
      cLocalContext * server_context = (cLocalContext*)(*i).second;
      if (server_context->get_IsClientContext()) {
         server_context->Start();
      }
      i++;
   }
   if (_EventChannel != NULL) {
      _EventChannel->Start();
   }
   cControlThread::Start();
  //## end cSHProcess::Start%1123228418.body
}

void cSHProcess::Stop ()
{
  //## begin cSHProcess::Stop%1123228419.body preserve=yes
   cControlThread::Stop();
   if (_ProxyRequester != NULL) {
      _ProxyRequester->Stop();
   }
   if (_EventChannel != NULL) {
      _EventChannel->Stop();
   }
   CONTEXT_MAP_T::const_iterator i = _LocalContexts.cbegin();
   while (i != _LocalContexts.cend()) {
      cLocalContext * server_context = (cLocalContext*)(*i).second;
      if (server_context->get_IsClientContext()) {
         server_context->Stop();
      }
      i++;
   }
  //## end cSHProcess::Stop%1123228419.body
}

INT_T cSHProcess::MainFunc (void *extra)
{
  //## begin cSHProcess::MainFunc%1037122841.body preserve=yes
MAINFUNC_PROLOG(_Name.c_str())
   StartReceiving();
   Pulse();
   while (Active()) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      Pulse();
      if (Active()) {
         try {
            OnCycle();
         } catch (cError & e) {
            ErrorPrintf("%s in OnCycle method of thread %s\n", (const char*)e, _Name.c_str());
         } catch (...) {
            ErrorPrintf("unhandled exception in OnCycle method of thread %s\n", _Name.c_str());
         }
         cSystemUtils::Suspend(_IdleTime);
      }
MAINFUNC_LOOP_EPILOG
   }
   StopReceiving();
   Pulse();
   return 0;
MAINFUNC_EPILOG
  //## end cSHProcess::MainFunc%1037122841.body
}

void cSHProcess::AddChannel (CONST_STRING_T name, cChannel *channel, BOOL_T remote)
{
  //## begin cSHProcess::AddChannel%1065778445.body preserve=yes
   if (remote) {
      _RemoteChannels[name] = channel;
   } else {
      _LocalChannels[name] = channel;
   }
  //## end cSHProcess::AddChannel%1065778445.body
}

cChannel * cSHProcess::Channel (CONST_STRING_T name)
{
  //## begin cSHProcess::Channel%1065778446.body preserve=yes
   CHANNEL_MAP_T::const_iterator i;
   i = _LocalChannels.find(name);
   if (i != _LocalChannels.cend()) return (*i).second;
   i = _RemoteChannels.find(name);
   if (i != _RemoteChannels.cend()) return (*i).second;
   return NULL;
  //## end cSHProcess::Channel%1065778446.body
}

void cSHProcess::AddContext (CONST_STRING_T name, cContext *context)
{
  //## begin cSHProcess::AddContext%1054828772.body preserve=yes
   context->set_Name(name);
   BOOL_T is_remote = context->IsRemote();
   if (is_remote) {
      _RemoteContexts[name] = context;
   } else {
      _LocalContexts[name] = context;
   }
  //## end cSHProcess::AddContext%1054828772.body
}

cContext * cSHProcess::Context (CONST_STRING_T name, ULONG_T filter)
{
  //## begin cSHProcess::Context%1054632818.body preserve=yes
   CONTEXT_MAP_T::const_iterator i;
   if (filter & LOCAL_CONTEXTS) {
      i = _LocalContexts.find(name);
      if (i != _LocalContexts.cend()) {
         return (*i).second;
      }
   }
   if (filter & REMOTE_CONTEXTS) {
      i = _RemoteContexts.find(name);
      if (i != _RemoteContexts.cend()) {
         return (*i).second;
      }
   }
   return NULL;
  //## end cSHProcess::Context%1054632818.body
}

void cSHProcess::AddService (CONST_STRING_T service)
{
  //## begin cSHProcess::AddService%1054897237.body preserve=yes
   _Services.push_back(service);
  //## end cSHProcess::AddService%1054897237.body
}

void cSHProcess::NewProxy (cProxy *proxy)
{
  //## begin cSHProcess::NewProxy%1054890582.body preserve=yes
   INT_T object_type = proxy->get_Type();
   STRING_T proxy_name = proxy->get_ProxyName();
   if (object_type == OT_CORBA_CELL_PROXY) {
      cCellProxy * cell_proxy = dynamic_cast<cCellProxy*>(proxy);
      if (cell_proxy == NULL) {
         ErrorPrintf("cell proxy is null in %s %d\n", __FILE__, __LINE__);
      } else {
         cell_proxy->set_IFType(_IFType);
         cContext * context = Context(proxy_name.c_str(), REMOTE_CONTEXTS);
         if (context != NULL) {
            // PR 03.08.10 - exchange proxy in context object to avoid accessibility problems
            //               in OPC services
            if (context->IsRemote()) {
               cRemoteContext * remote_context = static_cast<cRemoteContext*>(context);
               if (remote_context != NULL) {
                  proxy->AddRef();
                  remote_context->SetCellProxy(dynamic_cast<cCellProxy*>(proxy));
               }
            }
//          if (context->IsRemote()) {
//             _RemoteContexts.erase(proxy_name.c_str());
//             delete context;
//          }
         } else {
            context = new cRemoteContext(this, (cCellProxy*)proxy);
            AddContext(proxy_name.c_str(), context);
         }
/*
         if (context->IsRemote()) {
            cRemoteContext * remote_context = (cRemoteContext*)context;
            remote_context->Update(proxy->get_ProcessId());
         }
*/
      }
   } else if (object_type == OT_COS_EVENTCHANNEL_PROXY) {
      if (Channel(proxy_name.c_str()) == NULL) {
         cCOSChannel * channel = new cCOSChannel(proxy_name.c_str(), (cCosEventChannelProxy*)proxy);
         AddChannel(proxy_name.c_str(), channel, true);
      }
   } else {
   }
   //## end cSHProcess::NewProxy%1054890582.body
}

void cSHProcess::ContextNames (STRING_LIST_T &context_names, ULONG_T filter)
{
  //## begin cSHProcess::ContextNames%1075059041.body preserve=yes
   CONTEXT_MAP_T::const_iterator i;
   if (filter & LOCAL_CONTEXTS) {
      i = _LocalContexts.cbegin();
      while (i != _LocalContexts.cend()) {
         cContext * context = (*i).second;
         if (context != NULL) {
///            context_names.push_back(context->get_Name().c_str());
            context_names.push_back((*i).first.c_str());
         }
         i++;
      }
   }
   if (filter & REMOTE_CONTEXTS) {
      i = _RemoteContexts.cbegin();
      while (i != _RemoteContexts.cend()) {
         context_names.push_back((*i).first.c_str());
         i++;
      }
   }
  //## end cSHProcess::ContextNames%1075059041.body
}

cProxy * cSHProcess::Proxy (CONST_STRING_T name)
{
  //## begin cSHProcess::Proxy%1097408539.body preserve=yes
   cObjectLock __lock__(&_ReceiverMutex);
   PROXY_RECEIVER_MAP_T::const_iterator i = _ProxyReceiverMap.cbegin();
   while (i != _ProxyReceiverMap.cend()) {
      cProxyReceiver * receiver = (*i).second;
      if (receiver != NULL) {
         cProxy * proxy = receiver->Proxy(name);
         if (proxy != NULL) {
            return proxy;
         }
      }
      i++;
   }
   return NULL;
  //## end cSHProcess::Proxy%1097408539.body
}

void cSHProcess::Send (cTransientObject *object)
{
  //## begin cSHProcess::Send%1122555426.body preserve=yes
   if (_EventChannel != NULL) {
      _EventChannel->Send(object);
   }
  //## end cSHProcess::Send%1122555426.body
}

cChannel * cSHProcess::EventChannel ()
{
  //## begin cSHProcess::EventChannel%1122619257.body preserve=yes
   return _EventChannel;
  //## end cSHProcess::EventChannel%1122619257.body
}

void cSHProcess::Pulse ()
{
  //## begin cSHProcess::Pulse%1011276239.body preserve=yes
   cObjectLock __lock__(&_ServiceMutex);
   int size = _Services.size();
   SERVICE_LIST_T::const_iterator s = _Services.cbegin();
   while (s != _Services.cend()) {
      STRING_T serialized_proxy = (*s);
      cObjectLock __lock__(&_SenderMutex);
      PROXY_SENDER_MAP_T::const_iterator i = _ProxySenderMap.begin();
      while (i != _ProxySenderMap.cend()) {
         cProxySender * sender = (*i).second;
         long nsend = sender->Send(serialized_proxy.c_str());
         cSystemUtils::Suspend(10);
         i++;
      }
      s++;
   }
  //## end cSHProcess::Pulse%1011276239.body
}

void cSHProcess::StartReceiving ()
{
  //## begin cSHProcess::StartReceiving%1065795129.body preserve=yes
#ifdef lassma
   PROXY_RECEIVER_MAP_T::const_iterator i = _ProxyReceiverMap.cbegin();
   while (i != _ProxyReceiverMap.cend()) {
      cProxyReceiver * proxy_receiver = (*i).second;
      proxy_receiver->Start();
      i++;
   }
#endif
   if (_EventChannel != NULL) {
      _EventChannel->Start();
   }
  //## end cSHProcess::StartReceiving%1065795129.body
}

void cSHProcess::StopReceiving ()
{
  //## begin cSHProcess::StopReceiving%1065795130.body preserve=yes
   if (_EventChannel != NULL) {
      _EventChannel->Stop();
   }
   cClients::Exit();
   PROXY_RECEIVER_MAP_T::const_iterator i = _ProxyReceiverMap.cbegin();
   while (i != _ProxyReceiverMap.cend()) {
      cProxyReceiver * proxy_receiver = (*i).second;
      proxy_receiver->Stop();
      i++;
   }
  //## end cSHProcess::StopReceiving%1065795130.body
}

void cSHProcess::AddProxyReceiver (CONST_STRING_T receiver_name, cProxyReceiver *receiver)
{
  //## begin cSHProcess::AddProxyReceiver%1125297032.body preserve=yes
   if (ReceiverExists(receiver_name)) {
//      InfoPrintf("proxy receiver %s already exists\n", receiver_name);
      return;
   }
   cObjectLock __lock__(&_ReceiverMutex);
   _ProxyReceiverMap[receiver_name] = receiver;
   receiver->Start();
  //## end cSHProcess::AddProxyReceiver%1125297032.body
}

void cSHProcess::AddProxyReceiver (USHORT_T port)
{
  //## begin cSHProcess::AddProxyReceiver%1134383666.body preserve=yes
   STRING_T receiver_name = cProxyReceiver::ReceiverName(port);
   if (ReceiverExists(receiver_name.c_str())) {
//      InfoPrintf("proxy receiver %s already exists\n", receiver_name.c_str());
      return;
   }
   cProxyReceiver * proxy_receiver = new cProxyReceiver(this, port);
   AddProxyReceiver(receiver_name.c_str(), proxy_receiver);
  //## end cSHProcess::AddProxyReceiver%1134383666.body
}

void cSHProcess::AddProxySender (CONST_STRING_T sender_name, cProxySender *sender)
{
  //## begin cSHProcess::AddProxySender%1125297033.body preserve=yes
   if (SenderExists(sender_name)) {
//      InfoPrintf("proxy sender %s already exists\n", sender_name);
      return;
   }
   cObjectLock __lock__(&_SenderMutex);
   _ProxySenderMap[sender_name] = sender;
   InfoPrintf("sending proxy informations to %s\n", sender_name);
  //## end cSHProcess::AddProxySender%1125297033.body
}

void cSHProcess::AddProxySender (CONST_STRING_T addr, USHORT_T port)
{
  //## begin cSHProcess::AddProxySender%1134383667.body preserve=yes
   STRING_T sender_name = cProxySender::SenderName(addr, port);
   if (SenderExists(sender_name.c_str())) {
//      InfoPrintf("proxy sender %s already exists\n", sender_name.c_str());
      return;
   }
   cProxySender * proxy_sender = new cProxySender(addr, port);
   AddProxySender(sender_name.c_str(), proxy_sender);
//   InfoPrintf("sending proxy informations to %s:%d\n", addr, (int)port);
  //## end cSHProcess::AddProxySender%1134383667.body
}

void cSHProcess::AddProxyRequest (CONST_STRING_T addr)
{
  //## begin cSHProcess::AddProxyRequest%1134387057.body preserve=yes
   if (_ProxyRequester != NULL) {
      _ProxyRequester->AddAddress(addr);
   }
  //## end cSHProcess::AddProxyRequest%1134387057.body
}

void cSHProcess::AddProxyRequest (USHORT_T port)
{
  //## begin cSHProcess::AddProxyRequest%1134387058.body preserve=yes
   if (_ProxyRequester != NULL) {
      _ProxyRequester->AddPort(port);
   }
  //## end cSHProcess::AddProxyRequest%1134387058.body
}

void cSHProcess::AddRequestedPort (USHORT_T port)
{
  //## begin cSHProcess::AddRequestedPort%1134387059.body preserve=yes
   if (_ProxyRequester != NULL) {
      _ProxyRequester->AddRequestedPort(port);
   }
  //## end cSHProcess::AddRequestedPort%1134387059.body
}

BOOL_T cSHProcess::ReceiverExists (CONST_STRING_T name)
{
  //## begin cSHProcess::ReceiverExists%1134385872.body preserve=yes
   PROXY_RECEIVER_MAP_T::const_iterator i = _ProxyReceiverMap.find(name);
   if (i == _ProxyReceiverMap.cend()) {
      return false;
   } else {
      return true;
   }
  //## end cSHProcess::ReceiverExists%1134385872.body
}

BOOL_T cSHProcess::SenderExists (CONST_STRING_T name)
{
  //## begin cSHProcess::SenderExists%1134385873.body preserve=yes
   PROXY_SENDER_MAP_T::const_iterator i = _ProxySenderMap.find(name);
   if (i == _ProxySenderMap.cend()) {
      return false;
   } else {
      return true;
   }
  //## end cSHProcess::SenderExists%1134385873.body
}

void cSHProcess::OnCycle ()
{
  //## begin cSHProcess::OnCycle%1125301339.body preserve=yes
  //## end cSHProcess::OnCycle%1125301339.body
}

void cSHProcess::RegisterHandler (cRequestHandler *handler)
{
  //## begin cSHProcess::RegisterHandler%1125391948.body preserve=yes
   STRING_T name = handler->get_Name();
   _HandlerMap[name.c_str()] = handler;
  //## end cSHProcess::RegisterHandler%1125391948.body
}

void cSHProcess::RemoveHandler (cRequestHandler *handler)
{
  //## begin cSHProcess::RemoveHandler%1125391949.body preserve=yes
   STRING_T name = handler->get_Name();
   _HandlerMap.erase(name.c_str());
  //## end cSHProcess::RemoveHandler%1125391949.body
}

void cSHProcess::ReadIORFile ()
{
  //## begin cSHProcess::ReadIORFile%1132072708.body preserve=yes
   cIniFile ini_file(_IORFile.c_str());
   if (!ini_file.Exists()) {
      return;
   }
   STRING_VECTOR_T chapters;
   ini_file.ReadChapters(chapters);
   STRING_VECTOR_T::const_iterator _chapter = chapters.cbegin();
   while (_chapter != chapters.cend()) {
      STRING_T obj_name = (*_chapter).c_str();
      if (IDENTIFIER_EQUAL("Servers", obj_name.c_str())) {
         STRING_VECTOR_T keys;
         ini_file.ReadKeys(obj_name.c_str(), keys);
         STRING_VECTOR_T::const_iterator _key = keys.cbegin();
         while (_key != keys.cend()) {
            try {
               STRING_T server_name = (*_key).c_str();
               STRING_T ior = ini_file.ReadValue(obj_name.c_str(), server_name.c_str(), "");
               cCorbaCellProxy * cell_proxy = new cCorbaCellProxy;
               cell_proxy->set_IOR(ior.c_str());
               cell_proxy->SetItf();
               cell_proxy->set_ProxyName(server_name.c_str());
               cContext * context = new cRemoteContext(this, cell_proxy);
               AddContext(server_name.c_str(), context);
            } catch (cError & e) {
            } catch(...) {
            }
            _key++;
         }
      }
      _chapter++;
   }
  //## end cSHProcess::ReadIORFile%1132072708.body
}

void cSHProcess::RequestProxies ()
{
  //## begin cSHProcess::RequestProxies%1132208636.body preserve=yes
   if (_IsClient &&
       _ProxyRequester != NULL) {
      cObjectLock __lock__(&_SenderMutex);
      PROXY_RECEIVER_MAP_T::const_iterator i = _ProxyReceiverMap.cbegin();
      while (i != _ProxyReceiverMap.cend()) {
         cProxyReceiver * receiver = (*i).second;
         if (receiver != NULL) {
            USHORT_T requested_port = (USHORT_T)receiver->get_Port();
            _ProxyRequester->RequestProxy("localhost", requested_port);
         }
         i++;
      }  
   }
  //## end cSHProcess::RequestProxies%1132208636.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cSHProcess::get_ProcessId () const
{
  //## begin cSHProcess::get_ProcessId%3C4D442B03C6.get preserve=no
  return _ProcessId;
  //## end cSHProcess::get_ProcessId%3C4D442B03C6.get
}

STRING_T cSHProcess::get_Computer () const
{
  //## begin cSHProcess::get_Computer%3C4D739601E0.get preserve=no
  return _Computer;
  //## end cSHProcess::get_Computer%3C4D739601E0.get
}

STRING_T cSHProcess::get_Path () const
{
  //## begin cSHProcess::get_Path%3C4D4453002A.get preserve=no
  return _Path;
  //## end cSHProcess::get_Path%3C4D4453002A.get
}

void cSHProcess::set_Path (STRING_T value)
{
  //## begin cSHProcess::set_Path%3C4D4453002A.set preserve=no
  _Path = value;
  //## end cSHProcess::set_Path%3C4D4453002A.set
}

LONG_T cSHProcess::get_IFType () const
{
  //## begin cSHProcess::get_IFType%438AD8F301BD.get preserve=no
  return _IFType;
  //## end cSHProcess::get_IFType%438AD8F301BD.get
}

// Additional Declarations
  //## begin cSHProcess%3C46E64A0182.declarations preserve=yes
STRING_T cSHProcess::CorbaLocIOR(const STRING_T & host_name)
{
   char ior[0x200] = {0};
   int port = cBroker::ObjectDefaultPort();
   STRING_T object_key = CELL_OBJECT_KEY;
   SafePrintf(ior, sizeof(ior), "corbaloc:iiop:%s:%d/%s", host_name.c_str(), port, object_key.c_str());
   return ior;
}

bool cSHProcess::TranslateAdresses(CONST_STRING_T new_address, STRING_T & service)
{
   if (cBroker::GetUseCorbaLoc()) {
      cObjectLock __lock__(&_ServiceMutex);
      if (strcmp(_TranslatedIpAddress.c_str(), new_address) != 0) {
         _TranslatedIpAddress = new_address;
         SERVICE_LIST_T new_services;
         SERVICE_LIST_T::const_iterator s = _Services.cbegin();
         while (s != _Services.cend()) {
            STRING_T serialized_proxy = (*s);
            STRING_T new_serialized_proxy;
            cCorbaCellProxy * cell_proxy = new cCorbaCellProxy;
            if (cell_proxy->Construct(serialized_proxy.c_str())) {
               STRING_T ior = cell_proxy->get_IOR();
               STRING_T ip_address = cell_proxy->get_IPAddress();
               ULONG_T ip_port = cell_proxy->get_Port();
               STRING_T new_ior;
               new_ior = this->CorbaLocIOR(new_address);
               cell_proxy->set_IPAddress(new_address);
               cell_proxy->set_IOR(new_ior.c_str());
               cTimeObject now;
               ULONG_T time_value = (ULONG_T)now;
               cell_proxy->set_TimeStamp(time_value);
               new_serialized_proxy = cell_proxy->Serialize();
               new_services.push_back(new_serialized_proxy.c_str());
               service = new_serialized_proxy;
            } else {
               ErrorPrintf("failed to construct proxy for address translation: %s\n", serialized_proxy.c_str());
            }
            s++;
         }
         _Services.clear();
         _Services = new_services;
         InfoPrintf("translated addresses to %s\n", new_address);
         return true;
      }
   }
   return false;
}
  //## end cSHProcess%3C46E64A0182.declarations

//## begin module%3C46E64A0182.epilog preserve=yes
//## end module%3C46E64A0182.epilog
