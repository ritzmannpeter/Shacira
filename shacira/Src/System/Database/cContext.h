//## begin module%3E0031DC0265.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0031DC0265.cm

//## begin module%3E0031DC0265.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0031DC0265.cp

//## Module: cContext%3E0031DC0265; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cContext.h

#ifndef cContext_h
#define cContext_h 1

//## begin module%3E0031DC0265.includes preserve=yes
#include "System/Database/cBinaryObject.h"
#include "System/Database/RootContext.h"
//## end module%3E0031DC0265.includes

// cAlarm
#include "System/Objects/cAlarm.h"
// cStaticObject
#include "System/Objects/cStaticObject.h"
// cUnitDef
#include "System/Database/cUnitDef.h"

class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cProgress;
class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cVariable;
class __DLL_EXPORT__ cFileContext;
class __DLL_EXPORT__ cFuncDecl;
class __DLL_EXPORT__ cFuncRef;
class __DLL_EXPORT__ cInterfaceFilter;
class __DLL_EXPORT__ cUnitDef;
class __DLL_EXPORT__ cRefCache;
class __DLL_EXPORT__ cSHFile;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cControlStartCondition;
class __DLL_EXPORT__ cControlProcedure;
class __DLL_EXPORT__ cControlProgram;
class __DLL_EXPORT__ cControlState;
class __DLL_EXPORT__ cInternalBridge;
class __DLL_EXPORT__ cAdapter;
class __DLL_EXPORT__ cChannel;
class __DLL_EXPORT__ cSubFile;
class __DLL_EXPORT__ cPersistenceChannel;
class __DLL_EXPORT__ cDataChangeAdapter;
class __DLL_EXPORT__ cStyxParser;

//## begin module%3E0031DC0265.additionalDeclarations preserve=yes

#define UNDEFINED_SYMBOL_VALUE	-1

typedef std::map<STRING_T,cAdapter*> ADAPTER_MAP_T;
typedef std::map<ULONG_T,cInterfaceFilter*> FILTER_MAP_T;
typedef void (*UI_UPDATE_FUNCTION_T)();

//## end module%3E0031DC0265.additionalDeclarations


//## begin cContext%3E0031DC0265.preface preserve=yes
//## end cContext%3E0031DC0265.preface

//## Class: cContext%3E0031DC0265
//	Ths class enables access to the resources of a
//	manufacturing cell. cContext is an abstract base class.
//	A concrete implementation can be of type cRemoteContext
//	that offers remote access to cell ressources, cFile
//	Context that offer access to ressources stored in a file
//	or cLocalContext that houses a manufacturing cell
//	object. The factory object for cContext classes is a
//	process object of type cSHProcess.
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E259F98023E;cVariable { -> F}
//## Uses: <unnamed>%3E9C189402AF;cVarRef { -> F}
//## Uses: <unnamed>%3E9C18A60242;cFuncRef { -> F}
//## Uses: <unnamed>%3E9C2654034B;cStyxParser { -> F}
//## Uses: <unnamed>%3EA9350300DA;cFileSystemUtils { -> F}
//## Uses: <unnamed>%3EDDC42301F4;cConfigurationObject { -> F}
//## Uses: <unnamed>%3EE062330000;cSHFile { -> F}
//## Uses: <unnamed>%3F86C60401B5;cAdapter { -> F}
//## Uses: <unnamed>%4075496E01C5;cAlarm { -> }
//## Uses: <unnamed>%41AF003B0196;cFileContext { -> F}
//## Uses: <unnamed>%4213462603A9;cDataChangeAdapter { -> F}
//## Uses: <unnamed>%42E643B70271;cProgress { -> F}
//## Uses: <unnamed>%42E6452201F4;cSubFile { -> F}
//## Uses: <unnamed>%42E9DBCA02EE;cPersistenceChannel { -> F}
//## Uses: <unnamed>%44054B3A0352;cInterfaceFilter { -> F}

class __DLL_EXPORT__ cContext : public cStaticObject  //## Inherits: <unnamed>%400EC51A02CE
{
  //## begin cContext%3E0031DC0265.initialDeclarations preserve=yes
public:
  //## end cContext%3E0031DC0265.initialDeclarations

    //## Constructors (generated)
      cContext();

      cContext(const cContext &right);

    //## Constructors (specified)
      //## Operation: cContext%1122375230
      cContext (cSHProcess *process, cConfigurationObject *config_obj);
      cContext (cSHProcess *process);

    //## Destructor (generated)
      virtual ~cContext();


    //## Other Operations (specified)
      //## Operation: IsRemote%1042447642
      //	Is this Context a remote context ?
      //	Returns true if the concrete context is a remote
      //	context, false oterwise.
      virtual BOOL_T IsRemote ();

      //## Operation: Connect%1050753125
      //	Connect connects to a remote context. It is implemented
      //	by local contexts as well as by remote contexts.
      //	Connecting to a local context does not activate any
      //	functionality. Connecting to a remote context includes
      //	the connection functionality of the underllying
      //	middleware.
      //	Should not be used by a context user.
      virtual void Connect (ULONG_T if_type = 0);

      //## Operation: Create%1042447637
      //	Create is in the sane way as the Connect method
      //	implemented in different ways by local or remote
      //	contexts. Local contexts in general will allocate
      //	necessary resources when the Create method is executed
      //	(creates storage for variables for example).
      //	Should not be used by a context user.
      virtual void Create ();

      //## Operation: CreateDynamic%1090073689
      virtual void CreateDynamic ();

      //## Operation: GetVarDefs%1054726257
      //	Gets all variable definitions as a list of serialized
      //	objects. This method is used to exchange variable type
      //	information.
      //	Should not be used by a context user.
      virtual ULONG_T GetVarDefs (STRING_T &var_defs, ULONG_T if_type = 0);

      //## Operation: EventChannel%1073299988
      //	Returns the event channel object associated with the
      //	"slow" event channel of a context.
      virtual cChannel * EventChannel ();

      //## Operation: Search%1050753126
      //	Adds an additional context to the context. The added
      //	context will be searched for variables and functions.
      //	The number of search contexts associated with a context
      //	is not restricted.
      void Search (cContext *context);

      //## Operation: LoadSymbols%1054726255
      //	Loads symbol information from a symbol file.
      //	Symbols are used to map mnemonic names to numeric ids
      //	like addresses.
      //	Should not be used by a context user.
      void LoadSymbols (CONST_STRING_T symbol_file);

      //## Operation: AddSymbolValue%1050432222
      //	Adds a symbol value to the context.
      //	Should not be used by a context user.
      void AddSymbolValue (CONST_STRING_T symbol, LONG_T symbol_value);

      //## Operation: SymbolValue%1041261887
      //	Returns the value of the symbol specified by the
      //	argument symbol.
      LONG_T SymbolValue (CONST_STRING_T symbol);

      //## Operation: ParseDatabaseFromFile%1042447636
      //	Parses sddl descriptions from a file.
      void ParseDatabaseFromFile (CONST_STRING_T source);

      //## Operation: ParseDatabaseFromString%1090067637
      //	Parses sddl descriptions from a string.
      void ParseDatabaseFromString (CONST_STRING_T source);

      //## Operation: AddFuncDecl%1040992370
      //	Adds a function declaration to the context.
      //	Should not be used by a context user.
      void AddFuncDecl (CONST_STRING_T func_name, cFuncDecl *func_decl);

      //## Operation: AddVarDef%1040992371
      //	Adds a variable definition to the context.
      //	Should not be used by a context user.
      void AddVarDef (CONST_STRING_T var_name, cVarDef *var_def);

      //## Operation: RemoveVarDef%1090223212
      //	Removes a variable definition from the context. All
      //	resources are removed.
      void RemoveVarDef (CONST_STRING_T var_name);

      //## Operation: VariableNames%1042459998
      //	Returns the names of all variables defined within this
      //	context.
      void VariableNames (STRING_LIST_T &var_names);

      //## Operation: VarDef%1040992360
      //	Returns a variable definition object of the variable
      //	with name var_name if it exists in the context. Returns
      //	NULL otherwise.
      cVarDef * VarDef (CONST_STRING_T var_name);

      //## Operation: VarRef%1050417247
      //	This method trys to parse the argument spec to build a
      //	valid refrence. When the method succeeds it returns a
      //	variable reference that can be used to set and get
      //	variable values and that can be registered for data
      //	changes occuring in the scope of the variable.
      cVarRef * VarRef (CONST_STRING_T spec, BOOL_T cached = true);

      //## Operation: Variable%1042648651
      //	Returns a variable object of the variable with name var_
      //	name if it exists in the context. Returns NULL otherwise.
      cVariable * Variable (CONST_STRING_T var_name);

      //## Operation: Variable%1092067701
      //	Returns a variable object of the variable with name var_
      //	name if it exists in the context. Returns NULL otherwise.
      cVariable * Variable (LONG_T var_id);

      //## Operation: FunctionNames%1042459997
      //	Returns the names of all functions declared within this
      //	context.
      void FunctionNames (STRING_LIST_T &func_names);

      //## Operation: FuncDecl%1040992359
      //	Returns a function declaration object of the function
      //	with name function_name if it exists in the context.
      //	Returns NULL otherwise.
      cFuncDecl * FuncDecl (CONST_STRING_T func_name);

      //## Operation: FuncRef%1050417248
      //	This method trys to parse the argument spec to build a
      //	valid function refrence. When the method isucceeds it
      //	returns a function reference that can be used to  get
      //	function values.
      cFuncRef * FuncRef (CONST_STRING_T spec);

      //## Operation: ParseProgramFromFile%1090073693
      //	Parses an scpl program from a file.
      void ParseProgramFromFile (CONST_STRING_T source, BOOL_T dynamic = true);

      //## Operation: ParseProgramFromString%1090073694
      //	Parses an scpl program from a string.
      void ParseProgramFromString (CONST_STRING_T source, BOOL_T dynamic = true);

      //## Operation: AddControlState%1060682986
      //	Adds a control state to the context.
      //	Should not be used by a context user.
      void AddControlState (CONST_STRING_T state_name, cControlState *state);

      //## Operation: AddControlProgram%1060682987
      //	Adds a control program to the context.
      //	Should not be used by a context user.
      void AddControlProgram (CONST_STRING_T program_name, cControlProgram *program);

      //## Operation: AddControlProcedure%1060682988
      //	Adds a control procedure to the context.
      //	Should not be used by a context user.
      void AddControlProcedure (CONST_STRING_T procedure_name, cControlProcedure *proc);

      //## Operation: RemoveControlProcedure%1090223213
      //	Removes a control procedure from the context including
      //	all dependent resources.
      void RemoveControlProcedure (CONST_STRING_T procedure_name);

      //## Operation: AddControlStartCondition%1060682989
      //	Adds a control start condition to the context.
      //	Should not be used by a context user.
      void AddControlStartCondition (CONST_STRING_T condition_name, cControlStartCondition *cond);

      //## Operation: StateNames%1060691311
      //	Returns the names of all state variables defined within
      //	this context.
      void StateNames (STRING_LIST_T &state_names);

      //## Operation: State%1060691312
      //	Returns a state variable object of the state with name
      //	state_name if it exists in the context. Returns NULL
      //	otherwise.
      cControlState * State (CONST_STRING_T state_name);

      //## Operation: ControlProgramNames%1060691313
      //	Returns the names of all programs (SCPL programs!)
      //	defined within this context.
      void ControlProgramNames (STRING_LIST_T &program_names);

      //## Operation: ControlProgram%1060691314
      //	Returns a program object (SCPL program!) of the program
      //	with name progr_name if it exists in the context.
      //	Returns NULL otherwise.
      cControlProgram * ControlProgram (CONST_STRING_T prog_name);

      //## Operation: ProcedureNames%1060691315
      //	Returns the names of all procedures (SCPL procedures)
      //	defined within this context.
      void ProcedureNames (STRING_LIST_T &proc_names);

      //## Operation: Procedure%1060691316
      //	Returns a procedure object (SCPL procedure) of the
      //	procedure with name proc_name if it exists in the
      //	context. Returns NULL otherwise.
      cControlProcedure * Procedure (CONST_STRING_T proc_name);

      //## Operation: StartConditionNames%1060691317
      //	Returns the names of all start conditions (SCPL start
      //	conditions)  defined within this context.
      void StartConditionNames (STRING_LIST_T &cond_names);

      //## Operation: StartCondition%1060691318
      //	Returns a start condition object (SCPL start condition)
      //	of the start condition with name cond_name if it exists
      //	in the context. Returns NULL otherwise.
      cControlStartCondition * StartCondition (CONST_STRING_T cond_name);

      //## Operation: Alarms%1089103361
      virtual ULONG_T Alarms (ULONG_T selection);

      //## Operation: Alarms%1081425825
      virtual ULONG_T Alarms (ULONG_T selection, ALARM_MAP_T &alarms);

      //## Operation: ClearAlarm%1081425826
      virtual void ClearAlarm (ULONG_T ident, BOOL_T propagate = true);

      //## Operation: ClearAlarms%1081425827
      virtual void ClearAlarms (BOOL_T propagate = true);

      //## Operation: GetValue%1041514715
      //	Retrieves the value of a variable specified by name and
      //	indices into a variable of type STRING_T.
      //	To retrieve variable values it is recommended to use the
      //	variable or variable reference interface.
      void GetValue (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetValue%1041514716
      //	Retrieves the value of a variable specified by name and
      //	indices into a variable of type LONG_T.
      //	To retrieve variable values it is recommended to use the
      //	variable or variable reference interface.
      void GetValue (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetValue%1041514717
      //	Retrieves the value of a variable specified by name and
      //	indices into a variable of type DOUBLE_T.
      //	To retrieve variable values it is recommended to use the
      //	variable or variable reference interface.
      void GetValue (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Refresh%1133172776
      //	Refreshes a variable value
      void Refresh (CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1041514718
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a constant string value.
      //	To retrieve variable values it is recommended to use the
      //	variable or variable reference interface.
      void SetValue (CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1041514719
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a  LONG_T value.
      //	To retrieve variable values it is recommended to use the
      //	variable or variable reference interface.
      void SetValue (CONST_STRING_T var_name, LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1041514720
      //	Sets the value of a variable specified by name and
      //	indices. The value is passed as a DOUBLE_T value.
      //	To retrieve variable values it is recommended to use the
      //	variable or variable reference interface.
      void SetValue (CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetMinimum%1089103377
      //	Gets the minimum value of a variable specified by
      //	variable name.
      void GetMinimum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103378
      //	Gets the minimum value of a variable specified by
      //	variable name.
      void GetMinimum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103379
      //	Gets the minimum value of a variable specified by
      //	variable name.
      void GetMinimum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103383
      //	Gets the maximum value of a variable specified by
      //	variable name.
      void GetMaximum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103384
      //	Gets the maximum value of a variable specified by
      //	variable name.
      void GetMaximum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103385
      //	Gets the maximum value of a variable specified by
      //	variable name.
      void GetMaximum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103380
      //	Gets the minimum value of a variable specified by
      //	variable id.
      void GetMinimum (LONG_T var_id, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103381
      //	Gets the minimum value of a variable specified by
      //	variable id.
      void GetMinimum (LONG_T var_id, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103382
      //	Gets the minimum value of a variable specified by
      //	variable id.
      void GetMinimum (LONG_T var_id, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103386
      //	Gets the maximum value of a variable specified by
      //	variable id.
      void GetMaximum (LONG_T var_id, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103387
      //	Gets the maximum value of a variable specified by
      //	variable id.
      void GetMaximum (LONG_T var_id, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103388
      //	Gets the maximum value of a variable specified by
      //	variable id.
      void GetMaximum (LONG_T var_id, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetDeviceValue%1082984450
      //	Retrieves a value of a variable directly from a device.
      virtual void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value);

      //## Operation: GetDeviceValue%1083004733
      //	Retrieves a value of a variable directly from a device.
      void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, BOOL_T &value);

      //## Operation: GetDeviceValue%1082984451
      void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, LONG_T &value);

      //## Operation: GetDeviceValue%1082984452
      void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, DOUBLE_T &value);

      //## Operation: SetDeviceValue%1082984453
      virtual void SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value);

      //## Operation: SetDeviceValue%1082984454
      void SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, LONG_T value);

      //## Operation: SetDeviceValue%1082984455
      void SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, DOUBLE_T value);

      //## Operation: ExecuteCommand%1089292610
      //	Executes a command on a program owned by the context.
      //	The program is denoted by program name.
      virtual void ExecuteCommand (CONST_STRING_T program_name, ULONG_T command);

      //## Operation: ExecuteRequest%1133771770
      //	Executes a request on a program owned by the context.
      //	The program is denoted by program name.
      virtual void ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request);

      //## Operation: Save%1092293194
      virtual void Save (UCHAR_T refresh_type, ULONG_T refresh_value);

      //## Operation: Download%1091687830
      //	The download method activates a download of all device
      //	data hold in a database.
      virtual void Download (ULONG_T ctrl = 0);

      //## Operation: Upload%1091687831
      //	The upload method activates an upload of all device data
      //	hold in devices.
      virtual void Upload (ULONG_T ctrl = 0);

      //## Operation: ReadFile%1091699603
      virtual void ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_files, STRING_T &buf);
      virtual void ReadFile(CONST_STRING_T file_name, CONST_STRING_T sub_files, cStringBuffer &buf);
      virtual void ExportVariables(STRING_T &buf, CONST_STRING_T sub_file, CONST_STRING_T separator);

      //## Operation: WriteFile%1091699604
      virtual void WriteFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, CONST_STRING_T buf);

      //## Operation: Copy%1091957520
      virtual void Copy (cContext *src_context, CONST_STRING_T sub_file, BOOL_T show_errors=true, BOOL_T buffered = true);

      //## Operation: SetJob%1093930659
      virtual void SetJob (cJobSpec *job_spec);

      //## Operation: GetJobSpec%1093930660
      virtual cJobSpec * GetJobSpec (CONST_STRING_T job_name);

      //## Operation: CopyCommand%1100714370
      virtual void CopyCommand (ULONG_T src, ULONG_T dst, BOOL_T exchange, ULONG_T copy_flags = 0);

      //## Operation: Compare%1108566001
      virtual STRING_T Compare (ULONG_T flags = 0);

      //## Operation: GetFileContext%1101987270
      cContext * GetFileContext (CONST_STRING_T file_name, BOOL_T header_only = false);

      //## Operation: GetFileContextFromString%1136199171
      cContext * GetFileContextFromString(CONST_STRING_T dataset, BOOL_T header_only = false);
      // Method to read in a dataset directly from a file
      cContext * GetFileContextFromFile(CONST_STRING_T file_name);

      //## Operation: RegisterVarRefs%1108559439
      BOOL_T RegisterVarRefs (cDataChangeAdapter *adapter);

      //## Operation: UnitDef%1109752576
      //	Returns a variable definition object of the variable
      //	with name var_name if it exists in the context. Returns
      //	NULL otherwise.
      cUnitDef * UnitDef (CONST_STRING_T unit_name);

      //## Operation: AddUnitDef%1109752577
      //	Adds a variable definition to the context.
      //	Should not be used by a context user.
      void AddUnitDef (CONST_STRING_T unit_name, cUnitDef *unit_def);

      //## Operation: SetUnit%1109785975
      void SetUnit (CONST_STRING_T unit_name, UCHAR_T selection);

      //## Operation: UnitDefs
      ULONG_T UnitDefs (UNITDEF_MAP_T &UnitDefs, CONST_STRING_T selection="*");

      //## Operation: Process%1117632421
      cSHProcess * Process ();

      //## Operation: SetProgress%1122375231
      void SetProgress (ULONG_T indicator, ULONG_T value);

      //## Operation: PersistenceChannel%1122375233
      //	Returns the persistence channel object associated with
      //	the context.
      virtual cPersistenceChannel * PersistenceChannel ();

      //## Operation: Send%1122638220
      virtual void Send (cTransientObject *object, ULONG_T flags=0);

      //## Operation: IsActive%1125662157
      BOOL_T IsActive ();

      //## Operation: IsConnected%1134147948
      virtual BOOL_T IsConnected ();

      //## Operation: Ping%1134227771
      virtual BOOL_T Ping ();

      //## Operation: AddFilter%1141197872
      void AddFilter (ULONG_T if_type, cInterfaceFilter *filter);

      //## Operation: RemoveFilter%1141197873
      void RemoveFilter (ULONG_T if_type);

      //## Operation: DefFilter%1141208304
      virtual void DefFilter (ULONG_T if_type, cVarDef *var_def);

      //## Operation: RefFilter%1141202703
      void RefFilter (ULONG_T if_type, STRING_T &var_name, LONG_T &i1, LONG_T &i2, LONG_T &i3, LONG_T &i4);

      //## Operation: FilteredVarRef%1141230223
      cVarRef * FilteredVarRef (ULONG_T if_type, CONST_STRING_T var_name, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: Filter%1141664738
      cInterfaceFilter * Filter (ULONG_T if_type);

      //## Operation: ShadowChanges%1191857051
      ULONG_T ShadowChanges ();

      //## Operation: AlterShadowChanges%1191857052
      void AlterShadowChanges (LONG_T step);

      //## Operation: SetShadowChanges%1191857053
      void SetShadowChanges (ULONG_T value);

      //## Operation: ResetShadowBuffers%1191857054
      void ResetShadowBuffers ();

      //## Operation: GetObject%1238478450
      ULONG_T GetObject (CONST_STRING_T var_name, cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetObject%1238478451
      void SetObject (CONST_STRING_T var_name, const cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: ExecuteJob%1244547093
      //	Executes a job on a program owned by the context. The
      //	program is denoted by program name.
      virtual void ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async = false);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ProcessId%403B4A190280
      ULONG_T get_ProcessId () const;
      void set_ProcessId (ULONG_T value);

      //## Attribute: IsRootContext%42E909150213
      BOOL_T get_IsRootContext () const;
      void set_IsRootContext (BOOL_T value);

      //## Attribute: CellName%4393E7390323
      STRING_T get_CellName () const;

    // Data Members for Class Attributes

      //## Attribute: ActDeviceName%3E22C9E7016D
      //## begin cContext::ActDeviceName%3E22C9E7016D.attr preserve=no  public: STRING_T {U} 
      STRING_T _ActDeviceName;
      //## end cContext::ActDeviceName%3E22C9E7016D.attr

  public:
    // Additional Public Declarations
      //## begin cContext%3E0031DC0265.public preserve=yes
      static void SetUiUpdateFunction(UI_UPDATE_FUNCTION_T function);
      static void UpdateUi();
      static UI_UPDATE_FUNCTION_T GetUiUpdateFuntion();
  protected:
      static UI_UPDATE_FUNCTION_T _UiUpdateFunction;
      //## end cContext%3E0031DC0265.public

  protected:
    // Data Members for Class Attributes

      //## begin cContext::ProcessId%403B4A190280.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ProcessId;
      //## end cContext::ProcessId%403B4A190280.attr

      //## begin cContext::IsRootContext%42E909150213.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _IsRootContext;
      //## end cContext::IsRootContext%42E909150213.attr

      //## begin cContext::CellName%4393E7390323.attr preserve=no  public: STRING_T {U} 
      STRING_T _CellName;
      //## end cContext::CellName%4393E7390323.attr

      //## Attribute: Created%3EF84E9D033C
      //## begin cContext::Created%3EF84E9D033C.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Created;
      //## end cContext::Created%3EF84E9D033C.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E0737AD02F8
      //## Role: cContext::FuncDecls%3E0737AE03AE
      //## Qualifier: name%3E07390303C2; STRING_T
      //## begin cContext::FuncDecls%3E0737AE03AE.role preserve=no  public: cFuncDecl {1 -> 0..nRFHN}
      std::map<STRING_T, cFuncDecl*> _FuncDecls;
      //## end cContext::FuncDecls%3E0737AE03AE.role

      //## Association: System::Database::<unnamed>%3E9C21DB0157
      //## Role: cContext::SearchContexts%3E9C21E9031C
      //## Qualifier: name%3E9C2298031C; STRING_T
      //## begin cContext::SearchContexts%3E9C21E9031C.role preserve=no  public: cContext { -> 0..nRFHN}
      std::map<STRING_T, cContext*> _SearchContexts;
      //## end cContext::SearchContexts%3E9C21E9031C.role

      //## Association: System::Database::<unnamed>%3E07379A01A6
      //## Role: cContext::VarDefs%3E07379B014E
      //## Qualifier: name%3E0738C803E5; STRING_T
      //## begin cContext::VarDefs%3E07379B014E.role preserve=no  public: cVarDef {1 -> 0..nRFHN}
      std::map<STRING_T, cVarDef*> _VarDefs;
      //## end cContext::VarDefs%3E07379B014E.role

      //## Association: System::Database::<unnamed>%42257C0A02EE
      //## Role: cContext::UnitDefs%42257C0D005D
      //## Qualifier: name%42257C5F0399; STRING_T
      //## begin cContext::UnitDefs%42257C0D005D.role preserve=no  public: cUnitDef {1 -> 0..nRFHN}
      UNITDEF_MAP_T _UnitDefs;
      //## end cContext::UnitDefs%42257C0D005D.role

      //## Association: <unnamed>%42120B2C001F
      //## Role: cContext::RefCache%42120B2D006D
      //## begin cContext::RefCache%42120B2D006D.role preserve=no  public: cRefCache {1 -> 1RFHN}
      cRefCache *_RefCache;
      //## end cContext::RefCache%42120B2D006D.role

      //## Association: System::Process::<unnamed>%3EE063540148
      //## Role: cContext::Process%3EE063550261
      //## begin cContext::Process%3EE063550261.role preserve=no  public: cSHProcess { -> 0..1RFHN}
      cSHProcess *_Process;
      //## end cContext::Process%3EE063550261.role

      //## Association: System::Database::<unnamed>%3FF941AA02BF
      //## Role: cContext::EventChannel%3FF941AB0177
      //## begin cContext::EventChannel%3FF941AB0177.role preserve=no  public: cChannel { -> 0..1RFHN}
      cChannel *_EventChannel;
      //## end cContext::EventChannel%3FF941AB0177.role

      //## Association: System::Database::<unnamed>%42E6435F00BB
      //## Role: cContext::Dispatcher%42E643600128
      //## begin cContext::Dispatcher%42E643600128.role preserve=no  public: cChannel { -> 0..1RFHN}
      cChannel *_Dispatcher;
      //## end cContext::Dispatcher%42E643600128.role

      //## Association: System::Database::<unnamed>%42E75F1D0109
      //## Role: cContext::InternalBridge%42E75F2101E4
      //## begin cContext::InternalBridge%42E75F2101E4.role preserve=no  public: cInternalBridge { -> 0..1RFHN}
      cInternalBridge *_InternalBridge;
      //## end cContext::InternalBridge%42E75F2101E4.role

      //## Association: System::PLC::<unnamed>%3F3902B700CB
      //## Role: cContext::States%3F3902B8035B
      //## Qualifier: name%3F3902FE0222; STRING_T
      //## begin cContext::States%3F3902B8035B.role preserve=no  public: cControlState { -> 0..nRFHN}
      std::map<STRING_T, cControlState*> _States;
      //## end cContext::States%3F3902B8035B.role

      //## Association: System::PLC::<unnamed>%3F39031F02BF
      //## Role: cContext::Programs%3F390320038B
      //## Qualifier: name%3F3903390222; STRING_T
      //## begin cContext::Programs%3F390320038B.role preserve=no  public: cControlProgram { -> 0..nRFHN}
      std::map<STRING_T, cControlProgram*> _Programs;
      //## end cContext::Programs%3F390320038B.role

      //## Association: System::PLC::<unnamed>%3F390364005D
      //## Role: cContext::StartConditions%3F390365000F
      //## Qualifier: name%3F3903DC0251; STRING_T
      //## begin cContext::StartConditions%3F390365000F.role preserve=no  public: cControlStartCondition { -> 0..nRFHN}
      std::map<STRING_T, cControlStartCondition*> _StartConditions;
      //## end cContext::StartConditions%3F390365000F.role

      //## Association: System::PLC::<unnamed>%3F390397031C
      //## Role: cContext::Procedures%3F39039A0213
      //## Qualifier: name%3F3903C501D4; STRING_T
      //## begin cContext::Procedures%3F39039A0213.role preserve=no  public: cControlProcedure { -> 0..nRFHN}
      std::map<STRING_T, cControlProcedure*> _Procedures;
      //## end cContext::Procedures%3F39039A0213.role

    // Additional Protected Declarations
      //## begin cContext%3E0031DC0265.protected preserve=yes
      //## end cContext%3E0031DC0265.protected

  private:
    // Additional Private Declarations
      //## begin cContext%3E0031DC0265.private preserve=yes
      //## end cContext%3E0031DC0265.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: GetHeader%1102334008
      STRING_T GetHeader (CONST_STRING_T buf);

    // Data Members for Class Attributes

      //## Attribute: Symbols%3E9C53AB0186
      //## begin cContext::Symbols%3E9C53AB0186.attr preserve=no  private: LONG_MAP_T {U} 
      LONG_MAP_T _Symbols;
      //## end cContext::Symbols%3E9C53AB0186.attr

      //## Attribute: Adapters%3EBFB5880251
      //## begin cContext::Adapters%3EBFB5880251.attr preserve=no  private: ADAPTER_MAP_T {U} 
      ADAPTER_MAP_T _Adapters;
      //## end cContext::Adapters%3EBFB5880251.attr

      //## Attribute: Filters%44054AEA02C4
      //## begin cContext::Filters%44054AEA02C4.attr preserve=no  private: FILTER_MAP_T {U} 
      FILTER_MAP_T _Filters;
      //## end cContext::Filters%44054AEA02C4.attr

      //## Attribute: ShadowChanges%470A5F2E02C7
      //## begin cContext::ShadowChanges%470A5F2E02C7.attr preserve=no  private: ULONG_T {U} 0
      ULONG_T _ShadowChanges;
      //## end cContext::ShadowChanges%470A5F2E02C7.attr

    // Additional Implementation Declarations
      //## begin cContext%3E0031DC0265.implementation preserve=yes
      //## end cContext%3E0031DC0265.implementation

};

//## begin cContext%3E0031DC0265.postscript preserve=yes
//## end cContext%3E0031DC0265.postscript

// Class cContext 

//## begin module%3E0031DC0265.epilog preserve=yes
//## end module%3E0031DC0265.epilog


#endif
