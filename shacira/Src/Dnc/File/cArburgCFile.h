//## begin module%3B9CE68C00A4.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9CE68C00A4.cm

//## begin module%3B9CE68C00A4.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9CE68C00A4.cp

//## Module: cArburgCFile%3B9CE68C00A4; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cArburgCFile.h

#ifndef cArburgCFile_h
#define cArburgCFile_h 1

//## begin module%3B9CE68C00A4.includes preserve=yes
//## end module%3B9CE68C00A4.includes

// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B9CE68C00A4.additionalDeclarations preserve=yes
//## end module%3B9CE68C00A4.additionalDeclarations


//## begin cArburgCFile%3B9CE68C00A4.preface preserve=yes
//## end cArburgCFile%3B9CE68C00A4.preface

//## Class: cArburgCFile%3B9CE68C00A4
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cArburgCFile : public cToolFile  //## Inherits: <unnamed>%3B9CE9050389
{
  //## begin cArburgCFile%3B9CE68C00A4.initialDeclarations preserve=yes
  //## end cArburgCFile%3B9CE68C00A4.initialDeclarations

    //## Constructors (generated)
      cArburgCFile();

      cArburgCFile(const cArburgCFile &right);

    //## Constructors (specified)
      //## Operation: cArburgCFile%1000119080
      cArburgCFile (CONST_STRING_T name, cFileSystem *file_system = NULL);

    //## Destructor (generated)
      virtual ~cArburgCFile();


    //## Other Operations (specified)
      //## Operation: Save%1062507895
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cArburgCFile%3B9CE68C00A4.public preserve=yes
      //## end cArburgCFile%3B9CE68C00A4.public

  protected:
    // Additional Protected Declarations
      //## begin cArburgCFile%3B9CE68C00A4.protected preserve=yes
      //## end cArburgCFile%3B9CE68C00A4.protected

  private:
    // Additional Private Declarations
      //## begin cArburgCFile%3B9CE68C00A4.private preserve=yes
      //## end cArburgCFile%3B9CE68C00A4.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cArburgCFile%3B9CE68C00A4.implementation preserve=yes
      //## end cArburgCFile%3B9CE68C00A4.implementation

};

//## begin cArburgCFile%3B9CE68C00A4.postscript preserve=yes
//## end cArburgCFile%3B9CE68C00A4.postscript

// Class cArburgCFile 

//## begin module%3B9CE68C00A4.epilog preserve=yes
//## end module%3B9CE68C00A4.epilog


#endif
