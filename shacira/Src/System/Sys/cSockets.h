//## begin module%3DD2953F0027.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD2953F0027.cm

//## begin module%3DD2953F0027.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD2953F0027.cp

//## Module: cSockets%3DD2953F0027; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cSockets.h

#ifndef cSockets_h
#define cSockets_h 1

//## begin module%3DD2953F0027.includes preserve=yes

#if defined(__linux__)

#include "System/Sys/cLinuxPort.h"

#elif defined(_WIN32)

#include <winsock2.h>
typedef int socklen_t;
#define TIMED_OUT(ec) (ec == WSAETIMEDOUT)

#else

#pragma error("this platform is not supported")

#endif

//## end module%3DD2953F0027.includes


class cMutexSem;
class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cConvUtils;

//## begin module%3DD2953F0027.additionalDeclarations preserve=yes
//## end module%3DD2953F0027.additionalDeclarations


//## begin cSockets%3DD2953F0027.preface preserve=yes
//## end cSockets%3DD2953F0027.preface

//## Class: cSockets%3DD2953F0027
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DD29800018A;cConvUtils { -> F}
//## Uses: <unnamed>%3DD2A37201F1;cMutexSem { -> F}
//## Uses: <unnamed>%3DD2A3870273;cObjectLock { -> F}

class __DLL_EXPORT__ cSockets 
{
  //## begin cSockets%3DD2953F0027.initialDeclarations preserve=yes
public:
  //## end cSockets%3DD2953F0027.initialDeclarations

    //## Constructors (generated)
      cSockets();

      cSockets(const cSockets &right);

    //## Destructor (generated)
      virtual ~cSockets();


    //## Other Operations (specified)
      //## Operation: Initialize%1049215550
      static void Initialize ();

      //## Operation: SetReceiveTimeout%1145091000
      static BOOL_T SetReceiveTimeout (SOCKET socket, ULONG_T msecs);

  public:
    // Additional Public Declarations
      //## begin cSockets%3DD2953F0027.public preserve=yes
      //## end cSockets%3DD2953F0027.public

  protected:
    // Additional Protected Declarations
      //## begin cSockets%3DD2953F0027.protected preserve=yes
      //## end cSockets%3DD2953F0027.protected

  private:
    // Additional Private Declarations
      //## begin cSockets%3DD2953F0027.private preserve=yes
      //## end cSockets%3DD2953F0027.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: StartSockets%1037211076
      static void StartSockets ();

      //## Operation: StopSockets%1037211077
      static void StopSockets ();

    // Data Members for Class Attributes

      //## Attribute: RefCount%3DD2A1B3014E
      //## begin cSockets::RefCount%3DD2A1B3014E.attr preserve=no  implementation: static ULONG_T {U} 0
      static ULONG_T _RefCount;
      //## end cSockets::RefCount%3DD2A1B3014E.attr

      //## Attribute: Mutex%3DD2A21E0025
      //## begin cSockets::Mutex%3DD2A21E0025.attr preserve=no  implementation: static cMutexSem {U} 
      static cMutexSem _Mutex;
      //## end cSockets::Mutex%3DD2A21E0025.attr

      //## Attribute: Sockets%3E89C5F9031C
      //## begin cSockets::Sockets%3E89C5F9031C.attr preserve=no  implementation: static cSockets * {U} NULL
      static cSockets *_Sockets;
      //## end cSockets::Sockets%3E89C5F9031C.attr

    // Additional Implementation Declarations
      //## begin cSockets%3DD2953F0027.implementation preserve=yes
      //## end cSockets%3DD2953F0027.implementation

};

//## begin cSockets%3DD2953F0027.postscript preserve=yes
//## end cSockets%3DD2953F0027.postscript

// Class cSockets 

//## begin module%3DD2953F0027.epilog preserve=yes
//## end module%3DD2953F0027.epilog


#endif
