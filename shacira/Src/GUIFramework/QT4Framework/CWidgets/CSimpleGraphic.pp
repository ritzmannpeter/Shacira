
#ifndef CSIMPLEGRAPHIC_H
#define CSIMPLEGRAPHIC_H

#include "CCoordSystem.h"
#include <qpixmap.h>
#include <qpainter.h>

#define MAX_XVALUES  10

class _CWIDGET_EXPORT_ CSimpleGraphic : public CCoordSystem
{

// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   Q_ENUMS(ViewModes)
   VAR_REF_2i(XCount)
   VAR_REF_2i(X0)
   VAR_REF_2i(X1)
   VAR_REF_2i(X2)
   VAR_REF_2i(X3)
   VAR_REF_2i(X4)
   VAR_REF_2i(X5)
   VAR_REF_2i(X6)
   VAR_REF_2i(X7)
   VAR_REF_2i(X8)
   VAR_REF_2i(X9)
   VAR_REF_2i(Y0)
   VAR_REF_2i(Y1)
   VAR_REF_2i(Y2)
   VAR_REF_2i(Y3)
   VAR_REF_2i(Y4)
   VAR_REF_2i(Y5)
   VAR_REF_2i(Y6)
   VAR_REF_2i(Y7)
   VAR_REF_2i(Y8)
   VAR_REF_2i(Y9)
   PROPERTY_2i(QColor,CurveColor)
   PROPERTY_2i(ViewModes,ViewMode)
   // end of widget specific properties
public:
   // setter and getter methods of common widget properties
   enum ViewModes {
         Steps = 0,
         Ramps = 1,
         StepsStartAtXMin = 2
   };

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
   CSimpleGraphic(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CSimpleGraphic();

protected:
   LONG_T _XCount;
   DOUBLE_T _XValues[MAX_XVALUES];
   DOUBLE_T _YValues[MAX_XVALUES];

protected:
   virtual void PaintCurves(QPainter & painter);
   void SetXCount();
};

#endif


