# Microsoft Developer Studio Generated NMAKE File, Based on ecl_lib_store.dsp
!IF "$(CFG)" == ""
CFG=ecl_lib_store - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ecl_lib_store - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ecl_lib_store - Win32 Release" && "$(CFG)" != "ecl_lib_store - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_lib_store.mak" CFG="ecl_lib_store - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ecl_lib_store - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ecl_lib_store - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ecl_lib_store - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\eclsto.lib"


CLEAN :
	-@erase "$(INTDIR)\es_base.obj"
	-@erase "$(INTDIR)\es_field.obj"
	-@erase "$(INTDIR)\es_filter.obj"
	-@erase "$(INTDIR)\es_query.obj"
	-@erase "$(INTDIR)\es_row.obj"
	-@erase "$(INTDIR)\es_store.obj"
	-@erase "$(INTDIR)\es_var.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\eclsto.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ecl_lib_store.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_lib_store.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\eclsto.lib" 
LIB32_OBJS= \
	"$(INTDIR)\es_base.obj" \
	"$(INTDIR)\es_field.obj" \
	"$(INTDIR)\es_filter.obj" \
	"$(INTDIR)\es_query.obj" \
	"$(INTDIR)\es_row.obj" \
	"$(INTDIR)\es_store.obj" \
	"$(INTDIR)\es_var.obj"

"$(OUTDIR)\eclsto.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ecl_lib_store - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\eclstod.lib"


CLEAN :
	-@erase "$(INTDIR)\es_base.obj"
	-@erase "$(INTDIR)\es_field.obj"
	-@erase "$(INTDIR)\es_filter.obj"
	-@erase "$(INTDIR)\es_query.obj"
	-@erase "$(INTDIR)\es_row.obj"
	-@erase "$(INTDIR)\es_store.obj"
	-@erase "$(INTDIR)\es_var.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\eclstod.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ecl_lib_store.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_lib_store.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\eclstod.lib" 
LIB32_OBJS= \
	"$(INTDIR)\es_base.obj" \
	"$(INTDIR)\es_field.obj" \
	"$(INTDIR)\es_filter.obj" \
	"$(INTDIR)\es_query.obj" \
	"$(INTDIR)\es_row.obj" \
	"$(INTDIR)\es_store.obj" \
	"$(INTDIR)\es_var.obj"

"$(OUTDIR)\eclstod.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ecl_lib_store.dep")
!INCLUDE "ecl_lib_store.dep"
!ELSE 
!MESSAGE Warning: cannot find "ecl_lib_store.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ecl_lib_store - Win32 Release" || "$(CFG)" == "ecl_lib_store - Win32 Debug"
SOURCE=..\..\..\src\store\es_base.cpp

"$(INTDIR)\es_base.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\store\es_field.cpp

"$(INTDIR)\es_field.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\store\es_filter.cpp

"$(INTDIR)\es_filter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\store\es_query.cpp

"$(INTDIR)\es_query.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\store\es_row.cpp

"$(INTDIR)\es_row.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\store\es_store.cpp

"$(INTDIR)\es_store.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\store\es_var.cpp

"$(INTDIR)\es_var.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

