

#include "FirstHeader.h"
#include "System/Process/cOptions.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Config/cConfiguration.h"
#include "System/Config/cConfigurationObject.h"
#include "Orb/cBroker.h"
#include "System/Sys/cSockets.h"
#include "System/Console/cStandardConsole.h"
#include "System/Console/cMemoryConsole.h"
#include "System/Console/cSocketConsole.h"
#include "Apps/ChannelMgr/cEventChannelManager.h"
#ifdef __BLCPP__
#include <dir.h>
#else
#include <direct.h>
#endif

// Ctrl + x handler
BOOL WINAPI CtrlHandler(DWORD dwCtrlType)
{
   switch (dwCtrlType) {
   case CTRL_C_EVENT:
      InfoPrintf("CTRL+C\n");
      cResources::ShutDown();
      break;
   case CTRL_BREAK_EVENT:
      InfoPrintf("CTRL+BREAK\n");
      break;
   case CTRL_CLOSE_EVENT:
      InfoPrintf("CTRL+CLOSE\n");
      break;
   case CTRL_LOGOFF_EVENT:
      InfoPrintf("CTRL+LOGOFF\n");
      break;
   case CTRL_SHUTDOWN_EVENT:
      InfoPrintf("CTRL+SHUTDOWN\n");
      cResources::ShutDown();
      break;
   }
   return true;
}

int ChannelMgr(int argc, char* argv[])
{
MAINFUNC_PROLOG("TestProcess")
   try {
		cSockets::Initialize();
		cBroker::Initialize();
      cResources resources(argc, argv);
      STRING_T config_file_name = "test.cfg";
      STRING_T log_file_name = "Log/test.log";
      STRING_T root_name = "ChannelManager";
      cOptions options("-w-c-r-l", argc, argv);
      if (options.OptionSet("-w")) {
         chdir(options.Option("-w").c_str());
      }
      if (options.OptionSet("-c")) {
         config_file_name = options.Option("-c").c_str();
      }
      if (options.OptionSet("-r")) {
         root_name = options.Option("-r").c_str();
         log_file_name = cFileSystemUtils::AppendPath("Log", root_name.c_str()).c_str();
         log_file_name += ".log";
      }
      if (options.OptionSet("-l")) {
         log_file_name = options.Option("-l").c_str();
      }
      cConfiguration * config = NULL;
      try {
         config = new cConfiguration(cConfiguration::DefaultConfigFile());
      } catch (cError & e) {
         ErrorPrintf("%s\n", (const char *)e);
         return -9;
      }
      cConfigurationObject * process_obj = config->Object(root_name.c_str());
      if (process_obj != NULL) {
         log_file_name = cFileSystemUtils::AppendPath("Log", process_obj->get_Name().c_str());
         log_file_name += ".log";
         cResources::SetLogFile(log_file_name.c_str());
         cEventChannelManager process(process_obj);
         process.set_Path(argv[0]);
         process.StartUp();
         cResources::RegisterProcess(&process);
         SetConsoleCtrlHandler(CtrlHandler, true);
         while (!process.get_ShutDownRequest()) {
            cSystemUtils::Suspend(100);
         }
         return 0;
      } else {
         fprintf(stderr, "Root object %s not found\n", root_name.c_str());
         return -1;
      }
   } catch (InvalidOption & o) {
      ErrorPrintf("Invalid Option %s\n", o.GetOption());
      return -10;
   } catch (cError & e) {
      ErrorPrintf("%s\n", (const char*) e);
      return -11;
   } catch (...) {
      ErrorPrintf("Unhandled exception in main Thread\n");
      return -12;
   }
MAINFUNC_EPILOG
}


#ifdef __MSCPP__

int main(int argc, char* argv[])
{
   return ChannelMgr(argc, argv);
}

#endif
