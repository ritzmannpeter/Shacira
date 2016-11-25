//## begin module%3B99015D0356.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B99015D0356.cm

//## begin module%3B99015D0356.cp preserve=no
//## end module%3B99015D0356.cp

//## Module: cCellDirectory%3B99015D0356; Pseudo Package specification
//## Source file: d:\usr\prj\ls2i\src\Dnc\FileSystem\cCellDirectory.h

#ifndef cCellDirectory_h
#define cCellDirectory_h 1

//## begin module%3B99015D0356.additionalIncludes preserve=no
//## end module%3B99015D0356.additionalIncludes

//## begin module%3B99015D0356.includes preserve=yes
//## end module%3B99015D0356.includes

// cDirectory
#include "Dnc\FileSystem\cDirectory.h"
//## begin module%3B99015D0356.additionalDeclarations preserve=yes
//## end module%3B99015D0356.additionalDeclarations


//## begin cCellDirectory%3B99015D0356.preface preserve=yes
//## end cCellDirectory%3B99015D0356.preface

//## Class: cCellDirectory%3B99015D0356
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class cCellDirectory : public cDirectory  //## Inherits: <unnamed>%3B99017603CA
{
  //## begin cCellDirectory%3B99015D0356.initialDeclarations preserve=yes
  //## end cCellDirectory%3B99015D0356.initialDeclarations

  public:
    //## Constructors (generated)
      cCellDirectory();

      cCellDirectory(const cCellDirectory &right);

    //## Constructors (specified)
      //## Operation: cCellDirectory%999877038
      cCellDirectory (cFileSystem *file_system, CONST_STRING_T path);

    //## Destructor (generated)
      ~cCellDirectory();

    //## Assignment Operation (generated)
      const cCellDirectory & operator=(const cCellDirectory &right);

    //## Equality Operations (generated)
      int operator==(const cCellDirectory &right) const;

      int operator!=(const cCellDirectory &right) const;

    // Additional Public Declarations
      //## begin cCellDirectory%3B99015D0356.public preserve=yes
      //## end cCellDirectory%3B99015D0356.public

  protected:
    // Additional Protected Declarations
      //## begin cCellDirectory%3B99015D0356.protected preserve=yes
      //## end cCellDirectory%3B99015D0356.protected

  private:
    // Additional Private Declarations
      //## begin cCellDirectory%3B99015D0356.private preserve=yes
      //## end cCellDirectory%3B99015D0356.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCellDirectory%3B99015D0356.implementation preserve=yes
      //## end cCellDirectory%3B99015D0356.implementation

};

//## begin cCellDirectory%3B99015D0356.postscript preserve=yes
//## end cCellDirectory%3B99015D0356.postscript

// Class cCellDirectory 

//## begin module%3B99015D0356.epilog preserve=yes
//## end module%3B99015D0356.epilog


#endif
