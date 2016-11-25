

#include "safefunctions.h"

#ifdef __linux__
#include "cexceptionhnd.h"
extern unsigned long _VirtualMemory;
extern unsigned long _TransientObjects;
unsigned long _ProcessFlags = PFLAG_IREGULAR_EXIT;
#endif

#if defined(_WIN32)

//==========================================
// Matt Pietrek
// Microsoft Systems Journal, April 1997
// FILE: MSJEXHND.CPP
//==========================================
#include <stdio.h>
#include <time.h>
#include "cexceptionhnd.h"

extern unsigned long _VirtualMemory;
extern unsigned long _TransientObjects;
unsigned long _ProcessFlags = PFLAG_IREGULAR_EXIT;

extern "C" {
extern void PrintMemStatistics(FILE * stream);
}
static char _TimeText[0x200] = {0};
static const char * TimeText()
{
   memset(_TimeText, 0, sizeof(_TimeText));
   time_t timer;
   struct tm * time_struct;
   timer = time(NULL);
   time_struct = localtime(&timer);
   SafePrintf(_TimeText, sizeof(_TimeText), "%s", asctime(time_struct));
   return _TimeText;
}

//============================== Global Variables =============================
//
// Declare the static variables of the cExceptionHnd class
//

TCHAR cExceptionHnd::m_szLogFileName[MAX_PATH] = ""; 
LPTOP_LEVEL_EXCEPTION_FILTER cExceptionHnd::m_previousFilter;
bool cExceptionHnd::_PrintingActive = FALSE;

//============================== Class Methods =============================
//=============
// Constructor 
//=============
cExceptionHnd::cExceptionHnd( )
{
   SetErrorMode(SEM_NOGPFAULTERRORBOX);
   // Install the unhandled exception filter function
   m_previousFilter = SetUnhandledExceptionFilter(MSJUnhandledExceptionFilter);
   // Figure out what the report file will be named, and store it away
   if (m_szLogFileName[0] != 0) {
   } else {
      _tcscpy(m_szLogFileName, EXCEPTION_LOG_FILE_1);
#ifdef lassma
      GetModuleFileName(0, m_szLogFileName, MAX_PATH);
      // Look for the '.' before the "EXE" extension.  Replace the extension
      // with "RPT"
      PTSTR pszDot = _tcsrchr( m_szLogFileName, _T('.') );
      if (pszDot) {
         pszDot++;   // Advance past the '.'
         if (_tcslen(pszDot) >= 3) {
            _tcscpy( pszDot, _T("RPT") );   // "RPT" -> "Report"
         }
      }
#endif
   }
   int rc = atexit(ExitFunction);
   StartupFunction();
}

//============
// Destructor 
//============
cExceptionHnd::~cExceptionHnd()
{
   SetUnhandledExceptionFilter( m_previousFilter );
}

//==============================================================
// Lets user change the name of the report file to be generated 
//==============================================================
void cExceptionHnd::SetLogFileName(PTSTR pszLogFileName)
{
   _tcscpy(m_szLogFileName, pszLogFileName);
}

void cExceptionHnd::SetShaciraLogFileName(PTSTR pszLogFileName)
{
   SetLogFileName(pszLogFileName);
}

const char * cExceptionHnd::GetLogFileName()
{
   return m_szLogFileName;
}

//===========================================================
// Entry point where control comes on an unhandled exception 
//===========================================================
LONG WINAPI cExceptionHnd::MSJUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
   GenerateExceptionReport2(pExceptionInfo);
   if (m_previousFilter) {
      return m_previousFilter(pExceptionInfo);
   } else {
      return EXCEPTION_CONTINUE_SEARCH;
   }
}
 
//===========================================================================
// Open the report file, and write the desired information to it.  Called by 
// MSJUnhandledExceptionFilter                                               
//===========================================================================
void cExceptionHnd::GenerateExceptionReport(PEXCEPTION_POINTERS pExceptionInfo)
{
   if (_PrintingActive) {
      return;
   }
   _PrintingActive = TRUE;
   HANDLE report_hnd = CreateFile(m_szLogFileName,
                                  GENERIC_WRITE,
                                  0,
                                  0,
                                  OPEN_ALWAYS,
                                  FILE_FLAG_WRITE_THROUGH,
                                  0);
   if (report_hnd) {
      SetFilePointer(report_hnd, 0, 0, FILE_END);
      // Start out with a banner
      _tprintf(report_hnd, _T("//=====================================================\n"));
      _tprintf(report_hnd, _T("exception \t\t%s"), TimeText());
      _tprintf(report_hnd, _T("memory: %d objects %d\n"), _VirtualMemory, _TransientObjects);
      _tprintf(report_hnd, _T("//=====================================================\n"));
      PEXCEPTION_RECORD pExceptionRecord = pExceptionInfo->ExceptionRecord;
      // First print information about the type of fault
      _tprintf(report_hnd, _T("Exception code: %08X %s\n"),
               pExceptionRecord->ExceptionCode,
               GetExceptionString(pExceptionRecord->ExceptionCode));
      // Now print information about where the fault occured
      TCHAR szFaultingModule[MAX_PATH];
      DWORD section, offset;
      GetLogicalAddress(pExceptionRecord->ExceptionAddress,
                        szFaultingModule,
                        sizeof(szFaultingModule),
                        section, offset);
      _tprintf(report_hnd, _T("Fault address:  %08X %02X:%08X %s\n"),
               pExceptionRecord->ExceptionAddress,
               section, offset, szFaultingModule);
      PCONTEXT pCtx = pExceptionInfo->ContextRecord;
      // Show the registers
#ifdef _M_IX86  // Intel Only!
      _tprintf(report_hnd, _T("\nRegisters:\n") );
      _tprintf(report_hnd, _T("EAX:%08X\nEBX:%08X\nECX:%08X\nEDX:%08X\nESI:%08X\nEDI:%08X\n"),
               pCtx->Eax, pCtx->Ebx, pCtx->Ecx, pCtx->Edx, pCtx->Esi, pCtx->Edi);
      _tprintf(report_hnd, _T("CS:EIP:%04X:%08X\n"), pCtx->SegCs, pCtx->Eip);
      _tprintf(report_hnd, _T("SS:ESP:%04X:%08X  EBP:%08X\n"),
               pCtx->SegSs, pCtx->Esp, pCtx->Ebp);
      _tprintf(report_hnd, _T("DS:%04X  ES:%04X  FS:%04X  GS:%04X\n"),
               pCtx->SegDs, pCtx->SegEs, pCtx->SegFs, pCtx->SegGs);
      _tprintf(report_hnd,  _T("Flags:%08X\n"), pCtx->EFlags);
      // Walk the stack using x86 specific code
      IntelStackWalk(report_hnd, pCtx);
#endif
 
      _tprintf(report_hnd,  _T("\n") );
      CloseHandle(report_hnd);
   }
   _PrintingActive = FALSE;
}

//===========================================================================
// Open the report file, and write the desired information to it.  Called by 
// MSJUnhandledExceptionFilter                                               
//===========================================================================
void cExceptionHnd::GenerateExceptionReport2(PEXCEPTION_POINTERS pExceptionInfo)
{
   if (_PrintingActive) {
      return;
   }
   HANDLE report_hnd = 0;
   // Start out with a banner
   _tprintf(report_hnd, _T("//=====================================================\n") );
   _tprintf(report_hnd, _T("exception \t\t%s"), TimeText());
   _tprintf(report_hnd, _T("memory: %d objects %d\n"), _VirtualMemory, _TransientObjects);
   _tprintf(report_hnd, _T("//=====================================================\n"));
   PEXCEPTION_RECORD pExceptionRecord = pExceptionInfo->ExceptionRecord;
   // First print information about the type of fault
   _tprintf(report_hnd, _T("Exception code: %08X %s\n"),
            pExceptionRecord->ExceptionCode,
            GetExceptionString(pExceptionRecord->ExceptionCode));
   // Now print information about where the fault occured
   TCHAR szFaultingModule[MAX_PATH];
   DWORD section, offset;
   GetLogicalAddress(pExceptionRecord->ExceptionAddress,
                     szFaultingModule,
                     sizeof(szFaultingModule),
                     section, offset);
   _tprintf(report_hnd, _T("Fault address:  %08X %02X:%08X %s\n"),
            pExceptionRecord->ExceptionAddress,
            section, offset, szFaultingModule);
   PCONTEXT pCtx = pExceptionInfo->ContextRecord;
   // Show the registers
#ifdef _M_IX86  // Intel Only!
   _tprintf(report_hnd, _T("\nRegisters:\n") );
   _tprintf(report_hnd, _T("EAX:%08X\nEBX:%08X\nECX:%08X\nEDX:%08X\nESI:%08X\nEDI:%08X\n"),
            pCtx->Eax, pCtx->Ebx, pCtx->Ecx, pCtx->Edx, pCtx->Esi, pCtx->Edi);
   _tprintf(report_hnd, _T("CS:EIP:%04X:%08X\n"), pCtx->SegCs, pCtx->Eip);
   _tprintf(report_hnd, _T("SS:ESP:%04X:%08X  EBP:%08X\n"),
            pCtx->SegSs, pCtx->Esp, pCtx->Ebp);
   _tprintf(report_hnd, _T("DS:%04X  ES:%04X  FS:%04X  GS:%04X\n"),
            pCtx->SegDs, pCtx->SegEs, pCtx->SegFs, pCtx->SegGs);
   _tprintf(report_hnd,  _T("Flags:%08X\n"), pCtx->EFlags);
   // Walk the stack using x86 specific code
   IntelStackWalk(report_hnd, pCtx);
#endif
   _tprintf(report_hnd,  _T("\n") );
   _PrintingActive = FALSE;
}

//======================================================================
// Given an exception code, returns a pointer to a static string with a 
// description of the exception                                         
//======================================================================
LPTSTR cExceptionHnd::GetExceptionString(DWORD dwCode)
{
#define EXCEPTION( x ) case EXCEPTION_##x: return _T(#x);
   switch(dwCode) {
      EXCEPTION( ACCESS_VIOLATION )
      EXCEPTION( DATATYPE_MISALIGNMENT )
      EXCEPTION( BREAKPOINT )
      EXCEPTION( SINGLE_STEP )
      EXCEPTION( ARRAY_BOUNDS_EXCEEDED )
      EXCEPTION( FLT_DENORMAL_OPERAND )
      EXCEPTION( FLT_DIVIDE_BY_ZERO )
      EXCEPTION( FLT_INEXACT_RESULT )
      EXCEPTION( FLT_INVALID_OPERATION )
      EXCEPTION( FLT_OVERFLOW )
      EXCEPTION( FLT_STACK_CHECK )
      EXCEPTION( FLT_UNDERFLOW )
      EXCEPTION( INT_DIVIDE_BY_ZERO )
      EXCEPTION( INT_OVERFLOW )
      EXCEPTION( PRIV_INSTRUCTION )
      EXCEPTION( IN_PAGE_ERROR )
      EXCEPTION( ILLEGAL_INSTRUCTION )
      EXCEPTION( NONCONTINUABLE_EXCEPTION )
      EXCEPTION( STACK_OVERFLOW )
      EXCEPTION( INVALID_DISPOSITION )
      EXCEPTION( GUARD_PAGE )
      EXCEPTION( INVALID_HANDLE )
   }
   // If not one of the "known" exceptions, try to get the string
   // from NTDLL.DLL's message table.
static TCHAR szBuffer[512] = { 0 };
   FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
                 GetModuleHandle(_T("NTDLL.DLL")),
                 dwCode, 0, szBuffer, sizeof(szBuffer), 0);
   return szBuffer;
}

//==============================================================================
// Given a linear address, locates the module, section, and offset containing  
// that address.                                                               
//                                                                             
// Note: the szModule paramater buffer is an output buffer of length specified 
// by the len parameter (in characters!)                                       
//==============================================================================
BOOL cExceptionHnd::GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset)
{
   MEMORY_BASIC_INFORMATION mbi;
   if (!VirtualQuery( addr, &mbi, sizeof(mbi))) {
      return FALSE;
   }
   DWORD hMod = (DWORD)mbi.AllocationBase;
   if (!GetModuleFileName( (HMODULE)hMod, szModule, len)) {
      return FALSE;
   }
   // Point to the DOS header in memory
   PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;
   // From the DOS header, find the NT (PE) header
   PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);
   PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHdr);
   DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address
   // Iterate through the section table, looking for the one that encompasses
   // the linear address.
   for (unsigned i = 0;
        i < pNtHdr->FileHeader.NumberOfSections;
        i++, pSection++) {
      DWORD sectionStart = pSection->VirtualAddress;
      DWORD sectionEnd = sectionStart + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);
      // Is the address in this section???
      if ((rva >= sectionStart) && (rva <= sectionEnd)) {
         // Yes, address is in the section.  Calculate section and offset,
         // and store in the "section" & "offset" params, which were
         // passed by reference.
         section = i+1;
         offset = rva - sectionStart;
         return TRUE;
      }
   }
   return FALSE;   // Should never get here!
}

//============================================================
// Walks the stack, and writes the results to the report file 
//============================================================
void cExceptionHnd::IntelStackWalk(HANDLE report_hnd, PCONTEXT pContext)
{
   _tprintf(report_hnd,  _T("\nCall stack:\n") );
   _tprintf(report_hnd,  _T("Address   Frame     Logical addr  Module\n") );
   DWORD pc = pContext->Eip;
   PDWORD pFrame, pPrevFrame;
   pFrame = (PDWORD)pContext->Ebp;
   do {
      TCHAR szModule[MAX_PATH] = _T("");
      DWORD section = 0, offset = 0;
      GetLogicalAddress((PVOID)pc, szModule,sizeof(szModule),section,offset );
      _tprintf(report_hnd, _T("%08X  %08X  %04X:%08X %s\n"),
               pc, pFrame, section, offset, szModule);
      pc = pFrame[1];
      pPrevFrame = pFrame;
      pFrame = (PDWORD)pFrame[0]; // precede to next higher frame on stack
      if ((DWORD)pFrame & 3) {    // Frame pointer must be aligned on a
         break;                   // DWORD boundary.  Bail if not so.
      }
      if (pFrame <= pPrevFrame) {
         break;
      }
      // Can two DWORDs be read from the supposed frame address?          
      if (IsBadWritePtr(pFrame, sizeof(PVOID)*2)) {
         break;
      }
   } while ( 1 );
}

//============================================================================
// Helper function that writes to the report file, and allows the user to use 
// printf style formating                                                     
//============================================================================
int __cdecl cExceptionHnd::_tprintf(HANDLE report_hnd, const TCHAR * format, ...)
{
   TCHAR szBuff[1024];
   int retValue;
   DWORD cbWritten;
   va_list argptr;
   va_start(argptr, format);
   retValue = wvsprintf(szBuff, format, argptr);
   va_end(argptr);
   if (report_hnd != 0) {
      WriteFile(report_hnd, szBuff, retValue * sizeof(TCHAR), &cbWritten, 0);
   } else {
      FILE * stream = NULL;
      const char * log_file = GetLogFileName();
      if (stream == NULL) {
         stream = fopen(log_file, "a");
      }
      if (stream == NULL) {
         stream = fopen(EXCEPTION_LOG_FILE_1, "a");
      }
      if (stream == NULL) {
         stream = fopen(EXCEPTION_LOG_FILE_2, "a");
      }
      if (stream) {
         fprintf(stream, "%s", szBuff);
         fclose(stream);
      }
   }
   return retValue;
}

void cExceptionHnd::ExitFunction()
{
   try {
      FILE * stream = NULL;
      const char * log_file = GetLogFileName();
      if (stream == NULL) {
         stream = fopen(log_file, "a");
      }
      if (stream == NULL) {
         stream = fopen(EXCEPTION_LOG_FILE_1, "a");
      }
      if (stream == NULL) {
         stream = fopen(EXCEPTION_LOG_FILE_2, "a");
      }
      if (stream) {
         if (_ProcessFlags & PFLAG_IREGULAR_EXIT) {
            fprintf(stream, "memory: %d objects %d\n", _VirtualMemory, _TransientObjects);
            PrintMemStatistics(stream);
            fprintf(stream, "sudden exit \t\t%s", TimeText());
         } else {
            fprintf(stream, "regular exit \t\t%s\n", TimeText());
         }
         fclose(stream);
      }
   } catch (...) {
   }
}

void cExceptionHnd::StartupFunction()
{
   try {
      FILE * stream = NULL;
      const char * log_file = GetLogFileName();
      if (stream == NULL) {
         stream = fopen(log_file, "a");
      }
      if (stream == NULL) {
         stream = fopen(EXCEPTION_LOG_FILE_1, "a");
      }
      if (stream == NULL) {
         stream = fopen(EXCEPTION_LOG_FILE_2, "a");
      }
      if (stream) {
         fprintf(stream, "start up \t\t%s", TimeText());
         fclose(stream);
      }
   } catch (...) {
   }
}

#endif   //  _WIN32


