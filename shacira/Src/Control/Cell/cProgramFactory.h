//## begin module%3FE7501801C5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FE7501801C5.cm

//## begin module%3FE7501801C5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FE7501801C5.cp

//## Module: cProgramFactory%3FE7501801C5; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Cell\cProgramFactory.h

#ifndef cProgramFactory_h
#define cProgramFactory_h 1

//## begin module%3FE7501801C5.includes preserve=yes
//## end module%3FE7501801C5.includes

// cCustomFunctions
#include "System/cCustomFunctions.h"
// cGateway
#include "Control/Cell/cGateway.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cProgram;
class __DLL_EXPORT__ cCell;
class __DLL_EXPORT__ cEM63Program;

//## begin module%3FE7501801C5.additionalDeclarations preserve=yes
//## end module%3FE7501801C5.additionalDeclarations


//## begin cProgramFactory%3FE7501801C5.preface preserve=yes
//## end cProgramFactory%3FE7501801C5.preface

//## Class: cProgramFactory%3FE7501801C5
//## Category: Control::Cell%3A7EAD1F0170
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FE7512E01A5;cContext { -> F}
//## Uses: <unnamed>%3FE7527F0157;cProgram { -> F}
//## Uses: <unnamed>%3FE754310128;cConfigurationObject { -> F}
//## Uses: <unnamed>%407199F102BF;cCell { -> F}
//## Uses: <unnamed>%41E6AB5A035B;cCustomFunctions { -> }
//## Uses: <unnamed>%429C6EAD000F;cGateway { -> }
//## Uses: <unnamed>%43B118A20025;cEM63Program { -> F}

class __DLL_EXPORT__ cProgramFactory 
{
  //## begin cProgramFactory%3FE7501801C5.initialDeclarations preserve=yes
public:
  //## end cProgramFactory%3FE7501801C5.initialDeclarations

    //## Constructors (generated)
      cProgramFactory();

      cProgramFactory(const cProgramFactory &right);

    //## Destructor (generated)
      virtual ~cProgramFactory();


    //## Other Operations (specified)
      //## Operation: CreateProgram%1072120971
      static cProgram * CreateProgram (cConfigurationObject *config_obj, cContext *context);

      //## Operation: CreateExternal%1074705362
      static cProgram * CreateExternal (cConfigurationObject *config_obj, cContext *context);

  public:
    // Additional Public Declarations
      //## begin cProgramFactory%3FE7501801C5.public preserve=yes
      //## end cProgramFactory%3FE7501801C5.public

  protected:
    // Additional Protected Declarations
      //## begin cProgramFactory%3FE7501801C5.protected preserve=yes
      //## end cProgramFactory%3FE7501801C5.protected

  private:
    // Additional Private Declarations
      //## begin cProgramFactory%3FE7501801C5.private preserve=yes
      //## end cProgramFactory%3FE7501801C5.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cProgramFactory%3FE7501801C5.implementation preserve=yes
      //## end cProgramFactory%3FE7501801C5.implementation

};

//## begin cProgramFactory%3FE7501801C5.postscript preserve=yes
//## end cProgramFactory%3FE7501801C5.postscript

// Class cProgramFactory 

//## begin module%3FE7501801C5.epilog preserve=yes
//## end module%3FE7501801C5.epilog


#endif
