
#include "FirstHeader.h"
#include "System\Sys\cSHFile.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Objects/cTransientObject.h"
#include "System/Database/cContext.h"
#include "System/Database/cVariable.h"
#include "System/Objects/cInfo.h"
#include "System/Objects/cAlarm.h"
#include "System/Objects/cDataChange.h"
#include "System/Objects/cJobEntry.h"
#include "System/Structs/cExtendedObjectRing.h"
#include "Language/cEM63StyxParser.h"
#include "Control/Device/EM63/cEM63Interface.h"
#include "Control/Device/EM63/cEM63Session.h"
#include "Programs/EM63Program.h"

EM63Program::EM63Program(cConfigurationObject * config_obj, cContext *context)
      : cEM63Program(config_obj, context)
{
}

EM63Program::~EM63Program()
{
}

void EM63Program::ProcessEvent(cTransientObject *object)
{
   try {  
      ULONG_T object_type = object->get_Type();
      if(object_type == OT_JOB_ENTRY) {
      } else if(object_type == OT_DATA_CHANGE) {
         cDataChange * data_change =(cDataChange*)object;
         ULONG_T var_type = data_change->get_VarType();
         if(var_type == SH_VAR_SET) {
            STRING_T user = data_change->get_UserName();
            STRING_T var_name = data_change->get_VarName();
            if(!user.empty()) {
//               if(!isExcluded(var_name)) {    
                  _Interface->SetEvent(data_change);
//               }
            }
         }
      } else if(object_type == OT_ALARM) {
         _Interface->SetEvent(object);
      }
   } catch(cError & e) {
      ErrorPrintf("%s while processing event in %s\n", e.ErrMsg().c_str(), _Name.c_str());
   } catch(...) {
      ErrorPrintf("unhandled exception while processing event in %s\n", _Name.c_str());
   }
}

void EM63Program::Initialize()
{
   cEM63Program::Initialize();
}

STRING_T EM63Program::RootDirectory()
{
   return SessionDirectory();
}

STRING_T EM63Program::SessionDirectory()
{
   return "\\\\wilma\\public\\user\\EM63";
}

STRING_T EM63Program::LD()
{
   return ",";
}

STRING_T EM63Program::DatasetId(CONST_STRING_T keyword)
{
   if(stricmp(keyword, "active") == 0) {
      return "dset[0]";
   } else if(stricmp(keyword, "foreground") == 0) {
      return "dset[0]";
   } else if(stricmp(keyword, "background") == 0) {
      return "dset[1]";
   } else {
      return "unknown";
   }
}

STRING_T EM63Program::ShotCounterId()
{
   return "ActCntMachAdd";
}

LONG_T EM63Program::ShotCounterValue()
{
   LONG_T value = 0;
   GetVar(ShotCounterId().c_str(), value);
   return value;
}

ULONG_T EM63Program::InjUnitNbrValue()
{
   ULONG_T value = 0;
   GetVar("InjUnits", value);
   return value;
}

STRING_T EM63Program::MoldNbrValue()
{
   STRING_T value;
   GetVar("SetDescMachMldName", value);
   return value;
}

STRING_T EM63Program::MachNbrValue()
{
   STRING_T value;
   GetVar("MashineNr", value);
   return value;
}

STRING_T EM63Program::MaterialNbrValue()
{
   STRING_T value;
   GetVar("SetDescMachTxtMaterial", value, 0);
   return value;
}

STRING_T EM63Program::MachVendor()
{
   return "Ferromatik Milacron Maschinenbau GmbH";
}

STRING_T EM63Program::MachDesc()
{
   STRING_T value;
   GetVar("MashineType", value);
   return value;
}

STRING_T EM63Program::ContrType()
{
   return cEM63Program::ContrType();
}

STRING_T EM63Program::ContrVersion()
{
   return cEM63Program::ContrVersion();
}

ULONG_T EM63Program::MaxJobs()
{
   return cEM63Program::MaxJobs();
}

ULONG_T EM63Program::MaxChanges()
{
   return cEM63Program::MaxChanges();
}

ULONG_T EM63Program::MaxAlarms()
{
   return cEM63Program::MaxAlarms();
}

ULONG_T EM63Program::MaxCurrentAlarms()
{
   return cEM63Program::MaxCurrentAlarms();
}

ULONG_T EM63Program::MaxReports()
{
   return cEM63Program::MaxReports();
}

ULONG_T EM63Program::MaxArchives()
{
   return cEM63Program::MaxArchives();
}

ULONG_T EM63Program::MaxSessions()
{
   return cEM63Program::MaxSessions();
}

STRING_T EM63Program::CharDef()
{
   return cEM63Program::CharDef();
}

STRING_T EM63Program::Version()
{
   return cEM63Program::Version();
}






