/*.SH.**********************************************************************
*
*  HEADER-DATEI-NAME:
*     GLOBAL.H
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
*     01.04.92 -PR-    Portierung des IQT-350 auf IQT-450
*     08.05.92 -PR-    Einfuehrung des neuen Konzepts fuer Header-Dateien
*     11.06.92 -SF-    TREND_NO und SPC_NO nach <trend.h>, <spc.h> verlagert
*     16.06.92 -SF-    Glob_TabVal eingefuegt
*     09.10.92 -PR-    NrPages aus BBram uebernommen
*     20.04.93 -PR-    TlgRegPort und TlgAddrTab eingefuegt
*     22.05.93 -PR-    ActInpEP eingefuegt
*     01.07.97 -TSchw- KbdPortAt_ptr entfernt
*     26.02.98 -TSchw- CoreVersNeededByDstruct eingefuegt
*     11.03.98 -TSchw- DiagFileHandle eingefuegt
*     09.02.00 -TSchw- SoftkeyHandle__ Tabelle von 6 auf 8 Softkeys erweitert
*     07.06.00 -TSchw- Verschiedene Dimensionen von Handles von 4 auf 5 erhoeht.
*     08.11.00 -TSchw- Handle für Kartenleser eingefuegt, siehe CardHandle
*     19.03.01 -TSchw- Handle und Semaphore für Euromap 17 Device eingefügt, 
*                      siehe EM17
*     04.05.01 -TSchw- Neu ab KPTool V.2.00: ToolParamTabAdd, AggParamTabAdd,
*                      SnParamTab1Add, SnParamTab2Add, SnParamTab3Add,
*                      PlausParamTab (siehe KPTool V.2.00).
*     30.07.01 -TSchw- Letzten Index von SoftkeyHandle__ entfernt, da jetzt
*                      beide Softkeyzeilen in ein einziges Textfenster
*                      geschrieben werden (damit ggf. auch normalgroße Fonts
*                      verwendet werden können, z.B. für Chinesisch).
*     15.08.01 -TSchw- VersText, SpecText und TimeText existieren nicht mehr
*                      und wurden hier entfernt.
*     13.12.02 -HA-    SnParamTabAdd angefuegt.
*                      SPSType angefuegt.
*                      ExclDRVERRSema__ angefügt.
*     13.02.03 -HA-    ErrLineHandle eingefuegt.
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

#ifndef _global
#define _global

/*.SI.***********************************************************************/
#include <syntax.h>
#include <iqttsk.h>
#include <iqtmem.h>
#include <iqtdev.h>
#include <telereg.h>
#include <host.h>
#include <ifk.h>
#include <bde.h>
#include <trend.h>
#include <spc.h>
#include <g_const.h>
#include <dstruct.h>
#include <dsdisk.h>
#include <disk.h>
#include <drverror.h>
/*.EI.***********************************************************************/

#define  MAX_FIX_HANDLE   4      /* Anzahl fester Handles */
#define  MAX_VAR_HANDLE   6      /* Anzahl variabler Handles */

#define  MAX_TASK_FLAGS    256/8

#define PPC_CHANNELS            4

typedef struct shared_data_type {
SEMAPHORE ExclSPCSema__;
SEMAPHORE ExclActElementSema__;
SEMAPHORE ExclBDESema__;
SEMAPHORE ExclCursorSema__;
SEMAPHORE ExclDarkSema__;
SEMAPHORE ExclPrintSema__;
SEMAPHORE ExclCyclePrintSema__;
SEMAPHORE ExclIscosSema__;
SEMAPHORE ExclHostBufferSema__;
SEMAPHORE ExclHostErrBufSema__;
SEMAPHORE ExclSollInpSema__;
SEMAPHORE ExclBlueWhiteSema__;
SEMAPHORE ExclPortSema__;
SEMAPHORE ExclCLBSema__;
SEMAPHORE ExclScreenSema__;
SEMAPHORE ExclWindowSema__;
MSGPORT BuildScreenPort__;
MSGPORT ScreenUpdatePort__;
MSGPORT PrintPagePort__;
MSGPORT BDEPort__;
MSGPORT InjRegPort__;
MSGPORT TlgRegPort__;
MSGPORT DiagModePort__;
MSGPORT PGPort__;
MSGPORT * KbdPort_ptr__;
IQT_HANDLE TextHandle__[5][MAX_FIX_HANDLE];
IQT_HANDLE HelpHandle__[5][2];
IQT_HANDLE StatLineHandle__[5];
IQT_HANDLE SoftkeyParent__[5];
IQT_HANDLE SoftkeyHandle__[5][8];
IQT_HANDLE VarHandle__[5][MAX_VAR_HANDLE];
IQT_HANDLE HostCrtHandle__[5];
IQT_HANDLE DiagOutHandle__;
IQT_HANDLE DiagStatHandle__;
IQT_HANDLE ControllerHandle__[PPC_CHANNELS];
IQT_HANDLE MeasureHandle__;
IQT_HANDLE KbdHandle__;
IQT_HANDLE RtcHandle__;
IQT_HANDLE * ComHandle__;
IQT_HANDLE DiagPrintHandle__;
IQT_HANDLE RobotHandle__;
IQT_HANDLE HostHandle__;
IQT_HANDLE PortHandle__;
IQT_HANDLE CardHandle__;
TASKFLAGS BgTaskFlag__[MAX_TASK_FLAGS];
BYTE BackgroundDataset__;
BYTE OptFunction__;
BYTE CompareFgBg__;
BYTE SetupValueChanged__;
BYTE SmallScreenActive__;
BYTE HelpActive__;
BYTE ProcGraphActiveTab__[4];
BYTE HostAccess__;
BYTE LineFlag__;
BYTE LineDirect__;
HEADER_DSTRUCT * HeaderP__;
char ** PrnProgListTabP__;
UWORD ActPageIndex__;
UWORD ActPageNr__;
UWORD ActObjectIndex__;
OBJECT * ActObject__;
ELEMENT * ActElement__;
BYTE ActSollExist__;
int ActBitArrayInd__;
UWORD SmallPageIndex__;
BYTE KlickMode__;
OBJECT * ShowKlickObject__;
ELEMENT * VarHandleEl__[5][MAX_VAR_HANDLE];
ELEMENT * SollInpEP__;
ELEMENT * ActInpEP__;
long LParamUser1__;
char * TParamUser1__;
COLOR ChangeCol__;
POS ChangeTextPos__;
GRAPHPOS ChangeGraphPos__;
BYTE Change__;
BYTE InfoForDark__;
UWORD GotoPageNr__;
long GotoVarNr__;
BYTE NrPages__;
int ActLanguage__;
BOOL StopScreenUpdate__;
BOOL StopWindowUpdate__;
void * ScreenUpdateList__[8];
BYTE FastRegDone__;
BYTE DiagInitFlag__;
int InjHeatChange__;
int MinKeyPos__;
BYTE ScreenPrinted__;
int Print_CycleCount__;
int Print_TimeCount__;
BOOL Print_AutMashStopPrinted__;
BOOL DiagModeActive__;
int DiagIscosNo__;
TLGADR_TYPE * TlgAddrTab__;
TICKER Ticker__;
int Glob_TabVal__;
BOOL DataTransferActive__;
/*      Kundenprom
 */
char    *VersKprom__;
char    *SpecKprom__;
char    *TimeKprom__;
BYTE    *OptionTab__;
UWORD   *ToolParamTab__;
UWORD   *AggParamTab__;
UWORD   *SnParamTab1__;
UWORD   *SnParamTab2__;
UWORD   *SnParamTab3__;
UWORD   MaxInjUnits__;
UWORD   MaxResUnits__;
UWORD   MaxInjCyc__;
UWORD   MaxStat__;
UWORD   MaxToolHeatZones__;
UWORD   MaxResHeatZones__;
UWORD   MaxTempTools__;
UWORD   MaxRegler__;
UWORD   MaxTrk__;
UWORD   MaxHeatRegs__;
UWORD   MaxInjHeatZones__;
UWORD   MaxDMAAddr__;
UWORD   *TlgDMAAddr__;
char    *OrderNr__;
char    *MashineNr__;
char    *MashineType__;
char    *ClosePower__;
char    *Language1__;
char    *Language2__;
char    *Language3__;
char    *IqtVersion__;
char    *Customer__;
char    *FreeText1__;
char    *FreeText2__;
char    *FreeText3__;
char    *FreeText4__;
int     CLB_SollBufSize__;
int     CLB_IstBufSize__;
int     CLB_ErrBufSize__;
char    *CLB_Password__;
int     MaxIntfKonf__;
INTF_KONF_TYPE * IntfKonf__;
int     MaxDevKonf__;
DEV_KONF_TYPE * DevKonf__;
UWORD   *FreeTabP__;
UWORD   *InjSpeed_Max__;
UWORD   *InjSpeed_Conv__;
BYTE    *InjHeatTabP__;
BYTE    *ToolHeatTabP__; 
BYTE    *TempHeatTabP__; 
BYTE    OilHeat__;
BYTE    *ResHeatTabP__; 
char    *ReglerNameP__;
UWORD   *ReglerParamP__;
BYTE    ScreenSaveTime__;
/*      Versionen
 */
char VersIqtkern__[30];
char SpecIqtkern__[30];
char TimeIqtkern__[30];
char CoreVersNeededByDstruct__[30];
char VersDstruct__[30];
char SpecDstruct__[30];
char TimeDstruct__[30];
char VersText__[3][30];
char SpecText__[3][30];
char TimeText__[3][30];
/* weitere globale Daten
 */
UWORD * SnParamTab__;
BYTE * OptModeTabP__;
REGIST *        SPCPTab__[SPCNO];
UWORD BDEFirstStopError__;
UWORD BDELastStopError__;
BYTE * ASCIIGraph__;
OBJECT FreeObjTab1__[MAX_FREEOBJTAB];
OBJECT FreeObjTab2__[MAX_FREEOBJTAB];
OBJECT FreeObjTab3__[MAX_FREEOBJTAB];
BOOL HeatErrorOK__;
WRITE_FILE_INFO * DiagFileHandle__;
IQT_HANDLE EM17Handle__;   /* EM17 */
SEMAPHORE ExclEM17Sema__;  /* EM17 */

/* Neu ab KPTool V.2.00: */
UWORD   *ToolParamTabAdd__;
UWORD   *AggParamTabAdd__;
UWORD   *SnParamTab1Add__;
UWORD   *SnParamTab2Add__;
UWORD   *SnParamTab3Add__;
UWORD   *PlausParamTab__;
char    *Lan1SpsText1__;
char    *Lan1SpsText2__;
char    *Lan1SpsText3__;
char    *Lan1SpsText4__;
char    *Lan1SpsText5__;
char    *Lan1SpsText6__;
char    *Lan1SpsText7__;
char    *Lan1SpsText8__;
char    *Lan1SpsText9__;
char    *Lan1SpsText10__;
char    *Lan1SpsText11__;
char    *Lan1SpsText12__;
char    *Lan1SpsText13__;
char    *Lan1SpsText14__;
char    *Lan1SpsText15__;
char    *Lan2SpsText1__;
char    *Lan2SpsText2__;
char    *Lan2SpsText3__;
char    *Lan2SpsText4__;
char    *Lan2SpsText5__;
char    *Lan2SpsText6__;
char    *Lan2SpsText7__;
char    *Lan2SpsText8__;
char    *Lan2SpsText9__;
char    *Lan2SpsText10__;
char    *Lan2SpsText11__;
char    *Lan2SpsText12__;
char    *Lan2SpsText13__;
char    *Lan2SpsText14__;
char    *Lan2SpsText15__;
char    *Lan3SpsText1__;
char    *Lan3SpsText2__;
char    *Lan3SpsText3__;
char    *Lan3SpsText4__;
char    *Lan3SpsText5__;
char    *Lan3SpsText6__;
char    *Lan3SpsText7__;
char    *Lan3SpsText8__;
char    *Lan3SpsText9__;
char    *Lan3SpsText10__;
char    *Lan3SpsText11__;
char    *Lan3SpsText12__;
char    *Lan3SpsText13__;
char    *Lan3SpsText14__;
char    *Lan3SpsText15__;
UWORD   *SnParamTabAdd__;
PARAMETER SPSType__;
SEMAPHORE ExclDRVERRSema__;
IQT_HANDLE ErrLineHandle__[5];
} SHARED_DATA_TYPE;

#ifdef C86

#define ExclSPCSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclSPCSema__)
#define ExclActElementSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclActElementSema__)
#define ExclBDESema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclBDESema__)
#define ExclCursorSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclCursorSema__)
#define ExclDarkSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclDarkSema__)
#define ExclPrintSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclPrintSema__)
#define ExclCyclePrintSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclCyclePrintSema__)
#define ExclIscosSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclIscosSema__)
#define ExclHostBufferSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclHostBufferSema__)
#define ExclHostErrBufSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclHostErrBufSema__)
#define ExclSollInpSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclSollInpSema__)
#define ExclBlueWhiteSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclBlueWhiteSema__)
#define ExclPortSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclPortSema__)
#define ExclCLBSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclCLBSema__)
#define ExclScreenSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclScreenSema__)
#define ExclWindowSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclWindowSema__)
#define BuildScreenPort (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->BuildScreenPort__)
#define ScreenUpdatePort (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ScreenUpdatePort__)
#define PrintPagePort (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->PrintPagePort__)
#define BDEPort (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->BDEPort__)
#define InjRegPort (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->InjRegPort__)
#define TlgRegPort (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TlgRegPort__)
#define DiagModePort (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DiagModePort__)
#define PGPort (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->PGPort__)
#define KbdPort_ptr (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->KbdPort_ptr__)
#define TextHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TextHandle__)
#define HelpHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->HelpHandle__)
#define StatLineHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->StatLineHandle__)
#define SoftkeyParent (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SoftkeyParent__)
#define SoftkeyHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SoftkeyHandle__)
#define VarHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->VarHandle__)
#define HostCrtHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->HostCrtHandle__)
#define DiagOutHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DiagOutHandle__)
#define DiagStatHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DiagStatHandle__)
#define ControllerHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ControllerHandle__)
#define MeasureHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MeasureHandle__)
#define KbdHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->KbdHandle__)
#define RtcHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->RtcHandle__)
#define ComHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ComHandle__)
#define DiagPrintHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DiagPrintHandle__)
#define RobotHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->RobotHandle__)
#define HostHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->HostHandle__)
#define PortHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->PortHandle__)
#define CardHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->CardHandle__)
#define BgTaskFlag (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->BgTaskFlag__)
#define BackgroundDataset (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->BackgroundDataset__)
#define OptFunction (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->OptFunction__)
#define CompareFgBg (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->CompareFgBg__)
#define SetupValueChanged (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SetupValueChanged__)
#define SmallScreenActive (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SmallScreenActive__)
#define HelpActive (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->HelpActive__)
#define ProcGraphActiveTab (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ProcGraphActiveTab__)
#define HostAccess (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->HostAccess__)
#define LineFlag (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->LineFlag__)
#define LineDirect (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->LineDirect__)
#define HeaderP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->HeaderP__)
#define PrnProgListTabP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->PrnProgListTabP__)
#define ActPageIndex (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActPageIndex__)
#define ActPageNr (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActPageNr__)
#define ActObjectIndex (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActObjectIndex__)
#define ActObject (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActObject__)
#define ActElement (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActElement__)
#define ActSollExist (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActSollExist__)
#define ActBitArrayInd (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActBitArrayInd__)
#define SmallPageIndex (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SmallPageIndex__)
#define KlickMode (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->KlickMode__)
#define ShowKlickObject (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ShowKlickObject__)
#define VarHandleEl (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->VarHandleEl__)
#define SollInpEP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SollInpEP__)
#define ActInpEP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActInpEP__)
#define LParamUser1 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->LParamUser1__)
#define TParamUser1 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TParamUser1__)
#define ChangeCol (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ChangeCol__)
#define ChangeTextPos (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ChangeTextPos__)
#define ChangeGraphPos (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ChangeGraphPos__)
#define Change (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Change__)
#define InfoForDark (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->InfoForDark__)
#define GotoPageNr (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->GotoPageNr__)
#define GotoVarNr (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->GotoVarNr__)
#define NrPages (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->NrPages__)
#define ActLanguage (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ActLanguage__)
#define StopScreenUpdate (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->StopScreenUpdate__)
#define StopWindowUpdate (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->StopWindowUpdate__)
#define ScreenUpdateList (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ScreenUpdateList__)
#define FastRegDone (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FastRegDone__)
#define DiagInitFlag (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DiagInitFlag__)
#define InjHeatChange (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->InjHeatChange__)
#define MinKeyPos (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MinKeyPos__)
#define ScreenPrinted (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ScreenPrinted__)
#define Print_CycleCount (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Print_CycleCount__)
#define Print_TimeCount (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Print_TimeCount__)
#define Print_AutMashStopPrinted (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Print_AutMashStopPrinted__)
#define DiagModeActive (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DiagModeActive__)
#define DiagIscosNo (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DiagIscosNo__)
#define TlgAddrTab (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TlgAddrTab__)
#define Ticker (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Ticker__)
#define Glob_TabVal (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Glob_TabVal__)
#define DataTransferActive (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DataTransferActive__)
/*              Kundenprom
 */
#define VersKprom (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->VersKprom__)
#define SpecKprom (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SpecKprom__)
#define TimeKprom (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TimeKprom__)
#define OptionTab (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->OptionTab__)
#define ToolParamTab (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ToolParamTab__)
#define AggParamTab (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->AggParamTab__)
#define SnParamTab1 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SnParamTab1__)
#define SnParamTab2 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SnParamTab2__)
#define SnParamTab3 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SnParamTab3__)
#define MaxInjUnits (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxInjUnits__)
#define MaxResUnits (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxResUnits__)
#define MaxInjCyc (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxInjCyc__)
#define MaxStat (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxStat__)
#define MaxToolHeatZones (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxToolHeatZones__)
#define MaxResHeatZones (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxResHeatZones__)
#define MaxTempTools (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxTempTools__)
#define MaxRegler (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxRegler__)
#define MaxTrk (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxTrk__)
#define MaxHeatRegs (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxHeatRegs__)
#define MaxInjHeatZones (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxInjHeatZones__)
#define MaxDMAAddr (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxDMAAddr__)
#define TlgDMAAddr (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TlgDMAAddr__)
#define OrderNr (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->OrderNr__)
#define MashineNr (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MashineNr__)
#define MashineType (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MashineType__)
#define ClosePower (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ClosePower__)
#define Language1 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Language1__)
#define Language2 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Language2__)
#define Language3 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Language3__)
#define IqtVersion (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->IqtVersion__)
#define Customer (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Customer__)
#define FreeText1 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FreeText1__)
#define FreeText2 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FreeText2__)
#define FreeText3 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FreeText3__)
#define FreeText4 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FreeText4__)
#define CLB_SollBufSize (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->CLB_SollBufSize__)
#define CLB_IstBufSize (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->CLB_IstBufSize__)
#define CLB_ErrBufSize (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->CLB_ErrBufSize__)
#define CLB_Password (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->CLB_Password__)
#define MaxIntfKonf (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxIntfKonf__)
#define IntfKonf (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->IntfKonf__)
#define MaxDevKonf (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->MaxDevKonf__)
#define DevKonf (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->DevKonf__)
#define FreeTabP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FreeTabP__)
#define InjSpeed_Max (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->InjSpeed_Max__)
#define InjSpeed_Conv (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->InjSpeed_Conv__)
#define InjHeatTabP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->InjHeatTabP__)
#define ToolHeatTabP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ToolHeatTabP__)
#define TempHeatTabP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TempHeatTabP__)
#define OilHeat (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->OilHeat__)
#define ResHeatTabP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ResHeatTabP__)
#define ReglerNameP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ReglerNameP__)
#define ReglerParamP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ReglerParamP__)
#define ScreenSaveTime (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ScreenSaveTime__)
/*      Versionen
 */
#define VersIqtkern (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->VersIqtkern__)
#define SpecIqtkern (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SpecIqtkern__)
#define TimeIqtkern (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TimeIqtkern__)
#define CoreVersNeededByDstruct (((SHARED_DATA_TYPE *)Shared_Data_Ptr())->CoreVersNeededByDstruct__)
#define VersDstruct (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->VersDstruct__)
#define SpecDstruct (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SpecDstruct__)
#define TimeDstruct (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->TimeDstruct__)
/* weitere globale Daten
 */
#define SnParamTab (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SnParamTab__)
#define OptModeTabP (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->OptModeTabP__)
#define ASCIIGraph (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ASCIIGraph__)
#define SPCPTab (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SPCPTab__)
#define BDEFirstStopError (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->BDEFirstStopError__)
#define BDELastStopError (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->BDELastStopError__)
#define FreeObjTab1 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FreeObjTab1__)
#define FreeObjTab2 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FreeObjTab2__)
#define FreeObjTab3 (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->FreeObjTab3__)
#define HeatErrorOK (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->HeatErrorOK__)
#define DiagFileHandle (((SHARED_DATA_TYPE *)Shared_Data_Ptr())->DiagFileHandle__)
#define EM17Handle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->EM17Handle__)     /* EM17*/
#define ExclEM17Sema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclEM17Sema__) /* EM17 */

/* Neu ab KPTool V.2.00: */
#define ToolParamTabAdd (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ToolParamTabAdd__)
#define AggParamTabAdd (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->AggParamTabAdd__)
#define SnParamTab1Add (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SnParamTab1Add__)
#define SnParamTab2Add (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SnParamTab2Add__)
#define SnParamTab3Add (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SnParamTab3Add__)
#define PlausParamTab  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->PlausParamTab__)
#define Lan1SpsText1   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText1__)
#define Lan1SpsText2   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText2__)
#define Lan1SpsText3   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText3__)
#define Lan1SpsText4   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText4__)
#define Lan1SpsText5   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText5__)
#define Lan1SpsText6   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText6__)
#define Lan1SpsText7   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText7__)
#define Lan1SpsText8   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText8__)
#define Lan1SpsText9   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText9__)
#define Lan1SpsText10  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText10__)
#define Lan1SpsText11  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText11__)
#define Lan1SpsText12  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText12__)
#define Lan1SpsText13  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText13__)
#define Lan1SpsText14  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText14__)
#define Lan1SpsText15  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan1SpsText15__)
#define Lan2SpsText1   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText1__)
#define Lan2SpsText2   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText2__)
#define Lan2SpsText3   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText3__)
#define Lan2SpsText4   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText4__)
#define Lan2SpsText5   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText5__)
#define Lan2SpsText6   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText6__)
#define Lan2SpsText7   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText7__)
#define Lan2SpsText8   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText8__)
#define Lan2SpsText9   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText9__)
#define Lan2SpsText10  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText10__)
#define Lan2SpsText11  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText11__)
#define Lan2SpsText12  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText12__)
#define Lan2SpsText13  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText13__)
#define Lan2SpsText14  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText14__)
#define Lan2SpsText15  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan2SpsText15__)
#define Lan3SpsText1   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText1__)
#define Lan3SpsText2   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText2__)
#define Lan3SpsText3   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText3__)
#define Lan3SpsText4   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText4__)
#define Lan3SpsText5   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText5__)
#define Lan3SpsText6   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText6__)
#define Lan3SpsText7   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText7__)
#define Lan3SpsText8   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText8__)
#define Lan3SpsText9   (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText9__)
#define Lan3SpsText10  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText10__)
#define Lan3SpsText11  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText11__)
#define Lan3SpsText12  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText12__)
#define Lan3SpsText13  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText13__)
#define Lan3SpsText14  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText14__)
#define Lan3SpsText15  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->Lan3SpsText15__)
#define SnParamTabAdd  (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SnParamTabAdd__)
#define SPSType (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->SPSType__)
#define ExclDRVERRSema (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ExclDRVERRSema__)
#define ErrLineHandle (((SHARED_DATA_TYPE*)Shared_Data_Ptr())->ErrLineHandle__)

#else

GLOBAL void * SharedDataPtr(void);
GLOBAL int InitSharedData(void);
extern SHARED_DATA_TYPE SharedData;

#define ExclSPCSema SharedData.ExclSPCSema__
#define ExclActElementSema SharedData.ExclActElementSema__
#define ExclBDESema SharedData.ExclBDESema__
#define ExclCursorSema SharedData.ExclCursorSema__
#define ExclDarkSema SharedData.ExclDarkSema__
#define ExclPrintSema SharedData.ExclPrintSema__
#define ExclCyclePrintSema SharedData.ExclCyclePrintSema__
#define ExclIscosSema SharedData.ExclIscosSema__
#define ExclHostBufferSema SharedData.ExclHostBufferSema__
#define ExclHostErrBufSema SharedData.ExclHostErrBufSema__
#define ExclSollInpSema SharedData.ExclSollInpSema__
#define ExclBlueWhiteSema SharedData.ExclBlueWhiteSema__
#define ExclPortSema SharedData.ExclPortSema__
#define ExclCLBSema SharedData.ExclCLBSema__
#define ExclScreenSema SharedData.ExclScreenSema__
#define ExclWindowSema SharedData.ExclWindowSema__
#define BuildScreenPort SharedData.BuildScreenPort__
#define ScreenUpdatePort SharedData.ScreenUpdatePort__
#define PrintPagePort SharedData.PrintPagePort__
#define BDEPort SharedData.BDEPort__
#define InjRegPort SharedData.InjRegPort__
#define TlgRegPort SharedData.TlgRegPort__
#define DiagModePort SharedData.DiagModePort__
#define PGPort SharedData.PGPort__
#define KbdPort_ptr SharedData.KbdPort_ptr__
#define TextHandle SharedData.TextHandle__
#define HelpHandle SharedData.HelpHandle__
#define StatLineHandle SharedData.StatLineHandle__
#define SoftkeyParent SharedData.SoftkeyParent__
#define SoftkeyHandle SharedData.SoftkeyHandle__
#define VarHandle SharedData.VarHandle__
#define HostCrtHandle SharedData.HostCrtHandle__
#define DiagOutHandle SharedData.DiagOutHandle__
#define DiagStatHandle SharedData.DiagStatHandle__
#define ControllerHandle SharedData.ControllerHandle__
#define MeasureHandle SharedData.MeasureHandle__
#define KbdHandle SharedData.KbdHandle__
#define RtcHandle SharedData.RtcHandle__
#define ComHandle SharedData.ComHandle__
#define DiagPrintHandle SharedData.DiagPrintHandle__
#define RobotHandle SharedData.RobotHandle__
#define HostHandle SharedData.HostHandle__
#define PortHandle SharedData.PortHandle__
#define CardHandle SharedData.CardHandle__
#define BgTaskFlag SharedData.BgTaskFlag__
#define BackgroundDataset SharedData.BackgroundDataset__
#define OptFunction SharedData.OptFunction__
#define CompareFgBg SharedData.CompareFgBg__
#define SetupValueChanged SharedData.SetupValueChanged__
#define SmallScreenActive SharedData.SmallScreenActive__
#define HelpActive SharedData.HelpActive__
#define ProcGraphActiveTab SharedData.ProcGraphActiveTab__
#define HostAccess SharedData.HostAccess__
#define LineFlag SharedData.LineFlag__
#define LineDirect SharedData.LineDirect__
#define HeaderP SharedData.HeaderP__
#define PrnProgListTabP SharedData.PrnProgListTabP__
#define ActPageIndex SharedData.ActPageIndex__
#define ActPageNr SharedData.ActPageNr__
#define ActObjectIndex SharedData.ActObjectIndex__
#define ActObject SharedData.ActObject__
#define ActElement SharedData.ActElement__
#define ActSollExist SharedData.ActSollExist__
#define ActBitArrayInd SharedData.ActBitArrayInd__
#define SmallPageIndex SharedData.SmallPageIndex__
#define KlickMode SharedData.KlickMode__
#define ShowKlickObject SharedData.ShowKlickObject__
#define VarHandleEl SharedData.VarHandleEl__
#define SollInpEP SharedData.SollInpEP__
#define ActInpEP SharedData.ActInpEP__
#define LParamUser1 SharedData.LParamUser1__
#define TParamUser1 SharedData.TParamUser1__
#define ChangeCol SharedData.ChangeCol__
#define ChangeTextPos SharedData.ChangeTextPos__
#define ChangeGraphPos SharedData.ChangeGraphPos__
#define Change SharedData.Change__
#define InfoForDark SharedData.InfoForDark__
#define GotoPageNr SharedData.GotoPageNr__
#define GotoVarNr SharedData.GotoVarNr__
#define NrPages SharedData.NrPages__
#define ActLanguage SharedData.ActLanguage__
#define StopScreenUpdate SharedData.StopScreenUpdate__
#define StopWindowUpdate SharedData.StopWindowUpdate__
#define ScreenUpdateList SharedData.ScreenUpdateList__
#define FastRegDone SharedData.FastRegDone__
#define DiagInitFlag SharedData.DiagInitFlag__
#define InjHeatChange SharedData.InjHeatChange__
#define MinKeyPos SharedData.MinKeyPos__
#define ScreenPrinted SharedData.ScreenPrinted__
#define Print_CycleCount SharedData.Print_CycleCount__
#define Print_TimeCount SharedData.Print_TimeCount__
#define Print_AutMashStopPrinted SharedData.Print_AutMashStopPrinted__
#define DiagModeActive SharedData.DiagModeActive__
#define DiagIscosNo SharedData.DiagIscosNo__
#define TlgAddrTab SharedData.TlgAddrTab__
#define Ticker SharedData.Ticker__
#define Glob_TabVal SharedData.Glob_TabVal__
#define DataTransferActive SharedData.DataTransferActive__
/*              Kundenprom
 */
#define VersKprom SharedData.VersKprom__
#define SpecKprom SharedData.SpecKprom__
#define TimeKprom SharedData.TimeKprom__
#define OptionTab SharedData.OptionTab__
#define ToolParamTab SharedData.ToolParamTab__
#define AggParamTab SharedData.AggParamTab__
#define SnParamTab1 SharedData.SnParamTab1__
#define SnParamTab2 SharedData.SnParamTab2__
#define SnParamTab3 SharedData.SnParamTab3__
#define MaxInjUnits SharedData.MaxInjUnits__
#define MaxResUnits SharedData.MaxResUnits__
#define MaxInjCyc SharedData.MaxInjCyc__
#define MaxStat SharedData.MaxStat__
#define MaxToolHeatZones SharedData.MaxToolHeatZones__
#define MaxResHeatZones SharedData.MaxResHeatZones__
#define MaxTempTools SharedData.MaxTempTools__
#define MaxRegler SharedData.MaxRegler__
#define MaxTrk SharedData.MaxTrk__
#define MaxHeatRegs SharedData.MaxHeatRegs__
#define MaxInjHeatZones SharedData.MaxInjHeatZones__
#define MaxDMAAddr SharedData.MaxDMAAddr__
#define TlgDMAAddr SharedData.TlgDMAAddr__
#define OrderNr SharedData.OrderNr__
#define MashineNr SharedData.MashineNr__
#define MashineType SharedData.MashineType__
#define ClosePower SharedData.ClosePower__
#define Language1 SharedData.Language1__
#define Language2 SharedData.Language2__
#define Language3 SharedData.Language3__
#define IqtVersion SharedData.IqtVersion__
#define Customer SharedData.Customer__
#define FreeText1 SharedData.FreeText1__
#define FreeText2 SharedData.FreeText2__
#define FreeText3 SharedData.FreeText3__
#define FreeText4 SharedData.FreeText4__
#define CLB_SollBufSize SharedData.CLB_SollBufSize__
#define CLB_IstBufSize SharedData.CLB_IstBufSize__
#define CLB_ErrBufSize SharedData.CLB_ErrBufSize__
#define CLB_Password SharedData.CLB_Password__
#define MaxIntfKonf SharedData.MaxIntfKonf__
#define IntfKonf SharedData.IntfKonf__
#define MaxDevKonf SharedData.MaxDevKonf__
#define DevKonf SharedData.DevKonf__
#define FreeTabP SharedData.FreeTabP__
#define InjSpeed_Max SharedData.InjSpeed_Max__
#define InjSpeed_Conv SharedData.InjSpeed_Conv__
#define InjHeatTabP SharedData.InjHeatTabP__
#define ToolHeatTabP SharedData.ToolHeatTabP__
#define TempHeatTabP SharedData.TempHeatTabP__
#define OilHeat SharedData.OilHeat__
#define ResHeatTabP SharedData.ResHeatTabP__
#define ReglerNameP SharedData.ReglerNameP__
#define ReglerParamP SharedData.ReglerParamP__
#define ScreenSaveTime SharedData.ScreenSaveTime__
/*      Versionen
 */
#define VersIqtkern SharedData.VersIqtkern__
#define SpecIqtkern SharedData.SpecIqtkern__
#define TimeIqtkern SharedData.TimeIqtkern__
#define CoreVersNeededByDstruct SharedData.CoreVersNeededByDstruct__
#define VersDstruct SharedData.VersDstruct__
#define SpecDstruct SharedData.SpecDstruct__
#define TimeDstruct SharedData.TimeDstruct__
/* weitere globale Daten
 */
#define SnParamTab SharedData.SnParamTab__
#define OptModeTabP SharedData.OptModeTabP__
#define ASCIIGraph SharedData.ASCIIGraph__
#define SPCPTab SharedData.SPCPTab__
#define BDEFirstStopError SharedData.BDEFirstStopError__
#define BDELastStopError SharedData.BDELastStopError__
#define FreeObjTab1 SharedData.FreeObjTab1__
#define FreeObjTab2 SharedData.FreeObjTab2__
#define FreeObjTab3 SharedData.FreeObjTab3__
#define HeatErrorOK SharedData.HeatErrorOK__

#define DiagFileHandle SharedData.DiagFileHandle__
#define EM17Handle SharedData.EM17Handle__      /* EM17 */
#define ExclEM17Sema SharedData.ExclEM17Sema__  /* EM17 */

/* Neu ab KPTool V.2.00: */
#define ToolParamTabAdd SharedData.ToolParamTabAdd__
#define AggParamTabAdd SharedData.AggParamTabAdd__
#define SnParamTab1Add SharedData.SnParamTab1Add__
#define SnParamTab2Add SharedData.SnParamTab2Add__
#define SnParamTab3Add SharedData.SnParamTab3Add__
#define PlausParamTab SharedData.PlausParamTab__
#define Lan1SpsText1 SharedData.Lan1SpsText1__
#define Lan1SpsText2 SharedData.Lan1SpsText2__
#define Lan1SpsText3 SharedData.Lan1SpsText3__
#define Lan1SpsText4 SharedData.Lan1SpsText4__
#define Lan1SpsText5 SharedData.Lan1SpsText5__
#define Lan1SpsText6 SharedData.Lan1SpsText6__
#define Lan1SpsText7 SharedData.Lan1SpsText7__
#define Lan1SpsText8 SharedData.Lan1SpsText8__
#define Lan1SpsText9 SharedData.Lan1SpsText9__
#define Lan1SpsText10 SharedData.Lan1SpsText10__
#define Lan1SpsText11 SharedData.Lan1SpsText11__
#define Lan1SpsText12 SharedData.Lan1SpsText12__
#define Lan1SpsText13 SharedData.Lan1SpsText13__
#define Lan1SpsText14 SharedData.Lan1SpsText14__
#define Lan1SpsText15 SharedData.Lan1SpsText15__
#define Lan2SpsText1 SharedData.Lan2SpsText1__
#define Lan2SpsText2 SharedData.Lan2SpsText2__
#define Lan2SpsText3 SharedData.Lan2SpsText3__
#define Lan2SpsText4 SharedData.Lan2SpsText4__
#define Lan2SpsText5 SharedData.Lan2SpsText5__
#define Lan2SpsText6 SharedData.Lan2SpsText6__
#define Lan2SpsText7 SharedData.Lan2SpsText7__
#define Lan2SpsText8 SharedData.Lan2SpsText8__
#define Lan2SpsText9 SharedData.Lan2SpsText9__
#define Lan2SpsText10 SharedData.Lan1SpsText10__
#define Lan2SpsText11 SharedData.Lan1SpsText11__
#define Lan2SpsText12 SharedData.Lan1SpsText12__
#define Lan2SpsText13 SharedData.Lan1SpsText13__
#define Lan2SpsText14 SharedData.Lan1SpsText14__
#define Lan2SpsText15 SharedData.Lan1SpsText15__
#define Lan3SpsText1 SharedData.Lan3SpsText1__
#define Lan3SpsText2 SharedData.Lan3SpsText2__
#define Lan3SpsText3 SharedData.Lan3SpsText3__
#define Lan3SpsText4 SharedData.Lan3SpsText4__
#define Lan3SpsText5 SharedData.Lan3SpsText5__
#define Lan3SpsText6 SharedData.Lan3SpsText6__
#define Lan3SpsText7 SharedData.Lan3SpsText7__
#define Lan3SpsText8 SharedData.Lan3SpsText8__
#define Lan3SpsText9 SharedData.Lan3SpsText9__
#define Lan3SpsText10 SharedData.Lan3SpsText10__
#define Lan3SpsText11 SharedData.Lan3SpsText11__
#define Lan3SpsText12 SharedData.Lan3SpsText12__
#define Lan3SpsText13 SharedData.Lan3SpsText13__
#define Lan3SpsText14 SharedData.Lan3SpsText14__
#define Lan3SpsText15 SharedData.Lan3SpsText15__
#define SnParamTabAdd SharedData.SnParamTabAdd__
#define SPSType SharedData.SPSType__
#define ExclDRVERRSema SharedData.ExclDRVERRSema__
#define ErrLineHandle SharedData.ErrLineHandle__

#endif

#endif         /* ifndef _global */

