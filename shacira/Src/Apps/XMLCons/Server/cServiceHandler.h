
#ifndef _cServiceHandler_h
#define _cServiceHandler_h

#include "cSocketApi.h"
#include "cService.h"
#include "base/eb_thread.hpp"
class cTCPServer;
class cService;

class cServiceHandler : public cThread
{
public:
   cServiceHandler(cTCPServer * server, SOCKET socket, cService * service);
   virtual ~cServiceHandler() {};
   inline SOCKET Socket() {return _Socket;};
   bool Start();
   void Stop();
   bool onEnter(void *extra);
   int onMain(void *extra);
   void onLeave(int rc);
   virtual int Service();
private:
   cTCPServer * _Server;
   cService * _Service;
   SOCKET _Socket;
   bool _Terminate;
   bool _Terminated;
   int _TerminationCode;
   int _IdleCount;
};

#endif
