
#ifndef _echoservice_h
#define _echoservice_h

#include "service.h"

class COMM_EXPORT cEchoService : public cService
{
public:
   cEchoService(cDriver * driver, cSession * session);
   cEchoService(cDriver * driver, cClient * client);
   virtual ~cEchoService();
   virtual void handleInput(unsigned char * input, int inputLength);
   virtual void handleFrame(const cByteBuffer & buffer);
   virtual int request(const cByteBuffer & request, cByteBuffer & reply);
};

#endif // _echoservice_h_
