# Microsoft Developer Studio Project File - Name="Robot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Robot - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Robot.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Robot.mak" CFG="Robot - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Robot - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Robot - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Robot - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "Widgets\Src\Generated" /I "Widgets\Forms\Generated" /I ".\\" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\Interface" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated" /I "Forms\Generated" /I "Forms" /I "Include" /I "$(SHACIRADIR)\GUIFramework\Generated" /I "." /I "Widgets\Generated" /I "Generated" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Generated" /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "Widgets" /I "Widgets\Src" /I "$(QTDIR)\include" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\ECL\src" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Plugins" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Styles" /I "$(SHACIRADIR)\Src\GUIFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread2_rt.lib omniORB304_rt.lib omniDynamic304_rt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib"

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "Widgets\Generated" /I "Generated" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Generated" /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "Widgets" /I "Widgets\Src" /I "$(QTDIR)\include" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\ECL\src" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Plugins" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Styles" /I "$(SHACIRADIR)\Src\GUIFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".\Devices\Protocol\ .\Devices\VirAs\\" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(QTDIR)\lib\qui.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread32_rtd.lib omniORB407_rtd.lib omniDynamic407_rtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib"
# SUBTRACT LINK32 /force

!ENDIF 

# Begin Target

# Name "Robot - Win32 Release"
# Name "Robot - Win32 Debug"
# Begin Group "Widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\Generated\moc_RobotCurves.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\RobotCurves.cpp
# End Source File
# End Group
# Begin Group "Programs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Programs\RobotProgram.cpp
# End Source File
# Begin Source File

SOURCE=.\Programs\RobotProgram.h
# End Source File
# End Group
# Begin Group "Functions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Funcs\Robot.h
# End Source File
# Begin Source File

SOURCE=.\Funcs\Robot.mdl

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\Robot.mdl
InputName=Robot

BuildCmds= \
	mdlc verbose=true input=$(InputPath) \
	copy $(InputPath) ..\..\RobotTest\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\Robot.mdl
InputName=Robot

BuildCmds= \
	mdlc verbose=true input=$(InputPath) \
	copy $(InputPath) ..\..\RobotTest\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Funcs\Robot.tab.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\RobotGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\RobotGUI.dec

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\RobotGUI.dec
InputName=RobotGUI

BuildCmds= \
	mdlc verbose=true input=$(InputPath) class=gui \
	copy $(InputPath) ..\..\RobotTest\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\RobotGUI.dec
InputName=RobotGUI

BuildCmds= \
	mdlc verbose=true input=$(InputPath) class=gui \
	copy $(InputPath) ..\..\RobotTest\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Funcs\RobotGUI.h
# End Source File
# Begin Source File

SOURCE=.\Funcs\RobotGUI.tab.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\RobotMDL.cpp
# End Source File
# End Group
# Begin Group "Devices"

# PROP Default_Filter ""
# Begin Group "Protocol"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Devices\Protocol\defs.h
# End Source File
# Begin Source File

SOURCE=.\Devices\Protocol\meta.c
# End Source File
# Begin Source File

SOURCE=.\Devices\Protocol\meta.h
# End Source File
# Begin Source File

SOURCE=.\Devices\Protocol\queue_handle.c
# End Source File
# Begin Source File

SOURCE=.\Devices\Protocol\queue_handle.h
# End Source File
# Begin Source File

SOURCE=.\Devices\Protocol\state_machine.c
# End Source File
# Begin Source File

SOURCE=.\Devices\Protocol\state_machine.h
# End Source File
# End Group
# Begin Group "VirAs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Devices\VirAs\asuro_v.c
# End Source File
# Begin Source File

SOURCE=.\Devices\VirAs\leds.c

!IF  "$(CFG)" == "Robot - Win32 Release"

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Devices\VirAs\leds.h
# End Source File
# Begin Source File

SOURCE=.\Devices\VirAs\object_defs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Devices\cCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\Devices\cCommands.h
# End Source File
# Begin Source File

SOURCE=.\Devices\cRobotDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\Devices\cRobotDevice.h
# End Source File
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
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Generated/moc_RobotFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_RobotFrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_RobotPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\moc_RobotPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\moc_RobotPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_RobotStartup.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_RobotStartupImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/RobotFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/RobotPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\RobotPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\RobotPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/RobotStartup.cpp
# End Source File
# End Group
# Begin Group "Forms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Forms\RobotFrame.ui

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\RobotFrame.ui
InputName=RobotFrame

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\RobotFrame.ui
InputName=RobotFrame

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\RobotFrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\RobotFrameImpl.h

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\RobotFrameImpl.h
InputName=RobotFrameImpl

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "Generated/moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\RobotFrameImpl.h
InputName=RobotFrameImpl

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "Generated/moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\RobotPage1.ui

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\RobotPage1.ui
InputName=RobotPage1

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\RobotPage1.ui
InputName=RobotPage1

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\RobotPage2.ui

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\RobotPage2.ui
InputName=RobotPage2

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\RobotPage2.ui
InputName=RobotPage2

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\RobotPage3.ui

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\RobotPage3.ui
InputName=RobotPage3

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\RobotPage3.ui
InputName=RobotPage3

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\RobotPageList.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\RobotStartup.ui

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\RobotStartup.ui
InputName=RobotStartup

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\RobotStartup.ui
InputName=RobotStartup

BuildCmds= \
	$(QTDIR)\bin\uic  $(InputPath) -o Generated/$(InputName).h \
	$(QTDIR)\bin\uic  $(InputPath) -i Generated/$(InputName).h -o Generated/$(InputName).cpp \
	$(QTDIR)\bin\moc Generated/$(InputName).h -o Generated/moc_$(InputName).cpp \
	

"Generated/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\RobotStartupImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\RobotStartupImpl.h

!IF  "$(CFG)" == "Robot - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\RobotStartupImpl.h
InputName=RobotStartupImpl

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "Generated/moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Robot - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\RobotStartupImpl.h
InputName=RobotStartupImpl

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "Generated/moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\Application.cpp
# End Source File
# End Target
# End Project
