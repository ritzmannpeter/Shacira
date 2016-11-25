
#include "stdio.h"
#include "stdarg.h"
#include "../CarDLL32/cardll32.h"

#define FALSE  0
#define TRUE   1
#define MAX_SIZE 0x8000
static char _Buffer[MAX_SIZE] = {0};
static char _TextBuffer[0x2000] = {0};
const char * _LogFileName = "check.log";
const char * _DumpFileName = "check.dmp";
static char _Repair = FALSE;

static void Log(const char * fmt_str, ...)
{
   va_list args;
   FILE * stream = NULL;
   va_start(args, fmt_str);
   vsprintf(_TextBuffer, fmt_str, args);
   va_end(args);
   printf("%s", _TextBuffer);
   stream = fopen(_LogFileName, "a");
   if (stream != NULL) {
      fprintf(stream, "%s", _TextBuffer);
      fclose(stream);
   }
}

static void PrintPort(HANDLE hnd, const char * param_name,  const char * port_value_name)
{
   long port_value = -1;
   long port_addr = 0;
   long rc = CAR_GetParam(hnd, param_name, &port_addr);
   if (rc >= 0) {
      rc = CAR_GetParam(hnd, port_value_name, &port_value);
      if (rc >= 0) {
         Log("Port\t%s\t%x\t%x\n", param_name, port_addr, port_value);
         return;
      }
   }
   printf("Error reading parameter %s: %d\n", param_name, rc);
}

static void PrintParam(HANDLE hnd, const char * param_name, const char * fmt)
{
   long value = 0;
   long rc = CAR_GetParam(hnd, param_name, &value);
   if (rc >= 0) {
      Log(fmt, param_name, value);
      return;
   }
   Log("Error reading parameter %s: %d\n", param_name, rc);
}

static void Repair(HANDLE hnd, int size)
{
   int err = 0;
   unsigned char b_0 = 0, b_2048 = 0, zero = 0;
   if (size > 0x2000) return;
   err = CAR_Read(hnd, 0, &b_0, 1, 1);
   if (err < 0) return;
   err = CAR_Read(hnd, 2048, &b_2048, 1, 1);
   if (err < 0) return;
   if (b_2048 != 0) {
      if (b_0 == b_2048) {
         err = CAR_Write(hnd, 0, &zero, 1);
         if (err >= 0) {
            Log("synchronized carrier: byte 0 set to 0 (%d)\n", b_0);
         }
         err = CAR_Write(hnd, 2048, &zero, 1);
         if (err >= 0) {
            Log("synchronized carrier: byte 2048 set to 0 (%d)\n", b_2048);
         }
      }
   }
}

static void Check()
{
   int size = 0;
   int nwrite = 0;
   const char * file_name = _DumpFileName;
   FILE * stream = NULL;
   int err = 0;
   HANDLE hnd;
   Log("\ncheck carrier ...\n");
   hnd = CAR_Open();
   if (hnd != INVALID_HANDLE_VALUE) {
      PrintParam(hnd, "PORT_ADDRESS", "%s\t%x\n");
      PrintParam(hnd, "VERSION", "%s\t%d\n");
      PrintParam(hnd, "CHECK_MODE", "%s\t%d\n");
      PrintParam(hnd, "RETRIES", "%s\t%d\n");
      PrintParam(hnd, "STABILITY", "%s\t%d\n");
      PrintParam(hnd, "DELAY_TIME", "%s\t%d\n");
      PrintPort(hnd, "ADDR_LOW_PORT", "VALUE_LOW_PORT");
      PrintPort(hnd, "ADDR_HIGH_PORT", "VALUE_HIGH_PORT");
      PrintPort(hnd, "CMD_PORT", "VALUE_CMD_PORT");
      PrintPort(hnd, "READ_PORT", "VALUE_READ_PORT");
      PrintPort(hnd, "WRITE_PORT", "VALUE_WRITE_PORT");
      PrintPort(hnd, "STATUS_PORT", "VALUE_STATUS_PORT");
      PrintParam(hnd, "SIM_MEM_SIZE", "%s\t%d\n");
      PrintParam(hnd, "SIM_MEMORY", "%s\t%x\n");
      PrintParam(hnd, "SIM_MEM_VAL0", "%s\t%d\n");
      PrintParam(hnd, "SIM_MEM_VAL1", "%s\t%d\n");
      PrintParam(hnd, "SIM_MEM_VAL2", "%s\t%d\n");
      PrintParam(hnd, "SIM_MEM_VAL3", "%s\t%d\n");
      Log("\n");
      size = CAR_Check(hnd);
      if (size == 4 ||
          size == 8 ||
          size == 32) {
         size *= 1024;
         Log("size = %d\n", size);
         err = CAR_Read(hnd, 0, _Buffer, sizeof(_Buffer), size);
         if (err < 0) {
            Log("read error: %d\n", err);
            CAR_Close(hnd);
            return;
         }
      } else {
         Log("check error: %d\n", size);
         CAR_Close(hnd);
         return;
      }
      if (_Repair) Repair(hnd, size);
      CAR_Close(hnd);
   } else {
      Log("Failed to open carrier device\n");
      return;
   }
   stream = fopen(file_name, "wb");
   if (stream == NULL) {
      Log("failed to open file %s\n", file_name);
      return;
   }
   nwrite = fwrite(_Buffer, 1, size, stream);
   if (nwrite != size) {
      Log("failed to write to file %s\n", file_name);
      fclose(stream);
      return;
   }
   fclose(stream);
}

int main(int argc, char ** argv)
{
   int i = 0;
   if (argc > 1) {
      for (i=1; i<argc; i++) {
         if (stricmp(argv[i], "-sync") == 0) {
            _Repair = TRUE;
         } else {
            fprintf(stderr, "invalid option %s\n", argv[i]);
            fprintf(stderr, "available options: -sync\n");
            return 0;
         }
      }
   }
   Check();
   return 0;
}
