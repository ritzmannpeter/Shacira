/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [styx_int.h]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef styx_int_INCL
#define styx_int_INCL


#include "ptm.h"
#include "gls.h"


#ifdef __cplusplus
extern "C" {
#endif


/* --------------------- symbol objects - init & quit --------------------- */

void styx_initSymbols();               /*                                   */
void styx_quitSymbols();               /*                                   */

/* -------------------------- Types & Constants --------------------------- */

AbstractType( styx );

AbstractType( styxSource );
AbstractType( styxOptCfg );
AbstractType( styxQlxDfn );
AbstractType( styxQlxCat );
AbstractType( styxQlxGrp );
AbstractType( styxQlxOpt );
AbstractType( styxExp  );
AbstractType( styxOptNat );
AbstractType( styxLimit );
AbstractType( styxDfn  );
AbstractType( styxCat  );
AbstractType( styxDfnOpt );
AbstractType( styxLay  );
AbstractType( styxPrd  );
AbstractType( styxMbr  );

/* --------------------------- Access to Tokens --------------------------- */

c_bool Tstyx_Ide(GLS_Tok x);           /*                                   */
c_bool Tstyx_Nat(GLS_Tok x);           /*                                   */
c_bool Tstyx_Set(GLS_Tok x);           /*                                   */
c_bool Tstyx_Seq(GLS_Tok x);           /*                                   */

/* --------------------------- Access to Terms ---------------------------- */

c_bool styx_styx(PT_Term x, styx* x1);         /*                           */
c_bool styx_Source(PT_Term x, styxSource* x1); /*                           */
c_bool styx_OptCfg(PT_Term x, styxOptCfg* x1); /*                           */
c_bool styx_QlxDfn(PT_Term x, styxQlxDfn* x1); /*                           */
c_bool styx_QlxCat(PT_Term x, styxQlxCat* x1); /*                           */
c_bool styx_QlxGrp(PT_Term x, styxQlxGrp* x1); /*                           */
c_bool styx_QlxOpt(PT_Term x, styxQlxOpt* x1); /*                           */
c_bool styx_Exp(PT_Term x, styxExp* x1);       /*                           */
c_bool styx_OptNat(PT_Term x, styxOptNat* x1); /*                           */
c_bool styx_Limit(PT_Term x, styxLimit* x1);   /*                           */
c_bool styx_Dfn(PT_Term x, styxDfn* x1);       /*                           */
c_bool styx_Cat(PT_Term x, styxCat* x1);       /*                           */
c_bool styx_DfnOpt(PT_Term x, styxDfnOpt* x1); /*                           */
c_bool styx_Lay(PT_Term x, styxLay* x1);       /*                           */
c_bool styx_Prd(PT_Term x, styxPrd* x1);       /*                           */
c_bool styx_Mbr(PT_Term x, styxMbr* x1);       /*                           */

/* --------------------------------- styx --------------------------------- */

c_bool styx_Start_Source(styx x, styxSource* x1)
#define styx_Start_0   styx_Start_Source
;


/* -------------------------------- Source -------------------------------- */

c_bool styxSource_root(styxSource x, GLS_Tok* x1, GLS_Lst(styxQlxDfn)* x2,
                       styxOptCfg* x3)
;


/* -------------------------------- OptCfg -------------------------------- */

c_bool styxOptCfg_non(styxOptCfg x);                       /*               */
c_bool styxOptCfg_cfg(styxOptCfg x, GLS_Lst(styxDfn)* x1); /*               */

/* -------------------------------- QlxDfn -------------------------------- */

c_bool styxQlxDfn_igrp(styxQlxDfn x, GLS_Tok* x1); /*                       */

c_bool styxQlxDfn_defn(styxQlxDfn x, styxQlxCat* x1, styxQlxOpt* x2,
                       styxQlxGrp* x3, GLS_Tok* x4,
                       styxQlxGrp* x5, styxExp* x6)
;

c_bool styxQlxDfn_mgrp(styxQlxDfn x, GLS_Tok* x1, GLS_Lst(GLS_Tok)* x2);/*  */
c_bool styxQlxDfn_xgrp(styxQlxDfn x, GLS_Tok* x1); /*                       */

/* -------------------------------- QlxCat -------------------------------- */

c_bool styxQlxCat_tokC(styxQlxCat x);  /*                                   */
c_bool styxQlxCat_indC(styxQlxCat x);  /*                                   */
c_bool styxQlxCat_ignC(styxQlxCat x);  /*                                   */
c_bool styxQlxCat_comC(styxQlxCat x);  /*                                   */
c_bool styxQlxCat_lanC(styxQlxCat x);  /*                                   */
c_bool styxQlxCat_letC(styxQlxCat x);  /*                                   */

/* -------------------------------- QlxGrp -------------------------------- */

c_bool styxQlxGrp_pgrp(styxQlxGrp x, GLS_Tok* x1); /*                       */
c_bool styxQlxGrp_non(styxQlxGrp x);               /*                       */
c_bool styxQlxGrp_pigrp(styxQlxGrp x);             /*                       */
c_bool styxQlxGrp_grp(styxQlxGrp x, GLS_Tok* x1);  /*                       */
c_bool styxQlxGrp_igrp(styxQlxGrp x);              /*                       */
c_bool styxQlxGrp_pop(styxQlxGrp x);               /*                       */

/* -------------------------------- QlxOpt -------------------------------- */

c_bool styxQlxOpt_ignca(styxQlxOpt x); /*                                   */
c_bool styxQlxOpt_non(styxQlxOpt x);   /*                                   */

/* --------------------------------- Exp ---------------------------------- */

c_bool styxExp_opt(styxExp x, styxExp* x1);                  /*             */
c_bool styxExp_plusn(styxExp x, styxExp* x1, styxLimit* x2); /*             */
c_bool styxExp_plus0(styxExp x, styxExp* x1);                /*             */
c_bool styxExp_star(styxExp x, styxExp* x1);                 /*             */
c_bool styxExp_quot(styxExp x, styxExp* x1, styxExp* x2);    /*             */
c_bool styxExp_plus(styxExp x, styxExp* x1);                 /*             */

c_bool styxExp_epat(styxExp x, styxExp* x1, GLS_Tok* x2,
                    styxExp* x3)
;

c_bool styxExp_union(styxExp x, styxExp* x1, styxExp* x2);   /*             */
c_bool styxExp_sequ(styxExp x, GLS_Tok* x1);                 /*             */

c_bool styxExp_dyck(styxExp x, styxExp* x1, styxExp* x2,
                    styxExp* x3)
;

c_bool styxExp_non(styxExp x);                               /*             */
c_bool styxExp_range(styxExp x, styxExp* x1, styxExp* x2);   /*             */
c_bool styxExp_ident(styxExp x, GLS_Tok* x1);                /*             */
c_bool styxExp_diff(styxExp x, styxExp* x1, styxExp* x2);    /*             */
c_bool styxExp_set(styxExp x, GLS_Tok* x1);                  /*             */

c_bool styxExp_spat(styxExp x, styxExp* x1, GLS_Tok* x2,
                    styxExp* x3)
;

c_bool styxExp_conc(styxExp x, styxExp* x1, styxExp* x2);    /*             */

/* -------------------------------- OptNat -------------------------------- */

c_bool styxOptNat_non(styxOptNat x);              /*                        */
c_bool styxOptNat_nat(styxOptNat x, GLS_Tok* x1); /*                        */

/* -------------------------------- Limit --------------------------------- */

c_bool styxLimit_ntime(styxLimit x, GLS_Tok* x1);                 /*        */
c_bool styxLimit_range(styxLimit x, GLS_Tok* x1, styxOptNat* x2); /*        */

/* --------------------------------- Dfn ---------------------------------- */

c_bool styxDfn_defn(styxDfn x, styxCat* x1, styxDfnOpt* x2,
                    GLS_Tok* x3, GLS_Lst(styxPrd)* x4)
;


/* --------------------------------- Cat ---------------------------------- */

c_bool styxCat_letC(styxCat x);        /*                                   */
c_bool styxCat_bgnC(styxCat x);        /*                                   */

/* -------------------------------- DfnOpt -------------------------------- */

c_bool styxDfnOpt_errnt(styxDfnOpt x); /*                                   */
c_bool styxDfnOpt_non(styxDfnOpt x);   /*                                   */

/* --------------------------------- Lay ---------------------------------- */

c_bool styxLay_dft(styxLay x);         /*                                   */
c_bool styxLay_rec(styxLay x);         /*                                   */
c_bool styxLay_grp(styxLay x);         /*                                   */

/* --------------------------------- Prd ---------------------------------- */

c_bool styxPrd_prod(styxPrd x, styxLay* x1, GLS_Tok* x2,
                    GLS_Lst(styxMbr)* x3)
;


/* --------------------------------- Mbr ---------------------------------- */

c_bool styxMbr_else(styxMbr x);             /*                              */
c_bool styxMbr_tkm(styxMbr x, GLS_Tok* x1); /*                              */
c_bool styxMbr_ntm(styxMbr x, GLS_Tok* x1); /*                              */


#ifdef __cplusplus
}
#endif

#endif
