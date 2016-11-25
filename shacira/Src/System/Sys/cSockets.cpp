//## begin module%3DD2953F0027.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD2953F0027.cm

//## begin module%3DD2953F0027.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD2953F0027.cp

//## Module: cSockets%3DD2953F0027; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSockets.cpp

//## begin module%3DD2953F0027.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DD2953F0027.additionalIncludes

//## begin module%3DD2953F0027.includes preserve=yes
//## end module%3DD2953F0027.includes

// eb_sema
#include "base/eb_sema.hpp"
// cObjectLock
#include "System/Objects/cObjectLock.h"
// cSockets
#include "System/Sys/cSockets.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
//## begin module%3DD2953F0027.additionalDeclarations preserve=yes
//## end module%3DD2953F0027.additionalDeclarations


// Class cSockets 

//## begin cSockets::RefCount%3DD2A1B3014E.attr preserve=no  implementation: static ULONG_T {U} 0
ULONG_T cSockets::_RefCount = 0;
//## end cSockets::RefCount%3DD2A1B3014E.attr

//## begin cSockets::Mutex%3DD2A21E0025.attr preserve=no  implementation: static cMutexSem {U} 
cMutexSem cSockets::_Mutex;
//## end cSockets::Mutex%3DD2A21E0025.attr

//## begin cSockets::Sockets%3E89C5F9031C.attr preserve=no  implementation: static cSockets * {U} NULL
cSockets *cSockets::_Sockets = NULL;
//## end cSockets::Sockets%3E89C5F9031C.attr

cSockets::cSockets()
  //## begin cSockets::cSockets%.hasinit preserve=no
  //## end cSockets::cSockets%.hasinit
  //## begin cSockets::cSockets%.initialization preserve=yes
  //## end cSockets::cSockets%.initialization
{
  //## begin cSockets::cSockets%.body preserve=yes
   cObjectLock __lock__(&_Mutex);
   _RefCount++;
   if (_RefCount > 1) return;
   StartSockets();
  //## end cSockets::cSockets%.body
}

cSockets::cSockets(const cSockets &right)
  //## begin cSockets::cSockets%copy.hasinit preserve=no
  //## end cSockets::cSockets%copy.hasinit
  //## begin cSockets::cSockets%copy.initialization preserve=yes
  //## end cSockets::cSockets%copy.initialization
{
  //## begin cSockets::cSockets%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSockets::cSockets%copy.body
}


cSockets::~cSockets()
{
  //## begin cSockets::~cSockets%.body preserve=yes
   cObjectLock __lock__(&_Mutex);
   _RefCount--;
   if (_RefCount > 0) return;
   StopSockets();
  //## end cSockets::~cSockets%.body
}



//## Other Operations (implementation)
void cSockets::Initialize ()
{
  //## begin cSockets::Initialize%1049215550.body preserve=yes
	if (_Sockets == NULL) {
		_Sockets = new cSockets;
	}
  //## end cSockets::Initialize%1049215550.body
}

BOOL_T cSockets::SetReceiveTimeout (SOCKET socket, ULONG_T msecs)
{
  //## begin cSockets::SetReceiveTimeout%1145091000.body preserve=yes
   if (msecs > 0) {
      ULONG_T sec = (msecs/1000);
      ULONG_T remaining = (msecs%1000);
      ULONG_T usec = remaining * 1000;
      timeval t = {0};
      t.tv_sec = sec;
      t.tv_usec = usec;
#if defined(_WIN32)
      if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&msecs, sizeof(msecs)) < 0) {
#else
	  if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&t, sizeof(t)) < 0) {
#endif
         ErrorPrintf("failed to set receive timeout to %d msecs\n", msecs);
         return false;
      } else {
         return true;
      }
   } else {
      timeval t = {0};
      if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&t, sizeof(t)) < 0) {
         ErrorPrintf("failed to set receive timeout to %d msecs\n", msecs);
         return false;
      } else {
         return true;
      }
   }
  //## end cSockets::SetReceiveTimeout%1145091000.body
}

void cSockets::StartSockets ()
{
  //## begin cSockets::StartSockets%1037211076.body preserve=yes
#if defined(_WIN32)
   WORD req_version = MAKEWORD(2, 2);
   WSADATA wsa_data;
   int err = WSAStartup(req_version, &wsa_data);
   if (err != 0) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      throw cError(SOCKET_STARTUP, err);
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
      throw cError(SOCKET_VERSION, 0, cConvUtils::StringValue(LOBYTE(wsa_data.wVersion)).c_str(),
                   cConvUtils::StringValue(HIBYTE(wsa_data.wVersion)).c_str());
   }
   /* The WinSock DLL is acceptable. Proceed. */
#endif
  //## end cSockets::StartSockets%1037211076.body
}

void cSockets::StopSockets ()
{
  //## begin cSockets::StopSockets%1037211077.body preserve=yes
#if defined(_WIN32)
   WSACleanup();
#endif
  //## end cSockets::StopSockets%1037211077.body
}

// Additional Declarations
  //## begin cSockets%3DD2953F0027.declarations preserve=yes
  //## end cSockets%3DD2953F0027.declarations

//## begin module%3DD2953F0027.epilog preserve=yes
//## end module%3DD2953F0027.epilog
