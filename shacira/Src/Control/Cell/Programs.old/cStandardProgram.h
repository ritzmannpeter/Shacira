//## begin module%3AB6251201D9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AB6251201D9.cm

//## begin module%3AB6251201D9.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3AB6251201D9.cp

//## Module: cStandardProgram%3AB6251201D9; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cStandardProgram.h

#ifndef cStandardProgram_h
#define cStandardProgram_h 1

//## begin module%3AB6251201D9.includes preserve=yes
//## end module%3AB6251201D9.includes

// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cProgram
#include "Control/Cell/Programs/cProgram.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cCell;

//## begin module%3AB6251201D9.additionalDeclarations preserve=yes
//## end module%3AB6251201D9.additionalDeclarations


//## begin cStandardProgram%3AB6251201D9.preface preserve=yes
//## end cStandardProgram%3AB6251201D9.preface

//## Class: cStandardProgram%3AB6251201D9
//## Category: Control::Cell::Programs%3AB6268F0083
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3AB63157010D;cConfigurationObject { -> }
//## Uses: <unnamed>%3BD7EFCA014A;cCell { -> F}
//## Uses: <unnamed>%3E36D5BB01B9;cContext { -> F}

class __DLL_EXPORT__ cStandardProgram : public cProgram  //## Inherits: <unnamed>%3AB6255A0237
{
  //## begin cStandardProgram%3AB6251201D9.initialDeclarations preserve=yes
  //## end cStandardProgram%3AB6251201D9.initialDeclarations

    //## Constructors (generated)
      cStandardProgram();

      cStandardProgram(const cStandardProgram &right);

    //## Constructors (specified)
      //## Operation: cStandardProgram%985080213
      cStandardProgram (cCell *cell, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cStandardProgram();


    //## Other Operations (specified)
      //## Operation: Start%1047387660
      virtual BOOL_T Start ();

      //## Operation: Stop%1047387661
      virtual BOOL_T Stop ();

      //## Operation: ProcessEvent%1047387662
      virtual void ProcessEvent (cTransientObject *object);

  public:
    // Additional Public Declarations
      //## begin cStandardProgram%3AB6251201D9.public preserve=yes
      //## end cStandardProgram%3AB6251201D9.public

  protected:
    // Additional Protected Declarations
      //## begin cStandardProgram%3AB6251201D9.protected preserve=yes
      //## end cStandardProgram%3AB6251201D9.protected

  private:
    // Additional Private Declarations
      //## begin cStandardProgram%3AB6251201D9.private preserve=yes
      //## end cStandardProgram%3AB6251201D9.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cStandardProgram%3AB6251201D9.implementation preserve=yes
      //## end cStandardProgram%3AB6251201D9.implementation

};

//## begin cStandardProgram%3AB6251201D9.postscript preserve=yes
//## end cStandardProgram%3AB6251201D9.postscript

// Class cStandardProgram 

//## begin module%3AB6251201D9.epilog preserve=yes
//## end module%3AB6251201D9.epilog


#endif
