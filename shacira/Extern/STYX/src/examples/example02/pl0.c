/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [pl0.c]                      PL0 Interpreter                             */
/*                                                                          */
/* Copyright (c) 2000 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"  // General Definitions (for gcc)
#include "ptm_gen.h" // General Parsing Routines
#include "ptm_pp.h"  // Pretty Printer
#include "gls.h"     // General Language Services
#include "hmap.h"    // Datatype: Finite Maps
#include "symbols.h" // Datatype: Symbols

#include "pl0_int.h" // grammar interface
#include "pl0_lim.h" // scanner table
#include "pl0_pim.h" // parser  table


/* Auxiluary Functions ----------------------------------------------------- */

static void ppExp(pl0Exp exp)
/* somewhat misused pretty printer */
/* This is only for demonstration purposes, so we don't care to get the   */
/* parser table and initialize things here over and over. We do not even  */
/* reformat. See [stypp.c] for how to do it the right way. For diagnostic */
/* purposes, one will certainly prefere the PT_print routine.             */
{ PLR_Tab plr = PLR_get_pl0(); // Get parser table
  PTP_init(plr);               // Init Pretty Printer
  PTP_pp(exp,stdout);          // slightly abused
  PTP_quit();                  // Done Pretty Printer
  PLR_delTab(plr);             // Free parser table
}

static MAP(symbol, pl0Dfn) collectFunctions(pl0Program src, bool emitErrors)
/* collect global definitions, emit duplicate errors if requiered */
{ GLS_Lst(pl0Dfn) dfns; GLS_Lst(pl0Dfn) dit;
  MAP(symbol, pl0Dfn) glo = MAP_newPrimMap(); // global environment
  bug0( pl0Program_pgm(src,&dfns,_), "program expected");
  GLS_FORALL(dit,dfns)
  { GLS_Tok fid; pl0Dfn dfn = GLS_FIRST(pl0Dfn,dit);
    bug0( pl0Dfn_fun(dfn, &fid,_,_), "expecting fun Dfn");
    if (MAP_defined(glo,GLS_Tok_symbol(fid)))
    {
      if (emitErrors)
        PT_error(fid,"Function '%s' is already defined",GLS_Tok_string(fid));
    }
    else
      MAP_define(glo,GLS_Tok_symbol(fid),dfn);
  }
  return glo;
}

/* Static Semantics -------------------------------------------------------- */

static void StaticSemantic(pl0Program src)
/* Collect definitions and validate scoping rules */
{
  PT_Itr it; pl0Dfn d; pl0Exp e;
  MAP(symbol, pl0Dfn) glo; // global environment.
  MAP(symbol, void) local; // local environment, a set really.
  //
  // Pass 1
  //   - function names are unique
  //   : collect them in 'glo' for later use
  //
  glo = collectFunctions(src,True);
  //
  // Pass 2
  //   - applied function occurences are defined ...
  //   - ... and have the right arity
  //   - formal parameter names are unique
  //   - applied identfiers refer to formal parameters
  //
  local = NULL; // only to make gcc happy
  PT_FORALL(it,src)
  { PT_Term t = PT_termIT(it);

    if (PT_stateIT(it) == PT_PRAE && pl0_Dfn(t,&d) )
    // start of function definition
    { GLS_Lst(GLS_Tok) fpl; GLS_Lst(GLS_Tok) fpit;
      bug0( pl0Dfn_fun(d, _,&fpl,_), "expecting fun Dfn");
      local = MAP_newPrimMap(); // create local environment
      GLS_FORALL(fpit,fpl)
      { GLS_Tok fp = GLS_FIRST(GLS_Tok,fpit);
        if (MAP_defined(local,GLS_Tok_symbol(fp)))
          PT_error(fp,"Parameter '%s' is already defined",GLS_Tok_string(fp));
        else
          MAP_define(local,GLS_Tok_symbol(fp),_);
      }
    }
    
    if (PT_stateIT(it) == PT_POST && pl0_Dfn(t,&d) )
    // end of function definition
    { 
      MAP_freeMap(local); // drop local environment
    }

    if (PT_stateIT(it) == PT_PRAE && pl0_Exp(t,&e) )
    // found expression
    { GLS_Tok fid; GLS_Tok vid; GLS_Lst(pl0Exp) apl;

      if (pl0Exp_app(e, &fid, &apl)) // applied function
      {
        // check for defined occurence
        if (MAP_defined(glo,GLS_Tok_symbol(fid)))
        { GLS_Lst(GLS_Tok) fpl;
          bug0( pl0Dfn_fun( MAP_apply(pl0Dfn,glo,GLS_Tok_symbol(fid)), _,&fpl,_),
                "fun expected");
          // check for matching arity
          if (GLS_Lst_length(fpl) != GLS_Lst_length(apl))
            PT_error(e,"arity error");
        }
        else
          PT_error(e,"undefined function '%s'",GLS_Tok_string(fid));
      }
      
      if (pl0Exp_var(e, &vid)) // applied variable
      {
        // check for defined occurence
        if (!MAP_defined(local,GLS_Tok_symbol(vid)))
          PT_error(vid,"Undefined variable '%s'",GLS_Tok_string(vid));
      }
    }
  }
  MAP_freeMap(glo);
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
    PT_error(ex,"unrecognized expression type");
    return 0; // fault, but we continue anyway.
  }
}

static void DynamicSemantic(pl0Program src)
/* semantic of the program: evaluate and print each "run" expression */
{ GLS_Lst(pl0Run) runs; GLS_Lst(pl0Run) runit;
  MAP(symbol,pl0Dfn) glo = collectFunctions(src,False); // global environment
  MAP(symbol,int) loc = MAP_newPrimMap(); // empty local environment
  bug0( pl0Program_pgm(src,_,&runs), "program expected");
  GLS_FORALL(runit,runs)
  { pl0Exp exp; pl0Run run = GLS_FIRST(pl0Run,runit);
    bug0( pl0Run_run(run, &exp), "expecting run Run");
    calls = 0; evals = 0;              // init execution profile
    printf("running: "); ppExp(exp);   // pretty print expression
    printf(" = %d",eval(exp,glo,loc)); // calculate and print result
    printf(" [%d calls, %d expressions evaluated]\n",calls,evals);
  }
  MAP_freeMap(loc);
  MAP_freeMap(glo);
}

/* Main Program ------------------------------------------------------------ */

void PL0(string fileid)
/* initialize and get source */
{ Scn_T scn; Scn_Stream cstream; // scanner table & configuration
  PLR_Tab plr; PT_Cfg PCfg;      // parser  table & configuration
  PT_Term srcterm;               // the source term
  //
  // init modules
  //
  MAP_init(); initSymbols(); pl0_initSymbols();
  //
  // Parse the source file
  //
  Scn_get_pl0(&scn);                           // Get scanner table
  cstream = Stream_file(scn,"",fileid,"");     // Open source file
  plr     = PLR_get_pl0();                     // Get parser table
  PCfg    = PT_init(plr,cstream);              // Create parser
  srcterm = PT_PARSE(PCfg,"Program");          // Parse
  PT_setErrorCnt(PT_synErrorCnt(PCfg));        // Save error count
  PT_quit(PCfg);                               // Free parser
  Stream_close(cstream);                       // Close source stream
  Stream_free(cstream);                        // Free source stream
  Scn_free(scn);                               // Free scanner table
  PLR_delTab(plr);                             // Free parser table
  //
  // done parsing, proceed if no syntax errors
  //
  if (PT_errorCnt() == 0)
  { pl0Program src;
    // get tree for start symbol
    bug0( pl0_Start_Program((pl0)srcterm,&src), "Program expected");
    // check & execute program
    StaticSemantic(src);
    if (PT_errorCnt() == 0) DynamicSemantic(src);
  }
  if (PT_errorCnt() > 0)
  {
    fprintf(stderr,"Total %d errors.\n",PT_errorCnt());
    STD_ERREXIT;
  }
  //
  // release allocated objects
  //
  PT_delT(srcterm);
  pl0_quitSymbols();
  freeSymbols();
  MAP_quit();
}

int main(int argc, string argv[])
{
  if( argc > 1 ) PL0(argv[1]);
  else fprintf(stderr,"missing source\n");
  BUG_CORE; // check for object left over
  return 0;
}
