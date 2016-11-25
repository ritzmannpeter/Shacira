
#ifndef _CCURVE_H_
#define _CCURVE_H_

#include "qvaluevector.h"
#include "qpointarray.h"
#define QT_THREAD_SUPPORT
#include <qmutex.h>

typedef struct coordinate {
   double x;
   double y;
}  COORDINATE_T;

class cCurve {
public:
   cCurve(unsigned int size = 100, bool discrete = false);
   virtual ~cCurve();
   void SetPoint(double x, double y, bool derivated = false);
   COORDINATE_T * GetCoordinate(unsigned long pos);
   unsigned long Size();
   unsigned long Count();
   unsigned long Begin(unsigned long x);
   unsigned long End(unsigned long x);
   void SetXScale(double t_x0, double t_x1, double s_x0, double s_x1);
   double ScaleX(double x);
   void GetXSpan(double & x0, double & x1);
   void GetYSpan(double & y0, double & y1);
   void FillPointArray(QPointArray & points, double begin, double end);
private:
   bool _Discrete;
   unsigned long _Size;
   double _XMin;
   double _XMax;
   double _YMin;
   double _YMax;
   double _TargetXScale[2];
   double _SourceXScale[2];
   QValueVector<COORDINATE_T> _Coordinates;
   QMutex * _CurveMutex;
};

#endif

