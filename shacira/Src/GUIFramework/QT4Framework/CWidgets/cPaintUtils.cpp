
#include "cpaintutils.h"

#undef XP_STYLE
#define SHRINK_FACTOR   6
#define XP_LIGHT_BLUE   190

QStyle * _Style = NULL;

void cPaintUtils::SetTab(QPainter & painter, QRect * rectangle)
{
#ifdef XP_STYLE
   QColor color = Qt::blue;
   color = color.light(XP_LIGHT_BLUE);
   QBrush brush(color);
   painter.setBrush(brush);
   painter.drawRect(*rectangle);
   SetBox(painter, rectangle, Qt::white);
#else
   QBrush brush(Qt::gray);
   painter.setBrush(brush);
   painter.drawRect(*rectangle);
   SetSunken(painter, rectangle);
#endif
}

void cPaintUtils::SetShape(QPainter & painter, QRect * rectangle, QColor color)
{
   QBrush brush(color);
   QPen pen(color, 0);
   painter.setPen(pen);
   painter.setBrush(brush);
   painter.drawRect(*rectangle);
}

void cPaintUtils::SetBox(QPainter & painter, QRect * rectangle, QColor color)
{
#ifdef XP_STYLE
   QPen pen(color, 1);
   painter.setPen(pen);
   painter.drawRoundRect(*rectangle, 3, 3);
#else
   QPen pen(color, 1);
   painter.setPen(pen);
   painter.drawLine(rectangle->left(), rectangle->top(), rectangle->right(), rectangle->top());
   painter.drawLine(rectangle->left(), rectangle->top(), rectangle->left(), rectangle->bottom());
   painter.drawLine(rectangle->right(), rectangle->bottom(), rectangle->right(), rectangle->top());
   painter.drawLine(rectangle->right(), rectangle->bottom(), rectangle->left(), rectangle->bottom());
#endif
}

void cPaintUtils::SetRaised(QPainter & painter, QRect * rectangle)
{
   QPen pen(Qt::white, 0);
   painter.setPen(pen);
   painter.drawLine(rectangle->left(), rectangle->top(), rectangle->right(), rectangle->top());
   painter.drawLine(rectangle->left(), rectangle->top(), rectangle->left(), rectangle->bottom());
   pen.setColor(Qt::gray);
   painter.setPen(pen);
   painter.drawLine(rectangle->right(), rectangle->bottom(), rectangle->right(), rectangle->top());
   painter.drawLine(rectangle->right(), rectangle->bottom(), rectangle->left(), rectangle->bottom());
}

void cPaintUtils::SetSunken(QPainter & painter, QRect * rectangle)
{
   QPen pen(Qt::gray, 0);
   painter.setPen(pen);
   painter.drawLine(rectangle->left(), rectangle->top(), rectangle->right(), rectangle->top());
   painter.drawLine(rectangle->left(), rectangle->top(), rectangle->left(), rectangle->bottom());
   pen.setColor(Qt::white);
   painter.setPen(pen);
   painter.drawLine(rectangle->right(), rectangle->bottom(), rectangle->right(), rectangle->top());
   painter.drawLine(rectangle->right(), rectangle->bottom(), rectangle->left(), rectangle->bottom());
}

void cPaintUtils::PaintUpGrip(QPainter & painter, QRect * rectangle)
{
#ifdef XP_STYLE
   QColor color = Qt::blue;
   color = color.light(XP_LIGHT_BLUE);
   SetShape(painter, rectangle, color);
   QPen pen(Qt::black, 3);
   painter.setPen(pen);
   int x1 = rectangle->width() / 2;
   int xspan = x1 / 2;
   int x0 = x1 - xspan;
   int x2 = x1 + xspan;
   int yspan = rectangle->height() / 3;
   int y0 = rectangle->bottom() - yspan;
   int y1 = rectangle->top() + yspan;
   painter.drawLine(x0, y0, x1, y1);
   painter.drawLine(x1, y1, x2, y0);
   SetBox(painter, rectangle, Qt::white);
#else
   QBrush brush(Qt::black);
   QPen pen(Qt::black, 0);
   painter.setBrush(brush);
   painter.setPen(pen);
   int x = rectangle->width() / 2;
   QPoint p1(rectangle->left() + SHRINK_FACTOR, rectangle->bottom() - SHRINK_FACTOR);
   QPoint p2(x, rectangle->top() + SHRINK_FACTOR);
   QPoint p3(rectangle->right() - SHRINK_FACTOR, rectangle->bottom() - SHRINK_FACTOR);
   QPoint p4(rectangle->left() + SHRINK_FACTOR, rectangle->bottom() - SHRINK_FACTOR);
#ifdef QT4
   QPolygon points(4);
#else
   QPointArray points(4);
#endif
   points.setPoint(0, p1);
   points.setPoint(1, p2);
   points.setPoint(2, p3);
   points.setPoint(3, p4);
   painter.drawPolygon(points);
   SetRaised(painter, rectangle);
#endif
}

void cPaintUtils::PaintDownGrip(QPainter & painter, QRect * rectangle)
{
#ifdef XP_STYLE
   QColor color = Qt::blue;
   color = color.light(XP_LIGHT_BLUE);
   SetShape(painter, rectangle, color);
   QPen pen(Qt::black, 3);
   painter.setPen(pen);
   int x1 = rectangle->width() / 2;
   int xspan = x1 / 2;
   int x0 = x1 - xspan;
   int x2 = x1 + xspan;
   int yspan = rectangle->height() / 3;
   int y0 = rectangle->bottom() - yspan;
   int y1 = rectangle->top() + yspan;
   painter.drawLine(x0, y1, x1, y0);
   painter.drawLine(x1, y0, x2, y1);
   SetBox(painter, rectangle, Qt::white);
#else
   QBrush brush(Qt::black);
   QPen pen(Qt::black, 0);
   painter.setBrush(brush);
   painter.setPen(pen);
   int x = rectangle->width() / 2;
   QPoint p1(rectangle->left() + SHRINK_FACTOR, rectangle->top() + SHRINK_FACTOR);
   QPoint p2(x, rectangle->bottom() - SHRINK_FACTOR);
   QPoint p3(rectangle->right() - SHRINK_FACTOR, rectangle->top() + SHRINK_FACTOR);
   QPoint p4(rectangle->left() + SHRINK_FACTOR, rectangle->top() + SHRINK_FACTOR);
#ifdef QT4
   QPolygon points(4);
#else
   QPointArray points(4);
#endif
   points.setPoint(0, p1);
   points.setPoint(1, p2);
   points.setPoint(2, p3);
   points.setPoint(3, p4);
   painter.drawPolygon(points);
   SetRaised(painter, rectangle);
#endif
}


