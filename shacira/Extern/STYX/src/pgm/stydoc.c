/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [stydoc.c]            STYX Documentation Generator                       */
/*                                                                          */
/* Copyright (c) 1999 by D\olle, Manns, Steffen                             */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"
#include "scn_base.h"
#include "scn_pre.h"
#include "prs.h"
#include "ptm.h"
#include "ptm_gen.h"
#include "cfg_abs.h"
#include "symbols.h"
#include "hmap.h"
#include "hset.h"
#include "sink.h"
#include "line_scn.h"
#include "pathes.h"

#include "hpat.h"

#include "styx_int.h"
#include "styx_lim.h"
#include "styx_pim.h"
#include "styd_cim.h"


/* ------------------------- Macros, Types & Globals ---------------------- */

#define infile            CTX_EVAL(c_string,"InFile")
#define outfile           CTX_EVAL(c_string,"OutFile")
#define styxpath          CTX_EVAL(c_string,"StyxPath")
#define template          CTX_EVAL(c_string,"Template")
#define refalias          CTX_EVAL(c_string,"RefAlias")
#define recursiv          CTX_EVAL(c_bool,"recursiv")
#define prodcom           CTX_EVAL(c_bool,"prodcom")
#define nts_to_keep       CTX_EVAL(c_string,"keepNTs")
#define cls_to_split      CTX_EVAL(c_string,"noClass")
#define excl_prods        CTX_EVAL(c_string,"exProds")
#define ign_rref          CTX_EVAL(c_string,"ignRRef")
#define binpath           CTX_EVAL(string,"BINSTYX")

/* STYX Documentation Pattern */
#define SD_PAT_CFGDFN     stringToSymbol("cfgdfn")
#define SD_PAT_COMSEC     stringToSymbol("comsec")
#define SD_PAT_TKMSEC     stringToSymbol("tkmsec")
#define SD_PAT_NTMSEC     stringToSymbol("ntmsec")
#define SD_PAT_PRDSEC     stringToSymbol("prdsec")
#define SD_PAT_MBRSEC     stringToSymbol("mbrsec")
#define SD_PAT_CFGID      stringToSymbol("cfgid")
#define SD_PAT_DFNID      stringToSymbol("dfnid")
#define SD_PAT_DFNREF     stringToSymbol("dfnref")
#define SD_PAT_LANREF     stringToSymbol("lanref")
#define SD_PAT_DFNCAT     stringToSymbol("dfncat")
#define SD_PAT_DFNOPT     stringToSymbol("dfnopt")
#define SD_PAT_MBRID      stringToSymbol("mbrid")
#define SD_PAT_DFNCOM     stringToSymbol("dfncom")
#define SD_PAT_GRPCOM     stringToSymbol("grpcom")
#define SD_PAT_BOTCOM     stringToSymbol("botcom")
#define SD_PAT_OPTCOM     stringToSymbol("optgrpcom")
#define SD_PAT_NEWLINE    stringToSymbol("nl")


ConcreteType(StyDoc_T)
{
  PT_Term                  pTree;    // STYX derivation tree of 'infile'
  MAP(symbol,ROW(PT_Term)) pDfnCom;  // comments of token, nonterminal 
                                     // and production definitions
  MAP(symbol,ROW(PT_Term)) pGrpCom;  // post definition --> group comments 
  PLR_Tab                  pTab;     // language parse table
  int*                     aPol;     // nonterminal/class types
  SET(int)*                aNtm;     // nonterminal partition
  SET(int)*                aPrd;     // nonterminal productions
  MAP(symbol,styxQlxDfn)   pGMap;    // group symbol |--> definition
  MAP(symbol,styxQlxDfn)   pTMap;    // token symbol |--> definition
  MAP(symbol,long)         pNTMap;   // nonterminal symbol |--> index 
  MAP(symbol,symbol)       pClsMap;  // nonterminal symbol |--> class symbol
  SET(symbol)              pLSet;    // embedded languages
  ROW(_)                   pDocBase; // language documentation base:
                                     // ROW( T/NT symbol, 
                                     //   ROW(ROW(T/NTGroup/Value symbol)) ) 
  HPat_T                   pHPat;    // template pattern
  // generation context 
  FILE*                    pSysOut;  // output fp
  long                     lDocIdx;  // 0 .. pDocBase.Count/2-1 oder -1
  long                     lMbrIdx;  // 0 .. pDocBase.pCurRow.Count-1 or -1
  long                     lComIdx;  // current start index into comment row
  ROW(symbol)              pCurRow;  // 0 .. pDocBase.lDocIdx.Count-1 or -1
};

static SET(symbol)             pNTsToKeep;
static SET(symbol)             pClsToSplit;
static SET(symbol)             pIgnRecRef;
static MAP(symbol,SET(symbol)) pExcludedProds;

static c_bool                  bConcreteCfg = C_False;


/* ------------------------- Auxiliary ------------------------------------ */

static c_string SD_com_string
                (
                  ROW(PT_Term) pComments, long* lIdx
                )
/* comment token --> string */
{ c_string szResult = (string)NULL;
  long lCnt = OT_CNT(pComments), lDiff, lI = *lIdx;
  Sink pSnk = Sink_open();
  for( ; *lIdx < lCnt; ++(*lIdx) )
  { PT_Term t = OT_GET(PT_Term,pComments,*lIdx), p;
    if( !PT_isComment(t) ) 
    {
      ++(*lIdx); break;
    }
    else 
    {
      if( *lIdx > lI )
      {
        p = OT_GET(PT_Term,pComments,(*lIdx)-1);
        lDiff = PT_row(t) - PT_row(p);
        if( lDiff >= 2 )
          Sink_printf(pSnk,"\n\n");
        else
        if( lDiff == 1 )
          Sink_printf(pSnk,"\n");
      }
      Sink_printf(pSnk,"\n%s",GLS_Tok_string(t)+1);
    }
  }
  szResult = Sink_close(pSnk);
  return szResult;
}

static long SD_getIgnNTIdx(long lPrdIdx, StyDoc_T pStyDoc)
{ long lMbrCnt, lSym, lTyp, lI;
  lMbrCnt = PLR_prodSymCnt(pStyDoc->pTab,lPrdIdx);
  for( lI=0; lI < lMbrCnt; ++lI )
  {
    lSym = PLR_prodSymbol(pStyDoc->pTab,lPrdIdx,lI); 
    lTyp = PLR_symType(pStyDoc->pTab,lSym);
    if( CFG_NTM(lTyp) ) return lSym - PLR_tokenCnt(pStyDoc->pTab);
  }
  C_BUG; return -1;
}

static c_bool SD_IsLLProd(long lPrdIdx, StyDoc_T pStyDoc)
{ long lTCnt  = PLR_tokenCnt(pStyDoc->pTab),
       lNTIdx = PLR_prodNonTerm(pStyDoc->pTab,lPrdIdx);
  return( lNTIdx == PLR_prodSymbol(pStyDoc->pTab,lPrdIdx,0) - lTCnt );
}

static c_bool SD_IsNTUnion(ROW(symbol) pNTLine)
{ long lCnt = OT_CNT(pNTLine), lI;
  for( lI=0; lI < lCnt; ++lI )
  { c_string szSymbol = symbolToString(OT_GET(symbol,pNTLine,lI));
    if( ! strcmp(szSymbol,"\"|\"") ) return C_True;
  }
  return C_False;
}

static bool SD_IsNTRecRef(long lNTIdx, StyDoc_T pStyDoc)
{ long     lClsIdx  = PLR_ntClassId(pStyDoc->pTab,lNTIdx),
           lSym     = lNTIdx + PLR_tokenCnt(pStyDoc->pTab),
           lClsSym  = lClsIdx + PLR_tokenCnt(pStyDoc->pTab);
  c_string szSym    = PLR_symName(pStyDoc->pTab,lSym),
           szClsSym = PLR_symName(pStyDoc->pTab,lClsSym);
  symbol   pSym     = stringToSymbol(szSym),
           pClsSym  = stringToSymbol(szClsSym);
  return ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_RECREF) &&
         ! HS_MBR_ELM(pSym,pIgnRecRef) &&
         ! HS_MBR_ELM(pClsSym,pIgnRecRef);
}

static c_bool SD_IsNTSequence(ROW(symbol) pNTLine)
{ long lCnt = OT_CNT(pNTLine);
  if( lCnt > 1 )
  { c_string szSymbol = symbolToString(OT_GET(symbol,pNTLine,0));
    if( ( ! strncmp(szSymbol,"\"(\"",3) || 
          ! strncmp(szSymbol,"\"{\"",3) ||
          ! strncmp(szSymbol,"\"[\"",3)  ) &&
        ( atol(szSymbol+3) + 2 == lCnt     ||
          ( atol(szSymbol+3) + 2 == lCnt - 1 &&
            !strcmp(symbolToString(OT_GET(symbol,pNTLine,lCnt-1)),"\"+\"") ) ) )
      return C_True;
    else
    if( lCnt == 2 && 
        ! strcmp(symbolToString(OT_GET(symbol,pNTLine,1)),"\"+\"") )
      return C_True;
    return C_False;
  }
  else return C_True;
}

static ROW(symbol) SD_rowToNTSeq
                   (
                     c_bool bCond, c_string szSeq, 
                     ROW(symbol) pDstRow, ROW(symbol) pSrcRow
                   )
{ ROW(symbol) pResRow = pDstRow;
  if( bCond )
  { c_string szSym;
    if( pDstRow == pSrcRow ) pResRow = OT_CREATE_ADT(symbol);
    szSym = Str_printf("\"%c\"%ld",szSeq[0],OT_CNT(pSrcRow));
    OT_PUSH(stringToSymbol(szSym),pResRow);
    FreeMem(szSym);
    OT_APPEND(pResRow,pSrcRow);
    szSym = Str_printf("\"%c\"",szSeq[1]);
    OT_PUSH(stringToSymbol(szSym),pResRow);
    FreeMem(szSym);
    if( pDstRow == pSrcRow ) OT_DEL_T(pDstRow);
  }
  else 
  if( pDstRow != pSrcRow ) OT_APPEND(pResRow,pSrcRow);
  return pResRow;
}

static ROW(symbol) SD_symbolToNTSeq
                   (
                     c_bool bCond, c_string szSeq, 
                     ROW(symbol) pDstRow, symbol pSrcSym
                   )
{
  if( bCond )
  { c_string szSym = Str_printf("\"%c\"1",szSeq[0]);
    OT_PUSH(stringToSymbol(szSym),pDstRow);
    FreeMem(szSym);
    OT_PUSH(pSrcSym,pDstRow);
    szSym = Str_printf("\"%c\"",szSeq[1]);
    OT_PUSH(stringToSymbol(szSym),pDstRow);
    FreeMem(szSym);
  }
  else OT_PUSH(pSrcSym,pDstRow);
  return pDstRow;
}

static c_bool SD_IsNTMetaSym(symbol pNTSym, symbol* ppMetaSym)
{ c_string szNTSym = symbolToString(pNTSym), 
           szS     = szNTSym;
  if( *szS == '"' )
  { char szBuffer[STD_BUFFLEN+1];
    int  nI = 0;
    for( szS++; *szS != '"' && *szS != '\0'; ++nI, ++szS )
      szBuffer[nI] = *szS;
    szBuffer[nI] = '\0';
    if( ppMetaSym != (symbol*)NULL ) 
      *ppMetaSym = stringToSymbol(szBuffer);
    return C_True;
  }
  else return C_False;
}

static c_bool SD_IsTMetaSym(symbol pTSym)
// Meta-Symbols: ()|+{}[]<>-/, and ..
{ c_string szMetaSet = "(){}[]<>|+-/,",
           szTSym    = symbolToString(pTSym);
  if( strlen(szTSym) == 1 )
    return strstr(szMetaSet,szTSym) != (c_string)NULL;
  if( strlen(szTSym) == 2 )
    return !strcmp(szTSym,"..") ||
           !strcmp(szTSym,">=") ||
           !strcmp(szTSym,"<=") ||
           !strcmp(szTSym,"<?");
  return C_False;
}

/* ------------------------- Init & Quit ---------------------------------- */

static void SD_init(int argc, c_string argv[])
/* init STYX documentation generation */
{ c_string szS, szT;
  PIT      pItr;
  CTX_init_stydoc(argc,argv);
  initSymbols();
  MAP_init();
  styx_initSymbols();
  HP_init();
  pClsToSplit = HS_CREATE_ADTSET(symbol);
  if( !strcmp(cls_to_split,"--all--") )
    bConcreteCfg = C_True;
  else
  if( strlen(cls_to_split) > 0 )
  {
    pItr = PIT_make(cls_to_split); 
    while( ( szS = PIT_read(pItr) ) != NULL )
      HS_SET_ELM(stringToSymbol(szS),pClsToSplit);
    PIT_drop(pItr);
  }
  pNTsToKeep = HS_CREATE_ADTSET(symbol);
  if( !bConcreteCfg && strlen(nts_to_keep) > 0 )
  {
    pItr = PIT_make(nts_to_keep); 
    while( ( szS = PIT_read(pItr) ) != NULL )
      HS_SET_ELM(stringToSymbol(szS),pNTsToKeep);
    PIT_drop(pItr);
  }
  pIgnRecRef = HS_CREATE_ADTSET(symbol);
  if( !bConcreteCfg && strlen(ign_rref) > 0 )
  {
    pItr = PIT_make(ign_rref); 
    while( ( szS = PIT_read(pItr) ) != NULL )
      HS_SET_ELM(stringToSymbol(szS),pIgnRecRef);
    PIT_drop(pItr);
  }
  pExcludedProds = MAP_newPrimMap();
  if( strlen(excl_prods) > 0 )
  { 
    pItr = PIT_make(excl_prods); 
    while( ( szS = PIT_read(pItr) ) != NULL )
    {
      szT = strstr(szS,".");
      if( szT != (c_string)NULL )
      { symbol      pNTSym, pProdSym;
        SET(symbol) pProdSet;
        *szT     = '\0';
        pNTSym   = stringToSymbol(szS);
        pProdSym = stringToSymbol(szT+1);
        *szT     = '.';
        if( MAP_defined(pExcludedProds,pNTSym) )
          pProdSet = MAP_apply(SET(symbol),pExcludedProds,pNTSym);
        else 
        {
          pProdSet = HS_CREATE_ADTSET(symbol);
          MAP_dfndom(pExcludedProds,pNTSym,pProdSet);
        }
        HS_SET_ELM(pProdSym,pProdSet);
      }
    }
    PIT_drop(pItr);
  }
}

static void SD_quit(void)
/* quit STYX documentation generation */
{ MAPIT       pItr;
  SET(symbol) pProdSet;
  symbol      pNTSym;
  MAP_forItrAsg(pNTSym,pProdSet,pItr,pExcludedProds)
    HS_DROP_SET(pProdSet);
  MAP_freeMap(pExcludedProds);
  HS_DROP_SET(pNTsToKeep);
  HS_DROP_SET(pClsToSplit);
  HS_DROP_SET(pIgnRecRef);
  HP_quit();
  styx_quitSymbols();
  MAP_quit();
  freeSymbols();
  CTX_quit();
}

static StyDoc_T SD_init_base(void)
/* init documentation base */
{ StyDoc_T pStyDoc     = New(StyDoc_T);
  pStyDoc->pDfnCom     = MAP_newPrimMap();
  pStyDoc->pGrpCom     = MAP_newPrimMap();
  pStyDoc->pTree       = (PT_Term)NULL;
  pStyDoc->pTab        = (PLR_Tab)NULL;
  pStyDoc->aPol        = (int*)NULL;
  pStyDoc->aNtm        = (SET(int)*)NULL;
  pStyDoc->aPrd        = (SET(int)*)NULL;
  pStyDoc->pGMap       = MAP_newPrimMap();
  pStyDoc->pTMap       = MAP_newPrimMap();
  pStyDoc->pNTMap      = MAP_newPrimMap();
  pStyDoc->pClsMap     = MAP_newPrimMap();
  pStyDoc->pLSet       = HS_CREATE_ADTSET(symbol);
  pStyDoc->pDocBase    = OT_CREATE_ADT(_);
  pStyDoc->pHPat       = (HPat_T)NULL;
  pStyDoc->pSysOut     = (FILE*)NULL;
  pStyDoc->lDocIdx     = -1;
  pStyDoc->lComIdx     = -1;
  pStyDoc->lMbrIdx     = -1;
  pStyDoc->pCurRow     = (ROW(symbol))NULL;
  return pStyDoc;
}

/* ------------------------- Output Generation ---------------------------- */

static void SD_gendoc_raw(StyDoc_T pStyDoc)
/* generate raw documentation - without template */
{ long lCnt = OT_CNT(pStyDoc->pDocBase)/2, lI, lJ, lK;
  fprintf(pStyDoc->pSysOut,"\n%s - CFG Section\n",PLR_language(pStyDoc->pTab));
  for( lI=0; lI < lCnt; ++lI )
  { ROW(ROW(symbol)) pLines = OT_GET
                              (
                                ROW(ROW(symbol)),
                                pStyDoc->pDocBase,pStyDoc->lDocIdx*2+1
                              );
    symbol           pSym   = OT_GET
                              (
                                symbol,pStyDoc->pDocBase,pStyDoc->lDocIdx*2
                              ),
                              pMbrSym;
    if( lI >= MAP_count(pStyDoc->pTMap) &&
        MAP_defined(pStyDoc->pClsMap,pSym) )
      pSym = MAP_apply(symbol,pStyDoc->pClsMap,pSym);
    if( lI == 0 ) 
      fprintf(pStyDoc->pSysOut,"\nToken Section\n");
    else 
    if( lI == MAP_count(pStyDoc->pTMap) )
      fprintf(pStyDoc->pSysOut,"\nNonterminal Section\n");
    fprintf(pStyDoc->pSysOut,"\n");
    for( lJ=0; lJ < OT_CNT(pLines); ++lJ )
    { ROW(symbol) pCurRow = OT_GET(ROW(symbol),pLines,lJ);
      fprintf(pStyDoc->pSysOut,"\n\t%s ::",symbolToString(pSym));
      for( lK=0; lK < OT_CNT(pCurRow); ++lK )
      {
        pMbrSym = OT_GET(symbol,pCurRow,lK);
        if( lI >= MAP_count(pStyDoc->pTMap) &&
            MAP_defined(pStyDoc->pClsMap,pMbrSym) )
          pMbrSym = MAP_apply(symbol,pStyDoc->pClsMap,pMbrSym);
        fprintf(pStyDoc->pSysOut," %s",symbolToString(pMbrSym));
      }
    }
  }
}

static void SD_gendoc_txt(HPat_T pHPat, c_string szTxt)
/* generate documentation according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  fprintf(pStyDoc->pSysOut,"%s",szTxt);
}

static c_bool SD_gendoc_dref(HPat_T pHPat)
/* generate definition reference according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  pStyDoc->lComIdx = 0;
  if( pStyDoc->lDocIdx >= 0 && pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 )
  { symbol pSym = OT_GET(symbol,pStyDoc->pDocBase,pStyDoc->lDocIdx*2);
    if( pStyDoc->lDocIdx >= MAP_count(pStyDoc->pTMap) )
    {
      if( MAP_defined(pStyDoc->pClsMap,pSym) )
        pSym = MAP_apply(symbol,pStyDoc->pClsMap,pSym);
    }
    fprintf(pStyDoc->pSysOut,"%s",symbolToString(pSym));
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_did(HPat_T pHPat)
/* generate definition id according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  pStyDoc->lComIdx = 0;
  if( pStyDoc->lDocIdx >= 0 && pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 )
  { symbol pSym = OT_GET(symbol,pStyDoc->pDocBase,pStyDoc->lDocIdx*2);
    if( pStyDoc->lDocIdx < MAP_count(pStyDoc->pTMap) )
    { styxQlxDfn pQDfn = MAP_apply(styxQlxDfn,pStyDoc->pTMap,pSym);
      styxQlxGrp pSGrp, pDGrp; GLS_Tok pSId, pDId;
      assert0( styxQlxDfn_defn(pQDfn,_,_,&pSGrp,_,&pDGrp,_), "" );
      if( styxQlxGrp_non(pSGrp) && styxQlxGrp_non(pDGrp) )
        fprintf(pStyDoc->pSysOut,"%s",symbolToString(pSym));
      else
      { Sink pSnk = Sink_open(); c_string szID;
        if( styxQlxGrp_grp(pSGrp,&pSId) )
        {
          Sink_printf(pSnk,"%s:",GLS_Tok_string(pSId));
        }
        Sink_printf(pSnk,"%s",symbolToString(pSym));
        if( styxQlxGrp_grp(pDGrp,&pDId) )
        {
          Sink_printf(pSnk,":%s",GLS_Tok_string(pDId));
        }
        else
        if( styxQlxGrp_igrp(pDGrp) )
        {
          Sink_printf(pSnk,":[initial]");
        }
        else
        if( styxQlxGrp_pgrp(pDGrp,&pDId) )
        {
          Sink_printf(pSnk,":[push], %s",GLS_Tok_string(pDId));
        }
        else
        if( styxQlxGrp_pigrp(pDGrp) )
        {
          Sink_printf(pSnk,":[push], [initial]");
        }
        else
        if( styxQlxGrp_pop(pDGrp) )
        {
          Sink_printf(pSnk,":[pop]");
        }
        szID = Sink_close(pSnk);
        fprintf(pStyDoc->pSysOut,"%s",szID);
        FreeMem(szID);
      }
    }
    else
    {
      if( MAP_defined(pStyDoc->pClsMap,pSym) )
        pSym = MAP_apply(symbol,pStyDoc->pClsMap,pSym);
      fprintf(pStyDoc->pSysOut,"%s",symbolToString(pSym));
    }
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_lref(HPat_T pHPat)
/* generate embedded language reference according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  if( pStyDoc->lDocIdx >= 0                          && 
      pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 && 
      pStyDoc->pCurRow != (ROW(symbol))NULL          &&
      pStyDoc->lMbrIdx >= 0                          && 
      pStyDoc->lMbrIdx < OT_CNT(pStyDoc->pCurRow)     )
  { symbol pMbrSym = OT_GET(symbol,pStyDoc->pCurRow,pStyDoc->lMbrIdx);
    if( strlen(outfile) > 0 )
    { MAP(symbol,symbol) pReplaceMap = MAP_newPrimMap();
      c_string szPath = FilePrefix(outfile), szFile;
      MAP_dfndom
      (
        pReplaceMap,stringToSymbol(PLR_language(pStyDoc->pTab)),pMbrSym
      );
      szFile = Line_replace(outfile+strlen(szPath),pReplaceMap);
      fprintf(pStyDoc->pSysOut,"%s%s",szPath,szFile);
      MAP_freeMap(pReplaceMap);
      FreeMem(szPath); FreeMem(szFile);
    }
    else
      fprintf(pStyDoc->pSysOut,"#%s",symbolToString(pMbrSym));
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_dcom(HPat_T pHPat)
/* generate definition comment according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  if( pStyDoc->lDocIdx >= 0 && pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 )
  { symbol pSym = OT_GET(symbol,pStyDoc->pDocBase,pStyDoc->lDocIdx*2);
    if( MAP_defined(pStyDoc->pDfnCom,pSym) &&
        ( pStyDoc->lComIdx == 0 || prodcom  ) )
    { ROW(PT_Term) pComments = MAP_apply(ROW(PT_Term),pStyDoc->pDfnCom,pSym);
      string       szCom = SD_com_string(pComments,&pStyDoc->lComIdx);
      if( szCom && HP_fun_defined(pHPat,SD_PAT_DFNCOM) )
      { c_string szRCom = HP_fun_apply(pHPat,SD_PAT_DFNCOM,szCom);
        if( szCom != szRCom )
        {
          FreeMem(szCom); szCom = szRCom;
        }
      }
      HP_gendoc_pat(pHPat,SD_PAT_NEWLINE);
      fprintf(pStyDoc->pSysOut,"%s",szCom);
      if( szCom != (string)NULL ) FreeMem(szCom);
    }
    else fprintf(pStyDoc->pSysOut," ");
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_ocom(HPat_T pHPat)
/* generate group comment section according template or "" */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  pStyDoc->lComIdx = 0;
  if( pStyDoc->lDocIdx >= 0 && pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 )
  { symbol pSym = OT_GET(symbol,pStyDoc->pDocBase,pStyDoc->lDocIdx*2);
    if( MAP_defined(pStyDoc->pGrpCom,pSym) )
    { 
      HP_gendoc_pat(pHPat,SD_PAT_COMSEC);
    }
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_gcom(HPat_T pHPat)
/* generate group comment according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  pStyDoc->lComIdx = 0;
  if( pStyDoc->lDocIdx >= 0 && pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 )
  { symbol pSym = OT_GET(symbol,pStyDoc->pDocBase,pStyDoc->lDocIdx*2);
    if( MAP_defined(pStyDoc->pGrpCom,pSym) )
    { ROW(PT_Term) pComments = MAP_apply(ROW(PT_Term),pStyDoc->pGrpCom,pSym);
      string       szCom = SD_com_string(pComments,&pStyDoc->lComIdx);
      if( szCom && HP_fun_defined(pHPat,SD_PAT_GRPCOM) )
      { c_string szRCom = HP_fun_apply(pHPat,SD_PAT_GRPCOM,szCom);
        if( szCom != szRCom )
        {
          FreeMem(szCom); szCom = szRCom;
        }
      }
      fprintf(pStyDoc->pSysOut,"%s",szCom);
      if( szCom != (string)NULL ) FreeMem(szCom);
    }
    else fprintf(pStyDoc->pSysOut," ");
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_bcom(HPat_T pHPat)
/* generate last group comment according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  pStyDoc->lComIdx = 0;
  if( MAP_defined(pStyDoc->pGrpCom,NULL) )
  { ROW(PT_Term) pComments = MAP_apply(ROW(PT_Term),pStyDoc->pGrpCom,NULL);
    string       szCom = SD_com_string(pComments,&pStyDoc->lComIdx);
    if( szCom && HP_fun_defined(pHPat,SD_PAT_BOTCOM) )
    { c_string szRCom = HP_fun_apply(pHPat,SD_PAT_BOTCOM,szCom);
      if( szCom != szRCom )
      {
        FreeMem(szCom); szCom = szRCom;
      }
    }
    fprintf(pStyDoc->pSysOut,"%s",szCom);
    if( szCom != (string)NULL ) FreeMem(szCom);
  }
  else fprintf(pStyDoc->pSysOut," ");
  return C_True;
}

static c_bool SD_gendoc_dcat(HPat_T pHPat)
/* generate definition category according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  if( pStyDoc->lDocIdx >= 0 && pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 )
  { symbol pSym = OT_GET(symbol,pStyDoc->pDocBase,pStyDoc->lDocIdx*2);
    if( pStyDoc->lDocIdx < MAP_count(pStyDoc->pTMap) )
    { styxQlxDfn pQDfn = MAP_apply(styxQlxDfn,pStyDoc->pTMap,pSym);
      styxQlxCat pQCat;
      assert0( styxQlxDfn_defn(pQDfn,&pQCat,_,_,_,_,_), "" );
      if( styxQlxCat_letC(pQCat) ) fprintf(pStyDoc->pSysOut,"let");
      else
      if( styxQlxCat_comC(pQCat) ) fprintf(pStyDoc->pSysOut,"com");
      else
      if( styxQlxCat_ignC(pQCat) ) fprintf(pStyDoc->pSysOut,"ign");
      else
      if( styxQlxCat_tokC(pQCat) ) fprintf(pStyDoc->pSysOut,"tok");
      else
      if( styxQlxCat_lanC(pQCat) ) fprintf(pStyDoc->pSysOut,"lan");
      else
      if( styxQlxCat_indC(pQCat) ) fprintf(pStyDoc->pSysOut,"ind");
    }
    else
    { long lNTIdx = MAP_apply(long,pStyDoc->pNTMap,pSym);
      if( ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_START) )
        fprintf(pStyDoc->pSysOut,"start");
      else fprintf(pStyDoc->pSysOut,"let");
    }
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_dopt(HPat_T pHPat)
/* generate definition option according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  if( pStyDoc->lDocIdx >= 0 && pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 )
  { symbol pSym = OT_GET(symbol,pStyDoc->pDocBase,pStyDoc->lDocIdx*2);
    if( pStyDoc->lDocIdx < MAP_count(pStyDoc->pTMap) )
    { styxQlxDfn pQDfn = MAP_apply(styxQlxDfn,pStyDoc->pTMap,pSym);
      styxQlxCat pQOpt;
      assert0( styxQlxDfn_defn(pQDfn,_,&pQOpt,_,_,_,_), "" );
      if( styxQlxOpt_ignca(pQOpt) ) fprintf(pStyDoc->pSysOut,"[I]");
    }
    else
    { long lNTIdx = MAP_apply(long,pStyDoc->pNTMap,pSym);
      if( PLR_isErrorNt(pStyDoc->pTab,lNTIdx) )
        fprintf(pStyDoc->pSysOut,"[E]");
    }
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_mid(HPat_T pHPat)
/* generate member id according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  if( pStyDoc->lDocIdx >= 0                          && 
      pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 && 
      pStyDoc->pCurRow != (ROW(symbol))NULL          &&
      pStyDoc->lMbrIdx >= 0                          && 
      pStyDoc->lMbrIdx < OT_CNT(pStyDoc->pCurRow)     )
  { symbol pMbrSym = OT_GET(symbol,pStyDoc->pCurRow,pStyDoc->lMbrIdx),
           pDocSym = pMbrSym;
    if( pStyDoc->lDocIdx >= MAP_count(pStyDoc->pTMap) )
    {
      if( ! SD_IsNTMetaSym(pMbrSym,&pDocSym) )
      {
        if( MAP_defined(pStyDoc->pClsMap,pDocSym) )
          pDocSym = MAP_apply(symbol,pStyDoc->pClsMap,pDocSym);
      }
    }
    if( !HP_fun_defined(pHPat,SD_PAT_MBRID) )
      fprintf(pStyDoc->pSysOut,"%s",symbolToString(pDocSym));
    else
    { c_string szRes = HP_fun_apply
                       (
                         pHPat,SD_PAT_MBRID,symbolToString(pDocSym)
                       );
      fprintf(pStyDoc->pSysOut,"%s",szRes);
      if( szRes != symbolToString(pDocSym) ) FreeMem(szRes);
    }
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_cid(HPat_T pHPat)
/* generate language id according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  fprintf(pStyDoc->pSysOut,"%s",PLR_language(pStyDoc->pTab));
  return C_True;
}

static c_bool SD_gendoc_dsec(HPat_T pHPat, symbol pSec)
/* generate definition section according template */
{ StyDoc_T    pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  long        lCnt    = ( pSec == SD_PAT_TKMSEC )
                        ? MAP_count(pStyDoc->pTMap) 
                        : OT_CNT(pStyDoc->pDocBase)/2,
              lBgn    = ( pSec == SD_PAT_TKMSEC )
                        ? 0 : MAP_count(pStyDoc->pTMap),
              lDocIdx, lMbrIdx, lI, lJ;
  ROW(symbol) pRow    = HP_getListPatRow(pHPat,pSec), pCurRow;
  symbol      pDfn    = OT_GET(symbol,pRow,0);
  lDocIdx = pStyDoc->lDocIdx;
  lMbrIdx = pStyDoc->lMbrIdx;
  pCurRow = pStyDoc->pCurRow;
  for( lI=lBgn, lJ=0; lI < lCnt; ++lI, ++lJ )
  { ROW(ROW(symbol)) pLines = OT_GET(ROW(ROW(symbol)),pStyDoc->pDocBase,2*lI+1);
    if( lJ > 0 ) 
    {
      HP_gendoc_pat(pHPat,pSec);
      if( OT_CNT(pRow) > lJ ) pDfn = OT_GET(symbol,pRow,lJ);
    }
    pStyDoc->lDocIdx = lI;
    pStyDoc->lMbrIdx = -1;
    pStyDoc->pCurRow = ( lI < MAP_count(pStyDoc->pTMap) )
                       ? OT_GET(ROW(symbol),pLines,0) : (ROW(symbol))NULL;
    HP_gendoc_pat(pHPat,pDfn);
  } 
  pStyDoc->lDocIdx = lDocIdx;
  pStyDoc->lMbrIdx = lMbrIdx;
  pStyDoc->pCurRow = pCurRow;
  return C_True;
}

static c_bool SD_gendoc_tsec(HPat_T pHPat)
/* generate token section according template */
{ 
  return SD_gendoc_dsec(pHPat,SD_PAT_TKMSEC);
}

static c_bool SD_gendoc_nsec(HPat_T pHPat)
/* generate nonterminal section according template */
{ 
  return SD_gendoc_dsec(pHPat,SD_PAT_NTMSEC);
}

static c_bool SD_gendoc_psec(HPat_T pHPat)
/* generate production section according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  if( pStyDoc->lDocIdx >= 0                          && 
      pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2  )
  { ROW(ROW(symbol)) pLines = OT_GET
                              (
                                ROW(ROW(symbol)),
                                pStyDoc->pDocBase,pStyDoc->lDocIdx*2+1
                              );
    ROW(symbol)      pRow   = HP_getListPatRow(pHPat,SD_PAT_PRDSEC), pCurRow;
    symbol           pDfn   = OT_GET(symbol,pRow,0);
    long             lCnt   = OT_CNT(pLines), lI;
    pCurRow = pStyDoc->pCurRow;
    for( lI=0; lI < lCnt; ++lI )
    {
      if( lI > 0 ) 
      {
        HP_gendoc_pat(pHPat,SD_PAT_PRDSEC);
        if( OT_CNT(pRow) > lI ) pDfn = OT_GET(symbol,pRow,lI);
      }
      pStyDoc->pCurRow = OT_GET(ROW(symbol),pLines,lI);
      HP_gendoc_pat(pHPat,pDfn);
    } 
    pStyDoc->pCurRow = pCurRow;
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_msec(HPat_T pHPat)
/* generate member section according template */
{ StyDoc_T pStyDoc = (StyDoc_T)HP_getContext(pHPat);
  if( pStyDoc->lDocIdx >= 0                          && 
      pStyDoc->lDocIdx < OT_CNT(pStyDoc->pDocBase)/2 && 
      pStyDoc->pCurRow != (ROW(symbol))NULL           )
  { ROW(symbol) pPRow = HP_getListPatRow(pHPat,SD_PAT_MBRSEC);
    symbol      pRPat = OT_GET(symbol,pPRow,0), 
                pMPat = OT_CNT(pPRow) >= 2 ? OT_GET(symbol,pPRow,1) : pRPat,
                pVPat = OT_CNT(pPRow) >= 3 ? OT_GET(symbol,pPRow,2) : pMPat,
                pLPat = OT_CNT(pPRow) >= 4 ? OT_GET(symbol,pPRow,3) : pRPat,
                pMbrSym;
    long        lCnt  = OT_CNT(pStyDoc->pCurRow), lMbrIdx, lI;
    lMbrIdx = pStyDoc->lMbrIdx;
    for( lI=0; lI < lCnt; ++lI )
    {
      if( lI > 0 ) HP_gendoc_pat(pHPat,SD_PAT_MBRSEC);
      pMbrSym = OT_GET(symbol,pStyDoc->pCurRow,lI);
      pStyDoc->lMbrIdx = lI;
      if( HS_MBR_ELM(pMbrSym,pStyDoc->pLSet) )
      {
        HP_gendoc_pat(pHPat,pLPat);
      }
      else
      if( MAP_defined(pStyDoc->pNTMap,pMbrSym) || 
          MAP_defined(pStyDoc->pTMap,pMbrSym)   )
      {
        HP_gendoc_pat(pHPat,pRPat);
      }
      else
      if( pStyDoc->lDocIdx < MAP_count(pStyDoc->pTMap) )
      {
        if( SD_IsTMetaSym(pMbrSym) )
          HP_gendoc_pat(pHPat,pMPat);
        else HP_gendoc_pat(pHPat,pVPat);
      }
      else
      {
        if( SD_IsNTMetaSym(pMbrSym,(symbol*)NULL)          ||
            !strcmp(symbolToString(pMbrSym),PLR_TOK_Other)  )
          HP_gendoc_pat(pHPat,pMPat);
        else HP_gendoc_pat(pHPat,pVPat);
      }
    }
    pStyDoc->lMbrIdx = lMbrIdx;
    return C_True;
  }
  return C_False;
}

static c_bool SD_gendoc_cfg(HPat_T pHPat)
/* generate documentation according template */
{
  HP_gendoc_pat(pHPat,SD_PAT_CFGDFN);
  return C_True;
}

/* ------------------------- Load & Unload -------------------------------- */

#define IS_QEXP_UDC(e) (    styxExp_union(e,_,_)  \
                         || styxExp_diff(e,_,_)   \
                         || styxExp_conc(e,_,_)   ) 

static void SD_collectSubExps(styxExp e, SET(styxExp) pSubExps)
// collection of sub expression ( ... ) 
{ PT_Itr it;
  PT_FORALL(it,e)
  { PT_Term t = PT_termIT(it), p;
    if (PT_stateIT(it) == PT_PRAE)
    { styxExp exp; 
      if (styx_Exp(t,&exp) && ignProd(symbolToString(PT_product(exp))))
      {
        p = PT_parts(exp);
        while( p != (PT_Term)NULL && !PT_isNonTerm(p) )
        {
          if( PT_isKey(p) && !strcmp(symbolToString(PT_value(p)),"(") )
          {
            p = PT_ign_Skip(exp);
            if( p != (PT_Term)NULL ) HS_SET_ELM(p,pSubExps);
          }
          p = PT_next(p);
        }
      }
    }
  }
}

static void SD_evalQExp(styxExp e, ROW(symbol) l, SET(styxExp) pSubExps)
// Meta-Symbols: ()|+{}[]- and ..
{ styxExp exp1, exp2, exp3; styxLimit limit = {0}; GLS_Tok tok;
  if( styxExp_quot(e,&exp1,&exp2) )
  {
    SD_evalQExp(exp1,l,pSubExps);
    OT_PUSH(stringToSymbol("/"),l);
    SD_evalQExp(exp2,l,pSubExps);
  }
  else
  if( styxExp_dyck(e,&exp1,&exp2,&exp3) )
  { 
     OT_PUSH(stringToSymbol("<"),l);
     SD_evalQExp(exp1,l,pSubExps);
     OT_PUSH(stringToSymbol(">"),l);
     SD_evalQExp(exp2,l,pSubExps);
     OT_PUSH(stringToSymbol("<"),l);
     SD_evalQExp(exp3,l,pSubExps);
     OT_PUSH(stringToSymbol(">"),l);
  }
  else
  if( styxExp_spat(e,&exp1,&tok,&exp2) || styxExp_epat(e,&exp1,&tok,&exp2) )
  { 
    if( styxExp_spat(e,_,_,_) )
      OT_PUSH(stringToSymbol("<="),l);
    else
      OT_PUSH(stringToSymbol("<?"),l);
    SD_evalQExp(exp1,l,pSubExps);
    OT_PUSH(stringToSymbol(">"),l);
    OT_PUSH(GLS_Tok_symbol(tok),l);
    OT_PUSH(stringToSymbol("<"),l);
    SD_evalQExp(exp2,l,pSubExps);
    OT_PUSH(stringToSymbol(">"),l);
  }
  else
  if( styxExp_union(e,&exp1,&exp2) )
  { 
    if( HS_MBR_ELM(exp1,pSubExps) )
    {
      OT_PUSH(stringToSymbol("("),l);
      SD_evalQExp(exp1,l,pSubExps);
      OT_PUSH(stringToSymbol(")"),l);
    }
    else SD_evalQExp(exp1,l,pSubExps);
    OT_PUSH(stringToSymbol("|"),l);
    if( HS_MBR_ELM(exp2,pSubExps) )
    {
      OT_PUSH(stringToSymbol("("),l);
      SD_evalQExp(exp2,l,pSubExps);
      OT_PUSH(stringToSymbol(")"),l);
    }
    else SD_evalQExp(exp2,l,pSubExps);
  }
  else
  if( styxExp_diff(e,&exp1,&exp2) )
  { 
    if( HS_MBR_ELM(exp1,pSubExps) )
    {
      OT_PUSH(stringToSymbol("("),l);
      SD_evalQExp(exp1,l,pSubExps);
      OT_PUSH(stringToSymbol(")"),l);
    }
    else SD_evalQExp(exp1,l,pSubExps);
    OT_PUSH(stringToSymbol("-"),l);
    if( HS_MBR_ELM(exp2,pSubExps) )
    {
      OT_PUSH(stringToSymbol("("),l);
      SD_evalQExp(exp2,l,pSubExps);
      OT_PUSH(stringToSymbol(")"),l);
    }
    else SD_evalQExp(exp2,l,pSubExps);
  }
  else
  if( styxExp_conc(e,&exp1,&exp2) )
  { 
    if( HS_MBR_ELM(exp1,pSubExps) )
    {
      OT_PUSH(stringToSymbol("("),l);
      SD_evalQExp(exp1,l,pSubExps);
      OT_PUSH(stringToSymbol(")"),l);
    }
    else SD_evalQExp(exp1,l,pSubExps);
    if( HS_MBR_ELM(exp2,pSubExps) )
    {
      OT_PUSH(stringToSymbol("("),l);
      SD_evalQExp(exp2,l,pSubExps);
      OT_PUSH(stringToSymbol(")"),l);
    }
    else SD_evalQExp(exp2,l,pSubExps);
  }
  else
  if( styxExp_opt(e,&exp1) )
  { 
    OT_PUSH(stringToSymbol("["),l);
    SD_evalQExp(exp1,l,pSubExps);
    OT_PUSH(stringToSymbol("]"),l);
  }
  else
  if( styxExp_star(e,&exp1) || styxExp_plus0(e,&exp1) )
  { 
    OT_PUSH(stringToSymbol("{"),l);
    SD_evalQExp(exp1,l,pSubExps);
    OT_PUSH(stringToSymbol("}"),l);
  }
  else
  if( styxExp_plus(e,&exp1) || styxExp_plusn(e,&exp1,&limit) )
  { 
    if( HS_MBR_ELM(exp1,pSubExps) )
    {
      OT_PUSH(stringToSymbol("("),l);
      SD_evalQExp(exp1,l,pSubExps);
      OT_PUSH(stringToSymbol(")"),l);
    }
    else SD_evalQExp(exp1,l,pSubExps);
    if( styxExp_plus(e,_) )
      OT_PUSH(stringToSymbol("+"),l);
    else
    { styxOptNat optnat;
      if( styxLimit_ntime(limit,&tok) )
        OT_PUSH(GLS_Tok_symbol(tok),l);
      else
      if( styxLimit_range(limit,&tok,&optnat) )
      {
        if( styxOptNat_non(optnat) )
        {
          OT_PUSH(stringToSymbol(">="),l);
          OT_PUSH(GLS_Tok_symbol(tok),l);
        }
        else
        {
          OT_PUSH(GLS_Tok_symbol(tok),l);
          OT_PUSH(stringToSymbol(","),l);
          assert( styxOptNat_nat(optnat,&tok), "");
          OT_PUSH(GLS_Tok_symbol(tok),l);
        }
      }
    }
  }
  else
  if( styxExp_range(e,&exp1,&exp2) )
  { 
    SD_evalQExp(exp1,l,pSubExps);
    OT_PUSH(stringToSymbol(".."),l);
    SD_evalQExp(exp2,l,pSubExps);
  }
  else
  if( styxExp_set(e,&tok) )
  {
    OT_PUSH(GLS_Tok_symbol(tok),l);
  }
  else
  if( styxExp_sequ(e,&tok) )
  {
    OT_PUSH(GLS_Tok_symbol(tok),l);
  }
  else
  if( styxExp_ident(e,&tok) )
  {
    OT_PUSH(GLS_Tok_symbol(tok),l);
  }
  else 
  if( !styxExp_non(e) ) C_BUG;
}

static void SD_load_com(StyDoc_T pStyDoc)
/* load comments */
{ PT_Itr pItr; GLS_Tok pIde; 
  ROW(PT_Term) pComments    = NULL;
  ROW(PT_Term) pGrpComments = NULL;
  long lRow = 0, lDRow = 0;
  PT_FORALL(pItr,pStyDoc->pTree)
  { PT_Term t = PT_termIT(pItr), c;
    if (PT_stateIT(pItr) == PT_PRAE)
    { 
      if( PT_hasPos(t) )
      {
        lRow = PT_row(t);
        if( PT_isComment(t) && strstr(GLS_Tok_string(t),";;") == NULL )
        { 
          if( pComments == NULL )
          {
            if( pGrpComments == NULL )
            {
              pGrpComments = OT_CREATE_ADT(PT_Term);
            }
            OT_PUSH(t,pGrpComments);
          }
          else
          {
            if( lDRow == lRow || lDRow + 1 == lRow ) 
              OT_PUSH(t,pComments);
            else
            {
              if( OT_CNT(pComments) > 0 )
              {
                c = OT_TOP(PT_Term,pComments);
                if( lRow == (long)(PT_row(c) + 1) )
                  OT_PUSH(t,pComments);
                else
                {
                  if( pGrpComments == NULL )
                  {
                    pGrpComments = OT_CREATE_ADT(PT_Term);
                  }
                  OT_PUSH(t,pGrpComments);
                }
              }
              else
              {
                if( pGrpComments == NULL )
                {
                  pGrpComments = OT_CREATE_ADT(PT_Term);
                }
                OT_PUSH(t,pGrpComments);
              }
            }
          }
        }
        else
        if( PT_isNonTerm(t) )
        { 
          if( styx_QlxDfn(t,_) )
          {
            assert0(   styxQlxDfn_defn((styxQlxDfn)t,_,_,_,&pIde,_,_)
                    || styxQlxDfn_igrp((styxQlxDfn)t,&pIde)
                    || styxQlxDfn_xgrp((styxQlxDfn)t,&pIde)
                    || styxQlxDfn_mgrp((styxQlxDfn)t,&pIde,_), "");
            if( !MAP_defined(pStyDoc->pDfnCom,GLS_Tok_symbol(pIde)) )
            {
              pComments = OT_CREATE_ADT(PT_Term);
              MAP_dfndom(pStyDoc->pDfnCom,GLS_Tok_symbol(pIde),pComments);
              if( pGrpComments != NULL )
              {
                MAP_dfndom(pStyDoc->pGrpCom,GLS_Tok_symbol(pIde),pGrpComments);
                pGrpComments = NULL;
              }
              lDRow = lRow;
            }
          }
          else
          if( styx_Dfn(t,_) )
          {
            styxDfn_defn((styxDfn)t,_,_,&pIde,_);
            if( !MAP_defined(pStyDoc->pDfnCom,GLS_Tok_symbol(pIde)) )
            {
              pComments = OT_CREATE_ADT(PT_Term);
              MAP_dfndom(pStyDoc->pDfnCom,GLS_Tok_symbol(pIde),pComments);
              if( pGrpComments != NULL )
              {
                MAP_dfndom(pStyDoc->pGrpCom,GLS_Tok_symbol(pIde),pGrpComments);
                pGrpComments = NULL;
              }
              lDRow = lRow;
            }
          }
          else
          if( styx_Prd(t,_) )
          {
            styxPrd_prod((styxPrd)t,_,&pIde,_);
            OT_PUSH(pIde,pComments);
            if( pGrpComments != NULL )
            {
              OT_APPEND(pComments,pGrpComments);
              OT_DEL_T(pGrpComments);
              pGrpComments = NULL;
            }
            lDRow = lRow;
          }
        }
      }
    } 
  }
  if( pGrpComments != NULL )
    MAP_dfndom(pStyDoc->pGrpCom,NULL,pGrpComments);
}

static void SD_load_lex(GLS_Lst(styxQlxDfn) pQDfns, StyDoc_T pStyDoc)
/* load documentation base for lexical analysis */
{ GLS_Lst(styxQlxDfn) pItr;
  GLS_Tok             pIde, pLan;
  styxQlxGrp          pQGrp; 
  styxQlxDfn          pQDfn; 
  styxQlxCat          pQCat;
  styxExp             pQExp;
  symbol              pTSym;
  c_string            szETok;
  GLS_FORALL(pItr,pQDfns) // token map
  { 
    pQDfn = GLS_FIRST(styxQlxDfn,pItr);
    if( styxQlxDfn_defn(pQDfn,&pQCat,_,&pQGrp,&pIde,_,_) )
    {
      if( styxQlxCat_lanC(pQCat) )
      {
        assert0(styxQlxGrp_grp(pQGrp,&pLan),"");
        HS_SET_ELM(GLS_Tok_symbol(pLan),pStyDoc->pLSet);
        szETok = Str_printf("%s%s",GLS_Tok_string(pLan),GLS_Tok_string(pIde));
        pTSym = stringToSymbol(szETok);
        FreeMem(szETok);
      }
      else pTSym = GLS_Tok_symbol(pIde);
      if( ! MAP_defined(pStyDoc->pTMap,pTSym) )
        MAP_dfndom(pStyDoc->pTMap,pTSym,pQDfn);
    }
    else
    if( styxQlxDfn_igrp(pQDfn,&pIde) || styxQlxDfn_xgrp(pQDfn,&pIde) ||
        styxQlxDfn_mgrp(pQDfn,&pIde,_) )
    {
      if( ! MAP_defined(pStyDoc->pGMap,GLS_Tok_symbol(pIde)) )
        MAP_dfndom(pStyDoc->pGMap,GLS_Tok_symbol(pIde),pQDfn);
    }
  }
  GLS_FORALL(pItr,pQDfns) // token document base
  { ROW(ROW(symbol)) pTLines;
    ROW(symbol)      pTLine;
    SET(styxExp)     pSubExps;
    pQDfn = GLS_FIRST(styxQlxDfn,pItr);
    if( styxQlxDfn_defn(pQDfn,&pQCat,_,&pQGrp,&pIde,_,&pQExp) )
    {
      pTLines = OT_CREATE(ROW(symbol),primCopy,OT_delT,primEqual);
      pTLine  = OT_CREATE_ADT(symbol);
      if( !styxQlxCat_lanC(pQCat) )
        pTSym = GLS_Tok_symbol(pIde);
      else
      {
        assert0(styxQlxGrp_grp(pQGrp,&pLan),"");
        szETok = Str_printf("%s%s",GLS_Tok_string(pLan),GLS_Tok_string(pIde));
        pTSym = stringToSymbol(szETok);
        FreeMem(szETok);
      }
      OT_PUSH(pTSym,pStyDoc->pDocBase);
      OT_PUSH(pTLines,pStyDoc->pDocBase);
      OT_PUSH(pTLine,pTLines);
      if( !styxQlxCat_lanC(pQCat) )
      {
        pSubExps = HS_CREATE_ADTSET(styxExp);
        SD_collectSubExps(pQExp,pSubExps);
        SD_evalQExp(pQExp,pTLine,pSubExps);
        HS_DROP_SET(pSubExps);
      }
      else
      {
        OT_PUSH(GLS_Tok_symbol(pLan),pTLine);
      }
    }
  }
}

// Meta-Symbols in Productions are enclosed with ".

/**/static long SD_load_ntgroup
                (
                  long lNTIdx, MAP(long,ROW(ROW(symbol))) pEBNF, 
                  StyDoc_T pStyDoc
                );

static c_bool SD_splitClass(StyDoc_T pStyDoc, long lClsIdx)
/* create separate rules for each nonterminal */
{ symbol pClsSym = stringToSymbol(PLR_symName
                   (
                     pStyDoc->pTab, PLR_tokenCnt(pStyDoc->pTab) + lClsIdx
                   ));
  return HS_MBR_ELM(pClsSym,pClsToSplit);
}

static ROW(symbol) SD_load_ntprod
                   (
                     long lNTIdx, long lPrdIdx, long lDocIdx, c_bool bNTList,
                     MAP(long,ROW(ROW(symbol))) pEBNF, StyDoc_T pStyDoc
                   )
/* load documentation base for a production of nonterminal 'lNTIdx' */
{ long             lMbrCnt, lSym, lSymIdx, lClsIdx, lTyp, 
                   lSubSym, lClsSym, lSubIdx, lI, lJ;
  ROW(ROW(symbol)) pNTLines = MAP_apply(ROW(ROW(symbol)),pEBNF,lDocIdx),
                              pMbrLines;
  ROW(symbol)      pNTLine  = OT_CREATE_ADT(symbol), pMbrLine;
  c_string         szSym, szClsSym;
  symbol           pSym, pClsSym;
  c_bool           bOptNT;
  lMbrCnt = PLR_prodSymCnt(pStyDoc->pTab,lPrdIdx);
  for( lI=0; lI < lMbrCnt; ++lI )
  {
    lSym = PLR_prodSymbol(pStyDoc->pTab,lPrdIdx,lI); 
    lTyp = PLR_symType(pStyDoc->pTab,lSym);
    if( CFG_NTM(lTyp) )
    {
      lSymIdx   = lSym-PLR_tokenCnt(pStyDoc->pTab);
      lClsIdx   = PLR_ntClassId(pStyDoc->pTab,lSymIdx);
      lSubIdx   = SD_load_ntgroup(lSymIdx,pEBNF,pStyDoc);
      lSubSym   = lSubIdx + PLR_tokenCnt(pStyDoc->pTab);
      lClsSym   = lClsIdx + PLR_tokenCnt(pStyDoc->pTab);
      szSym     = PLR_symName(pStyDoc->pTab,lSubSym);
      szClsSym  = SD_splitClass(pStyDoc,lClsIdx)
                  ? szSym : PLR_symName(pStyDoc->pTab,lClsSym);
      pSym      = stringToSymbol(szSym);
      pClsSym   = stringToSymbol(szClsSym);
      pMbrLines = MAP_apply(ROW(ROW(symbol)),pEBNF,lSubIdx);
      bOptNT    =   ACFG_HAS_NTTYP(pStyDoc->aPol[lSubIdx],ACFG_NTTYP_OPT) &&
                  ! ACFG_HAS_NTTYP(pStyDoc->aPol[lSubIdx],ACFG_NTTYP_RECTYP);
      if( HS_MBR_ELM(pSym,pNTsToKeep) ||
          ( ( MAP_defined(pStyDoc->pNTMap,pSym) ||
              SD_IsNTRecRef(lSymIdx, pStyDoc)   ||
              ! ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_LIST) ) &&
            ( ACFG_HAS_NTTYP(pStyDoc->aPol[lSubIdx],ACFG_NTTYP_RECTYP) ||
              ( OT_CNT(pMbrLines) > 1 &&
                ! ( ACFG_HAS_NTTYP(pStyDoc->aPol[lSymIdx],ACFG_NTTYP_REF1) &&
                    ignProd(PLR_prodName(pStyDoc->pTab,lPrdIdx)) && 
                    lMbrCnt == 1 ) ) ) ) )
/*HM 26.1.2005
      if( ( MAP_defined(pStyDoc->pNTMap,pSym) ||
            HS_MBR_ELM(pSym,pNTsToKeep)       ||
            SD_IsNTRecRef(lSymIdx, pStyDoc)   ||
            ! ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_LIST) ) &&
          ( ACFG_HAS_NTTYP(pStyDoc->aPol[lSubIdx],ACFG_NTTYP_RECTYP) ||
            ( OT_CNT(pMbrLines) > 1 &&
              ! ( ACFG_HAS_NTTYP(pStyDoc->aPol[lSymIdx],ACFG_NTTYP_REF1) &&
                  ignProd(PLR_prodName(pStyDoc->pTab,lPrdIdx)) && 
                  lMbrCnt == 1 ) ) ) )
*/
      {
        if( ! MAP_defined(pStyDoc->pNTMap,pSym) )
        {
          if( pSym != pClsSym &&
              !MAP_defined(pStyDoc->pNTMap,pClsSym) )
            MAP_dfndom(pStyDoc->pClsMap,pSym,pClsSym);
          MAP_dfndom(pStyDoc->pNTMap,pSym,lSubIdx);
          OT_PUSH(pSym,pStyDoc->pDocBase);
          OT_PUSH(pMbrLines,pStyDoc->pDocBase);
        }
        SD_symbolToNTSeq(bOptNT,"[]",pNTLine,pSym);
      }
      else
      if( OT_CNT(pMbrLines) > 0 )
      {
        if( ! bNTList ) 
        {
          if( OT_CNT(pMbrLines) == 1 )
          {
            pMbrLine = OT_GET(ROW(symbol),pMbrLines,0);
            if( ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_LIST) )
              SD_rowToNTSeq
              (
                lMbrCnt > 1 && SD_IsNTUnion(pMbrLine) && 
                !SD_IsNTSequence(pMbrLine),
                "()", pNTLine,pMbrLine
              );
            else SD_rowToNTSeq(bOptNT,"[]",pNTLine,pMbrLine);
          }
          else
          {
            assert0( pMbrLines != pNTLines,szSym );
            for( lJ=0; lJ < OT_CNT(pMbrLines); ++lJ )
            {
              pMbrLine = OT_GET(ROW(symbol),pMbrLines,lJ);
              OT_PUSH(OT_COPY(pMbrLine),pNTLines);
            }
          }
        }
        else // in this case only one line is possible !!!
        if( lNTIdx != lSymIdx ) // CONSREF 
        {
          pMbrLine = OT_GET(ROW(symbol),pMbrLines,0);
          if( PLR_ntClassId(pStyDoc->pTab,lNTIdx) != lClsIdx         &&
              ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_LIST)  )
            SD_rowToNTSeq
            (
              SD_IsNTUnion(pMbrLine) && !SD_IsNTSequence(pMbrLine),
              "()", pNTLine,pMbrLine
            );
          else SD_rowToNTSeq(bOptNT,"[]",pNTLine,pMbrLine);
        }
      }
    }
    else
    {
      szSym = PLR_symName(pStyDoc->pTab,lSym);
      OT_PUSH(stringToSymbol(szSym),pNTLine);
    }
  }
  return pNTLine;
}

static void SD_cons_ntprod
            (
              long lDocIdx, MAP(long,ROW(ROW(symbol))) pEBNF, StyDoc_T pStyDoc
            )
/* concat simple nonterminal/class productions */ 
{ 
  ROW(ROW(symbol)) pNTLines = MAP_apply(ROW(ROW(symbol)),pEBNF,lDocIdx);
  ROW(symbol)      pNTLine;
  long             lClsIdx  = PLR_ntClassId(pStyDoc->pTab,lDocIdx), lCnt, lI;
  c_bool           bSimple;
  bSimple = ! ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_LIST) &&
            ( ACFG_HAS_NTTYP(pStyDoc->aPol[lDocIdx],ACFG_NTTYP_PRIM) ||
              ACFG_HAS_NTTYP(pStyDoc->aPol[lDocIdx],ACFG_NTTYP_PRIMC) );
  lCnt = OT_CNT(pNTLines);
  if( lCnt > 1 && bSimple )
  { 
    pNTLine = OT_GET(ROW(symbol),pNTLines,0);
    if( OT_CNT(pNTLine) > 0 )
    {
      for( lI=1; lI < lCnt; ++lI )
      {
        OT_PUSH(stringToSymbol("\"|\""),pNTLine);
        OT_APPEND(pNTLine,OT_GET(ROW(symbol),pNTLines,lI));
      }
      OT_DEL_ES(pNTLines,1,lCnt-1);
    }
  }
}

static void SD_load_nt
            (
              long lNTIdx, c_bool bNTClass,
              MAP(long,ROW(ROW(symbol))) pEBNF, StyDoc_T pStyDoc
            )
/* load documentation base for a nonterminal/class */
{ long             lClsIdx  = PLR_ntClassId(pStyDoc->pTab,lNTIdx), 
                   lDocIdx  = bNTClass ? lClsIdx : lNTIdx,
                   lPrdIdx;
  ROW(ROW(symbol)) pNTLines = MAP_apply(ROW(ROW(symbol)),pEBNF,lDocIdx);
  ROW(symbol)      pNTLine;
  HS_Itr           pItr;
  symbol           pNTSym   = stringToSymbol(PLR_symName
                              (
                                pStyDoc->pTab, 
                                PLR_tokenCnt(pStyDoc->pTab) + lNTIdx
                              )), pProdSym;
  c_bool           bExcluded;
  HS_FORALL(lPrdIdx,pItr,pStyDoc->aPrd[lNTIdx])
  { 
    pProdSym  = stringToSymbol(PLR_prodName(pStyDoc->pTab,lPrdIdx));
    bExcluded = MAP_defined(pExcludedProds,pNTSym) &&
                HS_MBR_ELM
                (
                  pProdSym,MAP_apply(SET(symbol),pExcludedProds,pNTSym)
                );
    if( ! bExcluded &&
        ( ! bNTClass                                    || 
          !ignProd(PLR_prodName(pStyDoc->pTab,lPrdIdx)) || 
          PLR_prodSymCnt(pStyDoc->pTab,lPrdIdx) > 1      ) )
    {
      pNTLine = SD_load_ntprod(lNTIdx,lPrdIdx,lDocIdx,C_False,pEBNF,pStyDoc);
      if( OT_CNT(pNTLine) > 0 )
        OT_PUSH(pNTLine,pNTLines);
      else OT_DEL_T(pNTLine);
    }
  }
}

static c_bool SD_add_listprod
              (
                long lNTIdx, long lPrdIdx, 
                c_bool bNTNil, ROW(symbol) pListLine,
                MAP(long,ROW(ROW(symbol))) pEBNF, StyDoc_T pStyDoc
              )
/* appends list production to 'pListLine' if not empty. RC = opt. list */
{ ROW(symbol) pNTLine = SD_load_ntprod
                        (
                          lNTIdx,lPrdIdx,lNTIdx,C_True,pEBNF,pStyDoc
                        );
  c_bool      bEmpty  = ( OT_CNT(pNTLine) == 0 );
  if( ! bEmpty )
  {
    bEmpty = bNTNil;
    if( OT_CNT(pListLine) > 0 ) OT_PUSH(stringToSymbol("\"|\""),pListLine);
    OT_APPEND(pListLine,pNTLine);
  }
  OT_DEL_T(pNTLine);
  return bEmpty;
}

static c_bool SD_add_consprod
              (
                long lNTIdx, long lPrdIdx, 
                c_bool bNTNil, ROW(symbol)* pListLine,
                MAP(long,ROW(ROW(symbol))) pEBNF, StyDoc_T pStyDoc
              )
/* appends cons production to 'pListLine' if not empty. RC = opt. list */
{ ROW(symbol) pNTLine = SD_load_ntprod
                        (
                          lNTIdx,lPrdIdx,lNTIdx,C_True,pEBNF,pStyDoc
                        ),
              pTmpLine;
  c_bool      bEmpty  = ( OT_CNT(pNTLine) == 0 );
  if( ! bEmpty )
  { 
    bEmpty   = ( bNTNil && OT_CNT(*pListLine) > 0 );
    pTmpLine = OT_CREATE_ADT(symbol);
    SD_rowToNTSeq
    (
      bNTNil || !SD_IsNTSequence(pNTLine), bNTNil?"{}":"()", pTmpLine,pNTLine
    );
    if( ! bNTNil ) OT_PUSH(stringToSymbol("\"+\""),pTmpLine);
    pTmpLine = 
      SD_rowToNTSeq(!bNTNil && OT_CNT(*pListLine) > 0,"[]",pTmpLine,pTmpLine);
    if( SD_IsLLProd(lPrdIdx,pStyDoc) )
    {
      OT_APPEND(*pListLine,pTmpLine); OT_DEL_T(pTmpLine);
    }
    else
    {
      OT_APPEND(pTmpLine,*pListLine); OT_DEL_T(*pListLine);
      *pListLine = pTmpLine;
    }
  }
  OT_DEL_T(pNTLine);
  return bEmpty;
}

static void SD_load_ntlist
            (
              long lNTIdx, MAP(long,ROW(ROW(symbol))) pEBNF, StyDoc_T pStyDoc
            )
/* load documentation base for a nonterminal list */
{ long        lConsIdx  = -1, lMbrCnt, lPrdIdx, lIgnNTIdx;
  c_bool      bNTNil    = ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_NIL),
              bConsRef  = 
                  ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_CONSREF) &&
                ! SD_IsNTRecRef(lNTIdx, pStyDoc);
  ROW(symbol) pListLine = OT_CREATE_ADT(symbol);
  HS_Itr      pItr;
  HS_FORALL(lPrdIdx,pItr,pStyDoc->aPrd[lNTIdx])
  {
    lMbrCnt = PLR_prodSymCnt(pStyDoc->pTab,lPrdIdx);
    if( nilProd(PLR_prodName(pStyDoc->pTab,lPrdIdx)) && lMbrCnt > 0 ) 
      bNTNil = SD_add_listprod(lNTIdx,lPrdIdx,bNTNil,pListLine,pEBNF,pStyDoc);
    else
    if( ignProd(PLR_prodName(pStyDoc->pTab,lPrdIdx)) ) 
    {
      lIgnNTIdx = SD_getIgnNTIdx(lPrdIdx,pStyDoc);
      if( lMbrCnt > 1 || 
          ( ! ACFG_HAS_NTTYP(pStyDoc->aPol[lIgnNTIdx],ACFG_NTTYP_EMPTY) && 
            lIgnNTIdx != lNTIdx ) )
        bNTNil = SD_add_listprod(lNTIdx,lPrdIdx,bNTNil,pListLine,pEBNF,pStyDoc);
      else
        bNTNil |= ACFG_HAS_NTTYP(pStyDoc->aPol[lIgnNTIdx],ACFG_NTTYP_EMPTY);
    }
    else
    if( consProd(PLR_prodName(pStyDoc->pTab,lPrdIdx)) ) 
    {
      if( bConsRef ) lConsIdx = lPrdIdx;
      else
        bNTNil = SD_add_listprod(lNTIdx,lPrdIdx,bNTNil,pListLine,pEBNF,pStyDoc);
    }
  }
  if( lConsIdx >= 0 )
    bNTNil = SD_add_consprod(lNTIdx,lConsIdx,bNTNil,&pListLine,pEBNF,pStyDoc);
  pListLine = 
    SD_rowToNTSeq(bNTNil && OT_CNT(pListLine) > 0,"[]",pListLine,pListLine);
  if( OT_CNT(pListLine) > 0 )
  { ROW(ROW(symbol)) pNTLines = MAP_apply(ROW(ROW(symbol)),pEBNF,lNTIdx);
    OT_PUSH(pListLine,pNTLines);
  }
  else OT_DEL_T(pListLine);
}

static long SD_load_ntgroup
            (
              long lNTIdx, MAP(long,ROW(ROW(symbol))) pEBNF, StyDoc_T pStyDoc
            )
/* load documentation base for a nonterminal/class/list */
{ long   lClsIdx  = PLR_ntClassId(pStyDoc->pTab,lNTIdx), lDocIdx;
  c_bool bNTList  = ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_LIST),
         bNTClass = !bNTList && 
                    ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_CLASS) &&
                    ! SD_splitClass(pStyDoc,lClsIdx);
  lDocIdx = bNTClass ? lClsIdx : lNTIdx;
  if( ! MAP_defined(pEBNF,lDocIdx) )
  { ROW(ROW(symbol)) pNTLines = OT_CREATE
                                (
                                  ROW(symbol),primCopy,OT_delT,primEqual
                                );
    symbol           pNTSym   = stringToSymbol(PLR_symName
                                (
                                  pStyDoc->pTab, 
                                  PLR_tokenCnt(pStyDoc->pTab) + lDocIdx
                                )),
                     pClsSym  = SD_splitClass(pStyDoc,lClsIdx)
                                ? pNTSym
                                : stringToSymbol(PLR_symName
                                  (
                                    pStyDoc->pTab, 
                                    PLR_tokenCnt(pStyDoc->pTab) + lClsIdx
                                  ));
    HS_Itr           pItr;
    MAP_dfndom(pEBNF,lDocIdx,pNTLines);
    if( ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_START) &&
        ! MAP_defined(pStyDoc->pNTMap,pNTSym)                   )  
    {
      if( pNTSym != pClsSym &&
          !MAP_defined(pStyDoc->pNTMap,pClsSym) )
        MAP_dfndom(pStyDoc->pClsMap,pNTSym,pClsSym);
      MAP_dfndom(pStyDoc->pNTMap,pNTSym,lDocIdx);
      OT_PUSH(pNTSym,pStyDoc->pDocBase);
      OT_PUSH(pNTLines,pStyDoc->pDocBase);
    }
    if( bNTClass )
    {
      if( ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_RECTYP) &&
          ACFG_HAS_NTTYP(pStyDoc->aPol[lClsIdx],ACFG_NTTYP_OPT)     )
        OT_PUSH(OT_CREATE_ADT(symbol),pNTLines);
      HS_FORALL(lNTIdx,pItr,pStyDoc->aNtm[lClsIdx])
        if( HS_CARD(pStyDoc->aPrd[lNTIdx]) > 1 ||
            ! ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_EMPTY) )
        {
          SD_load_nt(lNTIdx,bNTClass,pEBNF,pStyDoc);
        }
    }
    else
    {
      if( HS_CARD(pStyDoc->aPrd[lNTIdx]) > 1 ||
          ! ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_EMPTY) )
      {
        if( bNTList ) SD_load_ntlist(lNTIdx,pEBNF,pStyDoc);
        else
        {
          if( ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_RECTYP) &&
              ACFG_HAS_NTTYP(pStyDoc->aPol[lNTIdx],ACFG_NTTYP_OPT)     )
            OT_PUSH(OT_CREATE_ADT(symbol),pNTLines);
          SD_load_nt(lNTIdx,bNTClass,pEBNF,pStyDoc);
        }
      }
    }
  }
  return lDocIdx;
}

static void SD_load_cfg(StyDoc_T pStyDoc)
/* load documentation base for context free grammar */
{ MAP(long,ROW(ROW(symbol))) pEBNF;
  ROW(ROW(symbol))           pNTLines;
  MAPIT                      pItr;
  long                       lCnt = PLR_startCnt(pStyDoc->pTab), 
                             lDocIdx, lI;
  symbol                     pNTSym;
  pEBNF = MAP_newPrimMap();
  for( lI=0; lI < lCnt; ++lI )
  {
    lDocIdx = SD_load_ntgroup
              (
                PLR_startSymbol(pStyDoc->pTab,lI)-PLR_tokenCnt(pStyDoc->pTab),
                pEBNF,pStyDoc
              );
  }
  MAP_forItrAsg(pNTSym,lDocIdx,pItr,pStyDoc->pNTMap)
  {
    SD_cons_ntprod(lDocIdx,pEBNF,pStyDoc);
    MAP_rmvdom(pEBNF,lDocIdx);
  }
  MAP_forItrAsg(lDocIdx,pNTLines,pItr,pEBNF)
    if( pNTLines != (ROW(ROW(symbol)))NULL ) OT_DEL_T(pNTLines);
  MAP_freeMap(pEBNF);
}

static void SD_load_cnt
            (
              long lNTIdx,
              MAP(long,ROW(ROW(symbol))) pEBNF, StyDoc_T pStyDoc
            )
/* load documentation base for a nonterminal */
{ long             lPrdIdx, lSymCnt, lSym, lI;
  ROW(ROW(symbol)) pNTLines = MAP_apply(ROW(ROW(symbol)),pEBNF,lNTIdx);
  ROW(symbol)      pNTLine;
  HS_Itr           pItr;
  symbol           pNTSym   = stringToSymbol(PLR_symName
                              (
                                pStyDoc->pTab, 
                                PLR_tokenCnt(pStyDoc->pTab) + lNTIdx
                              )), pProdSym;
  c_bool           bExcluded;
  HS_FORALL(lPrdIdx,pItr,pStyDoc->aPrd[lNTIdx])
  { 
    pProdSym  = stringToSymbol(PLR_prodName(pStyDoc->pTab,lPrdIdx));
    bExcluded = MAP_defined(pExcludedProds,pNTSym) &&
                HS_MBR_ELM
                (
                  pProdSym,MAP_apply(SET(symbol),pExcludedProds,pNTSym)
                );
    if( ! bExcluded )
    {
      pNTLine = OT_CREATE_ADT(symbol);
      OT_PUSH(pNTLine,pNTLines);
      lSymCnt = PLR_prodSymCnt(pStyDoc->pTab,lPrdIdx);
      for( lI=0; lI < lSymCnt; ++lI )
      { c_string szSym;
        lSym = PLR_prodSymbol(pStyDoc->pTab,lPrdIdx,lI); 
        szSym = PLR_symName(pStyDoc->pTab,lSym);
        OT_PUSH(stringToSymbol(szSym),pNTLine);
      }
    }
  }
}

static void SD_load_ccfg(StyDoc_T pStyDoc)
/* load documentation base for the concrete context free grammar */
{ MAP(long,ROW(ROW(symbol))) pEBNF;
  ROW(ROW(symbol))           pNTLines;
  MAPIT                      pItr;
  long                       lCnt = PLR_startCnt(pStyDoc->pTab), 
                             lDocIdx, lI;
  symbol                     pNTSym;
  pEBNF = MAP_newPrimMap();
  for( lI=0; lI < lCnt; ++lI )
  {
    lDocIdx = PLR_startSymbol(pStyDoc->pTab,lI)-PLR_tokenCnt(pStyDoc->pTab);
    pNTSym  = stringToSymbol
              (
                PLR_symName(pStyDoc->pTab,PLR_tokenCnt(pStyDoc->pTab)+lDocIdx)
              );
    MAP_dfndom(pStyDoc->pNTMap,pNTSym,lDocIdx);
    pNTLines = OT_CREATE(ROW(symbol),primCopy,OT_delT,primEqual);
    MAP_dfndom(pEBNF,lDocIdx,pNTLines);
    OT_PUSH(pNTSym,pStyDoc->pDocBase);
    OT_PUSH(pNTLines,pStyDoc->pDocBase);
    SD_load_cnt(lDocIdx,pEBNF,pStyDoc);
  }
  lCnt = PLR_nontermCnt(pStyDoc->pTab);
  for( lI=0; lI < lCnt; ++lI )
  {
    if( !MAP_defined(pEBNF,lI) )
    {
      pNTSym  = stringToSymbol
                (
                  PLR_symName(pStyDoc->pTab,PLR_tokenCnt(pStyDoc->pTab)+lI)
                );
      MAP_dfndom(pStyDoc->pNTMap,pNTSym,lI);
      pNTLines = OT_CREATE(ROW(symbol),primCopy,OT_delT,primEqual);
      MAP_dfndom(pEBNF,lI,pNTLines);
      OT_PUSH(pNTSym,pStyDoc->pDocBase);
      OT_PUSH(pNTLines,pStyDoc->pDocBase);
      SD_load_cnt(lI,pEBNF,pStyDoc);
    }
  }
  MAP_forItrAsg(pNTSym,lDocIdx,pItr,pStyDoc->pNTMap)
  {
    MAP_rmvdom(pEBNF,lDocIdx);
  }
  MAP_forItrAsg(lDocIdx,pNTLines,pItr,pEBNF)
    if( pNTLines != (ROW(ROW(symbol)))NULL ) OT_DEL_T(pNTLines);
  MAP_freeMap(pEBNF);
}

static c_bool SD_load_pat(StyDoc_T pStyDoc)
/* load template */
{ 
  if( strlen(template) > 0 )
  { Scn_Stream pStream;
    pStyDoc->pHPat = HP_create();
    HP_setContext(pStyDoc->pHPat,pStyDoc);
    HP_setPrintFun(pStyDoc->pHPat,SD_gendoc_txt);
    if( strlen(refalias) > 0 )
      HP_setRefAlias(pStyDoc->pHPat,stringToSymbol(refalias));
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_CFGDFN,SD_gendoc_cfg,HPAT_REF_PAT);
    //HP_addPatSpec(pStyDoc->pHPat,SD_PAT_COMSEC,SD_gendoc_csec,HPAT_REF_PAT);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_TKMSEC,SD_gendoc_tsec,HPAT_REF_LIST);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_NTMSEC,SD_gendoc_nsec,HPAT_REF_LIST);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_MBRSEC,SD_gendoc_msec,HPAT_REF_LIST);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_PRDSEC,SD_gendoc_psec,HPAT_REF_LIST);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_CFGID,SD_gendoc_cid,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_DFNID,SD_gendoc_did,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_DFNREF,SD_gendoc_dref,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_LANREF,SD_gendoc_lref,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_DFNCAT,SD_gendoc_dcat,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_DFNOPT,SD_gendoc_dopt,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_MBRID,SD_gendoc_mid,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_DFNCOM,SD_gendoc_dcom,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_GRPCOM,SD_gendoc_gcom,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_BOTCOM,SD_gendoc_bcom,HPAT_REF_PAR);
    HP_addPatSpec(pStyDoc->pHPat,SD_PAT_OPTCOM,SD_gendoc_ocom,HPAT_REF_PAR);
    pStream = Stream_file(HP_getScanner(pStyDoc->pHPat),"",template,"");
    return HP_load(pStyDoc->pHPat,pStream,NULL,SD_PAT_CFGDFN,recursiv) &&
           HP_check(pStyDoc->pHPat);
  }
  else return C_True;
}

static c_bool SD_load(StyDoc_T* ppStyDoc)
/* load documentation base */
{ PLR_Tab          pTab; 
  Scn_T            pScn; 
  Scn_Stream       pStream; 
  PT_Cfg           pCfg; 
  StyDoc_T         pStyDoc;
  MAP(long,symbol) pPreParMap; 
  SPP_T            pPP;
  // init database
  pStyDoc = *ppStyDoc = SD_init_base();
  // parse language definition
  pPreParMap = MAP_newPrimMap();
  MAP_dfndom(pPreParMap,SPP_INC_PATH,stringToSymbol(styxpath));
  pPP = SPP_init_reentrant(pPreParMap);
  Scn_get_styx(&pScn);
  pStream        = Stream_file(pScn,"",infile,"");
  Stream_premac_set(pStream, SPP_premac);
  Stream_add_ctxval(pStream,stringToSymbol("SPP_premac"),pPP);
  pTab           = PLR_get_styx();
  pCfg           = PT_init(pTab,pStream);
  pStyDoc->pTree = PT_PARSE(pCfg,"");
  PT_setErrorCnt(PT_synErrorCnt(pCfg));
  PT_quit(pCfg);
  Stream_close(pStream);
  Stream_free(pStream);
  Scn_free(pScn);
  PLR_delTab(pTab);
  SPP_quit_reentrant(pPP);
  MAP_freeMap(pPreParMap);
  if( PT_errorCnt() == 0 )
  { styxSource          pSrc;
    GLS_Lst(styxQlxDfn) pQDfns;
    GLS_Lst(styxDfn)    pDfns;
    styxOptCfg          pOptCfg;
    GLS_Tok             pIde;
    // fill documentation base
    styx_Start_Source(pStyDoc->pTree,&pSrc);
    styxSource_root(pSrc,&pIde,&pQDfns,&pOptCfg);
    SD_load_com(pStyDoc);
    SD_load_lex(pQDfns,pStyDoc);
    if( styxOptCfg_cfg(pOptCfg,&pDfns) && ! GLS_EMPTY(pDfns) )
    {
      pStyDoc->pTab = PLR_getTab_env(binpath,GLS_Tok_string(pIde));
      if( pStyDoc->pTab != (PLR_Tab)NULL &&
          acfg_init_doc(pStyDoc->pTab,
                        &pStyDoc->aPol,&pStyDoc->aNtm,&pStyDoc->aPrd) )
      {
        if( bConcreteCfg )
          SD_load_ccfg(pStyDoc);
        else
          SD_load_cfg(pStyDoc);
        return SD_load_pat(pStyDoc);
      }
    }
    else 
      return SD_load_pat(pStyDoc);
  }
  return C_False;
}

static void SD_unload(StyDoc_T pStyDoc)
/* unload documentation base */
{ long lCnt = OT_CNT(pStyDoc->pDocBase)/2, lDom, lI;
  MAPIT pItr; ROW(PT_Term) pRng;
  if( pStyDoc->pTree != (PT_Term)NULL ) 
    PT_delT(pStyDoc->pTree);
  if( pStyDoc->pTab  != (PLR_Tab)NULL ) 
  {
    acfg_quit(pStyDoc->pTab,pStyDoc->aPol,pStyDoc->aNtm,pStyDoc->aPrd);
    PLR_delTab(pStyDoc->pTab);
  }
  MAP_forItrAsg(lDom,pRng,pItr,pStyDoc->pDfnCom)
    OT_DEL_T(pRng);
  MAP_freeMap(pStyDoc->pDfnCom);
  MAP_forItrAsg(lDom,pRng,pItr,pStyDoc->pGrpCom)
    OT_DEL_T(pRng);
  MAP_freeMap(pStyDoc->pGrpCom);
  MAP_freeMap(pStyDoc->pGMap);
  MAP_freeMap(pStyDoc->pTMap);
  MAP_freeMap(pStyDoc->pNTMap);
  MAP_freeMap(pStyDoc->pClsMap);
  HS_DROP_SET(pStyDoc->pLSet);
  for( lI=0; lI < lCnt; ++lI )
    OT_DEL_T(OT_GET(ROW(_),pStyDoc->pDocBase,2*lI+1));
  OT_DEL_T(pStyDoc->pDocBase);
  if( pStyDoc->pHPat != (HPat_T)NULL )
    HP_drop(pStyDoc->pHPat);
  FreeMem(pStyDoc);
}

/* ------------------------- Main ----------------------------------------- */

int main(int argc, c_string argv[])
{ StyDoc_T pStyDoc;
  SD_init(argc,argv);
  if( SD_load(&pStyDoc) )
  { 
    // generate language documentation 
    if( strlen(outfile) > 0 )
      pStyDoc->pSysOut = OpnFile(outfile,"wt");
    else 
      pStyDoc->pSysOut = stdout;
    if( pStyDoc->pHPat != (HPat_T)NULL )
      SD_gendoc_cfg(pStyDoc->pHPat);
    else SD_gendoc_raw(pStyDoc);
    fclose(pStyDoc->pSysOut);
  }
  SD_unload(pStyDoc);
  SD_quit();
  BUG_CORE;
  return(0);
}
