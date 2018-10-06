//## begin module%4380805F01D0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380805F01D0.cm

//## begin module%4380805F01D0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380805F01D0.cp

//## Module: cGetInfoCmd%4380805F01D0; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cGetInfoCmd.cpp

//## begin module%4380805F01D0.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4380805F01D0.additionalIncludes

//## begin module%4380805F01D0.includes preserve=yes
//## end module%4380805F01D0.includes

// cGetInfoCmd
#include "Control/Device/EM63/cGetInfoCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%4380805F01D0.additionalDeclarations preserve=yes
//## end module%4380805F01D0.additionalDeclarations


// Class cGetInfoCmd 

cGetInfoCmd::cGetInfoCmd()
  //## begin cGetInfoCmd::cGetInfoCmd%.hasinit preserve=no
  //## end cGetInfoCmd::cGetInfoCmd%.hasinit
  //## begin cGetInfoCmd::cGetInfoCmd%.initialization preserve=yes
  //## end cGetInfoCmd::cGetInfoCmd%.initialization
{
  //## begin cGetInfoCmd::cGetInfoCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cGetInfoCmd::cGetInfoCmd%.body
}

cGetInfoCmd::cGetInfoCmd(const cGetInfoCmd &right)
  //## begin cGetInfoCmd::cGetInfoCmd%copy.hasinit preserve=no
  //## end cGetInfoCmd::cGetInfoCmd%copy.hasinit
  //## begin cGetInfoCmd::cGetInfoCmd%copy.initialization preserve=yes
  //## end cGetInfoCmd::cGetInfoCmd%copy.initialization
{
  //## begin cGetInfoCmd::cGetInfoCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cGetInfoCmd::cGetInfoCmd%copy.body
}

cGetInfoCmd::cGetInfoCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cGetInfoCmd::cGetInfoCmd%1136548772.hasinit preserve=no
  //## end cGetInfoCmd::cGetInfoCmd%1136548772.hasinit
  //## begin cGetInfoCmd::cGetInfoCmd%1136548772.initialization preserve=yes
  : cPresentationCmd(job, command_name)
  //## end cGetInfoCmd::cGetInfoCmd%1136548772.initialization
{
  //## begin cGetInfoCmd::cGetInfoCmd%1136548772.body preserve=yes
   _CommandType = EM63_GETINFO_COMMAND;
   INCREMENT_OBJECT_COUNT()
   //## end cGetInfoCmd::cGetInfoCmd%1136548772.body
}


cGetInfoCmd::~cGetInfoCmd()
{
  //## begin cGetInfoCmd::~cGetInfoCmd%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cGetInfoCmd::~cGetInfoCmd%.body
}



//## Other Operations (implementation)
BOOL_T cGetInfoCmd::Process (cContext *context)
{
  //## begin cGetInfoCmd::Process%1135093202.body preserve=yes
   return true;
  //## end cGetInfoCmd::Process%1135093202.body
}

BOOL_T cGetInfoCmd::Start ()
{
  //## begin cGetInfoCmd::Start%1135093203.body preserve=yes
   if (HasFailed()) {
      return false;
   }
   if (!IsStarted()) {
      Started();
      STRING_T ld = _Interface->LD();
      ld += "\t";
      STRING_T info;
      AddString(info, "MachVendor", _Interface->MachVendor().c_str(), ld.c_str());
      AddString(info, "MachNbr", _Interface->MachNbrValue().c_str(), ld.c_str());
      AddString(info, "MachDesc", _Interface->MachDesc().c_str(), ld.c_str());
      AddString(info, "ContrType", _Interface->ContrType().c_str(), ld.c_str());
      AddString(info, "ContrVersion", _Interface->ContrVersion().c_str(), ld.c_str());
      AddString(info, "Version", _Interface->Version().c_str(), ld.c_str());
      AddInteger(info, "MaxJobs", _Interface->MaxJobs(), ld.c_str());
      AddEventTypes(_Interface, info, ld.c_str()),
      AddInteger(info, "MaxReports", _Interface->MaxReports(), ld.c_str());
      AddInteger(info, "MaxArchives", _Interface->MaxArchives(), ld.c_str());
      AddInteger(info, "InjUnitNbr", _Interface->InjUnitNbrValue(), ld.c_str());
      AddString(info, "MaterialNbr", _Interface->MaterialNbrValue().c_str(), ld.c_str());
      AddString(info, "CharDef", _Interface->CharDef().c_str(), ld.c_str());
      AddInteger(info, "MaxSessions", _Interface->MaxSessions(), ld.c_str());
      AddActiveJobs(_Interface, info, ld.c_str());
      AddActiveReports(_Interface, info, ld.c_str());
      AddActiveEvents(_Interface, info, ld.c_str());
#ifdef EM63_LOGGING_INTERFACE
      int rc = 0;
      if ((rc = _Interface->Put(CAT_SYNC, _OutputFile.c_str(), info.c_str(), 0)) < 0) {
         Failed(CREATE_DESTINATION_FILE, _OutputFile.c_str());
         Terminated();
         return false;
      }
#else
      cAbstractFileSystem * file_system = _Interface->FileSystem();
      if (file_system != NULL) {
         file_system->Put(_OutputFile.c_str(), info.c_str(), 0);
      } else {
      }
#endif
      Terminated();
      return true;
   } else {
      return false;
   }
  //## end cGetInfoCmd::Start%1135093203.body
}

void cGetInfoCmd::Stop ()
{
  //## begin cGetInfoCmd::Stop%1135093204.body preserve=yes
  //## end cGetInfoCmd::Stop%1135093204.body
}

void cGetInfoCmd::AddString (STRING_T &info, CONST_STRING_T name, CONST_STRING_T value, CONST_STRING_T delimiter)
{
  //## begin cGetInfoCmd::AddString%1135098391.body preserve=yes
   info += name;
   info += delimiter;
   info += "\"";
   info += value;
   info += "\";\n";
  //## end cGetInfoCmd::AddString%1135098391.body
}

void cGetInfoCmd::AddInteger (STRING_T &info, CONST_STRING_T name, LONG_T value, CONST_STRING_T delimiter)
{
  //## begin cGetInfoCmd::AddInteger%1135098392.body preserve=yes
   char ival[0x40] = {0};
   SafePrintf(ival, sizeof(ival), "%d", value);
   info += name;
   info += delimiter;
   info += ival;
   info += ";\n";
  //## end cGetInfoCmd::AddInteger%1135098392.body
}

void cGetInfoCmd::AddActiveJobs (cEM63Interface *itf, STRING_T &info, CONST_STRING_T delimiter)
{
  //## begin cGetInfoCmd::AddActiveJobs%1135162374.body preserve=yes
   info += "ActiveJobs";
   info += delimiter;
   JOB_LIST_T job_list;
   itf->Jobs(job_list);
   JOB_LIST_T::const_iterator i = job_list.cbegin();
   while (i != job_list.cend()) {
      cEM63Job * job = (*i);
      if (job->IsActive()) {
         info += "\n";
         info += "\t";
         info += "\"";
         info += job->get_JobName().c_str();
         info += "\"\n";
         info += "\t";
         info += "\"";
         info += job->RequestFile().c_str();
         info += "\"\n";
         info += "\t";
         info += "\"";
         info += job->ResponseFile().c_str();
         info += "\"";
      }
      i++;
   }
   info += ";\n";
  //## end cGetInfoCmd::AddActiveJobs%1135162374.body
}

void cGetInfoCmd::AddActiveReports (cEM63Interface *itf, STRING_T &info, CONST_STRING_T delimiter)
{
  //## begin cGetInfoCmd::AddActiveReports%1135162375.body preserve=yes
   info += "ActiveReports";
   info += delimiter;
   CMD_LIST_T report_list;
   itf->Reports(report_list);
   CMD_LIST_T::const_iterator i = report_list.cbegin();
   while (i != report_list.cend()) {
      cPresentationCmd * command = (*i);
      if (command->IsReport() && command->IsActive()) {
         info += "\n";
         info += "\t";
         info += "\"";
         info += command->get_CommandName().c_str();
         info += "\"\n";
         info += "\t";
         info += "\"";
         info += command->Job()->RequestFile().c_str();
         info += "\"\n";
         info += "\t";
         info += "\"";
         info += command->OutputFile().c_str();
         info += "\"";
      }
      i++;
   }
   info += ";\n";
  //## end cGetInfoCmd::AddActiveReports%1135162375.body
}

void cGetInfoCmd::AddActiveEvents (cEM63Interface *itf, STRING_T &info, CONST_STRING_T delimiter)
{
  //## begin cGetInfoCmd::AddActiveEvents%1135162376.body preserve=yes
   info += "ActiveEvents";
   info += delimiter;
   CMD_LIST_T event_log_list;
   itf->EventLogs(event_log_list);
   CMD_LIST_T::const_iterator i = event_log_list.cbegin();
   while (i != event_log_list.cend()) {
      cPresentationCmd * command = (*i);
      if (command->IsEvent() && command->IsActive()) {
         info += "\n";
         info += "\t";
         info += "\"";
         info += command->get_CommandName().c_str();
         info += "\"\n";
         info += "\t";
         info += "\"";
         info += command->Job()->RequestFile().c_str();
         info += "\"\n";
         info += "\t";
         info += "\"";
         info += command->OutputFile().c_str();
         info += "\"";
      }
      i++;
   }
   info += ";\n";
  //## end cGetInfoCmd::AddActiveEvents%1135162376.body
}

void cGetInfoCmd::AddEventTypes (cEM63Interface *itf, STRING_T &info, CONST_STRING_T delimiter)
{
  //## begin cGetInfoCmd::AddEventTypes%1135177951.body preserve=yes
   char ival[0x40] = {0};
   info += "MaxEvents";
   info += delimiter;
   info += "\n";

   SafePrintf(ival, sizeof(ival), "%d", itf->MaxCurrentAlarms());
   info += "\t";
   info += "CURRENT_ALARMS";
   info += "\t";
   info += ival;
   info += "\n";

   SafePrintf(ival, sizeof(ival), "%d", itf->MaxAlarms());
   info += "\t";
   info += "ALARMS";
   info += "\t";
   info += ival;
   info += "\n";

   SafePrintf(ival, sizeof(ival), "%d", itf->MaxChanges());
   info += "\t";
   info += "CHANGES";
   info += "\t";
   info += ival;
   info += ";\n";
  //## end cGetInfoCmd::AddEventTypes%1135177951.body
}

void cGetInfoCmd::AddRefString (STRING_T &info, CONST_STRING_T name, CONST_STRING_T var_spec, CONST_STRING_T delimiter)
{
  //## begin cGetInfoCmd::AddRefString%1136199178.body preserve=yes
   STRING_T value;
   _Interface->GetParamValue(var_spec, value);
   AddString(info, name, value.c_str(), delimiter);
  //## end cGetInfoCmd::AddRefString%1136199178.body
}

void cGetInfoCmd::AddRefInteger (STRING_T &info, CONST_STRING_T name, CONST_STRING_T var_spec, CONST_STRING_T delimiter)
{
  //## begin cGetInfoCmd::AddRefInteger%1136199179.body preserve=yes
   STRING_T value;
   _Interface->GetParamValue(var_spec, value);
   AddInteger(info, name, atol(value.c_str()), delimiter);
  //## end cGetInfoCmd::AddRefInteger%1136199179.body
}

// Additional Declarations
  //## begin cGetInfoCmd%4380805F01D0.declarations preserve=yes
  //## end cGetInfoCmd%4380805F01D0.declarations

//## begin module%4380805F01D0.epilog preserve=yes
//## end module%4380805F01D0.epilog
