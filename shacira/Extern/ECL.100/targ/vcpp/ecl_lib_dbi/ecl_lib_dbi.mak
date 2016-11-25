# Microsoft Developer Studio Generated NMAKE File, Based on ecl_lib_dbi.dsp
!IF "$(CFG)" == ""
CFG=ecl_lib_dbi - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ecl_lib_dbi - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ecl_lib_dbi - Win32 Release" && "$(CFG)" != "ecl_lib_dbi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_lib_dbi.mak" CFG="ecl_lib_dbi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ecl_lib_dbi - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ecl_lib_dbi - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ecl_lib_dbi - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ecldbi.lib"


CLEAN :
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
	-@erase "$(OUTDIR)\ecldbi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "..\..\..\src" /D "__ODBC__" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ecl_lib_dbi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_lib_dbi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ecldbi.lib" 
LIB32_OBJS= \
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
	"$(INTDIR)\edb_var.obj"

"$(OUTDIR)\ecldbi.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ecl_lib_dbi - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ecldbid.lib"


CLEAN :
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
	-@erase "$(OUTDIR)\ecldbid.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "__ODBC__" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ecl_lib_dbi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_lib_dbi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ecldbid.lib" 
LIB32_OBJS= \
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
	"$(INTDIR)\edb_var.obj"

"$(OUTDIR)\ecldbid.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ecl_lib_dbi.dep")
!INCLUDE "ecl_lib_dbi.dep"
!ELSE 
!MESSAGE Warning: cannot find "ecl_lib_dbi.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ecl_lib_dbi - Win32 Release" || "$(CFG)" == "ecl_lib_dbi - Win32 Debug"
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



!ENDIF 

