//## begin module%3B9C9E1602A9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9C9E1602A9.cm

//## begin module%3B9C9E1602A9.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9C9E1602A9.cp

//## Module: cFX25File%3B9C9E1602A9; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFX25File.h

#ifndef cFX25File_h
#define cFX25File_h 1

//## begin module%3B9C9E1602A9.includes preserve=yes
//## end module%3B9C9E1602A9.includes

// cError
#include "System/cError.h"
// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B9C9E1602A9.additionalDeclarations preserve=yes
//## end module%3B9C9E1602A9.additionalDeclarations


//## begin cFX25File%3B9C9E1602A9.preface preserve=yes
//## end cFX25File%3B9C9E1602A9.preface

//## Class: cFX25File%3B9C9E1602A9
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B9CA1570243;cError { -> }

class __DLL_EXPORT__ cFX25File : public cToolFile  //## Inherits: <unnamed>%3B9C9E27013B
{
  //## begin cFX25File%3B9C9E1602A9.initialDeclarations preserve=yes
  //## end cFX25File%3B9C9E1602A9.initialDeclarations

    //## Constructors (generated)
      cFX25File();

      cFX25File(const cFX25File &right);

    //## Constructors (specified)
      //## Operation: cFX25File%1000119069
      cFX25File (CONST_STRING_T name, cFileSystem *file_system = NULL);

    //## Destructor (generated)
      virtual ~cFX25File();


    //## Other Operations (specified)
      //## Operation: Save%1062507899
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cFX25File%3B9C9E1602A9.public preserve=yes
      //## end cFX25File%3B9C9E1602A9.public

  protected:
    // Additional Protected Declarations
      //## begin cFX25File%3B9C9E1602A9.protected preserve=yes
      //## end cFX25File%3B9C9E1602A9.protected

  private:
    // Additional Private Declarations
      //## begin cFX25File%3B9C9E1602A9.private preserve=yes
      //## end cFX25File%3B9C9E1602A9.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ComputeAddress%1001057896
      LONG_T ComputeAddress (CONST_STRING_T spec);

    // Additional Implementation Declarations
      //## begin cFX25File%3B9C9E1602A9.implementation preserve=yes
      //## end cFX25File%3B9C9E1602A9.implementation

};

//## begin cFX25File%3B9C9E1602A9.postscript preserve=yes
//## end cFX25File%3B9C9E1602A9.postscript

// Class cFX25File 

//## begin module%3B9C9E1602A9.epilog preserve=yes
//## end module%3B9C9E1602A9.epilog


#endif
