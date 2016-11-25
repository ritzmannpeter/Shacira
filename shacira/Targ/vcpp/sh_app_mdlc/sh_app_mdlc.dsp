# Microsoft Developer Studio Project File - Name="sh_app_mdlc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=sh_app_mdlc - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "sh_app_mdlc.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "sh_app_mdlc.mak" CFG="sh_app_mdlc - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "sh_app_mdlc - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "sh_app_mdlc - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sh_app_mdlc - Win32 Release"

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
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Extern\OPC\src\OPCInterface" /I "..\..\..\Extern\OPC\src\OPCInterface\Include" /I "..\..\..\Src\System" /I "..\..\..\Src\CellControl\SerialChannel\Base" /I "..\..\..\Src\CellControl\DigitalChannel\AddiData\Base" /I "..\..\..\Src\Orb" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /D "_NO_QT_" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 xerces-c_3.lib addidata.lib omnithread$(ORBTHREADVERSION)_rt.lib omniORB$(ORBVERSION)_rt.lib omniDynamic$(ORBVERSION)_rt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /map /machine:I386 /out:"Release/mdlc.exe" /libpath:"$(ORBDIR)\lib\x86_win32" /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\ADDIDATA\lib" /libpath:"..\..\..\Extern\FALCON\lib" /libpath:"..\..\..\Extern\XERCES\lib\vc6"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Release\mdlc.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "sh_app_mdlc - Win32 Debug"

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
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Extern\OPC\src\OPCInterface" /I "..\..\..\Extern\OPC\src\OPCInterface\Include" /I "..\..\..\Src\System" /I "..\..\..\Src\CellControl\SerialChannel\Base" /I "..\..\..\Src\CellControl\DigitalChannel\AddiData\Base" /I "..\..\..\Src\Orb" /I "..\..\..\Extern\ECL\src" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /D "_NO_QT_" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xerces-c_3D.lib addidata.lib omnithread$(ORBTHREADVERSION)_rtd.lib omniORB$(ORBVERSION)_rtd.lib omniDynamic$(ORBVERSION)_rtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /incremental:no /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /force /out:"Debug/mdlc.exe" /pdbtype:sept /libpath:"$(ORBDIR)\lib\x86_win32" /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\ADDIDATA\lib" /libpath:"..\..\..\Extern\FALCON\lib" /libpath:"..\..\..\Extern\XERCES\lib\vc6"
# SUBTRACT LINK32 /profile /pdb:none
# Begin Special Build Tool
TargetPath=.\Debug\mdlc.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "sh_app_mdlc - Win32 Release"
# Name "sh_app_mdlc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\Src\Tools\mdlc\mdlc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
