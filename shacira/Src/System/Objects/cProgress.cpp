//## begin module%42CBD3270232.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42CBD3270232.cm

//## begin module%42CBD3270232.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%42CBD3270232.cp

//## Module: cProgress%42CBD3270232; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cProgress.cpp

//## begin module%42CBD3270232.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%42CBD3270232.additionalIncludes

//## begin module%42CBD3270232.includes preserve=yes
//## end module%42CBD3270232.includes

// cProgress
#include "System/Objects/cProgress.h"
//## begin module%42CBD3270232.additionalDeclarations preserve=yes
//## end module%42CBD3270232.additionalDeclarations


// Class cProgress 



cProgress::cProgress()
  //## begin cProgress::cProgress%.hasinit preserve=no
      : _IndicatorId(0), _Value(0)
  //## end cProgress::cProgress%.hasinit
  //## begin cProgress::cProgress%.initialization preserve=yes
  //## end cProgress::cProgress%.initialization
{
  //## begin cProgress::cProgress%.body preserve=yes
   _Type = OT_PROGRESS;
  //## end cProgress::cProgress%.body
}

cProgress::cProgress(const cProgress &right)
  //## begin cProgress::cProgress%copy.hasinit preserve=no
      : _IndicatorId(0), _Value(0)
  //## end cProgress::cProgress%copy.hasinit
  //## begin cProgress::cProgress%copy.initialization preserve=yes
  //## end cProgress::cProgress%copy.initialization
{
  //## begin cProgress::cProgress%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProgress::cProgress%copy.body
}

cProgress::cProgress (cStaticObject *source, ULONG_T indicator_id, ULONG_T value)
  //## begin cProgress::cProgress%1120654321.hasinit preserve=no
      : _IndicatorId(0), _Value(0)
  //## end cProgress::cProgress%1120654321.hasinit
  //## begin cProgress::cProgress%1120654321.initialization preserve=yes
   , cTransientObject(source)
  //## end cProgress::cProgress%1120654321.initialization
{
  //## begin cProgress::cProgress%1120654321.body preserve=yes
   _Type = OT_PROGRESS;
   _IndicatorId = indicator_id;
   _Value = value;
  //## end cProgress::cProgress%1120654321.body
}


cProgress::~cProgress()
{
  //## begin cProgress::~cProgress%.body preserve=yes
  //## end cProgress::~cProgress%.body
}



//## Other Operations (implementation)
STRING_T cProgress::Serialize ()
{
  //## begin cProgress::Serialize%1120654322.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _IndicatorId, ObjectBody);
   obj.AddAttribute(1, _Value, ObjectBody);
   return obj.Serialize().c_str();
  //## end cProgress::Serialize%1120654322.body
}

BOOL_T cProgress::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cProgress::Construct%1120654323.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _IndicatorId, ObjectBody);
   obj.GetAttribute(1, _Value, ObjectBody);
   return true;
  //## end cProgress::Construct%1120654323.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cProgress::get_IndicatorId () const
{
  //## begin cProgress::get_IndicatorId%42CBD3B601E4.get preserve=no
  return _IndicatorId;
  //## end cProgress::get_IndicatorId%42CBD3B601E4.get
}

void cProgress::set_IndicatorId (ULONG_T value)
{
  //## begin cProgress::set_IndicatorId%42CBD3B601E4.set preserve=no
  _IndicatorId = value;
  //## end cProgress::set_IndicatorId%42CBD3B601E4.set
}

ULONG_T cProgress::get_Value () const
{
  //## begin cProgress::get_Value%42CBD3D8009C.get preserve=no
  return _Value;
  //## end cProgress::get_Value%42CBD3D8009C.get
}

void cProgress::set_Value (ULONG_T value)
{
  //## begin cProgress::set_Value%42CBD3D8009C.set preserve=no
  _Value = value;
  //## end cProgress::set_Value%42CBD3D8009C.set
}

// Additional Declarations
  //## begin cProgress%42CBD3270232.declarations preserve=yes
  //## end cProgress%42CBD3270232.declarations

//## begin module%42CBD3270232.epilog preserve=yes
//## end module%42CBD3270232.epilog
