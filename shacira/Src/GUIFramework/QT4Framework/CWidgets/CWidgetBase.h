
/// PR 28.06.05 - added flag IGNORE_SYNTAX_VALIDATOR
/// PR 24.08.06 - added flag SHOW_MAXIMIZED
/// PR 24.03.07 - generally reworked
/// PR 04.06.13 - added flag SYNC_USER_FUNCTIONS

#ifndef _cwidgetbase_h_
#define _cwidgetbase_h_

#include "qt4port.h"
#include "pluginfactory.h"

#include <qwidget.h>
#include <qobject.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qdatastream.h>
#include <qpainter.h>
#include <qthread.h>

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "guievents.h"
#include "guiops.h"
#include "guisignals.h"
#include "safefunctions.h"

#define OBJ_FLT_EVENT                    1
#define OBJ_FLT_ALARM                    2
#define OBJ_FLT_INFO                     3
#define OBJ_FLT_STATE                    4
#define OBJ_FLT_DATA_CHANGE              5
#define OBJ_FLT_REQUEST                  6
#define OBJ_FLT_JOB_SPEC                 7
#define OBJ_FLT_JOB_ENTRY                8
#define OBJ_FLT_LOCAL_CELL_PROXY         9
#define OBJ_FLT_CORBA_CELL_PROXY         10
#define OBJ_FLT_COS_EVENTCHANNEL_PROXY   11
#define OBJ_FLT_USER_INFO                12
#define OBJ_FLT_PROGRESS                 13
#define OBJ_FLT_PROTOCOL                 14
#define OBJ_FLT_ALL_EVENTS               15
#define ALL_EVENTS                       OBJ_FLT_ALL_EVENTS

class CWidgetBase;
class CAppFrame;
class CPage;
class cCommInterface;
class cSignalManager;
class cEventView;
class cDataView;
class cGuiSignal;
class ApplicationFilter;

// GUI application flags 
#define TOUCH_SCREEN               0x00000001
#define FULL_SCREEN                0x00000002
#define CURSOR_DISABLED            0x00000004
#define NON_STANDARD_BUTTONS       0x00000008
#define REFERENCE_CACHE            0x00000010
#define SHOW_REFERENCES            0x00000020
#define IGNORE_NUMBER_VALIDATION   0x00000040
#define SCROLLABLE_SCREEN          0x00000080
#define SHOW_MAXIMIZED             0x00000100
#define CHG_TXTWIDGET_BGROUNDCOLOR 0x00000200
#define UTF8_ENCODED_INPUT         0x00000400
#define SYNC_USER_FUNCTIONS        0x00000800
#define GUI_FLAG_RESTART           0x00001000
#define USE_GESTURE                0x00002000

// refresh types
#define PROPAGATE_ALL            0x01000000
#define IMMEDIATE_OPERATION      0x02000000

#define CODE_SLOW_REFRESH        0x00000001
#define CODE_FAST_REFRESH        0x00000002
#define CODE_CYCLE_REFRESH       0x00000004
#define CODE_EVENT_REFRESH       0x00000008
#define CODE_DATA_REFRESH        0x00000010
#define CODE_TEXT_REFRESH        0x00000020
#define CODE_BG_DATA_REFRESH     0x00000040

#define IS_SLOW_REFRESH(rt)      (rt & CODE_SLOW_REFRESH)
#define IS_FAST_REFRESH(rt)      (rt & CODE_FAST_REFRESH)
#define IS_CYCLE_REFRESH(rt)     (rt & CODE_CYCLE_REFRESH)
#define IS_DATA_REFRESH(rt)      (rt & CODE_DATA_REFRESH)
#define IS_EVENT_REFRESH(rt)     (rt & CODE_EVENT_REFRESH)
#define IS_TEXT_REFRESH(rt)      (rt & CODE_TEXT_REFRESH)
#define IS_BG_DATA_REFRESH(rt)   (rt & CODE_BG_DATA_REFRESH)

#define GENERAL_REFRESH          ( CODE_SLOW_REFRESH | CODE_FAST_REFRESH \
                                 | CODE_CYCLE_REFRESH | CODE_EVENT_ERFRESH \
                                 | PROPAGATE_ALL | IMMEDIATE_OPERATION)
#define SLOW_REFRESH             (CODE_SLOW_REFRESH)
#define FAST_REFRESH             (CODE_FAST_REFRESH)
#define CYCLE_REFRESH            (CODE_CYCLE_REFRESH)
#define EVENT_REFRESH            (CODE_EVENT_REFRESH)
#define DATA_REFRESH             (CODE_DATA_REFRESH | PROPAGATE_ALL)
#define TEXT_REFRESH             (CODE_TEXT_REFRESH | PROPAGATE_ALL)
#define FORCED_DATA_REFRESH      (CODE_DATA_REFRESH | PROPAGATE_ALL | IMMEDIATE_OPERATION)
#define FORCED_TEXT_REFRESH      (CODE_TEXT_REFRESH | PROPAGATE_ALL | IMMEDIATE_OPERATION)
#define BG_DATA_REFRESH          (CODE_BG_DATA_REFRESH | PROPAGATE_ALL)

#define IS_IMMEDIATE(rt)         (rt & IMMEDIATE_OPERATION)
#define PROPAGATE(rt)            (rt & PROPAGATE_ALL)

#define MAX_ACCESS_GROUPS        8

#define CONSTRUCT_WIDGET \
      _RefreshValue = NoRefresh; \
      _Group0Value = WriteAccess; \
      _Group1Value = WriteAccess; \
      _Group2Value = WriteAccess; \
      _Group3Value = WriteAccess; \
      _Group4Value = WriteAccess; \
      _Group5Value = WriteAccess; \
      _Group6Value = WriteAccess; \
      _Group7Value = WriteAccess;  \
      _EventFilterValue = NoEvents; \
      _ListeningValue = false;

#define TOUCH_SCREEN_ACTIVE() Flag(TOUCH_SCREEN)
#define CHG_TXTWIDGET_BGROUNDCOLOR_ACTIVE() Flag(CHG_TXTWIDGET_BGROUNDCOLOR)

#ifdef QT_PLUGIN

#include <string>
#include <map>
#include <list>

typedef bool BOOL_T;
typedef unsigned char UCHAR_T;
typedef char CHAR_T;
typedef long LONG_T;
typedef unsigned long ULONG_T;
typedef double DOUBLE_T;
typedef const char * CONST_STRING_T;
typedef unsigned char * BUF_T;
typedef float FLOAT_T;
typedef short SHORT_T;
typedef unsigned short USHORT_T;
typedef int INT_T;
typedef unsigned int UINT_T;
typedef std::string STRING_T;
typedef std::list<STRING_T> STRING_LIST_T;

class cTransientObject;
class cInfo;
class cJobSpec;
class cJobEntry;
class cDataChange;
class cAlarm;
class cUserInfo;
class cContext;
class cFuncRef;
class cVarRef;
class cArgument;
class cVariable;
class cDataChangeAdapter;
class cEventAdapter;
class cExtendedObjectRing; 
class cError;
class cNode;
namespace ecl {
   class cMutexSem;
};

#else

#include "FirstHeader.h"
#include "shacira.h"
#include "System/Objects/cTransientObject.h"
#include "System/Objects/cInfo.h"
#include "System/Objects/cJobSpec.h"
#include "System/Objects/cJobEntry.h"
#include "System/Objects/cDataChange.h"
#include "System/Objects/cAlarm.h"
#include "System/Objects/cUserInfo.h"
#include "System/Database/cContext.h"
#include "System/Database/cFuncRef.h"
#include "System/Database/cVarRef.h"
#include "System/Database/cArgument.h"
#include "System/Database/cVariable.h"
#include "Client/Adapters/cDataChangeAdapter.h"
#include "Client/Adapters/cEventAdapter.h"
#include "System/Structs/cExtendedObjectRing.h" 
#include "cNode.h"
#include "base/eb_sema.hpp"
#include "base/eb_err.hpp"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Text/cText.h"

#endif

typedef cTransientObject * TRANSIENT_OBJECT_PTR;
typedef cInfo * INFO_PTR;
typedef cJobSpec * JOB_SPEC_PTR;
/// for v13 compatibility
typedef JOB_SPEC_PTR JOB_SPEC_PTR_T;
typedef cJobEntry * JOB_ENTRY_PTR;
typedef cDataChange * DATA_CHANGE_PTR;
typedef cAlarm * ALARM_PTR;
typedef cUserInfo * USER_INFO_PTR;
typedef cUserInfo * USER_INFO_PTR_T;
typedef cContext * CONTEXT_PTR;
typedef cFuncRef * FUNC_REF_PTR;
typedef cVarRef * VAR_REF_PTR;
typedef cArgument * ARGUMENT_PTR;
typedef cVariable * VARIABLE_PTR;
typedef cDataChangeAdapter * DATA_CHANGE_ADAPTER_PTR;
typedef cEventAdapter * EVENT_ADAPTER_PTR;
typedef cExtendedObjectRing * EXTENDED_OBJECTRING_PTR; 
typedef cNode * NODE_PTR;
typedef ecl::cMutexSem * MUTEX_PTR;
typedef cEventView * EVENT_VIEW_PTR;
typedef cDataView * DATA_VIEW_PTR;
typedef CWidgetBase * CWIDGETBASE_PTR;
typedef QWidget * WIDGET_PTR;
typedef QDataStream & STREAM_T;
typedef QPainter & PAINTER_T;
typedef cError & ERROR_REF_T;

#ifndef QT_PLUGIN

#include "cViewInterface.h"

#endif

#define WMETHOD_PROLOG \
   try {

#ifndef QT_PLUGIN
#define WMETHOD_VOID_EPILOG \
   } catch (cError & e) { \
      if (e.get_ErrCode() != VARIABLE_NULL_MAPPING && \
          e.get_ErrCode() != -VARIABLE_NULL_MAPPING) { \
         ErrorPrintf("unhandled GUI cError exception: %s\n", (CONST_STRING_T)e); \
      } \
      return; \
   } catch (cErrBase & e) { \
         ErrorPrintf("unhandled GUI cErrBase Exception (%d,%d,%d)\n", e.getClass(), e.getCode(), e.getPrefix()); \
      return; \
   } catch (...) { \
      ErrorPrintf("unhandled GUI exception\n"); \
      return; \
   }

#define WMETHOD_RC_EPILOG(rc) \
   } catch (cError & e) { \
      if (e.get_ErrCode() != VARIABLE_NULL_MAPPING && \
          e.get_ErrCode() != -VARIABLE_NULL_MAPPING) { \
         ErrorPrintf("unhandled GUI cError exception: %s\n", (CONST_STRING_T)e); \
      } \
      return rc; \
   } catch (cErrBase & e) { \
      ErrorPrintf("unhandled GUI cErrBase Exception (%d,%d,%d)\n", e.getClass(), e.getCode(), e.getPrefix()); \
      return rc; \
   } catch (...) { \
      ErrorPrintf("unhandled GUI exception\n"); \
      return rc; \
   }
#else
#define WMETHOD_VOID_EPILOG \
   } catch (cError & e) { \
      ErrorPrintf("unhandled GUI cError exception: %s\n", (CONST_STRING_T)e); \
      return; \
   } catch (cErrBase & e) { \
      ErrorPrintf("unhandled GUI cErrBase Exception (%d,%d,%d)\n", e.getClass(), e.getCode(), e.getPrefix()); \
      return; \
   } catch (...) { \
      ErrorPrintf("unhandled GUI exception\n"); \
      return; \
   }

#define WMETHOD_RC_EPILOG(rc) \
   } catch (cError & e) { \
      ErrorPrintf("unhandled GUI cError exception: %s\n", (CONST_STRING_T)e); \
      return rc; \
   } catch (cErrBase & e) { \
      ErrorPrintf("unhandled GUI cErrBase Exception (%d,%d,%d)\n", e.getClass(), e.getCode(), e.getPrefix()); \
      return rc; \
   } catch (...) { \
      ErrorPrintf("unhandled GUI exception\n"); \
      return rc; \
   }
#endif

#ifdef QT_PLUGIN

typedef void * DATA_REFRESH_MAP_PTR;

#else

class cDataRefreshMap;
typedef cDataRefreshMap * DATA_REFRESH_MAP_PTR;
#include "cDataRefreshMap.h"

#endif

typedef std::map<STRING_T,DATA_VIEW_PTR> DATA_VIEW_MAP_T;

enum BackgroundMode { NoBackground,
                      PaletteForeground,
                      PaletteBackground,
                      PaletteButton,
                      PaletteLight,
                      PaletteMidlight,
                      PaletteDark,
                      PaletteMid,
                      PaletteText,
                      PaletteBrightText,
                      PaletteButtonText,
                      PaletteBase,
                      PaletteShadow,
                      PaletteHighlight,
                      PaletteHighlightedText,
                      PaletteLink,
                      PaletteLinkVisited,
                      X11ParentRelative
};

#ifdef QT4

// register custom event types
// const QEvent::Type ParentPaletteChanged = (QEvent::Type)QEvent::registerEventType();
const QEvent::Type ParentPaletteChanged = (QEvent::Type)(QEvent::User + 1);

enum WFlags {
               WType_TopLevel=1,
               WType_Dialog,
               WType_Popup,
               WType_Desktop,
               WStyle_Customize,
               WStyle_NormalBorder,
               WStyle_DialogBorder,
               WStyle_NoBorder,
               WStyle_NoBorderEx,
               WStyle_Title,
               WStyle_SysMenu,
               WStyle_Minimize,
               WStyle_Maximize,
               WStyle_MinMax,
               WStyle_ContextHelp,
               WStyle_Tool
            };
#ifdef doku
Qt::WType_TopLevel - indicates that this widget is a top-level widget, usually with a window-system frame and so on. 
Qt::WType_Dialog - indicates that this widget is a top-level window that should be decorated as a dialog (i.e. typically no maximize or minimize buttons in the title bar). If you want to use it as a modal dialog it should be launched from another window, or have a parent and this flag should be combined with WShowModal. If you make it modal, the dialog will prevent other top-level windows in the application from getting any input. WType_Dialog implies WType_TopLevel. We refer to a top-level window that has a parent as a secondary window. (See also WGroupLeader.) 
Qt::WType_Popup - indicates that this widget is a popup top-level window, i.e. that it is modal, but has a window system frame appropriate for popup menus. WType_Popup implies WType_TopLevel. 
Qt::WType_Desktop - indicates that this widget is the desktop. See also WPaintDesktop below. WType_Desktop implies WType_TopLevel. 
Qt::WStyle_Customize - indicates that the WStyle_* flags should be used to build the window instead of the default flags. 
Qt::WStyle_NormalBorder - gives the window a normal border. This cannot be combined with WStyle_DialogBorder or WStyle_NoBorder. 
Qt::WStyle_DialogBorder - gives the window a thin dialog border. This cannot be combined with WStyle_NormalBorder or WStyle_NoBorder. 
Qt::WStyle_NoBorder - produces a borderless window. Note that the user cannot move or resize a borderless window via the window system. This cannot be combined with WStyle_NormalBorder or WStyle_DialogBorder. On Windows, the flag works fine. On X11, the result of the flag is dependent on the window manager and its ability to understand MOTIF and/or NETWM hints: most existing modern window managers can handle this. With WX11BypassWM, you can bypass the window manager completely. This results in a borderless window that is not managed at all (i.e. no keyboard input unless you call setActiveWindow() manually). 
Qt::WStyle_NoBorderEx - this value is obsolete. It has the same effect as using WStyle_NoBorder. 
Qt::WStyle_Title - gives the window a title bar. 
Qt::WStyle_SysMenu - adds a window system menu. 
Qt::WStyle_Minimize - adds a minimize button. Note that on Windows this has to be combined with WStyle_SysMenu for it to work. 
Qt::WStyle_Maximize - adds a maximize button. Note that on Windows this has to be combined with WStyle_SysMenu for it to work. 
Qt::WStyle_MinMax - is equal to WStyle_Minimize|WStyle_Maximize. Note that on Windows this has to be combined with WStyle_SysMenu to work. 
Qt::WStyle_ContextHelp - adds a context help button to dialogs. 
Qt::WStyle_Tool - makes the window a tool window. A tool window is often a small window with a smaller than usual title bar and decoration, typically used for collections of tool
#endif
#endif

class _CWIDGET_EXPORT_ CWidgetBase
{
friend class cCommInterface;
public:
   // constructor and destructor
   // the constructor receives a to the associated QT widget class
   CWidgetBase(QWidget * qt_widget);
   ~CWidgetBase();
   inline QWidget * Widget() const {return _QWidget;};

protected:
   // type specific intialization
   void InitializeWidget(NODE_PTR node, CONTEXT_PTR context);
   // type specific setup
   void SetupWidget();
   // refresh data of this widget
   void RefreshData();
   // refresh background sensitive data of this widget
   void RefreshBGData();
   int getScaledHeight(QWidget *widget, int baseValue) const;
   int getScaledWidth(QWidget * widget, int baseValue) const;
   int getScaledPointSize(QString &fontName, int baseValue) const;

public:
   // query metods for widget informations
   BOOL_T IsVisible() {return _QWidget->isVisible();};
   static BOOL_T WidgetIsVisible(QWidget * widget) {return widget->isVisible();};
   static QWidget * CustomParent(QWidget * _widget);
   static BOOL_T IsCustomWidget(QWidget * widget);
   static BOOL_T IsCustomContainer(QWidget * widget);
   static BOOL_T IsContainer(QWidget * widget);
   static const QColor VirtualFocusColor();
   static QString StyleSheet(QWidget * widget);

   // information propagation methods
   static void PropagateConnections(QWidget * parent, QWidget * widget, ULONG_T level = 0);
   static void Connect(QWidget * parent, QWidget * widget);
   static void PropagateContext(QWidget * widget, NODE_PTR node, CONTEXT_PTR context, ULONG_T level = 0);
   static void SetupWidgets(QWidget * widget, ULONG_T level = 0);
   static void SetContext(QWidget * widget, NODE_PTR node, CONTEXT_PTR context);
   static void SetupWidget(QWidget * widget);
   static BOOL_T RefreshWidgetData();
   static BOOL_T RefreshWidgetData(QWidget * widget);
   static void InvalidateDataRefreshs(int refresh_type);
   static inline BOOL_T IsRefreshed(VAR_REF_PTR var_ref);
   static inline void SetRefreshed(VAR_REF_PTR var_ref);

   // user function execution
   ULONG_T ExecuteDarkFunc(FUNC_REF_PTR function);
   ULONG_T ExecutePlausFunc(FUNC_REF_PTR function, QString input);
   ULONG_T ExecuteUserFunc(FUNC_REF_PTR function, QString input);
   ULONG_T ExecuteGUISignalFilterFunc(FUNC_REF_PTR function, ULONG_T signal);
   ULONG_T ExecuteGUISlotFunc(FUNC_REF_PTR function, ULONG_T signal, CWidgetBase * sender);
   ULONG_T ExecuteButtonFunc(FUNC_REF_PTR function, BOOL_T sync = true);
   ULONG_T AsyncExec(FUNC_REF_PTR func_ref, ERROR_REF_T e);
   ULONG_T ExecuteButtonFuncs(FUNC_REF_PTR pre_exec_func_ref,
                              FUNC_REF_PTR button_func_ref,
                              BOOL_T sync = false,
                              const QString & dialog_name = NULL,
                              WIDGET_FLAGS_TYPE dialog_flags = 0);
   LONG_T ExecuteValueFunc(FUNC_REF_PTR function, LONG_T value, ULONG_T flags = 0);
   ULONG_T ExecuteEventFilterFunc(FUNC_REF_PTR function, TRANSIENT_OBJECT_PTR object);
   ULONG_T ExecuteInitFunc(FUNC_REF_PTR function);
   
   // activation methods
   // notification directed to the Qt gui thread
   void Notify(ULONG_T event_code = VIEW_DATA);
   void ExecuteNotification(ULONG_T event_code);
   void PostNewValue(const QString & value, ULONG_T id, ULONG_T time_offset,
                     UCHAR_T data_type, ULONG_T size, ULONG_T data_set);
   void PostNewBuf(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                   UCHAR_T data_type, ULONG_T size, ULONG_T data_set);
   void PostNewObject(TRANSIENT_OBJECT_PTR object);
   void PostMessageBox(const QString & caption, const QString & text, QMessageBox::Icon icon,
                       int button0, int button1, int button2,
                       QFont font);
   void PropagateObject(TRANSIENT_OBJECT_PTR object);
   // emit a general signal
   void EmitGUISignal(ULONG_T signal);
   void EmitGUISignal(cGuiSignal * signal);
   // listen to general signals
   void ListenTo(const QString & widget_name);
   // display custom specific error message
   void DisplayError(const QString & err_msg, const QString & param1 = QString(),
                     const QString & param2 = QString(), const QString & param3 = QString(), const QString & param4 = QString());
   static QString ErrorText(ERROR_REF_T e);
   // set the application frame object
   static void SetAppFrame(CAppFrame * app_frame);

public: 
   // GUI related virtual methods
   // notification method of a widget executed by the gui thread
   virtual void Notification(ULONG_T event_code);
   // Notification(event_code = VIEW_DATA)
   virtual void View();
   // language change after original event
   virtual void DelayedLanguageChange();
   static void DelayedLanguageChange(QWidget * widget);

   // general "slot" method
   virtual void GUISignal(ULONG_T signal, CWidgetBase * sender);

   // CCS related virtual methods
   virtual void CCSSetContext(NODE_PTR node, CONTEXT_PTR context);
   virtual void CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object);

   // widget specific virtual methods
   virtual void Setup();

public:
   // CCS related helper methods

   // sync refresh (get) and variable set methods
   BOOL_T CCSGetValue(VAR_REF_PTR var_ref, STRING_T & value);
   BOOL_T CCSSetValue(VAR_REF_PTR var_ref, CONST_STRING_T value, BOOL_T propagate_exception = false);

   // create and remove function references
   void CCSCreateFuncRef(CONST_STRING_T func_spec, FUNC_REF_PTR & func_ref, BOOL_T cached = true);
   void CCSRemoveFuncRef(FUNC_REF_PTR & func_ref);

   // initialize variable references and arguments
   void CCSInitializeVarRef(CONST_STRING_T var_spec, VAR_REF_PTR & var_ref, BOOL_T cached = true);
   void CCSInitializeVarRef(CONST_STRING_T var_spec, VAR_REF_PTR & var_ref, DATA_VIEW_PTR & data_view, ULONG_T id, BOOL_T cached = true);

   void CCSInitializeArgument(CONST_STRING_T arg_spec, ARGUMENT_PTR & arg, DATA_VIEW_PTR & data_view, ULONG_T id);

   // initialize event infrastructure
   void CCSCreateEventLink();
   void CCSRemoveEventLink();

   // create and remove variables references and arguments
   void CCSCreateVarRef(CONST_STRING_T var_spec, VAR_REF_PTR & var_ref, BOOL_T cached);
   void CCSCreateVarRef(CONST_STRING_T var_spec, VAR_REF_PTR & var_ref, DATA_VIEW_PTR & data_view, ULONG_T id, BOOL_T cached);

   // establish and remove callbacks for data change events
   void CCSRegisterVarRef(VAR_REF_PTR var_ref);
   void CCSUnRegisterVarRef(VAR_REF_PTR var_ref);
   void CCSRemoveVarRef(VAR_REF_PTR & var_ref);
   void CCSRemoveVarRef(VAR_REF_PTR & var_ref, DATA_VIEW_PTR & data_view, ULONG_T id);
   void CCSRemoveDataLinks();

private:
   void CCSCreateArgument(CONST_STRING_T arg_spec, ARGUMENT_PTR & arg, DATA_VIEW_PTR & data_view, ULONG_T id);
   void CCSRemoveArgument(ARGUMENT_PTR & argument, DATA_VIEW_PTR & data_view, ULONG_T id);

   void CCSRegisterDataView(DATA_VIEW_PTR data_view);
public:
   void SetRefresh(VAR_REF_PTR var_ref);
   void RemoveRefresh(VAR_REF_PTR var_ref);

public:
   // text related helper methods
   static QString Translate(const QString & text,
                            const QString & context,
                            const QString & p1 = QString(),
                            const QString & p2 = QString(),
                            const QString & p3 = QString(),
                            const QString & p4 = QString());
   static QString SubstParams(const QString & text,
                              const QString & p1 = QString(),
                              const QString & p2 = QString(),
                              const QString & p3 = QString(),
                              const QString & p4 = QString());
   static QString RefText(CONTEXT_PTR context, VAR_REF_PTR var_ref, const QString & language = QString());
   static QString VariableText(CONTEXT_PTR context, VARIABLE_PTR variable,
                               LONG_T i1,
                               LONG_T i2,
                               LONG_T i3,
                               LONG_T i4, const QString & language = QString());
   static QString AlarmText(CONTEXT_PTR context, ALARM_PTR alarm, const QString & language = "default");
   static QString ChangeText(CONTEXT_PTR context, DATA_CHANGE_PTR data_change, const QString & language = "default");

public:
   // language and help related helper methods
   static QString ActLanguage();
   BOOL_T HelpActive();
   void SetHelpIds(BOOL_T show_immediately=true);
   void SetHelpIds(QWidget * widget);
   static void GetActHelpIds(QString & help_id1, QString & help_id2);
   static void GetHelpIds(QWidget * widget, QString & help_id1, QString & help_id2);
   static BOOL_T useEnglishKeyboard();
   void SetBaseHelpId1(QString help_id1) { _BaseHelpId1 = help_id1;};
   void SetBaseHelpId2(QString help_id2) { _BaseHelpId2 = help_id2;};

   static void SetGUIThreadId();
   static int GetGUIThreadId();
   static void SetGUIThread();
   static QThread * GetGUIThread();
   static QThread * GetCurrentThread();
   static bool CheckThread();
   static void SetDefaultGroupId(ULONG_T id);
   static void SetCurrentDataSet(ULONG_T data_set);
   static ULONG_T GetCurrentDataSet();

protected:
   DATA_VIEW_MAP_T _DataViewMap;
   DATA_REFRESH_MAP_PTR _RefreshMap;
   static DATA_REFRESH_MAP_PTR _PendingRefreshMap;
   QString _DarkFuncSpec;
   FUNC_REF_PTR _DarkFuncRef;
   QString _GUISignalFilterFuncSpec;
   FUNC_REF_PTR _GUISignalFilterFuncRef;
   QString _GUISlotFuncSpec;
   FUNC_REF_PTR _GUISlotFuncRef;
   QString _QualifiedName;           // holds a qualified name of the widget
   QString _EventFilterFuncSpec;
   FUNC_REF_PTR _EventFilterFuncRef;
   EVENT_VIEW_PTR _EventView;
   BOOL_T _Listening;
   QString _ListenTo;
   QString _InitFuncSpec;
   FUNC_REF_PTR _InitFuncRef;

   QWidget * _QWidget;    // pointer to QWidget base class
   QString _Name;
   NODE_PTR _Node;
   CONTEXT_PTR _Context;
   BOOL_T _ViewPending;
   QString _BaseHelpId1;
   QString _BaseHelpId2;
   int _GroupAccess[MAX_ACCESS_GROUPS];
#ifdef DEPRECATED_15
   BOOL_T _BackgroundSensitive;
#endif
   ULONG_T _DataSet;
protected:
   int _EventFilter;                  // holds the event filter value

public:
   static CAppFrame * _AppFrame;
   static ULONG_T _DefaultGroupId;
   static NODE_PTR _GlobalNode;
protected:
   static ULONG_T _QtGUIThreadId;
#ifdef QT4
   static QThread * _QtGUIThread;
#endif
   static ULONG_T _CurrentDataSet;
   static QString _ActHelpId1;
   static QString _ActHelpId2;
private:
   static cSignalManager * _SignalManager;
   static cCommInterface * _CommInterface;
   static ApplicationFilter * _ApplicationFilter;

/// appearance functionality integrating user access rights
/// and blanking (dark) functionality

public:
   inline int EventFilter()
   {
#ifndef QT_PLUGIN
      switch (_EventFilter) {
      case OBJ_FLT_EVENT: return OT_EVENT;
      case OBJ_FLT_ALARM: return OT_ALARM;
      case OBJ_FLT_INFO: return OT_INFO;
      case OBJ_FLT_STATE: return OT_STATE;
      case OBJ_FLT_DATA_CHANGE: return OT_DATA_CHANGE;
      case OBJ_FLT_REQUEST: return OT_REQUEST;
      case OBJ_FLT_JOB_SPEC: return OT_JOB_SPEC;
      case OBJ_FLT_JOB_ENTRY: return OT_JOB_ENTRY;
      case OBJ_FLT_LOCAL_CELL_PROXY: return OT_LOCAL_CELL_PROXY;
      case OBJ_FLT_CORBA_CELL_PROXY: return OT_CORBA_CELL_PROXY;
      case OBJ_FLT_COS_EVENTCHANNEL_PROXY: return OT_COS_EVENTCHANNEL_PROXY;
      case OBJ_FLT_USER_INFO: return OT_USER_INFO;
      case OBJ_FLT_PROGRESS: return OT_PROGRESS;
      case OBJ_FLT_PROTOCOL: return OT_PROTOCOL;
      case OBJ_FLT_ALL_EVENTS: return OBJ_FLT_ALL_EVENTS;
      }
#endif
      return 0;
   };
   static inline CAppFrame * AppFrame()
   {
#ifndef QT_PLUGIN
      return _AppFrame;
#endif
      return NULL;
   };
   void CheckAppearance(ULONG_T refresh_type, ULONG_T parent_state);
   ULONG_T GetAppearanceState();
   void Show();
   void Hide();
   static void Hide(WIDGET_PTR widget);
   void Disable();
   void Enable();
   void SetWidgetActive(QWidget * widget, BOOL_T state);
   void SetActive(QWidget * widget, BOOL_T state);
   void SetActive(BOOL_T state);
   void SetGroupAccess(ULONG_T group_id, int access, int level = 0);
   static void SetGroupAccess(QWidget * widget, ULONG_T group_id, int access, BOOL_T track_parents = false, int level = 0);
   static CPage * MyPage(QWidget * widget);
   static CWidgetBase * BaseWidget(QWidget * widget);
   static QString FromUtf8(const QString & text);
   static QString FromLatin(const QString & text);
private:
   ULONG_T CheckWidgetAccess(USER_INFO_PTR user_info);
   int Access(ULONG_T group_id);
   void ShowState();
   void ForceShow();
   void ForceHide();
   void ForceDisable();
   void ForceEnable();
#ifdef QT4
   void SetColors(QObject * object, ULONG_T dataset, const QColor & color);
#endif
public:
   void SetColor(ULONG_T dataset);
   void SetMappedBackgroundColor();
   static void SetMappedBackgroundColor(QWidget * widget);
   void ClearMappedBackgroundColor();
   static void ClearMappedBackgroundColor(QWidget * widget);
protected:
   ULONG_T _DarkState;
   ULONG_T _DirectState;
   ULONG_T _AccessState;
   ULONG_T _AppearanceState;
   ULONG_T _PreviousAppearanceState;
   BOOL_T _IsActive;

public:
   // debug and logging support

#define REFRESH_PROPAGATION       0x000000001
#define CONNECTION_HIERARCHY      0x000000002
#define FUNCTION_EXECUTION        0x000000004
#define FUNCTION_INIT             0x000000008
#define VARIABLE_INIT             0x000000010
#define CONTEXT_SETTINGS          0x000000020
#define CONNECTIONS               0x000000040
#define GUI_INFO                  0x000000080

   static unsigned long _DebugFlags;
   // methods for debugging and error handling
   static void DebugPrintf(unsigned long flags, const char * fmt_str, ...);
   static void WidgetError(const char * fmt_str, ...);
   static void LogInitialize(unsigned long flags);

public:
   // appearance flags
   static void SetFlag(ULONG_T flag);
   static void ResetFlag(ULONG_T flag);
   static BOOL_T Flag(ULONG_T flag);
protected:
   static ULONG_T _Flags;
public:
   QString Name() const;
   QString className() const;
   static QString Name(QWidget * widget);
   static QString className(QWidget * widget);

#ifdef QT4
public:
   void setWFlags(unsigned int flags);
   static Qt::WindowFlags qt4WindowFlags(unsigned int flags);
   void setBackgroundMode(BackgroundMode mode);
   static QColor paletteBackgroundColor(QWidget * widget);
   static void setPaletteBackgroundColor(QWidget * widget, const QColor & color);
   static QColor paletteForegroundColor(QWidget * widget);
   static void setPaletteForegroundColor(QWidget * widget, const QColor & color);
   static QBrush paletteBackgroundBrush(QWidget * widget);
   static QPixmap * paletteBackgroundPixmap(QWidget * widget);
   inline QColor paletteBackgroundColor() const {return paletteBackgroundColor(_QWidget);};
   inline QColor backgroundColor() const {return paletteBackgroundColor(_QWidget);};
   inline void setPaletteBackgroundColor(const QColor & color) {setPaletteBackgroundColor(_QWidget, color);};
   inline QColor paletteForegroundColor() const {return paletteForegroundColor(_QWidget);};
   inline void setPaletteForegroundColor(const QColor & color) {setPaletteForegroundColor(_QWidget, color);};
   inline QBrush paletteBackgroundBrush() const {return paletteBackgroundBrush(_QWidget);};
   inline QPixmap * paletteBackgroundPixmap() const {return paletteBackgroundPixmap(_QWidget);};
   inline QBrush backgroundBrush() const {return paletteBackgroundBrush(_QWidget);};
   inline QPixmap * backgroundPixmap() const {return paletteBackgroundPixmap(_QWidget);};
   QObject * child(const char * objName, const char * inheritsClass = 0, bool recursiveSearch = true);
   QObject * _child(const char * objName, const char * inheritsClass = 0, bool recursiveSearch = true);
   QObject * child(const std::string & objName, const char * inheritsClass = 0, bool recursiveSearch = true);
   QObject * child(const QString & objName, const char * inheritsClass = 0, bool recursiveSearch = true);
#endif
};

#ifdef QT4

inline QColor paletteForegroundColor(QWidget * widget)
{
   return CWidgetBase::paletteForegroundColor(widget);
};
inline void setPaletteForegroundColor(QWidget * widget, const QColor & color)
{
   return CWidgetBase::setPaletteForegroundColor(widget, color);
};
inline QColor paletteBackgroundColor(QWidget * widget)
{
   return CWidgetBase::paletteBackgroundColor(widget);
};
inline void setPaletteBackgroundColor(QWidget * widget, const QColor & color)
{
   return CWidgetBase::setPaletteBackgroundColor(widget, color);
};

#endif

#endif


