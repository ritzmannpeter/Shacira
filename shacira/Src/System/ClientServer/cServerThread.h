//## begin module%4296ED620186.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4296ED620186.cm

//## begin module%4296ED620186.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4296ED620186.cp

//## Module: cServerThread%4296ED620186; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cServerThread.h

#ifndef cServerThread_h
#define cServerThread_h 1

//## begin module%4296ED620186.includes preserve=yes
//## end module%4296ED620186.includes

// eb_thread
#include "base/eb_thread.hpp"
// cTCPComm
#include "System/ClientServer/cTCPComm.h"

class __DLL_EXPORT__ cServer;

//## begin module%4296ED620186.additionalDeclarations preserve=yes
//## end module%4296ED620186.additionalDeclarations


//## begin cServerThread%4296ED620186.preface preserve=yes
//## end cServerThread%4296ED620186.preface

//## Class: cServerThread%4296ED620186
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%429AC1BC0186;cTCPComm { -> }

class __DLL_EXPORT__ cServerThread : public cThread  //## Inherits: <unnamed>%4296ED7D02BF
{
  //## begin cServerThread%4296ED620186.initialDeclarations preserve=yes
public:
  //## end cServerThread%4296ED620186.initialDeclarations

    //## Constructors (generated)
      cServerThread();

      cServerThread(const cServerThread &right);

    //## Constructors (specified)
      //## Operation: cServerThread%1117174991
      cServerThread (cServer *server, SOCKET socket);

    //## Destructor (generated)
      virtual ~cServerThread();


    //## Other Operations (specified)
      //## Operation: onMain%1117174992
      virtual INT_T onMain (void *extra);

  public:
    // Additional Public Declarations
      //## begin cServerThread%4296ED620186.public preserve=yes
      //## end cServerThread%4296ED620186.public

  protected:
    // Data Members for Associations

      //## Association: System::ClientServer::<unnamed>%4296F1C202FD
      //## Role: cServerThread::Server%4296F1C30222
      //## begin cServerThread::Server%4296F1C30222.role preserve=no  public: cServer { -> 1RFHN}
      cServer *_Server;
      //## end cServerThread::Server%4296F1C30222.role

    // Additional Protected Declarations
      //## begin cServerThread%4296ED620186.protected preserve=yes
      //## end cServerThread%4296ED620186.protected

  private:
    // Additional Private Declarations
      //## begin cServerThread%4296ED620186.private preserve=yes
      //## end cServerThread%4296ED620186.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: FreeResources%1117204074
      void FreeResources ();

    // Data Members for Class Attributes

      //## Attribute: Socket%4296FD6E0251
      //## begin cServerThread::Socket%4296FD6E0251.attr preserve=no  implementation: SOCKET {U} INVALID_SOCKET
      SOCKET _Socket;
      //## end cServerThread::Socket%4296FD6E0251.attr

    // Additional Implementation Declarations
      //## begin cServerThread%4296ED620186.implementation preserve=yes
      //## end cServerThread%4296ED620186.implementation

};

//## begin cServerThread%4296ED620186.postscript preserve=yes
//## end cServerThread%4296ED620186.postscript

// Class cServerThread 

//## begin module%4296ED620186.epilog preserve=yes
//## end module%4296ED620186.epilog


#endif
