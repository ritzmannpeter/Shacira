
#include "FirstHeader.h"
#include "cCurve.h"

cCurve::cCurve(unsigned int size, bool discrete)
{
   _Size = size;
   _Discrete = discrete;
   _XMin = cSystemUtils::RealtimeOffset();;
   _XMax = 0;
   _YMin = 0xfffffff;
   _YMax = 0;
   _TargetXScale[0] = 0;
   _TargetXScale[1] = 0;
   _SourceXScale[0] = 0;
   _SourceXScale[1] = 0;
   _CurveMutex = new QMutex(true);
}

cCurve::~cCurve()
{
}

void cCurve::SetPoint(double x, double y, bool derivated)
{
   QMutexLocker __lock__(_CurveMutex);
   if (_Discrete && !derivated) {
      unsigned long count = Count();
      if (count > 0) {
         COORDINATE_T * prev_ptr = GetCoordinate(count - 1);
         if (prev_ptr != NULL) {
            unsigned long _x = prev_ptr->x;
            unsigned long _y = prev_ptr->y;
            if (y != _y) {
               SetPoint(_x, y, true);
            }
         }
      }
   }
   if (_Coordinates.size() >= _Size) {
      _XMin = GetCoordinate(1)->x;
      QValueVector<COORDINATE_T>::iterator i = _Coordinates.begin();
      _Coordinates.erase(i);
   }
   COORDINATE_T coordinate;
   coordinate.x = (double)x;
   coordinate.y = y;
   _Coordinates.push_back(coordinate);
   if (x > _XMax) {
      _XMax = x;
   } else if (x < _XMin) {
      _XMin = x;
   }
   if (y > _YMax) {
      _YMax = y;
   } else if (y < _YMin) {
      _YMin = y;
   }
}

#ifdef lassma
static bool erased = true;
if (erased) {
   Beep(100,100);
   Beep(100,100);
   Beep(100,100);
   Beep(100,100);
   erased = false;
}
#endif

COORDINATE_T * cCurve::GetCoordinate(unsigned long pos)
{
   QMutexLocker __lock__(_CurveMutex);
   return &_Coordinates[pos];
}

unsigned long cCurve::Size()
{
   QMutexLocker __lock__(_CurveMutex);
   return _Coordinates.size();
}

unsigned long cCurve::Count()
{
   QMutexLocker __lock__(_CurveMutex);
   return _Coordinates.count();
}

unsigned long cCurve::Begin(unsigned long x)
{
   QMutexLocker __lock__(_CurveMutex);
   unsigned long count = Count();
   if (count == 0) return 0;
   for (int i=count-1; i>=0; i--) {
      unsigned long _x = _Coordinates[i].x;
      if (_x <= x) {
         return i;
      }
   }
   return count - 1;
}

unsigned long cCurve::End(unsigned long x)
{
   QMutexLocker __lock__(_CurveMutex);
   unsigned long count = Count();
   if (count == 0) return 0;
   for (int i=count-1; i>=0; i--) {
      unsigned long _x = _Coordinates[i].x;
      if (_x <= x) {
         if (i < count - 1) {
            return i + 1;
         } else {
            return i;
         }
      }
   }
   return 0;
}

void cCurve::SetXScale(double t_x0, double t_x1, double s_x0, double s_x1)
{
   _TargetXScale[0] = t_x0;
   _TargetXScale[1] = t_x1;
   _SourceXScale[0] = s_x0;
   _SourceXScale[1] = s_x1;
}

void cCurve::GetXSpan(double & x0, double & x1)
{
   x0 = _XMin;
   x1 = _XMax;
}

void cCurve::GetYSpan(double & y0, double & y1)
{
   y0 = _YMin;
   y1 = _YMax;
}

double cCurve::ScaleX(double x)
{
   double d0 = _SourceXScale[1] - _SourceXScale[0];
   if (d0 != 0) {
      double d1 = _TargetXScale[1] - _TargetXScale[0];
      double scaled = (x - _SourceXScale[0]) * (d1 / d0);
      return scaled;
   } else {
      return x;
   }
}

void cCurve::FillPointArray(QPointArray & points, double begin, double end)
{
   QMutexLocker __lock__(_CurveMutex);
   unsigned long count = Count();
   if (count == 0) return;
   unsigned long begin_index = Begin(begin);
   unsigned long end_index = End(end);
   int size = (begin_index - end_index) + 1;
   if (size > 0) {
      COORDINATE_T * coordinate = NULL;
      points.resize(size+2);
      coordinate = GetCoordinate(end_index);
      points.setPoint(0, _TargetXScale[0], coordinate->y);
      int index = 0;
      for (unsigned long i=end_index; i<=begin_index; i++) {
         coordinate = GetCoordinate(i);
         index = i - end_index + 1;
         double scaled_x = ScaleX(coordinate->x);
         double y = coordinate->y;
         points.setPoint(index, scaled_x, y);
      }
      coordinate = GetCoordinate(begin_index);
      points.setPoint(index + 1, _TargetXScale[1], coordinate->y);
   }
}
