


#include "FirstHeader.h"
#include "System/Objects/cTransientObject.h"
#include "System/Database/cContext.h"
#include "Control/Cell/Programs/cTestProgram.h"
#include "System/Objects/cInfo.h"

cTestProgram::cTestProgram (cConfigurationObject * config_obj, cContext *context)
      : cProgram(config_obj, context)
{
   _Context = context;
   _IdleTime = 10;
}


cTestProgram::~cTestProgram()
{
}

void cTestProgram::ProcessEvent (cTransientObject *object)
{
}

void cTestProgram::Cycle ()
{
}

