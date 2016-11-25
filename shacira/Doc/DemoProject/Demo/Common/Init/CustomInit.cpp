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

// helper functions to set and get variable values

void SetVar(cLocalContext * context, CONST_STRING_T var_name, USHORT_T value,
            LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   cVariable * variable = context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4);
   }
}

void SetLongVar(cLocalContext * context, CONST_STRING_T var_name, LONG_T value,
            LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   cVariable * variable = context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4);
   }
}

void SetVar(cLocalContext * context, CONST_STRING_T var_name, CONST_STRING_T value,
            LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   cVariable * variable = context->Variable(var_name);
   if (variable != NULL) {
      variable->Set(value, i1, i2, i3, i4);
   }
}

void GetVar (cLocalContext * context, CONST_STRING_T var_name, USHORT_T &value,
             LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   cVariable * variable = context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4);
   }
}

void GetVar(cLocalContext * context, CONST_STRING_T var_name, STRING_T &value,
            LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   cVariable * variable = context->Variable(var_name);
   if (variable != NULL) {
      variable->Get(value, i1, i2, i3, i4);
   }
}

