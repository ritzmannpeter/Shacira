
#ifndef cs_h
#define cs_h 1

// TCP/IP-based Client server

#ifdef OBSOLETE

class cSocketError {
public:
   cSocketError(int err, const char * function)
   {
      _SocketError = err;
      _SocketFunction = function;
   };
   virtual ~cSocketError() {};
public:
   int _SocketError;
   const char * _SocketFunction;
};

#endif

#endif
