/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     DSGLOBAL.H - globale Variable der Datenstrukturen
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
*     VERSION:    4.0                       DATUM:   08.05.92
*     AUTOR(EN):  -PR-   P. Ritzmann        TELEFON: (0761) 42257
*
*  HISTORY:
*     08.05.92 -PR-    Portierung des IQT-350 auf IQT-450
*                      Einfuehrung des neuen Konzepts fuer Header-Dateien
*     04.03.96 -HAns-  Parameter fuer die Umrechnung der Datentraeger-Werte 
*                      auf bis zu 4 Farben erweitert.
*     08.11.96 -HAns-  Variable Iscos_CarType eingefuegt.
*     01.02.01 -HAns-  Parameter fuer die Umrechnung der Datentraeger-Werte 
*                      auf bis zu 6 Farben erweitert.
*     15.09.03 -HA-     ActLanguageIsUC eingefuegt.
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


#ifndef _dsglobal
#define _dsglobal

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
/*.EI.***********************************************************************/


/* Hier werden saemtliche innerhalb der Datenstruktur bekannten globalen     */
/* Variable aus dem Modul DSGLOBAL extern definiert.                         */
extern int  far AusSoft;             /* Variable fuer AuswerferNullpunktabgleich */
extern int  far ReadHeatErrAnz;      /* Variable fuer Heizungsfehlermeldungen    */
extern BYTE far ToolTolActive;       /* Fuer Dunkeltastung der Tol. auf S. 33, 34*/
extern long far WkzIStuf;            /* Werkzeuginnendruckabhaengige Umschaltung */
extern BYTE far WkzIFlag;            /* TRUE:Zwangsfuehrung nach Setzen der Stufe*/
extern int  far BolzSoft;            /* Variable fuer Druckbolzenabgleich        */

/* Parameter fuer die Umrechnung der Datentraeger-Werte */
extern int      far ProgNr;              /* Sonderprogramm-Nr */
extern int      far MouldOpWay;          /* Werkzeugoeffnungsweg */
extern int      far DiskMaxAgg;          /* Anzahl Aggregate auf Disk */
extern BYTE     far OldDiskFlag;         /* alter Datentraeger lesen */
extern BYTE     far DiskVersStruct;      /* Versionsnummer Datenstruktur auf Disk */


/* Parameter fuer die Umrechnung der Datentraeger-Werte, 1. Aggregat */
extern BYTE     far HeatZoneCount;       /* Anzahl Heizzonen */
extern long     far PresConst;           /* Umrechnungskonstante fuer Druck */
extern long     far WaySpeedConst;       /* Umrechnungskonstante fuer Weg/Geschw. */
extern int      far ScrewSuckBack;       /* Auswahl Schneckenrueckzug */
extern int      far PlastWay;            /* Plastifizierweg */
extern int      far MouldInPres;         /* Werkzeuginnendruckstufe */
extern int      far MaxInjPres;          /* Maximaler Einspritzdruck */

/* Parameter fuer die Umrechnung der Datentraeger-Werte, 2. Aggregat */
extern BYTE     far HeatZoneCount2;      /* Anzahl Heizzonen */
extern long     far PresConst2;          /* Umrechnungskonstante fuer Druck */
extern long     far WaySpeedConst2;      /* Umrechnungskonstante fuer Weg/Geschw. */
extern int      far ScrewSuckBack2;      /* Auswahl Schneckenrueckzug */
extern int      far PlastWay2;           /* Plastifizierweg */
extern int      far MouldInPres2;        /* Werkzeuginnendruckstufe */
extern int      far MaxInjPres2;         /* Maximaler Einspritzdruck */

/* Parameter fuer die Umrechnung der Datentraeger-Werte, 3. Aggregat */
extern BYTE     far HeatZoneCount3;      /* Anzahl Heizzonen */
extern long     far PresConst3;          /* Umrechnungskonstante fuer Druck */
extern long     far WaySpeedConst3;      /* Umrechnungskonstante fuer Weg/Geschw. */
extern int      far ScrewSuckBack3;      /* Auswahl Schneckenrueckzug */
extern int      far PlastWay3;           /* Plastifizierweg */
extern int      far MouldInPres3;        /* Werkzeuginnendruckstufe */
extern int      far MaxInjPres3;         /* Maximaler Einspritzdruck */

/* Parameter fuer die Umrechnung der Datentraeger-Werte, 4. Aggregat */
extern BYTE     far HeatZoneCount4;      /* Anzahl Heizzonen */
extern long     far PresConst4;          /* Umrechnungskonstante fuer Druck */
extern long     far WaySpeedConst4;      /* Umrechnungskonstante fuer Weg/Geschw. */
extern int      far ScrewSuckBack4;      /* Auswahl Schneckenrueckzug */
extern int      far PlastWay4;           /* Plastifizierweg */
extern int      far MouldInPres4;        /* Werkzeuginnendruckstufe */
extern int      far MaxInjPres4;         /* Maximaler Einspritzdruck */

/* Parameter fuer die Umrechnung der Datentraeger-Werte, 5. Aggregat */
extern BYTE     far HeatZoneCount5;      /* Anzahl Heizzonen */
extern long     far PresConst5;          /* Umrechnungskonstante fuer Druck */
extern long     far WaySpeedConst5;      /* Umrechnungskonstante fuer Weg/Geschw. */
extern int      far ScrewSuckBack5;      /* Auswahl Schneckenrueckzug */
extern int      far PlastWay5;           /* Plastifizierweg */
extern int      far MouldInPres5;        /* Werkzeuginnendruckstufe */
extern int      far MaxInjPres5;         /* Maximaler Einspritzdruck */

/* Parameter fuer die Umrechnung der Datentraeger-Werte, 6. Aggregat */
extern BYTE     far HeatZoneCount6;      /* Anzahl Heizzonen */
extern long     far PresConst6;          /* Umrechnungskonstante fuer Druck */
extern long     far WaySpeedConst6;      /* Umrechnungskonstante fuer Weg/Geschw. */
extern int      far ScrewSuckBack6;      /* Auswahl Schneckenrueckzug */
extern int      far PlastWay6;           /* Plastifizierweg */
extern int      far MouldInPres6;        /* Werkzeuginnendruckstufe */
extern int      far MaxInjPres6;         /* Maximaler Einspritzdruck */

extern BYTE far DiskReadActive;  /* TRUE:  Datentraeger wird gerade gelesen  */
                                 /* FALSE: Datentraeger wird nicht gelesen   */
                                 /* Damit koennen Filterfunktionen anders    */
                                 /* reagieren, wenn sie vom Datentraegermodul*/
                                 /* aus aufgerufen werden.                   */
extern BYTE far HeatOptActive;   

extern int  far Wkzcount;
extern int  far WkzSoft1;
extern int  far WkzSoft2;
extern BYTE far SetSSFAU4;
extern UWORD far StopCycTasks;

extern BYTE far Iscos_CarType;   /* Iscos-Datentraegertype                   */ 

extern UWORD far SESoft1;

extern UWORD far ActLanguageIsUC; /* TRUE  = Aktuelle Language ist VR angewaehlt */
                                 /* FALSE = Aktuelle Language ist keine VR Language angewaehlt */

#endif /* ifndef _dsglobal */