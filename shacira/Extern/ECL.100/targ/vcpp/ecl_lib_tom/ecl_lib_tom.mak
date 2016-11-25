# Microsoft Developer Studio Generated NMAKE File, Based on ecl_lib_tom.dsp
!IF "$(CFG)" == ""
CFG=ecl_lib_tom - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. ecl_lib_tom - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "ecl_lib_tom - Win32 Release" && "$(CFG)" != "ecl_lib_tom - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "ecl_lib_tom.mak" CFG="ecl_lib_tom - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "ecl_lib_tom - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "ecl_lib_tom - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "ecl_lib_tom - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ecl_lib_tom.lib"


CLEAN :
	-@erase "$(INTDIR)\et_con.obj"
	-@erase "$(INTDIR)\et_concli.obj"
	-@erase "$(INTDIR)\et_conser.obj"
	-@erase "$(INTDIR)\et_tomate.obj"
	-@erase "$(INTDIR)\et_tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ecl_lib_tom.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ecl_lib_tom.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_lib_tom.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ecl_lib_tom.lib" 
LIB32_OBJS= \
	"$(INTDIR)\et_con.obj" \
	"$(INTDIR)\et_concli.obj" \
	"$(INTDIR)\et_conser.obj" \
	"$(INTDIR)\et_tomate.obj" \
	"$(INTDIR)\et_tools.obj"

"$(OUTDIR)\ecl_lib_tom.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ecl_lib_tom - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ecl_lib_tom.lib"


CLEAN :
	-@erase "$(INTDIR)\et_con.obj"
	-@erase "$(INTDIR)\et_concli.obj"
	-@erase "$(INTDIR)\et_conser.obj"
	-@erase "$(INTDIR)\et_tomate.obj"
	-@erase "$(INTDIR)\et_tools.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ecl_lib_tom.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ecl_lib_tom.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ecl_lib_tom.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ecl_lib_tom.lib" 
LIB32_OBJS= \
	"$(INTDIR)\et_con.obj" \
	"$(INTDIR)\et_concli.obj" \
	"$(INTDIR)\et_conser.obj" \
	"$(INTDIR)\et_tomate.obj" \
	"$(INTDIR)\et_tools.obj"

"$(OUTDIR)\ecl_lib_tom.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("ecl_lib_tom.dep")
!INCLUDE "ecl_lib_tom.dep"
!ELSE 
!MESSAGE Warning: cannot find "ecl_lib_tom.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ecl_lib_tom - Win32 Release" || "$(CFG)" == "ecl_lib_tom - Win32 Debug"
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

