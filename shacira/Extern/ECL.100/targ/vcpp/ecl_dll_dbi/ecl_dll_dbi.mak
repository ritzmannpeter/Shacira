# Microsoft Developer Studio Generated NMAKE File, Based on ecl_dll_dbi.dsp
!IF "$(CFG)" == ""
CFG=ecl_dll_dbi - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ecl_dll_dbi - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ecl_dll_dbi - Win32 Release" && "$(CFG)" != "ecl_dll_dbi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_dll_dbi.mak" CFG="ecl_dll_dbi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ecl_dll_dbi - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ecl_dll_dbi - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ecl_dll_dbi - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ecldbi.dll"

!ELSE 

ALL : "ecl_dll_base - Win32 Release" "$(OUTDIR)\ecldbi.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\edb_cursor.obj"
	-@erase "$(INTDIR)\edb_cursor_ex.obj"
	-@erase "$(INTDIR)\edb_database.obj"
	-@erase "$(INTDIR)\edb_dictionary.obj"
	-@erase "$(INTDIR)\edb_dml.obj"
	-@erase "$(INTDIR)\edb_field.obj"
	-@erase "$(INTDIR)\edb_function.obj"
	-@erase "$(INTDIR)\edb_query.obj"
	-@erase "$(INTDIR)\edb_record.obj"
	-@erase "$(INTDIR)\edb_row.obj"
	-@erase "$(INTDIR)\edb_sql.obj"
	-@erase "$(INTDIR)\edb_transaction.obj"
	-@erase "$(INTDIR)\edb_var.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ecldbi.dll"
	-@erase "$(OUTDIR)\ecldbi.exp"
	-@erase "$(OUTDIR)\ecldbi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "..\..\..\src" /D "__ODBC__" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_DBI_EXPORTS" /Fp"$(INTDIR)\ecl_dll_dbi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_dll_dbi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ecldbi.pdb" /machine:I386 /out:"$(OUTDIR)\ecldbi.dll" /implib:"$(OUTDIR)\ecldbi.lib" 
LINK32_OBJS= \
	"$(INTDIR)\edb_dml.obj" \
	"$(INTDIR)\edb_function.obj" \
	"$(INTDIR)\edb_transaction.obj" \
	"$(INTDIR)\edb_cursor.obj" \
	"$(INTDIR)\edb_cursor_ex.obj" \
	"$(INTDIR)\edb_database.obj" \
	"$(INTDIR)\edb_dictionary.obj" \
	"$(INTDIR)\edb_record.obj" \
	"$(INTDIR)\edb_sql.obj" \
	"$(INTDIR)\edb_field.obj" \
	"$(INTDIR)\edb_query.obj" \
	"$(INTDIR)\edb_row.obj" \
	"$(INTDIR)\edb_var.obj" \
	"..\ecl_dll_base\Release\eclbse.lib"

"$(OUTDIR)\ecldbi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\ecldbi.dll
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "ecl_dll_base - Win32 Release" "$(OUTDIR)\ecldbi.dll"
   copy .\Release\ecldbi.dll ..\..\..\bin\win32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ecl_dll_dbi - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ecldbid.dll"

!ELSE 

ALL : "ecl_dll_base - Win32 Debug" "$(OUTDIR)\ecldbid.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ecl_dll_base - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\edb_cursor.obj"
	-@erase "$(INTDIR)\edb_cursor_ex.obj"
	-@erase "$(INTDIR)\edb_database.obj"
	-@erase "$(INTDIR)\edb_dictionary.obj"
	-@erase "$(INTDIR)\edb_dml.obj"
	-@erase "$(INTDIR)\edb_field.obj"
	-@erase "$(INTDIR)\edb_function.obj"
	-@erase "$(INTDIR)\edb_query.obj"
	-@erase "$(INTDIR)\edb_record.obj"
	-@erase "$(INTDIR)\edb_row.obj"
	-@erase "$(INTDIR)\edb_sql.obj"
	-@erase "$(INTDIR)\edb_transaction.obj"
	-@erase "$(INTDIR)\edb_var.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ecldbid.dll"
	-@erase "$(OUTDIR)\ecldbid.exp"
	-@erase "$(OUTDIR)\ecldbid.ilk"
	-@erase "$(OUTDIR)\ecldbid.lib"
	-@erase "$(OUTDIR)\ecldbid.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "__ODBC__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_DBI_EXPORTS" /D "_CRTDBG_MAP_ALLOC" /Fp"$(INTDIR)\ecl_dll_dbi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_dll_dbi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ecldbid.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ecldbid.dll" /implib:"$(OUTDIR)\ecldbid.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\edb_dml.obj" \
	"$(INTDIR)\edb_function.obj" \
	"$(INTDIR)\edb_transaction.obj" \
	"$(INTDIR)\edb_cursor.obj" \
	"$(INTDIR)\edb_cursor_ex.obj" \
	"$(INTDIR)\edb_database.obj" \
	"$(INTDIR)\edb_dictionary.obj" \
	"$(INTDIR)\edb_record.obj" \
	"$(INTDIR)\edb_sql.obj" \
	"$(INTDIR)\edb_field.obj" \
	"$(INTDIR)\edb_query.obj" \
	"$(INTDIR)\edb_row.obj" \
	"$(INTDIR)\edb_var.obj" \
	"..\ecl_dll_base\Debug\eclbsed.lib"

"$(OUTDIR)\ecldbid.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\ecldbid.dll
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "ecl_dll_base - Win32 Debug" "$(OUTDIR)\ecldbid.dll"
   copy .\Debug\ecldbid.dll ..\..\..\bin\win32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ecl_dll_dbi.dep")
!INCLUDE "ecl_dll_dbi.dep"
!ELSE 
!MESSAGE Warning: cannot find "ecl_dll_dbi.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ecl_dll_dbi - Win32 Release" || "$(CFG)" == "ecl_dll_dbi - Win32 Debug"
SOURCE=..\..\..\src\dbi\edb_dml.cpp

"$(INTDIR)\edb_dml.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_function.cpp

"$(INTDIR)\edb_function.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_transaction.cpp

"$(INTDIR)\edb_transaction.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_cursor.cpp

"$(INTDIR)\edb_cursor.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_cursor_ex.cpp

"$(INTDIR)\edb_cursor_ex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_database.cpp

"$(INTDIR)\edb_database.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_dictionary.cpp

"$(INTDIR)\edb_dictionary.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_record.cpp

"$(INTDIR)\edb_record.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_sql.cpp

"$(INTDIR)\edb_sql.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_field.cpp

"$(INTDIR)\edb_field.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_query.cpp

"$(INTDIR)\edb_query.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_row.cpp

"$(INTDIR)\edb_row.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\dbi\edb_var.cpp

"$(INTDIR)\edb_var.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "ecl_dll_dbi - Win32 Release"

"ecl_dll_base - Win32 Release" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" 
   cd "..\ecl_dll_dbi"

"ecl_dll_base - Win32 ReleaseCLEAN" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Release" RECURSE=1 CLEAN 
   cd "..\ecl_dll_dbi"

!ELSEIF  "$(CFG)" == "ecl_dll_dbi - Win32 Debug"

"ecl_dll_base - Win32 Debug" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" 
   cd "..\ecl_dll_dbi"

"ecl_dll_base - Win32 DebugCLEAN" : 
   cd "\usr\prj\Shacira\Extern\ECL\targ\vcpp\ecl_dll_base"
   $(MAKE) /$(MAKEFLAGS) /F .\ecl_dll_base.mak CFG="ecl_dll_base - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\ecl_dll_dbi"

!ENDIF 


!ENDIF 

