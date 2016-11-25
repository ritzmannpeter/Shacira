
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "string"
#include "liba.h"
#include <qstring.h>

typedef std::string STRING_T;

#ifdef lassma

#include <System/Sys/cLinuxPort.h>
#include "iostream.h"
#include "string"
#include "list"
#include "vector"
#include "map"

using std::endl;
using std::istream;
using std::ostream;
using std::cout;
using std::string;
//using std::wstring;
using std::list;
using std::map;
using std::vector;

#define isprint(c) TRUE
typedef std::string STRING_T;

#include "base/eb_array.hpp"
#include "base/eb_base.hpp"
#include "base/eb_bprintf.hpp"
#include "base/eb_clip.hpp"
//#include "base/eb_cmdarg.hpp"
//#include "base/eb_cmdline.hpp"
#include "base/eb_collect.hpp"
#include "base/eb_dde.hpp"
//#include "base/eb_docview.hpp"
#include "base/eb_elo.hpp"
#include "base/eb_eloex.hpp"
#include "base/eb_err.hpp"
#include "base/eb_event.hpp"
//#include "base/eb_file.hpp"
#include "base/eb_geo2d.hpp"
#include "base/eb_list.hpp"
#include "base/eb_map.hpp"
#include "base/eb_math.hpp"
#include "base/eb_msg.hpp"
#include "base/eb_npipe.hpp"
#include "base/eb_object.hpp"
#include "base/eb_osver.hpp"
//#include "base/eb_parse.hpp"
#include "base/eb_process.hpp"
#include "base/eb_prof.hpp"
#include "base/eb_queue.hpp"
#include "base/eb_res.hpp"
#include "base/eb_ring.hpp"
#include "base/eb_sema.hpp"
#include "base/eb_shmem.hpp"
#include "base/eb_str.hpp"
#include "base/eb_strex.hpp"
#include "base/eb_thread.hpp"
#include "base/eb_time.hpp"

#define TYPE      int
#define ARG_TYPE  int
cList<int,int> pNode;
std::list<int> heinz;

#endif

static void Out(char c)
{
return;
#ifdef lassma
   char out[0x10] = {0};
   if (isprint(c)) {
      sprintf(out, "%c", c);
   } else {
      sprintf(out, "[%d]", (int)c);
   }
   printf("%s", out);
   FILE * stream = fopen("out.log", "a");
   if (stream != NULL) {
      fprintf(stream, "%s", out);
      fclose(stream);
   }
#endif
}

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

#define MAX_STACK_LENGTH   256

typedef struct _inner {
   char fill[MAX_STACK_LENGTH];
}  inner;
    
typedef struct {
   int start_of_struct;
   inner stack;
}  PARAMS;

typedef struct _smem {
   char mem[MAX_STACK_LENGTH];
}  smem;
    
typedef struct {
   int addr;
   void * sp;
   smem mem;
}  STACK_T;

#define STACK_INIT(stack)  \
   stack.addr = 0; \
   stack.sp = &(stack.mem.mem[stack.addr]);

#define STACK_PUSH(stack,type,value)  \
   *(type*)stack.sp = value; \
   stack.addr += sizeof(value); \
   stack.sp = &(stack.mem.mem[stack.addr]);

typedef void (*VOID_FUNC)(inner stack);
typedef double (*double_func)(inner stack);
typedef int (*int_func)(int i1, int i2, int i3, int i4);
typedef int (*_int_func)(smem mem);
typedef float (*_float_func)(smem mem);

typedef void (*FUNC_T)(inner stack);
typedef struct {
   const char * func_name;
   FUNC_T func_ptr;
   unsigned char func_class;
}  FUNC_ENTRY_T;

typedef void (*FUNC_ADDRESS_T)();


extern "C" {

int f0(short i1, int i2, int i3, int i4)
{
   printf("adding %d + %d + %d + %d\n",
          (long)i1,
          (long)i2,
          (long)i3,
          (long)i4);
   return (i1 + i2 + i3 + i4);
}

float f1(short i1, float f1, double f2, long i2, double f3, void * a1)
{
   printf("adding %d + %f + %f + %d + %f + %p\n",
          (int)i1,
          (double)f1,
          (double)f2,
          (int)i2,
          (double)f3,
          (void*)a1);
   return (float)f3;
}

}

#define PUSH_VALUE(type,value) \
   *(type*)ap = value; \
   va_arg(ap, type);

void test_call(int i1, ...)
{
   int ires = 0;
   float fres = 0;
   _int_func addr1 = (_int_func)f0;
   _float_func addr2 = (_float_func)f1;
   STACK_T stack;

   STACK_INIT(stack);
   STACK_PUSH(stack,short,1);
   STACK_PUSH(stack,int,2);
   STACK_PUSH(stack,int,3);
   STACK_PUSH(stack,int,4);
   ires = addr1(stack.mem);
   printf("ires is %d\n", ires);

   STACK_INIT(stack);
   STACK_PUSH(stack,short,1);
   STACK_PUSH(stack,float,(float)2.2);
   STACK_PUSH(stack,double,3.3);
   STACK_PUSH(stack,long,4);
   STACK_PUSH(stack,double,5.5);
   STACK_PUSH(stack,void*, stack.sp);
   fres = addr2(stack.mem);
   printf("fres is %f\n", (double)fres);
}

int main(int argc, char* argv[])
{
   printf("\n\n");
   liba a;
   a.print();
   a.print();

   WORD req_version = MAKEWORD(2, 2);
   WSADATA wsa_data;
   int err = WSAStartup(req_version, &wsa_data);
 

   printf("calling ...\n");
   test_call(5);


#if defined(__GNUC__)
#if !defined(__MINGW32__)
#error "ltoa is not part of cygwin"
char sval[0x50] = {0};
char * num_ptr = ltoa(255, sval, 10);
printf("converted to %s\n", num_ptr);
#endif
#endif

STRING_T s1 = "s1";
STRING_T s2 = "s2";
STRING_T s = s1 + s2.c_str();
printf("concatenation of %s and %s = %s\n", s1.c_str(), s2.c_str(), s.c_str());

QCString qs1 = "s1";
QCString qs2 = "s2";
QCString qs = qs1 + (const char *)qs2;
printf("concatenation of %s and %s = %s\n", (const char*)qs1, (const char*)qs2, (const char*)qs);

#ifdef lassma

   const char * port = "com1";
   if (argc > 1) {
      port = argv[1];
   }
   unsigned long baud_rate = 9600;
   if (argc > 2) {
      baud_rate = atol(argv[2]);
   }
   int parity = NOPARITY;
   if (argc > 3) {
      parity = Parity(argv[3]);
   }
   int stop_bits = ONESTOPBIT;
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
      DCB dcb = {0};
      if (!GetCommState(handle, &dcb)) {
         printf("failed to get state %d\n", GetLastError());
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
            printf("failed to get state %d\n", GetLastError());
         }
      }
      char c = 0;
      unsigned long nread = 0;
      printf("listening on %s\n...\n", port);
      while (42) {
         if (ReadFile(handle, &c, 1, &nread, NULL) == 0) {
            printf("read error %d\n", GetLastError());
         } else {
            Out(c);
         }
      }
      CloseHandle(handle);
   } else {
      printf("failed to create connection on %s\n", port);
   }
#endif
   return 0;
}

