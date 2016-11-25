
#include "crubberband.h"
#include <qstyle.h>
#include <qcolor.h>

cRubberBand::cRubberBand(QWidget * widget)
{
   _Widget = widget;
   _IsShown = false;
   _IsActive = false;
   _FullSet = 0;
   _ActRectangle = QRect(20, 20, 100, 100);
   _SrcScaleWidth = 0;
   _SrcScaleHeight = 0;
   _DstScaleWidth = 0;
   _DstScaleHeight = 0;
}

cRubberBand::~cRubberBand()
{
}

bool cRubberBand::IsActive()
{
   return _IsActive;
}

void cRubberBand::SetActive(bool value)
{
   _IsActive = value;
}

void cRubberBand::SetScale(int src_width, int src_height, int dst_width, int dst_height)
{
   _SrcScaleWidth = src_width;
   _SrcScaleHeight = src_height;
   _DstScaleWidth = dst_width;
   _DstScaleHeight = dst_height;
}

void cRubberBand::SetLeft(int left)
{
   _ActRectangle.setLeft(ScaleX(left));
   _FullSet |= 0x0001;
   if (_FullSet == 0x000f) {
      _IsActive = true;
   }
}

void cRubberBand::SetTop(int top)
{
   _ActRectangle.setTop(ScaleY(top));
   _FullSet |= 0x0002;
   if (_FullSet == 0x000f) {
      _IsActive = true;
   }
}

void cRubberBand::SetRight(int right)
{
   _ActRectangle.setRight(ScaleX(right));
   _FullSet |= 0x0004;
   if (_FullSet == 0x000f) {
      _IsActive = true;
   }
}

void cRubberBand::SetBottom(int bottom)
{
   _ActRectangle.setBottom(ScaleY(bottom));
   _FullSet |= 0x0008;
   if (_FullSet == 0x000f) {
      _IsActive = true;
   }
}

void cRubberBand::Grip(int x, int y)
{
   if (!_IsActive) return;
   QPoint p = QPoint(x, y);
   _TempRectangle.setTopLeft(p);
   _TempRectangle.setBottomRight(p);
   _IsShown = true;
}

void cRubberBand::Ungrip(int x, int y)
{
   if (!_IsActive) return;
   _ActRectangle = _TempRectangle;
   _IsShown = false;
}

void cRubberBand::UpdateRegion()
{
}

void cRubberBand::UpdateRegion(const QPoint pos)
{
   _TempRectangle.setBottomRight(pos);
   _Widget->update();
}

void cRubberBand::Paint(QPainter & painter)
{
   if (!_IsActive) return;
   QRect r = _Widget->rect();
   QColorGroup g = _Widget->colorGroup();
   if (_IsShown) {
      painter.setPen(_Widget->colorGroup().light());
      painter.setPen(Qt::DashDotLine);
      painter.drawRect(_TempRectangle.normalize());
   } else {
      painter.setPen(Qt::green);
      painter.drawRect(_ActRectangle.normalize());
   }
}

void cRubberBand::GetRectangle(int & left, int & top, int & right, int & bottom)
{
   left = UnscaleX(_ActRectangle.normalize().left());
   top = UnscaleY(_ActRectangle.normalize().top());
   right = UnscaleX(_ActRectangle.normalize().right());
   bottom = UnscaleY(_ActRectangle.normalize().bottom());
}

int cRubberBand::ScaleX(int value)
{
   if (_SrcScaleWidth == 0 ||
       _DstScaleWidth == 0) return value;
   if (_SrcScaleWidth == _DstScaleWidth) return value;
   double y_factor = (double)_SrcScaleWidth / (double)_DstScaleWidth;
   int scaled = (int)((double)value * y_factor);
   return scaled;
}

int cRubberBand::ScaleY(int value)
{
   if (_SrcScaleHeight == 0 ||
       _DstScaleHeight == 0) return value;
   if (_SrcScaleHeight == _DstScaleHeight) return value;
   double y_factor = (double)_SrcScaleHeight / (double)_DstScaleHeight;
   int scaled = (int)((double)value * y_factor);
   return scaled;
}

int cRubberBand::UnscaleX(int value)
{
   if (_SrcScaleWidth == 0 ||
       _DstScaleWidth == 0) return value;
   if (_SrcScaleWidth == _DstScaleWidth) return value;
   double y_factor = (double)_DstScaleWidth / (double)_SrcScaleWidth;
   int scaled = (int)((double)value * y_factor);
   return scaled;
}

int cRubberBand::UnscaleY(int value)
{
   if (_SrcScaleHeight == 0 ||
       _DstScaleHeight == 0) return value;
   if (_SrcScaleHeight == _DstScaleHeight) return value;
   double y_factor = (double)_DstScaleHeight / (double)_SrcScaleHeight;
   int scaled = (int)((double)value * y_factor);
   return scaled;
}

