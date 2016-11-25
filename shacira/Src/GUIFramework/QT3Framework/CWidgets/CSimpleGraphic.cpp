

// PR 07.04.05 - optimized screen representation for very small values

#include "cPaintUtils.h"
#include "CSimpleGraphic.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(AdditionalWidget,
                   CSimpleGraphic, \
                   ICON_SET("cgraphic"), \
                   "simple graphic widget for the display of curves in a 2D coordinate system")
#endif

CSimpleGraphic::CSimpleGraphic(QWidget * parent, const char * name, WFlags f)
   : CCoordSystem(parent, name, 0)
{
   _XCountRef = NULL;
   _XCountView = NULL;
   _XMaxRef = NULL;
   _XMaxView = NULL;
   _YMaxRef = NULL;
   _YMaxView = NULL;
   
   _X0Ref = NULL;
   _X0View = NULL;
   _X1Ref = NULL;
   _X1View = NULL;
   _X2Ref = NULL;
   _X2View = NULL;
   _X3Ref = NULL;
   _X3View = NULL;
   _X4Ref = NULL;
   _X4View = NULL;
   _X5Ref = NULL;
   _X5View = NULL;
   _X6Ref = NULL;
   _X6View = NULL;
   _X7Ref = NULL;
   _X7View = NULL;
   _X8Ref = NULL;
   _X8View = NULL;
   _X9Ref = NULL;
   _X9View = NULL;

   _Y0Ref = NULL;
   _Y0View = NULL;
   _Y1Ref = NULL;
   _Y1View = NULL;
   _Y2Ref = NULL;
   _Y2View = NULL;
   _Y3Ref = NULL;
   _Y3View = NULL;
   _Y4Ref = NULL;
   _Y4View = NULL;
   _Y5Ref = NULL;
   _Y5View = NULL;
   _Y6Ref = NULL;
   _Y6View = NULL;
   _Y7Ref = NULL;
   _Y7View = NULL;
   _Y8Ref = NULL;
   _Y8View = NULL;
   _Y9Ref = NULL;
   _Y9View = NULL;

   _XCount = -1;
   for (ULONG_T i=0; i<MAX_XVALUES; i++) {
      _XValues[i] = 0;
      _YValues[i] = 0;
   }

   _CurveColorValue = Qt::gray;
   _ViewModeValue = Steps;
}

CSimpleGraphic::~CSimpleGraphic() 
{
}

void CSimpleGraphic::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CCoordSystem::mousePressEvent(e);
   }
}

void CSimpleGraphic::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
#ifdef lassma
      CCoordSystem::mouseReleaseEvent(e);
      if (_ViewModeValue == Ramps) {
         _ViewModeValue = Steps;
      } else {
         _ViewModeValue = Ramps;
      }
      PaintIt();
#endif
   }
}

// GUI related virtual methods

void CSimpleGraphic::View()
{
   PaintIt();
}

void CSimpleGraphic::DelayedLanguageChange()
{
   PaintIt();
}

// CCS related virtual methods

void CSimpleGraphic::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCoordSystem::CCSSetContext(node, context);
   CCSInitializeVarRef(_XCountSpec, _XCountRef, _XCountView, 4);
   CCSInitializeVarRef(_X0Spec, _X0Ref, _X0View, 5);
   CCSInitializeVarRef(_X1Spec, _X1Ref, _X1View, 6);
   CCSInitializeVarRef(_X2Spec, _X2Ref, _X2View, 7);
   CCSInitializeVarRef(_X3Spec, _X3Ref, _X3View, 8);
   CCSInitializeVarRef(_X4Spec, _X4Ref, _X4View, 9);
   CCSInitializeVarRef(_X5Spec, _X5Ref, _X5View, 10);
   CCSInitializeVarRef(_X6Spec, _X6Ref, _X6View, 11);
   CCSInitializeVarRef(_X7Spec, _X7Ref, _X7View, 12);
   CCSInitializeVarRef(_X8Spec, _X8Ref, _X8View, 13);
   CCSInitializeVarRef(_X9Spec, _X9Ref, _X9View, 14);
   CCSInitializeVarRef(_Y0Spec, _Y0Ref, _Y0View, 15);
   CCSInitializeVarRef(_Y1Spec, _Y1Ref, _Y1View, 16);
   CCSInitializeVarRef(_Y2Spec, _Y2Ref, _Y2View, 17);
   CCSInitializeVarRef(_Y3Spec, _Y3Ref, _Y3View, 18);
   CCSInitializeVarRef(_Y4Spec, _Y4Ref, _Y4View, 19);
   CCSInitializeVarRef(_Y5Spec, _Y5Ref, _Y5View, 20);
   CCSInitializeVarRef(_Y6Spec, _Y6Ref, _Y6View, 21);
   CCSInitializeVarRef(_Y7Spec, _Y7Ref, _Y7View, 22);
   CCSInitializeVarRef(_Y8Spec, _Y8Ref, _Y8View, 23);
   CCSInitializeVarRef(_Y9Spec, _Y9Ref, _Y9View, 24);
   SetXCount();
WMETHOD_VOID_EPILOG
#endif
}

void CSimpleGraphic::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                                 UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   int index = 0;
   switch (id) {
   case 0:
   case 1:
   case 2:
   case 3:
      CCoordSystem::CCSNewValue(value, id, time_offset, data_type, size);
      return;
   case 4:
      _XCount = atol(value);
      break;
   case 5:
      _XValues[0] = atof(value);
      break;
   case 6:
      _XValues[1] = atof(value);
      break;
   case 7:
      _XValues[2] = atof(value);
      break;
   case 8:
      _XValues[3] = atof(value);
      break;
   case 9:
      _XValues[4] = atof(value);
      break;
   case 10:
      _XValues[5] = atof(value);
      break;
   case 11:
      _XValues[6] = atof(value);
      break;
   case 12:
      _XValues[7] = atof(value);
      break;
   case 13:
      _XValues[8] = atof(value);
      break;
   case 14:
      _XValues[9] = atof(value);
      break;
   case 15:
      _YValues[0] = atof(value);
      break;
   case 16:
      _YValues[1] = atof(value);
      break;
   case 17:
      _YValues[2] = atof(value);
      break;
   case 18:
      _YValues[3] = atof(value);
      break;
   case 19:
      _YValues[4] = atof(value);
      break;
   case 20:
      _YValues[5] = atof(value);
      break;
   case 21:
      _YValues[6] = atof(value);
      break;
   case 22:
      _YValues[7] = atof(value);
      break;
   case 23:
      _YValues[8] = atof(value);
      break;
   case 24:
      _YValues[9] = atof(value);
      break;
   }
   Notify(VIEW_DATA);
WMETHOD_VOID_EPILOG
#endif
}

void CSimpleGraphic::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                                 UCHAR_T data_type, ULONG_T size)
{
}

void CSimpleGraphic::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CSimpleGraphic::PaintCurves(QPainter & painter)
{
   if (_XCount == -1) return;

#ifndef QT_PLUGIN
WMETHOD_PROLOG
   DOUBLE_T x_stretch_factor = 100;
   DOUBLE_T y_stretch_factor = 100;
   if (_XMaxValue != 0) {
      x_stretch_factor = _CurveRectangle.width() / _XMaxValue;
   }
   if (_YMaxValue != 0) {
      y_stretch_factor = _CurveRectangle.height() / _YMaxValue;
   }
   QPoint points[MAX_XVALUES*2];
   QPointArray point_array;
   if (_ViewModeValue == Ramps) {
      ULONG_T array_size = _MIN_(_XCount, MAX_XVALUES);
      point_array.resize(array_size);
      for (ULONG_T i=0; i<array_size; i++) {
         points[i].setX(_XValues[i]);
         points[i].setY(_YMaxValue - _YValues[i]);
         point_array.setPoint(i, points[i]);
      }
   } 
   else if ((_ViewModeValue == Steps) || 
            (_ViewModeValue == StepsStartAtXMin)) {
      ULONG_T i = 0;
      DOUBLE_T temp_xvalues[MAX_XVALUES] = {0};
      DOUBLE_T temp_yvalues[MAX_XVALUES] = {0};
      for (i=0; i<(ULONG_T)_XCount; i++) {
         if (_ViewModeValue == StepsStartAtXMin) {
            if (_SystemTypeValue == RightBottom ||
               _SystemTypeValue == RightTop ) {
               if (i == 0) {
                  if (_XValues[0] > _XValues[_XCount-1]) {
                     temp_xvalues[i] = _XMaxValue - _XMaxValue;
                  }
                  else {
                     temp_xvalues[i] = _XMaxValue;
                  }
                  temp_yvalues[i] = _YValues[i];
               }
               else {
                  if (_XValues[i-1] && (_XValues[i] == 0)) {
                     return;
                  }
                  temp_xvalues[i] = _XMaxValue - _XValues[i-1];
                  temp_yvalues[i] = _YValues[i];
               }
            } else {
               if (i == 0) {
                  temp_xvalues[i] = _XMinValue;
                  temp_yvalues[i] = _YValues[i];
               }
               else {
                  if (_XValues[i-1] && (_XValues[i] == 0)) {
                     return;
                  }
                  temp_xvalues[i] = _XValues[i-1];
                  temp_yvalues[i] = _YValues[i];
               }
            }
         }
         else {
            if (_SystemTypeValue == RightBottom ||
                _SystemTypeValue == RightTop ) {
               temp_xvalues[i] = _XMaxValue - _XValues[i];
               temp_yvalues[i] = _YValues[i];
            } else {
               temp_xvalues[i] = _XValues[i];
               temp_yvalues[i] = _YValues[i+1];
            }
         }
      }
      ULONG_T array_size = _MIN_(_XCount, MAX_XVALUES) * 2;
      point_array.resize(array_size);
      ULONG_T pi = 0;
      for (i=0; i<array_size/2; i++) {
         points[pi].setX(temp_xvalues[i] * x_stretch_factor);
         points[pi].setY((_YMaxValue - temp_yvalues[i]) * y_stretch_factor);
         point_array.setPoint(pi, points[pi]);
         pi++;        
         if (i == (array_size / 2) - 1) {
            if (i != 0) {
               if (temp_xvalues[i] >= temp_xvalues[i - 1]) {
                  points[pi].setX(_XMaxValue * x_stretch_factor);
               } else {
                  points[pi].setX(_XMinValue * x_stretch_factor);
               }
               points[pi].setY((_YMaxValue - temp_yvalues[i]) * y_stretch_factor);
               point_array.setPoint(pi, points[pi]);
            }
            else {
               if (_SystemTypeValue == RightBottom ||
                  _SystemTypeValue == RightTop ) {
                  if ((_XCount == 1) && 
                      (points[0].x() != ((_XMaxValue-_XMinValue) * x_stretch_factor))) {
                     points[pi].setX((_XMaxValue-_XMinValue) * x_stretch_factor);
                  } else {
                     points[pi].setX(_XMinValue * x_stretch_factor);
                  }
               }
               else {
                  points[pi].setX(_XMaxValue * x_stretch_factor);
               }

               points[pi].setY((_YMaxValue - temp_yvalues[i]) * y_stretch_factor);
               point_array.setPoint(pi, points[pi]);
            }
         } else {
            points[pi].setX(temp_xvalues[i+1] * x_stretch_factor);
            points[pi].setY((_YMaxValue - temp_yvalues[i]) * y_stretch_factor);
            point_array.setPoint(pi, points[pi]);
         }
         pi++;
      }
   }
   
   QColor color = _CurveColorValue;
   QPen pen(color, 2);
   double x_factor = ((double)(_CurveRectangle.width()) / (_XMaxValue * x_stretch_factor));
   double y_factor = (double)(_CurveRectangle.height()) / (_YMaxValue * y_stretch_factor);
   QWMatrix matrix(x_factor, 0, 0, y_factor, _CurveRectangle.left(), _CurveRectangle.top());

   painter.setPen(pen);
   painter.setWorldMatrix(matrix);
   painter.drawPolyline(point_array);
   QWMatrix identity;
   painter.setWorldMatrix(identity);
WMETHOD_VOID_EPILOG
#endif
}

void CSimpleGraphic::SetXCount()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_XCount != -1) return;
   if (_X9Ref != NULL) {
      _XCount = 10;
   } else if (_X8Ref != NULL) {
      _XCount = 9;
   } else if (_X7Ref != NULL) {
      _XCount = 6;
   } else if (_X6Ref != NULL) {
      _XCount = 7;
   } else if (_X5Ref != NULL) {
      _XCount = 6;
   } else if (_X4Ref != NULL) {
      _XCount = 5;
   } else if (_X3Ref != NULL) {
      _XCount = 4;
   } else if (_X2Ref != NULL) {
      _XCount = 3;
   } else if (_X1Ref != NULL) {
      _XCount = 2;
   } else if (_X0Ref != NULL) {
      _XCount = 1;
   } else {
      _XCount = MAX_XVALUES;
   }
WMETHOD_VOID_EPILOG
#endif
}
