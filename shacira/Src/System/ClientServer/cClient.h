//## begin module%42959917003F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42959917003F.cm

//## begin module%42959917003F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%42959917003F.cp

//## Module: cClient%42959917003F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cClient.h

#ifndef cClient_h
#define cClient_h 1

//## begin module%42959917003F.includes preserve=yes
//## end module%42959917003F.includes

// cTCPComm
#include "System/ClientServer/cTCPComm.h"
//## begin module%42959917003F.additionalDeclarations preserve=yes
//## end module%42959917003F.additionalDeclarations


//## begin cClient%42959917003F.preface preserve=yes
//## end cClient%42959917003F.preface

//## Class: cClient%42959917003F
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%429AC116004E;cTCPComm { -> }

class __DLL_EXPORT__ cClient 
{
  //## begin cClient%42959917003F.initialDeclarations preserve=yes
public:
  //## end cClient%42959917003F.initialDeclarations

    //## Constructors (generated)
      cClient();

      cClient(const cClient &right);

    //## Constructors (specified)
      //## Operation: cClient%1117174981
      cClient (USHORT_T server_port, CONST_STRING_T server_host = "localhost");

    //## Destructor (generated)
      virtual ~cClient();


    //## Other Operations (specified)
      //## Operation: Request%1117174982
      int Request (cStreamMsg &in_msg, cStreamMsg &out_msg, ULONG_T request_id = 0);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ServerPort%42959AF000B8
      USHORT_T get_ServerPort () const;
      void set_ServerPort (USHORT_T value);

      //## Attribute: ServerHost%42959B18015F
      STRING_T get_ServerHost () const;
      void set_ServerHost (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cClient%42959917003F.public preserve=yes
      //## end cClient%42959917003F.public

  protected:
    // Data Members for Class Attributes

      //## begin cClient::ServerPort%42959AF000B8.attr preserve=no  public: USHORT_T {U} 0
      USHORT_T _ServerPort;
      //## end cClient::ServerPort%42959AF000B8.attr

      //## begin cClient::ServerHost%42959B18015F.attr preserve=no  public: STRING_T {U} "localhost"
      STRING_T _ServerHost;
      //## end cClient::ServerHost%42959B18015F.attr

    // Additional Protected Declarations
      //## begin cClient%42959917003F.protected preserve=yes
      //## end cClient%42959917003F.protected

  private:
    // Additional Private Declarations
      //## begin cClient%42959917003F.private preserve=yes
      //## end cClient%42959917003F.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Initialize%1117174987
      void Initialize ();

      //## Operation: Connect%1117174983
      INT_T Connect ();

    // Data Members for Class Attributes

      //## Attribute: Socket%4295A1E801FD
      //## begin cClient::Socket%4295A1E801FD.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _Socket;
      //## end cClient::Socket%4295A1E801FD.attr

      //## Attribute: Connected%4296E587029F
      //## begin cClient::Connected%4296E587029F.attr preserve=no  implementation: BOOL_T {U} false
      BOOL_T _Connected;
      //## end cClient::Connected%4296E587029F.attr

    // Additional Implementation Declarations
      //## begin cClient%42959917003F.implementation preserve=yes
      //## end cClient%42959917003F.implementation

};

//## begin cClient%42959917003F.postscript preserve=yes
//## end cClient%42959917003F.postscript

// Class cClient 

//## begin module%42959917003F.epilog preserve=yes
//## end module%42959917003F.epilog


#endif
