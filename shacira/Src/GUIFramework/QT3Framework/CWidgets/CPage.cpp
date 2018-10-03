
#include "CPage.h"
#include "CTabWidget.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(FormWidget, \
                   CPage, \
                   ICON_SET("designer_form"),
                   "SHACIRA frame work information page widget, use File->New... to create")
#endif

#include "CGroupSelectButton.h"
#include "plugin_log.h"
#define OFFSET(comp) ((char*)(&comp) - (char*)this)

CPage::CPage (QWidget * parent, const char * name, WFlags f) :
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

   _SpecificColorValue = paletteBackgroundColor();
   _ScrollViewValue = false;
   _SelectButton = NULL;
   _TabContents = NULL;
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
   CWidget::showEvent(e);
   ActivateButton();
   emit(PageShown(this));
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

BOOL_T CPage::IsVisible()
{
   return (_AppearanceState != elementInvisible) ? true : false;
}