
#ifndef _cgraphic_h_
#define _cgraphic_h_

#include "CCoordSystem.h"
#include <qpixmap.h>
#include <qpainter.h>

#define MAX_CURVES		5

/**!
  * @brief A widget to display curve data in a coordinate system.
  */
class SH_QT_WIDGET_PLUGIN_EXPORT CGraphic : public CCoordSystem
{

// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   VAR_REF_2i(LeftCursor)
   VAR_REF_2i(RightCursor)
   VAR_REF_2i(Y0Min)
   VAR_REF_2i(Y1Min)
   VAR_REF_2i(Y2Min)
   VAR_REF_2i(Y3Min)
   VAR_REF_2i(Y4Min)
   VAR_REF_2i(Y0Max)
   VAR_REF_2i(Y1Max)
   VAR_REF_2i(Y2Max)
   VAR_REF_2i(Y3Max)
   VAR_REF_2i(Y4Max)
   VAR_REF_2i(Curve0)
   VAR_REF_2i(Curve1)
   VAR_REF_2i(Curve2)
   VAR_REF_2i(Curve3)
   VAR_REF_2i(Curve4)
   PROPERTY_2i(QColor,Curve0Color)
   PROPERTY_2i(QColor,Curve1Color)
   PROPERTY_2i(QColor,Curve2Color)
   PROPERTY_2i(QColor,Curve3Color)
   PROPERTY_2i(QColor,Curve4Color)
   PROPERTY_2i(QString,Y0Unit)
   PROPERTY_2i(QString,Y1Unit)
   PROPERTY_2i(QString,Y2Unit)
   PROPERTY_2i(QString,Y3Unit)
   PROPERTY_2i(QString,Y4Unit)
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      CCoordSystem::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      CCoordSystem::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      CCoordSystem::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      CCoordSystem::keyReleaseEvent(e);
   };
   void resizeEvent(QResizeEvent * e)
   {
      CCoordSystem::resizeEvent(e);
   };

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
   CGraphic(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   ~CGraphic();

private:
   DOUBLE_T _LeftCursorPos;
   DOUBLE_T _RightCursorPos;
   DOUBLE_T _YMin[MAX_CURVES];
   DOUBLE_T _YMax[MAX_CURVES];
   QString _YMinString[MAX_CURVES];
   QString _YMaxString[MAX_CURVES];
   QString _YScaleStartString[MAX_CURVES];
   QString _YScaleEndString[MAX_CURVES];
   BUF_T _CurveBuffer[MAX_CURVES];
   ULONG_T _CurveCount;

protected:
   virtual void PaintCurves(QPainter & painter);
   virtual void PaintLegend(QPainter & painter);
   virtual void PaintCurveLegend(QPainter & painter);
private:
   void PaintText(QPainter & painter, QRect & rect, QColor color, QString & text);
   void PaintCurve(QPainter & painter, ULONG_T index);
   void ExtendGrid(QPainter & painter);
   QColor CurveColor(ULONG_T index);
   ULONG_T CurveCount();
   void FormatYScale(ULONG_T index,
                     DOUBLE_T yscale_start, DOUBLE_T yscale_end,
                     DOUBLE_T min, DOUBLE_T max);
   void FormatValue(ULONG_T precision, QString & text, DOUBLE_T value);
};

#endif


