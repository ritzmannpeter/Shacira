/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [prs.h]                      LALR(1) Parser                              */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef prs_INCL
#define prs_INCL


#include "prs_io.h" /* to complete the interface */
#include "otab.h"


#ifdef __cplusplus
extern "C" {
#endif


/* 
   <p>This module [prs] does the actual - low level - parsing based on a given
   STYX-konform parse table definition. ( see <a href="prs_gen.htm">[prs_gen]</a> )
   <p>The parser is reentrant and allows multiple parse operations at a time.
   <p>A second facility refers to its flexible configuration which for example
      allows the use of another scanner than provided by the STYX system.
   <br>
   <p>Within the STYX system the parse interface will only be used by the higher
   level parse and term construction module <a href="ptm_gen.htm">[ptm_gen]</a>.
   <br>
   <p>Beside that the module offers access to the parse table definition.
   <br>
   <p>The parser handles syntax errors as described below:
   <p>On activated early reduction mode and in the case none of the nonterminals
      are specified as resumption points the parse process will stop.
   <p>Otherwise a variant of the panic-mode error recovery method which only tracks
      the specified nonterminals will be applied.
   <br>
*/

/* ------------------------------ Types ------------------------------------- */

AbstractType(PLR_Pdf); /* Abstract parser type */

/* ============================ Parse interface ============================= */

/* ---------------------------- Configuration ------------------------------- */

PLR_Pdf PLR_createPdf(PLR_Tab PTab, StdCPtr extCfg)
/* creates a parser for table 'PTab' and external configuration 'extCfg' */
;

void PLR_addGetF(PLR_Pdf Parser, int (*getToken)(PLR_Pdf Parser))
/* adds next token function 'getToken' to 'Parser' */
;

void PLR_addCurSyF(PLR_Pdf Parser, c_string (*getCurSy)(PLR_Pdf Parser))
/* adds current token name debug function 'getCurSy' to 'Parser' */
;

void PLR_addRedF
     (
       PLR_Pdf Parser,
       StdCPtr (*redVal)(PLR_Pdf Parser, int symcnt, int prodId, c_bool accept)
     )
/* adds reduction function 'redVal' to 'Parser' */
;

void PLR_addSftF
     (
       PLR_Pdf Parser, StdCPtr (*shiftVal)(PLR_Pdf Parser, int symbol)
     )
/* adds shift function 'shiftVal' to 'Parser' */
;

void PLR_addErrF(PLR_Pdf Parser, void (*error)(PLR_Pdf Parser))
/* adds error function 'error' to 'Parser' */
;

void PLR_addDbgF(PLR_Pdf Parser, void (*debug)(PLR_Pdf Parser, StdCPtr val))
/* adds debug function 'debug' to 'Parser' */
;

void    PLR_delPdf(PLR_Pdf Parser);    /* removes 'Parser'                  */

StdCPtr PLR_CfgExt(PLR_Pdf Parser)
#define PLR_CFGEXT(type,pdf) ((type)PLR_CfgExt(pdf))
/* external configuration of 'Parser' */
;

PLR_Tab PLR_CfgTab(PLR_Pdf Parser);    /* parse table of 'Parser'           */

/* ---------------------- Parsing ------------------------------------------- */

c_bool PLR_parse(PLR_Pdf Parser, c_string StartSymbol, c_bool interprete)
/* does the parsing for start nonterminal 'StartSymbol'
   interprete --> early reduction
*/
;

c_bool PLR_accept(PLR_Pdf Parser)
/* whether the parser accepts the EOF token */
;

StdCPtr PLR_topVal(PLR_Pdf Parser)
/* pops and returns the top stack value of 'Parser' */
;

ROW(StdCPtr) PLR_valStack(PLR_Pdf Parser)
/* returns the value stack of 'Parser' ( use with care ! ) */
;


/* ========================= Parse table interface ========================== */

/* --------------------------- Copy & Delete -------------------------------- */

PLR_Tab PLR_copyTab(PLR_Tab PTab);     /* copies parse table 'PTab'         */
void    PLR_delTab(PLR_Tab PTab);      /* removes parse table 'PTab'        */

/* --------------------------- Accessing ------------------------------------ */

c_string PLR_language(PLR_Tab PTab); /* language name of parse table 'PTab' */

int PLR_conflictCnt(PLR_Tab PTab)
/* number of conflicts of parse table 'PTab';
   available only after construction
*/
;

int PLR_tokenCnt(PLR_Tab PTab);  /* number of tokens of parse table 'PTab'  */

int PLR_nontermCnt(PLR_Tab PTab)
/* number of nonterminals of parse table 'PTab' */
;

int PLR_startCnt(PLR_Tab PTab)
/* number of startsymbols of parse table 'PTab' */
;

int PLR_symbolCnt(PLR_Tab PTab); /* number of symbols of parse table 'PTab' */

/* 
  <p><b>Nonterminal conversion macros</b>
*/

/* Nonterminal index to symbol */
#define PLR_NTI_TO_NTS(t,i)   (PLR_tokenCnt(t)+(i))
/* Nonterminal symbol to index */
#define PLR_NTS_TO_NTI(t,s)   ((s)-PLR_tokenCnt(t))
/* Nonterminal symbol to class */
#define PLR_NTS_TO_NTC(t,s)   PLR_ntClass((t), \
                                PLR_ntClassId((t),PLR_NTS_TO_NTI(t,s)))

int PLR_startSymbol(PLR_Tab PTab, int startId)
/* startsymbol 'startId' of parse table 'PTab'
   [startId=0..StartCnt-1] --> [0..SymbolCnt-1]
*/
;

c_bool PLR_isErrorNt(PLR_Tab PTab, int ntId)
/* whether 'ntId' is an error nonterminal of parse table 'PTab'
   [ntId=0..NtCnt-1]
*/
;

int PLR_ntClassId(PLR_Tab PTab, int ntId)
/* class index of nonterminal 'ntId' of parse table 'PTab'
   [ntId=0..NtCnt-1] --> [0..NtCnt-1]
*/
;

int PLR_ntClass(PLR_Tab PTab, int ntClsId)
/* class symbol of nonterminal 'ntId' of parse table 'PTab'
   [ntClsId=0..NtCnt-1] --> [0..SymbolCnt-1]
*/
;

int PLR_symType(PLR_Tab PTab, int symId)
/* type of symbol 'symId' of parse table 'PTab' [symId=0..SymbolCnt-1] */
;

c_string PLR_symName(PLR_Tab PTab, int symId)
/* name of symbol 'symId' of parse table 'PTab' [symId=0..SymbolCnt-1] */
;

int PLR_prodCnt(PLR_Tab PTab)
/* number of productions of parse table 'PTab' */
;

int PLR_prodNonTerm(PLR_Tab PTab, int prodId)
/* nonterminal of production 'prodId' of parse table 'PTab'
   [prodId=0..PCnt-1] --> [0..SymbolCnt-1]
*/
;

int PLR_prodMethod(PLR_Tab PTab, int prodId); /* unused                     */

int PLR_prodSymCnt(PLR_Tab PTab, int prodId)
/* number of members of production 'prodId'
   of parse table 'PTab' [prodId=0..PCnt-1]
*/
;

int PLR_prodSymbol(PLR_Tab PTab, int prodId, int psymId)
/* symbol of production 'prodId' and member 'psymId'
   of parse table 'PTab'
   [prodId=0..PCnt-1,psymId=0..PSCnt-1] --> [0..SymbolCnt-1]
*/
;

int PLR_prodSymFrm(PLR_Tab PTab, int prodId, int psymId)
/* layout info for production 'prodId' and member 'psymId'
   of parse table 'PTab'
   [prodId=0..PCnt-1,psymId=0..PSCnt-1] -->
   [negative(-->NL)] column position
*/
;

c_string PLR_prodName(PLR_Tab PTab, int prodId)
/* name of production 'prodId' of parse table 'PTab'
   [prodId=0..PCnt-1]
*/
;

int PLR_stateCnt(PLR_Tab PTab);   /* number of states in parse table 'PTab' */

ROW(int) PLR_shiftValues(PLR_Tab PTab, int stateId)
/* shift value ( tokenId, followStateId ) ...
   of state 'stateId' in parse table 'PTab'; allocs result row
   [followStateId,stateId=0..StateCnt-1, tokenId=0..TokenCnt-1]
*/
;

ROW(int) PLR_gotoValues(PLR_Tab PTab, int ntId)
/* goto value ( followStateId, fromStateId ) ...
   of nonterminal 'ntId' in parse table 'PTab'; allocs result row
   [followStateId,fromStateId=0..StateCnt-1, ntId=0..NtCnt-1]
*/
;

ROW(int) PLR_actionValues(PLR_Tab PTab, int stateId)
/* action value ( error=-2|accept=-1|prodId, tokenId|startId|-1 ) ...
   of state 'stateId' in parse table 'PTab'; allocs result row
   [stateId=0..StateCnt-1, prodId=0..PCnt-1,
    tokenId=0..TokenCnt-1, startId=TokenCnt..TokenCnt+StartCnt-1]
*/
;



#ifdef __cplusplus
}
#endif

#endif
