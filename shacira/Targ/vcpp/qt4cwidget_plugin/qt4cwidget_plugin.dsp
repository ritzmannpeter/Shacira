# Microsoft Developer Studio Project File - Name="QT4CWidgets" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=QT4CWidgets - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "qt4cwidget_plugin.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "qt4cwidget_plugin.mak" CFG="QT4CWidgets - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "QT4CWidgets - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "QT4CWidgets - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QT4CWidgets - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /O1 /I "$(QTDIR)\include" /I "$(QTDIR)\include\QtCore" /I "$(QTDIR)\include\QtGUI" /I "$(QTDIR)\include\Qt3Support" /I "$(QTDIR)\include\Qt" /I "..\..\..\Src" /I "..\..\..\Src\Orb" /I "..\..\..\Src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Src\GUIFramework\QT4Framework\CWidgets" /I "..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\Interface" /I "..\..\..\Src\GUIFramework\QT4Framework" /I "..\..\..\Src\GUIFramework\QT4Framework\keypads" /I "..\..\..\Src\GUIFramework\QT4Framework\dialogs" /I "..\..\..\Src\GUIFramework\QT4Framework\dialogs\generated" /I "..\..\..\Src\GUIFramework\QT4Framework\keypads\generated" /D "NDEBUG" /D "QT_NO_DEBUG" /D "QT_LICENSE_PROFESSIONAL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_NO_STL" /D "QT_DLL" /D "QT_PLUGIN" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D "QT_ACCESSIBILITY_SUPPORT" /D "QT3_SUPPORT" /FD -Zm200 /c
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winmm.lib winspool.lib opengl32.lib glu32.lib /nologo /dll /machine:IX86 /out:"Release\qt4cwidgets.dll" /libpath:"..\..\..\Extern\Stl\Lib" /libpath:"..\..\..\Extern\Drv\AddiData\x86_win32"

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /I "$(QTDIR)\include\QtCore" /I "$(QTDIR)\include\QtGUI" /I "$(QTDIR)\include\Qt3Support" /I "$(QTDIR)\include\Qt" /I "..\..\..\Src" /I "..\..\..\Src\Orb" /I "..\..\..\Src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Src\GUIFramework\QT4Framework\CWidgets" /I "..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\Interface" /I "..\..\..\Src\GUIFramework\QT4Framework" /I "..\..\..\Src\GUIFramework\QT4Framework\keypads" /I "..\..\..\Src\GUIFramework\QT4Framework\dialogs" /I "..\..\..\Src\GUIFramework\QT4Framework\dialogs\generated" /I "..\..\..\Src\GUIFramework\QT4Framework\keypads\generated" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QT_NO_STL" /D "QT_DLL" /D "QT_PLUGIN" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D "QT_ACCESSIBILITY_SUPPORT" /D "QT3_SUPPORT" /FD /GZ -Zm200 /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winmm.lib winspool.lib opengl32.lib glu32.lib /nologo /dll /debug /machine:IX86 /out:"debug\qt4cwidgets.dll" /pdbtype:sept /libpath:"..\..\..\Extern\Stl\Lib" /libpath:"..\..\..\Extern\Drv\AddiData\x86_win32"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Kopiere DEBUG-VERSION des Plugin ins Qt-Verzeichnis
PostBuild_Cmds=copy Debug\qt4cwidgets.dll $(QTDIR)\plugins\designer	copy Debug\qt4cwidgets.exp $(QTDIR)\plugins\designer
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "CWidgets - Win32 Release"
# Name "CWidgets - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cactiondialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cactvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\calarmwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cappframe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cbuttongroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccheckbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccombobox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccomplistview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccomposedstack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccoordsystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdatetime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cfixtext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cframe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgroupbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgroupselectbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cguievents.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cindreqvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cinfolabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cinput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\clistview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpaintutils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cprocgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cprogressbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpushbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cradiobutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\creqvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cringgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\crubberband.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cscrollbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\csimplegraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cslider.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cspinbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cstartupform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cstatebutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctabwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctextedit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctoolbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvardimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvideo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvirtualkeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetcomm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgethelper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetstack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\plugin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\pluginlog.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cactiondialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cactvalue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\calarmwidget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cappframe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cbuttongroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ccheckbox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ccombobox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ccomplistview.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ccomposedstack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ccoordsystem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cdate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cdatetime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cdirectory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cfixtext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cframe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cGraphic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cgroupbox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cgroupselectbutton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cindreqvalue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cinfolabel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\clistview.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cpage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cprocgraphic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cprogressbar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cpushbutton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cradiobutton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\creqvalue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cringgraphic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cscrollbar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\csimplegraphic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cslider.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cspinbox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cstartupform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cstatebutton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ctable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ctabwidget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ctextedit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ctime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\ctoolbutton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cvardimension.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cvideo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cvirtualkeyboard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cwidget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\cwidgetstack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cactiondialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cactvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_calarmwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cappframe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cbuttongroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ccheckbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ccombobox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ccomplistview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ccomposedstack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ccoordsystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cdate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cdatetime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cdirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cfixtext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cframe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cgroupbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cgroupselectbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cindreqvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cinfolabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_clistview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cpage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cprocgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cprogressbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cpushbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cradiobutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_creqvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cringgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cscrollbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_csimplegraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cslider.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cspinbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cstartupform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cstatebutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ctable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ctabwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ctextedit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ctime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_ctoolbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cvardimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cvideo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cvirtualkeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cwidgetcomm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Generated\moc_cwidgetstack.cpp
# End Source File
# End Group
# Begin Group "Pictures"

# PROP Default_Filter "bmp"
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\cactvalue.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\ccheckbox.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\cfixtext.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\cframe.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\charpushbutton.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\cpage.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\cpushbutton.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\cradiobutton.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\creqvalue.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\ctabwidget.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\ctoolbutton.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\Plugin\Images\embedded_images.h
# End Source File
# End Group
# Begin Group "Preprocessor files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cactiondialog.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cactiondialog.pp
InputName=cactiondialog

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cactiondialog.pp
InputName=cactiondialog

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cactvalue.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cactvalue.pp
InputName=cactvalue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cactvalue.pp
InputName=cactvalue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\calarmwidget.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\calarmwidget.pp
InputName=calarmwidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\calarmwidget.pp
InputName=calarmwidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cappframe.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cappframe.pp
InputName=cappframe

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cappframe.pp
InputName=cappframe

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cbuttongroup.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cbuttongroup.pp
InputName=cbuttongroup

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cbuttongroup.pp
InputName=cbuttongroup

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccheckbox.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccheckbox.pp
InputName=ccheckbox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccheckbox.pp
InputName=ccheckbox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccombobox.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccombobox.pp
InputName=ccombobox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccombobox.pp
InputName=ccombobox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccomplistview.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccomplistview.pp
InputName=ccomplistview

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccomplistview.pp
InputName=ccomplistview

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccomposedstack.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccomposedstack.pp
InputName=ccomposedstack

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccomposedstack.pp
InputName=ccomposedstack

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccoordsystem.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccoordsystem.pp
InputName=ccoordsystem

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ccoordsystem.pp
InputName=ccoordsystem

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdate.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdate.pp
InputName=cdate

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdate.pp
InputName=cdate

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdatetime.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdatetime.pp
InputName=cdatetime

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdatetime.pp
InputName=cdatetime

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdirectory.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdirectory.pp
InputName=cdirectory

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cdirectory.pp
InputName=cdirectory

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cfixtext.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cfixtext.pp
InputName=cfixtext

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cfixtext.pp
InputName=cfixtext

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cframe.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cframe.pp
InputName=cframe

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cframe.pp
InputName=cframe

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cGraphic.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cGraphic.pp
InputName=cGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cGraphic.pp
InputName=cGraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgroupbox.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgroupbox.pp
InputName=cgroupbox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgroupbox.pp
InputName=cgroupbox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgroupselectbutton.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgroupselectbutton.pp
InputName=cgroupselectbutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cgroupselectbutton.pp
InputName=cgroupselectbutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cindreqvalue.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cindreqvalue.pp
InputName=cindreqvalue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cindreqvalue.pp
InputName=cindreqvalue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cinfolabel.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cinfolabel.pp
InputName=cinfolabel

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cinfolabel.pp
InputName=cinfolabel

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\clistview.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\clistview.pp
InputName=clistview

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\clistview.pp
InputName=clistview

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpage.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpage.pp
InputName=cpage

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpage.pp
InputName=cpage

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cprocgraphic.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cprocgraphic.pp
InputName=cprocgraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cprocgraphic.pp
InputName=cprocgraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cprogressbar.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cprogressbar.pp
InputName=cprogressbar

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cprogressbar.pp
InputName=cprogressbar

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpushbutton.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpushbutton.pp
InputName=cpushbutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpushbutton.pp
InputName=cpushbutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cradiobutton.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cradiobutton.pp
InputName=cradiobutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cradiobutton.pp
InputName=cradiobutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\creqvalue.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\creqvalue.pp
InputName=creqvalue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\creqvalue.pp
InputName=creqvalue

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cringgraphic.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cringgraphic.pp
InputName=cringgraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cringgraphic.pp
InputName=cringgraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cscrollbar.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cscrollbar.pp
InputName=cscrollbar

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cscrollbar.pp
InputName=cscrollbar

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\csimplegraphic.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\csimplegraphic.pp
InputName=csimplegraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\csimplegraphic.pp
InputName=csimplegraphic

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cslider.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cslider.pp
InputName=cslider

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cslider.pp
InputName=cslider

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cspinbox.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cspinbox.pp
InputName=cspinbox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cspinbox.pp
InputName=cspinbox

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cstartupform.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cstartupform.pp
InputName=cstartupform

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cstartupform.pp
InputName=cstartupform

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cstatebutton.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cstatebutton.pp
InputName=cstatebutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cstatebutton.pp
InputName=cstatebutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctable.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctable.pp
InputName=ctable

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctable.pp
InputName=ctable

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctabwidget.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctabwidget.pp
InputName=ctabwidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctabwidget.pp
InputName=ctabwidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctextedit.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctextedit.pp
InputName=ctextedit

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctextedit.pp
InputName=ctextedit

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctime.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctime.pp
InputName=ctime

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctime.pp
InputName=ctime

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctoolbutton.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctoolbutton.pp
InputName=ctoolbutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\ctoolbutton.pp
InputName=ctoolbutton

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvardimension.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvardimension.pp
InputName=cvardimension

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvardimension.pp
InputName=cvardimension

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvideo.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvideo.pp
InputName=cvideo

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvideo.pp
InputName=cvideo

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvirtualkeyboard.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvirtualkeyboard.pp
InputName=cvirtualkeyboard

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cvirtualkeyboard.pp
InputName=cvirtualkeyboard

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidget.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidget.pp
InputName=cwidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidget.pp
InputName=cwidget

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetstack.pp

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetstack.pp
InputName=cwidgetstack

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetstack.pp
InputName=cwidgetstack

BuildCmds= \
	..\..\..\bin\win32\pp.exe -f..\..\..\bin\win32\ppQt.pre -o$(InputDir)\Generated\$(InputName).h $(InputPath) \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Header files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\casyncfunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cguievents.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cinput.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cpaintutils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\crubberband.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetbase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetcomm.h

!IF  "$(CFG)" == "CWidgets - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetcomm.h
InputName=cwidgetcomm

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputPath) -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CWidgets - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QT4Framework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgetcomm.h
InputName=cwidgetcomm

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputPath) -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\cwidgethelper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\guiops.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QT4Framework\CWidgets\guisignals.h
# End Source File
# End Group
# End Target
# End Project
