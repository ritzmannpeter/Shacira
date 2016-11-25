//## begin module%3CAC8A25015D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CAC8A25015D.cm

//## begin module%3CAC8A25015D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3CAC8A25015D.cp

//## Module: cTCPReceiver%3CAC8A25015D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cTCPReceiver.cpp

//## begin module%3CAC8A25015D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3CAC8A25015D.additionalIncludes

//## begin module%3CAC8A25015D.includes preserve=yes
//## end module%3CAC8A25015D.includes

// cCharRingBuffer
#include "System/Memory/cCharRingBuffer.h"
// cTCPReceiver
#include "Control/SerialChannel/cTCPReceiver.h"
//## begin module%3CAC8A25015D.additionalDeclarations preserve=yes
//## end module%3CAC8A25015D.additionalDeclarations


// Class cTCPReceiver 


cTCPReceiver::cTCPReceiver()
  //## begin cTCPReceiver::cTCPReceiver%.hasinit preserve=no
      : _Socket(INVALID_SOCKET)
  //## end cTCPReceiver::cTCPReceiver%.hasinit
  //## begin cTCPReceiver::cTCPReceiver%.initialization preserve=yes
  //## end cTCPReceiver::cTCPReceiver%.initialization
{
  //## begin cTCPReceiver::cTCPReceiver%.body preserve=yes
  //## end cTCPReceiver::cTCPReceiver%.body
}

cTCPReceiver::cTCPReceiver(const cTCPReceiver &right)
  //## begin cTCPReceiver::cTCPReceiver%copy.hasinit preserve=no
      : _Socket(INVALID_SOCKET)
  //## end cTCPReceiver::cTCPReceiver%copy.hasinit
  //## begin cTCPReceiver::cTCPReceiver%copy.initialization preserve=yes
  //## end cTCPReceiver::cTCPReceiver%copy.initialization
{
  //## begin cTCPReceiver::cTCPReceiver%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTCPReceiver::cTCPReceiver%copy.body
}

cTCPReceiver::cTCPReceiver (SOCKET socket)
  //## begin cTCPReceiver::cTCPReceiver%1017940475.hasinit preserve=no
      : _Socket(INVALID_SOCKET)
  //## end cTCPReceiver::cTCPReceiver%1017940475.hasinit
  //## begin cTCPReceiver::cTCPReceiver%1017940475.initialization preserve=yes
  //## end cTCPReceiver::cTCPReceiver%1017940475.initialization
{
  //## begin cTCPReceiver::cTCPReceiver%1017940475.body preserve=yes
   _Socket = socket;
  //## end cTCPReceiver::cTCPReceiver%1017940475.body
}


cTCPReceiver::~cTCPReceiver()
{
  //## begin cTCPReceiver::~cTCPReceiver%.body preserve=yes
  //## end cTCPReceiver::~cTCPReceiver%.body
}



//## Other Operations (implementation)
LONG_T cTCPReceiver::Get (STRING_BUF_T buffer, ULONG_T amount, ULONG_T timeout)
{
  //## begin cTCPReceiver::Get%1017940476.body preserve=yes
   unsigned long len = _RingBuffer->Get(buffer, amount);
   if (len == amount) return len;
   if (setsockopt(_Socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
      int err_code = WSAGetLastError();
      InfoPrintf("setsockopt SO_RCVTIMEO on Socket returns %d\n", err_code);
      throw cError(SOCKET_SETSOCKOPT, err_code, "SO_RCVTIMEO", "Socket");
   }
   char buf[4096];
   while (len < amount) {
      int nread = recv(_Socket, buf, sizeof(buf), 0);
      if (nread < 0) {
         int err_code = WSAGetLastError();
         if (!TIMED_OUT(err_code)) {
            InfoPrintf("recvfrom on Socket returns %d\n", err_code);
            throw cError(SOCKET_RECVFROM, err_code, "Socket");
         }
         return len;
      } else {
         _RingBuffer->Put(buf, nread);
         len += _RingBuffer->Get(buffer + len, amount - len);
         return len;
      }
   }
	return len;
  //## end cTCPReceiver::Get%1017940476.body
}

void cTCPReceiver::Flush ()
{
  //## begin cTCPReceiver::Flush%1017940477.body preserve=yes
   _RingBuffer->Clear();
  //## end cTCPReceiver::Flush%1017940477.body
}

// Additional Declarations
  //## begin cTCPReceiver%3CAC8A25015D.declarations preserve=yes
  //## end cTCPReceiver%3CAC8A25015D.declarations

//## begin module%3CAC8A25015D.epilog preserve=yes
//## end module%3CAC8A25015D.epilog
