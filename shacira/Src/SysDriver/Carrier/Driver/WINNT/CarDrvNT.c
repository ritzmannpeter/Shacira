
//
// Embedding layer for Windows NT kernel mode
//

#include "CarDrvNT.h"

static CCB * Ccb = NULL;

//
// Implementation of environment specific functions
// that are needed by Carrier functions
//

void Wait(unsigned long ms)
{
   PLOCAL_DEVICE_INFO ldi = NULL;
   if (Ccb == NULL) return;
   ldi = Ccb->DriverContext;
   if (ldi == NULL) return;
   KeSetTimer(&ldi->WaitTimer,
              RtlConvertLongToLargeInteger(ms * -10000),  // Time in 100 nsec
              NULL );
   KeWaitForSingleObject (&ldi->WaitTimer, Executive, KernelMode, FALSE, 0);
}

unsigned char Inport(unsigned short port)
{
   return READ_PORT_UCHAR((unsigned char *)port);
}

void Outport(unsigned short port, unsigned char value)
{ 
   WRITE_PORT_UCHAR((unsigned char *)port, value);
}

/****************************************************************************
                          Forward declarations
****************************************************************************/

NTSTATUS DriverEntry (IN PDRIVER_OBJECT driver_object, 
                      IN PUNICODE_STRING registry_path);
NTSTATUS CarrierCreate(IN PDRIVER_OBJECT driver_object,
                       IN PUNICODE_STRING registry_path);
VOID CarrierRelease(IN PDRIVER_OBJECT driver_object);
VOID CarrierUnload(IN PDRIVER_OBJECT driver_object);
VOID CarrierDeviceIO(IN PDEVICE_OBJECT device_object, IN PIRP irp);
NTSTATUS DispatchOpenClose(IN PDEVICE_OBJECT device_object, IN PIRP irp);
NTSTATUS DispatchWrite(IN PDEVICE_OBJECT device_object, IN PIRP irp);
NTSTATUS DispatchRead(IN PDEVICE_OBJECT device_object, IN PIRP irp);
NTSTATUS DispatchIoctl(IN PDEVICE_OBJECT device_object, IN PIRP irp);
NTSTATUS CarrierRead(IN PLOCAL_DEVICE_INFO ldi,
                     IN PIRP irp,
                     IN PIO_STACK_LOCATION stack);
NTSTATUS CarrierWrite(IN PLOCAL_DEVICE_INFO ldi,
                      IN PIRP irp,
                      IN PIO_STACK_LOCATION stack);
NTSTATUS CarrierDeviceControl(IN PLOCAL_DEVICE_INFO ldi,
                              IN PIRP irp,
                              IN PIO_STACK_LOCATION stack,
                              IN ULONG ctl_code);

// If the compiler can handle it, make all possible
// routines discardable, so that they doesn't waste space
#ifdef ALLOC_PRAGMA
#pragma alloc_text( init, DriverEntry )
#pragma alloc_text( init, CarrierCreate )
#pragma alloc_text( page, CarrierUnload )
#pragma alloc_text( page, CarrierRelease )
#pragma alloc_text( page, DispatchOpenClose )
#pragma alloc_text( page, DispatchWrite )
#pragma alloc_text( page, DispatchRead )
#pragma alloc_text( page, DispatchIoctl )
#endif // ALLOC_PRAGMA

/****************************************************************************
                         Local helper functions
****************************************************************************/

static BOOLEAN TranslatePortBase (PLOCAL_DEVICE_INFO ldi,
                                  unsigned int original_port,
                                  unsigned int *translated_port)
{
   ULONG sizeOfResourceList = 0;
   PCM_RESOURCE_LIST resourceList = NULL;
   PCM_PARTIAL_RESOURCE_DESCRIPTOR partial;
   BOOLEAN conflictDetected = TRUE;
   PHYSICAL_ADDRESS translatedIoPort;
   ULONG uAddressSpace = 1;
   NTSTATUS status = STATUS_SUCCESS;

   // Alloc enough memory to build a resource list & zero it out
   sizeOfResourceList = sizeof(CM_RESOURCE_LIST) +
                        (sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR));
   resourceList = ExAllocatePool (PagedPool, sizeOfResourceList);
   if (!resourceList) return FALSE;  // Cannot build resource list
   RtlZeroMemory (resourceList, sizeOfResourceList);

   // Fill in the reosurce list assume Isa, bus # 0
   resourceList->Count = 1;
   resourceList->List[0].InterfaceType = Isa;
   resourceList->List[0].BusNumber     = 0;
   resourceList->List[0].PartialResourceList.Count = 1;

   partial = &resourceList->List[0].PartialResourceList.PartialDescriptors[0];
   // allocate ports for the carrier controler
   partial->Type = CmResourceTypePort;
   partial->ShareDisposition = CmResourceShareDriverExclusive;
   partial->Flags = CM_RESOURCE_PORT_IO;
   partial->u.Port.Start.LowPart = original_port;
   partial->u.Port.Start.HighPart = 0;
   partial->u.Port.Length = 6;

   status = IoReportResourceUsage(NULL,
                                  ldi->DeviceObject->DriverObject,
                                  resourceList,         // resource for whole driver
                                  sizeOfResourceList,
                                  ldi->DeviceObject,
                                  NULL,                 // no resource for device
                                  0,
                                  FALSE,                // don't override if in use
                                  &conflictDetected);
   if (resourceList) {
       ExFreePool (resourceList);
       if (!NT_SUCCESS( status ) || conflictDetected) return FALSE;
   }
   if (!HalTranslateBusAddress(Isa, 0,
                               partial->u.Port.Start,
                               &uAddressSpace,
                               &translatedIoPort)) return FALSE;
   *translated_port = translatedIoPort.LowPart;
   return TRUE;
}

/****************************************************************************
                           Main Driver Fuction
 ****************************************************************************/

NTSTATUS DriverEntry (IN PDRIVER_OBJECT driver_object, 
                      IN PUNICODE_STRING registry_path)
{
   NTSTATUS status = STATUS_SUCCESS;

   // Export other driver entry points...
   driver_object->DriverStartIo = CarrierDeviceIO;
   driver_object->DriverUnload = CarrierUnload;
   driver_object->MajorFunction[IRP_MJ_CREATE] = DispatchOpenClose;
   driver_object->MajorFunction[IRP_MJ_CLOSE] = DispatchOpenClose;
   driver_object->MajorFunction[IRP_MJ_WRITE] = DispatchWrite;
   driver_object->MajorFunction[IRP_MJ_READ] = DispatchRead;
   driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchIoctl;

   // Initialize a device object (there is only one device for the driver)
   status = CarrierCreate(driver_object, registry_path);
   if (NT_SUCCESS(status)) {
      return STATUS_SUCCESS;
   } else {
      return status;
   }
}

/****************************************************************************
                          dispatcher functions
 ****************************************************************************/

NTSTATUS DispatchOpenClose(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
   // Initialize state variables of the device
   PLOCAL_DEVICE_INFO ldi = device_object->DeviceExtension;
   ldi->SeekPos = 0L;
   irp->IoStatus.Status = STATUS_SUCCESS;
   irp->IoStatus.Information = 0;
   IoCompleteRequest( irp, IO_NO_INCREMENT );
   return STATUS_SUCCESS;
}

NTSTATUS DispatchWrite(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
   // Start device operation (sequentialize access)
   IoMarkIrpPending(irp);
   IoStartPacket(device_object, irp, 0, NULL);
   return STATUS_PENDING;
}

NTSTATUS DispatchRead(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
   // Start device operation (sequentialize access)
   IoMarkIrpPending(irp);
   IoStartPacket(device_object, irp, 0, NULL);
   return STATUS_PENDING;
}

NTSTATUS DispatchIoctl(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
   // Start device operation (sequentialize access)
   IoMarkIrpPending(irp);
   IoStartPacket(device_object, irp, 0, NULL);
   return STATUS_PENDING;
}

static VOID CarrierDeviceIO(IN PDEVICE_OBJECT device_object, IN PIRP irp)
{
   NTSTATUS status = STATUS_SUCCESS;
   PLOCAL_DEVICE_INFO ldi = device_object->DeviceExtension;
   PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);
   switch (stack->MajorFunction) {
   case IRP_MJ_CREATE:
      break;
   case IRP_MJ_CLOSE:
      break;
   case IRP_MJ_WRITE:
      status = CarrierWrite(ldi, irp, stack);
      break;
   case IRP_MJ_READ:
      status = CarrierRead(ldi, irp, stack);
      break;
   case IRP_MJ_DEVICE_CONTROL:
      status = CarrierDeviceControl(ldi, irp, stack,
                                    stack->Parameters.DeviceIoControl.IoControlCode);
      break;
   default:
      status = STATUS_NOT_SUPPORTED;
   }
   irp->IoStatus.Status = status;
   IoCompleteRequest(irp, IO_SERIAL_INCREMENT);
   IoStartNextPacket(device_object, FALSE);
}

NTSTATUS CarrierDeviceControl(IN PLOCAL_DEVICE_INFO ldi,
                              IN PIRP irp,
                              IN PIO_STACK_LOCATION stack,
                              IN ULONG ctl_code)
{
    CARRIER_CTL_STRUCT carctl = {0};
    void * ccb = Ccb;
    unsigned long check_result = 0;
    unsigned long seek_pos = 0;
    char * param_name = NULL;
    long param_value = 0;
    unsigned long address = 0;
    unsigned long amount = 0;
    long rc = 0;
    PULONG io_buf;
    ULONG out_len = 0;
    ULONG inbuf_size;
    ULONG outbuf_size;
    unsigned char * write_buf = NULL;

    PAGED_CODE();

    if (ctl_code != IOCTL_CARRIER_GET_LAST_ERROR) ldi->LastError = 0;
    irp->IoStatus.Information = 0;
    if (ccb == NULL) return STATUS_DEVICE_DOES_NOT_EXIST;
    inbuf_size = stack->Parameters.DeviceIoControl.InputBufferLength;
    outbuf_size = stack->Parameters.DeviceIoControl.OutputBufferLength;
    io_buf = (PULONG)irp->AssociatedIrp.SystemBuffer;
    memcpy(&carctl, io_buf, sizeof(carctl));

    switch (ctl_code) {
    case IOCTL_CARRIER_CHECK:
        rc = check_result = CARRIER_Check(ccb);
        if (rc < 0) {
	   ldi->LastError = rc;
        } else {
	   *(long*)io_buf = check_result;
           out_len = sizeof(long);
	   if (outbuf_size < out_len) return STATUS_INSUFFICIENT_RESOURCES;
        }
        break;
    case IOCTL_CARRIER_GET_PARAM:
        param_name = carctl.pByte;
        rc = CARRIER_GetParam(ccb, param_name, &param_value);
        if (rc < 0) {
	   ldi->LastError = rc;
        } else {
	   *(long*)io_buf = param_value;
           out_len = sizeof(long);
	   if (outbuf_size < out_len) return STATUS_INSUFFICIENT_RESOURCES;
        }
        break;
    case IOCTL_CARRIER_READ:
        address = carctl.Long1;
        amount = carctl.Long2;
        rc = CARRIER_Read(ccb, address, io_buf, inbuf_size, amount);
        if (rc < 0) {
	   ldi->LastError = rc;
        } else {
           out_len = amount;
	   if (outbuf_size < out_len) return STATUS_INSUFFICIENT_RESOURCES;
        }
        break;
    case IOCTL_CARRIER_GET_LAST_ERROR:
        *(long*)io_buf = ldi->LastError;
        out_len = sizeof(long);
	break;
    case IOCTL_CARRIER_SEEK:
	seek_pos = carctl.Long1;
        rc = seek_pos;
        if (rc < 0) {
           ldi->LastError = rc;
        } else {
           *(long*)io_buf = seek_pos;
           out_len = sizeof(long);
           if (outbuf_size < out_len) return STATUS_INSUFFICIENT_RESOURCES;
        }
        break;
    case IOCTL_CARRIER_SET_PARAM:
        param_name = carctl.pByte;
        param_value = carctl.Long1;
        rc = CARRIER_SetParam(ccb, param_name, param_value);
        if (rc < 0) {
           ldi->LastError = rc;
        } else {
           *(long*)io_buf = 0;
           out_len = sizeof(long);
           if (outbuf_size < out_len) return STATUS_INSUFFICIENT_RESOURCES;
        }
        break;
    case IOCTL_CARRIER_WRITE:
        address = carctl.Long1;
        amount = carctl.Long2;
        write_buf = carctl.pByte;
        if (write_buf != NULL) {
	   rc = CARRIER_Write(ccb, address, write_buf, amount);
           if (rc < 0) {
              ldi->LastError = rc;
           } else {
              *(long*)io_buf = amount;
              out_len = sizeof(long);
              if (outbuf_size < out_len) return STATUS_INSUFFICIENT_RESOURCES;
           }
        } else {
           return STATUS_INSUFFICIENT_RESOURCES;
        }
        break;
    default:      
        return STATUS_INVALID_PARAMETER;
    }
    //
    // Indicate # of bytes read
    //
    if (ldi->LastError == 0 ||
        ctl_code == IOCTL_CARRIER_GET_LAST_ERROR) {
       irp->IoStatus.Information = out_len;
    }
    return STATUS_SUCCESS;
}

NTSTATUS CarrierRead(IN PLOCAL_DEVICE_INFO ldi,
                     IN PIRP irp,
                     IN PIO_STACK_LOCATION stack)
{
   return STATUS_NOT_SUPPORTED;
}


NTSTATUS CarrierWrite(IN PLOCAL_DEVICE_INFO ldi,
                      IN PIRP irp,
                      IN PIO_STACK_LOCATION stack)
{
   return STATUS_NOT_SUPPORTED;
}

static ULONG GetPortBase(PUNICODE_STRING registry_path)
{
   NTSTATUS status = STATUS_SUCCESS;
   ULONG port_base = 0x360;
   RTL_QUERY_REGISTRY_TABLE reg_table[10];
   RtlZeroMemory(reg_table, sizeof(reg_table));
   reg_table[0].Name = L"PortBase";
   reg_table[0].Flags = RTL_QUERY_REGISTRY_DIRECT;
   reg_table[0].EntryContext = &port_base;
   status = RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE,
                                   registry_path->Buffer,
                                   reg_table, NULL, NULL);
   if (status == STATUS_SUCCESS) {
      return port_base;
   } else {
      return 0x360;
   }
}

static NTSTATUS CarrierCreate(IN PDRIVER_OBJECT driver_object, IN PUNICODE_STRING registry_path)
{
   NTSTATUS status = STATUS_SUCCESS;
   PDEVICE_OBJECT device_object = NULL;
   PLOCAL_DEVICE_INFO ldi = NULL;
   unsigned int mapped_address = 0;
   UNICODE_STRING device_name;
   WCHAR device_name_buf[MAX_DEV_NAME_LEN];
   UNICODE_STRING link_name;
   WCHAR link_name_buf[MAX_DEV_NAME_LEN];

   device_name.Buffer = device_name_buf;
   device_name.MaximumLength = MAX_DEV_NAME_LEN;
   device_name.Length = 0;
   RtlAppendUnicodeToString(&device_name, CARRIER_NT_DEVICE_NAME);
   
   link_name.Buffer = link_name_buf;
   link_name.MaximumLength = MAX_DEV_NAME_LEN;
   link_name.Length = 0;
   RtlAppendUnicodeToString(&link_name, CARRIER_DOS_DEVICE_NAME);
   
   // Create a Device object for this device...
   status = IoCreateDevice(driver_object,
                           sizeof(LOCAL_DEVICE_INFO),
                           &device_name,
                           CARRIER_DEVICE_TYPE,
                           0,
                           TRUE,
                           &device_object);
   if (!NT_SUCCESS(status)) return status;
   device_object->Flags |= DO_BUFFERED_IO;
   // Initialize the Device Extension
   ldi = device_object->DeviceExtension;
   ldi->DeviceObject = device_object;
   ldi->PortBase = GetPortBase(registry_path);
   if (!TranslatePortBase(ldi, ldi->PortBase, &mapped_address)) {
      return STATUS_INSUFFICIENT_RESOURCES;
   }

   // Initialize the timer, needed for driver waitstates
   KeInitializeTimer( &ldi->WaitTimer );

   if (Ccb == NULL) Ccb = CARRIER_Init(ldi, mapped_address);
   if (Ccb == NULL) {
      IoDeleteDevice( device_object );
      return STATUS_DEVICE_DOES_NOT_EXIST;
   }
   // Create a symbolic link so our device is visible to Win32...
   status = IoCreateSymbolicLink(&link_name, &device_name);
    
    // See if the symbolic link was created...
   if (!NT_SUCCESS(status)) {
      IoDeleteDevice(device_object);
      return status;
   }
   return status;
}

static VOID CarrierUnload(IN PDRIVER_OBJECT driver_object)
{
   CARRIER_Exit(Ccb);
   // Stop interrupt processing and release hardware
   CarrierRelease(driver_object);
}

static VOID CarrierRelease(IN PDRIVER_OBJECT driver_object)
{
   PDEVICE_OBJECT device_object = NULL;
   PLOCAL_DEVICE_INFO ldi = NULL;
   UNICODE_STRING link_name;
   WCHAR link_name_buf[MAX_DEV_NAME_LEN];
   CM_RESOURCE_LIST res_list;
   BOOLEAN conflicts = FALSE;

   device_object = driver_object->DeviceObject;
   ldi = device_object->DeviceExtension;

   // Deallocate hardware resources owned by the Device object...
   res_list.Count = 0;
   IoReportResourceUsage(NULL,
                         driver_object,
                         NULL,
                         0,
                         device_object,
                         &res_list,
                         sizeof(res_list),
                         FALSE,
                         &conflicts);

   // Form the Win32 symbolic link name.
   link_name.Buffer = link_name_buf;
   link_name.MaximumLength = MAX_DEV_NAME_LEN;
   link_name.Length = 0;

   RtlAppendUnicodeToString(&link_name, CARRIER_DOS_DEVICE_NAME);
   // Remove symbolic link from Object namespace...
   IoDeleteSymbolicLink(&link_name);
   // Get rid of the device object
   IoDeleteDevice(device_object);
}
