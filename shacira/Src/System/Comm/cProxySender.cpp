//## begin module%3C5ED32D01D2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C5ED32D01D2.cm

//## begin module%3C5ED32D01D2.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C5ED32D01D2.cp

//## Module: cProxySender%3C5ED32D01D2; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxySender.cpp

//## begin module%3C5ED32D01D2.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C5ED32D01D2.additionalIncludes

//## begin module%3C5ED32D01D2.includes preserve=yes
//## end module%3C5ED32D01D2.includes

// cProxy
#include "System/Objects/cProxy.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cProxySender
#include "System/Comm/cProxySender.h"
//## begin module%3C5ED32D01D2.additionalDeclarations preserve=yes
//## end module%3C5ED32D01D2.additionalDeclarations


// Class cProxySender 




cProxySender::cProxySender()
  //## begin cProxySender::cProxySender%.hasinit preserve=no
      : _IPAddress("127.0.0.1"), _Port(0), _Socket(INVALID_SOCKET)
  //## end cProxySender::cProxySender%.hasinit
  //## begin cProxySender::cProxySender%.initialization preserve=yes
  //## end cProxySender::cProxySender%.initialization
{
  //## begin cProxySender::cProxySender%.body preserve=yes
  //## end cProxySender::cProxySender%.body
}

cProxySender::cProxySender(const cProxySender &right)
  //## begin cProxySender::cProxySender%copy.hasinit preserve=no
      : _IPAddress("127.0.0.1"), _Port(0), _Socket(INVALID_SOCKET)
  //## end cProxySender::cProxySender%copy.hasinit
  //## begin cProxySender::cProxySender%copy.initialization preserve=yes
  //## end cProxySender::cProxySender%copy.initialization
{
  //## begin cProxySender::cProxySender%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProxySender::cProxySender%copy.body
}

cProxySender::cProxySender (CONST_STRING_T ip_addr, ULONG_T port)
  //## begin cProxySender::cProxySender%1012812258.hasinit preserve=no
      : _IPAddress("127.0.0.1"), _Port(0), _Socket(INVALID_SOCKET)
  //## end cProxySender::cProxySender%1012812258.hasinit
  //## begin cProxySender::cProxySender%1012812258.initialization preserve=yes
  //## end cProxySender::cProxySender%1012812258.initialization
{
  //## begin cProxySender::cProxySender%1012812258.body preserve=yes
   _Port = port;
   _IPAddress = ip_addr;
   SetSockets();
   char name[0x100] = {0};
   SafePrintf(name, sizeof(name), "Sender.%s:%d", _IPAddress.c_str(), _Port);
   _Name = name;
  //## end cProxySender::cProxySender%1012812258.body
}

cProxySender::cProxySender (cConfigurationObject *config_obj)
  //## begin cProxySender::cProxySender%1012812259.hasinit preserve=no
      : _IPAddress("127.0.0.1"), _Port(0), _Socket(INVALID_SOCKET)
  //## end cProxySender::cProxySender%1012812259.hasinit
  //## begin cProxySender::cProxySender%1012812259.initialization preserve=yes
  //## end cProxySender::cProxySender%1012812259.initialization
{
  //## begin cProxySender::cProxySender%1012812259.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   _Name = config_obj->get_Name().c_str();
   _Port = config_obj->PropertyValue("SendPort", _Port);
   _IPAddress = config_obj->PropertyValue("IPAddress", _IPAddress.c_str());
   SetSockets();
   char name[0x100] = {0};
   SafePrintf(name, sizeof(name), "Sender.%s:%d", _IPAddress.c_str(), _Port);
   _Name = name;
  //## end cProxySender::cProxySender%1012812259.body
}


cProxySender::~cProxySender()
{
  //## begin cProxySender::~cProxySender%.body preserve=yes
   CloseSockets();
  //## end cProxySender::~cProxySender%.body
}



//## Other Operations (implementation)
BOOL_T cProxySender::Send (cProxy *proxy)
{
  //## begin cProxySender::Send%1054547837.body preserve=yes
   try {
      STRING_T serialized_proxy = proxy->Serialize();
      if (Send(serialized_proxy.c_str()) == serialized_proxy.size()) {
         return true;
      }
   } catch (cError & e) {
      ErrorPrintf("%s: error %s while sending proxy info\n", _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("%s: unhandled execption while sending proxy info\n", _Name.c_str());
   }
   return false;
  //## end cProxySender::Send%1054547837.body
}

ULONG_T cProxySender::Send (CONST_STRING_T serialized_proxy)
{
  //## begin cProxySender::Send%1054632819.body preserve=yes
   try {
      if (_Socket == INVALID_SOCKET) {
         cSystemUtils::Suspend(100);
         return 0;
      }
      unsigned long msg_size = strlen(serialized_proxy);
      struct sockaddr_in addr = {0};
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(_IPAddress.c_str());
      addr.sin_port = htons((unsigned short)_Port);
      int flags = 0;
      int nsend = sendto(_Socket, serialized_proxy, msg_size, flags, (struct sockaddr *)&addr, sizeof(addr));
      if (nsend < 0) {
         int err = WSAGetLastError();
         if (err != WSAEHOSTUNREACH) {
            throw cError(SOCKET_SENDTO, err, _IPAddress.c_str(),
                         cConvUtils::StringValue(_Port).c_str());
         } else {
            return 0;
         }
      } else {
         return nsend;
      }
   } catch (cError & e) {
      ErrorPrintf("%s: error %s while sending proxy info\n", _Name.c_str(), (const char *)e);
   } catch (...) {
      ErrorPrintf("%s: unhandled execption while sending proxy info\n", _Name.c_str());
   }
   return 0;
  //## end cProxySender::Send%1054632819.body
}

STRING_T cProxySender::SenderName (CONST_STRING_T addr, USHORT_T port)
{
  //## begin cProxySender::SenderName%1134385869.body preserve=yes
   char sender_name[0x100] = {0};
   SafePrintf(sender_name, sizeof(sender_name), "sender.%s:%d", addr, port);
   return sender_name;
  //## end cProxySender::SenderName%1134385869.body
}

void cProxySender::SetSockets ()
{
  //## begin cProxySender::SetSockets%1054547838.body preserve=yes
   int on = 1;
   if (_Port != 0) {
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
   }
  //## end cProxySender::SetSockets%1054547838.body
}

void cProxySender::CloseSockets ()
{
  //## begin cProxySender::CloseSockets%1054547839.body preserve=yes
   if (_Socket != INVALID_SOCKET) closesocket(_Socket); 
  //## end cProxySender::CloseSockets%1054547839.body
}

// Additional Declarations
  //## begin cProxySender%3C5ED32D01D2.declarations preserve=yes
  //## end cProxySender%3C5ED32D01D2.declarations

//## begin module%3C5ED32D01D2.epilog preserve=yes
//## end module%3C5ED32D01D2.epilog
