//## begin module%3DD3932702C4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD3932702C4.cm

//## begin module%3DD3932702C4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD3932702C4.cp

//## Module: cSocketConsole%3DD3932702C4; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cSocketConsole.cpp

//## begin module%3DD3932702C4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DD3932702C4.additionalIncludes

//## begin module%3DD3932702C4.includes preserve=yes
//## end module%3DD3932702C4.includes

// cSocketConsole
#include "System/Console/cSocketConsole.h"
// cSockets
#include "System/Sys/cSockets.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
//## begin module%3DD3932702C4.additionalDeclarations preserve=yes
//## end module%3DD3932702C4.additionalDeclarations


// Class cSocketConsole 




cSocketConsole::cSocketConsole()
  //## begin cSocketConsole::cSocketConsole%.hasinit preserve=no
      : _IPAddress("127.0.0.1"), _Port(0), _Socket(INVALID_SOCKET)
  //## end cSocketConsole::cSocketConsole%.hasinit
  //## begin cSocketConsole::cSocketConsole%.initialization preserve=yes
  //## end cSocketConsole::cSocketConsole%.initialization
{
  //## begin cSocketConsole::cSocketConsole%.body preserve=yes
_ASSERT_UNCOND
  //## end cSocketConsole::cSocketConsole%.body
}

cSocketConsole::cSocketConsole(const cSocketConsole &right)
  //## begin cSocketConsole::cSocketConsole%copy.hasinit preserve=no
      : _IPAddress("127.0.0.1"), _Port(0), _Socket(INVALID_SOCKET)
  //## end cSocketConsole::cSocketConsole%copy.hasinit
  //## begin cSocketConsole::cSocketConsole%copy.initialization preserve=yes
  //## end cSocketConsole::cSocketConsole%copy.initialization
{
  //## begin cSocketConsole::cSocketConsole%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSocketConsole::cSocketConsole%copy.body
}

cSocketConsole::cSocketConsole (CONST_STRING_T ip_address, ULONG_T port, INT_T direction)
  //## begin cSocketConsole::cSocketConsole%1037267677.hasinit preserve=no
      : _IPAddress("127.0.0.1"), _Port(0), _Socket(INVALID_SOCKET)
  //## end cSocketConsole::cSocketConsole%1037267677.hasinit
  //## begin cSocketConsole::cSocketConsole%1037267677.initialization preserve=yes
  , cConsole(direction)
  //## end cSocketConsole::cSocketConsole%1037267677.initialization
{
  //## begin cSocketConsole::cSocketConsole%1037267677.body preserve=yes
   _IPAddress = ip_address;
   _Port = port;
   SetSockets();
  //## end cSocketConsole::cSocketConsole%1037267677.body
}


cSocketConsole::~cSocketConsole()
{
  //## begin cSocketConsole::~cSocketConsole%.body preserve=yes
  //## end cSocketConsole::~cSocketConsole%.body
}



//## Other Operations (implementation)
void cSocketConsole::Write (CONST_STRING_T text)
{
  //## begin cSocketConsole::Write%1037267678.body preserve=yes
   CHECK_DIRECTION(DIRECTION_OUTPUT)
   if (_Socket == INVALID_SOCKET) return;
   Send(text);
  //## end cSocketConsole::Write%1037267678.body
}

LONG_T cSocketConsole::Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout)
{
  //## begin cSocketConsole::Read%1037267679.body preserve=yes
   CHECK_DIRECTION(DIRECTION_INPUT)
   if (_Socket == INVALID_SOCKET) return 0;
   return Receive(buf, buf_size, timeout);
  //## end cSocketConsole::Read%1037267679.body
}

void cSocketConsole::FlushInput ()
{
  //## begin cSocketConsole::FlushInput%1037267680.body preserve=yes
  //## end cSocketConsole::FlushInput%1037267680.body
}

void cSocketConsole::FlushOutput ()
{
  //## begin cSocketConsole::FlushOutput%1037267681.body preserve=yes
  //## end cSocketConsole::FlushOutput%1037267681.body
}

void cSocketConsole::SetSockets ()
{
  //## begin cSocketConsole::SetSockets%1037267682.body preserve=yes
   int on = 1;
   if (_Port != 0) {
      if (_Direction == DIRECTION_OUTPUT) {
         if ((_Socket = socket(AF_INET, SOCK_DGRAM, 0)) != INVALID_SOCKET) {
      		if (setsockopt(_Socket, SOL_SOCKET, SO_BROADCAST, (const char*)&on, sizeof(on)) < 0) {
               throw cError(SOCKET_SETSOCKOPT, WSAGetLastError(), _IPAddress.c_str(),
                           cConvUtils::StringValue(_Port).c_str(), "SO_BROADCAST");
   		   }
            if (setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
               throw cError(SOCKET_SETSOCKOPT, WSAGetLastError(), _IPAddress.c_str(),
                           cConvUtils::StringValue(_Port).c_str(), "SO_REUSEADDR");
            }
         } else {
            throw cError(SOCKET_CREATE, WSAGetLastError(), _IPAddress.c_str(),
                        cConvUtils::StringValue(_Port).c_str());
         }
      } else if (_Direction == DIRECTION_INPUT) {
         struct sockaddr_in client_addr = {0};
         if ((_Socket = socket(AF_INET, SOCK_DGRAM, 0)) != INVALID_SOCKET) {
            if (setsockopt(_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
               throw cError(SOCKET_SETSOCKOPT, WSAGetLastError(), _IPAddress.c_str(),
                           cConvUtils::StringValue(_Port).c_str(), "SO_REUSEADDR");
            }
            client_addr.sin_family = AF_INET;
            client_addr.sin_addr.s_addr = INADDR_ANY;
            client_addr.sin_port = htons((unsigned short)_Port);
            if (!bind(_Socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0) {
               throw cError(SOCKET_BIND, WSAGetLastError(), _IPAddress.c_str(),
                           cConvUtils::StringValue(_Port).c_str());
            }
         } else {
            throw cError(SOCKET_CREATE, WSAGetLastError(), _IPAddress.c_str(),
                        cConvUtils::StringValue(_Port).c_str());
         }
      }
   }
  //## end cSocketConsole::SetSockets%1037267682.body
}

void cSocketConsole::CloseSockets ()
{
  //## begin cSocketConsole::CloseSockets%1037267683.body preserve=yes
  //## end cSocketConsole::CloseSockets%1037267683.body
}

LONG_T cSocketConsole::Receive (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout)
{
  //## begin cSocketConsole::Receive%1037267686.body preserve=yes
   if (_Socket == INVALID_SOCKET) {
      cSystemUtils::Suspend(100);
      return 0;
   }
   cSockets::SetReceiveTimeout(_Socket, timeout);
   struct sockaddr addr = {0};
   socklen_t addr_size = sizeof(addr);
   int flags = 0;
   int nreceive = recvfrom(_Socket, buf, buf_size, flags, &addr, &addr_size);
   if (nreceive < 0) {
      int err_code = WSAGetLastError();
      if (!TIMED_OUT(err_code)) {
         throw cError(SOCKET_RECVFROM, WSAGetLastError(), _IPAddress.c_str(),
                      cConvUtils::StringValue(_Port).c_str());
      }
      return 0;
   } else {
      if ((long)buf_size >= nreceive) {
         // ??
         // memcpy((void*)buf, buf, nreceive);
         return nreceive;
      } else {
         throw cError(SOCKET_BUF_TOO_SMALL, 0, _IPAddress.c_str(),
                      cConvUtils::StringValue(_Port).c_str(),
                      cConvUtils::StringValue(nreceive).c_str(),
                      cConvUtils::StringValue(buf_size).c_str());
      }
   }
  //## end cSocketConsole::Receive%1037267686.body
}

void cSocketConsole::Send (CONST_STRING_T msg)
{
  //## begin cSocketConsole::Send%1037267687.body preserve=yes
   if (_Socket == INVALID_SOCKET) {
      cSystemUtils::Suspend(1000);
      return;
   }
   unsigned long msg_size = strlen(msg);
   struct sockaddr_in addr = {0};
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = inet_addr(_IPAddress.c_str());
   addr.sin_port = htons((unsigned short)_Port);
   int flags = 0;
   int nsend = sendto(_Socket, (char*)msg, msg_size, flags, (struct sockaddr *)&addr, sizeof(addr));
   if (nsend < 0) {
      throw cError(SOCKET_SENDTO, WSAGetLastError(), _IPAddress.c_str(),
                   cConvUtils::StringValue(_Port).c_str());
   }
  //## end cSocketConsole::Send%1037267687.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cSocketConsole::get_IPAddress () const
{
  //## begin cSocketConsole::get_IPAddress%3DD393AF0297.get preserve=no
  return _IPAddress;
  //## end cSocketConsole::get_IPAddress%3DD393AF0297.get
}

ULONG_T cSocketConsole::get_Port () const
{
  //## begin cSocketConsole::get_Port%3DD393AF02A1.get preserve=no
  return _Port;
  //## end cSocketConsole::get_Port%3DD393AF02A1.get
}

// Additional Declarations
  //## begin cSocketConsole%3DD3932702C4.declarations preserve=yes
  //## end cSocketConsole%3DD3932702C4.declarations

//## begin module%3DD3932702C4.epilog preserve=yes
//## end module%3DD3932702C4.epilog
