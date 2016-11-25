
/** 
 * @file cstatebutton.h
 *
 * @brief Button widget to switch different states
 */

#ifndef CSTATEBUTTON_H
#define CSTATEBUTTON_H

#include <qpushbutton.h>
#include "cwidgetbase.h"
#include "cinput.h"

#define MAX_STATES      5

/**
 * @class CStateButton cstatebutton.h "cstatebutton.h"
 *
 * @brief Button widget to switch different states
 * 
 * A state button switches up to 5 different states
 * The states appear either as image or as text on the
 * on the button surface.
 * With every button state 3 objects are associated:
 *   - a text to appear on the button
 *   - a pixmap to appear on the button
 *   - an integral value to synchronize button states
 *   - with a variable reference
 *
 * This class inherits @b QPushButton, CWidgetBase.
 */
class _CWIDGET_EXPORT_ CStateButton : public QPushButton, public CWidgetBase  
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
   Q_ENUMS(ExecModes)
   PROPERTY_2i(ExecModes,ExecMode)
   PROPERTY_2i(QByteArray,ActionDialog)
   VAR_REF_2i(Var)
   VAR_REF_2i(ShowVar)
   VAR_REF_2i(Show2Var)
   FUNC_REF_2i(PreExecFunc)
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
   enum ExecModes {
         Sync = 0,            ///< button function will be executed synchronous (blocking)
         Async = 1            ///< button function will be executed asynchronous (non blocking)
   };
   /// end of common property definitions of C widgets

   /// further widget specific properties
   FUNC_REF_2i(ButtonFunc)
   FUNC_REF_2i(PlausFunc)
   FUNC_REF_2i(UserFunc)
   FUNC_REF_2i(ValueFunc)

   Q_ENUMS(Modes)
   PROPERTY_2i(Modes,Mode)
   PROPERTY_2i(bool,MouseKeyEnable)

   /// number of states to be used (up to 5)
   PROPERTY_2i(int,StateCount)

   /// properties of state 0
   PROPERTY_2i(QString,State0Text)
   PROPERTY_2i(QPixmap,State0Pixmap)
   PROPERTY_2i(int,State0Value)

   /// properties of state 1
   PROPERTY_2i(QString,State1Text)
   PROPERTY_2i(QPixmap,State1Pixmap)
   PROPERTY_2i(int,State1Value)

   /// properties of state 2
   PROPERTY_2i(QString,State2Text)
   PROPERTY_2i(QPixmap,State2Pixmap)
   PROPERTY_2i(int,State2Value)

   /// properties of state 3
   PROPERTY_2i(QString,State3Text)
   PROPERTY_2i(QPixmap,State3Pixmap)
   PROPERTY_2i(int,State3Value)

   /// properties of state 4
   PROPERTY_2i(QString,State4Text)
   PROPERTY_2i(QPixmap,State4Pixmap)
   PROPERTY_2i(int,State4Value)
   Q_ENUMS(ButtonStyles)
   PROPERTY_2i(ButtonStyles,ButtonStyle)
   // end of widget specific properties
public:
   enum Modes {
      ShowNext = 0,      ///< standard operation pixmap is pixmap of the next state
      ShowCurrent = 1    ///< pixmap is pixmap of the current state
   };
   enum ButtonStyles {
         QtSpecific = 0,      ///< drawing of buttons is not altered
         NoBorders = 1        ///< the widget borders are not drawn
   };

public:
   /// further widget specific getter and setter methods
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
// this is no container
//      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }
   virtual void Print()
   {
   }

protected slots:
   virtual void languageChange()
   {
   }

signals:
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);
   void ButtonFunctionExecuted(ULONG_T result);

protected:
   /// overloaded qt widget methods
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
   virtual void keyReleaseEvent(QKeyEvent * e);
#ifdef QT4
   virtual void paintEvent(QPaintEvent * e);
   virtual void showEvent(QShowEvent * e);
   virtual void hideEvent(QHideEvent * e);
#else
   virtual void drawButton(QPainter * qpPainter);
#endif

public: 
   /// GUI related virtual methods
   virtual void View();
   virtual void Notification(ULONG_T event_code) {};
   virtual void GUIEvent(ULONG_T signal, QWidget * sender) {};
   virtual void DelayedLanguageChange() {};

   /// CCS related virtual methods
   virtual void CCSSetContext(NODE_PTR node, CONTEXT_PTR context);
   virtual void CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object);

signals:
#ifdef QT4
	void stateChanged(int newState);
#endif

protected:
   /// view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition

public:
   CStateButton (QWidget * parent = 0, const char * name = 0);
   ~CStateButton();
#ifdef QT4
   virtual void SetIcon(const QPixmap & pixmap);
#else
   virtual void SetIcon(const QPixmap & pixmap, QIconSet::Size size = QIconSet::Automatic);
#endif
private:
   void ShowState();
protected:
   cInput _Input;
   ULONG_T _PrevIndex;
   ULONG_T _ActIndex;
   LONG_T _ActShowVarRefValue;
   LONG_T _ActShow2VarRefValue;
protected:
   virtual void SaveValue();
   virtual void ResetValue();
   virtual void SetValue(const QString & value);
   virtual QString NewValue();
protected:
   void SetState(ULONG_T state);
   ULONG_T NextStateIndex(ULONG_T act_index);
   ULONG_T StateValue(ULONG_T index);
   QString StateText(ULONG_T index);
   QPixmap & StatePixmap(ULONG_T index);
};

#endif

