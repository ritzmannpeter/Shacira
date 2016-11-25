//## begin module%429C6E310167.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%429C6E310167.cm

//## begin module%429C6E310167.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%429C6E310167.cp

//## Module: cGatewayServer%429C6E310167; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cGatewayServer.h

#ifndef cGatewayServer_h
#define cGatewayServer_h 1

//## begin module%429C6E310167.includes preserve=yes
//## end module%429C6E310167.includes

// cServer
#include "System/ClientServer/cServer.h"

class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cGateway;

//## begin module%429C6E310167.additionalDeclarations preserve=yes
//## end module%429C6E310167.additionalDeclarations


//## begin cGatewayServer%429C6E310167.preface preserve=yes
//## end cGatewayServer%429C6E310167.preface

//## Class: cGatewayServer%429C6E310167
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%42E632E301A5;cContext { -> F}

class __DLL_EXPORT__ cGatewayServer : public cServer  //## Inherits: <unnamed>%429C6E7303A9
{
  //## begin cGatewayServer%429C6E310167.initialDeclarations preserve=yes
public:
  //## end cGatewayServer%429C6E310167.initialDeclarations

    //## Constructors (generated)
      cGatewayServer();

      cGatewayServer(const cGatewayServer &right);

    //## Constructors (specified)
      //## Operation: cGatewayServer%1117548694
      cGatewayServer (cGateway *gateway, USHORT_T listener_port, cSHProcess *process);

    //## Destructor (generated)
      virtual ~cGatewayServer();


    //## Other Operations (specified)
      //## Operation: Request%1117545272
      virtual void Request (cStreamMsg &in_msg, cStreamMsg &out_msg);

  public:
    // Additional Public Declarations
      //## begin cGatewayServer%429C6E310167.public preserve=yes
      //## end cGatewayServer%429C6E310167.public

  protected:
    // Data Members for Associations

      //## Association: Control::Cell::<unnamed>%429C71AE038A
      //## Role: cGatewayServer::Gateway%429C71AF02A0
      //## begin cGatewayServer::Gateway%429C71AF02A0.role preserve=no  public: cGateway {1 -> 1RFHN}
      cGateway *_Gateway;
      //## end cGatewayServer::Gateway%429C71AF02A0.role

      //## Association: Control::Cell::<unnamed>%429DB860038A
      //## Role: cGatewayServer::Process%429DB8610261
      //## begin cGatewayServer::Process%429DB8610261.role preserve=no  public: cSHProcess { -> 1RFHN}
      cSHProcess *_Process;
      //## end cGatewayServer::Process%429DB8610261.role

    // Additional Protected Declarations
      //## begin cGatewayServer%429C6E310167.protected preserve=yes
      //## end cGatewayServer%429C6E310167.protected

  private:
    // Additional Private Declarations
      //## begin cGatewayServer%429C6E310167.private preserve=yes
      //## end cGatewayServer%429C6E310167.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cGatewayServer%429C6E310167.implementation preserve=yes
      //## end cGatewayServer%429C6E310167.implementation

};

//## begin cGatewayServer%429C6E310167.postscript preserve=yes
//## end cGatewayServer%429C6E310167.postscript

// Class cGatewayServer 

//## begin module%429C6E310167.epilog preserve=yes
//## end module%429C6E310167.epilog


#endif
