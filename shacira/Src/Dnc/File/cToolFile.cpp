//## begin module%3B98E14E0070.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98E14E0070.cm

//## begin module%3B98E14E0070.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98E14E0070.cp

//## Module: cToolFile%3B98E14E0070; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\File\cToolFile.cpp

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
#include "Dnc/File/cToolFile.h"
//## begin module%3B98E14E0070.additionalDeclarations preserve=yes

#define MIN_BUF_SIZE       0x4000

//## end module%3B98E14E0070.additionalDeclarations


// Class cToolFile 



cToolFile::cToolFile()
  //## begin cToolFile::cToolFile%.hasinit preserve=no
      : _FileSystem(NULL)
  //## end cToolFile::cToolFile%.hasinit
  //## begin cToolFile::cToolFile%.initialization preserve=yes
  //## end cToolFile::cToolFile%.initialization
{
  //## begin cToolFile::cToolFile%.body preserve=yes
  //## end cToolFile::cToolFile%.body
}

cToolFile::cToolFile(const cToolFile &right)
  //## begin cToolFile::cToolFile%copy.hasinit preserve=no
      : _FileSystem(NULL)
  //## end cToolFile::cToolFile%copy.hasinit
  //## begin cToolFile::cToolFile%copy.initialization preserve=yes
  //## end cToolFile::cToolFile%copy.initialization
{
  //## begin cToolFile::cToolFile%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cToolFile::cToolFile%copy.body
}

cToolFile::cToolFile (TOOLFILE_HEADER_T *file_header, cToolFileSystem *file_system)
  //## begin cToolFile::cToolFile%999877031.hasinit preserve=no
      : _FileSystem(NULL)
  //## end cToolFile::cToolFile%999877031.hasinit
  //## begin cToolFile::cToolFile%999877031.initialization preserve=yes
  //## end cToolFile::cToolFile%999877031.initialization
{
  //## begin cToolFile::cToolFile%999877031.body preserve=yes
   cToolFileSystem::CopyHeader(&_FileHeader, file_header);
   _FileSystem = file_system;
  //## end cToolFile::cToolFile%999877031.body
}


cToolFile::~cToolFile()
{
  //## begin cToolFile::~cToolFile%.body preserve=yes
  //## end cToolFile::~cToolFile%.body
}



//## Other Operations (implementation)
void cToolFile::Serialize (void * &buf, ULONG_T &buf_size)
{
  //## begin cToolFile::Serialize%1000308631.body preserve=yes
  //## end cToolFile::Serialize%1000308631.body
}

void cToolFile::AddSubFile (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cToolFile::AddSubFile%1062507906.body preserve=yes
  //## end cToolFile::AddSubFile%1062507906.body
}

// Additional Declarations
  //## begin cToolFile%3B98E14E0070.declarations preserve=yes
  //## end cToolFile%3B98E14E0070.declarations

//## begin module%3B98E14E0070.epilog preserve=yes
//## end module%3B98E14E0070.epilog
