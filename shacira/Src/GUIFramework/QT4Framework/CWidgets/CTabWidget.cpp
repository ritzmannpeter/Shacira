
/// PR 06.04.05 hope i worked around the bug of unnecessarily appearing
///             scroll arrows
/// PR 27.07.05 added a general delayed language change event when starting up
///             by setting member variable _LanguageChanged to true
///             additionaly checking language change situations in ActivatePage
/// PR 13.02.07 calling showPage before raiseWidget in ActivatePage otherwise
///             a show event is sent to the currently active page of the
///             tab widget. This is superflous and can confuse the page history.
///             (the currently active page of this tab widget then will be
///              the last shown page)
/// PR 22.11.07 - added workaround for page title problems with pages that are shown
///               after they have been hidden and specific languages like russian
///               page titles are not shown correctly when appearing again
///               method ShowPage(...)
/// PR 09.12.08 - added setting of tab bar color defined in CAppFrame

#include "CTabWidget.h"
#include <qtabbar.h>

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(FormWidget, \
                   CTabWidget, \
                   ICON_SET("tabwidget"), \
                   "tabbed widget")
#endif

#include "CScrollView.h"
#include "CPage.h"
#include "CWidgetStack.h"

#ifndef QT_PLUGIN

#define MAX_PAGES    50

class cTabs
{
public:
   cTabs(CTabWidget * tab_widget)
   {
      _TabWidget = tab_widget;
      for (int i=0; i<MAX_PAGES; i++) {
         _Pages[i] = NULL;
         _Shown[i] = true;
      }
   };
   virtual ~cTabs()
   {
   };
   CPage * Page(int pos)
   {
      if (pos < MAX_PAGES) {
         return _Pages[pos];
      } else {
         return NULL;
      }
   };
   int SetPage(CPage * page)
   {
      int pos = page->getPositionInGroup();
      for (int i=0; i<MAX_PAGES; i++) {
         CPage * _page = _Pages[i];
         if (_page == page) {
            return i;
         } else if (_page == NULL && i >= pos) {
            _Pages[i] = page;
            return i;
         }
      }
      return -1;
   };
   int RelPos(CPage * page)
   {
      int rel_pos = 0;
      for (int i=0; i<MAX_PAGES; i++) {
         if (_Pages[i] != NULL && _Shown[i]) {
            if (_Pages[i] == page) {
               return rel_pos;
            }
            rel_pos++;
         }
      }
      return rel_pos;
   };
   void SetShown(CPage * page)
   {
      int abs_pos = page->GetAbsPos();
      if (abs_pos >= 0 && abs_pos < MAX_PAGES) {
         _Shown[abs_pos] = true;
      }
   };
   BOOL_T IsShown(CPage * page)
   {
      int abs_pos = page->GetAbsPos();
      if (abs_pos >= 0 && abs_pos < MAX_PAGES) {
         return _Shown[abs_pos];
      } else {
         return false;
      }
   };
   void SetHidden(CPage * page)
   {
      int abs_pos = page->GetAbsPos();
      if (abs_pos >= 0 && abs_pos < MAX_PAGES) {
         _Shown[abs_pos] = false;
      }
   };
private:
   CTabWidget * _TabWidget;
   CPage * _Pages[MAX_PAGES];
   BOOL_T _Shown[MAX_PAGES];
};

#endif

CTabWidget::CTabWidget(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QTabWidget(parent),
#else
   : QTabWidget(parent, name, f),
#endif
     CWidgetBase(this)
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
   _SelectButton = NULL;
   _Tabs = NULL;
   _LanguageChanged = true;
   _ScrollingEnabled = true;
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _WidgetStack = parent->inherits("CWidgetStack") ? (CWidgetStack*)parent : NULL;

   if (_AppFrame != NULL) {
      QTabBar * bar = tabBar();
#ifdef QT4
      setPaletteBackgroundColor(bar, _AppFrame->getTabBarBackgroundColor());
      setPaletteForegroundColor(bar, _AppFrame->getTabBarForegroundColor());
#else
      bar->setPaletteBackgroundColor(_AppFrame->getTabBarBackgroundColor());
      bar->setPaletteForegroundColor(_AppFrame->getTabBarForegroundColor());
#endif
   }

   if (_WidgetStack) {
      _Tabs = new cTabs(this);
   }
   else {
      connect(this, SIGNAL(currentChanged(int)), this, SLOT(currentChangedSlot(int)));
   }
WMETHOD_VOID_EPILOG
#else
   _WidgetStack = NULL;
#endif
}

CTabWidget::~CTabWidget() 
{
}

void CTabWidget::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QTabWidget::mousePressEvent(e);
   }
}

void CTabWidget::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QTabWidget::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CTabWidget::View()
{
}

void CTabWidget::DelayedLanguageChange()
{
   /// PR 06.04.05 avoid to set properties of widgets,
   ///             that are not raised in the stack.
   ///             doing this causes the appearance of
   ///             tab scroll arrows even if there is no need
   if (_WidgetStack == NULL) return;

   QWidget * visible_widget = _WidgetStack->visibleWidget();
   if (this == visible_widget) {
      ULONG_T pages = count();
      for (ULONG_T i=0; i<pages; i++) {
#ifdef QT4
         QWidget * widget = this->widget(i);
#else
         QWidget * widget = page(i);
#endif
         CPage * p = Page(widget);
         if (p != NULL) {
            QString head_line = p->getPageHeadline();
//            setTabLabel(p, head_line);
/// PR 29.09.07 widget must be supplied, otherwise the tablabel will not be changed (translation)
///
#ifdef QT4
            setTabText(indexOf(widget), head_line);
#else
            setTabLabel(widget, head_line);
#endif
         }
      }
      _LanguageChanged = false;
   } else {
      _LanguageChanged = true;
   }
}

// CCS related virtual methods

void CTabWidget::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
#endif
}

void CTabWidget::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CTabWidget::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CTabWidget::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CTabWidget::SetSelectButton(CGroupSelectButton * select_button)
{
   _SelectButton = select_button;
}

CGroupSelectButton * CTabWidget::GetSelectButton()
{
   return _SelectButton;
}

void CTabWidget::ShowGroup()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_WidgetStack == NULL) return;

   _WidgetStack->raiseWidget(this);
   if (_LanguageChanged) {
      DelayedLanguageChange();
   }
   PrepareTabs();
WMETHOD_VOID_EPILOG
#endif
}

int CTabWidget::RelPos(CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Tabs != NULL) {
      return _Tabs->RelPos(page);
   }
WMETHOD_RC_EPILOG(-1)
#endif
   return -1;
}

void CTabWidget::AddPage(CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Tabs == NULL) 
       return;

   QString title = page->getPageHeadline();
   int position_in_group = page->getPositionInGroup();
   int abs_pos = _Tabs->SetPage(page);
   if (abs_pos >= 0) {
      page->SetAbsPos(abs_pos);
      int rel_pos = _Tabs->RelPos(page);
      if (rel_pos >= 0) {
         QWidget * widget = TabContents(this, page);
#ifdef QT4
         insertTab(rel_pos, widget, title);
#else
         insertTab(widget, title, rel_pos);
#endif
         Reset();
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CTabWidget::ShowPage(CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Tabs == NULL) 
       return;

   if (!_Tabs->IsShown(page)) {
      int abs_pos = page->GetAbsPos();
      if (abs_pos >= 0) {
         _Tabs->SetShown(page);
         QString title = page->getPageHeadline();
         int rel_pos = _Tabs->RelPos(page);
         if (rel_pos >= 0) {
            QWidget * widget = TabContents(this, page);
#ifdef QT4
            insertTab(rel_pos, widget, title);
#else
            insertTab(widget, title, rel_pos);
#endif
            page->setEnabled(true);
            // PR 22.11.07 - workaround for page title problems
            if (title[0] == '?') {
               DelayedLanguageChange();
            }
            return;
         }
      }
   } else {
      if (!page->isEnabled()) {
         page->setEnabled(true);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CTabWidget::DisablePage(CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Tabs == NULL) 
       return;

   if (!_Tabs->IsShown(page)) {
      int abs_pos = page->GetAbsPos();
      if (abs_pos >= 0) {
         _Tabs->SetShown(page);
         QString title = page->getPageHeadline();
         int rel_pos = _Tabs->RelPos(page);
         if (rel_pos >= 0) {
            QWidget * widget = TabContents(this, page);
#ifdef QT4
            insertTab(rel_pos, widget, title);
#else
            insertTab(widget, title, rel_pos);
#endif
            page->setEnabled(false);
            return;
         }
      }
   } else {
      if (page->isEnabled()) {
         page->setEnabled(false);
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CTabWidget::HidePage(CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Tabs == NULL) 
       return;

   if (_Tabs->IsShown(page)) {
      int abs_pos = page->GetAbsPos();
      if (abs_pos >= 0) {
         _Tabs->SetHidden(page);
         QWidget * widget = page->TabContents();
         if (widget != NULL) {
#ifdef QT4
            removeTab(indexOf(widget));
#else
            removePage(widget);
#endif
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

void CTabWidget::ActivatePage(CPage * page)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   QWidget * widget = page->TabContents();
   if (widget != NULL) {
#ifdef QT4
      setCurrentIndex(indexOf(widget));
#else
      showPage(widget);
#endif
   }
   _WidgetStack->raiseWidget(this);
   if (_LanguageChanged) {
      DelayedLanguageChange();
   }
WMETHOD_VOID_EPILOG
#endif
}

void CTabWidget::Reset()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
#ifdef QT4
   int index = currentIndex();
   if (index != 0) {
      setCurrentIndex(0);
   }
#else
   int index = currentPageIndex();
   if (index != 0) {
      setCurrentPage(0);
   }
#endif
WMETHOD_VOID_EPILOG
#endif
}

QWidget * CTabWidget::TabContents(CTabWidget * tab_widget, CPage * page)
{
   if (_ScrollingEnabled) {
      if (page->getScrollView()) {
         CScrollView * scroll_view = new CScrollView(page);
#ifdef QT4
         scroll_view->setWidget(page);
#else
         scroll_view->addChild(page);
#endif
         page->SetTabContents(scroll_view);
         return scroll_view;
      } else {
         page->SetTabContents(page);
         return page;
      }
   } else {
      page->SetTabContents(page);
      return page;
   }
}

CPage * CTabWidget::Page(QWidget * tab_contents)
{
   CPage * page = NULL;
   if (_ScrollingEnabled) {
      if (tab_contents != NULL) {
         if (tab_contents->inherits("CScrollView")) {
            CScrollView * scroll_view = (CScrollView*)tab_contents;
            page = scroll_view->Page();
         } else {
            page = (CPage*)tab_contents;
         }
      } else {
         page = (CPage*)tab_contents;
      }
   } else {
      page = (CPage*)tab_contents;
   }
   return page;
}

void CTabWidget::PrepareTabs()
{
#ifdef OBSOLETED_SUPERFLUOS_CODE
   // PR 22.01.15
   // this code was superfluosly introduced caused by stepwise changes:
   //
   // 1. problems with first pages in a tab widget that are dark
   // 2. problems with the page forward/backward functionality
   // 3. problems with transparent pages showing the first page of a tab
   //    in areas not covered by widgets of the page

//   QWidget * widget = this->widget(0);
//   CPage * page = dynamic_cast<CPage*>(widget);
//   if (page != NULL) {
//      page->show();
//   }
//   return;
   int page_count = this->count();
   int page_index = 0;
   for (page_index=0; page_index<page_count; page_index++) {
      QWidget * widget = this->widget(page_index);
      CPage * page = dynamic_cast<CPage*>(widget);
      if (page != NULL) {
         ULONG_T appearance_state = page->GetAppearanceState();
         if (appearance_state != 2) {
            page->show();
            return;
         }
      }
   }
   page_index = this->currentIndex();
   QWidget * widget = this->widget(page_index);
   CPage * page = dynamic_cast<CPage*>(widget);
   if (page != NULL) {
      ULONG_T appearance_state = page->GetAppearanceState();
      page->show();
   }
#endif
}

QTabBar * CTabWidget::TabBar()
{
   return this->tabBar();
}

//Slot that is called when Tab selection changes
void CTabWidget::currentChangedSlot(int index)
{
   EmitGUISignal(SIG_TABWIDGET_CURRENT_CHANGED);
}


int CTabWidget::addTab (QWidget * page, const QString & label)
{
   if (_Tabs == NULL) {
#ifndef QT_PLUGIN
       BOOL_T construct_opaque_pages = false;
       cResources::GetOption("ConstructOpaquePages", construct_opaque_pages);
       if (construct_opaque_pages) {
          page->setAutoFillBackground(true);
       }
#endif
   }
   return QTabWidget::addTab(page, label);
}

int CTabWidget::addTab (QWidget * page, const QIcon & icon, const QString & label)
{
   if (_Tabs == NULL) {
#ifndef QT_PLUGIN
       BOOL_T construct_opaque_pages = false;
       cResources::GetOption("ConstructOpaquePages", construct_opaque_pages);
       if (construct_opaque_pages) {
          page->setAutoFillBackground(true);
       }
#endif
   }

   return QTabWidget::addTab(page, icon, label);
}