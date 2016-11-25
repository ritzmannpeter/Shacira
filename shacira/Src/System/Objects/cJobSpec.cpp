//## begin module%3DDBC48B032A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DDBC48B032A.cm

//## begin module%3DDBC48B032A.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DDBC48B032A.cp

//## Module: cJobSpec%3DDBC48B032A; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cJobSpec.cpp

//## begin module%3DDBC48B032A.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DDBC48B032A.additionalIncludes

//## begin module%3DDBC48B032A.includes preserve=yes
//## end module%3DDBC48B032A.includes

// cTransferObject
#include "System/Objects/cTransferObject.h"
// cJobSpec
#include "System/Objects/cJobSpec.h"
//## begin module%3DDBC48B032A.additionalDeclarations preserve=yes
//## end module%3DDBC48B032A.additionalDeclarations


// Class cJobSpec 







cJobSpec::cJobSpec()
  //## begin cJobSpec::cJobSpec%.hasinit preserve=no
      : _RefreshType(UNDEFINED), _RefreshValue(0)
  //## end cJobSpec::cJobSpec%.hasinit
  //## begin cJobSpec::cJobSpec%.initialization preserve=yes
  //## end cJobSpec::cJobSpec%.initialization
{
  //## begin cJobSpec::cJobSpec%.body preserve=yes
   _Type = OT_JOB_SPEC;
  //## end cJobSpec::cJobSpec%.body
}

cJobSpec::cJobSpec(const cJobSpec &right)
  //## begin cJobSpec::cJobSpec%copy.hasinit preserve=no
      : _RefreshType(UNDEFINED), _RefreshValue(0)
  //## end cJobSpec::cJobSpec%copy.hasinit
  //## begin cJobSpec::cJobSpec%copy.initialization preserve=yes
  //## end cJobSpec::cJobSpec%copy.initialization
{
  //## begin cJobSpec::cJobSpec%copy.body preserve=yes
	_JobName = right._JobName;
	_RefreshType = right._RefreshType;
	_RefreshValue = right._RefreshValue;
	_Properties = right._Properties;
  //## end cJobSpec::cJobSpec%copy.body
}

cJobSpec::cJobSpec (cStaticObject *source, CONST_STRING_T job_name, UCHAR_T refresh_type, ULONG_T refresh_value)
  //## begin cJobSpec::cJobSpec%1047655597.hasinit preserve=no
      : _RefreshType(UNDEFINED), _RefreshValue(0)
  //## end cJobSpec::cJobSpec%1047655597.hasinit
  //## begin cJobSpec::cJobSpec%1047655597.initialization preserve=yes
  , cTransientObject(source)
  //## end cJobSpec::cJobSpec%1047655597.initialization
{
  //## begin cJobSpec::cJobSpec%1047655597.body preserve=yes
   _Type = OT_JOB_SPEC;
	_JobName = job_name;
	_RefreshType = refresh_type;
	_RefreshValue = refresh_value;
  //## end cJobSpec::cJobSpec%1047655597.body
}


cJobSpec::~cJobSpec()
{
  //## begin cJobSpec::~cJobSpec%.body preserve=yes
  //## end cJobSpec::~cJobSpec%.body
}



//## Other Operations (implementation)
ULONG_T cJobSpec::Properties ()
{
  //## begin cJobSpec::Properties%1047655598.body preserve=yes
	return _Properties.size();
  //## end cJobSpec::Properties%1047655598.body
}

STRING_T cJobSpec::Property (ULONG_T index)
{
  //## begin cJobSpec::Property%1047655599.body preserve=yes
	if (index < _Properties.size()) {
		return _Properties[index];
	} else {
		throw cError(JOB_SPEC_INVALID_INDEX, 0, _JobName.c_str(),
						 cConvUtils::StringValue(index).c_str());
	}
  //## end cJobSpec::Property%1047655599.body
}

void cJobSpec::AddProperty (CONST_STRING_T property_name)
{
  //## begin cJobSpec::AddProperty%1047655600.body preserve=yes
	ULONG_T index = _Properties.size();
	Resize(index);
	_Properties[index] = property_name;
  //## end cJobSpec::AddProperty%1047655600.body
}

void cJobSpec::RemoveProperty(CONST_STRING_T property_name)
{
	STRING_VECTOR_T::iterator it = _Properties.begin();

	while (it != _Properties.end())
	{
		STRING_T str = *(it);
		if (str == property_name)
		{
			_Properties.erase(it);
			break;
		}
		it++;
	}

	_FlagMap.erase(property_name);

}

void cJobSpec::SetNameList (STRING_LIST_T name_list)
{
  //## begin cJobSpec::SetNameList%1138452345.body preserve=yes
   STRING_LIST_T::const_iterator i = name_list.begin();
   while (i != name_list.end()) {
      AddProperty((*i).c_str());
      i++;
   }
  //## end cJobSpec::SetNameList%1138452345.body
}

void cJobSpec::SetNameList (CONST_STRING_T *name_list)
{
  //## begin cJobSpec::SetNameList%1138452346.body preserve=yes
   CONST_STRING_T * name_ptr = name_list;
   CONST_STRING_T name = *name_ptr;
   while (name != NULL) {
      AddProperty(name);
      name_ptr++;
      name = *name_ptr;
   }
  //## end cJobSpec::SetNameList%1138452346.body
}

BOOL_T cJobSpec::Exists (CONST_STRING_T property_name)
{
  //## begin cJobSpec::Exists%1048090498.body preserve=yes
   ULONG_T names = _Properties.size();
   for (ULONG_T i=0; i<names; i++) {
      if (strcmp(property_name, _Properties[i].c_str()) == 0) return true;
   }
   return false;
  //## end cJobSpec::Exists%1048090498.body
}

STRING_T cJobSpec::Serialize ()
{
  //## begin cJobSpec::Serialize%1046160460.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _JobName.c_str(), ObjectBody);
   obj.AddAttribute(1, _RefreshType, ObjectBody);
   obj.AddAttribute(2, _RefreshValue, ObjectBody);
	ULONG_T properties = _Properties.size();
	for (ULONG_T i=0; i<properties; i++) {
		obj.AddAttribute(i, _Properties[i].c_str(), ObjectParams);
		obj.AddAttribute(i, GetFlags(_Properties[i].c_str()), ObjectFlags);
	}
   return obj.Serialize().c_str();
  //## end cJobSpec::Serialize%1046160460.body
}

BOOL_T cJobSpec::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cJobSpec::Construct%1046160461.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) {
      return false;
   }
   obj.GetAttribute(0, _JobName, ObjectBody);
   obj.GetAttribute(1, _RefreshType, ObjectBody);
   obj.GetAttribute(2, _RefreshValue, ObjectBody);
	STRING_T property_name;
   ULONG_T flags = 0;
   ULONG_T params = obj.Params();
	for (ULONG_T i=0; i<params; i++) {
		obj.GetAttribute(i, property_name, ObjectParams);
		AddProperty(property_name.c_str());
		obj.GetAttribute(i, flags, ObjectFlags);
      SetFlags(property_name.c_str(), flags);
	}
   return true;
  //## end cJobSpec::Construct%1046160461.body
}

BOOL_T cJobSpec::SetFlags (CONST_STRING_T property_name, ULONG_T flags)
{
  //## begin cJobSpec::SetFlags%1100678884.body preserve=yes
   _FlagMap[property_name] = flags;
   return true;
  //## end cJobSpec::SetFlags%1100678884.body
}

BOOL_T cJobSpec::SetFlag (CONST_STRING_T property_name, UCHAR_T flag_pos, BOOL_T state)
{
  //## begin cJobSpec::SetFlag%1100678885.body preserve=yes
   if (flag_pos > 32) {
      return false;
   } else {
      ULONG_T flags = GetFlags(property_name);
      if (state) {
         flags |= (1 << flag_pos);
      } else {
         flags &= (~(1 << flag_pos));
      }
      SetFlags(property_name, flags);
      return true;
   }
  //## end cJobSpec::SetFlag%1100678885.body
}

ULONG_T cJobSpec::GetFlags (CONST_STRING_T property_name)
{
  //## begin cJobSpec::GetFlags%1100678886.body preserve=yes
   ULONG_MAP_T::const_iterator i = _FlagMap.find(property_name);
   if (i != _FlagMap.end()) {
      return (*i).second;
   }
   return 0;
  //## end cJobSpec::GetFlags%1100678886.body
}

BOOL_T cJobSpec::GetFlag (CONST_STRING_T property_name, UCHAR_T flag_pos)
{
  //## begin cJobSpec::GetFlag%1100678887.body preserve=yes
   if (flag_pos > 32) {
      return false;
   } else {
      ULONG_T flags = GetFlags(property_name);
      if (flags & (1 << flag_pos)) {
         return true;
      } else {
         return false;
      }
   }
  //## end cJobSpec::GetFlag%1100678887.body
}

BOOL_T cJobSpec::Matches (cJobSpec *job_spec)
{
  //## begin cJobSpec::Matches%1106841437.body preserve=yes
   ULONG_T properties = Properties();
   if (properties != job_spec->Properties()) {
      return false;
   }
   for (ULONG_T i=0; i<properties; i++) {
      STRING_T prop1 = Property(i);
      STRING_T prop2 = job_spec->Property(i);
      if (strcmp(prop1.c_str(), prop2.c_str()) != 0) {
         return false;
      }
   }
   return true;
  //## end cJobSpec::Matches%1106841437.body
}

void cJobSpec::Resize (ULONG_T index)
{
  //## begin cJobSpec::Resize%1047655601.body preserve=yes
	if (index >= _Properties.size()) {
		_Properties.resize(index + 1);
	}
  //## end cJobSpec::Resize%1047655601.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cJobSpec::get_JobName () const
{
  //## begin cJobSpec::get_JobName%3DDCDB400236.get preserve=no
  return _JobName;
  //## end cJobSpec::get_JobName%3DDCDB400236.get
}

void cJobSpec::set_JobName (STRING_T value)
{
  //## begin cJobSpec::set_JobName%3DDCDB400236.set preserve=no
  _JobName = value;
  //## end cJobSpec::set_JobName%3DDCDB400236.set
}

ULONG_T cJobSpec::get_RefreshType () const
{
  //## begin cJobSpec::get_RefreshType%3E71F31500BB.get preserve=no
  return _RefreshType;
  //## end cJobSpec::get_RefreshType%3E71F31500BB.get
}

void cJobSpec::set_RefreshType (ULONG_T value)
{
  //## begin cJobSpec::set_RefreshType%3E71F31500BB.set preserve=no
  _RefreshType = value;
  //## end cJobSpec::set_RefreshType%3E71F31500BB.set
}

ULONG_T cJobSpec::get_RefreshValue () const
{
  //## begin cJobSpec::get_RefreshValue%3E71F3440290.get preserve=no
  return _RefreshValue;
  //## end cJobSpec::get_RefreshValue%3E71F3440290.get
}

void cJobSpec::set_RefreshValue (ULONG_T value)
{
  //## begin cJobSpec::set_RefreshValue%3E71F3440290.set preserve=no
  _RefreshValue = value;
  //## end cJobSpec::set_RefreshValue%3E71F3440290.set
}

// Additional Declarations
  //## begin cJobSpec%3DDBC48B032A.declarations preserve=yes
  //## end cJobSpec%3DDBC48B032A.declarations

//## begin module%3DDBC48B032A.epilog preserve=yes
//## end module%3DDBC48B032A.epilog
