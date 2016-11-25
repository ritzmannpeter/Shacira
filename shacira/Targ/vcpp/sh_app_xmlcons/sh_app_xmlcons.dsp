# Microsoft Developer Studio Project File - Name="sh_app_xmlcons" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=sh_app_xmlcons - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "sh_app_xmlcons.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "sh_app_xmlcons.mak" CFG="sh_app_xmlcons - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "sh_app_xmlcons - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "sh_app_xmlcons - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sh_app_xmlcons - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "SocketApi" /I "Server" /I "..\SocketApi" /I "$(QTDIR)\include" /I "..\..\..\Extern\XERCES\include" /I "..\..\..\Src\Apps\XMLCons\SocketApi" /I "..\..\..\Src\Apps\XMLCons\Server" /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\Src" /I "..\..\..\Src\Orb" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /D "_NO_QT_" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 xerces-c_3.lib omnithread$(ORBTHREADVERSION)_rt.lib omniORB$(ORBVERSION)_rt.lib omniDynamic$(ORBVERSION)_rt.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib addidata.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /map /machine:I386 /out:"Release/xcons.exe" /libpath:"..\..\..\Extern\XERCES\lib\vc6" /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\ADDIDATA\lib" /libpath:"..\..\..\Extern\FALCON\lib" /libpath:"$(ORBDIR)\lib\x86_win32"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Release\xcons.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "sh_app_xmlcons - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /I "..\..\..\Extern\XERCES\include" /I "..\..\..\Src\Apps\XMLCons\SocketApi" /I "..\..\..\Src\Apps\XMLCons\Server" /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\Src" /I "..\..\..\Src\Orb" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /D "_NO_QT_" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xerces-c_3D.lib omnithread$(ORBTHREADVERSION)_rtd.lib omniORB$(ORBVERSION)_rtd.lib omniDynamic$(ORBVERSION)_rtd.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib addidata.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"Debug/xconsd.exe" /pdbtype:sept /libpath:"..\..\..\Extern\XERCES\lib\vc6" /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\ADDIDATA\lib" /libpath:"..\..\..\Extern\FALCON\lib" /libpath:"$(ORBDIR)\lib\x86_win32"
# SUBTRACT LINK32 /profile /pdb:none /force
# Begin Special Build Tool
TargetPath=.\Debug\xconsd.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "sh_app_xmlcons - Win32 Release"
# Name "sh_app_xmlcons - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Server"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cAlloc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cAlloc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cBinaryFrameHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cBinaryFrameHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cChunkBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cChunkBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cFrameHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cFrameHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cService.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cService.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cServiceHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cServiceHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cTCPServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\Server\cTCPServer.h
# End Source File
# End Group
# Begin Group "SocketApi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\SocketApi\cSocketApi.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\SocketApi\cSocketApi.h
# End Source File
# End Group
# Begin Group "XML"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\XML\DOMPrintFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\XML\DOMPrintFilter.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\XML\XMLUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\XML\XMLUtils.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\cImageConverter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\cImageConverter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\cProcessWrapper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\cProcessWrapper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\cXMLService.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\cXMLService.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Apps\XMLCons\xmlcons.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
