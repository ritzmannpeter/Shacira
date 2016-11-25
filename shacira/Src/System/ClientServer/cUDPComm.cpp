//## begin module%410281A302BF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%410281A302BF.cm

//## begin module%410281A302BF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%410281A302BF.cp

//## Module: cUDPComm%410281A302BF; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cUDPComm.cpp

//## begin module%410281A302BF.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%410281A302BF.additionalIncludes

//## begin module%410281A302BF.includes preserve=yes
#include "System/ClientServer/cs.h"
//## end module%410281A302BF.includes

// cUDPComm
#include "System/ClientServer/cUDPComm.h"
//## begin module%410281A302BF.additionalDeclarations preserve=yes
//## end module%410281A302BF.additionalDeclarations


// Class cUDPComm 






cUDPComm::cUDPComm()
  //## begin cUDPComm::cUDPComm%.hasinit preserve=no
      : _ReadPort(0), _WritePort(0), _ReadSocket(INVALID_SOCKET), _WriteSocket(INVALID_SOCKET), _Host(NULL)
  //## end cUDPComm::cUDPComm%.hasinit
  //## begin cUDPComm::cUDPComm%.initialization preserve=yes
  //## end cUDPComm::cUDPComm%.initialization
{
  //## begin cUDPComm::cUDPComm%.body preserve=yes
   if ((_ReadSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
      int err = WSAGetLastError();
      throw cError(SOCKET_CREATE, err, "0.0.0.0",
                   cConvUtils::StringValue(_ReadPort).c_str());
   }
   if ((_WriteSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
      int err = WSAGetLastError();
      throw cError(SOCKET_CREATE, err, "0.0.0.0",
                   cConvUtils::StringValue(_WritePort).c_str());
   }
  //## end cUDPComm::cUDPComm%.body
}

cUDPComm::cUDPComm(const cUDPComm &right)
  //## begin cUDPComm::cUDPComm%copy.hasinit preserve=no
      : _ReadPort(0), _WritePort(0), _ReadSocket(INVALID_SOCKET), _WriteSocket(INVALID_SOCKET), _Host(NULL)
  //## end cUDPComm::cUDPComm%copy.hasinit
  //## begin cUDPComm::cUDPComm%copy.initialization preserve=yes
  //## end cUDPComm::cUDPComm%copy.initialization
{
  //## begin cUDPComm::cUDPComm%copy.body preserve=yes
   _ReadPort = right._ReadPort;
   _WritePort = right._WritePort;
   _ReadSocket = right._ReadSocket;
   _WriteSocket = right._WriteSocket;
  //## end cUDPComm::cUDPComm%copy.body
}

cUDPComm::cUDPComm (unsigned short read_port, unsigned short write_port, const char *host)
  //## begin cUDPComm::cUDPComm%1090681461.hasinit preserve=no
      : _ReadPort(0), _WritePort(0), _ReadSocket(INVALID_SOCKET), _WriteSocket(INVALID_SOCKET), _Host(NULL)
  //## end cUDPComm::cUDPComm%1090681461.hasinit
  //## begin cUDPComm::cUDPComm%1090681461.initialization preserve=yes
  //## end cUDPComm::cUDPComm%1090681461.initialization
{
  //## begin cUDPComm::cUDPComm%1090681461.body preserve=yes
   _ReadPort = read_port;
   _WritePort = write_port;
   _Host = host;
   if ((_ReadSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
      int err = WSAGetLastError();
      throw cError(SOCKET_CREATE, err, "0.0.0.0",
                   cConvUtils::StringValue(_ReadPort).c_str());
   }
   if ((_WriteSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
      int err = WSAGetLastError();
      throw cError(SOCKET_CREATE, err, "0.0.0.0",
                   cConvUtils::StringValue(_WritePort).c_str());
   }
   int on = 1;
   if (setsockopt(_ReadSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
      int err = WSAGetLastError();
      throw cError(SOCKET_SETSOCKOPT, err, "SO_REUSEADDR", "0.0.0.0",
                   cConvUtils::StringValue(_ReadPort).c_str());
   }
   cInetAddress * address = new cInetAddress(_ReadPort);
   SOCK_ADDRESS_PTR rcv_addr = address->SockAddr();
   if (bind(_ReadSocket, rcv_addr, sizeof(*rcv_addr)) != 0) {
      int err = WSAGetLastError();
      throw cError(SOCKET_BIND, err, "0.0.0.0",
                   cConvUtils::StringValue(_ReadPort).c_str());
   }
   _ReadAddress = address;
   if (address->InetAddr()->sin_addr.s_addr == INADDR_ANY) {
      InfoPrintf("listening to any address port %d\n", address->Port());
   }
   else {
       InfoPrintf("listening to %s port %d\n", address->InetAddress(), address->Port());
   }
   if (host != NULL) {
      address = new cInetAddress(_WritePort, _Host);
      _WriteAddress = address;
      InfoPrintf("writing to %s port %d\n", address->InetAddress(), address->Port());
   }
  //## end cUDPComm::cUDPComm%1090681461.body
}


cUDPComm::~cUDPComm()
{
  //## begin cUDPComm::~cUDPComm%.body preserve=yes
   if (_ReadSocket != INVALID_SOCKET) {
      closesocket(_ReadSocket);
   }
   if (_WriteSocket != INVALID_SOCKET) {
      closesocket(_WriteSocket);
   }
  //## end cUDPComm::~cUDPComm%.body
}



//## Other Operations (implementation)
void cUDPComm::Send (cCSMsg *msg, cCSAddress *address)
{
  //## begin cUDPComm::Send%1090681458.body preserve=yes
   cInetAddress * inet_address = NULL;
   if (address == NULL) {
      if (_WriteAddress == NULL) {
         return;
      } else {
         inet_address = (cInetAddress*)_WriteAddress;
      }
   } else {
      inet_address = (cInetAddress*)address;
   }
   SOCK_ADDRESS_PTR destination = inet_address->SockAddr();
   socklen_t addr_size = sizeof(*destination);
   PTR_T msg_buf = msg->Data();
   ULONG_T msg_len = msg->DataSize();
   if (msg_len > 0) {
      long nwrite = sendto(_WriteSocket, (char*)msg_buf, msg_len, 0, destination, addr_size);
      if (nwrite < 0) {
         int err = WSAGetLastError();
         throw cError(SOCKET_SENDTO, err,
                      inet_address->InetAddress(),
                      cConvUtils::StringValue(_WritePort).c_str(),
                      cConvUtils::StringValue(msg_len).c_str());
      }
   } else {
      ErrorPrintf("null message\n");
   }
  //## end cUDPComm::Send%1090681458.body
}

void cUDPComm::Reply (cCSMsg *msg, cCSAddress *client_address)
{
  //## begin cUDPComm::Reply%1090862817.body preserve=yes
   cInetAddress * address = (cInetAddress*)client_address;
   address->SetPort(_WritePort);
   Send(msg, address);
  //## end cUDPComm::Reply%1090862817.body
}

void cUDPComm::Receive (cCSMsg &msg, cCSAddress *sender_address, ULONG_T tmo)
{
  //## begin cUDPComm::Receive%1090681459.body preserve=yes
   SetReadTimeout(tmo);
   SOCK_ADDRESS_T source = {0};
   socklen_t addr_size = sizeof(source);
   PTR_T msg_buf = msg.Data();
   ULONG_T msg_buf_size = msg.DataSize();
   long nread = recvfrom(_ReadSocket, (char*)msg_buf, msg_buf_size, 0, &source, &addr_size);
   if (nread < 0) {
      msg.SetAppDataSize(0);
      int err = WSAGetLastError();
      if (!TIMED_OUT(err)) {
         throw cError(SOCKET_RECVFROM, err,
                      "0.0.0.0",
                      cConvUtils::StringValue(_ReadPort).c_str());
      }
   } else {
      msg.SetAppDataSize(nread);
      cInetAddress * a = (cInetAddress*)sender_address;
      a->SetAddress(&source);
      if (_WriteAddress == NULL) {
         cInetAddress * address = new cInetAddress(*a);
         address->SetPort(_WritePort);
         InfoPrintf("writing to %s port %d\n", address->InetAddress(), address->Port());
         _WriteAddress = address;
      }
      return;
   }
  //## end cUDPComm::Receive%1090681459.body
}

LONG_T cUDPComm::Receive (PTR_T buf, ULONG_T buf_size, cCSAddress *sender_address, ULONG_T tmo)
{
  //## begin cUDPComm::Receive%1107416647.body preserve=yes
   SetReadTimeout(tmo);
   SOCK_ADDRESS_T source = {0};
   socklen_t addr_size = sizeof(source);
   long nread = recvfrom(_ReadSocket, (char*)buf, buf_size, 0, &source, &addr_size);
   if (nread < 0) {
      int err = WSAGetLastError();
      if (!TIMED_OUT(err)) {
         throw cError(SOCKET_RECVFROM, err,
                      "0.0.0.0",
                      cConvUtils::StringValue(_ReadPort).c_str());
      } else {
         return 0;
      }
   } else {
      cInetAddress * a = (cInetAddress*)sender_address;
      a->SetAddress(&source);
      if (_WriteAddress == NULL) {
         cInetAddress * address = new cInetAddress(*a);
         address->SetPort(_WritePort);
         _WriteAddress = address;
      }
      return nread;
   }
  //## end cUDPComm::Receive%1107416647.body
}

cCSAddress * cUDPComm::ReadAddress ()
{
  //## begin cUDPComm::ReadAddress%1090862812.body preserve=yes
   return _ReadAddress;
  //## end cUDPComm::ReadAddress%1090862812.body
}

cCSAddress * cUDPComm::WriteAddress ()
{
  //## begin cUDPComm::WriteAddress%1090862813.body preserve=yes
   return _WriteAddress;
  //## end cUDPComm::WriteAddress%1090862813.body
}

void cUDPComm::SetReadTimeout (ULONG_T tmo)
{
  //## begin cUDPComm::SetReadTimeout%1090681470.body preserve=yes
   if (setsockopt(_ReadSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tmo, sizeof(tmo)) < 0) {
      int err = WSAGetLastError();
      throw cError(SOCKET_SETSOCKOPT, err, "SO_RCVTIMEO", "0.0.0.0",
                   cConvUtils::StringValue(_ReadPort).c_str());
   }
  //## end cUDPComm::SetReadTimeout%1090681470.body
}

// Additional Declarations
  //## begin cUDPComm%410281A302BF.declarations preserve=yes
  //## end cUDPComm%410281A302BF.declarations

//## begin module%410281A302BF.epilog preserve=yes
//## end module%410281A302BF.epilog
