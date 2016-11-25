
#ifndef __cardrvNT__
#define __cardrvNT__

/*.SI.***********************************************************************/

#include <ntddk.h>
#include "CarCtl.h"
#include "Carrier.h"

/*.EI.***********************************************************************/

#define MAX_DEV_NAME_LEN  64

typedef struct _LOCAL_DEVICE_INFO {
    void * Ccb;
    unsigned long SeekPos;
    long LastError;
    KTIMER WaitTimer;

    ULONG PortBase;
    PDEVICE_OBJECT DeviceObject;
    PDEVICE_OBJECT NextLowerDriver; // The top of the stack
    BOOLEAN Started;
    BOOLEAN Removed;
// W2K   IO_REMOVE_LOCK RemoveLock;
} LOCAL_DEVICE_INFO, *PLOCAL_DEVICE_INFO;

#endif /* __cardrvNT__ */

