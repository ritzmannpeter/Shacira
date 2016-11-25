
#ifndef __THUNK_H
#define __THUNK_H

#include <windows.h>
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
extern "C" {
#include <wownt16.h>
}

#define PAR(pos) (0x00000001 << (pos-1))

void Message(const char * fmt, ... );
void ErrMessage(const char * fmt, ...);

#undef LOAD_KERNEL_ADRESSES

#define HPROC32 LPVOID
#define HINSTANCE32 DWORD
#define bool BOOL

class TGenericThunk
{
	 public:
		  ~TGenericThunk ();
		  bool IsOK() const {return _Module != NULL; }
		  void SetModule(HINSTANCE32 module);

	 protected:
		  TGenericThunk (const char * fileName);
		  DWORD __cdecl CallProc32    (HPROC32, DWORD fAddrCvt, DWORD nArgs, ...);
		  DWORD __cdecl CallFunc32(const char * input, const char * output,
											HPROC32 proc, DWORD param_flags, DWORD argc);
		  void          FreeVdmPtr32  (void far *);
		  HPROC32       GetProcAddr32 (const char * procName);
		  DWORD         GetVdmPtr16   (void far *buffer, unsigned cbSize);
		  void far *    GetVdmPtr32   (DWORD dwAddr32, DWORD cbSize);
		  HINSTANCE32   GetInstance   () const { return _Module; }
	 private:
		  HINSTANCE32 _Module;
#ifdef LOAD_KERNEL_ADRESSES
		  static HINSTANCE32 (WINAPI *_LoadLibraryEx32W) (LPCSTR, DWORD, DWORD);
		  static BOOL        (WINAPI *_FreeLibrary32W)   (HINSTANCE32);
		  static HPROC32     (WINAPI *_GetProcAddress32W)(HINSTANCE32, LPCSTR);
		  static DWORD       (WINAPI *_GetVDMPointer32W) (LPVOID, UINT);
		  static DWORD       (WINAPI *_CallProc32W)      (HPROC32, DWORD, DWORD);
#endif
};

#endif  // __THUNK_H

