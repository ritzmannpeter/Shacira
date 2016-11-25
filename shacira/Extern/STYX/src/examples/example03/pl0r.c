/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [pl0r.c]                     PL0 Runtime                                 */
/*                                                                          */
/* Copyright (c) 2000 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"  // General Definitions (for gcc)
#include "gls.h"     // General Language Services
#include "hmap.h"    // Datatype: Finite Maps
#include "symbols.h" // Datatype: Symbols

#include "pl0_int.h" // grammar interface

/* Auxiluary Functions ----------------------------------------------------- */

static void pl0_get(string name, pl0Program* pgm)
/* get "compiled" pl0 program */
{
  getBgn("",name,"");
  getHeader("pl0",1,0);
  PT_getT(pgm);
  getEnd();
}

static MAP(symbol, pl0Dfn) collectFunctions(pl0Program src)
/* collect global definitions, emit duplicate errors if requiered */
{ GLS_Lst(pl0Dfn) dfns; GLS_Lst(pl0Dfn) dit;
  MAP(symbol, pl0Dfn) glo = MAP_newPrimMap(); // global environment
  bug0( pl0Program_pgm(src,&dfns,_), "program expected");
  GLS_FORALL(dit,dfns)
  { GLS_Tok fid; pl0Dfn dfn = GLS_FIRST(pl0Dfn,dit);
    bug0( pl0Dfn_fun(dfn, &fid,_,_), "expecting fun Dfn");
    MAP_define(glo,GLS_Tok_symbol(fid),dfn);
  }
  return glo;
}

/* Dynamic Semantic -------------------------------------------------------- */

static int calls; // profiling function calls
static int evals; // profiling evaluated expression

static int eval(pl0Exp ex, MAP(symbol,pl0Dfn) glo, MAP(symbol,int) loc)
/* a standard expression evaluator */
{ pl0Exp ex1, ex2, ex3; GLS_Tok tok; GLS_Lst(pl0Exp) exps;
  evals++; // profile
  if( pl0Exp_equ(ex, &ex1,&ex2) ) return eval(ex1,glo,loc) == eval(ex2,glo,loc); else
  if( pl0Exp_les(ex, &ex1,&ex2) ) return eval(ex1,glo,loc) <  eval(ex2,glo,loc); else
  if( pl0Exp_div(ex, &ex1,&ex2) ) return eval(ex1,glo,loc) /  eval(ex2,glo,loc); else
  if( pl0Exp_mlt(ex, &ex1,&ex2) ) return eval(ex1,glo,loc) *  eval(ex2,glo,loc); else
  if( pl0Exp_sub(ex, &ex1,&ex2) ) return eval(ex1,glo,loc) -  eval(ex2,glo,loc); else
  if( pl0Exp_add(ex, &ex1,&ex2) ) return eval(ex1,glo,loc) +  eval(ex2,glo,loc); else
  if( pl0Exp_neg(ex, &ex1) )      return - eval(ex1,glo,loc);                    else
  if( pl0Exp_int(ex, &tok) )      return atoi(GLS_Tok_string(tok));              else
  if( pl0Exp_var(ex, &tok) )      return MAP_apply(int,loc,GLS_Tok_symbol(tok)); else
  if( pl0Exp_exp(ex, &tok,&ex1) ) 
  { int val = eval(ex1,glo,loc);
    MAP_ovrdom(loc,GLS_Tok_symbol(tok),val); // overwrite previous assignment
    return val;
  }
  else
  if( pl0Exp_if(ex, &ex1,&ex2,&ex3) ) return eval(eval(ex1,glo,loc)?ex2:ex3,glo,loc);
  else
  if( pl0Exp_app(ex, &tok,&exps) )
  { int res; GLS_Lst(GLS_Tok) fpit, fpl; pl0Exp body;
    MAP(symbol,int) newloc = MAP_newPrimMap();
    pl0Dfn dfn = MAP_apply(pl0Dfn,glo,GLS_Tok_symbol(tok));
    bug0( pl0Dfn_fun( dfn, _, &fpl, &body), "function expected");
    calls++; // profile
    // evaluate actual parameter list creating new local environment
    GLS_FORALL(fpit,fpl)
    { GLS_Tok fp = GLS_FIRST(GLS_Tok,fpit);
      pl0Exp  ap = GLS_FIRST(pl0Exp,exps);
      MAP_define(newloc,GLS_Tok_symbol(fp),eval(ap,glo,loc));
      exps = GLS_REST(pl0Exp,exps);
    }
    res = eval(body,glo,newloc); // recursively evaluate function body
    MAP_freeMap(newloc); // free new local environment
    return res;
  }
  else
  {
    bug0(False,"unrecognized expression type");
    return 0; // never reached
  }
}

static void DynamicSemantic(pl0Program src)
/* semantic of the program: evaluate and print each "run" expression */
{ GLS_Lst(pl0Run) runs; GLS_Lst(pl0Run) runit;
  MAP(symbol,pl0Dfn) glo = collectFunctions(src); // global environment
  MAP(symbol,int) loc = MAP_newPrimMap(); // empty local environment
  bug0( pl0Program_pgm(src,_,&runs), "program expected");
  GLS_FORALL(runit,runs)
  { pl0Exp exp; pl0Run run = GLS_FIRST(pl0Run,runit);
    bug0( pl0Run_run(run, &exp), "expecting run Run");
    calls = 0; evals = 0; // init execution profile
    printf("running: [TERM] = %d",eval(exp,glo,loc)); // calculate and print result
    printf(" [%d calls, %d expressions evaluated]\n",calls,evals);
  }
  MAP_freeMap(loc);
  MAP_freeMap(glo);
}

/* Main Program ------------------------------------------------------------ */

static void PL0_run(string fileid)
/* initialize and get source */
{ pl0Program src;

  // init modules
  MAP_init(); initSymbols(); pl0_initSymbols();

  pl0_get(fileid,&src); // get binary image
  DynamicSemantic(src); // execute program

  // release memory
  PT_delT(src);
  pl0_quitSymbols();
  freeSymbols();
  MAP_quit();
}

int main(int argc, string argv[])
{
  if( argc > 1 ) PL0_run(argv[1]);
  else fprintf(stderr,"missing source\n");
  BUG_CORE; // check for object left over
  return 0;
}
