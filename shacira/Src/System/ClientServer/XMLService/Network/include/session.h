
#ifndef _session_h
#define _session_h

#include "comm.h"
#include "driver.h"
#include "service.h"

class cSession
{
public:
   cSession(cDriver * driver);
   virtual ~cSession();
   virtual void startService() = 0;
   virtual int send(const OCTET_T * output, LENGTH_T length) = 0;
public:
   inline cService * service() const {return _service;};
   inline cDriver * driver() const {return _driver;};
protected:
   cDriver * _driver;
   cService * _service;
};

#endif // _session_h_
