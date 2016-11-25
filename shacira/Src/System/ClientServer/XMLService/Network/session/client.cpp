
#include "client.h"

cClient::cClient(cDriver * driver)
   : _driver(driver), _connected(false), _terminated(false)
{
   _service = _driver->createService(this);
}

cClient::~cClient()
{
   if (_service != NULL) {
      delete _service;
   }
}

