
#include "FirstHeader.h"
#include "System/Process/cOptions.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Process/cSHProcess.h"
#include "System/Config/cConfiguration.h"
#include "System/Config/cConfigurationObject.h"
#include "Orb/cBroker.h"
#include "System/Sys/cSockets.h"
#include "System/Console/cStandardConsole.h"
#include "System/Console/cMemoryConsole.h"
#include "System/Console/cSocketConsole.h"
#include "System/Objects/cInfo.h"
#include "Control/CellProcess/cCellProcess.h"

#if defined(_WIN32)

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

#endif

int CCS(int argc, char* argv[])
{
MAINFUNC_PROLOG("CCS")
   try {
      cResources resources(argc, argv);
		cSockets::Initialize();
		cBroker::Initialize();
      cConfiguration * config = NULL;
      try {
         STRING_T config_file = cFileSystemUtils::AppendPath(cResources::ConfigPath().c_str(),
                                                                  cConfiguration::DefaultConfigFile());
         config = new cConfiguration(config_file.c_str());
      } catch (cError & e) {
         ErrorPrintf("%s\n", (const char *)e);
         return -9;
      }
      STRING_T root_name = "LocalProcess";
      cResources::GetOption("RootName", root_name);
      cConfigurationObject * process_obj = config->Object(root_name.c_str());
      if (process_obj != NULL) {
         cCellProcess process(process_obj);
         process.set_Path(argv[0]);
   		process.Start();
         cResources::RegisterProcess(&process);
#if defined(_WIN32)
         SetConsoleCtrlHandler(CtrlHandler, true);
#endif
         while (!process.Terminated()) {
            cSystemUtils::Suspend(1000);
         }
      } else {
         ErrorPrintf("Root object %s not found\n", root_name.c_str());
      }
      return 0;
   } catch (cError & e) {
      ErrorPrintf("%s\n", (const char*) e);
      return -11;
   } catch (...) {
      ErrorPrintf("unhandled exception in main thread\n");
      return -12;
   }
MAINFUNC_EPILOG
}

int main(int argc, char* argv[])
{
   return CCS(argc, argv);
}
