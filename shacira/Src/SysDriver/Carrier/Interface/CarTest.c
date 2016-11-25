 
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>

#include "caritf.h"

#define NUL "NUL"
#define MAXDATA "MAXDATA"
#define MAX_BUFFER 0x8000
#define MAX_ERRORS 1000

enum CMD {NOCMD=0, AUTO, CHECK, PARAMLIST, PARAMSET, 
          READ, READBINARY, READVERBOSE, READFILE, 
          WRITE, WRITETOKEN, WRITEFILE, STAT};

int Cmd = NOCMD;
char msgbuf[2*MAX_BUFFER];

int DebugPrintf(char * fmtstr, ...)
{
   va_list args;
   FILE * stream;
   char buffer[2*MAX_BUFFER];

   va_start(args, fmtstr);
   vsprintf(buffer, fmtstr, args);
   va_end(args);
   stream = fopen("Cartest.txt", "a");
   if (stream != NULL) {
      fprintf(stream, "%s", buffer);
      fclose(stream);
   }
   return 0;
}

static void PrintParam(HANDLE hnd, const char * param_name, const char * fmt)
{
   long value = 0;
   long rc = CARITF_GetParam(hnd, param_name, &value);
   if (rc >= 0) {
      printf(fmt, param_name, value);
      return;
   }
   printf("Error reading parameter %s: %d\n", param_name, rc);
}

static void PrintPort(HANDLE hnd, const char * param_name,  const char * port_value_name)
{
   long port_value = -1;
   long port_addr = 0;
   long rc = CARITF_GetParam(hnd, param_name, &port_addr);
   if (rc >= 0) {
      rc = CARITF_GetParam(hnd, port_value_name, &port_value);
      if (rc >= 0) {
         printf("Port\t%s\t%x\t%x\n", param_name, port_addr, port_value);
         return;
      }
   }
   printf("Error reading parameter %s: %d\n", param_name, rc);
}

int main(int argc, char ** argv)
{
   unsigned char c = '\0';
   long size, bytes, addr, lval = 0;
   int i, ret = 0, errcount = 0;
   int stats = 100;
   char iobuf[MAX_BUFFER] = {0};
   char buffer[MAX_BUFFER] = {0};
   HANDLE hnd = 0;
   char * param_name = "";

   remove("Cartest.txt");
   if (argc < 2) {
      printf("\n  Use Cartest.exe -? for further help\n");
      return 0;
   } 
   _strupr(argv[1]);
   if (argv[1][0] == '-' || argv[1][0] == '/') {
      switch (argv[1][1]) {
      case 'A': 
         if (argv[1][2] == '\0')
            Cmd = AUTO; 
         break;

      case 'C': 
         if (argv[1][2] == '\0')
            Cmd = CHECK; 
         break;

      case 'S': 
         if (argv[1][2] == '\0')
            Cmd = STAT; 
         break;

      case 'P': 
         if (argv[1][2] == 'L' && argv[1][3] == '\0')
            Cmd = PARAMLIST;
         else if (argv[1][2] == 'S' && argv[1][3] == '\0')
            Cmd = PARAMSET;
         break;

      case 'R':
         if (argv[1][2] == '\0')
            Cmd = READ;
         else if (argv[1][2] == 'B' && argv[1][3] == '\0')
            Cmd = READBINARY;
         else if (argv[1][2] == 'V' && argv[1][3] == '\0')
            Cmd = READVERBOSE;
         else if (argv[1][2] == 'F' && argv[1][3] == '\0')
            Cmd = READFILE;
         break;

      case 'W':
         if (argv[1][2] == '\0')
            Cmd = WRITE;
         else if (argv[1][2] == 'T' && argv[1][3] == '\0')
            Cmd = WRITETOKEN;
         else if (argv[1][2] == 'F' && argv[1][3] == '\0')
            Cmd = WRITEFILE;
         break;

      case '?':
         printf("\n  Use one of the following options");
         printf("\n  --------------------------------");
         printf("\n    Automatic logs Errors in Cartest.txt -a  (leave with ESC)");
         printf("\n    Check Carrier Size in KB             -c");
         printf("\n    Stat Carrier Size in KB              -s");
         printf("\n    List Driver Parameters               -pl [times]");
         printf("\n    Set Driver Parameter                 -ps V|C|D|S|R param");
         printf("\n    Read from Carrier                    -r  addr bytes");
         printf("\n    Read from Carrier (binary)           -rb addr bytes");
         printf("\n    Read from Carrier (verbose)          -rv addr bytes");
         printf("\n    Read from Carrier into File          -rf addr bytes path");
         printf("\n    Write to Carrier                     -w  addr text");
         printf("\n    Write Block of Tokens                -wt addr bytes token");
         printf("\n    Write a File on Carrier              -wf addr bytes path");
         printf("\n");
         printf("\n  Further information");
         printf("\n  -------------------");
         printf("\n    addr  : Decimale Address (0..MAXDATA)");
         printf("\n    bytes : Number of Bytes (0..MAXDATA)");
         printf("\n    token : Any Character (or NUL)");
         printf("\n    path  : Path to a File");
         printf("\n    param : Parameter value (as DWORD)");
         printf("\n    V=Version C=CheckMode D=DelayTime S=Stability R=Retries");
         printf("\n    'MAXDATA' can be used as bytes- 'NUL' as token-parameter");
         printf("\n");
         return 0;
      }
   }
   if (Cmd == NOCMD) {
      printf("\n  Invalid option %s\n", argv[1]);
      return 0;
   }
   hnd = CARITF_Open();
   if (hnd == INVALID_HANDLE_VALUE) {
      printf("Failed to open device\n");
      return 0;
   }
//   printf("Device opened successfully\n");
   if (Cmd != PARAMLIST && Cmd != PARAMSET && Cmd != STAT) {
      if ((ret = CARITF_Check(hnd)) > 0) {
         size = ret;
         bytes = ret * 1024l;
      } else {
         printf("\n Check Error %ld\n", ret);
         CARITF_Close(hnd);
         return 0;
      }
   }
   switch (Cmd) {
   case AUTO:
      srand((unsigned)time(NULL));
      while (errcount < MAX_ERRORS) {
         char datebuf[9];
         char timebuf[9];
         if (kbhit())
            if (getch() == 27) break;
         addr = rand() & (size >= 32 ? 0x7fff : 0x0fff);
         bytes = rand() & (size >= 32 ? 0x1fff : 0x3ff);
         c = (unsigned char)rand();
         memset(iobuf, c, bytes);
         printf("\nWrite %ld Byte(s) to Carrier:\n", bytes);
         if ((ret = CARITF_Write(hnd, addr, iobuf, bytes)) >= 0) {
            const Line = 20;
            int count = bytes;
            i = 0;
            errcount = 0;
            while (count>Line) {
               Sleep(10);
               if (kbhit()) if (getch() == 27) {
                  CARITF_Close(hnd);
                  return 0;
               }
               sprintf(msgbuf,
                  ".%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X."
                  ".%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X.",
                  (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], 
                  (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], 
                  (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], 
                  (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], 
                  (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], 
                  (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], (unsigned char)iobuf[i++], 
                  (unsigned char)iobuf[i++], (unsigned char)iobuf[i++]);
               printf(msgbuf);
               count -= Line;
               if (CARITF_Check(hnd) < 0) count = 0;
            }
            for (count; count>0; count--)
               printf(".%02X.", (unsigned char)iobuf[i]);
            printf("\nWritten %ld Byte(s) to Carrier:\n", ret);
         } else {
            Beep(440, 125);
            _strdate(datebuf);
            _strtime(timebuf);
            sprintf(msgbuf, "\n(%s|%s)  ", datebuf, timebuf);
            DebugPrintf(msgbuf);
            sprintf(msgbuf, "Write Error %ld -> Cannot Write %ld Bytes to Addr %ld", ret, bytes, addr);
            printf(msgbuf);
            DebugPrintf(msgbuf);
            errcount++;
            continue;
         }
         if (kbhit())
            if (getch() == 27) break;
         if ((ret = CARITF_Read(hnd, addr, buffer, sizeof(buffer),  bytes)) >= 0) {
            const Line = 20;
            int count = bytes;
            i = 0;
            errcount = 0;
            while (count>Line) {
               Sleep(10);
               if (kbhit()) if (getch() == 27) {
                  CARITF_Close(hnd);
                  return 0;
               }
               sprintf(msgbuf,
                  ".%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X."
                  ".%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X..%02X.",
                  (unsigned char)buffer[i++], (unsigned char)buffer[i++], (unsigned char)buffer[i++], 
                  (unsigned char)buffer[i++], (unsigned char)buffer[i++], (unsigned char)buffer[i++], 
                  (unsigned char)buffer[i++], (unsigned char)buffer[i++], (unsigned char)buffer[i++], 
                  (unsigned char)buffer[i++], (unsigned char)buffer[i++], (unsigned char)buffer[i++], 
                  (unsigned char)buffer[i++], (unsigned char)buffer[i++], (unsigned char)buffer[i++],
                  (unsigned char)buffer[i++], (unsigned char)buffer[i++], (unsigned char)buffer[i++], 
                  (unsigned char)buffer[i++], (unsigned char)buffer[i++]);
               printf(msgbuf);
               count -= Line;
               if (CARITF_Check(hnd) < 0) count = 0;
            }
            for (count; count>0; count--)
               printf(".%02X.", (unsigned char)buffer[i]);
            printf("\nRead %ld Byte(s) from Carrier:\n", ret);
         } else {
            Beep(440, 125);
            _strdate(datebuf);
            _strtime(timebuf);
            sprintf(msgbuf, "\n(%s|%s)  ", datebuf, timebuf);
            DebugPrintf(msgbuf);
            sprintf(msgbuf, "Read Error %ld -> Cannot Read %ld Bytes form Addr %ld", ret, bytes, addr);
            printf(msgbuf);
            DebugPrintf(msgbuf);
            errcount++;
            continue;
         }
         if (memcmp(iobuf, buffer, bytes)) {
            Beep(440, 125);
            _strdate(datebuf);
            _strtime(timebuf);
            sprintf(msgbuf, "\n(%s|%s)  Compairing Out- and InBuffer not successful\n", datebuf, timebuf);
            DebugPrintf(msgbuf);
            sprintf(msgbuf, "[OUTBUFFER] %ld Bytes\n", bytes);
            for (i=0; i<bytes; i++) {
               char buf[5];
               sprintf(buf, ".%02X.", (unsigned char)iobuf[i]);
               strcat(msgbuf, buf);
            }
            strcat(msgbuf, "\n");
            DebugPrintf(msgbuf);
            sprintf(msgbuf, "[INBUFFER] %ld Bytes\n", bytes);
            for (i=0; i<bytes; i++) {
               char buf[5];
               sprintf(buf, ".%02X.", (unsigned char)buffer[i]);
               strcat(msgbuf, buf);
            }
            strcat(msgbuf, "\n");
            DebugPrintf(msgbuf);
            errcount++;
         }

         if (kbhit())
            if (getch() == 27) break;
      }
      CARITF_Close(hnd);
      return 0;
   case CHECK:
      printf("\n  Check Carrier Size...\r");
      if ((ret = CARITF_Check(hnd)) > 0) {
         printf("  Carrier size is %ld KB (%s)\n", ret, ret<32 ? "yellow":"grey");
         PrintParam(hnd, "PAGE_MODE", "%s\t%d\n");
      } else {
         printf("  Check Carrier was not successful: Error %ld\n", ret);
      }
      CARITF_Close(hnd);
      return 0;
   case STAT:
      if (argc == 3) {
         stats = atoi(argv[2]);
      }
      printf("\n  Stat Carrier %d times ...\r", stats);
      for (i=0; i<stats; i++) {
         PrintPort(hnd, "STATUS_PORT", "VALUE_STATUS_PORT");
      }
      CARITF_Close(hnd);
      return 0;
   case PARAMLIST:
      printf("\n  List Driver Parameters...\n");
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
      break;
   case PARAMSET:
      if (argc < 4) {
         printf("\n  Set Driver Parameter missing %ld argument(s)\n", 4-argc);
         CARITF_Close(hnd);
         return 0;
      }
      if (argv[2][1] != '\0') {
         printf("  Invalid Driver Parameter: %s\n  Please use: V|C|D|S|R\n", argv[2]);
         CARITF_Close(hnd);
         return 0;
      }
      _strupr(argv[2]);
      switch (argv[2][0]) {
      case 'V': 
         sprintf(buffer, "Version"); break;
      case 'C': 
         sprintf(buffer, "CheckMode"); break;
      case 'D': 
         sprintf(buffer, "DelayTime"); break;
      case 'R': 
         sprintf(buffer, "Retries"); break;
      case 'S':
         sprintf(buffer, "Stability"); break;
      default:
         printf("  Invalid Driver Parameter: %s\n  Please use: V|C|D|S|R\n", argv[2]);
         CARITF_Close(hnd);
         return 0;
      }
      printf("\n  Set Driver Parameter...\r");
      if ((ret = CARITF_SetParam(hnd, buffer, atol(argv[3]))) == 0)
         printf("  Set Driver Parameter '%s' to %ld\n", buffer, atol(argv[3]));
      else
         printf("  Cannot set Driver Parameter '%s' to %ld: Error %ld\n", buffer, atol(argv[3]), ret);
      CARITF_Close(hnd);
      return 0;
   case READ:
   case READBINARY:
   case READVERBOSE:
   case READFILE:
      if (argc < 4) {
         if (Cmd == READFILE)
            printf("\n  Read from Carrier missing %ld argument(s)\n", 5-argc);
         else
            printf("\n  Read from Carrier missing %ld argument(s)\n", 4-argc);
         CARITF_Close(hnd);
         return 0;
      }
      if (Cmd == READFILE && argc < 5) {
         printf("\n  Read from Carrier into File missing Filename\n");
         CARITF_Close(hnd);
         return 0;
      }
      printf("\n  Read from Carrier...\r");
      addr = atoi(argv[2]);
      bytes -= addr;
      if (strcmp(MAXDATA, argv[3])) bytes = atoi(argv[3]);
      if (bytes > MAX_BUFFER) {
         printf("  %ld Bytes is the Maximum of Input Buffer\n", MAX_BUFFER);
         CARITF_Close(hnd);
         return 0;
      }
      if (Cmd == READFILE) {
         FILE *fp = fopen(argv[argc-1], "wb");
         if (fp == NULL) {
            printf("  Cannot Create this File: %s\n", argv[argc-1]);
         } else {
            if ((ret = CARITF_Read(hnd, addr, iobuf, sizeof(iobuf), bytes)) >= 0) {
               if ((long)fwrite(iobuf, 1, bytes, fp) == bytes)
                  printf("  %ld Byte(s) read from Carrier written to File %s\n", bytes, argv[argc-1]); 
               else
                  printf("  Cannot Write this File: %s\n", argv[argc-1]);
            } else
               printf("  Read from Carrier into File was not successful: Error %ld\n", ret);                         
            fclose(fp);
         }
      } else if ((ret = CARITF_Read(hnd, addr, iobuf, sizeof(iobuf), bytes)) >= 0) {
         if (Cmd == READBINARY) {
            printf("  Read %ld Byte(s) from Carrier:\n\n", ret);
            for (i=0; i<bytes; i++)
               printf(".%02X.", (unsigned char)iobuf[i]);
            printf("\n");
         } else if (Cmd == READVERBOSE) {
            printf("  Read %ld Byte(s) from Carrier:\n\n", ret);
            for (i=0; i<bytes; i++) {
               char buf[4] = {0};
               unsigned char c = iobuf[i];
               switch (c) {
               case 0:
                  sprintf(buf, "NUL"); break;
               case 7:
                  sprintf(buf, "BEL"); break;
               case 8:
                  sprintf(buf, "BSP"); break;
               case 9:
                  sprintf(buf, "TAB"); break;
               case 10:
                  sprintf(buf, "CR "); break;
               case 13:
                  sprintf(buf, "LF "); break;
               case 26:
                  sprintf(buf, "EOF"); break;
               default:
                  sprintf(buf, "(%c)", iobuf[i]);
               }
               printf(" [%05ld] %02X %s ", i+addr, (unsigned char)iobuf[i], buf);
            } 
         } else
            printf("  Read %ld Byte(s) from Carrier: %s\n", ret, iobuf);
      } else
         printf("  Read from Carrier was not successful: Error %ld\n", ret);
      CARITF_Close(hnd);
      return 0;
   case WRITE:
   case WRITETOKEN:
   case WRITEFILE:
      if (argc < 4) {
         if (Cmd == WRITE)
            printf("\n  Write to Carrier missing %ld argument(s)\n", 4-argc);
         else
            printf("\n  Write to Carrier missing %ld argument(s)\n", 5-argc);
         CARITF_Close(hnd);
         return 0;
      }
      if (Cmd == WRITEFILE && argc < 5) {
         printf("\n  Write a File on Carrier missing Filename\n");
         CARITF_Close(hnd);
         return 0;
      }
      if (Cmd == WRITETOKEN && argc < 5) {
         printf("\n  Write Block of Tokens missing a Token\n");
         CARITF_Close(hnd);
         return 0;
      }
      printf("\n  Write to Carrier...\r");
      addr = atoi(argv[2]);
      bytes -= addr;
      if (strcmp(MAXDATA, argv[3])) bytes = atoi(argv[3]);
      if (bytes > MAX_BUFFER) {
         printf("  %ld Bytes is the Maximum of Output Buffer\n", MAX_BUFFER);
         CARITF_Close(hnd);
         return 0;
      }
      if (Cmd == WRITETOKEN) {
         if (strcmp(NUL, argv[4])) c = argv[4][0];
         memset(iobuf, c, bytes);
         if ((ret = CARITF_Write(hnd, addr, iobuf, bytes)) >= 0)
            printf("  Block of %ld Bytes of '%c' Token written\n", bytes, c);
         else
            printf("  Write Block of Tokens was not successful: Error %ld\n", ret);
      } else if (Cmd == WRITEFILE) {
         FILE *fp = fopen(argv[4], "rb");
         if (fp == NULL)
            printf("  Cannot Open this File: %s\n", argv[4]);
         else {
            if ((bytes = fread(iobuf, 1, bytes, fp)) >= 0) {
               if ((ret = CARITF_Write(hnd, addr, iobuf, bytes)) >= 0)
                  printf("  %ld Byte(s) written to Carrier read from File %s\n", bytes, argv[4]); 
               else
                  printf("  Write a File on Carrier was not successful: Error %ld\n", ret);
            } else
               printf("  Cannot Read this File: %s\n", argv[4]);
            fclose(fp);
         }
      } else {
         bytes = strlen(argv[3]);
         strncpy(iobuf, argv[3], bytes);
         if ((ret = CARITF_Write(hnd, addr, iobuf, bytes)) >= 0)
            printf("  Write %ld Byte(s) to Carrier: '%s'\n", ret, iobuf);
         else
            printf("  Write to Carrier was not successful: Error %ld\n", ret);
      }
      CARITF_Close(hnd);
      return 0;
   }
   CARITF_Close(hnd);
   return 0;
}
