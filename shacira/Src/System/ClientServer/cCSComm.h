//## begin module%4102741F004E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4102741F004E.cm

//## begin module%4102741F004E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4102741F004E.cp

//## Module: cCSComm%4102741F004E; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cCSComm.h

#ifndef cCSComm_h
#define cCSComm_h 1

//## begin module%4102741F004E.includes preserve=yes
//## end module%4102741F004E.includes

// cCSMsg
#include "System/ClientServer/cCSMsg.h"

class __DLL_EXPORT__ cUDPClient;
class __DLL_EXPORT__ cCSAddress;
class __DLL_EXPORT__ cUDPServer;

//## begin module%4102741F004E.additionalDeclarations preserve=yes

#define WAIT_FOR_EVER   0xFFFFFFFF

//## end module%4102741F004E.additionalDeclarations


//## begin cCSComm%4102741F004E.preface preserve=yes
//## end cCSComm%4102741F004E.preface

//## Class: cCSComm%4102741F004E
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%410276970280;cCSMsg { -> }

class __DLL_EXPORT__ cCSComm 
{
  //## begin cCSComm%4102741F004E.initialDeclarations preserve=yes
public:
  //## end cCSComm%4102741F004E.initialDeclarations

    //## Constructors (generated)
      cCSComm();

      cCSComm(const cCSComm &right);

    //## Destructor (generated)
      virtual ~cCSComm();


    //## Other Operations (specified)
      //## Operation: Send%1090681454
      virtual void Send (cCSMsg *msg, cCSAddress *address) = 0;

      //## Operation: Reply%1090862816
      virtual void Reply (cCSMsg *msg, cCSAddress *client_address) = 0;

      //## Operation: Receive%1090680480
      virtual void Receive (cCSMsg &msg, cCSAddress *sender_address, ULONG_T tmo = WAIT_FOR_EVER) = 0;

      //## Operation: Receive%1107416648
      virtual LONG_T Receive (PTR_T buf, ULONG_T buf_size, cCSAddress *sender_address, ULONG_T tmo = WAIT_FOR_EVER) = 0;

      //## Operation: ReadAddress%1090862814
      virtual cCSAddress * ReadAddress () = 0;

      //## Operation: WriteAddress%1090862815
      virtual cCSAddress * WriteAddress () = 0;

  public:
    // Additional Public Declarations
      //## begin cCSComm%4102741F004E.public preserve=yes
      //## end cCSComm%4102741F004E.public

  protected:
    // Data Members for Associations

      //## Association: System::ClientServer::<unnamed>%4104D43E0271
      //## Role: cCSComm::Server%4104D43F01D5
      //## begin cCSComm::Server%4104D43F01D5.role preserve=no  public: cUDPServer {1 -> 0..1RFHN}
      cUDPServer *_Server;
      //## end cCSComm::Server%4104D43F01D5.role

      //## Association: System::ClientServer::<unnamed>%41054483030D
      //## Role: cCSComm::ReadAddress%410544840280
      //## begin cCSComm::ReadAddress%410544840280.role preserve=no  public: cCSAddress { -> 1RFHN}
      cCSAddress *_ReadAddress;
      //## end cCSComm::ReadAddress%410544840280.role

      //## Association: System::ClientServer::<unnamed>%4105448A031C
      //## Role: cCSComm::WriteAddress%4105448B0399
      //## begin cCSComm::WriteAddress%4105448B0399.role preserve=no  public: cCSAddress { -> 1RFHN}
      cCSAddress *_WriteAddress;
      //## end cCSComm::WriteAddress%4105448B0399.role

      //## Association: System::ClientServer::<unnamed>%4104D4150167
      //## Role: cCSComm::Client%4104D41600DB
      //## begin cCSComm::Client%4104D41600DB.role preserve=no  public: cUDPClient {1 -> 0..1RFHN}
      cUDPClient *_Client;
      //## end cCSComm::Client%4104D41600DB.role

    // Additional Protected Declarations
      //## begin cCSComm%4102741F004E.protected preserve=yes
      //## end cCSComm%4102741F004E.protected

  private:
    // Additional Private Declarations
      //## begin cCSComm%4102741F004E.private preserve=yes
      //## end cCSComm%4102741F004E.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCSComm%4102741F004E.implementation preserve=yes
      //## end cCSComm%4102741F004E.implementation

};

//## begin cCSComm%4102741F004E.postscript preserve=yes
//## end cCSComm%4102741F004E.postscript

// Class cCSComm 

//## begin module%4102741F004E.epilog preserve=yes
//## end module%4102741F004E.epilog


#endif
