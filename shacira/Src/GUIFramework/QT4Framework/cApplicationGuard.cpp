
#include "FirstHeader.h"
#include "cApplicationGuard.h"
#include "System/Process/cResources.h"

cApplicationGuard::cApplicationGuard()
{
   if (qApp != NULL) {
      QObject::connect(qApp, SIGNAL(lastWindowClosed()), this, SLOT(Shutdown()));
      QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(Shutdown()));
   }
}

cApplicationGuard::~cApplicationGuard()
{
}

void cApplicationGuard::Shutdown()
{
   cResources::ShutDown();
}


