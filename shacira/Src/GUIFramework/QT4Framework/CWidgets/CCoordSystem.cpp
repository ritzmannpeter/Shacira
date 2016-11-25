
#undef VISU_TEST

#include "CCoordSystem.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(AdditionalWidget,
                   CCoordSystem, \
                   ICON_SET("graphicsview"), \
                   "basic graphic widget for the display of curves in a 2D coordinate system")
#endif

#include "cPaintUtils.h"

#ifndef _MIN_
#define _MIN_(a,b) (((a)<(b)) ? a : b)
#endif

CCoordSystem::CCoordSystem(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QFrame(parent, f),
#else
   : QFrame(parent, name, f),
#endif
     CWidgetBase(this) 
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
   _XMinRef = NULL;
   _XMinView = NULL;
   _XMaxRef = NULL;
   _XMaxView = NULL;
   _YMinRef = NULL;
   _YMinView = NULL;
   _YMaxRef = NULL;
   _YMaxView = NULL;

   _XMinValue = 0;
   _YMinValue = 0;
   _XMaxValue = 200;
   _YMaxValue = 200;
   _XPrecisionValue = 0;
   _YPrecisionValue = 0;

   _XStepsValue = 5;
   _YStepsValue = 5;
   _XAxisHeightValue = 10;
   _YAxisWidthValue = 15;
   _XDistanceValue = 5;
   _YDistanceValue = 5;

   _SystemTypeValue = LeftBottom;
#ifdef QT4
   _GridColorValue = CWidgetBase::paletteBackgroundColor();
#else
   _GridColorValue = paletteBackgroundColor();
#endif
   _AxisColorValue = Qt::gray;
   _LegendColorValue = Qt::black;
   for (ULONG_T i=0; i<MAX_SCALE_STEPS; i++) {
      _XGrainPos[i] = 0;
      _YGrainPos[i] = 0;
   }
   _Initialized = false;
}

CCoordSystem::~CCoordSystem() 
{
}

void CCoordSystem::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QFrame::mousePressEvent(e);
   }
}

void CCoordSystem::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QFrame::mouseReleaseEvent(e);
   }
}

void CCoordSystem::resizeEvent(QResizeEvent * e)
{
   QFrame::resizeEvent(e);
   Initialize();
   PaintIt();
}

void CCoordSystem::paintEvent(QPaintEvent * e)
{
   QFrame::paintEvent(e);
#ifdef QT4
   QPainter painter(this);
   painter.drawImage(_XDistanceValue, _YDistanceValue, _DoubleBuffer.toImage());
#else
   bitBlt(this, _XDistanceValue, _YDistanceValue, &_DoubleBuffer);
#endif
}


// GUI related virtual methods

void CCoordSystem::View()
{
   PaintIt();
}

void CCoordSystem::DelayedLanguageChange()
{
   PaintIt();
}

// CCS related virtual methods

void CCoordSystem::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   Initialize();
   CCSInitializeVarRef(_XMinSpec, _XMinRef, _XMinView, 0);
   CCSInitializeVarRef(_XMaxSpec, _XMaxRef, _XMaxView, 1);
   CCSInitializeVarRef(_YMinSpec, _YMinRef, _YMinView, 2);
   CCSInitializeVarRef(_YMaxSpec, _YMaxRef, _YMaxView, 3);
WMETHOD_VOID_EPILOG
#endif
}

void CCoordSystem::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   switch (id) {
   case 0:
      _XMinValue = atof(value);
      if (_XMinRef != NULL) {
         _XPrecisionValue = _XMinRef->Precision();
      }
      _XUnitText = XUnitText();
      break;
   case 1:
      _XMaxValue = atof(value);
      if (_XMaxRef != NULL) {
         _XPrecisionValue = _XMaxRef->Precision();
      }
      _XUnitText = XUnitText();
      break;
   case 2:
      _YMinValue = atof(value);
//      _YMaxValue = atof(value);
      if (_YMinRef != NULL) {
         _YPrecisionValue = _YMinRef->Precision();
      }
      _YUnitText = YUnitText();
      break;
   case 3:
      _YMaxValue = atof(value);
      if (_YMaxRef != NULL) {
         _YPrecisionValue = _YMaxRef->Precision();
      }
      _YUnitText = YUnitText();
      break;
   }
   Notify(VIEW_DATA);
WMETHOD_VOID_EPILOG
#endif
}

void CCoordSystem::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size)
{
}

void CCoordSystem::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CCoordSystem::InitWidget()
{
#ifdef QT4
   CWidgetBase::setBackgroundMode(NoBackground);
#else
   setBackgroundMode(Qt::NoBackground);
#endif
   CalculateAreas();
}

void CCoordSystem::Initialize()
{
   InitWidget();
   _Initialized = true;
}

void CCoordSystem::PaintIt()
{
#ifdef VISU_TEST
   QPainter painter;
   painter.begin(&_DoubleBuffer, this);
   cPaintUtils::SetShape(painter, &ret(), red);
   cPaintUtils::SetShape(painter, &_XAxisRectangle, green);
   cPaintUtils::SetShape(painter, &_YAxisRectangle, blue);
   cPaintUtils::SetShape(painter, &_CurveRectangle, yellow);
   update();
   return;
#endif

   QPainter painter;
#ifdef QT4
   painter.begin(&_DoubleBuffer);
   painter.initFrom(this);
#else
   painter.begin(&_DoubleBuffer, this);
#endif
   PaintBackground(painter);
   PaintGrid(painter);
   PaintAxis(painter);
   PaintLegend(painter);
   PaintCurves(painter);
   update();
}

void CCoordSystem::PaintBackground(QPainter & painter)
{
#ifdef VISU_TEST
   return;
#endif
#ifdef QT4
   cPaintUtils::SetShape(painter, &rect(), CWidgetBase::paletteBackgroundColor());
#else
   cPaintUtils::SetShape(painter, &rect(), paletteBackgroundColor());
#endif
}

void CCoordSystem::PaintGrid(QPainter & painter)
{
#ifdef VISU_TEST
   return;
#endif
   QPen pen = QPen(_GridColorValue, 0);
   painter.setPen(pen);
   ULONG_T i = 0;

   ULONG_T x_pos = 0;
//   ULONG_T x_size = _CurveRectangle.width();
   ULONG_T x_steps = _MIN_(_XStepsValue + 1, MAX_SCALE_STEPS);
   ULONG_T y_start = _CurveRectangle.top();
   ULONG_T y_end = _CurveRectangle.bottom();
   for (i=0; i<x_steps; i++) {
      if (i > 0) {
         x_pos = _XGrainPos[i];
         painter.drawLine(x_pos, y_start, x_pos, y_end);
      }
   }

   ULONG_T y_pos = 0;
//   ULONG_T y_size = _YAxisRectangle.height();
   ULONG_T y_steps = _MIN_(_YStepsValue + 1, MAX_SCALE_STEPS);
   ULONG_T x_start = _CurveRectangle.left();
   ULONG_T x_end = _CurveRectangle.right();
   for (i=0; i<y_steps; i++) {
      if (i > 0) {
         y_pos = _YGrainPos[i];
         painter.drawLine(x_start, y_pos, x_end, y_pos);
      }
   }

}

void CCoordSystem::PaintAxis(QPainter & painter)
{
#ifdef VISU_TEST
   return;
#endif
   QPen pen = QPen(_AxisColorValue, 0);
   painter.setPen(pen);
   PaintXScale(painter);
   PaintYScale(painter);
}

void CCoordSystem::PaintCurves(QPainter & painter)
{
}

void CCoordSystem::PaintLegend(QPainter & painter)
{
#define WIDTH_CORRECTION   10
#define WIDTH_OFFSET       2
#define HEIGHT_CORRECTION  3
#ifdef VISU_TEST
   return;
#endif
   FormatLegendText();
   QFont w_font = font();
   QFontMetrics w_fm(w_font);
   
   QRect bRect = w_fm.boundingRect(_XMinString);
   int LabelWidth = bRect.width() + WIDTH_OFFSET;
   int LabelHeight = bRect.height();

   if((_SystemTypeValue == LeftBottom) || (_SystemTypeValue == RightBottom))
   {
	   _XLeftRectangle = QRect(_XAxisRectangle.left(), 
	                           _XAxisRectangle.bottom() - LabelHeight + HEIGHT_CORRECTION,
	                           LabelWidth,
	                           LabelHeight);
	   if(_SystemTypeValue == LeftBottom)
	   {
#ifdef QT4
         _XLeftRectangle = _XLeftRectangle.translated(-10,0);
#else
         _XLeftRectangle.moveBy(-10,0);
#endif
	   }

	   bRect = w_fm.boundingRect(_XMaxString);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _XRightRectangle = QRect(_XAxisRectangle.right() - LabelWidth,
		                        _XAxisRectangle.bottom() - LabelHeight + HEIGHT_CORRECTION,
	                            LabelWidth,
	                            LabelHeight);
	   if(_SystemTypeValue == RightBottom)
	   {
#ifdef QT4
         _XRightRectangle = _XRightRectangle.translated(10,0);
#else
			_XRightRectangle.moveBy(10,0);
#endif
      }

	   bRect = w_fm.boundingRect(_XUnitText);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _XMidRectangle = QRect(_XAxisRectangle.right() - (_XAxisRectangle.width() / 2),
	                          _XAxisRectangle.bottom() - LabelHeight + HEIGHT_CORRECTION,
	                          LabelWidth,
	                          LabelHeight);
   }
   else
   if((_SystemTypeValue == LeftTop) || (_SystemTypeValue == RightTop))
   {
	   _XLeftRectangle = QRect(_XAxisRectangle.left(), 
	                           _XAxisRectangle.top(),
	                           LabelWidth,
	                           LabelHeight);
	   if(_SystemTypeValue == LeftTop)
	   {
#ifdef QT4
         _XLeftRectangle = _XLeftRectangle.translated(-10,0);
#else
			_XLeftRectangle.moveBy(-10,0);
#endif
      }

	   bRect = w_fm.boundingRect(_XMaxString);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _XRightRectangle = QRect(_XAxisRectangle.right() - LabelWidth,
		                        _XAxisRectangle.top(),
	                            LabelWidth,
	                            LabelHeight);
	   if(_SystemTypeValue == RightTop)
	   {
#ifdef QT4
         _XRightRectangle = _XRightRectangle.translated(10,0);
#else
			_XRightRectangle.moveBy(10,0);
#endif
      }

	   bRect = w_fm.boundingRect(_XUnitText);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _XMidRectangle = QRect(_XAxisRectangle.right() - (_XAxisRectangle.width() / 2),
	                          _XAxisRectangle.top(),
	                          LabelWidth,
	                          LabelHeight);
   }
   


   if((_SystemTypeValue == LeftBottom) || (_SystemTypeValue == LeftTop))
   {
	   bRect = w_fm.boundingRect(_YMaxString);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _YTopRectangle = QRect(_YAxisRectangle.right() - (LabelWidth + WIDTH_CORRECTION),
	                          _YAxisRectangle.top() ,
	                          LabelWidth,
	                          LabelHeight);

	   if(_SystemTypeValue == LeftTop)
	   {
#ifdef QT4
         _YTopRectangle = _YTopRectangle.translated(0,-3);
#else
			_YTopRectangle.moveBy(0,-3);
#endif
      }

	   bRect = w_fm.boundingRect(_YMinString);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _YBottomRectangle = QRect(_YAxisRectangle.right() - (LabelWidth + WIDTH_CORRECTION),
	                             _YAxisRectangle.bottom() - LabelHeight,
	                             LabelWidth,
	                             LabelHeight);

	   if(_SystemTypeValue == LeftBottom)
	   {
#ifdef QT4
         _YBottomRectangle = _YBottomRectangle.translated(0,3);
#else
			_YBottomRectangle.moveBy(0,3);
#endif
      }

	   bRect = w_fm.boundingRect(_YUnitText);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _YMidRectangle = QRect(_YAxisRectangle.right() - (LabelWidth + WIDTH_CORRECTION),
	                          _YAxisRectangle.bottom() - (_YAxisRectangle.height() / 2),
	                          LabelWidth,
	                          LabelHeight);
   }
   else
   if((_SystemTypeValue == RightBottom) || (_SystemTypeValue == RightTop))
   {
	   bRect = w_fm.boundingRect(_YMaxString);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _YTopRectangle = QRect(_YAxisRectangle.left() + WIDTH_CORRECTION,
	                          _YAxisRectangle.top() ,
	                          LabelWidth,
	                          LabelHeight);

	   if(_SystemTypeValue == RightTop)
	   {
#ifdef QT4
         _YTopRectangle = _YTopRectangle.translated(0,-3);
#else
			_YTopRectangle.moveBy(0,-3);
#endif
      }

	   bRect = w_fm.boundingRect(_YMinString);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _YBottomRectangle = QRect(_YAxisRectangle.left() + WIDTH_CORRECTION,
	                             _YAxisRectangle.bottom() - LabelHeight,
	                             LabelWidth,
	                             LabelHeight);

	   if(_SystemTypeValue == RightBottom)
	   {
#ifdef QT4
         _YBottomRectangle = _YBottomRectangle.translated(0,3);
#else
			_YBottomRectangle.moveBy(0,3);
#endif
      }
	   
	   bRect = w_fm.boundingRect(_YUnitText);
	   LabelWidth = bRect.width() + WIDTH_OFFSET;
	   LabelHeight = bRect.height();

	   _YMidRectangle = QRect(_YAxisRectangle.left() + WIDTH_CORRECTION,
	                          _YAxisRectangle.bottom() - (_YAxisRectangle.height() / 2),
	                          LabelWidth,
	                          LabelHeight);
   }

   painter.setPen(_LegendColorValue);
   int flags = Qt::AlignHCenter | Qt::AlignVCenter;
   int flags1 = Qt::AlignHCenter | Qt::AlignTop;
   painter.drawText(_XLeftRectangle, flags, _XMinString);
   painter.drawText(_XMidRectangle, flags, _XUnitText);
   painter.drawText(_XRightRectangle, flags, _XMaxString);
   painter.drawText(_YTopRectangle, flags1, _YMaxString);
   painter.drawText(_YMidRectangle, flags, _YUnitText);
   painter.drawText(_YBottomRectangle, flags, _YMinString);

   
   return;
}

void CCoordSystem::PaintXScale(QPainter & painter)
{
#ifdef VISU_TEST
   return;
#endif
   ULONG_T y_start = 0;
   ULONG_T y_end = 0;
   if (_SystemTypeValue == RightBottom ||
       _SystemTypeValue == LeftBottom) {
      painter.drawLine(_XAxisRectangle.left(),
                       _XAxisRectangle.top(),
                       _XAxisRectangle.right(),
                       _XAxisRectangle.top());
      y_start = _XAxisRectangle.top();
      y_end = y_start + SCALE_GRAIN_SIZE;
   } else if (_SystemTypeValue == RightTop ||
              _SystemTypeValue == LeftTop) {
      painter.drawLine(_XAxisRectangle.left(),
                       _XAxisRectangle.bottom(),
                       _XAxisRectangle.right(),
                       _XAxisRectangle.bottom());
      y_end = _XAxisRectangle.bottom();
      y_start = y_end - SCALE_GRAIN_SIZE;
   }
   ULONG_T x_pos = 0;
   ULONG_T x_steps = _MIN_(_XStepsValue + 1, MAX_SCALE_STEPS);
   for (ULONG_T i=0; i<x_steps; i++) {
      x_pos = _XGrainPos[i];
      painter.drawLine(x_pos, y_start, x_pos, y_end);
   }
}

void CCoordSystem::PaintYScale(QPainter & painter)
{
   ULONG_T x_start = 0;
   ULONG_T x_end = 0;
   if (_SystemTypeValue == LeftTop ||
       _SystemTypeValue == LeftBottom) {
      painter.drawLine(_YAxisRectangle.right(),
                       _YAxisRectangle.top(),
                       _YAxisRectangle.right(),
                       _YAxisRectangle.bottom());
      x_end = _YAxisRectangle.right();
      x_start = x_end - SCALE_GRAIN_SIZE;
   } else if (_SystemTypeValue == RightTop ||
              _SystemTypeValue == RightBottom) {
      painter.drawLine(_YAxisRectangle.left(),
                       _YAxisRectangle.top(),
                       _YAxisRectangle.left(),
                       _YAxisRectangle.bottom());
      x_start = _YAxisRectangle.left();
      x_end = x_start + SCALE_GRAIN_SIZE;
   }
   ULONG_T y_pos = 0;
   ULONG_T y_steps = _MIN_(_YStepsValue + 1, MAX_SCALE_STEPS);
   for (ULONG_T i=0; i<y_steps; i++) {
      y_pos = _YGrainPos[i];
      painter.drawLine(x_start, y_pos, x_end, y_pos);
   }
}

void CCoordSystem::CalculateAreas()
{
   QSize widget_size = size();
   if (_XDistanceValue > 0) {
      widget_size.setWidth(widget_size.width() - (2 * _XDistanceValue));
   }
   if (_YDistanceValue > 0) {
      widget_size.setHeight(widget_size.height() - (2 * _YDistanceValue));
   }
   _DoubleBuffer = QPixmap(widget_size);
   setMinimumSize((_XDistanceValue * 2) + _YAxisWidthValue + 20,
                  (_YDistanceValue * 2) + _XAxisHeightValue + 20);

   if (_SystemTypeValue == LeftBottom) {
      _CurveRectangle.setLeft(rect().left() + _YAxisWidthValue);
      _CurveRectangle.setTop(rect().top());
      _CurveRectangle.setWidth(rect().width() - _YAxisWidthValue);
      _CurveRectangle.setHeight(rect().height() - _XAxisHeightValue);
      _XAxisRectangle = QRect(_CurveRectangle.left(),
                              _CurveRectangle.bottom(),// + 1,
                              _CurveRectangle.width(),
                              _XAxisHeightValue);
      _YAxisRectangle = QRect(rect().left(),
                              _CurveRectangle.top(),
                              _YAxisWidthValue + 1,
                              _CurveRectangle.height());
   } else if (_SystemTypeValue == RightBottom) {
      _CurveRectangle.setLeft(rect().left());
      _CurveRectangle.setTop(rect().top());
      _CurveRectangle.setWidth(rect().width() - _YAxisWidthValue);
      _CurveRectangle.setHeight(rect().height() - _XAxisHeightValue);
      _XAxisRectangle = QRect(_CurveRectangle.left(),
                              _CurveRectangle.bottom(),// + 1,
                              _CurveRectangle.width(),
                              _XAxisHeightValue);
      _YAxisRectangle = QRect(_CurveRectangle.right(),// + 1,
                              _CurveRectangle.top(),
                              _YAxisWidthValue,
                              _CurveRectangle.height());
   }
   CalculateScaleAreas();
}

void CCoordSystem::CalculateScaleAreas()
{
   ULONG_T i = 0;
   ULONG_T x_pos = 0;
   ULONG_T x_steps = _MIN_(_XStepsValue + 0, MAX_SCALE_STEPS-1);
   ULONG_T x_size = _XAxisRectangle.width();
   ULONG_T x_diff = x_size / x_steps;
   ULONG_T y_pos = 0;
   ULONG_T y_steps = _MIN_(_YStepsValue + 0, MAX_SCALE_STEPS-1);
   ULONG_T y_size = _YAxisRectangle.height();
   ULONG_T y_diff = y_size / y_steps;
   if (_SystemTypeValue == LeftBottom) {
      x_pos = _XAxisRectangle.left();
      for (i=0; i<x_steps; i++) {
         _XGrainPos[i] = x_pos;
         x_pos += x_diff;
      }
      y_pos = _YAxisRectangle.bottom();// + 1;
      for (i=0; i<y_steps; i++) {
         _YGrainPos[i] = y_pos;
         y_pos -= y_diff;
      }
      _XGrainPos[x_steps] = _XAxisRectangle.right();// - 1;
      _YGrainPos[y_steps] = _YAxisRectangle.top();
   } else if (_SystemTypeValue == RightBottom) {
      x_pos = _XAxisRectangle.right();
      for (i=0; i<x_steps; i++) {
         _XGrainPos[i] = x_pos;
         x_pos -= x_diff;
      }
      y_pos = _YAxisRectangle.bottom();// + 1;
      for (i=0; i<y_steps; i++) {
         _YGrainPos[i] = y_pos;
         y_pos -= y_diff;
      }
      _XGrainPos[x_steps] = _XAxisRectangle.left();
      _YGrainPos[y_steps] = _YAxisRectangle.top();
   }
}

void CCoordSystem::FormatLegendText()
{
   char min_x[32] = {0};
   char max_x[32] = {0};
   char min_y[32] = {0};
   char max_y[32] = {0};
  
   // x-axis values
   if ((_XPrecisionValue >= 0) && (_XPrecisionValue <= 4)) {
      SafePrintf(min_x, sizeof(min_x), "%.*f", _XPrecisionValue, _XMinValue);
      SafePrintf(max_x, sizeof(max_x), "%.*f", _XPrecisionValue, _XMaxValue);
   }
   else {
      SafePrintf(min_x, sizeof(min_x), "%.lf", _XMinValue);
      SafePrintf(max_x, sizeof(max_x), "%.lf", _XMaxValue);
   }

   // y-axis values
   if ((_YPrecisionValue >= 0) && (_YPrecisionValue <= 4)) {
      SafePrintf(min_y, sizeof(min_y), "%.*f", _YPrecisionValue, _YMinValue);
      SafePrintf(max_y, sizeof(max_y), "%.*f", _YPrecisionValue, _YMaxValue);
   }
   else {
      SafePrintf(min_y, sizeof(min_y), "%.lf", _YMinValue);
      SafePrintf(max_y, sizeof(max_y), "%.lf", _YMaxValue);
   }

   if (_SystemTypeValue == LeftBottom) {
      _YMinString = min_y;
      _YMaxString = max_y;
      _XMinString = min_x;
      _XMaxString = max_x;
   } else if (_SystemTypeValue == LeftTop) {
      _YMinString = max_y;
      _YMaxString = min_y;
      _XMinString = min_x;
      _XMaxString = max_x;
   } else if (_SystemTypeValue == RightBottom) {
      _YMinString = min_y;
      _YMaxString = max_y;
      _XMinString = max_x;
      _XMaxString = min_x;
   } else if (_SystemTypeValue == RightTop) {
      _YMinString = max_y;
      _YMaxString = min_y;
      _XMinString = max_x;
      _XMaxString = min_x;
   }
}

QString CCoordSystem::XUnitText()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   cVariable * variable = _Context->Variable(CONST_STRING(_XUnitValue));
   if (variable == NULL) {
      return _XUnitValue;
   } else {
#ifdef QT4
      QString dimension = QString::fromLocal8Bit(variable->UnitText().c_str());
#else
      QString dimension = variable->UnitText().c_str();
#endif
      return dimension;
   }
WMETHOD_RC_EPILOG("?")
#endif
   return "??";
}

QString CCoordSystem::YUnitText()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   cVariable * variable = _Context->Variable(CONST_STRING(_YUnitValue));
   if (variable == NULL) {
      return _YUnitValue;
   } else {
#ifdef QT4
      QString dimension = QString::fromLocal8Bit(variable->UnitText().c_str());
#else
      QString dimension = variable->UnitText().c_str();
#endif
      return dimension;
   }
WMETHOD_RC_EPILOG("?")
#endif
   return "??";
}


