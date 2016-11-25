
#ifndef _cServer_h
#define _cServer_h

#include "cSocketApi.h"

class cServiceHandler;
class cService;

class cTCPServer
{
public:
   cTCPServer(unsigned int port, int max_connections, cService * service) : _Port(port), _MaxConnections(max_connections), _Service(service) {};
   virtual ~cTCPServer() {};
   int Start();
   void HandlerTerminated(cServiceHandler * handler);
   void ClosePendingSockets();
private:
   unsigned int _Port;
   int _MaxConnections;
   cService * _Service;
};

#endif
