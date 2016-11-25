
#include "portingcontext.h"

void PortingContext::collectFiles()
{
   APPLICATION_MAP_T::const_iterator i = _applicationMap.begin();
   while (i != _applicationMap.end()) {
      PortingApplication * application = (*i).second;
      application->collectFiles();;
      i++;
   }
}

void PortingContext::portFiles()
{
   APPLICATION_MAP_T::const_iterator i = _applicationMap.begin();
   while (i != _applicationMap.end()) {
      PortingApplication * application = (*i).second;
      application->portFiles();;
      i++;
   }
}

void PortingContext::generateResources()
{
   APPLICATION_MAP_T::const_iterator i = _applicationMap.begin();
   while (i != _applicationMap.end()) {
      PortingApplication * application = (*i).second;
      application->generateResources();
      i++;
   }
}

void PortingContext::printFormHeaderInformations()
{
   APPLICATION_MAP_T::const_iterator i = _applicationMap.begin();
   while (i != _applicationMap.end()) {
      PortingApplication * application = (*i).second;
      application->printFormHeaderInformations();
      i++;
   }
}

