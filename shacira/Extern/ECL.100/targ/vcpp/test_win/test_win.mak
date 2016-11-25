# Microsoft Developer Studio Generated NMAKE File, Based on test_win.dsp
!IF "$(CFG)" == ""
CFG=test_win - Win32 Debug
!MESSAGE No configuration specified. Defaulting to test_win - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "test_win - Win32 Release" && "$(CFG)" != "test_win - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test_win.mak" CFG="test_win - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test_win - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "test_win - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "test_win - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_win.exe"

!ELSE 

ALL : "ecl_dll_win - Win32 Release" "ecl_dll_dbi - Win32 Release" "ecl_dll_base - Win32 Release" "$(OUTDIR)\test_win.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 ReleaseCLEAN" "ecl_dll_dbi - Win32 ReleaseCLEAN" "ecl_dll_win - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\test_win.obj"
	-@erase "$(INTDIR)\test_win.res"
	-@erase "$(INTDIR)\tw_direct_view.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\test_win.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\src" /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\test_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\test_win.res" /i "..\..\..\src" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_win.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\test_win.pdb" /machine:I386 /out:"$(OUTDIR)\test_win.exe" 
LINK32_OBJS= \
	"$(INTDIR)\test_win.obj" \
	"$(INTDIR)\tw_direct_view.obj" \
	"$(INTDIR)\test_win.res" \
	"..\ecl_dll_base\Release\eclbse.lib" \
	"..\ecl_dll_dbi\Release\ecldbi.lib" \
	"..\ecl_dll_win\Release\eclwin.lib"

"$(OUTDIR)\test_win.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test_win - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_win.exe"

!ELSE 

ALL : "ecl_dll_win - Win32 Debug" "ecl_dll_dbi - Win32 Debug" "ecl_dll_base - Win32 Debug" "$(OUTDIR)\test_win.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 DebugCLEAN" "ecl_dll_dbi - Win32 DebugCLEAN" "ecl_dll_win - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\test_win.obj"
	-@erase "$(INTDIR)\test_win.res"
	-@erase "$(INTDIR)\tw_direct_view.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\test_win.exe"
	-@erase "$(OUTDIR)\test_win.ilk"
	-@erase "$(OUTDIR)\test_win.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /I "." /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)\test_win.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\test_win.res" /i "..\..\..\src" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_win.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\test_win.pdb" /debug /machine:I386 /out:"$(OUTDIR)\test_win.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\test_win.obj" \
	"$(INTDIR)\tw_direct_view.obj" \
	"$(INTDIR)\test_win.res" \
	"..\ecl_dll_base\Debug\eclbsed.lib" \
	"..\ecl_dll_dbi\Debug\ecldbid.lib" \
	"..\ecl_dll_win\Debug\eclwind.lib"

"$(OUTDIR)\test_win.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("test_win.dep")
!INCLUDE "test_win.dep"
!ELSE 
!MESSAGE Warning: cannot find "test_win.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test_win - Win32 Release" || "$(CFG)" == "test_win - Win32 Debug"
SOURCE=..\..\..\src\win\demo\test_win.cpp

"$(INTDIR)\test_win.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\demo\tw_direct_view.cpp

"$(INTDIR)\tw_direct_view.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\test_win.rc

"$(INTDIR)\test_win.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "test_win - Win32 Release"

"ecl_dll_base - Win32 Release" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" 
   cd "..\test_win"

"ecl_dll_base - Win32 ReleaseCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_win"

!ELSEIF  "$(CFG)" == "test_win - Win32 Debug"

"ecl_dll_base - Win32 Debug" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" 
   cd "..\test_win"

"ecl_dll_base - Win32 DebugCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_win"

!ENDIF 

!IF  "$(CFG)" == "test_win - Win32 Release"

"ecl_dll_dbi - Win32 Release" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Release" 
   cd "..\test_win"

"ecl_dll_dbi - Win32 ReleaseCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_win"

!ELSEIF  "$(CFG)" == "test_win - Win32 Debug"

"ecl_dll_dbi - Win32 Debug" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Debug" 
   cd "..\test_win"

"ecl_dll_dbi - Win32 DebugCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_win"

!ENDIF 

!IF  "$(CFG)" == "test_win - Win32 Release"

"ecl_dll_win - Win32 Release" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Release" 
   cd "..\test_win"

"ecl_dll_win - Win32 ReleaseCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_win"

!ELSEIF  "$(CFG)" == "test_win - Win32 Debug"

"ecl_dll_win - Win32 Debug" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Debug" 
   cd "..\test_win"

"ecl_dll_win - Win32 DebugCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_win"

!ENDIF 


!ENDIF 

