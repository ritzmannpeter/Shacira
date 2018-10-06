
#ifndef _cpage_h_
#define _cpage_h_

#include "CWidgetBase.h"
#include "CAppFrame.h"
#include "CToolButton.h"
class CScrollView;
#include <qpixmap.h>

/**!
  * @brief Central information page widget of the shacira gui framework.
  * <p>
  * A CPage widget is the central container for all informations represented by
  * arbitrary widgets.
  */
class SH_QT_WIDGET_PLUGIN_EXPORT CPage : public CWidget
{
// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   PROPERTY_2i(QCString, PageGroup)
//   PROPERTY_2i(QCString, PageName)
//   PROPERTY_2i(QString, PageHeadline)
   Q_PROPERTY(QCString PageName READ getPageName WRITE setPageName)
   Q_PROPERTY(QString PageHeadline READ getPageHeadline WRITE setPageHeadline)
   PROPERTY_2i(QString, LongPageHeadline)
   PROPERTY_2i(int,PositionInGroup)
   // end of widget specific properties

   // further widget specific properties
   PROPERTY_2i(int,UserFlags)
   PROPERTY_2i(QPixmap,GroupPixmap)
   PROPERTY_2i(QString,SpecificName)
   PROPERTY_2i(QColor,SpecificColor)
   PROPERTY_2i(bool,ScrollView)
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

public:
   QCString getPageName() const                 {return QCString(name());};     // PageName = QObject name
   void setPageName(QCString text)              {setName(text);};

   QString getPageHeadline() const              {return QString(caption());};   // PageName = QObject caption
   void setPageHeadline(QString text)           {setCaption(text);};

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
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

signals:
   void PageShown(CPage * page);

protected:
   virtual void showEvent(QShowEvent * e);

public:
   CPage(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   ~CPage();

   void SetTabWidget(CTabWidget * tab_widget);
   CTabWidget * TabWidget();
   void SetAbsPos(LONG_T position);
   LONG_T GetAbsPos();
   LONG_T GetRelPos();
   void SetSelectButton(CGroupSelectButton * button);
   void Activate();
   void ActivateButton();
   void Leave();
   void Enter();
   BOOL_T IsVisible();

private:
   int _PositionInGroup;                          // Position der Seite innerhalb der Seitengruppe,
   BOOL_T _DataRefreshPending;
   BOOL_T _BGDataRefreshPending;
   BOOL_T _TextRefreshPending;
   CTabWidget * _TabWidget;
   LONG_T _AbsPos;
   CGroupSelectButton * _SelectButton;
   QWidget * _TabContents;

public:
   void SetTabContents(QWidget * widget)
   {
      _TabContents = widget;
   };
   QWidget * TabContents()
   {
      return _TabContents;
   };
};

#endif


