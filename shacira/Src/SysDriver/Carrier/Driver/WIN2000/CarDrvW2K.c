//
// Embedding layer for Windows 2000 kernel mode
//

#include "CarDrvW2K.h"

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

NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver_object,
                     IN PUNICODE_STRING registry_path);
NTSTATUS CarrierAddDevice(IN PDRIVER_OBJECT driver_object,
                          IN PDEVICE_OBJECT physical_device_object);
NTSTATUS CarrierCompletionRoutine(IN PDEVICE_OBJECT device_object,
                                  IN PIRP irp, IN PVOID context);
NTSTATUS CarrierDispatchPnp(IN PDEVICE_OBJECT device_object,
                            IN PIRP irp);
NTSTATUS CarrierStartDevice (IN PDEVICE_OBJECT device_object,
                             IN PIRP irp);
NTSTATUS CarrierDispatchPower(IN PDEVICE_OBJECT device_object,
                              IN PIRP irp);
NTSTATUS CarrierDispatchSystemControl(IN PDEVICE_OBJECT device_object,
                                      IN PIRP irp);
VOID CarrierUnload(IN PDRIVER_OBJECT driver_object);
NTSTATUS CarrierDispatch(IN PDEVICE_OBJECT device_object,
                         IN PIRP irp);
NTSTATUS CarrierDeviceControl(IN PLOCAL_DEVICE_INFO ldi,
                              IN PIRP irp,
                              IN PIO_STACK_LOCATION stack,
                              IN ULONG ctl_code);
NTSTATUS CarrierRead(IN PLOCAL_DEVICE_INFO ldi,
                     IN PIRP irp,
                     IN PIO_STACK_LOCATION stack);
NTSTATUS CarrierWrite(IN PLOCAL_DEVICE_INFO ldi,
                     IN PIRP irp,
                     IN PIO_STACK_LOCATION stack);

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, CarrierAddDevice)
#pragma alloc_text (PAGE, CarrierDispatchPnp)
#pragma alloc_text (PAGE, CarrierDispatchSystemControl)
#pragma alloc_text (PAGE, CarrierUnload)
#pragma alloc_text (PAGE, CarrierDispatch)
#pragma alloc_text (PAGE, CarrierDeviceControl)
#pragma alloc_text (PAGE, CarrierRead)
#pragma alloc_text (PAGE, CarrierWrite)
#pragma alloc_text (PAGE, CarrierStartDevice)
#endif

NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver_object,
                     IN PUNICODE_STRING registry_path)
{
   UNREFERENCED_PARAMETER (registry_path);

   DebugPrint (("Entered Driver Entry\n"));
    
   driver_object->MajorFunction[IRP_MJ_CREATE] = CarrierDispatch;
   driver_object->MajorFunction[IRP_MJ_CLOSE] = CarrierDispatch;
   driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = CarrierDispatch;
   driver_object->DriverUnload = CarrierUnload;
   driver_object->MajorFunction[IRP_MJ_PNP] = CarrierDispatchPnp;
   driver_object->MajorFunction[IRP_MJ_POWER] = CarrierDispatchPower;
   driver_object->MajorFunction[IRP_MJ_SYSTEM_CONTROL] = CarrierDispatchSystemControl;
   driver_object->DriverExtension->AddDevice = CarrierAddDevice;
   return STATUS_SUCCESS;
}

NTSTATUS CarrierAddDevice(IN PDRIVER_OBJECT driver_object,
                          IN PDEVICE_OBJECT physical_device_object)
{
   NTSTATUS status = STATUS_SUCCESS;
   PDEVICE_OBJECT device_object = NULL;
   PLOCAL_DEVICE_INFO device_info; 
   UNICODE_STRING device_name;
   UNICODE_STRING win32_device_name;

   PAGED_CODE();

   RtlInitUnicodeString(&device_name, CARRIER_NT_DEVICE_NAME);

   status = IoCreateDevice (driver_object,
                            sizeof (LOCAL_DEVICE_INFO),
                            &device_name,
                            CARRIER_DEVICE_TYPE,
                            0,
                            FALSE,
                            &device_object);
   if (!NT_SUCCESS (status)) {
       //
       // Either not enough memory to create a deviceobject or another
       // deviceobject with the same name exits. This could happen
       // if you install another instance of this device.
       //
       return status;
   }

   RtlInitUnicodeString(&win32_device_name, CARRIER_DOS_DEVICE_NAME);

   status = IoCreateSymbolicLink(&win32_device_name, &device_name);
   if (!NT_SUCCESS(status)) {
      IoDeleteDevice(device_object);
       return status;
   }

   device_info = (PLOCAL_DEVICE_INFO) device_object->DeviceExtension;
   device_info->NextLowerDriver =
      IoAttachDeviceToDeviceStack(device_object, physical_device_object);
   if (NULL == device_info->NextLowerDriver) {
      IoDeleteSymbolicLink(&win32_device_name);
      IoDeleteDevice(device_object);
      return STATUS_NO_SUCH_DEVICE;
   }

   IoInitializeRemoveLock(&device_info->RemoveLock, 
                          PORTIO_TAG,
                          1,  // MaxLockedMinutes 
                          5); // HighWatermark, this parameter is 
                              // used only on checked build.
   //
   // Set the flag if the device is not holding a pagefile
   // crashdump file or hibernate file. 
   // 
   device_object->Flags |=  DO_POWER_PAGABLE;
   device_info->DeviceObject = device_object;
   device_info->Removed = FALSE;
   device_info->Started = FALSE;
   device_object->Flags &= ~DO_DEVICE_INITIALIZING;

   //
   // This values is based on the hardware design.
   // Let us assume the address is in I/O space. 
   //
   device_info->PortMemoryType = 1; 

   DebugPrint(("AddDevice: %p to %p->%p \n", device_object, 
                       device_info->NextLowerDriver,
                       physical_device_object));

   return STATUS_SUCCESS;
}

NTSTATUS CarrierCompletionRoutine(IN PDEVICE_OBJECT device_object,
                                  IN PIRP irp, IN PVOID context)
{
   PKEVENT event = (PKEVENT)context;

   UNREFERENCED_PARAMETER(device_object);

   if (irp->PendingReturned) {
       IoMarkIrpPending(irp);
   }

   //
   // We could switch on the major and minor functions of the IRP to perform
   // different functions, but we know that context is an event that needs
   // to be set.
   //
   KeSetEvent(event, 0, FALSE);

   //
   // Allows the caller to reuse the IRP
   //
   return STATUS_MORE_PROCESSING_REQUIRED;
}


NTSTATUS CarrierDispatchPnp(IN PDEVICE_OBJECT device_object,
                            IN PIRP irp)
{
   PIO_STACK_LOCATION stack;
   NTSTATUS status = STATUS_SUCCESS;
   KEVENT event;        
   UNICODE_STRING win32_device_name;
   PLOCAL_DEVICE_INFO device_info;
 
   PAGED_CODE();

   device_info = (PLOCAL_DEVICE_INFO) device_object->DeviceExtension;
   stack = IoGetCurrentIrpStackLocation(irp);

   status = IoAcquireRemoveLock (&device_info->RemoveLock, NULL);
   if (!NT_SUCCESS (status)) {
      irp->IoStatus.Status = status;
      IoCompleteRequest (irp, IO_NO_INCREMENT);
      return status;
   }

   DebugPrint(("%s\n",PnPMinorFunctionString(stack->MinorFunction)));

   switch (stack->MinorFunction) {
   case IRP_MN_START_DEVICE:
        //
        // The device is starting.
        //
        // We cannot touch the device (send it any non pnp irps) until a
        // start device has been passed down to the lower drivers.
        //
        IoCopyCurrentIrpStackLocationToNext(irp);
        KeInitializeEvent(&event, NotificationEvent, FALSE);

        IoSetCompletionRoutine(irp,
                               (PIO_COMPLETION_ROUTINE) CarrierCompletionRoutine, 
                               &event, TRUE, TRUE, TRUE);
                               
        status = IoCallDriver(device_info->NextLowerDriver, irp);
        if (STATUS_PENDING == status) {
           KeWaitForSingleObject(&event,
                                 Executive, // Waiting for reason of a driver
                                 KernelMode, // Must be kernelmode if event memory is in stack
                                 FALSE, // No allert
                                 NULL); // No timeout
        }
        if (NT_SUCCESS(status) && NT_SUCCESS(irp->IoStatus.Status)) {
            status = CarrierStartDevice(device_object, irp);
            if(NT_SUCCESS(status))
            {
                //
                // As we are successfully now back from our start device
                // we can do work.
                //
                device_info->Started = TRUE;
                device_info->Removed = FALSE;
            }
        }
        //
        // We must now complete the IRP, since we stopped it in the
        // completion routine with STATUS_MORE_PROCESSING_REQUIRED.
        //
        irp->IoStatus.Status = status;
        IoCompleteRequest(irp, IO_NO_INCREMENT);
        break;
    case IRP_MN_QUERY_STOP_DEVICE:
        //
        // Fail the query stop to prevent the system from taking away hardware 
        // resources. If you do support this you must have a queue to hold
        // incoming requests between stop and subsequent start with new set of
        // resources.
        //
        irp->IoStatus.Status = status = STATUS_UNSUCCESSFUL;
        IoCompleteRequest(irp, IO_NO_INCREMENT);
        break;
    case IRP_MN_QUERY_REMOVE_DEVICE:
        //
        // The device can be removed without disrupting the machine. 
        //
        irp->IoStatus.Status = STATUS_SUCCESS;
        IoSkipCurrentIrpStackLocation(irp);
        status = IoCallDriver(device_info->NextLowerDriver, irp);
        break;
    case IRP_MN_SURPRISE_REMOVAL:
        //
        // The device has been unexpectedly removed from the machine 
        // and is no longer available for I/O. Stop all access to the device.
        // Release any resources associated with the device, but leave the 
        // device object attached to the device stack until the PnP Manager 
        // sends a subsequent IRP_MN_REMOVE_DEVICE request. 
        // You should fail any outstanding I/O to the device. You will
        // not get a remove until all the handles open to the device
        // have been closed.
        //
        device_info->Removed = TRUE;
        device_info->Started = FALSE;
        //
        // Wait for all outstanding requests to complete
        //

        DebugPrint(("Waiting for outstanding requests\n"));

        IoReleaseRemoveLockAndWait(&device_info->RemoveLock, irp);
        if (device_info->PortWasMapped) {
           MmUnmapIoSpace(device_info->PortBase, device_info->PortCount);
           device_info->PortWasMapped = FALSE;
        }
        RtlInitUnicodeString(&win32_device_name, CARRIER_DOS_DEVICE_NAME);
        IoDeleteSymbolicLink(&win32_device_name);           
        IoSkipCurrentIrpStackLocation(irp);
        status = IoCallDriver(device_info->NextLowerDriver, irp);
        break;       
    case IRP_MN_REMOVE_DEVICE:
        //
        // Relinquish all resources here.
        // Detach and delete the device object so that
        // your driver can be unloaded. You get remove
        // either after query_remove or surprise_remove.
        //
        if (!device_info->Removed) {
           device_info->Removed = TRUE;
           device_info->Started = FALSE;
           //
           // Wait for all outstanding requests to complete
           //

           DebugPrint(("Waiting for outstanding requests\n"));

           IoReleaseRemoveLockAndWait(&device_info->RemoveLock, irp);
           if (device_info->PortWasMapped) {
              MmUnmapIoSpace(device_info->PortBase, device_info->PortCount);
              device_info->PortWasMapped = FALSE;
           }
           RtlInitUnicodeString(&win32_device_name, CARRIER_DOS_DEVICE_NAME);
           IoDeleteSymbolicLink(&win32_device_name);           
        }        
        IoSkipCurrentIrpStackLocation(irp);
        status = IoCallDriver(device_info->NextLowerDriver, irp);
        IoDetachDevice(device_info->NextLowerDriver); 
        IoDeleteDevice(device_object);
        return status;
    case IRP_MN_STOP_DEVICE:
        // Since you failed query stop, you will not get this request.
    case IRP_MN_CANCEL_REMOVE_DEVICE: 
        // No action required in this case. Just pass it down.
    case IRP_MN_CANCEL_STOP_DEVICE: 
        //No action required in this case.
    default:
        //
        // Please see PnP documentation for use of these IRPs.
        //
        IoSkipCurrentIrpStackLocation (irp);
        status = IoCallDriver(device_info->NextLowerDriver, irp);
        break;
    }
    IoReleaseRemoveLock(&device_info->RemoveLock, NULL);       
    return status;
}

NTSTATUS CarrierStartDevice (IN PDEVICE_OBJECT device_object,
                             IN PIRP irp)
{
    NTSTATUS status = STATUS_SUCCESS;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR resource;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR resource_trans;
    PCM_PARTIAL_RESOURCE_LIST partial_resource_list;
    PCM_PARTIAL_RESOURCE_LIST partial_resource_list_translated;
    PIO_STACK_LOCATION stack;
    ULONG i;
    PLOCAL_DEVICE_INFO device_info;

    device_info = (PLOCAL_DEVICE_INFO) device_object->DeviceExtension;
    stack = IoGetCurrentIrpStackLocation (irp);

    PAGED_CODE();

    //
    // We need to check that we haven't received a surprise removal
    //
    if (device_info->Removed) {
        //
        // Some kind of surprise removal arrived. We will fail the IRP
        // The dispatch routine that called us will take care of 
        // completing the IRP.
        //
        return STATUS_DELETE_PENDING;
    }
    //
    // Do whatever initialization needed when starting the device: 
    // gather information about it,  update the registry, etc.
    //
    if ((NULL == stack->Parameters.StartDevice.AllocatedResources) &&
        (NULL == stack->Parameters.StartDevice.AllocatedResourcesTranslated)) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    //
    // Parameters.StartDevice.AllocatedResources points to a 
    // CM_RESOURCE_LIST describing the hardware resources that 
    // the PnP Manager assigned to the device. This list contains 
    // the resources in raw form. Use the raw resources to program 
    // the device.
    //

    partial_resource_list = 
    &stack->Parameters.StartDevice.AllocatedResources->List[0].PartialResourceList;
    resource = &partial_resource_list->PartialDescriptors[0];
    //
    // Parameters.StartDevice.AllocatedResourcesTranslated points 
    // to a CM_RESOURCE_LIST describing the hardware resources that 
    // the PnP Manager assigned to the device. This list contains 
    // the resources in translated form. Use the translated resources 
    // to connect the interrupt vector, map I/O space, and map memory.
    //
    partial_resource_list_translated = 
    &stack->Parameters.StartDevice.AllocatedResourcesTranslated->List[0].PartialResourceList;
    resource_trans = &partial_resource_list_translated->PartialDescriptors[0];
    for (i = 0;
         i < partial_resource_list->Count; i++, resource++, resource_trans++) {
        switch (resource->Type) {
        case CmResourceTypePort:
            switch (resource_trans->Type) {
            case CmResourceTypePort:
                device_info->PortWasMapped = FALSE;
                device_info->PortBase = (PVOID)resource_trans->u.Port.Start.LowPart;
                device_info->PortCount = resource_trans->u.Port.Length;
                DebugPrint(("Resource Translated Port: (%x) Length: (%d)\n", 
                    resource_trans->u.Port.Start.LowPart, 
                    resource_trans->u.Port.Length));
		if ((Ccb = CARRIER_Init(device_info,
		                        (unsigned long)device_info->PortBase)) == NULL) {
		   device_info->Ccb = Ccb;
		   return STATUS_INSUFFICIENT_RESOURCES;
		}
		// Initialize the timer, needed for driver waitstates
		KeInitializeTimer( &device_info->WaitTimer );
                break;
#ifdef lassma
            case CmResourceTypeMemory:
                //
                // We need to map the memory
                //
                device_info->PortBase = (PVOID)
                    MmMapIoSpace(resource_trans->u.Memory.Start,
                                 resource_trans->u.Memory.Length,
                                 MmNonCached);
                device_info->PortCount = resource_trans->u.Memory.Length;
                device_info->PortWasMapped = TRUE;

                DebugPrint(("Resource Translated Memory: (%x) Length: (%d)\n", 
                    resource_trans->u.Memory.Start.LowPart, 
                    resource_trans->u.Memory.Length));

                break;
#endif
            default:
                DebugPrint(("Unhandled resource_type (0x%x)\n", resource_trans->Type));
                status = STATUS_UNSUCCESSFUL;
                TRAP ();
            }             
            break;
        case CmResourceTypeMemory:
            device_info->PortBase = (PVOID)
                MmMapIoSpace (resource_trans->u.Memory.Start,
                              resource_trans->u.Memory.Length,
                              MmNonCached);
            device_info->PortCount = resource_trans->u.Memory.Length;
            device_info->PortWasMapped = TRUE;

            DebugPrint(("Resource Translated Memory: (%x) Length: (%d)\n", 
                resource_trans->u.Memory.Start.LowPart, 
                resource_trans->u.Memory.Length));

            break;
        case CmResourceTypeInterrupt:
        default:

            DebugPrint(("Unhandled resource type (0x%x)\n", resource->Type));

            status = STATUS_UNSUCCESSFUL;
            break;
        } // end of switch
    } // end of for
    return status;
}

NTSTATUS CarrierDispatchPower(IN PDEVICE_OBJECT device_object,
                              IN PIRP irp)
{
   PLOCAL_DEVICE_INFO device_info;
   device_info = (PLOCAL_DEVICE_INFO) device_object->DeviceExtension;
   //
   // If the device has been removed, the driver should not pass 
   // the IRP down to the next lower driver.
   //
   if (device_info->Removed) {
      PoStartNextPowerIrp(irp);
      irp->IoStatus.Status =  STATUS_DELETE_PENDING;
      IoCompleteRequest(irp, IO_NO_INCREMENT );
      return STATUS_DELETE_PENDING;
   }
   PoStartNextPowerIrp(irp);
   IoSkipCurrentIrpStackLocation(irp);
   return PoCallDriver(device_info->NextLowerDriver, irp);
}

NTSTATUS CarrierDispatchSystemControl(IN PDEVICE_OBJECT device_object,
                                      IN PIRP irp)
{
   PLOCAL_DEVICE_INFO device_info;

   PAGED_CODE();

   device_info = (PLOCAL_DEVICE_INFO) device_object->DeviceExtension;
   IoSkipCurrentIrpStackLocation(irp);
   return IoCallDriver(device_info->NextLowerDriver, irp);
}

VOID CarrierUnload(IN PDRIVER_OBJECT driver_object)
{
   PAGED_CODE ();

   //
   // The device object(s) should be NULL now
   // (since we unload, all the devices objects associated with this
   // driver must have been deleted.
   //
   ASSERT(driver_object->device_object == NULL);
    
   DebugPrint (("unload\n"));

   return;
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


NTSTATUS CarrierDispatch(IN PDEVICE_OBJECT device_object,
                         IN PIRP irp)
{
   PLOCAL_DEVICE_INFO ldi;
   PIO_STACK_LOCATION stack;
   NTSTATUS status;

   PAGED_CODE();

   irp->IoStatus.Information = 0;
   ldi = (PLOCAL_DEVICE_INFO)device_object->DeviceExtension;    // Get local info struct

   DebugPrint (("Entered CarrierDispatch\n"));

   status = IoAcquireRemoveLock (&ldi->RemoveLock, NULL);
   if (!NT_SUCCESS (status)) {
       irp->IoStatus.Information = 0;
       irp->IoStatus.Status = status;
       IoCompleteRequest (irp, IO_NO_INCREMENT);
       return status;
   }

   if (!ldi->Started) {
       //
       // We fail all the IRPs that arrive before the device is started.
       //
       irp->IoStatus.Status = status = STATUS_DEVICE_NOT_READY;
       IoCompleteRequest(irp, IO_NO_INCREMENT );
       IoReleaseRemoveLock(&ldi->RemoveLock, NULL);       
       return status;
   }
   stack = IoGetCurrentIrpStackLocation(irp);
   // Dispatch based on major fcn code.
   switch (stack->MajorFunction) {
   case IRP_MJ_CREATE:
   case IRP_MJ_CLOSE:
      // We don't need any special processing on open/close so we'll
      // just return success.
      status = STATUS_SUCCESS;
      break;
   case IRP_MJ_DEVICE_CONTROL:
      //  Dispatch on IOCTL
      status = CarrierDeviceControl(ldi, irp, stack,
                            stack->Parameters.DeviceIoControl.IoControlCode);
      break;
   case IRP_MJ_WRITE:
      status = CarrierWrite(ldi, irp, stack);
      break;
   case IRP_MJ_READ:
      status = CarrierRead(ldi, irp, stack);
      break;
   default: 
      status = STATUS_NOT_IMPLEMENTED;
      break;
   }

   // We're done with I/O request.  Record the status of the I/O action.
   irp->IoStatus.Status = status;

   // Don't boost priority when returning since this took little time.
   IoCompleteRequest(irp, IO_NO_INCREMENT );
   IoReleaseRemoveLock(&ldi->RemoveLock, NULL);       
   return status;
}





#if DBG
PCHAR PnPMinorFunctionString(UCHAR MinorFunction)
{
   switch (MinorFunction) {
   case IRP_MN_START_DEVICE:
      return "IRP_MN_START_DEVICE";
   case IRP_MN_QUERY_REMOVE_DEVICE:
      return "IRP_MN_QUERY_REMOVE_DEVICE";
   case IRP_MN_REMOVE_DEVICE:
      return "IRP_MN_REMOVE_DEVICE";
   case IRP_MN_CANCEL_REMOVE_DEVICE:
      return "IRP_MN_CANCEL_REMOVE_DEVICE";
   case IRP_MN_STOP_DEVICE:
      return "IRP_MN_STOP_DEVICE";
   case IRP_MN_QUERY_STOP_DEVICE:
      return "IRP_MN_QUERY_STOP_DEVICE";
   case IRP_MN_CANCEL_STOP_DEVICE:
      return "IRP_MN_CANCEL_STOP_DEVICE";
   case IRP_MN_QUERY_DEVICE_RELATIONS:
      return "IRP_MN_QUERY_DEVICE_RELATIONS";
   case IRP_MN_QUERY_INTERFACE:
      return "IRP_MN_QUERY_INTERFACE";
   case IRP_MN_QUERY_CAPABILITIES:
      return "IRP_MN_QUERY_CAPABILITIES";
   case IRP_MN_QUERY_RESOURCES:
      return "IRP_MN_QUERY_RESOURCES";
   case IRP_MN_QUERY_RESOURCE_REQUIREMENTS:
      return "IRP_MN_QUERY_RESOURCE_REQUIREMENTS";
   case IRP_MN_QUERY_DEVICE_TEXT:
      return "IRP_MN_QUERY_DEVICE_TEXT";
   case IRP_MN_FILTER_RESOURCE_REQUIREMENTS:
      return "IRP_MN_FILTER_RESOURCE_REQUIREMENTS";
   case IRP_MN_READ_CONFIG:
      return "IRP_MN_READ_CONFIG";
   case IRP_MN_WRITE_CONFIG:
      return "IRP_MN_WRITE_CONFIG";
   case IRP_MN_EJECT:
      return "IRP_MN_EJECT";
   case IRP_MN_SET_LOCK:
      return "IRP_MN_SET_LOCK";
   case IRP_MN_QUERY_ID:
      return "IRP_MN_QUERY_ID";
   case IRP_MN_QUERY_PNP_DEVICE_STATE:
      return "IRP_MN_QUERY_PNP_DEVICE_STATE";
   case IRP_MN_QUERY_BUS_INFORMATION:
      return "IRP_MN_QUERY_BUS_INFORMATION";
   case IRP_MN_DEVICE_USAGE_NOTIFICATION:
      return "IRP_MN_DEVICE_USAGE_NOTIFICATION";
   case IRP_MN_SURPRISE_REMOVAL:
      return "IRP_MN_SURPRISE_REMOVAL";
   default:
      return "IRP_MN_?????";
   }
}

#endif

