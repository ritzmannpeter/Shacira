//## begin module%3B9C9DEE028D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9C9DEE028D.cm

//## begin module%3B9C9DEE028D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9C9DEE028D.cp

//## Module: cFMT1File%3B9C9DEE028D; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFMT1File.h

#ifndef cFMT1File_h
#define cFMT1File_h 1

//## begin module%3B9C9DEE028D.includes preserve=yes
//## end module%3B9C9DEE028D.includes

// cError
#include "System/cError.h"
// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B9C9DEE028D.additionalDeclarations preserve=yes
//## end module%3B9C9DEE028D.additionalDeclarations


//## begin cFMT1File%3B9C9DEE028D.preface preserve=yes
//## end cFMT1File%3B9C9DEE028D.preface

//## Class: cFMT1File%3B9C9DEE028D
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B9CA15400D6;cError { -> }

class __DLL_EXPORT__ cFMT1File : public cToolFile  //## Inherits: <unnamed>%3B9C9E0B019F
{
  //## begin cFMT1File%3B9C9DEE028D.initialDeclarations preserve=yes
  //## end cFMT1File%3B9C9DEE028D.initialDeclarations

    //## Constructors (generated)
      cFMT1File();

      cFMT1File(const cFMT1File &right);

    //## Constructors (specified)
      //## Operation: cFMT1File%1000119070
      cFMT1File (CONST_STRING_T name, cFileSystem *file_system = NULL);

    //## Destructor (generated)
      virtual ~cFMT1File();


    //## Other Operations (specified)
      //## Operation: Save%1062507900
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cFMT1File%3B9C9DEE028D.public preserve=yes
      //## end cFMT1File%3B9C9DEE028D.public

  protected:
    // Additional Protected Declarations
      //## begin cFMT1File%3B9C9DEE028D.protected preserve=yes
      //## end cFMT1File%3B9C9DEE028D.protected

  private:
    // Additional Private Declarations
      //## begin cFMT1File%3B9C9DEE028D.private preserve=yes
      //## end cFMT1File%3B9C9DEE028D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: ComputeAddress%1001057892
      LONG_T ComputeAddress (CONST_STRING_T spec);

    // Additional Implementation Declarations
      //## begin cFMT1File%3B9C9DEE028D.implementation preserve=yes
      //## end cFMT1File%3B9C9DEE028D.implementation

};

//## begin cFMT1File%3B9C9DEE028D.postscript preserve=yes
//## end cFMT1File%3B9C9DEE028D.postscript

// Class cFMT1File 

//## begin module%3B9C9DEE028D.epilog preserve=yes
//## end module%3B9C9DEE028D.epilog


#endif
