//## begin module%3C42C87A0274.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C42C87A0274.cm

//## begin module%3C42C87A0274.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C42C87A0274.cp

//## Module: cTypeDef%3C42C87A0274; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cTypeDef.cpp

//## begin module%3C42C87A0274.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C42C87A0274.additionalIncludes

//## begin module%3C42C87A0274.includes preserve=yes
//## end module%3C42C87A0274.includes

// cTypeFactory
#include "System/Config/cTypeFactory.h"
// cPropertyDef
#include "System/Config/cPropertyDef.h"
// cTypeDef
#include "System/Config/cTypeDef.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
//## begin module%3C42C87A0274.additionalDeclarations preserve=yes

static const char * BaseTypeText(BaseTypes type)
{
   switch (type) {
      case UndefinedBaseType: return "UndefinedBaseType";
      case Numeric: return "Numeric";
      case String: return "String";
      case TypeDef: return "TypeDef";
      case ObjectDef: return "ObjectDef";
      default: return "UnknownBaseType";
   }
}

static const char * RangeTypeText(RangeTypes type)
{
   switch (type) {
      case UndefinedRangeType: return "UndefinedRangeType";
      case Unlimited: return "Unlimited";
      case Limited: return "Limited";
      case Enumeration: return "Enumeration";
      default: return "UnknownRangeType";
   }
}

//## end module%3C42C87A0274.additionalDeclarations


// Class cTypeDef 

















cTypeDef::cTypeDef()
  //## begin cTypeDef::cTypeDef%.hasinit preserve=no
      : _BaseType(UndefinedBaseType), _RangeType(UndefinedRangeType), _Min(0), _Max(0), _TypeFactory(NULL), _TypeDef(NULL)
  //## end cTypeDef::cTypeDef%.hasinit
  //## begin cTypeDef::cTypeDef%.initialization preserve=yes
  //## end cTypeDef::cTypeDef%.initialization
{
  //## begin cTypeDef::cTypeDef%.body preserve=yes
  //## end cTypeDef::cTypeDef%.body
}

cTypeDef::cTypeDef(const cTypeDef &right)
  //## begin cTypeDef::cTypeDef%copy.hasinit preserve=no
      : _BaseType(UndefinedBaseType), _RangeType(UndefinedRangeType), _Min(0), _Max(0), _TypeFactory(NULL), _TypeDef(NULL)
  //## end cTypeDef::cTypeDef%copy.hasinit
  //## begin cTypeDef::cTypeDef%copy.initialization preserve=yes
  //## end cTypeDef::cTypeDef%copy.initialization
{
  //## begin cTypeDef::cTypeDef%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cTypeDef::cTypeDef%copy.body
}

cTypeDef::cTypeDef (CONST_STRING_T name, cTypeFactory *factory)
  //## begin cTypeDef::cTypeDef%1011013293.hasinit preserve=no
      : _BaseType(UndefinedBaseType), _RangeType(UndefinedRangeType), _Min(0), _Max(0), _TypeFactory(NULL), _TypeDef(NULL)
  //## end cTypeDef::cTypeDef%1011013293.hasinit
  //## begin cTypeDef::cTypeDef%1011013293.initialization preserve=yes
  //## end cTypeDef::cTypeDef%1011013293.initialization
{
  //## begin cTypeDef::cTypeDef%1011013293.body preserve=yes
_ASSERT_COND(factory != NULL)
   _Name = name;
   _TypeFactory = factory;
  //## end cTypeDef::cTypeDef%1011013293.body
}


cTypeDef::~cTypeDef()
{
  //## begin cTypeDef::~cTypeDef%.body preserve=yes
   std::map<STRING_T, cPropertyDef*>::const_iterator i = _PropertyDefs.begin();
   while (i != _PropertyDefs.end()) {
      cPropertyDef * property_def = (*i).second;
      if (property_def != NULL) {
         delete property_def;
      }
      i++;
   }
   _PropertyDefs.clear();
  //## end cTypeDef::~cTypeDef%.body
}



//## Other Operations (implementation)
void cTypeDef::SetBaseType (BaseTypes base_type)
{
  //## begin cTypeDef::SetBaseType%1011018902.body preserve=yes
   _BaseType = base_type;
  //## end cTypeDef::SetBaseType%1011018902.body
}

void cTypeDef::SetRangeType (RangeTypes range_type)
{
  //## begin cTypeDef::SetRangeType%1011021296.body preserve=yes
   _RangeType = range_type;
  //## end cTypeDef::SetRangeType%1011021296.body
}

void cTypeDef::SetDefName (CONST_STRING_T typedef_name)
{
  //## begin cTypeDef::SetDefName%1011021281.body preserve=yes
   _DefName = typedef_name;
  //## end cTypeDef::SetDefName%1011021281.body
}

void cTypeDef::SetRange (CONST_STRING_T spec)
{
  //## begin cTypeDef::SetRange%1011021287.body preserve=yes
   if (strlen(spec) == 0) return;
   if (_RangeType == UndefinedRangeType) {
      switch (_BaseType) {
      case String:
         SetStringRange(spec);
         break;
      case Numeric:
         SetNumericRange(spec);
         break;
      case TypeDef:
      case ObjectDef:
      case UndefinedBaseType:
         throw cError(CONFIG_CANNOT_SET_RANGE, 0, _Name.c_str());
      }
   } else {
      throw cError(CONFIG_AMBIGUOUS_RANGETYPE, 0,
                   _Name.c_str(), cConvUtils::StringValue(_RangeType).c_str());
   }
  //## end cTypeDef::SetRange%1011021287.body
}

void cTypeDef::SetPropertyDef (CONST_STRING_T property_name, CONST_STRING_T property_spec)
{
  //## begin cTypeDef::SetPropertyDef%1011021291.body preserve=yes
   cPropertyDef * property_def = new cPropertyDef(property_name, property_spec, _TypeFactory);
   if (PropertyDef(property_name) == NULL) {
      _PropertyDefs[property_name] = property_def;
   } else {
      throw cError(CONFIG_AMBIGUOUS_PROPERTY, 0, property_name);
   }
  //## end cTypeDef::SetPropertyDef%1011021291.body
}

BOOL_T cTypeDef::IsValid (CONST_STRING_T value)
{
  //## begin cTypeDef::IsValid%1011021283.body preserve=yes
   double fval = 0;
   if (_BaseType == Numeric) {
      fval = atof(value);
      if (_RangeType == Limited) {
         if (fval < _Min || fval > _Max) {
            return false;
         } else {
            return true;
         }
      } else if (_RangeType == Enumeration) {
         DOUBLE_LIST_T::const_iterator e = _NumericEnumeration.begin();
         while (e != _NumericEnumeration.end()) {
            double compval = (*e);
            if (fval == compval) return true;
            e++;
         }
         return false;
      }
   } else if (_BaseType == String) {
      if (_RangeType == Enumeration) {
         STRING_LIST_T::const_iterator e = _StringEnumeration.begin();
         while (e != _StringEnumeration.end()) {
            STRING_T compval = (*e);
            if (strcmp(value, compval.c_str()) == 0) return true;
            e++;
         }
         return false;
      }
   }
   return true;
  //## end cTypeDef::IsValid%1011021283.body
}

void cTypeDef::Resolve ()
{
  //## begin cTypeDef::Resolve%1011021284.body preserve=yes
   switch (_BaseType) {
   case TypeDef:
      {
         cTypeDef * type_def = _TypeFactory->Definition(_DefName.c_str());
         if (type_def == NULL) {
            throw cError(CONFIG_UNKNOWN_TYPEDEF, 0, _Name.c_str());
         } else {
            type_def->Resolve();
            _BaseType = type_def->get_BaseType();
            _RangeType = type_def->get_RangeType();
            _Min = type_def->get_Min();
            _Max = type_def->get_Max();
            _StringEnumeration = type_def->get_StringEnumeration();
            _NumericEnumeration = type_def->get_NumericEnumeration();
         }
      }
      break;
   case ObjectDef:
      {
         std::map<STRING_T, cPropertyDef*>::const_iterator def = _PropertyDefs.begin();
         while (def != _PropertyDefs.end()) {
            cPropertyDef * property_def = (*def).second;
            property_def->Resolve();
            def++;
         }
      }
      break;
   case String:
   case Numeric:
      break;
   case UndefinedBaseType:
      throw cError(CONFIG_UNDEFINED_BASETYPE, 0, _Name.c_str());
   }
  //## end cTypeDef::Resolve%1011021284.body
}

cPropertyDef * cTypeDef::PropertyDef (CONST_STRING_T name)
{
  //## begin cTypeDef::PropertyDef%1011021292.body preserve=yes
   std::map<STRING_T, cPropertyDef*>::const_iterator def = _PropertyDefs.find(name);
   if (def == _PropertyDefs.end()) {
      return NULL;
   } else {
      return (*def).second;
   }
  //## end cTypeDef::PropertyDef%1011021292.body
}

void cTypeDef::SetRange (DOUBLE_T min, DOUBLE_T max)
{
  //## begin cTypeDef::SetRange%1011018900.body preserve=yes
   _RangeType = Limited;
   _Min = min;
   _Max = max;
  //## end cTypeDef::SetRange%1011018900.body
}

void cTypeDef::SetRange (DOUBLE_LIST_T &enumeration)
{
  //## begin cTypeDef::SetRange%1011018899.body preserve=yes
   _RangeType = Enumeration;
   DOUBLE_LIST_T::const_iterator i = enumeration.begin();
   while (i != enumeration.end()) {
      _NumericEnumeration.push_back((*i));
      i++;
   }
  //## end cTypeDef::SetRange%1011018899.body
}

void cTypeDef::SetRange (STRING_LIST_T &enumeration)
{
  //## begin cTypeDef::SetRange%1011018901.body preserve=yes
   _RangeType = Enumeration;
   STRING_LIST_T::const_iterator i = enumeration.begin();
   while (i != enumeration.end()) {
      _StringEnumeration.push_back((*i));
      i++;
   }
  //## end cTypeDef::SetRange%1011018901.body
}

void cTypeDef::SetStringRange (CONST_STRING_T spec)
{
  //## begin cTypeDef::SetStringRange%1011021288.body preserve=yes
   STRING_LIST_T value_list;
   cTypeFactory::ParseList(spec, value_list);
   SetRange(value_list);
  //## end cTypeDef::SetStringRange%1011021288.body
}

void cTypeDef::SetNumericRange (CONST_STRING_T spec)
{
  //## begin cTypeDef::SetNumericRange%1011021289.body preserve=yes
   double min = 0, max = 0;
   if (cTypeFactory::ParseRange(spec, min, max)) {
      SetRange(min, max);
   } else {
      DOUBLE_LIST_T value_list;
      cTypeFactory::ParseList(spec, value_list);
      SetRange(value_list);
   }
  //## end cTypeDef::SetNumericRange%1011021289.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cTypeDef::get_Name () const
{
  //## begin cTypeDef::get_Name%3C42CA3702EC.get preserve=no
  return _Name;
  //## end cTypeDef::get_Name%3C42CA3702EC.get
}

void cTypeDef::set_Name (STRING_T value)
{
  //## begin cTypeDef::set_Name%3C42CA3702EC.set preserve=no
  _Name = value;
  //## end cTypeDef::set_Name%3C42CA3702EC.set
}

BaseTypes cTypeDef::get_BaseType () const
{
  //## begin cTypeDef::get_BaseType%3C42C9E9007D.get preserve=no
  return _BaseType;
  //## end cTypeDef::get_BaseType%3C42C9E9007D.get
}

RangeTypes cTypeDef::get_RangeType () const
{
  //## begin cTypeDef::get_RangeType%3C42EC020039.get preserve=no
  return _RangeType;
  //## end cTypeDef::get_RangeType%3C42EC020039.get
}

STRING_LIST_T cTypeDef::get_StringEnumeration () const
{
  //## begin cTypeDef::get_StringEnumeration%3C42E9010141.get preserve=no
  return _StringEnumeration;
  //## end cTypeDef::get_StringEnumeration%3C42E9010141.get
}

DOUBLE_LIST_T cTypeDef::get_NumericEnumeration () const
{
  //## begin cTypeDef::get_NumericEnumeration%3C42EB330095.get preserve=no
  return _NumericEnumeration;
  //## end cTypeDef::get_NumericEnumeration%3C42EB330095.get
}

DOUBLE_T cTypeDef::get_Min () const
{
  //## begin cTypeDef::get_Min%3C42EE0102A0.get preserve=no
  return _Min;
  //## end cTypeDef::get_Min%3C42EE0102A0.get
}

DOUBLE_T cTypeDef::get_Max () const
{
  //## begin cTypeDef::get_Max%3C42EE120164.get preserve=no
  return _Max;
  //## end cTypeDef::get_Max%3C42EE120164.get
}

// Additional Declarations
  //## begin cTypeDef%3C42C87A0274.declarations preserve=yes
  //## end cTypeDef%3C42C87A0274.declarations

//## begin module%3C42C87A0274.epilog preserve=yes
//## end module%3C42C87A0274.epilog
