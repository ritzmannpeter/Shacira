
#ifndef __carrier_h__
#define __carrier_h__

#include <stddef.h>
#include "carsim.h"

// driver specific definitions

#define CARRIER_NT_DEVICE_NAME	 L"\\Device\\CARRIER"
#define CARRIER_DOS_DEVICE_NAME	 L"\\DosDevices\\CARRIER"

#define CARRIER_OK                  0        // no error
#define CARRIER_INIT              -50        // Ccb is NULL
#define CARRIER_NOT_FOUND         -52        // no carrier plugged in
#define CARRIER_VERIFY_ERROR      -53        // check of written data not successful
#define CARRIER_NOT_READY         -55        // ???
#define CARRIER_INVALID_ADDR      -56        // address is not valid
#define CARRIER_ADDR_ERROR        -57        // overflow address space
#define CARRIER_READ_ERROR        -60        // 
#define CARRIER_INVALID_MODE      -61        // PageMode must be OFF at old carrier
#define CARRIER_READ_FAILED       -62        // 
#define CARRIER_PARAM_NOT_EXISTS  -65        // 
#define CARRIER_BAD_PARAMETER     -66        // invalid parameter value
#define CARRIER_NOT_SIMULATED     -67
#define CARRIER_INVALID_SIMULATED_SIZE     -68

#define CARRIER_0K    0
#define CARRIER_2K    2
#define CARRIER_4K    4
#define CARRIER_8K    8
#define CARRIER_32K  32
#define CARRIER_64K  64

/* commands */
#define NO_OP       0xff
#define NO_OP_W     0x7f
#define READ_OP     0xf9
#define SELECT_R    0xfb
#define WRITE_OP    0x7a
#define SELECT_W    0x7b

//
// Functions that must be supplied by the embedding
// environment (W2K/NT-kernel mode drivers W9x-VXD or DLL)
//

extern void Wait(unsigned long ms);            	// thread suspension
extern unsigned char Inport(unsigned short port);	// read io port (BYTE)
extern void Outport(unsigned short port, unsigned char value);	// write io port (BYTE)
extern unsigned char SimulatedInport(unsigned short port);	// simulate read io port (BYTE)
extern void SimulatedOutport(unsigned short port, unsigned char value);	// simulate write io port (BYTE)

//
// Configuration params
//

// Default base port
#define DEF_BASE_PORT       0x360

// Hardware version
#define V_UNDEF 	         -1
#define V_0       	      0
#define V_1                1
#define HW_VERSIONS        (V_1 + 1)
#define DEF_VERSION        V_1

// Check mode
#define DESTRUCTIVE         0
#define NON_DESTRUCTIVE     1
#define DEF_CHECK_MODE	    DESTRUCTIVE

// Default retries
#define DEF_RETRIES	      20

// Default stability
#define DEF_STABILITY	   10

// Default programming delay time
#define DEF_DELAY_TIME	   15

// Switch
#define OFF  0
#define ON   1

// Hardware simulation
#define DEF_SIM_FLAG       OFF

typedef struct
{
   void * DriverContext;
   unsigned long PortAddress;
   unsigned long HardwareVersion;
   unsigned long addr_low;
   unsigned long addr_high;
   unsigned long addr_cmd;
   unsigned long addr_write;
   unsigned long addr_read;
   unsigned long addr_status;
   unsigned long CheckMode;
   unsigned long DelayTime;
   unsigned long Stability;
   unsigned long Retries;
   unsigned char PageMode;
   unsigned long CarrierSize;
   unsigned long SimulateHardware;
   HARDWARE * SimulatedHardware;
}  CCB;

CCB * CARRIER_Init(void * driver_context, unsigned int port_address);
void CARRIER_Exit(CCB * ccb);
long CARRIER_Check(CCB * ccb);
long CARRIER_Read(CCB * ccb, unsigned long address, void * buf, unsigned long bufsize, unsigned long len);
long CARRIER_Write(CCB * ccb, unsigned long address, void * buf, unsigned long len);
long CARRIER_SetParam(CCB * ccb, const char * param_name, long param_value);
long CARRIER_GetParam(CCB * ccb, const char * param_name, long * param_value);

#endif   /* __carrier_h__ */

