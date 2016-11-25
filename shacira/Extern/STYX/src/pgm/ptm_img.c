/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ptm_img.c]             Put&Get Term                                     */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"

#include "binimg.h"
#include "pgm_base.h"
#include "pgm_sopt.h"
#include "pgm_popt.h"

#include "ptm__cim.h"

#define img      CTX_EVAL(string,"Img")
#define language CTX_EVAL(string,"Language")
#define filename CTX_EVAL(string,"FileName")
#define binmode  CTX_EVAL(bool,"binmode")
#define binpath  CTX_EVAL(string,"BINSTYX")

int main(int argc, string argv[])
{ PLR_Tab PTab; PT_Term PTree = (PT_Term)NULL;
  ROW(PT_Term) trees = OT_CREATE(PT_Term,primCopy,PT_delT,primEqual);
  /* init module */
  PGM_init(argc,argv,CTX_init_ptm_img);
  /* create & init parse table */
  PTab = PLR_getTab_env(binpath,language);
  if( strlen(filename) ) // parse and put source file
  { string s = Str_printf("[%s] Binary %s Derivation Tree",img,language);
    Scn_T Scn; Scn_Stream cStream; PT_Cfg PCfg;
    /* init pre-processing */
    PGM_initPreprocessing(prepar,premac,cset);
    /* create & init scan table */
    Scn_get_env(binpath,language,&Scn);
    /* create & init scan stream */
    cStream = PGM_initScanStream
              (
                Scn,filename,prepar,prefun,binmode,cset,
                skipset,CTX_EVAL(bool,"lookahead"),False
              );
    /* init parse configuration */
    PCfg = PGM_initParsing(cStream,PTab);
    /* parse, put and release tree */
    /* early --> parse, put and release partial trees */
    PTree = PGM_parse(PCfg,start,shiftfun,reducefun,early,xaron);
    if( PTree != (PT_Term)NULL )
    { 
      putBgn("",img,"");
      putHeader(s,"ptmimg",2,0);
      if( early )
      { 
        while( PTree != (PT_Term)NULL )
        { 
          OT_PUSH(PTree,trees);
          putReference(PTree,PT_putT);
          PTree = PGM_parse(PCfg,start,shiftfun,reducefun,early,xaron);
          putByte((byte)(PTree != (PT_Term)NULL));
        }
      }
      else
      if( PTree != (PT_Term)NULL )
      {
        OT_PUSH(PTree,trees);
        putReference(PTree,PT_putT);
        putByte((byte)0);
      }
      putEnd();
    }
    /* quit parse configuration */
    PT_quit(PCfg);
    /* release scan stream & scan table */
    PGM_quitScanStream(cStream);
    Scn_free(Scn);
    /* quit preprocessing */
    PGM_quitPreprocessing(prepar);
    FreeMem(s);
  }
  else // get image file and print tree(s)
  { byte b;
    getBgn("",img,"");
    getHeader("ptmimg",2,0);
    getReference(&PTree,PT_getT);
    OT_PUSH(PTree,trees);
    PGM_printTree(PTree,cset,wprint);
    getByte(&b);
    while( b == (byte)1 ) // fetch and print tree
    {
      getReference(&PTree,PT_getT);
      OT_PUSH(PTree,trees);
      PGM_printTree(PTree,cset,wprint);
      getByte(&b);
    }
    getEnd();
  }
  /* release derivation tree(s) */
  OT_DEL_T(trees);
  /* release parse table */
  PLR_delTab(PTab);
  /* quit module */
  PGM_quit();
  BUG_CORE;
  return(0);
}
