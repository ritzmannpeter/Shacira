
#ifndef _cstartupform_h
#define _cstartupform_h

#include <qtimer.h>
#include "CWidgetBase.h"
#include "CWidget.h"
#ifndef QT_PLUGIN
#include "FirstHeader.h"
#include "System/Console/cConsole.h"
#include "Client/Adapters/cEventControl.h"
typedef cConsole * CONSOLE_PTR;
class CStartupForm;

class cEventSink: public cEventControl
{
private:
   CStartupForm * _Form;
public:
   cEventSink(CStartupForm * form);
   virtual ~cEventSink();
   virtual void Object(TRANSIENT_OBJECT_PTR object); 
};
typedef cEventSink * EVENT_SINK_PTR;

#else

typedef void * CONSOLE_PTR;
typedef void * EVENT_SINK_PTR;
#endif

#define INFO_MESSAGES	10

class SH_QT_WIDGET_PLUGIN_EXPORT CStartupForm : public CWidget
{
   Q_OBJECT

public:
   /// further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

protected:
   /// overloaded qt widget methods
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
   CStartupForm(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   ~CStartupForm();
   virtual void Refresh();
   virtual void Object(TRANSIENT_OBJECT_PTR object);
   void SetConsole(CONSOLE_PTR console);
   virtual void Info(const QString & info, unsigned int index, BOOL_T refresh);
   void CreateEventSink(EVENT_ADAPTER_PTR adapter);
protected:
   CONSOLE_PTR _Console;
   QString _Infos[INFO_MESSAGES];
public slots:
   void TimerExpired();
private:
   QTimer * _RefreshTimer;
   EVENT_ADAPTER_PTR _EventAdapter;
   EVENT_SINK_PTR _EventSink;
};

#endif


