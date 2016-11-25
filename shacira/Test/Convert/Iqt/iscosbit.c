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
*     ISCOSBIT.C
*
*  BESCHREIBUNG:                                                   
*     Definition der Tabelle IscosBitTab, die alle ISCOS-Bits      
*     beschreibt, und Belegen der Tabelle mit Werten.              
*     Die Endekennung {0xffff} muss immer da sein.                 
*                                                                  
*  HISTORY:                                                        
*     08.06.89 -TSchw-  Implementierung                           
*     22.10.93 -MBa-    totale Neuorganisation fuer BUR           
*     17.02.94 -TSchw-  Bit IWZM_HANF neu eingefuegt              
*     06.04.94 -TSchw   Bits fuer Qualitaetskontrolle und         
*                       Selektierweiche vom IQT 450 uebernommen   
*     12.04.94 -TSchw-  Bit fuer Heizungsoptimierung vom IQT 450  
*                       uebernommen.                              
*     20.06.94 -TSchw-  Fehlerbit XFKZAUS nachgetragen, hat bis-  
*                       her gefehlt, was bei der entsprechenden   
*                       Fehlermeldung zu sporadischem Erscheinen  
*                       fÅhrte.                                   
*     08.07.96 -HAns-   Folgende Fehlerbits mussten neu geordnet  
*                       werden: IFK_AGM_VOR, IFK_PLM_AKT,         
*                       IFK_OELFIL1,2, IFK_SGE_VEN, IFK_AWD_NUL   
*                       und IFK_KEPRF                             
*     27.07.96 -HAns-   XIQSSONBIT0-9, XZYITANALYS, XSLDPSDREIN   
*                       und XSLM_SDREIN eingefuegt.               
*     13-09-96 -PR-     ISCOS-Bits fuer frei progr. Kernzuege     
*							    eingefuehrt (IKEEINAUS).                  
*     06.12.96 -HAns-   XFAGSICH1-4, XFK_PLIV1AK - XFK_PLIV2AK und
*                       XFK_FHMIN eingefuegt.
*     19.12.96 -HAns-   XDOSFORCE01 - XDOSFORCE32 eingefuegt.
*     16.01.97 -HAns-   Fehlerbits XFK_WTABGEL, XFK_SPSDIAG und XFK_NOWZBEW
*                       eingefuegt.
*     30.01.97 -HAns-   Fehlerbits fuer errtab.cp eingefuegt.
*     03.02.96 -HAns-   IQSSonBit0-9 nach IQsSonBit0-9 geaendert.
*                       Fehlerbits fuer errtab.cp eingefuegt.    
*     05.02.97 -HAns-   Fehlerbits XFK_AWS99F und XFK_AWSFULL eingefuegt.
*     13.02.97 -HAns-   XOPTION_DV7 eingefuegt.
*     15.02.97 -HAns-   XDWSP01 bis XDWSPRF eingefuegt. (fuer MF-Maschinen)
*     05.03.97 -HAns-   XPLS_RAMPE eingefuegt.
*     06.03.97 -HAns-   XPLS_RAMPE2 bis 4 eingefuegt.
*     20.11.97 -HAns-   XDOSFORCE01 bis XDOSFORCE32 herausgenommen.
*     28.11.97 -HAns-   Bits der Seiten 87.1 und 87.2 herausgenommen:
*                       Iy9008soll, Iy90081soll, Iy9016soll, Iy9017soll, Iy9009soll
*                       Iy9025soll, Iy90251soll, Iy9026soll,
*                       Iy9008ist, Iy90081ist, Iy9016ist, Iy9017ist, Iy9009ist,
*                       Iy9025ist, Iy90251ist, Iy9026ist, Iy9020ist, Iy9010ist,
*                       Iy9014ist, Iy90141ist, Iy9023ist, Iy9011ist, I5f1ist,
*                       Iy9002ist, Iy9001ist, Iy90011ist
*     15.02.00 -HAns-   IKELINEACT eingefuegt.
*     06.06.01 -HAns-   XDWSP12 herausgenommen, da nirgends verwendet.
*                       XDWSPPS, XDWSPRF RegType DSK herausgenommen, da
*                       diese durch die Flt-Funktionen Flt_EinParSer, Flt_AggParSer,
*                       Flt_EinReihenfolge und Flt_AggReihenfolge (iqtreg.c) beschrieben werden.                 
*     05.07.02 -HA-     XBXSOLL entfernt
*     10.07.02 -HA-     XWDMPENDLAG bis XWZA_CHKFSS eingefuegt.
*                       XFK_DTNREF bis XFK_WZAECHK eingefuegt.
*                       XOP_WENDEN bis XOP_WKZAPV  eingefuegt.
*                       XOPM_KARTON und XFK_KARTON1 eingefuegt.
*     11.07.02 -HA-     XFK_PLEDRIVE, XFK_PLEINIT,  XFK_PLETEMP, XFK_PLEPOWER und XFK_PLEWARN eingefuegt.
*                       XOPM_EPLAST, XOPM_LUFT8 eingefuegt.
*                       XQUM_IQTFRD eingefuegt
*     12.07.02 -HA-     XSEABGLST1 bis XSEABGLTASTE2 und XFK_SE1WEGM bis XFK_SE2NAG eingefuegt (SE mit Wegmesslineal).
*                       XOPM_IOT800 eingefuegt.
*                       Bits fuer Seite 39.9
*                       Bit fuer Schutzt}re verwendet
*                       XFK_SGERR1, XFK_SGERR2 und XFK_SGREF fuer elektr. Schutztuer eingefuegt.
*                       IOM_AOIQT und IOM_DIOIQT  Komunikation fuer SPS-freigabe der 
*                       freikonfigurierbaren digitalen bzw. analogen Ein/Ausgaenge Seiten 66.0,1,2 eingefuegt.
*                       XFK_IOE_DI1 bis XFK_IOE_DI4 eingefuegt
*     15.07.02 -HA-     XOPM_AIRPR, XOPM_APPROP, XOPM_APIP, XFK_APEAKTIV, XFK_APSTOER und XFK_APPESYST eingefuegt.
*     20.08.02 -HAns-   XFK_PMMIN, Freigabebit XPOMFOERDER fuer Seite 71.0 und
*                       XFK_DRSB707, XOPMF_PACK und XOPMFP_PACK fuer KDS eingefuegt.
*                       XUP_SPSTEXT eingefuegt.
*     22.08.02 -HA-     XFMOTS2, IFK_SPSTELL, XFMOT132, XFK_SGM1TUR, XFK_SGM2TUR und XFK_SGM1SS eingefuegt.
*     02.10.02 -HA-     XOP_WKZAUS2 und XWZA2CHKVOR bis XFK_WZA2EPR eingefuegt.
*     20.11.02 -HA-     Fehlerbits XFK_TSTAGG2 bis XFK_WSWTDF eingefuegt.
*     25.11.02 -HA-     XHXSNECHO_2 eingefuegt
*     10.03.03 -HA-     XFK_XSM_ANF und XFK_XSM_AN2 eingefuegt.
*                       XSPS_OPTION1-16 eingefuegt.  
*     12.03.03 -HA-     XOP_CANWINK und XFK_CANWINK eingefuegt.
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
*     ACHTUNG !!!!!                                                 
*     Die Tabelle IscosBitTab muss nach Registernummern aufsteigend 
*     geordnet sein. Dies ist zwingend vorgeschrieben. Ist dies     
*     nicht der Fall, so fuehrt dies zu Fehlern beim Zugriff auf die
*     Register.                                                     
*
*****************************************************************************
*
*  FUNKTIONEN: keine
*
**.EM.**********************************************************************/

#define BUR

/*.SI.**********************************************************************/

#include <syntax.h>

#define USE_ALL_ISCOSBIT
#define IMPORT_NOT_GLOBAL
#define IMPORT_FLTFUNC

#include <iqtdstr.h>
#include <symbit.h>

/*.EI.**********************************************************************/

/* Schwanz eines Tabellen-Eintrags */
#define MAKE_ADR(adr)            adr/0x10, adr%0x10
#define TAIL_ADR(adr)              0, 0, MAKE_ADR(adr)
#define TAIL_FLT_ADR(flt,adr)    flt, 0, MAKE_ADR(adr)

/* Abkuerzungen fuer Konstanten (TP = Type) */
#define TP_STD          REG_WR | REG_WR_NORMAL
#define TP_DL           REG_WR | REG_WR_DOWN
#define TP_DSK_BG_DL    REG_DISK_TOOL | REG_BG | REG_WR | REG_WR_DOWN
#define TP_BG_DL        REG_BG | REG_WR | REG_WR_DOWN


const ISCOSBIT_TYPE IscosBitTab [] =
{
{XDDUMMI,      TP_DSK_BG_DL,  TAIL_ADR( ddummi      )},
/* ---------------- Start Kernzug ----------------------------------------- */
{XDKZON,       TP_DSK_BG_DL,  TAIL_ADR( dkzon       )},
{XK1EPAR,      TP_DSK_BG_DL,  TAIL_ADR( k1epar      )},
{XK1APAR,      TP_DSK_BG_DL,  TAIL_ADR( k1apar      )},
{XK2EPAR,      TP_DSK_BG_DL,  TAIL_ADR( k2epar      )},
{XK2APAR,      TP_DSK_BG_DL,  TAIL_ADR( k2apar      )},
/* ---------------- Ende Kernzug ------------------------------------------ */
{XDWSP01,      TP_DSK_BG_DL,  TAIL_ADR( dwsp01      )},
{XDWSP02,      TP_DSK_BG_DL,  TAIL_ADR( dwsp02      )},
/*{XDWSP12,      TP_DSK_BG_DL,  TAIL_ADR( dwsp12      )},*/
{XDWSPPS,      TP_BG_DL,      TAIL_ADR( dwspps      )},
{XDWSPRF,      TP_BG_DL,      TAIL_ADR( dwsprf      )},
{XMIHEIE,      TP_STD,        TAIL_ADR( miheie      )},
{XMIMOTE,      TP_STD,        TAIL_ADR( mimote      )},
{XMIEXT1,      TP_STD,        TAIL_ADR( miext1      )},
{XMIEXT2,      TP_STD,        TAIL_ADR( miext2      )},
{IROM_TYPE,    TP_DSK_BG_DL,  TAIL_ADR( ROm_Type    )},
{IROM_AUSGRF,  TP_DSK_BG_DL,  TAIL_ADR( ROm_AusGrf  )},
{IROM_AUSHUB,  TP_DSK_BG_DL,  TAIL_ADR( ROm_AusHub  )},
{IROM_BCAXIS,  TP_DSK_BG_DL,  TAIL_ADR( ROm_BCAxis  )},
{IROM_TCONTR,  TP_DSK_BG_DL,  TAIL_ADR( ROm_TContr  )},
{IROM_VAKUUM,  TP_DSK_BG_DL,  TAIL_ADR( ROm_Vakuum  )},
{IROM_ZANGE,   TP_DSK_BG_DL,  TAIL_ADR( ROm_Zange   )},
{IROM_SONDANG, TP_DSK_BG_DL,  TAIL_ADR( ROm_SondAng )},
{IROM_SONDSCH, TP_DSK_BG_DL,  TAIL_ADR( ROm_SondSch )},
{IROM_AN,      TP_DSK_BG_DL,  TAIL_ADR( ROm_An      )},
{ISNM_ERHNM,   TP_DSK_BG_DL,  TAIL_ADR( SNm_ErhNm   )},
{IDIM_INIT,    TP_STD,        TAIL_ADR( DIm_Init    )},
{IDIM_CLEAR,   TP_STD,        TAIL_ADR( DIm_Clear   )},
{XEZHASC,      TP_STD,        TAIL_ADR( ezhasc      )},
{XMIHEIA,      TP_STD,        TAIL_ADR( miheia      )},
{XMIMOTA,      TP_STD,        TAIL_ADR( mimota      )},
{XMIEX1A,      TP_STD,        TAIL_ADR( miex1a      )},
{XMIEX2A,      TP_STD,        TAIL_ADR( miex2a      )},
{XDSCHWE,      TP_DSK_BG_DL,  TAIL_ADR( dschwe      )},
{XMASWNP,      TP_STD,        TAIL_ADR( maswnp      )},
{XD4B5,        TP_DSK_BG_DL,  TAIL_ADR( d4b5        )},
{XMTOLUE,      TP_STD,        TAIL_ADR( mtolue      )},
{XMTOMAX,      TP_STD,        TAIL_ADR( mtomax      )},
{XDTOL1,       TP_STD,        TAIL_ADR( dtol1       )},
{XDMAUS,       TP_DSK_BG_DL,  TAIL_ADR( dmaus       )},
{XDOELHZ,      TP_DSK_BG_DL,  TAIL_ADR( doelhz      )},
/* ---------------- BEGIN_MODE_10 ----------------------------------------- */
#ifndef MODE_10
   /* {XDSCHSP,TP_DSK_BG_DL,  TAIL_ADR( dschsp      )}, */
   /* {XDSCHS2,TP_DSK_BG_DL,  TAIL_ADR( dschs2      )}, */
#else
   {XDSCHSP,   TP_STD,        TAIL_ADR( dschsp      )}, /* Bei 10-Stufen Dummy */
   {XDSCHS2,   TP_STD,        TAIL_ADR( dschs2      )}, /* Bei 10-Stufen Dummy */
#endif
/* ---------------- END_MODE_10 ------------------------------------------- */
{XDOPT,        TP_DSK_BG_DL,  TAIL_ADR( dopt        )},
{XDANF,        TP_DSK_BG_DL,  TAIL_ADR( danf        )},
{XDLAGER,      TP_DSK_BG_DL,  TAIL_ADR( dlager      )},
{XDDUESE,      TP_DSK_BG_DL,  TAIL_ADR( dduese      )},
{XDAUSWR,      TP_DSK_BG_DL,  TAIL_ADR( dauswr      )},
{XDLICHT,      TP_DSK_BG_DL,  TAIL_ADR( dlicht      )},
{XDKEINZ,      TP_DSK_BG_DL,  TAIL_ADR( dkeinz      )},
{XDKAUSZ,      TP_DSK_BG_DL,  TAIL_ADR( dkausz      )},
{XDK1EID,      TP_DSK_BG_DL,  TAIL_ADR( dk1eid      )},
{XDK2EID,      TP_DSK_BG_DL,  TAIL_ADR( dk2eid      )},
{XDK1AUD,      TP_DSK_BG_DL,  TAIL_ADR( dk1aud      )},
{XDK2AUD,      TP_DSK_BG_DL,  TAIL_ADR( dk2aud      )},
{XDKEI2Z,      TP_DSK_BG_DL,  TAIL_ADR( dkei2z      )},
{XDKAU2Z,      TP_DSK_BG_DL,  TAIL_ADR( dkau2z      )},
{XENSDTR,      TP_STD,        TAIL_ADR( ensdtr      )},
{XDPLAFO,      TP_DSK_BG_DL,  TAIL_ADR( dplafo      )},
{XMSUZER,      TP_STD,        TAIL_ADR( msuzer      )},
{XENKRQD,      TP_STD,        TAIL_ADR( enkrqd      )},
{XMEXTSI,      TP_STD,        TAIL_ADR( mextsi      )},
{XMTIANF,      TP_STD,        TAIL_ADR( mtianf      )},
{XDSUSEI,      TP_STD,        TAIL_ADR( dsusei      )},
{XDRADS1,      TP_STD,        TAIL_ADR( drads1      )},
{XDEXRS,       TP_STD,        TAIL_ADR( dexrs       )},
{XMSIGEX,      TP_STD,        TAIL_ADR( msigex      )},
{XMSSZSP,      TP_STD,        TAIL_ADR( msszsp      )},
{IROM_GRDST,   TP_STD,        TAIL_ADR( ROm_GrdSt   )},
{IDIM_FOR,     TP_STD,        TAIL_ADR( DIm_For     )},
{IDIM_FORON,   TP_STD,        TAIL_ADR( DIm_ForOn   )},
{ISPM_DOWN,    TP_STD,        TAIL_ADR( SPm_Down    )},
{XMFTRKS,      TP_STD,        TAIL_ADR( mftrks      )},
{XMASWOK,      TP_STD,        TAIL_ADR( maswok      )},
/* ---------------- BEGIN_MODE_10 ----------------------------------------- */
#ifndef MODE_10
   {XMSUM11,   TP_STD,        TAIL_ADR( msum11      )},
#endif
/* ---------------- END_MODE_10 ------------------------------------------- */
{XMSUM12,      TP_STD,        TAIL_ADR( msum12      )},
{XMSUM13,      TP_STD,        TAIL_ADR( msum13      )},
{XMSUM14,      TP_STD,        TAIL_ADR( msum14      )},
{XMSUM15,      TP_STD,        TAIL_ADR( msum15      )},
{XMTUM11,      TP_STD,        TAIL_ADR( mtum11      )},
{XMTUM12,      TP_STD,        TAIL_ADR( mtum12      )},
{XMTUM13,      TP_STD,        TAIL_ADR( mtum13      )},
{XMTUM14,      TP_STD,        TAIL_ADR( mtum14      )},
{XMTUM15,      TP_STD,        TAIL_ADR( mtum15      )},
{XMTUM16,      TP_STD,        TAIL_ADR( mtum16      )},
{XMPUM11,      TP_STD,        TAIL_ADR( mpum11      )},
{XMPUM12,      TP_STD,        TAIL_ADR( mpum12      )},
{XMPUM13,      TP_STD,        TAIL_ADR( mpum13      )},
{XMPUM14,      TP_STD,        TAIL_ADR( mpum14      )},
{XMPUM15,      TP_STD,        TAIL_ADR( mpum15      )},
{XMEINR,       TP_STD,        TAIL_ADR( meinr       )},
{XMHAND,       TP_STD,        TAIL_ADR( mhand       )},
{XMHALB,       TP_STD,        TAIL_ADR( mhalb       )},
{XMAUTO,       TP_STD,        TAIL_ADR( mauto       )},
{XMI4B6,       TP_STD,        TAIL_ADR( mi4b6       )},
{XMIHOEH,      TP_STD,        TAIL_ADR( mihoeh      )},
{XMPAUSD,      TP_STD,        TAIL_ADR( mpausd      )},
{XMIKANF,      TP_STD,        TAIL_ADR( mikanf      )},
{XMXSTDT,      TP_STD,        TAIL_ADR( mxstdt      )},
{XFPFISC,      TP_STD,        TAIL_ADR( fpfisc      )},
{XFWEG1,       TP_STD,        TAIL_ADR( fweg1       )},
{XFWEG2,       TP_STD,        TAIL_ADR( fweg2       )},
{XFWEG3,       TP_STD,        TAIL_ADR( fweg3       )},
{XFWEG4,       TP_STD,        TAIL_ADR( fweg4       )},
{XFOELN,       TP_STD,        TAIL_ADR( foeln       )},
{XFMOTS,       TP_STD,        TAIL_ADR( fmots       )},
{XFTNOTA,      TP_STD,        TAIL_ADR( ftnota      )},
{XFATUR,       TP_STD,        TAIL_ADR( fatur       )},
{XFSTUR,       TP_STD,        TAIL_ADR( fstur       )},
{XFDTUR,       TP_STD,        TAIL_ADR( fdtur       )},
{XFSKMIN,      TP_STD,        TAIL_ADR( fskmin      )},
{XFPUV2,       TP_STD,        TAIL_ADR( fpuv2       )},
{XFE6,         TP_STD,        TAIL_ADR( fe6         )},
{XFE27,        TP_STD,        TAIL_ADR( fe27        )},
{XFKZNRF,      TP_STD,        TAIL_ADR( fkznrf      )},
{XFTSDR,       TP_STD,        TAIL_ADR( ftsdr       )},
{XFBFORM,      TP_STD,        TAIL_ADR( fbform      )},
{XFE4,         TP_STD,        TAIL_ADR( fe4         )},
{XFE5,         TP_STD,        TAIL_ADR( fe5         )},
{XFBLE10,      TP_STD,        TAIL_ADR( fble10      )},
{XFMOT13,      TP_STD,        TAIL_ADR( fmot13      )},
{XFOELVW,      TP_STD,        TAIL_ADR( foelvw      )},
{XFTNIDR,      TP_STD,        TAIL_ADR( ftnidr      )},
{XFNFSS,       TP_STD,        TAIL_ADR( fnfss       )},
{XFAUSW,       TP_STD,        TAIL_ADR( fausw       )},
{XFHOEHE,      TP_STD,        TAIL_ADR( fhoehe      )},
{XF4B21,       TP_STD,        TAIL_ADR( f4b21       )},
{XFKERN,       TP_STD,        TAIL_ADR( fkern       )},
{XFWEGF,       TP_STD,        TAIL_ADR( fwegf       )},
{XFHEIAU,      TP_STD,        TAIL_ADR( fheiau      )},
{XFSNEK,       TP_STD,        TAIL_ADR( fsnek       )},
{XFTDOS2,      TP_STD,        TAIL_ADR( ftdos2      )},
{XFANFLA,      TP_STD,        TAIL_ADR( fanfla      )},
{XFPROD,       TP_STD,        TAIL_ADR( fprod       )},
{XFTZYKL,      TP_STD,        TAIL_ADR( ftzykl      )},
{XFT2ZYK,      TP_STD,        TAIL_ADR( ft2zyk      )},
{XFTDOS1,      TP_STD,        TAIL_ADR( ftdos1      )},
{XFLICHT,      TP_STD,        TAIL_ADR( flicht      )},
{XFOELF,       TP_STD,        TAIL_ADR( foelf       )},
{XFPFET,       TP_STD,        TAIL_ADR( fpfet       )},
{XFLFET,       TP_STD,        TAIL_ADR( flfet       )},
{XFMAUS,       TP_STD,        TAIL_ADR( fmaus       )},
{XFDOS,        TP_STD,        TAIL_ADR( fdos        )},
{XFKMOT1,      TP_STD,        TAIL_ADR( fkmot1      )},
{XFTEMAB,      TP_STD,        TAIL_ADR( ftemab      )},
{XFEXSTP,      TP_STD,        TAIL_ADR( fexstp      )},
{XFEXGER,      TP_STD,        TAIL_ADR( fexger      )},
{XFEXSON,      TP_STD,        TAIL_ADR( fexson      )},
{XFDOS2,       TP_STD,        TAIL_ADR( fdos2       )},
{XFA2RUH,      TP_STD,        TAIL_ADR( fa2ruh      )},
{XFTEM5,       TP_STD,        TAIL_ADR( ftem5       )},
{XFTEM6,       TP_STD,        TAIL_ADR( ftem6       )},
{XF1WWC,       TP_STD,        TAIL_ADR( f1wwc       )},
{XFSONC,       TP_STD,        TAIL_ADR( fsonc       )},
{XFSOND,       TP_STD,        TAIL_ADR( fsond       )},
{XFSONE,       TP_STD,        TAIL_ADR( fsone       )},
{XFSONF,       TP_STD,        TAIL_ADR( fsonf       )},
{XFSONP0,      TP_STD,        TAIL_ADR( fsonp0      )},
{XFSONP1,      TP_STD,        TAIL_ADR( fsonp1      )},
{XFSONP2,      TP_STD,        TAIL_ADR( fsonp2      )},
{XFSONP3,      TP_STD,        TAIL_ADR( fsonp3      )},
{XFSONP4,      TP_STD,        TAIL_ADR( fsonp4      )},
{XFSONP5,      TP_STD,        TAIL_ADR( fsonp5      )},
{XFSONP6,      TP_STD,        TAIL_ADR( fsonp6      )},
{XFSONP7,      TP_STD,        TAIL_ADR( fsonp7      )},
{XFSONP8,      TP_STD,        TAIL_ADR( fsonp8      )},
{XFSONP9,      TP_STD,        TAIL_ADR( fsonp9      )},
{XFSONPA,      TP_STD,        TAIL_ADR( fsonpa      )},
{XFSONPB,      TP_STD,        TAIL_ADR( fsonpb      )},
{XFSONPC,      TP_STD,        TAIL_ADR( fsonpc      )},
{XFSONPD,      TP_STD,        TAIL_ADR( fsonpd      )},
{XFTKER1,      TP_STD,        TAIL_ADR( ftker1      )},
{XFTKER2,      TP_STD,        TAIL_ADR( ftker2      )},
{XFBEND1,      TP_STD,        TAIL_ADR( fbend1      )},
{XFBEND2,      TP_STD,        TAIL_ADR( fbend2      )},
{XFK1POS,      TP_STD,        TAIL_ADR( fk1pos      )},
{XFK2POS,      TP_STD,        TAIL_ADR( fk2pos      )},
{XFKBLK1,      TP_STD,        TAIL_ADR( fkblk1      )},
{XFKBLK2,      TP_STD,        TAIL_ADR( fkblk2      )},
{XFKBLAU,      TP_STD,        TAIL_ADR( fkblau      )},
{XFSTART,      TP_STD,        TAIL_ADR( fstart      )},
{XFSCHWE,      TP_STD,        TAIL_ADR( fschwe      )},
{XFKZAUS,      TP_STD,        TAIL_ADR( fkzaus      )},
{XFA1RUH,      TP_STD,        TAIL_ADR( fa1ruh      )},
{XFWHTAB,      TP_STD,        TAIL_ADR( fwhtab      )},
{XFFELDKL,     TP_STD,        TAIL_ADR( ffeldkl     )},
{XFMODUL,      TP_STD,        TAIL_ADR( fmodul      )},
{XFMODTEMP,    TP_STD,        TAIL_ADR( fmodtemp    )},
{XFIOERR,      TP_STD,        TAIL_ADR( fioerr      )},
{XFCONF1,      TP_STD,        TAIL_ADR( fconf1      )},
{XFCONF2,      TP_STD,        TAIL_ADR( fconf2      )},
{XFSCHWE2,     TP_STD,        TAIL_ADR( fschwe2     )},
{XFAGSICH1,    TP_STD,        TAIL_ADR( fagsich1    )},
{XFAGSICH2,    TP_STD,        TAIL_ADR( fagsich2    )},
{XFK_PLIV1AK,  TP_STD,        TAIL_ADR( FK_PLiv1Ak  )},
{XF1B3,        TP_STD,        TAIL_ADR( f1b3        )},
{IFK_AGM_VOR,  TP_STD,        TAIL_ADR( FK_AGm_Vor  )},
{IFK_PLM_AKT,  TP_STD,        TAIL_ADR( FK_PLm_Akt  )},
{IFK_OELFIL1,  TP_STD,        TAIL_ADR( FK_OelFil1  )},
{IFK_OELFIL2,  TP_STD,        TAIL_ADR( FK_OelFil2  )},
{IFK_SGE_VEN,  TP_STD,        TAIL_ADR( FK_SGe_Ven  )},
{IFK_AWD_NUL,  TP_STD,        TAIL_ADR( FK_AWd_Nul  )},
{IFK_KEPRF,    TP_STD,        TAIL_ADR( FK_KEprf    )},
{XFK_PLIV2AK,  TP_STD,        TAIL_ADR( FK_PLiv2Ak  )},
{XFTEMAB2,     TP_STD,        TAIL_ADR( ftemab2     )},
{XFSNEK2,      TP_STD,        TAIL_ADR( fsnek2      )},
{XFTEMAB3,     TP_STD,        TAIL_ADR( ftemab3     )},
{XFSNEK3,      TP_STD,        TAIL_ADR( fsnek3      )},
{XFTEMAB4,     TP_STD,        TAIL_ADR( ftemab4     )},
{XFSNEK4,      TP_STD,        TAIL_ADR( fsnek4      )},
/* ------------------------------------------------------------------------ */
{XFK_PMMIN,    TP_STD,        TAIL_ADR( FK_PMmin    )},
/* ------------------------------------------------------------------------ */
{IFK_SPSTELL,  TP_STD,        TAIL_ADR( FK_SpStell  )},
/* ------------------------------------------------------------------------ */
{XIQSSONBIT0,  TP_STD,        TAIL_ADR( IQsSonBit0  )},
{XIQSSONBIT1,  TP_STD,        TAIL_ADR( IQsSonBit1  )},
{XIQSSONBIT2,  TP_STD,        TAIL_ADR( IQsSonBit2  )},
{XIQSSONBIT3,  TP_STD,        TAIL_ADR( IQsSonBit3  )},
{XIQSSONBIT4,  TP_STD,        TAIL_ADR( IQsSonBit4  )},
{XIQSSONBIT5,  TP_STD,        TAIL_ADR( IQsSonBit5  )},
{XIQSSONBIT6,  TP_STD,        TAIL_ADR( IQsSonBit6  )},
{XIQSSONBIT7,  TP_STD,        TAIL_ADR( IQsSonBit7  )},
{XIQSSONBIT8,  TP_STD,        TAIL_ADR( IQsSonBit8  )},
{XIQSSONBIT9,  TP_STD,        TAIL_ADR( IQsSonBit9  )},
{XZYITANALYS,  TP_STD,        TAIL_ADR( ZYitAnalys  )},
{XSLM_SDREIN,  TP_STD,        TAIL_ADR( SLm_SDREin  )},
{XSLDPSDREIN,  TP_STD,        TAIL_ADR( SLdpSDREin  )},
{XOPTION_DV7,  TP_DL,         TAIL_ADR( OB_DV7      )},
{XPLS_RAMPE,   TP_STD,        TAIL_ADR( PLs_Rampe   )},
{XPLS_RAMPE2,  TP_STD,        TAIL_ADR( PLs_Rampe2  )},
{XPLS_RAMPE3,  TP_STD,        TAIL_ADR( PLs_Rampe3  )},
{XPLS_RAMPE4,  TP_STD,        TAIL_ADR( PLs_Rampe4  )},
{XPOMFOERDER,  TP_STD,        TAIL_ADR( POmFoerder  )},
{XOPMF_PACK,   TP_STD,        TAIL_ADR( OPmF_Pack   )},
{XOPMFP_PACK,  TP_STD,        TAIL_ADR( OPmFP_Pack  )},
{XFTDOS3,      TP_STD,        TAIL_ADR( ftdos3      )},
{XFDOS3,       TP_STD,        TAIL_ADR( fdos3       )},
{XFK_PLM3AKT,  TP_STD,        TAIL_ADR( FK_PLm3Akt  )},
/* ------------------------------------------------------------------------ */
{XMFOHOE,      TP_STD,        TAIL_ADR( mfohoe      )},
{IWAS_UEBV,    TP_DSK_BG_DL,  TAIL_ADR( WAs_Uebv    )},
{IWAS_UEBZ,    TP_DSK_BG_DL,  TAIL_ADR( WAs_Uebz    )},
{IWAS_FSS,     TP_DSK_BG_DL,  TAIL_ADR( WAs_fss     )},
{IFK_ROE_WS,   TP_STD,        TAIL_ADR( FK_ROe_ws   )},
{IFK_ROE_SI,   TP_STD,        TAIL_ADR( FK_ROe_si   )},
{IFK_ROE_AWV,  TP_STD,        TAIL_ADR( FK_ROe_awv  )},
{IFK_ROE_AWZ,  TP_STD,        TAIL_ADR( FK_ROe_awz  )},
{IFK_ROE_WO,   TP_STD,        TAIL_ADR( FK_ROe_wo   )},
{IFK_ROFRG,    TP_STD,        TAIL_ADR( FK_ROfrg    )},
{IWZM_HANF,    TP_STD,        TAIL_ADR( WZm_HAnf    )},
/*------------------- Qualitaetskontrolle --------------------------------*/
{IQUSNSUB,     TP_DSK_BG_DL,  TAIL_ADR( QUsnsub     )},
{IQUSNEXZ,     TP_DSK_BG_DL,  TAIL_ADR( QUsnexz     )},
{IQUSNINV,     TP_DSK_BG_DL,  TAIL_ADR( QUsninv     )},
/*------------------ Selektierweiche -------------------------------------*/
{IQUS_SPRANG,  TP_DSK_BG_DL,  TAIL_ADR( QUs_SprAng  )},
{IQUS_INVERS,  TP_DSK_BG_DL,  TAIL_ADR( QUs_Invers  )},
/*------------------ Heizungsoptimierung ---------------------------------*/
{IHEM_READY,   TP_STD,        TAIL_ADR( HEm_Ready   )},
{IHEM_START,   TP_STD,        TAIL_ADR( HEm_Start   )},
/* ------------------------------------------------------------------------ */
{IKZM_SOND,    TP_STD,        TAIL_ADR( KZm_Sond    )},
{IHEM_ABORT,   TP_STD,        TAIL_ADR( HEm_Abort   )},
/* ------------------------------------------------------------------------ */
{IFK_SKM2TUR,  TP_STD,        TAIL_ADR( FK_SKm2Tur  )},
/* ------------------------------------------------------------------------ */
{XFK_DRSB707,  TP_STD,        TAIL_ADR( FK_DrSB707  )},
/* ------------------------------------------------------------------------ */
{XFK_SGM1TUR,  TP_STD,        TAIL_ADR( FK_SGm1Tur  )},
{XFK_SGM2TUR,  TP_STD,        TAIL_ADR( FK_SGm2Tur  )},
/* ------------------------------------------------------------------------ */
{XFK_FHMIN,    TP_STD,        TAIL_ADR( FK_FHmin    )},
/* ------------------------------------------------------------------------ */
{XFK_SGM1SS,   TP_STD,        TAIL_ADR( FK_SGm1SS   )},
/* ------------------------------------------------------------------------ */
{XFK_PLEDRIVE, TP_STD,        TAIL_ADR( FK_PLeDrive )},
{XFK_PLEINIT,  TP_STD,        TAIL_ADR( FK_PLeInit  )},
{XFK_PLEWARN,  TP_STD,        TAIL_ADR( FK_PLeWarn  )},
{XOPM_EPLAST,  TP_STD,        TAIL_ADR( OPm_EPlast  )},
{XOPM_LUFT8,   TP_STD,        TAIL_ADR( OPm_Luft8   )},
/* ------------------------------------------------------------------------ */
{XFTDOS4,      TP_STD,        TAIL_ADR( ftdos4      )},
{XFDOS4,       TP_STD,        TAIL_ADR( fdos4       )},
{XFK_PLM4AKT,  TP_STD,        TAIL_ADR( FK_PLm4Akt  )},
{XFSCHWE3,     TP_STD,        TAIL_ADR( fschwe3     )},
{XFSCHWE4,     TP_STD,        TAIL_ADR( fschwe4     )},
{XFA3RUH,      TP_STD,        TAIL_ADR( fa3ruh      )},
{XFA4RUH,      TP_STD,        TAIL_ADR( fa4ruh      )},
{XFAGSICH3,    TP_STD,        TAIL_ADR( fagsich3    )},
{XFAGSICH4,    TP_STD,        TAIL_ADR( fagsich4    )},
{XFWEG12,      TP_STD,        TAIL_ADR( fweg12      )},
{XFWEG13,      TP_STD,        TAIL_ADR( fweg13      )},
{XFWEG14,      TP_STD,        TAIL_ADR( fweg14      )},
{XFK_DRB7208,  TP_STD,        TAIL_ADR( FK_DrB7208  )},
{XFK_DRB7308,  TP_STD,        TAIL_ADR( FK_DrB7308  )},
{XFK_AGM3VOR,  TP_STD,        TAIL_ADR( FK_AGm3Vor  )},
{XFK_AGM4VOR,  TP_STD,        TAIL_ADR( FK_AGm4Vor  )},
{XFK_PLIV3AK,  TP_STD,        TAIL_ADR( FK_PLiv3Ak  )},
{XFK_PLIV4AK,  TP_STD,        TAIL_ADR( FK_PLiv4Ak  )},
/* ------------------------------------------------------------------------ */
{XFK_WTABGEL,  TP_STD,        TAIL_ADR( FK_WTabgel  )},
{XFK_SPSDIAG,  TP_STD,        TAIL_ADR( FK_SPSDiag  )},
{XFK_NOWZBEW,  TP_STD,        TAIL_ADR( FK_NoWZBew  )},
{XFK_AWS99F,   TP_STD,        TAIL_ADR( FK_AWS99F   )},
{XFK_AWSFULL,  TP_STD,        TAIL_ADR( FK_AWSFull  )},
/* ---------------- SPS-Optionsbits Wenden/Werkzeugauswerfer -------------- */
{XOP_WENDEN,   TP_STD,        TAIL_ADR( OP_Wenden   )},
{XOP_WDGR_GS,  TP_STD,        TAIL_ADR( OP_WDgr_gs  )},
{XOP_WKZAUSW,  TP_STD,        TAIL_ADR( OP_WkzAusw  )},
{XOP_WKZAPV,   TP_STD,        TAIL_ADR( OP_WkzApv   )},
/* ------------------------------------------------------------------------ */
{XUP_SPSTEXT,  TP_STD,        TAIL_ADR( UP_SPSText  )},
/* ------------------------------------------------------------------------ */
{IKEEINAUS,    TP_DL,         TAIL_ADR( KEEinAus    )},
{IKELINEACT,   TP_STD,        TAIL_ADR( KELineAct0  )},
/* ------------------------------------------------------------------------ */
{XFMOTS2,      TP_STD,        TAIL_ADR( fmots2      )},
{XFMOT132,     TP_STD,        TAIL_ADR( fmot132     )},
/* ---------------- Airpress ---------------------------------------------- */
{XOPM_AIRPR,   TP_STD,        TAIL_ADR( OPm_Airpr   )},
{XOPM_APPROP,  TP_STD,        TAIL_ADR( OPm_APProp  )},
{XOPM_APIP,    TP_STD,        TAIL_ADR( OPm_APip    )},
{XFK_APEAKTIV, TP_STD,        TAIL_ADR( FK_APeAktiv )},
{XFK_APSTOER,  TP_STD,        TAIL_ADR( FK_APStoer  )},
{XFK_APPESYST, TP_STD,        TAIL_ADR( FK_APpeSysT )},
/* ---------------- Kartonzaehler ----------------------------------------- */
{XOPM_KARTON,  TP_STD,        TAIL_ADR( OPm_Karton  )},
{XFK_KARTON1,  TP_STD,        TAIL_ADR( FK_Karton1  )},
/* ---------------- Werkzeug Wenden --------------------------------------- */
{XWDMPENDLAG,  TP_DSK_BG_DL,  TAIL_ADR( WDmpEndlag  )},
{XWDM_FUNKRS,  TP_DSK_BG_DL,  TAIL_ADR( WDm_Funkrs  )},
/* ---------------- Werkzeug Drehteller-Parameter ------------------------- */
{XDTSZSPUMK,   TP_STD,        TAIL_ADR( DTszSpumk   )},
{XDTIZSPUMK,   TP_STD,        TAIL_ADR( DTizSpumk   )},
{XDTSZDRUMK,   TP_STD,        TAIL_ADR( DTszDrumk   )},
{XDTIZDRUMK,   TP_STD,        TAIL_ADR( DTizDrumk   )},
/* ---------------- Werkzeugauswerfer ------------------------------------- */
{XWZA_CHKVOR,  TP_DSK_BG_DL,  TAIL_ADR( WZA_Chkvor  )},
{XWZA_CHKZUR,  TP_DSK_BG_DL,  TAIL_ADR( WZA_Chkzur  )},
{XWZA_CHKFSS,  TP_DSK_BG_DL,  TAIL_ADR( WZA_ChkFSS  )},
/* ---------------- Fehlermeldungen Wenden -------------------------------- */
{XFK_DTNREF,   TP_STD,        TAIL_ADR( FK_DTnRef   )},
{XFK_ENDWEND,  TP_STD,        TAIL_ADR( FK_EndWend  )},
{XFK_BLWEND,   TP_STD,        TAIL_ADR( FK_BlWend   )},
{XFK_SPWEND,   TP_STD,        TAIL_ADR( FK_SPWend   )},
{XFK_EPKOVER,  TP_STD,        TAIL_ADR( FK_EPkOver  )},
{XFK_ELNFIX,   TP_STD,        TAIL_ADR( FK_ELnFix   )},
{XFK_DTBLOCK,  TP_STD,        TAIL_ADR( FK_DTBlock  )},
/* ---------------- Fehlermeldungen Werkzeugauswerfer --------------------- */
{XFK_WZAVBL,   TP_STD,        TAIL_ADR( FK_WZAvBl   )},
{XFK_WZAZBL,   TP_STD,        TAIL_ADR( FK_WZAzBl   )},
{XFK_WZAECHK,  TP_STD,        TAIL_ADR( FK_WZAEChk  )},
/* ------------------------------------------------------------------------ */
{XFK_PLETEMP,  TP_STD,        TAIL_ADR( FK_PLeTemp  )}, 
{XFK_PLEPOWER, TP_STD,        TAIL_ADR( FK_PLePower )}, 
/* ---------------- Spritzeinheit-Abgleich -------------------------------- */
{XSEABGLST1,   TP_STD,        TAIL_ADR( SEAbglST1   )},
{XSEABGLST2,   TP_STD,        TAIL_ADR( SEAbglST2   )},
{XSEABGLRS1,   TP_STD,        TAIL_ADR( SEAbglRS1   )},
{XSEABGLRS2,   TP_STD,        TAIL_ADR( SEAbglRS2   )},
{XSEABGLTASTE1,TP_STD,        TAIL_ADR( SEAbglTas1  )},
{XSEABGLTASTE2,TP_STD,        TAIL_ADR( SEAbglTas2  )},
/* ---------- SPS Optionsbits --------------------------------------------- */  
{XSPS_OPTION1, TP_DL,         TAIL_ADR( OBIQTPLC1  )},
{XSPS_OPTION2, TP_DL,         TAIL_ADR( OBIQTPLC2  )},
{XSPS_OPTION3, TP_DL,         TAIL_ADR( OBIQTPLC3  )},
{XSPS_OPTION4, TP_DL,         TAIL_ADR( OBIQTPLC4  )},
{XSPS_OPTION5, TP_DL,         TAIL_ADR( OBIQTPLC5  )},
{XSPS_OPTION6, TP_DL,         TAIL_ADR( OBIQTPLC6  )},
{XSPS_OPTION7, TP_DL,         TAIL_ADR( OBIQTPLC7  )},
{XSPS_OPTION8, TP_DL,         TAIL_ADR( OBIQTPLC8  )},
{XSPS_OPTION9, TP_DL,         TAIL_ADR( OBIQTPLC9  )},
{XSPS_OPTION10,TP_DL,         TAIL_ADR( OBIQTPLC10 )},
{XSPS_OPTION11,TP_DL,         TAIL_ADR( OBIQTPLC11 )},
{XSPS_OPTION12,TP_DL,         TAIL_ADR( OBIQTPLC12 )},
{XSPS_OPTION13,TP_DL,         TAIL_ADR( OBIQTPLC13 )},
{XSPS_OPTION14,TP_DL,         TAIL_ADR( OBIQTPLC14 )},
{XSPS_OPTION15,TP_DL,         TAIL_ADR( OBIQTPLC15 )},
{XSPS_OPTION16,TP_DL,         TAIL_ADR( OBIQTPLC16 )},
/* ------------------------------------------------------------------------ */
{XQUM_IQTFRD  ,TP_STD,        TAIL_ADR( QUm_IQTfrd  )}, /* 71.0 SPS-Freigabebit Foerderband         */
{XOPM_IQT800  ,TP_STD,        TAIL_ADR( OPm_IQT800  )}, /* SPS_IQT-Option Kuehlwasser-Abschaltung Seite 80 */
/* ------------------------------------------------------------------------ */
{XFK_XSM_ANF  ,TP_STD,        TAIL_ADR( FK_XSm_Anf  )}, /* Fehlerbit Produktionsstart: Parameter aktiv */          
{XFK_XSM_AN2  ,TP_STD,        TAIL_ADR( FK_XSm_An2  )}, /* Fehlerbit Produktionsstart: WKZ-Sicherungsdruck aktiv */
/* ------------------------------------------------------------------------ */
{XFK_SE1WEGM,  TP_STD,        TAIL_ADR( FK_SE1WegM  )},
{XFK_SE1NACT,  TP_STD,        TAIL_ADR( FK_SE1NAct  )}, 
{XFK_SE2WEGM,  TP_STD,        TAIL_ADR( FK_SE2WegM  )},
{XFK_SE2NACT,  TP_STD,        TAIL_ADR( FK_SE2NAct  )},
/* ------------------------------------------------------------------------ */
{XFK_IOE_DI1,  TP_STD,        TAIL_ADR( FK_IOe_DI1  )}, 
{XFK_IOE_DI2,  TP_STD,        TAIL_ADR( FK_IOe_DI2  )}, 
{XFK_IOE_DI3,  TP_STD,        TAIL_ADR( FK_IOe_DI3  )}, 
{XFK_IOE_DI4,  TP_STD,        TAIL_ADR( FK_IOe_DI4  )}, 
/* ------------------------------------------------------------------------ */
{IOM_AOIQT,    TP_STD,        TAIL_ADR( OPm_AOIqt   )},
{IOM_DIOIQT,   TP_STD,        TAIL_ADR( OPm_DIOIqt  )},
/* ------------------------------------------------------------------------ */
{XFK_SERINI,   TP_STD,        TAIL_ADR( FK_SerIni   )},
{XFK_SERCOM,   TP_STD,        TAIL_ADR( FK_SerCom   )},
{XFK_SEREXT,   TP_STD,        TAIL_ADR( FK_SerExt   )},
{XFK_SERPRO,   TP_STD,        TAIL_ADR( FK_SerPro   )},
{XHXSNECHO,    TP_DSK_BG_DL,  TAIL_ADR( HXsnEcho    )},
{XHXSNECHO_2  ,TP_DSK_BG_DL,  TAIL_ADR( HXsnEcho_2  )}, /* Echobit_2 S. 39.9 */
{XOPM_IQT399  ,TP_STD,        TAIL_ADR( OPm_IQT399  )}, /* Komunikation fuer SPS-freigabe der S. 39.9 */ 
{XOPM_IQT710  ,TP_STD,        TAIL_ADR( OPm_IQT710  )}, /* Komunikation fuer SPS-freigabe der S. 71.0 */               
{XSGM_SETPOS  ,TP_STD,        TAIL_ADR( SGm_SetPos  )}, /* Komunikation fuer Zwischenposition Schutztuer S. 71.0 */
{XFK_SGERR1   ,TP_STD,        TAIL_ADR( FK_SGErr1   )}, /* Fehlerbit St|rung vordere Schutzt}rantrieb */
{XFK_SGERR2   ,TP_STD,        TAIL_ADR( FK_SGErr2   )}, /* Fehlerbit Blockierung der vorderen Schutzt}r*/
{XFK_SGREF    ,TP_STD,        TAIL_ADR( FK_SGRef    )}, /* Fehlerbit Vordere Schutzt}r nicht referenziert */
/* ---------------- Werkzeugauswerfer ------------------------------------- */
{XOP_WKZAUSW2, TP_STD,        TAIL_ADR( OP_WkzAus2  )},
{XWZA2CHKVOR,  TP_DSK_BG_DL,  TAIL_ADR( WZA2Chkvor  )},
{XWZA2CHKZUR,  TP_DSK_BG_DL,  TAIL_ADR( WZA2Chkzur  )},
{XWZA2CHKFSS,  TP_DSK_BG_DL,  TAIL_ADR( WZA2ChkFSS  )},
{XFK_WZA2VBL,  TP_STD,        TAIL_ADR( FK_WZA2vbl  )}, /* FK: Werkzeugauswerfer 2 vor blockiert    */
{XFK_WZA2ZBL,  TP_STD,        TAIL_ADR( FK_WZA2zbl  )}, /* FK: Werkzeugauswerfer 2 zur}ck blockiert */
{XFK_WZA2EPR,  TP_STD,        TAIL_ADR( FK_WZA2epr  )}, /* FK: Endlage Werkzeugauswerfer 2 pr}fen   */
/* ------------------------------------------------------------------------ */
{XFK_TSTAGG2,  TP_STD,        TAIL_ADR( FK_TstAgg2  )}, /* FK: Zusatztasten Seitenaggregat aktiv    */        
{XFK_AG2SICH,  TP_STD,        TAIL_ADR( FK_Ag2Sich  )}, /* FK: Absicherung Nebenaggregat            */        
{XFK_PUEBERS,  TP_STD,        TAIL_ADR( FK_pUebers  )}, /* FK: Fehler Druck}bersetzer               */        
{XFK_WESMIRD,  TP_STD,        TAIL_ADR( FK_WEsmird  )}, /* FK: Schmierdruck Drehteller nicht erreicht   */    
{XFK_QUIT   ,  TP_STD,        TAIL_ADR( FK_Quit     )}, /* FK: Bitte Quittiertaste bet{tigen            */    
{XFK_QUITBGS,  TP_STD,        TAIL_ADR( FK_QuitBgS  )}, /* FK: Quittiertaste Bediengegenseite bet{tigen */    
{XFK_QUTIBS ,  TP_STD,        TAIL_ADR( FK_QuitBS   )}, /* FK: Quittiertaste Bedienseite bet{tigen      */    
{XFK_NEHI   ,  TP_STD,        TAIL_ADR( FK_NeHi     )}, /* FK: Monoaggregat nicht in richtiger Stellung */    
{XFK_SNIKOKM,  TP_STD,        TAIL_ADR( FK_SNikOkM  )}, /* FK: Schneckenfreigabe Monoaggregat fehlt     */    
{XFK_ZHMABNI,  TP_STD,        TAIL_ADR( FK_ZHmAbNI  )}, /* FK: Temperaturabsenkung Monoaggregat l{uft   */    
{XFK_ZHM_AUM,  TP_STD,        TAIL_ADR( FK_ZHm_AuM  )}, /* FK: Heizung Monoaggregat ausgeschaltet       */    
{XFK_ARRET  ,  TP_STD,        TAIL_ADR( FK_Arret    )}, /* FK: Arretierung l|sen                        */    
{XFK_MECHSSP,  TP_STD,        TAIL_ADR( FK_mechSsp  )}, /* FK: Mechanische Schlie~sperre                */    
{XFK_MSPESDF,  TP_STD,        TAIL_ADR( FK_mSpESdf  )}, /* FK: Mechanische Schlie~sperre Endschalter defekt */
{XFK_EINRICH,  TP_STD,        TAIL_ADR( FK_Einrich  )}, /* FK: Einrichten bet{tigen                         */
{XFK_KEAWOST,  TP_STD,        TAIL_ADR( FK_KEAWoSt  )}, /* FK: Kernzug und Auswerfer bei offener Schutzt}r  */
{XFK_SPZYLNP,  TP_STD,        TAIL_ADR( FK_SPZylnP  )}, /* FK: Spannzylinder nicht in Position              */
{XFK_BAP44PR,  TP_STD,        TAIL_ADR( FK_BAP44pr  )}, /* FK: Betriebsart Seite 44 pr}fen                  */
{XFK_MISCHK ,  TP_STD,        TAIL_ADR( FK_Mischk   )}, /* FK: Fehler Mischkopfbetrieb                      */
{XFK_WPKTNPL,  TP_STD,        TAIL_ADR( FK_Wpktnpl  )}, /* FK: Wegpunkt nicht plausibel                     */
{XFK_UWWKZBW,  TP_STD,        TAIL_ADR( FK_UwWkzBw  )}, /* FK: ]berwachung Werkzeugbewegung                 */
{XFK_UWAWBEW,  TP_STD,        TAIL_ADR( FK_UwAWBew  )}, /* FK: ]berwachung Auswerferbewegung                */
{XFK_PARPROD,  TP_STD,        TAIL_ADR( FK_ParProd  )}, /* FK: Parameter Produktionsstart                   */
{XFK_WSWTDF ,  TP_STD,        TAIL_ADR( FK_WS2WTdf  )}, /* FK: Wegmesssystem 2 Wendetisch defekt            */
/* ------------------------------------------------------------------------ */
{XOP_CANWINK,  TP_STD,        TAIL_ADR( OP_CanWink  )}, /* Optionsbit CAN-Winkelkodierer            */        
{XFK_CANWINK,  TP_STD,        TAIL_ADR( FK_CanWink  )}, /* FK: Fehler Winkelkodierer                */        
{0xffff} /* ENDEKENNUNG: muss IMMER da sein */          
};
