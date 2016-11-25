# Microsoft Developer Studio Project File - Name="DemoWidgets" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DemoWidgets - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "demo_widget_plugin.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "demo_widget_plugin.mak" CFG="DemoWidgets - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "DemoWidgets - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DemoWidgets - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DemoWidgets - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /O1 /I "..\..\Init" /I "Src\Generated" /I ".\\" /I "$(SHACIRADIR)\Src" /I "Src" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated" /I ".\Forms\Generated" /I "$(QTDIR)\tools\designer\interfaces" /I "$(QTDIR)\include" /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_NO_STL" /D "QT_DLL" /D "QT_PLUGIN" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D "QT_ACCESSIBILITY_SUPPORT" /D "QT_NO_DEBUG" /FD -Zm200 /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winmm.lib winspool.lib opengl32.lib glu32.lib /nologo /dll /machine:IX86 /out:"Release\demowidgets.dll" /libpath:"$(SHACIRADIR)\Extern\Stl\Lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere Plugin ins Qt-Verzeichnis
PostBuild_Cmds=copy Release\demowidgets.dll $(QTDIR)\plugins\designer	copy Release\demowidgets.exp $(QTDIR)\plugins\designer
# End Special Build Tool

!ELSEIF  "$(CFG)" == "DemoWidgets - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\Init" /I "Src\Generated" /I ".\\" /I "$(SHACIRADIR)\Src" /I "Src" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated" /I ".\Forms\Generated" /I "$(QTDIR)\tools\designer\interfaces" /I "$(QTDIR)\include" /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_NO_STL" /D "QT_DLL" /D "QT_PLUGIN" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D "QT_ACCESSIBILITY_SUPPORT" /D "QT_LICENSE_PROFESSIONAL" /FR /FD /GZ -Zm200 /c
# SUBTRACT CPP /X
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winmm.lib winspool.lib opengl32.lib glu32.lib /nologo /dll /debug /machine:IX86 /out:"debug\demowidgets.dll" /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\Stl\Lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere DEBUG-VERSION des Plugin ins Qt-Verzeichnis
PostBuild_Cmds=copy Debug\demowidgets.dll $(QTDIR)\plugins\designer	copy Debug\demowidgets.exp $(QTDIR)\plugins\designer
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "DemoWidgets - Win32 Release"
# Name "DemoWidgets - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Src\dactvalue.cpp

!IF  "$(CFG)" == "DemoWidgets - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "DemoWidgets - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\dframe.cpp

!IF  "$(CFG)" == "DemoWidgets - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "DemoWidgets - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Plugin\dplugin.cpp
# End Source File
# End Group
# Begin Group "Preprocessor files"

# PROP Default_Filter "pp"
# Begin Source File

SOURCE=.\Src\dactvalue.pp

!IF  "$(CFG)" == "DemoWidgets - Win32 Release"

# Begin Custom Build
InputDir=.\Src
InputPath=.\Src\dactvalue.pp
InputName=dactvalue

BuildCmds= \
	pp -f$(SHACIRADIR)\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DemoWidgets - Win32 Debug"

# Begin Custom Build
InputDir=.\Src
InputPath=.\Src\dactvalue.pp
InputName=dactvalue

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
# Begin Source File

SOURCE=.\Src\dframe.pp

!IF  "$(CFG)" == "DemoWidgets - Win32 Release"

# Begin Custom Build
InputDir=.\Src
InputPath=.\Src\dframe.pp
InputName=dframe

BuildCmds= \
	pp -f$(SHACIRADIR)\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DemoWidgets - Win32 Debug"

# Begin Custom Build
InputDir=.\Src
InputPath=.\Src\dframe.pp
InputName=dframe

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
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\Generated\dactvalue.h
# End Source File
# Begin Source File

SOURCE=.\Src\Generated\dframe.h
# End Source File
# Begin Source File

SOURCE=.\Src\Generated\moc_dactvalue.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\Generated\moc_dframe.cpp
# End Source File
# End Group
# Begin Group "CWidgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cactvalue.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\calarmwidget.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cappframe.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cbuttongroup.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ccheckbox.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ccombobox.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ccomplistview.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ccomposedstack.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ccoordsystem.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cdirectory.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cfixtext.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cframe.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cgraphic.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cgroupbox.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cgroupselectbutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cguievents.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cindreqvalue.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cinfolabel.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cinput.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\clistview.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cpage.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cpaintutils.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cprocgraphic.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cpushbutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cradiobutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\creqvalue.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cringgraphic.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\crubberband.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cscrollbar.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\csimplegraphic.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cstartupform.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cstatebutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ctable.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ctabwidget.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ctextedit.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\ctoolbutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cvardimension.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cvideo.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cvirtualkeyboard.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cwidget.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cwidgetbase.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cwidgetcomm.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cwidgethelper.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\cwidgetstack.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cactvalue.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_calarmwidget.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cappframe.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cbuttongroup.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccheckbox.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccombobox.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccomplistview.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccomposedstack.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccoordsystem.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cdirectory.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cfixtext.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cframe.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cGraphic.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cgroupbox.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cgroupselectbutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cindreqvalue.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cinfolabel.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_clistview.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cpage.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cprocgraphic.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cpushbutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cradiobutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_creqvalue.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cringgraphic.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cscrollbar.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_csimplegraphic.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cstartupform.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cstatebutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctable.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctabwidget.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctextedit.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctoolbutton.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cvardimension.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cvideo.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cvirtualkeyboard.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cwidget.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cwidgetcomm.cpp"
# End Source File
# Begin Source File

SOURCE="$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cwidgetstack.cpp"
# End Source File
# End Group
# End Target
# End Project
