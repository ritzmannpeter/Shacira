
#ifdef USE_BOOST

#include "asiosession.h"
#include "echoservice.h"
#include "xmlservice.h"
#include "binaryframehandler.h"
#include "trivialframehandler.h"
#include <cstdlib>
#include <iostream>

cAsioSession::cAsioSession(boost::asio::io_service& io_service, cDriver * driver)
   : cSession(driver), _socket(io_service)
{
}

cAsioSession::~cAsioSession()
{
}

void cAsioSession::startService()
{
   readInput();
}

int cAsioSession::send(const OCTET_T * output, LENGTH_T outputLength)
{
#define BUF_SIZE 65536
   const OCTET_T * ptr = output;
   int rest = (int)outputLength;
   int size = BUF_SIZE;
   while (rest > 0) {
      if (rest < size) {
         size = rest;
      }
      boost::asio::async_write(socket(),
                               boost::asio::buffer(ptr, size),
                               boost::bind(&cAsioSession::handle_write, this,
                                            boost::asio::placeholders::error, size));
      rest -= BUF_SIZE;
      ptr += BUF_SIZE;
   }
   return 0;
}

void cAsioSession::readInput()
{
   socket().async_read_some(boost::asio::buffer(data_, max_length),
                            boost::bind(&cAsioSession::handle_read, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void cAsioSession::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
   if (!error) {
      if (_service != NULL) {
         _service->handleInput((unsigned char *)&data_, (int)bytes_transferred);
      } else {
         COMM_ASSERT("no service");
      }
      readInput();
   } else {
      COMM_ASSERT(error.message().c_str());
      delete this;
   }
}

void cAsioSession::handle_write(const boost::system::error_code& error, size_t bytes_read)
{
return;
   if (!error) {
   } else {
      COMM_ASSERT(error.message().c_str());
      delete this;
   }
}

#endif // USE_BOOST

