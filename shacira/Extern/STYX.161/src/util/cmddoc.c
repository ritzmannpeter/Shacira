/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [cmddoc.c]                   CMD Documentation Generator                 */
/*                                                                          */
/* Copyright (c) 1999 by D\olle, Manns, Steffen                             */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"
#include "symbols.h"
#include "hmap.h"
#include "hset.h"
#include "ptm.h"
#include "gls.h"
#include "sink.h"
#include "pathes.h"
#include "cmdlib.h"
#include "cmdd_cim.h"
#include "cmd_int.h"
#include "hpat.h"


#define infile     CTX_EVAL(c_string,"InFile")
#define outfile    CTX_EVAL(c_string,"OutFile")
#define template   CTX_EVAL(c_string,"Template")
#define refalias   CTX_EVAL(c_string,"RefAlias")
#define recursiv   CTX_EVAL(c_bool,"recursiv")


/* CMD Documentation Pattern */
#define CD_PAT_PGMDFN     stringToSymbol("pgmdfn")
#define CD_PAT_ARGSEC     stringToSymbol("argsec")
#define CD_PAT_OPTSEC     stringToSymbol("optsec")
#define CD_PAT_ENVSEC     stringToSymbol("envsec")
#define CD_PAT_PGMID      stringToSymbol("pgmid")
#define CD_PAT_PARID      stringToSymbol("parid")
#define CD_PAT_PARTYP     stringToSymbol("partyp")
#define CD_PAT_PARVAL     stringToSymbol("parval")
#define CD_PAT_DOLTXT     stringToSymbol("doltxt")
#define CD_PAT_DOCTXT     stringToSymbol("doctxt")

#define CD_CTXIDX_TSRC    0
#define CD_CTXIDX_HPAT    1
#define CD_CTXIDX_FILE    2
#define CD_CTXIDX_TDOC    3
#define CD_CTXIDX_TSEC    4


static void CD_gendoc_raw(ROW(_) pCmdCtx)
/* generate raw documentation - without template */
{
}

static void CD_gendoc_txt(HPat_T pHPat, c_string szTxt)
/* generate documentation according template */
{ ROW(_) pCmdCtx = (ROW(_))HP_getContext(pHPat);
  FILE*  pSysOut = OT_GET(FILE*,pCmdCtx,CD_CTXIDX_FILE);
  fprintf(pSysOut,"%s",szTxt);
}

static c_bool CD_gendoc_pgmdfn(HPat_T pHPat)
/* generate documentation according template */
{
  HP_gendoc_pat(pHPat,CD_PAT_PGMDFN);
  return C_True;
}

static c_bool CD_gendoc_pgmid(HPat_T pHPat)
/* generate program identifier according template */
{ ROW(_)           pCmdCtx = (ROW(_))HP_getContext(pHPat);
  FILE*            pSysOut = OT_GET(FILE*,pCmdCtx,CD_CTXIDX_FILE);
  cmdSource        pSrc    = OT_GET(cmdSource,pCmdCtx,CD_CTXIDX_TSRC);
  GLS_Lst(GLS_Tok) pLst;
  c_string         szIde, szS;
  assert0(cmdSource_root(pSrc,&pLst,_,_,_,_,_,_,_,_),"");
  szIde = CMD_FidString(pLst);
  if( HP_fun_defined(pHPat,CD_PAT_PGMID) )
    szS = HP_fun_apply(pHPat,CD_PAT_PGMID,szIde);
  else szS = szIde;
  fprintf(pSysOut,"%s",szS);
  if( szS != szIde ) FreeMem(szS);
  FreeMem(szIde);
  return C_True;
}

static c_bool CD_gendoc_parid(HPat_T pHPat)
/* generate parameter identifier according template */
{ ROW(_)          pCmdCtx = (ROW(_))HP_getContext(pHPat);
  FILE*           pSysOut = OT_GET(FILE*,pCmdCtx,CD_CTXIDX_FILE);
  GLS_Lst(cmdDfn) pLst    = OT_GET(GLS_Lst(cmdDfn),pCmdCtx,CD_CTXIDX_TSEC);
  cmdDfn          pDfn    = GLS_FIRST(cmdDfn,pLst);
  GLS_Tok         pIde;
  c_string        szIde, szS;
  assert0(cmdDfn_defn(pDfn,&pIde,_,_,_),"");
  szIde = GLS_Tok_string(pIde);
  if( HP_fun_defined(pHPat,CD_PAT_PARID) )
    szS = HP_fun_apply(pHPat,CD_PAT_PARID,szIde);
  else szS = szIde;
  fprintf(pSysOut,"%s",szS);
  if( szS != szIde ) FreeMem(szS);
  return C_True;
}

static c_bool CD_gendoc_partyp(HPat_T pHPat)
/* generate parameter type according template */
{ ROW(_)          pCmdCtx = (ROW(_))HP_getContext(pHPat);
  FILE*           pSysOut = OT_GET(FILE*,pCmdCtx,CD_CTXIDX_FILE);
  GLS_Lst(cmdDfn) pLst    = OT_GET(GLS_Lst(cmdDfn),pCmdCtx,CD_CTXIDX_TSEC);
  cmdDfn          pDfn    = GLS_FIRST(cmdDfn,pLst);
  cmdTyp          pTyp;
  c_string        szTyp, szS;
  Sink            pSnk    = Sink_open();
  assert0(cmdDfn_defn(pDfn,_,&pTyp,_,_),"");
  PT_TermToSink(pTyp,pSnk);
  szTyp = Sink_close(pSnk);
  if( HP_fun_defined(pHPat,CD_PAT_PARTYP) )
    szS = HP_fun_apply(pHPat,CD_PAT_PARTYP,szTyp);
  else szS = szTyp;
  fprintf(pSysOut,"%s",szS);
  if( szS != szTyp ) FreeMem(szS);
  FreeMem(szTyp);
  return C_True;
}

static c_bool CD_gendoc_parval(HPat_T pHPat)
/* generate default option value according template */
{ ROW(_)          pCmdCtx = (ROW(_))HP_getContext(pHPat);
  FILE*           pSysOut = OT_GET(FILE*,pCmdCtx,CD_CTXIDX_FILE);
  GLS_Lst(cmdDfn) pLst    = OT_GET(GLS_Lst(cmdDfn),pCmdCtx,CD_CTXIDX_TSEC);
  cmdDfn          pDfn    = GLS_FIRST(cmdDfn,pLst);
  cmdOptVal       pOptVal;
  cmdVal          pVal;
  c_string        szVal, szS;
  assert0(cmdDfn_defn(pDfn,_,_,&pOptVal,_),"");
  if( cmdOptVal_val(pOptVal,&pVal) )
  {
    szVal = CMD_Val_to_String(pVal);
    if( HP_fun_defined(pHPat,CD_PAT_PARVAL) )
      szS = HP_fun_apply(pHPat,CD_PAT_PARVAL,szVal);
    else szS = szVal;
    fprintf(pSysOut,"%s",*szS=='\0'?"\"\"":szS);
    if( szS != szVal ) FreeMem(szS);
    FreeMem(szVal);
  }
  return C_True;
}

static c_bool CD_gendoc_doltxt(HPat_T pHPat)
/* generate short documentation text according template */
{ ROW(_)    pCmdCtx = (ROW(_))HP_getContext(pHPat);
  FILE*     pSysOut = OT_GET(FILE*,pCmdCtx,CD_CTXIDX_FILE);
  cmdSource pSrc    = OT_GET(cmdSource,pCmdCtx,CD_CTXIDX_TSRC);
  GLS_Tok   pDol;
  c_string  szDol, szS;
  if( OT_CNT(pCmdCtx) == CD_CTXIDX_TDOC )
  {
    assert0(cmdSource_root(pSrc,_,&pDol,_,_,_,_,_,_,_),"");
  }
  else
  { GLS_Lst(cmdDfn) pLst = OT_GET(GLS_Lst(cmdDfn),pCmdCtx,CD_CTXIDX_TSEC);
    cmdDfn          pDfn = GLS_FIRST(cmdDfn,pLst);
    assert0(cmdDfn_defn(pDfn,_,_,_,&pDol),"");
  }
  szDol = GLS_Tok_string(pDol) + 2;
  if( HP_fun_defined(pHPat,CD_PAT_DOLTXT) )
    szS = HP_fun_apply(pHPat,CD_PAT_DOLTXT,szDol);
  else szS = szDol;
  fprintf(pSysOut,"%s",szS);
  if( szS != szDol ) FreeMem(szS);
  return C_True;
}

static c_bool CD_gendoc_doctxt(HPat_T pHPat)
/* generate long documentation text according template */
{ ROW(_)    pCmdCtx = (ROW(_))HP_getContext(pHPat);
  FILE*     pSysOut = OT_GET(FILE*,pCmdCtx,CD_CTXIDX_FILE);
  cmdSource pSrc    = OT_GET(cmdSource,pCmdCtx,CD_CTXIDX_TSRC);
  GLS_Tok   pDoc    = (GLS_Tok)NULL;
  c_string  szDoc   = (c_string)NULL, szS;
  if( OT_CNT(pCmdCtx) == CD_CTXIDX_TDOC )
  {
    assert0(cmdSource_root(pSrc,_,_,&pDoc,_,_,_,_,_,_),"");
  }
  else
  { cmdOptDoc pOptDoc = OT_GET(cmdOptDoc,pCmdCtx,CD_CTXIDX_TDOC);
    cmdOptDoc_doc(pOptDoc,&pDoc);
  }
  if( pDoc != (GLS_Tok)NULL )
  {
    szDoc = StrCopy(GLS_Tok_string(pDoc)+3);
    szDoc[strlen(szDoc)-3] = '\0';
    if( HP_fun_defined(pHPat,CD_PAT_DOCTXT) )
      szS = HP_fun_apply(pHPat,CD_PAT_DOCTXT,szDoc);
    else szS = szDoc;
    fprintf(pSysOut,"%s",szS);
    if( szS != szDoc ) FreeMem(szS);
    FreeMem(szDoc);
  }
  return C_True;
}

static c_bool CD_gendoc_argsec(HPat_T pHPat)
/* generate argument section according template */
{ ROW(_)          pCmdCtx = (ROW(_))HP_getContext(pHPat);
  cmdSource       pSrc    = OT_GET(cmdSource,pCmdCtx,CD_CTXIDX_TSRC);
  ROW(symbol)     pRow    = HP_getListPatRow(pHPat,CD_PAT_ARGSEC);
  symbol          pDfn    = OT_GET(symbol,pRow,0),
                  pTop    = OT_GET(symbol,pRow,1),
                  pBot    = OT_GET(symbol,pRow,2);
  GLS_Lst(cmdDfn) pLst, pItr;
  cmdOptDoc       pOptDoc;
  assert0(cmdSource_root(pSrc,_,_,_,&pLst,&pOptDoc,_,_,_,_),"");
  if( ! GLS_EMPTY(pLst) )
  {
    OT_PUSH(pOptDoc,pCmdCtx);
    OT_PUSH(pLst,pCmdCtx);
    HP_gendoc_pat(pHPat,pTop);
    GLS_FORALL(pItr,pLst)
    {
      OT_UPD(PT_Term,pCmdCtx,CD_CTXIDX_TSEC,pItr);
      if( pLst != pItr )
        HP_gendoc_pat(pHPat,CD_PAT_ARGSEC);
      HP_gendoc_pat(pHPat,pDfn);
    }
    HP_gendoc_pat(pHPat,pBot);
    OT_POP(pCmdCtx);
    OT_POP(pCmdCtx);
  }
  return C_True;
}

static c_bool CD_gendoc_optsec(HPat_T pHPat)
/* generate option section according template */
{ ROW(_)          pCmdCtx = (ROW(_))HP_getContext(pHPat);
  cmdSource       pSrc    = OT_GET(cmdSource,pCmdCtx,CD_CTXIDX_TSRC);
  ROW(symbol)     pRow    = HP_getListPatRow(pHPat,CD_PAT_OPTSEC);
  symbol          pDfn    = OT_GET(symbol,pRow,0),
                  pTop    = OT_GET(symbol,pRow,1),
                  pBot    = OT_GET(symbol,pRow,2);
  GLS_Lst(cmdDfn) pLst, pItr;
  cmdOptDoc       pOptDoc;
  assert0(cmdSource_root(pSrc,_,_,_,_,_,&pLst,&pOptDoc,_,_),"");
  if( ! GLS_EMPTY(pLst) )
  {
    OT_PUSH(pOptDoc,pCmdCtx);
    OT_PUSH(pLst,pCmdCtx);
    HP_gendoc_pat(pHPat,pTop);
    GLS_FORALL(pItr,pLst)
    {
      OT_UPD(PT_Term,pCmdCtx,CD_CTXIDX_TSEC,pItr);
      if( pLst != pItr )
        HP_gendoc_pat(pHPat,CD_PAT_OPTSEC);
      HP_gendoc_pat(pHPat,pDfn);
    }
    HP_gendoc_pat(pHPat,pBot);
    OT_POP(pCmdCtx);
    OT_POP(pCmdCtx);
  }
  return C_True;
}

static c_bool CD_gendoc_envsec(HPat_T pHPat)
/* generate environment section according template */
{ ROW(_)          pCmdCtx = (ROW(_))HP_getContext(pHPat);
  cmdSource       pSrc    = OT_GET(cmdSource,pCmdCtx,CD_CTXIDX_TSRC);
  ROW(symbol)     pRow    = HP_getListPatRow(pHPat,CD_PAT_ENVSEC);
  symbol          pDfn    = OT_GET(symbol,pRow,0),
                  pTop    = OT_GET(symbol,pRow,1),
                  pBot    = OT_GET(symbol,pRow,2);
  GLS_Lst(cmdDfn) pLst, pItr;
  cmdOptDoc       pOptDoc;
  assert0(cmdSource_root(pSrc,_,_,_,_,_,_,_,&pLst,&pOptDoc),"");
  if( ! GLS_EMPTY(pLst) )
  {
    OT_PUSH(pOptDoc,pCmdCtx);
    OT_PUSH(pLst,pCmdCtx);
    HP_gendoc_pat(pHPat,pTop);
    GLS_FORALL(pItr,pLst)
    {
      OT_UPD(PT_Term,pCmdCtx,CD_CTXIDX_TSEC,pItr);
      if( pLst != pItr )
        HP_gendoc_pat(pHPat,CD_PAT_ENVSEC);
      HP_gendoc_pat(pHPat,pDfn);
    }
    HP_gendoc_pat(pHPat,pBot);
    OT_POP(pCmdCtx);
    OT_POP(pCmdCtx);
  }
  return C_True;
}


static c_bool CD_load_pat(ROW(_) pCmdCtx)
/* load templates */
{ 
  if( strlen(template) > 0 )
  { Scn_Stream pStream;
    HPat_T     pHPat;
    PIT        pItr; 
    c_string   szT;
    c_bool     bResult = C_True;
    pHPat = HP_create();
    OT_PUSH(pHPat,pCmdCtx);
    HP_setContext(pHPat,pCmdCtx);
    HP_setPrintFun(pHPat,CD_gendoc_txt);
    if( strlen(refalias) > 0 )
      HP_setRefAlias(pHPat,stringToSymbol(refalias));
    HP_addPatSpec(pHPat,CD_PAT_PGMDFN,CD_gendoc_pgmdfn,HPAT_REF_PAT);
    HP_addPatSpec(pHPat,CD_PAT_ARGSEC,CD_gendoc_argsec,HPAT_REF_LIST);
    HP_addPatSpec(pHPat,CD_PAT_OPTSEC,CD_gendoc_optsec,HPAT_REF_LIST);
    HP_addPatSpec(pHPat,CD_PAT_ENVSEC,CD_gendoc_envsec,HPAT_REF_LIST);
    HP_addPatSpec(pHPat,CD_PAT_PGMID,CD_gendoc_pgmid,HPAT_REF_PAR);
    HP_addPatSpec(pHPat,CD_PAT_PARID,CD_gendoc_parid,HPAT_REF_PAR);
    HP_addPatSpec(pHPat,CD_PAT_PARTYP,CD_gendoc_partyp,HPAT_REF_PAR);
    HP_addPatSpec(pHPat,CD_PAT_PARVAL,CD_gendoc_parval,HPAT_REF_PAR);
    HP_addPatSpec(pHPat,CD_PAT_DOLTXT,CD_gendoc_doltxt,HPAT_REF_PAR);
    HP_addPatSpec(pHPat,CD_PAT_DOCTXT,CD_gendoc_doctxt,HPAT_REF_PAR);
    pItr = PIT_make(template); 
    while( ( szT = PIT_read(pItr) ) != NULL )
    { 
      pStream  = Stream_file(HP_getScanner(pHPat),"",szT,"");
      bResult &= HP_load(pHPat,pStream,NULL,CD_PAT_PGMDFN,recursiv);
    }
    PIT_drop(pItr);
    bResult &= HP_check(pHPat);
    return bResult;
  }
  else 
  {
    OT_PUSH((HPat_T)NULL,pCmdCtx);
    return C_True;
  }
}

static c_bool CD_init(int argc, string argv[], ROW(_)* pCmdCtx)
/* init */
{ cmdSource pSrc;
  FILE*     pSysOut;
  c_string  szPath, szBase;
  c_bool    bResult;
  CTX_init_cmddoc(argc, argv);
  initSymbols();
  MAP_init();
  HP_init();
  szPath   = FilePrefix(infile);
  szBase   = BaseFile(infile);
  pSrc     = CMD_init(szPath,szBase,C_False);
  *pCmdCtx = OT_CREATE_ADT(_);
  OT_PUSH(pSrc,*pCmdCtx);
  bResult  = CD_load_pat(*pCmdCtx);
  if( bResult == C_True )
  {
    pSysOut = OpnFile(outfile,"wt");
    OT_PUSH(pSysOut,*pCmdCtx);
  }
  FreeMem(szPath);
  FreeMem(szBase);
  return bResult;
}

void CD_quit(ROW(_) pCmdCtx)
/* quit */
{
  if( pCmdCtx != (ROW(_))NULL )
  { HPat_T pHPat = OT_GET(HPat_T,pCmdCtx,CD_CTXIDX_HPAT);
    FILE*  pSysOut;
    if( pHPat != (HPat_T)NULL ) HP_drop(pHPat);
    if( OT_CNT(pCmdCtx) > CD_CTXIDX_FILE )
    {
      pSysOut = OT_GET(FILE*,pCmdCtx,CD_CTXIDX_FILE); 
      if( pSysOut != (FILE*)NULL ) fclose(pSysOut);
    }
    OT_DEL_T(pCmdCtx);
  }
  CMD_done();
  HP_quit();
  MAP_quit();
  freeSymbols();
  CTX_quit();
}

int main(int argc, string argv[])
{ ROW(_) pCmdCtx = (ROW(_))NULL;
  if( CD_init(argc,argv,&pCmdCtx) )
  { HPat_T pHPat = OT_GET(HPat_T,pCmdCtx,CD_CTXIDX_HPAT);
    if( pHPat != (HPat_T)NULL )
      CD_gendoc_pgmdfn(pHPat);
    else CD_gendoc_raw(pCmdCtx);
  }
  CD_quit(pCmdCtx);
  BUG_CORE;
  return(0);
}
