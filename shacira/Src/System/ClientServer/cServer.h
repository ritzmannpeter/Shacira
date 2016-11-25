//## begin module%4295992400CA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4295992400CA.cm

//## begin module%4295992400CA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4295992400CA.cp

//## Module: cServer%4295992400CA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cServer.h

#ifndef cServer_h
#define cServer_h 1

//## begin module%4295992400CA.includes preserve=yes
//## end module%4295992400CA.includes

// eb_thread
#include "base/eb_thread.hpp"
// cTCPComm
#include "System/ClientServer/cTCPComm.h"

class __DLL_EXPORT__ cServerThread;

//## begin module%4295992400CA.additionalDeclarations preserve=yes
//## end module%4295992400CA.additionalDeclarations


//## begin cServer%4295992400CA.preface preserve=yes
//## end cServer%4295992400CA.preface

//## Class: cServer%4295992400CA
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4296F1A300FA;cServerThread { -> F}
//## Uses: <unnamed>%429AC11A02BF;cTCPComm { -> }

class __DLL_EXPORT__ cServer : public cThread  //## Inherits: <unnamed>%42959FC00113
{
  //## begin cServer%4295992400CA.initialDeclarations preserve=yes
public:
  //## end cServer%4295992400CA.initialDeclarations

    //## Constructors (generated)
      cServer();

      cServer(const cServer &right);

    //## Constructors (specified)
      //## Operation: cServer%1117174977
      cServer (USHORT_T listener_port);

    //## Destructor (generated)
      virtual ~cServer();


    //## Other Operations (specified)
      //## Operation: onMain%1117174978
      virtual INT_T onMain (void *extra);

      //## Operation: Request%1117174979
      virtual void Request (cStreamMsg &in_msg, cStreamMsg &out_msg);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ListenerPort%42959BDE0313
      USHORT_T get_ListenerPort () const;
      void set_ListenerPort (USHORT_T value);

      //## Attribute: MaxConnections%4296F0AC01C5
      ULONG_T get_MaxConnections () const;
      void set_MaxConnections (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cServer%4295992400CA.public preserve=yes
      //## end cServer%4295992400CA.public

  protected:
    // Data Members for Class Attributes

      //## begin cServer::ListenerPort%42959BDE0313.attr preserve=no  public: USHORT_T {U} 0
      USHORT_T _ListenerPort;
      //## end cServer::ListenerPort%42959BDE0313.attr

      //## begin cServer::MaxConnections%4296F0AC01C5.attr preserve=no  public: ULONG_T {U} 5
      ULONG_T _MaxConnections;
      //## end cServer::MaxConnections%4296F0AC01C5.attr

    // Additional Protected Declarations
      //## begin cServer%4295992400CA.protected preserve=yes
      //## end cServer%4295992400CA.protected

  private:
    // Additional Private Declarations
      //## begin cServer%4295992400CA.private preserve=yes
      //## end cServer%4295992400CA.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Initialize%1117174993
      void Initialize ();

    // Data Members for Class Attributes

      //## Attribute: Socket%4296F02600BB
      //## begin cServer::Socket%4296F02600BB.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _Socket;
      //## end cServer::Socket%4296F02600BB.attr

    // Additional Implementation Declarations
      //## begin cServer%4295992400CA.implementation preserve=yes
      //## end cServer%4295992400CA.implementation

};

//## begin cServer%4295992400CA.postscript preserve=yes
//## end cServer%4295992400CA.postscript

// Class cServer 

//## begin module%4295992400CA.epilog preserve=yes
//## end module%4295992400CA.epilog


#endif
