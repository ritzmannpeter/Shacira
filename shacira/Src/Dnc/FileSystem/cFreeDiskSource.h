//## begin module%3BA0C0600038.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA0C0600038.cm

//## begin module%3BA0C0600038.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA0C0600038.cp

//## Module: cFreeDiskSource%3BA0C0600038; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cFreeDiskSource.h

#ifndef cFreeDiskSource_h
#define cFreeDiskSource_h 1

//## begin module%3BA0C0600038.includes preserve=yes
//## end module%3BA0C0600038.includes

// cToolFileSource
#include "Dnc/FileSystem/cToolFileSource.h"

class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cFreeDiskFileSystem;

//## begin module%3BA0C0600038.additionalDeclarations preserve=yes
//## end module%3BA0C0600038.additionalDeclarations


//## begin cFreeDiskSource%3BA0C0600038.preface preserve=yes
//## end cFreeDiskSource%3BA0C0600038.preface

//## Class: cFreeDiskSource%3BA0C0600038
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BA0C29300BA;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3BAB6E3502DC;cFreeDiskFileSystem { -> F}

class __DLL_EXPORT__ cFreeDiskSource : public cToolFileSource  //## Inherits: <unnamed>%3BA0C0AF0046
{
  //## begin cFreeDiskSource%3BA0C0600038.initialDeclarations preserve=yes
  //## end cFreeDiskSource%3BA0C0600038.initialDeclarations

    //## Constructors (generated)
      cFreeDiskSource();

      cFreeDiskSource(const cFreeDiskSource &right);

    //## Constructors (specified)
      //## Operation: cFreeDiskSource%1000386744
      cFreeDiskSource (CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cFreeDiskSource();


    //## Other Operations (specified)
      //## Operation: FileSystem%1000386740
      virtual cFileSystem * FileSystem ();

  public:
    // Additional Public Declarations
      //## begin cFreeDiskSource%3BA0C0600038.public preserve=yes
      //## end cFreeDiskSource%3BA0C0600038.public

  protected:
    // Additional Protected Declarations
      //## begin cFreeDiskSource%3BA0C0600038.protected preserve=yes
      //## end cFreeDiskSource%3BA0C0600038.protected

  private:
    // Additional Private Declarations
      //## begin cFreeDiskSource%3BA0C0600038.private preserve=yes
      //## end cFreeDiskSource%3BA0C0600038.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cFreeDiskSource%3BA0C0600038.implementation preserve=yes
      //## end cFreeDiskSource%3BA0C0600038.implementation

};

//## begin cFreeDiskSource%3BA0C0600038.postscript preserve=yes
//## end cFreeDiskSource%3BA0C0600038.postscript

// Class cFreeDiskSource 

//## begin module%3BA0C0600038.epilog preserve=yes
//## end module%3BA0C0600038.epilog


#endif
