//## begin module%4380835603C0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380835603C0.cm

//## begin module%4380835603C0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380835603C0.cp

//## Module: cEM63Job%4380835603C0; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\EM63\cEM63Job.cpp

//## begin module%4380835603C0.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4380835603C0.additionalIncludes

//## begin module%4380835603C0.includes preserve=yes
//## end module%4380835603C0.includes

// cContext
#include "System/Database/cContext.h"
// cPresentationCmd
#include "Control/Device/EM63/cPresentationCmd.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
// cEM63Job
#include "Control/Device/EM63/cEM63Job.h"
//## begin module%4380835603C0.additionalDeclarations preserve=yes
//## end module%4380835603C0.additionalDeclarations


// Class cEM63Job 













cEM63Job::cEM63Job()
  //## begin cEM63Job::cEM63Job%.hasinit preserve=no
      : _Failed(false), _ErrorCode(0), _Session(NULL)
  //## end cEM63Job::cEM63Job%.hasinit
  //## begin cEM63Job::cEM63Job%.initialization preserve=yes
  //## end cEM63Job::cEM63Job%.initialization
{
  //## begin cEM63Job::cEM63Job%.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63Job::cEM63Job%.body
}

cEM63Job::cEM63Job(const cEM63Job &right)
  //## begin cEM63Job::cEM63Job%copy.hasinit preserve=no
      : _Failed(false), _ErrorCode(0), _Session(NULL)
  //## end cEM63Job::cEM63Job%copy.hasinit
  //## begin cEM63Job::cEM63Job%copy.initialization preserve=yes
  //## end cEM63Job::cEM63Job%copy.initialization
{
  //## begin cEM63Job::cEM63Job%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63Job::cEM63Job%copy.body
}

cEM63Job::cEM63Job (cEM63Session *session, CONST_STRING_T request_file)
  //## begin cEM63Job::cEM63Job%1134738523.hasinit preserve=no
      : _Failed(false), _ErrorCode(0), _Session(NULL)
  //## end cEM63Job::cEM63Job%1134738523.hasinit
  //## begin cEM63Job::cEM63Job%1134738523.initialization preserve=yes
  //## end cEM63Job::cEM63Job%1134738523.initialization
{
  //## begin cEM63Job::cEM63Job%1134738523.body preserve=yes
   _Session = session;
   if (_Session->Interface() != NULL) {
      _RequestFile = _Session->Interface()->AbsPath(request_file);
   }
   INCREMENT_OBJECT_COUNT()
  //## end cEM63Job::cEM63Job%1134738523.body
}

cEM63Job::cEM63Job (cEM63Session *session)
  //## begin cEM63Job::cEM63Job%1233306614.hasinit preserve=no
      : _Failed(false), _ErrorCode(0), _Session(NULL)
  //## end cEM63Job::cEM63Job%1233306614.hasinit
  //## begin cEM63Job::cEM63Job%1233306614.initialization preserve=yes
  //## end cEM63Job::cEM63Job%1233306614.initialization
{
  //## begin cEM63Job::cEM63Job%1233306614.body preserve=yes
   _Session = session;
   INCREMENT_OBJECT_COUNT()
  //## end cEM63Job::cEM63Job%1233306614.body
}

cEM63Job::~cEM63Job()
{
  //## begin cEM63Job::~cEM63Job%.body preserve=yes
   if (_Session->Interface() != NULL) {
      _Session->Interface()->RemoveJob(this);
   }
   DECREMENT_OBJECT_COUNT()
  //## end cEM63Job::~cEM63Job%.body
}



//## Other Operations (implementation)
void cEM63Job::Initialize (CONST_STRING_T job_name, CONST_STRING_T response_file)
{
  //## begin cEM63Job::Initialize%1135078974.body preserve=yes
   _JobName = job_name;
   if (_Session->Interface() != NULL) {
      if (_Session->Interface()->JobCount() < _Session->Interface()->MaxJobs()) {
         _ResponseFile = _Session->Interface()->AbsPath(response_file);
         _Session->Interface()->AddJob(this);
      }
      else { // Max Jobs reached
         Failed(TOO_MANY_ACTIVE_JOBS);
      }
   }
  //## end cEM63Job::Initialize%1135078974.body
}

void cEM63Job::SetSession (cEM63Session *session)
{
  //## begin cEM63Job::SetSession%1134835346.body preserve=yes
   _Session = session;
  //## end cEM63Job::SetSession%1134835346.body
}

cEM63Session * cEM63Job::Session ()
{
  //## begin cEM63Job::Session%1134835347.body preserve=yes
   return _Session;
  //## end cEM63Job::Session%1134835347.body
}

void cEM63Job::AddCommand (cPresentationCmd *command)
{
  //## begin cEM63Job::AddCommand%1134738524.body preserve=yes
   ULONG_T size = _Commands.size();
   _Commands.resize(size + 1);
   _Commands[size] = command;
  //## end cEM63Job::AddCommand%1134738524.body
}

void cEM63Job::Commands (COMMAND_LIST_T &commands)
{
  //## begin cEM63Job::Commands%1134835350.body preserve=yes
   ULONG_T size = _Commands.size();
   for (ULONG_T i=0; i<size; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         commands.push_back(command);
      }
   }
  //## end cEM63Job::Commands%1134835350.body
}

void cEM63Job::Failed (ULONG_T code, CONST_STRING_T param1, CONST_STRING_T param2)
{
  //## begin cEM63Job::Failed%1135017138.body preserve=yes
   _Failed = true;
   _ErrorCode = code;
   _Param1 = param1;
   _Param2 = param2;
#ifdef EM63_LOGGING_INTERFACE
   _ErrorMsg = cEM63Interface::ErrorText(EM63_PRESENTATION, code, param1, param2);
   if (_Session->Interface() != NULL) {
      _Session->Interface()->Log(CAT_SYNC, OP_GENERAL, code, _ErrorMsg.c_str());
   }
#endif
  //## end cEM63Job::Failed%1135017138.body
}

BOOL_T cEM63Job::Process (cContext *context)
{
  //## begin cEM63Job::Process%1135068536.body preserve=yes
   ULONG_T commands = _Commands.size();
   for (ULONG_T i=0; i<commands; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
#ifdef EM63_LOGGING_INTERFACE
         if (_Session->Interface() != NULL) {
            if (command->Process(context)) {
               _Session->Interface()->Log(CAT_SYNC, OP_PROCESS_CMD, 0, _JobName.c_str(), "processed");
            } else {
               _Session->Interface()->Log(CAT_SYNC, OP_PROCESS_CMD, -1, _JobName.c_str(), "failed to process");
            }
         }
#else
         command->Process(context);
#endif
      }
   }
   return true;
  //## end cEM63Job::Process%1135068536.body
}

void cEM63Job::Respond ()
{
  //## begin cEM63Job::Respond%1135068540.body preserve=yes
   cTimeObject t;
   ULONG_T now = t;
   ULONG_T commands = _Commands.size();
   for (ULONG_T i=0; i<commands; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         cBufferedFile file;
         if (i == 0) {
            BOOL_T failed = HasFailed();
            if (failed) {
               ULONG_T error_code = get_ErrorCode();
               STRING_T error_msg = get_ErrorMsg();
               file.Printf("COMMAND %d ERROR %02.02d %08.08d \"%s\" %s %s;\n", i + 1,
                           6,
                           error_code,
                           error_msg.c_str(),
                           cEM63Interface::Date(now).c_str(),
                           cEM63Interface::Time(now).c_str());
            } else {
               file.Printf("COMMAND %d PROCESSED \"%s\" %s %s;\n", i + 1,
                           command->CommandString(EM63_JOB_COMMAND).c_str(),
                           cEM63Interface::Date(now).c_str(), cEM63Interface::Time(now).c_str());
            }
         }

         BOOL_T failed = command->HasFailed();
         if (failed) {
            ULONG_T error_code = command->get_ErrorCode();
            STRING_T error_msg = command->get_ErrorMsg();
            file.Printf("COMMAND %d ERROR %02.02d %08.08d \"%s\" %s %s;\n", i + 2, // HA030506 change 1->2
                        6,
                        error_code,
                        error_msg.c_str(),
                        cEM63Interface::Date(now).c_str(),
                        cEM63Interface::Time(now).c_str());
         } else {
            file.Printf("COMMAND %d PROCESSED \"%s\" %s %s;\n", i + 2,
                        command->CommandString().c_str(),
                        cEM63Interface::Date(now).c_str(),
                        cEM63Interface::Time(now).c_str());
         }
#ifdef EM63_LOGGING_INTERFACE
         if (_Session->Interface() != NULL) {
            STRING_T text = file.Buffer();
            int rc = _Session->Interface()->Put(CAT_SYNC, _ResponseFile.c_str(), text.c_str(), i == 0 ? 0 : FS_FLAG_APPEND);
            if (rc < 0) {
               _Session->Failed(CREATE_JOB_RESPONSE_FILE, _ResponseFile.c_str());
            }
         }
#else
         if (_Session->Interface() != NULL) {
            cAbstractFileSystem * file_system = _Session->Interface()->FileSystem();
            if (file_system != NULL) {
               STRING_T text = file.Buffer();
               file_system->Put(_ResponseFile.c_str(), text.c_str(), i == 0 ? 0 : FS_FLAG_APPEND);
            }
         }
#endif
      }
   }
  //## end cEM63Job::Respond%1135068540.body
}

BOOL_T cEM63Job::Start ()
{
  //## begin cEM63Job::Start%1135068537.body preserve=yes
   ULONG_T commands = _Commands.size();
   for (ULONG_T i=0; i<commands; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         if (!command->IsStarted() && !command->HasFailed()) {
#ifdef EM63_LOGGING_INTERFACE
            if (_Session->Interface() != NULL) {
               char msg[0x100] = {0};
               SafePrintf(msg, sizeof(msg), "starting job %s", _JobName.c_str());
               _Session->Interface()->Log(CAT_SYNC, OP_START_CMD, 0, msg);
               if (!command->Start()) {
                  _Session->Interface()->Log(CAT_SYNC, OP_START_CMD, 0, _JobName.c_str(), "failed to start");
               }
            }
#else
            command->Start();
#endif
         }
      }
   }
   return true;
  //## end cEM63Job::Start%1135068537.body
}

void cEM63Job::Control ()
{
  //## begin cEM63Job::Control%1135068538.body preserve=yes
   ULONG_T size = _Commands.size();
   for (ULONG_T i=0; i<size; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         if (command->IsActive()) {
            command->Control();
         }
      }
   }
  //## end cEM63Job::Control%1135068538.body
}

void cEM63Job::Stop ()
{
  //## begin cEM63Job::Stop%1135068539.body preserve=yes
   ULONG_T size = _Commands.size();
   for (ULONG_T i=0; i<size; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         if (command->IsActive()) {
            command->Stop();
         }
      }
   }
  //## end cEM63Job::Stop%1135068539.body
}

void cEM63Job::CleanUp ()
{
  //## begin cEM63Job::CleanUp%1136213366.body preserve=yes
   ULONG_T size = _Commands.size();
   for (ULONG_T i=0; i<size; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         if (command->IsTerminated()) {
            _Commands[i] = NULL;
#ifdef EM63_LOGGING_INTERFACE
#else
            InfoPrintf("deleting command %s\n", command->Key().c_str());
#endif
            delete command;
         }
      }
   }
  //## end cEM63Job::CleanUp%1136213366.body
}

void cEM63Job::Abort (int abort_type, CONST_STRING_T name)
{
  //## begin cEM63Job::Abort%1136213370.body preserve=yes
   ULONG_T size = _Commands.size();
   for (ULONG_T i=0; i<size; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         command->Abort(abort_type, name);
      }
   }
  //## end cEM63Job::Abort%1136213370.body
}

cPresentationCmd * cEM63Job::Command (ULONG_T index)
{
  //## begin cEM63Job::Command%1134835351.body preserve=yes
   ULONG_T size = _Commands.size();
   if (index < size) {
      return _Commands[index];
   } else {
      return NULL;
   }
  //## end cEM63Job::Command%1134835351.body
}

BOOL_T cEM63Job::IsActive ()
{
  //## begin cEM63Job::IsActive%1135162872.body preserve=yes
   ULONG_T size = _Commands.size();
   for (ULONG_T i=0; i<size; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         if (command->IsActive()) {
            return true;
         }
      }
   }
   return false;
  //## end cEM63Job::IsActive%1135162872.body
}

BOOL_T cEM63Job::IsTerminated ()
{
  //## begin cEM63Job::IsTerminated%1136286709.body preserve=yes
   if (HasFailed() && (get_ErrorCode() == JOB_WITH_THE_SAME_NAME)) {
      return true; // Terminate job when job have the same name
   }

   ULONG_T size = _Commands.size();
   for (ULONG_T i=0; i<size; i++) {
      cPresentationCmd * command = _Commands[i];
      if (command != NULL) {
         if (!command->IsTerminated()) {
            return false;
         }
      }
   }
   return true;
  //## end cEM63Job::IsTerminated%1136286709.body
}

BOOL_T cEM63Job::HasFailed ()
{
  //## begin cEM63Job::HasFailed%1136457204.body preserve=yes
   return _Failed;
  //## end cEM63Job::HasFailed%1136457204.body
}

ULONG_T cEM63Job::get_ErrorCode () const
{
  //## begin cEM63Job::get_ErrorCode
  return _ErrorCode;
  //## end cEM63Job::get_ErrorCode
}

STRING_T cEM63Job::get_ErrorMsg () const
{
  //## begin cEM63Job::get_ErrorMsg
  return _ErrorMsg;
  //## end cEM63Job::get_ErrorMsg
}

void cEM63Job::SetRequestFile (const STRING_T &file)
{
  //## begin cEM63Job::SetRequestFile%1166170826.body preserve=yes
   if (_Session->Interface() != NULL) {
      _RequestFile = _Session->Interface()->AbsPath(file.c_str());
   }
   //## end cEM63Job::SetRequestFile%1166170826.body
}

STRING_T cEM63Job::RequestFile ()
{
  //## begin cEM63Job::RequestFile%1166170827.body preserve=yes
   return _RequestFile;
  //## end cEM63Job::RequestFile%1166170827.body
}

void cEM63Job::SetResponseFile (const STRING_T &file)
{
  //## begin cEM63Job::SetResponseFile%1166170828.body preserve=yes
   if (_Session->Interface() != NULL) {
      _ResponseFile = _Session->Interface()->AbsPath(file.c_str());
   }
  //## end cEM63Job::SetResponseFile%1166170828.body
}

STRING_T cEM63Job::ResponseFile ()
{
  //## begin cEM63Job::ResponseFile%1166170829.body preserve=yes
   return _ResponseFile;
  //## end cEM63Job::ResponseFile%1166170829.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cEM63Job::get_JobName () const
{
  //## begin cEM63Job::get_JobName%43A2B9720014.get preserve=no
  return _JobName;
  //## end cEM63Job::get_JobName%43A2B9720014.get
}

void cEM63Job::set_JobName (STRING_T value)
{
  //## begin cEM63Job::set_JobName%43A2B9720014.set preserve=no
  _JobName = value;
  //## end cEM63Job::set_JobName%43A2B9720014.set
}

STRING_T cEM63Job::get_CommandIdentifier () const
{
  //## begin cEM63Job::get_CommandIdentifier%43F4D80F0236.get preserve=no
  return _CommandIdentifier;
  //## end cEM63Job::get_CommandIdentifier%43F4D80F0236.get
}

void cEM63Job::set_CommandIdentifier (STRING_T value)
{
  //## begin cEM63Job::set_CommandIdentifier%43F4D80F0236.set preserve=no
  _CommandIdentifier = value;
  //## end cEM63Job::set_CommandIdentifier%43F4D80F0236.set
}

// Additional Declarations
  //## begin cEM63Job%4380835603C0.declarations preserve=yes
  //## end cEM63Job%4380835603C0.declarations

//## begin module%4380835603C0.epilog preserve=yes
//## end module%4380835603C0.epilog
