//## begin module%3DD8B83600E4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD8B83600E4.cm

//## begin module%3DD8B83600E4.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3DD8B83600E4.cp

//## Module: cEventChannelWrapper%3DD8B83600E4; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Apps\ChannelMgr\cEventChannelWrapper.cpp

//## begin module%3DD8B83600E4.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DD8B83600E4.additionalIncludes

//## begin module%3DD8B83600E4.includes preserve=yes
//## end module%3DD8B83600E4.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cSystemUtils
#include "System/Sys/cSystemUtils.h"
// cSysProcess
#include "System/Sys/cSysProcess.h"
// cCosEventChannelProxy
#include "Orb/cCosEventChannelProxy.h"
// cEventChannelWrapper
#include "Apps/ChannelMgr/cEventChannelWrapper.h"
// cEventChannelManager
#include "Apps/ChannelMgr/cEventChannelManager.h"
//## begin module%3DD8B83600E4.additionalDeclarations preserve=yes
//## end module%3DD8B83600E4.additionalDeclarations


// Class cEventChannelWrapper 











cEventChannelWrapper::cEventChannelWrapper()
  //## begin cEventChannelWrapper::cEventChannelWrapper%.hasinit preserve=no
      : _Active(false), _ProcessId(0), _Process(NULL), _ChannelProcess(NULL)
  //## end cEventChannelWrapper::cEventChannelWrapper%.hasinit
  //## begin cEventChannelWrapper::cEventChannelWrapper%.initialization preserve=yes
  //## end cEventChannelWrapper::cEventChannelWrapper%.initialization
{
  //## begin cEventChannelWrapper::cEventChannelWrapper%.body preserve=yes
_ASSERT_UNCOND
  //## end cEventChannelWrapper::cEventChannelWrapper%.body
}

cEventChannelWrapper::cEventChannelWrapper(const cEventChannelWrapper &right)
  //## begin cEventChannelWrapper::cEventChannelWrapper%copy.hasinit preserve=no
      : _Active(false), _ProcessId(0), _Process(NULL), _ChannelProcess(NULL)
  //## end cEventChannelWrapper::cEventChannelWrapper%copy.hasinit
  //## begin cEventChannelWrapper::cEventChannelWrapper%copy.initialization preserve=yes
  //## end cEventChannelWrapper::cEventChannelWrapper%copy.initialization
{
  //## begin cEventChannelWrapper::cEventChannelWrapper%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEventChannelWrapper::cEventChannelWrapper%copy.body
}

cEventChannelWrapper::cEventChannelWrapper (cEventChannelManager *process, cConfigurationObject *config_obj)
  //## begin cEventChannelWrapper::cEventChannelWrapper%1037610185.hasinit preserve=no
      : _Active(false), _ProcessId(0), _Process(NULL), _ChannelProcess(NULL)
  //## end cEventChannelWrapper::cEventChannelWrapper%1037610185.hasinit
  //## begin cEventChannelWrapper::cEventChannelWrapper%1037610185.initialization preserve=yes
  //## end cEventChannelWrapper::cEventChannelWrapper%1037610185.initialization
{
  //## begin cEventChannelWrapper::cEventChannelWrapper%1037610185.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   _ChannelType = COS_EVENT_COMM_VISIBROKER;
   _ThreadName = config_obj->get_Name().c_str();
   _ChannelName = _ThreadName.c_str();
   _ProcessName = config_obj->PropertyValue("ProcessName", "");
   _ProcessArgs = config_obj->PropertyValue("ProcessArgs", "");
   _Process = process;
  //## end cEventChannelWrapper::cEventChannelWrapper%1037610185.body
}


cEventChannelWrapper::~cEventChannelWrapper()
{
  //## begin cEventChannelWrapper::~cEventChannelWrapper%.body preserve=yes
   DELETE_OBJECT(cSysProcess, _ChannelProcess)
  //## end cEventChannelWrapper::~cEventChannelWrapper%.body
}



//## Other Operations (implementation)
void cEventChannelWrapper::StartProcess ()
{
  //## begin cEventChannelWrapper::StartProcess%1037610196.body preserve=yes
   if (_ProcessName.size() > 0) {
      _ChannelProcess = new cSysProcess;
      if (!_ChannelProcess->Create(_ProcessName.c_str(), _ProcessArgs.c_str())) {
         throw cError(CHANNEL_WRAPPER_START_PROCESS, 0, _ProcessName.c_str(), _ProcessArgs.c_str(), _ThreadName.c_str());
      } else {
         _ProcessId = _ChannelProcess->get_Pid();
      }
   }
  //## end cEventChannelWrapper::StartProcess%1037610196.body
}

void cEventChannelWrapper::StopProcess ()
{
  //## begin cEventChannelWrapper::StopProcess%1037610197.body preserve=yes
   if (_ChannelProcess != NULL) _ChannelProcess->Terminate();
  //## end cEventChannelWrapper::StopProcess%1037610197.body
}

//## Get and Set Operations for Class Attributes (implementation)

INT_T cEventChannelWrapper::get_ChannelType () const
{
  //## begin cEventChannelWrapper::get_ChannelType%3DD8B83600F0.get preserve=no
  return _ChannelType;
  //## end cEventChannelWrapper::get_ChannelType%3DD8B83600F0.get
}

void cEventChannelWrapper::set_ChannelType (INT_T value)
{
  //## begin cEventChannelWrapper::set_ChannelType%3DD8B83600F0.set preserve=no
  _ChannelType = value;
  //## end cEventChannelWrapper::set_ChannelType%3DD8B83600F0.set
}

BOOL_T cEventChannelWrapper::get_Active () const
{
  //## begin cEventChannelWrapper::get_Active%3DD8B83600F1.get preserve=no
  return _Active;
  //## end cEventChannelWrapper::get_Active%3DD8B83600F1.get
}

void cEventChannelWrapper::set_Active (BOOL_T value)
{
  //## begin cEventChannelWrapper::set_Active%3DD8B83600F1.set preserve=no
  _Active = value;
  //## end cEventChannelWrapper::set_Active%3DD8B83600F1.set
}

ULONG_T cEventChannelWrapper::get_ProcessId () const
{
  //## begin cEventChannelWrapper::get_ProcessId%3DD8B83600F2.get preserve=no
  return _ProcessId;
  //## end cEventChannelWrapper::get_ProcessId%3DD8B83600F2.get
}

void cEventChannelWrapper::set_ProcessId (ULONG_T value)
{
  //## begin cEventChannelWrapper::set_ProcessId%3DD8B83600F2.set preserve=no
  _ProcessId = value;
  //## end cEventChannelWrapper::set_ProcessId%3DD8B83600F2.set
}

STRING_T cEventChannelWrapper::get_Computer () const
{
  //## begin cEventChannelWrapper::get_Computer%3DD8B83600F3.get preserve=no
  return _Computer;
  //## end cEventChannelWrapper::get_Computer%3DD8B83600F3.get
}

void cEventChannelWrapper::set_Computer (STRING_T value)
{
  //## begin cEventChannelWrapper::set_Computer%3DD8B83600F3.set preserve=no
  _Computer = value;
  //## end cEventChannelWrapper::set_Computer%3DD8B83600F3.set
}

STRING_T cEventChannelWrapper::get_ChannelName () const
{
  //## begin cEventChannelWrapper::get_ChannelName%3DD8B83600F4.get preserve=no
  return _ChannelName;
  //## end cEventChannelWrapper::get_ChannelName%3DD8B83600F4.get
}

void cEventChannelWrapper::set_ChannelName (STRING_T value)
{
  //## begin cEventChannelWrapper::set_ChannelName%3DD8B83600F4.set preserve=no
  _ChannelName = value;
  //## end cEventChannelWrapper::set_ChannelName%3DD8B83600F4.set
}

STRING_T cEventChannelWrapper::get_ProcessName () const
{
  //## begin cEventChannelWrapper::get_ProcessName%3DD8B83600F5.get preserve=no
  return _ProcessName;
  //## end cEventChannelWrapper::get_ProcessName%3DD8B83600F5.get
}

void cEventChannelWrapper::set_ProcessName (STRING_T value)
{
  //## begin cEventChannelWrapper::set_ProcessName%3DD8B83600F5.set preserve=no
  _ProcessName = value;
  //## end cEventChannelWrapper::set_ProcessName%3DD8B83600F5.set
}

STRING_T cEventChannelWrapper::get_ProcessArgs () const
{
  //## begin cEventChannelWrapper::get_ProcessArgs%3DD8B83600F6.get preserve=no
  return _ProcessArgs;
  //## end cEventChannelWrapper::get_ProcessArgs%3DD8B83600F6.get
}

void cEventChannelWrapper::set_ProcessArgs (STRING_T value)
{
  //## begin cEventChannelWrapper::set_ProcessArgs%3DD8B83600F6.set preserve=no
  _ProcessArgs = value;
  //## end cEventChannelWrapper::set_ProcessArgs%3DD8B83600F6.set
}

STRING_T cEventChannelWrapper::get_IOR () const
{
  //## begin cEventChannelWrapper::get_IOR%3DD8B83600F7.get preserve=no
  return _IOR;
  //## end cEventChannelWrapper::get_IOR%3DD8B83600F7.get
}

void cEventChannelWrapper::set_IOR (STRING_T value)
{
  //## begin cEventChannelWrapper::set_IOR%3DD8B83600F7.set preserve=no
  _IOR = value;
  //## end cEventChannelWrapper::set_IOR%3DD8B83600F7.set
}

// Additional Declarations
  //## begin cEventChannelWrapper%3DD8B83600E4.declarations preserve=yes
  //## end cEventChannelWrapper%3DD8B83600E4.declarations

//## begin module%3DD8B83600E4.epilog preserve=yes
//## end module%3DD8B83600E4.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
#endif
