//## begin module%3DDBC4B0023D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DDBC4B0023D.cm

//## begin module%3DDBC4B0023D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DDBC4B0023D.cp

//## Module: cJobEntry%3DDBC4B0023D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cJobEntry.cpp

//## begin module%3DDBC4B0023D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3DDBC4B0023D.additionalIncludes

//## begin module%3DDBC4B0023D.includes preserve=yes
//## end module%3DDBC4B0023D.includes

// cTransferObject
#include "System/Objects/cTransferObject.h"
// cJobEntry
#include "System/Objects/cJobEntry.h"
// cJobSpec
#include "System/Objects/cJobSpec.h"
//## begin module%3DDBC4B0023D.additionalDeclarations preserve=yes
//## end module%3DDBC4B0023D.additionalDeclarations


// Class cJobEntry 











cJobEntry::cJobEntry()
  //## begin cJobEntry::cJobEntry%.hasinit preserve=no
      : _RefreshType(UNDEFINED), _RefreshValue(0), _Shot(0), _Quality(NO_QUALITY)
  //## end cJobEntry::cJobEntry%.hasinit
  //## begin cJobEntry::cJobEntry%.initialization preserve=yes
  //## end cJobEntry::cJobEntry%.initialization
{
  //## begin cJobEntry::cJobEntry%.body preserve=yes
   _Type = OT_JOB_ENTRY;
  //## end cJobEntry::cJobEntry%.body
}

cJobEntry::cJobEntry(const cJobEntry &right)
  //## begin cJobEntry::cJobEntry%copy.hasinit preserve=no
      : _RefreshType(UNDEFINED), _RefreshValue(0), _Shot(0), _Quality(NO_QUALITY)
  //## end cJobEntry::cJobEntry%copy.hasinit
  //## begin cJobEntry::cJobEntry%copy.initialization preserve=yes
  //## end cJobEntry::cJobEntry%copy.initialization
{
  //## begin cJobEntry::cJobEntry%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cJobEntry::cJobEntry%copy.body
}

cJobEntry::cJobEntry (cStaticObject *source, CONST_STRING_T job_name)
  //## begin cJobEntry::cJobEntry%1047655602.hasinit preserve=no
      : _RefreshType(UNDEFINED), _RefreshValue(0), _Shot(0), _Quality(NO_QUALITY)
  //## end cJobEntry::cJobEntry%1047655602.hasinit
  //## begin cJobEntry::cJobEntry%1047655602.initialization preserve=yes
  , cTransientObject(source)
  //## end cJobEntry::cJobEntry%1047655602.initialization
{
  //## begin cJobEntry::cJobEntry%1047655602.body preserve=yes
   _Type = OT_JOB_ENTRY;
	_JobName = job_name;
  //## end cJobEntry::cJobEntry%1047655602.body
}

cJobEntry::cJobEntry (cStaticObject *source, cJobSpec *job_spec)
  //## begin cJobEntry::cJobEntry%1138452012.hasinit preserve=no
      : _RefreshType(UNDEFINED), _RefreshValue(0), _Shot(0), _Quality(NO_QUALITY)
  //## end cJobEntry::cJobEntry%1138452012.hasinit
  //## begin cJobEntry::cJobEntry%1138452012.initialization preserve=yes
  , cTransientObject(source)
  //## end cJobEntry::cJobEntry%1138452012.initialization
{
  //## begin cJobEntry::cJobEntry%1138452012.body preserve=yes
   _Type = OT_JOB_ENTRY;
   int properties = job_spec->Properties();
   for (int i=0; i<properties; i++) {
      STRING_T property = job_spec->Property(i);
      AddProperty(property.c_str());
   }
  //## end cJobEntry::cJobEntry%1138452012.body
}


cJobEntry::~cJobEntry()
{
  //## begin cJobEntry::~cJobEntry%.body preserve=yes
  //## end cJobEntry::~cJobEntry%.body
}



//## Other Operations (implementation)
ULONG_T cJobEntry::Properties ()
{
  //## begin cJobEntry::Properties%1047655603.body preserve=yes
	return _Properties.size();
  //## end cJobEntry::Properties%1047655603.body
}

BOOL_T cJobEntry::PropertyExists (CONST_STRING_T property_name)
{
  //## begin cJobEntry::PropertyExists%1047655618.body preserve=yes
	ULONG_MAP_T::const_iterator i = _PropertyMap.find(property_name);
	if (i != _PropertyMap.end()) {
		return true;
	} else {
		return false;
	}
  //## end cJobEntry::PropertyExists%1047655618.body
}

STRING_T cJobEntry::Property (ULONG_T index)
{
  //## begin cJobEntry::Property%1047655613.body preserve=yes
	if (index < _Properties.size()) {
		return _Properties[index];
	} else {
		throw cError(JOB_ENTRY_INVALID_PROPERTY_INDEX, 0, _JobName.c_str(),
						 cConvUtils::StringValue(index).c_str());
	}
  //## end cJobEntry::Property%1047655613.body
}

STRING_T cJobEntry::PropertyValue (ULONG_T index)
{
  //## begin cJobEntry::PropertyValue%1047655614.body preserve=yes
	if (index < _PropertyValues.size()) {
		return _PropertyValues[index];
	} else {
		throw cError(JOB_ENTRY_INVALID_VALUE_INDEX, 0, _JobName.c_str(),
						 cConvUtils::StringValue(index).c_str());
	}
  //## end cJobEntry::PropertyValue%1047655614.body
}

STRING_T cJobEntry::PropertyValue (CONST_STRING_T property_name)
{
  //## begin cJobEntry::PropertyValue%1047655615.body preserve=yes
	ULONG_MAP_T::const_iterator i = _PropertyMap.find(property_name);
	if (i != _PropertyMap.end()) {
		return PropertyValue((*i).second);
	} else {
		throw cError(JOB_ENTRY_INVALID_PROPERTY, 0, _JobName.c_str(), property_name);
	}
  //## end cJobEntry::PropertyValue%1047655615.body
}

void cJobEntry::AddProperty (CONST_STRING_T property_name)
{
  //## begin cJobEntry::AddProperty%1047655616.body preserve=yes
	ULONG_T index = _Properties.size();
	ULONG_MAP_T::const_iterator i = _PropertyMap.find(property_name);
	if (i != _PropertyMap.end()) {
		index = (*i).second;
		Resize(index);
	} else {
		index = _Properties.size();
		Resize(index);
		_PropertyMap[property_name] = index;
	}
	_Properties[index] = property_name;
  //## end cJobEntry::AddProperty%1047655616.body
}

void cJobEntry::AddPropertyValue (CONST_STRING_T property_name, CONST_STRING_T value)
{
  //## begin cJobEntry::AddPropertyValue%1047655617.body preserve=yes
	ULONG_T index = _Properties.size();
	ULONG_MAP_T::const_iterator i = _PropertyMap.find(property_name);
	if (i != _PropertyMap.end()) {
		index = (*i).second;
		Resize(index);
	} else {
		index = _Properties.size();
		Resize(index);
		_PropertyMap[property_name] = index;
	}
	_Properties[index] = property_name;
	_PropertyValues[index] = value;
  //## end cJobEntry::AddPropertyValue%1047655617.body
}

void cJobEntry::AddPropertyValue (ULONG_T index, CONST_STRING_T property_name, CONST_STRING_T value)
{
  //## begin cJobEntry::AddPropertyValue%1047655619.body preserve=yes
	if (index < _Properties.size()) {
		throw cError(JOB_ENTRY_INVALID_OPERATION, 0, _JobName.c_str(),
						 cConvUtils::StringValue(index).c_str(), "AddPropertyValue");
	} else {
		Resize(index);
		_PropertyMap[property_name] = index;
		_Properties[index] = property_name;
		_PropertyValues[index] = value;
	}
  //## end cJobEntry::AddPropertyValue%1047655619.body
}

STRING_T cJobEntry::Serialize ()
{
  //## begin cJobEntry::Serialize%1046160458.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _JobName.c_str(), ObjectBody);
   obj.AddAttribute(1, _RefreshType, ObjectBody);
   obj.AddAttribute(2, _RefreshValue, ObjectBody);
   obj.AddAttribute(3, _Shot, ObjectBody);
   obj.AddAttribute(4, _Quality, ObjectBody);
   obj.AddAttribute(5, _Ident.c_str(), ObjectBody);
	ULONG_T properties = _Properties.size();
	for (ULONG_T i=0; i<properties; i++) {
		obj.AddAttribute(i, _Properties[i].c_str(), ObjectParams);
		obj.AddAttribute(i, _PropertyValues[i].c_str(), ObjectParamValues);
		obj.AddAttribute(i, GetFlags(_Properties[i].c_str()), ObjectFlags);
	}
   return obj.Serialize().c_str();
  //## end cJobEntry::Serialize%1046160458.body
}

BOOL_T cJobEntry::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cJobEntry::Construct%1046160459.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _JobName, ObjectBody);
   obj.GetAttribute(1, _RefreshType, ObjectBody);
   obj.GetAttribute(2, _RefreshValue, ObjectBody);
   obj.GetAttribute(3, _Shot, ObjectBody);
   obj.GetAttribute(4, _Quality, ObjectBody);
   obj.GetAttribute(5, _Ident, ObjectBody);
	STRING_T property_name;
	STRING_T property_value;
	ULONG_T flags;
	ULONG_T params = obj.Params();
	for (ULONG_T i=0; i<params; i++) {
		obj.GetAttribute(i, property_name, ObjectParams);
		obj.GetAttribute(i, property_value, ObjectParamValues);
		obj.GetAttribute(i, flags, ObjectFlags);
      SetFlags(property_name.c_str(), flags);
		AddPropertyValue(i, property_name.c_str(), property_value.c_str());
	}
   return true;
  //## end cJobEntry::Construct%1046160459.body
}

void cJobEntry::SetPropertyValue (ULONG_T index, CONST_STRING_T value)
{
  //## begin cJobEntry::SetPropertyValue%1097751638.body preserve=yes
	if (index < _Properties.size()) {
		_PropertyValues[index] = value;
	}
  //## end cJobEntry::SetPropertyValue%1097751638.body
}

BOOL_T cJobEntry::SetFlags (CONST_STRING_T property, ULONG_T flags)
{
  //## begin cJobEntry::SetFlags%1100678880.body preserve=yes
   _FlagMap[property] = flags;
   return true;
  //## end cJobEntry::SetFlags%1100678880.body
}

BOOL_T cJobEntry::SetFlag (CONST_STRING_T property, UCHAR_T flag_pos, BOOL_T state)
{
  //## begin cJobEntry::SetFlag%1100678881.body preserve=yes
   if (flag_pos > 32) {
      return false;
   } else {
      ULONG_T flags = GetFlags(property);
      if (state) {
         flags |= (1 << flag_pos);
      } else {
         flags &= (~(1 << flag_pos));
      }
      SetFlags(property, flags);
      return true;
   }
  //## end cJobEntry::SetFlag%1100678881.body
}

ULONG_T cJobEntry::GetFlags (CONST_STRING_T property)
{
  //## begin cJobEntry::GetFlags%1100678882.body preserve=yes
   ULONG_MAP_T::const_iterator i = _FlagMap.find(property);
   if (i != _FlagMap.end()) {
      return (*i).second;
   }
   return 0;
  //## end cJobEntry::GetFlags%1100678882.body
}

BOOL_T cJobEntry::GetFlag (CONST_STRING_T property, UCHAR_T flag_pos)
{
  //## begin cJobEntry::GetFlag%1100678883.body preserve=yes
   if (flag_pos > 32) {
      return false;
   } else {
      ULONG_T flags = GetFlags(property);
      if (flags & (1 << flag_pos)) {
         return true;
      } else {
         return false;
      }
   }
  //## end cJobEntry::GetFlag%1100678883.body
}

BOOL_T cJobEntry::Matches (cJobEntry *job_entry)
{
  //## begin cJobEntry::Matches%1106841435.body preserve=yes
   ULONG_T properties = Properties();
   if (properties != job_entry->Properties()) {
      return false;
   }
   for (ULONG_T i=0; i<properties; i++) {
      STRING_T prop1 = Property(i);
      STRING_T prop2 = job_entry->Property(i);
      if (strcmp(prop1.c_str(), prop2.c_str()) != 0) {
         return false;
      }
   }
   return true;
  //## end cJobEntry::Matches%1106841435.body
}

BOOL_T cJobEntry::Matches (cJobSpec *job_spec)
{
  //## begin cJobEntry::Matches%1106841436.body preserve=yes
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
  //## end cJobEntry::Matches%1106841436.body
}

void cJobEntry::Resize (ULONG_T index)
{
  //## begin cJobEntry::Resize%1047655606.body preserve=yes
	if (index >= _Properties.size()) {
		_Properties.resize(index + 1);
		_PropertyValues.resize(index + 1);
	}
  //## end cJobEntry::Resize%1047655606.body
}

void cJobEntry::SetProperties (CHAR_T *prop_dst, CHAR_T *val_dst)
{
  //## begin cJobEntry::SetProperties%1094142498.body preserve=yes
   ULONG_T size = Properties();
   ULONG_T i = 0;
   STRING_T properties;
   for (i=0; i<size; i++) {
      STRING_T name = Property(i);
      if (properties.size() + name.size() + 1 > TEXT_BUF_LENGTH) {
         break;
      }
      properties += name.c_str();
      properties += ";";
   }
   memcpy(prop_dst, properties.c_str(), TEXT_BUF_LENGTH);
   STRING_T property_values;
   for (i=0; i<size; i++) {
      STRING_T value = PropertyValue(i);
      if (property_values.size() + value.size() + 1 > TEXT_BUF_LENGTH) {
         break;
      }
      property_values += value.c_str();
      property_values += ";";
   }
   memcpy(val_dst, property_values.c_str(), TEXT_BUF_LENGTH);
  //## end cJobEntry::SetProperties%1094142498.body
}

void cJobEntry::GetProperties (CONST_STRING_T prop_src, CONST_STRING_T val_src)
{
  //## begin cJobEntry::GetProperties%1094142499.body preserve=yes
   cTokenizer prop_tokenizer(prop_src, strlen(prop_src));
   cTokenizer val_tokenizer(val_src, strlen(val_src));
   CONST_STRING_T name_token = prop_tokenizer.GetToken(";");
   CONST_STRING_T val_token = val_tokenizer.GetToken(";");
   while (name_token != NULL && strlen(name_token) > 0) {
      STRING_T value = val_token == NULL ? "?" : val_token;
      AddPropertyValue(name_token, value.c_str());
      name_token = prop_tokenizer.GetToken(";");
      val_token = val_tokenizer.GetToken(";");
   }
  //## end cJobEntry::GetProperties%1094142499.body
}

void cJobEntry::SetFlagValues (ULONG_T *flag_buf)
{
  //## begin cJobEntry::SetFlagValues%1101801393.body preserve=yes
   ULONG_T flag_count = _MIN_(MAX_FLAG_COUNT,Properties());
   for (ULONG_T i=0; i<flag_count; i++) {
      try {
         ULONG_T flags = GetFlags(Property(i).c_str());
         flag_buf[i] = flags;
      } catch (...) {
         return;
      }
   }
  //## end cJobEntry::SetFlagValues%1101801393.body
}

void cJobEntry::GetFlagValues (ULONG_T *flag_buf)
{
  //## begin cJobEntry::GetFlagValues%1101801394.body preserve=yes
   ULONG_T flag_count = _MIN_(MAX_FLAG_COUNT,Properties());
   for (ULONG_T i=0; i<flag_count; i++) {
      try {
         ULONG_T flags = flag_buf[i];
         SetFlags(Property(i).c_str(), flags);
      } catch (...) {
         return;
      }
   }
  //## end cJobEntry::GetFlagValues%1101801394.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cJobEntry::get_JobName () const
{
  //## begin cJobEntry::get_JobName%3DDCDB590296.get preserve=no
  return _JobName;
  //## end cJobEntry::get_JobName%3DDCDB590296.get
}

void cJobEntry::set_JobName (STRING_T value)
{
  //## begin cJobEntry::set_JobName%3DDCDB590296.set preserve=no
  _JobName = value;
  //## end cJobEntry::set_JobName%3DDCDB590296.set
}

ULONG_T cJobEntry::get_RefreshType () const
{
  //## begin cJobEntry::get_RefreshType%41374A7301D4.get preserve=no
  return _RefreshType;
  //## end cJobEntry::get_RefreshType%41374A7301D4.get
}

void cJobEntry::set_RefreshType (ULONG_T value)
{
  //## begin cJobEntry::set_RefreshType%41374A7301D4.set preserve=no
  _RefreshType = value;
  //## end cJobEntry::set_RefreshType%41374A7301D4.set
}

ULONG_T cJobEntry::get_RefreshValue () const
{
  //## begin cJobEntry::get_RefreshValue%41374A7301D5.get preserve=no
  return _RefreshValue;
  //## end cJobEntry::get_RefreshValue%41374A7301D5.get
}

void cJobEntry::set_RefreshValue (ULONG_T value)
{
  //## begin cJobEntry::set_RefreshValue%41374A7301D5.set preserve=no
  _RefreshValue = value;
  //## end cJobEntry::set_RefreshValue%41374A7301D5.set
}

LONG_T cJobEntry::get_Shot () const
{
  //## begin cJobEntry::get_Shot%3E5B7F880157.get preserve=no
  return _Shot;
  //## end cJobEntry::get_Shot%3E5B7F880157.get
}

void cJobEntry::set_Shot (LONG_T value)
{
  //## begin cJobEntry::set_Shot%3E5B7F880157.set preserve=no
  _Shot = value;
  //## end cJobEntry::set_Shot%3E5B7F880157.set
}

INT_T cJobEntry::get_Quality () const
{
  //## begin cJobEntry::get_Quality%3E5B7FB30376.get preserve=no
  return _Quality;
  //## end cJobEntry::get_Quality%3E5B7FB30376.get
}

void cJobEntry::set_Quality (INT_T value)
{
  //## begin cJobEntry::set_Quality%3E5B7FB30376.set preserve=no
  _Quality = value;
  //## end cJobEntry::set_Quality%3E5B7FB30376.set
}

STRING_T cJobEntry::get_Ident () const
{
  //## begin cJobEntry::get_Ident%3E5B7FC60264.get preserve=no
  return _Ident;
  //## end cJobEntry::get_Ident%3E5B7FC60264.get
}

void cJobEntry::set_Ident (STRING_T value)
{
  //## begin cJobEntry::set_Ident%3E5B7FC60264.set preserve=no
  _Ident = value;
  //## end cJobEntry::set_Ident%3E5B7FC60264.set
}

// Additional Declarations
  //## begin cJobEntry%3DDBC4B0023D.declarations preserve=yes
  //## end cJobEntry%3DDBC4B0023D.declarations

//## begin module%3DDBC4B0023D.epilog preserve=yes
//## end module%3DDBC4B0023D.epilog
