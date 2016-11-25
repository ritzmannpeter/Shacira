//## begin module%3B98FB79000E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98FB79000E.cm

//## begin module%3B98FB79000E.cp preserve=no
//## end module%3B98FB79000E.cp

//## Module: cDiskDirectory%3B98FB79000E; Pseudo Package specification
//## Source file: d:\usr\prj\ls2i\src\Dnc\FileSystem\cDiskDirectory.h

#ifndef cDiskDirectory_h
#define cDiskDirectory_h 1

//## begin module%3B98FB79000E.additionalIncludes preserve=no
//## end module%3B98FB79000E.additionalIncludes

//## begin module%3B98FB79000E.includes preserve=yes
//## end module%3B98FB79000E.includes

// GlobalDefinitions
#include "System\GlobalDefinitions.h"
// cDirectory
#include "Dnc\FileSystem\cDirectory.h"
//## begin module%3B98FB79000E.additionalDeclarations preserve=yes
//## end module%3B98FB79000E.additionalDeclarations


//## begin cDiskDirectory%3B98FB79000E.preface preserve=yes
//## end cDiskDirectory%3B98FB79000E.preface

//## Class: cDiskDirectory%3B98FB79000E
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B98FC890074;GlobalDefinitions { -> }

class cDiskDirectory : public cDirectory  //## Inherits: <unnamed>%3B98FBA2013A
{
  //## begin cDiskDirectory%3B98FB79000E.initialDeclarations preserve=yes
  //## end cDiskDirectory%3B98FB79000E.initialDeclarations

  public:
    //## Constructors (generated)
      cDiskDirectory();

      cDiskDirectory(const cDiskDirectory &right);

    //## Constructors (specified)
      //## Operation: cDiskDirectory%999877037
      cDiskDirectory (cFileSystem *file_system, CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cDiskDirectory();

    // Additional Public Declarations
      //## begin cDiskDirectory%3B98FB79000E.public preserve=yes
      //## end cDiskDirectory%3B98FB79000E.public

  protected:
    // Additional Protected Declarations
      //## begin cDiskDirectory%3B98FB79000E.protected preserve=yes
      //## end cDiskDirectory%3B98FB79000E.protected

  private:
    // Additional Private Declarations
      //## begin cDiskDirectory%3B98FB79000E.private preserve=yes
      //## end cDiskDirectory%3B98FB79000E.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDiskDirectory%3B98FB79000E.implementation preserve=yes
      //## end cDiskDirectory%3B98FB79000E.implementation

};

//## begin cDiskDirectory%3B98FB79000E.postscript preserve=yes
//## end cDiskDirectory%3B98FB79000E.postscript

// Class cDiskDirectory 

//## begin module%3B98FB79000E.epilog preserve=yes
//## end module%3B98FB79000E.epilog


#endif
