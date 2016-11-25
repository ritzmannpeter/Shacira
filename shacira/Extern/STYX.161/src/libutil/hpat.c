/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [hpat.c]              Template / Pattern Evaluation                      */
/*                                                                          */
/* Copyright (c) 1999 by D\olle, Manns, Steffen                             */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "scn_base.h"
#include "symbols.h"
#include "otab.h"
#include "gls.h"
#include "hpat_int.h"

#include "hmap.h"
#include "hset.h"
#include "ptm.h"
#include "prs.h"
#include "ptm_gen.h"
#include "sink.h"
#include "pathes.h"
#include "line_scn.h"

#include "hpat_lim.h"
#include "hpat_pim.h"

/*!
  <p>The module [hpat] provides some functionality for the evaluation of
  template files based on the context-free grammar [hpat.sty].
  <p>It is used by the <a href="cmd_stydoc.htm">STYX reference generator</a>.
  <br>
*/

/*I------------------------- Types & Macros ----------------------------- */

#define HPAT_TOK_PATREF    "PatRef"
#define HPAT_PREFIX_PATREF '&'

#define HPAT_FUN_REPLACE   "REPLACE"

/*! <p><b>Pattern types</b> */
/*DOC_INTERFACE*/
#define HPAT_REF_LIST   0 // pattern list
#define HPAT_REF_PAT    1 // pattern
#define HPAT_REF_PAR    2 // pattern parameter

AbstractType(HPat_T); // Abstract template type

/*! <p><b>Callback function types</b> */

/*DOC_INTERFACE*/
// pattern reference evaluation function
typedef c_bool (*PFN_Pat)(HPat_T pHPat);

/*DOC_INTERFACE*/
// print function
typedef void (*PFN_PatPrint)(HPat_T pHPat, c_string szTxt);

/*DOC_INTERFACE*/
// replacement specification pattern load function
typedef StdCPtr (*PFN_PatLoad)(GLS_Lst(hpatContent) pLst);
// replacement specification apply function
typedef c_string (*PFN_PatOpr)(c_string szTxt, StdCPtr pData);
// replacement specification free function
typedef void (*PFN_PatFree)(StdCPtr pData);

// documentation pattern type ( implementation )
ConcreteType(HPat_T_IMP)
{
  MAP(symbol,PT_Term)     pPatTreeMap;  // template trees
  MAP(symbol,PT_Term)     pPatMap;      // patterns
  MAP(symbol,ROW(symbol)) pListPatMap;  // list patterns
  MAP(symbol,PFN_Pat)     pPatFunMap;   // pattern reference |--> 
                                        //   generation function
  MAP(symbol,_)           pFunDfnMap;   // special pattern |--> special content
  MAP(symbol,ROW(symbol)) pFunRefMap;   // special patterns <--| apply reference
  MAP(symbol,long)        pPatTypMap;   // pattern reference |--> type
  SET(symbol)             pRefIdSet;    // referenced patterns
  PLR_Tab                 pTab;         // hpat parse table 
  Scn_T                   pScn;         // hpat scanner
  PT_Term                 pFirstTree;   // first template tree
  Abs_T                   pDocCtx;      // documentation context
  PFN_PatPrint            pPrint;       // print text function
  symbol                  pRefAlias;    // reference alias
};

// current pattern context 
static HPat_T_IMP pCurHPat = (HPat_T_IMP)NULL;

// supported special pattern functions
static MAP(symbol,ROW(_)) pSpecialFunMap;

/*I-------------------------- Special Functions -------------------------- */

c_string HP_pat_to_txt(GLS_Lst(hpatContent) pLst)
/* template term list 'pLst' to string; allocs memory */
{ GLS_Lst(hpatContent) pItr, pPatLst;
  Sink pSnk = Sink_open();
  GLS_FORALL(pItr,pLst)
  { hpatContent pContent = GLS_FIRST(hpatContent,pItr);
    GLS_Tok     pOther, pPatRef, pPatHdr, pPatEnd;
    if( hpatContent_else(pContent,&pOther) )
      Sink_printf(pSnk,"%s",GLS_Tok_string(pOther));
    else
    if( hpatContent_pat(pContent,&pPatHdr,&pPatLst,&pPatEnd) )
    { c_string szPat;
      Sink_printf(pSnk,"%s",GLS_Tok_string(pPatHdr));
      szPat = HP_pat_to_txt(pPatLst);
      Sink_printf(pSnk,"%s",szPat);
      FreeMem(szPat);
      Sink_printf(pSnk,"%s",GLS_Tok_string(pPatEnd));
    }
    else
    if( hpatContent_ref(pContent,&pPatRef) )
      Sink_printf(pSnk,"%s",GLS_Tok_string(pPatRef));
  }
  return Sink_close(pSnk);
}

static symbol HP_get_patid(GLS_Tok pPatHdr)
{ c_string     szPatHdr = GLS_Tok_string(pPatHdr),
               szS      = szPatHdr, szId;
  Sink         pSnk     = Sink_open();
  symbol       pId      = (symbol)NULL;
  while( *szS != '\0' && ! isspace(*szS) ) ++szS;
  while( *szS != '\0' && isspace(*szS) )   ++szS;
  while( *szS != '\0' && *szS != '>' && ! isspace(*szS) )
  {
    Sink_putc(pSnk,*szS); ++szS;
  }
  szId = Sink_close(pSnk);
  pId  = stringToSymbol(szId);
  FreeMem(szId);
  return pId;
}

static StdCPtr HP_load_fun_replace(GLS_Lst(hpatContent) pLst)
{ GLS_Lst(hpatContent) pItr, pPatLst;
  MAP(symbol,symbol)   pReplaceMap = MAP_newPrimMap();
  ROW(symbol)          pKeyRow     = OT_CREATE_ADT(symbol),
                       pTxtRow     = OT_CREATE_ADT(symbol);
  long                 lCnt, lI;
  GLS_FORALL(pItr,pLst)
  { hpatContent pContent = GLS_FIRST(hpatContent,pItr);
    GLS_Tok     pPatHdr;
    if( hpatContent_pat(pContent,&pPatHdr,&pPatLst,_) )
    { c_string szTxt;
      symbol   pKey;
      pKey = HP_get_patid(pPatHdr);
      szTxt = HP_pat_to_txt(pPatLst);
      OT_PUSH(pKey,pKeyRow);
      OT_PUSH(stringToSymbol(szTxt),pTxtRow);
      FreeMem(szTxt);
    }
  }
  lCnt = OT_CNT(pKeyRow);
  if( (lCnt % 2) == 0 )
  {
    for( lI=0; lI < lCnt; lI+=2 )
    {
      if( OT_GET(symbol,pKeyRow,lI) == OT_GET(symbol,pKeyRow,lI+1) )
      {
        MAP_dfndom
        (
          pReplaceMap,OT_GET(symbol,pTxtRow,lI),OT_GET(symbol,pTxtRow,lI+1)
        );
      }
      else 
      {
        MAP_freeMap(pReplaceMap); 
        pReplaceMap = (MAP(symbol,symbol))NULL;
        break;
      }
    }
  }
  else 
  {
    MAP_freeMap(pReplaceMap); 
    pReplaceMap = (MAP(symbol,symbol))NULL;
  }
  OT_DEL_T(pKeyRow);
  OT_DEL_T(pTxtRow);
  return pReplaceMap;
}

static c_string HP_apply_fun_replace(c_string szTxt, StdCPtr pData)
{
  return Line_replace(szTxt,(MAP(symbol,symbol))pData);
}

static void HP_free_fun_replace(StdCPtr pData)
{
  MAP_freeMap((MAP(symbol,symbol))pData);
}

/*I------------------------- Init & Quit -------------------------------- */

void HP_init(void)
/* initializes template evaluation module */
{ ROW(_) pFunRow = OT_CREATE_ADT(_);
  hpat_initSymbols();
  pSpecialFunMap = MAP_newPrimMap();
  MAP_dfndom(pSpecialFunMap,stringToSymbol(HPAT_FUN_REPLACE),pFunRow);
  OT_PUSH(HP_load_fun_replace,pFunRow);
  OT_PUSH(HP_apply_fun_replace,pFunRow);
  OT_PUSH(HP_free_fun_replace,pFunRow);
}

void HP_quit(void)
/* terminates template evaluation module */
{ MAPIT  pItr;
  symbol pPatSym;
  ROW(_) pFunRow;
  MAP_forItrAsg(pPatSym,pFunRow,pItr,pSpecialFunMap) 
    OT_DEL_T(pFunRow);
  MAP_freeMap(pSpecialFunMap);
  hpat_quitSymbols();
}

/*I------------------------- Create & Dispose --------------------------- */

HPat_T HP_create(void)
/* creates a template evaluation object */
{ HPat_T_IMP pHPat = New(HPat_T_IMP);
  pHPat->pPatTreeMap  = MAP_newPrimMap();
  pHPat->pPatMap      = MAP_newPrimMap();
  pHPat->pListPatMap  = MAP_newPrimMap();
  pHPat->pPatFunMap   = MAP_newPrimMap();
  pHPat->pPatTypMap   = MAP_newPrimMap();
  pHPat->pRefIdSet    = HS_CREATE_ADTSET(symbol);
  pHPat->pFunDfnMap   = MAP_newPrimMap();
  pHPat->pFunRefMap   = MAP_newPrimMap();
  Scn_get_hpat(&pHPat->pScn);
  pHPat->pTab         = PLR_get_hpat();
  pHPat->pFirstTree   = (PT_Term)NULL;
  pHPat->pDocCtx      = (Abs_T)NULL;
  pHPat->pPrint       = (PFN_PatPrint)NULL;
  pHPat->pRefAlias    = (symbol)NULL;
  return (HPat_T)pHPat;
}

void HP_drop(HPat_T pHP)
/* frees template evaluation object 'pHP' */
{ HPat_T_IMP  pHPat = (HPat_T_IMP)pHP;
  MAPIT       pItr;
  PT_Term     pTree;
  ROW(symbol) pRow;
  symbol      pSym;
  StdCPtr     pData;
  MAP_forItrAsg(pSym,pTree,pItr,pHPat->pPatTreeMap) 
  {
    if( pTree != (PT_Term)NULL ) PT_delT(pTree);
  }
  MAP_freeMap(pHPat->pPatTreeMap);
  MAP_freeMap(pHPat->pPatMap);
  MAP_forItrAsg(pSym,pRow,pItr,pHPat->pListPatMap) OT_DEL_T(pRow);
  MAP_freeMap(pHPat->pListPatMap);
  MAP_freeMap(pHPat->pPatFunMap);
  MAP_freeMap(pHPat->pPatTypMap);
  HS_DROP_SET(pHPat->pRefIdSet);
  MAP_forItrAsg(pSym,pData,pItr,pHPat->pFunDfnMap) 
  { PFN_PatFree pPatFree;
    pPatFree = OT_GET(PFN_PatFree,MAP_apply(ROW(_),pSpecialFunMap,pSym),2);
    (*pPatFree)(pData);
  }
  MAP_freeMap(pHPat->pFunDfnMap);
  MAP_forItrAsg(pSym,pRow,pItr,pHPat->pFunRefMap) OT_DEL_T(pRow);
  MAP_freeMap(pHPat->pFunRefMap);
  if( pHPat->pScn != (Scn_T)NULL ) Scn_free(pHPat->pScn);
  PLR_delTab(pHPat->pTab);
  FreeMem(pHPat);
}

/*I------------------------- Get & Set ---------------------------------- */

void HP_setContext(HPat_T pHP, Abs_T pDocCtx)
/* sets evaluation context 'pDocCtx' in template object 'pHP' */
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  pHPat->pDocCtx = pDocCtx;
}

Abs_T HP_getContext(HPat_T pHP)
/* evaluation context of template object 'pHP' */
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  return pHPat->pDocCtx;
}

void HP_setPrintFun(HPat_T pHP, PFN_PatPrint pPrint)
/* sets print function 'pPrint' in template object 'pHP' */
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  pHPat->pPrint  = pPrint;
}

PFN_PatPrint HP_getPrintFun(HPat_T pHP)
/* print function of template object 'pHP' */
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  return pHPat->pPrint;
}

void HP_setRefAlias(HPat_T pHP, symbol pRefAlias)
/* sets reference alias 'pRefAlias' in template object 'pHP' 
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  pHPat->pRefAlias = pRefAlias;
}

symbol HP_getRefAlias(HPat_T pHP)
/* reference alias of template object 'pHP' */
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  return pHPat->pRefAlias;
}

void HP_addPatSpec
     (
       HPat_T pHP, symbol pPat, PFN_Pat pPatFun, long lPatTyp
     )
/* adds/overwrites evaluation function 'pPatFun' 
   for pattern 'pPat' of type 'lPatTyp'
   to template object 'pHP' 
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  MAP_ovrdom(pHPat->pPatFunMap,pPat,pPatFun); 
  MAP_ovrdom(pHPat->pPatTypMap,pPat,lPatTyp); 
}

PFN_Pat HP_getPatFun(HPat_T pHP, symbol pPat)
/* evaluation function for pattern 'pPat'
   in template object 'pHP' 
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  if( MAP_defined(pHPat->pPatFunMap,pPat) )
    return MAP_apply(PFN_Pat,pHPat->pPatFunMap,pPat);
  else return (PFN_Pat)NULL;
}

ROW(symbol) HP_getListPatRow(HPat_T pHP, symbol pListPat)
/* member patterns of pattern list 'pListPat' 
   in template object 'pHP' 
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  if( MAP_defined(pHPat->pListPatMap,pListPat) )
    return MAP_apply(ROW(symbol),pHPat->pListPatMap,pListPat);
  else return (ROW(symbol))NULL;
}

void HP_setScanner(HPat_T pHP, Scn_T pScn)
/* sets external scanner 'pScn' in template object 'pHP' 
   ( will be removed by HP_drop ) 
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  if( pHPat->pScn != (Scn_T)NULL ) Scn_free(pHPat->pScn);
  pHPat->pScn = pScn;
}

Scn_T HP_getScanner(HPat_T pHP)
/* pattern scanner of template object 'pHP' */
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  return pHPat->pScn;
}

symbol HP_getPatRef(GLS_Tok pPatRef)
/* symbol of pattern refernce token 'pPatRef' */
{ c_string szPatRef = StrCopy(GLS_Tok_string(pPatRef)+1);
  symbol   pResult;
  szPatRef[strlen(szPatRef)-1] = '\0';
  pResult = stringToSymbol(szPatRef);
  FreeMem(szPatRef);
  return pResult;
}

c_bool HP_addSpecialFun
       (
         symbol      pPatSym, 
         PFN_PatLoad pPatLoad,
         PFN_PatOpr  pPatOpr,
         PFN_PatFree pPatFree
       )
/* adds special evaluation functions for 
   replacement specification pattern 'pPatSym'
   'pPatLoad': loads replacement specification
   'pPatOpr' : applies replacement specification
   'pPatFree': frees replacement specification
   ( RC = ok/error ) 
*/
{
  if( ! MAP_defined(pSpecialFunMap,pPatSym) )
  { ROW(_) pFunRow = OT_CREATE_ADT(_);
    MAP_dfndom(pSpecialFunMap,pPatSym,pFunRow);
    OT_PUSH(pPatLoad,pFunRow);
    OT_PUSH(pPatOpr,pFunRow);
    OT_PUSH(pPatFree,pFunRow);
    return C_True;
  }
  else return C_False;
}

/*I------------------------- Load & Check ------------------------------- */

static symbol HP_add_pat(HPat_T_IMP pHPat, hpatContent pContent)
/* add template pattern */
{ GLS_Tok pPatHdr;
  symbol  pFunSym = (symbol)NULL;
  if( hpatContent_pat(pContent,&pPatHdr,_,_) )
  { c_string     szPatHdr = GLS_Tok_string(pPatHdr),
                 szS      = szPatHdr, szId;
    Sink         pSnk     = Sink_open();
    symbol       pId, pPatId;
    while( *szS != '\0' && ! isspace(*szS) ) ++szS;
    while( *szS != '\0' && isspace(*szS) )   ++szS;
    while( *szS != '\0' && *szS != '>' && ! isspace(*szS) )
    {
      Sink_putc(pSnk,*szS); ++szS;
    }
    szId = Sink_close(pSnk);
    pId  = stringToSymbol(szId);
    FreeMem(szId);
    if( ! MAP_defined(pHPat->pPatMap,pId)    &&
        ! MAP_defined(pHPat->pFunDfnMap,pId)  )
    {
      if( MAP_defined(pSpecialFunMap,pId) )
        pFunSym = pId;
      else MAP_dfndom(pHPat->pPatMap,pId,pContent);
      while( *szS != '\0' && isspace(*szS) ) ++szS;
      if( *szS != '>' )
      { ROW(symbol) pPatIdRow = (ROW(symbol))NULL;
        if( pFunSym == (symbol)NULL )
        {
          pPatIdRow = OT_CREATE_ADT(symbol);
          MAP_dfndom(pHPat->pListPatMap,pId,pPatIdRow);
        }
        while( *szS != '\0' && *szS != '>' )
        {
          pSnk = Sink_open();
          while( *szS != '\0' && *szS != '>' && ! isspace(*szS) )
          {
            Sink_putc(pSnk,*szS); ++szS;
          }
          szId   = Sink_close(pSnk);
          pPatId = stringToSymbol(szId);
          FreeMem(szId);
          if( pFunSym == (symbol)NULL )
            OT_PUSH(pPatId,pPatIdRow);
          else 
          { ROW(symbol) pRefRow;
            if( MAP_defined(pHPat->pFunRefMap,pPatId) )
              pRefRow = MAP_apply(ROW(symbol),pHPat->pFunRefMap,pPatId);
            else
            {
              pRefRow = OT_CREATE_ADT(symbol);
              MAP_dfndom(pHPat->pFunRefMap,pPatId,pRefRow);
            }
            OT_PUSH(pId,pRefRow);
          }
          while( *szS != '\0' && isspace(*szS) ) ++szS;
        }
      }
    }
    else PT_error(pPatHdr,"pattern '%s' already defined",symbolToString(pId));
  }
  return pFunSym;
}

static void HP_load_content
            (
              HPat_T_IMP pHPat, GLS_Lst(hpatContent) pLst, c_bool bRecursive
            )
/* load pattern content */
{ GLS_Lst(hpatContent) pItr, pPatLst;
  GLS_FORALL(pItr,pLst)
  { hpatContent pContent = GLS_FIRST(hpatContent,pItr);
    GLS_Tok     pPatRef;
    if( hpatContent_pat(pContent,_,&pPatLst,_) )
    { symbol pFunSym = HP_add_pat(pHPat,pContent);
      if( pFunSym != (symbol)NULL )
      { PFN_PatLoad pPatLoad;
        StdCPtr     pData;
        pPatLoad = OT_GET
                   (
                     PFN_PatLoad,MAP_apply(ROW(_),pSpecialFunMap,pFunSym),0
                   );
        pData    = (*pPatLoad)(pPatLst);
        if( pData != (StdCPtr)NULL )
        {
          MAP_dfndom(pHPat->pFunDfnMap,pFunSym,pData);
        }
        else
        {
          PT_error
          (
            pContent,"load of pattern '%s' failed",symbolToString(pFunSym)
          );
        }
      }
      else
      if( bRecursive ) HP_load_content(pHPat,pPatLst,bRecursive);
    }
    else
    if( hpatContent_ref(pContent,&pPatRef) )
    { symbol pRefId = HP_getPatRef(pPatRef);
      if( MAP_defined(pHPat->pPatFunMap,pRefId) &&
          MAP_defined(pHPat->pPatTypMap,pRefId) &&
          MAP_apply(long,pHPat->pPatTypMap,pRefId) != HPAT_REF_PAR )
        HS_SET_ELM(pRefId,pHPat->pRefIdSet);
    }
  }
}

static int HP_premac
           (
             Scn_Stream pStream, string cTokNam, string cTokVal, symbol* cMacVal
           )
/* pre-process token */
{ symbol pValSym = stringToSymbol(cTokVal);
  if( !strcmp(cTokNam,HPAT_TOK_PATREF) && pCurHPat->pRefAlias == pValSym )
  { 
    *cMacVal = (symbol)HPAT_PREFIX_PATREF;
    return SCN_FLG_RescanChar;
  }
  else
  { 
    *cMacVal = pValSym;
    return SCN_FLG_RescanNone;
  }
}

c_bool HP_load
       (
         HPat_T pHP, Scn_Stream pStream, symbol pSrcId,
         symbol pRootPat, c_bool bRecursive
       )
/* loads template pattern from scan stream 'pStream' 
   into template object 'pHP'
   'pSrcId'    : optional source identifier
   'pRootPat'  : root pattern for evaluation
   'bRecursive': recursive evaluation
   ( RC = ok/error ) 
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  PT_Cfg     pCfg; 
  PT_Term    pTree;
  symbol     pStreamId;
  pStreamId = Stream_cfil(pStream);
  if( pHPat->pRefAlias != (symbol)NULL )
  {
    pCurHPat = pHPat;
    Stream_premac_set(pStream, HP_premac);
  }
  Stream_concat_other(pStream);
  pCfg      = PT_init(pHPat->pTab,pStream);
  pTree     = PT_PARSE(pCfg,"");
  if( pHPat->pRefAlias != (symbol)NULL ) 
    pCurHPat = (HPat_T_IMP)NULL;
  PT_setErrorCnt(PT_errorCnt() + PT_synErrorCnt(pCfg));
  PT_quit(pCfg);
  Stream_close(pStream);
  Stream_free(pStream);
  if( pSrcId != (symbol)NULL )
    MAP_dfndom(pHPat->pPatTreeMap,pSrcId,pTree);
  else MAP_dfndom(pHPat->pPatTreeMap,pStreamId,pTree);
  if( PT_errorCnt() == 0 )
  { GLS_Lst(hpatContent) pLst;
    hpatHPatDoc          pSrc;
    if( pHPat->pFirstTree == (PT_Term)NULL )
      pHPat->pFirstTree = pTree;
    hpat_Start_HPatDoc(pTree,&pSrc);
    hpatHPatDoc_dfn(pSrc,&pLst);
    HP_load_content(pHPat,pLst,bRecursive);
    if( pRootPat != (symbol)NULL ) 
    {
      if( MAP_defined(pHPat->pPatFunMap,pRootPat) &&
          MAP_defined(pHPat->pPatTypMap,pRootPat) &&
          MAP_apply(long,pHPat->pPatTypMap,pRootPat) != HPAT_REF_PAR )
        HS_SET_ELM(pRootPat,pHPat->pRefIdSet);
      else PT_error(pTree,"root pattern '%s'",symbolToString(pRootPat));
    }
  }
  return PT_errorCnt() == 0;
}

c_bool HP_check(HPat_T pHP)
/* checks loaded template pattern in template object 'pHP'
   ( RC = ok/error ) 
*/
{ HPat_T_IMP  pHPat = (HPat_T_IMP)pHP;
  HS_Itr      pSItr;
  MAPIT       pMItr;
  ROW(symbol) pRow;
  PT_Term     pTree;
  symbol      pPatId, pRefId;
  MAP_forItrAsg(pPatId,pRow,pMItr,pHPat->pListPatMap)
  { long lCnt = OT_CNT(pRow), lI;
    for( lI=0; lI < lCnt; ++lI )
    {
      pRefId = OT_GET(symbol,pRow,lI);
      if( ! MAP_defined(pHPat->pPatMap,pRefId) )
      {
        pTree = MAP_apply(PT_Term,pHPat->pPatMap,pPatId);
        PT_error(pTree,"missing pattern '%s'",symbolToString(pRefId));
      }
    }
  }
  HS_FORALL(pRefId,pSItr,pHPat->pRefIdSet)
  { long lPatTyp = MAP_apply(long,pHPat->pPatTypMap,pRefId);
    if( lPatTyp == HPAT_REF_LIST && ! MAP_defined(pHPat->pListPatMap,pRefId) )
      PT_error
      (
        pHPat->pFirstTree,"missing list pattern '%s'",symbolToString(pRefId)
      );
    else
    if( lPatTyp == HPAT_REF_PAT && ! MAP_defined(pHPat->pPatMap,pRefId) )
      PT_error(pHPat->pFirstTree,"missing pattern '%s'",symbolToString(pRefId));
  }
  return PT_errorCnt() == 0;
}

/*I------------------------- Output Generation -------------------------- */

/*forward*/ void HP_gendoc_pat(HPat_T pHP, symbol pPatSym);

void HP_gendoc_ref(HPat_T pHP, GLS_Tok pPatRef)
/* evaluates and prints reference token 'pPatRef'
   according template object 'pHP'
*/
{ HPat_T_IMP  pHPat   = (HPat_T_IMP)pHP;
  symbol      pRefSym = HP_getPatRef(pPatRef);
  if( MAP_defined(pHPat->pPatFunMap,pRefSym) )
  { PFN_Pat pPatFun = MAP_apply(PFN_Pat,pHPat->pPatFunMap,pRefSym);
    if( ! (*pPatFun)(pHP) )
      PT_error(pPatRef,"misplaced reference '%s'",symbolToString(pRefSym));
  }
  else
  if( MAP_defined(pHPat->pPatMap,pRefSym)       &&
      ! MAP_defined(pHPat->pListPatMap,pRefSym)  )
    HP_gendoc_pat(pHP,pRefSym);
  else
  if( pHPat->pPrint != (PFN_PatPrint)NULL )
    (*pHPat->pPrint)(pHP,GLS_Tok_string(pPatRef));
}

static void HP_gendoc_content(HPat_T_IMP pHPat, GLS_Lst(hpatContent) pLst)
/* generate content */
{ hpatContent          pTxt;
  GLS_Lst(hpatContent) pSubLst, pItr;
  GLS_FORALL(pItr,pLst)
  { GLS_Tok pPatRef, pPatHdr, pPatEnd, pOther;
    pTxt = GLS_FIRST(hpatContent,pItr);
    if( hpatContent_ref(pTxt,&pPatRef) )
      HP_gendoc_ref(pHPat,pPatRef);
    else
    if( hpatContent_else(pTxt,&pOther) && pHPat->pPrint != (PFN_PatPrint)NULL )
      (*pHPat->pPrint)(pHPat,GLS_Tok_string(pOther));
    else
    if( hpatContent_pat(pTxt,&pPatHdr,&pSubLst,&pPatEnd) )
    {
      if( pHPat->pPrint != (PFN_PatPrint)NULL )
        (*pHPat->pPrint)(pHPat,GLS_Tok_string(pPatHdr));
      HP_gendoc_content(pHPat,pSubLst);
      if( pHPat->pPrint != (PFN_PatPrint)NULL )
        (*pHPat->pPrint)(pHPat,GLS_Tok_string(pPatEnd));
    }
  }
}

c_bool HP_fun_defined(HPat_T pHP, symbol pRefSym)
/* whether template object 'pHP' contains a
   replacement specification for pattern 'pRefSym' 
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  return MAP_defined(pHPat->pFunRefMap,pRefSym);
}

c_string HP_fun_apply(HPat_T pHP, symbol pRefSym, c_string szTxt)
/* applies the replacement specification for pattern 'pRefSym' 
   in template object 'pHP' to text 'szText' 
   RC = szTxt, if no functions defined, else result text
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  c_string   szRes = szTxt, szTmp;
  if( MAP_defined(pHPat->pFunRefMap,pRefSym) )
  { ROW(symbol) pFunRow = MAP_apply(ROW(symbol),pHPat->pFunRefMap,pRefSym);
    long        lCnt    = OT_CNT(pFunRow), lI;
    for( lI=0; lI < lCnt; ++lI )
    { symbol     pPatSym = OT_GET(symbol,pFunRow,lI);
      PFN_PatOpr pPatOpr;
      pPatOpr = OT_GET(PFN_PatOpr,MAP_apply(ROW(_),pSpecialFunMap,pPatSym),1);
      szTmp   = (*pPatOpr)(szRes,MAP_apply(StdCPtr,pHPat->pFunDfnMap,pPatSym));
      if( szRes != szTxt ) FreeMem(szRes);
      szRes = szTmp;
    }
  }
  return szRes;
}

void HP_gendoc_pat(HPat_T pHP, symbol pPatSym)
/* evaluates and prints pattern 'pPatSym'
   according template object 'pHP'
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  if( MAP_defined(pHPat->pPatMap,pPatSym) )
  { hpatContent          pPat  = MAP_apply(hpatContent,pHPat->pPatMap,pPatSym);
    GLS_Lst(hpatContent) pLst;
    assert0(hpatContent_pat(pPat,_,&pLst,_), "");
    HP_gendoc_content(pHPat,pLst);
  }
}

void HP_gendoc_src(HPat_T pHP, symbol pSrcId)
/* evaluates and prints template 'pSrcId'
   according template object 'pHP'
*/
{ HPat_T_IMP pHPat = (HPat_T_IMP)pHP;
  if( MAP_defined(pHPat->pPatTreeMap,pSrcId) )
  { PT_Term              pTree = MAP_apply(PT_Term,pHPat->pPatTreeMap,pSrcId);
    hpatHPatDoc          pSrc;
    GLS_Lst(hpatContent) pLst;
    hpat_Start_HPatDoc(pTree,&pSrc);
    hpatHPatDoc_dfn(pSrc,&pLst);
    HP_gendoc_content(pHPat,pLst);
  }
}
