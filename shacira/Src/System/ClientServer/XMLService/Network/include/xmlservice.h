
#ifndef _xmlservice_h
#define _xmlservice_h

#include "service.h"
#include "xmlstruct.h"

class COMM_EXPORT cXMLService : public cService
{
public:
   cXMLService(cDriver * driver, cSession * session);
   cXMLService(cDriver * driver, cClient * client);
   virtual ~cXMLService();
   virtual void handleFrame(const cByteBuffer & buffer);
   virtual int request(const cByteBuffer & request, cByteBuffer & reply);
private:
   int createResponse(const cByteBuffer & request, cByteBuffer & response);
};

#endif // _xmlservice_h_
