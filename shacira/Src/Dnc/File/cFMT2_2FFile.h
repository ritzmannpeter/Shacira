//## begin module%3B9CE6040134.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9CE6040134.cm

//## begin module%3B9CE6040134.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9CE6040134.cp

//## Module: cFMT2_2FFile%3B9CE6040134; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMT2_2FFile.h

#ifndef cFMT2_2FFile_h
#define cFMT2_2FFile_h 1

//## begin module%3B9CE6040134.includes preserve=yes
//## end module%3B9CE6040134.includes

// cError
#include "System/cError.h"
// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B9CE6040134.additionalDeclarations preserve=yes
//## end module%3B9CE6040134.additionalDeclarations


//## begin cFMT2_2FFile%3B9CE6040134.preface preserve=yes
//## end cFMT2_2FFile%3B9CE6040134.preface

//## Class: cFMT2_2FFile%3B9CE6040134
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BA62F400062;cError { -> }

class __DLL_EXPORT__ cFMT2_2FFile : public cToolFile  //## Inherits: <unnamed>%3B9CE639011D
{
  //## begin cFMT2_2FFile%3B9CE6040134.initialDeclarations preserve=yes
  //## end cFMT2_2FFile%3B9CE6040134.initialDeclarations

    //## Constructors (generated)
      cFMT2_2FFile();

      cFMT2_2FFile(const cFMT2_2FFile &right);

    //## Constructors (specified)
      //## Operation: cFMT2_2FFile%1000119074
      cFMT2_2FFile (CONST_STRING_T name, cFileSystem *file_system = NULL);

    //## Destructor (generated)
      virtual ~cFMT2_2FFile();


    //## Other Operations (specified)
      //## Operation: Save%1062507897
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cFMT2_2FFile%3B9CE6040134.public preserve=yes
      //## end cFMT2_2FFile%3B9CE6040134.public

  protected:
    // Additional Protected Declarations
      //## begin cFMT2_2FFile%3B9CE6040134.protected preserve=yes
      //## end cFMT2_2FFile%3B9CE6040134.protected

  private:
    // Additional Private Declarations
      //## begin cFMT2_2FFile%3B9CE6040134.private preserve=yes
      //## end cFMT2_2FFile%3B9CE6040134.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: DINT2Long%1000724936
      LONG_T DINT2Long (LONG_T value);

      //## Operation: ComputeAddress%1001057894
      LONG_T ComputeAddress (CONST_STRING_T spec);

    // Additional Implementation Declarations
      //## begin cFMT2_2FFile%3B9CE6040134.implementation preserve=yes
      //## end cFMT2_2FFile%3B9CE6040134.implementation

};

//## begin cFMT2_2FFile%3B9CE6040134.postscript preserve=yes
//## end cFMT2_2FFile%3B9CE6040134.postscript

// Class cFMT2_2FFile 

//## begin module%3B9CE6040134.epilog preserve=yes
//## end module%3B9CE6040134.epilog


#endif
