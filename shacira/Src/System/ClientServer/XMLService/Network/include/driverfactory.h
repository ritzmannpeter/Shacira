
#ifndef _driverfactory_h_
#define _driverfactory_h_

#include "comm.h"
#include "driver.h"
#include "servicefactory.h"

class COMM_EXPORT cDriverFactory
{
public:
   cDriverFactory();
   virtual ~cDriverFactory();
   // driver factory
   static cDriver * create(cDriver::DriverType driverType, short port, cServiceFactory * serviceFactory = NULL);
   static cDriver * create(cDriver::DriverType driverType, const std::string & host, short port, cServiceFactory * _serviceFactory = NULL);
};

#endif // _driverfactory_h__
