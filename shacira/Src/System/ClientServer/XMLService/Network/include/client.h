
#ifndef _client_h_
#define _client_h_

#include "comm.h"
#include "driver.h"
#include "service.h"

#define WAIT_FOR_EVER   0xffffffff

class cClient
{
public:
   cClient(cDriver * driver);
   virtual ~cClient();
   virtual int execute() = 0;
   virtual int send(const OCTET_T * output, LENGTH_T length) = 0;
   virtual int wait(unsigned long timeout = WAIT_FOR_EVER) = 0;
   virtual int connect() = 0;
public:
   inline cService * service() const {return _service;};
   inline void setService(cService * service) {_service = service;};
   inline cDriver * driver() const {return _driver;};
   inline int receiveBuffer(cByteBuffer & reply) const {reply = _receiveBuffer; return 0;};
   inline bool connected() const {return _connected;};
   inline bool terminated() const {return _terminated;};
protected:
   cDriver * _driver;
   cService * _service;
   cByteBuffer _receiveBuffer;
   bool _connected;
   bool _terminated;
};

#endif // _client_h_
