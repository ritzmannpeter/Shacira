//## begin module%4104CB3B00AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4104CB3B00AB.cm

//## begin module%4104CB3B00AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4104CB3B00AB.cp

//## Module: cUDPServer%4104CB3B00AB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cUDPServer.cpp

//## begin module%4104CB3B00AB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4104CB3B00AB.additionalIncludes

//## begin module%4104CB3B00AB.includes preserve=yes
#include "System/ClientServer/cs.h"
//## end module%4104CB3B00AB.includes

// cInetAddress
#include "System/ClientServer/cInetAddress.h"
// cCSComm
#include "System/ClientServer/cCSComm.h"
// cUDPServer
#include "System/ClientServer/cUDPServer.h"
//## begin module%4104CB3B00AB.additionalDeclarations preserve=yes

#define SERVER_IDLE_TIME   10

//## end module%4104CB3B00AB.additionalDeclarations


// Class cUDPServer 





cUDPServer::cUDPServer()
  //## begin cUDPServer::cUDPServer%.hasinit preserve=no
      : _Terminated(false), _InBuf(NULL), _InBufSize(0x2000), _CSComm(NULL)
  //## end cUDPServer::cUDPServer%.hasinit
  //## begin cUDPServer::cUDPServer%.initialization preserve=yes
  //## end cUDPServer::cUDPServer%.initialization
{
  //## begin cUDPServer::cUDPServer%.body preserve=yes
_ASSERT_UNCOND
  //## end cUDPServer::cUDPServer%.body
}

cUDPServer::cUDPServer(const cUDPServer &right)
  //## begin cUDPServer::cUDPServer%copy.hasinit preserve=no
      : _Terminated(false), _InBuf(NULL), _InBufSize(0x2000), _CSComm(NULL)
  //## end cUDPServer::cUDPServer%copy.hasinit
  //## begin cUDPServer::cUDPServer%copy.initialization preserve=yes
  //## end cUDPServer::cUDPServer%copy.initialization
{
  //## begin cUDPServer::cUDPServer%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cUDPServer::cUDPServer%copy.body
}

cUDPServer::cUDPServer (cCSComm *comm)
  //## begin cUDPServer::cUDPServer%1090833149.hasinit preserve=no
      : _Terminated(false), _InBuf(NULL), _InBufSize(0x2000), _CSComm(NULL)
  //## end cUDPServer::cUDPServer%1090833149.hasinit
  //## begin cUDPServer::cUDPServer%1090833149.initialization preserve=yes
  //## end cUDPServer::cUDPServer%1090833149.initialization
{
  //## begin cUDPServer::cUDPServer%1090833149.body preserve=yes
   _CSComm = comm;
   _InBuf = (BUF_T)cSystemUtils::Alloc(_InBufSize);
  //## end cUDPServer::cUDPServer%1090833149.body
}


cUDPServer::~cUDPServer()
{
  //## begin cUDPServer::~cUDPServer%.body preserve=yes
   if (_InBuf != NULL) {
      cSystemUtils::Free(_InBuf);
   }
  //## end cUDPServer::~cUDPServer%.body
}



//## Other Operations (implementation)
void cUDPServer::Start ()
{
  //## begin cUDPServer::Start%1090840949.body preserve=yes
   if (start(teStart)) {
      InfoPrintf("server started\n");
   } else {
      InfoPrintf("failed to start server\n");
   }
   waitFor(teStart);
  //## end cUDPServer::Start%1090840949.body
}

void cUDPServer::Stop ()
{
  //## begin cUDPServer::Stop%1090840950.body preserve=yes
   _Terminated = true;
  //## end cUDPServer::Stop%1090840950.body
}

BOOL_T cUDPServer::onEnter (void *extra)
{
  //## begin cUDPServer::onEnter%1090833157.body preserve=yes
   return true;
  //## end cUDPServer::onEnter%1090833157.body
}

INT_T cUDPServer::onMain (void *extra)
{
  //## begin cUDPServer::onMain%1090833158.body preserve=yes
   try {
      while (!_Terminated) {
         try {
            if (_CSComm != NULL) {
               cCSMsg rcv_msg(_InBuf, _InBufSize);
               cInetAddress client_address;
               if (_CSComm != NULL) {
                  _CSComm->Receive(rcv_msg, (cCSAddress*)&client_address);
                  if (rcv_msg.AppDataSize() > 0) {
                     Dispatch(&rcv_msg, &client_address);
                  }
               }
            } else {
               cSystemUtils::Suspend(SERVER_IDLE_TIME);
            }
         } catch (cError & e) {
            ErrorPrintf("error %s in server main thread\n", (const char*)e);
            cSystemUtils::Suspend(SERVER_IDLE_TIME);
         } catch (...) {
            ErrorPrintf("unhandled exception in server main thread\n");
            cSystemUtils::Suspend(SERVER_IDLE_TIME);
         }
      }
      InfoPrintf("termination requested on server ...\n");
      return 0;
   } catch (...) {
      ErrorPrintf("unhandled exception in server terminating\n");
      return -2;
   }
  //## end cUDPServer::onMain%1090833158.body
}

void cUDPServer::onLeave (INT_T rc)
{
  //## begin cUDPServer::onLeave%1090833159.body preserve=yes
  //## end cUDPServer::onLeave%1090833159.body
}

void cUDPServer::Dispatch (cCSMsg *msg, cCSAddress *client_address)
{
  //## begin cUDPServer::Dispatch%1090833151.body preserve=yes
   Reply(msg, client_address);
  //## end cUDPServer::Dispatch%1090833151.body
}

void cUDPServer::Reply (cCSMsg *msg, cCSAddress *client_address)
{
  //## begin cUDPServer::Reply%1090833152.body preserve=yes
   if (_CSComm != NULL) {
      cInetAddress * addr = (cInetAddress*)client_address;
      try {
         _CSComm->Reply(msg, client_address);
      } catch (...) {
         ErrorPrintf("unhandled exception in in server reply to %s:%d\n",
                     addr->InetAddress(), (ULONG_T)addr->Port());
      }
   }
  //## end cUDPServer::Reply%1090833152.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cUDPServer::get_Terminated () const
{
  //## begin cUDPServer::get_Terminated%4104E42F036B.get preserve=no
  return _Terminated;
  //## end cUDPServer::get_Terminated%4104E42F036B.get
}

void cUDPServer::set_Terminated (BOOL_T value)
{
  //## begin cUDPServer::set_Terminated%4104E42F036B.set preserve=no
  _Terminated = value;
  //## end cUDPServer::set_Terminated%4104E42F036B.set
}

// Additional Declarations
  //## begin cUDPServer%4104CB3B00AB.declarations preserve=yes
  //## end cUDPServer%4104CB3B00AB.declarations

//## begin module%4104CB3B00AB.epilog preserve=yes
//## end module%4104CB3B00AB.epilog
