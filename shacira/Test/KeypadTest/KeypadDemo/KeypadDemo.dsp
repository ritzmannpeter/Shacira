# Microsoft Developer Studio Project File - Name="KeypadDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KeypadDemo - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "KeypadDemo.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "KeypadDemo.mak" CFG="KeypadDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "KeypadDemo - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "KeypadDemo - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(QTDIR)\include" /I "..\..\..\Src\GUIFramework\QTFramework" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winspool.lib winmm.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Src\GUIFramework\QTFramework" /I "$(QTDIR)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winspool.lib winmm.lib $(QTDIR)\lib\qt-mt$(QTVERSION).lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "KeypadDemo - Win32 Release"
# Name "KeypadDemo - Win32 Debug"
# Begin Group "Qt"

# PROP Default_Filter ""
# Begin Group "generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\generated\moc_keyboardmodal.cpp
# End Source File
# Begin Source File

SOURCE=.\generated\moc_keypaddemodialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboard_layout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keyboardalpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_qt_keypadnumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\generated\moc_uic_keyboardmodal.cpp
# End Source File
# Begin Source File

SOURCE=.\generated\moc_uic_keypaddemodialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_uic_qt_keyboard_layout_german.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_uic_qt_keyboard_layout_standard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_uic_qt_keyboardalpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_uic_qt_keypadnumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\generated\uic_keyboardmodal.cpp
# End Source File
# Begin Source File

SOURCE=.\generated\uic_keyboardmodal.h
# End Source File
# Begin Source File

SOURCE=.\generated\uic_keypaddemodialog.cpp
# End Source File
# Begin Source File

SOURCE=.\generated\uic_keypaddemodialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\uic_qt_keyboard_layout_german.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\uic_qt_keyboard_layout_german.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\uic_qt_keyboard_layout_standard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\uic_qt_keyboard_layout_standard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\uic_qt_keyboardalpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\uic_qt_keyboardalpha.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\uic_qt_keypadnumeric.cpp
# End Source File
# End Group
# Begin Group "QTFramework"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\property_interface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h
InputName=qt_keyboard

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h
InputName=qt_keyboard

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_button.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h
InputName=qt_keyboard_button

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_button.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h
InputName=qt_keyboard_button

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.h

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_input.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.h
InputName=qt_keyboard_input

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_input.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.h
InputName=qt_keyboard_input

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_layout.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h
InputName=qt_keyboard_layout

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_layout.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h
InputName=qt_keyboard_layout

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_german.ui

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_german.ui...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_german.ui
InputName=qt_keyboard_layout_german

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_german.ui...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_german.ui
InputName=qt_keyboard_layout_german

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_standard.ui

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_standard.ui...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_standard.ui
InputName=qt_keyboard_layout_standard

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_standard.ui...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_standard.ui
InputName=qt_keyboard_layout_standard

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.h

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboardalpha.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.h
InputName=qt_keyboardalpha

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboardalpha.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.h
InputName=qt_keyboardalpha

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.ui

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboardalpha.ui...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.ui
InputName=qt_keyboardalpha

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboardalpha.ui...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboardalpha.ui
InputName=qt_keyboardalpha

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.h

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keypadnumeric.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.h
InputName=qt_keypadnumeric

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keypadnumeric.h...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.h
InputName=qt_keypadnumeric

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.ui

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keypadnumeric.ui...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.ui
InputName=qt_keypadnumeric

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keypadnumeric.ui...
InputDir=\Proj\visu_trunk\Shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keypadnumeric.ui
InputName=qt_keypadnumeric

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_number_validator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_number_validator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_property_widget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_property_widget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_string_validator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_string_validator.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\keyboardmodal.cpp
# End Source File
# Begin Source File

SOURCE=.\keyboardmodal.h

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing keyboardmodal.h...
InputDir=.
InputPath=.\keyboardmodal.h
InputName=keyboardmodal

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing keyboardmodal.h...
InputDir=.
InputPath=.\keyboardmodal.h
InputName=keyboardmodal

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\keyboardmodal.ui

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing keyboardmodal.ui...
InputDir=.
InputPath=.\keyboardmodal.ui
InputName=keyboardmodal

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing keyboardmodal.ui...
InputDir=.
InputPath=.\keyboardmodal.ui
InputName=keyboardmodal

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\keypaddemodialog.cpp
# End Source File
# Begin Source File

SOURCE=.\keypaddemodialog.h

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing keypaddemodialog.h...
InputDir=.
InputPath=.\keypaddemodialog.h
InputName=keypaddemodialog

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing keypaddemodialog.h...
InputDir=.
InputPath=.\keypaddemodialog.h
InputName=keypaddemodialog

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\keypaddemodialog.ui

!IF  "$(CFG)" == "KeypadDemo - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing keypaddemodialog.ui...
InputDir=.
InputPath=.\keypaddemodialog.ui
InputName=keypaddemodialog

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadDemo - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing keypaddemodialog.ui...
InputDir=.
InputPath=.\keypaddemodialog.ui
InputName=keypaddemodialog

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\generated\uic_$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i uic_$(InputName).h -o $(InputDir)\generated\uic_$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\generated\uic_$(InputName).h -o $(InputDir)\generated\moc_uic_$(InputName).cpp \
	

"$(InputDir)\generated\uic_$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\generated\moc_uic_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Group
# End Target
# End Project
