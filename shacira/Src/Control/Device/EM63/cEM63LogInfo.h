
#ifndef _cEM63LogInfo_h
#define _cEM63LogInfo_h 	1

#if (SHACIRA_MAJOR < 2 && SHACIRA_MINOR < 4)
#if defined(_WIN32)
   #include <windows.h>
   typedef volatile int ATOMIC_T;
   #define __ECL_ATOMIC_SET__(n,v) n = v;
   #define __ECL_ATOMIC_GET__(n) (n)
   #define __ECL_ATOMIC_INCREMENT__(n) InterlockedIncrement((long*)&n)
   #define __ECL_ATOMIC_DECREMENT__(n) InterlockedDecrement((long*)&n)
#elif defined(__linux__)
   #include "asm/atomic.h"
   typedef atomic_t ATOMIC_T;
   #define __ECL_ATOMIC_SET__(n,v) n.counter = v;
   #define __ECL_ATOMIC_GET__(n) atomic_read(&n)
   #define __ECL_ATOMIC_INCREMENT__(n) atomic_add_return(1,&n)
   #define __ECL_ATOMIC_DECREMENT__(n) atomic_sub_return(1,&n)
#else
   typedef volatile int ATOMIC_T;
   #define __ECL_ATOMIC_SET__(n,v) n = v;
   #define __ECL_ATOMIC_GET__(n) (n)
   #define __ECL_ATOMIC_INCREMENT__(n) ++n
   #define __ECL_ATOMIC_DECREMENT__(n) --n
#endif
#else
#include "base/base_ex.h"
   using namespace ecl;
#endif

class cEM63LogInfo {
public:
   cEM63LogInfo();
   cEM63LogInfo(ULONG_T category, ULONG_T operation, int err_code,
                CONST_STRING_T param1 = NULL, CONST_STRING_T param2 = NULL, CONST_STRING_T param3 = NULL);
protected:
   ~cEM63LogInfo();
public:
   void AddRef();
   void Release();
   ULONG_T Category();
   void SetCategory(ULONG_T category);
   ULONG_T Operation();
   void SetOperation(ULONG_T operation);
   int ErrCode();
   void SetErrCode(ULONG_T err_code);
   STRING_T Param1();
   void SetParam1(const char * param);
   STRING_T Param2();
   void SetParam2(const char * param);
   STRING_T Param3();
   void SetParam3(const char * param);
protected:
   ATOMIC_T _RefCount;
   ULONG_T _Category;
   ULONG_T _Operation;
   int _ErrCode;
   STRING_T _Param1;
   STRING_T _Param2;
   STRING_T _Param3;
};

#endif

