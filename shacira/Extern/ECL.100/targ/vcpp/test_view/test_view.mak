# Microsoft Developer Studio Generated NMAKE File, Based on test_view.dsp
!IF "$(CFG)" == ""
CFG=test_view - Win32 Debug
!MESSAGE No configuration specified. Defaulting to test_view - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "test_view - Win32 Release" && "$(CFG)" != "test_view - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test_view.mak" CFG="test_view - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test_view - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "test_view - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "test_view - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_view.exe"

!ELSE 

ALL : "ecl_dll_win - Win32 Release" "ecl_dll_base - Win32 Release" "$(OUTDIR)\test_view.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 ReleaseCLEAN" "ecl_dll_win - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\test_view.obj"
	-@erase "$(INTDIR)\test_view.res"
	-@erase "$(INTDIR)\tw_direct_view.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\test_view.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "..\..\..\src" /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\test_view.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\test_view.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_view.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\test_view.pdb" /machine:I386 /out:"$(OUTDIR)\test_view.exe" 
LINK32_OBJS= \
	"$(INTDIR)\test_view.res" \
	"$(INTDIR)\tw_direct_view.obj" \
	"$(INTDIR)\test_view.obj" \
	"..\ecl_dll_base\Release\eclbse.lib" \
	"..\ecl_dll_win\Release\eclwin.lib"

"$(OUTDIR)\test_view.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test_view - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_view.exe"

!ELSE 

ALL : "ecl_dll_win - Win32 Debug" "ecl_dll_base - Win32 Debug" "$(OUTDIR)\test_view.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 DebugCLEAN" "ecl_dll_win - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\test_view.obj"
	-@erase "$(INTDIR)\test_view.res"
	-@erase "$(INTDIR)\tw_direct_view.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\test_view.exe"
	-@erase "$(OUTDIR)\test_view.ilk"
	-@erase "$(OUTDIR)\test_view.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\test_view.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\test_view.res" /i "..\..\..\src" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_view.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\test_view.pdb" /debug /machine:I386 /out:"$(OUTDIR)\test_view.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\test_view.res" \
	"$(INTDIR)\tw_direct_view.obj" \
	"$(INTDIR)\test_view.obj" \
	"..\ecl_dll_base\Debug\eclbsed.lib" \
	"..\ecl_dll_win\Debug\eclwind.lib"

"$(OUTDIR)\test_view.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("test_view.dep")
!INCLUDE "test_view.dep"
!ELSE 
!MESSAGE Warning: cannot find "test_view.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test_view - Win32 Release" || "$(CFG)" == "test_view - Win32 Debug"
SOURCE=..\..\..\src\win\demo\test_view.cpp

"$(INTDIR)\test_view.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\win\demo\tw_direct_view.cpp

"$(INTDIR)\tw_direct_view.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\test_view.rc

"$(INTDIR)\test_view.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "test_view - Win32 Release"

"ecl_dll_base - Win32 Release" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" 
   cd "..\test_view"

"ecl_dll_base - Win32 ReleaseCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_view"

!ELSEIF  "$(CFG)" == "test_view - Win32 Debug"

"ecl_dll_base - Win32 Debug" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" 
   cd "..\test_view"

"ecl_dll_base - Win32 DebugCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_view"

!ENDIF 

!IF  "$(CFG)" == "test_view - Win32 Release"

"ecl_dll_win - Win32 Release" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Release" 
   cd "..\test_view"

"ecl_dll_win - Win32 ReleaseCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_view"

!ELSEIF  "$(CFG)" == "test_view - Win32 Debug"

"ecl_dll_win - Win32 Debug" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Debug" 
   cd "..\test_view"

"ecl_dll_win - Win32 DebugCLEAN" : 
   cd "\proj\hht\WinFBS\ecl\targ\vcpp\ecl_dll_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_win.mak CFG="ecl_dll_win - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_view"

!ENDIF 


!ENDIF 

