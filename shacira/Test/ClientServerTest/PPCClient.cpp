
#include "FirstHeader.h"
#include "System/ClientServer/cUDPComm.h"
#include "System/ClientServer/cInetAddress.h"
#include "System/ClientServer/cs.h"
#include "cPPCDevice.h"
#include "stdio.h"
#include "string.h"

static void StartSockets()
{
   WORD req_version = MAKEWORD(2, 2);
   WSADATA wsa_data;
   int err = WSAStartup(req_version, &wsa_data);
   if (err != 0) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      throw cSocketError(err, "WSAStartup");
   }
   /* Confirm that the WinSock DLL supports 2.2.*/
   /* Note that if the DLL supports versions greater    */
   /* than 2.2 in addition to 2.2, it will still return */
   /* 2.2 in wVersion since that is the version we      */
   /* requested.                                        */
   if (LOBYTE(wsa_data.wVersion) != 2 ||
       HIBYTE(wsa_data.wVersion) != 2) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      WSACleanup();
      throw cSocketError(-1, "invalid socket library");
   }
}

static char _InBuf[0x2000];
static unsigned short _ReadBuf[0x2000];

#define CMD_UNDEF    0
#define CMD_READ     1
#define CMD_WRITE    2
#define CMD_AUTO     3

static int GetCommand(char * buf,
                      const char * & buf_spec,
                      unsigned long & addr,
                      unsigned long & regs,
                      unsigned short & value)
{
   memset(_InBuf, 0, sizeof(_InBuf));
   gets(buf);
   unsigned long _addr = 0;
   unsigned long _regs = 0;
   unsigned long _value;
   if (stricmp(buf, "auto") == 0) {
      return CMD_AUTO;
   } else {
      if (sscanf(buf, "rr %d %d", &_addr, &_regs) == 2) {
         buf_spec = "register";
         addr = _addr;
         regs = _regs;
         return CMD_READ;
      } else if (sscanf(buf, "rl %d %d", &_addr, &_regs) == 2) {
         buf_spec = "logic";
         addr = _addr;
         regs = _regs;
         return CMD_READ;
      } else if (sscanf(buf, "wr %d %d", &_addr, &_value) == 2) {
         buf_spec = "register";
         addr = _addr;
         regs = 1;
         value = _value;
         return CMD_WRITE;
      } else if (sscanf(buf, "wl %d %d", &_addr, &_value) == 2) {
         buf_spec = "logic";
         addr = _addr;
         regs = 1;
         value = _value;
         return true;
      }
   }
   return CMD_UNDEF;
}

static const char * _BufSpec = NULL;
static int _Command = 0;
static unsigned long _Addr = 0;
static unsigned long _Regs = 0;
static unsigned short _Value = 0;

static void ExecuteCommand(cPPCDevice * device,
                           int command,
                           const char * buf_spec,
                           unsigned long addr,
                           unsigned long regs,
                           unsigned short value)
{
   if (command == CMD_AUTO) {
      while (42) {
         ExecuteCommand(device,
                        _Command,
                        _BufSpec,
                        _Addr,
                        _Regs,
                        _Value);
      }
   } else {
      ULONG_T t = 0, diff = 0;
      ULONG_T i = 0;
      switch (command) {
      case CMD_READ:
         memset(_ReadBuf, 0, sizeof(_ReadBuf));
         t = GetTickCount();
         device->Read(buf_spec, addr, regs * 2, _ReadBuf, sizeof(_ReadBuf));
         diff = GetTickCount() - t;
         if (device->_LastError == 0) {
            for (i=0; i<regs; i++) {
               if ((i % 10) == 0) {
                  printf("\n");
               }
               printf("[%d]", _ReadBuf[i]);
            }
            printf("\n");
         }
         printf("%d ms\n", diff);
         _BufSpec = buf_spec;
         _Command = command;
         _Addr = addr;
         _Regs = regs;
         _Value = value;
         break;
      case CMD_WRITE:
         device->Write(buf_spec, addr, regs * 2, &value);
         _BufSpec = buf_spec;
         _Command = command;
         _Addr = addr;
         _Regs = regs;
         _Value = value;
         break;
      default:
         printf("command %s is invalid\n", _InBuf);
      }
   }
}

bool _Debug = false;

int main(int argc, char* argv[])
{
   unsigned short send_port = 19000;
   unsigned short receive_port = 19000;
   const char * server_host = "localhost";
   for (ULONG_T arg=1; arg<argc; arg++) {
      if (strnicmp(argv[arg], "-r", 2) == 0) {
         receive_port = atol(&(argv[arg][2]));
      } else if (strnicmp(argv[arg], "-s", 2) == 0) {
         send_port = atol(&(argv[arg][2]));
      } else if (strnicmp(argv[arg], "-h", 2) == 0) {
         server_host = &(argv[arg][2]);
      } else if (strnicmp(argv[arg], "-d", 2) == 0) {
         _Debug = true;
      } else if (stricmp(argv[arg], "-?") == 0) {
         printf("usage:\n\tppcclient options\n");
         printf("\toptions:\n");
         printf("\t-r<receive_port> port where the client is waiting for data (%d)\n", receive_port);
         printf("\t-s<send_port> port where the server is waiting for data (%d)\n", send_port);
         printf("\t-h<host> address of the server host (%s)\n", server_host);
         printf("\t-d switches to debug mode\n");
         printf("\t-? this text\n");
         return 0;
      }
   }
   printf("client at %d %d %s\n", send_port, receive_port, server_host);
   if (_Debug) printf("debug mode\n");
   try {
      StartSockets();
      cPPCDevice device(receive_port, send_port, server_host);
      device.Start();
      ULONG_T i = 0;
      while (true) {
         memset(_InBuf, 0, sizeof(_InBuf));
         const char * buf_spec = NULL;
         unsigned long addr = 0;
         unsigned long regs = 0;
         unsigned long tmo = 1000;
         unsigned short value = 0;
         int command = GetCommand(_InBuf, buf_spec, addr, regs, value);
         ExecuteCommand(&device, command, buf_spec, addr, regs, value);
         i++;
      }
      return 0;
   } catch (cSocketError e) {
      printf("socket error %d in function %s\n", e._SocketError, e._SocketFunction);
      return -1;
   } catch (...) {
      printf("unhandled exception\n");
      return -1;
   }
   return 0;
}
