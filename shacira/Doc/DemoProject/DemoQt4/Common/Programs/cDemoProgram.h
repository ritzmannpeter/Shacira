
#ifndef cDemoProgram_h
#define cDemoProgram_h 1


#include "Control/Cell/cProgram.h"
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cContext;

class __DLL_EXPORT__ cDemoProgram : public cProgram
{
public:
   cDemoProgram (cConfigurationObject * config_obj, cContext *context);
   virtual ~cDemoProgram();

protected:
   virtual void ExecuteCommand(ULONG_T command);
   virtual void ProcessEvent (cTransientObject *object);
   virtual void Cycle ();
   virtual void Initialize();

private:
   BOOL_T _Count;

};

#endif
