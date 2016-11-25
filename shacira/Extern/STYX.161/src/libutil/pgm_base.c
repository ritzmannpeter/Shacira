/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [pgm_base.c]      Common function library for the (test) programms       */
/*                                                                          */
/* Copyright (c) 2002 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "symbols.h"
#include "hmap.h"
#include "scn_pre.h"
#include "scn_base.h"
#include "prs.h"
#include "prs_io.h"
#include "ptm.h"
#include "ptm_gen.h"

#include "glo_tab.h"
#include "literal.h"
#include "pathes.h"
#include "gstream.h"
#include "ctx.h"


static MAP(long,symbol) pPreParMap = (MAP(_,_))NULL;
static SPP_T            pPP        = (SPP_T)NULL;


void PGM_init(int argc, char* argv[], void (*ctxinit)(int argc, char* argv[]))
/* init program */
{
  (*ctxinit)(argc,argv);
  initSymbols();
  MAP_init();
  Glo_init();
}

void PGM_quit(void)
/* quit program */
{
  Glo_quit();
  MAP_quit();
  freeSymbols();
  CTX_quit();
}

void PGM_initPreprocessing(c_string prepar, c_string premac, c_string cset)
/* init STYX-like macro preprocessing 
   according commandline parameters 'prepar', 'premac' and 'cset'
*/
{
  if( strlen(prepar) > 0 )
  { c_string szS, szT; PIT pItr; 
    pPreParMap = MAP_newPrimMap();
    pItr = PIT_make(prepar); 
    PIT_sep(pItr,",");
    while( ( szS = PIT_read(pItr) ) != NULL )
    {
      szT = strstr(szS,"~");
      if( szT != (c_string)NULL )
      {
        *szT = '\0';
        MAP_ovrdom(pPreParMap,atol(szS),stringToSymbol(szT+1));
        *szT = '~';
      }
    }
    PIT_drop(pItr);
    if( ! MAP_defined(pPreParMap,SPP_INC_CHARSET) && strlen(cset) > 0 )
      MAP_ovrdom(pPreParMap,SPP_INC_CHARSET,stringToSymbol(cset));
    pPP = SPP_init_reentrant(pPreParMap);
    /* add pre-defined macros */
    if( strlen(premac) > 0 )
    {
      pItr = PIT_make(premac); 
      PIT_sep(pItr,",");
      while( ( szS = PIT_read(pItr) ) != NULL )
      {
        SPP_addCtxMacro_reentrant(pPP,lstringToSymbol(szS));
      }
      PIT_drop(pItr);
    }
  }
}

void PGM_quitPreprocessing(c_string prepar)
/* quit STYX-like macro preprocessing; release resources */
{
  if( strlen(prepar) > 0 )
  {
    if( pPreParMap != (MAP(_,_))NULL ) MAP_freeMap(pPreParMap);
    if( pPP != (SPP_T)NULL )           SPP_quit_reentrant(pPP);
  }
}

Scn_Stream PGM_initScanStream
           (
             Scn_T Scn, c_string filename,
             c_string prepar, c_string prefun, 
             c_bool binmode, c_string cset,
             c_string skipset, c_bool stdTokIDs
           )
/* create and init scan stream according commandline parameters 
   'filename', 'prepar', 'prefun', 'binmode' and 'cset'
   stdTokIDs --> set default token IDs
*/
{ Scn_Stream cStream = (Scn_Stream)NULL; 
  c_string   prelib  = (c_string)NULL, s = (c_string)NULL;
  size_t     l       = strlen(prefun);
  assert0
  ( 
    ( strlen(prepar) == 0 || l == 0 ) && 
    ( l == 0 || (s=strstr(prefun,"@")) != (c_string)NULL ),
    "prepar and prefun option not allowed or missing prefun-library"
  );
  assert0
  ( 
    !binmode || strlen(cset) == 0,
    "binmode and charset option not allowed"
  );
  if( strlen(cset) == 0 )
  {
    cStream = Stream_file(Scn,"",filename,"");
    if( binmode ) Stream_binmode_set(cStream);
  }
  else
  { FILE*          pFP = OpnFile(filename,"rb");
    GStream_T      pGS = GS_stream_file_new(pFP, cset, True); 
    Scn_Stream_Itr pChrItr;
    assert1(pGS != (GStream_T)NULL, "creation of stream '%s' failed",filename);
    pChrItr = Stream_Itr_new
              (
                GS_stream_get_wcrc, GS_fun_destruct(pGS), GS_ucs4_to_utf8, 
                GS_fun_seek(pGS), pGS, filename
              );
    cStream = Stream_bgn(Scn,pChrItr);
    Stream_Itr_free(pChrItr);
  }
  if( strlen(prepar) > 0 && pPP != (SPP_T)NULL )
  {
    Stream_premac_set(cStream, SPP_premac);
    Stream_add_ctxval(cStream,SPP_premac,pPP);
  }
  if( strlen(prefun) > 0 )
  { Scn_PreMacFun fun;
    prelib = s+1; *s = '\0';
    fun = (Scn_PreMacFun)Glo_load
          (
            stringToSymbol(prelib),stringToSymbol(prefun),True
          );
    *s = '@';
    Stream_premac_set(cStream, fun);
  }
  if( strlen(skipset) )
  { long len, i; c_bool ucs4;
    wc_string s = LIT_styx_lit_str(&len,skipset,&ucs4);
    for( i=0; i < len; ++i )
      Stream_skip_character(cStream,(int)s[i]);
    FreeMem(s);
  }
  if( stdTokIDs )
  { int i, j, k = 1, g = Scn_groups(Scn);
    Stream_defEofId(cStream,-1);
    Stream_defErrId(cStream, 0);
    for( j=0; j < g || ( j == g && g == 0 ); ++j )
    { Scn_T gscn = ( g == 0 ) ? Scn : Scn_group(Scn,j);
      for (i = 1; i < Scn_tokens(gscn); i++, k++)
      { string s = Scn_tokid(gscn,i);
        Stream_defTokId( cStream, s, (short)k );
        FreeMem(s);
      }
    }
  }
  return cStream;
}

void PGM_quitScanStream(Scn_Stream cStream)
/* close and release scan stream */
{
  if( cStream != (Scn_Stream)NULL )
  {
    Stream_close(cStream);
    Stream_free(cStream);
  }
}

void PGM_initTables
     (
       c_string Environ, c_string language, PLR_Tab* PTab, Scn_T* Scn
     )
/* create scan and parse tables according commandline parameter 
   'Environ' and 'language' 
*/
{
  Scn_get_env(Environ,language,Scn);
  *PTab = PLR_getTab_env(Environ,language);
}

PT_Cfg PGM_initParsing(Scn_Stream cStream, PLR_Tab PTab)
/* init parse term configuration for 
   scan stream 'cStream' and parse table 'PTab' 
*/
{ PT_Cfg PCfg = PT_init(PTab,cStream);
  PT_setEParser(PCfg,PLR_getETab,PLR_delTab,NULL);
  return PCfg;
}

void PGM_quitTables(PLR_Tab PTab, Scn_T Scn)
/* release scan and parse tables */
{
  if( Scn != (Scn_T)NULL )    Scn_free(Scn);
  if( PTab != (PLR_Tab)NULL ) PLR_delTab(PTab);
}

PT_Term PGM_parse
        (
          PT_Cfg PCfg, c_string start, 
          c_string shiftfun, c_string reducefun,
          c_bool early, c_bool xaron
        )
/* parse according commandline parameters 
   'start', 'shiftfun', 'reducefun', 'early' and 'xaron' 
*/
{ PT_Term PTree = (PT_Term)NULL;
  if( PCfg != (PT_Cfg)NULL )
  { c_string shiftlib, reducelib, s;
    if( strlen(shiftfun) > 0 )
    { symbol (*fun)(symbol tok, symbol val);
      assert0
      ( 
        (s=strstr(shiftfun,"@")) != (c_string)NULL, "missing shiftfun-library"
      );
      shiftlib = s+1; *s = '\0';
      fun = (symbol (*)(symbol tok, symbol val))Glo_load
            (
              stringToSymbol(shiftlib),stringToSymbol(shiftfun),True
            );
      *s = '@';
      PT_setTokConvFun(PCfg,fun);
    }
    if( strlen(reducefun) > 0 )
    { PT_Term (*fun)(PT_Term Tree);
      assert0
      ( 
        (s=strstr(reducefun,"@")) != (c_string)NULL, "missing reducefun-library"
      );
      reducelib = s+1; *s = '\0';
      fun = (PT_Term (*)(PT_Term Tree))Glo_load
            (
              stringToSymbol(reducelib),stringToSymbol(reducefun),True
            );
      *s = '@';
      PT_setNtmConvFun(PCfg,fun);
    }
    if( ! xaron ) 
    {
      if( ! early )
        PTree = PT_PARSE(PCfg,start);
      else
      {
        PTree = PT_INTERPRETE(PCfg,start);
      }
    }
    else          
    {
      if( ! early )
        PTree = XPT_PARSE(PCfg,start);
      else
      {
        PTree = XPT_INTERPRETE(PCfg,start);
      }
    }
  }
  return PTree;
}

void PGM_printTree(PT_Term PTree, c_string cset, c_bool wprint)
/* print 'PTree' according commandline parameters 'cset' and 'wprint' */
{
  if( PTree != (PT_Term)NULL ) 
  {
    if( strlen(cset) == 0 ) PT_print(PTree);
    else 
    if( wprint ) PT_print_utf8(PTree);
    else         PT_print_rawutf8(PTree);
  }
}

void PGM_scan(Scn_Stream cStream, c_bool output, c_string cset, c_bool wprint)
/* scan 'cStream' 
   output --> print according commandline parameters 'cset' and 'wprint' 
*/
{ 
  if( cStream != (Scn_Stream)NULL )
  { Scn_T    Scn = Stream_scn(cStream);
    c_string s = (c_string)NULL, t = (c_string)NULL;
    int      maxlen = 0, i, j, g = Scn_groups(Scn);
    /* prepare layout */
    for( j=0; j < g || ( j == g && g == 0 ); ++j )
    { Scn_T gscn = ( g == 0 ) ? Scn : Scn_group(Scn,j);
      for (i = 0; i < Scn_tokens(gscn); i++)
      { 
        s      = Scn_tokid(gscn,i);
        maxlen = MAX(maxlen, strlen(s));
        FreeMem(s);
      }
    }
    /* output */
    for
    (
      Stream_next(cStream);
      Stream_ctid(cStream) >= 0;
      Stream_next(cStream)
    )
    if( output )
    {
      s = Stream_ctnam(cStream);
      if( strlen(cset) == 0 || !wprint )
      {
        fprint_raw(STDOUT,symbolToString(Stream_cfil(cStream)),-1);
        fprintf
        (
          STDOUT, ":%06ld:%03ld %s%*s : ",
          Stream_clin(cStream),
          Stream_ccol(cStream),
          s,
          maxlen - strlen(s), ""
        );
      }
      else
      {
        t = (c_string)NewMem
            (
              strlen(symbolToString(Stream_cfil(cStream)))+maxlen+15+1
            );
        sprintf
        (
          t,"%s:%06ld:%03ld %s%*s : ",
          symbolToString(Stream_cfil(cStream)),
          Stream_clin(cStream),
          Stream_ccol(cStream),
          s,
          maxlen - strlen(s), ""
        );
        GS_fprint_utf8(STDOUT,t,False);
        FreeMem(t);
      }
      if( strlen(cset) == 0 )
      {
        fprintf(STDOUT,"%s\n", symbolToString(Stream_csym(cStream)));
      }
      else
      {
        if( wprint )
        {
          GS_fprint_utf8(STDOUT,symbolToString(Stream_csym(cStream)),False);
          GS_fprint_utf8(STDOUT,"\n",False);
        }
        else 
        {
          GS_fprint_utf8(STDOUT,symbolToString(Stream_csym(cStream)),True);
          fprintf(STDOUT,"\n");
        }
      }
    }
  }
}

