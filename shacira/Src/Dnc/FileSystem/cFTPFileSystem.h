//## begin module%3BAB6CA103C2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BAB6CA103C2.cm

//## begin module%3BAB6CA103C2.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BAB6CA103C2.cp

//## Module: cFTPFileSystem%3BAB6CA103C2; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cFTPFileSystem.h

#ifndef cFTPFileSystem_h
#define cFTPFileSystem_h 1

//## begin module%3BAB6CA103C2.includes preserve=yes
//## end module%3BAB6CA103C2.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"

class __DLL_EXPORT__ cFTPSource;

//## begin module%3BAB6CA103C2.additionalDeclarations preserve=yes
//## end module%3BAB6CA103C2.additionalDeclarations


//## begin cFTPFileSystem%3BAB6CA103C2.preface preserve=yes
//## end cFTPFileSystem%3BAB6CA103C2.preface

//## Class: cFTPFileSystem%3BAB6CA103C2
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BAB6DF3030A;cFTPSource { -> F}

class __DLL_EXPORT__ cFTPFileSystem : public cToolFileSystem  //## Inherits: <unnamed>%3BAB6CB700FC
{
  //## begin cFTPFileSystem%3BAB6CA103C2.initialDeclarations preserve=yes
  //## end cFTPFileSystem%3BAB6CA103C2.initialDeclarations

    //## Constructors (generated)
      cFTPFileSystem();

      cFTPFileSystem(const cFTPFileSystem &right);

    //## Constructors (specified)
      //## Operation: cFTPFileSystem%1001090078
      cFTPFileSystem (cFTPSource *file_source, CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cFTPFileSystem();


    //## Other Operations (specified)
      //## Operation: Format%1001090079
      INT_T Format (INT_T format);

      //## Operation: Directory%1001090080
      INT_T Directory (STRING_LIST_T &file_names);

      //## Operation: Load%1001090081
      LONG_T Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: Save%1001090082
      LONG_T Save (CONST_STRING_T file_name, void *buf, ULONG_T size);

      //## Operation: Delete%1001090083
      INT_T Delete (CONST_STRING_T file_name);

      //## Operation: FileSize%1001090084
      LONG_T FileSize (CONST_STRING_T file_name);

      //## Operation: File%1001090085
      cFile * File (CONST_STRING_T file_name);

      //## Operation: GetTime%1001090086
      cTimeObject GetTime (CONST_STRING_T file_name);

  public:
    // Additional Public Declarations
      //## begin cFTPFileSystem%3BAB6CA103C2.public preserve=yes
      //## end cFTPFileSystem%3BAB6CA103C2.public

  protected:
    // Additional Protected Declarations
      //## begin cFTPFileSystem%3BAB6CA103C2.protected preserve=yes
      //## end cFTPFileSystem%3BAB6CA103C2.protected

  private:
    // Additional Private Declarations
      //## begin cFTPFileSystem%3BAB6CA103C2.private preserve=yes
      //## end cFTPFileSystem%3BAB6CA103C2.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cFTPFileSystem%3BAB6CA103C2.implementation preserve=yes
      //## end cFTPFileSystem%3BAB6CA103C2.implementation

};

//## begin cFTPFileSystem%3BAB6CA103C2.postscript preserve=yes
//## end cFTPFileSystem%3BAB6CA103C2.postscript

// Class cFTPFileSystem 

//## begin module%3BAB6CA103C2.epilog preserve=yes
//## end module%3BAB6CA103C2.epilog


#endif
