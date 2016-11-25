# Microsoft Developer Studio Generated NMAKE File, Based on test_sql.dsp
!IF "$(CFG)" == ""
CFG=test_sql - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. test_sql - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "test_sql - Win32 Release" && "$(CFG)" != "test_sql - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "test_sql.mak" CFG="test_sql - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "test_sql - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "test_sql - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "test_sql - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_sql.exe"

!ELSE 

ALL : "ecl_lib_dbi - Win32 Release" "ecl_lib_base - Win32 Release" "$(OUTDIR)\test_sql.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_lib_base - Win32 ReleaseCLEAN" "ecl_lib_dbi - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\test_sql.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\test_sql.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\test_sql.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_sql.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\test_sql.pdb" /machine:I386 /out:"$(OUTDIR)\test_sql.exe" 
LINK32_OBJS= \
	"$(INTDIR)\test_sql.obj" \
	"..\ecl_lib_base\Release\ecl_lib_base.lib" \
	"..\ecl_lib_dbi\Release\ecl_lib_dbi.lib"

"$(OUTDIR)\test_sql.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "test_sql - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\test_sql.exe"

!ELSE 

ALL : "ecl_lib_dbi - Win32 Debug" "ecl_lib_base - Win32 Debug" "$(OUTDIR)\test_sql.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_lib_base - Win32 DebugCLEAN" "ecl_lib_dbi - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\test_sql.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\test_sql.exe"
	-@erase "$(OUTDIR)\test_sql.ilk"
	-@erase "$(OUTDIR)\test_sql.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /I "..\..\..\..\src\ecl" /D "_CONSOLE" /D "__TEST_edb_sql__" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)\test_sql.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_sql.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\test_sql.pdb" /debug /machine:I386 /out:"$(OUTDIR)\test_sql.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\test_sql.obj" \
	"..\ecl_lib_base\Debug\ecl_lib_base.lib" \
	"..\ecl_lib_dbi\Debug\ecl_lib_dbi.lib"

"$(OUTDIR)\test_sql.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("test_sql.dep")
!INCLUDE "test_sql.dep"
!ELSE 
!MESSAGE Warning: cannot find "test_sql.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test_sql - Win32 Release" || "$(CFG)" == "test_sql - Win32 Debug"
SOURCE=..\..\..\src\dbi\demo\test_sql.cpp

"$(INTDIR)\test_sql.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "test_sql - Win32 Release"

"ecl_lib_base - Win32 Release" : 
   cd "\proj\ecl\targ\vcpp\ecl_lib_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_lib_base.mak CFG="ecl_lib_base - Win32 Release" 
   cd "..\test_sql"

"ecl_lib_base - Win32 ReleaseCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_lib_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_lib_base.mak CFG="ecl_lib_base - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_sql"

!ELSEIF  "$(CFG)" == "test_sql - Win32 Debug"

"ecl_lib_base - Win32 Debug" : 
   cd "\proj\ecl\targ\vcpp\ecl_lib_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_lib_base.mak CFG="ecl_lib_base - Win32 Debug" 
   cd "..\test_sql"

"ecl_lib_base - Win32 DebugCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_lib_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_lib_base.mak CFG="ecl_lib_base - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_sql"

!ENDIF 

!IF  "$(CFG)" == "test_sql - Win32 Release"

"ecl_lib_dbi - Win32 Release" : 
   cd "\proj\ecl\targ\vcpp\ecl_lib_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_lib_dbi.mak CFG="ecl_lib_dbi - Win32 Release" 
   cd "..\test_sql"

"ecl_lib_dbi - Win32 ReleaseCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_lib_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_lib_dbi.mak CFG="ecl_lib_dbi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\test_sql"

!ELSEIF  "$(CFG)" == "test_sql - Win32 Debug"

"ecl_lib_dbi - Win32 Debug" : 
   cd "\proj\ecl\targ\vcpp\ecl_lib_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_lib_dbi.mak CFG="ecl_lib_dbi - Win32 Debug" 
   cd "..\test_sql"

"ecl_lib_dbi - Win32 DebugCLEAN" : 
   cd "\proj\ecl\targ\vcpp\ecl_lib_dbi"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_lib_dbi.mak CFG="ecl_lib_dbi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\test_sql"

!ENDIF 


!ENDIF 

