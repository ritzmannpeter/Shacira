
#ifndef _DACTVALUE_H_
#define _DACTVALUE_H_

#include "cactvalue.h"

class _DWIDGET_EXPORT_ DActValue : public CActValue
{
// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   PROPERTY_2i(QColor, AlarmColor)
   PROPERTY_2i(QColor, NotAlarmColor)
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   // end of further widget specific getter and setter methods

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e)
   {
      CActValue::mousePressEvent (e);
   };
   virtual void mouseReleaseEvent(QMouseEvent * e)
   {
      CActValue::mouseReleaseEvent(e);
   };
   virtual void paintEvent(QPaintEvent * e)
   {
      CActValue::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      CActValue::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      CActValue::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      CActValue::keyReleaseEvent(e);
   };

public: 
   // GUI related virtual methods
   virtual void View();
//   virtual void Notification(ULONG_T event_code);
//   virtual void RefreshData();
//   virtual void GUIEvent(ULONG_T signal, QWidget * sender);

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
   DActValue(QWidget * parent = 0, const char * name = 0, Qt::WindowFlags f = 0);
   virtual ~DActValue();
};

#endif
