//## begin module%3C4305A10207.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4305A10207.cm

//## begin module%3C4305A10207.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4305A10207.cp

//## Module: cPropertyDef%3C4305A10207; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Config\cPropertyDef.cpp

//## begin module%3C4305A10207.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C4305A10207.additionalIncludes

//## begin module%3C4305A10207.includes preserve=yes
//## end module%3C4305A10207.includes

// cTypeFactory
#include "System/Config/cTypeFactory.h"
// cPropertyDef
#include "System/Config/cPropertyDef.h"
// cTypeDef
#include "System/Config/cTypeDef.h"
//## begin module%3C4305A10207.additionalDeclarations preserve=yes
//## end module%3C4305A10207.additionalDeclarations


// Class cPropertyDef 








cPropertyDef::cPropertyDef()
  //## begin cPropertyDef::cPropertyDef%.hasinit preserve=no
      : _IsVector(false), _TypeDef(NULL), _TypeFactory(NULL)
  //## end cPropertyDef::cPropertyDef%.hasinit
  //## begin cPropertyDef::cPropertyDef%.initialization preserve=yes
  //## end cPropertyDef::cPropertyDef%.initialization
{
  //## begin cPropertyDef::cPropertyDef%.body preserve=yes
  //## end cPropertyDef::cPropertyDef%.body
}

cPropertyDef::cPropertyDef(const cPropertyDef &right)
  //## begin cPropertyDef::cPropertyDef%copy.hasinit preserve=no
      : _IsVector(false), _TypeDef(NULL), _TypeFactory(NULL)
  //## end cPropertyDef::cPropertyDef%copy.hasinit
  //## begin cPropertyDef::cPropertyDef%copy.initialization preserve=yes
  //## end cPropertyDef::cPropertyDef%copy.initialization
{
  //## begin cPropertyDef::cPropertyDef%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cPropertyDef::cPropertyDef%copy.body
}

cPropertyDef::cPropertyDef (CONST_STRING_T name, CONST_STRING_T type_spec, cTypeFactory *type_factory)
  //## begin cPropertyDef::cPropertyDef%1011021290.hasinit preserve=no
      : _IsVector(false), _TypeDef(NULL), _TypeFactory(NULL)
  //## end cPropertyDef::cPropertyDef%1011021290.hasinit
  //## begin cPropertyDef::cPropertyDef%1011021290.initialization preserve=yes
  //## end cPropertyDef::cPropertyDef%1011021290.initialization
{
  //## begin cPropertyDef::cPropertyDef%1011021290.body preserve=yes
_ASSERT_COND(type_factory != NULL)
   _Name = name;
   _TypeFactory = type_factory;
   ParseTypeSpec(type_spec);
  //## end cPropertyDef::cPropertyDef%1011021290.body
}


cPropertyDef::~cPropertyDef()
{
  //## begin cPropertyDef::~cPropertyDef%.body preserve=yes
  //## end cPropertyDef::~cPropertyDef%.body
}



//## Other Operations (implementation)
cTypeDef * cPropertyDef::TypeDef ()
{
  //## begin cPropertyDef::TypeDef%1011095987.body preserve=yes
   return _TypeDef;
  //## end cPropertyDef::TypeDef%1011095987.body
}

void cPropertyDef::Resolve ()
{
  //## begin cPropertyDef::Resolve%1011021293.body preserve=yes
   cTypeDef * type_def = _TypeFactory->Definition(_DefName.c_str());
   if (type_def != NULL) {
      _TypeDef = type_def;
   } else {
      throw cError(CONFIG_UNKNOWN_TYPEDEF, 0, _DefName.c_str(), _Name.c_str());
   }
  //## end cPropertyDef::Resolve%1011021293.body
}

cPropertyDef::operator CONST_STRING_T ()
{
  //## begin cPropertyDef::operator CONST_STRING_T%1011021297.body preserve=yes
   _Text = "";
   _Text += _Name.c_str();
   _Text += ": ";
   if (_TypeDef == NULL) {
      _Text += "type not defined";
   } else {
      if (_IsVector) {
         _Text += "Vector<";
         _Text += _TypeDef->get_Name().c_str();
         _Text += ">";
      } else {
         _Text += _TypeDef->get_Name().c_str();
      }
   }
   return _Text.c_str();
  //## end cPropertyDef::operator CONST_STRING_T%1011021297.body
}

void cPropertyDef::ParseTypeSpec (CONST_STRING_T type_spec)
{
  //## begin cPropertyDef::ParseTypeSpec%1011021294.body preserve=yes
   _TypeFactory->ParseType(type_spec, _DefName, _IsVector);
  //## end cPropertyDef::ParseTypeSpec%1011021294.body
}

//## Get and Set Operations for Class Attributes (implementation)

STRING_T cPropertyDef::get_Name () const
{
  //## begin cPropertyDef::get_Name%3C4306600251.get preserve=no
  return _Name;
  //## end cPropertyDef::get_Name%3C4306600251.get
}

BOOL_T cPropertyDef::get_IsVector () const
{
  //## begin cPropertyDef::get_IsVector%3C43085F0397.get preserve=no
  return _IsVector;
  //## end cPropertyDef::get_IsVector%3C43085F0397.get
}

STRING_T cPropertyDef::get_DefName () const
{
  //## begin cPropertyDef::get_DefName%3C430C1D0091.get preserve=no
  return _DefName;
  //## end cPropertyDef::get_DefName%3C430C1D0091.get
}

// Additional Declarations
  //## begin cPropertyDef%3C4305A10207.declarations preserve=yes
  //## end cPropertyDef%3C4305A10207.declarations

//## begin module%3C4305A10207.epilog preserve=yes
//## end module%3C4305A10207.epilog
