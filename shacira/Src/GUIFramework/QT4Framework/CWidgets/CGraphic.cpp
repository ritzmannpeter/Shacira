
#include "CGraphic.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(AdditionalWidget, \
                   CGraphic, \
                   ICON_SET("graphicsview"), \
                   "basic graphic widget for the display of curves in a 2D coordinate system")
#endif

#include "cPaintUtils.h"
#ifndef QT_PLUGIN
#include "System/Structs/cShortCurve.h"
#include "System/Structs/cFloatCurve.h"
#endif
#ifdef QT4
#include <qvector.h>
#include <qpolygon.h>
#else
#include <qvaluevector.h>
#endif

#ifndef _MIN_
#define _MIN_(a,b) (((a)<(b)) ? a : b)
#endif

#ifndef QT_PLUGIN

static void Limits(cFloatCurve & curve, DOUBLE_T & min, DOUBLE_T & max)
{  
   min = 100000;
   max = -100000;
   FLOAT_T value = 0;
   ULONG_T value_count = curve.GetValueCount();
   for (ULONG_T i=0; i<value_count; i++) {
      curve.GetYVal(value, i);
      if (value < min) {
         min = value;
      }
      if (value > max) {
         max = value;
      }
   }
}

#endif

CGraphic::CGraphic(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f) :
        CCoordSystem(parent, name, 0)
{
   _LeftCursorRef = NULL;
   _LeftCursorView = NULL;
   _RightCursorRef = NULL;
   _RightCursorView = NULL;

   _Y0MinRef = NULL;
   _Y0MinView = NULL;
   _Y1MinRef = NULL;
   _Y1MinView = NULL;
   _Y2MinRef = NULL;
   _Y2MinView = NULL;
   _Y3MinRef = NULL;
   _Y3MinView = NULL;
   _Y4MinRef = NULL;
   _Y4MinView = NULL;
   _Y0MaxRef = NULL;
   _Y0MaxView = NULL;
   _Y1MaxRef = NULL;
   _Y1MaxView = NULL;
   _Y2MaxRef = NULL;
   _Y2MaxView = NULL;
   _Y3MaxRef = NULL;
   _Y3MaxView = NULL;
   _Y4MaxRef = NULL;
   _Y4MaxView = NULL;
   
   _Curve0Ref = NULL;
   _Curve0View = NULL;
   _Curve1Ref = NULL;
   _Curve1View = NULL;
   _Curve2Ref = NULL;
   _Curve2View = NULL;
   _Curve3Ref = NULL;
   _Curve3View = NULL;
   _Curve4Ref = NULL;
   _Curve4View = NULL;

   for (ULONG_T i=0; i<MAX_CURVES; i++) {
      _YMin[i] = 0;
      _YMax[i] = 200;
      _CurveBuffer[i] = NULL;
   }
   
   _LeftCursorPos = _XMinValue;
   _RightCursorPos = _XMaxValue;
   
   _Curve0ColorValue = Qt::gray;
   _Curve1ColorValue = Qt::gray;
   _Curve2ColorValue = Qt::gray;
   _Curve3ColorValue = Qt::gray;
   _Curve4ColorValue = Qt::gray;
   _CurveCount = 0;
}

CGraphic::~CGraphic() 
{
}

void CGraphic::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CCoordSystem::mousePressEvent(e);
   }
}

void CGraphic::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      CCoordSystem::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CGraphic::View()
{
   PaintIt();
}

void CGraphic::DelayedLanguageChange()
{
   PaintIt();
}

// CCS related virtual methods

void CGraphic::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCoordSystem::CCSSetContext(node, context);
   CCSInitializeVarRef(_LeftCursorSpec, _LeftCursorRef, _LeftCursorView, 4);
   CCSInitializeVarRef(_RightCursorSpec, _RightCursorRef, _RightCursorView, 5);
   CCSInitializeVarRef(_Y0MinSpec, _Y0MinRef, _Y0MinView, 6);
   CCSInitializeVarRef(_Y1MinSpec, _Y1MinRef, _Y1MinView, 7);
   CCSInitializeVarRef(_Y2MinSpec, _Y2MinRef, _Y2MinView, 8);
   CCSInitializeVarRef(_Y3MinSpec, _Y3MinRef, _Y3MinView, 9);
   CCSInitializeVarRef(_Y4MinSpec, _Y4MinRef, _Y4MinView, 10);
   CCSInitializeVarRef(_Y0MaxSpec, _Y0MaxRef, _Y0MaxView, 11);
   CCSInitializeVarRef(_Y1MaxSpec, _Y1MaxRef, _Y1MaxView, 12);
   CCSInitializeVarRef(_Y2MaxSpec, _Y2MaxRef, _Y2MaxView, 13);
   CCSInitializeVarRef(_Y3MaxSpec, _Y3MaxRef, _Y3MaxView, 14);
   CCSInitializeVarRef(_Y4MaxSpec, _Y4MaxRef, _Y4MaxView, 15);
   CCSInitializeVarRef(_Curve0Spec, _Curve0Ref, _Curve0View, 16);
   CCSInitializeVarRef(_Curve1Spec, _Curve1Ref, _Curve1View, 17);
   CCSInitializeVarRef(_Curve2Spec, _Curve2Ref, _Curve2View, 18);
   CCSInitializeVarRef(_Curve3Spec, _Curve3Ref, _Curve3View, 19);
   CCSInitializeVarRef(_Curve4Spec, _Curve4Ref, _Curve4View, 20);
   _CurveCount = CurveCount();
WMETHOD_VOID_EPILOG
#endif
}

void CGraphic::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                           UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (id) {
   case 0:
   case 1:
   case 2:
   case 3:
      CCoordSystem::CCSNewValue(value, id, time_offset, data_type, size);
      return;
   case 4:
   {
      QString qValue = value;
      _LeftCursorPos = qValue.toDouble();
      break;
   }
   case 5:
   {
      QString qValue = value;
      _RightCursorPos = qValue.toDouble();
      break;
   }
   case 6:
   {
      QString qValue = value;
      _YMin[0] = qValue.toDouble();
      break;
   }
   case 7:
   {
      QString qValue = value;
      _YMin[1] = qValue.toDouble();
      break;
   }
   case 8:
   {
      QString qValue = value;
      _YMin[2] = qValue.toDouble();
      break;
   }
   case 9:
   {
      QString qValue = value;
      _YMin[3] = qValue.toDouble();
      break;
   }
   case 10:
   {
      QString qValue = value;
      _YMin[4] = qValue.toDouble();
      break;
   }
   case 11:
   {
      QString qValue = value;
      _YMax[0] = qValue.toDouble();
      break;
   }
   case 12:
   {
      QString qValue = value;
      _YMax[1] = qValue.toDouble();
      break;
   }
   case 13:
   {
      QString qValue = value;
      _YMax[2] = qValue.toDouble();
      break;
   }
   case 14:
   {
      QString qValue = value;
      _YMax[3] = qValue.toDouble();
      break;
   }
   case 15:
   {
      QString qValue = value;
      _YMax[4] = qValue.toDouble();
      break;
   }
   default: return;
   }
   Notify(VIEW_DATA);
WMETHOD_VOID_EPILOG
#endif
}

void CGraphic::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                           UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (id) {
   case 16:
      _CurveBuffer[0] = buf;
      break;
   case 17:
      _CurveBuffer[1] = buf;
      break;
   case 18:
      _CurveBuffer[2] = buf;
      break;
   case 19:
      _CurveBuffer[3] = buf;
      break;
   case 20:
      _CurveBuffer[4] = buf;
      break;
   default: return;
   }
   Notify(VIEW_DATA);
WMETHOD_VOID_EPILOG
#endif
}

void CGraphic::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CGraphic::PaintCurves(QPainter & painter)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   for (ULONG_T i=0; i<MAX_CURVES; i++) {
      if (_CurveBuffer[i] != NULL) {
         PaintCurve(painter, i);
      }
   }
   PaintCurveLegend(painter);
WMETHOD_VOID_EPILOG
#endif
}

void CGraphic::PaintLegend(QPainter & painter)
{
#define WIDTH_CORRECTION   5
#define HEIGHT_CORRECTION   5
#ifdef VISU_TEST
   return;
#endif
   ExtendGrid(painter);
   FormatLegendText();
   QFont w_font = font();
   int font_size = w_font.pointSize();
   _XLeftRectangle = QRect(_XAxisRectangle.left(),
                           _XAxisRectangle.top() + font_size - HEIGHT_CORRECTION,
                           font_size * _XMinString.length() + WIDTH_CORRECTION,
                           font_size);
   _XRightRectangle = QRect(_XAxisRectangle.right() - (font_size * _XMaxString.length()),
                            _XAxisRectangle.top() + font_size - HEIGHT_CORRECTION,
                            font_size * _XMaxString.length() + WIDTH_CORRECTION,
                            font_size);
   _XMidRectangle = QRect(_XAxisRectangle.right() - (_XAxisRectangle.width() / 2),
                          _XAxisRectangle.top() + font_size - HEIGHT_CORRECTION,
                          font_size * _XUnitValue.length() + WIDTH_CORRECTION,
                          font_size);
   painter.setPen(_LegendColorValue);
   int flags = Qt::AlignHCenter | Qt::AlignVCenter;
   painter.drawText(_XLeftRectangle, flags, _XMinString);
   painter.drawText(_XMidRectangle, flags, _XUnitValue);
   painter.drawText(_XRightRectangle, flags, _XMaxString);
}

void CGraphic::PaintCurveLegend(QPainter & painter)
{
   QFont w_font = font();
   int font_size = w_font.pointSize() + 5;
   painter.setFont(w_font);
   ULONG_T unit_pos = _YAxisRectangle.top() - 5;
   ULONG_T scale_end_pos = unit_pos + font_size;
   ULONG_T max_pos = scale_end_pos + font_size + 5;
   ULONG_T min_pos = _YAxisRectangle.bottom() - font_size;
   ULONG_T scale_start_pos = _XAxisRectangle.bottom() - font_size;
   ULONG_T x_start[MAX_CURVES] = {0};
   if (_CurveCount == 0) return;
   ULONG_T x_dist = _YAxisRectangle.width() / _CurveCount;
   x_start[0] = _YAxisRectangle.left();
   if (_CurveCount == 1) {
   } else if (_CurveCount == 2) {
      x_start[1] = x_start[0] + x_dist;
   } else if (_CurveCount == 3) {
      x_start[1] = x_start[0] + x_dist;
      x_start[2] = x_start[0] + (2 * x_dist);
      QRect rect;

      rect.setTop(unit_pos);
      rect.setBottom(max_pos);
      rect.setLeft(x_start[0]);
      rect.setRight(x_start[1]);
      PaintText(painter, rect, _Curve0ColorValue, _Y0UnitValue);
      rect.setLeft(x_start[1]);
      rect.setRight(x_start[2]);
      PaintText(painter, rect, _Curve1ColorValue, _Y1UnitValue);
      rect.setLeft(x_start[2]);
      rect.setRight(x_start[2] + x_dist);
      PaintText(painter, rect, _Curve2ColorValue, _Y2UnitValue);

      rect.setTop(scale_end_pos);
      rect.setBottom(scale_end_pos + font_size);
      rect.setLeft(x_start[0]);
      rect.setRight(x_start[1]);
      PaintText(painter, rect, _Curve0ColorValue, _YScaleEndString[0]);
      rect.setLeft(x_start[1]);
      rect.setRight(x_start[2]);
      PaintText(painter, rect, _Curve1ColorValue, _YScaleEndString[1]);
      rect.setLeft(x_start[2]);
      rect.setRight(x_start[2] + x_dist);
      PaintText(painter, rect, _Curve2ColorValue, _YScaleEndString[2]);

      rect.setTop(max_pos);
      rect.setBottom(max_pos + font_size);
      rect.setLeft(x_start[0]);
      rect.setRight(x_start[1]);
      PaintText(painter, rect, _Curve0ColorValue, _YMaxString[0]);
      rect.setLeft(x_start[1]);
      rect.setRight(x_start[2]);
      PaintText(painter, rect, _Curve1ColorValue, _YMaxString[1]);
      rect.setLeft(x_start[2]);
      rect.setRight(x_start[2] + x_dist);
      PaintText(painter, rect, _Curve2ColorValue, _YMaxString[2]);

      rect.setTop(min_pos);
      rect.setBottom(min_pos + font_size);
      rect.setLeft(x_start[0]);
      rect.setRight(x_start[1]);
      PaintText(painter, rect, _Curve0ColorValue, _YMinString[0]);
      rect.setLeft(x_start[1]);
      rect.setRight(x_start[2]);
      PaintText(painter, rect, _Curve1ColorValue, _YMinString[1]);
      rect.setLeft(x_start[2]);
      rect.setRight(x_start[2] + x_dist);
      PaintText(painter, rect, _Curve2ColorValue, _YMinString[2]);

      rect.setTop(scale_start_pos);
      rect.setBottom(scale_start_pos + font_size);
      rect.setLeft(x_start[0]);
      rect.setRight(x_start[1]);
      PaintText(painter, rect, _Curve0ColorValue, _YScaleStartString[0]);
      rect.setLeft(x_start[1]);
      rect.setRight(x_start[2]);
      PaintText(painter, rect, _Curve1ColorValue, _YScaleStartString[1]);
      rect.setLeft(x_start[2]);
      rect.setRight(x_start[2] + x_dist);
      PaintText(painter, rect, _Curve2ColorValue, _YScaleStartString[2]);

   } else if (_CurveCount == 4) {
      x_start[1] = x_start[0] + x_dist;
      x_start[2] = x_start[0] + (2 * x_dist);
      x_start[3] = x_start[0] + (3 * x_dist);
   } else if (_CurveCount == 5) {
      x_start[1] = x_start[0] + x_dist;
      x_start[2] = x_start[0] + (2 * x_dist);
      x_start[3] = x_start[0] + (3 * x_dist);
      x_start[4] = x_start[0] + (4 * x_dist);
   }
   
}

void CGraphic::PaintText(QPainter & painter, QRect & rect, QColor color, QString & text)
{
   int flags = Qt::AlignLeft | Qt::AlignTop;
   painter.setPen(color);
   painter.drawText(rect, flags, text);
//   cPaintUtils::SetBox(painter, &rect, Qt::red);
}

void CGraphic::PaintCurve(QPainter & painter, ULONG_T index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   USHORT_T precision_factor = 100;
   cFloatCurve curve(_CurveBuffer[index]);
   double xwidth = curve.GetXScaleEnd() - curve.GetXScaleStart();
_XMaxValue = curve.GetXScaleEnd();
   double yscale_start = curve.GetYScaleStart();
   double yscale_end = curve.GetYScaleEnd();
   double ywidth = yscale_end - yscale_start;
double min = 0;
double max = 0;
   Limits(curve, min, max);
   FormatYScale(index, yscale_start, yscale_end, min, max);
   if (ywidth <= 0) return;
   if (xwidth <= 0) return;
   QColor color = CurveColor(index);
   QPen pen = QPen(color, 0);
   painter.setPen(pen);
   ULONG_T count = curve.GetValueCount();
   ULONG_T i = 0;
#ifdef QT4
   QPolygon point_array(count);
#else
   QPointArray point_array(count);
#endif
   QPoint point;
   FLOAT_T xval = 0;
   FLOAT_T yval = 0;
   for (i=0; i<count; i++) {
      curve.GetXVal(xval, i);
      curve.GetYVal(yval, i);
//      yval = ywidth - (yval - yscale_start);
      yval = ywidth - yval;
      point.setX((int)(xval*precision_factor));
      point.setY((int)(yval*precision_factor));
      point_array.setPoint(i, point);
   }
   double x_factor = (double)(_CurveRectangle.width()) / (xwidth*precision_factor);
   double y_factor = (double)(_CurveRectangle.height()) / (ywidth*precision_factor);
#ifdef QT4
   QMatrix matrix(x_factor, 0, 0, y_factor, _CurveRectangle.left(), _CurveRectangle.top());
#else
   QWMatrix matrix(x_factor, 0, 0, y_factor, _CurveRectangle.left(), _CurveRectangle.top());
#endif
   painter.setWorldMatrix(matrix);
   painter.drawPolyline(point_array);
#ifdef QT4
   QMatrix identity;
#else
   QWMatrix identity;
#endif
   painter.setWorldMatrix(identity);
WMETHOD_VOID_EPILOG
#endif
}

QColor CGraphic::CurveColor(ULONG_T index)
{
   switch (index) {
   case 0: return _Curve0ColorValue;
   case 1: return _Curve1ColorValue;
   case 2: return _Curve2ColorValue;
   case 3: return _Curve3ColorValue;
   case 4: return _Curve4ColorValue;
   }
   return Qt::gray;
}

void CGraphic ::FormatYScale(ULONG_T index,
                             DOUBLE_T yscale_start, DOUBLE_T yscale_end,
                             DOUBLE_T min, DOUBLE_T max)
{
   ULONG_T precision = 0;
   if (index == 0) {
      precision = 0;
   } else if (index == 1) {
      precision = 1;
   } else if (index == 2) {
      precision = 1;
   }
   FormatValue(precision, _YScaleStartString[index], yscale_start);
   FormatValue(precision, _YScaleEndString[index], yscale_end);
   FormatValue(precision, _YMinString[index], min);
   FormatValue(precision, _YMaxString[index], max);
}

void CGraphic::FormatValue(ULONG_T precision, QString & text, DOUBLE_T value)
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

void CGraphic::ExtendGrid(QPainter & painter)
{
   QPen pen = QPen(_GridColorValue, 0);
   painter.setPen(pen);
   ULONG_T i = 0;

   ULONG_T x_pos = 0;
   ULONG_T x_size = _XAxisRectangle.width();
   ULONG_T x_steps = _MIN_(_XStepsValue + 1, MAX_SCALE_STEPS);
   ULONG_T y_start = _XAxisRectangle.top();
   ULONG_T y_end = _XAxisRectangle.bottom();
   for (i=0; i<x_steps; i++) {
      if (i > 0) {
         x_pos = _XGrainPos[i];
         painter.drawLine(x_pos, y_start, x_pos, y_end);
      }
   }

   ULONG_T y_dist = _YGrainPos[0] - _YGrainPos[1];
   ULONG_T x_start = _XAxisRectangle.left();
   ULONG_T x_end = _XAxisRectangle.right();
   ULONG_T y_max = _XAxisRectangle.bottom();
   ULONG_T y_pos = _XAxisRectangle.top() + y_dist;
   while (y_pos < y_max - 2) {
      painter.drawLine(x_start, y_pos, x_end, y_pos);
      y_pos += y_dist;
   }
   y_pos = _XAxisRectangle.bottom();
   painter.drawLine(x_start, y_pos, x_end, y_pos);

   pen = QPen(_AxisColorValue, 0);
   painter.setPen(pen);
   x_pos = _XAxisRectangle.left();
   painter.drawLine(x_pos, y_start, x_pos, y_end);
   y_pos = _XAxisRectangle.top();
   x_start = _XAxisRectangle.left() - SCALE_GRAIN_SIZE;
   x_end = _XAxisRectangle.left();
   while (y_pos < y_max - 2) {
      painter.drawLine(x_start, y_pos, x_end, y_pos);
      y_pos += y_dist;
   }
   y_pos = _XAxisRectangle.bottom();
   painter.drawLine(x_start, y_pos, x_end, y_pos);

   y_start = _XAxisRectangle.top() - SCALE_GRAIN_SIZE;
   y_end = _XAxisRectangle.top() + SCALE_GRAIN_SIZE;
   for (i=0; i<x_steps; i++) {
      if (i > 0) {
         x_pos = _XGrainPos[i];
         painter.drawLine(x_pos, y_start, x_pos, y_end);
      }
   }
}

ULONG_T CGraphic::CurveCount()
{
   ULONG_T curve_count = 0;
   if (_Curve0Ref != NULL) curve_count++;
   if (_Curve1Ref != NULL) curve_count++;
   if (_Curve2Ref != NULL) curve_count++;
   if (_Curve3Ref != NULL) curve_count++;
   if (_Curve4Ref != NULL) curve_count++;
   return curve_count;
}

