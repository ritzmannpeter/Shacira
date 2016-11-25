
/// PR 12.05.05 - removed in handling of return values after thread termination

#include "casyncfunction.h"

cAsyncFunction::cAsyncFunction(FUNC_REF_PTR func_ref, QWidget * widget, USER_INFO_PTR user_info)
{
   _UserInfo = user_info;
   _FuncRef = func_ref;
   _Widget = widget;
   _ErrorThrown = false;
   _Terminated = false;
   _Action = actionProceed;
}

cAsyncFunction::~cAsyncFunction()
{
}

int cAsyncFunction::onMain(void * extra)
{
   try {
      cSystemUtils::SetThreadData(_UserInfo);
      _Action = actionProceed;
      if (_FuncRef == NULL) {
         _Terminated = true;
      } else {
         _FuncRef->CallGUIFunc(_Action, _Widget);
         _Terminated = true;
      }
   } catch (cError & e) {
      _ErrorThrown = true;
      _Error = e;
      _Action = actionReject;
      _Terminated = true;
   } catch (...) {
      _ErrorThrown = true;
      _Error = cError();
      _Action = actionReject;
      _Terminated = true;
   }
   return _Action;
}

void cAsyncFunction::Execute()
{
   start();
}

BOOL_T cAsyncFunction::Terminated()
{
   return _Terminated;
}

ULONG_T cAsyncFunction::Action()
{
   return _Action;
}

