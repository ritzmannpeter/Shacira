/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     IFKCONST.H
*
*  BESCHREIBUNG:
*     Diese Datei enthaelt Interfacekonstanten fuer das Kundenprom.
*     
*
*  UMGEBUNG:
*     ZIELRECHNER:           IQT-450
*     ENTWICKLUNGSRECHNER:   PC-AT/QNX v3.15
*     UEBERSETZER:           c86 v3.3
*     OPTIONEN:              ...
*
*  VERSION:
*     VERSION:    4.0                       DATUM:   01.04.92
*     AUTOR(EN):  -UP-   U. Pfrengle        TELEFON: (0761) 42257
*     AUTOR(EN):  -SF-   S. Fleig           TELEFON: (0761) 42257
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     08.08.90 -UP-    Ausgelagert von IFK.H, da fuer KPROM benoetigt
*     01.04.92 -SF-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*
*
*  BEMERKUNGEN:
*     Die Datei darf nur #define - Konstrukte enthalten, da sie auch vom
*     CCC verwendet wird.
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

#ifndef _ifkconst
#define _ifkconst


/*********************************************************************
*  KONSTANTEN
*********************************************************************/

/* Anzahl Bits pro Zeichen */
#define  IFK_CHAR_5        5
#define  IFK_CHAR_6        6
#define  IFK_CHAR_7        7
#define  IFK_CHAR_8        8

/* Anzahl Stopbits */
#define  IFK_STOP_1        1
#define  IFK_STOP_2        2
#define  IFK_STOP_1_5      3

/* Parity */
#define  IFK_PARITY_NONE   0
#define  IFK_PARITY_ODD    1
#define  IFK_PARITY_EVEN   2

/* Anzeigemodi */
#define  IFK_SHOW          0
#define  IFK_HIDDEN        1

/* Fuer Parameter DevMask */
#define  IFK_USE_ISCOS        0x8000
#define  IFK_USE_KBD          0x4000
#define  IFK_USE_PRN          0x2000
#define  IFK_USE_HOST         0x1000
#define  IFK_USE_ALL          0xffff
#define  IFK_USE_NOT_KBD      IFK_USE_ISCOS | IFK_USE_PRN | IFK_USE_HOST
#define  IFK_USE_NONE         0x0000

/* Alle Schnittstellen */
#define  IFK_UNUSED       -1

#define  IFK_X1            0
#define  IFK_X2            1
#define  IFK_X3            2
#define  IFK_X4            3
#define  IFK_X7            4

/* Aenderungsmodi */
#define  IFK_FIX           0
#define  IFK_CHG_INIT      1
#define  IFK_CHG           2

#endif /* ifdef _ifkconst */