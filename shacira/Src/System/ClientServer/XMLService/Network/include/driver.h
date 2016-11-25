
#ifndef _driver_h_
#define _driver_h_

#include "comm.h"
#include "servicefactory.h"
class cSession;
class cService;
class cFrameHandler;
class cClient;

class COMM_EXPORT cDriver
{
public:
   enum DriverType {ASIO, SOCKETIO};
public:
   cDriver(bool isClient, cServiceFactory * serviceFactory);
   virtual ~cDriver();
   // client factory (client)
   virtual int run() = 0;
   virtual cClient * createClient() = 0;
   // service factory (server)
   cService * createService(cSession * session);
   cService * createService(cClient * client);
   cFrameHandler * createFrameHandler();
   inline DriverType driverType() {return _driverType;};
   inline bool isClient() const {return _isClient;};
protected:
   cServiceFactory * _serviceFactory;
   DriverType _driverType;
   bool _isClient;
};

#endif // _driver_h__
