
#ifndef __cardrvW2K__
#define __cardrvW2K__

/*.SI.***********************************************************************/

#include <ntddk.h>
#include "CarCtl.h"
#include "Carrier.h"

/*.EI.***********************************************************************/

#define PORTIO_TAG 'TROP'

#define MAX_DEV_NAME_LEN  64

typedef struct _LOCAL_DEVICE_INFO {
    void * Ccb;
    unsigned long SeekPos;
    long LastError;
    KTIMER WaitTimer;

    BOOLEAN PortWasMapped;  // If TRUE, we have to unmap on unload
    PVOID PortBase;       // base port address
    ULONG PortCount;      // Count of I/O addresses used.
    ULONG PortMemoryType; // HalTranslateBusAddress MemoryType
    PDEVICE_OBJECT DeviceObject;   // The Gpd device object.
    PDEVICE_OBJECT NextLowerDriver;     // The top of the stack
    BOOLEAN Started;
    BOOLEAN Removed;
    IO_REMOVE_LOCK      RemoveLock;
} LOCAL_DEVICE_INFO, *PLOCAL_DEVICE_INFO;

#if DBG

#define DebugPrint(_x_) \
               DbgPrint ("PortIo:"); \
               DbgPrint _x_;
#define TRAP() DbgBreakPoint()

#else

#define DebugPrint(_x_)
#define TRAP()

#endif

#endif /* __cardrvW2K__ */

