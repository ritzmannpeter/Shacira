//## begin module%3AC4C3880219.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AC4C3880219.cm

//## begin module%3AC4C3880219.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3AC4C3880219.cp

//## Module: cObjectQueue%3AC4C3880219; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cObjectQueue.h

#ifndef cObjectQueue_h
#define cObjectQueue_h 1

//## begin module%3AC4C3880219.includes preserve=yes
//## end module%3AC4C3880219.includes

// cObjectBuffer
#include "System/Objects/cObjectBuffer.h"

class __DLL_EXPORT__ cTransientObject;

//## begin module%3AC4C3880219.additionalDeclarations preserve=yes
//## end module%3AC4C3880219.additionalDeclarations


//## begin cObjectQueue%3AC4C3880219.preface preserve=yes
//## end cObjectQueue%3AC4C3880219.preface

//## Class: cObjectQueue%3AC4C3880219
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AE48513029A;cTransientObject { -> F}

class __DLL_EXPORT__ cObjectQueue : public cObjectBuffer  //## Inherits: <unnamed>%3AC4C3EB01C1
{
  //## begin cObjectQueue%3AC4C3880219.initialDeclarations preserve=yes
public:
  //## end cObjectQueue%3AC4C3880219.initialDeclarations

    //## Constructors (generated)
      cObjectQueue();

      cObjectQueue(const cObjectQueue &right);

    //## Constructors (specified)
      //## Operation: cObjectQueue%985973979
      cObjectQueue (ULONG_T size, QMode mode = QOverwrite);

    //## Destructor (generated)
      virtual ~cObjectQueue();


    //## Other Operations (specified)
      //## Operation: Add%985973981
      virtual BOOL_T Add (cTransientObject *object);

      //## Operation: GetNext%985973980
      virtual cTransientObject * GetNext (BOOL_T wait = false);

  public:
    // Additional Public Declarations
      //## begin cObjectQueue%3AC4C3880219.public preserve=yes
      //## end cObjectQueue%3AC4C3880219.public

  protected:
    // Additional Protected Declarations
      //## begin cObjectQueue%3AC4C3880219.protected preserve=yes
      //## end cObjectQueue%3AC4C3880219.protected

  private:
    // Additional Private Declarations
      //## begin cObjectQueue%3AC4C3880219.private preserve=yes
      //## end cObjectQueue%3AC4C3880219.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cObjectQueue%3AC4C3880219.implementation preserve=yes
      //## end cObjectQueue%3AC4C3880219.implementation

};

//## begin cObjectQueue%3AC4C3880219.postscript preserve=yes
//## end cObjectQueue%3AC4C3880219.postscript

// Class cObjectQueue 

//## begin module%3AC4C3880219.epilog preserve=yes
//## end module%3AC4C3880219.epilog


#endif
