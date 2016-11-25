
#ifndef _cEchoService_h
#define _cEchoService_h

#include "cServiceHandler.h"

class cEchoService : public cServiceHandler
{
public:
   cEchoService(cConnectionHandler * ch, cFrameHandler * fh);
   virtual ~cEchoService();
   virtual int HandleRequest(void * in_frame, unsigned long in_length,
                             void * out_frame, unsigned long * out_length);
   virtual int Request(void * out_frame, unsigned long out_length,
                       void * in_frame, unsigned long * in_length);
private:
};

#endif
