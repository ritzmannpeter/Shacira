
#include "CGroupSelectButton.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(ButtonWidget, \
                   CGroupSelectButton, \
                   ICON_SET("toolbutton"), \
                   "Tool button to select SHACIRA framework information page groups")
#endif

CGroupSelectButton::CGroupSelectButton(QWidget * parent, const char * name)
   : CToolButton(parent, name)
{
   _ContainerSensitiveValue = true;
   _GroupPosValue = 0;
}

CGroupSelectButton::~CGroupSelectButton() 
{
}

void CGroupSelectButton::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      CToolButton::mousePressEvent(e);
   }
}

void	CGroupSelectButton::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      CToolButton::mouseReleaseEvent(e);
//      emit GroupSelected(_PageGroupValue);
   }
   emit GroupSelected(_PageGroupValue);
}

// GUI related virtual methods

void CGroupSelectButton::View()
{
}

// CCS related virtual methods

void CGroupSelectButton::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
   CToolButton::CCSSetContext(node, context);
#endif
}

void CGroupSelectButton::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                                     UCHAR_T data_type, ULONG_T size)
{
}

void CGroupSelectButton::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                                     UCHAR_T data_type, ULONG_T size)
{
}

void CGroupSelectButton::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

