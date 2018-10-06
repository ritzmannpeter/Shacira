//## begin module%3A530768030F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A530768030F.cm

//## begin module%3A530768030F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A530768030F.cp

//## Module: cConfigurationObject%3A530768030F; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cConfigurationObject.cpp

//## begin module%3A530768030F.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A530768030F.additionalIncludes

//## begin module%3A530768030F.includes preserve=yes
//## end module%3A530768030F.includes

// cTypeFactory
#include "System/Config/cTypeFactory.h"
// cTypeDef
#include "System/Config/cTypeDef.h"
// cConfiguration
#include "System/Config/cConfiguration.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
//## begin module%3A530768030F.additionalDeclarations preserve=yes
//## end module%3A530768030F.additionalDeclarations


// Class cConfigurationObject 










cConfigurationObject::cConfigurationObject()
  //## begin cConfigurationObject::cConfigurationObject%.hasinit preserve=no
      : _HasChildren(false), _Referenced(false), _Configuration(NULL), _TypeDef(NULL), _TypeFactory(NULL)
  //## end cConfigurationObject::cConfigurationObject%.hasinit
  //## begin cConfigurationObject::cConfigurationObject%.initialization preserve=yes
  //## end cConfigurationObject::cConfigurationObject%.initialization
{
  //## begin cConfigurationObject::cConfigurationObject%.body preserve=yes
  //## end cConfigurationObject::cConfigurationObject%.body
}

cConfigurationObject::cConfigurationObject(const cConfigurationObject &right)
  //## begin cConfigurationObject::cConfigurationObject%copy.hasinit preserve=no
      : _HasChildren(false), _Referenced(false), _Configuration(NULL), _TypeDef(NULL), _TypeFactory(NULL)
  //## end cConfigurationObject::cConfigurationObject%copy.hasinit
  //## begin cConfigurationObject::cConfigurationObject%copy.initialization preserve=yes
  //## end cConfigurationObject::cConfigurationObject%copy.initialization
{
  //## begin cConfigurationObject::cConfigurationObject%copy.body preserve=yes
   _Configuration = right._Configuration;
   _Name = right._Name;
  //## end cConfigurationObject::cConfigurationObject%copy.body
}

cConfigurationObject::cConfigurationObject (cConfiguration *configuration, CONST_STRING_T name, CONST_STRING_T type_name, CONST_STRING_T source)
  //## begin cConfigurationObject::cConfigurationObject%978518090.hasinit preserve=no
      : _HasChildren(false), _Referenced(false), _Configuration(NULL), _TypeDef(NULL), _TypeFactory(NULL)
  //## end cConfigurationObject::cConfigurationObject%978518090.hasinit
  //## begin cConfigurationObject::cConfigurationObject%978518090.initialization preserve=yes
  //## end cConfigurationObject::cConfigurationObject%978518090.initialization
{
  //## begin cConfigurationObject::cConfigurationObject%978518090.body preserve=yes
_ASSERT_COND(configuration != NULL)
   _TypeFactory = configuration->TypeFactory();
   _Configuration = configuration;
   _Name = name;
   _TypeName = type_name;
   _Source = source;
   cTypeDef * type_def = _TypeFactory->Definition(type_name);
   if (type_def != NULL) {
      _TypeDef = type_def;
   } else {
      throw cError(CONFIG_INVALID_TYPEDEF, 0, type_name, name);
   }
  //## end cConfigurationObject::cConfigurationObject%978518090.body
}


cConfigurationObject::~cConfigurationObject()
{
  //## begin cConfigurationObject::~cConfigurationObject%.body preserve=yes
   std::map<STRING_T, cProperty*>::const_iterator i = _Properties.cbegin();
   while (i != _Properties.cend()) {
      cProperty * property = (*i).second;
      if (property != NULL) {
         delete property;
      }
      i++;
   }
   _Properties.clear();
  //## end cConfigurationObject::~cConfigurationObject%.body
}



//## Other Operations (implementation)
cConfiguration * cConfigurationObject::Configuration () const
{
  //## begin cConfigurationObject::Configuration%1011095977.body preserve=yes
   return _Configuration;
  //## end cConfigurationObject::Configuration%1011095977.body
}

cTypeDef * cConfigurationObject::TypeDef ()
{
  //## begin cConfigurationObject::TypeDef%1011095988.body preserve=yes
   return _TypeDef;
  //## end cConfigurationObject::TypeDef%1011095988.body
}

BOOL_T cConfigurationObject::IsRoot ()
{
  //## begin cConfigurationObject::IsRoot%1011204314.body preserve=yes
   if (_HasChildren && !_Referenced) {
      return true;
   } else {
      return false;
   }
  //## end cConfigurationObject::IsRoot%1011204314.body
}

void cConfigurationObject::SetProperty (cProperty *property)
{
  //## begin cConfigurationObject::SetProperty%1011095975.body preserve=yes
   STRING_T name = property->get_Name().c_str();
   if (Property(name.c_str()) == NULL) {
      _Properties[name.c_str()] = property;
   } else {
      throw cError(CONFIG_AMBIGUOUS_PROPERTY, 0, name.c_str());
   }
  //## end cConfigurationObject::SetProperty%1011095975.body
}

void cConfigurationObject::Resolve ()
{
  //## begin cConfigurationObject::Resolve%1011095993.body preserve=yes
   std::map<STRING_T, cProperty*>::const_iterator i = _Properties.cbegin();
   while (i != _Properties.cend()) {
      cProperty * property = (*i).second;
      property->Resolve();
      i++;
   }
  //## end cConfigurationObject::Resolve%1011095993.body
}

void cConfigurationObject::Save ()
{
  //## begin cConfigurationObject::Save%1011186742.body preserve=yes
   std::map<STRING_T, cProperty*>::const_iterator i = _Properties.cbegin();
   while (i != _Properties.cend()) {
      cProperty * property = (*i).second;
      property->Save();
      i++;
   }
  //## end cConfigurationObject::Save%1011186742.body
}

cProperty * cConfigurationObject::Property (CONST_STRING_T name) const
{
  //## begin cConfigurationObject::Property%978594336.body preserve=yes
   std::map<STRING_T,cProperty*>::const_iterator i = _Properties.find(name);
   if (i == _Properties.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cConfigurationObject::Property%978594336.body
}

cProperty * cConfigurationObject::Property (CONST_STRING_T name, BOOL_T mandatory)
{
  //## begin cConfigurationObject::Property%980256069.body preserve=yes
   cProperty * property = Property(name);
   if (property == NULL && mandatory) throw cError(CONFIG_NO_PROPVAL, 0, name, _Name.c_str());
   return property;
  //## end cConfigurationObject::Property%980256069.body
}

ULONG_T cConfigurationObject::PropertyList (STRING_LIST_T &property_list)
{
  //## begin cConfigurationObject::PropertyList%980778564.body preserve=yes
   std::map<STRING_T, cProperty*>::const_iterator i = _Properties.cbegin();
   while (i != _Properties.cend()) {
      property_list.push_back((*i).first);
      i++;
   }
   return property_list.size();
  //## end cConfigurationObject::PropertyList%980778564.body
}

DOUBLE_T cConfigurationObject::PropertyValue (CONST_STRING_T name, DOUBLE_T default_value, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%980256062.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return default_value;
   } else {
      return property->Value(default_value);
   }
  //## end cConfigurationObject::PropertyValue%980256062.body
}

LONG_T cConfigurationObject::PropertyValue (CONST_STRING_T name, LONG_T default_value, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%1011095974.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return default_value;
   } else {
      return property->Value(default_value);
   }
  //## end cConfigurationObject::PropertyValue%1011095974.body
}

ULONG_T cConfigurationObject::PropertyValue (CONST_STRING_T name, ULONG_T default_value, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%1011276241.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return default_value;
   } else {
      return property->Value(default_value);
   }
  //## end cConfigurationObject::PropertyValue%1011276241.body
}

BOOL_T cConfigurationObject::PropertyValue (CONST_STRING_T name, BOOL_T default_value, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%980256064.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return default_value;
   } else {
      return property->Value(default_value);
   }
  //## end cConfigurationObject::PropertyValue%980256064.body
}

STRING_T cConfigurationObject::PropertyValue (CONST_STRING_T name, CONST_STRING_T default_value, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%980256065.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return default_value;
   } else {
      return property->Value(default_value);
   }
  //## end cConfigurationObject::PropertyValue%980256065.body
}

cConfigurationObject * cConfigurationObject::PropertyValue (CONST_STRING_T name, cConfigurationObject *default_value, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%981360505.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return default_value;
   } else {
      return property->Value(default_value);
   }
  //## end cConfigurationObject::PropertyValue%981360505.body
}

INT_T cConfigurationObject::PropertyValue (CONST_STRING_T name, STRING_VECTOR_T &vec, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%1011114948.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return 0;
   } else {
      return property->Value(vec);
   }
  //## end cConfigurationObject::PropertyValue%1011114948.body
}

INT_T cConfigurationObject::PropertyValue (CONST_STRING_T name, NUMERIC_VECTOR_T &vec, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%1011114949.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return 0;
   } else {
      return property->Value(vec);
   }
  //## end cConfigurationObject::PropertyValue%1011114949.body
}

INT_T cConfigurationObject::PropertyValue (CONST_STRING_T name, CONFOBJ_VECTOR_T &vec, BOOL_T mandatory)
{
  //## begin cConfigurationObject::PropertyValue%1011114950.body preserve=yes
   cProperty * property = Property(name, mandatory);
   if (property == NULL) {
      return 0;
   } else {
      return property->Value(vec);
   }
  //## end cConfigurationObject::PropertyValue%1011114950.body
}

void cConfigurationObject::SetPropertyValue (CONST_STRING_T name, CONST_STRING_T value, ULONG_T index)
{
  //## begin cConfigurationObject::SetPropertyValue%1011186740.body preserve=yes
   cProperty * property = Property(name, true);
   if (property != NULL) property->SetValue(value, index);
  //## end cConfigurationObject::SetPropertyValue%1011186740.body
}

void cConfigurationObject::SetPropertyValue (CONST_STRING_T name, DOUBLE_T value, ULONG_T index)
{
  //## begin cConfigurationObject::SetPropertyValue%1011186752.body preserve=yes
   cProperty * property = Property(name, true);
   if (property != NULL) property->SetValue(value, index);
  //## end cConfigurationObject::SetPropertyValue%1011186752.body
}

void cConfigurationObject::SetPropertyValue (CONST_STRING_T name, LONG_T value, ULONG_T index)
{
  //## begin cConfigurationObject::SetPropertyValue%1011186755.body preserve=yes
   cProperty * property = Property(name, true);
   if (property != NULL) property->SetValue(value, index);
  //## end cConfigurationObject::SetPropertyValue%1011186755.body
}

void cConfigurationObject::SetPropertyValue (CONST_STRING_T name, ULONG_T value, ULONG_T index)
{
  //## begin cConfigurationObject::SetPropertyValue%1011276242.body preserve=yes
   cProperty * property = Property(name, true);
   if (property != NULL) property->SetValue(value, index);
  //## end cConfigurationObject::SetPropertyValue%1011276242.body
}

void cConfigurationObject::SetPropertyValue (CONST_STRING_T name, cConfigurationObject *value, ULONG_T index)
{
  //## begin cConfigurationObject::SetPropertyValue%1011186753.body preserve=yes
   cProperty * property = Property(name, true);
   if (property != NULL) property->SetValue(value, index);
  //## end cConfigurationObject::SetPropertyValue%1011186753.body
}

void cConfigurationObject::SetPropertyValue (CONST_STRING_T name, BOOL_T value, ULONG_T index)
{
  //## begin cConfigurationObject::SetPropertyValue%1011186754.body preserve=yes
   cProperty * property = Property(name, true);
   if (property != NULL) property->SetValue(value, index);
  //## end cConfigurationObject::SetPropertyValue%1011186754.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cConfigurationObject::get_Name () const
{
  //## begin cConfigurationObject::get_Name%3A5307CA019D.get preserve=no
  return _Name;
  //## end cConfigurationObject::get_Name%3A5307CA019D.get
}

STRING_T cConfigurationObject::get_TypeName () const
{
  //## begin cConfigurationObject::get_TypeName%3C45D6A101BF.get preserve=no
  return _TypeName;
  //## end cConfigurationObject::get_TypeName%3C45D6A101BF.get
}

STRING_T cConfigurationObject::get_Source () const
{
  //## begin cConfigurationObject::get_Source%3A542F2600F0.get preserve=no
  return _Source;
  //## end cConfigurationObject::get_Source%3A542F2600F0.get
}

void cConfigurationObject::set_Source (STRING_T value)
{
  //## begin cConfigurationObject::set_Source%3A542F2600F0.set preserve=no
  _Source = value;
  //## end cConfigurationObject::set_Source%3A542F2600F0.set
}

BOOL_T cConfigurationObject::get_HasChildren () const
{
  //## begin cConfigurationObject::get_HasChildren%3C45C6EE02E2.get preserve=no
  return _HasChildren;
  //## end cConfigurationObject::get_HasChildren%3C45C6EE02E2.get
}

void cConfigurationObject::set_HasChildren (BOOL_T value)
{
  //## begin cConfigurationObject::set_HasChildren%3C45C6EE02E2.set preserve=no
  _HasChildren = value;
  //## end cConfigurationObject::set_HasChildren%3C45C6EE02E2.set
}

BOOL_T cConfigurationObject::get_Referenced () const
{
  //## begin cConfigurationObject::get_Referenced%3C45D4EC029D.get preserve=no
  return _Referenced;
  //## end cConfigurationObject::get_Referenced%3C45D4EC029D.get
}

void cConfigurationObject::set_Referenced (BOOL_T value)
{
  //## begin cConfigurationObject::set_Referenced%3C45D4EC029D.set preserve=no
  _Referenced = value;
  //## end cConfigurationObject::set_Referenced%3C45D4EC029D.set
}

// Additional Declarations
  //## begin cConfigurationObject%3A530768030F.declarations preserve=yes
  //## end cConfigurationObject%3A530768030F.declarations

//## begin module%3A530768030F.epilog preserve=yes
//## end module%3A530768030F.epilog
