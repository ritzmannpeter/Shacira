/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [cmdlib.c]                   CMD Compiler Library                        */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* TODO:                                                                    */
/* - Typenpruefung (Pass1?)                                                 */
/* - CMD_to_MAN                                                             */

#include "standard.h"
#include "cmd_int.h"

#include "hmap.h"
#include "symbols.h"
#include "ptm.h"
#include "gls.h"
#ifdef __BORLANDC__
#include "INC/ctx.h"
#else
#include "ctx.h"
#endif

#include "pathes.h"
#include "literal.h"
#include "ptm_gen.h"
#include "scn_pre.h"

#include "cmd_lim.h"
#include "cmd_pim.h"


static PT_Term   srcterm;
static cmdSource src;

static MAPTY                 gloty; /* Type for global definitions     */
static MAP(PT_Term, PT_Term) glo;   /* Global Definitions              */


/*I------------------ Command description parsing and evaluation ------------------------- */

/**/string CMD_FidString(GLS_Lst(GLS_Tok) f);

static string StrConcat(string a, string b)
/* strcat with alloc, frees arguments */
{ string res = (string)NewMem(strlen(a)+strlen(b)+1);
  sprintf(res,"%s%s",a,b);
  FreeMem(a); FreeMem(b);
  return res;
}

static void Pass1(cmdSource s)
/* Aufsammeln der Definitionen und Scoping Rules */
{ PT_Itr it; PT_Term il; GLS_Tok id; cmdDfn d; cmdOptVal ov;
  GLS_Lst(cmdDfn) args; GLS_Lst(cmdDfn) opts; GLS_Lst(cmdDfn) envs;
  PT_FORALL(it,s)
  { PT_Term t = PT_termIT(it);
    if (PT_stateIT(it) == PT_POST)
    { 
      /* Scope(Source): alle Bezeichner in Definitionen */
      if( cmd_Dfn(t,&d) && cmdDfn_defn(d,&id,_,_,_) )
      { 
        if (MAP_defined(glo,id))
          PT_error(id,"identifier allready defined");
        else
          MAP_dfndom(glo,id,d);
      }
    }
  }
  cmdSource_root(s,_,_,_,&args,_,&opts,_,&envs,_);
  GLS_FORALL(il,args)
  { 
    cmdDfn_defn(GLS_FIRST(cmdDfn,il),_,_,&ov,_);
    if (cmdOptVal_val(ov,_)) PT_error(ov,"initialisation not allowed");
  }
  GLS_FORALL(il,opts)
  {
    cmdDfn_defn(( d = GLS_FIRST(cmdDfn,il) ),&id,_,&ov,_);
    if (cmdOptVal_non(ov)) PT_error(d,"initialisation mandantory");
    if( !strcmp(GLS_Tok_string(id),CTX_VARG) )
      PT_error(d,"forbidden name '%s'",CTX_VARG);
  }
  GLS_FORALL(il,envs)
  {
    cmdDfn_defn(( d = GLS_FIRST(cmdDfn,il) ),&id,_,&ov,_);
    if( !strcmp(GLS_Tok_string(id),CTX_VARG) )
      PT_error(d, "forbidden name '%s'",CTX_VARG);
  }
}

static string aux_FidString(GLS_Lst(GLS_Tok) f)
/* Fid to string */
{ GLS_Lst(GLS_Tok) lst; GLS_Tok id;
  return
    GLS_EMPTY(f)             ? StrCopy("")
  : GLS_Lst_cons(f,&id,&lst) ? StrConcat
                               (
                                 StrCopy("_"),
                                 StrConcat
                                 (
                                   StrCopy(GLS_Tok_string(id)),
                                   aux_FidString(lst)
                                 )
                               )
  : (BUG, "");
}

static string PidString(cmdPid f)
/* Pid to string */
{ GLS_Lst(GLS_Tok) lst; GLS_Tok id;
  return
    cmdPid_curr(f)          ? StrCopy(".")
  : cmdPid_prev(f)          ? StrCopy("..")
  : cmdPid_name(f,&lst)     ? CMD_FidString(lst)
  : cmdPid_ext (f,&lst,&id) ? StrConcat
                              (
                                CMD_FidString(lst),
                                StrConcat
                                (
                                  StrCopy("."), StrCopy(GLS_Tok_string(id))
                                )
                              )
  : (BUG, "");
}

static string aux_RelPString(GLS_Lst(cmdPid) f)
/* Dirlist to string */
{ GLS_Lst(cmdPid) lst; cmdPid p;
  return
    GLS_EMPTY(f)            ? StrCopy("")
  : GLS_Lst_cons(f,&p,&lst) ? StrConcat
                              (
                                StrCopy(DirSep()),
                                StrConcat(PidString(p),aux_RelPString(lst))
                              )
  : (BUG, "");
}

static string RelPString(GLS_Lst(cmdPid) f)
/* Dirlist to string */
{ GLS_Lst(cmdPid) lst; cmdPid p;
  return
    GLS_Lst_cons(f,&p,&lst)
    ? StrConcat(PidString(p),aux_RelPString(lst))
    : StrCopy("");
}

static string AbsDrvString(cmdOptDrv f)
/* OptDrv with Separator to string */
{ GLS_Tok id;
  return
    cmdOptDrv_non(f)       ? StrCopy(DirSep())
  : cmdOptDrv_drive(f,&id) ? StrConcat(StrCopy(GLS_Tok_string(id)),
                             StrConcat(StrCopy(":"),StrCopy(DirSep())))
  : (BUG, "");
}

static string PathString(cmdPath f)
/* Path to string */
{ GLS_Lst(cmdPid) lst; GLS_Tok id; cmdOptDrv odr;
  return
    cmdPath_abs(f,&odr,&lst) ? StrConcat(AbsDrvString(odr),RelPString(lst))
  : cmdPath_rel(f,&lst)      ? RelPString(lst)
  : cmdPath_env(f,&id,&lst)  ? StrConcat
                               (
                                 StrConcat
                                 (
                                   StrCopy("$"),StrCopy(GLS_Tok_string(id))
                                 ),
                                 StrConcat(StrCopy(DirSep()),RelPString(lst))
                               )
  : (BUG, "");
}

static string aux_PLstString(GLS_Lst(cmdPath) f)
/* Pathlist to string */
{ GLS_Lst(cmdPath) lst; cmdPath p;
  return
    GLS_EMPTY(f)            ? StrCopy("")
  : GLS_Lst_cons(f,&p,&lst) ? StrConcat
                              (
                                StrCopy(PathSep()),
                                StrConcat(PathString(p),aux_PLstString(lst))
                              )
  : (BUG, "");
}

static string PLstString(GLS_Lst(cmdPath) f)
/* Pathlist to string */
{ GLS_Lst(cmdPath) lst; cmdPath p;
  return
    GLS_Lst_cons(f,&p,&lst)
    ? StrConcat ( PathString(p),aux_PLstString(lst))
    : (BUG, "");
}

static string TRANS_Seq(GLS_Tok seq)
{ wc_string tstring; long len; c_bool ucs4; 
  string s = GLS_Tok_string(seq), res;
  tstring = LIT_styx_lit_str(&len,s,&ucs4);
  res     = WCToStrCopy(tstring);
  bug0(strlen(res) == len,"'\\0' not allowed within keywords");
  FreeMem(tstring);
  return res;
}

cmdSource CMD_init(c_string ctx, c_string cmdid, c_bool envflg)
/* get command description from file ['ctx'/'cmdid'.cmd] 
   'envflg' --> 'ctx' is treated as environment variable
*/
{ Scn_T scn; Scn_Stream cstream; PLR_Tab plr; PT_Cfg PCfg;
  GLS_Lst(GLS_Tok) fid; string cmdfid, path;
  MAPTY mtyp_prim = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  MAP(long,symbol) pPreParMap = MAP_newMap(mtyp_prim);
  SPP_T pPP = (SPP_T)NULL;
  MAP_dfndom(pPreParMap,SPP_INC_PATH,stringToSymbol(ctx));
  pPP = SPP_init_reentrant(pPreParMap);
  cmd_initSymbols();
  Scn_get_cmd(&scn); 
  if( envflg )
    cstream = Stream_file(scn,ctx,cmdid,".cmd");
  else
  {
    path    = MkPath(ctx,cmdid,".cmd",'d');
    cstream = Stream_file(scn,"",path,"");
    FreeMem(path);
  }
  Stream_premac_set(cstream, SPP_premac);
  Stream_add_ctxval(cstream,SPP_premac,pPP);
  plr     = PLR_get_cmd();
  PCfg    = PT_init(plr,cstream);
  srcterm = PT_PARSE(PCfg,"Source");
  PT_setErrorCnt(PT_synErrorCnt(PCfg));
  PT_quit(PCfg);
  Stream_close(cstream);
  Stream_free(cstream);
  Scn_free(scn);
  PLR_delTab(plr);
  SPP_quit_reentrant(pPP);
  MAP_freeMap(pPreParMap);
  MAP_freeTyp(mtyp_prim);
  if (PT_errorCnt() == 0)
  {
    cmd_Start_0((cmd)srcterm,&src);
    cmdSource_root(src,&fid,_,_,_,_,_,_,_,_);
    cmdfid = CMD_FidString(fid);
    if( strcmp(cmdfid,cmdid) != 0 )
      PT_error(fid,"different command and file name");
    FreeMem(cmdfid);
    gloty = MAP_newTyp(primCopy,primFree,PT_equal,PT_hash,primCopy,primFree);
    glo   = MAP_newMap(gloty);
    Pass1(src); /* Pass 1: uniqueness */
  }
  if (PT_errorCnt() > 0)
  {
    fprintf(stderr,"Totally %d errors.\n",PT_errorCnt());
    STD_ERREXIT;
  }
  return src;
}

void CMD_done(void)
/* throughout with command description */
{
  MAP_freeMap(glo);
  MAP_freeTyp(gloty);
  PT_delT(srcterm);
  cmd_quitSymbols();
}

c_string CMD_FidString(GLS_Lst(GLS_Tok) f)
/* translates file specification 'f' into a string; allocs memory */
{ GLS_Lst(GLS_Tok) lst; GLS_Tok id;
  return
    GLS_Lst_cons(f,&id,&lst)
    ? StrConcat(StrCopy(GLS_Tok_string(id)),aux_FidString(lst))
    : (BUG, "");
}

c_string CMD_Val_to_String(cmdVal val)
/* translates argument specification 'val' into a string; allocs memory */
{ GLS_Lst(cmdPath) plst; GLS_Tok tok;
  if (cmdVal_true(val))       return StrCopy("true");
  if (cmdVal_false(val))      return StrCopy("false");
  if (cmdVal_int(val,&tok))   return StrCopy(GLS_Tok_string(tok));
  if (cmdVal_str(val,&tok))   return TRANS_Seq(tok);
  if (cmdVal_name(val,&tok))  return StrCopy(GLS_Tok_string(tok));
  if (cmdVal_path(val,&plst)) return PLstString(plst);
  BUG; return "";
}

long CMD_NumberOfValues(void)
/* number of context variables */
{
  return MAP_count(glo);
}
