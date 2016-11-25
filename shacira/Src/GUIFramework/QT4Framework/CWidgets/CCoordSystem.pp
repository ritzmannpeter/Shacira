
#ifndef _ccoordsystem_h_
#define _ccoordsystem_h_

#include "CWidgetBase.h"
#include <qframe.h>
#include <qpainter.h>
#include <qpixmap.h>

#define MAX_SCALE_STEPS				30
#define SCALE_GRAIN_SIZE			5

/**!
  * @brief A widget that serves as base widget for coordinate system graphics.
  * <p>
  */
class _CWIDGET_EXPORT_ CCoordSystem : public QFrame, public CWidgetBase  
{
// start 2i generic widget definition

   Q_OBJECT

   // common property definitions of C widgets
public:
   Q_ENUMS(EventFilters)
   PROPERTY_2i(QByteArray,Comment)
   PROPERTY_2i(QByteArray,QualifiedName)
   PROPERTY_2i(QByteArray,DarkFuncRef)
   PROPERTY_2i(QByteArray,GUISlotFuncRef)
   PROPERTY_2i(QByteArray,GUISignalFilterFuncRef)
   PROPERTY_2i(EventFilters,EventFilter)
   PROPERTY_2i(QByteArray,EventFilterFuncRef)
   PROPERTY_2i(bool,Listening)
   PROPERTY_2i(QByteArray,ListenTo)
   PROPERTY_2i(QByteArray,InitFuncRef)
   Q_ENUMS(AccesTypes)
   PROPERTY_2i(AccesTypes,Group0)
   PROPERTY_2i(AccesTypes,Group1)
   PROPERTY_2i(AccesTypes,Group2)
   PROPERTY_2i(AccesTypes,Group3)
   PROPERTY_2i(AccesTypes,Group4)
   PROPERTY_2i(AccesTypes,Group5)
   PROPERTY_2i(AccesTypes,Group6)
   PROPERTY_2i(AccesTypes,Group7)
   Q_ENUMS(RefreshTypes)
   PROPERTY_2i(RefreshTypes,Refresh)
   PROPERTY_2i(QByteArray,HelpId1)
   PROPERTY_2i(QByteArray,HelpId2)
   // used enum type definitions
public:
   enum EventFilters {
         NoEvents = 0,
         BaseEvent = OBJ_FLT_EVENT,
         Alarm = OBJ_FLT_ALARM,
         Info = OBJ_FLT_INFO,
         State = OBJ_FLT_STATE,
         DataChange = OBJ_FLT_DATA_CHANGE,
         JobSpec = OBJ_FLT_JOB_SPEC,
         JobEntry = OBJ_FLT_JOB_ENTRY,
         Progress = OBJ_FLT_PROGRESS,
         Protocol = OBJ_FLT_PROTOCOL,
         AllEvents = ALL_EVENTS
   };
   enum AccesTypes {
         NoAccess = 0,        ///< no access the widget is not visible
         ReadOnlyAccess = 1,  ///< the widget is shown but input is disabled
         WriteAccess = 2      ///< the widget is shown and input is enabled
   };
   enum RefreshTypes {
         NoRefresh = 0,       ///< no automatic widget refresh
         FastRefresh = 1,     ///< fast widget refresh
         SlowRefresh = 2,     ///< slow widget refresh
         CycleRefresh = 3,    ///< slow widget refresh
         EventRefresh = 4     ///< event based widget refresh
   };
   /// end of common property definitions of C widgets

   // further widget specific properties
   PROPERTY_2i(double,XMin)
   PROPERTY_2i(double,XMax)
   PROPERTY_2i(double,YMin)
   PROPERTY_2i(double,YMax)
   PROPERTY_2i(int,XPrecision)
   PROPERTY_2i(int,YPrecision)
   VAR_REF_2i(XMin)
   VAR_REF_2i(XMax)
   VAR_REF_2i(YMin)
   VAR_REF_2i(YMax)
   PROPERTY_2i(int,XSteps)
   PROPERTY_2i(int,YSteps)
   PROPERTY_2i(int,XAxisHeight)
   PROPERTY_2i(int,YAxisWidth)
   PROPERTY_2i(int,XDistance)
   PROPERTY_2i(int,YDistance)
   PROPERTY_2i(QString,XUnit)
   PROPERTY_2i(QString,YUnit)
   Q_ENUMS(SystemTypes)
   PROPERTY_2i(SystemTypes,SystemType)
   PROPERTY_2i(QColor,GridColor)
   PROPERTY_2i(QColor,AxisColor)
   PROPERTY_2i(QColor,LegendColor)
   // end of widget specific properties
public:
   enum SystemTypes {
         LeftBottom = 0,
         LeftTop = 1,
         RightBottom = 2,
         RightTop = 3
   };

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

   virtual void Print(STREAM_T stream)
   {
   }
   virtual void Print(PAINTER_T painter)
   {
   }

public slots:
   void CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
   {
      CheckAppearance(refresh_type, parent_state);
// this is no container
//      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }
   virtual void Print()
   {
   }

signals:
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e);
   virtual void focusInEvent(QFocusEvent * e)
   {
      QFrame::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      QFrame::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      QFrame::keyReleaseEvent(e);
   };
   void resizeEvent(QResizeEvent * e);

public: 
   // GUI related virtual methods
   virtual void View();
   virtual void Notification(ULONG_T event_code) {};
   virtual void GUIEvent(ULONG_T signal, QWidget * sender) {};
   virtual void DelayedLanguageChange();

   // CCS related virtual methods
   virtual void CCSSetContext(NODE_PTR node, CONTEXT_PTR context);
   virtual void CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object);

protected:
   // view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition

public:
   CCoordSystem(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CCoordSystem();

protected:
   QPixmap _DoubleBuffer;
   BOOL_T _Initialized;

   QString _XMinString;
   QString _XMaxString;
   QString _YMinString;
   QString _YMaxString;

   QRect _CurveRectangle;
   QRect _XAxisRectangle;
   QRect _YAxisRectangle;

   LONG_T _XGrainPos[MAX_SCALE_STEPS];
   LONG_T _YGrainPos[MAX_SCALE_STEPS];

   QRect _XLeftRectangle;
   QRect _XRightRectangle;
   QRect _XMidRectangle;
   QRect _YTopRectangle;
   QRect _YBottomRectangle;
   QRect _YMidRectangle;

   QString _XUnitText;
   QString _YUnitText;

private:
   void Initialize();
   void InitWidget();
protected:
   virtual void PaintIt();
   virtual void PaintBackground(QPainter & painter);
   virtual void PaintGrid(QPainter & painter);
   virtual void PaintAxis(QPainter & painter);
   virtual void PaintCurves(QPainter & painter);
   virtual void PaintLegend(QPainter & painter);
   virtual void PaintXScale(QPainter & painter);
   virtual void PaintYScale(QPainter & painter);
   virtual void CalculateAreas();
   virtual void CalculateScaleAreas();
   virtual void FormatLegendText();
   virtual QString XUnitText();
   virtual QString YUnitText();
};

#endif


