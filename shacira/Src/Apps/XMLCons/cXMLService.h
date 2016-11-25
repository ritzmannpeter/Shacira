
#ifndef _cXMLService_h
#define _cXMLService_h

#include "cService.h"

class cXMLService : public cService
{
public:
   cXMLService();
   virtual ~cXMLService();
   virtual int Request(const unsigned char * request, int request_len, unsigned char * & response, int & response_len);
private:
   STRING_T WrapXML(const char * data);
};

#endif
