# Microsoft Developer Studio Project File - Name="libdstyx" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libdstyx - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libdstyx.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libdstyx.mak" CFG="libdstyx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libdstyx - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libdstyx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libdstyx - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBDSTYX_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\libbase" /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBDSTYX_EXPORTS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 msvcrt.lib kernel32.lib user32.lib advapi32.lib oldnames.lib /nologo /dll /machine:I386 /nodefaultlib /def:"libdstyx.def"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "libdstyx - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBDSTYX_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\libbase" /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBDSTYX_EXPORTS" /FR /FD /GZ /c
# SUBTRACT CPP /X /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 msvcrt.lib kernel32.lib user32.lib advapi32.lib oldnames.lib /nologo /dll /debug /machine:I386 /nodefaultlib /def:"libdstyx.def" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "libdstyx - Win32 Release"
# Name "libdstyx - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\libbase\literal.c
# End Source File
# Begin Source File

SOURCE=..\libbase\prs_abs.c
# End Source File
# Begin Source File

SOURCE=..\libbase\binset.c
# End Source File
# Begin Source File

SOURCE=..\libbase\ctx_app.c
# End Source File
# Begin Source File

SOURCE=..\libbase\cfg_dfn.c
# End Source File
# Begin Source File

SOURCE=..\libbase\ptm.c
# End Source File
# Begin Source File

SOURCE=..\libbase\prim.c
# End Source File
# Begin Source File

SOURCE=..\libbase\scn_pre.c
# End Source File
# Begin Source File

SOURCE=..\libbase\scn_base.c
# End Source File
# Begin Source File

SOURCE=..\libbase\gstream.c
# End Source File
# Begin Source File

SOURCE=..\libbase\otab.c
# End Source File
# Begin Source File

SOURCE=..\libbase\hmap.c
# End Source File
# Begin Source File

SOURCE=..\libbase\line_scn.c
# End Source File
# Begin Source File

SOURCE=..\libbase\ptm_pp.c
# End Source File
# Begin Source File

SOURCE=..\libbase\hset.c
# End Source File
# Begin Source File

SOURCE=..\libbase\binimg.c
# End Source File
# Begin Source File

SOURCE=..\libbase\sink.c
# End Source File
# Begin Source File

SOURCE=..\libbase\ptm_gen.c
# End Source File
# Begin Source File

SOURCE=..\libbase\scn_abs.c
# End Source File
# Begin Source File

SOURCE=..\libbase\sysbase0.c
# End Source File
# Begin Source File

SOURCE=..\libbase\sysbase1.c
# End Source File
# Begin Source File

SOURCE=..\libbase\scn_io.c
# End Source File
# Begin Source File

SOURCE=..\modstd\gls.c
# End Source File
# Begin Source File

SOURCE=..\libbase\list.c
# End Source File
# Begin Source File

SOURCE=..\libbase\symbols.c
# End Source File
# Begin Source File

SOURCE=..\libbase\prs.c
# End Source File
# Begin Source File

SOURCE=..\libbase\prs_io.c
# End Source File
# Begin Source File

SOURCE=..\libbase\glo_tab.c
# End Source File
# Begin Source File

SOURCE=..\libbase\cfg_abs.c
# End Source File
# Begin Source File

SOURCE=..\libbase\pathes.c
# End Source File
# Begin Source File

SOURCE=..\modstd\memosx.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\inc\sysbase1.h
# End Source File
# Begin Source File

SOURCE=..\libbase\prs_dfn.h
# End Source File
# Begin Source File

SOURCE=..\inc\ptm.h
# End Source File
# Begin Source File

SOURCE=..\inc\otab.h
# End Source File
# Begin Source File

SOURCE=..\libbase\prs_imp.h
# End Source File
# Begin Source File

SOURCE=..\inc\binset.h
# End Source File
# Begin Source File

SOURCE=..\libbase\syscbhdl.h
# End Source File
# Begin Source File

SOURCE=..\inc\ptm_gen.h
# End Source File
# Begin Source File

SOURCE=..\inc\literal.h
# End Source File
# Begin Source File

SOURCE=..\inc\ptm_pp.h
# End Source File
# Begin Source File

SOURCE=..\inc\mem_base.h
# End Source File
# Begin Source File

SOURCE=..\inc\scn_base.h
# End Source File
# Begin Source File

SOURCE=..\inc\scn_pre.h
# End Source File
# Begin Source File

SOURCE=..\inc\pathes.h
# End Source File
# Begin Source File

SOURCE=..\inc\binimg.h
# End Source File
# Begin Source File

SOURCE=..\inc\memosx.h
# End Source File
# Begin Source File

SOURCE=..\inc\sysbase0.h
# End Source File
# Begin Source File

SOURCE=..\inc\hmap.h
# End Source File
# Begin Source File

SOURCE=..\inc\prim.h
# End Source File
# Begin Source File

SOURCE=..\inc\ctx_app.h
# End Source File
# Begin Source File

SOURCE=..\inc\sink.h
# End Source File
# Begin Source File

SOURCE=..\inc\glo_tab.h
# End Source File
# Begin Source File

SOURCE=..\inc\line_scn.h
# End Source File
# Begin Source File

SOURCE=..\inc\list.h
# End Source File
# Begin Source File

SOURCE=..\inc\cfg_dfn.h
# End Source File
# Begin Source File

SOURCE=..\libbase\ctx_imp.h
# End Source File
# Begin Source File

SOURCE=..\inc\prs_io.h
# End Source File
# Begin Source File

SOURCE=..\inc\hset.h
# End Source File
# Begin Source File

SOURCE=..\inc\scn_io.h
# End Source File
# Begin Source File

SOURCE=..\libbase\styconf0.h
# End Source File
# Begin Source File

SOURCE=..\libbase\ctx_dfn.h
# End Source File
# Begin Source File

SOURCE=..\libbase\scn_imp.h
# End Source File
# Begin Source File

SOURCE=..\inc\gstream.h
# End Source File
# Begin Source File

SOURCE=..\inc\prs.h
# End Source File
# Begin Source File

SOURCE=..\inc\cfg_abs.h
# End Source File
# Begin Source File

SOURCE=..\inc\gls.h
# End Source File
# Begin Source File

SOURCE=..\inc\prs_abs.h
# End Source File
# Begin Source File

SOURCE=..\libbase\standard.h
# End Source File
# Begin Source File

SOURCE=..\inc\scn_abs.h
# End Source File
# Begin Source File

SOURCE=..\inc\symbols.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
