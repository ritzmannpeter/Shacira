//## begin module%3EDDCAEC005D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EDDCAEC005D.cm

//## begin module%3EDDCAEC005D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EDDCAEC005D.cp

//## Module: cLocalContext%3EDDCAEC005D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cLocalContext.cpp

//## begin module%3EDDCAEC005D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3EDDCAEC005D.additionalIncludes

//## begin module%3EDDCAEC005D.includes preserve=yes

/// PR 09.05.05 - restricted Compare operations to variables of type SH_VAR_SET
/// PR 01.09.05 - constructing service proxy object as heap object and release it properly
/// PR 12.09.05 - setting devices buffered while executing copy command
///             - extended error handling for load, save and copy processes
/// PR 04.10.05 - removed potential memory (object) leak in alarm handling functionality
/// PR 03.11.05 - avoiding to access uninitialized dispatcher object
/// PR 14.11.05 - enabled ClearAlarm and ClearAlarms to propagate alarm over dispatcher 
/// PR 15.11.05 - added file based propagation of connection information
/// PR 16.11.05 - made file based propagation of connection information switchable (_PrintIOR)
/// PR 02.12.05 - set context name to cell name
/// PR 05.12.05 - remove setting of context name due to problems in
///               naming of persistent data file
/// PR 10,01.06 - slight changes in formatting of info messages
/// PR 27.01.06 - restructured startup procedure
/// PR 16.02.06 - starting persistence channel directly after construction
///               to avoid semi initialized systems in case of interrupted
///               startups
/// PR 23.02.06 - returning 1 instead of 0 when no definition filter is set
/// PR 28.04.06 - removed assertion in standard constructor and no more raise
///               an exception, when no dispatcher is available; this has been done
///               to enable lightweight local contexts without infrastructure
/// PR 26.05.06 - throwing an exception when trying to acces uninitialized _Cell
/// PR 10.10.06 - changed method ReadFile:
///               argument subfile now controls the set of variables that van be
///               stored to a file
///               sub_file == ""        all variables stored (previous behaviour)
///               sub_file == "<name>"  only variables with the "file name" are stored (new)
///               sub_file == "-"  only variables with the "file name" != "" are stored (new)
/// PR 23.10.06 - added management of ProxyService
/// PR 08.11.06 - added delayed creation of CORBA object, when no valid IP address is active
/// PR 20.11.06 - added filter for additional network interfaces that must be ignored
///               when creating the corba service object
/// PR 21.11.06 - fixed bug in network interface filter
/// PR 30.01.07 - added local method ActiveAlarm to determine the next active
///               alarm to be emitted through a cInfo event
/// PR 13.02.07 - added functionality for address checking in device mappings
/// PR 15.02.07 - extended address checking to mapping check
/// PR 26.06.07 - host variables are exported only when the variable is marked as
///               HOST_READ or HOST_WRITE in case of non proprietary host interfaces
///               (OPC, ...) (Horst Anselm FM)
/// PR 13.07.07 - added method ::EmitChanges to emit changes caused by persistent variable values
///               the functionality can be activated via resource flag PF_EMIT_CHANGES
/// PR 07.10.07 - full implementation of shadow dataset control for local variables
/// PR 09.10.07 - implemented cleanup functionality for startup errors
///                can be activated via resource flag PF_CLEANUP_ON_STARTUP_ERROR
/// PR 22.10.07 - extended control of ::CopyCommand through copy_flags
/// PR 23.10.07 - suppressing progress events when copying shadow dataset
/// PR 26.11.07 - preparation for modular variable creation
/// PR 01.08.08 - reusing dynamic variables if possible in ::CreateDynamic()
/// PR 11.10.10 - added new xml service for tcp/ip based data exchange
/// PR 06.04.13 - added UpdateUi() function call in Send()
/// PR 31.07.14 - added file buffering hooks in copy methods
/// HA 15.06.15 - changed method ReadFile:
///               argument subfile now controls the set of variables that van be
///               stored to a file
///               sub_file == ""   all variables stored (previous behaviour)
///               sub_file == "<subfile name>"  only variables with the "subfile name" are stored
///               sub_file == "-"  only variables with the subfile name != "" are stored
///               sub_file == "-<subfile name>"  store all variables and excluding variables with the "subfile name"
/// PR 28.01.18 - added method void cLocalContext::ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_file, cStringBuffer &buf)
///               This method does not deliver an ascii dataset in a std::string variable but writes an ascii dataset directly to
///               to a file represented by a cStringBuffer object.
///               When ascii datasets are very large (a 2 meg dataset for example),
///               the std::string type method potentially runs into low memory.

#include "Control/Device/Performance/cPerfDevice.h"
//## end module%3EDDCAEC005D.includes

// cIniFile
#include "System/cIniFile.h"
// cSHProcess
#include "System/Process/cSHProcess.h"
// cInfo
#include "System/Objects/cInfo.h"
// cJobSpec
#include "System/Objects/cJobSpec.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cFileContext
#include "System/Database/cFileContext.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cInternalBridge
#include "System/Channel/cInternalBridge.h"
// cLocalChannel
#include "System/Channel/cLocalChannel.h"
// cXmlService
#include "System/ClientServer/XMLService/cXmlService.h"
// cProgramFactory
#include "Control/Cell/cProgramFactory.h"
// cProgram
#include "Control/Cell/cProgram.h"
// cCell
#include "Control/Cell/cCell.h"
// cJobManager
#include "Control/Cell/cJobManager.h"
// cLocalVariable
#include "Control/LocalDatabase/cLocalVariable.h"
// cPersistenceChannel
#include "Control/LocalDatabase/cPersistenceChannel.h"
// cLocalContext
#include "Control/LocalDatabase/cLocalContext.h"
// cSubFile
#include "Control/LocalDatabase/cSubFile.h"
// cDevice
#include "Control/Device/cDevice.h"
// cCorbaCellProxy
#include "Orb/cCorbaCellProxy.h"
// cBroker
#include "Orb/cBroker.h"
// cStyxParser
#include "Language/cStyxParser.h"
// iCellObject
#include "Orb\iCellObject.h"
//## begin module%3EDDCAEC005D.additionalDeclarations preserve=yes

#include "Control/LocalDatabase/cPersistenceManager.h"

#define CHECK_CELL \
   if (_Cell == NULL) { \
      throw cError(CELL_UNINITIALIZED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str()); \
   }

#define USE_PROXY_SERVICE
#ifdef USE_PROXY_SERVICE
#include "System/Comm/cProxyService.h"
static cProxyService * _ProxyService = NULL;
#endif

#include "System/Sys/cStringBuffer.h"

class cObjectService: public cThread
{
public:
   cObjectService(cLocalContext * local_context);
   virtual ~cObjectService() {};
   virtual void Start();
   virtual void Stop();
   virtual bool onEnter (void *extra) {return cThread::onEnter(extra);};
   virtual int onMain (void *extra);
   virtual void onLeave (INT_T rc) {cThread::onLeave(rc);};
private:
   cLocalContext * _LocalContext;
   bool _Active;
   bool _StopRequest;
};


cObjectService::cObjectService(cLocalContext * local_context)
{
   _Active = false;
   _StopRequest = false;
   _LocalContext = local_context;
}

void cObjectService::Start()
{
   start();
}
   
void cObjectService::Stop()
{
   if (_Active) {
      _StopRequest = true;
      waitFor(teEnd);
   }
}
   
int cObjectService::onMain (void *extra)
{
   _Active = true;
   while (!_StopRequest) {
      if (_LocalContext->ActivateCorbaObject()) {
         _Active = false;
         return 0;
      } else {
         cSystemUtils::Suspend(1000);
      }
   }
   return 0;
}

#define OMNIORB_USEHOSTNAME_VAR "OMNIORB_USEHOSTNAME"
static char USEHOST_ENV_STRING[0x200] = {0};

static bool AddressValid()
{
   char host_name[0x200] = {0};
   if (gethostname(host_name, sizeof(host_name)) == 0) {
      struct hostent * e = gethostbyname(host_name);
      if (e != NULL) {
         unsigned long addr = *(unsigned long*)e->h_addr;
         int ip[4] = {0};
         ip[3] = (addr & 0xff000000) >> 24; 
         ip[2] = (addr & 0x00ff0000) >> 16; 
         ip[1] = (addr & 0x0000ff00) >> 8; 
         ip[0] = addr & 0x000000ff;
         if (ip[0] == 0 ||
             ip[1] == 0 ||
             ip[2] == 0 ||
             ip[3] == 0) {
            return false;
         } else {
            return true;
         }
      } else {
         return false;
      }
   } else {
      return false;
   }
}

typedef std::map<ULONG_T,STRING_T> IP_ADDR_MAP_T;

static char _HostName[0x200] = {0};
static const char * HostName()
{
   if (strlen(_HostName) > 0) {
      return _HostName;
   }
   int rc = gethostname(_HostName, sizeof(_HostName));
   if (rc == 0) {
      return _HostName;
   }
   return NULL;
}

static ULONG_T IpAddr2Long(const char * ip_addr)
{
   ULONG_T seg[4] = {0};
   int params = sscanf(ip_addr, "%d.%d.%d.%d", &seg[0], &seg[1], &seg[2], &seg[3]);
   if (params == 4) {
      ULONG_T laddr = 0;
      laddr += (seg[3] << 24);
      laddr += (seg[2] << 16);
      laddr += (seg[1] << 8);
      laddr += seg[0];
      return laddr;
   } else {
      return 0;
   }
}

static STRING_T Long2IpAddr(ULONG_T laddr)
{
   ULONG_T seg[4] = {0};
   seg[3] = (laddr & 0xff000000) >> 24;
   seg[2] = (laddr & 0x00ff0000) >> 16;
   seg[1] = (laddr & 0x0000ff00) >> 8;
   seg[0] = (laddr & 0x000000ff);
   char ip_addr[0x100] = {0};
   SafePrintf(ip_addr, sizeof(ip_addr), "%d.%d.%d.%d", seg[0], seg[1], seg[2], seg[3]);
   return ip_addr;
}

static bool ValidAddress(STRING_VECTOR_T ignore_list, STRING_T & valid_address)
{
   const char * host_name = HostName();
   if (host_name == NULL) {
      return false;
   } else {
      IP_ADDR_MAP_T ign_addresses;
      int size = ignore_list.size();
      int i = 0;
      for (i=0; i<size; i++) {
         ULONG_T address = IpAddr2Long(ignore_list[i].c_str());
         if (address != 0) {
            ign_addresses[address] = ignore_list[i].c_str();
///            InfoPrintf("skipping address %s\n", ignore_list[i].c_str());
         } else {
            InfoPrintf("failed to translate address %s\n", ignore_list[i].c_str());
            ErrorPrintf("failed to translate address %s\n", ignore_list[i].c_str());
         }
      }
      struct hostent * e = gethostbyname(host_name);
      if (e != NULL) {
         int i = 0;
         while(e->h_addr_list[i]) {
            ULONG_T laddr = *((ULONG_T*)e->h_addr_list[i]);
            if (laddr != IpAddr2Long("127.0.0.1")) {
               /// local host address will be generally filtered out
               IP_ADDR_MAP_T::const_iterator a = ign_addresses.find(laddr);
               if (a == ign_addresses.end()) {
                  valid_address = Long2IpAddr(laddr);
                  return true;
               }
            }
            i++;
         }
      }
      return false;
   }
}

//## end module%3EDDCAEC005D.additionalDeclarations


// Class cLocalContext 













//## begin cLocalContext::VarDefFilterFuncAddress%438831300244.attr preserve=no  implementation: static VARDEF_FILTER_T {U} NULL
VARDEF_FILTER_T cLocalContext::_VarDefFilterFuncAddress = NULL;
//## end cLocalContext::VarDefFilterFuncAddress%438831300244.attr

//## begin cLocalContext::HostItfCache%438837020108.attr preserve=no  implementation: static HOSTITF_CACHE_T {U} 
HOSTITF_CACHE_T cLocalContext::_HostItfCache;
//## end cLocalContext::HostItfCache%438837020108.attr








cLocalContext::cLocalContext()
  //## begin cLocalContext::cLocalContext%.hasinit preserve=no
      : _CorbaService(true), _ForceCorbaService(false), _IsClientContext(false), _RunLevel(0), _RunFlags(0), _MdlInitFuncAddress(NULL), _PrintIOR(false), _ConfigObject(NULL), _ObjectService(NULL), _CorbaObjectActive(false), _ShadowManager(NULL), _JobManager(NULL), _PersistenceChannel(NULL), _Cell(NULL)
  //## end cLocalContext::cLocalContext%.hasinit
  //## begin cLocalContext::cLocalContext%.initialization preserve=yes
  , _CellObject(NULL)
  //## end cLocalContext::cLocalContext%.initialization
{
  //## begin cLocalContext::cLocalContext%.body preserve=yes
///_ASSERT_UNCOND
  //## end cLocalContext::cLocalContext%.body
}

cLocalContext::cLocalContext(const cLocalContext &right)
  //## begin cLocalContext::cLocalContext%copy.hasinit preserve=no
      : _CorbaService(true), _ForceCorbaService(false), _IsClientContext(false), _RunLevel(0), _RunFlags(0), _MdlInitFuncAddress(NULL), _PrintIOR(false), _ConfigObject(NULL), _ObjectService(NULL), _CorbaObjectActive(false), _ShadowManager(NULL), _JobManager(NULL), _PersistenceChannel(NULL), _Cell(NULL)
  //## end cLocalContext::cLocalContext%copy.hasinit
  //## begin cLocalContext::cLocalContext%copy.initialization preserve=yes
  , _CellObject(NULL)
  //## end cLocalContext::cLocalContext%copy.initialization
{
  //## begin cLocalContext::cLocalContext%copy.body preserve=yes
/// PR 28.04.06
///   _ASSERT_UNCOND
  //## end cLocalContext::cLocalContext%copy.body
}

cLocalContext::cLocalContext (cSHProcess *process, cConfigurationObject *config_obj, BOOL_T client_context)
  //## begin cLocalContext::cLocalContext%1122450441.hasinit preserve=no
      : _CorbaService(true), _ForceCorbaService(false), _IsClientContext(false), _RunLevel(0), _RunFlags(0), _MdlInitFuncAddress(NULL), _PrintIOR(false), _ConfigObject(NULL), _ObjectService(NULL), _CorbaObjectActive(false), _ShadowManager(NULL), _JobManager(NULL), _PersistenceChannel(NULL), _Cell(NULL)
  //## end cLocalContext::cLocalContext%1122450441.hasinit
  //## begin cLocalContext::cLocalContext%1122450441.initialization preserve=yes
  , cContext(process, config_obj), _CellObject(NULL)
  //## end cLocalContext::cLocalContext%1122450441.initialization
{
  //## begin cLocalContext::cLocalContext%1122450441.body preserve=yes
_ASSERT_COND(config_obj != NULL)
   _ConfigObject = config_obj;

   Initialize(SH_PRE_CONTEXT_INSTANTIATION);

   _IsClientContext = client_context;
   _Name = config_obj->get_Name();;
   _Name = config_obj->PropertyValue("ContextName", _Name.c_str());
   _CorbaService = config_obj->PropertyValue("CorbaService", _CorbaService);
   _ForceCorbaService = config_obj->PropertyValue("ForceCorbaService", _ForceCorbaService);
   config_obj->PropertyValue("SkipNetworks", _SkipNetworks);
   if (_IsClientContext) {
      _CorbaService = false;
   } else {
      _IORDirectory = config_obj->PropertyValue("IORDirectory", _IORDirectory.c_str());
      _IORDirectory = cFileSystemUtils::FullPath(_IORDirectory.c_str());
      _IORFile = cFileSystemUtils::AppendPath(_IORDirectory.c_str(), "iors.dat");
      _PrintIOR = config_obj->PropertyValue("PrintIOR", _PrintIOR);
   }

   // create basic channels
   STRING_T event_channel_name = _Name;
   event_channel_name += ".";
   event_channel_name += "EventChannel";
   _EventChannel = new cLocalChannel(event_channel_name.c_str());
   STRING_T dispatcher_name = _Name;
   dispatcher_name += ".";
   dispatcher_name += "Dispatcher";
   _Dispatcher = new cLocalChannel(dispatcher_name.c_str());
   if (_Dispatcher != NULL) {
      if (_EventChannel != NULL) {
         _Dispatcher->Connect(_EventChannel);
      }
   }

   STRING_T bridge_name = _Name;
   bridge_name += ".";
   bridge_name += "Bridge";
   if (!_IsClientContext) {
      _InternalBridge = new cInternalBridge(bridge_name.c_str());
      if (_InternalBridge != NULL) {
         if (_Dispatcher != NULL) {
            _Dispatcher->Connect(_InternalBridge);
         }
      }
   }

   // instantiate cell
   cConfigurationObject * cell_obj = (cConfigurationObject*)config_obj->PropertyValue("Cell", (cConfigurationObject*)NULL);
   if (cell_obj != NULL) {
      _Cell = new cCell(this, cell_obj);
      _Name = _Cell->get_Name();
      _CellName = cell_obj->PropertyValue("CellName", _Name.c_str());
   } 

   InfoPrintf("loading context ...\n");
   STRING_VECTOR_T model_file_names;
   config_obj->PropertyValue("ModelFiles", model_file_names);
   ULONG_T file_count = model_file_names.size();
   if (file_count > 0) {
      STRING_T model_path = cResources::ModelPath();
      STRING_VECTOR_T symbol_file_names;
      config_obj->PropertyValue("SymbolFiles", symbol_file_names);
      ULONG_T symbol_file_count = symbol_file_names.size();
      if (symbol_file_count > 0) {
         for (ULONG_T i=0; i<symbol_file_count; i++) {
            STRING_T symbol_file = cFileSystemUtils::AppendPath(model_path.c_str(), symbol_file_names[i].c_str());
            LoadSymbols(symbol_file.c_str());
         }
      }
      for (ULONG_T i=0; i<file_count; i++) {
         STRING_T file_name = cFileSystemUtils::AppendPath(model_path.c_str(), model_file_names[i].c_str());
         ParseDatabaseFromFile(file_name.c_str());
      }
      Initialize(SH_PRE_CONTEXT_CREATION);
      Create();
      Initialize(SH_POST_CONTEXT_CREATION);
   }
   InfoPrintf("loading context done\n");

   // instantiate job manager
   InfoPrintf("creating job manager ...\n");
   cConfigurationObject * manager_obj =
      (cConfigurationObject*)config_obj->PropertyValue("JobManager", (cConfigurationObject*)NULL);
   if (manager_obj == NULL) {
      _JobManager = new cJobManager("JobManager", this);
   } else {
      _JobManager = new cJobManager(manager_obj, this);
   }
   InfoPrintf("creating job manager done\n");

   Initialize(SH_POST_CONTEXT_INSTANTIATION);

   RootContext::Set(this);

  //## end cLocalContext::cLocalContext%1122450441.body
}

cLocalContext::cLocalContext (cSHProcess *process)
   : _CorbaService(true), _ForceCorbaService(false), _IsClientContext(false), _RunLevel(0), _RunFlags(0), _MdlInitFuncAddress(NULL), _PrintIOR(false), _ConfigObject(NULL), _ObjectService(NULL), _CorbaObjectActive(false), _ShadowManager(NULL), _JobManager(NULL),
     _PersistenceChannel(NULL), _Cell(NULL), cContext(process), _CellObject(NULL)
{
  //## begin cLocalContext::cLocalContext%1122450441.body preserve=yes
_ASSERT_COND(process != NULL)
   _Cell = new cCell(this);
}

cLocalContext::~cLocalContext()
{
  //## begin cLocalContext::~cLocalContext%.body preserve=yes
   Stop();
   std::map<STRING_T,cProgram*>::iterator i = _Programs.begin();
   while (i != _Programs.end()) {
      cProgram * program = (*i).second;
      if (!program->HasReferences()) {
         InfoPrintf("deleting program %s\n", program->get_Name().c_str());
         DELETE_OBJECT(cProgram,program)
         _Programs.erase(i);
      }
      i++;
   }
   i = _Programs.begin();
   while (i != _Programs.end()) {
      cProgram * program = (*i).second;
      if (program->HasReferences()) {
         InfoPrintf("deleting program %s\n", program->get_Name().c_str());
         DELETE_OBJECT(cProgram,program)
         _Programs.erase(i);
      }
      i++;
   }
   _Programs.clear();
   DELETE_OBJECT(cPersistenceChannel, _PersistenceChannel)
   DELETE_OBJECT(cChannel, _Dispatcher)
   DELETE_OBJECT(cChannel, _EventChannel)
   DELETE_OBJECT(cJobManager, _JobManager)
  //## end cLocalContext::~cLocalContext%.body
}



//## Other Operations (implementation)
BOOL_T cLocalContext::IsRemote ()
{
  //## begin cLocalContext::IsRemote%1054715290.body preserve=yes
   return false;
  //## end cLocalContext::IsRemote%1054715290.body
}

void cLocalContext::Start ()
{
  //## begin cLocalContext::Start%1122450442.body preserve=yes
   Initialize(SH_PRE_SYSTEM_STARTUP);
   ULONG_T total = cSystemUtils::RealtimeOffset();
   ULONG_T t = 0;
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
      _ShadowManager = new cPersistenceManager(this, SHADOW_DATASET);
   }
   CreatePersistenceChannel();
   SetCellName();
   CreatePrograms();
   if (_Dispatcher != NULL) {
      _Dispatcher->Start();
   }
   if (_EventChannel != NULL) {
      _EventChannel->Start();
   }
   if (_InternalBridge != NULL) {
      _InternalBridge->Start();
   }
   t = cSystemUtils::RealtimeOffset();
   /// set device buffers with current values
   LoadVariables();
   /// emit data change events for current values
   EmitChanges();
   InfoPrintf("%s load variables in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - t);
   /// must be done before upload or download
   t = cSystemUtils::RealtimeOffset();
   _Cell->Start();
   InfoPrintf("%s cell start in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - t);
   if (!cResources::FlagSet(PF_FAST_STARTUP)) {
///      t = cSystemUtils::RealtimeOffset();
///      Upload();
///      InfoPrintf("%s upload in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - t);
      t = cSystemUtils::RealtimeOffset();
      Download();
      InfoPrintf("%s download in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - t);
   }
   _Cell->SetDevicesCached(false);
   _Cell->SetDevicesBuffered(false);
   t = cSystemUtils::RealtimeOffset();
   Initialize(SH_CACHE_IS_FREE);
   InfoPrintf("%s SH_CACHE_IS_FREE in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - t);
   t = cSystemUtils::RealtimeOffset();
   StartPrograms();
   InfoPrintf("%s start programs in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - t);
   t = cSystemUtils::RealtimeOffset();
   StartServices();
   InfoPrintf("%s start services in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - t);
   if (_JobManager != NULL) {
      _JobManager->Start();
   }
   t = cSystemUtils::RealtimeOffset();
   Initialize(SH_POST_SYSTEM_STARTUP);
   InfoPrintf("%s SH_POST_SYSTEM_STARTUP in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - t);
   InfoPrintf("%s started in %d msecs\n", _Name.c_str(), cSystemUtils::RealtimeOffset() - total);
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
      if (_PersistenceChannel->DataInitialized()) {
         CopyCommand(FOREGROUND_DATASET, SHADOW_DATASET, false, CP_FLAG_SUPPRESS_PROGRESS);
      }
      CheckShadowDataset();
   }
   //## end cLocalContext::Start%1122450442.body
}

void cLocalContext::Stop ()
{
  //## begin cLocalContext::Stop%1122450443.body preserve=yes
   _Cell->Stop();
   StopPrograms();
	StopServices();
   if (_InternalBridge != NULL) {
      _InternalBridge->Stop();
   }
   if (_Dispatcher != NULL) {
      _Dispatcher->Stop();
   }
   if (_EventChannel != NULL) {
      _EventChannel->Stop();
   }
   if (_JobManager != NULL) {
      _JobManager->Stop();
   }
   if (_PersistenceChannel != NULL) {
      _PersistenceChannel->Stop();
   }
  //## end cLocalContext::Stop%1122450443.body
}

BOOL_T cLocalContext::ActivateCorbaObject ()
{
  //## begin cLocalContext::ActivateCorbaObject%1163011502.body preserve=yes
   if (_CorbaObjectActive) {
      return true;
   }
   try {
      STRING_T valid_address;
      if (_ForceCorbaService ||
          ValidAddress(_SkipNetworks, valid_address)) {
         if (!_ForceCorbaService) {
            if (strlen(USEHOST_ENV_STRING) == 0) {
               SafePrintf(USEHOST_ENV_STRING, sizeof(USEHOST_ENV_STRING), "%s=%s", OMNIORB_USEHOSTNAME_VAR, valid_address.c_str());
               int rc = _putenv(USEHOST_ENV_STRING);
               if (rc == 0) {
                  const char * object_ip = getenv(OMNIORB_USEHOSTNAME_VAR);
                  if (object_ip != NULL && _stricmp(object_ip, valid_address.c_str()) == 0) {
                     InfoPrintf("set corba object ip address to %s\n", valid_address.c_str());
                  } else {
                     ErrorPrintf("failed to set corba object ip address to %s\n", valid_address.c_str());
                     return false;
                  }
               } else {
                  ErrorPrintf("failed to set corba object ip address to %s\n", valid_address.c_str());
                  return false;
               }
            }
         }
         if (cResources::FlagSet(PF_DELAYED_ORB_INIT)) {
            cBroker::Initialize();
         }
         STRING_T ior;
         _CellObject = new iCellObject(_Name.c_str(), (void*)this);
         ior = _CellObject->IOR();
         PrintIOR(_Name.c_str(), ior.c_str());
         cCorbaCellProxy * proxy = new cCorbaCellProxy;
   	   proxy->set_CellName(_Name.c_str());
   	   proxy->set_SourceName(_Name.c_str());
   	   proxy->set_IOR(ior.c_str());
   	   proxy->set_ProxyName(_Name.c_str());
         proxy->set_Computer(cSystemUtils::ComputerName());
         proxy->set_Host(cSystemUtils::HostName());
         ULONG_T port = 0;
         STRING_T ip_addr;
         cBroker::DecodeIOR(ior.c_str(), ip_addr, port);
         InfoPrintf("starting CORBA context object on ip address %s port %d ior:\n%s\n", ip_addr.c_str(), port, ior.c_str());
         proxy->set_IPAddress(ip_addr);
         proxy->set_Port(port);
   	   proxy->set_ProcessId(cSystemUtils::ProcessId());
   	   proxy->set_Object(this);
   	   proxy->set_ProcessName(_Process->get_Name().c_str());
         STRING_T serialized_proxy = proxy->Serialize();
   	   _Process->AddService(serialized_proxy.c_str());
         _CorbaObjectActive = true;
#ifdef USE_PROXY_SERVICE
         if (!_IsClientContext) {
            _ProxyService = new cProxyService(_Process, serialized_proxy.c_str(), _Name.c_str());
            _ProxyService->Start();
         }
#endif
         proxy->Release();
      }
   } catch(CORBA::SystemException& ex) {
      ErrorPrintf("CORBA::SystemException: %s\n", (CONST_STRING_T)ex._name());
   } catch(CORBA::Exception& ex) {
      ErrorPrintf("CORBA::Exception: %s\n", (CONST_STRING_T)ex._name());
   } catch(omniORB::fatalException& ex) {
      ErrorPrintf("CORBA::fatalException: %s:%d: %s\n", (CONST_STRING_T)ex.file(), ex.line(), ex.errmsg());
   } catch (...) {
      ErrorPrintf("unhandled exception in cLocalContext::ActivateCorbaObject\n");
   }
   return _CorbaObjectActive;
  //## end cLocalContext::ActivateCorbaObject%1163011502.body
}

void cLocalContext::Create ()
{
  //## begin cLocalContext::Create%1054715292.body preserve=yes
   BOOL_T check_mapping = cResources::FlagSet(PF_CHECK_DEVICE_MAPPING);
   STRING_MAP_T id_map;
   std::map<STRING_T, cContext*>::const_iterator j = _SearchContexts.begin();
   while (j != _SearchContexts.end()) {
      cContext * search_context = (*j).second;
      if (search_context != NULL) {
         search_context->Create();
         j++;
		}
   }
   if (_Created) return;
   InfoPrintf("creating local context %p %s\n", this, _Name.c_str());
   _Created = true;
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
#undef MODULAR_CREATION
#ifdef MODULAR_CREATION
      const char * var_name = var_def->_VarName.c_str();
      cLocalVariable * variable = (cLocalVariable*)var_def->_Variable;
      if (variable == NULL) {
         variable = new cLocalVariable(var_def);
      }
      variable->Create(this);
      if (check_mapping) {
         cDevice * device = Device(var_def->_DeviceName.c_str());
         cMapping * mapping = var_def->_Mapping;
         if (mapping != NULL &&
             device != NULL) {
            int i = 0;
            int elements = var_def->Elements();
            for (i=0; i<elements; i++) {
               CheckMapping(id_map, device, var_def, mapping, i);
            }
         }
      }
#else
      cMapping * mapping = var_def->_Mapping;
      if (mapping != NULL) {
         UCHAR_T refresh_type = var_def->_RefreshType;
         ULONG_T len = mapping->_ItemCount;
         for (ULONG_T i=0; i<len; i++) {
            MAP_ITEM_T * map_item = mapping->MapItem(i);
            if (map_item != NULL) {
               CONST_STRING_T device_name = map_item->device_name;
               if (device_name != NULL) {
                  _ASSERT_COND(_Cell != NULL)
                  cDevice * device = _Cell->Device(device_name);
                  if (device != NULL) {
                     map_item->device = device;
                     UCHAR_T var_type = var_def->_VarType;
                     if (var_type == SH_VAR_ACT) {
                        if (refresh_type == SH_REFRESH_INTERVAL) {
                           ULONG_T cache_value = var_def->_RefreshValue;
                           if (cache_value > 0) {
                              if (map_item->name == NULL) {
                                 if (map_item->address != UNUSED_ADDRESS) {
                                    device->Cache(map_item->buf_spec,
                                                  map_item->address,
                                                  map_item->size,
                                                  SH_REFRESH_INTERVAL,
                                                  cache_value);
                                 }
                              } else {
                                 device->Cache(map_item->buf_spec,
                                               map_item->name,
                                               map_item->size,
                                               SH_REFRESH_INTERVAL,
                                               cache_value);
                              }
                           }
                        } else if (refresh_type == SH_REFRESH_EVENT) {
                           ULONG_T event_code = var_def->_RefreshValue;
                           if (map_item->name == NULL) {
                              if (map_item->address != UNUSED_ADDRESS) {
                                 device->Cache(map_item->buf_spec,
                                               map_item->address,
                                               map_item->size,
                                               SH_REFRESH_EVENT,
                                               event_code);
                              }
                           } else {
                              device->Cache(map_item->buf_spec,
                                            map_item->name,
                                            map_item->size,
                                            SH_REFRESH_EVENT,
                                            event_code);
                           }
                        }
                     } else if (var_type == SH_VAR_SET) {
                        if (map_item->name == NULL) {
                           if (map_item->address != UNUSED_ADDRESS) {
                              device->Buffer(map_item);
                           }
                        } else {
                           device->Buffer(map_item->buf_spec,
                                          map_item->name,
                                          map_item->size);
                        }
                        int dummy = 0;
                     }
                  }
               }
            }
         }
      }
      cVariable * variable = var_def->_Variable;
      if (variable == NULL) {
         variable = new cLocalVariable(var_def);
         if (mapping != NULL) {
            UCHAR_T refresh_type = var_def->_RefreshType;
            ULONG_T len = mapping->_ItemCount;
            UCHAR_T var_type = var_def->_VarType;
            BOOL_T reference_set_variables = cResources::FlagSet(PF_REFERENCE_SET_VARIABLES);
            for (ULONG_T i=0; i<len; i++) {
               MAP_ITEM_T * map_item = mapping->MapItem(i);
               if (map_item != NULL) {
                  cDevice * device = map_item->device;
                  if (device != NULL) {
                     if (refresh_type == SH_REFRESH_INTERVAL) {
                        ULONG_T cache_value = var_def->_RefreshValue;
                        if (cache_value > 0) {
                           LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
                           var_def->GetIndices(i, i1, i2, i3, i4);
                           device->SetVariable(map_item,
                                               (cLocalVariable*)variable,
                                               i1, i2, i3, i4);
                        }
                     } else if ((refresh_type == SH_REFRESH_EVENT) || (reference_set_variables && (var_type == SH_VAR_SET))) {
                        LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
                        var_def->GetIndices(i, i1, i2, i3, i4);
                        device->SetVariable(map_item,
                                            (cLocalVariable*)variable,
                                            i1, i2, i3, i4);
                     }
                     if (check_mapping) {
                        CheckMapping(id_map, device, var_def, mapping, i);
                     }
                  }
               }
            }
         }
      } else {
         // state variables are automatically instantiated
      }
      var_def->_Variable = variable;
#endif
      i++;
   }
  //## end cLocalContext::Create%1054715292.body
}

void cLocalContext::CreateDynamic ()
{
  //## begin cLocalContext::CreateDynamic%1090073690.body preserve=yes
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      if (var_def != NULL && var_def->IsDynamic()) {
         cVariable * variable = var_def->_Variable;
         if (variable == NULL) {
            variable = new cLocalVariable(var_def);
            var_def->_Variable = variable;
         } else {
            // reuse already created variable
         }
      }
      i++;
   }
  //## end cLocalContext::CreateDynamic%1090073690.body
}

ULONG_T cLocalContext::GetVarDefs (STRING_T &var_defs, ULONG_T if_type)
{
  //## begin cLocalContext::GetVarDefs%1054726258.body preserve=yes
   HOSTITF_CACHE_T::const_iterator c = _HostItfCache.find(if_type);
   if (c != _HostItfCache.end()) {
      var_defs = (*c).second.c_str();
      return 0;
   }
   STRING_MAP_T var_names;
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      if (if_type != IF_PROPRIETARY) {
         if (var_def->_SystemFlags & HOST_READ ||
             var_def->_SystemFlags & HOST_WRITE) {
            cVarDef * new_var_def = new cVarDef(*var_def);
            if (VarDefFilter(this, if_type, new_var_def)) {
               DefFilter(if_type, new_var_def);
               STRING_T var_spec = "def ";
               new_var_def->Unparse(var_spec, IGN_VALUES);
               var_defs += var_spec.c_str();
            }
            STRING_T var_name = new_var_def->_VarName;
            STRING_MAP_T::const_iterator vn = var_names.find(var_name.c_str());
            if (vn == var_names.end()) {
               var_names[var_name.c_str()] = var_name.c_str();
            } else {
               ErrorPrintf("variable name %s already defined for host interface %d\n", var_name.c_str(), if_type);
            }
            delete new_var_def;
         }
      } else {
         STRING_T var_spec = "def ";
         var_def->Unparse(var_spec, IGN_VALUES);
         var_defs += var_spec.c_str();
      }
      i++;
   }
#ifdef LOCAL_VARIABLES_ARE_GLOBAL
   ULONG_T size = _VarDefs.size();
   std::map<STRING_T, cContext*>::const_iterator j = _SearchContexts.begin();
   while (j != _SearchContexts.end()) {
      cContext * search_context = (*j).second;
      if (search_context != NULL) {
         size += search_context->GetVarDefs(obj_list);
         j++;
		}
   }
   return size;
#endif
   _HostItfCache[if_type] = var_defs.c_str();
   return 0;
  //## end cLocalContext::GetVarDefs%1054726258.body
}

cCell * cLocalContext::Cell ()
{
  //## begin cLocalContext::Cell%1081425823.body preserve=yes
   return _Cell;
  //## end cLocalContext::Cell%1081425823.body
}

cChannel * cLocalContext::EventChannel ()
{
  //## begin cLocalContext::EventChannel%1073299990.body preserve=yes
   return _EventChannel;
  //## end cLocalContext::EventChannel%1073299990.body
}

ULONG_T cLocalContext::Alarms (ULONG_T selection)
{
  //## begin cLocalContext::Alarms%1089103362.body preserve=yes
   return _AlarmMap.size();
  //## end cLocalContext::Alarms%1089103362.body
}

ULONG_T cLocalContext::Alarms (ULONG_T selection, ALARM_MAP_T &alarms)
{
  //## begin cLocalContext::Alarms%1081425828.body preserve=yes
   ALARM_MAP_T::const_iterator i = _AlarmMap.begin();
   while (i != _AlarmMap.end()) {
      cAlarm * alarm = (*i).second;
      ULONG_T ident = alarm->get_Ident();
      alarms[ident] = alarm; 
      i++;
   }
   return _AlarmMap.size();
  //## end cLocalContext::Alarms%1081425828.body
}

void cLocalContext::ClearAlarm (ULONG_T ident, BOOL_T propagate)
{
  //## begin cLocalContext::ClearAlarm%1081425829.body preserve=yes
   cAlarm * alarm = Alarm(ident);
   if (alarm != NULL) {
      if (propagate) {
         cTimeObject now;
         if (_Dispatcher != NULL) {
            cAlarm * reset_alarm = new cAlarm(*alarm);
            reset_alarm->set_State(false);
            reset_alarm->set_TimeStamp(now);
            _Dispatcher->Send(reset_alarm);
            reset_alarm->Release();
         }
      }
      _AlarmMap.erase(ident);
      if (Alarms(0) == 0) {
         if (_Dispatcher != NULL) {
            cInfo * info = new cInfo(this, IT_ALARM_INFO, 0, "");
            info->set_InfoId(alarm->get_Ident());
            _Dispatcher->Send(info);
            info->Release();
         }
      } else {
         ALARM_MAP_T alarm_map;
         Alarms(0, alarm_map);
         cAlarm * active_alarm = ActiveAlarm(alarm_map);
         if (active_alarm != NULL) {
            if (_Dispatcher != NULL) {
               cInfo * info = new cInfo(this, IT_ALARM_INFO,
                                        active_alarm->get_TextId1(), active_alarm->get_Text1().c_str());
               info->set_InfoId(active_alarm->get_Ident());
               if (active_alarm->get_Param1().size() > 0) {
                  info->set_Param1(active_alarm->get_Param1().c_str());
               }
               if (active_alarm->get_Param2().size() > 0) {
                  info->set_Param2(active_alarm->get_Param2().c_str());
               }
               if (active_alarm->get_Param3().size() > 0) {
                  info->set_Param3(active_alarm->get_Param3().c_str());
               }
               if (active_alarm->get_Param4().size() > 0) {
                  info->set_Param4(active_alarm->get_Param4().c_str());
               }
               _Dispatcher->Send(info);
               info->Release();
            }
         }
      }
      alarm->Release();
   } else {
      InfoPrintf("alarm %08d not set\n", ident);
   }
  //## end cLocalContext::ClearAlarm%1081425829.body
}

void cLocalContext::ClearAlarms (BOOL_T propagate)
{
  //## begin cLocalContext::ClearAlarms%1081425830.body preserve=yes
   while (true) {
      ALARM_MAP_T::const_iterator i = _AlarmMap.begin();
      if (i == _AlarmMap.end()) return;
      cAlarm * alarm = (*i).second;
      ULONG_T ident = alarm->get_Ident();
      ClearAlarm(ident, propagate);
   }
  //## end cLocalContext::ClearAlarms%1081425830.body
}

void cLocalContext::GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value)
{
  //## begin cLocalContext::GetDeviceValue%1082984460.body preserve=yes
CHECK_CELL
   if (_Cell != NULL) {
      _Cell->GetDeviceValue(buf_spec, address, value);
   }
  //## end cLocalContext::GetDeviceValue%1082984460.body
}

void cLocalContext::SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value)
{
  //## begin cLocalContext::SetDeviceValue%1082984461.body preserve=yes
CHECK_CELL
   if (_Cell != NULL) {
      _Cell->SetDeviceValue(buf_spec, address, value);
   }
  //## end cLocalContext::SetDeviceValue%1082984461.body
}

cDevice * cLocalContext::Device (CONST_STRING_T name)
{
  //## begin cLocalContext::Device%1085574712.body preserve=yes
   if (_Cell != NULL) {
      return _Cell->Device(name);
   } else {
      return NULL;
   }
  //## end cLocalContext::Device%1085574712.body
}

void cLocalContext::ExecuteCommand (CONST_STRING_T program_name, ULONG_T command)
{
  //## begin cLocalContext::ExecuteCommand%1089292613.body preserve=yes
   cProgram * program = Program(program_name);
   if (program != NULL) {
      program->ExecuteCommand(command);
   } else {
      throw cError(CELL_UNKNOWN_PROGRAM, 0, program_name);
   }
  //## end cLocalContext::ExecuteCommand%1089292613.body
}

void cLocalContext::ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request)
{
  //## begin cLocalContext::ExecuteRequest%1133771768.body preserve=yes
   cProgram * program = Program(program_name);
   if (program != NULL) {
      program->ExecuteRequest(reply, request);
   }
  //## end cLocalContext::ExecuteRequest%1133771768.body
}

void cLocalContext::Save (UCHAR_T refresh_type, ULONG_T refresh_value)
{
  //## begin cLocalContext::Save%1092293195.body preserve=yes
CHECK_CELL
   if (_Cell != NULL) {
      _Cell->Save(refresh_type, refresh_value);
   }
  //## end cLocalContext::Save%1092293195.body
}

void cLocalContext::Download (ULONG_T ctrl)
{
  //## begin cLocalContext::Download%1091687832.body preserve=yes
CHECK_CELL
   if (_Cell != NULL) {
      _Cell->Download(ctrl);
   }
  //## end cLocalContext::Download%1091687832.body
}

void cLocalContext::Upload (ULONG_T ctrl)
{
  //## begin cLocalContext::Upload%1091687833.body preserve=yes
CHECK_CELL
   if (_Cell != NULL) {
      _Cell->Upload(ctrl);
   }
  //## end cLocalContext::Upload%1091687833.body
}

void cLocalContext::ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_file, STRING_T &buf)
{
   //## begin cLocalContext::ReadFile%1091699605.body preserve=yes
   cObjectLock __lock__(&_DataFileMutex);
   std::map<STRING_T, cSubFile*> sub_file_map;
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      cLocalVariable * variable = (cLocalVariable*)var_def->_Variable;
      if (variable != NULL) {
         STRING_T var_name = var_def->_VarName;
         UCHAR_T var_type = var_def->_VarType;
         BOOL_T header_flag = variable->GetFlag(Header);
         if (header_flag) {
            STRING_T sub_file_name = "Header";
            cSubFile * _sub_file = NULL;
            std::map<STRING_T, cSubFile*>::const_iterator j = sub_file_map.find(sub_file_name.c_str());
            if (j == sub_file_map.end()) {
               _sub_file = new cSubFile(sub_file_name.c_str());
               sub_file_map[sub_file_name.c_str()] = _sub_file;
            }
            else {
               _sub_file = (*j).second;
            }
            _sub_file->AddVariable(var_name.c_str(), variable);
         }
         else if (var_type == SH_VAR_SET) {
            STRING_T sub_file_name = var_def->_FileName;
            if (strlen(sub_file) > 0) {
               if (sub_file[0] == '-') {
                  if ((strcmp(sub_file, "-") == 0) && sub_file_name.size() == 0) {
                     i++;
                     continue;
                  }
                  else {
                     if (_stricmp(&sub_file[1], sub_file_name.c_str()) == 0) {
                        i++;
                        continue;
                     }
                  }
               }
               else {
                  if (_stricmp(sub_file, sub_file_name.c_str()) != 0) {
                     i++;
                     continue;
                  }
               }
            }
            if (sub_file_name.size() == 0) {
               sub_file_name = "free";
            }
            cSubFile * _sub_file = NULL;
            std::map<STRING_T, cSubFile*>::const_iterator j = sub_file_map.find(sub_file_name.c_str());
            if (j == sub_file_map.end()) {
               _sub_file = new cSubFile(sub_file_name.c_str());
               sub_file_map[sub_file_name.c_str()] = _sub_file;
            }
            else {
               _sub_file = (*j).second;
            }
            _sub_file->AddVariable(var_name.c_str(), (cLocalVariable*)var_def->_Variable);
         }
      }
      i++;
   }
   STRING_T dm;
   std::map<STRING_T, cSubFile*>::const_iterator j = sub_file_map.begin();
   while (j != sub_file_map.end()) {
      cSubFile * _sub_file = (*j).second;
      if (_sub_file != NULL) {
         STRING_T db;
         _sub_file->PrintVariables(db);
         dm += db;
         delete _sub_file;
      }
      j++;
   }
   buf = dm;
   //## end cLocalContext::ReadFile%1091699605.body
}

void cLocalContext::ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_file, cStringBuffer &buf)
{
   //## begin cLocalContext::ReadFile%1091699605.body preserve=yes
   cObjectLock __lock__(&_DataFileMutex);
   std::map<STRING_T, cSubFile*> sub_file_map;
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      cLocalVariable * variable = (cLocalVariable*)var_def->_Variable;
      if (variable != NULL) {
         STRING_T var_name = var_def->_VarName;
         UCHAR_T var_type = var_def->_VarType;
         BOOL_T header_flag = variable->GetFlag(Header);
         if (header_flag) {
            STRING_T sub_file_name = "Header";
            cSubFile * _sub_file = NULL;
            std::map<STRING_T, cSubFile*>::const_iterator j = sub_file_map.find(sub_file_name.c_str());
            if (j == sub_file_map.end()) {
               _sub_file = new cSubFile(sub_file_name.c_str());
               sub_file_map[sub_file_name.c_str()] = _sub_file;
            }
            else {
               _sub_file = (*j).second;
            }
            _sub_file->AddVariable(var_name.c_str(), variable);
         }
         else if (var_type == SH_VAR_SET) {
            STRING_T sub_file_name = var_def->_FileName;
            if (strlen(sub_file) > 0) {
               if (sub_file[0] == '-') {
                  if ((strcmp(sub_file, "-") == 0) && sub_file_name.size() == 0) {
                     i++;
                     continue;
                  }
                  else {
                     if (_stricmp(&sub_file[1], sub_file_name.c_str()) == 0) {
                        i++;
                        continue;
                     }
                  }
               }
               else {
                  if (_stricmp(sub_file, sub_file_name.c_str()) != 0) {
                     i++;
                     continue;
                  }
               }
            }
            if (sub_file_name.size() == 0) {
               sub_file_name = "free";
            }
            cSubFile * _sub_file = NULL;
            std::map<STRING_T, cSubFile*>::const_iterator j = sub_file_map.find(sub_file_name.c_str());
            if (j == sub_file_map.end()) {
               _sub_file = new cSubFile(sub_file_name.c_str());
               sub_file_map[sub_file_name.c_str()] = _sub_file;
            }
            else {
               _sub_file = (*j).second;
            }
            _sub_file->AddVariable(var_name.c_str(), (cLocalVariable*)var_def->_Variable);
         }
      }
      i++;
   }
   STRING_T dm;
   std::map<STRING_T, cSubFile*>::const_iterator j = sub_file_map.begin();
   while (j != sub_file_map.end()) {
      cSubFile * _sub_file = (*j).second;
      if (_sub_file != NULL) {
         _sub_file->PrintVariables(buf);
         delete _sub_file;
      }
      j++;
   }
   //## end cLocalContext::ReadFile%1091699605.body
}

void cLocalContext::WriteFile(CONST_STRING_T file_name, CONST_STRING_T sub_file, CONST_STRING_T buf)
{
  //## begin cLocalContext::WriteFile%1091699606.body preserve=yes
CHECK_CELL
   cObjectLock __lock__(&_DataFileMutex);
   cFileContext file_context;
   cStyxParser parser;
   parser.ParseDatabaseFromString(&file_context, buf);
   file_context.Create();
   if (_Cell != NULL) {
      _Cell->SetDevicesBuffered(true);
      _Cell->SetDevicesCached(true);
   }
   file_context.Copy(this, sub_file);
   if (_Cell != NULL) {
      _Cell->SetDevicesBuffered(false);
      _Cell->SetDevicesCached(false);
   }
  //## end cLocalContext::WriteFile%1091699606.body
}

void cLocalContext::Copy (cContext *src_context, CONST_STRING_T sub_file, BOOL_T show_errors, BOOL_T buffered)
{
  //## begin cLocalContext::Copy%1102418726.body preserve=yes
CHECK_CELL
   cObjectLock __lock__(&_DataFileMutex);
   if ((_Cell != NULL) && buffered) {
      _Cell->SetDevicesBuffered(true);
      _Cell->SetDevicesCached(true);
   }
   cPersistenceManager * persistence_manager = PersistenceManager();
   if (persistence_manager != NULL) {
      persistence_manager->SetBuffered(true);
   }
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      STRING_T var_name = var_def->_VarName;
      cVariable * dst = var_def->_Variable;
      if (dst != NULL) {
         cVariable * src = src_context->Variable(var_name.c_str());
         if (src != NULL) {
            STRING_T dst_sub_file = dst->FileName();
            ULONG_T dst_var_type = dst->VarType();
            if (dst_var_type == SH_VAR_SET &&
                (_stricmp(dst_sub_file.c_str(), sub_file) == 0)) {
               src->Copy(dst, show_errors);
            }
         }
      }
      i++;
   }
   if ((_Cell != NULL) && buffered) {
      _Cell->SetDevicesBuffered(false);
      _Cell->SetDevicesCached(false);
   }
   if (persistence_manager != NULL) {
      persistence_manager->SetBuffered(false);
   }
  //## end cLocalContext::Copy%1102418726.body
}

void cLocalContext::LoadVariables ()
{
  //## begin cLocalContext::LoadVariables%1084445993.body preserve=yes
CHECK_CELL
   BOOL_T buffered_state = _Cell->GetDevicesBuffered();
   if (buffered_state != true) {
      _Cell->SetDevicesBuffered(true);
   }
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
//      if (var_def->_VarType != SH_VAR_ACT) {
      if (var_def->_VarType == SH_VAR_SET) {
         cLocalVariable * local_var = (cLocalVariable*)var_def->_Variable;
         if (local_var != NULL) {
            try {
               local_var->LoadVariable();
            } catch (cError & e) {
               ErrorPrintf("%s while loading variable %s\n",
                           e.ErrMsg().c_str(), var_def->_VarName.c_str());
            } catch (...) {
               ErrorPrintf("unknown exception while loading variable %s\n",
                           var_def->_VarName.c_str());
            }
         } else {
            ErrorPrintf("no local variable instance for %s loading variable\n",
                        var_def->_VarName.c_str());
         }
      }
      else if (var_def->_VarType == SH_VAR_VOLATILE) {
         cLocalVariable * local_var = (cLocalVariable*)var_def->_Variable;
         if (local_var != NULL) {
             UCHAR_T ptype = var_def->_PersistenceType;
             if (ptype != UNDEFINED && ptype != SH_RAM && var_def->_Mapping) {
                ErrorPrintf("Volatile/persist/Mapping Variablenname %s\n", var_def->_VarName.c_str());
             }
         }
      }
      i++;
   }
   if (buffered_state != true) {
      _Cell->SetDevicesBuffered(buffered_state);
   }
  //## end cLocalContext::LoadVariables%1084445993.body
}

void cLocalContext::SaveVariables ()
{
  //## begin cLocalContext::SaveVariables%1091180972.body preserve=yes
   BOOL_T cached_state = _Cell->GetDevicesCached();
   if (cached_state != true) {
      _Cell->SetDevicesCached(true);
   }
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      if (var_def->_VarType != SH_VAR_ACT) {
         cLocalVariable * local_var = (cLocalVariable*)var_def->_Variable;
         if (local_var != NULL) {
            try {
               local_var->SaveVariable();
            } catch(cError & e) {
               ErrorPrintf("%s while saving variable %s\n",
                           e.ErrMsg().c_str(), var_def->_VarName.c_str());
            } catch (...) {
               ErrorPrintf("unknown exception while saving variable %s\n",
                           var_def->_VarName.c_str());
            }
         } else {
            ErrorPrintf("no local variable instance for %s saving variable\n",
                        var_def->_VarName.c_str());
         }
      }
      i++;
   }
   if (cached_state != true) {
      _Cell->SetDevicesCached(cached_state);
   }
  //## end cLocalContext::SaveVariables%1091180972.body
}

void cLocalContext::SetJob (cJobSpec *job_spec)
{
  //## begin cLocalContext::SetJob%1093930661.body preserve=yes
   if (_JobManager != NULL) {
      _JobManager->SetJob(job_spec);
   }
  //## end cLocalContext::SetJob%1093930661.body
}

cJobSpec * cLocalContext::GetJobSpec (CONST_STRING_T job_name)
{
  //## begin cLocalContext::GetJobSpec%1093930662.body preserve=yes
   if (_JobManager != NULL) {
      return _JobManager->GetJobSpec(job_name);
   }
   return NULL;
  //## end cLocalContext::GetJobSpec%1093930662.body
}

void cLocalContext::CopyCommand (ULONG_T src, ULONG_T dst, BOOL_T exchange, ULONG_T copy_flags)
{
  //## begin cLocalContext::CopyCommand%1100714371.body preserve=yes
   BOOL_T buffered_state = _Cell->GetDevicesBuffered();
   if ((copy_flags & CP_FLAG_NOTCHANGE_DEVBUFFERED_STATE) &&
       (buffered_state != true)) {
      _Cell->SetDevicesBuffered(true);
   }
   cPersistenceManager * persistence_manager = PersistenceManager();
   if (persistence_manager != NULL) {
      persistence_manager->SetBuffered(true);
   }
   int size = _VarDefs.size(); // HA 230805
   int vardef_no = 0; // HA 230805
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      vardef_no++; // HA 230805
      if (copy_flags & CP_FLAG_SUPPRESS_PROGRESS) {
         // suppress raising of progress events
      } else {
         SetProgress(COPY_FGBG_DATA_PROGRESS, (100 * vardef_no) / size); // HA 230805
         UpdateUi();
      }
      cVarDef * var_def = (*i).second;
      if (var_def != NULL) {
         BOOL_T bg_var = var_def->_BackgroundVar;
         if (bg_var) {
            cLocalVariable * variable = (cLocalVariable*)var_def->_Variable;
            if (variable != NULL) {
               try {
                  variable->CopyCommand(src, dst, exchange, copy_flags);
               } catch (cError & e) {
                  ErrorPrintf("%s while copying variable %s\n",
                              e.ErrMsg().c_str(), var_def->_VarName.c_str());
               } catch (...) {
                  ErrorPrintf("unknown exception while copying variable %s\n",
                              var_def->_VarName.c_str());
               }
            } else {
               ErrorPrintf("no local variable instance for %s in copy process\n",
                           var_def->_VarName.c_str());
            }
         }
      }
      i++;
   }
   if ((copy_flags & CP_FLAG_NOTCHANGE_DEVBUFFERED_STATE) &&
       (buffered_state != true)) {
      _Cell->SetDevicesBuffered(buffered_state);
   }
   if (persistence_manager != NULL) {
      persistence_manager->SetBuffered(false);
   }
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
      if (dst == SHADOW_DATASET) {
         PersistShadowDataset();
         ResetShadowBuffers();
         SetShadowChanges(0);
      }
   }
  //## end cLocalContext::CopyCommand%1100714371.body
}

STRING_T cLocalContext::Compare (ULONG_T flags)
{
  //## begin cLocalContext::Compare%1108566002.body preserve=yes
   STRING_T result;
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      if (var_def != NULL) {
         STRING_T var_name = var_def->_VarName;
         cLocalVariable * variable = (cLocalVariable*)var_def->_Variable;
         if (variable != NULL) {
            UCHAR_T var_type = variable->VarType();
            if (var_type == SH_VAR_SET) {
               if (var_def->_DataType != SH_BYTE) {
                  STRING_T variable_result;
                  if (variable->Compare(result, flags)) {
                     result += variable_result.c_str();
                  }
               }
            }
         }
         i++;
      }
   }
   return result;
  //## end cLocalContext::Compare%1108566002.body
}

BOOL_T cLocalContext::SetAlarm (cAlarm *alarm)
{
  //## begin cLocalContext::SetAlarm%1122475152.body preserve=yes
   cObjectLock __lock__(&_AlarmMutex);
   ULONG_T ident = alarm->get_Ident();
   BOOL_T state = alarm->get_State();
   if (state) {
      if (Alarm(ident) == NULL) {
         alarm->AddRef();
         _AlarmMap[ident] = alarm;
         if (_Dispatcher != NULL) {
//         _Dispatcher->Send(alarm);
            cInfo * info = new cInfo(this, IT_ALARM_INFO,
                                     alarm->get_TextId1(), alarm->get_Text1().c_str());
            info->set_InfoId(alarm->get_Ident());
            if (alarm->get_Param1().size() > 0) {
               info->set_Param1(alarm->get_Param1().c_str());
            }
            if (alarm->get_Param2().size() > 0) {
               info->set_Param2(alarm->get_Param2().c_str());
            }
            if (alarm->get_Param3().size() > 0) {
               info->set_Param3(alarm->get_Param3().c_str());
            }
            if (alarm->get_Param4().size() > 0) {
               info->set_Param4(alarm->get_Param4().c_str());
            }
            _Dispatcher->Send(info);
            info->Release();
         }
      } else {
         return true;
      }
   } else {
      if (Alarm(ident) != NULL) {
         ClearAlarm(ident, false);
      } else {
         return true;
      }
   }
   return false;
  //## end cLocalContext::SetAlarm%1122475152.body
}

cAlarm * cLocalContext::Alarm (ULONG_T ident)
{
  //## begin cLocalContext::Alarm%1122475153.body preserve=yes
   ALARM_MAP_T::const_iterator i = _AlarmMap.find(ident);
   if (i == _AlarmMap.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cLocalContext::Alarm%1122475153.body
}

void cLocalContext::Send (cTransientObject *object)
{
  //## begin cLocalContext::Send%1122475164.body preserve=yes
   UCHAR_T object_type = (UCHAR_T)object->get_Type();
   if (object_type == OT_ALARM) {
      cAlarm * alarm = (cAlarm*)object;
      if (SetAlarm(alarm)) {
         return;
      }
   }
   if (_Dispatcher == NULL) {
/// PR 28.04.06 ignore it simply
///      throw cError(CELL_NO_DISPATCHER, 0);
   } else {
      _Dispatcher->Send(object);
      UpdateUi();
   }
  //## end cLocalContext::Send%1122475164.body
}

cProgram * cLocalContext::Program (CONST_STRING_T name)
{
  //## begin cLocalContext::Program%1122475166.body preserve=yes
   std::map<STRING_T,cProgram*>::const_iterator i = _Programs.find(name);
   if (i == _Programs.end()) {
      return NULL;
   } else {
      cProgram * program = (*i).second;
      return program;
   }
  //## end cLocalContext::Program%1122475166.body
}

void cLocalContext::SetJob (CONST_STRING_T job_spec)
{
  //## begin cLocalContext::SetJob%1122529737.body preserve=yes
   cJobSpec * new_job_spec = new cJobSpec;
   new_job_spec->Construct(job_spec);
   SetJob(new_job_spec);
  //## end cLocalContext::SetJob%1122529737.body
}

STRING_T cLocalContext::GetJobSpecText (CONST_STRING_T job_name)
{
  //## begin cLocalContext::GetJobSpecText%1122529738.body preserve=yes
   if (_JobManager != NULL) {
      cJobSpec * job_spec = _JobManager->GetJobSpec(job_name);
      if (job_spec != NULL) {
         STRING_T spec_text = job_spec->Serialize();
         return spec_text;
      }
   }
   throw cError(NO_SUCH_JOB, 0, job_name);
  //## end cLocalContext::GetJobSpecText%1122529738.body
}

cPersistenceChannel * cLocalContext::PersistenceChannel ()
{
  //## begin cLocalContext::PersistenceChannel%1122619258.body preserve=yes
   return _PersistenceChannel;
  //## end cLocalContext::PersistenceChannel%1122619258.body
}

void cLocalContext::StartServices ()
{
  //## begin cLocalContext::StartServices%1122475148.body preserve=yes
   if (!_IsRootContext) {
      return;
   }
   if (_CorbaService) {
      if (!ActivateCorbaObject()) {
         _ObjectService = new cObjectService(this);
         _ObjectService->Start();
      }
   }
  //## end cLocalContext::StartServices%1122475148.body
}

void cLocalContext::StopServices ()
{
  //## begin cLocalContext::StopServices%1122475149.body preserve=yes
   if (_ObjectService != NULL) {
      _ObjectService->Stop();
   }
   if (_CellObject != NULL) {
      _CellObject->Remove();
      _CellObject = NULL;
   }
#ifdef USE_PROXY_SERVICE
   if (!_IsClientContext) {
      if (_ProxyService != NULL) {
         _ProxyService->Stop();
      }
   }
#endif
  //## end cLocalContext::StopServices%1122475149.body
}

void cLocalContext::StartPrograms ()
{
  //## begin cLocalContext::StartPrograms%1122475150.body preserve=yes
   std::map<STRING_T,cProgram*>::const_iterator i = _Programs.begin();
   while (i != _Programs.end()) {
      cProgram * program = (*i).second;
      program->Start();
      i++;
   }
  //## end cLocalContext::StartPrograms%1122475150.body
}

void cLocalContext::StopPrograms ()
{
  //## begin cLocalContext::StopPrograms%1122475151.body preserve=yes
   std::map<STRING_T,cProgram*>::const_iterator i = _Programs.begin();
   while (i != _Programs.end()) {
      cProgram * program = (*i).second;
      program->Stop();
      i++;
   }
  //## end cLocalContext::StopPrograms%1122475151.body
}

void cLocalContext::CreatePersistenceChannel ()
{
  //## begin cLocalContext::CreatePersistenceChannel%1138346769.body preserve=yes
   InfoPrintf("creating persistence channel ...\n");
   Initialize(SH_PRE_LOAD_DATA); // HA130206
   _PersistenceChannel = new cPersistenceChannel(this);
   _PersistenceChannel->Start();
   InfoPrintf("creating persistence channel done\n");
   if (_PersistenceChannel->DataInitialized()) {
      _RunFlags |= RF_BBRAM_INITIALIZED;
      InfoPrintf("detected data initialization:initialize persistent storage\n");
      Initialize(SH_INITIALIZE_DATA);
      InfoPrintf("persistent storage initialized\n");
   }
   Initialize(SH_DATA_INITIALIZED);
  //## end cLocalContext::CreatePersistenceChannel%1138346769.body
}

void cLocalContext::CreatePrograms ()
{
  //## begin cLocalContext::CreatePrograms%1138346770.body preserve=yes
   if (_ConfigObject == NULL) {
      return;
   }
   InfoPrintf("creating programs ...\n");
   CONFOBJ_VECTOR_T program_vec;
   _ConfigObject->PropertyValue("Programs", program_vec);
   ULONG_T programs = program_vec.size();
   for (ULONG_T i=0; i<programs; i++) {
      cConfigurationObject * program_obj = program_vec[i];
      InfoPrintf("creating program %s ...\n", program_obj->get_Name().c_str());
      CreateProgram(program_obj, this);
      InfoPrintf("creating program %s done\n", program_obj->get_Name().c_str());
   }
   InfoPrintf("creating programs done\n");
  //## end cLocalContext::CreatePrograms%1138346770.body
}

void cLocalContext::SetCellName ()
{
  //## begin cLocalContext::SetCellName%1138346771.body preserve=yes
   if (_CellName.size() > 0) {
      STRING_T new_cell_name;
      try {
         cVarRef * var_ref = VarRef(_CellName.c_str());
         var_ref->GetValue(new_cell_name);
      } catch (cError & e) {
      } catch (...) {
      }
      if (new_cell_name.size() > 0) {
         _CellName = new_cell_name;
      }
      _Name = _CellName;
   }
  //## end cLocalContext::SetCellName%1138346771.body
}

void cLocalContext::CreateProgram (cConfigurationObject *program_obj, cContext *context)
{
  //## begin cLocalContext::CreateProgram%1122475158.body preserve=yes
   cProgram * program = cProgramFactory::CreateProgram(program_obj, context);
   if (program != NULL) {
CHECK_CELL
      STRING_T program_name = program->get_Name();
      _Programs[program_name.c_str()] = program;
      if (_Cell != NULL) {
         _Cell->ListenTo(program);
         if (_Dispatcher != NULL) {
            _Dispatcher->Connect(program);
         }
      }
   } else {
      STRING_T program_name = program_obj->get_Name();
      throw cError(CELL_CREATE_PROGRAM, 0, program_name.c_str());
   }
  //## end cLocalContext::CreateProgram%1122475158.body
}

void cLocalContext::PrintIOR (CONST_STRING_T context_name, CONST_STRING_T ior)
{
  //## begin cLocalContext::PrintIOR%1132068351.body preserve=yes
   if (_PrintIOR) {
      cIniFile ini_file(_IORFile.c_str());
      ini_file.WriteValue("Servers", context_name, ior);
   }
  //## end cLocalContext::PrintIOR%1132068351.body
}

BOOL_T cLocalContext::Initialize (ULONG_T step)
{
  //## begin cLocalContext::Initialize%1122450440.body preserve=yes
   if (!_IsRootContext) {
      return true;
   }
   InfoPrintf("CCS init call step %d ...\n", step);
   if (_MdlInitFuncAddress == NULL) {
      _MdlInitFuncAddress = cCustomFunctions::MdlInitFuncAddress();
   }
   if (_MdlInitFuncAddress == NULL) {
      InfoPrintf("no CCS init function address\n");
      return true;
   } else {
      BOOL_T success = false;
      BOOL_T exception_occured = false;
      cError error;
      try {
         success = _MdlInitFuncAddress(step, this);
      } catch (cError & e) {
         exception_occured = true;
         error = cError(CCS_INIT_FUNCTION_FAILURE, 0, cConvUtils::StringValue(step).c_str(), e.ErrMsg().c_str());
      } catch (...) {
         exception_occured = true;
         error = cError(CCS_INIT_FUNCTION_FAILURE, 0, cConvUtils::StringValue(step).c_str(), "unhandled exception");
      }
      if (success) {
         InfoPrintf("CCS init call step %d done\n", step);
      } else {
         if ((_RunFlags & RF_BBRAM_INITIALIZED)) {
            if (cResources::FlagSet(PF_CLEANUP_ON_STARTUP_ERROR)) {
               if (_PersistenceChannel != NULL) {
                  _PersistenceChannel->Stop();
                  _PersistenceChannel->Clear();
               }
               if (_ShadowManager != NULL) {
                  _ShadowManager->Stop();
                  _ShadowManager->Clear();
               }
            }
         }
         if (exception_occured) {
            throw error;
         } else {
            throw cError(CCS_INIT_FUNCTION_FAILURE, 0, cConvUtils::StringValue(step).c_str(), "");
         }
      }
      return success;
   }
  //## end cLocalContext::Initialize%1122450440.body
}

ULONG_T cLocalContext::VarDefFilter (cContext *context, ULONG_T if_type, cVarDef *var_def)
{
  //## begin cLocalContext::VarDefFilter%1132999007.body preserve=yes
   if (_VarDefFilterFuncAddress == NULL) {
      _VarDefFilterFuncAddress = cCustomFunctions::VarDefFilterFuncAddress();
   }
   if (_VarDefFilterFuncAddress == NULL) {
      return 1;
   } else {
      return _VarDefFilterFuncAddress(context, if_type, var_def);
   }
  //## end cLocalContext::VarDefFilter%1132999007.body
}

cAlarm * cLocalContext::ActiveAlarm (ALARM_MAP_T &alarms)
{
  //## begin cLocalContext::ActiveAlarm%1170178867.body preserve=yes
   cAlarm * active_alarm = NULL;
   if (alarms.size() > 0) {
      ULONG_T max = 0;
      ALARM_MAP_T::const_iterator i = alarms.begin();
      while (i != alarms.end()) {
         cAlarm * alarm = (*i).second;
         ULONG_T time_stamp = alarm->get_TimeStamp();
         if (time_stamp > max) {
            max = time_stamp;
            active_alarm = alarm;
         }
         i++;
      }
   }
   return active_alarm;
  //## end cLocalContext::ActiveAlarm%1170178867.body
}

void cLocalContext::CheckMapping (STRING_MAP_T &id_map, cDevice *device, cVarDef *var_def, cMapping *mapping, int pos)
{
  //## begin cLocalContext::CheckMapping%1171386481.body preserve=yes
   MAP_ITEM_T * map_item = mapping->MapItem(pos);
   if (map_item->name != NULL) {
      return;
   }
   ULONG_T address = map_item->address;
   if (address == (ULONG_T)-1) {
      return;
   }
   char log_file[0x100] = {0};
   SafePrintf(log_file, sizeof(log_file), "%s/%s.map", cResources::LogPath().c_str(), device->get_Name().c_str());
   UCHAR_T var_type = var_def->_VarType;
   CONST_STRING_T buf_spec = map_item->buf_spec;
   STRING_T var_name = var_def->_VarName;
   LONG_T i1 = -1, i2 = -1, i3 = -1, i4 = -1;
   var_def->GetIndices(pos, i1, i2, i3, i4);
   const char * var_type_name = "?";
   switch (var_type) {
   case SH_VAR_ACT: var_type_name = "act"; break;
   case SH_VAR_SET: var_type_name = "set"; break;
   case SH_VAR_VOLATILE: var_type_name = "volatile"; break;
   }
   int dims = var_def->Dims();
   char key[0x100] = {0};
   SafePrintf(key, sizeof(key), "%s.%s:%08x", device->get_Name().c_str(), map_item->buf_spec, address);
   char var_ref[0x100] = {0};
   if (dims == 0) {
      SafePrintf(var_ref, sizeof(var_ref), "%s", var_name.c_str());
   } else if (dims == 1) {
      SafePrintf(var_ref, sizeof(var_ref), "%s[%d]", var_name.c_str(), i1);
   } else if (dims == 2) {
      SafePrintf(var_ref, sizeof(var_ref), "%s[%d][%d]", var_name.c_str(), i1, i2);
   } else if (dims == 3) {
      SafePrintf(var_ref, sizeof(var_ref), "%s[%d][%d][%d]", var_name.c_str(), i1, i2, i3);
   } else if (dims == 4) {
      SafePrintf(var_ref, sizeof(var_ref), "%s[%d][%d][%d][%d]", var_name.c_str(), i1, i2, i3, i4);
   }
   STRING_MAP_T::const_iterator i = id_map.find(key);
   if (i == id_map.end()) {
      id_map[key] = STRING_T(var_ref);
   } else {
      STRING_T mk = (*i).first;
      STRING_T vr = (*i).second;
      ErrorPrintf("%s: address %s already mapped for %s type %s\n",
                  var_ref, mk.c_str(), vr.c_str(), var_type_name);
      FILE * stream = fopen(log_file, "a");
      if (stream != NULL) {
         fprintf(stream, "%s: address %s already mapped for %s type %s\n",
                 var_ref, mk.c_str(), vr.c_str(), var_type_name);
         fclose(stream);
      }
   }
   UCHAR_T map_data_type = map_item->data_type;
   if (!device->MappingValid(buf_spec, address, map_data_type)) {
      const char * data_type_name = "?";
      switch (map_data_type) {
      case SH_VOID:
         data_type_name = "void";
         break;
      case SH_CHAR:
         data_type_name = "char/bool";
         break;
      case SH_UCHAR:
         data_type_name = "uchar/bool";
         break;
      case SH_SHORT:
         data_type_name = "short";
         break;
      case SH_USHORT:
         data_type_name = "ushort";
         break;
      case SH_LONG:
         data_type_name = "long";
         break;
      case SH_ULONG:
         data_type_name = "ulong";
         break;
      case SH_FLOAT:
         data_type_name = "float";
         break;
      case SH_DOUBLE:
         data_type_name = "double";
         break;
      case SH_STRING:
         data_type_name = "string";
         break;
      case SH_WSTRING:
         data_type_name = "wstring";
         break;
      case SH_BYTE:
         data_type_name = "byte";
         break;
      case SH_OBJECT:
         data_type_name = "object";
         break;
      case SH_BIT_8:
         data_type_name = "bit8";
         break;
      case SH_BIT_16:
         data_type_name = "bit16";
         break;
      case SH_BIT_32:
         data_type_name = "bit32";
         break;
      }
      ErrorPrintf("invalid mapping for %s: %s:%08x type %s\n",
                  var_ref, buf_spec, address, data_type_name);
      FILE * stream = fopen(log_file, "a");
      if (stream != NULL) {
         fprintf(stream, "invalid mapping for %s: %s:%08x type %s\n",
                 var_ref, buf_spec, address, data_type_name);
         fclose(stream);
      }
   }
  //## end cLocalContext::CheckMapping%1171386481.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cLocalContext::get_CorbaService () const
{
  //## begin cLocalContext::get_CorbaService%42E73CF701E4.get preserve=no
  return _CorbaService;
  //## end cLocalContext::get_CorbaService%42E73CF701E4.get
}

void cLocalContext::set_CorbaService (BOOL_T value)
{
  //## begin cLocalContext::set_CorbaService%42E73CF701E4.set preserve=no
  _CorbaService = value;
  //## end cLocalContext::set_CorbaService%42E73CF701E4.set
}

BOOL_T cLocalContext::get_ForceCorbaService () const
{
  //## begin cLocalContext::get_ForceCorbaService%4552251A0148.get preserve=no
  return _ForceCorbaService;
  //## end cLocalContext::get_ForceCorbaService%4552251A0148.get
}

void cLocalContext::set_ForceCorbaService (BOOL_T value)
{
  //## begin cLocalContext::set_ForceCorbaService%4552251A0148.set preserve=no
  _ForceCorbaService = value;
  //## end cLocalContext::set_ForceCorbaService%4552251A0148.set
}

STRING_VECTOR_T cLocalContext::get_SkipNetworks () const
{
  //## begin cLocalContext::get_SkipNetworks%4561ECB3030D.get preserve=no
  return _SkipNetworks;
  //## end cLocalContext::get_SkipNetworks%4561ECB3030D.get
}

void cLocalContext::set_SkipNetworks (STRING_VECTOR_T value)
{
  //## begin cLocalContext::set_SkipNetworks%4561ECB3030D.set preserve=no
  _SkipNetworks = value;
  //## end cLocalContext::set_SkipNetworks%4561ECB3030D.set
}

BOOL_T cLocalContext::get_IsClientContext () const
{
  //## begin cLocalContext::get_IsClientContext%42EFABD70109.get preserve=no
  return _IsClientContext;
  //## end cLocalContext::get_IsClientContext%42EFABD70109.get
}

void cLocalContext::set_IsClientContext (BOOL_T value)
{
  //## begin cLocalContext::set_IsClientContext%42EFABD70109.set preserve=no
  _IsClientContext = value;
  //## end cLocalContext::set_IsClientContext%42EFABD70109.set
}

ULONG_T cLocalContext::get_RunLevel () const
{
  //## begin cLocalContext::get_RunLevel%43D9C40502F3.get preserve=no
  return _RunLevel;
  //## end cLocalContext::get_RunLevel%43D9C40502F3.get
}

ULONG_T cLocalContext::get_RunFlags () const
{
  //## begin cLocalContext::get_RunFlags%43D9C42F0264.get preserve=no
  return _RunFlags;
  //## end cLocalContext::get_RunFlags%43D9C42F0264.get
}

cPersistenceManager * cLocalContext::PersistenceManager() const
{
   if (_PersistenceChannel == NULL) {
      return NULL;
   } else {
      return _PersistenceChannel->PersistenceManager();
   }
}

void cLocalContext::EmitChanges()
{
   if (cResources::FlagSet(PF_EMIT_CHANGES)) {
      std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
      while (i != _VarDefs.end()) {
         cVarDef * var_def = (*i).second;
         cLocalVariable * local_var = (cLocalVariable*)var_def->_Variable;
         if (local_var != NULL) {
            ULONG_T ptype = local_var->PersistenceType();
            if (ptype != UNDEFINED && ptype != SH_RAM) {
               try {
                  local_var->EmitChanges();
               } catch (cError & e) {
                  ErrorPrintf("%s emitting changes of variable %s\n",
                              e.ErrMsg().c_str(), var_def->_VarName.c_str());
               } catch (...) {
                  ErrorPrintf("unknown exception emitting changes of variable %s\n",
                              var_def->_VarName.c_str());
               }
            }
         } else {
            ErrorPrintf("no local variable instance for %s while emitting changes\n",
                        var_def->_VarName.c_str());
         }
         i++;
      }
   }
}

void cLocalContext::PersistShadowDataset ()
{
   _ShadowManager->Save();
}

void cLocalContext::CheckShadowDataset ()
{
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      if (var_def != NULL) {
         STRING_T var_name = var_def->_VarName;
         cLocalVariable * variable = (cLocalVariable*)var_def->_Variable;
         if (variable != NULL) {
            UCHAR_T var_type = variable->VarType();
            if (var_type == SH_VAR_SET) {
               ULONG_T dims = variable->Dims();
               LONG_T i1 = -1;
               LONG_T i2 = -1;
               LONG_T i3 = -1;
               LONG_T i4 = -1;
               if (dims == 0) {
                  variable->CheckShadowDataset(i1, i2, i3, i4);
               } else if (dims == 1) {
                  ULONG_T dim_size1 = variable->DimSize(0);
                  for (i1=0; i1<dim_size1; i1++) {
                     variable->CheckShadowDataset(i1, i2, i3, i4);
                  }
               } else if (dims == 2) {
                  ULONG_T dim_size1 = variable->DimSize(0);
                  ULONG_T dim_size2 = variable->DimSize(1);
                  for (i1=0; i1<dim_size1; i1++) {
                     for (i2=0; i2<dim_size2; i2++) {
                        variable->CheckShadowDataset(i1, i2, i3, i4);
                     }
                  }
               } else if (dims == 3) {
                  ULONG_T dim_size1 = variable->DimSize(0);
                  ULONG_T dim_size2 = variable->DimSize(1);
                  ULONG_T dim_size3 = variable->DimSize(2);
                  for (i1=0; i1<dim_size1; i1++) {
                     for (i2=0; i2<dim_size2; i2++) {
                        for (i3=0; i3<dim_size3; i3++) {
                           variable->CheckShadowDataset(i1, i2, i3, i4);
                        }
                     }
                  }
               } else if (dims == 4) {
                  ULONG_T dim_size1 = variable->DimSize(0);
                  ULONG_T dim_size2 = variable->DimSize(1);
                  ULONG_T dim_size3 = variable->DimSize(2);
                  ULONG_T dim_size4 = variable->DimSize(3);
                  for (i1=0; i1<dim_size1; i1++) {
                     for (i2=0; i2<dim_size2; i2++) {
                        for (i3=0; i3<dim_size3; i3++) {
                           for (i4=0; i4<dim_size4; i4++) {
                              variable->CheckShadowDataset(i1, i2, i3, i4);
                           }
                        }
                     }
                  }
               }

            }
         }
         i++;
      }
   }
}

void cLocalContext::ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async)
{
   cProgram * program = Program(program_name);
   if (program != NULL) {
      program->ExecuteJob(job, async);
   } else {
      throw cError(CELL_UNKNOWN_PROGRAM, 0, program_name);
   }
}


// Additional Declarations
  //## begin cLocalContext%3EDDCAEC005D.declarations preserve=yes
  //## end cLocalContext%3EDDCAEC005D.declarations

//## begin module%3EDDCAEC005D.epilog preserve=yes
//## end module%3EDDCAEC005D.epilog
