
#include "service.h"
#include <string.h>

cService::cService(cDriver * driver, cSession * session)
   : _session(session), _client(NULL), _frameHandler(NULL)
{
   _frameHandler = driver->createFrameHandler();
}

cService::cService(cDriver * driver, cClient * client)
   : _session(NULL), _client(client), _frameHandler(NULL)
{
   _frameHandler = driver->createFrameHandler();
}

cService::~cService()
{
   if (_frameHandler != NULL) {
      delete _frameHandler;
   }
}

int cService::send(const OCTET_T * output, LENGTH_T length)
{
   if (_session == NULL && _client == NULL) {
      COMM_ASSERT("no session and no client");
      return -1;
   }
   if (_frameHandler == NULL) {
      COMM_ASSERT("no frameHandler");
      return -1;
   }
   cByteBuffer::show("->", output, length);
   cByteBuffer buffer;
   _frameHandler->pack(output, length, buffer);
   const OCTET_T * frame = buffer.data();
   int frameLength = (int)buffer.size();
   if (_session != NULL) {
      return _session->send(frame, frameLength);
   } else if (_client != NULL) {
      return _client->send(frame, frameLength);
   }
   return -1;
}

void cService::handleInput(const OCTET_T * input, LENGTH_T inputLength)
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

