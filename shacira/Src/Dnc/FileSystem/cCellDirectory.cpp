//## begin module%3B99015D0356.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B99015D0356.cm

//## begin module%3B99015D0356.cp preserve=no
//## end module%3B99015D0356.cp

//## Module: cCellDirectory%3B99015D0356; Pseudo Package body
//## Source file: d:\usr\prj\ls2i\src\Dnc\FileSystem\cCellDirectory.cpp

//## begin module%3B99015D0356.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B99015D0356.additionalIncludes

//## begin module%3B99015D0356.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

//## end module%3B99015D0356.includes

// cCellDirectory
#include "Dnc\FileSystem\cCellDirectory.h"
//## begin module%3B99015D0356.additionalDeclarations preserve=yes
//## end module%3B99015D0356.additionalDeclarations


// Class cCellDirectory 

cCellDirectory::cCellDirectory()
  //## begin cCellDirectory::cCellDirectory%.hasinit preserve=no
  //## end cCellDirectory::cCellDirectory%.hasinit
  //## begin cCellDirectory::cCellDirectory%.initialization preserve=yes
  //## end cCellDirectory::cCellDirectory%.initialization
{
  //## begin cCellDirectory::cCellDirectory%.body preserve=yes
  //## end cCellDirectory::cCellDirectory%.body
}

cCellDirectory::cCellDirectory(const cCellDirectory &right)
  //## begin cCellDirectory::cCellDirectory%copy.hasinit preserve=no
  //## end cCellDirectory::cCellDirectory%copy.hasinit
  //## begin cCellDirectory::cCellDirectory%copy.initialization preserve=yes
  //## end cCellDirectory::cCellDirectory%copy.initialization
{
  //## begin cCellDirectory::cCellDirectory%copy.body preserve=yes
  //## end cCellDirectory::cCellDirectory%copy.body
}

cCellDirectory::cCellDirectory (cFileSystem *file_system, CONST_STRING_T path)
  //## begin cCellDirectory::cCellDirectory%999877038.hasinit preserve=no
  //## end cCellDirectory::cCellDirectory%999877038.hasinit
  //## begin cCellDirectory::cCellDirectory%999877038.initialization preserve=yes
   : cDirectory(file_system, path)
  //## end cCellDirectory::cCellDirectory%999877038.initialization
{
  //## begin cCellDirectory::cCellDirectory%999877038.body preserve=yes
  //## end cCellDirectory::cCellDirectory%999877038.body
}


cCellDirectory::~cCellDirectory()
{
  //## begin cCellDirectory::~cCellDirectory%.body preserve=yes
  //## end cCellDirectory::~cCellDirectory%.body
}


const cCellDirectory & cCellDirectory::operator=(const cCellDirectory &right)
{
  //## begin cCellDirectory::operator=%.body preserve=yes
  //## end cCellDirectory::operator=%.body
}


int cCellDirectory::operator==(const cCellDirectory &right) const
{
  //## begin cCellDirectory::operator==%.body preserve=yes
  //## end cCellDirectory::operator==%.body
}

int cCellDirectory::operator!=(const cCellDirectory &right) const
{
  //## begin cCellDirectory::operator!=%.body preserve=yes
  //## end cCellDirectory::operator!=%.body
}


// Additional Declarations
  //## begin cCellDirectory%3B99015D0356.declarations preserve=yes
  //## end cCellDirectory%3B99015D0356.declarations

//## begin module%3B99015D0356.epilog preserve=yes
//## end module%3B99015D0356.epilog
