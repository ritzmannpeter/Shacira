

#include "FirstHeader.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Database/cContext.h"
#include "Control/Cell/cProgram.h"

extern "C" {

#ifdef _USRDLL
   
__SH_DLL_EXPORT__ cProgram * CreateProgram(cConfigurationObject * config_obj, cContext * context)
{
   return _CreateProgram(config_obj, context);
}

#endif

}
