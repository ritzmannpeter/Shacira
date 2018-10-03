//## begin module%43A2BA9F0287.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43A2BA9F0287.cm

//## begin module%43A2BA9F0287.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43A2BA9F0287.cp

//## Module: cEM63Interface%43A2BA9F0287; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cEM63Interface.cpp

//## begin module%43A2BA9F0287.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43A2BA9F0287.additionalIncludes

//## begin module%43A2BA9F0287.includes preserve=yes

#include "Control/Device/EM63/cEM63LogInfo.h"

//## end module%43A2BA9F0287.includes

// cTimeObject
#include "System/cTimeObject.h"
// cStringUtils
#include "System/cStringUtils.h"
// cTransientObject
#include "System/Objects/cTransientObject.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cContext
#include "System/Database/cContext.h"
// cInterfaceFilter
#include "System/Database/cInterfaceFilter.h"
// cEM63Program
#include "Control/Cell/cEM63Program.h"
// cEventlogCmd
#include "Control/Device/EM63/cEventlogCmd.h"
// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
//## begin module%43A2BA9F0287.additionalDeclarations preserve=yes

static const EM63_ERR_DESCRIPTION_T _EM63SessionErrorTable[] =
{
   {0, "no error"},
   {1, "No response from network station"},
   {2, "Invalid syntax in session request command: #1"},
   {3, "Unable to create/open JOB response file #1"},
   {4, "Interface was started"},
   {5, "Interface is busy"},
   {6, "Machine is offline"},
   {7, "Invalid syntax in job command: #1"},
   // vendor specific session layer error codes 10000 - 99999999
   {CREATE_SESSION_RESPONSE_FILE, "Unable to create/open SESSION response file #1"},
   {OPEN_JOB_REQUEST_FILE, "Unable to open JOB request file #1"},
   {SESSION_NUMBER_TO_LARGE, "Session number #1 to large #1 , max = #2"},
   {JOB_WITH_THE_SAME_NAME, "JOB with the same name running (#1)"},
   {99999999, "last error"}
};
#define SESSION_ERROR_DESCRIPTIONS (sizeof(_EM63SessionErrorTable)/sizeof(EM63_ERR_DESCRIPTION_T))

static const EM63_ERR_DESCRIPTION_T _EM63PresentationErrorTable[] =
{
   {0, "no error"},
   {1, "reserved"},
   {2, "reserved"},
   {3, "too many active jobs"},
   {4, "unable to create/open destination file #1"},
   {5, "invalid REPORT command syntax"},
   {6, "unknown REPORT parameter #1"},
   {7, "too many active reports"},
   {8, "invalid EVENT command syntax"},
   {9, "too many active EVENTS"},
   {10, "unknown EVENT token #1"},
   {11, "invalid ABORT command syntax"},
   {12, "invalid UPLOAD command syntax"},
   {13, "unable to create/open UPLOAD destination directory file #1"},
   {14, "invalid DOWNLOAD command syntax"},
   {15, "unable to open DOWNLOAD source file #1"},
   {16, "DOWNLOAD operation denied"},
   {17, "invalid GETINFO command syntax"},
   {18, "invalid GETID command syntax"},
   {19, "invalid SET command syntax"},
   {20, "SET operation of parameter #1 denied"},
   {21, "SET value for #1 out of range"},
   {22, "unknown SET parameter #1"},
   {23, "unsupported command #1"},
   {24, "invalid START parameter syntax"},
   {25, "invalid STOP parameter syntax"},
   {26, "application parameter or constant too long"},
   {27, "invalid numeric format"},
   {28, "invalid comparison format"},
   {29, "invalid time format"},
   {30, "invalid date format"},
   {31, "end of command expected"},
   {32, "unknown error: #1"},
   {33, "REPORT with the same name and type already running"},
   {34, "EVENT with the same name and type already running"},
   {35, "DOWNLOAD is already running"},
   {36, "the specified command to abort is not active"},
   {36, "error during command processing"},
   /// vendor specific presentation layer error codes 10000 - 99999999
   {UPLOAD_DENIED, "UPLOAD operation denied"},
   {PROCESS_START_CONDITION, "processing start condition failed"},
   {PROCESS_STOP_CONDITION, "processing stop condition failed"},
   {PROCESS_CYCLE_CONDITION, "processing cyclic condition failed"},
   {PROCESS_REPORT_CONDITION, "processing report condition failed"},
   {JOB_WITH_THE_SAME_NAME, "JOB with the same name running (#1)"},
   {99999999, "last error"}
};
#define PRESENTATION_ERROR_DESCRIPTIONS (sizeof(_EM63PresentationErrorTable)/sizeof(EM63_ERR_DESCRIPTION_T))

//## end module%43A2BA9F0287.additionalDeclarations


// Class cEM63Interface 

















cEM63Interface::cEM63Interface()
  //## begin cEM63Interface::cEM63Interface%.hasinit preserve=no
      : _Verbose(false), _LogFilter(0), _Program(NULL), _Context(NULL), _FileSystem(NULL)
  //## end cEM63Interface::cEM63Interface%.hasinit
  //## begin cEM63Interface::cEM63Interface%.initialization preserve=yes
  //## end cEM63Interface::cEM63Interface%.initialization
{
  //## begin cEM63Interface::cEM63Interface%.body preserve=yes
   INCREMENT_OBJECT_COUNT()
   //## end cEM63Interface::cEM63Interface%.body
}

cEM63Interface::cEM63Interface(const cEM63Interface &right)
  //## begin cEM63Interface::cEM63Interface%copy.hasinit preserve=no
      : _Verbose(false), _LogFilter(0), _Program(NULL), _Context(NULL), _FileSystem(NULL)
  //## end cEM63Interface::cEM63Interface%copy.hasinit
  //## begin cEM63Interface::cEM63Interface%copy.initialization preserve=yes
  //## end cEM63Interface::cEM63Interface%copy.initialization
{
  //## begin cEM63Interface::cEM63Interface%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63Interface::cEM63Interface%copy.body
}

cEM63Interface::cEM63Interface (cEM63Program *program)
  //## begin cEM63Interface::cEM63Interface%1136191745.hasinit preserve=no
      : _Verbose(false), _LogFilter(0), _Program(NULL), _Context(NULL), _FileSystem(NULL)
  //## end cEM63Interface::cEM63Interface%1136191745.hasinit
  //## begin cEM63Interface::cEM63Interface%1136191745.initialization preserve=yes
  //## end cEM63Interface::cEM63Interface%1136191745.initialization
{
  //## begin cEM63Interface::cEM63Interface%1136191745.body preserve=yes
   _Program = program;
   _FileSystem = cAbstractFileSystem::Create(FS_STANDARD);
   INCREMENT_OBJECT_COUNT()
  //## end cEM63Interface::cEM63Interface%1136191745.body
}


cEM63Interface::~cEM63Interface()
{
  //## begin cEM63Interface::~cEM63Interface%.body preserve=yes
   DELETE_OBJECT(cAbstractFileSystem,_FileSystem)
   DECREMENT_OBJECT_COUNT()
  //## end cEM63Interface::~cEM63Interface%.body
}



//## Other Operations (implementation)
void cEM63Interface::SetEvent (cTransientObject *object)
{
  //## begin cEM63Interface::SetEvent%1136559695.body preserve=yes
   CMD_MAP_T::const_iterator i = _EventLogs.cbegin();
   while (i != _EventLogs.cend()) {
      cEventlogCmd * event_log = (cEventlogCmd*)(*i).second;
      if (event_log != NULL) {
         event_log->SetEvent(object);
      }
      i++;
   }
  //## end cEM63Interface::SetEvent%1136559695.body
}

void cEM63Interface::SetContext (cContext *context)
{
  //## begin cEM63Interface::SetContext%1135947275.body preserve=yes
   _Context = context;
  //## end cEM63Interface::SetContext%1135947275.body
}

ULONG_T cEM63Interface::AddSession (cEM63Session *session)
{
  //## begin cEM63Interface::AddSession%1134738525.body preserve=yes
   static int id = 0;
   ULONG_T ret_value = SESSION_CODE_NO_ERROR;

   if (session->get_SessionId() < MaxSessions()) {
      if (SessionCount() > 0) id++;
      
      //session->set_SessionId(id);
      _Sessions[id] = session;
   }
   else { // Session number to large
      ret_value = SESSION_NUMBER_TO_LARGE;
   }
   return ret_value;
  //## end cEM63Interface::AddSession%1134738525.body
}

ULONG_T cEM63Interface::SessionCount ()
{
  //## begin cEM63Interface::SessionCount%1135162870.body preserve=yes
   return _Sessions.size();
  //## end cEM63Interface::SessionCount%1135162870.body
}

void cEM63Interface::Start ()
{
  //## begin cEM63Interface::Start%1135272167.body preserve=yes
   SESSION_MAP_T::const_iterator i = _Sessions.cbegin();
   while (i != _Sessions.cend()) {
      cEM63Session * session = (*i).second;
      session->Start();
      i++;
   }
  //## end cEM63Interface::Start%1135272167.body
}

void cEM63Interface::Control ()
{
  //## begin cEM63Interface::Control%1135177952.body preserve=yes
   SESSION_MAP_T::const_iterator i = _Sessions.cbegin();
   while (i != _Sessions.cend()) {
      cEM63Session * session = (*i).second;
      if (session->IsActive()) {
         session->Control();
      }
      i++;
   }
  //## end cEM63Interface::Control%1135177952.body
}

void cEM63Interface::Stop ()
{
  //## begin cEM63Interface::Stop%1135773616.body preserve=yes
   SESSION_MAP_T::const_iterator i = _Sessions.cbegin();
   while (i != _Sessions.cend()) {
      cEM63Session * session = (*i).second;
      if (session->IsActive()) {
         session->Stop();
      }
      i++;
   }
  //## end cEM63Interface::Stop%1135773616.body
}

void cEM63Interface::CleanUp ()
{
  //## begin cEM63Interface::CleanUp%1136213365.body preserve=yes
   SESSION_LIST_T::const_iterator r = _RemovedSessions.cbegin();
   while (r != _RemovedSessions.cend()) {
      cEM63Session * session = (*r);
#ifdef EM63_LOGGING_INTERFACE
#else
      InfoPrintf("deleting session %d\n", session->get_SessionId());
#endif
      delete session;
      r++;
   }
   _RemovedSessions.clear();
   LONG_LIST_T removed_ids;
   SESSION_MAP_T::const_iterator i = _Sessions.cbegin();
   while (i != _Sessions.cend()) {
      cEM63Session * session = (*i).second;
      session->CleanUp();
      if (session->IsTerminated()) {
         LONG_T id = (*i).first;
         removed_ids.push_back(id);
         _RemovedSessions.push_back(session);
      }
      i++;
   }
   LONG_LIST_T::const_iterator j = removed_ids.cbegin();
   while (j != removed_ids.cend()) {
      LONG_T id = (*j);
      _Sessions.erase(id);
      j++;
   }
  //## end cEM63Interface::CleanUp%1136213365.body
}

void cEM63Interface::Abort (int abort_type, CONST_STRING_T name)
{
  //## begin cEM63Interface::Abort%1136213369.body preserve=yes
   SESSION_MAP_T::const_iterator i = _Sessions.cbegin();
   while (i != _Sessions.cend()) {
      cEM63Session * session = (*i).second;
      if (session->IsActive()) {
         session->Abort(abort_type, name);
      }
      i++;
   }
  //## end cEM63Interface::Abort%1136213369.body
}

STRING_T cEM63Interface::Time (ULONG_T time)
{
  //## begin cEM63Interface::Time%1135258643.body preserve=yes
   char time_string[0x100] = {0};
   cTimeObject t(time);
   SafePrintf(time_string, sizeof(time_string), "%02.2d:%02.2d:%02.2d",
           t.Get(cTimeObject::HOUR),
           t.Get(cTimeObject::MINUTE),
           t.Get(cTimeObject::SECOND));
   return time_string;
  //## end cEM63Interface::Time%1135258643.body
}

STRING_T cEM63Interface::Date (ULONG_T time)
{
  //## begin cEM63Interface::Date%1135258644.body preserve=yes
   char date_string[0x100] = {0};
   cTimeObject t(time);
   SafePrintf(date_string, sizeof(date_string), "%04.4d%02.2d%02.2d",
           t.Get(cTimeObject::YEAR),
           t.Get(cTimeObject::MONTH),
           t.Get(cTimeObject::DAY));
   return date_string;
  //## end cEM63Interface::Date%1135258644.body
}

void cEM63Interface::AddParamSpec (cVarRef *var_ref, CONST_STRING_T param_id, UCHAR_T data_type, ULONG_T length, UCHAR_T precision, UCHAR_T access_rights, CONST_STRING_T unit, CONST_STRING_T comment, CONST_STRING_T dim1_text, CONST_STRING_T dim2_text, CONST_STRING_T dim3_text, CONST_STRING_T dim4_text, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cEM63Interface::AddParamSpec%1135761104.body preserve=yes
   PARAM_SPEC_T * param = (PARAM_SPEC_T*)cSystemUtils::Alloc(sizeof(*param));
   param->var_ref = var_ref;
   strncpy(param->param_id, param_id, PARAM_ID_SIZE);
   param->data_type = data_type;
   param->length = length;
   param->precision = precision;
   param->access_rights = access_rights;
   strncpy(param->unit, unit, UNIT_SIZE);
   strncpy(param->comment, comment, DESCRIPTION_SIZE);
   strncpy(param->dim1Text, dim1_text, DIMTEXT_SIZE);
   strncpy(param->dim2Text, dim2_text, DIMTEXT_SIZE);
   strncpy(param->dim3Text, dim3_text, DIMTEXT_SIZE);
   strncpy(param->dim4Text, dim4_text, DIMTEXT_SIZE);
   param->i1 = i1;
   param->i2 = i2;
   param->i3 = i3;
   param->i4 = i4;
   _ParamSpecs[param_id] = param;
   _VarSpecs[var_ref->_Spec.c_str()] = param_id;
  //## end cEM63Interface::AddParamSpec%1135761104.body
}

void cEM63Interface::GetParamSpecs (PARAM_SPEC_MAP_T &param_specs)
{
  //## begin cEM63Interface::GetParamSpecs%1135761105.body preserve=yes
   param_specs = _ParamSpecs;
  //## end cEM63Interface::GetParamSpecs%1135761105.body
}

BOOL_T cEM63Interface::ParamExists (CONST_STRING_T param_id)
{
  //## begin cEM63Interface::ParamExists%1135773612.body preserve=yes
   PARAM_SPEC_T * param_spec = ParamSpec(param_id);
   if (param_spec == NULL) {
      return false;
   } else {
      return true;
   }
  //## end cEM63Interface::ParamExists%1135773612.body
}

BOOL_T cEM63Interface::ParamIsWriteable (CONST_STRING_T param_id)
{
  //## begin cEM63Interface::ParamIsWriteable%1135788723.body preserve=yes
   PARAM_SPEC_T * param_spec = ParamSpec(param_id);
   if (param_spec == NULL) {
      return false;
   } else {
      return (param_spec->access_rights == 1);
   }
  //## end cEM63Interface::ParamIsWriteable%1135788723.body
}

int cEM63Interface::GetParamValue (CONST_STRING_T param_id, STRING_T &value)
{
  //## begin cEM63Interface::GetParamValue%1135773613.body preserve=yes
   PARAM_SPEC_T * param_spec = ParamSpec(param_id);
   if (param_spec == NULL) {
      return E63_UNKNOWN_PARAM_ID;
   } else {
      cVarRef * var_ref = param_spec->var_ref;
      if (var_ref == NULL) {
         return E63_UNKNOWN_VARREF;
      } else {
         STRING_T var_name = var_ref->VarName();
         LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
         var_ref->GetIndices(i1, i2, i3, i4);
         cVariable * variable = _Context->Variable(var_name.c_str());
         if (variable == NULL) {
            return E63_UNKNOWN_VARIABLE;
         } else {
            ULONG_T flags = 0;
            VF_SET_IF_TYPE(flags, IF_EM63)
            try {
               variable->Get(value, i1, i2, i3, i4, flags);
               return 0;
            } catch (cError & e) {
               return E63_ACCESS_DENIED;
            } catch (...) {
               return E63_ACCESS_DENIED;
            }
         }
      }
   }
  //## end cEM63Interface::GetParamValue%1135773613.body
}

int cEM63Interface::SetParamValue (CONST_STRING_T param_id, CONST_STRING_T value)
{
  //## begin cEM63Interface::SetParamValue%1135773614.body preserve=yes
   PARAM_SPEC_T * param_spec = ParamSpec(param_id);
   if (param_spec == NULL) {
      return E63_UNKNOWN_PARAM_ID;
   } else {
      cVarRef * var_ref = param_spec->var_ref;
      if (var_ref == NULL) {
         return E63_UNKNOWN_VARREF;
      } else {
         int err = CheckRange(var_ref, value);
         if (err == 0) {
            STRING_T var_name = var_ref->VarName();
            LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
            var_ref->GetIndices(i1, i2, i3, i4);
            cVariable * variable = _Context->Variable(var_name.c_str());
            if (variable == NULL) {
               return E63_UNKNOWN_VARIABLE;
            } else {
               ULONG_T flags = 0;
               VF_SET_IF_TYPE(flags, IF_EM63)
               try {
                  variable->Set(value, i1, i2, i3, i4, flags);
                  return 0;
               } catch (cError & e) {
                  return E63_ACCESS_DENIED;
               } catch (...) {
                  return E63_ACCESS_DENIED;
               }
            }
         } else {
            return err;
         }
      }
   }
  //## end cEM63Interface::SetParamValue%1135773614.body
}

STRING_T cEM63Interface::ErrorText (UCHAR_T layer, ULONG_T code, CONST_STRING_T param1, CONST_STRING_T param2)
{
  //## begin cEM63Interface::ErrorText%1135017137.body preserve=yes
   const EM63_ERR_DESCRIPTION_T * error_description = ErrorDescription(layer, code);
   char err_text[0x500] = {0};
   if (error_description == NULL) {
      if (layer == EM63_SESSION) {
         SafePrintf(err_text, sizeof(err_text), "unknown error %d in session command (%s,%s)", code, param1, param2);
      } else if (layer == EM63_PRESENTATION) {
         SafePrintf(err_text, sizeof(err_text), "unknown error %d in presentation command (%s,%s)", code, param1, param2);
      } else {
         SafePrintf(err_text, sizeof(err_text), "unknown error %d (%s,%s)", code, param1, param2);
      }
      return err_text;
   } else {
      STRING_T rep_text = error_description->description;
      if (param1 != NULL) {
         rep_text = cStringUtils::Replace(rep_text, "#1", param1);
      }
      if (param2 != NULL) {
         rep_text = cStringUtils::Replace(rep_text, "#2", param2);
      }
      SafePrintf(err_text, sizeof(err_text), "%s", rep_text.c_str());
      int i = 0, len = strlen(err_text);
      for (i=0; i<len; i++) {
         if (err_text[i] == '\n') {
            err_text[i] = ' ';
         }
      }
      return err_text;
   }
  //## end cEM63Interface::ErrorText%1135017137.body
}

void cEM63Interface::AddJob (cEM63Job *job)
{
  //## begin cEM63Interface::AddJob%1136548759.body preserve=yes
   STRING_T job_name = job->get_JobName();

   if (Job(job_name.c_str()) == NULL) {
      _Jobs[job_name.c_str()] = job;
   }
   else { // JOB with the same name running
       job->Failed(JOB_WITH_THE_SAME_NAME, job_name.c_str());
   }
  //## end cEM63Interface::AddJob%1136548759.body
}

void cEM63Interface::RemoveJob (cEM63Job *job)
{
  //## begin cEM63Interface::RemoveJob%1136548760.body preserve=yes
   STRING_T job_name = job->get_JobName();
   cEM63Job * jobFinded = Job(job_name.c_str());

   if ((jobFinded != NULL) && job->HasFailed()) {
      if (job->get_ErrorCode() == JOB_WITH_THE_SAME_NAME) { // Don't remove job with the same name
         return;
      }
   }

   _Jobs.erase(job_name.c_str());
  //## end cEM63Interface::RemoveJob%1136548760.body
}

cEM63Job * cEM63Interface::Job (CONST_STRING_T name)
{
  //## begin cEM63Interface::Job%1136548774.body preserve=yes
   JOB_MAP_T::const_iterator i = _Jobs.find(name);
   if (i == _Jobs.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cEM63Interface::Job%1136548774.body
}

void cEM63Interface::Jobs (JOB_LIST_T &jobs)
{
  //## begin cEM63Interface::Jobs%1135162871.body preserve=yes
   JOB_MAP_T::const_iterator i = _Jobs.cbegin();
   while (i != _Jobs.cend()) {
      cEM63Job * job = (*i).second;
      jobs.push_back(job);
      i++;
   }
  //## end cEM63Interface::Jobs%1135162871.body
}

ULONG_T cEM63Interface::JobCount ()
{
  //## begin cEM63Interface::JobCount%1136548779.body preserve=yes
   return _Jobs.size();
  //## end cEM63Interface::JobCount%1136548779.body
}

void cEM63Interface::AddReport (cPresentationCmd *report)
{
  //## begin cEM63Interface::AddReport%1136548761.body preserve=yes
   STRING_T report_name = report->get_CommandName();
   _Reports[report_name.c_str()] = report;
  //## end cEM63Interface::AddReport%1136548761.body
}

void cEM63Interface::RemoveReport (cPresentationCmd *report)
{
  //## begin cEM63Interface::RemoveReport%1136548762.body preserve=yes
   STRING_T report_name = report->get_CommandName();
   _Reports.erase(report_name.c_str());
  //## end cEM63Interface::RemoveReport%1136548762.body
}

cPresentationCmd * cEM63Interface::Report (CONST_STRING_T name)
{
  //## begin cEM63Interface::Report%1136548775.body preserve=yes
   CMD_MAP_T::const_iterator i = _Reports.find(name);
   if (i == _Reports.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cEM63Interface::Report%1136548775.body
}

void cEM63Interface::Reports (CMD_LIST_T &reports)
{
  //## begin cEM63Interface::Reports%1136548776.body preserve=yes
   CMD_MAP_T::const_iterator i = _Reports.cbegin();
   while (i != _Reports.cend()) {
      cPresentationCmd * report = (*i).second;
      reports.push_back(report);
      i++;
   }
  //## end cEM63Interface::Reports%1136548776.body
}

ULONG_T cEM63Interface::ReportCount ()
{
  //## begin cEM63Interface::ReportCount%1136548780.body preserve=yes
   return _Reports.size();
  //## end cEM63Interface::ReportCount%1136548780.body
}

void cEM63Interface::AddEventLog (cPresentationCmd *event_log)
{
  //## begin cEM63Interface::AddEventLog%1136548763.body preserve=yes
   STRING_T event_log_name = event_log->get_CommandName();
   _EventLogs[event_log_name.c_str()] = event_log;
  //## end cEM63Interface::AddEventLog%1136548763.body
}

void cEM63Interface::RemoveEventLog (cPresentationCmd *event_log)
{
  //## begin cEM63Interface::RemoveEventLog%1136548764.body preserve=yes
   STRING_T event_log_name = event_log->get_CommandName();
   _EventLogs.erase(event_log_name.c_str());
  //## end cEM63Interface::RemoveEventLog%1136548764.body
}

cPresentationCmd * cEM63Interface::EventLog (CONST_STRING_T name)
{
  //## begin cEM63Interface::EventLog%1136548777.body preserve=yes
   CMD_MAP_T::const_iterator i = _EventLogs.find(name);
   if (i == _EventLogs.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cEM63Interface::EventLog%1136548777.body
}

void cEM63Interface::EventLogs (CMD_LIST_T &event_logs)
{
  //## begin cEM63Interface::EventLogs%1136548778.body preserve=yes
   CMD_MAP_T::const_iterator i = _EventLogs.cbegin();
   while (i != _EventLogs.cend()) {
      cPresentationCmd * event_log = (*i).second;
      event_logs.push_back(event_log);
      i++;
   }
  //## end cEM63Interface::EventLogs%1136548778.body
}

ULONG_T cEM63Interface::EventLogCount (CONST_STRING_T event_type)
{
  //## begin cEM63Interface::EventLogCount%1136548781.body preserve=yes
   return _EventLogs.size();
  //## end cEM63Interface::EventLogCount%1136548781.body
}

const EM63_ERR_DESCRIPTION_T * cEM63Interface::ErrorDescription (UCHAR_T layer, ULONG_T code)
{
  //## begin cEM63Interface::ErrorDescription%1135773617.body preserve=yes
   const EM63_ERR_DESCRIPTION_T * error_description = NULL;
   ULONG_T error_descriptions = 0;
   if (layer == EM63_SESSION) {
      error_descriptions = SESSION_ERROR_DESCRIPTIONS;
   } else if (layer == EM63_PRESENTATION) {
      error_descriptions = PRESENTATION_ERROR_DESCRIPTIONS;
   }
   for (ULONG_T i=0; i<error_descriptions; i++) {
      if (layer == EM63_SESSION) {
         error_description = &(_EM63SessionErrorTable[i]);
      } else if (layer == EM63_PRESENTATION) {
         error_description = &(_EM63PresentationErrorTable[i]);
      }
      if (error_description->code == code) {
         return error_description;
      }
   }
   return NULL;
  //## end cEM63Interface::ErrorDescription%1135773617.body
}

PARAM_SPEC_T * cEM63Interface::ParamSpec (CONST_STRING_T param_id)
{
  //## begin cEM63Interface::ParamSpec%1135773615.body preserve=yes
   PARAM_SPEC_MAP_T::const_iterator i = _ParamSpecs.find(param_id);
   if (i != _ParamSpecs.cend()) {
      return (*i).second;
   } else {
      return NULL;
   }
  //## end cEM63Interface::ParamSpec%1135773615.body
}

int cEM63Interface::CheckRange (cVarRef *var_ref, CONST_STRING_T value)
{
  //## begin cEM63Interface::CheckRange%1135947265.body preserve=yes
   ULONG_T system_flags = var_ref->VarDef()->_SystemFlags;
   if (!(system_flags & HOST_WRITE)) {
      return E63_ACCESS_DENIED;
   }
   UCHAR_T data_type = var_ref->DataType();
   if (data_type == SH_STRING ||
       data_type == SH_WSTRING ||
       data_type == SH_BYTE) {
      return 0;
   }
   STRING_T min_string, max_string;
   var_ref->GetMinimum(min_string);
   var_ref->GetMaximum(max_string);
   DOUBLE_T minimum = atof(min_string.c_str());
   DOUBLE_T maximum = atof(max_string.c_str());
   DOUBLE_T dval = atof(value);
   if (minimum > dval) {
      return E63_MINIMUM_ERROR;
   }
   if (maximum < dval) {
      return E63_MAXIMUM_ERROR;
   }
   return 0;
  //## end cEM63Interface::CheckRange%1135947265.body
}

STRING_T cEM63Interface::RootDirectory ()
{
  //## begin cEM63Interface::RootDirectory%1136631602.body preserve=yes
   if (_Program != NULL) {
      return _Program->RootDirectory();
   } else {
      return "";
   }
  //## end cEM63Interface::RootDirectory%1136631602.body
}

STRING_T cEM63Interface::SessionDirectory ()
{
  //## begin cEM63Interface::SessionDirectory%1136631603.body preserve=yes
   if (_Program != NULL) {
      return _Program->SessionDirectory();
   } else {
      return "";
   }
  //## end cEM63Interface::SessionDirectory%1136631603.body
}

STRING_T cEM63Interface::LD ()
{
  //## begin cEM63Interface::LD%1136631604.body preserve=yes
   if (_Program != NULL) {
      return _Program->LD();
   } else {
      return ",";
   }
  //## end cEM63Interface::LD%1136631604.body
}

STRING_T cEM63Interface::DatasetId (CONST_STRING_T keyword)
{
  //## begin cEM63Interface::DatasetId%1136191747.body preserve=yes
   if (_Program != NULL) {
      return _Program->DatasetId(keyword);
   } else {
      return "";
   }
  //## end cEM63Interface::DatasetId%1136191747.body
}

STRING_T cEM63Interface::ShotCounterId ()
{
  //## begin cEM63Interface::ShotCounterId%1136631622.body preserve=yes
   if (_Program != NULL) {
      return _Program->ShotCounterId();
   } else {
      return "unknown";
   }
  //## end cEM63Interface::ShotCounterId%1136631622.body
}

LONG_T cEM63Interface::ShotCounterValue ()
{
  //## begin cEM63Interface::ShotCounterValue%1136569865.body preserve=yes
   if (_Program != NULL) {
      return _Program->ShotCounterValue();
   } else {
      return 0;
   }
  //## end cEM63Interface::ShotCounterValue%1136569865.body
}

LONG_T cEM63Interface::InjUnitNbrValue ()
{
  //## begin cEM63Interface::InjUnitNbrValue%1136199175.body preserve=yes
   if (_Program != NULL) {
      return _Program->InjUnitNbrValue();
   } else {
      return 1;
   }
  //## end cEM63Interface::InjUnitNbrValue%1136199175.body
}

STRING_T cEM63Interface::MachNbrValue ()
{
  //## begin cEM63Interface::MachNbrValue%1136631618.body preserve=yes
   if (_Program != NULL) {
      return _Program->MachNbrValue();
   } else {
      return "";
   }
  //## end cEM63Interface::MachNbrValue%1136631618.body
}

STRING_T cEM63Interface::MaterialNbrValue ()
{
  //## begin cEM63Interface::MaterialNbrValue%1136199176.body preserve=yes
   if (_Program != NULL) {
      return _Program->MaterialNbrValue();
   } else {
      return "";
   }
  //## end cEM63Interface::MaterialNbrValue%1136199176.body
}

STRING_T cEM63Interface::MoldNbrValue ()
{
  //## begin cEM63Interface::MoldNbrValue%1136199177.body preserve=yes
   if (_Program != NULL) {
      return _Program->MoldNbrValue();
   } else {
      return "";
   }
  //## end cEM63Interface::MoldNbrValue%1136199177.body
}

STRING_T cEM63Interface::MachVendor ()
{
  //## begin cEM63Interface::MachVendor%1136631605.body preserve=yes
   if (_Program != NULL) {
      return _Program->MachVendor();
   } else {
      return "unkown";
   }
  //## end cEM63Interface::MachVendor%1136631605.body
}

STRING_T cEM63Interface::MachDesc ()
{
  //## begin cEM63Interface::MachDesc%1136631606.body preserve=yes
   if (_Program != NULL) {
      return _Program->MachDesc();
   } else {
      return "";
   }
  //## end cEM63Interface::MachDesc%1136631606.body
}

STRING_T cEM63Interface::ContrType ()
{
  //## begin cEM63Interface::ContrType%1136631607.body preserve=yes
   if (_Program != NULL) {
      return _Program->ContrType();
   } else {
      return "";
   }
  //## end cEM63Interface::ContrType%1136631607.body
}

STRING_T cEM63Interface::ContrVersion ()
{
  //## begin cEM63Interface::ContrVersion%1136631608.body preserve=yes
   if (_Program != NULL) {
      return _Program->ContrVersion();
   } else {
      return "";
   }
  //## end cEM63Interface::ContrVersion%1136631608.body
}

ULONG_T cEM63Interface::MaxJobs ()
{
  //## begin cEM63Interface::MaxJobs%1136631609.body preserve=yes
   if (_Program != NULL) {
      return _Program->MaxJobs();
   } else {
      return 5;
   }
  //## end cEM63Interface::MaxJobs%1136631609.body
}

ULONG_T cEM63Interface::MaxChanges ()
{
  //## begin cEM63Interface::MaxChanges%1136631610.body preserve=yes
   if (_Program != NULL) {
      return _Program->MaxChanges();
   } else {
      return 1;
   }
  //## end cEM63Interface::MaxChanges%1136631610.body
}

ULONG_T cEM63Interface::MaxAlarms ()
{
  //## begin cEM63Interface::MaxAlarms%1136631611.body preserve=yes
   if (_Program != NULL) {
      return _Program->MaxAlarms();
   } else {
      return 1;
   }
  //## end cEM63Interface::MaxAlarms%1136631611.body
}

ULONG_T cEM63Interface::MaxCurrentAlarms ()
{
  //## begin cEM63Interface::MaxCurrentAlarms%1136631612.body preserve=yes
   if (_Program != NULL) {
      return _Program->MaxCurrentAlarms();
   } else {
      return 1;
   }
  //## end cEM63Interface::MaxCurrentAlarms%1136631612.body
}

ULONG_T cEM63Interface::MaxReports ()
{
  //## begin cEM63Interface::MaxReports%1136631613.body preserve=yes
   if (_Program != NULL) {
      return _Program->MaxReports();
   } else {
      return 5;
   }
  //## end cEM63Interface::MaxReports%1136631613.body
}

ULONG_T cEM63Interface::MaxArchives ()
{
  //## begin cEM63Interface::MaxArchives%1136631614.body preserve=yes
   if (_Program != NULL) {
      return _Program->MaxArchives();
   } else {
      return 1;
   }
  //## end cEM63Interface::MaxArchives%1136631614.body
}

ULONG_T cEM63Interface::MaxSessions ()
{
  //## begin cEM63Interface::MaxSessions%1136631615.body preserve=yes
   if (_Program != NULL) {
      return _Program->MaxSessions();
   } else {
      return 10;
   }
  //## end cEM63Interface::MaxSessions%1136631615.body
}

STRING_T cEM63Interface::CharDef ()
{
  //## begin cEM63Interface::CharDef%1136631616.body preserve=yes
   if (_Program != NULL) {
      return _Program->CharDef();
   } else {
      return "850";
   }
  //## end cEM63Interface::CharDef%1136631616.body
}

STRING_T cEM63Interface::Version ()
{
  //## begin cEM63Interface::Version%1136631620.body preserve=yes
   if (_Program != NULL) {
      return _Program->Version();
   } else {
      return "unknown";
   }
  //## end cEM63Interface::Version%1136631620.body
}

STRING_T cEM63Interface::GetAlarmText (cAlarm *alarm)
{
  //## begin cEM63Interface::GetAlarmText%1139403382.body preserve=yes
   if (_Program != NULL) {
      return _Program->GetAlarmText(alarm);
   } else {
      return "unknown";
   }
  //## end cEM63Interface::GetAlarmText%1139403382.body
}

STRING_T cEM63Interface::GetCustomAlarmId (cAlarm *alarm)
{
   if (_Program != NULL) {
      return _Program->GetCustomAlarmId(alarm);
   } else {
      return "unknown";
   }
}

cMutexSem * cEM63Interface::SessionMutex ()
{
  //## begin cEM63Interface::SessionMutex%1140161326.body preserve=yes
   return &(_SessionMutex);
  //## end cEM63Interface::SessionMutex%1140161326.body
}

cAbstractFileSystem * cEM63Interface::FileSystem ()
{
  //## begin cEM63Interface::FileSystem%1141375556.body preserve=yes
   return _FileSystem;
  //## end cEM63Interface::FileSystem%1141375556.body
}

int cEM63Interface::ParamError (int err)
{
  //## begin cEM63Interface::ParamError%1141641104.body preserve=yes
   switch (err) {
   case E63_MINIMUM_ERROR: return SET_RANGE_ERROR;
   case E63_MAXIMUM_ERROR: return SET_RANGE_ERROR;
   case E63_UNKNOWN_PARAM_ID: return UNKNOWN_SET_PARAMETER;
   case E63_UNKNOWN_VARREF: return UNKNOWN_ERROR;
   case E63_UNKNOWN_VARIABLE: return UNKNOWN_ERROR;
   case E63_ACCESS_DENIED: return SET_DENIED;
   }
   return err;
  //## end cEM63Interface::ParamError%1141641104.body
}

STRING_T cEM63Interface::ParamId (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cEM63Interface::ParamId%1141664737.body preserve=yes
   char var_spec[0x100] = {0};
   if (i4 != -1) {
      SafePrintf(var_spec, sizeof(var_spec), "%s[%d][%d][%d][%d]", var_name, i1, i2, i3, i4);
   } else if (i3 != -1) {
      SafePrintf(var_spec, sizeof(var_spec), "%s[%d][%d][%d]", var_name, i1, i2, i3);
   } else if (i2 != -1) {
      SafePrintf(var_spec, sizeof(var_spec), "%s[%d][%d]", var_name, i1, i2);
   } else if (i1 != -1) {
      SafePrintf(var_spec, sizeof(var_spec), "%s[%d]", var_name, i1);
   } else {
      SafePrintf(var_spec, sizeof(var_spec), "%s", var_name);
   }
   VAR_SPEC_MAP_T::const_iterator i = _VarSpecs.find(var_spec);
   if (i != _VarSpecs.cend()) {
      return (*i).second;
   } else {
      if (i4 != -1) {
         SafePrintf(var_spec, sizeof(var_spec), "@%s[%d,%d,%d,%d]", var_name, i1, i2, i3, i4);
      } else if (i3 != -1) {
         SafePrintf(var_spec, sizeof(var_spec), "@%s[%d,%d,%d]", var_name, i1, i2, i3);
      } else if (i2 != -1) {
         SafePrintf(var_spec, sizeof(var_spec), "@%s[%d,%d]", var_name, i1, i2);
      } else if (i1 != -1) {
         SafePrintf(var_spec, sizeof(var_spec), "@%s[%d]", var_name, i1);
      } else {
         SafePrintf(var_spec, sizeof(var_spec), "@%s", var_name);
      }
      return var_spec;
   }
  //## end cEM63Interface::ParamId%1141664737.body
}

STRING_T cEM63Interface::GetVarCommentType ()
{
  //## begin cEM63Interface::GetVarCommentType%1151500989.body preserve=yes
   if (_Program != NULL) {
      return _Program->GetVarCommentType();
   } else {
      return "description";
   }
  //## end cEM63Interface::GetVarCommentType%1151500989.body
}

BOOL_T cEM63Interface::VariableText(STRING_T &ids_text, PARAM_SPEC_T * param_spec)
{
   if (_Program != NULL) {
      return _Program->VariableText(ids_text, param_spec);
   } else {
      return false;
   }
}

ULONG_T cEM63Interface::Scan (STRING_LIST_T &file_names, CONST_STRING_T pattern, CONST_STRING_T directory)
{
  //## begin cEM63Interface::Scan%1166083887.body preserve=yes
   if (_FileSystem != NULL) {
      if (directory != NULL) {
         _FileSystem->set_BasePath(directory);
      }
      ULONG_T rc = _FileSystem->Scan(file_names, pattern);
//      Log(CAT_FILE_SYSTEM, OP_SCAN, 0, _FileSystem->get_BasePath().c_str(), "");
      return rc;
   } else {
      return 0;
   }
  //## end cEM63Interface::Scan%1166083887.body
}

int cEM63Interface::Get (ULONG_T category, CONST_STRING_T path, STRING_T &buffer, ULONG_T flags)
{
  //## begin cEM63Interface::Get%1166083888.body preserve=yes
   if (_FileSystem != NULL) {
      STRING_T file = path;
      char message[0x200] = {0};
      int rc = _FileSystem->Get(path, buffer, flags);
      if (rc < 0) {
         SafePrintf(message, sizeof(message), "failed to get data from %s: %s",
                 file.c_str(), _FileSystem->ErrorText(rc));
      } else {
         SafePrintf(message, sizeof(message), "get %d bytes from %s", buffer.size(), file.c_str());
      }
      Log(category, OP_GET, rc, message);
      return rc;
   } else {
      return -1;
   }
  //## end cEM63Interface::Get%1166083888.body
}

int cEM63Interface::Put (ULONG_T category, CONST_STRING_T path, CONST_STRING_T text, ULONG_T flags)
{
  //## begin cEM63Interface::Put%1166083889.body preserve=yes
   if (_FileSystem != NULL) {
      STRING_T file = path;
      char message[0x200] = {0};
      int rc = _FileSystem->Put(path, text, flags);
      if (rc < 0) {
         SafePrintf(message, sizeof(message), "failed to put %d bytes into %s: %s",
                 strlen(text), file.c_str(), _FileSystem->ErrorText(rc));
      } else {
         SafePrintf(message, sizeof(message), "put %d bytes into %s", strlen(text), file.c_str());
      }
      Log(category, OP_PUT, rc, message);
      return rc;
   } else {
      return -1;
   }
  //## end cEM63Interface::Put%1166083889.body
}

int cEM63Interface::RemoveFile (ULONG_T category, CONST_STRING_T path)
{
  //## begin cEM63Interface::Put%1166083889.body preserve=yes
   if (_FileSystem != NULL) {
      STRING_T file = path;
      char message[0x200] = {0};
      int rc = _FileSystem->RemoveFile(path);
      if (rc < 0) {
         SafePrintf(message, sizeof(message), "Failed to remove file %s", file.c_str());
      } else {
         SafePrintf(message, sizeof(message), "Removed file %s", file.c_str());
      }
      Log(category, OP_PUT, rc, message);
      return rc;
   } else {
      return -1;
   }
  //## end cEM63Interface::Put%1166083889.body
}

void cEM63Interface::Log (ULONG_T category, ULONG_T operation, int error_code, CONST_STRING_T param1, CONST_STRING_T param2, CONST_STRING_T param3)
{
  //## begin cEM63Interface::Log%1166083890.body preserve=yes
   if (category & _LogFilter) {
      #define MAX_PARAM_LEN 0x1000
      if (param1 == NULL) {
         param1 = "";
      } else {
         if (strlen(param1) > MAX_PARAM_LEN) {
            param1 = "...";
         }
      }
      if (param2 == NULL) {
         param2 = "";
      } else {
         if (strlen(param2) > MAX_PARAM_LEN) {
            param2 = "...";
         }
      }
      if (param3 == NULL) {
         param3 = "";
      } else {
         if (strlen(param3) > MAX_PARAM_LEN) {
            param3 = "...";
         }
      }
      cEM63LogInfo * log_info = new cEM63LogInfo(category, operation, error_code, param1, param2, param3);
      log_info->AddRef();
      _Program->Log(log_info);
      log_info->Release();
   }
  //## end cEM63Interface::Log%1166083890.body
}

STRING_T cEM63Interface::AbsPath (CONST_STRING_T path)
{
  //## begin cEM63Interface::AbsPath%1166170819.body preserve=yes
   STRING_T abs_path;
   if (cFileSystemUtils::IsAbsolutePath(path)) {
      abs_path = path;
   } else {
      abs_path = cFileSystemUtils::AppendPath(_FileSystem->get_BasePath().c_str(), path);
   }
   return abs_path;
  //## end cEM63Interface::AbsPath%1166170819.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cEM63Interface::get_Verbose () const
{
  //## begin cEM63Interface::get_Verbose%43BF9D810132.get preserve=no
  return _Verbose;
  //## end cEM63Interface::get_Verbose%43BF9D810132.get
}

void cEM63Interface::set_Verbose (BOOL_T value)
{
  //## begin cEM63Interface::set_Verbose%43BF9D810132.set preserve=no
  _Verbose = value;
  //## end cEM63Interface::set_Verbose%43BF9D810132.set
}

ULONG_T cEM63Interface::get_LogFilter () const
{
  //## begin cEM63Interface::get_LogFilter%458106A00290.get preserve=no
  return _LogFilter;
  //## end cEM63Interface::get_LogFilter%458106A00290.get
}

void cEM63Interface::set_LogFilter (ULONG_T value)
{
  //## begin cEM63Interface::set_LogFilter%458106A00290.set preserve=no
  _LogFilter = value;
  //## end cEM63Interface::set_LogFilter%458106A00290.set
}

ULONG_T cEM63Interface::Options ()
{
   if (_Program != NULL) {
      return _Program->Options();
   } else {
      return 0;
   }
}


// Additional Declarations
  //## begin cEM63Interface%43A2BA9F0287.declarations preserve=yes
  //## end cEM63Interface%43A2BA9F0287.declarations

//## begin module%43A2BA9F0287.epilog preserve=yes

std::map<STRING_T,int> cEM63Interface::_EM63ObjectCount;

void cEM63Interface::ControlObjectCount()
{
   std::map<STRING_T,int>::const_iterator i = _EM63ObjectCount.cbegin();
   while (i != _EM63ObjectCount.cend()) {
      STRING_T n = (*i).first;
      int v = (*i).second;
      if (v > 300) {
         ErrorPrintf("suspicious count %s: %d\n", n.c_str(), v);
      }
      i++;
   }
}

void cEM63Interface::IncrementObjectCount(const STRING_T & oname)
{
   int v = 0;
   std::map<STRING_T,int>::const_iterator i = _EM63ObjectCount.find(oname);
   if (i != _EM63ObjectCount.cend()) {
      v = (*i).second;
   }
   v++;
   _EM63ObjectCount[oname] = v;
}

void cEM63Interface::DecrementObjectCount(const STRING_T & oname)
{
   int v = 0;
   std::map<STRING_T,int>::const_iterator i = _EM63ObjectCount.find(oname);
   if (i != _EM63ObjectCount.cend()) {
      v = (*i).second;
   }
   v--;
   _EM63ObjectCount[oname] = v;
}

//## end module%43A2BA9F0287.epilog
