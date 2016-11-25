

#include "FirstHeader.h"
#include "System/cOptions.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Config/cConfiguration.h"
#include "System/Config/cConfigurationObject.h"
#include "cInstall.h"

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

int Installer(int argc, char* argv[])
{
   try {
      STRING_T config_file_name = "cfg/Shacira.cfg";
      cOptions options("-w", argc, argv);
      if (options.OptionSet("-w")) {
         chdir(options.Option("-w").c_str());
      }
      cConfiguration * config = NULL;
      try {
         config = new cConfiguration(config_file_name.c_str());
         cConfigurationObject * vol_obj = config->Object("Volume");
      } catch (cError & e) {
         printf("%s\n", (const char *)e);
         return -9;
      }
      return 0;
   } catch (InvalidOption & o) {
      printf("Invalid Option %s\n", o.GetOption());
      return -10;
   } catch (cError & e) {
      printf("%s\n", (const char*) e);
      return -11;
   } catch (...) {
      printf("Unhandled exception in main Thread\n");
      return -12;
   }
}

int main(int argc, char* argv[])
{
   return Installer(argc, argv);
}
