//## begin module%3CFDF5550396.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3CFDF5550396.cm

//## begin module%3CFDF5550396.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3CFDF5550396.cp

//## Module: cDataChange%3CFDF5550396; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cDataChange.cpp

//## begin module%3CFDF5550396.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3CFDF5550396.additionalIncludes

//## begin module%3CFDF5550396.includes preserve=yes

/// PR 05.07.07 - added additional information to the cDataChange class
///               UnitCode (the input state for the supplied value)
///               UnitText (the unit text for the supplied value)
/// PR 12.10.07 - added change flags

//## end module%3CFDF5550396.includes

// cStringUtils
#include "System/cStringUtils.h"
// cTransferObject
#include "System/Objects/cTransferObject.h"
// cDataChange
#include "System/Objects/cDataChange.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cBlob
#include "System/Database/cBlob.h"
//## begin module%3CFDF5550396.additionalDeclarations preserve=yes
//## end module%3CFDF5550396.additionalDeclarations


// Class cDataChange 



















cDataChange::cDataChange()
  //## begin cDataChange::cDataChange%.hasinit preserve=no
      : _VarId(-1), _Index1(-1), _Index2(-1), _Index3(-1), _Index4(-1), _BufPtr(NULL), _DataSet(0), _State(0), _DataType(UNDEFINED), _VarType(UNDEFINED), _Precision(0), _ValueSize(0), _PersistenceType(UNDEFINED), _TimeOffset(0), _Pos(0), _UnitCode(0), _ChangeFlags(0)
  //## end cDataChange::cDataChange%.hasinit
  //## begin cDataChange::cDataChange%.initialization preserve=yes
  //## end cDataChange::cDataChange%.initialization
{
  //## begin cDataChange::cDataChange%.body preserve=yes
   _Type = OT_DATA_CHANGE;
  //## end cDataChange::cDataChange%.body
}

cDataChange::cDataChange(const cDataChange &right)
  //## begin cDataChange::cDataChange%copy.hasinit preserve=no
      : _VarId(-1), _Index1(-1), _Index2(-1), _Index3(-1), _Index4(-1), _BufPtr(NULL), _DataSet(0), _State(0), _DataType(UNDEFINED), _VarType(UNDEFINED), _Precision(0), _ValueSize(0), _PersistenceType(UNDEFINED), _TimeOffset(0), _Pos(0), _UnitCode(0), _ChangeFlags(0)
  //## end cDataChange::cDataChange%copy.hasinit
  //## begin cDataChange::cDataChange%copy.initialization preserve=yes
  //## end cDataChange::cDataChange%copy.initialization
{
  //## begin cDataChange::cDataChange%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cDataChange::cDataChange%copy.body
}

cDataChange::cDataChange (CONST_STRING_T var_name, LONG_T var_id, CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
  //## begin cDataChange::cDataChange%1023287637.hasinit preserve=no
      : _VarId(-1), _Index1(-1), _Index2(-1), _Index3(-1), _Index4(-1), _BufPtr(NULL), _DataSet(0), _State(0), _DataType(UNDEFINED), _VarType(UNDEFINED), _Precision(0), _ValueSize(0), _PersistenceType(UNDEFINED), _TimeOffset(0), _Pos(0), _UnitCode(0), _ChangeFlags(0)
  //## end cDataChange::cDataChange%1023287637.hasinit
  //## begin cDataChange::cDataChange%1023287637.initialization preserve=yes
  //## end cDataChange::cDataChange%1023287637.initialization
{
  //## begin cDataChange::cDataChange%1023287637.body preserve=yes
   _Type = OT_DATA_CHANGE;
   _VarName = var_name;
   _VarId = var_id;
   _Index1 = i1;
   _Index2 = i2;
   _Index3 = i3;
   _Index4 = i4;
   _Value = value;
   _TimeOffset = cSystemUtils::RealtimeOffset();
  //## end cDataChange::cDataChange%1023287637.body
}

cDataChange::cDataChange (CONST_STRING_T var_name, LONG_T var_id, BUF_T buf, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
  //## begin cDataChange::cDataChange%1073900392.hasinit preserve=no
      : _VarId(-1), _Index1(-1), _Index2(-1), _Index3(-1), _Index4(-1), _BufPtr(NULL), _DataSet(0), _State(0), _DataType(UNDEFINED), _VarType(UNDEFINED), _Precision(0), _ValueSize(0), _PersistenceType(UNDEFINED), _TimeOffset(0), _Pos(0), _UnitCode(0), _ChangeFlags(0)
  //## end cDataChange::cDataChange%1073900392.hasinit
  //## begin cDataChange::cDataChange%1073900392.initialization preserve=yes
  //## end cDataChange::cDataChange%1073900392.initialization
{
  //## begin cDataChange::cDataChange%1073900392.body preserve=yes
   _Type = OT_DATA_CHANGE;
   _VarName = var_name;
   _VarId = var_id;
   _Index1 = i1;
   _Index2 = i2;
   _Index3 = i3;
   _Index4 = i4;
   _BufPtr = buf;
   char value[0x100] = {0};
   SafePrintf(value, sizeof(value),  "memory:%p", buf);
   _Value = value;
   _TimeOffset = cSystemUtils::RealtimeOffset();
  //## end cDataChange::cDataChange%1073900392.body
}


cDataChange::~cDataChange()
{
  //## begin cDataChange::~cDataChange%.body preserve=yes
  //## end cDataChange::~cDataChange%.body
}



//## Other Operations (implementation)
STRING_T cDataChange::Serialize ()
{
  //## begin cDataChange::Serialize%1023780987.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _VarName.c_str(), ObjectBody);
   obj.AddAttribute(1, _VarId, ObjectBody);
   obj.AddAttribute(2, _Index1, ObjectBody);
   obj.AddAttribute(3, _Index2, ObjectBody);
   obj.AddAttribute(4, _Index3, ObjectBody);
   obj.AddAttribute(5, _Index4, ObjectBody);
   obj.AddAttribute(6, _OldValue.c_str(), ObjectBody);
   if (_DataType == SH_OBJECT ||
       _DataType == SH_BYTE) {
      cConvUtils::Ptr2String(_Value, _BufPtr);
   }
   obj.AddAttribute(7, _Value.c_str(), ObjectBody);
   obj.AddAttribute(8, _DataSet, ObjectBody);
   obj.AddAttribute(9, _State, ObjectBody);
   obj.AddAttribute(10, _DataType, ObjectBody);
   obj.AddAttribute(11, _VarType, ObjectBody);
   obj.AddAttribute(12, _Precision, ObjectBody);
   obj.AddAttribute(13, _ValueSize, ObjectBody);
   obj.AddAttribute(14, _PersistenceType, ObjectBody);
   obj.AddAttribute(15, _TimeOffset, ObjectBody);
   obj.AddAttribute(16, _UserName.c_str(), ObjectBody);
   obj.AddAttribute(17, _UnitCode, ObjectBody);
   obj.AddAttribute(18, _UnitText.c_str(), ObjectBody);
   obj.AddAttribute(19, _ChangeFlags, ObjectBody);
   STRING_T serialized_obj = obj.Serialize().c_str();
   return serialized_obj;
  //## end cDataChange::Serialize%1023780987.body
}

BOOL_T cDataChange::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cDataChange::Construct%1023780988.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _VarName, ObjectBody);
   obj.GetAttribute(1, _VarId, ObjectBody);
   obj.GetAttribute(2, _Index1, ObjectBody);
   obj.GetAttribute(3, _Index2, ObjectBody);
   obj.GetAttribute(4, _Index3, ObjectBody);
   obj.GetAttribute(5, _Index4, ObjectBody);
   obj.GetAttribute(6, _OldValue, ObjectBody);
   obj.GetAttribute(7, _Value, ObjectBody);
   if (_DataType == SH_OBJECT ||
       _DataType == SH_BYTE) {
      PTR_T ptr = NULL;
      cConvUtils::String2Ptr(ptr, _Value.c_str());
      _BufPtr = (BUF_T)ptr;
   }
   obj.GetAttribute(8, _DataSet, ObjectBody);
   obj.GetAttribute(9, _State, ObjectBody);
   obj.GetAttribute(10, _DataType, ObjectBody);
   obj.GetAttribute(11, _VarType, ObjectBody);
   obj.GetAttribute(12, _Precision, ObjectBody);
   obj.GetAttribute(13, _ValueSize, ObjectBody);
   obj.GetAttribute(14, _PersistenceType, ObjectBody);
   obj.GetAttribute(15, _TimeOffset, ObjectBody);
   obj.GetAttribute(16, _UserName, ObjectBody);
   obj.GetAttribute(17, _UnitCode, ObjectBody);
   obj.GetAttribute(18, _UnitText, ObjectBody);
   obj.GetAttribute(19, _ChangeFlags, ObjectBody);
#ifdef BINARY_TRANS
   if (_DataType == SH_OBJECT ||
       _DataType == SH_BYTE) {
      INT_T pos = cStringUtils::Find(serialized_obj, "bcd(");
      if (pos > 0) {
         _BufPtr = cSystemUtils::CachedAlloc(_VarName.c_str(),
                                             _Index1, _Index2, _Index3, _Index4,
                                             _ValueSize);
         if (_BufPtr != NULL) {
            CONST_STRING_T attachment = serialized_obj + pos;
            cConvUtils::String2Buf(attachment, _BufPtr, _ValueSize);
         }
         _Value = "";
      }
   }
#endif
   return true;
  //## end cDataChange::Construct%1023780988.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cDataChange::get_VarName () const
{
  //## begin cDataChange::get_VarName%3CFDF6240023.get preserve=no
  return _VarName;
  //## end cDataChange::get_VarName%3CFDF6240023.get
}

void cDataChange::set_VarName (STRING_T value)
{
  //## begin cDataChange::set_VarName%3CFDF6240023.set preserve=no
  _VarName = value;
  //## end cDataChange::set_VarName%3CFDF6240023.set
}

LONG_T cDataChange::get_VarId () const
{
  //## begin cDataChange::get_VarId%3D08572D0224.get preserve=no
  return _VarId;
  //## end cDataChange::get_VarId%3D08572D0224.get
}

void cDataChange::set_VarId (LONG_T value)
{
  //## begin cDataChange::set_VarId%3D08572D0224.set preserve=no
  _VarId = value;
  //## end cDataChange::set_VarId%3D08572D0224.set
}

LONG_T cDataChange::get_Index1 () const
{
  //## begin cDataChange::get_Index1%3D0856C6003B.get preserve=no
  return _Index1;
  //## end cDataChange::get_Index1%3D0856C6003B.get
}

void cDataChange::set_Index1 (LONG_T value)
{
  //## begin cDataChange::set_Index1%3D0856C6003B.set preserve=no
  _Index1 = value;
  //## end cDataChange::set_Index1%3D0856C6003B.set
}

LONG_T cDataChange::get_Index2 () const
{
  //## begin cDataChange::get_Index2%3D0856E0034F.get preserve=no
  return _Index2;
  //## end cDataChange::get_Index2%3D0856E0034F.get
}

void cDataChange::set_Index2 (LONG_T value)
{
  //## begin cDataChange::set_Index2%3D0856E0034F.set preserve=no
  _Index2 = value;
  //## end cDataChange::set_Index2%3D0856E0034F.set
}

LONG_T cDataChange::get_Index3 () const
{
  //## begin cDataChange::get_Index3%3D0856E20077.get preserve=no
  return _Index3;
  //## end cDataChange::get_Index3%3D0856E20077.get
}

void cDataChange::set_Index3 (LONG_T value)
{
  //## begin cDataChange::set_Index3%3D0856E20077.set preserve=no
  _Index3 = value;
  //## end cDataChange::set_Index3%3D0856E20077.set
}

LONG_T cDataChange::get_Index4 () const
{
  //## begin cDataChange::get_Index4%3D0856E301FF.get preserve=no
  return _Index4;
  //## end cDataChange::get_Index4%3D0856E301FF.get
}

void cDataChange::set_Index4 (LONG_T value)
{
  //## begin cDataChange::set_Index4%3D0856E301FF.set preserve=no
  _Index4 = value;
  //## end cDataChange::set_Index4%3D0856E301FF.set
}

STRING_T cDataChange::get_OldValue () const
{
  //## begin cDataChange::get_OldValue%3E79A29F035B.get preserve=no
  return _OldValue;
  //## end cDataChange::get_OldValue%3E79A29F035B.get
}

void cDataChange::set_OldValue (STRING_T value)
{
  //## begin cDataChange::set_OldValue%3E79A29F035B.set preserve=no
  _OldValue = value;
  //## end cDataChange::set_OldValue%3E79A29F035B.set
}

STRING_T cDataChange::get_Value () const
{
  //## begin cDataChange::get_Value%3CFDF624002D.get preserve=no
  return _Value;
  //## end cDataChange::get_Value%3CFDF624002D.get
}

void cDataChange::set_Value (STRING_T value)
{
  //## begin cDataChange::set_Value%3CFDF624002D.set preserve=no
  _Value = value;
  //## end cDataChange::set_Value%3CFDF624002D.set
}

BUF_T cDataChange::get_BufPtr () const
{
  //## begin cDataChange::get_BufPtr%40026F620222.get preserve=no
  return _BufPtr;
  //## end cDataChange::get_BufPtr%40026F620222.get
}

void cDataChange::set_BufPtr (BUF_T value)
{
  //## begin cDataChange::set_BufPtr%40026F620222.set preserve=no
  _BufPtr = value;
  //## end cDataChange::set_BufPtr%40026F620222.set
}

ULONG_T cDataChange::get_DataSet () const
{
  //## begin cDataChange::get_DataSet%4039EC2C007D.get preserve=no
  return _DataSet;
  //## end cDataChange::get_DataSet%4039EC2C007D.get
}

void cDataChange::set_DataSet (ULONG_T value)
{
  //## begin cDataChange::set_DataSet%4039EC2C007D.set preserve=no
  _DataSet = value;
  //## end cDataChange::set_DataSet%4039EC2C007D.set
}

ULONG_T cDataChange::get_State () const
{
  //## begin cDataChange::get_State%429AB70B02AF.get preserve=no
  return _State;
  //## end cDataChange::get_State%429AB70B02AF.get
}

void cDataChange::set_State (ULONG_T value)
{
  //## begin cDataChange::set_State%429AB70B02AF.set preserve=no
  _State = value;
  //## end cDataChange::set_State%429AB70B02AF.set
}

ULONG_T cDataChange::get_DataType () const
{
  //## begin cDataChange::get_DataType%40228F66006D.get preserve=no
  return _DataType;
  //## end cDataChange::get_DataType%40228F66006D.get
}

void cDataChange::set_DataType (ULONG_T value)
{
  //## begin cDataChange::set_DataType%40228F66006D.set preserve=no
  _DataType = value;
  //## end cDataChange::set_DataType%40228F66006D.set
}

ULONG_T cDataChange::get_VarType () const
{
  //## begin cDataChange::get_VarType%417CCF4500AB.get preserve=no
  return _VarType;
  //## end cDataChange::get_VarType%417CCF4500AB.get
}

void cDataChange::set_VarType (ULONG_T value)
{
  //## begin cDataChange::set_VarType%417CCF4500AB.set preserve=no
  _VarType = value;
  //## end cDataChange::set_VarType%417CCF4500AB.set
}

ULONG_T cDataChange::get_Precision () const
{
  //## begin cDataChange::get_Precision%40D09ACA0196.get preserve=no
  return _Precision;
  //## end cDataChange::get_Precision%40D09ACA0196.get
}

void cDataChange::set_Precision (ULONG_T value)
{
  //## begin cDataChange::set_Precision%40D09ACA0196.set preserve=no
  _Precision = value;
  //## end cDataChange::set_Precision%40D09ACA0196.set
}

ULONG_T cDataChange::get_ValueSize () const
{
  //## begin cDataChange::get_ValueSize%40228F83004E.get preserve=no
  return _ValueSize;
  //## end cDataChange::get_ValueSize%40228F83004E.get
}

void cDataChange::set_ValueSize (ULONG_T value)
{
  //## begin cDataChange::set_ValueSize%40228F83004E.set preserve=no
  _ValueSize = value;
  //## end cDataChange::set_ValueSize%40228F83004E.set
}

ULONG_T cDataChange::get_PersistenceType () const
{
  //## begin cDataChange::get_PersistenceType%403B2E9402AF.get preserve=no
  return _PersistenceType;
  //## end cDataChange::get_PersistenceType%403B2E9402AF.get
}

void cDataChange::set_PersistenceType (ULONG_T value)
{
  //## begin cDataChange::set_PersistenceType%403B2E9402AF.set preserve=no
  _PersistenceType = value;
  //## end cDataChange::set_PersistenceType%403B2E9402AF.set
}

ULONG_T cDataChange::get_TimeOffset () const
{
  //## begin cDataChange::get_TimeOffset%40228F44031C.get preserve=no
  return _TimeOffset;
  //## end cDataChange::get_TimeOffset%40228F44031C.get
}

void cDataChange::set_TimeOffset (ULONG_T value)
{
  //## begin cDataChange::set_TimeOffset%40228F44031C.set preserve=no
  _TimeOffset = value;
  //## end cDataChange::set_TimeOffset%40228F44031C.set
}

ULONG_T cDataChange::get_Pos () const
{
  //## begin cDataChange::get_Pos%429ABA0B0148.get preserve=no
  return _Pos;
  //## end cDataChange::get_Pos%429ABA0B0148.get
}

void cDataChange::set_Pos (ULONG_T value)
{
  //## begin cDataChange::set_Pos%429ABA0B0148.set preserve=no
  _Pos = value;
  //## end cDataChange::set_Pos%429ABA0B0148.set
}

ULONG_T cDataChange::get_UnitCode () const
{
  return _UnitCode;
}

void cDataChange::set_UnitCode (ULONG_T value)
{
  _UnitCode = value;
}

STRING_T cDataChange::get_UnitText () const
{
  return _UnitText;
}

void cDataChange::set_UnitText (STRING_T value)
{
  _UnitText = value;
}

ULONG_T cDataChange::get_ChangeFlags () const
{
  //## begin cDataChange::get_ChangeFlags%470F192601DD.get preserve=no
  return _ChangeFlags;
  //## end cDataChange::get_ChangeFlags%470F192601DD.get
}

void cDataChange::set_ChangeFlags (ULONG_T value)
{
  //## begin cDataChange::set_ChangeFlags%470F192601DD.set preserve=no
  _ChangeFlags = value;
  //## end cDataChange::set_ChangeFlags%470F192601DD.set
}

// Additional Declarations
  //## begin cDataChange%3CFDF5550396.declarations preserve=yes
  //## end cDataChange%3CFDF5550396.declarations

//## begin module%3CFDF5550396.epilog preserve=yes
//## end module%3CFDF5550396.epilog
