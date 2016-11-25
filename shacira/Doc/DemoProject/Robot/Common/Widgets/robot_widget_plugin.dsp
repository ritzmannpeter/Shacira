# Microsoft Developer Studio Project File - Name="RobotWidgets" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RobotWidgets - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "robot_widget_plugin.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "robot_widget_plugin.mak" CFG="RobotWidgets - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "RobotWidgets - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RobotWidgets - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RobotWidgets - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /O1 /I "tmp\moc\release_mt_shared\\" /I "$(QTDIR)\mkspecs\win32-msvc" /I "." /I ".\include" /I "$(SHACIRADIR)\src" /I "$(SHACIRADIR)\src\Include" /I "$(SHACIRADIR)\Src\System" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\\Extern\ECL\src" /I "$(SHACIRADIR)\Src" /I "Generated" /I ".\\" /I "..\Src" /I "Src" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Generated" /I "$(QTDIR)\tools\designer\interfaces" /I "$(QTDIR)\include" /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_NO_STL" /D "QT_DLL" /D "QT_PLUGIN" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D "QT_ACCESSIBILITY_SUPPORT" /D "QT_NO_DEBUG" /FD -Zm200 /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winmm.lib winspool.lib opengl32.lib glu32.lib /nologo /dll /machine:IX86 /out:"Release\robotwidgets.dll" /libpath:"$(SHACIRADIR)\Extern\Stl\Lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Plugin ins Qt-Verzeichnis
PostBuild_Cmds=copy Release\robotwidgets.dll $(QTDIR)\plugins\designer	copy Release\robotwidgets.exp $(QTDIR)\plugins\designer
# End Special Build Tool

!ELSEIF  "$(CFG)" == "RobotWidgets - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Src" /I "Generated" /I ".\\" /I "..\Src" /I "Src" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Generated" /I "$(QTDIR)\tools\designer\interfaces" /I "$(QTDIR)\include" /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_NO_STL" /D "QT_DLL" /D "QT_PLUGIN" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D "QT_ACCESSIBILITY_SUPPORT" /D "QT_LICENSE_PROFESSIONAL" /D "_ROBOT_WIDGET_PLUGIN_" /FR /FD /GZ -Zm200 /c
# SUBTRACT CPP /X
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winmm.lib winspool.lib opengl32.lib glu32.lib /nologo /dll /debug /machine:IX86 /out:"debug\robotwidgets.dll" /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\Stl\Lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere DEBUG-VERSION des Plugin ins Qt-Verzeichnis
PostBuild_Cmds=copy Debug\robotwidgets.dll $(QTDIR)\plugins\designer	copy Debug\robotwidgets.exp $(QTDIR)\plugins\designer
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "RobotWidgets - Win32 Release"
# Name "RobotWidgets - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cQtPluginRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\cQtPluginRegistry.h
# End Source File
# Begin Source File

SOURCE=.\default_icon.h
# End Source File
# Begin Source File

SOURCE=.\embedded_images.h
# End Source File
# Begin Source File

SOURCE=.\FrameworkPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameworkPlugin.h
# End Source File
# Begin Source File

SOURCE=.\plugin_icons.h
# End Source File
# Begin Source File

SOURCE=.\plugin_log.cpp
# End Source File
# Begin Source File

SOURCE=.\plugin_log.h
# End Source File
# Begin Source File

SOURCE=.\RobotCurves.cpp
# End Source File
# Begin Source File

SOURCE=.\RobotWidgetPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\RobotWidgetPlugin.h
# End Source File
# End Group
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Generated\moc_RobotCurves.cpp
# End Source File
# End Group
# Begin Group "Pictures"

# PROP Default_Filter "bmp"
# End Group
# Begin Group "CWidgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CCoordSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Src\GUIFramework\QT3Framework\CWidgets\cPaintUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Src\GUIFramework\QT3Framework\CWidgets\CWidgetBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CCoordSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\Src\GUIFramework\QT3Framework\Generated\moc_CWidget.cpp
# End Source File
# End Group
# Begin Group "Preprocessor files"

# PROP Default_Filter "pp"
# Begin Source File

SOURCE=.\RobotCurves.pp

!IF  "$(CFG)" == "RobotWidgets - Win32 Release"

# Begin Custom Build
InputDir=.
InputPath=.\RobotCurves.pp
InputName=RobotCurves

BuildCmds= \
	pp -f$(SHACIRADIR)\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "RobotWidgets - Win32 Debug"

# Begin Custom Build
InputDir=.
InputPath=.\RobotCurves.pp
InputName=RobotCurves

BuildCmds= \
	pp -f$(SHACIRADIR)\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
