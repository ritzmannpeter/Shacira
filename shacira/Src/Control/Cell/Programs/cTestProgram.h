
#ifndef cTestProgram_h
#define cTestProgram_h 1

#include "Control/Cell/cProgram.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cTestProgram : public cProgram
{
public:
   cTestProgram (cConfigurationObject * config_obj, cContext *context);
   virtual ~cTestProgram();
protected:
   virtual void ProcessEvent (cTransientObject *object);
   virtual void Cycle ();
};

#endif
