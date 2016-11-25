
#ifndef __linux__

// ===========================================================================
// base/process.cpp                                             ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
//
// ===========================================================================


// Interface header
#include "base/process.h"

// Other ECL headers
#include "base/string.h"

// Platform dependant headers
#if defined __ECL_OS2__
   #define INCL_PM
   #define INCL_NLS
   #define INCL_BASE
   #define INCL_DOSPROCESS
   #include <os2.h>
#elif defined __ECL_W32__
   #include <process.h>
   #include <windows.h>
   #include "base/system/enum_procs.h"
#endif

         
         

namespace ecl {


// ===========================================================================
// Private data
// ===========================================================================

struct cProcess::cPrivate {
   #if defined __ECL_W32__
      cPrivate() {
         _hnd_process = _hnd_thread = 0;
         _process_id = _thread_id = 0;
      }
      HANDLE _hnd_process;
      HANDLE _hnd_thread;
      int _process_id;
      int _thread_id;
   #endif
};


// ===========================================================================
// Construction/Destruction/Copying
// ===========================================================================

cProcess::cProcess() :
   _start_options(0),
   _data(new cPrivate)
{
   __ECL_STATISTIC__("cProcess")
}

cProcess::cProcess(const cString& exe_name, const cString& params) :
   _start_options(0),
   _data(new cPrivate)
{
   __ECL_STATISTIC__("cProcess(exe)")
   start(exe_name, params);
}

cProcess::~cProcess()
{
   #if defined __ECL_W32__
      if ( _data->_hnd_process != 0 )
         CloseHandle(_data->_hnd_process);
      if ( _data->_hnd_thread != 0 )
         CloseHandle(_data->_hnd_thread);
   #endif

   delete _data;
}


// ===========================================================================
// Process management
// ===========================================================================

bool cProcess::start(const cString& exe_name, const cString& params)
{
   bool ok = false;

   #if defined __ECL_W32__

      cString cmd_line_str = "\"" + exe_name + "\" " + params;
      char *cmd_line = (char *)cmd_line_str.ccp();
      PROCESS_INFORMATION process_info;

      STARTUPINFO startup_info;
      memset(&startup_info, 0, sizeof startup_info);
      startup_info.cb = sizeof startup_info;

      if ( getStartOptions() & startMinimized ) {
         startup_info.dwFlags |= STARTF_USESHOWWINDOW;
         startup_info.wShowWindow |= SW_SHOWMINIMIZED;
      } else if ( getStartOptions() & startMaximized ) {
         startup_info.dwFlags |= STARTF_USESHOWWINDOW;
         startup_info.wShowWindow |= SW_SHOWMAXIMIZED;
      }

      ok = !!CreateProcess(
         0,                            // lpApplicationName
         cmd_line,                     // lpCommandLine
         0,                            // lpProcessAttributes
         0,                            // lpThreadAttributes
         FALSE,                        // bInheritHandles
         0,                            // dwCreationFlags
         0,                            // lpEnvironment
         0,                            // lpCurrentDirectory
         &startup_info,                // lpStartupInfo
         &process_info                 // lpProcessInformation
      );

      if ( __ECL_ASSERT_PRINTF__(ok, cBase::dbgError|cBase::dbgIpc|cBase::dbgAssert, ("Could not start process '%s', cause = %d", exe_name, GetLastError())) ) {
         _data->_hnd_process = process_info.hProcess;
         _data->_hnd_thread  = process_info.hThread;
         _data->_process_id  = process_info.dwProcessId;
         _data->_thread_id   = process_info.dwThreadId;
      }

   #endif

   return ok;
}

/**
 * Starts a process and waits until it's completion.
 * 
 * \return Returns the exit code of the called process or -1 if the
 *         process could not be started.
 */
int cProcess::call(const cString& exe_name, const cString& params)
{
   if ( !start(exe_name, params) || !waitFor() ) {
      return -1;
   } else {
      return getExitCode();
   }
}

bool cProcess::kill(int exit_code)
{
   bool ok = false;

   #if defined __ECL_W32__
      ok = !!TerminateProcess(_data->_hnd_process, exit_code);
      __ECL_ASSERT_PRINTF__(ok, cBase::dbgError|cBase::dbgIpc|cBase::dbgAssert, ("Could not terminate process ID %d (0x%08x), cause = %d", _data->_process_id, _data->_hnd_process, GetLastError()));
   #endif

   return ok;
}

bool cProcess::waitFor(PROCESS_EVENT event, int timeout)
{
   switch ( event ) {
      case peNone:
         return true;
      case peStart:
         __ECL_ASSERT_PRINTF__(false, cBase::dbgError|cBase::dbgIpc|cBase::dbgAssert, ("Unimplemented feature: waitFor(peStart)"));
         break;
      case peEnd:
         {
            DWORD rc = WaitForSingleObject(_data->_hnd_process, timeout < 0 ? INFINITE : timeout);
            return rc == WAIT_OBJECT_0;
         }
      default:
         break;
   }

   return false;
}



// ===========================================================================
// Find processes
// ===========================================================================


/**
 * Tries to find a process by it's process ID.
 *
 * \return Returns a Pointer to a newly allocated cProcess object or 0, if
 *         process could not be found. This object must be deleted by the caller.
 * \param  proc_id  ID of process to be found
 */
cProcess * cProcess::findProcessById(unsigned long proc_id)
{
   HANDLE proc_hnd = ::OpenProcess(STANDARD_RIGHTS_REQUIRED, FALSE, proc_id);
   cProcess *proc = 0;

   if ( proc_hnd != 0 ) {
      proc = new cProcess;
      proc->_data->_process_id = proc_id;
      proc->_data->_hnd_process = proc_hnd;
   }

   return proc;
}


/**
 * Helper for findProcessByName
 */
struct FIND_PROCESS_PARAM { DWORD _pid; cString _name; };
static BOOL CALLBACK FindProcessCallback(DWORD pid, WORD, LPSTR name, LPARAM param)
{
   FIND_PROCESS_PARAM *fp_param = (FIND_PROCESS_PARAM*)param;
   if ( cString(name).getUpcase().endsWith(fp_param->_name) ) {
      fp_param->_pid = pid;
      return FALSE;
   }
   return TRUE;
}


/**
 * Tries to find a process by it's name.
 *
 * \return Returns a Pointer to a newly allocated cProcess object or 0, if
 *         process could not be found. This object must be deleted by the caller.
 * \param  proc_name  Name of process to be found. This name is matched against
 *                    the full path name of the project's executable file. When
 *                    an incomplete path is given, the process' path name must end
 *                    with \a proc_name for the match to become true.
 */
cProcess * cProcess::findProcessByName(const cString& proc_name)
{
// PR GNUC
   #if defined __GNUC__
   return 0;
   #else
   FIND_PROCESS_PARAM param;
   param._pid = 0;
   param._name = proc_name.getUpcase();

   EnumProcs(FindProcessCallback, (LPARAM)&param);

   cProcess *proc = 0;

   if ( param._pid != 0 ) {
      proc = new cProcess;
      proc->_data->_process_id = param._pid;
      proc->_data->_hnd_process = ::OpenProcess(PROCESS_DUP_HANDLE|PROCESS_QUERY_INFORMATION|SYNCHRONIZE, FALSE, param._pid);
   }

   return proc;
   #endif
// PR GNUC
}


/**
 * Helper for findProcessByWindowTitle
 */
struct FIND_WINDOW_PARAM { HWND _hwnd; cString _title; };
static BOOL CALLBACK FindWindowCallback(HWND hwnd, LPARAM param)
{
   FIND_WINDOW_PARAM *fw_param = (FIND_WINDOW_PARAM*)param;
   char title_buf[256]; GetWindowText(hwnd, title_buf, sizeof title_buf);
   cString title = cString(title_buf).getUpcase();

   if ( fw_param->_title.startsWith("*") ) {
      if ( fw_param->_title.endsWith("*") ) {
         if ( title.contains(fw_param->_title.getMid(1, fw_param->_title.getLength() - 2)) ) {
            fw_param->_hwnd = hwnd;
            return FALSE;
         }
      } else {
         if ( title.endsWith(fw_param->_title.delRight(1)) ) {
            fw_param->_hwnd = hwnd;
            return FALSE;
         }
      }
   } else if ( fw_param->_title.endsWith("*") ) {
      if ( title.startsWith(fw_param->_title.delLeft(1)) ) {
         fw_param->_hwnd = hwnd;
         return FALSE;
      }
   } else {
      if ( cString(title).getUpcase() == fw_param->_title ) {
         fw_param->_hwnd = hwnd;
         return FALSE;
      }
   }

   return TRUE;
}


/**
 * Tries to find a process by looking at the window titles.
 *
 * \return Returns a Pointer to a newly allocated cProcess object or 0, if
 *         process could not be found. This object must be deleted by the caller.
 * \param  title         Name of process to be found
 * \param  desktop_only  true if only top level windows should be found
 */
cProcess * cProcess::findProcessByWindowTitle(const cString& title, bool desktop_only)
{
   FIND_WINDOW_PARAM param;
   param._hwnd = 0;
   param._title = title.getUpcase();

   if ( desktop_only ) {
      EnumDesktopWindows(0, FindWindowCallback, (LPARAM)&param);
   } else {
      EnumWindows(FindWindowCallback, (LPARAM)&param);
   }

   cProcess *proc = 0;

   if ( param._hwnd != 0 ) {
      DWORD proc_id = 0;
      proc = new cProcess;
      proc->_data->_thread_id = GetWindowThreadProcessId(param._hwnd, &proc_id);
      proc->_data->_process_id = proc_id;
      proc->_data->_hnd_process = ::OpenProcess(PROCESS_DUP_HANDLE|PROCESS_QUERY_INFORMATION|SYNCHRONIZE, FALSE, proc_id);
   }

   return proc;
}



// ===========================================================================
// Exit code
// ===========================================================================


bool cProcess::isActive() const
{
   #if defined __ECL_W32__
      DWORD exit_code = 0;
      if ( _data->_hnd_process == 0 || !GetExitCodeProcess(_data->_hnd_process, &exit_code) )
         return false;
      return exit_code == STILL_ACTIVE;
   #else
      return 0;
   #endif
}

int cProcess::getExitCode() const
{
   #if defined __ECL_W32__
      DWORD exit_code = 0;
      if ( _data->_hnd_process == 0 || !GetExitCodeProcess(_data->_hnd_process, &exit_code) )
         return -1;
      return exit_code;
   #else
      return 0;
   #endif
}


}; // namespace ecl

#endif
