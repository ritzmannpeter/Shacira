//## begin module%3C552714024C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C552714024C.cm

//## begin module%3C552714024C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C552714024C.cp

//## Module: cProxyReceiver%3C552714024C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxyReceiver.cpp

//## begin module%3C552714024C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C552714024C.additionalIncludes

//## begin module%3C552714024C.includes preserve=yes

#include "base/eb_shmem.hpp"
#include "base/base_ex.h"
#include "System/Sys/cSockets.h"

//## end module%3C552714024C.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cCellProxy
#include "System/Process/cCellProxy.h"
// cProxy
#include "System/Objects/cProxy.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cProxyReceiver
#include "System/Comm/cProxyReceiver.h"
// cProxyTable
#include "System/Comm/cProxyTable.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
// cChannelProxy
#include "System/Channel/cChannelProxy.h"
// cCosEventChannelProxy
#include "Orb/cCosEventChannelProxy.h"
// cCorbaCellProxy
#include "Orb/cCorbaCellProxy.h"
//## begin module%3C552714024C.additionalDeclarations preserve=yes

#include "base/base_ex.h"
using namespace ecl;

#define RECEIVER_ADDRESS   "127.0.0.1"
#define RECEIVER_TIMEOUT   1000
#define INBUF_SIZE         0x1000

#define NEW_PROXY_MANAGEMENT

#define MAX_INFO_SIZE      INBUF_SIZE
#define MAX_PROXIES        500
#define PROXY_NAME_LEN     0x100
#define SEGMENT_NAME       "Shacira.ProxyInfos"
typedef struct _proxy_info {
   ULONG_T time;
   char name[PROXY_NAME_LEN+1];
   char info[MAX_INFO_SIZE+1];
}  PROXY_INFO_T;
typedef struct _proxy_info_table {
   PROXY_INFO_T proxy_info[MAX_PROXIES+1];
}  PROXY_INFO_TABLE_T;

class cSharedProxyInfo {
public:
   cSharedProxyInfo()
   {
      _MemorySegment = NULL;
      _GlobalInfoTable = NULL;
      _LocalInfoTable = NULL;
      try {
         _MemorySegment = new cSharedMem(SEGMENT_NAME, cSharedMem::memOpenOrCreate, sizeof(PROXY_INFO_TABLE_T));
      } catch (...) {
         return;
      }
      char * mem = (char*)_MemorySegment->getAdr();
      _RefCount = (ATOMIC_T*)mem;
      _GlobalInfoTable = (PROXY_INFO_TABLE_T*)(mem + sizeof(int));
      _LocalInfoTable = (PROXY_INFO_TABLE_T*)cSystemUtils::Alloc(sizeof(PROXY_INFO_TABLE_T));
   };
   ~cSharedProxyInfo()
   {
      if (_MemorySegment != NULL) {
         delete _MemorySegment;
      }
      if (_LocalInfoTable != NULL) {
         cSystemUtils::Free(_LocalInfoTable);
      }
   };
   void SetProxyInfo(ULONG_T time, CONST_STRING_T name, CONST_STRING_T info)
   {
      WaitForExclusiveAccess();
      if (_GlobalInfoTable != NULL) {
         for (int i=0; i<MAX_PROXIES; i++) {
            PROXY_INFO_T * info_ptr = &(_GlobalInfoTable->proxy_info[i]);
            if (strcmp(info_ptr->name, name) == 0) {
               if (time != info_ptr->time) {
                  info_ptr->time = time;
                  memset(info_ptr->info, 0, MAX_INFO_SIZE);
                  memcpy(info_ptr->info, info, strlen(info));
               } else {
                  int dummy = 0;
               }
               __ECL_ATOMIC_DECREMENT__(*_RefCount);
               return;
            } if (strlen(info_ptr->name) == 0) {
               info_ptr->time = time;
               memcpy(info_ptr->name, name, strlen(name));
               memcpy(info_ptr->info, info, strlen(info));
               __ECL_ATOMIC_DECREMENT__(*_RefCount);
               return;
            }
         }
      }
      __ECL_ATOMIC_DECREMENT__(*_RefCount);
   };
   void GetNewProxyInfos(STRING_LIST_T & proxy_infos)
   {
      if (!WaitForExclusiveAccess(5000)) {
         return;
      }
      if (_GlobalInfoTable != NULL) {
         for (int i=0; i<MAX_PROXIES; i++) {
            PROXY_INFO_T * global_info_ptr = &(_GlobalInfoTable->proxy_info[i]);
            if (*(global_info_ptr->name) == 0) {
               __ECL_ATOMIC_DECREMENT__(*_RefCount);
               return;
            } else {
               PROXY_INFO_T * local_info_ptr = &(_LocalInfoTable->proxy_info[i]);
               if (local_info_ptr->time < global_info_ptr->time) {
                  proxy_infos.push_back(global_info_ptr->info);
                  memcpy(local_info_ptr, global_info_ptr, sizeof(_proxy_info));
               }
            }
         }
      }
      __ECL_ATOMIC_DECREMENT__(*_RefCount);
   };
private:
   BOOL_T WaitForExclusiveAccess(int timeout = -1)
   {
return true;
      int remaining = 0;
      long count = 0;
      if (timeout != -1) {
         remaining = timeout;
      }
      while (true) {
         if (timeout != -1 && remaining < 0) {
            return false;
         }
         count = __ECL_ATOMIC_INCREMENT__(*_RefCount);
         if (count == 1) {
            return true;
         }
         remaining -= 100;
         cSystemUtils::Suspend(100);
         __ECL_ATOMIC_DECREMENT__(*_RefCount);
      }
   };
private:
   ATOMIC_T * _RefCount;
   cSharedMem * _MemorySegment;
   PROXY_INFO_TABLE_T * _GlobalInfoTable;
   PROXY_INFO_TABLE_T * _LocalInfoTable;
};

static cSharedProxyInfo * _ProxyInfoTable = NULL;

//## end module%3C552714024C.additionalDeclarations


// Class cProxyReceiver 





//## begin cProxyReceiver::ProxyTableMutex%43F463C20125.attr preserve=no  implementation: static cMutexSem {U} 
cMutexSem cProxyReceiver::_ProxyTableMutex;
//## end cProxyReceiver::ProxyTableMutex%43F463C20125.attr

//## begin cProxyReceiver::ProxyTable%43F45E970120.attr preserve=no  implementation: static cProxyTable * {U} NULL
cProxyTable *cProxyReceiver::_ProxyTable = NULL;
//## end cProxyReceiver::ProxyTable%43F45E970120.attr

//## begin cProxyReceiver::ProxyTableRefCount%4CF3D7960124.attr preserve=no  implementation: static long {U} 0
long cProxyReceiver::_ProxyTableRefCount = 0;
//## end cProxyReceiver::ProxyTableRefCount%4CF3D7960124.attr

cProxyReceiver::cProxyReceiver()
  //## begin cProxyReceiver::cProxyReceiver%.hasinit preserve=no
      : _Port(0), _Socket(INVALID_SOCKET), _Process(NULL)
  //## end cProxyReceiver::cProxyReceiver%.hasinit
  //## begin cProxyReceiver::cProxyReceiver%.initialization preserve=yes
  //## end cProxyReceiver::cProxyReceiver%.initialization
{
  //## begin cProxyReceiver::cProxyReceiver%.body preserve=yes
   cObjectLock __lock__(&_ProxyTableMutex);
   if (_ProxyTable == NULL) {
      _ProxyTable = new cProxyTable;
   }
   _InBuf.Size(INBUF_SIZE);
   InterlockedIncrement(&_ProxyTableRefCount);
#ifdef NEW_PROXY_MANAGEMENT
   if (_ProxyInfoTable == NULL) {
      _ProxyInfoTable = new cSharedProxyInfo;
   }
#endif
  //## end cProxyReceiver::cProxyReceiver%.body
}

cProxyReceiver::cProxyReceiver(const cProxyReceiver &right)
  //## begin cProxyReceiver::cProxyReceiver%copy.hasinit preserve=no
      : _Port(0), _Socket(INVALID_SOCKET), _Process(NULL)
  //## end cProxyReceiver::cProxyReceiver%copy.hasinit
  //## begin cProxyReceiver::cProxyReceiver%copy.initialization preserve=yes
  //## end cProxyReceiver::cProxyReceiver%copy.initialization
{
  //## begin cProxyReceiver::cProxyReceiver%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProxyReceiver::cProxyReceiver%copy.body
}

cProxyReceiver::cProxyReceiver (cSHProcess *process, ULONG_T port)
  //## begin cProxyReceiver::cProxyReceiver%1012207924.hasinit preserve=no
      : _Port(0), _Socket(INVALID_SOCKET), _Process(NULL)
  //## end cProxyReceiver::cProxyReceiver%1012207924.hasinit
  //## begin cProxyReceiver::cProxyReceiver%1012207924.initialization preserve=yes
  //## end cProxyReceiver::cProxyReceiver%1012207924.initialization
{
  //## begin cProxyReceiver::cProxyReceiver%1012207924.body preserve=yes
   cObjectLock __lock__(&_ProxyTableMutex);
   if (_ProxyTable == NULL) {
      _ProxyTable = new cProxyTable;
   }
   InterlockedIncrement(&_ProxyTableRefCount);
   _InBuf.Size(INBUF_SIZE);
   _Port = port;
   SetSockets();
   _Process = process;
   char name[0x100] = {0};
   SafePrintf(name, sizeof(name), "Receiver.%s:%d", RECEIVER_ADDRESS, _Port);
   _Name = name;
#ifdef NEW_PROXY_MANAGEMENT
   if (_ProxyInfoTable == NULL) {
      _ProxyInfoTable = new cSharedProxyInfo;
   }
#endif
  //## end cProxyReceiver::cProxyReceiver%1012207924.body
}

cProxyReceiver::cProxyReceiver (cConfigurationObject *config_obj, cSHProcess *process)
  //## begin cProxyReceiver::cProxyReceiver%1012207925.hasinit preserve=no
      : _Port(0), _Socket(INVALID_SOCKET), _Process(NULL)
  //## end cProxyReceiver::cProxyReceiver%1012207925.hasinit
  //## begin cProxyReceiver::cProxyReceiver%1012207925.initialization preserve=yes
  //## end cProxyReceiver::cProxyReceiver%1012207925.initialization
{
  //## begin cProxyReceiver::cProxyReceiver%1012207925.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   cObjectLock __lock__(&_ProxyTableMutex);
   if (_ProxyTable == NULL) {
      _ProxyTable = new cProxyTable;
   }
   InterlockedIncrement(&_ProxyTableRefCount);
   _InBuf.Size(INBUF_SIZE);
   _Name = config_obj->get_Name().c_str();
   _Port = config_obj->PropertyValue("ReceivePort", _Port);
   SetSockets();
   _Process = process;
   char name[0x100] = {0};
   SafePrintf(name, sizeof(name), "Receiver.%s:%d", RECEIVER_ADDRESS, _Port);
   _Name = name;
#ifdef NEW_PROXY_MANAGEMENT
   if (_ProxyInfoTable == NULL) {
      _ProxyInfoTable = new cSharedProxyInfo;
   }
#endif
  //## end cProxyReceiver::cProxyReceiver%1012207925.body
}


cProxyReceiver::~cProxyReceiver()
{
  //## begin cProxyReceiver::~cProxyReceiver%.body preserve=yes
   Stop();
   CloseSockets();
   long ref_count = InterlockedDecrement(&_ProxyTableRefCount);
   if (ref_count == 0) {
      DELETE_OBJECT(cProxyTable, _ProxyTable)
   }
  //## end cProxyReceiver::~cProxyReceiver%.body
}



//## Other Operations (implementation)
cProxy * cProxyReceiver::Proxy (CONST_STRING_T name)
{
  //## begin cProxyReceiver::Proxy%1012295717.body preserve=yes
   return _ProxyTable->Proxy(name);
  //## end cProxyReceiver::Proxy%1012295717.body
}

cCellProxy * cProxyReceiver::CellProxy (CONST_STRING_T name)
{
  //## begin cProxyReceiver::CellProxy%1012295719.body preserve=yes
   cObjectLock __lock__(&_ProxyTableMutex);
   return _ProxyTable->CellProxy(name);
  //## end cProxyReceiver::CellProxy%1012295719.body
}

cChannelProxy * cProxyReceiver::ChannelProxy (CONST_STRING_T name)
{
  //## begin cProxyReceiver::ChannelProxy%1012295720.body preserve=yes
   cObjectLock __lock__(&_ProxyTableMutex);
   return _ProxyTable->ChannelProxy(name);
  //## end cProxyReceiver::ChannelProxy%1012295720.body
}

INT_T cProxyReceiver::MainFunc (void *extra)
{
  //## begin cProxyReceiver::MainFunc%1012207938.body preserve=yes
MAINFUNC_PROLOG(_Name.c_str())
   while (Active()) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      if (Terminated()) {
         return 0;
      }
      long size = Receive(_InBuf, _InBuf.Size(), RECEIVER_TIMEOUT);
      if (size > 0) {
         ((char*)_InBuf)[size] = 0;
         const char * serialized_obj = (const char *)_InBuf;
         int object_type = cTransferObject::ObjectType(serialized_obj);
         cProxy * proxy = NULL;
         if (object_type == OT_CORBA_CELL_PROXY) {
            proxy = new cCorbaCellProxy;
         } else if (object_type == OT_COS_EVENTCHANNEL_PROXY) {
            proxy = new cCosEventChannelProxy;
         } else {
            throw cError(PROXY_RECEIVER_UNKNOWN_POT, 0,
                         cConvUtils::StringValue(object_type).c_str(),
                         _Name.c_str(), serialized_obj);
         }
         if (proxy != NULL) {
            if (proxy->Construct(serialized_obj)) {
               if (_ProxyInfoTable == NULL) {            
                  STRING_T ior = proxy->get_IOR();
                  if (!Exists(ior.c_str())) {
                     cObjectLock __lock__(&_ProxyTableMutex);
                     _ProxyTable->SetProxy(proxy);
                     if (_Process != NULL) {
                        _Process->NewProxy(proxy);
                     }
                  }
               } else {
                  ULONG_T time = (ULONG_T)proxy->get_TimeStamp();
                  STRING_T proxy_name = proxy->get_ProxyName();
                  STRING_T proxy_info = serialized_obj;
                  _ProxyInfoTable->SetProxyInfo(time, proxy_name.c_str(), proxy_info.c_str());
               }
            } else {
					RELEASE_OBJECT(proxy)
               throw cError(PROXY_RECEIVER_FAILED_TO_CONSTRUCT, 0,
                            _Name.c_str(), serialized_obj);
            }
            RELEASE_OBJECT(proxy)
         }
      }
      if (_ProxyInfoTable != NULL) {
         STRING_LIST_T new_proxy_infos;
         _ProxyInfoTable->GetNewProxyInfos(new_proxy_infos);
         STRING_LIST_T::const_iterator i = new_proxy_infos.begin();
         while (i != new_proxy_infos.end()) {
            STRING_T new_proxy_info = (*i);
            i++;
            int object_type = cTransferObject::ObjectType(new_proxy_info.c_str());
            cProxy * new_proxy = NULL;
            if (object_type == OT_CORBA_CELL_PROXY) {
               new_proxy = new cCorbaCellProxy;
            } else if (object_type == OT_COS_EVENTCHANNEL_PROXY) {
               new_proxy = new cCosEventChannelProxy;
            } else {
            }
            if (new_proxy != NULL) {
               if (new_proxy->Construct(new_proxy_info.c_str())) {
                  cObjectLock __lock__(&_ProxyTableMutex);
                  _ProxyTable->SetProxy(new_proxy);
                  if (_Process != NULL) {
                     _Process->NewProxy(new_proxy);
                  }
               }
               RELEASE_OBJECT(new_proxy)
            }
         }
         cSystemUtils::Suspend(10);
      }
MAINFUNC_LOOP_EPILOG
   }
   return 0;
MAINFUNC_EPILOG
  //## end cProxyReceiver::MainFunc%1012207938.body
}

STRING_T cProxyReceiver::ReceiverName (USHORT_T port)
{
  //## begin cProxyReceiver::ReceiverName%1134385868.body preserve=yes
   char receiver_name[0x100] = {0};
   SafePrintf(receiver_name, sizeof(receiver_name), "receiver.%s:%d", RECEIVER_ADDRESS, port);
   return receiver_name;
  //## end cProxyReceiver::ReceiverName%1134385868.body
}

ULONG_T cProxyReceiver::Receive (CONST_STRING_T buf, ULONG_T buf_size, ULONG_T timeout)
{
  //## begin cProxyReceiver::Receive%1054547834.body preserve=yes
   if (_Socket == INVALID_SOCKET) {
      cSystemUtils::Suspend(100);
      return 0;
   }
   cSockets::SetReceiveTimeout(_Socket, timeout);
   struct sockaddr addr = {0};
   socklen_t addr_size = sizeof(addr);
   int flags = 0;
   int nreceive = recvfrom(_Socket, _InBuf, _InBuf.Size(), flags, &addr, &addr_size);
   int err_code = WSAGetLastError();
   if (nreceive < 0) {
      if (!TIMED_OUT(err_code)) {
         throw cError(SOCKET_RECVFROM, err_code, RECEIVER_ADDRESS,
                      cConvUtils::StringValue(_Port).c_str(),
                      cConvUtils::StringValue(err_code).c_str());
      }
      return 0;
   } else {
      if ((long)buf_size >= nreceive) {
         memcpy((void*)buf, _InBuf, nreceive);
         return nreceive;
      } else {
         throw cError(SOCKET_BUF_TOO_SMALL, 0, RECEIVER_ADDRESS,
                      cConvUtils::StringValue(_Port).c_str(),
                      cConvUtils::StringValue(nreceive).c_str(),
                      cConvUtils::StringValue(buf_size).c_str());
      }
   }
  //## end cProxyReceiver::Receive%1054547834.body
}

void cProxyReceiver::SetSockets ()
{
  //## begin cProxyReceiver::SetSockets%1054547835.body preserve=yes
   int on = 1;
   if (_Port != 0) {
      struct sockaddr_in client_addr = {0};
      if ((_Socket = socket(AF_INET, SOCK_DGRAM, 0)) != INVALID_SOCKET) {
         if (setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
            throw cError(SOCKET_SETSOCKOPT, WSAGetLastError(), RECEIVER_ADDRESS,
                         cConvUtils::StringValue(_Port).c_str(), "SO_REUSEADDR");
         }
         client_addr.sin_family = AF_INET;
         client_addr.sin_addr.s_addr = INADDR_ANY;
         client_addr.sin_port = htons((unsigned short)_Port);
         if (!bind(_Socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0) {
            throw cError(SOCKET_BIND, WSAGetLastError(), RECEIVER_ADDRESS,
                         cConvUtils::StringValue(_Port).c_str());
         }
         int timeout = RECEIVER_TIMEOUT;
         cSockets::SetReceiveTimeout(_Socket, timeout);
      } else {
         throw cError(SOCKET_CREATE, WSAGetLastError(), RECEIVER_ADDRESS,
                      cConvUtils::StringValue(_Port).c_str());
      }
   }
  //## end cProxyReceiver::SetSockets%1054547835.body
}

void cProxyReceiver::CloseSockets ()
{
  //## begin cProxyReceiver::CloseSockets%1054547836.body preserve=yes
   if (_Socket != INVALID_SOCKET) {
      closesocket(_Socket);
   }
  //## end cProxyReceiver::CloseSockets%1054547836.body
}

BOOL_T cProxyReceiver::Exists (CONST_STRING_T ior)
{
  //## begin cProxyReceiver::Exists%1133788614.body preserve=yes
   IOR_MAP_T::const_iterator i = _IORMap.find(ior);
   if (i == _IORMap.end()) {
      _IORMap[ior] = ior;
      return false;
   } else {
      return true;
   }
  //## end cProxyReceiver::Exists%1133788614.body
}

void cProxyReceiver::FlushInput ()
{
  //## begin cProxyReceiver::FlushInput%1134636719.body preserve=yes
/// flushing is neither needed nor a good idea
   return;
   if (_Socket == INVALID_SOCKET) {
      return;
   }
   int timeout = 10;
   cSockets::SetReceiveTimeout(_Socket, timeout);
   struct sockaddr addr = {0};
   socklen_t addr_size = sizeof(addr);
   int flags = 0;
   int nreceive = recvfrom(_Socket, _InBuf, _InBuf.Size(), flags, &addr, &addr_size);
   while (nreceive > 0) {
      nreceive = recvfrom(_Socket, _InBuf, _InBuf.Size(), flags, &addr, &addr_size);
   }
  //## end cProxyReceiver::FlushInput%1134636719.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cProxyReceiver::get_Port () const
{
  //## begin cProxyReceiver::get_Port%3EDB23D201B5.get preserve=no
  return _Port;
  //## end cProxyReceiver::get_Port%3EDB23D201B5.get
}

// Additional Declarations
  //## begin cProxyReceiver%3C552714024C.declarations preserve=yes
  //## end cProxyReceiver%3C552714024C.declarations

//## begin module%3C552714024C.epilog preserve=yes
//## end module%3C552714024C.epilog
