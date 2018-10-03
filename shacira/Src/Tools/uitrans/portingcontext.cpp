
#include "portingcontext.h"

void PortingContext::collectFiles()
{
   APPLICATION_MAP_T::const_iterator i = _applicationMap.cbegin();
   while (i != _applicationMap.cend()) {
      PortingApplication * application = (*i).second;
      application->collectFiles();;
      i++;
   }
}

void PortingContext::portFiles()
{
   APPLICATION_MAP_T::const_iterator i = _applicationMap.cbegin();
   while (i != _applicationMap.cend()) {
      PortingApplication * application = (*i).second;
      application->portFiles();;
      i++;
   }
}

void PortingContext::generateResources()
{
   APPLICATION_MAP_T::const_iterator i = _applicationMap.cbegin();
   while (i != _applicationMap.cend()) {
      PortingApplication * application = (*i).second;
      application->generateResources();
      i++;
   }
}

