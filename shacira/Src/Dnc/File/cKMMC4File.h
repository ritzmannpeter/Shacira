//## begin module%3F4E048B02BF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4E048B02BF.cm

//## begin module%3F4E048B02BF.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3F4E048B02BF.cp

//## Module: cKMMC4File%3F4E048B02BF; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cKMMC4File.h

#ifndef cKMMC4File_h
#define cKMMC4File_h 1

//## begin module%3F4E048B02BF.includes preserve=yes
//## end module%3F4E048B02BF.includes

// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3F4E048B02BF.additionalDeclarations preserve=yes
//## end module%3F4E048B02BF.additionalDeclarations


//## begin cKMMC4File%3F4E048B02BF.preface preserve=yes
//## end cKMMC4File%3F4E048B02BF.preface

//## Class: cKMMC4File%3F4E048B02BF
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cKMMC4File : public cToolFile  //## Inherits: <unnamed>%3F4E04B200AB
{
  //## begin cKMMC4File%3F4E048B02BF.initialDeclarations preserve=yes
  //## end cKMMC4File%3F4E048B02BF.initialDeclarations

    //## Constructors (generated)
      cKMMC4File();

      cKMMC4File(const cKMMC4File &right);

    //## Destructor (generated)
      virtual ~cKMMC4File();


    //## Other Operations (specified)
      //## Operation: Save%1062507892
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cKMMC4File%3F4E048B02BF.public preserve=yes
      //## end cKMMC4File%3F4E048B02BF.public

  protected:
    // Additional Protected Declarations
      //## begin cKMMC4File%3F4E048B02BF.protected preserve=yes
      //## end cKMMC4File%3F4E048B02BF.protected

  private:
    // Additional Private Declarations
      //## begin cKMMC4File%3F4E048B02BF.private preserve=yes
      //## end cKMMC4File%3F4E048B02BF.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cKMMC4File%3F4E048B02BF.implementation preserve=yes
      //## end cKMMC4File%3F4E048B02BF.implementation

};

//## begin cKMMC4File%3F4E048B02BF.postscript preserve=yes
//## end cKMMC4File%3F4E048B02BF.postscript

// Class cKMMC4File 

//## begin module%3F4E048B02BF.epilog preserve=yes
//## end module%3F4E048B02BF.epilog


#endif
