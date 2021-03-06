
#include "CProgressBar.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "cQtPluginRegistry.h"
#include "plugin_icons.h"
SH_PLUGIN_REGISTER(DisplayWidget, \
                   CProgressBar, \
                   ICON_SET("designer_progress"), \
                   "progress bar widget")
#endif

#ifndef QT_PLUGIN
#include "System/Objects/cProgress.h"
#endif

CProgressBar::CProgressBar(QWidget * parent, const char * name, WFlags f)
   : QProgressBar(parent, name),
     CWidgetBase(this) 
{
   CONSTRUCT_WIDGET

   _ValueRef = NULL;
   _ValueView = NULL;
   _MaximumRef = NULL;
   _MaximumView = NULL;
   _IndicatorIdValue = 0;
   _Value = 0;
   _Maximum = 100;
}

CProgressBar::~CProgressBar() 
{
}

void CProgressBar::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QProgressBar::mousePressEvent(e);
   }
}

void CProgressBar::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QProgressBar::mouseReleaseEvent(e);
   }
}

void CProgressBar::paintEvent (QPaintEvent * e)
{
   QProgressBar::paintEvent(e);
}

void CProgressBar::SetProgress(int value)
{
   if (value < 0) value = 0; 
   if (value > 100) value = 100; 
   setProgress(value, 100);
}

// GUI related virtual methods

void CProgressBar::View()
{
}

// CCS related virtual methods

void CProgressBar::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   CCSInitializeVarRef(_ValueSpec, _ValueRef, _ValueView, 0);
   CCSInitializeVarRef(_MaximumSpec, _MaximumRef, _MaximumView, 1);
WMETHOD_VOID_EPILOG
#endif
}

void CProgressBar::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                             UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   LONG_T lval = atol(value);
   switch (id) {
   case 0:
      _Value = lval;
      break;
   case 1:
      _Maximum = lval;
      break;
   }
   LONG_T progress_value = 0;
   if (_Maximum > 0) {
      progress_value = (_Value * 100) / _Maximum;
   }
   SetProgress(progress_value);
WMETHOD_VOID_EPILOG
#endif
}

void CProgressBar::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                          UCHAR_T data_type, ULONG_T size)
{
}

void CProgressBar::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   UCHAR_T object_type = object->get_Type();
   if (object_type == OT_PROGRESS) {
      cProgress * progress = (cProgress*)object;
      ULONG_T indicator_id = progress->get_IndicatorId();
      if ((int)indicator_id == _IndicatorIdValue) {
         int value = progress->get_Value();
         SetProgress(value);
      }
   }
   WMETHOD_VOID_EPILOG
#endif
}

