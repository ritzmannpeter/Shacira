
#ifndef _cprocgraphic_h_
#define _cprocgraphic_h_

#include "cWidgetBase.h"
#include <qpainter.h>
#include <qlabel.h>
#include <qpixmap.h>

#define MAX_PROC_CURVES  6

typedef enum {LeftCursor, RightCursor, CursorDistance} Cursors;
typedef enum {LeftDirection, RightDirection} Directions;

/**!
  * @brief Very specific display widget to display process value curves.
  * <p>
  */
class SH_QT_WIDGET_PLUGIN_EXPORT CProcGraphic : public QFrame, public CWidgetBase  
{

// start 2i generic widget definition

   Q_OBJECT

   // common property definitions of C widgets
public:
   Q_ENUMS(EventFilters)
   PROPERTY_2i(QCString,Comment)
   PROPERTY_2i(QCString,QualifiedName)
   PROPERTY_2i(QCString,DarkFuncRef)
   PROPERTY_2i(QCString,GUISlotFuncRef)
   PROPERTY_2i(QCString,GUISignalFilterFuncRef)
   PROPERTY_2i(EventFilters,EventFilter)
   PROPERTY_2i(QCString,EventFilterFuncRef)
   PROPERTY_2i(bool,Listening)
   PROPERTY_2i(QCString,ListenTo)
   PROPERTY_2i(QCString,InitFuncRef)
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
   PROPERTY_2i(QCString,HelpId1)
   PROPERTY_2i(QCString,HelpId2)
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
   PROPERTY_2i(bool,Cursor)
   PROPERTY_2i(QColor,CursorColor)
   PROPERTY_2i(bool,MoveSelectedCursor)
   PROPERTY_2i(QColor,GridColor)
   PROPERTY_2i(QColor,AxisColor)
   PROPERTY_2i(int,GridXLines)
   PROPERTY_2i(int,GridYLines)
   PROPERTY_2i(int,XPrecision)
   PROPERTY_2i(int,Aequator)
   PROPERTY_2i(int,NullMeridian)
   VAR_REF_2i(Curve0)
   VAR_REF_2i(Curve1)
   VAR_REF_2i(Curve2)
   VAR_REF_2i(Curve3)
   VAR_REF_2i(Curve4)
   VAR_REF_2i(Curve5)
   PROPERTY_2i(QColor,Curve0Color)
   PROPERTY_2i(QColor,Curve1Color)
   PROPERTY_2i(QColor,Curve2Color)
   PROPERTY_2i(QColor,Curve3Color)
   PROPERTY_2i(QColor,Curve4Color)
   PROPERTY_2i(QColor,Curve5Color)
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

public slots:
   virtual void LeftCursorLeft();
   virtual void LeftCursorRight();
   virtual void RightCursorLeft();
   virtual void RightCursorRight();
   virtual void ZoomIn();
   virtual void ZoomOut();
   virtual void ZoomInOut();

public slots:
   void CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
   {
      CheckAppearance(refresh_type, parent_state);
      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }

protected slots:
   virtual void languageChange()
   {
   }

signals:
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);

signals:
   void XStartChanged(QString value);
   void XEndChanged(QString value);
   void XDimChanged(QString value);

   void YStart0Changed(QString value);
   void YStart1Changed(QString value);
   void YStart2Changed(QString value);
   void YStart3Changed(QString value);
   void YStart4Changed(QString value);
   void YStart5Changed(QString value);

   void YEnd0Changed(QString value);
   void YEnd1Changed(QString value);
   void YEnd2Changed(QString value);
   void YEnd3Changed(QString value);
   void YEnd4Changed(QString value);
   void YEnd5Changed(QString value);

   void YMin0Changed(QString value);
   void YMin1Changed(QString value);
   void YMin2Changed(QString value);
   void YMin3Changed(QString value);
   void YMin4Changed(QString value);
   void YMin5Changed(QString value);

   void YMax0Changed(QString value);
   void YMax1Changed(QString value);
   void YMax2Changed(QString value);
   void YMax3Changed(QString value);
   void YMax4Changed(QString value);
   void YMax5Changed(QString value);

   void LeftCurXChanged(QString value);
   void RightCurXChanged(QString value);
   void DiffCurXChanged(QString value);

   void LeftCurVal0Changed(QString value);
   void LeftCurVal1Changed(QString value);
   void LeftCurVal2Changed(QString value);
   void LeftCurVal3Changed(QString value);
   void LeftCurVal4Changed(QString value);
   void LeftCurVal5Changed(QString value);

   void RightCurVal0Changed(QString value);
   void RightCurVal1Changed(QString value);
   void RightCurVal2Changed(QString value);
   void RightCurVal3Changed(QString value);
   void RightCurVal4Changed(QString value);
   void RightCurVal5Changed(QString value);

   void Dimension0Changed(QString value);
   void Dimension1Changed(QString value);
   void Dimension2Changed(QString value);
   void Dimension3Changed(QString value);
   void Dimension4Changed(QString value);
   void Dimension5Changed(QString value);

   void Refreshed(QWidget * graphic);

protected:
   // overloaded qt widget methods
   virtual void mouseMoveEvent(QMouseEvent * e);
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
   virtual void showEvent(QShowEvent * e);
   virtual void resizeEvent(QResizeEvent * e);

public: 
   // GUI related virtual methods
   virtual void View();
   virtual void Notification(ULONG_T event_code) {};
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
   CProcGraphic(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   ~CProcGraphic();
public:
   /// the following methods are used to retrieve coordinate system specific data
   /// this method retrieves the left boundary of the x-coordinate system
   /// this method retrieves the dimension string of the x-coordinate system
   virtual BOOL_T XDimension(QString & value);
   /// this method retrieves the specification of the x-coordinate system
   virtual BOOL_T XSpecification(QString & value);
   /// this method retrieves the left boundary of the x-coordinate system
   virtual BOOL_T XScaleStart(QString & value);
   virtual BOOL_T XScaleStart(DOUBLE_T & value);
   /// this method retrieves the right boundary of the x-coordinate system
   virtual BOOL_T XScaleEnd(QString & value);
   virtual BOOL_T XScaleEnd(DOUBLE_T & value);
   virtual BOOL_T XScaleEnd(int curve_index, QString & value);
   virtual BOOL_T XScaleEnd(int curve_index, DOUBLE_T & value);
   /// this method retrieves the position of the cursor denoted by cursor
   virtual BOOL_T CursorPosition(Cursors cursor, QString & value);
   virtual BOOL_T CursorPosition(Cursors cursor, DOUBLE_T & value);

   /// the following methods are used to retrieve curve specific data
   /// the adressed curve is denoted by the curve index value
   /// this method retrieves the dimension string of the curve denoted by curve_index
   virtual BOOL_T YDimension(int curve_index, QString & value);
   /// this method retrieves the specification of the curve denoted by curve_index
   virtual BOOL_T YSpecification(int curve_index, QString & value);
   /// this method retrieves the bottom boundary of the curve denoted by curve_index
   virtual BOOL_T YScaleStart(int curve_index, QString & value);
   virtual BOOL_T YScaleStart(int curve_index, DOUBLE_T & value);
   /// this method retrieves the top boundary of the curve denoted by curve_index
   virtual BOOL_T YScaleEnd(int curve_index, QString & value);
   virtual BOOL_T YScaleEnd(int curve_index, DOUBLE_T & value);
   /// this method retrieves the minimum value of the curve denoted by curve_index
   /// when restrict_to_view is set only the visible part of the curve is considered
   virtual BOOL_T Min(int curve_index, QString & value, BOOL_T restrict_to_view = false);
   virtual BOOL_T Min(int curve_index, DOUBLE_T & value, BOOL_T restrict_to_view = false);
   /// this method retrieves the maximum value of the curve denoted by curve_index
   /// when restrict_to_view is set only the visible part of the curve is considered
   virtual BOOL_T Max(int curve_index, QString & value, BOOL_T restrict_to_view = false);
   virtual BOOL_T Max(int curve_index, DOUBLE_T & value, BOOL_T restrict_to_view = false);
   /// this method retrieves the value of the curve denoted by curve_index
   /// at the position of the cursor denoted by cursor
   virtual BOOL_T CursorValue(int curve_index, Cursors cursor, QString & value);
   virtual BOOL_T CursorValue(int curve_index, Cursors cursor, DOUBLE_T & value);
   /// this method retrieves the color of the curve denoted by curve_index
   virtual BOOL_T CurveColor(int curve_index, QColor & color);
   /// this method checks a curve for existence (configured and data present)
   virtual BOOL_T CurveExists(int curve_index);
   /// this method retrieves the function of a curve
   virtual BOOL_T Function(int curve_index, ULONG_T & value);
   /// this method retrieves the current function unit of a curve
   virtual BOOL_T FunctionUnit(int curve_index, ULONG_T & value);
   /// this method retrieves the curve id of a curve
   virtual BOOL_T CurveId(int curve_index, ULONG_T & value);

   /// the following methods are used to manipulate coordinate system specific data
   /// this method moves the ccordsystem cursor to the left or right
   virtual BOOL_T MoveCursor(Cursors cursor, Directions direction, int steps = 1);
   /// this method toggles the zoom state of the ccordsystem

   virtual BOOL_T MoveCursor(Cursors cursor, int xpos);

   virtual BOOL_T Zoom();
   virtual BOOL_T SetCursorsAtBeginnAndEnd(); // 210305 HA

   /// the following methods are used to manipulate curve specific data
   /// this method sets y scale end value for the specific curve
   virtual BOOL_T SetYScaleEnd(int curve_index, QString value);
   virtual BOOL_T SetYScaleEnd(int curve_index, DOUBLE_T value);
   
   // this method get the Object valid of the graphic curve
   virtual BOOL_T GetObjectValid(int curve_index);

private:
   QPixmap _DoubleBuffer;
   QRect _DrawRectangle;
   DOUBLE_T _XScaleStart;           /// start value of x scale (world coordinate)
   DOUBLE_T _XScaleEnd;	            /// end value of x scale (world coordinate)
   DOUBLE_T _XScaleEndCurve[MAX_PROC_CURVES];
   ULONG_T _LeftCursorPos;          /// position of left cursor (pixel coordinates)
   ULONG_T _RightCursorPos;         /// position of right cursor (pixel coordinate)
   ULONG_T _LeftZoomPos;           /// left zoom position (pixel coordinate)
   ULONG_T _RightZoomPos;          /// right zoom position (pixe coordinate)
   BUF_T _CurveBuffer[MAX_PROC_CURVES]; // curve buffers
   double _AequatorPos;
   double _NullMeridianPos;
   bool _ZoomState;
   bool _LeftCursorGrabbed;
   bool _RightCursorGrabbed;
   LONG_T _GrabPosition;
protected:
   virtual void PaintAll();
   virtual void PaintGrid(QPainter & painter);
   virtual void PaintCursors(QPainter & painter);
   virtual void PaintCurves(QPainter & painter);
private:
   void InitWidget();
   void PaintCurve(QPainter & painter, ULONG_T index);
   QColor CurveColor(ULONG_T index);
   void FormatValue(ULONG_T precision, QString & text, DOUBLE_T value);
   void EmitAllChanges();
   void EmitLeftCurValChanged(ULONG_T curve_index, ULONG_T precision, double value);
   void EmitRightCurValChanged(ULONG_T curve_index, ULONG_T precision, double value);
   void EmitYStartChanged(ULONG_T curve_index, ULONG_T precision, double value);
   void EmitYEndChanged(ULONG_T curve_index, ULONG_T precision, double value);
   void EmitYMinChanged(ULONG_T curve_index, ULONG_T precision, double value);
   void EmitYMaxChanged(ULONG_T curve_index, ULONG_T precision, double value);
   double GetCurveValue(ULONG_T curve_index, double xpos);

public:
   BOOL_T GetZoomState();
   BOOL_T IsZoomEnabled();
};

#endif


