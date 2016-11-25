/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [meta_prs.c]           Meta-Source Parser (--> meta expressions)         */
/*                                                                          */
/* Copyright (c) 1999 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "otab.h"

#include "symbols.h"
#include "scn_base.h"
#include "ptm_gen.h"
#include "literal.h"
#include "hmap.h"
#include "hset.h"
#include "sink.h"
#include "pathes.h"

#include "meta_exp.h"

#include "meta_lim.h"
#include "meta_pim.h"
#include "meta_int.h"

/*!
  <p><b>under construction</b>
*/

/*I------------------------- Types & Macros ----------------------------- */

AbstractType(MSpec_T); // abstract meta source specification type



/*I------------------------- Meta Specification Parsing ----------------- */


static void MPrs_printErrMsg(c_string msg)
{
  fprintf(STDERR,"%s",msg);
}

static MSpec_T MPrs_getSpec(Scn_Stream cstream, PT_Diag diag)
/* read meta source specification */
{ Scn_T   scn = Stream_scn(cstream);
  PLR_Tab plr; 
  PT_Cfg  cfg;
  PT_Term tree; 
  MSpec_T mspec = (MSpec_T)NULL;
  plr     = PLR_get_meta();
  cfg     = PT_init(plr,cstream);
  PT_setDiagFun(cfg,diag);
  tree    = PT_PARSE(cfg,"Source");
  PT_diag_setErrorCnt(diag,PT_synErrorCnt(cfg));
  PT_quit(cfg);
  Stream_close(cstream);
  Stream_free(cstream);
  Scn_free(scn);
  PLR_delTab(plr);
  if (PT_diag_errorCnt(diag) == 0)
  { metaSource       src;
    GLS_Lst(metaElm) elmlst = (GLS_Lst(metaElm))NULL;
    assert0(meta_Start_Source((meta)tree,&src),"");
    assert0(metaSource_dfn(src,&elmlst),"");
    mspec = (MSpec_T)elmlst;
  }
  if (PT_diag_errorCnt(diag) > 0)
  { 
    PT_diag_msg((PT_Term)NULL,diag,"Totally %d errors",PT_diag_errorCnt(diag));
  }
  return mspec;
}


MSpec_T MPrs_getSpecFromPath(c_string path, void (*prMsg)(c_string msg))
/* loads meta source specification 'path';
   uses 'prMsg' for error reporting
*/
{ Scn_T      scn; 
  Scn_Stream cstream; 
  MSpec_T    mspec = (MSpec_T)NULL; 
  PT_Diag    diag;
  BUG_NULL(path);
  diag = PT_diag_init(prMsg==NULL?MPrs_printErrMsg:prMsg);
  meta_initSymbols();
  Scn_get_meta(&scn); 
  if( IsPath(path) )
  {
    cstream = Stream_file(scn,"",path,"");
    mspec = MPrs_getSpec(cstream,diag);
  }
  else
  {
    PT_diag_msg((PT_Term)NULL,diag,"missing %s",path);
  }
  meta_quitSymbols();
  PT_diag_quit(diag);
  return mspec;
}


/*I------------------------- Meta-Source Parsing ------------------------ */


