
#ifndef __csymboltable_h___
#define __csymboltable_h___

#include "global_defs.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>

typedef std::map <STRING_T,double> NUMERIC_SYMBOL_TABLE_T;
typedef std::map <STRING_T,STRING_T> STRING_SYMBOL_TABLE_T;

class cSymbolTable
{
public:
   cSymbolTable(const char * name)
   {
      _Name = name;
#ifdef DEBUG_TABLE
FILE * stream = fopen("defs", "a");
if (stream != NULL) {
   fprintf(stream, "%s/%p: created\n", _Name.c_str(), _Name.c_str(), this);
   fclose(stream);
}
#endif
   };
   virtual ~cSymbolTable()
   {
#ifdef DEBUG_TABLE
FILE * stream = fopen("defs", "a");
if (stream != NULL) {
   fprintf(stream, "%s/%p: deleted\n", _Name.c_str(), this);
   fclose(stream);
}
#endif
   };
   inline void Clear()
   {
      _NumericSymbolTable.clear();
#ifdef DEBUG_TABLE
FILE * stream = fopen("defs", "a");
if (stream != NULL) {
   fprintf(stream, "%s/%p: cleared\n", _Name.c_str(), this);
   fclose(stream);
}
#endif
   };
   inline void Define(const char * symbol, double value = 1)
   {
      if (symbol != NULL) {
         _NumericSymbolTable[symbol] = value;
#ifdef DEBUG_TABLE
if (strcmp(symbol, "_MSC_VER") == 0 ||
    strcmp(symbol, "_WIN32") == 0) {
   FILE * stream = fopen("defs", "a");
   if (stream != NULL) {
      fprintf(stream, "%s/%p: define %s=%d\n", _Name.c_str(), this, symbol, (int)value);
      fclose(stream);
   }
}
#endif
      }
   };
   inline void Define(const char * symbol, const char * value)
   {
      if (symbol != NULL) {
         _StringSymbolTable[symbol] = value;
      }
   };
   inline void Undef(const char * symbol)
   {
      if (symbol != NULL) {
         _NumericSymbolTable.erase(symbol);
#ifdef DEBUG_TABLE
if (strcmp(symbol, "_MSC_VER") == 0 ||
    strcmp(symbol, "_WIN32") == 0) {
   FILE * stream = fopen("defs", "a");
   if (stream != NULL) {
      fprintf(stream, "%s/%p: undef %s\n", _Name.c_str(), this, symbol);
      fclose(stream);
   }
}
#endif
      }
   };
   inline bool Defined(const char * symbol)
   {
      if (symbol != NULL) {
         NUMERIC_SYMBOL_TABLE_T::const_iterator i = _NumericSymbolTable.find(symbol);
         if (i == _NumericSymbolTable.end()) {
#ifdef DEBUG_TABLE
if (strcmp(symbol, "_MSC_VER") == 0 ||
    strcmp(symbol, "_WIN32") == 0) {
   FILE * stream = fopen("defs", "a");
   if (stream != NULL) {
      fprintf(stream, "%s/%p: %s undefined\n", _Name.c_str(), this, symbol);
      fclose(stream);
   }
}
#endif
            return false;
         } else {
#ifdef DEBUG_TABLE
if (strcmp(symbol, "_MSC_VER") == 0 ||
    strcmp(symbol, "_WIN32") == 0) {
   FILE * stream = fopen("defs", "a");
   if (stream != NULL) {
      fprintf(stream, "%s/%p: %s defined\n", _Name.c_str(), this, symbol);
      fclose(stream);
   }
}
#endif
            return true;
         }
      } else {
         return false;
      }
   };
   inline double SymbolValue(const char * symbol)
   {
      if (symbol != NULL) {
         NUMERIC_SYMBOL_TABLE_T::const_iterator i = _NumericSymbolTable.find(symbol);
         if (i == _NumericSymbolTable.end()) {
#ifdef DEBUG_TABLE
if (strcmp(symbol, "_MSC_VER") == 0 ||
    strcmp(symbol, "_WIN32") == 0) {
   FILE * stream = fopen("defs", "a");
   if (stream != NULL) {
      fprintf(stream, "%s/%p: %s==%d\n", _Name.c_str(), this, symbol, (int)0);
      fclose(stream);
   }
}
#endif
            return 0;
         } else {
#ifdef DEBUG_TABLE
if (strcmp(symbol, "_MSC_VER") == 0 ||
    strcmp(symbol, "_WIN32") == 0) {
   FILE * stream = fopen("defs", "a");
   if (stream != NULL) {
      fprintf(stream, "%s/%p: %s==%d\n", _Name.c_str(), this, symbol, (int)(*i).second);
      fclose(stream);
   }
}
#endif
            return (*i).second;
         }
      } else {
         return 0;
      }
   };
   inline const char * SymbolString(const char * symbol)
   {
      if (symbol != NULL) {
         STRING_SYMBOL_TABLE_T::const_iterator i = _StringSymbolTable.find(symbol);
         if (i == _StringSymbolTable.end()) {
            return "";
         } else {
            return (*i).second.c_str();
         }
      } else {
         return "";
      }
   };
protected:
   NUMERIC_SYMBOL_TABLE_T _NumericSymbolTable;
   STRING_SYMBOL_TABLE_T _StringSymbolTable;
   STRING_T _Name;
};

#endif
