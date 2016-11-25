//## begin module%437B8D91006B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%437B8D91006B.cm

//## begin module%437B8D91006B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%437B8D91006B.cp

//## Module: cProxyRequester%437B8D91006B; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Comm\cProxyRequester.h

#ifndef cProxyRequester_h
#define cProxyRequester_h 1

//## begin module%437B8D91006B.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%437B8D91006B.includes

// cMemoryPtr
#include "System/Memory/cMemoryPtr.h"
// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cProxySender;
class __DLL_EXPORT__ cClients;

//## begin module%437B8D91006B.additionalDeclarations preserve=yes

typedef std::map<USHORT_T,USHORT_T> PORT_MAP_T;
typedef std::map<USHORT_T,SOCKET> SOCKET_MAP_T;
typedef std::map<STRING_T,STRING_T> ADDRESS_MAP_T;

//## end module%437B8D91006B.additionalDeclarations


//## begin cProxyRequester%437B8D91006B.preface preserve=yes
//## end cProxyRequester%437B8D91006B.preface

//## Class: cProxyRequester%437B8D91006B
//## Category: System::Comm%3A8CE33700FD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%437B9694004B;cMemoryPtr { -> }
//## Uses: <unnamed>%437B9B490397;cProxySender { -> F}
//## Uses: <unnamed>%441C2D990228;cClients { -> F}

class __DLL_EXPORT__ cProxyRequester : public cControlThread  //## Inherits: <unnamed>%437B8E8E0349
{
  //## begin cProxyRequester%437B8D91006B.initialDeclarations preserve=yes
public:
  //## end cProxyRequester%437B8D91006B.initialDeclarations

    //## Constructors (generated)
      cProxyRequester();

      cProxyRequester(const cProxyRequester &right);

    //## Constructors (specified)
      //## Operation: cProxyRequester%1132170917
      cProxyRequester (cSHProcess *process, BOOL_T is_client);

    //## Destructor (generated)
      virtual ~cProxyRequester();


    //## Other Operations (specified)
      //## Operation: AddPort%1132170918
      void AddPort (USHORT_T port);

      //## Operation: AddRequestedPort%1132208637
      void AddRequestedPort (USHORT_T port);

      //## Operation: AddAddress%1132208638
      void AddAddress (CONST_STRING_T address);

      //## Operation: RequestProxy%1132208368
      void RequestProxy (CONST_STRING_T server_addr, USHORT_T requested_port);

      //## Operation: RequestProxy%1132208635
      void RequestProxy (CONST_STRING_T server_addr, USHORT_T server_port, USHORT_T requested_port);

      //## Operation: MainFunc%1132170919
      virtual INT_T MainFunc (void *extra);

  public:
    // Additional Public Declarations
      //## begin cProxyRequester%437B8D91006B.public preserve=yes
      //## end cProxyRequester%437B8D91006B.public

  protected:
    // Data Members for Associations

      //## Association: System::Process::<unnamed>%439D694C01D3
      //## Role: cProxyRequester::Process%439D694D0231
      //## begin cProxyRequester::Process%439D694D0231.role preserve=no  public: cSHProcess {0..1 -> 1RFHN}
      cSHProcess *_Process;
      //## end cProxyRequester::Process%439D694D0231.role

    // Additional Protected Declarations
      //## begin cProxyRequester%437B8D91006B.protected preserve=yes
      //## end cProxyRequester%437B8D91006B.protected

  private:
    // Additional Private Declarations
      //## begin cProxyRequester%437B8D91006B.private preserve=yes
      //## end cProxyRequester%437B8D91006B.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: HandleRequests%1132170921
      void HandleRequests ();

      //## Operation: HandlePort%1132170925
      void HandlePort (USHORT_T port, ULONG_T timeout);

      //## Operation: Socket%1132170924
      SOCKET Socket (USHORT_T port);

      //## Operation: SetSocket%1132170922
      void SetSocket (USHORT_T port);

      //## Operation: CloseSockets%1132170923
      void CloseSockets ();

      //## Operation: ReceiveFromPort%1132170926
      int ReceiveFromPort (USHORT_T port, CONST_STRING_T buf, ULONG_T buf_size, ULONG_T timeout, STRING_T &sender_addr);

      //## Operation: RequestProxies%1132208639
      void RequestProxies ();

    // Data Members for Class Attributes

      //## Attribute: RequesterPortMap%437B8E1C0107
      //## begin cProxyRequester::RequesterPortMap%437B8E1C0107.attr preserve=no  implementation: PORT_MAP_T {U} 
      PORT_MAP_T _RequesterPortMap;
      //## end cProxyRequester::RequesterPortMap%437B8E1C0107.attr

      //## Attribute: RequestedPortMap%437C306D005D
      //## begin cProxyRequester::RequestedPortMap%437C306D005D.attr preserve=no  implementation: PORT_MAP_T {U} 
      PORT_MAP_T _RequestedPortMap;
      //## end cProxyRequester::RequestedPortMap%437C306D005D.attr

      //## Attribute: AddressMap%437C308102ED
      //## begin cProxyRequester::AddressMap%437C308102ED.attr preserve=no  implementation: ADDRESS_MAP_T {U} 
      ADDRESS_MAP_T _AddressMap;
      //## end cProxyRequester::AddressMap%437C308102ED.attr

      //## Attribute: SocketMap%437B924C01D2
      //## begin cProxyRequester::SocketMap%437B924C01D2.attr preserve=no  implementation: SOCKET_MAP_T {U} 
      SOCKET_MAP_T _SocketMap;
      //## end cProxyRequester::SocketMap%437B924C01D2.attr

      //## Attribute: InBuf%437B965A00A9
      //## begin cProxyRequester::InBuf%437B965A00A9.attr preserve=no  implementation: cMemoryPtr {U} 
      cMemoryPtr _InBuf;
      //## end cProxyRequester::InBuf%437B965A00A9.attr

      //## Attribute: IsClient%437C298F0199
      //## begin cProxyRequester::IsClient%437C298F0199.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _IsClient;
      //## end cProxyRequester::IsClient%437C298F0199.attr

    // Additional Implementation Declarations
      //## begin cProxyRequester%437B8D91006B.implementation preserve=yes
      //## end cProxyRequester%437B8D91006B.implementation

};

//## begin cProxyRequester%437B8D91006B.postscript preserve=yes
//## end cProxyRequester%437B8D91006B.postscript

// Class cProxyRequester 

//## begin module%437B8D91006B.epilog preserve=yes
//## end module%437B8D91006B.epilog


#endif
