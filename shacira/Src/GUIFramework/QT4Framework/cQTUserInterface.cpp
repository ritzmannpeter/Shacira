//## begin module%40054B200109.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40054B200109.cm

//## begin module%40054B200109.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40054B200109.cp

/// PR 06.04.05 - mapped SetNewLanguage method to _AppFrame->SetNewLanguage(..)
///             - placed SetNewLanguage(..) call at the end of the constructor
///               the old version didnt work, when startuo language != default
///               because two different translator objects have been used, one
///               in cQtUserInterface and one in CAppFrame
/// PR 02.06.05 - changed distribution of init functions on threads
///               to avoid calling gui init functions by non gui threads
/// PR 03.06.05 - added LoadCCSInterface also to GUI thread execution list
/// PR            to avoid concurrent widget access problems
/// PR 20.07.05 - method Start now returns the return value of exec()
/// PR 02.08.05 - general redesign of startup process
///               removed cSystemLoader and the related communication object
///               the startup process now is executed by the GUI thread
///               CCSInterface functions LoadCCSInterface and StartCCSInterface
///               are executed asynchronously
/// PR 01.09.05 - added scrollable screen functionality
/// PR 26.09.05 - deleting startup form after startup to cancel timer actions
///               of startup form
/// PR 24.08.06 - Maximize window only when full screen is active or
///               when flag SHOW_MAXIMIZED is set

#include "FirstHeader.h"
#ifdef QT4
#include "CScrollView.h"
#else
#include <qscrollview.h>
#endif

#include "System/Database/cContext.h"
#include "GUIFramework/Interface/cCCSInterface.h"
#include "GUIFramework/cNodeList.h"
#include "GUIFramework/cNode.h"
#include "cContextExplorer.h"
#include "cQTUserInterface.h"
#include "CAppFrame.h"
#include "CStartupForm.h"
#include "uiupdate.h"

extern CAppFrame * CreateAppFrame();

#include "CGroupSelectButton.h"
#ifndef QT4
#include <qobjectlist.h>
#endif

static char _Message[0x2000] = {0};

#define GUI_IDLE_TIME  400

#define FC_UNDEFINED             0
#define FC_LOAD_CCS_INTERFACE    1
#define FC_START_CCS_INTERFACE   2

class cAsyncInitFunction : public cThread
{
public:
   cAsyncInitFunction(cCCSInterface * ccs_interface, ULONG_T function_code = FC_UNDEFINED)
   {
      _ErrorThrown = false;
      _Terminated = false;
      _FunctionCode = function_code;
      _CCSInterface = ccs_interface;
      _ReturnCode = false;
   };
   virtual ~cAsyncInitFunction()
   {
   };
   virtual int onMain(void * extra)
   {
      try {
         _ReturnCode = false;
         if (_CCSInterface == NULL) {
            _Terminated = true;
         } else {
            switch (_FunctionCode) {
            case FC_LOAD_CCS_INTERFACE:
               _ReturnCode = _CCSInterface->Load();
               break;
            case FC_START_CCS_INTERFACE:
               _ReturnCode = _CCSInterface->Start();
               break;
            }
            _Terminated = true;
         }
      } catch (cError & e) {
         _ErrorThrown = true;
         _Error = e;
         _ReturnCode = false;
         _Terminated = true;
      } catch (...) {
         _ErrorThrown = true;
         _Error = cError();
         _ReturnCode = false;
         _Terminated = true;
      }
      return 0;
   };
   void Execute()
   {
      start();
   };
   BOOL_T Terminated()
   {
      return _Terminated;
   };
   BOOL_T ReturnCode()
   {
      return _ReturnCode;
   };
public:
   BOOL_T _ErrorThrown;
   cError _Error;
private:
   cCCSInterface * _CCSInterface;
   ULONG_T _FunctionCode;
   BOOL_T _Terminated;
   BOOL_T _ReturnCode;
};

static BOOL_T ExecuteAsyncInitFunction(cCCSInterface * ccs_interface, ULONG_T function_code)
{
   cAsyncInitFunction init_function(ccs_interface, function_code);
   init_function.Execute();
   BOOL_T terminated = false;
   while (!terminated) {
      qApp->processEvents();
      cSystemUtils::Suspend(100);
      terminated = init_function.Terminated();
   }
   return init_function.ReturnCode();
}

cQTUserInterface::cQTUserInterface()
      : _Application(NULL), _MainWidget(NULL), _MainLayout(NULL), _StartupForm(NULL), _AppFrame(NULL), _PageContainer(NULL), _WidgetStack(NULL), _PageList(NULL), _Context(NULL)
{
_ASSERT_UNCOND
}

cQTUserInterface::cQTUserInterface(const cQTUserInterface &right)
      : _Application(NULL), _MainWidget(NULL), _MainLayout(NULL), _StartupForm(NULL), _AppFrame(NULL), _PageContainer(NULL), _WidgetStack(NULL), _PageList(NULL), _Context(NULL)
{
_ASSERT_UNCOND
}

cQTUserInterface::cQTUserInterface (QApplication *app, BOOL_T remote, const QString & language, cConsole *console, const QString & title, QPixmap *icon)
      : _Application(NULL), _MainWidget(NULL), _MainLayout(NULL), _StartupForm(NULL), _AppFrame(NULL), _PageContainer(NULL), _WidgetStack(NULL), _PageList(NULL), _Context(NULL)
  , cUserInterface(remote, CONST_STRING(language), console)
{
   CWidgetBase::SetGUIThreadId();
   WIDGET_FLAGS_TYPE f = 0;
   if (CWidgetBase::Flag(FULL_SCREEN)) {
#ifdef QT4
      f = Qt::CustomizeWindowHint | Qt::FramelessWindowHint;
#else
      f = Qt::WStyle_Customize | Qt::WStyle_NoBorder;
#endif
   }
   _Application = app;
   if (CWidgetBase::Flag(SCROLLABLE_SCREEN)) {
#ifdef QT4
      _MainWidget = new CScrollView(NULL);
      _MainWidget->setObjectName("MainWidget");
#else
      _MainWidget = new QScrollView(NULL, "MainWidget", f);
#endif
   } else {
#ifdef QT4
      _MainWidget = new QWidget(NULL, f);
      _MainWidget->setObjectName("MainWidget");
#else
      _MainWidget = new QWidget(NULL, "MainWidget", f);
#endif
   }
#ifdef QT4
   _MainLayout = new QVBoxLayout(_MainWidget);
   _MainLayout->setObjectName("main_layout");
   _MainLayout->setContentsMargins(0, 0, 0, 0);
   _MainLayout->setSpacing(0);
   _AppFrame = CreateAppFrame();
   _AppFrame->setPageContainerWidth(_AppFrame->GetPageContainer()->width());
   _AppFrame->setPageContainerHeight(_AppFrame->GetPageContainer()->height());
   _AppFrame->setParent(_MainWidget);
   _MainWidget->move(QPoint(0, 0));
   _MainLayout->addWidget(_AppFrame);
   if (title != NULL) {
      _MainWidget->setWindowTitle(title);
   } else {
      _MainWidget->setWindowTitle(_AppFrame->windowTitle());
   }
   if (icon != NULL) {
      _MainWidget->setWindowIcon(*icon);
   }
#else
   _MainLayout = new QVBoxLayout(_MainWidget, 0, 0, "main_layout"); 
   _AppFrame = CreateAppFrame();
   _AppFrame->reparent(_MainWidget, QPoint(0, 0));
   _MainLayout->addWidget(_AppFrame);
   if (title != NULL) {
      _MainWidget->setCaption(title);
   } else {
      _MainWidget->setCaption(_AppFrame->caption());
   }
   if (icon != NULL) {
      _MainWidget->setIcon(*icon);
   }
#endif
   if (CWidgetBase::Flag(SCROLLABLE_SCREEN)) {
#ifdef QT4
      if (_MainWidget->inherits("CScrollView")) {
         CScrollView * scrollView = static_cast<CScrollView*>(_MainWidget);
         scrollView->setWidget(_AppFrame);
         _AppFrame->setMinimumSize(1280,1024);
      }
#else
      if (_MainWidget->inherits("QScrollView")) {
         ((QScrollView*)_MainWidget)->addChild(_AppFrame);
         _AppFrame->setMinimumSize(1280,1024);
      }
#endif
   }

   CWidgetBase::SetAppFrame(_AppFrame);
   SetNewLanguage(language);
}


cQTUserInterface::~cQTUserInterface()
{
   qApp->processEvents();
   if (_MainWidget != NULL) {
      delete _MainWidget;
   }
}

void cQTUserInterface::Initialize (cCCSInterface *ccs_interface, cConsole *console)
{
   GUIInitialize(SH_PRE_UI_INSTANTIATION, _ActContext);
   _CCSInterface = ccs_interface;
   _Console = console;
   _PageContainer = _AppFrame->GetPageContainer();
   QVBoxLayout * layout = new QVBoxLayout(_PageContainer); 
   _WidgetStack = new CWidgetStack(_PageContainer, "WidgetStack");
   _WidgetStack->setFrameShape((_PageContainer)->frameShape());
   _WidgetStack->setFrameStyle((_PageContainer)->frameStyle());
   _WidgetStack->setMinimumSize((_PageContainer)->minimumSize());
   _WidgetStack->setMaximumSize((_PageContainer)->maximumSize());
#ifdef QT4
   layout->setContentsMargins(0, 0, 0, 0);
   layout->setSpacing(0);
   QSizePolicy policy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   policy.setHorizontalStretch(1);
   policy.setVerticalStretch(1);
   _WidgetStack->setSizePolicy(policy);
   _WidgetStack->SetPreventFromPropagation(true);
#else
   _WidgetStack->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding, 1, 1));
#endif
   layout->addWidget(_WidgetStack);
   _ContextChooser = new cContextExplorer(_AppFrame);
   CreateGroupDefs();
   CreateStartupForm();
   GUIInitialize(SH_POST_UI_INSTANTIATION, _ActContext);
}

int cQTUserInterface::Start (BOOL_T success)
{
#ifdef QT4
#pragma message(__LOC__ "not portable")
NOT_PORTED("not ported yet")
#else
   _Application->setMainWidget(_MainWidget);
#endif
   if (CWidgetBase::Flag(FULL_SCREEN)) {
      _MainWidget->showFullScreen();
   } else if (CWidgetBase::Flag(SHOW_MAXIMIZED)) {
      _MainWidget->showMaximized();
   } else {
      _MainWidget->showNormal();
   }
   StartGUI();
   if (_AppFrame != NULL) {
      if (_AppFrame->Flag(GUI_FLAG_RESTART)) {
         return 0;
      } else {
         return _Application->exec();
      }
   } else {
      return _Application->exec();
   }
}

BOOL_T cQTUserInterface::SetNewLanguage (const QString & language)
{
   if (_AppFrame != NULL) {
      return _AppFrame->SetNewLanguage(language);
   } else {
      return false;
   }
}

QString cQTUserInterface::GetLanguage ()
{
   if (_AppFrame != NULL) {
      return _AppFrame->GetLanguage();
   } else {
      return QString();
   }
}

BOOL_T cQTUserInterface::GUIInitialize (ULONG_T step, cContext *context)
{
   int thread_id = cSystemUtils::ThreadId();
   int gui_thread_id = CWidgetBase::GetGUIThreadId();
   if (thread_id == gui_thread_id) {
      return cUserInterface::GUIInitialize(step, context);
   } else {
      Error("gui init call step %d failed runtime system aborted", step);
      return false;
   }
}

void cQTUserInterface::StartGUI ()
{
   QString step = "starting GUI";
#ifdef lassma
   if (CWidgetBase::Flag(SYNC_USER_FUNCTIONS)) {
      cCCSInterface::SetUiUpdateFunction(ProcessEventQueue);
   }
#endif
   UiUpdate uiUpdate(CWidgetBase::Flag(SYNC_USER_FUNCTIONS));
   try {
      if (IsRemote()) {
         if (_CCSInterface->PrepareProcess()) {
            _NodeList = _CCSInterface->NodeList();
            _Process = _CCSInterface->Process();
            ChooseContext();
         } else {
            return;
         }
         Info(false, "load remote CCS service");
         step = "loading remote context";
         if (_CCSInterface->LoadRemote(_Context)) {
            step = "creating pages";
            CreatePages();
            step = "propagating connections";
            PropagateConnections();
            step = "propagating contexts";
            PropagateContexts();
            SetupWidgets();
            CWidgetBase::RefreshWidgetData();
            Info(false, "starting system");
            step = "starting system";
            StartSystem();
         } else {
            StartupError("failed to load remote CCS service");
         }
      } else {
         Info(false, "loading CCS service");
         step = "loading CCS interface";
         ProcessEvents();
         if (CCSLoadInterface()) {
            _NodeList = _CCSInterface->NodeList();
            step = "creating pages";
            ProcessEvents();
            CreatePages();
            ProcessEvents();
            step = "propagating connections";
            ProcessEvents();
            PropagateConnections();
            ProcessEvents();
            step = "propagating contexts";
            ProcessEvents();
            PropagateContexts();
            ProcessEvents();
            Info(false, "starting CCS service");
            step = "starting CCS interface";
            if (CCSStartInterface()) {
               Info(false, "starting system");
               step = "starting system";
               StartSystem();
            } else {
               StartupError("failed to start CCS service");
            }
         } else {
            StartupError("failed to load CCS service");
         }
      }
   } catch(cError & e) {
      SafePrintf(_Message, sizeof(_Message), "error %s while %s", e.ErrMsg().c_str(), CONST_STRING(step));
      StartupError(_Message);
   } catch(...) {
      SafePrintf(_Message, sizeof(_Message), "unknown exception while %s", CONST_STRING(step));
      StartupError(_Message);
   }
}

void cQTUserInterface::CreateGroupDefs ()
{
   CreateFreeGroupDefs(_AppFrame);
}

void cQTUserInterface::CreateFreeGroupDefs (QWidget *widget)
{
#ifdef QT4
   const QObjectList children = widget->children();
   QObjectList::const_iterator i = children.constBegin();
   while (i != children.constEnd()) {
      QObject * object = (*i);
      if (object->isWidgetType()) {
         QWidget * child = (QWidget*)object;
         if (child->inherits("CGroupSelectButton")) {
            CGroupSelectButton * select_button = (CGroupSelectButton*)child;
            QString group_name = select_button->getPageGroup();
            if (!group_name.isEmpty()) {
               CTabWidget * tab_widget = _AppFrame->TabWidget(group_name);
               if (tab_widget == NULL) {
                  tab_widget = new CTabWidget(_WidgetStack, CONST_STRING(group_name));
                  _WidgetStack->addWidget(tab_widget);
// dont call show on tab widget with Qt 4
// this seems to add the tab widget parallel to the widget stack (not clarified completeley)
//                  tab_widget->show();

// The following code sequences are default settings for the QTabWidget
//                  QSizePolicy policy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//                  policy.setHorizontalStretch(0);
//                  policy.setVerticalStretch(0);
//                  tab_widget->setSizePolicy(policy);
                  tab_widget->setObjectName(group_name);
                  _AppFrame->AddTabWidget(group_name, tab_widget);
               }
               QObject::connect(select_button,
                                SIGNAL(GroupSelected(QString)),
                                _AppFrame,
                                SLOT(SelectGroup(QString)));
               tab_widget->SetSelectButton(select_button);
//}
            }
         }
         CreateFreeGroupDefs(child);
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
         if (child->inherits("CGroupSelectButton")) {
            CGroupSelectButton * select_button = (CGroupSelectButton*)child;
            CONST_STRING_T group_name = select_button->getPageGroup();
            if (group_name != NULL) {
               CTabWidget * tab_widget = _AppFrame->TabWidget(group_name);
               if (tab_widget == NULL) {
                  tab_widget = new CTabWidget(_WidgetStack, group_name);
                  _WidgetStack->addWidget(tab_widget);
                  tab_widget->show();
                  tab_widget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding, 0, 0));
                  tab_widget->setName(group_name);
                  _AppFrame->AddTabWidget(group_name, tab_widget);
               }
               QObject::connect(select_button,
                                SIGNAL(GroupSelected(QString)),
                                _AppFrame,
                                SLOT(SelectGroup(QString)));
               tab_widget->SetSelectButton(select_button);
            }
         }
         CreateFreeGroupDefs(child);
      }
      ++i;
   }
#endif
}

void cQTUserInterface::CreatePages ()
{
   if (_NodeList == NULL) {
      ErrorPrintf("missing node list in CreatePages\n");
      return;
   }
   Info(false, "create pages");
   ProcessEvents();
   ULONG_T t = cSystemUtils::RealtimeOffset();
   STRING_LIST_T node_names;
   ULONG_T nodes = _NodeList->NodeNames(node_names);
   if (nodes > 0) {
      STRING_LIST_T::const_iterator i = node_names.cbegin();
      while (i != node_names.cend()) {
         cNode * node = _NodeList->Node((*i).c_str());
         CreatePages(node);
         ProcessEvents();
         i++;
      }
   }
   Info(true, "create pages done %d", cSystemUtils::RealtimeOffset() - t);
   ProcessEvents();
}

void cQTUserInterface::CreatePages (cNode *node)
{
   _AppFrame->SetCurrentContext(node->Context());
   Info(true, "create page list");
   _PageList = _AppFrame->CreatePageList(_WidgetStack);
   Info(true, "create page list done");
#ifdef QT4
   PageList::const_iterator i = _PageList->constBegin();
   while (i != _PageList->constEnd()) {
      CPage * page = (*i);
      QString group_name = page->getPageGroup();
      QString page_name = page->Name();
      Info(true, "create page  %s", CONST_STRING(page_name));
      CTabWidget * tab_widget = _AppFrame->TabWidget(group_name);
      if (tab_widget == NULL) {
         CWidgetBase::WidgetError("no group %s for page %s\n", CONST_STRING(group_name), CONST_STRING(page_name));
      } else {
         CGroupSelectButton * select_button = tab_widget->GetSelectButton();
         if (select_button == NULL) {
            CWidgetBase::WidgetError("no select button group %s\n", CONST_STRING(group_name));
         } else {
            page->SetSelectButton(select_button);
            _AppFrame->SetSelectButton(group_name, select_button);
            tab_widget->AddPage(page);
            page->SetTabWidget(tab_widget);
            QObject::connect(page,
                             SIGNAL(PageShown(CPage*)),
                             _AppFrame,
                             SLOT(SelectPage(CPage*)));
            _AppFrame->AddPage(page_name, page);
         }
      }
      Info(true, "create page  %s done", CONST_STRING(page_name));
      ProcessEvents();
      i++;
   }
#else
   CPage * page = NULL;
   for (page = _PageList->first(); page; page = _PageList->next() ) {
      CONST_STRING_T group_name = page->getPageGroup();
      CONST_STRING_T page_name = page->name();
      Info(true, "create page  %s", page_name);
      CTabWidget * tab_widget = _AppFrame->TabWidget(group_name);
      if (tab_widget == NULL) {
         CWidgetBase::WidgetError("no group %s for page %s\n", group_name, page_name);
      } else {
         CGroupSelectButton * select_button = tab_widget->GetSelectButton();
         if (select_button == NULL) {
            CWidgetBase::WidgetError("no select button group %s\n", group_name);
         } else {
            page->SetSelectButton(select_button);
            _AppFrame->SetSelectButton(group_name, select_button);
            tab_widget->AddPage(page);
            page->SetTabWidget(tab_widget);
            QObject::connect(page,
                             SIGNAL(PageShown(CPage*)),
                             _AppFrame,
                             SLOT(SelectPage(CPage*)));
            _AppFrame->AddPage(page_name, page);
         }
      }
      Info(true, "create page  %s done", page_name);
      ProcessEvents();
   }
#endif
}

void cQTUserInterface::PropagateConnections ()
{
   if (_NodeList == NULL) {
      ErrorPrintf("missing node list in PropagateConnections\n");
      return;
   }
   Info(false, "propagate connections");
   ULONG_T t = cSystemUtils::RealtimeOffset();
   Info(true, "propagate connections of app frame");
   CWidgetBase::PropagateConnections(NULL, _AppFrame);
   Info(true, "propagate connections of app frame done");
   Info(true, "propagate connections done %d", cSystemUtils::RealtimeOffset() - t);
}

void cQTUserInterface::PropagateContexts ()
{
   if (_NodeList == NULL) {
      Error("missing node list in PropagateContexts");
      return;
   }
   Info(false, "propagate contexts");
   ULONG_T t = cSystemUtils::RealtimeOffset();
   STRING_LIST_T node_names;
   ULONG_T nodes = _NodeList->NodeNames(node_names);
   if (nodes == 0) {
      return;
   }
   STRING_LIST_T::const_iterator i = node_names.cbegin();
   ProcessEvents();
   while (i != node_names.cend()) {
      cNode * node = _NodeList->Node((*i).c_str());
      if (_StartupForm != NULL) {
         _StartupForm->CreateEventSink(node->EventAdapter());
      }
      _ActContext = node->Context();
      GUIInitialize(SH_PRE_CONTEXT_PROPAGATION, _ActContext);
      CWidgetBase::PropagateContext(_AppFrame, node, _ActContext);
      GUIInitialize(SH_POST_CONTEXT_PROPAGATION, _ActContext);
      i++;
   }
   Info(true, "propagate contexts done %d", cSystemUtils::RealtimeOffset() - t);
   ProcessEvents();
}

void cQTUserInterface::SetupWidgets ()
{
   Info(false, "setup widgets");
   ULONG_T t = cSystemUtils::RealtimeOffset();
   ProcessEvents();
   CWidgetBase::SetupWidgets(_AppFrame);
   Info(true, "setup widgets done %d", cSystemUtils::RealtimeOffset() - t);
   ProcessEvents();
}

void cQTUserInterface::StartSystem ()
{
   GUIInitialize(SH_PRE_UI_START, _ActContext);
   RemoveStartupForm();
   _AppFrame->Start();
}

void cQTUserInterface::CreateStartupForm ()
{
   if (_AppFrame != NULL) {
      _StartupForm = _AppFrame->CreateStartupForm();
      if (_StartupForm != NULL) {
         _AppFrame->SetStartupForm(_StartupForm);
#ifdef QT4
         _StartupForm->setParent(_PageContainer);
         _StartupForm->move(QPoint(0, 0));
#else
         _StartupForm->reparent(_PageContainer, QPoint(0, 0));
#endif
         _StartupForm->SetConsole(_Console);
      }
   }
}

void cQTUserInterface::RemoveStartupForm ()
{
   if (_StartupForm != NULL) {
      if (_AppFrame != NULL) {
         _AppFrame->SetStartupForm(NULL);
      }
      _StartupForm->hide();
      delete _StartupForm;
      _StartupForm = NULL;
   }
}

void cQTUserInterface::ChooseContext ()
{
   if (_ContextChooser != NULL) {
      _ContextChooser->SetProcess(_Process);
      _Context = _ContextChooser->GetContext();
      if (_Context == NULL) {
         Error("no valid context failed to load CCS interface");
      }
   }
}

void cQTUserInterface::GUIWait (ULONG_T msecs)
{
   cSystemUtils::Suspend(msecs);
}

void cQTUserInterface::ProcessEvents ()
{
   qApp->processEvents();
}

BOOL_T cQTUserInterface::CCSLoadInterface (cContext *context)
{
   if (CWidgetBase::Flag(SYNC_USER_FUNCTIONS)) {
      return _CCSInterface->Load();
   } else {
      return ExecuteAsyncInitFunction(_CCSInterface, FC_LOAD_CCS_INTERFACE);
   }
}

BOOL_T cQTUserInterface::CCSStartInterface ()
{
   BOOL_T success = false;
   GUIInitialize(SH_PRE_CCS_SERVICE_STARTUP, _ActContext);
   if (CWidgetBase::Flag(SYNC_USER_FUNCTIONS)) {
      success = _CCSInterface->Start();
   } else {
      success = ExecuteAsyncInitFunction(_CCSInterface, FC_START_CCS_INTERFACE);
   }
   if (success) {
      success = GUIInitialize(SH_POST_CCS_SERVICE_STARTUP, _ActContext);
      if (success) {
         Info(false, "initialize UI data");
         success = GUIInitialize(SH_PRE_INITIALIZE_UI_DATA, _ActContext);
         if (success) {
            SetupWidgets();
            Info(true, "refresh widget data");
            success = CWidgetBase::RefreshWidgetData();
            if (success) {
               success = GUIInitialize(SH_POST_INITIALIZE_UI_DATA, _ActContext);
               if (!success) {
                  Error("gui init function SH_POST_INITIALIZE_UI_DATA failed");
               }
            } else {
               Error("registering of variable references failed");
            }
         } else {
            Error("gui init function SH_PRE_INITIALIZE_DATA failed");
         }
      } else {
         Error("gui init function SH_POST_CCS_SERVICE_STARTUP failed");
      }
   }
   return success;
}

void cQTUserInterface::StartupInfo (const QString & text, BOOL_T console_only)
{
   InfoPrintf("%s\n", CONST_STRING(text));
   if (!console_only  &&
      _StartupForm != NULL) {
      _StartupForm->Info(text, 0, true);
   }
}

void cQTUserInterface::StartupError (const QString & text)
{
   ErrorPrintf("%s\n", CONST_STRING(text));
   qApp->processEvents();
}

void cQTUserInterface::Info(BOOL_T console_only, const char * fmt_str, ... )
{
   va_list args;
   va_start(args, fmt_str);
   _vsnprintf(_Message, sizeof(_Message)-1, fmt_str, args);
   va_end(args);
   StartupInfo(_Message, console_only);
}

void cQTUserInterface::Error(const char * fmt_str, ... )
{
   va_list args;
   va_start(args, fmt_str);
   _vsnprintf(_Message, sizeof(_Message)-1, fmt_str, args);
   va_end(args);
   StartupError(_Message);
}

