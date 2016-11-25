# Microsoft Developer Studio Project File - Name="_make_all" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=_make_all - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "_make_all.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "_make_all.mak" CFG="_make_all - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "_make_all - Win32 Release" (basierend auf  "Win32 (x86) Generic Project")
!MESSAGE "_make_all - Win32 Debug" (basierend auf  "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "_make_all - Win32 Release"

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

!ELSEIF  "$(CFG)" == "_make_all - Win32 Debug"

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

!ENDIF 

# Begin Target

# Name "_make_all - Win32 Release"
# Name "_make_all - Win32 Debug"
# Begin Group "copy_dll"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\ADDIDATA\bin\Addi_int.dll

!IF  "$(CFG)" == "_make_all - Win32 Release"

!ELSEIF  "$(CFG)" == "_make_all - Win32 Debug"

# Begin Custom Build - Copy bin\win32\$(InputName).dll from addidata
InputPath=..\..\..\Extern\ADDIDATA\bin\Addi_int.dll
InputName=Addi_int

"..\..\..\bin\win32\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\bin\win32\$(InputName).dll >nul

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ADDIDATA\bin\ADDIDATA.DLL

!IF  "$(CFG)" == "_make_all - Win32 Release"

!ELSEIF  "$(CFG)" == "_make_all - Win32 Debug"

# Begin Custom Build - Copy bin\win32\$(InputName).dll from addidata
InputPath=..\..\..\Extern\ADDIDATA\bin\ADDIDATA.DLL
InputName=ADDIDATA

"..\..\..\bin\win32\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\bin\win32\$(InputName).dll >nul

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ADDIDATA\bin\ADDIKERN.DLL

!IF  "$(CFG)" == "_make_all - Win32 Release"

!ELSEIF  "$(CFG)" == "_make_all - Win32 Debug"

# Begin Custom Build - Copy bin\win32\$(InputName).dll from addidata
InputPath=..\..\..\Extern\ADDIDATA\bin\ADDIKERN.DLL
InputName=ADDIKERN

"..\..\..\bin\win32\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) ..\..\..\bin\win32\$(InputName).dll >nul

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
