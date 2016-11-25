# Microsoft Developer Studio Generated NMAKE File, Based on ecl_dll_base.dsp
!IF "$(CFG)" == ""
CFG=ecl_dll_base - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. ecl_dll_base - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "ecl_dll_base - Win32 Release" && "$(CFG)" != "ecl_dll_base - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_dll_base.mak" CFG="ecl_dll_base - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ecl_dll_base - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ecl_dll_base - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ecl_dll_base - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\eclbse.dll"


CLEAN :
	-@erase "$(INTDIR)\eb_array.obj"
	-@erase "$(INTDIR)\eb_base.obj"
	-@erase "$(INTDIR)\eb_bprintf.obj"
	-@erase "$(INTDIR)\eb_clip.obj"
	-@erase "$(INTDIR)\eb_cmdarg.obj"
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
	-@erase "$(INTDIR)\eb_sema.obj"
	-@erase "$(INTDIR)\eb_str.obj"
	-@erase "$(INTDIR)\eb_strex.obj"
	-@erase "$(INTDIR)\eb_thread.obj"
	-@erase "$(INTDIR)\eb_time.obj"
	-@erase "$(INTDIR)\es_base.obj"
	-@erase "$(INTDIR)\es_field.obj"
	-@erase "$(INTDIR)\es_filter.obj"
	-@erase "$(INTDIR)\es_query.obj"
	-@erase "$(INTDIR)\es_row.obj"
	-@erase "$(INTDIR)\es_store.obj"
	-@erase "$(INTDIR)\es_var.obj"
	-@erase "$(INTDIR)\et_con.obj"
	-@erase "$(INTDIR)\et_concli.obj"
	-@erase "$(INTDIR)\et_conser.obj"
	-@erase "$(INTDIR)\et_tomate.obj"
	-@erase "$(INTDIR)\et_tools.obj"
	-@erase "$(INTDIR)\ring.obj"
	-@erase "$(INTDIR)\sharedmem.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\eclbse.dll"
	-@erase "$(OUTDIR)\eclbse.exp"
	-@erase "$(OUTDIR)\eclbse.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_BASE_EXPORTS" /Fp"$(INTDIR)\ecl_dll_base.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_dll_base.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\eclbse.pdb" /machine:I386 /out:"$(OUTDIR)\eclbse.dll" /implib:"$(OUTDIR)\eclbse.lib" 
LINK32_OBJS= \
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
	"$(INTDIR)\eb_sema.obj" \
	"$(INTDIR)\ring.obj" \
	"$(INTDIR)\sharedmem.obj" \
	"$(INTDIR)\eb_cmdarg.obj" \
	"$(INTDIR)\eb_dde.obj" \
	"$(INTDIR)\eb_except.obj" \
	"$(INTDIR)\eb_file.obj" \
	"$(INTDIR)\eb_osver.obj" \
	"$(INTDIR)\eb_process.obj" \
	"$(INTDIR)\eb_prof.obj" \
	"$(INTDIR)\eb_res.obj" \
	"$(INTDIR)\eb_thread.obj" \
	"$(INTDIR)\es_base.obj" \
	"$(INTDIR)\es_field.obj" \
	"$(INTDIR)\es_filter.obj" \
	"$(INTDIR)\es_query.obj" \
	"$(INTDIR)\es_row.obj" \
	"$(INTDIR)\es_store.obj" \
	"$(INTDIR)\es_var.obj" \
	"$(INTDIR)\et_con.obj" \
	"$(INTDIR)\et_concli.obj" \
	"$(INTDIR)\et_conser.obj" \
	"$(INTDIR)\et_tomate.obj" \
	"$(INTDIR)\et_tools.obj"

"$(OUTDIR)\eclbse.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\eclbse.dll
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\eclbse.dll"
   copy .\Release\eclbse.dll ..\..\..\bin\win32
	copy .\Release\eclbse.dll ..\..\..\..\..\bin\win32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ecl_dll_base - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\eclbsed.dll"


CLEAN :
	-@erase "$(INTDIR)\eb_array.obj"
	-@erase "$(INTDIR)\eb_base.obj"
	-@erase "$(INTDIR)\eb_bprintf.obj"
	-@erase "$(INTDIR)\eb_clip.obj"
	-@erase "$(INTDIR)\eb_cmdarg.obj"
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
	-@erase "$(INTDIR)\eb_sema.obj"
	-@erase "$(INTDIR)\eb_str.obj"
	-@erase "$(INTDIR)\eb_strex.obj"
	-@erase "$(INTDIR)\eb_thread.obj"
	-@erase "$(INTDIR)\eb_time.obj"
	-@erase "$(INTDIR)\es_base.obj"
	-@erase "$(INTDIR)\es_field.obj"
	-@erase "$(INTDIR)\es_filter.obj"
	-@erase "$(INTDIR)\es_query.obj"
	-@erase "$(INTDIR)\es_row.obj"
	-@erase "$(INTDIR)\es_store.obj"
	-@erase "$(INTDIR)\es_var.obj"
	-@erase "$(INTDIR)\et_con.obj"
	-@erase "$(INTDIR)\et_concli.obj"
	-@erase "$(INTDIR)\et_conser.obj"
	-@erase "$(INTDIR)\et_tomate.obj"
	-@erase "$(INTDIR)\et_tools.obj"
	-@erase "$(INTDIR)\ring.obj"
	-@erase "$(INTDIR)\sharedmem.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\eclbsed.dll"
	-@erase "$(OUTDIR)\eclbsed.exp"
	-@erase "$(OUTDIR)\eclbsed.ilk"
	-@erase "$(OUTDIR)\eclbsed.lib"
	-@erase "$(OUTDIR)\eclbsed.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ECL_DLL_BASE_EXPORTS" /D "_CRTDBG_MAP_ALLOC" /Fp"$(INTDIR)\ecl_dll_base.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_dll_base.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\eclbsed.pdb" /debug /machine:I386 /out:"$(OUTDIR)\eclbsed.dll" /implib:"$(OUTDIR)\eclbsed.lib" /pdbtype:sept 
LINK32_OBJS= \
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
	"$(INTDIR)\eb_sema.obj" \
	"$(INTDIR)\ring.obj" \
	"$(INTDIR)\sharedmem.obj" \
	"$(INTDIR)\eb_cmdarg.obj" \
	"$(INTDIR)\eb_dde.obj" \
	"$(INTDIR)\eb_except.obj" \
	"$(INTDIR)\eb_file.obj" \
	"$(INTDIR)\eb_osver.obj" \
	"$(INTDIR)\eb_process.obj" \
	"$(INTDIR)\eb_prof.obj" \
	"$(INTDIR)\eb_res.obj" \
	"$(INTDIR)\eb_thread.obj" \
	"$(INTDIR)\es_base.obj" \
	"$(INTDIR)\es_field.obj" \
	"$(INTDIR)\es_filter.obj" \
	"$(INTDIR)\es_query.obj" \
	"$(INTDIR)\es_row.obj" \
	"$(INTDIR)\es_store.obj" \
	"$(INTDIR)\es_var.obj" \
	"$(INTDIR)\et_con.obj" \
	"$(INTDIR)\et_concli.obj" \
	"$(INTDIR)\et_conser.obj" \
	"$(INTDIR)\et_tomate.obj" \
	"$(INTDIR)\et_tools.obj"

"$(OUTDIR)\eclbsed.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\eclbsed.dll
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\eclbsed.dll"
   copy .\Debug\eclbsed.dll ..\..\..\bin\win32
	copy .\Debug\eclbsed.dll ..\..\..\..\..\bin\win32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ecl_dll_base.dep")
!INCLUDE "ecl_dll_base.dep"
!ELSE 
!MESSAGE Warning: cannot find "ecl_dll_base.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ecl_dll_base - Win32 Release" || "$(CFG)" == "ecl_dll_base - Win32 Debug"
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


SOURCE=..\..\..\src\base\eb_sema.cpp

"$(INTDIR)\eb_sema.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\ring.cpp

"$(INTDIR)\ring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\sharedmem.cpp

"$(INTDIR)\sharedmem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_cmdarg.cpp

"$(INTDIR)\eb_cmdarg.obj" : $(SOURCE) "$(INTDIR)"
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


SOURCE=..\..\..\src\tom\et_con.cpp

"$(INTDIR)\et_con.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\tom\et_concli.cpp

"$(INTDIR)\et_concli.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\tom\et_conser.cpp

"$(INTDIR)\et_conser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\tom\et_tomate.cpp

"$(INTDIR)\et_tomate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\tom\et_tools.cpp

"$(INTDIR)\et_tools.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

