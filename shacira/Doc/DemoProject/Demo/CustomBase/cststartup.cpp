

#include "FirstHeader.h"
#include "Control/LocalDatabase/cLocalContext.h"
#include "CustomText.h"

extern BOOL_T CustomInitialize(ULONG_T step, cLocalContext * context);

extern "C" {

__SH_DLL_EXPORT__ BOOL_T MdlInit(ULONG_T step, cLocalContext * context)
{
   return _MdlInit(step, context);
}

__SH_DLL_EXPORT__ CONST_STRING_T GetCustomText(ULONG_T text_id)
{
   return _GetCustomText(text_id);
}

}
