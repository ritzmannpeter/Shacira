
#include "cFrameHandler.h"
#include "cServiceHandler.h"
#include "cTCPServer.h"
#include "cAlloc.h"
#include <stdio.h>

static int _HandlerCount = 0;

cServiceHandler::cServiceHandler(cTCPServer * server, SOCKET socket, cService * service)
 : cThread(cThread::tdAutoDel), _Server(server), _Socket(socket), _Service(service), _Terminate(false), _Terminated(false), _TerminationCode(0), _IdleCount(0)
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
   int rc = 0;
   unsigned char * request = NULL;
   int request_size = 0;
   unsigned char buf[CHUNK_SIZE] = {0};
   int nread = cSocketApi::Recv(_Socket, (char*)buf, sizeof(buf), 0);
   while (nread > 0) {
      unsigned char * raw_data = NULL;
      int raw_data_size = 0;
      if (_Service->FrameHandler()->Input(buf, nread, raw_data, raw_data_size)) {
         request = raw_data;
         request_size = raw_data_size;
         break;
      }
      nread = cSocketApi::Recv(_Socket, (char*)buf, sizeof(buf), 0);
   }
   rc = nread;
   unsigned char * response = NULL;
   int response_size = 0;
   if (request != NULL) {
      if (request_size > 0) {
         _Service->Request(request, request_size, response, response_size);
         int nwrite = 0;
         if (response != NULL) {
            if (response_size > 0) {
               int frame_size = 0;
               unsigned char * frame = _Service->FrameHandler()->Output(response, response_size, frame_size);
               if (frame != NULL) {
                  if (frame_size > 0) {
                     nwrite = cSocketApi::Send(_Socket, (char*)frame, frame_size, 0);
                     rc = nwrite;
                  }
                  cAlloc::Free(frame);
               }
            }
            cAlloc::Free(response);
         }
      }
      cAlloc::Free(request);
   }
   rc = 0;
   return rc;
}






