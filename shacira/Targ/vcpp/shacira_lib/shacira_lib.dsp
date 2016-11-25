# Microsoft Developer Studio Project File - Name="shacira_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=shacira_lib - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "shacira_lib.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "shacira_lib.mak" CFG="shacira_lib - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "shacira_lib - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "shacira_lib - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "shacira_lib - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\src\System\ClientServer\XMLService\Network" /I "..\..\..\src\System\ClientServer\XMLService\Network\include" /I "..\..\..\src" /I "..\..\..\src\Include" /I "..\..\..\Extern\ECL\Src" /I "..\..\..\src\Orb" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Extern\SIEMENS\C" /I "..\..\..\Extern\ISYS\Include" /I "..\..\..\Extern\ADDIDATA\include" /I "..\..\..\Extern\XERCES\include" /D "NDEBUG" /D "_LIB" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /D "_NO_QT_" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "shacira_lib - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\src\System\ClientServer\XMLService\Network" /I "..\..\..\src\System\ClientServer\XMLService\Network\include" /I "..\..\..\src" /I "..\..\..\src\Include" /I "..\..\..\Extern\ECL\Src" /I "..\..\..\src\Orb" /I "..\..\..\Extern\STYX\Src\INC" /I "..\..\..\Extern\STYX\Src\LIBBASE" /I "..\..\..\Extern\STYX\Src\MODSTD" /I "..\..\..\Extern\STL\stlport" /I "..\..\..\Extern\STL\stlport\old_hp" /I "$(ORBDIR)\include" /I "$(ORBDIR)\include\omniORB4" /I "$(ORBDIR)\include\COS" /I "..\..\..\Extern\FALCON\include" /I "..\..\..\Extern\SIEMENS\C" /I "..\..\..\Extern\ISYS\Include" /I "..\..\..\Extern\ADDIDATA\include" /I "..\..\..\Extern\XERCES\include" /D "_DEBUG" /D "_LIB" /D "_MBCS" /D "__x86__" /D "__WIN32__" /D "_COS_LIBRARY" /D "_NO_QT_" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\shacira_libd.lib"

!ENDIF 

# Begin Target

# Name "shacira_lib - Win32 Release"
# Name "shacira_lib - Win32 Debug"
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

SOURCE=..\..\..\Src\System\Channel\cInternalBridge.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Channel\cInternalBridge.h
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
# Begin Group "XMLService"

# PROP Default_Filter ""
# Begin Group "Network"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\buffer\alloc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\session\asioclient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\driver\asiodriver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\session\asiosession.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\Base\basefuncs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\Base\basefuncs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\framing\binaryframehandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\buffer\bytebuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\buffer\chunkbuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\struct\commstruct..cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\driver\driver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\driver\driverfactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\service\echoservice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\framing\framehandler..cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\service\service.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\session\session.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\driver\sockdriver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\session\socksession.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\Base\system.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\Base\system.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\driver\testxmlservicefactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\framing\trivialframehandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\XML\xmlhandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\XML\xmlhandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\service\xmlservice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\struct\xmlstruct.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\XML\xmlutils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\Network\XML\xmlutils.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\cXmlService.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ClientServer\XMLService\cXmlService.h
# End Source File
# End Group
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

SOURCE=..\..\..\Src\System\Comm\cProxyRequester.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyRequester.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxySender.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxySender.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyService.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Comm\cProxyService.h
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

SOURCE=..\..\..\Src\System\Database\cBinaryObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cBinaryObject.h
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

SOURCE=..\..\..\Src\System\Database\cInterfaceFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\cInterfaceFilter.h
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
# Begin Source File

SOURCE=..\..\..\Src\System\Database\RootContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Database\RootContext.h
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

SOURCE=..\..\..\Src\System\Objects\cProgress.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Objects\cProgress.h
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

SOURCE=..\..\..\Src\System\Process\cOPCClientProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOPCClientProcess.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOPCRequestHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOPCRequestHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cOptions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cRequestHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cRequestHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cResources.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cResources.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cSHClientProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Process\cSHClientProcess.h
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

SOURCE=..\..\..\Src\System\Sys\cAbstractFileSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cAbstractFileSystem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cBufferedFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cBufferedFile.h
# End Source File
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

SOURCE=..\..\..\Src\System\Sys\cexceptionhnd.h
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

SOURCE=..\..\..\Src\System\Sys\cStandardFileSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\Sys\cStandardFileSystem.h
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

SOURCE=..\..\..\Src\System\Text\cText.h
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

SOURCE=..\..\..\Src\System\ApplicationInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\ApplicationInterface.h
# End Source File
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

SOURCE=..\..\..\Src\System\cLiteString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cLiteString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cLiteWString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\System\cLiteWString.h
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
# Begin Source File

SOURCE=..\..\..\Src\Include\safefunctions.h
# End Source File
# End Group
# Begin Group "Control"

# PROP Default_Filter ""
# Begin Group "Cell"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cCell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cCell.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cEM63Program.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cEM63Program.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cEM63Requester.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cEM63Requester.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cGateway.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cGateway.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cGatewayServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cGatewayServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJob.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJob.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJobManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJobManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJobs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cJobs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cProgram.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cProgramFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cProgramFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cSCPLProgram.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Cell\cSCPLProgram.h
# End Source File
# End Group
# Begin Group "Device"

# PROP Default_Filter ""
# Begin Group "DigIO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cAddiStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cAddiStandard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cDigIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cDigIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cMemIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cMemIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cPA150.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\DigIO\cPA150.h
# End Source File
# End Group
# Begin Group "Ids"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Ids\cIdsGrabber.cpp
# End Source File
# End Group
# Begin Group "PPCCom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCClient.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCOperator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCSerialComm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCSerialComm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\PPCCom\cPPCServer.h
# End Source File
# End Group
# Begin Group "Performance"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\CNTRDATA.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\cPerfDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\cPerfDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\cPerformance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\cPerformance.h
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
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\Performance\Perfdata.h
# End Source File
# End Group
# Begin Group "EM63"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cAbortCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cAbortCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cCyclicCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cCyclicCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cDownloadCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cDownloadCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEM63Interface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEM63Interface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEM63Job.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEM63Job.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEM63LogInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEM63LogInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEM63Session.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEM63Session.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEventlogCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cEventlogCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cGetIdCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cGetIdCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cGetInfoCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cGetInfoCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cInterval.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cInterval.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cParamCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cParamCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cPresentationCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cPresentationCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cReportCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cReportCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cSetCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cSetCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cTimeCondition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cTimeCondition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cUploadCmd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\cUploadCmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\EM63\Euromap63.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cBitOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cBitOperator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cBlockCache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cBlockCache.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cCache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cCache.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cCacheControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cCacheControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cConfigurationDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cConfigurationDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDeviceFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDeviceFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDigIODevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cDigIODevice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cElementRefs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cElementRefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cFM2Device.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cFM2Device.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cGrabberDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cGrabberDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cMemoryAddressedDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cMemoryAddressedDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cNullOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cNullOperator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cS7Device.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cS7Device.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cS7Operator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cS7Operator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cSerialDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cSerialDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cStringCache.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\Device\cStringCache.h
# End Source File
# End Group
# Begin Group "CellProcess"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\CellProcess\cBackupThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\CellProcess\cBackupThread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\CellProcess\cCellProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\CellProcess\cCellProcess.h
# End Source File
# End Group
# Begin Group "SerialChannel"

# PROP Default_Filter ""
# Begin Group "Base"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\Base\cStandardBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\Base\cStandardWin32.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cBridgeControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cBridgeControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cCharReceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cCharReceiver.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cMultiplexer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cMultiplexer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialBridge.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialBridge.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialChannelFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSerialChannelFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSocketChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSocketChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSocketReceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cSocketReceiver.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cStandardChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cStandardChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cTCPReceiver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cTCPReceiver.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cVirtualSocketChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cVirtualSocketChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cWTNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cWTNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cWTNodes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\SerialChannel\cWTNodes.h
# End Source File
# End Group
# Begin Group "LocalDatabase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cBBRAMStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cBBRAMStorage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cFileStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cFileStorage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cLocalContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cLocalContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cLocalVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cLocalVariable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistenceChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistenceChannel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistenceManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistenceManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistentVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cPersistentVariable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cStorage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cSubFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cSubFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cValueBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Control\LocalDatabase\cValueBuffer.h
# End Source File
# End Group
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
# Begin Group "ClientData"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Client\ClientData\cClientData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\ClientData\cClientData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\ClientData\cClients.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Client\ClientData\cClients.h
# End Source File
# End Group
# End Group
# Begin Group "Language"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Src\Language\cEM63Parser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\cEM63Parser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\cEM63StyxParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\cEM63StyxParser.h
# End Source File
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

SOURCE=..\..\..\Src\Language\EM63.sty

!IF  "$(CFG)" == "shacira_lib - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Language
InputPath=..\..\..\Src\Language\EM63.sty

BuildCmds= \
	cd $(InputDir) \
	del em63_lim.h \
	del em63_pim.h \
	del em63_int.h \
	..\..\bin\win32\styx.exe -makeIMG -makeC -makeINT EM63 \
	..\..\bin\win32\ctoh.exe \
	

"$(InputDir)\em63_int.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_int.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_lim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_lim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_pim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_pim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "shacira_lib - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Language
InputPath=..\..\..\Src\Language\EM63.sty

BuildCmds= \
	cd $(InputDir) \
	del em63_lim.h \
	del em63_pim.h \
	del em63_int.h \
	..\..\bin\win32\styx.exe -makeIMG -makeC -makeINT EM63 \
	..\..\bin\win32\ctoh.exe \
	

"$(InputDir)\em63_int.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_int.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_lim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_lim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_pim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\em63_pim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\EM63_int.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\em63_int.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\EM63_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\em63_lim.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\EM63_pim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\em63_pim.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shacira.sty

!IF  "$(CFG)" == "shacira_lib - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Language
InputPath=..\..\..\Src\Language\Shacira.sty

BuildCmds= \
	cd $(InputDir) \
	del shacira_lim.h \
	del shacira_pim.h \
	del shacira_int.h \
	..\..\bin\win32\styx.exe -makeIMG -makeC -makeINT Shacira \
	..\..\bin\win32\ctoh.exe \
	

"$(InputDir)\shacira_lim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_lim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_pim.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\shacira_pim.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "shacira_lib - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Language
InputPath=..\..\..\Src\Language\Shacira.sty

BuildCmds= \
	cd $(InputDir) \
	del shacira_lim.h \
	del shacira_pim.h \
	del shacira_int.h \
	..\..\bin\win32\styx.exe -makeIMG -makeC -makeINT Shacira \
	..\..\bin\win32\ctoh.exe \
	

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

SOURCE=..\..\..\Src\Language\shacira_int.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shacira_lim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\shacira_lim.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\Shacira_pim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Src\Language\shacira_pim.h
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

!IF  "$(CFG)" == "shacira_lib - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Orb
InputPath=..\..\..\Src\Orb\Control.idl
InputName=Control

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

!ELSEIF  "$(CFG)" == "shacira_lib - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Orb
InputPath=..\..\..\Src\Orb\Control.idl
InputName=Control

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

!IF  "$(CFG)" == "shacira_lib - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Orb
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

!ELSEIF  "$(CFG)" == "shacira_lib - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Orb
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

!IF  "$(CFG)" == "shacira_lib - Win32 Release"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Orb
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

!ELSEIF  "$(CFG)" == "shacira_lib - Win32 Debug"

# Begin Custom Build
InputDir=\Mosaic_Qt338\Shacira_Trunk\Src\Orb
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

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\CTX_DFN.H
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\CTX_IMP.H
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

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\PRS_DFN.H
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\PRS_IMP.H
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

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SCN_IMP.H
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

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\STANDARD.H
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\STYCONF0.H
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SYMBOLS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SYSBASE0.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\INC\sysbase0.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SYSBASE1.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBBASE\SYSCBHDL.H
# End Source File
# End Group
# Begin Group "Libutil"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\CHARLIB.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\COM_GET.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\CTX.C
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

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\OLIST.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBUTIL\Pgm_base.c
# End Source File
# End Group
# Begin Group "Libstyx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\LIBSTYX\PRS_GEN.C
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
# End Group
# Begin Group "Modstd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\MODSTD\GLS.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\MODSTD\MEMOSX.C
# End Source File
# End Group
# Begin Group "Gen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\CCNV_LIM.C
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

SOURCE=..\..\..\Extern\STYX\src\GEN\CTOH_CIM.C
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

SOURCE=..\..\..\Extern\STYX\src\GEN\PIM__CIM.C
# End Source File
# Begin Source File

SOURCE=..\..\..\Extern\STYX\src\GEN\PTM__CIM.C
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
