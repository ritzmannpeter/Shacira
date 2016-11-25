//## begin module%3C552714024C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C552714024C.cm

//## begin module%3C552714024C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C552714024C.cp

//## Module: cProxyService%3C552714024C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxyService.h

#ifndef cProxyService_h
#define cProxyService_h 1

#include "base/eb_thread.hpp"
#include "Orb/cCorbaCellProxy.h"
#include "Orb/cCosEventChannelProxy.h"
#include "System/Sys/cSockets.h"

class cSHProcess;
class cCellProxy;
class cProxy;
class cConvUtils;
class cChannelProxy;
class cCosEventChannelProxy;
class cCorbaCellProxy;

#define DEFAULT_CONNECTION_PORT     21010
#define DEFAULT_SENDER_PORT         21001

#define SERVICE_SIGNATURE           0x12345678
#define DEFAULT_SERVICE_RECEIVE_TIMEOUT   2000
#define DEFAULT_CLIENT_RECEIVE_TIMEOUT    500

/// commands
#define SI_INFO                     1
#define SI_PROXY                    2

#define NAME_MAX_LEN                0x60
#define IOR_MAX_LEN                 0x200
typedef struct _service_command {
   ULONG_T signature;
   UCHAR_T command;
   char service_name[NAME_MAX_LEN];
   char service[IOR_MAX_LEN];
   UCHAR_T sh_major;
   UCHAR_T sh_minor;
   UCHAR_T sh_bug_fix;
}  SERVICE_COMMAND_T;

class cProxyService : public cThread
{
public:
   cProxyService(cSHProcess * process, unsigned short port = DEFAULT_CONNECTION_PORT);
   cProxyService(cSHProcess * process, CONST_STRING_T service, CONST_STRING_T service_name,
                 unsigned short port = DEFAULT_CONNECTION_PORT);
   ~cProxyService();
   virtual INT_T onMain(void *extra);
   void Start();
   void Stop();
   BOOL_T Request(CONST_STRING_T host, UCHAR_T command, int & error,
                  void * response_buf, ULONG_T buf_size);
   BOOL_T Request(SOCKET socket, CONST_STRING_T host, UCHAR_T command, int & error,
                  void * response_buf, ULONG_T buf_size);
   cProxy * CreateProxy(CONST_STRING_T serialized_proxy);
   unsigned short Port();
protected:
   unsigned short _Port;
   cSHProcess * _Process;
   STRING_T _Service;
   STRING_T _ServiceName;
private:
   void InitServer();
   int HandleRequest(SOCKET s, CONST_STRING_T host);
   void HandleRequests();
private:
   BOOL_T _Active;
   BOOL_T _StopRequest;
   SOCKET _Socket;
   int _ClientReceiveTimeout;
   int _ServerReceiveTimeout;
};

#endif
