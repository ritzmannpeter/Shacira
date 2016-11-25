
#ifndef _robot2program_h
#define _robot2program_h

#include "Control/Cell/cProgram.h"
#include "Control/Device/cDevice.h"

class RobotProgram : public cProgram
{
public:
   RobotProgram (cConfigurationObject * config_obj, cContext *context);
   virtual ~RobotProgram();
protected:
   virtual void ExecuteCommand(ULONG_T command);
   virtual void ProcessEvent (cTransientObject *object);
   virtual void Cycle ();
   virtual void Initialize();
};

#endif
