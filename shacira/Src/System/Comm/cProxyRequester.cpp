//## begin module%437B8D91006B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%437B8D91006B.cm

//## begin module%437B8D91006B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%437B8D91006B.cp

//## Module: cProxyRequester%437B8D91006B; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxyRequester.cpp

//## begin module%437B8D91006B.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%437B8D91006B.additionalIncludes

//## begin module%437B8D91006B.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%437B8D91006B.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cProxyRequester
#include "System/Comm/cProxyRequester.h"
// cProxySender
#include "System/Comm/cProxySender.h"
// cClients
#include "Client/ClientData/cClients.h"
//## begin module%437B8D91006B.additionalDeclarations preserve=yes

#define RECEIVER_ADDRESS   "127.0.0.1"
#define RECEIVER_TIMEOUT   100
#define INBUF_SIZE         0x1000

//## end module%437B8D91006B.additionalDeclarations


// Class cProxyRequester 








cProxyRequester::cProxyRequester()
  //## begin cProxyRequester::cProxyRequester%.hasinit preserve=no
      : _IsClient(false), _Process(NULL)
  //## end cProxyRequester::cProxyRequester%.hasinit
  //## begin cProxyRequester::cProxyRequester%.initialization preserve=yes
  //## end cProxyRequester::cProxyRequester%.initialization
{
  //## begin cProxyRequester::cProxyRequester%.body preserve=yes
_ASSERT_UNCOND
  //## end cProxyRequester::cProxyRequester%.body
}

cProxyRequester::cProxyRequester(const cProxyRequester &right)
  //## begin cProxyRequester::cProxyRequester%copy.hasinit preserve=no
      : _IsClient(false), _Process(NULL)
  //## end cProxyRequester::cProxyRequester%copy.hasinit
  //## begin cProxyRequester::cProxyRequester%copy.initialization preserve=yes
  //## end cProxyRequester::cProxyRequester%copy.initialization
{
  //## begin cProxyRequester::cProxyRequester%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProxyRequester::cProxyRequester%copy.body
}

cProxyRequester::cProxyRequester (cSHProcess *process, BOOL_T is_client)
  //## begin cProxyRequester::cProxyRequester%1132170917.hasinit preserve=no
      : _IsClient(false), _Process(NULL)
  //## end cProxyRequester::cProxyRequester%1132170917.hasinit
  //## begin cProxyRequester::cProxyRequester%1132170917.initialization preserve=yes
  //## end cProxyRequester::cProxyRequester%1132170917.initialization
{
  //## begin cProxyRequester::cProxyRequester%1132170917.body preserve=yes
   _Name = "ProxyRequester";
   _IsClient = is_client;
   _InBuf.Size(INBUF_SIZE);
   _Process = process;
   _IdleTime = 1000;
  //## end cProxyRequester::cProxyRequester%1132170917.body
}


cProxyRequester::~cProxyRequester()
{
  //## begin cProxyRequester::~cProxyRequester%.body preserve=yes
  //## end cProxyRequester::~cProxyRequester%.body
}



//## Other Operations (implementation)
void cProxyRequester::AddPort (USHORT_T port)
{
  //## begin cProxyRequester::AddPort%1132170918.body preserve=yes
   _RequesterPortMap[port] = port;
   SetSocket(port);
  //## end cProxyRequester::AddPort%1132170918.body
}

void cProxyRequester::AddRequestedPort (USHORT_T port)
{
  //## begin cProxyRequester::AddRequestedPort%1132208637.body preserve=yes
   _RequestedPortMap[port] = port;
  //## end cProxyRequester::AddRequestedPort%1132208637.body
}

void cProxyRequester::AddAddress (CONST_STRING_T address)
{
  //## begin cProxyRequester::AddAddress%1132208638.body preserve=yes
   _AddressMap[address] = address;
  //## end cProxyRequester::AddAddress%1132208638.body
}

void cProxyRequester::RequestProxy (CONST_STRING_T server_addr, USHORT_T requested_port)
{
  //## begin cProxyRequester::RequestProxy%1132208368.body preserve=yes
   if (cClients::GetConnected()) {
      return;
   }
   PORT_MAP_T::const_iterator i = _RequesterPortMap.begin();
   while (i != _RequesterPortMap.end()) {
      USHORT_T server_port = (*i).second;
      RequestProxy(server_addr, server_port, requested_port); 
      i++;
   }
  //## end cProxyRequester::RequestProxy%1132208368.body
}

void cProxyRequester::RequestProxy (CONST_STRING_T server_addr, USHORT_T server_port, USHORT_T requested_port)
{
  //## begin cProxyRequester::RequestProxy%1132208635.body preserve=yes
   if (cClients::GetConnected()) {
      return;
   }
   SOCKET socket = Socket(server_port);
   if (socket == INVALID_SOCKET) {
      return;
   }
   char _requested_port[0x40] = {0};
   SafePrintf(_requested_port, sizeof(_requested_port), "%d", requested_port);
   unsigned long msg_size = strlen(_requested_port);
   struct sockaddr_in addr = {0};
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = inet_addr(server_addr);
   addr.sin_port = htons(server_port);
   int flags = 0;
   int nsend = sendto(socket, _requested_port, msg_size, flags, (struct sockaddr *)&addr, sizeof(addr));
   if (nsend < 0) {
      int err = WSAGetLastError();
      if (err != WSAEHOSTUNREACH) {
         throw cError(SOCKET_SENDTO, err, server_addr,
                      cConvUtils::StringValue(server_port).c_str());
      } else {
         return;
      }
   } else {
      return;
   }
  //## end cProxyRequester::RequestProxy%1132208635.body
}

INT_T cProxyRequester::MainFunc (void *extra)
{
  //## begin cProxyRequester::MainFunc%1132170919.body preserve=yes
MAINFUNC_PROLOG(_Name.c_str())
   while (Active() && !_Terminated) {
MAINFUNC_LOOP_PROLOG(_Name.c_str())
      if (_IsClient) {
         RequestProxies();
      } else {
         HandleRequests();
      }
      cSystemUtils::Suspend(10);
MAINFUNC_LOOP_EPILOG
   }
   return 0;
MAINFUNC_EPILOG
  //## end cProxyRequester::MainFunc%1132170919.body
}

void cProxyRequester::HandleRequests ()
{
  //## begin cProxyRequester::HandleRequests%1132170921.body preserve=yes
   PORT_MAP_T::const_iterator i = _RequesterPortMap.begin();
   while (i != _RequesterPortMap.end()) {
      USHORT_T port = (*i).second;
      HandlePort(port, RECEIVER_TIMEOUT); 
      i++;
   }
  //## end cProxyRequester::HandleRequests%1132170921.body
}

void cProxyRequester::HandlePort (USHORT_T port, ULONG_T timeout)
{
  //## begin cProxyRequester::HandlePort%1132170925.body preserve=yes
   STRING_T sender_addr;
   int nreceive = ReceiveFromPort(port, _InBuf, _InBuf.Size(), timeout, sender_addr);
   if (nreceive > 0) {
      int requested_port = atoi(_InBuf);
      _Process->AddProxySender(sender_addr.c_str(), requested_port);
   }
  //## end cProxyRequester::HandlePort%1132170925.body
}

SOCKET cProxyRequester::Socket (USHORT_T port)
{
  //## begin cProxyRequester::Socket%1132170924.body preserve=yes
   SOCKET_MAP_T::const_iterator i = _SocketMap.find(port);
   if (i == _SocketMap.end()) {
      return INVALID_SOCKET;
   } else {
      return (*i).second;
   }
  //## end cProxyRequester::Socket%1132170924.body
}

void cProxyRequester::SetSocket (USHORT_T port)
{
  //## begin cProxyRequester::SetSocket%1132170922.body preserve=yes
   int on = 1;
   if (port != 0) {
      SOCKET _socket = socket(AF_INET, SOCK_DGRAM, 0);
      if (_socket != INVALID_SOCKET) {
         if (_IsClient) {
            int on = 1;
   		   if (setsockopt(_socket, SOL_SOCKET, SO_BROADCAST, (const char*)&on, sizeof(on)) < 0) {
               throw cError(SOCKET_SETSOCKOPT, WSAGetLastError(), "",
                           cConvUtils::StringValue(port).c_str(), "SO_BROADCAST");
   		   }
            if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
               throw cError(SOCKET_SETSOCKOPT, WSAGetLastError(), "",
                           cConvUtils::StringValue(port).c_str(), "SO_REUSEADDR");
            }
         } else {
            if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
               throw cError(SOCKET_SETSOCKOPT, WSAGetLastError(), RECEIVER_ADDRESS,
                            cConvUtils::StringValue(port).c_str(), "SO_REUSEADDR");
            }
            struct sockaddr_in client_addr = {0};
            client_addr.sin_family = AF_INET;
            client_addr.sin_addr.s_addr = INADDR_ANY;
            client_addr.sin_port = htons((unsigned short)port);
            if (!bind(_socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0) {
               throw cError(SOCKET_BIND, WSAGetLastError(), RECEIVER_ADDRESS,
                            cConvUtils::StringValue(port).c_str());
            }
         }
         _SocketMap[port] = _socket;
      } else {
         throw cError(SOCKET_CREATE, WSAGetLastError(), RECEIVER_ADDRESS,
                      cConvUtils::StringValue(port).c_str());
      }
   }
  //## end cProxyRequester::SetSocket%1132170922.body
}

void cProxyRequester::CloseSockets ()
{
  //## begin cProxyRequester::CloseSockets%1132170923.body preserve=yes
   SOCKET_MAP_T::const_iterator i = _SocketMap.begin();
   while (i != _SocketMap.end()) {
      SOCKET socket = (*i).second;
      if (socket != INVALID_SOCKET) {
         closesocket(socket);
      }
      i++;
   }
  //## end cProxyRequester::CloseSockets%1132170923.body
}

int cProxyRequester::ReceiveFromPort (USHORT_T port, CONST_STRING_T buf, ULONG_T buf_size, ULONG_T timeout, STRING_T &sender_addr)
{
  //## begin cProxyRequester::ReceiveFromPort%1132170926.body preserve=yes
   SOCKET socket = Socket(port);
   if (socket == INVALID_SOCKET) {
      return 0;
   }
   cSockets::SetReceiveTimeout(socket, timeout);
   struct sockaddr_in addr = {0};
   socklen_t addr_size = sizeof(addr);
   int flags = 0;
   int nreceive = recvfrom(socket, _InBuf, _InBuf.Size(), flags, (struct sockaddr *)&addr, &addr_size);
   int err_code = WSAGetLastError();
   if (nreceive < 0) {
      if (!TIMED_OUT(err_code)) {
         throw cError(SOCKET_RECVFROM, err_code, RECEIVER_ADDRESS,
                      cConvUtils::StringValue(port).c_str(),
                      cConvUtils::StringValue(err_code).c_str());
      }
      return nreceive;
   } else {
      if ((long)buf_size >= nreceive) {
         sender_addr = inet_ntoa(addr.sin_addr);
         memcpy((void*)buf, _InBuf, nreceive);
         return nreceive;
      } else {
         throw cError(SOCKET_BUF_TOO_SMALL, 0, RECEIVER_ADDRESS,
                      cConvUtils::StringValue(port).c_str(),
                      cConvUtils::StringValue(nreceive).c_str(),
                      cConvUtils::StringValue(buf_size).c_str());
      }
   }
  //## end cProxyRequester::ReceiveFromPort%1132170926.body
}

void cProxyRequester::RequestProxies ()
{
  //## begin cProxyRequester::RequestProxies%1132208639.body preserve=yes
   if (_IsClient) {
      ADDRESS_MAP_T::const_iterator ai = _AddressMap.begin();
      while (ai != _AddressMap.end()) {
         STRING_T address = (*ai).second;
         PORT_MAP_T::const_iterator rpi = _RequestedPortMap.begin();
         while (rpi != _RequestedPortMap.end()) {
            USHORT_T requested_port = (*rpi).second;
            PORT_MAP_T::const_iterator pi = _RequesterPortMap.begin();
            while (pi != _RequesterPortMap.end()) {
               USHORT_T server_port = (*pi).second;
               RequestProxy(address.c_str(), server_port, requested_port); 
               pi++;
            }
            rpi++;
         }
         ai++;
      }
      cSystemUtils::Suspend(2000);
   }
  //## end cProxyRequester::RequestProxies%1132208639.body
}

// Additional Declarations
  //## begin cProxyRequester%437B8D91006B.declarations preserve=yes
  //## end cProxyRequester%437B8D91006B.declarations

//## begin module%437B8D91006B.epilog preserve=yes
//## end module%437B8D91006B.epilog
