

#ifndef _testxmlservicefactory_h_
#define _testxmlservicefactory_h_

#include "servicefactory.h"

class COMM_EXPORT cTestXmlServiceFactory : public cServiceFactory
{
public:
   cTestXmlServiceFactory();
   virtual ~cTestXmlServiceFactory();
   virtual cService * createService(cDriver * driver, cSession * session);
   virtual cService * createService(cDriver * driver, cClient * client);
   virtual cFrameHandler * createFrameHandler();
};

#endif // _testxmlservicefactory_h__
