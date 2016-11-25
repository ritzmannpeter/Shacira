
#ifndef _xmlinterface_h_
#define _xmlinterface_h_

#include "clientinterface.h"

class COMM_EXPORT cXMLInterface : public cClientInterface
{
public:
   cXMLInterface(cCommDriver * driver);
   virtual ~cXMLInterface();
   virtual int request(const cCommStruct & request, cCommStruct & reply);
};

#endif // _xmlinterface_h__
