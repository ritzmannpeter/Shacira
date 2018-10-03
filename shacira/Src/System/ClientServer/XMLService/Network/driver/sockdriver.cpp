
#include "sockdriver.h"
#include "socksession.h"

cSockDriver::cSockDriver(short port, cServiceFactory * serviceFactory)
   : cDriver(false, serviceFactory), _port(port)
{
   initializeSockets();
   _driverType = cDriver::SOCKETIO;
}

cSockDriver::~cSockDriver()
{
}

cClient * cSockDriver::createClient()
{
   // client interface not supported
   return NULL;
}

int cSockDriver::run()
{
   try {
      int rc = mainLoop();
      return rc;
   } catch (std::exception& e) {
      COMM_ASSERT(e.what());
      return -1;
   } catch (...) {
      COMM_ASSERT("unhandled exception");
      return -1;
   }
}

void cSockDriver::handleAccept(SOCKET socket)
{
   addSession(socket);
}

int cSockDriver::mainLoop()
{
   SOCKET listenSocket;
   struct protoent * protoentry = NULL;
   if ((protoentry = ::getprotobyname("tcp")) == NULL)	{
	   cout << "getprotobyname() failed" << endl;
	   return -1;
	}
   if ((listenSocket = ::socket(PF_INET, SOCK_STREAM, protoentry->p_proto)) == INVALID_SOCKET) {
	   cout << "socket() failed" << endl;
	   return -1;
	}
   int on = 1;
   if (::setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0) {
	   cout << "setsockopt() failed" << endl;
	   return -1;
   }
   struct sockaddr_in ownaddress = {0};
   ownaddress.sin_family = AF_INET;
   ownaddress.sin_port = htons(_port);
   ownaddress.sin_addr.s_addr = INADDR_ANY;

	/* bind socket */
	cout << "bind(" << inet_ntoa(ownaddress.sin_addr) << ")" << endl;
	if (::bind(listenSocket, (struct sockaddr *)&ownaddress, sizeof(ownaddress)) == -1) {
	   cout << "bind() failed" << endl;
	   return -1;
	}
   cout << "service succesfully bound to port " << _port << endl;

	/* accept and recvfrom expect int-pointers ... */
	struct sockaddr_in remoteaddress = {0};
	int address_length = sizeof(remoteaddress);

	/* initialize remoteaddress */
	memset(&remoteaddress, 0, sizeof(remoteaddress));

	/* listen for connection attempts */
   int maxConnections = 6;
	if (::listen(listenSocket, maxConnections) == -1) {
	   cout << "listen() failed" << endl;
		return -1;
   }
   cout << "service listening (max " << maxConnections << " connections) ..." << endl;
   fd_set socks;
   while (true) {
      FD_ZERO(&socks);
      FD_SET(listenSocket, &socks);
      SESSION_MAP_T::const_iterator i = _sessionMap.cbegin();
      while (i != _sessionMap.cend()) {
         SOCKET socket = (*i).first;
         FD_SET(socket, &socks);
         i++;
      }
      struct timeval timeout;
		timeout.tv_sec = 100;
		timeout.tv_usec = 0;
      int readsocks = ::select(listenSocket + 1, &socks, (fd_set*)0, (fd_set*)0, &timeout);
		if (readsocks < 0) {
   	   cout << "select() failed" << endl;
         exit(-1);
      } else if (readsocks == 0) {
   	   cout << ".";
			fflush(stdout);
      } else {
			readSockets(listenSocket, &socks);
      }
   }
   ::closesocket(listenSocket);
   return 0;
}

void cSockDriver::addSession(SOCKET socket)
{
   cSockSession * session = new cSockSession(socket, this);
   _sessionMap[socket] = session;
}

void cSockDriver::removeSession(SOCKET socket)
{
   cSockSession * session = this->session(socket);
   if (session != NULL) {
      _sessionMap.erase(socket);
      delete session;
   }
}

cSockSession * cSockDriver::session(SOCKET socket)
{
   SESSION_MAP_T::const_iterator i = _sessionMap.find(socket);
   if (i != _sessionMap.cend()) {
      return (*i).second;
   } else {
      return NULL;
   }
}

void cSockDriver::readSockets(SOCKET socket, fd_set * socks)
{
   if (FD_ISSET(socket, socks)) {
      // a new connection
		handleConnect(socket, socks);
   } else {
      SOCKET_LIST_T socketList;
      SESSION_MAP_T::const_iterator i = _sessionMap.cbegin();
      while (i != _sessionMap.cend()) {
         SOCKET s = (*i).first;
         if (FD_ISSET(s, socks)) {
            socketList.push_back(s);
         }
         i++;
      }
      SOCKET_LIST_T::const_iterator j = socketList.begin();
      while (j != socketList.end()) {
         SOCKET s = (*j);
         handleData(s, socks);
         j++;
      }
   }
}

void cSockDriver::handleConnect(SOCKET socket, fd_set * socks)
{
	SOCKET newSocket = INVALID_SOCKET;
	/* We have a new connection coming in!  We'll try to find a spot for it in connectlist. */
	newSocket = accept(socket, NULL, NULL);
	if (newSocket == INVALID_SOCKET) {
      cout << "accept() failed" << endl;
      return;
	}
	setNonBlocking(newSocket);
   cout << "connect()" << newSocket << endl;
   handleAccept(newSocket);
}

void cSockDriver::handleData(SOCKET socket, fd_set * socks)
{
   char buffer[80] = {0};
   int rc = ::recv(socket, buffer, sizeof(buffer), 0);
   if (rc < 0) {
      // disconnected
      handleDisconnect(socket, socks);
   } else if (rc == 0) {
      // probably disconnected
      handleDisconnect(socket, socks);
   } else {
      // handle read data
      cout << "read() on " << socket << " = " <<  rc << endl;
      cSockSession * session = this->session(socket);
      if (session != NULL) {
         cSockError error;
         session->handle_read(error, (unsigned char*)buffer, rc);
      }
   }
}

void cSockDriver::handleDisconnect(SOCKET socket, fd_set * socks)
{
   removeSession(socket);
   cout << socket << " disconnected" << endl;
}

void cSockDriver::setNonBlocking(SOCKET socket)
{
   u_long arg = 1;
   int rc = ::ioctlsocket(socket, FIONBIO, &arg);
}

void cSockDriver::initializeSockets()
{
   WORD req_version = MAKEWORD(2, 2);
   WSADATA wsa_data;
   int err = WSAStartup(req_version, &wsa_data);
   if (err != 0) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
   }
   /* Confirm that the WinSock DLL supports 2.2.*/
   /* Note that if the DLL supports versions greater    */
   /* than 2.2 in addition to 2.2, it will still return */
   /* 2.2 in wVersion since that is the version we      */
   /* requested.                                        */
   if (LOBYTE(wsa_data.wVersion) != 2 ||
       HIBYTE(wsa_data.wVersion) != 2) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      WSACleanup();
   }
}

