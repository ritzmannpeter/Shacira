/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     IFK.H
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
*     13-09-96 -PR-    Komponente Baudrate in INTF_KONF_TYPE auf
*                      UWORD geaendert.
*     13.06.97 -PR-    Im Zuge der Portierung auf 32-Bit int-Typen in 
*                      den Konfigurationstrukturen auf short umgestellt.
*     08.11.00 -TSchw- IFK_CARD und IFK_MAX_PPCCOM eingefuegt (siehe MEMCARD).
*     19.03.01 -TSchw- IFK_EM17 eingefuegt (siehe EM17).
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

#ifndef _ifk
#define _ifk

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqtdev.h>
#include <ifkconst.h>
/*.EI.***********************************************************************/

/*********************************************************************
*  TYPEN   
*********************************************************************/

/* Schnittstellen-Beschreibung */
typedef struct {
   UWORD     Baudrate;         /* Uebertragungsgeschwindigkeit */
   short    Stopbits;         /* Anzahl Stopbits */
   short    Databits;         /* Anzahl Datenbits */
   short    Parity;           /* Paritaet */
   short    ShowMode;         /* Anzeigemodus */
   short    DevMask;          /* Erlaubte Geraete an Schnittstelle */
   } INTF_KONF_TYPE;

/* Zuordnung der Geraete zu Schnittstellen */
typedef struct {
   short    IntfIndex;        /* Index in Interfacetabelle oder -1 */
   short    ChangeMode;       /* Aenderungsmodus */
   } DEV_KONF_TYPE;

/*********************************************************************
*  TABELLEN
*********************************************************************/

/* Anzahl der Tabellen-Eintraege */
#define MAX_DEV_KONF    6        /* Anzahl Geraete + 1 */

/* Alle Geraete (Parameter DevNr) */
                                 /* Wird nicht mehr benutzt */
#define  IFK_TERMINAL      1     /* Wird jetzt als Terminalanschluss benutzt
                                  */
#define  IFK_KBD           2
#define  IFK_PRN           3
#define  IFK_HOST          4
#define  IFK_PPCCOM        5 
#define  IFK_ISCOS_1       5
#define  IFK_ISCOS_2       6
#define  IFK_ISCOS_3       7
#define  IFK_ISCOS_4       8
#define  IFK_MEASURE       9
#define  IFK_ROBOT        10
#define  IFK_MAX_PPCCOM   11  /* MEMCARD */
#define  IFK_CARD         11  /* MEMCARD */
#define  IFK_EM17         12


#define  IFK_BOOT          0
#define  IFK_NO_BOOT       1


GLOBAL int  IFK_Init(BOOL init_bbram, int init_type);
GLOBAL IQT_HANDLE IFK_GetComHandle( int DevNr );
GLOBAL UWORD IFK_DarkObj( UWORD Index );
GLOBAL UWORD IFK_DarkCom( UWORD Index );
GLOBAL UWORD IFK_DarkDev( UWORD Index );
GLOBAL UWORD IFK_PlausCom( UWORD RegNr );
GLOBAL UWORD IFK_PlausDev( UWORD Index );
GLOBAL UWORD IFK_User2( UWORD ParamInd );
GLOBAL UWORD IFK_InitShow( UWORD Dummy );
GLOBAL UWORD IFK_SoftSetAll( UWORD cal );
GLOBAL int IFK_GetParam( int DevNr, UWORD Param );

#endif   /* ifndef _ifk */
