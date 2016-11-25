//## begin module%4105571B0128.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4105571B0128.cm

//## begin module%4105571B0128.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4105571B0128.cp

//## Module: cBlockQueue%4105571B0128; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cBlockQueue.h

#ifndef cBlockQueue_h
#define cBlockQueue_h 1

//## begin module%4105571B0128.includes preserve=yes
//## end module%4105571B0128.includes

// eb_queue
#include "base/eb_queue.hpp"
// eb_sema
#include "base/eb_sema.hpp"
//## begin module%4105571B0128.additionalDeclarations preserve=yes

typedef struct {
   PTR_T block;
   ULONG_T block_size;
}  BLOCK_T;

#define BLOCK_QUEUE_SIZE   100

//## end module%4105571B0128.additionalDeclarations


//## begin cBlockQueue%4105571B0128.preface preserve=yes
//## end cBlockQueue%4105571B0128.preface

//## Class: cBlockQueue%4105571B0128
//## Category: System::ClientServer%410273FC034B
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4105597B0261;cEventSem { -> }
//## Uses: <unnamed>%4105FBA9003E;cQueue { -> }

class __DLL_EXPORT__ cBlockQueue 
{
  //## begin cBlockQueue%4105571B0128.initialDeclarations preserve=yes
public:
  //## end cBlockQueue%4105571B0128.initialDeclarations

    //## Constructors (generated)
      cBlockQueue();

      cBlockQueue(const cBlockQueue &right);

    //## Constructors (specified)
      //## Operation: cBlockQueue%1090868764
      cBlockQueue (LONG_T channel);

    //## Destructor (generated)
      virtual ~cBlockQueue();


    //## Other Operations (specified)
      //## Operation: GetBlock%1090868765
      BLOCK_T * GetBlock (ULONG_T tmo);

      //## Operation: Flush%1090946394
      void Flush ();

      //## Operation: SetBlock%1090868766
      void SetBlock (PTR_T block, ULONG_T block_size);

      //## Operation: ReleaseBlock%1090910860
      void ReleaseBlock (BLOCK_T *block);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Channel%41055773034B
      ULONG_T get_Channel () const;

  public:
    // Additional Public Declarations
      //## begin cBlockQueue%4105571B0128.public preserve=yes
      //## end cBlockQueue%4105571B0128.public

  protected:
    // Data Members for Class Attributes

      //## begin cBlockQueue::Channel%41055773034B.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Channel;
      //## end cBlockQueue::Channel%41055773034B.attr

    // Additional Protected Declarations
      //## begin cBlockQueue%4105571B0128.protected preserve=yes
      //## end cBlockQueue%4105571B0128.protected

  private:
    // Additional Private Declarations
      //## begin cBlockQueue%4105571B0128.private preserve=yes
      //## end cBlockQueue%4105571B0128.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: CreateBlock%1090910858
      BLOCK_T * CreateBlock (PTR_T block, ULONG_T block_size);

      //## Operation: DeleteBlock%1090910859
      void DeleteBlock (BLOCK_T *block);

    // Data Members for Class Attributes

      //## Attribute: Event%4105598902DE
      //## begin cBlockQueue::Event%4105598902DE.attr preserve=no  implementation: cEventSem {U} 
      cEventSem _Event;
      //## end cBlockQueue::Event%4105598902DE.attr

      //## Attribute: Mutex%41055C7901A5
      //## begin cBlockQueue::Mutex%41055C7901A5.attr preserve=no  implementation: cMutexSem {U} 
      cMutexSem _Mutex;
      //## end cBlockQueue::Mutex%41055C7901A5.attr

      //## Attribute: Queue%4105FBF003B9
      //## begin cBlockQueue::Queue%4105FBF003B9.attr preserve=no  implementation: cQueue<BLOCK_T*> {U} 
      cQueue<BLOCK_T*> _Queue;
      //## end cBlockQueue::Queue%4105FBF003B9.attr

    // Additional Implementation Declarations
      //## begin cBlockQueue%4105571B0128.implementation preserve=yes
      //## end cBlockQueue%4105571B0128.implementation

};

//## begin cBlockQueue%4105571B0128.postscript preserve=yes
//## end cBlockQueue%4105571B0128.postscript

// Class cBlockQueue 

//## begin module%4105571B0128.epilog preserve=yes
//## end module%4105571B0128.epilog


#endif
