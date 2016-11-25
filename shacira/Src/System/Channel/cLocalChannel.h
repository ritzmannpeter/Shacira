//## begin module%3F82FE2F0157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F82FE2F0157.cm

//## begin module%3F82FE2F0157.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F82FE2F0157.cp

//## Module: cLocalChannel%3F82FE2F0157; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cLocalChannel.h

#ifndef cLocalChannel_h
#define cLocalChannel_h 1

//## begin module%3F82FE2F0157.includes preserve=yes
//## end module%3F82FE2F0157.includes

// cChannel
#include "System/Channel/cChannel.h"

class cMsgBox;
class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cAdapter;

//## begin module%3F82FE2F0157.additionalDeclarations preserve=yes

typedef struct
{
	INT_T msg_id;
	cTransientObject * object;
}	AsyncMessage;

#define MSG_ID_TERMINATE		-1
#define MSG_ID_OBJECT			1

//## end module%3F82FE2F0157.additionalDeclarations


//## begin cLocalChannel%3F82FE2F0157.preface preserve=yes
//## end cLocalChannel%3F82FE2F0157.preface

//## Class: cLocalChannel%3F82FE2F0157
//## Category: System::Channel%3F82F2E2001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F83059F038A;cTransientObject { -> F}
//## Uses: <unnamed>%3F8306AD034B;cAdapter { -> F}

class __DLL_EXPORT__ cLocalChannel : public cChannel  //## Inherits: <unnamed>%3F82FEA2037A
{
  //## begin cLocalChannel%3F82FE2F0157.initialDeclarations preserve=yes
public:
  //## end cLocalChannel%3F82FE2F0157.initialDeclarations

    //## Constructors (generated)
      cLocalChannel();

      cLocalChannel(const cLocalChannel &right);

    //## Constructors (specified)
      //## Operation: cLocalChannel%1065547486
      cLocalChannel (CONST_STRING_T channel_name);

    //## Destructor (generated)
      virtual ~cLocalChannel();


    //## Other Operations (specified)
      //## Operation: Start%1072724216
      virtual void Start ();

      //## Operation: Stop%1072724217
      virtual void Stop ();

      //## Operation: ObjectGetParam%1075904923
      virtual BOOL_T ObjectGetParam (CONST_STRING_T name, STRING_T &value);

      //## Operation: ObjectSetParam%1075904924
      virtual BOOL_T ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value);

      //## Operation: MainFunc%1065547489
      virtual INT_T MainFunc (void *extra);

      //## Operation: Listen%1065703995
      virtual void Listen ();

      //## Operation: StopListen%1065629499
      virtual void StopListen ();

      //## Operation: Send%1065547487
      //	Method to send an object to (into) the front end of the
      //	channel
      virtual void Send (cTransientObject *object);

      //## Operation: Size%1124211832
      virtual ULONG_T Size ();

    // Data Members for Class Attributes

      //## Attribute: Size%42D22FA401E4
      //## begin cLocalChannel::Size%42D22FA401E4.attr preserve=no  public: static ULONG_T {U} 0x4000
      static ULONG_T _Size;
      //## end cLocalChannel::Size%42D22FA401E4.attr

  public:
    // Additional Public Declarations
      //## begin cLocalChannel%3F82FE2F0157.public preserve=yes
      //## end cLocalChannel%3F82FE2F0157.public

  protected:
    // Data Members for Associations

      //## Association: System::Channel::<unnamed>%3F8301E3029F
      //## Role: cLocalChannel::MsgBox%3F8301E400EA
      //## begin cLocalChannel::MsgBox%3F8301E400EA.role preserve=no  public: cMsgBox { -> 1RFHN}
      cMsgBox *_MsgBox;
      //## end cLocalChannel::MsgBox%3F8301E400EA.role

    // Additional Protected Declarations
      //## begin cLocalChannel%3F82FE2F0157.protected preserve=yes
      //## end cLocalChannel%3F82FE2F0157.protected

  private:
    // Additional Private Declarations
      //## begin cLocalChannel%3F82FE2F0157.private preserve=yes
      //## end cLocalChannel%3F82FE2F0157.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: SendMutex%43099E1A035B
      //## begin cLocalChannel::SendMutex%43099E1A035B.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _SendMutex;
      //## end cLocalChannel::SendMutex%43099E1A035B.attr

    // Additional Implementation Declarations
      //## begin cLocalChannel%3F82FE2F0157.implementation preserve=yes
      //## end cLocalChannel%3F82FE2F0157.implementation

};

//## begin cLocalChannel%3F82FE2F0157.postscript preserve=yes
//## end cLocalChannel%3F82FE2F0157.postscript

// Class cLocalChannel 

//## begin module%3F82FE2F0157.epilog preserve=yes
//## end module%3F82FE2F0157.epilog


#endif
