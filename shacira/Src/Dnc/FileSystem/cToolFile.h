//## begin module%3B98E14E0070.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98E14E0070.cm

//## begin module%3B98E14E0070.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98E14E0070.cp

//## Module: cToolFile%3B98E14E0070; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cToolFile.h

#ifndef cToolFile_h
#define cToolFile_h 1

//## begin module%3B98E14E0070.includes preserve=yes
//## end module%3B98E14E0070.includes

// cTimeObject
#include "System/cTimeObject.h"
// cMemoryPtr
#include "System/Memory/cMemoryPtr.h"

class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cToolFileSystem;

//## begin module%3B98E14E0070.additionalDeclarations preserve=yes
//## end module%3B98E14E0070.additionalDeclarations


//## begin cToolFile%3B98E14E0070.preface preserve=yes
//## end cToolFile%3B98E14E0070.preface

//## Class: cToolFile%3B98E14E0070
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B9F94F40299;cMemoryPtr { -> }
//## Uses: <unnamed>%3BA070AE0348;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3BA21ACD00BA;cTimeObject { -> }

class __DLL_EXPORT__ cToolFile 
{
  //## begin cToolFile%3B98E14E0070.initialDeclarations preserve=yes
  //## end cToolFile%3B98E14E0070.initialDeclarations

    //## Constructors (generated)
      cToolFile();

      cToolFile(const cToolFile &right);

    //## Constructors (specified)
      //## Operation: cToolFile%999877031
      cToolFile (CONST_STRING_T name, cToolFileSystem *file_system);

    //## Destructor (generated)
      virtual ~cToolFile();


    //## Other Operations (specified)
      //## Operation: GetVariableValue%1000119051
      virtual INT_T GetVariableValue (CONST_STRING_T name, STRING_T &value) = 0;

      //## Operation: SetVariableValue%1000119052
      virtual INT_T SetVariableValue (CONST_STRING_T name, CONST_STRING_T value) = 0;

      //## Operation: Save%1000369127
      virtual INT_T Save (cToolFileSystem *file_system = NULL, CONST_STRING_T file_name = NULL) = 0;

      //## Operation: GetBuf%1000308631
      INT_T GetBuf (void * &buf, ULONG_T &buf_size);

    // Data Members for Associations

      //## Association: Dnc::FileSystem::<unnamed>%3BA0E59C0297
      //## Role: cToolFile::FileSystem%3BA0E59D031B
      //## begin cToolFile::FileSystem%3BA0E59D031B.role preserve=no  public: cToolFileSystem { -> 0..1RFHN}
      cToolFileSystem *_FileSystem;
      //## end cToolFile::FileSystem%3BA0E59D031B.role

  public:
    // Additional Public Declarations
      //## begin cToolFile%3B98E14E0070.public preserve=yes
      //## end cToolFile%3B98E14E0070.public

  protected:
    // Data Members for Associations

      //## Association: Dnc::FileSystem::<unnamed>%3B9C9D0F0229
      //## Role: cToolFile::FileBuffer%3B9C9D10016C
      //## begin cToolFile::FileBuffer%3B9C9D10016C.role preserve=no  public: cMemoryPtr { -> 1RFHN}
      cMemoryPtr *_FileBuffer;
      //## end cToolFile::FileBuffer%3B9C9D10016C.role

    // Additional Protected Declarations
      //## begin cToolFile%3B98E14E0070.protected preserve=yes
      //## end cToolFile%3B98E14E0070.protected

  private:
    // Additional Private Declarations
      //## begin cToolFile%3B98E14E0070.private preserve=yes
      //## end cToolFile%3B98E14E0070.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: FileInfo%3F4E0530036B
      //## begin cToolFile::FileInfo%3F4E0530036B.attr preserve=no  implementation: FILE_INFO_T {U} 
      FILE_INFO_T _FileInfo;
      //## end cToolFile::FileInfo%3F4E0530036B.attr

    // Additional Implementation Declarations
      //## begin cToolFile%3B98E14E0070.implementation preserve=yes
      //## end cToolFile%3B98E14E0070.implementation

};

//## begin cToolFile%3B98E14E0070.postscript preserve=yes
//## end cToolFile%3B98E14E0070.postscript

// Class cToolFile 

//## begin module%3B98E14E0070.epilog preserve=yes
//## end module%3B98E14E0070.epilog


#endif
