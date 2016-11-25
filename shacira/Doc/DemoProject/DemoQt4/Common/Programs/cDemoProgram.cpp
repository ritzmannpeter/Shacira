
#include "FirstHeader.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Objects/cTransientObject.h"
#include "System/Database/cContext.h"
#include "System/Objects/cInfo.h"
#include "System/Objects/cAlarm.h"
#include "System/Objects/cDataChange.h"
#include "System/Objects/cJobEntry.h"
#include "cdemoprogram.h"


cDemoProgram::cDemoProgram (cConfigurationObject * config_obj, cContext *context)
      : cProgram(config_obj, context)
{
_ASSERT_COND(config_obj != NULL)
   _Count = false;
}

cDemoProgram::~cDemoProgram()
{
}


void cDemoProgram::ExecuteCommand(ULONG_T command)
{
   if (command == 1) {
      _Count = true;
   } else if (command == 0) {
      _Count = false;
   }
}

void cDemoProgram::ProcessEvent (cTransientObject *object)
{
  try {  
      ULONG_T object_type = object->get_Type();
      if (object_type == OT_JOB_ENTRY) {    // process trend data
         cJobEntry * entry = (cJobEntry*)object;
      } else if (object_type == OT_DATA_CHANGE) {  // process data change
         cDataChange * cdcData = (cDataChange*)object;
//         Beep(50,50);
      } else if (object_type == OT_ALARM) {
         cAlarm * alarm = (cAlarm*)object;
      }
   } catch(cError & e) {
      ErrorPrintf("%s while processing event in %s\n", e.ErrMsg().c_str(), _Name.c_str());
   } catch(...) {
      ErrorPrintf("unhandled exception while processing event in %s\n", _Name.c_str());
   }
}

void cDemoProgram::Cycle ()
{
   if (_Count) {
      ULONG_T index1 = 0, index2 = 0;
      FLOAT_T value = 0;
      GetVar("index1", index1);
      GetVar("index2", index2);
      GetVar("matrix1", value, index1, index2);
      value += (FLOAT_T)0.1;
      SetVar("matrix1", value, index1, index2);
   }
}

void cDemoProgram::Initialize()
{
}

