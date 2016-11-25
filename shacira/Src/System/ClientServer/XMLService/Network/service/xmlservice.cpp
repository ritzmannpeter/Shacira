
#include "xmlservice.h"

cXMLService::cXMLService(cDriver * driver, cSession * session)
   : cService(driver, session)
{
}

cXMLService::cXMLService(cDriver * driver, cClient * client)
   : cService(driver, client)
{
}

cXMLService::~cXMLService()
{
}

void cXMLService::handleFrame(const cByteBuffer & buffer)
{
   const unsigned char * d1 = NULL;
   const OCTET_T * d2 = NULL;
   d2 = d1;

   buffer.show("<-");
   cXMLStruct * xmlRequest = cXMLStruct::construct(buffer.data(), (int)buffer.size());
   if (xmlRequest != NULL) {
      cByteBuffer response;
      int rc = createResponse(buffer, response);
      if (rc == 0) {
         rc = send(response.data(), (int)response.size());
      }
   }
}

int cXMLService::request(const cByteBuffer & request, cByteBuffer & reply)
{
   int rc = 0;
   if (_client != NULL) {
      rc = _client->send(request.data(), (int)request.size());
      if (rc == 0) {
         rc = _client->receiveBuffer(reply);
      }
   }
   return rc;
}

int cXMLService::createResponse(const cByteBuffer & request, cByteBuffer & reply)
{
   return -1;
}

