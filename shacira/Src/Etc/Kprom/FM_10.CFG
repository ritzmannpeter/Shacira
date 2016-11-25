/************************************************************************
*                                                                       *
* MODUL-NAME: KPROM.CFG (m<maschnr>.cfg)                                *
*                                                                       *
* Auf Version 55 umgestellt:                                            *
* - InjUnits nach oben geholt, ResUnits eingebaut                       *
* - Versionsnummer von 00.m4.00.01 auf 00.m4.10.55 erhoeht              *
* - Sonderprogrammnummer SpecKprom eingefuegt                           *
* - FreeText1 ist jetzt wieder frei, auf Seite 20 werden die ersten 2   *
*   oder 3 Zeichen von MashineType angezeigt                            *
* - OptionTab ganz neu aufgeteilt                                       *
* - InjSpeedMax, InjSpeedConv eingefuegt                                *
* - AggParamTab und SnParamTab auf 3 Dimension erweitert                *
* - Kundenpromfehlermeldungen eingebaut                                 *
* - 10-Stufen-Prom fuer FM erschaffen!                                  *
*   und Parameter fuer Telegramm-DMA-Adressen eingefuehrt               *
*                                                                       *
************************************************************************/

#include "kprom.typ"
#include "ifkconst.h"
#include <comptime.h>

InjUnits  =     1;      /* Anzahl der Spritzeinheiten                   */
ResUnits  =     1;      /* Anzahl Reserveaggregate zum Austauschen,Def.1*/
InjCycles =    10;      /* Anzahl der Spritzzyklen (6 oder 20)          */
TempCards =     1;      /* Anzahl der Temperaturkarten                  */


VersKprom       = "00.04.10.55";/* Kundenprom-Versionsnummer            */
SpecKprom       = "003E.3";     /* Kundenprom-Sonderprogrammnummer, fuer  */
                                /* Standardprogramme genau 6 Leerzeichen! */
TimeKprom       = COMPILE_TIME;
OrderNr         = "Auftrags-Nummer 18690027500";
MashineNr       = "Maschinen-Nummer  266291"; /*Stets 6-stellig, ggf. fuehr.0*/
MashineType     = "FXR75";
CloseForce      = "max. Schliesskraft = 75t";
Language1       = "      D";
Language2       = "     GB";
Language3       = "      F";
IqtVersion      = "5.5";
/*                          1         2                         */
/*                 12345678901234567890123456789                */
Customer        = "KFM Test FXR";
FreeText1       = "Alle Optionen gesetzt";
FreeText2       = "";
FreeText3       = "";
FreeText4       = "";
ScreenSaveT     = 10; /* nach 10 min Bildschirm dunkel schalten */

OptionTab  = {
      /* -------  Heizung Aggregat 1 -------*/
   1, /*  0: mit Einzugszone (Trichterstuecktemp.) (Seite 30.0,Zone 0)  */
   1, /*  1: mit Massetemperatur (Seite 30.0,Zone 21)                   */
   1, /*  2: mit Schneckentemeperierung (Seite 30.0 ,Zone 20)           */
   1, /*  3: mit Motorzeitkonstante (Seite 39.1 Zeile 18)               */
   1, /*  4: mit Schalthyst. und Arbeitspunkt (Seite 39.1 Zeilen 14,15) */
   0, /*  5:     Reserve                                                */
   0, /*  6:     Reserve                                                */
   0, /*  7:     Reserve                                                */
   0, /*  8:     Reserve                                                */
   0, /*  9:     Reserve                                                */

      /* -------  Heizung Aggregat 2 -------*/
   0, /* 10: mit Einzugszone (Trichterstuecktemp.) Aggregat 2           */
   0, /* 11: mit Massetemperatur  Aggregat 2                            */
   0, /* 12: mit Schneckentemperierung Aggregat 2                       */
   0, /* 13:     Reserve                                                */
   0, /* 14:     Reserve                                                */
   0, /* 15:     Reserve                                                */
   0, /* 16:     Reserve                                                */
   0, /* 17:     Reserve                                                */
   0, /* 18:     Reserve                                                */
   0, /* 19:     Reserve                                                */

      /* ------- Kernzug  -----------------*/
   1, /* 20: mit Proprotionalkernzug (S.61.0 bis S.62.1 je Z.17 u.18)   */
   1, /* 21: mit Ausschrauben (S.68 ,Z.2 bis 11) NICHT mit E-Motor!     */
   1, /* 22: mit Ausschrauben mit Prop.-Ventile (S.68 ,Z.14 bis 19)     */
   0, /* 23:     Reserve                                                */
   0, /* 24:     Reserve                                                */
   0, /* 25:     Reserve                                                */
   0, /* 26:     Reserve                                                */
   0, /* 27:     Reserve                                                */
   0, /* 28:     Reserve                                                */
   0, /* 29:     Reserve                                                */

      /* -------- ROBOT   ------------------*/
   0, /* 30: mit CNC - Robot       ACHTUNG: OPTIONEN SCHLIESSEN SICH    */
   0, /* 31: mit Handlinggeraet    GEGENSEITIG AUS !!!!!                */
   0, /* 32:     Reserve                                                */
   0, /* 33:     Reserve                                                */
   0, /* 34:     Reserve                                                */
   0, /* 35:     Reserve                                                */
   0, /* 36:     Reserve                                                */
   0, /* 37:     Reserve                                                */
   0, /* 38:     Reserve                                                */
   0, /* 39:     Reserve                                                */

      /* -------- Auswerfer  ---------------*/
   1, /* 40: mit Ruhelage Ueberwachung ausschalten (Seite 52.0,Zeile 16)*/
   1, /* 41: mit Asw. relat. Nullpkt (Seite 52.0 ,Zeile 4 FXR STANDARD) */
   1, /* 42: mit Auswerferdruck Propventil (Seite 52.0 ,Zeile 12)       */
   1, /* 43: mit Schnellkuppl. f. Asw.-Ruhelage Hasco (Bit EZHASC)      */
   1, /* 44: mit Zusatzauswerfer (Seite 53)                             */
   0, /* 45: mit Auswerferkraft 'an Maschine einstellbar'(nur FM)       */
   0, /* 46:     Reserve                                                */
   0, /* 47:     Reserve                                                */
   0, /* 48:     Reserve                                                */
   0, /* 49:     Reserve                                                */

      /* -------- Duesenbewegung  ---------------*/
   0, /* 50: mit Duesenanpressdruck Pg49 Line13 (ACHTUNG nur FXA !!!)   */
   0, /* 51: mit Duesenanpressdruck  Aggregat 2                         */
   1, /* 52: mit Duesengeschw. (S.49 Line11+12; bei FXR+FM auch Line13) */
   0, /* 53: mit Duesengeschwindigkeit Aggregat 2                       */
   1, /* 54: mit Schneckenwechsel (Seite 49 Zeile 14)  STANDARD FXR     */
   0, /* 55:     Reserve                                                */
   0, /* 56:     Reserve                                                */
   0, /* 57:     Reserve                                                */
   0, /* 58:     Reserve                                                */
   0, /* 59:     Reserve                                                */

      /* -------- Werkzeugbewegung ---------------*/
   1, /* 60: mit Fss-Wiederholung (Seite 50.0  Zeile 17)                */
   0, /* 61:     Reserve                                                */
   0, /* 62:     Reserve                                                */
   0, /* 63:     Reserve                                                */
   0, /* 64:     Reserve                                                */

      /* -------- Betriebsdaten -------------------*/
   1, /* 65: mit Werkzeugnummer-Istwert (Seite 21.0  Zeile 8)           */
   0, /* 66:     Reserve                                                */
   0, /* 67:     Reserve                                                */
   0, /* 68:     Reserve                                                */
   0, /* 69:     Reserve                                                */

      /* -------- Werkzeug Schnellspannen ---------*/
   1, /* 70: mit Schnellspannvorrichtung (Seite 56)                     */
   0, /* 71:     Reserve                                                */
   0, /* 72:     Reserve                                                */
   0, /* 73:     Reserve                                                */
   0, /* 74:     Reserve                                                */

      /* -------- Schliesszylinder ---------------*/
   1, /* 75: mit Zentralschmierungsperiode (Seite 15.0  Zeile 7)        */
   0, /* 76:     Reserve                                                */
   0, /* 77:     Reserve                                                */
   0, /* 78:     Reserve                                                */
   0, /* 79:     Reserve                                                */

      /* -------- Graphic -------------------------*/
   1, /* 80: mit Prozessgraphik (Seite 45.0 bis Seite 47.1)             */
   1, /* 81: mit Statistischer Prozesskontrolle (Seite 90 bis Seite 94) */
   0, /* 82:     Reserve                                                */
   0, /* 83:     Reserve                                                */
   0, /* 84:     Reserve                                                */

      /* -------- Praegen -------------------------*/
   1, /* 85: mit Atmen und Praegen (Seite 54.1 Zeilen 2 bis 10)         */
   1, /* 86: mit gestaffeltem Schliessdruckaufbau (S.54.1 Line 11 b.19) */
   0, /* 87:     Reserve                                                */
   0, /* 88:     Reserve                                                */
   0, /* 89:     Reserve                                                */

      /* -------- Leitrechner ---------------------*/
   1, /* 90: mit Leitrechner-Anschluss (Seite 10  Zeile 11 und 15)      */
   0, /* 91:     Reserve                                                */
   0, /* 92:     Reserve                                                */
   0, /* 93:     Reserve                                                */
   0, /* 94:     Reserve                                                */

      /* -------- Sonderausstattung ---------------*/
   1, /* 95: mit Floppy-Laufwerk                                        */
   1, /* 96: mit Wochentagsschaltuhr   (Seite 14)                       */
   0, /* 97:     Reserve                                                */
   0, /* 98:     Reserve                                                */
   0  /* 99:     Reserve                                                */
   };


/* Umrechungsfaktor fuer Einspritzgeschwindigkeit S.41/42         */
/*    8 - Geschwindigkeit bis  500 mm/sec (Default)               */
/*    4 - Geschwindigkeit bis 1000 mm/sec                         */
/*    Aggregat: 1    2    3                                       */
InjSpeedConv = {8};  

/* Maximale Eingabe fuer Einpritzgeschwindigkeit S.41/42          */
/*    Aggregat: 1    2    3                                       */
InjSpeedMax  = {500}; 

ToolParamTab = {
   75,      /* Param 2 machine type fx */
   2380,    /* Param 3 Schliesflache x10 (mm)2 */
   75,      /* Param 4 Schlieskraft bei 160 bar */
   7500,    /* Param 5 Plattenabstand */
   4000,    /* Param 6 Formeinbauhohe */
   2380,    /* Param 7 Schlieskraft fur Sollwert */
   1500,    /* Param 8 Auswerferweg */
   34,      /* Param 9 Auswerferkraft */
   2600,    /* Param 10 Druckbolzen */
   0,       /* Param 11 Reserve */
   0,       /* Param 12 Reserve */
   100,     /* Param 13 Korrekturfaktor Druckubersetzer */
   0,       /* Param 14 Plattenverstaerkung (deldik)  */
   22       /* Param 15 minimaler Schliesdruck */
   };      

/* Aggregatparametertabelle:                                            */
/* AggParamTab [Reseveaggregat] [Aggregat] [Parameter]                  */
/* Bei Einfarbenmaschinen wird bloss eine Dimension benoetigt. Die      */
/* Tabelle besteht dann aus einer Zeile mit den Parametern 16 bis 24.   */
/* Die Variable InjUnits am Anfang der Datei ist dann 1.                */
/* Bei Zwei- bzw. Dreifarbenmaschinen, ist diese Zeile zwei bzw. drei   */
/* mal vorhanden fuer zwei bzw. drei Aggregate, InjUnits ist 2 oder 3.  */
/* Nur in seltenen Faellen kommt es vor, dass mehrere Reserveaggregate  */
/* zum Wechseln mittgegeben werden. In diesem Fall werden die ganzen    */
/* Tabelleneintraege verdoppelt, verdreifacht etc., die Variable        */
/* ResUnits ist groesser als 1.                                         */
/* Parameter 16 Aggregatweg                                             */
/* Parameter 17 Plastifizierweg                                         */
/* Parameter 18 Kolbenflache                                            */
/* Parameter 19 Drehzahl                                                */
/* Parameter 20 Zahnezahl (klein)                                       */
/* Parameter 21 Zahnezahl (mittel)                                      */
/* Parameter 22 Zahnezahl (gross)                                       */
/* Parameter 23 Aggregattyp (FM=1, FX=2)                                */
/* Parameter 24 Aggregatgroesse                                         */
/* Parameter 24_1 Max. Eingabe fuer Einpritzgeschwindigkeit S.41/42     */
/* Parameter 24_2 Umrechungsfaktor fuer Einspritzgeschwindigkeit        */
/*                8 - Geschwindigkeit bis  500 mm/sec (Default)         */
/*                4 - Geschwindigkeit bis 1000 mm/sec                   */

/*             Par16 Par17 Par18 Par19 Par20 Par21 Par22 Par23 Par24  */
AggParamTab = {2500, 1200,  950,  430,    1,    1,    1,    2,   75};


/*********************************************************************
*  SnParamTab1 - kleine    Schneckengroesse
*  SnParamTab2 - mittlere  Schneckengroesse
*  SnParamTab3 - grosse     Schneckengroesse
*********************************************************************/

/* Schneckenparametertabellen                                           */
/* SnParamTabx [Reseveaggregat] [Aggregat] [Parameter]                  */
/* Der Kommentar der Aggregatparametertabelle gilt auch hier            */
/* Parameter 25 Schneckendurchmesser                                    */
/* Parameter 26 Max Spritzdruck                                         */
/* Parameter 27 Ausfuhrung                                              */
/* Parameter 28 Anzahl Heizzonen                                        */
/* Parameter 29 Heizungsparametersatz                                   */

/*              Par25  Par16  Par27  Par28  Par29                       */
SnParamTab1 = {    30,   170,     1,     5, 0x0122}; /* ag250-80mm-thermopl. */

SnParamTab2 = {    40,   170,     1,     5, 0x0122}; /* ag250-70mm-thermopl. */

SnParamTab3 = {    35,   170,     1,     5, 0x0122}; /* ag250-85mm-thermopl. */

/*----------------------------------------------------------------------*
 | Groesse und Password des Crashlogbuchs                               |
 *----------------------------------------------------------------------*/
CLB_SollBufSize = 50;
CLB_IstBufSize  = 3;    /* Anzahl zu merkender Spritzzyklen */
CLB_ErrBufSize  = 25;   /* Anzahl zu merkender Fehlermeldungen */
CLB_Password    = "MERDE";


/* Interface-Konfiguration */
IntfCount = 4;

IntfKonf = {
   {  9600,                /* X1 */
      IFK_STOP_1,
      IFK_CHAR_8,
      IFK_PARITY_NONE,
      IFK_SHOW,
      IFK_USE_NOT_KBD } ,
   {  9600,                /* X2 */
      IFK_STOP_1,
      IFK_CHAR_8,
      IFK_PARITY_NONE,
      IFK_SHOW,
      IFK_USE_NOT_KBD } ,
   {  9600,                /* X3 */
      IFK_STOP_1,
      IFK_CHAR_8,
      IFK_PARITY_NONE,
      IFK_SHOW,
      IFK_USE_NOT_KBD } ,
   {  9600,                /* X4 */
      IFK_STOP_1,
      IFK_CHAR_8,
      IFK_PARITY_NONE,
      IFK_SHOW,
      IFK_USE_NOT_KBD }
};

DevCount = 5;

DevKonf = {
   {  IFK_UNUSED,                      /* muss frei sein */
      IFK_CHG } ,                      /* muss stets CHG sein */
   {  IFK_X4,                          /* Iscos */
      IFK_CHG } ,
   {  IFK_UNUSED,                      /* Tastatur */
      IFK_CHG_INIT } ,
   {  IFK_UNUSED,                      /* Drucker */
      IFK_CHG } ,
   {  IFK_X3,                          /* Host */
      IFK_CHG }
};


/*----------------------------------------------------------------------*
 | Regler - Zuordnungstabellen                                          |
 *----------------------------------------------------------------------*/
InjHeatZones = 21;              /* absolute Tabellenlaenge              */
InjHeatTab = {  /* Tabelle der Reglernummern auf Seite 30               */
   0, 3,        /* Option Einzug, ZylinderZone 0, Regler 3              */
   0, 5,        /* ZylinderZone 1, Regler 5                             */
   0, 6,        /* ZylinderZone 2, Regler 6 od. Reg.4, wenn letzte Zone */
   0, 7,        /* ZylinderZone 3, Regler 7 od. Reg.4, wenn letzte Zone */
   0, 8,        /* ZylinderZone 4, Regler 8 od. Reg.4, wenn letzte Zone */
   0, 4,        /* ZylinderZone 5, Regler 9 od. Reg.4, wenn letzte Zone */      
   0, 0,        /* ZylinderZone 6, Regler 4 letzte Zone immer Reg.4 !!! */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 0,        /* ??? => dummy                                         */
   0, 2,        /* Option Schneckentemperieung Zone20, Regler 2         */
   0, 11};      /* Option Massetemperatur Zone 21, Regler 11            */
   
Stations  =     1;      /* Anzahl der Stationen                         */
HeatZones =     7;      /* max. moegliche Groesse der ToolHeatTab       */
TempTools =     3;      /* max. moegliche Groesse der TempHeatTab       */
ResHeatZones =  0;      /* Anzahl der Zonen der Reserveheizung          */

ToolHeatTab = { /* Tabelle der Reglernummern fuer Werkzeugheizungen     */
   0, 0,        /* Offset 0 als Platzhalter !!!                         */
   0, 1,        /* Werkzeugzone 1, Regler 1                             */
   0, 0,        /* Werkzeugzone 2, Regler 2  ODER Option Schnecke       */
   0, 0,        /* Werkzeugzone 3, Regler 3  ODER Option Trichter       */
   0, 10,       /* Werkzeugzone 4, Regler 10                            */ 
   0, 0,           /* Werkzeugzone 5, Regler 11 ODER Option Masse               */
   0, 13,       /* Werkzeugzone 6, Regler 13                            */
   0, 14};      /* Werkzeugzone 7, Regler 14                            */
   
TempHeatTab = { /* Tabelle der Reglernummern fuer Temperiergeraete      */
   0, 0,        /* Offset 0 als Platzhalter !!!                         */
   0, 0,        /* Temperiergeraete, Zone 1, Regler 1 (3pkt. Regler)    */
   0, 0,        /* Temperiergeraete, Zone 2, Regler 2 (3pkt. Regler)    */
   0, 0};       /* Temperiergeraete, Zone 3, Regler 3 (3pkt. Regler)    */
                /* in ToolHeatTab UND TempHeatTab duerfen NIE die       */
                /* gleichen Reglernummern stehen!!!                     */
   
                /* v = Anzahl der Stationen                             */
                /* v = Anzahl der Heizzonen der Reserveheizgruppe       */
ResHeatTab = {0, 0};
   
OilHeat = 12;   /* Regler fuer Oelvorwaermtemperatur                    */

/*----------------------------------------------------------------------*
 | Regler - Tabellen                                                    |
 *----------------------------------------------------------------------*/
Regler = 14;    /* Anzahl der Regler aller Temperaturkarten             */
HeatRegs = 33;  /* Anzahl der Reglerparameter                           */
ReglerName =
"           \
Wkz.-Zone 1\
Schneckent.\
Einzug     \
Zyl.-Zone 5\
Zyl.-Zone 1\
Zyl.-Zone 2\
Zyl.-Zone 3\
Zyl.-Zone 4\
Re 9   frei\
Wkz.-Zone 4\
Massetemp. \
Re12   Oel \
Wkz.-Zone 6\
Wkz.-Zone 7" ;

/* HEIZUNGSPARAMETER                                                        */

ReglerParam = {
/* ---0---0---0---0---0------0----0----0-----0-----0---1---1---1----1----1----1-1---1-1-1-2--2--2--2--2-2-2-2-2-2-3-3-3 */
/* ---0---1---2---3---4------5----6----7-----8-----9---0---1---2----3----4----5-6---7-8-9-0--1--2--3--4-5-6-7-8-9-0-1-2 */
  {   0,  0,  0,  0,  0, 0,   0,   0,    0,    0,  0,  0,  0,   0,   0,   0,0,  0,0,0,0,21,22,23,24,0,0,0,0,0,0,0,0},
  {   0,200,100,200,100, 0,  45,  45, 1750, 1440,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100, 0,  45,  45, 1750, 1440,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,3,0,0,0,0,0},
  {   0,200,100,200,100, 0,  45,  45, 1750, 1440,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,3,0,0,0,0,0},
  {   0,200,100,200,100, 0,  54,  54,  950,  920,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,2,0,0,0,0,0},
  {   0,200,100,200,100, 0,  82,  82, 2550, 2480,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,2,0,0,0,0,0},
  {   0,200,100,200,100, 0,  75,  75, 2460, 2400,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,2,0,0,0,0,0},
  {   0,200,100,200,100, 0,  81,  81, 2460, 2400,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,2,0,0,0,0,0},
  {   0,200,100,200,100, 0,  82,  82, 2550, 2480,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,2,0,0,0,0,0},
  {   0,200,100,200,100, 0,  81,  81, 2460, 2400,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,2,0,0,0,0,0},
  {   0,200,100,200,100, 0,  75,  75, 1750, 1440,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100, 0,  45,  45, 1750, 1440,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,2,0,0,0,0,0},
  { 350,800,400,800,400, 0,  45,  45, 1750, 1440,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,1,2,0,0,0,0,0},
  {   0,  0,  0,  0,  0, 0,   0,   0,    0,    0,  0,  0,  0,   0,   0,   0,0,  0,0,0,0,21,22,23,24,0,0,1,0,0,0,0,0},
  {   0,  0,  0,  0,  0, 0,   0,   0,    0,    0,  0,  0,  0,   0,   0,   0,0,  0,0,0,0,21,22,23,24,0,0,1,0,0,0,0,0}
/* Eintraege fuer eine 2. Temperaturkarte,Vorbelegung als Werkzeugheizonen  
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,3,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,2,0,0,0,0,0},
  {   0,200,100,200,100,0x00f9,  30,  30, 1750, 1750,100,100,  0,   0,1000,1000,0,  0,0,0,0,21,22,23,24,0,0,2,0,0,0,0,0},
  {   0,  0,  0,  0,  0,0x00fa,   0,   0,    0,    0,  0,  0,  0,   0,   0,   0,0,  0,0,0,0,21,22,23,24,0,0,1,0,0,0,0,0},
  {   0,  0,  0,  0,  0,0x00fa,   0,   0,    0,    0,  0,  0,  0,   0,   0,   0,0,  0,0,0,0,21,22,23,24,0,0,1,0,0,0,0,0}
*/
  };
   /* letzte Zeile ist Dummy */

 MaxDMAAddr = 5;
 TlgDMAAddr = {0,
               /*WK1+IND*/ 0x36,
               0,
               0,
               0,
               0
               };


/*------------------------------------------------------------------*
 | Kundenpromdefinierte Fehlertexte                                 |
 *------------------------------------------------------------------*/

/* Sprache 1, Fehler 1 - 16, max. 44 Zeichen, bis hierher v */
Lan1Error1  = "KPROM-Fehler 1";
Lan1Error2  = "KPROM-Fehler 2";
Lan1Error3  = "KPROM-Fehler 3";
Lan1Error4  = "KPROM-Fehler 4";
Lan1Error5  = "KPROM-Fehler 5";
Lan1Error6  = "KPROM-Fehler 6";
Lan1Error7  = "KPROM-Fehler 7";
Lan1Error8  = "KPROM-Fehler 8";
Lan1Error9  = "KPROM-Fehler 9";
Lan1Error10 = "KPROM-Fehler 10";
Lan1Error11 = "KPROM-Fehler 11";
Lan1Error12 = "KPROM-Fehler 12";
Lan1Error13 = "KPROM-Fehler 13";
Lan1Error14 = "KPROM-Fehler 14";
Lan1Error15 = "KPROM-Fehler 15";
Lan1Error16 = "KPROM-Fehler 16";

/* Sprache 2, Fehler 1 - 16, max. 44 Zeichen, bis hierher v */
Lan2Error1  = "KPROM-Error 1";
Lan2Error2  = "KPROM-Error 2";
Lan2Error3  = "KPROM-Error 3";
Lan2Error4  = "KPROM-Error 4";
Lan2Error5  = "KPROM-Error 5";
Lan2Error6  = "KPROM-Error 6";
Lan2Error7  = "KPROM-Error 7";
Lan2Error8  = "KPROM-Error 8";
Lan2Error9  = "KPROM-Error 9";
Lan2Error10 = "KPROM-Error 10";
Lan2Error11 = "KPROM-Error 11";
Lan2Error12 = "KPROM-Error 12";
Lan2Error13 = "KPROM-Error 13";
Lan2Error14 = "KPROM-Error 14";
Lan2Error15 = "KPROM-Error 15";
Lan2Error16 = "KPROM-Error 16";

/* Sprache 3, Fehler 1 - 16, max. 44 Zeichen, bis hierher v */
Lan3Error1  = "KPROM-D{faut 1";
Lan3Error2  = "KPROM-D{faut 2";
Lan3Error3  = "KPROM-D{faut 3";
Lan3Error4  = "KPROM-D{faut 4";
Lan3Error5  = "KPROM-D{faut 5";
Lan3Error6  = "KPROM-D{faut 6";
Lan3Error7  = "KPROM-D{faut 7";
Lan3Error8  = "KPROM-D{faut 8";
Lan3Error9  = "KPROM-D{faut 9";
Lan3Error10 = "KPROM-D{faut 10";
Lan3Error11 = "KPROM-D{faut 11";
Lan3Error12 = "KPROM-D{faut 12";
Lan3Error13 = "KPROM-D{faut 13";
Lan3Error14 = "KPROM-D{faut 14";
Lan3Error15 = "KPROM-D{faut 15";
Lan3Error16 = "KPROM-D{faut 16";


