//## begin module%3E0C47C10368.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0C47C10368.cm

//## begin module%3E0C47C10368.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0C47C10368.cp

//## Module: cStyxParser%3E0C47C10368; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Language\cStyxParser.cpp

//## begin module%3E0C47C10368.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E0C47C10368.additionalIncludes

//## begin module%3E0C47C10368.includes preserve=yes

/// PR 02.04.07 - created new variable definition in ::ParseVarDef
///               when step is 2. Thus previously defined properties
///               are no more inherited.

//## end module%3E0C47C10368.includes

// cVariableValues
#include "System/Database/cVariableValues.h"
// cSHVariant
#include "System/Database/cSHVariant.h"
// cUnitDef
#include "System/Database/cUnitDef.h"
// cProcedureLine
#include "System/PLC/cProcedureLine.h"
// cAtomicCondition
#include "System/PLC/cAtomicCondition.h"
// cControlCondition
#include "System/PLC/cControlCondition.h"
// cControlStartCondition
#include "System/PLC/cControlStartCondition.h"
// cControlProgram
#include "System/PLC/cControlProgram.h"
// cControlState
#include "System/PLC/cControlState.h"
// cStyxParser
#include "Language/cStyxParser.h"
//## begin module%3E0C47C10368.additionalDeclarations preserve=yes

/// PR 24.01.06 - added delayed check for unresolved symbols
/// PR 25.01.06 - now removing mapping, when mapping definition doesnt exist

#define ENABLE_STEPS
#define ENABLE_PREPROCESSING
#define STORE_SPECIFICATIONS

#define PARSE_LINE   0
#define PARSE_COL    0

/// poor mans union of syntax checking

extern "C" {
   extern long _ErrorRow;
   extern long _ErrorColumn;
}

#define ADD_LINE(line,lines) \
{ \
   int size = lines.size(); \
   lines.resize(size + 1); \
   lines[size] = line; \
}

/// delayed checking for unresolved symbols

#define UNRESOLVED_SYMBOL_VALUE  -2
typedef struct _unresolved_symbol {
   cContext * context;
   cVarDef * var_def;
   char symname[0x100];
   int line;
   int col;
   int pos;
}  UNRESOLVED_SYMBOL_T;
typedef std::list<UNRESOLVED_SYMBOL_T*> UNRESOLVED_SYMBOL_LIST_T;
static UNRESOLVED_SYMBOL_LIST_T _UnresolvedSymbols;
static void AddUnresolvedSymbol(cContext * context, cVarDef * var_def, CONST_STRING_T symname, int line, int col, int pos)
{
   UNRESOLVED_SYMBOL_T * ures = (UNRESOLVED_SYMBOL_T *)cSystemUtils::Alloc(sizeof(UNRESOLVED_SYMBOL_T));
   ures->context = context;
   ures->var_def = var_def;
   memcpy(ures->symname, symname, _MIN_(strlen(symname), 0x100-1));
   ures->line = line;
   ures->col = col;
   ures->pos = pos;
   _UnresolvedSymbols.push_back(ures);
}

static BOOL_T CheckUnresolvedSymbols()
{
   BOOL_T unresolved_symbols = false;
   UNRESOLVED_SYMBOL_LIST_T::const_iterator i = _UnresolvedSymbols.cbegin();
   while (i != _UnresolvedSymbols.cend()) {
      UNRESOLVED_SYMBOL_T * ures = (*i);
      if (ures != NULL) {
         cContext * context = ures->context;
         cVarDef * var_def = ures->var_def;
         cVarDef * active_var_def = context->VarDef(var_def->_VarName.c_str());
         if (active_var_def == var_def) {
            cMapping * mapping = var_def->_Mapping;
            if (mapping != NULL) {
               int pos = ures->pos;
               MAP_ITEM_T * map_item = mapping->MapItem(pos);
               if (map_item != NULL) {
                  ULONG_T address = map_item->address;
                  if (address == UNRESOLVED_SYMBOL_VALUE) {
                     unresolved_symbols = true;
                     ErrorPrintf("unresolved symbol %s in variable %s line %d column %d\n",
                                 ures->symname,
                                 var_def->_VarName.c_str(),
                                 ures->line, ures->col);
                  }
               }
            }
         }
      }
      i++;
   }
   _UnresolvedSymbols.clear();
   return unresolved_symbols;
}

//## end module%3E0C47C10368.additionalDeclarations


// Class cStyxParser 

//## begin cStyxParser::StyxMutex%40FCDE7A0280.attr preserve=no  public: static cMutexSem {U} 
cMutexSem cStyxParser::_StyxMutex;
//## end cStyxParser::StyxMutex%40FCDE7A0280.attr







cStyxParser::cStyxParser()
  //## begin cStyxParser::cStyxParser%.hasinit preserve=no
      : _ScanTable(NULL), _ScanStream(NULL), _ParseTable(NULL), _ParseConfig(NULL), _Root(NULL)
  //## end cStyxParser::cStyxParser%.hasinit
  //## begin cStyxParser::cStyxParser%.initialization preserve=yes
  //## end cStyxParser::cStyxParser%.initialization
{
  //## begin cStyxParser::cStyxParser%.body preserve=yes
   _StyxMutex.request();
   MAP_init();
   initSymbols();
   // init language symbols
   Shac_initSymbols();
  //## end cStyxParser::cStyxParser%.body
}

cStyxParser::cStyxParser(const cStyxParser &right)
  //## begin cStyxParser::cStyxParser%copy.hasinit preserve=no
      : _ScanTable(NULL), _ScanStream(NULL), _ParseTable(NULL), _ParseConfig(NULL), _Root(NULL)
  //## end cStyxParser::cStyxParser%copy.hasinit
  //## begin cStyxParser::cStyxParser%copy.initialization preserve=yes
  //## end cStyxParser::cStyxParser%copy.initialization
{
  //## begin cStyxParser::cStyxParser%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cStyxParser::cStyxParser%copy.body
}


cStyxParser::~cStyxParser()
{
  //## begin cStyxParser::~cStyxParser%.body preserve=yes
   // release language symbols
   Shac_quitSymbols();
   // modul termination for hash maps and symbols
   freeSymbols();
   MAP_quit();
//   BUG_CORE;
   _StyxMutex.release();
  //## end cStyxParser::~cStyxParser%.body
}



//## Other Operations (implementation)
BOOL_T cStyxParser::ParseDatabaseFromFile (cContext *context, CONST_STRING_T source, BOOL_T dynamic)
{
  //## begin cStyxParser::ParseDatabaseFromFile%1040992336.body preserve=yes
   _File = source;
   _Line = -1;
   _Column = -1;
   BOOL_T success = true;
   _Dynamic = false;
   ULONG_T errors = 0;
   InitFileParser(source);
   if ((errors = PT_errorCnt()) == 0) {
      try {
         ParseDefList(context, errors);
      } catch (cError & e) {
         ErrorPrintf("%s in %s\n", (const char *)e, _File.c_str());
         success = false;
      } catch (...) {
         ErrorPrintf("unhandled exception while parsing %s\n", _File.c_str());
         success = false;
      }
   }
   ExitParser();
   if (success && errors > 0) {
      _Line = _ErrorRow;
      _Column = _ErrorColumn;
      ErrorPrintf("syntax error in %s(%d,%d)\n", source, _Line, _Column);
      success = false;
   }
   if (_IDEActive) {
      return success;
   } else {
      if (!success || CheckUnresolvedSymbols()) {
         throw cError(PARSE_PARSING_ABORTED, 0);
      }
      return true;
   }
  //## end cStyxParser::ParseDatabaseFromFile%1040992336.body
}

BOOL_T cStyxParser::ParseDatabaseFromString (cContext *context, CONST_STRING_T source, BOOL_T dynamic)
{
  //## begin cStyxParser::ParseDatabaseFromString%1040992340.body preserve=yes
   BOOL_T success = true;
   _Dynamic = false;
   ULONG_T errors = 0;
   InitStringParser(source);
   if ((errors = PT_errorCnt()) == 0) {
      try {
         ULONG_T parseDefListErrors = 0;
         ParseDefList(context, parseDefListErrors);
         if (parseDefListErrors > 0) {
            ErrorPrintf("Errors while parsing def list\n");
            success = false;
         }
      } catch (cError & e) {
         ErrorPrintf("%s in %s\n", (const char *)e, _File.c_str());
         success = false;
      } catch (...) {
         ErrorPrintf("unhandled exception while parsing %s\n", _File.c_str());
         success = false;
      }
   }
   ExitParser();
   if (success && errors > 0) {
      ErrorPrintf("errors occured while parsing %s at row %d column %d\n", _File.c_str(), _ErrorRow, _ErrorColumn);
      success = false;
   }
   if (_IDEActive) {
      return success;
   } else {
      if (!success || CheckUnresolvedSymbols()) {
         throw cError(PARSE_PARSING_ABORTED, 0);
      }
      return true;
   }
  //## end cStyxParser::ParseDatabaseFromString%1040992340.body
}

BOOL_T cStyxParser::ParseDBLiteFromString (cContext *context, CONST_STRING_T source)
{
  //## begin cStyxParser::ParseDBLiteFromString%1102338845.body preserve=yes
   BOOL_T success = true;
   _Dynamic = false;
   ULONG_T errors = 0;
   InitLiteStringParser(source);
   if ((errors = PT_errorCnt()) == 0) {
      try {
         ParseDefList(context, errors);
      } catch (cError & e) {
         ErrorPrintf("%s in %s\n", (const char *)e, _File.c_str());
         success = false;
      } catch (...) {
         ErrorPrintf("unhandled exception while parsing %s\n", _File.c_str());
         success = false;
      }
   }
   ExitParser();
   if (success && errors > 0) {
      ErrorPrintf("errors occured while parsing %s at row %d column %d\n", _File.c_str(), _ErrorRow, _ErrorColumn);
      success = false;
   }
   if (_IDEActive) {
      return success;
   } else {
      if (!success || CheckUnresolvedSymbols()) {
         throw cError(PARSE_PARSING_ABORTED, 0);
      }
      return true;
   }
  //## end cStyxParser::ParseDBLiteFromString%1102338845.body
}

cFuncRef * cStyxParser::FuncRef (cContext *context, CONST_STRING_T source, UCHAR_T requested_data_type, UCHAR_T requested_class)
{
  //## begin cStyxParser::FuncRef%1040992341.body preserve=yes
   if (_Optimized) {
      cFuncRef * func_ref = ParseFuncRefOptimized(context, source,
                                                  requested_data_type, requested_class);
      if (func_ref != NULL) {
#ifdef STORE_SPECIFICATIONS
         func_ref->_Spec = source;
#endif
         return func_ref;
      }
   }
   ULONG_T errors = 0;
   InitLiteStringParser(source);
   cFuncRef * func_ref = NULL;
   try {
      GLS_Lst(ShacDefinition) def_list;
      GLS_Lst(ShacDefinition) def_list_it;
      ShacDefinitions start;  // start nonterminal tree node
      if ((errors = PT_errorCnt()) == 0) {
         GLS_Lst(ShacDefinition) def_list;
         GLS_Lst(ShacDefinition) def_list_it;
         ShacDefinitions start;  // start nonterminal tree node
         _ASSERT_COND(Shacira_Start_Definitions(_Root, &start))
         _ASSERT_COND(ShacDefinitions_defs(start, &def_list))
         _ASSERT_COND(ShacDefinitions_defs(start,&def_list))
         GLS_FORALL(def_list_it, def_list) {
            ShacDefinition sh_definition = GLS_FIRST(ShacDefinition, def_list_it);
            ShacDatabaseDef sh_database_def;
            ShacFuncDecl sh_func_decl;
            ShacVarRef sh_var_ref;
            ShacFuncRef sh_func_ref;
            if (ShacDefinition_dbdef(sh_definition, &sh_database_def)) {
            } else if (ShacDefinition_funcdec(sh_definition, &sh_func_decl)) {
            } else if (ShacDefinition_varref(sh_definition, &sh_var_ref)) {
            } else if (ShacDefinition_funcref(sh_definition, &sh_func_ref)) {
               func_ref = ParseFuncRef(context, (void**)sh_func_ref,
                                       requested_data_type, requested_class);
#ifdef STORE_SPECIFICATIONS
               if (func_ref != NULL) func_ref->_Spec = source;
#endif
            } else {
_ASSERT_UNCOND
            }
         }
      }
   } catch (cError & e) {
      ExitParser();
      throw e;
   } catch (...) {
      throw cError(UNHANDLED_EXCEPTION, 0, "ParseFuncRef", "StyxParser");
   }
   ExitParser();
   if (errors > 0) {
      throw cError(PARSE_SYNTAX_ERRORS_IN_STRING, 0, source,
                   cConvUtils::StringValue(_ErrorRow).c_str(),
                   cConvUtils::StringValue(_ErrorColumn).c_str());
   }
   return func_ref;
  //## end cStyxParser::FuncRef%1040992341.body
}

cVarRef * cStyxParser::VarRef (cContext *context, CONST_STRING_T source, UCHAR_T requested_data_type)
{
  //## begin cStyxParser::VarRef%1040992342.body preserve=yes
   if (_Optimized) {
      cVarRef * var_ref = ParseVarRefOptimized(context, source, requested_data_type);
      if (var_ref != NULL) {
#ifdef STORE_SPECIFICATIONS
         var_ref->_Spec = source;
#endif
         return var_ref;
      }
   }
   ULONG_T errors = 0;
   InitLiteStringParser(source);
   cVarRef * var_ref = NULL;
   try {
      GLS_Lst(ShacDefinition) def_list;
      GLS_Lst(ShacDefinition) def_list_it;
      ShacDefinitions start;  // start nonterminal tree node
      if ((errors = PT_errorCnt()) == 0) {
         GLS_Lst(ShacDefinition) def_list;
         GLS_Lst(ShacDefinition) def_list_it;
         ShacDefinitions start;  // start nonterminal tree node
         _ASSERT_COND(Shacira_Start_Definitions(_Root, &start))
         _ASSERT_COND(ShacDefinitions_defs(start, &def_list))
         _ASSERT_COND(ShacDefinitions_defs(start,&def_list))
         GLS_FORALL(def_list_it, def_list) {
            ShacDefinition sh_definition = GLS_FIRST(ShacDefinition, def_list_it);
            ShacDatabaseDef sh_database_def;
            ShacFuncDecl sh_func_decl;
            ShacVarRef sh_var_ref;
            ShacFuncRef sh_func_ref;
            if (ShacDefinition_dbdef(sh_definition, &sh_database_def)) {
            } else if (ShacDefinition_funcdec(sh_definition, &sh_func_decl)) {
            } else if (ShacDefinition_varref(sh_definition, &sh_var_ref)) {
               var_ref = ParseVarRef(context, (void**)sh_var_ref, UNDEFINED);
#ifdef STORE_SPECIFICATIONS
               if (var_ref != NULL) var_ref->_Spec = source;
#endif
            } else if (ShacDefinition_funcref(sh_definition, &sh_func_ref)) {
            } else {
_ASSERT_UNCOND
            }
         }
      }
   } catch (cError & e) {
      ExitParser();
      throw e;
   } catch (...) {
      throw cError(UNHANDLED_EXCEPTION, 0, "ParseVarRef", "StyxParser");
   }
   ExitParser();
   if (errors > 0) {
      throw cError(PARSE_SYNTAX_ERRORS_IN_STRING, 0, source,
                   cConvUtils::StringValue(_ErrorRow).c_str(),
                   cConvUtils::StringValue(_ErrorColumn).c_str());
   }
   return var_ref;
  //## end cStyxParser::VarRef%1040992342.body
}

void cStyxParser::ParseProgramFromFile (cContext *context, CONST_STRING_T source, BOOL_T dynamic)
{
  //## begin cStyxParser::ParseProgramFromFile%1060622593.body preserve=yes
   _Dynamic = dynamic;
   ULONG_T errors = 0;
   InitFileParser(source);
   if ((errors = PT_errorCnt()) == 0) {
      try {
         ParseDefList(context, errors);
      } catch (cError & e) {
         _Dynamic = false;
         ExitParser();
         throw e;
      } catch (...) {
         _Dynamic = false;
         throw cError(UNHANDLED_EXCEPTION, 0, "ParseProgramFromFile", "StyxParser");
      }
   }
   _Dynamic = false;
   ExitParser();
   if (errors > 0) {
      throw cError(PARSE_SYNTAX_ERRORS_IN_FILE, 0, source,
                   cConvUtils::StringValue(_ErrorRow).c_str(),
                   cConvUtils::StringValue(_ErrorColumn).c_str());
   }
   context->CreateDynamic();
  //## end cStyxParser::ParseProgramFromFile%1060622593.body
}

void cStyxParser::ParseProgramFromString (cContext *context, CONST_STRING_T source, BOOL_T dynamic)
{
  //## begin cStyxParser::ParseProgramFromString%1060622594.body preserve=yes
   _Dynamic = dynamic;
   ULONG_T errors = 0;
   InitStringParser(source);
   if ((errors = PT_errorCnt()) == 0) {
      try {
         ParseDefList(context, errors);
      } catch (cError & e) {
         _Dynamic = false;
         ExitParser();
         throw e;
      } catch (...) {
         _Dynamic = false;
         throw cError(UNHANDLED_EXCEPTION, 0, "ParseProgramFromString", "StyxParser");
      }
   }
   ExitParser();
   _Dynamic = false;
   if (errors > 0) {
      throw cError(PARSE_SYNTAX_ERRORS_IN_FILE, 0, "Context Definition File",
                   cConvUtils::StringValue(_ErrorRow).c_str(),
                   cConvUtils::StringValue(_ErrorColumn).c_str());
   }
   context->CreateDynamic();
  //## end cStyxParser::ParseProgramFromString%1060622594.body
}

void cStyxParser::InitFileParser (CONST_STRING_T parse_file)
{
  //## begin cStyxParser::InitFileParser%1040992346.body preserve=yes
   _File = parse_file;
   Scn_get_Shacira(&_ScanTable);          // create scan table
   _ParseTable = PLR_get_Shacira();       // create parse table
   _ScanStream = Stream_file(_ScanTable, "", (char *)parse_file, ""); // create scanner from string
#ifdef ENABLE_PREPROCESSING
   MAP(long,symbol) pPreParMap;
   pPreParMap = MAP_newPrimMap();
   MAP_dfndom(pPreParMap, SPP_INC_PATH, stringToSymbol("."));
   SPP_init(pPreParMap);
   Stream_premac_set(_ScanStream, SPP_premac);
#endif
   _ParseConfig = PT_init(_ParseTable, _ScanStream); // create parse configuration
   _Root = PT_INTERPRETE(_ParseConfig, "");     // parse from first start nonterminal
   PT_setErrorCnt(PT_synErrorCnt(_ParseConfig));
#ifdef ENABLE_PREPROCESSING
   SPP_quit();
#endif
  //## end cStyxParser::InitFileParser%1040992346.body
}

void cStyxParser::InitStringParser (CONST_STRING_T parse_string)
{
  //## begin cStyxParser::InitStringParser%1040992347.body preserve=yes
   Scn_get_Shacira(&_ScanTable);          // create scan table
   _ParseTable = PLR_get_Shacira();       // create parse table
   _ScanStream = Stream_string(_ScanTable, (char*)parse_string); // create scanner from string
#ifdef ENABLE_PREPROCESSING
   MAP(long,symbol) pPreParMap;
   pPreParMap = MAP_newPrimMap();
   MAP_dfndom(pPreParMap, SPP_INC_PATH, stringToSymbol("."));
   SPP_init(pPreParMap);
   Stream_premac_set(_ScanStream, SPP_premac);
#endif
   _ParseConfig = PT_init(_ParseTable, _ScanStream); // create parse configuration
   _Root = PT_INTERPRETE(_ParseConfig, "");     // parse from first start nonterminal
   PT_setErrorCnt(PT_synErrorCnt(_ParseConfig));
#ifdef ENABLE_PREPROCESSING
   SPP_quit();
#endif
  //## end cStyxParser::InitStringParser%1040992347.body
}

void cStyxParser::InitLiteStringParser (CONST_STRING_T parse_string)
{
  //## begin cStyxParser::InitLiteStringParser%1093971309.body preserve=yes
   Scn_get_Shacira(&_ScanTable);          // create scan table
   _ParseTable = PLR_get_Shacira();       // create parse table
   _ScanStream = Stream_string(_ScanTable, (char*)parse_string); // create scanner from string
   _ParseConfig = PT_init(_ParseTable, _ScanStream); // create parse configuration
   _Root = PT_INTERPRETE(_ParseConfig, "");     // parse from first start nonterminal
   PT_setErrorCnt(PT_synErrorCnt(_ParseConfig));
  //## end cStyxParser::InitLiteStringParser%1093971309.body
}

void cStyxParser::ExitParser ()
{
  //## begin cStyxParser::ExitParser%1040992348.body preserve=yes
   if (_Root != NULL ) PT_delT(_Root);    // release derivation tree
   if (_ParseConfig != NULL) PT_quit(_ParseConfig);           // release parse configuration
   if (_ScanStream != NULL) {
      Stream_close(_ScanStream);          // close scan stream
      Stream_free(_ScanStream);           // release scan stream
   }
   if (_ScanTable != NULL) Scn_free(_ScanTable);               // release scan table
   if (_ParseTable != NULL) PLR_delTab(_ParseTable);            // release parse table
  //## end cStyxParser::ExitParser%1040992348.body
}

void cStyxParser::ParseDefList (cContext *context, ULONG_T &parsDefErrors)
{
  //## begin cStyxParser::ParseDefList%1040992343.body preserve=yes
#ifdef ENABLE_STEPS
   if (_Steps > 0) {
      int errors = 0;
      for (_Step=1; _Step<=_Steps && !errors; _Step++) {
         GLS_Lst(ShacDefinition) def_list;
         GLS_Lst(ShacDefinition) def_list_it;
         ShacDefinitions start;  // start nonterminal tree node
         _ASSERT_COND(Shacira_Start_Definitions(_Root, &start))
         if (!ShacDefinitions_defs(start, &def_list)) {
            // empty
            return;
         }
         _ASSERT_COND(ShacDefinitions_defs(start,&def_list))
         GLS_FORALL(def_list_it, def_list) {
            ShacDefinition sh_definition = GLS_FIRST(ShacDefinition, def_list_it);
            ParseDefinition(context, (void**)sh_definition, parsDefErrors);
         }
         errors = PT_errorCnt();
      }
      return;
   }
#endif
   GLS_Lst(ShacDefinition) def_list;
   GLS_Lst(ShacDefinition) def_list_it;
   ShacDefinitions start;  // start nonterminal tree node
   _ASSERT_COND(Shacira_Start_Definitions(_Root, &start))
   if (!ShacDefinitions_defs(start, &def_list)) {
      // empty
      return;
   }
   _ASSERT_COND(ShacDefinitions_defs(start,&def_list))
   GLS_FORALL(def_list_it, def_list) {
      ShacDefinition sh_definition = GLS_FIRST(ShacDefinition, def_list_it);
      ParseDefinition(context, (void**)sh_definition, parsDefErrors);
   }
  //## end cStyxParser::ParseDefList%1040992343.body
}

void cStyxParser::ParseDefinition (cContext *context, ShacDefinition *sh_definition, ULONG_T &parseVarDefErrors)
{
  //## begin cStyxParser::ParseDefinition%1040992350.body preserve=yes
   ShacDynamicDecls sh_dyndecls_def;
   ShacDatabaseDef sh_database_def;
   ShacFuncDecl sh_func_decl;
   ShacVarRef sh_var_ref;
   ShacVarDef sh_var_def;
   ShacUnitDef sh_unit_def;
   ShacFuncRef sh_func_ref;
   ShacState sh_state;
   ShacProgram sh_program;
   ShacProcedure sh_procedure;
   ShacStartCondition sh_start_condition;
   if (ShacDefinition_dyndec(sh_definition, &sh_dyndecls_def)) {
      GLS_Lst(GLS_Tok) ide_list;
      if (ShacDynamicDecls_def(sh_dyndecls_def, &ide_list)) {
         GLS_Lst(GLS_Tok) ide_list_it;
         GLS_FORALL(ide_list_it, ide_list) {
            GLS_Tok sh_var_name = GLS_FIRST(GLS_Tok, ide_list_it);
            STRING_T var_name = (const char *)GLS_Tok_string(sh_var_name);
            _DynamicVars[var_name.c_str()] = var_name;
         }
      }
   } else if (ShacDefinition_dbdef(sh_definition, &sh_database_def)) {
      if (!_IgnoreDataDefinitions) {
         ParseDatabaseDef(context, (void**)sh_database_def, parseVarDefErrors);
      }
   } else if (ShacDefinition_funcdec(sh_definition, &sh_func_decl)) {
      cFuncDecl * func_decl = ParseFuncDecl(context, (void**)sh_func_decl);
      if (func_decl != NULL) {
         context->AddFuncDecl(func_decl->_FuncName.c_str(), func_decl);
      }
   } else if (ShacDefinition_varref(sh_definition, &sh_var_ref)) {
      cVarRef * var_ref = ParseVarRef(context, (void**)sh_var_ref);
   } else if (ShacDefinition_funcref(sh_definition, &sh_func_ref)) {
      cFuncRef * func_ref = ParseFuncRef(context, (void**)sh_func_ref);
   } else if (ShacDefinition_state(sh_definition, &sh_state)) {
      cControlState * state = ParseState(context, (void**)sh_state);
      if (state != NULL) context->AddControlState(state->_StateName.c_str(), state);
   } else if (ShacDefinition_prog(sh_definition, &sh_program)) {
      cControlProgram * program = ParseProgram(context, (void**)sh_program);
      if (program != NULL) context->AddControlProgram(program->Name().c_str(), program);
   } else if (ShacDefinition_proc(sh_definition, &sh_procedure)) {
      cControlProcedure * procedure = ParseProcedure(context, (void**)sh_procedure);
      if (procedure != NULL) context->AddControlProcedure(procedure->Name().c_str(), procedure);
   } else if (ShacDefinition_cond(sh_definition, &sh_start_condition)) {
      cControlStartCondition * start_condition = ParseStartCondition(context, (void**)sh_start_condition);
      if (start_condition != NULL) context->AddControlStartCondition(start_condition->_ConditionName.c_str(), start_condition);
   } else if (ShacDefinition_vardef(sh_definition, &sh_var_def)) {
      cVarDef * var_def = ParseVarDef(context, (void**)sh_var_def, _ActDatabaseName.c_str(), _ActDeviceName.c_str(), parseVarDefErrors);
      if (var_def != NULL) {
         context->AddVarDef(var_def->_VarName.c_str(), var_def); 
      }
   } else if (ShacDefinition_unitdef(sh_definition, &sh_unit_def)) {
      cUnitDef * unit_def = ParseUnitDef(context, (void**)sh_unit_def);
      if (unit_def != NULL) {
         context->AddUnitDef(unit_def->_UnitName.c_str(), unit_def); 
      }
   } else {
_ASSERT_UNCOND
   }
  //## end cStyxParser::ParseDefinition%1040992350.body
}

void cStyxParser::ParseDatabaseDef (cContext *context, ShacDatabaseDef *sh_database_def, ULONG_T &parseVarDefErrors)
{
  //## begin cStyxParser::ParseDatabaseDef%1040992351.body preserve=yes
   GLS_Tok sh_db_name;
   ShacDeviceSpec sh_device_spec;
   GLS_Lst(ShacVarDef) var_def_list;
   GLS_Lst(ShacVarDef) var_def_list_it;
   if (ShacDatabaseDef_def(sh_database_def, &sh_db_name, &sh_device_spec, &var_def_list)) {
      STRING_T database_name = (const char *)GLS_Tok_string(sh_db_name);
      _ActDatabaseName = database_name;
      ParseDeviceSpec(context, (void**)sh_device_spec);
      GLS_FORALL(var_def_list_it, var_def_list) {
         ShacVarDef sh_var_def = GLS_FIRST(ShacVarDef, var_def_list_it);
         cVarDef * var_def = ParseVarDef(context, (void**)sh_var_def, _ActDatabaseName.c_str(), _ActDeviceName.c_str(), parseVarDefErrors);
         if (var_def != NULL) {
            context->AddVarDef(var_def->_VarName.c_str(), var_def); 
         }
      }
   } else {
      _ActDatabaseName = "";
   }
  //## end cStyxParser::ParseDatabaseDef%1040992351.body
}

cFuncDecl * cStyxParser::ParseFuncDecl (cContext *context, ShacFuncDecl *sh_func_decl)
{
  //## begin cStyxParser::ParseFuncDecl%1040992352.body preserve=yes
   GLS_Tok sh_func_name;
   STRING_T func_name;
   GLS_Tok sh_param_name;
   STRING_T param_name;
   cFuncDecl * func_decl = NULL;
   ShacBaseType sh_base_type;
   ShacStringType sh_string_type;
   GLS_Lst(ShacArgDecl) arg_decl_list;
   GLS_Lst(ShacArgDecl) arg_decl_list_it;
   if (ShacFuncDecl_free1(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_FREE);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_free2(sh_func_decl, &sh_string_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), StringType((void**)sh_string_type), SH_FREE);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_emb1(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_EMBED);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_emb2(sh_func_decl, &sh_string_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), StringType((void**)sh_string_type), SH_EMBED);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_conv1(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_CONVERSION);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_conv2(sh_func_decl, &sh_string_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), StringType((void**)sh_string_type), SH_CONVERSION);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_filt1(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_FILTER);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_filt2(sh_func_decl, &sh_string_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), StringType((void**)sh_string_type), SH_FILTER);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_acc1(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_ACCESS);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_acc2(sh_func_decl, &sh_string_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), StringType((void**)sh_string_type), SH_ACCESS);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_lim1(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_LIMIT);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_lim2(sh_func_decl, &sh_string_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), StringType((void**)sh_string_type), SH_LIMIT);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_view1(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_VIEW);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_view2(sh_func_decl, &sh_string_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), StringType((void**)sh_string_type), SH_VIEW);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_dark(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_ULONG, SH_DARK);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_plaus(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_ULONG, SH_PLAUS);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_user(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_ULONG, SH_USER);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_btn(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_ULONG, SH_BUTTON);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_sigflt(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_ULONG, SH_SIG_FILTER);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_slot(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_ULONG, SH_SLOT);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_valf(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_LONG, SH_VALUE);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_unit(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_UNIT);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_evflt(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_ULONG, SH_EVENT_FILTER);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShacFuncDecl_init(sh_func_decl, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), SH_ULONG, SH_WINIT);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else if (ShaciraFuncDecl_devst(sh_func_decl, &sh_base_type, &sh_func_name, &arg_decl_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      func_decl = new cFuncDecl(func_name.c_str(), BaseType((void**)sh_base_type), SH_DEVICE_STATE);
      GLS_FORALL(arg_decl_list_it, arg_decl_list) {
         ShacArgDecl sh_arg_decl = GLS_FIRST(ShacArgDecl, arg_decl_list_it);
         ShacBaseType sh_base_param_type;
         ShacStringType sh_string_param_type;
         if (ShacArgDecl_argdec1(sh_arg_decl, &sh_base_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(BaseType((void**)sh_base_param_type), param_name.c_str());
         } else if (ShacArgDecl_argdec2(sh_arg_decl, &sh_string_param_type, &sh_param_name)) {
            param_name = (const char *)GLS_Tok_string(sh_param_name);
            func_decl->AddParam(StringType((void**)sh_string_param_type), param_name.c_str());
         }
      }
   } else {
_ASSERT_UNCOND
   }
   return func_decl;
  //## end cStyxParser::ParseFuncDecl%1040992352.body
}

cFuncRef * cStyxParser::ParseFuncRef (cContext *context, ShacFuncRef *sh_func_ref, UCHAR_T requested_data_type, UCHAR_T requested_class)
{
  //## begin cStyxParser::ParseFuncRef%1040992353.body preserve=yes
#ifdef ENABLE_STEPS
   if (_Steps > 0) {
      if (_Step == 1) {
         return NULL;
      }
   }
#endif
   cFuncRef * func_ref = NULL;
   STRING_T func_name;
   GLS_Tok sh_func_name;
   GLS_Lst(ShacArgument) argument_list;
   GLS_Lst(ShacArgument) argument_list_it;
   if (ShacFuncRef_ref(sh_func_ref, &sh_func_name, &argument_list)) {
      func_name = (const char *)GLS_Tok_string(sh_func_name);
      cFuncDecl * func_decl = context->FuncDecl(func_name.c_str());
      if (func_decl == NULL) {
         ParseError(PARSE_FUNCREF_NOT_DECLARED, (void**)sh_func_name);
      } else {
         func_ref = new cFuncRef(func_decl, context);
         ULONG_T params = func_decl->Params();
         if (CheckTypes(requested_data_type, func_decl->_DataType, (void**)sh_func_name) &&
             CheckClass(requested_class, func_decl->FuncClass(), (void**)sh_func_name)) { 
            INT_T param_pos = 0;
            GLS_FORALL(argument_list_it, argument_list) {
               if (param_pos >= params) {
                  ParseError(PARSE_FUNCREF_TOO_MUCH_PARAMS, (void**)sh_func_name);
               } else {
                  ShacArgument argument = GLS_FIRST(ShacArgument, argument_list_it);
                  cArgument * arg = ParseArgument(context, (void**)argument, func_decl->ParamType(param_pos));
                  if (func_ref != NULL && arg != NULL) {
                     func_ref->SetArg(param_pos, arg);
                  }
               }
               param_pos++;
            }
            if (!(params == 0 && param_pos == 0)) {
               if (param_pos < params) {
                  ParseError(PARSE_FUNCREF_TOO_FEW_PARAMS, (void**)sh_func_name);
                  delete func_ref;
                  func_ref = NULL;
               }
            }
         }
      }
   }
   return func_ref;
  //## end cStyxParser::ParseFuncRef%1040992353.body
}

cVarRef * cStyxParser::ParseVarRef (cContext *context, ShacVarRef *sh_var_ref, UCHAR_T requested_data_type)
{
  //## begin cStyxParser::ParseVarRef%1040992354.body preserve=yes
#ifdef ENABLE_STEPS
   if (_Steps > 0) {
      if (_Step == 1) {
         return NULL;
      }
   }
#endif
   cVarRef * var_ref = NULL;
   STRING_T var_name;
   GLS_Tok sh_var_name;
   GLS_Lst(ShacIndexRef) index_ref_list;
   GLS_Lst(ShacIndexRef) index_ref_list_it;
   if (ShacVarRef_ref(sh_var_ref, &sh_var_name, &index_ref_list)) {
      var_name = (const char *)GLS_Tok_string(sh_var_name);
      cVarDef * var_def = context->VarDef(var_name.c_str());
      if (var_def == NULL) {
#ifdef ENABLE_STEPS
            if (_Step == 2) {
               if (_IDEActive) {
                  if (!IsDynamic((const char *)GLS_Tok_string(sh_var_name))) {
                     ParseError(PARSE_VARREF_NOT_DECLARED, (void**)sh_var_name);
                  }
               } else {
                  ParseError(PARSE_VARREF_NOT_DECLARED, (void**)sh_var_name);
               }
            } else if (_Step == 0) {
               ParseError(PARSE_VARREF_NOT_DECLARED, (void**)sh_var_name);
            }
#else
         if (_IDEActive) {
            return NULL;
         } else {
            ParseError(PARSE_VARREF_NOT_DECLARED, (void**)sh_var_name);
         }
#endif
      } else {
         var_ref = new cVarRef(var_def, context);
         ULONG_T indices = var_def->Dims();
         INT_T data_type_code = var_def->_DataType;
         if (CheckTypes(requested_data_type, data_type_code, (void**)sh_var_name)) {
            INT_T index_pos = 0;
            GLS_FORALL(index_ref_list_it, index_ref_list) {
               if (index_pos >= indices) {
                  ParseError(PARSE_VARREF_TOO_MUCH_INDICES, (void**)sh_var_name);
                  delete var_ref;
                  var_ref = NULL;
               } else {
                  ShacIndexRef index_ref = GLS_FIRST(ShacIndexRef, index_ref_list_it);
                  cArgument * arg = NULL;
                  GLS_Tok sh_nat_value;
                  GLS_Tok sh_hex_value;
                  ShacFuncRef sh_func_ref;
                  ShacVarRef sh_var_ref2;
                  if (ShacIndexRef_cnat(index_ref, &sh_nat_value)) {
                     ULONG_T index = NatValue(&sh_nat_value);
                     if (index >= var_def->DimSize(index_pos)) {
                        ParseError(PARSE_VARREF_INVALID_INDEX, (void**)sh_var_name,
                                   cConvUtils::StringValue(index_pos).c_str());
                        delete var_ref;
                        var_ref = NULL;
                     } else {
                        arg = new cConstInt(index);
                     }
                  } else if (ShacIndexRef_chex(index_ref, &sh_hex_value)) {
                     ULONG_T index = HexValue(&sh_nat_value);
                     if (index >= var_def->DimSize(index_pos)) {
                        ParseError(PARSE_VARREF_INVALID_INDEX, (void**)sh_var_name,
                                   cConvUtils::StringValue(index_pos).c_str());
                        delete var_ref;
                        var_ref = NULL;
                     } else {
                        arg = new cConstInt(index);
                     }
                  } else if (ShacIndexRef_func(index_ref, &sh_func_ref)) {
                     cFuncRef * func_ref = ParseFuncRef(context, (void**)sh_func_ref, SH_ULONG);
                     if (func_ref != NULL) {
                        arg = new cFuncRefArg(func_ref);
                     } else {
                        delete var_ref;
                        var_ref = NULL;
                     }
                  } else if (ShacIndexRef_var(index_ref, &sh_var_ref2)) {
                     cVarRef * var_ref2 = ParseVarRef(context, (void**)sh_var_ref2, SH_ULONG);
                     if (var_ref2 != NULL) {
                        arg = new cVarRefArg(var_ref2);
                     } else {
                        delete var_ref;
                        var_ref = NULL;
                     }
                  } else {
                     ParseError(PARSE_VARREF_NO_INDEX, (void**)sh_var_name,
                                cConvUtils::StringValue(index_pos).c_str());
                     delete var_ref;
                     var_ref = NULL;
                  }
                  if (var_ref != NULL && arg != NULL) {
                     var_ref->SetIndex(index_pos, arg);
                  }
               }
               index_pos++;
            }
            if (!(indices == 0 && index_pos == 0)) {
               if (index_pos < indices) {
                  ParseError(PARSE_VARREF_TOO_FEW_INDICES, (void**)sh_var_name);
                  delete var_ref;
                  var_ref = NULL;
               }
            }
         }
      }
   }
   return var_ref;
  //## end cStyxParser::ParseVarRef%1040992354.body
}

cVarDef * cStyxParser::ParseVarDef (cContext *context, ShacVarDef *sh_var_def, CONST_STRING_T database_name, CONST_STRING_T device_name, ULONG_T &parseMapErrors)
{
  //## begin cStyxParser::ParseVarDef%1040992372.body preserve=yes
   STRING_T var_name;
   cVarDef * var_def = NULL;
   GLS_Tok sh_var_name;
   GLS_Lst(ShacDimSpec) dim_spec_list;
   GLS_Lst(ShacDimSpec) dim_spec_list_it;
   ShacDataTypeSpec sh_data_type_spec;
   ShacVarSpecSeq sh_var_spec_seq;
   ShacMapDef sh_map_def;
   if (ShacVarDef_def(sh_var_def, &sh_var_name, &dim_spec_list, &sh_data_type_spec, &sh_var_spec_seq, &sh_map_def)) {
      var_name = (const char *)GLS_Tok_string(sh_var_name);
      ShacDescription sh_description;
      ShacText sh_text;
      ShacDim1 sh_dim1_text;
      ShacDim2 sh_dim2_text;
      ShacDim3 sh_dim3_text;
      ShacDim4 sh_dim4_text;
      ShacFlags sh_flags;
      ShacSystemFlags sh_system_flags;
      ShacVarTypeSpec sh_var_type_spec;
      ShacUnitRef sh_unit_ref;
      ShacPersistence sh_persistence;
      ShacFile sh_file;
      ShacFilterFunc sh_filter_func;
      ShacAccessFunc sh_access_func;
      ShacMinSpec sh_min_spec;
      ShacMaxSpec sh_max_spec;
      ShaciraOption sh_option;
      ShacValueSpec sh_value_spec;
      ShacFuncRef sh_access_func_ref;
      ShacFuncRef sh_filter_func_ref;
      ShacBaseType sh_base_type;
      ShacStringType sh_string_type;
      GLS_Tok sh_nat_value;
      UCHAR_T data_type = UNDEFINED;
      ULONG_T length = 1;
      UCHAR_T precision = 0;
      ParseDataTypeSpec((void**)sh_data_type_spec, data_type, length, precision);
#ifdef ENABLE_STEPS
      var_def = context->VarDef(var_name.c_str());
      if (var_def == NULL) {
         var_def = new cVarDef(var_name.c_str(), data_type, length, precision, _Dynamic);
      } else {
         if (_Step == 1) {
            ParseWarning(PARSE_VARREF_ALREADY_DECLARED,
                         Line((void**)sh_var_def), Column((void**)sh_var_def),
                         var_def->_VarName.c_str());
            var_def = new cVarDef(var_name.c_str(), data_type, length, precision, _Dynamic);
            context->UpdateUi();
         } else if (_Step == 2) {
            var_def = new cVarDef(var_name.c_str(), data_type, length, precision, _Dynamic);
         }
      }
#else
      var_def = new cVarDef(var_name.c_str(), data_type, length, precision, _Dynamic);
#endif
      if (database_name != NULL) {
         var_def->_DatabaseName = STRING_T(database_name);
      }
      if (device_name != NULL) {
         var_def->_DeviceName = STRING_T(device_name);
      }
      var_def->_Context = context;
      ULONG_T dim = 0;
      GLS_FORALL(dim_spec_list_it, dim_spec_list) {
         ShacDimSpec dim_spec = GLS_FIRST(ShacDimSpec, dim_spec_list_it);
         if (ShacDimSpec_dimspec(dim_spec, &sh_nat_value)) {
            var_def->AddDim(dim, NatValue(&sh_nat_value));
         }
         dim++;
      }
      if (ShacVarSpecSeq_specs(sh_var_spec_seq,
                               &sh_var_type_spec,
                               &sh_system_flags,
                               &sh_unit_ref,
                               &sh_description,
                               &sh_text,
                               &sh_dim1_text,
                               &sh_dim2_text,
                               &sh_dim3_text,
                               &sh_dim4_text,
                               &sh_flags,
                               &sh_persistence,
                               &sh_file,
                               &sh_filter_func,
                               &sh_access_func,
                               &sh_min_spec,
                               &sh_max_spec,
                               &sh_value_spec,
                               &sh_option)) {
         ParseDescription(context, (void**)sh_description, var_def);
         ParseSystemFlags(context, (void**)sh_system_flags, var_def);
         ParseFlags(context, (void**)sh_flags, var_def);
         ParseOption(context, (void**)sh_option, var_def);
         ParseText(context, (void**)sh_text, var_def);
         ParseDim1Text(context, (void**)sh_dim1_text, var_def);
         ParseDim2Text(context, (void**)sh_dim2_text, var_def);
         ParseDim3Text(context, (void**)sh_dim3_text, var_def);
         ParseDim4Text(context, (void**)sh_dim4_text, var_def);
         ParseVarType(context, (void**)sh_var_type_spec, var_def);
         ParsePersistence(context, (void**)sh_persistence, var_def);
         ParseFile(context, (void**)sh_file, var_def);
         ParseValueSpec(context, (void**)sh_value_spec, var_def);
         ParseUnitRef(context, (void**)sh_unit_ref, var_def);
         if (ShacFilterFunc_ref(sh_filter_func, &sh_filter_func_ref)) {
            cFuncRef * func_ref = ParseFuncRef(context, (void**)sh_filter_func_ref, UNDEFINED, SH_FILTER);
            var_def->SetFilter(func_ref);
         }
         if (ShacAccessFunc_ref(sh_access_func, &sh_access_func_ref)) {
            cFuncRef * func_ref = ParseFuncRef(context, (void**)sh_access_func_ref, UNDEFINED, SH_ACCESS);
            var_def->SetAccess(func_ref);
         }
         ShacArgument sh_min_arg;
         if (ShacMinSpec_spec(sh_min_spec, &sh_min_arg)) {
            cArgument * min_arg = ParseArgument(context, (void**)sh_min_arg, data_type);
            var_def->SetMinSpec(min_arg);
         }
         ShacArgument sh_max_arg;
         if (ShacMaxSpec_spec(sh_max_spec, &sh_max_arg)) {
            cArgument * max_arg = ParseArgument(context, (void**)sh_max_arg, data_type);
            var_def->SetMaxSpec(max_arg);
         }
      }
      if (var_def != NULL) {
         cMapping * mapping = ParseMapDef(context, (void**)sh_map_def, var_def, parseMapErrors);
         if (mapping != NULL) {
            var_def->SetMapping(mapping);
         } else {
            var_def->SetMapping(NULL);
         }
      }
   }
   return var_def;
  //## end cStyxParser::ParseVarDef%1040992372.body
}

cMapping * cStyxParser::ParseMapDef (cContext *context, ShacMapDef *sh_map_def, cVarDef *var_def, ULONG_T &parseItemSpecErrors)
{
  //## begin cStyxParser::ParseMapDef%1041236869.body preserve=yes
   if (context->IsRemote()) return NULL;
   INT_T data_type = var_def->_DataType;
   cMapping * mapping = NULL;
   ShacMapTypeSpec sh_map_type_spec;
   ShacItemSpec sh_item_spec;
   ShacRefresh sh_refresh;
   ShacConvFunc sh_conv_func;
   ShacFuncRef sh_func_ref;
   GLS_Lst(ShacItemSpec) item_spec_list;
   GLS_Tok sh_phys_spec;
   if (ShacMapDef_map1(sh_map_def, &sh_phys_spec, &sh_map_type_spec, &sh_item_spec,
                       &sh_refresh, &sh_conv_func)) {
      ParseRefresh(context, (void**)sh_refresh, var_def);
      UCHAR_T data_type = UNDEFINED;
      ULONG_T length = 1;
      UCHAR_T precision = 0;
      ParseMapTypeSpec((void**)sh_map_type_spec, data_type, length, precision);
      mapping = new cMapping(var_def->Elements());
      mapping->_PhysSpec = (const char *)GLS_Tok_string(sh_phys_spec);
      mapping->_DataType = data_type;
      mapping->_Length = length;
      mapping->_Precision = precision;
      if (var_def->Dims() > 0) {
         ParseItemSpecArray(context, mapping, (void**)sh_item_spec, var_def);
      } else {
         MAP_ITEM_T * map_item = ParseItemSpec(context, (void**)sh_item_spec, var_def, 0);
         map_item->buf_spec = mapping->_PhysSpec.c_str();
         map_item->data_type = mapping->_DataType;
         map_item->size = mapping->_Length * cSHVariant::TypeSize(map_item->data_type);
         map_item->var_def = var_def;
         mapping->SetItem(0, map_item);
      }
   } else if (ShacMapDef_map2(sh_map_def, &sh_phys_spec, &sh_map_type_spec, &item_spec_list,
                              &sh_refresh, &sh_conv_func)) {
      ParseRefresh(context, (void**)sh_refresh, var_def);
      UCHAR_T data_type = UNDEFINED;
      ULONG_T length = 1;
      UCHAR_T precision = 0;
      ParseMapTypeSpec((void**)sh_map_type_spec, data_type, length, precision);
      mapping = new cMapping(var_def->Elements());
      mapping->_PhysSpec = (const char *)GLS_Tok_string(sh_phys_spec);
      mapping->_DataType = data_type;
      mapping->_Length = length;
      mapping->_Precision = precision;
      ParseItemSpecList(context, mapping, sh_map_def, var_def, parseItemSpecErrors);
   } else if (ShacMapDef_nul(sh_map_def)) {
      // nix
      return NULL;
   } else {
_ASSERT_UNCOND
   }
   if (mapping != NULL) {
      cFuncRef * conv = NULL;
      if (ShacConvFunc_conv(sh_conv_func, &sh_func_ref)) {
         conv = ParseFuncRef(context, (void**)sh_func_ref, UNDEFINED, SH_CONVERSION);
         mapping->SetConvFunc(conv);
      }
   }
   return mapping;
  //## end cStyxParser::ParseMapDef%1041236869.body
}

MAP_ITEM_T * cStyxParser::ParseItemSpec (cContext *context, ShacItemSpec *sh_item_spec, cVarDef *var_def, int pos)
{
  //## begin cStyxParser::ParseItemSpec%1041236881.body preserve=yes
   MAP_ITEM_T * map_item = NewMapItem();
   map_item->device_name = CopyName(var_def->_DeviceName);
   ShacItemSpecifier sh_item_specifier;   
   GLS_Tok sh_lower_bit;
   GLS_Tok sh_upper_bit;
   if (ShacItemSpec_spec1(sh_item_spec, &sh_item_specifier)) {
   } else if (ShacItemSpec_spec2(sh_item_spec, &sh_item_specifier, &sh_lower_bit)) {
      UCHAR_T lower_bit = (UCHAR_T)NatValue(&sh_lower_bit);
      UCHAR_T upper_bit = lower_bit;
      map_item->bit_pos_b = lower_bit;
      map_item->bit_pos_e = upper_bit;
      if (lower_bit > 31) ParseError(PARSE_BITPOS, NULL, cConvUtils::StringValue(lower_bit).c_str());
   } else if (ShacItemSpec_spec3(sh_item_spec, &sh_item_specifier, &sh_lower_bit, &sh_upper_bit)) {
      UCHAR_T lower_bit = (UCHAR_T)NatValue(&sh_lower_bit);
      UCHAR_T upper_bit = (UCHAR_T)NatValue(&sh_upper_bit);
      map_item->bit_pos_b = lower_bit;
      map_item->bit_pos_e = upper_bit;
      if (lower_bit > 31) ParseError(PARSE_BITPOS, NULL, cConvUtils::StringValue(lower_bit).c_str());
      if (upper_bit > 31) ParseError(PARSE_BITPOS, NULL, cConvUtils::StringValue(upper_bit).c_str());
      if (lower_bit > upper_bit) {
         ParseError(PARSE_BITPOS_SPECIFICATION,
                    0, 0,
                    cConvUtils::StringValue(lower_bit).c_str(),
                    cConvUtils::StringValue(upper_bit).c_str());
      }
   } else {
_ASSERT_UNCOND
   }
   GLS_Tok sh_name;
   ShacSymbol sh_symbol;
   if (ShacItemSpecifier_symbol(sh_item_specifier, &sh_symbol)) {
      GLS_Tok sh_token;
      if (ShacSymbol_dec(sh_symbol, &sh_token)) {
         map_item->address = NatValue(&sh_token);
      } else if (ShacSymbol_ide(sh_symbol, &sh_token)) {
         STRING_T symname = StringValue(&sh_token);
         ULONG_T symval = context->SymbolValue(symname.c_str());
         if (symval == UNDEFINED_SYMBOL_VALUE) {
            symval = (ULONG_T)UNRESOLVED_SYMBOL_VALUE;
            PT_Term * symbol = (void**)sh_token;
            int line = PT_row(symbol);
            int col = PT_col(symbol);
            if (_Step == 2) {
               AddUnresolvedSymbol(context, var_def, symname.c_str(), line, col, pos);
            }
//            ParseError(PARSE_SYMBOL_RESOLVE, (void**)sh_token);
         }
         map_item->address = symval;
      } else if (ShacSymbol_hex(sh_symbol, &sh_token)) {
         map_item->address = HexValue(&sh_token);
      }
   } else if (ShacItemSpecifier_name(sh_item_specifier, &sh_name)) {
     map_item->name = PersistentStringValue(&sh_name);
   }   
   return map_item;
  //## end cStyxParser::ParseItemSpec%1041236881.body
}

void cStyxParser::ParseItemSpecArray (cContext *context, cMapping *mapping, ShacItemSpec *sh_item_spec, cVarDef *var_def)
{
  //## begin cStyxParser::ParseItemSpecArray%1041236871.body preserve=yes
   ULONG_T array_size = var_def->Elements();
   MAP_ITEM_T * base_item = ParseItemSpec(context, (void**)sh_item_spec, var_def, 0);
   MAP_ITEM_T * map_item = NULL;
   for (ULONG_T i=0; i<array_size; i++) {
      map_item = NewMapItem(base_item);
      map_item->buf_spec = mapping->_PhysSpec.c_str();
      map_item->device_name = CopyName(var_def->_DeviceName);
      map_item->address = base_item->address + i;
      map_item->var_def = var_def;
      map_item->pos = i;
      map_item->data_type = mapping->_DataType;
      map_item->size = mapping->_Length * cSHVariant::TypeSize(map_item->data_type);
      mapping->SetItem(i, map_item);
   }
   delete base_item;
  //## end cStyxParser::ParseItemSpecArray%1041236871.body
}

void cStyxParser::ParseItemSpecList (cContext *context, cMapping *mapping, ShacMapDef *sh_map_def, cVarDef *var_def, ULONG_T &parseItemSpecErrors)
{
  //## begin cStyxParser::ParseItemSpecList%1041236879.body preserve=yes
   ULONG_T i = 0;
   GLS_Lst(ShacItemSpec) item_spec_list;
   GLS_Lst(ShacItemSpec) item_spec_list_it;
   ShacMapTypeSpec sh_map_type_spec;
   ShacRefresh sh_refresh;
   ShacConvFunc sh_conv_func;
   GLS_Tok sh_phys_spec;
   _ASSERT_COND(ShacMapDef_map2(sh_map_def, &sh_phys_spec, &sh_map_type_spec, &item_spec_list,
                &sh_refresh, &sh_conv_func))
   MAP_ITEM_T * map_item = NULL;
   GLS_FORALL(item_spec_list_it, item_spec_list) {
      ShacItemSpec sh_item_spec = GLS_FIRST(ShacItemSpec, item_spec_list_it);
      map_item = ParseItemSpec(context, (void**)sh_item_spec, var_def, i);
      map_item->buf_spec = mapping->_PhysSpec.c_str();
      map_item->device_name = CopyName(var_def->_DeviceName);
      map_item->var_def = var_def;
      map_item->data_type = mapping->_DataType;
      map_item->size = mapping->_Length * cSHVariant::TypeSize(map_item->data_type);
      map_item->pos = i;
      mapping->SetItem(i, map_item);
      i++;
   }

   if (map_item != NULL && map_item->name == NULL) {
      ULONG_T address = map_item->address;
      ULONG_T j = 0;
      ULONG_T elements = mapping->_ItemCount;
      for (j=i; j<elements; j++) {
         MAP_ITEM_T * new_item = CopyItemSpec(context, map_item, var_def);
         address++;
         new_item->address = address;
         new_item->pos = j;
         mapping->SetItem(j, new_item);

         if (i != 1) {
            ErrorPrintf("Auto mapping error at more then one mapping (var size larger then number of mappings, %s)\n", new_item->var_def->_VarName.c_str());
            parseItemSpecErrors++;
         }
      }
   }
  //## end cStyxParser::ParseItemSpecList%1041236879.body
}

void cStyxParser::ParseDataTypeSpec (ShacDataTypeSpec *sh_data_type_spec, UCHAR_T &data_type, ULONG_T &length, UCHAR_T &precision)
{
  //## begin cStyxParser::ParseDataTypeSpec%1042459988.body preserve=yes
   ShacBaseType sh_base_type;
   ShacStringType sh_string_type;
   GLS_Tok sh_nat_value;
   if (ShacDataTypeSpec_type1(sh_data_type_spec, &sh_base_type)) {
      data_type = BaseType((void**)sh_base_type);
      length = 1;
      precision = 0;
   } else if (ShacDataTypeSpec_type2(sh_data_type_spec, &sh_base_type, &sh_nat_value)) {
      data_type = BaseType((void**)sh_base_type);
      length = 1;
      precision = (UCHAR_T)NatValue(&sh_nat_value);
   } else if (ShacDataTypeSpec_type3(sh_data_type_spec, &sh_string_type, &sh_nat_value)) {
      data_type = StringType((void**)sh_string_type);
      length = NatValue(&sh_nat_value);
      precision = 0;
   } else if (ShacDataTypeSpec_type4(sh_data_type_spec, &sh_string_type)) {
      data_type = StringType((void**)sh_string_type);
      length = 1;
      precision = 0;
   } else {
_ASSERT_UNCOND
   }
  //## end cStyxParser::ParseDataTypeSpec%1042459988.body
}

void cStyxParser::ParseMapTypeSpec (ShacMapTypeSpec *sh_map_type_spec, UCHAR_T &data_type, ULONG_T &length, UCHAR_T &precision)
{
  //## begin cStyxParser::ParseMapTypeSpec%1042792991.body preserve=yes
   ShacBaseType sh_base_type;
   ShacStringType sh_string_type;
   GLS_Tok sh_nat_value;
   if (ShacMapTypeSpec_type1(sh_map_type_spec, &sh_base_type)) {
      data_type = BaseType((void**)sh_base_type);
   } else if (ShacMapTypeSpec_type2(sh_map_type_spec, &sh_base_type, &sh_nat_value)) {
      data_type = BaseType((void**)sh_base_type);
      precision = (UCHAR_T)NatValue(&sh_nat_value);
   } else if (ShacMapTypeSpec_type3(sh_map_type_spec, &sh_string_type, &sh_nat_value)) {
      data_type = StringType((void**)sh_string_type);
      length = NatValue(&sh_nat_value);
   } else if (ShacMapTypeSpec_type4(sh_map_type_spec, &sh_string_type)) {
      data_type = StringType((void**)sh_string_type);
      length = 1;
   } else {
_ASSERT_UNCOND
   }
  //## end cStyxParser::ParseMapTypeSpec%1042792991.body
}

void cStyxParser::ParseDeviceSpec (cContext *context, ShacDeviceSpec *sh_device_spec)
{
  //## begin cStyxParser::ParseDeviceSpec%1042459994.body preserve=yes
   GLS_Tok sh_device_name;
   if (ShacDeviceSpec_spec(sh_device_spec, &sh_device_name)) {
      STRING_T device_name = (const char *)GLS_Tok_string(sh_device_name);
      context->_ActDeviceName = device_name;
      _ActDeviceName = device_name;
   } else {
      _ActDeviceName = "";
   }
  //## end cStyxParser::ParseDeviceSpec%1042459994.body
}

void cStyxParser::ParseRefresh (cContext *context, ShacRefresh *sh_refresh, cVarDef *var_def)
{
  //## begin cStyxParser::ParseRefresh%1051713140.body preserve=yes
   ShacRefreshType sh_refresh_type;
   if (ShacRefresh_refresh(sh_refresh, &sh_refresh_type)) {
      LONG_T refresh_value = 0;
      UCHAR_T refresh_type = RefreshType((void**)sh_refresh_type, refresh_value);
      var_def->_RefreshType = refresh_type;
      var_def->_RefreshValue = refresh_value;
   }
  //## end cStyxParser::ParseRefresh%1051713140.body
}

void cStyxParser::ParseDescription (cContext *context, ShacDescription *sh_description, cVarDef *var_def)
{
  //## begin cStyxParser::ParseDescription%1051713141.body preserve=yes
   GLS_Tok sh_string;
   if (ShacDescription_desc(sh_description, &sh_string)) {
      var_def->_Description = StringValue(&sh_string);
   }
  //## end cStyxParser::ParseDescription%1051713141.body
}

void cStyxParser::ParseVarType (cContext *context, ShacVarTypeSpec* sh_var_type_spec, cVarDef *var_def)
{
  //## begin cStyxParser::ParseVarType%1051713142.body preserve=yes
   ShacVarType sh_var_type;
   if (ShacVarTypeSpec_vartype(sh_var_type_spec, &sh_var_type)) {
      var_def->_VarType = VarType((void**)sh_var_type);
   }
  //## end cStyxParser::ParseVarType%1051713142.body
}

void cStyxParser::ParsePersistence (cContext *context, ShacPersistence *sh_persistence, cVarDef *var_def)
{
  //## begin cStyxParser::ParsePersistence%1051713143.body preserve=yes
   ShacPersistenceType sh_persistence_type;
   if (ShacPersistence_persist(sh_persistence, &sh_persistence_type)) {
      var_def->_PersistenceType = PersistenceType((void**)sh_persistence_type);
   }
  //## end cStyxParser::ParsePersistence%1051713143.body
}

void cStyxParser::ParseFile (cContext *context, ShacFile *sh_file, cVarDef *var_def)
{
  //## begin cStyxParser::ParseFile%1051713144.body preserve=yes
   GLS_Tok sh_file_name;
   if (ShacFile_file(sh_file, &sh_file_name)) {
      var_def->_FileName = (const char *)GLS_Tok_string(sh_file_name);
   }
  //## end cStyxParser::ParseFile%1051713144.body
}

void cStyxParser::ParseValueSpec (cContext *context, ShacValueSpec *sh_value_spec, cVarDef *var_def)
{
  //## begin cStyxParser::ParseValueSpec%1091802227.body preserve=yes
   GLS_Lst(ShacValueSpec) value_spec_list;
   GLS_Lst(ShacValueSpec) value_spec_list_it;
   if (ShacValueSpec_spec(sh_value_spec, &value_spec_list)) {
      cVariableValues * values = new cVariableValues(var_def, var_def->Elements());
      ULONG_T pos = 0;
      GLS_FORALL(value_spec_list_it, value_spec_list) {
         ShacValue sh_value = GLS_FIRST(ShacValue, value_spec_list_it);
         STRING_T value = ParseValue(context, (void**)sh_value);
         values->SetValue(pos, value.c_str());
         pos++;
      }
   }
  //## end cStyxParser::ParseValueSpec%1091802227.body
}

STRING_T cStyxParser::ParseValue (cContext *context, ShacValue *sh_value)
{
  //## begin cStyxParser::ParseValue%1091802228.body preserve=yes
   STRING_T value;
   GLS_Tok sh_nat_value;
   GLS_Tok sh_hex_value;
   GLS_Tok sh_real_value;
   GLS_Tok sh_string_value;
   GLS_Tok sh_ide_value;
   ShacBcd sh_bcd;
   char svalue[64] = {0};
   LONG_T lvalue = 0;
   DOUBLE_T dvalue = 0;
   if (ShacValue_nat(sh_value, &sh_nat_value)) {
      lvalue = NatValue(&sh_nat_value);
      SafePrintf(svalue, sizeof(svalue), "%d", lvalue);
      value = svalue;
   } else if (ShacValue_hex(sh_value, &sh_hex_value)) {
      lvalue = HexValue(&sh_hex_value);
      SafePrintf(svalue, sizeof(svalue), "%d", lvalue);
      value = svalue;
   } else if (ShacValue_real(sh_value, &sh_real_value)) {
      dvalue = RealValue(&sh_real_value);
      SafePrintf(svalue, sizeof(svalue), "%f", dvalue);
      value = svalue;
   } else if (ShacValue_str(sh_value, &sh_string_value)) {
      value = StringValue(&sh_string_value);
   } else if (ShacValue_ide(sh_value, &sh_ide_value)) {
      value = (const char *)GLS_Tok_string(sh_ide_value);
   } else if (ShacValue_bcd(sh_value, &sh_bcd)) {
      value = ParseBcdValue(context, (void**)sh_bcd);
   } else {
_ASSERT_UNCOND
   }
   return value;
  //## end cStyxParser::ParseValue%1091802228.body
}

STRING_T cStyxParser::ParseBcdValue (cContext *context, ShacBcd *sh_bcd)
{
  //## begin cStyxParser::ParseBcdValue%1092218354.body preserve=yes
   STRING_T value;
   GLS_Tok sh_bcd_seq;
   if (ShacBcd_bcd(sh_bcd, &sh_bcd_seq)) {
      value = "bcd(";
      value += (const char *)GLS_Tok_string(sh_bcd_seq);
      value += ")";
   }
   return value;
  //## end cStyxParser::ParseBcdValue%1092218354.body
}

UCHAR_T cStyxParser::BaseType (ShacBaseType *sh_base_type)
{
  //## begin cStyxParser::BaseType%1040992355.body preserve=yes
   if (ShacBaseType_char(sh_base_type)) {
      return SH_CHAR;
   } else if (ShacBaseType_uchar(sh_base_type)) {
      return SH_UCHAR;
   } else if (ShacBaseType_short(sh_base_type)) {
      return SH_SHORT;
   } else if (ShacBaseType_ushort(sh_base_type)) {
      return SH_USHORT;
   } else if (ShacBaseType_long(sh_base_type)) {
      return SH_LONG;
   } else if (ShacBaseType_ulong(sh_base_type)) {
      return SH_ULONG;
   } else if (ShacBaseType_float(sh_base_type)) {
      return SH_FLOAT;
   } else if (ShacBaseType_double(sh_base_type)) {
      return SH_DOUBLE;
   } else if (ShacBaseType_void(sh_base_type)) {
      return UNDEFINED;
   } else if (ShacBaseType_bool(sh_base_type)) {
      return SH_UCHAR;
   } else if (ShacBaseType_object(sh_base_type)) {
      return SH_OBJECT;
   } else if (ShacBaseType_bit8(sh_base_type)) {
      return SH_BIT_8;
   } else if (ShacBaseType_bit16(sh_base_type)) {
      return SH_BIT_16;
   } else if (ShacBaseType_bit32(sh_base_type)) {
      return SH_BIT_32;
   }
   return UNDEFINED;
  //## end cStyxParser::BaseType%1040992355.body
}

UCHAR_T cStyxParser::StringType (ShacStringType *sh_string_type)
{
  //## begin cStyxParser::StringType%1040992358.body preserve=yes
   if (ShacStringType_string(sh_string_type)) {
      return SH_STRING;
   } else if (ShacStringType_wstring(sh_string_type)) {
      return SH_WSTRING;
   } else if (ShacStringType_byte(sh_string_type)) {
      return SH_BYTE;
   }
   return UNDEFINED;
  //## end cStyxParser::StringType%1040992358.body
}

INT_T cStyxParser::VarType (ShacVarType *sh_var_type)
{
  //## begin cStyxParser::VarType%1041236874.body preserve=yes
   if (ShacVarType_set(sh_var_type)) {
      return SH_VAR_SET;
   } else if (ShacVarType_act(sh_var_type)) {
      return SH_VAR_ACT;
   } else if (ShacVarType_volatile(sh_var_type)) {
      return SH_VAR_VOLATILE;
   } else if (ShacVarType_virtual(sh_var_type)) {
      return SH_VAR_VIRTUAL;
   }
   return UNDEFINED;
  //## end cStyxParser::VarType%1041236874.body
}

INT_T cStyxParser::EventType (ShacEventType *sh_event_type)
{
  //## begin cStyxParser::EventType%1041236876.body preserve=yes
   if (ShacEventType_cycle(sh_event_type)) {
      return SH_EVENT_CYCLE;
   } else if (ShacEventType_automatic(sh_event_type)) {
      return SH_EVENT_AUTOMATIC;
   } else if (ShacEventType_data(sh_event_type)) {
      return SH_EVENT_DATA;
   }
   return UNDEFINED;
  //## end cStyxParser::EventType%1041236876.body
}

INT_T cStyxParser::PersistenceType (ShacPersistenceType *sh_persistence_type)
{
  //## begin cStyxParser::PersistenceType%1051713137.body preserve=yes
   if (ShaciraPersistenceType_ram(sh_persistence_type)) {
      return SH_RAM;
   } else if (ShaciraPersistenceType_bbram(sh_persistence_type)) {
      return SH_BBRAM;
   } else if (ShaciraPersistenceType_filebased(sh_persistence_type)) {
      return SH_FILE;
   } else if (ShaciraPersistenceType_setup(sh_persistence_type)) {
      return SH_SETUP_PST;
   }
   return UNDEFINED;
  //## end cStyxParser::PersistenceType%1051713137.body
}

UCHAR_T cStyxParser::RefreshType (ShacRefreshType *sh_refresh_type, LONG_T &value)
{
  //## begin cStyxParser::RefreshType%1051713139.body preserve=yes
   GLS_Tok sh_nat_value;
   ShacEventType sh_event_type;
   if (ShacRefreshType_cyclic(sh_refresh_type, &sh_nat_value)) {
      value = atol((const char *)GLS_Tok_string(sh_nat_value));   
      return SH_REFRESH_INTERVAL;
   } else if (ShacRefreshType_event1(sh_refresh_type, &sh_event_type)) {
      value = EventType((void**)sh_event_type);
      return SH_REFRESH_EVENT;
   } else if (ShacRefreshType_event2(sh_refresh_type, &sh_nat_value)) {
      value = atol((const char *)GLS_Tok_string(sh_nat_value));   
      return SH_REFRESH_EVENT;
   }
   return UNDEFINED;
  //## end cStyxParser::RefreshType%1051713139.body
}

LONG_T cStyxParser::NatValue (GLS_Tok *token)
{
  //## begin cStyxParser::NatValue%1040992364.body preserve=yes
   STRING_T value = (const char *)GLS_Tok_string(*token);
   return atol(value.c_str());
  //## end cStyxParser::NatValue%1040992364.body
}

LONG_T cStyxParser::HexValue (GLS_Tok *token)
{
  //## begin cStyxParser::HexValue%1040992367.body preserve=yes
   STRING_T value = (const char *)GLS_Tok_string(*token);
   LONG_T lval = 0;
   int params = sscanf(value.c_str(), "%x", &lval);
   if (params != 1) {
      params = sscanf(value.c_str(), "%X", &lval);
   }
   return lval;
  //## end cStyxParser::HexValue%1040992367.body
}

DOUBLE_T cStyxParser::RealValue (GLS_Tok *token)
{
  //## begin cStyxParser::RealValue%1040992365.body preserve=yes
   STRING_T value = (const char *)GLS_Tok_string(*token);
   return atof(value.c_str());
  //## end cStyxParser::RealValue%1040992365.body
}

STRING_T cStyxParser::StringValue (GLS_Tok *token)
{
  //## begin cStyxParser::StringValue%1040992366.body preserve=yes
   STRING_T value = (const char *)GLS_Tok_string(*token);
	if (*value.c_str() == '"') {
		value = STRING_T(value, 1, value.size() - 2);
	}
   return value;
  //## end cStyxParser::StringValue%1040992366.body
}

CONST_STRING_T cStyxParser::PersistentStringValue (GLS_Tok *token)
{
  //## begin cStyxParser::PersistentStringValue%1072085857.body preserve=yes
   STRING_T value = StringValue(token);
   ULONG_T size = value.size();
   char * _value = (char*)cSystemUtils::Alloc(size + 1);
   memcpy(_value, value.c_str(), size);
   return _value;
  //## end cStyxParser::PersistentStringValue%1072085857.body
}

cControlState * cStyxParser::ParseState (cContext *context, ShacState *sh_state)
{
  //## begin cStyxParser::ParseState%1060682990.body preserve=yes
   cControlState * state = NULL;
   ShacCondition sh_condition;
   GLS_Tok sh_string;
   if (ShacState_state(sh_state, &sh_string, &sh_condition)) {
      cControlCondition * condition = ParseCondition(context, (void**)sh_condition);
      if (condition != NULL) {
         state = new cControlState((const char *)GLS_Tok_string(sh_string), condition);
      } else {
 _ASSERT_UNCOND
      }
   }
   return state;
  //## end cStyxParser::ParseState%1060682990.body
}

cControlProgram * cStyxParser::ParseProgram (cContext *context, ShacProgram *sh_program)
{
  //## begin cStyxParser::ParseProgram%1060682991.body preserve=yes
return NULL;
  //## end cStyxParser::ParseProgram%1060682991.body
}

cControlProcedure * cStyxParser::ParseProcedure (cContext *context, ShacProcedure *sh_procedure)
{
  //## begin cStyxParser::ParseProcedure%1060682992.body preserve=yes
   cProcedureLine * first_line = NULL;
   cProcedureLine * last_line = NULL;
   LINE_VECTOR_T lines;
   cControlProcedure * proc = NULL;
   ShacStatementBlock sh_statement_block;
   GLS_Tok sh_string;
   if (ShacProcedure_proc(sh_procedure, &sh_string, &sh_statement_block)) {
      proc = new cControlProcedure((const char *)GLS_Tok_string(sh_string));
      ParseStatements(context, (void**)sh_statement_block, lines, 0, first_line, last_line, NULL);
      int size = lines.size();
      int i = 0;
      for (i=0; i<size; i++) {
         cProcedureLine * line = lines[i];
         line->_Line = i;
      }
      for (i=0; i<size; i++) {
         cProcedureLine * line = lines[i];
         line->Resolve();
         proc->AddLine(line);
      }
//proc->PrintLines();
   } else {
_ASSERT_UNCOND
   }
   return proc;
  //## end cStyxParser::ParseProcedure%1060682992.body
}

cControlStartCondition * cStyxParser::ParseStartCondition (cContext *context, ShacStartCondition *sh_start_condition)
{
  //## begin cStyxParser::ParseStartCondition%1060682993.body preserve=yes
return NULL;
  //## end cStyxParser::ParseStartCondition%1060682993.body
}

cControlCondition * cStyxParser::ParseCondition (cContext *context, ShacCondition *sh_condition)
{
  //## begin cStyxParser::ParseCondition%1060691301.body preserve=yes
   cControlCondition * condition = NULL;
   ShacCondition sh_condition1;
   ShacCondition sh_condition2;
   ShacAtomicCondition sh_atomic_condition;
   GLS_Tok sh_string;
   if (ShacCondition_atom(sh_condition, &sh_atomic_condition)) {
      cAtomicCondition * atomic_condition = ParseAtomicCondition(context, (void**)sh_atomic_condition);
      if (atomic_condition != NULL) {
         condition = new cControlCondition(atomic_condition);
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacCondition_or(sh_condition, &sh_condition1, &sh_condition2)) {
      cControlCondition * condition1 = ParseCondition(context, (void**)sh_condition1);
      cControlCondition * condition2 = ParseCondition(context, (void**)sh_condition2);
      if (condition1 != NULL && condition2 != NULL) {
         condition = new cControlCondition(condition1, condition2, LOGOP_OR);
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacCondition_and(sh_condition, &sh_condition1, &sh_condition2)) {
      cControlCondition * condition1 = ParseCondition(context, (void**)sh_condition1);
      cControlCondition * condition2 = ParseCondition(context, (void**)sh_condition2);
      if (condition1 != NULL && condition2 != NULL) {
         condition = new cControlCondition(condition1, condition2, LOGOP_AND);
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacCondition_not(sh_condition, &sh_condition1)) {
      cControlCondition * condition1 = ParseCondition(context, (void**)sh_condition1);
      if (condition1 != NULL) {
         condition = new cControlCondition(condition1, NULL, LOGOP_NOT);
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacCondition_name(sh_condition, &sh_string)) {
      cControlState * state = context->State((const char *)GLS_Tok_string(sh_string));
      if (state != NULL) {
         condition = new cControlCondition(state);
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacCondition_brack(sh_condition, &sh_condition1)) {
      cControlCondition * condition1 = ParseCondition(context, (void**)sh_condition1);
      if (condition1 != NULL) {
         condition = new cControlCondition(condition1);
      } else {
_ASSERT_UNCOND
      }
   } else {
_ASSERT_UNCOND
   }
   return condition;
  //## end cStyxParser::ParseCondition%1060691301.body
}

cAtomicCondition * cStyxParser::ParseAtomicCondition (cContext *context, ShacAtomicCondition *sh_atomic_condition)
{
  //## begin cStyxParser::ParseAtomicCondition%1060691302.body preserve=yes
   cAtomicCondition * condition = NULL;
   cArgument * arg1 = NULL;
   cArgument * arg2 = NULL;
   ShacArgument sh_argument1;
   ShacArgument sh_argument2;
   ShacRelOp sh_relop;
   if (ShacAtomicCondition_rel(sh_atomic_condition, &sh_argument1, &sh_relop, &sh_argument2)) {
      arg1 = ParseArgument(context, (void**)sh_argument1);
      arg2 = ParseArgument(context, (void**)sh_argument2);
   } else {
_ASSERT_UNCOND
   }
   RelOps relop = (RelOps)RelOp((void**)sh_relop);
   condition = new cAtomicCondition(arg1, relop, arg2);
   return condition;
  //## end cStyxParser::ParseAtomicCondition%1060691302.body
}

INT_T cStyxParser::RelOp (ShacRelOp *sh_relop)
{
  //## begin cStyxParser::RelOp%1060691307.body preserve=yes
   if (ShacRelOp_lt(sh_relop)) {
      return RELOP_LT;
   } else if (ShacRelOp_le(sh_relop)) {
      return RELOP_LE;
   } else if (ShacRelOp_gt(sh_relop)) {
      return RELOP_GT;
   } else if (ShacRelOp_ge(sh_relop)) {
      return RELOP_GE;
   } else if (ShacRelOp_eq(sh_relop)) {
      return RELOP_EQ;
   } else if (ShacRelOp_ne(sh_relop)) {
      return RELOP_NE;
   } else {
_ASSERT_UNCOND
   }
   return UNDEFINED;
  //## end cStyxParser::RelOp%1060691307.body
}

void cStyxParser::ParseStatements (cContext *context, ShacStatementBlock *sh_statement_block, LINE_VECTOR_T &lines, INT_T depth, cProcedureLine * &first_line, cProcedureLine * &last_line, cProcedureLine *parent_line)
{
  //## begin cStyxParser::ParseStatements%1060779898.body preserve=yes
   depth++;
   GLS_Lst(ShacStatement) statement_list;
   GLS_Lst(ShacStatement) statement_list_it;
   cProcedureLine * previous_line = NULL;
   cProcedureLine * line = NULL;
   if (ShacStatementBlock_stmts(sh_statement_block, &statement_list)) {
      GLS_FORALL(statement_list_it, statement_list) {
         ShacStatement sh_statement = GLS_FIRST(ShacStatement, statement_list_it);
         line = ParseStatement(context, (void**)sh_statement, lines, depth);
         line->ParentLine(parent_line);
         if (statement_list_it == statement_list) {
            first_line = line;
         }
         if (previous_line != NULL) {
            previous_line->NextLine(line);
         }
         previous_line = line;
      }
   }
   cProcedureLine * end_line = new cProcedureLine;
   ADD_LINE(end_line,lines)
   last_line = end_line;
   last_line->ParentLine(parent_line);
   if (line != NULL) {
      line->NextLine(end_line);
   }
  //## end cStyxParser::ParseStatements%1060779898.body
}

cProcedureLine * cStyxParser::ParseStatement (cContext *context, ShacStatement *sh_statement, LINE_VECTOR_T &lines, INT_T depth)
{
  //## begin cStyxParser::ParseStatement%1060779897.body preserve=yes
   cProcedureLine * line = NULL;
   cProcedureLine * first_line = NULL;
   cProcedureLine * last_line = NULL;
   ShacStatementBlock sh_statement_block1;;
   ShacStatementBlock sh_statement_block2;;
   ShacVarRef sh_var_ref;
   ShacFuncRef sh_func_ref;
   ShacArgument sh_argument;
   ShacCondition sh_condition;
   GLS_Tok sh_string;
   if (ShacStatement_if(sh_statement, &sh_condition, &sh_statement_block1)) {
      cControlCondition * condition = ParseCondition(context, (void**)sh_condition);
      if (condition != NULL) {
         line = new cProcedureLine(IF_STMT, condition, depth);
         ADD_LINE(line,lines)
         ParseStatements(context, (void**)sh_statement_block1, lines, depth, first_line, last_line, line);
         line->CondLine(first_line);
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacStatement_while(sh_statement, &sh_condition, &sh_statement_block1)) {
      cControlCondition * condition = ParseCondition(context, (void**)sh_condition);
      if (condition != NULL) {
         line = new cProcedureLine(WHILE_STMT, condition, depth);
         ADD_LINE(line,lines)
         ParseStatements(context, (void**)sh_statement_block1, lines, depth, first_line, last_line, line);
         line->CondLine(first_line);
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacStatement_ifels(sh_statement, &sh_condition, &sh_statement_block1, &sh_statement_block2)) {
      cControlCondition * condition = ParseCondition(context, (void**)sh_condition);
      if (condition != NULL) {
         line = new cProcedureLine(IF_ELSE_STMT, condition, depth);
         ADD_LINE(line,lines)
         ParseStatements(context, (void**)sh_statement_block1, lines, depth, first_line, last_line, line);
         line->CondLine(first_line);
         ParseStatements(context, (void**)sh_statement_block2, lines, depth, first_line, last_line, line);
         line->NotCondLine(first_line);
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacStatement_proc(sh_statement, &sh_string)) {
      line = new cProcedureLine(EXEC_STMT, (const char *)GLS_Tok_string(sh_string), depth);
      ADD_LINE(line,lines)
   } else if (ShacStatement_func(sh_statement, &sh_func_ref)) {
      cFuncRef * func_ref = ParseFuncRef(context, (void**)sh_func_ref, UNDEFINED);
      if (func_ref != NULL) {
         line = new cProcedureLine(CALL_STMT, func_ref, depth);
         ADD_LINE(line,lines)
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacStatement_assg1(sh_statement, &sh_var_ref, &sh_argument)) {
      cVarRef * var_ref = ParseVarRef(context, (void**)sh_var_ref, UNDEFINED);
      if (var_ref != NULL) {
         UCHAR_T requested_data_type = var_ref->DataType();
         cArgument * arg = ParseArgument(context, (void**)sh_argument, requested_data_type);
         line = new cProcedureLine(ARG_ASSIGN_STMT, var_ref, arg, depth);
         ADD_LINE(line,lines)
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacStatement_assg2(sh_statement, &sh_var_ref, &sh_string)) {
      cVarRef * var_ref = ParseVarRef(context, (void**)sh_var_ref, UNDEFINED);
      if (var_ref != NULL) {
         line = new cProcedureLine(PARAM_ASSIGN_STMT, var_ref, (const char *)GLS_Tok_string(sh_string), depth);
         ADD_LINE(line,lines)
      } else {
_ASSERT_UNCOND
      }
   } else if (ShacStatement_ret(sh_statement)) {
      line = new cProcedureLine(RETURN_STMT, depth);
      ADD_LINE(line,lines)
   } else {
_ASSERT_UNCOND
   }
   return line;
  //## end cStyxParser::ParseStatement%1060779897.body
}

cArgument * cStyxParser::ParseArgument (cContext *context, ShacArgument *sh_argument, UCHAR_T requested_data_type)
{
  //## begin cStyxParser::ParseArgument%1061574772.body preserve=yes
   cArgument * arg = NULL;
   GLS_Tok sh_nat_value;
   GLS_Tok sh_hex_value;
   GLS_Tok sh_real_value;
   GLS_Tok sh_string_value;
   ShacFuncRef sh_func_ref;
   ShacVarRef sh_var_ref;
   if (ShacArgument_cnat(sh_argument, &sh_nat_value)) {
      arg = new cConstInt(NatValue(&sh_nat_value));
      UCHAR_T data_type_code = arg->DataType();
      if (CheckTypes(requested_data_type, data_type_code, (void**)sh_nat_value)) {
      }
   } else if (ShacArgument_chex(sh_argument, &sh_hex_value)) {
      arg = new cConstInt(HexValue(&sh_hex_value));
      UCHAR_T data_type_code = arg->DataType();
      if (CheckTypes(requested_data_type, data_type_code, (void**)sh_hex_value)) {
      }
   } else if (ShacArgument_creal(sh_argument, &sh_real_value)) {
      arg = new cConstReal(RealValue(&sh_real_value));
      UCHAR_T data_type_code = arg->DataType();
      if (CheckTypes(requested_data_type, data_type_code, (void**)sh_real_value)) {
      }
   } else if (ShacArgument_cstring(sh_argument, &sh_string_value)) {
      arg = new cConstString(StringValue(&sh_string_value).c_str());
      UCHAR_T data_type_code = arg->DataType();
      if (CheckTypes(requested_data_type, data_type_code, (void**)sh_string_value)) {
      }
   } else if (ShacArgument_func(sh_argument, &sh_func_ref)) {
      cFuncRef * func_ref = ParseFuncRef(context, (void**)sh_func_ref, requested_data_type);
      if (func_ref != NULL) {
         arg = new cFuncRefArg(func_ref);
         UCHAR_T data_type_code = arg->DataType();
         if (CheckTypes(requested_data_type, data_type_code, (void**)sh_nat_value)) {
         }
      } else {
#ifdef ENABLE_STEPS
         if (_Step != 1) {
_ASSERT_UNCOND
         }
#else
_ASSERT_UNCOND
#endif
      }
   } else if (ShacArgument_var(sh_argument, &sh_var_ref)) {
      cVarRef * var_ref = ParseVarRef(context, (void**)sh_var_ref, requested_data_type);
      if (var_ref != NULL) {
         arg = new cVarRefArg(var_ref);
         UCHAR_T data_type_code = arg->DataType();
         if (CheckTypes(requested_data_type, data_type_code, (void**)sh_nat_value)) {
         }
      } else {
         if (!_IDEActive) {
#ifdef ENABLE_STEPS
            if (_Step != 1) {
_ASSERT_UNCOND
            }
#else
_ASSERT_UNCOND
#endif
         }
      }
   } else {
_ASSERT_UNCOND
   }
   return arg;
  //## end cStyxParser::ParseArgument%1061574772.body
}

BOOL_T cStyxParser::CheckTypes (UCHAR_T requested_data_type, UCHAR_T supplied_data_type, PT_Term *symbol)
{
  //## begin cStyxParser::CheckTypes%1061805338.body preserve=yes
   if (TYPE_UNSPECIFIED(requested_data_type) ||
       TYPES_COMPATIBLE(requested_data_type, supplied_data_type)) {
      return true;
   } else {
      ParseError(PARSE_TYPES_NOT_COMPATIBLE,
                 Line(symbol),
                 Column(symbol),
                 cSHVariant::TypeName(requested_data_type).c_str(),
                 cSHVariant::TypeName(supplied_data_type).c_str());
      return false;
   }
  //## end cStyxParser::CheckTypes%1061805338.body
}

BOOL_T cStyxParser::CheckClass (UCHAR_T requested_class, UCHAR_T supplied_class, PT_Term *symbol)
{
  //## begin cStyxParser::CheckClass%1061805342.body preserve=yes
   if (requested_class == UNDEFINED) {
      return true;
   } else {
      if (requested_class != supplied_class) {
         ParseError(PARSE_FUNCREF_INVALID_CLASS,
                    Line(symbol),
                    Column(symbol),
                    cFuncDecl::ClassName(requested_class).c_str(),
                    cFuncDecl::ClassName(supplied_class).c_str());
         return false;
      } else {
         return true;
      }
   }
  //## end cStyxParser::CheckClass%1061805342.body
}

MAP_ITEM_T * cStyxParser::CopyItemSpec (cContext *context, MAP_ITEM_T *map_item, cVarDef *var_def)
{
  //## begin cStyxParser::CopyItemSpec%1084888946.body preserve=yes
   MAP_ITEM_T * new_item = NewMapItem();
   new_item->var_def = var_def;
   new_item->device_name = CopyName(var_def->_DeviceName);
   new_item->buf_spec = map_item->buf_spec;
   new_item->data_type = map_item->data_type;
   new_item->size = map_item->size;
   new_item->name = map_item->name;
   new_item->address = map_item->address;
   new_item->bit_pos_b = map_item->bit_pos_b;
   new_item->bit_pos_e = map_item->bit_pos_e;
   return new_item;
  //## end cStyxParser::CopyItemSpec%1084888946.body
}

cFuncRef * cStyxParser::ParseFuncRefOptimized (cContext *context, CONST_STRING_T func_spec, UCHAR_T requested_data_type, UCHAR_T requested_class)
{
  //## begin cStyxParser::ParseFuncRefOptimized%1093975009.body preserve=yes
   return NULL;
  //## end cStyxParser::ParseFuncRefOptimized%1093975009.body
}

cVarRef * cStyxParser::ParseVarRefOptimized (cContext *context, CONST_STRING_T var_spec, UCHAR_T requested_data_type)
{
  //## begin cStyxParser::ParseVarRefOptimized%1093975010.body preserve=yes
//return NULL;
   long i1 = -1;
   long i2 = -1;
   long i3 = -1;
   int params = 0;
   int nread = 0;
   char c = 0;
   int len = strlen(var_spec);
   char var_name[256];
   for (int i=0; i<len; i++) {
      if (var_spec[i] == '[') {
         params = sscanf(var_spec, "%[^[][%d][%d][%d]%n", var_name, &i1, &i2, &i3, &nread);
         if (params == 4) {
            c = var_spec[nread];
            if (c == 0) {
               cVarDef * var_def = context->VarDef(var_name);
               if (var_def == NULL) {
                  return NULL;
               } else {
                  int dims = var_def->Dims();
                  if (dims < 3) {
                     throw cError(PARSE_VARREF_TOO_MUCH_INDICES, 0, "1", "0", var_name);
                  } else if (dims > 3) {
                     throw cError(PARSE_VARREF_TOO_FEW_INDICES, 0, "1", "0", var_name);
                  }
                  cVarRef * var_ref = new cVarRef(var_def, context);
                  cArgument * arg1 = new cConstInt(i1);
                  var_ref->SetIndex(0, arg1);
                  cArgument * arg2 = new cConstInt(i2);
                  var_ref->SetIndex(1, arg2);
                  cArgument * arg3 = new cConstInt(i3);
                  var_ref->SetIndex(2, arg3);
                  return var_ref;
               }
            } else {
               return NULL;
            }
         }
         params = sscanf(var_spec, "%[^[][%d][%d]%n", var_name, &i1, &i2, &nread);
         if (params == 3) {
            c = var_spec[nread];
            if (c == 0) {
               cVarDef * var_def = context->VarDef(var_name);
               if (var_def == NULL) {
                  return NULL;
               } else {
                  int dims = var_def->Dims();
                  if (dims < 2) {
                     throw cError(PARSE_VARREF_TOO_MUCH_INDICES, 0, "1", "0", var_name);
                  } else if (dims > 2) {
                     throw cError(PARSE_VARREF_TOO_FEW_INDICES, 0, "1", "0", var_name);
                  }
                  cVarRef * var_ref = new cVarRef(var_def, context);
                  cArgument * arg1 = new cConstInt(i1);
                  var_ref->SetIndex(0, arg1);
                  cArgument * arg2 = new cConstInt(i2);
                  var_ref->SetIndex(1, arg2);
                  return var_ref;
               }
            } else {
               return NULL;
            }
         }
         params = sscanf(var_spec, "%[^[][%d]%n", var_name, &i1, &nread);
         if (params == 2) {
            c = var_spec[nread];
            if (c == 0) {
               cVarDef * var_def = context->VarDef(var_name);
               if (var_def == NULL) {
                  return NULL;
               } else {
                  int dims = var_def->Dims();
                  if (dims < 1) {
                     throw cError(PARSE_VARREF_TOO_MUCH_INDICES, 0, "1", "0", var_name);
                  } else if (dims > 1) {
                     throw cError(PARSE_VARREF_TOO_FEW_INDICES, 0, "1", "0", var_name);
                  }
                  cVarRef * var_ref = new cVarRef(var_def, context);
                  cArgument * arg1 = new cConstInt(i1);
                  var_ref->SetIndex(0, arg1);
                  return var_ref;
               }
            } else {
               return NULL;
            }
         }
      }
   }
   cVarDef * var_def = context->VarDef(var_spec);
   if (var_def == NULL) {
      return NULL;
   } else {
      int dims = var_def->Dims();
      if (dims > 0) {
         throw cError(PARSE_VARREF_TOO_FEW_INDICES, 0, "1", "0", var_spec);
      }
      cVarRef * var_ref = new cVarRef(var_def, context);
      return var_ref;
   }
  //## end cStyxParser::ParseVarRefOptimized%1093975010.body
}

void cStyxParser::ParseText (cContext *context, ShacText *sh_text, cVarDef *var_def)
{
  //## begin cStyxParser::ParseText%1108111669.body preserve=yes
   GLS_Tok sh_string;
   if (ShacText_text(sh_text, &sh_string)) {
      var_def->_Text = StringValue(&sh_string);
   }
  //## end cStyxParser::ParseText%1108111669.body
}

void cStyxParser::ParseDim1Text (cContext *context, ShacDim1 *sh_dim1_text, cVarDef *var_def)
{
  //## begin cStyxParser::ParseDim1Text%1108111664.body preserve=yes
   GLS_Tok sh_string;
   if (ShacDim1_text(sh_dim1_text, &sh_string)) {
      var_def->_Dim1Text = StringValue(&sh_string);
   }
  //## end cStyxParser::ParseDim1Text%1108111664.body
}

void cStyxParser::ParseDim2Text (cContext *context, ShacDim2 *sh_dim2_text, cVarDef *var_def)
{
  //## begin cStyxParser::ParseDim2Text%1108111665.body preserve=yes
   GLS_Tok sh_string;
   if (ShacDim2_text(sh_dim2_text, &sh_string)) {
      var_def->_Dim2Text = StringValue(&sh_string);
   }
  //## end cStyxParser::ParseDim2Text%1108111665.body
}

void cStyxParser::ParseDim3Text (cContext *context, ShacDim3 *sh_dim3_text, cVarDef *var_def)
{
  //## begin cStyxParser::ParseDim3Text%1108111666.body preserve=yes
   GLS_Tok sh_string;
   if (ShacDim3_text(sh_dim3_text, &sh_string)) {
      var_def->_Dim3Text = StringValue(&sh_string);
   }
  //## end cStyxParser::ParseDim3Text%1108111666.body
}

void cStyxParser::ParseDim4Text (cContext *context, ShacDim4 *sh_dim4_text, cVarDef *var_def)
{
  //## begin cStyxParser::ParseDim4Text%1108111667.body preserve=yes
   GLS_Tok sh_string;
   if (ShacDim4_text(sh_dim4_text, &sh_string)) {
      var_def->_Dim4Text = StringValue(&sh_string);
   }
  //## end cStyxParser::ParseDim4Text%1108111667.body
}

void cStyxParser::ParseFlags (cContext *context, ShacFlags *sh_flags, cVarDef *var_def)
{
  //## begin cStyxParser::ParseFlags%1108111668.body preserve=yes
   ShacFlagValue sh_flag_value;
   if (ShacFlags_value(sh_flags, &sh_flag_value)) {
      GLS_Tok sh_nat_value;
      GLS_Tok sh_hex_value;
      if (ShacFlagValue_cnat(sh_flag_value, &sh_nat_value)) {
         var_def->_Flags = NatValue(&sh_nat_value);
      } else if (ShacFlagValue_chex(sh_flag_value, &sh_hex_value)) {
         var_def->_Flags = HexValue(&sh_hex_value);
      } else {
_ASSERT_UNCOND
      }
   }
  //## end cStyxParser::ParseFlags%1108111668.body
}

void cStyxParser::ParseOption (cContext *context, ShaciraOption *sh_option, cVarDef *var_def)
{
  //## begin cStyxParser::ParseFlags%1108111668.body preserve=yes
   ShaciraOptionValue sh_option_value;
   if (ShaciraOption_value(sh_option, &sh_option_value)) {
      GLS_Tok sh_nat_value;
      GLS_Tok sh_hex_value;
      if (ShaciraOptionValue_cnat(sh_option_value, &sh_nat_value)) {
         var_def->set_Option(NatValue(&sh_nat_value));
      } else if (ShaciraOptionValue_chex(sh_nat_value, &sh_hex_value)) {
         var_def->set_Option(HexValue(&sh_hex_value));
      } else {
_ASSERT_UNCOND
      }
   }
  //## end cStyxParser::ParseFlags%1108111668.body
}

cUnitDef * cStyxParser::ParseUnitDef (cContext *context, ShacUnitDef *sh_unit_def)
{
  //## begin cStyxParser::ParseUnitDef%1109752578.body preserve=yes
   GLS_Tok sh_unit_name;
   GLS_Tok sh_dataset;
   GLS_Tok sh_device;
   ShaciraFuncRef sh_func_ref;
   ShaciraDevState sh_devstate;
   ShaciraFuncRef sh_devstate_func_ref;
   cUnitDef * unit_def = new cUnitDef(SH_FLOAT, context);
   GLS_Lst(ShacUnitSpec) sh_unit_spec_list;
   GLS_Lst(ShacUnitSpec) sh_unit_spec_list_it;
   if (ShacUnitDef_def(sh_unit_def, &sh_unit_name, &sh_func_ref,
                       &sh_unit_spec_list,
                       &sh_dataset,
                       &sh_devstate)) {
      GLS_FORALL(sh_unit_spec_list_it, sh_unit_spec_list) {
         ShacUnitSpec sh_unit_spec = GLS_FIRST(ShacDefinition, sh_unit_spec_list_it);
         GLS_Tok sh_precision;
         GLS_Tok sh_unit_string;
         if (ShacUnitSpec_spec(sh_unit_spec, &sh_precision, &sh_unit_string)) {
            UCHAR_T precision = (UCHAR_T)NatValue(&sh_precision);
            STRING_T unit_text = StringValue(&sh_unit_string);
            unit_def->AddUnitSpec(unit_text.c_str(), precision);
         } else {
_ASSERT_UNCOND
         }
      }
      STRING_T unit_name = StringValue(&sh_unit_name);
      unit_def->_UnitName = unit_name;
      cFuncRef * func_ref = ParseFuncRef(context, (void**)sh_func_ref, UNDEFINED, SH_UNIT);
      unit_def->set_FuncRef(func_ref);
      UCHAR_T dataset_state = (UCHAR_T)NatValue(&sh_dataset);
      unit_def->set_DatasetState(dataset_state);

      if (ShaciraDevState_state1(sh_devstate, &sh_device)) {
         UCHAR_T device_state = (UCHAR_T)NatValue(&sh_device);
         unit_def->set_DeviceState(device_state);
      } else if (ShaciraDevState_state2(sh_devstate, &sh_devstate_func_ref)) {
         cFuncRef * devstate_func_ref = ParseFuncRef(context, (void**)sh_devstate_func_ref, UNDEFINED, SH_DEVICE_STATE);
         unit_def->set_DevStateFuncRef(devstate_func_ref);
      }

      context->AddUnitDef(unit_name.c_str(), unit_def);
      return unit_def;
   } else if (ShacUnitDef_defe(sh_unit_def, &sh_unit_name, &sh_func_ref,
                               &sh_unit_spec_list,
                               &sh_dataset, &sh_devstate)) {
      GLS_FORALL(sh_unit_spec_list_it, sh_unit_spec_list) {
         ShacUnitSpec sh_unit_spec = GLS_FIRST(ShacDefinition, sh_unit_spec_list_it);
         GLS_Tok sh_precision;
         GLS_Tok sh_unit_string;
         if (ShacUnitSpec_spec(sh_unit_spec, &sh_precision, &sh_unit_string)) {
            UCHAR_T precision = (UCHAR_T)NatValue(&sh_precision);
            STRING_T unit_text = StringValue(&sh_unit_string);
            unit_def->AddUnitSpec(unit_text.c_str(), precision);
         } else {
_ASSERT_UNCOND
         }
      }
      STRING_T unit_name = StringValue(&sh_unit_name);
      unit_def->_UnitName = unit_name;
      cFuncRef * func_ref = ParseFuncRef(context, (void**)sh_func_ref, UNDEFINED, SH_UNIT);
      unit_def->set_FuncRef(func_ref);
      UCHAR_T dataset_state = (UCHAR_T)NatValue(&sh_dataset);
      unit_def->set_DatasetState(dataset_state);
      unit_def->set_TargetDependent(true);

      if (ShaciraDevState_state1(sh_devstate, &sh_device)) {
         UCHAR_T device_state = (UCHAR_T)NatValue(&sh_device);
         unit_def->set_DeviceState(device_state);
      } else if (ShaciraDevState_state2(sh_devstate, &sh_devstate_func_ref)) {
         cFuncRef * devstate_func_ref = ParseFuncRef(context, (void**)sh_devstate_func_ref, UNDEFINED, SH_DEVICE_STATE);
         unit_def->set_DevStateFuncRef(devstate_func_ref);
      }

      context->AddUnitDef(unit_name.c_str(), unit_def);
      return unit_def;
   } else {
_ASSERT_UNCOND
   }
   return NULL;
  //## end cStyxParser::ParseUnitDef%1109752578.body
}

void cStyxParser::ParseUnitRef (cContext *context, ShacUnitRef *sh_unit_ref, cVarDef *var_def)
{
  //## begin cStyxParser::ParseUnitRef%1109752579.body preserve=yes
   GLS_Tok sh_string_value;
   GLS_Tok sh_ide_value;
   if (ShacUnitRef_ref1(sh_unit_ref, &sh_ide_value)) {
      cUnitDef * unit_def = context->UnitDef((const char *)GLS_Tok_string(sh_ide_value));
      if (unit_def != NULL) {
         var_def->set_UnitDef(unit_def);
      } else {
         ParseError(PARSE_UNIT_NOT_DECLARED, (void**)sh_ide_value);
      }
   } else if (ShacUnitRef_ref2(sh_unit_ref, &sh_string_value)) {
      var_def->_UnitText = (const char *)GLS_Tok_string(sh_string_value);
   }
  //## end cStyxParser::ParseUnitRef%1109752579.body
}

void cStyxParser::ParseSystemFlags (cContext *context, ShacSystemFlags *sh_system_flags, cVarDef *var_def)
{
  //## begin cStyxParser::ParseSystemFlags%1125675931.body preserve=yes
   GLS_Lst(ShacSystemFlag) sh_system_flag_list;
   GLS_Lst(ShacSystemFlag) sh_system_flag_list_it;
   if (ShacSystemFlags_value(sh_system_flags, &sh_system_flag_list)) {
      GLS_Tok flag_token;
      GLS_FORALL(sh_system_flag_list_it, sh_system_flag_list) {
         ShacSystemFlag sh_system_flag = GLS_FIRST(ShacSystemFlag, sh_system_flag_list_it);
         if (ShacSystemFlag_hread(sh_system_flag)) {
            var_def->_SystemFlags |= HOST_READ;
         } else if (ShacSystemFlag_hwrite(sh_system_flag)) {
            var_def->_SystemFlags |= HOST_WRITE;
         } else if (ShacSystemFlag_ofs1(sh_system_flag)) {
            var_def->_SystemFlags |= DIM1_OFFSET;
         } else if (ShacSystemFlag_ofs2(sh_system_flag)) {
            var_def->_SystemFlags |= DIM2_OFFSET;
         } else if (ShacSystemFlag_ofs3(sh_system_flag)) {
            var_def->_SystemFlags |= DIM3_OFFSET;
         } else if (ShacSystemFlag_ofs4(sh_system_flag)) {
            var_def->_SystemFlags |= DIM4_OFFSET;
         } else if (ShacSystemFlag_em63(sh_system_flag)) {
            var_def->_SystemFlags |= EM63_VARIABLE;
         } else {
_ASSERT_UNCOND
         }
      }
   }
  //## end cStyxParser::ParseSystemFlags%1125675931.body
}

void cStyxParser::ParseError (INT_T err_code, PT_Term *symbol, CONST_STRING_T param)
{
  //## begin cStyxParser::ParseError%1040992349.body preserve=yes
   int line = 0;
   STRING_T obj_name;
   STRING_T row = "?";
   STRING_T col = "?";
#ifdef CHECK_SYMBOL_TYPE
   if (symbol != NULL &&
       PT_isToken(symbol)) {
#else
   if (symbol != NULL) {
#endif
      obj_name = (const char *)GLS_Tok_string(symbol);
      row = cConvUtils::StringValue(PT_row(symbol));
      col = cConvUtils::StringValue(PT_col(symbol));
      line = PT_row(symbol);
   }
   if (_IDEActive) {
      cError error(err_code, 0, row.c_str(), col.c_str(), obj_name.c_str(), param);
      fprintf(stderr, "%s(%d) : error S%d : %s\n", _File.c_str(), line, err_code, (const char *)error);
      throw cError(PARSE_PARSING_ABORTED, 0);
   } else {
      throw cError(err_code, 0, row.c_str(), col.c_str(), obj_name.c_str(), param);
   }
  //## end cStyxParser::ParseError%1040992349.body
}

void cStyxParser::ParseError (INT_T err_code, int line, int column, CONST_STRING_T obj_name, CONST_STRING_T param)
{
  //## begin cStyxParser::ParseError%1129135545.body preserve=yes
   STRING_T row = cConvUtils::StringValue(line);
   STRING_T col = cConvUtils::StringValue(column);
   if (_IDEActive) {
      cError error(err_code, 0, row.c_str(), col.c_str(), obj_name, param);
      fprintf(stderr, "%s(%d) : error S%d : %s\n", _File.c_str(), line, err_code, (const char *)error);
      throw cError(PARSE_PARSING_ABORTED, 0);
   } else {
      throw cError(err_code, 0, row.c_str(), col.c_str(), obj_name, param);
   }
  //## end cStyxParser::ParseError%1129135545.body
}

void cStyxParser::ParseWarning (INT_T err_code, PT_Term *symbol, CONST_STRING_T param)
{
  //## begin cStyxParser::ParseWarning%1129134826.body preserve=yes
   int line = 0;
   STRING_T obj_name;
   STRING_T row = "?";
   STRING_T col = "?";
#ifdef CHECK_SYMBOL_TYPE
   if (symbol != NULL &&
       PT_isToken(symbol)) {
#else
   if (symbol != NULL) {
#endif
      obj_name = (const char *)GLS_Tok_string(symbol);
      row = cConvUtils::StringValue(PT_row(symbol));
      col = cConvUtils::StringValue(PT_col(symbol));
      line = PT_row(symbol);
   }
   if (_IDEActive) {
      cError error(err_code, 0, row.c_str(), col.c_str(), obj_name.c_str(), param);
      fprintf(stderr, "%s(%d) : warning S%d : %s\n", _File.c_str(), line, err_code, (const char *)error);
   } else {
      cError error(err_code, 0, row.c_str(), col.c_str(), obj_name.c_str(), param);
      InfoPrintf("%s(%d) : %s\n", _File.c_str(), line, (const char *)error);
   }
  //## end cStyxParser::ParseWarning%1129134826.body
}

void cStyxParser::ParseWarning (INT_T err_code, int line, int column, CONST_STRING_T obj_name, CONST_STRING_T param)
{
  //## begin cStyxParser::ParseWarning%1129135546.body preserve=yes
   STRING_T row = cConvUtils::StringValue(line);
   STRING_T col = cConvUtils::StringValue(column);
   if (_IDEActive) {
      cError error(err_code, 0, row.c_str(), col.c_str(), obj_name, param);
      fprintf(stderr, "%s(%d) : warning S%d ; %s\n", _File.c_str(), line, err_code, (const char *)error);
   } else {
      cError error(err_code, 0, row.c_str(), col.c_str(), obj_name, param);
      InfoPrintf("%s(%d) : %s\n", _File.c_str(), line, (const char *)error);
   }
  //## end cStyxParser::ParseWarning%1129135546.body
}

int cStyxParser::Line (PT_Term *symbol)
{
  //## begin cStyxParser::Line%1129135111.body preserve=yes
#ifdef CHECK_SYMBOL_TYPE
   if (symbol != NULL &&
       PT_isToken(symbol)) {
#else
   if (symbol != NULL) {
#endif
      return PT_row(symbol);
   }
   return 0;
  //## end cStyxParser::Line%1129135111.body
}

int cStyxParser::Column (PT_Term *symbol)
{
  //## begin cStyxParser::Column%1129135112.body preserve=yes
#ifdef CHECK_SYMBOL_TYPE
   if (symbol != NULL &&
       PT_isToken(symbol)) {
#else
   if (symbol != NULL) {
#endif
      return PT_col(symbol);
   }
   return 0;
  //## end cStyxParser::Column%1129135112.body
}

BOOL_T cStyxParser::IsDynamic (CONST_STRING_T var_name)
{
  //## begin cStyxParser::IsDynamic%1129142496.body preserve=yes
   STRING_MAP_T::const_iterator i = _DynamicVars.find(var_name);
   if (i == _DynamicVars.cend()) {
      return false;
   } else {
      return true;
   }
  //## end cStyxParser::IsDynamic%1129142496.body
}

// Additional Declarations
  //## begin cStyxParser%3E0C47C10368.declarations preserve=yes
  //## end cStyxParser%3E0C47C10368.declarations

//## begin module%3E0C47C10368.epilog preserve=yes
//## end module%3E0C47C10368.epilog
