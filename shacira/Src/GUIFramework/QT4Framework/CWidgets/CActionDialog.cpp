
/// PR 13.06.08 - only emit "check appearance signal" when dialog is active

#include "CActionDialog.h"

#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(AdditionalWidget,
                   CActionDialog, \
                   ICON_SET("form"), \
                   "base widget for external dialogs")
#endif

CActionDialog::CActionDialog (QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
#ifdef QT4
   : QDialog(parent, f),
#else
   : CWidget(parent, name, f),
#endif
     CWidgetBase(this), _Result(actionProceed)
{
#ifdef QT4
   setObjectName(name);
#endif
   CONSTRUCT_WIDGET
   _ActionTimer = NULL;
   _Widget = NULL;
   _FuncRef = NULL;
   SetActive(false);
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _ActionTimer = new QTimer(this);
   connect(_ActionTimer, SIGNAL(timeout()), SLOT(ExecuteFunction()));
WMETHOD_VOID_EPILOG
#endif
}

CActionDialog::~CActionDialog ( ) 
{
#ifndef QT_PLUGIN
   _ActionTimer->stop();
   disconnect(_ActionTimer, SIGNAL(timeout()), 0, 0);
   delete _ActionTimer;
   _ActionTimer = NULL;
#endif
}

// GUI related virtual methods

void CActionDialog::View()
{
}

void CActionDialog::CheckAppearanceSlot(ULONG_T refresh_type, ULONG_T parent_state)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   if (_IsActive) {
      emit(CheckAppearanceSignal(refresh_type, _AppearanceState));
   }
WMETHOD_VOID_EPILOG
#endif
}

void CActionDialog::ExecuteFunction()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   int rc = actionProceed;
   if (_Widget != NULL &&
       _FuncRef != NULL) {
      if (CWidgetBase::Flag(SYNC_USER_FUNCTIONS)) {
         LONG_T action = actionReject;
         CWidgetBase * widget = _Widget;
         FUNC_REF_PTR func_ref = _FuncRef;
         _Widget = NULL;
         _FuncRef = NULL;
         try {
//            cSystemUtils::SetThreadData(_UserInfo);
            func_ref->CallGUIFunc(action, widget->Widget());
         } catch (cError & e) {
            rc = action;
            Terminated(rc, e);
            return;
         } catch (...) {
            rc = action;
            Terminated(rc);
            return;
         }

         rc = action;
         Terminated(rc);
      } else {
         CWidgetBase * widget = _Widget;
         FUNC_REF_PTR func_ref = _FuncRef;
         _Widget = NULL;
         _FuncRef = NULL;
         cError e;
         rc = widget->AsyncExec(func_ref, e);
         if ((rc == actionReject) && 
             ((e.get_ErrCode() != 0) || e.get_NativeCode() != 0)) {
            Terminated(rc, e);
         } else {
            Terminated(rc);
         }
      }
   }
WMETHOD_VOID_EPILOG
#endif
}

// CCS related virtual methods

void CActionDialog::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
   _Name = Name();
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

void CActionDialog::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                                UCHAR_T data_type, ULONG_T size)
{
}

void CActionDialog::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                                UCHAR_T data_type, ULONG_T size)
{
}

void CActionDialog::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CActionDialog::Reset()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

void CActionDialog::SetContext(NODE_PTR node, CONTEXT_PTR context)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
   _Node = node;
   _Context = context;
   CWidgetBase::PropagateContext(this, _Node, _Context);
WMETHOD_VOID_EPILOG
#endif
}

void CActionDialog::SetFunction(CWidgetBase * widget, FUNC_REF_PTR func_ref)
{
   _Widget = widget;
   _FuncRef = func_ref;
   _ActionTimer->start(400);
}

void CActionDialog::Terminated()
{
}

void CActionDialog::Terminated(ULONG_T rc)
{
}

void CActionDialog::Terminated(ULONG_T rc, ERROR_REF_T e)
{
}

