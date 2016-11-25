//## begin module%3DD3BCC70122.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD3BCC70122.cm

//## begin module%3DD3BCC70122.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD3BCC70122.cp

//## Module: cResources%3DD3BCC70122; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cResources.cpp

//## begin module%3DD3BCC70122.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DD3BCC70122.additionalIncludes

//## begin module%3DD3BCC70122.includes preserve=yes

#include <time.h>
#include "debug_log.h"
#include "System/cTimeObject.h"
#include "System/Sys/cexceptionhnd.h"

//## end module%3DD3BCC70122.includes

// cResources
#include "System/Process/cResources.h"
// cSHProcess
#include "System/Process/cSHProcess.h"
// cOptions
#include "System/Process/cOptions.h"
// cObjectLock
#include "System/Objects/cObjectLock.h"
// cMemoryConsole
#include "System/Console/cMemoryConsole.h"
// cStandardConsole
#include "System/Console/cStandardConsole.h"
// cConsole
#include "System/Console/cConsole.h"
// cFileConsole
#include "System/Console/cFileConsole.h"
// cSocketConsole
#include "System/Console/cSocketConsole.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
//## begin module%3DD3BCC70122.additionalDeclarations preserve=yes

static char _ShaciraVersion[0x200] = {0};
static char _Text[0x8000];
static cMutexSem _WriteInfoMutex;
#define LOCK_WRITE_INFO cObjectLock __lock__(&_WriteInfoMutex);

// <-MW- 2005-04-19
const char *cResources::_current_file = 0;
int cResources::_current_line = -1;
// -MW->

static char _TimeText[0x200] = {0};
static const char * TimeText()
{
   memset(_TimeText, 0, sizeof(_TimeText));
   time_t timer;
   struct tm * time_struct;
   timer = time(NULL);
   time_struct = localtime(&timer);
   sprintf(_TimeText, "%s", asctime(time_struct));
   return _TimeText;
}

//## end module%3DD3BCC70122.additionalDeclarations


// Class cResources 

//## begin cResources::UseDebugLog%4237147402FD.attr preserve=no  public: static BOOL_T {U} true
BOOL_T cResources::_UseDebugLog = true;
//## end cResources::UseDebugLog%4237147402FD.attr

//## begin cResources::LogGenerations%42305CB401A5.attr preserve=no  public: static ULONG_T {U} 2
ULONG_T cResources::_LogGenerations = 2;
//## end cResources::LogGenerations%42305CB401A5.attr

//## begin cResources::LogFileSize%42305CD30128.attr preserve=no  public: static ULONG_T {U} 0x40000
ULONG_T cResources::_LogFileSize = 0x40000;
//## end cResources::LogFileSize%42305CD30128.attr

//## begin cResources::LogFileName%4013D8330251.attr preserve=no  public: static STRING_T {U} "Shacira.log"
STRING_T cResources::_LogFileName = "Shacira.log";
//## end cResources::LogFileName%4013D8330251.attr

//## begin cResources::DefaultConsole%4060280E004E.attr preserve=no  public: static cConsole * {U} 
cConsole *cResources::_DefaultConsole;
//## end cResources::DefaultConsole%4060280E004E.attr

//## begin cResources::DefaultLanguage%4549BF39006D.attr preserve=no  public: static STRING_T {U} "de"
STRING_T cResources::_DefaultLanguage = "de";
//## end cResources::DefaultLanguage%4549BF39006D.attr

//## begin cResources::LogPath%3DD3C67601D1.attr preserve=no  implementation: static STRING_T {U} "Log"
STRING_T cResources::_LogPath = "Log";
//## end cResources::LogPath%3DD3C67601D1.attr

//## begin cResources::ConfigPath%3DE5D8A8009A.attr preserve=no  implementation: static STRING_T {U} "Cfg"
STRING_T cResources::_ConfigPath = "Cfg";
//## end cResources::ConfigPath%3DE5D8A8009A.attr

//## begin cResources::DataPath%400D72190177.attr preserve=no  implementation: static STRING_T {U} "Data"
STRING_T cResources::_DataPath = "Data";
//## end cResources::DataPath%400D72190177.attr

//## begin cResources::AppDataPath%4219A20801D4.attr preserve=no  implementation: static STRING_T {U} "Internal"
STRING_T cResources::_AppDataPath = "Internal";
//## end cResources::AppDataPath%4219A20801D4.attr

//## begin cResources::ModelPath%400D7234032C.attr preserve=no  implementation: static STRING_T {U} "Model"
STRING_T cResources::_ModelPath = "Model";
//## end cResources::ModelPath%400D7234032C.attr

//## begin cResources::Process%3DD4B5820030.attr preserve=no  implementation: static cSHProcess * {U} NULL
cSHProcess *cResources::_Process = NULL;
//## end cResources::Process%3DD4B5820030.attr

//## begin cResources::Options%400E5C2D0213.attr preserve=no  implementation: static cOptions * {U} NULL
cOptions *cResources::_Options = NULL;
//## end cResources::Options%400E5C2D0213.attr

//## begin cResources::RefCount%3E70820B02FD.attr preserve=no  implementation: static ULONG_T {U} 0
ULONG_T cResources::_RefCount = 0;
//## end cResources::RefCount%3E70820B02FD.attr

//## begin cResources::Argc%3E70824D034B.attr preserve=no  implementation: static int {U} 0
int cResources::_Argc = 0;
//## end cResources::Argc%3E70824D034B.attr

//## begin cResources::Argv%3E7082630280.attr preserve=no  implementation: static char ** {U} NULL
char **cResources::_Argv = NULL;
//## end cResources::Argv%3E7082630280.attr

//## begin cResources::InstanceHandle%3E7082880203.attr preserve=no  implementation: static ULONG_T {U} 0
ULONG_T cResources::_InstanceHandle = 0;
//## end cResources::InstanceHandle%3E7082880203.attr

//## begin cResources::Log%4013D856002E.attr preserve=no  implementation: static BOOL_T {U} true
BOOL_T cResources::_Log = true;
//## end cResources::Log%4013D856002E.attr

//## begin cResources::DefaultLogFile%4060278B0251.attr preserve=no  implementation: static STRING_T {U} 
STRING_T cResources::_DefaultLogFile;
//## end cResources::DefaultLogFile%4060278B0251.attr

//## begin cResources::ErrorLogFile%422DD40102CE.attr preserve=no  implementation: static STRING_T {U} 
STRING_T cResources::_ErrorLogFile;
//## end cResources::ErrorLogFile%422DD40102CE.attr

//## begin cResources::FatalLogFile%4289B2B4000F.attr preserve=no  implementation: static STRING_T {U} 
STRING_T cResources::_FatalLogFile;
//## end cResources::FatalLogFile%4289B2B4000F.attr

//## begin cResources::Flags%42173E3300DA.attr preserve=no  implementation: static ULONG_T {U} 0
ULONG_T cResources::_Flags = 0;
//## end cResources::Flags%42173E3300DA.attr

cResources::cResources()
  //## begin cResources::cResources%.hasinit preserve=no
  //## end cResources::cResources%.hasinit
  //## begin cResources::cResources%.initialization preserve=yes
  //## end cResources::cResources%.initialization
{
  //## begin cResources::cResources%.body preserve=yes
_ASSERT_UNCOND
  //## end cResources::cResources%.body
}

cResources::cResources(const cResources &right)
  //## begin cResources::cResources%copy.hasinit preserve=no
  //## end cResources::cResources%copy.hasinit
  //## begin cResources::cResources%copy.initialization preserve=yes
  //## end cResources::cResources%copy.initialization
{
  //## begin cResources::cResources%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cResources::cResources%copy.body
}

cResources::cResources (int argc, char **argv)
  //## begin cResources::cResources%1047561050.hasinit preserve=no
  //## end cResources::cResources%1047561050.hasinit
  //## begin cResources::cResources%1047561050.initialization preserve=yes
  //## end cResources::cResources%1047561050.initialization
{
  //## begin cResources::cResources%1047561050.body preserve=yes
   cSystemUtils::SetMainThread();
   _Argc = argc;
	_Argv = argv;
   _Options = new cOptions(argc, argv);
	Initialize();
  //## end cResources::cResources%1047561050.body
}

cResources::cResources (ULONG_T h_inst, CONST_STRING_T cmd_line)
  //## begin cResources::cResources%1047561051.hasinit preserve=no
  //## end cResources::cResources%1047561051.hasinit
  //## begin cResources::cResources%1047561051.initialization preserve=yes
  //## end cResources::cResources%1047561051.initialization
{
  //## begin cResources::cResources%1047561051.body preserve=yes
	_InstanceHandle = h_inst;
	// generate _Argc and _Argv from cmd_line
_ASSERT_UNCOND
	Initialize();
  //## end cResources::cResources%1047561051.body
}


cResources::~cResources()
{
  //## begin cResources::~cResources%.body preserve=yes
  //## end cResources::~cResources%.body
}



//## Other Operations (implementation)
void cResources::EPrintf (CONST_STRING_T fmt_str, ... )
{
  //## begin cResources::EPrintf%1037286964.body preserve=yes
   // cObjectLock __lock__(&_LogMutex);
   // <-MW- 2005-04-20 Functionality moved to vEPrintf()
   va_list args;
   va_start(args, fmt_str);
   vEPrintf(fmt_str, args);
   va_end(args);
   // -MW->
  //## end cResources::EPrintf%1037286964.body
}

void cResources::IPrintf (CONST_STRING_T fmt_str, ... )
{
  //## begin cResources::IPrintf%1037286965.body preserve=yes
   // cObjectLock __lock__(&_LogMutex);
   // <-MW- 2005-04-20 Functionality moved to vEPrintf()
   va_list args;
   va_start(args, fmt_str);
   vIPrintf(fmt_str, args);
   va_end(args);
   // -MW->
  //## end cResources::IPrintf%1037286965.body
}

void cResources::FPrintf (CONST_STRING_T fmt_str, ... )
{
  //## begin cResources::FPrintf%1116319885.body preserve=yes
   va_list args;
   va_start(args, fmt_str);
   vFPrintf(fmt_str, args);
   va_end(args);
  //## end cResources::FPrintf%1116319885.body
}

STRING_T cResources::LogPath ()
{
  //## begin cResources::LogPath%1038473719.body preserve=yes
   return _LogPath;
  //## end cResources::LogPath%1038473719.body
}

STRING_T cResources::ConfigPath ()
{
  //## begin cResources::ConfigPath%1074625638.body preserve=yes
   return _ConfigPath;
  //## end cResources::ConfigPath%1074625638.body
}

STRING_T cResources::ModelPath ()
{
  //## begin cResources::ModelPath%1074625639.body preserve=yes
   return _ModelPath;
  //## end cResources::ModelPath%1074625639.body
}

STRING_T cResources::DataPath ()
{
  //## begin cResources::DataPath%1074625640.body preserve=yes
   return _DataPath;
  //## end cResources::DataPath%1074625640.body
}

STRING_T cResources::AppDataPath ()
{
  //## begin cResources::AppDataPath%1108976194.body preserve=yes
   return _AppDataPath;
  //## end cResources::AppDataPath%1108976194.body
}

BOOL_T cResources::IsArgsFileFound ()
{
   BOOL_T argsFileFound = false;
   if (_Options != NULL) {
      argsFileFound = _Options->IsArgsFileFound();
   }
   return argsFileFound;
}

void cResources::GetOption (CONST_STRING_T option_name, STRING_T &value)
{
  //## begin cResources::GetOption%1074682883.body preserve=yes
   if (_Options != NULL) {
      _Options->GetOption(option_name, value);
   }
  //## end cResources::GetOption%1074682883.body
}

void cResources::GetOption (CONST_STRING_T option_name, LONG_T &value)
{
  //## begin cResources::GetOption%1074682884.body preserve=yes
   if (_Options != NULL) {
      _Options->GetOption(option_name, value);
   }
  //## end cResources::GetOption%1074682884.body
}

void cResources::GetOption (CONST_STRING_T option_name, DOUBLE_T &value)
{
  //## begin cResources::GetOption%1074682885.body preserve=yes
   if (_Options != NULL) {
      _Options->GetOption(option_name, value);
   }
  //## end cResources::GetOption%1074682885.body
}

void cResources::GetOption (CONST_STRING_T option_name, BOOL_T &value)
{
  //## begin cResources::GetOption%1074682886.body preserve=yes
   if (_Options != NULL) {
      _Options->GetOption(option_name, value);
   }
  //## end cResources::GetOption%1074682886.body
}

INT_T cResources::Exit (INT_T exit_code, BOOL_T popup)
{
  //## begin cResources::Exit%1037286967.body preserve=yes
   try {
//      if (popup) {
      if (false) {
         char msg[0x200] = {0};
         SafePrintf(msg, sizeof(msg), "an unrecoverable error condition occured:%d", exit_code);
         cSystemUtils::MsgBox("system error", msg);
      }
      if (_Process != NULL) {
//         FatalPrintf("process %s shutdown ...\n", _Process->get_Name().c_str());
//         ShutDown();
         exit(exit_code);
      } else {
//         FatalPrintf("process exit\n");
         exit(exit_code);
      }
      return exit_code;
   } catch (...) {
//      FatalPrintf("process exit\n");
      exit(exit_code);
   }
  //## end cResources::Exit%1037286967.body
}

void cResources::ShutDown ()
{
  //## begin cResources::ShutDown%1037349735.body preserve=yes
   if (_Process != NULL) {
      _Process->Stop();
   } else {
      Exit(0, false);
   }
  //## end cResources::ShutDown%1037349735.body
}

void cResources::RegisterProcess (cSHProcess *process)
{
  //## begin cResources::RegisterProcess%1037349736.body preserve=yes
   _Process = process;
  //## end cResources::RegisterProcess%1037349736.body
}

BOOL_T cResources::ProcessTerminated ()
{
  //## begin cResources::ProcessTerminated%1108818875.body preserve=yes
#ifndef BASE_LIBRARY
   if (_Process != NULL) {
      return _Process->Terminated();
   }
#endif
   return false;
  //## end cResources::ProcessTerminated%1108818875.body
}

long __stdcall cResources::Filter (_EXCEPTION_POINTERS *exceptions)
{
  //## begin cResources::Filter%1037286968.body preserve=yes
#if defined(_WIN32)
#if defined(__MINGW32__)
PORT_LEVEL_5
   return 0;
#else
   PrintException(exceptions);
   return EXCEPTION_EXECUTE_HANDLER;
#endif
#elif defined(__linux__)
PORT_LEVEL_5
   return 0;
#else
NO_PLATFORM
#endif
  //## end cResources::Filter%1037286968.body
}

BOOL_T cResources::FlagSet (ULONG_T flag)
{
  //## begin cResources::FlagSet%1108819738.body preserve=yes
   if (flag < MAX_FLAGS) {
      return _Flags & (1 << flag);
   } else {
      return false;
   }
  //## end cResources::FlagSet%1108819738.body
}

void cResources::SetFlag (ULONG_T flag)
{
  //## begin cResources::SetFlag%1108819739.body preserve=yes
   if (flag < MAX_FLAGS) {
      _Flags |= (1 << flag);
   }
  //## end cResources::SetFlag%1108819739.body
}

void cResources::ResetFlag (ULONG_T flag)
{
  //## begin cResources::ResetFlag%1108819740.body preserve=yes
   if (flag < MAX_FLAGS) {
      _Flags &= ~(1 << flag);
   }
  //## end cResources::ResetFlag%1108819740.body
}

CONST_STRING_T cResources::GetVersion ()
{
  //## begin cResources::GetVersion%1121669292.body preserve=yes
   if (strlen(_ShaciraVersion) == 0) {
      SetVersion();
   }
   return _ShaciraVersion;
  //## end cResources::GetVersion%1121669292.body
}

void cResources::SetVersion ()
{
  //## begin cResources::SetVersion%1121668880.body preserve=yes
   SafePrintf(_ShaciraVersion, sizeof(_ShaciraVersion), "%d.%d.%d", SHACIRA_MAJOR, SHACIRA_MINOR, SHACIRA_BUG_FIX);
  //## end cResources::SetVersion%1121668880.body
}

void cResources::Initialize (CONST_STRING_T log_file)
{
  //## begin cResources::Initialize%1037286970.body preserve=yes
   SetVersion();
   GetOption("ConfigPath", _ConfigPath);
   GetOption("LogPath", _LogPath);
   GetOption("ModelPath", _ModelPath);
   GetOption("DataPath", _DataPath);
   GetOption("AppDataPath", _AppDataPath);
   GetOption("DefaultLanguage", _DefaultLanguage);
   SetFullPath(_ConfigPath);
   SetFullPath(_LogPath);
   SetFullPath(_ModelPath);
   SetFullPath(_DataPath);
   SetFullPath(_AppDataPath);
   _DefaultLogFile = cFileSystemUtils::AppendPath(_LogPath.c_str(), _LogFileName.c_str());
   _ErrorLogFile = cFileSystemUtils::BaseFileName(_DefaultLogFile.c_str());
   _ErrorLogFile += "Err.log";
   _ErrorLogFile = cFileSystemUtils::AppendPath(_LogPath.c_str(), _ErrorLogFile.c_str());
   _FatalLogFile = cFileSystemUtils::BaseFileName(_DefaultLogFile.c_str());
   _FatalLogFile += "FatalErr.log";
   _FatalLogFile = cFileSystemUtils::AppendPath(_LogPath.c_str(), _FatalLogFile.c_str());
   DEBUG_LOG()->assignIdToFile(0, _ErrorLogFile.c_str());
   DEBUG_LOG()->setLimits(0, _LogGenerations, _LogFileSize);
   DEBUG_LOG()->assignIdToFile(1, _DefaultLogFile.c_str());
   DEBUG_LOG()->setLimits(1, _LogGenerations, _LogFileSize);
   DEBUG_LOG()->assignIdToFile(2, _FatalLogFile.c_str());
   DEBUG_LOG()->setLimits(2, _LogGenerations, _LogFileSize);
  //## end cResources::Initialize%1037286970.body
}

void cResources::PrintException (_EXCEPTION_POINTERS *exceptions)
{
  //## begin cResources::PrintException%1037286969.body preserve=yes
#if defined(_WIN32)
#ifndef BASE_LIBRARY
   __TRY__ {
      cExceptionHnd::GenerateExceptionReport2(exceptions);
   } __EXCEPT__(EXCEPTION_EXECUTE_HANDLER) {
   }
#endif
#elif defined(__linux__)
PORT_LEVEL_5
#else
NO_PLATFORM
#endif
  //## end cResources::PrintException%1037286969.body
}

void cResources::SetFullPath (STRING_T &path)
{
  //## begin cResources::SetFullPath%1038473721.body preserve=yes
   path = cFileSystemUtils::FullPath(path.c_str());
  //## end cResources::SetFullPath%1038473721.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cResources::get_UseDebugLog ()
{
  //## begin cResources::get_UseDebugLog%4237147402FD.get preserve=no
  return _UseDebugLog;
  //## end cResources::get_UseDebugLog%4237147402FD.get
}

void cResources::set_UseDebugLog (BOOL_T value)
{
  //## begin cResources::set_UseDebugLog%4237147402FD.set preserve=no
  _UseDebugLog = value;
  //## end cResources::set_UseDebugLog%4237147402FD.set
}

ULONG_T cResources::get_LogGenerations ()
{
  //## begin cResources::get_LogGenerations%42305CB401A5.get preserve=no
  return _LogGenerations;
  //## end cResources::get_LogGenerations%42305CB401A5.get
}

void cResources::set_LogGenerations (ULONG_T value)
{
  //## begin cResources::set_LogGenerations%42305CB401A5.set preserve=no
  _LogGenerations = value;
  //## end cResources::set_LogGenerations%42305CB401A5.set
}

ULONG_T cResources::get_LogFileSize ()
{
  //## begin cResources::get_LogFileSize%42305CD30128.get preserve=no
  return _LogFileSize;
  //## end cResources::get_LogFileSize%42305CD30128.get
}

void cResources::set_LogFileSize (ULONG_T value)
{
  //## begin cResources::set_LogFileSize%42305CD30128.set preserve=no
  _LogFileSize = value;
  //## end cResources::set_LogFileSize%42305CD30128.set
}

STRING_T cResources::get_LogFileName ()
{
  //## begin cResources::get_LogFileName%4013D8330251.get preserve=no
  return _LogFileName;
  //## end cResources::get_LogFileName%4013D8330251.get
}

void cResources::set_LogFileName (STRING_T value)
{
  //## begin cResources::set_LogFileName%4013D8330251.set preserve=no
  _LogFileName = value;
  //## end cResources::set_LogFileName%4013D8330251.set
}

cConsole * cResources::get_DefaultConsole ()
{
  //## begin cResources::get_DefaultConsole%4060280E004E.get preserve=no
  return _DefaultConsole;
  //## end cResources::get_DefaultConsole%4060280E004E.get
}

void cResources::set_DefaultConsole (cConsole * value)
{
  //## begin cResources::set_DefaultConsole%4060280E004E.set preserve=no
  _DefaultConsole = value;
  //## end cResources::set_DefaultConsole%4060280E004E.set
}

STRING_T cResources::get_DefaultLanguage ()
{
  //## begin cResources::get_DefaultLanguage%4549BF39006D.get preserve=no
  return _DefaultLanguage;
  //## end cResources::get_DefaultLanguage%4549BF39006D.get
}

void cResources::set_DefaultLanguage (STRING_T value)
{
  //## begin cResources::set_DefaultLanguage%4549BF39006D.set preserve=no
  _DefaultLanguage = value;
  //## end cResources::set_DefaultLanguage%4549BF39006D.set
}

cSHProcess * cResources::get_Process ()
{
  //## begin cResources::get_Process%3DD4B5820030.get preserve=no
  return _Process;
  //## end cResources::get_Process%3DD4B5820030.get
}

cOptions * cResources::get_Options ()
{
  //## begin cResources::get_Options%400E5C2D0213.get preserve=no
  return _Options;
  //## end cResources::get_Options%400E5C2D0213.get
}

BOOL_T cResources::get_Log ()
{
  //## begin cResources::get_Log%4013D856002E.get preserve=no
  return _Log;
  //## end cResources::get_Log%4013D856002E.get
}

void cResources::set_Log (BOOL_T value)
{
  //## begin cResources::set_Log%4013D856002E.set preserve=no
  _Log = value;
  //## end cResources::set_Log%4013D856002E.set
}

// Additional Declarations
  //## begin cResources%3DD3BCC70122.declarations preserve=yes
  //## end cResources%3DD3BCC70122.declarations

//## begin module%3DD3BCC70122.epilog preserve=yes

// <-MW- 2005-04-19
void cResources::StoreLocation(const char *file, int line)
{
   _current_file = file;
   _current_line = line;
}

cResources::cPrint::cPrint(const char *file, int line)
{
   _current_file = file;
   _current_line = line;
}

void cResources::cPrint::Error (CONST_STRING_T fmt_str, ... )
{
   cResources::StoreLocation(_current_file, _current_line);
   
   va_list ap;
   va_start(ap, fmt_str);
   cResources::vEPrintf(fmt_str, ap);
   va_end(ap);
}

void cResources::cPrint::Info (CONST_STRING_T fmt_str, ... )
{
   cResources::StoreLocation(_current_file, _current_line);

   va_list ap;
   va_start(ap, fmt_str);
   cResources::vIPrintf(fmt_str, ap);
   va_end(ap);
}

void cResources::cPrint::FatalError (CONST_STRING_T fmt_str, ... )
{
#ifndef BASE_LIBRARY
   FILE * stream = NULL;
#if defined(_WIN32)
   const char * log_file = cExceptionHnd::GetLogFileName();
   if (stream == NULL &&
       log_file != NULL &&
       strlen(log_file) > 0) {
      stream = fopen(log_file, "a");
   }
#elif defined(__linux__)
PORT_LEVEL_5
   const char * log_file = "linux.log";
#else
NO_PLATFORM
#endif
   va_list ap;
   va_start(ap, fmt_str);
   try {
      _vsnprintf(_Text, sizeof(_Text)-1, fmt_str, ap);
      FILE * stream = NULL;
      if (stream == NULL) {
         stream = fopen(EXCEPTION_LOG_FILE_1, "a");
      }
      if (stream == NULL) {
         stream = fopen(EXCEPTION_LOG_FILE_2, "a");
      }
      if (stream != NULL) {
         fprintf(stream, "fatal error %stime\t\t\t%s", _Text, TimeText());
         fprintf(stream, "memory: %d objects %d\n", _VirtualMemory, _TransientObjects);
         fclose(stream);
      }
#if defined(_WIN32)
      MessageBox(0, _Text, "Fatal Error", MB_ICONSTOP);
#endif
   } catch (...) {
   }
   va_end(ap);
#endif
}

void cResources::vEPrintf (CONST_STRING_T fmt_str, va_list args)
{
   LOCK_WRITE_INFO
   try {
      _vsnprintf(_Text, sizeof(_Text)-1, fmt_str, args);
      cTimeObject t;
      char timestamp[256] = {0};
      SafePrintf(timestamp, sizeof(timestamp), "%s", (const char *)t);
      cSystemUtils::DebugConsolePrintf(_Text);
      if (_Log) {
         fprintf(stdout, "%s", _Text);
         if (_DefaultConsole != NULL) {
            _DefaultConsole->Write(_Text);
         }
         if (_UseDebugLog) {
            ULONG_T len = strlen(_Text);
            len = _MIN_(len,sizeof(_Text)-1);
            if (_Text[len-1] == '\n') {
               _Text[len-1] = 0;
            }
            // <-MW- 2005-04-19
            // DEBUG_LOG_TEXT(0, _Text);
            if (_current_file != 0) {
               cDebugLog::getInstance()->writeStatic( _current_file, _current_line, 0, _Text );
               _current_file = 0;
               _current_line = -1;
            } else {
               cDebugLog::getInstance()->writeStatic( "unknown", -1, 0, _Text );
            }
            // -MW->
         } else {
            if (_ErrorLogFile.size() > 0) {
               FILE * stream = fopen(_ErrorLogFile.c_str(), "a");
               if (stream != NULL) {
                  fprintf(stream, "E: %s: %s", timestamp, _Text);
                  fclose(stream);
               }
            }
         }
      }
   } catch (...) {
   }
}

void cResources::vIPrintf (CONST_STRING_T fmt_str, va_list args)
{
   LOCK_WRITE_INFO
   try {
      _vsnprintf(_Text, sizeof(_Text)-1, fmt_str, args);
      cTimeObject t;
      char timestamp[256] = {0};
      SafePrintf(timestamp, sizeof(timestamp), "%s", (const char *)t);
      if (_Log) {
         fprintf(stdout, "%s", _Text);
         if (_DefaultConsole != NULL) {
            _DefaultConsole->Write(_Text);
         }
         if (_UseDebugLog) {
            ULONG_T len = strlen(_Text);
            len = _MIN_(len,sizeof(_Text)-1);
            if (_Text[len-1] == '\n') {
               _Text[len-1] = 0;
            }
            // <-MW- 2005-04-19
            // DEBUG_LOG_TEXT(1, _Text);
            if (_current_file != 0) {
               cDebugLog::getInstance()->writeStatic( _current_file, _current_line, 1, _Text );
               _current_file = 0;
               _current_line = -1;
            } else {
               cDebugLog::getInstance()->writeStatic( "unknown", -1, 1, _Text );
            }
            // -MW->
         } else {
            if (_DefaultLogFile.size() > 0) {
               FILE * stream = fopen(_DefaultLogFile.c_str(), "a");
               if (stream != NULL) {
                  fprintf(stream, "I: %s: %s", timestamp, _Text);
                  fclose(stream);
               }
            }
         }
      }
   } catch (...) {
   }
}
// -MW->

void cResources::vFPrintf (CONST_STRING_T fmt_str, va_list args)
{
   LOCK_WRITE_INFO
   try {
      _vsnprintf(_Text, sizeof(_Text)-1, fmt_str, args);
      cTimeObject t;
      char timestamp[256] = {0};
      SafePrintf(timestamp, sizeof(timestamp), "%s", (const char *)t);
      cSystemUtils::DebugConsolePrintf(_Text);
      if (_Log) {
         fprintf(stdout, "%s", _Text);
         if (_DefaultConsole != NULL) {
            _DefaultConsole->Write(_Text);
         }
         if (_UseDebugLog) {
            ULONG_T len = strlen(_Text);
            len = _MIN_(len,sizeof(_Text)-1);
            if (_Text[len-1] == '\n') {
               _Text[len-1] = 0;
            }
            // <-MW- 2005-04-19
            // DEBUG_LOG_TEXT(0, _Text);
            if (_current_file != 0) {
               cDebugLog::getInstance()->writeStatic( _current_file, _current_line, 2, _Text );
               _current_file = 0;
               _current_line = -1;
            } else {
               cDebugLog::getInstance()->writeStatic( "unknown", -1, 2, _Text );
            }
            // -MW->
         } else {
            if (_ErrorLogFile.size() > 0) {
               FILE * stream = fopen(_ErrorLogFile.c_str(), "a");
               if (stream != NULL) {
                  fprintf(stream, "E: %s: %s", timestamp, _Text);
                  fclose(stream);
               }
            }
         }
      }
   } catch (...) {
   }
}

//## end module%3DD3BCC70122.epilog
