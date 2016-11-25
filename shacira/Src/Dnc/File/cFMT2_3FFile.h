//## begin module%3B9CE61F0396.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9CE61F0396.cm

//## begin module%3B9CE61F0396.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9CE61F0396.cp

//## Module: cFMT2_3FFile%3B9CE61F0396; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMT2_3FFile.h

#ifndef cFMT2_3FFile_h
#define cFMT2_3FFile_h 1

//## begin module%3B9CE61F0396.includes preserve=yes
//## end module%3B9CE61F0396.includes

// cError
#include "System/cError.h"
// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B9CE61F0396.additionalDeclarations preserve=yes
//## end module%3B9CE61F0396.additionalDeclarations


//## begin cFMT2_3FFile%3B9CE61F0396.preface preserve=yes
//## end cFMT2_3FFile%3B9CE61F0396.preface

//## Class: cFMT2_3FFile%3B9CE61F0396
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BA62F32013E;cError { -> }

class __DLL_EXPORT__ cFMT2_3FFile : public cToolFile  //## Inherits: <unnamed>%3B9CE63D00BE
{
  //## begin cFMT2_3FFile%3B9CE61F0396.initialDeclarations preserve=yes
  //## end cFMT2_3FFile%3B9CE61F0396.initialDeclarations

    //## Constructors (generated)
      cFMT2_3FFile();

      cFMT2_3FFile(const cFMT2_3FFile &right);

    //## Constructors (specified)
      //## Operation: cFMT2_3FFile%1000119071
      cFMT2_3FFile (CONST_STRING_T name, cFileSystem *file_system);

    //## Destructor (generated)
      virtual ~cFMT2_3FFile();


    //## Other Operations (specified)
      //## Operation: Save%1062507896
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cFMT2_3FFile%3B9CE61F0396.public preserve=yes
      //## end cFMT2_3FFile%3B9CE61F0396.public

  protected:
    // Additional Protected Declarations
      //## begin cFMT2_3FFile%3B9CE61F0396.protected preserve=yes
      //## end cFMT2_3FFile%3B9CE61F0396.protected

  private:
    // Additional Private Declarations
      //## begin cFMT2_3FFile%3B9CE61F0396.private preserve=yes
      //## end cFMT2_3FFile%3B9CE61F0396.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: DINT2Long%1000724935
      LONG_T DINT2Long (LONG_T value);

      //## Operation: ComputeAddress%1001057893
      LONG_T ComputeAddress (CONST_STRING_T spec);

    // Additional Implementation Declarations
      //## begin cFMT2_3FFile%3B9CE61F0396.implementation preserve=yes
      //## end cFMT2_3FFile%3B9CE61F0396.implementation

};

//## begin cFMT2_3FFile%3B9CE61F0396.postscript preserve=yes
//## end cFMT2_3FFile%3B9CE61F0396.postscript

// Class cFMT2_3FFile 

//## begin module%3B9CE61F0396.epilog preserve=yes
//## end module%3B9CE61F0396.epilog


#endif
