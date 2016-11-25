//## begin module%3B98FB79000E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98FB79000E.cm

//## begin module%3B98FB79000E.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B98FB79000E.cp

//## Module: cDiskFileSystem%3B98FB79000E; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cDiskFileSystem.cpp

//## begin module%3B98FB79000E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B98FB79000E.additionalIncludes

//## begin module%3B98FB79000E.includes preserve=yes
//## end module%3B98FB79000E.includes

// cDiskSource
#include "Dnc/FileSystem/cDiskSource.h"
// cDiskFileSystem
#include "Dnc/FileSystem/cDiskFileSystem.h"
//## begin module%3B98FB79000E.additionalDeclarations preserve=yes
//## end module%3B98FB79000E.additionalDeclarations


// Class cDiskFileSystem 

cDiskFileSystem::cDiskFileSystem()
  //## begin cDiskFileSystem::cDiskFileSystem%.hasinit preserve=no
  //## end cDiskFileSystem::cDiskFileSystem%.hasinit
  //## begin cDiskFileSystem::cDiskFileSystem%.initialization preserve=yes
  //## end cDiskFileSystem::cDiskFileSystem%.initialization
{
  //## begin cDiskFileSystem::cDiskFileSystem%.body preserve=yes
  //## end cDiskFileSystem::cDiskFileSystem%.body
}

cDiskFileSystem::cDiskFileSystem(const cDiskFileSystem &right)
  //## begin cDiskFileSystem::cDiskFileSystem%copy.hasinit preserve=no
  //## end cDiskFileSystem::cDiskFileSystem%copy.hasinit
  //## begin cDiskFileSystem::cDiskFileSystem%copy.initialization preserve=yes
  //## end cDiskFileSystem::cDiskFileSystem%copy.initialization
{
  //## begin cDiskFileSystem::cDiskFileSystem%copy.body preserve=yes
  //## end cDiskFileSystem::cDiskFileSystem%copy.body
}

cDiskFileSystem::cDiskFileSystem (cDiskSource *file_source, CONST_STRING_T path)
  //## begin cDiskFileSystem::cDiskFileSystem%999877037.hasinit preserve=no
  //## end cDiskFileSystem::cDiskFileSystem%999877037.hasinit
  //## begin cDiskFileSystem::cDiskFileSystem%999877037.initialization preserve=yes
   : cFileSystem(path)
  //## end cDiskFileSystem::cDiskFileSystem%999877037.initialization
{
  //## begin cDiskFileSystem::cDiskFileSystem%999877037.body preserve=yes
  //## end cDiskFileSystem::cDiskFileSystem%999877037.body
}


cDiskFileSystem::~cDiskFileSystem()
{
  //## begin cDiskFileSystem::~cDiskFileSystem%.body preserve=yes
  //## end cDiskFileSystem::~cDiskFileSystem%.body
}



//## Other Operations (implementation)
INT_T cDiskFileSystem::Format (INT_T format)
{
  //## begin cDiskFileSystem::Format%1000119093.body preserve=yes
  //## end cDiskFileSystem::Format%1000119093.body
}

INT_T cDiskFileSystem::Directory (STRING_LIST_T &file_names)
{
  //## begin cDiskFileSystem::Directory%1000119094.body preserve=yes
  //## end cDiskFileSystem::Directory%1000119094.body
}

LONG_T cDiskFileSystem::Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cDiskFileSystem::Load%1000119095.body preserve=yes
  //## end cDiskFileSystem::Load%1000119095.body
}

LONG_T cDiskFileSystem::Save (CONST_STRING_T file_name, void *buf, ULONG_T size)
{
  //## begin cDiskFileSystem::Save%1000119096.body preserve=yes
  //## end cDiskFileSystem::Save%1000119096.body
}

INT_T cDiskFileSystem::Delete (CONST_STRING_T file_name)
{
  //## begin cDiskFileSystem::Delete%1000119097.body preserve=yes
  //## end cDiskFileSystem::Delete%1000119097.body
}

LONG_T cDiskFileSystem::FileSize (CONST_STRING_T file_name)
{
  //## begin cDiskFileSystem::FileSize%1000386728.body preserve=yes
  //## end cDiskFileSystem::FileSize%1000386728.body
}

cFile * cDiskFileSystem::File (CONST_STRING_T file_name)
{
  //## begin cDiskFileSystem::File%1000386729.body preserve=yes
  //## end cDiskFileSystem::File%1000386729.body
}

cTimeObject cDiskFileSystem::GetTime (CONST_STRING_T file_name)
{
  //## begin cDiskFileSystem::GetTime%1000456412.body preserve=yes
  //## end cDiskFileSystem::GetTime%1000456412.body
}

// Additional Declarations
  //## begin cDiskFileSystem%3B98FB79000E.declarations preserve=yes
  //## end cDiskFileSystem%3B98FB79000E.declarations

//## begin module%3B98FB79000E.epilog preserve=yes
//## end module%3B98FB79000E.epilog
