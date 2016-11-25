# Microsoft Developer Studio Project File - Name="PPCServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=PPCServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PPCServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PPCServer.mak" CFG="PPCServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PPCServer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "PPCServer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PPCServer - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Extern\OPC\src\OPCInterface" /I "..\..\..\Extern\OPC\src\OPCInterface\Include" /I "..\..\..\Src\System" /I "..\..\..\Src\CellControl\SerialChannel\Base" /I "..\..\..\Src\CellControl\DigitalChannel\AddiData\Base" /I "..\..\..\Src\Orb" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\src" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /D "__x86__" /D "_OCS_TRACE" /D "__NT__" /D __OSVERSION__=4 /D "__USE_REC__" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 omnithread2_rt.lib omniORB304_rt.lib omniDynamic304_rt.lib addidata.lib pa150.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /map /machine:I386 /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\DRV\AddiData\x86_win32"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Release\PPCServer.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=xcopy /D /Y ..\..\..\Extern\DRV\AddiData\*.dll ..\..\..\Bin\win32	xcopy /D /Y ..\..\..\Extern\STL\lib\*.dll ..\..\..\Bin\win32	xcopy /D /Y $(TargetPath) ..\..\..\Bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PPCServer - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\Src" /I "..\..\Src\Include" /I "..\..\Extern\STL\stlport" /I "..\..\Extern\STL\stlport\old_hp" /I "..\..\Extern\ECL\src" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /D "__x86__" /D "_OCS_TRACE" /D "__NT__" /D __OSVERSION__=4 /D "__USE_REC__" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /pdbtype:sept /libpath:"..\..\Extern\STL\lib" /libpath:"..\..\Extern\DRV\AddiData\x86_win32"
# SUBTRACT LINK32 /profile /pdb:none /force

!ENDIF 

# Begin Target

# Name "PPCServer - Win32 Release"
# Name "PPCServer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cBlockQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cCSAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cCSComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cCSMsg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cInetAddress.cpp
# End Source File
# Begin Source File

SOURCE=.\cIntegration.cpp
# End Source File
# Begin Source File

SOURCE=.\cPPCClient.cpp
# End Source File
# Begin Source File

SOURCE=.\cPPCDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\cPPCServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cUDPComm.cpp
# End Source File
# Begin Source File

SOURCE=.\PPCServer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cCSAddress.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cCSComm.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cCSMsg.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cInetAddress.h
# End Source File
# Begin Source File

SOURCE=.\cPPCServer.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cs.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cServer.h
# End Source File
# Begin Source File

SOURCE=..\..\Src\System\ClientServer\cUDPComm.h
# End Source File
# End Group
# End Target
# End Project
