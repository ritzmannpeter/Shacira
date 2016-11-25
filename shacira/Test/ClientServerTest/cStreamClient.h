
#ifndef cStreamClient_h
#define cStreamClient_h 1

#include "System/ClientServer/cClient.h"

class cStreamClient : public cClient
{
public:
   cStreamClient(cCSComm *comm);
   virtual ~cStreamClient();
   virtual void Dispatch (cCSMsg *msg, cCSAddress *client_address);
private:
};

#endif

