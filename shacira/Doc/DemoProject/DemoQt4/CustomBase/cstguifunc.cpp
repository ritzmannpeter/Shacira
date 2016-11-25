#include "FirstHeader.h"
#include "cwidgetbase.h"
#include "System/Database/cContext.h"
#include "System/Database/FuncSpecs.h"
#ifdef _USRDLL
#include "GUIFuncHeaders"
#else
#include "Funcs/GUIFuncHeaders"
#endif

extern "C" {

static FUNC_ENTRY_T ClientFuncTable[] = {
#ifdef _USRDLL
#include "GUIFuncEntries"
#else
#include "Funcs/GUIFuncEntries"
#endif
   {NULL, (FUNC_T)NULL}
};

VOID_FUNC_T _GUIFuncAddr(UCHAR_T func_class, CONST_STRING_T func_name)
{
   FUNC_ENTRY_T * entry = ClientFuncTable;
   while (entry->func_name != NULL) {
      if (strcmp(func_name, entry->func_name) == 0) {
         if (entry->func_class == func_class) {
            return entry->func_ptr;
         }
      }
      entry++;
   }
   return NULL;
}

#ifdef _USRDLL

__SH_DLL_EXPORT__ BOOL_T GUIInit(ULONG_T step, cContext * context)
{
   return _GUIInit(step, context);
}

__SH_DLL_EXPORT__ VOID_FUNC_T GUIFuncAddr(UCHAR_T func_class, CONST_STRING_T func_name)
{
   return _GUIFuncAddr(func_class, func_name);
}

__SH_DLL_EXPORT__ void ShareAppframe(CAppFrame * app_frame)
{
   _ShareAppframe(app_frame);
}

#endif

}

