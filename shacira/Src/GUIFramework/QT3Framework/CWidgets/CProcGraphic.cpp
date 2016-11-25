
// 21.07.05 HA Methode YSpecification: Include voltage

#include "CProcGraphic.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(AdditionalWidget, \
                   CProcGraphic, \
                   ICON_SET("cgraphic"), \
                   "graphic widget for the display of very special curves in a 2D coordinate system")
#endif

#include "cPaintUtils.h"
#ifndef QT_PLUGIN
#include "System/Structs/cFloatCurve.h"
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

CProcGraphic::CProcGraphic(QWidget * parent, const char * name, WFlags f)
   : QFrame(parent, name, 0),
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
   _Curve5Ref = NULL;
   _Curve5View = NULL;
   ULONG_T i = 0;
   for (i=0; i<MAX_PROC_CURVES; i++) {
      _CurveBuffer[i] = NULL;
      _XScaleEndCurve[i] = 0;
   }
   
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
   _ZoomState=false;

   _LeftCursorGrabbed=false;
   _RightCursorGrabbed=false;
   _GrabPosition = 0; 
   _MoveSelectedCursorValue = false;
}

CProcGraphic::~CProcGraphic() 
{
}

void CProcGraphic::showEvent(QShowEvent * e)
{
   QFrame::showEvent(e);

   emit Refreshed(this);
}

void CProcGraphic::resizeEvent(QResizeEvent * e)
{
//   QFrame::resizeEvent(e);
   InitWidget();
   PaintAll();
}

void CProcGraphic::paintEvent(QPaintEvent * e)
{
   QPainter painter(this);
   bitBlt(this, 0, 0, &_DoubleBuffer);
   PaintCursors(painter);
}

void CProcGraphic::mouseMoveEvent(QMouseEvent * e)
{
   QFrame::mouseMoveEvent(e);
   if (_MoveSelectedCursorValue == true) {
      if((_LeftCursorGrabbed) && (_RightCursorGrabbed)) {
         if(e->pos().x() > _GrabPosition) {
            _LeftCursorGrabbed = false;
         }
         else {
            if(e->pos().x() < _GrabPosition) {
               _RightCursorGrabbed = false;
            }
            else {
               return;// haven't moved yet 
            }
         }
      }
      if(_LeftCursorGrabbed) {
         MoveCursor(LeftCursor, e->pos().x());
      }
      else {
         if(_RightCursorGrabbed) {
            MoveCursor(RightCursor, e->pos().x());
         }
      }
   }
}

void CProcGraphic::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QFrame::mousePressEvent(e);
      if (_MoveSelectedCursorValue == true) {
         if (!_ZoomState) {
            int dxpos_left = abs((long)(e->pos().x() - _LeftCursorPos));
            int dxpos_right = abs((long)(e->pos().x() - _RightCursorPos));
            if(dxpos_left == dxpos_right) { // equidistant between cursors or cursors are at same location
               if(dxpos_left < 10) {
                  // grab both cursors and then let go of one when we see which way we are moving 
                  _LeftCursorGrabbed = true;
                  _RightCursorGrabbed = true;
                  _GrabPosition = e->pos().x(); 
		        }
		     }
            if(dxpos_left < dxpos_right) { // closer to left cursor
               if(dxpos_left < 10) {
                  _LeftCursorGrabbed = true;
                  MoveCursor(LeftCursor, e->pos().x());
		        }
		     }
            else { // closer to right cursor
               if(dxpos_right < 10) {
                  _RightCursorGrabbed = true;
                  MoveCursor(RightCursor, e->pos().x());
		        }
		     }
         }
      }
   }
}

void CProcGraphic::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QFrame::mouseReleaseEvent(e);
      if (_MoveSelectedCursorValue == true) {
         if(_LeftCursorGrabbed) {
		    _LeftCursorGrabbed = false;
            MoveCursor(LeftCursor, e->pos().x());
	     }
         if(_RightCursorGrabbed) {
		    _RightCursorGrabbed = false;
            MoveCursor(RightCursor, e->pos().x());
	     }
      }
   }
}

void CProcGraphic::LeftCursorLeft()
{
   if (_LeftCursorPos > _LeftZoomPos) {
      _LeftCursorPos--;
      double WorldLeftCursorPos=World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()),
             WorldRightCursorPos=World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());

      QString svalue = QString::number(WorldLeftCursorPos, 'f', _XPrecisionValue);
      emit LeftCurXChanged(svalue);

      svalue = QString::number(WorldRightCursorPos - WorldLeftCursorPos, 'f', _XPrecisionValue);
      emit DiffCurXChanged(svalue);
      update();
      EmitAllChanges();
   }
}

void CProcGraphic::LeftCursorRight()
{
   if (_LeftCursorPos < _RightCursorPos) {
      _LeftCursorPos++;
      double WorldLeftCursorPos=World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()),
             WorldRightCursorPos=World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());

      QString svalue = QString::number(WorldLeftCursorPos, 'f', _XPrecisionValue);
      emit LeftCurXChanged(svalue);

      svalue = QString::number(WorldRightCursorPos - WorldLeftCursorPos, 'f', _XPrecisionValue);
      emit DiffCurXChanged(svalue);
      update();
      EmitAllChanges();
   }
}

void CProcGraphic::RightCursorLeft()
{
   if (_RightCursorPos > _LeftCursorPos) {
      _RightCursorPos--;
      double WorldRightCursorPos=World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()),
             WorldLeftCursorPos=World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());

      QString svalue = QString::number(WorldRightCursorPos, 'f', _XPrecisionValue);
      emit RightCurXChanged(svalue);

      svalue = QString::number(WorldRightCursorPos - WorldLeftCursorPos, 'f', _XPrecisionValue);
      emit DiffCurXChanged(svalue);
      update();
      EmitAllChanges();
   }
}

void CProcGraphic::RightCursorRight()
{
   if (_RightCursorPos < _RightZoomPos) {
      _RightCursorPos++;
      double WorldRightCursorPos=World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()),
             WorldLeftCursorPos=World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());

      QString svalue = QString::number(WorldRightCursorPos, 'f', _XPrecisionValue);
      emit RightCurXChanged(svalue);

      svalue = QString::number(WorldRightCursorPos - WorldLeftCursorPos, 'f', _XPrecisionValue);
      emit DiffCurXChanged(svalue);
      update();
      EmitAllChanges();
   }
}

void CProcGraphic::ZoomIn()
{
   _LeftZoomPos = _LeftCursorPos;
   _RightZoomPos = _RightCursorPos;
   QString svalue = QString::number(World(_LeftZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()), 'f', _XPrecisionValue);
   emit XStartChanged(svalue);

   svalue = QString::number(World(_RightZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()), 'f', _XPrecisionValue);
   emit XEndChanged(svalue);
   PaintAll();
}

void CProcGraphic::ZoomOut()
{
   _LeftZoomPos = 0;
   _RightZoomPos = XPIXEL_END();
   QString svalue = QString::number(_XScaleStart, 'f', _XPrecisionValue);
   emit XStartChanged(svalue);

   svalue = QString::number(_XScaleEnd, 'f', _XPrecisionValue);
   emit XEndChanged(svalue);
   PaintAll();
}

void CProcGraphic::ZoomInOut()
{
   if (!_ZoomState) {
	  if(IsZoomEnabled())
	  {
      ZoomIn();
      _ZoomState=true;
	  }
   }
   else {
      ZoomOut();
      _ZoomState=false;
   }
}

// GUI related virtual methods

void CProcGraphic::View()
{
   PaintAll();
}

void CProcGraphic::DelayedLanguageChange()
{
}

// CCS related virtual methods

void CProcGraphic::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_Curve0Spec, _Curve0Ref, _Curve0View, 0);
   CCSInitializeVarRef(_Curve1Spec, _Curve1Ref, _Curve1View, 1);
   CCSInitializeVarRef(_Curve2Spec, _Curve2Ref, _Curve2View, 2);
   CCSInitializeVarRef(_Curve3Spec, _Curve3Ref, _Curve3View, 3);
   CCSInitializeVarRef(_Curve4Spec, _Curve4Ref, _Curve4View, 4);
   CCSInitializeVarRef(_Curve5Spec, _Curve5Ref, _Curve4View, 5);
WMETHOD_VOID_EPILOG
#endif
   setBackgroundMode(Qt::NoBackground);
   InitWidget();
   PaintAll();
}

void CProcGraphic::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
#endif
}

void CProcGraphic::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (id) {
   case 0:
      _CurveBuffer[0] = buf;
      break;
   case 1:
      _CurveBuffer[1] = buf;
      break;
   case 2:
      _CurveBuffer[2] = buf;
      break;
   case 3:
      _CurveBuffer[3] = buf;
      break;
   case 4:
      _CurveBuffer[4] = buf;
      break;
   case 5:
      _CurveBuffer[5] = buf;
      break;
   default: return;
   }

   Notify(VIEW_DATA);
WMETHOD_VOID_EPILOG
#endif
}

void CProcGraphic::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CProcGraphic::PaintAll()
{
   QPainter painter;
   painter.begin(&_DoubleBuffer, this);
   cPaintUtils::SetShape(painter, &_DrawRectangle, paletteBackgroundColor());
   PaintGrid(painter);
   PaintCurves(painter);
   painter.end();
   update();
   EmitAllChanges();
//   emit Refreshed(this);
}

void CProcGraphic::PaintGrid(QPainter & painter)
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

void CProcGraphic::PaintCursors(QPainter & painter)
{
   if (!_CursorValue) {
      return;
   }
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

void CProcGraphic::PaintCurves(QPainter & painter)
{
   ULONG_T i = 0;
   for (i=0; i<MAX_PROC_CURVES; i++) {
      if (_CurveBuffer[i] != NULL) {
         PaintCurve(painter, i);
      }
   }
}

void CProcGraphic::InitWidget()
{
   _DoubleBuffer = QPixmap(size());
   _DrawRectangle.setLeft(0);
   _DrawRectangle.setTop(0);
   _DrawRectangle.setWidth(width());
   _DrawRectangle.setHeight(height());
   _LeftCursorPos = _LeftZoomPos = 0; // 210305 HA change _RightZoomPos to _LefZoomPos
   _RightCursorPos = _RightZoomPos = XPIXEL_END();
}

void CProcGraphic::PaintCurve(QPainter & painter, ULONG_T index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   cFloatCurve curve(_CurveBuffer[index]);
   if (curve.IsValid() == false) return;

   double min = curve.GetMinVal();;
   double max = curve.GetMaxVal();
   ULONG_T value_count = curve.GetValueCount();
   _XScaleStart = curve.GetXScaleStart();
   
   if (curve.GetXScaleEnd() != 0) {
      _XScaleEnd = curve.GetXScaleEnd();
      _XScaleEndCurve[index] = _XScaleEnd;
   }

   if(_XScaleEnd == _XScaleStart) {
      _XScaleEnd = _XScaleStart + 1.0;// To prevent divide by zero
      _XScaleEndCurve[index] = _XScaleEnd;
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
// COMMENTED THE FOLLOWING 2 LINES TO FIX PLOTTNG PROBLEM WHEN DATA EXTENDS BELOW THE EQUATOR  FJC 11-30-05
   //double ynull_correction = 0;
   //SET_Y_NULL_CORRECTION(ynull_correction,yscale_start,yscale_end,0,YPIXEL_END(),_AequatorPos);
#endif
   for (i=0; i<value_count; i++) {
      curve.GetXVal(xval, i);
      curve.GetYVal(yval, i);
      xval = xval - xview_start;
      yval = ywidth - yval + yscale_start;
      xval = Pixel(xval, xview_start, xview_end, 0, XPIXEL_END());
// ADDED/CHANGED THE FOLLOWING TO FIX PLOTTNG PROBLEM WHEN DATA EXTENDS BELOW THE EQUATOR  FJC 11-30-05
      if (_AequatorValue != 0) {
         yval = Pixel(yval, yscale_start, yscale_end, 0, _AequatorPos);
	   }
	   else {
         yval = Pixel(yval, yscale_start, yscale_end, 0, YPIXEL_END());
	   }
      if (_NullMeridianValue != 0) {
#ifdef USE_MACROS
         SET_X_ZERO_VALUE(xval,xnull_correction,0,XPIXEL_END(),_NullMeridianPos);
#else
         xval = XZero(xval, _XScaleStart, _XScaleEnd, 0, XPIXEL_END(), _NullMeridianPos);
#endif
      }
      point.setX(xval);
// COMMENTED THE FOLLOWING TO FIX PLOTTNG PROBLEM WHEN DATA EXTENDS BELOW THE EQUATOR  FJC 11-30-05
/*      if (_AequatorValue != 0) {
#ifdef USE_MACROS
         SET_Y_ZERO_VALUE(yval,ynull_correction,0,YPIXEL_END(),_AequatorPos);
#else
         yval = YZero(yval, yscale_start, yscale_end, 0, YPIXEL_END(), _AequatorPos);
#endif
      }*/
      point.setY(yval);
      point_array.setPoint(i, point);
   }
   painter.drawPolyline(point_array);
   QWMatrix identity;
   painter.setWorldMatrix(identity);
WMETHOD_VOID_EPILOG
#endif
}

QColor CProcGraphic::CurveColor(ULONG_T index)
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

void CProcGraphic::EmitAllChanges()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG

   emit Refreshed(this);
   return;

#ifdef lassma
   ULONG_T i = 0;
   for (i=0; i<MAX_PROC_CURVES; i++) {
      if (_CurveBuffer[i] != NULL) {
         cFloatCurve curve(_CurveBuffer[i]);
         if (curve.IsValid() == false) return;

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
         double WorldLeftCursorPos=World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()),
                WorldRightCursorPos=World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());

         QString svalue = QString::number(World(_LeftZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()), 'f', _XPrecisionValue);
         emit XStartChanged(svalue);

         svalue = QString::number(World(_RightZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()), 'f', _XPrecisionValue);
         emit XEndChanged(svalue);

         svalue = QString::number(WorldLeftCursorPos, 'f', _XPrecisionValue);
         emit LeftCurXChanged(svalue);

         svalue = QString::number(WorldRightCursorPos, 'f', _XPrecisionValue);
         emit RightCurXChanged(svalue);

         svalue = QString::number(WorldRightCursorPos - WorldLeftCursorPos, 'f', _XPrecisionValue);
         emit DiffCurXChanged(svalue);
      }
   }
#endif

WMETHOD_VOID_EPILOG
#endif
}

void CProcGraphic::EmitLeftCurValChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue = QString::number(value, 'f', precision);
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

void CProcGraphic::EmitRightCurValChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue = QString::number(value, 'f', precision);
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

void CProcGraphic::EmitYStartChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue = QString::number(value, 'f', precision);
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

void CProcGraphic::EmitYEndChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue = QString::number(value, 'f', precision);
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

void CProcGraphic::EmitYMinChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue = QString::number(value, 'f', precision);
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

void CProcGraphic::EmitYMaxChanged(ULONG_T curve_index, ULONG_T precision, double value)
{
   QString svalue = QString::number(value, 'f', precision);
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

double CProcGraphic::GetCurveValue(ULONG_T curve_index, double xpos)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index)) {
      cFloatCurve curve(_CurveBuffer[curve_index]);
      if (curve.IsValid() == false) return 0;

      BOOL_T xact_x_match = false;
      ULONG_T value_count = curve.GetValueCount();
      FLOAT_T xval = 0;
      FLOAT_T yval = 0;
      ULONG_T i = 0;
      for (i=0; i<value_count; i++) {
         curve.GetXVal(xval, i);
         if (xpos == xval) {
            xact_x_match = true;
            break;
         } else if (xpos < xval) {
            if (i > 0) {
               i--;
            }
            break;
         }
      }
      if (i == value_count) {
         i--;
      }
      curve.GetYVal(yval, i);
#define LINEAR_STEP_INTERPOLATION
#ifdef LINEAR_STEP_INTERPOLATION
      if (xact_x_match) {
         return yval;
      } else {
         if (i < value_count - 1) {
            DOUBLE_T yval1 = yval;
            curve.GetYVal(yval, i + 1);
            DOUBLE_T yval2 = yval;
            DOUBLE_T dy = yval2 - yval1;
            if (dy == 0) {
               return yval1;
            } else {
               FLOAT_T xval1 = 0;
               FLOAT_T xval2 = 0;
               curve.GetXVal(xval1, i);
               curve.GetXVal(xval2, i + 1);
               DOUBLE_T dx = xval2 - xval1;
               if (dx == 0) {
                  return yval1;
               } else {
                  DOUBLE_T comp_yval = yval1;
                  DOUBLE_T m = dy / dx;
                  DOUBLE x_dist = xpos -  xval1;
                  comp_yval += x_dist * m;
                  return comp_yval;
               }
            }
         }
      }
#endif
      return yval;
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

#ifdef OBSOLETE

QString CProcGraphic::YEnd(int curve_index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index)) {
      cFloatCurve curve(_CurveBuffer[curve_index]);
      if (curve.IsValid() == false) return "?";

      ULONG_T precision = curve.GetYPrecision();
      double value = curve.GetMaxVal();
      QString svalue = QString::number(value, 'f', precision);
      return svalue;
   } else {
      return "??";
   }
WMETHOD_RC_EPILOG("")
#endif
   return "";
}

#endif

BOOL_T CProcGraphic::XDimension(QString & value)
{
#ifndef QT_PLUGIN
#endif
   return false;
}

BOOL_T CProcGraphic::XSpecification(QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString dim_val;
   if (XDimension(dim_val)) {
      if (_stricmp(CONST_STRING(dim_val), "sec") == 0) {
         value = "t";
      } else if (_stricmp(CONST_STRING(dim_val), "mm") == 0) {
         value = "s";
      } else if (_stricmp(CONST_STRING(dim_val), "bar") == 0) {
         value = "ph";
      } else if (_stricmp(CONST_STRING(dim_val), "mm/s") == 0) {
         value = "v";
      } else {
         value = "?";
      }
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::XScaleStart(QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   DOUBLE_T dval = _XScaleStart;
   value = QString::number(dval, 'f', _XPrecisionValue);
   return true;
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::XScaleStart(DOUBLE_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   value = _XScaleStart;
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::XScaleEnd(QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   DOUBLE_T dval = _XScaleEnd;
   value = QString::number(dval, 'f', _XPrecisionValue);
   return true;
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::XScaleEnd(DOUBLE_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   value = _XScaleEnd;
   return true;
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::XScaleEnd(int curve_index, QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (curve_index < MAX_PROC_CURVES) {
      DOUBLE_T dval = _XScaleEndCurve[curve_index];
      value = QString::number(dval, 'f', _XPrecisionValue);
      return true;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::XScaleEnd(int curve_index, DOUBLE_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (curve_index < MAX_PROC_CURVES) {
      value = _XScaleEndCurve[curve_index];
      return true;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::CursorPosition(Cursors cursor, QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   DOUBLE_T dval = 0;
   if (CursorPosition(cursor, dval)) {
      value = QString::number(dval, 'f', _XPrecisionValue);
      return true;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::CursorPosition(Cursors cursor, DOUBLE_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (cursor) {
   case LeftCursor:
      value = World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());
      return true;
   case RightCursor:
      value = World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END());
      return true;
   case CursorDistance:
      if(_XScaleStart > _XScaleEnd)// inverted X axis 
	  {
         value = World((_RightCursorPos - _LeftCursorPos), _XScaleEnd, _XScaleStart, 0, XPIXEL_END());
	  }
	  else
	  {
         value = World((_RightCursorPos - _LeftCursorPos), _XScaleStart, _XScaleEnd, 0, XPIXEL_END());
	  }
      return true;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::YDimension(int curve_index, QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   value = curve.GetYDim();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::YSpecification(int curve_index, QString & value)
{
/// PR 12.03 neu >>>
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      value = "";
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   ULONG_T curve_id = curve.GetCurveId();
   if (curve_id == 3) {
      value = "pi";
      return true;
   }
   QString dim_val = curve.GetYDim();
   if (_stricmp(CONST_STRING(dim_val), "mm") == 0) {
      value = "s";
   } else if (_stricmp(CONST_STRING(dim_val), "bar") == 0) {
      value = "ph";
   } else if (_stricmp(CONST_STRING(dim_val), "mm/s") == 0) {
      value = "v";
   } else if (_stricmp(CONST_STRING(dim_val), "V") == 0) {
      value = "U";
   } else {
      value = "?";
   }
   WMETHOD_RC_EPILOG(false)
#endif
   return false;
/// PR 12.03 neu <<<
}

BOOL_T CProcGraphic::YScaleStart(int curve_index, QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   ULONG_T precision = curve.GetYPrecision();
   DOUBLE_T dval = curve.GetYScaleStart();
   value = QString::number(dval, 'f', precision);
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::YScaleStart(int curve_index, DOUBLE_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   value = curve.GetYScaleStart();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::YScaleEnd(int curve_index, QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   ULONG_T precision = curve.GetYPrecision();
   DOUBLE_T dval = curve.GetYScaleEnd();
   value = QString::number(dval, 'f', precision);
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::YScaleEnd(int curve_index, DOUBLE_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   value = curve.GetYScaleEnd();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::Min(int curve_index, QString & value, BOOL_T restrict_to_view)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   ULONG_T precision = curve.GetYPrecision();
   DOUBLE_T dval = curve.GetMinVal();
   value = QString::number(dval, 'f', precision);
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::Min(int curve_index, DOUBLE_T & value, BOOL_T restrict_to_view)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   value = curve.GetMinVal();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::Max(int curve_index, QString & value, BOOL_T restrict_to_view)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   ULONG_T precision = curve.GetYPrecision();
   DOUBLE_T dval = curve.GetMaxVal();
   value = QString::number(dval, 'f', precision);
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::Max(int curve_index, DOUBLE_T & value, BOOL_T restrict_to_view)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   value = curve.GetMaxVal();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::CursorValue(int curve_index, Cursors cursor, QString & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   ULONG_T precision = curve.GetYPrecision();
   DOUBLE_T dval = 0;
   if (CursorValue(curve_index, cursor, dval)) {
      value = QString::number(dval, 'f', precision);
      return true;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::CursorValue(int curve_index, Cursors cursor, DOUBLE_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   if (cursor == LeftCursor) {
      DOUBLE_T left_value = GetCurveValue(curve_index, World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
      value = left_value;
      return true;
   } else if (cursor == RightCursor) {
      DOUBLE_T right_value = GetCurveValue(curve_index, World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
      value = right_value;
      return true;
   } else if (cursor == CursorDistance) {
      DOUBLE_T left_value = GetCurveValue(curve_index, World(_LeftCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
      DOUBLE_T right_value = GetCurveValue(curve_index, World(_RightCursorPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()));
      value = right_value - left_value;
      return true;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::CurveColor(int curve_index, QColor & color)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }

   switch (curve_index) {
   case 0: color = _Curve0ColorValue; break;
   case 1: color = _Curve1ColorValue; break;
   case 2: color = _Curve2ColorValue; break;
   case 3: color = _Curve3ColorValue; break;
   case 4: color = _Curve4ColorValue; break;
   case 5: color = _Curve5ColorValue; break;
   default: color = Qt::black;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::CurveExists(int curve_index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (curve_index < 0 || curve_index >= MAX_PROC_CURVES ||
       _CurveBuffer[curve_index] == NULL) {
      return false;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::Function(int curve_index, ULONG_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   value = curve.GetFunction();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}


BOOL_T CProcGraphic::FunctionUnit(int curve_index, ULONG_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   value = curve.GetFunctionUnit();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::CurveId(int curve_index, ULONG_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   value = curve.GetCurveId();
   if(value != 0) return true;
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CProcGraphic::MoveCursor(Cursors cursor, Directions direction, int steps)
{
   switch (cursor) {
   case LeftCursor:
      switch (direction) {
      case LeftDirection:
         LeftCursorLeft();
         return true;
      case RightDirection:
         LeftCursorRight();
         return true;
      }
      break;
   case RightCursor:
      switch (direction) {
      case LeftDirection:
         RightCursorLeft();
         return true;
      case RightDirection:
         RightCursorRight();
         return true;
      }
      break;
   }
   return false;
}

BOOL_T CProcGraphic::MoveCursor(Cursors cursor, int new_xpos)
{
   ULONG_T NewXpos = (ULONG_T)new_xpos;  
   if(new_xpos < 0)NewXpos = 0;

   switch (cursor) 
   {
      case LeftCursor:
		 {
            if(NewXpos > _LeftCursorPos)
			{
               if(NewXpos >= _RightCursorPos) _LeftCursorPos = _RightCursorPos - 1;
			   else _LeftCursorPos = NewXpos - 1;
               LeftCursorRight();
			}
			else 
            if(NewXpos < _LeftCursorPos)
			{
               if(NewXpos <= _LeftZoomPos) _LeftCursorPos = _LeftZoomPos + 1;
			   else _LeftCursorPos = NewXpos + 1;
               LeftCursorLeft();
			}
			return true;
		 }
      case RightCursor:
		 {
            if(NewXpos < _RightCursorPos)
			{
               if(NewXpos <= _LeftCursorPos) _RightCursorPos = _LeftCursorPos + 1;
			   else _RightCursorPos = NewXpos + 1;
               RightCursorLeft();
			}
			else 
            if(NewXpos > _RightCursorPos)
			{
               if(NewXpos >= _RightZoomPos) _RightCursorPos = _RightZoomPos - 1;
			   else _RightCursorPos = NewXpos - 1;
               RightCursorRight();
			}
			return true;
		 }
   }
   return false;
}
BOOL_T CProcGraphic::Zoom()
{
   ZoomInOut();
   return true;
}

// Start 210305 HA
BOOL_T CProcGraphic::SetCursorsAtBeginnAndEnd()
{
   _LeftCursorPos = _LeftZoomPos = 0; 
   _RightCursorPos = _RightZoomPos = XPIXEL_END();

   QString svalue = QString::number(World(_LeftZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()), 'f', _XPrecisionValue);
   emit XStartChanged(svalue);

   svalue = QString::number(World(_RightZoomPos, _XScaleStart, _XScaleEnd, 0, XPIXEL_END()), 'f', _XPrecisionValue);
   emit XEndChanged(svalue);
   PaintAll();

   return true;
}
// End 210305 HA

BOOL_T CProcGraphic::SetYScaleEnd(int curve_index, QString value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;
   FLOAT_T dval = atof(CONST_STRING(value));
   if(curve.GetYScaleEnd() != dval)
   {
      ULONG_T precision = curve.GetYPrecision();
      curve.SetYScaleEnd(dval);
      EmitYEndChanged(curve_index, precision, dval);
   }
   PaintAll();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CProcGraphic::SetYScaleEnd(int curve_index, DOUBLE_T value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (CurveExists(curve_index) == false) {
      return false;
   }
   cFloatCurve curve(_CurveBuffer[curve_index]);
   if (curve.IsValid() == false) return false;

   if(curve.GetYScaleEnd() != value)
   {
      ULONG_T precision = curve.GetYPrecision();
      curve.SetYScaleEnd(value);
      EmitYEndChanged(curve_index, precision, value);
   }
   PaintAll();
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}


// this method get the Object valid of the graphic curve
// Start 210305 HA
BOOL_T CProcGraphic::GetObjectValid(int curve_index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   cFloatCurve curve(_CurveBuffer[curve_index]);

   return (curve.IsValid());
WMETHOD_RC_EPILOG(false)
#endif
   return (false);
}
// End 210305 HA

BOOL_T CProcGraphic::GetZoomState()
{
	return _ZoomState;
}


BOOL_T CProcGraphic::IsZoomEnabled()
{
   if((_LeftCursorPos == 0) && (_RightCursorPos == (ULONG_T)XPIXEL_END())) return false;

   return true;
}
