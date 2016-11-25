
#include "FirstHeader.h"
#include "System/Text/cText.h"
#include "Control/LocalDatabase/cLocalContext.h"
#include "System/Database/cVariable.h"
#include "Control/Device/cDevice.h"

BOOL_T _MdlInit(ULONG_T step, cLocalContext * context)
{
   // phase 2

   if (step == SH_PRE_CONTEXT_INSTANTIATION) {
   }

   if (step == SH_PRE_CONTEXT_CREATION) {
   }

   if (step == SH_POST_CONTEXT_CREATION) {
   }

   if (step == SH_POST_CONTEXT_INSTANTIATION) {
   }

   // phase 4

   if (step == SH_PRE_SYSTEM_STARTUP) {
   }

   if (step == SH_PRE_LOAD_DATA) {
      // hibernate
   }

   if (step == SH_INITIALIZE_DATA) {
      // BBRAM init
   }

   if (step == SH_DATA_INITIALIZED) {
   }

   if (step == SH_PRE_UPLOAD) {
   }

   if (step == SH_POST_UPLOAD) {
   }

   if (step == SH_PRE_DOWNLOAD) {
   }

   if (step == SH_POST_DOWNLOAD) {
   }

   if (step == SH_CACHE_IS_FREE) {
   }

   if (step == SH_POST_SYSTEM_STARTUP) {
   }

   return true;
}

