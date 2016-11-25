//## begin module%41469323034B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41469323034B.cm

//## begin module%41469323034B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41469323034B.cp

//## Module: cShortCurve%41469323034B; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cShortCurve.cpp

//## begin module%41469323034B.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%41469323034B.additionalIncludes

//## begin module%41469323034B.includes preserve=yes
//## end module%41469323034B.includes

// cShortCurve
#include "System/Structs/cShortCurve.h"
//## begin module%41469323034B.additionalDeclarations preserve=yes
//## end module%41469323034B.additionalDeclarations


// Class cShortCurve 



cShortCurve::cShortCurve()
  //## begin cShortCurve::cShortCurve%.hasinit preserve=no
  //## end cShortCurve::cShortCurve%.hasinit
  //## begin cShortCurve::cShortCurve%.initialization preserve=yes
  //## end cShortCurve::cShortCurve%.initialization
{
  //## begin cShortCurve::cShortCurve%.body preserve=yes
_ASSERT_UNCOND
  //## end cShortCurve::cShortCurve%.body
}

cShortCurve::cShortCurve(const cShortCurve &right)
  //## begin cShortCurve::cShortCurve%copy.hasinit preserve=no
  //## end cShortCurve::cShortCurve%copy.hasinit
  //## begin cShortCurve::cShortCurve%copy.initialization preserve=yes
  //## end cShortCurve::cShortCurve%copy.initialization
{
  //## begin cShortCurve::cShortCurve%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cShortCurve::cShortCurve%copy.body
}

cShortCurve::cShortCurve (PTR_T data, ULONG_T data_size, ULONG_T value_count)
  //## begin cShortCurve::cShortCurve%1095144427.hasinit preserve=no
  //## end cShortCurve::cShortCurve%1095144427.hasinit
  //## begin cShortCurve::cShortCurve%1095144427.initialization preserve=yes
  : cGraphicCurve(data, data_size, value_count, 2)
  //## end cShortCurve::cShortCurve%1095144427.initialization
{
  //## begin cShortCurve::cShortCurve%1095144427.body preserve=yes
   SHORT_T * object_data = (SHORT_T*)((FLAT_OBJECT_HEADER_T*)_Header)->object_data;
   _XValues = &(object_data[0]);
   _YValues = &(object_data[GetValueCount()]);
  //## end cShortCurve::cShortCurve%1095144427.body
}

cShortCurve::cShortCurve (PTR_T data)
  //## begin cShortCurve::cShortCurve%1095144428.hasinit preserve=no
  //## end cShortCurve::cShortCurve%1095144428.hasinit
  //## begin cShortCurve::cShortCurve%1095144428.initialization preserve=yes
  : cGraphicCurve(data)
  //## end cShortCurve::cShortCurve%1095144428.initialization
{
  //## begin cShortCurve::cShortCurve%1095144428.body preserve=yes
   SHORT_T * object_data = (SHORT_T*)((FLAT_OBJECT_HEADER_T*)_Header)->object_data;
   _XValues = &(object_data[0]);
   _YValues = &(object_data[GetValueCount()]);
  //## end cShortCurve::cShortCurve%1095144428.body
}


cShortCurve::~cShortCurve()
{
  //## begin cShortCurve::~cShortCurve%.body preserve=yes
  //## end cShortCurve::~cShortCurve%.body
}



//## Other Operations (implementation)
void cShortCurve::SetXVal (SHORT_T value, ULONG_T index)
{
  //## begin cShortCurve::SetXVal%1095144433.body preserve=yes
   if (index >= GetValueCount()) {
      return;
   }
   _XValues[index] = value;
  //## end cShortCurve::SetXVal%1095144433.body
}

void cShortCurve::SetYVal (SHORT_T value, ULONG_T index)
{
  //## begin cShortCurve::SetYVal%1095144434.body preserve=yes
   if (index >= GetValueCount()) {
      return;
   }
   _YValues[index] = value;
  //## end cShortCurve::SetYVal%1095144434.body
}

void cShortCurve::GetXVal (SHORT_T &value, ULONG_T index)
{
  //## begin cShortCurve::GetXVal%1095144435.body preserve=yes
   if (index < GetValueCount()) {
      value = _XValues[index];
   }
  //## end cShortCurve::GetXVal%1095144435.body
}

void cShortCurve::GetYVal (SHORT_T &value, ULONG_T index)
{
  //## begin cShortCurve::GetYVal%1095144436.body preserve=yes
   if (index < GetValueCount()) {
      value = _YValues[index];
   }
  //## end cShortCurve::GetYVal%1095144436.body
}

// Additional Declarations
  //## begin cShortCurve%41469323034B.declarations preserve=yes
  //## end cShortCurve%41469323034B.declarations

//## begin module%41469323034B.epilog preserve=yes
//## end module%41469323034B.epilog
