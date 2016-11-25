
#include "cUDPInterface.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"

bool cUDPInterface::_Initialized = false;

cUDPInterface::cUDPInterface(unsigned short server_port,
                             unsigned short reply_port)
{
   _LastError = 0;
   _ServerPort = server_port;
   _ReplyPort = reply_port;
}

cUDPInterface::~cUDPInterface()
{
}

int cUDPInterface::LastError()
{
   return _LastError;
}

bool cUDPInterface::InitializeSockets()
{
   bool success = false;
   if (!_Initialized) {
      success = StartSockets();
      if (!success) {
         return false;
      } else {
         _Initialized = true;
      }
   }
   return true;
}

int cUDPInterface::SendTo(void * buf, unsigned long bytes,
                          struct sockaddr_in * destination)
{
   int addr_size = sizeof(*destination);
   long nwrite = sendto(_Socket, (char*)buf, bytes, 0,
                        (struct sockaddr*)destination, addr_size);
   if (nwrite < 0) {
      _LastError = WSAGetLastError();
      return -1;
   } else {
      return nwrite;
   }
}

int cUDPInterface::ReceiveFrom(void * buf, unsigned long buf_size,
                                  struct sockaddr_in * source,
                                  unsigned long timeout)
{
   if (!SetTimeout(timeout)) return -1;
   int addr_size = sizeof(*source);
   long nread = recvfrom(_Socket, (char*)buf, buf_size, 0,
                         (struct sockaddr*)source, &addr_size);
   if (nread < 0) {
      int err_code = WSAGetLastError();
      if (err_code == WSAETIMEDOUT) {
         return 0;
      } else {
         _LastError = err_code;
         return -1;
      }
   } else {
      return nread;
   }
}

bool cUDPInterface::StartSockets()
{
   WORD req_version = MAKEWORD(2, 2);
   WSADATA wsa_data;
   int err = WSAStartup(req_version, &wsa_data);
   if (err != 0) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      return false;
   }
   /* Confirm that the WinSock DLL supports 2.2.*/
   /* Note that if the DLL supports versions greater    */
   /* than 2.2 in addition to 2.2, it will still return */
   /* 2.2 in wVersion since that is the version we      */
   /* requested.                                        */
   if (LOBYTE(wsa_data.wVersion) != 2 ||
       HIBYTE(wsa_data.wVersion) != 2) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      WSACleanup();
      return false;
   }
   /* The WinSock DLL is acceptable. Proceed. */
   return true;
}

unsigned int cUDPInterface::GetFreePortNum()
{
   return (GetCurrentProcessId() + (rand() % 200)) + 20000;
}

bool cUDPInterface::SetTimeout(unsigned long timeout)
{
   if (setsockopt(_Socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
      int _LastError = WSAGetLastError();
      return false;
   }
   return true;
}

const char * cUDPInterface::InetAddress(struct sockaddr_in * addr)
{
   memset(_TempBuf, 0, sizeof(_TempBuf));
   sprintf(_TempBuf, "%s:%d", inet_ntoa(addr->sin_addr), htons(addr->sin_port));
   return _TempBuf;
}

