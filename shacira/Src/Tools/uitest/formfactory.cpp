
#include "formfactory.h"

#include "ui_Mosaicframe.h"
#define ALL_PAGES
#ifndef ALL_PAGES
#define TMP
#ifdef ALR
#include "ui_Alr_Changelog.h"
#include "ui_Alr_Monitoring.h"
#include "ui_Alr_Overview.h"
#include "ui_Alr_Statistic.h"
#endif
#ifdef AUT
#include "ui_Aut_Configaoscrollview.h"
#include "ui_Aut_Configdiscrollview.h"
#include "ui_Aut_Configdoscrollview.h"
#include "ui_Aut_Configio.h"
#include "ui_Aut_Customized.h"
#include "ui_Aut_General.h"
#include "ui_Aut_Handling.h"
#include "ui_Aut_Qualcontr_Selswitch.h"
#include "ui_Aut_Remoterobot.h"
#endif
#ifdef CLP
#include "ui_Clp_Airejector.h"
#include "ui_Clp_Compression.h"
#include "ui_Clp_Ejector.h"
#include "ui_Clp_Ejectorwizard.h"
#include "ui_Clp_Minmoldheightwizard.h"
#include "ui_Clp_Openclose.h"
#include "ui_Clp_Productejector.h"
#include "ui_Clp_Setup.h"
#endif
#ifdef COR
#include "ui_Cor_Customized.h"
#include "ui_Cor_Overview.h"
#include "ui_Cor_Prgwizard.h"
#include "ui_Cor_Program.h"
#include "ui_Cor_Status.h"
#include "ui_Cor_Test.h"
#include "ui_Cor_Test3.h"
#include "ui_Cor_Turntable.h"
#include "ui_Cor_Turntableadjust.h"
#include "ui_Cor_Usermanualdialog.h"
#endif
#ifdef DIAG
#include "ui_Diag_Host.h"
#include "ui_Diag_Io.h"
#include "ui_Diag_Lockingforcesensorwizard.h"
#include "ui_Diag_Statestep.h"
#include "ui_Diag_Valveadjustment.h"
#include "ui_Diag_Version.h"
#include "ui_Hlp_Viewer.h"
#endif
#ifdef INJ
#include "ui_Inj_Airpress.h"
#include "ui_Inj_Cascade.h"
#include "ui_Inj_Cascadescrollview.h"
#include "ui_Inj_Extruder.h"
#include "ui_Inj_Graphic.h"
#include "ui_Inj_Pressure.h"
#include "ui_Inj_Prodstart.h"
#include "ui_Inj_Ramp.h"
#include "ui_Inj_Sequencerdialog.h"
#include "ui_Inj_Set.h"
#include "ui_Inj_Setunitmodewizard.h"
#include "ui_Inj_Sled.h"
#include "ui_Inj_Sledwithstroketrans.h"
#include "ui_Inj_Sledwithstroketranswizard.h"
#include "ui_Inj_Velocity.h"
#include "ui_Inj_Velocitymoldcavitywizard.h"
#endif
#ifdef MDAT
#include "ui_Mdat_Changefgbgdialog.h"
#include "ui_Mdat_Checklimit_Dialog.h"
#include "ui_Mdat_Complistviewdialog.h"
#include "ui_Mdat_Copyfgtobgdialog.h"
#include "ui_Mdat_Fgbgdata.h"
#include "ui_Mdat_Notepad.h"
#include "ui_Mdat_Readdatadialog.h"
#include "ui_Mdat_Setinfo1.h"
#include "ui_Mdat_Setinfo2.h"
#include "ui_Mdat_Storage.h"
#endif
#ifdef OVW
#include "ui_Ovw_Configbarrelwizard.h"
#include "ui_Ovw_General.h"
#include "ui_Ovw_Notepad.h"
#include "ui_Ovw_Password.h"
#include "ui_Ovw_Posting.h"
#include "ui_Ovw_Postit_Tearoff.h"
#include "ui_Ovw_Service.h"
#include "ui_Ovw_Setpoints.h"
#include "ui_Ovw_weektimer.h"
#endif
#ifdef PROC
#include "ui_Proc_Cycleanalysis.h"
#include "ui_Proc_Monitor.h"
#include "ui_Proc_Power.h"
#include "ui_Proc_Powernotedialog.h"
#include "ui_Proc_Proddata.h"
#include "ui_Proc_Production.h"
#include "ui_Proc_Trenddata.h"
#include "ui_Proc_Trendgraph.h"
#endif
#ifdef SYS
#include "ui_Sys_Cardinfodialog.h"
#include "ui_Sys_Cardmasterdialog.h"
#include "ui_Sys_Cardwizard.h"
#include "ui_Sys_Datetime.h"
#include "ui_Sys_Dirdialog.h"
#include "ui_Sys_Directory.h"
#include "ui_Sys_Filehandlingdialog.h"
#include "ui_Sys_Filehandlingfaultdialog.h"
#include "ui_Sys_Filehandlingwizard.h"
#include "ui_Sys_Filesavedialog.h"
#include "ui_Sys_Filesavereadwizard.h"
#include "ui_Sys_Infomation.h"
#include "ui_Sys_Language.h"
#include "ui_Sys_Network.h"
#include "ui_Sys_Reports.h"
#include "ui_Sys_Reportsinfodialog.h"
#include "ui_Sys_Security.h"
#include "ui_Sys_Startupdialog.h"
#endif
#ifdef TMP
#include "ui_Tmp_Autotune.h"
#include "ui_Tmp_Barrel.h"
#include "ui_Tmp_Ctlparamdialog.h"
#include "ui_Tmp_Hotrunner.h"
#include "ui_Tmp_Interfaceconfig.h"
#include "ui_Tmp_Interfacewizard.h"
#include "ui_Tmp_Moldcooling.h"
#include "ui_Tmp_Options.h"
#include "ui_Tmp_Overview.h"
#include "ui_Tmp_Temperatures.h" 
#endif
#else
#include "ui_Alr_Changelog.h"
#include "ui_Alr_Monitoring.h"
#include "ui_Alr_Overview.h"
#include "ui_Alr_Statistic.h"
#include "ui_Aut_Configaoscrollview.h"
#include "ui_Aut_Configdiscrollview.h"
#include "ui_Aut_Configdoscrollview.h"
#include "ui_Aut_Configio.h"
#include "ui_Aut_Customized.h"
#include "ui_Aut_General.h"
#include "ui_Aut_Handling.h"
#include "ui_Aut_Qualcontr_Selswitch.h"
#include "ui_Aut_Remoterobot.h"
#include "ui_Clp_Airejector.h"
#include "ui_Clp_Compression.h"
#include "ui_Clp_Ejector.h"
#include "ui_Clp_Ejectorwizard.h"
#include "ui_Clp_Minmoldheightwizard.h"
#include "ui_Clp_Openclose.h"
#include "ui_Clp_Productejector.h"
#include "ui_Clp_Setup.h"
#include "ui_Cor_Customized.h"
#include "ui_Cor_Overview.h"
#include "ui_Cor_Prgwizard.h"
#include "ui_Cor_Program.h"
#include "ui_Cor_Status.h"
#include "ui_Cor_Test.h"
#include "ui_Cor_Test3.h"
#include "ui_Cor_Turntable.h"
#include "ui_Cor_Turntableadjust.h"
#include "ui_Cor_Usermanualdialog.h"
#include "ui_Diag_Host.h"
#include "ui_Diag_Io.h"
#include "ui_Diag_Lockingforcesensorwizard.h"
#include "ui_Diag_Statestep.h"
#include "ui_Diag_Valveadjustment.h"
#include "ui_Diag_Version.h"
#include "ui_Hlp_Viewer.h"
#include "ui_Inj_Airpress.h"
#include "ui_Inj_Cascade.h"
#include "ui_Inj_Cascadescrollview.h"
#include "ui_Inj_Extruder.h"
#include "ui_Inj_Graphic.h"
#include "ui_Inj_Pressure.h"
#include "ui_Inj_Prodstart.h"
#include "ui_Inj_Ramp.h"
#include "ui_Inj_Sequencerdialog.h"
#include "ui_Inj_Set.h"
#include "ui_Inj_Setunitmodewizard.h"
#include "ui_Inj_Sled.h"
#include "ui_Inj_Sledwithstroketrans.h"
#include "ui_Inj_Sledwithstroketranswizard.h"
#include "ui_Inj_Velocity.h"
#include "ui_Inj_Velocitymoldcavitywizard.h"
#include "ui_KeyboardAlpha.h"
#include "ui_KeyboardLayoutGerman.h"
#include "ui_KeyboardLayoutStandard.h"
#include "ui_KeypadNumeric.h"
#include "ui_Mdat_Changefgbgdialog.h"
#include "ui_Mdat_Checklimit_Dialog.h"
#include "ui_Mdat_Complistviewdialog.h"
#include "ui_Mdat_Copyfgtobgdialog.h"
#include "ui_Mdat_Fgbgdata.h"
#include "ui_Mdat_Notepad.h"
#include "ui_Mdat_Readdatadialog.h"
#include "ui_Mdat_Setinfo1.h"
#include "ui_Mdat_Setinfo2.h"
#include "ui_Mdat_Storage.h"
#include "ui_Mosaicframe.h"
#include "ui_Mosaicstartupform.h"
#include "ui_Ovw_Configbarrelwizard.h"
#include "ui_Ovw_General.h"
#include "ui_Ovw_Notepad.h"
#include "ui_Ovw_Password.h"
#include "ui_Ovw_Posting.h"
#include "ui_Ovw_Postit_Tearoff.h"
#include "ui_Ovw_Service.h"
#include "ui_Ovw_Setpoints.h"
#include "ui_Ovw_weektimer.h"
#include "ui_Proc_Cycleanalysis.h"
#include "ui_Proc_Monitor.h"
#include "ui_Proc_Power.h"
#include "ui_Proc_Powernotedialog.h"
#include "ui_Proc_Proddata.h"
#include "ui_Proc_Production.h"
#include "ui_Proc_Trenddata.h"
#include "ui_Proc_Trendgraph.h"
#include "ui_Sys_Cardinfodialog.h"
#include "ui_Sys_Cardmasterdialog.h"
#include "ui_Sys_Cardwizard.h"
#include "ui_Sys_Datetime.h"
#include "ui_Sys_Dirdialog.h"
#include "ui_Sys_Directory.h"
#include "ui_Sys_Filehandlingdialog.h"
#include "ui_Sys_Filehandlingfaultdialog.h"
#include "ui_Sys_Filehandlingwizard.h"
#include "ui_Sys_Filesavedialog.h"
#include "ui_Sys_Filesavereadwizard.h"
#include "ui_Sys_Infomation.h"
#include "ui_Sys_Language.h"
#include "ui_Sys_Network.h"
#include "ui_Sys_Reports.h"
#include "ui_Sys_Reportsinfodialog.h"
#include "ui_Sys_Security.h"
#include "ui_Sys_Startupdialog.h"
#include "ui_Tmp_Autotune.h"
#include "ui_Tmp_Barrel.h"
#include "ui_Tmp_Ctlparamdialog.h"
#include "ui_Tmp_Hotrunner.h"
#include "ui_Tmp_Interfaceconfig.h"
#include "ui_Tmp_Interfacewizard.h"
#include "ui_Tmp_Moldcooling.h"
#include "ui_Tmp_Options.h"
#include "ui_Tmp_Overview.h"
#include "ui_Tmp_Temperatures.h" 
#endif

FormFactory::FormFactory()
{
}

FormFactory::~FormFactory()
{
}

#define ADD_FRAME(type) \
   { \
      CAppFrame * frame = new CAppFrame; \
      type ui; \
      ui.setupUi(frame); \
      _frameMap[#type] = frame; \
   }

#define ADD_PAGE(type) \
   { \
      CPage * page = new CPage; \
      type ui; \
      ui.setupUi(page); \
      _pageMap[#type] = page; \
   }

#define ADD_ACTION_DIALOG(type) \
   { \
      CActionDialog * dialog = new CActionDialog(NULL); \
      type ui; \
      ui.setupUi(dialog); \
      _actionDialogMap[#type] = dialog; \
   }

#define ADD_DIALOG(type) \
   { \
      QDialog * dialog = new QDialog; \
      type ui; \
      ui.setupUi(dialog); \
      _dialogMap[#type] = dialog; \
   }

#define ADD_WIZARD(type) \
   { \
      QWizard * wizard = new QWizard; \
      type ui; \
      ui.setupUi(wizard); \
      _wizardMap[#type] = wizard; \
   }


void FormFactory::create()
{
   ADD_FRAME(Ui_MosaicFrame)
#ifndef ALL_PAGES
#ifdef ALR
   ADD_PAGE(Ui_Alr_ChangeLog)
   ADD_PAGE(Ui_Alr_Monitoring)
   ADD_PAGE(Ui_Alr_Overview)
   ADD_PAGE(Ui_Alr_Statistic)
#endif
#ifdef AUT
   ADD_PAGE(Ui_Aut_ConfigAOScrollView)
   ADD_PAGE(Ui_Aut_ConfigDIScrollView)
   ADD_PAGE(Ui_Aut_ConfigDOScrollView)
   ADD_PAGE(Ui_Aut_ConfigIO)
   ADD_PAGE(Ui_Aut_Customized)
   ADD_PAGE(Ui_Aut_General)
   ADD_PAGE(Ui_Aut_Handling)
   ADD_PAGE(Ui_Aut_QualContr_SelSwitch)
   ADD_PAGE(Ui_Aut_RemoteRobot)
#endif
#ifdef CLP
   ADD_PAGE(Ui_Clp_AirEjector)
   ADD_PAGE(Ui_Clp_Compression)
   ADD_PAGE(Ui_Clp_Ejector)
   ADD_WIZARD(Ui_Clp_EjectorWizard)
   ADD_WIZARD(Ui_Clp_MinMoldHeightWizard)
   ADD_PAGE(Ui_Clp_OpenClose)
   ADD_PAGE(Ui_Clp_ProductEjector)
   ADD_PAGE(Ui_Clp_Setup)
#endif
#ifdef COR
   ADD_PAGE(Ui_Cor_Customized)
   ADD_PAGE(Ui_Cor_Overview)
   ADD_WIZARD(Ui_Cor_PrgWizard)
   ADD_PAGE(Ui_Cor_Program)
   ADD_PAGE(Ui_Cor_Status)
   ADD_PAGE(Ui_Cor_Test)
   ADD_PAGE(Ui_Cor_Test3)
   ADD_PAGE(Ui_Cor_Turntable)
   ADD_PAGE(Ui_Cor_TurntableAdjust)
   ADD_DIALOG(Ui_Cor_UserManualDialog)
#endif
#ifdef DIAG
   ADD_PAGE(Ui_Diag_Host)
   ADD_PAGE(Ui_Diag_IO)
   ADD_WIZARD(Ui_Diag_LockingForceSensorWizard)
   ADD_PAGE(Ui_Diag_StateStep)
   ADD_PAGE(Ui_Diag_ValveAdjustment)
   ADD_PAGE(Ui_Diag_Version)
   ADD_DIALOG(Ui_HlpViewer)
#endif
#ifdef INJ
   ADD_PAGE(Ui_Inj_Airpress)
   ADD_PAGE(Ui_Inj_Cascade)
   ADD_PAGE(Ui_Inj_CascadeScrollView)
   ADD_PAGE(Ui_Inj_Extruder)
   ADD_PAGE(Ui_Inj_Graphic)
   ADD_PAGE(Ui_Inj_Pressure)
   ADD_PAGE(Ui_Inj_ProdStart)
   ADD_PAGE(Ui_Inj_Ramp)
   ADD_DIALOG(Ui_Inj_SequencerDialog)
   ADD_PAGE(Ui_Inj_Set)
   ADD_WIZARD(Ui_Inj_SetUnitModeWizard)
   ADD_PAGE(Ui_Inj_Sled)
   ADD_PAGE(Ui_Inj_SledWithStrokeTrans)
   ADD_WIZARD(Ui_Inj_SledWithStrokeTransWizard)
   ADD_PAGE(Ui_Inj_Velocity)
   ADD_WIZARD(Ui_Inj_VelocityMoldCavityWizard)
#endif
#ifdef MDAT
   ADD_ACTION_DIALOG(Ui_MDat_ChangeFgBgDialog)
   ADD_DIALOG(Ui_MDat_CheckLimit_Dialog)
   ADD_DIALOG(Ui_MDat_CompListViewDialog)
   ADD_ACTION_DIALOG(Ui_MDat_CopyFgToBgDialog)
   ADD_PAGE(Ui_MDat_FGBGData)
   ADD_PAGE(Ui_MDat_Notepad)
   ADD_ACTION_DIALOG(Ui_MDat_ReadDataDialog)
   ADD_PAGE(Ui_MDat_SetInfo1)
   ADD_PAGE(Ui_MDat_SetInfo2)
   ADD_PAGE(Ui_MDat_Storage)
#endif
#ifdef OVW
   ADD_WIZARD(Ui_Ovw_ConfigBarrelWizard)
   ADD_PAGE(Ui_Ovw_General)
   ADD_PAGE(Ui_Ovw_Notepad)
   ADD_PAGE(Ui_Ovw_Password)
   ADD_PAGE(Ui_Ovw_Posting)
   ADD_DIALOG(Ui_OVW_PostitTearOffDialog)
   ADD_PAGE(Ui_Ovw_Service)
   ADD_PAGE(Ui_Ovw_Setpoints)
   ADD_PAGE(Ui_Ovw_WeekTimer)
#endif
#ifdef PROC
   ADD_PAGE(Ui_Proc_CycleAnalysis)
   ADD_PAGE(Ui_Proc_Monitor)
   ADD_PAGE(Ui_Proc_Power)
   ADD_DIALOG(Ui_Proc_PowerNoteDialog)
   ADD_PAGE(Ui_Proc_ProdData)
   ADD_PAGE(Ui_Proc_Production)
   ADD_PAGE(Ui_Proc_TrendData)
   ADD_PAGE(Ui_Proc_TrendGraph)
#endif
#ifdef SYS
   ADD_DIALOG(Ui_Sys_CardInfoDialog)
   ADD_DIALOG(Ui_Sys_CardMasterDialog)
   ADD_WIZARD(Ui_Sys_CardWizard)
   ADD_PAGE(Ui_Sys_DateTime)
   ADD_DIALOG(Ui_Sys_DirDialog)
   ADD_PAGE(Ui_Sys_Directory)
   ADD_ACTION_DIALOG(Ui_Sys_FileHandlingDialog)
   ADD_DIALOG(Ui_Sys_FileHandlingFaultDialog)
   ADD_WIZARD(Ui_Sys_FileHandlingWizard)
   ADD_DIALOG(Ui_Sys_FileSaveDialog)
   ADD_WIZARD(Ui_Sys_FileSaveReadWizard)
   ADD_PAGE(Ui_Sys_Infomation)
   ADD_PAGE(Ui_Sys_Language)
   ADD_PAGE(Ui_Sys_Network)
   ADD_PAGE(Ui_Sys_Reports)
   ADD_DIALOG(Ui_Sys_ReportsInfoDialog)
   ADD_PAGE(Ui_Sys_Security)
   ADD_DIALOG(Ui_Sys_StartUpDialog)
#endif
#ifdef TMP
   ADD_PAGE(Ui_Tmp_AutoTune)
   ADD_PAGE(Ui_Tmp_Barrel)
   ADD_DIALOG(Ui_Tmp_CtlParamDialog)
   ADD_PAGE(Ui_Tmp_Hotrunner)
   ADD_PAGE(Ui_Tmp_InterfaceConfig)
   ADD_WIZARD(Ui_Tmp_InterfaceWizard)
   ADD_PAGE(Ui_Tmp_MoldCooling)
   ADD_PAGE(Ui_Tmp_Options)
   ADD_PAGE(Ui_Tmp_Overview)
   ADD_PAGE(Ui_Tmp_Temperatures)
#endif
#else
   ADD_PAGE(Ui_Alr_ChangeLog)
   ADD_PAGE(Ui_Alr_Monitoring)
   ADD_PAGE(Ui_Alr_Overview)
   ADD_PAGE(Ui_Alr_Statistic)
   ADD_PAGE(Ui_Aut_ConfigAOScrollView)
   ADD_PAGE(Ui_Aut_ConfigDIScrollView)
   ADD_PAGE(Ui_Aut_ConfigDOScrollView)
   ADD_PAGE(Ui_Aut_ConfigIO)
   ADD_PAGE(Ui_Aut_Customized)
   ADD_PAGE(Ui_Aut_General)
   ADD_PAGE(Ui_Aut_Handling)
   ADD_PAGE(Ui_Aut_QualContr_SelSwitch)
   ADD_PAGE(Ui_Aut_RemoteRobot)
   ADD_PAGE(Ui_Clp_AirEjector)
   ADD_PAGE(Ui_Clp_Compression)
   ADD_PAGE(Ui_Clp_Ejector)
   ADD_WIZARD(Ui_Clp_EjectorWizard)
   ADD_WIZARD(Ui_Clp_MinMoldHeightWizard)
   ADD_PAGE(Ui_Clp_OpenClose)
   ADD_PAGE(Ui_Clp_ProductEjector)
   ADD_PAGE(Ui_Clp_Setup)
   ADD_PAGE(Ui_Cor_Customized)
   ADD_PAGE(Ui_Cor_Overview)
   ADD_WIZARD(Ui_Cor_PrgWizard)
   ADD_PAGE(Ui_Cor_Program)
   ADD_PAGE(Ui_Cor_Status)
   ADD_PAGE(Ui_Cor_Test)
   ADD_PAGE(Ui_Cor_Test3)
   ADD_PAGE(Ui_Cor_Turntable)
   ADD_PAGE(Ui_Cor_TurntableAdjust)
   ADD_DIALOG(Ui_Cor_UserManualDialog)
   ADD_PAGE(Ui_Diag_Host)
   ADD_PAGE(Ui_Diag_IO)
   ADD_WIZARD(Ui_Diag_LockingForceSensorWizard)
   ADD_PAGE(Ui_Diag_StateStep)
   ADD_PAGE(Ui_Diag_ValveAdjustment)
   ADD_PAGE(Ui_Diag_Version)
   ADD_DIALOG(Ui_HlpViewer)
   ADD_PAGE(Ui_Inj_Airpress)
   ADD_PAGE(Ui_Inj_Cascade)
   ADD_PAGE(Ui_Inj_CascadeScrollView)
   ADD_PAGE(Ui_Inj_Extruder)
   ADD_PAGE(Ui_Inj_Graphic)
   ADD_PAGE(Ui_Inj_Pressure)
   ADD_PAGE(Ui_Inj_ProdStart)
   ADD_PAGE(Ui_Inj_Ramp)
   ADD_DIALOG(Ui_Inj_SequencerDialog)
   ADD_PAGE(Ui_Inj_Set)
   ADD_WIZARD(Ui_Inj_SetUnitModeWizard)
   ADD_PAGE(Ui_Inj_Sled)
   ADD_PAGE(Ui_Inj_SledWithStrokeTrans)
   ADD_WIZARD(Ui_Inj_SledWithStrokeTransWizard)
   ADD_PAGE(Ui_Inj_Velocity)
   ADD_WIZARD(Ui_Inj_VelocityMoldCavityWizard)
   ADD_ACTION_DIALOG(Ui_MDat_ChangeFgBgDialog)
   ADD_DIALOG(Ui_MDat_CheckLimit_Dialog)
   ADD_DIALOG(Ui_MDat_CompListViewDialog)
   ADD_ACTION_DIALOG(Ui_MDat_CopyFgToBgDialog)
   ADD_PAGE(Ui_MDat_FGBGData)
   ADD_PAGE(Ui_MDat_Notepad)
   ADD_ACTION_DIALOG(Ui_MDat_ReadDataDialog)
   ADD_PAGE(Ui_MDat_SetInfo1)
   ADD_PAGE(Ui_MDat_SetInfo2)
   ADD_PAGE(Ui_MDat_Storage)
   ADD_FRAME(Ui_MosaicFrame)
   ADD_WIZARD(Ui_Ovw_ConfigBarrelWizard)
   ADD_PAGE(Ui_Ovw_General)
   ADD_PAGE(Ui_Ovw_Notepad)
   ADD_PAGE(Ui_Ovw_Password)
   ADD_PAGE(Ui_Ovw_Posting)
   ADD_DIALOG(Ui_OVW_PostitTearOffDialog)
   ADD_PAGE(Ui_Ovw_Service)
   ADD_PAGE(Ui_Ovw_Setpoints)
   ADD_PAGE(Ui_Ovw_WeekTimer)
   ADD_PAGE(Ui_Proc_CycleAnalysis)
   ADD_PAGE(Ui_Proc_Monitor)
   ADD_PAGE(Ui_Proc_Power)
   ADD_DIALOG(Ui_Proc_PowerNoteDialog)
   ADD_PAGE(Ui_Proc_ProdData)
   ADD_PAGE(Ui_Proc_Production)
   ADD_PAGE(Ui_Proc_TrendData)
   ADD_PAGE(Ui_Proc_TrendGraph)
   ADD_DIALOG(Ui_Sys_CardInfoDialog)
   ADD_DIALOG(Ui_Sys_CardMasterDialog)
   ADD_WIZARD(Ui_Sys_CardWizard)
   ADD_PAGE(Ui_Sys_DateTime)
   ADD_DIALOG(Ui_Sys_DirDialog)
   ADD_PAGE(Ui_Sys_Directory)
   ADD_ACTION_DIALOG(Ui_Sys_FileHandlingDialog)
   ADD_DIALOG(Ui_Sys_FileHandlingFaultDialog)
   ADD_WIZARD(Ui_Sys_FileHandlingWizard)
   ADD_DIALOG(Ui_Sys_FileSaveDialog)
   ADD_WIZARD(Ui_Sys_FileSaveReadWizard)
   ADD_PAGE(Ui_Sys_Infomation)
   ADD_PAGE(Ui_Sys_Language)
   ADD_PAGE(Ui_Sys_Network)
   ADD_PAGE(Ui_Sys_Reports)
   ADD_DIALOG(Ui_Sys_ReportsInfoDialog)
   ADD_PAGE(Ui_Sys_Security)
   ADD_DIALOG(Ui_Sys_StartUpDialog)
   ADD_PAGE(Ui_Tmp_AutoTune)
   ADD_PAGE(Ui_Tmp_Barrel)
   ADD_DIALOG(Ui_Tmp_CtlParamDialog)
   ADD_PAGE(Ui_Tmp_Hotrunner)
   ADD_PAGE(Ui_Tmp_InterfaceConfig)
   ADD_WIZARD(Ui_Tmp_InterfaceWizard)
   ADD_PAGE(Ui_Tmp_MoldCooling)
   ADD_PAGE(Ui_Tmp_Options)
   ADD_PAGE(Ui_Tmp_Overview)
   ADD_PAGE(Ui_Tmp_Temperatures)
#endif
   int dummy = 0;
}



