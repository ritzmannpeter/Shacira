//## begin module%3A542AD30289.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A542AD30289.cm

//## begin module%3A542AD30289.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A542AD30289.cp

//## Module: cProperty%3A542AD30289; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cProperty.cpp

//## begin module%3A542AD30289.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3A542AD30289.additionalIncludes

//## begin module%3A542AD30289.includes preserve=yes
//## end module%3A542AD30289.includes

// cTokenizer
#include "System/cTokenizer.h"
// cIniFile
#include "System/cIniFile.h"
// cStringUtils
#include "System/cStringUtils.h"
// cTypeFactory
#include "System/Config/cTypeFactory.h"
// cPropertyDef
#include "System/Config/cPropertyDef.h"
// cTypeDef
#include "System/Config/cTypeDef.h"
// cConfiguration
#include "System/Config/cConfiguration.h"
// cProperty
#include "System/Config/cProperty.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
//## begin module%3A542AD30289.additionalDeclarations preserve=yes
//## end module%3A542AD30289.additionalDeclarations


// Class cProperty 











cProperty::cProperty()
  //## begin cProperty::cProperty%.hasinit preserve=no
      : _Dirty(false), _PropertyDef(NULL), _Configuration(NULL), _TypeDef(NULL), _TypeFactory(NULL), _ConfigurationObject(NULL)
  //## end cProperty::cProperty%.hasinit
  //## begin cProperty::cProperty%.initialization preserve=yes
  //## end cProperty::cProperty%.initialization
{
  //## begin cProperty::cProperty%.body preserve=yes
  //## end cProperty::cProperty%.body
}

cProperty::cProperty(const cProperty &right)
  //## begin cProperty::cProperty%copy.hasinit preserve=no
      : _Dirty(false), _PropertyDef(NULL), _Configuration(NULL), _TypeDef(NULL), _TypeFactory(NULL), _ConfigurationObject(NULL)
  //## end cProperty::cProperty%copy.hasinit
  //## begin cProperty::cProperty%copy.initialization preserve=yes
  //## end cProperty::cProperty%copy.initialization
{
  //## begin cProperty::cProperty%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cProperty::cProperty%copy.body
}

cProperty::cProperty (cConfigurationObject *config_object, CONST_STRING_T name, CONST_STRING_T buffer)
  //## begin cProperty::cProperty%978594326.hasinit preserve=no
      : _Dirty(false), _PropertyDef(NULL), _Configuration(NULL), _TypeDef(NULL), _TypeFactory(NULL), _ConfigurationObject(NULL)
  //## end cProperty::cProperty%978594326.hasinit
  //## begin cProperty::cProperty%978594326.initialization preserve=yes
  //## end cProperty::cProperty%978594326.initialization
{
  //## begin cProperty::cProperty%978594326.body preserve=yes
_ASSERT_COND(config_object != NULL)
   _ConfigurationObject = config_object;
   _Configuration = _ConfigurationObject->Configuration();
   _TypeFactory = _Configuration->TypeFactory();
   _Name = name;
   cTypeDef * object_def = _ConfigurationObject->TypeDef();
   if (object_def != NULL) {
      _PropertyDef = object_def->PropertyDef(name);
      if (_PropertyDef == NULL) {
         _PropertyDef = object_def->PropertyDef("PropertyType");
         if (_PropertyDef == NULL) {
            throw cError(CONFIG_NO_PROPERTYDEF, 0, name, _ConfigurationObject->get_Name().c_str());
         }
      }
      _TypeDef = _PropertyDef->TypeDef();
      if (_TypeDef == NULL) {
         throw cError(CONFIG_NO_TYPEDEF, 0, name, _ConfigurationObject->get_Name().c_str());
      }
      ParseValue(buffer);
   }
  //## end cProperty::cProperty%978594326.body
}


cProperty::~cProperty()
{
  //## begin cProperty::~cProperty%.body preserve=yes
  //## end cProperty::~cProperty%.body
}



//## Other Operations (implementation)
cPropertyDef * cProperty::PropertyDef ()
{
  //## begin cProperty::PropertyDef%1011204315.body preserve=yes
   return _PropertyDef;
  //## end cProperty::PropertyDef%1011204315.body
}

void cProperty::Save ()
{
  //## begin cProperty::Save%1011186741.body preserve=yes
   if (_Dirty) {
      STRING_T file_name = _ConfigurationObject->get_Source().c_str();
      cIniFile ini_file(file_name.c_str());
      if (ini_file.Exists()) {
         STRING_T object_name = _ConfigurationObject->get_Name().c_str();
         STRING_T value = ConstructValue();
         ini_file.WriteValue(object_name.c_str(), _Name.c_str(), value.c_str());
      }
   }
  //## end cProperty::Save%1011186741.body
}

void cProperty::Resolve ()
{
  //## begin cProperty::Resolve%1011095992.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());;
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());;
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type == ObjectDef) {
      if (_ObjectVector.size() > 0) {
         throw cError(CONFIG_PROPERTY_ALREADY_RESOLVED, 0, _Name.c_str());
      } else {
         int size = _StringVector.size();
         for (int i=0; i<size; i++) {
            _ObjectVector.resize(i+1);
            STRING_T object_name = _StringVector[i];
            cConfigurationObject * object = _Configuration->Object(object_name.c_str());
            if (object != NULL) {
               STRING_T property_type = _PropertyDef->get_DefName().c_str();
               STRING_T object_type = object->get_TypeName().c_str();
               if (strcmp(property_type.c_str(), object_type.c_str()) != 0) {
                  throw cError(CONFIG_OBJECT_TYPE_MISMATCH, 0,
                               _Name.c_str(), _ConfigurationObject->get_Name().c_str(),
                               property_type.c_str(), object_type.c_str());
               }
               _ConfigurationObject->set_HasChildren(true);
               object->set_Referenced(true);
               _ObjectVector[i] = object;
            } else {
               throw cError(CONFIG_UNABLE_TO_RESOLVE_OBJECT, 0, object_name.c_str());
            }
         }
      }
   }
  //## end cProperty::Resolve%1011095992.body
}

DOUBLE_T cProperty::Value (DOUBLE_T default_value)
{
  //## begin cProperty::Value%1011114940.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_PropertyDef->get_IsVector()) throw cError(CONFIG_NO_SCALAR, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != Numeric) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                          _ConfigurationObject->get_Name().c_str(),
                                          cConvUtils::StringValue(base_type).c_str());
   if (_NumericVector.size() == 0)  throw cError(CONFIG_NO_VALUE, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   return _NumericVector[0];
  //## end cProperty::Value%1011114940.body
}

LONG_T cProperty::Value (LONG_T default_value)
{
  //## begin cProperty::Value%1011114941.body preserve=yes
   return (long)Value((double)default_value);
  //## end cProperty::Value%1011114941.body
}

ULONG_T cProperty::Value (ULONG_T default_value)
{
  //## begin cProperty::Value%1011276243.body preserve=yes
   return (unsigned long)Value((double)default_value);
  //## end cProperty::Value%1011276243.body
}

BOOL_T cProperty::Value (BOOL_T default_value)
{
  //## begin cProperty::Value%1011114942.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_PropertyDef->get_IsVector()) throw cError(CONFIG_NO_SCALAR, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != String) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                         _ConfigurationObject->get_Name().c_str(),
                                         cConvUtils::StringValue(base_type).c_str());
   if (_StringVector.size() == 0)  throw cError(CONFIG_NO_VALUE, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   STRING_T sval = _StringVector[0];
   return BoolValue(sval.c_str());
  //## end cProperty::Value%1011114942.body
}

STRING_T cProperty::Value (CONST_STRING_T default_value)
{
  //## begin cProperty::Value%1011114943.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_PropertyDef->get_IsVector()) throw cError(CONFIG_NO_SCALAR, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != String) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                         _ConfigurationObject->get_Name().c_str(),
                                         cConvUtils::StringValue(base_type).c_str());
   if (_StringVector.size() == 0)  throw cError(CONFIG_NO_VALUE, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   return _StringVector[0].c_str();
  //## end cProperty::Value%1011114943.body
}

cConfigurationObject * cProperty::Value (cConfigurationObject *default_value)
{
  //## begin cProperty::Value%1011114944.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_PropertyDef->get_IsVector()) throw cError(CONFIG_NO_SCALAR, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != ObjectDef) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                            _ConfigurationObject->get_Name().c_str(),
                                            cConvUtils::StringValue(base_type).c_str());
   if (_ObjectVector.size() == 0)  throw cError(CONFIG_NO_VALUE, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   return _ObjectVector[0];
  //## end cProperty::Value%1011114944.body
}

INT_T cProperty::Value (STRING_VECTOR_T &vec)
{
  //## begin cProperty::Value%1011114945.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (!_PropertyDef->get_IsVector()) throw cError(CONFIG_NO_VECTOR, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != String) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                         _ConfigurationObject->get_Name().c_str(),
                                         cConvUtils::StringValue(base_type).c_str());
   int size = _StringVector.size();
   if (size > 0) {
      vec.resize(size);
      for (int i=0; i<size; i++) {
         vec[i] = _StringVector[i];
      }
   }
   return size;
  //## end cProperty::Value%1011114945.body
}

INT_T cProperty::Value (NUMERIC_VECTOR_T &vec)
{
  //## begin cProperty::Value%1011114946.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (!_PropertyDef->get_IsVector()) throw cError(CONFIG_NO_VECTOR, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != Numeric) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                          _ConfigurationObject->get_Name().c_str(),
                                          cConvUtils::StringValue(base_type).c_str());
   int size = _NumericVector.size();
   if (size > 0) {
      vec.resize(size);
      for (int i=0; i<size; i++) {
         vec[i] = _NumericVector[i];
      }
   }
   return size;
  //## end cProperty::Value%1011114946.body
}

INT_T cProperty::Value (CONFOBJ_VECTOR_T &vec)
{
  //## begin cProperty::Value%1011114947.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (!_PropertyDef->get_IsVector()) throw cError(CONFIG_NO_VECTOR, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != ObjectDef) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                            _ConfigurationObject->get_Name().c_str(),
                                            cConvUtils::StringValue(base_type).c_str());
   int size = _ObjectVector.size();
   if (size > 0) {
      vec.resize(size);
      for (int i=0; i<size; i++) {
         vec[i] = _ObjectVector[i];
      }
   }
   return size;
  //## end cProperty::Value%1011114947.body
}

void cProperty::SetValue (CONST_STRING_T value, ULONG_T index)
{
  //## begin cProperty::SetValue%1011186739.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (!_TypeDef->IsValid(value)) throw cError(CONFIG_INVALID_VALUE, 0, value, _Name.c_str(),
                                               _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != String) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                         _ConfigurationObject->get_Name().c_str(),
                                         cConvUtils::StringValue(base_type).c_str());
   unsigned long size = _StringVector.size();
   if (index == size) {
      _StringVector.resize(index+1);
   } else if (index > size) {
      throw cError(CONFIG_INVALID_INDEX, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   }
   _StringVector[index] = value;
   _Dirty = true;
  //## end cProperty::SetValue%1011186739.body
}

void cProperty::SetValue (DOUBLE_T value, ULONG_T index)
{
  //## begin cProperty::SetValue%1011186748.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   STRING_T sval = cConvUtils::StringValue(value);
   if (!_TypeDef->IsValid(sval.c_str())) throw cError(CONFIG_INVALID_VALUE, 0, sval.c_str(), _Name.c_str(),
                                               _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != Numeric) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                          _ConfigurationObject->get_Name().c_str(),
                                          cConvUtils::StringValue(base_type).c_str());
   unsigned long size = _NumericVector.size();
   if (index == size) {
      _NumericVector.resize(index+1);
   } else if (index > size) {
      throw cError(CONFIG_INVALID_INDEX, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   }
   _NumericVector[index] = value;
   _Dirty = true;
  //## end cProperty::SetValue%1011186748.body
}

void cProperty::SetValue (LONG_T value, ULONG_T index)
{
  //## begin cProperty::SetValue%1011186751.body preserve=yes
   SetValue((double)value, index);
  //## end cProperty::SetValue%1011186751.body
}

void cProperty::SetValue (ULONG_T value, ULONG_T index)
{
  //## begin cProperty::SetValue%1011276244.body preserve=yes
   SetValue((double)value, index);
  //## end cProperty::SetValue%1011276244.body
}

void cProperty::SetValue (cConfigurationObject *value, ULONG_T index)
{
  //## begin cProperty::SetValue%1011186749.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type != ObjectDef) throw cError(CONFIG_INVALID_TYPE, 0, _Name.c_str(),
                                            _ConfigurationObject->get_Name().c_str(),
                                            cConvUtils::StringValue(base_type).c_str());
   unsigned long size = _ObjectVector.size();
   if (index == size) {
      _ObjectVector.resize(index+1);
   } else if (index > size) {
      throw cError(CONFIG_INVALID_INDEX, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   }
   _ObjectVector[index] = value;
   _Dirty = true;
  //## end cProperty::SetValue%1011186749.body
}

void cProperty::SetValue (BOOL_T value, ULONG_T index)
{
  //## begin cProperty::SetValue%1011186750.body preserve=yes
   if (value) {
      SetValue("true", index);
   } else {
      SetValue("false", index);
   }
  //## end cProperty::SetValue%1011186750.body
}

STRING_T cProperty::ConstructValue ()
{
  //## begin cProperty::ConstructValue%1011186743.body preserve=yes
   if (_PropertyDef == NULL) throw cError(CONFIG_NO_PROPERTYDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());;
   if (_TypeDef == NULL) throw cError(CONFIG_NO_TYPEDEF, 0, _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (base_type == String) {
      return StringList(_StringVector);
   } else if (base_type == Numeric) {
      return StringList(_NumericVector);
   } else if (base_type == ObjectDef) {
      return StringList(_ObjectVector);
   } else {
      throw cError(CONFIG_INVALID_BASETYPE, 0, cConvUtils::StringValue(base_type).c_str(),
                   _Name.c_str(), _ConfigurationObject->get_Name().c_str());
   }
  //## end cProperty::ConstructValue%1011186743.body
}

void cProperty::ParseValue (CONST_STRING_T buffer)
{
  //## begin cProperty::ParseValue%1011095978.body preserve=yes
   if (_PropertyDef == NULL) return;
   if (_TypeDef == NULL) return;
   BaseTypes base_type = _TypeDef->get_BaseType();
   if (_PropertyDef->get_IsVector()) {
      if (base_type == String) {
         ParseVector(buffer, _StringVector);
      } else if (base_type == Numeric) {
         ParseVector(buffer, _NumericVector);
      } else if (base_type == ObjectDef) {
         ParseVector(buffer, _StringVector);
      } else {
         throw cError(CONFIG_INVALID_BASETYPE, 0, cConvUtils::StringValue(base_type).c_str(),
                      _Name.c_str(), _ConfigurationObject->get_Name().c_str());
      }
   } else {
      if (base_type == String) {
         _StringVector.resize(1);
         ParseString(buffer, _StringVector[0]);
      } else if (base_type == Numeric) {
         _NumericVector.resize(1);
         ParseNumeric(buffer, _NumericVector[0]);
      } else if (base_type == ObjectDef) {
         _StringVector.resize(1);
         ParseString(buffer, _StringVector[0]);
      } else {
         throw cError(CONFIG_INVALID_BASETYPE, 0, cConvUtils::StringValue(base_type).c_str(),
                      _Name.c_str(), _ConfigurationObject->get_Name().c_str());
      }
   }
  //## end cProperty::ParseValue%1011095978.body
}

void cProperty::ParseString (CONST_STRING_T buffer, STRING_T &value)
{
  //## begin cProperty::ParseString%1011361700.body preserve=yes
   if (!_TypeDef->IsValid(buffer)) {
      throw cError(CONFIG_INVALID_VALUE, 0, buffer, _Name.c_str(),
                   _ConfigurationObject->get_Name().c_str());
   }
   value = buffer;
  //## end cProperty::ParseString%1011361700.body
}

void cProperty::ParseNumeric (CONST_STRING_T buffer, DOUBLE_T &value)
{
  //## begin cProperty::ParseNumeric%1011361701.body preserve=yes
   if (!_TypeDef->IsValid(buffer)) {
      throw cError(CONFIG_INVALID_VALUE, 0, buffer, _Name.c_str(),
                   _ConfigurationObject->get_Name().c_str());
   }
   if (IsNumeric(buffer)) {
      value = atof(buffer);
   } else {
      throw cError(CONFIG_NOT_NUMERIC, 0, _Name.c_str(),
                   _ConfigurationObject->get_Name().c_str(), buffer);
   }
  //## end cProperty::ParseNumeric%1011361701.body
}

BOOL_T cProperty::ParseVector (CONST_STRING_T buffer, STRING_VECTOR_T &vec)
{
  //## begin cProperty::ParseVector%1011095989.body preserve=yes
   int i = 0;
   const char * token = NULL;
   cTokenizer tokenizer(buffer, strlen(buffer));
   while ((token = tokenizer.GetToken(",")) != NULL) {
      STRING_T sval = cStringUtils::Trim(token);
      sval = cStringUtils::Trim(sval.c_str(), '\t');
      token = sval.c_str();
      if (!_TypeDef->IsValid(token)) {
         throw cError(CONFIG_INVALID_VALUE, 0, token, _Name.c_str(),
                      _ConfigurationObject->get_Name().c_str());
      }
      vec.resize(i+1);
      vec[i] = token;
      i++;
   }
   return true;
  //## end cProperty::ParseVector%1011095989.body
}

BOOL_T cProperty::ParseVector (CONST_STRING_T buffer, NUMERIC_VECTOR_T &vec)
{
  //## begin cProperty::ParseVector%1011095990.body preserve=yes
   int i = 0;
   const char * token = NULL;
   cTokenizer tokenizer(buffer, strlen(buffer));
   while ((token = tokenizer.GetToken(",")) != NULL) {
      STRING_T sval = cStringUtils::Trim(token);
      sval = cStringUtils::Trim(sval.c_str(), '\t');
      token = sval.c_str();
      if (!_TypeDef->IsValid(token)) {
         throw cError(CONFIG_INVALID_VALUE, 0, token, _Name.c_str(),
                      _ConfigurationObject->get_Name().c_str());
      }
      double fval = 0;
      if (IsNumeric(token)) {
         fval = atof(token);
      } else {
         throw cError(CONFIG_NOT_NUMERIC, 0, _Name.c_str(),
                      _ConfigurationObject->get_Name().c_str(), buffer);
      }
      vec.resize(i+1);
      vec[i] = fval;
      i++;
   }
   return true;
  //## end cProperty::ParseVector%1011095990.body
}

BOOL_T cProperty::BoolValue (CONST_STRING_T value)
{
  //## begin cProperty::BoolValue%1011114951.body preserve=yes
   if (strnicmp(value, "true", 4) == 0) return true;
   if (strnicmp(value, "yes", 3) == 0) return true;
   if (strnicmp(value, "false", 5) == 0) return false;
   if (strnicmp(value, "no", 2) == 0) return false;
   throw cError(CONFIG_INVALID_BOOL_SPEC, 0, _Name.c_str(),
                _ConfigurationObject->get_Name().c_str(), value);
#ifdef __MSCPP__
   return false;
#endif
  //## end cProperty::BoolValue%1011114951.body
}

STRING_T cProperty::StringList (STRING_VECTOR_T &vec)
{
  //## begin cProperty::StringList%1011186744.body preserve=yes
   STRING_T string_list;
   int size = vec.size();
   for (int i=0; i<size; i++) {
      if (i != 0) string_list += ",";
      string_list += vec[i].c_str();
   }
   return string_list;
  //## end cProperty::StringList%1011186744.body
}

STRING_T cProperty::StringList (NUMERIC_VECTOR_T &vec)
{
  //## begin cProperty::StringList%1011186745.body preserve=yes
   STRING_T string_list;
   int size = vec.size();
   for (int i=0; i<size; i++) {
      if (i != 0) string_list += ",";
      string_list += cConvUtils::StringValue(vec[i]).c_str();
   }
   return string_list;
  //## end cProperty::StringList%1011186745.body
}

STRING_T cProperty::StringList (CONFOBJ_VECTOR_T &vec)
{
  //## begin cProperty::StringList%1011186746.body preserve=yes
   STRING_T string_list;
   int size = vec.size();
   for (int i=0; i<size; i++) {
      if (i != 0) string_list += ",";
      cConfigurationObject * object = vec[i];
      string_list += object->get_Name().c_str();
   }
   return string_list;
  //## end cProperty::StringList%1011186746.body
}

BOOL_T cProperty::IsNumeric (CONST_STRING_T value)
{
  //## begin cProperty::IsNumeric%1011361702.body preserve=yes
   return cConvUtils::IsNumeric(value);
  //## end cProperty::IsNumeric%1011361702.body
}

BOOL_T cProperty::IsInteger ()
{
  //## begin cProperty::IsInteger%1083004730.body preserve=yes
   BaseTypes base_type = _TypeDef->get_BaseType();
   return (base_type == Numeric);
  //## end cProperty::IsInteger%1083004730.body
}

BOOL_T cProperty::IsReal ()
{
  //## begin cProperty::IsReal%1083004731.body preserve=yes
   BaseTypes base_type = _TypeDef->get_BaseType();
   return (base_type == Numeric);
  //## end cProperty::IsReal%1083004731.body
}

BOOL_T cProperty::IsString ()
{
  //## begin cProperty::IsString%1083004732.body preserve=yes
   BaseTypes base_type = _TypeDef->get_BaseType();
   return (base_type == String);
  //## end cProperty::IsString%1083004732.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cProperty::get_Name () const
{
  //## begin cProperty::get_Name%3A542B0902E0.get preserve=no
  return _Name;
  //## end cProperty::get_Name%3A542B0902E0.get
}

// Additional Declarations
  //## begin cProperty%3A542AD30289.declarations preserve=yes
  //## end cProperty%3A542AD30289.declarations

//## begin module%3A542AD30289.epilog preserve=yes
//## end module%3A542AD30289.epilog
