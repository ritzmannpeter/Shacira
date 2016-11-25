//## begin module%3BAB6CA103C2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BAB6CA103C2.cm

//## begin module%3BAB6CA103C2.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BAB6CA103C2.cp

//## Module: cFTPFileSystem%3BAB6CA103C2; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cFTPFileSystem.cpp

//## begin module%3BAB6CA103C2.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BAB6CA103C2.additionalIncludes

//## begin module%3BAB6CA103C2.includes preserve=yes
//## end module%3BAB6CA103C2.includes

// cFTPFileSystem
#include "Dnc/FileSystem/cFTPFileSystem.h"
// cFTPSource
#include "Dnc/FileSystem/cFTPSource.h"
//## begin module%3BAB6CA103C2.additionalDeclarations preserve=yes
//## end module%3BAB6CA103C2.additionalDeclarations


// Class cFTPFileSystem 

cFTPFileSystem::cFTPFileSystem()
  //## begin cFTPFileSystem::cFTPFileSystem%.hasinit preserve=no
  //## end cFTPFileSystem::cFTPFileSystem%.hasinit
  //## begin cFTPFileSystem::cFTPFileSystem%.initialization preserve=yes
  //## end cFTPFileSystem::cFTPFileSystem%.initialization
{
  //## begin cFTPFileSystem::cFTPFileSystem%.body preserve=yes
  //## end cFTPFileSystem::cFTPFileSystem%.body
}

cFTPFileSystem::cFTPFileSystem(const cFTPFileSystem &right)
  //## begin cFTPFileSystem::cFTPFileSystem%copy.hasinit preserve=no
  //## end cFTPFileSystem::cFTPFileSystem%copy.hasinit
  //## begin cFTPFileSystem::cFTPFileSystem%copy.initialization preserve=yes
  //## end cFTPFileSystem::cFTPFileSystem%copy.initialization
{
  //## begin cFTPFileSystem::cFTPFileSystem%copy.body preserve=yes
  //## end cFTPFileSystem::cFTPFileSystem%copy.body
}

cFTPFileSystem::cFTPFileSystem (cFTPSource *file_source, CONST_STRING_T path)
  //## begin cFTPFileSystem::cFTPFileSystem%1001090078.hasinit preserve=no
  //## end cFTPFileSystem::cFTPFileSystem%1001090078.hasinit
  //## begin cFTPFileSystem::cFTPFileSystem%1001090078.initialization preserve=yes
  //## end cFTPFileSystem::cFTPFileSystem%1001090078.initialization
{
  //## begin cFTPFileSystem::cFTPFileSystem%1001090078.body preserve=yes
  //## end cFTPFileSystem::cFTPFileSystem%1001090078.body
}


cFTPFileSystem::~cFTPFileSystem()
{
  //## begin cFTPFileSystem::~cFTPFileSystem%.body preserve=yes
  //## end cFTPFileSystem::~cFTPFileSystem%.body
}



//## Other Operations (implementation)
INT_T cFTPFileSystem::Format (INT_T format)
{
  //## begin cFTPFileSystem::Format%1001090079.body preserve=yes
  //## end cFTPFileSystem::Format%1001090079.body
}

INT_T cFTPFileSystem::Directory (STRING_LIST_T &file_names)
{
  //## begin cFTPFileSystem::Directory%1001090080.body preserve=yes
  //## end cFTPFileSystem::Directory%1001090080.body
}

LONG_T cFTPFileSystem::Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cFTPFileSystem::Load%1001090081.body preserve=yes
  //## end cFTPFileSystem::Load%1001090081.body
}

LONG_T cFTPFileSystem::Save (CONST_STRING_T file_name, void *buf, ULONG_T size)
{
  //## begin cFTPFileSystem::Save%1001090082.body preserve=yes
  //## end cFTPFileSystem::Save%1001090082.body
}

INT_T cFTPFileSystem::Delete (CONST_STRING_T file_name)
{
  //## begin cFTPFileSystem::Delete%1001090083.body preserve=yes
  //## end cFTPFileSystem::Delete%1001090083.body
}

LONG_T cFTPFileSystem::FileSize (CONST_STRING_T file_name)
{
  //## begin cFTPFileSystem::FileSize%1001090084.body preserve=yes
  //## end cFTPFileSystem::FileSize%1001090084.body
}

cFile * cFTPFileSystem::File (CONST_STRING_T file_name)
{
  //## begin cFTPFileSystem::File%1001090085.body preserve=yes
  //## end cFTPFileSystem::File%1001090085.body
}

cTimeObject cFTPFileSystem::GetTime (CONST_STRING_T file_name)
{
  //## begin cFTPFileSystem::GetTime%1001090086.body preserve=yes
  //## end cFTPFileSystem::GetTime%1001090086.body
}

// Additional Declarations
  //## begin cFTPFileSystem%3BAB6CA103C2.declarations preserve=yes
  //## end cFTPFileSystem%3BAB6CA103C2.declarations

//## begin module%3BAB6CA103C2.epilog preserve=yes
//## end module%3BAB6CA103C2.epilog
