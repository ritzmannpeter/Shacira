//## begin module%3EDDCC7F0167.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EDDCC7F0167.cm

//## begin module%3EDDCC7F0167.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EDDCC7F0167.cp

//## Module: cRemoteContext%3EDDCC7F0167; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\RemoteDatabase\cRemoteContext.cpp

//## begin module%3EDDCC7F0167.additionalIncludes preserve=no
#include "FirstHeader.h"
#include "System/Database/RootContext.h"
//## end module%3EDDCC7F0167.additionalIncludes

//## begin module%3EDDCC7F0167.includes preserve=yes

/// PR 23.10.06 - added reference counting to proxy

//## end module%3EDDCC7F0167.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cCellProxy
#include "System/Process/cCellProxy.h"
// cProxy
#include "System/Objects/cProxy.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cInternalBridge
#include "System/Channel/cInternalBridge.h"
// cRemoteBridge
#include "System/Channel/cRemoteBridge.h"
// cRemoteContext
#include "Client/RemoteDatabase/cRemoteContext.h"
// cRemoteVar
#include "Client/RemoteDatabase/cRemoteVar.h"
// cStyxParser
#include "Language/cStyxParser.h"
//## begin module%3EDDCC7F0167.additionalDeclarations preserve=yes

#include "Control/LocalDatabase/cLocalVariable.h"
#include "Client/ClientData/cClients.h"

//## end module%3EDDCC7F0167.additionalDeclarations


// Class cRemoteContext 







cRemoteContext::cRemoteContext()
  //## begin cRemoteContext::cRemoteContext%.hasinit preserve=no
      : _ClientId(0), _CellProxy(NULL)
  //## end cRemoteContext::cRemoteContext%.hasinit
  //## begin cRemoteContext::cRemoteContext%.initialization preserve=yes
  //## end cRemoteContext::cRemoteContext%.initialization
{
  //## begin cRemoteContext::cRemoteContext%.body preserve=yes
   _UserName = cSystemUtils::UserName();
   _Password = cSystemUtils::UserName();
  //## end cRemoteContext::cRemoteContext%.body
}

cRemoteContext::cRemoteContext(const cRemoteContext &right)
  //## begin cRemoteContext::cRemoteContext%copy.hasinit preserve=no
      : _ClientId(0), _CellProxy(NULL)
  //## end cRemoteContext::cRemoteContext%copy.hasinit
  //## begin cRemoteContext::cRemoteContext%copy.initialization preserve=yes
  //## end cRemoteContext::cRemoteContext%copy.initialization
{
  //## begin cRemoteContext::cRemoteContext%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cRemoteContext::cRemoteContext%copy.body
}

cRemoteContext::cRemoteContext (cSHProcess *process, cCellProxy *proxy)
  //## begin cRemoteContext::cRemoteContext%1054715296.hasinit preserve=no
      : _ClientId(0), _CellProxy(NULL)
  //## end cRemoteContext::cRemoteContext%1054715296.hasinit
  //## begin cRemoteContext::cRemoteContext%1054715296.initialization preserve=yes
  , cContext(process, NULL)
  //## end cRemoteContext::cRemoteContext%1054715296.initialization
{
  //## begin cRemoteContext::cRemoteContext%1054715296.body preserve=yes
_ASSERT_COND(proxy != NULL)
_ASSERT_COND(process != NULL)
   proxy->AddRef();
   _CellProxy = proxy;
   _Process = process;
   _UserName = cSystemUtils::UserName();
   _Password = cSystemUtils::UserName();
  //## end cRemoteContext::cRemoteContext%1054715296.body
}


cRemoteContext::~cRemoteContext()
{
  //## begin cRemoteContext::~cRemoteContext%.body preserve=yes
   _CellProxy->Logout();
//   RELEASE_OBJECT(_CellProxy)
  //## end cRemoteContext::~cRemoteContext%.body
}



//## Other Operations (implementation)
BOOL_T cRemoteContext::IsRemote ()
{
  //## begin cRemoteContext::IsRemote%1054715293.body preserve=yes
   return true;
  //## end cRemoteContext::IsRemote%1054715293.body
}

void cRemoteContext::Connect (ULONG_T if_type)
{
  //## begin cRemoteContext::Connect%1054715294.body preserve=yes
   if (_Created) {
      return;
   }
_ASSERT_COND(_CellProxy != NULL)
   ULONG_T client_id = _CellProxy->LoginIfType("", "", if_type);
   if (client_id > USER_CLIENTS_ID_MAX) {
      // Get no correct client id (old handling) now client_id is interface type
      client_id = if_type;
   }

   _CellProxy->set_IFType(if_type);
   _ClientId = client_id;
   _CellProxy->set_ClientId(_ClientId);
   RemoveVarDefs();
   STRING_T var_defs;
   GetVarDefs(var_defs);
   cStyxParser parser;
   parser.ParseDatabaseFromString(this, var_defs.c_str());
   _Name = _CellProxy->Name();
   RootContext::Set(this);
   InfoPrintf("client %d connected\n", _ClientId);
   cClients::SetConnected(true);
  //## end cRemoteContext::Connect%1054715294.body
}

void cRemoteContext::Create ()
{
  //## begin cRemoteContext::Create%1054715295.body preserve=yes
   if (_Created) {
      return;
   }
   _Created = true;
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.cbegin();
   while (i != _VarDefs.cend()) {
      cVarDef * var_def = (*i).second;
      cVariable * variable = new cRemoteVar(var_def);
      var_def->_Variable = variable;
      i++;
   }
  //## end cRemoteContext::Create%1054715295.body
}

void cRemoteContext::CreateDynamic ()
{
  //## begin cRemoteContext::CreateDynamic%1090073691.body preserve=yes
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.cbegin();
   while (i != _VarDefs.cend()) {
      cVarDef * var_def = (*i).second;
      if (var_def != NULL && var_def->IsDynamic()) {
         cVariable * variable = var_def->_Variable;
         variable = new cLocalVariable(var_def);
         var_def->_Variable = variable;
      }
      i++;
   }
  //## end cRemoteContext::CreateDynamic%1090073691.body
}

ULONG_T cRemoteContext::GetVarDefs (STRING_T &var_defs, ULONG_T if_type)
{
  //## begin cRemoteContext::GetVarDefs%1054726259.body preserve=yes
	return _CellProxy->GetVarDefs(var_defs);
  //## end cRemoteContext::GetVarDefs%1054726259.body
}

cChannel * cRemoteContext::LocalChannel ()
{
  //## begin cRemoteContext::LocalChannel%1086771868.body preserve=yes
   return NULL;
  //## end cRemoteContext::LocalChannel%1086771868.body
}

cChannel * cRemoteContext::EventChannel ()
{
  //## begin cRemoteContext::EventChannel%1073299992.body preserve=yes
   if (_EventChannel == NULL) {
      _EventChannel = new cInternalBridge(_CellProxy, _ClientId, cSystemUtils::ComputerName().c_str());
      ((cInternalBridge*)_EventChannel)->set_UserName(_UserName.c_str());
      ((cInternalBridge*)_EventChannel)->set_Password(_Password.c_str());
      _EventChannel->Start();
   }
   return _EventChannel;
  //## end cRemoteContext::EventChannel%1073299992.body
}

ULONG_T cRemoteContext::Alarms (ULONG_T selection)
{
  //## begin cRemoteContext::Alarms%1089103363.body preserve=yes
   if (_CellProxy != NULL) {
      return _CellProxy->Alarms(selection);
   }
   return 0;
  //## end cRemoteContext::Alarms%1089103363.body
}

ULONG_T cRemoteContext::Alarms (ULONG_T selection, ALARM_MAP_T &alarms)
{
  //## begin cRemoteContext::Alarms%1081425831.body preserve=yes
   if (_CellProxy != NULL) {
      return _CellProxy->Alarms(selection, alarms);
   }
   return 0;
  //## end cRemoteContext::Alarms%1081425831.body
}

void cRemoteContext::ClearAlarm (ULONG_T ident, BOOL_T propagate)
{
  //## begin cRemoteContext::ClearAlarm%1081425832.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->ClearAlarm(ident);
   }
  //## end cRemoteContext::ClearAlarm%1081425832.body
}

void cRemoteContext::ClearAlarms (BOOL_T propagate)
{
  //## begin cRemoteContext::ClearAlarms%1081425833.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->ClearAlarms();
   }
  //## end cRemoteContext::ClearAlarms%1081425833.body
}

void cRemoteContext::GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value)
{
  //## begin cRemoteContext::GetDeviceValue%1082991643.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->GetDeviceValue(buf_spec, address, value);
   }
  //## end cRemoteContext::GetDeviceValue%1082991643.body
}

void cRemoteContext::SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value)
{
  //## begin cRemoteContext::SetDeviceValue%1082991644.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->SetDeviceValue(buf_spec, address, value);
   }
  //## end cRemoteContext::SetDeviceValue%1082991644.body
}

void cRemoteContext::ExecuteCommand (CONST_STRING_T program_name, ULONG_T command)
{
  //## begin cRemoteContext::ExecuteCommand%1089292614.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->ExecuteCommand(program_name, command);
   }
  //## end cRemoteContext::ExecuteCommand%1089292614.body
}

void cRemoteContext::ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request)
{
  //## begin cRemoteContext::ExecuteRequest%1133771769.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->ExecuteRequest(program_name, reply, request);
   }
  //## end cRemoteContext::ExecuteRequest%1133771769.body
}

void cRemoteContext::ReadFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, STRING_T &buf)
{
  //## begin cRemoteContext::ReadFile%1091699607.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->ReadFile(file_name, sub_files, buf);
   }
  //## end cRemoteContext::ReadFile%1091699607.body
}

void cRemoteContext::ExportVariables(STRING_T &buf, CONST_STRING_T sub_file, CONST_STRING_T separator)
{
   if (_CellProxy != NULL) {
      _CellProxy->ExportVariables(buf, sub_file, separator);
   }
}

void cRemoteContext::WriteFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, CONST_STRING_T buf)
{
  //## begin cRemoteContext::WriteFile%1091699608.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->WriteFile(file_name, sub_files, buf);
   }
  //## end cRemoteContext::WriteFile%1091699608.body
}

void cRemoteContext::Update (ULONG_T process_id)
{
  //## begin cRemoteContext::Update%1077626054.body preserve=yes
   if (_ProcessId == 0) {
      _ProcessId = process_id;
   } else {
/* PR 09.10.04 this will crash remote user interfaces
               because all variable references will become invalid
      if (_ProcessId != process_id) {
         RemoveVarDefs();
         STRING_T var_defs;
         GetVarDefs(var_defs);
         cStyxParser parser;
         parser.ParseDatabaseFromString(this, var_defs.c_str());
         std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.cbegin();
         while (i != _VarDefs.cend()) {
            cVarDef * var_def = (*i).second;
            cVariable * variable = new cRemoteVar(var_def);
            var_def->_Variable = variable;
            i++;
         }
         _ProcessId = process_id;
      }
*/
   }
  //## end cRemoteContext::Update%1077626054.body
}

void cRemoteContext::RemoveVarDefs ()
{
  //## begin cRemoteContext::RemoveVarDefs%1092122758.body preserve=yes
   if (_Created) {
      return;
   }
   _Created = false;
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.cbegin();
   while (i != _VarDefs.cend()) {
      cVarDef * var_def = (*i).second;
      cVariable * variable = var_def->_Variable;
      DELETE_OBJECT(cVarDef, var_def)
      i++;
   }
   _VarDefs.clear();
  //## end cRemoteContext::RemoveVarDefs%1092122758.body
}

void cRemoteContext::SetJob (cJobSpec *job_spec)
{
  //## begin cRemoteContext::SetJob%1093930663.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->SetJob(job_spec);
   }
  //## end cRemoteContext::SetJob%1093930663.body
}

cJobSpec * cRemoteContext::GetJobSpec (CONST_STRING_T job_name)
{
  //## begin cRemoteContext::GetJobSpec%1093930664.body preserve=yes
   if (_CellProxy != NULL) {
      return _CellProxy->GetJobSpec(job_name);
   } else {
      return NULL;
   }
  //## end cRemoteContext::GetJobSpec%1093930664.body
}

void cRemoteContext::Send (cTransientObject *object)
{
  //## begin cRemoteContext::Send%1125073057.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->SendObject(object);
   }
  //## end cRemoteContext::Send%1125073057.body
}

BOOL_T cRemoteContext::IsConnected ()
{
  //## begin cRemoteContext::IsConnected%1134148706.body preserve=yes
   if (_CellProxy == NULL) {
      return false;
   } else {
      return _CellProxy->get_Connected();
   }
  //## end cRemoteContext::IsConnected%1134148706.body
}

BOOL_T cRemoteContext::Ping ()
{
  //## begin cRemoteContext::Ping%1134227772.body preserve=yes
   if (_CellProxy == NULL) {
      return false;
   } else {
      return _CellProxy->Ping();
   }
  //## end cRemoteContext::Ping%1134227772.body
}

BOOL_T cRemoteContext::IsLocal ()
{
  //## begin cRemoteContext::IsLocal%1141892789.body preserve=yes
   if (_CellProxy == NULL) {
      return false;
   } else {
      STRING_T computer_name = cSystemUtils::ComputerName();
      STRING_T remote_computer_name = _CellProxy->get_Computer();
      if (computer_name == remote_computer_name) {
         return true;
      } else {
         return false;
      }
   }
  //## end cRemoteContext::IsLocal%1141892789.body
}

BOOL_T cRemoteContext::Synchronize ()
{
  //## begin cRemoteContext::Synchronize%1228401754.body preserve=yes
   if (!_CellProxy->get_Synchronized()) {
      STRING_T proxy_name = _CellProxy->get_ProxyName();
      STRING_T var_defs;
      try {
         if (_CellProxy->get_ClientId() == 0) {
            ULONG_T if_type = _CellProxy->get_IFType();
            ULONG_T client_id = _CellProxy->LoginIfType("", "", if_type);

            if (client_id > USER_CLIENTS_ID_MAX) {
               // Get no correct client id (old handling) now client_id is interface type
               client_id = if_type;
            }

            _CellProxy->set_IFType(if_type);
            _ClientId = client_id;
            _CellProxy->set_ClientId(_ClientId);
         }

         _CellProxy->GetVarDefs(var_defs);
         return true;
      } catch (cError & e) {
         ErrorPrintf("%s while synchronizing client with service %s\n", (const char *)e, proxy_name.c_str());
      } catch (...) {
         ErrorPrintf("unknown exception while synchronizing client with service %s\n", proxy_name.c_str());
      }
   }
   return false;
  //## end cRemoteContext::Synchronize%1228401754.body
}

BOOL_T cRemoteContext::Synchronized ()
{
  //## begin cRemoteContext::Synchronized%1228414413.body preserve=yes
   return _CellProxy->get_Synchronized();
  //## end cRemoteContext::Synchronized%1228414413.body
}

cCellProxy * cRemoteContext::Proxy ()
{
  //## begin cRemoteContext::Proxy%1228414414.body preserve=yes
   return _CellProxy;
  //## end cRemoteContext::Proxy%1228414414.body
}

void cRemoteContext::ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async)
{
  //## begin cRemoteContext::ExecuteJob%1244547095.body preserve=yes
   if (_CellProxy != NULL) {
      _CellProxy->ExecuteJob(program_name, job, async);
   }
  //## end cRemoteContext::ExecuteJob%1244547095.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cRemoteContext::get_ClientId () const
{
  //## begin cRemoteContext::get_ClientId%42DE0E9502DE.get preserve=no
  return _ClientId;
  //## end cRemoteContext::get_ClientId%42DE0E9502DE.get
}

STRING_T cRemoteContext::get_UserName () const
{
  //## begin cRemoteContext::get_UserName%42DF90BA02FD.get preserve=no
  return _UserName;
  //## end cRemoteContext::get_UserName%42DF90BA02FD.get
}

void cRemoteContext::set_UserName (STRING_T value)
{
  //## begin cRemoteContext::set_UserName%42DF90BA02FD.set preserve=no
  _UserName = value;
  //## end cRemoteContext::set_UserName%42DF90BA02FD.set
}

STRING_T cRemoteContext::get_Password () const
{
  //## begin cRemoteContext::get_Password%42DF90E00213.get preserve=no
  return _Password;
  //## end cRemoteContext::get_Password%42DF90E00213.get
}

void cRemoteContext::set_Password (STRING_T value)
{
  //## begin cRemoteContext::set_Password%42DF90E00213.set preserve=no
  _Password = value;
  //## end cRemoteContext::set_Password%42DF90E00213.set
}

cCellProxy * cRemoteContext::GetCellProxy() const
{
   return _CellProxy;
}

void cRemoteContext::SetCellProxy(cCellProxy * cell_proxy)
{
   if (_CellProxy) {
      InfoPrintf("Set CellProxy (interfacetype %d) with new proxy\n", _CellProxy->get_IFType());
   }
   _CellProxy = cell_proxy;
}

void cRemoteContext::GetParam (CONST_STRING_T param_name, STRING_T &value)
{
   if (_CellProxy != NULL) {
      _CellProxy->GetParam(param_name, value);
   }
}

// Additional Declarations
  //## begin cRemoteContext%3EDDCC7F0167.declarations preserve=yes
  //## end cRemoteContext%3EDDCC7F0167.declarations

//## begin module%3EDDCC7F0167.epilog preserve=yes
//## end module%3EDDCC7F0167.epilog
