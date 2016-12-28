
/// PR 06.04.05 - added virtual property VirtualFocusColor 
/// PR 12.05.05 - extended ExecDialog method with page index (solution supplied by Wendelin Troxler FM)
/// PR 27.06.05 - added select button info management
/// PR 05.07.05 - releasing user info pointers in async functions causes problems
/// PR 07.07.05 - added action dialogs
/// PR 12.08.05 - avoid to set a group id greater than MAX_GROUP_ID
/// HA 14.08.05 - SetLanguage: Before load translation-file check exist file.
/// PR 19.08.05 - now checking for indefinite recursive function calls in Refresh methods
///               to avoid stack overflows when operating undelayed refresh calls from
///               dark functions
/// PR 01.09.05 - checking tab widget pointer for NULL in Refresh method
/// PR 07.10.05 - method SetLanguage now is virtual (SE,FM)
/// PR 19.10.05 - virtual method GetTranslatedText for application specific
///               translated texts added
/// PR 27.01.06 - added foreground/background related data refresh
/// PR 03.02.06 - extended dialogs and wizards with data refresh functionality
/// PR 18.01.07 - notifying LANGUAGE_CHANGE only when _ActLanguage != language
///               in ::SetNewLanguage
/// PR 13.02.07 - added public method SetLastPage(...) as workaround for the problem
///               solved in CTabWidget.cpp. This method is no more used to work around
///               this problem. Nevertheless the method survives the bug fix to
///               extend the CAppFrame-API for future needs.
/// PR 18.10.07 - fixed bugs in dialog and wizard refresh functionality
/// PR 06.11.07 - added virtual method ::PageChanged(..) to signal changes in page selection
/// PR 07.11.07 - added virtual methods ::WizardStateChanged(..) and ::DialogStateChanged(..)
//                to signal changes in dialog and wizard states
/// PR 09.12.08 - added properties for tab bar colors
/// PR 03.03.09 - substituted GetTranslatedText by GetTranslation
/// PR 03.03.09 - added virtual methods AlphaNumericStateChanged(..) and
///               NumericStateChanged(..) to signal state changes in keypads and keyboards
///               supplied by Horst Anselm (FM)

#include "CAppFrame.h"
#include "CTabWidget.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(FormWidget, \
                   CAppFrame, \
                   ICON_SET("designer_form"), \
                   "application frame widget, use File->New... to create")
#endif

#include <qfileinfo.h>
#include "CToolButton.h"
#include "CPage.h"
#include "CActionDialog.h"
#ifndef QT_PLUGIN
#include "System/Objects/cProgress.h"
#include <qobjectlist.h>
#endif

CAppFrame::CAppFrame(QWidget * parent, const char * name, WFlags flags)
   : CWidget(parent, name, flags)
{
   CONSTRUCT_WIDGET

   _RefreshActive = false;
   _Translator = NULL;
   _ActLanguage = "default";
   _ActPage = NULL;
   _ActDialog = NULL;
   _ActWizard = NULL;
   _LastPage = NULL;
   _UserInfo = NULL;
   _CurrentContext = NULL;
   _Started = false;
   _Started_SyncUserFunctions = false;
   _HelpInterface = NULL;
   _RefreshTimer = NULL;
   _BGColorValue = Qt::blue;
   _BGMarkColorValue = Qt::yellow;
   _BGDiffColorValue = Qt::green;
   _LoggingControl = false;
   _Remaining = 0;
   _AbsoluteTimeControl = false;
   _StartupForm = NULL;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _UserInfo = new cUserInfo;
   cSystemUtils::SetThreadData(_UserInfo);
   CWidgetBase::SetCurrentDataSet(_UserInfo->get_DataSet());
   _RefreshTimer = new QTimer(this);
   connect(_RefreshTimer, SIGNAL(timeout()), SLOT(CyclicRefresh()));
WMETHOD_VOID_EPILOG
#endif
   _Node = NULL;
   _VirtualFocusColorValue = Qt::white;
   _TabBarBackgroundColorValue = paletteBackgroundColor();
   _TabBarForegroundColorValue = paletteForegroundColor();
   _AppDefaultFont = QFont("Arial", 11);
   _AppName = "unnamed application";
}

CAppFrame::~CAppFrame( ) 
{
}

void CAppFrame::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CWidget::mousePressEvent(e);
   }
}

void CAppFrame::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      CWidget::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CAppFrame::DelayedLanguageChange()
{
   SetPageHeader();
}

void CAppFrame::LoggedOff(CONTEXT_PTR context, USER_INFO_PTR_T user_info, BOOL_T automatic)
{
}

// CCS related virtual methods

void CAppFrame::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Node = node;
   _Context = context;
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CAppFrame::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CAppFrame::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
   Object(object);
}

void CAppFrame::CCSPostEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   PropagateObject(object);
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SetProgress(ULONG_T indicator, ULONG_T value)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
  cProgress * progress = new cProgress(NULL, indicator, value);
  PropagateObject(progress);
  progress->Release();
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SelectGroup(QString group_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CTabWidget * tab_widget = TabWidget(group_name);
   if (tab_widget != NULL) {
      tab_widget->ShowGroup();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SelectPage(CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (page != _ActPage) {
      _LastPage = _ActPage;
   }
   _ActPage = page;
   PageChanged(_LastPage, _ActPage);
   if (_LastPage != _ActPage)
   {
      if (_LastPage)
         _LastPage->Leave();
     
      if (_ActPage)
         _ActPage->Enter();     
   }

   SetPageHeader();
   Refresh(EVENT_REFRESH);
// PR 09.03.05 help page must be refreshed when selecting a new page
   _ActPage->SetHelpIds();
   if ((_HelpInterface != NULL) && HelpActive()) {
      QString help_id1;
      QString help_id2;
      CWidgetBase::GetActHelpIds(help_id1, help_id2);
      _HelpInterface->set_AdditionalPath("");
      _HelpInterface->ShowHelp(help_id1, help_id2);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::ShowPage(QString page_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CPage * page = Page(page_name);
   if (page != NULL) {
      ShowPage(page);
   }
WMETHOD_VOID_EPILOG
#endif   
}

void CAppFrame::ShowPage(CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (page != NULL) {
      CTabWidget * tab_widget = page->TabWidget();
      if (tab_widget != NULL) {
         tab_widget->ActivatePage(page);
      }
   }
WMETHOD_VOID_EPILOG
#endif   
}

void CAppFrame::TogglePrintPage(const QString & page_name)
{
}

void CAppFrame::PrintPages(ULONG_T flags)
{
}

void CAppFrame::PrintActPage(ULONG_T flags)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CPage * page = _ActPage;
   if(page != NULL) {
      PrintPage(page, flags);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::PrintPage(const QString & page_name, ULONG_T flags)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (page_name == NULL) {
      PrintFrame(flags);
   } else {
      CPage * page = Page(page_name);
      if(page != NULL) {
         PrintPage(page);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::CyclicRefresh()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_LoggingControl) {
      CheckLogging();
   }
   Refresh(FAST_REFRESH);
#ifdef TEST_SEQUENCE_FOR_APPEARING_ARROWS
static int count = 0;
if (count == 10) {
   SetNewLanguage("default");
} else if (count == 20) {
   SetNewLanguage("sv");
   count = 0;
}
count++;
#endif
WMETHOD_VOID_EPILOG
#endif
}

bool CAppFrame::SetNewLanguage(const QString & language)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (SetLanguage(language)) {
      if (_stricmp(CONST_STRING(_ActLanguage), CONST_STRING(language)) != 0) {
         _ActLanguage = language;
         Notify(LANGUAGE_CHANGE);
      }
      return true;
   }
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

QString CAppFrame::GetLanguage()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _ActLanguage;
WMETHOD_RC_EPILOG("")
#else
   return "";
#endif
}

void CAppFrame::AddPage(const QString & page_name, CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Pages[page_name] = page;
   if (_ActPage == NULL) {
      _ActPage = page;
      PageChanged(_LastPage, _ActPage);
      if (_LastPage != _ActPage)
      {
         if (_LastPage)
            _LastPage->Leave();
        
         if (_ActPage)
            _ActPage->Enter();
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

CPage * CAppFrame::Page(const QString & page_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   PAGE_MAP_T::const_iterator i = _Pages.find(page_name);
   if (i != _Pages.end()) {
      return (*i).second;
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

CPage * CAppFrame::ActPage()
{
   return _ActPage;
}

CPage * CAppFrame::LastPage()
{
   return _LastPage;
}

QString CAppFrame::ActPageName()
{
   if (_ActPage != NULL) {
      return _ActPage->Name();
   } else {
      return "";
   }
}

void CAppFrame::GetPages(PAGE_LIST_T & pages, ULONG_T flags)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   PAGE_MAP_T::const_iterator i = _Pages.begin();
   while (i != _Pages.end()) {
      CPage * page = (*i).second;
      pages.push_back(page);
      i++;
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::AddTabWidget(const QString & group_name, CTabWidget * tab_widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   TAB_WIDGET_MAP_T::const_iterator i = _TabWidgets.find(group_name);
   if (i != _TabWidgets.end()) {
   }
   _TabWidgets[group_name] = tab_widget;
WMETHOD_VOID_EPILOG
#endif
}

CTabWidget * CAppFrame::TabWidget(const QString & group_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   TAB_WIDGET_MAP_T::const_iterator i = _TabWidgets.find(group_name);
   if (i != _TabWidgets.end()) {
      return (*i).second;
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

void CAppFrame::Start()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_HelpInterface == NULL) {
      _HelpInterface = new cHelpInterface;
   }

   _RefreshTimer->start(RefreshInterval());
   ShowPage(_ActPage);
   _Started = true;
   _Started_SyncUserFunctions = true;
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::Refresh(int refresh_type, BOOL_T delayed, BOOL_T force_check)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!_Started_SyncUserFunctions && !delayed) {
      return;
   }
   if (_RefreshActive ||
       delayed ||
       _QtGUIThreadId != cSystemUtils::ThreadId()) {
      if (!_Started_SyncUserFunctions && Flag(SYNC_USER_FUNCTIONS)) {
         _Started_SyncUserFunctions = true;
      }
      if (IS_DATA_REFRESH(refresh_type)) {
         Notify(REFRESH_DATA);
         return;
      } else if (IS_BG_DATA_REFRESH(refresh_type)) {
         Notify(REFRESH_BG_DATA);
         return;
      } else if (IS_EVENT_REFRESH(refresh_type)) {
         return;
      }
   } else {
      if (PROPAGATE(refresh_type)) {
         CWidgetBase::InvalidateDataRefreshs(refresh_type);
      }
   }
   _RefreshActive = true;
   try {
      emit(CheckAppearanceSignal(refresh_type, elementFree));
      PAGE_MAP_T::const_iterator i = _Pages.begin();
      while (i != _Pages.end()) {
         CPage * page = (*i).second;
         CTabWidget * tab_widget = page->TabWidget();
         if (tab_widget != NULL) {
            QString current_group = _ActPage->getPageGroup();
            QString page_group = page->getPageGroup();
            if (force_check || (current_group == page_group)) {
               page->CheckAppearance(refresh_type, elementFree);
               ULONG_T appearance_state = page->GetAppearanceState();
               if (appearance_state == elementInvisible) {
                  tab_widget->HidePage(page);
               } else if (appearance_state == elementDisabled) {
                  tab_widget->DisablePage(page);
               } else if (appearance_state == elementFree) {
                  tab_widget->ShowPage(page);
               }
            }
         }
         i++;
      }
      if (_ActPage != NULL) {
         _ActPage->CheckAppearanceSlot(refresh_type, elementFree);
      }
      RefreshDialogs(refresh_type, delayed, elementFree);
   } catch (cError & e) {
      ErrorPrintf("unhandled cError exception %s in CAppFrame::Refresh\n", (CONST_STRING_T)e);
      return;
   } catch (cErrBase & e) {
      ErrorPrintf("unhandled cErrBase exception (%d,%d,%d) in CAppFrame::Refresh\n", e.getClass(), e.getCode(), e.getPrefix());
      return;
   } catch (...) {
      ErrorPrintf("unhandled exception in CAppFrame::Refresh\n");
      return;
   }
   _RefreshActive = false;
WMETHOD_VOID_EPILOG
#endif   
}

void CAppFrame::RefreshDialogs(ULONG_T refresh_type, ULONG_T parent_state, BOOL_T delayed)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
/* PR 18.10.07 this avoids calling of text refresh
   if (!IS_DATA_REFRESH(refresh_type)) {
      return;
   }
*/
   WIZARD_MAP_T::const_iterator i = _Wizards.begin();
   while (i != _Wizards.end()) {
      WIZARD_T * wizard_buf = (*i).second;
      if (IS_DATA_REFRESH(refresh_type)) {
         wizard_buf->data_refresh_pending = true;
      } else if (IS_BG_DATA_REFRESH(refresh_type)) {
         wizard_buf->bgdata_refresh_pending = true;
      } else if (IS_TEXT_REFRESH(refresh_type)) {
         wizard_buf->text_refresh_pending = true;
      }
      i++;
   }
   DIALOG_MAP_T::const_iterator j = _Dialogs.begin();
   while (j != _Dialogs.end()) {
      DIALOG_T * dialog_buf = (*j).second;
      if (IS_DATA_REFRESH(refresh_type)) {
         dialog_buf->data_refresh_pending = true;
      } else if (IS_BG_DATA_REFRESH(refresh_type)) {
         dialog_buf->bgdata_refresh_pending = true;
      } else if (IS_TEXT_REFRESH(refresh_type)) {
         dialog_buf->text_refresh_pending = true;
      }
      j++;
   }
WMETHOD_VOID_EPILOG
#endif   
}

void CAppFrame::RefreshWidget(QWidget * widget, ULONG_T refresh_type)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (IsCustomWidget(widget)) {
      if (IS_DATA_REFRESH(refresh_type)) {
         RefreshWidgetData(widget);
      } else if (IS_TEXT_REFRESH(refresh_type)) {
         CWidgetBase::DelayedLanguageChange(widget);
      } else {
         return;
      }
   }
   const QObjectList * children = widget->children();
   if (children == NULL) {
      return;
   }
   QObjectListIt i = QObjectListIt(*children);
   if (i == 0) {
      return;
   }
   QObject * object = NULL;
   while ((object = i.current())) {
      QWidget * child = (QWidget*)object;
      if (object->isWidgetType()) {
         RefreshWidget(child, refresh_type);
      }
      ++i;
   }
WMETHOD_VOID_EPILOG
#endif   
}

// custom specific methods to configure the frame
// these methods must be overloaded by custom specific
// implementations

PageList * CAppFrame::CreatePageList(QWidget * parent)
{
   return NULL;
}

CFrame * CAppFrame::GetPageContainer()
{
   return NULL;
}

CFixText * CAppFrame::GetPageHeader()
{
   return NULL;
}

void CAppFrame::Object(TRANSIENT_OBJECT_PTR object)
{
}

void CAppFrame::Message(BOOL_T async,
                        const QString & message,
                        const QString & details,
                        const QString & param1,
                        const QString & param2,
                        const QString & param3,
                        const QString & param4)
{
}

void CAppFrame::Message(BOOL_T async,
                        ERROR_REF_T error)
{
}

int CAppFrame::RefreshInterval()
{
   return 500;
}

CStartupForm * CAppFrame::CreateStartupForm()
{
   // PR 11.03.05 must be overloaded in custom frame
   return NULL;
}

void CAppFrame::SetStartupForm(CStartupForm * form)
{
   _StartupForm = form;
}

CStartupForm * CAppFrame::StartupForm()
{
   return _StartupForm;
}

void CAppFrame::GUIInit(ULONG_T step)
{
#ifndef QT_PLUGIN
#endif
}

CActionDialog * CAppFrame::GetActionDialog(const QString & dialog_name, cPublicDialog * dialog)
{
#ifndef QT_PLUGIN
#endif
   return NULL;
}

void CAppFrame::ActionDialogTerminated(const QString & dialog_name, ULONG_T rc, cPublicDialog * dialog, CActionDialog * action_dialog)
{
#ifndef QT_PLUGIN
   delete dialog;
#endif
}

void CAppFrame::ShowHelp()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_HelpInterface != NULL) {
      _HelpInterface->Show();
      QString help_id1;
      QString help_id2;
      CWidgetBase::GetActHelpIds(help_id1, help_id2);
      _HelpInterface->ShowHelp(help_id1, help_id2);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SetHelpAdditionalPath(const QString & additional_path)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_HelpInterface != NULL) {
      _HelpInterface->set_AdditionalPath(CONST_STRING(additional_path));
   }
WMETHOD_VOID_EPILOG
#endif
}

BOOL_T CAppFrame::ExistHelpFile(const QString & help_id1, const QString & help_id2)
{
#ifdef QT_PLUGIN
   return false;
#else
WMETHOD_PROLOG
   if (_HelpInterface == NULL) {
      return false;
   } else {
      return _HelpInterface->ExistHelpFile(help_id1, help_id2);
   }
WMETHOD_RC_EPILOG(false)
#endif
}

void CAppFrame::ShowLastPage()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_LastPage != NULL) {
      ShowPage(_LastPage);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SetLastPage(CPage* page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
	_LastPage = page;
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::HideHelp()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_HelpInterface != NULL) {
      _HelpInterface->Hide();
   }
WMETHOD_VOID_EPILOG
#endif
}

BOOL_T CAppFrame::ShowHelp(const QString & help_id1, const QString & help_id2)
{
#ifdef QT_PLUGIN
   return false;
#else
WMETHOD_PROLOG
   if (_HelpInterface == NULL) {
      return false;
   } else {
      return _HelpInterface->ShowHelp(help_id1, help_id2);
   }
WMETHOD_RC_EPILOG(false)
#endif
}

BOOL_T CAppFrame::HelpActive()
{
#ifdef QT_PLUGIN
   return false;
#else
WMETHOD_PROLOG
   if (_HelpInterface == NULL) {
      return false;
   } else {
      return _HelpInterface->Active();
   }
WMETHOD_RC_EPILOG(false)
#endif
}

void CAppFrame::GetActHelpIds(QString help_id1, QString help_id2)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CWidgetBase::GetActHelpIds(help_id1, help_id2);
WMETHOD_VOID_EPILOG
#endif
}

CONTEXT_PTR CAppFrame::CurrentContext()
{
   return _CurrentContext;
}

void CAppFrame::SetCurrentContext(CONTEXT_PTR context)
{
   _CurrentContext = context;
}

void CAppFrame::Initialize()
{
   SetAppFrame(this);
}

QImage CAppFrame::GetImage(const QString & page_name, ULONG_T flags)
{
   QImage image;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (page_name != NULL) {
      CPage * page = Page(page_name);
      if(page != NULL) {
         page->CheckAppearanceSlot(EVENT_REFRESH, elementFree);
         QPixmap pixmap = QPixmap::grabWidget(page);
         image = pixmap.convertToImage();
      }
   } else {
      CheckAppearanceSlot(EVENT_REFRESH, elementFree);
      QPixmap pixmap = QPixmap::grabWidget(this);
      image = pixmap.convertToImage();
   }
WMETHOD_RC_EPILOG(image)
#endif
   return image;
}

CPage * CAppFrame::GetPage(const QString & page_name)
{
   CPage * page = NULL;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (page_name != NULL) {
      page = Page(page_name);
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return page;
}

void CAppFrame::RegisterDialog(QDialog * dialog)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   SetWidgetActive(dialog, false);
   DIALOG_T * dialog_buf = (DIALOG_T*)cSystemUtils::Alloc(sizeof(*dialog_buf));
   dialog_buf->dialog = dialog;
   dialog_buf->active = false;
   dialog_buf->data_refresh_pending = false;
   dialog_buf->bgdata_refresh_pending = false;
   dialog_buf->text_refresh_pending = false;
   _Dialogs[CWidgetBase::Name((QWidget*)dialog)] = dialog_buf;
   WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::RegisterDialog(QWizard * wizard)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   SetWidgetActive(wizard, false);
   WIZARD_T * wizard_buf = (WIZARD_T*)cSystemUtils::Alloc(sizeof(*wizard_buf));
   wizard_buf->wizard = wizard;
   wizard_buf->active = false;
   wizard_buf->data_refresh_pending = false;
   wizard_buf->bgdata_refresh_pending = false;
   wizard_buf->text_refresh_pending = false;
   _Wizards[CWidgetBase::Name((QWidget*)wizard)] = wizard_buf;
WMETHOD_VOID_EPILOG
#endif
}

int CAppFrame::ExecDialog(const QString & dialog_name, int page_index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QDialog * dialog = Dialog(dialog_name);
   if (dialog == NULL) {
      QWizard * qWizard = Wizard(dialog_name);
      if (qWizard == NULL) {
      } else {
         QWidget * page = qWizard->page(page_index);
         if (page == NULL) {
            return 0; //Rejected
         } else {
            // search first page to show
            while (page_index <= (qWizard->pageCount()-1)) {
               page = qWizard->page(page_index);
               if (qWizard->appropriate(page) == false) {
                  page_index++;
               } else {
                  break;
               }
            }
            qWizard->showPage(page);
         }
         int rc = 0; //Rejected
         if (_ActWizard == NULL) {
            SetWidgetActive(qWizard, true);
            SetActive(qWizard, true);
            rc = qWizard->exec();
            SetActive(qWizard, false);
            SetWidgetActive(qWizard, false);
         }
         return rc;
      }
   } else {
      int rc = 0; //Rejected
      if (_ActDialog == NULL) {
         SetWidgetActive(dialog, true);
         SetActive(dialog, true);
         rc = dialog->exec();
         SetActive(dialog, false);
         SetWidgetActive(dialog, false);
      }
      return rc;
   }
WMETHOD_RC_EPILOG(0)
#endif
   return 0;
}

void CAppFrame::ShowDialog(const QString & dialog_name, int page_index)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QDialog * dialog = Dialog(dialog_name);
   if (dialog == NULL) {
      QWizard * qWizard = Wizard(dialog_name);
      if (qWizard == NULL) {
      } else {
         QWidget * page = qWizard->page(page_index);
         if (page == NULL) {
            return;
         } else {
            // search first page to show
            while (page_index <= (qWizard->pageCount()-1)) {
               page = qWizard->page(page_index);
               if (qWizard->appropriate(page) == false) {
                  page_index++;
               } else {
                  break;
               }
            }
            qWizard->showPage(page);
         }
         if (_ActWizard == NULL) {
            SetWidgetActive(qWizard, true);
            SetActive(qWizard, true);
            qWizard->show();
            SetActive(qWizard, false);
            SetWidgetActive(qWizard, false);
         }
      }
   } else {
      if (_ActDialog == NULL) {
         SetWidgetActive(dialog, true);
         SetActive(dialog, true);
         dialog->show();
         SetActive(dialog, false);
         SetWidgetActive(dialog, false);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

QWizard * CAppFrame::Wizard(const QString & name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   WIZARD_MAP_T::const_iterator i = _Wizards.find(name);
   if (i == _Wizards.end()) {
      return NULL;
   } else {
      WIZARD_T * wizard_buf = (*i).second;
      return wizard_buf->wizard;
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

QDialog * CAppFrame::Dialog(const QString & name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   DIALOG_MAP_T::const_iterator i = _Dialogs.find(name);
   if (i == _Dialogs.end()) {
      return NULL;
   } else {
      DIALOG_T * dialog_buf = (*i).second;
      return dialog_buf->dialog;;
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

QWizard * CAppFrame::ActiveWizard()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_ActWizard == NULL) {
      return NULL;
   } else {
      return _ActWizard->wizard;
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

QDialog * CAppFrame::ActiveDialog()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_ActDialog == NULL) {
      return NULL;
   } else {
      return _ActDialog->dialog;
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

WIZARD_T * CAppFrame::ActWizard()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _ActWizard;
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

DIALOG_T * CAppFrame::ActDialog()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _ActDialog;
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

void CAppFrame::SetActive(QWizard * wizard, BOOL_T state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (state) {
      WIZARD_MAP_T::const_iterator i = _Wizards.find(CWidgetBase::Name((QWidget*)wizard));
      if (i != _Wizards.end()) {
         _ActWizard = (*i).second;
         WizardStateChanged(_ActWizard, true);

         if (_ActWizard && _ActWizard->data_refresh_pending) {
            RefreshWidget(wizard, DATA_REFRESH);
            _ActWizard->data_refresh_pending = false;
         }

         if (_ActWizard && _ActWizard->bgdata_refresh_pending) {
            RefreshWidget(wizard, BG_DATA_REFRESH);
            _ActWizard->bgdata_refresh_pending = false;
         }

         if (_ActWizard && _ActWizard->text_refresh_pending) {
            RefreshWidget(wizard, TEXT_REFRESH);
            _ActWizard->text_refresh_pending = false;
         }
      }
   } else {
      WizardStateChanged(_ActWizard, false);
      _ActWizard = NULL;
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SetActive(QDialog * dialog, BOOL_T state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (state) {
      DIALOG_MAP_T::const_iterator i = _Dialogs.find(CWidgetBase::Name((QWidget*)dialog));
      if (i != _Dialogs.end()) {
         _ActDialog = (*i).second;
         DialogStateChanged(_ActDialog, true);

         if (_ActDialog && _ActDialog->data_refresh_pending) {
            RefreshWidget(dialog, DATA_REFRESH);
            _ActDialog->data_refresh_pending = false;
         }

         if (_ActDialog && _ActDialog->bgdata_refresh_pending) {
            RefreshWidget(dialog, BG_DATA_REFRESH);
            _ActDialog->bgdata_refresh_pending = false;
         }

         if (_ActDialog && _ActDialog->text_refresh_pending) {
            RefreshWidget(dialog, TEXT_REFRESH);
            _ActDialog->text_refresh_pending = false;
         }
      }
   } else {
      DialogStateChanged(_ActDialog, false);
      _ActDialog = NULL;
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SetGroupId(ULONG_T id)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_UserInfo != NULL) {
      if (id > MAX_GROUP_ID) {
         _UserInfo->set_GroupId(MAX_GROUP_ID);
      } else {
         _UserInfo->set_GroupId(id);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SetUserInfo(USER_INFO_PTR_T user_info)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (user_info->get_GroupId() > MAX_GROUP_ID) {
      user_info->set_GroupId(MAX_GROUP_ID);
   }
   if (_UserInfo != user_info) {
      if (_UserInfo != NULL) {
//         _UserInfo->Release();
      }
      _UserInfo = user_info;
      cSystemUtils::SetThreadData(_UserInfo);
      CWidgetBase::SetCurrentDataSet(_UserInfo->get_DataSet());
   }
   Login();
WMETHOD_VOID_EPILOG
#endif
}

USER_INFO_PTR_T CAppFrame::GetUserInfo()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _UserInfo;
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

void CAppFrame::Login(USER_INFO_PTR_T user_info)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   SetUserInfo(user_info);
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::Logoff(BOOL_T automatic)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_UserInfo != NULL) {
      ULONG_T act_group_id = _UserInfo->get_GroupId();
      if (act_group_id != 0) {
         cUserInfo user_info = *_UserInfo;
         _UserInfo->set_GroupId(0);
         _UserInfo->set_DataSet(0);
         _UserInfo->set_UserName("");
         CWidgetBase::SetCurrentDataSet(_UserInfo->get_DataSet());
         _AbsoluteTimeControl = false;
         _LoggingControl = false;
         LoggedOff(_Context, &user_info, automatic);
         Refresh(FAST_REFRESH, false, true); // Page show problem after logoff in Qt3 application
         Refresh(DATA_REFRESH);
         Refresh(EVENT_REFRESH);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::ResyncLogoff()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_UserInfo != NULL && !_AbsoluteTimeControl) {
      ULONG_T logoff_interval = _UserInfo->get_LogoffInterval();
      if (logoff_interval > 0) {
         _LoggingControl = true;
         _Remaining = (logoff_interval * (1000 / RefreshInterval()));
      } else {
         _LoggingControl = false;
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

QString CAppFrame::ActLanguage()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _ActLanguage;
WMETHOD_RC_EPILOG("")
#endif
   return "";
}

BOOL_T CAppFrame::SetLanguage(const QString & language)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Translator == NULL) {
      _Translator = new QTranslator(NULL);
   }
   if (strcmpi(CONST_STRING(language), CONST_STRING(_ActLanguage)) == 0) {
      return true;
   }
   if (strcmpi(CONST_STRING(language), "default") != 0) {
      QString lang_spec = language;
      lang_spec += ".qm";
      QFileInfo trans_file(lang_spec);
      if (trans_file.exists()) {
         if (_Translator->load(trans_file.absFilePath())) {
            qApp->installTranslator(_Translator);
            return true;
         }
         else {
            return false;
         }
      } else {
         ErrorPrintf("translation file '%s' not found\n", CONST_STRING(trans_file.absFilePath()));
         return false;
      }
   } else {
      _Translator->clear();
      BOOL_T empty = _Translator->isEmpty();
      return true;
   }
#ifdef falls_der_font_noch_umgeschaltet_wird
   QFont font;
   if (_ActLanguage == "VR" || _ActLanguage == "vr") {
      font = QFont("Bitstream Cyberbit", 14);
      font.setStyleStrategy (QFont::NoAntialias);
   } else {
      font = QFont("Arial", 10);
   }
   _Application->setFont(font, TRUE);
#endif
WMETHOD_RC_EPILOG(false)
#endif
   return false;
}

void CAppFrame::SetSelectButton(const QString & group_name, CGroupSelectButton * button)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _SelectButtons[group_name] = button;
WMETHOD_VOID_EPILOG
#endif
}

CGroupSelectButton * CAppFrame::GetSelectButton(const QString & group_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   SELECT_BUTTON_MAP_T::const_iterator i = _SelectButtons.find(group_name);
   if (i != _SelectButtons.end()) {
      return (*i).second;
   }
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

void CAppFrame::GetSelectButtons(SELECT_BUTTON_MAP_T & buttons)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   buttons = _SelectButtons;
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::PrintPage(CPage * page, ULONG_T flags)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QPainter painter;
   QPrinter printer(QPrinter::HighResolution);
   QString timestr;
   int leftMarginMM = 20;   // Linker Rand in mm
   int topMarginMM  = 10;   // Oberer Rand in mm
   int leftMargin;          // Linker Rand in Druckerpixeln
   int topMargin;           // Oberer Rand in Druckerpixeln
   int prnwidth;            // Breite der Druckerseite in Druckerpixeln
   double scaleFactor;      // Skalierungsfaktor Seite -> Drucker

   if(page == NULL) return;
   printer.setNumCopies(1);
   printer.setFullPage(true);
   printer.newPage();
   if(!painter.begin(&printer)) return;
   // Angaben ueber den Drucker holen und einige druckerspezifische Werte berechnen
   QPaintDeviceMetrics prnMetrics(&printer);
   QPaintDeviceMetrics screenMetrics(page);
   scaleFactor =(double)prnMetrics.logicalDpiX() / screenMetrics.logicalDpiX();
   prnwidth = prnMetrics.width();
   leftMargin = leftMarginMM *((double)prnwidth / prnMetrics.widthMM());
   topMargin = topMarginMM *((double)prnMetrics.height() / prnMetrics.heightMM());
   // Font setzen
   QFont font = getApplication()->font();
   font.setBold(TRUE);
   font.setPointSize(font.pointSize() + 2);
   painter.setFont(font);
   painter.setBackgroundColor(Qt::white);
   painter.setPen(Qt::black);
   QFontMetrics fm(font);
   // Ueberschrift ausgeben. Bei drawText wird als Y-Position die baseline verwendet,
   // die Linie auf der die normalen Zeichen 'stehen'. ascent ist die Höhe in Pixel
   // eines Fonts von ganz oben bis zur Baseline.
   QString s = page->getLongPageHeadline();
   painter.drawText(leftMargin, topMargin + fm.ascent(), s);
   // Datum und Uhrzeit rechtsbündig ausgeben. Leider gibt fm.width() nicht die Länge
   // des Strings auf dem Drucker zurück, so daß man skalieren muß, wobei die exakte
   // Skalierung des Fonts auf dem Drucker unbekannt ist. Die Stringlängenberechnung
   // auf dem Drucker ist also eine(aufgerundete) Daumenpeilung.
   timestr = QDateTime::currentDateTime().toString("d.MM.yyyy h:mm:ss");
   painter.drawText(prnwidth - fm.width(timestr) *(scaleFactor * 1.2), 
                     topMargin + fm.ascent(), timestr);
   // Pixmap auf den Drucker ausgeben. Vorher muß das Pixmap skaliert werden. Dazu
   // wird es in ein QImage umgewandelt.
   QImage image = GetImage(page->Name(), flags);
   image = image.scaleWidth(prnwidth - leftMargin);
   painter.drawImage(leftMargin, topMargin + fm.height() + 2, image);
   // Druckerjob zum Drucker schicken
   painter.end();
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::PrintFrame(ULONG_T flags)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QPainter painter;
   QPrinter printer(QPrinter::HighResolution);
   QString timestr;
   int leftMarginMM = 20;   // Linker Rand in mm
   int topMarginMM  = 10;   // Oberer Rand in mm
   int rightMarginMM = 10;  // Rechter Rand in mm  HA 110105
   int leftMargin;          // Linker Rand in Druckerpixeln
   int rightMargin;         // Rechter Rand in Druckerpixeln
   int topMargin;           // Oberer Rand in Druckerpixeln
   int prnwidth;            // Breite der Druckerseite in Druckerpixeln
   int beginn_prnwidth;     // scaled width of beginn print page in printer pixels  HA 110105
   double scaleFactor;      // Skalierungsfaktor Seite -> Drucker

   printer.setNumCopies(1);
   printer.setFullPage(true);
   printer.newPage();
   if(!painter.begin(&printer)) return;

   // Angaben ueber den Drucker holen und einige druckerspezifische Werte berechnen
   QPaintDeviceMetrics prnMetrics(&printer);
   QPaintDeviceMetrics screenMetrics(this);
   scaleFactor =(double)prnMetrics.logicalDpiX() / screenMetrics.logicalDpiX();
   prnwidth = prnMetrics.width();
   leftMargin = leftMarginMM *((double)prnwidth / prnMetrics.widthMM());
   rightMargin = rightMarginMM *((double)prnwidth / prnMetrics.widthMM()); // HA 110105
   topMargin = topMarginMM *((double)prnMetrics.height() / prnMetrics.heightMM());
   beginn_prnwidth = topMargin; // HA 110105

   if (!(flags & PRN_FLAG_NO_HEADER)) { // HA 110105
      // Font setzen
      QFont font = getApplication()->font();
      font.setBold(TRUE);
      font.setPointSize(font.pointSize() + 2);
      painter.setFont(font);
      painter.setBackgroundColor(Qt::white);
      painter.setPen(Qt::black);
      QFontMetrics fm(font);
      // Ueberschrift ausgeben. Bei drawText wird als Y-Position die baseline verwendet,
      // die Linie auf der die normalen Zeichen 'stehen'. ascent ist die Höhe in Pixel
      // eines Fonts von ganz oben bis zur Baseline.
      QString s = "screen shot";
      painter.drawText(leftMargin, topMargin + fm.ascent(), s);
      // Datum und Uhrzeit rechtsbündig ausgeben. Leider gibt fm.width() nicht die Länge
      // des Strings auf dem Drucker zurück, so daß man skalieren muß, wobei die exakte
      // Skalierung des Fonts auf dem Drucker unbekannt ist. Die Stringlängenberechnung
      // auf dem Drucker ist also eine(aufgerundete) Daumenpeilung.
      timestr = QDateTime::currentDateTime().toString("d.MM.yyyy h:mm:ss");
      painter.drawText(prnwidth - fm.width(timestr) *(scaleFactor * 1.2), 
                       topMargin + fm.ascent(), timestr);
      beginn_prnwidth = topMargin + fm.height() + 2;
   }

   // Pixmap auf den Drucker ausgeben. Vorher muß das Pixmap skaliert werden. Dazu
   // wird es in ein QImage umgewandelt.
   QImage image = GetImage(NULL, flags);
   image = image.scaleWidth(prnwidth - (leftMargin + rightMargin)); // HA 110105
   painter.drawImage(leftMargin, beginn_prnwidth, image); // HA 110105
   // Druckerjob zum Drucker schicken
   painter.end();
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::SetPageHeader()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CPage * page = _ActPage;
   if (page != NULL) {
      CFixText * header_widget = GetPageHeader();
      if (header_widget != NULL) {
         QString header_text = page->getLongPageHeadline();
         if (header_text != NULL) {
            header_widget->setText(header_text);
         } else {
            header_widget->setText("");
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::CheckLogging()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_AbsoluteTimeControl) {
      cTimeObject now;
      ULONG_T diff = (ULONG_T)_LogoffTime - (ULONG_T)now;
      if (diff < 0) {
         Logoff(true);
      }
   } else {
      if (_Remaining <= 0) {
         Logoff(true);
      } else {
         _Remaining--;
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::Login()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_UserInfo != NULL) {
      _LoginTime.Now();
      ULONG_T now = _LoginTime;
      ULONG_T logoff_interval = _UserInfo->get_LogoffInterval();
      if (logoff_interval > now) {
         _LoggingControl = true;
         _AbsoluteTimeControl = true;
         _Remaining = 0;
         _LogoffTime = logoff_interval;
      } else if (logoff_interval > 0) {
         _LoggingControl = true;
         _AbsoluteTimeControl = false;
         _Remaining = (logoff_interval * (1000 / RefreshInterval()));
      } else {
         _LoggingControl = false;
         _AbsoluteTimeControl = false;
      }
      CWidgetBase::SetCurrentDataSet(_UserInfo->get_DataSet());
   }
WMETHOD_VOID_EPILOG
#endif
}

void CAppFrame::MessageBox(const QString & caption, const QString & text, QMessageBox::Icon icon,
                           int button0, int button1, int button2,
                           QFont font)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   PostMessageBox(caption, text, icon, button0, button1, button2, font);
WMETHOD_VOID_EPILOG
#endif
}

BOOL_T CAppFrame::getWidgetInputUTF8Encoded() const
{
    return CWidgetBase::Flag(UTF8_ENCODED_INPUT);
}

