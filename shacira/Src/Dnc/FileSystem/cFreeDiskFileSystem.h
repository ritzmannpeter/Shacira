//## begin module%3BA0AC11001E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA0AC11001E.cm

//## begin module%3BA0AC11001E.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA0AC11001E.cp

//## Module: cFreeDiskFileSystem%3BA0AC11001E; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cFreeDiskFileSystem.h

#ifndef cFreeDiskFileSystem_h
#define cFreeDiskFileSystem_h 1

//## begin module%3BA0AC11001E.includes preserve=yes
//## end module%3BA0AC11001E.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"

class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cFreeDiskSource;

//## begin module%3BA0AC11001E.additionalDeclarations preserve=yes
//## end module%3BA0AC11001E.additionalDeclarations


//## begin cFreeDiskFileSystem%3BA0AC11001E.preface preserve=yes
//## end cFreeDiskFileSystem%3BA0AC11001E.preface

//## Class: cFreeDiskFileSystem%3BA0AC11001E
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BA0C49A03A5;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3BAB6E3F01F0;cFreeDiskSource { -> F}

class __DLL_EXPORT__ cFreeDiskFileSystem : public cToolFileSystem  //## Inherits: <unnamed>%3BA0AC4A0297
{
  //## begin cFreeDiskFileSystem%3BA0AC11001E.initialDeclarations preserve=yes
  //## end cFreeDiskFileSystem%3BA0AC11001E.initialDeclarations

    //## Constructors (generated)
      cFreeDiskFileSystem();

      cFreeDiskFileSystem(const cFreeDiskFileSystem &right);

    //## Constructors (specified)
      //## Operation: cFreeDiskFileSystem%1000369128
      cFreeDiskFileSystem (cFreeDiskSource *file_source, CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cFreeDiskFileSystem();


    //## Other Operations (specified)
      //## Operation: Format%1000369129
      INT_T Format (INT_T format);

      //## Operation: Directory%1000369130
      INT_T Directory (STRING_LIST_T &file_names);

      //## Operation: Load%1000369131
      LONG_T Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: Save%1000369132
      LONG_T Save (CONST_STRING_T file_name, void *buf, ULONG_T size);

      //## Operation: Delete%1000369133
      INT_T Delete (CONST_STRING_T file_name);

      //## Operation: FileSize%1000386732
      LONG_T FileSize (CONST_STRING_T file_name);

      //## Operation: File%1000386733
      cFile * File (CONST_STRING_T file_name);

      //## Operation: GetTime%1000456414
      cTimeObject GetTime (CONST_STRING_T file_name);

  public:
    // Additional Public Declarations
      //## begin cFreeDiskFileSystem%3BA0AC11001E.public preserve=yes
      //## end cFreeDiskFileSystem%3BA0AC11001E.public

  protected:
    // Additional Protected Declarations
      //## begin cFreeDiskFileSystem%3BA0AC11001E.protected preserve=yes
      //## end cFreeDiskFileSystem%3BA0AC11001E.protected

  private:
    // Additional Private Declarations
      //## begin cFreeDiskFileSystem%3BA0AC11001E.private preserve=yes
      //## end cFreeDiskFileSystem%3BA0AC11001E.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cFreeDiskFileSystem%3BA0AC11001E.implementation preserve=yes
      //## end cFreeDiskFileSystem%3BA0AC11001E.implementation

};

//## begin cFreeDiskFileSystem%3BA0AC11001E.postscript preserve=yes
//## end cFreeDiskFileSystem%3BA0AC11001E.postscript

// Class cFreeDiskFileSystem 

//## begin module%3BA0AC11001E.epilog preserve=yes
//## end module%3BA0AC11001E.epilog


#endif
