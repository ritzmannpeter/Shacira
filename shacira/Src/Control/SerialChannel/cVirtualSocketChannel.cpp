//## begin module%378B702202CC.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%378B702202CC.cm

//## begin module%378B702202CC.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%378B702202CC.cp

//## Module: cVirtualSocketChannel%378B702202CC; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cVirtualSocketChannel.cpp

//## begin module%378B702202CC.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%378B702202CC.additionalIncludes

//## begin module%378B702202CC.includes preserve=yes

#include "System/Sys/cSockets.h"

//## end module%378B702202CC.includes

// cError
#include "System/cError.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cSocketReceiver
#include "Control/SerialChannel/cSocketReceiver.h"
// cCharReceiver
#include "Control/SerialChannel/cCharReceiver.h"
// cVirtualSocketChannel
#include "Control/SerialChannel/cVirtualSocketChannel.h"
//## begin module%378B702202CC.additionalDeclarations preserve=yes
//## end module%378B702202CC.additionalDeclarations


// Class cVirtualSocketChannel 







cVirtualSocketChannel::cVirtualSocketChannel()
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%.hasinit preserve=no
      : _RXSocket(INVALID_SOCKET), _TXSocket(INVALID_SOCKET), _IPAddress("127.0.0.1"), _RXPort(20000), _TXPort(20001), _Receiver(NULL)
  //## end cVirtualSocketChannel::cVirtualSocketChannel%.hasinit
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%.initialization preserve=yes
  //## end cVirtualSocketChannel::cVirtualSocketChannel%.initialization
{
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%.body preserve=yes
  //## end cVirtualSocketChannel::cVirtualSocketChannel%.body
}

cVirtualSocketChannel::cVirtualSocketChannel(const cVirtualSocketChannel &right)
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%copy.hasinit preserve=no
      : _RXSocket(INVALID_SOCKET), _TXSocket(INVALID_SOCKET), _IPAddress("127.0.0.1"), _RXPort(20000), _TXPort(20001), _Receiver(NULL)
  //## end cVirtualSocketChannel::cVirtualSocketChannel%copy.hasinit
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%copy.initialization preserve=yes
  //## end cVirtualSocketChannel::cVirtualSocketChannel%copy.initialization
{
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cVirtualSocketChannel::cVirtualSocketChannel%copy.body
}

cVirtualSocketChannel::cVirtualSocketChannel (cConfigurationObject *config_obj)
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%1009995363.hasinit preserve=no
      : _RXSocket(INVALID_SOCKET), _TXSocket(INVALID_SOCKET), _IPAddress("127.0.0.1"), _RXPort(20000), _TXPort(20001), _Receiver(NULL)
  //## end cVirtualSocketChannel::cVirtualSocketChannel%1009995363.hasinit
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%1009995363.initialization preserve=yes
  //## end cVirtualSocketChannel::cVirtualSocketChannel%1009995363.initialization
{
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%1009995363.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   _IPAddress = config_obj->PropertyValue("IPAddress", _IPAddress.c_str());
   _RXPort = config_obj->PropertyValue("RXPort", _RXPort);
   _TXPort = config_obj->PropertyValue("TXPort", _TXPort);
   if (StartUp()) {
      SetSockets();
   }
  //## end cVirtualSocketChannel::cVirtualSocketChannel%1009995363.body
}

cVirtualSocketChannel::cVirtualSocketChannel (ULONG_T rx_port, ULONG_T tx_port)
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%1010072192.hasinit preserve=no
      : _RXSocket(INVALID_SOCKET), _TXSocket(INVALID_SOCKET), _IPAddress("127.0.0.1"), _RXPort(20000), _TXPort(20001), _Receiver(NULL)
  //## end cVirtualSocketChannel::cVirtualSocketChannel%1010072192.hasinit
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%1010072192.initialization preserve=yes
  //## end cVirtualSocketChannel::cVirtualSocketChannel%1010072192.initialization
{
  //## begin cVirtualSocketChannel::cVirtualSocketChannel%1010072192.body preserve=yes
   _RXPort = rx_port;
   _TXPort = tx_port;
   if (StartUp()) {
      SetSockets();
   }
  //## end cVirtualSocketChannel::cVirtualSocketChannel%1010072192.body
}


cVirtualSocketChannel::~cVirtualSocketChannel()
{
  //## begin cVirtualSocketChannel::~cVirtualSocketChannel%.body preserve=yes
   if (_RXSocket != INVALID_SOCKET) closesocket(_RXSocket);
   if (_TXSocket != INVALID_SOCKET) closesocket(_TXSocket);
  //## end cVirtualSocketChannel::~cVirtualSocketChannel%.body
}



//## Other Operations (implementation)
ULONG_T cVirtualSocketChannel::GetBaudRate ()
{
  //## begin cVirtualSocketChannel::GetBaudRate%1009995364.body preserve=yes
   return 0;
  //## end cVirtualSocketChannel::GetBaudRate%1009995364.body
}

void cVirtualSocketChannel::SetBaudRate (ULONG_T baud_rate)
{
  //## begin cVirtualSocketChannel::SetBaudRate%1009995365.body preserve=yes
  //## end cVirtualSocketChannel::SetBaudRate%1009995365.body
}

UCHAR_T cVirtualSocketChannel::GetStopBits ()
{
  //## begin cVirtualSocketChannel::GetStopBits%1009995366.body preserve=yes
   return 0;
  //## end cVirtualSocketChannel::GetStopBits%1009995366.body
}

void cVirtualSocketChannel::SetStopBits (UCHAR_T stop_bits)
{
  //## begin cVirtualSocketChannel::SetStopBits%1009995367.body preserve=yes
  //## end cVirtualSocketChannel::SetStopBits%1009995367.body
}

UCHAR_T cVirtualSocketChannel::GetStartBits ()
{
  //## begin cVirtualSocketChannel::GetStartBits%1009995368.body preserve=yes
   return 0;
  //## end cVirtualSocketChannel::GetStartBits%1009995368.body
}

void cVirtualSocketChannel::SetStartBits (UCHAR_T start_bits)
{
  //## begin cVirtualSocketChannel::SetStartBits%1009995369.body preserve=yes
  //## end cVirtualSocketChannel::SetStartBits%1009995369.body
}

UCHAR_T cVirtualSocketChannel::GetCharLen ()
{
  //## begin cVirtualSocketChannel::GetCharLen%1009995370.body preserve=yes
   return 0;
  //## end cVirtualSocketChannel::GetCharLen%1009995370.body
}

void cVirtualSocketChannel::SetCharLen (UCHAR_T data_len)
{
  //## begin cVirtualSocketChannel::SetCharLen%1009995371.body preserve=yes
  //## end cVirtualSocketChannel::SetCharLen%1009995371.body
}

ParityTypes cVirtualSocketChannel::GetParity ()
{
  //## begin cVirtualSocketChannel::GetParity%1009995372.body preserve=yes
   return UndefinedParity;
  //## end cVirtualSocketChannel::GetParity%1009995372.body
}

void cVirtualSocketChannel::SetParity (ParityTypes parity)
{
  //## begin cVirtualSocketChannel::SetParity%1009995373.body preserve=yes
  //## end cVirtualSocketChannel::SetParity%1009995373.body
}

HandshakeTypes cVirtualSocketChannel::GetHandshake ()
{
  //## begin cVirtualSocketChannel::GetHandshake%1009995374.body preserve=yes
   return UndefinedHandshake;
  //## end cVirtualSocketChannel::GetHandshake%1009995374.body
}

void cVirtualSocketChannel::SetHandshake (HandshakeTypes handshake)
{
  //## begin cVirtualSocketChannel::SetHandshake%1009995375.body preserve=yes
  //## end cVirtualSocketChannel::SetHandshake%1009995375.body
}

ULONG_T cVirtualSocketChannel::GetTimeout ()
{
  //## begin cVirtualSocketChannel::GetTimeout%1009995376.body preserve=yes
   return 0;
  //## end cVirtualSocketChannel::GetTimeout%1009995376.body
}

void cVirtualSocketChannel::SetTimeout (ULONG_T timeout)
{
  //## begin cVirtualSocketChannel::SetTimeout%1009995377.body preserve=yes
  //## end cVirtualSocketChannel::SetTimeout%1009995377.body
}

void cVirtualSocketChannel::GetState (COM_STATE_T *state)
{
  //## begin cVirtualSocketChannel::GetState%1014886110.body preserve=yes
  //## end cVirtualSocketChannel::GetState%1014886110.body
}

void cVirtualSocketChannel::Open ()
{
  //## begin cVirtualSocketChannel::Open%1009995378.body preserve=yes
  //## end cVirtualSocketChannel::Open%1009995378.body
}

void cVirtualSocketChannel::Close ()
{
  //## begin cVirtualSocketChannel::Close%1009995379.body preserve=yes
  //## end cVirtualSocketChannel::Close%1009995379.body
}

void cVirtualSocketChannel::Reset (INT_T type)
{
  //## begin cVirtualSocketChannel::Reset%1014806625.body preserve=yes
  //## end cVirtualSocketChannel::Reset%1014806625.body
}

LONG_T cVirtualSocketChannel::Read (UCHAR_T *buffer, ULONG_T amount, ULONG_T timeout)
{
  //## begin cVirtualSocketChannel::Read%1009995380.body preserve=yes
   long rc = _Receiver->Get((char*)buffer, amount, timeout);
   if (_Verbose) PrintBuf((const char *)buffer, rc, CHANNEL_INPUT);
   return rc;
  //## end cVirtualSocketChannel::Read%1009995380.body
}

LONG_T cVirtualSocketChannel::Write (UCHAR_T *buffer, ULONG_T amount)
{
  //## begin cVirtualSocketChannel::Write%1009995381.body preserve=yes
   if (_Verbose) PrintBuf((const char *)buffer, amount, CHANNEL_OUTPUT);
   struct sockaddr_in addr = {0};
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = inet_addr(_IPAddress.c_str());
   addr.sin_port = htons((unsigned short)_TXPort);
   int flags = 0;
   int nwrite = sendto(_TXSocket, (char*)buffer, amount, flags, (struct sockaddr *)&addr, sizeof(addr));
   if (nwrite < 0) {
      int err_code = WSAGetLastError();
      InfoPrintf("sendto returns %d\n", err_code);
#ifndef REPORT_ONLY
      throw cError(SOCKET_SENDTO, err_code);
#endif
      return err_code;
   } else {
      return nwrite;
   }
  //## end cVirtualSocketChannel::Write%1009995381.body
}

void cVirtualSocketChannel::FlushInput ()
{
  //## begin cVirtualSocketChannel::FlushInput%1009995382.body preserve=yes
   _Receiver->Flush();
  //## end cVirtualSocketChannel::FlushInput%1009995382.body
}

void cVirtualSocketChannel::FlushOutput ()
{
  //## begin cVirtualSocketChannel::FlushOutput%1009995383.body preserve=yes
  //## end cVirtualSocketChannel::FlushOutput%1009995383.body
}

BOOL_T cVirtualSocketChannel::StartUp ()
{
  //## begin cVirtualSocketChannel::StartUp%1010072191.body preserve=yes
   cSockets::Initialize();
   return true;
  //## end cVirtualSocketChannel::StartUp%1010072191.body
}

BOOL_T cVirtualSocketChannel::SetSockets ()
{
  //## begin cVirtualSocketChannel::SetSockets%1010072193.body preserve=yes
   int err = 0;
   int on = 1;
   struct sockaddr_in client_addr = {0};
   if ((_RXSocket = socket(AF_INET, SOCK_DGRAM, 0)) != INVALID_SOCKET) {
      if (setsockopt(_RXSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
         int err_code = WSAGetLastError();
         InfoPrintf("setsockopt SO_REUSEADDR on RXSocket returns %d\n", err_code);
#ifndef REPORT_ONLY
         throw cError(SOCKET_SETSOCKOPT, err_code, "SO_REUSEADDR", "RXSocket");
#endif
      }
      client_addr.sin_family = AF_INET;
      client_addr.sin_addr.s_addr = INADDR_ANY;
      client_addr.sin_port = htons((unsigned short)_RXPort);
      if (bind(_RXSocket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0) {
         _Receiver = new cSocketReceiver(_RXSocket);
      } else {
         throw cError(SOCKET_BIND, WSAGetLastError(), "RXSocket");
      }
   } else {
      throw cError(SOCKET_CREATE, WSAGetLastError(), "RXSocket");
   }
   if ((_TXSocket = socket(AF_INET, SOCK_DGRAM, 0)) != INVALID_SOCKET) {
      if (setsockopt(_RXSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
         int err_code = WSAGetLastError();
         InfoPrintf("setsockopt SO_REUSEADDR on TXSocket returns %d\n", err_code);
#ifndef REPORT_ONLY
         throw cError(SOCKET_SETSOCKOPT, err_code, "SO_REUSEADDR", "TXSocket");
#endif
      }
   } else {
      throw cError(SOCKET_CREATE, WSAGetLastError(), "TXSocket");
   }
   return true;
  //## end cVirtualSocketChannel::SetSockets%1010072193.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cVirtualSocketChannel::get_IPAddress () const
{
  //## begin cVirtualSocketChannel::get_IPAddress%378B70590112.get preserve=no
  return _IPAddress;
  //## end cVirtualSocketChannel::get_IPAddress%378B70590112.get
}

void cVirtualSocketChannel::set_IPAddress (STRING_T value)
{
  //## begin cVirtualSocketChannel::set_IPAddress%378B70590112.set preserve=no
  _IPAddress = value;
  //## end cVirtualSocketChannel::set_IPAddress%378B70590112.set
}

ULONG_T cVirtualSocketChannel::get_RXPort () const
{
  //## begin cVirtualSocketChannel::get_RXPort%3C3430360057.get preserve=no
  return _RXPort;
  //## end cVirtualSocketChannel::get_RXPort%3C3430360057.get
}

void cVirtualSocketChannel::set_RXPort (ULONG_T value)
{
  //## begin cVirtualSocketChannel::set_RXPort%3C3430360057.set preserve=no
  _RXPort = value;
  //## end cVirtualSocketChannel::set_RXPort%3C3430360057.set
}

ULONG_T cVirtualSocketChannel::get_TXPort () const
{
  //## begin cVirtualSocketChannel::get_TXPort%3C34306000B2.get preserve=no
  return _TXPort;
  //## end cVirtualSocketChannel::get_TXPort%3C34306000B2.get
}

void cVirtualSocketChannel::set_TXPort (ULONG_T value)
{
  //## begin cVirtualSocketChannel::set_TXPort%3C34306000B2.set preserve=no
  _TXPort = value;
  //## end cVirtualSocketChannel::set_TXPort%3C34306000B2.set
}

// Additional Declarations
  //## begin cVirtualSocketChannel%378B702202CC.declarations preserve=yes
  //## end cVirtualSocketChannel%378B702202CC.declarations

//## begin module%378B702202CC.epilog preserve=yes
//## end module%378B702202CC.epilog
