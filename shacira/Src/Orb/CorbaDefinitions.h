
#ifndef CorbaDefinitions_h
#define CorbaDefinitions_h 1

#include "System/cError.h"
#include "orb_def.h"

#define CORBA_STRING_DUP  CORBA::string_dup
#define FREE_CORBA_STRING(str) if (str != NULL) CORBA::string_free(str);

#define OMNI_ORB_IDENTIFIER "omniORB4"
#define OMNI_BOA_IDENTIFIER "omniORB4_BOA"
#include <CORBA.h>
#define strdup string_dup
#include "CosEventComm.hh"
#include "CosEventChannelAdmin.hh"
#include "Control.hh"

// if (itf == NULL) throw cError(PROXY_NO_INTERFACE, 0, name);  error when not initilized

#define CORBA_ITF_PROLOG(name,itf) \
if (itf == NULL) SetItf(); \
const char * __name__ = name; \
try {
#define CORBA_ITF_EPILOG \
} catch (const Control::AppException & e) { \
   throw cError(e.ErrCode, e.NativeCode, e.Param1, e.Param2, e.Param3, e.Param4); \
} catch(CORBA::COMM_FAILURE & e) { \
   _Connected = false; \
   throw cError(PROXY_NO_OBJECT, 0, __name__); \
} catch(CORBA::SystemException & e) { \
   _Connected = false; \
   throw cError(PROXY_CORBA_SYSTEM, 0, __name__); \
} catch(CORBA::Exception & e) { \
   _Connected = false; \
   throw cError(PROXY_CORBA_SYSTEM, 0, __name__); \
} catch (...) { \
   _Connected = false; \
   throw cError(PROXY_UNHANDLED_EXCEPTION, 0, __name__); \
}

#define CORBA_BIND_PROLOG(name, ior) \
if (strlen(ior) == 0) throw cError(PROXY_NO_OBJECT_INTERFACE, 0, name); \
const char * __name__ = name; \
try {
#define CORBA_BIND_EPILOG \
} catch(CORBA::COMM_FAILURE & e) { \
   throw cError(PROXY_NO_OBJECT, 0, __name__); \
} catch(CORBA::SystemException & e) { \
   throw cError(PROXY_CORBA_SYSTEM, 0, __name__); \
} catch(CORBA::Exception & e) { \
   throw cError(PROXY_CORBA_SYSTEM, 0, __name__); \
} catch (...) { \
   throw cError(PROXY_UNHANDLED_EXCEPTION, 0, __name__); \
}

// General definitions (not depending on the type of the concrete ORB)

#include "base/eb_sema.hpp"
#include "System/Objects/cObjectLock.h"
#define CORBA_OBJECT_SEMAPHORE cMutexSem _CorbaObjectMutex;

#define CORBA_OBJECT_PROLOG_NO_LOCK(name) \
const char * __name__ = name; \
try {
#define CORBA_OBJECT_PROLOG(name) \
cObjectLock __lock__(&_CorbaObjectMutex); \
const char * __name__ = name; \
try {
#define CORBA_OBJECT_EPILOG \
} catch (cError & e) { \
   ThrowAppException(e); \
} catch (...) { \
   ThrowUnhandledException(__name__); \
}

#define NULL_ORB     CORBA::ORB::_nil()
#define NULL_BOA     CORBA::BOA::_nil()
#define NULL_OBJ     CORBA::Object::_nil()
#define NULL_POA     PortableServer::POA::_nil()

void __DLL_EXPORT__ ThrowAppException(cError & e);
void __DLL_EXPORT__ ThrowUnhandledException(const char * method_name);

typedef void PUSH_CALLBACK_T(CORBA::Any & any);

#endif

