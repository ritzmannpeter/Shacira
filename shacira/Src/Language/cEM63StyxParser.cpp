//## begin module%4380553D004C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380553D004C.cm

//## begin module%4380553D004C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380553D004C.cp

//## Module: cEM63StyxParser%4380553D004C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Language\cEM63StyxParser.cpp

//## begin module%4380553D004C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4380553D004C.additionalIncludes

//## begin module%4380553D004C.includes preserve=yes
//## end module%4380553D004C.includes

// cContext
#include "System/Database/cContext.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cEM63Session
#include "Control/Device/EM63/cEM63Session.h"
// cDownloadCmd
#include "Control/Device/EM63/cDownloadCmd.h"
// cUploadCmd
#include "Control/Device/EM63/cUploadCmd.h"
// cSetCmd
#include "Control/Device/EM63/cSetCmd.h"
// cGetInfoCmd
#include "Control/Device/EM63/cGetInfoCmd.h"
// cGetIdCmd
#include "Control/Device/EM63/cGetIdCmd.h"
// cEventlogCmd
#include "Control/Device/EM63/cEventlogCmd.h"
// cReportCmd
#include "Control/Device/EM63/cReportCmd.h"
// cAbortCmd
#include "Control/Device/EM63/cAbortCmd.h"
// cCyclicCondition
#include "Control/Device/EM63/cCyclicCondition.h"
// cInterval
#include "Control/Device/EM63/cInterval.h"
// cParamCondition
#include "Control/Device/EM63/cParamCondition.h"
// cTimeCondition
#include "Control/Device/EM63/cTimeCondition.h"
// cCondition
#include "Control/Device/EM63/cCondition.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
// cEM63Job
#include "Control/Device/EM63/cEM63Job.h"
// cEM63StyxParser
#include "Language/cEM63StyxParser.h"
// cStyxParser
#include "Language/cStyxParser.h"
//## begin module%4380553D004C.additionalDeclarations preserve=yes

extern "C" {
   extern long _ErrorRow;
   extern long _ErrorColumn;
}

static void E63Uninitialzed(const char * text)
{
}

//## end module%4380553D004C.additionalDeclarations


// Class cEM63StyxParser 






cEM63StyxParser::cEM63StyxParser()
  //## begin cEM63StyxParser::cEM63StyxParser%.hasinit preserve=no
      : _ScanTable(NULL), _ScanStream(NULL), _ParseTable(NULL), _ParseConfig(NULL), _Root(NULL)
  //## end cEM63StyxParser::cEM63StyxParser%.hasinit
  //## begin cEM63StyxParser::cEM63StyxParser%.initialization preserve=yes
  //## end cEM63StyxParser::cEM63StyxParser%.initialization
{
  //## begin cEM63StyxParser::cEM63StyxParser%.body preserve=yes
   cStyxParser::_StyxMutex.request();
   MAP_init();
   initSymbols();
   EM63_initSymbols();
  //## end cEM63StyxParser::cEM63StyxParser%.body
}

cEM63StyxParser::cEM63StyxParser(const cEM63StyxParser &right)
  //## begin cEM63StyxParser::cEM63StyxParser%copy.hasinit preserve=no
      : _ScanTable(NULL), _ScanStream(NULL), _ParseTable(NULL), _ParseConfig(NULL), _Root(NULL)
  //## end cEM63StyxParser::cEM63StyxParser%copy.hasinit
  //## begin cEM63StyxParser::cEM63StyxParser%copy.initialization preserve=yes
  //## end cEM63StyxParser::cEM63StyxParser%copy.initialization
{
  //## begin cEM63StyxParser::cEM63StyxParser%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63StyxParser::cEM63StyxParser%copy.body
}


cEM63StyxParser::~cEM63StyxParser()
{
  //## begin cEM63StyxParser::~cEM63StyxParser%.body preserve=yes
   EM63_quitSymbols();
   freeSymbols();
   MAP_quit();
   cStyxParser::_StyxMutex.release();
  //## end cEM63StyxParser::~cEM63StyxParser%.body
}



//## Other Operations (implementation)
BOOL_T cEM63StyxParser::ParseSessionRequest (cEM63Session *session, CONST_STRING_T file, CONST_STRING_T source_code)
{
  //## begin cEM63StyxParser::ParseSessionRequest%1134738526.body preserve=yes
   BOOL_T success = false;
#ifndef PARSE_FILES
   _File = file;
   _Line = -1;
   _Column = -1;
   ULONG_T errors = 0;
   InitStringParser(source_code);
   if ((errors = PT_errorCnt()) == 0) {
      try {
         success = ParseSessionRequest(session);
      } catch (cError & e) {
         ErrorPrintf("%s in %s\n", (const char *)e, file);
         return false;
      } catch (...) {
         ErrorPrintf("unhandled exception while parsing %s\n", file);
         return false;
      }
   }
   ExitParser();
   if (errors > 0) {
      _Line = _ErrorRow;
      _Column = _ErrorColumn;
      char error_msg[0x500] = {0}; // HA04052006
      SafePrintf(error_msg, sizeof(error_msg), "syntax error in %s line (%d,%d)", file, _Line, _Column);
      ErrorPrintf("%s\n", error_msg);
      _ErrorText = error_msg;
      return false;
   } else {
      if (success) {
         return true;
      } else {
         return false;
      }
   }
#else
   _File = file;
   _Line = -1;
   _Column = -1;
   ULONG_T errors = 0;
   if (cFileSystemUtils::FileExists(file)) {
      InitFileParser(file);
      if ((errors = PT_errorCnt()) == 0) {
         try {
            success = ParseSessionRequest(session);
         } catch (cError & e) {
            ErrorPrintf("%s in %s\n", (const char *)e, file);
            return false;
         } catch (...) {
            ErrorPrintf("unhandled exception while parsing %s\n", file);
            return false;
         }
      }
      ExitParser();
      if (errors > 0) {
         _Line = _ErrorRow;
         _Column = _ErrorColumn;
         char error_msg[0x500] = {0}; // HA04052006
         SafePrintf(error_msg, sizeof(error_msg), "syntax error in %s line (%d,%d)", file, _Line, _Column);
         ErrorPrintf("%s\n", error_msg);
         _ErrorText = error_msg;
         return false;
      } else {
         if (success) {
            return true;
         } else {
            return false;
         }
      }
   } else {
      ErrorPrintf("file %s not found\n", file);
      return false;
   }
#endif
  //## end cEM63StyxParser::ParseSessionRequest%1134738526.body
}

BOOL_T cEM63StyxParser::ParsePresentationRequest (cEM63Session *session, cEM63Job *job, CONST_STRING_T file, CONST_STRING_T source_code)
{
  //## begin cEM63StyxParser::ParsePresentationRequest%1134738529.body preserve=yes
   BOOL_T success = false;
#ifndef PARSE_FILES
   _File = file;
   _Line = -1;
   _Column = -1;
   ULONG_T errors = 0;
   InitStringParser(source_code);
   if ((errors = PT_errorCnt()) == 0) {
      try {
         success = ParsePresentationRequest(session, job);
      } catch (cError & e) {
         ErrorPrintf("%s in %s\n", (const char *)e, file);
         return false;
      } catch (...) {
         ErrorPrintf("unhandled exception while parsing %s\n", file);
         return false;
      }
   }
   ExitParser();
   if (errors > 0) {
      _Line = _ErrorRow;
      _Column = _ErrorColumn;
      char error_msg[0x500] = {0}; // HA04052006
      SafePrintf(error_msg, sizeof(error_msg), "syntax error in %s line (%d,%d)", file, _Line, _Column);
      ErrorPrintf("%s\n", error_msg);
      _ErrorText = error_msg;
      return false;
   } else {
      if (success) {
         return true;
      } else {
         return false;
      }
   }
#else
   _File = file;
   _Line = -1;
   _Column = -1;
   ULONG_T errors = 0;
   if (cFileSystemUtils::FileExists(file)) {
      InitFileParser(file);
      if ((errors = PT_errorCnt()) == 0) {
         try {
            success = ParsePresentationRequest(session, job);
         } catch (cError & e) {
            ErrorPrintf("%s in %s\n", (const char *)e, file);
            return false;
         } catch (...) {
            ErrorPrintf("unhandled exception while parsing %s\n", file);
            return false;
         }
      }
      ExitParser();
      if (errors > 0) {
         _Line = _ErrorRow;
         _Column = _ErrorColumn;
         char error_msg[0x500] = {0}; // HA04052006
         SafePrintf(error_msg, sizeof(error_msg), "syntax error in %s line (%d,%d)", file, _Line, _Column);
         ErrorPrintf("%s\n", error_msg);
         _ErrorText = error_msg;
         return false;
      } else {
         if (success) {
            return true;
         } else {
            return false;
         }
      }
   } else {
      ErrorPrintf("file %s not found\n", file);
      return false;
   }
#endif
  //## end cEM63StyxParser::ParsePresentationRequest%1134738529.body
}

void cEM63StyxParser::InitFileParser (CONST_STRING_T parse_file)
{
  //## begin cEM63StyxParser::InitFileParser%1133880597.body preserve=yes
   Scn_get_EM63(&_ScanTable);          // create scan table
   _ParseTable = PLR_get_EM63();       // create parse table
   _ScanStream = Stream_file(_ScanTable, "", (char *)parse_file, ""); // create scanner from string
   _ParseConfig = PT_init(_ParseTable, _ScanStream); // create parse configuration
   _Root = PT_INTERPRETE(_ParseConfig, "");     // parse from first start nonterminal
   PT_setErrorCnt(PT_synErrorCnt(_ParseConfig));
  //## end cEM63StyxParser::InitFileParser%1133880597.body
}

void cEM63StyxParser::InitStringParser (CONST_STRING_T parse_string)
{
  //## begin cEM63StyxParser::InitStringParser%1133880598.body preserve=yes
   Scn_get_EM63(&_ScanTable);          // create scan table
   _ParseTable = PLR_get_EM63();       // create parse table
   _ScanStream = Stream_string(_ScanTable, (char*)parse_string); // create scanner from string
   _ParseConfig = PT_init(_ParseTable, _ScanStream); // create parse configuration
   _Root = PT_INTERPRETE(_ParseConfig, "");     // parse from first start nonterminal
   PT_setErrorCnt(PT_synErrorCnt(_ParseConfig));
  //## end cEM63StyxParser::InitStringParser%1133880598.body
}

void cEM63StyxParser::ExitParser ()
{
  //## begin cEM63StyxParser::ExitParser%1133880600.body preserve=yes
   if (_Root != NULL ) PT_delT(_Root);    // release derivation tree
   if (_ParseConfig != NULL) PT_quit(_ParseConfig);           // release parse configuration
   if (_ScanStream != NULL) {
      Stream_close(_ScanStream);          // close scan stream
      Stream_free(_ScanStream);           // release scan stream
   }
   if (_ScanTable != NULL) Scn_free(_ScanTable);               // release scan table
   if (_ParseTable != NULL) PLR_delTab(_ParseTable);            // release parse table
  //## end cEM63StyxParser::ExitParser%1133880600.body
}

BOOL_T cEM63StyxParser::ParseSessionRequest (cEM63Session *session)
{
  //## begin cEM63StyxParser::ParseSessionRequest%1134738533.body preserve=yes
   EM63Interface start;  // start nonterminal tree node
   _ASSERT_COND(EM63_Start_Interface(_Root, &start))
   EM63SessionRequest e63_session_request;
   if (EM63Interface_sesreq(start, &e63_session_request)) {
      GLS_Lst(EM63ExecCmd) cmd_list;
      GLS_Lst(EM63ExecCmd) cmd_list_it;
      if (EM63SessionRequest_req((void**)e63_session_request, &cmd_list)) {
         GLS_FORALL(cmd_list_it, cmd_list) {
            EM63SessionCmd e63_session_cmd = GLS_FIRST(EM63SessionCmd, cmd_list_it);
            ParseSessionCmd(session, (void**)e63_session_cmd);
         }
      }
      return true;
   } else {
      ErrorPrintf("failed to parse euromap 63 session request: session id %d\n", session->get_SessionId());
      return false;
   }
  //## end cEM63StyxParser::ParseSessionRequest%1134738533.body
}

cEM63Job * cEM63StyxParser::ParseSessionCmd (cEM63Session *session, EM63SessionCmd e63_session_cmd)
{
  //## begin cEM63StyxParser::ParseSessionCmd%1134738528.body preserve=yes
   EM63FileSpec e63_file_spec;
   EM63CmdIde e63_cmd_identifier;
   if (EM63SessionCmd_con(e63_session_cmd, &e63_cmd_identifier)) {
      cEM63Job * job = new cEM63Job(session);
      STRING_T cmd_id = CommandIdentifier((void**)e63_cmd_identifier);
      job->set_CommandIdentifier(cmd_id);
      session->AddJob(job);
      return job;
   } else if (EM63SessionCmd_exe(e63_session_cmd, &e63_cmd_identifier, &e63_file_spec)) {
      STRING_T file_spec = ParseFileSpec((void**)e63_file_spec);
      cEM63Job * job = new cEM63Job(session, file_spec.c_str());
      STRING_T cmd_id = CommandIdentifier((void**)e63_cmd_identifier);
      job->set_CommandIdentifier(cmd_id);
      session->AddJob(job);
      return job;
   } else {
      return NULL;
   }
  //## end cEM63StyxParser::ParseSessionCmd%1134738528.body
}

BOOL_T cEM63StyxParser::ParsePresentationRequest (cEM63Session *session, cEM63Job *job)
{
  //## begin cEM63StyxParser::ParsePresentationRequest%1134738534.body preserve=yes
   EM63Interface start;  // start nonterminal tree node
   _ASSERT_COND(EM63_Start_Interface(_Root, &start))
   EM63PresentationRequest e63_presentation_request;
   if (EM63Interface_presreq(start, &e63_presentation_request)) {
      EM63JobSpec e63_job_spec;
      GLS_Lst(EM63PresCmd) cmd_list;
      GLS_Lst(EM63PresCmd) cmd_list_it;
      if (EM63PresentationRequest_req((void**)e63_presentation_request, &e63_job_spec, &cmd_list)) {
         GLS_Tok e63_job_name;
         EM63FileSpec e63_file_spec;
         if (EM63JobSpec_job((void**)e63_job_spec, &e63_job_name, &e63_file_spec)) {
            STRING_T job_name = StringValue((void**)e63_job_name);
            STRING_T file_spec = ParseFileSpec((void**)e63_file_spec);
            if (job != NULL) {
               job->Initialize(job_name.c_str(), file_spec.c_str());
            } else {
               E63Uninitialzed("job is null\n");
            }

            if ((job != NULL) && job->HasFailed() &&
                (job->get_ErrorCode() == JOB_WITH_THE_SAME_NAME)) {
                return false;
            }
            GLS_FORALL(cmd_list_it, cmd_list) {
               EM63PresCmd e63_pres_cmd = GLS_FIRST(EM63PresCmd, cmd_list_it);
               ParsePresCmd(job, (void**)e63_pres_cmd);
            }
         }
      }
      return true;
   } else {
      if (session != NULL) {
         ErrorPrintf("failed to parse euromap 63 presentation request: session id %d\n", session->get_SessionId());
      } else {
         E63Uninitialzed("session is null\n");
      }
      return false;
   }
  //## end cEM63StyxParser::ParsePresentationRequest%1134738534.body
}

void cEM63StyxParser::ParsePresCmd (cEM63Job *job, EM63PresCmd e63_pres_cmd)
{
  //## begin cEM63StyxParser::ParsePresCmd%1134835345.body preserve=yes
   EM63ReportSpec e63_report_spec;
   EM63EventSpec e63_event_spec;
   EM63AbortSpec e63_abort_spec;  
   EM63UploadSpec e63_upload_spec;  
   EM63DownloadSpec e63_download_spec;  
   EM63GetIdSpec e63_getid_spec;  
   EM63GetInfoSpec e63_getinfo_spec;  
   EM63SetSpec e63_set_spec;  
   if (EM63PresCmd_report((void**)e63_pres_cmd, &e63_report_spec)) {
      ParseReportSpec(job, e63_report_spec);
   } else if (EM63PresCmd_event((void**)e63_pres_cmd, &e63_event_spec)) {
      ParseEventSpec(job, e63_event_spec);
   } else if (EM63PresCmd_abort((void**)e63_pres_cmd, &e63_abort_spec)) {
      ParseAbortSpec(job, e63_abort_spec);
   } else if (EM63PresCmd_upload((void**)e63_pres_cmd, &e63_upload_spec)) {
      ParseUploadSpec(job, e63_upload_spec);
   } else if (EM63PresCmd_download((void**)e63_pres_cmd, &e63_download_spec)) {
      ParseDownloadSpec(job, e63_download_spec);
   } else if (EM63PresCmd_ids((void**)e63_pres_cmd, &e63_getid_spec)) {
      ParseGetIdSpec(job, e63_getid_spec);
   } else if (EM63PresCmd_info((void**)e63_pres_cmd, &e63_getinfo_spec)) {
      ParseGetInfoSpec(job, e63_getinfo_spec);
   } else if (EM63PresCmd_set((void**)e63_pres_cmd, &e63_set_spec)) {
      ParseSetSpec(job, e63_set_spec);
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 report command: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParsePresCmd%1134835345.body
}

void cEM63StyxParser::ParseReportSpec (cEM63Job *job, EM63ReportSpec e63_report_spec)
{
  //## begin cEM63StyxParser::ParseReportSpec%1134980219.body preserve=yes
   GLS_Tok e63_report_name;
   EM63PresSpec e63_pres_spec;
   EM63FileSpec e63_file_spec;
   EM63StartSpec e63_start_spec;
   EM63StopSpec e63_stop_spec;
   EM63ReportCondSpec e63_report_cond_spec;
   EM63CycleSpec e63_cycle_spec;
   EM63SamplesSpec e63_samples_spec;
   EM63SessionsSpec e63_sessions_spec;
   GLS_Lst(EM63Parameter) parameter_list;
   GLS_Lst(EM63Parameter) parameter_list_it;
   if (EM63ReportSpec_report((void**)e63_report_spec,
                             &e63_report_name,
                             &e63_pres_spec,
                             &e63_file_spec,
                             &e63_start_spec,
                             &e63_stop_spec,
                             &e63_report_cond_spec,
                             &e63_cycle_spec,
                             &e63_samples_spec,
                             &e63_sessions_spec,
                             &parameter_list)) {
      STRING_T report_name = StringValue((void**)e63_report_name);
      cReportCmd * report_cmd = new cReportCmd(job, report_name.c_str());
      if (job != NULL) {
         job->AddCommand(report_cmd);
      } else {
         E63Uninitialzed("job is null\n");
      }
      int presentation_type = ParsePresSpec((void**)e63_pres_spec);
      report_cmd->set_PresentationType(presentation_type);
      STRING_T file_spec = ParseFileSpec((void**)e63_file_spec);
      report_cmd->SetOutputFile(file_spec);
      cCondition * condition = ParseStartSpec((void**)e63_start_spec);
      report_cmd->SetStartCondition(condition);
      condition = ParseStopSpec((void**)e63_stop_spec);
      report_cmd->SetStopCondition(condition);
      ParseReportCondSpec(report_cmd, (void**)e63_report_cond_spec);
      ParseCycleSpec(report_cmd, (void**)e63_cycle_spec);
      int samples = ParseSamplesSpec((void**)e63_samples_spec);
      report_cmd->set_Samples(samples);
      int sessions = ParseSessionsSpec((void**)e63_sessions_spec);
      report_cmd->set_Sessions(sessions);
      GLS_FORALL(parameter_list_it, parameter_list) {
         EM63Parameter e63_parameter = GLS_FIRST(EM63Parameter, parameter_list_it);
         STRING_T parameter = ParseParameter((void**)e63_parameter);
         report_cmd->AddParameter(parameter.c_str());
      }
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 report specification: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParseReportSpec%1134980219.body
}

void cEM63StyxParser::ParseGetInfoSpec (cEM63Job *job, EM63GetInfoSpec e63_getinfo_spec)
{
  //## begin cEM63StyxParser::ParseGetInfoSpec%1135093198.body preserve=yes
   EM63FileSpec e63_file_spec;
   if (EM63GetInfoSpec_info((void**)e63_getinfo_spec,
                             &e63_file_spec)) {
      cGetInfoCmd * getinfo_cmd = new cGetInfoCmd(job);
      if (job != NULL) {
         job->AddCommand(getinfo_cmd);
      } else {
         E63Uninitialzed("job is null\n");
      }
      STRING_T file_spec = ParseFileSpec((void**)e63_file_spec);
      getinfo_cmd->SetOutputFile(file_spec);
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 info specification: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParseGetInfoSpec%1135093198.body
}

void cEM63StyxParser::ParseGetIdSpec (cEM63Job *job, EM63GetIdSpec e63_getid_spec)
{
  //## begin cEM63StyxParser::ParseGetIdSpec%1135761100.body preserve=yes
   EM63FileSpec e63_file_spec;
   if (EM63GetIdSpec_ids((void**)e63_getid_spec, &e63_file_spec)) {
      cGetIdCmd * getid_cmd = new cGetIdCmd(job);
      if (job != NULL) {
         job->AddCommand(getid_cmd);
      } else {
         E63Uninitialzed("job is null\n");
      }
      STRING_T file_spec = ParseFileSpec((void**)e63_file_spec);
      getid_cmd->SetOutputFile(file_spec);
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 id specification: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParseGetIdSpec%1135761100.body
}

void cEM63StyxParser::ParseSetSpec (cEM63Job *job, EM63SetSpec e63_set_spec)
{
  //## begin cEM63StyxParser::ParseSetSpec%1135788722.body preserve=yes
   EM63ValueSpec e63_value_spec;
   EM63ParamId e63_param_id;
   if (EM63SetSpec_set((void**)e63_set_spec, &e63_param_id, &e63_value_spec)) {
      EM63ConstantSpec e63_constant_spec;
      STRING_T param_id = ParseParamId((void**)e63_param_id);
      STRING_T value;
      if (EM63ValueSpec_value((void**)e63_value_spec, &e63_constant_spec)) {
         value = ParseConstantSpec((void**)e63_constant_spec);
      } else {
         ErrorPrintf("failed to parse euromap 63 value specification: job name %s\n", job->get_JobName().c_str());
      }
      cSetCmd * set_cmd = new cSetCmd(job);
      if (job != NULL) {
         job->AddCommand(set_cmd);
      } else {
         E63Uninitialzed("job is null\n");
      }
      set_cmd->set_ParamId(param_id);
      set_cmd->set_ParamValue(value);
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 set value specification: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParseSetSpec%1135788722.body
}

void cEM63StyxParser::ParseUploadSpec (cEM63Job *job, EM63UploadSpec e63_upload_spec)
{
  //## begin cEM63StyxParser::ParseUploadSpec%1135947266.body preserve=yes
   EM63FileSpec e63_file_spec;
   EM63SourceSpec e63_source_spec;
   EM63StartSpec e63_start_spec;
   if (EM63UploadSpec_upload((void**)e63_upload_spec, &e63_file_spec, &e63_source_spec, &e63_start_spec)) {
      cUploadCmd * upload_cmd = new cUploadCmd(job);
      if (job != NULL) {
         job->AddCommand(upload_cmd);
      } else {
         E63Uninitialzed("job is null\n");
      }
      STRING_T file_spec = ParseFileSpec((void**)e63_file_spec);
      upload_cmd->SetOutputFile(file_spec);
      EM63FileSpec e63_av_spec;
      GLS_Tok e63_keyword;
      if (EM63SourceSpec_active((void**)e63_source_spec)) {
         upload_cmd->set_ActiveSource(true);
      } else if (EM63SourceSpec_avspec((void**)e63_source_spec, &e63_av_spec)) {
         STRING_T av_spec = ParseFileSpec((void**)e63_av_spec);
         upload_cmd->set_AvSource(av_spec);
      } else if (EM63SourceSpec_keyword((void**)e63_source_spec, &e63_keyword)) {
         STRING_T keyword = StringValue((void**)e63_keyword);
         upload_cmd->set_Keyword(keyword);
      } else {
         if (job != NULL) {
            ErrorPrintf("failed to parse euromap 63 source specification: job name %s\n", job->get_JobName().c_str());
         } else {
            E63Uninitialzed("job is null\n");
         }
      }
      cCondition * condition = ParseStartSpec((void**)e63_start_spec);
      upload_cmd->SetStartCondition(condition);
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 start specification: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParseUploadSpec%1135947266.body
}

void cEM63StyxParser::ParseDownloadSpec (cEM63Job *job, EM63DownloadSpec e63_download_spec)
{
  //## begin cEM63StyxParser::ParseDownloadSpec%1135947267.body preserve=yes
   EM63FileSpec e63_file_spec;
   EM63SourceSpec e63_source_spec;
   EM63StartSpec e63_start_spec;
   if (EM63DownloadSpec_download((void**)e63_download_spec, &e63_file_spec, &e63_source_spec, &e63_start_spec)) {
      cDownloadCmd * download_cmd = new cDownloadCmd(job);
      if (job != NULL) {
         job->AddCommand(download_cmd);
      } else {
         E63Uninitialzed("job is null\n");
      }
      STRING_T file_spec = ParseFileSpec((void**)e63_file_spec);
      download_cmd->SetOutputFile(file_spec);
      EM63FileSpec e63_av_spec;
      GLS_Tok e63_keyword;
      if (EM63SourceSpec_active((void**)e63_source_spec)) {
         download_cmd->set_ActiveSource(true);
      } else if (EM63SourceSpec_avspec((void**)e63_source_spec, &e63_av_spec)) {
         STRING_T av_spec = ParseFileSpec((void**)e63_av_spec);
         download_cmd->set_AvSource(av_spec);
      } else if (EM63SourceSpec_keyword((void**)e63_source_spec, &e63_keyword)) {
         STRING_T keyword = StringValue((void**)e63_keyword);
         download_cmd->set_Keyword(keyword);
      } else {
         if (job != NULL) {
            ErrorPrintf("failed to parse euromap 63 source specification: job name %s\n", job->get_JobName().c_str());
         } else {
            E63Uninitialzed("job is null\n");
         }
      }
      cCondition * condition = ParseStartSpec((void**)e63_start_spec);
      download_cmd->SetStartCondition(condition);
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 download specification: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParseDownloadSpec%1135947267.body
}

void cEM63StyxParser::ParseEventSpec (cEM63Job *job, EM63EventSpec e63_event_spec)
{
  //## begin cEM63StyxParser::ParseEventSpec%1136281473.body preserve=yes
   GLS_Tok e63_event_name;
   GLS_Tok e63_event_type;
   EM63PresSpec e63_pres_spec;
   EM63FileSpec e63_file_spec;
   EM63StartSpec e63_start_spec;
   EM63StopSpec e63_stop_spec;
   if (EM63EventSpec_event((void**)e63_event_spec,
                           &e63_event_name,
                           &e63_event_type,
                           &e63_pres_spec,
                           &e63_file_spec,
                           &e63_start_spec,
                           &e63_stop_spec)) {
      STRING_T event_name = StringValue((void**)e63_event_name);
      cEventlogCmd * eventlog_cmd = new cEventlogCmd(job, event_name.c_str());
      if (job != NULL) {
         job->AddCommand(eventlog_cmd);
      } else {
         E63Uninitialzed("job is null\n");
      }
      STRING_T event_type = StringValue((void**)e63_event_type);
      eventlog_cmd->set_EventType(event_type);
      int presentation_type = ParsePresSpec((void**)e63_pres_spec);
      eventlog_cmd->set_PresentationType(presentation_type);
      STRING_T file_spec = ParseFileSpec((void**)e63_file_spec);
      eventlog_cmd->SetOutputFile(file_spec);
      cCondition * condition = ParseStartSpec((void**)e63_start_spec);
      eventlog_cmd->SetStartCondition(condition);
      condition = ParseStopSpec((void**)e63_stop_spec);
      eventlog_cmd->SetStopCondition(condition);
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 event specification: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParseEventSpec%1136281473.body
}

void cEM63StyxParser::ParseAbortSpec (cEM63Job *job, EM63AbortSpec e63_abort_spec)
{
  //## begin cEM63StyxParser::ParseAbortSpec%1136281474.body preserve=yes
   GLS_Tok e63_name;
   cAbortCmd * abort_cmd = new cAbortCmd(job);
   if (job != NULL) {
      job->AddCommand(abort_cmd);
   } else {
      E63Uninitialzed("job is null\n");
   }
   if (EM63AbortSpec_all((void**)e63_abort_spec)) {
      abort_cmd->set_AbortType(ABORT_ALL);
   } else if (EM63AbortSpec_alljobs((void**)e63_abort_spec)) {
      abort_cmd->set_AbortType(ABORT_ALL_JOBS);
   } else if (EM63AbortSpec_allreports((void**)e63_abort_spec)) {
      abort_cmd->set_AbortType(ABORT_ALL_REPORTS);
   } else if (EM63AbortSpec_allevents((void**)e63_abort_spec)) {
      abort_cmd->set_AbortType(ABORT_ALL_EVENTS);
   } else if (EM63AbortSpec_job((void**)e63_abort_spec,
                                &e63_name)) {
      abort_cmd->set_AbortType(ABORT_JOB);
      STRING_T name = StringValue((void**)e63_name);
      abort_cmd->set_JobName(name);
   } else if (EM63AbortSpec_report((void**)e63_abort_spec,
                                   &e63_name)) {
      abort_cmd->set_AbortType(ABORT_REPORT);
      STRING_T name = StringValue((void**)e63_name);
      abort_cmd->set_ReportName(name);
   } else if (EM63AbortSpec_event((void**)e63_abort_spec,
                                  &e63_name)) {
      abort_cmd->set_AbortType(ABORT_EVENT);
      STRING_T name = StringValue((void**)e63_name);
      abort_cmd->set_EventName(name);
   } else {
      if (job != NULL) {
         ErrorPrintf("failed to parse euromap 63 abort specification: job name %s\n", job->get_JobName().c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   }
  //## end cEM63StyxParser::ParseAbortSpec%1136281474.body
}

int cEM63StyxParser::ParsePresSpec (EM63PresSpec *e63_pres_spec)
{
  //## begin cEM63StyxParser::ParsePresSpec%1134980220.body preserve=yes
   if (EM63PresSpec_append((void**)e63_pres_spec)) {
      return EM63_APPEND;
   } else if (EM63PresSpec_rewrite((void**)e63_pres_spec)) {
      return EM63_REWRITE;
   } else {
      // default is append
      return EM63_APPEND;
   }
  //## end cEM63StyxParser::ParsePresSpec%1134980220.body
}

cCondition * cEM63StyxParser::ParseStartSpec (EM63StartSpec *e63_start_spec)
{
  //## begin cEM63StyxParser::ParseStartSpec%1134980224.body preserve=yes
   cCondition * condition = NULL;
   EM63TimeCondSpec e63_time_cond_spec;
   EM63CondSpec e63_cond_spec;
   if (EM63StartSpec_imm((void**)e63_start_spec)) {
      condition = new cTimeCondition(EM63_GT, 0);
   } else if (EM63StartSpec_timc((void**)e63_start_spec, &e63_time_cond_spec)) {
      condition = ParseTimeCondSpec((void**)e63_time_cond_spec);
   } else if (EM63StartSpec_cond((void**)e63_start_spec, &e63_cond_spec)) {
      condition = ParseCondSpec((void**)e63_cond_spec);
   } else if (EM63StartSpec_nul((void**)e63_start_spec)) {
      // empty
   } else {
      ErrorPrintf("failed to parse euromap 63 start specification\n");
   }
   return condition;
  //## end cEM63StyxParser::ParseStartSpec%1134980224.body
}

cCondition * cEM63StyxParser::ParseStopSpec (EM63StopSpec *e63_stop_spec)
{
  //## begin cEM63StyxParser::ParseStopSpec%1134980225.body preserve=yes
   cCondition * condition = NULL;
   EM63TimeCondSpec e63_time_cond_spec;
   EM63CondSpec e63_cond_spec;
   if (EM63StopSpec_never((void**)e63_stop_spec)) {
      condition = new cTimeCondition(EM63_LT, 0);
   } else if (EM63StopSpec_timc((void**)e63_stop_spec, &e63_time_cond_spec)) {
      condition = ParseTimeCondSpec((void**)e63_time_cond_spec);
   } else if (EM63StopSpec_cond((void**)e63_stop_spec, &e63_cond_spec)) {
      condition = ParseCondSpec((void**)e63_cond_spec);
   } else if (EM63StopSpec_nul((void**)e63_stop_spec)) {
      // empty
   } else {
      ErrorPrintf("failed to parse euromap 63 stop specification\n");
   }
   return condition;
  //## end cEM63StyxParser::ParseStopSpec%1134980225.body
}

void cEM63StyxParser::ParseReportCondSpec (cReportCmd *report_cmd, EM63ReportCondSpec *e63_report_cond_spec)
{
  //## begin cEM63StyxParser::ParseReportCondSpec%1134980226.body preserve=yes
   cCondition * condition = NULL;
   EM63ParamId e63_param_id;
   EM63CondSpec e63_cond_spec;
   if (EM63ReportCondSpec_cs11((void**)e63_report_cond_spec, &e63_param_id, &e63_cond_spec)) {
      condition = ParseCondSpec((void**)e63_cond_spec);
   } else if (EM63ReportCondSpec_cs12((void**)e63_report_cond_spec, &e63_param_id, &e63_cond_spec)) {
      condition = ParseCondSpec((void**)e63_cond_spec);
      condition->SetLogOp(EM63_NOT);
   } else if (EM63ReportCondSpec_cs21((void**)e63_report_cond_spec, &e63_param_id)) {
      STRING_T param_id = ParseParamId((void**)e63_param_id);
      condition = new cParamCondition(param_id.c_str(), EM63_PARAM_CHANGED);
   } else if (EM63ReportCondSpec_cs22((void**)e63_report_cond_spec, &e63_param_id)) {
      STRING_T param_id = ParseParamId((void**)e63_param_id);
      condition = new cParamCondition(param_id.c_str(), EM63_PARAM_CHANGED);
      condition->SetLogOp(EM63_NOT);
   } else if (EM63ReportCondSpec_nul((void**)e63_report_cond_spec)) {
      // empty
   } else {
      ErrorPrintf("failed to parse euromap 63 report command specification\n");
   }
   report_cmd->SetReportCondition(condition);
  //## end cEM63StyxParser::ParseReportCondSpec%1134980226.body
}

void cEM63StyxParser::ParseCycleSpec (cReportCmd *report_cmd, EM63CycleSpec *e63_cycle_spec)
{
  //## begin cEM63StyxParser::ParseCycleSpec%1134980227.body preserve=yes
   cCondition * condition = NULL;
   EM63TimeConst e63_time_const;
   EM63IntegerConst e63_integer_const;
   if (EM63CycleSpec_cyc((void**)e63_cycle_spec)) {
      if (report_cmd->Job() != NULL) {
         cEM63Interface * itf = report_cmd->Job()->Session()->Interface();
         STRING_T shot_param_id = "ActCntMachAdd";
         if (itf != NULL) {
            shot_param_id = itf->ShotCounterId();
         } else {
            E63Uninitialzed("itf is null\n");
         }
         condition = new cCyclicCondition(0, shot_param_id.c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   } else if (EM63CycleSpec_time((void**)e63_cycle_spec, &e63_time_const)) {
      ULONG_T time = ParseTimeConst((void**)e63_time_const);
      condition = new cInterval(time);
   } else if (EM63CycleSpec_shot((void**)e63_cycle_spec, &e63_integer_const)) {
      if (report_cmd->Job() != NULL) {
         cEM63Interface * itf = report_cmd->Job()->Session()->Interface();
         STRING_T shot_param_id = "ActCntMachAdd";
         if (itf != NULL) {
            shot_param_id = itf->ShotCounterId();
         } else {
            E63Uninitialzed("itf is null\n");
         }
         int shot = ParseIntegerConst((void**)e63_integer_const);
         condition = new cCyclicCondition(shot, shot_param_id.c_str());
      } else {
         E63Uninitialzed("job is null\n");
      }
   } else if (EM63CycleSpec_nul((void**)e63_cycle_spec)) {
      // empty
   } else {
      ErrorPrintf("failed to parse euromap 63 cyclic specification\n");
   }
   report_cmd->SetCycleCondition(condition);
  //## end cEM63StyxParser::ParseCycleSpec%1134980227.body
}

int cEM63StyxParser::ParseSamplesSpec (EM63SamplesSpec *e63_samples_spec)
{
  //## begin cEM63StyxParser::ParseSamplesSpec%1134980221.body preserve=yes
   EM63IntegerConst e63_integer_const;
   if (EM63SamplesSpec_num((void**)e63_samples_spec, &e63_integer_const)) {
      return ParseIntegerConst((void**)e63_integer_const);
   } else {
      // empty default is 1
      return 1;
   }
  //## end cEM63StyxParser::ParseSamplesSpec%1134980221.body
}

int cEM63StyxParser::ParseSessionsSpec (EM63SessionsSpec *e63_sessions_spec)
{
  //## begin cEM63StyxParser::ParseSessionsSpec%1134980222.body preserve=yes
   EM63IntegerConst e63_integer_const;
   if (EM63SessionsSpec_num((void**)e63_sessions_spec, &e63_integer_const)) {
      return ParseIntegerConst((void**)e63_integer_const);
   } else {
      // empty default is 0
      return 0;
   }
  //## end cEM63StyxParser::ParseSessionsSpec%1134980222.body
}

STRING_T cEM63StyxParser::ParseParameter (EM63Parameter *e63_parameter)
{
  //## begin cEM63StyxParser::ParseParameter%1134980223.body preserve=yes
   EM63ParamId e63_param_id;
   if (EM63Parameter_time((void**)e63_parameter)) {
      return "TIME";
   } else if (EM63Parameter_date((void**)e63_parameter)) {
      return "DATE";
   } else if (EM63Parameter_count((void**)e63_parameter)) {
      return "COUNT";
   } else if (EM63Parameter_param((void**)e63_parameter, &e63_param_id)) {
      return ParseParamId((void**)e63_param_id);
   } else {
      ErrorPrintf("failed to parse euromap 63 parameter specification\n");
   }
   return "";
  //## end cEM63StyxParser::ParseParameter%1134980223.body
}

STRING_T cEM63StyxParser::ParseFileSpec (EM63FileSpec *e63_file_spec)
{
  //## begin cEM63StyxParser::ParseFileSpec%1133963358.body preserve=yes
   GLS_Tok file_spec_token;
   if (EM63FileSpec_fspec((void**)e63_file_spec, &file_spec_token)) {
      STRING_T file_spec = (const char *)GLS_Tok_string(file_spec_token);
      file_spec = cStringUtils::Trim(file_spec.c_str(), '"');
      return file_spec;
   } else {
      ErrorPrintf("failed to parse euromap 63 file specification\n");
   }
   return "";
  //## end cEM63StyxParser::ParseFileSpec%1133963358.body
}

STRING_T cEM63StyxParser::ParseParamId (EM63ParamId *e63_param_id)
{
  //## begin cEM63StyxParser::ParseParamId%1134980233.body preserve=yes
   char param_id[0x200] = {0};
   STRING_T var_name;
   ULONG_T dim = 0;
   ULONG_T index[4] = {0};
   EM63VarRef e63_var_ref;
   if (EM63ParamId_parid((void**)e63_param_id, &e63_var_ref)) {
      EM63VarName e63_var_name;
      EM63IndexRef e63_index_ref;
      if (EM63VarRef_ref1((void**)e63_var_ref, &e63_var_name)) {
         GLS_Tok ide;
         if (EM63VarName_name1((void**)e63_var_name, &ide)) {
            var_name = StringValue((void**)ide);
         } else if (EM63VarName_name2((void**)e63_var_name, &ide)) {
            var_name = StringValue((void**)ide);
         }
      } else if (EM63VarRef_ref2((void**)e63_var_ref, &e63_var_name, &e63_index_ref)) {
         GLS_Tok ide;
         if (EM63VarName_name1((void**)e63_var_name, &ide)) {
            var_name = StringValue((void**)ide);
         } else if (EM63VarName_name2((void**)e63_var_name, &ide)) {
            var_name = StringValue((void**)ide);
         }
         GLS_Lst(GLS_Tok) index_list;
         GLS_Lst(GLS_Tok) index_list_it;
         if (EM63IndexRef_ref((void**)e63_index_ref, &index_list)) {
            GLS_FORALL(index_list_it, index_list) {
               GLS_Tok e63_index = GLS_FIRST(EM63IndexRef, index_list_it);
               int value = NatValue((void**)e63_index);
               if (dim < 4) {
                  index[dim] = value;
                  dim++;
               }
            }
         }
      }
   } else {
      ErrorPrintf("failed to parse euromap 63 parameter id\n");
   }
   if (dim == 0) {
      SafePrintf(param_id, sizeof(param_id), "%s", var_name.c_str());
   } else if (dim == 1) {
      SafePrintf(param_id, sizeof(param_id), "%s[%d]", var_name.c_str(), index[0]);
   } else if (dim == 2) {
      SafePrintf(param_id, sizeof(param_id), "%s[%d,%d]", var_name.c_str(), index[0], index[1]);
   } else if (dim == 3) {
      SafePrintf(param_id, sizeof(param_id), "%s[%d,%d,%d]", var_name.c_str(), index[0], index[1], index[2]);
   } else if (dim == 4) {
      SafePrintf(param_id, sizeof(param_id), "%s[%d,%d,%d,%d]", var_name.c_str(), index[0], index[1], index[2], index[3]);
   }
   return param_id;
  //## end cEM63StyxParser::ParseParamId%1134980233.body
}

int cEM63StyxParser::ParseTimeConst (EM63TimeConst *e63_time_const)
{
  //## begin cEM63StyxParser::ParseTimeConst%1134992996.body preserve=yes
   GLS_Tok e63_hours;
   GLS_Tok e63_minutes;
   GLS_Tok e63_seconds;
   if (EM63TimeConst_time((void**)e63_time_const, &e63_hours, &e63_minutes, &e63_seconds)) {
      int hours = NatValue((void**)e63_hours);
      int minutes = NatValue((void**)e63_minutes);
      int seconds = NatValue((void**)e63_seconds);
      cTimeObject _time(0);
      _time.Set(cTimeObject::HOUR, hours);
      _time.Set(cTimeObject::MINUTE, minutes);
      _time.Set(cTimeObject::SECOND, seconds);
      seconds = (ULONG_T)_time;
      return seconds;
   } else {
      return 0;
   }
  //## end cEM63StyxParser::ParseTimeConst%1134992996.body
}

int cEM63StyxParser::ParseDateConst (EM63DateConst *e63_date_const)
{
  //## begin cEM63StyxParser::ParseDateConst%1134992993.body preserve=yes
   GLS_Tok e63_date;
   if (EM63DateConst_date((void**)e63_date_const, &e63_date)) {
      int date = NatValue((void**)e63_date);
      int year = date / 10000;
      int month = (date % 10000) / 100;
      int day = (date % 100);
      cTimeObject _date(0);
      _date.Set(cTimeObject::YEAR, year);
      _date.Set(cTimeObject::MONTH, month);
      _date.Set(cTimeObject::DAY, day);
      int seconds = (ULONG_T)_date;
      return seconds;
   } else {
      return 0;
   }
  //## end cEM63StyxParser::ParseDateConst%1134992993.body
}

int cEM63StyxParser::ParseIntegerConst (EM63IntegerConst *e63_integer_const)
{
  //## begin cEM63StyxParser::ParseIntegerConst%1134980228.body preserve=yes
   EM63Integer e63_integer;
   if (EM63IntegerConst_num((void**)e63_integer_const, &e63_integer)) {
      return atoi(ParseInteger((void**)e63_integer).c_str());
   } else {
      return 0;
   }
  //## end cEM63StyxParser::ParseIntegerConst%1134980228.body
}

STRING_T cEM63StyxParser::ParseInteger (EM63Integer *e63_integer)
{
  //## begin cEM63StyxParser::ParseInteger%1134980228.body preserve=yes
   GLS_Tok e63_uint_value;
   GLS_Tok e63_int_value;
   if (EM63Integer_uint((void**)e63_integer, &e63_uint_value)) {
      return StringValue((void**)e63_uint_value);
   } else if (EM63Integer_int((void**)e63_integer, &e63_int_value)) {
      return StringValue((void**)e63_int_value);
   } else {
      return "";
   }
  //## end cEM63StyxParser::ParseIntegerConst%1134980228.body
}

cCondition * cEM63StyxParser::ParseCondSpec (EM63CondSpec *e63_cond_spec)
{
  //## begin cEM63StyxParser::ParseCondSpec%1134992990.body preserve=yes
   EM63ParamId e63_param_id;
   EM63RelOp e63_relop;
   EM63ConstantSpec e63_constant_spec;
   if (EM63CondSpec_cs1((void**)e63_cond_spec, &e63_param_id,  &e63_relop, &e63_constant_spec)) {
      STRING_T param_id = ParseParamId((void**)e63_param_id);
      STRING_T value = ParseConstantSpec((void**)e63_constant_spec);
      int rel_op = ParseRelOp((void**)e63_relop);
      cCondition * condition = new cParamCondition(param_id.c_str(), rel_op, value.c_str());
      return condition;
   } else {
      ErrorPrintf("failed to parse euromap 63 condition specification\n");
   }
   return NULL;
  //## end cEM63StyxParser::ParseCondSpec%1134992990.body
}

cCondition * cEM63StyxParser::ParseTimeCondSpec (EM63TimeCondSpec *e63_time_cond_spec)
{
  //## begin cEM63StyxParser::ParseTimeCondSpec%1134992991.body preserve=yes
   EM63RelOp e63_relop;
   EM63TimeConst e63_time_const;
   EM63DateConst e63_date_const;
   if (EM63TimeCondSpec_tim((void**)e63_time_cond_spec, &e63_relop, &e63_time_const, &e63_date_const)) {
      int relop = ParseRelOp((void**)e63_relop);
      int time = ParseTimeConst((void**)e63_time_const);
      int date = ParseDateConst((void**)e63_date_const);
      cCondition * condition = new cTimeCondition(relop, (date + time));
      return condition;
   } else {
      ErrorPrintf("failed to parse euromap 63 timed condition specification\n");
   }
   return NULL;
  //## end cEM63StyxParser::ParseTimeCondSpec%1134992991.body
}

int cEM63StyxParser::ParseRelOp (EM63RelOp *e63_relop)
{
  //## begin cEM63StyxParser::ParseRelOp%1134992982.body preserve=yes
   if (EM63RelOp_lt((void**)e63_relop)) {
      return EM63_LT;
   } else if (EM63RelOp_le((void**)e63_relop)) {
      return EM63_LE;
   } else if (EM63RelOp_gt((void**)e63_relop)) {
      return EM63_GT;
   } else if (EM63RelOp_ge((void**)e63_relop)) {
      return EM63_GE;
   } else if (EM63RelOp_eq((void**)e63_relop)) {
      return EM63_EQ;
   } else if (EM63RelOp_ne((void**)e63_relop)) {
      return EM63_NE;
   }
   return EM63_EQ;
  //## end cEM63StyxParser::ParseRelOp%1134992982.body
}

STRING_T cEM63StyxParser::ParseConstantSpec (EM63ConstantSpec *e63_constant_spec)
{
  //## begin cEM63StyxParser::ParseConstantSpec%1134992994.body preserve=yes
   GLS_Tok e63_hex;
   EM63Integer e63_integer;
   GLS_Tok e63_real;
   GLS_Tok e63_seq;
   if (EM63ConstantSpec_num1((void**)e63_constant_spec, &e63_hex)) {
      return StringValue((void**)e63_hex);
   } else if (EM63ConstantSpec_num2((void**)e63_constant_spec, &e63_integer)) {
      return ParseInteger((void**)e63_integer);
   } else if (EM63ConstantSpec_num3((void**)e63_constant_spec, &e63_real)) {
      return StringValue((void**)e63_real);
   } else if (EM63ConstantSpec_str((void**)e63_constant_spec, &e63_seq)) {
      return StringValue((void**)e63_seq);
   } else {
      ErrorPrintf("failed to parse euromap 63 constant specification\n");
   }
   return "";
  //## end cEM63StyxParser::ParseConstantSpec%1134992994.body
}

int cEM63StyxParser::NatValue (GLS_Tok *token)
{
  //## begin cEM63StyxParser::NatValue%1134980229.body preserve=yes
   if (token != NULL) {
      STRING_T value = (const char *)GLS_Tok_string(token);
      return atol(value.c_str());
   } else {
      return 0;
   }
  //## end cEM63StyxParser::NatValue%1134980229.body
}

int cEM63StyxParser::HexValue (GLS_Tok *token)
{
  //## begin cEM63StyxParser::HexValue%1134980230.body preserve=yes
   if (token != NULL) {
      STRING_T value = (const char *)GLS_Tok_string(token);
      LONG_T lval = 0;
      int params = sscanf(value.c_str(), "%x", &lval);
      if (params != 1) {
         params = sscanf(value.c_str(), "%X", &lval);
      }
      return lval;
   } else {
      return 0;
   }
  //## end cEM63StyxParser::HexValue%1134980230.body
}

double cEM63StyxParser::RealValue (GLS_Tok *token)
{
  //## begin cEM63StyxParser::RealValue%1134980231.body preserve=yes
   if (token != NULL) {
      STRING_T value = (const char *)GLS_Tok_string(token);
      return atof(value.c_str());
   } else {
      return 0;
   }
  //## end cEM63StyxParser::RealValue%1134980231.body
}

STRING_T cEM63StyxParser::StringValue (GLS_Tok *token)
{
  //## begin cEM63StyxParser::StringValue%1134980232.body preserve=yes
   if (token != NULL) {
      STRING_T value = (const char *)GLS_Tok_string(token);
	   if (*value.c_str() == '"') {
		   value = STRING_T(value, 1, value.size() - 2);
	   }
      return value;
   } else {
      return "";
   }
  //## end cEM63StyxParser::StringValue%1134980232.body
}

STRING_T cEM63StyxParser::CommandIdentifier(EM63CmdIde * e63_cmd_identifier)
{
   GLS_Tok ide;
   EM63IntegerConst e63_integer_const;
   if (EM63CmdIde_ide0((void**)e63_cmd_identifier, &ide)) {
      return StringValue((void**)ide);
   } else if (EM63CmdIde_key0((void**)e63_cmd_identifier, &e63_integer_const)) {
      GLS_Tok e63_uint_value;
      GLS_Tok e63_int_value;
      if (EM63Integer_uint((void**)e63_integer_const, &e63_uint_value)) {
         return StringValue((void**)e63_uint_value);
      } else if (EM63Integer_int((void**)e63_integer_const, &e63_int_value)) {
         return StringValue((void**)e63_int_value);
      } else {
         return "";
      }
   } else {
      return "";
   }
}

// Additional Declarations
  //## begin cEM63StyxParser%4380553D004C.declarations preserve=yes
  //## end cEM63StyxParser%4380553D004C.declarations

//## begin module%4380553D004C.epilog preserve=yes
//## end module%4380553D004C.epilog
