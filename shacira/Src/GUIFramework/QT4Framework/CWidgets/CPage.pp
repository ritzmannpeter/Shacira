
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
class _CWIDGET_EXPORT_ CPage : public CWidget
{
// start 2i generic widget definition

   Q_OBJECT

   // further widget specific properties
   PROPERTY_2i(QByteArray,PageGroup)
//   PROPERTY_2i(QByteArray,PageName)
//   PROPERTY_2i(QString,PageHeadline)
   Q_PROPERTY(QByteArray PageName READ getPageName WRITE setPageName)
   Q_PROPERTY(QString PageHeadline READ getPageHeadline WRITE setPageHeadline)
   PROPERTY_2i(QString,LongPageHeadline)
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

#define ORIGINAL_VERSION
#ifndef ORIGINAL_VERSION
protected:
   QByteArray _pageNameValue;
   QString _pageHeadlineValue;
public:
   // PageName = QObject name
   QByteArray getPageName()
   {
      if (_pageNameValue.isEmpty()) {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
         _pageNameValue.append(objectName());
#else
	     _pageNameValue = objectName().toAscii();
#endif
      }
      return _pageNameValue;
   };
   void setPageName(const QByteArray & text)
   {
      _pageNameValue = text;
      setObjectName(text);
   };
   // PageName = windowTitle
   QString getPageHeadline()
   {
      if (_pageHeadlineValue.isEmpty()) {
	     _pageHeadlineValue = windowTitle();
	  }
      return _pageHeadlineValue;
   };
   void setPageHeadline(const QString & text)
   {
      _pageHeadlineValue = text;
      setWindowTitle(text);
   };
#else
public:
   QByteArray getPageName() const               {return QByteArray(objectName().toStdString().c_str());};     // PageName = QObject name
   void setPageName(const QByteArray text)      {setObjectName(text);};

   QString getPageHeadline() const              {return QString(windowTitle());};       // PageName = windowTitle
   void setPageHeadline(const QString & text)   {setWindowTitle(text);};
#endif
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
   CPage(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
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
   BOOL_T similarSizeAsFramePage();

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


