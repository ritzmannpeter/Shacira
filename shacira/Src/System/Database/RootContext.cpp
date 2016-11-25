
#include "FirstHeader.h"
#include "RootContext.h"
#include "System/Database/cContext.h"

cContext * RootContext::_Context = 0;

void RootContext::Set(cContext * context)
{
   if (context->get_IsRootContext() ||
       context->IsRemote()) {
      _Context = context;
   }
}

cContext * RootContext::Context()
{
   return _Context;
}

