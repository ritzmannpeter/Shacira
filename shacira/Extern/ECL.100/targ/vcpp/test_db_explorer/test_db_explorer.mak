# Microsoft Developer Studio Generated NMAKE File, Based on test_db_explorer.dsp
!IF "$(CFG)" == ""
CFG=test_db_explorer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to test_db_explorer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "test_db_explorer - Win32 Release" && "$(CFG)" != "test_db_explorer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test_db_explorer.mak" CFG="test_db_explorer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test_db_explorer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "test_db_explorer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test_db_explorer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_db_explorer.exe"

!ELSE 

ALL : "ecl_dll_win - Win32 Release" "ecl_dll_dbi - Win32 Release" "ecl_dll_base - Win32 Release" "$(OUTDIR)\test_db_explorer.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 ReleaseCLEAN" "ecl_dll_dbi - Win32 ReleaseCLEAN" "ecl_dll_win - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\db_explorer.obj"
	-@erase "$(INTDIR)\test_db_explorer.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\test_db_explorer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\test_db_explorer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\test_db_explorer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_db_explorer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\test_db_explorer.pdb" /machine:I386 /out:"$(OUTDIR)\test_db_explorer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\db_explorer.obj" \
	"$(INTDIR)\test_db_explorer.res" \
	"..\ecl_dll_base\Release\eclbse.lib" \
	"..\ecl_dll_dbi\Release\ecldbi.lib" \
	"..\ecl_dll_win\Release\eclwin.lib"

"$(OUTDIR)\test_db_explorer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test_db_explorer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_db_explorer.exe"

!ELSE 

ALL : "ecl_dll_win - Win32 Debug" "ecl_dll_dbi - Win32 Debug" "ecl_dll_base - Win32 Debug" "$(OUTDIR)\test_db_explorer.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 DebugCLEAN" "ecl_dll_dbi - Win32 DebugCLEAN" "ecl_dll_win - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\db_explorer.obj"
	-@erase "$(INTDIR)\test_db_explorer.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\test_db_explorer.exe"
	-@erase "$(OUTDIR)\test_db_explorer.ilk"
	-@erase "$(OUTDIR)\test_db_explorer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\test_db_explorer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\test_db_explorer.res" /i "..\..\..\src" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_db_explorer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\test_db_explorer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\test_db_explorer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\db_explorer.obj" \
	"$(INTDIR)\test_db_explorer.res" \
	"..\ecl_dll_base\Debug\eclbsed.lib" \
	"..\ecl_dll_dbi\Debug\ecldbid.lib" \
	"..\ecl_dll_win\Debug\eclwind.lib"

"$(OUTDIR)\test_db_explorer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("test_db_explorer.dep")
!INCLUDE "test_db_explorer.dep"
!ELSE 
!MESSAGE Warning: cannot find "test_db_explorer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test_db_explorer - Win32 Release" || "$(CFG)" == "test_db_explorer - Win32 Debug"
SOURCE=..\..\..\src\win\demo\db_explorer.cpp

"$(INTDIR)\db_explorer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\test_db_explorer.rc

"$(INTDIR)\test_db_explorer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "test_db_explorer - Win32 Release"

"ecl_dll_base - Win32 Release" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" 
   cd "..\test_db_explorer"

"ecl_dll_base - Win32 ReleaseCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_db_explorer"

!ELSEIF  "$(CFG)" == "test_db_explorer - Win32 Debug"

"ecl_dll_base - Win32 Debug" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" 
   cd "..\test_db_explorer"

"ecl_dll_base - Win32 DebugCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_db_explorer"

!ENDIF 

!IF  "$(CFG)" == "test_db_explorer - Win32 Release"

"ecl_dll_dbi - Win32 Release" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Release" 
   cd "..\test_db_explorer"

"ecl_dll_dbi - Win32 ReleaseCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_db_explorer"

!ELSEIF  "$(CFG)" == "test_db_explorer - Win32 Debug"

"ecl_dll_dbi - Win32 Debug" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Debug" 
   cd "..\test_db_explorer"

"ecl_dll_dbi - Win32 DebugCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_db_explorer"

!ENDIF 

!IF  "$(CFG)" == "test_db_explorer - Win32 Release"

"ecl_dll_win - Win32 Release" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Release" 
   cd "..\test_db_explorer"

"ecl_dll_win - Win32 ReleaseCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_db_explorer"

!ELSEIF  "$(CFG)" == "test_db_explorer - Win32 Debug"

"ecl_dll_win - Win32 Debug" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Debug" 
   cd "..\test_db_explorer"

"ecl_dll_win - Win32 DebugCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_db_explorer"

!ENDIF 


!ENDIF 

