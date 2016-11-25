//## begin module%3B9D038D0187.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9D038D0187.cm

//## begin module%3B9D038D0187.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9D038D0187.cp

//## Module: cDiskSource%3B9D038D0187; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cDiskSource.h

#ifndef cDiskSource_h
#define cDiskSource_h 1

//## begin module%3B9D038D0187.includes preserve=yes
//## end module%3B9D038D0187.includes

// cToolFileSource
#include "Dnc/FileSystem/cToolFileSource.h"
//## begin module%3B9D038D0187.additionalDeclarations preserve=yes
//## end module%3B9D038D0187.additionalDeclarations


//## begin cDiskSource%3B9D038D0187.preface preserve=yes
//## end cDiskSource%3B9D038D0187.preface

//## Class: cDiskSource%3B9D038D0187
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cDiskSource : public cToolFileSource  //## Inherits: <unnamed>%3B9D03B101F7
{
  //## begin cDiskSource%3B9D038D0187.initialDeclarations preserve=yes
public:
  //## end cDiskSource%3B9D038D0187.initialDeclarations

    //## Constructors (generated)
      cDiskSource();

      cDiskSource(const cDiskSource &right);

    //## Constructors (specified)
      //## Operation: cDiskSource%1062078693
      cDiskSource (CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cDiskSource();


    //## Other Operations (specified)
      //## Operation: FileSystem%1062507917
      virtual cToolFileSystem * FileSystem ();

  public:
    // Additional Public Declarations
      //## begin cDiskSource%3B9D038D0187.public preserve=yes
      //## end cDiskSource%3B9D038D0187.public

  protected:
    // Additional Protected Declarations
      //## begin cDiskSource%3B9D038D0187.protected preserve=yes
      //## end cDiskSource%3B9D038D0187.protected

  private:
    // Additional Private Declarations
      //## begin cDiskSource%3B9D038D0187.private preserve=yes
      //## end cDiskSource%3B9D038D0187.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDiskSource%3B9D038D0187.implementation preserve=yes
      //## end cDiskSource%3B9D038D0187.implementation

};

//## begin cDiskSource%3B9D038D0187.postscript preserve=yes
//## end cDiskSource%3B9D038D0187.postscript

// Class cDiskSource 

//## begin module%3B9D038D0187.epilog preserve=yes
//## end module%3B9D038D0187.epilog


#endif
