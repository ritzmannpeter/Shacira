

#include "CTable.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CTable, \
                   ICON_SET("table"), \
                   "table widget")
#endif

CTable::CTable(QWidget * parent, const char * name)
#ifdef QT4
   : CTABLE_BASE_CLASS(parent),
#else
   : CTABLE_BASE_CLASS(parent, name),
#endif
     CWidgetBase(this)
{
   CONSTRUCT_WIDGET

   _VarRef = NULL;
   _VarView = NULL;
   _readOnly = false;
}

CTable::~CTable() 
{
}

void CTable::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CTABLE_BASE_CLASS::mousePressEvent(e);
   }
}

void CTable::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      CTABLE_BASE_CLASS::mouseReleaseEvent(e);
   }
}

// GUI related virtual methods

void CTable::View()
{
}

// CCS related virtual methods

void CTable::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
WMETHOD_VOID_EPILOG
#endif
}

void CTable::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
#endif
}

void CTable::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                         UCHAR_T data_type, ULONG_T size)
{
}

void CTable::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

