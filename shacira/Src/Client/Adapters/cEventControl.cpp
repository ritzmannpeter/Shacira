//## begin module%3EBFAF27035B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3EBFAF27035B.cm

//## begin module%3EBFAF27035B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3EBFAF27035B.cp

//## Module: cEventControl%3EBFAF27035B; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Client\Adapters\cEventControl.cpp

//## begin module%3EBFAF27035B.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3EBFAF27035B.additionalIncludes

//## begin module%3EBFAF27035B.includes preserve=yes
//## end module%3EBFAF27035B.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cEventControl
#include "Client/Adapters/cEventControl.h"
//## begin module%3EBFAF27035B.additionalDeclarations preserve=yes
//## end module%3EBFAF27035B.additionalDeclarations


// Class cEventControl 

cEventControl::cEventControl()
  //## begin cEventControl::cEventControl%.hasinit preserve=no
  //## end cEventControl::cEventControl%.hasinit
  //## begin cEventControl::cEventControl%.initialization preserve=yes
  //## end cEventControl::cEventControl%.initialization
{
  //## begin cEventControl::cEventControl%.body preserve=yes
  //## end cEventControl::cEventControl%.body
}

cEventControl::cEventControl(const cEventControl &right)
  //## begin cEventControl::cEventControl%copy.hasinit preserve=no
  //## end cEventControl::cEventControl%copy.hasinit
  //## begin cEventControl::cEventControl%copy.initialization preserve=yes
  //## end cEventControl::cEventControl%copy.initialization
{
  //## begin cEventControl::cEventControl%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEventControl::cEventControl%copy.body
}


cEventControl::~cEventControl()
{
  //## begin cEventControl::~cEventControl%.body preserve=yes
  //## end cEventControl::~cEventControl%.body
}



//## Other Operations (implementation)
void cEventControl::Object (cTransientObject *object)
{
  //## begin cEventControl::Object%1052744774.body preserve=yes
   throw cError(VIRTUAL_METHOD_NOT_IMPLEMENTED, 0, "cEventControl::Object", "cEventControlControl");
  //## end cEventControl::Object%1052744774.body
}

// Additional Declarations
  //## begin cEventControl%3EBFAF27035B.declarations preserve=yes
  //## end cEventControl%3EBFAF27035B.declarations

//## begin module%3EBFAF27035B.epilog preserve=yes
//## end module%3EBFAF27035B.epilog
