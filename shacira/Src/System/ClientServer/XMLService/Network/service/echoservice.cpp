

#include "echoservice.h"

cEchoService::cEchoService(cDriver * driver, cSession * session)
   : cService(driver, session)
{
}

cEchoService::cEchoService(cDriver * driver, cClient * client)
   : cService(driver, client)
{
}

cEchoService::~cEchoService()
{
}

void cEchoService::handleInput(unsigned char * input, int inputLength)
{
   if (_session == NULL) {
      COMM_ASSERT("no session");
      return;
   }
   if (_frameHandler == NULL) {
      COMM_ASSERT("no frameHandler");
      return;
   }
   cByteBuffer frame;
   if (_frameHandler->add(input, inputLength, frame)) {
      handleFrame(frame);
   }
}

void cEchoService::handleFrame(const cByteBuffer & buffer)
{
   const OCTET_T * frame = buffer.data();
   int frameLength = (int)buffer.size();
   int rc = send(frame, frameLength);
}

int cEchoService::request(const cByteBuffer & request, cByteBuffer & reply)
{
   return 0;
}

