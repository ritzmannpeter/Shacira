//## begin module%3B9D035D003D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9D035D003D.cm

//## begin module%3B9D035D003D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9D035D003D.cp

//## Module: cCarrierSource%3B9D035D003D; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCarrierSource.cpp

//## begin module%3B9D035D003D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3B9D035D003D.additionalIncludes

//## begin module%3B9D035D003D.includes preserve=yes

#include "legacy.h"
#include "Dnc/ToolFiles.h"

//## end module%3B9D035D003D.includes

// cCarrier
#include "Dnc/Carrier/cCarrier.h"
// cCARRIERFat
#include "Dnc/FileSystem/cCARRIERFat.h"
// cCarrierSource
#include "Dnc/FileSystem/cCarrierSource.h"
//## begin module%3B9D035D003D.additionalDeclarations preserve=yes
//## end module%3B9D035D003D.additionalDeclarations


// Class cCarrierSource 


cCarrierSource::cCarrierSource()
  //## begin cCarrierSource::cCarrierSource%.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierSource::cCarrierSource%.hasinit
  //## begin cCarrierSource::cCarrierSource%.initialization preserve=yes
  //## end cCarrierSource::cCarrierSource%.initialization
{
  //## begin cCarrierSource::cCarrierSource%.body preserve=yes
   _Carrier = new cCarrier;
  //## end cCarrierSource::cCarrierSource%.body
}

cCarrierSource::cCarrierSource(const cCarrierSource &right)
  //## begin cCarrierSource::cCarrierSource%copy.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierSource::cCarrierSource%copy.hasinit
  //## begin cCarrierSource::cCarrierSource%copy.initialization preserve=yes
  //## end cCarrierSource::cCarrierSource%copy.initialization
{
  //## begin cCarrierSource::cCarrierSource%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCarrierSource::cCarrierSource%copy.body
}

cCarrierSource::cCarrierSource (CONST_STRING_T path)
  //## begin cCarrierSource::cCarrierSource%1062078709.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCarrierSource::cCarrierSource%1062078709.hasinit
  //## begin cCarrierSource::cCarrierSource%1062078709.initialization preserve=yes
  , cToolFileSource(path)
  //## end cCarrierSource::cCarrierSource%1062078709.initialization
{
  //## begin cCarrierSource::cCarrierSource%1062078709.body preserve=yes
   _Carrier = new cCarrier(path);
  //## end cCarrierSource::cCarrierSource%1062078709.body
}


cCarrierSource::~cCarrierSource()
{
  //## begin cCarrierSource::~cCarrierSource%.body preserve=yes
   DELETE_OBJECT(cCarrier, _Carrier)
  //## end cCarrierSource::~cCarrierSource%.body
}



//## Other Operations (implementation)
cToolFileSystem * cCarrierSource::FileSystem ()
{
  //## begin cCarrierSource::FileSystem%1062078710.body preserve=yes
   int size = _Carrier->Size();
   if (size > 0) {
      switch (size) {
      case 4:
      case 8:
         break;
      case 32:
         return new cCARRIERFat(_Path.c_str(), _Carrier);
      }
   }
   return NULL;
  //## end cCarrierSource::FileSystem%1062078710.body
}

// Additional Declarations
  //## begin cCarrierSource%3B9D035D003D.declarations preserve=yes
  //## end cCarrierSource%3B9D035D003D.declarations

//## begin module%3B9D035D003D.epilog preserve=yes
//## end module%3B9D035D003D.epilog
