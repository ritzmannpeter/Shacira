//## begin module%3E0031DC0265.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0031DC0265.cm

//## begin module%3E0031DC0265.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0031DC0265.cp

//## Module: cContext%3E0031DC0265; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cContext.cpp

//## begin module%3E0031DC0265.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3E0031DC0265.additionalIncludes

//## begin module%3E0031DC0265.includes preserve=yes
//## end module%3E0031DC0265.includes

// cSHProcess
#include "System/Process/cSHProcess.h"
// cProgress
#include "System/Objects/cProgress.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
// cVariable
#include "System/Database/cVariable.h"
// cFileContext
#include "System/Database/cFileContext.h"
// cFuncDecl
#include "System/Database/cFuncDecl.h"
// cFuncRef
#include "System/Database/cFuncRef.h"
// cInterfaceFilter
#include "System/Database/cInterfaceFilter.h"
// cUnitDef
#include "System/Database/cUnitDef.h"
// cRefCache
#include "System/Database/cRefCache.h"
// cSHFile
#include "System/Sys/cSHFile.h"
// cFileSystemUtils
#include "System/Sys/cFileSystemUtils.h"
// cControlStartCondition
#include "System/PLC/cControlStartCondition.h"
// cControlProcedure
#include "System/PLC/cControlProcedure.h"
// cControlProgram
#include "System/PLC/cControlProgram.h"
// cControlState
#include "System/PLC/cControlState.h"
// cInternalBridge
#include "System/Channel/cInternalBridge.h"
// cAdapter
#include "System/Channel/cAdapter.h"
// cChannel
#include "System/Channel/cChannel.h"
// cSubFile
#include "Control/LocalDatabase/cSubFile.h"
// cPersistenceChannel
#include "Control/LocalDatabase/cPersistenceChannel.h"
// cDataChangeAdapter
#include "Client/Adapters/cDataChangeAdapter.h"
// cStyxParser
#include "Language/cStyxParser.h"
//## begin module%3E0031DC0265.additionalDeclarations preserve=yes

/// PR 28.01.16 - added method read in a dataset from a file:
///               cContext * GetFileContextFromFile(CONST_STRING_T file_name);

//## end module%3E0031DC0265.additionalDeclarations


// Class cContext 








































cContext::cContext()
  //## begin cContext::cContext%.hasinit preserve=no
      : _ProcessId(0), _IsRootContext(false), _Created(false), _ShadowChanges(0), _RefCache(NULL), _Process(NULL), _EventChannel(NULL), _Dispatcher(NULL), _InternalBridge(NULL)
  //## end cContext::cContext%.hasinit
  //## begin cContext::cContext%.initialization preserve=yes
  //## end cContext::cContext%.initialization
{
  //## begin cContext::cContext%.body preserve=yes
   _RefCache = new cRefCache(this);
  //## end cContext::cContext%.body
}

cContext::cContext(const cContext &right)
  //## begin cContext::cContext%copy.hasinit preserve=no
      : _ProcessId(0), _IsRootContext(false), _Created(false), _ShadowChanges(0), _RefCache(NULL), _Process(NULL), _EventChannel(NULL), _Dispatcher(NULL), _InternalBridge(NULL)
  //## end cContext::cContext%copy.hasinit
  //## begin cContext::cContext%copy.initialization preserve=yes
  //## end cContext::cContext%copy.initialization
{
  //## begin cContext::cContext%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cContext::cContext%copy.body
}

cContext::cContext (cSHProcess *process, cConfigurationObject *config_obj)
  //## begin cContext::cContext%1122375230.hasinit preserve=no
      : _ProcessId(0), _IsRootContext(false), _Created(false), _ShadowChanges(0), _RefCache(NULL), _Process(NULL), _EventChannel(NULL), _Dispatcher(NULL), _InternalBridge(NULL)
  //## end cContext::cContext%1122375230.hasinit
  //## begin cContext::cContext%1122375230.initialization preserve=yes
  //## end cContext::cContext%1122375230.initialization
{
  //## begin cContext::cContext%1122375230.body preserve=yes
   _RefCache = new cRefCache(this);
   _Process = process;
   if (config_obj != NULL) {
      _IsRootContext = config_obj->PropertyValue("RootContext", _IsRootContext);
   }
  //## end cContext::cContext%1122375230.body
}

cContext::cContext (cSHProcess *process)
   : _ProcessId(0), _IsRootContext(true), _Created(false), _ShadowChanges(0), _RefCache(NULL), _Process(NULL), _EventChannel(NULL), _Dispatcher(NULL), _InternalBridge(NULL)
{
   _RefCache = new cRefCache(this);
   _Process = process;
}

cContext::~cContext()
{
  //## begin cContext::~cContext%.body preserve=yes
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      delete var_def;
      i++;
   }
   if (_RefCache != NULL) {
      delete _RefCache;
   }
  //## end cContext::~cContext%.body
}



//## Other Operations (implementation)
BOOL_T cContext::IsRemote ()
{
  //## begin cContext::IsRemote%1042447642.body preserve=yes
   return false;
  //## end cContext::IsRemote%1042447642.body
}

void cContext::Connect (ULONG_T if_type)
{
  //## begin cContext::Connect%1050753125.body preserve=yes
  //## end cContext::Connect%1050753125.body
}

void cContext::Create ()
{
  //## begin cContext::Create%1042447637.body preserve=yes
  //## end cContext::Create%1042447637.body
}

void cContext::CreateDynamic ()
{
  //## begin cContext::CreateDynamic%1090073689.body preserve=yes
  //## end cContext::CreateDynamic%1090073689.body
}

ULONG_T cContext::GetVarDefs (STRING_T &var_defs, ULONG_T if_type)
{
  //## begin cContext::GetVarDefs%1054726257.body preserve=yes
   return 0;
  //## end cContext::GetVarDefs%1054726257.body
}

cChannel * cContext::EventChannel ()
{
  //## begin cContext::EventChannel%1073299988.body preserve=yes
   return NULL;
  //## end cContext::EventChannel%1073299988.body
}

void cContext::Search (cContext *context)
{
  //## begin cContext::Search%1050753126.body preserve=yes
	_SearchContexts[context->_Name.c_str()] = context;
  //## end cContext::Search%1050753126.body
}

void cContext::LoadSymbols (CONST_STRING_T symbol_file)
{
  //## begin cContext::LoadSymbols%1054726255.body preserve=yes
   cSHFile file(symbol_file);
   if (!file.Exists()) throw cError(FILE_NOT_FOUND, 0, symbol_file);
   file.Open(FILE_ACCESS_READ_ONLY);
   STRING_T line;
static char symbol[0x500] = {0};
static char def_buf[0x500] = {0};
   LONG_T definition = 0;
   while (file.ReadLine(line)) {
      if (line.size() > 0) {
         memset(symbol, 0, sizeof(symbol));
         memset(def_buf, 0, sizeof(def_buf));
         int params = sscanf(line.c_str(), "#define %s %s", symbol, def_buf);
         if (params == 2) {
            if (strncmp(def_buf, "0x",2) == 0) {
               params = sscanf(line.c_str(), "#define %s %x", symbol, &definition);
            } else {
               params = sscanf(line.c_str(), "#define %s %d", symbol, &definition);
            }
            if (params == 2) {
               AddSymbolValue(symbol, definition);
            }
         }
      }
   }
  //## end cContext::LoadSymbols%1054726255.body
}

void cContext::AddSymbolValue (CONST_STRING_T symbol, LONG_T symbol_value)
{
  //## begin cContext::AddSymbolValue%1050432222.body preserve=yes
	_Symbols[symbol] = symbol_value;
  //## end cContext::AddSymbolValue%1050432222.body
}

LONG_T cContext::SymbolValue (CONST_STRING_T symbol)
{
  //## begin cContext::SymbolValue%1041261887.body preserve=yes
	LONG_MAP_T::const_iterator i = _Symbols.find(symbol);
	if (i == _Symbols.end()) {
		return UNDEFINED_SYMBOL_VALUE;
	} else {
		return (*i).second;
	}
  //## end cContext::SymbolValue%1041261887.body
}

void cContext::ParseDatabaseFromFile (CONST_STRING_T source)
{
  //## begin cContext::ParseDatabaseFromFile%1042447636.body preserve=yes
   STRING_T file = cFileSystemUtils::FullPath(source);
   if (!cFileSystemUtils::FileExists(file.c_str())) {
      throw cError(CONFIG_FILE_NOT_FOUND, 0, file.c_str());
   }
   cStyxParser parser;
   parser.set_Steps(2);
   parser.ParseDatabaseFromFile(this, file.c_str());
  //## end cContext::ParseDatabaseFromFile%1042447636.body
}

void cContext::ParseDatabaseFromString (CONST_STRING_T source)
{
  //## begin cContext::ParseDatabaseFromString%1090067637.body preserve=yes
   cStyxParser parser;
   parser.set_Steps(2);
   parser.ParseDatabaseFromString(this, source);
  //## end cContext::ParseDatabaseFromString%1090067637.body
}

void cContext::AddFuncDecl (CONST_STRING_T func_name, cFuncDecl *func_decl)
{
  //## begin cContext::AddFuncDecl%1040992370.body preserve=yes
   _FuncDecls[func_name] = func_decl;
  //## end cContext::AddFuncDecl%1040992370.body
}

void cContext::AddVarDef (CONST_STRING_T var_name, cVarDef *var_def)
{
  //## begin cContext::AddVarDef%1040992371.body preserve=yes
   cVarDef * old_var_def = VarDef(var_name);
   if (old_var_def != NULL &&
       var_def == old_var_def) {
   } else {
      _VarDefs[var_name] = var_def;
   }
  //## end cContext::AddVarDef%1040992371.body
}

void cContext::RemoveVarDef (CONST_STRING_T var_name)
{
  //## begin cContext::RemoveVarDef%1090223212.body preserve=yes
   cVarDef * old_var_def = VarDef(var_name);
   if (old_var_def != NULL) {
      _VarDefs.erase(var_name);
      delete old_var_def;
   }
  //## end cContext::RemoveVarDef%1090223212.body
}

void cContext::VariableNames (STRING_LIST_T &var_names)
{
  //## begin cContext::VariableNames%1042459998.body preserve=yes
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
   while (i != _VarDefs.end()) {
      cVarDef * var_def = (*i).second;
      var_names.push_back(var_def->_VarName.c_str());
      i++;
   }
  //## end cContext::VariableNames%1042459998.body
}

cVarDef * cContext::VarDef (CONST_STRING_T var_name)
{
  //## begin cContext::VarDef%1040992360.body preserve=yes
   std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.find(var_name);
   if (i == _VarDefs.end()) {
	   std::map<STRING_T, cContext*>::const_iterator j = _SearchContexts.begin();
		while (j != _SearchContexts.end()) {
			cVarDef * var_def = (*j).second->VarDef(var_name);
         if (var_def != NULL) {
            return var_def;
         }
			j++;
		}
		return NULL;
   } else {
      return (*i).second;
   }
  //## end cContext::VarDef%1040992360.body
}

cVarRef * cContext::VarRef (CONST_STRING_T spec, BOOL_T cached)
{
  //## begin cContext::VarRef%1050417247.body preserve=yes
   cVarRef * var_ref = NULL;
   if (cached) {
      var_ref = _RefCache->VarRef(spec);
   }
   if (var_ref == NULL) {
      cStyxParser parser;
      var_ref = parser.VarRef(this, spec);
      if (var_ref != NULL) {
         if (cached) {
            _RefCache->AddVarRef(spec, var_ref);
            var_ref->set_Cached(true);
         } else {
            var_ref->set_Cached(false);
         }
      }
   }
   return var_ref;
  //## end cContext::VarRef%1050417247.body
}

cVariable * cContext::Variable (CONST_STRING_T var_name)
{
  //## begin cContext::Variable%1042648651.body preserve=yes
   cVarDef * var_def = VarDef(var_name);
   if (var_def == NULL) {
      return NULL;
   } else {
      return var_def->_Variable;;
   }
  //## end cContext::Variable%1042648651.body
}

cVariable * cContext::Variable (LONG_T var_id)
{
  //## begin cContext::Variable%1092067701.body preserve=yes
   return NULL;
  //## end cContext::Variable%1092067701.body
}

void cContext::FunctionNames (STRING_LIST_T &func_names)
{
  //## begin cContext::FunctionNames%1042459997.body preserve=yes
   std::map<STRING_T, cFuncDecl*>::const_iterator i = _FuncDecls.begin();
   while (i != _FuncDecls.end()) {
      cFuncDecl * func_decl = (*i).second;
      func_names.push_back(func_decl->_FuncName.c_str());
      i++;
   }
  //## end cContext::FunctionNames%1042459997.body
}

cFuncDecl * cContext::FuncDecl (CONST_STRING_T func_name)
{
  //## begin cContext::FuncDecl%1040992359.body preserve=yes
   std::map<STRING_T, cFuncDecl*>::const_iterator i = _FuncDecls.find(func_name);
   if (i == _FuncDecls.end()) {
	   std::map<STRING_T, cContext*>::const_iterator j = _SearchContexts.begin();
		while (j != _SearchContexts.end()) {
			cFuncDecl * func_decl = (*j).second->FuncDecl(func_name);
			if (func_decl != NULL) return func_decl;
			j++;
		}
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cContext::FuncDecl%1040992359.body
}

cFuncRef * cContext::FuncRef (CONST_STRING_T spec)
{
  //## begin cContext::FuncRef%1050417248.body preserve=yes
   cFuncRef * func_ref = _RefCache->FuncRef(spec);
   if (func_ref == NULL) {
      cStyxParser parser;
      func_ref = parser.FuncRef(this, spec);
	   return func_ref;
   } else {
      return func_ref;
   }
  //## end cContext::FuncRef%1050417248.body
}

void cContext::ParseProgramFromFile (CONST_STRING_T source, BOOL_T dynamic)
{
  //## begin cContext::ParseProgramFromFile%1090073693.body preserve=yes
   STRING_T file = cFileSystemUtils::FullPath(source);
   if (!cFileSystemUtils::FileExists(file.c_str())) {
      throw cError(CONFIG_FILE_NOT_FOUND, 0, file.c_str());
   }
   cStyxParser parser;
   parser.ParseProgramFromString(this, source, dynamic);
  //## end cContext::ParseProgramFromFile%1090073693.body
}

void cContext::ParseProgramFromString (CONST_STRING_T source, BOOL_T dynamic)
{
  //## begin cContext::ParseProgramFromString%1090073694.body preserve=yes
   cStyxParser parser;
   parser.ParseProgramFromString(this, source, dynamic);
  //## end cContext::ParseProgramFromString%1090073694.body
}

void cContext::AddControlState (CONST_STRING_T state_name, cControlState *state)
{
  //## begin cContext::AddControlState%1060682986.body preserve=yes
   _States[state_name] = state;
   cVarDef * var_def = state->VarDef();
   if (var_def != NULL) {
      AddVarDef(state_name, var_def);
   }
  //## end cContext::AddControlState%1060682986.body
}

void cContext::AddControlProgram (CONST_STRING_T program_name, cControlProgram *program)
{
  //## begin cContext::AddControlProgram%1060682987.body preserve=yes
   _Programs[program_name] = program;
  //## end cContext::AddControlProgram%1060682987.body
}

void cContext::AddControlProcedure (CONST_STRING_T procedure_name, cControlProcedure *proc)
{
  //## begin cContext::AddControlProcedure%1060682988.body preserve=yes
   RemoveControlProcedure(procedure_name);
   _Procedures[procedure_name] = proc;
  //## end cContext::AddControlProcedure%1060682988.body
}

void cContext::RemoveControlProcedure (CONST_STRING_T procedure_name)
{
  //## begin cContext::RemoveControlProcedure%1090223213.body preserve=yes
   cControlProcedure * old_proc = Procedure(procedure_name);
   if (old_proc != NULL) {
      _Procedures.erase(procedure_name);
      delete old_proc;
   }
  //## end cContext::RemoveControlProcedure%1090223213.body
}

void cContext::AddControlStartCondition (CONST_STRING_T condition_name, cControlStartCondition *cond)
{
  //## begin cContext::AddControlStartCondition%1060682989.body preserve=yes
   _StartConditions[condition_name] = cond;
  //## end cContext::AddControlStartCondition%1060682989.body
}

void cContext::StateNames (STRING_LIST_T &state_names)
{
  //## begin cContext::StateNames%1060691311.body preserve=yes
   std::map<STRING_T, cControlState*>::const_iterator i = _States.begin();
   while (i != _States.end()) {
      cControlState * state = (*i).second;
      state_names.push_back(state->_StateName.c_str());
      i++;
   }
  //## end cContext::StateNames%1060691311.body
}

cControlState * cContext::State (CONST_STRING_T state_name)
{
  //## begin cContext::State%1060691312.body preserve=yes
   std::map<STRING_T, cControlState*>::const_iterator i = _States.find(state_name);
   if (i == _States.end()) {
		return NULL;
   } else {
      return (*i).second;
   }
  //## end cContext::State%1060691312.body
}

void cContext::ControlProgramNames (STRING_LIST_T &program_names)
{
  //## begin cContext::ControlProgramNames%1060691313.body preserve=yes
   std::map<STRING_T, cControlProgram*>::const_iterator i = _Programs.begin();
   while (i != _Programs.end()) {
      cControlProgram * program = (*i).second;
      program_names.push_back(program->Name().c_str());
      i++;
   }
  //## end cContext::ControlProgramNames%1060691313.body
}

cControlProgram * cContext::ControlProgram (CONST_STRING_T prog_name)
{
  //## begin cContext::ControlProgram%1060691314.body preserve=yes
   std::map<STRING_T, cControlProgram*>::const_iterator i = _Programs.find(prog_name);
   if (i == _Programs.end()) {
		return NULL;
   } else {
      return (*i).second;
   }
  //## end cContext::ControlProgram%1060691314.body
}

void cContext::ProcedureNames (STRING_LIST_T &proc_names)
{
  //## begin cContext::ProcedureNames%1060691315.body preserve=yes
   std::map<STRING_T, cControlProcedure*>::const_iterator i = _Procedures.begin();
   while (i != _Procedures.end()) {
      cControlProcedure * proc = (*i).second;
      proc_names.push_back(proc->Name().c_str());
      i++;
   }
  //## end cContext::ProcedureNames%1060691315.body
}

cControlProcedure * cContext::Procedure (CONST_STRING_T proc_name)
{
  //## begin cContext::Procedure%1060691316.body preserve=yes
   std::map<STRING_T, cControlProcedure*>::const_iterator i = _Procedures.find(proc_name);
   if (i == _Procedures.end()) {
		return NULL;
   } else {
      return (*i).second;
   }
  //## end cContext::Procedure%1060691316.body
}

void cContext::StartConditionNames (STRING_LIST_T &cond_names)
{
  //## begin cContext::StartConditionNames%1060691317.body preserve=yes
   std::map<STRING_T, cControlStartCondition*>::const_iterator i = _StartConditions.begin();
   while (i != _StartConditions.end()) {
      cControlStartCondition * start_cond = (*i).second;
      cond_names.push_back(start_cond->_ConditionName.c_str());
      i++;
   }
  //## end cContext::StartConditionNames%1060691317.body
}

cControlStartCondition * cContext::StartCondition (CONST_STRING_T cond_name)
{
  //## begin cContext::StartCondition%1060691318.body preserve=yes
   std::map<STRING_T, cControlStartCondition*>::const_iterator i = _StartConditions.find(cond_name);
   if (i == _StartConditions.end()) {
		return NULL;
   } else {
      return (*i).second;
   }
  //## end cContext::StartCondition%1060691318.body
}

ULONG_T cContext::Alarms (ULONG_T selection)
{
  //## begin cContext::Alarms%1089103361.body preserve=yes
   return 0;
  //## end cContext::Alarms%1089103361.body
}

ULONG_T cContext::Alarms (ULONG_T selection, ALARM_MAP_T &alarms)
{
  //## begin cContext::Alarms%1081425825.body preserve=yes
   return 0;
  //## end cContext::Alarms%1081425825.body
}

void cContext::ClearAlarm (ULONG_T ident, BOOL_T propagate)
{
  //## begin cContext::ClearAlarm%1081425826.body preserve=yes
  //## end cContext::ClearAlarm%1081425826.body
}

void cContext::ClearAlarms (BOOL_T propagate)
{
  //## begin cContext::ClearAlarms%1081425827.body preserve=yes
  //## end cContext::ClearAlarms%1081425827.body
}

void cContext::GetValue (CONST_STRING_T var_name, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::GetValue%1041514715.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      variable->Get(value, i1, i2, i3, i4, flags);
   }
  //## end cContext::GetValue%1041514715.body
}

void cContext::GetValue (CONST_STRING_T var_name, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::GetValue%1041514716.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      variable->Get(value, i1, i2, i3, i4, flags);
   }
  //## end cContext::GetValue%1041514716.body
}

void cContext::GetValue (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::GetValue%1041514717.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      variable->Get(value, i1, i2, i3, i4, flags);
   }
  //## end cContext::GetValue%1041514717.body
}

void cContext::Refresh (CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::Refresh%1133172776.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      variable->Refresh(i1, i2, i3, i4, flags);
   }
  //## end cContext::Refresh%1133172776.body
}

void cContext::SetValue (CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::SetValue%1041514718.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      variable->Set(value, i1, i2, i3, i4, flags);
   }
  //## end cContext::SetValue%1041514718.body
}

void cContext::SetValue (CONST_STRING_T var_name, LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::SetValue%1041514719.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      variable->Set(value, i1, i2, i3, i4, flags);
   }
  //## end cContext::SetValue%1041514719.body
}

void cContext::SetValue (CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::SetValue%1041514720.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      variable->Set(value, i1, i2, i3, i4, flags);
   }
  //## end cContext::SetValue%1041514720.body
}

void cContext::GetMinimum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMinimum%1089103377.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable != NULL) {
      variable->GetMinimum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMinimum%1089103377.body
}

void cContext::GetMinimum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMinimum%1089103378.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable != NULL) {
      variable->GetMinimum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMinimum%1089103378.body
}

void cContext::GetMinimum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMinimum%1089103379.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable != NULL) {
      variable->GetMinimum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMinimum%1089103379.body
}

void cContext::GetMaximum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMaximum%1089103383.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable != NULL) {
      variable->GetMaximum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMaximum%1089103383.body
}

void cContext::GetMaximum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMaximum%1089103384.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable != NULL) {
      variable->GetMaximum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMaximum%1089103384.body
}

void cContext::GetMaximum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMaximum%1089103385.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable != NULL) {
      variable->GetMaximum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMaximum%1089103385.body
}

void cContext::GetMinimum (LONG_T var_id, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMinimum%1089103380.body preserve=yes
   cVariable * variable = Variable(var_id);
   if (variable != NULL) {
      variable->GetMinimum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMinimum%1089103380.body
}

void cContext::GetMinimum (LONG_T var_id, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMinimum%1089103381.body preserve=yes
   cVariable * variable = Variable(var_id);
   if (variable != NULL) {
      variable->GetMinimum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMinimum%1089103381.body
}

void cContext::GetMinimum (LONG_T var_id, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMinimum%1089103382.body preserve=yes
   cVariable * variable = Variable(var_id);
   if (variable != NULL) {
      variable->GetMinimum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMinimum%1089103382.body
}

void cContext::GetMaximum (LONG_T var_id, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMaximum%1089103386.body preserve=yes
   cVariable * variable = Variable(var_id);
   if (variable != NULL) {
      variable->GetMaximum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMaximum%1089103386.body
}

void cContext::GetMaximum (LONG_T var_id, LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMaximum%1089103387.body preserve=yes
   cVariable * variable = Variable(var_id);
   if (variable != NULL) {
      variable->GetMaximum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMaximum%1089103387.body
}

void cContext::GetMaximum (LONG_T var_id, DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::GetMaximum%1089103388.body preserve=yes
   cVariable * variable = Variable(var_id);
   if (variable != NULL) {
      variable->GetMaximum(value, i1, i2, i3, i4);
   } else {
   }
  //## end cContext::GetMaximum%1089103388.body
}

void cContext::GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value)
{
  //## begin cContext::GetDeviceValue%1082984450.body preserve=yes
  //## end cContext::GetDeviceValue%1082984450.body
}

void cContext::GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, BOOL_T &value)
{
  //## begin cContext::GetDeviceValue%1083004733.body preserve=yes
   STRING_T svalue;
   GetDeviceValue(buf_spec, address, svalue);
   if (IDENTIFIER_EQUAL(svalue.c_str(), "true")) {
      value = true;
   } else if (IDENTIFIER_EQUAL(svalue.c_str(), "false")) {
      value = false;
   }
  //## end cContext::GetDeviceValue%1083004733.body
}

void cContext::GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, LONG_T &value)
{
  //## begin cContext::GetDeviceValue%1082984451.body preserve=yes
   STRING_T svalue;
   GetDeviceValue(buf_spec, address, svalue);
   if (svalue.size() > 0) {
      value = atol(svalue.c_str());
   }
  //## end cContext::GetDeviceValue%1082984451.body
}

void cContext::GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, DOUBLE_T &value)
{
  //## begin cContext::GetDeviceValue%1082984452.body preserve=yes
   STRING_T svalue;
   GetDeviceValue(buf_spec, address, svalue);
   if (svalue.size() > 0) {
      value = atof(svalue.c_str());
   }
  //## end cContext::GetDeviceValue%1082984452.body
}

void cContext::SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value)
{
  //## begin cContext::SetDeviceValue%1082984453.body preserve=yes
  //## end cContext::SetDeviceValue%1082984453.body
}

void cContext::SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, LONG_T value)
{
  //## begin cContext::SetDeviceValue%1082984454.body preserve=yes
   char svalue[64] = {0};
   SafePrintf(svalue, sizeof(svalue), "%d", value);
   SetDeviceValue(buf_spec, address, svalue);
  //## end cContext::SetDeviceValue%1082984454.body
}

void cContext::SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, DOUBLE_T value)
{
  //## begin cContext::SetDeviceValue%1082984455.body preserve=yes
   char svalue[64] = {0};
   SafePrintf(svalue, sizeof(svalue), "%f", value);
   SetDeviceValue(buf_spec, address, svalue);
  //## end cContext::SetDeviceValue%1082984455.body
}

void cContext::ExecuteCommand (CONST_STRING_T program_name, ULONG_T command)
{
  //## begin cContext::ExecuteCommand%1089292610.body preserve=yes
  //## end cContext::ExecuteCommand%1089292610.body
}

void cContext::ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request)
{
  //## begin cContext::ExecuteRequest%1133771770.body preserve=yes
  //## end cContext::ExecuteRequest%1133771770.body
}

void cContext::Save (UCHAR_T refresh_type, ULONG_T refresh_value)
{
  //## begin cContext::Save%1092293194.body preserve=yes
  //## end cContext::Save%1092293194.body
}

void cContext::Download (ULONG_T ctrl)
{
  //## begin cContext::Download%1091687830.body preserve=yes
  //## end cContext::Download%1091687830.body
}

void cContext::Upload (ULONG_T ctrl)
{
  //## begin cContext::Upload%1091687831.body preserve=yes
  //## end cContext::Upload%1091687831.body
}

void cContext::ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_files, STRING_T &buf)
{
   //## begin cContext::ReadFile%1091699603.body preserve=yes
   //## end cContext::ReadFile%1091699603.body
}

void cContext::ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_files, cStringBuffer &buf)
{
}

void cContext::WriteFile(CONST_STRING_T file_name, CONST_STRING_T sub_files, CONST_STRING_T buf)
{
  //## begin cContext::WriteFile%1091699604.body preserve=yes
  //## end cContext::WriteFile%1091699604.body
}

void cContext::Copy (cContext *src_context, CONST_STRING_T sub_file, BOOL_T show_errors, BOOL_T buffered)
{
  //## begin cContext::Copy%1091957520.body preserve=yes
  //## end cContext::Copy%1091957520.body
}

void cContext::SetJob (cJobSpec *job_spec)
{
  //## begin cContext::SetJob%1093930659.body preserve=yes
  //## end cContext::SetJob%1093930659.body
}

cJobSpec * cContext::GetJobSpec (CONST_STRING_T job_name)
{
  //## begin cContext::GetJobSpec%1093930660.body preserve=yes
   return NULL;
  //## end cContext::GetJobSpec%1093930660.body
}

void cContext::CopyCommand (ULONG_T src, ULONG_T dst, BOOL_T exchange, ULONG_T copy_flags)
{
  //## begin cContext::CopyCommand%1100714370.body preserve=yes
  //## end cContext::CopyCommand%1100714370.body
}

STRING_T cContext::Compare (ULONG_T flags)
{
  //## begin cContext::Compare%1108566001.body preserve=yes
   return "";
  //## end cContext::Compare%1108566001.body
}

cContext * cContext::GetFileContext (CONST_STRING_T file_name, BOOL_T header_only)
{
  //## begin cContext::GetFileContext%1101987270.body preserve=yes
   STRING_T file = cFileSystemUtils::FullPath(file_name) ;
   cSHFile _file(file.c_str());
   if (_file.Exists()) {
      STRING_T buf = _file.ToString();
      if (buf.empty()) return NULL;

      cFileContext * file_context = new cFileContext;
      try {
         cStyxParser parser;
         if (header_only) {
            STRING_T header = GetHeader(buf.c_str());
            parser.ParseDBLiteFromString(file_context, header.c_str());
         } else {
            parser.ParseDBLiteFromString(file_context, buf.c_str());
         }
         file_context->Create();
         return file_context;
      } catch (cError & e) {
         ErrorPrintf("%s while parsing %s\n", (const char *)e, file.c_str());
         delete file_context;
         return NULL;
      } catch (...) {
         ErrorPrintf("unhandled exception while parsing %s\n", file.c_str());
         delete file_context;
         return NULL;
      }
   } else {
      return NULL;
   }
  //## end cContext::GetFileContext%1101987270.body
}

cContext * cContext::GetFileContextFromString (CONST_STRING_T dataset, BOOL_T header_only)
{
  //## begin cContext::GetFileContextFromString%1136199171.body preserve=yes
   if (!strcmp(dataset, "")) return NULL;

   cFileContext * file_context = new cFileContext;
   try {
      cStyxParser parser;
      if (header_only) {
         STRING_T header = GetHeader(dataset);
         parser.ParseDBLiteFromString(file_context, header.c_str());
      } else {
         parser.ParseDBLiteFromString(file_context, dataset);
      }
      file_context->Create();
      return file_context;
   } catch (cError & e) {
      ErrorPrintf("%s parsing file context from string\n", (const char *)e);
      delete file_context;
      return NULL;
   } catch (...) {
      ErrorPrintf("unhandled exception parsing parsing file context from string\n");
      delete file_context;
      return NULL;
   }
  //## end cContext::GetFileContextFromString%1136199171.body
}

cContext * cContext::GetFileContextFromFile(CONST_STRING_T file_name)
{
   STRING_T file = cFileSystemUtils::FullPath(file_name);
   cSHFile _file(file.c_str());
   if (_file.Exists()) {
      cFileContext * file_context = new cFileContext;
      try {
         cStyxParser parser;
         parser.ParseDatabaseFromFile(file_context, file_name);
         file_context->Create();
         return file_context;
      } catch (cError & e) {
         ErrorPrintf("%s while parsing %s\n", (const char *)e, file.c_str());
         delete file_context;
         return NULL;
      } catch (...) {
         ErrorPrintf("unhandled exception while parsing %s\n", file.c_str());
         delete file_context;
         return NULL;
      }
   } else {
      return NULL;
   }
}

BOOL_T cContext::RegisterVarRefs(cDataChangeAdapter *adapter)
{
  //## begin cContext::RegisterVarRefs%1108559439.body preserve=yes
   if (_RefCache != NULL) {
      return _RefCache->RegisterVarRefs(adapter);
   } else {
      return false;
   }
  //## end cContext::RegisterVarRefs%1108559439.body
}

cUnitDef * cContext::UnitDef (CONST_STRING_T unit_name)
{
  //## begin cContext::UnitDef%1109752576.body preserve=yes
   std::map<STRING_T, cUnitDef*>::const_iterator i = _UnitDefs.find(unit_name);
   if (i == _UnitDefs.end()) {
		return NULL;
   } else {
      return (*i).second;
   }
  //## end cContext::UnitDef%1109752576.body
}

void cContext::AddUnitDef (CONST_STRING_T unit_name, cUnitDef *unit_def)
{
  //## begin cContext::AddUnitDef%1109752577.body preserve=yes
   _UnitDefs[unit_name] = unit_def;
  //## end cContext::AddUnitDef%1109752577.body
}

void cContext::SetUnit (CONST_STRING_T unit_name, UCHAR_T selection)
{
  //## begin cContext::SetUnit%1109785975.body preserve=yes
   cUnitDef * unit_def = UnitDef(unit_name);
   if (unit_def != NULL) {
      unit_def->SetState(selection);
   } else {
	   std::map<STRING_T, cContext*>::const_iterator j = _SearchContexts.begin();
		while (j != _SearchContexts.end()) {
         cContext * context = (*j).second;
         if (context != NULL) {
            unit_def = context->UnitDef(unit_name);
            if (unit_def != NULL) {
               unit_def->SetState(selection);
            }
         }
         j++;
		}
   }
  //## end cContext::SetUnit%1109785975.body
}

cSHProcess * cContext::Process ()
{
  //## begin cContext::Process%1117632421.body preserve=yes
   return _Process;
  //## end cContext::Process%1117632421.body
}

STRING_T cContext::GetHeader (CONST_STRING_T buf)
{
  //## begin cContext::GetHeader%1102334008.body preserve=yes
#define HEADER_DB "database Header"
#define H_INIT    0
#define H_PRE_DB  1
#define H_IN_DB   2

   ULONG_T depth = 0;
   UCHAR_T state = H_INIT;
   STRING_T header;
   CONST_STRING_T src_ptr = buf;
   ULONG_T buf_size = strlen(buf);
   for (ULONG_T i=0; i<buf_size; i++) {
      if (state == H_INIT) {
         if (strnicmp(src_ptr, HEADER_DB, strlen(HEADER_DB)) == 0) {
            header = HEADER_DB;
            src_ptr += strlen(HEADER_DB);
            state = H_PRE_DB;
         }
         src_ptr++;
      } else if (state == H_PRE_DB) {
         if (*src_ptr == '{') {
            state = H_IN_DB;
            depth = 1;
         }
         header += *(src_ptr);
         src_ptr++;
      } else if (state == H_IN_DB) {
         if (*src_ptr == '}') {
            depth--;
         } else if (*src_ptr == '{') {
            depth++;
         }
         if (depth == 0) {
            header += "};";
            return header;
         } else {
            header += *(src_ptr);
            src_ptr++;
         }
      }
   }
   return buf;
  //## end cContext::GetHeader%1102334008.body
}

void cContext::SetProgress (ULONG_T indicator, ULONG_T value)
{
  //## begin cContext::SetProgress%1122375231.body preserve=yes
#ifndef BASE_LIBRARY
   if (_Dispatcher != NULL) {
      cProgress * progress = new cProgress(this, indicator, value);
      _Dispatcher->Send(progress);
      progress->Release();
   }
#endif
   //## end cContext::SetProgress%1122375231.body
}

cPersistenceChannel * cContext::PersistenceChannel ()
{
  //## begin cContext::PersistenceChannel%1122375233.body preserve=yes
   return NULL;
  //## end cContext::PersistenceChannel%1122375233.body
}

void cContext::Send (cTransientObject *object)
{
  //## begin cContext::Send%1122638220.body preserve=yes
   throw cError(METHOD_NOT_OVERLOADED, 0, __FILE__, cConvUtils::StringValue(__LINE__).c_str());
  //## end cContext::Send%1122638220.body
}

BOOL_T cContext::IsActive ()
{
  //## begin cContext::IsActive%1125662157.body preserve=yes
   return _Created;
  //## end cContext::IsActive%1125662157.body
}

BOOL_T cContext::IsConnected ()
{
  //## begin cContext::IsConnected%1134147948.body preserve=yes
   return true;
  //## end cContext::IsConnected%1134147948.body
}

BOOL_T cContext::Ping ()
{
  //## begin cContext::Ping%1134227771.body preserve=yes
   return true;
  //## end cContext::Ping%1134227771.body
}

void cContext::AddFilter (ULONG_T if_type, cInterfaceFilter *filter)
{
  //## begin cContext::AddFilter%1141197872.body preserve=yes
   _Filters[if_type] = filter;
  //## end cContext::AddFilter%1141197872.body
}

void cContext::RemoveFilter (ULONG_T if_type)
{
  //## begin cContext::RemoveFilter%1141197873.body preserve=yes
   _Filters.erase(if_type);
  //## end cContext::RemoveFilter%1141197873.body
}

void cContext::DefFilter (ULONG_T if_type, cVarDef *var_def)
{
  //## begin cContext::DefFilter%1141208304.body preserve=yes
   cInterfaceFilter * filter = Filter(if_type);
   if (filter != NULL) {
      filter->DefFilter(this, if_type, var_def);
   }
  //## end cContext::DefFilter%1141208304.body
}

void cContext::RefFilter (ULONG_T if_type, STRING_T &var_name, LONG_T &i1, LONG_T &i2, LONG_T &i3, LONG_T &i4)
{
  //## begin cContext::RefFilter%1141202703.body preserve=yes
   cInterfaceFilter * filter = Filter(if_type);
   if (filter != NULL) {
      filter->RefFilter(var_name, i1, i2, i3, i4);
   }
  //## end cContext::RefFilter%1141202703.body
}

cVarRef * cContext::FilteredVarRef (ULONG_T if_type, CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
  //## begin cContext::FilteredVarRef%1141230223.body preserve=yes
   cVarRef * var_ref = NULL;
   cInterfaceFilter * filter = Filter(if_type);
   if (filter != NULL) {
      var_ref = filter->FilteredVarRef(this, var_name, i1, i2, i3, i4);
   }
   if (var_ref != NULL) {
      return var_ref;
   } else {
      char var_spec[0x200] = {0};
      if (i1 == -1) {
         SafePrintf(var_spec, sizeof(var_spec), "%s", var_name);
      } else if (i2 == -1) {
         SafePrintf(var_spec, sizeof(var_spec), "%s[%d]", var_name, i1);
      } else if (i3 == -1) {
         SafePrintf(var_spec, sizeof(var_spec), "%s[%d][%d]", var_name, i1, i2);
      } else if (i4 == -1) {
         SafePrintf(var_spec, sizeof(var_spec), "%s[%d][%d][%d]", var_name, i1, i2, i3);
      } else {
         SafePrintf(var_spec, sizeof(var_spec), "%s[%d][%d][%d][%d]", var_name, i1, i2, i3, i4);
      }
      return VarRef(var_spec);
   }
  //## end cContext::FilteredVarRef%1141230223.body
}

cInterfaceFilter * cContext::Filter (ULONG_T if_type)
{
  //## begin cContext::Filter%1141664738.body preserve=yes
   FILTER_MAP_T::const_iterator i = _Filters.find(if_type);
   if (i != _Filters.end()) {
      return (*i).second;
   } else {
      return NULL;
   }
  //## end cContext::Filter%1141664738.body
}

ULONG_T cContext::ShadowChanges ()
{
  //## begin cContext::ShadowChanges%1191857051.body preserve=yes
   return _ShadowChanges;
  //## end cContext::ShadowChanges%1191857051.body
}

void cContext::AlterShadowChanges (LONG_T step)
{
  //## begin cContext::AlterShadowChanges%1191857052.body preserve=yes
   LONG_T shadow_changes = _ShadowChanges;
   shadow_changes += step;
   if (shadow_changes >= 0) {
      _ShadowChanges = shadow_changes;
   }
  //## end cContext::AlterShadowChanges%1191857052.body
}

void cContext::SetShadowChanges (ULONG_T value)
{
  //## begin cContext::SetShadowChanges%1191857053.body preserve=yes
   _ShadowChanges = value;
  //## end cContext::SetShadowChanges%1191857053.body
}

void cContext::ResetShadowBuffers ()
{
  //## begin cContext::ResetShadowBuffers%1191857054.body preserve=yes
   if (cResources::FlagSet(PF_ENABLE_SHADOW_DATASET)) {
      std::map<STRING_T, cVarDef*>::const_iterator i = _VarDefs.begin();
      while (i != _VarDefs.end()) {
         cVarDef * var_def = (*i).second;
         cVariable * variable = var_def->_Variable;
         if (variable != NULL)
            variable->ResetShadowBuffer();
         i++;
      }
   }
  //## end cContext::ResetShadowBuffers%1191857054.body
}

ULONG_T cContext::GetObject (CONST_STRING_T var_name, cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::GetObject%1238478450.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      return variable->GetObject(object, i1, i2, i3, i4, flags);
   }
  //## end cContext::GetObject%1238478450.body
}

void cContext::SetObject (CONST_STRING_T var_name, const cBinaryObject &object, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags)
{
  //## begin cContext::SetObject%1238478451.body preserve=yes
   cVariable * variable = Variable(var_name);
   if (variable == NULL) {
      throw cError(VARIABLE_NOT_FOUND, 0, var_name);
   } else {
      variable->SetObject(object, i1, i2, i3, i4, flags);
   }
  //## end cContext::SetObject%1238478451.body
}

void cContext::ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async)
{
  //## begin cContext::ExecuteJob%1244547093.body preserve=yes
  //## end cContext::ExecuteJob%1244547093.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cContext::get_ProcessId () const
{
  //## begin cContext::get_ProcessId%403B4A190280.get preserve=no
  return _ProcessId;
  //## end cContext::get_ProcessId%403B4A190280.get
}

void cContext::set_ProcessId (ULONG_T value)
{
  //## begin cContext::set_ProcessId%403B4A190280.set preserve=no
  _ProcessId = value;
  //## end cContext::set_ProcessId%403B4A190280.set
}

BOOL_T cContext::get_IsRootContext () const
{
  //## begin cContext::get_IsRootContext%42E909150213.get preserve=no
  return _IsRootContext;
  //## end cContext::get_IsRootContext%42E909150213.get
}

void cContext::set_IsRootContext (BOOL_T value)
{
  //## begin cContext::set_IsRootContext%42E909150213.set preserve=no
  _IsRootContext = value;
  //## end cContext::set_IsRootContext%42E909150213.set
}

STRING_T cContext::get_CellName () const
{
  //## begin cContext::get_CellName%4393E7390323.get preserve=no
  return _CellName;
  //## end cContext::get_CellName%4393E7390323.get
}

// Additional Declarations
  //## begin cContext%3E0031DC0265.declarations preserve=yes
UI_UPDATE_FUNCTION_T cContext::_UiUpdateFunction = NULL;
void cContext::SetUiUpdateFunction(UI_UPDATE_FUNCTION_T function)
{
   _UiUpdateFunction = function;
}

void cContext::UpdateUi()
{
   if (_UiUpdateFunction != NULL) {
      _UiUpdateFunction();
   }
}

UI_UPDATE_FUNCTION_T cContext::GetUiUpdateFuntion()
{ 
   return _UiUpdateFunction;
}

  //## end cContext%3E0031DC0265.declarations

//## begin module%3E0031DC0265.epilog preserve=yes
//## end module%3E0031DC0265.epilog
