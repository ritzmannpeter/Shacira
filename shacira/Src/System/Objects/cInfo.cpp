//## begin module%3ABA1A7A023D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3ABA1A7A023D.cm

//## begin module%3ABA1A7A023D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3ABA1A7A023D.cp

//## Module: cInfo%3ABA1A7A023D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cInfo.cpp

//## begin module%3ABA1A7A023D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3ABA1A7A023D.additionalIncludes

//## begin module%3ABA1A7A023D.includes preserve=yes
//## end module%3ABA1A7A023D.includes

// cInfo
#include "System/Objects/cInfo.h"
// cTransferObject
#include "System/Objects/cTransferObject.h"
//## begin module%3ABA1A7A023D.additionalDeclarations preserve=yes
//## end module%3ABA1A7A023D.additionalDeclarations


// Class cInfo 










cInfo::cInfo()
  //## begin cInfo::cInfo%.hasinit preserve=no
      : _InfoType(0), _InfoCustomType(0), _InfoId(0), _InfoTextId(0)
  //## end cInfo::cInfo%.hasinit
  //## begin cInfo::cInfo%.initialization preserve=yes
  //## end cInfo::cInfo%.initialization
{
  //## begin cInfo::cInfo%.body preserve=yes
   _Type = OT_INFO;
  //## end cInfo::cInfo%.body
}

cInfo::cInfo(const cInfo &right)
  //## begin cInfo::cInfo%copy.hasinit preserve=no
      : _InfoType(0), _InfoCustomType(0), _InfoId(0), _InfoTextId(0)
  //## end cInfo::cInfo%copy.hasinit
  //## begin cInfo::cInfo%copy.initialization preserve=yes
  //## end cInfo::cInfo%copy.initialization
{
  //## begin cInfo::cInfo%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cInfo::cInfo%copy.body
}

cInfo::cInfo (cStaticObject *source, ULONG_T info_type, ULONG_T info_text_id, CONST_STRING_T info_text)
  //## begin cInfo::cInfo%985267668.hasinit preserve=no
      : _InfoType(0), _InfoCustomType(0), _InfoId(0), _InfoTextId(0)
  //## end cInfo::cInfo%985267668.hasinit
  //## begin cInfo::cInfo%985267668.initialization preserve=yes
   , cTransientObject(source)
  //## end cInfo::cInfo%985267668.initialization
{
  //## begin cInfo::cInfo%985267668.body preserve=yes
   _Type = OT_INFO;
   _InfoType = info_type;
   _InfoTextId = info_text_id;
   if (info_text != NULL) _InfoText = info_text;
//InfoPrintf("type %d, info type %d text id %d info text %s info custom type %d\n",
//           _Type, _InfoType, _InfoTextId, _InfoText.c_str(), _InfoCustomType);
  //## end cInfo::cInfo%985267668.body
}


cInfo::~cInfo()
{
  //## begin cInfo::~cInfo%.body preserve=yes
  //## end cInfo::~cInfo%.body
}



//## Other Operations (implementation)
STRING_T cInfo::Serialize ()
{
  //## begin cInfo::Serialize%1023780979.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _InfoType, ObjectBody);
   obj.AddAttribute(1, _InfoCustomType, ObjectBody);
   obj.AddAttribute(2, _InfoId, ObjectBody);
   obj.AddAttribute(3, _InfoTextId, ObjectBody);
   obj.AddAttribute(4, _InfoText.c_str(), ObjectBody);
   obj.AddAttribute(5, _Param1.c_str(), ObjectBody);
   obj.AddAttribute(6, _Param2.c_str(), ObjectBody);
   obj.AddAttribute(7, _Param3.c_str(), ObjectBody);
   obj.AddAttribute(8, _Param4.c_str(), ObjectBody);
   return obj.Serialize().c_str();
  //## end cInfo::Serialize%1023780979.body
}

BOOL_T cInfo::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cInfo::Construct%1023780980.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _InfoType, ObjectBody);
   obj.GetAttribute(1, _InfoCustomType, ObjectBody);
   obj.GetAttribute(2, _InfoId, ObjectBody);
   obj.GetAttribute(3, _InfoTextId, ObjectBody);
   obj.GetAttribute(4, _InfoText, ObjectBody);
   obj.GetAttribute(5, _Param1, ObjectBody);
   obj.GetAttribute(6, _Param2, ObjectBody);
   obj.GetAttribute(7, _Param3, ObjectBody);
   obj.GetAttribute(8, _Param4, ObjectBody);
   return true;
  //## end cInfo::Construct%1023780980.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cInfo::get_InfoType () const
{
  //## begin cInfo::get_InfoType%3E5B712C00D9.get preserve=no
  return _InfoType;
  //## end cInfo::get_InfoType%3E5B712C00D9.get
}

void cInfo::set_InfoType (ULONG_T value)
{
  //## begin cInfo::set_InfoType%3E5B712C00D9.set preserve=no
  _InfoType = value;
  //## end cInfo::set_InfoType%3E5B712C00D9.set
}

ULONG_T cInfo::get_InfoCustomType () const
{
  //## begin cInfo::get_InfoCustomType%41FFCD830203.get preserve=no
  return _InfoCustomType;
  //## end cInfo::get_InfoCustomType%41FFCD830203.get
}

void cInfo::set_InfoCustomType (ULONG_T value)
{
  //## begin cInfo::set_InfoCustomType%41FFCD830203.set preserve=no
  _InfoCustomType = value;
  //## end cInfo::set_InfoCustomType%41FFCD830203.set
}

ULONG_T cInfo::get_InfoId () const
{
  //## begin cInfo::get_InfoId%41FFCDB00109.get preserve=no
  return _InfoId;
  //## end cInfo::get_InfoId%41FFCDB00109.get
}

void cInfo::set_InfoId (ULONG_T value)
{
  //## begin cInfo::set_InfoId%41FFCDB00109.set preserve=no
  _InfoId = value;
  //## end cInfo::set_InfoId%41FFCDB00109.set
}

ULONG_T cInfo::get_InfoTextId () const
{
  //## begin cInfo::get_InfoTextId%3ABA1AC40026.get preserve=no
  return _InfoTextId;
  //## end cInfo::get_InfoTextId%3ABA1AC40026.get
}

void cInfo::set_InfoTextId (ULONG_T value)
{
  //## begin cInfo::set_InfoTextId%3ABA1AC40026.set preserve=no
  _InfoTextId = value;
  //## end cInfo::set_InfoTextId%3ABA1AC40026.set
}

STRING_T cInfo::get_InfoText () const
{
  //## begin cInfo::get_InfoText%4132D9E40271.get preserve=no
  return _InfoText;
  //## end cInfo::get_InfoText%4132D9E40271.get
}

void cInfo::set_InfoText (STRING_T value)
{
  //## begin cInfo::set_InfoText%4132D9E40271.set preserve=no
  _InfoText = value;
  //## end cInfo::set_InfoText%4132D9E40271.set
}

STRING_T cInfo::get_Param1 () const
{
  //## begin cInfo::get_Param1%4132DFB2008C.get preserve=no
  return _Param1;
  //## end cInfo::get_Param1%4132DFB2008C.get
}

void cInfo::set_Param1 (STRING_T value)
{
  //## begin cInfo::set_Param1%4132DFB2008C.set preserve=no
  _Param1 = value;
  //## end cInfo::set_Param1%4132DFB2008C.set
}

STRING_T cInfo::get_Param2 () const
{
  //## begin cInfo::get_Param2%4132DFB2008D.get preserve=no
  return _Param2;
  //## end cInfo::get_Param2%4132DFB2008D.get
}

void cInfo::set_Param2 (STRING_T value)
{
  //## begin cInfo::set_Param2%4132DFB2008D.set preserve=no
  _Param2 = value;
  //## end cInfo::set_Param2%4132DFB2008D.set
}

STRING_T cInfo::get_Param3 () const
{
  //## begin cInfo::get_Param3%4132DFB2008E.get preserve=no
  return _Param3;
  //## end cInfo::get_Param3%4132DFB2008E.get
}

void cInfo::set_Param3 (STRING_T value)
{
  //## begin cInfo::set_Param3%4132DFB2008E.set preserve=no
  _Param3 = value;
  //## end cInfo::set_Param3%4132DFB2008E.set
}

STRING_T cInfo::get_Param4 () const
{
  //## begin cInfo::get_Param4%4132DFB2009C.get preserve=no
  return _Param4;
  //## end cInfo::get_Param4%4132DFB2009C.get
}

void cInfo::set_Param4 (STRING_T value)
{
  //## begin cInfo::set_Param4%4132DFB2009C.set preserve=no
  _Param4 = value;
  //## end cInfo::set_Param4%4132DFB2009C.set
}

// Additional Declarations
  //## begin cInfo%3ABA1A7A023D.declarations preserve=yes
  //## end cInfo%3ABA1A7A023D.declarations

//## begin module%3ABA1A7A023D.epilog preserve=yes
//## end module%3ABA1A7A023D.epilog
