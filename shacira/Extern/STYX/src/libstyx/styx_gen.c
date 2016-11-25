/* ------------------------------------------------------------------------- */
/*                                                                           */
/* [styx_gen.c]                 STYX Compiler Library                        */
/*                   - realizes an abstract syntax tree -                    */
/*                                                                           */
/* Copyright (c) 2002 by D\olle, Manns.                                      */
/* ------------------------------------------------------------------------- */

#include "standard.h"
#include "scn_base.h"
#include "prs.h"
#include "hmap.h"

#include "pathes.h"
#include "literal.h"
#include "prs_gen.h"
#include "cfg_abs.h"
#include "ptm.h"
#include "ptm_gen.h"
#include "gls.h"
#include "symbols.h"
#include "hset.h"
#include "scn_gen.h"
#include "scn_pre.h"
#include "sink.h"
#include "gstream.h"

#include "styx_int.h"
#include "styx_lim.h"
#include "styx_pim.h"


/*!!
   The module [styx_gen] provides an reentrant interface for the compilation of 
   STYX definitions. 
*/

/*I-------------------------- Types and macros ------------------------------ */


/* Scanner & parser translation */

#define UsageLet     -100
#define UsageIgn     1
#define UsageTok     2
#define UsageCom     3
#define UsageLan     4
#define UsageInd     5

#define InitialGroup stringToSymbol("_INIT_")

#define RootCtx(c)   ( ((c)->root == (Styx_T)NULL) ? (c) : (c)->root )

/* Interface generation */

#define INTEXT       "int" /* FileNames will be LANGUAGE_INTEXT.(c|h) */
#define ANTEXT       "ant" /* FileNames will be LANGUAGE_ANTEXT.(c|h) */

#define LineLen      78


ExternalType( StyxApp_T ) /* Abstract STYX application type */
{
  PLR_Tab PTab; /* STYX Parse table */
  Scn_T   Scn;  /* STYX Scan table  */
};


ExternalType( Styx_T ) /* Abstract STYX compiler type */
{
  StyxApp_T                styapp;      /* STYX application configuration */
  /* STYX compilation configuration                                       */
  c_bool                   verbose;     /* print progress information     */
  c_bool                   diagnose;    /* print diagnose information     */
  c_bool                   conflicts;   /* allow conflicts ?              */
  /* Parsing & semantic check of STYX definition                          */
  c_string                 language;    /* STYX language                  */
  symbol                   incpath;     /* STYX include & embedded path   */
  PT_Term                  PTree;       /* Source derivation tree         */
  PT_Diag                  diag;        /* Diagnose context               */
  MAPTY                    gloty;       /* Type for global definitions    */
  MAP(PT_Term, PT_Term)    glo;         /* Global definitions             */
  MAP(symbol,PT_Term)      grp;         /* Scan groups                    */
  MAP(GLS_Tok,symbol)      grptok;      /* Scan group tokens              */
  MAP(symbol,symbol)       langrp;      /* Embedded language token group  */
  MAP(GLS_Tok,symbol)      tokgrp;      /* Token --> group to activate    */
  MAP(symbol,SET(symbol))  metagrp;     /* meta group --> token groups    */
  MAP(GLS_Tok,byte)        tokflg;      /* special token flags            */
  Styx_T                   root;        /* Main language                  */
  MAP(symbol,Styx_T)       embed;       /* Embedded languages             */
  c_string (*ef_info)(Styx_T styctx,c_string language, c_string incpath);
                /* Embedded language path / definition retrieval function */
  int (*ef_compile)(Styx_T styctx, c_string e_info, c_string incpath);
                /* Embedded language path / definition compile function   */
  Any_T                    extctx;      /* external context               */
  HS_Set                   tkset;       /* Used tokens                    */
  MAP(symbol,_)            indtokkeys;  /* (de)indent token keywords      */
  int                      errorCnt;    /* number of translation errors   */
  /* Scanner translation                                                  */
  MAP(GLS_Tok,RegSet_T)    qlx;         /* Computed RegSets               */
  /* Scan & parse table    generation                                     */
  PLR_Tab                  PTab;        /* Parse table                    */
  Scn_T                    Scn;         /* Scan table                     */
  /* abstract syntax data structure ( see comments in cfg_abs.c )         */
  int*                     aPol;
  HS_Set*                  aNtm;
  HS_Set*                  aPrd;
  /* Interface generation                                                 */
  FILE*                    SysOut;      /* Interface output file          */
  c_bool                   genabs; 
                           /* True: generate for row representation       */
  int                      maxlen;      
                           /* Layout: maximal function name length        */
  c_string                 tkclsnam;    /* Token class name               */
  c_string                 lprefix;     /* Language prefix                */
  c_string                 cprefix;     /* comment prefix                 */
  c_string                 csuffix;     /* comment suffix                 */
};


/*I----------------------------- Init & Quit --------------------------------- */

StyxApp_T STYX_app_init(void)
/* init STYX application */
{ StyxApp_T styapp;
  initSymbols();
  MAP_init();
  styx_initSymbols();
  styapp = New(StyxApp_T);
  Scn_get_styx(&styapp->Scn);
  styapp->PTab = PLR_get_styx();
  return styapp;
}

void STYX_app_quit(StyxApp_T styapp)
/* quit STYX application; release resources */
{
  if( styapp != (StyxApp_T)NULL )
  {
    if( styapp->PTab != (PLR_Tab)NULL ) 
    {
      PLR_delTab(styapp->PTab); 
      styapp->PTab = (PLR_Tab)NULL;
    }
    if( styapp->Scn != (Scn_T)NULL ) 
    {
      Scn_free(styapp->Scn); 
      styapp->Scn = (Scn_T)NULL;
    }
    FreeMem(styapp);
  }
  styx_quitSymbols();
  MAP_quit();
  freeSymbols();
}

/*forward*/ void STYX_quit(Styx_T styctx);
/*forward*/ int STYX_compile_file
                (
                  Styx_T styctx, c_string stydfn, c_string incpath
                );
/*forward*/ int STYX_compile_string
                (
                  Styx_T styctx, c_string stydfn, c_string incpath
                );

static void STYX_reset(Styx_T styctx)
{ 
  styctx->errorCnt    = 0;
  styctx->SysOut      = (FILE*)NULL;
  styctx->genabs      = C_False;
  styctx->maxlen      = 0;
  if( styctx->embed != (MAP(_,_))NULL ) 
  { 
    if( MAP_count(styctx->embed) > 0 )
    { MAPIT itr; Styx_T rng; symbol dom;
      ROW(Styx_T) tmp = OT_CREATE_ADT(Styx_T);
      long cnt, i;
      MAP_forItrAsg(dom,rng,itr,styctx->embed)
      {
        if( !strcmp(symbolToString(dom),rng->language) )
          OT_PUSH(rng,tmp);
      }
      cnt = OT_CNT(tmp);
      for( i=0; i < cnt; ++i )
        STYX_quit(OT_GET(Styx_T,tmp,i));
      OT_DEL_T(tmp);
    }
    MAP_freeMap(styctx->embed);
    styctx->embed = (MAP(_,_))NULL;
  }
  if( styctx->grp != (MAP(_,_))NULL ) 
  {
    MAP_freeMap(styctx->grp);
    styctx->grp = (MAP(_,_))NULL;
  }
  if( styctx->grptok != (MAP(_,_))NULL ) 
  { 
    MAP_freeMap(styctx->grptok);
    styctx->grptok = (MAP(_,_))NULL;
  }
  if( styctx->langrp != (MAP(_,_))NULL ) 
  { 
    MAP_freeMap(styctx->langrp);
    styctx->langrp = (MAP(_,_))NULL;
  }
  if( styctx->tokgrp != (MAP(_,_))NULL ) 
  { 
    MAP_freeMap(styctx->tokgrp);
    styctx->tokgrp = (MAP(_,_))NULL;
  }
  if( styctx->metagrp != (MAP(_,_))NULL ) 
  { MAPIT itr; SET(symbol) rng; symbol dom;
    MAP_forItrAsg(dom,rng,itr,styctx->metagrp) 
      HS_DROP_SET(rng);
    MAP_freeMap(styctx->metagrp);
    styctx->metagrp = (MAP(_,_))NULL;
  }
  if( styctx->tokflg != (MAP(_,_))NULL ) 
  { 
    MAP_freeMap(styctx->tokflg);
    styctx->tokflg = (MAP(_,_))NULL;
  }
  if( styctx->glo != (MAP(_,_))NULL ) 
  {
    MAP_freeMap(styctx->glo);
    styctx->glo = (MAP(_,_))NULL;
  }
  if( styctx->qlx != (MAP(_,_))NULL ) 
  { MAPIT itr; RegSet_T rng; symbol dom;
    MAP_forItrAsg(dom,rng,itr,styctx->qlx) 
      RegSet_Free(rng);
    MAP_freeMap(styctx->qlx);
    styctx->qlx = (MAP(_,_))NULL;
  }
  if( styctx->indtokkeys != (MAP(symbol,_))NULL )
  {
    MAP_freeMap(styctx->indtokkeys);
    styctx->indtokkeys = (MAP(symbol,_))NULL;
  }
  if( styctx->gloty != (MAPTY)NULL ) 
  {
    MAP_freeTyp(styctx->gloty);
    styctx->gloty = (MAPTY)NULL;
  }
  if( styctx->tkset != (HS_Set)NULL ) 
  {
    HS_DROP_SET(styctx->tkset);
    styctx->tkset = (HS_Set)NULL;
  }
  if( styctx->PTree != (PT_Term)NULL ) 
  {
    PT_delT(styctx->PTree);
    styctx->PTree = (PT_Term)NULL;
  }
  if( styctx->PTab != (PLR_Tab)NULL ) 
  {
    acfg_quit(styctx->PTab,styctx->aPol,styctx->aNtm,styctx->aPrd);
    PLR_delTab(styctx->PTab);
    styctx->PTab = (PLR_Tab)NULL;
    styctx->aPol = (int*)NULL;
    styctx->aNtm = (HS_Set*)NULL;
    styctx->aPrd = (HS_Set*)NULL;
  }
  if( styctx->Scn != (Scn_T)NULL ) 
  {
    Scn_free(styctx->Scn); 
    styctx->Scn = (Scn_T)NULL;
  }
  if( styctx->cprefix != (c_string)NULL ) 
  {
    FreeMem(styctx->cprefix);
    styctx->cprefix = (c_string)NULL;
  }
  if( styctx->csuffix != (c_string)NULL ) 
  {
    FreeMem(styctx->csuffix);
    styctx->csuffix = (c_string)NULL;
  }
  if( styctx->diag != (PT_Diag)NULL )
  {
    PT_diag_setErrorCnt(styctx->diag,0);
    PT_diag_setWarningCnt(styctx->diag,0);
  }
}

Styx_T STYX_init
       (
         StyxApp_T styapp, c_string language,
         void (*prMsg)(c_string msg), c_bool verbose, c_bool diagnose
       )
/* init STYX compilation for 'language';
   'prMsg'    --> print function or NULL
   'verbose'  --> (de)activate progress information
   'diagnose' --> (de)activate diagnose information 
*/
{ Styx_T styctx;
  BUG_NULL(styapp); BUG_NULL(language);
  styctx              = New(Styx_T);
  styctx->root        = (Styx_T)NULL;
  styctx->styapp      = styapp;
  styctx->verbose     = verbose;
  styctx->diagnose    = diagnose;
  styctx->conflicts   = C_True;
  styctx->language    = StrCopy(language);
  styctx->incpath     = (symbol)NULL;
  styctx->diag        = PT_diag_init(prMsg!=NULL?prMsg:prMsg_stderr);
  styctx->PTree       = (PT_Term)NULL;
  styctx->gloty       = (MAPTY)NULL;
  styctx->glo         = (MAP(_,_))NULL;
  styctx->embed       = (MAP(_,_))NULL;
  styctx->ef_info     = 
    (c_string (*)(Styx_T styctx,c_string language,c_string incpath))NULL;
  styctx->ef_compile  = STYX_compile_file;
  styctx->extctx      = (Any_T)NULL;
  styctx->grp         = (MAP(_,_))NULL;
  styctx->grptok      = (MAP(_,_))NULL;
  styctx->langrp      = (MAP(_,_))NULL;
  styctx->tokgrp      = (MAP(_,_))NULL;
  styctx->metagrp     = (MAP(_,_))NULL;
  styctx->tokflg      = (MAP(_,_))NULL;
  styctx->tkset       = (HS_Set)NULL;
  styctx->indtokkeys  = (MAP(symbol,_))NULL;
  styctx->errorCnt    = 0;
  styctx->qlx         = (MAP(_,_))NULL;
  styctx->PTab        = (PLR_Tab)NULL;
  styctx->Scn         = (Scn_T)NULL;
  styctx->aPol        = (int*)NULL;
  styctx->aNtm        = (HS_Set*)NULL;
  styctx->aPrd        = (HS_Set*)NULL;
  styctx->SysOut      = (FILE*)NULL;
  styctx->genabs      = C_False;
  styctx->maxlen      = 0;
  styctx->tkclsnam    = Str_printf("T%s",language);
  styctx->lprefix     = StrCopy(language);
  styctx->cprefix     = (c_string)NULL;
  styctx->csuffix     = (c_string)NULL;
  return styctx;
}

void STYX_quit(Styx_T styctx)
/* quit STYX compilation; release resources */
{
  if(styctx != (Styx_T)NULL )
  {
    STYX_reset(styctx);
    if( styctx->language != (c_string)NULL ) 
    {
      FreeMem(styctx->language);
      styctx->language = (c_string)NULL;
    }
    if( styctx->lprefix != (c_string)NULL ) 
    {
      FreeMem(styctx->lprefix);
      styctx->lprefix = (c_string)NULL;
    }
    if( styctx->tkclsnam != (c_string)NULL ) 
    {
      FreeMem(styctx->tkclsnam);
      styctx->tkclsnam = (c_string)NULL;
    }
    if( styctx->diag != (PT_Diag)NULL ) 
    {
      PT_diag_quit(styctx->diag);
      styctx->diag = (PT_Diag)NULL;
    }
    FreeMem(styctx);
  }
}

/*I----------------------------- Set & Get ----------------------------------- */

void STYX_set_conflict_policy(Styx_T styctx, c_bool conflicts)
/* (dis)allow conflicts during parse table generation */
{
  BUG_NULL(styctx);
  styctx->conflicts = conflicts;
}

void STYX_set_verbose(Styx_T styctx, c_bool verbose)
/* (de)activate progress information */
{
  BUG_NULL(styctx);
  styctx->verbose = verbose;
}

void STYX_set_diagnose(Styx_T styctx, c_bool diagnose)
/* (de)activate diagnose information */
{
  BUG_NULL(styctx);
  styctx->diagnose = diagnose;
}

void STYX_set_shortform(Styx_T styctx, c_bool shortform)
/* (de)activate short filenames ( default: longform ) */
{
  BUG_NULL(styctx);
  if( styctx->lprefix != (c_string)NULL ) FreeMem(styctx->lprefix);
  if( shortform )
    styctx->lprefix = Str_printf("%.4s",styctx->language);
  else
    styctx->lprefix = StrCopy(styctx->language);
  if( styctx->tkclsnam != (c_string)NULL ) FreeMem(styctx->tkclsnam);
  if( shortform )
    styctx->tkclsnam = Str_printf("T%.4s",styctx->language);
  else
    styctx->tkclsnam = Str_printf("T%s",styctx->language);
}

void STYX_set_context(Styx_T styctx, Any_T extctx)
/* set external context information */
{
  BUG_NULL(styctx);
  assert0(RootCtx(styctx) == styctx,"");
  styctx->extctx = extctx;
}

Any_T STYX_get_context(Styx_T styctx)
/* get external context information */
{
  BUG_NULL(styctx);
  return RootCtx(styctx)->extctx;
}

void STYX_set_fun_epath
     (
       Styx_T styctx, 
       c_string (*ef_path)(Styx_T styctx, c_string language, c_string incpath)
     )
/* (re)set embedded language path retrieval function */
{
  BUG_NULL(styctx);
  assert0(RootCtx(styctx) == styctx,"");
  styctx->ef_info    = ef_path;
  styctx->ef_compile = STYX_compile_file;
}

void STYX_set_fun_edfn
     (
       Styx_T styctx, 
       c_string (*ef_dfn)(Styx_T styctx, c_string language, c_string incpath)
     )
/* (re)set embedded language definition retrieval function */
{
  if( ef_dfn == NULL )
    STYX_set_fun_epath(styctx,ef_dfn);
  else
  {
    BUG_NULL(styctx);
    assert0(RootCtx(styctx) == styctx,"");
    styctx->ef_info    = ef_dfn;
    styctx->ef_compile = STYX_compile_string;
  }
}

MAP(symbol,Styx_T) STYX_get_embed(Styx_T styctx)
/* STYX compilations of embedded languages or NULL;
   The result map has to be released.
*/
{ MAP(symbol,Styx_T) embed = (MAP(_,_))NULL;
  if( MAP_count(styctx->embed) > 0 )
  { MAPIT itr; Styx_T rng; symbol dom;
    embed = MAP_newPrimMap();
    MAP_forItrAsg(dom,rng,itr,styctx->embed)
    {
      if( !strcmp(symbolToString(dom),rng->language) )
        MAP_dfndom(embed,dom,rng);
    }
  }
  return embed;
}

void STYX_get_tables(Styx_T styctx, PLR_Tab* PTab, Scn_T* Scn)
/* get scan & parse table */
{
  BUG_NULL(styctx);
  if( PTab != (PLR_Tab*)NULL ) 
    *PTab = styctx->PTab;
  if( Scn != (Scn_T*)NULL ) 
    *Scn = styctx->Scn;
}

/*I----------------------------- Compilation --------------------------------- */

/* semantic check */

static c_bool pop_group(Styx_T styctx, styxQlxGrp grp)
{ 
  return styxQlxGrp_pop(grp);
}

static c_bool push_group(Styx_T styctx, styxQlxGrp grp)
{ 
  return styxQlxGrp_pigrp(grp) || styxQlxGrp_pgrp(grp,_);
}

static void getGroupInfo
            (
              Styx_T styctx, styxQlxGrp grp, 
              symbol* grpsym, c_bool prError
            )
{ GLS_Tok id;
  if( grpsym != (symbol*)NULL )
    *grpsym = (symbol)NULL;
  if( styxQlxGrp_grp(grp,&id) || styxQlxGrp_pgrp(grp,&id) )
  {
    if( !MAP_defined(styctx->grp,GLS_Tok_symbol(id)) )
    {
      if( prError )
        PT_diag_err
        (
          id,styctx->diag,"identifier '%s' undefined",
          GLS_Tok_string(id)
        );
    }
    else
    {
      if( grpsym != (symbol*)NULL )
        *grpsym = GLS_Tok_symbol(id);
    }
  }
  else
  if( styxQlxGrp_igrp(grp) || styxQlxGrp_pigrp(grp) )
  {
    if( grpsym != (symbol*)NULL )
      *grpsym = InitialGroup;
  }
}

static void addTokenFlag(Styx_T styctx, GLS_Tok id, byte f)
{
  if( MAP_defined(styctx->tokflg,id) )
    f |= MAP_apply_small(byte,styctx->tokflg,id);
  MAP_ovrdom(styctx->tokflg,id,f);
}

static PT_Term getDfn(Styx_T styctx, GLS_Tok id, c_bool force)
{ Styx_T rootctx = RootCtx(styctx);
  if(MAP_defined(styctx->glo,id))
    return MAP_apply(PT_Term,styctx->glo,id);
  else
  {
    if( MAP_defined(rootctx->embed,GLS_Tok_symbol(id)) )
      return MAP_apply(PT_Term,styctx->grp,GLS_Tok_symbol(id));
  }
  if( force == C_True ) C_BUG; 
  return (PT_Term)NULL;
}

static int qlx_usage(Styx_T styctx, PT_Term t)
{ styxQlxCat cat;
  if (styx_QlxDfn(t,_) )
    styxQlxDfn_defn((styxQlxDfn)t,&cat,_,_,_,_,_);
  else
    styxQlxDfn_defn((styxQlxDfn)getDfn(styctx,t,C_True),&cat,_,_,_,_,_);
  if (styxQlxCat_letC(cat)) return UsageLet;
  if (styxQlxCat_tokC(cat)) return UsageTok;
  if (styxQlxCat_comC(cat)) return UsageCom;
  if (styxQlxCat_ignC(cat)) return UsageIgn;
  if (styxQlxCat_lanC(cat)) return UsageLan;
  if (styxQlxCat_indC(cat)) return UsageInd;
  C_BUG; return 0;
}

static c_bool qlx_quotient(Styx_T styctx, GLS_Tok id)
{ styxExp exp;
  styxQlxDfn_defn((styxQlxDfn)getDfn(styctx,id,C_True),_,_,_,_,_,&exp);
  return styxExp_quot(exp,_,_);
}

static c_bool qlx_dyck(Styx_T styctx, GLS_Tok id)
{ styxExp exp;
  styxQlxDfn_defn((styxQlxDfn)getDfn(styctx,id,C_True),_,_,_,_,_,&exp);
  if( styxExp_quot(exp,&exp,_) )
    /* noop */;
  return styxExp_dyck(exp,_,_,_);
}

static c_bool qlx_pattern(Styx_T styctx, GLS_Tok id)
{ styxExp exp;
  styxQlxDfn_defn((styxQlxDfn)getDfn(styctx,id,C_True),_,_,_,_,_,&exp);
  if( styxExp_quot(exp,&exp,_) )
    /* noop */;
  return styxExp_spat(exp,_,_,_) || styxExp_epat(exp,_,_,_);
}

static c_bool qlx_ica(Styx_T styctx, GLS_Tok id)
{ styxQlxOpt opt;
  styxQlxDfn_defn((styxQlxDfn)getDfn(styctx,id,C_True),_,&opt,_,_,_,_);
  return styxQlxOpt_ignca(opt);
}

static void Pass1(Styx_T styctx, styxSource s)
/* Collecting definitions and scoping rules */
{ Styx_T lanctx, rootctx; bool startflg = False; int indcnt = 0, rc;
  MAP(PT_Term,NULL) pro = MAP_newMap(styctx->gloty); /* Productions */
  PT_Itr it; styxOptCfg optcfg; GLS_Lst(styxDfn) dfns;
  rootctx = RootCtx(styctx);
  styxSource_root(s,_,_,&optcfg);
  /* set initial group */
  MAP_dfndom(styctx->grp,InitialGroup,(PT_Term)NULL);
  /* collect definitions */
  PT_FORALL(it,s)
  { PT_Term t = PT_termIT(it), st = (PT_Term)NULL;
    if (PT_stateIT(it) == PT_POST)
    { styxQlxDfn qd; styxDfn pd; styxPrd p; GLS_Tok id, sgid, dgid;
      /* Scope(Source): all identifiers in QLX definitions */
      if (styx_QlxDfn(t,&qd) )
      { styxQlxOpt o; styxQlxCat c; styxQlxGrp gsrc, gdst; styxExp e, e1;
        if( styxQlxDfn_igrp(qd,&id) || styxQlxDfn_xgrp(qd,&id) ||
            styxQlxDfn_mgrp(qd,&id,_) )
        { GLS_Lst(GLS_Tok) ids, lst;
          if (MAP_defined(styctx->grp,GLS_Tok_symbol(id)) ||
              !strcmp(styctx->language,GLS_Tok_string(id)))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' already defined",
              GLS_Tok_string(id)
            );
          else 
          {
            MAP_dfndom(styctx->grp,GLS_Tok_symbol(id),qd);
            if( styxQlxDfn_mgrp(qd,_,&ids) )
            { SET(symbol) grpset = HS_CREATE_ADTSET(symbol);
              MAP_dfndom(styctx->metagrp,GLS_Tok_symbol(id),grpset);
              GLS_FORALL(lst,ids)
              { GLS_Tok grpid = GLS_FIRST(GLS_Tok,lst);
                if( !strcmp(styctx->language,GLS_Tok_string(grpid)) )
                  HS_SET_ELM(InitialGroup,grpset);
                else
                if( !MAP_defined(styctx->grp,GLS_Tok_symbol(grpid)) )
                  PT_diag_err
                  (
                    grpid,styctx->diag,"identifier '%s' undefined",
                    GLS_Tok_string(grpid)
                  );
                else
                if( MAP_defined(styctx->metagrp,GLS_Tok_symbol(grpid)) )
                  PT_diag_err(grpid,styctx->diag,"invalid group");
                else
                  HS_SET_ELM(GLS_Tok_symbol(grpid),grpset);
              }
            }
          }
        }
        else
        if ( styxQlxDfn_defn(qd,&c,&o,&gsrc,&id,&gdst,&e) )
        {
          if( !styxQlxCat_lanC(c) && MAP_defined(styctx->glo,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' already defined",
              GLS_Tok_string(id)
            );
          else 
          {
            if( !styxQlxCat_lanC(c) )
              MAP_dfndom(styctx->glo,id,qd);
            if( styxQlxCat_letC(c) )
            {
              if( !styxQlxGrp_non(gsrc) || !styxQlxGrp_non(gdst) )
                PT_diag_err(qd,styctx->diag,"grouping not allowed here");
            }
            else
            if( styxQlxCat_lanC(c) )
            {
              if( !(styxQlxGrp_grp(gsrc,&sgid) && styxQlxGrp_grp(gdst,&dgid)) )
                PT_diag_err
                (
                  qd,styctx->diag,"invalid or incomplete embedded language specification"
                );
              else
              { c_string lantok, lanpath; symbol lansym;
                lantok  = Str_printf
                          (
                            "%s%s",GLS_Tok_string(sgid),GLS_Tok_string(id)
                          );
                lansym  = stringToSymbol(lantok);
                if( MAP_defined(styctx->grp,lansym) )
                  PT_diag_err
                  (
                    id,styctx->diag,"identifier '%s' already defined",
                    symbolToString(lansym)
                  );
                else
                { styxCat c; 
                  MAP_dfndom(styctx->grp,lansym,qd);
                  if( !MAP_defined(rootctx->embed,GLS_Tok_symbol(sgid)) )
                  { c_string incpath = symbolToString(styctx->incpath);
                    lanctx = STYX_init
                             (
                               styctx->styapp, GLS_Tok_string(sgid),
                               PT_diag_msgFun(styctx->diag),
                               styctx->verbose, styctx->diagnose
                             );
                    lanctx->root = rootctx;
                    MAP_dfndom(rootctx->embed,GLS_Tok_symbol(sgid),lanctx);
                    MAP_ovrdom(rootctx->embed,lansym,lanctx);
                    if( rootctx->ef_info != NULL )
                      lanpath = 
                        (*rootctx->ef_info)(styctx,GLS_Tok_string(sgid),incpath);
                    else
                      lanpath = MkPath(incpath,GLS_Tok_string(sgid),".sty",'p');
                    rc = (*rootctx->ef_compile)(lanctx,lanpath,incpath);
                    if( rc != 0 )
                      PT_diag_err
                      (
                        qd,styctx->diag,
                        "compilation of embedded language '%s' failed",
                        GLS_Tok_string(sgid)
                      );
                    FreeMem(lanpath);
                  }
                  else
                  {
                    lanctx = MAP_apply(Styx_T,rootctx->embed,GLS_Tok_symbol(sgid));
                    MAP_ovrdom(rootctx->embed,lansym,lanctx);
                    if( lanctx->qlx == (MAP(_,_))NULL )
                      PT_diag_err
                      (
                        qd,styctx->diag,
                        "cyclic referenced embedded language '%s'",
                        GLS_Tok_string(sgid)
                      );
                  }
                  if( strcmp(styctx->language,GLS_Tok_string(dgid)) &&
                      strcmp(lanctx->language,GLS_Tok_string(dgid))  )
                    PT_diag_err
                    (
                      dgid,styctx->diag,
                      "unknown EOF or follow token language '%s'",
                      GLS_Tok_string(dgid)
                    );
                  if( MAP_defined(lanctx->glo,id) )
                    st = MAP_apply(PT_Term,lanctx->glo,id);
                  if( st != (PT_Term)NULL && 
                      ( !styx_Dfn(st,&pd) ||
                        !styxDfn_defn(pd,&c,_,_,_) || !styxCat_bgnC(c) ) )
                    PT_diag_err
                    (
                      id,styctx->diag,
                      "start symbol '%s' doesn't exist in language '%s'",
                      GLS_Tok_string(id), GLS_Tok_string(sgid)
                    );
                }
                FreeMem(lantok);
              }
            }
            else
            { symbol srcsym = (symbol)NULL,
                     dstsym = (symbol)NULL;
              getGroupInfo(styctx,gsrc,&srcsym,C_True);
              if( srcsym == (symbol)NULL )
                srcsym = InitialGroup;
              MAP_dfndom(styctx->grptok,id,srcsym);
              if( MAP_defined(rootctx->embed,srcsym) )
                PT_diag_err(gsrc,styctx->diag,"invalid group or group list");
              getGroupInfo(styctx,gdst,&dstsym,C_True);
              if( MAP_defined(styctx->metagrp,dstsym) )
                PT_diag_err(gdst,styctx->diag,"invalid group");
              else
              if( dstsym != (symbol)NULL )
              {
                MAP_ovrdom(styctx->tokgrp,id,dstsym);
              }
              if( push_group(styctx,gdst) || pop_group(styctx,gdst) )
              {
                addTokenFlag(styctx,id,SCN_FLG_GroupStack);
                if( styxExp_spat(e,_,_,_) ||
                    ( styxExp_quot(e,&e1,_) && styxExp_spat(e1,_,_,_) ) )
                  PT_diag_err(c,styctx->diag,"push/pop group not allowed here");
              }
              if( MAP_defined(rootctx->embed,dstsym) )
              {
                addTokenFlag(styctx,id,SCN_FLG_SwitchToken);
                if( MAP_defined(styctx->langrp,dstsym) )
                {
                  if( MAP_apply(symbol,styctx->langrp,dstsym) != srcsym )
                    PT_diag_err
                    (
                      gsrc,styctx->diag,
                      "different embedded language token group '%s'",
                      symbolToString(srcsym)
                    );
                }
                else
                {
                  MAP_dfndom(styctx->langrp,dstsym,srcsym);
                }
                if( push_group(styctx,gdst) )
                  PT_diag_err(c,styctx->diag,"push group not allowed here");
                if( ! styxQlxCat_tokC(c) && ! styxQlxCat_comC(c) )
                  PT_diag_err(c,styctx->diag,"invalid switch token category");
              }
            }
          }
          /* quotient expression must be set or sequence */
          if( styxExp_quot(e,_,&e1) &&
              !( styxExp_set(e1,_) || styxExp_sequ(e1,_) ) )
            PT_diag_err
            (
              e1,styctx->diag,"quotient expression must be set or sequence"
            );
          /* CaseIgnore only with categories tok, com */
          if(   styxQlxOpt_ignca(o) && 
              ! styxQlxCat_tokC(c)  && 
              ! styxQlxCat_comC(c)   )
            PT_diag_err(o,styctx->diag,"CaseIgnore not allowed here");
          /* dyck, pattern not with categories let, lan, ind */
          if( (styxExp_quot(e,_,_) || styxExp_dyck(e,_,_,_) || 
               styxExp_spat(e,_,_,_) || styxExp_epat(e,_,_,_)) && 
              (styxQlxCat_letC(c) || styxQlxCat_lanC(c) || styxQlxCat_indC(c)) )
            PT_diag_err(e,styctx->diag,"quotient, dyck or pattern token definition not allowed here");
          /* pattern not with category ign */
          if( (styxExp_quot(e,_,_) || styxExp_spat(e,_,_,_) || styxExp_epat(e,_,_,_)) && 
              styxQlxCat_ignC(c) )
            PT_diag_err(e,styctx->diag,"quotient or pattern token definition not allowed here");
          /* maximal 1 (de)indent token per scanner (group) */
          indcnt += styxQlxCat_indC(c);
          if( indcnt > 1 )
            PT_diag_err(o,styctx->diag,"too many (de)indent tokens");
        }
      }

      /* Scope(Source): all identifiers in CFG definitions */
      if (styx_Dfn(t,&pd))
      { styxCat c; styxDfnOpt o;
        if ( styxDfn_defn(pd,&c,&o,&id,_) )
        { 
          if (MAP_defined(styctx->glo,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' already defined",
              symbolToString(GLS_Tok_symbol(id))
            );
          else MAP_dfndom(styctx->glo,id,pd);
          if (MAP_emptyMap(pro))
            PT_diag_err
            (
              id,styctx->diag,"production '%s' has no rules",
              GLS_Tok_string(id)
            );
          MAP_rmvall(pro);
          startflg |= styxCat_bgnC(c);
        }
      }

      /* Scope(Definition): all production identifiers */
      if (styx_Prd(t,&p))
      { 
        if ( styxPrd_prod(p,_,&id,_) )
        { 
          if (MAP_defined(pro,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' already defined",
              GLS_Tok_string(id)
            );
          else MAP_dfndom(pro,id,NULL);
        }
      }
    }
  }
  if( ! startflg && styxOptCfg_cfg(optcfg,&dfns) && ! GLS_EMPTY(dfns) ) 
    PT_diag_err(dfns,styctx->diag,"missing start production");
  MAP_freeMap(pro);
}

static void Pass2(Styx_T styctx, styxSource s)
/* References */
{ PT_Itr it; Styx_T rootctx = RootCtx(styctx), tokctx;
  MAP(PT_Term,Styx_T) lanexp = MAP_newPrimMap();
  GLS_Lst(styxQlxDfn) qlxdfns;
  styxSource_root(s,_,&qlxdfns,_);
  PT_FORALL(it,s)
  { PT_Term t = PT_termIT(it);
    styxExp exp; GLS_Tok id, lid;
    if (PT_stateIT(it) == PT_PRAE)
    { styxQlxDfn qd; styxQlxCat c; styxQlxGrp g;
      if (styx_QlxDfn(t,&qd) &&
          styxQlxDfn_defn(qd,&c,_,_,_,&g,&exp) &&
          styxQlxCat_lanC(c) &&
          styxQlxGrp_grp(g,&lid))
      { 
        if( MAP_defined(rootctx->embed,GLS_Tok_symbol(lid)) )
          MAP_dfndom
          (
            lanexp,exp,MAP_apply(Styx_T,rootctx->embed,GLS_Tok_symbol(lid))
          );
        else
          MAP_dfndom(lanexp,exp,styctx);
      }
    }
    else
    if (PT_stateIT(it) == PT_POST)
    { styxMbr m; 
      if (styx_Exp(t,&exp) )
      {
        if ( styxExp_ident(exp,&id) )
        {
          tokctx = styctx;
          if( MAP_defined(lanexp,exp) )
            tokctx = MAP_apply(Styx_T,lanexp,exp);
          if (!MAP_defined(tokctx->glo,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' undefined",GLS_Tok_string(id)
            );
          else
            if (!styx_QlxDfn(MAP_apply(PT_Term,tokctx->glo,id),_))
              PT_diag_err
              (
                id,styctx->diag,"'%s' is no QLX-identifier",
                GLS_Tok_string(id)
              );
          else
            if( qlx_usage(tokctx,id) == UsageLan || 
                qlx_quotient(tokctx,id) || qlx_dyck(tokctx,id) 
                /*|| qlx_pattern(tokctx,id)*/ )
              PT_diag_err
              (
                id,styctx->diag,"'%s' can't be used as subexpression",
                GLS_Tok_string(id)
              );
        }
      }
      if (styx_Mbr(t,&m) )
      { 
        if ( styxMbr_ntm(m,&id) )
        { 
          if (!MAP_defined(styctx->glo,id) &&
              !MAP_defined(rootctx->embed,GLS_Tok_symbol(id)))
          {
            if( !GLS_EMPTY(qlxdfns) )
              PT_diag_err
              (
                id,styctx->diag,"identifier '%s' undefined",GLS_Tok_string(id)
              );
          }
          else
          if (MAP_defined(styctx->glo,id))
          { PT_Term def = MAP_apply(PT_Term,styctx->glo,id); 
            styxQlxDfn qd; styxQlxCat qc;
            if( ! ( styx_Dfn(def,_)                     ||
                    ( styx_QlxDfn(def,&qd)              &&
                      styxQlxDfn_defn(qd,&qc,_,_,_,_,_) &&
                      (styxQlxCat_tokC(qc) || styxQlxCat_lanC(qc)) ) ) )
              PT_diag_err
              (
                id,styctx->diag,"'%s' is no grammar symbol",GLS_Tok_string(id)
              );
          }
        }
      }
    }
  }
  MAP_freeMap(lanexp);
}

/* Scanner Translation */

static RegSet_T trans_Ide(Styx_T styctx, GLS_Tok id);
static RegSet_T trans_Exp(Styx_T styctx, styxExp e);

static RegSet_T TRANS_RegSet_String(string s)
{ RegSet_T reg; long len; c_bool ucs4;
  wc_string tstring = LIT_styx_lit_str(&len,s,&ucs4);
  reg = RegSet_StringN(tstring,len);
  FreeMem(tstring); 
  return reg;
}

static RegSet_T TRANS_RegSet_Cset
                (
                  Styx_T styctx, string s, PT_Term t, c_bool setrange
                )
{ RegSet_T reg, a, b; long len, i; c_bool ucs4;
  wc_string tstring = LIT_styx_lit_str(&len,s,&ucs4);
  if( !setrange || strstr(s,"..") == (c_string)NULL )
    reg = RegSet_CsetN(tstring,len);
  else
  { reg = (RegSet_T)NULL;
    for( i=0; i < len; ++i )
    {
      if( i + 3 < len &&
          tstring[i+1] == WCHAR_LITERAL('.') &&
          tstring[i+2] == WCHAR_LITERAL('.') )
      {
        if (tstring[i] > tstring[i+3])
        { 
          PT_diag_err
          (
            t,styctx->diag,"range ( %ld, %ld ) must be ordered",
            tstring[i], tstring[i+3]
          ); 
          a = RegSet_Range(tstring[i+3], tstring[i]);
        }
        else
        {
          a = RegSet_Range(tstring[i], tstring[i+3]);
        }
        i+= 3;
      }
      else
      {
        a = RegSet_CsetN(&tstring[i],1);
      }
      if( reg == (RegSet_T)NULL ) reg = a;
      else
      {
        b = RegSet_Union(reg,a);
        RegSet_Free(a); RegSet_Free(reg);
        reg = b;
      }
    }
  }
  FreeMem(tstring); return reg;
}

static c_string TRANS_ID_Cset
                (
                  Styx_T styctx, string s, PT_Term t, 
                  c_bool setrange, c_bool quotient
                )
{ Sink snk = Sink_open(); long len, i; c_bool ucs4;
  wc_string tstring = LIT_styx_lit_str(&len,s,&ucs4);
  Sink_printf(snk,"%c",SCN_SEP_TOK_ID_PATTERN);
  if( quotient )
  {
    Sink_printf(snk,"%03d",(unsigned int)s[0]);
  }
  else /* pattern */
  {
    Sink_printf(snk,"000");
  }
  if( ucs4 )
  {
    PT_diag_err(t,styctx->diag,"invalid unicode character in set"); 
  }
  else
  if( !setrange || strstr(s,"..") == (c_string)NULL )
  {
    for( i=0; i < len; ++i )
    {
      Sink_printf(snk,"%03ld",tstring[i]);
    }
  }
  else
  {
    for( i=0; i < len; ++i )
    {
      if( i + 3 < len &&
          tstring[i+1] == WCHAR_LITERAL('.') &&
          tstring[i+2] == WCHAR_LITERAL('.') )
      {
        if (tstring[i] > tstring[i+3])
        { /* error already reported */
          Sink_printf(snk,"%03ld...%03ld",tstring[i+3], tstring[i]);
        }
        else
        {
          Sink_printf(snk,"%03ld...%03ld",tstring[i], tstring[i+3]);
        }
        i+= 3;
      }
      else
      {
        Sink_printf(snk,"%03ld",tstring[i]);
      }
    }
  }
  FreeMem(tstring); 
  return Sink_close(snk);
}

static c_string TRANS_ID_quotient
                (
                  Styx_T styctx, styxExp exp, c_bool setrange
                )
{ styxExp exp1; GLS_Tok tok;
  assert0(styxExp_quot(exp,_,&exp1),"");
  if( styxExp_set(exp1,&tok) )
  {
    return TRANS_ID_Cset(styctx,GLS_Tok_string(tok),tok,C_True,C_True);
  }
  else
  if( styxExp_sequ(exp1,&tok) )
  {
    return TRANS_ID_Cset(styctx,GLS_Tok_string(tok),tok,C_True,C_True);
  }
  else /* error, already reported */
  {
    return StrCopy("");
  }
}

static StdCPtr TRANS_Seq(GLS_Tok seq, c_bool* ucs4)
{ StdCPtr res; wc_string tstring; long len; 
  string s = symbolToString(GLS_Tok_symbol(seq));
  tstring = LIT_styx_lit_str(&len,s,ucs4);
  if( *ucs4 == C_False )
  {
    res = WCToStrCopy(tstring);
    bug0(strlen((string)res) == len,"'\\0' not allowed in keywords");
    FreeMem(tstring);
  }
  else
  {
    bug0(WCStrLen(tstring) == len,"'L\\0' not allowed in keywords");
    res = tstring;
  }
  return res;
}

static RegSet_T trans_Ide(Styx_T styctx, GLS_Tok id)
{
  if (!MAP_defined(styctx->qlx,id))
  { RegSet_T res,old; styxExp exp, lft;
    /* Flag to protect against endless recursion */
    MAP_dfndom(styctx->qlx,id,NULL); 
    styxQlxDfn_defn(MAP_apply(styxQlxDfn,styctx->glo,id),_,_,_,_,_,&exp);
    if( styxExp_quot(exp,&exp,_) )
      /* noop */;
    if( styxExp_dyck(exp,&lft,_,_) )
      res = trans_Exp(styctx,lft);
    else res = trans_Exp(styctx,exp);
    old = MAP_apply(RegSet_T,styctx->qlx,id);
    if (old != (RegSet_T)NULL) RegSet_Free(old);
    MAP_upddom(styctx->qlx,id,res);
  }
  else
  if (MAP_apply(RegSet_T,styctx->qlx,id) == (RegSet_T)NULL)
  {
    PT_diag_err(id,styctx->diag,"recursive definition");
    MAP_upddom(styctx->qlx,id,RegSet_Empty());
  }
  return RegSet_Copy(MAP_apply(RegSet_T,styctx->qlx,id));
}

static RegSet_T trans_Exp(Styx_T styctx, styxExp e)
{ styxExp exp1; styxExp exp2; 
  styxLimit limit; GLS_Tok tok;
  if( styxExp_union(e,&exp1,&exp2) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T b = trans_Exp(styctx,exp2);
    RegSet_T res = RegSet_Union(a,b);
    RegSet_Free(a); RegSet_Free(b);
    return res;
  }
  if( styxExp_diff(e,&exp1,&exp2) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T b = trans_Exp(styctx,exp2);
    RegSet_T res = RegSet_Difference(a,b);
    RegSet_Free(a); RegSet_Free(b);
    return res;
  }
  if( styxExp_conc(e,&exp1,&exp2) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T b = trans_Exp(styctx,exp2);
    RegSet_T res;
    res = RegSet_Concat(a,b);
    RegSet_Free(a); RegSet_Free(b);
    return res;
  }
  if( styxExp_spat(e,&exp1,&tok,&exp2) )
  { RegSet_T a = styxExp_non(exp1) 
                 ? RegSet_Epsilon() : trans_Exp(styctx,exp1);
    RegSet_T b = styxExp_non(exp2) 
                 ? RegSet_Epsilon() : trans_Exp(styctx,exp2);
    RegSet_T c = TRANS_RegSet_Cset
                 (
                   styctx,symbolToString(GLS_Tok_symbol(tok)),tok,C_True
                 );
    RegSet_T d = RegSet_Plus(c);
    RegSet_T e = RegSet_Concat(a,d);
    RegSet_T res = RegSet_Concat(e,b);
    RegSet_Free(a); 
    RegSet_Free(b);
    RegSet_Free(c);
    RegSet_Free(d);
    RegSet_Free(e);
    return res;
  }
  if( styxExp_epat(e,&exp1,&tok,&exp2) )
  { styxExp exp; RegSet_T a, b, c, d, e, res;
    a = styxExp_non(exp1) ? RegSet_Epsilon() : trans_Exp(styctx,exp1);
    b = styxExp_non(exp2) ? RegSet_Epsilon() : trans_Exp(styctx,exp2);
    styxQlxDfn_defn(MAP_apply(styxQlxDfn,styctx->glo,tok),_,_,_,_,_,&exp);
    if( styxExp_quot(exp,&exp,_) )
      /* noop */;
    if( !styxExp_spat(exp,_,&tok,_) )
    { 
      PT_diag_err
      (
        tok,styctx->diag,"'%s' is no start pattern",GLS_Tok_string(tok)
      );
      d = trans_Exp(styctx,exp);
    }
    else
    {
      c = TRANS_RegSet_Cset
          (
            styctx,symbolToString(GLS_Tok_symbol(tok)),tok,C_True
          );
      d = RegSet_Plus(c);
      RegSet_Free(c);
    }
    e = RegSet_Concat(a,d);
    res = RegSet_Concat(e,b);
    RegSet_Free(a); 
    RegSet_Free(b);
    RegSet_Free(d);
    RegSet_Free(e);
    return res;
  }
  if( styxExp_opt(e,&exp1) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T res = RegSet_Option(a);
    RegSet_Free(a);
    return res;
  }
  if( styxExp_star(e,&exp1) || styxExp_plus0(e,&exp1) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T res = RegSet_Star(a);
    RegSet_Free(a);
    return res;
  }
  if( styxExp_plus(e,&exp1) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T res = RegSet_Plus(a);
    RegSet_Free(a);
    return res;
  }
  if( styxExp_plusn(e,&exp1,&limit) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T res = (RegSet_T)NULL;
    styxOptNat optnat;
    int lwr = -1, upr = -1;
    if( styxLimit_ntime(limit,&tok) )
    {
      lwr = atoi(GLS_Tok_string(tok));
      if (lwr < 0) PT_diag_err(tok,styctx->diag,"limit >= 0");
      res = RegSet_Plus_ntimes(a,lwr);
    }
    else
    if( styxLimit_range(limit,&tok,&optnat) )
    { 
      lwr = atoi(GLS_Tok_string(tok));
      if (lwr < 0) PT_diag_err(tok,styctx->diag,"limit >= 0");
      if( styxOptNat_nat(optnat,&tok) )
      {
        upr = atoi(GLS_Tok_string(tok));
        if (upr < 0) PT_diag_err(tok,styctx->diag,"limit >= 0");
        res = RegSet_Plus_range(a,lwr,upr);
      }
      else
      {
        RegSet_T b = RegSet_Plus_ntimes(a,lwr);
        RegSet_T c = RegSet_Star(a);
        res = RegSet_Concat(b,c);
        RegSet_Free(b); RegSet_Free(c);
      }
    }
    RegSet_Free(a);
    return res;
  }
  if( styxExp_range(e,&exp1,&exp2) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T b = trans_Exp(styctx,exp2);
    RegSet_T res;
    wc_char al, bu;
    if (!RegSet_isChar(a)) PT_diag_err(exp1,styctx->diag,"single character");
    if (!RegSet_isChar(b)) PT_diag_err(exp2,styctx->diag,"single character");
    al = RegSet_charVal(a);
    bu = RegSet_charVal(b);
    if (al > bu)
    { wc_char x = al; al = bu; bu = x; 
      PT_diag_err(e,styctx->diag,"range ( %ld, %ld ) must be ordered",bu,al); 
    }
    res = RegSet_Range(al,bu);
    RegSet_Free(a); RegSet_Free(b);
    return res;
  }
  if( styxExp_set(e,&tok) )
    return TRANS_RegSet_Cset(styctx,GLS_Tok_string(tok),tok,C_False);
  if( styxExp_sequ(e,&tok) )
    return TRANS_RegSet_String(GLS_Tok_string(tok));
  if( styxExp_ident(e,&tok) )
    return trans_Ide(styctx,tok);
  C_BUG; return (RegSet_T)NULL;
}

static void collectEofOrFollowTokens
            (
              Styx_T styctx, Styx_T parctx, symbol lansym, styxExp e, 
              MAP(symbol,MAP(GLS_Tok,RegSet_T)) g_ftoks
            )
{ Styx_T rootctx = RootCtx(styctx),
         lanctx  = MAP_apply(Styx_T,rootctx->embed,lansym), ftokctx;
  styxQlxDfn qd = MAP_apply(styxQlxDfn,styctx->grp,lansym);
  styxQlxGrp gs, gd; styxExp exp1, exp2; GLS_Tok tok, slid = {0}, dlid = {0}; 
  MAP(GLS_Tok,RegSet_T) ftoks; 
  assert0
  ( 
    styxQlxDfn_defn(qd,_,_,&gs,_,&gd,_) && 
    styxQlxGrp_grp(gs,&slid) && styxQlxGrp_grp(gd,&dlid),"" 
  );
  ftokctx = ( !strcmp(GLS_Tok_string(dlid),styctx->language) ) 
            ? styctx : lanctx;
  if( MAP_defined(g_ftoks,GLS_Tok_symbol(slid)) )
    ftoks = MAP_apply(MAP(_,_),g_ftoks,GLS_Tok_symbol(slid));
  else
  {
    ftoks = MAP_newMap(styctx->gloty);
    MAP_dfndom(g_ftoks,GLS_Tok_symbol(slid),ftoks);
    MAP_dfndom(ftoks,(GLS_Tok)NULL,(RegSet_T)NULL);
  }
  if( styxExp_conc(e,&exp1,&exp2) )
  { 
    collectEofOrFollowTokens(styctx,parctx,lansym,exp1,g_ftoks);
    collectEofOrFollowTokens(styctx,parctx,lansym,exp2,g_ftoks);
  }
  else
  if( styxExp_ident(e,&tok) )
  { styxQlxGrp gsrc; symbol grpsym;
    if( qlx_pattern(ftokctx,tok) )
      PT_diag_err
      (
        tok,parctx->diag,
        "pattern token '%s' not allowed here", GLS_Tok_string(tok)
      );
    else
    if( ftokctx != lanctx && MAP_defined(lanctx->glo,tok) )
      PT_diag_err
      (
        tok,parctx->diag,
        "identifier '%s' already defined in embedded language '%s'",
        GLS_Tok_string(tok),lanctx->language
      );
    else
    { styxQlxCat c;
      styxQlxDfn_defn(MAP_apply(styxQlxDfn,ftokctx->glo,tok),&c,_,&gsrc,_,_,_);
      if( ftokctx == styctx )
      {
        getGroupInfo(styctx,gsrc,&grpsym,C_False);
        if( grpsym == (symbol)NULL )
          grpsym = InitialGroup;
        if( MAP_defined(styctx->langrp,lansym) &&
            MAP_apply(symbol,styctx->langrp,lansym) != grpsym )
          PT_diag_err
          (
            gsrc,parctx->diag,
            "different embedded language token group '%s'",
            symbolToString(grpsym)
          );
        else 
        { RegSet_T a, b, u;
          if( MAP_defined(ftoks,tok) )
          { 
            a = MAP_apply(RegSet_T,ftoks,tok);
            b = trans_Ide(styctx,tok);
            u = RegSet_Union(a,b);
            MAP_dfndom(ftoks,tok,u);
            RegSet_Free(a); RegSet_Free(b);
          }
          else
          { 
            u = trans_Ide(styctx,tok);
            MAP_dfndom(ftoks,tok,u);
          }
          a = MAP_apply(RegSet_T,ftoks,(GLS_Tok)NULL);
          if( a == (RegSet_T)NULL )
          {
            MAP_upddom(ftoks,(GLS_Tok)NULL,RegSet_Copy(u));
          }
          else
          {
            b = RegSet_Union(a,u);
            MAP_upddom(ftoks,(GLS_Tok)NULL,b);
            RegSet_Free(a); 
          }
        }
      }
      else MAP_ovrdom(ftoks,tok,(RegSet_T)NULL);
      if( ! styxQlxCat_tokC(c) && ! styxQlxCat_comC(c) )
        PT_diag_err(c,parctx->diag,"invalid EOF or follow token category");
    }
  }
  else PT_diag_err(e,parctx->diag,"malformed follow token");
}

static Scn_T trans_Dyck
             (
               Styx_T styctx, GLS_Tok id, RegSet_T left
             )
{ Scn_T dyck; ScnDfn_T scndfn; 
  styxExp exp, pat, rgt; RegSet_T rpat, rrgt;
  c_string sl = Str_printf("%sPrefix",GLS_Tok_string(id)), 
           sp = Str_printf("%sPattern",GLS_Tok_string(id)),  
           sr = Str_printf("%sSuffix",GLS_Tok_string(id)); 
  scndfn = Scn_dfnBegin_reentrant(symbolToString(GLS_Tok_symbol(id)));
  Scn_setMsgFun_reentrant(scndfn,PT_diag_msgFun(styctx->diag));
  Scn_dfnToken_reentrant
  (
    scndfn,sl,(byte)( qlx_ica(styctx,id)?SCN_FLG_IgnoreCase:0 ),left
  );
  styxQlxDfn_defn(MAP_apply(styxQlxDfn,styctx->glo,id),_,_,_,_,_,&exp);
  if( styxExp_quot(exp,&exp,_) )
    /* noop */;
  styxExp_dyck(exp,_,&pat,&rgt);
  rrgt = trans_Exp(styctx,rgt);
  Scn_dfnToken_reentrant
  (
    scndfn,sr,(byte)( qlx_ica(styctx,id)?SCN_FLG_IgnoreCase:0 ),rrgt
  );
  RegSet_Free(rrgt); 
  if( !styxExp_non(pat) )
  {
    rpat = trans_Exp(styctx,pat);
    Scn_dfnToken_reentrant
    (
      scndfn,sp,(byte)( qlx_ica(styctx,id)?SCN_FLG_IgnoreCase:0 ),rpat
    );
    RegSet_Free(rpat);
  }
  FreeMem(sl); FreeMem(sp); FreeMem(sr);
  dyck = Scn_dfnEnd_reentrant(scndfn,styctx->diagnose);
  return dyck;
}

static Scn_T trans_QlxDfns(Styx_T styctx, styxSource s)
{ GLS_Tok id; ScnDfn_T scndfn;
  PT_Itr it; MAPIT itr;
  styctx->qlx = MAP_newMap(styctx->gloty);
  styxSource_root(s,&id,_,_);
  scndfn = Scn_dfnBegin_reentrant(symbolToString(GLS_Tok_symbol(id)));
  Scn_setMsgFun_reentrant(scndfn,PT_diag_msgFun(styctx->diag));
  PT_FORALL(it,s) if (PT_stateIT(it) == PT_PRAE)
  { PT_Term t = PT_termIT(it); styxQlxDfn d; styxQlxGrp gsrc, gdst;
    if( styx_QlxDfn(t,&d) )
    { styxQlxOpt o;
      if( styxQlxDfn_defn(d,_,&o,&gsrc,&id,&gdst,_) )
      {
        if( qlx_usage(styctx,d) == UsageTok ||
            qlx_usage(styctx,d) == UsageIgn ||
            qlx_usage(styctx,d) == UsageCom ||
            qlx_usage(styctx,d) == UsageInd  )
        { RegSet_T a = trans_Ide(styctx,id);
          byte     f = 0;
          if( qlx_usage(styctx,d) == UsageInd )
            f |= SCN_FLG_IndentToken;
          if( !qlx_dyck(styctx,id) )
          { c_string tid = GLS_Tok_string(id);
            if( qlx_pattern(styctx,id) )
            { styxExp exp; GLS_Tok tok;
              styxQlxDfn_defn(MAP_apply(styxQlxDfn,styctx->glo,id),_,_,_,_,_,&exp);
              if( styxExp_quot(exp,&exp,_) )
                /* noop */;
              if( styxExp_spat(exp,_,&tok,_) )
              { c_string pat = TRANS_ID_Cset(styctx,GLS_Tok_string(tok),tok,C_True,C_False),
                         pid = Str_printf("%s%s",tid,pat);
                tid = symbolToString(stringToSymbol(pid));
                FreeMem(pat); FreeMem(pid);
              }
              f |= SCN_FLG_PatternToken;
            }
            if( qlx_quotient(styctx,id) )
            { styxExp exp; c_string pat, pid;
              styxQlxDfn_defn(MAP_apply(styxQlxDfn,styctx->glo,id),_,_,_,_,_,&exp);
              pat = TRANS_ID_quotient(styctx,exp,C_True);
              pid = Str_printf("%s%s",tid,pat);
              tid = symbolToString(stringToSymbol(pid));
              FreeMem(pat); FreeMem(pid);
            }
            Scn_dfnToken_reentrant
            (
              scndfn, tid,
              (byte)( qlx_usage(styctx,d) == UsageIgn
                      ? SCN_FLG_IgnoreToken
                      : f | ( styxQlxOpt_ignca(o) ? SCN_FLG_IgnoreCase : 0)
                    ),
              a
            );
          }
          else
          { Scn_T dyck = trans_Dyck(styctx,id,a);
            c_string tid = GLS_Tok_string(id);
            if( qlx_quotient(styctx,id) )
            { styxExp exp; c_string pat, pid;
              styxQlxDfn_defn(MAP_apply(styxQlxDfn,styctx->glo,id),_,_,_,_,_,&exp);
              pat = TRANS_ID_quotient(styctx,exp,C_True);
              pid = Str_printf("%s%s",tid,pat);
              tid = symbolToString(stringToSymbol(pid));
              FreeMem(pat); FreeMem(pid);
            }
            Scn_dfnDyckToken_reentrant
            (
              scndfn, tid,
              (byte)( qlx_usage(styctx,d) == UsageIgn
                      ? SCN_FLG_IgnoreToken
                      : f | ( styxQlxOpt_ignca(o) ? SCN_FLG_IgnoreCase : 0)
                    ),
              a, dyck
            );
          }
          RegSet_Free(a);
        }
      }
    }
  }
  styctx->Scn = Scn_dfnEnd_reentrant(scndfn,styctx->diagnose);
  if( styctx->root == (Styx_T)NULL )
  {
    MAP_forItr(id,itr,styctx->qlx) 
      RegSet_Free(MAP_apply(RegSet_T,styctx->qlx,id));
    MAP_freeMap(styctx->qlx); styctx->qlx = (MAP(_,_))NULL;
  }
  return styctx->Scn;
}

static void trans_QlxGroupDfns
            (
              Styx_T styctx, ScnDfn_T scndfn, symbol grpsym,
              MAP(GLS_Tok,RegSet_T) ftoks,
              MAP(GLS_Tok,symbol) patids
            )
{ GLS_Tok id; MAPIT itr; RegSet_T a, u, d; symbol rng; byte f;
  MAP_forItrAsg(id,rng,itr,styctx->grptok)
  {
    if( rng == grpsym || 
        ( MAP_defined(styctx->metagrp,rng) &&
          HS_MBR_ELM(grpsym,MAP_apply(SET(symbol),styctx->metagrp,rng)) ) )
    { styxQlxDfn qd; styxQlxGrp gsrc, gdst; styxQlxOpt o; styxExp exp;
      qd = MAP_apply(styxQlxDfn,styctx->glo,id);
      if( styxQlxDfn_defn(qd,_,&o,&gsrc,&id,&gdst,&exp) )
      { 
        if( qlx_usage(styctx,qd) == UsageTok ||
            qlx_usage(styctx,qd) == UsageIgn ||
            qlx_usage(styctx,qd) == UsageCom ||
            qlx_usage(styctx,qd) == UsageInd  )
        { 
          a = trans_Ide(styctx,id);
          u = ( ftoks == (MAP(_,_))NULL )
              ? (RegSet_T)NULL : MAP_apply(RegSet_T,ftoks,(GLS_Tok)NULL); 
          d = ( u == (RegSet_T)NULL ) ? a : RegSet_Difference(a,u);
          f = 0;
          if( qlx_usage(styctx,qd) == UsageInd )
            f |= SCN_FLG_IndentToken;
          if( MAP_defined(styctx->tokflg,id) )
            f |= MAP_apply_small(byte,styctx->tokflg,id);
          if( ftoks != (MAP(_,_))NULL && MAP_defined(ftoks,id) && 
              MAP_apply(RegSet_T,ftoks,id) == (RegSet_T)NULL )
            f |= SCN_FLG_EofToken;
          if( !qlx_dyck(styctx,id) )
          { c_string tid = GLS_Tok_string(id);
            if( qlx_pattern(styctx,id) )
            { GLS_Tok tok;
              if( styxExp_quot(exp,&exp,_) )
                /* noop */;
              if( styxExp_spat(exp,_,&tok,_) )
              { c_string pat = TRANS_ID_Cset(styctx,GLS_Tok_string(tok),tok,C_True,C_False),
                         pid = Str_printf("%s%s",tid,pat);
                symbol   psy = stringToSymbol(pid);
                tid = symbolToString(psy);
                MAP_ovrdom(patids,id,psy);
                FreeMem(pat); FreeMem(pid);
              }
              f |= SCN_FLG_PatternToken;
            }
            if( qlx_quotient(styctx,id) )
            { styxExp exp; c_string pat, pid; symbol psy;
              styxQlxDfn_defn(qd,_,_,_,_,_,&exp);
              pat = TRANS_ID_quotient(styctx,exp,C_True);
              pid = Str_printf("%s%s",tid,pat);
              psy = stringToSymbol(pid);
              tid = symbolToString(psy);
              MAP_ovrdom(patids,id,psy);
              FreeMem(pat); FreeMem(pid);
            }
            Scn_dfnToken_reentrant
            (
              scndfn, tid,
              (byte)( qlx_usage(styctx,qd) == UsageIgn
                      ? SCN_FLG_IgnoreToken
                      : f | ( styxQlxOpt_ignca(o) ? SCN_FLG_IgnoreCase : 0)
                    ),
              d
            );
          }
          else
          { Scn_T dyck = trans_Dyck(styctx,id,a);
            c_string tid = GLS_Tok_string(id);
            if( qlx_quotient(styctx,id) )
            { styxExp exp; c_string pat, pid; symbol psy;
              styxQlxDfn_defn(qd,_,_,_,_,_,&exp);
              pat = TRANS_ID_quotient(styctx,exp,C_True);
              pid = Str_printf("%s%s",tid,pat);
              psy = stringToSymbol(pid);
              tid = symbolToString(psy);
              MAP_ovrdom(patids,id,psy);
              FreeMem(pat); FreeMem(pid);
            }
            Scn_dfnDyckToken_reentrant
            (
              scndfn, tid,
              (byte)( qlx_usage(styctx,qd) == UsageIgn
                      ? SCN_FLG_IgnoreToken
                      : f | ( styxQlxOpt_ignca(o) ? SCN_FLG_IgnoreCase : 0)
                    ),
              a, dyck
            );
          }
          if( d != a ) RegSet_Free(d);
          RegSet_Free(a);
        }
      }
    }
  }
  if( ftoks != (MAP(_,_))NULL )
  {
    MAP_forItrAsg(id,a,itr,ftoks)
    {
      if( a != (RegSet_T)NULL )
      {
        f = SCN_FLG_EofToken | SCN_FLG_SwitchToken;
        Scn_dfnToken_reentrant(scndfn, GLS_Tok_string(id),f,a);
      }
    }
  }
}

static void trans_QlxGroups_prepare
            (
              Styx_T styctx, Styx_T parctx,
              MAP(symbol,MAP(GLS_Tok,RegSet_T)) g_ftoks
            )
{ Styx_T rootctx = RootCtx(styctx), lanctx;
  MAPIT itr; symbol grpsym; 
  styxQlxDfn d; styxExp e;
  MAP_forItrAsg(grpsym,lanctx,itr,rootctx->embed)
  {
    if( MAP_defined(styctx->grp,grpsym) )
    {
      d = MAP_apply(styxQlxDfn,styctx->grp,grpsym);
      styxQlxDfn_defn(d,_,_,_,_,_,&e);
      collectEofOrFollowTokens(styctx,parctx,grpsym,e,g_ftoks);
      trans_QlxGroups_prepare(lanctx,parctx,g_ftoks);
    }
  }
}

static void trans_QlxGroups_aux
            (
              Styx_T styctx, Styx_T parctx, symbol elansym,
              MAP(symbol,MAP(GLS_Tok,RegSet_T)) g_ftoks,
              MAP(symbol,symbol) grpset,
              MAP(GLS_Tok,symbol) patids
            )
{ Styx_T rootctx = RootCtx(styctx), lanctx;
  MAPIT itr, itr2; MAP(GLS_Tok,RegSet_T) ftoks;
  ScnDfn_T scndfn; Scn_T scn; styxQlxDfn d; GLS_Tok id;
  symbol rng, grpsym, lansym; c_string grpid, igrpid, sgrpid; 
  /* initialGroup */
  ftoks = (MAP(_,_))NULL;
  if( parctx == styctx )
    igrpid = StrCopy(symbolToString(InitialGroup));
  else
  {
    igrpid = Str_printf
             (
               "%s_%s",styctx->language,
               symbolToString(elansym)+strlen(styctx->language)
             );
    lansym = stringToSymbol(styctx->language);
    if( MAP_defined(g_ftoks,lansym) )
      ftoks = MAP_apply(MAP(_,_),g_ftoks,lansym);
  }
  if( !MAP_defined(grpset,stringToSymbol(igrpid)) )
  {
    MAP_dfndom(grpset,stringToSymbol(igrpid),InitialGroup);
    scndfn = Scn_dfnBegin_reentrant(igrpid);
    Scn_setMsgFun_reentrant(scndfn,PT_diag_msgFun(parctx->diag));
    trans_QlxGroupDfns(styctx,scndfn,InitialGroup,ftoks,patids);
    MAP_forItrAsg(lansym,rng,itr,styctx->langrp)
    {
      if( rng == InitialGroup )
      {
        lanctx = MAP_apply(Styx_T,rootctx->embed,lansym);
        Scn_dfnToken_reentrant
        (
          scndfn,symbolToString(lansym),SCN_FLG_CfgToken,(RegSet_T)NULL
        );
      }
    }
    scn = Scn_dfnEnd_reentrant(scndfn,parctx->diagnose);
    ScnGrp_dfnScanner(parctx->Scn,scn);
  }
  /* other groups and embedded languages */
  MAP_forItrAsg(grpsym,d,itr,styctx->grp)
  { 
    if( !MAP_defined(rootctx->embed,grpsym) )
    {
      if( grpsym != InitialGroup &&
          !MAP_defined(styctx->metagrp,grpsym) )
      {
        ftoks = (MAP(_,_))NULL;
        if( parctx == styctx )
        {
          grpid = StrCopy(symbolToString(grpsym));
        }
        else
        {
          grpid = Str_printf
                  (
                    "%s__%s",styctx->language,symbolToString(grpsym)
                  );
          lansym = stringToSymbol(styctx->language);
          if( MAP_defined(g_ftoks,lansym) )
            ftoks = MAP_apply(MAP(_,_),g_ftoks,lansym);
        }
        if( !MAP_defined(grpset,stringToSymbol(grpid)) )
        {
          MAP_dfndom(grpset,stringToSymbol(grpid),grpsym);
          scndfn = Scn_dfnBegin_reentrant(grpid);
          Scn_setMsgFun_reentrant(scndfn,PT_diag_msgFun(parctx->diag));
          trans_QlxGroupDfns(styctx,scndfn,grpsym,ftoks,patids);
          if( styxQlxDfn_igrp(d,_) )
            trans_QlxGroupDfns(styctx,scndfn,InitialGroup,ftoks,patids);
          MAP_forItrAsg(lansym,rng,itr2,styctx->langrp)
          {
            if( rng == grpsym )
            {
              lanctx = MAP_apply(Styx_T,rootctx->embed,lansym);
              Scn_dfnToken_reentrant
              (
                scndfn,symbolToString(lansym),SCN_FLG_CfgToken,(RegSet_T)NULL
              );
            }
          }
          scn = Scn_dfnEnd_reentrant(scndfn,parctx->diagnose);
          if( scn != (Scn_T)NULL )
            ScnGrp_dfnScanner(parctx->Scn,scn);
        }
        FreeMem(grpid);
      }
    }
    else
    { 
      lanctx = MAP_apply(Styx_T,rootctx->embed,grpsym);
      trans_QlxGroups_aux(lanctx, parctx, grpsym, g_ftoks, grpset, patids);
    }
  }
  /* set token group switch information */
  MAP_forItrAsg(id,rng,itr,styctx->tokgrp)
  {
    grpsym = MAP_apply(symbol,styctx->grptok,id);
    if( grpsym == InitialGroup )
      grpid = StrCopy(igrpid);
    else
    if( parctx == styctx )
      grpid = StrCopy(symbolToString(grpsym));
    else
      grpid = Str_printf
              (
                "%s__%s",styctx->language,symbolToString(grpsym)
              );
    if( rng == InitialGroup )
      sgrpid = StrCopy(igrpid);
    else
    if( MAP_defined(rootctx->embed,rng) )
    {
      lanctx = MAP_apply(Styx_T,rootctx->embed,rng);
      sgrpid = Str_printf
               (
                 "%s_%s",lanctx->language,
                 symbolToString(rng)+strlen(lanctx->language)
               );
    }
    else
    if( parctx == styctx )
      sgrpid = StrCopy(symbolToString(rng));
    else
      sgrpid = Str_printf
               (
                 "%s__%s",styctx->language,symbolToString(rng)
               );
    if( !MAP_defined(styctx->metagrp,grpsym) )
    {
      if( MAP_defined(patids,id) )
      { symbol psy = MAP_apply(symbol,patids,id);
        ScnGrp_dfnSwitch(parctx->Scn, grpid, symbolToString(psy), sgrpid);
      }
      else
        ScnGrp_dfnSwitch(parctx->Scn, grpid, GLS_Tok_string(id), sgrpid);
    }
    else
    { SET(symbol) grpset = MAP_apply(SET(symbol),styctx->metagrp,grpsym);
      HS_Itr it; symbol elm;
      HS_FORALL(elm,it,grpset)
      {
        if( MAP_defined(patids,id) )
        { symbol psy = MAP_apply(symbol,patids,id);
          ScnGrp_dfnSwitch
          (
            parctx->Scn, symbolToString(elm), symbolToString(psy), sgrpid
          );
        }
        else
          ScnGrp_dfnSwitch
          (
            parctx->Scn, symbolToString(elm), GLS_Tok_string(id), sgrpid
          );
      }
    }
    FreeMem(grpid); FreeMem(sgrpid);
  }
  FreeMem(igrpid);
}

static Scn_T trans_QlxGroups(Styx_T styctx)
{ MAP(symbol,MAP(GLS_Tok,byte)) g_ftoks; 
  MAP(GLS_Tok,RegSet_T) ftoks;
  MAP(GLS_Tok,symbol) patids;
  MAP(symbol,symbol) grpset;
  MAPIT itr1, itr2; RegSet_T reg;
  GLS_Tok tok; symbol lansym; int rc;
  styctx->qlx = MAP_newMap(styctx->gloty);
  g_ftoks = MAP_newPrimMap();
  grpset  = MAP_newPrimMap();
  patids  = MAP_newPrimMap();
  trans_QlxGroups_prepare(styctx,styctx,g_ftoks);
  if( PT_diag_errorCnt(styctx->diag) == 0 )
  {
    styctx->Scn = ScnGrp_dfnBegin(styctx->language);
    trans_QlxGroups_aux(styctx,styctx,(symbol)NULL,g_ftoks,grpset,patids);
    rc = ScnGrp_dfnEnd(styctx->Scn);
    if( rc != 0 )
      PT_diag_warn(styctx->PTree,styctx->diag,"%d unreachable groups",rc);
  }
  MAP_forItrAsg(lansym,ftoks,itr1,g_ftoks)
  {
    MAP_forItrAsg(tok,reg,itr2,ftoks)
    {
      if( reg != (RegSet_T)NULL )
        RegSet_Free(reg);
    }
    MAP_freeMap(ftoks);
  }
  MAP_freeMap(g_ftoks);
  MAP_freeMap(grpset);
  MAP_freeMap(patids);
  if( styctx->root == (Styx_T)NULL )
  {
    MAP_forItr(tok,itr1,styctx->qlx) 
      RegSet_Free(MAP_apply(RegSet_T,styctx->qlx,tok));
    MAP_freeMap(styctx->qlx); styctx->qlx = (MAP(_,_))NULL;
  }
  return styctx->Scn;
}

/* checking keywords */

static void Pass3(Styx_T styctx, styxSource src)
/* keywords */
{ PT_Itr it; GLS_Lst(styxQlxDfn) qlxdfns;
  styxSource_root(src,_,&qlxdfns,_);
  if( !GLS_EMPTY(qlxdfns) )
  { 
    PT_FORALL(it,src) 
    {
      if (PT_stateIT(it) == PT_POST) /* all reserved words */
      { PT_Term trm = PT_termIT(it); styxMbr m; GLS_Tok seq;
        if( styx_Mbr(trm,&m) && styxMbr_tkm(m,&seq) )
        { c_bool u; int t; StdCPtr s = TRANS_Seq(seq,&u);
          /*FIXME: comments are not allowed, too*/
          if( Scn_groups(styctx->Scn) == 0 )
          {
            if( (!u && !(t=Scn_check_Token(styctx->Scn,(string)s)))     || 
                (u && !(t=Scn_check_WCToken(styctx->Scn,(wc_string)s)))  )
              PT_diag_err(seq,styctx->diag,"malformed token");
            else
            if( MAP_count(styctx->indtokkeys) < 3 &&
                ( Scn_tokFlags(styctx->Scn,t) & SCN_FLG_IndentToken ) )
              MAP_ovrdom(styctx->indtokkeys,GLS_Tok_symbol(seq),NULL);
          }
          else
          {
            if( (!u && !(t=Scn_check_GroupToken(styctx->Scn,(string)s)))     || 
                (u && !(t=Scn_check_GroupWCToken(styctx->Scn,(wc_string)s)))  )
              PT_diag_err(seq,styctx->diag,"malformed token");
            else
            { Scn_T grpscn = Scn_group(styctx->Scn,I32_HIGHVAL(t));
              if( MAP_count(styctx->indtokkeys) < 3 &&
                  ( Scn_tokFlags(grpscn,I32_LOWVAL(t)) & 
                      SCN_FLG_IndentToken ) )
                MAP_ovrdom(styctx->indtokkeys,GLS_Tok_symbol(seq),NULL);
            }
          }
          FreeMem(s);
        }
      }
    }
    if( MAP_count(styctx->indtokkeys) >= 3 )
      PT_diag_err(qlxdfns,styctx->diag,"too many (de)indent token keywords");
  }
}

/* Parser Translation */

static string normalKeyword
              (
                Styx_T styctx, GLS_Tok seq, c_bool extkey, c_bool* ucs4
              )
/* normalizes keywords (IgnoreCase) */
{ StdCPtr s = TRANS_Seq(seq,ucs4); long tid; Scn_T grpscn;
  if( extkey == C_True )
  {
    if( *ucs4 == C_False )
      return (string)s;
    else
    { string mbkey;
      bug0((mbkey = GS_ucs4_to_utf8((wc_string)s))!=(string)NULL,"");
      FreeMem(s);
      return mbkey;
    }
  }
  else
  if( *ucs4 == C_False )
  {
    if( Scn_groups(styctx->Scn) == 0 )
    {
      tid = Scn_check_Token(styctx->Scn,(string)s);
      bug1(tid,"token '%s' does not belong to grammar\n",(string)s);
      if( Scn_tokFlags(styctx->Scn,(short)tid) & SCN_FLG_IgnoreCase ) 
        StrToLower((string)s);
    }
    else
    { 
      tid = Scn_check_GroupToken(styctx->Scn,(string)s);
      bug1(tid,"token '%s' does not belong to grammar\n",(string)s);
      grpscn = Scn_group(styctx->Scn,I32_HIGHVAL(tid));  
      if( Scn_tokFlags(grpscn,I32_LOWVAL(tid)) & SCN_FLG_IgnoreCase ) 
        StrToLower((string)s);
    }
    return (string)s;
  }
  else
  { string mbkey, tmp;
    if( Scn_groups(styctx->Scn) == 0 )
      tid = Scn_check_WCToken(styctx->Scn,(wc_string)s);
    else
      tid = Scn_check_GroupWCToken(styctx->Scn,(wc_string)s);
    if( !tid )
    { Sink snk = Sink_open();
      mbkey = GS_ucs4_to_utf8((wc_string)s);
      Sink_puts(snk,"token '");
      if( mbkey != (string)NULL ) Sink_puts_raw(styctx->Scn,mbkey);
      Sink_puts(snk,"' does not belong to grammar\n");
      tmp = Sink_close(snk);
      FreeMem(s); FreeMem(mbkey);
      bug1(False,"%s",tmp);
    }
    else
    {
      if( Scn_groups(styctx->Scn) == 0 )
      {
        if( Scn_tokFlags(styctx->Scn,(short)tid) & SCN_FLG_IgnoreCase ) 
          WCStrToLower((wc_string)s);
      }
      else
      {
        grpscn = Scn_group(styctx->Scn,I32_HIGHVAL(tid));  
        if( Scn_tokFlags(grpscn,I32_LOWVAL(tid)) & SCN_FLG_IgnoreCase ) 
          WCStrToLower((wc_string)s);
      }
      bug0((mbkey = GS_ucs4_to_utf8((wc_string)s))!=(string)NULL,"");
      FreeMem(s);
    }
    return mbkey;
  }
}

static PLR_Cfg trans_Dfns(Styx_T styctx, styxSource src)
{ Styx_T rootctx = RootCtx(styctx);
  MAPTY keyty; MAP(symbol,NULL) key, exttok; /* reserved words */
  PLR_Cfg Cfg; MAPIT itr; PT_Itr it; 
  GLS_Lst(styxQlxDfn) qlxdfns; GLS_Lst(styxDfn) dfns; styxOptCfg optcfg;
  styxDfn pd; styxMbr m; GLS_Tok id, nt, elan, seq;
  c_bool tkother = C_False;
  styxSource_root(src,&id,&qlxdfns,&optcfg);
  styxOptCfg_cfg(optcfg,&dfns);
  Cfg    = PLR_createCfg(symbolToString(GLS_Tok_symbol(id)));
  keyty  = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  key    = MAP_newMap(keyty);
  exttok = MAP_newMap(keyty);
  PT_FORALL(it,src) if( PT_stateIT(it) == PT_PRAE )
  { PT_Term t = PT_termIT(it); styxQlxDfn qd; 
    if( styx_QlxDfn(t,&qd) ) /* Token */
    { styxQlxGrp gsrc, gdst;
      if( styxQlxDfn_defn(qd,_,_,&gsrc,&id,&gdst,_) &&
          ( qlx_usage(styctx,qd) == UsageTok || 
            qlx_usage(styctx,qd) == UsageCom ||
            qlx_usage(styctx,qd) == UsageLan ||
            qlx_usage(styctx,qd) == UsageInd ) )
      {
        if( qlx_usage(styctx,qd) != UsageLan )
          PLR_addTK(Cfg,GLS_Tok_string(id),PLR_TYP_TOK);
        else
        { c_string lantok;
          assert0( styxQlxGrp_grp(gsrc,&elan), "");
          lantok = Str_printf("%s%s",GLS_Tok_string(elan),GLS_Tok_string(id));
          PLR_addTK(Cfg,lantok,PLR_TYP_CFG);
          FreeMem(lantok);
        }
      }
    }
    else
    if( styx_Dfn(t,&pd) ) /* Nonterminal */
    { styxDfnOpt o;
      if( styxDfn_defn(pd,_,&o,&id,_) )
        PLR_addNT(Cfg,GLS_Tok_string(id),styxDfnOpt_errnt(o));
    }
    else
    if( styx_Mbr(t,&m) ) /* Keyword */
    { 
      if( styxMbr_tkm(m,&seq) )
      { c_bool ucs4; 
        string s = normalKeyword(styctx,seq,GLS_EMPTY(qlxdfns),&ucs4); 
        symbol keyword = stringToSymbol(s);
        FreeMem(s);
        if( ! MAP_defined(key,keyword) )
        {
          MAP_dfndom(key,keyword,NULL);
          PLR_addTK(Cfg,symbolToString(keyword),(ucs4?PLR_TYP_WKY:PLR_TYP_KEY));
        }
      }
      else
      if( GLS_EMPTY(qlxdfns) && styxMbr_ntm(m,&id) )
      {
        if (!MAP_defined(styctx->glo,id) &&
            !MAP_defined(rootctx->embed,GLS_Tok_symbol(id)))
        {
          if( ! MAP_defined(exttok,GLS_Tok_symbol(id)) )
          {
            MAP_dfndom(exttok,GLS_Tok_symbol(id),NULL);
            PLR_addTK(Cfg,GLS_Tok_string(id),PLR_TYP_TOK);
          }
        }
      }     
      else
      if( styxMbr_else(m) )
      {
        tkother = C_True;
      }     
    }
  }
  if( tkother )
  {
    PLR_addTK(Cfg,PLR_TOK_Other,PLR_TYP_TOK);
  }
  MAP_freeMap( key );
  MAP_freeMap( exttok );
  MAP_freeTyp( keyty );

  PLR_endSD(Cfg); /* Sorting Token & Nonterminals */

  MAP_forItr(id,itr,styctx->glo)
    if( styx_QlxDfn(MAP_apply(PT_Term,styctx->glo,id),_) && 
        qlx_usage(styctx,id) == UsageCom ) /* Special Token */
      PLR_addST(Cfg,GLS_Tok_string(id));
  PT_FORALL(it,dfns) if( PT_stateIT(it) == PT_PRAE )
  { PT_Term t = PT_termIT(it); styxPrd p;
    if( styx_Dfn(t,&pd) ) /* Startsymbol */
    { styxCat c;
      if( styxDfn_defn(pd,&c,_,&nt,_) && styxCat_bgnC(c) )
        PLR_addSN(Cfg,GLS_Tok_string(nt));
    }
    else
    if( styx_Prd(t,&p) ) /* Production */
    { styxLay lay; GLS_Tok pid;
      if( styxPrd_prod(p,&lay,&pid,_) )
      {
        if( styxLay_dft(lay) )
          PLR_addPR
          (
            Cfg,GLS_Tok_string(pid), PLR_PRD_DFT,GLS_Tok_string(nt)
          );
        else
        if( styxLay_rec(lay) )
          PLR_addPR
          (
            Cfg,GLS_Tok_string(pid), PLR_PRD_REC,GLS_Tok_string(nt)
          );
        else
        if( styxLay_grp(lay) )
          PLR_addPR
          (
            Cfg,GLS_Tok_string(pid), PLR_PRD_GRP,GLS_Tok_string(nt)
          );
      }
    }
    else
    if( styx_Mbr(t,&m) ) /* Production Symbol */
    { long r = PT_row(m), c = PT_col(m);
      if( styxMbr_tkm(m,&seq) )
      { c_bool ucs4; 
        string s = normalKeyword(styctx,seq,GLS_EMPTY(qlxdfns),&ucs4);
        PLR_addPK(Cfg,s,r,c);
        FreeMem(s);
      }
      else
      if( styxMbr_ntm(m,&id) )
      { PT_Term t = getDfn(styctx,id,!GLS_EMPTY(qlxdfns));
        r = PT_row(id);
        c = PT_col(id);
        if( t == (PT_Term)NULL || styx_QlxDfn(t,_) )
        {
          PLR_addPT(Cfg,GLS_Tok_string(id),r,c);
          HS_SET_ELM(GLS_Tok_symbol(id),styctx->tkset);
        }
        else
        if( styx_Dfn(t,_) )
          PLR_addPN(Cfg,GLS_Tok_string(id),r,c);
      }
      else
      if( styxMbr_else(m) )
      {
        PLR_addPT(Cfg,PLR_TOK_Other,r,c);
        HS_SET_ELM(stringToSymbol(PLR_TOK_Other),styctx->tkset);
      }
    }
  }
  return Cfg;
}

static void STYX_compile_free(Styx_T styctx, int rc)
{
  if( styctx->qlx != (MAP(_,_))NULL ) 
  { MAPIT itr; RegSet_T rng; symbol dom;
    MAP_forItrAsg(dom,rng,itr,styctx->qlx) 
      RegSet_Free(rng);
    MAP_freeMap(styctx->qlx); styctx->qlx = (MAP(_,_))NULL;
  }
  if( styctx->glo != (MAP(_,_))NULL )
  {
    MAP_freeMap(styctx->glo); styctx->glo = (MAP(_,_))NULL;
  }
  if( styctx->grp != (MAP(_,_))NULL ) 
  {
    MAP_freeMap(styctx->grp); styctx->grp = (MAP(_,_))NULL;
  }
  if( styctx->grptok != (MAP(_,_))NULL ) 
  { 
    MAP_freeMap(styctx->grptok); styctx->grptok = (MAP(_,_))NULL;
  }
  if( styctx->langrp != (MAP(_,_))NULL ) 
  { 
    MAP_freeMap(styctx->langrp); styctx->langrp = (MAP(_,_))NULL;
  }
  if( styctx->tokgrp != (MAP(_,_))NULL ) 
  { 
    MAP_freeMap(styctx->tokgrp); styctx->tokgrp = (MAP(_,_))NULL;
  }
  if( styctx->tokflg != (MAP(_,_))NULL ) 
  { 
    MAP_freeMap(styctx->tokflg); styctx->tokflg = (MAP(_,_))NULL;
  }
  if( rc != 0 && styctx->tkset != (HS_Set)NULL )
  {
    HS_DROP_SET(styctx->tkset); styctx->tkset = (HS_Set)NULL;
  }
  if( styctx->indtokkeys != (MAP(symbol,_))NULL )
  {
    MAP_freeMap(styctx->indtokkeys); styctx->indtokkeys = (MAP(symbol,_))NULL;
  }
  if( styctx->gloty != (MAPTY)NULL ) 
  {
    MAP_freeTyp(styctx->gloty); styctx->gloty = (MAPTY)NULL;
  }
}

static int STYX_compile(Styx_T styctx, Scn_Stream cStream, c_string incpath)
{ PLR_Cfg Cfg; PT_Cfg PCfg;
  MAP(long,symbol) pPreParMap; SPP_T pPP;
  styxSource s = {0}; styxOptCfg optcfg; GLS_Lst(styxDfn) dfns; 
  GLS_Lst(styxQlxDfn) qlxdfns = {0}; GLS_Tok id; 
  void (*prMsg)(c_string msg) = PT_diag_msgFun(styctx->diag);
  MAPIT itr; Styx_T rng; symbol dom;
  long indcnt = 0; int rc = 0, tblcnt = 2;
  if (styctx->verbose) (*prMsg)("parsing ...\n");
  STYX_reset(styctx);
  styctx->incpath = stringToSymbol(incpath);
  pPreParMap = MAP_newPrimMap();
  MAP_dfndom(pPreParMap,SPP_INC_PATH,styctx->incpath);
  pPP = SPP_init_reentrant(pPreParMap);
  Stream_premac_set(cStream, SPP_premac);
  Stream_add_ctxval(cStream,SPP_premac,pPP);
  PCfg          = PT_init(styctx->styapp->PTab,cStream);
  styctx->PTree = (styx)PT_PARSE(PCfg,"Source");
  PT_diag_setErrorCnt(styctx->diag,PT_synErrorCnt(PCfg));
  PT_quit(PCfg);
  SPP_quit_reentrant(pPP);
  MAP_freeMap(pPreParMap);
  if (styctx->verbose) (*prMsg)("done parsing\n");
  if( (styctx->errorCnt=PT_diag_errorCnt(styctx->diag)) == 0 )
  {
    styx_Start_0(styctx->PTree,&s);
    styxSource_root(s,&id,&qlxdfns,&optcfg);
    if( strcmp(GLS_Tok_string(id),styctx->language) != 0 )
      PT_diag_err
      (
        id,styctx->diag,"language identifier und file name are different"
      );
  
    styctx->gloty      = MAP_newTyp
                         (
                           primCopy,primFree,PT_equal,PT_hash, 
                           primCopy,primFree
                         );
    styctx->glo        = MAP_newMap(styctx->gloty);
    styctx->tkset      = HS_CREATE_ADTSET(symbol);
    styctx->indtokkeys = MAP_newPrimMap();
    styctx->grp        = MAP_newPrimMap();
    styctx->grptok     = MAP_newMap(styctx->gloty);
    styctx->langrp     = MAP_newPrimMap();
    styctx->tokgrp     = MAP_newMap(styctx->gloty);
    styctx->metagrp    = MAP_newPrimMap();
    styctx->tokflg     = MAP_newMap(styctx->gloty);
    if( styctx->root == (Styx_T)NULL )
      styctx->embed = MAP_newPrimMap();

    if (styctx->verbose) (*prMsg)("Pass 1\n"); 
    Pass1(styctx,s); /* Pass 1: uniqueness */
    if (styctx->verbose) (*prMsg)("Pass 2\n"); 
    Pass2(styctx,s); /* Pass 2: references */
  }
  if( (styctx->errorCnt=PT_diag_errorCnt(styctx->diag)) > 0 )
  {
    PT_diag_msg
    (
      (PT_Term)NULL,styctx->diag,"Totally %d errors.\n",
      PT_diag_errorCnt(styctx->diag)
    ); 
  }
  else
  {
    /* QLX translator */

    if( !GLS_EMPTY(qlxdfns) )
    {
      if (styctx->verbose) (*prMsg)("begin scanner creation\n");
      if( MAP_count(styctx->grp) <= 1 )
        styctx->Scn = trans_QlxDfns(styctx,s);
      else
        styctx->Scn = trans_QlxGroups(styctx);
      if (styctx->verbose) (*prMsg)("end scanner creation\n");
    }
    else 
    {
      --tblcnt; (*prMsg)("Note: No scanner specified.\n");
    }
    if( GLS_EMPTY(qlxdfns) || styctx->Scn != (Scn_T)NULL )
    {
      if (styctx->verbose) (*prMsg)("Pass 3\n"); 
      Pass3(styctx,s); /* Pass 3: keyword */
      if( styctx->root == (Styx_T)NULL    && 
          styctx->embed != (MAP(_,_))NULL && 
          (styctx->errorCnt=PT_diag_errorCnt(styctx->diag)) == 0 )
      {
        MAP_forItrAsg(dom,rng,itr,styctx->embed)
        {
          indcnt += MAP_count(rng->indtokkeys);
        }
        if( indcnt >= 3 )
          PT_diag_err(s,styctx->diag,"too many (de)indent token keywords");
      }
      if( (styctx->errorCnt=PT_diag_errorCnt(styctx->diag)) == 0 )
      {
        /* CFG translator */
  
        if( styxOptCfg_cfg(optcfg,&dfns) && ! GLS_EMPTY(dfns) )
        {
          styctx->PTab = PLR_createTab
                         (
                           (Cfg=trans_Dfns(styctx,s)),
                           styctx->verbose,styctx->diagnose
                         );
          PLR_delCfg(Cfg);
  
          if( styctx->PTab != (PLR_Tab)NULL )
          {
            if( ! acfg_init(styctx->PTab,
                            &styctx->aPol,&styctx->aNtm,&styctx->aPrd,True) )
            {
              acfg_quit(styctx->PTab,styctx->aPol,styctx->aNtm,styctx->aPrd);
              PLR_delTab(styctx->PTab); styctx->PTab = (PLR_Tab)NULL;
            }
          }
          else (*prMsg)("Parse table creation failed.\n");
          if( styctx->PTab == (PLR_Tab)NULL && styctx->Scn != (Scn_T)NULL )
          {
            Scn_free(styctx->Scn); styctx->Scn = (Scn_T)NULL;
          }
        }
        else 
        {
          --tblcnt; (*prMsg)("Note: No parser specified.\n");
        }
      }
      else
      if( styctx->Scn != (Scn_T)NULL )
      {
        Scn_free(styctx->Scn); styctx->Scn = (Scn_T)NULL;
      }
    }
    else 
    {
      (*prMsg)("Scan table creation failed.\n");
    }
  }
  if( styctx->errorCnt > 0 )
    rc = styctx->errorCnt;
  else
  if( tblcnt > 0 && styctx->Scn == (Scn_T)NULL && 
      styctx->PTab == (PLR_Tab)NULL )
    rc = -1;
  if( styctx->root == (Styx_T)NULL ) 
  {
    if( styctx->embed != (MAP(_,_))NULL ) 
    { 
      MAP_forItrAsg(dom,rng,itr,styctx->embed)
      {
        STYX_compile_free(rng,rc);
      }
    }
    STYX_compile_free(styctx,rc);
  }
  return rc;
}

int STYX_compile_file(Styx_T styctx, c_string stydfn, c_string incpath)
/* compiles STYX definition in file 'stydfn' and
   creates the corresponding scan & parse table;
   uses 'incpath' as include path
   RC >  0: number of syntax and semantic errors
   RC = -1: table creation failed
   RC =  0: successful compilation
*/
{ Scn_Stream cStream; int rc = 0;
  BUG_NULL(styctx);
  cStream = Stream_file(styctx->styapp->Scn,"",stydfn,"");
  rc = STYX_compile(styctx,cStream,incpath);
  Stream_free(cStream);
  return rc;
}

int STYX_compile_string(Styx_T styctx, c_string stydfn, c_string incpath)
/* compiles STYX definition in string 'stydfn' and
   creates the corresponding scan & parse table;
   uses 'incpath' as include path
   RC >  0: number of syntax and semantic errors
   RC = -1: table creation failed
   RC =  0: successful compilation
*/
{ Scn_Stream cStream; int rc = 0;
  BUG_NULL(styctx);
  cStream = Stream_string(styctx->styapp->Scn,stydfn);
  rc = STYX_compile(styctx,cStream,incpath);
  Stream_free(cStream);
  return rc;
}

/*I----------------------- Table image & source generation ------------------- */

void STYX_createTabIMG(Styx_T styctx, c_string Environ)
/* unloads scan & parse table to images 
   [$'Environ'/]<Language>.lim 
   [$'Environ'/]<Language>.pim (optional)
*/
{
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0,
    "image creation failed"
  );
  if( styctx->Scn != (Scn_T)NULL )
    Scn_put(Environ,styctx->Scn);
  if( styctx->PTab != (PLR_Tab)NULL &&
      (styctx->conflicts || PLR_conflictCnt(styctx->PTab) == 0 ) )
    PLR_putTab(Environ,styctx->PTab);
}

void STYX_appendTabIMG(Styx_T styctx, BinImg_T lim, BinImg_T pim)
/* unloads scan & parse table to images 'lim' and 
   optional 'pim'
*/
{
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0,
    "image creation failed"
  );
  if( styctx->Scn != (Scn_T)NULL && lim != (BinImg_T)NULL )
    Scn_fput_bin(lim,styctx->Scn);
  if( styctx->PTab != (PLR_Tab)NULL && pim != (BinImg_T)NULL &&
      (styctx->conflicts || PLR_conflictCnt(styctx->PTab) == 0 ) )
    PLR_fputTab_bin(pim,styctx->PTab);
}

void STYX_createTabC(Styx_T styctx, c_string Environ)
/* creates scan & parse table sources 
   [$'Environ'/]<Language>_lim.c 
   [$'Environ'/]<Language>_pim.c (optional)
*/
{ c_bool shortform = C_False;
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0,
    "image creation failed"
  );
  if( strcmp(styctx->lprefix,styctx->language) )
    shortform = C_True;
  if( styctx->Scn != (Scn_T)NULL )
    Scn_C_Modul(Environ,styctx->Scn,shortform);
  if( styctx->PTab != (PLR_Tab)NULL &&
      (styctx->conflicts || PLR_conflictCnt(styctx->PTab) == 0 ) )
    PLR_CTab_Modul(Environ,styctx->PTab,shortform);
}

void STYX_exportTab(Styx_T styctx, c_string Environ, c_string Template)
/* exports scan table definition, optional based on a given template definition 
   [$'Environ'/]<Language>.ltbl
   [$'Environ'/]<Language>.ptbl (optional)
*/
{
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0,
    "export failed"
  );
  if( styctx->Scn != (Scn_T)NULL )
    Scn_Src_Modul(Environ,styctx->Scn,Template);
  if( styctx->PTab != (PLR_Tab)NULL &&
      (styctx->conflicts || PLR_conflictCnt(styctx->PTab) == 0 ) )
    PLR_Src_Modul(Environ,styctx->PTab,Template);
}

void STYX_appendTabC
     (
       Styx_T styctx, 
       FILE* lfp, c_string lfid, FILE* pfp, c_string pfid
     )
/* appends scan & parse table sources to files 'lfp' and 
   optional 'pfp';
   'lfid', 'pfid' --> optional file names
*/
{ 
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0,
    "image creation failed"
  );
  if( styctx->Scn != (Scn_T)NULL && lfp != (FILE*)NULL )
    Scn_C_Source(lfp,lfid,styctx->Scn);
  if( styctx->PTab != (PLR_Tab)NULL && pfp != (FILE*)NULL &&
      (styctx->conflicts || PLR_conflictCnt(styctx->PTab) == 0 ) )
    PLR_CTab_Source(pfp,pfid,styctx->PTab);
}

/* --------------------- Interface generation (auxiliary) -------------------- */

static void nChar(Styx_T styctx, int n, char c)
/* n * c */
{ int i; FILE* f = styctx->SysOut;
  for( i = 0; i < n; i++) fprintf(f,"%c",c);
}

static void fileComment(Styx_T styctx, string filename, string s)
/* layout a file comment */
{ FILE*    f  = styctx->SysOut;
  c_string cp = styctx->cprefix, cs = styctx->csuffix;
  fprintf(f,"%s ",cp); nChar(styctx,LineLen-6,'-'); fprintf(f," %s",cs); 
  FNL(f);
  fprintf(f,"%s ",cp); nChar(styctx,LineLen-6,' '); fprintf(f," %s",cs); 
  FNL(f);
  fprintf(f,"%s [%s]",cp,filename);
  nChar(styctx,(LineLen-6-strlen(s)+0)/2-2-strlen(filename),' ');
  fprintf(f,"%s",s);
  nChar(styctx,(LineLen-6-strlen(s)+1)/2,' ');
  fprintf(f," %s",cs); 
  FNL(f);
  fprintf(f,"%s ",cp); nChar(styctx,LineLen-6,' '); fprintf(f," %s",cs); 
  FNL(f);
  fprintf(f,"%s ",cp); nChar(styctx,LineLen-6,'-'); fprintf(f," %s",cs); 
  FNL(f); FNL(f);
}

static void sectionComment(Styx_T styctx, string s)
/* layout a section comment */
{ FILE*    f  = styctx->SysOut;
  c_string cp = styctx->cprefix, cs = styctx->csuffix;
  FNL(f);
  fprintf(f,"%sI",cp);
  nChar(styctx,(LineLen-6-strlen(s)-2+0)/2,'-');
  fprintf(f," %s ",s);
  nChar(styctx,(LineLen-6-strlen(s)-2+1)/2,'-');
  fprintf(f," %s",cs); 
  FNL(f);
}

/*I--------------------- Abstract interface generation ----------------------- */

static void genNtmMbrComment(Styx_T styctx, int clsidx)
/* generates nonterminal member comment */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  if( styctx->aPol[clsidx] == -1 )
    fprintf(f,"%s",PLR_symName(PTab,PLR_ntClass(PTab,clsidx)));
  else
  {
    if( styctx->aPol[clsidx] >= 0 )
      genNtmMbrComment(styctx,styctx->aPol[clsidx]); 
    else
    {
      if( ABS(styctx->aPol[clsidx]+2) == PLR_tokenCnt(PTab) )
        fprintf(f,"GLS_Tok");
      else
      {
        fprintf(f,"%s",PLR_symName(PTab,ABS(styctx->aPol[clsidx]+2))); 
      }
    }
    fprintf(f,"*");
  }
}

static void genProdComment(Styx_T styctx, int i, int indent)
/* generates production comment */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  int     cnt  = PLR_prodSymCnt(PTab,i), j; 
  c_bool  flg  = C_True;
  if( indent ) fprintf(f,"  %*s",indent,"");
  fprintf(f,"%s",PLR_prodName(PTab,i));
  for( j=0; j < cnt; ++j )
  { int sym = PLR_prodSymbol(PTab,i,j), typ = PLR_symType(PTab,sym);
    if( CFG_TOK_NTM(typ) )
    {
      if( flg == True ) { flg = False; fprintf(f,"("); }
      else fprintf(f,", ");
      if( CFG_TOK(typ) ) fprintf(f,"%s",PLR_symName(PTab,sym));
      if( CFG_NTM(typ) )
        genNtmMbrComment(styctx,PLR_ntClassId(PTab,sym-PLR_tokenCnt(PTab)));
    }
  }
  fprintf(f,"%s", ( flg ) ? "" : ")");
}

static void genTokenCom(Styx_T styctx)
/* generates comment for tokens */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  int     cnt  = PLR_tokenCnt(PTab), i; 
  c_bool  flg  = C_True;
  fprintf(f,"TOKENS"); FNL(f);
  FNL(f);
  fprintf(f,"  ");
  for( i=0; i < cnt; ++i ) 
  {
    if( CFG_TOK(PLR_symType(PTab,i)) &&
        HS_MBR_ELM(stringToSymbol(PLR_symName(PTab,i)),styctx->tkset) )
    {
      if( flg == True ) flg = False;
      else              fprintf(f,", ");
      fprintf(f,"%s",PLR_symName(PTab,i));
    }
  }
  FNL(f);
}

static void genTypesCom(Styx_T styctx, string filename)
/* generates comment for types */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  int     scnt = PLR_startCnt(PTab), ncnt = PLR_nontermCnt(PTab), i;
  styctx->maxlen = MAX(styctx->maxlen,strlen(PLR_language(PTab)));
  for (i = 0; i < PLR_nontermCnt(PTab); i++) if (PLR_ntClassId(PTab,i) == i)
      styctx->maxlen = MAX
                       (
                         styctx->maxlen,
                           strlen(PLR_symName(PTab,PLR_ntClass(PTab,i)))
                         + strlen(styctx->lprefix)
                       );
  fileComment(styctx,filename,"Abstract Grammar");
  fprintf(f,"LANGUAGE %s",PLR_language(PTab)); FNL(f);
  FNL(f);
  genTokenCom(styctx);
  FNL(f);
  fprintf(f,"TYPES"); FNL(f);
  FNL(f);
  fprintf(f,"  %-*s = ",styctx->maxlen,PLR_language(PTab));
  /* 'start' productions */
  for (i = 0; i < scnt; i++) 
  {
    genProdComment(styctx,PLR_prodCnt(PTab)-scnt+i,(!i)?0:styctx->maxlen+3);
    if( i < scnt - 1 ) fprintf(f,";"); FNL(f);
  }
  /* normal productions */
  for (i = 0; i < ncnt; i++) 
    if (PLR_ntClassId(PTab,i) == i && 
        styctx->aPol[i] == -1 && ! HS_EMPTY_SET(styctx->aPrd[i]))
    { HS_Itr itr; HS_Elm elm; int cnt = 0, indent = 0;
      FNL(f);
      fprintf
      (
        f,"  %-*s = ",styctx->maxlen,PLR_symName(PTab,PLR_ntClass(PTab,i))
      );
      /* Here is some stuff to report class equivalence.  */
      /* We dont use it, but must eventually activate it. */
      /*
      { int j; int ntcls = PLR_ntClass(PTab,i);
        for (j = 0; j < ncnt; j++) 
        { int nt = PLR_NTI_TO_NTS(PTab,j), equiv = PLR_NTS_TO_NTC(PTab,nt);
          if( ntcls == equiv ) fprintf(f," %s",PLR_symName(PTab,nt));
        }
      }
      */
      HS_FORALL(elm,itr,styctx->aPrd[i]) 
      {
        genProdComment(styctx,intCAST(elm),indent);
        ++cnt; if( cnt < HS_CARD(styctx->aPrd[i]) ) fprintf(f,";"); FNL(f);
        if( ! indent ) indent = styctx->maxlen + 3;
      }
    }
  FNL(f);
/*
  fprintf(f,"  X*%*s = nil; cons(X,X*)",MAX(0,styctx->maxlen-2),""); FNL(f);
  FNL(f); 
*/
}

void STYX_createABS(Styx_T styctx, c_string Environ)
/* create abstract interface [$'Environ'/]<Language>.abs */
{ string filename = (c_string)NULL;
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0 && 
    styctx->PTab != (PLR_Tab)NULL,
    "missing parse table"
  );
  styctx->SysOut  = OpenPath(Environ,PLR_language(styctx->PTab),".abs","wt");
  styctx->cprefix = StrCopy("/*");
  styctx->csuffix = StrCopy("*/");
  filename        = Str_printf("%s.abs",PLR_language(styctx->PTab));
  genTypesCom(styctx,filename);
  fclose(styctx->SysOut); styctx->SysOut = (FILE*)NULL;
  FreeMem(styctx->cprefix); styctx->cprefix = (c_string)NULL;
  FreeMem(styctx->csuffix); styctx->csuffix = (c_string)NULL;
  FreeMem(filename);
}

void STYX_appendABS(Styx_T styctx, FILE* fp, c_string fid)
/* append abstract interface to file 'fp'; 
   'fid' --> optional file name
*/
{ 
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0 && 
    styctx->PTab != (PLR_Tab)NULL && fp != (FILE*)NULL,
    "missing parse table or file"
  );
  styctx->SysOut  = fp;
  styctx->cprefix = StrCopy("/*");
  styctx->csuffix = StrCopy("*/");
  genTypesCom(styctx,fid);
  styctx->SysOut = (FILE*)NULL;
  FreeMem(styctx->cprefix); styctx->cprefix = (c_string)NULL;
  FreeMem(styctx->csuffix); styctx->csuffix = (c_string)NULL;
}

/*I--------------------- C interface generation ------------------------------ */

static void genCNtmArgTyp(Styx_T styctx, int clsidx)
/* generates nonterminal argument type name */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  if( styctx->aPol[clsidx] == -1 )
    fprintf
    (
      f,"%s%s",styctx->lprefix,PLR_symName(PTab,PLR_ntClass(PTab,clsidx))
    );
  else
  {
    fprintf(f,"GLS_Lst(");
    if( styctx->aPol[clsidx] >= 0 )
      genCNtmArgTyp(styctx,styctx->aPol[clsidx]);
    else fprintf(f,"GLS_Tok");
    fprintf(f,")");
  }
}

static void genCProd(Styx_T styctx, int i)
/* generates for Production i */
{ FILE*   f      = styctx->SysOut;
  PLR_Tab PTab   = styctx->PTab;
  int     nt     = PLR_prodNonTerm(PTab,i), 
          clsidx = PLR_ntClassId(PTab,nt-PLR_tokenCnt(PTab)), 
          ntcls  = PLR_ntClass(PTab,clsidx), 
          num    = 0, cnt, len, j;
  c_bool  flg    = True;
  HS_Itr  itr; HS_Elm elm; 
  len =   7 + strlen(styctx->lprefix) + strlen(PLR_symName(PTab,ntcls))
        + 1 + strlen(PLR_prodName(PTab,i)) + 1;
  FNL(f);
  fprintf
  (
    f,"c_bool %s%s_%s(%s%s x", 
    styctx->lprefix, PLR_symName(PTab,ntcls), PLR_prodName(PTab,i), 
    styctx->lprefix, PLR_symName(PTab,ntcls)
  );
  cnt = PLR_prodSymCnt(PTab,i);
  for( j=0; j < cnt; ++j )
  { int sym = PLR_prodSymbol(PTab,i,j), typ = PLR_symType(PTab,sym); 
    if( CFG_TOK(typ) ) 
    {
      if( num > 1 && ! ( num % 2 ) )
        fprintf(f,",\n%*sGLS_Tok* x%d",len,"",++num);
      else
        fprintf(f,", GLS_Tok* x%d",++num);
    }
    if( CFG_NTM(typ) )
    { 
      if( num > 1 && ! ( num % 2 ) ) fprintf(f,",\n%*s",len,"");
      else                           fprintf(f,", ");
      genCNtmArgTyp(styctx,PLR_ntClassId(PTab,sym-PLR_tokenCnt(PTab)));
      fprintf(f,"* x%d",++num);
    }
  }
  fprintf(f,")"); 
  FNL(f); fprintf(f,"{"); 
  FNL(f); fprintf(f,"  assert0( ");
  HS_FORALL(elm,itr,styctx->aNtm[clsidx])
  {
    if( flg )
    {
      flg = False;
    }
    else
    {
      FNL(f); fprintf(f,"        ||");
    }
    if (styctx->genabs)
      fprintf(f," PT_Abs_nonterm(x) == CfgSyms[%d]",intCAST(elm));
    else
      fprintf(f," PT_THISNTM((PT_Term)x, CfgSyms[%d])",intCAST(elm));
  }
  fprintf(f,", \"%s expected\" );",PLR_symName(PTab,ntcls));
  FNL(f);
  if (styctx->genabs)
    fprintf
    (
      f,"  if( PT_Abs_product(x) != PrdSyms[%d] ) return False;",i
    );
  else
    fprintf
    (
      f,"  if( ! PT_THISPRD((PT_Term)x, PrdSyms[%d]) ) return False;",i
    );
  if( num )
  { bool xflg = False;
    if( !styctx->genabs )
    {
      FNL(f); fprintf(f,"  { PT_Term y;"); 
    }
XARON_STEP:
    if( !styctx->genabs )
    {
      if( ! xflg )
      {
        FNL(f); fprintf(f,"    if( ! PT_isXaron(x) )"); 
      }
      else
      {
        FNL(f); fprintf(f,"    else"); 
      }
      FNL(f); fprintf(f,"    {"); 
    }
    for( num = 0, j=0; j < cnt; ++j )
    { int sym = PLR_prodSymbol(PTab,i,j), typ = PLR_symType(PTab,sym);
      if( CFG_TOK_NTM(typ) )
      {
        FNL(f);
        if (!styctx->genabs)
        {
          if( ! xflg )
            fprintf
            (
              f,"      x = (%s%s)GLS_keycom_Skip(PT_%s(x));",
              styctx->lprefix, PLR_symName(PTab,ntcls),
              num ? "next" : "parts"
            );
          else
          {
            fprintf
            (
              f,"      x = XGLS_keycom_Skip(%s(x));",
              num ? "rst" : "XPT_parts"
            );
            fprintf
            (
              f," y = fst(%s%s,x);",styctx->lprefix,PLR_symName(PTab,ntcls)
            );
          }
          FNL(f);
        }
        ++num;
        fprintf
        (
          f, "  %sif( (%sCPtr)x%d != (%sCPtr)NULL )",
          styctx->genabs?"":"    ", 
          styctx->genabs?"Huge":"Std", num, styctx->genabs?"Huge":"Std"
        );
        if (!styctx->genabs) { FNL(f); fprintf(f,"       "); }
        if( CFG_TOK(typ) )
          fprintf(f," *x%d = (GLS_Tok)", num);
        else
        {
          fprintf(f," *x%d = (", num);
          genCNtmArgTyp(styctx,PLR_ntClassId(PTab,sym-PLR_tokenCnt(PTab)));
          fprintf(f,")");
        }
        if (styctx->genabs)
          fprintf(f,"PT_Abs_part(x,%d);",num-1);
        else
          fprintf(f,"GLS_ign_Skip(%s);",( ! xflg ) ? "x" : "y");
      }
    }
    if( !styctx->genabs )
    {
      FNL(f); fprintf(f,"    }"); 
      xflg = ( ! xflg ) ? True : False;
      if( xflg ) goto XARON_STEP;
      FNL(f); fprintf(f,"  }"); 
    }
  }
  FNL(f); fprintf(f,"  return True;");
  FNL(f); fprintf(f,"}"); 
  FNL(f);
}

static void genCNonTerm(Styx_T styctx, int i)
/* generates for nonterminal class i */
{ int nt = PLR_ntClass(styctx->PTab,i); HS_Elm elm; HS_Itr itr;
  sectionComment(styctx,PLR_symName(styctx->PTab,nt));
  HS_FORALL(elm,itr,styctx->aPrd[i]) genCProd(styctx,intCAST(elm));
}

static void genCTermTyp(Styx_T styctx, int i)
/* generates for terminal i */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  FNL(f); 
  fprintf(f,"c_bool %s_%s(GLS_Tok x)",styctx->tkclsnam,PLR_symName(PTab,i));
  FNL(f); fprintf(f,"{");
  FNL(f); 
  if (styctx->genabs)
    fprintf(f,"  return PT_Abs_token(x) == CfgSyms[%d];",i);
  else
    fprintf(f,"  return( PT_THISTOK((PT_Term)x, CfgSyms[%d]) );",i);
  FNL(f); fprintf(f,"}"); 
  FNL(f);
}

static void genCStartTrm(Styx_T styctx)
/* generates for startsymbol class term */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  int     nt   = PLR_prodNonTerm(PTab,PLR_prodCnt(PTab)-PLR_startCnt(PTab));
  FNL(f); 
  fprintf
  (
    f,"c_bool %s_%s(PT_%sTerm x, %s* x1)",
    styctx->lprefix, PLR_language(PTab), 
    styctx->genabs?"Abs_":"", PLR_language(PTab)
  );
  FNL(f); fprintf(f,"{");
  FNL(f);
  if (styctx->genabs)
    fprintf(f,"  if( PT_Abs_nonterm(x) == CfgSyms[%d] )",nt);
  else
    fprintf(f,"  if( PT_THISNTM(x, CfgSyms[%d]) )",nt);
  FNL(f); fprintf(f,"  {");
  FNL(f); 
  fprintf
  (
    f,"    if( (%sCPtr)x1 != (%sCPtr)NULL ) *x1 = (%s)x;", 
    styctx->genabs?"Huge":"Std",styctx->genabs?"Huge":"Std",
    PLR_language(PTab)
  );
  FNL(f); fprintf(f,"    return True;");
  FNL(f); fprintf(f,"  }");
  FNL(f); fprintf(f,"  return False;");
  FNL(f); fprintf(f,"}"); 
  FNL(f);
}

static void genCNtmTrm(Styx_T styctx, int i)
/* generates for nonterminal class term i */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  int     nt   = PLR_ntClass(PTab,i); 
  c_bool  flg  = True; 
  HS_Elm elm; HS_Itr itr;
  FNL(f); 
  fprintf
  (
    f,"c_bool %s_%s(PT_%sTerm x, %s%s* x1)", 
    styctx->lprefix, PLR_symName(PTab,nt), styctx->genabs?"Abs_":"", 
    styctx->lprefix, PLR_symName(PTab,nt)  
  );
  FNL(f); fprintf(f,"{");
  FNL(f); fprintf(f,"  if( ");
  HS_FORALL(elm,itr,styctx->aNtm[i])
  {
    if( flg )
    {
      flg = False;
    }
    else
    {
      FNL(f); fprintf(f,"    ||");
    }
    if (styctx->genabs)
      fprintf(f," PT_Abs_nonterm(x) == CfgSyms[%d]",intCAST(elm));
    else
      fprintf(f," PT_THISNTM(x, CfgSyms[%d])",intCAST(elm));
  }
  fprintf(f," )");
  FNL(f); fprintf(f,"  {");
  FNL(f); 
  fprintf
  (
    f,"    if( (%sCPtr)x1 != (%sCPtr)NULL ) *x1 = (%s%s)x;",
    styctx->genabs?"Huge":"Std",styctx->genabs?"Huge":"Std",
    styctx->lprefix, PLR_symName(PTab,nt)
  );
  FNL(f); fprintf(f,"    return True;");
  FNL(f); fprintf(f,"  }");
  FNL(f); fprintf(f,"  return False;");
  FNL(f); fprintf(f,"}"); 
  FNL(f);
}

static void genCStart(Styx_T styctx, int i)
/* generates for start production i */
{ FILE*   f       = styctx->SysOut;
  PLR_Tab PTab    = styctx->PTab;
  int     prod    = PLR_prodCnt(PTab)-PLR_startCnt(PTab)+i,
          nt      = PLR_prodNonTerm(PTab,prod),
          ntstart = PLR_startSymbol(PTab,i),
          ntclsid = PLR_ntClassId(PTab,ntstart-PLR_tokenCnt(PTab));
  FNL(f); 
  fprintf
  (
    f,"c_bool %s_%s(%s x, ",
    PLR_language(PTab), PLR_prodName(PTab,prod), PLR_language(PTab)
  );
  genCNtmArgTyp(styctx,ntclsid);
  fprintf(f,"* x1)");
  /* for backward compatibility purposes ... */
  FNL(f); 
  fprintf
  (
    f,"#define %s_Start_%d   %s_%s",
    PLR_language(PTab), i, PLR_language(PTab), PLR_prodName(PTab,prod)
  );
  /* ... for backward compatibility purposes */
  FNL(f); fprintf(f,"{");
  FNL(f); 
  if (styctx->genabs)
    fprintf
    (
      f,"  assert0( PT_Abs_nonterm(x) == CfgSyms[%d], \"%s expected\" );",
      nt, PLR_language(PTab)
    );
  else
    fprintf
    (
      f,"  assert0( PT_THISNTM((PT_Term)x, CfgSyms[%d]), \"%s expected\" );",
      nt, PLR_language(PTab)
    );
  FNL(f); 
  if (styctx->genabs)
    fprintf
    (
      f,"  if( PT_Abs_product(x) != PrdSyms[%d] ) return False;", prod
    );
  else
    fprintf
    (
      f,"  if( ! PT_THISPRD((PT_Term)x, PrdSyms[%d]) ) return False;", prod
    );
  FNL(f);
  fprintf
  (
    f,"  if( (%sCPtr)x1 != (%sCPtr)NULL )",
    styctx->genabs?"Huge":"Std",styctx->genabs?"Huge":"Std"
  );
  FNL(f); fprintf(f,"    *x1 = (");
  genCNtmArgTyp(styctx,ntclsid);
  if (styctx->genabs)
    fprintf(f,")PT_Abs_part(x,0);");
  else
    fprintf
    (
      f,")GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[%d], %d, True));",
      ntstart,1
    );
  FNL(f); fprintf(f,"  return True;");
  FNL(f); fprintf(f,"}");
  FNL(f);
}

static void genCTypes(Styx_T styctx)
/* generates the types */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  int     i;
  sectionComment(styctx,"Types & Constants");
  FNL(f); 
  fprintf
  (
    f,"Abstract%sType( %-*s );", styctx->genabs?"Huge":"",
    styctx->maxlen, PLR_language(PTab)
  ); 
  FNL(f);
  for (i = 0; i < PLR_nontermCnt(PTab); i++) 
    if (PLR_ntClassId(PTab,i) == i && styctx->aPol[i] == -1)
    {
      FNL(f);
      fprintf
      (
        f,"Abstract%sType( %s%-*s );", styctx->genabs?"Huge":"",
        styctx->lprefix, (int)(styctx->maxlen - strlen(styctx->lprefix)), 
        PLR_symName(PTab,PLR_ntClass(PTab,i))
      );
    }
  FNL(f);
  /* terminal types */
  sectionComment(styctx,"Access to Tokens");
  for (i = 0; i < PLR_tokenCnt(PTab); i++) 
    if( CFG_TOK(PLR_symType(PTab,i)) &&
        HS_MBR_ELM(stringToSymbol(PLR_symName(PTab,i)),styctx->tkset) )
      genCTermTyp(styctx,i);
  /* nonterminal types */
  sectionComment(styctx,"Access to Terms");
  genCStartTrm(styctx);
  for (i = 0; i < PLR_nontermCnt(PTab); i++) 
    if (PLR_ntClassId(PTab,i) == i && styctx->aPol[i] == -1) 
      genCNtmTrm(styctx,i);
  /* special type "access" */
  sectionComment(styctx,PLR_language(PTab));
  for (i = 0; i < PLR_startCnt(PTab); i++) 
    genCStart(styctx,i);
  for (i = 0; i < PLR_nontermCnt(PTab); i++) 
    if (PLR_ntClassId(PTab,i) == i && styctx->aPol[i] == -1) 
      genCNonTerm(styctx,i);
}

static void genCSymbolQuit(Styx_T styctx)
/* generates symbol objects: quit function */
{ FILE* f = styctx->SysOut;
  FNL(f); fprintf(f,"void %s_quitSymbols()",styctx->lprefix);
  FNL(f); fprintf(f,"{");
  FNL(f); fprintf(f,"  --initcount_%s;",styctx->lprefix);
  FNL(f); fprintf(f,"  if( initcount_%s == 0 )",styctx->lprefix);
  FNL(f); fprintf(f,"  {");
  FNL(f); fprintf
          (
            f,
            "    assert0(CfgSyms != (symbol*)NULL,\"%sSymbols not initialized\");",
            styctx->lprefix
          );
  FNL(f); fprintf(f,"    if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);");
  FNL(f); fprintf(f,"    CfgSyms = (symbol*)NULL;");
  FNL(f); fprintf(f,"    if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);");
  FNL(f); fprintf(f,"    PrdSyms = (symbol*)NULL;");
  FNL(f); fprintf(f,"  }");
  FNL(f); fprintf(f,"}");
  FNL(f);
}

static void genCSymbolInit(Styx_T styctx)
/* generates symbol objects: initializing function */
{ FILE*   f    = styctx->SysOut;
  PLR_Tab PTab = styctx->PTab;
  int     i;
  FNL(f); fprintf(f,"void %s_initSymbols()",styctx->lprefix);
  FNL(f); fprintf(f,"{");
  FNL(f); fprintf(f,"  if( initcount_%s == 0 )",styctx->lprefix);
  FNL(f); fprintf(f,"  {");
  FNL(f); fprintf(f,"    GLS_init();");
  FNL(f); fprintf
          (
            f,
            "    assert0(CfgSyms == (symbol*)NULL,\"%sSymbols already initialized\");",
            styctx->lprefix
          );
  FNL(f); fprintf
          (
            f,"    CfgSyms = (symbol*)NewMem(sizeof(symbol)*%d);",
            PLR_symbolCnt(PTab)
          );
  FNL(f); fprintf
          (
            f,"    PrdSyms = (symbol*)NewMem(sizeof(symbol)*%d);",
            PLR_prodCnt(PTab)
          );
  FNL(f);
  for( i=0; i < PLR_symbolCnt(PTab); ++i )
  { string t = LIT_c_str_lit(PLR_symName(PTab,i));
    FNL(f); fprintf
            (
              f,"    CfgSyms[%d] = stringToSymbol(%s);", i,t
            );
    FreeMem(t);
  }
  FNL(f);
  for( i=0; i < PLR_prodCnt(PTab); ++i )
  {
    FNL(f); fprintf
            (
              f,"    PrdSyms[%d] = stringToSymbol(\"%s\");",
              i,PLR_prodName(PTab,i)
            );
  }
  FNL(f); fprintf(f,"  }");
  FNL(f); fprintf(f,"  ++initcount_%s;",styctx->lprefix);
  FNL(f); fprintf(f,"}"); 
  FNL(f);
}

static void genCSymbolAccess(Styx_T styctx)
/* generates symbol objects: initializing and quit functions */
{ FILE* f = styctx->SysOut;
  sectionComment(styctx,"symbol objects - init & quit"); FNL(f);
  fprintf(f,"static symbol* CfgSyms = (symbol*)NULL;"); FNL(f);
  fprintf(f,"static symbol* PrdSyms = (symbol*)NULL;"); FNL(f);
  fprintf(f,"static int initcount_%s = 0;",styctx->lprefix); FNL(f);
  genCSymbolInit(styctx);
  genCSymbolQuit(styctx);
}

static void genCInterface(Styx_T styctx, c_string filename)
/* generates the interface */
{ FILE* f = styctx->SysOut;
  styctx->maxlen  = 0;
  styctx->cprefix = StrCopy("/*");
  styctx->csuffix = StrCopy("*/");
  fileComment(styctx,filename,"Language Interface");
  fprintf(f,"#include \"ptm.h\""); FNL(f);
  fprintf(f,"#include \"gls%s.h\"",styctx->genabs?"_abs":""); FNL(f);
  genCSymbolAccess(styctx);
  genCTypes(styctx);
  FreeMem(styctx->cprefix); styctx->cprefix = (c_string)NULL;
  FreeMem(styctx->csuffix); styctx->csuffix = (c_string)NULL;
}

static void STYX_createC
            (
              Styx_T styctx, c_string Environ, c_bool genabs
            )
{ c_string filename = (c_string)NULL,
           base_ext = genabs?ANTEXT:INTEXT;
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0 && 
    styctx->PTab != (PLR_Tab)NULL,
    "missing parse table"
  );
  if( styctx->conflicts || PLR_conflictCnt(styctx->PTab) == 0 )
  {
    styctx->genabs = genabs;
    filename       = Str_printf("%s_%s.c",styctx->lprefix,base_ext);
    styctx->SysOut = OpenPath(Environ,filename,"","wt");
    genCInterface(styctx,filename);
    fclose(styctx->SysOut); styctx->SysOut = (FILE*)NULL;
    styctx->genabs     = C_False;
    FreeMem(filename);
  }
}

void STYX_createIntC(Styx_T styctx, c_string Environ)
/* create C interface [$'Environ'/]<Language>_int.c */
{ 
  STYX_createC(styctx,Environ,C_False);
}

void STYX_createAntC(Styx_T styctx, c_string Environ)
/* create special abstract C interface [$'Environ'/]<Language>_ant.c */
{ 
  STYX_createC(styctx,Environ,C_True);
}

static void STYX_appendC
            (
              Styx_T styctx, FILE* fp, c_string fid, c_bool genabs
            )
{ 
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0 && 
    styctx->PTab != (PLR_Tab)NULL && fp != (FILE*)NULL,
    "missing parse table or file"
  );
  if( styctx->conflicts || PLR_conflictCnt(styctx->PTab) == 0 )
  {
    styctx->genabs     = genabs;
    styctx->SysOut     = fp;
    genCInterface(styctx,fid);
    styctx->SysOut     = (FILE*)NULL;
    styctx->genabs     = C_False;
  }
}

void STYX_appendIntC(Styx_T styctx, FILE* fp, c_string fid)
/* append C interface to file 'fp';
   'fid' --> optional file name
*/
{ 
  STYX_appendC(styctx,fp,fid,C_False);
}

void STYX_appendAntC(Styx_T styctx, FILE* fp, c_string fid)
/* append C interface to file 'fp';
   'fid' --> optional file name
*/
{ 
  STYX_appendC(styctx,fp,fid,C_True);
}

