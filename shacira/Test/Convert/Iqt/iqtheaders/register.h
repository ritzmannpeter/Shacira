/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     REGISTER.H
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
*               10.09.96 -PR-    Anzahl der Register in REG_CMD (n) von BYTE auf UWORD
*                                                         umgestellt, damit auch mal mehr als 255 Register
*                                                         uebertragen werden koennen.
*     01.04.98 -TSchw- REG_SPECTAB eingefuegt, um bei den Registern markieren
*                      zu koennen, wer ueber Filterfunktion eine spezielle
*                      Tabellenbehandlung bekommt. Diese Register duerfen
*                      von den Hintergrundfunktionen nicht bearbeitet werden.
*     21.09.98 -TSchw- Makro IS_HEATREG eingefuegt.
*     16.04.99 -TSchw- REG_DISK_PG eingefuegt.
*     23.04.99 -TSchw- REG_DISK_CORE eingefuegt.
*     03.06.03 -HA-    RegId eingefuegt.
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

/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     REGISTER.H   - Register-Funktionen (mit oder ohne DLL)
*
*  BESCHREIBUNG:
*     Deklarationen und Definitionen der Register-Funktionen.
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   23.04.92
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*
*  HISTORY:
*     23.04.92 -SF-    Implementierung
*
*  BEMERKUNGEN:
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  FUNKTIONEN:
*     Reg_Init - Initialisierung des Moduls IQTREGIM
*     ...
*
*  DATENTYPEN:
*     Nicht dokumentiert
*
*  VARIABLEN:
*     Keine
*
*.EM.***********************************************************************/

#ifndef _register
#define _register

/*.SI.***********************************************************************/
#include <syntax.h>
/*.EI.***********************************************************************/

/*********************************************************************
X  AUFBAU DES STEUERPARAMETERS CONTROL:
*
*  Bit:   15 14 13  12   11   10 09 08  07  06   05 04  03 02  01 00
*  Feld:  -------- BLOCK S/M  COM       FLT E/P  IND3   IND2   IND1
*                   BIT
*
*  ZUGRIFFSMACROS:
*
*  SET_ALL_INDINFO( i1,i2,i3 ) - Indexmaske zusammenstellen
*
*  GET_CTRL_IND1( ctrl ) - IND1 isolieren
*  GET_CTRL_IND2( ctrl ) - ...
*  GET_CTRL_IND3( ctrl ) - ...
*  GET_CTRL_EP( ctrl ) - E/P isolieren
*  GET_CTRL_FLT( ctrl ) - ...
*  GET_CTRL_COM( ctrl ) - ...
*  GET_CTRL_SM( ctrl ) - S/M isolieren
*  GET_CTRL_BLOCKBIT( ctrl ) - Blockbit isolieren
*
*********************************************************************/
/* Das folgende Makro kann wie eine Konstante benutzt werden zum Setzen des  */
/* Indexinfobytes in der Datenstruktur                                       */
#define SET_ALL_INDINFO(i1,i2,i3)   ( (i1) | (i2) << 2 | (i3) << 4 )

#define GET_CTRL_IND1( ctrl )       ( (ctrl) & 0x0003 )
#define GET_CTRL_IND2( ctrl )       ( (ctrl) >> 2 & 0x0003 )
#define GET_CTRL_IND3( ctrl )       ( (ctrl) >> 4 & 0x0003 )
#define GET_CTRL_EP( ctrl )         ( (ctrl) & 0x0040 )
#define GET_CTRL_FLT( ctrl )        ( (ctrl) & 0x0080 )
#define GET_CTRL_COM( ctrl )        ( (ctrl) & 0x0700 )
#define GET_CTRL_SM( ctrl )         ( (ctrl) & 0x0800 )
#define GET_CTRL_BLOCKBIT( ctrl )   ( (ctrl) & 0x1000 )


/*********************************************************************
X  BITMASKEN FUER CONTROL
*********************************************************************/
#define REG_IND_UNUSED           0   /* Werte fuer IND1/IND2/IND3 */
#define REG_IND_CONST            1
#define REG_IND_VAR              2

#define REG_IND1_UNUSED     0x0000   /* Direkte Werte fuer IND1 */
#define REG_IND1_CONST      0x0001
#define REG_IND1_VAR        0x0002

#define REG_IND2_UNUSED     0x0000   /* Direkte Werte fuer IND2 */
#define REG_IND2_CONST      0x0004
#define REG_IND2_VAR        0x0008

#define REG_IND3_UNUSED     0x0000   /* Direkte Werte fuer IND3 */
#define REG_IND3_CONST      0x0010
#define REG_IND3_VAR        0x0020

#define REG_PHYS            0x0000   /* Werte fuer E/P */
#define REG_EL              0x0040

#define REG_FILTER          0x0000   /* Werte fuer FLT */
#define REG_NO_FILTER       0x0080

#define REG_COM_NORMAL      0x0000   /* Werte fuer COM */
#define REG_COM_DIRECT_ID   0x0100
#define REG_COM_DIRECT_REG  0x0200
#define REG_COM_DIRECT_LW   0x0300
#define REG_COM_BUFFER      0x0400
#define REG_COM_SEND        0x0500
#define REG_COM_DIRECT_BIT  0x0600
#define REG_COM_BUFFER_LW   0x0700

#define REG_SINGLE          0x0000   /* Werte fuer S/M */
#define REG_MULTIPLE        0x0800

#define REG_BLOCKBIT        0x0000   /* Werte fuer Blockbit */
#define REG_NO_BLOCKBIT     0x1000

#define REG_WRITE           0x8000   /* Flag bei Filterfunktionen */

#define REG_BLOCK_NORMAL         0   /* Uebertragungstyp bei REG_MULTILPLE */
#define REG_BLOCK_FAST           1
#define REG_BLOCK_SLOW           2
#define REG_BLOCK_INJ            3

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
#define REGIND_UUU  SET_ALL_INDINFO(REG_IND_UNUSED,REG_IND_UNUSED,REG_IND_UNUSED)
#define REGIND_CUU  SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_UNUSED,REG_IND_UNUSED)
#define REGIND_CCU  SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_CONST ,REG_IND_UNUSED)
#define REGIND_CCC  SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_CONST ,REG_IND_CONST)
#define REGIND_CVU  SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_VAR   ,REG_IND_UNUSED)
#define REGIND_CVC  SET_ALL_INDINFO(REG_IND_CONST ,REG_IND_VAR   ,REG_IND_CONST)
#define REGIND_VUU  SET_ALL_INDINFO(REG_IND_VAR   ,REG_IND_UNUSED,REG_IND_UNUSED)
#define REGIND_VCU  SET_ALL_INDINFO(REG_IND_VAR   ,REG_IND_CONST ,REG_IND_UNUSED)
#define REGIND_VVU  SET_ALL_INDINFO(REG_IND_VAR   ,REG_IND_VAR   ,REG_IND_UNUSED)
#define REGIND_VCC  SET_ALL_INDINFO(REG_IND_VAR,REG_IND_CONST,REG_IND_CONST)
#define REGIND_VVC  SET_ALL_INDINFO(REG_IND_VAR,REG_IND_VAR,REG_IND_CONST)
#define REGIND_CCV  SET_ALL_INDINFO(REG_IND_CONST,REG_IND_CONST,REG_IND_VAR)
#define REGIND_CVV  SET_ALL_INDINFO(REG_IND_CONST,REG_IND_VAR,REG_IND_VAR)

#define ALL_IND_CONST   REGIND_CCC
#define NO_INDEX        REGIND_UUU

/*********************************************************************
X  KONSTANTEN FUER FILTERFUNKTIONEN
*********************************************************************/
#define REG_WRITE           0x8000   /* Gesetzt in cntrl bei DevWrite */
#define REG_READ            0x0000   /* ... bei DevRead */

#define REG_ABORT                0   /* Rueckgabewerte */
#define REG_CONTINUE             1


/*********************************************************************
X  REGISTER-KOMMUNIKATIONSBLOCK
*********************************************************************/
typedef struct {
   UWORD n;           /* Anzahl zu uebertragender Register */
   BYTE isc;         /* Nummer der ISCOS, falls erforderlich */
   UWORD id;          /* Nummer des ersten Registers */
   void * adr;       /* Zeiger auf Datenbereich */
} REG_CMD;

/*********************************************************************
X  AUFBAU DES TYPPARAMETERS REGTYPE:
*
*  Bit:   15    14 13   12  11   10    09 08   07 06   05 04 03 02 01 00
*  Feld:  TAB   DSK     TRF BG   DIR   RWI     DSK     REG              
*
*  BEDEUTUNG:
*
*  REG (6 Bit) - Registertyp (int, long, etc.)
*  DSK (4 Bit) - Datentraegertyp  
*  RWI (2 Bit) - Lese-/Schreib-Zusatzinformation
*  DIR (1 Bit) - Uebertragungsrichtung
*  BG  (1 Bit) - Art der Behandlung in Vorder-/Hintergrund
*  TRF (1 Bit) - Art der Uebertragung (1=TELEGRAMM 0=Normal)
*  TAB (1 Bit) - Spezielle Tabellenbehandlung ueber Filterfunktion
*
*  ZUGRIFFSMACROS:
*
*  GET_REGTYPE ( type ) - Registertyp isolieren
*  GET_DISKTYPE( type ) - Datentraegertyp isolieren
*  GET_RWITYPE ( type ) - Lese-Schreibinformation isolieren
*  GET_DIRTYPE ( type ) - Uebertragungsrichtung isolieren
*  GET_FGBGTYPE( type ) - Vorder-/Hintergrundtyp isolieren
*  GET_TRANSFER( type ) - TRF isolieren
*
*********************************************************************/
#define GET_REGTYPE(R)      ( (R) & 0x003f )
#define GET_DISKTYPE(R)     ( (R) & 0x60c0 )
#define GET_RWITYPE(R)      ( (R) & 0x0300 )
#define GET_DIRTYPE(R)      ( (R) & 0x0400 )
#define GET_FGBGTYPE(R)     ( (R) & 0x0800 )
#define GET_TRANSFER(R)     ( (R) & 0x1000 )
#define GET_SPECTAB(R)      ( (R) & 0x8000 )


/*********************************************************************
X  BITMASKEN FUER REGTYPE
*********************************************************************/
/* ---- Typgruppe REG: Registertyp                                         */
#define REG_NOTYPE   0x0000  /* Kein Typ (Fehler)                          */
#define REG_INT      0x0001  /* Integer-Register                           */
#define REG_DINT     0x0002  /* DoubleInt-Register (nur ISCOS)             */
#define REG_LONG     0x0003  /* Long-Register (nur IQT)                    */
#define REG_INT10    0x0004  /* Integer-Tab mit 10 Eintraegen (nur IQT)    */
#define REG_INT20    0x0005  /* Integer-Tab mit 20 Eintraegen (nur IQT)    */
#define REG_LONG10   0x0006  /* Long-Tab. mit 10 Eintraegen (nur IQT)      */
#define REG_LONG20   0x0007  /* Long-Tab. mit 20 Eintraegen (nur IQT)      */
#define REG_INJTAB   0x0008  /* Int-ISCOS-Reg-Tab. mit Spritzindizes       */
                             /* RegTab [MaxInjCyc] [MaxInjUnits] [MaxStat] */

/* ---- Typgruppe DSK: Dateityp */
#define REG_NODISK     0x0000 /* Reg. wird nicht auf Datentraeger gesp. */
#define REG_DISK_TOOL  0x0040 /* Datentraegerspeicherung werkzeugspezifisch */
#define REG_DISK_MAT   0x0080 /* Datentraegerspeicherung materialspezifisch */
#define REG_DISK_SETUP 0x00c0 /* Einrichtinformation */
#define REG_DISK_ROB   0x2000 /* Roboter-Register */
#define REG_DISK_FOT   0x2040 /* FOT-Register (frei konf. Seiten) */
#define REG_DISK_ABGL  0x2080 /* Maschinenabgleich-Register */
#define REG_DISK_PG    0x20c0 /* Prozessgraphik-Register */
#define REG_DISK_CORE  0x4000 /* Kernzug-Register, CORE */

/* ---- Typgruppe RWI: Lese-/Schreib-Zusatzinformation */
/* Lesen: DIR == REG_RD */
#define REG_RD_FAST    0x0000 /* wird mit schnellen Istwerten geholt */
#define REG_RD_INJ     0x0100 /* wird mit Spritzistwerten geholt */
#define REG_RD_SLOW    0x0200 /* wird mit langsamen Istwerten geholt */
#define REG_RD_SPEC    0x0300 /* Sonderdaten ausserhalb der Zyklen */
/* Schreiben: DIR == REG_WR */
#define REG_WR_NORMAL  0x0000 /* Nichts ist unmoeglich - RECOLA ! */
#define REG_WR_DOWN    0x0100 /* Sollwert, der bei Download gesendet wird */

/* ---- Typgruppe DIR: Uebertragungsrichtung */
#define REG_WR         0x0000 /* Nichts ist unmoeglich - RECOLA ! */
#define REG_RD         0x0400 /* Kann nicht geschrieben werden */

/* ---- Typgruppe BG:  Vorder-/Hintergrundbehandlung */
#define REG_FGBG       0x0000 /* Reg ist in Vorder- und Hintergrund gleich */
#define REG_BG         0x0800 /* Reg wird fuer Hintergrund separat behandelt*/

/* ---- Typgruppe TRF: Uebertragungsart zur ISCOS */
#define REG_NOTELEGR   0x0000 /* Normal */
#define REG_TELEGR     0x1000 /* Telegramm */

/* ---- Typgruppe TAB: Spezielle Tabellenbehandlung ueber Filterfunktion */
#define REG_NOSPECTAB  0x0000 /* Normal */
#define REG_SPECTAB    0x8000 /* Spezielle Tabellenbehandlung */


/*********************************************************************
X  TYPDEFINITIONEN FUER IQT-REGISTERTABELLEN
*********************************************************************/
typedef int    INT_N [];
typedef long   LONG_N [];


/*********************************************************************
X  KODIERUNG DES KONTROLLWORTS VON 'RegAddr'
*********************************************************************/
/* ID_TYPE */
#define REG_ID        0x000
#define ISCOS_ADDRESS 0x001
#define TABLE_INDEX   0x002

/* STORAGE_TYPE */
#define PHYSICAL      0x000
#define ELECTRIC      0x004

/* REG_TYPE */
#define ISCOSREG      0x000
#define IQTREG        0x010
#define ISCOSBIT      0x020
#define IQTBIT        0x030

#define ID_TYPE(Ctrl)      (Ctrl&0x0003)
#define STORAGE_TYPE(Ctrl) (Ctrl&0x000C)
#define REG_TYPE(Ctrl)     (Ctrl&0x00F0)


/*********************************************************************
X  PARAMETZER FUER FUNKTION 'RegBlkRdWrt'
*********************************************************************/
#define RD_FAST            0
#define RD_INJ             1
#define RD_SLOW            2
#define WRT_DOWN           3

/*********************************************************************
X  FEHLERCODES
*********************************************************************/
#define REG_ERR_NOT_FOUND    1         /* Register-ID nicht gefunden */
#define REG_ERR_BAD_PARAM    2         /* Fehlerhafte Parameter (Ctrl) */
#define REG_ERR_INDEX_RANGE  3         /* Indexwert zu gross */
#define REG_ERR_DATACOM      4         /* Fehler bei ISCOS-Kommunikation */
#define REG_ERR_TIMEOUT      5         /* Timeout-Fehler */
#define REG_ERR_WRITE             6                     /* Register Schreiben nicht erlaubt */
#define REG_ERR_READ                      7                     /* Register Lesen nicht erlaubt */
#define RECOLA_STOP         99         /* nicht schoen, aber bei
                                        * Filterfunktionen noetig */

/*********************************************************************
X  BEREICHSEINTEILUNG DER ISCOS-REGISTER
*********************************************************************/

#define START_ISCOS_BITS      0        /* ISCOS-Bits gehen ab 0 los */
#define START_ISCOS_BITS_KERN 1500     /* ISCOS-Kern-Bits gehen ab 1500 los */
#define START_IQT_BITS        2000     /* IQT-Bits gehen ab 2000 los */
#define START_ISCOS_REGS      3000     /* ISCOS-Register gehen ab 3000 los */
#define START_ISCOS_REGS_KERN 15000    /* ISCOS-Kern-Reg. gehen ab 15000 los */
#define START_REGLER_REGS     19000    /* Regler-Register gehen ab 19800 los */
#define START_IQT_REGS        20000    /* IQT-Register gehen ab 20000 los */
#define START_IQT_REGS_KERN   30000    /* IQT-Kern-Regs gehen ab 30000 los */

/* Die folgende Konstanten setzen die Grenzen der Registernummern fuer die
   einzelnen Registertypen fest. Die Registernummer eines Typs muss kleiner
   als ihr REGMAX und grosser oder gleich dem naechstunteren REGMAX sein. */
#define REGMAX_ISCOS_BIT      2000
#define REGMAX_IQT_BIT        3000
#define REGMAX_ISCOS_REG     19000
#define REGSTART_CYLHEAT_REG 19000
#define REGMAX_CYLHEAT_REG   19100
#define REGMAX_TOOLHEAT_REG  19200
#define REGMAX_TEMPHEAT_REG  19300 
#define REGMAX_OILHEAT_REG   19400
#define REGMAX_GENHEAT_REG   19500
#define REGMAX_RESHEAT_REG   19600
#define REGMAX_HEAT_REG      20000
#define REGMAX_IQT_REG       32000

#define IS_HEATREG(id) ((id)>=REGSTART_CYLHEAT_REG && (id)<REGMAX_HEAT_REG)

/*********************************************************************
X  FEHLERCODES BEI INITIALISIERUNG
*********************************************************************/
#define REG_ERR_INIT_REGS 0x0100
#define REG_ERR_INIT_TLGS 0x0200
#define REG_ERR_INIT_COM  0x0300

#define REG_ERR_ALLOC_DRAM  0x01   
#define REG_ERR_ALLOC_BBRAM 0x02
                         
#define REG_ERR_NOT_SORTED  0x01    /* Tabelle nicht aufsteigend sortiert */
#define REG_ERR_NO_ENDMARK  0x02    /* Keine Endekennung erkannt */
#define REG_TAB_ISCREG      0x10    /* Tabelle ist Iscos-Registertabelle */
#define REG_TAB_ISCBIT      0x20    /* Tabelle ist Iscos-Bittabelle */
#define REG_TAB_IQTREG      0x30    /* Tabelle iqt Iqt-Registertabelle */
#define REG_TAB_KISCREG     0x40    /* Tabelle ist Iscos-Registertabelle */
#define REG_TAB_KISCBIT     0x50    /* Tabelle ist Iscos-Bittabelle */
#define REG_TAB_KIQTREG     0x60    /* Tabelle iqt Iqt-Registertabelle */
#define REG_ERR_ISCREG_NOT_SORTED   ( REG_TAB_ISCREG | REG_ERR_NOT_SORTED )
#define REG_ERR_ISCREG_NO_ENDMARK   ( REG_TAB_ISCREG | REG_ERR_NO_ENDMARK )
#define REG_ERR_ISCBIT_NOT_SORTED   ( REG_TAB_ISCBIT | REG_ERR_NOT_SORTED )
#define REG_ERR_ISCBIT_NO_ENDMARK   ( REG_TAB_ISCBIT | REG_ERR_NO_ENDMARK )
#define REG_ERR_IQTREG_NOT_SORTED   ( REG_TAB_IQTREG | REG_ERR_NOT_SORTED )
#define REG_ERR_IQTREG_NO_ENDMARK   ( REG_TAB_IQTREG | REG_ERR_NO_ENDMARK )
#define REG_ERR_SEMINIT     0xff    /* Fehler bei Semaphoreninitialisierung */

/* Funktionen von IQTREGIM.C */
GLOBAL int RegInit( int ctrl );
GLOBAL int RegRead( UWORD ctrl, UWORD id, long* val, ... );
GLOBAL int RegWrite( UWORD ctrl, UWORD id, long val, ... );
GLOBAL int RegType( UWORD ctrl, UWORD id, ... );
GLOBAL int BlockBit( UWORD ctrl, UWORD id, ... );
GLOBAL UWORD RegId( UWORD ctrl, UWORD id, ... );
GLOBAL void RegProtect( void );   
GLOBAL void RegUnprotect( void );
GLOBAL void * RegAddr( UWORD ctrl, UWORD id, BYTE isc_nr );

/* Funktionen von REGWORK.C */
GLOBAL int RWrk_Init( BOOL init_bbram );
GLOBAL int RegBlkRdWrt( int from );
GLOBAL int RegSetBuffer( void* tab_ptr );
GLOBAL int RegDownload( int dl_type );
GLOBAL int IncReg( UWORD id, UWORD min, UWORD max );
GLOBAL int RegReadInt( UWORD id );

#endif /* _register */

