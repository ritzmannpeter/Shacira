
#include "thunkmod.h"
#include "thunkdll.h"
#include "stdarg.h"

#undef VERBOSE

void Message(const char * fmt, ... )
{
#ifdef VERBOSE
	va_list args;
	char text[1024] = {0};
	va_start(args, fmt);
	vsprintf(text, fmt, args);
	va_end(args);
	MessageBox(NULL, text, "Thunk Dll", MB_OK);
#endif
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

DWORD _Module = 0;

int FAR PASCAL LibMain(HANDLE hInstance, WORD wDataSeg, WORD wHeapSize,
							  LPSTR lpszCmdLine )
{
//	Message("loading Cardll32.dll");
	_Module = LoadLibraryEx32W("cardll32.dll", NULL, 0);
	if (_Module == NULL) {
		ErrMessage("Failed to load cardll32.dll");
		return 0;
	}
//	Message("Cardll32.dll loaded");
	return 1;
}

void FreeRessources()
{
//	Message("Free ressources");
	if (_Module != NULL) {
		Message("Free module");
		FreeLibrary32W(_Module);
		_Module = NULL;
	}
}

// exported functions

DWORD FAR PASCAL CallProc32W(DWORD, DWORD, LPVOID, DWORD, DWORD);

#define _CHECK_MODULE_ \
if (_Module == NULL) { \
	ErrMessage("No module available"); \
	return -1000; \
}

typedef void (FAR PASCAL * CARRIER)(LPSTR, LPSTR);
static CARRIER _Carrier = NULL;
int __export FAR PASCAL Carrier(char * input, char * output)
{
	DWORD err = 0;
_CHECK_MODULE_
	if (_Carrier == NULL) {
		if ((_Carrier = (CARRIER)GetProcAddress32W(_Module, "Carrier")) == NULL) {
			ErrMessage( "Failed to get address of function Carrier");
			return -1001;
		}
	}
//	Message("Calling %p (%p, %p): %ld, %ld", _Carrier, (DWORD)input, (DWORD)output, (DWORD)(CPEX_DEST_STDCALL | 2), (DWORD)(PARAM_01 | PARAM_02));
	err = CallProc32W((DWORD)input, (DWORD)output,
							(LPVOID)_Carrier,
							(DWORD)(PARAM_01 | PARAM_02),
							(DWORD)(CPEX_DEST_STDCALL | 2));
//	Message("Calling %p (%p: %s, %p: %s): %ld, %ld", _Carrier, (DWORD)input, (DWORD)input, (DWORD)output, (DWORD)output, (DWORD)(CPEX_DEST_STDCALL | 2), (DWORD)(PARAM_01 | PARAM_02));
	return err;
}

typedef void (FAR PASCAL * FILE_INFO)(LPSTR, LPVOID);
static FILE_INFO _FileInfo = NULL;
int __export FAR PASCAL _export CARRIER_FileInfo(char * path, void * file_info)
{
	DWORD err = 0;
_CHECK_MODULE_
//	Message("CARRIER_FileInfo");
	if (_FileInfo == NULL) {
		if ((_FileInfo = (FILE_INFO)GetProcAddress32W(_Module, "CARRIER_FileInfo")) == NULL) {
			ErrMessage( "Failed to get address of function CARRIER_FileInfo");
			return -1002;
		}
	}
//	Message("Calling %p (%p, %p): %ld, %ld", _FileInfo, (DWORD)path, (DWORD)file_info, (DWORD)(CPEX_DEST_STDCALL | 2), (DWORD)(PARAM_01 | PARAM_02));
	err = CallProc32W((DWORD)path, (DWORD)file_info,
							(LPVOID)_FileInfo,
							(DWORD)(PARAM_01 | PARAM_02),
							(DWORD)(CPEX_DEST_STDCALL | 2));
	return err;
}


