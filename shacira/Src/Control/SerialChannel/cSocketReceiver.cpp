//## begin module%3C34419E00AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C34419E00AF.cm

//## begin module%3C34419E00AF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C34419E00AF.cp

//## Module: cSocketReceiver%3C34419E00AF; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSocketReceiver.cpp

//## begin module%3C34419E00AF.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C34419E00AF.additionalIncludes

//## begin module%3C34419E00AF.includes preserve=yes
//## end module%3C34419E00AF.includes

// cTimeObject
#include "System/cTimeObject.h"
// cError
#include "System/cError.h"
// cCharRingBuffer
#include "System/Memory/cCharRingBuffer.h"
// cSocketReceiver
#include "Control/SerialChannel/cSocketReceiver.h"
//## begin module%3C34419E00AF.additionalDeclarations preserve=yes
//## end module%3C34419E00AF.additionalDeclarations


// Class cSocketReceiver 


cSocketReceiver::cSocketReceiver()
  //## begin cSocketReceiver::cSocketReceiver%.hasinit preserve=no
      : _Socket(INVALID_SOCKET)
  //## end cSocketReceiver::cSocketReceiver%.hasinit
  //## begin cSocketReceiver::cSocketReceiver%.initialization preserve=yes
  //## end cSocketReceiver::cSocketReceiver%.initialization
{
  //## begin cSocketReceiver::cSocketReceiver%.body preserve=yes
  //## end cSocketReceiver::cSocketReceiver%.body
}

cSocketReceiver::cSocketReceiver(const cSocketReceiver &right)
  //## begin cSocketReceiver::cSocketReceiver%copy.hasinit preserve=no
      : _Socket(INVALID_SOCKET)
  //## end cSocketReceiver::cSocketReceiver%copy.hasinit
  //## begin cSocketReceiver::cSocketReceiver%copy.initialization preserve=yes
  //## end cSocketReceiver::cSocketReceiver%copy.initialization
{
  //## begin cSocketReceiver::cSocketReceiver%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSocketReceiver::cSocketReceiver%copy.body
}

cSocketReceiver::cSocketReceiver (SOCKET socket)
  //## begin cSocketReceiver::cSocketReceiver%1010053285.hasinit preserve=no
      : _Socket(INVALID_SOCKET)
  //## end cSocketReceiver::cSocketReceiver%1010053285.hasinit
  //## begin cSocketReceiver::cSocketReceiver%1010053285.initialization preserve=yes
  //## end cSocketReceiver::cSocketReceiver%1010053285.initialization
{
  //## begin cSocketReceiver::cSocketReceiver%1010053285.body preserve=yes
   _Socket = socket;
  //## end cSocketReceiver::cSocketReceiver%1010053285.body
}


cSocketReceiver::~cSocketReceiver()
{
  //## begin cSocketReceiver::~cSocketReceiver%.body preserve=yes
  //## end cSocketReceiver::~cSocketReceiver%.body
}



//## Other Operations (implementation)
LONG_T cSocketReceiver::Get (STRING_BUF_T buffer, ULONG_T amount, ULONG_T timeout)
{
  //## begin cSocketReceiver::Get%1010053286.body preserve=yes
   int len = _RingBuffer->Get(buffer, amount);
   if (len == (int)amount) return len;
   if (setsockopt(_Socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
      int err_code = WSAGetLastError();
      InfoPrintf("setsockopt SO_RCVTIMEO on Socket returns %d\n", err_code);
#ifndef REPORT_ONLY
      throw cError(SOCKET_SETSOCKOPT, err_code, "SO_RCVTIMEO", "Socket");
#endif
   }
   struct sockaddr addr = {0};
   socklen_t addr_size = sizeof(addr);
   int flags = 0;
   char buf[4096] = {0};
   int nread = recvfrom(_Socket, buf, sizeof(buf), flags, &addr, &addr_size);
   if (nread < 0) {
      int err_code = WSAGetLastError();
      if (!TIMED_OUT(err_code)) {
         InfoPrintf("recvfrom on Socket returns %d\n", err_code);
#ifndef REPORT_ONLY
         throw cError(SOCKET_RECVFROM, err_code, "Socket");
#endif
      }
      return len;
   } else {
      _RingBuffer->Put(buf, nread);
      len += _RingBuffer->Get(buffer + len, amount - len);
      return len;
   }
  //## end cSocketReceiver::Get%1010053286.body
}

void cSocketReceiver::Flush ()
{
  //## begin cSocketReceiver::Flush%1010131286.body preserve=yes
   _RingBuffer->Clear();
/* is there a nedd to do this ??
   struct sockaddr addr = {0};
   int addr_size = sizeof(addr);
   int flags = 0;
   char buf[4096] = {0};
   int timeout = 10;
   if (setsockopt(_Socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0) {
      int err_code = WSAGetLastError();
      InfoPrintf("setsockopt SO_RCVTIMEO on Socket returns %d\n", err_code);
#ifndef REPORT_ONLY
      throw cError(SOCKET_SETSOCKOPT, err_code, "SO_RCVTIMEO", "Socket");
#endif
   }
ULONG_T t = cSystemUtils::RealtimeOffset();
int nread = 0;
   while ((nread = recvfrom(_Socket, buf, sizeof(buf), flags, &addr, &addr_size) > 0)) {
   }
InfoPrintf("flush socket %d msecs\n", cSystemUtils::RealtimeOffset() - t);
*/
  //## end cSocketReceiver::Flush%1010131286.body
}

// Additional Declarations
  //## begin cSocketReceiver%3C34419E00AF.declarations preserve=yes
  //## end cSocketReceiver%3C34419E00AF.declarations

//## begin module%3C34419E00AF.epilog preserve=yes
//## end module%3C34419E00AF.epilog
