//## begin module%410281DC01D4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%410281DC01D4.cm

//## begin module%410281DC01D4.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%410281DC01D4.cp

//## Module: cInetAddress%410281DC01D4; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cInetAddress.cpp

//## begin module%410281DC01D4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%410281DC01D4.additionalIncludes

//## begin module%410281DC01D4.includes preserve=yes
#include "System/ClientServer/cs.h"
//## end module%410281DC01D4.includes

// cInetAddress
#include "System/ClientServer/cInetAddress.h"
//## begin module%410281DC01D4.additionalDeclarations preserve=yes
//## end module%410281DC01D4.additionalDeclarations


// Class cInetAddress 


cInetAddress::cInetAddress()
  //## begin cInetAddress::cInetAddress%.hasinit preserve=no
  //## end cInetAddress::cInetAddress%.hasinit
  //## begin cInetAddress::cInetAddress%.initialization preserve=yes
  //## end cInetAddress::cInetAddress%.initialization
{
  //## begin cInetAddress::cInetAddress%.body preserve=yes
   memset(&_Address, 0, sizeof(_Address));
  //## end cInetAddress::cInetAddress%.body
}

cInetAddress::cInetAddress(const cInetAddress &right)
  //## begin cInetAddress::cInetAddress%copy.hasinit preserve=no
  //## end cInetAddress::cInetAddress%copy.hasinit
  //## begin cInetAddress::cInetAddress%copy.initialization preserve=yes
  //## end cInetAddress::cInetAddress%copy.initialization
{
  //## begin cInetAddress::cInetAddress%copy.body preserve=yes
   SetAddress((IN_ADDRESS_PTR)&(right._Address));
  //## end cInetAddress::cInetAddress%copy.body
}

cInetAddress::cInetAddress (USHORT_T port, CONST_STRING_T host)
  //## begin cInetAddress::cInetAddress%1090681462.hasinit preserve=no
  //## end cInetAddress::cInetAddress%1090681462.hasinit
  //## begin cInetAddress::cInetAddress%1090681462.initialization preserve=yes
  //## end cInetAddress::cInetAddress%1090681462.initialization
{
  //## begin cInetAddress::cInetAddress%1090681462.body preserve=yes
   memset(&_Address, 0, sizeof(_Address));
   SetAddress(port, host);
  //## end cInetAddress::cInetAddress%1090681462.body
}


cInetAddress::~cInetAddress()
{
  //## begin cInetAddress::~cInetAddress%.body preserve=yes
  //## end cInetAddress::~cInetAddress%.body
}



//## Other Operations (implementation)
const char * cInetAddress::Sender ()
{
  //## begin cInetAddress::Sender%1090862820.body preserve=yes
   static char buf[512] = {0};
   SafePrintf(buf, sizeof(buf), "%s:%d", InetAddress(), Port());
   return buf;
  //## end cInetAddress::Sender%1090862820.body
}

void cInetAddress::SetAddress (USHORT_T port, CONST_STRING_T host)
{
  //## begin cInetAddress::SetAddress%1090681465.body preserve=yes
   if (host == NULL) {
      _Address.sin_family = AF_INET;
      _Address.sin_addr.s_addr = INADDR_ANY;
      _Address.sin_port = htons(port);
   } else {
      struct hostent * host_entry = gethostbyname(host);
      if (host_entry == NULL) {
         int err = WSAGetLastError();
         ErrorPrintf("failed to get host entry for %s\n");
      } else {
         _Address.sin_family = AF_INET;
         memcpy((char *)&(_Address).sin_addr,
               (char *)host_entry->h_addr,
             host_entry->h_length);
         _Address.sin_port = htons(port);
      }
   }
  //## end cInetAddress::SetAddress%1090681465.body
}

void cInetAddress::SetAddress (IN_ADDRESS_PTR address)
{
  //## begin cInetAddress::SetAddress%1090681466.body preserve=yes
   memcpy(&_Address, address, sizeof(_Address));
  //## end cInetAddress::SetAddress%1090681466.body
}

void cInetAddress::SetAddress (IN_ADDRESS_PTR address, unsigned short port)
{
  //## begin cInetAddress::SetAddress%1090840952.body preserve=yes
  //## end cInetAddress::SetAddress%1090840952.body
}

void cInetAddress::SetAddress (SOCK_ADDRESS_PTR address)
{
  //## begin cInetAddress::SetAddress%1090681467.body preserve=yes
   memcpy(&_Address, address, sizeof(_Address));
  //## end cInetAddress::SetAddress%1090681467.body
}

IN_ADDRESS_PTR cInetAddress::InetAddr ()
{
  //## begin cInetAddress::InetAddr%1090681463.body preserve=yes
   return &_Address;
  //## end cInetAddress::InetAddr%1090681463.body
}

SOCK_ADDRESS_PTR cInetAddress::SockAddr ()
{
  //## begin cInetAddress::SockAddr%1090681464.body preserve=yes
   return (SOCK_ADDRESS_PTR)&_Address;
  //## end cInetAddress::SockAddr%1090681464.body
}

const char * cInetAddress::InetAddress ()
{
  //## begin cInetAddress::InetAddress%1090695922.body preserve=yes
   return inet_ntoa(_Address.sin_addr);
  //## end cInetAddress::InetAddress%1090695922.body
}

USHORT_T cInetAddress::Port ()
{
  //## begin cInetAddress::Port%1090695923.body preserve=yes
   return htons(_Address.sin_port);
  //## end cInetAddress::Port%1090695923.body
}

void cInetAddress::SetPort (unsigned short port)
{
  //## begin cInetAddress::SetPort%1090840953.body preserve=yes
   _Address.sin_port = htons(port);
  //## end cInetAddress::SetPort%1090840953.body
}

// Additional Declarations
  //## begin cInetAddress%410281DC01D4.declarations preserve=yes
  //## end cInetAddress%410281DC01D4.declarations

//## begin module%410281DC01D4.epilog preserve=yes
//## end module%410281DC01D4.epilog
