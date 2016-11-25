
#include "FirstHeader.h"
#include "Client/GatewayInterface/cGatewayInterface.h"
#include "System/cTimeObject.h"


static char _LogBuffer[0x1000] = {0};

static void LogPrintf(const char * fmt_str, ...)
{
   va_list args;
   va_start(args, fmt_str);
   vsprintf(_LogBuffer, fmt_str, args);
   va_end(args);
   FILE * stream = fopen("test.log", "a");
   if (stream != NULL) {
      cTimeObject t;
      char timestamp[256] = {0};
      sprintf(timestamp, "%s", (const char *)t);
      printf("%s", _LogBuffer);
      fprintf(stream, "%s: %s", timestamp, _LogBuffer);
      fclose(stream);
   }
}


int main(int argc, char ** argv)
{
   const char * hostname = "localhost";
   if (argc > 1) {
      hostname = argv[1];
   }
   int rc = GIInit(0, 20000, hostname);
   if (rc == 0) {
      char value[0x200] = {0};
      while (1) {
         rc = GIGetValue("sepp", "ActCntMachAdd", value, sizeof(value));
         if (rc == 0) {
            LogPrintf("add. Schusszaehler: %s\n", value);
         } else {
            LogPrintf("failed to get ActCntMachAdd: %d\n", rc);
         }
         rc = GIGetValue("sepp", "ActCntMachSub", value, sizeof(value));
         if (rc == 0) {
            LogPrintf("sub. Schusszaehler: %s\n", value);
         } else {
            LogPrintf("failed to get ActCntMachSub: %d\n", rc);
         }
         Sleep(200);
      }
   } else {
      LogPrintf("failed to initialize gateway client: %d\n", rc);
   }
   return 0;
}

