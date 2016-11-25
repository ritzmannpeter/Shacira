
#include "CRingGraphic.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(AdditionalWidget, \
                   CRingGraphic, \
                   ICON_SET("cgraphic"), \
                   "graphic widget to display of the data of numeric data rings")
#endif

#include "cPaintUtils.h"
#ifndef QT_PLUGIN
#include "System/Structs/cExtendedObjectRing.h"
#include "System/Objects/cJobEntry.h"
#endif

#if defined(_WIN32)
#include <windows.h>
#endif

#ifndef _MIN_
#define _MIN_(a,b) (((a)<(b)) ? a : b)
#endif

#define XPIXEL_END() (_DrawRectangle.right())
#define YPIXEL_END() (_DrawRectangle.bottom())
#define PIXEL_WIDTH() (_DrawRectangle.width())
#define PIXEL_HEIGHT() (_DrawRectangle.height())

#define SET_X_NULL_CORRECTION(nc,ws,we,ps,pe,np) \
{ \
   if (ws != 0) { \
      nc = (ws) / (we - ws); \
      nc = nc * pe; \
   } \
   nc += np; \
}

#define SET_Y_NULL_CORRECTION(nc,ws,we,ps,pe,np) \
{ \
   if (ws != 0) { \
      nc = (ws) / (we - ws); \
      nc = nc * pe; \
   } \
   nc += (pe - np); \
}

#define SET_X_ZERO_VALUE(v,nc,ps,pe,np) \
{ \
   v += nc; \
   if (nc != 0) { \
      double diff = v - np; \
      if (diff > 0) { \
         double fact = (pe - np) / ((pe - np) + nc); \
         diff *= fact; \
         v = np + diff; \
      } else if (diff == 0) { \
      } else { \
         double fact = (np + nc) / np; \
         diff *= fact; \
         v = np + diff; \
      } \
   } \
}

#define SET_Y_ZERO_VALUE(v,nc,ps,pe,np) \
{ \
   v -= nc; \
   if (nc != 0) { \
      double diff = v - np; \
      if (diff < 0) { \
         double fact = np / (np + nc); \
         diff *= fact; \
         v = np + diff; \
      } else if (diff == 0) { \
      } else { \
         double fact = (np + nc) / np; \
         diff *= fact; \
         v = np + diff; \
      } \
   } \
}

static double XZero(double value, double world_start, double world_end,
                    double pixel_start, double pixel_end, double null_pos)
{
   if (null_pos == 0) {
      return value;
   } else {
      double null_correction = 0;
      if (world_start != 0) {
         null_correction = (world_start) / (world_end - world_start);
         null_correction = null_correction * pixel_end;
      }
      null_correction += null_pos;
      value += null_correction;

      double diff = value - null_pos;
      if (diff > 0) {
         // stauchen
         double fact = (pixel_end - null_pos) / ((pixel_end - null_pos) + null_correction);
         diff *= fact;
         value = null_pos + diff;
      } else if (diff == 0) {
         return value;
      } else {
         // strecken
         double fact = (null_pos + null_correction) / null_pos;
         diff *= fact;
         value = null_pos + diff;
      }
      return value;
   }
}

static double YZero(double value, double world_start, double world_end,
                    double pixel_start, double pixel_end, double null_pos)
{
   if (null_pos == 0) {
      return value;
   } else {
      double null_correction = 0;
      if (world_start != 0) {
         null_correction = (world_start) / (world_end - world_start);
         null_correction = null_correction * pixel_end;
      }
      null_correction += (pixel_end - null_pos);
      value -= null_correction;

      double diff = value - null_pos;
      if (diff < 0) {
         // stauchen
         double fact = null_pos / (null_pos + null_correction);
         diff *= fact;
         value = null_pos + diff;
      } else if (diff == 0) {
         return value;
      } else {
         // strecken
         double fact = (null_pos + null_correction) / null_pos;
         diff *= fact;
         value = null_pos + diff;
      }
      return value;
   }
}

static int Pixel(double world, double world_start, double world_end, double pixel_start, double pixel_end)
{
   double pixel_span = pixel_end - pixel_start;
   double world_span = world_end - world_start;
   double factor = pixel_span / world_span;
   double value = world * factor;
   value += pixel_start;
   return value;
}

static double World(double pixel, double world_start, double world_end, double pixel_start, double pixel_end)
{
   double pixel_span = pixel_end - pixel_start;
   double world_span = world_end - world_start;
   double factor = world_span / pixel_span;
   double value = pixel * factor;
   value += world_start;
   return value;
}

CRingGraphic::CRingGraphic(QWidget * parent, const char * name, WFlags f)
   : QLabel(parent, name, 0),
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET

   _CursorValue = false;
   _CursorColorValue = Qt::red;
   _GridColorValue = Qt::white;
   _AxisColorValue = Qt::black;
   _GridXLinesValue = 10;
   _GridYLinesValue = 10;
   _AequatorValue = 0;
   _NullMeridianValue = 0;

   _RingRef = NULL;
   _RingView = NULL;

   _Curve0IndexValue = -1;
   _Curve1IndexValue = -1;
   _Curve2IndexValue = -1;
   _Curve3IndexValue = -1;
   _Curve4IndexValue = -1;
   _Curve5IndexValue = -1;

   _RingBuffer = NULL;
   _RingBufSize = 0;
   
   _Curve0ColorValue = Qt::black;
   _Curve1ColorValue = Qt::black;
   _Curve2ColorValue = Qt::black;
   _Curve3ColorValue = Qt::black;
   _Curve4ColorValue = Qt::black;
   _Curve5ColorValue = Qt::black;

   _LeftCursorPos = _LeftZoomPos = 0;
   _RightCursorPos = _RightZoomPos = 0;
   _XScaleStart = 0;
   _XScaleEnd = 0;
   _XPrecisionValue = 1;
   _AequatorPos = 0;
   _NullMeridianPos = 0;
}

CRingGraphic::~CRingGraphic() 
{
}

void CRingGraphic::resizeEvent(QResizeEvent * e)
{
//   QLabel::resizeEvent(e);
   InitWidget();
   PaintAll();
}

void CRingGraphic::paintEvent(QPaintEvent * e)
{
   QPainter painter(this);
   bitBlt(this, 0, 0, &_DoubleBuffer);
   PaintCursors(painter);
}

void CRingGraphic::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QLabel::mousePressEvent(e);
   }
}

void CRingGraphic::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QLabel::mouseReleaseEvent(e);
   }
}

void CRingGraphic::LeftCursorLeft()
{
   if (_LeftCursorPos > _LeftZoomPos) {
      _LeftCursorPos--;
      char value[128] = {0};
      SafePrintf(value, sizeof(value), "%.1f", World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
      emit LeftCurXChanged(value);
      update();
      EmitAllChanges();
   }
}

void CRingGraphic::LeftCursorRight()
{
   if (_LeftCursorPos < _RightCursorPos) {
      _LeftCursorPos++;
      char value[128] = {0};
      SafePrintf(value, sizeof(value), "%.1f", World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
      emit LeftCurXChanged(value);
      update();
      EmitAllChanges();
   }
}

void CRingGraphic::RightCursorLeft()
{
   if (_RightCursorPos > _LeftCursorPos) {
      _RightCursorPos--;
      char value[128] = {0};
      SafePrintf(value, sizeof(value), "%.1f", World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
      emit RightCurXChanged(value);
      update();
      EmitAllChanges();
   }
}

void CRingGraphic::RightCursorRight()
{
   if (_RightCursorPos < _RightZoomPos) {
      _RightCursorPos++;
      char value[128] = {0};
      SafePrintf(value, sizeof(value), "%.1f", World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
      emit RightCurXChanged(value);
      update();
      EmitAllChanges();
   }
}

void CRingGraphic::ZoomIn()
{
   _LeftZoomPos = _LeftCursorPos;
   _RightZoomPos = _RightCursorPos;
   QString svalue;
   FormatValue(_XPrecisionValue, svalue, World(_LeftZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
   emit XStartChanged(svalue);
   FormatValue(_XPrecisionValue, svalue, World(_RightZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
   emit XEndChanged(svalue);
   PaintAll();
}

void CRingGraphic::ZoomOut()
{
   _LeftZoomPos = 0;
   _RightZoomPos = XPIXEL_END();
   QString svalue;
   FormatValue(_XPrecisionValue, svalue, _XScaleStart);
   emit XStartChanged(svalue);
   FormatValue(_XPrecisionValue, svalue, _XScaleEnd);
   emit XEndChanged(svalue);
   PaintAll();
}


// GUI related virtual methods

void CRingGraphic::View()
{
   PaintAll();
}

void CRingGraphic::DelayedLanguageChange()
{
}

// CCS related virtual methods

void CRingGraphic::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_RingSpec, _RingRef, _RingView, 0);
   if (_RingRef != 0) {
      _RingBufSize = _RingRef->ValueSize();
   }
WMETHOD_VOID_EPILOG
#endif
   setBackgroundMode(Qt::NoBackground);
   InitWidget();
   PaintAll();
}

void CRingGraphic::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
#endif
}

void CRingGraphic::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (id) {
   case 0:
      _RingBuffer = buf;
      break;
   default: return;
   }
   Notify(VIEW_DATA);
WMETHOD_VOID_EPILOG
#endif
}

void CRingGraphic::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CRingGraphic::PaintAll()
{
   QPainter painter;
   painter.begin(&_DoubleBuffer, this);
   cPaintUtils::SetShape(painter, &_DrawRectangle, paletteBackgroundColor());
   PaintGrid(painter);
   PaintCurves(painter);
   painter.end();
   update();
   EmitAllChanges();
}

void CRingGraphic::PaintGrid(QPainter & painter)
{
   int i = 0;
   double pos = 0;
   QPen pen = QPen(_GridColorValue, 0);
   QPen null_pen = QPen(_AxisColorValue, 0);
   painter.setPen(pen);
   int x_lines = _GridXLinesValue;
   double x_scale_factor = XPIXEL_END() / (double)x_lines;
   for (i=0; i<x_lines; i++) {
      if (i == 0) {
         continue;
      }
      pos = i * x_scale_factor;
      if (i == _NullMeridianValue) {
         painter.setPen(null_pen);
         painter.drawLine(pos, 0, pos, YPIXEL_END());
         painter.setPen(pen);
         _NullMeridianPos = pos;
      } else {
         painter.drawLine(pos, 0, pos, YPIXEL_END());
      }
   }
   int y_lines = _GridYLinesValue;
   double y_scale_factor = YPIXEL_END() / (double)y_lines;
   for (i=0; i<y_lines; i++) {
      if (i == 0) {
         continue;
      }
      pos = i * y_scale_factor;
      if (i == _AequatorValue) {
         painter.setPen(null_pen);
         painter.drawLine(0, pos, XPIXEL_END(), pos);
         painter.setPen(pen);
         _AequatorPos = pos;
      } else {
         painter.drawLine(0, pos, XPIXEL_END(), pos);
      }
   }
#ifdef lassma
   painter.setPen(null_pen);
   if (0 == _NullMeridianValue) {
      painter.drawLine(0, 0, 0, YPIXEL_END());
      _NullMeridianPos = 0;
   }
   if (0 == _AequatorValue) {
     painter.drawLine(0, YPIXEL_END(), XPIXEL_END(), YPIXEL_END());
     _AequatorPos = 0;
   }
#endif
}

void CRingGraphic::PaintCursors(QPainter & painter)
{
   if (!_CursorValue) {
      return;
   }
   int i = 0;
   double pos = 0;
   QPen pen = QPen(_CursorColorValue, 1);
   painter.setPen(pen);
//   ULONG_T left_pos = _LeftCursorPos - _LeftZoomPos;
//   ULONG_T right_pos = Pixel(_XScaleEnd, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());
//   right_pos -= (_RightZoomPos - _RightCursorPos);
   ULONG_T left_dist = _LeftCursorPos - _LeftZoomPos;
   ULONG_T right_dist = _RightZoomPos - _RightCursorPos;
   double scale_factor = (double)XPIXEL_END() / (double)(_RightZoomPos - _LeftZoomPos);
   left_dist *= scale_factor;
   right_dist *= scale_factor;
   ULONG_T left_pos = left_dist;
   ULONG_T right_pos = XPIXEL_END() - right_dist;
   painter.drawLine(left_pos, 0, left_pos, YPIXEL_END());
   painter.drawLine(right_pos, 0, right_pos, YPIXEL_END());
}

void CRingGraphic::PaintCurves(QPainter & painter)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (_RingBuffer != NULL) {
         cExtendedObjectRing ring(_RingBuffer, _RingBufSize);
         ULONG_T used = ring.Used();
         if (used > 0) {
            _XScaleStart = 0;
            _XScaleEnd = used;
            double yscale_start = 0;
            double yscale_end = 150;
            double ywidth = yscale_end - yscale_start;
            double xview_start = World(0, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());
            double xview_end = World(used, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());
            FLOAT_T xval = 0;
            FLOAT_T yval = 0;
            QPointArray curve0(used);
            QPointArray curve1(used);
            QPointArray curve2(used);
            QPointArray curve3(used);
            QPointArray curve4(used);
            QPointArray curve5(used);
            for (ULONG_T i=0; i<used; i++) {
               cTransientObject * object = ring.GetObject(i);
               if (object != NULL) {
                  UCHAR_T object_type = object->get_Type();
                  if (object_type == OT_JOB_ENTRY) {
                     cJobEntry * entry = (cJobEntry*)object;
                     ULONG_T properties = entry->Properties();
                     if (_Curve0IndexValue >=0 && _Curve0IndexValue < properties) {
try {
                        STRING_T svalue = entry->PropertyValue(_Curve0IndexValue);
                        DOUBLE_T dvalue = atof(svalue.c_str());
                        xval = (FLOAT_T)i - xview_start;
                        yval = ywidth - (FLOAT_T)dvalue + yscale_start;
                        xval = Pixel(xval, xview_start, xview_end, 0, XPIXEL_END());
                        yval = Pixel(yval, yscale_start, yscale_end, 0, YPIXEL_END());
                        QPoint point;
                        point.setX(xval);
                        point.setY(yval);
                        curve0.setPoint(i, point);
} catch (...) {
   int dummy = 0;
}
                     } else {
                        curve0.setPoint(i, QPoint(0,0));
                     }
                     if (_Curve1IndexValue >= 0 && _Curve1IndexValue < properties) {
try {
                        STRING_T svalue = entry->PropertyValue(_Curve1IndexValue);
                        DOUBLE_T dvalue = atof(svalue.c_str());
                        xval = (FLOAT_T)i - xview_start;
                        yval = ywidth - (FLOAT_T)dvalue + yscale_start;
                        xval = Pixel(xval, xview_start, xview_end, 0, XPIXEL_END());
                        yval = Pixel(yval, yscale_start, yscale_end, 0, YPIXEL_END());
                        QPoint point;
                        point.setX(xval);
                        point.setY(yval);
                        curve1.setPoint(i, point);
} catch (...) {
   int dummy = 0;
}
                     } else {
                        curve1.setPoint(i, QPoint(0,0));
                     }
                     if (_Curve2IndexValue >= 0 && _Curve2IndexValue < properties) {
try {
                        STRING_T svalue = entry->PropertyValue(_Curve2IndexValue);
                        DOUBLE_T dvalue = atof(svalue.c_str());
                        xval = (FLOAT_T)i - xview_start;
                        yval = ywidth - (FLOAT_T)dvalue + yscale_start;
                        xval = Pixel(xval, xview_start, xview_end, 0, XPIXEL_END());
                        yval = Pixel(yval, yscale_start, yscale_end, 0, YPIXEL_END());
                        QPoint point;
                        point.setX(xval);
                        point.setY(yval);
                        curve2.setPoint(i, point);
} catch (...) {
   int dummy = 0;
}
                     } else {
                        curve2.setPoint(i, QPoint(0,0));
                     }
                     if (_Curve3IndexValue >= 0 && _Curve3IndexValue < properties) {
try {
                        STRING_T svalue = entry->PropertyValue(_Curve3IndexValue);
                        DOUBLE_T dvalue = atof(svalue.c_str());
                        xval = (FLOAT_T)i - xview_start;
                        yval = ywidth - (FLOAT_T)dvalue + yscale_start;
                        xval = Pixel(xval, xview_start, xview_end, 0, XPIXEL_END());
                        yval = Pixel(yval, yscale_start, yscale_end, 0, YPIXEL_END());
                        QPoint point;
                        point.setX(xval);
                        point.setY(yval);
                        curve3.setPoint(i, point);
} catch (...) {
   int dummy = 0;
}
                     } else {
                        curve3.setPoint(i, QPoint(0,0));
                     }
                     if (_Curve4IndexValue >= 0 && _Curve4IndexValue < properties) {
try {
                        STRING_T svalue = entry->PropertyValue(_Curve4IndexValue);
                        DOUBLE_T dvalue = atof(svalue.c_str());
                        xval = (FLOAT_T)i - xview_start;
                        yval = ywidth - (FLOAT_T)dvalue + yscale_start;
                        xval = Pixel(xval, xview_start, xview_end, 0, XPIXEL_END());
                        yval = Pixel(yval, yscale_start, yscale_end, 0, YPIXEL_END());
                        QPoint point;
                        point.setX(xval);
                        point.setY(yval);
                        curve4.setPoint(i, point);
} catch (...) {
   int dummy = 0;
}
                     } else {
                        curve4.setPoint(i, QPoint(0,0));
                     }
                     if (_Curve5IndexValue >= 0 && _Curve5IndexValue < properties) {
try {
                        STRING_T svalue = entry->PropertyValue(_Curve5IndexValue);
                        DOUBLE_T dvalue = atof(svalue.c_str());
                        xval = (FLOAT_T)i - xview_start;
                        yval = ywidth - (FLOAT_T)dvalue + yscale_start;
                        xval = Pixel(xval, xview_start, xview_end, 0, XPIXEL_END());
                        yval = Pixel(yval, yscale_start, yscale_end, 0, YPIXEL_END());
                        QPoint point;
                        point.setX(xval);
                        point.setY(yval);
                        curve5.setPoint(i, point);
} catch (...) {
   int dummy = 0;
}
                     } else {
                        curve5.setPoint(i, QPoint(0,0));
                     }
                  }
                  object->Release();
               }
            }
int size = curve0.size();
            QColor color = CurveColor(0);
            QPen pen = QPen(color, 0);
            painter.setPen(pen);
            painter.drawPolyline(curve0);

size = curve1.size();
            color = CurveColor(1);
            pen = QPen(color, 0);
            painter.setPen(pen);
            painter.drawPolyline(curve1);

size = curve2.size();
            color = CurveColor(2);
            pen = QPen(color, 0);
            painter.setPen(pen);
            painter.drawPolyline(curve2);

size = curve3.size();
            color = CurveColor(3);
            pen = QPen(color, 0);
            painter.setPen(pen);
            painter.drawPolyline(curve3);

size = curve4.size();
            color = CurveColor(4);
            pen = QPen(color, 0);
            painter.setPen(pen);
            painter.drawPolyline(curve4);

size = curve5.size();
            color = CurveColor(5);
            pen = QPen(color, 0);
            painter.setPen(pen);
            painter.drawPolyline(curve5);
         }
      }
   } catch (...) {
      ErrorPrintf("unhandled exception getting ring data\n");
   }
WMETHOD_VOID_EPILOG
#endif
}

void CRingGraphic::InitWidget()
{
   _DoubleBuffer = QPixmap(size());
   _DrawRectangle.setLeft(0);
   _DrawRectangle.setTop(0);
   _DrawRectangle.setWidth(width());
   _DrawRectangle.setHeight(height());
   _LeftCursorPos = _RightZoomPos = 0;
   _RightCursorPos = _RightZoomPos = XPIXEL_END();
}

void CRingGraphic::PaintCurve(QPainter & painter, ULONG_T index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
#ifdef lassma
   QRect paint_area = _DrawRectangle;
   cFloatCurve curve(_CurveBuffer[index]);
   double min = curve.GetMinVal();;
   double max = curve.GetMaxVal();
   ULONG_T value_count = curve.GetValueCount();
   _XScaleStart = curve.GetXScaleStart();
   if (curve.GetXScaleEnd() != 0) {
      _XScaleEnd = curve.GetXScaleEnd();
      _XPrecisionValue = curve.GetXPrecision();
   }
   double yscale_start = curve.GetYScaleStart();
   double yscale_end = curve.GetYScaleEnd();
   double ywidth = yscale_end - yscale_start;
   QColor color = CurveColor(index);
   QPen pen = QPen(color, 0);
   painter.setPen(pen);
   QPointArray point_array(value_count);
   ULONG_T i = 0;
   QPoint point;
   FLOAT_T xval = 0;
   FLOAT_T yval = 0;
   double xview_start = World(_LeftZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());
   double xview_end = World(_RightZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());
#define USE_MACROS
#ifdef USE_MACROS
   double xnull_correction = 0;
   SET_X_NULL_CORRECTION(xnull_correction,_XScaleStart,_XScaleEnd,0,XPIXEL_END(),_NullMeridianPos);
   double ynull_correction = 0;
   SET_Y_NULL_CORRECTION(ynull_correction,yscale_start,yscale_end,0,YPIXEL_END(),_AequatorPos);
#endif
   for (i=0; i<value_count; i++) {
      curve.GetXVal(xval, i);
      curve.GetYVal(yval, i);
      xval = xval - xview_start;
      yval = ywidth - yval + yscale_start;
      xval = Pixel(xval, xview_start, xview_end, 0, XPIXEL_END());
      yval = Pixel(yval, yscale_start, yscale_end, 0, YPIXEL_END());
      if (_NullMeridianValue != 0) {
#ifdef USE_MACROS
         SET_X_ZERO_VALUE(xval,xnull_correction,0,XPIXEL_END(),_NullMeridianPos);
#else
         xval = XZero(xval, _XScaleStart, _XScaleEnd, 0, XPIXEL_END(), _NullMeridianPos);
#endif
      }
      point.setX(xval);
      if (_AequatorValue != 0) {
#ifdef USE_MACROS
         SET_Y_ZERO_VALUE(yval,ynull_correction,0,YPIXEL_END(),_AequatorPos);
#else
         yval = YZero(yval, yscale_start, yscale_end, 0, YPIXEL_END(), _AequatorPos);
#endif
      }
      point.setY(yval);
      point_array.setPoint(i, point);
   }
   painter.drawPolyline(point_array);
   QWMatrix identity;
   painter.setWorldMatrix(identity);
#endif
WMETHOD_VOID_EPILOG
#endif
}

QColor CRingGraphic::CurveColor(ULONG_T index)
{
   switch (index) {
   case 0: return _Curve0ColorValue;
   case 1: return _Curve1ColorValue;
   case 2: return _Curve2ColorValue;
   case 3: return _Curve3ColorValue;
   case 4: return _Curve4ColorValue;
   case 5: return _Curve5ColorValue;
   }
   return Qt::black;
}

void CRingGraphic::FormatValue(ULONG_T precision, QString & text, DOUBLE_T value)
{
   char sval[64] = {0};
   switch (precision) {
   case 0:
      SafePrintf(sval, sizeof(sval), "%.0f", value);
      break;
   case 1:
      SafePrintf(sval, sizeof(sval), "%.1f", value);
      break;
   case 2:
      SafePrintf(sval, sizeof(sval), "%.2f", value);
      break;
   case 3:
      SafePrintf(sval, sizeof(sval), "%.3f", value);
      break;
   case 4:
      SafePrintf(sval, sizeof(sval), "%.4f", value);
      break;
   default:
      SafePrintf(sval, sizeof(sval), "%f", value);
      break;
   }
   text = sval;
}

void CRingGraphic::EmitAllChanges()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
#ifdef lassma
   for (ULONG_T i=0; i<MAX_PROC_CURVES; i++) {
      if (_CurveBuffer[i] != NULL) {
         cFloatCurve curve(_CurveBuffer[i]);
         ULONG_T precision = curve.GetYPrecision();
         QString dim = curve.GetYDim();
         emit Dimension0Changed(dim);

         double value = GetCurveValue(i, World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
         EmitLeftCurValChanged(i, precision, value);

         value = GetCurveValue(i, World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
         EmitRightCurValChanged(i, precision, value);

         value = curve.GetYScaleStart();
         EmitYStartChanged(i, precision, value);

         value = curve.GetYScaleEnd();
         EmitYEndChanged(i, precision, value);

         value = curve.GetMinVal();
         EmitYMinChanged(i, precision, value);

         value = curve.GetMaxVal();
         EmitYMaxChanged(i, precision, value);

         // intermediate
         QString svalue;

         FormatValue(_XPrecisionValue, svalue, World(_LeftZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
         emit XStartChanged(svalue);
         FormatValue(_XPrecisionValue, svalue, World(_RightZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
         emit XEndChanged(svalue);

         FormatValue(_XPrecisionValue, svalue, World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
         emit LeftCurXChanged(svalue);
         FormatValue(_XPrecisionValue, svalue, World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
         emit RightCurXChanged(svalue);

      }
   }
#endif
WMETHOD_VOID_EPILOG
#endif
}

void CRingGraphic::EmitLeftCurValChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue;
   FormatValue(precision, svalue, value);
   switch (curve_index) {
   case 0:
      emit LeftCurVal0Changed(svalue);
      break;
   case 1:
      emit LeftCurVal1Changed(svalue);
      break;
   case 2:
      emit LeftCurVal2Changed(svalue);
      break;
   case 3:
      emit LeftCurVal3Changed(svalue);
      break;
   case 4:
      emit LeftCurVal4Changed(svalue);
      break;
   case 5:
      emit LeftCurVal5Changed(svalue);
      break;
   }
}

void CRingGraphic::EmitRightCurValChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue;
   FormatValue(precision, svalue, value);
   switch (curve_index) {
   case 0:
      emit RightCurVal0Changed(svalue);
      break;
   case 1:
      emit RightCurVal1Changed(svalue);
      break;
   case 2:
      emit RightCurVal2Changed(svalue);
      break;
   case 3:
      emit RightCurVal3Changed(svalue);
      break;
   case 4:
      emit RightCurVal4Changed(svalue);
      break;
   case 5:
      emit RightCurVal5Changed(svalue);
      break;
   }
}

void CRingGraphic::EmitYStartChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue;
   FormatValue(precision, svalue, value);
   switch (curve_index) {
   case 0:
      emit YStart0Changed(svalue);
      break;
   case 1:
      emit YStart1Changed(svalue);
      break;
   case 2:
      emit YStart2Changed(svalue);
      break;
   case 3:
      emit YStart3Changed(svalue);
      break;
   case 4:
      emit YStart4Changed(svalue);
      break;
   case 5:
      emit YStart5Changed(svalue);
      break;
   }
}

void CRingGraphic::EmitYEndChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue;
   FormatValue(precision, svalue, value);
   switch (curve_index) {
   case 0:
      emit YEnd0Changed(svalue);
      break;
   case 1:
      emit YEnd1Changed(svalue);
      break;
   case 2:
      emit YEnd2Changed(svalue);
      break;
   case 3:
      emit YEnd3Changed(svalue);
      break;
   case 4:
      emit YEnd4Changed(svalue);
      break;
   case 5:
      emit YEnd5Changed(svalue);
      break;
   }
}

void CRingGraphic::EmitYMinChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue;
   FormatValue(precision, svalue, value);
   switch (curve_index) {
   case 0:
      emit YMin0Changed(svalue);
      break;
   case 1:
      emit YMin1Changed(svalue);
      break;
   case 2:
      emit YMin2Changed(svalue);
      break;
   case 3:
      emit YMin3Changed(svalue);
      break;
   case 4:
      emit YMin4Changed(svalue);
      break;
   case 5:
      emit YMin5Changed(svalue);
      break;
   }
}

void CRingGraphic::EmitYMaxChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue;
   FormatValue(precision, svalue, value);
   switch (curve_index) {
   case 0:
      emit YMax0Changed(svalue);
      break;
   case 1:
      emit YMax1Changed(svalue);
      break;
   case 2:
      emit YMax2Changed(svalue);
      break;
   case 3:
      emit YMax3Changed(svalue);
      break;
   case 4:
      emit YMax4Changed(svalue);
      break;
   case 5:
      emit YMax5Changed(svalue);
      break;
   }
}

double CRingGraphic::GetCurveValue(ULONG_T curve_index, double xpos)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
#ifdef lassma
   if (curve_index < MAX_PROC_CURVES && _CurveBuffer[curve_index] != NULL) {
      cFloatCurve curve(_CurveBuffer[curve_index]);
      ULONG_T value_count = curve.GetValueCount();
      FLOAT_T xval = 0;
      for (ULONG_T i=0; i<value_count; i++) {
         curve.GetXVal(xval, i);
         if (i == value_count) {
            break;
         } else {
            if (xpos < xval) {
               break;
            }
         }
      }
      curve.GetYVal(xval, i);
      return xval;
   }
#endif
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

