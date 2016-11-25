
#include "CScrollView.h"
#include "CPage.h"

#ifdef _XCWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(FormWidget, \
                   CScrollView, \
                   ICON_SET("designer_form"),
                   "SHACIRA framework information view widget, use File->New... to create")
#endif

#include "CGroupSelectButton.h"

CScrollView::CScrollView(CPage * page, QWidget * parent, const char * name, WFlags f)
   : QScrollView(parent, name, WStaticContents),
     CWidgetBase(this)
{
   _Page = page;
   if (_Page != NULL) {
      QString view_name = _Page->Name();
      view_name += "_ScrollView";
   } else {
      setName(name);
   }
   setFrameShape(NoFrame);
}

CScrollView::~CScrollView ( ) 
{
}

void CScrollView::mousePressEvent(QMouseEvent * e)
{
}

void CScrollView::mouseReleaseEvent(QMouseEvent * e)
{
   QScrollView::mouseReleaseEvent(e);
}

// GUI related virtual methods

void CScrollView::View()
{
}

void CScrollView::CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
{
}

// CCS related virtual methods

void CScrollView::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
}

void CScrollView::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                        UCHAR_T data_type, ULONG_T size)
{
}

void CScrollView::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                        UCHAR_T data_type, ULONG_T size)
{
}

void CScrollView::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CScrollView::showEvent(QShowEvent * e)
{
   QScrollView::showEvent(e);
}

