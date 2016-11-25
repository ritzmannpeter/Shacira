

#include "FirstHeader.h"
#include "System/Config/cConfigurationObject.h"
#include "Control/Device/cS7Device.h"
#include "System/Process/cResources.h"

extern "C" {

__SH_DLL_EXPORT__ cDevice * CreateDevice(cConfigurationObject * config_obj, cCell * cell)
{
   cResources(0, NULL);
   return new cS7Device(config_obj, (cCell*)cell);
}

}
