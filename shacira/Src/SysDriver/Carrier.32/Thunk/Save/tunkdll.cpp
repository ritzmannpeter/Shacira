
#include "Thunk.h"

class cCarrierThunk : public TGenericThunk
{
public:
	cCarrierThunk() : TGenericThunk ("cardll32")
		, _Carrier(NULL), _FileInfo(NULL)
	{
	};
	long Carrier(char * input, char * output);
	long FileInfo(const char * path, void * file_info);
 private:
	HPROC32 _Carrier;
	HPROC32 _FileInfo;
};

long cCarrierThunk::Carrier(char * input, char * output)
{
	if (_Carrier == NULL) _Carrier = GetProcAddr32("Carrier");
	if (_Carrier != NULL) {
		Message("%s", input);
		long rc = CallFunc32(input, output, _Carrier, PAR(1)|PAR(2), 2);
		Message("%s: %d", output, rc);
		return rc;
	} else {
		ErrMessage("No address for function _Carrier");
		return -1001;
	}
};

long cCarrierThunk::FileInfo(const char * path, void * file_info)
{
	if (_FileInfo == NULL) _FileInfo = GetProcAddr32("CARRIER_FileInfo");
	if (_FileInfo != NULL) {
		Message("%s", path);
		long rc = CallProc32(_FileInfo, PAR(1)|PAR(2), 2, path, file_info);
		Message("%d", rc);
		return rc;
	} else {
		ErrMessage("No address for function _Carrier");
		return -1002;
	}
};

cCarrierThunk _Thunk;

extern "C" {

static DWORD _Module = 0;

static int Active()
{
	if (_Module == 0) {
		Message("loading cardll32.dll");
		_Module = LoadLibraryEx32W("cardll32.dll", NULL, 0);
		if (_Module == 0) {
			ErrMessage("Failed to load cardll32.dll");
			return 0;
		}
		Message("Setting module to %p", _Module);
		_Thunk.SetModule(_Module);
		Message("cardll32.dll loaded");
	}
	return 0;
}

int extern __export FAR PASCAL Carrier(char * input, char * output)
{
	Active();
	return (int)_Thunk.Carrier(input, output);
}

int extern __export FAR PASCAL _export CARRIER_FileInfo(char * path, void * file_info)
{
	Active();
Message("call file info");
	return (int)_Thunk.FileInfo(path, file_info);
}

}

int FAR PASCAL LibMain(HANDLE hInstance, WORD wDataSeg, WORD wHeapSize,
							  LPSTR lpszCmdLine )
{
	return 1;
}



