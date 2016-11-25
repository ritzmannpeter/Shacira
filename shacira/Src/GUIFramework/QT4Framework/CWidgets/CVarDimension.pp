
#ifndef _cvardimension_h
#define _cvardimension_h

#include "CFixText.h"

class _CWIDGET_EXPORT_ CVarDimension : public CFixText  
{

// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   PROPERTY_2i(QByteArray,Variable)
   // setter and getter methods of common widget properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      CFixText::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      CFixText::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      CFixText::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      CFixText::keyReleaseEvent(e);
   };

public slots:
   void slotSetVariable(const QString variable_name);

public: 
   // GUI related virtual methods
   virtual void View();
   virtual void Notification(ULONG_T event_code) {};
   virtual void GUIEvent(ULONG_T signal, QWidget * sender) {};
   virtual void DelayedLanguageChange()
   {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
       View();
#endif
   };

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
   CVarDimension(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CVarDimension();
private:
   VARIABLE_PTR _Variable;
};

#endif


