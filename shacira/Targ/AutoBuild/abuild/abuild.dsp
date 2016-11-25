# Microsoft Developer Studio Project File - Name="abuild" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=abuild - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "abuild.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "abuild.mak" CFG="abuild - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "abuild - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "abuild - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "abuild - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "..\include" /I "..\graph" /I "..\expressions" /I "..\base" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /map /machine:I386 /libpath:"..\..\..\Extern\STL\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Release\abuild.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) $(SHACIRADIR)\bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "abuild - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\graph" /I "..\expressions" /I "..\base" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"Debug/abuildd.exe" /pdbtype:sept /libpath:"..\..\..\Extern\STL\lib"
# SUBTRACT LINK32 /profile /pdb:none /force

!ENDIF 

# Begin Target

# Name "abuild - Win32 Release"
# Name "abuild - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Graph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\graph\cangle.cpp
# End Source File
# Begin Source File

SOURCE=..\graph\cangle.h
# End Source File
# Begin Source File

SOURCE=..\graph\cgraph.cpp
# End Source File
# Begin Source File

SOURCE=..\graph\cgraph.h
# End Source File
# Begin Source File

SOURCE=..\graph\cnode.cpp
# End Source File
# Begin Source File

SOURCE=..\graph\cnode.h
# End Source File
# Begin Source File

SOURCE=..\graph\cproperty.cpp
# End Source File
# Begin Source File

SOURCE=..\graph\cproperty.h
# End Source File
# End Group
# Begin Group "Expressions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\expressions\cexpparser.cpp
# End Source File
# Begin Source File

SOURCE=..\expressions\cexpparser.h
# End Source File
# Begin Source File

SOURCE=..\expressions\cexpression.cpp
# End Source File
# Begin Source File

SOURCE=..\expressions\cexpression.h
# End Source File
# Begin Source File

SOURCE=..\expressions\cexptokenizer.cpp
# End Source File
# Begin Source File

SOURCE=..\expressions\cexptokenizer.h
# End Source File
# Begin Source File

SOURCE=..\expressions\cparser.h
# End Source File
# Begin Source File

SOURCE=..\expressions\cpp.cpp
# End Source File
# Begin Source File

SOURCE=..\expressions\cpp.h
# End Source File
# Begin Source File

SOURCE=..\expressions\cstatestack.cpp
# End Source File
# Begin Source File

SOURCE=..\expressions\cstatestack.h
# End Source File
# Begin Source File

SOURCE=..\expressions\cstreamtokenizer.h
# End Source File
# Begin Source File

SOURCE=..\expressions\csymboltable.cpp
# End Source File
# Begin Source File

SOURCE=..\expressions\csymboltable.h
# End Source File
# End Group
# Begin Group "Base"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\base\cvalue.cpp
# End Source File
# Begin Source File

SOURCE=..\base\cvalue.h
# End Source File
# Begin Source File

SOURCE=..\base\cvaluet.cpp
# End Source File
# Begin Source File

SOURCE=..\base\cvaluet.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\abuild.cpp
# End Source File
# Begin Source File

SOURCE=.\abuild.h
# End Source File
# Begin Source File

SOURCE=.\cbuildconfiguration.cpp
# End Source File
# Begin Source File

SOURCE=.\cbuildconfiguration.h
# End Source File
# Begin Source File

SOURCE=.\cconfigbase.cpp
# End Source File
# Begin Source File

SOURCE=.\cconfigbase.h
# End Source File
# Begin Source File

SOURCE=.\cdirectoryutils.cpp
# End Source File
# Begin Source File

SOURCE=.\cdirectoryutils.h
# End Source File
# Begin Source File

SOURCE=.\cfileenumerator.cpp
# End Source File
# Begin Source File

SOURCE=.\cfileenumerator.h
# End Source File
# Begin Source File

SOURCE=.\cgraphnode.cpp
# End Source File
# Begin Source File

SOURCE=.\cgraphnode.h
# End Source File
# Begin Source File

SOURCE=.\cpath.cpp
# End Source File
# Begin Source File

SOURCE=.\cpath.h
# End Source File
# Begin Source File

SOURCE=.\cpathgroup.cpp
# End Source File
# Begin Source File

SOURCE=.\cpathgroup.h
# End Source File
# Begin Source File

SOURCE=.\cproject.cpp
# End Source File
# Begin Source File

SOURCE=.\cproject.h
# End Source File
# Begin Source File

SOURCE=.\cprojectfile.cpp
# End Source File
# Begin Source File

SOURCE=.\cprojectfile.h
# End Source File
# Begin Source File

SOURCE=.\creliance.cpp
# End Source File
# Begin Source File

SOURCE=.\creliance.h
# End Source File
# Begin Source File

SOURCE=.\ctool.cpp
# End Source File
# Begin Source File

SOURCE=.\ctool.h
# End Source File
# Begin Source File

SOURCE=.\ctoolfactory.cpp
# End Source File
# Begin Source File

SOURCE=.\ctoolfactory.h
# End Source File
# Begin Source File

SOURCE=.\cvirtualfilesystem.cpp
# End Source File
# Begin Source File

SOURCE=.\cvirtualfilesystem.h
# End Source File
# Begin Source File

SOURCE=.\file_types.h
# End Source File
# Begin Source File

SOURCE=.\portingsupport.cpp
# End Source File
# Begin Source File

SOURCE=.\portingsupport.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\global_defs.h
# End Source File
# End Group
# End Target
# End Project
