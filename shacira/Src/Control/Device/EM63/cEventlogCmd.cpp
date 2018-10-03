//## begin module%438080340163.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%438080340163.cm

//## begin module%438080340163.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%438080340163.cp

//## Module: cEventlogCmd%438080340163; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cEventlogCmd.cpp

//## begin module%438080340163.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%438080340163.additionalIncludes

//## begin module%438080340163.includes preserve=yes
//## end module%438080340163.includes

// eb_sema
#include "base/eb_sema.hpp"
// cAlarm
#include "System/Objects/cAlarm.h"
// cDataChange
#include "System/Objects/cDataChange.h"
// cObjectQueue
#include "System/Objects/cObjectQueue.h"
// cEventlogCmd
#include "Control/Device/EM63/cEventlogCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
// cEM63Program
#include "Control/Cell/cEM63Program.h"
//## begin module%438080340163.additionalDeclarations preserve=yes
//## end module%438080340163.additionalDeclarations


// Class cEventlogCmd 








cEventlogCmd::cEventlogCmd()
  //## begin cEventlogCmd::cEventlogCmd%.hasinit preserve=no
      : _PresentationType(EM63_APPEND), _StartCondition(NULL), _StopCondition(NULL), _Count(0), _EventQueue(NULL)
  //## end cEventlogCmd::cEventlogCmd%.hasinit
  //## begin cEventlogCmd::cEventlogCmd%.initialization preserve=yes
  //## end cEventlogCmd::cEventlogCmd%.initialization
{
  //## begin cEventlogCmd::cEventlogCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cEventlogCmd::cEventlogCmd%.body
}

cEventlogCmd::cEventlogCmd(const cEventlogCmd &right)
  //## begin cEventlogCmd::cEventlogCmd%copy.hasinit preserve=no
      : _PresentationType(EM63_APPEND), _StartCondition(NULL), _StopCondition(NULL), _Count(0), _EventQueue(NULL)
  //## end cEventlogCmd::cEventlogCmd%copy.hasinit
  //## begin cEventlogCmd::cEventlogCmd%copy.initialization preserve=yes
  //## end cEventlogCmd::cEventlogCmd%copy.initialization
{
  //## begin cEventlogCmd::cEventlogCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEventlogCmd::cEventlogCmd%copy.body
}

cEventlogCmd::cEventlogCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cEventlogCmd::cEventlogCmd%1136548766.hasinit preserve=no
      : _PresentationType(EM63_APPEND), _StartCondition(NULL), _StopCondition(NULL), _Count(0), _EventQueue(NULL)
  //## end cEventlogCmd::cEventlogCmd%1136548766.hasinit
  //## begin cEventlogCmd::cEventlogCmd%1136548766.initialization preserve=yes
  , cPresentationCmd(job, command_name)
  //## end cEventlogCmd::cEventlogCmd%1136548766.initialization
{
  //## begin cEventlogCmd::cEventlogCmd%1136548766.body preserve=yes
   _CommandType = EM63_EVENT_COMMAND;
   if (_Interface != NULL) {
      _Interface->AddEventLog(this);
   }
   _EventQueue = new cObjectQueue(0x200, QBlock);
   INCREMENT_OBJECT_COUNT()
   //## end cEventlogCmd::cEventlogCmd%1136548766.body
}


cEventlogCmd::~cEventlogCmd()
{
  //## begin cEventlogCmd::~cEventlogCmd%.body preserve=yes
   _Interface->RemoveEventLog(this);
   delete _EventQueue;
   if (_StartCondition != NULL) {
      delete _StartCondition;
   }
   if (_StopCondition != NULL) {
      delete _StopCondition;
   }
   DECREMENT_OBJECT_COUNT()
   //## end cEventlogCmd::~cEventlogCmd%.body
}



//## Other Operations (implementation)
void cEventlogCmd::SetEvent (cTransientObject *object)
{
  //## begin cEventlogCmd::SetEvent%1136559696.body preserve=yes
   if (IsActive()) {
      ULONG_T object_type = object->get_Type();
      if (object_type == OT_ALARM) {
         if (_stricmp(_EventType.c_str(), "ALARMS") != 0) {
            return;
         }
      } else if (object_type == OT_DATA_CHANGE) {
         if (_stricmp(_EventType.c_str(), "CHANGES") != 0) {
            return;
         }
      }
      cObjectLock __lock__(&_QueueMutex);
      _EventQueue->Add(object);
   }
  //## end cEventlogCmd::SetEvent%1136559696.body
}

void cEventlogCmd::HandleEvents (BOOL_T clear)
{
  //## begin cEventlogCmd::HandleEvents%1136559697.body preserve=yes
   cObjectLock __lock__(&_QueueMutex);
   try {
      cTransientObject * object = _EventQueue->GetNext();
      while (object != NULL) {
         if (!clear) {
            ULONG_T object_type = object->get_Type();
            if (object_type == OT_ALARM) {
               HandleAlarm((cAlarm*)object);
            } else if (object_type == OT_DATA_CHANGE) {
               HandleChange((cDataChange*)object);
            }
         }
         object->Release();
         object = _EventQueue->GetNext();
      }
   } catch(cError & e) {
      ErrorPrintf("%s in cEventlogCmd::HandleEvents\n", e.ErrMsg().c_str());
   } catch (...) {
      ErrorPrintf("unhandled exception in cEventlogCmd::HandleEvents\n");
   }
  //## end cEventlogCmd::HandleEvents%1136559697.body
}

void cEventlogCmd::SetStartCondition (cCondition *condition)
{
  //## begin cEventlogCmd::SetStartCondition%1136281475.body preserve=yes
   _StartCondition = condition;
  //## end cEventlogCmd::SetStartCondition%1136281475.body
}

void cEventlogCmd::SetStopCondition (cCondition *condition)
{
  //## begin cEventlogCmd::SetStopCondition%1136281476.body preserve=yes
   _StopCondition = condition;
  //## end cEventlogCmd::SetStopCondition%1136281476.body
}

BOOL_T cEventlogCmd::Process (cContext *context)
{
  //## begin cEventlogCmd::Process%1136457194.body preserve=yes
   BOOL_T success = true;
   _Context = context;
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
   if (_stricmp(_EventType.c_str(), "ALARMS") == 0) {
   } else if (_stricmp(_EventType.c_str(), "CURRENT_ALARMS") == 0) {
   } else if (_stricmp(_EventType.c_str(), "CHANGES") == 0) {
   } else {
      Failed(UNKNOWN_EVENT_TOKEN, "invalid event type");
      success = false;
   }
   if (!success) {
      Terminated();
   }
   return success;
  //## end cEventlogCmd::Process%1136457194.body
}

BOOL_T cEventlogCmd::Start ()
{
  //## begin cEventlogCmd::Start%1136457195.body preserve=yes
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
  //## end cEventlogCmd::Start%1136457195.body
}

void cEventlogCmd::Control ()
{
  //## begin cEventlogCmd::Control%1136457196.body preserve=yes
   if (IsActive()) {
      if (_stricmp(_EventType.c_str(), "CURRENT_ALARMS") == 0) {
         PrintCurrentAlarms();
      } else {
         HandleEvents(false);
      }
   } else {
      HandleEvents(true);
   }
  //## end cEventlogCmd::Control%1136457196.body
}

void cEventlogCmd::Stop ()
{
  //## begin cEventlogCmd::Stop%1136457197.body preserve=yes
   if (IsActive()) {
      if (_StopCondition != NULL) {
         if (_StopCondition->Eval()) {
            Terminated();
         }
      }
   }
  //## end cEventlogCmd::Stop%1136457197.body
}

BOOL_T cEventlogCmd::IsEvent ()
{
  //## begin cEventlogCmd::IsEvent%1136286715.body preserve=yes
   return true;
  //## end cEventlogCmd::IsEvent%1136286715.body
}

void cEventlogCmd::PrintCurrentAlarms ()
{
  //## begin cEventlogCmd::PrintCurrentAlarms%1136567370.body preserve=yes
   cBufferedFile file;
   ALARM_MAP_T alarms;
   _Context->Alarms(0, alarms);
   ALARM_MAP_T::const_iterator i = alarms.cbegin();
   while (i != alarms.cend()) {
      cAlarm * alarm = (*i).second;
      PrintAlarm(&file, alarm, false);
      i++;
   }
#ifdef EM63_LOGGING_INTERFACE
   STRING_T text = file.Buffer();
   int rc = _Session->Interface()->Put(CAT_ASYNC, _OutputFile.c_str(), text.c_str(), 0);
   if (rc < 0) {
      Failed(CREATE_DESTINATION_FILE, _OutputFile.c_str());
   }
#else
   cAbstractFileSystem * file_system = _Session->Interface()->FileSystem();
   if (file_system != NULL) {
      STRING_T text = file.Buffer();
      if (!file_system->Put(_OutputFile.c_str(), text.c_str(), 0)) {
         // tu noch was
      }
   }
#endif
   Terminated();
  //## end cEventlogCmd::PrintCurrentAlarms%1136567370.body
}

void cEventlogCmd::HandleAlarm (cAlarm *alarm)
{
  //## begin cEventlogCmd::HandleAlarm%1136559699.body preserve=yes
   _Count++;
   cBufferedFile file;
   PrintAlarm(&file, alarm);
#ifdef EM63_LOGGING_INTERFACE
   ULONG_T flags = 0;
   if (_PresentationType != EM63_REWRITE) {
      flags |= FS_FLAG_APPEND;
   }
   STRING_T text = file.Buffer();
   int rc = _Session->Interface()->Put(CAT_ASYNC, _OutputFile.c_str(), text.c_str(), flags);
   if (rc < 0) {
      Failed(CREATE_DESTINATION_FILE, _OutputFile.c_str());
   }
#else
   cAbstractFileSystem * file_system = _Session->Interface()->FileSystem();
   if (file_system != NULL) {
      ULONG_T flags = 0;
      if (_PresentationType != EM63_REWRITE) {
         flags |= FS_FLAG_APPEND;
      }
      STRING_T text = file.Buffer();
      if (!file_system->Put(_OutputFile.c_str(), text.c_str(), flags)) {
         // tu noch was
      }
   }
#endif
  //## end cEventlogCmd::HandleAlarm%1136559699.body
}

void cEventlogCmd::HandleChange (cDataChange *change)
{
  //## begin cEventlogCmd::HandleChange%1136559698.body preserve=yes
   // filters for specific variables
   if (!(_Interface->Options() & EM63_OPT_LOG_FILE_CHANGES)) {
      if (change->get_ChangeFlags() & CH_FLAG_FILE_INPUT) {
         // change originated in file input
         return;
      }
   }
   if (!(_Interface->Options() & EM63_OPT_LOG_UNKNOWN)) {
      cVariable * variable = _Context->Variable(change->get_VarName().c_str());
      if (variable == NULL) {
         // this variable is unknown
         return;
      } else {
         ULONG_T system_flags = variable->_VarDef->_SystemFlags;
         if ((system_flags & HOST_READ) ||
             (system_flags & HOST_WRITE)) {
         } else {
            // no host variable
            return;
         }
      }
   }
   _Count++;
   cBufferedFile file;
   PrintChange(&file, change);
#ifdef EM63_LOGGING_INTERFACE
   ULONG_T flags = 0;
   if (_PresentationType != EM63_REWRITE) {
      flags |= FS_FLAG_APPEND;
   }
   STRING_T text = file.Buffer();
   int rc = _Session->Interface()->Put(CAT_ASYNC, _OutputFile.c_str(), text.c_str(), flags);
   if (rc < 0) {
      Failed(CREATE_DESTINATION_FILE, _OutputFile.c_str());
   }
#else
   cAbstractFileSystem * file_system = _Session->Interface()->FileSystem();
   if (file_system != NULL) {
      ULONG_T flags = 0;
      if (_PresentationType != EM63_REWRITE) {
         flags |= FS_FLAG_APPEND;
      }
      STRING_T text = file.Buffer();
      if (!file_system->Put(_OutputFile.c_str(), text.c_str(), flags)) {
         // tu noch was
      }
   }
#endif
  //## end cEventlogCmd::HandleChange%1136559698.body
}

void cEventlogCmd::PrintAlarm (cBufferedFile *file, cAlarm *alarm, BOOL_T print_state)
{
  //## begin cEventlogCmd::PrintAlarm%1136567368.body preserve=yes
   STRING_T value;
   cTimeObject t;
   ULONG_T now = t;
   file->Printf("%d", _Count);
   file->Printf("%s", _LD.c_str());
   value = cEM63Interface::Date(now).c_str();
   file->Printf("%s", value.c_str());
   file->Printf("%s", _LD.c_str());
   value = cEM63Interface::Time(now).c_str();
   file->Printf("%s", value.c_str());
   file->Printf("%s", _LD.c_str());
   file->Printf("%d", _Interface->ShotCounterValue());
   file->Printf("%s", _LD.c_str());
   if (print_state) {
      file->Printf("%d", alarm->get_State() ? 1 : 0);
      file->Printf("%s", _LD.c_str());
   }

   ULONG_T custom_id = strtoul(_Interface->GetCustomAlarmId(alarm).c_str(), NULL, 0);
   file->Printf("%08.08d", custom_id);
   file->Printf("%s", _LD.c_str());
   file->Printf("\"%s\"", _Interface->GetAlarmText(alarm).c_str()); // HA060206
   file->Printf("\n");
  //## end cEventlogCmd::PrintAlarm%1136567368.body
}

void cEventlogCmd::PrintChange (cBufferedFile *file, cDataChange *change)
{
  //## begin cEventlogCmd::PrintChange%1136567369.body preserve=yes
   STRING_T value;
   cTimeObject t;
   ULONG_T now = t;
   file->Printf("%d", _Count);
   file->Printf("%s", _LD.c_str());
   value = cEM63Interface::Date(now).c_str();
   file->Printf("%s", value.c_str());
   file->Printf("%s", _LD.c_str());
   value = cEM63Interface::Time(now).c_str();
   file->Printf("%s", value.c_str());
   file->Printf("%s", _LD.c_str());
   file->Printf("%d", _Interface->ShotCounterValue());
   file->Printf("%s", _LD.c_str());
   STRING_T param_id = _Session->Interface()->ParamId(change->get_VarName().c_str(),
                                                      change->get_Index1(),
                                                      change->get_Index2(),
                                                      change->get_Index3(),
                                                      change->get_Index4());
//   file->Printf("%s", change->get_VarName().c_str());
   file->Printf("%s", param_id.c_str());
   file->Printf("%s", _LD.c_str());
   file->Printf("%s", change->get_OldValue().c_str());
   file->Printf("%s", _LD.c_str());
   file->Printf("%s", change->get_Value().c_str());
   file->Printf("%s", _LD.c_str());
   file->Printf("%s", change->get_UserName().c_str());
   file->Printf("%s", _LD.c_str());
   file->Printf("%s", "50");
   file->Printf("%s", _LD.c_str());
   file->Printf("%s", "\"\""); // reason HA09022006
   file->Printf("\n");
  //## end cEventlogCmd::PrintChange%1136567369.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cEventlogCmd::get_EventType () const
{
  //## begin cEventlogCmd::get_EventType%43BA4D80027E.get preserve=no
  return _EventType;
  //## end cEventlogCmd::get_EventType%43BA4D80027E.get
}

void cEventlogCmd::set_EventType (STRING_T value)
{
  //## begin cEventlogCmd::set_EventType%43BA4D80027E.set preserve=no
  _EventType = value;
  //## end cEventlogCmd::set_EventType%43BA4D80027E.set
}

int cEventlogCmd::get_PresentationType () const
{
  //## begin cEventlogCmd::get_PresentationType%43BA4C7B02DF.get preserve=no
  return _PresentationType;
  //## end cEventlogCmd::get_PresentationType%43BA4C7B02DF.get
}

void cEventlogCmd::set_PresentationType (int value)
{
  //## begin cEventlogCmd::set_PresentationType%43BA4C7B02DF.set preserve=no
  _PresentationType = value;
  //## end cEventlogCmd::set_PresentationType%43BA4C7B02DF.set
}

cCondition * cEventlogCmd::get_StartCondition () const
{
  //## begin cEventlogCmd::get_StartCondition%43BA4C7B02EF.get preserve=no
  return _StartCondition;
  //## end cEventlogCmd::get_StartCondition%43BA4C7B02EF.get
}

void cEventlogCmd::set_StartCondition (cCondition * value)
{
  //## begin cEventlogCmd::set_StartCondition%43BA4C7B02EF.set preserve=no
  _StartCondition = value;
  //## end cEventlogCmd::set_StartCondition%43BA4C7B02EF.set
}

cCondition * cEventlogCmd::get_StopCondition () const
{
  //## begin cEventlogCmd::get_StopCondition%43BA4C7B02FE.get preserve=no
  return _StopCondition;
  //## end cEventlogCmd::get_StopCondition%43BA4C7B02FE.get
}

void cEventlogCmd::set_StopCondition (cCondition * value)
{
  //## begin cEventlogCmd::set_StopCondition%43BA4C7B02FE.set preserve=no
  _StopCondition = value;
  //## end cEventlogCmd::set_StopCondition%43BA4C7B02FE.set
}

ULONG_T cEventlogCmd::get_Count () const
{
  //## begin cEventlogCmd::get_Count%43BEA53102D5.get preserve=no
  return _Count;
  //## end cEventlogCmd::get_Count%43BEA53102D5.get
}

// Additional Declarations
  //## begin cEventlogCmd%438080340163.declarations preserve=yes
  //## end cEventlogCmd%438080340163.declarations

//## begin module%438080340163.epilog preserve=yes
//## end module%438080340163.epilog
