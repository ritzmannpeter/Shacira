//## begin module%3F85593E00AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F85593E00AB.cm

//## begin module%3F85593E00AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F85593E00AB.cp

//## Module: cCOSChannel%3F85593E00AB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cCOSChannel.h

#ifndef cCOSChannel_h
#define cCOSChannel_h 1

//## begin module%3F85593E00AB.includes preserve=yes
//## end module%3F85593E00AB.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cRemoteChannel
#include "System/Channel/cRemoteChannel.h"
// cCosEventChannelProxy
#include "Orb/cCosEventChannelProxy.h"
//## begin module%3F85593E00AB.additionalDeclarations preserve=yes
//## end module%3F85593E00AB.additionalDeclarations


//## begin cCOSChannel%3F85593E00AB.preface preserve=yes
//## end cCOSChannel%3F85593E00AB.preface

//## Class: cCOSChannel%3F85593E00AB
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F8559A302CE;cTransientObject { -> }
//## Uses: <unnamed>%3FFE86840119;cCosEventChannelProxy { -> }

class __DLL_EXPORT__ cCOSChannel : public cRemoteChannel  //## Inherits: <unnamed>%3FFE7FB401C5
{
  //## begin cCOSChannel%3F85593E00AB.initialDeclarations preserve=yes
public:
  //## end cCOSChannel%3F85593E00AB.initialDeclarations

    //## Constructors (generated)
      cCOSChannel();

      cCOSChannel(const cCOSChannel &right);

    //## Constructors (specified)
      //## Operation: cCOSChannel%1065703992
      cCOSChannel (CONST_STRING_T channel_name, cCosEventChannelProxy *proxy);

    //## Destructor (generated)
      virtual ~cCOSChannel();


    //## Other Operations (specified)
      //## Operation: Listen%1065703997
      virtual void Listen ();

      //## Operation: StopListen%1065703998
      virtual void StopListen ();

      //## Operation: Send%1065703993
      //	Method to send an object to (into) the front end of the
      //	channel
      virtual void Send (cTransientObject *object);

  public:
    // Additional Public Declarations
      //## begin cCOSChannel%3F85593E00AB.public preserve=yes
      //## end cCOSChannel%3F85593E00AB.public

  protected:
    // Additional Protected Declarations
      //## begin cCOSChannel%3F85593E00AB.protected preserve=yes
      //## end cCOSChannel%3F85593E00AB.protected

  private:
    // Additional Private Declarations
      //## begin cCOSChannel%3F85593E00AB.private preserve=yes
      //## end cCOSChannel%3F85593E00AB.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCOSChannel%3F85593E00AB.implementation preserve=yes
      //## end cCOSChannel%3F85593E00AB.implementation

};

//## begin cCOSChannel%3F85593E00AB.postscript preserve=yes
//## end cCOSChannel%3F85593E00AB.postscript

// Class cCOSChannel 

//## begin module%3F85593E00AB.epilog preserve=yes
//## end module%3F85593E00AB.epilog


#endif
