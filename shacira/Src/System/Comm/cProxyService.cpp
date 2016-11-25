
#include "FirstHeader.h"
#include "System/Comm/cProxyService.h"
#include "System/Comm/cProxySender.h"
#include "System/Process/cSHProcess.h"

cProxyService::cProxyService(cSHProcess *process, unsigned short port)
{
   _Active = false;
   _ClientReceiveTimeout = DEFAULT_CLIENT_RECEIVE_TIMEOUT;
   _ServerReceiveTimeout = DEFAULT_SERVICE_RECEIVE_TIMEOUT;
   _Process = process;
   _Port = port;
   _StopRequest = false;
   _Socket = INVALID_SOCKET;
}

cProxyService::cProxyService(cSHProcess *process, CONST_STRING_T service, CONST_STRING_T service_name,
                             unsigned short port)
{
   _Active = false;
   _ClientReceiveTimeout = DEFAULT_CLIENT_RECEIVE_TIMEOUT;
   _ServerReceiveTimeout = DEFAULT_SERVICE_RECEIVE_TIMEOUT;
   _Process = process;
   _Service = service;
   _ServiceName = service_name;
   _Port = port;
   _StopRequest = false;
   _Socket = INVALID_SOCKET;
}

cProxyService::~cProxyService()
{
}

INT_T cProxyService::onMain(void *extra)
{
   _Active = true;
   InitServer();
   HandleRequests();
   _Active = false;
   return 0;
}

void cProxyService::Start()
{
   start(teStart);
}

void cProxyService::Stop()
{
   if (!_Active) {
      return;
   }
   closesocket(_Socket);
   _StopRequest = true;
   waitFor(teEnd);
}

void cProxyService::InitServer()
{
}

BOOL_T cProxyService::Request(CONST_STRING_T host, UCHAR_T command, int & error,
                              void * response_buf, ULONG_T buf_size)
{
   unsigned short port = _Port;
   error = 0;
   struct hostent * host_entry = NULL;
   SOCKET client_socket = INVALID_SOCKET;
   struct protoent * protoentry = NULL;
   if ((protoentry = getprotobyname("tcp")) == NULL) {
      error = WSAGetLastError();
      ErrorPrintf("failed to get protocol: %d\n", error);
      return false;
   } else {
      if ((client_socket = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
         error = WSAGetLastError();
///	      ErrorPrintf("failed to create client socket: %d\n", error);
         return false;
      }
	}
   int on = 1;
   if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
      error = WSAGetLastError();
      ErrorPrintf("failed to set socket option SO_REUSEADDR: %d\n", error);
   }
   if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&_ClientReceiveTimeout, sizeof(_ClientReceiveTimeout)) < 0) {
      error = WSAGetLastError();
      ErrorPrintf("failed to set receive timeout: %d\n", error);
   }
   
   host_entry = gethostbyname(host);
   if (host_entry != NULL) {
      struct sockaddr_in server_address = {0};
      server_address.sin_family = AF_INET;
      server_address.sin_family = AF_INET;
      server_address.sin_port = htons(port);
      server_address.sin_addr.s_addr = INADDR_ANY;
      memcpy((char *)&(server_address).sin_addr,
             (char *)host_entry->h_addr,
             host_entry->h_length);
      if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
         error = WSAGetLastError();
///         ErrorPrintf("failed to connect to host %s port %d: %d\n",
///                     host, (int)port, error);
         closesocket(client_socket);
         return false;
      }
   } else {
      error = WSAGetLastError();
///      ErrorPrintf("host %s unknown: %d\n",
///                  host, error);
      closesocket(client_socket);
      return false;
   }

   SERVICE_COMMAND_T request = {0};
   // used for address translatiuons (vpn, ...)
   int service_len = min(strlen(host), sizeof(request.service)-1);
   strncpy(request.service, host, service_len);
   request.signature = SERVICE_SIGNATURE;
   request.command = command;
   int nsend = send(client_socket, (const char *)&request, sizeof(request), 0);
   if (nsend < 0) {
      error = WSAGetLastError();
///      ErrorPrintf("failed to send to host %s port %d: %d\n",
///                  host, (int)port, error);
      closesocket(client_socket);
      return false;
   }

   struct sockaddr_in remote_addr = {0};
   int addr_len = sizeof(remote_addr);
   SERVICE_COMMAND_T response = {0};
   int nread = recvfrom(client_socket, (char*)&response, sizeof(response), 0, (struct sockaddr *)&remote_addr, &addr_len);
   if (nread < 0) {
      error = WSAGetLastError();
///      ErrorPrintf("failed to read from host %s port %d: %d\n",
///                  host, (int)port, error);
      closesocket(client_socket);
      return false;
   }
   ULONG_T len = sizeof(response);
   if (buf_size < len) {
      len = buf_size;
   }
   memcpy(response_buf, &response, len);
   closesocket(client_socket);
   return true;
}

BOOL_T cProxyService::Request(SOCKET socket, CONST_STRING_T host, UCHAR_T command, int & error,
                              void * response_buf, ULONG_T buf_size)
{
   unsigned short port = _Port;
   SOCKET client_socket = socket;
   int on = 1;
   if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
      error = WSAGetLastError();
      ErrorPrintf("failed to set socket option SO_REUSEADDR: %d\n", error);
   }
   if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&_ClientReceiveTimeout, sizeof(_ClientReceiveTimeout)) < 0) {
      error = WSAGetLastError();
      ErrorPrintf("failed to set receive timeout: %d\n", error);
   }
   SERVICE_COMMAND_T request = {0};
   // used for address translatiuons (vpn, ...)
   int service_len = min(strlen(host), sizeof(request.service)-1);
   strncpy(request.service, host, service_len);
   request.signature = SERVICE_SIGNATURE;
   request.command = command;
   int nsend = send(client_socket, (const char *)&request, sizeof(request), 0);
   if (nsend < 0) {
      error = WSAGetLastError();
      return false;
   }
   struct sockaddr_in remote_addr = {0};
   int addr_len = sizeof(remote_addr);
   SERVICE_COMMAND_T response = {0};
   int nread = recvfrom(client_socket, (char*)&response, sizeof(response), 0, (struct sockaddr *)&remote_addr, &addr_len);
   if (nread < 0) {
      error = WSAGetLastError();
      return false;
   }
   ULONG_T len = sizeof(response);
   if (buf_size < len) {
      len = buf_size;
   }
   memcpy(response_buf, &response, len);
   return true;
}

cProxy * cProxyService::CreateProxy(CONST_STRING_T serialized_proxy)
{
   cProxy * proxy = NULL;
   try {
      int object_type = cTransferObject::ObjectType(serialized_proxy);
      if (object_type == OT_CORBA_CELL_PROXY) {
         proxy = new cCorbaCellProxy;
      } else if (object_type == OT_COS_EVENTCHANNEL_PROXY) {
         proxy = new cCosEventChannelProxy;
      }
      if (proxy != NULL) {
         if (proxy->Construct(serialized_proxy)) {
         } else {
            RELEASE_OBJECT(proxy)
            proxy = NULL;
         }
      }
   } catch (cError & e) {
      ErrorPrintf("%s while constructing proxy\n", (const char *)e);
      proxy = NULL;
   } catch (...) {
      ErrorPrintf("unhandled exception while constructing proxy\n");
      proxy = NULL;
   }
   return proxy;
}

unsigned short cProxyService::Port()
{
   return _Port;
}

int cProxyService::HandleRequest(SOCKET s, CONST_STRING_T address)
{
   int error = 0;
   try {
      if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&_ServerReceiveTimeout, sizeof(_ServerReceiveTimeout)) < 0) {
         error = WSAGetLastError();
         ErrorPrintf("failed to set receive timeout: %d\n", error);
         return error;
      }

      SERVICE_COMMAND_T request = {0};
      int nread = recv(s, (char*)&request, sizeof(request), 0);
      if (nread < 0) {
         error = WSAGetLastError();
         ErrorPrintf("failed to read from socket %d: %d\n",
                     socket, error);
         return error;
      }
   
      if (request.service[0] != 0) {
         if (strcmp(address, request.service) != 0) {
            // translate adresses
            STRING_T new_service;
            if (_Process->TranslateAdresses(request.service, new_service)) {
               _Service = new_service;
            }
         }
      }

      SERVICE_COMMAND_T response = {0};
      response.signature = request.signature;
      response.command = request.command;
      response.sh_major = SHACIRA_MAJOR;
      response.sh_minor = SHACIRA_MINOR;
      response.sh_bug_fix = SHACIRA_BUG_FIX;
      int name_len = _ServiceName.size();
      if (sizeof(response.service_name) <= name_len) {
         name_len = sizeof(response.service_name) - 1;
      }
      memcpy(response.service_name, _ServiceName.c_str(), name_len);
      int service_len = _Service.size();
      if (sizeof(response.service) <= service_len) {
         service_len = sizeof(response.service) - 1;
      }
      memcpy(response.service, _Service.c_str(), service_len);
      int nsend = send(s, (const char *)&response, sizeof(response), 0);
      if (nsend < 0) {
         error = WSAGetLastError();
         ErrorPrintf("failed to send to socket %d: %d\n",
                    socket, error);
         return error;
      } 
      _Process->AddProxySender(address, DEFAULT_SENDER_PORT);
      return 0;
   } catch (...) {
      return -1;
   }
}

void cProxyService::HandleRequests()
{
   int error = 0;
   try {
      struct protoent * protoentry = NULL;
      if ((protoentry = getprotobyname("tcp")) == NULL)	{
         ErrorPrintf("proxy service failed to get tcp protocol: %d\n", WSAGetLastError());
         return;
      }
      if ((_Socket = socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
         ErrorPrintf("proxy service failed to get socket: %d\n", WSAGetLastError());
         return;
	   }
      int on = 1;
      if (setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
         InfoPrintf("proxy service failed to reuse address: %d", WSAGetLastError());
      }
      struct sockaddr_in ownaddress = {0};
      ownaddress.sin_family = AF_INET;
      ownaddress.sin_port = htons(_Port);
      ownaddress.sin_addr.s_addr = INADDR_ANY;
      if (bind(_Socket, (struct sockaddr *)&ownaddress, sizeof(ownaddress)) == -1) {
         ErrorPrintf("proxy service failed to bind to port %d: %d\n", _Port, WSAGetLastError());
         return;
	   }
      SOCKET incoming_socket = INVALID_SOCKET;
      struct sockaddr_in remoteaddress = {0};
      int address_length = sizeof(remoteaddress);
      const char * address = "unknown";
      if (listen(_Socket, 5) == -1) {
         ErrorPrintf("proxy service failed to listen to port %d: %d\n", _Port, WSAGetLastError());
         return;
      } else {
         InfoPrintf("proxy service listening on port: %d", _Port);
         while (!_StopRequest) {
            incoming_socket = accept(_Socket, (struct sockaddr *)&remoteaddress, &address_length);
            if (incoming_socket == INVALID_SOCKET) {
               int err = WSAGetLastError();
               if (err != WSAEINTR) {
                  ErrorPrintf("proxy service failed to accept on port %d: %d\n", _Port, err);
               }
               return;
            }
            address = inet_ntoa(((struct sockaddr_in *)(&remoteaddress))->sin_addr);
///            InfoPrintf("%s connected to proxy service\n", address);
            error = HandleRequest(incoming_socket, address);
            closesocket(incoming_socket);
         }
      }
   } catch (...) {
      ErrorPrintf("unhandled exception starting proxy service\n");
   }
}


