# Microsoft Developer Studio Project File - Name="ecl_dll_base" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ecl_dll_base - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "ecl_dll_base.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_dll_base.mak" CFG="ecl_dll_base - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ecl_dll_base - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ecl_dll_base - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ecl_dll_base - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_BASE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_BASE_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/eclbse.dll"
# Begin Special Build Tool
TargetPath=.\Release\eclbse.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32	copy $(TargetPath) ..\..\..\..\..\bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ecl_dll_base - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_BASE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_BASE_EXPORTS" /D "_CRTDBG_MAP_ALLOC" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/eclbsed.dll" /pdbtype:sept
# Begin Special Build Tool
TargetPath=.\Debug\eclbsed.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32	copy $(TargetPath) ..\..\..\..\..\bin\win32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ecl_dll_base - Win32 Release"
# Name "ecl_dll_base - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "_base"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\base\eb_base.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_bprintf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_docview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_elo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_eloex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_err.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_event.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_str.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_strex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_time.cpp
# End Source File
# End Group
# Begin Group "_collect"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\base\eb_array.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_collect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_list.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_map.cpp
# End Source File
# End Group
# Begin Group "_math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\base\eb_geo2d.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_math.cpp
# End Source File
# End Group
# Begin Group "_ipc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\base\eb_clip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_msg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_npipe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_queue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_sema.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\ring.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\sharedmem.cpp
# End Source File
# End Group
# Begin Group "_sys"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\base\eb_cmdarg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_dde.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_except.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_osver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_process.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_prof.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_res.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_thread.cpp
# End Source File
# End Group
# Begin Group "_store"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\store\es_base.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\store\es_field.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\store\es_filter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\store\es_query.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\store\es_row.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\store\es_store.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\store\es_var.cpp
# End Source File
# End Group
# Begin Group "_tom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\tom\et_con.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\tom\et_concli.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\tom\et_conser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\tom\et_tomate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\tom\et_tools.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
