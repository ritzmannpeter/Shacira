# Microsoft Developer Studio Generated NMAKE File, Based on ecl_dll_win.dsp
!IF "$(CFG)" == ""
CFG=ecl_dll_win - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ecl_dll_win - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ecl_dll_win - Win32 Release" && "$(CFG)" != "ecl_dll_win - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ecl_dll_win - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\eclwin.dll"

!ELSE 

ALL : "ecl_dll_dbi - Win32 Release" "ecl_dll_base - Win32 Release" "$(OUTDIR)\eclwin.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 ReleaseCLEAN" "ecl_dll_dbi - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\eclwin.res"
	-@erase "$(INTDIR)\ed_base.obj"
	-@erase "$(INTDIR)\ed_context.obj"
	-@erase "$(INTDIR)\ed_device.obj"
	-@erase "$(INTDIR)\ed_font.obj"
	-@erase "$(INTDIR)\ed_matrix.obj"
	-@erase "$(INTDIR)\ed_object.obj"
	-@erase "$(INTDIR)\ed_space.obj"
	-@erase "$(INTDIR)\ed_store.obj"
	-@erase "$(INTDIR)\er_printer.obj"
	-@erase "$(INTDIR)\er_prndraw.obj"
	-@erase "$(INTDIR)\er_prnform.obj"
	-@erase "$(INTDIR)\er_prnspool.obj"
	-@erase "$(INTDIR)\er_repelem.obj"
	-@erase "$(INTDIR)\er_report.obj"
	-@erase "$(INTDIR)\ew_application.obj"
	-@erase "$(INTDIR)\ew_base.obj"
	-@erase "$(INTDIR)\ew_buttonctls.obj"
	-@erase "$(INTDIR)\ew_cnrctls.obj"
	-@erase "$(INTDIR)\ew_commands.obj"
	-@erase "$(INTDIR)\ew_context.obj"
	-@erase "$(INTDIR)\ew_controls.obj"
	-@erase "$(INTDIR)\ew_device.obj"
	-@erase "$(INTDIR)\ew_dialogs.obj"
	-@erase "$(INTDIR)\ew_dragdrop.obj"
	-@erase "$(INTDIR)\ew_draw.obj"
	-@erase "$(INTDIR)\ew_editctls.obj"
	-@erase "$(INTDIR)\ew_frames.obj"
	-@erase "$(INTDIR)\ew_gridctls.obj"
	-@erase "$(INTDIR)\ew_lboxctls.obj"
	-@erase "$(INTDIR)\ew_listctls.obj"
	-@erase "$(INTDIR)\ew_logwins.obj"
	-@erase "$(INTDIR)\ew_menus.obj"
	-@erase "$(INTDIR)\ew_nbctls.obj"
	-@erase "$(INTDIR)\ew_statctls.obj"
	-@erase "$(INTDIR)\ew_threads.obj"
	-@erase "$(INTDIR)\ew_toolbars.obj"
	-@erase "$(INTDIR)\ew_treectls.obj"
	-@erase "$(INTDIR)\ew_views.obj"
	-@erase "$(INTDIR)\ew_windows.obj"
	-@erase "$(INTDIR)\mfc.obj"
	-@erase "$(INTDIR)\mfc_c.obj"
	-@erase "$(INTDIR)\mfc_d.obj"
	-@erase "$(INTDIR)\mfc_m.obj"
	-@erase "$(INTDIR)\mfc_t.obj"
	-@erase "$(INTDIR)\Mycug97.obj"
	-@erase "$(INTDIR)\OX3DTabView.obj"
	-@erase "$(INTDIR)\OXCoolToolBar.obj"
	-@erase "$(INTDIR)\OXDragDockContext.obj"
	-@erase "$(INTDIR)\OXFrameWndDock.obj"
	-@erase "$(INTDIR)\OXHistoryCtrl.obj"
	-@erase "$(INTDIR)\OXHookWnd.obj"
	-@erase "$(INTDIR)\OXLayoutManager.obj"
	-@erase "$(INTDIR)\OXMDIFloatWnd.obj"
	-@erase "$(INTDIR)\OXMenuBar.obj"
	-@erase "$(INTDIR)\OXMultiComboBox.obj"
	-@erase "$(INTDIR)\OXRectTracker.obj"
	-@erase "$(INTDIR)\OXRulerOrganizer.obj"
	-@erase "$(INTDIR)\OXScrollWnd.obj"
	-@erase "$(INTDIR)\OXSizeCtrlBar.obj"
	-@erase "$(INTDIR)\OXSizeDockBar.obj"
	-@erase "$(INTDIR)\OXSizeToolBar.obj"
	-@erase "$(INTDIR)\OXSplitterRect.obj"
	-@erase "$(INTDIR)\OXSzMiniDockFrmWnd.obj"
	-@erase "$(INTDIR)\OXTabView.obj"
	-@erase "$(INTDIR)\OXZoomVw.obj"
	-@erase "$(INTDIR)\UGCBType.obj"
	-@erase "$(INTDIR)\UGCell.obj"
	-@erase "$(INTDIR)\UGCelTyp.obj"
	-@erase "$(INTDIR)\UGCnrBtn.obj"
	-@erase "$(INTDIR)\UGCTarrw.obj"
	-@erase "$(INTDIR)\UGCtrl.obj"
	-@erase "$(INTDIR)\UGDLType.obj"
	-@erase "$(INTDIR)\UGDrgDrp.obj"
	-@erase "$(INTDIR)\UGDrwHnt.obj"
	-@erase "$(INTDIR)\UGDtaSrc.obj"
	-@erase "$(INTDIR)\UGEdit.obj"
	-@erase "$(INTDIR)\UGExcel.obj"
	-@erase "$(INTDIR)\UGFormat.obj"
	-@erase "$(INTDIR)\UGGdInfo.obj"
	-@erase "$(INTDIR)\UGGrid.obj"
	-@erase "$(INTDIR)\UGHint.obj"
	-@erase "$(INTDIR)\UGHScrol.obj"
	-@erase "$(INTDIR)\UGLstBox.obj"
	-@erase "$(INTDIR)\UGMemMan.obj"
	-@erase "$(INTDIR)\UGMultiS.obj"
	-@erase "$(INTDIR)\UGPrint.obj"
	-@erase "$(INTDIR)\UGPtrLst.obj"
	-@erase "$(INTDIR)\UGSideHd.obj"
	-@erase "$(INTDIR)\UGTab.obj"
	-@erase "$(INTDIR)\UGTopHdg.obj"
	-@erase "$(INTDIR)\UGVScrol.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\w32_defprn.obj"
	-@erase "$(INTDIR)\w32_prndev.obj"
	-@erase "$(OUTDIR)\eclwin.dll"
	-@erase "$(OUTDIR)\eclwin.exp"
	-@erase "$(OUTDIR)\eclwin.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W4 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_WIN_EXPORTS" /Fp"$(INTDIR)\ecl_dll_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\eclwin.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_dll_win.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\eclwin.pdb" /machine:I386 /out:"$(OUTDIR)\eclwin.dll" /implib:"$(OUTDIR)\eclwin.lib" 
LINK32_OBJS= \
	"$(INTDIR)\ew_application.obj" \
	"$(INTDIR)\ew_base.obj" \
	"$(INTDIR)\ew_commands.obj" \
	"$(INTDIR)\ew_dialogs.obj" \
	"$(INTDIR)\ew_dragdrop.obj" \
	"$(INTDIR)\ew_frames.obj" \
	"$(INTDIR)\ew_logwins.obj" \
	"$(INTDIR)\ew_menus.obj" \
	"$(INTDIR)\ew_threads.obj" \
	"$(INTDIR)\ew_toolbars.obj" \
	"$(INTDIR)\ew_views.obj" \
	"$(INTDIR)\ew_windows.obj" \
	"$(INTDIR)\ew_buttonctls.obj" \
	"$(INTDIR)\ew_cnrctls.obj" \
	"$(INTDIR)\ew_controls.obj" \
	"$(INTDIR)\ew_editctls.obj" \
	"$(INTDIR)\ew_gridctls.obj" \
	"$(INTDIR)\ew_lboxctls.obj" \
	"$(INTDIR)\ew_listctls.obj" \
	"$(INTDIR)\ew_nbctls.obj" \
	"$(INTDIR)\ew_statctls.obj" \
	"$(INTDIR)\ew_treectls.obj" \
	"$(INTDIR)\ed_base.obj" \
	"$(INTDIR)\ed_context.obj" \
	"$(INTDIR)\ed_device.obj" \
	"$(INTDIR)\ed_font.obj" \
	"$(INTDIR)\ed_matrix.obj" \
	"$(INTDIR)\ed_object.obj" \
	"$(INTDIR)\ed_space.obj" \
	"$(INTDIR)\ed_store.obj" \
	"$(INTDIR)\ew_context.obj" \
	"$(INTDIR)\ew_device.obj" \
	"$(INTDIR)\ew_draw.obj" \
	"$(INTDIR)\er_printer.obj" \
	"$(INTDIR)\er_prndraw.obj" \
	"$(INTDIR)\er_prnform.obj" \
	"$(INTDIR)\er_prnspool.obj" \
	"$(INTDIR)\er_repelem.obj" \
	"$(INTDIR)\er_report.obj" \
	"$(INTDIR)\OX3DTabView.obj" \
	"$(INTDIR)\OXCoolToolBar.obj" \
	"$(INTDIR)\OXDragDockContext.obj" \
	"$(INTDIR)\OXFrameWndDock.obj" \
	"$(INTDIR)\OXHistoryCtrl.obj" \
	"$(INTDIR)\OXHookWnd.obj" \
	"$(INTDIR)\OXLayoutManager.obj" \
	"$(INTDIR)\OXMDIFloatWnd.obj" \
	"$(INTDIR)\OXMenuBar.obj" \
	"$(INTDIR)\OXMultiComboBox.obj" \
	"$(INTDIR)\OXRectTracker.obj" \
	"$(INTDIR)\OXRulerOrganizer.obj" \
	"$(INTDIR)\OXScrollWnd.obj" \
	"$(INTDIR)\OXSizeCtrlBar.obj" \
	"$(INTDIR)\OXSizeDockBar.obj" \
	"$(INTDIR)\OXSizeToolBar.obj" \
	"$(INTDIR)\OXSplitterRect.obj" \
	"$(INTDIR)\OXSzMiniDockFrmWnd.obj" \
	"$(INTDIR)\OXTabView.obj" \
	"$(INTDIR)\OXZoomVw.obj" \
	"$(INTDIR)\Mycug97.obj" \
	"$(INTDIR)\UGCBType.obj" \
	"$(INTDIR)\UGCell.obj" \
	"$(INTDIR)\UGCelTyp.obj" \
	"$(INTDIR)\UGCnrBtn.obj" \
	"$(INTDIR)\UGCTarrw.obj" \
	"$(INTDIR)\UGCtrl.obj" \
	"$(INTDIR)\UGDLType.obj" \
	"$(INTDIR)\UGDrgDrp.obj" \
	"$(INTDIR)\UGDrwHnt.obj" \
	"$(INTDIR)\UGDtaSrc.obj" \
	"$(INTDIR)\UGEdit.obj" \
	"$(INTDIR)\UGExcel.obj" \
	"$(INTDIR)\UGFormat.obj" \
	"$(INTDIR)\UGGdInfo.obj" \
	"$(INTDIR)\UGGrid.obj" \
	"$(INTDIR)\UGHint.obj" \
	"$(INTDIR)\UGHScrol.obj" \
	"$(INTDIR)\UGLstBox.obj" \
	"$(INTDIR)\UGMemMan.obj" \
	"$(INTDIR)\UGMultiS.obj" \
	"$(INTDIR)\UGPrint.obj" \
	"$(INTDIR)\UGPtrLst.obj" \
	"$(INTDIR)\UGSideHd.obj" \
	"$(INTDIR)\UGTab.obj" \
	"$(INTDIR)\UGTopHdg.obj" \
	"$(INTDIR)\UGVScrol.obj" \
	"$(INTDIR)\mfc.obj" \
	"$(INTDIR)\mfc_c.obj" \
	"$(INTDIR)\mfc_d.obj" \
	"$(INTDIR)\mfc_m.obj" \
	"$(INTDIR)\mfc_t.obj" \
	"$(INTDIR)\w32_defprn.obj" \
	"$(INTDIR)\w32_prndev.obj" \
	"$(INTDIR)\eclwin.res" \
	"..\ecl_dll_base\Release\eclbse.lib" \
	"..\ecl_dll_dbi\Release\ecldbi.lib"

"$(OUTDIR)\eclwin.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\eclwin.dll
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "ecl_dll_dbi - Win32 Release" "ecl_dll_base - Win32 Release" "$(OUTDIR)\eclwin.dll"
   copy .\Release\eclwin.dll ..\..\..\bin\win32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ecl_dll_win - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\eclwind.dll"

!ELSE 

ALL : "ecl_dll_dbi - Win32 Debug" "ecl_dll_base - Win32 Debug" "$(OUTDIR)\eclwind.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 DebugCLEAN" "ecl_dll_dbi - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\eclwin.res"
	-@erase "$(INTDIR)\ed_base.obj"
	-@erase "$(INTDIR)\ed_context.obj"
	-@erase "$(INTDIR)\ed_device.obj"
	-@erase "$(INTDIR)\ed_font.obj"
	-@erase "$(INTDIR)\ed_matrix.obj"
	-@erase "$(INTDIR)\ed_object.obj"
	-@erase "$(INTDIR)\ed_space.obj"
	-@erase "$(INTDIR)\ed_store.obj"
	-@erase "$(INTDIR)\er_printer.obj"
	-@erase "$(INTDIR)\er_prndraw.obj"
	-@erase "$(INTDIR)\er_prnform.obj"
	-@erase "$(INTDIR)\er_prnspool.obj"
	-@erase "$(INTDIR)\er_repelem.obj"
	-@erase "$(INTDIR)\er_report.obj"
	-@erase "$(INTDIR)\ew_application.obj"
	-@erase "$(INTDIR)\ew_base.obj"
	-@erase "$(INTDIR)\ew_buttonctls.obj"
	-@erase "$(INTDIR)\ew_cnrctls.obj"
	-@erase "$(INTDIR)\ew_commands.obj"
	-@erase "$(INTDIR)\ew_context.obj"
	-@erase "$(INTDIR)\ew_controls.obj"
	-@erase "$(INTDIR)\ew_device.obj"
	-@erase "$(INTDIR)\ew_dialogs.obj"
	-@erase "$(INTDIR)\ew_dragdrop.obj"
	-@erase "$(INTDIR)\ew_draw.obj"
	-@erase "$(INTDIR)\ew_editctls.obj"
	-@erase "$(INTDIR)\ew_frames.obj"
	-@erase "$(INTDIR)\ew_gridctls.obj"
	-@erase "$(INTDIR)\ew_lboxctls.obj"
	-@erase "$(INTDIR)\ew_listctls.obj"
	-@erase "$(INTDIR)\ew_logwins.obj"
	-@erase "$(INTDIR)\ew_menus.obj"
	-@erase "$(INTDIR)\ew_nbctls.obj"
	-@erase "$(INTDIR)\ew_statctls.obj"
	-@erase "$(INTDIR)\ew_threads.obj"
	-@erase "$(INTDIR)\ew_toolbars.obj"
	-@erase "$(INTDIR)\ew_treectls.obj"
	-@erase "$(INTDIR)\ew_views.obj"
	-@erase "$(INTDIR)\ew_windows.obj"
	-@erase "$(INTDIR)\mfc.obj"
	-@erase "$(INTDIR)\mfc_c.obj"
	-@erase "$(INTDIR)\mfc_d.obj"
	-@erase "$(INTDIR)\mfc_m.obj"
	-@erase "$(INTDIR)\mfc_t.obj"
	-@erase "$(INTDIR)\Mycug97d.obj"
	-@erase "$(INTDIR)\OX3DTabView.obj"
	-@erase "$(INTDIR)\OXCoolToolBar.obj"
	-@erase "$(INTDIR)\OXDragDockContext.obj"
	-@erase "$(INTDIR)\OXFrameWndDock.obj"
	-@erase "$(INTDIR)\OXHistoryCtrl.obj"
	-@erase "$(INTDIR)\OXHookWnd.obj"
	-@erase "$(INTDIR)\OXLayoutManager.obj"
	-@erase "$(INTDIR)\OXMDIFloatWnd.obj"
	-@erase "$(INTDIR)\OXMenuBar.obj"
	-@erase "$(INTDIR)\OXMultiComboBox.obj"
	-@erase "$(INTDIR)\OXRectTracker.obj"
	-@erase "$(INTDIR)\OXRulerOrganizer.obj"
	-@erase "$(INTDIR)\OXScrollWnd.obj"
	-@erase "$(INTDIR)\OXSizeCtrlBar.obj"
	-@erase "$(INTDIR)\OXSizeDockBar.obj"
	-@erase "$(INTDIR)\OXSizeToolBar.obj"
	-@erase "$(INTDIR)\OXSplitterRect.obj"
	-@erase "$(INTDIR)\OXSzMiniDockFrmWnd.obj"
	-@erase "$(INTDIR)\OXTabView.obj"
	-@erase "$(INTDIR)\OXZoomVw.obj"
	-@erase "$(INTDIR)\UGCBType.obj"
	-@erase "$(INTDIR)\UGCell.obj"
	-@erase "$(INTDIR)\UGCelTyp.obj"
	-@erase "$(INTDIR)\UGCnrBtn.obj"
	-@erase "$(INTDIR)\UGCTarrw.obj"
	-@erase "$(INTDIR)\UGCtrl.obj"
	-@erase "$(INTDIR)\UGDLType.obj"
	-@erase "$(INTDIR)\UGDrgDrp.obj"
	-@erase "$(INTDIR)\UGDrwHnt.obj"
	-@erase "$(INTDIR)\UGDtaSrc.obj"
	-@erase "$(INTDIR)\UGEdit.obj"
	-@erase "$(INTDIR)\UGExcel.obj"
	-@erase "$(INTDIR)\UGFormat.obj"
	-@erase "$(INTDIR)\UGGdInfo.obj"
	-@erase "$(INTDIR)\UGGrid.obj"
	-@erase "$(INTDIR)\UGHint.obj"
	-@erase "$(INTDIR)\UGHScrol.obj"
	-@erase "$(INTDIR)\UGLstBox.obj"
	-@erase "$(INTDIR)\UGMemMan.obj"
	-@erase "$(INTDIR)\UGMultiS.obj"
	-@erase "$(INTDIR)\UGPrint.obj"
	-@erase "$(INTDIR)\UGPtrLst.obj"
	-@erase "$(INTDIR)\UGSideHd.obj"
	-@erase "$(INTDIR)\UGTab.obj"
	-@erase "$(INTDIR)\UGTopHdg.obj"
	-@erase "$(INTDIR)\UGVScrol.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\w32_defprn.obj"
	-@erase "$(INTDIR)\w32_prndev.obj"
	-@erase "$(OUTDIR)\eclwind.dll"
	-@erase "$(OUTDIR)\eclwind.exp"
	-@erase "$(OUTDIR)\eclwind.ilk"
	-@erase "$(OUTDIR)\eclwind.lib"
	-@erase "$(OUTDIR)\eclwind.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_WIN_EXPORTS" /Fp"$(INTDIR)\ecl_dll_win.pch" /YX"mfc.hpp" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\eclwin.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_dll_win.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\eclwind.pdb" /debug /machine:I386 /out:"$(OUTDIR)\eclwind.dll" /implib:"$(OUTDIR)\eclwind.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ew_application.obj" \
	"$(INTDIR)\ew_base.obj" \
	"$(INTDIR)\ew_commands.obj" \
	"$(INTDIR)\ew_dialogs.obj" \
	"$(INTDIR)\ew_dragdrop.obj" \
	"$(INTDIR)\ew_frames.obj" \
	"$(INTDIR)\ew_logwins.obj" \
	"$(INTDIR)\ew_menus.obj" \
	"$(INTDIR)\ew_threads.obj" \
	"$(INTDIR)\ew_toolbars.obj" \
	"$(INTDIR)\ew_views.obj" \
	"$(INTDIR)\ew_windows.obj" \
	"$(INTDIR)\ew_buttonctls.obj" \
	"$(INTDIR)\ew_cnrctls.obj" \
	"$(INTDIR)\ew_controls.obj" \
	"$(INTDIR)\ew_editctls.obj" \
	"$(INTDIR)\ew_gridctls.obj" \
	"$(INTDIR)\ew_lboxctls.obj" \
	"$(INTDIR)\ew_listctls.obj" \
	"$(INTDIR)\ew_nbctls.obj" \
	"$(INTDIR)\ew_statctls.obj" \
	"$(INTDIR)\ew_treectls.obj" \
	"$(INTDIR)\ed_base.obj" \
	"$(INTDIR)\ed_context.obj" \
	"$(INTDIR)\ed_device.obj" \
	"$(INTDIR)\ed_font.obj" \
	"$(INTDIR)\ed_matrix.obj" \
	"$(INTDIR)\ed_object.obj" \
	"$(INTDIR)\ed_space.obj" \
	"$(INTDIR)\ed_store.obj" \
	"$(INTDIR)\ew_context.obj" \
	"$(INTDIR)\ew_device.obj" \
	"$(INTDIR)\ew_draw.obj" \
	"$(INTDIR)\er_printer.obj" \
	"$(INTDIR)\er_prndraw.obj" \
	"$(INTDIR)\er_prnform.obj" \
	"$(INTDIR)\er_prnspool.obj" \
	"$(INTDIR)\er_repelem.obj" \
	"$(INTDIR)\er_report.obj" \
	"$(INTDIR)\OX3DTabView.obj" \
	"$(INTDIR)\OXCoolToolBar.obj" \
	"$(INTDIR)\OXDragDockContext.obj" \
	"$(INTDIR)\OXFrameWndDock.obj" \
	"$(INTDIR)\OXHistoryCtrl.obj" \
	"$(INTDIR)\OXHookWnd.obj" \
	"$(INTDIR)\OXLayoutManager.obj" \
	"$(INTDIR)\OXMDIFloatWnd.obj" \
	"$(INTDIR)\OXMenuBar.obj" \
	"$(INTDIR)\OXMultiComboBox.obj" \
	"$(INTDIR)\OXRectTracker.obj" \
	"$(INTDIR)\OXRulerOrganizer.obj" \
	"$(INTDIR)\OXScrollWnd.obj" \
	"$(INTDIR)\OXSizeCtrlBar.obj" \
	"$(INTDIR)\OXSizeDockBar.obj" \
	"$(INTDIR)\OXSizeToolBar.obj" \
	"$(INTDIR)\OXSplitterRect.obj" \
	"$(INTDIR)\OXSzMiniDockFrmWnd.obj" \
	"$(INTDIR)\OXTabView.obj" \
	"$(INTDIR)\OXZoomVw.obj" \
	"$(INTDIR)\Mycug97d.obj" \
	"$(INTDIR)\UGCBType.obj" \
	"$(INTDIR)\UGCell.obj" \
	"$(INTDIR)\UGCelTyp.obj" \
	"$(INTDIR)\UGCnrBtn.obj" \
	"$(INTDIR)\UGCTarrw.obj" \
	"$(INTDIR)\UGCtrl.obj" \
	"$(INTDIR)\UGDLType.obj" \
	"$(INTDIR)\UGDrgDrp.obj" \
	"$(INTDIR)\UGDrwHnt.obj" \
	"$(INTDIR)\UGDtaSrc.obj" \
	"$(INTDIR)\UGEdit.obj" \
	"$(INTDIR)\UGExcel.obj" \
	"$(INTDIR)\UGFormat.obj" \
	"$(INTDIR)\UGGdInfo.obj" \
	"$(INTDIR)\UGGrid.obj" \
	"$(INTDIR)\UGHint.obj" \
	"$(INTDIR)\UGHScrol.obj" \
	"$(INTDIR)\UGLstBox.obj" \
	"$(INTDIR)\UGMemMan.obj" \
	"$(INTDIR)\UGMultiS.obj" \
	"$(INTDIR)\UGPrint.obj" \
	"$(INTDIR)\UGPtrLst.obj" \
	"$(INTDIR)\UGSideHd.obj" \
	"$(INTDIR)\UGTab.obj" \
	"$(INTDIR)\UGTopHdg.obj" \
	"$(INTDIR)\UGVScrol.obj" \
	"$(INTDIR)\mfc.obj" \
	"$(INTDIR)\mfc_c.obj" \
	"$(INTDIR)\mfc_d.obj" \
	"$(INTDIR)\mfc_m.obj" \
	"$(INTDIR)\mfc_t.obj" \
	"$(INTDIR)\w32_defprn.obj" \
	"$(INTDIR)\w32_prndev.obj" \
	"$(INTDIR)\eclwin.res" \
	"..\ecl_dll_base\Debug\eclbsed.lib" \
	"..\ecl_dll_dbi\Debug\ecldbid.lib"

"$(OUTDIR)\eclwind.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\eclwind.dll
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "ecl_dll_dbi - Win32 Debug" "ecl_dll_base - Win32 Debug" "$(OUTDIR)\eclwind.dll"
   copy .\Debug\eclwind.dll ..\..\..\bin\win32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ecl_dll_win.dep")
!INCLUDE "ecl_dll_win.dep"
!ELSE 
!MESSAGE Warning: cannot find "ecl_dll_win.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ecl_dll_win - Win32 Release" || "$(CFG)" == "ecl_dll_win - Win32 Debug"
SOURCE=..\..\..\src\win\ew_application.cpp

"$(INTDIR)\ew_application.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_base.cpp

"$(INTDIR)\ew_base.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_commands.cpp

"$(INTDIR)\ew_commands.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_dialogs.cpp

"$(INTDIR)\ew_dialogs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_dragdrop.cpp

"$(INTDIR)\ew_dragdrop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_frames.cpp

"$(INTDIR)\ew_frames.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_logwins.cpp

"$(INTDIR)\ew_logwins.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_menus.cpp

"$(INTDIR)\ew_menus.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_threads.cpp

"$(INTDIR)\ew_threads.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_toolbars.cpp

"$(INTDIR)\ew_toolbars.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_views.cpp

"$(INTDIR)\ew_views.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_windows.cpp

"$(INTDIR)\ew_windows.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_buttonctls.cpp

"$(INTDIR)\ew_buttonctls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_cnrctls.cpp

"$(INTDIR)\ew_cnrctls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_controls.cpp

"$(INTDIR)\ew_controls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_editctls.cpp

"$(INTDIR)\ew_editctls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_gridctls.cpp

"$(INTDIR)\ew_gridctls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_lboxctls.cpp

"$(INTDIR)\ew_lboxctls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_listctls.cpp

"$(INTDIR)\ew_listctls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_nbctls.cpp

"$(INTDIR)\ew_nbctls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_statctls.cpp

"$(INTDIR)\ew_statctls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_treectls.cpp

"$(INTDIR)\ew_treectls.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\draw\ed_base.cpp

"$(INTDIR)\ed_base.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\draw\ed_context.cpp

"$(INTDIR)\ed_context.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\draw\ed_device.cpp

"$(INTDIR)\ed_device.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\draw\ed_font.cpp

"$(INTDIR)\ed_font.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\draw\ed_matrix.cpp

"$(INTDIR)\ed_matrix.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\draw\ed_object.cpp

"$(INTDIR)\ed_object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\draw\ed_space.cpp

"$(INTDIR)\ed_space.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\draw\ed_store.cpp

"$(INTDIR)\ed_store.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_context.cpp

"$(INTDIR)\ew_context.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_device.cpp

"$(INTDIR)\ew_device.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\ew_draw.cpp

"$(INTDIR)\ew_draw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\rep\er_printer.cpp

"$(INTDIR)\er_printer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\rep\er_prndraw.cpp

"$(INTDIR)\er_prndraw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\rep\er_prnform.cpp

"$(INTDIR)\er_prnform.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\rep\er_prnspool.cpp

"$(INTDIR)\er_prnspool.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\rep\er_repelem.cpp

"$(INTDIR)\er_repelem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\rep\er_report.cpp

"$(INTDIR)\er_report.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OX3DTabView.cpp

"$(INTDIR)\OX3DTabView.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXCoolToolBar.cpp

"$(INTDIR)\OXCoolToolBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXDragDockContext.cpp

"$(INTDIR)\OXDragDockContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXFrameWndDock.cpp

"$(INTDIR)\OXFrameWndDock.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXHistoryCtrl.cpp

"$(INTDIR)\OXHistoryCtrl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXHookWnd.cpp

"$(INTDIR)\OXHookWnd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXLayoutManager.cpp

"$(INTDIR)\OXLayoutManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXMDIFloatWnd.cpp

"$(INTDIR)\OXMDIFloatWnd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXMenuBar.cpp

"$(INTDIR)\OXMenuBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXMultiComboBox.cpp

"$(INTDIR)\OXMultiComboBox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXRectTracker.cpp

"$(INTDIR)\OXRectTracker.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXRulerOrganizer.cpp

"$(INTDIR)\OXRulerOrganizer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXScrollWnd.cpp

"$(INTDIR)\OXScrollWnd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeCtrlBar.CPP

"$(INTDIR)\OXSizeCtrlBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeDlgBar.cpp
SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeDockBar.cpp

"$(INTDIR)\OXSizeDockBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXSizeToolBar.cpp

"$(INTDIR)\OXSizeToolBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXSplitterRect.cpp

"$(INTDIR)\OXSplitterRect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXSzMiniDockFrmWnd.cpp

"$(INTDIR)\OXSzMiniDockFrmWnd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXTabView.cpp

"$(INTDIR)\OXTabView.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\utool\OXZoomVw.cpp

"$(INTDIR)\OXZoomVw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\Mycug97.cpp

!IF  "$(CFG)" == "ecl_dll_win - Win32 Release"


"$(INTDIR)\Mycug97.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ecl_dll_win - Win32 Debug"

!ENDIF 

SOURCE=..\..\..\src\win\system\mfc\ugrid\Mycug97d.cpp

!IF  "$(CFG)" == "ecl_dll_win - Win32 Release"

!ELSEIF  "$(CFG)" == "ecl_dll_win - Win32 Debug"


"$(INTDIR)\Mycug97d.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCBType.cpp

"$(INTDIR)\UGCBType.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCell.cpp

"$(INTDIR)\UGCell.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCelTyp.cpp

"$(INTDIR)\UGCelTyp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCnrBtn.cpp

"$(INTDIR)\UGCnrBtn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCTarrw.cpp

"$(INTDIR)\UGCTarrw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGCtrl.cpp

"$(INTDIR)\UGCtrl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDLType.cpp

"$(INTDIR)\UGDLType.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDrgDrp.cpp

"$(INTDIR)\UGDrgDrp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDrwHnt.cpp

"$(INTDIR)\UGDrwHnt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGDtaSrc.cpp

"$(INTDIR)\UGDtaSrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGEdit.cpp

"$(INTDIR)\UGEdit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGExcel.cpp

"$(INTDIR)\UGExcel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGFormat.cpp

"$(INTDIR)\UGFormat.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGGdInfo.cpp

"$(INTDIR)\UGGdInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGGrid.cpp

"$(INTDIR)\UGGrid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGHint.cpp

"$(INTDIR)\UGHint.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGHScrol.cpp

"$(INTDIR)\UGHScrol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGLstBox.cpp

"$(INTDIR)\UGLstBox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGMemMan.cpp

"$(INTDIR)\UGMemMan.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGMultiS.cpp

"$(INTDIR)\UGMultiS.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGPrint.cpp

"$(INTDIR)\UGPrint.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGPtrLst.cpp

"$(INTDIR)\UGPtrLst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGSideHd.cpp

"$(INTDIR)\UGSideHd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGTab.cpp

"$(INTDIR)\UGTab.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGTopHdg.cpp

"$(INTDIR)\UGTopHdg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\ugrid\UGVScrol.cpp

"$(INTDIR)\UGVScrol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\exlist\GfxCategoryManager.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxColumnManager.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxCustomizeColumnDlg.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxFormatColumnDlg.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxHeaderCtrl.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInCombo.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboEdit.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboList.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInComboStatic.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxInEdit.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxListCtrl.cpp
SOURCE=..\..\..\src\win\system\mfc\exlist\GfxListTip.cpp
SOURCE=..\..\..\src\win\system\mfc\mfc.cpp

"$(INTDIR)\mfc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\mfc_c.cpp

"$(INTDIR)\mfc_c.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\mfc_d.cpp

"$(INTDIR)\mfc_d.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\mfc_m.cpp

"$(INTDIR)\mfc_m.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\system\mfc\mfc_t.cpp

"$(INTDIR)\mfc_t.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\rep\system\w32\w32_defprn.cpp

"$(INTDIR)\w32_defprn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\rep\system\w32\w32_prndev.cpp

"$(INTDIR)\w32_prndev.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\eclwin.rc

"$(INTDIR)\eclwin.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "ecl_dll_win - Win32 Release"

"ecl_dll_base - Win32 Release" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" 
   cd "..\ecl_dll_win"

"ecl_dll_base - Win32 ReleaseCLEAN" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" RECURSE=1 CLEAN 
   cd "..\ecl_dll_win"

!ELSEIF  "$(CFG)" == "ecl_dll_win - Win32 Debug"

"ecl_dll_base - Win32 Debug" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" 
   cd "..\ecl_dll_win"

"ecl_dll_base - Win32 DebugCLEAN" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\ecl_dll_win"

!ENDIF 

!IF  "$(CFG)" == "ecl_dll_win - Win32 Release"

"ecl_dll_dbi - Win32 Release" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Release" 
   cd "..\ecl_dll_win"

"ecl_dll_dbi - Win32 ReleaseCLEAN" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\ecl_dll_win"

!ELSEIF  "$(CFG)" == "ecl_dll_win - Win32 Debug"

"ecl_dll_dbi - Win32 Debug" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Debug" 
   cd "..\ecl_dll_win"

"ecl_dll_dbi - Win32 DebugCLEAN" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\ecl_dll_win"

!ENDIF 


!ENDIF 

