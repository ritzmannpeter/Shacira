
#ifndef _cServiceHandler_h
#define _cServiceHandler_h

#include "cSocketApi.h"
#include "base/eb_thread.hpp"
class cServer;

class cServiceHandler : public cThread
{
public:
   cServiceHandler();
   virtual ~cServiceHandler() {};
   inline void SetServer(cServer * server) {_Server = server;};
   inline SOCKET Socket() {return _Socket;};
   inline void SetSocket(SOCKET socket) {_Socket = socket;};
   bool Start();
   void Stop();
   bool onEnter(void *extra);
   int onMain(void *extra);
   void onLeave(int rc);
   virtual int Service();
private:
   cServer * _Server;
   SOCKET _Socket;
   bool _Terminate;
   bool _Terminated;
   int _TerminationCode;
   int _IdleCount;
};

#endif
