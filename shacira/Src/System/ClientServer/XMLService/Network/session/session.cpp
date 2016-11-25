
#include "session.h"

cSession::cSession(cDriver * driver)
   : _driver(driver), _service(NULL)
{
   _service = _driver->createService(this);
}

cSession::~cSession()
{
   if (_service != NULL) {
      delete _service;
   }
}

