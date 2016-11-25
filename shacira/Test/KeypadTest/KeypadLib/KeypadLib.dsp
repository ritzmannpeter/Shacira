# Microsoft Developer Studio Project File - Name="KeypadLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=KeypadLib - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "KeypadLib.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "KeypadLib.mak" CFG="KeypadLib - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "KeypadLib - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "KeypadLib - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KeypadLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(QTDIR)\include" /I "..\..\..\Src\GUIFramework\QTFramework" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "KeypadLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Src\GUIFramework\QTFramework" /I "$(QTDIR)\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "KeypadLib - Win32 Release"
# Name "KeypadLib - Win32 Debug"
# Begin Group "Qt"

# PROP Default_Filter ""
# Begin Group "generated"

# PROP Default_Filter ""
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

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_uic_qt_keyboard_layout_german.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\generated\moc_uic_qt_keyboard_layout_standard.cpp
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
# End Group
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h

!IF  "$(CFG)" == "KeypadLib - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard.h...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard.h
InputName=qt_keyboard

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadLib - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard.h...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
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

!IF  "$(CFG)" == "KeypadLib - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_button.h...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_button.h
InputName=qt_keyboard_button

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadLib - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_button.h...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
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

!IF  "$(CFG)" == "KeypadLib - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_input.h...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_input.h
InputName=qt_keyboard_input

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadLib - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_input.h...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
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

!IF  "$(CFG)" == "KeypadLib - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_layout.h...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h
InputName=qt_keyboard_layout

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "KeypadLib - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing qt_keyboard_layout.h...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
InputPath=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout.h
InputName=qt_keyboard_layout

"$(InputDir)\generated\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe "$(InputDir)\$(InputName).h" -o "$(InputDir)\generated\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_german.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_german.ui

!IF  "$(CFG)" == "KeypadLib - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_german.ui...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
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

!ELSEIF  "$(CFG)" == "KeypadLib - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_german.ui...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
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

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_standard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\GUIFramework\QTFramework\Keypads\qt_keyboard_layout_standard.ui

!IF  "$(CFG)" == "KeypadLib - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_standard.ui...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
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

!ELSEIF  "$(CFG)" == "KeypadLib - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - UICing qt_keyboard_layout_standard.ui...
InputDir=\Proj\visu_V_2_0_0\shacira\Src\GUIFramework\QTFramework\Keypads
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
# End Group
# End Target
# End Project
