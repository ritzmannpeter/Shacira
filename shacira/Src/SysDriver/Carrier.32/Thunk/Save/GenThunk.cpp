#include "OwlExt.i"
#pragma hdrstop

#ifndef __WIN32__  // only for 16-bit platform

#include <stdarg.h>
#include "GenThunk.h"

HINSTANCE32 (WINAPI *TGenericThunk::LoadLibraryEx32W) (LPCSTR, DWORD, DWORD);
BOOL        (WINAPI *TGenericThunk::FreeLibrary32W)   (HINSTANCE32);
HPROC32     (WINAPI *TGenericThunk::GetProcAddress32W)(HINSTANCE32, LPCSTR);
DWORD       (WINAPI *TGenericThunk::GetVDMPointer32W) (LPVOID, UINT);
DWORD       (WINAPI *TGenericThunk::CallProc32W)      (HPROC32, DWORD, DWORD);


TGenericThunk::TGenericThunk (const char * fileName)
{
    //  Initialize our static members if they're not already:
    //
    if (! LoadLibraryEx32W)
    {
        HMODULE hKernel = GetModuleHandle ("KERNEL");

        (FARPROC) LoadLibraryEx32W  = GetProcAddress (hKernel, "LoadLibraryEx32W");
        (FARPROC) FreeLibrary32W    = GetProcAddress (hKernel, "FreeLibrary32W");
        (FARPROC) GetProcAddress32W = GetProcAddress (hKernel, "GetProcAddress32W");
        (FARPROC) GetVDMPointer32W  = GetProcAddress (hKernel, "GetVDMPointer32W");
        (FARPROC) CallProc32W       = GetProcAddress (hKernel, "CallProc32W");

        //  All or nothing:
        if (! LoadLibraryEx32W || ! FreeLibrary32W || ! GetProcAddress32W ||
            ! GetVDMPointer32W || ! CallProc32W)
        {
            LoadLibraryEx32W    = 0;
            FreeLibrary32W      = 0;
            GetProcAddress32W   = 0;
            GetVDMPointer32W    = 0;
            CallProc32W         = 0;
        }
    }


    mInst32 = 0;

    if (LoadLibraryEx32W)
        mInst32 = LoadLibraryEx32W (fileName, 0, 0);
}


TGenericThunk::~TGenericThunk ()
{
    if (mInst32)
    {
        FreeLibrary32W (mInst32);
        mInst32 = 0;
    }
}


HPROC32 TGenericThunk::GetProcAddr32 (const char * procName)
{
    return mInst32 ? GetProcAddress32W (mInst32, procName)
                   : NULL;
}


////////////////////////////////////////////////////////////////////////////
//  This method makes the call to the 32-bit function referenced by hProc.
//  The fAddrCvt flags are the trickiest part, while nArgs is simply the
//  number of DWORD arguments to pass.  Each bit of fAddrCvt maps to one of
//  the arguments.  The lowest bit represents the last parameter, the 2nd
//  lowest bit represents the 2nd-to-last parameter, etc..  If the bit is
//  set (ie, a 1), that parameters is treated as a 16:16 far pointer.  The
//  32-bit side will receive a 32-bit pointer to that buffer.  If the bit
//  is not set, the 32-bit side will receive the 32-bit value unchanged.
//
DWORD __cdecl TGenericThunk::CallProc32 (HPROC32 hProc, DWORD fAddrCvt,
                                                        DWORD nArgs, ...)
{
    va_list     args;
    DWORD       dwTemp;


    if (! CallProc32W || ! hProc)
        return 0;

    va_start (args, nArgs);

    //  Copy the arguments from our stack frame to the stack frame that
    //  CallProc32W expects:
    //
    for (DWORD n = nArgs; n; )
    {
        dwTemp = va_arg (args, DWORD);
        -- n;

        __asm push word ptr [dwTemp+2];
        __asm push word ptr [dwTemp];
    }

    va_end (args);

    //  Call CallProc32W.  The pushed variable list precedes the parameters,
    //  as assumed by CallProc32W.  Appropriate parameters will be popped by
    //  CallProc32W based on the value of nArgs:
    //
    return CallProc32W (hProc, fAddrCvt, nArgs);
}


////////////////////////////////////////////////////////////////////////////
//  This method returns the 32-bit address for the specified 16:16 address
//  and size. 
//
DWORD TGenericThunk::GetVdmPtr16 (void far *buffer, unsigned cbSize)
{
    return GetVDMPointer32W ? GetVDMPointer32W (buffer, cbSize)
                            : 0;
}


////////////////////////////////////////////////////////////////////////////
//  This method will allocate a 16:16 pointer that points at the specified
//  32-bit memory address range.  This pointer must be released by calling
//  FreeVdmPtr32.
//
void far * TGenericThunk::GetVdmPtr32 (DWORD dwAddr32, DWORD cbSize)
{
    UINT  uSelector = ::AllocSelector (_DS); // our DS (for access rights)


    if (uSelector)
    {
        // Assign its linear base address and limit
        ::SetSelectorBase  (uSelector, dwAddr32);
        ::SetSelectorLimit (uSelector, cbSize);
    }

    return MAKELP (uSelector, 0);
}


////////////////////////////////////////////////////////////////////////////
//  This method will free the selector allocated by GetVdmPtr32.
//
void TGenericThunk::FreeVdmPtr32 (void far *ptr)
{
    if (SELECTOROF (ptr))
        ::FreeSelector (SELECTOROF (ptr));
}


#endif  // __WIN32__

