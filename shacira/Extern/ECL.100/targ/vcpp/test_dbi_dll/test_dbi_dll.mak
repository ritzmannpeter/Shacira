# Microsoft Developer Studio Generated NMAKE File, Based on test_dbi_dll.dsp
!IF "$(CFG)" == ""
CFG=test_dbi_dll - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. test_dbi_dll - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "test_dbi_dll - Win32 Release" && "$(CFG)" != "test_dbi_dll - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "test_dbi_dll.mak" CFG="test_dbi_dll - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "test_dbi_dll - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "test_dbi_dll - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test_dbi_dll - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_dbi_dll.exe"

!ELSE 

ALL : "ecl_dll_dbi - Win32 Release" "ecl_dll_base - Win32 Release" "$(OUTDIR)\test_dbi_dll.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 ReleaseCLEAN" "ecl_dll_dbi - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\test_dbi.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\test_dbi_dll.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\test_dbi_dll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_dbi_dll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\test_dbi_dll.pdb" /machine:I386 /out:"$(OUTDIR)\test_dbi_dll.exe" 
LINK32_OBJS= \
	"$(INTDIR)\test_dbi.obj" \
	"..\ecl_dll_base\Release\ecl_dll_base.lib" \
	"..\ecl_dll_dbi\Release\ecl_dll_dbi.lib"

"$(OUTDIR)\test_dbi_dll.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test_dbi_dll - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_dbi_dll.exe"

!ELSE 

ALL : "ecl_dll_dbi - Win32 Debug" "ecl_dll_base - Win32 Debug" "$(OUTDIR)\test_dbi_dll.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 DebugCLEAN" "ecl_dll_dbi - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\test_dbi.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\test_dbi_dll.exe"
	-@erase "$(OUTDIR)\test_dbi_dll.ilk"
	-@erase "$(OUTDIR)\test_dbi_dll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\test_dbi_dll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_dbi_dll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\test_dbi_dll.pdb" /debug /machine:I386 /out:"$(OUTDIR)\test_dbi_dll.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\test_dbi.obj" \
	"..\ecl_dll_base\Debug\ecl_dll_base.lib" \
	"..\ecl_dll_dbi\Debug\ecl_dll_dbi.lib"

"$(OUTDIR)\test_dbi_dll.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("test_dbi_dll.dep")
!INCLUDE "test_dbi_dll.dep"
!ELSE 
!MESSAGE Warning: cannot find "test_dbi_dll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test_dbi_dll - Win32 Release" || "$(CFG)" == "test_dbi_dll - Win32 Debug"
SOURCE=..\..\..\src\dbi\demo\test_dbi.cpp

"$(INTDIR)\test_dbi.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "test_dbi_dll - Win32 Release"

"ecl_dll_base - Win32 Release" : 
   cd "\proj\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" 
   cd "..\test_dbi_dll"

"ecl_dll_base - Win32 ReleaseCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_dbi_dll"

!ELSEIF  "$(CFG)" == "test_dbi_dll - Win32 Debug"

"ecl_dll_base - Win32 Debug" : 
   cd "\proj\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" 
   cd "..\test_dbi_dll"

"ecl_dll_base - Win32 DebugCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_dbi_dll"

!ENDIF 

!IF  "$(CFG)" == "test_dbi_dll - Win32 Release"

"ecl_dll_dbi - Win32 Release" : 
   cd "\proj\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Release" 
   cd "..\test_dbi_dll"

"ecl_dll_dbi - Win32 ReleaseCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_dbi_dll"

!ELSEIF  "$(CFG)" == "test_dbi_dll - Win32 Debug"

"ecl_dll_dbi - Win32 Debug" : 
   cd "\proj\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Debug" 
   cd "..\test_dbi_dll"

"ecl_dll_dbi - Win32 DebugCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_dll_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_dbi.mak CFG="ecl_dll_dbi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_dbi_dll"

!ENDIF 


!ENDIF 

