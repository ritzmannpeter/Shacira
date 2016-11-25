//## begin module%3E0C47C10368.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0C47C10368.cm

//## begin module%3E0C47C10368.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0C47C10368.cp

//## Module: cStyxParser%3E0C47C10368; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Language\cStyxParser.h

#ifndef cStyxParser_h
#define cStyxParser_h 1

//## begin module%3E0C47C10368.includes preserve=yes

#include "stdosx.h"    // base header STYX library
#include "scn_base.h"  // scanner
#include "scn_pre.h"   // scanner preprocessor
#include "ptm_pp.h"    // Pretty Printer
#include "ptm_gen.h"   // parse & term construction
#include "gls.h"       // general language services
#include "symbols.h"   // symbol table
#include "hmap.h"      // hash maps
#include "Shacira_lim.h"  // Shacira scanner table
#include "Shacira_pim.h"  // Shacira parser table
#include "Shacira_int.h"  // Shacira language interface

//## end module%3E0C47C10368.includes

// eb_sema
#include "base/eb_sema.hpp"
// cControlProcedure
#include "System/PLC/cControlProcedure.h"
// cSDDLParser
#include "Language/cSDDLParser.h"

class __DLL_EXPORT__ cVariableValues;
class __DLL_EXPORT__ cSHVariant;
class __DLL_EXPORT__ cUnitDef;
class __DLL_EXPORT__ cProcedureLine;
class __DLL_EXPORT__ cAtomicCondition;
class __DLL_EXPORT__ cControlCondition;
class __DLL_EXPORT__ cControlStartCondition;
class __DLL_EXPORT__ cControlProgram;
class __DLL_EXPORT__ cControlState;

//## begin module%3E0C47C10368.additionalDeclarations preserve=yes

typedef ShaciraDefinition ShacDefinition;
typedef ShaciraDatabaseDef ShacDatabaseDef;
typedef ShaciraFuncDecl ShacFuncDecl;
typedef ShaciraFuncRef ShacFuncRef;
typedef ShaciraVarRef ShacVarRef;
typedef ShaciraVarDef ShacVarDef;
typedef ShaciraMapDef ShacMapDef;
typedef ShaciraItemSpec ShacItemSpec;
typedef ShaciraItemSpec ShacItemSpec;
typedef ShaciraMapDef ShacMapDef;
typedef ShaciraDataTypeSpec ShacDataTypeSpec;
typedef ShaciraMapTypeSpec ShacMapTypeSpec;
typedef ShaciraDeviceSpec ShacDeviceSpec;
typedef ShaciraRefresh ShacRefresh;
typedef ShaciraDescription ShacDescription;
typedef ShaciraVarTypeSpec ShacVarTypeSpec;
typedef ShaciraPersistence ShacPersistence;
typedef ShaciraFile ShacFile;
typedef ShaciraValueSpec ShacValueSpec;
typedef ShaciraValue ShacValue;
typedef ShaciraBcd ShacBcd;
typedef ShaciraBaseType ShacBaseType;
typedef ShaciraStringType ShacStringType;
typedef ShaciraVarType ShacVarType;
typedef ShaciraEventType ShacEventType;
typedef ShaciraPersistenceType ShacPersistenceType;
typedef ShaciraRefreshType ShacRefreshType;
typedef ShaciraState ShacState;
typedef ShaciraProgram ShacProgram;
typedef ShaciraProcedure ShacProcedure;
typedef ShaciraStartCondition ShacStartCondition;
typedef ShaciraCondition ShacCondition;
typedef ShaciraAtomicCondition ShacAtomicCondition;
typedef ShaciraRelOp ShacRelOp;
typedef ShaciraStatementBlock ShacStatementBlock;
typedef ShaciraStatement ShacStatement;
typedef ShaciraArgument ShacArgument;
typedef ShaciraText ShacText;
typedef ShaciraDim1 ShacDim1;
typedef ShaciraDim2 ShacDim2;
typedef ShaciraDim3 ShacDim3;
typedef ShaciraDim4 ShacDim4;
typedef ShaciraFlags ShacFlags;
typedef ShaciraUnitDef ShacUnitDef;
typedef ShaciraUnitRef ShacUnitRef;
typedef ShaciraSystemFlags ShacSystemFlags;
#define Shac_initSymbols Shacira_initSymbols
#define Shac_quitSymbols Shacira_quitSymbols
typedef ShaciraDefinitions ShacDefinitions;
#define ShacDefinitions_defs ShaciraDefinitions_defs
#define ShacDefinition_dbdef ShaciraDefinition_dbdef
#define ShacDefinition_funcdec ShaciraDefinition_funcdec
#define ShacDefinition_varref ShaciraDefinition_varref
#define ShacDefinition_funcref ShaciraDefinition_funcref
#define ShacDynamicDecls ShaciraDynamicDecls
#define ShacDefinition_dyndec ShaciraDefinition_dyndec
#define ShacDynamicDecls_def ShaciraDynamicDecls_def
#define ShacDefinition_state ShaciraDefinition_state
#define ShacDefinition_prog ShaciraDefinition_prog
#define ShacDefinition_proc ShaciraDefinition_proc
#define ShacDefinition_cond ShaciraDefinition_cond
#define ShacDefinition_vardef ShaciraDefinition_vardef
#define ShacDefinition_unitdef ShaciraDefinition_unitdef
#define ShacDatabaseDef_def ShaciraDatabaseDef_def
#define ShacFuncDecl_free1 ShaciraFuncDecl_free1
#define ShacFuncDecl_free2 ShaciraFuncDecl_free2
#define ShacFuncDecl_emb1 ShaciraFuncDecl_emb1
#define ShacFuncDecl_emb2 ShaciraFuncDecl_emb2
#define ShacFuncDecl_conv1 ShaciraFuncDecl_conv1
#define ShacFuncDecl_conv2 ShaciraFuncDecl_conv2
#define ShacFuncDecl_filt1 ShaciraFuncDecl_filt1
#define ShacFuncDecl_filt2 ShaciraFuncDecl_filt2
#define ShacFuncDecl_acc1 ShaciraFuncDecl_acc1
#define ShacFuncDecl_acc2 ShaciraFuncDecl_acc2
#define ShacFuncDecl_lim1 ShaciraFuncDecl_lim1
#define ShacFuncDecl_lim2 ShaciraFuncDecl_lim2
#define ShacFuncDecl_view1 ShaciraFuncDecl_view1
#define ShacFuncDecl_view2 ShaciraFuncDecl_view2
#define ShacFuncDecl_dark ShaciraFuncDecl_dark
#define ShacFuncDecl_plaus ShaciraFuncDecl_plaus
#define ShacFuncDecl_user ShaciraFuncDecl_user
#define ShacFuncDecl_btn ShaciraFuncDecl_btn
#define ShacFuncDecl_sigflt ShaciraFuncDecl_sigflt
#define ShacFuncDecl_slot ShaciraFuncDecl_slot
#define ShacFuncDecl_valf ShaciraFuncDecl_valf
#define ShacFuncDecl_unit ShaciraFuncDecl_unit
#define ShacFuncDecl_evflt ShaciraFuncDecl_evflt
#define ShacFuncDecl_init ShaciraFuncDecl_init
#define ShacFuncRef_ref ShaciraFuncRef_ref
typedef ShaciraArgDecl ShacArgDecl;
#define ShacArgDecl_argdec1 ShaciraArgDecl_argdec1
#define ShacArgDecl_argdec2 ShaciraArgDecl_argdec2
#define ShacVarRef_ref ShaciraVarRef_ref
typedef ShaciraIndexRef ShacIndexRef;
#define ShacIndexRef_cnat ShaciraIndexRef_cnat
#define ShacIndexRef_chex ShaciraIndexRef_chex
#define ShacIndexRef_func ShaciraIndexRef_func
#define ShacIndexRef_var ShaciraIndexRef_var
typedef ShaciraVarSpecSeq ShacVarSpecSeq;
#define ShacVarDef_def ShaciraVarDef_def
typedef ShaciraFilterFunc ShacilterFunc;
typedef ShaciraMinSpec ShacMinSpec;
typedef ShaciraMaxSpec ShacMaxSpec;
typedef ShaciraDimSpec ShacDimSpec;
#define ShacDimSpec_dimspec ShaciraDimSpec_dimspec
#define ShacVarSpecSeq_specs ShaciraVarSpecSeq_specs
#define ShacFilterFunc_ref ShaciraFilterFunc_ref
#define ShacAccessFunc_ref ShaciraAccessFunc_ref
#define ShacMinSpec_spec ShaciraMinSpec_spec
#define ShacMaxSpec_spec ShaciraMaxSpec_spec
typedef ShaciraConvFunc ShacConvFunc;
#define ShacMapDef_map1 ShaciraMapDef_map1
#define ShacMapDef_map2 ShaciraMapDef_map2
#define ShacMapDef_nul ShaciraMapDef_nul
#define ShacConvFunc_conv ShaciraConvFunc_conv
typedef ShaciraItemSpecifier ShacItemSpecifier;
#define ShacItemSpec_spec1 ShaciraItemSpec_spec1
#define ShacItemSpec_spec2 ShaciraItemSpec_spec2
#define ShacItemSpec_spec3 ShaciraItemSpec_spec3
typedef ShaciraSymbol ShacSymbol;
#define ShacItemSpecifier_symbol ShaciraItemSpecifier_symbol
#define ShacSymbol_dec ShaciraSymbol_dec
#define ShacSymbol_ide ShaciraSymbol_ide
#define ShacSymbol_hex ShaciraSymbol_hex
#define ShacItemSpecifier_name ShaciraItemSpecifier_name
#define ShacDataTypeSpec_type1 ShaciraDataTypeSpec_type1
#define ShacDataTypeSpec_type2 ShaciraDataTypeSpec_type2
#define ShacDataTypeSpec_type3 ShaciraDataTypeSpec_type3
#define ShacDataTypeSpec_type4 ShaciraDataTypeSpec_type4
#define ShacMapTypeSpec_type1 ShaciraMapTypeSpec_type1
#define ShacMapTypeSpec_type2 ShaciraMapTypeSpec_type2
#define ShacMapTypeSpec_type3 ShaciraMapTypeSpec_type3
#define ShacMapTypeSpec_type4 ShaciraMapTypeSpec_type4
#define ShacDeviceSpec_spec ShaciraDeviceSpec_spec
#define ShacRefresh_refresh ShaciraRefresh_refresh
#define ShacDescription_desc ShaciraDescription_desc
#define ShacVarTypeSpec_vartype ShaciraVarTypeSpec_vartype
#define ShacPersistence_persist ShaciraPersistence_persist
#define ShacFile_file ShaciraFile_file
#define ShacValueSpec_spec ShaciraValueSpec_spec
#define ShacValue_nat ShaciraValue_nat
#define ShacValue_real ShaciraValue_real
#define ShacValue_str ShaciraValue_str
#define ShacValue_ide ShaciraValue_ide
#define ShacValue_bcd ShaciraValue_bcd
#define ShacBcd_bcd ShaciraBcd_bcd
#define ShacBaseType_char ShaciraBaseType_char
#define ShacBaseType_char ShaciraBaseType_char
#define ShacBaseType_uchar ShaciraBaseType_uchar
#define ShacBaseType_short ShaciraBaseType_short
#define ShacBaseType_ushort ShaciraBaseType_ushort
#define ShacBaseType_long ShaciraBaseType_long
#define ShacBaseType_ulong ShaciraBaseType_ulong
#define ShacBaseType_float ShaciraBaseType_float
#define ShacBaseType_double ShaciraBaseType_double
#define ShacBaseType_bool ShaciraBaseType_bool
#define ShacBaseType_void ShaciraBaseType_void
#define ShacBaseType_object ShaciraBaseType_object
#define ShacBaseType_bit8 ShaciraBaseType_bit8
#define ShacBaseType_bit16 ShaciraBaseType_bit16
#define ShacBaseType_bit32 ShaciraBaseType_bit32
#define ShacStringType_string ShaciraStringType_string
#define ShacStringType_wstring ShaciraStringType_wstring
#define ShacStringType_bat ShaciraStringType_byte
#define ShacVarType_set ShaciraVarType_set
#define ShacVarType_act ShaciraVarType_act
#define ShacVarType_volatile ShaciraVarType_volatile
#define ShacVarType_virtual ShaciraVarType_virtual
typedef ShaciraFilterFunc ShacFilterFunc;
typedef ShaciraAccessFunc ShacAccessFunc;
#define ShacValue_hex ShaciraValue_hex
#define ShacStringType_byte ShaciraStringType_byte
#define ShacEventType_cycle ShaciraEventType_cycle
#define ShacEventType_automatic ShaciraEventType_automatic
#define ShacEventType_data ShaciraEventType_data
#define ShacPersistenceType_ram ShaciraPersistenceType_ram
#define ShacPersistenceType_bbram ShaciraPersistenceType_bbram
#define ShacPersistenceType_filebased ShaciraPersistenceType_filebased
#define ShacRefreshType_cyclic ShaciraRefreshType_cyclic
#define ShacRefreshType_event1 ShaciraRefreshType_event1
#define ShacRefreshType_event2 ShaciraRefreshType_event2
#define ShacState_state ShaciraState_state
#define ShacProcedure_proc ShaciraProcedure_proc
#define ShacCondition_atom ShaciraCondition_atom
#define ShacCondition_or ShaciraCondition_or
#define ShacCondition_and ShaciraCondition_and
#define ShacCondition_not ShaciraCondition_not
#define ShacCondition_name ShaciraCondition_name
#define ShacCondition_brack ShaciraCondition_brack
#define ShacAtomicCondition_rel ShaciraAtomicCondition_rel
#define ShacRelOp_le ShaciraRelOp_le
#define ShacRelOp_lt ShaciraRelOp_lt
#define ShacRelOp_gt ShaciraRelOp_gt
#define ShacRelOp_ge ShaciraRelOp_ge
#define ShacRelOp_eq ShaciraRelOp_eq
#define ShacRelOp_ne ShaciraRelOp_ne
#define ShacStatementBlock_stmts ShaciraStatementBlock_stmts
#define ShacStatement_if ShaciraStatement_if
#define ShacStatement_while ShaciraStatement_while
#define ShacStatement_ifels ShaciraStatement_ifels
#define ShacStatement_proc ShaciraStatement_proc
#define ShacStatement_func ShaciraStatement_func
#define ShacStatement_assg1 ShaciraStatement_assg1
#define ShacStatement_assg2 ShaciraStatement_assg2
#define ShacStatement_ret ShaciraStatement_ret
#define ShacArgument_cnat ShaciraArgument_cnat
#define ShacArgument_chex ShaciraArgument_chex
#define ShacArgument_creal ShaciraArgument_creal
#define ShacArgument_cstring ShaciraArgument_cstring
#define ShacArgument_func ShaciraArgument_func
#define ShacArgument_var ShaciraArgument_var
#define ShacText_text ShaciraText_text
#define ShacDim1_text ShaciraDim1_text
#define ShacDim2_text ShaciraDim2_text
#define ShacDim3_text ShaciraDim3_text
#define ShacDim4_text ShaciraDim4_text
typedef ShaciraFlagValue ShacFlagValue;
#define ShacFlags_value ShaciraFlags_value
#define ShacFlagValue_cnat ShaciraFlagValue_cnat
#define ShacFlagValue_chex ShaciraFlagValue_chex
#define ShacUnitDef_def ShaciraUnitDef_def
#define ShacUnitDef_defe ShaciraUnitDef_defe
typedef ShaciraUnitSpec ShacUnitSpec;
#define ShacUnitSpec_spec ShaciraUnitSpec_spec
#define ShacUnitRef_ref1 ShaciraUnitRef_ref1
#define ShacUnitRef_ref2 ShaciraUnitRef_ref2
#define ShacSystemFlags_value ShaciraSystemFlags_value
typedef ShaciraSystemFlag ShacSystemFlag;
#define ShacSystemFlag_hread ShaciraSystemFlag_hread
#define ShacSystemFlag_hwrite ShaciraSystemFlag_hwrite
#define ShacSystemFlag_ofs1 ShaciraSystemFlag_ofs1
#define ShacSystemFlag_ofs2 ShaciraSystemFlag_ofs2
#define ShacSystemFlag_ofs3 ShaciraSystemFlag_ofs3
#define ShacSystemFlag_ofs4 ShaciraSystemFlag_ofs4
#define ShacSystemFlag_em63 ShaciraSystemFlag_em63

//## end module%3E0C47C10368.additionalDeclarations


//## begin cStyxParser%3E0C47C10368.preface preserve=yes
//## end cStyxParser%3E0C47C10368.preface

//## Class: cStyxParser%3E0C47C10368
//## Category: Language%3E0C4A4402CD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3EF897D40177;cSHVariant { -> F}
//## Uses: <unnamed>%3F38BDDF01D4;cControlState { -> F}
//## Uses: <unnamed>%3F38BDE80177;cControlProgram { -> F}
//## Uses: <unnamed>%3F38BDF40203;cControlProcedure { -> }
//## Uses: <unnamed>%3F38BDFF033C;cControlStartCondition { -> F}
//## Uses: <unnamed>%3F38DDC10271;cControlCondition { -> F}
//## Uses: <unnamed>%3F38E3E400AB;cAtomicCondition { -> F}
//## Uses: <unnamed>%3F3A3B800280;cProcedureLine { -> F}
//## Uses: <unnamed>%40FCDE9D00CB;cMutexSem { -> }
//## Uses: <unnamed>%4113A13103C8;cVariableValues { -> F}
//## Uses: <unnamed>%42257AF501C5;cUnitDef { -> F}

class __DLL_EXPORT__ cStyxParser : public cSDDLParser  //## Inherits: <unnamed>%3E0C47FF0245
{
  //## begin cStyxParser%3E0C47C10368.initialDeclarations preserve=yes
public:
  //## end cStyxParser%3E0C47C10368.initialDeclarations

    //## Constructors (generated)
      cStyxParser();

      cStyxParser(const cStyxParser &right);

    //## Destructor (generated)
      virtual ~cStyxParser();


    //## Other Operations (specified)
      //## Operation: ParseDatabaseFromFile%1040992336
      virtual BOOL_T ParseDatabaseFromFile (cContext *context, CONST_STRING_T source, BOOL_T dynamic = false);

      //## Operation: ParseDatabaseFromString%1040992340
      virtual BOOL_T ParseDatabaseFromString (cContext *context, CONST_STRING_T source, BOOL_T dynamic = false);

      //## Operation: ParseDBLiteFromString%1102338845
      virtual BOOL_T ParseDBLiteFromString (cContext *context, CONST_STRING_T source);

      //## Operation: FuncRef%1040992341
      virtual cFuncRef * FuncRef (cContext *context, CONST_STRING_T source, UCHAR_T requested_data_type = UNDEFINED, UCHAR_T requested_class = UNDEFINED);

      //## Operation: VarRef%1040992342
      virtual cVarRef * VarRef (cContext *context, CONST_STRING_T source, UCHAR_T requested_data_type = UNDEFINED);

      //## Operation: ParseProgramFromFile%1060622593
      virtual void ParseProgramFromFile (cContext *context, CONST_STRING_T source, BOOL_T dynamic = false);

      //## Operation: ParseProgramFromString%1060622594
      virtual void ParseProgramFromString (cContext *context, CONST_STRING_T source, BOOL_T dynamic = false);

    // Data Members for Class Attributes

      //## Attribute: StyxMutex%40FCDE7A0280
      //## begin cStyxParser::StyxMutex%40FCDE7A0280.attr preserve=no  public: static cMutexSem {U} 
      static cMutexSem _StyxMutex;
      //## end cStyxParser::StyxMutex%40FCDE7A0280.attr

  public:
    // Additional Public Declarations
      //## begin cStyxParser%3E0C47C10368.public preserve=yes
      //## end cStyxParser%3E0C47C10368.public

  protected:
    // Additional Protected Declarations
      //## begin cStyxParser%3E0C47C10368.protected preserve=yes
      //## end cStyxParser%3E0C47C10368.protected

  private:
    // Additional Private Declarations
      //## begin cStyxParser%3E0C47C10368.private preserve=yes
      //## end cStyxParser%3E0C47C10368.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: InitFileParser%1040992346
      void InitFileParser (CONST_STRING_T parse_file);

      //## Operation: InitStringParser%1040992347
      void InitStringParser (CONST_STRING_T parse_string);

      //## Operation: InitLiteStringParser%1093971309
      void InitLiteStringParser (CONST_STRING_T parse_string);

      //## Operation: ExitParser%1040992348
      void ExitParser ();

      //## Operation: ParseDefList%1040992343
      void ParseDefList (cContext *context, ULONG_T &parsDefErrors);

      //## Operation: ParseDefinition%1040992350
      void ParseDefinition (cContext *context, ShacDefinition *sh_definition, ULONG_T &parseVarDefErrors);

      //## Operation: ParseDatabaseDef%1040992351
      void ParseDatabaseDef (cContext *context, ShacDatabaseDef *sh_database_def, ULONG_T &parseVarDefErrors);

      //## Operation: ParseFuncDecl%1040992352
      cFuncDecl * ParseFuncDecl (cContext *context, ShacFuncDecl *sh_func_decl);

      //## Operation: ParseFuncRef%1040992353
      cFuncRef * ParseFuncRef (cContext *context, ShacFuncRef *sh_func_ref, UCHAR_T requested_data_type = UNDEFINED, UCHAR_T requested_class = UNDEFINED);

      //## Operation: ParseVarRef%1040992354
      cVarRef * ParseVarRef (cContext *context, ShacVarRef *sh_var_ref, UCHAR_T requested_data_type = UNDEFINED);

      //## Operation: ParseVarDef%1040992372
      cVarDef * ParseVarDef (cContext *context, ShacVarDef *sh_var_def, CONST_STRING_T database_name, CONST_STRING_T device_name, ULONG_T &parseMapErrors);

      //## Operation: ParseMapDef%1041236869
      cMapping * ParseMapDef (cContext *context, ShacMapDef *sh_map_def, cVarDef *var_def, ULONG_T &errors);

      //## Operation: ParseItemSpec%1041236881
      MAP_ITEM_T * ParseItemSpec (cContext *context, ShacItemSpec *sh_item_spec, cVarDef *var_def, int pos = 0);

      //## Operation: ParseItemSpecArray%1041236871
      void ParseItemSpecArray (cContext *context, cMapping *mapping, ShacItemSpec *sh_item_spec, cVarDef *var_def);

      //## Operation: ParseItemSpecList%1041236879
      void ParseItemSpecList (cContext *context, cMapping *mapping, ShacMapDef *sh_map_def, cVarDef *var_def, ULONG_T &parseItemSpecErrors);

      //## Operation: ParseDataTypeSpec%1042459988
      void ParseDataTypeSpec (ShacDataTypeSpec *sh_data_type_spec, UCHAR_T &data_type, ULONG_T &length, UCHAR_T &precision);

      //## Operation: ParseMapTypeSpec%1042792991
      void ParseMapTypeSpec (ShacMapTypeSpec *sh_map_type_spec, UCHAR_T &data_type, ULONG_T &length, UCHAR_T &precision);

      //## Operation: ParseDeviceSpec%1042459994
      void ParseDeviceSpec (cContext *context, ShacDeviceSpec *sh_device_spec);

      //## Operation: ParseRefresh%1051713140
      void ParseRefresh (cContext *context, ShacRefresh *sh_refresh, cVarDef *var_def);

      //## Operation: ParseDescription%1051713141
      void ParseDescription (cContext *context, ShacDescription *sh_description, cVarDef *var_def);

      //## Operation: ParseVarType%1051713142
      void ParseVarType (cContext *context, ShacVarTypeSpec* sh_var_type_spec, cVarDef *var_def);

      //## Operation: ParsePersistence%1051713143
      void ParsePersistence (cContext *context, ShacPersistence *sh_persistence, cVarDef *var_def);

      //## Operation: ParseFile%1051713144
      void ParseFile (cContext *context, ShacFile *sh_file, cVarDef *var_def);

      //## Operation: ParseValueSpec%1091802227
      void ParseValueSpec (cContext *context, ShacValueSpec *sh_value_spec, cVarDef *var_def);

      //## Operation: ParseValue%1091802228
      STRING_T ParseValue (cContext *context, ShacValue *sh_value);

      //## Operation: ParseBcdValue%1092218354
      STRING_T ParseBcdValue (cContext *context, ShacBcd *sh_bcd);

      //## Operation: BaseType%1040992355
      UCHAR_T BaseType (ShacBaseType *sh_base_type);

      //## Operation: StringType%1040992358
      UCHAR_T StringType (ShacStringType *sh_string_type);

      //## Operation: VarType%1041236874
      INT_T VarType (ShacVarType *sh_var_type);

      //## Operation: EventType%1041236876
      INT_T EventType (ShacEventType *sh_event_type);

      //## Operation: PersistenceType%1051713137
      INT_T PersistenceType (ShacPersistenceType *sh_persistence_type);

      //## Operation: RefreshType%1051713139
      UCHAR_T RefreshType (ShacRefreshType *sh_refresh_type, LONG_T &value);

      //## Operation: NatValue%1040992364
      LONG_T NatValue (GLS_Tok *token);

      //## Operation: HexValue%1040992367
      LONG_T HexValue (GLS_Tok *token);

      //## Operation: RealValue%1040992365
      DOUBLE_T RealValue (GLS_Tok *token);

      //## Operation: StringValue%1040992366
      STRING_T StringValue (GLS_Tok *token);

      //## Operation: PersistentStringValue%1072085857
      CONST_STRING_T PersistentStringValue (GLS_Tok *token);

      //## Operation: ParseState%1060682990
      cControlState * ParseState (cContext *context, ShacState *sh_state);

      //## Operation: ParseProgram%1060682991
      cControlProgram * ParseProgram (cContext *context, ShacProgram *sh_program);

      //## Operation: ParseProcedure%1060682992
      cControlProcedure * ParseProcedure (cContext *context, ShacProcedure *sh_procedure);

      //## Operation: ParseStartCondition%1060682993
      cControlStartCondition * ParseStartCondition (cContext *context, ShacStartCondition *sh_start_condition);

      //## Operation: ParseCondition%1060691301
      cControlCondition * ParseCondition (cContext *context, ShacCondition *sh_condition);

      //## Operation: ParseAtomicCondition%1060691302
      cAtomicCondition * ParseAtomicCondition (cContext *context, ShacAtomicCondition *sh_atomic_condition);

      //## Operation: RelOp%1060691307
      INT_T RelOp (ShacRelOp *sh_relop);

      //## Operation: ParseStatements%1060779898
      void ParseStatements (cContext *context, ShacStatementBlock *sh_statement_block, LINE_VECTOR_T &lines, INT_T depth, cProcedureLine * &first_line, cProcedureLine * &last_line, cProcedureLine *parent_line);

      //## Operation: ParseStatement%1060779897
      cProcedureLine * ParseStatement (cContext *context, ShacStatement *sh_statement, LINE_VECTOR_T &lines, INT_T depth);

      //## Operation: ParseArgument%1061574772
      cArgument * ParseArgument (cContext *context, ShacArgument *sh_argument, UCHAR_T requested_data_type = UNDEFINED);

      //## Operation: CheckTypes%1061805338
      BOOL_T CheckTypes (UCHAR_T requested_data_type, UCHAR_T supplied_data_type, PT_Term *symbol);

      //## Operation: CheckClass%1061805342
      BOOL_T CheckClass (UCHAR_T requested_class, UCHAR_T supplied_class, PT_Term *symbol);

      //## Operation: ConstStringCopy%1072085858
//      CONST_STRING_T ConstStringCopy (CONST_STRING_T str);

      //## Operation: CopyItemSpec%1084888946
      MAP_ITEM_T * CopyItemSpec (cContext *context, MAP_ITEM_T *map_item, cVarDef *var_def);

      //## Operation: ParseFuncRefOptimized%1093975009
      cFuncRef * ParseFuncRefOptimized (cContext *context, CONST_STRING_T func_spec, UCHAR_T requested_data_type = UNDEFINED, UCHAR_T requested_class = UNDEFINED);

      //## Operation: ParseVarRefOptimized%1093975010
      cVarRef * ParseVarRefOptimized (cContext *context, CONST_STRING_T var_spec, UCHAR_T requested_data_type = UNDEFINED);

      //## Operation: ParseText%1108111669
      void ParseText (cContext *context, ShacText *sh_text, cVarDef *var_def);

      //## Operation: ParseDim1Text%1108111664
      void ParseDim1Text (cContext *context, ShacDim1 *sh_dim1_text, cVarDef *var_def);

      //## Operation: ParseDim2Text%1108111665
      void ParseDim2Text (cContext *context, ShacDim2 *sh_dim2_text, cVarDef *var_def);

      //## Operation: ParseDim3Text%1108111666
      void ParseDim3Text (cContext *context, ShacDim3 *sh_dim3_text, cVarDef *var_def);

      //## Operation: ParseDim4Text%1108111667
      void ParseDim4Text (cContext *context, ShacDim4 *sh_dim4_text, cVarDef *var_def);

      //## Operation: ParseFlags%1108111668
      void ParseFlags (cContext *context, ShacFlags *sh_flags, cVarDef *var_def);
      void ParseOption (cContext *context, ShaciraOption *sh_option, cVarDef *var_def);

      //## Operation: ParseUnitDef%1109752578
      cUnitDef * ParseUnitDef (cContext *context, ShacUnitDef *sh_unit_def);

      //## Operation: ParseUnitRef%1109752579
      void ParseUnitRef (cContext *context, ShacUnitRef *sh_unit_ref, cVarDef *var_def);

      //## Operation: ParseSystemFlags%1125675931
      void ParseSystemFlags (cContext *context, ShacSystemFlags *sh_system_flags, cVarDef *var_def);

      //## Operation: ParseError%1040992349
      void ParseError (INT_T err_code, PT_Term *symbol, CONST_STRING_T param = "");

      //## Operation: ParseError%1129135545
      void ParseError (INT_T err_code, int line, int column, CONST_STRING_T obj_name, CONST_STRING_T param = "");

      //## Operation: ParseWarning%1129134826
      void ParseWarning (INT_T err_code, PT_Term *symbol, CONST_STRING_T param = "");

      //## Operation: ParseWarning%1129135546
      void ParseWarning (INT_T err_code, int line, int column, CONST_STRING_T obj_name, CONST_STRING_T param = "");

      //## Operation: Line%1129135111
      int Line (PT_Term *symbol);

      //## Operation: Column%1129135112
      int Column (PT_Term *symbol);

      //## Operation: IsDynamic%1129142496
      BOOL_T IsDynamic (CONST_STRING_T var_name);

    // Data Members for Class Attributes

      //## Attribute: ScanTable%3E0C629302B7
      //## begin cStyxParser::ScanTable%3E0C629302B7.attr preserve=no  implementation: Scn_T {U} NULL
      Scn_T _ScanTable;
      //## end cStyxParser::ScanTable%3E0C629302B7.attr

      //## Attribute: ScanStream%3E0C62E10129
      //## begin cStyxParser::ScanStream%3E0C62E10129.attr preserve=no  implementation: Scn_Stream {U} NULL
      Scn_Stream _ScanStream;
      //## end cStyxParser::ScanStream%3E0C62E10129.attr

      //## Attribute: ParseTable%3E0C62F90187
      //## begin cStyxParser::ParseTable%3E0C62F90187.attr preserve=no  implementation: PLR_Tab {U} NULL
      PLR_Tab _ParseTable;
      //## end cStyxParser::ParseTable%3E0C62F90187.attr

      //## Attribute: ParseConfig%3E0C63100299
      //## begin cStyxParser::ParseConfig%3E0C63100299.attr preserve=no  implementation: PT_Cfg {U} NULL
      PT_Cfg _ParseConfig;
      //## end cStyxParser::ParseConfig%3E0C63100299.attr

      //## Attribute: Root%3E0C636B0285
      //## begin cStyxParser::Root%3E0C636B0285.attr preserve=no  implementation: PT_Term {U} NULL
      PT_Term _Root;
      //## end cStyxParser::Root%3E0C636B0285.attr

      //## Attribute: DynamicVars%434D587200F9
      //## begin cStyxParser::DynamicVars%434D587200F9.attr preserve=no  implementation: STRING_MAP_T {U} 
      STRING_MAP_T _DynamicVars;
      //## end cStyxParser::DynamicVars%434D587200F9.attr

    // Additional Implementation Declarations
      //## begin cStyxParser%3E0C47C10368.implementation preserve=yes
      //## end cStyxParser%3E0C47C10368.implementation

};

//## begin cStyxParser%3E0C47C10368.postscript preserve=yes
//## end cStyxParser%3E0C47C10368.postscript

// Class cStyxParser 

//## begin module%3E0C47C10368.epilog preserve=yes
//## end module%3E0C47C10368.epilog


#endif
