
#ifndef __cpaintutils__
#define __cpaintutils__

#include "CWidgetBase.h"
#include <qpainter.h>
#include <qrect.h>
#include <qstyle.h>

class SH_QT_WIDGET_PLUGIN_EXPORT cPaintUtils
{
public:
   static void SetTab(QPainter & painter, QRect * rectangle);
   static void SetShape(QPainter & painter, QRect * rectangle, QColor color);
   static void SetBox(QPainter & painter, QRect * rectangle, QColor color);
   static void SetRaised(QPainter & painter, QRect * rectangle);
   static void SetSunken(QPainter & painter, QRect * rectangle);
   static void PaintUpGrip(QPainter & painter, QRect * rectangle);
   static void PaintDownGrip(QPainter & painter, QRect * rectangle);
private:
   static QStyle * _Style;
};

#endif

