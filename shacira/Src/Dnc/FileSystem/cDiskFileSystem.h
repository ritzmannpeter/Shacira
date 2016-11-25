//## begin module%3B98FB79000E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98FB79000E.cm

//## begin module%3B98FB79000E.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98FB79000E.cp

//## Module: cDiskFileSystem%3B98FB79000E; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cDiskFileSystem.h

#ifndef cDiskFileSystem_h
#define cDiskFileSystem_h 1

//## begin module%3B98FB79000E.includes preserve=yes
//## end module%3B98FB79000E.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"

class __DLL_EXPORT__ cDiskSource;

//## begin module%3B98FB79000E.additionalDeclarations preserve=yes
//## end module%3B98FB79000E.additionalDeclarations


//## begin cDiskFileSystem%3B98FB79000E.preface preserve=yes
//## end cDiskFileSystem%3B98FB79000E.preface

//## Class: cDiskFileSystem%3B98FB79000E
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BAB6E610195;cDiskSource { -> F}

class __DLL_EXPORT__ cDiskFileSystem : public cToolFileSystem  //## Inherits: <unnamed>%3B98FBA2013A
{
  //## begin cDiskFileSystem%3B98FB79000E.initialDeclarations preserve=yes
  //## end cDiskFileSystem%3B98FB79000E.initialDeclarations

    //## Constructors (generated)
      cDiskFileSystem();

      cDiskFileSystem(const cDiskFileSystem &right);

    //## Constructors (specified)
      //## Operation: cDiskFileSystem%999877037
      cDiskFileSystem (cDiskSource *file_source, CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cDiskFileSystem();


    //## Other Operations (specified)
      //## Operation: Format%1000119093
      INT_T Format (INT_T format);

      //## Operation: Directory%1000119094
      INT_T Directory (STRING_LIST_T &file_names);

      //## Operation: Load%1000119095
      LONG_T Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: Save%1000119096
      LONG_T Save (CONST_STRING_T file_name, void *buf, ULONG_T size);

      //## Operation: Delete%1000119097
      INT_T Delete (CONST_STRING_T file_name);

      //## Operation: FileSize%1000386728
      LONG_T FileSize (CONST_STRING_T file_name);

      //## Operation: File%1000386729
      cFile * File (CONST_STRING_T file_name);

      //## Operation: GetTime%1000456412
      cTimeObject GetTime (CONST_STRING_T file_name);

  public:
    // Additional Public Declarations
      //## begin cDiskFileSystem%3B98FB79000E.public preserve=yes
      //## end cDiskFileSystem%3B98FB79000E.public

  protected:
    // Additional Protected Declarations
      //## begin cDiskFileSystem%3B98FB79000E.protected preserve=yes
      //## end cDiskFileSystem%3B98FB79000E.protected

  private:
    // Additional Private Declarations
      //## begin cDiskFileSystem%3B98FB79000E.private preserve=yes
      //## end cDiskFileSystem%3B98FB79000E.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cDiskFileSystem%3B98FB79000E.implementation preserve=yes
      //## end cDiskFileSystem%3B98FB79000E.implementation

};

//## begin cDiskFileSystem%3B98FB79000E.postscript preserve=yes
//## end cDiskFileSystem%3B98FB79000E.postscript

// Class cDiskFileSystem 

//## begin module%3B98FB79000E.epilog preserve=yes
//## end module%3B98FB79000E.epilog


#endif
