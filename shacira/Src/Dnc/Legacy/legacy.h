
#ifndef _legacy
#define _legacy

#if _MSC_VER >= 1100

#if !defined(__WIN32__)
#define __WIN32__
#endif

#define __MSCPP__               // internal define

#if !defined(__x86__)
#define __x86__
#endif

#define PACKED

#define __PLATFORM_DEFINED__

#else

#error "unsupported compiler"

#endif

#include "errcode.h"
#include "iqtdev.h"
#include "devdisk.h"
#include "fmfat.h"
#include "fmt2.h"
#include "fmt1.h"
#include "fx25.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DRIVE_NO     DISK_DRV_EEP1

#define MAX_FMT2_FILES  3

#define MIN_HEADER_LEN	78
#define MAX_HEADER_LEN	252

long CarrierPos(int fileno, int object);
USR_BYTE Checksum(USR_BYTE * buffer, int src, int offs);
int FMT2_TestChecksum();
int FMT2_2F_TestChecksum();
int FMT2_3F_TestChecksum();
int DeviceError(int hnd);

#ifdef __cplusplus
}
#endif

#endif /* _legacy */
