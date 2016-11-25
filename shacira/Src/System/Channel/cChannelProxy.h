//## begin module%3AF294560295.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AF294560295.cm

//## begin module%3AF294560295.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AF294560295.cp

//## Module: cChannelProxy%3AF294560295; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cChannelProxy.h

#ifndef cChannelProxy_h
#define cChannelProxy_h 1

//## begin module%3AF294560295.includes preserve=yes
//## end module%3AF294560295.includes

// cProxy
#include "System/Objects/cProxy.h"
// cTransferObject
#include "System/Objects/cTransferObject.h"
// cChannel
#include "System/Channel/cChannel.h"

class cMutexSem;

//## begin module%3AF294560295.additionalDeclarations preserve=yes
//## end module%3AF294560295.additionalDeclarations


//## begin cChannelProxy%3AF294560295.preface preserve=yes
//## end cChannelProxy%3AF294560295.preface

//## Class: cChannelProxy%3AF294560295
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5B2B070114;cTransferObject { -> }
//## Uses: <unnamed>%3F866A7A02AF;cChannel { -> }
//## Uses: <unnamed>%4167E9FB0399;cMutexSem { -> F}

class __DLL_EXPORT__ cChannelProxy : public cProxy  //## Inherits: <unnamed>%3EDCC9340167
{
  //## begin cChannelProxy%3AF294560295.initialDeclarations preserve=yes
public:
  //## end cChannelProxy%3AF294560295.initialDeclarations

    //## Constructors (generated)
      cChannelProxy();

      cChannelProxy(const cChannelProxy &right);

    //## Destructor (generated)
      virtual ~cChannelProxy();


    //## Other Operations (specified)
      //## Operation: Send%1012812229
      virtual BOOL_T Send (cTransientObject *object) = 0;

      //## Operation: Listen%1054632831
      virtual BOOL_T Listen () = 0;

      //## Operation: Object%1054547845
      virtual void Object (cTransientObject *object);

      //## Operation: RegisterChannel%1065773702
      void RegisterChannel (cChannel *channel);

  public:
    // Additional Public Declarations
      //## begin cChannelProxy%3AF294560295.public preserve=yes
      //## end cChannelProxy%3AF294560295.public

  protected:
    // Additional Protected Declarations
      //## begin cChannelProxy%3AF294560295.protected preserve=yes
      //## end cChannelProxy%3AF294560295.protected

  private:
    // Additional Private Declarations
      //## begin cChannelProxy%3AF294560295.private preserve=yes
      //## end cChannelProxy%3AF294560295.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: ChannelName%3EDCDBE601D4
      //## begin cChannelProxy::ChannelName%3EDCDBE601D4.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _ChannelName;
      //## end cChannelProxy::ChannelName%3EDCDBE601D4.attr

      //## Attribute: Channels%3EDCDBB10138
      //## begin cChannelProxy::Channels%3EDCDBB10138.attr preserve=no  implementation: CHANNEL_LIST_T {U} 
      CHANNEL_LIST_T _Channels;
      //## end cChannelProxy::Channels%3EDCDBB10138.attr

    // Additional Implementation Declarations
      //## begin cChannelProxy%3AF294560295.implementation preserve=yes
      //## end cChannelProxy%3AF294560295.implementation

};

//## begin cChannelProxy%3AF294560295.postscript preserve=yes
//## end cChannelProxy%3AF294560295.postscript

// Class cChannelProxy 

//## begin module%3AF294560295.epilog preserve=yes
//## end module%3AF294560295.epilog


#endif
