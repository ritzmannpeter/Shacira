# Microsoft Developer Studio Project File - Name="DatasetViewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DatasetViewer - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "DatasetViewer.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "DatasetViewer.mak" CFG="DatasetViewer - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "DatasetViewer - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "DatasetViewer - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DatasetViewer - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "$(QTDIR)\include" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\ECL\src" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework" /I "$(SHACIRADIR)\Src\GUIFramework\Interface" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated" /I "Forms\Generated" /I "Forms" /I "Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread2_rt.lib omniORB304_rt.lib omniDynamic304_rt.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib"
# Begin Special Build Tool
TargetPath=.\Release\DatasetViewer.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) Viewer
# End Special Build Tool

!ELSEIF  "$(CFG)" == "DatasetViewer - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "$(QTDIR)\include" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\ECL\src" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework" /I "$(SHACIRADIR)\Src\GUIFramework\Interface" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated" /I "Forms\Generated" /I "Forms" /I "Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread2_rtd.lib omniORB304_rtd.lib omniDynamic304_rtd.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/DatasetViewerd.exe" /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib" /libpath:"$(SHACIRADIR)\Extern\STL\lib"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "DatasetViewer - Win32 Release"
# Name "DatasetViewer - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Conversion"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Conversion\cEM17Data.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cEM17Data.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cFMFatFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cFMFatFile.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cFMTestHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cFMTestHandler.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cHeader.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cHeatGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cHeatGroup.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cHeatText.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cHeatText.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cHeatZone.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cHeatZone.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cNewProcessGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cNewProcessGraphic.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cPositionedBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cPositionedBuffer.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cProcessGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cProcessGraphic.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cRegister.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cSubfile.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cSubfile.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cTextVar.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cTextVar.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\cTransformationHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\Conversion\cTransformationHandler.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\FileDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\FileObjects.h
# End Source File
# End Group
# Begin Group "Forms"

# PROP Default_Filter ""
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\View\Generated\DatasetViewerForm.cpp
# End Source File
# Begin Source File

SOURCE=.\View\Generated\DatasetViewerForm.h
# End Source File
# Begin Source File

SOURCE=.\View\Generated\moc_coutput.cpp
# End Source File
# Begin Source File

SOURCE=.\View\Generated\moc_csubfilelist.cpp
# End Source File
# Begin Source File

SOURCE=.\View\Generated\moc_DatasetViewerForm.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\View\coutput.cpp
# End Source File
# Begin Source File

SOURCE=.\View\coutput.h

!IF  "$(CFG)" == "DatasetViewer - Win32 Release"

# Begin Custom Build
InputDir=.\View
InputPath=.\View\coutput.h
InputName=coutput

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "DatasetViewer - Win32 Debug"

# Begin Custom Build
InputDir=.\View
InputPath=.\View\coutput.h
InputName=coutput

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\View\cregdescription.cpp
# End Source File
# Begin Source File

SOURCE=.\View\cregdescription.h
# End Source File
# Begin Source File

SOURCE=.\View\csubfilelist.cpp
# End Source File
# Begin Source File

SOURCE=.\View\csubfilelist.h

!IF  "$(CFG)" == "DatasetViewer - Win32 Release"

# Begin Custom Build
InputDir=.\View
InputPath=.\View\csubfilelist.h
InputName=csubfilelist

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "DatasetViewer - Win32 Debug"

# Begin Custom Build
InputDir=.\View
InputPath=.\View\csubfilelist.h
InputName=csubfilelist

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\View\DatasetViewerForm.ui

!IF  "$(CFG)" == "DatasetViewer - Win32 Release"

# Begin Custom Build
InputDir=.\View
InputPath=.\View\DatasetViewerForm.ui
InputName=DatasetViewerForm

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DatasetViewer - Win32 Debug"

# Begin Custom Build
InputDir=.\View
InputPath=.\View\DatasetViewerForm.ui
InputName=DatasetViewerForm

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "legacy_headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Conversion\iqtbit.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\iqtreg.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\iscosbit.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\iscosreg.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\ktabs.c.doc
# End Source File
# Begin Source File

SOURCE=.\Conversion\robreg.h
# End Source File
# Begin Source File

SOURCE=.\Conversion\textvar.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\View\DatasetViewer.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\IQT\iqtheaders\dsglobal.h
# End Source File
# Begin Source File

SOURCE=.\IQT\iqtheaders\syntax.h
# End Source File
# Begin Source File

SOURCE=.\IQT\iqtheaders\tasks.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
