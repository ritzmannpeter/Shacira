//## begin module%3B9D037703C0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9D037703C0.cm

//## begin module%3B9D037703C0.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9D037703C0.cp

//## Module: cCellSource%3B9D037703C0; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCellSource.h

#ifndef cCellSource_h
#define cCellSource_h 1

//## begin module%3B9D037703C0.includes preserve=yes
//## end module%3B9D037703C0.includes

// cToolFileSource
#include "Dnc/FileSystem/cToolFileSource.h"
//## begin module%3B9D037703C0.additionalDeclarations preserve=yes
//## end module%3B9D037703C0.additionalDeclarations


//## begin cCellSource%3B9D037703C0.preface preserve=yes
//## end cCellSource%3B9D037703C0.preface

//## Class: cCellSource%3B9D037703C0
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cCellSource : public cToolFileSource  //## Inherits: <unnamed>%3B9D03AE0383
{
  //## begin cCellSource%3B9D037703C0.initialDeclarations preserve=yes
  //## end cCellSource%3B9D037703C0.initialDeclarations

    //## Constructors (generated)
      cCellSource();

      cCellSource(const cCellSource &right);

    //## Constructors (specified)
      //## Operation: cCellSource%1062078701
      cCellSource (CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cCellSource();


    //## Other Operations (specified)
      //## Operation: FileSystem%1062507916
      virtual cToolFileSystem * FileSystem ();

  public:
    // Additional Public Declarations
      //## begin cCellSource%3B9D037703C0.public preserve=yes
      //## end cCellSource%3B9D037703C0.public

  protected:
    // Additional Protected Declarations
      //## begin cCellSource%3B9D037703C0.protected preserve=yes
      //## end cCellSource%3B9D037703C0.protected

  private:
    // Additional Private Declarations
      //## begin cCellSource%3B9D037703C0.private preserve=yes
      //## end cCellSource%3B9D037703C0.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCellSource%3B9D037703C0.implementation preserve=yes
      //## end cCellSource%3B9D037703C0.implementation

};

//## begin cCellSource%3B9D037703C0.postscript preserve=yes
//## end cCellSource%3B9D037703C0.postscript

// Class cCellSource 

//## begin module%3B9D037703C0.epilog preserve=yes
//## end module%3B9D037703C0.epilog


#endif
