//## begin module%3DD37DAE031A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DD37DAE031A.cm

//## begin module%3DD37DAE031A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DD37DAE031A.cp

//## Module: cMemoryConsole%3DD37DAE031A; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Console\cMemoryConsole.h

#ifndef cMemoryConsole_h
#define cMemoryConsole_h 1

//## begin module%3DD37DAE031A.includes preserve=yes
//## end module%3DD37DAE031A.includes

// cConsole
#include "System/Console/cConsole.h"

class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cCharRingBuffer;

//## begin module%3DD37DAE031A.additionalDeclarations preserve=yes
//## end module%3DD37DAE031A.additionalDeclarations


//## begin cMemoryConsole%3DD37DAE031A.preface preserve=yes
//## end cMemoryConsole%3DD37DAE031A.preface

//## Class: cMemoryConsole%3DD37DAE031A
//## Category: System::Console%3DC92CF602A4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E3158B00293;cObjectLock { -> F}

class __DLL_EXPORT__ cMemoryConsole : public cConsole  //## Inherits: <unnamed>%3DD37F680026
{
  //## begin cMemoryConsole%3DD37DAE031A.initialDeclarations preserve=yes
public:
  //## end cMemoryConsole%3DD37DAE031A.initialDeclarations

    //## Constructors (generated)
      cMemoryConsole();

      cMemoryConsole(const cMemoryConsole &right);

    //## Constructors (specified)
      //## Operation: cMemoryConsole%1037267672
      cMemoryConsole (ULONG_T buf_size);

    //## Destructor (generated)
      virtual ~cMemoryConsole();


    //## Other Operations (specified)
      //## Operation: Write%1037267673
      virtual void Write (CONST_STRING_T text);

      //## Operation: Read%1037267674
      virtual LONG_T Read (STRING_BUF_T buf, ULONG_T buf_size, ULONG_T timeout = 0);

      //## Operation: FlushInput%1037267675
      virtual void FlushInput ();

      //## Operation: FlushOutput%1037267676
      virtual void FlushOutput ();

  public:
    // Additional Public Declarations
      //## begin cMemoryConsole%3DD37DAE031A.public preserve=yes
      //## end cMemoryConsole%3DD37DAE031A.public

  protected:
    // Data Members for Associations

      //## Association: System::Console::<unnamed>%3DD37FE40255
      //## Role: cMemoryConsole::Buffer%3DD37FE501E9
      //## begin cMemoryConsole::Buffer%3DD37FE501E9.role preserve=no  public: cCharRingBuffer { -> 1RFHN}
      cCharRingBuffer *_Buffer;
      //## end cMemoryConsole::Buffer%3DD37FE501E9.role

    // Additional Protected Declarations
      //## begin cMemoryConsole%3DD37DAE031A.protected preserve=yes
      //## end cMemoryConsole%3DD37DAE031A.protected

  private:
    // Additional Private Declarations
      //## begin cMemoryConsole%3DD37DAE031A.private preserve=yes
      //## end cMemoryConsole%3DD37DAE031A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cMemoryConsole%3DD37DAE031A.implementation preserve=yes
      //## end cMemoryConsole%3DD37DAE031A.implementation

};

//## begin cMemoryConsole%3DD37DAE031A.postscript preserve=yes
//## end cMemoryConsole%3DD37DAE031A.postscript

// Class cMemoryConsole 

//## begin module%3DD37DAE031A.epilog preserve=yes
//## end module%3DD37DAE031A.epilog


#endif
