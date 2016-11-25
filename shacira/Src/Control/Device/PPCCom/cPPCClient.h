//## begin module%4108980A01F4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4108980A01F4.cm

//## begin module%4108980A01F4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4108980A01F4.cp

//## Module: cPPCClient%4108980A01F4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\PPCCom\cPPCClient.h

#ifndef cPPCClient_h
#define cPPCClient_h 1

//## begin module%4108980A01F4.includes preserve=yes
//## end module%4108980A01F4.includes

// cUDPClient
#include "System/ClientServer/cUDPClient.h"

class __DLL_EXPORT__ cPPCDevice;

//## begin module%4108980A01F4.additionalDeclarations preserve=yes
//## end module%4108980A01F4.additionalDeclarations


//## begin cPPCClient%4108980A01F4.preface preserve=yes
//## end cPPCClient%4108980A01F4.preface

//## Class: cPPCClient%4108980A01F4
//## Category: Control::Device::PPCCom%410896E5001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cPPCClient : public cUDPClient  //## Inherits: <unnamed>%4108986F01E4
{
  //## begin cPPCClient%4108980A01F4.initialDeclarations preserve=yes
public:
  //## end cPPCClient%4108980A01F4.initialDeclarations

    //## Constructors (generated)
      cPPCClient();

      cPPCClient(const cPPCClient &right);

    //## Constructors (specified)
      //## Operation: cPPCClient%1091082168
      cPPCClient (cCSComm *comm, cPPCDevice *device);

    //## Destructor (generated)
      virtual ~cPPCClient();


    //## Other Operations (specified)
      //## Operation: Dispatch%1091082165
      virtual void Dispatch (cCSMsg *msg, cCSAddress *client_address);

  public:
    // Additional Public Declarations
      //## begin cPPCClient%4108980A01F4.public preserve=yes
      //## end cPPCClient%4108980A01F4.public

  protected:
    // Data Members for Associations

      //## Association: Control::Device::PPCCom::<unnamed>%4108990700BB
      //## Role: cPPCClient::Device%41089907034C
      //## begin cPPCClient::Device%41089907034C.role preserve=no  public: cPPCDevice {0..1 -> 1RFHN}
      cPPCDevice *_Device;
      //## end cPPCClient::Device%41089907034C.role

    // Additional Protected Declarations
      //## begin cPPCClient%4108980A01F4.protected preserve=yes
      //## end cPPCClient%4108980A01F4.protected

  private:
    // Additional Private Declarations
      //## begin cPPCClient%4108980A01F4.private preserve=yes
      //## end cPPCClient%4108980A01F4.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cPPCClient%4108980A01F4.implementation preserve=yes
      //## end cPPCClient%4108980A01F4.implementation

};

//## begin cPPCClient%4108980A01F4.postscript preserve=yes
//## end cPPCClient%4108980A01F4.postscript

// Class cPPCClient 

//## begin module%4108980A01F4.epilog preserve=yes
//## end module%4108980A01F4.epilog


#endif
