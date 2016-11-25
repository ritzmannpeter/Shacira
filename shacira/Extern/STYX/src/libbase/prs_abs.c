/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [prs_abs.c]              Abstract LR Parser Interface                    */
/*                                                                          */
/* Copyright (c) 2002 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "prs_dfn.h"


/*!
   <p>This module [prs_abs] provides an abstract LR parser interface for the
   term generation module <a href="ptm_gen.htm">[ptm_gen]</a>. 
   <p>It can be used to integrate an externally defined parser with the STYX term
   generation facility.
*/

/*I----------------------------- The Types --------------------------------- */

ExternalDecl(AbsPlr_T); /* Abstract parser interface type */


/*!! 
  Types of the parser (interface and configuration) functions 
*/
/*DOC_INTERFACE*/
typedef int      (*PF_cfgsize )(Abs_T parser);
typedef int      (*PF_symType )(Abs_T parser, int symID);
typedef c_string (*PF_symName )(Abs_T parser, int symID);
typedef int      (*PF_startSym)(Abs_T parser, int startID);
typedef int      (*PF_prodNT  )(Abs_T parser, int prodID);
typedef c_string (*PF_prodName)(Abs_T parser, int prodID);
typedef int      (*PIF_nextTok)(AbsPlr_T pconfig);
typedef c_string (*PIF_curTok )(AbsPlr_T pconfig);
typedef Any_T    (*PIF_topVal )(AbsPlr_T pconfig);
typedef Any_T    (*PIF_shift  )(AbsPlr_T pconfig, int symID);
typedef Any_T    (*PIF_reduce )
                 (
                   AbsPlr_T pconfig, int symcnt, int prodID, c_bool accept
                 );
typedef c_bool   (*PIF_parse  )
                 (
                   AbsPlr_T pconfig, c_string symStart, c_bool early
                 );
typedef c_bool   (*PIF_accept )(AbsPlr_T pconfig);
typedef void     (*PIF_error  )(AbsPlr_T pconfig);
typedef void     (*PIF_debug  )(AbsPlr_T pconfig, Any_T value);


ConcreteImp(AbsPlr_T) /* Parser interface type (implementation) */
{
  Abs_T       extCfg;   /* ext. Configuration          */
  Abs_T       extPlr;   /* ext. Parser                 */
  PF_cfgsize  symCnt;   /* CB for PLR_symbolCnt        */
  PF_cfgsize  tokCnt;   /* CB for PLR_tokenCnt         */
  PF_cfgsize  prodCnt;  /* CB for PLR_prodCnt          */
  PF_symType  symType;  /* CB for PLR_symType          */
  PF_symName  symName;  /* CB for PLR_symName          */
  PF_startSym startSym; /* CB for PLR_startSymbol      */
  PF_prodNT   prodNT;   /* CB for PLR_prodNonTerm      */
  PF_prodName prodName; /* CB for PLR_prodName         */
  PIF_nextTok nextTok;  /* CB for 'next token'         */
  PIF_curTok  curTok;   /* CB for 'current token name' */
  PIF_topVal  topVal;   /* CB for 'top stack value'    */
  PIF_shift   shift;    /* CB for 'shift operation'    */
  PIF_reduce  reduce;   /* CB for 'reduce operation'   */
  PIF_parse   parse;    /* CB for 'parse operation'    */
  PIF_accept  accept;   /* CB for 'accept recognizer'  */
  PIF_error   error;    /* CB for 'error reporting'    */
  PIF_debug   debug;    /* CB for 'error reporting'    */
};


/*I---------------------------- Init & Quit -------------------------------- */

AbsPlr_T AP_init(void)
/* creates an abstract parser interface */
{ AbsPlr_T pconfig  = New(AbsPlr_T);
  pconfig->extCfg   = (Abs_T)NULL;
  pconfig->extPlr   = (Abs_T)NULL;
  pconfig->symCnt   = (PF_cfgsize)NULL;
  pconfig->tokCnt   = (PF_cfgsize)NULL;
  pconfig->prodCnt  = (PF_cfgsize)NULL;
  pconfig->symType  = (PF_symType)NULL;
  pconfig->symName  = (PF_symName)NULL;
  pconfig->startSym = (PF_startSym)NULL;
  pconfig->prodNT   = (PF_prodNT)NULL;
  pconfig->prodName = (PF_prodName)NULL;
  pconfig->nextTok  = (PIF_nextTok)NULL;
  pconfig->curTok   = (PIF_curTok)NULL;
  pconfig->topVal   = (PIF_topVal)NULL;
  pconfig->shift    = (PIF_shift)NULL;
  pconfig->reduce   = (PIF_reduce)NULL;
  pconfig->parse    = (PIF_parse)NULL;
  pconfig->accept   = (PIF_accept)NULL;
  pconfig->error    = (PIF_error)NULL;
  pconfig->debug    = (PIF_debug)NULL;
  return pconfig;
}

void AP_quit(AbsPlr_T pconfig)
/* removes abstract parser interface 'pconfig' */
{
  if( pconfig != (AbsPlr_T)NULL ) 
    FreeMem(pconfig);
}

/*I--------------- Specification of the external parser interface ---------- */

void AP_setParser(AbsPlr_T pconfig, Abs_T parser)
/* specifies the external 'parser' of the abstract interface 'pconfig' */
{
  BUG_NULL(pconfig);
  pconfig->extPlr = parser;
}

/*!
  <p>An external defined parser must provide the following interface 
     functions. They have to be assigned to the abstract parser interface 
     before initializing the term generation. That module calls them 
     during the construction of the derivation tree.
*/

void AP_setFunSymCnt(AbsPlr_T pconfig, PF_cfgsize symCnt)
/* specifies 'symCnt' as corresponding function for PLR_symbolCnt 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->symCnt = symCnt;
}

void AP_setFunTokCnt(AbsPlr_T pconfig, PF_cfgsize tokCnt)
/* specifies 'tokCnt' as corresponding function for PLR_tokenCnt 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->tokCnt = tokCnt;
}

void AP_setFunProdCnt(AbsPlr_T pconfig, PF_cfgsize prodCnt)
/* specifies 'prodCnt' as corresponding function for PLR_prodCnt 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->prodCnt = prodCnt;
}

void AP_setFunSymType(AbsPlr_T pconfig, PF_symType symType)
/* specifies 'symType' as corresponding function for PLR_symType 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->symType = symType;
}

void AP_setFunSymName(AbsPlr_T pconfig, PF_symName symName)
/* specifies 'symName' as corresponding function for PLR_symName 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->symName = symName;
}

void AP_setFunStartSym(AbsPlr_T pconfig, PF_startSym startSym)
/* specifies 'startSym' as corresponding function for PLR_startSymbol 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->startSym = startSym;
}

void AP_setFunProdNT(AbsPlr_T pconfig, PF_prodNT prodNT)
/* specifies 'prodNT' as corresponding function for PLR_prodNonTerm 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->prodNT = prodNT;
}

void AP_setFunProdName(AbsPlr_T pconfig, PF_prodName prodName)
/* specifies 'prodName' as corresponding function for PLR_prodName 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->prodName = prodName;
}

void AP_setFunTopVal(AbsPlr_T pconfig, PIF_topVal topVal)
/* specifies 'topVal' as corresponding function for PLR_topVal 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->topVal = topVal;
}

void AP_setFunParse(AbsPlr_T pconfig, PIF_parse parse)
/* specifies 'parse' as corresponding function for PLR_parse 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->parse = parse;
}

void AP_setFunAccept(AbsPlr_T pconfig, PIF_accept accept)
/* specifies 'accept' as corresponding function for PLR_accept 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->accept = accept;
}


/*I--------------- Specification of the external parser configuration ------ */

void AP_setExtCfg(AbsPlr_T pconfig, Abs_T extcfg)
/* specifies the external configuration 'extcfg' 
   of the abstract interface 'pconfig' 
*/
{
  BUG_NULL(pconfig);
  pconfig->extCfg = extcfg;
}

/*!
  <p>An external defined parser must be configurable by the following callback 
     functions. These handlers will be defined and assigned by the term 
     generation module and must be called by the parser during processing.
*/

void AP_setFunNextTok(AbsPlr_T pconfig, PIF_nextTok nextTok)
/* specifies 'nextTok' as "get next token" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->nextTok = nextTok;
}

void AP_setFunCurTok(AbsPlr_T pconfig, PIF_curTok curTok)
/* specifies 'curTok' as "get current token name" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->curTok = curTok;
}

void AP_setFunShift(AbsPlr_T pconfig, PIF_shift shift)
/* specifies 'shift' as "shift operation" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->shift = shift;
}

void AP_setFunReduce(AbsPlr_T pconfig, PIF_reduce reduce)
/* specifies 'reduce' as "reduce operation" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->reduce = reduce;
}

void AP_setFunError(AbsPlr_T pconfig, PIF_error error)
/* specifies 'error' as "error reporting" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->error = error;
}

void AP_setFunDebug(AbsPlr_T pconfig, PIF_debug debug)
/* specifies 'debug' as "debugging" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  pconfig->debug = debug;
}


/*I--------------- Accessing the external parser interface ----------------- */

Abs_T AP_getParser(AbsPlr_T pconfig)
/* get the external parser of the abstract interface 'pconfig' */
{
  BUG_NULL(pconfig);
  return pconfig->extPlr;
}

PF_cfgsize AP_getFunSymCnt(AbsPlr_T pconfig)
/* get the corresponding function for PLR_symbolCnt 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->symCnt;
}

PF_cfgsize AP_getFunTokCnt(AbsPlr_T pconfig)
/* get the corresponding function for PLR_tokenCnt 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->tokCnt;
}

PF_cfgsize AP_getFunProdCnt(AbsPlr_T pconfig)
/* get the corresponding function for PLR_prodCnt 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->prodCnt;
}

PF_symType AP_getFunSymType(AbsPlr_T pconfig)
/* get the corresponding function for PLR_symType 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->symType;
}

PF_symName AP_getFunSymName(AbsPlr_T pconfig)
/* get the corresponding function for PLR_symName 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->symName;
}

PF_startSym AP_getFunStartSym(AbsPlr_T pconfig)
/* get the corresponding function for PLR_startSymbol 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->startSym;
}

PF_prodNT AP_getFunProdNT(AbsPlr_T pconfig)
/* get the corresponding function for PLR_prodNonTerm 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->prodNT;
}

PF_prodName AP_getFunProdName(AbsPlr_T pconfig)
/* get the corresponding function for PLR_prodName 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->prodName;
}

PIF_topVal AP_getFunTopVal(AbsPlr_T pconfig)
/* get the corresponding function for PLR_topVal 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->topVal;
}

PIF_parse AP_getFunParse(AbsPlr_T pconfig)
/* get the corresponding function for PLR_parse 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->parse;
}

PIF_accept AP_getFunAccept(AbsPlr_T pconfig)
/* get the corresponding function for PLR_accept 
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->accept;
}


/*I--------------- Accessing the external parser configuration ------------- */

Abs_T AP_getExtCfg(AbsPlr_T pconfig)
/* get the external configuration 
   of the abstract interface 'pconfig' 
*/
{
  BUG_NULL(pconfig);
  return pconfig->extPlr;
}

PIF_nextTok AP_getFunNextTok(AbsPlr_T pconfig)
/* get the "get next token" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->nextTok;
}

PIF_curTok AP_getFunCurTok(AbsPlr_T pconfig)
/* get the "get current token name" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->curTok;
}

PIF_shift AP_getFunShift(AbsPlr_T pconfig)
/* get the "shift operation" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->shift;
}

PIF_reduce AP_getFunReduce(AbsPlr_T pconfig)
/* get the "reduce operation" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->reduce;
}

PIF_error AP_getFunError(AbsPlr_T pconfig)
/* get the "error reporting" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->error;
}

PIF_debug AP_getFunDebug(AbsPlr_T pconfig)
/* get the "debugging" handler
   in the abstract interface 'pconfig'
*/
{
  BUG_NULL(pconfig);
  return pconfig->debug;
}
