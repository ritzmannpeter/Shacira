//## begin module%3B99015D0356.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B99015D0356.cm

//## begin module%3B99015D0356.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B99015D0356.cp

//## Module: cCellFileSystem%3B99015D0356; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCellFileSystem.cpp

//## begin module%3B99015D0356.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B99015D0356.additionalIncludes

//## begin module%3B99015D0356.includes preserve=yes
//## end module%3B99015D0356.includes

// cCellSource
#include "Dnc/FileSystem/cCellSource.h"
// cCellFileSystem
#include "Dnc/FileSystem/cCellFileSystem.h"
//## begin module%3B99015D0356.additionalDeclarations preserve=yes
//## end module%3B99015D0356.additionalDeclarations


// Class cCellFileSystem 

cCellFileSystem::cCellFileSystem()
  //## begin cCellFileSystem::cCellFileSystem%.hasinit preserve=no
  //## end cCellFileSystem::cCellFileSystem%.hasinit
  //## begin cCellFileSystem::cCellFileSystem%.initialization preserve=yes
  //## end cCellFileSystem::cCellFileSystem%.initialization
{
  //## begin cCellFileSystem::cCellFileSystem%.body preserve=yes
  //## end cCellFileSystem::cCellFileSystem%.body
}

cCellFileSystem::cCellFileSystem(const cCellFileSystem &right)
  //## begin cCellFileSystem::cCellFileSystem%copy.hasinit preserve=no
  //## end cCellFileSystem::cCellFileSystem%copy.hasinit
  //## begin cCellFileSystem::cCellFileSystem%copy.initialization preserve=yes
  //## end cCellFileSystem::cCellFileSystem%copy.initialization
{
  //## begin cCellFileSystem::cCellFileSystem%copy.body preserve=yes
  //## end cCellFileSystem::cCellFileSystem%copy.body
}

cCellFileSystem::cCellFileSystem (cCellSource *file_source, CONST_STRING_T path)
  //## begin cCellFileSystem::cCellFileSystem%999877038.hasinit preserve=no
  //## end cCellFileSystem::cCellFileSystem%999877038.hasinit
  //## begin cCellFileSystem::cCellFileSystem%999877038.initialization preserve=yes
   : cFileSystem(path)
  //## end cCellFileSystem::cCellFileSystem%999877038.initialization
{
  //## begin cCellFileSystem::cCellFileSystem%999877038.body preserve=yes
  //## end cCellFileSystem::cCellFileSystem%999877038.body
}


cCellFileSystem::~cCellFileSystem()
{
  //## begin cCellFileSystem::~cCellFileSystem%.body preserve=yes
  //## end cCellFileSystem::~cCellFileSystem%.body
}


const cCellFileSystem & cCellFileSystem::operator=(const cCellFileSystem &right)
{
  //## begin cCellFileSystem::operator=%.body preserve=yes
  //## end cCellFileSystem::operator=%.body
}


INT_T cCellFileSystem::operator==(const cCellFileSystem &right) const
{
  //## begin cCellFileSystem::operator==%.body preserve=yes
  //## end cCellFileSystem::operator==%.body
}

INT_T cCellFileSystem::operator!=(const cCellFileSystem &right) const
{
  //## begin cCellFileSystem::operator!=%.body preserve=yes
  //## end cCellFileSystem::operator!=%.body
}



//## Other Operations (implementation)
INT_T cCellFileSystem::Format (INT_T format)
{
  //## begin cCellFileSystem::Format%1000119083.body preserve=yes
  //## end cCellFileSystem::Format%1000119083.body
}

INT_T cCellFileSystem::Directory (STRING_LIST_T &file_names)
{
  //## begin cCellFileSystem::Directory%1000119084.body preserve=yes
  //## end cCellFileSystem::Directory%1000119084.body
}

LONG_T cCellFileSystem::Load (CONST_STRING_T file_name, void *buf, ULONG_T size)
{
  //## begin cCellFileSystem::Load%1000119085.body preserve=yes
  //## end cCellFileSystem::Load%1000119085.body
}

LONG_T cCellFileSystem::Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size)
{
  //## begin cCellFileSystem::Save%1000119086.body preserve=yes
  //## end cCellFileSystem::Save%1000119086.body
}

INT_T cCellFileSystem::Delete (CONST_STRING_T file_name)
{
  //## begin cCellFileSystem::Delete%1000119087.body preserve=yes
  //## end cCellFileSystem::Delete%1000119087.body
}

LONG_T cCellFileSystem::FileSize (CONST_STRING_T file_name)
{
  //## begin cCellFileSystem::FileSize%1000386736.body preserve=yes
  //## end cCellFileSystem::FileSize%1000386736.body
}

cFile * cCellFileSystem::File (CONST_STRING_T file_name)
{
  //## begin cCellFileSystem::File%1000386737.body preserve=yes
  //## end cCellFileSystem::File%1000386737.body
}

cTimeObject cCellFileSystem::GetTime (CONST_STRING_T file_name)
{
  //## begin cCellFileSystem::GetTime%1000456416.body preserve=yes
  //## end cCellFileSystem::GetTime%1000456416.body
}

// Additional Declarations
  //## begin cCellFileSystem%3B99015D0356.declarations preserve=yes
  //## end cCellFileSystem%3B99015D0356.declarations

//## begin module%3B99015D0356.epilog preserve=yes
//## end module%3B99015D0356.epilog
