//## begin module%4296ED620186.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4296ED620186.cm

//## begin module%4296ED620186.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4296ED620186.cp

//## Module: cServerThread%4296ED620186; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cServerThread.cpp

//## begin module%4296ED620186.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4296ED620186.additionalIncludes

//## begin module%4296ED620186.includes preserve=yes
//## end module%4296ED620186.includes

// cServerThread
#include "System/ClientServer/cServerThread.h"
// cServer
#include "System/ClientServer/cServer.h"
//## begin module%4296ED620186.additionalDeclarations preserve=yes
//## end module%4296ED620186.additionalDeclarations


// Class cServerThread 



cServerThread::cServerThread()
  //## begin cServerThread::cServerThread%.hasinit preserve=no
      : _Socket(INVALID_SOCKET), _Server(NULL)
  //## end cServerThread::cServerThread%.hasinit
  //## begin cServerThread::cServerThread%.initialization preserve=yes
   , cThread(cThread::tdAutoDel)
  //## end cServerThread::cServerThread%.initialization
{
  //## begin cServerThread::cServerThread%.body preserve=yes
_ASSERT_UNCOND
  //## end cServerThread::cServerThread%.body
}

cServerThread::cServerThread(const cServerThread &right)
  //## begin cServerThread::cServerThread%copy.hasinit preserve=no
      : _Socket(INVALID_SOCKET), _Server(NULL)
  //## end cServerThread::cServerThread%copy.hasinit
  //## begin cServerThread::cServerThread%copy.initialization preserve=yes
   , cThread(cThread::tdAutoDel)
  //## end cServerThread::cServerThread%copy.initialization
{
  //## begin cServerThread::cServerThread%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cServerThread::cServerThread%copy.body
}

cServerThread::cServerThread (cServer *server, SOCKET socket)
  //## begin cServerThread::cServerThread%1117174991.hasinit preserve=no
      : _Socket(INVALID_SOCKET), _Server(NULL)
  //## end cServerThread::cServerThread%1117174991.hasinit
  //## begin cServerThread::cServerThread%1117174991.initialization preserve=yes
   , cThread(cThread::tdAutoDel)
  //## end cServerThread::cServerThread%1117174991.initialization
{
  //## begin cServerThread::cServerThread%1117174991.body preserve=yes
   setPriority(cThread::plIdle);
   _Server = server;
   _Socket = socket;
  //## end cServerThread::cServerThread%1117174991.body
}


cServerThread::~cServerThread()
{
  //## begin cServerThread::~cServerThread%.body preserve=yes
   FreeResources();
  //## end cServerThread::~cServerThread%.body
}



//## Other Operations (implementation)
INT_T cServerThread::onMain (void *extra)
{
  //## begin cServerThread::onMain%1117174992.body preserve=yes
   try {
      cStreamMsg in_msg;
      while (1) {
         ULONG_T request_id = 0;
         int rc = cTCPComm::ReceiveMsg(_Socket, in_msg, request_id);
         if (rc < 0) {
            ErrorPrintf("server connection terminated: %d\n", LastError());
            FreeResources();
            return 0;
         } else {
            cStreamMsg reply_msg;
            _Server->Request(in_msg, reply_msg);
cSystemUtils::Suspend(10);
            int nsend = cTCPComm::SendMsg(_Socket, reply_msg, request_id);
//            InfoPrintf("server reply %d\n", request_id);
         }
      }
   } catch (...) {
      ErrorPrintf("unhandled exception in server thread\n");
   }
   FreeResources();
   return 0;
  //## end cServerThread::onMain%1117174992.body
}

void cServerThread::FreeResources ()
{
  //## begin cServerThread::FreeResources%1117204074.body preserve=yes
   cTCPComm::ShutDownSocket(_Socket);
  //## end cServerThread::FreeResources%1117204074.body
}

// Additional Declarations
  //## begin cServerThread%4296ED620186.declarations preserve=yes
  //## end cServerThread%4296ED620186.declarations

//## begin module%4296ED620186.epilog preserve=yes
//## end module%4296ED620186.epilog
