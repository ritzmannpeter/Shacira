//## begin module%3BAB6C78007A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BAB6C78007A.cm

//## begin module%3BAB6C78007A.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BAB6C78007A.cp

//## Module: cFTPSource%3BAB6C78007A; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cFTPSource.h

#ifndef cFTPSource_h
#define cFTPSource_h 1

//## begin module%3BAB6C78007A.includes preserve=yes
//## end module%3BAB6C78007A.includes

// cToolFileSource
#include "Dnc/FileSystem/cToolFileSource.h"
//## begin module%3BAB6C78007A.additionalDeclarations preserve=yes
//## end module%3BAB6C78007A.additionalDeclarations


//## begin cFTPSource%3BAB6C78007A.preface preserve=yes
//## end cFTPSource%3BAB6C78007A.preface

//## Class: cFTPSource%3BAB6C78007A
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cFTPSource : public cToolFileSource  //## Inherits: <unnamed>%3BAB6C930336
{
  //## begin cFTPSource%3BAB6C78007A.initialDeclarations preserve=yes
  //## end cFTPSource%3BAB6C78007A.initialDeclarations

    //## Constructors (generated)
      cFTPSource();

      cFTPSource(const cFTPSource &right);

    //## Constructors (specified)
      //## Operation: cFTPSource%1062078723
      cFTPSource (CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cFTPSource();


    //## Other Operations (specified)
      //## Operation: FileSystem%1062507915
      virtual cToolFileSystem * FileSystem ();

  public:
    // Additional Public Declarations
      //## begin cFTPSource%3BAB6C78007A.public preserve=yes
      //## end cFTPSource%3BAB6C78007A.public

  protected:
    // Additional Protected Declarations
      //## begin cFTPSource%3BAB6C78007A.protected preserve=yes
      //## end cFTPSource%3BAB6C78007A.protected

  private:
    // Additional Private Declarations
      //## begin cFTPSource%3BAB6C78007A.private preserve=yes
      //## end cFTPSource%3BAB6C78007A.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cFTPSource%3BAB6C78007A.implementation preserve=yes
      //## end cFTPSource%3BAB6C78007A.implementation

};

//## begin cFTPSource%3BAB6C78007A.postscript preserve=yes
//## end cFTPSource%3BAB6C78007A.postscript

// Class cFTPSource 

//## begin module%3BAB6C78007A.epilog preserve=yes
//## end module%3BAB6C78007A.epilog


#endif
