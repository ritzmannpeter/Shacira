//## begin module%410281A302BF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%410281A302BF.cm

//## begin module%410281A302BF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%410281A302BF.cp

//## Module: cUDPComm%410281A302BF; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cUDPComm.h

#ifndef cUDPComm_h
#define cUDPComm_h 1

//## begin module%410281A302BF.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%410281A302BF.includes

// cInetAddress
#include "System/ClientServer/cInetAddress.h"
// cCSComm
#include "System/ClientServer/cCSComm.h"
//## begin module%410281A302BF.additionalDeclarations preserve=yes
//## end module%410281A302BF.additionalDeclarations


//## begin cUDPComm%410281A302BF.preface preserve=yes
//## end cUDPComm%410281A302BF.preface

//## Class: cUDPComm%410281A302BF
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%410285AE0148;cInetAddress { -> }

class __DLL_EXPORT__ cUDPComm : public cCSComm  //## Inherits: <unnamed>%410281C900FA
{
  //## begin cUDPComm%410281A302BF.initialDeclarations preserve=yes
public:
  //## end cUDPComm%410281A302BF.initialDeclarations

    //## Constructors (generated)
      cUDPComm();

      cUDPComm(const cUDPComm &right);

    //## Constructors (specified)
      //## Operation: cUDPComm%1090681461
      cUDPComm (unsigned short read_port, unsigned short write_port, const char *host = NULL);

    //## Destructor (generated)
      virtual ~cUDPComm();


    //## Other Operations (specified)
      //## Operation: Send%1090681458
      virtual void Send (cCSMsg *msg, cCSAddress *address);

      //## Operation: Reply%1090862817
      virtual void Reply (cCSMsg *msg, cCSAddress *client_address);

      //## Operation: Receive%1090681459
      virtual void Receive (cCSMsg &msg, cCSAddress *sender_address, ULONG_T tmo = WAIT_FOR_EVER);

      //## Operation: Receive%1107416647
      virtual LONG_T Receive (PTR_T buf, ULONG_T buf_size, cCSAddress *sender_address, ULONG_T tmo = WAIT_FOR_EVER);

      //## Operation: ReadAddress%1090862812
      virtual cCSAddress * ReadAddress ();

      //## Operation: WriteAddress%1090862813
      virtual cCSAddress * WriteAddress ();

  public:
    // Additional Public Declarations
      //## begin cUDPComm%410281A302BF.public preserve=yes
      //## end cUDPComm%410281A302BF.public

  protected:
    // Additional Protected Declarations
      //## begin cUDPComm%410281A302BF.protected preserve=yes
      //## end cUDPComm%410281A302BF.protected

  private:
    // Additional Private Declarations
      //## begin cUDPComm%410281A302BF.private preserve=yes
      //## end cUDPComm%410281A302BF.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: SetReadTimeout%1090681470
      void SetReadTimeout (ULONG_T tmo);

    // Data Members for Class Attributes

      //## Attribute: ReadPort%41050B730109
      //## begin cUDPComm::ReadPort%41050B730109.attr preserve=no  implementation: unsigned short {U} 0
      unsigned short _ReadPort;
      //## end cUDPComm::ReadPort%41050B730109.attr

      //## Attribute: WritePort%41050B86031C
      //## begin cUDPComm::WritePort%41050B86031C.attr preserve=no  implementation: unsigned short {U} 0
      unsigned short _WritePort;
      //## end cUDPComm::WritePort%41050B86031C.attr

      //## Attribute: ReadSocket%4102AA2102FD
      //## begin cUDPComm::ReadSocket%4102AA2102FD.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _ReadSocket;
      //## end cUDPComm::ReadSocket%4102AA2102FD.attr

      //## Attribute: WriteSocket%4104B6D1037A
      //## begin cUDPComm::WriteSocket%4104B6D1037A.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _WriteSocket;
      //## end cUDPComm::WriteSocket%4104B6D1037A.attr

      //## Attribute: Host%4105466800BB
      //## begin cUDPComm::Host%4105466800BB.attr preserve=no  implementation: const char * {U} NULL
      const char *_Host;
      //## end cUDPComm::Host%4105466800BB.attr

    // Additional Implementation Declarations
      //## begin cUDPComm%410281A302BF.implementation preserve=yes
      //## end cUDPComm%410281A302BF.implementation

};

//## begin cUDPComm%410281A302BF.postscript preserve=yes
//## end cUDPComm%410281A302BF.postscript

// Class cUDPComm 

//## begin module%410281A302BF.epilog preserve=yes
//## end module%410281A302BF.epilog


#endif
