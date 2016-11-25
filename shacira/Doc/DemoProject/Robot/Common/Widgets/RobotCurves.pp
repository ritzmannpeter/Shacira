
#ifndef _robotcurves_h_
#define _robotcurves_h_

#include "CWidgetBase.h"
#include "CWidget.h"
#include <qpainter.h>
#include <qpixmap.h>

#define CURVE_COUNT  6

class SH_QT_WIDGET_PLUGIN_EXPORT RobotCurves : public CWidget
{
// start 2i generic widget definition

   Q_OBJECT
   Q_ENUMS(ValueTypes)
   PROPERTY_2i(ValueTypes,ValueType)
   VAR_REF_2i(Curve0)
   VAR_REF_2i(Curve1)
   VAR_REF_2i(Curve2)
   VAR_REF_2i(Curve3)
   VAR_REF_2i(Curve4)
   VAR_REF_2i(Curve5)

public:
   enum ValueTypes {
         Byte = 0,
         Short = 1,
         Long = 2,
         Float = 3,
         Double = 4
   };
   /// end of property definitions

protected:
   /// generated member attributes of property definitions
   ATTRIBUTES_2i

public:
   /// generated set and get methods of property definitions
   METHODS_2i   

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e)
   {
      CWidget::mousePressEvent(e);
   };
   virtual void mouseReleaseEvent(QMouseEvent * e)
   {
      CWidget::mouseReleaseEvent(e);
   };
   virtual void paintEvent(QPaintEvent * e);
   virtual void focusInEvent(QFocusEvent * e)
   {
      CWidget::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      CWidget::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      CWidget::keyReleaseEvent(e);
   };
   void resizeEvent(QResizeEvent * e);

public: 
   // GUI related virtual methods
   virtual void View();
   virtual void Notification(ULONG_T event_code) {};
   virtual void GUIEvent(ULONG_T signal, QWidget * sender) {};
   virtual void DelayedLanguageChange() {};

   // CCS related virtual methods
   virtual void CCSSetContext(NODE_PTR node, CONTEXT_PTR context);
   virtual void CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object)
   {
      CWidget::CCSEvent(object);
   };

protected:
   // view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition

public:
   RobotCurves(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   ~RobotCurves();

protected:
   virtual void PaintAll();
   virtual void PaintBackground(QPainter & painter);
   virtual void PaintGrid(QPainter & painter);
   virtual void PaintAxis(QPainter & painter);
   virtual void PaintCurves(QPainter & painter);
protected:
   QPixmap _DoubleBuffer;
   BUF_T _CurveBuffer[CURVE_COUNT];
   ULONG_T _ValueCount;
   DOUBLE_T _MaxValue;
};

#endif


