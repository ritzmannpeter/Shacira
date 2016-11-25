# Microsoft Developer Studio Generated NMAKE File, Based on ecl_lib_base.dsp
!IF "$(CFG)" == ""
CFG=ecl_lib_base - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ecl_lib_base - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ecl_lib_base - Win32 Release" && "$(CFG)" != "ecl_lib_base - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_lib_base.mak" CFG="ecl_lib_base - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ecl_lib_base - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ecl_lib_base - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ecl_lib_base - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\eclbse.lib"


CLEAN :
	-@erase "$(INTDIR)\eb_array.obj"
	-@erase "$(INTDIR)\eb_base.obj"
	-@erase "$(INTDIR)\eb_bprintf.obj"
	-@erase "$(INTDIR)\eb_clip.obj"
	-@erase "$(INTDIR)\eb_cmdarg.obj"
	-@erase "$(INTDIR)\eb_cmdline.obj"
	-@erase "$(INTDIR)\eb_collect.obj"
	-@erase "$(INTDIR)\eb_dde.obj"
	-@erase "$(INTDIR)\eb_docview.obj"
	-@erase "$(INTDIR)\eb_elo.obj"
	-@erase "$(INTDIR)\eb_eloex.obj"
	-@erase "$(INTDIR)\eb_err.obj"
	-@erase "$(INTDIR)\eb_event.obj"
	-@erase "$(INTDIR)\eb_except.obj"
	-@erase "$(INTDIR)\eb_file.obj"
	-@erase "$(INTDIR)\eb_geo2d.obj"
	-@erase "$(INTDIR)\eb_list.obj"
	-@erase "$(INTDIR)\eb_map.obj"
	-@erase "$(INTDIR)\eb_math.obj"
	-@erase "$(INTDIR)\eb_msg.obj"
	-@erase "$(INTDIR)\eb_npipe.obj"
	-@erase "$(INTDIR)\eb_object.obj"
	-@erase "$(INTDIR)\eb_osver.obj"
	-@erase "$(INTDIR)\eb_process.obj"
	-@erase "$(INTDIR)\eb_prof.obj"
	-@erase "$(INTDIR)\eb_queue.obj"
	-@erase "$(INTDIR)\eb_res.obj"
	-@erase "$(INTDIR)\eb_ring.obj"
	-@erase "$(INTDIR)\eb_sema.obj"
	-@erase "$(INTDIR)\eb_shmem.obj"
	-@erase "$(INTDIR)\eb_str.obj"
	-@erase "$(INTDIR)\eb_strex.obj"
	-@erase "$(INTDIR)\eb_thread.obj"
	-@erase "$(INTDIR)\eb_time.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\eclbse.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ecl_lib_base.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_lib_base.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\eclbse.lib" 
LIB32_OBJS= \
	"$(INTDIR)\eb_base.obj" \
	"$(INTDIR)\eb_bprintf.obj" \
	"$(INTDIR)\eb_docview.obj" \
	"$(INTDIR)\eb_elo.obj" \
	"$(INTDIR)\eb_eloex.obj" \
	"$(INTDIR)\eb_err.obj" \
	"$(INTDIR)\eb_event.obj" \
	"$(INTDIR)\eb_object.obj" \
	"$(INTDIR)\eb_str.obj" \
	"$(INTDIR)\eb_strex.obj" \
	"$(INTDIR)\eb_time.obj" \
	"$(INTDIR)\eb_array.obj" \
	"$(INTDIR)\eb_collect.obj" \
	"$(INTDIR)\eb_list.obj" \
	"$(INTDIR)\eb_map.obj" \
	"$(INTDIR)\eb_geo2d.obj" \
	"$(INTDIR)\eb_math.obj" \
	"$(INTDIR)\eb_clip.obj" \
	"$(INTDIR)\eb_msg.obj" \
	"$(INTDIR)\eb_npipe.obj" \
	"$(INTDIR)\eb_queue.obj" \
	"$(INTDIR)\eb_ring.obj" \
	"$(INTDIR)\eb_sema.obj" \
	"$(INTDIR)\eb_shmem.obj" \
	"$(INTDIR)\eb_cmdarg.obj" \
	"$(INTDIR)\eb_cmdline.obj" \
	"$(INTDIR)\eb_dde.obj" \
	"$(INTDIR)\eb_except.obj" \
	"$(INTDIR)\eb_file.obj" \
	"$(INTDIR)\eb_osver.obj" \
	"$(INTDIR)\eb_process.obj" \
	"$(INTDIR)\eb_prof.obj" \
	"$(INTDIR)\eb_res.obj" \
	"$(INTDIR)\eb_thread.obj"

"$(OUTDIR)\eclbse.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ecl_lib_base - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\eclbsed.lib"


CLEAN :
	-@erase "$(INTDIR)\eb_array.obj"
	-@erase "$(INTDIR)\eb_base.obj"
	-@erase "$(INTDIR)\eb_bprintf.obj"
	-@erase "$(INTDIR)\eb_clip.obj"
	-@erase "$(INTDIR)\eb_cmdarg.obj"
	-@erase "$(INTDIR)\eb_cmdline.obj"
	-@erase "$(INTDIR)\eb_collect.obj"
	-@erase "$(INTDIR)\eb_dde.obj"
	-@erase "$(INTDIR)\eb_docview.obj"
	-@erase "$(INTDIR)\eb_elo.obj"
	-@erase "$(INTDIR)\eb_eloex.obj"
	-@erase "$(INTDIR)\eb_err.obj"
	-@erase "$(INTDIR)\eb_event.obj"
	-@erase "$(INTDIR)\eb_except.obj"
	-@erase "$(INTDIR)\eb_file.obj"
	-@erase "$(INTDIR)\eb_geo2d.obj"
	-@erase "$(INTDIR)\eb_list.obj"
	-@erase "$(INTDIR)\eb_map.obj"
	-@erase "$(INTDIR)\eb_math.obj"
	-@erase "$(INTDIR)\eb_msg.obj"
	-@erase "$(INTDIR)\eb_npipe.obj"
	-@erase "$(INTDIR)\eb_object.obj"
	-@erase "$(INTDIR)\eb_osver.obj"
	-@erase "$(INTDIR)\eb_process.obj"
	-@erase "$(INTDIR)\eb_prof.obj"
	-@erase "$(INTDIR)\eb_queue.obj"
	-@erase "$(INTDIR)\eb_res.obj"
	-@erase "$(INTDIR)\eb_ring.obj"
	-@erase "$(INTDIR)\eb_sema.obj"
	-@erase "$(INTDIR)\eb_shmem.obj"
	-@erase "$(INTDIR)\eb_str.obj"
	-@erase "$(INTDIR)\eb_strex.obj"
	-@erase "$(INTDIR)\eb_thread.obj"
	-@erase "$(INTDIR)\eb_time.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\eclbsed.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ecl_lib_base.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_lib_base.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\eclbsed.lib" 
LIB32_OBJS= \
	"$(INTDIR)\eb_base.obj" \
	"$(INTDIR)\eb_bprintf.obj" \
	"$(INTDIR)\eb_docview.obj" \
	"$(INTDIR)\eb_elo.obj" \
	"$(INTDIR)\eb_eloex.obj" \
	"$(INTDIR)\eb_err.obj" \
	"$(INTDIR)\eb_event.obj" \
	"$(INTDIR)\eb_object.obj" \
	"$(INTDIR)\eb_str.obj" \
	"$(INTDIR)\eb_strex.obj" \
	"$(INTDIR)\eb_time.obj" \
	"$(INTDIR)\eb_array.obj" \
	"$(INTDIR)\eb_collect.obj" \
	"$(INTDIR)\eb_list.obj" \
	"$(INTDIR)\eb_map.obj" \
	"$(INTDIR)\eb_geo2d.obj" \
	"$(INTDIR)\eb_math.obj" \
	"$(INTDIR)\eb_clip.obj" \
	"$(INTDIR)\eb_msg.obj" \
	"$(INTDIR)\eb_npipe.obj" \
	"$(INTDIR)\eb_queue.obj" \
	"$(INTDIR)\eb_ring.obj" \
	"$(INTDIR)\eb_sema.obj" \
	"$(INTDIR)\eb_shmem.obj" \
	"$(INTDIR)\eb_cmdarg.obj" \
	"$(INTDIR)\eb_cmdline.obj" \
	"$(INTDIR)\eb_dde.obj" \
	"$(INTDIR)\eb_except.obj" \
	"$(INTDIR)\eb_file.obj" \
	"$(INTDIR)\eb_osver.obj" \
	"$(INTDIR)\eb_process.obj" \
	"$(INTDIR)\eb_prof.obj" \
	"$(INTDIR)\eb_res.obj" \
	"$(INTDIR)\eb_thread.obj"

"$(OUTDIR)\eclbsed.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ecl_lib_base.dep")
!INCLUDE "ecl_lib_base.dep"
!ELSE 
!MESSAGE Warning: cannot find "ecl_lib_base.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ecl_lib_base - Win32 Release" || "$(CFG)" == "ecl_lib_base - Win32 Debug"
SOURCE=..\..\..\src\base\eb_base.cpp

"$(INTDIR)\eb_base.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_bprintf.cpp

"$(INTDIR)\eb_bprintf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_docview.cpp

"$(INTDIR)\eb_docview.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_elo.cpp

"$(INTDIR)\eb_elo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_eloex.cpp

"$(INTDIR)\eb_eloex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_err.cpp

"$(INTDIR)\eb_err.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_event.cpp

"$(INTDIR)\eb_event.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_object.cpp

"$(INTDIR)\eb_object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_str.cpp

"$(INTDIR)\eb_str.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_strex.cpp

"$(INTDIR)\eb_strex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_time.cpp

"$(INTDIR)\eb_time.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_array.cpp

"$(INTDIR)\eb_array.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_collect.cpp

"$(INTDIR)\eb_collect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_list.cpp

"$(INTDIR)\eb_list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_map.cpp

"$(INTDIR)\eb_map.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_geo2d.cpp

"$(INTDIR)\eb_geo2d.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_math.cpp

"$(INTDIR)\eb_math.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_clip.cpp

"$(INTDIR)\eb_clip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_msg.cpp

"$(INTDIR)\eb_msg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_npipe.cpp

"$(INTDIR)\eb_npipe.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_queue.cpp

"$(INTDIR)\eb_queue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_ring.cpp

"$(INTDIR)\eb_ring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_sema.cpp

"$(INTDIR)\eb_sema.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_shmem.cpp

"$(INTDIR)\eb_shmem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_cmdarg.cpp

"$(INTDIR)\eb_cmdarg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_cmdline.cpp

"$(INTDIR)\eb_cmdline.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_dde.cpp

"$(INTDIR)\eb_dde.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_except.cpp

"$(INTDIR)\eb_except.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_file.cpp

"$(INTDIR)\eb_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_osver.cpp

"$(INTDIR)\eb_osver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_process.cpp

"$(INTDIR)\eb_process.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_prof.cpp

"$(INTDIR)\eb_prof.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_res.cpp

"$(INTDIR)\eb_res.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_thread.cpp

"$(INTDIR)\eb_thread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

