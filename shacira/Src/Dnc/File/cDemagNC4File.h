//## begin module%3B9CE6A802DF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9CE6A802DF.cm

//## begin module%3B9CE6A802DF.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9CE6A802DF.cp

//## Module: cDemagNC4File%3B9CE6A802DF; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cDemagNC4File.h

#ifndef cDemagNC4File_h
#define cDemagNC4File_h 1

//## begin module%3B9CE6A802DF.includes preserve=yes
//## end module%3B9CE6A802DF.includes

// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B9CE6A802DF.additionalDeclarations preserve=yes
//## end module%3B9CE6A802DF.additionalDeclarations


//## begin cDemagNC4File%3B9CE6A802DF.preface preserve=yes
//## end cDemagNC4File%3B9CE6A802DF.preface

//## Class: cDemagNC4File%3B9CE6A802DF
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cDemagNC4File : public cToolFile  //## Inherits: <unnamed>%3B9CE909021C
{
  //## begin cDemagNC4File%3B9CE6A802DF.initialDeclarations preserve=yes
  //## end cDemagNC4File%3B9CE6A802DF.initialDeclarations

    //## Constructors (generated)
      cDemagNC4File();

      cDemagNC4File(const cDemagNC4File &right);

    //## Constructors (specified)
      //## Operation: cDemagNC4File%1000119077
      cDemagNC4File (CONST_STRING_T name, cFileSystem *file_system = NULL);

    //## Destructor (generated)
      virtual ~cDemagNC4File();


    //## Other Operations (specified)
      //## Operation: Save%1062507894
      virtual void Save (cToolFileSystem *file_system = NULL);

  public:
    // Additional Public Declarations
      //## begin cDemagNC4File%3B9CE6A802DF.public preserve=yes
      //## end cDemagNC4File%3B9CE6A802DF.public

  protected:
    // Additional Protected Declarations
      //## begin cDemagNC4File%3B9CE6A802DF.protected preserve=yes
      //## end cDemagNC4File%3B9CE6A802DF.protected

  private:
    // Additional Private Declarations
      //## begin cDemagNC4File%3B9CE6A802DF.private preserve=yes
      //## end cDemagNC4File%3B9CE6A802DF.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDemagNC4File%3B9CE6A802DF.implementation preserve=yes
      //## end cDemagNC4File%3B9CE6A802DF.implementation

};

//## begin cDemagNC4File%3B9CE6A802DF.postscript preserve=yes
//## end cDemagNC4File%3B9CE6A802DF.postscript

// Class cDemagNC4File 

//## begin module%3B9CE6A802DF.epilog preserve=yes
//## end module%3B9CE6A802DF.epilog


#endif
