//## begin module%3C46E64A0182.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C46E64A0182.cm

//## begin module%3C46E64A0182.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C46E64A0182.cp

//## Module: cSHProcess%3C46E64A0182; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cSHProcess.h

#ifndef cSHProcess_h
#define cSHProcess_h 1

//## begin module%3C46E64A0182.includes preserve=yes
//## end module%3C46E64A0182.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cIniFile;
class __DLL_EXPORT__ cShutDownControl;
class __DLL_EXPORT__ cRequestHandler;
class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cProxy;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cProxyRequester;
class __DLL_EXPORT__ cProxySender;
class __DLL_EXPORT__ cProxyReceiver;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cSystemUtils;
class __DLL_EXPORT__ cCOSChannel;
class __DLL_EXPORT__ cLocalChannel;
class __DLL_EXPORT__ cChannel;
class __DLL_EXPORT__ cLocalContext;
class __DLL_EXPORT__ cCorbaCellProxy;
class __DLL_EXPORT__ cRemoteContext;
class __DLL_EXPORT__ cClients;

//## begin module%3C46E64A0182.additionalDeclarations preserve=yes

typedef std::list<STRING_T> SERVICE_LIST_T;
typedef std::map<STRING_T,cChannel*> CHANNEL_MAP_T;
typedef std::map<STRING_T,cContext*> CONTEXT_MAP_T;
typedef std::map<STRING_T,cProxySender*> PROXY_SENDER_MAP_T;
typedef std::map<STRING_T,cProxyReceiver*> PROXY_RECEIVER_MAP_T;
typedef std::map<STRING_T,cProxyRequester*> PROXY_REQUESTER_MAP_T;
typedef std::map<STRING_T,cChannel*> CHANNEL_MAP_T;

/// context filter constants
#define LOCAL_CONTEXTS     0x00000001
#define REMOTE_CONTEXTS    0x00000002
#define ALL_CONTEXTS       (LOCAL_CONTEXTS|REMOTE_CONTEXTS)

//## end module%3C46E64A0182.additionalDeclarations


//## begin cSHProcess%3C46E64A0182.preface preserve=yes
//## end cSHProcess%3C46E64A0182.preface

//## Class: cSHProcess%3C46E64A0182
//	cSHProcess is the base classfor all Shacira processes. c
//	SHProcess integrates functionality for CCS service
//	connections (server and client).
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C46ECAE02ED;cConfigurationObject { -> F}
//## Uses: <unnamed>%3C4D741D0040;cSystemUtils { -> F}
//## Uses: <unnamed>%3EDCB79E02CE;cContext { -> F}
//## Uses: <unnamed>%3EDCB914036B;cProxyReceiver { -> F}
//## Uses: <unnamed>%3EDCB92202FD;cProxySender { -> F}
//## Uses: <unnamed>%3EDE0E610157;cProxy { -> F}
//## Uses: <unnamed>%3EE05DAE01F4;cRemoteContext { -> F}
//## Uses: <unnamed>%3F867D2B003E;cCOSChannel { -> F}
//## Uses: <unnamed>%3F867EF902FD;cChannel { -> F}
//## Uses: <unnamed>%3FBF603B0222;cTransientObject { -> F}
//## Uses: <unnamed>%42DF5C1A02AF;cClients { -> F}
//## Uses: <unnamed>%42EF7890029F;cLocalContext { -> F}
//## Uses: <unnamed>%437A0F88006D;cFileSystemUtils { -> F}
//## Uses: <unnamed>%437A0FFC00EA;cIniFile { -> F}
//## Uses: <unnamed>%437A157902AF;cCorbaCellProxy { -> F}

class __DLL_EXPORT__ cSHProcess : public cControlThread  //## Inherits: <unnamed>%3C46E7AF0258
{
  //## begin cSHProcess%3C46E64A0182.initialDeclarations preserve=yes
public:
  //## end cSHProcess%3C46E64A0182.initialDeclarations

    //## Constructors (generated)
      cSHProcess();

      cSHProcess(const cSHProcess &right);

    //## Constructors (specified)
      //## Operation: cSHProcess%1011276236
      cSHProcess (cConfigurationObject *config_obj, BOOL_T is_client = true);

    //## Destructor (generated)
      virtual ~cSHProcess();


    //## Other Operations (specified)
      //## Operation: Start%1123228418
      virtual void Start ();

      //## Operation: Stop%1123228419
      virtual void Stop ();

      //## Operation: MainFunc%1037122841
      virtual INT_T MainFunc (void *extra);

      //## Operation: AddChannel%1065778445
      //	Adds a channel to the shacira process.
      //	Added channels can be queried and connected with.
      void AddChannel (CONST_STRING_T name, cChannel *channel, BOOL_T remote = false);

      //## Operation: Channel%1065778446
      //	Queries a channel from the process using channel name as
      //	identification.
      cChannel * Channel (CONST_STRING_T name);

      //## Operation: AddContext%1054828772
      //	Adds a context to the process.
      //	Added contexts can be queried and connected with.
      void AddContext (CONST_STRING_T name, cContext *context);

      //## Operation: Context%1054632818
      //	Queries a context from the process using context name as
      //	identification.
      cContext * Context (CONST_STRING_T name, ULONG_T filter);

      //## Operation: AddService%1054897237
      //	Adds a service to the process.
      void AddService (CONST_STRING_T service);

      //## Operation: NewProxy%1054890582
      //	Handles a newly arived proxy.
      void NewProxy (cProxy *proxy);

      //## Operation: ContextNames%1075059041
      void ContextNames (STRING_LIST_T &context_names, ULONG_T filter);

      //## Operation: Proxy%1097408539
      //	Queries a proxy object using proxy name as
      //	identification.
      cProxy * Proxy (CONST_STRING_T name);

      //## Operation: Send%1122555426
      virtual void Send (cTransientObject *object);

      //## Operation: EventChannel%1122619257
      cChannel * EventChannel ();

      //## Operation: AddProxyReceiver%1125297032
      //	Adds a proxy receiver to the process.
      void AddProxyReceiver (CONST_STRING_T receiver_name, cProxyReceiver *receiver);

      //## Operation: AddProxyReceiver%1134383666
      //	Adds a proxy receiver on port to the process.
      void AddProxyReceiver (USHORT_T port);

      //## Operation: AddProxySender%1125297033
      //	Adds a proxy sender to the process.
      void AddProxySender (CONST_STRING_T sender_name, cProxySender *sender);

      //## Operation: AddProxySender%1134383667
      //	Adds a proxy sender for ip-address addr on port port to
      //	the process.
      void AddProxySender (CONST_STRING_T addr, USHORT_T port);

      //## Operation: AddProxyRequest%1134387057
      //	Adds a proxy request address to the process.
      void AddProxyRequest (CONST_STRING_T addr);

      //## Operation: AddProxyRequest%1134387058
      //	Adds a proxy request port to the process.
      void AddProxyRequest (USHORT_T port);

      //## Operation: AddRequestedPort%1134387059
      //	Adds a requested  port to the process.
      void AddRequestedPort (USHORT_T port);

      //## Operation: ReceiverExists%1134385872
      BOOL_T ReceiverExists (CONST_STRING_T name);

      //## Operation: SenderExists%1134385873
      BOOL_T SenderExists (CONST_STRING_T name);

      //## Operation: OnCycle%1125301339
      virtual void OnCycle ();

      //## Operation: RegisterHandler%1125391948
      virtual void RegisterHandler (cRequestHandler *handler);

      //## Operation: RemoveHandler%1125391949
      virtual void RemoveHandler (cRequestHandler *handler);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ProcessId%3C4D442B03C6
      ULONG_T get_ProcessId () const;

      //## Attribute: Computer%3C4D739601E0
      STRING_T get_Computer () const;

      //## Attribute: Path%3C4D4453002A
      STRING_T get_Path () const;
      void set_Path (STRING_T value);

      //## Attribute: IFType%438AD8F301BD
      LONG_T get_IFType () const;

    // Data Members for Class Attributes

      //## Attribute: SenderMutex%438338900361
      //## begin cSHProcess::SenderMutex%438338900361.attr preserve=no  protected: cMutexSem {U} 
      cMutexSem _SenderMutex;
      //## end cSHProcess::SenderMutex%438338900361.attr

      //## Attribute: ReceiverMutex%4383389E02D4
      //## begin cSHProcess::ReceiverMutex%4383389E02D4.attr preserve=no  protected: cMutexSem {U} 
      cMutexSem _ReceiverMutex;
      //## end cSHProcess::ReceiverMutex%4383389E02D4.attr

      cMutexSem _ServiceMutex;

  public:
    // Additional Public Declarations
      //## begin cSHProcess%3C46E64A0182.public preserve=yes
      static STRING_T CorbaLocIOR(const STRING_T & host_name);
      bool TranslateAdresses(CONST_STRING_T new_address, STRING_T & service);
      //## end cSHProcess%3C46E64A0182.public

  protected:
    // Data Members for Class Attributes

      //## begin cSHProcess::ProcessId%3C4D442B03C6.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ProcessId;
      //## end cSHProcess::ProcessId%3C4D442B03C6.attr

      //## begin cSHProcess::Computer%3C4D739601E0.attr preserve=no  public: STRING_T {U} 
      STRING_T _Computer;
      //## end cSHProcess::Computer%3C4D739601E0.attr

      //## begin cSHProcess::Path%3C4D4453002A.attr preserve=no  public: STRING_T {U} 
      STRING_T _Path;
      //## end cSHProcess::Path%3C4D4453002A.attr

      //## begin cSHProcess::IFType%438AD8F301BD.attr preserve=no  public: LONG_T {U} IF_PROPRIETARY
      LONG_T _IFType;
      //## end cSHProcess::IFType%438AD8F301BD.attr

      //## Attribute: LocalContexts%3EDCB59102BF
      //## begin cSHProcess::LocalContexts%3EDCB59102BF.attr preserve=no  protected: CONTEXT_MAP_T {U} 
      CONTEXT_MAP_T _LocalContexts;
      //## end cSHProcess::LocalContexts%3EDCB59102BF.attr

      //## Attribute: RemoteContexts%3EDF7576002E
      //## begin cSHProcess::RemoteContexts%3EDF7576002E.attr preserve=no  protected: CONTEXT_MAP_T {U} 
      CONTEXT_MAP_T _RemoteContexts;
      //## end cSHProcess::RemoteContexts%3EDF7576002E.attr

      //## Attribute: IsClient%437B810602E7
      //## begin cSHProcess::IsClient%437B810602E7.attr preserve=no  protected: BOOL_T {U} true
      BOOL_T _IsClient;
public:
      BOOL_T get_IsClient () const {return _IsClient;};
protected:
      //## end cSHProcess::IsClient%437B810602E7.attr

    // Data Members for Associations

      //## Association: System::<unnamed>%3C69007200BA
      //## Role: cSHProcess::ShutDownControl%3C69007203BD
      //## begin cSHProcess::ShutDownControl%3C69007203BD.role preserve=no  public: cShutDownControl { -> 0..1RFHN}
      cShutDownControl *_ShutDownControl;
      //## end cSHProcess::ShutDownControl%3C69007203BD.role

      //## Association: System::Process::<unnamed>%42E8DFB20290
      //## Role: cSHProcess::EventChannel%42E8DFB30167
      //## begin cSHProcess::EventChannel%42E8DFB30167.role preserve=no  public: cLocalChannel { -> 1RFHN}
      cLocalChannel *_EventChannel;
      //## end cSHProcess::EventChannel%42E8DFB30167.role

      //## Association: System::Process::<unnamed>%43141D3E0004
      //## Role: cSHProcess::HandlerMap%43141D3F00FE
      //## Qualifier: name%43141D75036E; STRING_T
      //## begin cSHProcess::HandlerMap%43141D3F00FE.role preserve=no  public: cRequestHandler {1 -> 0..nRFHN}
      std::map<STRING_T, cRequestHandler*> _HandlerMap;
      //## end cSHProcess::HandlerMap%43141D3F00FE.role

      //## Association: System::Process::<unnamed>%439D694C01D3
      //## Role: cSHProcess::ProxyRequester%439D694D0230
      //## begin cSHProcess::ProxyRequester%439D694D0230.role preserve=no  public: cProxyRequester {1 -> 0..1RFHN}
      cProxyRequester *_ProxyRequester;
      //## end cSHProcess::ProxyRequester%439D694D0230.role

    // Additional Protected Declarations
      //## begin cSHProcess%3C46E64A0182.protected preserve=yes
      //## end cSHProcess%3C46E64A0182.protected

  private:
    // Additional Private Declarations
      //## begin cSHProcess%3C46E64A0182.private preserve=yes
      //## end cSHProcess%3C46E64A0182.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Pulse%1011276239
      void Pulse ();

      //## Operation: StartReceiving%1065795129
      void StartReceiving ();

      //## Operation: StopReceiving%1065795130
      void StopReceiving ();

      //## Operation: ReadIORFile%1132072708
      void ReadIORFile ();

      //## Operation: RequestProxies%1132208636
      void RequestProxies ();

    // Data Members for Class Attributes

      //## Attribute: Services%3EDCB3AB037A
      //## begin cSHProcess::Services%3EDCB3AB037A.attr preserve=no  implementation: SERVICE_LIST_T {U} 
      SERVICE_LIST_T _Services;
      //## end cSHProcess::Services%3EDCB3AB037A.attr

      //## Attribute: ProxyReceiverMap%3EDCB3AB038A
      //## begin cSHProcess::ProxyReceiverMap%3EDCB3AB038A.attr preserve=no  implementation: PROXY_RECEIVER_MAP_T {U} 
      PROXY_RECEIVER_MAP_T _ProxyReceiverMap;
      //## end cSHProcess::ProxyReceiverMap%3EDCB3AB038A.attr

      //## Attribute: ProxySenderMap%3EDCB3AB037B
      //## begin cSHProcess::ProxySenderMap%3EDCB3AB037B.attr preserve=no  implementation: PROXY_SENDER_MAP_T {U} 
      PROXY_SENDER_MAP_T _ProxySenderMap;
      //## end cSHProcess::ProxySenderMap%3EDCB3AB037B.attr

      //## Attribute: LocalChannels%3F86C15602DE
      //## begin cSHProcess::LocalChannels%3F86C15602DE.attr preserve=no  implementation: CHANNEL_MAP_T {U} 
      CHANNEL_MAP_T _LocalChannels;
      //## end cSHProcess::LocalChannels%3F86C15602DE.attr

      //## Attribute: RemoteChannels%3F867ECB0203
      //## begin cSHProcess::RemoteChannels%3F867ECB0203.attr preserve=no  implementation: CHANNEL_MAP_T {U} 
      CHANNEL_MAP_T _RemoteChannels;
      //## end cSHProcess::RemoteChannels%3F867ECB0203.attr

      //## Attribute: IORDirectory%437A0EC2003E
      //## begin cSHProcess::IORDirectory%437A0EC2003E.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _IORDirectory;
      //## end cSHProcess::IORDirectory%437A0EC2003E.attr

      //## Attribute: IORFile%437A0EC2005E
      //## begin cSHProcess::IORFile%437A0EC2005E.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _IORFile;
      //## end cSHProcess::IORFile%437A0EC2005E.attr

    // Additional Implementation Declarations
      //## begin cSHProcess%3C46E64A0182.implementation preserve=yes
      STRING_T _TranslatedIpAddress;
      //## end cSHProcess%3C46E64A0182.implementation

};

//## begin cSHProcess%3C46E64A0182.postscript preserve=yes
//## end cSHProcess%3C46E64A0182.postscript

// Class cSHProcess 

//## begin module%3C46E64A0182.epilog preserve=yes
//## end module%3C46E64A0182.epilog


#endif
