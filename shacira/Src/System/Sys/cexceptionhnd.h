
#ifndef __cExceptionHnd_h__
#define __cExceptionHnd_h__

#define EXCEPTION_LOG_FILE_1 "Log/System.log"
#define EXCEPTION_LOG_FILE_2 "System.log"

extern unsigned long _ProcessFlags;
extern unsigned long _VirtualMemory;
extern unsigned long _TransientObjects;

#define PFLAG_IREGULAR_EXIT   0x00000001

#if defined(_WIN32)

#include <windows.h>
#include <tchar.h>

#ifndef max
#define max(a,b) (((a)>(b)) ? a : b)
#endif
#ifndef min
#define min(a,b) (((a)<(b)) ? a : b)
#endif

class cExceptionHnd
{
public:
   cExceptionHnd();
   ~cExceptionHnd();
   static void SetLogFileName(PTSTR pszLogFileName);
   static void SetShaciraLogFileName(PTSTR pszLogFileName);
   static const char * GetLogFileName();
   // where report info is extracted and generated 
   static void GenerateExceptionReport(PEXCEPTION_POINTERS pExceptionInfo);
   static void GenerateExceptionReport2(PEXCEPTION_POINTERS pExceptionInfo);
private:
   static void __cdecl StartupFunction();
   static void __cdecl ExitFunction();
   // entry point where control comes on an unhandled exception
   static LONG WINAPI MSJUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo);
   // Helper functions
   static LPTSTR GetExceptionString(DWORD dwCode);
   static BOOL GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len,
                                 DWORD& section, DWORD& offset);
   static void IntelStackWalk(HANDLE report_hnd, PCONTEXT pContext);
   static int __cdecl _tprintf(HANDLE report_hnd, const TCHAR * format, ...);
   // Variables used by the class
   static TCHAR m_szLogFileName[MAX_PATH];
   static LPTOP_LEVEL_EXCEPTION_FILTER m_previousFilter;
   static bool _PrintingActive;
};

#endif
 
#endif

