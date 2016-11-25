
#ifndef _cConnectionHandler_h
#define _cConnectionHandler_h

#include "cTransportHandler.h"

class cConnectionHandler
{
public:
   cConnectionHandler();
   virtual ~cConnectionHandler();
   virtual cTransportHandler * Listen() = 0;
   virtual cTransportHandler * Connect() = 0;
   virtual void Disconnect() = 0;
protected:
};

#endif
