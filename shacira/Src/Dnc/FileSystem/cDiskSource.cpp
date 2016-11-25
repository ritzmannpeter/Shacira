//## begin module%3B9D038D0187.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9D038D0187.cm

//## begin module%3B9D038D0187.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9D038D0187.cp

//## Module: cDiskSource%3B9D038D0187; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cDiskSource.cpp

//## begin module%3B9D038D0187.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B9D038D0187.additionalIncludes

//## begin module%3B9D038D0187.includes preserve=yes
//## end module%3B9D038D0187.includes

// cDiskSource
#include "Dnc/FileSystem/cDiskSource.h"
//## begin module%3B9D038D0187.additionalDeclarations preserve=yes
//## end module%3B9D038D0187.additionalDeclarations


// Class cDiskSource 

cDiskSource::cDiskSource()
  //## begin cDiskSource::cDiskSource%.hasinit preserve=no
  //## end cDiskSource::cDiskSource%.hasinit
  //## begin cDiskSource::cDiskSource%.initialization preserve=yes
  //## end cDiskSource::cDiskSource%.initialization
{
  //## begin cDiskSource::cDiskSource%.body preserve=yes
  //## end cDiskSource::cDiskSource%.body
}

cDiskSource::cDiskSource(const cDiskSource &right)
  //## begin cDiskSource::cDiskSource%copy.hasinit preserve=no
  //## end cDiskSource::cDiskSource%copy.hasinit
  //## begin cDiskSource::cDiskSource%copy.initialization preserve=yes
  //## end cDiskSource::cDiskSource%copy.initialization
{
  //## begin cDiskSource::cDiskSource%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDiskSource::cDiskSource%copy.body
}

cDiskSource::cDiskSource (CONST_STRING_T path)
  //## begin cDiskSource::cDiskSource%1062078693.hasinit preserve=no
  //## end cDiskSource::cDiskSource%1062078693.hasinit
  //## begin cDiskSource::cDiskSource%1062078693.initialization preserve=yes
  //## end cDiskSource::cDiskSource%1062078693.initialization
{
  //## begin cDiskSource::cDiskSource%1062078693.body preserve=yes
  //## end cDiskSource::cDiskSource%1062078693.body
}


cDiskSource::~cDiskSource()
{
  //## begin cDiskSource::~cDiskSource%.body preserve=yes
  //## end cDiskSource::~cDiskSource%.body
}



//## Other Operations (implementation)
cToolFileSystem * cDiskSource::FileSystem ()
{
  //## begin cDiskSource::FileSystem%1062507917.body preserve=yes
return NULL;
  //## end cDiskSource::FileSystem%1062507917.body
}

// Additional Declarations
  //## begin cDiskSource%3B9D038D0187.declarations preserve=yes
  //## end cDiskSource%3B9D038D0187.declarations

//## begin module%3B9D038D0187.epilog preserve=yes
//## end module%3B9D038D0187.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin cDiskSource::FileSystem%1062507908.body preserve=no
return NULL;
//## end cDiskSource::FileSystem%1062507908.body

#endif
