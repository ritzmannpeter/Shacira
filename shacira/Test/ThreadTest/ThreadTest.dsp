# Microsoft Developer Studio Project File - Name="ThreadTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ThreadTest - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "ThreadTest.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ThreadTest.mak" CFG="ThreadTest - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ThreadTest - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "ThreadTest - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ThreadTest - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Src" /I "..\..\..\Src\Include" /I "..\..\..\Extern\OPC\src\OPCInterface" /I "..\..\..\Extern\OPC\src\OPCInterface\Include" /I "..\..\..\Src\System" /I "..\..\..\Src\CellControl\SerialChannel\Base" /I "..\..\..\Src\CellControl\DigitalChannel\AddiData\Base" /I "..\..\..\Src\Orb" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "..\..\..\Extern\ECL\src" /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\ECL\src" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /D "__x86__" /D "_OCS_TRACE" /D "__NT__" /D __OSVERSION__=4 /D "__USE_REC__" /D "_NO_QT_" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 addidata.lib omnithread32_rt.lib omniORB407_rt.lib omniDynamic407_rt.lib addidata.lib pa150.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /map /machine:I386 /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib" /libpath:"$(SHACIRADIR)\Extern\FALCON\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ThreadTest - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\ECL\src" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__WIN32__" /D "__x86__" /D "_OCS_TRACE" /D "__NT__" /D __OSVERSION__=4 /D "__USE_REC__" /D "_NO_QT_" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 addidata.lib omnithread32_rtd.lib omniORB407_rtd.lib omniDynamic407_rtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"Debug/ThreadTestd.exe" /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib" /libpath:"$(SHACIRADIR)\Extern\FALCON\lib"
# SUBTRACT LINK32 /profile /pdb:none /force

!ENDIF 

# Begin Target

# Name "ThreadTest - Win32 Release"
# Name "ThreadTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ThreadTest.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
