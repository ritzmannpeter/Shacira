# Microsoft Developer Studio Project File - Name="sh_tool_abuild" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=sh_tool_abuild - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "sh_tool_abuild.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "sh_tool_abuild.mak" CFG="sh_tool_abuild - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "sh_tool_abuild - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "sh_tool_abuild - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sh_tool_abuild - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Src\Tools\abuild" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /map /machine:I386 /out:"Release/abuild.exe" /libpath:"..\..\..\Extern\STL\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Release\abuild.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "sh_tool_abuild - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Src\Tools\abuild" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"Debug/abuildd.exe" /pdbtype:sept /libpath:"..\..\..\Extern\STL\lib"
# SUBTRACT LINK32 /profile /pdb:none /force
# Begin Special Build Tool
TargetPath=.\Debug\abuildd.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "sh_tool_abuild - Win32 Release"
# Name "sh_tool_abuild - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Graph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\Graph\cAngle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\Graph\cAngle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\Graph\cGraph.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\Graph\cGraph.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\Graph\cNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\Graph\cNode.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\tools\abuild\abuild.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cAutoProject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cDirectoryUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cPath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cPathGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cReliance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cVirtualFileSystem.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\abuild.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cAutoProject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cDirectoryUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cPath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cPathGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cReliance.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cSource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Tools\abuild\cVirtualFileSystem.h
# End Source File
# End Group
# End Target
# End Project
