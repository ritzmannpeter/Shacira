/// @file  shacira.h
/// @brief General Shacira definitions

#ifndef shacira_h
#define shacira_h 1

#include "sh_platform.h"
#include "shacira_version.h"
#include "safefunctions.h"

/*
 * Code organization
 */

#ifdef __SHACIRA_DLL__
#define __DLL_EXPORT__ __SH_DLL_EXPORT__
#else
#define __DLL_EXPORT__
#endif

/*
 * Global data type definitions
 */

typedef char CHAR_T;
typedef unsigned char UCHAR_T;
typedef short SHORT_T;
typedef unsigned short USHORT_T;
typedef int INT_T;
typedef unsigned int UINT_T;
typedef long LONG_T;
typedef unsigned long ULONG_T;
typedef float FLOAT_T;
typedef double DOUBLE_T;
typedef bool BOOL_T;
typedef std::string STRING_T;
typedef const CHAR_T * CONST_STRING_T;
typedef CHAR_T * STRING_BUF_T;
#if defined(__linux__) || defined(__MINGW32__)
#include "System/cLiteWString.h"
typedef short WCHAR_T;
typedef cLiteWString WSTRING_T;
#else
//typedef unsigned char WCHAR_T;
//typedef std::string WSTRING_T;
#include "System/cLiteWString.h"
typedef short WCHAR_T;
typedef cLiteWString WSTRING_T;
#endif
typedef const WCHAR_T * CONST_WSTRING_T;
typedef WCHAR_T * WSTRING_BUF_T;
typedef UCHAR_T * BUF_T;
typedef const UCHAR_T * CONST_BUF_T;
typedef WSTRING_T & WBUF_T;
typedef void * PTR_T;
typedef std::list<STRING_T> STRING_LIST_T;
typedef std::list<LONG_T> LONG_LIST_T;
typedef std::list<WSTRING_T> WSTRING_LIST_T;
typedef std::list<FLOAT_T> FLOAT_LIST_T;
typedef std::list<DOUBLE_T> DOUBLE_LIST_T;
typedef std::list<void *> POINTER_LIST_T;
typedef std::vector<BOOL_T> BOOL_VECTOR_T;
typedef std::vector<STRING_T> STRING_VECTOR_T;
typedef std::vector<WSTRING_T> WSTRING_VECTOR_T;
typedef std::vector<void *> POINTER_VECTOR_T;
typedef std::vector<int> INT_VECTOR_T;
typedef std::vector<SHORT_T> SHORT_VECTOR_T;
typedef std::vector<USHORT_T> USHORT_VECTOR_T;
typedef std::vector<INT_T> INT_VECTOR_T;
typedef std::vector<UINT_T> UINT_VECTOR_T;
typedef std::vector<LONG_T> LONG_VECTOR_T;
typedef std::vector<ULONG_T> ULONG_VECTOR_T;
typedef std::vector<BOOL_T> BOOL_VECTOR_T;
typedef std::map<STRING_T, STRING_T> STRING_MAP_T;
typedef std::map<STRING_T, ULONG_T> ULONG_MAP_T;
typedef std::map<STRING_T, LONG_T> LONG_MAP_T;
typedef std::map<STRING_T, BOOL_T> BOOL_MAP_T;

// Enums

#define TYPE_NAME(tc1,tc2) 	if (tc1 == tc2) return #tc2;
#define TYPE_CODE(tn,tc)   	if (strcmp(tn,#tc) == 0) return tc;
#define IDENTIFIER_EQUAL(i1,i2) (strcmp(i1,i2) == 0)

typedef enum {UndefinedRangeType=-1, Unlimited, Limited, Enumeration} RangeTypes;
typedef enum {UndefinedBaseType=-1, Numeric, String, TypeDef, ObjectDef} BaseTypes;
typedef enum {UndefinedDirection=-1,Input, Output} DirectionTypes;
// value types for configuration
typedef enum {UndefinedValue=-1,IntValue,IntVector,StringValue,StringVector,
              PointerValue,PointerVector,FloatValue,FloatVector,
              /*BoolValue,BoolVector*/} ValueTypes;
// action types for driver
typedef enum {UndefinedAction=-1,
              DriverStart,DriverStop,
              CommunicationStart,CommunicationAbort,
              ProductionStateChange,AutomaticStart,AutomaticStop,
              CycleSpecChanged,CycleSpecDeleted,
              ActivateCycleSpec,DeactivateCycleSpec} ActionTypes;

/*
 * Global function prototypes
 */

// <-MW- 2005-04-19
// Support for current file and line number added
// old: #define ErrorPrintf cResources::EPrintf
#define ErrorPrintf cResources::cPrint(__FILE__,__LINE__).Error
// old: #define InfoPrintf cResources::IPrintf
#define InfoPrintf cResources::cPrint(__FILE__,__LINE__).Info
#define FatalPrintf cResources::cPrint(__FILE__,__LINE__).FatalError

/// Print a printf style formatted error message to error log file. The message is
/// enlarged by a timestamp, the current file name and line number. Note: the
/// parameter list requires @b two brackets!
/// @code 
/// PrintErrorFmt(("Error code = %d", errno));
/// @endcode
#define PrintErrorFmt( params_in_brackets ) \
   cResources::cPrint(__FILE__,__LINE__).Error params_in_brackets

/// Print error message (string constant) to error log file. The message is enlarged
/// by a timestamp, the current file name and line number.
/// @code 
/// PrintErrorText("File not found");
/// @endcode
#define PrintErrorText( const_string ) \
   cResources::cPrint(__FILE__,__LINE__).Error("%s", const_string)

/// Print a printf style formatted information message to information log file. The message is
/// enlarged by a timestamp, the current file name and line number. Note: the
/// parameter list requires @b two brackets!
/// @code 
/// PrintErrorFmt(("Error code = %d", errno));
/// @endcode
#define PrintInfoFmt( params_in_brackets ) \
   cResources::cPrint(__FILE__,__LINE__).Info params_in_brackets

/// Print information message (string constant) to information log file. The message is enlarged
/// by a timestamp, the current file name and line number.
/// @code 
/// PrintErrorText("File not found");
/// @endcode
#define PrintInfoText( const_string ) \
   cResources::cPrint(__FILE__,__LINE__).Info("%s",const_string)
// -MW->
#define DCPrintf cSystemUtils::DebugConsolePrintf
#define ExitProcess cResources::Exit
#define ExceptionFilter cResources::Filter


/*
 * Global macro definitions
 */

#define _ASSERT_UNCOND   _ASSERT_COND(false)
#define _ASSERT_COND(condition) \
if (!(condition)) { \
   FatalPrintf("assertion failed in file %s line %d\n", __FILE__, __LINE__); \
   ExitProcess(-10); \
}

// Object delete macros

#define DELETE_OBJECT(type, obj) \
try { \
   if (obj != NULL) { \
      delete obj; \
   } \
} catch (...) { \
   FatalPrintf("failed to delete object in file %s line %d\n", __FILE__, __LINE__); \
   ExitProcess(-11, false); \
}

// Thread control macros to be used in MainFunc

#define MAINFUNC_PROLOG(thread_name) \
   const char * __thread_name__ = thread_name; \
   try {
#define MAINFUNC_EPILOG \
   } catch (cError & e) { \
      FatalPrintf("%s\nmain function of thread %s\n", (const char*)e, __thread_name__); \
      return ExitProcess(-12, false); \
   } catch (cErrBase & e) { \
      FatalPrintf("ErrBase exception (%d,%d,%d)\nmain function of thread %s\n", \
                 e.getClass(), e.getCode(), e.getPrefix(), __thread_name__); \
      return ExitProcess(-13, false); \
   } catch (...) { \
      FatalPrintf("unhandled exception\nmain function of thread %s\n", __thread_name__); \
      return ExitProcess(-14, false); \
   }

#define MAINFUNC_LOOP_PROLOG(thread_name) \
   const char * __thread_name__ = thread_name; \
   try {
#define MAINFUNC_LOOP_EPILOG \
   } catch (cError & e) { \
      ErrorPrintf("%s\nin main function loop of thread %s\n", (const char*)e, __thread_name__); \
   } catch (cErrBase & e) { \
      FatalPrintf("ErrBase exception (%d,%d,%d)\nmain function loop of thread %s\n", \
                 e.getClass(), e.getCode(), e.getPrefix(), __thread_name__); \
      return ExitProcess(-15); \
   } catch (...) { \
      FatalPrintf("unhandled exception\nmain function loop of thread %s\n", __thread_name__); \
      return ExitProcess(-16); \
   }

// Thread control macros to be used in MessageFunc

#define MESSAGEFUNC_PROLOG(thread_name) \
   const char * __thread_name__ = thread_name; \
   try {
#define MESSAGEFUNC_EPILOG \
   } catch (cError & e) { \
      FatalPrintf("%s\nmessage function of thread %s\n", (const char*)e, __thread_name__); \
      return ExitProcess(-17, false); \
   } catch (cErrBase & e) { \
      FatalPrintf("ErrBase exception (%d,%d,%d)\nmessage function of thread %s\n", \
                  e.getClass(), e.getCode(), e.getPrefix(), __thread_name__); \
      return ExitProcess(-18, false); \
   } catch (...) { \
      FatalPrintf("unhandled exception in message function of thread %s\n", __thread_name__); \
      return ExitProcess(-19, false); \
   }

// Thread control macros to be used in ControlFunc

#define CONTROLFUNC_PROLOG(thread_name) \
   const char * __thread_name__ = thread_name; \
   try {
#define CONTROLFUNC_EPILOG \
   } catch (cError & e) { \
      ErrorPrintf("%s\nControlFunc of thread %s\n", (const char*)e, __thread_name__); \
      return -19; \
   } catch (cErrBase & e) { \
      FatalPrintf("ErrBase exception (%d,%d,%d)\nControlFunc of thread %s\n", \
                 e.getClass(), e.getCode(), e.getPrefix(), __thread_name__); \
      return ExitProcess(-20, false); \
   } catch (...) { \
      FatalPrintf("unhandled exception\nControlFunc of thread %s\n", __thread_name__); \
      return ExitProcess(-21, false); \
   }

// Function control macros to be used in other controlled functions

#define FUNCTION_PROLOG(func_name) \
const char * __func_name__ = func_name; \
int __line__ = 0; \
__TRY__ {
#define FUNCTION_EPILOG \
} __EXCEPT__(ExceptionFilter(GetExceptionInformation())) { \
   FatalPrintf("unhandled structured exception in function %s\nThread %08x file %s line %d\n", \
              __func_name__, GetCurrentThreadId(), __FILE__, __line__); \
   return ExitProcess(-22, false); \
}
#define VOID_FUNCTION_EPILOG \
} __EXCEPT__(ExceptionFilter(GetExceptionInformation())) { \
   FatalPrintf("unhandled structured exception in function %s\nThread %08x file %s line %d\n", \
              __func_name__, GetCurrentThreadId(), __FILE__, __line__); \
   ExitProcess(-23, false); \
}
#define RC_FUNCTION_EPILOG(rc) \
} __EXCEPT__(ExceptionFilter(GetExceptionInformation())) { \
   FatalPrintf("unhandled structured exception in function %s\nThread %08x file %s line %d\n", \
              __func_name__, GetCurrentThreadId(), __FILE__, __line__); \
   ExitProcess(-24, false); \
   return rc; \
}

#define LINE   __line__ = __LINE__;
#define CRASH *(int*)NULL = 0;

#define PRINT_LINE printf("line %d in file %s\n", __LINE__, __FILE__);
#define _MIN_(a,b) (((a)<(b)) ? a : b)
#define _MAX_(a,b) (((a)>(b)) ? a : b)

// cell initalization steps

#define SH_PRE_CONTEXT_INSTANTIATION	1
#define SH_POST_CONTEXT_INSTANTIATION	2
#define SH_PRE_CONTEXT_CREATION		3
#define SH_POST_CONTEXT_CREATION	4
#define SH_PRE_LOAD_DATA		5
#define SH_INITIALIZE_DATA		6
#define SH_DATA_INITIALIZED		7
#define SH_PRE_SYSTEM_STARTUP		8
#define SH_POST_SYSTEM_STARTUP		9
#define SH_PRE_UPLOAD			10
#define SH_POST_UPLOAD			11
#define SH_PRE_DOWNLOAD			12
#define SH_POST_DOWNLOAD		13
#define SH_CACHE_IS_FREE		14

// user interface initalization steps

#define SH_PRE_UI_INSTANTIATION		1
#define SH_POST_UI_INSTANTIATION	2
#define SH_PRE_CONTEXT_PROPAGATION	3
#define SH_POST_CONTEXT_PROPAGATION	4
#define SH_PRE_UI_START			5
#define SH_PRE_CCS_SERVICE_STARTUP	6
#define SH_POST_CCS_SERVICE_STARTUP	7
#define SH_PRE_INITIALIZE_UI_DATA	8
#define SH_POST_INITIALIZE_UI_DATA	9

/*
 * Temporary stuff
 */

#include "ObjectTypes.h"
#include "System/cError.h"
#include "System/Sys/cSystemUtils.h"
#include "System/Sys/cConvUtils.h"
#include "System/Process/cResources.h"

#endif

