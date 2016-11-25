// CarDll32.cpp : Definiert den Einsprungpunkt für die DLL-Anwendung.
//

#include "CarDll32.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

// exported functions

CARDLL32_API int CARRIER_FileInfo(char * path, FILE_INFO * file_info)
{
   return _CARRIER_FileInfo(path, file_info);
}

CARDLL32_API int CARRIER_SetTime(char * path)
{
  return _CARRIER_SetTime(path);
}

CARDLL32_API int CARRIER_SetRegVal(char * path, long regid, int index, long value)
{
   return _CARRIER_SetRegVal(path, regid, index, value);
}

CARDLL32_API int CARRIER_GetRegVal(char * path, long regid, int index, long * value)
{
   return _CARRIER_GetRegVal(path, regid, index, value);
}

CARDLL32_API int CARRIER_SetData(char * path, char * artno, char * matno, char * toolno)
{
   return _CARRIER_SetData(path, artno, matno, toolno);
}

CARDLL32_API int Carrier(LPSTR input, LPSTR output)
{
   return _Carrier(input, output);
}

CARDLL32_API HANDLE CAR_Open()
{
   return CARITF_Open();
}

CARDLL32_API void CAR_Close(HANDLE hnd)
{
   CARITF_Close(hnd);
}

CARDLL32_API long CAR_SetParam(HANDLE hnd, const char * param_name, long param_value)
{
   return CARITF_SetParam(hnd, param_name, param_value);
}

CARDLL32_API long CAR_GetParam(HANDLE hnd, const char * param_name, long * param_value)
{
   return CARITF_GetParam(hnd, param_name, param_value);
}

CARDLL32_API long CAR_Check(HANDLE hnd)
{
   return CARITF_Check(hnd);
}

CARDLL32_API long CAR_Read(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long bufsize, unsigned long amount)
{
   return CARITF_Read(hnd, address, buf, bufsize, amount);
}

CARDLL32_API long CAR_Write(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long amount)
{
   return CARITF_Write(hnd, address, buf, amount);
}


