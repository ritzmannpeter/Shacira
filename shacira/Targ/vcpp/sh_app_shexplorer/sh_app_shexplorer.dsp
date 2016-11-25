# Microsoft Developer Studio Project File - Name="sh_app_shexplorer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=sh_app_shexplorer - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "sh_app_shexplorer.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "sh_app_shexplorer.mak" CFG="sh_app_shexplorer - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "sh_app_shexplorer - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "sh_app_shexplorer - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sh_app_shexplorer - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Src\GUIFramework\Q3TFramework\CWidgets" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Src\GUIFramework\QT3Framework\CWidgets" /I ".\\" /I "$(QTDIR)\include" /I "..\..\..\Src" /I "..\..\..\Src\Orb" /I "..\..\..\Src\Include" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Src\GUIFramework\QT3Framework\Generated" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\Interface" /I "..\..\..\Src\GUIFramework\QT3Framework" /I "..\..\..\Src\GUIFramework\QT3Framework\Plugins" /I "Forms\Generated" /I "..\..\..\Src\Apps\SHExplorer" /I "..\..\..\Src\Apps\SHExplorer\Generated" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /FD /c
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
# ADD LINK32 xerces-c_3.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread$(ORBTHREADVERSION)_rt.lib omniORB$(ORBVERSION)_rt.lib omniDynamic$(ORBVERSION)_rt.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/SHExplorer.exe" /libpath:"$(ORBDIR)\lib\x86_win32" /libpath:"..\..\..\Extern\ADDIDATA\lib" /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\XERCES\lib\vc6"
# Begin Special Build Tool
TargetPath=.\Release\SHExplorer.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "sh_app_shexplorer - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Src\GUIFramework\QT3Framework\CWidgets" /I ".\\" /I "$(QTDIR)\include" /I "..\..\..\Src" /I "..\..\..\Src\Orb" /I "..\..\..\Src\Include" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Src\GUIFramework\QT3Framework\Generated" /I "..\..\..\Src\GUIFramework" /I "..\..\..\Src\GUIFramework\Interface" /I "..\..\..\Src\GUIFramework\QT3Framework" /I "..\..\..\Src\GUIFramework\QT3Framework\Plugins" /I "Forms\Generated" /I "..\..\..\Src\Apps\SHExplorer" /I "..\..\..\Src\Apps\SHExplorer\Generated" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /FD /GZ /c
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
# ADD LINK32 xerces-c_3D.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread$(ORBTHREADVERSION)_rtd.lib omniORB$(ORBVERSION)_rtd.lib omniDynamic$(ORBVERSION)_rtd.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/SHExplorerd.exe" /pdbtype:sept /libpath:"$(ORBDIR)\lib\x86_win32" /libpath:"..\..\..\Extern\ADDIDATA\lib" /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\XERCES\lib\vc6"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
TargetPath=.\Debug\SHExplorerd.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "sh_app_shexplorer - Win32 Release"
# Name "sh_app_shexplorer - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Forms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Apps\SHExplorer\ExplorerForm.ui

!IF  "$(CFG)" == "sh_app_shexplorer - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Apps\SHExplorer
InputPath=..\..\..\Src\Apps\SHExplorer\ExplorerForm.ui
InputName=ExplorerForm

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

!ELSEIF  "$(CFG)" == "sh_app_shexplorer - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Apps\SHExplorer
InputPath=..\..\..\Src\Apps\SHExplorer\ExplorerForm.ui
InputName=ExplorerForm

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
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Apps\SHExplorer\generated\ExplorerForm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\SHExplorer\generated\ExplorerForm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\SHExplorer\generated\moc_CServerList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\SHExplorer\generated\moc_ExplorerForm.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\Apps\SHExplorer\CServerList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\SHExplorer\CServerList.h

!IF  "$(CFG)" == "sh_app_shexplorer - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Apps\SHExplorer
InputPath=..\..\..\Src\Apps\SHExplorer\CServerList.h
InputName=CServerList

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "sh_app_shexplorer - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Apps\SHExplorer
InputPath=..\..\..\Src\Apps\SHExplorer\CServerList.h
InputName=CServerList

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\SHExplorer\SHExplorer.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
