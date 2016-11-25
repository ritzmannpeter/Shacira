
#include "CScrollView.h"
#include "CPage.h"

#ifdef _XCWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(FormWidget, \
                   CScrollView, \
                   ICON_SET("scrollview"),
                   "SHACIRA framework information view widget, use File->New... to create")
#endif

#include "CGroupSelectButton.h"

CScrollView::CScrollView(CPage * page, QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : CSCROLLVIEW_BASE_CLASS(parent),
#else
   : CSCROLLVIEW_BASE_CLASS(parent, name, Qt::WStaticContents),
#endif
     CWidgetBase(this)
{
   _Page = page;
   if (_Page != NULL) {
      QString view_name = _Page->Name();
      view_name += "_ScrollView";
   } else {
#ifdef QT4
      setObjectName(name);
#else
      setName(name);
#endif
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
   CSCROLLVIEW_BASE_CLASS::mouseReleaseEvent(e);
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
   CSCROLLVIEW_BASE_CLASS::showEvent(e);
}

