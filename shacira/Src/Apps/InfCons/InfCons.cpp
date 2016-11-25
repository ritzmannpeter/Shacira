

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
#include "System/cError.h"
#include "Orb/cCorbaCellProxy.h"

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

int InfCons(int argc, char* argv[])
{
MAINFUNC_PROLOG("InfCons")
   try {
      cResources resources(argc, argv);
      cSockets::Initialize();
      char temp_buf[8192];
      LONG_T nread = 0;
      STRING_T ip_address = "127.0.0.1";
      cResources::GetOption("Address", ip_address);
      LONG_T ip_port = 21001;
      cResources::GetOption("Port", ip_port);
      BOOL_T show_proxies = false;
      cResources::GetOption("ShowProxies", show_proxies);
      BOOL_T show_pid = false;
      cResources::GetOption("ShowPID", show_pid);
      printf("Socket console on port %d ...\n", ip_port);
      STRING_T log_file_name = "Log/InfCons.log";
      cConsole * console = new cSocketConsole(ip_address.c_str(), ip_port, DIRECTION_INPUT);
      int count = 0;
      while (42) {
         memset(temp_buf, 0, sizeof(temp_buf));
         nread = console->Read(temp_buf, sizeof(temp_buf) - 1, 200);
         if (nread > 0) {
            if (show_proxies) {
               cCorbaCellProxy * proxy = new cCorbaCellProxy;
               if (proxy->Construct(temp_buf)) {
                  printf("%08.08d:%s:%s:%s:%d:%d\n", count,
                         proxy->get_ProxyName().c_str(),
                         proxy->get_Computer().c_str(),
                         proxy->get_IPAddress().c_str(),
                         proxy->get_Port(),
                         proxy->get_ProcessId());
               }
               delete proxy;
            } else {
               printf("%s", temp_buf);
            }
            count++;
         } else {
//printf("nix\n");
         }
      }
      return 0;
   } catch (cError & e) {
      ErrorPrintf("%s\n", (const char*) e);
      return -11;
   } catch (...) {
      ErrorPrintf("Unhandled exception in main Thread\n");
      return -12;
   }
MAINFUNC_EPILOG
}

int main(int argc, char* argv[])
{
   return InfCons(argc, argv);
}
