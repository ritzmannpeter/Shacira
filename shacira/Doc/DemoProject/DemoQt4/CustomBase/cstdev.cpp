

#include "FirstHeader.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Database/cContext.h"
#include "Control/Cell/cCell.h"
#include "Control/Device/cDevice.h"

extern "C" {

#ifdef _USRDLL

__SH_DLL_EXPORT__ cDevice * CreateDevice(cConfigurationObject * config_obj, cCell * cell)
{
   return _CreateDevice(config_obj, (cCell*) cell);
}

#endif

}
