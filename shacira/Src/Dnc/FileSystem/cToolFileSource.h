//## begin module%3B98E67C02E3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98E67C02E3.cm

//## begin module%3B98E67C02E3.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98E67C02E3.cp

//## Module: cToolFileSource%3B98E67C02E3; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cToolFileSource.h

#ifndef cToolFileSource_h
#define cToolFileSource_h 1

//## begin module%3B98E67C02E3.includes preserve=yes

#include "Dnc/ToolFiles.h"

//## end module%3B98E67C02E3.includes


class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cToolFileSystem;

//## begin module%3B98E67C02E3.additionalDeclarations preserve=yes
//## end module%3B98E67C02E3.additionalDeclarations


//## begin cToolFileSource%3B98E67C02E3.preface preserve=yes
//## end cToolFileSource%3B98E67C02E3.preface

//## Class: cToolFileSource%3B98E67C02E3
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B9DC9D103DE;cToolFileSystem { -> F}
//## Uses: <unnamed>%3BA0C04B03C7;cFileSystemUtils { -> F}

class __DLL_EXPORT__ cToolFileSource 
{
  //## begin cToolFileSource%3B98E67C02E3.initialDeclarations preserve=yes
public:
  //## end cToolFileSource%3B98E67C02E3.initialDeclarations

    //## Constructors (generated)
      cToolFileSource();

      cToolFileSource(const cToolFileSource &right);

    //## Constructors (specified)
      //## Operation: cToolFileSource%999875361
      cToolFileSource (CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cToolFileSource();


    //## Other Operations (specified)
      //## Operation: FileSystem%999875363
      virtual cToolFileSystem * FileSystem () = 0;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Path%3B9CFE4703C0
      STRING_T get_Path () const;

      //## Attribute: Format%3F4F158101B5
      INT_T get_Format () const;

  public:
    // Additional Public Declarations
      //## begin cToolFileSource%3B98E67C02E3.public preserve=yes
      //## end cToolFileSource%3B98E67C02E3.public

  protected:
    // Data Members for Class Attributes

      //## begin cToolFileSource::Path%3B9CFE4703C0.attr preserve=no  public: STRING_T {U} 
      STRING_T _Path;
      //## end cToolFileSource::Path%3B9CFE4703C0.attr

      //## begin cToolFileSource::Format%3F4F158101B5.attr preserve=no  public: INT_T {U} FMT_UNDEFINED
      INT_T _Format;
      //## end cToolFileSource::Format%3F4F158101B5.attr

    // Additional Protected Declarations
      //## begin cToolFileSource%3B98E67C02E3.protected preserve=yes
      //## end cToolFileSource%3B98E67C02E3.protected

  private:
    // Additional Private Declarations
      //## begin cToolFileSource%3B98E67C02E3.private preserve=yes
      //## end cToolFileSource%3B98E67C02E3.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cToolFileSource%3B98E67C02E3.implementation preserve=yes
      //## end cToolFileSource%3B98E67C02E3.implementation

};

//## begin cToolFileSource%3B98E67C02E3.postscript preserve=yes
//## end cToolFileSource%3B98E67C02E3.postscript

// Class cToolFileSource 

//## begin module%3B98E67C02E3.epilog preserve=yes
//## end module%3B98E67C02E3.epilog


#endif
