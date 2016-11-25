
#include "testxmlservicefactory.h"
#include "xmlservice.h"
#include "binaryframehandler.h"
#include "xmlservice.h"

cTestXmlServiceFactory::cTestXmlServiceFactory()
{
}

cTestXmlServiceFactory::~cTestXmlServiceFactory()
{
}

cService * cTestXmlServiceFactory::createService(cDriver * driver, cSession * session)
{
   cService * service = new cXMLService(driver, session);
   return service;
}

cService * cTestXmlServiceFactory::createService(cDriver * driver, cClient * client)
{
   cService * service = new cXMLService(driver, client);
   return service;
}

cFrameHandler * cTestXmlServiceFactory::createFrameHandler()
{
   cFrameHandler * frameHandler = new cBinaryFrameHandler;
   return frameHandler;
}


