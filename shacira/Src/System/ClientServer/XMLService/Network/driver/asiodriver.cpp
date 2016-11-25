
#ifdef USE_BOOST

#include "asiodriver.h"
#include "asiosession.h"
#include "asioclient.h"

cAsioDriver::cAsioDriver(short port, cServiceFactory * serviceFactory)
   : cDriver(false, serviceFactory), _acceptor(NULL), _port(port)
{
   _acceptor = new tcp::acceptor(_io_service, tcp::endpoint(tcp::v4(), port));
   _driverType = cDriver::ASIO;
   cAsioSession * session = new cAsioSession(_io_service, this);
   _acceptor->async_accept(session->socket(),
                           boost::bind(&cAsioDriver::handle_accept, this, session,
                                       boost::asio::placeholders::error));
}

cAsioDriver::cAsioDriver(const std::string & host, short port, cServiceFactory * serviceFactory)
   : cDriver(true, serviceFactory), _acceptor(NULL), _host(host), _port(port)
{
   _driverType = cDriver::ASIO;
}

cAsioDriver::~cAsioDriver()
{
   if (_acceptor != NULL) {
      delete _acceptor;
   }
}

cClient * cAsioDriver::createClient()
{
   if (_isClient) {
      return new cAsioClient(_io_service, this);
   } else {
      return NULL;
   }
}

int cAsioDriver::run()
{
   try {
      _io_service.run();
      return 0;
   } catch (std::exception& e) {
      COMM_ASSERT(e.what());
      return -1;
   } catch (...) {
      COMM_ASSERT("unhandled exception");
      return -1;
   }
}

void cAsioDriver::handle_accept(cAsioSession* new_session, const boost::system::error_code& error)
{
   if (!error) {
      new_session->startService();
      new_session = new cAsioSession(_io_service, this);
      _acceptor->async_accept(new_session->socket(),
                             boost::bind(&cAsioDriver::handle_accept, this, new_session,
                                          boost::asio::placeholders::error));
   } else {
      COMM_ASSERT(error.message().c_str());
      delete new_session;
   }
}

#endif // USE_BOOST
