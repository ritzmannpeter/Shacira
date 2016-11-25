# Microsoft Developer Studio Project File - Name="Memview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Memview - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "sh_app_memview.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "sh_app_memview.mak" CFG="Memview - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Memview - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Memview - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Memview - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /I "$(QTDIR)\include" /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/memview.exe" /libpath:"..\..\..\Extern\STL\lib"

!ELSEIF  "$(CFG)" == "Memview - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "$(QTDIR)\include" /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/memviewd.exe" /pdbtype:sept /libpath:"..\..\..\Extern\STL\lib"
# SUBTRACT LINK32 /force
# Begin Special Build Tool
TargetPath=.\Debug\memviewd.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Memview - Win32 Release"
# Name "Memview - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Forms_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\memory.cpp
# End Source File
# Begin Source File

SOURCE=.\memory.h
# End Source File
# Begin Source File

SOURCE=.\memviewimpl.cpp
# End Source File
# Begin Source File

SOURCE=.\memviewimpl.h

!IF  "$(CFG)" == "Memview - Win32 Release"

# Begin Custom Build
InputDir=.
InputPath=.\memviewimpl.h
InputName=memviewimpl

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "Memview - Win32 Debug"

# Begin Custom Build
InputDir=.
InputPath=.\memviewimpl.h
InputName=memviewimpl

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Forms"

# PROP Default_Filter ""
# Begin Group "Generated_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Generated\memview.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\memview.h
# End Source File
# Begin Source File

SOURCE=.\Generated\moc_memview.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\moc_memviewimpl.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\memview.ui

!IF  "$(CFG)" == "Memview - Win32 Release"

# Begin Custom Build
InputDir=.
InputPath=.\memview.ui
InputName=memview

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

!ELSEIF  "$(CFG)" == "Memview - Win32 Debug"

# Begin Custom Build
InputDir=.
InputPath=.\memview.ui
InputName=memview

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
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
