
#ifndef cPPCServer_h
#define cPPCServer_h 1

#include "System/ClientServer/cServer.h"
class cPPCDevice;

class cPPCServer : public cServer
{
public:
   cPPCServer (cPPCDevice * device, cCSComm *comm);
   virtual ~cPPCServer();
   virtual void Request (cCSMsg *msg, cCSAddress *client_address = NULL);
private:
   cPPCDevice * _Device;
};

#endif
