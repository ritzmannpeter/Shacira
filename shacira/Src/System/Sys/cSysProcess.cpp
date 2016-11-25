//## begin module%3AE83FE50190.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AE83FE50190.cm

//## begin module%3AE83FE50190.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AE83FE50190.cp

//## Module: cSysProcess%3AE83FE50190; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSysProcess.cpp

//## begin module%3AE83FE50190.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3AE83FE50190.additionalIncludes

//## begin module%3AE83FE50190.includes preserve=yes

#if defined(_WIN32)
#include <process.h>
#endif

//## end module%3AE83FE50190.includes

// cSysProcess
#include "System/Sys/cSysProcess.h"
//## begin module%3AE83FE50190.additionalDeclarations preserve=yes
//## end module%3AE83FE50190.additionalDeclarations


// Class cSysProcess 








cSysProcess::cSysProcess()
  //## begin cSysProcess::cSysProcess%.hasinit preserve=no
      : _Pid(0), _AutoTerminate(false), _ProcessHandle(NULL), _ThreadHandle(NULL)
  //## end cSysProcess::cSysProcess%.hasinit
  //## begin cSysProcess::cSysProcess%.initialization preserve=yes
  //## end cSysProcess::cSysProcess%.initialization
{
  //## begin cSysProcess::cSysProcess%.body preserve=yes
  //## end cSysProcess::cSysProcess%.body
}

cSysProcess::cSysProcess(const cSysProcess &right)
  //## begin cSysProcess::cSysProcess%copy.hasinit preserve=no
      : _Pid(0), _AutoTerminate(false), _ProcessHandle(NULL), _ThreadHandle(NULL)
  //## end cSysProcess::cSysProcess%copy.hasinit
  //## begin cSysProcess::cSysProcess%copy.initialization preserve=yes
  //## end cSysProcess::cSysProcess%copy.initialization
{
  //## begin cSysProcess::cSysProcess%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSysProcess::cSysProcess%copy.body
}

cSysProcess::cSysProcess (BOOL_T auto_terminate)
  //## begin cSysProcess::cSysProcess%1171392475.hasinit preserve=no
      : _Pid(0), _AutoTerminate(false), _ProcessHandle(NULL), _ThreadHandle(NULL)
  //## end cSysProcess::cSysProcess%1171392475.hasinit
  //## begin cSysProcess::cSysProcess%1171392475.initialization preserve=yes
  //## end cSysProcess::cSysProcess%1171392475.initialization
{
  //## begin cSysProcess::cSysProcess%1171392475.body preserve=yes
   _AutoTerminate = auto_terminate;
  //## end cSysProcess::cSysProcess%1171392475.body
}


cSysProcess::~cSysProcess()
{
  //## begin cSysProcess::~cSysProcess%.body preserve=yes
   if (_AutoTerminate) {
      Terminate();
   }
#if defined(_WIN32)
   if (_ProcessHandle != NULL) {
      CloseHandle(_ProcessHandle);
      _ProcessHandle = NULL;
   }
   if (_ThreadHandle != NULL) {
      CloseHandle(_ThreadHandle);
      _ThreadHandle = NULL;
   }
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
  //## end cSysProcess::~cSysProcess%.body
}



//## Other Operations (implementation)
BOOL_T cSysProcess::Create (CONST_STRING_T name, CONST_STRING_T args)
{
  //## begin cSysProcess::Create%988300376.body preserve=yes
#if defined(_WIN32)
   __TRY__ {
      if (_ProcessHandle != NULL) {
         CloseHandle(_ProcessHandle);
         _ProcessHandle = NULL;
      }
      if (_ThreadHandle != NULL) {
         CloseHandle(_ThreadHandle);
         _ThreadHandle = NULL;
      }
      STARTUPINFO suinfo = {0};
      PROCESS_INFORMATION pinfo = {0};
      _Name = name;
      if (args != NULL) _Args += args;
      char command[512] = {0};
      SafePrintf(command, sizeof(command),"%s %s", _Name.c_str(), _Args.c_str());
      suinfo.cb = sizeof(suinfo);
      int err = 0;
      BOOL_T success = (BOOL_T)CreateProcess(_Name.c_str(),
                                             command,
                                             NULL,
                                             NULL,
                                             false,
                                             CREATE_NO_WINDOW,
                                             NULL,
                                             NULL,
                                             &suinfo,
                                             &pinfo);
      if (success) {
         _ProcessHandle = pinfo.hProcess;
         _ThreadHandle = pinfo.hThread;
         return true;
      } else {
         err = GetLastError();
         InfoPrintf("Failed to create process %s %d\n", name, err);
         return false;
      }
   } __EXCEPT__(EXCEPTION_EXECUTE_HANDLER) {
      InfoPrintf("Failed to create process%s fatal\n", name);
      return false;
   }
   return false;
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
  //## end cSysProcess::Create%988300376.body
}

BOOL_T cSysProcess::Spawn (CONST_STRING_T name, CONST_STRING_T args)
{
  //## begin cSysProcess::Spawn%988306473.body preserve=yes
   __TRY__ {
      int pid = -1;
      _Name = name;
      if (args != NULL) _Args += args;
      try {
#if defined(_WIN32)
         pid = spawnlp(P_NOWAIT, name, name, args, NULL);
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
         if (pid > 0) {
            _Pid = pid;
            return true;
         } else {
            InfoPrintf("Failed to start process %s %d\n", name, GetLastError());
            return false;
         }
      } catch (...) {
         InfoPrintf("Failed to spawn process %s exception\n", name);
         return false;
      }
   } __EXCEPT__(EXCEPTION_EXECUTE_HANDLER) {
      InfoPrintf("Failed to spawn process %s fatal\n", name);
      return false;
   }
  //## end cSysProcess::Spawn%988306473.body
}

BOOL_T cSysProcess::Execute (int &exit_code, CONST_STRING_T name, CONST_STRING_T args)
{
  //## begin cSysProcess::Execute%1171386482.body preserve=yes
#if defined(_WIN32)
   __TRY__ {
      if (_ProcessHandle != NULL) {
         CloseHandle(_ProcessHandle);
         _ProcessHandle = NULL;
      }
      if (_ThreadHandle != NULL) {
         CloseHandle(_ThreadHandle);
         _ThreadHandle = NULL;
      }
      exit_code = -1;
      STARTUPINFO suinfo = {0};
      PROCESS_INFORMATION pinfo = {0};
      _Name = name;
      if (args != NULL) _Args += args;
      char command[512] = {0};
      SafePrintf(command, sizeof(command), "%s %s", _Name.c_str(), _Args.c_str());
      suinfo.cb = sizeof(suinfo);
      int err = 0;
      BOOL_T success = (BOOL_T)CreateProcess(_Name.c_str(),
                                             command,
                                             NULL,
                                             NULL,
                                             false,
                                             CREATE_NO_WINDOW,
                                             NULL,
                                             NULL,
                                             &suinfo,
                                             &pinfo);
      if (success) {
         _Pid = pinfo.dwProcessId;
         _ProcessHandle = pinfo.hProcess;
         _ThreadHandle = pinfo.hThread;
         DWORD ecode = STILL_ACTIVE;
         BOOL_T success = false;
         while (ecode == STILL_ACTIVE) {
            cSystemUtils::Suspend(20);
            success = GetExitCodeProcess(_ProcessHandle, &ecode);
            if (success == false) {
               return false;
            }
         }
         exit_code = ecode;
         _AutoTerminate = false;
         return true;
      } else {
         err = GetLastError();
         InfoPrintf("Failed to create process %s %d\n", name, err);
         return false;
      }
   } __EXCEPT__(EXCEPTION_EXECUTE_HANDLER) {
      InfoPrintf("Failed to create process%s fatal\n", name);
      return false;
   }
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
  //## end cSysProcess::Execute%1171386482.body
}

BOOL_T cSysProcess::Terminate ()
{
  //## begin cSysProcess::Terminate%988300377.body preserve=yes
   __TRY__ {
      BOOL_T success = true;
      int err = 0;
      if (_ProcessHandle != NULL) {
#if defined(_WIN32)
         success = (BOOL_T)TerminateProcess(_ProcessHandle, 0);
         if (success) {
            CloseHandle(_ProcessHandle);
            _ProcessHandle = NULL;
            if (_ThreadHandle != NULL) {
               CloseHandle(_ThreadHandle);
               _ThreadHandle = NULL;
            }
            return true;
         } else {
            err = GetLastError();
            InfoPrintf("Failed to terminate process %p %d\n", _ProcessHandle, err);
            return false;
         }
#elif defined(__linux__)
PORT_LEVEL_3
#else
NO_PLATFORM
#endif
      }
      return success;
   } __EXCEPT__(EXCEPTION_EXECUTE_HANDLER) {
      InfoPrintf("Failed to terminate process %p fatal\n", _ProcessHandle);
      return false;
   }
  //## end cSysProcess::Terminate%988300377.body
}

//## Get and Set Operations for Class Attributes (implementation)

INT_T cSysProcess::get_Pid () const
{
  //## begin cSysProcess::get_Pid%3AE8408B03D4.get preserve=no
  return _Pid;
  //## end cSysProcess::get_Pid%3AE8408B03D4.get
}

BOOL_T cSysProcess::get_AutoTerminate () const
{
  //## begin cSysProcess::get_AutoTerminate%45D2075101C5.get preserve=no
  return _AutoTerminate;
  //## end cSysProcess::get_AutoTerminate%45D2075101C5.get
}

void cSysProcess::set_AutoTerminate (BOOL_T value)
{
  //## begin cSysProcess::set_AutoTerminate%45D2075101C5.set preserve=no
  _AutoTerminate = value;
  //## end cSysProcess::set_AutoTerminate%45D2075101C5.set
}

// Additional Declarations
  //## begin cSysProcess%3AE83FE50190.declarations preserve=yes
  //## end cSysProcess%3AE83FE50190.declarations

//## begin module%3AE83FE50190.epilog preserve=yes
//## end module%3AE83FE50190.epilog
