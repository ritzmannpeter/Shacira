//## begin module%3B99015D0356.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B99015D0356.cm

//## begin module%3B99015D0356.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B99015D0356.cp

//## Module: cCellFileSystem%3B99015D0356; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCellFileSystem.h

#ifndef cCellFileSystem_h
#define cCellFileSystem_h 1

//## begin module%3B99015D0356.includes preserve=yes
//## end module%3B99015D0356.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"

class __DLL_EXPORT__ cCellSource;

//## begin module%3B99015D0356.additionalDeclarations preserve=yes
//## end module%3B99015D0356.additionalDeclarations


//## begin cCellFileSystem%3B99015D0356.preface preserve=yes
//## end cCellFileSystem%3B99015D0356.preface

//## Class: cCellFileSystem%3B99015D0356
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BAB6E870168;cCellSource { -> F}

class cCellFileSystem : public cToolFileSystem  //## Inherits: <unnamed>%3B99017603CA
{
  //## begin cCellFileSystem%3B99015D0356.initialDeclarations preserve=yes
  //## end cCellFileSystem%3B99015D0356.initialDeclarations

  public:
    //## Constructors (generated)
      cCellFileSystem();

      cCellFileSystem(const cCellFileSystem &right);

    //## Constructors (specified)
      //## Operation: cCellFileSystem%999877038
      cCellFileSystem (cCellSource *file_source, CONST_STRING_T path);

    //## Destructor (generated)
      ~cCellFileSystem();

    //## Assignment Operation (generated)
      const cCellFileSystem & operator=(const cCellFileSystem &right);

    //## Equality Operations (generated)
      INT_T operator==(const cCellFileSystem &right) const;

      INT_T operator!=(const cCellFileSystem &right) const;


    //## Other Operations (specified)
      //## Operation: Format%1000119083
      INT_T Format (INT_T format);

      //## Operation: Directory%1000119084
      INT_T Directory (STRING_LIST_T &file_names);

      //## Operation: Load%1000119085
      LONG_T Load (CONST_STRING_T file_name, void *buf, ULONG_T size);

      //## Operation: Save%1000119086
      LONG_T Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: Delete%1000119087
      INT_T Delete (CONST_STRING_T file_name);

      //## Operation: FileSize%1000386736
      LONG_T FileSize (CONST_STRING_T file_name);

      //## Operation: File%1000386737
      cFile * File (CONST_STRING_T file_name);

      //## Operation: GetTime%1000456416
      cTimeObject GetTime (CONST_STRING_T file_name);

    // Additional Public Declarations
      //## begin cCellFileSystem%3B99015D0356.public preserve=yes
      //## end cCellFileSystem%3B99015D0356.public

  protected:
    // Additional Protected Declarations
      //## begin cCellFileSystem%3B99015D0356.protected preserve=yes
      //## end cCellFileSystem%3B99015D0356.protected

  private:
    // Additional Private Declarations
      //## begin cCellFileSystem%3B99015D0356.private preserve=yes
      //## end cCellFileSystem%3B99015D0356.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCellFileSystem%3B99015D0356.implementation preserve=yes
      //## end cCellFileSystem%3B99015D0356.implementation

};

//## begin cCellFileSystem%3B99015D0356.postscript preserve=yes
//## end cCellFileSystem%3B99015D0356.postscript

// Class cCellFileSystem 

//## begin module%3B99015D0356.epilog preserve=yes
//## end module%3B99015D0356.epilog


#endif
