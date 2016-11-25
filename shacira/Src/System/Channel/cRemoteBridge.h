//## begin module%3F867D4403B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F867D4403B9.cm

//## begin module%3F867D4403B9.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F867D4403B9.cp

//## Module: cRemoteBridge%3F867D4403B9; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cRemoteBridge.h

#ifndef cRemoteBridge_h
#define cRemoteBridge_h 1

//## begin module%3F867D4403B9.includes preserve=yes
//## end module%3F867D4403B9.includes

// cChannel
#include "System/Channel/cChannel.h"

class __DLL_EXPORT__ cSHProcess;

//## begin module%3F867D4403B9.additionalDeclarations preserve=yes
//## end module%3F867D4403B9.additionalDeclarations


//## begin cRemoteBridge%3F867D4403B9.preface preserve=yes
//## end cRemoteBridge%3F867D4403B9.preface

//## Class: cRemoteBridge%3F867D4403B9
//	A remote bridge is a special type of channel that tries
//	to connect to a remote channel via name. Appearing and
//	disappearing remote channels must be handled by a remote
//	bridge.
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cRemoteBridge : public cChannel  //## Inherits: <unnamed>%3FF15ABF034B
{
  //## begin cRemoteBridge%3F867D4403B9.initialDeclarations preserve=yes
public:
  //## end cRemoteBridge%3F867D4403B9.initialDeclarations

    //## Constructors (generated)
      cRemoteBridge();

      cRemoteBridge(const cRemoteBridge &right);

    //## Constructors (specified)
      //## Operation: cRemoteBridge%1065778440
      cRemoteBridge (CONST_STRING_T channel_name, cSHProcess *process, CONST_STRING_T remote_channel_name = NULL);

    //## Destructor (generated)
      virtual ~cRemoteBridge();


    //## Other Operations (specified)
      //## Operation: Connect%1065778449
      //	Connects an adapter to the back end of the channel
      virtual void Connect (cAdapter *adapter);

      //## Operation: MainFunc%1065778448
      virtual INT_T MainFunc (void *extra);

      //## Operation: Listen%1065778442
      virtual void Listen ();

      //## Operation: StopListen%1065778443
      virtual void StopListen ();

      //## Operation: Send%1065778444
      //	Method to send an object to (into) the front end of the
      //	channel
      virtual void Send (cTransientObject *object);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: RemoteChannelName%3F8693B70128
      STRING_T get_RemoteChannelName () const;

  public:
    // Additional Public Declarations
      //## begin cRemoteBridge%3F867D4403B9.public preserve=yes
      //## end cRemoteBridge%3F867D4403B9.public

  protected:
    // Data Members for Class Attributes

      //## begin cRemoteBridge::RemoteChannelName%3F8693B70128.attr preserve=no  public: STRING_T {U} 
      STRING_T _RemoteChannelName;
      //## end cRemoteBridge::RemoteChannelName%3F8693B70128.attr

      //## Attribute: PendingAdapters%3F8694E70399
      //## begin cRemoteBridge::PendingAdapters%3F8694E70399.attr preserve=no  protected: CHANNEL_ADAPTER_LIST_T {U} 
      CHANNEL_ADAPTER_LIST_T _PendingAdapters;
      //## end cRemoteBridge::PendingAdapters%3F8694E70399.attr

    // Data Members for Associations

      //## Association: System::Channel::<unnamed>%3F867DB40232
      //## Role: cRemoteBridge::RemoteChannel%3F867DB601A5
      //## begin cRemoteBridge::RemoteChannel%3F867DB601A5.role preserve=no  public: cChannel { -> 1RFHN}
      cChannel *_RemoteChannel;
      //## end cRemoteBridge::RemoteChannel%3F867DB601A5.role

      //## Association: System::Channel::<unnamed>%3F867E040148
      //## Role: cRemoteBridge::Process%3F867E050251
      //## begin cRemoteBridge::Process%3F867E050251.role preserve=no  public: cSHProcess { -> 1RFHN}
      cSHProcess *_Process;
      //## end cRemoteBridge::Process%3F867E050251.role

    // Additional Protected Declarations
      //## begin cRemoteBridge%3F867D4403B9.protected preserve=yes
      //## end cRemoteBridge%3F867D4403B9.protected

  private:
    // Additional Private Declarations
      //## begin cRemoteBridge%3F867D4403B9.private preserve=yes
      //## end cRemoteBridge%3F867D4403B9.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ConnectPending%1065778450
      void ConnectPending ();

    // Additional Implementation Declarations
      //## begin cRemoteBridge%3F867D4403B9.implementation preserve=yes
      //## end cRemoteBridge%3F867D4403B9.implementation

};

//## begin cRemoteBridge%3F867D4403B9.postscript preserve=yes
//## end cRemoteBridge%3F867D4403B9.postscript

// Class cRemoteBridge 

//## begin module%3F867D4403B9.epilog preserve=yes
//## end module%3F867D4403B9.epilog


#endif
