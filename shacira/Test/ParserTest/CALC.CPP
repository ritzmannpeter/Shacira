#ifdef LANG_CALC

// [calc.cpp] STYX example: a simple calculator


// necessary includes
#include "iostream.h"

#include "stdosx.h"    // base header STYX library
#include "scn_base.h"  // scanner
#include "ptm_gen.h"   // term construction
#include "symbols.h"   // symbol table
#include "hmap.h"      // hash maps

#include "calc_lim.h"  // calc scanner table
#include "calc_pim.h"  // calc parser table
#include "calc_int.h"  // calc language interface

//#undef _G_HAVE_BOOL
//#include <stdiostream.h>


static int evalExp(calcExp ex)
// expression evaluation via generated language interface
{ calcExp x1; calcExp x2; GLS_Tok x3;
  if (calcExp_mlt(ex, &x1, &x2)) return evalExp(x1) * evalExp(x2);
  if (calcExp_div(ex, &x1, &x2)) return evalExp(x1) / evalExp(x2);
  if (calcExp_add(ex, &x1, &x2)) return evalExp(x1) + evalExp(x2);
  if (calcExp_sub(ex, &x1, &x2)) return evalExp(x1) - evalExp(x2);
  if (calcExp_neg(ex, &x2))      return             - evalExp(x2);
  if (calcExp_int(ex, &x3))      return atoi(GLS_Tok_string(x3));
  BUG;
}

static void calculate(void)
// parse & eval command line 
{ Scn_T      pScn;               // scan table
  Scn_Stream pCstream;           // scan stream
  PLR_Tab    pPlr;               // parse table
  PT_Cfg     pPCfg;              // parse configuration
  PT_Term    pSrc;               // derivation tree
  bool       bContinue = C_True; // continue flag
  Scn_get_calc(&pScn);               // create scan table
  pPlr = PLR_get_calc();             // create parse table
//  pCstream = STREAM_STDIN(pScn);     // create scanner from stdin
  pCstream = Stream_file(pScn, "", "T", ""); // create scanner from string
  pPCfg    = PT_init(pPlr,pCstream); // create parse configuration
  while( bContinue ) // continue process ?
  { calcCmd pCmd;    // subterm command
    calcExp pExp;    // subterm expression
    // parse command line and construct derivation tree
    // as soon as possible without waiting for EOF ( pre-reduction )
    // arguments: parse configuration, start symbol or "" for the first
    pSrc  = PT_INTERPRETE(pPCfg,"");
    // initializes error count with syntax error count
    PT_setErrorCnt(PT_synErrorCnt(pPCfg));
    // no errors --> eval derivation tree
    if( PT_errorCnt() == 0 ) 
    {
      // extract command
      assert0( calc_Start_Cmd(pSrc,&pCmd), "");
      // end command --> stop process
      if( calcCmd_end(pCmd) ) bContinue = C_False;
      else
      {
        // extract expression
        assert0( calcCmd_exp(pCmd,&pExp), "");
        // eval expression and and print result
        cout << evalExp(pExp) << "\n";
      }
    }
    else bContinue = C_False;
    PT_delT(pSrc);        // release derivation tree
  }
  PT_quit(pPCfg);         // release parse configuration
  Stream_close(pCstream); // close scan stream
  Stream_free(pCstream);  // release scan stream
  Scn_free(pScn);         // release scan table
  PLR_delTab(pPlr);       // release parse table
}


int main(int c, char* argv[])
{ 
  // modul initialisation for hash maps and symbols
  MAP_init();
  initSymbols();
  calc_initSymbols();
  // interpreter
  calculate();
  // modul termination for hash maps and symbols
  calc_quitSymbols();
  freeSymbols();
  MAP_quit();
  BUG_CORE;
  return 0;
}

#else // Shacira

// necessary includes
//#include "iostream.h"

#include "stdosx.h"    // base header STYX library
#include "scn_base.h"  // scanner
#include "ptm_gen.h"   // term construction
#include "symbols.h"   // symbol table
#include "hmap.h"      // hash maps

#include "shac_lim.h"  // calc scanner table
#include "shac_pim.h"  // calc parser table
#include "shac_int.h"  // calc language interface

//#undef _G_HAVE_BOOL
//#include <stdiostream.h>

static char _Buffer[0x100000] = {0};
#define BLOCK_SIZE  0x1000
static void LoadBuffer()
{
   char * buf_ptr = _Buffer;
   FILE * stream = fopen("fm.mdl", "r");
   int nread = fread(buf_ptr, 1, BLOCK_SIZE, stream);
   while (nread == BLOCK_SIZE) {
      buf_ptr += nread;
      nread = fread(buf_ptr, 1, BLOCK_SIZE, stream);
   }
}

static void calculate(void)
// parse & eval command line 
{ Scn_T      pScn;               // scan table
  Scn_Stream pCstream;           // scan stream
  PLR_Tab    pPlr;               // parse table
  PT_Cfg     pPCfg;              // parse configuration
  PT_Term    pSrc;               // derivation tree
  bool       bContinue = C_True; // continue flag
  Scn_get_Shacira(&pScn);               // create scan table
  pPlr = PLR_get_Shacira();             // create parse table
//  pCstream = STREAM_STDIN(pScn);     // create scanner from stdin
  LoadBuffer();
  pCstream = Stream_string(pScn, _Buffer); // create scanner from string
//  pCstream = Stream_file(pScn, "", "fm.mdl", ""); // create scanner from string
  pPCfg    = PT_init(pPlr,pCstream); // create parse configuration
#ifdef lassma
  while( bContinue ) // continue process ?
  { calcCmd pCmd;    // subterm command
    calcExp pExp;    // subterm expression
    // parse command line and construct derivation tree
    // as soon as possible without waiting for EOF ( pre-reduction )
    // arguments: parse configuration, start symbol or "" for the first
    pSrc  = PT_INTERPRETE(pPCfg,"");
    // initializes error count with syntax error count
    PT_setErrorCnt(PT_synErrorCnt(pPCfg));
    // no errors --> eval derivation tree
    if( PT_errorCnt() == 0 ) 
    {
      // extract command
      assert0( calc_Start_Cmd(pSrc,&pCmd), "");
      // end command --> stop process
      if( calcCmd_end(pCmd) ) bContinue = C_False;
      else
      {
        // extract expression
        assert0( calcCmd_exp(pCmd,&pExp), "");
      }
    }
    else bContinue = C_False;
    PT_delT(pSrc);        // release derivation tree
  }
#else
  pSrc  = PT_INTERPRETE(pPCfg,"");
  // initializes error count with syntax error count
  PT_setErrorCnt(PT_synErrorCnt(pPCfg));
  // no errors --> eval derivation tree
  if( PT_errorCnt() == 0 ) {
      printf("okay\n");
  } else {
      printf("errors\n");
  }
  PT_delT(pSrc);        // release derivation tree
#endif
  PT_quit(pPCfg);         // release parse configuration
  Stream_close(pCstream); // close scan stream
  Stream_free(pCstream);  // release scan stream
  Scn_free(pScn);         // release scan table
  PLR_delTab(pPlr);       // release parse table
}


int main(int c, char* argv[])
{ 
  // modul initialisation for hash maps and symbols
  MAP_init();
  initSymbols();
  Shac_initSymbols();
  // interpreter
  calculate();
  // modul termination for hash maps and symbols
  Shac_quitSymbols();
  freeSymbols();
  MAP_quit();
  BUG_CORE;
  return 0;
}

#endif
