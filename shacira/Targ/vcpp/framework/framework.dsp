# Microsoft Developer Studio Project File - Name="framework" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=framework - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "framework.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "framework.mak" CFG="framework - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "framework - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "framework - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "framework - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(QTDIR)\include" /I "..\..\..\Src" /I "..\..\..\Src\Orb" /I "..\..\..\Src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Src\GUIFramework\QTFramework\CWidgets" /I "..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\Interface" /I "..\..\..\Src\GUIFramework\QTFramework" /I "..\..\..\Src\GUIFramework\QTFramework\keypads" /I "..\..\..\Src\GUIFramework\QTFramework\dialogs" /I "..\..\..\Src\GUIFramework\QTFramework\dialogs\generated" /I "..\..\..\Src\GUIFramework\QTFramework\keypads\generated" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "__x86__" /D "__WIN32__" /D "__OMNIORB4__" /D "_COS_LIBRARY" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

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
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /I "..\..\..\Src" /I "..\..\..\Src\Orb" /I "..\..\..\Src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Src\GUIFramework\QTFramework\CWidgets" /I "..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\Interface" /I "..\..\..\Src\GUIFramework\QTFramework" /I "..\..\..\Src\GUIFramework\QTFramework\keypads" /I "..\..\..\Src\GUIFramework\QTFramework\dialogs" /I "..\..\..\Src\GUIFramework\QTFramework\dialogs\generated" /I "..\..\..\Src\GUIFramework\QTFramework\keypads\generated" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__x86__" /D "__WIN32__" /D "__OMNIORB4__" /D "_COS_LIBRARY" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\frameworkd.lib"

!ENDIF 

# Begin Target

# Name "framework - Win32 Release"
# Name "framework - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Interface_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\Interface\cCCSInterface.cpp
# End Source File
# End Group
# Begin Group "GUIFramework_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cGroupList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cNodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cUserInterface.cpp
# End Source File
# End Group
# Begin Group "QTFramework_c"

# PROP Default_Filter ""
# Begin Group "HTML"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\HTML\cFormRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\HTML\cFormRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\HTML\cHTMLDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\HTML\cHTMLDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\HTML\cHTMLElement.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\HTML\cHTMLElement.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\Interface\cContextChooser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\Interface\cContextChooser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cContextExplorer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cContextExplorer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cguithread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cguithread.h

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework
InputPath=..\..\..\Src\GUIFramework\QTFramework\cguithread.h
InputName=cguithread

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework
InputPath=..\..\..\Src\GUIFramework\QTFramework\cguithread.h
InputName=cguithread

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cHelpInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cHelpInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cQTUserInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cSyncView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cSyncView.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\generated\moc_cguithread.cpp
# End Source File
# End Group
# Begin Group "CWidgets_c"

# PROP Default_Filter ""
# Begin Group "Generated_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cactiondialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cactvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_calarmwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cappframe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cbuttongroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccheckbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccombobox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccomplistview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccomposedstack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ccoordsystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cdate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cdatetime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cdirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cfixtext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cframe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cGroupBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cgroupselectbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cindreqvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cinfolabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_clistview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cpage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cprocgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cprogressbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cpublicdialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cpushbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cradiobutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_creqvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cringgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cscrollbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_csimplegraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cslider.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cspinbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cstartupform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cstatebutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctabwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctextedit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_ctoolbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cvardimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cvideo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cvirtualkeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cWidgetComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\Generated\moc_cwidgetstack.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cactiondialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cactvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\calarmwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cappframe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\casyncfunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cbuttongroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ccheckbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ccombobox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ccomplistview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ccomposedstack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ccoordsystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cdate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cdatetime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cdirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cfixtext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cframe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cgroupbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cgroupselectbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cguievents.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cindreqvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cinfolabel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cinput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\clistview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cpage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cpaintutils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cprocgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cprogressbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cpushbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cradiobutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\creqvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cringgraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\crubberband.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cscrollbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\csignalmanager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\csimplegraphic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cslider.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cspinbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cstartupform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cstatebutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ctable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ctabwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ctextedit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ctime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\ctoolbutton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cvardimension.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cvideo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cvirtualkeyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cwidget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cwidgetbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cWidgetComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cwidgethelper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cwidgetstack.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "GUIFramework_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cGroupList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\cNodeList.h
# End Source File
# End Group
# Begin Group "QTFramework_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\cQTUserInterface.h
# End Source File
# End Group
# Begin Group "Interface_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\Interface\cCCSInterface.h
# End Source File
# End Group
# Begin Group "CWidgets_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cinput.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cpublicdialog.h

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cpublicdialog.h
InputName=cpublicdialog

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputPath) -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\CWidgets
InputPath=..\..\..\Src\GUIFramework\QTFramework\CWidgets\cpublicdialog.h
InputName=cpublicdialog

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputPath) -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\CWidgets\csignalmanager.h
# End Source File
# End Group
# End Group
# Begin Group "keypads"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\cQtKeyboardAlpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\cQtKeyboardAlpha.h

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\cQtKeyboardAlpha.h
InputName=cQtKeyboardAlpha

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\cQtKeyboardAlpha.h
InputName=cQtKeyboardAlpha

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\cQtKeypadNumeric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\cQtKeypadNumeric.h

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\cQtKeypadNumeric.h
InputName=cQtKeypadNumeric

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\cQtKeypadNumeric.h
InputName=cQtKeypadNumeric

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\property_interface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h
InputName=qt_keyboard

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
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
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h

!IF  "$(CFG)" == "framework - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_button.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h
InputName=qt_keyboard_button

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

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

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.h

!IF  "$(CFG)" == "framework - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_input.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.h
InputName=qt_keyboard_input

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_input.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.h
InputName=qt_keyboard_input

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h

!IF  "$(CFG)" == "framework - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_layout.h...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h
InputName=qt_keyboard_layout

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

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

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
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

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
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

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
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

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
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
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.ui

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.ui
InputName=qt_keyboardalpha

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

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.ui
InputName=qt_keyboardalpha

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

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.ui

!IF  "$(CFG)" == "framework - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keypadnumeric.ui...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.ui
InputName=qt_keypadnumeric

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

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keypadnumeric.ui...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.ui
InputName=qt_keypadnumeric

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

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_number_validator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_number_validator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_property_widget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_property_widget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_string_validator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_string_validator.h
# End Source File
# End Group
# Begin Group "generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Dialogs\generated\ContextExplorer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Dialogs\generated\moc_ContextExplorer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Dialogs\generated\moc_ContextExplorerDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_cQtKeyboardAlpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_cQtKeypadNumeric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_input.cpp
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

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboardalpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keypadnumeric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Styles\generated\moc_touch_style.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\qt_keyboard_layout_german.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\qt_keyboard_layout_standard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\qt_keyboardalpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\qt_keypadnumeric.cpp
# End Source File
# End Group
# Begin Group "Dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Dialogs\ContextExplorer.ui

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Dialogs
InputPath=..\..\..\Src\GUIFramework\QTFramework\Dialogs\ContextExplorer.ui
InputName=ContextExplorer

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

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Dialogs
InputPath=..\..\..\Src\GUIFramework\QTFramework\Dialogs\ContextExplorer.ui
InputName=ContextExplorer

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

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Dialogs\ContextExplorerDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Dialogs\ContextExplorerDialog.h

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Dialogs
InputPath=..\..\..\Src\GUIFramework\QTFramework\Dialogs\ContextExplorerDialog.h
InputName=ContextExplorerDialog

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Dialogs
InputPath=..\..\..\Src\GUIFramework\QTFramework\Dialogs\ContextExplorerDialog.h
InputName=ContextExplorerDialog

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Dialogs\qt_navigation_widget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Dialogs\qt_navigation_widget.h
# End Source File
# End Group
# Begin Group "styles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Styles\touch_style.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Styles\touch_style.h

!IF  "$(CFG)" == "framework - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Styles
InputPath=..\..\..\Src\GUIFramework\QTFramework\Styles\touch_style.h
InputName=touch_style

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "framework - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\Styles
InputPath=..\..\..\Src\GUIFramework\QTFramework\Styles\touch_style.h
InputName=touch_style

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
