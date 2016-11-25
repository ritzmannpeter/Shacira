/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [lim_test.c]                  Scanner Test                               */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"

#include "pgm_base.h"
#include "pgm_sopt.h"

#include "lim__cim.h"

#define filename CTX_EVAL(string,"FileName")
#define binmode  CTX_EVAL(bool,"binmode")
#define binpath  CTX_EVAL(string,"BINSTYX")

int main(int argc, string argv[])
{ Scn_Stream stream; Scn_T scn; 

  /* init module */
  PGM_init(argc,argv,CTX_init_lim_test);
  /* init preprocessing */
  PGM_initPreprocessing(prepar,premac,cset);
  /* get the scanner */
  Scn_get_env(binpath,CTX_EVAL(string,"Language"),&scn);
  /* create & init scan stream */
  stream = PGM_initScanStream
           (
             scn,filename,prepar,prefun,binmode,cset,
             skipset,CTX_EVAL(bool,"lookahead"),True
           );
  /* actual scanning & printing */
  PGM_scan(stream,CTX_EVAL(bool,"tokens"),cset,wprint);
  /* quit scan stream */
  PGM_quitScanStream(stream);
  Scn_free(scn);
  /* quit preprocessing */
  PGM_quitPreprocessing(prepar);
  /* print symbols */
  if (CTX_EVAL(bool,"symbols")) { NL; printSymbols(0); NL; }
  /* quit module */
  PGM_quit();
  BUG_CORE;
  return(0);
}
