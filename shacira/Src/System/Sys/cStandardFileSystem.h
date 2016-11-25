//## begin module%440802CA0370.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%440802CA0370.cm

//## begin module%440802CA0370.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%440802CA0370.cp

//## Module: cStandardFileSystem%440802CA0370; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Sys\cStandardFileSystem.h

#ifndef cStandardFileSystem_h
#define cStandardFileSystem_h 1

//## begin module%440802CA0370.includes preserve=yes
//## end module%440802CA0370.includes

// cAbstractFileSystem
#include "System/Sys/cAbstractFileSystem.h"

class __DLL_EXPORT__ cSHFile;

//## begin module%440802CA0370.additionalDeclarations preserve=yes
//## end module%440802CA0370.additionalDeclarations


//## begin cStandardFileSystem%440802CA0370.preface preserve=yes
//## end cStandardFileSystem%440802CA0370.preface

//## Class: cStandardFileSystem%440802CA0370
//## Category: System::Sys%3E5A1D1800A3
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%44080B90039F;cSHFile { -> F}

class __DLL_EXPORT__ cStandardFileSystem : public cAbstractFileSystem  //## Inherits: <unnamed>%440802FB01BA
{
  //## begin cStandardFileSystem%440802CA0370.initialDeclarations preserve=yes
public:
  //## end cStandardFileSystem%440802CA0370.initialDeclarations

    //## Constructors (generated)
      cStandardFileSystem();

      cStandardFileSystem(const cStandardFileSystem &right);

    //## Destructor (generated)
      virtual ~cStandardFileSystem();


    //## Other Operations (specified)
      //## Operation: Scan%1141375549
      virtual ULONG_T Scan (STRING_LIST_T &file_names, CONST_STRING_T pattern);

      //## Operation: Get%1141375550
      virtual int Get (CONST_STRING_T path, STRING_T &buffer, ULONG_T flags);

      //## Operation: Put%1141375551
      virtual int Put (CONST_STRING_T path, CONST_STRING_T text, ULONG_T flags);

      //## Operation: Rename%1141375552
      virtual BOOL_T Rename (CONST_STRING_T path, CONST_STRING_T new_path, ULONG_T flags);

      //## Operation: RemoveFile
      virtual int RemoveFile (CONST_STRING_T path);

      //## Operation: ErrorText%1166170817
      virtual CONST_STRING_T ErrorText (int error_code);

  public:
    // Additional Public Declarations
      //## begin cStandardFileSystem%440802CA0370.public preserve=yes
      //## end cStandardFileSystem%440802CA0370.public

  protected:
    // Additional Protected Declarations
      //## begin cStandardFileSystem%440802CA0370.protected preserve=yes
      //## end cStandardFileSystem%440802CA0370.protected

  private:
    // Additional Private Declarations
      //## begin cStandardFileSystem%440802CA0370.private preserve=yes
      //## end cStandardFileSystem%440802CA0370.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cStandardFileSystem%440802CA0370.implementation preserve=yes
      //## end cStandardFileSystem%440802CA0370.implementation

};

//## begin cStandardFileSystem%440802CA0370.postscript preserve=yes
//## end cStandardFileSystem%440802CA0370.postscript

// Class cStandardFileSystem 

//## begin module%440802CA0370.epilog preserve=yes
//## end module%440802CA0370.epilog


#endif
