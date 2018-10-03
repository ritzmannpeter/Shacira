//## begin module%4380829603D0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380829603D0.cm

//## begin module%4380829603D0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380829603D0.cp

//## Module: cEM63Session%4380829603D0; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cEM63Session.cpp

//## begin module%4380829603D0.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4380829603D0.additionalIncludes

//## begin module%4380829603D0.includes preserve=yes
//## end module%4380829603D0.includes

// cContext
#include "System/Database/cContext.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cEM63Session
#include "Control/Device/EM63/cEM63Session.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
// cEM63Job
#include "Control/Device/EM63/cEM63Job.h"
// cEM63StyxParser
#include "Language/cEM63StyxParser.h"
//## begin module%4380829603D0.additionalDeclarations preserve=yes
//## end module%4380829603D0.additionalDeclarations


// Class cEM63Session 













cEM63Session::cEM63Session()
  //## begin cEM63Session::cEM63Session%.hasinit preserve=no
      : _SessionId(0), _Failed(false), _ErrorCode(0), _Interface(NULL)
  //## end cEM63Session::cEM63Session%.hasinit
  //## begin cEM63Session::cEM63Session%.initialization preserve=yes
  //## end cEM63Session::cEM63Session%.initialization
{
  //## begin cEM63Session::cEM63Session%.body preserve=yes
   INCREMENT_OBJECT_COUNT()
   //## end cEM63Session::cEM63Session%.body
}

cEM63Session::cEM63Session(const cEM63Session &right)
  //## begin cEM63Session::cEM63Session%copy.hasinit preserve=no
      : _SessionId(0), _Failed(false), _ErrorCode(0), _Interface(NULL)
  //## end cEM63Session::cEM63Session%copy.hasinit
  //## begin cEM63Session::cEM63Session%copy.initialization preserve=yes
  //## end cEM63Session::cEM63Session%copy.initialization
{
  //## begin cEM63Session::cEM63Session%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63Session::cEM63Session%copy.body
}

cEM63Session::cEM63Session (cEM63Interface *itf, CONST_STRING_T request_file)
  //## begin cEM63Session::cEM63Session%1133895373.hasinit preserve=no
      : _SessionId(0), _Failed(false), _ErrorCode(0), _Interface(NULL)
  //## end cEM63Session::cEM63Session%1133895373.hasinit
  //## begin cEM63Session::cEM63Session%1133895373.initialization preserve=yes
  //## end cEM63Session::cEM63Session%1133895373.initialization
{
  //## begin cEM63Session::cEM63Session%1133895373.body preserve=yes
   _Interface = itf;
   if (_Interface != NULL) {
      _RequestFile = _Interface->AbsPath(request_file);

      STRING_T file_spec = cFileSystemUtils::FileName(_RequestFile.c_str());
      for (int i=0; i<file_spec.length(); i++) {
         file_spec.at(i) = toupper(file_spec.at(i));
      }

      int params = sscanf(file_spec.c_str(), "SESS%d.REQ", &_SessionId);
      char response_file_name[20] = {0};
      SafePrintf(response_file_name, sizeof(response_file_name), "SESS%04.04d.RSP", _SessionId);
      STRING_T response_path = cFileSystemUtils::DirName(_RequestFile.c_str());
      _ResponseFile = cFileSystemUtils::AppendPath(response_path.c_str(), response_file_name);
   }
   INCREMENT_OBJECT_COUNT()
   //## end cEM63Session::cEM63Session%1133895373.body
}


cEM63Session::~cEM63Session()
{
  //## begin cEM63Session::~cEM63Session%.body preserve=yes
   DECREMENT_OBJECT_COUNT()
   //## end cEM63Session::~cEM63Session%.body
}



//## Other Operations (implementation)
void cEM63Session::SetInterface (cEM63Interface *itf)
{
  //## begin cEM63Session::SetInterface%1134822065.body preserve=yes
   _Interface = itf;
  //## end cEM63Session::SetInterface%1134822065.body
}

cEM63Interface * cEM63Session::Interface ()
{
  //## begin cEM63Session::Interface%1134822067.body preserve=yes
   return _Interface;
  //## end cEM63Session::Interface%1134822067.body
}

void cEM63Session::AddJob (cEM63Job *job)
{
  //## begin cEM63Session::AddJob%1133895375.body preserve=yes
   ULONG_T size = _Jobs.size();
   _Jobs.resize(size+1);
   _Jobs[size] = job;
  //## end cEM63Session::AddJob%1133895375.body
}

void cEM63Session::Failed (ULONG_T code, CONST_STRING_T param1, CONST_STRING_T param2)
{
  //## begin cEM63Session::Failed%1135017139.body preserve=yes
   _Failed = true;
   _ErrorCode = code;
   _Param1 = param1;
   _Param2 = param2;
#ifdef EM63_LOGGING_INTERFACE
   _ErrorMsg = cEM63Interface::ErrorText(EM63_SESSION, code, param1, param2);
   Interface()->Log(CAT_SYNC, OP_GENERAL, code, _ErrorMsg.c_str());
#endif
  //## end cEM63Session::Failed%1135017139.body
}

BOOL_T cEM63Session::Process (cContext *context)
{
  //## begin cEM63Session::Process%1135068533.body preserve=yes
   if (_Interface == NULL) {
      return false;
   }
   _Interface->SetContext(context);
   ULONG_T jobs = _Jobs.size();
   for (ULONG_T i=0; i<jobs; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         STRING_T request_file = job->RequestFile();
         if (request_file.size() > 0) {
            STRING_T source_code;
#ifdef EM63_LOGGING_INTERFACE
            int err = _Interface->Get(CAT_SYNC, request_file.c_str(), source_code, 0);
            if (err == 0) {
               STRING_T err_text;
               if (ParsePresentationRequest(job, request_file.c_str(), source_code.c_str(), err_text)) {
                  if (!job->HasFailed()) {
                     job->Process(context);
                  }
               } else {
                  if (!job->HasFailed()) {
                     Failed(JOBCMD_INVALID_SYNTAX, err_text.c_str());
                  }
                  else {
                     return false;
                  }
               }
            } else {
               STRING_T sMsg = request_file + " not found";
               Failed(OPEN_JOB_REQUEST_FILE, sMsg.c_str());
               ErrorPrintf("job file %s\n", sMsg.c_str());
            }
#else
            cAbstractFileSystem * file_system = _Interface->FileSystem();
            int err = file_system->Get(request_file.c_str(), source_code, 0);
            if (err == 0) {
               STRING_T err_text;
               if (ParsePresentationRequest(job, source_code.c_str(), request_file.c_str(), err_text)) {
                  job->Process(context);
               } else {
                  job->Failed(JOBCMD_INVALID_SYNTAX, err_text.c_str());
               }
            } else {
               STRING_T sMsg = "job file " + request_file + " not found";
               job->Failed(CREATE_JOB_RESPONSE_FILE, sMsg.c_str());
               ErrorPrintf("%s\n", sMsg.c_str());
            }
#endif
         }
      }
   }
   return true;
  //## end cEM63Session::Process%1135068533.body
}

BOOL_T cEM63Session::Start ()
{
  //## begin cEM63Session::Start%1135068534.body preserve=yes
   ULONG_T jobs = _Jobs.size();
   for (ULONG_T i=0; i<jobs; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         job->Start();
      }
   }
   return true;
  //## end cEM63Session::Start%1135068534.body
}

void cEM63Session::Control ()
{
  //## begin cEM63Session::Control%1135068535.body preserve=yes
   ULONG_T size = _Jobs.size();
   for (ULONG_T i=0; i<size; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         if (job->IsActive()) {
            job->Control();
         }
      }
   }
  //## end cEM63Session::Control%1135068535.body
}

void cEM63Session::Stop ()
{
  //## begin cEM63Session::Stop%1135068541.body preserve=yes
   ULONG_T size = _Jobs.size();
   for (ULONG_T i=0; i<size; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         if (job->IsActive()) {
            job->Stop();
         }
      }
   }
  //## end cEM63Session::Stop%1135068541.body
}

void cEM63Session::CleanUp ()
{
  //## begin cEM63Session::CleanUp%1136213367.body preserve=yes
   ULONG_T size = _Jobs.size();
   for (ULONG_T i=0; i<size; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         job->CleanUp();
         if (job->IsTerminated()) {
            _Jobs[i] = NULL;
#ifdef EM63_LOGGING_INTERFACE
#else
            InfoPrintf("deleting job %s\n", job->get_JobName().c_str());
#endif
            delete job;
         }
      }
   }
  //## end cEM63Session::CleanUp%1136213367.body
}

void cEM63Session::Abort (int abort_type, CONST_STRING_T name)
{
  //## begin cEM63Session::Abort%1136213371.body preserve=yes
   ULONG_T size = _Jobs.size();
   for (ULONG_T i=0; i<size; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         if (job->IsActive()) {
            job->Abort(abort_type, name);
         }
      }
   }
  //## end cEM63Session::Abort%1136213371.body
}

void cEM63Session::Respond ()
{
  //## begin cEM63Session::Respond%1135017141.body preserve=yes
   ULONG_T jobs = _Jobs.size();
   for (ULONG_T i=0; i<jobs; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         job->Respond();
      }
   }
   cBufferedFile file;
   if (_Failed) {
      STRING_T text = cEM63Interface::ErrorText(EM63_SESSION, _ErrorCode, _Param1.c_str(), _Param2.c_str());
      file.Printf("ERROR %02.02d %08.08d \"%s\";\n", (int)5, _ErrorCode, text.c_str());
   } else {
//      file.Printf("CONNECT PROCESSED\n");
      for (ULONG_T i=0; i<jobs; i++) {
         cEM63Job * job = _Jobs[i];
         if (job != NULL) {
            STRING_T request_file = job->RequestFile();
            STRING_T cmd_ident = job->get_CommandIdentifier();
            BOOL_T failed = job->HasFailed();
            if (failed) {
               ULONG_T code = job->get_ErrorCode();
               STRING_T text = job->get_ErrorMsg();
               file.Printf("%s ERROR %02.02d %08.08d \"%s\";\n", cmd_ident.c_str(), (int)5, code, text.c_str());
            } else {
               if (request_file.size() > 0) {
                  file.Printf("%s PROCESSED \"EXECUTE %s\";\n", cmd_ident.c_str(), request_file.c_str());
               } else {
                  file.Printf("%s PROCESSED \"CONNECT\";\n", cmd_ident.c_str());
               }
            }
         }
      }
   }
#ifdef EM63_LOGGING_INTERFACE
   if (_Interface != NULL) {
      STRING_T text = file.Buffer();
      int rc = _Interface->Put(CAT_SYNC, _ResponseFile.c_str(), text.c_str(), 0);
      if (rc < 0) {
         Failed(CREATE_SESSION_RESPONSE_FILE, _ResponseFile.c_str());
      }
   }
#else
   if (_Interface != NULL) {
      cAbstractFileSystem * file_system = Interface()->FileSystem();
      if (file_system != NULL) {
         STRING_T text = file.Buffer();
         file_system->Put(_ResponseFile.c_str(), text.c_str(), 0);
      }
   }
#endif
  //## end cEM63Session::Respond%1135017141.body
}

BOOL_T cEM63Session::IsActive ()
{
  //## begin cEM63Session::IsActive%1135162873.body preserve=yes
   ULONG_T size = _Jobs.size();
   for (ULONG_T i=0; i<size; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         if (job->IsActive()) {
            return true;
         }
      }
   }
   return false;
  //## end cEM63Session::IsActive%1135162873.body
}

BOOL_T cEM63Session::IsTerminated ()
{
  //## begin cEM63Session::IsTerminated%1136286710.body preserve=yes
   ULONG_T size = _Jobs.size();
   for (ULONG_T i=0; i<size; i++) {
      cEM63Job * job = _Jobs[i];
      if (job != NULL) {
         if (!job->IsTerminated()) {
            return false;
         }
      }
   }
   return true;
  //## end cEM63Session::IsTerminated%1136286710.body
}

BOOL_T cEM63Session::HasFailed ()
{
  //## begin cEM63Session::HasFailed%1136457205.body preserve=yes
   return _Failed;
  //## end cEM63Session::HasFailed%1136457205.body
}

void cEM63Session::SetErrorInfo (int error_code, CONST_STRING_T param1, CONST_STRING_T param2)
{
  //## begin cEM63Session::SetErrorInfo%1140161327.body preserve=yes
   _Failed = true;
   _ErrorCode = error_code;
   _Param1 = param1;
   _Param2 = param2;
  //## end cEM63Session::SetErrorInfo%1140161327.body
}

void cEM63Session::SetRequestFile (const STRING_T &file)
{
  //## begin cEM63Session::SetRequestFile%1166170820.body preserve=yes
   if (_Interface != NULL) {
      _RequestFile = _Interface->AbsPath(file.c_str());
   }
  //## end cEM63Session::SetRequestFile%1166170820.body
}

STRING_T cEM63Session::RequestFile ()
{
  //## begin cEM63Session::RequestFile%1166170821.body preserve=yes
   return _RequestFile;
  //## end cEM63Session::RequestFile%1166170821.body
}

void cEM63Session::SetResponseFile (const STRING_T &file)
{
  //## begin cEM63Session::SetResponseFile%1166170822.body preserve=yes
   if (_Interface != NULL) {
      _ResponseFile = _Interface->AbsPath(file.c_str());
   }
  //## end cEM63Session::SetResponseFile%1166170822.body
}

STRING_T cEM63Session::ResponseFile ()
{
  //## begin cEM63Session::ResponseFile%1166170823.body preserve=yes
   return _ResponseFile;
  //## end cEM63Session::ResponseFile%1166170823.body
}

BOOL_T cEM63Session::ParsePresentationRequest (cEM63Job *job, CONST_STRING_T file, CONST_STRING_T source_code, STRING_T &err_text)
{
  //## begin cEM63Session::ParsePresentationRequest%1135068542.body preserve=yes
   cEM63StyxParser parser;
   if (!parser.ParsePresentationRequest(this, job, file, source_code)) {
      err_text = parser.get_ErrorText();
      ErrorPrintf("%s\n", err_text.c_str());
      return false;
   } else {
      return true;
   }
  //## end cEM63Session::ParsePresentationRequest%1135068542.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cEM63Session::get_SessionId () const
{
  //## begin cEM63Session::get_SessionId%4395DE920146.get preserve=no
  return _SessionId;
  //## end cEM63Session::get_SessionId%4395DE920146.get
}

void cEM63Session::set_SessionId (ULONG_T value)
{
  //## begin cEM63Session::set_SessionId%4395DE920146.set preserve=no
  _SessionId = value;
  //## end cEM63Session::set_SessionId%4395DE920146.set
}

// Additional Declarations
  //## begin cEM63Session%4380829603D0.declarations preserve=yes
  //## end cEM63Session%4380829603D0.declarations

//## begin module%4380829603D0.epilog preserve=yes
//## end module%4380829603D0.epilog
