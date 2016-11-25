
// Der folgende ifdef-Block zeigt die Standardlösung zur Erstellung von Makros, die das Exportieren 
// aus einer DLL vereinfachen. Alle Dateien in dieser DLL wurden mit dem in der Befehlszeile definierten
// Symbol CARDLL32_EXPORTS kompiliert. Dieses Symbol sollte für kein Projekt definiert werden, das
// diese DLL verwendet. Auf diese Weise betrachtet jedes andere Projekt, dessen Quellcodedateien diese Datei 
// einbeziehen, CARDLL32_API-Funktionen als aus einer DLL importiert, während diese DLL mit diesem 
// Makro definierte Symbole als exportiert betrachtet.

#include <windows.h>

#ifdef CARDLL32_EXPORTS
#define CARDLL32_API __declspec(dllexport)
#else
#define CARDLL32_API __declspec(dllimport)
#endif

#include "carfunc.h"
#include "caritf.h"

#ifdef __cplusplus
extern "C" {
#endif

CARDLL32_API int CARRIER_FileInfo(char * path, FILE_INFO * file_info);
CARDLL32_API int CARRIER_SetTime(char * path);
CARDLL32_API int CARRIER_SetRegVal(char * path, long regid, int index, long value);
CARDLL32_API int CARRIER_GetRegVal(char * path, long regid, int index, long * value);
CARDLL32_API int CARRIER_SetData(char * path, char * artno, char * matno, char * toolno);
CARDLL32_API int Carrier(LPSTR input, LPSTR output);

CARDLL32_API HANDLE CAR_Open();
CARDLL32_API void CAR_Close(HANDLE hnd);
CARDLL32_API long CAR_SetParam(HANDLE hnd, const char * param_name, long param_value);
CARDLL32_API long CAR_GetParam(HANDLE hnd, const char * param_name, long * param_value);
CARDLL32_API long CAR_Check(HANDLE hnd);
CARDLL32_API long CAR_Read(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long bufsize, unsigned long amount);
CARDLL32_API long CAR_Write(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long amount);

#ifdef __cplusplus
}
#endif

