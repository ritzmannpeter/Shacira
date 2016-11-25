# Microsoft Developer Studio Project File - Name="webs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=webs - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "webs.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "webs.mak" CFG="webs - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "webs - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "webs - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "webs - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Zp1 /MD /W3 /O1 /I "$(SHACIRADIR)\include" /I "$(SHACIRADIR)\Src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "WEBS" /D "UEMF" /D "WIN" /D "DIGEST_ACCESS_SUPPORT" /D "USER_MANAGEMENT_SUPPORT" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 omnithread2_rt.lib omniorb304_rt.lib omnidynamic304_rt.lib wsock32.lib kernel32.lib user32.lib advapi32.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /map /machine:I386 /force /libpath:"..\SH\lib" /libpath:"$(SHACIRADIR)\Extern\STL\lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "webs - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /I "$(SHACIRADIR)\include" /I "$(SHACIRADIR)\Src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "WIN" /D "WEBS" /D "UEMF" /D "DIGEST_ACCESS_SUPPORT" /D "USER_MANAGEMENT_SUPPORT" /D "ASSERT" /D "DEV" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WEBS" /d "WIN"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 omnithread2_rtd.lib omniorb304_rtd.lib omnidynamic304_rtd.lib wsock32.lib kernel32.lib user32.lib advapi32.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /map /debug /machine:I386 /out:"websd.exe" /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\STL\lib"
# SUBTRACT LINK32 /incremental:no /nodefaultlib

!ENDIF 

# Begin Target

# Name "webs - Win32 Release"
# Name "webs - Win32 Debug"
# Begin Group "ShaciraIntegration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SH\shweb.cpp
# End Source File
# Begin Source File

SOURCE=..\SH\webintegration.c
# End Source File
# Begin Source File

SOURCE=..\SH\webintegration.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\asp.c
# End Source File
# Begin Source File

SOURCE=..\balloc.c
# End Source File
# Begin Source File

SOURCE=..\base64.c
# End Source File
# Begin Source File

SOURCE=..\cgi.c
# End Source File
# Begin Source File

SOURCE=..\default.c
# End Source File
# Begin Source File

SOURCE=..\ejlex.c
# End Source File
# Begin Source File

SOURCE=..\ejparse.c
# End Source File
# Begin Source File

SOURCE=..\emfdb.c
# End Source File
# Begin Source File

SOURCE=..\form.c
# End Source File
# Begin Source File

SOURCE=..\h.c
# End Source File
# Begin Source File

SOURCE=..\handler.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=..\md5c.c
# End Source File
# Begin Source File

SOURCE=..\mime.c
# End Source File
# Begin Source File

SOURCE=..\misc.c
# End Source File
# Begin Source File

SOURCE=..\page.c
# End Source File
# Begin Source File

SOURCE=..\ringq.c
# End Source File
# Begin Source File

SOURCE=..\rom.c
# End Source File
# Begin Source File

SOURCE=..\security.c
# End Source File
# Begin Source File

SOURCE=..\sock.c
# End Source File
# Begin Source File

SOURCE=..\sockGen.c
# End Source File
# Begin Source File

SOURCE=..\sym.c
# End Source File
# Begin Source File

SOURCE=..\uemf.c
# End Source File
# Begin Source File

SOURCE=..\um.c
# End Source File
# Begin Source File

SOURCE=..\umui.c
# End Source File
# Begin Source File

SOURCE=..\url.c
# End Source File
# Begin Source File

SOURCE=..\value.c
# End Source File
# Begin Source File

SOURCE=..\webrom.c
# End Source File
# Begin Source File

SOURCE=..\webs.c
# End Source File
# Begin Source File

SOURCE=..\websda.c
# End Source File
# Begin Source File

SOURCE=..\websuemf.c
# End Source File
# End Target
# End Project
