# Microsoft Developer Studio Project File - Name="Demo2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Demo2 - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Demo2.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Demo2.mak" CFG="Demo2 - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Demo2 - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Demo2 - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Demo2 - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "Widgets\Src\Generated" /I "Widgets\Forms\Generated" /I ".\\" /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\Interface" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QTFramework\CWidgets\Generated" /I "Forms\Generated" /I "Forms" /I "Include" /I "$(SHACIRADIR)\GUIFramework\Generated" /I "." /I "$(SHACIRADIR)\Src\GUIFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Keypads" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Dialogs" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Styles" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\HTML" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Plugins" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Generated" /I "Generated" /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "Widgets" /I "Widgets\Src" /I "$(QTDIR)\include" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\ECL\src" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(SHACIRADIR)\Extern\STL\stlport" /I "$(SHACIRADIR)\Extern\STL\stlport\old_hp" /I "$(SHACIRADIR)\Src\GUIFramework" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Keypads" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\CWidgets" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Dialogs" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Styles" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\HTML" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Plugins" /I "$(SHACIRADIR)\Src\GUIFramework\QT3Framework\Generated" /I "Generated" /I "$(SHACIRADIR)\Extern\STYX\Src\INC" /I "$(SHACIRADIR)\Extern\STYX\Src\LIBBASE" /I "$(SHACIRADIR)\Extern\STYX\Src\MODSTD" /I "Widgets" /I "Widgets\Src" /I "$(QTDIR)\include" /I "$(SHACIRADIR)\Src" /I "$(SHACIRADIR)\Src\Orb" /I "$(SHACIRADIR)\Src\Include" /I "$(SHACIRADIR)\Extern\ECL\src" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /FR /FD /GZ /c
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
# ADD LINK32 $(QTDIR)\lib\qui.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib addidata.lib omnithread32_rtd.lib omniORB407_rtd.lib omniDynamic407_rtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/demod.exe" /pdbtype:sept /libpath:"$(SHACIRADIR)\Extern\STL\lib" /libpath:"$(SHACIRADIR)\Extern\ADDIDATA\lib"
# SUBTRACT LINK32 /force

!ENDIF 

# Begin Target

# Name "Demo2 - Win32 Release"
# Name "Demo2 - Win32 Debug"
# Begin Group "Widgets"

# PROP Default_Filter ""
# End Group
# Begin Group "Programs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Programs\Demo2Program.cpp
# End Source File
# Begin Source File

SOURCE=.\Programs\Demo2Program.h
# End Source File
# End Group
# Begin Group "Functions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Funcs\Demo2.h
# End Source File
# Begin Source File

SOURCE=.\Funcs\Demo2.mdl

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\Demo2.mdl
InputName=Demo2

BuildCmds= \
	mdlc verbose=true input=$(InputPath) \
	copy $(InputPath) ..\..\Demo2Test\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\Demo2.mdl
InputName=Demo2

BuildCmds= \
	mdlc verbose=true input=$(InputPath) \
	copy $(InputPath) ..\..\Demo2Test\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Funcs\Demo2.tab.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\Demo2GUI.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\Demo2GUI.dec

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\Demo2GUI.dec
InputName=Demo2GUI

BuildCmds= \
	mdlc verbose=true input=$(InputPath) class=gui \
	copy $(InputPath) ..\..\Demo2Test\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputDir=.\Funcs
InputPath=.\Funcs\Demo2GUI.dec
InputName=Demo2GUI

BuildCmds= \
	mdlc verbose=true input=$(InputPath) class=gui \
	copy $(InputPath) ..\..\Demo2Test\Model \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Funcs\Demo2GUI.h
# End Source File
# Begin Source File

SOURCE=.\Funcs\Demo2GUI.tab.cpp
# End Source File
# Begin Source File

SOURCE=.\Funcs\Demo2MDL.cpp
# End Source File
# End Group
# Begin Group "Devices"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Devices\cDemo2Device.cpp
# End Source File
# Begin Source File

SOURCE=.\Devices\cDemo2Device.h
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

SOURCE=.\Generated/Demo2Frame.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/Demo2Page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\Demo2Page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\Demo2Page3.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/Demo2Startup.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_Demo2Frame.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_Demo2FrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_Demo2Page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\moc_Demo2Page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated\moc_Demo2Page3.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_Demo2Startup.cpp
# End Source File
# Begin Source File

SOURCE=.\Generated/moc_Demo2StartupImpl.cpp
# End Source File
# End Group
# Begin Group "Forms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Forms\Demo2Frame.ui

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\Demo2Frame.ui
InputName=Demo2Frame

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

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\Demo2Frame.ui
InputName=Demo2Frame

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

SOURCE=.\Forms\Demo2FrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Demo2FrameImpl.h

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\Demo2FrameImpl.h
InputName=Demo2FrameImpl

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "Generated/moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\Demo2FrameImpl.h
InputName=Demo2FrameImpl

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "Generated/moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Forms\Demo2Page1.ui

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\Demo2Page1.ui
InputName=Demo2Page1

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

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\Demo2Page1.ui
InputName=Demo2Page1

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

SOURCE=.\Forms\Demo2Page2.ui

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\Demo2Page2.ui
InputName=Demo2Page2

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

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\Demo2Page2.ui
InputName=Demo2Page2

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

SOURCE=.\Forms\Demo2Page3.ui

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\Demo2Page3.ui
InputName=Demo2Page3

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

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\Demo2Page3.ui
InputName=Demo2Page3

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

SOURCE=.\Forms\Demo2PageList.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Demo2Startup.ui

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputPath=.\Forms\Demo2Startup.ui
InputName=Demo2Startup

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

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputPath=.\Forms\Demo2Startup.ui
InputName=Demo2Startup

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

SOURCE=.\Forms\Demo2StartupImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Forms\Demo2StartupImpl.h

!IF  "$(CFG)" == "Demo2 - Win32 Release"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\Demo2StartupImpl.h
InputName=Demo2StartupImpl

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "Generated/moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Demo2 - Win32 Debug"

# Begin Custom Build
InputDir=.\Forms
InputPath=.\Forms\Demo2StartupImpl.h
InputName=Demo2StartupImpl

"Generated/moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "Generated/moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\Demo2.cpp
# End Source File
# End Target
# End Project
