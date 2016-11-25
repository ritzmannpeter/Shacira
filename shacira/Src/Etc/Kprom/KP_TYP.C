/*********************************************************************
*                                                                    *
*  MODUL-NAME: KPROM.TYP                                             *
*                                                                    *
*  BESCHREIBUNG:                                                     *
*     Enthalt die Deklarationen der Paramter im Kundenprom.          *
*     Die hier beschriebenen Parameter dÅrfen bei einer              *
*     Konfiguration fÅr einen Kunden nicht verÑndert werden.         *
*     Die Daten fÅr das Kundenprom werden in KPROM.CFG beschrieben.  *
*                                                                    *
*  HISTORY:                                                          *
*     10.04.90    -JG-   Erstellt aus Kprom.c(125)                   *
*     27.07.90    -UP-  Angepasst an CCC                             *
*     24.09.90    -SF-  Kundenprom-Version eingebaut                 *
*     13.11.90  -TSchw- VersKprom als String ausgefuehrt             *
*     30.11.90    -JG-  OptionTab auf 48 Elemente erhoeht            *
*     15.04.91  -TSchw- ResUnits eingefuegt, AggParamTab und alle    *
*                       drei SnParamTabs von 1 auf 3 Dimensionen     *
*                       erweitert                                    *
*     06.06.91  -TSchw- InjSpeedMax, InjSpeedConv eingefuegt         *
*     07.06.91  -TSchw- Kundenpromdefinierte Fehlertexte eingefuegt  *
*     17.06.91  -TSchw- Sonderprogrammnummer SpecKprom eingefuegt    *
*     24.06.91  -TSchw- InjSpeedMax, InjSpeedConv ist Tabelle        *
*     25.06.91  -TSchw- OptionTab auf 120 erhoeht                    *
*     21.11.91  -PR-    Deklarationen fuer Parameter MaxDMAAddr und  *
*                       TlgDMAAddr eingefuehrt                       *
*                                                                    *
*  VERSION:                                                          *
*     VERSION:  1.0              AUTOR:       T. Schworer            *
*     DATUM:    27.06.89         TELEFON 2i:  0761/42257             *
*                                                                    *
*  UMGEBUNG:                                                         *
*     ZIELRECHNER:          Philips IQT-350                          *
*     PROGRAMMIERSPRACHE:   C (Intel ic86 4.0)                       *
*                                                                    *
*  BEMERKUNGEN:                                                      *
*                                                                    *
*********************************************************************/

#include <kprom.id>


/*********************************************************************
*  TYPVEREINBARUNGEN
*********************************************************************/

#define STRING30 byte [30]
#define STRING45 byte [45]

/********************************************************************
* Kundenpromdefinierte Fehlertexte
**********************************************************************/

STRING45 Lan1Error1    as KPID_LAN1ERROR1;
STRING45 Lan1Error2    as KPID_LAN1ERROR2;
STRING45 Lan1Error3    as KPID_LAN1ERROR3;
STRING45 Lan1Error4    as KPID_LAN1ERROR4;
STRING45 Lan1Error5    as KPID_LAN1ERROR5;
STRING45 Lan1Error6    as KPID_LAN1ERROR6;
STRING45 Lan1Error7    as KPID_LAN1ERROR7;
STRING45 Lan1Error8    as KPID_LAN1ERROR8;
STRING45 Lan1Error9    as KPID_LAN1ERROR9;
STRING45 Lan1Error10   as KPID_LAN1ERROR10;
STRING45 Lan1Error11   as KPID_LAN1ERROR11;
STRING45 Lan1Error12   as KPID_LAN1ERROR12;
STRING45 Lan1Error13   as KPID_LAN1ERROR13;
STRING45 Lan1Error14   as KPID_LAN1ERROR14;
STRING45 Lan1Error15   as KPID_LAN1ERROR15;
STRING45 Lan1Error16   as KPID_LAN1ERROR16;

STRING45 Lan2Error1    as KPID_LAN2ERROR1;
STRING45 Lan2Error2    as KPID_LAN2ERROR2;
STRING45 Lan2Error3    as KPID_LAN2ERROR3;
STRING45 Lan2Error4    as KPID_LAN2ERROR4;
STRING45 Lan2Error5    as KPID_LAN2ERROR5;
STRING45 Lan2Error6    as KPID_LAN2ERROR6;
STRING45 Lan2Error7    as KPID_LAN2ERROR7;
STRING45 Lan2Error8    as KPID_LAN2ERROR8;
STRING45 Lan2Error9    as KPID_LAN2ERROR9;
STRING45 Lan2Error10   as KPID_LAN2ERROR10;
STRING45 Lan2Error11   as KPID_LAN2ERROR11;
STRING45 Lan2Error12   as KPID_LAN2ERROR12;
STRING45 Lan2Error13   as KPID_LAN2ERROR13;
STRING45 Lan2Error14   as KPID_LAN2ERROR14;
STRING45 Lan2Error15   as KPID_LAN2ERROR15;
STRING45 Lan2Error16   as KPID_LAN2ERROR16;

STRING45 Lan3Error1    as KPID_LAN3ERROR1;
STRING45 Lan3Error2    as KPID_LAN3ERROR2;
STRING45 Lan3Error3    as KPID_LAN3ERROR3;
STRING45 Lan3Error4    as KPID_LAN3ERROR4;
STRING45 Lan3Error5    as KPID_LAN3ERROR5;
STRING45 Lan3Error6    as KPID_LAN3ERROR6;
STRING45 Lan3Error7    as KPID_LAN3ERROR7;
STRING45 Lan3Error8    as KPID_LAN3ERROR8;
STRING45 Lan3Error9    as KPID_LAN3ERROR9;
STRING45 Lan3Error10   as KPID_LAN3ERROR10;
STRING45 Lan3Error11   as KPID_LAN3ERROR11;
STRING45 Lan3Error12   as KPID_LAN3ERROR12;
STRING45 Lan3Error13   as KPID_LAN3ERROR13;
STRING45 Lan3Error14   as KPID_LAN3ERROR14;
STRING45 Lan3Error15   as KPID_LAN3ERROR15;
STRING45 Lan3Error16   as KPID_LAN3ERROR16;


/********************************************************************
* Das eigentliche Kundenprom
**********************************************************************/

STRING30 VersKprom    as KPID_VERSKPROM;
byte     SpecKprom[7] as KPID_SPECKPROM;
STRING30 TimeKprom    as KPID_TIMEKPROM;
word InjUnits     as KPID_INJUNITS;
word ResUnits     as KPID_RESUNITS;
word InjCycles    as KPID_INJCYCLES;
word Stations     as KPID_STATIONS;
word HeatZones    as KPID_HEATZONES;
word ResHeatZones as KPID_RESHEATZONES;
word TempTools    as KPID_TEMPTOOLS;
word Regler       as KPID_REGLER;
word HeatRegs     as KPID_HEATREGS;
word TempCards    as KPID_TEMPCARDS;
word InjHeatZones as KPID_INJHEATZONES;

byte InjHeatTab  [InjHeatZones+1][InjUnits+1] as KPID_INJHEATTAB  ;
byte ToolHeatTab [HeatZones+1][Stations+1]    as KPID_TOOLHEATTAB ;
byte TempHeatTab [TempTools+1][Stations+1]    as KPID_TEMPHEATTAB ;
byte ResHeatTab  [ResHeatZones+1][Stations+1] as KPID_RESHEATTAB  ;
byte ReglerName  [(Regler+1)*11+1]            as KPID_REGLERNAME  ;
word ReglerParam [Regler+1][HeatRegs]         as KPID_REGLERPARAM ;
word MaxDMAAddr                               as KPID_MAXDMAADDR;
word [MaxDMAAddr+1] TlgDMAAddr                as KPID_TLGDMAADDR;


STRING30  OrderNr         as KPID_ORDERNR     ;
STRING30  MashineNr       as KPID_MASHINENR   ;
byte      MashineType[7]  as KPID_MASHINETYPE ;
STRING30  CloseForce      as KPID_CLOSEFORCE  ;
STRING30  Language1       as KPID_LANGUAGE1   ;
STRING30  Language2       as KPID_LANGUAGE2   ;
STRING30  Language3       as KPID_LANGUAGE3   ;
STRING30  IqtVersion      as KPID_IQTVERSION  ;
STRING30  Customer        as KPID_CUSTOMER    ;
STRING30  FreeText1       as KPID_FREETEXT1   ;
STRING30  FreeText2       as KPID_FREETEXT2   ;
STRING30  FreeText3       as KPID_FREETEXT3   ;
STRING30  FreeText4       as KPID_FREETEXT4   ;

bit  [120] OptionTab      as KPID_OPTIONTAB   ;
word [23] ToolParamTab    as KPID_TOOLPARAMTAB;
word [ResUnits][InjUnits][9]  AggParamTab     as KPID_AGGPARAMTAB ;
word [ResUnits][InjUnits][5]  SnParamTab1     as KPID_SNPARAMTAB1 ;
word [ResUnits][InjUnits][5]  SnParamTab2     as KPID_SNPARAMTAB2 ;
word [ResUnits][InjUnits][5]  SnParamTab3     as KPID_SNPARAMTAB3 ;
byte      ScreenSaveT     as KPID_SCREENSAVET ;   /* Zeit bis Dunkelschaltung   */
byte      OilHeat         as KPID_OILHEAT     ;
word      CLB_SollBufSize as KPID_SOLLBUFSIZE ;
word      CLB_IstBufSize  as KPID_ISTBUFSIZE  ;
word      CLB_ErrBufSize  as KPID_ERRBUFSIZE  ;
byte [7]  CLB_Password    as KPID_PASSWORD    ;

word [InjUnits+2] InjSpeedMax     as KPID_INJSPEEDMAX ;
word [InjUnits+2] InjSpeedConv    as KPID_INJSPEEDCONV;

/********************************************************************
* Schnittstellenkram
**********************************************************************/

/* Anzahl der Tabellen-Eintraege */
word IntfCount    as KPID_INTFCOUNT;
word DevCount     as KPID_DEVCOUNT;

                   
word IntfKonf [IntfCount][6] as KPID_INTFKONF;
word DevKonf  [DevCount][2]  as KPID_DEVKONF;

/********************************************************************
* Frei benutzbare Tabelle
**********************************************************************/

word [50]  FreeTab     as KPID_FREETAB ;
