//## begin module%3B98FB79000E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B98FB79000E.cm

//## begin module%3B98FB79000E.cp preserve=no
//## end module%3B98FB79000E.cp

//## Module: cDiskDirectory%3B98FB79000E; Pseudo Package body
//## Source file: d:\usr\prj\ls2i\src\Dnc\FileSystem\cDiskDirectory.cpp

//## begin module%3B98FB79000E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B98FB79000E.additionalIncludes

//## begin module%3B98FB79000E.includes preserve=yes

#ifndef __PLATFORM_DEFINED__
#error "platform not defined"
#endif

//## end module%3B98FB79000E.includes

// cDiskDirectory
#include "Dnc\FileSystem\cDiskDirectory.h"
//## begin module%3B98FB79000E.additionalDeclarations preserve=yes
//## end module%3B98FB79000E.additionalDeclarations


// Class cDiskDirectory 

cDiskDirectory::cDiskDirectory()
  //## begin cDiskDirectory::cDiskDirectory%.hasinit preserve=no
  //## end cDiskDirectory::cDiskDirectory%.hasinit
  //## begin cDiskDirectory::cDiskDirectory%.initialization preserve=yes
  //## end cDiskDirectory::cDiskDirectory%.initialization
{
  //## begin cDiskDirectory::cDiskDirectory%.body preserve=yes
  //## end cDiskDirectory::cDiskDirectory%.body
}

cDiskDirectory::cDiskDirectory(const cDiskDirectory &right)
  //## begin cDiskDirectory::cDiskDirectory%copy.hasinit preserve=no
  //## end cDiskDirectory::cDiskDirectory%copy.hasinit
  //## begin cDiskDirectory::cDiskDirectory%copy.initialization preserve=yes
  //## end cDiskDirectory::cDiskDirectory%copy.initialization
{
  //## begin cDiskDirectory::cDiskDirectory%copy.body preserve=yes
  //## end cDiskDirectory::cDiskDirectory%copy.body
}

cDiskDirectory::cDiskDirectory (cFileSystem *file_system, CONST_STRING_T path)
  //## begin cDiskDirectory::cDiskDirectory%999877037.hasinit preserve=no
  //## end cDiskDirectory::cDiskDirectory%999877037.hasinit
  //## begin cDiskDirectory::cDiskDirectory%999877037.initialization preserve=yes
   : cDirectory(file_system, path)
  //## end cDiskDirectory::cDiskDirectory%999877037.initialization
{
  //## begin cDiskDirectory::cDiskDirectory%999877037.body preserve=yes
  //## end cDiskDirectory::cDiskDirectory%999877037.body
}


cDiskDirectory::~cDiskDirectory()
{
  //## begin cDiskDirectory::~cDiskDirectory%.body preserve=yes
  //## end cDiskDirectory::~cDiskDirectory%.body
}


// Additional Declarations
  //## begin cDiskDirectory%3B98FB79000E.declarations preserve=yes
  //## end cDiskDirectory%3B98FB79000E.declarations

//## begin module%3B98FB79000E.epilog preserve=yes
//## end module%3B98FB79000E.epilog
