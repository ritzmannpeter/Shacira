
#ifndef _asiosession_h_
#define _asiosession_h_

#ifdef USE_BOOST

#include "session.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
class cService;

using boost::asio::ip::tcp;

class cAsioSession : public cSession
{
public:
   cAsioSession(boost::asio::io_service& io_service, cDriver * driver);
   virtual ~cAsioSession();
   virtual void startService();
   virtual int send(const OCTET_T * output, LENGTH_T length);
public:
   inline tcp::socket & socket() {return _socket;};
private:
   virtual void readInput();
   void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
   void handle_write(const boost::system::error_code& error, size_t bytes_read);
private:
   tcp::socket _socket;
   enum { max_length = 1024 };
   char data_[max_length];
};

#endif // USE_BOOST

#endif // _asiosession_h_
