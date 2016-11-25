# Microsoft Developer Studio Project File - Name="qt_plugin_kbdlayouts" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=qt_plugin_kbdlayouts - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "qt_plugin_kbdlayouts.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "qt_plugin_kbdlayouts.mak" CFG="qt_plugin_kbdlayouts - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "qt_plugin_kbdlayouts - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "qt_plugin_kbdlayouts - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(QTDIR)/include" /I "..\..\..\Src\GUIFramework\QTFramework" /I "..\..\..\Src\GUIFramework\QTFramework\Keypads\generated" /I "..\..\..\Src\GUIFramework\QTFramework\Keypads" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_PLUGIN_KEYPADS_EXPORTS" /D "QT_DLL" /D "QT_PLUGIN" /D "QT_THREAD_SUPPORT" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winspool.lib winmm.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)/include" /I "..\..\..\Src\GUIFramework\QTFramework" /I "..\..\..\Src\GUIFramework\QTFramework\Keypads\generated" /I "..\..\..\Src\GUIFramework\QTFramework\Keypads" /D "_DEBUG" /D "QT_ACCESSIBILITY_SUPPORT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_PLUGIN_KEYPADS_EXPORTS" /D "QT_DLL" /D "QT_PLUGIN" /D "QT_THREAD_SUPPORT" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winspool.lib winmm.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"$(QTDIR)\lib"
# Begin Special Build Tool
TargetPath=.\Debug\qt_plugin_kbdlayouts.dll
SOURCE="$(InputPath)"
PostBuild_Desc=Plugin (Debug Version) in Qt Verzeichnis kopieren ...
PostBuild_Cmds=copy $(TargetPath) $(QTDIR)\plugins\designer >NUL
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "qt_plugin_kbdlayouts - Win32 Release"
# Name "qt_plugin_kbdlayouts - Win32 Debug"
# Begin Group "plugin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\Plugin\qt_plugin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\Plugin\qt_plugin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\Plugin\qt_plugin_register.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\Plugin\qt_plugin_register.h
# End Source File
# End Group
# Begin Group "widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h

!IF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h
InputName=qt_keyboard

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h
InputName=qt_keyboard

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.cpp
# ADD CPP /U "QT_PLUGIN"
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h

!IF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_button.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h
InputName=qt_keyboard_button

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_button.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h
InputName=qt_keyboard_button

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.cpp
# ADD CPP /U "QT_PLUGIN"
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h

!IF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_layout.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h
InputName=qt_keyboard_layout

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_layout.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h
InputName=qt_keyboard_layout

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_german.ui

!IF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_german.ui...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_german.ui
InputName=qt_keyboard_layout_german

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\generated\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\$(InputName).h -o $(InputDir)\generated\moc_$(InputName).cpp \
	

"$(InputDir)\generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_german.ui...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_german.ui
InputName=qt_keyboard_layout_german

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\generated\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\$(InputName).h -o $(InputDir)\generated\moc_$(InputName).cpp \
	

"$(InputDir)\generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_standard.ui

!IF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_standard.ui...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_standard.ui
InputName=qt_keyboard_layout_standard

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\generated\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\$(InputName).h -o $(InputDir)\generated\moc_$(InputName).cpp \
	

"$(InputDir)\generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "qt_plugin_kbdlayouts - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_standard.ui...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_standard.ui
InputName=qt_keyboard_layout_standard

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\generated\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\$(InputName).h -o $(InputDir)\generated\moc_$(InputName).cpp \
	

"$(InputDir)\generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_layout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_layout_german.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_layout_standard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\qt_keyboard_layout_german.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\qt_keyboard_layout_german.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\qt_keyboard_layout_standard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\qt_keyboard_layout_standard.h
# End Source File
# End Group
# End Target
# End Project
