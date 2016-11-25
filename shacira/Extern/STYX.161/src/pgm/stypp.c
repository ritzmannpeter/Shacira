/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [stypp.c]               Pretty Printer                                   */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"

#include "ptm_pp.h"
#include "glo_tab.h"
#include "pgm_base.h"
#include "pgm_sopt.h" /* after ptm_pp.h becourse of naming conflicts */
#include "pgm_popt.h"

#include "styp_cim.h"

#define srclang  CTX_EVAL(string,"srclang")
#define dstlang  CTX_EVAL(string,"dstlang")
#define filename CTX_EVAL(string,"filename")
#define ppfun    CTX_EVAL(string,"ppfun")
#define binpath  CTX_EVAL(string,"BINSTYX")

int main(int argc, string argv[])
{ PLR_Tab PTabS, PTabD; Scn_T Scn; 
  Scn_Stream cStream; PT_Cfg PCfg; PTP_T ctx;
  PT_Term PTreeS = (PT_Term)NULL, PTreeD = (PT_Term)NULL;
  c_string pplib, s;
  symbol (*fun)(symbol t_id, symbol t_src) = NULL;
  /* init module */
  PGM_init(argc,argv,CTX_init_stypp);
  /* init user-defined pp token conversion handler */
  if( strlen(ppfun) > 0 )
  { 
    assert0
    ( 
      (s=strstr(ppfun,"@")) != (c_string)NULL, "missing ppfun-library"
    );
    pplib = s+1; *s = '\0';
    fun = (symbol (*)(symbol tok, symbol val))Glo_load
          (
            stringToSymbol(pplib),stringToSymbol(ppfun),True
          );
    *s = '@';
  }
  /* init pre-processing */
  PGM_initPreprocessing(prepar,premac,cset);
  /* create & init scan & parse tables */
  PTabS = PLR_getTab_env(binpath,srclang);
  PTabD = PLR_getTab_env(binpath,dstlang);
  Scn_get_env(binpath,srclang,&Scn);
  /* create & init scan stream */
  cStream = PGM_initScanStream
            (
              Scn,filename,prepar,prefun,False,cset,skipset,False
            );
  /* init parse configuration */
  PCfg = PT_init(PTabS,cStream);
  /* parse, transform and pp tree */
  /* early --> parse, transform and pp partial trees */
  PTreeS = PGM_parse(PCfg,start,shiftfun,reducefun,early,xaron);
  PT_setErrorCnt(PT_synErrorCnt(PCfg));
  if( early )
  {
    while( PTreeS != (PT_Term)NULL && PT_errorCnt() == 0 )
    { 
      /* transform and pp partial source tree */
      ctx = PTP_init_reentrant(PTabD);
      if( fun != NULL ) PTP_tok_conv_reentrant(ctx,(symbol)NULL,fun);
      PTreeD = PTP_transform_reentrant(ctx,PTreeS);
      PTP_pp_reentrant(ctx,PTreeD,STDOUT);
      PTP_quit_reentrant(ctx);
      /* release partial source and target tree */
      if( PTreeD != (PT_Term)NULL ) PT_delT(PTreeD);
      PT_delT(PTreeS);
      /* parse next partial source tree */
      PTreeS = PGM_parse(PCfg,start,shiftfun,reducefun,early,xaron);
      PT_setErrorCnt(PT_synErrorCnt(PCfg));
    }
  }
  if( PTreeS != (PT_Term)NULL && PT_errorCnt() == 0 )
  { 
    /* transform and pp source tree */
    ctx = PTP_init_reentrant(PTabD);
    if( fun != NULL ) PTP_tok_conv_reentrant(ctx,(symbol)NULL,fun);
    PTreeD = PTP_transform_reentrant(ctx,PTreeS);
    PTP_pp_reentrant(ctx,PTreeD,STDOUT);
    PTP_quit_reentrant(ctx);
    /* release target tree */
    if( PTreeD != (PT_Term)NULL ) PT_delT(PTreeD);
  }
  /* quit parse configuration */
  PT_quit(PCfg);
  /* release source tree */
  if( PTreeS != (PT_Term)NULL ) PT_delT(PTreeS);
  /* release scan stream, scan & parse tables */
  PGM_quitScanStream(cStream);
  PLR_delTab(PTabD);
  PLR_delTab(PTabS);
  Scn_free(Scn);
  /* quit preprocessing */
  PGM_quitPreprocessing(prepar);
  /* quit module */
  PGM_quit();
  BUG_CORE;
  return(0);
}
