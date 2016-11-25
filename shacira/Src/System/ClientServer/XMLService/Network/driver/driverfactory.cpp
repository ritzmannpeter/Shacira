
#include "driverfactory.h"
#include "asiodriver.h"
#include "sockdriver.h"

cDriverFactory::cDriverFactory()
{
}

cDriverFactory::~cDriverFactory()
{
}

cDriver * cDriverFactory::create(cDriver::DriverType driverType, short port, cServiceFactory * serviceFactory)
{
   if (driverType == cDriver::ASIO) {
#ifdef USE_BOOST
      return new cAsioDriver(port, serviceFactory);
#else
      return NULL;
#endif
   }
   if (driverType == cDriver::SOCKETIO) {
      return new cSockDriver(port, serviceFactory);
   }
   return NULL;
}

cDriver * cDriverFactory::create(cDriver::DriverType driverType, const std::string & host, short port, cServiceFactory * serviceFactory)
{
   if (driverType == cDriver::ASIO) {
#ifdef USE_BOOST
      return new cAsioDriver(host, port, serviceFactory);
#else
      return NULL;
#endif
   }
   return NULL;
}

