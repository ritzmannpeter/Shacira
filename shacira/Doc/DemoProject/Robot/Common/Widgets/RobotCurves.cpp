
#include "RobotCurves.h"

#ifdef _ROBOT_WIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
#include "default_icon.h"
#include "embedded_images.h"
QT_PLUGIN_REGISTER(RobotCurves,
                   "RobotCurves.h",
                   QIconSet(qembed_findImage("cgraphic")),
                   "RobotWidgets",
                   "general graphic widget for the display of curves in a 2D coordinate system",
                   "general graphic widget for the display of curves in a 2D coordinate system",
                   false)
#endif

#include "cPaintUtils.h"

#ifndef _MIN_
#define _MIN_(a,b) (((a)<(b)) ? a : b)
#endif

RobotCurves::RobotCurves(QWidget * parent, const char * name, WFlags f) :
        CWidget(parent, name, 0)
{
   CONSTRUCT_WIDGET

   _ValueTypeValue = Byte;
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
   int i = 0;
   for (i=0; i<CURVE_COUNT; i++) {
      _CurveBuffer[i] = NULL;
///#ifdef QT_PLUGIN
      _CurveBuffer[i] = (BUF_T)calloc(1, 1000);
      int j = 0;
      for (j=0; j<1000; j++) {
         (_CurveBuffer[i])[j] = (i*40)+(((UCHAR_T)rand())%30);
      }
///#endif
   }
   _ValueCount = 500;
   _MaxValue = 255;
}

RobotCurves::~RobotCurves() 
{
}

/// reimplemented qt methods

void RobotCurves::paintEvent(QPaintEvent * e)
{
   /// copies memory resident paint buffer to the screen
   CWidget::paintEvent(e);
   bitBlt(this, 0, 0, &_DoubleBuffer);
}

void RobotCurves::resizeEvent(QResizeEvent * e)
{
   /// widget resize causes adjustment of background paint buffer
   CWidget::resizeEvent(e);
   _DoubleBuffer = QPixmap(size());
   PaintAll();
}

// GUI related virtual methods

void RobotCurves::View()
{
   /// this method paints all to the background paint buffer
   PaintAll();
}

// CCS related virtual methods

void RobotCurves::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   /// initialization of the CCS connections
   CWidget::CCSSetContext(node, context);
   CCSInitializeVarRef(_Curve0Spec, _Curve0Ref, _Curve0View, 0);
   CCSInitializeVarRef(_Curve1Spec, _Curve1Ref, _Curve1View, 1);
   CCSInitializeVarRef(_Curve2Spec, _Curve2Ref, _Curve2View, 2);
   CCSInitializeVarRef(_Curve3Spec, _Curve3Ref, _Curve3View, 3);
   CCSInitializeVarRef(_Curve4Spec, _Curve4Ref, _Curve4View, 4);
   CCSInitializeVarRef(_Curve5Spec, _Curve5Ref, _Curve5View, 5);
WMETHOD_VOID_EPILOG
#endif
}

void RobotCurves::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                              UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   Notify(VIEW_DATA);
WMETHOD_VOID_EPILOG
#endif
}

void RobotCurves::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                              UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (id < CURVE_COUNT) {
      _CurveBuffer[id] = buf;
      _ValueCount = size;
      /// controller notify "model" change and activates view operation
      Notify(VIEW_DATA);
   }
WMETHOD_VOID_EPILOG
#endif
}

void RobotCurves::PaintAll()
{
   /// refresh the background paint buffer
   /// this method is executed in the Vieww method
   QPainter painter(&_DoubleBuffer);
   PaintBackground(painter);
   PaintGrid(painter);
   PaintAxis(painter);
   PaintCurves(painter);
   /// activate repaint on the screen
   repaint();
}

void RobotCurves::PaintBackground(QPainter & painter)
{
   _DoubleBuffer.fill(paletteBackgroundColor());
}

void RobotCurves::PaintGrid(QPainter & painter)
{
#define GRID_COLOR Qt::white
#define STEP_SIZE 30
   painter.setPen(QPen(GRID_COLOR, 1));
   int x_steps = _DoubleBuffer.width() / STEP_SIZE;
   int y_steps = _DoubleBuffer.height() / STEP_SIZE;
   int x_pos = 0;
   int y_pos = 0;
   int i = 0;
   for (i=0; i<x_steps; i++) {
      x_pos = i * STEP_SIZE;
      painter.drawLine(x_pos, 0, x_pos, _DoubleBuffer.height());
   }
   for (i=0; i<y_steps; i++) {
      y_pos = i * STEP_SIZE;
      painter.drawLine(0, y_pos, _DoubleBuffer.width(), y_pos);
   }
}

void RobotCurves::PaintAxis(QPainter & painter)
{
#define AXIS_COLOR Qt::black
   painter.setPen(QPen(AXIS_COLOR, 1));
   /// y-axis
   painter.drawLine(0, 0, 0, _DoubleBuffer.height());
   /// x-axis
   painter.drawLine(0, _DoubleBuffer.height() - 1, _DoubleBuffer.width(), _DoubleBuffer.height() - 1);
}

static QColor CurveColor(int index)
{
   switch (index) {
   case 0: return Qt::red;
   case 1: return Qt::blue;
   case 2: return Qt::green;
   case 3: return Qt::magenta;
   case 4: return Qt::gray;
   case 5: return Qt::white;
   }
   return Qt::black;
}

void RobotCurves::PaintCurves(QPainter & painter)
{
#define XSCALE(p,w,xf) ((p)*(xf))
#define YSCALE(p,h,yf) ((h) - ((p)*(yf)))
//#ifndef QT_PLUGIN
//WMETHOD_PROLOG
   int i = 0;
   int width = _DoubleBuffer.width();
   int height = _DoubleBuffer.height();
   double xfact = (double)width/_ValueCount;
   double yfact = (double)height/_MaxValue;
   for (i=0; i<CURVE_COUNT; i++) {
      if (_CurveBuffer[i] != NULL) {
         painter.setPen(QPen(CurveColor(i), 1));
         int x_start = XSCALE(0,width,xfact);
         int y_start = YSCALE((_CurveBuffer[i])[0],height,yfact);
         int x_end = XSCALE(1,width,xfact);
         int y_end = YSCALE((_CurveBuffer[i])[1],height,yfact);
         int j = 0;
         for (j=0; j<_ValueCount-1; j++) {
            painter.drawLine(x_start, y_start, x_end, y_end);
            x_start = x_end;
            y_start = y_end;
            x_end = XSCALE(j+1,width,xfact);
            y_end = YSCALE((_CurveBuffer[i])[j+1],height,yfact);
         }
      }
   }
//WMETHOD_VOID_EPILOG
//#endif
}


