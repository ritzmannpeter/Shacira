/************************************************************************
*  Automatic Generation (Symgen):      Thu Mar 03 15:22:13 2005         *
************************************************************************/
/*.SS.***********************************************************************
*
*  BESCHREIBUNG:
*
*  HISTORY:
*     14.09.04 -HA-     FK_SEUebWa and SEs_pUEin included.
*
*  VERSION:
*     VERSION:  1.3              AUTOR:
*     DATUM:    14.12.95         TELEFON:
*
*  BEMERKUNGEN:
* 
**.ES.**********************************************************************/

/*.SM.***********************************************************************
*
*  MODUL-NAME: 
*     SYMBIT.H    
*
*  BESCHREIBUNG:                                                   
*     Definition der Bitadressen und -namen fuer die B & R  -  Steuerung
*
****************************************************************************
*                                                                  
*  HISTORY:                                                        
*     17.06.93 -MBa-    Ganze Symbit.h von COMMON uebernommen und angepasst
*     30.06.93 -MBa-    IDIm_For, IDIm_ForOn aufgenommen
*     06.07.93 -MBa-    neue Diagnosebits aufgenommen
*     21.10.93 -MBa-    alles nicht verwendete bei bur rausgeschmissen
*     27.01.94 -MBa-    Wkz-Auswerfer in den Standard uebernommen     
*     17.02.94 -TSchw-  WZm_HAnf neu eingefuegt
*     12.04.94 -MBa-    KZm_Sond neu eingefuegt
*     31.05.94 -MBa-    HEm_Abort neu eingefuegt
*     07.02.95 -MBa-    FKm_SKm2Tur neu eingefuegt
*     19.06.95 -HAns-   An Elektra-Version 2.0.0 angepasst (Neue Fehlerbits)
*     08.08.95 -HAns-   IQsSonBit0 bis IQsSonBit9 eingefuegt
*     18.08.95 -HAns-   WSs_pEinr eingefuegt
*     21.08.95 -HAns-   dduese herausgenommen, AWs_SynAus und AWs_DynPla eingef.
*     26.11.95 -HAns-   Fehlermeldungen an Prokontrol-Elektra angepasst.
*     24.01.96 -HAns-   MSm_ElTest eingefuegt.
*     07.02.96 -HAns-   Iy9008soll bis Iy9026soll herausgenommen
*                       Iy9008ist bis Iy90011ist herausgenommen
*     09.02.96 -HAns-   FK_FHmin und FK_FHmax eingefuegt.
*     25.04.96 -HAns-   FK_GK_Aufn und FK_SN_Aufn eingefuegt.
*     07.05.96 -HAns-   FK_Pol0mm eingefuegt.
*     29.10.96 -HAns-   FK_Son0 in FK_SGmvTur umbenannt.
*                       FK_Son1 in FK_SGmhTur umbenannt.
*                       FK_Sonc in FK_Sl_dms umbenannt.
*     17.03.97 -HAns-   PLs_Rampe und FK_GKSchm angelegt.
*     23.05.97 -GhG-    SLd_maxkr Not ™ffnung Kniehebel ein=1 aus=0
*                       nach Angabe von Herrn Bockstahler eingefuegt
*     27.05.97 -HAns-   Bits fuer freiprogrammierbaren Kernzug eingefuegt.
*                       (keine Funktionalitaet)
*     09.06.98 -GhG-    Erweiterungen fuer die Elektra 2f-Maschinen
*                       PLs_Rampe2    - Aggregat 2: Plastifizier-Rampe Ein/Ausschalten  
*                       msum21-msum25 - Aggregat 2: Wegumschaltbit fuer Spritzwerte
*                       mtum21-mtum21 - Aggregat 2: Zeitumschaltbit fuer Spritzwerte 
*                       mpum21-mpum21 - Aggregat 2: Druckumschaltbit fuer Spritzwerte
*                       SNm_ErhNm2    - erhoehtes Schneckendrehmoment Agg.2
*                       dwsp01        - Aggregat 1: Wahlbit fuer Spritzeinheit  S.44  
*                       dwsp02        - Aggregat 2: Wahlbit fuer Spritzeinheit  S.44  
*                       dwsp12        - Wahlbit fuer Wahl Spritzeinheit S.44 (2F)     
*                       dwspps        - Wahlbit fuer Betriebsart Einspritzen S.44 (2F)
*                       dwsprf        - Wahlbit fuer Reihenfolge Einspritzen S.44 (2F)
*                       dwagps        - Wahlbit fuer Betriebsart Aggregatbew. S.44 (2F)
*                       dwagrf        - Wahlbit fuer Reihenfolge Aggregatbew. S.44 (2F)
*                       dlagr2        - Schneckenendlageregelung S. 40 Agg 2        
*                       dschw2        - Schneckenwechsel  aus=0 ein=1  S.49 Agg. 2  
*                       FK_SNwech2    - Agregat 2: Schneckenwechsel
*                       FK_Ir2weg3    - Weggeber des Aggregates 2 defekt            
*                       FK_Ir2weg1    - Weggeber der Spritzachse 2 defekt           
*                       FK_AGm_Tu2    - Stoerung der Duesenschutztuer Agg 2         
*                       FK_SNikOk2    - Schneckenfreigabe fehlt Agg 2               
*                       FK_AGmlEr2    - Ueberlastung der Aggregatachse 2            
*                       FK_PLmlEr2    - Ueberlastung der Plastifizierachse 2        
*                       FK_SPmlEr2    - Ueberlastung der Einspritzachse 2           
*                       FK_PLutTi2    - Plast.-Zeit Agg. 2 ueberschritten           
*                       FK_SEp_Of2    - Einspritzdruck Offset Fehler Agg 2          
*                       FK_ZHTmpk2    - Zylindertemperaturen unter 150 [C Agg 2     
*                       FK_SN_Auf2    - Spritzkraft-Aufnehmer pr}fen Agg 2          
*                       FK_SPKraf2    - Zu grosse Schneckenrueckzugskraft Agg 2   
*                   
*                       FK_EXTnIni    - Schnittstelle Temp.Ger{t nicht initialisiert
*                       FK_EXTDat     - St|rung Datacom Temp.Ger{t                 
*                       FK_EXTemp     - St|rung ext. Temp.Ger{t                    
*                       FK_CDwblk     - Werkzeugbewegung von extern blockiert      
*                       FK_CDHGne     - Entnahme-HG Kupplung nicht entriegelt      
*                       FK_CDHGnv     - Entnahme-HG Kupplung nicht verriegelt      
*                       FK_CDHGnCD    - Entnahme-HG hat CD nicht gegriffen         
*                       FK_CDHGnAG    - Entnahme-HG hat Angu~ nicht gegriffen      
*                       FK_CDFHGn     - Folge-HG hat CD nicht gegriffen            
*                       FK_CDMwech    - Bitte Matrize wechseln                     
*
*     30.06.98 -HAns-   Erweiterungen fuer die Elektra 2f-Maschinen:
*                       FK_Ir2dreh    - Drehzahlgeber der Plast. 2 defekt          
*                       FK_DR3Err     - Stoerung im Drive der Spritzeinheit 2      
*                       FK_PLssEn2    - Plastifizierweg Agg 2 }berschritten        
*                       FK_AGm_Vo2    - D}senanlagedruck Agg 2 nicht erreicht      
*                       FK_PLm_Ak2    - Plastifizierweg Agg 2 nicht erreicht       
*                       FK_SPRefE2    - Schnecken-Referenzpunkt Agg 2 fehlt        
*                       FK_AGmsPo2    - Aggregat 2 nicht in Position               
*                       FK_SPmsPo2    - Schnecke 2 nicht in Position               
*                       FK_AG_Ver2    - Aggregat 2-Verriegelungsfehler             
*                       FK_SPRfEr2    - Einspritzachse-Referenzschalterfehler Agg 2
*                       FK_AGmlWr2    - Erhoehte Leistung bei Aggregatachse 2      
*                       FK_PLmlWr2    - Erhoehte Leistung bei Plastifizierachse 2  
*                       FK_SPmlWr2    - Erhoehte Leistung bei Einspritzachse 2     
*                       FK_DR3Temp    - Motoruebertemperatur am Spritzdrive Agg 2  
*     13.02.02 -HA-     Fehlerbits fuer E200/300 eingefuegt, FK_DR4Temp, FK_DR4Err,
*                       FK_B7001, mspinok und msgeleok.
*     14.02.02 -HA-     bxsoll, mtianf entfernt.
*     21.03.02 -HA-     Fehlerbits fuer 2 Farben entfernt.
*                       fagsich1 und FK_AGe2Tur eingefuegt
*     04.04.02 -HA-     IOm_AOiqt und IOm_DIOiqt  Komunikation fuer SPS-freigabe der 
*                       freikonfigurierbaren digitalen bzw. analogen Ein/Ausgaenge 
*                       Seiten 66.0,1,2 eingefuegt.
*                       FK_IOe_DI1 bis FK_IOe_DI4 eingefuegt                   
*     05.04.02 -HA-     OPm_Luft8 eingefuegt.
*     08.04.02 -HA-     FK_NoAbGlP und FK_SPSDiag eingefuegt.
*     09.04.02 -HA-     QUm_IQTfrd     71.0 SPS-Freigabebit Foerderband        
*                       QUm_IQT720     72.0 SPS-Freigabebit Qualitaetskontrolle
*                       QUm_IQT721     72.1 SPS-Freigabebit Selektierweiche    
*                       OPm_IQT800     SPS_IQT-Option Kuehlwasser-Abschaltung Seite 80
*     16.04.02 -HA-     FK_B7001 durch FK_AG_Aufn ersetzt.
*     17.04.02 -HA-     Ist-Bit UP_SPSText eingefuegt.
*     26.05.02 -HA-     FK_AWS99F und FK_AWSFull angelegt.
*                       Symboldefinition fuer frei progr.bare Kernzuege (KE..) eingefuegt.
*     27.05.02 -HA-     FK_ZSchmie eingefuegt.
*                       OBPLCIQT1 bis OBPLCIQT16 und OBIQTPLC1 bis OBIQTPLC16 eingefuegt.
*                       WZi_HAktiv eingefuegt und msspinok, msgeleok herausgenommen.
*     03.06.02 -HA-     FK_AW_Verr, FK_SP_Verr, FK_PL_Verr und FK_NDpBegr eingefuegt.
*                       Fehlermeldungen eingefuegt FK_XSm_Anf, FK_XSm_An2, FK_SerIni,
*                       FK_SerCom, FK_SerExt und FK_SerPro 
*                       OPm_IQT350, OPm_IQT399 und HXsnEcho eingefuegt
*     17.06.02 -HA-     OPm_Karton und FK_Karton1 eingefuegt.
*                       FK_SnBlock eingefuegt.
*     19.06.02 -HA-     ZSmDauerB eingefuegt.
*                       FK_DR3Err eingefuegt. 
*     25.06.02 -HA-     MOm_MotOn eingefuegt.
*     23.07.02 -HA-     NDs_DrBegr eingefuegt.
*     24.07.02 -HA-     OPm_Airpr, OPm_APProp, OPm_APip, FK_APeAktiv, FK_APStoer und FK_APpeSysT eingefuegt.
*     22.01.02 -HA-     ZYitAnalys eingefuegt.
*                       OPs_FssBlk und OPm_FssEnd eingefuegt.
*     23.01.03 -HA-     Fehlermeldungen eingefuegt FK_XSm_Anf und FK_XSm_An2
*     05.06.03 -HA-     Fehlermeldungen FK_SLVerr1 bis 3 eingefuegt.
*                       OPm_SlSens und OPm_AgBirk eingefuegt.
*     23.06.03 -HA-     AGm_NoBirk eingefuegt.
*     27.11.03 -HA-     FK_FSSTolN eingefuegt.
*     29.01.04 -HA-     IQm_Shutd eingefuegt.
*     30.06.04 -HA-     FK_SE1WegM und FK_SE1NAct eingefuegt.
*                       fa1ruh und foeln eingefuegt
*                       Bits fuer Wenden und Werkzeugauswerfer eingefuegt.
*                       FK_DTnReg bis FK_CanWink eingefuegt.
*                       FK_AgMoTmp und FK_DRV5Err eingefuegt.
*                       OPm_ZHAnf und FK_ZHAnf1,2 eingefuegt.
*                       FK_WEsmirl, FK_KZ_Aufn und FK_WEZsErr eingefuegt.
*     01.07.04 -HA-     Folgende Bits heraugenommen, da der programmierbare Kernzug
*                       nicht definiert wurde:
*                       dkzon, k1epar, k1apar, k2epar, k2apar, dkeinz, dkausz,
*                       dk1eid, dk2eid, dk1aud, dk2aud, dkei2z, dkau2z
*     11.08.04 -HA-     SetStsHotRunStbTmpOnOff und SetStsBrlStbTmpOnOff eingefuegt.
*     17.08.04 -HA-     mxstdt entfernt.
*     22.08.04 -HA-     ActStsInjSwOverWay16 - 1a, ActStsInjSwOverTim17 - 1a and ActStsInjSwOverPrs16 - 1a included
*
**.EM.**********************************************************************/

/* ---------------- Sollbits (Downloadbits) ------------------------------- */
#define ddummi     0x0    /*  Dummy-Bit                                      */
#define miheie     0x1    /*  Ein/Ausschaltbit fuer Heizung ein              */
#define mimote     0x2    /*  Ein/Ausschaltbit fuer Motor ein                */
#define miext1     0x3    /*  Ein/Ausschaltbit fuer Externes Geraet 1 ein    */
#define miext2     0x4    /*  Ein/Ausschaltbit fuer Externes Geraet 2 ein    */
#define ROm_Type   0x5    /*  Handlinggeraet Type Rx10/Rx20                  */
#define ROm_AusGrf 0x6    /*  Handlinggeraet Auswerfer vor/nach Greifer      */
#define ROm_AusHub 0x7    /*  Handlinggeraet: Auswerfer Einf./Mehrfachhub    */
#define ROm_BCAxis 0x8    /*  Handlinggeraet: mit/ohne B_C Achse             */
#define ROm_TContr 0x9    /*  Handlinggeraet: mit/ohne Teilekontrolle        */
#define ROm_Vakuum 0xa    /*  Handlinggeraet: Vakuum aus/ein                 */
#define ROm_Zange  0xb    /*  Handlinggeraet: Zange aus/ein                  */
#define ROm_SondAng 0xc    /*  Handlinggeraet: Anguss separieren ein/aus      */
#define ROm_SondSch 0xd    /*  Handlinggeraet: Jeder zweite Schuss ??         */
#define ROm_An     0xe    /*  Handlinggeraet an/aus                          */
#define DIm_ForOn  0xf    /*  Diagnosemode Forcemode enable                  */
#define SNm_ErhNm  0x10   /*  Aggregat 1: erhoehtes Schneckendrehmoment      */
#define SNm_ErhNm2 0x11   /*  Aggregat 2: erhoehtes Schneckendrehmoment      */
#define DIm_Init   0x12   /*  Init SPS                                       */
#define DIm_Clear  0x13   /*  loeschen aller Force Werte                     */
#define ezhasc     0x14   /*  Schnellkupplung fuer Auswerfer-Ruhelage HASCO  */
#define miheia     0x15   /*  Ein/Ausschaltbit fuer Heizung aus              */
#define mimota     0x16   /*  Ein/Ausschaltbit fuer Motor aus                */
#define miex1a     0x17   /*  Ein/Ausschaltbit fuer Externes Geraet 1 aus    */
#define miex2a     0x18   /*  Ein/Ausschaltbit fuer Externes Geraet 2 aus    */
#define dschwe     0x19   /*  Schneckenwechsel  aus=0 ein=1  S.49 Agg. 1     */
#define dschw2     0x1a   /*  Schneckenwechsel  aus=0 ein=1  S.49 Agg. 2     */
#define maswnp     0x1b   /*  Startbit Auswerfernullpunktabgleich            */
#define d4b5       0x1c   /*  Ruhelage Ueberwachung         S.52             */
#define mtolue     0x1d   /*  zuruecksetzen wenn Toleranzueberwachungsfehler */
#define mtomax     0x1e   /*  Maximum Toleranzueberschreitung erreicht       */
#define dmaus      0x1f   /*  Automatische Maschinenabschaltung S.80         */
#define doelhz     0x20   /*  Oelvorwaermung S.15                            */
#define dopt       0x21   /*  Wahlbit optische Werkzeugsicherung             */
#define danf       0x22   /*  Einschaltbit Werkzeugheizung                   */
#define dlager     0x23   /*  Schneckenendlageregelung S. 40 Agg 1           */
#define dlagr2     0x24   /*  Schneckenendlageregelung S. 40 Agg 2           */
#define AWs_SynAus 0x25   /*  Synchrones Ausstossen S. 52                    */
#define dauswr     0x26   /*  Auswerfer gerastet ja/nein S.52                */
#define dlicht     0x27   /*  Lichtschranke Ausfallwaage S.80                */
#define ensdtr     0x28   /*  Handschakebit fuer Heizungssollwertdatacom     */
#define dplafo     0x29   /*  Bewegung parallel plastifizieren aus=0  S.51   */
#define msuzer     0x2a   /*  Produktionsende                                */
#define enkrqd     0x2b   /*  Kommunikationsbit Heizung                      */
#define mextsi     0x2c   /*  Merker externes Signal                         */
#define WAs_Uebv   0x2d   /*  Wkz-Ausw Ueberwachung vorne Endschalter/Zeit   */
#define WAs_Uebz   0x2e   /*  Wkz-Ausw Ueberwachung zurueck Endschalter/Zeit */
#define WAs_fss    0x2f   /*  Wkz-Ausw Ueberwachung erst mit fss             */
/* ------------------ Qualitaetskontrolle --------------------------------- */
#define QUsnsub    0x30   /*  Subtrahierender Schusszaehler unterbrechen     */
#define QUsnexz    0x31   /*  Externer Zykl.zaehler unterbrechen             */
#define QUsninv    0x32   /*  Inversbetrieb                                  */
/* ---------------- Selektierweiche --------------------------------------- */
#define QUs_SprAng 0x33   /*  Spritzling selektieren                         */
#define QUs_Invers 0x34   /*  Inversbetrieb                                  */
#define WSs_pEinr  0x35   /*  S.50 Schliesskraft im Einrichten               */
/* ---------------- Sonderbits -------------------------------------------- */
#define IQsSonBit0 0x36   /*  Soll-Sonderbit 0                               */
#define IQsSonBit1 0x37   /*  Soll-Sonderbit 1                               */
#define IQsSonBit2 0x38   /*  Soll-Sonderbit 2                               */
#define IQsSonBit3 0x39   /*  Soll-Sonderbit 3                               */
#define IQsSonBit4 0x3a   /*  Soll-Sonderbit 4                               */
#define IQsSonBit5 0x3b   /*  Soll-Sonderbit 5                               */
#define IQsSonBit6 0x3c   /*  Soll-Sonderbit 6                               */
#define IQsSonBit7 0x3d   /*  Soll-Sonderbit 7                               */
#define IQsSonBit8 0x3e   /*  Soll-Sonderbit 8                               */
#define IQsSonBit9 0x3f   /*  Soll-Sonderbit 9                               */
/* ------------------------------------------------------------------------ */
#define AWs_DynPla 0x40   /*  Dynamische Plattensicherung S.52               */
#define MSm_ElTest 0x41   /*  Testbetrieb ein S.17.2                         */
#define SLd_maxkr  0x42   /*  Not ™ffnung Kniehebel ein=1 aus=0              */
#define dwsp01     0x43   /*  Aggregat 1: Wahlbit fuer Spritzeinheit S.44(2F) */
#define dwsp02     0x44   /*  Aggregat 2: Wahlbit fuer Spritzeinheit S.44(2F) */
#define dwsp12     0x45   /*  Wahlbit fuer Wahl Spritzeinheit S.44 (2F)      */
#define dwspps     0x46   /*  Wahlbit fuer Betriebsart Einspritzen S.44 (2F) */
#define dwsprf     0x47   /*  Wahlbit fuer Reihenfolge Einspritzen S.44 (2F) */
#define dwagps     0x48   /*  Wahlbit fuer Betriebsart Aggregatbew. S.44 (2F) */
#define dwagrf     0x49   /*  Wahlbit fuer Reihenfolge Aggregatbew. S.44 (2F) */
#define OBIQTPLC1  0x4a   /*  IQT/SPS-Optionsbit 1                           */
#define OBIQTPLC2  0x4b   /*  IQT/SPS-Optionsbit 2                           */
#define OBIQTPLC3  0x4c   /*  IQT/SPS-Optionsbit 3                           */
#define OBIQTPLC4  0x4d   /*  IQT/SPS-Optionsbit 4                           */
#define OBIQTPLC5  0x4e   /*  IQT/SPS-Optionsbit 5                           */
#define OBIQTPLC6  0x4f   /*  IQT/SPS-Optionsbit 6                           */
#define OBIQTPLC7  0x50   /*  IQT/SPS-Optionsbit 7                           */
#define OBIQTPLC8  0x51   /*  IQT/SPS-Optionsbit 8                           */
#define OBIQTPLC9  0x52   /*  IQT/SPS-Optionsbit 9                           */
#define OBIQTPLC10 0x53   /*  IQT/SPS-Optionsbit 10                          */
#define OBIQTPLC11 0x54   /*  IQT/SPS-Optionsbit 11                          */
#define OBIQTPLC12 0x55   /*  IQT/SPS-Optionsbit 12                          */
#define OBIQTPLC13 0x56   /*  IQT/SPS-Optionsbit 13                          */
#define OBIQTPLC14 0x57   /*  IQT/SPS-Optionsbit 14                          */
#define OBIQTPLC15 0x58   /*  IQT/SPS-Optionsbit 15                          */
#define OBIQTPLC16 0x59   /*  IQT/SPS-Optionsbit 16                          */
#define HXsnEcho   0x5a   /*  Echobit S. 39.9  */
#define HXsnEcho_2 0x5b   /*  Echobit S. 39.9  */
#define ZSmDauerB  0x5c   /*  Dauerbetrieb Zentralschmierung  */
#define NDs_DrBegr 0x5d   /*  Nachdruckbegrenzung ein/aus  */
#define OPs_FssBlk 0x5e   /*  FSS-Ende auffahren=0, zufahren=1  */
#define OPm_SlSens 0x5f   /*  IQT/SPS-Optionsbit 0 = Standardschliesskraftregelung, 1 = Schliesskraftregelung mit Sensor  */
#define OPm_AgBirk 0x60   /*  IQT/SPS-Optionsbit 0 = alte Agregatschaltung, 1 = neue Aggregatschaltung  */
#define AGm_NoBirk 0x61   /*  Medienwandler nicht f}llen  */
/* ---------------- Seite 49.0 mit Wegmesslineal -------------------------- */
#define SEAbglST1  0x62   /*  Start Spritzeinheitabgleich 1                  */
#define SEAbglRS1  0x63   /*  Ende  Spritzeinheitabgleich 1                  */
/* ------------------ Werkzeugauswerfer ----------------------------------- */
#define WZA_Chkvor 0x64   /*  Ueberwachung Auswerfer vor     S.53.0, Z. 9    */
#define WZA_Chkzur 0x65   /*  Ueberwachung Auswerfer zurueck S.53.0, Z.10    */
#define WZA_ChkFSS 0x66   /*  Endlageueberwachung mit FSS-B. S.53.0, Z.13    */
/* ------------------ Werkzeugauswerfer 2 --------------------------------- */
#define WZA2Chkvor 0x67   /*  Ueberwachung Auswerfer vor     S.53.1, Z. 9    */
#define WZA2Chkzur 0x68   /*  Ueberwachung Auswerfer zurueck S.53.1, Z.10    */
#define WZA2ChkFSS 0x69   /*  Endlageueberwachung mit FSS-B. S.53.1, Z.13    */
#define SetStsHotRunStbTmpOnOff 0x6a   /* On/Off Button Soft-Start hot runner */
#define SetStsBrlStbTmpOnOff 0x6b   /* On/Off Button Soft-Start temperature barrel */
#define ALIGNMENTBIT1 0x6c   /*  Reserve 1 (16 Bits) */
/* ---------------- sonstige Kommunikationsbits --------------------------- */
#define mfohoe     0x7c   /*  Startbit fuer Formhoehenabgleich               */
#define WZm_HAnf   0x7d   /*  Formhoehe nicht eingestellt                    */
#define HEm_Start  0x7e   /*  Heizungsoptimierung starten                    */
#define PLs_Rampe  0x7f   /*  Aggregat 1: Plastifizier-Rampe Ein/Ausschalten */
#define PLs_Rampe2 0x80   /*  Aggregat 2: Plastifizier-Rampe Ein/Ausschalten */
#define SEs_pUEin  0x81   /*  Spritzdrucküberwachung ein/aus, Agg 1 */
#define ALIGNMENTBIT2 0x82   /*  Reserve 2 (14 Bits) */

/* ---------------- Istbits ----------------------------------------------- */
#define Start_ActBits 0x90   /* Dummy Bit, Bitnummer des 1. Istbits */
#define dsusei     0x90   /*  Sub. Schusszaehler ruecksetzen               */
#define drads1     0x91   /*  Add. Schusszaehler ruecksetzen               */
#define dexrs      0x92   /*  Externes Signal reset neustart               */
#define msigex     0x93   /*  Merker um Signal extern zu sperren           */
#define msszsp     0x94   /*  Merker um sub. Schusszaehler zu sperren      */
#define ROm_GrdSt  0x95   /*  Robot ist (nicht) in Grundstellung           */
#define DIm_For    0x96   /*  Force Mode erlaube Bit                       */
#define mftrks     0x97   /*  wenn dieses Bit gesetzt ist, werden die      */
#define maswok     0x98   /*  Iscosfreigabe fuer Auswerfer                 */
#define msum11     0x99   /*  Aggregat 1: Wegumschaltbit fuer Spritzwerte Phase 1      */
#define msum12     0x9a   /*  Aggregat 1: Wegumschaltbit fuer Spritzwerte Phase 2      */
#define msum13     0x9b   /*  Aggregat 1: Wegumschaltbit fuer Spritzwerte Phase 3      */
#define msum14     0x9c   /*  Aggregat 1: Wegumschaltbit fuer Spritzwerte Phase 4      */
#define msum15     0x9d   /*  Aggregat 1: Wegumschaltbit fuer Spritzwerte Phase 5      */
#define ActStsInjSwOverStr16 0x9e   /* Injection 1: switch over stroke stage 6 */
#define ActStsInjSwOverStr17 0x9f   /* Injection 1: switch over stroke stage 7 */
#define ActStsInjSwOverStr18 0xa0   /* Injection 1: switch over stroke stage 8 */
#define ActStsInjSwOverStr19 0xa1   /* Injection 1: switch over stroke stage 9 */
#define ActStsInjSwOverStr1a 0xa2   /* Injection 1: switch over stroke stage 10 */
#define mtum11     0xa3   /*  Aggregat 1: Zeitumschaltbit fuer Spritzwerte Phase 1     */
#define mtum12     0xa4   /*  Aggregat 1: Zeitumschaltbit fuer Spritzwerte Phase 2     */
#define mtum13     0xa5   /*  Aggregat 1: Zeitumschaltbit fuer Spritzwerte Phase 3     */
#define mtum14     0xa6   /*  Aggregat 1: Zeitumschaltbit fuer Spritzwerte Phase 4     */
#define mtum15     0xa7   /*  Aggregat 1: Zeitumschaltbit fuer Spritzwerte Phase 5     */
#define mtum16     0xa8   /*  Aggregat 1: Zeitumschaltbit fuer Spritzwerte Phase 6     */
#define ActStsInjSwOverTim17 0xa9   /* Injection 1: switch over time stage 7 */
#define ActStsInjSwOverTim18 0xaa   /* Injection 1: switch over time stage 8 */
#define ActStsInjSwOverTim19 0xab   /* Injection 1: switch over time stage 9 */
#define ActStsInjSwOverTim1a 0xac   /* Injection 1: switch over time stage 10 */
#define mpum11     0xad   /*  Aggregat 1: Druckumschaltbit fuer Spritzwerte Phase 1    */
#define mpum12     0xae   /*  Aggregat 1: Druckumschaltbit fuer Spritzwerte Phase 2    */
#define mpum13     0xaf   /*  Aggregat 1: Druckumschaltbit fuer Spritzwerte Phase 3    */
#define mpum14     0xb0   /*  Aggregat 1: Druckumschaltbit fuer Spritzwerte Phase 4    */
#define mpum15     0xb1   /*  Aggregat 1: Druckumschaltbit fuer Spritzwerte Phase 5    */
#define ActStsInjSwOverPrs16 0xb2   /* Injection 1: switch over pressure stage 6 */
#define ActStsInjSwOverPrs17 0xb3   /* Injection 1: switch over pressure stage 7 */
#define ActStsInjSwOverPrs18 0xb4   /* Injection 1: switch over pressure stage 8 */
#define ActStsInjSwOverPrs19 0xb5   /* Injection 1: switch over pressure stage 9 */
#define ActStsInjSwOverPrs1a 0xb6   /* Injection 1: switch over pressure stage 10 */
#define meinr      0xb7   /*  Einrichten                                   */
#define mhand      0xb8   /*  Handbetrieb                                  */
#define mhalb      0xb9   /*  Betriebsart Halbautomatik                    */
#define mauto      0xba   /*  Betriebsart Vollautomatik                    */
#define mi4b6      0xbb   /*  gesetzt wenn Endschalter gedaempft           */
#define mihoeh     0xbc   /*  Reset Formhoehenabgleich                     */
#define mpausd     0xbd   /*  Spritzistwerte stehen bereit, wenn Bit ges.  */
#define mikanf     0xbe   /*  Anfahrschaltung erwuenscht?                  */
#define SPm_Down   0xbf   /*  Download anfordern von der SPS               */
#define HEm_Ready  0xc0   /*  Heizungsoptimierung beendet                  */
#define KZm_Sond   0xc1   /*  Kernuzug Sonderseite 65.0                    */
#define HEm_Abort  0xc2   /*  Heizungsoptimierung abbrechen                 */
#define IOm_DIOiqt 0xc3   /*  Komunikation fuer SPS-freigabe der digitalen Ein/Ausgaenge S. 66.0,1   */
#define IOm_AOiqt  0xc4   /*  Komunikation fuer SPS-freigabe der analogen Ausgaenge S. 66.2   */
#define OPm_Luft8  0xc5   /*  SPS_IQT-Option Freigabe der 5 bis 8 Luftventile  */
#define QUm_IQTfrd 0xc6   /*  71.0 SPS-Freigabebit Foerderband          */
#define QUm_IQT720 0xc7   /*  72.0 SPS-Freigabebit Qualitaetskontrolle  */
#define QUm_IQT721 0xc8   /*  72.1 SPS-Freigabebit Selektierweiche      */
#define OPm_IQT800 0xc9   /*  SPS_IQT-Option Kuehlwasser-Abschaltung Seite 80  */
#define UP_SPSText 0xca   /*  SPS-Texte von der SPS holen                  */
#define WZi_HAktiv 0xcb   /*  Meldung: Werkzeughoehenverstellung aktiv  */
#define OPm_IQT350 0xcc   /*  Komunikation fuer SPS-freigabe der S. 35  */
#define OPm_IQT399 0xcd   /*  Komunikation fuer SPS-freigabe der S. 39.9  */
#define OPm_Karton 0xce   /*  Komunikation fuer SPS-Freigabe der S.71.0, Zeile 14,15  */
#define MOm_MotOn  0xcf   /*  Motor-Ein/Betriebsstundenzaehler  */
/*------------------- Airpress -------------------------------------------- */
#define OPm_Airpr  0xd0   /*  Freigabe der Airpress-Option Seite 48.0 und 81.7  */
#define OPm_APProp 0xd1   /*  Freigabe des prop. Ventiles (Seite 48.0 Zeile 12-15)  */
#define OPm_APip   0xd2   /*  Freigabe der Zeile 18 Seite 48.0               */
/*------------------------------------------------------------------------- */
#define ZYitAnalys 0xd3   /*  Zeitanalyseregister werden im Einr. + Handb. */
#define OPm_FssEnd 0xd4   /*  Kommunikation fuer SPS-Freigabe der Seite 50.0, Zeile 16 FSS-Ende auffahren=0, zufahren=1  */
/* ------------------------------------------------------------------------ */
#define IQm_Shutd  0xd5   /*  Shutdown von USV der SPS angefordert           */
/* ------------------ Anfahrschaltung ------------------------------------- */
#define OPm_ZHAnf  0xd6   /*  Anfahrschaltung */
/* ---------------- Seite 49.0 mit Wegmesslineal -------------------------- */
#define SEAbglTas1 0xd7   /*  Spritzeinheittaste 1 gedrueckt                 */
#define SEAbglTas2 0xd8   /*  Spritzeinheittaste 2 gedrueckt                 */
#define OP_CanWink 0xd9   /*  SPS-Optionsbit fuer CAN-Winkelkodierer         */
/*------------------- SPS-Optionsbits Werkzeugauswerfer,Wenden ------------ */
#define OP_WkzAusw 0xda   /*  SPS-Optionsbit fuer Seite 53.0 Werkzeugausw.   */
#define OP_WkzAus2 0xdb   /*  SPS-Optionsbit fuer Seite 53.1 Werkzeugausw.   */
#define OP_WkzApv  0xdc   /*  SPS-Optionsbit fuer Seite 53.0 der Z.14 - 18   */
#define OP_Wenden  0xdd   /*  SPS-Optionsbit fuer Seite 57.0 Wenden          */
#define OP_WDgr_gs 0xde   /*  SPS-Optionsbit fuer Seite 57.0 der Z.16 - 19   */
#define ALIGNMENTBIT3 0xdf   /*  Reserve 3 (63 Bits) */

/* ---------------- freiprogrammierbare Kernzuege ------------------------- */
#define KEEinAus   0x11e  /*  Kernzug ein/aus                */
#define KELineAct0 0x12e  /*  aktive Kernzugprogrammzeile 0  */
#define KELineAct49 0x15f  /*  Ende                           */

#define ALIGNMENTBIT4 0x160  /*  Reserve 4 (576 Bits) */

/* ---------------- Fehlermeldungsbits ------------------------------------ */
#define FK_Start   0x3a0  /* Dummy Bit, Bitnummer des 1. Fehlerbits */
#define FK_SIe_24V 0x3a0  /*  Spannungsunterbrechung 24V Versorgung        */
#define FK_AWe_Tur 0x3a1  /*  Auswerferschutz offen                        */
#define FK_KEsnNr  0x3a2  /*  Kernzugnummer falsch                         */
#define FK_DRutAb  0x3a3  /*  Schliessdruck Ueberwachungszeit              */
#define FK_SLm_Stp 0x3a4  /*  Werkzeugbewegung blockiert                   */
#define FK_FSSmax  0x3a5  /*  Werkzeugsicherungswiederholung               */
#define FK_KEpos   0x3a6  /*  Kernposition fehlerhaft                      */
#define FK_OPgsNo  0x3a7  /*  Wegpunkt S.67 falsch                         */
#define FK_WHm_Anf 0x3a8  /*  Heizung Anfahrschaltung laeuft               */
#define FK_OPm_Ext 0x3a9  /*  Stoerung externes Geraet                     */
#define FK_OPm_Son 0x3aa  /*  Sonderfehlermeldung                          */
#define FK_SGmvTur 0x3ab  /*  vordere Formschutztuere nicht geschlossen    */
#define FK_SGmhTur 0x3ac  /*  hintere Formschutztuere nicht geschlossen    */
#define FK_AGm_Vor 0x3ad  /*  D}senanlagedruck nicht erreicht              */
#define FK_PLm_Akt 0x3ae  /*  Plastifizierweg Agg 1 nicht erreicht         */
#define FK_WHikOk  0x3af  /*  Wkz Heizung Freigabe fehlt                   */
#define FK_Sl_dms  0x3b0  /*  Schlie~kraftsensor pruefen                   */
#define FK_Sond    0x3b1  /*  Sonderbit                                    */
#define FK_Sone    0x3b2  /*  Sonderbit                                    */
#define FK_Sonf    0x3b3  /*  Sonderbit                                    */
#define FK_Sonp0   0x3b4  /*  Sonderbit                                    */
#define FK_Sonp1   0x3b5  /*  Sonderbit                                    */
#define FK_Sonp2   0x3b6  /*  Sonderbit                                    */
#define FK_Sonp3   0x3b7  /*  Sonderbit                                    */
#define FK_Sonp4   0x3b8  /*  Sonderbit                                    */
#define FK_Sonp5   0x3b9  /*  Sonderbit                                    */
#define FK_Sonp6   0x3ba  /*  Sonderbit                                    */
#define FK_Sonp7   0x3bb  /*  Sonderbit                                    */
#define FK_Sonp8   0x3bc  /*  Sonderbit                                    */
#define FK_Sonp9   0x3bd  /*  Sonderbit                                    */
#define FK_Sonpa   0x3be  /*  Sonderbit                                    */
#define FK_Sonpb   0x3bf  /*  Sonderbit                                    */
#define FK_Sonpc   0x3c0  /*  Sonderbit                                    */
#define FK_Sonpd   0x3c1  /*  Sonderbit                                    */
#define FK_AWd_Nul 0x3c2  /*  Auswerfernullpunkt unterschritten            */
#define FK_KEprf   0x3c3  /*  Kernposition }berpr}fen                      */
#define FK_KEkakt1 0x3c4  /*  Kern 1 Bewegung nicht ausgefuehrt            */
#define FK_KEkakt2 0x3c5  /*  Kern 2 Bewegung nicht ausgefuehrt            */
#define FK_KEbES1  0x3c6  /*  Kern 1 beide Endschalter betaetigt           */
#define FK_KEbES2  0x3c7  /*  Kern 2 beide Endschalter betaetigt           */
#define FK_KEfpos1 0x3c8  /*  Kern 1 nicht in richtiger Stellung           */
#define FK_KEfpos2 0x3c9  /*  Kern 2 nicht in richtiger Stellung           */
#define FK_AWblKE1 0x3ca  /*  Auswerfer blockiert Kern 1                   */
#define FK_AWblKE2 0x3cb  /*  Auswerfer blockiert Kern 2                   */
#define FK_KEblAW  0x3cc  /*  Kerne blockieren Auswerfer                   */
#define FK_SNwech  0x3cd  /*  Aggregat 1: Schneckenwechsel                 */
#define FK_KEaus   0x3ce  /*  Kernzug Seite 61 Zeile 2 ausschalten         */
#define FK_Feldkl  0x3cf  /*  Feldklemmenfehler                            */
#define FK_DoLoad  0x3d0  /*  Ueberlast Modul                              */
#define FK_DoTemp  0x3d1  /*  Uebertemperatur                              */
#define FK_Ir1_io  0x3d2  /*  I/O Error                                    */
#define FK_Ir1Par  0x3d3  /*  Config: EPROM voll                           */
#define FK_Ir2Par  0x3d4  /*  Config: kein RAM Speicher verfuegbar         */
#define FK_ROfrg   0x3d5  /*  Freigabe Sollwert Werkzeug schlie~en         */
#define FK_SGm2Tur 0x3d6  /*  hintere Schutztuer offen                     */
#define FK_GK_Aufn 0x3d7  /*  Gelenkkopfkraft-Aufnehmer pr}fen             */
#define FK_SN_Aufn 0x3d8  /*  Spritzkraft-Aufnehmer pr}fen Agg 1           */
#define FK_Pol0mm  0x3d9  /*  Polster-Istwert 0 mm                         */
#define FK_SL_QStp 0x3da  /*  St|rung Quick-Stop Schlie~einheit            */
#define FK_AW_QStp 0x3db  /*  St|rung Quick-Stop Auswerfer                 */
#define FK_PL_QStp 0x3dc  /*  St|rung Quick-Stop Plastifiziereinheit       */
#define FK_SP_QStp 0x3dd  /*  St|rung Quick-Stop Spritzeinheit             */
#define FK_ZSchmie 0x3de  /*  St|rung Zentralschmierung                    */
#define FK_AW_Verr 0x3df  /*  Auswerfer-Verriegelungsfehler                */

#define ALIGNMENTBIT5 0x3e0  /*  Reserve 5 (16 Bits) */

/* ---------------- new error-bit-numbers from Elektra V1.06 ------------ */
#define FK_SIe_Not 0x3f0  /*  Not-Aus-Taste betaetigt                      */
#define FK_SLRefES 0x3f1  /*  Formweg-Referenzpunkt fehlt                  */
#define FK_AWRefES 0x3f2  /*  Auswerfer-Referenzpunkt fehlt                */
#define FK_SP_Verr 0x3f3  /*  Spritzeinheit-Verriegelungsfehler            */
#define FK_SPRefES 0x3f4  /*  Schnecken-Referenzpunkt Agg 1 fehlt          */
#define FK_SPKraft 0x3f5  /*  Zu grosse Schneckenrueckzugskraft Agg 1      */
#define FK_SLssAuf 0x3f6  /*  Werkzeug nicht in Position                   */
#define FK_AWssZur 0x3f7  /*  Auswerfer nicht in hinterer Lage             */
#define FK_AGmsPos 0x3f8  /*  Aggregat 1 nicht in Position                 */
#define FK_SPmsPos 0x3f9  /*  Schnecke 1 nicht in Position                 */
#define FK_OelSaug 0x3fa  /*  Filterstoerung des Schmiersystems            */
#define FK_DR1Err  0x3fb  /*  Stoerung im Drive der Schlie~einheit         */
#define FK_DR2Err  0x3fc  /*  Stoerung im Drive der Spritzeinheit 1        */
#define FK_WSssZu  0x3fd  /*  Werkzeughoehe nicht eingestellt              */
#define FK_FHmsPos 0x3fe  /*  Werkzeughoehe nicht in Position              */
#define FK_SLsdr80 0x3ff  /*  Schliesskraft ausserhalb Toleranz            */
#define FK_SL_Verr 0x400  /*  Werkzeug-Verriegelungsfehler                 */
#define FK_AG_Verr 0x401  /*  Aggregat 1-Verriegelungsfehler               */
#define FK_SGm_Tur 0x402  /*  Formschutztuere nicht geschlossen            */
#define FK_AGe_Tur 0x403  /*  Duesenschutz nicht geschlossen               */
#define FK_SGm1Tur 0x404  /*  Stoerung der Formschutztuer                  */
#define FK_AGm_Tur 0x405  /*  Stoerung der Duesenschutztuer                */
#define FK_GK_Warn 0x406  /*  Erhoehte Reibung am Gelenksystem             */
#define FK_GK_Reib 0x407  /*  Zu grosse Reibung am Gelenksystem            */
#define FK_Ir1weg2 0x408  /*  Weggeber der Form defekt                     */
#define FK_Ir1weg4 0x409  /*  Weggeber des Auswerfers defekt               */
#define FK_Ir1weg3 0x40a  /*  Weggeber des Aggregates 1 defekt             */
#define FK_Ir1weg1 0x40b  /*  Weggeber der Spritzachse 1 defekt            */
#define FK_DRutAuf 0x40c  /*  Drehzahlgeber der Plast. 1 defekt            */
#define FK_MOeIShz 0x40d  /*  Stoerung am Motor-Sicherheitsschuetz         */
#define FK_SPS     0x40e  /*  Keine gueltigen Werte in der SPS             */
#define FK_SLmsSpn 0x40f  /*  Werkzeug auf Spannhubposition fahren         */
#define FK_FH_Blck 0x410  /*  Werkzeughoehenverstellung blockiert          */
#define FK_SL_Reib 0x411  /*  Zu grosse Reibung am Werkzeug                */
#define FK_WSutFSS 0x412  /*  Werkzeugsicherung                            */
#define FK_FSS_Ref 0x413  /*  Wkz-Sicherungs-Referenzzyklus fehlt          */
#define FK_PL_Verr 0x414  /*  Plastifizieren-Verriegelungsfehler           */
#define FK_SIe_Lsw 0x415  /*  Lichtschranke/Ausfallwaage                   */
#define FK_MOaHptS 0x416  /*  Motoren ausschalten - dann Hauptschalter     */
#define FK_MOa_Not 0x417  /*  Motoren ausgeschaltet nach NOT-STOP          */
#define FK_HZa_Not 0x418  /*  Heizung ausgeschaltet nach NOT-STOP          */
#define FK_ZHm_Abs 0x419  /*  Temp.Absenkung Zyl.Heizung laeuft            */
#define FK_SNikOk  0x41a  /*  Schneckenfreigabe fehlt                      */
#define FK_MOe_Ein 0x41b  /*  Motoren nicht eingeschaltet                  */
#define FK_ZHa_Aus 0x41c  /*  Zylinderheizungen nicht eingeschaltet        */
#define FK_AWs_WO  0x41d  /*  Ausw.- Hub oder \\ffnungsweite falsch        */
#define FK_AWe_Zur 0x41e  /*  Auswerferplattensicherung                    */
#define FK_AWRfErr 0x41f  /*  Auswerfer-Referenzschalterfehler             */
#define FK_ZYe_Ext 0x420  /*  Zyklusstop extern                            */
#define FK_AWmlWrn 0x421  /*  Erhoehte Leistung bei Auswerferachse         */
#define FK_SLmlWrn 0x422  /*  Erhoehte Leistung bei Schliessachse          */
#define FK_AGmlWrn 0x423  /*  Erhoehte Leistung bei Aggregatachse 1        */
#define FK_PLmlWrn 0x424  /*  Erhoehte Leistung bei Plastifizierachse 1    */
#define FK_SPmlWrn 0x425  /*  Erhoehte Leistung bei Einspritzachse 1       */
#define FK_AWmlErr 0x426  /*  Ueberlastung der Auswerferachse              */
#define FK_SLmlErr 0x427  /*  Ueberlastung der Schliessachse               */
#define FK_AGmlErr 0x428  /*  Ueberlastung der Aggregatachse 1             */
#define FK_PLmlErr 0x429  /*  Ueberlastung der Plastifizierachse 1         */
#define FK_SPmlErr 0x42a  /*  Ueberlastung der Einspritzachse 1            */
#define FK_WHm_Abs 0x42b  /*  Werkzeug Temperaturabsenkung laeuft          */
#define FK_TempFBr 0x42c  /*  Temperaturf}hlerbruch Elektroschrank         */
#define FK_AWS99F  0x42d  /*  AWS - Speicherplatz zu 99% voll              */
#define FK_CabTemp 0x42e  /*  Temp. im Elektroschrank ist zu hoch          */
#define FK_SLkEinr 0x42f  /*  Schlie~kraft im Einrichtbetrieb aktiv        */
#define FK_PLssEnd 0x430  /*  Plastifizierweg Agg 1 }berschritten          */
#define FK_ZYutTi1 0x431  /*  Zykluszeit ueberschritten                    */
#define FK_ZYutTi2 0x432  /*  Zykluszeit zum 2. Mal ueberschritten         */
#define FK_PLutTim 0x433  /*  Plast.-Zeit Agg. 1 ueberschritten            */
#define FK_QUm_Tol 0x434  /*  Produkt ausserhalb der Toleranz              */
#define FK_Maschab 0x435  /*  Automatische Maschinenabschaltung laeuft     */
#define FK_AWSFull 0x436  /*  AWS - Speicherplatz voll                     */
#define FK_OelNiv  0x437  /*  Oelniveau der Schmierung zu niedrig          */
#define FK_OelDr1  0x438  /*  Druckschalterfehler Gelenksystemschmierung   */
#define FK_OelDr2  0x439  /*  Druckschalterfehler Getriebeumlaufschmierung */
#define FK_RealTim 0x43a  /*  Echtzeituhr Fehler in der SPS                */
#define FK_ROe_wo  0x43b  /*  Start Werkzeug |ffnen vom HG fehlt           */
#define FK_ROe_ws  0x43c  /*  Start Werkzeug schlie~en vom HG fehlt        */
#define FK_ROe_si  0x43d  /*  Freigabe Werkzeugbewegung vom HG fehlt       */
#define FK_ROe_awv 0x43e  /*  Freigabe Auswerfer-Vorbewegung vom HG fehlt  */
#define FK_ROe_awz 0x43f  /*  Freigabe Auswerfer R}ckbewegung vom HG fehlt */
#define FK_TstZykl 0x440  /*  Testzyklus aktiv                             */
#define FK_ZHTmpkl 0x441  /*  Zylindertemperaturen unter 150 [C            */
#define FK_DR1Frg  0x442  /*  Freigabestoerung im Schliessdrive            */
#define FK_DR2Frg  0x443  /*  Freigabestoerung im Spritzdrive 1            */
#define FK_SLRfErr 0x444  /*  Schliessachse-Referenzschalterfehler         */
#define FK_SPRfErr 0x445  /*  Einspritzachse-Referenzschalterfehler Agg 1  */
#define FK_GKk_Off 0x446  /*  Gelenkkopfkraft Offset Fehler                */
#define FK_SEp_Off 0x447  /*  Einspritzdruck Offset Fehler                 */
#define FK_WHa_Aus 0x448  /*  Werkzeugheizung nicht eingeschaltet          */
#define FK_Einr    0x449  /*  Einrichten betaetigen                        */
#define FK_DR1Temp 0x44a  /*  Motoruebertemperatur am Schliessdrive        */
#define FK_DR2Temp 0x44b  /*  Motoruebertemperatur am Spritzdrive Agg 1    */
#define fagsich1   0x44c  /*  Sicherheitssch}tz 2-K0588 defekt             */
#define FK_AGe2Tur 0x44d  /*  hinterer D}senschutz nicht geschlossen       */
#define FK_EXTnIni 0x44e  /*  Schnittstelle Temp.Ger{t nicht initialisiert */
#define FK_EXTDat  0x44f  /*  St|rung Datacom Temp.Ger{t                   */
#define FK_EXTemp  0x450  /*  St|rung ext. Temp.Ger{t                      */
#define FK_CDwblk  0x451  /*  Werkzeugbewegung von extern blockiert        */
#define FK_CDHGne  0x452  /*  Entnahme-HG Kupplung nicht entriegelt        */
#define FK_CDHGnv  0x453  /*  Entnahme-HG Kupplung nicht verriegelt        */
#define FK_CDHGnCD 0x454  /*  Entnahme-HG hat CD nicht gegriffen           */
#define FK_CDHGnAG 0x455  /*  Entnahme-HG hat Angu~ nicht gegriffen        */
#define FK_CDFHGn  0x456  /*  Folge-HG hat CD nicht gegriffen              */
#define FK_CDMwech 0x457  /*  Bitte Matrize wechseln                       */
#define FK_DR4Temp 0x458  /*  Motor}bertemperatur am Plastifizierdrive     */
#define FK_DR4Err  0x459  /*  Stoerung im Drive der Auswerfereinheit  */
#define FK_AG_Aufn 0x45a  /*  Druckaufnehmer D}senanlage au~er Toleranz    */
#define FK_IOe_DI1 0x45b  /*  Freigabe von konf. digitaler Eingang 1 fehlt  */
#define FK_IOe_DI2 0x45c  /*  Freigabe von konf. digitaler Eingang 2 fehlt  */
#define FK_IOe_DI3 0x45d  /*  Freigabe von konf. digitaler Eingang 3 fehlt  */
#define FK_IOe_DI4 0x45e  /*  Freigabe von konf. digitaler Eingang 4 fehlt  */
#define FK_NoAbGlP 0x45f  /*  keine Abgleichparameter vorhanden            */
#define FK_SPSDiag 0x460  /*  SPS in Betriebsart DIAGNOSE                  */
#define FK_EinrHd  0x461  /*  Einrichten oder Handbetrieb anwaehlen        */
#define FK_ZYe_Los 0x462  /*  Bitte Starttaste betaetigen                  */
#define FK_FHmin   0x463  /*  Min. Werkzeugeinbauh|he unterschritten       */
#define FK_FHmax   0x464  /*  Max. Werkzeugeinbauh|he }berschritten        */
#define FK_GKSchm  0x465  /*  St|rung Gelenkschmiersystem                  */
#define FK_NDpBegr 0x466  /*  Nachdruck wurde begrenzt                     */
#define FK_SerIni  0x467  /*  Fehlerbit Serielle Schnittstelle nicht initialisiert  */
#define FK_SerCom  0x468  /*  Fehlerbit St|rung Datacom externe Heizung  */
#define FK_SerExt  0x469  /*  Fehlerbit St|rung externe Heizung  */
#define FK_SerPro  0x46a  /*  Fehlerbit Protokoll externe Heizung nicht verf]gbar  */
#define FK_Karton1 0x46b  /*  Fehlerbit Karton auf Position 1 fehlt        */
#define FK_SnBlock 0x46c  /*  Fehlerbit Schneckenanlaufsicherung aktiv     */
#define FK_DR3Err  0x46d  /*  Stoerung im Drive der Plastifiziereinheit    */
#define FK_APeAktiv 0x46e  /*  Airpress noch aktiv  */
#define FK_APStoer 0x46f  /*  St|rung Airpress  */
#define FK_APpeSysT 0x470  /*  Fehler Systemdruck Airpressanlage  */
#define FK_XSm_Anf 0x471  /*  Fehlerbit Produktionsstart: Parameter aktiv  */
#define FK_XSm_An2 0x472  /*  Fehlerbit Produktionsstart: WKZ-Sicherungsdruck aktiv  */
#define FK_SLVerr1 0x473  /*  Werkzeug-Verriegelungsfehler (]berstrom)     */
#define FK_SLVerr2 0x474  /*  Werkzeug-Verriegelungsfehler (Haltestrom)    */
#define FK_SLVerr3 0x475  /*  Werkzeug-Verriegelungsfehler (Minimalstrom)  */
#define FK_FSSTolN 0x476  /*  FSS-Toleranz kleiner Null  */
#define FK_SE1WegM 0x477  /*  Wegmesssystem Spritzeinheit 1 defekt           */
#define FK_SE1NAct 0x478  /*  Nullpunktabgl. Spritzeinh.1 nicht aktiv        */
#define fa1ruh     0x479  /*  Aggregat 1 nicht in hinterer Lage              */
#define foeln      0x47a  /*  Oelniveau zu niedrig                           */
/*------------------- Fehlermeldung Werkzeugauswerfer,Wenden -------------- */
#define FK_DTnRef  0x47b  /*  Drehteller nicht referenziert                  */
#define FK_EndWend 0x47c  /*  Fehler Endlage Wenden                          */
#define FK_BlWend  0x47d  /*  Fehler Blockierung Wenden                      */
#define FK_SPWend  0x47e  /*  Fehler Startpunkt Wenden                       */
#define FK_EPkOver 0x47f  /*  Ziel }berfahren                                */
#define FK_ELnFix  0x480  /*  Endlage nicht fixiert                          */
#define FK_DTBlock 0x481  /*  Drehteller blockiert                           */
#define FK_WZAvBl  0x482  /*  Werkzeugauswerfer 1 vor blockiert              */
#define FK_WZAzBl  0x483  /*  Werkzeugauswerfer 1 zur}ck blockiert           */
#define FK_WZAEChk 0x484  /*  Endlage Werkzeugauswerfer 1 pr}fen             */
/*------------------------------------------------------------------------- */
#define FK_WZA2vbl 0x485  /*  FK: Werkzeugauswerfer 2 vor blockiert     */
#define FK_WZA2zbl 0x486  /*  FK: Werkzeugauswerfer 2 zur}ck blockiert  */
#define FK_WZA2epr 0x487  /*  FK: Endlage Werkzeugauswerfer 2 pr}fen    */
#define FK_TstAgg2 0x488  /*  FK: Zusatztasten Seitenaggregat aktiv     */
#define FK_Ag2Sich 0x489  /*  FK: Absicherung Nebenaggregat             */
#define FK_pUebers 0x48a  /*  FK: Fehler Druck}bersetzer                */
#define FK_WEsmird 0x48b  /*  FK: Schmierdruck Drehteller nicht erreicht    */
#define FK_Quit    0x48c  /*  FK: Bitte Quittiertaste bet{tigen             */
#define FK_QuitBgS 0x48d  /*  FK: Quittiertaste Bediengegenseite bet{tigen  */
#define FK_QuitBS  0x48e  /*  FK: Quittiertaste Bedienseite bet{tigen       */
#define FK_NeHi    0x48f  /*  FK: Monoaggregat nicht in richtiger Stellung  */
#define FK_SNikOkM 0x490  /*  FK: Schneckenfreigabe Monoaggregat fehlt      */
#define FK_ZHmAbNI 0x491  /*  FK: Temperaturabsenkung Monoaggregat l{uft    */
#define FK_ZHm_AuM 0x492  /*  FK: Heizung Monoaggregat ausgeschaltet        */
#define FK_Arret   0x493  /*  FK: Arretierung l|sen                         */
#define FK_mechSsp 0x494  /*  FK: Mechanische Schlie~sperre                 */
#define FK_mSpESdf 0x495  /*  FK: Mechanische Schlie~sperre Endschalter defekt  */
#define FK_Einrich 0x496  /*  FK: Einrichten bet{tigen                          */
#define FK_KEAWoSt 0x497  /*  FK: Kernzug und Auswerfer bei offener Schutzt}r   */
#define FK_SPZylnP 0x498  /*  FK: Spannzylinder nicht in Position               */
#define FK_BAP44pr 0x499  /*  FK: Betriebsart Seite 44 pr}fen                   */
#define FK_Mischk  0x49a  /*  FK: Fehler Mischkopfbetrieb                       */
#define FK_Wpktnpl 0x49b  /*  FK: Wegpunkt nicht plausibel                      */
#define FK_UwWkzBw 0x49c  /*  FK: ]berwachung Werkzeugbewegung                  */
#define FK_UwAWBew 0x49d  /*  FK: ]berwachung Auswerferbewegung                 */
#define FK_ParProd 0x49e  /*  FK: Parameter Produktionsstart                    */
#define FK_WS2WTdf 0x49f  /*  FK: Wegmesssystem 2 Wendetisch defekt             */
#define FK_CanWink 0x4a0  /*  Fehlerbit Fehler Winkelkodierer                   */
#define FK_AgMoTmp 0x4a1  /*  \\ltemperatur Aggregatbewegung zu hoch            */
#define FK_DRV5Err 0x4a2  /*  St|rung im Drive der Wendeeinheit                 */
/*------------------------------------------------------------------------- */
#define FK_ZHAnf1  0x4a3  /*  Zylinderheiz.-Anfahrschaltung Agg.1 l{uft  */
/*------------------------------------------------------------------------- */
#define FK_WEsmirl 0x4a4  /*  FK: Schmierung Beh{lter Drehteller leer       */
#define FK_KZ_Aufn 0x4a5  /*  FK: Drucksensor Kernzug au~er Toleranz        */
#define FK_WEZsErr 0x4a6  /*  FK: Drehtellerschmierung gest|rt              */
#define FK_SEUebWa 0x4a7  /*  FK: Einspritzen von Spritzdrucküberwachung abgebrochen */
#define FK_End     0x4a8  /* Dummy Bit, Bitnummer for last faultbit */

/*** symgen EOF: last=0x4a7, count=1, (B=149, R=2384) ***/
