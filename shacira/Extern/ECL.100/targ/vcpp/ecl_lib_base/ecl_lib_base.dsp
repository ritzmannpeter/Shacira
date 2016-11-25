# Microsoft Developer Studio Project File - Name="ecl_lib_base" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ecl_lib_base - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "ecl_lib_base.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_lib_base.mak" CFG="ecl_lib_base - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ecl_lib_base - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "ecl_lib_base - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ecl_lib_base - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\eclbse.lib"

!ELSEIF  "$(CFG)" == "ecl_lib_base - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\eclbsed.lib"

!ENDIF 

# Begin Target

# Name "ecl_lib_base - Win32 Release"
# Name "ecl_lib_base - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "_base"

# PROP Default_Filter "*.cpp"
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

# PROP Default_Filter "*.cpp"
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

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\..\src\base\eb_geo2d.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_math.cpp
# End Source File
# End Group
# Begin Group "_ipc"

# PROP Default_Filter "*.cpp"
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

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\..\src\base\eb_cmdarg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\base\eb_cmdline.cpp
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
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
