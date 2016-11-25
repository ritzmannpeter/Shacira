//## begin module%3F82F311037A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F82F311037A.cm

//## begin module%3F82F311037A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F82F311037A.cp

//## Module: cChannel%3F82F311037A; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cChannel.h

#ifndef cChannel_h
#define cChannel_h 1

//## begin module%3F82F311037A.includes preserve=yes
//## end module%3F82F311037A.includes

// cPtrList
#include "System/Memory/cPtrList.h"
// cControlThread
#include "System/Threads/cControlThread.h"
// cAdapter
#include "System/Channel/cAdapter.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cConnector;

//## begin module%3F82F311037A.additionalDeclarations preserve=yes

typedef cPtrList CHANNEL_LIST_T;
typedef cPtrList CHANNEL_ADAPTER_LIST_T;
#define CHANNEL_VECTOR_SIZE    0x100
class cChannel;
typedef cChannel ** CHANNEL_VECTOR_T;

//## end module%3F82F311037A.additionalDeclarations


//## begin cChannel%3F82F311037A.preface preserve=yes
//## end cChannel%3F82F311037A.preface

//## Class: cChannel%3F82F311037A
//	Base class for channels.
//	A channel is a software object that receives transient
//	objects at the front end and transfers the object to the
//	back end of the channel.
//	A channel realizes an async m:n communication between
//	software objects that potentially crosses (but must not)
//	process or network borders.
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F82F473030D;cAdapter { -> }
//## Uses: <unnamed>%3F82F5F9033C;cTransientObject { -> F}
//## Uses: <unnamed>%3F8518350251;cConnector { -> F}
//## Uses: <unnamed>%3FFE7C6602EE;cPtrList { -> }

class __DLL_EXPORT__ cChannel : public cControlThread  //## Inherits: <unnamed>%3FF01DB703B9
{
  //## begin cChannel%3F82F311037A.initialDeclarations preserve=yes
public:
  //## end cChannel%3F82F311037A.initialDeclarations

    //## Constructors (generated)
      cChannel();

      cChannel(const cChannel &right);

    //## Constructors (specified)
      //## Operation: cChannel%1065547488
      cChannel (CONST_STRING_T channel_name);

    //## Destructor (generated)
      virtual ~cChannel();


    //## Other Operations (specified)
      //## Operation: Start%1072782024
      virtual void Start ();

      //## Operation: Stop%1072782025
      virtual void Stop ();

      //## Operation: Connect%1065547480
      //	Connects an adapter to the back end of the channel
      virtual void Connect (cAdapter *adapter);

      //## Operation: Connect%1065687232
      //	Connects the back end of the channel to the front end of
      //	"front_end"
      void Connect (cChannel *channel);

      //## Operation: Disconnect%1065547481
      //	Disconnects an adapter from the back end of the channel
      void Disconnect (cAdapter *adapter);

      //## Operation: Disconnect%1073642244
      //	Disconnects a channel from the back end of the channel
      void Disconnect (cChannel *channel);

      //## Operation: Listen%1073642247
      //	Enables listening to incoming objects at the back end of
      //	the channel.
      virtual void Listen ();

      //## Operation: StopListen%1073642248
      //	Stop listening to the back end of the channel. Incoming
      //	objects are no more processed.
      virtual void StopListen ();

      //## Operation: Send%1065547482
      //	Method to send an object to (into) the front end of the
      //	channel
      virtual void Send (cTransientObject *object) = 0;

      //## Operation: Object%1065547485
      //	Back end object method of the channel. Is called when an
      //	object arrives at the back end of the channel.
      void Object (cTransientObject *object);

      //## Operation: Size%1124211834
      virtual ULONG_T Size ();

      //## Operation: Fill%1124211835
      virtual ULONG_T Fill ();

      //## Operation: PrintChannels%1123319920
      static void PrintChannels ();

      //## Operation: GetChannel%1124212412
      static cChannel * GetChannel (ULONG_T index);

      //## Operation: GetChannelCount%1124212413
      static ULONG_T GetChannelCount ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Bridge%3FF9710F0167
      cChannel * get_Bridge () const;
      void set_Bridge (cChannel * value);

      //## Attribute: Fill%42F485D7030D
      ULONG_T get_Fill () const;
      void set_Fill (ULONG_T value);

    // Data Members for Class Attributes

      //## Attribute: ChannelVector%42F4837601D4
      //## begin cChannel::ChannelVector%42F4837601D4.attr preserve=no  public: static CHANNEL_VECTOR_T {U} 
      static CHANNEL_VECTOR_T _ChannelVector;
      //## end cChannel::ChannelVector%42F4837601D4.attr

  public:
    // Additional Public Declarations
      //## begin cChannel%3F82F311037A.public preserve=yes
      //## end cChannel%3F82F311037A.public

  protected:

    //## Other Operations (specified)
      //## Operation: Emit%1069152409
      //	Emit emits an object.
      void Emit (cTransientObject *object);

    // Data Members for Class Attributes

      //## begin cChannel::Bridge%3FF9710F0167.attr preserve=no  public: cChannel * {U} NULL
      cChannel *_Bridge;
      //## end cChannel::Bridge%3FF9710F0167.attr

      //## Attribute: Listening%3F856409038A
      //## begin cChannel::Listening%3F856409038A.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Listening;
      //## end cChannel::Listening%3F856409038A.attr

      //## Attribute: Adapters%3F82F5B103D8
      //## begin cChannel::Adapters%3F82F5B103D8.attr preserve=no  protected: CHANNEL_ADAPTER_LIST_T {U} 
      CHANNEL_ADAPTER_LIST_T _Adapters;
      //## end cChannel::Adapters%3F82F5B103D8.attr

      //## Attribute: Channels%3FFE7A70005D
      //## begin cChannel::Channels%3FFE7A70005D.attr preserve=no  protected: CHANNEL_LIST_T {U} 
      CHANNEL_LIST_T _Channels;
      //## end cChannel::Channels%3FFE7A70005D.attr

      //## begin cChannel::Fill%42F485D7030D.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Fill;
      //## end cChannel::Fill%42F485D7030D.attr

    // Additional Protected Declarations
      //## begin cChannel%3F82F311037A.protected preserve=yes
      //## end cChannel%3F82F311037A.protected

  private:
    // Additional Private Declarations
      //## begin cChannel%3F82F311037A.private preserve=yes
      //## end cChannel%3F82F311037A.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: AddChannel%1123319921
      void AddChannel ();

    // Data Members for Class Attributes

      //## Attribute: ChannelVectorMutex%42F4830F02BF
      //## begin cChannel::ChannelVectorMutex%42F4830F02BF.attr preserve=no  protected: static cMutexSem {U} 
      static cMutexSem _ChannelVectorMutex;
      //## end cChannel::ChannelVectorMutex%42F4830F02BF.attr

      //## Attribute: ChannelVectorIndex%42F4837601E4
      //## begin cChannel::ChannelVectorIndex%42F4837601E4.attr preserve=no  protected: static ULONG_T {U} 0
      static ULONG_T _ChannelVectorIndex;
      //## end cChannel::ChannelVectorIndex%42F4837601E4.attr

    // Additional Implementation Declarations
      //## begin cChannel%3F82F311037A.implementation preserve=yes
      //## end cChannel%3F82F311037A.implementation

};

//## begin cChannel%3F82F311037A.postscript preserve=yes
//## end cChannel%3F82F311037A.postscript

// Class cChannel 

//## begin module%3F82F311037A.epilog preserve=yes
//## end module%3F82F311037A.epilog


#endif
