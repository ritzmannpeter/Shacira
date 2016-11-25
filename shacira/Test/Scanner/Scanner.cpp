

#include <windows.h>
#include <stdio.h>

static int Parity(const char * parity_spec)
{
   if (strnicmp(parity_spec, "n", 1) == 0) {
      return NOPARITY;
   } else if (strnicmp(parity_spec, "e", 1) == 0) {
      return EVENPARITY;
   } else if (strnicmp(parity_spec, "o", 1) == 0) {
      return ODDPARITY;
   } else {
      return NOPARITY;
   }
}    

static const char * ParityString(int parity)
{
   switch (parity) {
   case NOPARITY:
      return "n";
   case EVENPARITY:
      return "e";
   case ODDPARITY:
      return "o";
   }
   return "?";
}    

static int StopBits(int bits)
{
   if (bits == 1) {
      return ONESTOPBIT;
   } else if (bits == 2) {
      return TWOSTOPBITS;
   } else {
      return ONESTOPBIT;
   }
}    

static void SetBaudRate(HANDLE handle, unsigned long baud_rate)
{
   DCB dcb = {0};
   if (!GetCommState(handle, &dcb)) {
      printf("failed to get comm state: %d\n", GetLastError());
   } else {
      dcb.BaudRate = baud_rate;
      if (!SetCommState(handle, &dcb)) {
         printf("failed to set comm state: %d\n", GetLastError());
      }
   }
}

static void SetCharLen(HANDLE handle, unsigned char char_length)
{
   DCB dcb = {0};
   if (!GetCommState(handle, &dcb)) {
      printf("failed to get comm state: %d\n", GetLastError());
   } else {
      dcb.ByteSize = char_length;
      if (!SetCommState(handle, &dcb)) {
         printf("failed to set comm state: %d\n", GetLastError());
      }
   }
}

static void SetStopBits(HANDLE handle, int stop_bits)
{
   DCB dcb = {0};
   if (!GetCommState(handle, &dcb)) {
      printf("failed to get comm state: %d\n", GetLastError());
   } else {
      dcb.StopBits = stop_bits;
      if (!SetCommState(handle, &dcb)) {
         printf("failed to set comm state: %d\n", GetLastError());
      }
   }
}

static void SetParity(HANDLE handle, int parity)
{
   DCB dcb = {0};
   if (!GetCommState(handle, &dcb)) {
      printf("failed to get comm state: %d\n", GetLastError());
   } else {
      dcb.Parity = parity;
      if (!SetCommState(handle, &dcb)) {
         printf("failed to set comm state: %d\n", GetLastError());
      }
   }
}

int main(int argc, char* argv[])
{
   const char * port = "com2";
   unsigned long baud_rate = 9600;
   int parity = NOPARITY;
   int stop_bits = StopBits(1);
   if (argc > 1) {
      port = argv[1];
   }
   if (argc > 2) {
      baud_rate = atol(argv[2]);
   }
   if (argc > 3) {
      parity = Parity(argv[3]);
   }
   if (argc > 4) {
      stop_bits = StopBits(atol(argv[4]));
   }
   HANDLE handle;
   DCB dcb = {0};
   char port_name[32] = {0};
   sprintf(port_name, "\\\\.\\%s",port);
   if ((handle = CreateFile(port_name,
                            GENERIC_WRITE | GENERIC_READ,
                            0, NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL)) != INVALID_HANDLE_VALUE) {
      if (!GetCommState(handle, &dcb)) {
         printf("failed to get state %d\n", GetLastError());
         return -1;
      } else {
         dcb.fOutxCtsFlow = FALSE;
         dcb.fOutxDsrFlow = FALSE;
         dcb.fDtrControl = DTR_CONTROL_ENABLE;
         dcb.fRtsControl = RTS_CONTROL_ENABLE;
         dcb.fOutX  = FALSE;
         dcb.fInX = FALSE;
         dcb.fParity = TRUE;
         dcb.BaudRate = baud_rate;
         dcb.Parity = parity;
         dcb.StopBits = stop_bits;
         if (!SetCommState(handle, &dcb)) {
            printf("failed to set state %d\n", GetLastError());
//            return -1;
         }
      }
      SetBaudRate(handle, baud_rate);
      SetCharLen(handle, 8);
      SetStopBits(handle, stop_bits);
      SetParity(handle, parity);
      COMMTIMEOUTS timeouts = {0};
      timeouts.ReadIntervalTimeout = 0;
      timeouts.ReadTotalTimeoutMultiplier = 0;
      timeouts.ReadTotalTimeoutConstant = 10000;
      if (!SetCommTimeouts(handle, &timeouts)) {
         printf("failed to set timeout %d\n", GetLastError());
         return -1;
      }
      unsigned long nwrite = 0;
      int ret = 0;
      char inbuf[0x2000] = {0};
      char * buf = NULL;
      printf("scanner on %s %d %s %d %d\n", port, baud_rate, ParityString(parity), 8, stop_bits);
      while (42)  {
         if (buf = gets(inbuf)) {
            char c = 0;
            int i = 0;
            for (i=0; i<(int)strlen(buf); i++) {
               c = buf[i];
               ret = WriteFile(handle, &c, 1, &nwrite, NULL);
            }
            c = 0x0d;
            ret = WriteFile(handle, &c, 1, &nwrite, NULL);
            c = 0x0a;
            ret = WriteFile(handle, &c, 1, &nwrite, NULL);
            memset(inbuf, 0, sizeof(inbuf));
            c = 0;
         }
      }
      CloseHandle(handle);
   } else {
      printf("failed to create connection on %s\n", port);
   }
   return 0;
}

