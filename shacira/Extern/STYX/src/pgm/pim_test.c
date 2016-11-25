/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [pim_test.c]                  Parser Test                                */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"

#include "pgm_base.h"
#include "pgm_sopt.h"
#include "pgm_popt.h"

#include "pim__cim.h"

#define language CTX_EVAL(string,"Language")
#define filename CTX_EVAL(string,"FileName")
#define binmode  CTX_EVAL(bool,"binmode")
#define tree     CTX_EVAL(bool,"tree")
#define binpath  CTX_EVAL(string,"BINSTYX")

int main(int argc, string argv[])
{ PLR_Tab PTab; Scn_T Scn; Scn_Stream cStream; 
  PT_Cfg PCfg; PT_Term PTree; 
  /* init module */
  PGM_init(argc,argv,CTX_init_pim_test);
  /* init pre-processing */
  PGM_initPreprocessing(prepar,premac,cset);
  /* create & init scan & parse tables */
  PGM_initTables(binpath,language,&PTab,&Scn);
  /* create & init scan stream */
  cStream = PGM_initScanStream
            (
              Scn,filename,prepar,prefun,binmode,cset,
              skipset,CTX_EVAL(bool,"lookahead"),False
            );
  /* init parse configuration */
  PCfg = PGM_initParsing(cStream,PTab);
  /* parse and construct tree */
  /* early --> print tree */
  PTree = PGM_parse(PCfg,start,shiftfun,reducefun,early,xaron);
  if( early )
  {
    while( PTree != (PT_Term)NULL )
    {
      if( tree ) PGM_printTree(PTree,cset,wprint);
      PT_delT(PTree);
      PTree = PGM_parse(PCfg,start,shiftfun,reducefun,early,xaron);
    }
  }
  /* quit parse configuration */
  PT_quit(PCfg);
  /* print derivation tree */
  if( tree ) PGM_printTree(PTree,cset,wprint);
  /* release derivation tree */
  if( PTree != (PT_Term)NULL ) PT_delT(PTree);
  /* release scan stream, scan & parse tables */
  PGM_quitScanStream(cStream);
  PGM_quitTables(PTab,Scn);
  /* quit preprocessing */
  PGM_quitPreprocessing(prepar);
  /* quit module */
  PGM_quit();
  BUG_CORE;
  return(0);
}
