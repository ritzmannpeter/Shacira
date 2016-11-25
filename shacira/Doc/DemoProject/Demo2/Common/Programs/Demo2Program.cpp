
#include "FirstHeader.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Objects/cTransientObject.h"
#include "System/Database/cContext.h"
#include "System/Objects/cInfo.h"
#include "System/Objects/cAlarm.h"
#include "System/Objects/cDataChange.h"
#include "System/Objects/cJobEntry.h"
#include "Demo2Program.h"
#include "System/ApplicationInterface.h"

REGISTER_PROGRAM("Demo2Program", Demo2Program)

Demo2Program::Demo2Program (cConfigurationObject * config_obj, cContext *context)
      : cProgram(config_obj, context)
{
}

Demo2Program::~Demo2Program()
{
}

void Demo2Program::ExecuteCommand(ULONG_T command)
{
}

void Demo2Program::ProcessEvent (cTransientObject *object)
{
}

void Demo2Program::Cycle ()
{
return;
//   cSystemUtils::AcousticSignal(50,50);
   ULONG_T value = rand() % 100;
   SetVar("test_var", value);
   RefreshVar("current_second");
}

void Demo2Program::Initialize()
{
}

