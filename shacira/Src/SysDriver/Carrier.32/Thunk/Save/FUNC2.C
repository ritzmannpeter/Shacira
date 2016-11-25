
#include "thunkdll.h"

typedef void (FAR PASCAL * FILEINFO)(LPSTR, LPVOID);
static FILEINFO Proc = NULL;
DWORD FAR PASCAL CallProc32W(DWORD, DWORD, LPVOID, DWORD, DWORD);

int extern __export FAR PASCAL _export CARRIER_FileInfo(char * path, void * file_info)
{
	DWORD err = 0;
	Message("CARRIER_FileInfo");
	if (Proc == NULL) {
		if ((Proc = (FILEINFO)GetProcAddress32W(_Module, "CARRIER_FileInfo")) == NULL) {
			ErrMessage( "failed to get address of function CARRIER_FileInfo");
			return -1001;
		}
	}
	Message("calling now");
	err = CallProc32W((DWORD)path, (DWORD)file_info,
							Proc,
							PARAM_01 | PARAM_02,
							CPEX_DEST_STDCALL | 2);
	return err;
}


