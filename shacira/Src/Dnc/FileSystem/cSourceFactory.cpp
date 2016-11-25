//## begin module%3F4DFB980290.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4DFB980290.cm

//## begin module%3F4DFB980290.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3F4DFB980290.cp

//## Module: cSourceFactory%3F4DFB980290; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cSourceFactory.cpp

//## begin module%3F4DFB980290.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F4DFB980290.additionalIncludes

//## begin module%3F4DFB980290.includes preserve=yes
//## end module%3F4DFB980290.includes

// cSourceFactory
#include "Dnc/FileSystem/cSourceFactory.h"
// cFTPSource
#include "Dnc/FileSystem/cFTPSource.h"
// cDiskSource
#include "Dnc/FileSystem/cDiskSource.h"
// cCellSource
#include "Dnc/FileSystem/cCellSource.h"
// cCarrierSource
#include "Dnc/FileSystem/cCarrierSource.h"
// cToolFileSource
#include "Dnc/FileSystem/cToolFileSource.h"
//## begin module%3F4DFB980290.additionalDeclarations preserve=yes
//## end module%3F4DFB980290.additionalDeclarations


// Class cSourceFactory 

cSourceFactory::cSourceFactory()
  //## begin cSourceFactory::cSourceFactory%.hasinit preserve=no
  //## end cSourceFactory::cSourceFactory%.hasinit
  //## begin cSourceFactory::cSourceFactory%.initialization preserve=yes
  //## end cSourceFactory::cSourceFactory%.initialization
{
  //## begin cSourceFactory::cSourceFactory%.body preserve=yes
_ASSERT_UNCOND
  //## end cSourceFactory::cSourceFactory%.body
}

cSourceFactory::cSourceFactory(const cSourceFactory &right)
  //## begin cSourceFactory::cSourceFactory%copy.hasinit preserve=no
  //## end cSourceFactory::cSourceFactory%copy.hasinit
  //## begin cSourceFactory::cSourceFactory%copy.initialization preserve=yes
  //## end cSourceFactory::cSourceFactory%copy.initialization
{
  //## begin cSourceFactory::cSourceFactory%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSourceFactory::cSourceFactory%copy.body
}


cSourceFactory::~cSourceFactory()
{
  //## begin cSourceFactory::~cSourceFactory%.body preserve=yes
  //## end cSourceFactory::~cSourceFactory%.body
}



//## Other Operations (implementation)
cToolFileSource * cSourceFactory::CreateSource (CONST_STRING_T path)
{
  //## begin cSourceFactory::CreateSource%1062075838.body preserve=yes
   if (path != NULL) {
      if (strcmp(path, "CARRIER") == 0) {
         return new cCarrierSource(path);
      }
   } else {
      return new cDiskSource;
   }
   return NULL;
  //## end cSourceFactory::CreateSource%1062075838.body
}

// Additional Declarations
  //## begin cSourceFactory%3F4DFB980290.declarations preserve=yes
  //## end cSourceFactory%3F4DFB980290.declarations

//## begin module%3F4DFB980290.epilog preserve=yes
//## end module%3F4DFB980290.epilog
