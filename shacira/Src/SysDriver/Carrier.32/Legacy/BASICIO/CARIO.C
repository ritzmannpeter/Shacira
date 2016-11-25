
#ifndef __WIN32__

/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     CARIO
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
*     VERSION:    1.00                      DATUM:   25.03.96
*     AUTOR(EN):  P. Ritzmann               TELEFON: (0761) 45205-0
*
*  HISTORY:
*     23.12.98 -PR- Anpassungen an neue Hardware implementiert.
*     14.07.99 -PR- Hardware und Version zusaetzlich uber Konfigurationsdatei
*                   hardware.set einstellbar.
*     04.02.99 -PR- Nicht zerstoerende Checkfunktion eingebaut.
*     09.02.99 -PR- Konfiguration der Hardware ueber die Datei Hardware.set
*                   ausgebaut.
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
*     CAR_Module
*
*  DATENTYPEN:
*     
*  VARIABLEN:
*
*.EM.***********************************************************************/
/***************************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __stddef__
#include <stddef.h>
#define __stddef__
#endif
#ifndef __stdlib__
#include <stdlib.h>
#define __stdlib__
#endif
#ifndef __stdio__
#include <stdio.h>
#define __stdio__
#endif
#ifndef __string__
#include <string.h>
#define __string__
#endif
#ifndef __conio__
#include <conio.h>
#define __conio__
#endif
#ifndef __errcode__
#include <errcode.h>
#define __errcode__
#endif
#ifndef __debug__
#include <debug.h>
#define __debug__
#endif
#ifndef __basicio__
#include <basicio.h>
#define __basicio__
#endif
#ifndef __cario__
#include <cario.h>
#define __cario__
#endif
#ifdef __WATCOMC__
#ifndef __i86__
#include <i86.h>
#define __i86__
#endif
#else
#ifndef __dos__
#include <dos.h>
#define __dos__
#endif
#endif
/***************************************************************************/

#define _inp(p)         inp((p))
#define _outp(p,b)      outp((p),(b))
#define WaitMS(ms)      delay(ms)
#define _enable()
#define _disable()

/* Hardware
 */
#define V_UNDEF   -1
#define V_0       0
#define V_1       1
#define HW_VERSIONS  (V_1 + 1)
typedef struct {
   unsigned int addr_low;
   unsigned int addr_high;
   unsigned int addr_cmd;
   unsigned int addr_write;
	unsigned int addr_read;
   unsigned int status;
}  DNC_REGS;

typedef struct
{  unsigned short io_base;
   int version;
   DNC_REGS regs[HW_VERSIONS];
}  DNC_HW;

LOCAL DNC_HW DncHWDefault =
{  0x360,
   V_UNDEF,
   {  {0x0, 0x1, 0x2, 0x3, 0x4, 0x5},
      {0x0, 0x1, 0x4, 0x2, 0x3, 0x5}
   }
};

LOCAL DNC_HW DncHW = {{0}};

#define DESTRUCTIVE         0
#define NON_DESTRUCTIVE     1

LOCAL int HWVersion = V_UNDEF;
LOCAL unsigned int IOBaseAddress = 0x360;
LOCAL int CheckMode = DESTRUCTIVE;
LOCAL int ProgDelay = 15;
LOCAL int ReadStability = 5;
LOCAL int ReadRetries = 50;

LOCAL int C_HWVersion = V_UNDEF;
LOCAL unsigned int C_IOBaseAddress = 0x360;
LOCAL int C_CheckMode = DESTRUCTIVE;
LOCAL int C_ProgDelay = 15;
LOCAL int C_ReadStability = 5;
LOCAL int C_ReadRetries = 50;

LOCAL int ReadByte(USR_LONG address, USR_BYTE * value);
LOCAL int WriteByte(USR_LONG address, USR_BYTE value, USR_BYTE page_mode, int delay_size);

LOCAL void PrintHWSettings(void)
{
	LogPrintf("hardware.log", "\nbase IO address  : %04x\n", IOBaseAddress);
	LogPrintf("hardware.log", "version           : %d\n", HWVersion);
	LogPrintf("hardware.log", "check mode        : %d\n", CheckMode);
	LogPrintf("hardware.log", "programming delay : %d\n", ProgDelay);
   LogPrintf("hardware.log", "read stability    : %d\n", ReadStability);
   LogPrintf("hardware.log", "read retries      : %d\n\n", ReadRetries);
}

LOCAL int ReadLine(FILE * stream, char * line, int len)
{  int c, i = 0;
   char * line_ptr = line;

   While ((c = fgetc(stream)) != EOF) Do
      If (i >= len - 1) Then
         line[len - 1] = 0;
         return TRUE;
      Endif
      If (c == '\n') Then
         *line_ptr = 0;
         return TRUE;
		Else
         *line_ptr = c;
         line_ptr++;
         i++;
      Endif
   Endwhile
   If (i == 0) Then
      return FALSE;
   Else
      line[i] = 0;
      return TRUE;
   Endif
}

LOCAL void ReadIOBaseAddress(char * line)
{  unsigned int io_base = 0x00;

   If (sscanf(line, "IOBASE=%x", &io_base) == 1) Then
      If (io_base < 0x100 || io_base > 0x400) Then
         LogPrintf("hardware.log", "invalid value %04x for io base address (100 - 400)\n", io_base);
         LogPrintf("hardware.log", "using default");
      Else
         C_IOBaseAddress = IOBaseAddress = io_base;
         LogPrintf("hardware.log", "set base IO address to %04x\n", IOBaseAddress);
      Endif
   Endif
}

LOCAL void ReadHWVersion(char * line)
{  int version = 0;

   If (sscanf(line, "VERSION=%d", &version) == 1) Then
      If (version < V_0 || version > V_1) Then
         LogPrintf("hardware.log", "invalid value %d for hardware version (0 - 1)\n", version);
      Else
         C_HWVersion = HWVersion = version;
         LogPrintf("hardware.log", "set hardware version to %d\n", HWVersion);
      Endif
   Endif
}

LOCAL void ReadCheckMode(char * line)
{  int checkmode = 0;

   If (sscanf(line, "CHECKMODE=%d", &checkmode) == 1) Then
      If (checkmode < DESTRUCTIVE || checkmode > NON_DESTRUCTIVE) Then
         LogPrintf("hardware.log", "invalid value %d for check mode (0 - 1)\n", checkmode);
      Else
         C_CheckMode = CheckMode = checkmode;
         LogPrintf("hardware.log", "set check mode to %d\n", CheckMode);
      Endif
   Endif
}

LOCAL void ReadProgDelay(char * line)
{  int progdelay = 0;

   If (sscanf(line, "PROGDELAY=%d", &progdelay) == 1) Then
      If (progdelay < 10 || progdelay > 50) Then
         LogPrintf("hardware.log", "invalid value %d for programming delay (10 - 50)\n", progdelay);
      Else
         C_ProgDelay = ProgDelay = progdelay;
         LogPrintf("hardware.log", "set programming delay to %d\n", ProgDelay);
      Endif
   Endif
}

LOCAL void ReadReadStability(char * line)
{  int read_stability = 0;

   If (sscanf(line, "READSTABILITY=%d", &read_stability) == 1) Then
      If (read_stability < 1 || read_stability > 50) Then
         LogPrintf("hardware.log", "invalid value %d for read stability (1 - 50)\n", read_stability);
      Else
         C_ReadStability = ReadStability = read_stability;
         LogPrintf("hardware.log", "set read stabilty to %d\n", ReadStability);
      Endif
   Endif
}

LOCAL void ReadReadRetries(char * line)
{  int read_retries = 0;

   If (sscanf(line, "READRETRIES=%d", &read_retries) == 1) Then
		If (read_retries < 50 || read_retries > 1000) Then
         LogPrintf("hardware.log", "invalid value %d for read retries (50 - 1000)\n", read_retries);
      Else
         C_ReadRetries = ReadRetries = read_retries;
         LogPrintf("hardware.log", "set read retries to %d\n", ReadRetries);
      Endif
   Endif
}

LOCAL char Line[512] = {0};
LOCAL void LoadHWSettings()
{  FILE * stream = fopen("hardware.set", "r");
        
   LogPrintf("hardware.log", "configuring Hardware\n");
   If (stream) Then
      LogPrintf("hardware.log", "hardware settings file openend\n");
      While (ReadLine(stream, &Line, sizeof(Line))) Do
         ReadIOBaseAddress(Line);
         ReadHWVersion(Line);
         ReadCheckMode(Line);
         ReadProgDelay(Line);
         ReadReadStability(Line);
         ReadReadRetries(Line);
      Endwhile
      fclose(stream);
   Else
      LogPrintf("hardware.log", "no hardware settings using defaults\n");
   Endif
	PrintHWSettings();
}

LOCAL void SetDncHW(DNC_HW * hw)
{  int i;

   memcpy(hw, &DncHWDefault, sizeof(*hw));
   hw->io_base = IOBaseAddress;
   For (i=0; i<HW_VERSIONS; i++) Do
      LogPrintf("hardware.log", "hardware %d: ", i);
      hw->regs[i].addr_low += hw->io_base;
      LogPrintf("hardware.log", "addr_low %04x: ", hw->regs[i].addr_low);
      hw->regs[i].addr_high += hw->io_base;
      LogPrintf("hardware.log", "addr_high %04x: ", hw->regs[i].addr_high);
      hw->regs[i].addr_cmd += hw->io_base;
      LogPrintf("hardware.log", "addr_cmd %04x: ", hw->regs[i].addr_cmd);
      hw->regs[i].addr_write += hw->io_base;
      LogPrintf("hardware.log", "addr_write %04x: ", hw->regs[i].addr_write);
      hw->regs[i].addr_read += hw->io_base;
      LogPrintf("hardware.log", "addr_read %04x: ", hw->regs[i].addr_read);
      hw->regs[i].status += hw->io_base;
      LogPrintf("hardware.log", "status %04x:\n", hw->regs[i].status);
   Endfor
   hw->version = HWVersion;
}

LOCAL USR_BOOL InitHW(DNC_HW * hw)
{
	If (HWVersion == V_UNDEF) Then
      LogPrintf("hardware.log", "undefined hardware version\n");
      return FALSE;
   Else
      SetDncHW(hw);
      return TRUE;      
   Endif
}

#define ADR_LOW     (DncHW.regs[DncHW.version].addr_low)
#define ADR_HIGH    (DncHW.regs[DncHW.version].addr_high)
#define ADR_CMD     (DncHW.regs[DncHW.version].addr_cmd)
#define ADR_WRITE   (DncHW.regs[DncHW.version].addr_write)
#define ADR_READ    (DncHW.regs[DncHW.version].addr_read)
#define STATUS      (DncHW.regs[DncHW.version].status)

/* state */
#define DATA_CARRIER_TEST               0x02
#define DATA_CARRIER_READY              0x08
#define DATA_CARRIER_WPROT              0x10

/* commands */
#define NO_OP           0xff
#define NO_OP_W         0x7f
#define READ_OP         0xf9

#define SELECT_R        0xfb 

#define WRITE_OP        0x7a
#define SELECT_W        0x7b

#define PAGE_SIZE        64UL
#define OFF              0
#define ON               1

/* Treiber-Parameterblock
 */
typedef struct
{  USR_BYTE page_mode;
   USR_LONG carrier_size;
   int retries;
   int delay_size;
   DNC_HW * hw;
}  CPB;
LOCAL CPB * Cpb = NULL;
LOCAL CPB CarrierControlBlock = {0};

LOCAL short CarrierState()
{  short state;
   state = 0x00ff & _inp(STATUS);
   If ((state & 1) == 1) Then
      return DCAR_NOT_FOUND;
   Else
      return DCAR_OK;
   Endif
}

#define BUFSIZE 0x40
LOCAL int GetSizeNonDestruct(CPB * cpb)
{  int i;
   char buf0[BUFSIZE] = {0};
   char buf4[BUFSIZE] = {0};
   char buf8[BUFSIZE] = {0};
   For (i=0; i<BUFSIZE; i++) Do
      ReadByte((unsigned long)i, &buf0[i]);
      ReadByte((unsigned long)i + 0x1000, &buf4[i]);
      ReadByte((unsigned long)i + 0x2000, &buf8[i]);
   Endfor
   cpb->page_mode = OFF;
   If (memcmp(buf0, buf8, BUFSIZE) != 0) Then
      cpb->page_mode = ON;
      cpb->carrier_size = (long)32 * 1024L;
      return 32;
   Elseif (memcmp(buf0, buf4, BUFSIZE) != 0) Then
      cpb->carrier_size = (long)8 * 1024L;
      return 8;
   Else
      cpb->carrier_size = (long)4 * 1024L;
      return 4;
   Endif
}

#define WAIT WaitMS(10);

LOCAL int GetSizeDestruct(CPB * cpb)
{  int size;
   USR_BYTE ch1, ch3, ch0, ch2, ch4, ch8, ch32;

   ReadByte(0lu, &ch0);
   ReadByte(2048lu, &ch2);
   ReadByte(4096lu, &ch4);
   ReadByte(8192lu, &ch8);
   ReadByte(32768lu, &ch32);

   size = DCAR_0K;
   WriteByte(0lu, 'A', OFF, cpb->delay_size);
   WriteByte(2048lu, 'B', OFF, cpb->delay_size);
   ReadByte(0lu, &ch1);
   ReadByte(2048lu, &ch3);
   if (ch1 != ch3) size = DCAR_4K;

   WriteByte(0lu, 'A', OFF, cpb->delay_size);
   WriteByte(4096lu, 'B', OFF, cpb->delay_size);
   ReadByte(0lu, &ch1);
   ReadByte(4096lu, &ch3);
   if (ch1 != ch3) size = DCAR_8K;

   WriteByte(0lu, 'A', OFF, cpb->delay_size);
   WriteByte(8192lu, 'B', OFF, cpb->delay_size);
   ReadByte(0lu, &ch1);
   ReadByte(8192lu, &ch3);
   if (ch1 != ch3) size = DCAR_32K;

   WriteByte(0lu, 'A', OFF, cpb->delay_size);
   WriteByte(32768lu, 'B', OFF, cpb->delay_size);
   ReadByte(0lu, &ch1);
   ReadByte(32768lu, &ch3);
   if (ch1 != ch3) size = DCAR_64K;

   WriteByte(0lu, ch0, OFF, cpb->delay_size);
   WriteByte(2048lu, ch2, OFF, cpb->delay_size);
   WriteByte(4096lu, ch4, OFF, cpb->delay_size);
   WriteByte(8192lu, ch8, OFF, cpb->delay_size);
   WriteByte(32768lu, ch32, OFF, cpb->delay_size);
          
   If (size >= DCAR_32K) Then
      cpb->page_mode = ON;
      ReadByte(2lu, &ch0);
      ReadByte(1lu, &ch4);
      WriteByte(2lu, 'A', ON, cpb->delay_size);
      WriteByte(1lu, 'A', ON, cpb->delay_size);
      WaitMS(cpb->delay_size);
      WriteByte(2lu, 'B', ON, cpb->delay_size);
      WriteByte(1lu, 'B', ON, cpb->delay_size);
      WaitMS(cpb->delay_size);
      ReadByte(2lu, &ch1);
      ReadByte(1lu, &ch3);                          
      If ((ch1 == 'B') && ('B' == ch3)) Then
         cpb->page_mode = ON;
      Else
			cpb->page_mode = OFF;
      Endif
      WriteByte(2lu, ch0, OFF, cpb->delay_size);
      WriteByte(1lu, ch4, OFF, cpb->delay_size);
   Else          
      cpb->page_mode = OFF;
   Endif
   cpb->carrier_size = (long)size * 1024L;
   return size;
}

LOCAL int CarrierCheck(CPB * cpb)
{  short state;
   
   cpb->carrier_size = 0L;
   cpb->page_mode = OFF;
   state = _inp(STATUS);
   if ((state & 1) == 1) return DCAR_NOT_FOUND;
/* Die neueste Hardware liefert das Signal so nicht
   if ((state & 2) == 0) return DCAR_NOT_READY;
 */
   If (cpb->hw->version == V_0) Then
      if ((state & 2) == 0) return DCAR_NOT_READY;
   Endif
   If (CheckMode == DESTRUCTIVE) Then
      return GetSizeDestruct(cpb);
   Else
      return GetSizeNonDestruct(cpb);
	Endif
}

//#define MAXTESTS         50
//#define STABILITY        5
//#define MAXTESTS         500
//#define STABILITY        50

#define _read_byte(v,a,m,e)\
{  int count = 0;\
   long abscount = 0;\
   unsigned char cval;\
   _outp(ADR_CMD, NO_OP);\
   _outp(ADR_LOW, (unsigned char)(a));\
   _outp(ADR_HIGH, (unsigned char)((unsigned short)(a) >> 8));\
   _disable();\
   _outp(ADR_CMD, SELECT_R & (m));\
   _outp(ADR_CMD, READ_OP & (m));\
   _enable();\
   v = _inp(ADR_READ);\
   cval = v;\
   While (count < ReadStability && abscount < ReadRetries) Do\
      v = _inp(ADR_READ);\
      If (v == cval) Then\
         count++;\
      Else\
         count = 0;\
         cval = v;\
		Endif\
      abscount++;\
   Endwhile\
   _outp(ADR_CMD, NO_OP);\
   If (abscount >= ReadRetries) Then\
      e = DCAR_READ_ERROR;\
   Endif\
}

#define VALUE 5

LOCAL int _ReadByte(USR_LONG address, USR_BYTE * value)
{  short state;
   unsigned char mask;
   int line = (int)((address & 0x1800L) >> 11);
   unsigned char val1 = VALUE, val2 = VALUE, val3 = VALUE, val4 = VALUE, val5 = VALUE;
   
   Switch(line)
   Case 0: mask = 0xF7; break;
   Case 1: mask = 0xEF; break;
   Case 2: mask = 0xDF; break;
   Case 3: mask = 0xBF; break;
   Default: mask = 0xFF; break;
   Endswitch

   state = CarrierState();
   If (state == DCAR_OK) Then
      _read_byte(val1, address, mask, state)
		If (state == DCAR_READ_ERROR) Then
         LogPrintf("hardware.log", "read error at %04x\n", address);
         return state;
      Endif
      _read_byte(val2, address, mask, state)
      If (state == DCAR_READ_ERROR) Then
         LogPrintf("hardware.log", "read error at %04x\n", address);
         return state;
      Endif
      _read_byte(val3, address, mask, state)
      If (state == DCAR_READ_ERROR) Then
         LogPrintf("hardware.log", "read error at %04x\n", address);
         return state;
      Endif
      _read_byte(val4, address, mask, state)
      If (state == DCAR_READ_ERROR) Then
         LogPrintf("hardware.log", "read error at %04x\n", address);
         return state;
      Endif
      _read_byte(val5, address, mask, state)
      If (state == DCAR_READ_ERROR) Then
         LogPrintf("hardware.log", "read error at %04x\n", address);
         return state;
      Endif
      If (val1 == val2 && val2 == val3 && val3 == val4 && val4 == val5) Then
         *value = val1;
         return DCAR_OK;
      Else
			*value = 0xaa;
         LogPrintf("hardware.log", "read failed at %04x\n", address);
         state = DCAR_READ_FAILED;
      Endif
   Endif
   return state;
}

LOCAL USR_BYTE LastByte = 55;

LOCAL int ReadByte(USR_LONG address, USR_BYTE * value)
{  int err = USR_NO_ERROR - 1;
   int tries = 10;

   While (err != USR_NO_ERROR && tries--) Do
      err = _ReadByte(address, value);
      If (err != USR_NO_ERROR) Then
         WaitMS(2);
      Endif
   Endwhile
   If (err == USR_NO_ERROR) Then
      LastByte = *value;
   Else
//      LogPrintf("carrier.log", "read error %d at %06ld last byte is %02x\n", err, address, LastByte);
   Endif   
   return err;
}

LOCAL int WriteByte(USR_LONG address, USR_BYTE value, USR_BYTE page_mode, int delay_size)
{  short state;
   unsigned char mask;
   int line = (int)((address & 0x1800L) >> 11);
   
   Switch(line)
   Case 0: mask = 0xF7; break;
   Case 1: mask = 0xEF; break;
   Case 2: mask = 0xDF; break;
   Case 3: mask = 0xBF; break;
   Default: mask = 0xFF; break;
   Endswitch
   if (!page_mode) _disable();
   state = CarrierState();
   If (state == DCAR_OK) Then
      _outp(ADR_CMD, NO_OP);
      _outp(ADR_LOW, (unsigned char)address);
      _outp(ADR_HIGH, (unsigned char)((unsigned short)address >> 8));
      _outp(ADR_CMD, SELECT_W & mask);
      _outp(ADR_WRITE, value);
      _outp(ADR_CMD, WRITE_OP & mask);
      _outp(ADR_CMD,SELECT_W & mask);
      _outp(ADR_CMD, NO_OP_W & mask);
      _outp(ADR_CMD, NO_OP);
        Else
                LogPrintf("hardware.log", "write failed at %04x: %d\n", address, state);
   Endif
   If (!page_mode) Then
      WaitMS(delay_size);
      _enable();
   Endif
   return state;
}

LOCAL int WritePage(USR_LONG address, USR_LONG size, void * buffer, CPB * cpb)
{  short state;
   int delay_size = cpb->delay_size;
   USR_BYTE page_mode = cpb->page_mode;
   USR_LONG limit = address + size;
   register USR_BYTE * buf_ptr;
   register USR_LONG i;

   If (page_mode == ON) Then
      _disable();
      For (i=address, buf_ptr=buffer; i<limit; i++, buf_ptr++) Do
         If ((state = WriteByte(i, *buf_ptr, ON, delay_size)) != DCAR_OK) Then
            _enable();
            return state;
         Endif
      Endfor
      WaitMS(delay_size);
      _enable();
      return DCAR_OK;
   Else
      return DCAR_INVALID_MODE;
   Endif
}

LOCAL int CarrierRead(CPB * cpb, USR_LONG address, USR_LONG size, void * buffer)
{  short state;
   USR_BYTE * buf_ptr;
   USR_LONG i, limit = address + size;

   DebugPrintf(DEBUG_CARIO, "read request %ld bytes at %ld\n", size, address);
   If (size == 0L) Then
      DebugPrintf(DEBUG_CARIO, "read failed: null size\n");
      return DCAR_ADR_ERROR;
   Endif
   If (limit > cpb->carrier_size) Then
      DebugPrintf(DEBUG_CARIO, "read failed: invalid address %ld\n", limit);
      return DCAR_ADR_ERROR;
   Endif

   For (i=address, buf_ptr=buffer; i<limit; i++, buf_ptr++) Do
      If ((state = ReadByte(i, buf_ptr)) != DCAR_OK) Then
         DebugPrintf(DEBUG_CARIO, "read failed at %ld state %d\n", i, state);
         return state;
      Endif
   Endfor
   DebugPrintf(DEBUG_CARIO, "%ld bytes read at %ld\n", size, address);
   return DCAR_OK;
}     

#define VERIFY_BUF_SIZE    256
LOCAL USR_BYTE VerifyBuf[VERIFY_BUF_SIZE];

LOCAL int CarrierWrite(CPB * cpb, USR_LONG address, USR_LONG size, void * buffer)
{  short state;
   USR_BYTE * buf_ptr;
   USR_LONG i, limit = address + size, write_size, page_no;
   USR_LONG bytes_to_process = size;

   DebugPrintf(DEBUG_CARIO, "write request %ld bytes at %ld\n", size, address);
   If (size == 0L) Then
      DebugPrintf(DEBUG_CARIO, "write failed: null size\n");
      return DCAR_ADR_ERROR;
   Endif
   If (limit > cpb->carrier_size) Then
      DebugPrintf(DEBUG_CARIO, "write failed: invalid address %ld\n", limit);
      return DCAR_ADR_ERROR;
   Endif

   If (cpb->page_mode == OFF) Then
      For (i=address, buf_ptr=buffer; i<limit; i++, buf_ptr++) Do
         If ((state = WriteByte(i, *buf_ptr, OFF, cpb->delay_size)) != DCAR_OK) Then
            DebugPrintf(DEBUG_CARIO, "write failed at %ld state %d\n", i, state);
            return state;
         Endif
      Endfor
   Else
      i = address;
      buf_ptr = buffer;
      page_no = address / PAGE_SIZE;
      write_size = ((page_no + 1) * PAGE_SIZE) - address;
      If (bytes_to_process > write_size) Then
         /* Der Puffer geht ueber mehrere Seiten
          */
         If ((state = WritePage(i, write_size, buf_ptr, cpb)) != DCAR_OK) Then
            DebugPrintf(DEBUG_CARIO, "write failed at %ld state %d\n", i, state);
            return state;
         Endif
         i += write_size;
         buf_ptr += write_size;
         bytes_to_process -= write_size;
         While (bytes_to_process > PAGE_SIZE) Do
            /* Vollstaendige Seiten
             */
            If ((state = WritePage(i, PAGE_SIZE, buf_ptr, cpb)) != DCAR_OK) Then
               DebugPrintf(DEBUG_CARIO, "write failed at %ld state %d\n", i, state);
               return state;
            Endif
            i += PAGE_SIZE;
            buf_ptr += PAGE_SIZE;
            bytes_to_process -= PAGE_SIZE;
         Endwhile
         If (bytes_to_process > 0) Then
            If ((state = WritePage(i, bytes_to_process, buf_ptr, cpb)) != DCAR_OK) Then
               DebugPrintf(DEBUG_CARIO, "write failed at %ld state %d\n", i, state);
               return state;
            Endif
         Endwhile
      Else
         /* Der gesamte Puffer kommt in einer Seite unter
          */
         If ((state = WritePage(address, bytes_to_process, buffer, cpb)) != DCAR_OK) Then
            DebugPrintf(DEBUG_CARIO, "write failed at %ld state %d\n", i, state);
            return state;
         Endif
      Endif
   Endif
   
   /* Verify
    */
   i = address;
   buf_ptr = buffer;
   bytes_to_process = size;
   While (bytes_to_process > VERIFY_BUF_SIZE) Do
      If ((state = CarrierRead(cpb, i, VERIFY_BUF_SIZE, VerifyBuf)) != DCAR_OK) Then
         DebugPrintf(DEBUG_CARIO, "write failed reading for verify at %ld state %d\n", i, state);
         return state;
      Endif
      If (memcmp(VerifyBuf, buf_ptr, VERIFY_BUF_SIZE)) Then
         DebugPrintf(DEBUG_CARIO, "verify failed at %ld\n", i);
         return DCAR_VERIFY_ERROR;
      Endif
      i += VERIFY_BUF_SIZE;
      buf_ptr += VERIFY_BUF_SIZE;
      bytes_to_process -= VERIFY_BUF_SIZE;
   Endwhile
   If (bytes_to_process > 0) Then
      If ((state = CAR_Read(i, bytes_to_process, VerifyBuf)) != DCAR_OK) Then
         DebugPrintf(DEBUG_CARIO, "write failed reading for verify at %ld state %d\n", i, state);
         return state;
      Endif
      If (memcmp(VerifyBuf, buf_ptr, bytes_to_process)) Then
         DebugPrintf(DEBUG_CARIO, "verify failed at %ld\n", i);
         return DCAR_VERIFY_ERROR;
      Endif
   Endwhile
   DebugPrintf(DEBUG_CARIO, "%ld bytes written at %ld\n", size, address);
   return DCAR_OK;
}     

LOCAL int CAR_Init(int delay_size, char * path, IO_MODULE_ ** module)
{  CPB * cpb;

/* Poor man's union: so wars eigentlich nicht beabsichtigt
 */
   If (Cpb == NULL) Then
/* Diese Konstruktion fuehrt in der DLL-Version zu massiven Problemen, weil
 * der Speicher scheinbar nach erfolgtem DLL-Funktionsaufruf wieder 
 * jedem zur Verfuegung steht (???) das muá mal generell geprueft werden.
      if ((cpb = (CPB*)malloc(sizeof(CPB))) == NULL) return DCAR_NO_MEMORY;
 * also
 */
      cpb = &CarrierControlBlock;
      LoadHWSettings();
      If (InitHW(&DncHW)) Then
         cpb->carrier_size = 0L;
         cpb->page_mode = OFF;
         cpb->retries = 3;
         cpb->delay_size = ProgDelay;
         cpb->hw = &DncHW;
         Cpb = cpb;
         *module = CAR_Module();
         return DCAR_OK;
      Else
         Cpb = NULL;
         *module = CAR_Module();
         return DCAR_INIT;
      Endif
   Else
      *module = CAR_Module();
      return DCAR_OK;
   Endif
}

LOCAL int CAR_Exit()
{
   if (Cpb == NULL) return DCAR_INIT;
   free(Cpb);
   return USR_NO_ERROR;
}

LOCAL int CAR_Check()
{  CPB * cpb = Cpb;

   if (cpb == NULL) return DCAR_INIT;
   return CarrierCheck(cpb);
}

LOCAL int CAR_Write(USR_LONG address, USR_LONG size, void * buffer)
{  int err = USR_NO_ERROR - 1;
   CPB * cpb;
   int retries;

   cpb = Cpb;
   if (cpb == NULL) return DCAR_INIT;
   if (size == 0) return USR_NO_ERROR;

   retries = cpb->retries;
   While (err != USR_NO_ERROR && retries--) Do
      err = CarrierWrite(cpb, address, size, buffer);
   Endwhile
   return err;   
}

LOCAL int CAR_Read(USR_LONG address, USR_LONG size, void * buffer)
{  int err = USR_NO_ERROR - 1;
   CPB * cpb;
   int retries;

   cpb = Cpb;
   if (cpb == NULL) return DCAR_INIT;
   if (size == 0) return USR_NO_ERROR;

   retries = cpb->retries;
   While (err != USR_NO_ERROR && retries--) Do
      err = CarrierRead(cpb, address, size, buffer);
   Endwhile
   return err;   
}

LOCAL const IO_MODULE CarIoModule =
{  CAR_Init,
   CAR_Check,
   CAR_Read,
   CAR_Write,
   CAR_Exit
};

GLOBAL const IO_MODULE * CAR_Module()
{
   return &CarIoModule;
}

#endif



