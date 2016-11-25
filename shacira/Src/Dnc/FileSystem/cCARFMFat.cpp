//## begin module%3F4F500A006D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F4F500A006D.cm

//## begin module%3F4F500A006D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3F4F500A006D.cp

//## Module: cCARFMFat%3F4F500A006D; Pseudo Package body
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cCARFMFat.cpp

//## begin module%3F4F500A006D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F4F500A006D.additionalIncludes

//## begin module%3F4F500A006D.includes preserve=yes
//## end module%3F4F500A006D.includes

// cCarrier
#include "Dnc/Carrier/cCarrier.h"
// cCARFMFat
#include "Dnc/FileSystem/cCARFMFat.h"
//## begin module%3F4F500A006D.additionalDeclarations preserve=yes
//## end module%3F4F500A006D.additionalDeclarations


// Class cCARFMFat 


cCARFMFat::cCARFMFat()
  //## begin cCARFMFat::cCARFMFat%.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCARFMFat::cCARFMFat%.hasinit
  //## begin cCARFMFat::cCARFMFat%.initialization preserve=yes
  //## end cCARFMFat::cCARFMFat%.initialization
{
  //## begin cCARFMFat::cCARFMFat%.body preserve=yes
  //## end cCARFMFat::cCARFMFat%.body
}

cCARFMFat::cCARFMFat(const cCARFMFat &right)
  //## begin cCARFMFat::cCARFMFat%copy.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCARFMFat::cCARFMFat%copy.hasinit
  //## begin cCARFMFat::cCARFMFat%copy.initialization preserve=yes
  //## end cCARFMFat::cCARFMFat%copy.initialization
{
  //## begin cCARFMFat::cCARFMFat%copy.body preserve=yes
  //## end cCARFMFat::cCARFMFat%copy.body
}

cCARFMFat::cCARFMFat (CONST_STRING_T path, cCarrier *carrier)
  //## begin cCARFMFat::cCARFMFat%1062162389.hasinit preserve=no
      : _Carrier(NULL)
  //## end cCARFMFat::cCARFMFat%1062162389.hasinit
  //## begin cCARFMFat::cCARFMFat%1062162389.initialization preserve=yes
  //## end cCARFMFat::cCARFMFat%1062162389.initialization
{
  //## begin cCARFMFat::cCARFMFat%1062162389.body preserve=yes
  //## end cCARFMFat::cCARFMFat%1062162389.body
}


cCARFMFat::~cCARFMFat()
{
  //## begin cCARFMFat::~cCARFMFat%.body preserve=yes
  //## end cCARFMFat::~cCARFMFat%.body
}


// Additional Declarations
  //## begin cCARFMFat%3F4F500A006D.declarations preserve=yes
  //## end cCARFMFat%3F4F500A006D.declarations

//## begin module%3F4F500A006D.epilog preserve=yes
//## end module%3F4F500A006D.epilog
