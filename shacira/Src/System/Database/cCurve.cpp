//## begin module%4045D069007D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4045D069007D.cm

//## begin module%4045D069007D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4045D069007D.cp

//## Module: cCurve%4045D069007D; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cCurve.cpp

//## begin module%4045D069007D.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4045D069007D.additionalIncludes

//## begin module%4045D069007D.includes preserve=yes
//## end module%4045D069007D.includes

// cCurve
#include "System/Database/cCurve.h"
//## begin module%4045D069007D.additionalDeclarations preserve=yes
//## end module%4045D069007D.additionalDeclarations


// Class cCurve 







cCurve::cCurve()
  //## begin cCurve::cCurve%.hasinit preserve=no
      : _Coords(0), _CurveHeader(NULL), _BufSize(0), _Buffer(NULL), _CurveData(NULL), _BufferAllocated(false)
  //## end cCurve::cCurve%.hasinit
  //## begin cCurve::cCurve%.initialization preserve=yes
  //## end cCurve::cCurve%.initialization
{
  //## begin cCurve::cCurve%.body preserve=yes
_ASSERT_UNCOND
  //## end cCurve::cCurve%.body
}

cCurve::cCurve(const cCurve &right)
  //## begin cCurve::cCurve%copy.hasinit preserve=no
      : _Coords(0), _CurveHeader(NULL), _BufSize(0), _Buffer(NULL), _CurveData(NULL), _BufferAllocated(false)
  //## end cCurve::cCurve%copy.hasinit
  //## begin cCurve::cCurve%copy.initialization preserve=yes
  //## end cCurve::cCurve%copy.initialization
{
  //## begin cCurve::cCurve%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cCurve::cCurve%copy.body
}

cCurve::cCurve (BUF_T buf)
  //## begin cCurve::cCurve%1078318183.hasinit preserve=no
      : _Coords(0), _CurveHeader(NULL), _BufSize(0), _Buffer(NULL), _CurveData(NULL), _BufferAllocated(false)
  //## end cCurve::cCurve%1078318183.hasinit
  //## begin cCurve::cCurve%1078318183.initialization preserve=yes
  //## end cCurve::cCurve%1078318183.initialization
{
  //## begin cCurve::cCurve%1078318183.body preserve=yes
   _Buffer = buf;
   _CurveHeader = (CURVE_HEADER_T*)buf;
   _BufSize = _CurveHeader->buf_size;
   _Coords = _CurveHeader->coords;
   _CurveData = buf + sizeof(*_CurveHeader);
  //## end cCurve::cCurve%1078318183.body
}

cCurve::cCurve (ULONG_T coords)
  //## begin cCurve::cCurve%1078318184.hasinit preserve=no
      : _Coords(0), _CurveHeader(NULL), _BufSize(0), _Buffer(NULL), _CurveData(NULL), _BufferAllocated(false)
  //## end cCurve::cCurve%1078318184.hasinit
  //## begin cCurve::cCurve%1078318184.initialization preserve=yes
  //## end cCurve::cCurve%1078318184.initialization
{
  //## begin cCurve::cCurve%1078318184.body preserve=yes
   _Coords = coords;
   _BufSize = sizeof(CURVE_HEADER_T) + (_Coords * sizeof(COORD_T));
   _Buffer = (BUF_T)cSystemUtils::Alloc(_BufSize);
   _BufferAllocated = true;
   _CurveHeader = (CURVE_HEADER_T*)_Buffer;
   _CurveHeader->coords = _Coords;
   _CurveHeader->buf_size = _BufSize;
   _CurveHeader->data = sizeof(*_CurveHeader);
   _CurveData = _Buffer + _CurveHeader->data;
  //## end cCurve::cCurve%1078318184.body
}


cCurve::~cCurve()
{
  //## begin cCurve::~cCurve%.body preserve=yes
   if (_BufferAllocated && _Buffer != NULL) {
      cSystemUtils::Free(_Buffer);
   }
  //## end cCurve::~cCurve%.body
}



//## Other Operations (implementation)
BOOL_T cCurve::IsEmpty ()
{
  //## begin cCurve::IsEmpty%1078318185.body preserve=yes
   return (_Coords == 0);
  //## end cCurve::IsEmpty%1078318185.body
}

ULONG_T cCurve::GetCurveSize ()
{
  //## begin cCurve::GetCurveSize%1078318186.body preserve=yes
   return _Coords;
  //## end cCurve::GetCurveSize%1078318186.body
}

BUF_T cCurve::GetCurveData ()
{
  //## begin cCurve::GetCurveData%1078318187.body preserve=yes
   return _CurveData;
  //## end cCurve::GetCurveData%1078318187.body
}

void cCurve::GetXVec (DOUBLE_T *xvec, ULONG_T coords)
{
  //## begin cCurve::GetXVec%1078318188.body preserve=yes
   ULONG_T len = _MIN_(GetCurveSize(), coords);
   COORD_T * coord_ptr = (COORD_T*)_CurveData;
   for (ULONG_T i=0; i<len; i++) {
      xvec[i] = coord_ptr->x;
      coord_ptr++;
   }
  //## end cCurve::GetXVec%1078318188.body
}

void cCurve::GetYVec (DOUBLE_T *yvec, ULONG_T coords)
{
  //## begin cCurve::GetYVec%1078318189.body preserve=yes
   ULONG_T len = _MIN_(GetCurveSize(), coords);
   COORD_T * coord_ptr = (COORD_T*)_CurveData;
   for (ULONG_T i=0; i<len; i++) {
      yvec[i] = coord_ptr->y;
      coord_ptr++;
   }
  //## end cCurve::GetYVec%1078318189.body
}

ULONG_T cCurve::GetSize ()
{
  //## begin cCurve::GetSize%1078318190.body preserve=yes
   return _BufSize;
  //## end cCurve::GetSize%1078318190.body
}

BUF_T cCurve::GetData ()
{
  //## begin cCurve::GetData%1078318191.body preserve=yes
   return _Buffer;
  //## end cCurve::GetData%1078318191.body
}

void cCurve::GetCoord (ULONG_T pos, DOUBLE_T &x, DOUBLE_T &y)
{
  //## begin cCurve::GetCoord%1078318192.body preserve=yes
      if (pos < _Coords) {
         COORD_T * coord_ptr = (COORD_T*)_CurveData;
         coord_ptr += pos;
         x = coord_ptr->x;
         y = coord_ptr->y;
      }
  //## end cCurve::GetCoord%1078318192.body
}

void cCurve::SetCoord (ULONG_T pos, DOUBLE_T x, DOUBLE_T y)
{
  //## begin cCurve::SetCoord%1078318193.body preserve=yes
      if (pos < _Coords) {
         COORD_T * coord_ptr = (COORD_T*)_CurveData;
         coord_ptr += pos;
         coord_ptr->x = x;
         coord_ptr->y = y;
      }
  //## end cCurve::SetCoord%1078318193.body
}

// Additional Declarations
  //## begin cCurve%4045D069007D.declarations preserve=yes
  //## end cCurve%4045D069007D.declarations

//## begin module%4045D069007D.epilog preserve=yes
//## end module%4045D069007D.epilog
