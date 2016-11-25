
#ifndef __cpp_h_
#define __cpp_h_

#include "csymboltable.h"
#include "cstatestack.h"

bool _ifndef(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _if(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _ifdef(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _elif(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _else(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _endif(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _define(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _undef(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _include(const char * file, int line, const char * text, int & level, cSymbolTable * symbol_table, cStateStack * state_stack);
bool _accept(int level, cStateStack * state_stack);
bool CheckCondition(int & def_level, const char * file, int line, const char * text, bool state,
                    cSymbolTable * symbol_table, cStateStack * state_stack);

#endif

