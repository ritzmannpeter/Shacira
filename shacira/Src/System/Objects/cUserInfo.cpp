//## begin module%419856D6000F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%419856D6000F.cm

//## begin module%419856D6000F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%419856D6000F.cp

//## Module: cUserInfo%419856D6000F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cUserInfo.cpp

//## begin module%419856D6000F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%419856D6000F.additionalIncludes

//## begin module%419856D6000F.includes preserve=yes
//## end module%419856D6000F.includes

// cUserInfo
#include "System/Objects/cUserInfo.h"
// cTransferObject
#include "System/Objects/cTransferObject.h"
//## begin module%419856D6000F.additionalDeclarations preserve=yes
//## end module%419856D6000F.additionalDeclarations


// Class cUserInfo 









cUserInfo::cUserInfo()
  //## begin cUserInfo::cUserInfo%.hasinit preserve=no
      : _UserId(0), _GroupId(0), _DataSet(0), _LogoffInterval(0), _ClientId(0), _IFType(0)
  //## end cUserInfo::cUserInfo%.hasinit
  //## begin cUserInfo::cUserInfo%.initialization preserve=yes
  //## end cUserInfo::cUserInfo%.initialization
{
  //## begin cUserInfo::cUserInfo%.body preserve=yes
	_Type = OT_USER_INFO;
  //## end cUserInfo::cUserInfo%.body
}

cUserInfo::cUserInfo(const cUserInfo &right)
  //## begin cUserInfo::cUserInfo%copy.hasinit preserve=no
      : _UserId(0), _GroupId(0), _DataSet(0), _LogoffInterval(0), _ClientId(0), _IFType(0)
  //## end cUserInfo::cUserInfo%copy.hasinit
  //## begin cUserInfo::cUserInfo%copy.initialization preserve=yes
  , cTransientObject(right)
  //## end cUserInfo::cUserInfo%copy.initialization
{
  //## begin cUserInfo::cUserInfo%copy.body preserve=yes
	_Type = OT_USER_INFO;
   _UserId = right._UserId;
   _UserName = right._UserName;
   _GroupId = right._GroupId;
   _DataSet = right._DataSet;
   _LogoffInterval = right._LogoffInterval;
  //## end cUserInfo::cUserInfo%copy.body
}

cUserInfo::cUserInfo (cStaticObject *source, ULONG_T user_id, CONST_STRING_T user_name)
  //## begin cUserInfo::cUserInfo%1100502934.hasinit preserve=no
      : _UserId(0), _GroupId(0), _DataSet(0), _LogoffInterval(0), _ClientId(0), _IFType(0)
  //## end cUserInfo::cUserInfo%1100502934.hasinit
  //## begin cUserInfo::cUserInfo%1100502934.initialization preserve=yes
  , cTransientObject(source)
  //## end cUserInfo::cUserInfo%1100502934.initialization
{
  //## begin cUserInfo::cUserInfo%1100502934.body preserve=yes
	_Type = OT_USER_INFO;
   _UserId = user_id;
   _UserName = user_name;
  //## end cUserInfo::cUserInfo%1100502934.body
}


cUserInfo::~cUserInfo()
{
  //## begin cUserInfo::~cUserInfo%.body preserve=yes
  //## end cUserInfo::~cUserInfo%.body
}



//## Other Operations (implementation)
STRING_T cUserInfo::Serialize ()
{
  //## begin cUserInfo::Serialize%1100502935.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _UserId, ObjectBody);
   obj.AddAttribute(1, _UserName.c_str(), ObjectBody);
   obj.AddAttribute(2, _GroupId, ObjectBody);
   obj.AddAttribute(3, _DataSet, ObjectBody);
   obj.AddAttribute(4, _LogoffInterval, ObjectBody);
   obj.AddAttribute(5, _ClientId, ObjectBody);
   obj.AddAttribute(6, _IFType, ObjectBody);
   return obj.Serialize().c_str();
  //## end cUserInfo::Serialize%1100502935.body
}

BOOL_T cUserInfo::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cUserInfo::Construct%1100502936.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _UserId, ObjectBody);
   obj.GetAttribute(1, _UserName, ObjectBody);
   obj.GetAttribute(2, _GroupId, ObjectBody);
   obj.GetAttribute(3, _DataSet, ObjectBody);
   obj.GetAttribute(4, _LogoffInterval, ObjectBody);
   obj.GetAttribute(5, _ClientId, ObjectBody);
   obj.GetAttribute(6, _IFType, ObjectBody);
   return true;
  //## end cUserInfo::Construct%1100502936.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cUserInfo::get_UserId () const
{
  //## begin cUserInfo::get_UserId%4198572202BF.get preserve=no
  return _UserId;
  //## end cUserInfo::get_UserId%4198572202BF.get
}

void cUserInfo::set_UserId (ULONG_T value)
{
  //## begin cUserInfo::set_UserId%4198572202BF.set preserve=no
  _UserId = value;
  //## end cUserInfo::set_UserId%4198572202BF.set
}

STRING_T cUserInfo::get_UserName () const
{
  //## begin cUserInfo::get_UserName%4198574B0290.get preserve=no
  return _UserName;
  //## end cUserInfo::get_UserName%4198574B0290.get
}

void cUserInfo::set_UserName (STRING_T value)
{
  //## begin cUserInfo::set_UserName%4198574B0290.set preserve=no
  _UserName = value;
  //## end cUserInfo::set_UserName%4198574B0290.set
}

ULONG_T cUserInfo::get_GroupId () const
{
  //## begin cUserInfo::get_GroupId%41985F59033C.get preserve=no
  return _GroupId;
  //## end cUserInfo::get_GroupId%41985F59033C.get
}

void cUserInfo::set_GroupId (ULONG_T value)
{
  //## begin cUserInfo::set_GroupId%41985F59033C.set preserve=no
  _GroupId = value;
  //## end cUserInfo::set_GroupId%41985F59033C.set
}

ULONG_T cUserInfo::get_DataSet () const
{
  //## begin cUserInfo::get_DataSet%41985F6F01D4.get preserve=no
  return _DataSet;
  //## end cUserInfo::get_DataSet%41985F6F01D4.get
}

void cUserInfo::set_DataSet (ULONG_T value)
{
  //## begin cUserInfo::set_DataSet%41985F6F01D4.set preserve=no
  _DataSet = value;
  //## end cUserInfo::set_DataSet%41985F6F01D4.set
}

ULONG_T cUserInfo::get_LogoffInterval () const
{
  //## begin cUserInfo::get_LogoffInterval%41AEDD3302DE.get preserve=no
  return _LogoffInterval;
  //## end cUserInfo::get_LogoffInterval%41AEDD3302DE.get
}

void cUserInfo::set_LogoffInterval (ULONG_T value)
{
  //## begin cUserInfo::set_LogoffInterval%41AEDD3302DE.set preserve=no
  _LogoffInterval = value;
  //## end cUserInfo::set_LogoffInterval%41AEDD3302DE.set
}

ULONG_T cUserInfo::get_ClientId () const
{
  //## begin cUserInfo::get_ClientId%4417DB44030A.get preserve=no
  return _ClientId;
  //## end cUserInfo::get_ClientId%4417DB44030A.get
}

void cUserInfo::set_ClientId (ULONG_T value)
{
  //## begin cUserInfo::set_ClientId%4417DB44030A.set preserve=no
  _ClientId = value;
  //## end cUserInfo::set_ClientId%4417DB44030A.set
}

ULONG_T cUserInfo::get_IFType () const
{
  //## begin cUserInfo::get_IFType%4417DB5B002A.get preserve=no
  return _IFType;
  //## end cUserInfo::get_IFType%4417DB5B002A.get
}

void cUserInfo::set_IFType (ULONG_T value)
{
  //## begin cUserInfo::set_IFType%4417DB5B002A.set preserve=no
  _IFType = value;
  //## end cUserInfo::set_IFType%4417DB5B002A.set
}

// Additional Declarations
  //## begin cUserInfo%419856D6000F.declarations preserve=yes
  //## end cUserInfo%419856D6000F.declarations

//## begin module%419856D6000F.epilog preserve=yes
//## end module%419856D6000F.epilog
