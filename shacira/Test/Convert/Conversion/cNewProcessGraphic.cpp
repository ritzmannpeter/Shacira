
#include "FirstHeader.h"
#include "cNewProcessGraphic.h"
#include "cFMFatFile.h"

cSetCurve::cSetCurve(SOLL_CURVE_HEADER * curve_header, void * curve_buffer)
{
   _Version = curve_header->Version;
   _CurveId = curve_header->CurveId;
   _GroupId = curve_header->GroupId;
   _FunctionUnit = curve_header->FunctionUnit;
   _ValueType = curve_header->ValueType;
   _DimensionId = curve_header->DimensionId;
   _CompressionType = curve_header->CompressionType;
   _CurveBufferSize = curve_header->CurveBufferSize;
   _Tolerance = curve_header->Tolerance;
   _YScale = curve_header->YScale;
   _YMax = curve_header->YMax;
   _CurveBuffer = cSystemUtils::Alloc(_CurveBufferSize);
   memcpy(_CurveBuffer, curve_buffer, _CurveBufferSize);
}

cSetCurve::~cSetCurve()
{
   cSystemUtils::Free(_CurveBuffer);
}

cNewProcessGraphic::cNewProcessGraphic(cFMFatFile * file, cSubfile * sub_file)
{
   _File = file;
   _Subfile = sub_file;
}

cNewProcessGraphic::~cNewProcessGraphic()
{
}

void cNewProcessGraphic::AddCurve(SOLL_CURVE_HEADER * curve_header, void * curve_buffer)
{
   if (curve_header->Magic == SOLL_CURVE_MAGIC) {
      cSetCurve * curve = new cSetCurve(curve_header, curve_buffer);
      _Curves.push_back(curve);
   }
}

void cNewProcessGraphic::SetCurves(SET_CURVE_LIST_T & curves)
{
   curves = _Curves;
}

void cNewProcessGraphic::Print(STRING_T & doc)
{
}


