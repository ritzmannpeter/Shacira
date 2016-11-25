

#include "CGraphicsView.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ViewWidget, \
                   CGraphicsView, \
                   ICON_SET("graphicsview"), \
                   "graphics view")
#endif

CGraphicsView::CGraphicsView(QWidget * parent, const char * name)
#ifdef QT4
   : QGraphicsView(parent),
#else
   : QGraphicsView(parent, name),
#endif
     CWidgetBase(this)
{
   if (name != NULL) {
      setObjectName(name);
   }
   CONSTRUCT_WIDGET

   _VarRef = NULL;
   _VarView = NULL;
}

CGraphicsView::~CGraphicsView() 
{
}

void CGraphicsView::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QGraphicsView::mousePressEvent(e);
   }
}

void CGraphicsView::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QGraphicsView::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CGraphicsView::View()
{
}

// CCS related virtual methods

void CGraphicsView::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
WMETHOD_VOID_EPILOG
#endif
}

void CGraphicsView::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
#endif
}

void CGraphicsView::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size)
{
}

void CGraphicsView::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

