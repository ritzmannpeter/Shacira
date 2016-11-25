/*.SS.***********************************************************************
*
*  BESCHREIBUNG:
*
*  HISTORY:
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
*     24.07.96 -HAns-   IQSSonBit0 bis IQSSonBit9 und ZYitAnalys eingefuegt.
*                       SLdpSDREin und SLm_SDREin eingefuegt.
*     13-09-96 -PR-     Symboldefinition fuer frei progr.bare Kernzuege (KE..).
*     06.12.96 -HAns-   fagsich1-4, FK_PLiv1Ak-FK_PLiv4Ak und FK_FHmin eingefuegt.
*     19.12.96 -HAns-   Diagnosebits Seite 87.6 DOsforce01 - 32 eingefuegt.
*     09.01.97 -TSchw-  Sonderbits gil_optbit.. und gil_istbit.. fuer 
*                       Gillette angelegt
*     13.01.97 -TSchw-  Sonderbits gil_optbit16 - 31 angelegt
*     16.01.97 -HAns-   FK_WTabgel, FK_SPSDiag und FK_NoWZBew angelegt.
*     17.01.97 -TSchw-  Sonderbits gil_istbit17 - 48 angelegt
*     03.02.96  -HAns-   IQSSonBit0-9 nach IQsSonBit0-9 geaendert.
*     03.02.97 -HAns-   Mehrfarbmaschinenbits fweg12 bis fsnek4 angelegt.
*     05.02.97 -HAns-   FK_AWS99F und FK_AWSFull angelegt.
*     13.02.97 -HAns-   OP_DV7 angelegt.
*     15.02.97 -HAns-   An MF-Maschinen angepasst.
*     05.03.97 -HAns-   PLs_Rampe angelegt.
*     06.03.97 -HAns-   PLs_Rampe2 bis 4 angelegt.
*     27.10.97 -HAns-   force600 - 61f, force700 - 71f, force800 - 81f und
*                       FK_PMmin eingefuegt.
*                       Freigabebit POmFoerder fuer Seite 71.0 eingefuegt.
*                       Optionsbits OPmF_Pack und OPmFP_Pack eingefuegt.
*                       Fehlerbit FK_DrSB707 eingefuegt.
*     20.11.97 -HAns-   force600 - 61f, force700 - 71f, force800 - 81f und
*                       DOsforce01 - 32 entfernt.
*                       Adressbereich Istbits von 0x120 nach 0x100 und 
*                       Fehlerbits von 0x160 nach 0x150 verlegt.
*                       Adressbereich fuer freieditierbaren Kernzug von 0x200
*                       nach 0x1f0 und Gillette-Sonderbits von 0x250 nach 0x240
*                       geaendert.
*     28.11.97 -HAns-   Bits der Seiten 87.1 und 87.2 herausgenommen:
*                       Iy9008soll, Iy90081soll, Iy9016soll, Iy9017soll, Iy9009soll
*                       Iy9025soll, Iy90251soll, Iy9026soll,
*                       Iy9008ist, Iy90081ist, Iy9016ist, Iy9017ist, Iy9009ist,
*                       Iy9025ist, Iy90251ist, Iy9026ist, Iy9020ist, Iy9010ist,
*                       Iy9014ist, Iy90141ist, Iy9023ist, Iy9011ist, I5f1ist,
*                       Iy9002ist, Iy9001ist, Iy90011ist
*     08.08.00 -HAns-   An QNX2-Symboltabelle angepasst.
*     10.07.02 -HA-     Bits fuer Wenden und Werkzeugauswerfer eingefuegt.
*                       OPm_Luft8, OPm_IQT350, OPm_IQT399 und OPm_Karton eingefuegt.
*                       FK_SerIni, FK_SerCom, FK_SerExt, FK_SerPro und FK_Karton1 eingefuegt.
*     11.07.02 -HA-     FK_PLeDrive, FK_PLeInit, FK_PLeTemp, FK_PLePower und FK_PLeWarn eingefuegt. 
*                       OPm_EPlast eingefuegt.
*                       QUm_IQTfrd     71.0 SPS-Freigabebit Foerderband  
*     12.07.02 -HA-     SEAbglST1 bis SEAbglRS2 und SEAbglTas1,2 eingefuegt.      
*                       FK_SE1WegM bis FK_SE2NAct eingefuegt.
*                       OPm_IQT800     SPS_IQT-Option Kuehlwasser-Abschaltung Seite 80
*                       FK_IOe_DI1 bis FK_IOe_DI4 eingefuegt                  
*                       OPmAOIqt, OPm_DIOIqt, OPm_Iqt710, SGm_SetPos, FK_SGErr1,2, FK_SGRef und HXsnEcho eingefuegt.
*     15.07.02 -HA-     OPm_Airpr, OPm_APProp, OPm_APip, FK_APeAktiv, FK_APStoer und FK_APpeSysT eingefuegt.
*     22.08.02 -HA-     FK_SpStell, fmots2, fmot132, FK_SGm1Tur, FK_SGm2Tur und FK_SGm1SS eingefuegt.
*     02.10.02 -HA-     OP_WkzAus2, WZA2Chkvor, WZA2Chkzur und WZA2ChkFSS eingefuegt.
*                       FK_WZA1vbl bis FK_WZA2epr eingefuegt.
*     20.11.02 -HA-     FK_TstAgg2, FK_Ag2Sich, FK_WEsmird, FK_WEsmirl, FK_Quit, FK_QuitBgS, FK_QuitBS, FK_NeHi, FK_SNikOkM,
*                       FK_ZHmAbNI, FK_ZHm_AuM, FK_Arret  , FK_mechSsp, FK_mSpESdf, FK_Einrich, FK_KEAWoSt, FK_SPZylnP,
*                       FK_BAP44pr, FK_Mischk , FK_Wpktnpl, FK_UwWkzBw, FK_UwAWBew, FK_ParProd, FK_WS2WTdf, FK_pUebers eingefuegt.
*                       gil_istbit48 - 63 angelegt  
*     25.11.02 -HA-     HXsnEcho_2 eingefuegt.
*     10.03.03 -HA-     Fehlermeldungen eingefuegt FK_XSm_Anf und FK_XSm_An2
*                       OBIQTPLC1 bis OBIQTPLC16 eingefuegt.
*     12.03.03 -HA-     OP_CanWink und FK_CanWink eingefuegt.
*
*
*  VERSION:                                                         
*     VERSION:  1.0              AUTOR:       T.Schwoerer           
*     DATUM:    08.06.89         TELEFON 2i:  0721/25785            
*                                                                   
*  UMGEBUNG:                                                        
*     ZIELRECHNER:          Philips IQT-450                         
*     PROGRAMMIERSPRACHE:   CI C86 V3.3                             
*                                                                   
*  BEMERKUNGEN:                                                     
*     ACHTUNG   ACHTUNG  ACHTUNG ACHTUNG  ACHTUNG   ACHTUNG   ACHTUNG
*        Diese Tabelle ist nur fuer die B & R -Steuerung gueltig
*
**.EM.**********************************************************************/

/*------------------- Sollbits (Downloadbits) ------------------------------*/
#define ddummi      0x000  /* Dummy-Bit                                     */
#define dkzon       0x001  /* Kernzugprogramm ein/aus  S.61                 */
#define k1epar      0x002  /* wird gesetzt bei XSSFZU3                      */
#define k1apar      0x003  /* wird gesetzt bei XSSFAU9                      */
#define k2epar      0x004  /* wird gesetzt bei XSFZSTP                      */
#define k2apar      0x005  /* wird gesetzt bei XSFASTP                      */
#define miheie      0x006  /* Ein/Ausschaltbit fuer Heizung ein             */
#define mimote      0x007  /* Ein/Ausschaltbit fuer Motor ein               */
#define miext1      0x008  /* Ein/Ausschaltbit fuer Externes Geraet 1 ein   */
#define miext2      0x009  /* Ein/Ausschaltbit fuer Externes Geraet 2 ein   */
#define ROm_Type    0x00a  /* Handlinggeraet Type Rx10/Rx20                 */
#define ROm_AusGrf  0x00b  /* Handlinggeraet Auswerfer vor/nach Greifer     */
#define bxsoll      0x00c  /*                                               */
#define ROm_AusHub  0x00d  /* Handlinggeraet: Auswerfer Einf./Mehrfachhub   */
#define ROm_BCAxis  0x00e  /* Handlinggeraet: mit/ohne B_C Achse            */
#define ROm_TContr  0x00f  /* Handlinggeraet: mit/ohne Teilekontrolle       */
#define ROm_Vakuum  0x010  /* Handlinggeraet: Vakuum aus/ein                */
#define ROm_Zange   0x011  /* Handlinggeraet: Zange aus/ein                 */
#define ROm_SondAng 0x012  /* Handlinggeraet: Anguss separieren ein/aus     */
#define ROm_SondSch 0x013  /* Handlinggeraet: Jeder zweite Schuss ??        */
#define ROm_An      0x014  /* Handlinggeraet an/aus                         */
#define DIm_ForOn   0x015  /* Diagnosemode Forcemode enable                 */
#define SNm_ErhNm   0x016  /* erhoehtes Schneckendrehmoment Agg.1           */
#define DIm_Init    0x017  /* Init SPS                                      */
#define DIm_Clear   0x018  /* loeschen aller Force Werte                    */
#define ezhasc      0x019  /* Schnellkupplung fuer Auswerfer-Ruhelage HASCO */
#define miheia      0x01a  /* Ein/Ausschaltbit fuer Heizung aus             */
#define mimota      0x01b  /* Ein/Ausschaltbit fuer Motor aus               */
#define miex1a      0x01c  /* Ein/Ausschaltbit fuer Externes Geraet 1 aus   */
#define miex2a      0x01d  /* Ein/Ausschaltbit fuer Externes Geraet 2 aus   */
#define dschwe      0x01e  /* Schneckenwechsel  aus=0 ein=1  S.49 Agg.1     */
#define dschw2      0x01f  /* Schneckenwechsel  aus=0 ein=1  S.49 Agg.2     */
#define maswnp      0x020  /* Startbit Auswerfernullpunktabgleich           */
#define d4b5        0x021  /* Ruhelage Ueberwachung         S.52            */
#define mtolue      0x022  /* zuruecksetzen wenn Toleranzueberwachungsfehler*/
#define mtomax      0x023  /* Maximum Toleranzueberschreitung erreicht      */
#define dtol1       0x024  /* wird gesetzt abhaengig vom Ergebnis der       */
                           /* Toleranzueberpruefung                         */
#define dmaus       0x025  /* Automatische Maschinenabschaltung S.80        */
#define doelhz      0x026  /* Oelvorwaermung S.15                           */
#define dopt        0x027  /* Wahlbit optische Werkzeugsicherung            */
#define danf        0x028  /* Einschaltbit Werkzeugheizung                  */
#define dlager      0x029  /* Staudruckentlastung S. 40          Agg.1      */
#define dduese      0x02a  /* Hydraulische Verschlussduese S 40  Agg.1      */
#define dlagr2      0x02b  /* Staudruckentlastung S. 40          Agg.2      */
#define ddues2      0x02c  /* Hydraulische Verschlussduese S 40  Agg.2      */
#define dauswr      0x02d  /* Auswerfer gerastet ja/nein S.52               */
#define dlicht      0x02e  /* Lichtschranke Ausfallwaage S.80               */
#define dkeinz      0x02f  /* Signal Kern Einfahren ueber Endschalter oder  */
#define dkausz      0x030  /* Signal Kern ausgefahren  S.61.1               */
#define dk1eid      0x031  /* Zustand nach Kern eingefahren      S.61       */
#define dk2eid      0x032  /* Zustand nach Kern eingefahren      S.62       */
#define dk1aud      0x033  /* Zustand nach Kern ausgefahren      S.61.1     */
#define dk2aud      0x034  /* Zustand nach Kern ausgefahren      S.62.1     */
#define dkei2z      0x035  /* Signal Kern eingefahren S.62                  */
#define dkau2z      0x036  /* Signal Kern ausgefahren S.62.1                */
#define ensdtr      0x037  /* Handschakebit fuer Heizungssollwertdatacom    */
#define dplafo      0x038  /* Bewegung parallel plastifizieren aus=0  S.51  */
#define msuzer      0x039  /* Produktionsende                               */
#define enkrqd      0x03a  /* Kommunikationsbit Heizung                     */
#define mextsi      0x03b  /* Merker externes Signal                        */
#define mtianf      0x03c  /* wird gesetzt, wenn ISCOS anfahren fertig ist  */
#define WAs_Uebv    0x03d  /* Wkz-Ausw Ueberwachung vorne Endschalter/Zeit  */
#define WAs_Uebz    0x03e  /* Wkz-Ausw Ueberwachung zurueck Endschalter/Zeit*/
#define WAs_fss     0x03f  /* Wkz-Ausw Ueberwachung erst mit fss            */
#define dwsp01      0x040  /* Wahlbit fuer Spritzeinheit 1 S.44             */
#define dwsp02      0x041  /* Wahlbit fuer Spritzeinheit 2 S.44             */
#define dwsp03      0x042  /* Wahlbit fuer Spritzeinheit 3 S.44             */
#define dwsp04      0x043  /* Wahlbit fuer Spritzeinheit 4 S.44             */
#define dwsp12      0x044  /* Wahlbit fuer Wahl Spritzeinheit S.44 (2F)     */
#define dwspps      0x045  /* Wahlbit fuer Betriebsart Einspritzen S.44 (2F)*/
#define dwsprf      0x046  /* Wahlbit fuer Reihenfolge Einspritzen S.44 (2F)*/
#define dwagps      0x047  /* Wahlbit fuer Betriebsart Aggregatbew. S.44 (2F)*/
#define dwagrf      0x048  /* Wahlbit fuer Reihenfolge Aggregatbew. S.44 (2F)*/
/* ------------------ Qualitaetskontrolle --------------------------------- */
#define QUsnsub     0x049  /* Subtrahierender Schusszaehler unterbrechen    */
#define QUsnexz     0x04a  /* Externer Zykl.zaehler unterbrechen            */
#define QUsninv     0x04b  /* Inversbetrieb                                 */
/*------------------- Selektierweiche ------------------------------------- */
#define QUs_SprAng  0x04c  /* Spritzling selektieren                        */
#define QUs_Invers  0x04d  /* Inversbetrieb                                 */
/*------------------ Sonderbits --------------------------------------------*/
#define IQsSonBit0  0x04e  /* Soll-Sonderbit 0                              */
#define IQsSonBit1  0x04f  /* Soll-Sonderbit 1                              */
#define IQsSonBit2  0x050  /* Soll-Sonderbit 2                              */
#define IQsSonBit3  0x051  /* Soll-Sonderbit 3                              */
#define IQsSonBit4  0x052  /* Soll-Sonderbit 4                              */
#define IQsSonBit5  0x053  /* Soll-Sonderbit 5                              */
#define IQsSonBit6  0x054  /* Soll-Sonderbit 6                              */
#define IQsSonBit7  0x055  /* Soll-Sonderbit 7                              */
#define IQsSonBit8  0x056  /* Soll-Sonderbit 8                              */
#define IQsSonBit9  0x057  /* Soll-Sonderbit 9                              */
#define dlagr3      0x058  /* Staudruckentlastung S. 40          Agg.3      */
#define ddues3      0x059  /* Hydraulische Verschlussduese S 40  Agg.3      */
#define dlagr4      0x05a  /* Staudruckentlastung S. 40          Agg.4      */
#define ddues4      0x05b  /* Hydraulische Verschlussduese S 40  Agg.4      */
#define dschw3      0x05c  /* Schneckenwechsel  aus=0 ein=1  S.49 Agg.3     */
#define dschw4      0x05d  /* Schneckenwechsel  aus=0 ein=1  S.49 Agg.4     */
#define SNm_ErhNm2  0x05e  /* erhoehtes Schneckendrehmoment Agg.2           */
#define SNm_ErhNm3  0x05f  /* erhoehtes Schneckendrehmoment Agg.3           */
#define SNm_ErhNm4  0x060  /* erhoehtes Schneckendrehmoment Agg.4           */
/* ------------------ Optionsbit fuer DV7 --------------------------------- */
#define OB_DV7      0x061  /* Optionsbit fuer DV7                           */
/* ------------------ Optionsbit fuer Vertikalaggregat 2 bis 4 ------------ */
#define OB_VAgg2    0x062  /* Optionsbit fuer Vertikal Aggregat 2           */
#define OB_VAgg3    0x063  /* Optionsbit fuer Vertikal Aggregat 3           */
#define OB_VAgg4    0x064  /* Optionsbit fuer Vertikal Aggregat 4           */
/* ------------------ Werkzeugauswerfer ----------------------------------- */
#define WZA_Chkvor  0x065  /* Ueberwachung Auswerfer vor     S.53.0, Z. 9   */
#define WZA_Chkzur  0x066  /* Ueberwachung Auswerfer zurueck S.53.0, Z.10   */
#define WZA_ChkFSS  0x067  /* Endlageueberwachung mit FSS-B. S.53.0, Z.13   */
/* ------------------ Werkzeugauswerfer 2 --------------------------------- */
#define WZA2Chkvor  0x068  /* Ueberwachung Auswerfer vor     S.53.1, Z. 9   */
#define WZA2Chkzur  0x069  /* Ueberwachung Auswerfer zurueck S.53.1, Z.10   */
#define WZA2ChkFSS  0x06a  /* Endlageueberwachung mit FSS-B. S.53.1, Z.13   */
/* ------------------ Werkzeug Wenden ------------------------------------- */
#define WDmpEndlag  0x06b  /* Zustand Endlage Wenden         S.57.0, Z.11   */
#define WDm_Funkrs  0x06c  /* Funktion Wenden (geregelt/gest.)S.57.0 Z.16   */
/* ---------------- Werkzeug Drehteller-Parameter ------------------------- */
#define DTszSpumk   0x06d  /* Spannungsumkehr                S.57.1  Z.16   */
#define DTszDrumk   0x06e  /* Drehrichtungsumkehr            S.57.1  Z.17   */
/* ------------------------------------------------------------------------ */
#define HXsnEcho    0x06f  /* Echobit S. 39.9 */
#define HXsnEcho_2  0x070  /* Echobit S. 39.9 */
/* ------------------ sonstige Kommunikationsbits ------------------------- */
#define mfohoe      0x071  /* Startbit fuer Formhoehenabgleich              */
#define WZm_HAnf    0x072  /* Formhoehe nicht eingestellt                   */
#define HEm_Start   0x073  /* Heizungsoptimierung starten                   */
#define SLdpSDREin  0x074  /* Schlie~druck im Einrichten anfordern          */
#define PLs_Rampe   0x075  /* Plastifizier-Rampe Ein/Ausschalten 1.Agg      */
#define PLs_Rampe2  0x076  /* Plastifizier-Rampe Ein/Ausschalten 2.Agg      */
#define PLs_Rampe3  0x077  /* Plastifizier-Rampe Ein/Ausschalten 3.Agg      */
#define PLs_Rampe4  0x078  /* Plastifizier-Rampe Ein/Ausschalten 4.Agg      */
/* ---------------- Seite 49.0 mit Wegmesslineal -------------------------- */
#define SEAbglST1   0x079  /* Start Spritzeinheitabgleich 1                 */
#define SEAbglRS1   0x07a  /* Ende  Spritzeinheitabgleich 1                 */
#define SEAbglST2   0x07b  /* Start Spritzeinheitabgleich 2                 */
#define SEAbglRS2   0x07c  /* Ende  Spritzeinheitabgleich 2                 */
/* ------------------------------------------------------------------------ */
#define SGm_SetPos  0x07d  /* Komunikation fuer Zwischenposition Schutztuer S. 71.0 */
/* ------------------------------------------------------------------------ */
#define OBIQTPLC1   0x07e  /* IQT/SPS-Optionsbit 1                          */
#define OBIQTPLC2   0x07f  /* IQT/SPS-Optionsbit 2                          */
#define OBIQTPLC3   0x080  /* IQT/SPS-Optionsbit 3                          */
#define OBIQTPLC4   0x081  /* IQT/SPS-Optionsbit 4                          */
#define OBIQTPLC5   0x082  /* IQT/SPS-Optionsbit 5                          */
#define OBIQTPLC6   0x083  /* IQT/SPS-Optionsbit 6                          */
#define OBIQTPLC7   0x084  /* IQT/SPS-Optionsbit 7                          */
#define OBIQTPLC8   0x085  /* IQT/SPS-Optionsbit 8                          */
#define OBIQTPLC9   0x086  /* IQT/SPS-Optionsbit 9                          */
#define OBIQTPLC10  0x087  /* IQT/SPS-Optionsbit 10                         */
#define OBIQTPLC11  0x088  /* IQT/SPS-Optionsbit 11                         */
#define OBIQTPLC12  0x089  /* IQT/SPS-Optionsbit 12                         */
#define OBIQTPLC13  0x08a  /* IQT/SPS-Optionsbit 13                         */
#define OBIQTPLC14  0x08b  /* IQT/SPS-Optionsbit 14                         */
#define OBIQTPLC15  0x08c  /* IQT/SPS-Optionsbit 15                         */
#define OBIQTPLC16  0x08d  /* IQT/SPS-Optionsbit 16                         */

/* ------------------------------------------------------------------------ */
/* $$$ Istbits                                                              */          
/* ------------------------------------------------------------------------ */
#define dsusei      0x100  /* Sub. Schusszaehler ruecksetzen                */
#define drads1      0x101  /* Add. Schusszaehler ruecksetzen                */
#define dexrs       0x102  /* Externes Signal reset neustart                */
#define msigex      0x103  /* Merker um Signal extern zu sperren            */
#define msszsp      0x104  /* Merker um sub. Schusszaehler zu sperren       */
#define ROm_GrdSt   0x105  /* Robot ist (nicht) in Grundstellung            */
#define DIm_For     0x106  /* Force Mode erlaube Bit                        */
#define mftrks      0x107  /* wenn dieses Bit gesetzt ist, werden die       */
#define maswok      0x108  /* Iscosfreigabe fuer Auswerfer                  */
#define msum11      0x109  /* Wegumschaltbit fuer Spritzwerte Phase 1       */
#define msum12      0x10a  /* Wegumschaltbit fuer Spritzwerte Phase 2       */
#define msum13      0x10b  /* Wegumschaltbit fuer Spritzwerte Phase 3       */
#define msum14      0x10c  /* Wegumschaltbit fuer Spritzwerte Phase 4       */
#define msum15      0x10d  /* Wegumschaltbit fuer Spritzwerte Phase 5       */
#define mtum11      0x10e  /* Zeitumschaltbit fuer Spritzwerte Phase 1      */
#define mtum12      0x10f  /* Zeitumschaltbit fuer Spritzwerte Phase 2    */
#define mtum13      0x110  /* Zeitumschaltbit fuer Spritzwerte Phase 3    */
#define mtum14      0x111  /* Zeitumschaltbit fuer Spritzwerte Phase 4    */
#define mtum15      0x112  /* Zeitumschaltbit fuer Spritzwerte Phase 5    */
#define mtum16      0x113  /* Zeitumschaltbit fuer Spritzwerte Phase 6    */
#define mpum11      0x114  /* Druckumschaltbit fuer Spritzwerte Phase 1   */
#define mpum12      0x115  /* Druckumschaltbit fuer Spritzwerte Phase 2   */
#define mpum13      0x116  /* Druckumschaltbit fuer Spritzwerte Phase 3   */
#define mpum14      0x117  /* Druckumschaltbit fuer Spritzwerte Phase 4   */
#define mpum15      0x118  /* Druckumschaltbit fuer Spritzwerte Phase 5   */
#define meinr       0x119  /* Einrichten                                  */
#define mhand       0x11a  /* Handbetrieb                                 */
#define mhalb       0x11b  /* Betriebsart Halbautomatik                   */
#define mauto       0x11c  /* Betriebsart Vollautomatik                   */
#define mi4b6       0x11d  /* gesetzt wenn Endschalter gedaempft          */
#define mihoeh      0x11e  /* Reset Formhoehenabgleich                    */
#define mpausd      0x11f  /* Spritzistwerte stehen bereit, wenn Bit ges. */
#define mikanf      0x120  /* Anfahrschaltung erwuenscht?                 */
#define mxstdt      0x121  /* Anforderungsbit fuer Heizungsdownload       */
#define SPm_Down    0x122  /* Download anfordern von der SPS              */
#define HEm_Ready   0x123  /* Heizungsoptimierung beendet                 */
#define KZm_Sond    0x124  /* Kernuzug Sonderseite 65.0                   */
#define HEm_Abort	  0x125	/* Heizungsoptimierung abbrechen					  */	
#define ZYitAnalys  0x126	/* Zeitanalyseregister werden im Einr. + Handb.*/
#define SLm_SDREin  0x127  /* gesetzt wenn Schliesskraft im Einrichten moeglich */
#define POmFoerder  0x128  /* Seitefreigabebit fuer Seite 71.0, Foerderband */
#define OPmF_Pack   0x129  /* Option F-Package                            */
#define OPmFP_Pack  0x12a  /* Option FP-Package                           */
#define UP_SPSText  0x12b  /* SPS-Texte von der SPS holen                 */
#define OPm_EPlast  0x12c  /* SPS_IQT-Option Elektr.Plastifizieren     */
#define OPm_Luft8   0x12d  /* SPS_IQT-Option Freigabe der 5 bis 8 Luftventile */
#define OPm_IQT350  0x12e  /* Komunikation fuer SPS-freigabe der S. 35 */
#define OPm_IQT399  0x12f  /* Komunikation fuer SPS-freigabe der S. 39.9 */
#define OPm_IQT710  0x130  /* SPS-IQT-Option Zwischenstop Schutztuer */
#define OPm_IQT800  0x131  /* SPS_IQT-Option Kuehlwasser-Abschaltung Seite 80 */
#define OPm_Karton  0x132  /* Komunikation fuer SPS-Freigabe der S.71.0, Zeile 14,15 */
#define QUm_IQTfrd  0x133  /* 71.0 SPS-Freigabebit Foerderband         */        
#define OPm_AOIqt   0x134  /* freikonfig. AO */
#define OPm_DIOIqt  0x135  /* freikonfig. DIO */
/*------------------- Airpress -------------------------------------------- */
#define OPm_Airpr   0x136  /* Freigabe der Airpress-Option Seite 48.0 und 81.7 */
#define OPm_APProp  0x137  /* Freigabe des prop. Ventiles (Seite 48.0 Zeile 12-15) */
#define OPm_APip    0x138  /* Freigabe der Zeile 18 Seite 48.0              */
/*------------------- SPS-Optionsbits Werkzeugauswerfer,Wenden ------------ */
#define OP_WkzAusw  0x139  /* SPS-Optionsbit fuer Seite 53.0 Werkzeugausw.  */
#define OP_WkzAus2  0x13a  /* SPS-Optionsbit fuer Seite 53.1 Werkzeugausw.  */
#define OP_WkzApv   0x13b  /* SPS-Optionsbit fuer Seite 53.0 der Z.14 - 18  */
#define OP_Wenden   0x13c  /* SPS-Optionsbit fuer Seite 57.0 Wenden         */
#define OP_WDgr_gs  0x13d  /* SPS-Optionsbit fuer Seite 57.0 der Z.16 - 19  */
/* ------------------------------------------------------------------------ */
#define DTizSpumk   0x13e  /* Defaultbit Spannungsumkehr S.57.1             */
#define DTizDrumk   0x13f  /* Defaultbit Drehrichtungsumkehr S.57.1         */
/* ---------------- Seite 49.0 mit Wegmesslineal -------------------------- */
#define SEAbglTas1  0x140  /* Spritzeinheittaste 1 gedrueckt                */
#define SEAbglTas2  0x141  /* Spritzeinheittaste 2 gedrueckt                */
#define OP_CanWink  0x142  /* SPS-Optionsbit fuer CAN-Winkelkodierer        */

/* ------------------------------------------------------------------------ */
/* $$$ Fehlermeldungsbits                                                   */
/* ------------------------------------------------------------------------ */
#define fpfisc      0x150  /* Spannungsunterbrechung 24V Versorgung         */
#define fweg1       0x151  /* Wegmesssystem 1 Schnecke 1 defekt             */
#define fweg2       0x152  /* Wegmesssystem 2 Werkzeug defekt               */
#define fweg3       0x153  /* Wegmesssystem 3 Schnecke 2 defekt             */
#define fweg4       0x154  /* Wegmesssystem 4 Auswerfer defekt              */
#define foeln       0x155  /* Oelniveau zu niedrig                          */
#define fmots       0x156  /* Motor Ueberstromrelais ausgeloest             */
#define ftnota      0x157  /* NOT-AUS-Taste betaetigt                       */
#define fatur       0x158  /* Auswerferschutz offen                         */
#define fstur       0x159  /* Schutztuere offen                             */
#define fdtur       0x15a  /* Duesenschutz offen                            */
#define fskmin      0x15b  /* Schliesskraft kleiner als 80 Prozent          */
#define fpuv2       0x15c  /* Fehler P+V-Karte 2                            */
#define fe6         0x15d  /* Druckfuehler e6 ausser Toleranz               */
#define fe27        0x15e  /* Druckfuehler e27 ausser Toleranz              */
#define fkznrf      0x15f  /* Kernzugnummer falsch                          */
#define ftsdr       0x160  /* Schliessdruck Ueberwachungszeit               */
#define fbform      0x161  /* Werkzeugbewegung blockiert                    */
#define fe4         0x162  /* Druckschalter e4 oeffnet nicht                */
#define fe5         0x163  /* Druckfuehler e5 ausser Toleranz               */
#define fble10      0x164  /* Auswerferplattensicherung                     */
#define fmot13      0x165  /* Motor nicht im Dreieckbetrieb                 */
#define foelvw      0x166  /* Oelvorwaermung laeuft                         */
#define ftnidr      0x167  /* Werkzeugsicherung                             */
#define fnfss       0x168  /* Werkzeugsicherungswiederholung                */
#define fausw       0x169  /* Auswerfer nicht in hinterer Lage              */
#define fhoehe      0x16a  /* Werkzeughoehe nicht eingestellt               */
#define f4b21       0x16b  /* Werkzeug nicht in Oeffnungsweite              */
#define fkern       0x16c  /* Kernposition fehlerhaft                       */
#define fwegf       0x16d  /* Wegpunkt S.67 falsch                          */
#define fheiau      0x16e  /* Heizung nicht eingeschaltet                   */
#define fsnek       0x16f  /* Schneckenfreigabe fehlt                       */
#define fanfla      0x170  /* Heizung Anfahrschaltung laeuft                */
#define fprod       0x171  /* Maximale Toleranzueberschreitungen            */
#define ftzykl      0x172  /* Zykluszeit ueberschritten                     */
#define ft2zyk      0x173  /* Zykluszeit zum 2. Mal ueberschritten          */
#define ftdos1      0x174  /* Plastifizierzeit Aggregat 1 ueberschritten    */
#define flicht      0x175  /* Lichtschranke/Ausfallwaage                    */
#define foelf       0x176  /* Oelfilter verschmutzt                         */
#define fpfet       0x177  /* Schmierdruck nicht erreicht                   */
#define flfet       0x178  /* Schmierung Behaelter leer                     */
#define fmaus       0x179  /* Automatische Maschinenabschaltung laeuft      */
#define fdos        0x17a  /* Plastifizierweg ueberschritten                */
#define fkmot1      0x17b  /* Motortemperatur zu hoch                       */
#define ftemab      0x17c  /* Fehlerbit "Temp.Absenkung Zyl.Heizung laeuft" */
#define fexstp      0x17d  /* Zyklusstop extern                             */
#define fexger      0x17e  /* Stoerung externes Geraet                      */
#define fexson      0x17f  /* Sonderfehlermeldung                           */
#define fson0       0x180  /* Reserve                                       */
#define fson1       0x181  /* Reserve                                       */
#define FK_AGm_Vor  0x182  /* D}senanlagedruck nicht erreicht               */
#define FK_PLm_Akt  0x183  /* Plastifizierweg nicht erreicht                */
#define FK_OelFil1  0x184  /* Druckfilter 1 verschmutzt                     */
#define FK_OelFil2  0x185  /* Druckfilter 2 verschmutzt                     */
#define ftem5       0x187  /* WkzHeizung nicht eingeschaltet                */
#define ftem6       0x188  /* Wkz Heizung Freigabe fehlt                    */
#define f1wwc       0x189  /* Oeltemperatur ausser weiter Toleranz          */
#define FK_SpStell  0x18a  /* Spritzeinheit nicht in Stellung */
#define FK_SGe_Ven  0x18b  /* Stoerung Absperrventil Schutztuer             */
#define fsonc       0x18c  /* Sonderbit                                     */    
#define fsond       0x18d  /* Sonderbit                                     */
#define fsone       0x18e  /* Sonderbit                                     */             
#define fsonf       0x18f  /* Sonderbit                                     */             
#define fsonp0      0x190  /* Sonderbit                                     */
#define fsonp1      0x191  /* Sonderbit                                     */
#define fsonp2      0x192  /* Sonderbit                                     */
#define fsonp3      0x193  /* Sonderbit                                     */
#define fsonp4      0x194  /* Sonderbit                                     */
#define fsonp5      0x195  /* Sonderbit                                     */
#define fsonp6      0x196  /* Sonderbit                                     */
#define fsonp7      0x197  /* Sonderbit                                     */
#define fsonp8      0x198  /* Sonderbit                                     */
#define fsonp9      0x199  /* Sonderbit                                     */
#define fsonpa      0x19a  /* Sonderbit                                     */
#define fsonpb      0x19b  /* Sonderbit                                     */
#define fsonpc      0x19c  /* Sonderbit                                     */
#define fsonpd      0x19d  /* Sonderbit                                     */
#define FK_AWd_Nul  0x19e  /* Auswerfernullpunkt unterschritten             */
#define FK_KEprf    0x19f  /* Kernposition }berpr}fen                       */
#define ftker1      0x1a0  /* Kern 1 Bewegung nicht ausgefuehrt             */
#define ftker2      0x1a1  /* Kern 2 Bewegung nicht ausgefuehrt             */
#define fbend1      0x1a2  /* Kern 1 beide Endschalter betaetigt            */
#define fbend2      0x1a3  /* Kern 2 beide Endschalter betaetigt            */
#define fk1pos      0x1a4  /* Kern 1 nicht in richtiger Stellung            */
#define fk2pos      0x1a5  /* Kern 2 nicht in richtiger Stellung            */
#define fkblk1      0x1a6  /* Auswerfer blockiert Kern 1                    */
#define fkblk2      0x1a7  /* Auswerfer blockiert Kern 2                    */
#define fkblau      0x1a8  /* Kerne blockieren Auswerfer                    */
#define fstart      0x1a9  /* Bitte Starttaste betaetigen                   */
#define fschwe      0x1aa  /* Schneckenwechsel                              */
#define fkzaus      0x1ab  /* Kernzug Seite 61 Zeile 2 ausschalten          */
#define fwhtab      0x1ac  /* Fehlerbit "Temp.Absenkung Wkz-Heizung laeuft  */
#define ffeldkl     0x1ad  /* Fehlerbit "Feldklemmenfehler                  */
#define fmodul      0x1ae  /* Fehlerbit "Ueberlast Modul                    */
#define fmodtemp    0x1af  /* Fehlerbit "Uebertemperatur                    */
#define fioerr      0x1b0  /* Fehlerbit "I/O Error                          */
#define fconf1      0x1b1  /* Fehlerbit "Config: EPROM vomm                 */
#define fconf2      0x1b2  /* Fehlerbit "Config:kein RAM Speicher verfuegbar*/
#define FK_ROe_ws   0x1b3  /* Start Werkzeug schlie~en vom HG fehlt         */
#define FK_ROe_si   0x1b4  /* Freigabe Werkzeugbewegung vom HG fehlt        */
#define FK_ROe_awv  0x1b5  /* Freigabe Auswerfer-Vorbewegung vom HG fehlt   */
#define FK_ROe_awz  0x1b6  /* Freigabe Auswerfer R}ckbewegung vom HG fehlt  */
#define FK_ROe_wo   0x1b7  /* Start Werkzeug |ffnen vom HG fehlt            */
#define FK_ROfrg    0x1b8  /* Freigabe Sollwert Werkzeug schlie~en          */
#define FK_SKm2Tur  0x1b9  /* hintere Schutztuer offen                      */
#define fagsich1    0x1ba  /* Sicherheitssch}tz Agg.1 defekt                */
#define fagsich2    0x1bb  /* Sicherheitssch}tz Agg.2 defekt                */
#define fagsich3    0x1bc  /* Sicherheitssch}tz Agg.3 defekt                */
#define fagsich4    0x1bd  /* Sicherheitssch}tz Agg.4 defekt                */
#define FK_PLiv1Ak  0x1be  /* Schneckendrehzahlmessung Agg.1 gest|rt        */
#define FK_PLiv2Ak  0x1bf  /* Schneckendrehzahlmessung Agg.2 gest|rt        */
#define FK_PLiv3Ak  0x1c0  /* Schneckendrehzahlmessung Agg.3 gest|rt        */
#define FK_PLiv4Ak  0x1c1  /* Schneckendrehzahlmessung Agg.4 gest|rt        */
#define FK_FHmin    0x1c2  /* Min. Werkzeugeinbauh|he unterschritten        */
#define FK_WTabgel  0x1c3  /* Wochentagschaltuhr abgelaufen                 */
#define FK_SPSDiag  0x1c4  /* SPS in Betriebsart DIAGNOSE                   */
#define FK_NoWZBew  0x1c5  /* Keine Werkzeugbewegung moeglich               */
#define FK_AWS99F   0x1c6  /* AWS - Speicherplatz zu 99% voll               */
#define FK_AWSFull  0x1c7  /* AWS - Speicherplatz voll                      */
#define fweg12      0x1c8  /* Wegmesssystem 3 Schnecke 2 defekt             */
#define fweg13      0x1c9  /* Wegmesssystem 3 Schnecke 3 defekt             */
#define fweg14      0x1ca  /* Wegmesssystem 3 Schnecke 4 defekt             */
#define FK_DrB7208  0x1cb  /* Druckfuehler B7208 ausser Tolernaz            */
#define FK_DrB7308  0x1cc  /* Druckfuehler B7308 ausser Tolernaz            */
#define FK_AGm3Vor  0x1cd  /* Duesenanlagedruck Agg. 3 nicht erreicht       */
#define FK_AGm4Vor  0x1ce  /* Duesenanlagedruck Agg. 4 nicht erreicht       */
#define f1b3        0x1cf  /* Druckfuehler .1-B3 ausser Toleranz            */
#define ftdos2      0x1d0  /* Plastifizierzeit Aggr.2 ueberschritten        */
#define ftdos3      0x1d1  /* Plastifizierzeit Aggr.3 ueberschritten        */
#define ftdos4      0x1d2  /* Plastifizierzeit Aggr.4 ueberschritten        */
#define fdos2       0x1d3  /* Plastifizierweg  Agg.2 ueberschritten         */
#define fdos3       0x1d4  /* Plastifizierweg  Agg.3 ueberschritten         */
#define fdos4       0x1d5  /* Plastifizierweg  Agg.4 ueberschritten         */
#define fa1ruh      0x1d6  /* Aggregat 1 nicht in hinterer Lage             */
#define fa2ruh      0x1d7  /* Aggregat 2 nicht in hinterer Lage             */
#define fa3ruh      0x1d8  /* Aggregat 3 nicht in hinterer Lage             */
#define fa4ruh      0x1d9  /* Aggregat 4 nicht in hinterer Lage             */
#define FK_PLm2Akt  0x1da  /* Plastifizierweg Agg.2 nicht erreicht          */
#define FK_PLm3Akt  0x1db  /* Plastifizierweg Agg.3 nicht erreicht          */
#define FK_PLm4Akt  0x1dc  /* Plastifizierweg Agg.4 nicht erreicht          */
#define fschwe2     0x1dd  /* Schneckenwechsel Aggregat 2                   */
#define fschwe3     0x1de  /* Schneckenwechsel Aggregat 3                   */
#define fschwe4     0x1df  /* Schneckenwechsel Aggregat 4                   */
#define ftemab2     0x1e0  /* Temp.Absenkung Schneckenzyl. Agg.2 laeuft     */
#define ftemab3     0x1e1  /* Temp.Absenkung Schneckenzyl. Agg.3 laeuft     */
#define ftemab4     0x1e2  /* Temp.Absenkung Schneckenzyl. Agg.4 laeuft     */
#define fsnek2      0x1e3  /* Schneckenfreigabe Agg.2 fehlt                 */
#define fsnek3      0x1e4  /* Schneckenfreigabe Agg.3 fehlt                 */
#define fsnek4      0x1e5  /* Schneckenfreigabe Agg.4 fehlt                 */
#define FK_PMmin    0x1e6  /* Minimaler Pumpendruck nicht erreicht          */
#define FK_DrSB707  0x1e7  /* Druckf}hler B7107 au~er Tolernaz              */
#define fmots2      0x1e8  /* Motor 2 Ueberstromrelais ausgeloest           */
#define fmot132     0x1e9  /* Motor nicht im Dreieckbetrieb                 */ 
#define FK_SGm1Tur  0x1ea  /* St|rung Schutzt}r .2-S5 .2-S6 .2-S20          */
#define FK_SGm2Tur  0x1eb  /* Sicherheitssch}tz .2-K14 defekt               */
#define FK_SGm1SS   0x1ec  /* St|rung Schutzt}r .2-S7 .2-S8                 */
/*------------------- Options-Fehlermeldung ------------------------------- */
#define FK_DTnRef   0x1ed  /* Drehteller nicht referenziert                 */
#define FK_EndWend  0x1ee  /* Fehler Endlage Wenden                         */
#define FK_BlWend   0x1ef  /* Fehler Blockierung Wenden                     */
#define FK_SPWend   0x1f0  /* Fehler Startpunkt Wenden                      */
#define FK_EPkOver  0x1f1  /* Ziel }berfahren                               */
#define FK_ELnFix   0x1f2  /* Endlage nicht fixiert                         */
#define FK_DTBlock  0x1f3  /* Drehteller blockiert                          */
#define FK_WZAvBl   0x1f4  /* Werkzeugauswerfer 1 vor blockiert             */
#define FK_WZAzBl   0x1f5  /* Werkzeugauswerfer 1 zur}ck blockiert          */
#define FK_WZAEChk  0x1f6  /* Endlage Werkzeugauswerfer 1 pr}fen            */
#define FK_SerIni   0x1f7  /* Fehlerbit Serielle Schnittstelle nicht initialisiert */       
#define FK_SerCom   0x1f8  /* Fehlerbit St|rung Datacom externe Heizung */                  
#define FK_SerExt   0x1f9  /* Fehlerbit St|rung externe Heizung */
#define FK_SerPro   0x1fa  /* Fehlerbit Protokoll externe Heizung nicht verf]gbar */        
#define FK_Karton1  0x1fb  /* Fehlerbit Karton auf Position 1 fehlt       */
#define FK_PLeDrive 0x1fc  /* Plastifizierantrieb nicht betriebsbereit      */
#define FK_PLeInit  0x1fd  /* Plastifizierantrieb Fehler Umrichter          */
#define FK_PLeWarn  0x1fe  /* Plastifizierantrieb }berlastet                */
#define FK_PLeTemp  0x1ff  /* Uebertemperatur Plastifiziergetriebe          */
#define FK_PLePower 0x200  /* Hauptschalter Plastifizierantrieb ausgel|st   */
#define FK_SE1WegM  0x201  /* Wegmesssystem Spritzeinheit 1 defekt          */
#define FK_SE1NAct  0x202  /* Nullpunktabgl. Spritzeinh.1 nicht aktiv       */
#define FK_SE2WegM  0x203  /* Wegmesssystem Spritzeinheit 2 defekt          */
#define FK_SE2NAct  0x204  /* Nullpunktabgl. Spritzeinh.2 nicht aktiv       */
#define FK_IOe_DI1  0x205  /* Freigabe von konf. Eingang 1 fehlt            */
#define FK_IOe_DI2  0x206  /* Freigabe von konf. Eingang 2 fehlt            */
#define FK_IOe_DI3  0x207  /* Freigabe von konf. Eingang 3 fehlt            */
#define FK_IOe_DI4  0x208  /* Freigabe von konf. Eingang 4 fehlt            */
#define FK_SGErr1   0x209  /* St|rung vordere Schutzt}rantrieb         */
#define FK_SGErr2   0x20a  /* Blockierung der vorderen Schutzt}r       */
#define FK_SGRef    0x20b  /* Vordere Schutzt}r nicht referenziert     */
#define FK_APeAktiv 0x20c  /* Airpress noch aktiv                      */
#define FK_APStoer  0x20d  /* St|rung Airpress                         */
#define FK_APpeSysT 0x20e  /* Fehler Systemdruck Airpressanlage        */
#define FK_WZA2vbl  0x20f  /* FK: Werkzeugauswerfer 2 vor blockiert    */
#define FK_WZA2zbl  0x210  /* FK: Werkzeugauswerfer 2 zur}ck blockiert */
#define FK_WZA2epr  0x211  /* FK: Endlage Werkzeugauswerfer 2 pr}fen   */
#define FK_TstAgg2  0x212  /* FK: Zusatztasten Seitenaggregat aktiv    */
#define FK_Ag2Sich  0x213  /* FK: Absicherung Nebenaggregat            */
#define FK_pUebers  0x214  /* FK: Fehler Druck}bersetzer               */
#define FK_WEsmird  0x215  /* FK: Schmierdruck Drehteller nicht erreicht   */
#define FK_Quit     0x216  /* FK: Bitte Quittiertaste bet{tigen            */
#define FK_QuitBgS  0x217  /* FK: Quittiertaste Bediengegenseite bet{tigen */
#define FK_QuitBS   0x218  /* FK: Quittiertaste Bedienseite bet{tigen      */
#define FK_NeHi     0x219  /* FK: Monoaggregat nicht in richtiger Stellung */
#define FK_SNikOkM  0x21a  /* FK: Schneckenfreigabe Monoaggregat fehlt     */
#define FK_ZHmAbNI  0x21b  /* FK: Temperaturabsenkung Monoaggregat l{uft   */
#define FK_ZHm_AuM  0x21c  /* FK: Heizung Monoaggregat ausgeschaltet       */
#define FK_Arret    0x21d  /* FK: Arretierung l|sen                        */
#define FK_mechSsp  0x21e  /* FK: Mechanische Schlie~sperre                */
#define FK_mSpESdf  0x21f  /* FK: Mechanische Schlie~sperre Endschalter defekt */
#define FK_Einrich  0x220  /* FK: Einrichten bet{tigen                         */
#define FK_KEAWoSt  0x221  /* FK: Kernzug und Auswerfer bei offener Schutzt}r  */
#define FK_SPZylnP  0x222  /* FK: Spannzylinder nicht in Position              */
#define FK_BAP44pr  0x223  /* FK: Betriebsart Seite 44 pr}fen                  */
#define FK_Mischk   0x224  /* FK: Fehler Mischkopfbetrieb                      */
#define FK_Wpktnpl  0x225  /* FK: Wegpunkt nicht plausibel                     */
#define FK_UwWkzBw  0x226  /* FK: ]berwachung Werkzeugbewegung                 */
#define FK_UwAWBew  0x227  /* FK: ]berwachung Auswerferbewegung                */
#define FK_ParProd  0x228  /* FK: Parameter Produktionsstart                   */
#define FK_WS2WTdf  0x229  /* FK: Wegmesssystem 2 Wendetisch defekt            */
#define FK_XSm_Anf  0x22a  /* Fehlerbit Produktionsstart: Parameter aktiv */                
#define FK_XSm_An2  0x22b  /* Fehlerbit Produktionsstart: WKZ-Sicherungsdruck aktiv */      
#define FK_CanWink  0x22c  /* Fehlerbit Fehler Winkelkodierer */
                           
/* ---------------- freiprogrammierbare Kernzuege ------------------------- */
#define KEEinAus	  0x230  /* Kernzug ein/aus					*/
#define KELineAct0  0x240  /* aktive Kernzugprogrammzeile 0	*/
                           /* ... 									*/
#define KELineAct49 0x271	/* Ende 									*/


/* Sonderbits fuer Gillette                                               */
#define gil_optbit0  0x280
#define gil_optbit1  0x281
#define gil_optbit2  0x282
#define gil_optbit3  0x283
#define gil_optbit4  0x284
#define gil_optbit5  0x285
#define gil_optbit6  0x286
#define gil_optbit7  0x287
#define gil_optbit8  0x288
#define gil_optbit9  0x289
#define gil_optbit10 0x28a
#define gil_optbit11 0x28b
#define gil_optbit12 0x28c
#define gil_optbit13 0x28d
#define gil_optbit14 0x28e
#define gil_optbit15 0x28f
#define gil_istbit0  0x290
#define gil_istbit1  0x291
#define gil_istbit2  0x292
#define gil_istbit3  0x293
#define gil_istbit4  0x294
#define gil_istbit5  0x295
#define gil_istbit6  0x296
#define gil_istbit7  0x297
#define gil_istbit8  0x298
#define gil_istbit9  0x299
#define gil_istbit10 0x29a
#define gil_istbit11 0x29b
#define gil_istbit12 0x29c
#define gil_istbit13 0x29d
#define gil_istbit14 0x29e
#define gil_istbit15 0x29f
#define gil_optbit16 0x2a0
#define gil_optbit17 0x2a1
#define gil_optbit18 0x2a2
#define gil_optbit19 0x2a3
#define gil_optbit20 0x2a4
#define gil_optbit21 0x2a5
#define gil_optbit22 0x2a6
#define gil_optbit23 0x2a7
#define gil_optbit24 0x2a8
#define gil_optbit25 0x2a9
#define gil_optbit26 0x2aa
#define gil_optbit27 0x2ab
#define gil_optbit28 0x2ac
#define gil_optbit29 0x2ad
#define gil_optbit30 0x2ae
#define gil_optbit31 0x2af
#define gil_istbit16 0x2b0
#define gil_istbit17 0x2b1
#define gil_istbit18 0x2b2
#define gil_istbit19 0x2b3
#define gil_istbit20 0x2b4
#define gil_istbit21 0x2b5
#define gil_istbit22 0x2b6
#define gil_istbit23 0x2b7
#define gil_istbit24 0x2b8
#define gil_istbit25 0x2b9
#define gil_istbit26 0x2ba
#define gil_istbit27 0x2bb
#define gil_istbit28 0x2bc
#define gil_istbit29 0x2bd
#define gil_istbit30 0x2be
#define gil_istbit31 0x2bf
#define gil_istbit32 0x2c0
#define gil_istbit33 0x2c1
#define gil_istbit34 0x2c2
#define gil_istbit35 0x2c3
#define gil_istbit36 0x2c4
#define gil_istbit37 0x2c5
#define gil_istbit38 0x2c6
#define gil_istbit39 0x2c7
#define gil_istbit40 0x2c8
#define gil_istbit41 0x2c9
#define gil_istbit42 0x2ca
#define gil_istbit43 0x2cb
#define gil_istbit44 0x2cc
#define gil_istbit45 0x2cd
#define gil_istbit46 0x2ce
#define gil_istbit47 0x2cf
#define gil_istbit48 0x2d0
#define gil_istbit49 0x2d1
#define gil_istbit50 0x2d2
#define gil_istbit51 0x2d3
#define gil_istbit52 0x2d4
#define gil_istbit53 0x2d5
#define gil_istbit54 0x2d6
#define gil_istbit55 0x2d7
#define gil_istbit56 0x2d8
#define gil_istbit57 0x2d9
#define gil_istbit58 0x2da
#define gil_istbit59 0x2db
#define gil_istbit60 0x2dc
#define gil_istbit61 0x2dd
#define gil_istbit62 0x2de
#define gil_istbit63 0x2df
