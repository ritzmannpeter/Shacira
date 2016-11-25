//## begin module%3E0042BA0033.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0042BA0033.cm

//## begin module%3E0042BA0033.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0042BA0033.cp

//## Module: cFuncDecl%3E0042BA0033; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFuncDecl.cpp

//## begin module%3E0042BA0033.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E0042BA0033.additionalIncludes

//## begin module%3E0042BA0033.includes preserve=yes
//## end module%3E0042BA0033.includes

// cContext
#include "System/Database/cContext.h"
// cFuncDecl
#include "System/Database/cFuncDecl.h"
//## begin module%3E0042BA0033.additionalDeclarations preserve=yes
//## end module%3E0042BA0033.additionalDeclarations


// Class cFuncDecl 








cFuncDecl::cFuncDecl()
  //## begin cFuncDecl::cFuncDecl%.hasinit preserve=no
      : _FuncClass(UNDEFINED), _DataType(UNDEFINED), _Context(NULL)
  //## end cFuncDecl::cFuncDecl%.hasinit
  //## begin cFuncDecl::cFuncDecl%.initialization preserve=yes
  //## end cFuncDecl::cFuncDecl%.initialization
{
  //## begin cFuncDecl::cFuncDecl%.body preserve=yes
_ASSERT_UNCOND
  //## end cFuncDecl::cFuncDecl%.body
}

cFuncDecl::cFuncDecl(const cFuncDecl &right)
  //## begin cFuncDecl::cFuncDecl%copy.hasinit preserve=no
      : _FuncClass(UNDEFINED), _DataType(UNDEFINED), _Context(NULL)
  //## end cFuncDecl::cFuncDecl%copy.hasinit
  //## begin cFuncDecl::cFuncDecl%copy.initialization preserve=yes
  //## end cFuncDecl::cFuncDecl%copy.initialization
{
  //## begin cFuncDecl::cFuncDecl%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFuncDecl::cFuncDecl%copy.body
}

cFuncDecl::cFuncDecl (CONST_STRING_T func_name, UCHAR_T func_type, UCHAR_T func_class)
  //## begin cFuncDecl::cFuncDecl%1040992356.hasinit preserve=no
      : _FuncClass(UNDEFINED), _DataType(UNDEFINED), _Context(NULL)
  //## end cFuncDecl::cFuncDecl%1040992356.hasinit
  //## begin cFuncDecl::cFuncDecl%1040992356.initialization preserve=yes
  //## end cFuncDecl::cFuncDecl%1040992356.initialization
{
  //## begin cFuncDecl::cFuncDecl%1040992356.body preserve=yes
   _FuncName = func_name;
   _DataType = func_type;
   _FuncClass = func_class;
  //## end cFuncDecl::cFuncDecl%1040992356.body
}


cFuncDecl::~cFuncDecl()
{
  //## begin cFuncDecl::~cFuncDecl%.body preserve=yes
  //## end cFuncDecl::~cFuncDecl%.body
}



//## Other Operations (implementation)
UCHAR_T cFuncDecl::FuncClass ()
{
  //## begin cFuncDecl::FuncClass%1061805343.body preserve=yes
   return _FuncClass;
  //## end cFuncDecl::FuncClass%1061805343.body
}

UCHAR_T cFuncDecl::DataType ()
{
  //## begin cFuncDecl::DataType%1061805341.body preserve=yes
   return _DataType;
  //## end cFuncDecl::DataType%1061805341.body
}

void cFuncDecl::AddParam (INT_T param_type, CONST_STRING_T param_name)
{
  //## begin cFuncDecl::AddParam%1040992357.body preserve=yes
   ULONG_T params = _ParamTypes.size() + 1;
   _ParamTypes.resize(params);
   _ParamTypes[params-1] = param_type;
   _ParamNames.resize(params);
   _ParamNames[params-1] = param_name;
  //## end cFuncDecl::AddParam%1040992357.body
}

ULONG_T cFuncDecl::Params ()
{
  //## begin cFuncDecl::Params%1040658555.body preserve=yes
   return _ParamTypes.size();
  //## end cFuncDecl::Params%1040658555.body
}

INT_T cFuncDecl::ParamType (ULONG_T pos)
{
  //## begin cFuncDecl::ParamType%1040658556.body preserve=yes
   ULONG_T size = _ParamTypes.size();
   if (pos >= size) {
      throw cError(FUNC_INVALID_PARAMPOS, 0, _FuncName.c_str(),
                   cConvUtils::StringValue(pos).c_str(),
                   cConvUtils::StringValue(size).c_str());
   }
   return _ParamTypes[pos];
  //## end cFuncDecl::ParamType%1040658556.body
}

STRING_T cFuncDecl::ParamName (ULONG_T pos)
{
  //## begin cFuncDecl::ParamName%1074795683.body preserve=yes
   ULONG_T size = _ParamTypes.size();
   if (pos >= size) {
      throw cError(FUNC_INVALID_PARAMPOS, 0, _FuncName.c_str(),
                   cConvUtils::StringValue(pos).c_str(),
                   cConvUtils::StringValue(size).c_str());
   }
   return _ParamNames[pos];
  //## end cFuncDecl::ParamName%1074795683.body
}

STRING_T cFuncDecl::ClassName (UCHAR_T class_code)
{
  //## begin cFuncDecl::ClassName%1061805344.body preserve=yes
   switch (class_code) {
   case UNDEFINED: return "undefined";
   case SH_FREE: return "free";
   case SH_EMBED: return "embedded";
   case SH_FILTER: return "filter";
   case SH_CONVERSION: return "conversion";
   case SH_VIEW: return "view";
   case SH_DARK: return "dark";
   case SH_PLAUS: return "plaus";
   case SH_USER: return "user";
   }
   return "unknown";
  //## end cFuncDecl::ClassName%1061805344.body
}

// Additional Declarations
  //## begin cFuncDecl%3E0042BA0033.declarations preserve=yes
  //## end cFuncDecl%3E0042BA0033.declarations

//## begin module%3E0042BA0033.epilog preserve=yes
//## end module%3E0042BA0033.epilog
