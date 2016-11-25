//## begin module%3C552714024C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C552714024C.cm

//## begin module%3C552714024C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C552714024C.cp

//## Module: cProxyReceiver%3C552714024C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxyReceiver.h

#ifndef cProxyReceiver_h
#define cProxyReceiver_h 1

//## begin module%3C552714024C.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%3C552714024C.includes

// cMemoryPtr
#include "System/Memory/cMemoryPtr.h"
// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cCellProxy;
class __DLL_EXPORT__ cProxy;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cProxyTable;
class __DLL_EXPORT__ cConvUtils;
class __DLL_EXPORT__ cChannelProxy;
class __DLL_EXPORT__ cCosEventChannelProxy;
class __DLL_EXPORT__ cCorbaCellProxy;

//## begin module%3C552714024C.additionalDeclarations preserve=yes

typedef std::map<STRING_T, STRING_T> IOR_MAP_T;

//## end module%3C552714024C.additionalDeclarations


//## begin cProxyReceiver%3C552714024C.preface preserve=yes
//## end cProxyReceiver%3C552714024C.preface

//## Class: cProxyReceiver%3C552714024C
//## Category: System::Comm%3A8CE33700FD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C5698A603B4;cProxy { -> F}
//## Uses: <unnamed>%3C5698C70040;cChannelProxy { -> F}
//## Uses: <unnamed>%3DCABCDA01EC;cCellProxy { -> F}
//## Uses: <unnamed>%3DCBA65D02F8;cCorbaCellProxy { -> F}
//## Uses: <unnamed>%3DCBA666028D;cCosEventChannelProxy { -> F}
//## Uses: <unnamed>%3DDA314E0375;cConvUtils { -> F}
//## Uses: <unnamed>%3EDB20C3029F;cConfigurationObject { -> F}
//## Uses: <unnamed>%3EDB21D10213;cMemoryPtr { -> }
//## Uses: <unnamed>%43F45E85015E;cProxyTable { -> F}

class __DLL_EXPORT__ cProxyReceiver : public cControlThread  //## Inherits: <unnamed>%3EDB214603D8
{
  //## begin cProxyReceiver%3C552714024C.initialDeclarations preserve=yes
public:
  //## end cProxyReceiver%3C552714024C.initialDeclarations

    //## Constructors (generated)
      cProxyReceiver();

      cProxyReceiver(const cProxyReceiver &right);

    //## Constructors (specified)
      //## Operation: cProxyReceiver%1012207924
      cProxyReceiver (cSHProcess *process, ULONG_T port);

      //## Operation: cProxyReceiver%1012207925
      cProxyReceiver (cConfigurationObject *config_obj, cSHProcess *process = NULL);

    //## Destructor (generated)
      virtual ~cProxyReceiver();


    //## Other Operations (specified)
      //## Operation: Proxy%1012295717
      cProxy * Proxy (CONST_STRING_T name);

      //## Operation: CellProxy%1012295719
      cCellProxy * CellProxy (CONST_STRING_T name);

      //## Operation: ChannelProxy%1012295720
      cChannelProxy * ChannelProxy (CONST_STRING_T name);

      //## Operation: MainFunc%1012207938
      virtual INT_T MainFunc (void *extra);

      //## Operation: ReceiverName%1134385868
      static STRING_T ReceiverName (USHORT_T port);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Port%3EDB23D201B5
      ULONG_T get_Port () const;

  public:
    // Additional Public Declarations
      //## begin cProxyReceiver%3C552714024C.public preserve=yes
      //## end cProxyReceiver%3C552714024C.public

  protected:
    // Data Members for Class Attributes

      //## begin cProxyReceiver::Port%3EDB23D201B5.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Port;
      //## end cProxyReceiver::Port%3EDB23D201B5.attr

    // Data Members for Associations

      //## Association: System::Process::<unnamed>%3EE059DC002E
      //## Role: cProxyReceiver::Process%3EE059DC02DE
      //## begin cProxyReceiver::Process%3EE059DC02DE.role preserve=no  public: cSHProcess { -> 1RFHN}
      cSHProcess *_Process;
      //## end cProxyReceiver::Process%3EE059DC02DE.role

    // Additional Protected Declarations
      //## begin cProxyReceiver%3C552714024C.protected preserve=yes
      //## end cProxyReceiver%3C552714024C.protected

  private:
    // Additional Private Declarations
      //## begin cProxyReceiver%3C552714024C.private preserve=yes
      //## end cProxyReceiver%3C552714024C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Receive%1054547834
      ULONG_T Receive (CONST_STRING_T buf, ULONG_T buf_size, ULONG_T timeout);

      //## Operation: SetSockets%1054547835
      void SetSockets ();

      //## Operation: CloseSockets%1054547836
      void CloseSockets ();

      //## Operation: Exists%1133788614
      BOOL_T Exists (CONST_STRING_T ior);

      //## Operation: FlushInput%1134636719
      void FlushInput ();

    // Data Members for Class Attributes

      //## Attribute: InBuf%3EDB21E000EA
      //## begin cProxyReceiver::InBuf%3EDB21E000EA.attr preserve=no  implementation: cMemoryPtr {U} 
      cMemoryPtr _InBuf;
      //## end cProxyReceiver::InBuf%3EDB21E000EA.attr

      //## Attribute: Socket%3EDB26BE00AB
      //## begin cProxyReceiver::Socket%3EDB26BE00AB.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _Socket;
      //## end cProxyReceiver::Socket%3EDB26BE00AB.attr

      //## Attribute: IORMap%43943DA101E4
      //## begin cProxyReceiver::IORMap%43943DA101E4.attr preserve=no  implementation: IOR_MAP_T {U} 
      IOR_MAP_T _IORMap;
      //## end cProxyReceiver::IORMap%43943DA101E4.attr

      //## Attribute: ProxyTableMutex%43F463C20125
      //## begin cProxyReceiver::ProxyTableMutex%43F463C20125.attr preserve=no  implementation: static cMutexSem {U} 
      static cMutexSem _ProxyTableMutex;
      //## end cProxyReceiver::ProxyTableMutex%43F463C20125.attr

      //## Attribute: ProxyTable%43F45E970120
      //## begin cProxyReceiver::ProxyTable%43F45E970120.attr preserve=no  implementation: static cProxyTable * {U} NULL
      static cProxyTable *_ProxyTable;
      //## end cProxyReceiver::ProxyTable%43F45E970120.attr

      //## Attribute: ProxyTableRefCount%4CF3D7960124
      //## begin cProxyReceiver::ProxyTableRefCount%4CF3D7960124.attr preserve=no  implementation: static long {U} 0
      static long _ProxyTableRefCount;
      //## end cProxyReceiver::ProxyTableRefCount%4CF3D7960124.attr

    // Additional Implementation Declarations
      //## begin cProxyReceiver%3C552714024C.implementation preserve=yes
      //## end cProxyReceiver%3C552714024C.implementation

};

//## begin cProxyReceiver%3C552714024C.postscript preserve=yes
//## end cProxyReceiver%3C552714024C.postscript

// Class cProxyReceiver 

//## begin module%3C552714024C.epilog preserve=yes
//## end module%3C552714024C.epilog


#endif
