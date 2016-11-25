//## begin module%4146F94202EE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4146F94202EE.cm

//## begin module%4146F94202EE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4146F94202EE.cp

//## Module: cFloatCurve%4146F94202EE; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cFloatCurve.cpp

//## begin module%4146F94202EE.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4146F94202EE.additionalIncludes

//## begin module%4146F94202EE.includes preserve=yes
//## end module%4146F94202EE.includes

// cFloatCurve
#include "System/Structs/cFloatCurve.h"
//## begin module%4146F94202EE.additionalDeclarations preserve=yes
//## end module%4146F94202EE.additionalDeclarations


// Class cFloatCurve 



cFloatCurve::cFloatCurve()
  //## begin cFloatCurve::cFloatCurve%.hasinit preserve=no
  //## end cFloatCurve::cFloatCurve%.hasinit
  //## begin cFloatCurve::cFloatCurve%.initialization preserve=yes
  //## end cFloatCurve::cFloatCurve%.initialization
{
  //## begin cFloatCurve::cFloatCurve%.body preserve=yes
_ASSERT_UNCOND
  //## end cFloatCurve::cFloatCurve%.body
}

cFloatCurve::cFloatCurve(const cFloatCurve &right)
  //## begin cFloatCurve::cFloatCurve%copy.hasinit preserve=no
  //## end cFloatCurve::cFloatCurve%copy.hasinit
  //## begin cFloatCurve::cFloatCurve%copy.initialization preserve=yes
  //## end cFloatCurve::cFloatCurve%copy.initialization
{
  //## begin cFloatCurve::cFloatCurve%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFloatCurve::cFloatCurve%copy.body
}

cFloatCurve::cFloatCurve (PTR_T data, ULONG_T data_size, ULONG_T value_count)
  //## begin cFloatCurve::cFloatCurve%1095170838.hasinit preserve=no
  //## end cFloatCurve::cFloatCurve%1095170838.hasinit
  //## begin cFloatCurve::cFloatCurve%1095170838.initialization preserve=yes
  : cGraphicCurve(data, data_size, value_count, 4)
  //## end cFloatCurve::cFloatCurve%1095170838.initialization
{
  //## begin cFloatCurve::cFloatCurve%1095170838.body preserve=yes
   ULONG_T curve_size = FLAT_OBJECT_HEADER_SIZE + ((sizeof(FLOAT_T) * MAX_CURVE_VALUES * 2));
   // PR 01.03.05 do not throw exceptions
   //if (data_size < curve_size) {
   //   throw cError(INSUFFICIENT_CURVE_SPACE, 0, 
   //                cConvUtils::StringValue(curve_size).c_str(),
   //                cConvUtils::StringValue(data_size).c_str());
   //}
   if (data_size >= curve_size) {
      FLOAT_T * object_data = (FLOAT_T*)((FLAT_OBJECT_HEADER_T*)_Header)->object_data;
      _XValues = &(object_data[0]);
      _YValues = &(object_data[MAX_CURVE_VALUES]);
   }
  //## end cFloatCurve::cFloatCurve%1095170838.body
}

cFloatCurve::cFloatCurve (PTR_T data)
  //## begin cFloatCurve::cFloatCurve%1095170839.hasinit preserve=no
  //## end cFloatCurve::cFloatCurve%1095170839.hasinit
  //## begin cFloatCurve::cFloatCurve%1095170839.initialization preserve=yes
  : cGraphicCurve(data)
  //## end cFloatCurve::cFloatCurve%1095170839.initialization
{
  //## begin cFloatCurve::cFloatCurve%1095170839.body preserve=yes
   ULONG_T data_size = GetDataSize();
   ULONG_T curve_size = FLAT_OBJECT_HEADER_SIZE + ((sizeof(FLOAT_T) * MAX_CURVE_VALUES * 2));
   // PR 01.03.05 do not throw exceptions
   // if (data_size < curve_size) {
   //   throw cError(INSUFFICIENT_CURVE_SPACE, 0, 
   //                cConvUtils::StringValue(curve_size).c_str(),
   //                cConvUtils::StringValue(data_size).c_str());
   //}
   if (data_size >= curve_size) {
      FLOAT_T * object_data = (FLOAT_T*)((FLAT_OBJECT_HEADER_T*)_Header)->object_data;
      _XValues = &(object_data[0]);
      _YValues = &(object_data[MAX_CURVE_VALUES]);
   }
  //## end cFloatCurve::cFloatCurve%1095170839.body
}


cFloatCurve::~cFloatCurve()
{
  //## begin cFloatCurve::~cFloatCurve%.body preserve=yes
  //## end cFloatCurve::~cFloatCurve%.body
}



//## Other Operations (implementation)
void cFloatCurve::SetXVal (FLOAT_T value, ULONG_T index)
{
  //## begin cFloatCurve::SetXVal%1095170840.body preserve=yes
   if (_ObjectValid) {
      if (index >= GetValueCount()) {
         return;
      }
      _XValues[index] = value;
   } else {
//      ErrorPrintf("float curve is not valid\n");
   }
  //## end cFloatCurve::SetXVal%1095170840.body
}

void cFloatCurve::SetYVal (FLOAT_T value, ULONG_T index)
{
  //## begin cFloatCurve::SetYVal%1095170841.body preserve=yes
   if (_ObjectValid) {
      if (index >= GetValueCount()) {
         return;
      }
      _YValues[index] = value;
   } else {
//      ErrorPrintf("float curve is not valid\n");
   }
  //## end cFloatCurve::SetYVal%1095170841.body
}

void cFloatCurve::GetXVal (FLOAT_T &value, ULONG_T index)
{
  //## begin cFloatCurve::GetXVal%1095170842.body preserve=yes
   if (_ObjectValid) {
      if (index < GetValueCount()) {
         value = _XValues[index];
      }
   } else {
      value = 0;
//      ErrorPrintf("float curve is not valid\n");
   }
  //## end cFloatCurve::GetXVal%1095170842.body
}

void cFloatCurve::GetYVal (FLOAT_T &value, ULONG_T index)
{
  //## begin cFloatCurve::GetYVal%1095170843.body preserve=yes
   if (_ObjectValid) {
      if (index < GetValueCount()) {
         value = _YValues[index];
      }
   } else {
      value = 0;
//      ErrorPrintf("float curve is not valid\n");
   }
  //## end cFloatCurve::GetYVal%1095170843.body
}

// Additional Declarations
  //## begin cFloatCurve%4146F94202EE.declarations preserve=yes
  //## end cFloatCurve%4146F94202EE.declarations

//## begin module%4146F94202EE.epilog preserve=yes
//## end module%4146F94202EE.epilog
