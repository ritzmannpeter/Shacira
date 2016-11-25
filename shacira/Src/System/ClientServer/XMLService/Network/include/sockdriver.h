
#ifndef _sockdriver_h_
#define _sockdriver_h_

#include "driver.h"
#include "socksession.h"

typedef map<SOCKET,cSockSession*> SESSION_MAP_T;
typedef list<SOCKET> SOCKET_LIST_T;

class COMM_EXPORT cSockDriver : public cDriver
{
public:
   cSockDriver(short port, cServiceFactory * serviceFactory);
   cSockDriver(const std::string & host, short port, cServiceFactory * serviceFactory);
   virtual ~cSockDriver();
   virtual cClient * createClient();
   virtual int run();
   inline std::string host() {return _host;};
   inline short port() {return _port;};
private:
   void handleAccept(SOCKET socket);
   int mainLoop();
   void addSession(SOCKET socket);
   void removeSession(SOCKET socket);
   cSockSession * session(SOCKET socket);
   void readSockets(SOCKET socket, fd_set * socks);
   void handleConnect(SOCKET socket, fd_set * socks);
   void handleData(SOCKET socket, fd_set * socks);
   void handleDisconnect(SOCKET socket, fd_set * socks);
   void setNonBlocking(SOCKET socket);
   void initializeSockets();
private:
   std::string _host;
   short _port;
   SESSION_MAP_T _sessionMap;
};

#endif // _sockdriver_h__
