//## begin module%3BA0C0600038.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3BA0C0600038.cm

//## begin module%3BA0C0600038.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3BA0C0600038.cp

//## Module: cFreeDiskSource%3BA0C0600038; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cFreeDiskSource.cpp

//## begin module%3BA0C0600038.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3BA0C0600038.additionalIncludes

//## begin module%3BA0C0600038.includes preserve=yes
//## end module%3BA0C0600038.includes

// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cFreeDiskSource
#include "Dnc/FileSystem/cFreeDiskSource.h"
// cFreeDiskFileSystem
#include "Dnc/FileSystem/cFreeDiskFileSystem.h"
//## begin module%3BA0C0600038.additionalDeclarations preserve=yes
//## end module%3BA0C0600038.additionalDeclarations


// Class cFreeDiskSource 

cFreeDiskSource::cFreeDiskSource()
  //## begin cFreeDiskSource::cFreeDiskSource%.hasinit preserve=no
  //## end cFreeDiskSource::cFreeDiskSource%.hasinit
  //## begin cFreeDiskSource::cFreeDiskSource%.initialization preserve=yes
  //## end cFreeDiskSource::cFreeDiskSource%.initialization
{
  //## begin cFreeDiskSource::cFreeDiskSource%.body preserve=yes
  //## end cFreeDiskSource::cFreeDiskSource%.body
}

cFreeDiskSource::cFreeDiskSource(const cFreeDiskSource &right)
  //## begin cFreeDiskSource::cFreeDiskSource%copy.hasinit preserve=no
  //## end cFreeDiskSource::cFreeDiskSource%copy.hasinit
  //## begin cFreeDiskSource::cFreeDiskSource%copy.initialization preserve=yes
  //## end cFreeDiskSource::cFreeDiskSource%copy.initialization
{
  //## begin cFreeDiskSource::cFreeDiskSource%copy.body preserve=yes
  //## end cFreeDiskSource::cFreeDiskSource%copy.body
}

cFreeDiskSource::cFreeDiskSource (CONST_STRING_T path)
  //## begin cFreeDiskSource::cFreeDiskSource%1000386744.hasinit preserve=no
  //## end cFreeDiskSource::cFreeDiskSource%1000386744.hasinit
  //## begin cFreeDiskSource::cFreeDiskSource%1000386744.initialization preserve=yes
   : cFileSource(path)
  //## end cFreeDiskSource::cFreeDiskSource%1000386744.initialization
{
  //## begin cFreeDiskSource::cFreeDiskSource%1000386744.body preserve=yes
  //## end cFreeDiskSource::cFreeDiskSource%1000386744.body
}


cFreeDiskSource::~cFreeDiskSource()
{
  //## begin cFreeDiskSource::~cFreeDiskSource%.body preserve=yes
  //## end cFreeDiskSource::~cFreeDiskSource%.body
}



//## Other Operations (implementation)
cFileSystem * cFreeDiskSource::FileSystem ()
{
  //## begin cFreeDiskSource::FileSystem%1000386740.body preserve=yes
   if (cFileSystemUtils::DirExists(_Path.c_str())) {
      return new cFreeDiskFileSystem(this, _Path.c_str());
   } else {
      _LastError = FSYS_NOT_PRESENT;
      return NULL;
   }
  //## end cFreeDiskSource::FileSystem%1000386740.body
}

// Additional Declarations
  //## begin cFreeDiskSource%3BA0C0600038.declarations preserve=yes
  //## end cFreeDiskSource%3BA0C0600038.declarations

//## begin module%3BA0C0600038.epilog preserve=yes
//## end module%3BA0C0600038.epilog
