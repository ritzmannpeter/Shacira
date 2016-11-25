
#ifndef _cvirtualkeyboard_h_
#define _cvirtualkeyboard_h_

#include "cWidgetBase.h"
#include "cInput.h"
#include "CTextEdit.h"
#include <qframe.h>
#include <qlayout.h>

class cQtKeyboard;
class cQtKeyboardInput;

#define UNDEFINED_KEYBOARD	0
#define ENGLISH_KEYBOARD	1
#define GERMAN_KEYBOARD		2

class _CWIDGET_EXPORT_ CVirtualKeyboard : public QFrame, public CWidgetBase  
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
   FUNC_REF_2i(PlausFunc)
   FUNC_REF_2i(UserFunc)
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
// this is no container
//      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }
   void slotSave();
   void slotReject();
   virtual void Print()
   {
   }

signals:
   void CheckAppearanceSignal(ULONG_T refresh_type, ULONG_T parent_state);
   void Accept();
   void Cancel();

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      QFrame::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      QFrame::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      QFrame::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      QFrame::keyReleaseEvent(e);
   };
   void resizeEvent(QResizeEvent * e);
   void hideEvent(QHideEvent* e);

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

   // widget specific virtual methods
   virtual void Setup();
   virtual bool ContentsChanged();

protected:
   // view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition

public:
   CVirtualKeyboard(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CVirtualKeyboard();

   void CancelInput();
   void ApplyInput();

private:
   void StartInput();
   void SetKeyboard();
   void CreateKeyboard(cQtKeyboard * & keyboard,
                       cQtKeyboardInput * & input,
                       int layout_type);
   void ChangeKeyboard();
   void SetText(QString text);

private slots:
   void slotValidationFailed(const QString &error);
   void slotClearValidationError();

protected:
   QString _Text;
   QString _PrevValue;
   cInput _Input;
   QFrame * _InputFrame;
   QFrame * _KeyboardFrame;
   QVBoxLayout * _Layout;
   QVBoxLayout * _Layout1;
   QVBoxLayout * _Layout2;
   QTextEdit * _TextEdit;
   cQtKeyboard * _GermanKeyboard;
   cQtKeyboard * _EnglishKeyboard;
   cQtKeyboardInput * _GermanKeyboardInput;
   cQtKeyboardInput * _EnglishKeyboardInput;
   ULONG_T _KeyboardType;
   bool _KeyboardChanged;
   bool _FontSizeType;
};

#endif


