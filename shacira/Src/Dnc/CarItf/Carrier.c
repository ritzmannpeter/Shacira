/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     CARRIER
*
*  BESCHREIBUNG:
*     Zugriffsfunktionen fuer EEPROM-Datentraeger.
*
*  UMGEBUNG:
*     ZIELRECHNER:           PC-AT
*     ENTWICKLUNGSRECHNER:   PC-AT
*     UEBERSETZER:
*     OPTIONEN:
*
*  VERSION:
*     VERSION:    1.00                      DATUM:
*     AUTOR(EN):  P. Ritzmann               TELEFON: (0761) 45205-0
*
*  HISTORY:
*
*
*  BEMERKUNGEN:
*
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  FUNKTIONEN:
*
*  DATENTYPEN:
*
*  VARIABLEN:
*
*.EM.***********************************************************************/
/***************************************************************************/

#include "Carrier.h"
#include <string.h>

#define DebugPrintf

/* Remove _enable() and _disable() functions */
#define _enable()
#define _disable()

/* Hardware structure
 */
typedef struct {
   unsigned int addr_low;
   unsigned int addr_high;
   unsigned int addr_cmd;
   unsigned int addr_write;
   unsigned int addr_read;
   unsigned int addr_status;
}  DNC_REGS;

typedef struct
{
   DNC_REGS regs[HW_VERSIONS];
}  DNC_HW;

static const DNC_REGS DncHardware[HW_VERSIONS] =
{
   {0x0L, 0x1L, 0x2L, 0x3L, 0x4L, 0x5L},
   {0x0L, 0x1L, 0x4L, 0x2L, 0x3L, 0x5L}
};

static CCB CarrierControlBlock = {
                                    NULL,
                                    DEF_BASE_PORT,
                                    DEF_VERSION,
                                    0L, 0L, 0L, 0L, 0L, 0L,
                                    DEF_CHECK_MODE,
                                    DEF_DELAY_TIME,
                                    DEF_STABILITY,
                                    DEF_RETRIES,
                                    OFF,
                                    0L,
                                    DEF_SIM_FLAG,
                                    NULL
                                 };

static CCB * Ccb = &CarrierControlBlock;

//#define _inp(p) ((Ccb->SimulateHardware == ON) ? SimulatedInport((unsigned short)p)) : Inport((unsigned short)p)))
#define _inp(p) (\
                  (Ccb->SimulateHardware == ON) ? \
                  SimulatedInport((unsigned short)p) : \
                  Inport((unsigned short)p)\
                )

#define _outp(p,v) \
   if (Ccb->SimulateHardware == ON) { \
      SimulatedOutport((unsigned short)p,(unsigned char)v); \
   } else { \
      Outport((unsigned short)p,(unsigned char)v); \
   }

#define ADR_LOW(ccb)     (ccb->addr_low)
#define ADR_HIGH(ccb)    (ccb->addr_high)
#define ADR_CMD(ccb)     (ccb->addr_cmd)
#define ADR_WRITE(ccb)   (ccb->addr_write)
#define ADR_READ(ccb)    (ccb->addr_read)
#define STATUS(ccb)      (ccb->addr_status)

static void * SetHardware(CCB * ccb)
{
   if (ccb == NULL) return NULL;
   ccb->addr_low = DncHardware[ccb->HardwareVersion].addr_low    + ccb->PortAddress;
   ccb->addr_high = DncHardware[ccb->HardwareVersion].addr_high   + ccb->PortAddress;
   ccb->addr_cmd = DncHardware[ccb->HardwareVersion].addr_cmd    + ccb->PortAddress;
   ccb->addr_write = DncHardware[ccb->HardwareVersion].addr_write  + ccb->PortAddress;
   ccb->addr_read = DncHardware[ccb->HardwareVersion].addr_read   + ccb->PortAddress;
   ccb->addr_status = DncHardware[ccb->HardwareVersion].addr_status + ccb->PortAddress;
   if (SetSimHardware(ccb) == NULL) {
      return NULL;
   }
   return ccb;
}

/* state */
#define DATA_CARRIER_TEST   0x02
#define DATA_CARRIER_READY  0x08
#define DATA_CARRIER_WPROT  0x10

#define CARRIER_PAGE_SIZE   64UL

static long ReadByte (CCB * ccb, unsigned long address, unsigned char * value);
static long WriteByte(CCB * ccb, unsigned long address, unsigned char value,
                      long page_mode, long delay_size);

static int CarrierState(CCB * ccb)
{
   short state;
   state = 0x00ff & _inp(STATUS(ccb));
   if ((state & 1) == 1) {
      return CARRIER_NOT_FOUND;
   } else {
      return CARRIER_OK;
   }
}

#define CHECK_BUFSIZE 0x40

static long GetSizeNonDestruct(CCB * ccb)
{  int i;
   char buf0[CHECK_BUFSIZE] = {0};
   char buf4[CHECK_BUFSIZE] = {0};
   char buf8[CHECK_BUFSIZE] = {0};
   for (i=0; i<CHECK_BUFSIZE; i++) {
      ReadByte(ccb, (unsigned long)i, &buf0[i]);
      ReadByte(ccb, (unsigned long)i + 0x1000, &buf4[i]);
      ReadByte(ccb, (unsigned long)i + 0x2000, &buf8[i]);
   }
   ccb->PageMode = OFF;
   if (memcmp(buf0, buf8, CHECK_BUFSIZE) != 0) {
      ccb->PageMode = ON;
      ccb->CarrierSize = (long)32 * 1024L;
      return CARRIER_32K;
   } else if (memcmp(buf0, buf4, CHECK_BUFSIZE) != 0) {
      ccb->CarrierSize = (long)8 * 1024L;
      return CARRIER_8K;
   } else {
      ccb->CarrierSize = (long)4 * 1024L;
      return CARRIER_4K;
   }
}

static long GetSizeDestruct(CCB * ccb)
{  int size;
   unsigned char ch1, ch3, ch0, ch2, ch4, ch8, ch32;

   ReadByte(ccb, 0lu, &ch0);
   ReadByte(ccb, 2048lu, &ch2);
   ReadByte(ccb, 4096lu, &ch4);
   ReadByte(ccb, 8192lu, &ch8);
   ReadByte(ccb, 32768lu, &ch32);

   size = CARRIER_0K;
   WriteByte(ccb, 0lu, 'A', OFF, ccb->DelayTime);
   WriteByte(ccb, 2048lu, 'B', OFF, ccb->DelayTime);
   ReadByte(ccb, 0lu, &ch1);
   ReadByte(ccb, 2048lu, &ch3);
   if (ch1 != ch3) size = CARRIER_4K;

   WriteByte(ccb, 0lu, 'A', OFF, ccb->DelayTime);
   WriteByte(ccb, 4096lu, 'B', OFF, ccb->DelayTime);
   ReadByte(ccb, 0lu, &ch1);
   ReadByte(ccb, 4096lu, &ch3);
   if (ch1 != ch3) size = CARRIER_8K;

   WriteByte(ccb, 0lu, 'A', OFF, ccb->DelayTime);
   WriteByte(ccb, 8192lu, 'B', OFF, ccb->DelayTime);
   ReadByte(ccb, 0lu, &ch1);
   ReadByte(ccb, 8192lu, &ch3);
   if (ch1 != ch3) size = CARRIER_32K;

   WriteByte(ccb, 0lu, 'A', OFF, ccb->DelayTime);
   WriteByte(ccb, 32768lu, 'B', OFF, ccb->DelayTime);
   ReadByte(ccb, 0lu, &ch1);
   ReadByte(ccb, 32768lu, &ch3);
   if (ch1 != ch3) size = CARRIER_64K;

   WriteByte(ccb, 0lu, ch0, OFF, ccb->DelayTime);
   WriteByte(ccb, 2048lu, ch2, OFF, ccb->DelayTime);
   WriteByte(ccb, 4096lu, ch4, OFF, ccb->DelayTime);
   WriteByte(ccb, 8192lu, ch8, OFF, ccb->DelayTime);
   WriteByte(ccb, 32768lu, ch32, OFF, ccb->DelayTime);

   if (size < CARRIER_32K)
      ccb->PageMode = OFF;
   else {
      ccb->PageMode = ON;
      ReadByte(ccb, 2lu, &ch0);
      ReadByte(ccb, 1lu, &ch4);
      WriteByte(ccb, 2lu, 'A', ON, ccb->DelayTime);
      WriteByte(ccb, 1lu, 'A', ON, ccb->DelayTime);
      Wait(ccb->DelayTime);
      WriteByte(ccb, 2lu, 'B', ON, ccb->DelayTime);
      WriteByte(ccb, 1lu, 'B', ON, ccb->DelayTime);
      Wait(ccb->DelayTime);
      ReadByte(ccb, 2lu, &ch1);
      ReadByte(ccb, 1lu, &ch3);
      if ((ch1 == 'B') && ('B' == ch3))
         ccb->PageMode = ON;
      else
         ccb->PageMode = OFF;
      WriteByte(ccb, 2lu, ch0, OFF, ccb->DelayTime);
      WriteByte(ccb, 1lu, ch4, OFF, ccb->DelayTime);
   }
   ccb->CarrierSize = (long)size * 1024L;
   return size;
}

static long CarrierCheck(CCB * ccb)
{
   short state;
   ccb->CarrierSize = 0L;
   ccb->PageMode = OFF;
   state = _inp(STATUS(ccb));
   if ((state & 1) == 1) return CARRIER_NOT_FOUND;
   if (ccb->HardwareVersion == V_0) {
      if ((state & 2) == 0) return CARRIER_NOT_READY;
   }
   if (ccb->CheckMode == DESTRUCTIVE) {
      return GetSizeDestruct(ccb);
   } else {
      return GetSizeNonDestruct(ccb);
   }
}

#define _read_byte(ccb,v,a,m,e)\
{  unsigned long count = 0;\
   unsigned long abscount = 0;\
   unsigned char cval;\
   _outp(ADR_CMD(ccb), NO_OP);\
   _outp(ADR_LOW(ccb), (unsigned char)(a));\
   _outp(ADR_HIGH(ccb), (unsigned char)((unsigned short)(a) >> 8));\
   _disable();\
   _outp(ADR_CMD(ccb), (SELECT_R & (m)));\
   _outp(ADR_CMD(ccb), (READ_OP & (m)));\
   _enable();\
   v = _inp(ADR_READ(ccb));\
   cval = v;\
   while (count < ccb->Stability && abscount < ccb->Retries) {\
      v = _inp(ADR_READ(ccb));\
      if (v == cval)\
         count++;\
      else {\
         count = 0;\
         cval = v;\
      }\
      abscount++;\
   }\
   _outp(ADR_CMD(ccb), NO_OP);\
   if (abscount >= ccb->Retries) e = CARRIER_READ_ERROR;\
}

#define VALUE 5

static long _ReadByte(CCB * ccb, unsigned long address, unsigned char * value)
{  short state;
   unsigned char mask;
   int line = (int)((address & 0x1800L) >> 11);
   unsigned char val1 = VALUE, val2 = VALUE, val3 = VALUE, val4 = VALUE, val5 = VALUE;

   switch(line) {
   case 0: mask = 0xF7; break;
   case 1: mask = 0xEF; break;
   case 2: mask = 0xDF; break;
   case 3: mask = 0xBF; break;
   default: mask = 0xFF; break;
   }

   state = CarrierState(ccb);
   if (state == CARRIER_OK) {
      _read_byte(ccb, val1, address, mask, state)
      if (state == CARRIER_READ_ERROR) {
         DebugPrintf(("read error at %04x\n", address));
         return state;
      }
      _read_byte(ccb, val2, address, mask, state)
      if (state == CARRIER_READ_ERROR) {
         DebugPrintf(("read error at %04x\n", address));
         return state;
      }
      _read_byte(ccb, val3, address, mask, state)
      if (state == CARRIER_READ_ERROR) {
         DebugPrintf(("read error at %04x\n", address));
         return state;
      }
      _read_byte(ccb, val4, address, mask, state)
      if (state == CARRIER_READ_ERROR) {
         DebugPrintf(("read error at %04x\n", address));
         return state;
      }
      _read_byte(ccb, val5, address, mask, state)
      if (state == CARRIER_READ_ERROR) {
         DebugPrintf(("read error at %04x\n", address));
         return state;
      }
      if (val1 == val2 && val2 == val3 && val3 == val4 && val4 == val5) {
         *value = val1;
         return CARRIER_OK;
      } else {
         *value = 0xaa;
         DebugPrintf(("read failed at %04x\n", address));
         state = CARRIER_READ_FAILED;
      }
   }
   return state;
}

static unsigned char LastByte = 55;

static long ReadByte(CCB * ccb, unsigned long address, unsigned char * value)
{
   int err = CARRIER_OK - 1;
   int tries = 10;

   while (err != CARRIER_OK && tries--) {
      err = _ReadByte(ccb, address, value);
      if (err != CARRIER_OK)
         Wait(2);
   }
   if (err == CARRIER_OK)
      LastByte = *value;
   else
      DebugPrintf(("read error %d at %06ld last byte is %02x\n", err, address, LastByte));
   return err;
}

static long WriteByte(CCB * ccb, unsigned long address, unsigned char value,
                      long page_mode, long delay_size)
{
   short state;
   unsigned char mask;
   int line = (int)((address & 0x1800L) >> 11);

   switch(line) {
   case 0: mask = 0xF7; break;
   case 1: mask = 0xEF; break;
   case 2: mask = 0xDF; break;
   case 3: mask = 0xBF; break;
   default: mask = 0xFF;
   }
   if (!page_mode) _disable();
   state = CarrierState(ccb);
   if (state == CARRIER_OK) {
      _outp(ADR_CMD(ccb), NO_OP);
      _outp(ADR_LOW(ccb), (unsigned char)address);
      _outp(ADR_HIGH(ccb), (unsigned char)((unsigned short)address >> 8));
      _outp(ADR_CMD(ccb), (SELECT_W & mask));
      _outp(ADR_WRITE(ccb), value);
      _outp(ADR_CMD(ccb), (WRITE_OP & mask));
      _outp(ADR_CMD(ccb), (SELECT_W & mask));
      _outp(ADR_CMD(ccb), (NO_OP_W & mask));
      _outp(ADR_CMD(ccb), NO_OP);
   } else
      DebugPrintf(("write failed at %04x: %d\n", address, state));
   if (!page_mode) {
      Wait(delay_size);
      _enable();
   }
   return state;
}

static long WritePage(CCB * ccb, unsigned long address, unsigned long size, void * buffer)
{
   long state;
   long delay_size = ccb->DelayTime;
   unsigned char page_mode = ccb->PageMode;
   unsigned long limit = address + size;
   register unsigned char * buf_ptr;
   register unsigned long i;

   if (page_mode == ON) {
      _disable();
      for (i=address, buf_ptr=buffer; i<limit; i++, buf_ptr++) {
         if ((state = WriteByte(ccb, i, *buf_ptr, ON, delay_size)) != CARRIER_OK) {
            _enable();
            return state;
         }
      }
      Wait(delay_size);
      _enable();
      return CARRIER_OK;
   } else
      return CARRIER_INVALID_MODE;
}

static long CarrierRead(CCB * ccb, unsigned long address, unsigned long size, void * buffer)
{
   long state;
   unsigned char * buf_ptr;
   unsigned long i, limit = address + size;

   DebugPrintf(("read request %ld bytes at %ld\n", size, address));
   if (address > ccb->CarrierSize) {
      DebugPrintf(("read failed: invalid address %ld\n", address));
      return CARRIER_INVALID_ADDR;
   }
   if (limit > ccb->CarrierSize) {
      DebugPrintf(("read failed: memory overflow %ld\n", limit));
      return CARRIER_ADDR_ERROR;
   }
   for (i=address, buf_ptr=buffer; i<limit; i++, buf_ptr++) {
      if ((state = ReadByte(ccb, i, buf_ptr)) != CARRIER_OK) {
         DebugPrintf(("read failed at %ld state %d\n", i, state));
         return state;
      }
   }
   DebugPrintf(("%ld bytes read at %ld\n", size, address));
   return CARRIER_OK;
}

#define VERIFY_BUF_SIZE    256
static unsigned char VerifyBuf[VERIFY_BUF_SIZE];

static long CarrierWrite(CCB * ccb, unsigned long address, unsigned long size, void * buffer)
{
   long state;
   unsigned char * buf_ptr;
   unsigned long i, limit = address + size, write_size, page_no;
   unsigned long bytes_to_process = size;

   DebugPrintf(("write request %ld bytes at %ld\n", size, address));
   if (address > ccb->CarrierSize) {
      DebugPrintf(("write failed: invalid address %ld\n", address));
      return CARRIER_INVALID_ADDR;
   }
   if (limit > ccb->CarrierSize) {
      DebugPrintf(("write failed: memory overflow %ld\n", limit));
      return CARRIER_ADDR_ERROR;
   }
   if (ccb->PageMode == OFF) {
      for (i=address, buf_ptr=buffer; i<limit; i++, buf_ptr++) {
         if ((state = WriteByte(ccb, i, *buf_ptr, OFF, ccb->DelayTime)) != CARRIER_OK) {
            DebugPrintf(("write failed at %ld state %d\n", i, state));
            return state;
         }
      }
   } else {
      i = address;
      buf_ptr = buffer;
      page_no = address / CARRIER_PAGE_SIZE;
      write_size = ((page_no + 1) * CARRIER_PAGE_SIZE) - address;
      if (bytes_to_process > write_size) {
         /* Der Puffer geht ueber mehrere Seiten
          */
         if ((state = WritePage(ccb, i, write_size, buf_ptr)) != CARRIER_OK) {
            DebugPrintf(("write failed at %ld state %d\n", i, state));
            return state;
         }
         i += write_size;
         buf_ptr += write_size;
         bytes_to_process -= write_size;
         while (bytes_to_process > CARRIER_PAGE_SIZE) {
            /* Vollstaendige Seiten
             */
            Wait(ccb->DelayTime);
            if ((state = WritePage(ccb, i, CARRIER_PAGE_SIZE, buf_ptr)) != CARRIER_OK) {
               DebugPrintf(("write failed at %ld state %d\n", i, state));
               return state;
            }
            i += CARRIER_PAGE_SIZE;
            buf_ptr += CARRIER_PAGE_SIZE;
            bytes_to_process -= CARRIER_PAGE_SIZE;
         }
         if (bytes_to_process > 0) {
            Wait(ccb->DelayTime);
            if ((state = WritePage(ccb, i, bytes_to_process, buf_ptr)) != CARRIER_OK) {
               DebugPrintf(("write failed at %ld state %d\n", i, state));
               return state;
            }
         }
      } else {
         /* Der gesamte Puffer kommt in einer Seite unter
          */
         if ((state = WritePage(ccb, address, bytes_to_process, buffer)) != CARRIER_OK) {
            DebugPrintf(("write failed at %ld state %d\n", i, state));
            return state;
         }
      }
   }

   /* Verify
    */
   i = address;
   buf_ptr = buffer;
   bytes_to_process = size;
   while (bytes_to_process > VERIFY_BUF_SIZE) {
      if ((state = CarrierRead(ccb, i, VERIFY_BUF_SIZE, VerifyBuf)) != CARRIER_OK) {
         DebugPrintf(("write failed reading for verify at %ld state %d\n", i, state));
         return state;
      }
      if (memcmp(VerifyBuf, buf_ptr, VERIFY_BUF_SIZE)) {
         DebugPrintf(("verify failed at %ld\n", i));
         return CARRIER_VERIFY_ERROR;
      }
      i += VERIFY_BUF_SIZE;
      buf_ptr += VERIFY_BUF_SIZE;
      bytes_to_process -= VERIFY_BUF_SIZE;
   }
   if (bytes_to_process > 0) {
      if ((state = CarrierRead(ccb, i, bytes_to_process, VerifyBuf)) != CARRIER_OK) {
         DebugPrintf(("write failed reading for verify at %ld state %d\n", i, state));
         return state;
      }
      if (memcmp(VerifyBuf, buf_ptr, bytes_to_process)) {
         DebugPrintf(("verify failed at %ld\n", i));
         return CARRIER_VERIFY_ERROR;
      }
   }
   return CARRIER_OK;
}

CCB * CARRIER_Init(void * driver_context, unsigned int port_address)
{
   Ccb->PortAddress = port_address;
   Ccb->DriverContext = driver_context;
   if (SetHardware(Ccb) == NULL) {
      return NULL;
   }
   return Ccb;
}

void CARRIER_Exit(CCB * ccb)
{
   ccb = NULL;
}

long CARRIER_Check(CCB * ccb)
{ 
   if (ccb == NULL) return CARRIER_INIT;
   return CarrierCheck(ccb);
}

long CARRIER_Write(CCB * ccb, unsigned long address, void * buf, unsigned long amount)
{
   int err = CARRIER_OK - 1;
   int retries;

   if (ccb == NULL) return CARRIER_INIT;
   if (amount == 0) return CARRIER_OK;

   retries = ccb->Retries;
   while (err != CARRIER_OK && retries--)
      err = CarrierWrite(ccb, address, amount, buf);
   if (err == CARRIER_OK) {
      return amount;
   } else {
      return err;
   }
}

long CARRIER_Read(CCB * ccb, unsigned long address, void * buf, unsigned long bufsize, unsigned long amount)
{
   int err = CARRIER_OK - 1;
   int retries;

   if (ccb == NULL) return CARRIER_INIT;
   if (amount == 0) return CARRIER_OK;

   retries = ccb->Retries;
   while (err != CARRIER_OK && retries--)
      err = CarrierRead(ccb, address, amount, buf);
   if (err == CARRIER_OK) {
      return amount;
   } else {
      return err;
   }
}

long CARRIER_SetParam(CCB * ccb, const char * param_name, long param_value)
{
   if (strcmp(param_name, "VERSION") == 0) {
      if ((long )param_value <= V_UNDEF || (long)param_value >= HW_VERSIONS) return CARRIER_BAD_PARAMETER;
      ccb->HardwareVersion = param_value;
      SetHardware(ccb);
   } else if (strcmp(param_name, "CHECK_MODE") == 0) {
      if (param_value != NON_DESTRUCTIVE && param_value != DESTRUCTIVE) return CARRIER_BAD_PARAMETER;
      ccb->CheckMode = param_value;
   } else if (strcmp(param_name, "SIMULATE_HARDWARE") == 0) {
      ccb->SimulateHardware = param_value;
   } else if (strcmp(param_name, "SIMULATED_SIZE") == 0) {
	   if (ccb->SimulateHardware == 0) {
	      return CARRIER_NOT_SIMULATED;
	   } else {
			if (param_value == 4 || param_value == 8 || param_value == 32) {
				SetSimulatedSize(param_value);
			} else {
		      return CARRIER_INVALID_SIMULATED_SIZE;
			}
	   }
   } else if (strcmp(param_name, "DELAY_TIME") == 0) {
      if (param_value < 0) return CARRIER_BAD_PARAMETER;
      ccb->DelayTime = param_value;
   } else if (strcmp(param_name, "STABILITY") == 0) {
      if (param_value < 0) return CARRIER_BAD_PARAMETER;
      ccb->Stability = param_value;
   } else if (strcmp(param_name, "RETRIES") == 0) {
      if (param_value < 0) return CARRIER_BAD_PARAMETER;
      ccb->Retries = param_value + 1;
   } else {
      return CARRIER_PARAM_NOT_EXISTS;
   }
   return 0;
}
long CARRIER_GetParam(CCB * ccb, const char * param_name, long * param_value)
{
   *param_value = 0L;
   if (strcmp(param_name, "PORT_ADDRESS") == 0) {
      *param_value = ccb->PortAddress;
   } else if (strcmp(param_name, "VERSION") == 0) {
      *param_value = ccb->HardwareVersion;
   } else if (strcmp(param_name, "CHECK_MODE") == 0) {
      *param_value = ccb->CheckMode;
   } else if (strcmp(param_name, "DELAY_TIME") == 0) {
      *param_value = ccb->DelayTime;
   } else if (strcmp(param_name, "STABILITY") == 0) {
      *param_value = ccb->Stability;
   } else if (strcmp(param_name, "RETRIES") == 0) {
      *param_value = ccb->Retries;
   } else if (strcmp(param_name, "ADDR_LOW_PORT") == 0) {
      *param_value = ADR_LOW(ccb);
   } else if (strcmp(param_name, "ADDR_HIGH_PORT") == 0) {
      *param_value = ADR_HIGH(ccb);
   } else if (strcmp(param_name, "CMD_PORT") == 0) {
      *param_value = ADR_CMD(ccb);
   } else if (strcmp(param_name, "READ_PORT") == 0) {
      *param_value = ADR_READ(ccb);
   } else if (strcmp(param_name, "WRITE_PORT") == 0) {
      *param_value = ADR_WRITE(ccb);
   } else if (strcmp(param_name, "STATUS_PORT") == 0) {
      *param_value = STATUS(ccb);
   } else if (strcmp(param_name, "VALUE_LOW_PORT") == 0) {
      *param_value = _inp(ADR_LOW(ccb));
   } else if (strcmp(param_name, "VALUE_HIGH_PORT") == 0) {
      *param_value = _inp(ADR_HIGH(ccb));
   } else if (strcmp(param_name, "VALUE_CMD_PORT") == 0) {
      *param_value = _inp(ADR_CMD(ccb));
   } else if (strcmp(param_name, "VALUE_READ_PORT") == 0) {
      *param_value = _inp(ADR_READ(ccb));
   } else if (strcmp(param_name, "VALUE_WRITE_PORT") == 0) {
      *param_value = _inp(ADR_WRITE(ccb));
   } else if (strcmp(param_name, "VALUE_STATUS_PORT") == 0) {
      *param_value = _inp(STATUS(ccb));
   } else if (strcmp(param_name, "PAGE_MODE") == 0) {
      *param_value = ccb->PageMode;
   } else if (strcmp(param_name, "SIMULATE_HARDWARE") == 0) {
      *param_value = ccb->SimulateHardware;
   } else if (strcmp(param_name, "SIM_MEM_SIZE") == 0) {
      *param_value = ccb->SimulatedHardware->memsize;
   } else if (strcmp(param_name, "SIM_MEM_VAL0") == 0) {
      *param_value = ((unsigned char *)(ccb->SimulatedHardware->memory))[0];
   } else if (strcmp(param_name, "SIM_MEM_VAL1") == 0) {
      *param_value = ((unsigned char *)(ccb->SimulatedHardware->memory))[1];
   } else if (strcmp(param_name, "SIM_MEM_VAL2") == 0) {
      *param_value = ((unsigned char *)(ccb->SimulatedHardware->memory))[2];
   } else if (strcmp(param_name, "SIM_MEM_VAL3") == 0) {
      *param_value = ((unsigned char *)(ccb->SimulatedHardware->memory))[3];
   } else if (strcmp(param_name, "SIM_MEMORY") == 0) {
      *param_value = (long)ccb->SimulatedHardware->memory;
   } else {
      return CARRIER_PARAM_NOT_EXISTS;
   }
   return 0;
}


