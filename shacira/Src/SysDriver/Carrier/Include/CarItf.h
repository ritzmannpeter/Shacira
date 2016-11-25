
#ifndef __caritf__
#define __caritf__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "CarCtl.h"
#include "Carrier.h"

#define CARRIER_DEVICE  "\\\\.\\Carrier"
#define CARRIER_VXD     "\\\\.\\Carrier.vxd"

HANDLE CARITF_Open();
void CARITF_Close(HANDLE hnd);
long CARITF_SetParam(HANDLE hnd, const char * param_name, long param_value);
long CARITF_GetParam(HANDLE hnd, const char * param_name, long * param_value);
long CARITF_Check(HANDLE hnd);
long CARITF_Read(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long bufsize, unsigned long amount);
long CARITF_Write(HANDLE hnd, unsigned long address, unsigned char * buf, unsigned long amount);
char * CarrierName(void);

// Interface errors

#define CARITF_NO_DEVICE_NAME    -100
#define CARITF_OPEN_DEVICE       -101
#define CARITF_DEVICE_NOT_OPEN   -102
#define CARITF_DEVICE_NOT_INITIALIZED  -103
#define CARITF_IOCTL_ERROR       -104

#ifdef __cplusplus
}
#endif

#endif /*__caritf__*/


