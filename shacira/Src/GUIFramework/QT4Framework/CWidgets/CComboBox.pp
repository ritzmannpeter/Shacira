
#ifndef _ccombobox_h_
#define _ccombobox_h_

#include "CWidgetBase.h"
#include <qcombobox.h>
#ifdef QT4
#include <qvector.h>
#else
#include <qvaluevector.h>
#endif
#include "cInput.h"

/**!
  * @brief An input widget derived from QComboBox that allows manipulating CCS variable reference data
  * through a combo box like input widget.
  * <p>
  */

class _CWIDGET_EXPORT_ CComboBox : public QComboBox, public CWidgetBase  
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
   /// end of common property definitions of C widgets

   // further widget specific properties
   VAR_REF_2i(Var)
   FUNC_REF_2i(ButtonFunc)
   FUNC_REF_2i(PlausFunc)
   FUNC_REF_2i(UserFunc)
   FUNC_REF_2i(ValueFunc)
   Q_ENUMS(Modes)
   PROPERTY_2i(Modes,Mode)
   Q_ENUMS(ItemHeights)
   PROPERTY_2i(ItemHeights,ItemHeight)
   PROPERTY_2i(int,Increment)
   PROPERTY_2i(bool,DisableParent)
   // end of widget specific properties
public:
   enum Modes {
      SetIndex = 0,          ///< set value is the index of the current item
      SetText = 1,           ///< set value is the text of the current item
      SetNumericText = 2     ///< set value is the text of the current item
	                         ///< converted to an integer
   };
   enum ItemHeights {
      NormalHeight = 0,      ///< height of an item is determined by font size
      Height24 = 1,          ///< 24 pixel height
      Height32 = 2,          ///< 32 pixel height
      Height38 = 3,          ///< 38 pixel height
      Height40 = 4,          ///< 40 pixel height
      Height48 = 5           ///< 48 pixel height
   };

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
   void clear();
   void CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
   {
      CheckAppearance(refresh_type, parent_state);
// this is no container
//      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }
   void SelectionChanged();
   virtual void Print()
   {
   }

signals:
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      QComboBox::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      QComboBox::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      QComboBox::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      int key = e->key();
      e->ignore();
      QComboBox::keyReleaseEvent(e);
      if (key == Qt::Key_Return || key == Qt::Key_Enter) {
         ExecuteButtonFunc(_ButtonFuncRef); 
      }
   };
   virtual bool event(QEvent * e);
   virtual void popup();

public: 
   // GUI related virtual methods
   virtual void View();
   virtual void Notification(ULONG_T event_code) {};
   virtual void DelayedLanguageChange();

   // CCS related virtual methods
   virtual void CCSSetContext(NODE_PTR node, CONTEXT_PTR context);
   virtual void CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object);
   virtual void SetItemText(int index, const QString & text);
   virtual QString FirstItemText();
   virtual BOOL_T FoundItemText(QString text);

protected:
   // view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition


public:
#ifdef QT4
   CComboBox(QWidget * parent = 0, const char * name = 0);
#else
   CComboBox(bool editable, QWidget * parent = 0, const char * name = 0);
#endif
   ~CComboBox();
   void AdjustItemHeight();
protected:
   cInput _Input;
   QString _PrevValue;
#ifdef QT4
   QVector<QString> _ItemStrings;
#else
   QValueVector<QString> _ItemStrings;
#endif

protected:
   virtual void ResetValue();
   virtual QString NewValue();
   virtual void SetValue(const QString & value);
   long ItemIndex(const QString & text);
   virtual void TranslateItems();
#ifdef QT4
public:
   int currentItem() const;
   void setCurrentItem(int index);
   QString text(int index) const;
   void changeItem(const QPixmap & pixmap, const QString & item_text, int index);
#endif
};

#endif


