

#include "socksession.h"
#include "binaryframehandler.h"
#include "trivialframehandler.h"
#include <cstdlib>
#include <iostream>

cSockSession::cSockSession(SOCKET socket, cDriver * driver)
   : cSession(driver), _socket(socket)
{
}

cSockSession::~cSockSession()
{
}

void cSockSession::startService()
{
}

int cSockSession::send(const OCTET_T * output, LENGTH_T outputLength)
{
#define BUF_SIZE 65536
   int error = 0;
   const OCTET_T * ptr = output;
   int rest = (int)outputLength;
   int size = BUF_SIZE;
   while (rest > 0) {
      if (rest < size) {
         size = rest;
      }
      int nsend = ::send(_socket, (const char *)ptr, size, 0);
      if (nsend < 0) {
         error = ::GetLastError();
      }
      rest -= BUF_SIZE;
      ptr += BUF_SIZE;
   }
   return 0;
}

void cSockSession::handle_read(const cSockError & error, unsigned char * data, size_t bytes_transferred)
{
   if (!error) {
      if (_service != NULL) {
         _service->handleInput((unsigned char *)data, (int)bytes_transferred);
      } else {
         COMM_ASSERT("no service");
      }
   } else {
      COMM_ASSERT(error.message().c_str());
      delete this;
   }
}

