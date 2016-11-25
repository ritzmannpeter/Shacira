
#include "FirstHeader.h"
#include "configure_app.h"
#include "System/Database/cFuncRef.h"
#include "System/cCustomFunctions.h"
#include "System/Sys/cSharedLibrary.h"

static FUNC_ADDRESS_T DLLFuncAddress(CONST_STRING_T library_name, CONST_STRING_T func_name)
{
   FUNC_ADDRESS_T func_address = NULL;
   cSharedLibrary * library = cSharedLibrary::Library(library_name);
   if (library != NULL) {
      try {
         library->Load();
         func_address = (FUNC_ADDRESS_T)library->FunctionAddress(func_name);
      } catch (cError & e) {
         ErrorPrintf("failed to load shared library %s: %s\n", library->LibraryName().c_str(), (const char*)e);
      } catch (...) {
         ErrorPrintf("failed to load shared library %s\n", library->LibraryName().c_str());
      }
   }
   return func_address;
}

#include "System/ApplicationInterface.h"

void ConfigureApp()
{
   bool successs = InitializeApplicationInterface(_MdlInit,
                                                  _GUIInit,
                                                  _GetCustomText);
   cCustomFunctions::GetCustomTextFuncAddress(_GetCustomText);
   cCustomFunctions::DeviceCreatorFuncAddress(_CreateDevice);
   cCustomFunctions::ProgramCreatorFuncAddress(_CreateProgram);
   cCustomFunctions::ShareAppframeFuncAddress(_ShareAppframe);
}
