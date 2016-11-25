
#ifndef _cService_h
#define _cService_h

#include "cSocketApi.h"
class cTCPServer;
class cServiceHandler;
class cFrameHandler;

class cService
{
public:
   cService() : _FrameHandler(NULL), _Server(NULL), _ServiceHandler(NULL) {};
   virtual ~cService() {};
   inline cTCPServer * Server() {return _Server;};
   inline void SetFrameHandler(cFrameHandler * frame_handler) {_FrameHandler = frame_handler;};
   inline cFrameHandler * FrameHandler() {return _FrameHandler;};
   inline void SetServer(cTCPServer * server) {_Server = server;};
   inline cServiceHandler * ServiceHandler() {return _ServiceHandler;};
   inline void SetServiceHandler(cServiceHandler * service_handler) {_ServiceHandler = service_handler;};
   virtual int Request(const unsigned char * request, int request_len, unsigned char * & response, int & response_len);
protected:
   cTCPServer * _Server;
   cFrameHandler * _FrameHandler;
   cServiceHandler * _ServiceHandler;
};

#endif
