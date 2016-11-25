
#include "CPage.h"
#include "CTabWidget.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(FormWidget, \
                   CPage, \
                   ICON_SET("form"),
                   "SHACIRA frame work information page widget, use File->New... to create")
#endif

#include "CGroupSelectButton.h"
#include "plugin_log.h"
#define OFFSET(comp) ((char*)(&comp) - (char*)this)

CPage::CPage (QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f) :
   CWidget(parent, name, f)
{
   CONSTRUCT_WIDGET

   _UserFlagsValue = 0;

   _DataRefreshPending = false;
   _BGDataRefreshPending = false;
   _TextRefreshPending = false;

   _TabWidget = NULL;
   _AbsPos = -1;
   _PositionInGroupValue = 0;
   _PositionInGroup = 0;

   _SpecificColorValue = CWidgetBase::paletteBackgroundColor();
   _ScrollViewValue = false;
   _SelectButton = NULL;
   _TabContents = NULL;

#ifndef QT_PLUGIN
   BOOL_T construct_opaque_pages = false;
   cResources::GetOption("ConstructOpaquePages", construct_opaque_pages);
   if (construct_opaque_pages) {
      setAutoFillBackground(true);
   }
#endif
}

CPage::~CPage ( ) 
{
#ifndef QT_PLUGIN
//   InfoPrintf("deleting page %s\n", CONST_STRING(Name()));
#endif
}

void CPage::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CWidget::mousePressEvent(e);
   }
}

void CPage::mouseReleaseEvent(QMouseEvent * e)
{
   CWidget::mouseReleaseEvent(e);
#ifndef QT_PLUGIN
#endif
}

// GUI related virtual methods

void CPage::View()
{
}

void CPage::CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_DataRefreshPending) {
      if (_QWidget->isVisible()) {
         emit(CheckAppearanceSignal(DATA_REFRESH, elementFree));
         _DataRefreshPending = false;
      }
   }
   if (_BGDataRefreshPending) {
      if (_QWidget->isVisible()) {
         emit(CheckAppearanceSignal(BG_DATA_REFRESH, elementFree));
         _BGDataRefreshPending = false;
      }
   }
   if (_TextRefreshPending) {
      if (_QWidget->isVisible()) {
         emit(CheckAppearanceSignal(TEXT_REFRESH, elementFree));
         _TextRefreshPending = false;
      }
   }
   CheckAppearance(refresh_type, parent_state);
   if (IS_DATA_REFRESH(refresh_type)) {
      if (_QWidget->isVisible() || IS_IMMEDIATE(refresh_type)) {
         emit(CheckAppearanceSignal(DATA_REFRESH, elementFree));
         _DataRefreshPending = false;
      } else {
         _DataRefreshPending = true;
         return;
      }
   }
   if (IS_BG_DATA_REFRESH(refresh_type)) {
      if (_QWidget->isVisible() || IS_IMMEDIATE(refresh_type)) {
         emit(CheckAppearanceSignal(BG_DATA_REFRESH, elementFree));
         _BGDataRefreshPending = false;
      } else {
         _BGDataRefreshPending = true;
         return;
      }
   }
   if (IS_TEXT_REFRESH(refresh_type)) {
      if (_QWidget->isVisible() || IS_IMMEDIATE(refresh_type)) {
         emit(CheckAppearanceSignal(TEXT_REFRESH, elementFree));
         _TextRefreshPending = false;
      } else {
         _TextRefreshPending = true;
         return;
      }
   }
   emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
WMETHOD_VOID_EPILOG
#endif
}

// CCS related virtual methods

void CPage::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
   _Name = Name();
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

void CPage::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                        UCHAR_T data_type, ULONG_T size)
{
}

void CPage::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                        UCHAR_T data_type, ULONG_T size)
{
}

void CPage::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CPage::showEvent(QShowEvent * e)
{
#ifdef OBSOLETED_SUPERFLUOS_CODE
   // PR 22.01.15
   // this code was superfluosly introduced caused by stepwise changes:
   //
   // 1. problems with first pages in a tab widget that are dark
   // 2. problems with the page forward/backward functionality
   // 3. problems with transparent pages showing the first page of a tab
   //    in areas not covered by widgets of the page

   // workaround for problem with pages that show through the current page
   // when using pages with background filling disabled
   CTabWidget * tabWidget = this->TabWidget();
   if (tabWidget != NULL) {
      QWidget * widget = tabWidget->currentWidget();
      if (widget != this) {
         // in this case showEvent is called for the first page of the tab widget
         // and this page is not the current page
         // if this case the first tab page (this page) must be hidden immediatly.
         // otherwise elements (widgets of this page may show through the current page)
         this->hide();
         return;
      }
   }
#endif
   CWidget::showEvent(e);
   ActivateButton();
   emit(PageShown(this));
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
      cUserInfo * user_info = (cUserInfo*)cSystemUtils::GetThreadData();
      ULONG_T dataset = user_info->get_DataSet();
      SetColor(dataset);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CPage::SetTabWidget(CTabWidget * tab_widget)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _TabWidget = tab_widget;
WMETHOD_VOID_EPILOG
#endif
}

CTabWidget * CPage::TabWidget()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _TabWidget;
WMETHOD_RC_EPILOG(NULL)
#endif
   return NULL;
}

void CPage::SetAbsPos(LONG_T abs_pos)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _AbsPos = abs_pos;
WMETHOD_VOID_EPILOG
#endif
}

LONG_T CPage::GetAbsPos()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   return _AbsPos;
WMETHOD_RC_EPILOG(-1)
#endif
   return -1;
}

LONG_T CPage::GetRelPos()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_TabWidget != NULL) {
      return _TabWidget->RelPos(this);
   }
WMETHOD_RC_EPILOG(-1)
#endif
   return -1;
}

void CPage::SetSelectButton(CGroupSelectButton * button)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _SelectButton = button;
WMETHOD_VOID_EPILOG
#endif
}

void CPage::Activate()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_TabWidget != NULL) {
      _TabWidget->ActivatePage(this);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CPage::ActivateButton()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_SelectButton != NULL) {
      _SelectButton->SetActive(true);
   }
WMETHOD_VOID_EPILOG
#endif
}

void CPage::Leave()
{
    EmitGUISignal(SIG_LEAVE_PAGE);
}

void CPage::Enter()
{
    EmitGUISignal(SIG_ENTER_PAGE);
}

BOOL_T CPage::similarSizeAsFramePage()
{
    BOOL_T similar = false;
    int maxWidthDelta = 20;
    int maxHeightDelta = 50;
    int pageContainerWidth  = CAppFrame::getPageContainerWidth();
    int pageContainerHeight = CAppFrame::getPageContainerHeight();
    int deltaPageContainerWidth = abs(pageContainerWidth - width());
    int deltaPageContainerHeight = abs(pageContainerHeight - height());
#ifdef QT_PLUGIN
    PluginPrintf("pageContainerSize (%d/%d)\n", pageContainerWidth, pageContainerHeight);
    PluginPrintf("deltaPageContainerWidth: %d  ,  deltaPageContainerHeight: %d\n", deltaPageContainerWidth, deltaPageContainerHeight);
#endif
    if ((deltaPageContainerWidth <= maxWidthDelta) && (deltaPageContainerHeight <= maxHeightDelta)) {
        similar = true;
    }
#ifdef QT_PLUGIN
    PluginPrintf("ObjectName %s  ,  similarSizeAsFramePage = %d\n", CONST_STRING(objectName()), similar);
#endif
    return similar;
}