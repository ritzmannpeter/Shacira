# Microsoft Developer Studio Project File - Name="q3_framework" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=q3_framework - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "q3_framework.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "q3_framework.mak" CFG="q3_framework - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "q3_framework - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "q3_framework - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "$(QTDIR)\include" /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Src\Orb" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\QT3Framework\Generated" /I "..\..\..\Src\GUIFramework\QT3Framework\Dialogs" /I "..\..\..\Src\GUIFramework\QT3Framework\Keypads" /I "..\..\..\Src\GUIFramework\QT3Framework\CWidgets" /I "..\..\..\Src\GUIFramework\QT3Framework\Plugins" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "__x86__" /D "__WIN32__" /D "__OMNIORB4__" /D "_COS_LIBRARY" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "$(QTDIR)\include" /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Src\Orb" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\QT3Framework\Generated" /I "..\..\..\Src\GUIFramework\QT3Framework\Dialogs" /I "..\..\..\Src\GUIFramework\QT3Framework\Keypads" /I "..\..\..\Src\GUIFramework\QT3Framework\CWidgets" /I "..\..\..\Src\GUIFramework\QT3Framework\Plugins" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__x86__" /D "__WIN32__" /D "__OMNIORB4__" /D "_COS_LIBRARY" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\q3_frameworkd.lib"

!ENDIF 

# Begin Target

# Name "q3_framework - Win32 Release"
# Name "q3_framework - Win32 Debug"
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\ContextExplorer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\KeyboardAlpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\KeyboardLayoutGerman.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\KeyboardLayoutStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\KeypadNumeric.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cContextChooser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cContextExplorer.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cGuiThread.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_ContextExplorer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_ContextExplorerDialog.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CPublicDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CPushButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeyboardAlpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeyboardButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeyboardInput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeyboardLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtKeypadNumeric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cQtTouchStyle.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_cWidgetComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CWidgetStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_KeyboardAlpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_KeyboardLayoutGerman.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_KeyboardLayoutStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_KeypadNumeric.cpp
# End Source File
# End Group
# Begin Group "Forms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\ContextExplorer.ui

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\ContextExplorer.ui
InputName=ContextExplorer

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

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\ContextExplorer.ui
InputName=ContextExplorer

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
# Begin Group "Dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\ContextExplorerDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\ContextExplorerDialog.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Dialogs
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\ContextExplorerDialog.h
InputName=ContextExplorerDialog

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Dialogs
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\ContextExplorerDialog.h
InputName=ContextExplorerDialog

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\cQtNavigationWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Dialogs\cQtNavigationWidget.h
# End Source File
# End Group
# Begin Group "CCSInterface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\Interface\cCCSInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\Interface\cContextChooser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\Interface\cContextChooser.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\Interface
InputPath=..\..\..\Src\GUIFramework\Interface\cContextChooser.h
InputName=cContextChooser

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\Interface
InputPath=..\..\..\Src\GUIFramework\Interface\cContextChooser.h
InputName=cContextChooser

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cAsyncFunction.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cCommInterface.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cGuiEvents.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cGuiThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cGuiThread.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cGuiThread.h
InputName=cGuiThread

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cGuiThread.h
InputName=cGuiThread

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\ClickFilter.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPublicDialog.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPublicDialog.h
InputName=CPublicDialog

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPublicDialog.h
InputName=CPublicDialog

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CPushButton.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cSignalManager.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cSyncView.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cViewInterface.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidgetBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cWidgetComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cWidgetComm.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cWidgetComm.h
InputName=cWidgetComm

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cWidgetComm.h
InputName=cWidgetComm

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidgetStack.cpp
# End Source File
# End Group
# Begin Group "Keypads"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardAlpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardAlpha.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Keypads
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardAlpha.h
InputName=cQtKeyboardAlpha

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Keypads
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardAlpha.h
InputName=cQtKeyboardAlpha

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardInput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardInput.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Keypads
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardInput.h
InputName=cQtKeyboardInput

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Keypads
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardInput.h
InputName=cQtKeyboardInput

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeyboardLayout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeypadNumeric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeypadNumeric.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Keypads
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeypadNumeric.h
InputName=cQtKeypadNumeric

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Keypads
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtKeypadNumeric.h
InputName=cQtKeypadNumeric

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtNumberValidator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtPathValidator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtPropertyWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Keypads\cQtStringValidator.cpp
# End Source File
# End Group
# Begin Group "Styles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Styles\cQtTouchStyle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Styles\cQtTouchStyle.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Styles
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Styles\cQtTouchStyle.h
InputName=cQtTouchStyle

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework\Styles
InputPath=..\..\..\Src\GUIFramework\QT3Framework\Styles\cQtTouchStyle.h
InputName=cQtTouchStyle

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "HTML"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Html\cFormRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Html\cFormRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Html\cHTMLDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Html\cHTMLDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Html\cHTMLElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Html\cHTMLElement.h
# End Source File
# End Group
# Begin Group "Factory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\CWidgetFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\CWidgetFactory.h
# End Source File
# End Group
# Begin Group "Plugin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\Plugins\plugin_log.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\cApplicationGuard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\cApplicationGuard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\cContextExplorer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\cContextExplorer.h

!IF  "$(CFG)" == "q3_framework - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework
InputPath=..\..\..\Src\GUIFramework\QT3Framework\cContextExplorer.h
InputName=cContextExplorer

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "q3_framework - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\GUIFramework\QT3Framework
InputPath=..\..\..\Src\GUIFramework\QT3Framework\cContextExplorer.h
InputName=cContextExplorer

"..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cGroupList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cGroupList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cHelpInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cHelpInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cNodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\cQTUserInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT3Framework\cQTUserInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cUserInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cUserInterface.h
# End Source File
# End Target
# End Project
