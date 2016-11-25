/*.SM.****************************************************************
*
*  MODUL-NAME: DEVIO.H
*
*  BESCHREIBUNG:
*     Plattformunabhaengige Definitionen zum Zugriff auf Geraete
*
*  HISTORY:
*     25.05.98 -TSchw-  READ_ACCESS, WRITE_ACCESS und READWRITE_ACCESS
*                       plattformabhaengig eingefuehrt
*
*.EM.***********************************************************************/

#ifndef __devio__
#define __devio__

#if defined(__QNXNTO__)

#include <errno.h>
#include <unistd.h>
#include <devctl.h>
#include <fcntl.h>
#include <stypes.h>

typedef int HANDLE_T;
typedef int STATUS_T;
typedef unsigned long USR_LONG;
typedef unsigned long FLAGS_T;
typedef int DEVCTL_CMD_T;
#define INV_HANDLE -1
#define HANDLE_OK(h) ((h)!=INV_HANDLE)

#define READ_ACCESS        O_RDONLY
#define WRITE_ACCESS       O_WRONLY
#define READWRITE_ACCESS   O_RDWR

#elif defined(__LINUX__)

#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stypes.h>

typedef int HANDLE_T;
typedef int STATUS_T;
typedef unsigned long USR_LONG;
typedef unsigned long FLAGS_T;
typedef int DEVCTL_CMD_T;
#define INV_HANDLE -1
#define HANDLE_OK(h) ((h)!=INV_HANDLE)

#define READ_ACCESS        O_RDONLY
#define WRITE_ACCESS       O_WRONLY
#define READWRITE_ACCESS   O_RDWR

#elif defined __QNX4__

#include <errno.h>
#include <unistd.h>
#include <sys/qioctl.h>
#include <fcntl.h>

typedef int HANDLE_T;
typedef int STATUS_T;
typedef unsigned long USR_LONG;
typedef unsigned long FLAGS_T;
typedef int DEVCTL_CMD_T;
#define INV_HANDLE -1
#define HANDLE_OK(h) ((h)!=INV_HANDLE)

#define READ_ACCESS        O_RDONLY
#define WRITE_ACCESS       O_WRONLY
#define READWRITE_ACCESS   O_RDWR

#elif defined __WIN32__

#include <windows.h>
//#include <winbase.h>
typedef HANDLE HANDLE_T;
typedef int STATUS_T;
typedef DWORD SIZE_T;
typedef unsigned long USR_LONG;
typedef unsigned long FLAGS_T;
typedef int DEVCTL_CMD_T;
#define INV_HANDLE INVALID_HANDLE_VALUE
#define HANDLE_OK(h) ((h)!=INV_HANDLE)

#define READ_ACCESS        GENERIC_READ
#define WRITE_ACCESS       GENERIC_WRITE
#define READWRITE_ACCESS   GENERIC_READ|GENERIC_WRITE

#endif

GLOBAL HANDLE_T DeviceOpen(char * device_name, USR_LONG flags);
GLOBAL STATUS_T DeviceClose(HANDLE_T handle);
GLOBAL SIZE_T DeviceRead(HANDLE_T handle, void * buffer, SIZE_T len);
GLOBAL SIZE_T DeviceWrite(HANDLE_T handle, const void * buffer, SIZE_T len);
GLOBAL STATUS_T DeviceControl(HANDLE_T handle, DEVCTL_CMD_T cmd,
										void * in_data, SIZE_T in_data_len,
										void * out_data, SIZE_T out_data_len);
GLOBAL void DeviceName(const char * format, int no, void * buffer);
GLOBAL int DeviceNo(const char * format, char * name);

#endif /* __devio__ */

