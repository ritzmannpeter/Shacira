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

#include "pathes.h"
#include "literal.h"
#include "prs_gen.h"
#include "cfg_abs.h"
#include "ptm.h"
#include "ptm_gen.h"
#include "gls.h"
#include "symbols.h"
#include "hmap.h"
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


/* Scanner translation */

#define UsageLet  -100
#define UsageIgn  1
#define UsageTok  2
#define UsageCom  3

/* Interface generation */

#define INTEXT    "int" /* FileNames will be LANGUAGE_INTEXT.(c|h) */
#define ANTEXT    "ant" /* FileNames will be LANGUAGE_ANTEXT.(c|h) */

#define LineLen   78


ExternalType( StyxApp_T ) /* Abstract STYX application type */
{
  PLR_Tab PTab; /* STYX Parse table */
  Scn_T   Scn;  /* STYX Scan table  */
};


ExternalType( Styx_T ) /* Abstract STYX compiler type */
{
  StyxApp_T             styapp;      /* STYX application configuration */
  /* STYX compilation configuration                                    */
  c_bool                verbose;     /* print progress information     */
  c_bool                diagnose;    /* print diagnose information     */
  /* Parsing & semantic check of STYX definition                       */
  c_string              language;    /* STYX language                  */
  PT_Term               PTree;       /* Source derivation tree         */
  PT_Diag               diag;        /* Diagnose context               */
  MAPTY                 gloty;       /* Type for global definitions    */
  MAP(PT_Term, PT_Term) glo;         /* Global definitions             */
  HS_Set                tkset;       /* Used tokens                    */
  int                   errorCnt;    /* number of translation errors   */
  /* Scanner translation                                               */
  MAP(GLS_Tok,RegSet_T) qlx;         /* Computed RegSets               */
  /* Scan & parse table generation                                     */
  PLR_Tab               PTab;        /* Parse table                    */
  Scn_T                 Scn;         /* Scan table                     */
  /* abstract syntax data structure ( see comments in cfg_abs.c )      */
  int*                  aPol;
  HS_Set*               aNtm;
  HS_Set*               aPrd;
  /* Interface generation                                              */
  FILE*                 SysOut;      /* Interface output file          */
  c_bool                genabs; 
                           /* True: generate for row representation    */
  int                   maxlen;      
                           /* Layout: maximal function name length     */
  char                  tkclsnam[6]; /* Token class name               */
  char                  lprefix[5];  /* Language prefix                */
  c_string              cprefix;     /* comment prefix                 */
  c_string              csuffix;     /* comment suffix                 */
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

static void STYX_reset(Styx_T styctx)
{
  styctx->errorCnt    = 0;
  styctx->SysOut      = (FILE*)NULL;
  styctx->genabs      = C_False;
  styctx->maxlen      = 0;
  styctx->tkclsnam[0] = '\0';
  styctx->lprefix[0]  = '\0';
  if( styctx->PTree != (PT_Term)NULL ) 
  {
    PT_delT(styctx->PTree);
    styctx->PTree = (PT_Term)NULL;
  }
  if( styctx->glo != (MAP(_,_))NULL ) 
  {
    MAP_freeMap(styctx->glo);
    styctx->glo = (MAP(_,_))NULL;
  }
  if( styctx->qlx != (MAP(_,_))NULL ) 
  {
    MAP_freeMap(styctx->qlx);
    styctx->qlx = (MAP(_,_))NULL;
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
  styctx->styapp      = styapp;
  styctx->verbose     = verbose;
  styctx->diagnose    = diagnose;
  styctx->language    = StrCopy(language);
  styctx->diag        = PT_diag_init(prMsg!=NULL?prMsg:prMsg_stderr);
  styctx->PTree       = (PT_Term)NULL;
  styctx->gloty       = (MAPTY)NULL;
  styctx->glo         = (MAP(_,_))NULL;
  styctx->tkset       = (HS_Set)NULL;
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
  styctx->tkclsnam[0] = '\0';
  styctx->lprefix[0]  = '\0';
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
    if( styctx->diag != (PT_Diag)NULL ) 
    {
      PT_diag_quit(styctx->diag);
      styctx->diag = (PT_Diag)NULL;
    }
    FreeMem(styctx);
  }
}

/*I----------------------------- Set & Get ----------------------------------- */

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

static void Pass1(Styx_T styctx, styxSource s)
/* Aufsammeln der Definitionen und Scoping Rules */
{ bool startflg = False;
  MAP(PT_Term,NULL) pro = MAP_newMap(styctx->gloty); /* Productions */
  PT_Itr it; styxOptCfg optcfg; GLS_Lst(styxDfn) dfns;
  styxSource_root(s,_,_,&optcfg);
  PT_FORALL(it,s)
  { PT_Term t = PT_termIT(it);
    if (PT_stateIT(it) == PT_POST)
    { styxQlxDfn qd; styxDfn pd; styxPrd p; GLS_Tok id;
      /* Scope(Source): alle Bezeichner in QLX-Definitionen */
      if (styx_QlxDfn(t,&qd) )
      { styxQlxOpt o; styxQlxCat c;
        if ( styxQlxDfn_defn(qd,&c,&o,&id,_) )
        {
          if (MAP_defined(styctx->glo,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' allready defined",
              symbolToString(GLS_Tok_symbol(id))
            );
          else MAP_dfndom(styctx->glo,id,qd);
          /* CaseIgnore nur mit Comment und Token */
          if(   styxQlxOpt_ignca(o) && 
              ! styxQlxCat_tokC(c)  && 
              ! styxQlxCat_comC(c)   )
            PT_diag_err(o,styctx->diag,"CaseIgnore not allowed here");
        }
      }

      /* Scope(Source): alle Bezeichner in CFG-Definitionen */
      if (styx_Dfn(t,&pd))
      { styxCat c; styxDfnOpt o;
        if ( styxDfn_defn(pd,&c,&o,&id,_) )
        { 
          if (MAP_defined(styctx->glo,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' allready defined",
              symbolToString(GLS_Tok_symbol(id))
            );
          else MAP_dfndom(styctx->glo,id,pd);
          if (MAP_emptyMap(pro))
            PT_diag_err
            (
              id,styctx->diag,"production '%s' has no rules",
              symbolToString(GLS_Tok_symbol(id))
            );
          MAP_rmvall(pro);
          startflg |= styxCat_bgnC(c);
        }
      }

      /* Scope(Definition): alle Produktionsbezeichner */
      if (styx_Prd(t,&p))
      { 
        if ( styxPrd_prod(p,_,&id,_) )
        { 
          if (MAP_defined(pro,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' allready defined",
              symbolToString(GLS_Tok_symbol(id))
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
/* Referenzen */
{ PT_Itr it;
  PT_FORALL(it,s)
  { PT_Term t = PT_termIT(it);
    if (PT_stateIT(it) == PT_POST)
    { styxExp exp; styxMbr m; GLS_Tok id;
      if (styx_Exp(t,&exp) )
      {
        if ( styxExp_ident(exp,&id) )
        {
          if (!MAP_defined(styctx->glo,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' undefined",
              symbolToString(GLS_Tok_symbol(id))
            );
          else
            if (!styx_QlxDfn(MAP_apply(PT_Term,styctx->glo,id),_))
              PT_diag_err
              (
                id,styctx->diag,"'%s' is no QLX-identifier",
                symbolToString(GLS_Tok_symbol(id))
              );
        }
      }
      if (styx_Mbr(t,&m) )
      { 
        if ( styxMbr_ntm(m,&id) )
        { 
          if (!MAP_defined(styctx->glo,id))
            PT_diag_err
            (
              id,styctx->diag,"identifier '%s' undefined",
              symbolToString(GLS_Tok_symbol(id))
            );
          else
          { PT_Term def = MAP_apply(PT_Term,styctx->glo,id); 
            styxQlxDfn qd; styxQlxCat qc;
            if( ! ( styx_Dfn(def,_)                 ||
                    ( styx_QlxDfn(def,&qd)          &&
                      styxQlxDfn_defn(qd,&qc,_,_,_) &&
                      styxQlxCat_tokC(qc)            ) ) )
              PT_diag_err
              (
                id,styctx->diag,"'%s' is no grammar symbol",
                symbolToString(GLS_Tok_symbol(id))
              );
          }
        }
      }
    }
  }
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

static RegSet_T TRANS_RegSet_Cset(string s)
{ RegSet_T reg; long len; c_bool ucs4;
  wc_string tstring = LIT_styx_lit_str(&len,s,&ucs4);
  reg = RegSet_CsetN(tstring,len);
  FreeMem(tstring); return reg;
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

static int qlx_usage(Styx_T styctx, GLS_Tok id)
{ styxQlxCat cat;
  styxQlxDfn_defn(MAP_apply(styxQlxDfn,styctx->glo,id),&cat,_,_,_);
  if (styxQlxCat_letC(cat)) return UsageLet;
  if (styxQlxCat_tokC(cat)) return UsageTok;
  if (styxQlxCat_comC(cat)) return UsageCom;
  if (styxQlxCat_ignC(cat)) return UsageIgn;
  BUG; return 0;
}

static RegSet_T trans_Ide(Styx_T styctx, GLS_Tok id)
{
  if (!MAP_defined(styctx->qlx,id))
  { RegSet_T res,old; styxExp exp;
    /* Flag to protect against endless recursion */
    MAP_dfndom(styctx->qlx,id,NULL); 
    styxQlxDfn_defn(MAP_apply(styxQlxDfn,styctx->glo,id),_,_,_,&exp);
    res = trans_Exp(styctx,exp);
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
{ styxExp exp1; styxExp exp2; GLS_Tok tok;
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
  if( styxExp_opt(e,&exp1) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T res = RegSet_Option(a);
    RegSet_Free(a);
    return res;
  }
  if( styxExp_star(e,&exp1) )
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
  if( styxExp_range(e,&exp1,&exp2) )
  { RegSet_T a = trans_Exp(styctx,exp1);
    RegSet_T b = trans_Exp(styctx,exp2);
    RegSet_T res;
    short al, bu;
    if (!RegSet_isChar(a)) PT_diag_err(exp1,styctx->diag,"single character");
    if (!RegSet_isChar(b)) PT_diag_err(exp2,styctx->diag,"single character");
    al = RegSet_charVal(a);
    bu = RegSet_charVal(b);
    if (al > bu)
    { short x = al; al = bu; bu = x; 
      PT_diag_err(e,styctx->diag,"range must be ordered"); 
    }
    res = RegSet_Range(al,bu);
    RegSet_Free(a); RegSet_Free(b);
    return res;
  }
  if( styxExp_set(e,&tok) )
    return TRANS_RegSet_Cset(symbolToString(GLS_Tok_symbol(tok)));
  if( styxExp_sequ(e,&tok) )
    return TRANS_RegSet_String(symbolToString(GLS_Tok_symbol(tok)));
  if( styxExp_ident(e,&tok) )
    return trans_Ide(styctx,tok);
  BUG; return (RegSet_T)NULL;
}

static Scn_T trans_QlxDfns(Styx_T styctx, styxSource s)
{ GLS_Tok id; ScnDfn_T scndfn;
  PT_Itr it; MAPIT itr;
  styctx->qlx = MAP_newMap(styctx->gloty);
  styxSource_root(s,&id,_,_);
  scndfn = Scn_dfnBegin_reentrant(symbolToString(GLS_Tok_symbol(id)));
  Scn_setMsgFun_reentrant(scndfn,PT_diag_msgFun(styctx->diag));
  PT_FORALL(it,s) if (PT_stateIT(it) == PT_PRAE)
  { PT_Term t = PT_termIT(it); styxQlxDfn d;
    if( styx_QlxDfn(t,&d) )
    { styxQlxOpt o;
      if( styxQlxDfn_defn(d,_,&o,&id,_) )
      {
        if( qlx_usage(styctx,id) == UsageTok ||
            qlx_usage(styctx,id) == UsageIgn ||
            qlx_usage(styctx,id) == UsageCom  )
        { RegSet_T a = trans_Ide(styctx,id);
          Scn_dfnToken_reentrant
          (
            scndfn, symbolToString(GLS_Tok_symbol(id)),
            (byte)( qlx_usage(styctx,id) == UsageIgn
                    ? SCN_FLG_IgnoreToken
                    : 0 | ( styxQlxOpt_ignca(o) ? SCN_FLG_IgnoreCase : 0)
                  ),
            a
          );
          RegSet_Free(a);
        }
      }
    }
  }
  styctx->Scn = Scn_dfnEnd_reentrant(scndfn,styctx->diagnose);
  MAP_forItr(id,itr,styctx->qlx) 
    RegSet_Free(MAP_apply(RegSet_T,styctx->qlx,id));
  MAP_freeMap(styctx->qlx); styctx->qlx = (MAP(_,_))NULL;
  return styctx->Scn;
}

/* checking keywords */

static void Pass3(Styx_T styctx, styxSource src)
/* keywords */
{ PT_Itr it;
  PT_FORALL(it,src) if (PT_stateIT(it) == PT_POST) /* alle reservierten Worte */
  { PT_Term t = PT_termIT(it); styxMbr m; GLS_Tok seq;
    if( styx_Mbr(t,&m) && styxMbr_tkm(m,&seq) )
    { c_bool ucs4; StdCPtr s = TRANS_Seq(seq,&ucs4);
      /*FIXME: comments are not allowed, too*/
      if( (!ucs4 && !Scn_check_Token(styctx->Scn,(string)s))     || 
          (ucs4 && !Scn_check_WCToken(styctx->Scn,(wc_string)s))  )
        PT_diag_err(seq,styctx->diag,"malformed token");
      FreeMem(s);
    }
  }
}

/* Parser Translation */

static string normalKeyword(Styx_T styctx, GLS_Tok seq, c_bool* ucs4)
/* normalizes keywords (IgnoreCase) */
{ StdCPtr s = TRANS_Seq(seq,ucs4); short tid;
  if( *ucs4 == C_False )
  {
    tid = Scn_check_Token(styctx->Scn,(string)s);
    bug1(tid,"token '%s' does not belong to grammar\n",(string)s);
    if( Scn_tokFlags(styctx->Scn,tid) & SCN_FLG_IgnoreCase ) 
      StrToLower((string)s);
    return (string)s;
  }
  else
  { string mbkey, tmp;
    tid = Scn_check_WCToken(styctx->Scn,(wc_string)s);
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
      if( Scn_tokFlags(styctx->Scn,tid) & SCN_FLG_IgnoreCase ) 
        WCStrToLower((wc_string)s);
      bug0((mbkey = GS_ucs4_to_utf8((wc_string)s))!=(string)NULL,"");
      FreeMem(s);
    }
    return mbkey;
  }
}

static PLR_Cfg trans_Dfns(Styx_T styctx, styxSource src)
{ MAPTY keyty; MAP(symbol,NULL) key; /* reserved words */
  PLR_Cfg Cfg; MAPIT itr; PT_Itr it; 
  GLS_Lst(styxDfn) dfns; styxOptCfg optcfg;
  styxDfn pd; styxMbr m; GLS_Tok id; GLS_Tok seq;
  styxSource_root(src,&id,_,&optcfg);
  styxOptCfg_cfg(optcfg,&dfns);
  Cfg   = PLR_createCfg(symbolToString(GLS_Tok_symbol(id)));
  keyty = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  key   = MAP_newMap(keyty);
  PT_FORALL(it,src) if( PT_stateIT(it) == PT_PRAE )
  { PT_Term t = PT_termIT(it); styxQlxDfn qd; 
    if( styx_QlxDfn(t,&qd) ) /* Token */
    { 
      if( styxQlxDfn_defn(qd,_,_,&id,_) &&
          ( qlx_usage(styctx,id) == UsageTok || 
            qlx_usage(styctx,id) == UsageCom ) )
          PLR_addTK(Cfg,symbolToString(GLS_Tok_symbol(id)),PLR_TYP_TOK);
    }
    if( styx_Dfn(t,&pd) ) /* Nonterminal */
    { styxDfnOpt o;
      if( styxDfn_defn(pd,_,&o,&id,_) )
        PLR_addNT(Cfg,symbolToString(GLS_Tok_symbol(id)),styxDfnOpt_errnt(o));
    }
    if( styx_Mbr(t,&m) ) /* Keyword */
    { 
      if( styxMbr_tkm(m,&seq) )
      { c_bool ucs4; string s = normalKeyword(styctx,seq,&ucs4); 
        symbol keyword = stringToSymbol(s);
        FreeMem(s);
        if( ! MAP_defined(key,keyword) )
        {
          MAP_dfndom(key,keyword,NULL);
          PLR_addTK(Cfg,symbolToString(keyword),(ucs4?PLR_TYP_WKY:PLR_TYP_KEY));
        }
      }
      else
      if( styxMbr_else(m) )
      {
        PLR_addTK(Cfg,PLR_TOK_Other,PLR_TYP_TOK);
      }     
    }
  }
  MAP_freeMap( key );
  MAP_freeTyp( keyty );

  PLR_endSD(Cfg); /* Sorting Token & Nonterminals */

  MAP_forItr(id,itr,styctx->glo)
    if( styx_QlxDfn(MAP_apply(PT_Term,styctx->glo,id),_) && 
        qlx_usage(styctx,id) == UsageCom ) /* Special Token */
      PLR_addST(Cfg,symbolToString(GLS_Tok_symbol(id)));
  PT_FORALL(it,dfns) if( PT_stateIT(it) == PT_PRAE )
  { PT_Term t = PT_termIT(it); GLS_Tok nt; styxPrd p;
    if( styx_Dfn(t,&pd) ) /* Startsymbol */
    { styxCat c;
      if( styxDfn_defn(pd,&c,_,&nt,_) && styxCat_bgnC(c) )
        PLR_addSN(Cfg,symbolToString(GLS_Tok_symbol(nt)));
    }

    if( styx_Prd(t,&p) ) /* Production */
    { styxLay lay; GLS_Tok pid;
      if( styxPrd_prod(p,&lay,&pid,_) )
      {
        if( styxLay_dft(lay) )
          PLR_addPR
          (
            Cfg,symbolToString(GLS_Tok_symbol(pid)),
            PLR_PRD_DFT,symbolToString(GLS_Tok_symbol(nt))
          );
        else
        if( styxLay_rec(lay) )
          PLR_addPR
          (
            Cfg,symbolToString(GLS_Tok_symbol(pid)),
            PLR_PRD_REC,symbolToString(GLS_Tok_symbol(nt))
          );
        else
        if( styxLay_grp(lay) )
          PLR_addPR
          (
            Cfg,symbolToString(GLS_Tok_symbol(pid)),
            PLR_PRD_GRP,symbolToString(GLS_Tok_symbol(nt))
          );
      }
    }
    if( styx_Mbr(t,&m) ) /* Production Symbol */
    { long r = PT_row(m), c = PT_col(m);
      if( styxMbr_tkm(m,&seq) )
      { c_bool ucs4; string s = normalKeyword(styctx,seq,&ucs4);
        PLR_addPT(Cfg,s,r,c);
        FreeMem(s);
      }
      else
      if( styxMbr_ntm(m,&id) )
      { PT_Term t = MAP_apply(PT_Term,styctx->glo,id);
        r = PT_row(id);
        c = PT_col(id);
        if( styx_QlxDfn(t,_) )
        {
          PLR_addPT(Cfg,symbolToString(GLS_Tok_symbol(id)),r,c);
          HS_SET_ELM(GLS_Tok_symbol(id),styctx->tkset);
        }
        if( styx_Dfn(t,_) )
          PLR_addPN(Cfg,symbolToString(GLS_Tok_symbol(id)),r,c);
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

static int STYX_compile(Styx_T styctx, Scn_Stream cStream, c_string incpath)
{ PLR_Cfg Cfg; PT_Cfg PCfg;
  MAP(long,symbol) pPreParMap; SPP_T pPP;
  styxSource s; styxOptCfg optcfg; GLS_Lst(styxDfn) dfns; GLS_Tok id; 
  void (*prMsg)(c_string msg) = PT_diag_msgFun(styctx->diag);
  if (styctx->verbose) (*prMsg)("parsing ...\n");
  STYX_reset(styctx);
  pPreParMap = MAP_newPrimMap();
  MAP_dfndom(pPreParMap,SPP_INC_PATH,stringToSymbol(incpath));
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
    styxSource_root(s,&id,_,&optcfg);
    if ( strcmp( symbolToString(GLS_Tok_symbol(id)),styctx->language) != 0)
      PT_diag_err(id,styctx->diag,"language identifier und file name are different");
  
    styctx->gloty = MAP_newTyp(primCopy,primFree,PT_equal,PT_hash, primCopy,primFree);
    styctx->glo   = MAP_newMap(styctx->gloty);
    styctx->tkset = HS_CREATE_ADTSET(symbol);

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
    /* QLX-Uebersetzer */

    if (styctx->verbose) (*prMsg)("begin scanner creation\n");
    styctx->Scn = trans_QlxDfns(styctx,s);
    if (styctx->verbose) (*prMsg)("end scanner creation\n");
    if( styctx->Scn != (Scn_T)NULL )
    {
      if (styctx->verbose) (*prMsg)("Pass 3\n"); 
      Pass3(styctx,s); /* Pass 3: keyword */
      if( (styctx->errorCnt=PT_diag_errorCnt(styctx->diag)) == 0 )
      {
        /* CFG-Uebersetzer */
  
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
          if( styctx->PTab == (PLR_Tab)NULL )
          {
            Scn_free(styctx->Scn); styctx->Scn = (Scn_T)NULL;
          }
        }
        else (*prMsg)("Note: No parser specified.\n");
      }
      else
      {
        Scn_free(styctx->Scn); styctx->Scn = (Scn_T)NULL;
      }
    }
    else 
    {
      (*prMsg)("Scan table creation failed.\n");
    }
  }
  if( styctx->glo != (MAP(_,_))NULL )
  {
    MAP_freeMap(styctx->glo); styctx->glo = (MAP(_,_))NULL;
  }
  if( styctx->gloty != (MAPTY)NULL ) 
  {
    MAP_freeTyp(styctx->gloty); styctx->gloty = (MAPTY)NULL;
  }
  if( styctx->Scn == (Scn_T)NULL && styctx->tkset != (HS_Set)NULL )
  {
    HS_DROP_SET(styctx->tkset); styctx->tkset = (HS_Set)NULL;
  }
  return styctx->errorCnt > 0 
         ? styctx->errorCnt
         : styctx->Scn == (Scn_T)NULL ? -1 : 0;
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
    styctx != (Styx_T)NULL && 
    styctx->errorCnt == 0 && styctx->Scn != (Scn_T)NULL,
    "missing scan table"
  );
  Scn_put(Environ,styctx->Scn);
  if( styctx->PTab != (PLR_Tab)NULL )
    PLR_putTab(Environ,styctx->PTab);
}

void STYX_appendTabIMG(Styx_T styctx, BinImg_T lim, BinImg_T pim)
/* unloads scan & parse table to images 'lim' and 
   optional 'pim'
*/
{
  assert0
  (
    styctx != (Styx_T)NULL && lim != (BinImg_T)NULL &&
    styctx->errorCnt == 0 && styctx->Scn != (Scn_T)NULL,
    "missing scan table or image"
  );
  Scn_fput_bin(lim,styctx->Scn);
  if( styctx->PTab != (PLR_Tab)NULL && pim != (BinImg_T)NULL )
    PLR_fputTab_bin(pim,styctx->PTab);
}

void STYX_createTabC(Styx_T styctx, c_string Environ)
/* creates scan & parse table sources 
   [$'Environ'/]<Language>_lim.c 
   [$'Environ'/]<Language>_pim.c (optional)
*/
{
  assert0
  (
    styctx != (Styx_T)NULL && 
    styctx->errorCnt == 0 && styctx->Scn != (Scn_T)NULL,
    "missing scan table"
  );
  Scn_C_Modul(Environ,styctx->Scn);
  if( styctx->PTab != (PLR_Tab)NULL )
    PLR_CTab_Modul(Environ,styctx->PTab);
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
    styctx != (Styx_T)NULL && lfp != (FILE*)NULL &&
    styctx->errorCnt == 0 && styctx->Scn != (Scn_T)NULL,
    "missing scan table or file"
  );
  Scn_C_Source(lfp, lfid,styctx->Scn);
  if( styctx->PTab != (PLR_Tab)NULL && pfp != (FILE*)NULL )
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
        genProdComment(styctx,(int)elm,indent);
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
    styctx->Scn != (Scn_T)NULL && styctx->PTab != (PLR_Tab)NULL,
    "missing tables"
  );
  styctx->SysOut  = OpenPath(Environ,PLR_language(styctx->PTab),".abs","wt");
  styctx->cprefix = StrCopy("/*");
  styctx->csuffix = StrCopy("*/");
  sprintf(styctx->lprefix,"%.4s",PLR_language(styctx->PTab));
  filename        = Str_printf("%s.abs",PLR_language(styctx->PTab));
  genTypesCom(styctx,filename);
  styctx->lprefix[0] = '\0';
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
    styctx->Scn != (Scn_T)NULL && styctx->PTab != (PLR_Tab)NULL &&
    fp != (FILE*)NULL,
    "missing tables or file"
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
      fprintf(f," PT_Abs_nonterm(x) == CfgSyms[%d]",(int)elm);
    else
      fprintf(f," PT_THISNTM((PT_Term)x, CfgSyms[%d])",(int)elm);
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
  HS_FORALL(elm,itr,styctx->aPrd[i]) genCProd(styctx,(int)elm);
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
      fprintf(f," PT_Abs_nonterm(x) == CfgSyms[%d]",(int)elm);
    else
      fprintf(f," PT_THISNTM(x, CfgSyms[%d])",(int)elm);
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
        styctx->lprefix, styctx->maxlen - strlen(styctx->lprefix), 
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
  FNL(f); fprintf(f,"  if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);");
  FNL(f); fprintf(f,"  if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);");
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
  FNL(f); fprintf(f,"  GLS_init();");
  FNL(f); fprintf
          (
            f,"  CfgSyms = (symbol*)NewMem(sizeof(symbol)*%d);",
            PLR_symbolCnt(PTab)
          );
  FNL(f); fprintf
          (
            f,"  PrdSyms = (symbol*)NewMem(sizeof(symbol)*%d);",
            PLR_prodCnt(PTab)
          );
  FNL(f);
  for( i=0; i < PLR_symbolCnt(PTab); ++i )
  { string t = LIT_c_str_lit(PLR_symName(PTab,i));
    FNL(f); fprintf
            (
              f,"  CfgSyms[%d] = stringToSymbol(%s);", i,t
            );
    FreeMem(t);
  }
  FNL(f);
  for( i=0; i < PLR_prodCnt(PTab); ++i )
  {
    FNL(f); fprintf
            (
              f,"  PrdSyms[%d] = stringToSymbol(\"%s\");",
              i,PLR_prodName(PTab,i)
            );
  }
  FNL(f); fprintf(f,"}"); 
  FNL(f);
}

static void genCSymbolAccess(Styx_T styctx)
/* generates symbol objects: initializing and quit functions */
{ FILE* f = styctx->SysOut;
  sectionComment(styctx,"symbol objects - init & quit"); FNL(f);
  fprintf(f,"static symbol* CfgSyms = (symbol*)NULL;"); FNL(f);
  fprintf(f,"static symbol* PrdSyms = (symbol*)NULL;"); FNL(f);
  genCSymbolInit(styctx);
  genCSymbolQuit(styctx);
}

static void genCInterface(Styx_T styctx, c_string filename)
/* generates the interface */
{ FILE* f = styctx->SysOut;
  styctx->maxlen  = 0;
  styctx->cprefix = StrCopy("/*");
  styctx->csuffix = StrCopy("*/");
  sprintf(styctx->tkclsnam,"T%s",styctx->lprefix);
  fileComment(styctx,filename,"Language Interface");
  fprintf(f,"#include \"ptm.h\""); FNL(f);
  fprintf(f,"#include \"gls%s.h\"",styctx->genabs?"_abs":""); FNL(f);
  genCSymbolAccess(styctx);
  genCTypes(styctx);
  styctx->tkclsnam[0] = '\0';
  FreeMem(styctx->cprefix); styctx->cprefix = (c_string)NULL;
  FreeMem(styctx->csuffix); styctx->csuffix = (c_string)NULL;
}

static void STYX_createC(Styx_T styctx, c_string Environ, c_bool genabs)
{ c_string filename = (c_string)NULL,
           base_ext = genabs?ANTEXT:INTEXT;
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0 && 
    styctx->Scn != (Scn_T)NULL && styctx->PTab != (PLR_Tab)NULL,
    "missing tables"
  );
  styctx->genabs = genabs;
  sprintf(styctx->lprefix,"%.4s",PLR_language(styctx->PTab));
  filename       = Str_printf("%s_%s.c",styctx->lprefix,base_ext);
  styctx->SysOut = OpenPath(Environ,filename,"","wt");
  genCInterface(styctx,filename);
  fclose(styctx->SysOut); styctx->SysOut = (FILE*)NULL;
  styctx->lprefix[0] = '\0';
  styctx->genabs     = C_False;
  FreeMem(filename);
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

static void STYX_appendC(Styx_T styctx, FILE* fp, c_string fid, c_bool genabs)
{ 
  assert0
  (
    styctx != (Styx_T)NULL && styctx->errorCnt == 0 && 
    styctx->Scn != (Scn_T)NULL && styctx->PTab != (PLR_Tab)NULL &&
    fp != (FILE*)NULL,
    "missing tables or file"
  );
  styctx->genabs     = genabs;
  styctx->SysOut     = fp;
  sprintf(styctx->lprefix,"%.4s",PLR_language(styctx->PTab));
  genCInterface(styctx,fid);
  styctx->lprefix[0] = '\0';
  styctx->SysOut     = (FILE*)NULL;
  styctx->genabs     = C_False;
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

