
#include "FirstHeader.h"
#include "CorbaDefinitions.h"

void __DLL_EXPORT__ ThrowAppException(cError & e)
{
   Control::AppException a;
   a.ErrCode = e.get_ErrCode();
   a.NativeCode = e.get_NativeCode();
   a.Param1 = e.get_Param1().c_str();
   a.Param2 = e.get_Param2().c_str();
   a.Param3 = e.get_Param3().c_str();
   a.Param4 = e.get_Param4().c_str();
   throw a;
}

void __DLL_EXPORT__ ThrowUnhandledException(const char * method_name)
{
   Control::AppException a;
   a.ErrCode = CORBA_UNHANDLED_EXCEPTION;
   a.NativeCode = 0;
   a.Param1 = method_name;
   throw a;
}


