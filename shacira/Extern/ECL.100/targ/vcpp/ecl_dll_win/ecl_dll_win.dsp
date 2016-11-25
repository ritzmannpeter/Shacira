# Microsoft Developer Studio Project File - Name="ecl_dll_win" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ecl_dll_win - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ecl_dll_win.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_dll_win.mak" CFG="ecl_dll_win - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ecl_dll_win - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ecl_dll_win - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ecl_dll_win - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_WIN_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_WIN_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/eclwin.dll"
# Begin Special Build Tool
TargetPath=.\Release\eclwin.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ecl_dll_win - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_WIN_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_WIN_EXPORTS" /YX"mfc.hpp" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/eclwind.dll" /pdbtype:sept
# Begin Special Build Tool
TargetPath=.\Debug\eclwind.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ecl_dll_win - Win32 Release"
# Name "ecl_dll_win - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "_win"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\..\src\win\ew_application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_base.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_commands.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_dialogs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_dragdrop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_frames.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_logwins.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_menus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_threads.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_toolbars.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_views.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_windows.cpp
# End Source File
# End Group
# Begin Group "_ctls"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\..\src\win\ew_buttonctls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_cnrctls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_controls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_editctls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_gridctls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_lboxctls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_listctls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_nbctls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_statctls.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_treectls.cpp
# End Source File
# End Group
# Begin Group "_draw"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\..\src\draw\ed_base.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\draw\ed_context.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\draw\ed_device.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\draw\ed_font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\draw\ed_matrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\draw\ed_object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\draw\ed_space.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\draw\ed_store.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_context.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_device.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\ew_draw.cpp
# End Source File
# End Group
# Begin Group "_rep"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\rep\er_printer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rep\er_prndraw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rep\er_prnform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rep\er_prnspool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rep\er_repelem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rep\er_report.cpp
# End Source File
# End Group
# Begin Group "_mfc"

# PROP Default_Filter "*.cpp *.h"
# Begin Group "utool"

# PROP Default_Filter "*.cpp *.h"
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OX3DTabView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXCoolToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXDragDockContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXFrameWndDock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXHistoryCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXHookWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXLayoutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXMDIFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXMultiComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXRulerOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXScrollWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeCtrlBar.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeDlgBar.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeDockBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSplitterRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSzMiniDockFrmWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXTabView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXZoomVw.cpp
# End Source File
# End Group
# Begin Group "ugrid"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\Mycug97.cpp

!IF  "$(CFG)" == "ecl_dll_win - Win32 Release"

!ELSEIF  "$(CFG)" == "ecl_dll_win - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\Mycug97d.cpp

!IF  "$(CFG)" == "ecl_dll_win - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ecl_dll_win - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCBType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCelTyp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCnrBtn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCTarrw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDLType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDrgDrp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDrwHnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDtaSrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGExcel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGFormat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGGdInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGHint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGHScrol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGLstBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGMemMan.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGMultiS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGPrint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGPtrLst.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGSideHd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGTab.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGTopHdg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGVScrol.cpp
# End Source File
# End Group
# Begin Group "exlist"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxCategoryManager.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxCategoryManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxColumnManager.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxColumnManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxCustomizeColumnDlg.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxCustomizeColumnDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxFormatColumnDlg.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxFormatColumnDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxHeaderCtrl.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInCombo.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInCombo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboEdit.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboList.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboStatic.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboStatic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInEdit.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxListCtrl.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxListCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxListTip.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\exlist\GfxListTip.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\mfc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\mfc_c.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\mfc_d.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\mfc_m.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\mfc_t.cpp
# End Source File
# End Group
# Begin Group "_w32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\rep\system\w32\w32_defprn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rep\system\w32\w32_prndev.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "_mfc_h"

# PROP Default_Filter ""
# Begin Group "_utool_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OX3DTabView.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXBaseSubclassedComboBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXCoolToolBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXDllExt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXDragDockContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXDragDropSupport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXDropEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXFrameWndDock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXHistoryCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXHookWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXLayoutManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXLayoutManager.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXMDIFloatWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXMenuBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXMultiComboBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXMultiComboBox.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXRectTracker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXRulerOrganizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXScrollWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeCtrlBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeDlgBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeDockBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeToolBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSplitterRect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXSzMiniDockFrmWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXTabView.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXZoomVw.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\utool\OXZoomVw.inl
# End Source File
# End Group
# Begin Group "_ugrid_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\Mycug97.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCBType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCell.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCelTyp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCnrBtn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCTarrw.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDefine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDLType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDrgDrp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDrwHnt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDtaSrc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGExcel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGGdInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGGrid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGHint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGHScrol.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGLstbox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGMemMan.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGMultiS.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGPrint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGPtrLst.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGSideHd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGStruct.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGTab.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGTopHdg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGVScrol.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\mfc_t.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\win\system\mfc\stdafx.h
# End Source File
# End Group
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\eclwin.manifest
# End Source File
# Begin Source File

SOURCE=.\eclwin.rc
# End Source File
# End Group
# End Target
# End Project
