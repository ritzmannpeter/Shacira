//## begin module%414092400109.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%414092400109.cm

//## begin module%414092400109.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%414092400109.cp

//## Module: cGraphicCurve%414092400109; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cGraphicCurve.cpp

//## begin module%414092400109.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%414092400109.additionalIncludes

//## begin module%414092400109.includes preserve=yes
//## end module%414092400109.includes

// cGraphicCurve
#include "System/Structs/cGraphicCurve.h"
//## begin module%414092400109.additionalDeclarations preserve=yes
//## end module%414092400109.additionalDeclarations


// Class cGraphicCurve 


cGraphicCurve::cGraphicCurve()
  //## begin cGraphicCurve::cGraphicCurve%.hasinit preserve=no
      : _CurveHeader(NULL)
  //## end cGraphicCurve::cGraphicCurve%.hasinit
  //## begin cGraphicCurve::cGraphicCurve%.initialization preserve=yes
  //## end cGraphicCurve::cGraphicCurve%.initialization
{
  //## begin cGraphicCurve::cGraphicCurve%.body preserve=yes
_ASSERT_UNCOND
  //## end cGraphicCurve::cGraphicCurve%.body
}

cGraphicCurve::cGraphicCurve(const cGraphicCurve &right)
  //## begin cGraphicCurve::cGraphicCurve%copy.hasinit preserve=no
      : _CurveHeader(NULL)
  //## end cGraphicCurve::cGraphicCurve%copy.hasinit
  //## begin cGraphicCurve::cGraphicCurve%copy.initialization preserve=yes
  //## end cGraphicCurve::cGraphicCurve%copy.initialization
{
  //## begin cGraphicCurve::cGraphicCurve%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cGraphicCurve::cGraphicCurve%copy.body
}

cGraphicCurve::cGraphicCurve (PTR_T data, ULONG_T data_size, ULONG_T value_count, ULONG_T value_size)
  //## begin cGraphicCurve::cGraphicCurve%1094751266.hasinit preserve=no
      : _CurveHeader(NULL)
  //## end cGraphicCurve::cGraphicCurve%1094751266.hasinit
  //## begin cGraphicCurve::cGraphicCurve%1094751266.initialization preserve=yes
  , cFlatObject(data, data_size)
  //## end cGraphicCurve::cGraphicCurve%1094751266.initialization
{
  //## begin cGraphicCurve::cGraphicCurve%1094751266.body preserve=yes
   _CurveHeader = (GRAPHIC_CURVE_HEADER_T*)_Header;
   _CurveHeader->header.flat_object_type = FO_GRAPHIC_CURVE;
   _CurveHeader->curve_info.value_count = value_count;
   _CurveHeader->curve_info.value_size = value_size;
   _ObjectValid = _CurveHeader->curve_info.value_size ? true : false;
  //## end cGraphicCurve::cGraphicCurve%1094751266.body
}

cGraphicCurve::cGraphicCurve (PTR_T data)
  //## begin cGraphicCurve::cGraphicCurve%1094751267.hasinit preserve=no
      : _CurveHeader(NULL)
  //## end cGraphicCurve::cGraphicCurve%1094751267.hasinit
  //## begin cGraphicCurve::cGraphicCurve%1094751267.initialization preserve=yes
  , cFlatObject(data)
  //## end cGraphicCurve::cGraphicCurve%1094751267.initialization
{
  //## begin cGraphicCurve::cGraphicCurve%1094751267.body preserve=yes
   _CurveHeader = (GRAPHIC_CURVE_HEADER_T*)_Header;
   _ObjectValid = _CurveHeader->curve_info.value_size ? true : false;
  //## end cGraphicCurve::cGraphicCurve%1094751267.body
}


cGraphicCurve::~cGraphicCurve()
{
  //## begin cGraphicCurve::~cGraphicCurve%.body preserve=yes
  //## end cGraphicCurve::~cGraphicCurve%.body
}



//## Other Operations (implementation)
ULONG_T cGraphicCurve::GetValueCount ()
{
  //## begin cGraphicCurve::GetValueCount%1094795554.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.value_count;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetValueCount%1094795554.body
}

ULONG_T cGraphicCurve::GetValueSize ()
{
  //## begin cGraphicCurve::GetValueSize%1094795555.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.value_size;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetValueSize%1094795555.body
}

DOUBLE_T cGraphicCurve::GetXScaleStart ()
{
  //## begin cGraphicCurve::GetXScaleStart%1094795557.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.xscale_start;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetXScaleStart%1094795557.body
}

DOUBLE_T cGraphicCurve::GetXScaleEnd ()
{
  //## begin cGraphicCurve::GetXScaleEnd%1094795556.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.xscale_end;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetXScaleEnd%1094795556.body
}

void cGraphicCurve::SetXScaleStart (DOUBLE_T value)
{
  //## begin cGraphicCurve::SetXScaleStart%1095952121.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.xscale_start = value;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetXScaleStart%1095952121.body
}

void cGraphicCurve::SetXScaleEnd (DOUBLE_T value)
{
  //## begin cGraphicCurve::SetXScaleEnd%1095952122.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.xscale_end = value;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetXScaleEnd%1095952122.body
}

DOUBLE_T cGraphicCurve::GetYScaleStart ()
{
  //## begin cGraphicCurve::GetYScaleStart%1095952123.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.yscale_start;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetYScaleStart%1095952123.body
}

DOUBLE_T cGraphicCurve::GetYScaleEnd ()
{
  //## begin cGraphicCurve::GetYScaleEnd%1095952124.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.yscale_end;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetYScaleEnd%1095952124.body
}

void cGraphicCurve::SetYScaleStart (DOUBLE_T value)
{
  //## begin cGraphicCurve::SetYScaleStart%1095952125.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.yscale_start = value;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetYScaleStart%1095952125.body
}

void cGraphicCurve::SetYScaleEnd (DOUBLE_T value)
{
  //## begin cGraphicCurve::SetYScaleEnd%1095952126.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.yscale_end = value;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetYScaleEnd%1095952126.body
}

DOUBLE_T cGraphicCurve::GetMinVal ()
{
  //## begin cGraphicCurve::GetMinVal%1094795558.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.min_val;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetMinVal%1094795558.body
}

DOUBLE_T cGraphicCurve::GetMaxVal ()
{
  //## begin cGraphicCurve::GetMaxVal%1094795559.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.max_val;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetMaxVal%1094795559.body
}

USHORT_T cGraphicCurve::GetFunction ()
{
  //## begin cGraphicCurve::GetFunction%1094890789.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.function;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetFunction%1094890789.body
}

USHORT_T cGraphicCurve::GetFunctionUnit ()
{
  //## begin cGraphicCurve::GetFunctionUnit%1094890790.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.function_unit;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetFunctionUnit%1094890790.body
}

USHORT_T cGraphicCurve::GetCurveId ()
{
  //## begin cGraphicCurve::GetCurveId%1094890791.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.curve_id;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetCurveId%1094890791.body
}

void cGraphicCurve::SetFunction (USHORT_T function)
{
  //## begin cGraphicCurve::SetFunction%1094890792.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.function = function;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetFunction%1094890792.body
}

void cGraphicCurve::SetFunctionUnit (USHORT_T function_unit)
{
  //## begin cGraphicCurve::SetFunctionUnit%1094890793.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.function_unit = function_unit;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetFunctionUnit%1094890793.body
}

void cGraphicCurve::SetCurveId (USHORT_T curve_id)
{
  //## begin cGraphicCurve::SetCurveId%1094890794.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.curve_id = curve_id;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetCurveId%1094890794.body
}

void cGraphicCurve::SetXVal (SHORT_T value, ULONG_T index)
{
  //## begin cGraphicCurve::SetXVal%1095144429.body preserve=yes
   if (_ObjectValid) {
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetXVal%1095144429.body
}

void cGraphicCurve::SetYVal (SHORT_T value, ULONG_T index)
{
  //## begin cGraphicCurve::SetYVal%1095144430.body preserve=yes
   if (_ObjectValid) {
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetYVal%1095144430.body
}

void cGraphicCurve::GetXVal (SHORT_T &value, ULONG_T index)
{
  //## begin cGraphicCurve::GetXVal%1095170832.body preserve=yes
   if (_ObjectValid) {
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::GetXVal%1095170832.body
}

void cGraphicCurve::GetYVal (SHORT_T &value, ULONG_T index)
{
  //## begin cGraphicCurve::GetYVal%1095170833.body preserve=yes
   if (_ObjectValid) {
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::GetYVal%1095170833.body
}

void cGraphicCurve::SetXVal (FLOAT_T value, ULONG_T index)
{
  //## begin cGraphicCurve::SetXVal%1095170834.body preserve=yes
   if (_ObjectValid) {
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetXVal%1095170834.body
}

void cGraphicCurve::SetYVal (FLOAT_T value, ULONG_T index)
{
  //## begin cGraphicCurve::SetYVal%1095170835.body preserve=yes
   if (_ObjectValid) {
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetYVal%1095170835.body
}

void cGraphicCurve::GetXVal (FLOAT_T &value, ULONG_T index)
{
  //## begin cGraphicCurve::GetXVal%1095170836.body preserve=yes
   if (_ObjectValid) {
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::GetXVal%1095170836.body
}

void cGraphicCurve::GetYVal (FLOAT_T &value, ULONG_T index)
{
  //## begin cGraphicCurve::GetYVal%1095170837.body preserve=yes
   if (_ObjectValid) {
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::GetYVal%1095170837.body
}

void cGraphicCurve::SetValueCount (ULONG_T value_count)
{
  //## begin cGraphicCurve::SetValueCount%1096448298.body preserve=yes
   if (_ObjectValid) {
      if (value_count < _CurveHeader->curve_info.value_count) {
         _CurveHeader->curve_info.value_count = value_count;
      }
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetValueCount%1096448298.body
}

void cGraphicCurve::SetMinVal (DOUBLE_T value)
{
  //## begin cGraphicCurve::SetMinVal%1102922391.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.min_val = value;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetMinVal%1102922391.body
}

void cGraphicCurve::SetMaxVal (DOUBLE_T value)
{
  //## begin cGraphicCurve::SetMaxVal%1102922392.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.max_val = value;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetMaxVal%1102922392.body
}

void cGraphicCurve::SetXPrecision (USHORT_T value)
{
  //## begin cGraphicCurve::SetXPrecision%1103015088.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.x_precision = value;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetXPrecision%1103015088.body
}

void cGraphicCurve::SetYPrecision (USHORT_T value)
{
  //## begin cGraphicCurve::SetYPrecision%1103015089.body preserve=yes
   if (_ObjectValid) {
      _CurveHeader->curve_info.y_precision = value;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetYPrecision%1103015089.body
}

USHORT_T cGraphicCurve::GetXPrecision ()
{
  //## begin cGraphicCurve::GetXPrecision%1103015090.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.x_precision;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetXPrecision%1103015090.body
}

USHORT_T cGraphicCurve::GetYPrecision ()
{
  //## begin cGraphicCurve::GetYPrecision%1103015091.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.y_precision;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return 0;
   }
  //## end cGraphicCurve::GetYPrecision%1103015091.body
}

void cGraphicCurve::SetXDim (CONST_STRING_T value)
{
  //## begin cGraphicCurve::SetXDim%1103015443.body preserve=yes
   if (_ObjectValid) {
      USHORT_T size = _MIN_(strlen(value),sizeof(_CurveHeader->curve_info.x_dim)-1);
      memcpy(_CurveHeader->curve_info.x_dim, (void*)value, size);
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetXDim%1103015443.body
}

void cGraphicCurve::SetYDim (CONST_STRING_T value)
{
  //## begin cGraphicCurve::SetYDim%1103015444.body preserve=yes
   if (_ObjectValid) {
      USHORT_T size = _MIN_(strlen(value),sizeof(_CurveHeader->curve_info.y_dim)-1);
      memcpy(_CurveHeader->curve_info.y_dim, (void*)value, size);
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
   }
  //## end cGraphicCurve::SetYDim%1103015444.body
}

CONST_STRING_T cGraphicCurve::GetXDim ()
{
  //## begin cGraphicCurve::GetXDim%1103015445.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.x_dim;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return "?";
   }
  //## end cGraphicCurve::GetXDim%1103015445.body
}

CONST_STRING_T cGraphicCurve::GetYDim ()
{
  //## begin cGraphicCurve::GetYDim%1103015446.body preserve=yes
   if (_ObjectValid) {
      return _CurveHeader->curve_info.y_dim;
   } else {
//      ErrorPrintf("graphic curve is not valid\n");
      return "?";
   }
  //## end cGraphicCurve::GetYDim%1103015446.body
}

// Additional Declarations
  //## begin cGraphicCurve%414092400109.declarations preserve=yes
  //## end cGraphicCurve%414092400109.declarations

//## begin module%414092400109.epilog preserve=yes
//## end module%414092400109.epilog
