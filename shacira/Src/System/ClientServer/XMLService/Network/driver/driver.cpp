
#include "driver.h"
#include "session.h"

cDriver::cDriver(bool isClient, cServiceFactory * serviceFactory)
   : _serviceFactory(serviceFactory), _isClient(isClient), _driverType(SOCKETIO)
{
}

cDriver::~cDriver()
{
}

cService * cDriver::createService(cSession * session)
{
   if (_serviceFactory != NULL) {
      cService * service = NULL;
      service = _serviceFactory->createService(this, session);
      return service;
   } else {
      return NULL;
   }
}

cService * cDriver::createService(cClient * client)
{
   if (_serviceFactory != NULL) {
      cService * service = NULL;
      service = _serviceFactory->createService(this, client);
      return service;
   } else {
      return NULL;
   }
}

cFrameHandler * cDriver::createFrameHandler()
{
   if (_serviceFactory != NULL) {
      cFrameHandler * frameHandler = NULL;
      frameHandler = _serviceFactory->createFrameHandler();
      return frameHandler;
   } else {
      return NULL;
   }
}







