
#include "FirstHeader.h"
#include "cEM63LogInfo.h"
#include "cEM63Interface.h"

cEM63LogInfo::cEM63LogInfo()
{
   __ECL_ATOMIC_SET__(_RefCount, 1);
   _Category = 0;
   _Operation = 0;
   _ErrCode = 0;
   INCREMENT_OBJECT_COUNT()
}

cEM63LogInfo::cEM63LogInfo(ULONG_T category, ULONG_T operation, int err_code,
                           CONST_STRING_T param1, CONST_STRING_T param2, CONST_STRING_T param3)
{
   __ECL_ATOMIC_SET__(_RefCount, 1);
   _Category = category;
   _Operation = operation;
   _ErrCode = err_code;
   if (param1 != NULL) {
      _Param1 = param1;
   }
   if (param2 != NULL) {
      _Param2 = param2;
   }
   if (param3 != NULL) {
      _Param3 = param3;
   }
   INCREMENT_OBJECT_COUNT()
}

cEM63LogInfo::~cEM63LogInfo()
{
   DECREMENT_OBJECT_COUNT()
}

void cEM63LogInfo::AddRef()
{
   __ECL_ATOMIC_INCREMENT__(_RefCount);
}

void cEM63LogInfo::Release()
{
   int ref_count = __ECL_ATOMIC_DECREMENT__(_RefCount);
   if (ref_count == 0) {
      delete this;
   }
}

ULONG_T cEM63LogInfo::Category()
{
   return _Category;
}

void cEM63LogInfo::SetCategory(ULONG_T category)
{
   _Category = category;
}

ULONG_T cEM63LogInfo::Operation()
{
   return _Operation;
}

void cEM63LogInfo::SetOperation(ULONG_T operation)
{
   _Operation = operation;
}

int cEM63LogInfo::ErrCode()
{
   return _ErrCode;
}

void cEM63LogInfo::SetErrCode(ULONG_T err_code)
{
   _ErrCode = err_code;
}

STRING_T cEM63LogInfo::Param1()
{
   return _Param1;
}

void cEM63LogInfo::SetParam1(const char * param)
{
   _Param1 = param;
}

STRING_T cEM63LogInfo::Param2()
{
   return _Param2;
}

void cEM63LogInfo::SetParam2(const char * param)
{
   _Param2 = param;
}

STRING_T cEM63LogInfo::Param3()
{
   return _Param3;
}

void cEM63LogInfo::SetParam3(const char * param)
{
   _Param3 = param;
}


