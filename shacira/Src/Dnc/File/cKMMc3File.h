//## begin module%3F4E04500222.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4E04500222.cm

//## begin module%3F4E04500222.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3F4E04500222.cp

//## Module: cKMMc3File%3F4E04500222; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cKMMc3File.h

#ifndef cKMMc3File_h
#define cKMMc3File_h 1

//## begin module%3F4E04500222.includes preserve=yes
//## end module%3F4E04500222.includes

// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3F4E04500222.additionalDeclarations preserve=yes
//## end module%3F4E04500222.additionalDeclarations


//## begin cKMMc3File%3F4E04500222.preface preserve=yes
//## end cKMMc3File%3F4E04500222.preface

//## Class: cKMMc3File%3F4E04500222
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cKMMc3File : public cToolFile  //## Inherits: <unnamed>%3F4E047800BB
{
  //## begin cKMMc3File%3F4E04500222.initialDeclarations preserve=yes
  //## end cKMMc3File%3F4E04500222.initialDeclarations

    //## Constructors (generated)
      cKMMc3File();

      cKMMc3File(const cKMMc3File &right);

    //## Destructor (generated)
      virtual ~cKMMc3File();


    //## Other Operations (specified)
      //## Operation: Save%1062507893
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cKMMc3File%3F4E04500222.public preserve=yes
      //## end cKMMc3File%3F4E04500222.public

  protected:
    // Additional Protected Declarations
      //## begin cKMMc3File%3F4E04500222.protected preserve=yes
      //## end cKMMc3File%3F4E04500222.protected

  private:
    // Additional Private Declarations
      //## begin cKMMc3File%3F4E04500222.private preserve=yes
      //## end cKMMc3File%3F4E04500222.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cKMMc3File%3F4E04500222.implementation preserve=yes
      //## end cKMMc3File%3F4E04500222.implementation

};

//## begin cKMMc3File%3F4E04500222.postscript preserve=yes
//## end cKMMc3File%3F4E04500222.postscript

// Class cKMMc3File 

//## begin module%3F4E04500222.epilog preserve=yes
//## end module%3F4E04500222.epilog


#endif
