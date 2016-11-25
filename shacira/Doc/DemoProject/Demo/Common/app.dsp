# Microsoft Developer Studio Project File - Name="App" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=App - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "app.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "app.mak" CFG="App - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "App - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "App - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "App - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "Widgets" /I "Widgets\Src" /I "Widgets\Src\Generated" /I "Widgets\Forms\Generated" /I ".\\" /I "$(QTDIR)\include" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\ECL\src" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework" /I "$(SHACIRADIR)\Src\GUIFramework\Interface" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated" /I "Forms\Generated" /I "Forms" /I "Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread2_rt.lib omniORB304_rt.lib omniDynamic304_rt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/demo.exe" /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib"

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "Widgets" /I "Widgets\Src" /I "Widgets\Src\Generated" /I "Widgets\Forms\Generated" /I ".\\" /I "$(QTDIR)\include" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Extern\ECL\src" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework" /I "$(SHACIRADIR)\Src\GUIFramework\Interface" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated" /I "Forms\Generated" /I "Forms" /I "Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread2_rtd.lib omniORB304_rtd.lib omniDynamic304_rtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/demod.exe" /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib"
# SUBTRACT LINK32 /force

!ENDIF 

# Begin Target

# Name "App - Win32 Release"
# Name "App - Win32 Debug"
# Begin Group "Forms_ui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Forms\demoframe.ui

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\demoframe.ui
InputName=demoframe

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\demoframe.ui
InputName=demoframe

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\demostartup.ui

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\demostartup.ui
InputName=demostartup

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\demostartup.ui
InputName=demostartup

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\page1.ui

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\page1.ui
InputName=page1

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\page1.ui
InputName=page1

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\page2.ui

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\page2.ui
InputName=page2

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\page2.ui
InputName=page2

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\page3.ui

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\page3.ui
InputName=page3

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\page3.ui
InputName=page3

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\page4.ui

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\page4.ui
InputName=page4

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\page4.ui
InputName=page4

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o $(InputDir)\Generated\$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\$(InputName).cpp \
	$(QTDIR)\bin\moc $(InputDir)\Generated\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp \
	

"$(InputDir)\Generated\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Forms_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Forms\demoframeimpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\demoframeimpl.h

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\demoframeimpl.h
InputName=demoframeimpl

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\demoframeimpl.h
InputName=demoframeimpl

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\demostartupimpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\demostartupimpl.h

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\demostartupimpl.h
InputName=demostartupimpl

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\demostartupimpl.h
InputName=demostartupimpl

"$(InputDir)\Generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc $(InputDir)\$(InputName).h -o $(InputDir)\Generated\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\pagelist.cpp
# End Source File
# End Group
# Begin Group "Forms_generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Forms\Generated\demoframe.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\demoframe.h
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\demostartup.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\demostartup.h
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\moc_demoframe.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\moc_demoframeimpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\moc_demostartup.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\moc_demostartupimpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\moc_page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\moc_page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\moc_page3.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\moc_page4.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\page1.h
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\page2.h
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\page3.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\page3.h
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\page4.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Generated\page4.h
# End Source File
# End Group
# Begin Group "Widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\Src\dactvalue.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\Src\dframe.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\Src\Generated\moc_dactvalue.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\Src\Generated\moc_dframe.cpp
# End Source File
# End Group
# Begin Group "Programs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Programs\cDemoProgram.cpp
# End Source File
# Begin Source File

SOURCE=.\Programs\cDemoProgram.h
# End Source File
# Begin Source File

SOURCE=.\Programs\CreateProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\CustomBase\cstpgm.cpp
# End Source File
# Begin Source File

SOURCE=.\Programs\EM63Program.cpp
# End Source File
# Begin Source File

SOURCE=.\Programs\EM63Program.h
# End Source File
# End Group
# Begin Group "Functions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\CustomBase\cstguifunc.cpp
# End Source File
# Begin Source File

SOURCE=..\CustomBase\cstmdlfunc.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\demo.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\demo.h
# End Source File
# Begin Source File

SOURCE=.\Funcs\demo.mdl

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\demo.mdl
InputName=demo

BuildCmds= \
	mdlc input=$(InputPath)  header=$(InputDir)\$(InputName).h table=$(InputDir)\$(InputName).tab strings=$(InputDir)\$(InputName).txt \
	copy $(InputPath) $(MOSAICDIR)\MosaicTest\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\demo.mdl
InputName=demo

BuildCmds= \
	mdlc verbose=false input=$(InputPath)  header=$(InputDir)\$(InputName).h table=$(InputDir)\$(InputName).tab strings=$(InputDir)\$(InputName).txt \
	copy $(InputPath) ..\..\DemoTest\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Funcs\Gui.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\GUI.dec

!IF  "$(CFG)" == "App - Win32 Release"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\GUI.dec
InputName=GUI

BuildCmds= \
	mdlc input=$(InputPath)  header=$(InputDir)\$(InputName).h table=$(InputDir)\$(InputName).tab strings=$(InputDir)\$(InputName).txt \
	copy $(InputPath) $(MOSAICDIR)\MosaicTest\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\GUI.dec
InputName=GUI

BuildCmds= \
	mdlc verbose=false input=$(InputPath)  header=$(InputDir)\$(InputName).h table=$(InputDir)\$(InputName).tab strings=$(InputDir)\$(InputName).txt \
	copy $(InputPath) ..\..\DemoTest\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Funcs\GUI.h
# End Source File
# End Group
# Begin Group "Devices"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Devices\cDemoDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\Devices\cDemoDevice.h
# End Source File
# Begin Source File

SOURCE=.\Devices\CreateDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\CustomBase\cstdev.cpp
# End Source File
# End Group
# Begin Group "Dialog_ui"

# PROP Default_Filter ""
# End Group
# Begin Group "Dialog_cpp"

# PROP Default_Filter ""
# End Group
# Begin Group "Dialog_generated"

# PROP Default_Filter ""
# End Group
# Begin Group "Init"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Init\CustomInit.cpp
# End Source File
# End Group
# Begin Group "Text"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Text\CustomText.cpp
# End Source File
# Begin Source File

SOURCE=.\Text\CustomText.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\app.cpp
# End Source File
# Begin Source File

SOURCE=..\CustomBase\configure_app.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Shacira\Src\GUIFramework\QTFramework\CWidgets\ctabwidget.moc

!IF  "$(CFG)" == "App - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ctabwidget.cpp...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\CWidgets
InputPath=..\..\Shacira\Src\GUIFramework\QTFramework\CWidgets\ctabwidget.moc
InputName=ctabwidget

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).cpp" -o "$(InputDir)\$(InputName).moc"

# End Custom Build

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing ctabwidget.cpp...
InputDir=\usr\prj\Shacira\Src\GUIFramework\QTFramework\CWidgets
InputPath=..\..\Shacira\Src\GUIFramework\QTFramework\CWidgets\ctabwidget.moc
InputName=ctabwidget

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).cpp" -o "$(InputDir)\$(InputName).moc"

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
