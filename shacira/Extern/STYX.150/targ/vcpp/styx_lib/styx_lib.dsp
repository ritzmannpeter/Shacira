# Microsoft Developer Studio Project File - Name="styx_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=styx_lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "styx_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "styx_lib.mak" CFG="styx_lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "styx_lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "styx_lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "styx_lib - Win32 Release"

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
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\src\INC" /I "..\..\..\src\LIBBASE" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\styxlib.lib"

!ELSEIF  "$(CFG)" == "styx_lib - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src\INC" /I "..\..\..\src\LIBBASE" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /D "_USRDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\styxlibd.lib"

!ENDIF 

# Begin Target

# Name "styx_lib - Win32 Release"
# Name "styx_lib - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "LIBBASE_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\BINIMG.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\BINSET.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\CFG_ABS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\CFG_DFN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\CTX_APP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\GLO_TAB.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\GSTREAM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\HMAP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\HSET.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\LINE_SCN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\LIST.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\LITERAL.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\OTAB.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\PATHES.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\PRIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\PRS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\PRS_ABS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\PTM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\PTM_GEN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\PTM_PP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\SCN_ABS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\SCN_BASE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\SCN_IO.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\SCN_PRE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\SINK.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\SYMBOLS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\SYSBASE0.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBBASE\SYSBASE1.C
# End Source File
# End Group
# Begin Group "LIBSTYX_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\BNF.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\META_EXP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\META_PRS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\PRS_GEN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\PRS_IO.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\REG_EXP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\SCN_GEN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\STYX_GEN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBSTYX\STYX_HDL.C
# End Source File
# End Group
# Begin Group "LIBUTIL_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\CHARLIB.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\CMDLIB.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\COM_GET.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\CTX.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\DATE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\DICT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\DICTS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\HPAT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\INTEGER.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\OLIST.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\PGM_BASE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\PRE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\RATIONAL.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\LIBUTIL\TERM.C
# End Source File
# End Group
# Begin Group "MODSTD_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\MODSTD\GLS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\src\MODSTD\MEMOSX.C
# End Source File
# End Group
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
