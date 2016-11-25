//## begin module%4104CB3B00AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4104CB3B00AB.cm

//## begin module%4104CB3B00AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4104CB3B00AB.cp

//## Module: cUDPServer%4104CB3B00AB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cUDPServer.h

#ifndef cUDPServer_h
#define cUDPServer_h 1

//## begin module%4104CB3B00AB.includes preserve=yes
//## end module%4104CB3B00AB.includes

// eb_thread
#include "base/eb_thread.hpp"
// cCSMsg
#include "System/ClientServer/cCSMsg.h"
// cCSAddress
#include "System/ClientServer/cCSAddress.h"

class __DLL_EXPORT__ cInetAddress;
class __DLL_EXPORT__ cCSComm;

//## begin module%4104CB3B00AB.additionalDeclarations preserve=yes
//## end module%4104CB3B00AB.additionalDeclarations


//## begin cUDPServer%4104CB3B00AB.preface preserve=yes
//## end cUDPServer%4104CB3B00AB.preface

//## Class: cUDPServer%4104CB3B00AB
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4104EB2F0242;cCSMsg { -> }
//## Uses: <unnamed>%4104EB500148;cCSAddress { -> }
//## Uses: <unnamed>%4201DEF8007D;cInetAddress { -> F}

class __DLL_EXPORT__ cUDPServer : public cThread  //## Inherits: <unnamed>%4104E0DC0138
{
  //## begin cUDPServer%4104CB3B00AB.initialDeclarations preserve=yes
public:
  //## end cUDPServer%4104CB3B00AB.initialDeclarations

    //## Constructors (generated)
      cUDPServer();

      cUDPServer(const cUDPServer &right);

    //## Constructors (specified)
      //## Operation: cUDPServer%1090833149
      cUDPServer (cCSComm *comm);

    //## Destructor (generated)
      virtual ~cUDPServer();


    //## Other Operations (specified)
      //## Operation: Start%1090840949
      void Start ();

      //## Operation: Stop%1090840950
      void Stop ();

      //## Operation: onEnter%1090833157
      virtual BOOL_T onEnter (void *extra);

      //## Operation: onMain%1090833158
      virtual INT_T onMain (void *extra);

      //## Operation: onLeave%1090833159
      virtual void onLeave (INT_T rc);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Terminated%4104E42F036B
      BOOL_T get_Terminated () const;
      void set_Terminated (BOOL_T value);

  public:
    // Additional Public Declarations
      //## begin cUDPServer%4104CB3B00AB.public preserve=yes
      //## end cUDPServer%4104CB3B00AB.public

  protected:

    //## Other Operations (specified)
      //## Operation: Dispatch%1090833151
      virtual void Dispatch (cCSMsg *msg, cCSAddress *client_address);

      //## Operation: Reply%1090833152
      void Reply (cCSMsg *msg, cCSAddress *client_address = NULL);

    // Data Members for Class Attributes

      //## begin cUDPServer::Terminated%4104E42F036B.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Terminated;
      //## end cUDPServer::Terminated%4104E42F036B.attr

      //## Attribute: InBuf%4201D6CB033C
      //## begin cUDPServer::InBuf%4201D6CB033C.attr preserve=no  protected: BUF_T {U} NULL
      BUF_T _InBuf;
      //## end cUDPServer::InBuf%4201D6CB033C.attr

      //## Attribute: InBufSize%4201D70F032C
      //## begin cUDPServer::InBufSize%4201D70F032C.attr preserve=no  protected: ULONG_T {U} 0x2000
      ULONG_T _InBufSize;
      //## end cUDPServer::InBufSize%4201D70F032C.attr

    // Data Members for Associations

      //## Association: System::ClientServer::<unnamed>%4104D43E0271
      //## Role: cUDPServer::CSComm%4104D43F01D4
      //## begin cUDPServer::CSComm%4104D43F01D4.role preserve=no  public: cCSComm {0..1 -> 1RFHN}
      cCSComm *_CSComm;
      //## end cUDPServer::CSComm%4104D43F01D4.role

    // Additional Protected Declarations
      //## begin cUDPServer%4104CB3B00AB.protected preserve=yes
      //## end cUDPServer%4104CB3B00AB.protected

  private:
    // Additional Private Declarations
      //## begin cUDPServer%4104CB3B00AB.private preserve=yes
      //## end cUDPServer%4104CB3B00AB.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cUDPServer%4104CB3B00AB.implementation preserve=yes
      //## end cUDPServer%4104CB3B00AB.implementation

};

//## begin cUDPServer%4104CB3B00AB.postscript preserve=yes
//## end cUDPServer%4104CB3B00AB.postscript

// Class cUDPServer 

//## begin module%4104CB3B00AB.epilog preserve=yes
//## end module%4104CB3B00AB.epilog


#endif
