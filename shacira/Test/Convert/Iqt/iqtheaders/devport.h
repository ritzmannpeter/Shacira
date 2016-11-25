/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     xxxxxxxxx
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
*     07.03.00 -TSchw- PORT_KEY_SIMULATED eingefuegt
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

/*********************************************************************
*
*  *** HISTORY ***
*  05.12.90 -TSchw-  Implementierung
*
*********************************************************************/

#ifndef _devport
#define _devport


/*********************************************************************
*  KBD-Treiber: KONSTANTEN UND ALLGEMEINE MAKROS
*********************************************************************/

#define PORT_KBD_LAMP_ON         1
#define PORT_KBD_LAMP_OFF        2
#define PORT_VIDEO_POWER_ON      3
#define PORT_VIDEO_POWER_OFF     4
#define PORT_KEY                 5
#define PORT_ID_FREEMEM          6
#define PORT_KEY_SIMULATED       7

#endif