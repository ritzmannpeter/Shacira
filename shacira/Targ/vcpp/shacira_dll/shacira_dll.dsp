# Microsoft Developer Studio Project File - Name="shacira_dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=shacira_dll - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "shacira_dll.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "shacira_dll.mak" CFG="shacira_dll - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "shacira_dll - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "shacira_dll - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "shacira_dll - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "shacira_dll_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\src" /I "..\..\..\src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\ECL\Src" /I "..\..\..\src\Orb" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I "..\..\..\src\Dnc\Legacy" /I "..\..\..\src\Dnc\CarItf" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Extern\SIEMENS\C" /I "..\..\..\Extern\ISYS\Include" /I "..\..\..\Extern\ADDIDATA\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "shacira_dll_EXPORTS" /D "__x86__" /D "__SHACIRA_DLL__" /D "__WIN32__" /D "__NT__" /D "_COS_LIBRARY" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 addidata.lib omnithread31_rt.lib omniORB406_rt.lib omniDynamic406_rt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /dll /machine:I386 /out:"Release/shacira.dll" /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\ADDIDATA\lib" /libpath:"..\..\..\Extern\FALCON\lib"
# Begin Special Build Tool
TargetPath=.\Release\shacira.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ELSEIF  "$(CFG)" == "shacira_dll - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "shacira_dll_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\src" /I "..\..\..\src\Include" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\ECL\Src" /I "..\..\..\src\Orb" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I "..\..\..\src\Dnc\Legacy" /I "..\..\..\src\Dnc\CarItf" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Extern\SIEMENS\C" /I "..\..\..\Extern\ISYS\Include" /I "..\..\..\Extern\ADDIDATA\include" /D "x_CRTDBG_MAP_ALLOC" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "shacira_dll_EXPORTS" /D "__x86__" /D "__SHACIRA_DLL__" /D "__WIN32__" /D "__NT__" /D "_COS_LIBRARY" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 addidata.lib omnithread31_rtd.lib omniORB406_rtd.lib omniDynamic406_rtd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"Debug/shacirad.dll" /pdbtype:sept /libpath:"..\..\..\Extern\STL\lib" /libpath:"..\..\..\Extern\ADDIDATA\lib" /libpath:"..\..\..\Extern\FALCON\lib"
# Begin Special Build Tool
TargetPath=.\Debug\shacirad.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(TargetPath) ..\..\..\bin\win32
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "shacira_dll - Win32 Release"
# Name "shacira_dll - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "System_c"

# PROP Default_Filter ""
# Begin Group "Objects_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cAlarm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cDataChange.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cJobEntry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cJobSpec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectLock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cProgress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cStaticObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cTransferObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cTransientObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cUserInfo.cpp
# End Source File
# End Group
# Begin Group "Sys_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cConvUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cexceptionhnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cFileSystemUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSharedLibrary.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSHFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSockets.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSysProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSystemUtils.cpp
# End Source File
# End Group
# Begin Group "Process_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cCellProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOPCClientProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOPCRequestHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cRequestHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cResources.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cSHClientProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cSHProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cShutDownControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\debug_log.cpp
# End Source File
# End Group
# Begin Group "Threads_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Threads\cAsyncChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Threads\cControlThread.cpp
# End Source File
# End Group
# Begin Group "Database_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cArgument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cBlob.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstInt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstReal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cCurve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFileContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFileVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncDecl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncRef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncRefArg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cInterfaceFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cRefCache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cSHVariant.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cUnitDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVariableValues.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarRef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarRefArg.cpp
# End Source File
# End Group
# Begin Group "PLC_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActProcedure.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cAtomicCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlProcedure.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlStartCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cProcedureLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cStateVariable.cpp
# End Source File
# End Group
# Begin Group "Namespace_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpace.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpaceIterator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpaceNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNodeContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNodeObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cTree.cpp
# End Source File
# End Group
# Begin Group "Comm_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyReceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyRequester.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxySender.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyTable.cpp
# End Source File
# End Group
# Begin Group "Console_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cFileConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cMemoryConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cSocketConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cStandardConsole.cpp
# End Source File
# End Group
# Begin Group "Memory_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cBlockBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cCharRingBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cMemoryPtr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cPtrList.cpp
# End Source File
# End Group
# Begin Group "Config_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cConfigurationObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cPropertyDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cTypeDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cTypeFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cValue.cpp
# End Source File
# End Group
# Begin Group "Channel_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cAdapter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cAdapterFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannelFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannelProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cConnector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cCOSChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cInternalBridge.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cLocalChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cRemoteBridge.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cRemoteChannel.cpp
# End Source File
# End Group
# Begin Group "ClientServer_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cBlockQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSMsg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cInetAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cServerThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cTCPComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPServer.cpp
# End Source File
# End Group
# Begin Group "Structs_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cExtendedObjectRing.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cExtendedObjectRing.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cFlatObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cFlatObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cFloatCurve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cFloatCurve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cGraphicCurve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cGraphicCurve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cShortCurve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cShortCurve.h
# End Source File
# End Group
# Begin Group "Text_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Text\cText.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Text\cText.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Text\cTextTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Text\SystemText.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Text\SystemText.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\System\cCustomFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cIniFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cLiteString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cLiteWString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cLogFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cStringUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cTimeObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cTimeProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cVariant.cpp
# End Source File
# End Group
# Begin Group "Language_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Language\cSDDLParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\cStyxParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shac_int.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shac_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shac_pim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shacira.sty

!IF  "$(CFG)" == "shacira_dll - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Language
InputPath=..\..\..\Src\Language\Shacira.sty

BuildCmds= \
	cd $(InputDir) \
	..\..\bin\win32\styx.exe -makeIMG -makeC -makeINT Shacira \
	..\..\bin\win32\ctoh.exe \
	

"$(InputDir)\shac_int.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_int.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_lim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_lim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_pim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_pim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "shacira_dll - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Language
InputPath=..\..\..\Src\Language\Shacira.sty

BuildCmds= \
	cd $(InputDir) \
	..\..\bin\win32\styx.exe -makeIMG -makeC -makeINT Shacira \
	..\..\bin\win32\ctoh.exe \
	

"$(InputDir)\shac_int.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_int.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_lim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_lim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_pim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shac_pim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Styx_c"

# PROP Default_Filter ""
# Begin Group "Libbase_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\BINIMG.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\BINSET.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\CFG_ABS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\CFG_DFN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\CTX_APP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\GLO_TAB.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\GSTREAM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\HMAP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\HSET.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\LINE_SCN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\LIST.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\LITERAL.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\OTAB.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\PATHES.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\PRIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\PRS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\PRS_ABS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\Ptm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\ptm_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\PTM_PP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SCN_ABS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SCN_BASE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SCN_IO.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SCN_PRE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SINK.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SYMBOLS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SYSBASE0.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SYSBASE1.C
# End Source File
# End Group
# Begin Group "Libutil_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\CHARLIB.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\Cmdlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\COM_GET.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\CTX.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\DATE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\DICT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\DICTS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\HPAT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\INTEGER.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\OLIST.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\Pgm_base.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\PRE.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\RATIONAL.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\TERM.C
# End Source File
# End Group
# Begin Group "Libstyx_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\BNF.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\META_EXP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\META_PRS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\PRS_GEN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\PRS_IO.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\REG_EXP.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\scn_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\STYX_GEN.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\STYX_HDL.C
# End Source File
# End Group
# Begin Group "Modstd_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\MODSTD\GLS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\MODSTD\MEMOSX.C
# End Source File
# End Group
# Begin Group "Gen_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\BIN__CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CCNV_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CDPS_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CMD__CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CMD_INT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CMD_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CMD_PIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CMDA_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CMDD_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\COM_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CPRJ_INT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CPRJ_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CPRJ_PIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CTOH_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\ESTY_INT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\ESTY_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\ESTY_PIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\GENM_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\HPAT_INT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\HPAT_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\HPAT_PIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\LIM__CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\META_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\META_INT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\META_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\META_PIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\PIM__CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\PRDP_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\PTM__CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\REFO_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\REXP_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\STYD_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\STYP_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\STYX_CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\STYX_INT.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\STYX_LIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\STYX_PIM.C
# End Source File
# End Group
# End Group
# Begin Group "Orb_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Orb\cBroker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\cCorbaCellProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\cCosEventChannelProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\Control.idl

!IF  "$(CFG)" == "shacira_dll - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Orb
InputPath=..\..\..\Src\Orb\Control.idl

BuildCmds= \
	omniidl -bcxx -WbBOA -Wba $(InputPath) \
	copy ControlSK.cc $(InputDir)\ControlSK.cpp \
	copy Control.hh $(InputDir)\Control.hh \
	copy ControlDynSK.cc $(InputDir)\ControlDynSK.cpp \
	del Control.hh \
	del ControlSK.cc \
	del ControlDynSK.cc \
	

"$(InputDir)\Control.hh" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\ControlSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\ControlDynSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "shacira_dll - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Orb
InputPath=..\..\..\Src\Orb\Control.idl

BuildCmds= \
	omniidl -bcxx -WbBOA -Wba $(InputPath) \
	copy ControlSK.cc $(InputDir)\ControlSK.cpp \
	copy Control.hh $(InputDir)\Control.hh \
	copy ControlDynSK.cc $(InputDir)\ControlDynSK.cpp \
	del Control.hh \
	del ControlSK.cc \
	del ControlDynSK.cc \
	

"$(InputDir)\Control.hh" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\ControlSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\ControlDynSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CorbaDefinitions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventChannelAdminDynSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventChannelAdminSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventCommDynSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventCommSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosLifeCycleDynSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosLifeCycleSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\EventChannelAdminDynSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\EventChannelAdminSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\OrbUtils.cpp
# End Source File
# End Group
# Begin Group "Client_c"

# PROP Default_Filter ""
# Begin Group "Remotedatabase_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Client\RemoteDatabase\cRemoteContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\RemoteDatabase\cRemoteVar.cpp
# End Source File
# End Group
# Begin Group "Adapters_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cDataChangeAdapter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cDataControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cEventAdapter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cEventControl.cpp
# End Source File
# End Group
# Begin Group "ClientData_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Client\ClientData\cClientData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\ClientData\cClients.cpp
# End Source File
# End Group
# End Group
# Begin Group "Control_c"

# PROP Default_Filter ""
# Begin Group "SerialChannel_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cBridgeControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cCharReceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cMultiplexer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialBridge.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialChannelFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSocketChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSocketReceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cStandardChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\Base\cStandardWin32.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cTCPReceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cVirtualSocketChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cWTNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cWTNodes.cpp
# End Source File
# End Group
# Begin Group "CellProcess_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\CellProcess\cBackupThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\CellProcess\cCellProcess.cpp
# End Source File
# End Group
# Begin Group "Cell_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cCell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cGateway.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cGatewayServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJob.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJobManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJobs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cProgramFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cSCPLProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\iCellObject.cpp
# End Source File
# End Group
# Begin Group "LocalDatabase_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cBBRAMStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cFileStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cLocalContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cLocalVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistenceChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistenceManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistentVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cSubFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cValueBuffer.cpp
# End Source File
# End Group
# Begin Group "Device_c"

# PROP Default_Filter ""
# Begin Group "DigIO_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cAddiStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cDigIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cMemIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cPA150.cpp
# End Source File
# End Group
# Begin Group "Ids"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Ids\cIdsGrabber.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Ids\cIdsGrabber.h
# End Source File
# End Group
# Begin Group "PPCCom_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCSerialComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCServer.cpp
# End Source File
# End Group
# Begin Group "Performance_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\CNTRDATA.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\cPerfDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\cPerformance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\INSTDATA.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\OBJDATA.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\Perfdata.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cBitOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cBlockCache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cCache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cCacheControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cConfigurationDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDeviceFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDigIODevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cElementRefs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cFM2Device.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cGrabberDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cMemoryAddressedDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cNullOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cS7Operator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cStringCache.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\Orb\ControlDynSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\ControlSK.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
