//## begin module%3B98E67C02E3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98E67C02E3.cm

//## begin module%3B98E67C02E3.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98E67C02E3.cp

//## Module: cToolFileSource%3B98E67C02E3; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cToolFileSource.cpp

//## begin module%3B98E67C02E3.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B98E67C02E3.additionalIncludes

//## begin module%3B98E67C02E3.includes preserve=yes
//## end module%3B98E67C02E3.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cToolFileSource
#include "Dnc/FileSystem/cToolFileSource.h"
// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"
//## begin module%3B98E67C02E3.additionalDeclarations preserve=yes
//## end module%3B98E67C02E3.additionalDeclarations


// Class cToolFileSource 




cToolFileSource::cToolFileSource()
  //## begin cToolFileSource::cToolFileSource%.hasinit preserve=no
      : _Format(FMT_UNDEFINED)
  //## end cToolFileSource::cToolFileSource%.hasinit
  //## begin cToolFileSource::cToolFileSource%.initialization preserve=yes
  //## end cToolFileSource::cToolFileSource%.initialization
{
  //## begin cToolFileSource::cToolFileSource%.body preserve=yes
  //## end cToolFileSource::cToolFileSource%.body
}

cToolFileSource::cToolFileSource(const cToolFileSource &right)
  //## begin cToolFileSource::cToolFileSource%copy.hasinit preserve=no
      : _Format(FMT_UNDEFINED)
  //## end cToolFileSource::cToolFileSource%copy.hasinit
  //## begin cToolFileSource::cToolFileSource%copy.initialization preserve=yes
  //## end cToolFileSource::cToolFileSource%copy.initialization
{
  //## begin cToolFileSource::cToolFileSource%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cToolFileSource::cToolFileSource%copy.body
}

cToolFileSource::cToolFileSource (CONST_STRING_T path)
  //## begin cToolFileSource::cToolFileSource%999875361.hasinit preserve=no
      : _Format(FMT_UNDEFINED)
  //## end cToolFileSource::cToolFileSource%999875361.hasinit
  //## begin cToolFileSource::cToolFileSource%999875361.initialization preserve=yes
  //## end cToolFileSource::cToolFileSource%999875361.initialization
{
  //## begin cToolFileSource::cToolFileSource%999875361.body preserve=yes
   _Path = path;
  //## end cToolFileSource::cToolFileSource%999875361.body
}


cToolFileSource::~cToolFileSource()
{
  //## begin cToolFileSource::~cToolFileSource%.body preserve=yes
  //## end cToolFileSource::~cToolFileSource%.body
}


//## Get and Set Operations for Class Attributes (implementation)

STRING_T cToolFileSource::get_Path () const
{
  //## begin cToolFileSource::get_Path%3B9CFE4703C0.get preserve=no
  return _Path;
  //## end cToolFileSource::get_Path%3B9CFE4703C0.get
}

INT_T cToolFileSource::get_Format () const
{
  //## begin cToolFileSource::get_Format%3F4F158101B5.get preserve=no
  return _Format;
  //## end cToolFileSource::get_Format%3F4F158101B5.get
}

// Additional Declarations
  //## begin cToolFileSource%3B98E67C02E3.declarations preserve=yes
  //## end cToolFileSource%3B98E67C02E3.declarations

//## begin module%3B98E67C02E3.epilog preserve=yes
//## end module%3B98E67C02E3.epilog
