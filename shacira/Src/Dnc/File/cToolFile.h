//## begin module%3B98E14E0070.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98E14E0070.cm

//## begin module%3B98E14E0070.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98E14E0070.cp

//## Module: cToolFile%3B98E14E0070; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cToolFile.h

#ifndef cToolFile_h
#define cToolFile_h 1

//## begin module%3B98E14E0070.includes preserve=yes

#include "Dnc/ToolFiles.h"

//## end module%3B98E14E0070.includes

// cTimeObject
#include "System/cTimeObject.h"

class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cToolFileSystem;

//## begin module%3B98E14E0070.additionalDeclarations preserve=yes
//## end module%3B98E14E0070.additionalDeclarations


//## begin cToolFile%3B98E14E0070.preface preserve=yes
//## end cToolFile%3B98E14E0070.preface

//## Class: cToolFile%3B98E14E0070
//## Category: Dnc::File%3F4DFF9F008C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BA070AE0348;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3BA21ACD00BA;cTimeObject { -> }

class __DLL_EXPORT__ cToolFile 
{
  //## begin cToolFile%3B98E14E0070.initialDeclarations preserve=yes
public:
  //## end cToolFile%3B98E14E0070.initialDeclarations

    //## Constructors (generated)
      cToolFile();

      cToolFile(const cToolFile &right);

    //## Constructors (specified)
      //## Operation: cToolFile%999877031
      cToolFile (TOOLFILE_HEADER_T *file_header, cToolFileSystem *file_system);

    //## Destructor (generated)
      virtual ~cToolFile();


    //## Other Operations (specified)
      //## Operation: Save%1000369127
      virtual void Save (cToolFileSystem *file_system = NULL) = 0;

      //## Operation: Serialize%1000308631
      void Serialize (void * &buf, ULONG_T &buf_size);

      //## Operation: AddSubFile%1062507906
      void AddSubFile (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

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
    // Additional Protected Declarations
      //## begin cToolFile%3B98E14E0070.protected preserve=yes
      //## end cToolFile%3B98E14E0070.protected

  private:
    // Additional Private Declarations
      //## begin cToolFile%3B98E14E0070.private preserve=yes
      //## end cToolFile%3B98E14E0070.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: FileHeader%3F4E0530036B
      //## begin cToolFile::FileHeader%3F4E0530036B.attr preserve=no  implementation: TOOLFILE_HEADER_T {U} 
      TOOLFILE_HEADER_T _FileHeader;
      //## end cToolFile::FileHeader%3F4E0530036B.attr

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
