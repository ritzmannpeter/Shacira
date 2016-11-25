//## begin module%3B98E11000AD.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98E11000AD.cm

//## begin module%3B98E11000AD.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98E11000AD.cp

//## Module: cToolFileSystem%3B98E11000AD; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cToolFileSystem.h

#ifndef cToolFileSystem_h
#define cToolFileSystem_h 1

//## begin module%3B98E11000AD.includes preserve=yes

#include "Dnc/ToolFiles.h"

//## end module%3B98E11000AD.includes


class __DLL_EXPORT__ cToolFileSource;
class __DLL_EXPORT__ cToolFile;

//## begin module%3B98E11000AD.additionalDeclarations preserve=yes
//## end module%3B98E11000AD.additionalDeclarations


//## begin cToolFileSystem%3B98E11000AD.preface preserve=yes
//## end cToolFileSystem%3B98E11000AD.preface

//## Class: cToolFileSystem%3B98E11000AD
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3F54982C005D;cToolFile { -> F}

class __DLL_EXPORT__ cToolFileSystem 
{
  //## begin cToolFileSystem%3B98E11000AD.initialDeclarations preserve=yes
public:
  //## end cToolFileSystem%3B98E11000AD.initialDeclarations

    //## Constructors (generated)
      cToolFileSystem();

      cToolFileSystem(const cToolFileSystem &right);

    //## Constructors (specified)
      //## Operation: cToolFileSystem%999875360
      cToolFileSystem (CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cToolFileSystem();


    //## Other Operations (specified)
      //## Operation: Directory%1000119099
      virtual void Directory (TOOLFILE_HEADER_T * &file_header, ULONG_T &file_count) = 0;

      //## Operation: Format%1000119098
      virtual void Format () = 0;

      //## Operation: Delete%1000119102
      virtual void Delete (CONST_STRING_T file_name) = 0;

      //## Operation: ReadFile%1062507903
      virtual ULONG_T ReadFile (CONST_STRING_T file_name, void *buf, ULONG_T buf_size) = 0;

      //## Operation: WriteFile%1062078692
      virtual void WriteFile (CONST_STRING_T file_name, void *buf, ULONG_T amount) = 0;

      //## Operation: ToolFile%1062507905
      virtual cToolFile * ToolFile (TOOLFILE_HEADER_T *file_header) = 0;

      //## Operation: AllocHeader%1062162394
      static TOOLFILE_HEADER_T * AllocHeader (ULONG_T files);

      //## Operation: FreeHeader%1062162395
      static void FreeHeader (TOOLFILE_HEADER_T *header);

      //## Operation: CopyHeader%1062507907
      static void CopyHeader (TOOLFILE_HEADER_T *dst, TOOLFILE_HEADER_T *src);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Format%3B9DD8F30280
      INT_T get_Format () const;

      //## Attribute: Path%3BA0C4F102CE
      STRING_T get_Path () const;

    //## Get and Set Operations for Associations (generated)

      //## Association: Dnc::FileSystem::<unnamed>%3F4DFB3E0186
      //## Role: cToolFileSystem::FileSource%3F4DFB410128
      const cToolFileSource * get_FileSource () const;
      void set_FileSource (cToolFileSource * value);

  public:
    // Additional Public Declarations
      //## begin cToolFileSystem%3B98E11000AD.public preserve=yes
      //## end cToolFileSystem%3B98E11000AD.public

  protected:
    // Data Members for Class Attributes

      //## begin cToolFileSystem::Format%3B9DD8F30280.attr preserve=no  public: INT_T {U} FMT_UNDEFINED
      INT_T _Format;
      //## end cToolFileSystem::Format%3B9DD8F30280.attr

      //## begin cToolFileSystem::Path%3BA0C4F102CE.attr preserve=no  public: STRING_T {U} 
      STRING_T _Path;
      //## end cToolFileSystem::Path%3BA0C4F102CE.attr

    // Additional Protected Declarations
      //## begin cToolFileSystem%3B98E11000AD.protected preserve=yes
      //## end cToolFileSystem%3B98E11000AD.protected

  private:
    // Additional Private Declarations
      //## begin cToolFileSystem%3B98E11000AD.private preserve=yes
      //## end cToolFileSystem%3B98E11000AD.private

  private: //## implementation
    // Data Members for Associations

      //## Association: Dnc::FileSystem::<unnamed>%3F4DFB3E0186
      //## begin cToolFileSystem::FileSource%3F4DFB410128.role preserve=no  public: cToolFileSource { -> 1RFHN}
      cToolFileSource *FileSource;
      //## end cToolFileSystem::FileSource%3F4DFB410128.role

    // Additional Implementation Declarations
      //## begin cToolFileSystem%3B98E11000AD.implementation preserve=yes
      //## end cToolFileSystem%3B98E11000AD.implementation

};

//## begin cToolFileSystem%3B98E11000AD.postscript preserve=yes
//## end cToolFileSystem%3B98E11000AD.postscript

// Class cToolFileSystem 

//## Get and Set Operations for Associations (inline)

inline const cToolFileSource * cToolFileSystem::get_FileSource () const
{
  //## begin cToolFileSystem::get_FileSource%3F4DFB410128.get preserve=no
  return FileSource;
  //## end cToolFileSystem::get_FileSource%3F4DFB410128.get
}

inline void cToolFileSystem::set_FileSource (cToolFileSource * value)
{
  //## begin cToolFileSystem::set_FileSource%3F4DFB410128.set preserve=no
  FileSource = value;
  //## end cToolFileSystem::set_FileSource%3F4DFB410128.set
}

//## begin module%3B98E11000AD.epilog preserve=yes
//## end module%3B98E11000AD.epilog


#endif
