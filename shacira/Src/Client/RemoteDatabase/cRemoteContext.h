//## begin module%3EDDCC7F0167.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EDDCC7F0167.cm

//## begin module%3EDDCC7F0167.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EDDCC7F0167.cp

//## Module: cRemoteContext%3EDDCC7F0167; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Client\RemoteDatabase\cRemoteContext.h

#ifndef cRemoteContext_h
#define cRemoteContext_h 1

//## begin module%3EDDCC7F0167.includes preserve=yes
//## end module%3EDDCC7F0167.includes

// cContext
#include "System/Database/cContext.h"

class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cCellProxy;
class __DLL_EXPORT__ cProxy;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cInternalBridge;
class __DLL_EXPORT__ cRemoteBridge;
class __DLL_EXPORT__ cRemoteVar;
class __DLL_EXPORT__ cStyxParser;

//## begin module%3EDDCC7F0167.additionalDeclarations preserve=yes
//## end module%3EDDCC7F0167.additionalDeclarations


//## begin cRemoteContext%3EDDCC7F0167.preface preserve=yes
//## end cRemoteContext%3EDDCC7F0167.preface

//## Class: cRemoteContext%3EDDCC7F0167
//## Category: Client::RemoteDatabase%3DFF22EE0346
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3EDDCCC9029F;cRemoteVar { -> F}
//## Uses: <unnamed>%3EDDCCE20177;cVarDef { -> F}
//## Uses: <unnamed>%3EDE18FD031C;cProxy { -> F}
//## Uses: <unnamed>%3EE063BE032C;cSHProcess { -> F}
//## Uses: <unnamed>%3FF9474601C5;cRemoteBridge { -> F}
//## Uses: <unnamed>%4117D0DD029F;cStyxParser { -> F}
//## Uses: <unnamed>%42DE0C4502FD;cInternalBridge { -> F}

class __DLL_EXPORT__ cRemoteContext : public cContext  //## Inherits: <unnamed>%3EDDCC91038A
{
  //## begin cRemoteContext%3EDDCC7F0167.initialDeclarations preserve=yes
public:
  //## end cRemoteContext%3EDDCC7F0167.initialDeclarations

    //## Constructors (generated)
      cRemoteContext();

      cRemoteContext(const cRemoteContext &right);

    //## Constructors (specified)
      //## Operation: cRemoteContext%1054715296
      cRemoteContext (cSHProcess *process, cCellProxy *proxy);

    //## Destructor (generated)
      virtual ~cRemoteContext();


    //## Other Operations (specified)
      //## Operation: IsRemote%1054715293
      //	Is this Context a remote context ?
      virtual BOOL_T IsRemote ();

      //## Operation: Connect%1054715294
      virtual void Connect (ULONG_T if_type);

      //## Operation: Create%1054715295
      //	Creates necessary resources.
      virtual void Create ();

      //## Operation: CreateDynamic%1090073691
      virtual void CreateDynamic ();

      //## Operation: GetVarDefs%1054726259
      //	Gets all variable definitions as a list of serialized
      //	objects.
      ULONG_T GetVarDefs (STRING_T &var_defs, ULONG_T if_type = 0);

      //## Operation: LocalChannel%1086771868
      virtual cChannel * LocalChannel ();

      //## Operation: EventChannel%1073299992
      virtual cChannel * EventChannel ();

      //## Operation: Alarms%1089103363
      virtual ULONG_T Alarms (ULONG_T selection);

      //## Operation: Alarms%1081425831
      virtual ULONG_T Alarms (ULONG_T selection, ALARM_MAP_T &alarms);

      //## Operation: ClearAlarm%1081425832
      virtual void ClearAlarm (ULONG_T ident, BOOL_T propagate = true);

      //## Operation: ClearAlarms%1081425833
      virtual void ClearAlarms (BOOL_T propagate = true);

      //## Operation: GetDeviceValue%1082991643
      //	Retrieves a value of a variable directly from a device.
      virtual void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value);

      //## Operation: SetDeviceValue%1082991644
      virtual void SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value);

      //## Operation: ExecuteCommand%1089292614
      //	Executes a command on a program owned by the context.
      //	The program is denoted by program name.
      virtual void ExecuteCommand (CONST_STRING_T program_name, ULONG_T command);

      //## Operation: ExecuteRequest%1133771769
      //	Executes a request on a program owned by the context.
      //	The program is denoted by program name.
      virtual void ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request);

      //## Operation: ReadFile%1091699607
      virtual void ReadFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, STRING_T &buf);

      //## Operation: WriteFile%1091699608
      virtual void WriteFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, CONST_STRING_T buf);

      //## Operation: Update%1077626054
      void Update (ULONG_T process_id);

      //## Operation: SetJob%1093930663
      virtual void SetJob (cJobSpec *job_spec);

      //## Operation: GetJobSpec%1093930664
      virtual cJobSpec * GetJobSpec (CONST_STRING_T job_name);

      //## Operation: Send%1125073057
      virtual void Send (cTransientObject *object);

      //## Operation: IsConnected%1134148706
      virtual BOOL_T IsConnected ();

      //## Operation: Ping%1134227772
      virtual BOOL_T Ping ();

      //## Operation: IsLocal%1141892789
      virtual BOOL_T IsLocal ();

      //## Operation: Synchronize%1228401754
      virtual BOOL_T Synchronize ();

      //## Operation: Synchronized%1228414413
      virtual BOOL_T Synchronized ();

      //## Operation: Proxy%1228414414
      virtual cCellProxy * Proxy ();

      //## Operation: ExecuteJob%1244547095
      //	Executes a job on a program owned by the context. The
      //	program is denoted by program name.
      virtual void ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async = false);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ClientId%42DE0E9502DE
      ULONG_T get_ClientId () const;

      //## Attribute: UserName%42DF90BA02FD
      STRING_T get_UserName () const;
      void set_UserName (STRING_T value);

      //## Attribute: Password%42DF90E00213
      STRING_T get_Password () const;
      void set_Password (STRING_T value);

    // Data Members for Associations

      //## Association: Client::RemoteDatabase::<unnamed>%3EDDCE61036B
      //## Role: cRemoteContext::CellProxy%3EDDCE620232
      //## begin cRemoteContext::CellProxy%3EDDCE620232.role preserve=no  public: cCellProxy { -> 1RFHN}
  private:
      cCellProxy *_CellProxy;
  public:
      cCellProxy * GetCellProxy() const;
      void SetCellProxy(cCellProxy * cell_proxy);
      //## end cRemoteContext::CellProxy%3EDDCE620232.role

  public:
    // Additional Public Declarations
      //## begin cRemoteContext%3EDDCC7F0167.public preserve=yes
      cCellProxy * CellProxy() const {return _CellProxy;};
      //## end cRemoteContext%3EDDCC7F0167.public

  protected:
    // Data Members for Class Attributes

      //## begin cRemoteContext::ClientId%42DE0E9502DE.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ClientId;
      //## end cRemoteContext::ClientId%42DE0E9502DE.attr

      //## begin cRemoteContext::UserName%42DF90BA02FD.attr preserve=no  public: STRING_T {U} 
      STRING_T _UserName;
      //## end cRemoteContext::UserName%42DF90BA02FD.attr

      //## begin cRemoteContext::Password%42DF90E00213.attr preserve=no  public: STRING_T {U} 
      STRING_T _Password;
      //## end cRemoteContext::Password%42DF90E00213.attr

    // Additional Protected Declarations
      //## begin cRemoteContext%3EDDCC7F0167.protected preserve=yes
      //## end cRemoteContext%3EDDCC7F0167.protected

  private:
    // Additional Private Declarations
      //## begin cRemoteContext%3EDDCC7F0167.private preserve=yes
      //## end cRemoteContext%3EDDCC7F0167.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: RemoveVarDefs%1092122758
      void RemoveVarDefs ();

    // Data Members for Class Attributes

      //## Attribute: EventChannelName%3EE5BB240213
      //## begin cRemoteContext::EventChannelName%3EE5BB240213.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _EventChannelName;
      //## end cRemoteContext::EventChannelName%3EE5BB240213.attr

      //## Attribute: DataChannelName%3EE5BB3D0232
      //## begin cRemoteContext::DataChannelName%3EE5BB3D0232.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _DataChannelName;
      //## end cRemoteContext::DataChannelName%3EE5BB3D0232.attr

    // Additional Implementation Declarations
      //## begin cRemoteContext%3EDDCC7F0167.implementation preserve=yes
      //## end cRemoteContext%3EDDCC7F0167.implementation

};

//## begin cRemoteContext%3EDDCC7F0167.postscript preserve=yes
//## end cRemoteContext%3EDDCC7F0167.postscript

// Class cRemoteContext 

//## begin module%3EDDCC7F0167.epilog preserve=yes
//## end module%3EDDCC7F0167.epilog


#endif
