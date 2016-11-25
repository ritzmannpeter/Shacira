

/// PR 07.04.05 - substituted stored reference map by a stored reference list
/// PR 08.04.05 - added verbose references
/// PR 10.05.05 - implemented widget initialization and event filter user functions
/// PR 12.05.05 - removed minor bugs in async function execution (handling of return values)
/// PR 13.05.05 - added selective propagation of exceptions in method CCSSetValue
/// PR 24.05.05 - call to ResyncLogoff will is also called in SetHelpIds
///             - second resync version us ing a global event filter via constant USE_CLICK_FILTER
/// PR 31.05.05 - Changed process event resolution in async functions from 100 to 10 ms
/// PR 02.06.05 - exported Qt gui thread id through method GetGUIThreadId
/// PR 28.06.05 - added CSlider, CSpinBox and CProgressBar
///             - first tests for GUI locking mechanism
/// PR 05.07.05 - added message box controled by GUI thread through method PostMessageBox(...)
/// PR 08.09.05 - implemented missing QString based parameter substitution
/// PR 05.10.05 - set initial default group id to 0
/// PR 15.11.05 - supplying GUI user info to async functions
///             - changed AlarmText method (Horst Anselm FM)
/// PR 24.01.06 - calling Refresh(DATA_REFRESH) before startup
/// PR 03.02.06 - new method RefreshWidgetData(QWidget * widget)
/// PR 07.02.06 - filtering new value events due to fore-/background definition
/// PR 24.02.06 - implemented new refresh mechanism that is capable of handling
///               refreshs of dynamic generated variables
/// PR 06.06.06 - added CTime, CDate and CDateTime
/// PR 28.06.06 - Removed file logging for situations when error is displayed on the screen
/// PR 20.07.06 - changes in ::VariableText to really support Unicode fonts (HA, FM)
/// PR 08.11.06 - added date and time to gui error log file
/// PR 18.01.07 - calling CAppFrame::Refresh(...) with parameter delayed = true
///               to enable correct language switching even when CAppFrame
///               is not started: in cCommInterface::GUIEvent(...)
///             - made module v 1.4 compliant (Beep)
/// PR 14.02.07 - Added static method ::SetGroupAccess to enable dynamic changes of access rights
///               in running applications
///             - Added static method ::MyPage to determine the page, an arbitrary
///               widget is placed on
/// PR 15.02.07 - Preparations for simplified CWidgetBase access (can be enabled through USE_WIDGET_MAP)
/// PR 24.03.07 - generally reworked
/// PR 18.10.07 - Added static DelayedLanguageChanged method for arbitrary widgets
/// PR 20.11.07 - Added static methods FromUtf8 and FromLatin that encapsulate QStrng::fromUtf8 andfromLatin
///               These methods check for correct coding in advance of decoding
/// PR 04.08.08 - Setting action dialog inactive before calling ActionDialogTerminate
///               to avoid heap corruptions and access violations when the dialog is deleted in
///               ActionDialogTerminated (bug fix by Horst Anselm FM)
/// PR 30.09.14 - introduced removal data links when a CWidgetBase typed widget is destroyed

#include "CWidgetBase.h"
#include "CWidget.h"
#include "CPage.h"
#include "QT4Framework/uiupdate.h"

#ifdef QT_PLUGIN

#define UNEXPECTED_BRANCH()

#else

#define UNEXPECTED_BRANCH() ErrorPrintf("unexpected branch line %d in file %s\n");

#include <qtooltip.h>
#include <qcolor.h>
#include <qmessagebox.h>
#include <qobject.h>
#ifndef QT4
#include <qobjectlist.h>
#endif
#include "CWidgetBase.h"
#include "CAppFrame.h"
#include "CWidget.h"
#include "CFrame.h"
#include "CGroupBox.h"
#include "CFixText.h"
#include "CInfoLabel.h"
#include "CProtocolWindow.h"
#include "CTabWidget.h"
#include "CToolButton.h"
#include "CGroupSelectButton.h"
#include "CPushButton.h"
#include "CStateButton.h"
#include "CRadioButton.h"
#include "CCheckBox.h"
#include "CComboBox.h"
#include "CTable.h"
#include "CActValue.h"
#include "CListView.h"
#include "CReqValue.h"
#include "CVideo.h"
#include "CSimpleGraphic.h"
#include "CGraphicsView.h"
#include "CGraphic.h"
#include "CProcGraphic.h"
#include "CRingGraphic.h"
#include "CButtonGroup.h"
#include "CAlarmWidget.h"
#include "CTextEdit.h"
#include "CScrollBar.h"
#include "CVirtualKeyboard.h"
#include "CCoordSystem.h"
#include "CDirectory.h"
#include "CComposedStack.h"
#include "CSlider.h"
#include "CSpinBox.h"
#include "CProgressBar.h"
#include "CTime.h"
#include "CDate.h"
#include "CDateTime.h"
#include "cSignalManager.h"
#include "cAsyncFunction.h"
#include "cWidgetMap.h"
#include "CCompListView.h"
#include "cWidgetComm.h"
#include "CWidgetStack.h"
#include "CComposedStack.h"
#include "CTabWidget.h"
#include "CFrame.h"
#include "CFixText.h"
#include "CInfoLabel.h"
#include "CProtocolWindow.h"
#include "CGroupBox.h"
#include "CButtonGroup.h"
#include "CActValue.h"
#include "CListView.h"
#include "CReqValue.h"
#include "CToolButton.h"
#include "CPushButton.h"
#include "CStateButton.h"
#include "CRadioButton.h"
#include "CCheckBox.h"

#ifndef QT4
#include "CPublicDialog.h"
#endif
#include "CActionDialog.h"
#include "cCommInterface.h"
#include "ApplicationFilter.h"
#include "cGuiEvents.h"
#include "cViewInterface.h"
#include "CWidgetStack.h"

#endif

#ifdef QT4
#ifndef QT_PLUGIN
#include <map>
using namespace std;
typedef map<QWidget*,QPalette> PALETTE_MAP_T;
class PaletteMap
{
public:
   QPalette Palette(QWidget * widget) const
   {
      PALETTE_MAP_T::const_iterator i = _PMap.find(widget);
      if (i != _PMap.end()) {
         return (*i).second;
      }
      return QPalette();
   };
   void SetPalette(QWidget * widget, const QPalette & palette)
   {
      _PMap[widget] = palette;
   };
   void ClearBackgroundColor(QWidget * widget)
   {
      PALETTE_MAP_T::const_iterator i = _PMap.find(widget);
      if (i != _PMap.end()) {
         return;
      }
      _PMap[widget] = QPalette();
   };
   int Size() const
   {
      int s = _PMap.size();
      return s;
   };
protected:
   PALETTE_MAP_T _PMap;
};
static PaletteMap _PaletteMap;
#endif
#endif

ULONG_T CWidgetBase::_DebugFlags = 0;
ULONG_T CWidgetBase::_Flags = 0;
CAppFrame * CWidgetBase::_AppFrame = NULL;
ULONG_T CWidgetBase::_DefaultGroupId = 0;
NODE_PTR CWidgetBase::_GlobalNode = NULL;
ULONG_T CWidgetBase::_QtGUIThreadId = 0;
QThread * CWidgetBase::_QtGUIThread = NULL;
ULONG_T CWidgetBase::_CurrentDataSet = 0;
QString CWidgetBase::_ActHelpId1 = "";
QString CWidgetBase::_ActHelpId2 = "";
cSignalManager * CWidgetBase::_SignalManager = NULL;
DATA_REFRESH_MAP_PTR CWidgetBase::_PendingRefreshMap = NULL;
cCommInterface * CWidgetBase::_CommInterface = NULL;
ApplicationFilter * CWidgetBase::_ApplicationFilter = NULL;

#ifdef TEST_SUPPORT
// some usefull methods for tests

inline bool isWidget(const CWidgetBase * baseWidget, const QString widgetName)
{
    QString name = baseWidget->Name();
    return (name == widgetName);
}

inline bool isPlusMachineState(const CWidgetBase * baseWidget)
{
    return isWidget(baseWidget, "MachineState2");
}

inline bool isMachineState(const CWidgetBase * baseWidget)
{
    return isWidget(baseWidget, "MaschineState");
}

inline bool isWidget(const QWidget * widget, const QString widgetName)
{
    QString name = widget->objectName();
    return (name == widgetName);
}

inline bool isPlusMachineState(const QWidget * widget)
{
    return isWidget(widget, "MachineState2");
}

inline bool isMachineState(const QWidget * widget)
{
    return isWidget(widget, "MaschineState");
}

#endif

CWidgetBase::CWidgetBase(QWidget * qt_widget)
{
   _QWidget = qt_widget;
   _Name = Name();
   _Node = NULL;
   _Context = NULL;
   _DarkFuncRef = NULL;
   _GUISignalFilterFuncRef = NULL;
   _GUISlotFuncRef = NULL;
   _EventFilterFuncRef = NULL;
   _InitFuncRef = NULL;
   _EventFilter = 0;
   _EventView = NULL;
   _Listening = false;
   _ViewPending = true;
#ifdef DEPRECATED_15
   _BackgroundSensitive = false;
#endif
   _DataSet = 0;
#ifndef QT4
   _OrgBackgroundColor = _QWidget->paletteBackgroundColor();
#endif
   _DarkState = elementFree;
   _DirectState = elementFree;
   _AccessState = elementFree;
   _AppearanceState = elementFree;
   _PreviousAppearanceState = elementFree;
   _IsActive = true;
   _RefreshMap = NULL;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (Flag(CURSOR_DISABLED)) {
      qt_widget->setCursor(Qt::BlankCursor);
   }
   if (_ApplicationFilter == NULL) {
      _ApplicationFilter = new ApplicationFilter;

      BOOL_T useApplicationFilterStyleSheet = true;
      cResources::GetOption("UseApplicationFilterStyleSheet", useApplicationFilterStyleSheet);
      _ApplicationFilter->setUseApplicationStyleSheet(useApplicationFilterStyleSheet);

      qApp->installEventFilter(_ApplicationFilter);
   }
   if (_SignalManager == NULL) {
      _SignalManager = new cSignalManager;
   }
   if (_CommInterface == NULL) {
      _CommInterface = new cCommInterface;
   }
   if (_PendingRefreshMap == NULL) {
      _PendingRefreshMap = new cDataRefreshMap;
   }
   CWidgetMap::SetBaseWidget(_QWidget, this);
WMETHOD_VOID_EPILOG
#endif
}

CWidgetBase::~CWidgetBase ( ) 
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSRemoveEventLink();
   CCSRemoveDataLinks();
WMETHOD_VOID_EPILOG
#endif
}

#define MAX_STATE(max, s1,s2,s3) \
   if (s1 >= s2 && s1 >= s3) { \
      max = s1; \
   } else if (s2 >= s3) { \
      max = s2; \
   } else { \
      max = s3; \
   }

#define INIT_WIDGET(type) \
      type * w = (type*)_QWidget; \
      _GroupAccess[0] = w->_Group0Value; \
      _GroupAccess[1] = w->_Group1Value; \
      _GroupAccess[2] = w->_Group2Value; \
      _GroupAccess[3] = w->_Group3Value; \
      _GroupAccess[4] = w->_Group4Value; \
      _GroupAccess[5] = w->_Group5Value; \
      _GroupAccess[6] = w->_Group6Value; \
      _GroupAccess[7] = w->_Group7Value; \
      _BaseHelpId1 = w->_HelpId1Value; \
      _BaseHelpId2 = w->_HelpId2Value; \
      _DarkFuncSpec = w->_DarkFuncRefValue; \
      _GUISignalFilterFuncSpec = w->_GUISignalFilterFuncRefValue; \
      _GUISlotFuncSpec = w->_GUISlotFuncRefValue; \
      _InitFuncSpec = w->_InitFuncRefValue; \
      _QualifiedName = w->_QualifiedNameValue; \
      _Listening = w->_ListeningValue; \
      _ListenTo = w->_ListenToValue; \
      _EventFilter = w->_EventFilterValue; \
      _EventFilterFuncSpec = w->_EventFilterFuncRefValue; \
      w->CCSSetContext(node, context);

#define EXECUTE_WIDGET_INIT(type) \
      type * w = (type*)_QWidget; \
      w->Setup(); \
      if (_InitFuncRef != NULL) { \
         if (w->ExecuteInitFunc(_InitFuncRef) == actionDisableDarkFunction) { \
            if (_DarkFuncRef) { \
               InfoPrintf("dark function %s on widget %s disabled\n", CONST_STRING(_DarkFuncSpec), CONST_STRING(Name(w))); \
               _DarkFuncSpec = ""; \
               _DarkFuncRef = NULL; \
            } \
         } \
      }

void CWidgetBase::InitializeWidget(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Node = node;
   _Context = context;
   if (_QWidget->inherits("CWidgetStack")) {
      INIT_WIDGET(CWidgetStack)
   } else if (_QWidget->inherits("CComposedStack")) {
      INIT_WIDGET(CComposedStack)
   } else if (_QWidget->inherits("CTabWidget")) {
      INIT_WIDGET(CTabWidget)
   } else if (_QWidget->inherits("CFrame")) {
      INIT_WIDGET(CFrame)
   } else if (_QWidget->inherits("CFixText")) {
      INIT_WIDGET(CFixText)
   } else if (_QWidget->inherits("CInfoLabel")) {
      INIT_WIDGET(CInfoLabel)
   } else if (_QWidget->inherits("CProtocolWindow")) {
      INIT_WIDGET(CProtocolWindow)
   } else if (_QWidget->inherits("CGroupBox")) {
      INIT_WIDGET(CGroupBox)
   } else if (_QWidget->inherits("CButtonGroup")) {
      INIT_WIDGET(CButtonGroup)
   } else if (_QWidget->inherits("CActValue")) {
      INIT_WIDGET(CActValue)
   } else if (_QWidget->inherits("CListView")) {
      INIT_WIDGET(CListView)
   } else if (_QWidget->inherits("CReqValue")) {
      INIT_WIDGET(CReqValue)
   } else if (_QWidget->inherits("CToolButton")) {
      INIT_WIDGET(CToolButton)
   } else if (_QWidget->inherits("CPushButton")) {
      INIT_WIDGET(CPushButton)
   } else if (_QWidget->inherits("CStateButton")) {
      INIT_WIDGET(CStateButton)
   } else if (_QWidget->inherits("CRadioButton")) {
      INIT_WIDGET(CRadioButton)
   } else if (_QWidget->inherits("CCheckBox")) {
      INIT_WIDGET(CCheckBox)
   } else if (_QWidget->inherits("CComboBox")) {
      INIT_WIDGET(CComboBox)
   } else if (_QWidget->inherits("CTable")) {
      INIT_WIDGET(CTable)
   } else if (_QWidget->inherits("CGraphicsView")) {
      INIT_WIDGET(CGraphicsView)
   } else if (_QWidget->inherits("CProcGraphic")) {
      INIT_WIDGET(CProcGraphic)
   } else if (_QWidget->inherits("CRingGraphic")) {
      INIT_WIDGET(CRingGraphic)
   } else if (_QWidget->inherits("CCoordSystem")) {
      INIT_WIDGET(CCoordSystem)
   } else if (_QWidget->inherits("CVideo")) {
      INIT_WIDGET(CVideo)
   } else if (_QWidget->inherits("CAlarmWidget")) {
      INIT_WIDGET(CAlarmWidget)
   } else if (_QWidget->inherits("CTextEdit")) {
      INIT_WIDGET(CTextEdit)
   } else if (_QWidget->inherits("CScrollBar")) {
      INIT_WIDGET(CScrollBar)
   } else if (_QWidget->inherits("CSlider")) {
      INIT_WIDGET(CSlider)
   } else if (_QWidget->inherits("CSpinBox")) {
      INIT_WIDGET(CSpinBox)
   } else if (_QWidget->inherits("CProgressBar")) {
      INIT_WIDGET(CProgressBar)
   } else if (_QWidget->inherits("CTime")) {
      INIT_WIDGET(CTime)
   } else if (_QWidget->inherits("CDate")) {
      INIT_WIDGET(CDate)
   } else if (_QWidget->inherits("CDateTime")) {
      INIT_WIDGET(CDateTime)
   } else if (_QWidget->inherits("CVirtualKeyboard")) {
      INIT_WIDGET(CVirtualKeyboard)
   } else if (_QWidget->inherits("CWidget")) {
      INIT_WIDGET(CWidget)
   } else {
      QString classname = className();
      UNEXPECTED_BRANCH()
   }
   if (!_DarkFuncSpec.isEmpty()) {
      CCSCreateFuncRef(CONST_STRING(_DarkFuncSpec), _DarkFuncRef, true);
   }
   if (!_GUISignalFilterFuncSpec.isEmpty()) {
      CCSCreateFuncRef(CONST_STRING(_GUISignalFilterFuncSpec), _GUISignalFilterFuncRef, true);
   }
   if (!_InitFuncSpec.isEmpty()) {
      CCSCreateFuncRef(CONST_STRING(_InitFuncSpec), _InitFuncRef, true);
   }
   if (!_EventFilterFuncSpec.isEmpty()) {
      CCSCreateFuncRef(CONST_STRING(_EventFilterFuncSpec), _EventFilterFuncRef, true);
   }
   CCSCreateEventLink();
   if (_Listening) {
      if (!_ListenTo.isEmpty()) {
         CCSCreateFuncRef(CONST_STRING(_GUISlotFuncSpec), _GUISlotFuncRef, true);
         ListenTo(_ListenTo);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetupWidget()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_QWidget->inherits("CWidgetStack")) {
      EXECUTE_WIDGET_INIT(CWidgetStack)
   } else if (_QWidget->inherits("CComposedStack")) {
      EXECUTE_WIDGET_INIT(CComposedStack)
   } else if (_QWidget->inherits("CTabWidget")) {
      EXECUTE_WIDGET_INIT(CTabWidget)
   } else if (_QWidget->inherits("CFrame")) {
      EXECUTE_WIDGET_INIT(CFrame)
   } else if (_QWidget->inherits("CFixText")) {
      EXECUTE_WIDGET_INIT(CFixText)
   } else if (_QWidget->inherits("CInfoLabel")) {
      EXECUTE_WIDGET_INIT(CInfoLabel)
   } else if (_QWidget->inherits("CProtocolWindow")) {
      EXECUTE_WIDGET_INIT(CProtocolWindow)
   } else if (_QWidget->inherits("CGroupBox")) {
      EXECUTE_WIDGET_INIT(CGroupBox)
   } else if (_QWidget->inherits("CButtonGroup")) {
      EXECUTE_WIDGET_INIT(CButtonGroup)
   } else if (_QWidget->inherits("CActValue")) {
      EXECUTE_WIDGET_INIT(CActValue)
   } else if (_QWidget->inherits("CListView")) {
      EXECUTE_WIDGET_INIT(CListView)
   } else if (_QWidget->inherits("CReqValue")) {
      EXECUTE_WIDGET_INIT(CReqValue)
   } else if (_QWidget->inherits("CToolButton")) {
      EXECUTE_WIDGET_INIT(CToolButton)
   } else if (_QWidget->inherits("CPushButton")) {
      EXECUTE_WIDGET_INIT(CPushButton)
   } else if (_QWidget->inherits("CStateButton")) {
      EXECUTE_WIDGET_INIT(CStateButton)
   } else if (_QWidget->inherits("CRadioButton")) {
      EXECUTE_WIDGET_INIT(CRadioButton)
   } else if (_QWidget->inherits("CCheckBox")) {
      EXECUTE_WIDGET_INIT(CCheckBox)
   } else if (_QWidget->inherits("CComboBox")) {
      EXECUTE_WIDGET_INIT(CComboBox)
   } else if (_QWidget->inherits("CTable")) {
      EXECUTE_WIDGET_INIT(CTable)
   } else if (_QWidget->inherits("CGraphicsView")) {
      EXECUTE_WIDGET_INIT(CGraphicsView)
   } else if (_QWidget->inherits("CProcGraphic")) {
      EXECUTE_WIDGET_INIT(CProcGraphic)
   } else if (_QWidget->inherits("CRingGraphic")) {
      EXECUTE_WIDGET_INIT(CRingGraphic)
   } else if (_QWidget->inherits("CCoordSystem")) {
      EXECUTE_WIDGET_INIT(CCoordSystem)
   } else if (_QWidget->inherits("CVideo")) {
      EXECUTE_WIDGET_INIT(CVideo)
   } else if (_QWidget->inherits("CAlarmWidget")) {
      EXECUTE_WIDGET_INIT(CAlarmWidget)
   } else if (_QWidget->inherits("CTextEdit")) {
      EXECUTE_WIDGET_INIT(CTextEdit)
   } else if (_QWidget->inherits("CScrollBar")) {
      EXECUTE_WIDGET_INIT(CScrollBar)
   } else if (_QWidget->inherits("CSlider")) {
      EXECUTE_WIDGET_INIT(CSlider)
   } else if (_QWidget->inherits("CSpinBox")) {
      EXECUTE_WIDGET_INIT(CSpinBox)
   } else if (_QWidget->inherits("CProgressBar")) {
      EXECUTE_WIDGET_INIT(CProgressBar)
   } else if (_QWidget->inherits("CTime")) {
      EXECUTE_WIDGET_INIT(CTime)
   } else if (_QWidget->inherits("CDate")) {
      EXECUTE_WIDGET_INIT(CDate)
   } else if (_QWidget->inherits("CDateTime")) {
      EXECUTE_WIDGET_INIT(CDateTime)
   } else if (_QWidget->inherits("CVirtualKeyboard")) {
      EXECUTE_WIDGET_INIT(CVirtualKeyboard)
   } else if (_QWidget->inherits("CWidget")) {
      EXECUTE_WIDGET_INIT(CWidget)
   } else {
      QString classname = className();
      UNEXPECTED_BRANCH()
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::InvalidateDataRefreshs(int refresh_type)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _PendingRefreshMap->Clear();
WMETHOD_VOID_EPILOG
#endif
}

BOOL_T CWidgetBase::IsRefreshed(VAR_REF_PTR var_ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _PendingRefreshMap->IsRefreshed(var_ref);
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

void CWidgetBase::SetRefreshed(VAR_REF_PTR var_ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _PendingRefreshMap->SetRefreshed(var_ref);
WMETHOD_VOID_EPILOG
#endif
}

// query metods for widget informations

QWidget * CWidgetBase::CustomParent(QWidget * _widget)
{
   QObject * parent = _widget->parent();
   while (parent != NULL) {
      if (parent->isWidgetType()) {
         QWidget * widget = (QWidget*)parent;
         if (IsCustomWidget(widget)) {
            return widget;
         }
      }
      parent = parent->parent();
   }
   return NULL;
}

BOOL_T CWidgetBase::IsCustomWidget(QWidget * widget)
{
#ifndef QT_PLUGIN
   if (widget->inherits("CPage")) return true;
   if (widget->inherits("CAppFrame")) return true;
   if (widget->inherits("CFixText")) return true;
   if (widget->inherits("CInfoLabel")) return true;
   if (widget->inherits("CProtocolWindow")) return true;
   if (widget->inherits("CReqValue")) return true;
   if (widget->inherits("CActValue")) return true;
   if (widget->inherits("CListView")) return true;
   if (widget->inherits("CCompListView")) return true;
   if (widget->inherits("CToolButton")) return true;
   if (widget->inherits("CGroupSelectButton")) return true;
   if (widget->inherits("CPushButton")) return true;
   if (widget->inherits("CStateButton")) return true;
   if (widget->inherits("CButtonGroup")) return true;
   if (widget->inherits("CRadioButton")) return true;
   if (widget->inherits("CCheckBox")) return true;
   if (widget->inherits("CFrame")) return true;
   if (widget->inherits("CGroupBox")) return true;
   if (widget->inherits("CTabWidget")) return true;
   if (widget->inherits("CWidget")) return true;
   if (widget->inherits("CWidgetStack")) return true;
   if (widget->inherits("CComposedStack")) return true;
   if (widget->inherits("CCoordSystem")) return true;
   if (widget->inherits("CDirectory")) return true;
   if (widget->inherits("CSimpleGraphic")) return true;
   if (widget->inherits("CGraphic")) return true;
   if (widget->inherits("CGraphicsView")) return true;
   if (widget->inherits("CProcGraphic")) return true;
   if (widget->inherits("CRingGraphic")) return true;
   if (widget->inherits("CVideo")) return true;
   if (widget->inherits("CComboBox")) return true;
   if (widget->inherits("CTable")) return true;
   if (widget->inherits("CStartupForm")) return true;
   if (widget->inherits("CAlarmWidget")) return true;
   if (widget->inherits("CTextEdit")) return true;
   if (widget->inherits("CScrollBar")) return true;
   if (widget->inherits("CSlider")) return true;
   if (widget->inherits("CSpinBox")) return true;
   if (widget->inherits("CProgressBar")) return true;
   if (widget->inherits("CTime")) return true;
   if (widget->inherits("CDate")) return true;
   if (widget->inherits("CDateTime")) return true;
   if (widget->inherits("CVirtualKeyboard")) return true;
#endif
   return false;
}

BOOL_T CWidgetBase::IsCustomContainer(QWidget * widget)
{
#ifndef QT_PLUGIN
   if (widget->inherits ("CAppFrame")) return true;
   if (widget->inherits ("CPage")) return true;
   if (widget->inherits ("CFrame")) return true;
   if (widget->inherits ("CGroupBox")) return true;
   if (widget->inherits ("CTabWidget")) return true;
   if (widget->inherits ("CWidget")) return true;
   if (widget->inherits ("CWidgetStack")) return true;
   if (widget->inherits ("CComposedStack")) return true;
   if (widget->inherits ("CButtonGroup")) return true;
   if (widget->inherits ("CProcGraphic")) return true;
   if (widget->inherits ("CRingGraphic")) return true;
#endif
   return false;
}

BOOL_T CWidgetBase::IsContainer(QWidget * widget)
{
#ifndef QT_PLUGIN
   if (widget->inherits ("QFrame")) return true;
   if (widget->inherits ("QGroupBox")) return true;
   if (widget->inherits ("QVBoxLayout")) return true;
   if (widget->inherits ("QHBoxLayout")) return true;
#endif
   return IsCustomContainer(widget);
}

const QColor CWidgetBase::VirtualFocusColor()
{
#ifndef QT_PLUGIN
   if (_AppFrame != NULL) {
      return _AppFrame->getVirtualFocusColor();
   }
#endif
   return Qt::white;
}

QString CWidgetBase::StyleSheet(QWidget * widget)
{
#ifndef QT_PLUGIN
   if (_AppFrame != NULL) {
      return _AppFrame->StyleSheet(widget);
   }
#endif
   return QString();
}

// information propagation methods

void CWidgetBase::PropagateConnections(QWidget * parent, QWidget * widget, ULONG_T level)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
#ifdef QT4
   const QObjectList children = widget->children();
   QObjectList::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * object = (*i);
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (IsCustomWidget(widget)) {
            if (IsCustomWidget(child)) {
               Connect(widget, child);
               PropagateConnections(widget, child, level + 1);
            } else {
               PropagateConnections(widget, child, level + 1);
            }
         } else {
            if (IsCustomWidget(child)) {
               if (parent != NULL &&
                  IsCustomWidget(parent)) {
                   Connect(parent, child);
               }
               PropagateConnections(parent, child, level + 1);
            } else {
               PropagateConnections(parent, child);
            }
         }
      }
      ++i;
   }
#else
   const QObjectList * children = widget->children();
   if (children == NULL) return;
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) return;
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (IsCustomWidget(widget)) {
            if (IsCustomWidget(child)) {
               Connect(widget, child);
               PropagateConnections(widget, child, level + 1);
            } else {
               PropagateConnections(widget, child, level + 1);
            }
         } else {
            if (IsCustomWidget(child)) {
               if (parent != NULL &&
                  IsCustomWidget(parent)) {
                   Connect(parent, child);
               }
               PropagateConnections(parent, child, level + 1);
            } else {
               PropagateConnections(parent, child);
            }
         }
      }
      ++i;
   }
#endif
   WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::Connect(QWidget * parent, QWidget * widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (parent->connect(parent, SIGNAL(CheckAppearanceSignal(ULONG_T,ULONG_T)), widget, SLOT(CheckAppearanceSlot(ULONG_T,ULONG_T)))) {
      CWidgetBase::DebugPrintf(CONNECTIONS, "connected Appearance %s to %s\n", CONST_STRING(Name(widget)), CONST_STRING(Name(parent)));
   } else {
      CWidgetBase::DebugPrintf(CONNECTIONS, "failed to connect appearance %s to %s\n", CONST_STRING(Name(widget)), CONST_STRING(Name(parent)));
      CWidgetBase::WidgetError("failed to connect appearance %s to %s\n", CONST_STRING(Name(widget)), CONST_STRING(Name(parent)));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::PropagateContext(QWidget * widget, NODE_PTR node, CONTEXT_PTR context, ULONG_T level)
{
#ifndef QT_PLUGIN
_ASSERT_COND(node != NULL)
_ASSERT_COND(context != NULL)
WMETHOD_PROLOG
   if (IsCustomWidget(widget)) {
      if (widget->inherits("CPage")) {
         InfoPrintf("propagate context of page %s\n", CONST_STRING(Name(widget)));
         qApp->processEvents();
      }
      SetContext(widget, node, context);
   }
#ifdef QT4
   const QObjectList children = widget->children();
   QObjectList::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * object = (*i);
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         PropagateContext(child, node, context, level + 1);
      }
      ++i;
   }
#else
   const QObjectList * children = widget->children();
   if (children == NULL) return;
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) return;
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         PropagateContext(child, node, context, level + 1);
      }
      ++i;
   }
#endif
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetupWidgets(QWidget * widget, ULONG_T level)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (IsCustomWidget(widget)) {
      SetupWidget(widget);
   }
#ifdef QT4
   if (widget->palette() != QPalette()) {
      _PaletteMap.SetPalette(widget, widget->palette());
   }
   const QObjectList children = widget->children();
   QObjectList::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * object = (*i);
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         SetupWidgets(child, level + 1);
      }
      ++i;
   }
#else
   const QObjectList * children = widget->children();
   if (children == NULL) return;
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) return;
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         SetupWidgets(child, level + 1);
      }
      ++i;
   }
#endif
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetContext(QWidget * widget, NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _GlobalNode = node;
   if (widget->inherits("CWidgetStack")) {
      ((CWidgetStack*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CComposedStack")) {
      ((CComposedStack*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CTabWidget")) {
      ((CTabWidget*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CFrame")) {
      ((CFrame*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CFixText")) {
      ((CFixText*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CInfoLabel")) {
      ((CInfoLabel*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CProtocolWindow")) {
      ((CProtocolWindow*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CGroupBox")) {
      ((CGroupBox*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CButtonGroup")) {
      ((CButtonGroup*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CActValue")) {
      ((CActValue*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CListView")) {
      ((CListView*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CReqValue")) {
      ((CReqValue*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CToolButton")) {
      ((CToolButton*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CPushButton")) {
      ((CPushButton*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CStateButton")) {
      ((CStateButton*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CRadioButton")) {
      ((CRadioButton*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CCheckBox")) {
      ((CCheckBox*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CComboBox")) {
      ((CComboBox*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CTable")) {
      ((CTable*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CGraphicsView")) {
      ((CGraphicsView*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CProcGraphic")) {
      ((CProcGraphic*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CRingGraphic")) {
      ((CRingGraphic*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CCoordSystem")) {
      ((CCoordSystem*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CVideo")) {
      ((CVideo*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CAlarmWidget")) {
      ((CAlarmWidget*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CTextEdit")) {
      ((CTextEdit*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CScrollBar")) {
      ((CScrollBar*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CSlider")) {
      ((CSlider*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CSpinBox")) {
      ((CSpinBox*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CProgressBar")) {
      ((CProgressBar*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CTime")) {
      ((CTime*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CDate")) {
      ((CDate*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CDateTime")) {
      ((CDateTime*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CVirtualKeyboard")) {
      ((CVirtualKeyboard*)widget)->InitializeWidget(node, context);
   } else if (widget->inherits("CWidget")) {
      ((CWidget*)widget)->InitializeWidget(node, context);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetupWidget(QWidget * widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (widget->inherits("CWidgetStack")) {
      ((CWidgetStack*)widget)->SetupWidget();
   } else if (widget->inherits("CComposedStack")) {
      ((CComposedStack*)widget)->SetupWidget();
   } else if (widget->inherits("CTabWidget")) {
      ((CTabWidget*)widget)->SetupWidget();
   } else if (widget->inherits("CFrame")) {
      ((CFrame*)widget)->SetupWidget();
   } else if (widget->inherits("CFixText")) {
      ((CFixText*)widget)->SetupWidget();
   } else if (widget->inherits("CInfoLabel")) {
      ((CInfoLabel*)widget)->SetupWidget();
   } else if (widget->inherits("CProtocolWindow")) {
      ((CProtocolWindow*)widget)->SetupWidget();
   } else if (widget->inherits("CGroupBox")) {
      ((CGroupBox*)widget)->SetupWidget();
   } else if (widget->inherits("CButtonGroup")) {
      ((CButtonGroup*)widget)->SetupWidget();
   } else if (widget->inherits("CActValue")) {
      ((CActValue*)widget)->SetupWidget();
   } else if (widget->inherits("CListView")) {
      ((CListView*)widget)->SetupWidget();
   } else if (widget->inherits("CReqValue")) {
      ((CReqValue*)widget)->SetupWidget();
   } else if (widget->inherits("CToolButton")) {
      ((CToolButton*)widget)->SetupWidget();
   } else if (widget->inherits("CPushButton")) {
      ((CPushButton*)widget)->SetupWidget();
   } else if (widget->inherits("CStateButton")) {
      ((CStateButton*)widget)->SetupWidget();
   } else if (widget->inherits("CRadioButton")) {
      ((CRadioButton*)widget)->SetupWidget();
   } else if (widget->inherits("CCheckBox")) {
      ((CCheckBox*)widget)->SetupWidget();
   } else if (widget->inherits("CComboBox")) {
      ((CComboBox*)widget)->SetupWidget();
   } else if (widget->inherits("CTable")) {
      ((CTable*)widget)->SetupWidget();
   } else if (widget->inherits("CGraphicsView")) {
      ((CGraphicsView*)widget)->SetupWidget();
   } else if (widget->inherits("CProcGraphic")) {
      ((CProcGraphic*)widget)->SetupWidget();
   } else if (widget->inherits("CRingGraphic")) {
      ((CRingGraphic*)widget)->SetupWidget();
   } else if (widget->inherits("CCoordSystem")) {
      ((CCoordSystem*)widget)->SetupWidget();
   } else if (widget->inherits("CVideo")) {
      ((CVideo*)widget)->SetupWidget();
   } else if (widget->inherits("CAlarmWidget")) {
      ((CAlarmWidget*)widget)->SetupWidget();
   } else if (widget->inherits("CTextEdit")) {
      ((CTextEdit*)widget)->SetupWidget();
   } else if (widget->inherits("CScrollBar")) {
      ((CScrollBar*)widget)->SetupWidget();
   } else if (widget->inherits("CSlider")) {
      ((CSlider*)widget)->SetupWidget();
   } else if (widget->inherits("CSpinBox")) {
      ((CSpinBox*)widget)->SetupWidget();
   } else if (widget->inherits("CProgressBar")) {
      ((CProgressBar*)widget)->SetupWidget();
   } else if (widget->inherits("CTime")) {
      ((CTime*)widget)->SetupWidget();
   } else if (widget->inherits("CDate")) {
      ((CDate*)widget)->SetupWidget();
   } else if (widget->inherits("CDateTime")) {
      ((CDateTime*)widget)->SetupWidget();
   } else if (widget->inherits("CVirtualKeyboard")) {
      ((CVirtualKeyboard*)widget)->SetupWidget();
   } else if (widget->inherits("CWidget")) {
      ((CWidget*)widget)->SetupWidget();
   }
WMETHOD_VOID_EPILOG
#endif
}

BOOL_T CWidgetBase::RefreshWidgetData()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_AppFrame != NULL) {
      _AppFrame->Refresh(DATA_REFRESH, true);
   }
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

BOOL_T CWidgetBase::RefreshWidgetData(QWidget * widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (widget->inherits("CWidgetStack")) {
      ((CWidgetStack*)widget)->RefreshData();
   } else if (widget->inherits("CComposedStack")) {
      ((CComposedStack*)widget)->RefreshData();
   } else if (widget->inherits("CTabWidget")) {
      ((CTabWidget*)widget)->RefreshData();
   } else if (widget->inherits("CFrame")) {
      ((CFrame*)widget)->RefreshData();
   } else if (widget->inherits("CFixText")) {
      ((CFixText*)widget)->RefreshData();
   } else if (widget->inherits("CInfoLabel")) {
      ((CInfoLabel*)widget)->RefreshData();
   } else if (widget->inherits("CProtocolWindow")) {
      ((CProtocolWindow*)widget)->RefreshData();
   } else if (widget->inherits("CGroupBox")) {
      ((CGroupBox*)widget)->RefreshData();
   } else if (widget->inherits("CButtonGroup")) {
      ((CButtonGroup*)widget)->RefreshData();
   } else if (widget->inherits("CActValue")) {
      ((CActValue*)widget)->RefreshData();
   } else if (widget->inherits("CListView")) {
      ((CListView*)widget)->RefreshData();
   } else if (widget->inherits("CReqValue")) {
      ((CReqValue*)widget)->RefreshData();
   } else if (widget->inherits("CToolButton")) {
      ((CToolButton*)widget)->RefreshData();
   } else if (widget->inherits("CPushButton")) {
      ((CPushButton*)widget)->RefreshData();
   } else if (widget->inherits("CStateButton")) {
      ((CStateButton*)widget)->RefreshData();
   } else if (widget->inherits("CRadioButton")) {
      ((CRadioButton*)widget)->RefreshData();
   } else if (widget->inherits("CCheckBox")) {
      ((CCheckBox*)widget)->RefreshData();
   } else if (widget->inherits("CComboBox")) {
      ((CComboBox*)widget)->RefreshData();
   } else if (widget->inherits("CTable")) {
      ((CTable*)widget)->RefreshData();
   } else if (widget->inherits("CGraphicsView")) {
      ((CGraphicsView*)widget)->RefreshData();
   } else if (widget->inherits("CProcGraphic")) {
      ((CProcGraphic*)widget)->RefreshData();
   } else if (widget->inherits("CRingGraphic")) {
      ((CRingGraphic*)widget)->RefreshData();
   } else if (widget->inherits("CCoordSystem")) {
      ((CCoordSystem*)widget)->RefreshData();
   } else if (widget->inherits("CVideo")) {
      ((CVideo*)widget)->RefreshData();
   } else if (widget->inherits("CAlarmWidget")) {
      ((CAlarmWidget*)widget)->RefreshData();
   } else if (widget->inherits("CTextEdit")) {
      ((CTextEdit*)widget)->RefreshData();
   } else if (widget->inherits("CScrollBar")) {
      ((CScrollBar*)widget)->RefreshData();
   } else if (widget->inherits("CSlider")) {
      ((CSlider*)widget)->RefreshData();
   } else if (widget->inherits("CSpinBox")) {
      ((CSpinBox*)widget)->RefreshData();
   } else if (widget->inherits("CProgressBar")) {
      ((CProgressBar*)widget)->RefreshData();
   } else if (widget->inherits("CTime")) {
      ((CTime*)widget)->RefreshData();
   } else if (widget->inherits("CDate")) {
      ((CDate*)widget)->RefreshData();
   } else if (widget->inherits("CDateTime")) {
      ((CDateTime*)widget)->RefreshData();
   } else if (widget->inherits("CVirtualKeyboard")) {
      ((CVirtualKeyboard*)widget)->RefreshData();
   } else if (widget->inherits("CWidget")) {
      ((CWidget*)widget)->RefreshData();
   }
WMETHOD_RC_EPILOG(false)
#endif
   return true;
}

// user function execution

ULONG_T CWidgetBase::ExecuteDarkFunc(FUNC_REF_PTR function)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      ULONG_T dark_state = elementFree;
      if (function != NULL) {
         function->CallGUIFunc(dark_state, _QWidget);
         DebugPrintf(FUNCTION_EXECUTION, "executed dark function %s: %p: %d in %s\n",
                     function->_Spec.c_str(), function, CONST_STRING(_Name));
      }
      return dark_state;
   } catch (cError & e) {
      ErrorPrintf("%s executing dark function %s:%p in %s\n", (CONST_STRING_T)e,
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return elementFree;
   } catch (...) {
      ErrorPrintf("unknown exception executing dark function %s:%p in %s\n",
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return elementFree;
   }
WMETHOD_RC_EPILOG(elementFree)
#endif
   return elementFree;
}

ULONG_T CWidgetBase::ExecutePlausFunc(FUNC_REF_PTR function, QString input)
{
#ifndef QT_PLUGIN
   if (function == NULL) {
      return actionProceed;
   } else {
      ULONG_T value = 0;
      function->CallGUIFunc(value, _QWidget, CONST_STRING(input));
      DebugPrintf(FUNCTION_EXECUTION, "executed plaus function %s: %p: %d in %s\n",
                  function->_Spec.c_str(), function,  value, CONST_STRING(_Name));
      return value;
   }
#endif
   return actionReject;
}

ULONG_T CWidgetBase::ExecuteUserFunc(FUNC_REF_PTR function, QString input)
{
#ifndef QT_PLUGIN
   if (function == NULL) {
      return actionProceed;
   } else {
      ULONG_T value = 0;
      function->CallGUIFunc(value, _QWidget, CONST_STRING(input));
      DebugPrintf(FUNCTION_EXECUTION, "executed user function %s: %p: %d in %s\n",
                  function->_Spec.c_str(), function,  value, CONST_STRING(_Name));
      return value;
    }
#endif
   return actionReject;
}

ULONG_T CWidgetBase::ExecuteGUISignalFilterFunc(FUNC_REF_PTR function, ULONG_T signal)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (function == NULL) {
         return signal;
      } else {
         ULONG_T value = 0;
         function->CallGUIFunc(value, _QWidget, signal);
         DebugPrintf(FUNCTION_EXECUTION, "executed signal filter function %s: %p: %d in %s\n",
                     function->_Spec.c_str(), function,  value, CONST_STRING(_Name));
         return value;
      }
   } catch (cError & e) {
      ErrorPrintf("%s executing signal filter function %s:%p in %s\n", (CONST_STRING_T)e,
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return 0;
   } catch (...) {
      ErrorPrintf("unknown exception executing signal filter function %s:%p in %s\n",
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return 0;
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

ULONG_T CWidgetBase::ExecuteGUISlotFunc(FUNC_REF_PTR function, ULONG_T signal, CWidgetBase * sender)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (function == NULL) {
         return 0;
      } else {
         ULONG_T value = 0;
         function->CallGUIFunc(value, _QWidget, signal, sender->_QWidget);
         DebugPrintf(FUNCTION_EXECUTION, "executed slot function %s: %p: %d in %s\n",
                     function->_Spec.c_str(), function,  value, CONST_STRING(_Name));
         return value;
      }
   } catch (cError & e) {
      DisplayError(e.ErrMsg().c_str());
      return 0;
   } catch (...) {
      DisplayError("unknown exception executing slot function");
      ErrorPrintf("unknown exception executing slot function %s:%p in %s\n",
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return 0;
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

ULONG_T CWidgetBase::ExecuteButtonFunc(FUNC_REF_PTR function, BOOL_T sync)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (sync) {
      try {
         ULONG_T action = actionProceed;
         if (function == NULL) {
            return action;
         } else {
            function->CallGUIFunc(action, _QWidget);
            DebugPrintf(FUNCTION_EXECUTION, "executed button function %s: %p:in %s\n",
                        function->_Spec.c_str(), function, CONST_STRING(_Name));
            return action;
         }
      } catch (cError & e) {
         DisplayError(cText::GetText(e).c_str(), e.get_Param1().c_str(),
                      e.get_Param2().c_str(), e.get_Param3().c_str(), e.get_Param4().c_str());
         return actionReject;
      } catch (...) {
         DisplayError("unknown exception executing button function");
         ErrorPrintf("unknown exception executing button function %s:%p in %s\n",
                     function->_Spec.c_str(), function, CONST_STRING(_Name));
         return actionReject;
      }
   } else {
      USER_INFO_PTR_T user_info = (USER_INFO_PTR_T)cSystemUtils::GetThreadData();
      if (user_info != NULL) {
         _QWidget->setEnabled(false);
         cAsyncFunction async_function(function, _QWidget, user_info);
         async_function.Execute();
         while (!async_function.Terminated()) {
            qApp->processEvents();
            cSystemUtils::Suspend(10);
         }
         if (async_function._ErrorThrown) {
            cError e = async_function._Error;
            if (e.get_ErrCode() == 0) {
               DisplayError("unknown exception executing button function");
            } else {
               DisplayError(cText::GetText(e).c_str(), e.get_Param1().c_str(),
                            e.get_Param2().c_str(), e.get_Param3().c_str(), e.get_Param4().c_str());
               ErrorPrintf("%s executing button function %s:%p in %s\n", (CONST_STRING_T)e,
                           function->_Spec.c_str(), function, CONST_STRING(_Name));
            }
            _QWidget->setEnabled(true);
            return actionReject;
         } else {
            _QWidget->setEnabled(true);
            return async_function.Action();
         }
      } else {
         DisplayError("user info is NULL while executing button function");
         ErrorPrintf("user info is NULL while executing button function %s:%p in %s\n", function->_Spec.c_str(), function, CONST_STRING(_Name));
         _QWidget->setEnabled(false);
         return actionReject;
      }
   }
WMETHOD_RC_EPILOG(actionReject)
#endif
   return actionReject;
}

ULONG_T CWidgetBase::AsyncExec(FUNC_REF_PTR func_ref, ERROR_REF_T e)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   USER_INFO_PTR user_info = (USER_INFO_PTR)cSystemUtils::GetThreadData();
   if (user_info != NULL) {
      cAsyncFunction async_function(func_ref, _QWidget, user_info);
      async_function.Execute();
      while (!async_function.Terminated()) {
         qApp->processEvents();
         cSystemUtils::Suspend(10);
      }
      if (async_function._ErrorThrown) {
         e = async_function._Error;
         return actionReject;
      } else {
         return async_function.Action();
      }
   } else {
      DisplayError("user info is NULL while executing async function");
      ErrorPrintf("user info is NULL while executing async function in %s\n", CONST_STRING(_Name));
      return actionReject;
   }
WMETHOD_RC_EPILOG(actionReject)
#endif
   return actionReject;
}

ULONG_T CWidgetBase::ExecuteButtonFuncs(FUNC_REF_PTR pre_exec_func_ref,
                                        FUNC_REF_PTR button_func_ref,
                                        BOOL_T sync,
                                        const QString & dialog_name,
                                        WIDGET_FLAGS_TYPE dialog_flags)
{
   ULONG_T rc = actionProceed;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   rc = ExecuteButtonFunc(pre_exec_func_ref, true);
   if (rc != actionReject) {
      if ((dialog_name.isEmpty() == false) &&
          (dialog_name.length() > 0)) {
         CAppFrame * app_frame = _AppFrame;
         if (app_frame != NULL) {
            CActionDialog * action_dialog = app_frame->GetActionDialog(dialog_name);
            if (action_dialog != NULL) {
               UiUpdate * uiUpdate = NULL;
               if (cContext::GetUiUpdateFuntion() == NULL) {
                  uiUpdate = new UiUpdate(CWidgetBase::Flag(SYNC_USER_FUNCTIONS));
               }

               action_dialog->Reset();
               action_dialog->SetContext(_Node, _Context);
               action_dialog->SetFunction(this, button_func_ref);
               action_dialog->SetActive(true);

               QPoint pt1App = app_frame->mapToGlobal(QPoint(0, 0));
               QPoint pt1Board = action_dialog->mapToGlobal(QPoint(0, 0));
               SHORT_T X = (app_frame->getPageAreaSize().width() - action_dialog->width()) / 2 + pt1App.x();
               SHORT_T Y = (app_frame->getPageAreaSize().height() - action_dialog->height()) / 2 + pt1App.y();
               QPoint ptDialog(X, Y);
               action_dialog->move(ptDialog);

               action_dialog->exec();
               rc = action_dialog->Result();
               action_dialog->SetActive(false);
               app_frame->ActionDialogTerminated(dialog_name, rc, action_dialog);

               if (uiUpdate) {
                   delete uiUpdate;
               }
            }
         }
      } else {
         rc = ExecuteButtonFunc(button_func_ref, sync);
      }
   }

WMETHOD_RC_EPILOG(actionReject)
#endif
   return rc;
}

LONG_T CWidgetBase::ExecuteValueFunc(FUNC_REF_PTR function, LONG_T value, ULONG_T flags)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (function == NULL) {
         return value;
      } else {
         LONG_T new_value = value;
         function->CallGUIFunc(new_value, _QWidget, value, flags);
         DebugPrintf(FUNCTION_EXECUTION, "executed value function %s: %p:in %s\n",
                     function->_Spec.c_str(), function, CONST_STRING(_Name));
         return new_value;
      }
   } catch (cError & e) {
      DisplayError(e.ErrMsg().c_str());
      return value;
   } catch (...) {
      DisplayError("unknown exception executing value function");
      ErrorPrintf("unknown exception executing list filter function %s:%p in %s\n",
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return value;
   }
WMETHOD_RC_EPILOG(actionReject)
#endif
   return actionReject;
}

ULONG_T CWidgetBase::ExecuteEventFilterFunc(FUNC_REF_PTR function, TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      ULONG_T rc = 0;
      if (function != NULL) {
         function->CallEventFilterFunc(rc, _QWidget, object);
         DebugPrintf(FUNCTION_EXECUTION, "executed event filter function %s: %p: in %s\n",
                     function->_Spec.c_str(), function, CONST_STRING(_Name));
      }
      return rc;
   } catch (cError & e) {
      ErrorPrintf("%s executing event filter function %s:%p in %s\n", (CONST_STRING_T)e,
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return 0;
   } catch (...) {
      ErrorPrintf("unknown exception executing event filter function %s:%p in %s\n",
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return 0;
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

ULONG_T CWidgetBase::ExecuteInitFunc(FUNC_REF_PTR function)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      ULONG_T action = 1;
      if (function == NULL) {
         return 1;
      } else {
         function->CallGUIFunc(action, _QWidget);
         DebugPrintf(FUNCTION_EXECUTION, "executed init function %s: %p:in %s\n",
                     function->_Spec.c_str(), function, CONST_STRING(_Name));
         return action;
      }
   } catch (cError & e) {
      ErrorPrintf("%s executing init function %s:%p in %s\n", (CONST_STRING_T)e,
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return 0;
   } catch (...) {
      ErrorPrintf("unknown exception executing init function %s:%p in %s\n",
                  function->_Spec.c_str(), function, CONST_STRING(_Name));
      return 0;
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 1;
}

// activation methods

void CWidgetBase::EmitGUISignal(ULONG_T signal)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ULONG_T new_signal = ExecuteGUISignalFilterFunc(_GUISignalFilterFuncRef, signal);
   _SignalManager->Signal(new_signal, _QualifiedName, this);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::EmitGUISignal(cGuiSignal * signal)
{
#ifndef QT_PLUGIN
#endif
}

void CWidgetBase::ListenTo(const QString & widget_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _SignalManager->ListenTo(widget_name, this);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::DisplayError(const QString & err_msg, 
                               const QString & param1,
                               const QString & param2,
                               const QString & param3,
                               const QString & param4)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_AppFrame == NULL) {
      cSystemUtils::AcousticSignal(100, 100);
#ifdef QT4
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
#else
      MessageBox(0, err_msg, "temporary", MB_OK);
#endif
   } else {
      _AppFrame->Message(false, err_msg, "", param1, param2, param3, param4); // 210305 HA
   }
WMETHOD_VOID_EPILOG
#endif
}

QString CWidgetBase::ErrorText(ERROR_REF_T e)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString err_text = cText::GetText(e).c_str();
   QString param1 = e.get_Param1().c_str();
   QString param2 = e.get_Param2().c_str();
   QString param3 = e.get_Param3().c_str();
   QString param4 = e.get_Param4().c_str();
   QString text = Translate(err_text, "custom", param1, param2, param3, param4);
   return text;
WMETHOD_RC_EPILOG("?")
#endif
   return "?";
}

void CWidgetBase::SetAppFrame(CAppFrame * app_frame)
{
   if (_AppFrame == NULL) {
      _AppFrame = app_frame;
   }

#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _AppFrame->SetGroupId(_DefaultGroupId);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::Notify(ULONG_T event_code)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_CommInterface == NULL) {
      _CommInterface = new cCommInterface;
   }
   if (_CommInterface != NULL) {
      cCommEvent * event = new cCommEvent(this, event_code);
      _CommInterface->Notify(event);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::ExecuteNotification(ULONG_T event_code)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      switch (event_code) {
      case VIEW_DATA:
         if (_QWidget->isVisible()) {
            _ViewPending = false;
            View();
         } else {
            _ViewPending = true;
         }
         break;
      default:
         Notification(event_code);
      }
   } catch(cError & e) {
      WidgetError("%s in GUI event %d of widget name %s\n", e.ErrMsg().c_str(), event_code, CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception in GUI event %d of widget name %s\n", event_code, CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::PostNewValue(const QString &  value, ULONG_T id, ULONG_T time_offset,
                               UCHAR_T data_type, ULONG_T size, ULONG_T data_set)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_CommInterface != NULL) {
      if (data_set & BACKGROUND_SENSITIVE) {
         if ((data_set & (~BACKGROUND_SENSITIVE)) != _CurrentDataSet) {
            /// this is not the desired dataset
            return;
         }
      }
      cNewValueEvent * event = new cNewValueEvent(this, value, id, time_offset, data_type, size);
      _CommInterface->Notify(event);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::PostNewBuf(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                             UCHAR_T data_type, ULONG_T size, ULONG_T data_set)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_CommInterface != NULL) {
      if (data_set & BACKGROUND_SENSITIVE) {
         if ((data_set & (~BACKGROUND_SENSITIVE)) != _CurrentDataSet) {
            /// this is not the desired dataset
            return;
         }
      }
      cNewBufEvent * event = new cNewBufEvent(this, buf, id, time_offset, data_type, size);
      _CommInterface->Notify(event);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::PostNewObject(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_CommInterface != NULL) {
      object->AddRef();
      cNewObjectEvent * event = new cNewObjectEvent(this, object);
      _CommInterface->Notify(event);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::PostMessageBox(const QString & caption, const QString & text, QMessageBox::Icon icon,
                                 int button0, int button1, int button2,
                                 QFont font)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_CommInterface != NULL) {
      cMessageBoxEvent * event = new cMessageBoxEvent(this, caption, text, icon,
                                                      button0, button1, button2,
                                                      font);
      _CommInterface->Notify(event);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::PropagateObject(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Node != NULL) {
      cEventAdapter * adapter = _Node->EventAdapter();
      if (adapter != NULL) {
         adapter->Object(object);
      } else {
         WidgetError("no adapter to send object to\n");
      }
   } else {
      WidgetError("no node to send object to\n");
   }
WMETHOD_VOID_EPILOG
#endif
}

// GUI related virtual methods

void CWidgetBase::Notification(ULONG_T event_code)
{
#ifndef QT_PLUGIN
#endif
}

void CWidgetBase::View()
{
#ifndef QT_PLUGIN
#endif
}

void CWidgetBase::DelayedLanguageChange()
{
#ifndef QT_PLUGIN
#endif
}

#define DELAYED_LANGUAGE_CHANGE(widget,type) \
      type * w = (type*)widget; \
      w->DelayedLanguageChange();

void CWidgetBase::DelayedLanguageChange(QWidget * widget)
{
#ifndef QT_PLUGIN
   if (widget->inherits("CWidgetStack")) {
      DELAYED_LANGUAGE_CHANGE(widget,CWidgetStack)
   } else if (widget->inherits("CComposedStack")) {
      DELAYED_LANGUAGE_CHANGE(widget,CComposedStack)
   } else if (widget->inherits("CTabWidget")) {
      DELAYED_LANGUAGE_CHANGE(widget,CTabWidget)
   } else if (widget->inherits("CFrame")) {
      DELAYED_LANGUAGE_CHANGE(widget,CFrame)
   } else if (widget->inherits("CFixText")) {
      DELAYED_LANGUAGE_CHANGE(widget,CFixText)
   } else if (widget->inherits("CInfoLabel")) {
      DELAYED_LANGUAGE_CHANGE(widget,CInfoLabel)
   } else if (widget->inherits("CGroupBox")) {
      DELAYED_LANGUAGE_CHANGE(widget,CGroupBox)
   } else if (widget->inherits("CButtonGroup")) {
      DELAYED_LANGUAGE_CHANGE(widget,CButtonGroup)
   } else if (widget->inherits("CActValue")) {
      DELAYED_LANGUAGE_CHANGE(widget,CActValue)
   } else if (widget->inherits("CListView")) {
      DELAYED_LANGUAGE_CHANGE(widget,CListView)
   } else if (widget->inherits("CReqValue")) {
      DELAYED_LANGUAGE_CHANGE(widget,CReqValue)
   } else if (widget->inherits("CToolButton")) {
      DELAYED_LANGUAGE_CHANGE(widget,CToolButton)
   } else if (widget->inherits("CPushButton")) {
      DELAYED_LANGUAGE_CHANGE(widget,CPushButton)
   } else if (widget->inherits("CStateButton")) {
      DELAYED_LANGUAGE_CHANGE(widget,CStateButton)
   } else if (widget->inherits("CRadioButton")) {
      DELAYED_LANGUAGE_CHANGE(widget,CRadioButton)
   } else if (widget->inherits("CCheckBox")) {
      DELAYED_LANGUAGE_CHANGE(widget,CCheckBox)
   } else if (widget->inherits("CComboBox")) {
      DELAYED_LANGUAGE_CHANGE(widget,CComboBox)
   } else if (widget->inherits("CTable")) {
      DELAYED_LANGUAGE_CHANGE(widget,CTable)
   } else if (widget->inherits("CGraphicsView")) {
      DELAYED_LANGUAGE_CHANGE(widget,CGraphicsView)
   } else if (widget->inherits("CProcGraphic")) {
      DELAYED_LANGUAGE_CHANGE(widget,CProcGraphic)
   } else if (widget->inherits("CRingGraphic")) {
      DELAYED_LANGUAGE_CHANGE(widget,CRingGraphic)
   } else if (widget->inherits("CCoordSystem")) {
      DELAYED_LANGUAGE_CHANGE(widget,CCoordSystem)
   } else if (widget->inherits("CVideo")) {
      DELAYED_LANGUAGE_CHANGE(widget,CVideo)
   } else if (widget->inherits("CAlarmWidget")) {
      DELAYED_LANGUAGE_CHANGE(widget,CAlarmWidget)
   } else if (widget->inherits("CTextEdit")) {
      DELAYED_LANGUAGE_CHANGE(widget,CTextEdit)
   } else if (widget->inherits("CScrollBar")) {
      DELAYED_LANGUAGE_CHANGE(widget,CScrollBar)
   } else if (widget->inherits("CSlider")) {
      DELAYED_LANGUAGE_CHANGE(widget,CSlider)
   } else if (widget->inherits("CSpinBox")) {
      DELAYED_LANGUAGE_CHANGE(widget,CSpinBox)
   } else if (widget->inherits("CProgressBar")) {
      DELAYED_LANGUAGE_CHANGE(widget,CProgressBar)
   } else if (widget->inherits("CTime")) {
      DELAYED_LANGUAGE_CHANGE(widget,CTime)
   } else if (widget->inherits("CDate")) {
      DELAYED_LANGUAGE_CHANGE(widget,CDate)
   } else if (widget->inherits("CDateTime")) {
      DELAYED_LANGUAGE_CHANGE(widget,CDateTime)
   } else if (widget->inherits("CVirtualKeyboard")) {
      DELAYED_LANGUAGE_CHANGE(widget,CVirtualKeyboard)
   } else if (widget->inherits("CWidget")) {
      DELAYED_LANGUAGE_CHANGE(widget,CWidget)
   } else {
      UNEXPECTED_BRANCH()
   }
#endif
}

void CWidgetBase::RefreshData()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
    if (_RefreshMap == NULL) return;

   _RefreshMap->RefreshData(_CurrentDataSet, _PendingRefreshMap);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::RefreshBGData()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
    if (_RefreshMap == NULL) return;

   _RefreshMap->RefreshBGData(_CurrentDataSet, _PendingRefreshMap);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::GUISignal(ULONG_T signal, CWidgetBase * sender)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ExecuteGUISlotFunc(_GUISlotFuncRef, signal, sender);
WMETHOD_VOID_EPILOG
#endif
}

// CCS related virtual methods

void CWidgetBase::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
}

void CWidgetBase::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                              UCHAR_T data_type, ULONG_T size)
{
}

void CWidgetBase::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                              UCHAR_T data_type, ULONG_T size)
{
}

void CWidgetBase::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

// widget specific virtual methods

void CWidgetBase::Setup()
{
}


// CCS related helper methods

BOOL_T CWidgetBase::CCSGetValue(VAR_REF_PTR var_ref, STRING_T & value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   var_ref->GetValue(value);
   return true;
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

BOOL_T CWidgetBase::CCSSetValue(VAR_REF_PTR var_ref, CONST_STRING_T value, BOOL_T propagate_exception)
{
#ifndef QT_PLUGIN
   try {
      var_ref->SetValue(value);
      if (_AppFrame != NULL) {
         _AppFrame->Refresh(EVENT_REFRESH);
         _AppFrame->ResyncLogoff();
      }
      return true;
   } catch (cError & e) {
      if (propagate_exception) {
         throw e;
      } else {
         ErrorPrintf("unhandled GUI cError exception: %s\n", (CONST_STRING_T)e);
      }
      return false;
   } catch (cErrBase & e) {
      ErrorPrintf("unhandled GUI cErrBase Exception (%d,%d,%d)\n", e.getClass(), e.getCode(), e.getPrefix());
      return false;
   } catch (...) {
      ErrorPrintf("unhandled GUI exception\n");
      return false;
   }
#endif
   return false;
}

void CWidgetBase::CCSCreateFuncRef(CONST_STRING_T func_spec, FUNC_REF_PTR & func_ref, BOOL_T cached)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (func_spec == NULL || *func_spec == 0) {
      return;
   }
   try {
      int spec_len = strlen(func_spec);
      if (spec_len > 0) {
         if (func_ref != NULL) {
            CCSRemoveFuncRef(func_ref);
         }
         QString reference;
         int i = 0;
         for (i=0; i<spec_len; i++) {
            if (func_spec[i] != '\\') {
               reference += func_spec[i];
            }
         }
         func_ref = _Context->FuncRef(CONST_STRING(reference));
         if (func_ref != NULL) {
            DebugPrintf(FUNCTION_INIT, "created function reference %s: %p in %s\n", func_spec, func_ref, CONST_STRING(_Name));
         } else {
            WidgetError("failed to create function reference %s in %s\n", func_spec, CONST_STRING(_Name));
         }
         if (func_spec != NULL && strlen(func_spec) > 0 &&
             Flag(SHOW_REFERENCES)) {
            QString info = "";
            info.sprintf("%s / %p", func_spec, func_ref);
#ifdef QT4
            _QWidget->setToolTip(info);
#else
            QToolTip::add(_QWidget, info);
#endif
         }
      }
   } catch(cError & e) {
      WidgetError("%s creating %s in %s\n", e.ErrMsg().c_str(), func_spec, CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception creating %s in %s\n", func_spec, CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSRemoveFuncRef(FUNC_REF_PTR & func_ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      DebugPrintf(FUNCTION_INIT, "removing function reference %s: %p in %s\n",
                  func_ref->_Spec.c_str(), func_ref, CONST_STRING(_Name));
      DELETE_OBJECT(cFuncRef, func_ref)
   } catch(cError & e) {
      WidgetError("%s removing function reference %s in %s\n",
                  e.ErrMsg().c_str(), func_ref->_Spec.c_str(), CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception removing function function reference %s in %s\n",
                  func_ref->_Spec.c_str(), CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSInitializeVarRef(CONST_STRING_T var_spec, VAR_REF_PTR & var_ref, BOOL_T cached)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (var_spec != NULL && strlen(var_spec) == 0) {
#ifndef QT4
      WidgetError("empty variable reference specification in %s\n", CONST_STRING(_Name));
#endif
   } else {
      CCSCreateVarRef(var_spec, var_ref, cached);
      if (var_spec != NULL && strlen(var_spec) > 0 &&
          Flag(SHOW_REFERENCES)) {
         QString info = "";
         info.sprintf("%s / %p %s", var_spec, var_ref, cached ? "cached" : "uncached");
#ifdef QT4
         _QWidget->setToolTip(info);
#else
         QToolTip::add(_QWidget, info);
#endif
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSInitializeVarRef(CONST_STRING_T var_spec, VAR_REF_PTR & var_ref, DATA_VIEW_PTR & data_view, ULONG_T id, BOOL_T cached)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (var_spec != NULL && strlen(var_spec) == 0) {
#ifndef QT4
      WidgetError("empty variable reference specification in %s\n", CONST_STRING(_Name));
#endif
   } else {
      CCSCreateVarRef(var_spec, var_ref, data_view, id, cached);
      CCSRegisterVarRef(var_ref);
      if (var_ref != NULL) {
#ifdef DEPRECATED_15
         if (var_ref->BackgroundVar()) {
            _BackgroundSensitive = true;
         }
#endif
         SetRefresh(var_ref);
      }
      if (var_spec != NULL && strlen(var_spec) > 0 &&
          Flag(SHOW_REFERENCES)) {
         QString info = "";
         info.sprintf("%s / %p %p", var_spec, var_ref, this);
#ifdef QT4
        _QWidget->setToolTip(info);
#else
         QToolTip::add(_QWidget, info);
#endif
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSInitializeArgument(CONST_STRING_T arg_spec, ARGUMENT_PTR & arg, DATA_VIEW_PTR & data_view, ULONG_T id)
{
#ifndef QT_PLUGIN
#endif
}

void CWidgetBase::CCSCreateVarRef(CONST_STRING_T var_spec, VAR_REF_PTR & var_ref, BOOL_T cached)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (_Context != NULL) {
         if (var_spec != NULL && strlen(var_spec) > 0) {
            var_ref = _Context->VarRef(var_spec, cached);
            if (var_ref == NULL) {
               WidgetError("failed to create variable reference %s: in %s\n",
                           var_spec, CONST_STRING(_Name));
               _QWidget->setEnabled(false);
            } else {
               DebugPrintf(VARIABLE_INIT, "created variable reference %s: %p in %p\n",
                           var_spec, var_ref, CONST_STRING(_Name));
            }
         }
      } else {
         WidgetError("no context for variable reference %s in %s\n",
                     var_spec, CONST_STRING(_Name));
      }
   } catch(cError & e) {
      WidgetError("%s creating variable reference %s in %s\n",
                  e.ErrMsg().c_str(), var_spec, CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception creating %s in %s\n", var_spec, CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSCreateVarRef(CONST_STRING_T var_spec, VAR_REF_PTR & var_ref, DATA_VIEW_PTR & data_view, ULONG_T id, BOOL_T cached)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (_Context != NULL) {
         if (var_spec != NULL && strlen(var_spec) > 0) {
            var_ref = _Context->VarRef(var_spec, cached);
            if (var_ref == NULL) {
               WidgetError("failed to create variable reference %s: in %s\n",
                           var_spec, CONST_STRING(_Name));
               _QWidget->setEnabled(false);
            } else {
               data_view = new cDataView(this, var_ref, id);
               CCSRegisterDataView(data_view);
               DebugPrintf(VARIABLE_INIT, "created variable reference %s: %p in %s\n",
                           var_spec, var_ref, CONST_STRING(_Name));
            }
         }
      } else {
         WidgetError("no context for variable reference %s in %s\n",
                     var_spec, CONST_STRING(_Name));
      }
   } catch(cError & e) {
      WidgetError("%s creating variable reference %s in %s\n",
                  e.ErrMsg().c_str(), var_spec, CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception creating %s in %s\n", var_spec, CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSRemoveVarRef(VAR_REF_PTR & var_ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (var_ref != NULL) {
         CCSUnRegisterVarRef(var_ref);
         DELETE_OBJECT(cVarRef, var_ref)
      }
   } catch(cError & e) {
      WidgetError("%s removing variable reference %s in %s\n",
                  e.ErrMsg().c_str(), var_ref->_Spec.c_str(), CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception  removing variable reference %s in %s\n",
                  var_ref->_Spec.c_str(), CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSRemoveVarRef(VAR_REF_PTR & var_ref, DATA_VIEW_PTR & data_view, ULONG_T id)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSRemoveVarRef(var_ref);
   try {
      if (data_view != NULL) {
         DELETE_OBJECT(cDataView, data_view)
      }
   } catch(cError & e) {
      WidgetError("%s removing control link in %s\n",
                  e.ErrMsg().c_str(), data_view, CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception removing control link %p in %s\n",
                  data_view, CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSRemoveDataLinks()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   DATA_VIEW_MAP_T::const_iterator i = _DataViewMap.begin();
   while (i != _DataViewMap.end()) {
      STRING_T ref_spec = (*i).first;
      DATA_VIEW_PTR view = (*i).second;
      cVarRef * var_ref = view->VarRef();
      var_ref->RemoveControl(view);
      i++;
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSCreateArgument(CONST_STRING_T arg_spec, ARGUMENT_PTR & arg, DATA_VIEW_PTR & data_view, ULONG_T id)
{
#ifndef QT_PLUGIN
#endif
}

void CWidgetBase::CCSRemoveArgument(ARGUMENT_PTR & argument, DATA_VIEW_PTR & data_view, ULONG_T id)
{
#ifndef QT_PLUGIN
#endif
}

void CWidgetBase::CCSRegisterVarRef(VAR_REF_PTR var_ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (var_ref != NULL) {
         if (_Node != NULL) {
            cDataChangeAdapter * adapter = _Node->DataChangeAdapter();
            if (adapter != NULL) {
               var_ref->Register(adapter);
               DebugPrintf(VARIABLE_INIT, "variable reference %s: %p in %s registered\n",
                           var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
            } else {
               WidgetError("no adapter to register variable reference %s: %p in %s\n",
                           var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
            }
         } else {
            WidgetError("no node to register variable reference %s: %p in %s\n",
                        var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
         }
      }
   } catch(cError & e) {
      WidgetError("%s registering variable reference %s: %p in %s\n",
                  e.ErrMsg().c_str(), var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception registering variable reference %s: %p in %s\n",
                  var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSUnRegisterVarRef(VAR_REF_PTR var_ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   try {
      if (var_ref != NULL) {
         if (_Node != NULL) {
            cDataChangeAdapter * adapter = _Node->DataChangeAdapter();
            if (adapter != NULL) {
               var_ref->UnRegister(adapter);
               DebugPrintf(VARIABLE_INIT, "variable reference %s: %p in %s unregistered\n",
                           var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
            } else {
               WidgetError("no adapter to unregister variable reference %s: %p in %s\n",
                           var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
            }
         } else {
            WidgetError("no node to unregister variable reference %s: %p in %s\n",
                        var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
         }
      }
   } catch(cError & e) {
      WidgetError("%s registering variable reference %s: %p in %s\n",
                  e.ErrMsg().c_str(), var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
   } catch(...) {
      WidgetError("unhandled exception registering variable reference %s: %p in %s\n",
                  var_ref->_Spec.c_str(), var_ref, CONST_STRING(_Name));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSRegisterDataView(DATA_VIEW_PTR data_view)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   VAR_REF_PTR var_ref = data_view->VarRef();
   STRING_T key = var_ref->_Spec;
   DATA_VIEW_MAP_T::const_iterator i = _DataViewMap.find(key);
   if (i == _DataViewMap.end()) {
      _DataViewMap[key] = data_view;
   } else {
      _DataViewMap[key] = data_view;
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetRefresh(VAR_REF_PTR var_ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_RefreshMap == NULL) {
      _RefreshMap = new cDataRefreshMap;
   }
   _RefreshMap->SetRefreshed(var_ref);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::RemoveRefresh(VAR_REF_PTR var_ref)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
    if (_RefreshMap == NULL) {
       return;
    }
   _RefreshMap->Erase(var_ref);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSCreateEventLink()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_EventFilter != 0) {
      _EventView = new cEventView(this);
      if (_Node != NULL) {
         cEventAdapter * event_adapter = _Node->EventAdapter();
         if (event_adapter != NULL) {
            event_adapter->RegisterControl(_EventView);
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::CCSRemoveEventLink()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_EventView != NULL) {
      if (_Node != NULL) {
         cEventAdapter * event_adapter = _Node->EventAdapter();
         if (event_adapter != NULL) {
            event_adapter->UnRegisterControl(_EventView);
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

// text related helper methods

QString CWidgetBase::SubstParams(const QString & text,
                                 const QString & p1,
                                 const QString & p2,
                                 const QString & p3,
                                 const QString & p4)
{
   QString new_text = text;
#ifndef QT_PLUGIN
   if (!p1.isNull()) {
      new_text.replace("#1", p1);
   }
   if (!p2.isNull()) {
      new_text.replace("#2", p2);
   }
   if (!p3.isNull()) {
      new_text.replace("#3", p3);
   }
   if (!p4.isNull()) {
      new_text.replace("#4", p4);
   }
#endif
   return new_text;
}

QString CWidgetBase::Translate(const QString & text,
                               const QString & context,
                               const QString & p1,
                               const QString & p2,
                               const QString & p3,
                               const QString & p4)
{
   QString new_text = text;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   new_text = QApplication::translate(CONST_STRING(context), CONST_STRING(new_text));

   if (new_text.isEmpty()) {
      new_text = QString::fromLatin1(CONST_STRING(text));
   }
   new_text = SubstParams(new_text, p1, p2, p3, p4);
WMETHOD_RC_EPILOG(new_text)
#endif
   return new_text;
}

QString CWidgetBase::RefText(CONTEXT_PTR context, VAR_REF_PTR var_ref, const QString & language)
{
   QString text = "?";
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   LONG_T i1 = -1;
   LONG_T i2 = -1;
   LONG_T i3 = -1;
   LONG_T i4 = -1;
   var_ref->GetIndices(i1, i2, i3, i4);
   VARIABLE_PTR variable = var_ref->_Variable;
   if (variable != NULL) {
      text = VariableText(context, variable, i1, i2, i3, i4);
   }
WMETHOD_RC_EPILOG(text)
#endif
   return text;
}

QString CWidgetBase::VariableText(CONTEXT_PTR context, VARIABLE_PTR variable,
                                  LONG_T i1,
                                  LONG_T i2,
                                  LONG_T i3,
                                  LONG_T i4, const QString & language)
{
   QString text = "?";
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CAppFrame * app_frame = CWidgetBase::_AppFrame;

   if (!app_frame->VariableText(text, language, variable, i1, i2, i3, i4)) {
      cVarDef * var_def = variable->_VarDef;
      if (var_def != NULL) {
         ULONG_T system_flags = var_def->_SystemFlags;
         QString qsvar_text = var_def->_Text.c_str();
         if (qsvar_text.length() == 0) {
            STRING_T var_name = variable->VarName();
            QString ref;
            if (i1 == -1) {
               ref = var_name.c_str();
            } else if (i2 == -1) {
               ref = QString("%1[%2]").arg(var_name.c_str()).arg(i1);
            } else if (i3 == -1) {
               ref = QString("%1[%2][%3]").arg(var_name.c_str()).arg(i1).arg(i2);
            } else if (i4 == -1) {
               ref = QString("%1[%2][%3][%4]").arg(var_name.c_str()).arg(i1).arg(i2).arg(i3);
            } else {
               ref = QString("%1[%2][%3][%4][%5]").arg(var_name.c_str()).arg(i1).arg(i2).arg(i3).arg(i4);
            }
            return ref;
         } else {
            qsvar_text = QApplication::translate("custom", CONST_STRING(qsvar_text));
         }
         QString dim1_text = var_def->_Dim1Text.c_str();
         QString dim2_text = var_def->_Dim2Text.c_str();
         QString dim3_text = var_def->_Dim3Text.c_str();
         QString dim4_text = var_def->_Dim4Text.c_str();
         if (i1 != -1) {
            qsvar_text += " ";
            qsvar_text += QApplication::translate("custom", CONST_STRING(dim1_text));
            qsvar_text += " ";
            qsvar_text += QString::number(i1 + ((system_flags & DIM1_OFFSET) != 0));
         }
         if (i2 != -1) {
            qsvar_text += " ";
            qsvar_text += QApplication::translate("custom", CONST_STRING(dim2_text));
            qsvar_text += " ";
            qsvar_text += QString::number(i2 + ((system_flags & DIM2_OFFSET) != 0));
         }
         if (i3 != -1) {
            qsvar_text += " ";
            qsvar_text += QApplication::translate("custom", CONST_STRING(dim3_text));
            qsvar_text += " ";
            qsvar_text += QString::number(i3 + ((system_flags & DIM3_OFFSET) != 0));
         }
         if (i4 != -1) {
            qsvar_text += " ";
            qsvar_text += QApplication::translate("custom", CONST_STRING(dim4_text));
            qsvar_text += " ";
            qsvar_text += QString::number(i4 + ((system_flags & DIM4_OFFSET) != 0));
         }
         text = qsvar_text;
      }
   }
WMETHOD_RC_EPILOG(text)
#endif
   return text;
}

QString CWidgetBase::AlarmText(CONTEXT_PTR context, ALARM_PTR alarm, const QString & language)
{
#ifdef QT_PLUGIN
   return "?";
#else
WMETHOD_PROLOG
   ULONG_T text_id1 = alarm->get_TextId1();
   QString text1;
   if (text_id1 != 0) { 
      text1 = cText::GetText(text_id1);
   } else {
      text1 = alarm->get_Text1().c_str();
   }
   
   CAppFrame * app_frame = CWidgetBase::_AppFrame;
   QString text = "";
   if (app_frame != NULL) {
      ULONG_T id = alarm->get_Ident();
      if (!app_frame->GetTranslation(text, app_frame->GetLanguage(),
                                     id, text1,
                                     alarm->get_Param1().c_str(), alarm->get_Param2().c_str(),
                                     alarm->get_Param3().c_str(), alarm->get_Param4().c_str())) {
         text = Translate(text1, "custom",
                          alarm->get_Param1().c_str(), alarm->get_Param2().c_str(),
                          alarm->get_Param3().c_str(), alarm->get_Param4().c_str());
      }
   }
   return text;
WMETHOD_RC_EPILOG("?")
#endif
}

QString CWidgetBase::ChangeText(CONTEXT_PTR context, DATA_CHANGE_PTR data_change, const QString & language)
{
   QString text = "?";
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_RC_EPILOG(text)
#endif
   return text;
}

// help and language related helper methods

QString CWidgetBase::ActLanguage()
{
   QString text = "?";
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_AppFrame == NULL) {
      text = "default";
   } else {
      text = _AppFrame->ActLanguage();
   }
WMETHOD_RC_EPILOG(text)
#endif
   return text;
}

BOOL_T CWidgetBase::HelpActive()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_AppFrame != NULL) {
      return _AppFrame->HelpActive();
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

void CWidgetBase::SetHelpIds()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!_BaseHelpId1.isEmpty()) {
      _ActHelpId1 = _BaseHelpId1;
      _ActHelpId2 = _BaseHelpId2;
      _AppFrame->SetHelpAdditionalPath("");
   } else {
      SetHelpIds((QWidget*)_QWidget->parent());
   }
   BOOL_T help_active = _AppFrame->HelpActive();
   if (help_active) {
      _AppFrame->ShowHelp(_ActHelpId1, _ActHelpId2);
   }
   if (_AppFrame != NULL) {
      _AppFrame->ResyncLogoff();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetHelpIds(QWidget * widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (widget == NULL) {
      _ActHelpId1 = "";
      _ActHelpId2 = "";
      return;
   }
   QObject * object = (QObject*)widget;
   if (object->isWidgetType()) {
      if (IsCustomWidget(widget)) {
         QString help_id1;
         QString help_id2;
         GetHelpIds(widget, help_id1, help_id2); 
         if (!help_id1.isEmpty()) {
            _ActHelpId1 = help_id1;
            _ActHelpId2 = help_id2;
            _AppFrame->SetHelpAdditionalPath("");
         } else {
            SetHelpIds((QWidget*)widget->parent());
         }
      } else {
         SetHelpIds((QWidget*)widget->parent());
      }
   } else {
      SetHelpIds((QWidget*)object->parent());
   }
   if (_AppFrame != NULL) {
      _AppFrame->ResyncLogoff();
   }
   WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::GetActHelpIds(QString & help_id1, QString & help_id2)
{
   help_id1 = _ActHelpId1;
   help_id2 = _ActHelpId2;
}

void CWidgetBase::GetHelpIds(QWidget * widget, QString & help_id1, QString & help_id2)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (widget->inherits("CWidgetStack")) {
   } else if (widget->inherits("CComposedStack")) {
      help_id1 = ((CComposedStack*)widget)->getHelpId1();
      help_id2 = ((CComposedStack*)widget)->getHelpId2();
   } else if (widget->inherits("CTabWidget")) {
      help_id1 = ((CTabWidget*)widget)->getHelpId1();
      help_id2 = ((CTabWidget*)widget)->getHelpId2();
   } else if (widget->inherits("CFrame")) {
      help_id1 = ((CFrame*)widget)->getHelpId1();
      help_id2 = ((CFrame*)widget)->getHelpId2();
   } else if (widget->inherits("CFixText")) {
      help_id1 = ((CFixText*)widget)->getHelpId1();
      help_id2 = ((CFixText*)widget)->getHelpId2();
   } else if (widget->inherits("CInfoLabel")) {
      help_id1 = ((CInfoLabel*)widget)->getHelpId1();
      help_id2 = ((CInfoLabel*)widget)->getHelpId2();
   } else if (widget->inherits("CProtocolWindow")) {
      help_id1 = ((CProtocolWindow*)widget)->getHelpId1();
      help_id2 = ((CProtocolWindow*)widget)->getHelpId2();
   } else if (widget->inherits("CGroupBox")) {
      help_id1 = ((CGroupBox*)widget)->getHelpId1();
      help_id2 = ((CGroupBox*)widget)->getHelpId2();
   } else if (widget->inherits("CButtonGroup")) {
      help_id1 = ((CButtonGroup*)widget)->getHelpId1();
      help_id2 = ((CButtonGroup*)widget)->getHelpId2();
   } else if (widget->inherits("CActValue")) {
      help_id1 = ((CActValue*)widget)->getHelpId1();
      help_id2 = ((CActValue*)widget)->getHelpId2();
   } else if (widget->inherits("CListView")) {
      help_id1 = ((CListView*)widget)->getHelpId1();
      help_id2 = ((CListView*)widget)->getHelpId2();
   } else if (widget->inherits("CReqValue")) {
      help_id1 = ((CReqValue*)widget)->getHelpId1();
      help_id2 = ((CReqValue*)widget)->getHelpId2();
   } else if (widget->inherits("CToolButton")) {
      help_id1 = ((CToolButton*)widget)->getHelpId1();
      help_id2 = ((CToolButton*)widget)->getHelpId2();
   } else if (widget->inherits("CPushButton")) {
      help_id1 = ((CPushButton*)widget)->getHelpId1();
      help_id2 = ((CPushButton*)widget)->getHelpId2();
   } else if (widget->inherits("CStateButton")) {
      help_id1 = ((CStateButton*)widget)->getHelpId1();
      help_id2 = ((CStateButton*)widget)->getHelpId2();
   } else if (widget->inherits("CRadioButton")) {
      help_id1 = ((CRadioButton*)widget)->getHelpId1();
      help_id2 = ((CRadioButton*)widget)->getHelpId2();
   } else if (widget->inherits("CCheckBox")) {
      help_id1 = ((CCheckBox*)widget)->getHelpId1();
      help_id2 = ((CCheckBox*)widget)->getHelpId2();
   } else if (widget->inherits("CComboBox")) {
      help_id1 = ((CComboBox*)widget)->getHelpId1();
      help_id2 = ((CComboBox*)widget)->getHelpId2();
   } else if (widget->inherits("CTable")) {
      help_id1 = ((CTable*)widget)->getHelpId1();
      help_id2 = ((CTable*)widget)->getHelpId2();
   } else if (widget->inherits("CGraphicsView")) {
      help_id1 = ((CGraphicsView*)widget)->getHelpId1();
      help_id2 = ((CGraphicsView*)widget)->getHelpId2();
   } else if (widget->inherits("CProcGraphic")) {
      help_id1 = ((CProcGraphic*)widget)->getHelpId1();
      help_id2 = ((CProcGraphic*)widget)->getHelpId2();
   } else if (widget->inherits("CRingGraphic")) {
      help_id1 = ((CRingGraphic*)widget)->getHelpId1();
      help_id2 = ((CRingGraphic*)widget)->getHelpId2();
   } else if (widget->inherits("CCoordSystem")) {
      help_id1 = ((CCoordSystem*)widget)->getHelpId1();
      help_id2 = ((CCoordSystem*)widget)->getHelpId2();
   } else if (widget->inherits("CVideo")) {
      help_id1 = ((CVideo*)widget)->getHelpId1();
      help_id2 = ((CVideo*)widget)->getHelpId2();
   } else if (widget->inherits("CAlarmWidget")) {
      help_id1 = ((CAlarmWidget*)widget)->getHelpId1();
      help_id2 = ((CAlarmWidget*)widget)->getHelpId2();
   } else if (widget->inherits("CTextEdit")) {
      help_id1 = ((CTextEdit*)widget)->getHelpId1();
      help_id2 = ((CTextEdit*)widget)->getHelpId2();
   } else if (widget->inherits("CScrollBar")) {
      help_id1 = ((CScrollBar*)widget)->getHelpId1();
      help_id2 = ((CScrollBar*)widget)->getHelpId2();
   } else if (widget->inherits("CVirtualKeyboard")) {
      help_id1 = ((CVirtualKeyboard*)widget)->getHelpId1();
      help_id2 = ((CVirtualKeyboard*)widget)->getHelpId2();
   } else if (widget->inherits("CWidget")) {
      help_id1 = ((CWidget*)widget)->getHelpId1();
      help_id2 = ((CWidget*)widget)->getHelpId2();
   }
WMETHOD_VOID_EPILOG
#endif
}

BOOL_T CWidgetBase::useEnglishKeyboard()
{
   BOOL_T use_english_keyboard = false;

#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QString act_language = ActLanguage();
   QString default_language = cResources::get_DefaultLanguage().c_str();
   if (_stricmp(CONST_STRING(default_language), "en-US") == 0) {
      if (_stricmp(CONST_STRING(act_language), "de") == 0) {
         use_english_keyboard = false;
      } else {
         use_english_keyboard = true;
      }
   } else { // default language german
      if (_stricmp(CONST_STRING(act_language), "") == 0 ||
          _stricmp(CONST_STRING(act_language), "default") == 0) {
         use_english_keyboard = false;
      } else {
         use_english_keyboard = true;
      }
   }
WMETHOD_RC_EPILOG(use_english_keyboard)
#endif
   return use_english_keyboard;
}

void CWidgetBase::SetGUIThreadId()
{
   if (_QtGUIThreadId == 0) {
      _QtGUIThreadId = (int)QThread::currentThreadId();
      DebugPrintf(GUI_INFO, "GUI thread id: %04x\n", _QtGUIThreadId);
   }
   SetGUIThread();
}

void CWidgetBase::SetGUIThread()
{
   if (_QtGUIThread == NULL) {
      _QtGUIThread = QThread::currentThread();
      DebugPrintf(GUI_INFO, "GUI thread: %p\n", _QtGUIThread);
   }
}

int CWidgetBase::GetGUIThreadId()
{
   return _QtGUIThreadId;
}

QThread * CWidgetBase::GetGUIThread()
{
   return _QtGUIThread;
}

QThread * CWidgetBase::GetCurrentThread()
{
   return QThread::currentThread();
}

bool CWidgetBase::CheckThread()
{
   return (GetCurrentThread() == GetGUIThread()) ? true : false;
}

void CWidgetBase::SetDefaultGroupId(ULONG_T id)
{
#ifndef QT_PLUGIN
   if (id > MAX_GROUP_ID) {
      _DefaultGroupId = MAX_GROUP_ID;
   } else {
      _DefaultGroupId = id;
   }
#endif
}

void CWidgetBase::SetCurrentDataSet(ULONG_T data_set)
{
#ifndef QT_PLUGIN
   _CurrentDataSet = data_set;
#endif
}

ULONG_T CWidgetBase::GetCurrentDataSet()
{
   ULONG_T currentDataSet = 0;
#ifndef QT_PLUGIN
   currentDataSet = _CurrentDataSet;
#endif
   return currentDataSet;
}

/// appearance functionality integrating user access rights
/// and blanking (dark) functionality

void CWidgetBase::CheckAppearance(ULONG_T refresh_type, ULONG_T parent_state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!_IsActive) {
      return;
   } else {
   }
   if (IS_DATA_REFRESH(refresh_type)) {
      RefreshData();
   } else if (IS_BG_DATA_REFRESH(refresh_type)) {
      RefreshBGData();
   } else if (IS_TEXT_REFRESH(refresh_type)) {
      DelayedLanguageChange();
   } else {
      cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData();
      if (user_info != NULL) {
         _DarkState = elementFree;
         if (_DarkFuncRef != NULL) {
            _DarkState = ExecuteDarkFunc(_DarkFuncRef);
         }
         _AccessState = CheckWidgetAccess(user_info);
         _PreviousAppearanceState = _AppearanceState;
         MAX_STATE(_AppearanceState, GET_STATE(_DarkState), _DirectState, _AccessState);
         if (_PreviousAppearanceState != _AppearanceState) {
            ShowState();
         }
         ULONG_T dataset = user_info->get_DataSet();
         if (dataset != _DataSet) {
            SetColor(dataset);
            _DataSet = dataset;
         }
         if (_QWidget->isVisible()) {
            if (_ViewPending) {
               _ViewPending = false;
               View();
            }
         }
      } else {
         ErrorPrintf("user info is NULL while executing check appearance\n");
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

ULONG_T CWidgetBase::GetAppearanceState()
{
#ifndef QT_PLUGIN
   return _AppearanceState;
#endif
   return 0;
}

void CWidgetBase::Show()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _DirectState = elementFree;
   _PreviousAppearanceState = _AppearanceState;
   MAX_STATE(_AppearanceState, GET_STATE(_DarkState), _DirectState, _AccessState);
   if (_AppearanceState != _PreviousAppearanceState) {
      ShowState();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::Hide()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _DirectState = elementInvisible;
   _PreviousAppearanceState = _AppearanceState;
   MAX_STATE(_AppearanceState, GET_STATE(_DarkState), _DirectState, _AccessState);
   if (_AppearanceState != _PreviousAppearanceState) {
      ShowState();
   }
WMETHOD_VOID_EPILOG
#endif
}


#define HIDE(type,widget) \
      type * w = static_cast<type*>(widget); \
      if (w != NULL) { \
         w->Hide(); \
      }

void CWidgetBase::Hide(WIDGET_PTR widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (widget->inherits("CWidgetStack")) {
      HIDE(CWidgetStack,widget)
   } else if (widget->inherits("CComposedStack")) {
      HIDE(CComposedStack,widget)
   } else if (widget->inherits("CTabWidget")) {
      HIDE(CTabWidget,widget)
   } else if (widget->inherits("CFrame")) {
      HIDE(CFrame,widget)
   } else if (widget->inherits("CFixText")) {
      HIDE(CFixText,widget)
   } else if (widget->inherits("CInfoLabel")) {
      HIDE(CInfoLabel,widget)
   } else if (widget->inherits("CProtocolWindow")) {
      HIDE(CProtocolWindow,widget)
   } else if (widget->inherits("CGroupBox")) {
      HIDE(CGroupBox,widget)
   } else if (widget->inherits("CButtonGroup")) {
      HIDE(CButtonGroup,widget)
   } else if (widget->inherits("CActValue")) {
      HIDE(CActValue,widget)
   } else if (widget->inherits("CListView")) {
      HIDE(CListView,widget)
   } else if (widget->inherits("CReqValue")) {
      HIDE(CReqValue,widget)
   } else if (widget->inherits("CToolButton")) {
      HIDE(CToolButton,widget)
   } else if (widget->inherits("CPushButton")) {
      HIDE(CPushButton,widget)
   } else if (widget->inherits("CStateButton")) {
      HIDE(CStateButton,widget)
   } else if (widget->inherits("CRadioButton")) {
      HIDE(CRadioButton,widget)
   } else if (widget->inherits("CCheckBox")) {
      HIDE(CCheckBox,widget)
   } else if (widget->inherits("CComboBox")) {
      HIDE(CComboBox,widget)
   } else if (widget->inherits("CTable")) {
      HIDE(CTable,widget)
   } else if (widget->inherits("CGraphicsView")) {
      HIDE(CGraphicsView,widget)
   } else if (widget->inherits("CProcGraphic")) {
      HIDE(CProcGraphic,widget)
   } else if (widget->inherits("CRingGraphic")) {
      HIDE(CRingGraphic,widget)
   } else if (widget->inherits("CCoordSystem")) {
      HIDE(CCoordSystem,widget)
   } else if (widget->inherits("CVideo")) {
      HIDE(CVideo,widget)
   } else if (widget->inherits("CAlarmWidget")) {
      HIDE(CAlarmWidget,widget)
   } else if (widget->inherits("CTextEdit")) {
      HIDE(CTextEdit,widget)
   } else if (widget->inherits("CScrollBar")) {
      HIDE(CScrollBar,widget)
   } else if (widget->inherits("CSlider")) {
      HIDE(CSlider,widget)
   } else if (widget->inherits("CSpinBox")) {
      HIDE(CSpinBox,widget)
   } else if (widget->inherits("CProgressBar")) {
      HIDE(CProgressBar,widget)
   } else if (widget->inherits("CTime")) {
      HIDE(CTime,widget)
   } else if (widget->inherits("CDate")) {
      HIDE(CDate,widget)
   } else if (widget->inherits("CDateTime")) {
      HIDE(CDateTime,widget)
   } else if (widget->inherits("CVirtualKeyboard")) {
      HIDE(CVirtualKeyboard,widget)
   } else if (widget->inherits("CWidget")) {
      HIDE(CWidget,widget)
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::Disable()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _DirectState = elementDisabled;
   _PreviousAppearanceState = _AppearanceState;
   MAX_STATE(_AppearanceState, GET_STATE(_DarkState), _DirectState, _AccessState);
   if (_AppearanceState != _PreviousAppearanceState) {
      ShowState();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::Enable()
{
#ifndef QT_PLUGIN
#endif
}

void CWidgetBase::SetWidgetActive(QWidget * widget, BOOL_T state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (IsCustomWidget(widget)) {
      SetActive(widget, state);
   }
#ifdef QT4
   const QObjectList children = widget->children();
   QObjectList::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * object = (*i);
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         SetWidgetActive(child, state);
      }
      ++i;
   }
#else
   const QObjectList * children = widget->children();
   if (children == NULL) return;
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) return;
   QObject * object = NULL;
   while ((object = i.current())) {
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         SetWidgetActive(child, state);
      }
      ++i;
   }
#endif
   WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetActive(QWidget * widget, BOOL_T state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (widget->inherits("CWidgetStack")) {
      ((CWidgetStack*)widget)->SetActive(state);
   } else if (widget->inherits("CComposedStack")) {
      ((CComposedStack*)widget)->SetActive(state);
   } else if (widget->inherits("CTabWidget")) {
      ((CTabWidget*)widget)->SetActive(state);
   } else if (widget->inherits("CFrame")) {
      ((CFrame*)widget)->SetActive(state);
   } else if (widget->inherits("CFixText")) {
      ((CFixText*)widget)->SetActive(state);
   } else if (widget->inherits("CInfoLabel")) {
      ((CInfoLabel*)widget)->SetActive(state);
   } else if (widget->inherits("CProtocolWindow")) {
      ((CProtocolWindow*)widget)->SetActive(state);
   } else if (widget->inherits("CGroupBox")) {
      ((CGroupBox*)widget)->SetActive(state);
   } else if (widget->inherits("CButtonGroup")) {
      ((CButtonGroup*)widget)->SetActive(state);
   } else if (widget->inherits("CActValue")) {
      ((CActValue*)widget)->SetActive(state);
   } else if (widget->inherits("CListView")) {
      ((CListView*)widget)->SetActive(state);
   } else if (widget->inherits("CReqValue")) {
      ((CReqValue*)widget)->SetActive(state);
   } else if (widget->inherits("CToolButton")) {
      ((CToolButton*)widget)->SetActive(state);
   } else if (widget->inherits("CPushButton")) {
      ((CPushButton*)widget)->SetActive(state);
   } else if (widget->inherits("CStateButton")) {
      ((CStateButton*)widget)->SetActive(state);
   } else if (widget->inherits("CRadioButton")) {
      ((CRadioButton*)widget)->SetActive(state);
   } else if (widget->inherits("CCheckBox")) {
      ((CCheckBox*)widget)->SetActive(state);
   } else if (widget->inherits("CComboBox")) {
      ((CComboBox*)widget)->SetActive(state);
   } else if (widget->inherits("CTable")) {
      ((CTable*)widget)->SetActive(state);
   } else if (widget->inherits("CGraphicsView")) {
     ((CGraphicsView*)widget)->SetActive(state);
   } else if (widget->inherits("CProcGraphic")) {
     ((CProcGraphic*)widget)->SetActive(state);
   } else if (widget->inherits("CRingGraphic")) {
     ((CRingGraphic*)widget)->SetActive(state);
   } else if (widget->inherits("CCoordSystem")) {
      ((CCoordSystem*)widget)->SetActive(state);
   } else if (widget->inherits("CVideo")) {
     ((CVideo*)widget)->SetActive(state);
   } else if (widget->inherits("CAlarmWidget")) {
     ((CAlarmWidget*)widget)->SetActive(state);
   } else if (widget->inherits("CTextEdit")) {
     ((CTextEdit*)widget)->SetActive(state);
   } else if (widget->inherits("CScrollBar")) {
     ((CScrollBar*)widget)->SetActive(state);
   } else if (widget->inherits("CVirtualKeyboard")) {
     ((CVirtualKeyboard*)widget)->SetActive(state);
   } else if (widget->inherits("CWidget")) {
      ((CWidget*)widget)->SetActive(state);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetActive(BOOL_T state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _IsActive = state;
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetGroupAccess(ULONG_T group_id, int access, int level)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (group_id >= MAX_ACCESS_GROUPS) {
      return;
   }
   if (level > 0) {
      if (_GroupAccess[group_id] >= access) {
         return;
      }
   }
   if (access <= (int)CWidget::WriteAccess) {
      _GroupAccess[group_id] = access;
   }
WMETHOD_VOID_EPILOG
#endif
}

#define SET_ACCESS_TYPE(widget,widget_type,group,access,level) \
   widget_type * w = (widget_type*)widget; \
   w->SetGroupAccess(group,access,level);

void CWidgetBase::SetGroupAccess(QWidget * widget, ULONG_T group_id, int access, BOOL_T track_parents, int level)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (widget == NULL) {
      return;
   }
   CWidgetBase * base_widget = CWidgetMap::BaseWidget(widget);
   if (base_widget != NULL) {
      base_widget->SetGroupAccess(group_id, access, level);
   }
   if (track_parents) {
      QObject * parent = widget->parent();
      if (parent != NULL) {
         if (parent->isWidgetType()) {
            QWidget * parent_widget = (QWidget*)parent;
            SetGroupAccess(parent_widget, group_id, access, track_parents, level + 1);
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

CPage * CWidgetBase::MyPage(QWidget * widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (widget == NULL) {
      return NULL;
   }
   QObject * parent = widget->parent();
   if (parent == NULL) {
      return NULL;
   } else {
      if (parent->isWidgetType()) {
         QWidget * parent_widget = (QWidget*)parent;
         if (parent_widget->inherits("CPage")) {
            return (CPage*)parent_widget;
         } else {
            return MyPage(parent_widget);
         }
      } else {
         return MyPage((QWidget*)parent->parent());
      }
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

CWidgetBase * CWidgetBase::BaseWidget(QWidget * widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CWidgetBase * base_widget = NULL;
   if (widget != NULL) {
      base_widget = CWidgetMap::BaseWidget(widget);
   }
   return base_widget;
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

QString CWidgetBase::FromUtf8(const QString & text)
{
   QString utf8Text = text.toUtf8();
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!text.isEmpty()) {
      int len = text.length();
      int i = 0;
      for (i=0; i<len; i++) {
#ifdef QT4
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
         unsigned char c = text[i].toLatin1();
#else
         unsigned char c = text[i].toAscii();
#endif
#else
         unsigned char c = (unsigned char)text[i];
#endif
         unsigned char cmsb = ((c >> 4) & 0x0f);
         if (cmsb > 7) {
            if (cmsb == 0x0c || cmsb == 0x0d) {
               if ((i + 1) >= len) {
                  // dereferencing i+1 in this case may crash the application
                  ErrorPrintf("invalid string (utf8 length: (%d,%d)) <%s> : %d\n", i, len, CONST_STRING(text), __LINE__);
                  return text;
//                  return QString::fromUtf8(CONST_STRING(text));
               }
               // first of 2 octet
#ifdef QT4
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
               unsigned char c1 = text[i+1].toLatin1();
#else
               unsigned char c1 = text[i+1].toAscii();
#endif
#else
               unsigned char c1 = (unsigned char)text[i+1];
#endif
               if (c1 >> 7) {
                  return QString::fromUtf8(CONST_STRING(text));
               } else {
                  // is affected by e4 ä and other german umlauts
//                  ErrorPrintf("invalid string (utf8 (%02x)) <%s> : %d\n", (unsigned int)c1, CONST_STRING(text), __LINE__);
               }
            } else if (cmsb == 0x0e) {
               // first of 3 octet
               unsigned char c1 = 0;
               unsigned char c2 = 0;
#ifdef QT4
               if ((i + 1) < len) {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
                  c1 = text[i+1].toLatin1();
#else
                  c1 = text[i+1].toAscii();
#endif
               }
               if ((i + 2) < len) {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
                  c2 = text[i+2].toLatin1();
#else
                  c2 = text[i+2].toAscii();
#endif
               }
#else
               if ((i + 1) < len) {
                  c1 = (unsigned char)text[i+1];
               }
               if ((i + 2) < len) {
                  c2 = (unsigned char)text[i+2];
               }
#endif
               if ((c1 >> 7) && (c2 >> 7)) {
                  return QString::fromUtf8(CONST_STRING(text));
               } else {
                  // is affected by e4 ä and other german umlauts
//                  ErrorPrintf("invalid string (utf8 (%02x,%02x)) <%s> : %d\n", (unsigned int)c1, (unsigned int)c2, CONST_STRING(text), __LINE__);
               }
            }
         }
      }
   }
WMETHOD_RC_EPILOG("?e")
#endif
   return text;
}

QString CWidgetBase::FromLatin(const QString & text)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_RC_EPILOG("?e")
#endif
   return text;
}

void CWidgetBase::ShowState()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_AppearanceState == elementFree) {
      ForceShow();
   } else if (_AppearanceState == elementDisabled) {
      ForceDisable();
   } else if (_AppearanceState == elementInvisible) {
      ForceHide();
   }
WMETHOD_VOID_EPILOG
#endif
}

int CWidgetBase::Access(ULONG_T group_id)
{
   if (group_id < MAX_ACCESS_GROUPS) {
      return _GroupAccess[group_id];
   } else {
      return (int)(CWidget::NoAccess);
   }
}

ULONG_T CWidgetBase::CheckWidgetAccess(USER_INFO_PTR user_info)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   ULONG_T group_id = user_info->get_GroupId();
   int access = Access(group_id);
   if (access == 0) {
      return elementInvisible;
   } else if (access == 1) {
      return elementDisabled;
   } else if (access == 2) {
      return elementFree;
   }
WMETHOD_RC_EPILOG(elementDisabled)
#endif
   return elementDisabled;
}

void CWidgetBase::ForceShow()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!_QWidget->inherits("CPage")) {
      _QWidget->show();
   }
   _QWidget->setEnabled(true);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::ForceHide()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _QWidget->hide();
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::ForceDisable()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!_QWidget->inherits("CPage")) {
      _QWidget->show();
   }
   _QWidget->setEnabled(false);
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::ForceEnable()
{
#ifndef QT_PLUGIN
#endif
}

#ifdef QT4
void CWidgetBase::SetColors(QObject * object, ULONG_T dataset, const QColor & color)
{
#ifndef QT_PLUGIN
   if (object->isWidgetType()) {
      QWidget * widget = dynamic_cast<QWidget*>(object);
      if (widget != NULL) {
         if (widget->inherits("CProcGraphic")) 
         {
            widget->setPalette(_PaletteMap.Palette(widget));
            ((CProcGraphic*)widget)->View();
         }
         else if (dataset == 0) {
            widget->setPalette(_PaletteMap.Palette(widget));
         } else {
            if (widget->inherits("QLineEdit") ||
                widget->inherits("QTextEdit") ||
                widget->inherits("QComboBox")) {
               if (widget->isEnabled()) {
                  widget->setPalette(_PaletteMap.Palette(widget));
               } else {
                  setPaletteBackgroundColor(widget, color);
               }
            } else {
               setPaletteBackgroundColor(widget, color);
            }
         }
      } else {
         UNEXPECTED_BRANCH()
      }
   }
   const QObjectList children = object->children();
   QObjectList::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * child = (*i);
      SetColors(child, dataset, color);
      ++i;
   }
#endif
}
#endif

void CWidgetBase::SetColor(ULONG_T dataset)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_QWidget->inherits("CPage")) {
#ifdef QT4
      CAppFrame * appFrame = _AppFrame;
      if (appFrame != NULL) {
         CPage * page = dynamic_cast<CPage*>(_QWidget);
         CPage * actPage = appFrame->ActPage();
         if (page != NULL && actPage != NULL) {
            if (page == actPage) {
               QColor bgColor = appFrame->getBGColor();
               SetColors(page, dataset, bgColor);
            }
         }
      }
#else
      if (dataset == 0) {
         _QWidget->setPaletteBackgroundColor(_OrgBackgroundColor);
      } else {
         _QWidget->setPaletteBackgroundColor(_AppFrame->getBGColor());
      }
#endif
   } else {
#ifdef DEPRECATED_15
      if (_BackgroundSensitive) {
         if (dataset == 0) {
            _QWidget->setPaletteBackgroundColor(_OrgBackgroundColor);
         } else {
            _QWidget->setPaletteBackgroundColor(_AppFrame->getBGMarkColor());
         }
      }
#endif
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetMappedBackgroundColor()
{
   SetMappedBackgroundColor(_QWidget);
}

void CWidgetBase::SetMappedBackgroundColor(QWidget * widget)
{
#ifndef QT_PLUGIN
   _PaletteMap.SetPalette(widget, widget->palette());
#endif
}

void CWidgetBase::ClearMappedBackgroundColor()
{
   ClearMappedBackgroundColor(_QWidget);
}

void CWidgetBase::ClearMappedBackgroundColor(QWidget * widget)
{
#ifndef QT_PLUGIN
   _PaletteMap.ClearBackgroundColor(widget);
#endif
}

// debugging and logging

static char _Text[0x2000];

static const char * LogFileName(unsigned long flags)
{
   if (flags & REFRESH_PROPAGATION) {
      return "GUIRefresh.log";
   } else if (flags & CONNECTION_HIERARCHY) {
      return "GUIHierarchy.log";
   } else if (flags & FUNCTION_EXECUTION) {
      return "GUIExecution.log";
   } else if (flags & FUNCTION_INIT) {
      return "GUIInit.log";
   } else if (flags & VARIABLE_INIT) {
      return "GUIInit.log";
   } else if (flags & CONTEXT_SETTINGS) {
      return "GUIContext.log";
   } else if (flags & CONNECTIONS) {
      return "GUIConnections.log";
   } else if (flags & GUI_INFO) {
      return "GUIInfo.log";
   } else {
      return "GUI.log";
   }
}

void CWidgetBase::DebugPrintf(unsigned long flags,
                              const char * fmt_str, ...)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!(flags & _DebugFlags)) return;
   va_list args;
   va_start(args, fmt_str);
   _vsnprintf(_Text, sizeof(_Text)-1, fmt_str, args);
   va_end(args);
   char file_name[512] = {0};
   SafePrintf(file_name, sizeof(file_name), "%s/%s", cResources::LogPath().c_str(), LogFileName(flags));
   try {
      FILE * stream = fopen(file_name, "a");
      if (stream != NULL) {
         fprintf(stream, "%s", _Text);
         fclose(stream);
      }
   } catch (...) {
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::WidgetError(const char * fmt_str, ...)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   va_list args;
   va_start(args, fmt_str);
   _vsnprintf(_Text, sizeof(_Text)-1, fmt_str, args);
   va_end(args);
   cTimeObject t;
   QString qTimestamp = (CONST_STRING_T)t;
   QString qfile_name;
   qfile_name.sprintf("%s/GUIErrors.log", cResources::LogPath().c_str());
   try {
      FILE * stream = fopen(CONST_STRING(qfile_name), "a");
      if (stream != NULL) {
         fprintf(stream, "%s: %s", CONST_STRING(qTimestamp), _Text);
         fclose(stream);
      }
   } catch (...) {
   }
   ErrorPrintf("%s\n", _Text);
WMETHOD_VOID_EPILOG
#endif
}

static void ClearFile(const char * file_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   char file[512] = {0};
   SafePrintf(file, sizeof(file), "%s/%s", cResources::LogPath().c_str(), file_name);
   try {
      FILE * stream = fopen(file, "w");
      if (stream != NULL) {
         fclose(stream);
      }
   } catch (...) {
   }
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::LogInitialize(unsigned long flags)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _DebugFlags = flags;
   ClearFile("GUIRefresh.log");
   ClearFile("GUIHierarchy.log");
   ClearFile("GUIConnections.log");
   ClearFile("GUIExecution.log");
   ClearFile("GUIInit.log");
   ClearFile("GUIContext.log");
   ClearFile("GUIErrors.log");
   ClearFile("GUIInfo.log");
   ClearFile("GUI.log");
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::SetFlag(ULONG_T flag)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Flags = _Flags | flag;
WMETHOD_VOID_EPILOG
#endif
}

void CWidgetBase::ResetFlag(ULONG_T flag)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Flags = _Flags & (~flag);
WMETHOD_VOID_EPILOG
#endif
}

BOOL_T CWidgetBase::Flag(ULONG_T flag)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _Flags & flag;
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

#ifdef QT4

QString CWidgetBase::Name() const
{
   return _QWidget->objectName();
}

QString CWidgetBase::className() const
{
   return _QWidget->metaObject()->className();
}

QString CWidgetBase::Name(QWidget * widget)
{
   return widget->objectName();
}

QString CWidgetBase::className(QWidget * widget)
{
   return widget->metaObject()->className();
}

#else

QString CWidgetBase::Name() const
{
   return _QWidget->name();
}

QString CWidgetBase::className() const
{
   return _QWidget->className();
}

QString CWidgetBase::Name(QWidget * widget)
{
   return widget->name();
}

QString CWidgetBase::className(QWidget * widget)
{
   return widget->className();
}

#endif

#ifdef QT4

void CWidgetBase::setWFlags(unsigned int flags)
{
   _QWidget->setWindowFlags(qt4WindowFlags(flags));
}

Qt::WindowFlags CWidgetBase::qt4WindowFlags(unsigned int flags)
{
   Qt::WindowFlags windowFlags = 0;
   if (flags & WType_TopLevel) {
      windowFlags |= Qt::Window;
   }
   if (flags & WType_Dialog) {
      windowFlags |= Qt::Dialog;
   }
   if (flags & WType_Popup) {
      windowFlags |= Qt::Popup;
   }
   if (flags & WType_Desktop) {
      windowFlags |= Qt::Desktop;
   }
   if (flags & WStyle_Customize) {
      windowFlags |= Qt::CustomizeWindowHint;
   }
   if (flags & WStyle_NormalBorder) {
      windowFlags |= 0;
   }
   if (flags & WStyle_DialogBorder) {
      windowFlags |= Qt::MSWindowsFixedSizeDialogHint;
   }
   if (flags & WStyle_NoBorder) {
      windowFlags |= Qt::MSWindowsFixedSizeDialogHint;
   }
   if (flags & WStyle_NoBorderEx) {
      windowFlags |= Qt::FramelessWindowHint;
   }
   if (flags & WStyle_Title) {
      windowFlags |= Qt::WindowTitleHint;
   }
   if (flags & WStyle_SysMenu) {
      windowFlags |= Qt::WindowSystemMenuHint;
   }
   if (flags & WStyle_Minimize) {
      windowFlags |= Qt::WindowMinimizeButtonHint;
   }
   if (flags & WStyle_Maximize) {
      windowFlags |= Qt::WindowMaximizeButtonHint;
   }
   if (flags & WStyle_MinMax) {
      windowFlags |= Qt::WindowMinMaxButtonsHint;
   }
   if (flags & WStyle_ContextHelp) {
      windowFlags |= Qt::WindowContextHelpButtonHint;
   }
   if (flags & WStyle_Tool) {
      windowFlags |= Qt::Tool;
   }
   return windowFlags;
}

void CWidgetBase::setBackgroundMode(BackgroundMode mode)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
}

QColor CWidgetBase::paletteBackgroundColor(QWidget * widget)
{
   return widget->palette().color(widget->backgroundRole());
}

void CWidgetBase::setPaletteBackgroundColor(QWidget * widget, const QColor & color)
{
   QPalette palette = widget->palette();
   palette.setColor(widget->backgroundRole(), color);
   widget->setPalette(palette);
}

QColor CWidgetBase::paletteForegroundColor(QWidget * widget)
{
   return widget->palette().color(widget->foregroundRole());
}

void CWidgetBase::setPaletteForegroundColor(QWidget * widget, const QColor & color)
{
   QPalette palette = widget->palette();
   palette.setColor(widget->foregroundRole(), color);
   widget->setPalette(palette);
}

QBrush CWidgetBase::paletteBackgroundBrush(QWidget * widget)
{
   QPalette palette = widget->palette();
   return palette.brush(QPalette::Window);
}

QPixmap * CWidgetBase::paletteBackgroundPixmap(QWidget * widget)
{
#pragma message(__LOC__ "not ported yet")
NOT_PORTED("not ported yet")
return NULL;
}

int CWidgetBase::getScaledHeight(QWidget * widget, int baseValue) const
{
   int iScaledValue = baseValue;
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   // search parent cpage
   QWidget * pWidget = widget;
   BOOL_T similarSizeAsFramePage = false;

   while (pWidget && !pWidget->inherits("CPage")) {
       if (pWidget->inherits("CAppFrame")) {
           similarSizeAsFramePage = true;
           break;
       }
       pWidget = pWidget->parentWidget();
   }

   // cpage found
   if ((pWidget != NULL) && !similarSizeAsFramePage) {
       similarSizeAsFramePage = static_cast<CPage *>(pWidget)->similarSizeAsFramePage();
#ifdef QT_PLUGIN
       PluginPrintf("%s similarSizeAsFramePage %d\n", CONST_STRING(pWidget->objectName()), similarSizeAsFramePage);
#endif

   }

   if (similarSizeAsFramePage) {
      qreal displayScale = CAppFrame::yDisplayScale();
      if (displayScale != 1.0f) {
         qreal qScaledValue = qreal(iScaledValue) * displayScale;
         iScaledValue = qRound(qScaledValue);
      }
   }
#endif

   return iScaledValue;
}

int CWidgetBase::getScaledWidth(QWidget * widget, int baseValue) const
{
   int iScaledValue = baseValue;
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
   // search parent cpage
   BOOL_T similarSizeAsFramePage = false;
   QWidget * pWidget = widget->parentWidget();
   while (pWidget && !pWidget->inherits("CPage")) {
       pWidget = pWidget->parentWidget();
   }

   // cpage found
   if (pWidget != NULL) {
       similarSizeAsFramePage = static_cast<CPage *>(pWidget)->similarSizeAsFramePage();
   }

   if (similarSizeAsFramePage) {
      qreal displayScale = CAppFrame::xDisplayScale();
      if (displayScale != 1.0f) {
          qreal qScaledValue = qreal(iScaledValue) * displayScale;
          iScaledValue = qRound(qScaledValue);
      }
    }
#endif

   return iScaledValue;
}

int CWidgetBase::getScaledPointSize(QString &fontName, int baseValue) const
{
    int iScaledValue = baseValue;
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    // Scale point size of font
    qreal scale = CAppFrame::yDisplayScale();
    if (scale != 1.0f) {
        QFont qFont(fontName, iScaledValue);
        QFontInfo qFontInfo(qFont);
        int pixelSizeOfFont = qFontInfo.pixelSize();
        qreal scaledValue = qreal(pixelSizeOfFont) * scale;
        pixelSizeOfFont = qRound(scaledValue);

        // Change font with scaled pixelSize
        qFont.setPixelSize(pixelSizeOfFont);
        qFontInfo = QFontInfo(qFont);
        iScaledValue = qFontInfo.pointSize() - 1; // decrement scaled font
    }
#endif

    return iScaledValue;
}


static void printGuiStructure(QObject * object, int level)
{
#ifdef QT4
   const char * fileName = "e:/temp/qt4gui.txt";
   QString name = object->objectName();
#else
   const char * fileName = "e:/temp/qt3gui.txt";
   QString name = object->name();
#endif
#ifdef QT4
   FILE * stream = fopen(fileName, "a");
   if (stream != NULL) {
      int spaces = level * 2;
      int n = 0;
      for (n=0; n<spaces; n++) {
         fprintf(stream, ".");
      }
      QString spec;
      if (object->isWidgetType()) {
         spec += "widget";
         QWidget * widget = static_cast<QWidget*>(object);
         if (CWidgetBase::IsCustomWidget(widget)) {
            spec += " and custom";
         }
      } else {
         spec += "no widget";
      }
      fprintf(stream, "%s %s\n", CONST_STRING(name), CONST_STRING(spec));
      fclose(stream);
   }
   const QObjectList children = object->children();
   QObjectList::const_iterator i = children.begin();
   while (i != children.end()) {
      QObject * child = (*i);
      printGuiStructure(child, level + 1);
      ++i;
   }
#else
   FILE * stream = fopen(fileName, "a");
   if (stream != NULL) {
      int spaces = level * 2;
      int n = 0;
      for (n=0; n<spaces; n++) {
         fprintf(stream, ".");
      }
      QString spec;
      if (object->isWidgetType()) {
         spec += "widget";
         QWidget * widget = static_cast<QWidget*>(object);
         if (CWidgetBase::IsCustomWidget(widget)) {
            spec += " and custom";
         }
      } else {
         spec += "no widget";
      }
      fprintf(stream, "%s %s\n", (const char*)name, (const char*)spec);
      fclose(stream);
   }
   const QObjectList * children = object->children();
   if (children == NULL) return;
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) return;
   QObject * child = NULL;
   while ((child = i.current())) {
      printGuiStructure(child, level + 1);
      ++i;
   }
#endif
}

QObject * CWidgetBase::child(const char * objName, const char * inheritsClass, bool recursiveSearch)
{
   return ::child((QObject*)_QWidget, objName, inheritsClass, recursiveSearch);
}

QObject * CWidgetBase::_child(const char * objName, const char * inheritsClass, bool recursiveSearch)
{
   return CWidgetBase::child(objName, inheritsClass, recursiveSearch);
}

QObject * CWidgetBase::child(const std::string & objName, const char * inheritsClass, bool recursiveSearch)
{
   return ::child((QObject*)_QWidget, objName, inheritsClass, recursiveSearch);
}

QObject * CWidgetBase::child(const QString & objName, const char * inheritsClass, bool recursiveSearch)
{
   return ::child((QObject*)_QWidget, objName, inheritsClass, recursiveSearch);
}

#endif
