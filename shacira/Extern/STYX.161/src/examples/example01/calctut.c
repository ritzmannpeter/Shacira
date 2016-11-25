/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [calctut.c]                  A silly calculator                          */
/*                                                                          */
/* Copyright (c) 2000 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* TODO:
   - check FIXMEs
   - extend some libraries as indicated
*/

#include "stdosx.h"   // General Definitions (for gcc)
#include "ptm_gen.h"  // General Parsing Routines
#include "gls.h"      // General Language Services
#include "hmap.h"     // Datatype: Finite Maps
#include "symbols.h"  // Datatype: Symbols
#include "line_scn.h" // Single Line Input

#include "calc_int.h" // grammar interface
#include "calc_lim.h" // scanner table
#include "calc_pim.h" // parser  table


/* Dynamic Semantic -------------------------------------------------------- */

static int eval(calcExp ex)
/* evaluation homorphism */
{ calcExp ex1, ex2; GLS_Tok tok;

  if( calcExp_div(ex, &ex1,&ex2) ) return eval(ex1) /  eval(ex2);
  if( calcExp_mlt(ex, &ex1,&ex2) ) return eval(ex1) *  eval(ex2);
  if( calcExp_sub(ex, &ex1,&ex2) ) return eval(ex1) -  eval(ex2);
  if( calcExp_add(ex, &ex1,&ex2) ) return eval(ex1) +  eval(ex2);
  if( calcExp_neg(ex, &ex1) )      return - eval(ex1);
  if( calcExp_int(ex, &tok) )      return atoi(GLS_Tok_string(tok));
    
  PT_error(ex,"unrecognized expression type");
  return 0; // fault, but we continue anyway.
}

static void DynamicSemantic(calcCommand src)
/* semantic of the program: evaluate and print each "run" expression */
{ calcExp exp;

  if( calcCommand_exp(src, &exp) )
    printf("= %d\n",eval(exp)); // calculate and print result

}

/* Main Program ------------------------------------------------------------ */

void CALC()
/* initialize and get source */
{ Scn_T scn; Scn_Stream cstream; // scanner table & configuration
  PLR_Tab plr; PT_Cfg PCfg;      // parser  table & configuration
  //
  // init modules
  //
  MAP_init(); initSymbols(); calc_initSymbols();
  //
  // Get tables
  //
  Scn_get_calc(&scn);                           // Get scanner table
  plr = PLR_get_calc();                         // Get parser table

  //
  //  Processor
  //
  while(1)
  { PT_Term srcterm;               // the source term
    string line;
    printf("> ");
    line = Line_get(stdin);
    if (!line || *line == '\0') 
    {
      if (line) FreeMem(line);
      break;
    }
    //
    // got a line, go parse it
    //
    cstream = Stream_string(scn,line);           // Create stream on string
    PCfg    = PT_init(plr,cstream);              // Create parser
    srcterm = PT_PARSE(PCfg,"Command");          // Parse
    PT_setErrorCnt(PT_synErrorCnt(PCfg));        // Save error count
    PT_quit(PCfg);                               // Free parser
    Stream_close(cstream);                       // Close source stream
    Stream_free(cstream);                        // Free source stream
    //
    // done parsing, proceed if no syntax errors
    //
    if (PT_errorCnt() == 0)
    { calcCommand src;
      // execute expression
      bug0( calc_Start_Command((calc)srcterm,&src), "");
      DynamicSemantic(src);
    }
    //
    // free line and derivation tree
    //
    PT_delT(srcterm);
    FreeMem(line);
  }
  printf("\n");

  //
  // release allocated objects
  //
  Scn_free(scn);                               // Free scanner table
  PLR_delTab(plr);                             // Free parser  table
  calc_quitSymbols();
  freeSymbols();
  MAP_quit();
}

int main(int argc, string argv[])
{
  CALC();
  BUG_CORE; // check for object left over
  return 0;
}
