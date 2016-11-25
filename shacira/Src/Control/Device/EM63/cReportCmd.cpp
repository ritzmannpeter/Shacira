//## begin module%4380801B000C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380801B000C.cm

//## begin module%4380801B000C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380801B000C.cp

//## Module: cReportCmd%4380801B000C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cReportCmd.cpp

//## begin module%4380801B000C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4380801B000C.additionalIncludes

//## begin module%4380801B000C.includes preserve=yes

/// PR 05.11.08 - report now is processed at least one time, when no cyclic condition is specified

//## end module%4380801B000C.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cContext
#include "System/Database/cContext.h"
// cReportCmd
#include "Control/Device/EM63/cReportCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%4380801B000C.additionalDeclarations preserve=yes
//## end module%4380801B000C.additionalDeclarations


// Class cReportCmd 












cReportCmd::cReportCmd()
  //## begin cReportCmd::cReportCmd%.hasinit preserve=no
      : _PresentationType(EM63_APPEND), _StartCondition(NULL), _StopCondition(NULL), _CycleCondition(NULL), _ReportCondition(NULL), _Samples(1), _Sessions(0), _Count(0), _AbsCount(0), _FirstEntry(true)
  //## end cReportCmd::cReportCmd%.hasinit
  //## begin cReportCmd::cReportCmd%.initialization preserve=yes
  //## end cReportCmd::cReportCmd%.initialization
{
  //## begin cReportCmd::cReportCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cReportCmd::cReportCmd%.body
}

cReportCmd::cReportCmd(const cReportCmd &right)
  //## begin cReportCmd::cReportCmd%copy.hasinit preserve=no
      : _PresentationType(EM63_APPEND), _StartCondition(NULL), _StopCondition(NULL), _CycleCondition(NULL), _ReportCondition(NULL), _Samples(1), _Sessions(0), _Count(0), _AbsCount(0), _FirstEntry(true)
  //## end cReportCmd::cReportCmd%copy.hasinit
  //## begin cReportCmd::cReportCmd%copy.initialization preserve=yes
  //## end cReportCmd::cReportCmd%copy.initialization
{
  //## begin cReportCmd::cReportCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cReportCmd::cReportCmd%copy.body
}

cReportCmd::cReportCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cReportCmd::cReportCmd%1136548765.hasinit preserve=no
      : _PresentationType(EM63_APPEND), _StartCondition(NULL), _StopCondition(NULL), _CycleCondition(NULL), _ReportCondition(NULL), _Samples(1), _Sessions(0), _Count(0), _AbsCount(0), _FirstEntry(true)
  //## end cReportCmd::cReportCmd%1136548765.hasinit
  //## begin cReportCmd::cReportCmd%1136548765.initialization preserve=yes
  , cPresentationCmd(job, command_name)
  //## end cReportCmd::cReportCmd%1136548765.initialization
{
  //## begin cReportCmd::cReportCmd%1136548765.body preserve=yes
   _CommandType = EM63_REPORT_COMMAND;
   if (_Interface != NULL) {
      _Interface->AddReport(this);
   }
   INCREMENT_OBJECT_COUNT()
   //## end cReportCmd::cReportCmd%1136548765.body
}


cReportCmd::~cReportCmd()
{
  //## begin cReportCmd::~cReportCmd%.body preserve=yes
   _Interface->RemoveReport(this);
   if (_StartCondition != NULL) {
      delete _StartCondition;
   }
   if (_StopCondition != NULL) {
      delete _StopCondition;
   }
   if (_CycleCondition != NULL) {
      delete _CycleCondition;
   }
   if (_ReportCondition != NULL) {
      delete _ReportCondition;
   }
   DECREMENT_OBJECT_COUNT()
   //## end cReportCmd::~cReportCmd%.body
}



//## Other Operations (implementation)
void cReportCmd::AddParameter (CONST_STRING_T param_id)
{
  //## begin cReportCmd::AddParameter%1134980234.body preserve=yes
   int size = _Params.size();
   _Params.resize(size+1);
   _Params[size] = param_id;
  //## end cReportCmd::AddParameter%1134980234.body
}

void cReportCmd::SetStartCondition (cCondition *condition)
{
  //## begin cReportCmd::SetStartCondition%1134992979.body preserve=yes
   _StartCondition = condition;
  //## end cReportCmd::SetStartCondition%1134992979.body
}

void cReportCmd::SetStopCondition (cCondition *condition)
{
  //## begin cReportCmd::SetStopCondition%1134992980.body preserve=yes
   _StopCondition = condition;
  //## end cReportCmd::SetStopCondition%1134992980.body
}

void cReportCmd::SetCycleCondition (cCondition *condition)
{
  //## begin cReportCmd::SetCycleCondition%1134992981.body preserve=yes
   _CycleCondition = condition;
  //## end cReportCmd::SetCycleCondition%1134992981.body
}

void cReportCmd::SetReportCondition (cCondition *condition)
{
  //## begin cReportCmd::SetReportCondition%1134992986.body preserve=yes
   _ReportCondition = condition;
  //## end cReportCmd::SetReportCondition%1134992986.body
}

BOOL_T cReportCmd::Process (cContext *context)
{
  //## begin cReportCmd::Process%1135078971.body preserve=yes
   BOOL_T terminate = false;
   BOOL_T success = true;
   _Context = context;
   ULONG_T params = _Params.size();
   for (ULONG_T i=0; i<params; i++) {
      STRING_T param_id = _Params[i];
      if (_stricmp(param_id.c_str(), "TIME") == 0) {
      } else if (_stricmp(param_id.c_str(), "DATE") == 0) {
      } else if (_stricmp(param_id.c_str(), "COUNT") == 0) {
      } else {
         if (!_Interface->ParamExists(param_id.c_str())) {
            Failed(UNKNOWN_REPORT_PARAMETER, param_id.c_str());
            success = false;
         }
      }
   }
   if (_StartCondition != NULL) {
      if (!_StartCondition->Process(context)) {
         Failed(PROCESS_START_CONDITION, "processing start condition failed");
         success = false;
      }
   }
   if (_StopCondition != NULL) {
      if (!_StopCondition->Process(context)) {
         Failed(PROCESS_STOP_CONDITION, "processing stop condition failed");
         success = false;
      }
   }
   if (_CycleCondition != NULL) {
      if (!_CycleCondition->Process(context)) {
         Failed(PROCESS_CYCLE_CONDITION, "processing cycle condition failed");
         success = false;
      }
   } else {
      // process report at least one time, when no cyclic condition is specified 
      Cycle();
      terminate = true;
   }
   if (_ReportCondition != NULL) {
      if (!_ReportCondition->Process(context)) {
         Failed(PROCESS_REPORT_CONDITION, "processing report condition failed");
         success = false;
      }
   }
   if (terminate || !success) {
      Terminated();
   }
   return success;
  //## end cReportCmd::Process%1135078971.body
}

BOOL_T cReportCmd::Start ()
{
  //## begin cReportCmd::Start%1135068546.body preserve=yes
   if (HasFailed()) {
      return false;
   }
   if (!IsActive()) {
      if (_StartCondition == NULL) {
         Started();
         return true;
      } else {
         if (_StartCondition->Eval()) {
            Started();
            return true;
         } else {
            return false;
         }
      }
   } else {
      return false;
   }
  //## end cReportCmd::Start%1135068546.body
}

void cReportCmd::Control ()
{
  //## begin cReportCmd::Control%1135068547.body preserve=yes
   if (IsActive()) {
      if (_ReportCondition != NULL) {
         if (!_ReportCondition->Eval()) {
            return;
         }
      }
      if (_CycleCondition != NULL) {
         if (_CycleCondition->Eval()) {
            Cycle();
         }
      }
   }
  //## end cReportCmd::Control%1135068547.body
}

void cReportCmd::Stop ()
{
  //## begin cReportCmd::Stop%1135068548.body preserve=yes
   if (IsActive()) {
      if (_Sessions > 0 && _Count >= _Sessions) {
         Terminated();
      } else {
         if (_StopCondition != NULL) {
            if (_StopCondition->Eval()) {
               Terminated();
            }
         }
      }
   }
  //## end cReportCmd::Stop%1135068548.body
}

BOOL_T cReportCmd::IsReport ()
{
  //## begin cReportCmd::IsReport%1136286712.body preserve=yes
   return true;
  //## end cReportCmd::IsReport%1136286712.body
}

void cReportCmd::Cycle ()
{
  //## begin cReportCmd::Cycle%1135179457.body preserve=yes
   _AbsCount++;
   if ((_AbsCount % _Samples) != 0) {
      return;
   }
   _Count++;
   ULONG_T flags = 0;
   cBufferedFile file;
   if (_PresentationType == EM63_REWRITE) {
      PrintHeader(&file);
      PrintEntry(&file);
   } else {
      flags |= FS_FLAG_APPEND;
      if (_FirstEntry) {
         PrintHeader(&file);
         _FirstEntry = false;
      }
      PrintEntry(&file);
   }
#ifdef EM63_LOGGING_INTERFACE
   STRING_T text = file.Buffer();
   int rc = _Session->Interface()->Put(CAT_ASYNC, _OutputFile.c_str(), text.c_str(), flags);
   if (rc < 0) {
      Failed(CREATE_DESTINATION_FILE, _OutputFile.c_str());
   }
#else
   cAbstractFileSystem * file_system = _Session->Interface()->FileSystem();
   if (file_system != NULL) {
      STRING_T text = file.Buffer();
      if (!file_system->Put(_OutputFile.c_str(), text.c_str(), flags)) {
         // tu noch was
      }
   }
#endif
  //## end cReportCmd::Cycle%1135179457.body
}

void cReportCmd::PrintHeader (cBufferedFile *file)
{
  //## begin cReportCmd::PrintHeader%1135179458.body preserve=yes
   BOOL_T first = true;
   ULONG_T params = _Params.size();
   for (ULONG_T i=0; i<params; i++) {
      STRING_T param_id = _Params[i];
      if (first) {
         first = false;
      } else {
         file->Printf("%s", _LD.c_str());
      }
      file->Printf("%s", param_id.c_str());
   }
   file->Printf("\n");
  //## end cReportCmd::PrintHeader%1135179458.body
}

void cReportCmd::PrintEntry (cBufferedFile *file)
{
  //## begin cReportCmd::PrintEntry%1135179459.body preserve=yes
   cTimeObject t;
   ULONG_T now = t;
   BOOL_T first = true;
   ULONG_T params = _Params.size();
   for (ULONG_T i=0; i<params; i++) {
      if (first) {
         first = false;
      } else {
         file->Printf("%s", _LD.c_str());
      }
      STRING_T param_id = _Params[i];
      STRING_T value;
      if (_stricmp(param_id.c_str(), "TIME") == 0) {
         value = cEM63Interface::Time(now).c_str();
      } else if (_stricmp(param_id.c_str(), "DATE") == 0) {
         value = cEM63Interface::Date(now).c_str();
      } else if (_stricmp(param_id.c_str(), "COUNT") == 0) {
         value = cConvUtils::StringValue(_Count);
      } else {
         if (_Interface->GetParamValue(param_id.c_str(), value) != 0) {
            value = "?";
         }
      }
      if (!file->Printf("%s", value.c_str())) {
         ErrorPrintf("EUROMAP 63: insufficient buffer size to format value of variable %s\n", param_id.c_str());
         Failed(PROCESS_REPORT_BUF_TOO_SMALL, "insufficient output buffer size", param_id.c_str());
      }
   }
   file->Printf("\n");
  //## end cReportCmd::PrintEntry%1135179459.body
}

//## Get and Set Operations for Class Attributes (implementation)

int cReportCmd::get_PresentationType () const
{
  //## begin cReportCmd::get_PresentationType%43A68A4201FB.get preserve=no
  return _PresentationType;
  //## end cReportCmd::get_PresentationType%43A68A4201FB.get
}

void cReportCmd::set_PresentationType (int value)
{
  //## begin cReportCmd::set_PresentationType%43A68A4201FB.set preserve=no
  _PresentationType = value;
  //## end cReportCmd::set_PresentationType%43A68A4201FB.set
}

cCondition * cReportCmd::get_StartCondition () const
{
  //## begin cReportCmd::get_StartCondition%43A68BD6024B.get preserve=no
  return _StartCondition;
  //## end cReportCmd::get_StartCondition%43A68BD6024B.get
}

void cReportCmd::set_StartCondition (cCondition * value)
{
  //## begin cReportCmd::set_StartCondition%43A68BD6024B.set preserve=no
  _StartCondition = value;
  //## end cReportCmd::set_StartCondition%43A68BD6024B.set
}

cCondition * cReportCmd::get_StopCondition () const
{
  //## begin cReportCmd::get_StopCondition%43A6A6950006.get preserve=no
  return _StopCondition;
  //## end cReportCmd::get_StopCondition%43A6A6950006.get
}

void cReportCmd::set_StopCondition (cCondition * value)
{
  //## begin cReportCmd::set_StopCondition%43A6A6950006.set preserve=no
  _StopCondition = value;
  //## end cReportCmd::set_StopCondition%43A6A6950006.set
}

cCondition * cReportCmd::get_CycleCondition () const
{
  //## begin cReportCmd::get_CycleCondition%43A6A6A70342.get preserve=no
  return _CycleCondition;
  //## end cReportCmd::get_CycleCondition%43A6A6A70342.get
}

void cReportCmd::set_CycleCondition (cCondition * value)
{
  //## begin cReportCmd::set_CycleCondition%43A6A6A70342.set preserve=no
  _CycleCondition = value;
  //## end cReportCmd::set_CycleCondition%43A6A6A70342.set
}

cCondition * cReportCmd::get_ReportCondition () const
{
  //## begin cReportCmd::get_ReportCondition%43A7DCDF02D2.get preserve=no
  return _ReportCondition;
  //## end cReportCmd::get_ReportCondition%43A7DCDF02D2.get
}

void cReportCmd::set_ReportCondition (cCondition * value)
{
  //## begin cReportCmd::set_ReportCondition%43A7DCDF02D2.set preserve=no
  _ReportCondition = value;
  //## end cReportCmd::set_ReportCondition%43A7DCDF02D2.set
}

ULONG_T cReportCmd::get_Samples () const
{
  //## begin cReportCmd::get_Samples%43A68F6E0345.get preserve=no
  return _Samples;
  //## end cReportCmd::get_Samples%43A68F6E0345.get
}

void cReportCmd::set_Samples (ULONG_T value)
{
  //## begin cReportCmd::set_Samples%43A68F6E0345.set preserve=no
  _Samples = value;
  //## end cReportCmd::set_Samples%43A68F6E0345.set
}

ULONG_T cReportCmd::get_Sessions () const
{
  //## begin cReportCmd::get_Sessions%43A68F830345.get preserve=no
  return _Sessions;
  //## end cReportCmd::get_Sessions%43A68F830345.get
}

void cReportCmd::set_Sessions (ULONG_T value)
{
  //## begin cReportCmd::set_Sessions%43A68F830345.set preserve=no
  _Sessions = value;
  //## end cReportCmd::set_Sessions%43A68F830345.set
}

ULONG_T cReportCmd::get_Count () const
{
  //## begin cReportCmd::get_Count%43AACC0F0101.get preserve=no
  return _Count;
  //## end cReportCmd::get_Count%43AACC0F0101.get
}

// Additional Declarations
  //## begin cReportCmd%4380801B000C.declarations preserve=yes
  //## end cReportCmd%4380801B000C.declarations

//## begin module%4380801B000C.epilog preserve=yes
//## end module%4380801B000C.epilog
