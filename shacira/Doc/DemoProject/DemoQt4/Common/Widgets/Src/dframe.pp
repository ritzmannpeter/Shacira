
#ifndef _DFRAME_H_
#define _DFRAME_H_

#include "cframe.h"

class _DWIDGET_EXPORT_ DFrame : public CFrame
{
// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   // end of further widget specific getter and setter methods

public slots:

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e);
   virtual void focusInEvent(QFocusEvent * e)
   {
      CFrame::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      CFrame::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      CFrame::keyReleaseEvent(e);
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
   DFrame(QWidget * parent = 0, const char * name = 0, Qt::WindowFlags f = 0);
   virtual ~DFrame();
};

#endif
