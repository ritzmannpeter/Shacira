
#ifndef _bbram
#define _bbram

/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     BBRAM.H
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
*     01.04.92 -PR-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     20.05.92 -PR-    DSConvTabP entfernt
*     09.06.92 -SF-    TextTabP nun (char**) statt (ULONG)
*     10.06.92 -PR-    Schalter NO_BBRAM_MACROS eingefuehrt
*     11.06.92 -SF-    <spc.h> einbinden, da SPCNO dort definiert ist
*                      SPC-Variable erhalten Praefix "Bbr_"
*     16.06.92 -SF-    ErrTextTabP, MaxErrTextTab, FOT_ConfigTabP,
*                      Bbr_SPCValuePTab, Bbr_SPCPreTestValuePTab entfernt
*                      (==> dummy1-dummy5 definiert).
*                      FreeObjTab in Bbr_FreeObjTab umbenannt.
*     09.07.92 -SF-    PTYPE durch UWORD ersetzt (==> je 1 Byte weniger, also
*                      dummy10 und 11 eingebaut)
*                      BDE-Variable in Bbr_BDE umbenannt
*     15.07.92 -SF-    WClock-Variable in Bbr_WClock umbenannt
*     21.08.92 -SF-    BitMapAdrP und MaxBitMapAdr in dummy's umbenannt
*     09.10.92 -PR-    Allle dummys rausgenommen
*     26.01.99 -TSchw- ErrBuf eingefuegt, neuer BBRam Fehlerpuffer
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
#ifndef _stddef
#include <stddef.h>
#define _stddef
#endif
#ifndef _trend
#include <trend.h>
#define _trend
#endif
#ifndef _iqtmem
#include <iqtmem.h>
#define _iqtmem
#endif
#ifndef _spc
#include <spc.h>
#define _spc
#endif
/*.EI.***********************************************************************/

typedef struct gen_bbram_type
{       MEMORY_ADDRESS DiagBuf__;
        MEMORY_ADDRESS RegPhysBuf__;
        MEMORY_ADDRESS IqtRegBuf__;
        MEMORY_ADDRESS BitPhysBuf__;
        MEMORY_ADDRESS IqtBitBuf__;
        MEMORY_ADDRESS TextBuf__;
        MEMORY_ADDRESS CLBBuf__[3];
        MEMORY_ADDRESS TrendValBuf__[TREND_NO];
        MEMORY_ADDRESS ErrBuf__;
}       GEN_BBRAM_TYPE;

#define _DiagBuf                        ((long)offsetof(GEN_BBRAM_TYPE, DiagBuf__))
#define _RegPhysBuf                     ((long)offsetof(GEN_BBRAM_TYPE, RegPhysBuf__))
#define _IqtRegBuf                      ((long)offsetof(GEN_BBRAM_TYPE, IqtRegBuf__))
#define _BitPhysBuf                     ((long)offsetof(GEN_BBRAM_TYPE, BitPhysBuf__))
#define _IqtBitBuf                      ((long)offsetof(GEN_BBRAM_TYPE, IqtBitBuf__))
#define _TextBuf                        ((long)offsetof(GEN_BBRAM_TYPE, TextBuf__))
#define _CLBBuf                         ((long)offsetof(GEN_BBRAM_TYPE, CLBBuf__))
#define _TrendValBuf            ((long)offsetof(GEN_BBRAM_TYPE, TrendValBuf__))
#define _ErrBuf                         ((long)offsetof(GEN_BBRAM_TYPE, ErrBuf__))

typedef struct bbram_type {
int dummy;
} BBRAM_TYPE;

#endif      /* #ifndef _bbram */
