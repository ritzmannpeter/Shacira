
#include <stdarg.h>
#include "Thunk.h"

#ifdef LOAD_KERNEL_ADRESSES
HINSTANCE32 (WINAPI *TGenericThunk::LoadLibraryEx32W) (LPCSTR, DWORD, DWORD);
BOOL        (WINAPI *TGenericThunk::FreeLibrary32W)   (HINSTANCE32);
HPROC32     (WINAPI *TGenericThunk::GetProcAddress32W)(HINSTANCE32, LPCSTR);
DWORD       (WINAPI *TGenericThunk::GetVDMPointer32W) (LPVOID, UINT);
DWORD       (WINAPI *TGenericThunk::CallProc32W)      (HPROC32, DWORD, DWORD);
#else
DWORD       (WINAPI *CallProc32W) (DWORD, DWORD, HPROC32, DWORD, DWORD);
#endif

TGenericThunk::TGenericThunk (const char * fileName)
{
	_Module = NULL;
#ifdef LOAD_KERNEL_ADRESSES
	_LoadLibraryEx32W = NULL;
	_FreeLibrary32W = NULL;
	_GetProcAddress32W = NULL;
	_GetVDMPointer32W = NULL;
	_CallProc32W = NULL;
	if (!LoadLibraryEx32W) {
		HMODULE hKernel = GetModuleHandle ("KERNEL");
		Message("Kernel module handle %p", hKernel);
		(FARPROC)_LoadLibraryEx32W  = GetProcAddress (hKernel, "LoadLibraryEx32W");
		(FARPROC)_FreeLibrary32W = GetProcAddress (hKernel, "FreeLibrary32W");
		(FARPROC)_GetProcAddress32W = GetProcAddress (hKernel, "GetProcAddress32W");
		(FARPROC)_GetVDMPointer32W = GetProcAddress (hKernel, "GetVDMPointer32W");
		(FARPROC)_CallProc32W = GetProcAddress (hKernel, "CallProc32W");
		if (_LoadLibraryEx32W == NULL) {
			ErrMessage("Failed to get address of LoadLibraryEx32W");
			return;
		}
		if (_FreeLibrary32W == NULL) {
			ErrMessage("Failed to get address of FreeLibraryEx32W");
			return;
		}
		if (_GetProcAddress32W == NULL) {
			ErrMessage("Failed to get address of GetProcAddr3232W");
			return;
		}
		if (_GetVDMPointer32W == NULL) {
			ErrMessage("Failed to get address of GetVDMPointer32W");
			return;
		}
		if (_CallProc32W == NULL) {
			ErrMessage("Failed to get address of CallProc32W");
			return;
		}
	}
	_Module = (HINSTANCE32)_LoadLibraryEx32W(fileName, NULL, 0);
#else
//	_Module = (HINSTANCE32)LoadLibraryEx32W(fileName, NULL, 0);
#endif
#ifdef lassma
	if (_Module == NULL) {
		ErrMessage("Failed to load module %s", fileName);
	}
#endif
}

TGenericThunk::~TGenericThunk ()
{
	Message("Destroy thunk");
	if (_Module != NULL) {
		Message("Free library");
		FreeLibrary32W(_Module);
	} else {
		ErrMessage("No module instance in destructor");
	}
}

HPROC32 TGenericThunk::GetProcAddr32 (const char * procName)
{
	Message("Get address of %s", procName);
	if (_Module != NULL) {
		return (HPROC32)GetProcAddress32W(_Module, procName);
	} else {
		ErrMessage("No module instance in get proc addr");
		return NULL;
	}
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
DWORD __cdecl TGenericThunk::CallProc32(HPROC32 hProc, DWORD fAddrCvt,
													 DWORD nArgs, ...)
{
Message("CallProc32 %p,%ld,%ld", hProc, fAddrCvt, nArgs);
	va_list args;
	DWORD params[32] = {0};
Message("1");
#ifdef LOAD_KERNEL_ADRESSES
	if (_CallProc32W == NULL) {
		ErrMessage("No address for function CallProc32W");
		return -1000;
	}
#endif
	va_start (args, nArgs);
Message("2");
	for (DWORD n = nArgs; n; ) {
#ifdef lassma
		dwTemp = va_arg (args, DWORD);
		--n;
		__asm push word ptr [dwTemp+2];
		__asm push word ptr [dwTemp];
#endif
Message("3");
		--n;
		params[n] = va_arg(args, DWORD);
	}
Message("4");
	va_end (args);
Message("5");
Message("Calling %p (%p, %p): %ld, %ld", hProc, params[1], params[0], CPEX_DEST_STDCALL | nArgs, fAddrCvt);
#ifdef LOAD_KERNEL_ADRESSES
	return _CallProc32W(hProc, fAddrCvt, nArgs);
#else
return CallProc32W(params[1], params[0], hProc, fAddrCvt, CPEX_DEST_STDCALL | nArgs);
return -2000;
#endif
}

DWORD __cdecl TGenericThunk::CallFunc32(const char * input, const char * output,
													 HPROC32 proc, DWORD param_flags, DWORD argc)
{
Message("Carrier(%s, %s)", input, output);
Message("Calling %p (%p, %p): %ld, %ld", proc, (DWORD)input, (DWORD)output, argc, param_flags);
	return CallProc32W((DWORD)input, (DWORD)output, proc, param_flags, argc);
}

////////////////////////////////////////////////////////////////////////////
//  This method returns the 32-bit address for the specified 16:16 address
//  and size.
//
DWORD TGenericThunk::GetVdmPtr16 (void far *buffer, unsigned cbSize)
{
	return GetVDMPointer32W ? GetVDMPointer32W (buffer, cbSize) : 0;
}


////////////////////////////////////////////////////////////////////////////
//  This method will allocate a 16:16 pointer that points at the specified
//  32-bit memory address range.  This pointer must be released by calling
//  FreeVdmPtr32.
//
void far * TGenericThunk::GetVdmPtr32 (DWORD dwAddr32, DWORD cbSize)
{
	UINT  uSelector = ::AllocSelector (_DS); // our DS (for access rights)
	if (uSelector) {
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
	if (SELECTOROF(ptr)) ::FreeSelector (SELECTOROF (ptr));
}

void TGenericThunk::SetModule(HINSTANCE32 module)
{
	_Module = module;
	Message("Module set to %p", _Module);
}

void Message(const char * fmt, ... )
{
   va_list args;
   char text[1024] = {0};
   va_start(args, fmt);
   vsprintf(text, fmt, args);
   va_end(args);
   MessageBox(NULL, text, "Thunk Dll", MB_OK);
}

void ErrMessage(const char * fmt, ...)
{
   va_list args;
   char text[1024] = {0};
   va_start(args, fmt);
   vsprintf(text, fmt, args);
   va_end(args);
   MessageBox(NULL, text, "Error in Thunk Dll", MB_OK);
}

