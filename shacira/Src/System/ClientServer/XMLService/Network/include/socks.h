
#ifndef _socks_h_
#define _socks_h_

#include "comm.h"
#include <winsock2.h>

class cSockError
{
public:
   cSockError()
      : _errorCode(0)
   {
   };
   cSockError(int errorCode)
      : _errorCode(errorCode)
   {
   };
   bool operator!() const
   {
      return _errorCode == 0;
   };
   int code() const {return _errorCode;};
   std::string message() const {return _errorMessage;};
private:
   int _errorCode;
   std::string _errorMessage;
};

#endif // _socks_h__
