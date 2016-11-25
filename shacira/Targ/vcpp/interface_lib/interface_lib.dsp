# Microsoft Developer Studio Project File - Name="interface_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=interface_lib - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "interface_lib.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "interface_lib.mak" CFG="interface_lib - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "interface_lib - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "interface_lib - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "interface_lib - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\src" /I "..\..\..\src\Include" /I "..\..\..\Extern\ECL\Src" /I "..\..\..\src\Orb" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Extern\SIEMENS\C" /I "..\..\..\Extern\ISYS\Include" /I "..\..\..\Extern\ADDIDATA\include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /D "_NO_QT_" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "interface_lib - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\src" /I "..\..\..\src\Include" /I "..\..\..\Extern\ECL\Src" /I "..\..\..\src\Orb" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Extern\SIEMENS\C" /I "..\..\..\Extern\ISYS\Include" /I "..\..\..\Extern\ADDIDATA\include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /D "_NO_QT_" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\interface_libd.lib"

!ENDIF 

# Begin Target

# Name "interface_lib - Win32 Release"
# Name "interface_lib - Win32 Debug"
# Begin Group "System"

# PROP Default_Filter ""
# Begin Group "Channel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cAdapter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cAdapter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cAdapterFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cAdapterFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannelFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannelFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannelProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cChannelProxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cConnector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cConnector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cCOSChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cCOSChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cLocalChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cLocalChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cRemoteBridge.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cRemoteBridge.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cRemoteChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cRemoteChannel.h
# End Source File
# End Group
# Begin Group "ClientServer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cBlockQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cBlockQueue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cClient.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSAddress.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSComm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSMsg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cCSMsg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cInetAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cInetAddress.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cServerThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cServerThread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cTCPComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cTCPComm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPClient.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPComm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\cUDPServer.h
# End Source File
# End Group
# Begin Group "PLC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActLine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActProcedure.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActProcedure.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cActProgram.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cAtomicCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cAtomicCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlProcedure.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlProcedure.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlProgram.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlStartCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlStartCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cControlState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cProcedureLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cProcedureLine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cStateVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\PLC\cStateVariable.h
# End Source File
# End Group
# Begin Group "Comm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyReceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyReceiver.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxySender.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxySender.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyTable.h
# End Source File
# End Group
# Begin Group "Config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cConfiguration.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cConfigurationObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cConfigurationObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cPropertyDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cPropertyDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cTypeDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cTypeDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cTypeFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Config\cTypeFactory.h
# End Source File
# End Group
# Begin Group "Console"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cConsole.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cFileConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cFileConsole.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cMemoryConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cMemoryConsole.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cSocketConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cSocketConsole.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cStandardConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Console\cStandardConsole.h
# End Source File
# End Group
# Begin Group "Database"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cArgument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cArgument.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cBlob.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cBlob.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstInt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstInt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstReal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstReal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cConstString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cCurve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cCurve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFileContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFileContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFileVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFileVariable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncDecl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncDecl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncRef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncRef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncRefArg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cFuncRefArg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cMapping.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cMapping.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cRefCache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cRefCache.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cSHVariant.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cSHVariant.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cUnitDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cUnitDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarDef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarDef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVariable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVariableValues.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVariableValues.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarRef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarRef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarRefArg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cVarRefArg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\FuncSpecs.h
# End Source File
# End Group
# Begin Group "Memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cBlockBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cBlockBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cCharRingBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cCharRingBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cMemoryPtr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cMemoryPtr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cPtrList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Memory\cPtrList.h
# End Source File
# End Group
# Begin Group "Namespace"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpace.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpace.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpaceIterator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpaceIterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpaceNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNameSpaceNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNodeContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNodeContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNodeObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cNodeObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Namespace\cTree.h
# End Source File
# End Group
# Begin Group "Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cAlarm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cAlarm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cCorbaProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cCorbaProxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cDataChange.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cDataChange.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cJobEntry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cJobEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cJobSpec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cJobSpec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectLock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectLock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cObjectQueue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cProtocol.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cProxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cStaticObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cStaticObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cTransferObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cTransferObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cTransientObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cTransientObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cUserInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cUserInfo.h
# End Source File
# End Group
# Begin Group "Process"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cCellProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cCellProxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOptions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cResources.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cResources.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cSHProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cSHProcess.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cShutDownControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cShutDownControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\debug_log.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\debug_log.h
# End Source File
# End Group
# Begin Group "Structs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cDataFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cDataFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cDataset.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cDataset.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cDatasetDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Structs\cDatasetDirectory.h
# End Source File
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
# Begin Group "Sys"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cConvUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cConvUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cexceptionhnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cFileSystemUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cFileSystemUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSharedLibrary.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSHFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSHFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSockets.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSockets.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSysProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSysProcess.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSystemUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cSystemUtils.h
# End Source File
# End Group
# Begin Group "Text"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Text\cText.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Text\cTextTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Text\cTextTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Text\SystemText.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Text\SystemText.h
# End Source File
# End Group
# Begin Group "Threads"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\Threads\cAsyncChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Threads\cAsyncChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Threads\cControlThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Threads\cControlThread.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\System\cCustomFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cCustomFunctions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cIniFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cIniFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cLogFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cLogFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cStringUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cStringUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cTimeObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cTimeObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cTokenizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cValue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cVariant.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cVariant.h
# End Source File
# End Group
# Begin Group "Client"

# PROP Default_Filter ""
# Begin Group "Adapters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cDataChangeAdapter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cDataChangeAdapter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cDataControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cDataControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cEventAdapter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cEventAdapter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cEventControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\Adapters\cEventControl.h
# End Source File
# End Group
# Begin Group "RemoteDatabase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Client\RemoteDatabase\cRemoteContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\RemoteDatabase\cRemoteContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\RemoteDatabase\cRemoteVar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\RemoteDatabase\cRemoteVar.h
# End Source File
# End Group
# Begin Group "GatewayInterface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Client\GatewayInterface\cGatewayClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\GatewayInterface\cGatewayClient.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\GatewayInterface\cGatewayInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\GatewayInterface\cGatewayInterface.h
# End Source File
# End Group
# End Group
# Begin Group "Language"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Language\cSDDLParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\cSDDLParser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\cStyxParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\cStyxParser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shacira.sty

!IF  "$(CFG)" == "interface_lib - Win32 Release"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Language
InputPath=..\..\..\Src\Language\Shacira.sty

BuildCmds= \
	cd $(InputDir) \
	del shacira_lim.h \
	del shacira_pim.h \
	del shacira_int.h \
	..\..\bin\win32\styx.exe -makeIMG -makeC -makeINT Shacira \
	..\..\bin\win32\ctoh.exe \
	

"$(InputDir)\shacira_int.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_int.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_lim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_lim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_pim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_pim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interface_lib - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Language
InputPath=..\..\..\Src\Language\Shacira.sty

BuildCmds= \
	cd $(InputDir) \
	del shacira_lim.h \
	del shacira_pim.h \
	del shacira_int.h \
	..\..\bin\win32\styx.exe -makeIMG -makeC -makeINT Shacira \
	..\..\bin\win32\ctoh.exe \
	

"$(InputDir)\shacira_int.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_int.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_lim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_lim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_pim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_pim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shacira_int.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shacira_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shacira_pim.c
# End Source File
# End Group
# Begin Group "Orb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Orb\cBroker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\cBroker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\cCorbaCellProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\cCorbaCellProxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\cCosEventChannelProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\cCosEventChannelProxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\Control.hh
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\Control.idl

!IF  "$(CFG)" == "interface_lib - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\Orb
InputPath=..\..\..\Src\Orb\Control.idl

BuildCmds= \
	$(ORBDIR)\bin\x86_win32\omniidl -C$(InputDir) -I$(InputDir) -bcxx -WbBOA -Wba $(InputPath) \
	copy $(InputDir)\$(InputName)SK.cc $(InputDir)\$(InputName)SK.cpp \
	copy $(InputDir)\$(InputName)DynSK.cc $(InputDir)\$(InputName)DynSK.cpp \
	del $(InputDir)\$(InputName)SK.cc \
	del $(InputDir)\$(InputName)DynSK.cc \
	

"$(InputDir)\Control.hh" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)SK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)DynSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interface_lib - Win32 Debug"

# Begin Custom Build
InputDir=\usr\prj\Shacira\Src\Orb
InputPath=..\..\..\Src\Orb\Control.idl

BuildCmds= \
	$(ORBDIR)\bin\x86_win32\omniidl -C$(InputDir) -I$(InputDir) -bcxx -WbBOA -Wba $(InputPath) \
	copy $(InputDir)\$(InputName)SK.cc $(InputDir)\$(InputName)SK.cpp \
	copy $(InputDir)\$(InputName)DynSK.cc $(InputDir)\$(InputName)DynSK.cpp \
	del $(InputDir)\$(InputName)SK.cc \
	del $(InputDir)\$(InputName)DynSK.cc \
	

"$(InputDir)\$(InputName).hh" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)SK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)DynSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\ControlDynSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\ControlSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CorbaDefinitions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CorbaDefinitions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventChannelAdmin.hh
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventChannelAdmin.idl

!IF  "$(CFG)" == "interface_lib - Win32 Release"

!ELSEIF  "$(CFG)" == "interface_lib - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\Orb
InputPath=..\..\..\Src\Orb\CosEventChannelAdmin.idl
InputName=CosEventChannelAdmin

BuildCmds= \
	$(ORBDIR)\bin\x86_win32\omniidl -C$(InputDir) -I$(InputDir) -bcxx -WbBOA -Wba $(InputPath) \
	copy $(InputDir)\$(InputName)SK.cc $(InputDir)\$(InputName)SK.cpp \
	copy $(InputDir)\$(InputName)DynSK.cc $(InputDir)\$(InputName)DynSK.cpp \
	del $(InputDir)\$(InputName)SK.cc \
	del $(InputDir)\$(InputName)DynSK.cc \
	

"$(InputDir)\$(InputName).hh" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)SK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)DynSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventChannelAdminDynSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventChannelAdminSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventComm.hh
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventComm.idl

!IF  "$(CFG)" == "interface_lib - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\Orb
InputPath=..\..\..\Src\Orb\CosEventComm.idl
InputName=CosEventComm

BuildCmds= \
	$(ORBDIR)\bin\x86_win32\omniidl -C$(InputDir) -I$(InputDir) -bcxx -WbBOA -Wba $(InputPath) \
	copy $(InputDir)\$(InputName)SK.cc $(InputDir)\$(InputName)SK.cpp \
	copy $(InputDir)\$(InputName)DynSK.cc $(InputDir)\$(InputName)DynSK.cpp \
	del $(InputDir)\$(InputName)SK.cc \
	del $(InputDir)\$(InputName)DynSK.cc \
	

"$(InputDir)\$(InputName).hh" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)SK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)DynSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "interface_lib - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira\Src\Orb
InputPath=..\..\..\Src\Orb\CosEventComm.idl
InputName=CosEventComm

BuildCmds= \
	$(ORBDIR)\bin\x86_win32\omniidl -C$(InputDir) -I$(InputDir) -bcxx -WbBOA -Wba $(InputPath) \
	copy $(InputDir)\$(InputName)SK.cc $(InputDir)\$(InputName)SK.cpp \
	copy $(InputDir)\$(InputName)DynSK.cc $(InputDir)\$(InputName)DynSK.cpp \
	del $(InputDir)\$(InputName)SK.cc \
	del $(InputDir)\$(InputName)DynSK.cc \
	

"$(InputDir)\$(InputName).hh" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)SK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName)DynSK.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventCommDynSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\CosEventCommSK.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\iCellObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\iCellObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Orb\OrbUtils.cpp
# End Source File
# End Group
# Begin Group "Styx"

# PROP Default_Filter ""
# Begin Group "Libbase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\binimg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\binset.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\cfg_abs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\cfg_dfn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\ctx_app.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\glo_tab.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\gstream.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\hmap.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\hset.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\line_scn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\list.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\literal.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\otab.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\pathes.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\prim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\prs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\prs_abs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\prs_io.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\ptm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\ptm_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\ptm_pp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\scn_abs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\scn_base.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\scn_io.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\scn_pre.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\sink.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\symbols.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\sysbase0.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libbase\sysbase1.c
# End Source File
# End Group
# Begin Group "Libutil"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libutil\charlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libutil\com_get.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libutil\ctx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libutil\dict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libutil\dicts.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libutil\hpat.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libutil\olist.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libutil\pgm_base.c
# End Source File
# End Group
# Begin Group "Libstyx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libstyx\prs_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libstyx\reg_exp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libstyx\scn_gen.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\libstyx\styx_gen.c
# End Source File
# End Group
# Begin Group "Modstd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\modstd\gls.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\modstd\memosx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\MODSTD\STDOSX.H
# End Source File
# End Group
# Begin Group "Gen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\ccnv_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\cmd_int.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\cmd_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\cmd_pim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\ctoh_cim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\hpat_int.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\hpat_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\hpat_pim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\lim__cim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\pim__cim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\ptm__cim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\rexp_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\styd_cim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\styp_cim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\styx_cim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\styx_int.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\styx_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\gen\styx_pim.c
# End Source File
# End Group
# End Group
# Begin Group "ecl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\base.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\base_ex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\bprintf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\bprintf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\collect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\collect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\system\enum_procs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\system\enum_procs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\error.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\error.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\event.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\event.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\logfile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\logfile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\map.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\map.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\message.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\message.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn_local.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn_local.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn_mslot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn_mslot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn_npipe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn_npipe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn_queue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\mn_queue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\namedpipe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\namedpipe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\object.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\osbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\osbase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\osversion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\osversion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\process.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\process.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\profile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\profile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\queue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\queue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\ring.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\ring.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\semaphore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\semaphore.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\sharedmem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\sharedmem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\singleton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\snprintf\snprintf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\driver\snprintf\snprintf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\string.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\string_ex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\string_ex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\thread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\ECL\src\base\thread.h
# End Source File
# End Group
# End Target
# End Project
