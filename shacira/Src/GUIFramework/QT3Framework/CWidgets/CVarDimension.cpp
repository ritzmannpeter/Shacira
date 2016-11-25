
#include "CVarDimension.h"
#include <qapplication.h>

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(DisplayWidget, \
                   CVarDimension, \
                   ICON_SET("designer_label"), \
                   "text display widget that shows the current physical unit of the corresponding variable reference")
#endif

CVarDimension::CVarDimension(QWidget * parent, const char * name, WFlags f)
   : CFixText(parent, name, f) 
{
   CONSTRUCT_WIDGET
   setMinimumHeight(25);
   _Variable = NULL;
}

CVarDimension::~CVarDimension ( ) 
{
}

void CVarDimension::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CFixText::mousePressEvent(e);
   }
}

void CVarDimension::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      CFixText::mouseReleaseEvent(e);
   }
}

void CVarDimension::slotSetVariable(const QCString variable_name)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (!variable_name.isEmpty()) {
      _Variable = _Context->Variable(CONST_STRING(variable_name));
      View();
   }
WMETHOD_VOID_EPILOG
#endif
}

// GUI related virtual methods

void CVarDimension::View()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_Variable != NULL) {
      STRING_T dimension = _Variable->UnitText();
      if (dimension.size() > 0) {
         setText(qApp->translate("custom", dimension.c_str()));
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

// CCS related virtual methods

void CVarDimension::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
   CFixText::CCSSetContext(node, context);
   if (!_VariableValue.isEmpty()) {
      _Variable = context->Variable((CONST_STRING_T)_VariableValue);
   }
#endif
}

void CVarDimension::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                           UCHAR_T data_type, ULONG_T size)
{
}

void CVarDimension::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CVarDimension::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
#endif
}

