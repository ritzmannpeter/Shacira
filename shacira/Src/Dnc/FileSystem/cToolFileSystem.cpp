//## begin module%3B98E11000AD.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98E11000AD.cm

//## begin module%3B98E11000AD.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98E11000AD.cp

//## Module: cToolFileSystem%3B98E11000AD; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cToolFileSystem.cpp

//## begin module%3B98E11000AD.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B98E11000AD.additionalIncludes

//## begin module%3B98E11000AD.includes preserve=yes
//## end module%3B98E11000AD.includes

// cToolFileSource
#include "Dnc/FileSystem/cToolFileSource.h"
// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"
// cToolFile
#include "Dnc/File/cToolFile.h"
//## begin module%3B98E11000AD.additionalDeclarations preserve=yes
//## end module%3B98E11000AD.additionalDeclarations


// Class cToolFileSystem 





cToolFileSystem::cToolFileSystem()
  //## begin cToolFileSystem::cToolFileSystem%.hasinit preserve=no
      : _Format(FMT_UNDEFINED)
  //## end cToolFileSystem::cToolFileSystem%.hasinit
  //## begin cToolFileSystem::cToolFileSystem%.initialization preserve=yes
  //## end cToolFileSystem::cToolFileSystem%.initialization
{
  //## begin cToolFileSystem::cToolFileSystem%.body preserve=yes
  //## end cToolFileSystem::cToolFileSystem%.body
}

cToolFileSystem::cToolFileSystem(const cToolFileSystem &right)
  //## begin cToolFileSystem::cToolFileSystem%copy.hasinit preserve=no
      : _Format(FMT_UNDEFINED)
  //## end cToolFileSystem::cToolFileSystem%copy.hasinit
  //## begin cToolFileSystem::cToolFileSystem%copy.initialization preserve=yes
  //## end cToolFileSystem::cToolFileSystem%copy.initialization
{
  //## begin cToolFileSystem::cToolFileSystem%copy.body preserve=yes
  //## end cToolFileSystem::cToolFileSystem%copy.body
}

cToolFileSystem::cToolFileSystem (CONST_STRING_T path)
  //## begin cToolFileSystem::cToolFileSystem%999875360.hasinit preserve=no
      : _Format(FMT_UNDEFINED)
  //## end cToolFileSystem::cToolFileSystem%999875360.hasinit
  //## begin cToolFileSystem::cToolFileSystem%999875360.initialization preserve=yes
  //## end cToolFileSystem::cToolFileSystem%999875360.initialization
{
  //## begin cToolFileSystem::cToolFileSystem%999875360.body preserve=yes
   _Path = path;
  //## end cToolFileSystem::cToolFileSystem%999875360.body
}


cToolFileSystem::~cToolFileSystem()
{
  //## begin cToolFileSystem::~cToolFileSystem%.body preserve=yes
  //## end cToolFileSystem::~cToolFileSystem%.body
}



//## Other Operations (implementation)
TOOLFILE_HEADER_T * cToolFileSystem::AllocHeader (ULONG_T files)
{
  //## begin cToolFileSystem::AllocHeader%1062162394.body preserve=yes
   TOOLFILE_HEADER_T * header = (TOOLFILE_HEADER_T *)cSystemUtils::Alloc(files * (sizeof(TOOLFILE_HEADER_T)));
   for (ULONG_T i=0; i<files; i++) {
      header[i].magic = TOOLFILE_MAGIC;
   }
   return header;
  //## end cToolFileSystem::AllocHeader%1062162394.body
}

void cToolFileSystem::FreeHeader (TOOLFILE_HEADER_T *header)
{
  //## begin cToolFileSystem::FreeHeader%1062162395.body preserve=yes
   cSystemUtils::Free(header);
  //## end cToolFileSystem::FreeHeader%1062162395.body
}

void cToolFileSystem::CopyHeader (TOOLFILE_HEADER_T *dst, TOOLFILE_HEADER_T *src)
{
  //## begin cToolFileSystem::CopyHeader%1062507907.body preserve=yes
   memcpy(dst, src, sizeof(TOOLFILE_HEADER_T));
  //## end cToolFileSystem::CopyHeader%1062507907.body
}

//## Get and Set Operations for Class Attributes (implementation)

INT_T cToolFileSystem::get_Format () const
{
  //## begin cToolFileSystem::get_Format%3B9DD8F30280.get preserve=no
  return _Format;
  //## end cToolFileSystem::get_Format%3B9DD8F30280.get
}

STRING_T cToolFileSystem::get_Path () const
{
  //## begin cToolFileSystem::get_Path%3BA0C4F102CE.get preserve=no
  return _Path;
  //## end cToolFileSystem::get_Path%3BA0C4F102CE.get
}

// Additional Declarations
  //## begin cToolFileSystem%3B98E11000AD.declarations preserve=yes
  //## end cToolFileSystem%3B98E11000AD.declarations

//## begin module%3B98E11000AD.epilog preserve=yes
//## end module%3B98E11000AD.epilog
