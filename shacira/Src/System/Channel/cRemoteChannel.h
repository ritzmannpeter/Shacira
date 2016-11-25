//## begin module%3FFE7F5901E4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FFE7F5901E4.cm

//## begin module%3FFE7F5901E4.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FFE7F5901E4.cp

//## Module: cRemoteChannel%3FFE7F5901E4; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cRemoteChannel.h

#ifndef cRemoteChannel_h
#define cRemoteChannel_h 1

//## begin module%3FFE7F5901E4.includes preserve=yes
//## end module%3FFE7F5901E4.includes

// cChannel
#include "System/Channel/cChannel.h"

class __DLL_EXPORT__ cChannelProxy;

//## begin module%3FFE7F5901E4.additionalDeclarations preserve=yes
//## end module%3FFE7F5901E4.additionalDeclarations


//## begin cRemoteChannel%3FFE7F5901E4.preface preserve=yes
//## end cRemoteChannel%3FFE7F5901E4.preface

//## Class: cRemoteChannel%3FFE7F5901E4
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cRemoteChannel : public cChannel  //## Inherits: <unnamed>%3FFE7FA50261
{
  //## begin cRemoteChannel%3FFE7F5901E4.initialDeclarations preserve=yes
public:
  //## end cRemoteChannel%3FFE7F5901E4.initialDeclarations

    //## Constructors (generated)
      cRemoteChannel();

      cRemoteChannel(const cRemoteChannel &right);

    //## Constructors (specified)
      //## Operation: cRemoteChannel%1073642249
      cRemoteChannel (CONST_STRING_T channel_name, cChannelProxy *proxy);

    //## Destructor (generated)
      virtual ~cRemoteChannel();

  public:
    // Additional Public Declarations
      //## begin cRemoteChannel%3FFE7F5901E4.public preserve=yes
      //## end cRemoteChannel%3FFE7F5901E4.public

  protected:
    // Data Members for Associations

      //## Association: System::Channel::<unnamed>%3FFE84B6030D
      //## Role: cRemoteChannel::Proxy%3FFE84B8035B
      //## begin cRemoteChannel::Proxy%3FFE84B8035B.role preserve=no  public: cChannelProxy { -> 1RFHN}
      cChannelProxy *_Proxy;
      //## end cRemoteChannel::Proxy%3FFE84B8035B.role

    // Additional Protected Declarations
      //## begin cRemoteChannel%3FFE7F5901E4.protected preserve=yes
      //## end cRemoteChannel%3FFE7F5901E4.protected

  private:
    // Additional Private Declarations
      //## begin cRemoteChannel%3FFE7F5901E4.private preserve=yes
      //## end cRemoteChannel%3FFE7F5901E4.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cRemoteChannel%3FFE7F5901E4.implementation preserve=yes
      //## end cRemoteChannel%3FFE7F5901E4.implementation

};

//## begin cRemoteChannel%3FFE7F5901E4.postscript preserve=yes
//## end cRemoteChannel%3FFE7F5901E4.postscript

// Class cRemoteChannel 

//## begin module%3FFE7F5901E4.epilog preserve=yes
//## end module%3FFE7F5901E4.epilog


#endif
