# Microsoft Developer Studio Project File - Name="version" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=version - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "version.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "version.mak" CFG="version - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "version - Win32 Release" (basierend auf  "Win32 (x86) Generic Project")
!MESSAGE "version - Win32 Debug" (basierend auf  "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "version - Win32 Release"

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

!ELSEIF  "$(CFG)" == "version - Win32 Debug"

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

# Name "version - Win32 Release"
# Name "version - Win32 Debug"
# Begin Group "Version"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\version_Mosaic.in

!IF  "$(CFG)" == "version - Win32 Release"

# Begin Custom Build
InputPath=..\version_Mosaic.in
InputName=version_Mosaic

BuildCmds= \
	SubWCRev $(MOSAICDIR)\Mosaic $(InputPath) $(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h

"$(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(MOSAICDIR)\Mosaic\Common\Init\dummyMosaic.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "version - Win32 Debug"

# Begin Custom Build
InputPath=..\version_Mosaic.in
InputName=version_Mosaic

BuildCmds= \
	SubWCRev $(MOSAICDIR)\Mosaic $(InputPath) $(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h

"$(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(MOSAICDIR)\Mosaic\Common\Init\dummyMosaic.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\MosaicTest\version_MosaicTest.in

!IF  "$(CFG)" == "version - Win32 Release"

# Begin Custom Build
InputPath=..\..\MosaicTest\version_MosaicTest.in
InputName=version_MosaicTest

BuildCmds= \
	SubWCRev $(MOSAICDIR)\MosaicTest $(InputPath) $(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h

"$(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(MOSAICDIR)\Mosaic\Common\Init\dummyMosaicTest.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "version - Win32 Debug"

# Begin Custom Build
InputPath=..\..\MosaicTest\version_MosaicTest.in
InputName=version_MosaicTest

BuildCmds= \
	SubWCRev $(MOSAICDIR)\MosaicTest $(InputPath) $(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h

"$(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(MOSAICDIR)\Mosaic\Common\Init\dummyMosaicTest.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\OmniORB.304\version_OmniORB.in

!IF  "$(CFG)" == "version - Win32 Release"

# Begin Custom Build
InputPath=..\..\OmniORB.304\version_OmniORB.in
InputName=version_OmniORB

BuildCmds= \
	SubWCRev $(ORBDIR) $(InputPath) $(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h

"$(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(MOSAICDIR)\Mosaic\Common\Init\dummyOmniORB.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "version - Win32 Debug"

# Begin Custom Build
InputPath=..\..\OmniORB.304\version_OmniORB.in
InputName=version_OmniORB

BuildCmds= \
	SubWCRev $(ORBDIR) $(InputPath) $(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h -d

"$(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(MOSAICDIR)\Mosaic\Common\Init\dummyOmniORB.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\PPCSps\version_PPCSps.in

!IF  "$(CFG)" == "version - Win32 Release"

# Begin Custom Build
InputPath=..\..\PPCSps\version_PPCSps.in
InputName=version_PPCSps

BuildCmds= \
	SubWCRev $(MOSAICDIR)\PPCSps $(InputPath) $(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h

"$(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(MOSAICDIR)\Mosaic\Common\Init\dummyPPCSps.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "version - Win32 Debug"

# Begin Custom Build
InputPath=..\..\PPCSps\version_PPCSps.in
InputName=version_PPCSps

BuildCmds= \
	SubWCRev $(MOSAICDIR)\PPCSps $(InputPath) $(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h

"$(MOSAICDIR)\Mosaic\Common\Init\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(MOSAICDIR)\Mosaic\Common\Init\dummyPPCSps.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
