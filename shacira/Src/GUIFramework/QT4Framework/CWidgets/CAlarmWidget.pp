
#ifndef _calarmwidget_h_
#define _calarmwidget_h_

#include "CWidgetBase.h"
#include "listview.h"
#include <qimage.h>

#ifdef QT_PLUGIN
#define ALARM_TABLE_T void*
#else
class AlarmTable;
#define ALARM_TABLE_T AlarmTable*
#endif

class _CWIDGET_EXPORT_ CAlarmWidgetItem : public ListViewItem
{
public:
   CAlarmWidgetItem(ListView * parent, const QString & help_id);
   virtual ~CAlarmWidgetItem();
   QString get_HelpId();
#ifdef QT4
//   virtual void setPixmap(int column, const QPixmap & pixmap);
//   virtual void setPixmap(int column, const QImage & image);
#endif
private:
   QString _help_id;
};

/**!
  * @brief A widget to display alarms hold by the CCS service.
  * as a list with columns for time, severity, alarm text, ...
  * <p>
  */
class _CWIDGET_EXPORT_ CAlarmWidget : public ListView, public CWidgetBase  
{

// start 2i generic widget definition

   Q_OBJECT

   // common property definitions of C widgets
public:
   Q_ENUMS(EventFilters)
   PROPERTY_2i(QByteArray,Comment)
   PROPERTY_2i(QByteArray,QualifiedName)
   PROPERTY_2i(QByteArray,DarkFuncRef)
   PROPERTY_2i(QByteArray,GUISlotFuncRef)
   PROPERTY_2i(QByteArray,GUISignalFilterFuncRef)
   PROPERTY_2i(EventFilters,EventFilter)
   PROPERTY_2i(QByteArray,EventFilterFuncRef)
   PROPERTY_2i(bool,Listening)
   PROPERTY_2i(QByteArray,ListenTo)
   PROPERTY_2i(QByteArray,InitFuncRef)
   Q_ENUMS(AccesTypes)
   PROPERTY_2i(AccesTypes,Group0)
   PROPERTY_2i(AccesTypes,Group1)
   PROPERTY_2i(AccesTypes,Group2)
   PROPERTY_2i(AccesTypes,Group3)
   PROPERTY_2i(AccesTypes,Group4)
   PROPERTY_2i(AccesTypes,Group5)
   PROPERTY_2i(AccesTypes,Group6)
   PROPERTY_2i(AccesTypes,Group7)
   Q_ENUMS(RefreshTypes)
   PROPERTY_2i(RefreshTypes,Refresh)
   PROPERTY_2i(QByteArray,HelpId1)
   PROPERTY_2i(QByteArray,HelpId2)
   Q_ENUMS(SelectionTypes)
   PROPERTY_2i(SelectionTypes,ItemSelectionType)
   // used enum type definitions
public:
   enum EventFilters {
         NoEvents = 0,
         BaseEvent = OBJ_FLT_EVENT,
         Alarm = OBJ_FLT_ALARM,
         Info = OBJ_FLT_INFO,
         State = OBJ_FLT_STATE,
         DataChange = OBJ_FLT_DATA_CHANGE,
         JobSpec = OBJ_FLT_JOB_SPEC,
         JobEntry = OBJ_FLT_JOB_ENTRY,
         Progress = OBJ_FLT_PROGRESS,
         Protocol = OBJ_FLT_PROTOCOL,
         AllEvents = ALL_EVENTS
   };
   enum AccesTypes {
         NoAccess = 0,        ///< no access the widget is not visible
         ReadOnlyAccess = 1,  ///< the widget is shown but input is disabled
         WriteAccess = 2      ///< the widget is shown and input is enabled
   };
   enum RefreshTypes {
         NoRefresh = 0,       ///< no automatic widget refresh
         FastRefresh = 1,     ///< fast widget refresh
         SlowRefresh = 2,     ///< slow widget refresh
         CycleRefresh = 3,    ///< slow widget refresh
         EventRefresh = 4     ///< event based widget refresh
   };
   enum SelectionTypes {
         Standard = 0,        ///< standard item selection
         ChangeHelpId1 = 1    ///< item selection change HelpId1
   };
   /// end of common property definitions of C widgets

   // further widget specific properties
   PROPERTY_2i(int,IconWidth)
   PROPERTY_2i(int,IconHeight)
   PROPERTY_2i(QPixmap,InfoPixmap)
   PROPERTY_2i(QPixmap,WarningPixmap)
   PROPERTY_2i(QPixmap,ErrorPixmap)
   PROPERTY_2i(QPixmap,SeriousErrorPixmap)
   PROPERTY_2i(QString,TimeColText)
   PROPERTY_2i(QString,IconColText)
   PROPERTY_2i(QString,MessageColText)
   PROPERTY_2i(int,TimeColWidth)
   PROPERTY_2i(int,IconColWidth)
   PROPERTY_2i(int,MessageColWidth)
   PROPERTY_2i(int,ColSpacing)
   PROPERTY_2i(int,ColSort)
   PROPERTY_2i(Qt::SortOrder,SortOrder)
   // end of widget specific properties

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

   virtual void Print(STREAM_T stream)
   {
   }
   virtual void Print(PAINTER_T painter)
   {
   }

public slots:
   void CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
   {
      CheckAppearance(refresh_type, parent_state);
	  if (_AppearanceState != elementInvisible) {
         emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
	  }
   }
   virtual void Print()
   {
   }
   void SelectionChanged(ListViewItem * item);

protected slots:
   virtual void languageChange()
   {
   }

signals:
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e)
   {
      ListView::mousePressEvent (e);
   }
   virtual void mouseReleaseEvent(QMouseEvent * e)
   {
      ListView::mouseReleaseEvent(e);
   }
   virtual void paintEvent(QPaintEvent * e)
   {
      ListView::paintEvent(e);
   }
   virtual void focusInEvent(QFocusEvent * e)
   {
      ListView::focusInEvent(e);
   }
   virtual void focusOutEvent(QFocusEvent * e)
   {
      ListView::focusOutEvent(e);
   }
   void keyReleaseEvent(QKeyEvent * e)
   {
      ListView::keyReleaseEvent(e);
   }

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
   CAlarmWidget(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CAlarmWidget();

protected:
   void ShowAlarms();
   void UpdateWidget();
   ULONG_T ItemPos(ListViewItem * item);
protected:
   bool _Invalidated;
   ALARM_TABLE_T _AlarmTable;
private:
   QImage _InfoImage;
   QImage _WarningImage;
   QImage _ErrorImage;
   QImage _SeriousErrorImage;
};

#endif


