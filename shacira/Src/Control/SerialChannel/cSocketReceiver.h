//## begin module%3C34419E00AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C34419E00AF.cm

//## begin module%3C34419E00AF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C34419E00AF.cp

//## Module: cSocketReceiver%3C34419E00AF; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cSocketReceiver.h

#ifndef cSocketReceiver_h
#define cSocketReceiver_h 1

//## begin module%3C34419E00AF.includes preserve=yes
#include "System/Sys/cSockets.h"
//## end module%3C34419E00AF.includes

// cCharReceiver
#include "Control/SerialChannel/cCharReceiver.h"

class __DLL_EXPORT__ cTimeObject;
class __DLL_EXPORT__ cError;
class __DLL_EXPORT__ cCharRingBuffer;

//## begin module%3C34419E00AF.additionalDeclarations preserve=yes

#define REPORT_ONLY

//## end module%3C34419E00AF.additionalDeclarations


//## begin cSocketReceiver%3C34419E00AF.preface preserve=yes
//## end cSocketReceiver%3C34419E00AF.preface

//## Class: cSocketReceiver%3C34419E00AF
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C3493C8015E;cCharRingBuffer { -> F}
//## Uses: <unnamed>%3C35647F0385;cError { -> F}
//## Uses: <unnamed>%3C358CB9002F;cTimeObject { -> F}

class __DLL_EXPORT__ cSocketReceiver : public cCharReceiver  //## Inherits: <unnamed>%3C3441B60103
{
  //## begin cSocketReceiver%3C34419E00AF.initialDeclarations preserve=yes
public:
  //## end cSocketReceiver%3C34419E00AF.initialDeclarations

    //## Constructors (generated)
      cSocketReceiver();

      cSocketReceiver(const cSocketReceiver &right);

    //## Constructors (specified)
      //## Operation: cSocketReceiver%1010053285
      cSocketReceiver (SOCKET socket);

    //## Destructor (generated)
      virtual ~cSocketReceiver();


    //## Other Operations (specified)
      //## Operation: Get%1010053286
      virtual LONG_T Get (STRING_BUF_T buffer, ULONG_T amount, ULONG_T timeout);

      //## Operation: Flush%1010131286
      virtual void Flush ();

  public:
    // Additional Public Declarations
      //## begin cSocketReceiver%3C34419E00AF.public preserve=yes
      //## end cSocketReceiver%3C34419E00AF.public

  protected:
    // Additional Protected Declarations
      //## begin cSocketReceiver%3C34419E00AF.protected preserve=yes
      //## end cSocketReceiver%3C34419E00AF.protected

  private:
    // Additional Private Declarations
      //## begin cSocketReceiver%3C34419E00AF.private preserve=yes
      //## end cSocketReceiver%3C34419E00AF.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Socket%3C34426D025B
      //## begin cSocketReceiver::Socket%3C34426D025B.attr preserve=no  private: SOCKET {U} INVALID_SOCKET
      SOCKET _Socket;
      //## end cSocketReceiver::Socket%3C34426D025B.attr

    // Additional Implementation Declarations
      //## begin cSocketReceiver%3C34419E00AF.implementation preserve=yes
      //## end cSocketReceiver%3C34419E00AF.implementation

};

//## begin cSocketReceiver%3C34419E00AF.postscript preserve=yes
//## end cSocketReceiver%3C34419E00AF.postscript

// Class cSocketReceiver 

//## begin module%3C34419E00AF.epilog preserve=yes
//## end module%3C34419E00AF.epilog


#endif
