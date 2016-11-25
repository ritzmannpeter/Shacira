
#ifndef cPPCClient_h
#define cPPCClient_h 1

#include "System/ClientServer/cClient.h"
class cPPCDevice;
//class __DLL_EXPORT__ cPPCClient : public cClient
class cPPCClient : public cClient
{
public:
   cPPCClient(cPPCDevice * device, cCSComm *comm);
   virtual ~cPPCClient();
   virtual void Dispatch (cCSMsg *msg, cCSAddress *client_address);
private:
   cPPCDevice * _Device;
};

#endif

