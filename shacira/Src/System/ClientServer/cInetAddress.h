//## begin module%410281DC01D4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%410281DC01D4.cm

//## begin module%410281DC01D4.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%410281DC01D4.cp

//## Module: cInetAddress%410281DC01D4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cInetAddress.h

#ifndef cInetAddress_h
#define cInetAddress_h 1

//## begin module%410281DC01D4.includes preserve=yes

#include "System/Sys/cSockets.h"
typedef struct sockaddr_in IN_ADDRESS_T;
typedef struct sockaddr SOCK_ADDRESS_T;
typedef struct sockaddr_in * IN_ADDRESS_PTR;
typedef struct sockaddr * SOCK_ADDRESS_PTR;

//## end module%410281DC01D4.includes

// cCSAddress
#include "System/ClientServer/cCSAddress.h"
//## begin module%410281DC01D4.additionalDeclarations preserve=yes
//## end module%410281DC01D4.additionalDeclarations


//## begin cInetAddress%410281DC01D4.preface preserve=yes
//## end cInetAddress%410281DC01D4.preface

//## Class: cInetAddress%410281DC01D4
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cInetAddress : public cCSAddress  //## Inherits: <unnamed>%4102826D01E4
{
  //## begin cInetAddress%410281DC01D4.initialDeclarations preserve=yes
public:
  //## end cInetAddress%410281DC01D4.initialDeclarations

    //## Constructors (generated)
      cInetAddress();

      cInetAddress(const cInetAddress &right);

    //## Constructors (specified)
      //## Operation: cInetAddress%1090681462
      cInetAddress (USHORT_T port, CONST_STRING_T host = NULL);

    //## Destructor (generated)
      virtual ~cInetAddress();


    //## Other Operations (specified)
      //## Operation: Sender%1090862820
      virtual const char * Sender ();

      //## Operation: SetAddress%1090681465
      void SetAddress (USHORT_T port, CONST_STRING_T host = "localhost");

      //## Operation: SetAddress%1090681466
      void SetAddress (IN_ADDRESS_PTR address);

      //## Operation: SetAddress%1090840952
      void SetAddress (IN_ADDRESS_PTR address, unsigned short port);

      //## Operation: SetAddress%1090681467
      void SetAddress (SOCK_ADDRESS_PTR address);

      //## Operation: InetAddr%1090681463
      IN_ADDRESS_PTR InetAddr ();

      //## Operation: SockAddr%1090681464
      SOCK_ADDRESS_PTR SockAddr ();

      //## Operation: InetAddress%1090695922
      const char * InetAddress ();

      //## Operation: Port%1090695923
      USHORT_T Port ();

      //## Operation: SetPort%1090840953
      void SetPort (unsigned short port);

  public:
    // Additional Public Declarations
      //## begin cInetAddress%410281DC01D4.public preserve=yes
      //## end cInetAddress%410281DC01D4.public

  protected:
    // Additional Protected Declarations
      //## begin cInetAddress%410281DC01D4.protected preserve=yes
      //## end cInetAddress%410281DC01D4.protected

  private:
    // Additional Private Declarations
      //## begin cInetAddress%410281DC01D4.private preserve=yes
      //## end cInetAddress%410281DC01D4.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Address%410291F9038A
      //## begin cInetAddress::Address%410291F9038A.attr preserve=no  implementation: IN_ADDRESS_T {U} 
      IN_ADDRESS_T _Address;
      //## end cInetAddress::Address%410291F9038A.attr

    // Additional Implementation Declarations
      //## begin cInetAddress%410281DC01D4.implementation preserve=yes
      //## end cInetAddress%410281DC01D4.implementation

};

//## begin cInetAddress%410281DC01D4.postscript preserve=yes
//## end cInetAddress%410281DC01D4.postscript

// Class cInetAddress 

//## begin module%410281DC01D4.epilog preserve=yes
//## end module%410281DC01D4.epilog


#endif
