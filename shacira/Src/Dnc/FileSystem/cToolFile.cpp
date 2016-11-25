//## begin module%3B98E14E0070.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98E14E0070.cm

//## begin module%3B98E14E0070.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98E14E0070.cp

//## Module: cToolFile%3B98E14E0070; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cToolFile.cpp

//## begin module%3B98E14E0070.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B98E14E0070.additionalIncludes

//## begin module%3B98E14E0070.includes preserve=yes
//## end module%3B98E14E0070.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"
// cToolFile
#include "Dnc/FileSystem/cToolFile.h"
//## begin module%3B98E14E0070.additionalDeclarations preserve=yes
//## end module%3B98E14E0070.additionalDeclarations


// Class cToolFile 




cToolFile::cToolFile()
  //## begin cToolFile::cToolFile%.hasinit preserve=no
      : _FileSystem(NULL), _FileBuffer(NULL)
  //## end cToolFile::cToolFile%.hasinit
  //## begin cToolFile::cToolFile%.initialization preserve=yes
  //## end cToolFile::cToolFile%.initialization
{
  //## begin cToolFile::cToolFile%.body preserve=yes
  //## end cToolFile::cToolFile%.body
}

cToolFile::cToolFile(const cToolFile &right)
  //## begin cToolFile::cToolFile%copy.hasinit preserve=no
      : _FileSystem(NULL), _FileBuffer(NULL)
  //## end cToolFile::cToolFile%copy.hasinit
  //## begin cToolFile::cToolFile%copy.initialization preserve=yes
  //## end cToolFile::cToolFile%copy.initialization
{
  //## begin cToolFile::cToolFile%copy.body preserve=yes
  //## end cToolFile::cToolFile%copy.body
}

cToolFile::cToolFile (CONST_STRING_T name, cToolFileSystem *file_system)
  //## begin cToolFile::cToolFile%999877031.hasinit preserve=no
      : _FileSystem(NULL), _FileBuffer(NULL)
  //## end cToolFile::cToolFile%999877031.hasinit
  //## begin cToolFile::cToolFile%999877031.initialization preserve=yes
  //## end cToolFile::cToolFile%999877031.initialization
{
  //## begin cToolFile::cToolFile%999877031.body preserve=yes
  //## end cToolFile::cToolFile%999877031.body
}


cToolFile::~cToolFile()
{
  //## begin cToolFile::~cToolFile%.body preserve=yes
  //## end cToolFile::~cToolFile%.body
}



//## Other Operations (implementation)
INT_T cToolFile::GetBuf (void * &buf, ULONG_T &buf_size)
{
  //## begin cToolFile::GetBuf%1000308631.body preserve=yes
  //## end cToolFile::GetBuf%1000308631.body
}

// Additional Declarations
  //## begin cToolFile%3B98E14E0070.declarations preserve=yes
  //## end cToolFile%3B98E14E0070.declarations

//## begin module%3B98E14E0070.epilog preserve=yes
//## end module%3B98E14E0070.epilog
