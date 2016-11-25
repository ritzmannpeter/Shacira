//## begin module%3B9C9E450148.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9C9E450148.cm

//## begin module%3B9C9E450148.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9C9E450148.cp

//## Module: cFMT2File%3B9C9E450148; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMT2File.h

#ifndef cFMT2File_h
#define cFMT2File_h 1

//## begin module%3B9C9E450148.includes preserve=yes
//## end module%3B9C9E450148.includes

// cError
#include "System/cError.h"
// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B9C9E450148.additionalDeclarations preserve=yes
//## end module%3B9C9E450148.additionalDeclarations


//## begin cFMT2File%3B9C9E450148.preface preserve=yes
//## end cFMT2File%3B9C9E450148.preface

//## Class: cFMT2File%3B9C9E450148
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B9CA1510009;cError { -> }

class __DLL_EXPORT__ cFMT2File : public cToolFile  //## Inherits: <unnamed>%3B9C9E690385
{
  //## begin cFMT2File%3B9C9E450148.initialDeclarations preserve=yes
  //## end cFMT2File%3B9C9E450148.initialDeclarations

    //## Constructors (generated)
      cFMT2File();

      cFMT2File(const cFMT2File &right);

    //## Constructors (specified)
      //## Operation: cFMT2File%1000119068
      cFMT2File (CONST_STRING_T name, cFileSystem *file_system = NULL);

    //## Destructor (generated)
      virtual ~cFMT2File();


    //## Other Operations (specified)
      //## Operation: Save%1062507898
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cFMT2File%3B9C9E450148.public preserve=yes
      //## end cFMT2File%3B9C9E450148.public

  protected:
    // Additional Protected Declarations
      //## begin cFMT2File%3B9C9E450148.protected preserve=yes
      //## end cFMT2File%3B9C9E450148.protected

  private:
    // Additional Private Declarations
      //## begin cFMT2File%3B9C9E450148.private preserve=yes
      //## end cFMT2File%3B9C9E450148.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: DINT2Long%1000724934
      LONG_T DINT2Long (LONG_T value);

      //## Operation: ComputeAddress%1001057895
      LONG_T ComputeAddress (CONST_STRING_T spec);

    // Additional Implementation Declarations
      //## begin cFMT2File%3B9C9E450148.implementation preserve=yes
      //## end cFMT2File%3B9C9E450148.implementation

};

//## begin cFMT2File%3B9C9E450148.postscript preserve=yes
//## end cFMT2File%3B9C9E450148.postscript

// Class cFMT2File 

//## begin module%3B9C9E450148.epilog preserve=yes
//## end module%3B9C9E450148.epilog


#endif
