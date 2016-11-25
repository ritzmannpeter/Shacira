
#ifndef _casyncfunction_h_
#define _casyncfunction_h_

#include "CWidgetBase.h"
#include "guiops.h"
#include "base/eb_thread.hpp"

class cAsyncFunction : public cThread
{
public:
   cAsyncFunction(FUNC_REF_PTR func_ref, QWidget * widget, USER_INFO_PTR user_info);
   virtual ~cAsyncFunction();
   virtual int onMain(void * extra);
   void Execute();
   BOOL_T Terminated();
   ULONG_T Action();
public:
   BOOL_T _ErrorThrown;
   cError _Error;
private:
   USER_INFO_PTR _UserInfo;
   QWidget * _Widget;
   FUNC_REF_PTR _FuncRef;
   BOOL_T _Terminated;
   ULONG_T _Action;
};


#endif
