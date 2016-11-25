#define TEST_NEWLOOK
/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DEVCRT.H
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
*     VERSION:    4.0                       DATUM:   18.03.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     18.03.92 -SF-    Portierung des IQT-350 auf IQT-450
*                      - CRT_INIT_BLOCK reduziert (unnoetiges entfernt)
*                      - CRT_PARAM_BLOCK: 'FontName' entfernt
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     01.06.92 -SF-    CRT_GRAPH_RECT_ABS und CRT_GRAPH_LINE_ABS definiert
*     11.06.92 -SF-    CRT_PARAM_BLOCK um 'Prio' erweitert
*     01.10.92 -SF-    CRT_CTRL_STRT_GRFPRN und CRT_CTRL_STOP_GRFPRN neu
*                      CRT_BITMAP: 'FileName' statt 'bitmap'
*     05.10.92 -SF-    CRT_BITMAP_FILENAME und CRT_BITMAP_DUMP definiert
*     08.10.92 -SF-    Fehlercodes nach <errcode.h> verlagert
*     13.10.92 -SF-    CRT_CTRL_BKGND_ON / OFF gibts nicht mehr
*     01.02.93 -MBa-   CRT_CTRL_HARDCOPY eingefuehrt
*     07.03.00 -TSchw- FONT_SYSTEM eingefuehrt, mit SYSPRN markiert.
*                      Damit kann ein ein betriebssystemspezifischer Font
*                      geladen werden zur Anzeige von Strings vom System.
*     30.07.01 -TSchw- CRT_ID_TEMP_FONT und CRT_ID_TEMP_FONT definiert,
*                      um für ein Fenster temporär einen anderen Font
*                      als den beim Open eingestellten wählen zu können.
*                      Die Positionierung basiert aber immer auf dem vor-
*                      eingestellten Fensterfont.
*     30.08.01 -TSchw- In CRT_BITMAP das Element Mode eingefügt, um Bitmaps
*                      auch transparent anzeigen zu können. Neue Id
*                      CRT_ID_TRANSPARENT_MODE angelegt, um auch Texte
*                      transparent anzeigen zu können.
*
*  BEMERKUNGEN:
*
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     CrtInit - Bildschirmtreiber einmalig initialisieren
*     CrtOpen - Handle fuer ein Fenster ermitteln
*     CrtClose - Handle fuer ein Fenster wieder freigeben
*     CrtGetParam - Fenster- und Systemparameter ermitteln
*     CrtSetParam - Fensterparameter einstellen
*     CrtRead - Fenster auslesen
*     CrtWrite - String in einem Fenster ausgeben
*     CrtControl - spezielle Ausgabesteuerungen
*     CrtExamine - Dummy-Funktion
*
*  DATENTYPEN:
*     CRT_INIT_BLOCK - Bei CrtInit
*     CRT_PARAM_BLOCK - Bei CrtOpen
*     CRT_BITMAP
*     CRT_WINDOW_LIST
*
*.EH.***********************************************************************/


#ifndef _devcrt
#define _devcrt

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
/*.EI.***********************************************************************/

/*********************************************************************
X  CRT-Treiber: DATENTYPEN
*********************************************************************/
 typedef struct {
   IQT_HANDLE Parent;
   PARAMETER State;
   PARAMETER Mode;
   PARAMETER Origin;
   PARAMETER Size;
   PARAMETER DefColor;
   PARAMETER Font;
   BYTE Prio;
} CRT_PARAM_BLOCK;

 typedef struct {
   UWORD CrtTasks;
   BYTE cardtype;
   BYTE monitortype;
   UWORD sizex;
   UWORD sizey;
   UWORD colors;
} CRT_INIT_BLOCK;

 typedef struct {
   int Type;
   int SizeX;
   int SizeY;
   char* FileName;
   int Mode;         /* BITMAP_OPAQUE oder BITMAP_TRANSPARENT */
} CRT_BITMAP;

 typedef struct {
   int HndCount;
   IQT_HANDLE* HndList;
} CRT_WINDOW_LIST;

/*********************************************************************
X  CRT-Treiber: FENSTERMODI UND FENSTERSTATI
*********************************************************************/
#define CRT_ST_INACTIVE 0L          /* STATI */
#define CRT_ST_ACTIVE   1L
#define CRT_ST_BKGND    2L

#define CRT_MD_TEXT     0
#define CRT_MD_GRAPHIC  0x01L       /* MODI */
#define CRT_MD_DYNAMIC  0
#define CRT_MD_STATIC   0x02L
#define CRT_MD_NOSCROLL 0
#define CRT_MD_SCROLL   0x04L
#define CRT_MD_NORMAL   0
#define CRT_MD_PROCESS  0x08L
#define CRT_MD_TWIN     0x10L
#define CRT_MD_BRAND    0x20L
#define CRT_MD_GTEXT    0x40L

#define CRT_RMD_NORMAL  0L          /* Lesemodi 09.05.90 *TE*/
#define CRT_RMD_COLTEXT 1L
#define CRT_RMD_BITMAP  2L

#define CRT_BA_USR      0L
#define CRT_BA_CHR      1L          /* Koordinatentypen */
#define CRT_BA_PIX      2L
#define CRT_BA_REL      3L
#define REL_MAX      10000          /* Konstante fuer 100% */

#define CRT_APPEND              0x00
#define CRT_ADDRESS             0x01

#define CRT_OPAQUE         0     /* Bitmap Modi */
#define CRT_TRANSPARENT    1

/*********************************************************************
X  CRT-Treiber: ZUGRIFFSMACROS FUER DIE FENSTERPARAMETER
*********************************************************************/
#define CRT_GET_TYP( ul ) ( (BYTE)(ul) & 0x03 )
#define CRT_GET_Y( ul ) (((int)((ul) >> 17) & 0x7FFF) - 0x4000)
#define CRT_GET_X( ul ) (((int)((ul) >> 2) & 0x7FFF) - 0x4000)

#define CRT_MAKE_TYP( t,x,y ) (((ULONG)((int)(y)+0x4000) << 17) | \
                           ((ULONG)((int)(x)+0x4000) << 2) & 0x0001FFFCL | (t))

#define CRT_MAKE_PIX( x,y ) CRT_MAKE_TYP( CRT_BA_PIX,(x),(y) )
#define CRT_MAKE_CHR( x,y ) CRT_MAKE_TYP( CRT_BA_CHR,(x),(y) )
#define CRT_MAKE_REL( x,y ) CRT_MAKE_TYP( CRT_BA_REL,(x),(y) )
#define CRT_MAKE_USR( x,y ) CRT_MAKE_TYP( CRT_BA_USR,(x),(y) )

#define CRT_GET_START( scale ) CRT_GET_X( scale )
#define CRT_GET_END( scale ) CRT_GET_Y( scale )
#define CRT_MAKE_SCALE( start,end ) CRT_MAKE_USR( start , end )

#define CRT_GET_BKGND_COLOR( ul ) ((BYTE) ((ul) >> 16))
#define CRT_GET_ATTR( ul ) ((BYTE) ((ul) >> 8))
#define CRT_GET_TEXT_COLOR( ul ) ((BYTE) (ul))
#define CRT_MAKE_COLOR( tx,bk,at ) (((ULONG)(bk) << 16) | \
                                    ((UWORD)(at) << 8 ) | (tx))


/*********************************************************************
X  CRT-Treiber: ATTRIBUTE
*********************************************************************/
#define ATTR_NORMAL   0x00
#define ATTR_DEFAULT  0x01
#define ATTR_INVERS   0x02
#define ATTR_BLINK    0x04
#define ATTR_TRANSP   0x08
#define ATTR_CHGCOL   0x10
#define ATTR_FILLED   0x20
#define ATTR_FEED     0x40
#define ATTR_NOCHANGE 0x80

/*********************************************************************
X  CRT-Treiber: FARBEN
*********************************************************************/
#ifndef COLOR_BLACK
#define COLOR_BLACK          0
#define COLOR_RED            1
#define COLOR_GREEN          2
#define COLOR_BROWN          3
#define COLOR_BLUE           4
#define COLOR_MAGENTA        5
#define COLOR_CYAN           6
#define COLOR_GRAY           7
#define COLOR_DARK_GRAY      8
#define COLOR_LIGHT_RED      9
#define COLOR_LIGHT_GREEN   10
#define COLOR_YELLOW        11
#define COLOR_LIGHT_BLUE    12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_LIGHT_CYAN    14
#endif
#define COLOR_WHITE         15
#define COLOR_DEFAULT       16
#define COLOR_NOCHANGE      17

/*********************************************************************
X  CRT-Treiber: FENSTERPARAMETER
*********************************************************************/
#define CRT_ID_PARENT         0
#define CRT_ID_MODE           1
#define CRT_ID_STATE          2
#define CRT_ID_ORIGIN         3
#define CRT_ID_SIZE           4
#define CRT_ID_CHAR_SIZE      5
#define CRT_ID_CURSOR         6
#define CRT_ID_BLOCK          7
#define CRT_ID_DEFAULT_COLOR  8
#define CRT_ID_CURRENT_COLOR  9
#define CRT_ID_GRAPHCMD      10
#define CRT_ID_MAX_ATTR      11
#define CRT_ID_SCREEN_SIZE   12
#define CRT_ID_MAX_COLOR     13
#define CRT_ID_FONT          14
#define CRT_ID_LANGUAGE      15
#define CRT_ID_TEXTURE       16
#define CRT_ID_USR_X         17
#define CRT_ID_USR_Y         18
#define CRT_ID_READ_MODE     19  /*TE*/
#define CRT_ID_REAL_MODE     20  /*TE*/
#define CRT_ID_ABS_ORIGIN    21  /*TE*/
#define CRT_ID_OBJECT_NUM    22
#define CRT_ID_REL_ORIGIN    23
#define CRT_ID_VIEWPORT_NUM  24
#define CRT_ID_LANGUAGE_FONT 25
#define CRT_ID_SYSTEM_TYPE   26
#define CRT_ID_SYSTEM_ROWS   27
#define CRT_ID_SYSTEM_COLS   28
#define CRT_ID_SYSTEM_COLORS 29
#define CRT_ID_SYSTEM_PAGES  30
#define CRT_ID_INC_BRIGHT    31 /* MBa */
#define CRT_ID_DEC_BRIGHT    32 /* MBa */ 
#define CRT_ID_INC_CONTRAST  33 /* MBa */ 
#define CRT_ID_DEC_CONTRAST  34 /* MBa */ 
#define CRT_ID_WRITE_MODE    35 /* PR */
#define CRT_ID_CURSOR_STATE  36 /* PR */
#ifdef TEST_NEWLOOK
#define CRT_ID_CURSOR_PIX    37 /* TSchw */
#define CRT_ID_SIZE_PIX      38 /* TSchw */
#endif
#define CRT_ID_GET_HW_COLOR  39 /* TSchw, SYSPRN */
#define CRT_ID_TEMP_FONT     40 /* TSchw */
#define CRT_ID_TRANSPARENT_MODE  41 /* TSchw */

/*********************************************************************
X  CRT-Treiber: ZEICHENSAETZE
*********************************************************************/
#define CRT_FONT_STANDARD    -1     /* Der beim CrtOpen definierte Font */
#define CRT_FONT_NARROW       0     /* 18 x  8 */
#define CRT_FONT_WIDE         1     /* 18 x 12 */
#define CRT_FONT_HALF_NARROW  2     /*  9 x  4 */
#define CRT_FONT_HALF_WIDE    3     /*  9 x  6 */
#define CRT_FONT_SYSTEM       4     /* SYSPRN: Betriebssystem-Standardfont */

/*********************************************************************
X  CRT-Treiber: GRAPHISCHE OBJEKTE
*********************************************************************/
#define CRT_GRAPH_POINT     0
#define CRT_GRAPH_LINE      1
#define CRT_GRAPH_RECT      2
#define CRT_GRAPH_BITMAP    3
#define CRT_GRAPH_TEXT      4
#define CRT_GRAPH_CROSS     5
#define CRT_GRAPH_POLYLINE  6
#define CRT_GRAPH_POLYGON   7
#define CRT_GRAPH_ELLIPSE   8
#define CRT_GRAPH_MACRO     9
#define CRT_GRAPH_RECT_ABS 10
#define CRT_GRAPH_LINE_ABS 11

/*********************************************************************
X  CRT-Treiber: MACRO-BEFEHLE
*********************************************************************/
#define CRT_MAC_NOP        0x0000
#define CRT_MAC_END        0x0100

#define CRT_MAC_JUMP       0x0200
#define CRT_MAC_COND       0x0300
#define CRT_MAC_CALL       0x0400
#define CRT_MAC_RETURN     0x0500
#define CRT_MAC_USER       0x0600

#define CRT_MAC_ABS_MOVE   0x0700
#define CRT_MAC_REL_MOVE   0x0800
#define CRT_MAC_PARAM      0x0900
#define CRT_MAC_PUSH       0x0a00
#define CRT_MAC_POP        0x0b00

#define CRT_MAC_POINT      0x0c00
#define CRT_MAC_LINE       0x0d00
#define CRT_MAC_RECT       0x0e00
#define CRT_MAC_BITMAP     0x0f00
#define CRT_MAC_TEXT       0x1000
#define CRT_MAC_CROSS      0x1100
#define CRT_MAC_POLYLINE   0x1200
#define CRT_MAC_POLYGON    0x1300
#define CRT_MAC_ELLIPSE    0x1400


/*********************************************************************
X  CRT-Treiber: IQT_BITMAP-ATTRIBUTE
*********************************************************************/
#define CRT_BITMAP_FILENAME     0   /* Dateiname enthaelt kodiertes Bild */
#define CRT_BITMAP_DUMP         1   /* Dateiname enthaelt Dump */


/*********************************************************************
X  CRT-Treiber: KONTROLLCODES
*********************************************************************/
#define CRT_CTRL_CLEAR      3       /* Fenster loeschen */
#define CRT_CTRL_FEED       4       /* Zeilenvorschub */
#define CRT_CTRL_WINLIST    5       /* Handleliste aufbereiten */
#define CRT_CTRL_VIDEO_ON   6       /* Bildgenerierung ein */
#define CRT_CTRL_VIDEO_OFF  7       /* Bildgenerierung aus */
#define CRT_CTRL_STRT_GRFPRN  8     /* Start des Grafikdrucks */
#define CRT_CTRL_STOP_GRFPRN  9     /* Ende des Grafikdrucks */
#define CRT_CTRL_HARDCOPY    10     /* Bildschirm Hardcopy   */

#define CRT_CTRL_PGR_SCALE  100     /* Scale Y */
#define CRT_CTRL_PGR_ZOOM   101     /* Zoom */
#define CRT_CTRL_PGR_DEFC   102     /* Define cursor */
#define CRT_CTRL_PGR_POSC   103     /* Position cursor */
#define CRT_CTRL_PGR_OPEN   104     /* Open coordinate system */
#define CRT_CTRL_PGR_CLOSE  105     /* Close coordinate system */
#define CRT_CTRL_PGR_DEFM   106     /* Define marker */
#define CRT_CTRL_PGR_CLRM   107     /* Clear marker */
#define CRT_CTRL_PGR_PRINT  108     /* Print curve */
#define CRT_CTRL_PGR_CLEAR  109     /* Clear curve */

/*********************************************************************
X  CRT-Treiber: FEHLERCODES
*********************************************************************/
/* Diese liegen nun in <errcode.h> */

/*********************************************************************
X  CRT-Treiber: DIAGNOSEFEHLERMELDUNGEN
*********************************************************************/

/* MACRO UM DIAGNOSE-MELDUNGEN ZU SICHERN
**
** UEBERNIMMT: (BYTE) err - ein DEVCRT-typischer Fehlercode
**             (BYTE) hnd - das Handle des betroffenen Fensters
**             (UWORD) num - spezifischer Zusatzparameter
**
** ... und so werden die drei Informationen im ULONG-Parameter kodiert:
**             +-----------+-----------+----------+
**             |31  err  24|23  hnd  16|15  num  0|
**             +-----------+-----------+----------+
*/
#define DIAGNOSE( err,hnd,num ) \
   DiagPutMsg( DM_DEVCRT, (((ULONG)(err))<<24) |    \
                           (((ULONG)((hnd)&0xff))<<16) |  \
                           ((ULONG)((num)&0xffff)) )

#define DM_CRT_INIT           0
#define DM_CRT_OPEN           1
#define DM_CRT_CLOSE          2
#define DM_CRT_READ           3
#define DM_CRT_WRITE          4
#define DM_CRT_CONTROL        5
#define DM_CRT_EXAMINE        6
#define DM_CRT_SETPARAM       7
#define DM_CRT_GETPARAM       8

#define DM_CRT_FONTINIT       0x10
#define DM_CRT_WCBUNLINK      0x11
#define DM_CRT_OUTGRAPHIC     0x12
#define DM_CRT_POSITIONRANGE  0x13
#define DM_CRT_SETSIZE        0x14
#define DM_CRT_SETORIGIN      0x15
#define DM_CRT_VSDDCREATE     0x16
#define DM_CRT_VSDDDELETE     0x17
#define DM_CRT_STATECREATE    0x18
#define DM_CRT_SETSTATE       0x19
#define DM_CRT_SWITCHBA       0x1A
#define DM_CRT_MONOCHROM      0x1B

/*********************************************************************
X  CRT-Treiber: Karten- und Monitortyp
*********************************************************************/

#define CRT_MONO        1
#define LCD_MONO        2
#define CRT_COLOUR      3
#define LCD_COLOUR      4

#define VGA_STANDARD    1

#define MONOCHROME(mt)  ((mt) == CRT_MONO || (mt) == LCD_MONO)
#define COLOURED(mt)    ((mt) == CRT_COLOUR || (mt) == LCD_COLOUR)

#endif  /* ifndef _devcrt */

