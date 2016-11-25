
#ifndef __FuncSpecs_h__
#define __FuncSpecs_h__

#include "FirstHeader.h"

#define MAX_STACK_LENGTH   256

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

typedef void (*VOID_FUNC)(smem mem);
typedef CHAR_T (*CHAR_FUNC)(smem mem);
typedef UCHAR_T (*UCHAR_FUNC)(smem mem);
typedef SHORT_T (*SHORT_FUNC)(smem mem);
typedef USHORT_T (*USHORT_FUNC)(smem mem);
typedef LONG_T (*LONG_FUNC)(smem mem);
typedef ULONG_T (*ULONG_FUNC)(smem mem);
typedef FLOAT_T (*FLOAT_FUNC)(smem mem);
typedef DOUBLE_T (*DOUBLE_FUNC)(smem mem);
typedef CONST_STRING_T (*STRING_FUNC)(smem mem);
typedef CONST_WSTRING_T (*WSTRING_FUNC)(smem mem);
typedef PTR_T (*PTR_FUNC)(smem mem);

typedef void (*FUNC_T)(smem mem);
typedef struct {
   const char * func_name;
   FUNC_T func_ptr;
   UCHAR_T func_class;
}  FUNC_ENTRY_T;

typedef void (*VOID_FUNC_T)(smem mem);
typedef void (*FUNC_ADDRESS_T)();

#endif

