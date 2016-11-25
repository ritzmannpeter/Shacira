# Microsoft Developer Studio Project File - Name="q3_cwidget_plugin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=q3_cwidget_plugin - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "q3_cwidget_plugin.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "q3_cwidget_plugin.mak" CFG="q3_cwidget_plugin - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "q3_cwidget_plugin - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "q3_cwidget_plugin - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GX /O1 /I "..\..\..\Src\include" /I "$(QTDIR)\include" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\QT3Framework\Generated" /I "..\..\..\Src\GUIFramework\QT3Framework\Plugins" /I "..\..\..\Src\GUIFramework\QT3Framework\Keypads" /I "..\..\..\Src\GUIFramework\QT3Framework\CWidgets" /D "NDEBUG" /D "QT_NO_DEBUG" /D "QT_LICENSE_PROFESSIONAL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_DLL" /D "QT_PLUGIN" /D "QT_THREAD_SUPPORT" /D "_KEYBOARD_PLUGIN_WIN32" /D "_CWIDGET_PLUGIN_" /FR /FD -Zm200 /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winmm.lib winspool.lib opengl32.lib glu32.lib /nologo /dll /machine:IX86 /libpath:"..\..\..\Extern\STL\Lib" /libpath:"..\..\..\Extern\Drv\AddiData\x86_win32"
# Begin Special Build Tool
TargetPath=.\Release\q3_cwidget_plugin.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) $(QTDIR)\plugins\designer
# End Special Build Tool

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Src\include" /I "$(QTDIR)\include" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\QT3Framework\Generated" /I "..\..\..\Src\GUIFramework\QT3Framework\Plugins" /I "..\..\..\Src\GUIFramework\QT3Framework\Keypads" /I "..\..\..\Src\GUIFramework\QT3Framework\CWidgets" /D "_DEBUG" /D "QT_ACCESSIBILITY_SUPPORT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_DLL" /D "QT_PLUGIN" /D "QT_THREAD_SUPPORT" /D "_CWIDGET_PLUGIN_" /FR /FD /GZ -Zm200 /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winmm.lib winspool.lib opengl32.lib glu32.lib /nologo /dll /debug /machine:IX86 /pdbtype:sept /libpath:"..\..\..\Extern\STL\Lib" /libpath:"..\..\..\Extern\Drv\AddiData\x86_win32"
# Begin Special Build Tool
TargetPath=.\Debug\q3_cwidget_plugin.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) $(QTDIR)\plugins\designer
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "q3_cwidget_plugin - Win32 Release"
# Name "q3_cwidget_plugin - Win32 Debug"
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\KeyboardLayoutGerman.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\KeyboardLayoutStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CActionDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CActValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CAlarmWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CAppFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CButtonGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CCheckBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CCompListView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CComposedStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CCoordSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CFixText.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CGraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CGroupBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CGroupSelectButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CIndReqValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CInfoLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CListView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CProcGraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CProtocolWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CPushButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeyboardButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeyboardLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CRadioButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CReqValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CRingGraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CScrollView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CSimpleGraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CSlider.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CSpinBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CStartupForm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CStateButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CTabWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CTextEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CToolButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CVarDimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CVideo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CVirtualKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CWidgetStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_KeyboardLayoutGerman.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_KeyboardLayoutStandard.cpp
# End Source File
# End Group
# Begin Group "Plugin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\cQtPluginRegistry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\cQtPluginRegistry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\CWidgetPlugin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\CWidgetPlugin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\default_icon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\embedded_images.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\FrameworkPlugin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\FrameworkPlugin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\plugin_icons.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\plugin_log.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\plugin_log.h
# End Source File
# End Group
# Begin Group "Forms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\KeyboardAlpha.ui

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\KeyboardAlpha.ui
InputName=KeyboardAlpha

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).cpp \
	%qtdir%\bin\moc.exe ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\KeyboardAlpha.ui
InputName=KeyboardAlpha

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).cpp \
	%qtdir%\bin\moc.exe ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\KeypadNumeric.ui

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\KeypadNumeric.ui
InputName=KeypadNumeric

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).cpp \
	%qtdir%\bin\moc.exe ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\KeypadNumeric.ui
InputName=KeypadNumeric

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).cpp \
	%qtdir%\bin\moc.exe ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Preprocessor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CActionDialog.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CActionDialog.pp
InputName=CActionDialog

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CActionDialog.pp
InputName=CActionDialog

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CActValue.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CActValue.pp
InputName=CActValue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CActValue.pp
InputName=CActValue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CAlarmWidget.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CAlarmWidget.pp
InputName=CAlarmWidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CAlarmWidget.pp
InputName=CAlarmWidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CAppFrame.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CAppFrame.pp
InputName=CAppFrame

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CAppFrame.pp
InputName=CAppFrame

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CButtonGroup.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CButtonGroup.pp
InputName=CButtonGroup

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CButtonGroup.pp
InputName=CButtonGroup

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCheckBox.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCheckBox.pp
InputName=CCheckBox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCheckBox.pp
InputName=CCheckBox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CComboBox.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CComboBox.pp
InputName=CComboBox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CComboBox.pp
InputName=CComboBox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCompListView.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCompListView.pp
InputName=CCompListView

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCompListView.pp
InputName=CCompListView

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CComposedStack.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CComposedStack.pp
InputName=CComposedStack

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CComposedStack.pp
InputName=CComposedStack

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCoordSystem.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCoordSystem.pp
InputName=CCoordSystem

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCoordSystem.pp
InputName=CCoordSystem

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDate.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDate.pp
InputName=CDate

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDate.pp
InputName=CDate

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDateTime.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDateTime.pp
InputName=CDateTime

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDateTime.pp
InputName=CDateTime

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDirectory.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDirectory.pp
InputName=CDirectory

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDirectory.pp
InputName=CDirectory

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CFixText.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CFixText.pp
InputName=CFixText

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CFixText.pp
InputName=CFixText

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CFrame.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CFrame.pp
InputName=CFrame

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CFrame.pp
InputName=CFrame

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGraphic.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGraphic.pp
InputName=CGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGraphic.pp
InputName=CGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGroupBox.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGroupBox.pp
InputName=CGroupBox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGroupBox.pp
InputName=CGroupBox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGroupSelectButton.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGroupSelectButton.pp
InputName=CGroupSelectButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGroupSelectButton.pp
InputName=CGroupSelectButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CIndReqValue.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CIndReqValue.pp
InputName=CIndReqValue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CIndReqValue.pp
InputName=CIndReqValue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CInfoLabel.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CInfoLabel.pp
InputName=CInfoLabel

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CInfoLabel.pp
InputName=CInfoLabel

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CListView.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CListView.pp
InputName=CListView

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CListView.pp
InputName=CListView

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPage.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPage.pp
InputName=CPage

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPage.pp
InputName=CPage

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProcGraphic.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProcGraphic.pp
InputName=CProcGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProcGraphic.pp
InputName=CProcGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProgressBar.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProgressBar.pp
InputName=CProgressBar

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProgressBar.pp
InputName=CProgressBar

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProtocolWindow.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProtocolWindow.pp
InputName=CProtocolWindow

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProtocolWindow.pp
InputName=CProtocolWindow

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPushButton.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPushButton.pp
InputName=CPushButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPushButton.pp
InputName=CPushButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CRadioButton.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CRadioButton.pp
InputName=CRadioButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CRadioButton.pp
InputName=CRadioButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CReqValue.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CReqValue.pp
InputName=CReqValue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CReqValue.pp
InputName=CReqValue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CRingGraphic.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CRingGraphic.pp
InputName=CRingGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CRingGraphic.pp
InputName=CRingGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CScrollBar.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CScrollBar.pp
InputName=CScrollBar

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CScrollBar.pp
InputName=CScrollBar

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CScrollView.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CScrollView.pp
InputName=CScrollView

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CScrollView.pp
InputName=CScrollView

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSimpleGraphic.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSimpleGraphic.pp
InputName=CSimpleGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSimpleGraphic.pp
InputName=CSimpleGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSlider.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSlider.pp
InputName=CSlider

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSlider.pp
InputName=CSlider

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSpinBox.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSpinBox.pp
InputName=CSpinBox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSpinBox.pp
InputName=CSpinBox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CStartupForm.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CStartupForm.pp
InputName=CStartupForm

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CStartupForm.pp
InputName=CStartupForm

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CStateButton.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CStateButton.pp
InputName=CStateButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CStateButton.pp
InputName=CStateButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTable.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTable.pp
InputName=CTable

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTable.pp
InputName=CTable

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTabWidget.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTabWidget.pp
InputName=CTabWidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTabWidget.pp
InputName=CTabWidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTextEdit.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTextEdit.pp
InputName=CTextEdit

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTextEdit.pp
InputName=CTextEdit

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTime.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTime.pp
InputName=CTime

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTime.pp
InputName=CTime

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CToolButton.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CToolButton.pp
InputName=CToolButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CToolButton.pp
InputName=CToolButton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVarDimension.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVarDimension.pp
InputName=CVarDimension

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVarDimension.pp
InputName=CVarDimension

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVideo.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVideo.pp
InputName=CVideo

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVideo.pp
InputName=CVideo

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVirtualKeyboard.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVirtualKeyboard.pp
InputName=CVirtualKeyboard

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVirtualKeyboard.pp
InputName=CVirtualKeyboard

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidget.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidget.pp
InputName=CWidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidget.pp
InputName=CWidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidgetStack.pp

!IF  "$(CFG)" == "q3_cwidget_plugin - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidgetStack.pp
InputName=CWidgetStack

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "q3_cwidget_plugin - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidgetStack.pp
InputName=CWidgetStack

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc ..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h -o ..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp \
	

"..\..\..\Src\GUIFramework\QT3Framework\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CActionDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CActValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CAlarmWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CAppFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CButtonGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCheckBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCompListView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CComposedStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCoordSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CFixText.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGroupBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CGroupSelectButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CIndReqValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CInfoLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cInput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CListView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cPaintUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProcGraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CProtocolWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPushButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CRadioButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CReqValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CRingGraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cRubberBand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CScrollView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSimpleGraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSlider.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CSpinBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CStartupForm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CStateButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTabWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTextEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CToolButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVarDimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVideo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CVirtualKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidgetBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidgetStack.cpp
# End Source File
# End Group
# End Target
# End Project
