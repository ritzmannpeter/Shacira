
#ifndef _cactvalue_h_
#define _cactvalue_h_

#include "CWidgetBase.h"
#include <qlabel.h>

/**!
  * @brief A widget to display the value of a variable reference in textual representeion..
  * <p>
  * The widget cannot be used to manipulate the data of a variable
  * reference (input is restricted in general).
  * If data must be altered a CReqValue widget must be used.
  */
class SH_QT_WIDGET_PLUGIN_EXPORT CActValue : public QLabel, public CWidgetBase  
{
   Q_OBJECT

public:
   Q_ENUMS(EventFilters)
   PROPERTY_2i(QCString,Comment)
   PROPERTY_2i(QCString,QualifiedName)
   PROPERTY_2i(QCString,DarkFuncRef)
   PROPERTY_2i(QCString,GUISlotFuncRef)
   PROPERTY_2i(QCString,GUISignalFilterFuncRef)
   PROPERTY_2i(EventFilters,EventFilter)
   PROPERTY_2i(QCString,EventFilterFuncRef)
   PROPERTY_2i(bool,Listening)
   PROPERTY_2i(QCString,ListenTo)
   PROPERTY_2i(QCString,InitFuncRef)
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
   PROPERTY_2i(QCString,HelpId1)
   PROPERTY_2i(QCString,HelpId2)

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
   Q_ENUMS(FormatTypes)
   PROPERTY_2i(FormatTypes,Format)
   Q_ENUMS(TransTypes)
   PROPERTY_2i(TransTypes,Translation) ///< HA10022006
   PROPERTY_2i(bool,IgnoreNullMapping)

public:
   enum FormatTypes {
         Native = 0,       ///< no formatting is done
         HexaDecimal = 1,  ///< the value is displayed as hexadecimal value if numeric
         Octal = 2,        ///< the value is displayed as octall value if numeric
         Binary = 3,       ///< the value is displayed as binary value if numeric
         Real = 4          ///< the value is displayed as real value if numeric
   };
   enum TransTypes {
         NoTranslation = 0,     ///< no translation
         NormalTranslation = 1, ///< normal translation
         LineTranslation = 2    ///< translate line per line
   };

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
      QLabel::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      QLabel::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      QLabel::focusOutEvent(e);
   };
   virtual void keyReleaseEvent(QKeyEvent * e)
   {
      QLabel::keyReleaseEvent(e);
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
   CActValue(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CActValue();

protected:
   QString _Text;

private:
   QString ParseText(QString parseText, LONG_T textLength);
   QString GetTranslatedText(QString text);
   BOOL_T InitializeVarRef();
};

#endif


