
#ifndef _ccomposedstack_h_
#define _ccomposedstack_h_

#include "CFrame.h"
#include "CProcGraphic.h"
#ifdef QT4
#include <qstackedwidget.h>
#else
#include <qwidgetstack.h>
#endif

/**!
  * @brief A widget to stack multiple widgets into one stack.
  * <p>
  */
class _CWIDGET_EXPORT_ CComposedStack : public CFrame  
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
   void CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state);
   void RaiseWidget(int id);
   void RaiseWidget(QWidget * widget);
   void PreWidgetShow(QWidget * widget);
   void GraphicRefreshSlot(QWidget * widget);
#ifdef QT4
   void PreWidgetShow(int index);
#endif

protected slots:
   virtual void languageChange()
   {
   }

signals:
   void AboutToShow(int id);
   void AboutToShow(QWidget * widget);
   void GraphicRefreshSignal(QWidget * widget);

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e)
   {
      CFrame::mousePressEvent (e);
   };
   virtual void mouseReleaseEvent(QMouseEvent * e)
   {
      CFrame::mouseReleaseEvent(e);
   };
   virtual void paintEvent(QPaintEvent * e)
   {
      CFrame::paintEvent(e);
   };
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

public:
   CComposedStack(QWidget * parent = 0, const char * name = 0);
   ~CComposedStack();
   QWidget * Widget(int id) const;
   int id(QWidget * widget) const;
   QWidget * VisibleWidget() const;

private:
#ifdef QT4
   QStackedWidget * _Stack;
#else
   QWidgetStack * _Stack;
#endif
   QWidget * _ActGraphic;

private:
#ifdef QT4
   QStackedWidget * SearchStack(QWidget * widget);
#else
   QWidgetStack * SearchStack(QWidget * widget);
#endif
   CProcGraphic * SearchGraphic(QWidget * widget);
   void ConnectGraphicWidgets(QWidget * widget);
};

#endif


