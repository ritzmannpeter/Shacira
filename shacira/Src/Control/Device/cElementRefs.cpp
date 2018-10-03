//## begin module%3FE1928F0203.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FE1928F0203.cm

//## begin module%3FE1928F0203.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FE1928F0203.cp

//## Module: cElementRefs%3FE1928F0203; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cElementRefs.cpp

//## begin module%3FE1928F0203.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FE1928F0203.additionalIncludes

//## begin module%3FE1928F0203.includes preserve=yes
//## end module%3FE1928F0203.includes

// cPtrList
#include "System/Memory/cPtrList.h"
// cLocalVariable
#include "Control/LocalDatabase/cLocalVariable.h"
// cElementRefs
#include "Control/Device/cElementRefs.h"
//## begin module%3FE1928F0203.additionalDeclarations preserve=yes
//## end module%3FE1928F0203.additionalDeclarations


// Class cElementRefs 




cElementRefs::cElementRefs()
  //## begin cElementRefs::cElementRefs%.hasinit preserve=no
  //## end cElementRefs::cElementRefs%.hasinit
  //## begin cElementRefs::cElementRefs%.initialization preserve=yes
  //## end cElementRefs::cElementRefs%.initialization
{
  //## begin cElementRefs::cElementRefs%.body preserve=yes
  //## end cElementRefs::cElementRefs%.body
}

cElementRefs::cElementRefs(const cElementRefs &right)
  //## begin cElementRefs::cElementRefs%copy.hasinit preserve=no
  //## end cElementRefs::cElementRefs%copy.hasinit
  //## begin cElementRefs::cElementRefs%copy.initialization preserve=yes
  //## end cElementRefs::cElementRefs%copy.initialization
{
  //## begin cElementRefs::cElementRefs%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cElementRefs::cElementRefs%copy.body
}


cElementRefs::~cElementRefs()
{
  //## begin cElementRefs::~cElementRefs%.body preserve=yes
  //## end cElementRefs::~cElementRefs%.body
}



//## Other Operations (implementation)
void cElementRefs::AddRef (ULONG_T address, cLocalVariable *variable, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cElementRefs::AddRef%1071741897.body preserve=yes
   cPtrList * refs = GetRefs(address);
   if (refs == NULL) {
      refs = new cPtrList;
      _AddressMap[address] = refs;
   }
   ELEMENT_REF_T * element_ref = (ELEMENT_REF_T*)cSystemUtils::Alloc(sizeof(*element_ref));
   element_ref->variable = variable;
   element_ref->i1 = i1;
   element_ref->i2 = i2;
   element_ref->i3 = i3;
   element_ref->i4 = i4;
   refs->Add(element_ref);
  //## end cElementRefs::AddRef%1071741897.body
}

void cElementRefs::AddRef (CONST_STRING_T name, cLocalVariable *variable, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cElementRefs::AddRef%1071741898.body preserve=yes
   cPtrList * refs = GetRefs(name);
   if (refs == NULL) {
      refs = new cPtrList;
      _NameMap[name] = refs;
   }
   ELEMENT_REF_T * element_ref = (ELEMENT_REF_T*)cSystemUtils::Alloc(sizeof(*element_ref));
   element_ref->variable = variable;
   element_ref->i1 = i1;
   element_ref->i2 = i2;
   element_ref->i3 = i3;
   element_ref->i4 = i4;
   refs->Add(element_ref);
  //## end cElementRefs::AddRef%1071741898.body
}

cPtrList * cElementRefs::GetRefs (ULONG_T address)
{
  //## begin cElementRefs::GetRefs%1071741899.body preserve=yes
   ADDRESS_MAP_T::const_iterator i = _AddressMap.find(address);
   if (i == _AddressMap.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cElementRefs::GetRefs%1071741899.body
}

cPtrList * cElementRefs::GetRefs (CONST_STRING_T name)
{
  //## begin cElementRefs::GetRefs%1071741900.body preserve=yes
   NAME_MAP_T::const_iterator i = _NameMap.find(name);
   if (i == _NameMap.cend()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cElementRefs::GetRefs%1071741900.body
}

// Additional Declarations
  //## begin cElementRefs%3FE1928F0203.declarations preserve=yes
  //## end cElementRefs%3FE1928F0203.declarations

//## begin module%3FE1928F0203.epilog preserve=yes
//## end module%3FE1928F0203.epilog
