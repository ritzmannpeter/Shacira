//## begin module%4039DEBE033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4039DEBE033C.cm

//## begin module%4039DEBE033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4039DEBE033C.cp

//## Module: cPersistenceChannel%4039DEBE033C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cPersistenceChannel.h

#ifndef cPersistenceChannel_h
#define cPersistenceChannel_h 1

//## begin module%4039DEBE033C.includes preserve=yes
//## end module%4039DEBE033C.includes

// cLocalChannel
#include "System/Channel/cLocalChannel.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cPersistenceManager;

//## begin module%4039DEBE033C.additionalDeclarations preserve=yes
//## end module%4039DEBE033C.additionalDeclarations


//## begin cPersistenceChannel%4039DEBE033C.preface preserve=yes
//## end cPersistenceChannel%4039DEBE033C.preface

//## Class: cPersistenceChannel%4039DEBE033C
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4039F2EC02CE;cContext { -> F}

class __DLL_EXPORT__ cPersistenceChannel : public cLocalChannel  //## Inherits: <unnamed>%4039DF220222
{
  //## begin cPersistenceChannel%4039DEBE033C.initialDeclarations preserve=yes
public:
  //## end cPersistenceChannel%4039DEBE033C.initialDeclarations

    //## Constructors (generated)
      cPersistenceChannel();

      cPersistenceChannel(const cPersistenceChannel &right);

    //## Constructors (specified)
      //## Operation: cPersistenceChannel%1077539617
      cPersistenceChannel (cContext *context);

    //## Destructor (generated)
      virtual ~cPersistenceChannel();


    //## Other Operations (specified)
      //## Operation: DataInitialized%1085497636
      BOOL_T DataInitialized ();

  public:
    // Additional Public Declarations
      //## begin cPersistenceChannel%4039DEBE033C.public preserve=yes
      void Clear();
      cPersistenceManager * PersistenceManager() const {return _PersistenceManager;};
      //## end cPersistenceChannel%4039DEBE033C.public

  protected:
    // Data Members for Associations

      //## Association: Control::LocalDatabase::<unnamed>%4039E1CC035B
      //## Role: cPersistenceChannel::PersistenceManager%4039E1CE01E4
      //## begin cPersistenceChannel::PersistenceManager%4039E1CE01E4.role preserve=no  public: cPersistenceManager { -> 1RFHN}
      cPersistenceManager *_PersistenceManager;
      //## end cPersistenceChannel::PersistenceManager%4039E1CE01E4.role

    // Additional Protected Declarations
      //## begin cPersistenceChannel%4039DEBE033C.protected preserve=yes
      //## end cPersistenceChannel%4039DEBE033C.protected

  private:
    // Additional Private Declarations
      //## begin cPersistenceChannel%4039DEBE033C.private preserve=yes
      //## end cPersistenceChannel%4039DEBE033C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cPersistenceChannel%4039DEBE033C.implementation preserve=yes
      //## end cPersistenceChannel%4039DEBE033C.implementation

};

//## begin cPersistenceChannel%4039DEBE033C.postscript preserve=yes
//## end cPersistenceChannel%4039DEBE033C.postscript

// Class cPersistenceChannel 

//## begin module%4039DEBE033C.epilog preserve=yes
//## end module%4039DEBE033C.epilog


#endif
