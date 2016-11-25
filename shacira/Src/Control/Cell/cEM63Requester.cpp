//## begin module%43B1044B015D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%43B1044B015D.cm

//## begin module%43B1044B015D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%43B1044B015D.cp

//## Module: cEM63Requester%43B1044B015D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cEM63Requester.cpp

//## begin module%43B1044B015D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%43B1044B015D.additionalIncludes

//## begin module%43B1044B015D.includes preserve=yes
//## end module%43B1044B015D.includes

// cUserInfo
#include "System/Objects/cUserInfo.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cEM63Requester
#include "Control/Cell/cEM63Requester.h"
// cEM63Program
#include "Control/Cell/cEM63Program.h"
// cEM63Session
#include "Control/Device/EM63/cEM63Session.h"
// cEM63Interface
#include "Control/Device/EM63/cEM63Interface.h"
// cEM63Job
#include "Control/Device/EM63/cEM63Job.h"
// cEM63StyxParser
#include "Language/cEM63StyxParser.h"
//## begin module%43B1044B015D.additionalDeclarations preserve=yes
//## end module%43B1044B015D.additionalDeclarations


// Class cEM63Requester 



cEM63Requester::cEM63Requester()
  //## begin cEM63Requester::cEM63Requester%.hasinit preserve=no
      : _Program(NULL), _Interface(NULL), _sessionDirectoryPresent(true)
  //## end cEM63Requester::cEM63Requester%.hasinit
  //## begin cEM63Requester::cEM63Requester%.initialization preserve=yes
  //## end cEM63Requester::cEM63Requester%.initialization
{
  //## begin cEM63Requester::cEM63Requester%.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63Requester::cEM63Requester%.body
}

cEM63Requester::cEM63Requester(const cEM63Requester &right)
  //## begin cEM63Requester::cEM63Requester%copy.hasinit preserve=no
      : _Program(NULL), _Interface(NULL), _sessionDirectoryPresent(true)
  //## end cEM63Requester::cEM63Requester%copy.hasinit
  //## begin cEM63Requester::cEM63Requester%copy.initialization preserve=yes
  //## end cEM63Requester::cEM63Requester%copy.initialization
{
  //## begin cEM63Requester::cEM63Requester%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEM63Requester::cEM63Requester%copy.body
}

cEM63Requester::cEM63Requester (cEM63Program *program)
  //## begin cEM63Requester::cEM63Requester%1135674629.hasinit preserve=no
      : _Program(NULL), _Interface(NULL), _sessionDirectoryPresent(true)
  //## end cEM63Requester::cEM63Requester%1135674629.hasinit
  //## begin cEM63Requester::cEM63Requester%1135674629.initialization preserve=yes
  //## end cEM63Requester::cEM63Requester%1135674629.initialization
{
  //## begin cEM63Requester::cEM63Requester%1135674629.body preserve=yes
   _Program = program;
   _Interface = program->_Interface;
  //## end cEM63Requester::cEM63Requester%1135674629.body
}


cEM63Requester::~cEM63Requester()
{
  //## begin cEM63Requester::~cEM63Requester%.body preserve=yes
  //## end cEM63Requester::~cEM63Requester%.body
}



//## Other Operations (implementation)
INT_T cEM63Requester::ControlFunc ()
{
  //## begin cEM63Requester::ControlFunc%1135674619.body preserve=yes
   cObjectLock __lock__(_Interface->SessionMutex());
   if (cSystemUtils::GetThreadData() == NULL) {
      cSystemUtils::SetThreadData(_Program->_UserInfo);
   }
   if (_Program->get_Active()) {
      STRING_T session_directory = _Program->SessionDirectory();
      if (!session_directory.empty()) {
         CheckRequest(session_directory.c_str());
      }
      else {
         if (!_sessionDirectoryPresent) {
            char log_message[0x200] = {0};
            SafePrintf(log_message, sizeof(log_message), "path now empty");
            _Interface->Log(CAT_ASYNC, OP_SCAN, 0, log_message);
            ErrorPrintf("Euromap 63: %s\n", log_message);

            // Delete fault message EM63_DIR_NOT_EXIST
            cAlarm * pAlarm = new cAlarm(this, 0x00000002, false);
            _Program->RaiseEvent(pAlarm);
            pAlarm->Release();

            _sessionDirectoryPresent = true;

            _Program->SessionDirectoryPresentChanged(_sessionDirectoryPresent);
         }
      }
   }
   return 0;
  //## end cEM63Requester::ControlFunc%1135674619.body
}

BOOL_T cEM63Requester::ParseSessionRequest (cEM63Session *session, CONST_STRING_T file)
{
  //## begin cEM63Requester::ParseSessionRequest%1135674621.body preserve=yes
   cEM63StyxParser parser;
#ifdef EM63_LOGGING_INTERFACE
   STRING_T source_code;
   int err = _Interface->Get(CAT_SYNC, file, source_code, 0/*FS_FLAG_REMOVE*/);
   if (err == 0) {
      BOOL_T success = parser.ParseSessionRequest(session, file, source_code.c_str());
      if (!success) {
         session->Failed(SESREQ_INVALID_SYNTAX, parser.get_ErrorText().c_str(), source_code.c_str());
      } 
      return success;
   } else {
      ErrorPrintf("failed to get data of file %s\n", file);
      return false;
   }
#else
   cAbstractFileSystem * file_system = _Interface->FileSystem();
   if (file_system != NULL) {
      STRING_T source_code;
      int err = file_system->Get(file, source_code, FS_FLAG_REMOVE);
      if (err == 0) {
         BOOL_T success = parser.ParseSessionRequest(session, source_code.c_str());
         if (!success) {
            session->SetErrorInfo(2, parser.get_ErrorText().c_str(), source_code.c_str());
         } 
         return success;
      } else {
         ErrorPrintf("failed to get data of file %s\n", file);
         return false;
      }
   } else {
      ErrorPrintf("missing file system to exchange Euromap 63 data\n");
      return false;
   }
#endif
  //## end cEM63Requester::ParseSessionRequest%1135674621.body
}

void cEM63Requester::CheckRequest (CONST_STRING_T directory)
{
  //## begin cEM63Requester::CheckRequest%1135674625.body preserve=yes
   STRING_LIST_T file_names;
#ifdef EM63_LOGGING_INTERFACE
   if (cFileSystemUtils::DirExists(directory)) {
      if (!_sessionDirectoryPresent) {
         char log_message[0x200] = {0};
         SafePrintf(log_message, sizeof(log_message), "path %s reachable again", directory);
         _Interface->Log(CAT_ASYNC, OP_SCAN, 0, log_message);
         ErrorPrintf("Euromap 63: %s\n", log_message);

         // Delete fault message EM63_DIR_NOT_EXIST
         cAlarm * pAlarm = new cAlarm(this, 0x00000002, false);
         _Program->RaiseEvent(pAlarm);
         pAlarm->Release();

         _sessionDirectoryPresent = true;
         
         _Program->SessionDirectoryPresentChanged(_sessionDirectoryPresent);
      }
      if (_Interface->Scan(file_names, "SESS*.REQ", directory) > 0) {
         STRING_LIST_T::const_iterator i = file_names.begin();
         while (i != file_names.end()) {
            STRING_T file = cFileSystemUtils::AppendPath(directory, (*i).c_str());
            HandleSession(file.c_str());
            i++;
         }
      }
   } else {
      if (_sessionDirectoryPresent) {
         char log_message[0x200] = {0};
         SafePrintf(log_message, sizeof(log_message), "path %s not existent or not reachable", directory);
         _Interface->Log(CAT_ASYNC, OP_SCAN, -1, log_message);
         ErrorPrintf("Euromap 63: %s\n", log_message);

         // Create fault message
         cAlarm * pAlarm = new cAlarm(this, 0x00000002, true, EM63_DIR_NOT_EXIST);
         pAlarm->set_Severity(SevError);
         pAlarm->set_Param1(directory);
         _Program->RaiseEvent(pAlarm);
         pAlarm->Release();

         _sessionDirectoryPresent = false;

         _Program->SessionDirectoryPresentChanged(_sessionDirectoryPresent);
      }
      cSystemUtils::Suspend(2000);
   }
#else
   cAbstractFileSystem * file_system = _Interface->FileSystem();
   if (file_system != NULL) {
      file_system->set_BasePath(directory);
      if (file_system->Scan(file_names, "SESS*.REQ") > 0) {
         STRING_LIST_T::const_iterator i = file_names.begin();
         while (i != file_names.end()) {
            STRING_T file = cFileSystemUtils::AppendPath(directory, (*i).c_str());
            HandleSession(file.c_str());
            i++;
         }
      }
   } else {
      ErrorPrintf("missing file system to exchange Euromap 63 data\n");
   }
#endif
  //## end cEM63Requester::CheckRequest%1135674625.body
}

void cEM63Requester::HandleSession (CONST_STRING_T source)
{
  //## begin cEM63Requester::HandleSession%1135674626.body preserve=yes
   cEM63Session * session = new cEM63Session(_Interface, source);
   ULONG_T rc = _Interface->AddSession(session);
   if (rc == SESSION_CODE_NO_ERROR) {
      cContext * context = _Program->_Context;
      if (ParseSessionRequest(session, source)) {
         if (session->Process(context)) {
            session->Start();
         }
      }
   }
   else { // couldn't add session
       char param1[0x10] = {0};
       char param2[0x10] = {0};
       SafePrintf(param1, sizeof(param1), "%d", session->get_SessionId());
       SafePrintf(param2, sizeof(param2), "%d", _Interface->MaxSessions());

       session->Failed(rc, param1, param2);
   }

   session->Respond();

   // Remove Request file after response and wait 50ms
   cSystemUtils::Suspend(50);
   _Interface->RemoveFile(CAT_SYNC, source);
   cSystemUtils::Suspend(50);
  //## end cEM63Requester::HandleSession%1135674626.body
}

// Additional Declarations
  //## begin cEM63Requester%43B1044B015D.declarations preserve=yes
  //## end cEM63Requester%43B1044B015D.declarations

//## begin module%43B1044B015D.epilog preserve=yes
//## end module%43B1044B015D.epilog
