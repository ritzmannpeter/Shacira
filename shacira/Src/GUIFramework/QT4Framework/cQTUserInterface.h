//## begin module%40054B200109.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40054B200109.cm

//## begin module%40054B200109.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40054B200109.cp

#ifndef cQTUserInterface_h
#define cQTUserInterface_h 1

#include <qwidget.h>
#include <qapplication.h>
#include <qtranslator.h>
#include <qlayout.h>
#include "CWidgetStack.h"
#include "CFrame.h"
#include "CTabWidget.h"
#include "CPage.h"
#include "cUserInterface.h"

class CAppFrame;

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cCCSInterface;
class __DLL_EXPORT__ cNodeList;
class __DLL_EXPORT__ cNode;
class __DLL_EXPORT__ cContextExplorer;

class __DLL_EXPORT__ cQTUserInterface : public cUserInterface
{
public:
   cQTUserInterface();
   cQTUserInterface(const cQTUserInterface &right);
   cQTUserInterface(QApplication *app, BOOL_T remote, const QString & language, cConsole *console = NULL, const QString & title = QString(), QPixmap *icon = NULL);
   virtual ~cQTUserInterface();
   virtual void Initialize(cCCSInterface *ccs_interface, cConsole *console);
   virtual int Start(BOOL_T success);
   virtual BOOL_T SetNewLanguage(const QString & language);
   virtual QString GetLanguage();
protected:
   cContext *_Context;
private:
   virtual BOOL_T GUIInitialize(ULONG_T step, cContext *context);
   void StartGUI();
   void CreateGroupDefs();
   void CreateFreeGroupDefs(QWidget *widget);
   void CreatePages();
   void CreatePages(cNode *node);
   void PropagateConnections();
   void PropagateContexts();
   void SetupWidgets();
   void StartSystem();
   void CreateStartupForm();
   void RemoveStartupForm();
   void ChooseContext();
   void GUIWait(ULONG_T msecs);
   void ProcessEvents();
   BOOL_T CCSLoadInterface(cContext *context = NULL);
   BOOL_T CCSStartInterface();
   virtual void StartupInfo(const QString & text, BOOL_T console_only = false);
   virtual void StartupError(const QString & text);
   virtual void Info(BOOL_T console_only, const char * fmt_str, ... );
   virtual void Error(const char * fmt_str, ... );
   QApplication *_Application;
   QWidget *_MainWidget;
   QVBoxLayout *_MainLayout;
   CStartupForm  *_StartupForm;
   CAppFrame *_AppFrame;
   CFrame *_PageContainer;
   CWidgetStack *_WidgetStack;
   PageList *_PageList;
friend class cPostInterface;
friend class cAsyncInitFunction;
};

//## begin cQTUserInterface%40054B200109.postscript preserve=yes
//## end cQTUserInterface%40054B200109.postscript

// Class cQTUserInterface 

//## begin module%40054B200109.epilog preserve=yes
//## end module%40054B200109.epilog


#endif
