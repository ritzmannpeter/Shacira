
#ifndef _cpushbutton_h_
#define _cpushbutton_h_

#include <qpushbutton.h>
#include "CWidgetBase.h"

class _CWIDGET_EXPORT_ CPushButton : public QPushButton, public CWidgetBase  
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
   FUNC_REF_2i(PreExecFunc)
   FUNC_REF_2i(ButtonFunc)
   Q_ENUMS(ButtonStyles)
   Q_PROPERTY(ButtonStyles ButtonStyle READ getButtonStyle WRITE setButtonStyle)
   Q_ENUMS(ExecModes)
   PROPERTY_2i(ExecModes,ExecMode)
   PROPERTY_2i(QByteArray,ActionDialog)
   PROPERTY_2i(bool,DisableParent)
   // end of widget specific properties
public:
   enum ExecModes {
         Sync = 0,            ///< button function will be executed synchronous (blocking)
         Async = 1            ///< button function will be executed asynchronous (non blocking)
   };

   enum ButtonStyles {
         QtSpecific = 0,      ///< drawing of buttons is not altered
         NoBorders = 1        ///< the widget borders are not drawn
   };

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

#if QT_VERSION >= 0x040000
   void setButtonStyle(const ButtonStyles &value);
#else
   void setButtonStyle(const ButtonStyles &value) { _ButtonStyleValue = value; PropertyChanged(); }
#endif
   ButtonStyles getButtonStyle() const { return _ButtonStyleValue; }

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
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);
   void ButtonFunctionExecuted(ULONG_T result);

protected:
   // overloaded qt widget methods
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   virtual bool event(QEvent * e);
#endif

   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void focusInEvent(QFocusEvent * e)
   {
      QPushButton::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      QPushButton::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e);
#ifdef QT4
   QPixmap _pixmap;
   virtual void paintEvent(QPaintEvent * e);
   virtual void showEvent(QShowEvent * e);
   virtual void hideEvent(QHideEvent * e);
#else
   virtual void drawButton(QPainter * qpPainter);
#endif

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

   ButtonStyles _ButtonStyleValue;

public:
   CPushButton(QWidget * parent = 0, const char * name = 0);
   ~CPushButton();
#ifdef QT4
   virtual void SetIcon(const QPixmap & pixmap);
   void setPixmap(const QPixmap & pixmap);
#else
   virtual void SetIcon(const QPixmap & pixmap, QIconSet::Size size = QIconSet::Automatic);
#endif
};

#endif


