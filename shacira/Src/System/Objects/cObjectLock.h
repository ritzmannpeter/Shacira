//## begin module%3A4B09E700B1.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A4B09E700B1.cm

//## begin module%3A4B09E700B1.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A4B09E700B1.cp

//## Module: cObjectLock%3A4B09E700B1; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cObjectLock.h

#ifndef cObjectLock_h
#define cObjectLock_h 1

//## begin module%3A4B09E700B1.includes preserve=yes
//## end module%3A4B09E700B1.includes

// eb_sema
#include "base/eb_sema.hpp"
//## begin module%3A4B09E700B1.additionalDeclarations preserve=yes
//## end module%3A4B09E700B1.additionalDeclarations


//## begin cObjectLock%3A4B09E700B1.preface preserve=yes
//## end cObjectLock%3A4B09E700B1.preface

//## Class: cObjectLock%3A4B09E700B1
//	This class supplies a lock mechanism, that locks objects
//	while the object lock is living (the object lock exists).
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DC900FB00A6;cMutexSem { -> }

class __DLL_EXPORT__ cObjectLock 
{
  //## begin cObjectLock%3A4B09E700B1.initialDeclarations preserve=yes
public:
  //## end cObjectLock%3A4B09E700B1.initialDeclarations

    //## Constructors (generated)
      cObjectLock();

      cObjectLock(const cObjectLock &right);

    //## Constructors (specified)
      //## Operation: cObjectLock%977993517
      cObjectLock (cMutexSem *mutex, CONST_STRING_T file = NULL, INT_T line = 0);

    //## Destructor (generated)
      virtual ~cObjectLock();

  public:
    // Additional Public Declarations
      //## begin cObjectLock%3A4B09E700B1.public preserve=yes
      //## end cObjectLock%3A4B09E700B1.public

  protected:
    // Additional Protected Declarations
      //## begin cObjectLock%3A4B09E700B1.protected preserve=yes
      //## end cObjectLock%3A4B09E700B1.protected

  private:
    // Additional Private Declarations
      //## begin cObjectLock%3A4B09E700B1.private preserve=yes
      //## end cObjectLock%3A4B09E700B1.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: Mutex%3DC9122F01B7
      //## begin cObjectLock::Mutex%3DC9122F01B7.attr preserve=no  implementation: cMutexSem * {U} NULL
      cMutexSem *_Mutex;
      //## end cObjectLock::Mutex%3DC9122F01B7.attr

    // Additional Implementation Declarations
      //## begin cObjectLock%3A4B09E700B1.implementation preserve=yes
      //## end cObjectLock%3A4B09E700B1.implementation

};

//## begin cObjectLock%3A4B09E700B1.postscript preserve=yes
//## end cObjectLock%3A4B09E700B1.postscript

// Class cObjectLock 

//## begin module%3A4B09E700B1.epilog preserve=yes
// #define __LOCK__(mutex_ptr)   cObjectLock __lock__(mutex_ptr, __FILE__, __LINE__, #mutex_ptr);
// #define __NAMED_LOCK__(name, mutex_ptr)   cObjectLock Lock_##name(mutex_ptr, __FILE__, __LINE__, #mutex_ptr);
#define __LOCK__(mutex_ptr)   cObjectLock __lock__(mutex_ptr, __FILE__, __LINE__);
#define __NAMED_LOCK__(name, mutex_ptr)   cObjectLock Lock_##name(mutex_ptr, __FILE__, __LINE__);
//## end module%3A4B09E700B1.epilog


#endif
