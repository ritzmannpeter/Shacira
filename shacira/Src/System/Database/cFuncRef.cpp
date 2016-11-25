//## begin module%3C7E428400AB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C7E428400AB.cm

//## begin module%3C7E428400AB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C7E428400AB.cp

//## Module: cFuncRef%3C7E428400AB; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cFuncRef.cpp

//## begin module%3C7E428400AB.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3C7E428400AB.additionalIncludes

//## begin module%3C7E428400AB.includes preserve=yes
//## end module%3C7E428400AB.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
// cBlockBuffer
#include "System/Memory/cBlockBuffer.h"
// cContext
#include "System/Database/cContext.h"
// cSHVariant
#include "System/Database/cSHVariant.h"
// cFuncDecl
#include "System/Database/cFuncDecl.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
// cSharedLibrary
#include "System/Sys/cSharedLibrary.h"
//## begin module%3C7E428400AB.additionalDeclarations preserve=yes

#define PUSH_PARAMS(stack) \
LONG_T long_val = 0; \
ULONG_T ulong_val = 0; \
FLOAT_T float_val = 0; \
DOUBLE_T double_val = 0; \
CONST_STRING_T const_string_val = ""; \
STRING_T string_val = ""; \
CONST_WSTRING_T const_wstring_val = (CONST_WSTRING_T)L""; \
WSTRING_T wstring_val; \
PTR_T ptr_val = NULL; \
cBlockBuffer buf; \
for (unsigned long i=0; i<_FuncDecl->Params(); i++) { \
	int type = _FuncDecl->ParamType(i); \
   switch (type) { \
   case SH_CHAR: \
   case SH_SHORT: \
   case SH_LONG: \
      _ParamVec[i]->GetValue(long_val); \
      STACK_PUSH(stack,LONG_T,long_val); \
      break; \
   case SH_UCHAR: \
   case SH_USHORT: \
   case SH_ULONG: \
   case SH_BIT_8: \
   case SH_BIT_16: \
   case SH_BIT_32: \
      _ParamVec[i]->GetValue(ulong_val); \
      STACK_PUSH(stack,ULONG_T,ulong_val); \
      break; \
   case SH_FLOAT: \
      _ParamVec[i]->GetValue(float_val); \
      STACK_PUSH(stack,FLOAT_T,float_val); \
      break; \
   case SH_DOUBLE: \
      _ParamVec[i]->GetValue(double_val); \
      STACK_PUSH(stack,DOUBLE_T,double_val); \
      break; \
   case SH_STRING: \
      _ParamVec[i]->GetValue(string_val); \
      const_string_val = buf.AllocString(string_val.c_str()); \
      STACK_PUSH(stack,CONST_STRING_T,const_string_val); \
      break; \
   case SH_WSTRING: \
      _ParamVec[i]->GetValue(wstring_val); \
      const_wstring_val = (CONST_WSTRING_T)buf.AllocString(wstring_val.c_str()); \
      STACK_PUSH(stack,CONST_WSTRING_T,const_wstring_val); \
      break; \
   case SH_BYTE: \
      _ParamVec[i]->GetValue(ptr_val); \
      STACK_PUSH(stack,PTR_T,ptr_val); \
      break; \
   case SH_OBJECT: \
      _ParamVec[i]->GetValue(ptr_val); \
      STACK_PUSH(stack,PTR_T,ptr_val); \
      break; \
   default: \
      throw cError(FUNCREF_PARAMETER_TYPE_NOT_SUPPORTED, 0, cSHVariant::TypeName(type).c_str()); \
      break; \
   } \
}

#define PUSH_INDICES(stack,i1,i2,i3,i4) \
   STACK_PUSH(stack,LONG_T,i1); \
   STACK_PUSH(stack,LONG_T,i2); \
   STACK_PUSH(stack,LONG_T,i3); \
   STACK_PUSH(stack,LONG_T,i4);

#define SET_FUNC_ADDR \
   STRING_T func_name = _FuncDecl->_FuncName; \
   UCHAR_T func_class = _FuncDecl->_FuncClass; \
   UCHAR_T func_type = _FuncDecl->DataType(); \
   switch(func_type) { \
   case SH_VOID: \
      _VoidFunc = (VOID_FUNC)GetFuncAddress(func_class, _Name.c_str()); \
      if (_VoidFunc == NULL) { \
         throw cError(FUNCREF_FUNCTION_NOT_RESOLVED, 0, _Name.c_str()); \
      } \
      break; \
   case SH_CHAR: \
   case SH_SHORT: \
   case SH_LONG: \
      _LongFunc = (LONG_FUNC)GetFuncAddress(func_class, _Name.c_str()); \
      if (_LongFunc == NULL) { \
         throw cError(FUNCREF_FUNCTION_NOT_RESOLVED, 0, _Name.c_str()); \
      } \
      break; \
   case SH_UCHAR: \
   case SH_BIT_8: \
   case SH_USHORT: \
   case SH_BIT_16: \
   case SH_ULONG: \
   case SH_BIT_32: \
      _ULongFunc = (ULONG_FUNC)GetFuncAddress(func_class, _Name.c_str()); \
      if (_ULongFunc == NULL) { \
         throw cError(FUNCREF_FUNCTION_NOT_RESOLVED, 0, _Name.c_str()); \
      } \
      break; \
   case SH_FLOAT: \
      _FloatFunc = (FLOAT_FUNC)GetFuncAddress(func_class, _Name.c_str()); \
      if (_FloatFunc == NULL) { \
         throw cError(FUNCREF_FUNCTION_NOT_RESOLVED, 0, _Name.c_str()); \
      } \
      break; \
   case SH_DOUBLE: \
      _DoubleFunc = (DOUBLE_FUNC)GetFuncAddress(func_class, _Name.c_str()); \
      if (_DoubleFunc == NULL) { \
         throw cError(FUNCREF_FUNCTION_NOT_RESOLVED, 0, _Name.c_str()); \
      } \
      break; \
   case SH_STRING: \
      _StringFunc = (STRING_FUNC)GetFuncAddress(func_class, _Name.c_str()); \
      if (_StringFunc == NULL) { \
         throw cError(FUNCREF_FUNCTION_NOT_RESOLVED, 0, _Name.c_str()); \
      } \
      break; \
   case SH_WSTRING: \
      _WStringFunc = (WSTRING_FUNC)GetFuncAddress(func_class, _Name.c_str()); \
      if (_WStringFunc == NULL) { \
         throw cError(FUNCREF_FUNCTION_NOT_RESOLVED, 0, _Name.c_str()); \
      } \
      break; \
   case SH_BYTE: \
   case SH_OBJECT: \
      _PtrFunc = (PTR_FUNC)GetFuncAddress(func_class, _Name.c_str()); \
      if (_PtrFunc == NULL) { \
         throw cError(FUNCREF_FUNCTION_NOT_RESOLVED, 0, _Name.c_str()); \
      } \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "unsupported function type"); \
   }

#define VOID_CALL(stack) \
   switch(func_type) { \
   case SH_VOID: \
      _VoidFunc(stack.mem); \
      break; \
   case SH_CHAR: \
   case SH_SHORT: \
   case SH_LONG: \
      _LongFunc(stack.mem); \
      break; \
   case SH_UCHAR: \
   case SH_BIT_8: \
   case SH_USHORT: \
   case SH_BIT_16: \
   case SH_ULONG: \
   case SH_BIT_32: \
      _ULongFunc(stack.mem); \
      break; \
   case SH_FLOAT: \
      _FloatFunc(stack.mem); \
      break; \
   case SH_DOUBLE: \
      _DoubleFunc(stack.mem); \
      break; \
   case SH_BYTE: \
   case SH_OBJECT: \
      _PtrFunc(stack.mem); \
      break; \
   case SH_STRING: \
      _StringFunc(stack.mem); \
      break; \
   case SH_WSTRING: \
      _WStringFunc(stack.mem); \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "incompatible function type"); \
   }

#define INT_CALL(stack,value) \
   switch(func_type) { \
   case SH_CHAR: \
   case SH_SHORT: \
   case SH_LONG: \
      value = _LongFunc(stack.mem); \
      break; \
   case SH_UCHAR: \
   case SH_BIT_8: \
   case SH_USHORT: \
   case SH_BIT_16: \
   case SH_ULONG: \
   case SH_BIT_32: \
      value = _ULongFunc(stack.mem); \
      break; \
   case SH_FLOAT: \
      value = (LONG_T)_FloatFunc(stack.mem); \
      break; \
   case SH_DOUBLE: \
      value = (LONG_T)_DoubleFunc(stack.mem); \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "incompatible function type"); \
   }

#define FLOAT_CALL(stack,value) \
   switch(func_type) { \
   case SH_CHAR: \
   case SH_SHORT: \
      value = (FLOAT_T)_LongFunc(stack.mem); \
      break; \
   case SH_UCHAR: \
   case SH_BIT_8: \
   case SH_USHORT: \
   case SH_BIT_16: \
      value = (FLOAT_T)_ULongFunc(stack.mem); \
      break; \
   case SH_FLOAT: \
      value = _FloatFunc(stack.mem); \
      break; \
   case SH_DOUBLE: \
      value = (FLOAT_T)_DoubleFunc(stack.mem); \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "incompatible function type"); \
   }

#define DOUBLE_CALL(stack,value) \
   switch(func_type) { \
   case SH_CHAR: \
   case SH_SHORT: \
   case SH_LONG: \
      value = _LongFunc(stack.mem); \
      break; \
   case SH_UCHAR: \
   case SH_BIT_8: \
   case SH_USHORT: \
   case SH_BIT_16: \
   case SH_ULONG: \
   case SH_BIT_32: \
      value = _ULongFunc(stack.mem); \
      break; \
   case SH_FLOAT: \
      value = _FloatFunc(stack.mem); \
      break; \
   case SH_DOUBLE: \
      value = _DoubleFunc(stack.mem); \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "incompatible function type"); \
   }

#define PTR_CALL(stack,value) \
   switch(func_type) { \
   case SH_ULONG: \
   case SH_BIT_32: \
      value = (void*)_ULongFunc(stack.mem); \
      break; \
   case SH_BYTE: \
   case SH_OBJECT: \
      value = _PtrFunc(stack.mem); \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "incompatible function type"); \
   }

#define PTR2_CALL(stack,value,size) \
   switch(func_type) { \
   case SH_OBJECT: \
      value = _PtrFunc(stack.mem); \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "incompatible function type"); \
   }

#define STRING_CALL(stack,value) \
   switch(func_type) { \
   case SH_BYTE: \
   case SH_OBJECT: \
      value = (CONST_STRING_T)_PtrFunc(stack.mem); \
      break; \
   case SH_STRING: \
      value = _StringFunc(stack.mem); \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "incompatible function type"); \
   }

#define WSTRING_CALL(stack,value) \
   switch(func_type) { \
   case SH_BYTE: \
   case SH_OBJECT: \
      value = (CONST_WSTRING_T)_PtrFunc(stack.mem); \
      break; \
   case SH_WSTRING: \
      value = _WStringFunc(stack.mem); \
      break; \
   default: throw cError(ERR_FUNCTION_CALL, 0, _Name.c_str(), "incompatible function type"); \
   }


//## end module%3C7E428400AB.additionalDeclarations


// Class cFuncRef 


























cFuncRef::cFuncRef()
  //## begin cFuncRef::cFuncRef%.hasinit preserve=no
      : _MdlFuncFactoryAddress(NULL), _GUIFuncFactoryAddress(NULL), _VoidFunc(NULL), _CharFunc(NULL), _UCharFunc(NULL), _LongFunc(NULL), _ULongFunc(NULL), _FloatFunc(NULL), _DoubleFunc(NULL), _StringFunc(NULL), _WStringFunc(NULL), _PtrFunc(NULL), _ShortFunc(NULL), _UShortFunc(NULL), _FuncDecl(NULL), _Context(NULL)
  //## end cFuncRef::cFuncRef%.hasinit
  //## begin cFuncRef::cFuncRef%.initialization preserve=yes
  //## end cFuncRef::cFuncRef%.initialization
{
  //## begin cFuncRef::cFuncRef%.body preserve=yes
  //## end cFuncRef::cFuncRef%.body
}

cFuncRef::cFuncRef(const cFuncRef &right)
  //## begin cFuncRef::cFuncRef%copy.hasinit preserve=no
      : _MdlFuncFactoryAddress(NULL), _GUIFuncFactoryAddress(NULL), _VoidFunc(NULL), _CharFunc(NULL), _UCharFunc(NULL), _LongFunc(NULL), _ULongFunc(NULL), _FloatFunc(NULL), _DoubleFunc(NULL), _StringFunc(NULL), _WStringFunc(NULL), _PtrFunc(NULL), _ShortFunc(NULL), _UShortFunc(NULL), _FuncDecl(NULL), _Context(NULL)
  //## end cFuncRef::cFuncRef%copy.hasinit
  //## begin cFuncRef::cFuncRef%copy.initialization preserve=yes
  //## end cFuncRef::cFuncRef%copy.initialization
{
  //## begin cFuncRef::cFuncRef%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFuncRef::cFuncRef%copy.body
}

cFuncRef::cFuncRef (cFuncDecl *func_decl, cContext *context)
  //## begin cFuncRef::cFuncRef%1040202772.hasinit preserve=no
      : _MdlFuncFactoryAddress(NULL), _GUIFuncFactoryAddress(NULL), _VoidFunc(NULL), _CharFunc(NULL), _UCharFunc(NULL), _LongFunc(NULL), _ULongFunc(NULL), _FloatFunc(NULL), _DoubleFunc(NULL), _StringFunc(NULL), _WStringFunc(NULL), _PtrFunc(NULL), _ShortFunc(NULL), _UShortFunc(NULL), _FuncDecl(NULL), _Context(NULL)
  //## end cFuncRef::cFuncRef%1040202772.hasinit
  //## begin cFuncRef::cFuncRef%1040202772.initialization preserve=yes
  //## end cFuncRef::cFuncRef%1040202772.initialization
{
  //## begin cFuncRef::cFuncRef%1040202772.body preserve=yes
_ASSERT_COND(context != NULL)
	_Context = context;
	_FuncDecl = func_decl;
   _Name = _FuncDecl->_FuncName;
  //## end cFuncRef::cFuncRef%1040202772.body
}


cFuncRef::~cFuncRef()
{
  //## begin cFuncRef::~cFuncRef%.body preserve=yes
   ULONG_T params = _ParamVec.size();
   for (ULONG_T i=0; i<params; i++) {
      cArgument * arg = _ParamVec[i];
      DELETE_OBJECT(cArgument, arg)
   }
  //## end cFuncRef::~cFuncRef%.body
}



//## Other Operations (implementation)
UCHAR_T cFuncRef::DataType ()
{
  //## begin cFuncRef::DataType%1061798000.body preserve=yes
   return _FuncDecl->DataType();
  //## end cFuncRef::DataType%1061798000.body
}

cFuncDecl * cFuncRef::FuncDecl ()
{
  //## begin cFuncRef::FuncDecl%1061797998.body preserve=yes
   return _FuncDecl;
  //## end cFuncRef::FuncDecl%1061797998.body
}

void cFuncRef::SetArg (ULONG_T pos, cArgument *param)
{
  //## begin cFuncRef::SetArg%1040202773.body preserve=yes
   if (pos >= _ParamVec.size()) _ParamVec.resize(pos+1);
   _ParamVec[pos] = param;
  //## end cFuncRef::SetArg%1040202773.body
}

ULONG_T cFuncRef::Args ()
{
  //## begin cFuncRef::Args%1040202774.body preserve=yes
   return _ParamVec.size();
  //## end cFuncRef::Args%1040202774.body
}

void cFuncRef::CallFunc ()
{
  //## begin cFuncRef::CallFunc%1088693728.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   PUSH_PARAMS(stack)
   VOID_CALL(stack)
  //## end cFuncRef::CallFunc%1088693728.body
}

void cFuncRef::CallFunc (LONG_T &value)
{
  //## begin cFuncRef::CallFunc%1088693729.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallFunc%1088693729.body
}

void cFuncRef::CallFunc (ULONG_T &value)
{
  //## begin cFuncRef::CallFunc%1088693730.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallFunc%1088693730.body
}

void cFuncRef::CallFunc (FLOAT_T &value)
{
  //## begin cFuncRef::CallFunc%1088693731.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   PUSH_PARAMS(stack)
   FLOAT_CALL(stack,value)
  //## end cFuncRef::CallFunc%1088693731.body
}

void cFuncRef::CallFunc (DOUBLE_T &value)
{
  //## begin cFuncRef::CallFunc%1088693732.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   PUSH_PARAMS(stack)
   DOUBLE_CALL(stack,value)
  //## end cFuncRef::CallFunc%1088693732.body
}

void cFuncRef::CallFunc (STRING_T &value)
{
  //## begin cFuncRef::CallFunc%1088693733.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   PUSH_PARAMS(stack)
   STRING_CALL(stack,value)
  //## end cFuncRef::CallFunc%1088693733.body
}

void cFuncRef::CallFunc (WSTRING_T &value)
{
  //## begin cFuncRef::CallFunc%1088693734.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   PUSH_PARAMS(stack)
   WSTRING_CALL(stack,value)
  //## end cFuncRef::CallFunc%1088693734.body
}

void cFuncRef::CallFunc (PTR_T &value)
{
  //## begin cFuncRef::CallFunc%1088693735.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   PUSH_PARAMS(stack)
   PTR_CALL(stack,value)
  //## end cFuncRef::CallFunc%1088693735.body
}

void cFuncRef::CallMDLFunc (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693736.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693736.body
}

void cFuncRef::CallMDLFunc (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693737.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693737.body
}

void cFuncRef::CallMDLFunc (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693738.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   FLOAT_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693738.body
}

void cFuncRef::CallMDLFunc (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693739.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   DOUBLE_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693739.body
}

void cFuncRef::CallMDLFunc (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693740.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   STRING_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693740.body
}

void cFuncRef::CallMDLFunc (WSTRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693741.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   WSTRING_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693741.body
}

void cFuncRef::CallMDLFunc (LONG_T &value, LONG_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693742.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,LONG_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693742.body
}

void cFuncRef::CallMDLFunc (ULONG_T &value, ULONG_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693743.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,ULONG_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693743.body
}

void cFuncRef::CallMDLFunc (FLOAT_T &value, FLOAT_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693744.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,FLOAT_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   FLOAT_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693744.body
}

void cFuncRef::CallMDLFunc (DOUBLE_T &value, DOUBLE_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693745.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,DOUBLE_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   DOUBLE_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693745.body
}

void cFuncRef::CallMDLFunc (STRING_T &value, CONST_STRING_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693746.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,CONST_STRING_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   STRING_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693746.body
}

void cFuncRef::CallMDLFunc (WSTRING_T &value, CONST_WSTRING_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693747.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,CONST_WSTRING_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   WSTRING_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693747.body
}

void cFuncRef::CallMDLFunc (PTR_T &value, PTR_T act_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693748.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,PTR_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   PTR_CALL(stack,value)
  //## end cFuncRef::CallMDLFunc%1088693748.body
}

void cFuncRef::CallMDLFunc (PTR_T &value, PTR_T act_value, ULONG_T * size, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cFuncRef::CallMDLFunc%1088693748.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,PTR_T,act_value);
   STACK_PUSH(stack,ULONG_T*,size);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack);
   PTR2_CALL(stack,value,size)
  //## end cFuncRef::CallMDLFunc%1088693748.body
}

void cFuncRef::CallGUIFunc (cAbstractWidget *abstract_widget)
{
  //## begin cFuncRef::CallGUIFunc%1088693749.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   PUSH_PARAMS(stack)
   VOID_CALL(stack)
  //## end cFuncRef::CallGUIFunc%1088693749.body
}

void cFuncRef::CallGUIFunc (LONG_T &value, cAbstractWidget *abstract_widget)
{
  //## begin cFuncRef::CallGUIFunc%1088693750.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693750.body
}

void cFuncRef::CallGUIFunc (ULONG_T &value, cAbstractWidget *abstract_widget)
{
  //## begin cFuncRef::CallGUIFunc%1088693751.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693751.body
}

void cFuncRef::CallGUIFunc (FLOAT_T &value, cAbstractWidget *abstract_widget)
{
  //## begin cFuncRef::CallGUIFunc%1088693752.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   PUSH_PARAMS(stack)
   FLOAT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693752.body
}

void cFuncRef::CallGUIFunc (DOUBLE_T &value, cAbstractWidget *abstract_widget)
{
  //## begin cFuncRef::CallGUIFunc%1088693753.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   PUSH_PARAMS(stack)
   DOUBLE_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693753.body
}

void cFuncRef::CallGUIFunc (STRING_T &value, cAbstractWidget *abstract_widget)
{
  //## begin cFuncRef::CallGUIFunc%1088693754.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   PUSH_PARAMS(stack)
   STRING_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693754.body
}

void cFuncRef::CallGUIFunc (WSTRING_T &value, cAbstractWidget *abstract_widget)
{
  //## begin cFuncRef::CallGUIFunc%1088693755.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   PUSH_PARAMS(stack)
   WSTRING_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693755.body
}

void cFuncRef::CallGUIFunc (PTR_T &value, cAbstractWidget *abstract_widget)
{
  //## begin cFuncRef::CallGUIFunc%1088693756.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   PUSH_PARAMS(stack)
   PTR_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693756.body
}

void cFuncRef::CallGUIFunc (cAbstractWidget *abstract_widget, CONST_STRING_T input)
{
  //## begin cFuncRef::CallGUIFunc%1088693757.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,CONST_STRING_T,input)
   PUSH_PARAMS(stack)
   VOID_CALL(stack)
  //## end cFuncRef::CallGUIFunc%1088693757.body
}

void cFuncRef::CallGUIFunc (LONG_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input)
{
  //## begin cFuncRef::CallGUIFunc%1088693758.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,CONST_STRING_T,input)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693758.body
}

void cFuncRef::CallGUIFunc (ULONG_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input)
{
  //## begin cFuncRef::CallGUIFunc%1088693759.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,CONST_STRING_T,input)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693759.body
}

void cFuncRef::CallGUIFunc (FLOAT_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input)
{
  //## begin cFuncRef::CallGUIFunc%1088693760.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,CONST_STRING_T,input)
   PUSH_PARAMS(stack)
   FLOAT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693760.body
}

void cFuncRef::CallGUIFunc (DOUBLE_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input)
{
  //## begin cFuncRef::CallGUIFunc%1088693761.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,CONST_STRING_T,input)
   PUSH_PARAMS(stack)
   DOUBLE_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693761.body
}

void cFuncRef::CallGUIFunc (STRING_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input)
{
  //## begin cFuncRef::CallGUIFunc%1088693762.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,CONST_STRING_T,input)
   PUSH_PARAMS(stack)
   STRING_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693762.body
}

void cFuncRef::CallGUIFunc (WSTRING_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input)
{
  //## begin cFuncRef::CallGUIFunc%1088693763.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,CONST_STRING_T,input)
   PUSH_PARAMS(stack)
   WSTRING_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693763.body
}

void cFuncRef::CallGUIFunc (PTR_T &value, cAbstractWidget *abstract_widget, CONST_STRING_T input)
{
  //## begin cFuncRef::CallGUIFunc%1088693764.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,CONST_STRING_T,input)
   PUSH_PARAMS(stack)
   PTR_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1088693764.body
}

void cFuncRef::CallGUIFunc (STRING_T &value, cAbstractWidget *abstract_widget, LONG_T index)
{
  //## begin cFuncRef::CallGUIFunc%1089303819.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,LONG_T,index)
   PUSH_PARAMS(stack)
   STRING_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1089303819.body
}

void cFuncRef::CallGUIFunc (ULONG_T &value, cAbstractWidget *abstract_widget, ULONG_T signal, cAbstractWidget *sender)
{
  //## begin cFuncRef::CallGUIFunc%1089304423.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,ULONG_T,signal)
   STACK_PUSH(stack,cAbstractWidget *,sender)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1089304423.body
}

void cFuncRef::CallGUIFunc (ULONG_T &value, cAbstractWidget *abstract_widget, ULONG_T signal)
{
  //## begin cFuncRef::CallGUIFunc%1089316462.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,ULONG_T,signal)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1089316462.body
}

void cFuncRef::CallGUIFunc (LONG_T &new_value, cAbstractWidget *abstract_widget, LONG_T value, ULONG_T flags)
{
  //## begin cFuncRef::CallGUIFunc%1089712048.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,LONG_T,value)
   STACK_PUSH(stack,ULONG_T,flags)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallGUIFunc%1089712048.body
}

void cFuncRef::CallEventFilterFunc (ULONG_T &value, cAbstractWidget *abstract_widget, cTransientObject *object)
{
  //## begin cFuncRef::CallEventFilterFunc%1115740686.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   if (!IS_FREE_FUNCTION(func_class)) {
      {STACK_PUSH(stack,void *,_Context);}
   }
   STACK_PUSH(stack,cAbstractWidget *,abstract_widget)
   STACK_PUSH(stack,cTransientObject *,object)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallEventFilterFunc%1115740686.body
}

void cFuncRef::CallUnitFunc (LONG_T &value, LONG_T act_value, ULONG_T flags, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFuncRef::CallUnitFunc%1109785971.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   STACK_PUSH(stack,void *,_Context);
   STACK_PUSH(stack,LONG_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
  //## end cFuncRef::CallUnitFunc%1109785971.body
}

void cFuncRef::CallUnitFunc (FLOAT_T &value, FLOAT_T act_value, ULONG_T flags, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFuncRef::CallUnitFunc%1109785973.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   STACK_PUSH(stack,void *,_Context);
   STACK_PUSH(stack,FLOAT_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   FLOAT_CALL(stack,value)
  //## end cFuncRef::CallUnitFunc%1109785973.body
}

void cFuncRef::CallUnitFunc (DOUBLE_T &value, DOUBLE_T act_value, ULONG_T flags, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cFuncRef::CallUnitFunc%1109785974.body preserve=yes
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   STACK_PUSH(stack,void *,_Context);
   STACK_PUSH(stack,DOUBLE_T,act_value);
   if (IS_TRANS_FUNCTION(func_class)) {
      {STACK_PUSH(stack,ULONG_T,flags);}
   }
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   DOUBLE_CALL(stack,value)
  //## end cFuncRef::CallUnitFunc%1109785974.body
}

void cFuncRef::CallDevStateFunc (int & value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   SET_FUNC_ADDR
   STACK_T stack = {0};
   STACK_INIT(stack);
   STACK_PUSH(stack,void *,_Context);
   PUSH_INDICES(stack,i1,i2,i3,i4)
   PUSH_PARAMS(stack)
   INT_CALL(stack,value)
}

VOID_FUNC_T cFuncRef::GetFuncAddress (UCHAR_T func_class, CONST_STRING_T func_name)
{
  //## begin cFuncRef::GetFuncAddress%1105976609.body preserve=yes
   if (_GUIFuncFactoryAddress == NULL) {
      _GUIFuncFactoryAddress = cCustomFunctions::GUIFuncFactoryAddress();
   }
   if (_MdlFuncFactoryAddress == NULL) {
      _MdlFuncFactoryAddress = cCustomFunctions::MdlFuncFactoryAddress();
   }
   if (IS_MODEL_FUNCTION(func_class)) {
      if (_MdlFuncFactoryAddress == NULL) {
         return NULL;
      } else {
         return _MdlFuncFactoryAddress(func_class, func_name);
      }
   } else if (IS_GUI_FUNCTION(func_class)) {
      if (_GUIFuncFactoryAddress == NULL) {
         return NULL;
      } else {
         return _GUIFuncFactoryAddress(func_class, func_name);
      }
   } else {
      VOID_FUNC_T ref = NULL;
      if (_MdlFuncFactoryAddress != NULL) {
         ref = _MdlFuncFactoryAddress(func_class, func_name);
      }
      if (ref == NULL) {
         return _GUIFuncFactoryAddress(func_class, func_name);
      } else {
         return ref;
      }
   }
   return NULL;
  //## end cFuncRef::GetFuncAddress%1105976609.body
}

// Additional Declarations
  //## begin cFuncRef%3C7E428400AB.declarations preserve=yes
  //## end cFuncRef%3C7E428400AB.declarations

//## begin module%3C7E428400AB.epilog preserve=yes
//## end module%3C7E428400AB.epilog
