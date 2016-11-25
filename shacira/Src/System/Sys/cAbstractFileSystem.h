//## begin module%440800B203DD.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%440800B203DD.cm

//## begin module%440800B203DD.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%440800B203DD.cp

//## Module: cAbstractFileSystem%440800B203DD; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cAbstractFileSystem.h

#ifndef cAbstractFileSystem_h
#define cAbstractFileSystem_h 1

//## begin module%440800B203DD.includes preserve=yes
//## end module%440800B203DD.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"

class __DLL_EXPORT__ cStandardFileSystem;

//## begin module%440800B203DD.additionalDeclarations preserve=yes

// file system types
#define FS_STANDARD     0
#define FS_FTP          1

// file system flags
#define FS_FLAG_REMOVE  0x00000001
#define FS_FLAG_APPEND  0x00000002

// error codes
#define FAILED_TO_CREATE_DIRECTORY  -1
#define FILE_DOES_NOT_EXIST         -2
#define FAILED_TO_WRITE_FILE        -3
#define FAILED_TO_RENAME_FILE       -4
#define FAILED_TO_CREATE_FILE       -5
#define FAILED_TO_REMOVE_FILE       -6

//## end module%440800B203DD.additionalDeclarations


//## begin cAbstractFileSystem%440800B203DD.preface preserve=yes
//## end cAbstractFileSystem%440800B203DD.preface

//## Class: cAbstractFileSystem%440800B203DD
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%440805660017;cStandardFileSystem { -> F}
//## Uses: <unnamed>%4408082102E8;cFileSystemUtils { -> }

class __DLL_EXPORT__ cAbstractFileSystem 
{
  //## begin cAbstractFileSystem%440800B203DD.initialDeclarations preserve=yes
public:
  //## end cAbstractFileSystem%440800B203DD.initialDeclarations

    //## Constructors (generated)
      cAbstractFileSystem();

      cAbstractFileSystem(const cAbstractFileSystem &right);

    //## Destructor (generated)
      virtual ~cAbstractFileSystem();


    //## Other Operations (specified)
      //## Operation: Scan%1141375544
      virtual ULONG_T Scan (STRING_LIST_T &file_names, CONST_STRING_T pattern) = 0;

      //## Operation: Get%1141375545
      virtual int Get (CONST_STRING_T path, STRING_T &buffer, ULONG_T flags) = 0;

      //## Operation: Put%1141375546
      virtual int Put (CONST_STRING_T path, CONST_STRING_T text, ULONG_T flags) = 0;

      //## Operation: Rename%1141375547
      virtual BOOL_T Rename (CONST_STRING_T path, CONST_STRING_T new_path, ULONG_T flags) = 0;

      //## Operation: RemoveFile
      virtual int RemoveFile (CONST_STRING_T path) = 0;

      //## Operation: Create%1141375548
      static cAbstractFileSystem * Create (ULONG_T type);

      //## Operation: ErrorText%1166170818
      virtual CONST_STRING_T ErrorText (int error_code);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: BasePath%440802080302
      STRING_T get_BasePath () const;
      void set_BasePath (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cAbstractFileSystem%440800B203DD.public preserve=yes
      //## end cAbstractFileSystem%440800B203DD.public

  protected:
    // Data Members for Class Attributes

      //## begin cAbstractFileSystem::BasePath%440802080302.attr preserve=no  public: STRING_T {U} 
      STRING_T _BasePath;
      //## end cAbstractFileSystem::BasePath%440802080302.attr

    // Additional Protected Declarations
      //## begin cAbstractFileSystem%440800B203DD.protected preserve=yes
      //## end cAbstractFileSystem%440800B203DD.protected

  private:
    // Additional Private Declarations
      //## begin cAbstractFileSystem%440800B203DD.private preserve=yes
      //## end cAbstractFileSystem%440800B203DD.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cAbstractFileSystem%440800B203DD.implementation preserve=yes
      //## end cAbstractFileSystem%440800B203DD.implementation

};

//## begin cAbstractFileSystem%440800B203DD.postscript preserve=yes
//## end cAbstractFileSystem%440800B203DD.postscript

// Class cAbstractFileSystem 

//## begin module%440800B203DD.epilog preserve=yes
//## end module%440800B203DD.epilog


#endif
