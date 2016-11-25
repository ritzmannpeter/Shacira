
#ifndef _iqtmem
#define _iqtmem

/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     IQTMEM.H 
*
*  BESCHREIBUNG:
*     ...
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   01.04.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     01.04.92 -SF-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     Keine
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

/*.SI.***********************************************************************/
#include <syntax.h>
#include <sys/types.h>
/*.EI.***********************************************************************/

typedef long MEMORY_ADDRESS;

typedef struct bbram_data
{       BOOL available;
        long size;
        long free;
        long used;
}       BBRAM_DATA;

#define MAX_SEGMENT_NO                  4

#define STD_BBRAM                               0
#define BANKED_BBRAM                    1
#define EXP_BBRAM1                              2
#define EXP_BBRAM2                              3

#define PTR_INVALID(a)          (a < 0)
#define BBRAM_ADDRESS(a)        ((long)(a & 0x8fffffffL))
#define BBRAM_SEGMENT(a)        (((BYTE)(a >> 28) & 0x07))
#define SET_BBRAM_ADDRESS(s,a)  (((long)s << 28) | a)

#define FOREGROUND                      0
#define BACKGROUND                      1
#define BUFFER_NAME_LEN         26

#define ERR_MEM_INIT                                                    -700
#define ERR_MEM_FULL                                                    -701
#define ERR_MEM_NO_BLOCKS                                               -702
#define STORE_WRITE_ERROR                                               -703
#define STORE_UNKNOWN_VARIABLE                          -704
#define RESTORE_READ_ERROR                                      -705
#define RESTORE_UNKNOWN_VARIABLE                        -706
#define INSTALL_BUFFER_FULL                                     -707
#define INSTALL_READ_ERROR                                      -708
#define INSTALL_ALLOC_ERROR                                     -709
#define INSTALL_UNKNOWN_VARIABLE                        -710
#define STOREPART_INVALID_OFFSET                        -711
#define RESTOREPART_INVALID_OFFSET                      -712
#define STOREPART_WRITE_ERROR                           -713
#define RESTOREPART_READ_ERROR                          -714
#define STOREPART_UNKNOWN_VARIABLE                      -715
#define RESTOREPART_UNKNOWN_VARIABLE            -716
#define INVALID_SEGMENT                                         -717

/* Parameter-Id's fuer MemGetParam
 */
#define   FREE_DRAM            0
#define   ALLOC_DRAM           1
#define   SEG_GLOBAL_DATA      2
#define   FREE_BBRAM           3
#define   ALLOC_BBRAM          4
#define   SEG_BBRAM_FOREGROUND 5
#define   SEG_BBRAM_BACKGROUND 6
#define   FREE_EXP_BBRAM       7
#define   ALLOC_EXP_BBRAM      8
#define   SEG_EXP_BBRAM        9
#define   TASK_ALLOC_DRAM     10
#define   SAVE_MEM_IMAGE      11

GLOBAL int MemInit();
GLOBAL void * MemAlloc(size_t size);
GLOBAL void MemFree(void * ptr);
GLOBAL size_t MemAvail(void);
GLOBAL int MemGetParam(int id, long * param, int index);
GLOBAL int MemSetParam(int id, long param, int index);

GLOBAL int BBRAM_Init(BOOL * init);
GLOBAL int BBRAM_Freeze(BOOL init_bbram);
GLOBAL MEMORY_ADDRESS BBRAM_Alloc(long size, BYTE segment);
GLOBAL int BBRAM_Info(BYTE segment, BBRAM_DATA * info);
GLOBAL void BBRAM_SetBank(BYTE segment, int bank);
GLOBAL int BBRAM_GetBank(BYTE segment);
GLOBAL long BBRAM_Read(void * dst, MEMORY_ADDRESS src, long size);
GLOBAL long BBRAM_Write(MEMORY_ADDRESS dst, void * src, long size);
GLOBAL long BBRAM_Set(MEMORY_ADDRESS dst, BYTE value, long size);
GLOBAL int BBRAM_Clear();

GLOBAL long BBRAM_Getlong(MEMORY_ADDRESS dst);
GLOBAL UWORD BBRAM_GetWORD(MEMORY_ADDRESS dst);
GLOBAL int BBRAM_Getint(MEMORY_ADDRESS dst);
GLOBAL BYTE BBRAM_GetBYTE(MEMORY_ADDRESS dst);
GLOBAL char BBRAM_Getchar(MEMORY_ADDRESS dst);

GLOBAL int BBRAM_Setlong(MEMORY_ADDRESS dst, long val);
GLOBAL int BBRAM_SetWORD(MEMORY_ADDRESS dst, UWORD val);
GLOBAL int BBRAM_Setint(MEMORY_ADDRESS dst, int val);
GLOBAL int BBRAM_SetBYTE(MEMORY_ADDRESS dst, BYTE val);
GLOBAL int BBRAM_Setchar(MEMORY_ADDRESS dst, char val);

GLOBAL int BBRAM_CopyBank(BYTE segment, int dst_bank, int src_bank);
GLOBAL int BBRAM_ExchangeBanks(BYTE segment, int bank1, int bank2);

GLOBAL int BBRAM_Install(char * buf_name, void * buf_ptr, long size,
                                                                          BYTE segment, BOOL init);
GLOBAL int BBRAM_Store(void * buf_ptr);
GLOBAL int BBRAM_Restore(void * buf_ptr);
GLOBAL int BBRAM_StorePart(void * buf_ptr, long offset, long len);
GLOBAL int BBRAM_RestorePart(void * buf_ptr, long offset, long len);

#endif /* ifndef _iqtmem */










