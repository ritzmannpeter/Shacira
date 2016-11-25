
#ifndef _demo2program_h
#define _demo2program_h

#include "Control/Cell/cProgram.h"
#include "Control/Device/cDevice.h"

class Demo2Program : public cProgram
{
public:
   Demo2Program (cConfigurationObject * config_obj, cContext *context);
   virtual ~Demo2Program();
protected:
   virtual void ExecuteCommand(ULONG_T command);
   virtual void ProcessEvent (cTransientObject *object);
   virtual void Cycle ();
   virtual void Initialize();
};

#endif
