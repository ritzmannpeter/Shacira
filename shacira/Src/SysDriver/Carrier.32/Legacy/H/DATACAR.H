/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
/*.EI.***********************************************************************/

#ifndef __datacar__
#define __datacar__

#define  SDISKJ      1
#define  PCMCIAJ     2
#define  FILEBASE    3
#define  SRAM        4
#define  DRAM        5
#define  CANMEM      6
#define  CAR450      7

typedef long DATACAR_ADDRESS;

typedef struct
{  BYTE type;
   void * config;
}  DATACAR_CONFIG;

#define DATACAR_Init(channel)                   NO_ERROR
#define DATACAR_Config(channel, config)         NO_ERROR
#define DATACAR_Check(channel)                  DataCar_Check(AUTODETECT)
#define DATACAR_Read(channel, dst, src, size)   DataCar_Read(src, (short)size, dst)
#define DATACAR_Write(channel, dst, src, size)  DataCar_Write(src, (short)size, dst)

#define DATACAR_DRIVER_NOT_INITIALIZED    -10
#define DATACAR_NO_MODULE_FOUND           -11
#define DATACAR_INVALID_ADDRESS_OR_SIZE   -12
#define DATACAR_VERIFY_ERROR              -13
#define DATACAR_NOT_DETECTED              -14
#define DATACAR_BANK_CHECK                -15

GLOBAL short DataCar_Check();
GLOBAL short DataCar_Read(long src, short size, char * dst);
GLOBAL short DataCar_Write(char * src, short size, long dst);

/* defines */

#define  AUTODETECT        0
#define  PAGEMODE       0x4000

/* error codes */

#define     DCAR_OK            0
#define     DCAR_BAD_TYP      -1
#define     DCAR_NOT_FOUND    -2
#define     DCAR_VERIFY_ERROR -3
#define     DCAR_NO_EEPROM    -4
#define     DCAR_NOT_READY    -5
#define     DCAR_ADR_ERROR    -6

#define     DCAR_0K        0
#define     DCAR_2K        2
#define     DCAR_4K        4
#define     DCAR_8K        8
#define     DCAR_32K    32
#define     DCAR_64K    64
/* register */

#define     DATA_CARRIER_BASE    0x8140
#define     DATA_CAR_COMMAND     DATA_CARRIER_BASE
#define     DATA_CAR_ADR         DATA_CARRIER_BASE + 4
#define     DATA_CAR_DATA        DATA_CARRIER_BASE + 6
#define     DATA_CAR_STATE       DATA_CARRIER_BASE + 7


/* commands */

#define     DATA_CARRIER_CMD     0x04

/* state */

#define     DATA_CARRIER_TEST    0x02
#define  DATA_CARRIER_READY      0x08
#define  DATA_CARRIER_WPROT      0x10

#endif   /* datacar */




