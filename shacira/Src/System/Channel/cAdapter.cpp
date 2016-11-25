//## begin module%3F82F35E004E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3F82F35E004E.cm

//## begin module%3F82F35E004E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3F82F35E004E.cp

//## Module: cAdapter%3F82F35E004E; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Channel\cAdapter.cpp

//## begin module%3F82F35E004E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3F82F35E004E.additionalIncludes

//## begin module%3F82F35E004E.includes preserve=yes
//## end module%3F82F35E004E.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cAdapter
#include "System/Channel/cAdapter.h"
//## begin module%3F82F35E004E.additionalDeclarations preserve=yes
//## end module%3F82F35E004E.additionalDeclarations


// Class cAdapter 

cAdapter::cAdapter()
  //## begin cAdapter::cAdapter%.hasinit preserve=no
  //## end cAdapter::cAdapter%.hasinit
  //## begin cAdapter::cAdapter%.initialization preserve=yes
  //## end cAdapter::cAdapter%.initialization
{
  //## begin cAdapter::cAdapter%.body preserve=yes
   _Class = "Adapter";
   _Type = "Adapter";
   char adapter_name[128] = {0};
   SafePrintf(adapter_name, sizeof(adapter_name), "adapter:%p", this);
   _Name = adapter_name;
  //## end cAdapter::cAdapter%.body
}

cAdapter::cAdapter(const cAdapter &right)
  //## begin cAdapter::cAdapter%copy.hasinit preserve=no
  //## end cAdapter::cAdapter%copy.hasinit
  //## begin cAdapter::cAdapter%copy.initialization preserve=yes
  //## end cAdapter::cAdapter%copy.initialization
{
  //## begin cAdapter::cAdapter%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cAdapter::cAdapter%copy.body
}


cAdapter::~cAdapter()
{
  //## begin cAdapter::~cAdapter%.body preserve=yes
  //## end cAdapter::~cAdapter%.body
}



// Additional Declarations
  //## begin cAdapter%3F82F35E004E.declarations preserve=yes
  //## end cAdapter%3F82F35E004E.declarations

//## begin module%3F82F35E004E.epilog preserve=yes
//## end module%3F82F35E004E.epilog
