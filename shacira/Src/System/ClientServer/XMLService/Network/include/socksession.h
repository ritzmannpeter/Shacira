
#ifndef _socksession_h_
#define _socksession_h_

#include "socks.h"
#include "session.h"
class cService;

class cSockSession : public cSession
{
public:
   cSockSession(SOCKET socket, cDriver * driver);
   virtual ~cSockSession();
   virtual void startService();
   virtual int send(const OCTET_T * output, LENGTH_T length);
   void handle_read(const cSockError & error, unsigned char * data, size_t bytes_transferred);
public:
   inline SOCKET & socket() {return _socket;};
private:
   SOCKET _socket;
};

#endif // _socksession_h_
