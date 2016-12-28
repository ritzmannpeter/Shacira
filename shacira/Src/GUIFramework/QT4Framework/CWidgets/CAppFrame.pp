
#ifndef _cappframe_h_
#define _cappframe_h_

#include "CWidgetBase.h"
#include "CWidget.h"
#include "CFrame.h"
#include "CTabWidget.h"
#include "CWidgetStack.h"
#include "CToolButton.h"
#include "CFixText.h"
#ifndef QT4
#include "CPublicDialog.h"
#endif
#include <qapplication.h>
#include <qpainter.h>
#include <qpaintdevice.h>
#include <qprinter.h>
#include <qimage.h>
#include <qdatetime.h>
#include <qlayout.h>
#include <qtranslator.h>
#include <qtimer.h>
#include <qdialog.h>
#include <qwizard.h>

class CActionDialog;
class CStartupForm;
class PageShiftRegister;

#ifdef QT_PLUGIN
typedef void * HELP_INTERFACE_PTR;
typedef void * PAGE_MAP_T;
typedef void * SELECT_BUTTON_MAP_T;
typedef void * PAGE_LIST_T;
typedef void * TAB_WIDGET_MAP_T;
typedef void * DIALOG_MAP_T;
typedef void * WIZARD_MAP_T;
typedef void * DIALOG_T;
typedef void * WIZARD_T;
#else
#include "cHelpInterface.h"
typedef cHelpInterface * HELP_INTERFACE_PTR;
typedef std::map<QString, CPage*> PAGE_MAP_T;
typedef std::list<CPage*> PAGE_LIST_T;
typedef std::map<QString, CGroupSelectButton*> SELECT_BUTTON_MAP_T;
typedef std::map<QString, CTabWidget*> TAB_WIDGET_MAP_T;
typedef struct _dialog {
   QDialog * dialog;
   BOOL_T active;
   BOOL_T data_refresh_pending;
   BOOL_T bgdata_refresh_pending;
   BOOL_T text_refresh_pending;
} DIALOG_T;
typedef std::map<QString, DIALOG_T*> DIALOG_MAP_T;
typedef struct _wizard {
   QWizard * wizard;
   BOOL_T active;
   BOOL_T data_refresh_pending;
   BOOL_T bgdata_refresh_pending;
   BOOL_T text_refresh_pending;
} WIZARD_T;
typedef std::map<QString, WIZARD_T*> WIZARD_MAP_T;

#include "System/cTimeObject.h"
#endif

#define MAX_GROUP_ID    7


// print operations including frame
#define PRINT_FRAME		(CONST_STRING_T)NULL

// flags for printing and images
#define PRN_FLAG_NO_HEADER		0x00000001

class CPage;
#ifdef QT4
typedef QList<CPage*> PageList;
#else
typedef QPtrList<CPage> PageList;
#endif

#define USE_PAGE_SHIFT_REGISTER

/**!
  * @brief This is the central widget to organize separate information pages of a shacira application.
  * It supplies functionality to navigate through the information pages.
  * <p>
  */
class _CWIDGET_EXPORT_ CAppFrame : public CWidget
{
// start 2i generic widget definition

   Q_OBJECT

   PROPERTY_2i(QColor,BGColor)
   PROPERTY_2i(QColor,BGMarkColor)
   PROPERTY_2i(QColor,BGDiffColor)
   PROPERTY_2i(QColor,VirtualFocusColor)
   PROPERTY_2i(QColor,TabBarBackgroundColor)
   PROPERTY_2i(QColor,TabBarForegroundColor)

   Q_PROPERTY(QSize PageAreaSize READ getPageAreaSize WRITE setPageAreaSize)

public:
   // further widget specific getter and setter methods
   METHODS_2i   
   friend class CWidgetBase;
   virtual void PropertyChanged() {}
   // end of further widget specific getter and setter methods

   void setPageAreaSize(const QSize &value);
   QSize getPageAreaSize() const;

   static qreal xDisplayScale();
   static qreal yDisplayScale();
   static void setXDisplayScale(qreal displayScale);
   static void setYDisplayScale(qreal displayScale);

   static int getPageContainerWidth();
   static int getPageContainerHeight();
   static void setPageContainerWidth(int pageContainerWidth);
   static void setPageContainerHeight(int pageContainerWidth);
   // end of further widget specific getter and setter methods

protected:
   // overloaded qt widget methods
   virtual void mousePressEvent(QMouseEvent * e);
   virtual void mouseReleaseEvent(QMouseEvent * e);
   virtual void paintEvent(QPaintEvent * e)
   {
      CWidget::paintEvent(e);
   };
   virtual void focusInEvent(QFocusEvent * e)
   {
      CWidget::focusInEvent(e);
   };
   virtual void focusOutEvent(QFocusEvent * e)
   {
      CWidget::focusOutEvent(e);
   };
   void keyReleaseEvent(QKeyEvent * e)
   {
      CWidget::keyReleaseEvent(e);
   };

public: 
   // GUI related virtual methods
   virtual void View() {};
   virtual void Notification(ULONG_T event_code) {};
   virtual void GUIEvent(ULONG_T signal, QWidget * sender) {};
   virtual void DelayedLanguageChange();
   virtual void LoggedOff(CONTEXT_PTR context, USER_INFO_PTR user_info, BOOL_T automatic);

   // CCS related virtual methods
   virtual void CCSSetContext(NODE_PTR node, CONTEXT_PTR context);
   virtual void CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size);
   virtual void CCSEvent(TRANSIENT_OBJECT_PTR object);
   
   // CCS post object method
   void CCSPostEvent(TRANSIENT_OBJECT_PTR object);
   void SetProgress(ULONG_T indicator, ULONG_T value);

protected:
   // view-model properties
   ATTRIBUTES_2i

// end 2i generic widget definition

public slots:
   void SelectGroup(QString group_name);
   void SelectPage(CPage * page);
   void CyclicRefresh();

public:
   CAppFrame(QWidget * parent = 0, const char * name = 0, WIDGET_FLAGS_TYPE f = 0);
   ~CAppFrame();

public:
   void Initialize();
   virtual void Start();
   void Refresh(int refresh_type, BOOL_T delayed = false, BOOL_T force_check = false);
   void RefreshDialogs(ULONG_T refresh_type, ULONG_T parent_state, BOOL_T delayed);
   void RefreshWidget(QWidget * widget, ULONG_T refresh_type);
   QApplication *getApplication() {return qApp;};

public:
// new and integral
   CTabWidget * TabWidget(const QString & group_name);
   void AddTabWidget(const QString & group_name, CTabWidget * tab_widget);
   CPage * Page(const QString & page_name);
   void AddPage(const QString & page_name, CPage * page);
   CPage * ActPage();
   CPage * LastPage();
   QString ActPageName();
   void GetPages(PAGE_LIST_T & pages, ULONG_T flags);
   bool SetNewLanguage(const QString & language);
   QString GetLanguage();
   void ShowPage(QString page_name);
   void ShowPage(CPage * page);
   void TogglePrintPage(const QString & page_name);
   void PrintPages(ULONG_T flags = 0);
   void PrintPage(const QString & page_name = NULL, ULONG_T flags = 0);
   void PrintActPage(ULONG_T flags = 0);
   QImage GetImage(const QString & page_name = NULL, ULONG_T flags = 0);
   CPage * GetPage(const QString & page_name);

   // Dialog Handling
   void RegisterDialog(QDialog * dialog);
   void RegisterDialog(QWizard * dialog);
   int ExecDialog(const QString & dialog_name, int page_index = 0);
   void ShowDialog(const QString & dialog_name, int page_index = 0);
   QWizard * Wizard(const QString & name);
   QDialog * Dialog(const QString & name);
   QWizard * ActiveWizard();
   QDialog * ActiveDialog();

   // user management
   void SetGroupId(ULONG_T id);
   void SetUserInfo(USER_INFO_PTR user_info);
   USER_INFO_PTR GetUserInfo();
   virtual void Login(USER_INFO_PTR user_info);
   void Logoff(BOOL_T automatic = false);
   void ResyncLogoff();

   QString ActLanguage();

   // group references
   void SetSelectButton(const QString & group_name, CGroupSelectButton * button);
   CGroupSelectButton * GetSelectButton(const QString & group_name);
   void GetSelectButtons(SELECT_BUTTON_MAP_T & buttons);

protected:
   QString _ActLanguage;
   HELP_INTERFACE_PTR _HelpInterface;
   virtual BOOL_T SetLanguage(const QString & language);

public:
   /// virtual methods for custom specific adaption
   virtual PageList * CreatePageList(QWidget * parent);
   virtual CFrame * GetPageContainer();
   virtual CFixText * GetPageHeader();
   virtual void SetAppTitle(QString title) {};
   virtual void Object(TRANSIENT_OBJECT_PTR object);
   virtual void Message(BOOL_T async,
                        const QString & message,
                        const QString & details = QString(),
                        const QString & param1 = QString(),
                        const QString & param2 = QString(),
                        const QString & param3 = QString(),
                        const QString & param4 = QString());
   virtual void Message(BOOL_T async,
                        ERROR_REF_T error);
   virtual int RefreshInterval();
   virtual CStartupForm * CreateStartupForm();
   void SetStartupForm(CStartupForm * form);
   CStartupForm * StartupForm();
   virtual void GUIInit(ULONG_T step);
   virtual CActionDialog * GetActionDialog(const QString & dialog_name);
   virtual void ActionDialogTerminated(const QString & dialog_name, ULONG_T rc, CActionDialog * action_dialog);
   virtual bool GetTranslation(QString & translated_text, const QString & string_id, ULONG_T int_id, const QString & text,
                               const QString & param1, const QString & param2, const QString & param3, const QString & param4) {return false;};
   virtual bool VariableText(QString & variable_text, const QString & language, VARIABLE_PTR variable, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4) {return false;};
   virtual BOOL_T GetStarted() { return _Started; };
   virtual void PageChanged(CPage * last_page, CPage * new_page) {};
   virtual void WizardStateChanged(WIZARD_T * wizard, bool active) {};
   virtual void DialogStateChanged(DIALOG_T * dialog, bool active) {};
   virtual void AlphaNumericStateChanged(const QString & var_name, bool active) {};
   virtual void NumericStateChanged(const QString & var_name, bool active) {};
   virtual QString StyleSheet(QWidget * widget);
   virtual BOOL_T getWidgetInputUTF8Encoded() const;

   // page stack
   void ShowLastPage();
   void SetLastPage(CPage* page);

   /// help interface
   void ShowHelp();
   void HideHelp();
   BOOL_T ShowHelp(const QString & help_id1, const QString & help_id2);
   BOOL_T HelpActive();
   void GetActHelpIds(QString help_id1, QString help_id2);
   void SetHelpAdditionalPath(const QString & additional_path);
   BOOL_T ExistHelpFile(const QString & help_id1, const QString & help_id2);

   // context management
   void SetCurrentContext(CONTEXT_PTR context);
   CONTEXT_PTR CurrentContext();
   void MessageBox(const QString & caption, const QString & text, QMessageBox::Icon icon,
                   int button0, int button1, int button2,
                   QFont font);

private:
   void PrintPage(CPage * page, ULONG_T flags = 0);
   void PrintFrame(ULONG_T flags = 0);
   void SetPageHeader();
   void CheckLogging();
   void Login();
   WIZARD_T * ActWizard();
   DIALOG_T * ActDialog();
   void SetActive(QWizard * wizard, BOOL_T state);
   void SetActive(QDialog * dialog, BOOL_T state);

private:
   BOOL_T _RefreshActive;
   QTimer * _RefreshTimer;
   BOOL_T _Started;
   BOOL_T _Started_SyncUserFunctions;
   CONTEXT_PTR _CurrentContext;
   CPage * _ActPage;
#ifndef USE_PAGE_SHIFT_REGISTER
   CPage * _LastPage;
#endif
   PAGE_MAP_T _Pages;
   SELECT_BUTTON_MAP_T _SelectButtons;
   TAB_WIDGET_MAP_T _TabWidgets;
   DIALOG_MAP_T _Dialogs;
   WIZARD_MAP_T _Wizards;
   QTranslator * _Translator;
   USER_INFO_PTR _UserInfo;
   BOOL_T _LoggingControl;
   LONG_T _Remaining;
   CStartupForm * _StartupForm;
   WIZARD_T * _ActWizard;
   DIALOG_T * _ActDialog;
   QSize _PageAreaSize;
protected:
   QString _AppName;
   QFont _AppDefaultFont;
   PageShiftRegister * _PageShiftRegister;

#ifndef QT_PLUGIN
   cTimeObject _LoginTime;
   cTimeObject _LogoffTime;
#endif
   BOOL_T _AbsoluteTimeControl;
public:
   NODE_PTR _Node;
   static BOOL_T loadUiParameters();
   static qreal _xDisplayScale;
   static qreal _yDisplayScale;

   static int _pageContainerWidth;
   static int _pageContainerHeight;
};

#endif


