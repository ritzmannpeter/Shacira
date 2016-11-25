#include "thunkdll.h"

typedef void (FAR PASCAL * CARRIER)(LPSTR, LPSTR);
static CARRIER Proc = NULL;
DWORD FAR PASCAL CallProc32W(DWORD, DWORD, LPVOID, DWORD, DWORD);

int extern __export FAR PASCAL Carrier(char * input, char * output)
{
	DWORD err = 0;
	Message("Carrier");
	if (Proc == NULL) {
		if ((Proc = (CARRIER)GetProcAddress32W(LibHandle, "Carrier")) == NULL) {
			ErrMessage( "failed to get address of function Carrier");
			return -1001;
		}
	}
Message("Calling %p (%p, %p): %ld, %ld", Proc, (DWORD)input, (DWORD)output, (DWORD)(CPEX_DEST_STDCALL | 2), (DWORD)(PARAM_01 | PARAM_02));
	err = CallProc32W((DWORD)input, (DWORD)output,
							Proc,
							PARAM_01 | PARAM_02,
							CPEX_DEST_STDCALL | 2);
	return err;
}




