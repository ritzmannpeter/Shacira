
#ifndef _crubberband_h_
#define _crubberband_h_

#include "CWidgetBase.h"
#include <qwidget.h>
#include <qpainter.h>

class SH_QT_WIDGET_PLUGIN_EXPORT cRubberBand {
public:
   cRubberBand(QWidget * widget);
   virtual ~cRubberBand();
   void SetActive(bool value);
   bool IsActive();
   void SetScale(int src_width, int src_height, int dst_width, int dst_height);
   void SetLeft(int left);
   void SetTop(int top);
   void SetRight(int right);
   void SetBottom(int bottom);
   void Grip(int x, int y);
   void Ungrip(int x, int y);
   void UpdateRegion();
   void UpdateRegion(const QPoint pos);
   void Paint(QPainter & painter);
   void GetRectangle(int & left, int & top, int & right, int & bottom);
private:
   int ScaleX(int value);
   int ScaleY(int value);
   int UnscaleX(int value);
   int UnscaleY(int value);
private:
   QWidget * _Widget;
   bool _IsShown;
   bool _IsActive;
   int _SrcScaleWidth;
   int _SrcScaleHeight;
   int _DstScaleWidth;
   int _DstScaleHeight;
   QRect _ActRectangle;
   QRect _TempRectangle;
   unsigned short _FullSet;
};
#endif


