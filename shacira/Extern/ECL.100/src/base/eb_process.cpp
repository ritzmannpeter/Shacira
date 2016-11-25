// ===========================================================================
// eb_process.cpp                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cBase
//     |
//     +-cProcess         -
//
// ===========================================================================

#include "base/eb_process.hpp"
#include "base/eb_str.hpp"

#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #define INCL_DOSPROCESS
   #include <os2.h>
#elif defined __ECL_W32__
   #include <process.h>
   #include <windows.h>
#endif




#ifdef __INTERFACE__

// Headerfiles
// ===========================================================================

#include "base/eb_thread.hpp"

#endif /*__INTERFACE__*/




#ifdef __INTERFACE__

// ===========================================================================
// cProcess
// ---------------------------------------------------------------------------
//
// cBase
//  +--cProcess
//
// ===========================================================================

class __ECL_DLLEXPORT__ cProcess : public cBase {

public:

   // Konstruiere Prozess-Objekt (anlegen mit Create)
   cProcess();
   // Konstruiere Standard-Prozess-Objekt (kann sofort gestartet werden)
   cProcess(const char *exe_name, const char *params = 0);
   // Destruktor
   ~cProcess();

   // Prozess starten
   bool start(const char *exe_name, const char *params = 0);
   // Thread starten ohne Parameteruebergabe
   bool kill(int exit_code = 0);

private:

   #if defined __ECL_OS2__
      // ???
   #elif defined __ECL_W32__
      void *hnd_process;
      void *hnd_thread;
      int process_id;
      int thread_id;
   #endif

};

#endif /*__INTERFACE__*/


// Implementierung cProcess
// ===========================================================================

cProcess::cProcess()
{
   #if defined __ECL_W32__
      hnd_process = 0; hnd_thread = 0;
      process_id = 0; thread_id = 0;
   #endif
}

cProcess::cProcess(const char *exe_name, const char *params)
{
   #if defined __ECL_W32__
      hnd_process = 0; hnd_thread = 0;
      process_id = 0; thread_id = 0;
   #endif

   start(exe_name, params);
}

cProcess::~cProcess()
{
   #if defined __ECL_W32__
      if ( hnd_process != 0 )
         CloseHandle((HANDLE)hnd_process);
      if ( hnd_thread != 0 )
         CloseHandle((HANDLE)hnd_thread);
   #endif
}

bool cProcess::start(const char *exe_name, const char *params)
{
   bool ok = false;

   #if defined __ECL_W32__

      cString cmd_line_str = cString(exe_name) + " " + params;
      char *cmd_line = (char *)(const char *)cmd_line_str;
      PROCESS_INFORMATION process_info;

      STARTUPINFO startup_info;
      memset(&startup_info, 0, sizeof startup_info);
      startup_info.cb = sizeof startup_info;

      ok = !!CreateProcess(
         exe_name,                     // lpApplicationName
         cmd_line,                     // lpCommandLine
         NULL,                         // lpProcessAttributes
         NULL,                         // lpThreadAttributes
         FALSE,                        // bInheritHandles
         0,                            // dwCreationFlags
         NULL,                         // lpEnvironment
         NULL,                         // lpCurrentDirectory
         &startup_info,                // lpStartupInfo
         &process_info                 // lpProcessInformation
      );

      if ( __ECL_ASSERT2__(ok, ("Could not start process '%s', cause = %d", exe_name, GetLastError())) ) {
         hnd_process = process_info.hProcess;
         hnd_thread  = process_info.hThread;
         process_id  = process_info.dwProcessId;
         thread_id   = process_info.dwThreadId;
      }

   #endif

   return ok;
}

bool cProcess::kill(int exit_code)
{
   bool ok = false;

   #if defined __ECL_W32__
      ok = !!TerminateProcess(hnd_process, exit_code);
      __ECL_ASSERT2__(ok, ("Could not terminate process ID %d (0x%08x), cause = %d", process_id, hnd_process, GetLastError()));
   #endif

   return ok;
}

