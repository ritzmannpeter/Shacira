/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVPRN
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
*     21.06.93 -PR-    PCB_TYP - Definition wieder ins Modul zurueck
*     05.03.98 -TSchw- PRN_LANGUAGE, PRN_ID_LANGUAGE und PRN_PRG_LANGUAGE_TAB
*                      eingefuegt
*     10.03.00 -TSchw- PRN_ID_BITMAP_CAP, PRN_MD_BITMAP eingefuehrt
*     13.12.02 -HA-    PRN_GET_MARG_LOWER logische Verundung mit 0x0000ffff
*
*
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

#ifndef _devprn_
#define _devprn_

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
#include <iqttsk.h>
/*.EI.***********************************************************************/

/*********************************************************************
*  PRN-Treiber: DATENTYPEN
*********************************************************************/

typedef struct {
   IQT_HANDLE ComHnd;
   void ** ProgList;
   PARAMETER Mode;
   TIME Timeout;
} PRN_PARAM_BLOCK;

typedef struct {
   BYTE Dummy;
} PRN_INIT_BLOCK;

typedef struct {
   char code;
   BYTE type;
} PRN_CTAB_ENTRY;

typedef union {
   UWORD sval;
   PRN_CTAB_ENTRY codtyp;
} PRN_CODETAB;

typedef struct {
   char *language;
   char *esc_seq;
} PRN_LANGUAGE;

/*********************************************************************
*  PRN-Treiber: Druckvarianten
*********************************************************************/

#define PRN_MD_LINE     0x00L
#define PRN_MD_TDUMP    0x01L
#define PRN_MD_GDUMP    0x02L
#define PRN_MD_RAW      0x03L
#define PRN_MD_BITMAP   0x04L

/*********************************************************************
*  PRN-Treiber: ZUGRIFFSMACROS FUER PARAMETER 
*********************************************************************/

#define PRN_GET_MARG_LOWER( p )  ( (unsigned int)(p & 0x0000ffff) )
#define PRN_GET_MARG_UPPER( p )  ( (unsigned int)( (p)>>16 ) )

#define PRN_MAKE_MARG( u,l )     ( (unsigned long)(u)<<16 | (unsigned long)(l) )

/*********************************************************************
*  PRN-Treiber: FARBEN  
*********************************************************************/

#ifndef COLOR_BLACK
#define COLOR_BLACK          ((unsigned int) 0)
#define COLOR_RED            ((unsigned int) 1)
#define COLOR_GREEN          ((unsigned int) 2)
#define COLOR_BROWN          ((unsigned int) 3)
#define COLOR_BLUE           ((unsigned int) 4)
#define COLOR_MAGENTA        ((unsigned int) 5) 
#define COLOR_CYAN           ((unsigned int) 6)
#define COLOR_GRAY           ((unsigned int) 7)
#define COLOR_DARK_GRAY      ((unsigned int) 8)
#define COLOR_LIGHT_RED      ((unsigned int) 9)
#define COLOR_LIGHT_GREEN   ((unsigned int) 10)
#define COLOR_YELLOW        ((unsigned int) 11)
#define COLOR_LIGHT_BLUE    ((unsigned int) 12)
#define COLOR_LIGHT_MAGENTA ((unsigned int) 13)
#define COLOR_LIGHT_CYAN    ((unsigned int) 14)

#define PRN_COLOR_WHITE     ((unsigned int) 15)
#endif

#define MIX_BLACK           ((unsigned int) (((unsigned int)1) << COLOR_BLACK)                )
#define MIX_RED             ((unsigned int) (((unsigned int)1) << COLOR_RED)                  )
#define MIX_GREEN           ((unsigned int) (((unsigned int)1) << COLOR_GREEN)                )
#define MIX_BROWN           ((unsigned int) (((unsigned int)1) << COLOR_BROWN)                )
#define MIX_BLUE            ((unsigned int) (((unsigned int)1) << COLOR_BLUE)                 )
#define MIX_MAGENTA         ((unsigned int) (((unsigned int)1) << COLOR_MAGENTA)              )
#define MIX_CYAN            ((unsigned int) (((unsigned int)1) << COLOR_CYAN)                 )
#define MIX_GRAY            ((unsigned int) (((unsigned int)1) << COLOR_GRAY)                 )
#define MIX_DARK_GRAY       ((unsigned int) (((unsigned int)1) << COLOR_DARK_GRAY)            )
#define MIX_LIGHT_RED       ((unsigned int) (((unsigned int)1) << COLOR_LIGHT_RED)            )
#define MIX_LIGHT_GREEN     ((unsigned int) (((unsigned int)1) << COLOR_LIGHT_GREEN)          )
#define MIX_YELLOW          ((unsigned int) (((unsigned int)1) << COLOR_YELLOW)               )
#define MIX_LIGHT_BLUE      ((unsigned int) (((unsigned int)1) << COLOR_LIGHT_BLUE)           )
#define MIX_LIGHT_MAGENTA   ((unsigned int) (((unsigned int)1) << COLOR_LIGHT_MAGENTA)        )
#define MIX_LIGHT_CYAN      ((unsigned int) (((unsigned int)1) << COLOR_LIGHT_CYAN)           )
#define MIX_WHITE           ((unsigned int) (((unsigned int)1) << PRN_COLOR_WHITE)            )

/*********************************************************************
*   PRN-Treiber: DRUCKERPARAMETER 
*********************************************************************/

#define PRN_ID_MODE           0
#define PRN_ID_FONT           1
#define PRN_ID_COLOR          2
#define PRN_ID_MAX_COLOR      3
#define PRN_ID_PAGELEN        4
#define PRN_ID_MARGIN         5
#define PRN_ID_LANGUAGE       6
#define PRN_ID_BITMAP_CAP     7

/*********************************************************************
*   PRN-Treiber: SCHRIFTARTEN
*********************************************************************/

#define PRN_FONT_NARROW       0
#define PRN_FONT_WIDE         1

/*********************************************************************
*   PRN-Treiber: PROGRAMMIER-OFFSETS
*********************************************************************/

#define PRN_PRG_RESET         0
#define PRN_PRG_CR            1
#define PRN_PRG_TEXT_LF       2
#define PRN_PRG_GRAPH_LF      3
#define PRN_PRG_FF            4
#define PRN_PRG_NORM_FONT     5
#define PRN_PRG_NARROW_FONT   6
#define PRN_PRG_DEF_DWNLD     7
#define PRN_PRG_ACTIV_DWNLD   8
#define PRN_PRG_DEACTIV_DWNLD 9
#define PRN_PRG_CODETAB       10
#define PRN_PRG_BLACK         11
#define PRN_PRG_RED           12
#define PRN_PRG_GREEN         13
#define PRN_PRG_BROWN         14
#define PRN_PRG_BLUE          15
#define PRN_PRG_MAGENTA       16
#define PRN_PRG_CYAN          17
#define PRN_PRG_GRAY          18
#define PRN_PRG_DARK_GRAY     19
#define PRN_PRG_LIGHT_RED     20
#define PRN_PRG_LIGHT_GREEN   21
#define PRN_PRG_YELLOW        22
#define PRN_PRG_LIGHT_BLUE    23
#define PRN_PRG_LIGHT_MAGENTA 24
#define PRN_PRG_LIGHT_CYAN    25
#define PRN_PRG_WHITE         26
#define PRN_PRG_COLTAB_LINE   27
#define PRN_PRG_COLTAB_TDUMP  28
#define PRN_PRG_COLTAB_GDUMP  29
#define PRN_PRG_GRAPH_MODE    30
#define PRN_PRG_GRAPH_ON      31
#define PRN_PRG_GRAPH_OFF     32
#define PRN_PRG_GRAPH_START   33
#define PRN_PRG_LANGUAGE_TAB  34

#define PRN_PRGID_XSTR        '\x01'   /* Stringterminierung 'xff' */
#define PRN_PRGID_LSTR        '\x02'   /* Stringlaenge angegeben (16 Bit) */
#define PRN_PRGID_FUNC        '\x03'   /* Funktionszeiger angegeben */

/*********************************************************************
*  PRN-Treiber: KONTROLLCODES
*********************************************************************/

#define PRN_CTRL_                   /* ... */

/*********************************************************************
*   PRN-Treiber: FEHLERCODES
*********************************************************************/

#define PRN_ERR_BAD_MODE        1
#define PRN_ERR_COMMUNICATION   2
#define PRN_ERR_USER            3

#endif /* _devprn_ */
