
#ifndef _cstfuncs_h
#define _cstfuncs_h

#include "System/Database/cContext.h"
#include "System/Database/FuncSpecs.h"
#include "cwidgetbase.h"

// meta function classes

#define MODEL_FUNCTIONS    0
#define GUI_FUNCTIONS      1

/// global functions to register function table modules

extern "C" {
extern void RegisterModelFunctionTable(FUNC_ENTRY_T * table, CONST_STRING_T table_name, ULONG_T level);
extern void RegisterGUIFunctionTable(FUNC_ENTRY_T * table, CONST_STRING_T table_name, ULONG_T level);
}

/// class for registering function table modules

class cFunctionTable
{
public:
   cFunctionTable(int meta_class, FUNC_ENTRY_T * table, CONST_STRING_T table_name, ULONG_T level)
   {
      if (meta_class == MODEL_FUNCTIONS) {
         RegisterModelFunctionTable(table, table_name, level);
      } else if (meta_class == GUI_FUNCTIONS) {
         RegisterGUIFunctionTable(table, table_name, level);
      }
   };
   virtual ~cFunctionTable()
   {
   };
};

#define MAX_LEVELS      10
typedef std::map<STRING_T, FUNC_ENTRY_T *> LEVEL_TABLES_T;

/// class for the management of function table modules

class cFunctionTables
{
public:
   cFunctionTables(CONST_STRING_T meta_class)
   {
      _MaxLevel = 0;
      _MetaClass = meta_class;
   };
   virtual ~cFunctionTables()
   {
   };
   void RegisterTable(FUNC_ENTRY_T * table, CONST_STRING_T table_name, ULONG_T level);
   VOID_FUNC_T GetFunctionAddress(UCHAR_T func_class, CONST_STRING_T func_name);
private:
   LEVEL_TABLES_T _FunctionTables[MAX_LEVELS];
   ULONG_T _MaxLevel;
   STRING_T _MetaClass;
};


#endif

