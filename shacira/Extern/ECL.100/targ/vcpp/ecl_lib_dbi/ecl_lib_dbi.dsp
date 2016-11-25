# Microsoft Developer Studio Project File - Name="ecl_lib_dbi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ecl_lib_dbi - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "ecl_lib_dbi.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_lib_dbi.mak" CFG="ecl_lib_dbi - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ecl_lib_dbi - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "ecl_lib_dbi - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ecl_lib_dbi - Win32 Release"

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
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\src" /D "__ODBC__" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\ecldbi.lib"

!ELSEIF  "$(CFG)" == "ecl_lib_dbi - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "__ODBC__" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\ecldbid.lib"

!ENDIF 

# Begin Target

# Name "ecl_lib_dbi - Win32 Release"
# Name "ecl_lib_dbi - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "_db_ta"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_dml.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_function.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_transaction.cpp
# End Source File
# End Group
# Begin Group "_db_base"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_cursor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_cursor_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_database.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_dictionary.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_record.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_sql.cpp
# End Source File
# End Group
# Begin Group "_db_store"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_field.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_query.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_row.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dbi\edb_var.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
