
#include "cServiceHandler.h"
#include "cServer.h"
#include <stdio.h>

static int _HandlerCount = 0;

cServiceHandler::cServiceHandler()
 : cThread(cThread::tdAutoDel), _Terminate(false), _Terminated(false), _TerminationCode(0), _IdleCount(0)
{
   _HandlerCount++;
}

bool cServiceHandler::Start()
{
   if (start(teStart)) {
      return true;
   } else {
      return false;
   }
}

void cServiceHandler::Stop()
{
   _Terminate = true;
}

bool cServiceHandler::onEnter(void *extra)
{
   return true;
}

int cServiceHandler::onMain(void *extra)
{
   int rc = 0;
   while (!_Terminate) {
      rc = Service();
      if (rc != 0) {
         _Terminate = true;
      }
      if (rc == 0) {
         // with blocking sockets this means the client has disconnected
         _Terminate = true;
      } else if (rc < 0) {
         _Terminate = true;
      } else {
         _IdleCount = 0;
      }
   }
   _Terminated = true;
   _TerminationCode = rc;
   cSocketApi::CloseSocket(_Socket);
//   printf("service on %d terminated with code %d\n", (int)_Socket, _TerminationCode);
   return rc;
}

void cServiceHandler::onLeave(int rc)
{
}

int cServiceHandler::Service()
{
   char buf[0x200] = {0};
   int nread = cSocketApi::Recv(_Socket, buf, sizeof(buf), 0);
   while (nread > 0) {
      int nwrite = cSocketApi::Send(_Socket, buf, nread, 0);
      if (nwrite < 0) {
         nread = nwrite;
      } else {
         nread = cSocketApi::Recv(_Socket, buf, sizeof(buf), 0);
      }
   }
   return nread;
}






