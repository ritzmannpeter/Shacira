//## begin module%3BA1C07F01D3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA1C07F01D3.cm

//## begin module%3BA1C07F01D3.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA1C07F01D3.cp

//## Module: cFreeFile%3BA1C07F01D3; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cFreeFile.h

#ifndef cFreeFile_h
#define cFreeFile_h 1

//## begin module%3BA1C07F01D3.includes preserve=yes
//## end module%3BA1C07F01D3.includes

// cToolFile
#include "Dnc/File/cToolFile.h"

class __DLL_EXPORT__ cToolFileSystem;

//## begin module%3BA1C07F01D3.additionalDeclarations preserve=yes
//## end module%3BA1C07F01D3.additionalDeclarations


//## begin cFreeFile%3BA1C07F01D3.preface preserve=yes
//## end cFreeFile%3BA1C07F01D3.preface

//## Class: cFreeFile%3BA1C07F01D3
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BA1E79E02BA;cToolFileSystem { -> F}

class __DLL_EXPORT__ cFreeFile : public cToolFile  //## Inherits: <unnamed>%3BA1C092036B
{
  //## begin cFreeFile%3BA1C07F01D3.initialDeclarations preserve=yes
  //## end cFreeFile%3BA1C07F01D3.initialDeclarations

    //## Constructors (generated)
      cFreeFile();

      cFreeFile(const cFreeFile &right);

    //## Constructors (specified)
      //## Operation: cFreeFile%1000456408
      cFreeFile (CONST_STRING_T name, cFileSystem *file_system = NULL);

    //## Destructor (generated)
      virtual ~cFreeFile();

  public:
    // Additional Public Declarations
      //## begin cFreeFile%3BA1C07F01D3.public preserve=yes
      //## end cFreeFile%3BA1C07F01D3.public

  protected:
    // Additional Protected Declarations
      //## begin cFreeFile%3BA1C07F01D3.protected preserve=yes
      //## end cFreeFile%3BA1C07F01D3.protected

  private:
    // Additional Private Declarations
      //## begin cFreeFile%3BA1C07F01D3.private preserve=yes
      //## end cFreeFile%3BA1C07F01D3.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: FilePos%3BA9FD4F01D0
      //## begin cFreeFile::FilePos%3BA9FD4F01D0.attr preserve=no  implementation: ULONG_T {U} 
      ULONG_T _FilePos;
      //## end cFreeFile::FilePos%3BA9FD4F01D0.attr

    // Additional Implementation Declarations
      //## begin cFreeFile%3BA1C07F01D3.implementation preserve=yes
      //## end cFreeFile%3BA1C07F01D3.implementation

};

//## begin cFreeFile%3BA1C07F01D3.postscript preserve=yes
//## end cFreeFile%3BA1C07F01D3.postscript

// Class cFreeFile 

//## begin module%3BA1C07F01D3.epilog preserve=yes
//## end module%3BA1C07F01D3.epilog


#endif
