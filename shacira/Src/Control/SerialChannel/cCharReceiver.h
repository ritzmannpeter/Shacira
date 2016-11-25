//## begin module%3C3440B80004.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C3440B80004.cm

//## begin module%3C3440B80004.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C3440B80004.cp

//## Module: cCharReceiver%3C3440B80004; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\SerialChannel\cCharReceiver.h

#ifndef cCharReceiver_h
#define cCharReceiver_h 1

//## begin module%3C3440B80004.includes preserve=yes
//## end module%3C3440B80004.includes


class __DLL_EXPORT__ cCharRingBuffer;

//## begin module%3C3440B80004.additionalDeclarations preserve=yes
//## end module%3C3440B80004.additionalDeclarations


//## begin cCharReceiver%3C3440B80004.preface preserve=yes
//## end cCharReceiver%3C3440B80004.preface

//## Class: cCharReceiver%3C3440B80004
//## Category: Control::SerialChannel%3789DE6A02A9
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCharReceiver 
{
  //## begin cCharReceiver%3C3440B80004.initialDeclarations preserve=yes
public:
  //## end cCharReceiver%3C3440B80004.initialDeclarations

    //## Constructors (generated)
      cCharReceiver();

      cCharReceiver(const cCharReceiver &right);

    //## Destructor (generated)
      virtual ~cCharReceiver();


    //## Other Operations (specified)
      //## Operation: Get%1010053287
      virtual LONG_T Get (STRING_BUF_T buffer, ULONG_T amount, ULONG_T timeout) = 0;

      //## Operation: Flush%1010131287
      virtual void Flush () = 0;

  public:
    // Additional Public Declarations
      //## begin cCharReceiver%3C3440B80004.public preserve=yes
      //## end cCharReceiver%3C3440B80004.public

  protected:
    // Data Members for Associations

      //## Association: Control::SerialChannel::<unnamed>%3C34901401D3
      //## Role: cCharReceiver::RingBuffer%3C3490150117
      //## begin cCharReceiver::RingBuffer%3C3490150117.role preserve=no  public: cCharRingBuffer { -> 1RFHN}
      cCharRingBuffer *_RingBuffer;
      //## end cCharReceiver::RingBuffer%3C3490150117.role

    // Additional Protected Declarations
      //## begin cCharReceiver%3C3440B80004.protected preserve=yes
      //## end cCharReceiver%3C3440B80004.protected

  private:
    // Additional Private Declarations
      //## begin cCharReceiver%3C3440B80004.private preserve=yes
      //## end cCharReceiver%3C3440B80004.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCharReceiver%3C3440B80004.implementation preserve=yes
      //## end cCharReceiver%3C3440B80004.implementation

};

//## begin cCharReceiver%3C3440B80004.postscript preserve=yes
//## end cCharReceiver%3C3440B80004.postscript

// Class cCharReceiver 

//## begin module%3C3440B80004.epilog preserve=yes
//## end module%3C3440B80004.epilog


#endif
