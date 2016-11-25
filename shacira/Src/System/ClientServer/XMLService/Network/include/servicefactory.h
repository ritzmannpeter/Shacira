
#ifndef _servicefactory_h_
#define _servicefactory_h_

#include "comm.h"
class cSession;
class cClient;
class cService;
class cFrameHandler;
class cDriver;

class COMM_EXPORT cServiceFactory
{
public:
   cServiceFactory()
   {
   };
   virtual ~cServiceFactory()
   {
   };
   virtual cService * createService(cDriver * driver, cSession * session) = 0;
   virtual cService * createService(cDriver * driver, cClient * client) = 0;
   virtual cFrameHandler * createFrameHandler() = 0;
};

#endif // _servicefactory_h__
