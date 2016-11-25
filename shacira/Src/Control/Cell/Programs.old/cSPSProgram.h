//## begin module%3D21E86F000D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D21E86F000D.cm

//## begin module%3D21E86F000D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3D21E86F000D.cp

//## Module: cSPSProgram%3D21E86F000D; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Control\Cell\Programs\cSPSProgram.h

#ifndef cSPSProgram_h
#define cSPSProgram_h 1

//## begin module%3D21E86F000D.includes preserve=yes
//## end module%3D21E86F000D.includes

// cProgram
#include "Control/Cell/Programs/cProgram.h"

class cConfigurationObject;
class cCell;

//## begin module%3D21E86F000D.additionalDeclarations preserve=yes
//## end module%3D21E86F000D.additionalDeclarations


//## begin cSPSProgram%3D21E86F000D.preface preserve=yes
//## end cSPSProgram%3D21E86F000D.preface

//## Class: cSPSProgram%3D21E86F000D
//## Category: Control::Cell::Programs%3AB6268F0083
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3D21E9A3015A;cCell { -> F}
//## Uses: <unnamed>%3D22D06B0298;cConfigurationObject { -> F}
//## Uses: <unnamed>%3D22D417013B; { -> F}
//## Uses: <unnamed>%3D22D41F0309; { -> F}

class cSPSProgram : public cProgram  //## Inherits: <unnamed>%3D21E8D600A1
{
  //## begin cSPSProgram%3D21E86F000D.initialDeclarations preserve=yes
  //## end cSPSProgram%3D21E86F000D.initialDeclarations

  public:
    //## Constructors (generated)
      cSPSProgram();

      cSPSProgram(const cSPSProgram &right);

    //## Constructors (specified)
      //## Operation: cSPSProgram%1025618961
      cSPSProgram (cCell *cell, cConfigurationObject *config_obj);

    //## Destructor (generated)
      virtual ~cSPSProgram();


    //## Other Operations (specified)
      //## Operation: Start%1047387666
      virtual BOOL_T Start ();

      //## Operation: Stop%1047387667
      virtual BOOL_T Stop ();

      //## Operation: ProcessEvent%1047387668
      virtual void ProcessEvent (cTransientObject *object);

    //## Get and Set Operations for Associations (generated)


    // Additional Public Declarations
      //## begin cSPSProgram%3D21E86F000D.public preserve=yes
      //## end cSPSProgram%3D21E86F000D.public

  protected:
    // Data Members for Associations


    // Additional Protected Declarations
      //## begin cSPSProgram%3D21E86F000D.protected preserve=yes
      //## end cSPSProgram%3D21E86F000D.protected

  private:
    // Additional Private Declarations
      //## begin cSPSProgram%3D21E86F000D.private preserve=yes
      //## end cSPSProgram%3D21E86F000D.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cSPSProgram%3D21E86F000D.implementation preserve=yes
      //## end cSPSProgram%3D21E86F000D.implementation

};

//## begin cSPSProgram%3D21E86F000D.postscript preserve=yes
//## end cSPSProgram%3D21E86F000D.postscript

// Class cSPSProgram 

//## begin module%3D21E86F000D.epilog preserve=yes
//## end module%3D21E86F000D.epilog


#endif
