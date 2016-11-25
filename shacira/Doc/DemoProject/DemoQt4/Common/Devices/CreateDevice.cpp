
#include "FirstHeader.h"
#include "System/Config/cConfigurationObject.h"
#include "Control/Cell/cCell.h"
#include "cDemoDevice.h"

extern "C" {

cDevice * _CreateDevice(cConfigurationObject * config_obj, cCell * cell)
{
   STRING_T device_type = config_obj->PropertyValue("DeviceType", "", true);
   if (IDENTIFIER_EQUAL(device_type.c_str(), "DemoDevice")) {
      return new cDemoDevice(config_obj, cell);
   } else {
      return NULL;
   }
}

}
