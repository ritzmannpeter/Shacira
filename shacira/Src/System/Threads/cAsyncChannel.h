//## begin module%3AA34DAE0338.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AA34DAE0338.cm

//## begin module%3AA34DAE0338.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AA34DAE0338.cp

//## Module: cAsyncChannel%3AA34DAE0338; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Threads\cAsyncChannel.h

#ifndef cAsyncChannel_h
#define cAsyncChannel_h 1

//## begin module%3AA34DAE0338.includes preserve=yes
//## end module%3AA34DAE0338.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class cMsgBox;
class __DLL_EXPORT__ cTransientObject;

//## begin module%3AA34DAE0338.additionalDeclarations preserve=yes
//## end module%3AA34DAE0338.additionalDeclarations


//## begin cAsyncChannel%3AA34DAE0338.preface preserve=yes
//## end cAsyncChannel%3AA34DAE0338.preface

//## Class: cAsyncChannel%3AA34DAE0338
//## Category: System::Threads%3DC7FCF00004
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E6F1E7E01F4;cTransientObject { -> F}

class __DLL_EXPORT__ cAsyncChannel : public cControlThread  //## Inherits: <unnamed>%3AA34DD90235
{
  //## begin cAsyncChannel%3AA34DAE0338.initialDeclarations preserve=yes
public:
  //## end cAsyncChannel%3AA34DAE0338.initialDeclarations

    //## Constructors (generated)
      cAsyncChannel();

      cAsyncChannel(const cAsyncChannel &right);

    //## Destructor (generated)
      virtual ~cAsyncChannel();


    //## Other Operations (specified)
      //## Operation: Stop%983778327
      virtual void Stop ();

      //## Operation: MainFunc%983778329
      virtual INT_T MainFunc (void *extra);

      //## Operation: MessageFunc%983778331
      virtual INT_T MessageFunc (cTransientObject *object) = 0;

      //## Operation: Send%983778336
      BOOL_T Send (cTransientObject *object);

  public:
    // Additional Public Declarations
      //## begin cAsyncChannel%3AA34DAE0338.public preserve=yes
      //## end cAsyncChannel%3AA34DAE0338.public

  protected:
    // Data Members for Associations

      //## Association: System::<unnamed>%3AA34E8000A5
      //## Role: cAsyncChannel::ReceiveBox%3AA34E8002CB
      //## begin cAsyncChannel::ReceiveBox%3AA34E8002CB.role preserve=no  public: cMsgBox { -> 1RFHN}
      cMsgBox *_ReceiveBox;
      //## end cAsyncChannel::ReceiveBox%3AA34E8002CB.role

    // Additional Protected Declarations
      //## begin cAsyncChannel%3AA34DAE0338.protected preserve=yes
      //## end cAsyncChannel%3AA34DAE0338.protected

  private:
    // Additional Private Declarations
      //## begin cAsyncChannel%3AA34DAE0338.private preserve=yes
      //## end cAsyncChannel%3AA34DAE0338.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cAsyncChannel%3AA34DAE0338.implementation preserve=yes
      //## end cAsyncChannel%3AA34DAE0338.implementation

};

//## begin cAsyncChannel%3AA34DAE0338.postscript preserve=yes
//## end cAsyncChannel%3AA34DAE0338.postscript

// Class cAsyncChannel 

//## begin module%3AA34DAE0338.epilog preserve=yes
//## end module%3AA34DAE0338.epilog


#endif
