
#ifndef _cdirectoryview_h_
#define _cdirectoryview_h_

#include "CWidgetBase.h"
#include <qfilesystemmodel.h>
#include <qsortfilterproxymodel.h>
#include <qtreeview.h>

class FileSystemModel : public QFileSystemModel
{
public:
   FileSystemModel(QObject * parent);
   virtual ~FileSystemModel();
   virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
   virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
};

class FileSystemProxyModel : public QSortFilterProxyModel
{
public:
   FileSystemProxyModel(QObject * parent);
   virtual ~FileSystemProxyModel();
protected:
   virtual bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const;
   bool lessThan(const QModelIndex & left, const QModelIndex & right) const;
};

/**!
  * @brief A widget to display structure of directories.
  * <p>
  */
class _CWIDGET_EXPORT_ CDirectoryView : public QTreeView, public CWidgetBase
{
   Q_OBJECT

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

   VAR_REF_2i(Var)
   Q_ENUMS(TransTypes)

public:
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
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
// this is no container
//      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }
   virtual void Print()
   {
   }


signals:
/*!
 * Qt signal that should be emitted, to check the appearance
 * of the widget. Probably appearance conditions for the 
 * widget have changed.
 */
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      QTreeView::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      QTreeView::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      QTreeView::focusOutEvent(e);
   };
   virtual void keyReleaseEvent(QKeyEvent * e)
   {
      QTreeView::keyReleaseEvent(e);
   };

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
   ATTRIBUTES_2i

public:
   CDirectoryView(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CDirectoryView();

protected:
   FileSystemModel * _model;
   FileSystemProxyModel * _proxy_model;
};

#endif


