/* [styx_hdl.c]  Test module for dynamic loadable user-defined preprocessing, scan & parse handlers */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* [styx_hdl.c]      Test modul for dynamic loadable user-defined            */
/*                   preprocessing, scan & parse handlers                    */
/*                                                                           */
/* Copyright (c) 2002 by D\olle, Manns.                                      */
/* ------------------------------------------------------------------------- */

#include "standard.h"
#include "scn_base.h"
#include "ptm_gen.h"
#include "ptm_pp.h"

symbol STYHDL_premac
       (
         Scn_Stream pStream, string cTokNam, 
         string cTokVal, symbol* cMacVal
       )
/* user-defined preprocessing handler */
{
  *cMacVal = stringToSymbol(cTokVal);
  return SCN_FLG_RescanNone;
}

symbol STYHDL_pp(symbol tok, symbol val)
/* user-defined pp token conversion handler */
{
  return stringToSymbol(symbolToString(val));
}

symbol STYHDL_shift(symbol tok, symbol val)
/* user-defined shift handler */
{
  return stringToSymbol(symbolToString(val));
}

PT_Term STYHDL_reduce(PT_Term tree)
/* user-defined reduce handler */
{
  return tree;
}

