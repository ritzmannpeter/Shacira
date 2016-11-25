# Microsoft Developer Studio Generated NMAKE File, Based on test_mfc.dsp
!IF "$(CFG)" == ""
CFG=test_mfc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to test_mfc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "test_mfc - Win32 Release" && "$(CFG)" != "test_mfc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test_mfc.mak" CFG="test_mfc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test_mfc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "test_mfc - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "test_mfc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_mfc.exe"

!ELSE 

ALL : "ecl_win - Win32 Release" "ecl_store - Win32 Release" "ecl_base - Win32 Release" "$(OUTDIR)\test_mfc.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_base - Win32 ReleaseCLEAN" "ecl_store - Win32 ReleaseCLEAN" "ecl_win - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MyDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\test_mfc.obj"
	-@erase "$(INTDIR)\test_mfc.pch"
	-@erase "$(INTDIR)\test_mfc.res"
	-@erase "$(INTDIR)\test_mfcDoc.obj"
	-@erase "$(INTDIR)\test_mfcView.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\test_mfc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\test_mfc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\test_mfc.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_mfc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\test_mfc.pdb" /machine:I386 /out:"$(OUTDIR)\test_mfc.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MyDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\test_mfc.obj" \
	"$(INTDIR)\test_mfcDoc.obj" \
	"$(INTDIR)\test_mfcView.obj" \
	"$(INTDIR)\test_mfc.res" \
	"..\ecl_base\Release\ecl_base.lib" \
	"..\ecl_store\Release\ecl_store.lib" \
	"..\ecl_win\Release\ecl_win.lib"

"$(OUTDIR)\test_mfc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test_mfc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_mfc.exe" "$(OUTDIR)\test_mfc.pch"

!ELSE 

ALL : "ecl_win - Win32 Debug" "ecl_store - Win32 Debug" "ecl_base - Win32 Debug" "$(OUTDIR)\test_mfc.exe" "$(OUTDIR)\test_mfc.pch"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_base - Win32 DebugCLEAN" "ecl_store - Win32 DebugCLEAN" "ecl_win - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MyDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\test_mfc.obj"
	-@erase "$(INTDIR)\test_mfc.pch"
	-@erase "$(INTDIR)\test_mfc.res"
	-@erase "$(INTDIR)\test_mfcDoc.obj"
	-@erase "$(INTDIR)\test_mfcView.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\test_mfc.exe"
	-@erase "$(OUTDIR)\test_mfc.ilk"
	-@erase "$(OUTDIR)\test_mfc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "_WINDOWS" /D "_AFXDLL" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\test_mfc.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_mfc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\test_mfc.pdb" /debug /machine:I386 /out:"$(OUTDIR)\test_mfc.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MyDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\test_mfc.obj" \
	"$(INTDIR)\test_mfcDoc.obj" \
	"$(INTDIR)\test_mfcView.obj" \
	"$(INTDIR)\test_mfc.res" \
	"..\ecl_base\Debug\ecl_base.lib" \
	"..\ecl_store\Debug\ecl_store.lib" \
	"..\ecl_win\Debug\ecl_win.lib"

"$(OUTDIR)\test_mfc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("test_mfc.dep")
!INCLUDE "test_mfc.dep"
!ELSE 
!MESSAGE Warning: cannot find "test_mfc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test_mfc - Win32 Release" || "$(CFG)" == "test_mfc - Win32 Debug"
SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "test_mfc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\test_mfc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\test_mfc.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "test_mfc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "_WINDOWS" /D "_AFXDLL" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\MyDialog.cpp

"$(INTDIR)\MyDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\test_mfc.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "test_mfc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\test_mfc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\test_mfc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "test_mfc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "_WINDOWS" /D "_AFXDLL" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)\test_mfc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\test_mfc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\test_mfc.cpp

"$(INTDIR)\test_mfc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\test_mfc.pch"


SOURCE=.\test_mfc.rc

"$(INTDIR)\test_mfc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\test_mfcDoc.cpp

"$(INTDIR)\test_mfcDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\test_mfc.pch"


SOURCE=.\test_mfcView.cpp

"$(INTDIR)\test_mfcView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\test_mfc.pch"


!IF  "$(CFG)" == "test_mfc - Win32 Release"

"ecl_base - Win32 Release" : 
   cd "\proj\ecl\targ\vcpp\ecl_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_base.mak CFG="ecl_base - Win32 Release" 
   cd "..\test_mfc"

"ecl_base - Win32 ReleaseCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_base.mak CFG="ecl_base - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_mfc"

!ELSEIF  "$(CFG)" == "test_mfc - Win32 Debug"

"ecl_base - Win32 Debug" : 
   cd "\proj\ecl\targ\vcpp\ecl_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_base.mak CFG="ecl_base - Win32 Debug" 
   cd "..\test_mfc"

"ecl_base - Win32 DebugCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_base.mak CFG="ecl_base - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_mfc"

!ENDIF 

!IF  "$(CFG)" == "test_mfc - Win32 Release"

"ecl_store - Win32 Release" : 
   cd "\proj\ecl\targ\vcpp\ecl_store"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_store.mak CFG="ecl_store - Win32 Release" 
   cd "..\test_mfc"

"ecl_store - Win32 ReleaseCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_store"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_store.mak CFG="ecl_store - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_mfc"

!ELSEIF  "$(CFG)" == "test_mfc - Win32 Debug"

"ecl_store - Win32 Debug" : 
   cd "\proj\ecl\targ\vcpp\ecl_store"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_store.mak CFG="ecl_store - Win32 Debug" 
   cd "..\test_mfc"

"ecl_store - Win32 DebugCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_store"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_store.mak CFG="ecl_store - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_mfc"

!ENDIF 

!IF  "$(CFG)" == "test_mfc - Win32 Release"

"ecl_win - Win32 Release" : 
   cd "\proj\ecl\targ\vcpp\ecl_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_win.mak CFG="ecl_win - Win32 Release" 
   cd "..\test_mfc"

"ecl_win - Win32 ReleaseCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_win.mak CFG="ecl_win - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_mfc"

!ELSEIF  "$(CFG)" == "test_mfc - Win32 Debug"

"ecl_win - Win32 Debug" : 
   cd "\proj\ecl\targ\vcpp\ecl_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_win.mak CFG="ecl_win - Win32 Debug" 
   cd "..\test_mfc"

"ecl_win - Win32 DebugCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_win"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_win.mak CFG="ecl_win - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_mfc"

!ENDIF 


!ENDIF 

