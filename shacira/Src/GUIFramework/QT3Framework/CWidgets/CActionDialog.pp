
#ifndef _cactiondialog_h_
#define _cactiondialog_h_

#include "CWidgetBase.h"
#include "CAppFrame.h"

/**!
  * @brief A widget to encapsulate arbitrary Qt dialogs
  * <p>
  */

class CActionDialog : public CWidget
{
// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

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
   virtual void paintEvent(QPaintEvent * e)
   {
      CWidget::paintEvent(e);
   };
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

// end 2i generic widget definition

public slots:
   void CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state);
   void ExecuteFunction();

signals:

public:
   CActionDialog(QWidget * parent, const char * name = 0, WFlags f = 0);
   ~CActionDialog();
   QDialog * Dialog();
   virtual void Reset();
   void SetContext(NODE_PTR node, CONTEXT_PTR context);
   void SetFunction(CWidgetBase * widget, FUNC_REF_PTR func_ref);

protected:
   virtual void Terminated(ULONG_T rc);
   virtual void Terminated(ULONG_T rc, ERROR_REF_T e);

protected:
   cPublicDialog * _Dialog;

private:
   QTimer * _ActionTimer;
   CWidgetBase * _Widget;
   FUNC_REF_PTR _FuncRef;
};

#endif


