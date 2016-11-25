
#include "FirstHeader.h"
#include "System/Database/cContext.h"
#include "System/Database/FuncSpecs.h"
#ifdef _USRDLL
#include "MdlFuncHeaders"
#else
#include "Funcs/MdlFuncHeaders"
#endif

extern "C" {

static FUNC_ENTRY_T MdlFuncTable[] = {
#ifdef _USRDLL
#include "MdlFuncEntries"
#else
#include "Funcs/MdlFuncEntries"
#endif
   {NULL, (FUNC_T)NULL}
};

VOID_FUNC_T _MdlFuncAddr(UCHAR_T func_class, CONST_STRING_T func_name)
{
   FUNC_ENTRY_T * entry = MdlFuncTable;
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

__SH_DLL_EXPORT__ VOID_FUNC_T MdlFuncAddr(UCHAR_T func_class, CONST_STRING_T func_name)
{
   return _MdlFuncAddr(func_class, func_name);
}

#endif

}
