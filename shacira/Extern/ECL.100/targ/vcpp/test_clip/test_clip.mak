# Microsoft Developer Studio Generated NMAKE File, Based on test_clip.dsp
!IF "$(CFG)" == ""
CFG=test_clip - Win32 Debug
!MESSAGE No configuration specified. Defaulting to test_clip - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "test_clip - Win32 Release" && "$(CFG)" != "test_clip - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test_clip.mak" CFG="test_clip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test_clip - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test_clip - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test_clip - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\clipview.exe"


CLEAN :
	-@erase "$(INTDIR)\eb_base.obj"
	-@erase "$(INTDIR)\eb_clip.obj"
	-@erase "$(INTDIR)\eb_collect.obj"
	-@erase "$(INTDIR)\eb_err.obj"
	-@erase "$(INTDIR)\eb_except.obj"
	-@erase "$(INTDIR)\eb_sema.obj"
	-@erase "$(INTDIR)\eb_str.obj"
	-@erase "$(INTDIR)\eb_thread.obj"
	-@erase "$(INTDIR)\test_clip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\clipview.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "..\..\..\src" /I "." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\test_clip.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_clip.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\clipview.pdb" /machine:I386 /out:"$(OUTDIR)\clipview.exe" 
LINK32_OBJS= \
	"$(INTDIR)\test_clip.obj" \
	"$(INTDIR)\eb_thread.obj" \
	"$(INTDIR)\eb_str.obj" \
	"$(INTDIR)\eb_base.obj" \
	"$(INTDIR)\eb_clip.obj" \
	"$(INTDIR)\eb_sema.obj" \
	"$(INTDIR)\eb_except.obj" \
	"$(INTDIR)\eb_err.obj" \
	"$(INTDIR)\eb_collect.obj"

"$(OUTDIR)\clipview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\clipview.exe
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\clipview.exe"
   copy .\Release\clipview.exe ..\..\..\bin\win32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "test_clip - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\clipview.exe"


CLEAN :
	-@erase "$(INTDIR)\eb_base.obj"
	-@erase "$(INTDIR)\eb_clip.obj"
	-@erase "$(INTDIR)\eb_collect.obj"
	-@erase "$(INTDIR)\eb_err.obj"
	-@erase "$(INTDIR)\eb_except.obj"
	-@erase "$(INTDIR)\eb_sema.obj"
	-@erase "$(INTDIR)\eb_str.obj"
	-@erase "$(INTDIR)\eb_thread.obj"
	-@erase "$(INTDIR)\test_clip.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\clipview.exe"
	-@erase "$(OUTDIR)\clipview.ilk"
	-@erase "$(OUTDIR)\clipview.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\src" /I "." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\test_clip.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\test_clip.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\clipview.pdb" /debug /machine:I386 /out:"$(OUTDIR)\clipview.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\test_clip.obj" \
	"$(INTDIR)\eb_thread.obj" \
	"$(INTDIR)\eb_str.obj" \
	"$(INTDIR)\eb_base.obj" \
	"$(INTDIR)\eb_clip.obj" \
	"$(INTDIR)\eb_sema.obj" \
	"$(INTDIR)\eb_except.obj" \
	"$(INTDIR)\eb_err.obj" \
	"$(INTDIR)\eb_collect.obj"

"$(OUTDIR)\clipview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\clipview.exe
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\clipview.exe"
   copy .\Debug\clipview.exe ..\..\..\bin\win32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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
!IF EXISTS("test_clip.dep")
!INCLUDE "test_clip.dep"
!ELSE 
!MESSAGE Warning: cannot find "test_clip.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "test_clip - Win32 Release" || "$(CFG)" == "test_clip - Win32 Debug"
SOURCE=..\..\..\src\base\demo\test_clip.cpp

"$(INTDIR)\test_clip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_base.cpp

"$(INTDIR)\eb_base.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_clip.cpp

"$(INTDIR)\eb_clip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_collect.cpp

"$(INTDIR)\eb_collect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_err.cpp

"$(INTDIR)\eb_err.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_except.cpp

"$(INTDIR)\eb_except.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_sema.cpp

"$(INTDIR)\eb_sema.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_str.cpp

"$(INTDIR)\eb_str.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\base\eb_thread.cpp

"$(INTDIR)\eb_thread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

