
#ifndef _cgroupselectbutton_h_
#define _cgroupselectbutton_h_

#include "CToolButton.h"

/**!
  * @brief A tool button widget taht is used to navigate between different shacira information page groups.
  * <p>
  * Property PageGroup associates the button with a set of information pages
  * that share the same group name (specified in the property PageGroup of
  * the CPage widget) and that are visually organized through tabs.
  */
class _CWIDGET_EXPORT_ CGroupSelectButton : public CToolButton
{
   Q_OBJECT

   // further widget specific properties
   PROPERTY_2i(QByteArray,PageGroup)
   PROPERTY_2i(int,GroupPos)
   PROPERTY_2i(QString,Title)
   PROPERTY_2i(QString,Description)
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

signals:
	void GroupSelected(QString group_name);

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      CToolButton::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      CToolButton::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      CToolButton::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      CToolButton::keyReleaseEvent(e);
      int key = e->key();
      e->ignore();
      if (key == Qt::Key_Return || key == Qt::Key_Enter) {
         emit GroupSelected(_PageGroupValue);
      }
   }

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
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object);


protected:
   // view-model properties
   ATTRIBUTES_2i

public:
   CGroupSelectButton(QWidget * parent = 0, const char * name = 0);
   ~CGroupSelectButton();
};

#endif


