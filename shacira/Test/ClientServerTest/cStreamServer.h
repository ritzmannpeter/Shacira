
#ifndef cStreamServer_h
#define cStreamServer_h 1

#include "System/ClientServer/cServer.h"

class cStreamServer : public cServer
{
public:
   cStreamServer (cCSComm *comm);
   virtual ~cStreamServer();
   virtual void Request (cCSMsg *msg, cCSAddress *client_address = NULL);
private:
};

#endif
