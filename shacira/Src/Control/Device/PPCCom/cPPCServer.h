//## begin module%410898950261.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%410898950261.cm

//## begin module%410898950261.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%410898950261.cp

//## Module: cPPCServer%410898950261; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCServer.h

#ifndef cPPCServer_h
#define cPPCServer_h 1

//## begin module%410898950261.includes preserve=yes
//## end module%410898950261.includes

// cUDPServer
#include "System/ClientServer/cUDPServer.h"

class __DLL_EXPORT__ cPPCDevice;

//## begin module%410898950261.additionalDeclarations preserve=yes
//## end module%410898950261.additionalDeclarations


//## begin cPPCServer%410898950261.preface preserve=yes
//## end cPPCServer%410898950261.preface

//## Class: cPPCServer%410898950261
//## Category: Control::Device::PPCCom%410896E5001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cPPCServer : public cUDPServer  //## Inherits: <unnamed>%410898AE0399
{
  //## begin cPPCServer%410898950261.initialDeclarations preserve=yes
public:
  //## end cPPCServer%410898950261.initialDeclarations

    //## Constructors (generated)
      cPPCServer();

      cPPCServer(const cPPCServer &right);

    //## Constructors (specified)
      //## Operation: cPPCServer%1091082167
      cPPCServer (cCSComm *comm, cPPCDevice *device);

    //## Destructor (generated)
      virtual ~cPPCServer();

  public:
    // Additional Public Declarations
      //## begin cPPCServer%410898950261.public preserve=yes
      //## end cPPCServer%410898950261.public

  protected:

    //## Other Operations (specified)
      //## Operation: Dispatch%1091082166
      virtual void Dispatch (cCSMsg *msg, cCSAddress *client_address);

    // Data Members for Associations

      //## Association: Control::Device::PPCCom::<unnamed>%410898D100DA
      //## Role: cPPCServer::Device%410898D200DB
      //## begin cPPCServer::Device%410898D200DB.role preserve=no  public: cPPCDevice {0..1 -> 1RFHN}
      cPPCDevice *_Device;
      //## end cPPCServer::Device%410898D200DB.role

    // Additional Protected Declarations
      //## begin cPPCServer%410898950261.protected preserve=yes
      //## end cPPCServer%410898950261.protected

  private:
    // Additional Private Declarations
      //## begin cPPCServer%410898950261.private preserve=yes
      //## end cPPCServer%410898950261.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cPPCServer%410898950261.implementation preserve=yes
      //## end cPPCServer%410898950261.implementation

};

//## begin cPPCServer%410898950261.postscript preserve=yes
//## end cPPCServer%410898950261.postscript

// Class cPPCServer 

//## begin module%410898950261.epilog preserve=yes
//## end module%410898950261.epilog


#endif
