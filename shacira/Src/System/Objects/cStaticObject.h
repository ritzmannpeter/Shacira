
#ifndef cStaticObject_h
#define cStaticObject_h 1

#include "base/eb_sema.hpp"
#include "System/cValue.h"

class __DLL_EXPORT__ cTransientObject;
class __DLL_EXPORT__ cConfigurationObject;

#define PARAM_NAME_EQUALS(pname,pconst)   (_stricmp(pname,pconst) == 0)
#define GET_BASE_PARAM(object_class, pname, pvalue) \
   object_class::ObjectGetParam(pname,pvalue)
#define SET_BASE_PARAM(object_class, pname, pvalue) \
   object_class::ObjectSetParam(pname,pvalue)

typedef std::map<STRING_T,cValue*>  PARAMETER_MAP_T;

class __DLL_EXPORT__ cStaticObject 
{
public:
typedef std::list<cStaticObject*> LISTENER_LIST_T;
typedef std::map<STRING_T,LISTENER_LIST_T> LISTENER_MAP_T;
   cStaticObject();
   cStaticObject(cConfigurationObject * config_object);
   virtual ~cStaticObject();
   virtual void Event(cTransientObject *object);
   void RaiseEvent(cTransientObject *object);
   void ListenTo(cStaticObject *source);
   virtual void Start();
   virtual void Stop();
   void Protocol(CONST_STRING_T fmt_str, ...);
   void Protocol2(ULONG_T level, CONST_STRING_T fmt_str, ...);
   cValue & Parameter(CONST_STRING_T name);
   BOOL_T SetParam(CONST_STRING_T name, CONST_STRING_T value);
   BOOL_T SetParam(CONST_STRING_T name, LONG_T value);
   BOOL_T SetParam(CONST_STRING_T name, ULONG_T value);
   BOOL_T SetParam(CONST_STRING_T name, DOUBLE_T value);
   BOOL_T GetParam(CONST_STRING_T name, STRING_T &value);
   BOOL_T GetParam(CONST_STRING_T name, LONG_T &value);
   BOOL_T GetParam(CONST_STRING_T name, ULONG_T &value);
   BOOL_T GetParam(CONST_STRING_T name, DOUBLE_T &value);
   BOOL_T HasReferences();
   void HasReferences(BOOL_T state);
   static ULONG_T get_ObjectCount();
   STRING_T get_Name() const;
   void set_Name(STRING_T value);
   STRING_T get_Class() const;
   void set_Class(STRING_T value);
   STRING_T get_Type() const;
   void set_Type(STRING_T value);
   ULONG_T get_Ident() const;
   void set_Ident(ULONG_T value);
   virtual BOOL_T ObjectSetParam (CONST_STRING_T name, CONST_STRING_T value);

protected:
   static ULONG_T _ObjectCount;
   STRING_T _Name;
   STRING_T _Class;
   STRING_T _Type;
   ULONG_T _Ident;
   BOOL_T _HasReferences;
   cMutexSem _LockMutex;
   cConfigurationObject * _ConfigurationObject;
private:
   void AddListener(cStaticObject *target);
private:
   LISTENER_LIST_T _Listeners;
   PARAMETER_MAP_T _Parameters;
   char * _PrintBuffer;
};


#endif
