// ===========================================================================
// base/process.h                                               ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// Dieses Modul stellt die folgenden Klassen zur Verfuegung:
//
//    cProcess
//
// ===========================================================================

#ifndef __ecl_process__
#define __ecl_process__


// Other ECL headers
#include "base/thread.h"


namespace ecl {


// ===========================================================================
// cProcess
// ===========================================================================

class __ECL_DLLEXPORT__ cProcess {

// ------------------------------------
// Construction/Destruction/Copying
// ------------------------------------
public:

   //! Create default process object
   cProcess();
   //! Create process object and start process immediately
   cProcess(const cString& exe_name, const cString& params = 0);
   //! Destroy process object
   ~cProcess();


// ------------------------------------
// Process management
// ------------------------------------
public:

   //! Possible process events
   enum PROCESS_EVENT {
      peNone,           //!< No event (do not wait)
      peStart,          //!< Process started
      peEnd             //!< Process terminated
   };

   //! Starts a process
   bool start(const cString& exe_name, const cString& params = 0);
   //! Starts a process and waits until it's completion
   int call(const cString& exe_name, const cString& params = 0);
   //! Kills the process
   bool kill(int exit_code = 0);
   //! Wait for a process event
   bool waitFor(PROCESS_EVENT event = peEnd, int timeout = -1);


// ------------------------------------
// Find processes
// ------------------------------------
public:

   // Tries to find a process by it's process ID
   static cProcess *findProcessById(unsigned long proc_id);
   // Tries to find a process by it's name
   static cProcess *findProcessByName(const cString& proc_name);
   // Tries to find a process by looking at the window titles
   static cProcess *findProcessByWindowTitle(const cString& title, bool desktop_only = true);


// ------------------------------------
// Start options
// ------------------------------------
public:

   //! Specifies the possible start options
   enum START_OPTIONS {
      startMinimized    = (1 << 0),    //!< Start with minimized window
      startMaximized    = (1 << 1)     //!< Start with maximized window
   };

   //! Sets options used when starting a process
   inline void setStartOptions(int options)
      { _start_options |= options; }
   //! Returns options used when starting a process
   inline int getStartOptions() const
      { return _start_options; }


// ------------------------------------
// Exit code
// ------------------------------------
public:

   //! Returns true if the process is currently active
   bool isActive() const;
   //! Returns the exit code of the process
   int getExitCode() const;


// ------------------------------------
// Attributes
// ------------------------------------
private:
   // Copying is not allowed!
   cProcess(const cProcess &other);
   cProcess &operator=(const cProcess &other);

   int _start_options;

   struct cPrivate;
   cPrivate *_data;

};


}; // namespace ecl


#endif // __ecl_process__

