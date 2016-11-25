//## begin module%3ABF397B02F1.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ABF397B02F1.cm

//## begin module%3ABF397B02F1.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3ABF397B02F1.cp

//## Module: cObjectBuffer%3ABF397B02F1; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cObjectBuffer.h

#ifndef cObjectBuffer_h
#define cObjectBuffer_h 1

//## begin module%3ABF397B02F1.includes preserve=yes
//## end module%3ABF397B02F1.includes

// eb_queue
#include "base/eb_queue.hpp"

class __DLL_EXPORT__ cTransientObject;

//## begin module%3ABF397B02F1.additionalDeclarations preserve=yes

#define QMode cQueueBase::PUT_MODE
#define QBlock cQueueBase::putBlock
#define QIgnore cQueueBase::putIgnore
#define QOverwrite cQueueBase::putOverwrite
#define QError cQueueBase::putError

//## end module%3ABF397B02F1.additionalDeclarations


//## begin cObjectBuffer%3ABF397B02F1.preface preserve=yes
//## end cObjectBuffer%3ABF397B02F1.preface

//## Class: cObjectBuffer%3ABF397B02F1
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3ABF660300D6;cQueue { -> }
//## Uses: <unnamed>%3ABF668E011C;cTransientObject { -> F}

class __DLL_EXPORT__ cObjectBuffer 
{
  //## begin cObjectBuffer%3ABF397B02F1.initialDeclarations preserve=yes
public:
  //## end cObjectBuffer%3ABF397B02F1.initialDeclarations

    //## Constructors (generated)
      cObjectBuffer();

      cObjectBuffer(const cObjectBuffer &right);

    //## Constructors (specified)
      //## Operation: cObjectBuffer%985610909
      cObjectBuffer (ULONG_T size, QMode mode = QBlock);

    //## Destructor (generated)
      virtual ~cObjectBuffer();


    //## Other Operations (specified)
      //## Operation: Add%985610910
      virtual BOOL_T Add (cTransientObject *object);

      //## Operation: GetNext%985610911
      virtual cTransientObject * GetNext (BOOL_T wait = false);

      //## Operation: Size%985610912
      ULONG_T Size () const;

      //## Operation: Elements%985610923
      ULONG_T Elements () const;

      //## Operation: IsFull%985610913
      BOOL_T IsFull () const;

      //## Operation: IsEmpty%985610914
      BOOL_T IsEmpty () const;

  public:
    // Additional Public Declarations
      //## begin cObjectBuffer%3ABF397B02F1.public preserve=yes
      //## end cObjectBuffer%3ABF397B02F1.public

  protected:
    // Additional Protected Declarations
      //## begin cObjectBuffer%3ABF397B02F1.protected preserve=yes
      //## end cObjectBuffer%3ABF397B02F1.protected

  private:
    // Additional Private Declarations
      //## begin cObjectBuffer%3ABF397B02F1.private preserve=yes
      //## end cObjectBuffer%3ABF397B02F1.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Queue%3ABF66160264
      //## begin cObjectBuffer::Queue%3ABF66160264.attr preserve=no  private: cQueue<cTransientObject*> {U} 
      cQueue<cTransientObject*> _Queue;
      //## end cObjectBuffer::Queue%3ABF66160264.attr

    // Additional Implementation Declarations
      //## begin cObjectBuffer%3ABF397B02F1.implementation preserve=yes
      //## end cObjectBuffer%3ABF397B02F1.implementation

};

//## begin cObjectBuffer%3ABF397B02F1.postscript preserve=yes
//## end cObjectBuffer%3ABF397B02F1.postscript

// Class cObjectBuffer 

//## begin module%3ABF397B02F1.epilog preserve=yes
//## end module%3ABF397B02F1.epilog


#endif
