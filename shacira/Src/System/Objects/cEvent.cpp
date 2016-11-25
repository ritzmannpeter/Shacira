//## begin module%3D05B0870231.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3D05B0870231.cm

//## begin module%3D05B0870231.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3D05B0870231.cp

//## Module: cEvent%3D05B0870231; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cEvent.cpp

//## begin module%3D05B0870231.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3D05B0870231.additionalIncludes

//## begin module%3D05B0870231.includes preserve=yes
//## end module%3D05B0870231.includes

// cTransferObject
#include "System/Objects/cTransferObject.h"
// cEvent
#include "System/Objects/cEvent.h"
//## begin module%3D05B0870231.additionalDeclarations preserve=yes
//## end module%3D05B0870231.additionalDeclarations


// Class cEvent 

cEvent::cEvent()
  //## begin cEvent::cEvent%.hasinit preserve=no
  //## end cEvent::cEvent%.hasinit
  //## begin cEvent::cEvent%.initialization preserve=yes
  //## end cEvent::cEvent%.initialization
{
  //## begin cEvent::cEvent%.body preserve=yes
   _Type = OT_EVENT;
  //## end cEvent::cEvent%.body
}

cEvent::cEvent(const cEvent &right)
  //## begin cEvent::cEvent%copy.hasinit preserve=no
  //## end cEvent::cEvent%copy.hasinit
  //## begin cEvent::cEvent%copy.initialization preserve=yes
  //## end cEvent::cEvent%copy.initialization
{
  //## begin cEvent::cEvent%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cEvent::cEvent%copy.body
}

cEvent::cEvent (cStaticObject *source, INT_T event_code)
  //## begin cEvent::cEvent%1023780997.hasinit preserve=no
  //## end cEvent::cEvent%1023780997.hasinit
  //## begin cEvent::cEvent%1023780997.initialization preserve=yes
  : cTransientObject(source)
  //## end cEvent::cEvent%1023780997.initialization
{
  //## begin cEvent::cEvent%1023780997.body preserve=yes
   _Type = OT_EVENT;
   _EventCode = event_code;
  //## end cEvent::cEvent%1023780997.body
}


cEvent::~cEvent()
{
  //## begin cEvent::~cEvent%.body preserve=yes
  //## end cEvent::~cEvent%.body
}



//## Other Operations (implementation)
STRING_T cEvent::Serialize ()
{
  //## begin cEvent::Serialize%1023780998.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _EventCode, ObjectBody);
   return obj.Serialize().c_str();
  //## end cEvent::Serialize%1023780998.body
}

BOOL_T cEvent::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cEvent::Construct%1023780999.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _EventCode, ObjectBody);
   return true;
  //## end cEvent::Construct%1023780999.body
}

// Additional Declarations
  //## begin cEvent%3D05B0870231.declarations preserve=yes
  //## end cEvent%3D05B0870231.declarations

//## begin module%3D05B0870231.epilog preserve=yes
//## end module%3D05B0870231.epilog
