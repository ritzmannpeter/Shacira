//## begin module%440482DD039C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%440482DD039C.cm

//## begin module%440482DD039C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%440482DD039C.cp

//## Module: cInterfaceFilter%440482DD039C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cInterfaceFilter.cpp

//## begin module%440482DD039C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%440482DD039C.additionalIncludes

//## begin module%440482DD039C.includes preserve=yes
//## end module%440482DD039C.includes

// cVarRef
#include "System/Database/cVarRef.h"
// cContext
#include "System/Database/cContext.h"
// cInterfaceFilter
#include "System/Database/cInterfaceFilter.h"
//## begin module%440482DD039C.additionalDeclarations preserve=yes
//## end module%440482DD039C.additionalDeclarations


// Class cInterfaceFilter 


cInterfaceFilter::cInterfaceFilter()
  //## begin cInterfaceFilter::cInterfaceFilter%.hasinit preserve=no
      : _Flags(0)
  //## end cInterfaceFilter::cInterfaceFilter%.hasinit
  //## begin cInterfaceFilter::cInterfaceFilter%.initialization preserve=yes
  //## end cInterfaceFilter::cInterfaceFilter%.initialization
{
  //## begin cInterfaceFilter::cInterfaceFilter%.body preserve=yes
  //## end cInterfaceFilter::cInterfaceFilter%.body
}

cInterfaceFilter::cInterfaceFilter(const cInterfaceFilter &right)
  //## begin cInterfaceFilter::cInterfaceFilter%copy.hasinit preserve=no
      : _Flags(0)
  //## end cInterfaceFilter::cInterfaceFilter%copy.hasinit
  //## begin cInterfaceFilter::cInterfaceFilter%copy.initialization preserve=yes
  //## end cInterfaceFilter::cInterfaceFilter%copy.initialization
{
  //## begin cInterfaceFilter::cInterfaceFilter%copy.body preserve=yes
  //## end cInterfaceFilter::cInterfaceFilter%copy.body
}


cInterfaceFilter::~cInterfaceFilter()
{
  //## begin cInterfaceFilter::~cInterfaceFilter%.body preserve=yes
  //## end cInterfaceFilter::~cInterfaceFilter%.body
}



//## Other Operations (implementation)
void cInterfaceFilter::DefFilter (cContext *context, ULONG_T if_type, cVarDef *var_def)
{
  //## begin cInterfaceFilter::DefFilter%1141208303.body preserve=yes
  //## end cInterfaceFilter::DefFilter%1141208303.body
}

void cInterfaceFilter::RefFilter (STRING_T &var_name, LONG_T &i1, LONG_T &i2, LONG_T &i3, LONG_T &i4)
{
  //## begin cInterfaceFilter::RefFilter%1141208302.body preserve=yes
  //## end cInterfaceFilter::RefFilter%1141208302.body
}

cVarRef * cInterfaceFilter::FilteredVarRef (cContext *context, CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cInterfaceFilter::FilteredVarRef%1141230224.body preserve=yes
   return NULL;
  //## end cInterfaceFilter::FilteredVarRef%1141230224.body
}

STRING_T cInterfaceFilter::ParamId (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cInterfaceFilter::ParamId%1141665072.body preserve=yes
   return "?";
  //## end cInterfaceFilter::ParamId%1141665072.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cInterfaceFilter::get_Flags () const
{
  //## begin cInterfaceFilter::get_Flags%440575020086.get preserve=no
  return _Flags;
  //## end cInterfaceFilter::get_Flags%440575020086.get
}

void cInterfaceFilter::set_Flags (ULONG_T value)
{
  //## begin cInterfaceFilter::set_Flags%440575020086.set preserve=no
  _Flags = value;
  //## end cInterfaceFilter::set_Flags%440575020086.set
}

// Additional Declarations
  //## begin cInterfaceFilter%440482DD039C.declarations preserve=yes
  //## end cInterfaceFilter%440482DD039C.declarations

//## begin module%440482DD039C.epilog preserve=yes
//## end module%440482DD039C.epilog
