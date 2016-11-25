//## begin module%43807F7B0079.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43807F7B0079.cm

//## begin module%43807F7B0079.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43807F7B0079.cp

//## Module: cPresentationCmd%43807F7B0079; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cPresentationCmd.cpp

//## begin module%43807F7B0079.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43807F7B0079.additionalIncludes

//## begin module%43807F7B0079.includes preserve=yes
//## end module%43807F7B0079.includes

// cContext
#include "System/Database/cContext.h"
// cEM63Session
#include "Control/Device/EM63/cEM63Session.h"
// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%43807F7B0079.additionalDeclarations preserve=yes
//## end module%43807F7B0079.additionalDeclarations


// Class cPresentationCmd 


















cPresentationCmd::cPresentationCmd()
  //## begin cPresentationCmd::cPresentationCmd%.hasinit preserve=no
      : _CommandType(EM63_UNDEFINED_COMMAND), _Terminated(false), _ErrorCode(0), _LD(","), _Failed(false), _Started(false), _Active(false), _Aborted(false), _Job(NULL), _Session(NULL), _Interface(NULL), _Context(NULL)
  //## end cPresentationCmd::cPresentationCmd%.hasinit
  //## begin cPresentationCmd::cPresentationCmd%.initialization preserve=yes
  //## end cPresentationCmd::cPresentationCmd%.initialization
{
  //## begin cPresentationCmd::cPresentationCmd%.body preserve=yes
_ASSERT_UNCOND
  //## end cPresentationCmd::cPresentationCmd%.body
}

cPresentationCmd::cPresentationCmd(const cPresentationCmd &right)
  //## begin cPresentationCmd::cPresentationCmd%copy.hasinit preserve=no
      : _CommandType(EM63_UNDEFINED_COMMAND), _Terminated(false), _ErrorCode(0), _LD(","), _Failed(false), _Started(false), _Active(false), _Aborted(false), _Job(NULL), _Session(NULL), _Interface(NULL), _Context(NULL)
  //## end cPresentationCmd::cPresentationCmd%copy.hasinit
  //## begin cPresentationCmd::cPresentationCmd%copy.initialization preserve=yes
  //## end cPresentationCmd::cPresentationCmd%copy.initialization
{
  //## begin cPresentationCmd::cPresentationCmd%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPresentationCmd::cPresentationCmd%copy.body
}

cPresentationCmd::cPresentationCmd (cEM63Job *job, CONST_STRING_T command_name)
  //## begin cPresentationCmd::cPresentationCmd%1136548767.hasinit preserve=no
      : _CommandType(EM63_UNDEFINED_COMMAND), _Terminated(false), _ErrorCode(0), _LD(","), _Failed(false), _Started(false), _Active(false), _Aborted(false), _Job(NULL), _Session(NULL), _Interface(NULL), _Context(NULL)
  //## end cPresentationCmd::cPresentationCmd%1136548767.hasinit
  //## begin cPresentationCmd::cPresentationCmd%1136548767.initialization preserve=yes
  //## end cPresentationCmd::cPresentationCmd%1136548767.initialization
{
  //## begin cPresentationCmd::cPresentationCmd%1136548767.body preserve=yes
   _Job = job;
   _CommandName = command_name;
   if (_Job != NULL) {
      _Session = _Job->Session();
      _Interface = _Session->Interface();
      _LD = _Interface->LD();
   }
   INCREMENT_OBJECT_COUNT()
   //## end cPresentationCmd::cPresentationCmd%1136548767.body
}


cPresentationCmd::~cPresentationCmd()
{
  //## begin cPresentationCmd::~cPresentationCmd%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cPresentationCmd::~cPresentationCmd%.body
}



//## Other Operations (implementation)
cEM63Job * cPresentationCmd::Job ()
{
  //## begin cPresentationCmd::Job%1134835349.body preserve=yes
   return _Job;
  //## end cPresentationCmd::Job%1134835349.body
}

BOOL_T cPresentationCmd::Process (cContext *context)
{
  //## begin cPresentationCmd::Process%1135078972.body preserve=yes
   return true;
  //## end cPresentationCmd::Process%1135078972.body
}

BOOL_T cPresentationCmd::Start ()
{
  //## begin cPresentationCmd::Start%1135068543.body preserve=yes
   return true;
  //## end cPresentationCmd::Start%1135068543.body
}

void cPresentationCmd::Control ()
{
  //## begin cPresentationCmd::Control%1135068544.body preserve=yes
  //## end cPresentationCmd::Control%1135068544.body
}

void cPresentationCmd::Stop ()
{
  //## begin cPresentationCmd::Stop%1135068545.body preserve=yes
  //## end cPresentationCmd::Stop%1135068545.body
}

void cPresentationCmd::Abort (int abort_type, CONST_STRING_T name)
{
  //## begin cPresentationCmd::Abort%1136213368.body preserve=yes
   if (IsAbortCmd()) {
      return;
   }
   if (!IsTerminated()) {
      if (abort_type == ABORT_ALL) {
         Aborted();
      } else if (abort_type == ABORT_ALL_JOBS) {
         Aborted();
      } else if (abort_type == ABORT_ALL_REPORTS) {
         if (IsReport()) {
            Aborted();
         }
      } else if (abort_type == ABORT_ALL_EVENTS) {
         if (IsEvent()) {
            Aborted();
         }
      } else if (abort_type == ABORT_JOB) {
         STRING_T job_name = _Job->get_JobName();
         if (_stricmp(job_name.c_str(), name) == 0) {
            Aborted();
         }
      } else if (abort_type == ABORT_REPORT) {
         if (IsReport()) {
            STRING_T cmd_name = _CommandName;
            if (_stricmp(cmd_name.c_str(), name) == 0) {
               Aborted();
            }
         }
      } else if (abort_type == ABORT_EVENT) {
         if (IsEvent()) {
            STRING_T cmd_name = _CommandName;
            if (_stricmp(cmd_name.c_str(), name) == 0) {
               Aborted();
            }
         }
      }
   }
  //## end cPresentationCmd::Abort%1136213368.body
}

BOOL_T cPresentationCmd::IsTerminated ()
{
  //## begin cPresentationCmd::IsTerminated%1136286711.body preserve=yes
   if (_Terminated || _Aborted) {
      return true;
   } else {
      return false;
   }
  //## end cPresentationCmd::IsTerminated%1136286711.body
}

BOOL_T cPresentationCmd::IsActive ()
{
  //## begin cPresentationCmd::IsActive%1136457201.body preserve=yes
   return _Active;
  //## end cPresentationCmd::IsActive%1136457201.body
}

BOOL_T cPresentationCmd::HasFailed ()
{
  //## begin cPresentationCmd::HasFailed%1136457202.body preserve=yes
   return _Failed;
  //## end cPresentationCmd::HasFailed%1136457202.body
}

BOOL_T cPresentationCmd::IsStarted ()
{
  //## begin cPresentationCmd::IsStarted%1136457206.body preserve=yes
   return _Started;
  //## end cPresentationCmd::IsStarted%1136457206.body
}

BOOL_T cPresentationCmd::IsReport ()
{
  //## begin cPresentationCmd::IsReport%1136286713.body preserve=yes
   return false;
  //## end cPresentationCmd::IsReport%1136286713.body
}

BOOL_T cPresentationCmd::IsEvent ()
{
  //## begin cPresentationCmd::IsEvent%1136286714.body preserve=yes
   return false;
  //## end cPresentationCmd::IsEvent%1136286714.body
}

BOOL_T cPresentationCmd::IsAbortCmd ()
{
  //## begin cPresentationCmd::IsAbortCmd%1136457212.body preserve=yes
   return false;
  //## end cPresentationCmd::IsAbortCmd%1136457212.body
}

STRING_T cPresentationCmd::Key ()
{
  //## begin cPresentationCmd::Key%1136457214.body preserve=yes
   if (_CommandName.size() > 0) {
      return _CommandName;
   } else {
      return CommandString();
   }
  //## end cPresentationCmd::Key%1136457214.body
}

STRING_T cPresentationCmd::CommandString (LONG_T command_type)
{
  //## begin cPresentationCmd::CommandString%1136541420.body preserve=yes
   if (command_type == -1)
       command_type = _CommandType;

   switch (command_type) {
   case EM63_REPORT_COMMAND: return "REPORT command";
   case EM63_GETINFO_COMMAND: return "GETINFO command";
   case EM63_EVENT_COMMAND: return "EVENT command";
   case EM63_ABORT_COMMAND: return "ABORT command";
   case EM63_UPLOAD_COMMAND: return "UPLOAD command";
   case EM63_DOWNLOAD_COMMAND: return "DOWNLOAD command";
   case EM63_SET_COMMAND: return "SET command";
   case EM63_GETID_COMMAND: return "GETID command";
   case EM63_JOB_COMMAND: return "JOB command";
   }

   return "UNKNOWN command";
  //## end cPresentationCmd::CommandString%1136541420.body
}

void cPresentationCmd::SetOutputFile (const STRING_T &file)
{
  //## begin cPresentationCmd::SetOutputFile%1166170824.body preserve=yes
   if (_Session != NULL) {
      _OutputFile = _Session->Interface()->AbsPath(file.c_str());
   }
  //## end cPresentationCmd::SetOutputFile%1166170824.body
}

STRING_T cPresentationCmd::OutputFile ()
{
  //## begin cPresentationCmd::OutputFile%1166170825.body preserve=yes
   return _OutputFile;
  //## end cPresentationCmd::OutputFile%1166170825.body
}

void cPresentationCmd::Processed ()
{
  //## begin cPresentationCmd::Processed%1136457210.body preserve=yes
#ifdef EM63_LOGGING_INTERFACE
#else
   InfoPrintf("command %s processed\n", Key().c_str());
#endif
  //## end cPresentationCmd::Processed%1136457210.body
}

void cPresentationCmd::Started ()
{
  //## begin cPresentationCmd::Started%1136457198.body preserve=yes
   _Active = true;
   _Started = true;
#ifdef EM63_LOGGING_INTERFACE
#else
   InfoPrintf("command %s started\n", Key().c_str());
#endif
  //## end cPresentationCmd::Started%1136457198.body
}

void cPresentationCmd::Terminated ()
{
  //## begin cPresentationCmd::Terminated%1136457199.body preserve=yes
   _Active = false;
   _Terminated = true;
#ifdef EM63_LOGGING_INTERFACE
   _Session->Interface()->Log(CAT_SYNC, OP_TERMINATE_CMD, 0, _Job->get_JobName().c_str(), "terminated");
#else
   InfoPrintf("command %s terminated\n", Key().c_str());
#endif
  //## end cPresentationCmd::Terminated%1136457199.body
}

void cPresentationCmd::Aborted ()
{
  //## begin cPresentationCmd::Aborted%1136457200.body preserve=yes
   _Active = false;
   _Aborted = true;
#ifdef EM63_LOGGING_INTERFACE
   _Session->Interface()->Log(CAT_SYNC, OP_ABORT_CMD, 0, _Job->get_JobName().c_str(), "aborted");
#else
   InfoPrintf("command %s aborted\n", Key().c_str());
#endif
  //## end cPresentationCmd::Aborted%1136457200.body
}

void cPresentationCmd::Failed (int err_code, CONST_STRING_T param1, CONST_STRING_T param2)
{
  //## begin cPresentationCmd::Failed%1136457203.body preserve=yes
   _Failed = true;
   _ErrorCode = err_code;
   _Param1 = param1;
   _Param2 = param2;
   _ErrorMsg = cEM63Interface::ErrorText(EM63_PRESENTATION, err_code, param1, param2);
#ifdef EM63_LOGGING_INTERFACE
   _Session->Interface()->Log(CAT_SYNC, OP_GENERAL, err_code, _ErrorMsg.c_str());
#endif
  //## end cPresentationCmd::Failed%1136457203.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cPresentationCmd::get_CommandType () const
{
  //## begin cPresentationCmd::get_CommandType%43A93F7700C4.get preserve=no
  return _CommandType;
  //## end cPresentationCmd::get_CommandType%43A93F7700C4.get
}

STRING_T cPresentationCmd::get_CommandName () const
{
  //## begin cPresentationCmd::get_CommandName%43A7CF3B0369.get preserve=no
  return _CommandName;
  //## end cPresentationCmd::get_CommandName%43A7CF3B0369.get
}

void cPresentationCmd::set_CommandName (STRING_T value)
{
  //## begin cPresentationCmd::set_CommandName%43A7CF3B0369.set preserve=no
  _CommandName = value;
  //## end cPresentationCmd::set_CommandName%43A7CF3B0369.set
}

BOOL_T cPresentationCmd::get_Terminated () const
{
  //## begin cPresentationCmd::get_Terminated%43A7CF7301E3.get preserve=no
  return _Terminated;
  //## end cPresentationCmd::get_Terminated%43A7CF7301E3.get
}

void cPresentationCmd::set_Terminated (BOOL_T value)
{
  //## begin cPresentationCmd::set_Terminated%43A7CF7301E3.set preserve=no
  _Terminated = value;
  //## end cPresentationCmd::set_Terminated%43A7CF7301E3.set
}

ULONG_T cPresentationCmd::get_ErrorCode () const
{
  //## begin cPresentationCmd::get_ErrorCode%43A8111C006E.get preserve=no
  return _ErrorCode;
  //## end cPresentationCmd::get_ErrorCode%43A8111C006E.get
}

STRING_T cPresentationCmd::get_Param1 () const
{
  //## begin cPresentationCmd::get_Param1%43A8113901B6.get preserve=no
  return _Param1;
  //## end cPresentationCmd::get_Param1%43A8113901B6.get
}

STRING_T cPresentationCmd::get_Param2 () const
{
  //## begin cPresentationCmd::get_Param2%43A811480139.get preserve=no
  return _Param2;
  //## end cPresentationCmd::get_Param2%43A811480139.get
}

STRING_T cPresentationCmd::get_ErrorMsg () const
{
  //## begin cPresentationCmd::get_ErrorMsg%43B2B076035A.get preserve=no
  return _ErrorMsg;
  //## end cPresentationCmd::get_ErrorMsg%43B2B076035A.get
}

// Additional Declarations
  //## begin cPresentationCmd%43807F7B0079.declarations preserve=yes
  //## end cPresentationCmd%43807F7B0079.declarations

//## begin module%43807F7B0079.epilog preserve=yes
//## end module%43807F7B0079.epilog
