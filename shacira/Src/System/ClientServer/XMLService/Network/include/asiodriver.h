
#ifndef _asiodriver_h_
#define _asiodriver_h_

#ifdef USE_BOOST

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "comm.h"
#include "driver.h"
#include "asiosession.h"

class COMM_EXPORT cAsioDriver : public cDriver
{
public:
   cAsioDriver(short port, cServiceFactory * serviceFactory);
   cAsioDriver(const std::string & host, short port, cServiceFactory * serviceFactory);
   virtual ~cAsioDriver();
   virtual cClient * createClient();
   virtual int run();
   void handle_accept(cAsioSession* new_session, const boost::system::error_code& error);
   boost::asio::io_service & ioService() {return _io_service;};
   inline std::string host() {return _host;};
   inline short port() {return _port;};
private:
   boost::asio::io_service _io_service;
   tcp::acceptor * _acceptor;
   std::string _host;
   short _port;
};

#endif // USE_BOOST

#endif // _asiodriver_h__
