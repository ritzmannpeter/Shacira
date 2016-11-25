//## begin module%3CAC8A25015D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CAC8A25015D.cm

//## begin module%3CAC8A25015D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3CAC8A25015D.cp

//## Module: cTCPReceiver%3CAC8A25015D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cTCPReceiver.h

#ifndef cTCPReceiver_h
#define cTCPReceiver_h 1

//## begin module%3CAC8A25015D.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%3CAC8A25015D.includes

// cError
#include "System/cError.h"
// cCharReceiver
#include "Control/SerialChannel/cCharReceiver.h"

class __DLL_EXPORT__ cCharRingBuffer;

//## begin module%3CAC8A25015D.additionalDeclarations preserve=yes
//## end module%3CAC8A25015D.additionalDeclarations


//## begin cTCPReceiver%3CAC8A25015D.preface preserve=yes
//## end cTCPReceiver%3CAC8A25015D.preface

//## Class: cTCPReceiver%3CAC8A25015D
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3CACA46F01FB;cCharRingBuffer { -> F}
//## Uses: <unnamed>%3CACA49801BE;cError { -> }

class __DLL_EXPORT__ cTCPReceiver : public cCharReceiver  //## Inherits: <unnamed>%3CAC8A8201D9
{
  //## begin cTCPReceiver%3CAC8A25015D.initialDeclarations preserve=yes
public:
  //## end cTCPReceiver%3CAC8A25015D.initialDeclarations

    //## Constructors (generated)
      cTCPReceiver();

      cTCPReceiver(const cTCPReceiver &right);

    //## Constructors (specified)
      //## Operation: cTCPReceiver%1017940475
      cTCPReceiver (SOCKET socket);

    //## Destructor (generated)
      virtual ~cTCPReceiver();


    //## Other Operations (specified)
      //## Operation: Get%1017940476
      virtual LONG_T Get (STRING_BUF_T buffer, ULONG_T amount, ULONG_T timeout);

      //## Operation: Flush%1017940477
      virtual void Flush ();

  public:
    // Additional Public Declarations
      //## begin cTCPReceiver%3CAC8A25015D.public preserve=yes
      //## end cTCPReceiver%3CAC8A25015D.public

  protected:
    // Additional Protected Declarations
      //## begin cTCPReceiver%3CAC8A25015D.protected preserve=yes
      //## end cTCPReceiver%3CAC8A25015D.protected

  private:
    // Additional Private Declarations
      //## begin cTCPReceiver%3CAC8A25015D.private preserve=yes
      //## end cTCPReceiver%3CAC8A25015D.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Socket%3CAC8AA502A2
      //## begin cTCPReceiver::Socket%3CAC8AA502A2.attr preserve=no  private: SOCKET {U} INVALID_SOCKET
      SOCKET _Socket;
      //## end cTCPReceiver::Socket%3CAC8AA502A2.attr

    // Additional Implementation Declarations
      //## begin cTCPReceiver%3CAC8A25015D.implementation preserve=yes
      //## end cTCPReceiver%3CAC8A25015D.implementation

};

//## begin cTCPReceiver%3CAC8A25015D.postscript preserve=yes
//## end cTCPReceiver%3CAC8A25015D.postscript

// Class cTCPReceiver 

//## begin module%3CAC8A25015D.epilog preserve=yes
//## end module%3CAC8A25015D.epilog


#endif
