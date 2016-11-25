//## begin module%41139FF901B5.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41139FF901B5.cm

//## begin module%41139FF901B5.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41139FF901B5.cp

//## Module: cVariableValues%41139FF901B5; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVariableValues.cpp

//## begin module%41139FF901B5.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41139FF901B5.additionalIncludes

//## begin module%41139FF901B5.includes preserve=yes
//## end module%41139FF901B5.includes

// cVarDef
#include "System/Database/cVarDef.h"
// cVariableValues
#include "System/Database/cVariableValues.h"
//## begin module%41139FF901B5.additionalDeclarations preserve=yes
//## end module%41139FF901B5.additionalDeclarations


// Class cVariableValues 



cVariableValues::cVariableValues()
  //## begin cVariableValues::cVariableValues%.hasinit preserve=no
      : _VarDef(NULL)
  //## end cVariableValues::cVariableValues%.hasinit
  //## begin cVariableValues::cVariableValues%.initialization preserve=yes
  //## end cVariableValues::cVariableValues%.initialization
{
  //## begin cVariableValues::cVariableValues%.body preserve=yes
  //## end cVariableValues::cVariableValues%.body
}

cVariableValues::cVariableValues(const cVariableValues &right)
  //## begin cVariableValues::cVariableValues%copy.hasinit preserve=no
      : _VarDef(NULL)
  //## end cVariableValues::cVariableValues%copy.hasinit
  //## begin cVariableValues::cVariableValues%copy.initialization preserve=yes
  //## end cVariableValues::cVariableValues%copy.initialization
{
  //## begin cVariableValues::cVariableValues%copy.body preserve=yes
  //## end cVariableValues::cVariableValues%copy.body
}

cVariableValues::cVariableValues (cVarDef *var_def, ULONG_T size)
  //## begin cVariableValues::cVariableValues%1091802229.hasinit preserve=no
      : _VarDef(NULL)
  //## end cVariableValues::cVariableValues%1091802229.hasinit
  //## begin cVariableValues::cVariableValues%1091802229.initialization preserve=yes
  //## end cVariableValues::cVariableValues%1091802229.initialization
{
  //## begin cVariableValues::cVariableValues%1091802229.body preserve=yes
   _Values.resize(size);
   _VarDef = var_def;
   var_def->SetValues(this);
  //## end cVariableValues::cVariableValues%1091802229.body
}


cVariableValues::~cVariableValues()
{
  //## begin cVariableValues::~cVariableValues%.body preserve=yes
  //## end cVariableValues::~cVariableValues%.body
}



//## Other Operations (implementation)
void cVariableValues::SetValue (ULONG_T pos, CONST_STRING_T value)
{
  //## begin cVariableValues::SetValue%1091802230.body preserve=yes
   ULONG_T size = _Values.size();
   if (pos >= size) {
      _Values.resize(pos+1);
   }
   _Values[pos] = value;
  //## end cVariableValues::SetValue%1091802230.body
}

STRING_T cVariableValues::GetValue (ULONG_T pos)
{
  //## begin cVariableValues::GetValue%1091802231.body preserve=yes
   ULONG_T size = _Values.size();
   if (pos < size) {
      return _Values[pos];
   } else {
      return "?";
   }
  //## end cVariableValues::GetValue%1091802231.body
}

ULONG_T cVariableValues::Size ()
{
  //## begin cVariableValues::Size%1091802233.body preserve=yes
   return _Values.size();
  //## end cVariableValues::Size%1091802233.body
}

// Additional Declarations
  //## begin cVariableValues%41139FF901B5.declarations preserve=yes
  //## end cVariableValues%41139FF901B5.declarations

//## begin module%41139FF901B5.epilog preserve=yes
//## end module%41139FF901B5.epilog
