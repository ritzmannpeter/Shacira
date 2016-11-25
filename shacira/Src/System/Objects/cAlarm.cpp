//## begin module%3DDBC52A0206.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DDBC52A0206.cm

//## begin module%3DDBC52A0206.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DDBC52A0206.cp

//## Module: cAlarm%3DDBC52A0206; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cAlarm.cpp

//## begin module%3DDBC52A0206.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DDBC52A0206.additionalIncludes

//## begin module%3DDBC52A0206.includes preserve=yes
//## end module%3DDBC52A0206.includes

// cTransferObject
#include "System/Objects/cTransferObject.h"
// cAlarm
#include "System/Objects/cAlarm.h"
//## begin module%3DDBC52A0206.additionalDeclarations preserve=yes

/// PR 04.10.05 removed initialization bug in constructor

//## end module%3DDBC52A0206.additionalDeclarations


// Class cAlarm 

















cAlarm::cAlarm()
  //## begin cAlarm::cAlarm%.hasinit preserve=no
      : _Ident(0), _Severity(SevError), _State(true), _TextId1(0), _TextId2(0), _TextId3(0), _TextId4(0)
  //## end cAlarm::cAlarm%.hasinit
  //## begin cAlarm::cAlarm%.initialization preserve=yes
  //## end cAlarm::cAlarm%.initialization
{
  //## begin cAlarm::cAlarm%.body preserve=yes
   _Type = OT_ALARM;
   _AcknowledgedTimeStamp = 0;
  //## end cAlarm::cAlarm%.body
}

cAlarm::cAlarm(const cAlarm &right)
  //## begin cAlarm::cAlarm%copy.hasinit preserve=no
      : _Ident(0), _Severity(SevError), _State(true), _TextId1(0), _TextId2(0), _TextId3(0), _TextId4(0)
  //## end cAlarm::cAlarm%copy.hasinit
  //## begin cAlarm::cAlarm%copy.initialization preserve=yes
  , cTransientObject(right)
  //## end cAlarm::cAlarm%copy.initialization
{
  //## begin cAlarm::cAlarm%copy.body preserve=yes
   _Type = OT_ALARM;
   _TimeStamp.Now();
   _Ident = right._Ident;
   _Severity = right._Severity;
   _State = right._State;
   _TextId1 = right._TextId1;
   _TextId2 = right._TextId2;
   _TextId3 = right._TextId3;
   _TextId4 = right._TextId4;
   _Text1 = right._Text1;
   _Text2 = right._Text2;
   _Text3 = right._Text3;
   _Text4 = right._Text4;
   _Param1 = right._Param1;
   _Param2 = right._Param2;
   _Param3 = right._Param3;
   _Param4 = right._Param4;
   _AcknowledgedTimeStamp = right._AcknowledgedTimeStamp;
   _HelpId = right._HelpId;
  //## end cAlarm::cAlarm%copy.body
}

cAlarm::cAlarm (cStaticObject *source, ULONG_T ident, BOOL_T state)
  //## begin cAlarm::cAlarm%1043349076.hasinit preserve=no
      : _Ident(0), _Severity(SevError), _State(true), _TextId1(0), _TextId2(0), _TextId3(0), _TextId4(0)
  //## end cAlarm::cAlarm%1043349076.hasinit
  //## begin cAlarm::cAlarm%1043349076.initialization preserve=yes
  , cTransientObject(source)
  //## end cAlarm::cAlarm%1043349076.initialization
{
  //## begin cAlarm::cAlarm%1043349076.body preserve=yes
   _Type = OT_ALARM;
   _Ident = ident;
   _State = state;
   _AcknowledgedTimeStamp = 0;
  //## end cAlarm::cAlarm%1043349076.body
}

cAlarm::cAlarm (cStaticObject *source, ULONG_T ident, BOOL_T state, ULONG_T text_id)
  //## begin cAlarm::cAlarm%1093283177.hasinit preserve=no
      : _Ident(0), _Severity(SevError), _State(true), _TextId1(0), _TextId2(0), _TextId3(0), _TextId4(0)
  //## end cAlarm::cAlarm%1093283177.hasinit
  //## begin cAlarm::cAlarm%1093283177.initialization preserve=yes
  , cTransientObject(source)
  //## end cAlarm::cAlarm%1093283177.initialization
{
  //## begin cAlarm::cAlarm%1093283177.body preserve=yes
   _Type = OT_ALARM;
   _Ident = ident;
   _State = state;
   _TextId1 = text_id;
   _AcknowledgedTimeStamp = 0;
  //## end cAlarm::cAlarm%1093283177.body
}

cAlarm::cAlarm (cStaticObject *source, ULONG_T ident, BOOL_T state, CONST_STRING_T text)
  //## begin cAlarm::cAlarm%1093283178.hasinit preserve=no
      : _Ident(0), _Severity(SevError), _State(true), _TextId1(0), _TextId2(0), _TextId3(0), _TextId4(0)
  //## end cAlarm::cAlarm%1093283178.hasinit
  //## begin cAlarm::cAlarm%1093283178.initialization preserve=yes
  , cTransientObject(source)
  //## end cAlarm::cAlarm%1093283178.initialization
{
  //## begin cAlarm::cAlarm%1093283178.body preserve=yes
   _Type = OT_ALARM;
   _Ident = ident;
   _State = state;
   if (text != NULL) {
      /// PR 04.10.05 only do this when text != NULL
      _Text1 = text;
   }
   _AcknowledgedTimeStamp = 0;
  //## end cAlarm::cAlarm%1093283178.body
}


cAlarm::~cAlarm()
{
  //## begin cAlarm::~cAlarm%.body preserve=yes
  //## end cAlarm::~cAlarm%.body
}



//## Other Operations (implementation)
cAlarm * cAlarm::Reset ()
{
  //## begin cAlarm::Reset%1081345949.body preserve=yes
   cAlarm * alarm = new cAlarm(*this);
   alarm->set_State(false);
   return alarm;
  //## end cAlarm::Reset%1081345949.body
}

STRING_T cAlarm::Serialize ()
{
  //## begin cAlarm::Serialize%1043349077.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _Ident, ObjectBody);
   obj.AddAttribute(1, _Severity, ObjectBody);
   obj.AddAttribute(2, _State, ObjectBody);
   obj.AddAttribute(3, _TextId1, ObjectBody);
   obj.AddAttribute(4, _TextId1, ObjectBody);
   obj.AddAttribute(5, _TextId1, ObjectBody);
   obj.AddAttribute(6, _TextId1, ObjectBody);
   obj.AddAttribute(7, _Text1.c_str(), ObjectBody);
   obj.AddAttribute(8, _Text2.c_str(), ObjectBody);
   obj.AddAttribute(9, _Text3.c_str(), ObjectBody);
   obj.AddAttribute(10, _Text4.c_str(), ObjectBody);
   obj.AddAttribute(11, _Param1.c_str(), ObjectBody);
   obj.AddAttribute(12, _Param2.c_str(), ObjectBody);
   obj.AddAttribute(13, _Param3.c_str(), ObjectBody);
   obj.AddAttribute(14, _Param4.c_str(), ObjectBody);
   obj.AddAttribute(15, _AcknowledgedTimeStamp, ObjectBody);
   obj.AddAttribute(16, _HelpId.c_str(), ObjectBody);
   return obj.Serialize().c_str();
  //## end cAlarm::Serialize%1043349077.body
}

BOOL_T cAlarm::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cAlarm::Construct%1043349078.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _Ident, ObjectBody);
   LONG_T severity = 0;
   obj.GetAttribute(1, severity, ObjectBody);
   _Severity = (SeverityTypes)severity;
   obj.GetAttribute(2, _State, ObjectBody);
   obj.GetAttribute(3, _TextId1, ObjectBody);
   obj.GetAttribute(4, _TextId2, ObjectBody);
   obj.GetAttribute(5, _TextId3, ObjectBody);
   obj.GetAttribute(6, _TextId4, ObjectBody);
   obj.GetAttribute(7, _Text1, ObjectBody);
   obj.GetAttribute(8, _Text2, ObjectBody);
   obj.GetAttribute(9, _Text3, ObjectBody);
   obj.GetAttribute(10, _Text4, ObjectBody);
   obj.GetAttribute(11, _Param1, ObjectBody);
   obj.GetAttribute(12, _Param2, ObjectBody);
   obj.GetAttribute(13, _Param3, ObjectBody);
   obj.GetAttribute(14, _Param4, ObjectBody);
   obj.GetAttribute(15, _AcknowledgedTimeStamp, ObjectBody);
   obj.GetAttribute(16, _HelpId, ObjectBody);
   return true;
  //## end cAlarm::Construct%1043349078.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cAlarm::get_Ident () const
{
  //## begin cAlarm::get_Ident%3DDCDB7B01C3.get preserve=no
  return _Ident;
  //## end cAlarm::get_Ident%3DDCDB7B01C3.get
}

void cAlarm::set_Ident (ULONG_T value)
{
  //## begin cAlarm::set_Ident%3DDCDB7B01C3.set preserve=no
  _Ident = value;
  //## end cAlarm::set_Ident%3DDCDB7B01C3.set
}

SeverityTypes cAlarm::get_Severity () const
{
  //## begin cAlarm::get_Severity%407262F20203.get preserve=no
  return _Severity;
  //## end cAlarm::get_Severity%407262F20203.get
}

void cAlarm::set_Severity (SeverityTypes value)
{
  //## begin cAlarm::set_Severity%407262F20203.set preserve=no
  _Severity = value;
  //## end cAlarm::set_Severity%407262F20203.set
}

BOOL_T cAlarm::get_State () const
{
  //## begin cAlarm::get_State%3E3042C303C8.get preserve=no
  return _State;
  //## end cAlarm::get_State%3E3042C303C8.get
}

void cAlarm::set_State (BOOL_T value)
{
  //## begin cAlarm::set_State%3E3042C303C8.set preserve=no
  _State = value;
  //## end cAlarm::set_State%3E3042C303C8.set
}

ULONG_T cAlarm::get_TextId1 () const
{
  //## begin cAlarm::get_TextId1%412A2C6701A5.get preserve=no
  return _TextId1;
  //## end cAlarm::get_TextId1%412A2C6701A5.get
}

void cAlarm::set_TextId1 (ULONG_T value)
{
  //## begin cAlarm::set_TextId1%412A2C6701A5.set preserve=no
  _TextId1 = value;
  //## end cAlarm::set_TextId1%412A2C6701A5.set
}

STRING_T cAlarm::get_Text1 () const
{
  //## begin cAlarm::get_Text1%3DDCDB9800CA.get preserve=no
  return _Text1;
  //## end cAlarm::get_Text1%3DDCDB9800CA.get
}

void cAlarm::set_Text1 (STRING_T value)
{
  //## begin cAlarm::set_Text1%3DDCDB9800CA.set preserve=no
  _Text1 = value;
  //## end cAlarm::set_Text1%3DDCDB9800CA.set
}

ULONG_T cAlarm::get_TextId2 () const
{
  //## begin cAlarm::get_TextId2%412A2C810242.get preserve=no
  return _TextId2;
  //## end cAlarm::get_TextId2%412A2C810242.get
}

void cAlarm::set_TextId2 (ULONG_T value)
{
  //## begin cAlarm::set_TextId2%412A2C810242.set preserve=no
  _TextId2 = value;
  //## end cAlarm::set_TextId2%412A2C810242.set
}

STRING_T cAlarm::get_Text2 () const
{
  //## begin cAlarm::get_Text2%407261CA0186.get preserve=no
  return _Text2;
  //## end cAlarm::get_Text2%407261CA0186.get
}

void cAlarm::set_Text2 (STRING_T value)
{
  //## begin cAlarm::set_Text2%407261CA0186.set preserve=no
  _Text2 = value;
  //## end cAlarm::set_Text2%407261CA0186.set
}

ULONG_T cAlarm::get_TextId3 () const
{
  //## begin cAlarm::get_TextId3%412A2C8C03D8.get preserve=no
  return _TextId3;
  //## end cAlarm::get_TextId3%412A2C8C03D8.get
}

void cAlarm::set_TextId3 (ULONG_T value)
{
  //## begin cAlarm::set_TextId3%412A2C8C03D8.set preserve=no
  _TextId3 = value;
  //## end cAlarm::set_TextId3%412A2C8C03D8.set
}

STRING_T cAlarm::get_Text3 () const
{
  //## begin cAlarm::get_Text3%407406BD01A5.get preserve=no
  return _Text3;
  //## end cAlarm::get_Text3%407406BD01A5.get
}

void cAlarm::set_Text3 (STRING_T value)
{
  //## begin cAlarm::set_Text3%407406BD01A5.set preserve=no
  _Text3 = value;
  //## end cAlarm::set_Text3%407406BD01A5.set
}

ULONG_T cAlarm::get_TextId4 () const
{
  //## begin cAlarm::get_TextId4%412A2C950242.get preserve=no
  return _TextId4;
  //## end cAlarm::get_TextId4%412A2C950242.get
}

void cAlarm::set_TextId4 (ULONG_T value)
{
  //## begin cAlarm::set_TextId4%412A2C950242.set preserve=no
  _TextId4 = value;
  //## end cAlarm::set_TextId4%412A2C950242.set
}

STRING_T cAlarm::get_Text4 () const
{
  //## begin cAlarm::get_Text4%4074071A034B.get preserve=no
  return _Text4;
  //## end cAlarm::get_Text4%4074071A034B.get
}

void cAlarm::set_Text4 (STRING_T value)
{
  //## begin cAlarm::set_Text4%4074071A034B.set preserve=no
  _Text4 = value;
  //## end cAlarm::set_Text4%4074071A034B.set
}

STRING_T cAlarm::get_Param1 () const
{
  //## begin cAlarm::get_Param1%407261B002CE.get preserve=no
  return _Param1;
  //## end cAlarm::get_Param1%407261B002CE.get
}

void cAlarm::set_Param1 (STRING_T value)
{
  //## begin cAlarm::set_Param1%407261B002CE.set preserve=no
  _Param1 = value;
  //## end cAlarm::set_Param1%407261B002CE.set
}

STRING_T cAlarm::get_Param2 () const
{
  //## begin cAlarm::get_Param2%407261B002CF.get preserve=no
  return _Param2;
  //## end cAlarm::get_Param2%407261B002CF.get
}

void cAlarm::set_Param2 (STRING_T value)
{
  //## begin cAlarm::set_Param2%407261B002CF.set preserve=no
  _Param2 = value;
  //## end cAlarm::set_Param2%407261B002CF.set
}

STRING_T cAlarm::get_Param3 () const
{
  //## begin cAlarm::get_Param3%407261B002D0.get preserve=no
  return _Param3;
  //## end cAlarm::get_Param3%407261B002D0.get
}

void cAlarm::set_Param3 (STRING_T value)
{
  //## begin cAlarm::set_Param3%407261B002D0.set preserve=no
  _Param3 = value;
  //## end cAlarm::set_Param3%407261B002D0.set
}

STRING_T cAlarm::get_Param4 () const
{
  //## begin cAlarm::get_Param4%407261B002D1.get preserve=no
  return _Param4;
  //## end cAlarm::get_Param4%407261B002D1.get
}

void cAlarm::set_Param4 (STRING_T value)
{
  //## begin cAlarm::set_Param4%407261B002D1.set preserve=no
  _Param4 = value;
  //## end cAlarm::set_Param4%407261B002D1.set
}

cTimeObject cAlarm::get_AcknowledgedTimeStamp () const
{
  //## begin cAlarm::get_AcknowledgedTimeStamp%45A38210006D.get preserve=no
  return _AcknowledgedTimeStamp;
  //## end cAlarm::get_AcknowledgedTimeStamp%45A38210006D.get
}

void cAlarm::set_AcknowledgedTimeStamp (cTimeObject value)
{
  //## begin cAlarm::set_AcknowledgedTimeStamp%45A38210006D.set preserve=no
  _AcknowledgedTimeStamp = value;
  //## end cAlarm::set_AcknowledgedTimeStamp%45A38210006D.set
}

STRING_T cAlarm::get_HelpId () const
{
  return _HelpId;
}

void cAlarm::set_HelpId (STRING_T value)
{
  _HelpId = value;
}

// Additional Declarations
  //## begin cAlarm%3DDBC52A0206.declarations preserve=yes
  //## end cAlarm%3DDBC52A0206.declarations

//## begin module%3DDBC52A0206.epilog preserve=yes
//## end module%3DDBC52A0206.epilog
