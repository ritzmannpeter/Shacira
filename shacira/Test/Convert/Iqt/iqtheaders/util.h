#define TEST_NEWLOOK
/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     UTIL.H   - UTIL-Funktionen (mit oder ohne DLL)
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
*     VERSION:    4.0                       DATUM:   09.04.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     09.04.92 -SF-    Implementierung
*     07.05.92 -TS-    Util_GetActDateTimeText
*                      Util_GetDateTimeText
*                      Util_GetActDateTime 
*                      Util_PrintCyclePages
*                      Util_CyclePrintMode
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     25.05.92 -SF-    Grafik-Funktionen aufgenommen
*     15.07.92 -SF-    Util_PrintOpen aufgenommen
*     18.08.92 -SF-    Util_GetActDateTime hat als Funktionswert 
*                      'PARAMETER' statt 'int'
*     04.10.96 -PR-     Aggregatnummer in die Nachrichtenkodierung fuer
*                      Drucker- und Bildschirmaufbautask aufgenommen.
*                      Bei der Druckertask musste hierfuer der Parameter
*                      "Textindex fuer Hilfetext" von 16-Bit auf 12-Bit
*                      Breite zurueckgenommen werden. Damit ist der groesste
*                      kodierbare Index nun 4095, was allerdings reichen sollte,
*                      da der maximale Zeilenindex in den Hilfetexttabellen so
*                      in etwa bei 1000 liegt.
*     25.02.97 -HAns-  Makro GET_PRINT_WINHELP Verundung mit 12-Bits versehen.
*     29.09.97 -TSchw- Util_GrfChangeDefColor und Util_GrfSetDefScreenColor
*                      deklariert;
*
*
*     05.11.97 -PR-    Nachrichtenkennung ID_PRINT_JOB fuer allgemeine
*                      Druckauftraege eingefuehrt.
*     13.03.98 -TSchw- Util_GrfAggWindow eingebaut.
*     09.11.98 -TSchw- Util_SetBGTaskFlag eingebaut.
*     06.03.00 -TSchw- Util_GrfSysPrinterWindow, SelectSystPrinterUser2 
*                      eingebaut. 
*     13.03.00 -TSchw- ID_PRINT_BITMAP_FILE eingebaut (SYSPRN)
*     02.05.00 -TSchw- GET_PRINT_PRINTER_TYPE erstellt und SET_PRINT_FLAGS
*                      erweitert, um das neue PrintToDisk-Flag zu uebergeben.
*     30.08.00 -TSchw- Einige Änderungen eingefügt für das ausdrucken
*                      gescrollter Seiten, markiert mit PRNSCROLL.
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  PROTOTYPEN:
*     Util_SendToTskBuild - Meldung an Seitenneuaufbau senden
*     Util_SendToTskUpdat - Meldung an Seitenaktualisierung senden
*     Util_SendToTskInjReg - Meldung an Task 'InjReg' senden
*     Util_SendToTskPrint - Meldung an Druckertask senden
*     Util_ReleaseMsg - Meldung beantworten und freigeben
*
*     Util_GetActDateTimeText - Datum/Uhrzeit holen (String)
*     Util_GetDateTimeText - Datum/Uhrzeit in String wandeln
*     Util_GetActDateTime - Datum/Uhrzeit holen (ULONG)
*
*     Util_PrintCyclePages - Zykl. Seiten drucken
*     Util_CyclePrintMode - Pruefung zykl. Drucken erlaubt
*     Util_PrintOpen - Druckerhandle bereitstellen
*
*     Util_GrfNewVarHnd - Neues Grafikhandle erfragen
*     Util_GrfSearchVarHnd - Grafikhandle fuer ein Element suchen
*     Util_GrfOpenWindow - Grafikfenster oeffnen
*     Util_GrfExpInput - Eingabe in einem Zusatzfenster
*     Util_GrfSecWindow - Sicherheitsabfrage durchfuehren
*     Util_GrfAggWindow - Aggregatnummer abfragen
*     Util_GrfSysPrnWindow - Systemdrucker auswaehlen und initialisieren
*     Util_SysPrnImplemented - Systemdruckerfunktione existieren ja/nein
*     Util_GrfInfoWindow - Informationsfenster anzeigen
*     Util_GrfInfoLine - Vereinfachte Version von Util_GrfInfoWindow
*     Util_GrfOutLine - Linie zeichnen
*     Util_GrfOutText - Text zeichnen
*     Util_GrfOutRect - Rechteck zeichnen
*     Util_GrfOutCircle - Kreis zeichnen
*     Util_GrfOutRaster - Raster zeichnen
*     Util_GrfOutCoord - Koordinatenkreuz zeichnen
*     Util_GrfSetCol - Farbe setzen
*     Util_GrfSetBackCol - Hintergrundfarbe setzen
*     Util_GrfTxtPosX - X-Position zum Zentrieren von Texten berechnen
*     Util_GrfTxtPosY - Y-Position zum Zentrieren von Texten berechnen
*
*  DATENTYPEN:
*     Keine
*
*.EH.***********************************************************************/

#ifndef _util
#define _util

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
#include <iqttsk.h>
#include <dstruct.h>
#include <ifk.h>
#include <mempool.h>
#include <sunichar.h>
/*.EI.***********************************************************************/

/*---------------------------------------------------------------------------
X Allgemeine Konstanten
---------------------------------------------------------------------------*/
/* Auswahlparameter fuer Get[Act]{Time|Date} Funktionen */
/* ---------------------------------------------------- */
#define Util_DATE               1 
#define Util_TIME               2

/* Meldungsparameter fuer 'InjReg' */
/* ------------------------------- */
#define ID_FAST                  0   /* InjReg von Fastreg gestartet */

/* Meldungsparameter fuer 'TskBuild' */
/* --------------------------------- */
#define PAGE_NR                  0   /* Seiten-Nummer wird uebergeben */
#define PAGE_INDEX               1   /* Seiten-Index wird uebergeben */
#define SHOW_ALL                 0   /* alles anzeigen */
#define SHOW_HEADER_SOFTKEY      1   /* nur Header und Softkeys anzeigen */
#define SET_ALL_BUILD_INFOS(W,P,S,A,NI) (((W)|((P)<<1)|((S)<<2)|((NI)<<3)|(A<<4))&0x000000ff) /*PRNSCROLL*/
#define GET_BUILD_WAIT(B)     ((B)&0x00000001)
#define GET_BUILD_PAGE(B)     (((B)&0x00000002)>>1)
#define GET_BUILD_SHOW(B)     (((B)&0x00000004)>>2)
#define GET_BUILD_AGGREGAT(A) (((A)&0x000000f0)>>4)
#define GET_BUILD_NOINIT(B)   (((B)&0x00000008)>>3) /*PRNSCROLL*/

/* Meldungsparameter fuer 'PrintPage' */
/* ---------------------------------- */
/* Macros zum Setzen/Lesen der Seiten fuer die Task PrintPage (Long-Param.) */
/* AZYYYXXX: XXX=Seiten-Nr. / YYY=Window-Nr. oder Textindex des Hilfetextes */
/* Z = Bank-Nr. des Hilfetextes / A = Aggregatnummer */
#define  SET_PRINT_PAGE(p,a,w,b)\
        (long)((long)(p)|(long)(w)<<12|(long)(b)<<24|(long)a<<28)
#define  GET_PRINT_PAGE(l)     (UWORD)((l) & 0x00000fff)
#define  GET_PRINT_WINHELP(l)  (UWORD)((l)>>12 & 0x00000fff)
#define  GET_PRINT_BANK(l)     (UWORD)((l)>>24 & 0x0000000f)
#define  GET_PRINT_AGGREGAT(l) (UWORD)((l)>>28 & 0x0000000f)

/* Macros zum Setzen/Lesen der Flags fuer die Task PrintPage (Word-Parameter):
   Bit  0:  0 = Vordergrund-Seite
            1 = Hintergrund-Seite
   Bit  1:  0 = ASCII-Seite  (nur Texte ausgeben)
            1 = Grafik-Seite (im Grafikmodus ausgeben)
   Bit  2:  0 = Statuszeile nicht ausgeben (blau-weisser Balken)
            1 = Statuszeile ausgeben
   Bit  3:  0 = Softkeys nicht ausgeben
            1 = Softkeys ausgeben
   Bit 4,5: 00 = Keine Hilfetexte
            01 = Hilfetext im kleinen Fenster
            10 = Hilfetext im grossen Fenster
   Bit  6:  0 = Scrollbare Seiten neu initialisieren      PRNSCROLL
            1 = Scrollbare Seiten nicht neu initialiseren PRNSCROLL
*/

#define PRINT_HELP_NONE    0x0000         /* Keine Hilfeseite drucken */
#define PRINT_HELP_SMALL   0x0010         /* Kleine Hilfeseite drucken */
#define PRINT_HELP_LARGE   0x0020         /* Grosse Hilfeseite drucken */

#define  SET_PRINT_FLAGS(bg,gr,sl,sk,hp,pt,ni)  \
         (UWORD)((bg) | (gr)<<1 | (sl)<<2 | (sk)<<3 | hp | ((pt)&0x000f)<<8 | (ni)<<6) /*PRNSCROLL*/
#define  GET_PRINT_FGBG_FLAG(f)        (UWORD)((f)    & 0x0001)
#define  GET_PRINT_GRAPHIC_FLAG(f)     (UWORD)((f)>>1 & 0x0001)
#define  GET_PRINT_STATLINE_FLAG(f)    (UWORD)((f)>>2 & 0x0001)
#define  GET_PRINT_SOFTKEY_FLAG(f)     (UWORD)((f)>>3 & 0x0001)
#define  GET_PRINT_HELP_FLAG(f)        (UWORD)((f) & 0x0030)
#define  GET_PRINT_PRINTER_TYPE(f)     (UWORD)((f)>>8 & 0x000f)
#define  GET_PRINT_NOINIT_FLAG(f)      (UWORD)((f)>>6 & 0x0001) /*PRNSCROLL*/

#define  ID_PRINT_PAGE        1     /* Seite drucken */
#define  ID_PRINT_CLEAR       2     /* alle Druckauftraege loeschen */
#define  ID_PRINT_JOB         3     /* Beliebigen Druckauftrag ausfuehren */
#define  ID_PRINT_BITMAP_FILE 4     /* Eine Seite in Bitmapfile ausgeben  */

#define  IDFLAG_NOINIT_PAGE   0x80  /* PRNSCROLL: Flag zum Ver-Odern mit  */
                                    /* dem id-Parameter der Util_SendToTsx*/
                                    /* Funktionen, sowie von Byte-Params  */
                                    /* anderer Funktionen. Beim Seitenneu-*/
                                    /* aufbau sollen gescrollte Seiten    */
                                    /* nicht an den Anfang zurückge-      */
                                    /* blättert werden.                   */
#define  GET_ID_NOINIT_FLAG(f)         (UWORD)(((f)&0x80)>>7)  /*PRNSCROLL*/
#define  CLEAR_ID_FLAGS(f)             ((f) & 0x7f)            /*PRNSCROLL*/

/* Konstanten fuer die Funktion Util_GrfExpInput */
#define GRF_INP_NONE    0        /* keine Eingabe */
#define GRF_INP_TEXT    1        /* Texteingabe */
#define GRF_INP_VALUE   2        /* Eingabe von Ziffern */
#define GRF_INP_SEC     3        /* Sicherheitsabfrage (1=yes, 0=no) */
#define GRF_INP_HIDDEN  8        /* Text verborgen (zum Ver-Odern) */

/* Konstanten fuer die Funktionen Util_GrfTxtPosX und Util_GrfTxtPosY */
#define  POS_LEFT    0
#define  POS_CENTRE  1
#define  POS_RIGHT   2
#define  POS_TOP     3
#define  POS_DOWN    4

typedef struct {
   IQT_HANDLE   Parent;     /* Vaterfenster */
   UNICHAR  *Text1;     /* anzuzeigender Text */
   UNICHAR  *Text2;     /* anzuzeigender Text */
   BYTE     StartLine;  /* Anfangszeile des Fensters */
   BYTE     Lines;      /* Anzahl Zeilen */
   BYTE     TextLine;   /* Zeile des ersten Textes */
   BYTE     Columns;    /* Breite des Fensters oder 0 */
   PARAMETER   Color;   /* Farbe */
   } INFO_WINDOW_TYPE;

/*---------------------------------------------------------------------------
X Verwendung von 'normalen' Funktionen
---------------------------------------------------------------------------*/
GLOBAL int Util_SendToTskBuild  (BYTE id, UWORD page, UWORD agg_no,
                                 BYTE page_info, BYTE show_info, BYTE wait);
GLOBAL int Util_SendToTskUpdat  (BYTE id);
GLOBAL int Util_SendToTskInjReg (BYTE id);
GLOBAL int Util_SendToTskPrint  (BYTE id, UWORD page_nr, UWORD agg_no, UWORD window_nr,
                                 UWORD help_flag, void* help_ptr);
GLOBAL void Util_ReleaseMsg     (MESSAGE* msg_ptr);

GLOBAL int Util_GetActDateTimeText    ( int choice, char    *txt_ptr, BYTE info );
GLOBAL int Util_GetActDateTimeText_Uni( int choice, UNICHAR *txt_ptr, BYTE info );
GLOBAL int Util_GetDateTimeText       ( int choice, char* txt_ptr, 
                                        PARAMETER param, BYTE info);
GLOBAL int Util_GetDateTimeText_Uni   ( int choice, UNICHAR* txt_ptr, 
                                        PARAMETER param, BYTE info );
GLOBAL PARAMETER Util_GetActDateTime  ( int choice );

GLOBAL void Util_PrintCyclePages(void);
GLOBAL BOOL Util_CyclePrintMode(void);
GLOBAL IQT_HANDLE Util_PrintOpen(IQT_HANDLE* hnd_tab, int hnd_cnt);

GLOBAL IQT_HANDLE* Util_GrfNewVarHnd(BYTE screen, ELEMENT* el_ptr);
GLOBAL IQT_HANDLE* Util_GrfSearchVarHnd(BYTE screen, BYTE from, BYTE to,
                                         ELEMENT** el_ptr_ptr, BYTE count);
GLOBAL IQT_HANDLE Util_GrfOpenWindow(IQT_HANDLE parent, int font,
                                      POS* start_pos_ptr, POS* end_pos_ptr,
                                      BYTE line, COLOR color);
GLOBAL int Util_GrfExpInput(UWORD ctrl, char* buf_ptr, int inp_size,
                                 UNICHAR* head_txt1_ptr, UNICHAR* head_txt2_ptr,
                                 int col_size, int line);
GLOBAL BOOL Util_GrfSecWindow(BYTE txt_ind);
GLOBAL int far Util_GrfAggWindow( void );
GLOBAL int Util_GrfSysPrnWindow( void );
GLOBAL BOOL  Util_SysPrnImplemented( void );
GLOBAL int Util_GrfInfoWindow(INFO_WINDOW_TYPE* info_ptr, BOOL show,
                                   IQT_HANDLE *hnd_ptr);
GLOBAL int Util_GrfInfoLine(UWORD txt_ind);
GLOBAL void Util_GrfOutLine(IQT_HANDLE hnd, int x1, int y1, int x2, int y2);
GLOBAL void Util_GrfOutText    (IQT_HANDLE hnd, int x, int y, const char * txt_ptr);
GLOBAL void Util_GrfOutText_Uni(IQT_HANDLE hnd, int x, int y, UNICHAR    * txt_ptr);
GLOBAL void Util_GrfOutRect(IQT_HANDLE hnd, int x1, int y1, int x2, int y2);
GLOBAL void Util_GrfOutCircle(IQT_HANDLE hnd, int x, int y);
GLOBAL void Util_GrfOutRaster(IQT_HANDLE hnd, int x1, int x2, int y1, int y2,
                                   int x_count, int y_count, BYTE rast_info);
GLOBAL void Util_GrfOutCoord(IQT_HANDLE hnd, int x1, int y1, int x2, int y2);
GLOBAL void Util_GrfSetCol(IQT_HANDLE hnd, BYTE color);
GLOBAL void Util_GrfSetBackCol(IQT_HANDLE hnd);
GLOBAL void Util_GrfChangeDefColor(BYTE screen, COLOR col); /*@COLOR */
GLOBAL void Util_GrfSetDefScreenColor( BYTE screen );       /*@COLOR */
GLOBAL int Util_GrfTxtPosX    (IQT_HANDLE hnd, char   * txt_ptr, int x, BYTE info);
GLOBAL int Util_GrfTxtPosX_Uni(IQT_HANDLE hnd, UNICHAR* txt_ptr, int x, BYTE info);
GLOBAL int Util_GrfTxtPosY(IQT_HANDLE hnd, int y, BYTE info);
GLOBAL int Util_ActKey(void);
GLOBAL void Util_SetBGTaskFlag( int val );
#ifdef TEST_NEWLOOK
GLOBAL void Util_PixOutLine( IQT_HANDLE hnd, int x1, int y1, int x2, int y2 );
void Util_FramePaint (IQT_HANDLE hnd, int x0, int y0, int x1, int y1,
                      BOOL thick, BOOL sunken);
void Util_FrameClear (IQT_HANDLE hnd, int x0, int y0, int x1, int y1, /*TSCHW24082001 */
                      BOOL thick);                                    /*TSCHW24082001 */
void Util_FramePaintWindow (IQT_HANDLE hnd, BOOL thick, BOOL sunken);
#endif

/* Gaeste von scrnew.c: */
GLOBAL int GetNrOfSoftkeys(void);
GLOBAL int GetNrOfUsedSoftkeys(void);
GLOBAL int GetIndexOfKeyPrompt(void);

#endif /* _util */

