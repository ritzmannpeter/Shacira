#undef EL_NEAR_PTR
/****************************************************************************
*
*
*         DSTRUCT.H
*
*  HISTORY:
*     05.12.89    -SF-     Typ fuer Datum und Uhrzeit eingefuegt
*     22.12.89    -TSchw-  Helptext ueberall entfernt
*     06.02.90    -SF-     ELEMENT TEXT um DiskFlag erweitert
*     12.02.90    -SF-     DISK_WRITETAB_TYPE und AXISTAB_TYPE eingebaut
*     19.02.90    -SF-     Element-Typ fuer Sollwertgraphik eingebaut
*     01.03.90    -SF-     Element-Typ fuer Sollwertgraphik geaendert
*     22.03.90    -TSchw-  HostP in ERRTAB_TYPE eingefuehrt
*      5.06.90    -SF-     CLB_TYPE eingebaut (Registeristwerte + Format)
*      6.06.90    -SF-     Struktur SWG geaendert
*      4.07.90    -SF-     Softkeytext und SWG-Texte in Stattab gelegt
*     09.08.90    -TSchw-  K_ISCOSREG_TYPE und K_ISCOSBIT_TYPE eingefuehrt
*     17.08.90    -TSchw-  Format um fuehrende Nullen erweitert
*     24.09.90    -SF-     ISCOSREG_EP_TYPE entfernt
*     12.11.90    -SF-     Standard-Objekte und Elemente definiert
*                          Alle REGIND-Mîglichkeiten definiert
*     23.11.90    -SF-     TEXT-Element geaendert und Kommentare berichtigt
*                          Standard-Objekte und Elemente nach std_el.h
*     07.12.90    -TSchw-  In der Struktur PROCGRAPH die neuen Elemente
*                          SpeedCurve1/2 und WayCurve1/2 definiert
*     13.12.90    -UP-     Typen fuer Telegrammbeschreiber u. -task integriert
*     07.01.91    -SF-     BITARRAY-Element eingebaut
*     02.05.91    -SF-     DiskInfo von VAR_TEXT_TYPE statt BYTE jetzt UWORD,
*                          Text-Konstanten fuer Datentraegerspeicher entfernt,
*                          Typen des Datentragers jetzt in dsdisk.h.
*                          K_ISCOSBIT_TYPE um Eintrag RegType erweitert
*                          K_IQTREG_TYPE neu
*     06.05.91    -PR-     Wait und InitPollrate in Telegrammbeschreiber 
*                          eingefuehrt
*     12.06.91    -TSchw-  BEGIN_STOP_ERROR, END_STOP_ERROR eingefuehrt
*     18.07.91    -SF-     Struktur DSP_PAGE_INFO ist neu
*     22.07.91    -PR-     Register fÅr die Anzahl der Zonen in den Graphik-
*                          elementen CYLROCKET und CYLHIST eingefuehrt
*     24.07.91    -SF-     Version mit Maintal abgeglichen
*     31.07.91    -PR-     Sollwertgraphik SWG erweitert um Mode-Array
*     30.08.91    -SF-     ERRTAB_TYPE geaendert und Macro's
*                          ERR_HOST und ERR_NO_HOST definiert
*     06.09.91    -UP-     ELEMENT_PTR eingefuehrt (Offset ohne Segment)
*     12.09.91    -SF-     BEGIN/END_STOP_ERROR entfernt
*     30.09.91    -SF-     SWG: Konstanten STAGES und RAMPS von PR uebernommen
*     19.11.91    -PR-     Telegrammbeschreibungsstruktur geaendert
*     09.12.91    -SF-     MODE_PASSWORD eingebaut
*     18.05.92    -TSchw-  AXISTAB_TYPE um einen Eintrag erweitert
*     26.06.92    -TSchw-  In der Struktur BITARRAY das Element Col einge-
*                          fuegt, um die Kompatibilitaet mit den anderen
*                          Sollwertstrukturen zu wahren. Alle Sollwertstruk-
*                          turen muessen bis einschliesslich zum Element
*                          VarNr identisch sein, damit man mit einem einzigen
*                          Cast auf die Variablennummer zugreifen kann, z.B.
*                          bei Ausgabe der Hilfetexte.
*     30.09.92    -SF-     PLAUS_SET_PG_LN und PLAUS_GET_xx eingefuegt
*     23.97.93    -PR-     REGIST-Varianten BINARY, HEX und OCTAL eingefuehrt
*                          und spezielles Format dafuer definiert.
*     18.08.93    -PR-     REGIST-Variante ASCII eingefuehrt.
*     09.02.93    -PR-     Aggregatregister fuer CYLHIST und CYLROCHKET-
*                          Element eingefuehrt.
*     14.11.94    -MBa-    ERR_HOST verbessert                          
*     21.03.96    -MBa-    MAX_FUNCTION_UNITS von 3 auf 4 erhoeht.      
*     13.09.96    -PR-     Zusaetzlicher Elementtyp fuer Klickmodus:
*									KLICK_TYPE
*		28.11.96		-PR-		AXISTAB_TYPE umdefiniert.
*		12.02.97		-HAns-	AXISTAB_TYPE fuer den Eintrag check_reg_no umdefiniert.
*     04.03.97    -TSchw-  In der Struktur TIME_TYPE das Element YY als
*                          UWORD definiert anstelle von BYTE, um eine volle
*                          Jahreszahl halten zu koennen.
*		31.03.99    -TSchw-  In der Struktur MARKER die neuen Elemente
*									SkalDiv und SkalMult eingefuegt, um damit
*									Unterschiede in der Dimensionierung zweier Register
*									auszugleichen.
*		07.04.99    -TSchw-  In der Struktur PG_CLIP_BOARD das Register
*									ActCurves eingefuegt.
*     01.02.01    -HAns-   MAX_FUNCTION_UNITS von 4 auf 6 erhoeht.      
*     14.03.02 -HA-     ELID_DRVERR eingefuegt.
*     15.03.02 -HA-     ELID_BDE_ACTVAL, ELID_BDE_FAULTMSG, ELID_BDE_DOWNTIMES,
*                       ELID_BDE_REQVALCHG eingefuegt.
*     27.08.02 -HA-     typdef von PG_CURVE_VALUE_TYPE von unsigned int nach unsigned short int geaendert.
*                       Da ein sizeof-Problem von QNX/WNT/LINUX vorhanden ist.
*
****************************************************************************/

#ifndef _dstruct
#define _dstruct

#include <syntax.h>

/* ------------------------------------------------------------------------- *
 |  Globale Umdefinitionen                                                   |
 * ------------------------------------------------------------------------- */

#define far

/* ------------------------------------------------------------------------- *
 |  Indizes in Tabellen                                                      |
 * ------------------------------------------------------------------------- */

typedef int FUNC_INDEX;        /* Index in Adresstabelle fuer Funktionen */
typedef int PARAM_INDEX;       /* Index in Tabelle mit Funktionsparametern */
typedef int BITMAP_INDEX;      /* Index in Adresstabelle fuer Bitmaps */
typedef int TEXTVAR_INDEX;     /* Index in Adr.tab. fuer Textvar. im BBRAM */
typedef int TEXTIND_INDEX;     /* Index in Adresstabelle fuer ind. Texte */
typedef struct
   {
   BYTE  Bank;                 /* Banknummer der Festtexttabelle */
   UWORD  Index;                /* Index in die Festtexttabelle */
   } TEXT_INDEX;

/* ------------------------------------------------------------------------- *
 |  Farben                                                                   |
 * ------------------------------------------------------------------------- */

typedef BYTE COLOR;

/* Die folgenden vier Makros konnen zum Setzen bzw. Abfragen von Vorder-     */
/* bzw. Hintergrundfarben verwendet werden                                   */

#define GET_FOGND_COLOR(C)     ( (C) & 0x0f )
#define GET_BKGND_COLOR(C)     ( ((C)>>4) & 0x0f )
#define SET_FOGND_COLOR(C,FGC) (C) = (C) & 0xf0 | ((FGC) & 0x0f)
#define SET_BKGND_COLOR(C,BGC) (C) = (C) & 0x0f | (((BGC)<<4) & 0xf0)

/* Setzen von Vorder- und Hintergrundfarbe als Konstante                    */
#define SET_FGBG_COLOR(FGC,BGC)  ( ((FGC) & 0x0f) | (((BGC)<<4) & 0xf0) )

/* Die folgenden Farbkombinationen sind Standardfarben, die in der Daten-   */
/* struktur verwendet werden. (HEADLINE_COLOR: Ueberschrift und Softkeys)   */
#define HEADLINE_COLOR  SET_FGBG_COLOR(COLOR_WHITE,COLOR_DARK_GRAY)
#define TEXT_COLOR      SET_FGBG_COLOR(COLOR_GREEN,COLOR_BLACK)
#define SOLL_COLOR      SET_FGBG_COLOR(COLOR_GREEN,COLOR_BLACK)
#define IST_COLOR       SET_FGBG_COLOR(COLOR_LIGHT_GREEN,COLOR_BLACK)
#define SHOW_COLOR      SET_FGBG_COLOR(COLOR_YELLOW,COLOR_BLACK)
#define KLICK_COLOR     SET_FGBG_COLOR(COLOR_BLACK,COLOR_YELLOW)


/* ------------------------------------------------------------------------- *
 |  Format von Fliesskommazahlen                                             |
 * ------------------------------------------------------------------------- */

typedef BYTE FORMAT;

/* Die folgenden vier Makros konnen zum Setzen bzw. Abfragen von Breite und  */
/* Anzahl Nachkommastellen einer Fliesskommazahl verwendet werden. Zusaetz-  */
/* lich wird im Formatbyte codiert, ob die Zahl mit fuehrenden Nullen aus-   */
/* gegeben werden soll.                                                      */
/* Die Gesamtanzahl der Stellen ist auf 15, die Anzahl der Nachkommastellen  */
/* auf 7 begrenzt.                                                           */
/* Das Formatbyte ist wie folgt aufgebaut:                                   */
/*    7  6  5  4   3  2  1  0                                                */
/*    \___ ____/   V  \__ __/                                                */
/*        V        |     V                                                   */
/*        |        |     Anzahl Nachkommastellen                             */
/*        |        Codierung fuehrende Nullen: 1 = Ja, 0 = Nein              */
/*        Anzahl Stellen gesamt                                              */


#define GET_FORMAT_PRECISION(F)     ( (F) & 0x07 )
#define GET_FORMAT_WIDTH(F)         ( ((F)>>4) & 0x0f )
#define GET_FORMAT_LEADING_ZEROS(F) ( ((F)>>3) & 0x01 )
#define SET_FORMAT_PRECISION(F,P)   (F) = (F) & 0xf0 | ((P) & 0x0f)
#define SET_FORMAT_WIDTH(F,W)       (F) = (F) & 0x0f | (((W)<<4) & 0xf0)

/* Folgendes Makro kann wie eine Konstante benutzt werden zum Setzen von    */
/* Weite (Anzahl Ziffern gesammt, W) und Genauigkeit (Anzahl Nachkomma-     */
/* stellen, P). Es werden KEINE fuehrenden Nullen ausgegeben.               */
#define SET_FORMAT(W,P)   (((W) << 4) | (P))

/* Folgendes Makros leistet dasselbe wie das vorige, nur werden fuehrende    */
/* Nullen ausgegeben.                                                        */
#define SET_FORMAT_LEADING_ZEROS(W,P)   (((W) << 4) | (P) | 0x08)

/* Spezielles Format fuer die SPC-Variable, das sich wie folgt zusammensetzt:
   Gleiches Format wie der zugehoerige (zu ueberwachende) Istwert plus
   2 Nachkommastellen */
#define FORMAT_SPC            0x0f
#define SPC_KOMMA_ANZAHL         2  /* plus 2 Nachkommastellen */
#define SPC_KOMMA_FAKTOR      100L  /* ==> stets * 100 nehmen  */

/* Spezielles Format fuer die Variablen-Auswahl fuer die SPC, BDE und Trendgr.
   Das Format sieht wie folgt aus:
      Seite * 1000L + Zeile * 10 + Element in Zeile
   Die Ausgabe/Eingabe sieht wie folgt aus:
      ss.u.zze : (ss=Seite / u=Unterseite / zz=Zeile / e=Element in Zeile) */
#define FORMAT_VARNR          0x0e

/* Umdefinition des Formats fuer nicht-Standardbasen
   ACHTUNG: Das Format unterscheidet sich vom Format des IQT 450
 */

/* Das Formatbyte ist wie folgt aufgebaut:                                   */
/*    7  6  5  4   3  2  1  0                                                */
/*    \--/  |   \___________/                                                */
/*      |   |         |                                                      */
/*      |   |         |                                                      */
/*      |   |     Anzahl Stellen                                             */
/*      |   Codierung fuehrende Nullen Ja = 1, Nein = 0                      */
/*      Codierung Hexformat, stets 1: Die Bits 4 bis 7 werden beim Standard- */
/*      format fuer die Anzahl der Stellen insgesamt verwendet. Die Codierung*/
/*      des Hexformats geht von der Annahme aus, da· die Bits 6 und 7 beim   */
/*      Standardformat niemals beide 1 sind, da eine Gesamtstellenanzahl von */
/*      12 beim Standardformat nicht sinnvoll ist (die Maximallaenge bei     */
/*      long-Registern betraegt im Dezimalsystem 10 Stellen).                */

/* Fuer die ASCII-Variante wird die Kodierung fuehrender Nullen der Laenge   */
/* zugerechnet um eine maximale Laenge von 64 kodieren zu koennen            */
/* Also:                                                                     */
/* Das Formatbyte ist wie folgt aufgebaut:                                   */
/*    7  6  5  4   3  2  1  0                                                */
/*    \--/  \_______________/                                                */
/*      |             |                                                      */
/*      |             |                                                      */
/*      |         Anzahl Stellen                                             */
/*      |...                                                                 */

/* Makros fuer die Erweiterung des Variablenformats fuer REGIST-Varianten
 * BINARY, HEX, OCTAL und ASCII
 */
#define MARK_NONSTD  0xc0
#define NO_FILL      0x00
#define FILL         0x20
#define SET_NONSTD_FORMAT(len,fill)   (MARK_NONSTD|(fill)|(len)) 
#define NONSTD_LEADING_ZEROES(format) ((format)&FILL)
#define NONSTD_LEN(format)            ((format)&(~FILL)&(~MARK_NONSTD))
#define IS_NONSTD(format)             ((((format)&MARK_NONSTD)==MARK_NONSTD) ? 1 : 0)
#define SET_STRING_FORMAT(len)        (MARK_NONSTD|((len)&0x3f))
#define STRING_LEN(format)            ((format)&0x3f)



/* ------------------------------------------------------------------------- *
 |  Funktionsaufrufe ueber die Datenstruktur                                 |
 * ------------------------------------------------------------------------- */

typedef struct {
   FUNC_INDEX  FuncInd;        /* Index in Adresstabelle fuer  Funktionen */
   PARAM_INDEX ParamInd;       /* Index in Tabelle fuer Parameter */
} FUNCT;

/* Folgende Konstante kann in der Datenstruktur als Null-Funktion verwendet  */
/* werden.                                                                   */

#define NOFUNC {0,0}

/* ------------------------------------------------------------------------- *
 |  Register                                                                 |
 * ------------------------------------------------------------------------- */

typedef struct {
   UWORD  RegNum;               /* Registernummer */
   UWORD  Ind1,Ind2,Ind3;       /* Indizes fuer das Register */
   BYTE  IndInfo;              /* Verwendung der Indizes */
} REGISTER;

/* Die folgenden zwei Makros konnen zum Abfragen bzw. Setzen des Index-Infos */
/* fuer einen bestimmten Index verwendet werden: I bezeichnet das IndInfo-    */
/* Byte, IX die Nummer des Inidzes (REG_INDEX1 - REG_INDEX3) und IF den Wert */
/* des Index-Infos: UNUSED, CONSTANT oder VARIABLE                           */

#define GET_REG_INDINFO(I,IX)     ( ((I) >> (IX)) & 0x03 )
#define SET_REG_INDINFO(I,IX,IF)  (I) = ( (I) & (0x03<<(IX)) | ((IF)<<(IX)) )

#define REG_INDEX1  0          /* Info fuer Index 1 */
#define REG_INDEX2  2          /* Info fuer Index 2 */
#define REG_INDEX3  4          /* Info fuer Index 3 */

#define NO_REGIND  0,0,0,0     /* Bei Abfrage eines Registers */
#define REGIND_UUU      SET_ALL_INDINFO(REG_IND_UNUSED,REG_IND_UNUSED,REG_IND_UNUSED)
#define REGIND_CUU      SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_UNUSED,REG_IND_UNUSED)
#define REGIND_CCU      SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_CONST ,REG_IND_UNUSED)
#define REGIND_CCC      SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_CONST ,REG_IND_CONST)
#define REGIND_CVU      SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_VAR   ,REG_IND_UNUSED)
#define REGIND_CVC      SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_VAR   ,REG_IND_CONST)
#define REGIND_VUU      SET_ALL_INDINFO(REG_IND_VAR   ,REG_IND_UNUSED,REG_IND_UNUSED)
#define REGIND_VCU      SET_ALL_INDINFO(REG_IND_VAR   ,REG_IND_CONST ,REG_IND_UNUSED)
#define REGIND_VVU      SET_ALL_INDINFO(REG_IND_VAR   ,REG_IND_VAR   ,REG_IND_UNUSED)
#define REGIND_VCC      SET_ALL_INDINFO(REG_IND_VAR,REG_IND_CONST,REG_IND_CONST)
#define REGIND_VVC      SET_ALL_INDINFO(REG_IND_VAR,REG_IND_VAR,REG_IND_CONST)
#define REGIND_CCV      SET_ALL_INDINFO(REG_IND_CONST,REG_IND_CONST,REG_IND_VAR)

#define ALL_IND_CONST   REGIND_CCC
#define NO_INDEX        REGIND_UUU

/* ------------------------------------------------------------------------- *
 |  Zyklischer und ereignisgetriebener Refresh                               |
 * ------------------------------------------------------------------------- */

typedef BYTE REFRESH;

/* Die folgenden Makros konnen zum Abfragen bzw. Setzen des zyklischen       */
/* Refresh-Modus verwendet werden und arbeiten mit Werten von 0..3           */

#define GET_CYCL_REFRESH(R)   ( (R) & 0x03 )
#define SET_CYCL_REFRESH(R,V) (R) = ((R) & 0x04) | (V)
#define CYCL_REFRESH_NONE    0
#define CYCL_REFRESH_SLOW    1
#define CYCL_REFRESH_INJ     2
#define CYCL_REFRESH_FAST    3

/* Die folgenden Makros konnen zum Abfragen bzw. Setzen des ereignis-        */
/* getriebenen Refreshs verwendet werden und arbeiten mit Boolean-Werten     */

#define GET_EVENT_REFRESH(R)   ( (R) & 0x04 )
#define SET_EVENT_REFRESH(R,V) (R) = ((R) & 0x03) | (V)
#define EVENT_REFRESH_ON     (0<<2)
#define EVENT_REFRESH_OFF    (1<<2)

/* Das folgende Makro kann dazu verwendet werden, die beiden Refreshtypen   */
/* bei der Definition der Strukturen zu setzen. Es kann wie eine Konstante  */
/* verwendet werden. C ist die zyklische Refreshinfo, E die ereignisgetr.   */

#define SET_REFRESH(C,E)     ((C) | (E))

/* ------------------------------------------------------------------------- *
 |  allgemein Konstanten (zur besseren Lesbarkeit)                           |
 * ------------------------------------------------------------------------- */

#define  UP                   1
#define  DOWN                 2
#define  LEFT                 3
#define  RIGHT                4

/* ------------------------------------------------------------------------- *
 |  Kennungen der verschiedenen Elementtypen:                                |
 * ------------------------------------------------------------------------- */

#define ELID_FIXTEXT       1
#define ELID_BITMAP        2
#define ELID_REGSOLL       3
#define ELID_REGIST        4
#define ELID_BITSOLL       5
#define ELID_BITIST        6
#define ELID_TEXT          7
#define ELID_INDTEXT       8
#define ELID_HEATTEXT      9

#define ELID_NAME         10
#define ELID_DIM          11
#define ELID_IST          12
#define ELID_BITARRAY     13

#define ELID_SPECFUNCT    20

#define ELID_BEAMH        30
#define ELID_BEAMV        31
#define ELID_CYLHIST      32
#define ELID_SOLLGRAF     33

#define ELID_CYLROCKET    40
#define ELID_COORDINATE   41
#define ELID_AXIS         42

#define ELID_XR           50
#define ELID_XS           51
#define ELID_GAUSS        52

#define ELID_OVERVIEW1    60
#define ELID_OVERVIEW2    61
#define ELID_WORK         62
#define ELID_SOLLIST1     63
#define ELID_SOLLIST2     64
#define ELID_SOLLIST3     65
#define ELID_SOLLIST4     66
#define ELID_TOL1         67
#define ELID_TOL2         68
#define ELID_TOL3         69
#define ELID_TOL4         70

#define ELID_DIR          80
#define ELID_ERR          81
#define ELID_BDE          82
#define ELID_DRVERR       83
#define ELID_BDE_ACTVAL   84
#define ELID_BDE_FAULTMSG 85
#define ELID_BDE_DOWNTIMES 86
#define ELID_BDE_REQVALCHG 87

#define ELID_ADJUST       90
#define ELID_DIAGNOSE    100
#define ELID_STATLINE    101
#define ELID_PROCGRAPH   110

#define ELID_REGIST_BINARY 120
#define ELID_REGIST_HEX    121
#define ELID_REGIST_OCTAL  122
#define ELID_REGIST_ASCII  123

#define ELID_KLICK			130

/* ------------------------------------------------------------------------- *
 |  Position in Textkoordinaten                                              |
 * ------------------------------------------------------------------------- */

typedef struct
   {
   BYTE  X;                    /* waagrechte Position */
   BYTE  Y;                    /* senkrechte Position */
   } POS;

/* ------------------------------------------------------------------------- *
 |  Position in Grakikkoordinaten                                            |
 * ------------------------------------------------------------------------- */

typedef struct
   {
   UWORD  X;                    /* waagrechte Position */
   UWORD  Y;                    /* senkrechte Position */
   } GRAPHPOS;

/* ------------------------------------------------------------------------- *
 |  Information ueber Aufbau des Directories des Datentraegers               |
 * ------------------------------------------------------------------------- */

typedef struct
   {
   BYTE  XPos;           /* x-Position der Ausgabe (0xff=keine Ausgabe) */
   BYTE  Length;         /* Laenge des Feldes */
   COLOR Col;            /* Farbe der Ausgabe */
   } DIR_INFO;


/****************************************************************************
*
*  Ab hier werden die verschiedenen Strukturen definiert, deren
*  Geammtheit die Datenstruktur ausmacht.
*
****************************************************************************/

#define NR_SOFTKEYS   5
#define NR_SPECKEYS   8
#define NR_FASTPAGE   11

/*****************************************************************************
*   Mit folgendem Typ kann man auf saemtliche Elemente zugreifen, da die 
*   ersten drei Eintraege in jedem Elementtyp gleich sind.
******************************************************************************/

typedef struct ELEMENTX ELEMENT;
#ifdef EL_NEAR_PTR
    /*typedef ELEMENT near *ELEMENT_PTR;*/
      typedef UWORD ELEMENT_PTR;
#  define NULL_ELEMENT (ELEMENT_PTR)0xffff
#else
   typedef ELEMENT *ELEMENT_PTR;
#  define NULL_ELEMENT NULL
#endif   

struct ELEMENTX
   {
   BYTE  Id;                  /* Identifizierung der Struktur */
   ELEMENT_PTR next;     /* Zeiger auf naechstes Element der Liste */
   REFRESH Refresh;           /* Refreshzyklus */
   };

/***************************************************************************
*  Folgender Typ definiert ein Objekt:
****************************************************************************/

typedef struct
   {
   BYTE    Line;              /* Zeile des Objektbeginns */
   ELEMENT *Element;          /* Zeiger auf untergeordnetes Element */
   REFRESH Refresh;           /* Zyklus fuer Dunkeltastungsroutine */
   FUNCT   Dark;              /* Zeiger auf Dunkeltastungsroutine */
   } OBJECT;

#define END_OF_PAGE {0xff}    /* Endekennung einer Objekttabelle */

/***************************************************************************
*  Folgender Typ definiert die Seitenstruktur
****************************************************************************/

typedef struct
   {
   UWORD        PageNr;                       /* Nummer der Seite */
   BYTE        Mode;                         /* Bit1: ASCII/Grafik */
   TEXT_INDEX  SoftkeyLine1 [NR_SOFTKEYS];   /* Index in StatTab */
   TEXT_INDEX  SoftkeyLine2 [NR_SOFTKEYS];   /* Index in StatTab */
   FUNCT       Softkeyfunct [NR_SOFTKEYS];   /* Zeiger auf Softkeyfunktion */
   FUNCT       Dark;                         /* Dunkeltastungsroutine */
   OBJECT      *OPointer;                    /* Zeiger auf erstes Objekt */
 } PAGE;

/*********************************************************************
X  AUFBAU DES PARAMETERS Mode in PAGE:
*
*  Bit:   07  06  05  04          03     02   01  00
*  Feld:  --  --  --  PASSWORD PMODE  ASCII  CHARSET
*
*  ZUGRIFFSMACROS:
*
*  SET_PAGE_PARAM    ( A, P, C, W ) - Parameter zusammenstellen
*  SET_PAGE_FULLMODE ( A, P, C )    - Parameter zusammenstellen (ohne Password)
*  SET_PAGE_MODE     ( A )          - ASCII-Grafik-Flag setzen, die anderen
*                                     Bits sind 0 (0=Standard)
*
*  GET_MODE_ASCIIGRAPH ( M )   - ASCII-Grafik-Flag isolieren
*  GET_MODE_PMODE      ( M )   - Pointer-Modus isolieren
*  GET_MODE_CHARSET    ( M )   - Zeichensatz isolieren
*  GET_MODE_PASSWORD   ( M )   - Password-Flag isolieren
*
*  Die OPointer-Indirektion wird nur bei den frei konfigurierbaren Seiten
*  benoetigt, bei denen nicht direkt auf die Objektliste gezeigt werden kann,
*  sondern nur ueber die Kern-Interfacetabelle, da die Objektliste hier im
*  BBRAM und damit im Kernprogramm liegt.
*  Die Zeichensatz-Option wird nur bei den Prozessgrafikseiten verwendet,
*  da diese einen kleineren Zeichensatz benoetigt.
*********************************************************************/

#define MODE_ASCII      0        /* Seite wird nur zeichenbezogen gedruckt */
#define MODE_GRAPHIC    1        /* Seite wird graphisch ausgedruckt.      */
#define MODE_PDIRECT    0        /* OPointer zeigt auf Objektliste         */
#define MODE_PINDIRECT  1        /* OPointer zeigt auf Pointer auf Objektl.*/
#define MODE_CHAR_STD   0        /* Standardzeichensatz verwenden          */
#define MODE_CHAR_PG    1        /* Zeichensatz fuer Prozessgrafik nehmen  */
#define MODE_CHAR_80    2        /* 80 Zeichen pro Zeile                   */
#define MODE_FREEPAGE   0x00     /* Seite nicht durch Password geschuetzt  */
#define MODE_PASSWORD   0x10     /* Seite nicht durch Password geschuetzt  */

/* Die folgenden Makros dienen zum Abfragen des Pagemodes.                 */
#define GET_MODE_ASCIIGRAPH(M)    ( ((M) >> 2) & 0x01)
#define GET_MODE_PMODE(M)         ( ((M) >> 3) & 0x01)
#define GET_MODE_CHARSET(M)       ( (M) & 0x03)
#define GET_MODE_PASSWORD(M)      ( (M) & 0x10)

/* Die folgenden Makros dienen zum Setzen des Modes. */
#define SET_PAGE_MODE(A)             ((A) << 2)
#define SET_PAGE_FULLMODE(A,P,C)   ( ((A) << 2) | ((P) << 3) | (C) )
#define SET_PAGE_PARAM(A,P,C,W)    (SET_PAGE_FULLMODE(A,P,C) | W )


/* Die folgenden Konstanten definieren moegliche Modes, die nicht in der   */
/* Seitenbeschreibung definiert werden, sondern nur Teile der Seite betref-*/
/* fen, welche mit der Dunkeltastungsroutine veraendert werden. Die Modes  */
/* werden ueber Softkey getoggelt.                                         */

#define MODE_WAY        0        /* Wegbezogene Seite                      */
#define MODE_VOLUME     1        /* Volumenbezogene Seite                  */


/****************************************************************************
*  Folgender Typ definiert den Header der Datenstruktur
****************************************************************************/

typedef struct
   {
   char  Zoom[2];             /* Zeichen mit Zoom-Symbol */
   POS   ZoomPos;
   char  ASCII[2];            /* Zeichen mit ASCII-Symbol */
   char  Graphik[2];          /* Zeichen mit Grafik-Symbol */
   POS   ASCII_Graphik_Pos;
   char  Download[2];         /* Zeichen mit Download-Symbol */
   POS   DownloadPos;
   FUNCT SpecKey [NR_SPECKEYS]; /* Zeiger auf Routinen fuer Sondertasten */
   UWORD  NrFirstPage;         /* Nummer der zuerst angezeigten Seite */
   UWORD  FastSelPage [NR_FASTPAGE];   /* Seiten fuer Schnellwahltasten */
   UWORD  Softkey [NR_SOFTKEYS];       /* Bitmapindex fuer Terminalmode-Softk. */
   FUNCT SoftkeyFunct [NR_SOFTKEYS];  /* Zeiger auf Softkeyfunktion */
   COLOR Text;                /* Standardfarbe fuer Festtexte */
   COLOR TextH;               /* Standardfarbe fuer Festtexte im Hintergrund */
   COLOR ActText;             /* Farbe fuer Festtext in Sollwertzeile */
   COLOR ActTextH;            /* Farbe fuer Festtext in Sollwertzeile im H. */
   COLOR Var;                 /* Standardfarbe fuer Soll- und Istwerte */
   COLOR VarH;                /* Standardfarbe fuer Soll- und Istwerte im H. */
   COLOR VarHNotEq;           /* Farbe fuer ungleichen Sollwert im Hintergrund*/
   COLOR AktVar;              /* Farbe fuer aktuellen Sollwert */
   COLOR AktVarH;             /* Farbe fuer aktuellen Sollwert im Hingergr. */
   COLOR InpVar;              /* Farbe fuer Sollwert bei Eingabe */
   COLOR InpVarH;             /* Farbe fuer Sollwert bei Eingabe im Hinterg. */
   PAGE *FirstPage;           /* Zeiger auf die Liste der Seiten */
   } HEADER_DSTRUCT;



/***************************************************************************
*  Hier werden die Typen der einzelnen Elemente definiert:
****************************************************************************/

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   COLOR       Col;           /* Farbe und Attribut */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   TEXT_INDEX  Statext;       /* Index in Adresstabelle der Festtexte */
   } FIXTEXT;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   BYTE        Prio;          /* Prioritaet des Bildschirmobjekts */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   BITMAP_INDEX BitmapPointer;/* Index in Adresstabelle der Bitmaps */
   } IQT_BITMAP;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   COLOR       Col;           /* Farbe und Attribut */
   BYTE        keypos;        /* Aenderung bei Schluesselschalterstellung */
   UWORD        VarNr;         /* Variablennummer (Zeilennummer) fuer Auswahl */
   REGISTER    Reg;           /* RegisterNr, Ind1, Ind2, Ind3, Indexinfo */
   FORMAT      Format;        /* Anzahl Stellen gesamt, Anzahl Nachkommast. */
   ELEMENT_PTR Dim;           /* Zeiger auf Fest- oder IndText mit Einheit */
   ELEMENT_PTR Name;          /* Zeiger auf Fest- oder IndText mit Namen */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   FUNCT       Funct1;        /* Userfunktion 1 */
   FUNCT       Funct2;        /* Userfunktion 2 */
   } REGSOLL;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   COLOR       Col;           /* Farbe und Attribut */
   REGISTER    Reg;           /* RegisterNr, Ind1, Ind2, Ind3, Indexinfo */
   FORMAT      Format;        /* Anzahl Stellen gesamt, Anzahl Nachkommast. */
   ELEMENT_PTR Dim;           /* Zeiger auf Fest- oder IndText mit Einheit */
   ELEMENT_PTR Name;          /* Zeiger auf Fest- oder IndText mit Namen */
   UWORD        VarNr;         /* Variablennummer (Zeilennummer) fuer Auswahl */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   } REGIST;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   COLOR       Col;           /* Farbe und Attribut */
   BYTE        keypos;        /* Aenderung ab Schluesselschalterstellung */
   UWORD        VarNr;         /* Variablennummer (Zeilennummer) fuer Auswahl */
   UWORD        RegNr;         /* Nummer (Name) des Bits */
   UWORD        Num0;          /* Einzugebende Zahl fuer Bit = 0 */
   UWORD        Num1;          /* Einzugebende Zahl fuer Bit = 1 */
   ELEMENT_PTR Name;          /* Zeiger auf Fest- oder IndText mit Namen */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   FUNCT       Funct1;        /* Userfunktion 1 */
   FUNCT       Funct2;        /* Userfunktion 2 */
   } BITSOLL;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   COLOR       Col;           /* Farbe und Attribute */
   UWORD        RegNr;         /* Nummer (Name) des Bits */
   TEXT_INDEX  Text0;         /* Index in Statext fuer Bit = 0 */
   TEXT_INDEX  Text1;         /* Index in Statext fuer Bit = 1 */
   ELEMENT_PTR Name;          /* Zeiger auf Fest- oder IndText mit Namen */
   UWORD        VarNr;         /* Variablennummer (Zeilennummer) fuer Auswahl */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   } BITIST;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   COLOR       Col;           /* Farbe und Attribut */
   BYTE        keypos;        /* Aenderung ab Schluesselschalterstellung */
   UWORD        VarNr;         /* Variablennummer (Zeilennummer) fuer Auswahl */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   FUNCT       Funct1;        /* Userfunktion 1 */
   FUNCT       Funct2;        /* Userfunktion 2 */
   BYTE        RowStart;      /* Start-Zeile  im var. Text */
   BYTE        ColumnStart;   /* Start-Spalte im var. Text */
   BYTE        RowSize;       /* Anzahl Ausgabe-Zeilen */
   BYTE        ColumnSize;    /* Anzahl Ausgabe-Spalten */
   BYTE        ArrowKey;      /* Pfeiltasten TRUE/FALSE */
   TEXTVAR_INDEX TextIndex;   /* Index in var. Texttabelle */
   REGISTER    Reg;           /* Offset zu RowStart */
   /* Bei ELID_HEATTEXT:         Reg.Ind1:    Index 1 der Umsetztabelle
                                 Reg.Ind2:    Index 2 der Umsetztabelle
                                 Reg.IndInfo: Konstante oder varibabel Indizes
                                 TextIndex:   1 = Zylinder, 2 = Werkzeug,
                                              3 = Temperierg.
   */
   } TEXT;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   COLOR       Col;           /* Farbe und Attribut */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   REGISTER    IndexReg;      /* RegisterNr, Ind1, Ind2, Ind3, Indexinfo */
   TEXTIND_INDEX TextPointer; /* Index in Adresstabelle der Texte */
   BYTE        Length;        /* Anzahl der benutzten Eintrage der Tabelle */
   } INDTEXT;


typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position des Textbeginns */
   COLOR       Col;           /* Farbe und Attribut */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   UWORD        VarTab;        /* Registernummer der ben. Variablentabelle */
   UWORD        Index;         /* Index in der Variablentabelle */
   BYTE        IndInfo;       /* Verw. des Index: REG_IND_CONST, REG_IND_VAR */
   UWORD        Length;        /* maximale Laenge des Strings */
   } NAMEDIMIST;


#define BA_HORIZONTAL   0x00
#define BA_VERTICAL     0x01
#define BA_LSB          0x00
#define BA_MSB          0x02
#define BA_OR           0x00     /* Alle Bit-Konstellationen erlaubt */
#define BA_XOR_0        0x04     /* Nur 1 Bit darf aus sein */
#define BA_XOR_1        0x08     /* Nur 1 Bit darf an sein */

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position */
   COLOR       Dummy;         /* 26.06.92 TSchw: eingefuegt wg. Kompatib.  */
   BYTE        keypos;        /* Aenderung bei Schluesselschalterstellung */
   UWORD        VarNr;         /* Variablennummer (Zeilennummer) fuer Auswahl */
   FUNCT       Dark;          /* Dunkeltastungsroutine */
   FUNCT       Funct1;        /* Userfunktion 1 */
   FUNCT       Funct2;        /* Userfunktion 2 */
   ELEMENT_PTR Dim;           /* Zeiger auf Fest- oder IndText mit Einheit */
   ELEMENT_PTR Name;          /* Zeiger auf Fest- oder IndText mit Namen */
   REGISTER    Reg;           /* Register, das die Bits enthaelt */
   COLOR       Col[3];        /* Farben ([0]: Bit=0, [1]: Bit=1, [2]: Trenn) */
   char        OnOffChar[2];  /* Ausgabezeichen ([0]: Bit OFF / [1]: Bit ON) */
   char        DistChar[4];   /* Trennzeichen (max. 4 Zeichen) */
   BYTE        Length;        /* Anzahl der Arrayelemente */
   BYTE        Offset;        /* Startoffset der Bits */
   BYTE        Distance;      /* Abstand der Arrayel. (1=keine Zwischenraum) */
   BYTE        Flags;         /* MSB/LSB, VERT/HORIZ, OR/XOR */
   } BITARRAY;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   FUNCT       Routine;       /* Zeiger auf die Sonderroutine */
   } SPECFUNCT;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         StartPos;      /* Linke, obere Ecke der Grafik in Textkoord. */
   POS         EndPos;        /* Rechte, untere Ecke der Grafik in Textkoord.*/
   REGISTER    IstReg;        /* Ist-RegisterNr, Ind1, Ind2, Ind3, Indexinfo */
   REGISTER    LeftSkal;      /* Linker Skalierendwert */
   REGISTER    RightSkal;     /* Rechter Skalierendwert */
   REGISTER    SollReg[10];   /* Sollwertregister, werden als Strich angez. */
   BYTE        SkalInfo;      /* Skalierendwerte konstant oder Register */
   FORMAT      Format;        /* Anzahl Stellen gesamt, Anzahl Nachkommast. */
   COLOR       BeamCol;       /* Farbe des Balkens */
   COLOR       SollCol;       /* Farbe der Sollwertstriche */
   COLOR       SkaleCol;      /* Farbe der Skala */
   COLOR       SkaleValCol;   /* Farbe der Skalierendwerte */
   BYTE        Prio;          /* Prioritaet des Grafikfensters */
   } BEAM;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         StartPos;      /* Linke, obere Ecke der Grafik in Textkoord. */
   POS         EndPos;        /* Rechte, untere Ecke der Grafik in Textkoord.*/
   BYTE        SkaleCol;      /* Farbe der Skala (alle Farben Vordergrundf.) */
   BYTE        LineCol;       /* Farbe der Querlinien                        */
   BYTE        SollBalkCol;   /* Farbe der Sollwertstriche                   */
   BYTE        IstOKCol;      /* Farbe des Istwertbalkens innerhalb der engen*/
                              /* Toleranzgrenzen                             */
   BYTE        IstNarrowCol;  /* Farbe des Istwertbalkens auserhalb der engen*/
                              /* und innerhalb der weiten Toleranzgrenzen    */
   BYTE        IstWideCol;    /* Farbe des Istwertbalkens auserhalb der wei- */
                              /* ten Toleranzgrenzen                         */
   BYTE        TolBeamCol;    /* Farbe des Toleranzbalkens                   */
   BYTE        TolWideCol;    /* Farbe der Striche der weiten Toleranzen     */
   BYTE        TolNarrowCol;  /* Farbe des Bereichs der engen Toleranzen     */
   BYTE        RefIstCol;     /* Farbe des Referenzistwertstriches           */
   BYTE        Prio;          /* Prioritaet des Grafikfensters */
   BYTE        PartNr;        /* Teil 1 oder 2 des Histogramms               */
   REGISTER    NoOfZones;     /* Anzahl der Zonen */
   UWORD        AggregatReg;   /* Aggregatregister */
   } CYLHIST;

typedef struct
   {
   REGISTER    Skal1;         /* Erster  Skalierendwert */
   REGISTER    Skal2;         /* Zweiter Skalierendwert */
   FORMAT      SkalFormat;    /* Format der Skalierwerte */
   BYTE        SkalInfo;      /* Skalierendwerte konstant oder Register */
   TEXT_INDEX  SkalTextTop;   /* Text an Pfeilspitze (Index in stattab) */
   TEXT_INDEX  SkalTextCurve; /* Text an Kurve (Index in stattab) */
   TEXT_INDEX  SkalTextDim;   /* Dimension an Pfeilspitze (Index in stattab) */
   } SKAL_TYPE;

#define STAGES       0        /* Defaultdarstellung Stufen */
#define RAMPS   0xffff        /* Defaultdarstellung Rampen */
#define SWG_ADD      0        /* Werte der X-Achse werden kumuliert */
#define SWG_ABS      1        /* Werte der X-Achse sind absolut */
#define SWG_Y_COUNT  2        /* Anzahl Sollwert-Kurven */

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   BYTE        Refresh;
   POS         StartPos;      /* Linke, obere Ecke der Grafik in Textkoord. */
   POS         EndPos;        /* Rechte, untere Ecke der Grafik in Textkoord.*/
   REGISTER    XRegNr[10];    /* Register-Nr. fuer X-Achse */
   BYTE        XRegInfo;      /* Werte der X-Achse addiert oder absolut */
   REGISTER    YRegNr[SWG_Y_COUNT][10];     /* Register-Nr. fuer Y-Achse */
   REGISTER    CountReg;      /* Anzahl der Spritzstufen oder 0 als RegNum */
   BYTE        Direction;     /* Aufbau von links oder rechts */
   SKAL_TYPE   XSkal;         /* Skalierung der X-Achse */
   SKAL_TYPE   YSkal[SWG_Y_COUNT];        /* Skalierungen der Y-Achse */
   COLOR       CurveCol[SWG_Y_COUNT];     /* Kurvenfarben */
   COLOR       SkaleCol[SWG_Y_COUNT];     /* Farbe der Beschriftung an Kurve */
   COLOR       TopCol[SWG_Y_COUNT];       /* Farbe der Texte an Y-Pfeilspitze */
   COLOR       Color[5];                  /* Alle restlichen Farben */
               /* Color[0] = Farbe der Beschriftung an X-Achse */
               /* Color[1] = Farbe der Texte an X-Pfeilspitze */
               /* Color[2] = Koordinatenkreuzfarbe */
               /* Color[3] = frei */
               /* Color[4] = frei */
   BYTE        Prio;          /* Prioritaet des Grafikfensters */
   UWORD        Mode[2]; /* Zwei Zustandsbits: Mode[0] ist das Bit fuer
                         * die Stufen-Rampen-Umschaltung (0=Rampen)
                         * Ist kein Bit angegeben, werden mit 0 (STEPS)
                         * Stufen und mit -1 (RAMPS) Rampen angezeigt
                         */
   } SWG;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;           /* Position der Grafikbeginn */
   COLOR       Col;           /* Farbe der Rakete */
   COLOR       ColTm;         /* Farbe fuer Massentemperierung */
   COLOR       TrennCol;      /* Farbe des Trennbalkens */
   COLOR       MinusCol;      /* Farbe der Nr. und des Balkens bei neg. Wert */
   COLOR       PlusCol;       /* Farbe der Nr. und des Balkens bei pos. Wert */
   BYTE        PartNr;        /* Teil 1 oder 2 der Rakete */
   REGISTER    NoOfZones;     /* Anzahl der Zonen */
   UWORD        AggregatReg;   /* Aggregatregister */
   } CYLROCKET;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   GRAPHPOS    Pos;           /* Linke, obere Ecke der Grafik */
   BYTE        XLength;       /* Breite der gesamten Grafik */
   BYTE        YLength;       /* Hohe der gesamten Grafik */
   UWORD        XAxis;         /* RegisterNr des angezeigten Sollwertes */
   UWORD        YAxis;         /* RegisterNr des angezeigten Sollwertes */
   UWORD        ZAxis;         /* RegisterNr des angezeigten Sollwertes */
   UWORD        OSkal;         /* Oberer Skalierendwert */
   UWORD        MaxLength;     /* Maximale Lange der Vektoren */
   COLOR       VecCol;        /* Farbe der Vektoren */
   BYTE        Prio;          /* Prioritat des Grafikfensters */
   } COORDINATE;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         StartPos;      /* Linke, obere Ecke der Grafik in Textkoord. */
   POS         EndPos;        /* Rechte, untere Ecke der Grafik in Textkoord.*/
   COLOR       FixCol1;       /* Farbe der Rasterung */
   COLOR       FixCol2;       /* Farbe der Achsen */
   COLOR       FixCol3;       /* Farbe der Toleranzgrenzen */
   COLOR       CurveCol1;     /* Balkenfarbe in Toleranzgrenze */
   COLOR       CurveCol2;     /* Balkenfarbe ausser Toleranzgrenze */
   UWORD        CurveInd;      /* Konstante mit Index in VarTab etc. */
   BYTE        Prio;          /* Prioritaet des Grafikfensters */
   } AXIS;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         StartPos;      /* Startposition des Grafik-Fensters */
   POS         EndPos;        /* Endposition des Grafik-Fensters */
   COLOR       TextCol;       /* XQ/XR: Farbe der Skalierungen */
                              /* GAUSS: Farbe der Skalierungen */
   COLOR       RasterCol;     /* XQ/XR: Farbe des Rasters */
                              /* GAUSS: Farbe des Rasters */
   COLOR       CountCol;      /* XQ/XR: Farbe des Schusszaehlers/Datums */
                              /* GAUSS: Farbe der Zeilen der Spezif.-Grenzen */
   COLOR       CurveCol;      /* XQ/XR: Farbe der drei Kurven */
                              /* GAUSS: Farbe der Wahrscheinlichkeitsgerade */
   COLOR       CurveCol2;     /* XQ/XR: Farbe der Ereignisgrenzen/Balkendiag.*/
                              /* GAUSS: Farbe des Balkendiagramms */
   COLOR       CurveCol3;     /* XQ/XR: Farbe der man. Ereignisgrenzen */
                              /* GAUSS: Farbe der Grenzen -2s / +2s */
   COLOR       CurveCol4;     /* XQ/XR: Farbe bei Aenderung Stichprobenumfang*/
                              /* GAUSS: Farbe der Summenprozenthaufigkeit */
   COLOR       ManualCol;     /* XQ/XR: Farbe bei manueller Stichprobe */
                              /* GAUSS: nicht belegt */
   BYTE        RastCount1;    /* XQ/XR: Anzahl Rasterzeilen der xq-Grafik */
                              /* GAUSS: Anzahl Rasterspalten des Balkendiag. */
   BYTE        RastCount2;    /* XQ/XR: Anzahl Rasterzeilen der RS-Grahik */
                              /* GAUSS: Anzahl Balken */
   BYTE        Prio;          /* Prioritat des Grafikfensters */
   } STATGRAPH;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   POS         Pos;
   BYTE        Width;         /* Breite */
   BYTE        High;          /* Hoehe */
   COLOR       Chan1;         /* Farbe fuer Kurve aus Kanal 1 */
   COLOR       Chan2;         /* Farbe fuer Kurve aus Kanal 2 */
   COLOR       Chan3;         /* Farbe fuer Kurve aus Kanal 3 */
   COLOR       Chan4;         /* Farbe fuer Kurve aus Kanal 4 */
   COLOR       Tol;           /* Farbe fuer Toleranzband */
   COLOR       SollCurve;     /* Farbe fuer Sollkurve */
   COLOR       Cursor;        /* Farbe fuer Cursor */
   COLOR       SpeedCurve1;   /* Farbe fuer Geschwindigkeitskurve S.47.1 */
   COLOR       SpeedCurve2;   /* Farbe fuer Geschwindigkeitskurve S.47.1 */
   COLOR       WayCurve1;     /* Farbe fuer Wegkurve S.47.1 */
   COLOR       WayCurve2;     /* Farbe fuer Wegkurve S.47.1 */
   } PROCGRAPH;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   BYTE        YPos;          /* Zeile, in der die Anzeige beginnt */
   BYTE        NrLines;       /* Anzahl der Zeilen fuer die Ausgabe */
   DIR_INFO    Info[11];      /* Farbe, Position und Laenge eines Feldes */
   } DIRPAGE;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   BYTE        YPos;          /* Zeile, in der die Anzeige beginnt */
   BYTE        NrLines;       /* Anzahl der Zeilen fuer die Ausgabe */
   COLOR       Col;           /* Farbe der Ausgabe */
   } SPECPAGE;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   BYTE        YPos;          /* Zeile, in der die Anzeige beginnt */
   UWORD        Constants[5];  /* Einstellkonstanten */
   COLOR       Col;           /* Farbe der Ausgabe */
   } ADJUST;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   BYTE        YPos;          /* Zeile, in der die Anzeige beginnt */
   COLOR       Col;           /* Farbe der Ausgabe */
   UWORD        IscosNr;       /* Nr. des Register mit IscosNr */
   UWORD        IscosAdr;      /* Nr. des Register mit IscosAdresse */
   UWORD        NrReg;         /* Nr. des Register mit Registeranzahl */
   } DIAGNOSE;

typedef struct
   {
   BYTE        Id;
   ELEMENT_PTR next;
   REFRESH     Refresh;
   BYTE        YPos;          /* Zeile, in der die Anzeige beginnt */
   } STATLINE;


/****************************************************************************
*
*  Ab hier werden Strukturen definert, die fuer die verschiedenen anderen 
*  Tabellen in den Datenstruktureproms und den Spracheproms gebraucht werden.
*
****************************************************************************/


/* ------------------------------------------------------------------------- *
 |  Typen fuer Register- und Bitbeschreibungstabellen im Datenstruktur-Eprom |
 * ------------------------------------------------------------------------- */

typedef struct
   {
   UWORD  RegNr;                /* Registernummer zum Zugriff auf das Reg. */
   UWORD  RegType;              /* Typ des Registers: int, double-int */
   UWORD  FltFunc;              /* Index in Zeigertabelle der Filterfunktionen*/
   FUNCT Conv;                 /* Zeiger auf Umwandlungsroutine */
   BYTE  IscosNr;              /* Nummer des ISCOS */
   UWORD  IscosAdr;             /* Adresse im ISCOS */
   UWORD  Blockbit;             /* Adresse des Blockbits im ISCOS */
   UWORD  UngleichNullBit;      /* Adresse des UngleichNullBits im ISCOS */
   } ISCOSREG_TYPE;

typedef struct
   {
   UWORD  RegNr;                /* Registernummer zum Zugriff auf das Reg. */
   UWORD  RegType;              /* Typ des Registers: int, long, Tabellen */
   UWORD  FltFunc;              /* Index in Zeigertabelle der Filterfunktionen*/
   } IQTREG_TYPE;

typedef struct
   {
   UWORD  RegNr;                /* Registernummer zum Zugriff auf das Bit */
   UWORD  RegType;              /* Typ des Registers */
   UWORD  FltFunc;              /* Index in Zeigertabelle der Filterfunktionen*/
   BYTE  IscosNr;              /* Nummer des ISCOS */
   UWORD  IscosAdr;             /* Adresse im ISCOS */
   BYTE  LogAdr;               /* Nummer des Bits innerhalb des Logikworts */
   } ISCOSBIT_TYPE;


typedef struct
   {
   UWORD  KRegNr;               /* Kernprogrammspezifische Registernummer  */
   UWORD  RegNr;                /* Registernummer zum Zugriff auf das Reg. */
   UWORD  RegType;              /* Typ des Registers: int, injreg */
   } K_ISCOSREG_TYPE;

typedef struct
   {
   UWORD  KRegNr;               /* Kernprogrammspezifische Registernummer  */
   UWORD  RegNr;                /* Registernummer zum Zugriff auf das Reg. */
   UWORD  RegType;              /* Typ des Registers: int, injreg */
   } K_IQTREG_TYPE;

typedef struct
   {
   UWORD  KRegNr;               /* Kernprogrammspezifische Registernummer */
   UWORD  RegNr;                /* Registernummer zum Zugriff auf das Bit */
   UWORD  RegType;              /* Typ des Registers: int, injreg */
   } K_ISCOSBIT_TYPE;

typedef struct {
   BYTE IscosNr;
   UWORD IscosAdr;
   UWORD Nr;
   } ITL_DESCR2;

/* ------------------------------------------------------------------------- *
X|  Type fuer Telegrammbeschreiber                                           |
 * ------------------------------------------------------------------------- */
typedef enum { TLG_HM_BEGIN=1, TLG_HM_COMPLETE, 
               TLG_HM_HEADER,  TLG_HM_DATA } TLGHM_TYPE;

typedef enum { TLG_HC_PROCEED, TLG_HC_DONE } TLGHC_TYPE;

typedef TLGHC_TYPE (*TLGHOOKFP)(TLGHM_TYPE, void *, UWORD, ULONG);

#define MAXTLGHEADLEN 10
typedef struct tlgdscr_type { 
   TLGHOOKFP Hook;            /* Funktion zum Eingreifen in Protokoll      */
   UWORD  IscosNo;             /* Iscosnummer                               */
   UWORD  IscosAddr;           /* Startadresse des Telegrammbereichs        */
   UWORD  HandSReg;            /* Direkte Logikwortadresse                  */
   UWORD  TlgType;             /* Bedeutung wie RegType in der Registertab. */
                              /* aber nur READ- und SOLLISTTYPE benutzt    */
   ULONG  MaxAge;              /* ms, Zulaessiges Alter der Istwerte        */
   UWORD  InitPollRate;        /* Wartezeit bis zum ersten Zugriff          */
   UWORD  PollRate;            /* msec, Spanne zwischen Handshaketests      */
                              /* 0=default, kleine Werte fuer dringende,   */
                              /* grosse (> 500) fuer weniger dringende.    */  
   UWORD  Timeout;             /* Anzahl der Zugriffe bis Timeout erfolgt   */
   BYTE  Wait;                /* Gibt an, ob die Registerschnittstelle auf */
                              /* Erledigung von Telegrammauftraegen warten */
                              /* soll (TRUE) oder nicht (FALSE)            */
   UWORD  HeadLen;             /* Laenge des Telegrammheaders in WORDs      */
   UWORD  DataLen;             /* Anzahl der Datenregister im Telegramm     */
   UWORD  DMAAddrInd;          /* DMA-Adresse als Index in Adresstabelle    */
                              /* im Kundenprom                             */
   UWORD  Header[MAXTLGHEADLEN];  /* Platz fuer den Header                  */
} TLGDSCR_TYPE;



/* ------------------------------------------------------------------------- *
 |  Typen fuer variable Texte                                                |
 * ------------------------------------------------------------------------- */

/* Umrechnungstabelle */
typedef struct
   {
   BYTE  RowSize;             /* Anzahl Zeilen */
   BYTE  ColumnSize;          /* Anzahl Spalten */
   UWORD  DiskInfo;            /* Kennung fuer Datentraeger-Speicherung */
   } VAR_TEXT_TYPE;


/* ------------------------------------------------------------------------- *
 |  Typen fuer Trenddarstellung                                              |
 * ------------------------------------------------------------------------- */

/* Referenz- und Toleranzgrenz-Tabelle */
#define  MAX_AXIS_TAB      5
#define  AXIS_TOL_ABSOLUT  0
#define  AXIS_TOL_PERCENT  1
/* PR 28.11.96
typedef  UWORD   AXISTAB_TYPE [ MAX_AXIS_TAB ];
*/
typedef struct axistab_type
{
	UWORD ist_reg_no;
	UWORD ref_reg_no;
	UWORD tolup_reg_no;
	UWORD toldown_reg_no;
	UWORD ctrl;
   UWORD check_reg_no;
	UWORD alt_ref_reg_no;
	UWORD alt_tolup_reg_no;
	UWORD alt_toldown_reg_no;
}	AXISTAB_TYPE;


/* ------------------------------------------------------------------------- *
 |  Typen fuer Text-Adresstabellen                                           |
 * ------------------------------------------------------------------------- */

typedef struct
   {
   UWORD  RegValue;             /* Wert des Registers, ab dem Text ang. wird */
   TEXT_INDEX  Text;           /* Index auf Text in Stattab */
   } INDTEXT_TYPE;

typedef struct
   {
   UWORD  BitNr;                /* Nummer des Bits, dem die Meldung zug. ist */
   char  *HostP;               /* Zeiger auf Host-Fehlerkuerzel */
   TEXT_INDEX Text;            /* Textindex der Fehlermeldung; */
   } ERRTAB_TYPE;

#define ERR_HOST(str)   #str
#define ERR_NO_HOST     NULL


/* ------------------------------------------------------------------------- *
 |  Typen fuer Datum/Uhrzeit                                                 |
 * ------------------------------------------------------------------------- */

/* moegliche Formate der Uhrzeit */
#define  TIME_STD    0     /* Standard-Format der Uhrzeit : xx:xx */

/* moegliche Formate des Datums */
#define  DATE_STD    0     /* Standard-Format des Datums  : xx.xx.xx */

typedef struct {
   BYTE DD, MM;
   UWORD YY;
   BYTE hh, mm, ss;
   } TIME_TYPE;                  /* Datum und Uhrzeit */

/* ------------------------------------------------------------------------- *
 |  Typen fuer Crashlogbuch                                                 |
 * ------------------------------------------------------------------------- */

/* Zur Bestimmung der zu ueberwachenden Register-Istwerte des Crashlogbuchs
   (incl. dessen Ausgabeformat) */
typedef struct
   {
   REGISTER    Reg;            /* Register-Istwerte */
   FORMAT      Format;         /* Ausgabeformat der Register */
   } CLB_REGIST_TYPE;

/*********************************************************************
X  Zustand der aktuellen Seite
*********************************************************************/

/* Struktur fuer DSPGetPageInfo */
 typedef struct dsp_page_info {
   UWORD     PageNr;     /* Aktuelle Seiten-Nr. */
   UWORD     WindowNr;   /* Aktuelle Window-Nr. */
   } DSP_PAGE_INFO;

/*********************************************************************
X  Macro's fuer Plausbilitaeten
*********************************************************************/
#define PLAUS_SET_PG_LN(p,l)  ((l)*1000+(p))
#define PLAUS_GET_PG(v)       ((v)%1000)
#define PLAUS_GET_LN(v)       ((v)/1000)



/*********************************************************************
X  Definitionen der neuen Prozessgrafik
*********************************************************************/

typedef struct
   {
   UWORD  X;                    /*  Groesse in X-Richtung */
   UWORD  Y;                    /*  Groesse in Y-Richtung */
   } PLANE_SIZE;

/* Farben fuer die verschiedenen Kanaele */
#define CHAN1_COLOR     COLOR_LIGHT_BLUE
#define CHAN2_COLOR     COLOR_GRAY
#define CHAN3_COLOR     COLOR_MAGENTA
#define CHAN4_COLOR     COLOR_BROWN
#define PG_TOL_COLOR    COLOR_RED
#define PG_SOLL_COLOR   COLOR_GREEN
#define SPEED1_COLOR    COLOR_BROWN
#define SPEED2_COLOR    COLOR_GRAY
#define WAY1_COLOR      COLOR_LIGHT_BLUE
#define WAY2_COLOR      COLOR_GREEN
#define CHAN1_TCOL      SET_FGBG_COLOR(CHAN1_COLOR,COLOR_BLACK)
#define CHAN2_TCOL      SET_FGBG_COLOR(CHAN2_COLOR,COLOR_BLACK)
#define CHAN3_TCOL      SET_FGBG_COLOR(CHAN3_COLOR,COLOR_BLACK)
#define CHAN4_TCOL      SET_FGBG_COLOR(CHAN4_COLOR,COLOR_BLACK)
#define PG_TOL_TCOL     SET_FGBG_COLOR(PG_TOL_COLOR,COLOR_BLACK)
#define PG_SOLL_TCOL    SET_FGBG_COLOR(PG_SOLL_COLOR,COLOR_BLACK)
#define SPEED1_TCOL     SET_FGBG_COLOR(SPEED1_COLOR,COLOR_BLACK)
#define SPEED2_TCOL     SET_FGBG_COLOR(SPEED2_COLOR,COLOR_BLACK)
#define WAY1_TCOL       SET_FGBG_COLOR(WAY1_COLOR,COLOR_BLACK)
#define WAY2_TCOL       SET_FGBG_COLOR(WAY2_COLOR,COLOR_BLACK)
#define STDCHAN1_CCOL   SET_FGBG_COLOR(COLOR_GREEN,COLOR_BLACK)
#define STDCHAN2_CCOL   SET_FGBG_COLOR(COLOR_LIGHT_GREEN,COLOR_BLACK)
#define STDCHAN1_TCOL   SET_FGBG_COLOR(COLOR_GREEN,COLOR_BLACK)
#define STDCHAN2_TCOL   SET_FGBG_COLOR(COLOR_LIGHT_GREEN,COLOR_BLACK)

#define MAX_CURVE_INDEX 200
#define MAX_GROUP_INDEX 10

/* Funktionen */
/* ACHTUNG: Die folgenden Funktions-ID's werden auf dem Datentraeger abge- */
/*  			speichert und duerfen daher NICHT GEAENDERT werden!!!				*/
#define FU_MACHINE    0
#define FU_AGGREGAT   1
#define FU_INJUNIT    2
#define FU_CLUNIT     3
#define FU_EJECTOR    4
#define FU_TOOL       5
#define FU_CORE       6


/* Funktionseinheiten je Funktion */
#define MAX_FUNCTION_UNITS 6

/* Kurven_Typ */
#define PG_IST         0
#define PG_SOLL        1
#define PG_TOL_UP      2
#define PG_TOL_DOWN    3
#define CURVE_TYPES    4

typedef unsigned short int	PG_CURVE_VALUE_TYPE;
#define NOOF_VALUES     1000

#define CURVE_COLOR    0

#define PG_SINGLE		1
#define PG_PAIR		2

/* Kurven_ID's */
/* ACHTUNG: Die folgenden Kurven-ID's werden auf dem Datentraeger abge-		*/
/*  			speichert und duerfen daher NICHT GEAENDERT werden!!!				*/
#define PG_CID_PH_T    1  /* ph(t) */ 
#define PG_CID_S_T     2  /* s(t) */ 
#define PG_CID_PI_T    3  /* pi(t) */ 
#define PG_CID_FREE    4  /* frei verfuegbar */ 
#define PG_CID_PH_S    5  /* ph(s) */ 
#define PG_CID_V_S     6  /* v(s) */ 
#define PG_CID_PI_S    7  /* pi(s) */ 
#define PG_CID_V_T     8  /* v(t) */ 
#define PG_CID_VERY_FREE 10

#define NO_REGISTER 0xff
#define REFERENCE    0x0000
#define NO_REFERENCE 0x0001

#define CURVE_COLORS  3
#define MAX_NOOF_CLIPBOARDS 20

/* Cursor- und X-Skalierpositionen
 */
#define LEFT_CURSOR  0
#define RIGHT_CURSOR 1
#define NO_CURSOR    0xff
#define LEFT_LIMIT   0
#define RIGHT_LIMIT  1

/* Modus fuer Datentraegerschreiboperation der Sollkurven 
 */
/* Nur die auf Seite 54.1 ausgewaehlten */
#define PG_SOLL_ACTUAL    1  
/* Alle Sollkurven */
#define PG_SOLL_COMPLETE  2

/* Kurve
 */

typedef struct
{
  UWORD CurveId;              /* Kurven-Id */
  UWORD GroupId;              /* Gruppen-Id */
  UWORD Ctrl;                 /* Kontrollwort fuer die naehere Spezifikation */
  BYTE ValueType;            /* Kurventyp */
  UWORD X_FactorMeas;         /* Skalierfaktor Messung Abszisse */
  UWORD X_FactorPhys;         /* Skalierfaktor physikalisch Abszisse */
  UWORD Y_FactorMeas;         /* Skalierfaktor Messung Ordinate */
  UWORD Y_FactorPhys;         /* Skalierfaktor physikalisch Ordinate */
  UWORD Y_Max;                /* Messbereichsendwert der Messwertaufnahme */
  COLOR Color[CURVE_COLORS]; /* Kurvenfarbe */
  UWORD DataBuf[2];           /* PPCCOM-Adresse Datenpuffer */
  UWORD ReqBlock[2];          /* PPCCOM-Adresse Request-Block */
  UWORD AckBlock;             /* PPCCOM-Adresse Acknowledge-Block */
  UWORD EventBuf;             /* PPCCOM-Adresse Ereignisse */
  REGISTER NoofUnits;        /* Anzahl Einheiten */
} PG_CURVE;

/* Kurvenzugriff
 */

typedef struct
{
  UWORD     GroupId;          /* Gruppen-Id */
  REGISTER CurveId;          /* Kurven-Id */
  UWORD     CurveType;        /* Kurventyp */
  REGISTER FunctionUnit;     /* Multiplexregister fuer Funktionseinheiten */
  REGISTER Y_0;              /* Messbereichsanfang der Darstellung */
  REGISTER Y_1;              /* Messbereichsende der Darstellung */
  COLOR Color[CURVE_COLORS];
} PG_CURVE_ACCESS;


typedef struct pg_config
   { 
   REGISTER RefChoice[2];
   REGISTER WorkTol;
   REGISTER StartWork;
   REGISTER EndWork;
   REGISTER Work;
   UWORD CarSollWrite;  /* Sollkurven Schreibmodus */
   PG_CURVE * Curves;
   UWORD NoofCurves;
   } PG_CONFIG;

typedef struct
   {
   REGISTER CurReg;
   COLOR	Color;
   } PG_CURSOR;
	
typedef struct pg_coord_sys
   {
   GRAPHPOS    Pos;           /* nicht benutzt
                               */
   PLANE_SIZE  Size;     	   /* Breite der Abszisse bzw. Ordinate
                               */
   UWORD        XSteps;        /* Anzahl Unterteilungsstriche Abszisse
                               */
   UWORD        YSteps;        /* Anzahl Unterteilungsstriche Ordinate
                               */
   COLOR       Color;
   } PG_COORD_SYS;
	
#define PG_MAX_CURVES	4


#define MAX_MARK_POSITIONS 6

typedef struct marker
   {
   COLOR Color;                          /* Farbe der Marker
                                          */
   REGISTER UpperLimit;                  /* Obergrenze der Markerpositionen (Anzahl)
                                          */
   REGISTER MarkPos[MAX_MARK_POSITIONS] ;/* Markerpositionen
                                          */
   UWORD SkalDiv;              			  /* Skalierfaktor (Mult/Div), um den */
   UWORD SkalMult;             			  /* die Register in MarkPos groesser */
													  /* sind als die view-Register,      */
													  /* z.B. MarkPos 1/100, view 1/10 sec*/
													  /*	  ==>  Mult = 10, Div = 1       */
   } MARKER;


typedef struct pg_clip_board
   {
   UWORD            CbId;          /* Klippbereichsnummer */
   UWORD            CbStateId;     /* Ressourcennummer */
   REGISTER        MeasPeriod;    /* Register X-Skalierung (nicht benutzt) */
   REGISTER        Mode;          /* Register Betriebsart   */
   REGISTER        Delay;         /* Register Verzoegerung  */
   REGISTER        Interval;      /* Register Messintervall  */
   REGISTER        Tolerance;     /* Toleranz */
   REGISTER        ActCurves;     /* Anzahl gleichzeitig angezeigter Istkurven */
   GRAPHPOS        Pos;           /* Linke, obere Ecke des Klippbereiches
                                   * in relativen Koordinaten
                                   */ 
   PLANE_SIZE      Size;          /* Groesse des Klippbereichs 
                                   * in relativen Koordinaten
                                   */
   PG_COORD_SYS    CoordSys;      /* Koordinatenkreuz */
   PG_CURVE_ACCESS CurveAccess[PG_MAX_CURVES]; /* n Kurven */
   REGISTER        XScale[2];     /* Skalierung der Abszisse (Maximalwert) */
   PG_CURSOR       Cursor[2];     /* Cursor */
   REGISTER        XView[2];      /* aktuelle Grenzen des X-Anzeigebereichs */
   MARKER          Mark;          /* Markierung der X-Achse */
   struct pg_clip_board *Next;    /* naechster Klippbereich */
   } PG_CLIP_BOARD;

typedef struct proc_graph
   {
   BYTE           Id;
   ELEMENT_PTR    next;
   REFRESH        Refresh;
   POS            Pos;		  	/* Linke, obere Ecke des Viewports
                                 * in Textkoordinaten
                                 */ 
   PLANE_SIZE     Size;         /* Groesse des Viewports in Text-
                                 * koordinaten
                                 */
   COLOR          Color;  	  	/* Farbe Viewport Hintergrund */
   PG_CLIP_BOARD  *ClipBoard; /* Erstes Clipboard */
   } PROC_GRAPH;

/* Elementdefinition fuer Klickmodus
 */
typedef struct klick_element
   {
   BYTE           Id;
   ELEMENT_PTR    next;
	UWORD				context;
	UWORD				entry;
	UWORD				context_ctrl;
   } KLICK_ELEMENT;

#endif      /* #ifndef _dstruct */




