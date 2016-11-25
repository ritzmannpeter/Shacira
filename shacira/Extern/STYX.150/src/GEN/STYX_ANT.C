/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [styx_ant.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls_abs.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;

void styx_initSymbols()
{
  GLS_init();
  CfgSyms = (symbol*)NewMem(sizeof(symbol)*62);
  PrdSyms = (symbol*)NewMem(sizeof(symbol)*49);

  CfgSyms[0] = stringToSymbol("Parenthesis");
  CfgSyms[1] = stringToSymbol("Comment");
  CfgSyms[2] = stringToSymbol("Ide");
  CfgSyms[3] = stringToSymbol("Nat");
  CfgSyms[4] = stringToSymbol("Opr");
  CfgSyms[5] = stringToSymbol("Set");
  CfgSyms[6] = stringToSymbol("Seq");
  CfgSyms[7] = stringToSymbol("MacInc");
  CfgSyms[8] = stringToSymbol("MacDfn");
  CfgSyms[9] = stringToSymbol("MacSep");
  CfgSyms[10] = stringToSymbol("MacCond");
  CfgSyms[11] = stringToSymbol("Language");
  CfgSyms[12] = stringToSymbol("Regular");
  CfgSyms[13] = stringToSymbol("Grammar");
  CfgSyms[14] = stringToSymbol("Context");
  CfgSyms[15] = stringToSymbol("Free");
  CfgSyms[16] = stringToSymbol("=");
  CfgSyms[17] = stringToSymbol("let");
  CfgSyms[18] = stringToSymbol("tok");
  CfgSyms[19] = stringToSymbol("ign");
  CfgSyms[20] = stringToSymbol("com");
  CfgSyms[21] = stringToSymbol("lan");
  CfgSyms[22] = stringToSymbol("[");
  CfgSyms[23] = stringToSymbol("ica");
  CfgSyms[24] = stringToSymbol("]");
  CfgSyms[25] = stringToSymbol("|");
  CfgSyms[26] = stringToSymbol("-");
  CfgSyms[27] = stringToSymbol("{");
  CfgSyms[28] = stringToSymbol("}");
  CfgSyms[29] = stringToSymbol("+");
  CfgSyms[30] = stringToSymbol("..");
  CfgSyms[31] = stringToSymbol("(");
  CfgSyms[32] = stringToSymbol(")");
  CfgSyms[33] = stringToSymbol("xtop");
  CfgSyms[34] = stringToSymbol("start");
  CfgSyms[35] = stringToSymbol("err");
  CfgSyms[36] = stringToSymbol(":");
  CfgSyms[37] = stringToSymbol("?");
  CfgSyms[38] = stringToSymbol("!");
  CfgSyms[39] = stringToSymbol("other");
  CfgSyms[40] = stringToSymbol("Source");
  CfgSyms[41] = stringToSymbol("OptCfg");
  CfgSyms[42] = stringToSymbol("QlxDfns");
  CfgSyms[43] = stringToSymbol("QlxDfn");
  CfgSyms[44] = stringToSymbol("QlxCat");
  CfgSyms[45] = stringToSymbol("QlxOpt");
  CfgSyms[46] = stringToSymbol("Exp");
  CfgSyms[47] = stringToSymbol("Exp1");
  CfgSyms[48] = stringToSymbol("Exp2");
  CfgSyms[49] = stringToSymbol("Exp3");
  CfgSyms[50] = stringToSymbol("Exp4");
  CfgSyms[51] = stringToSymbol("Dfns");
  CfgSyms[52] = stringToSymbol("Dfn");
  CfgSyms[53] = stringToSymbol("Cat0");
  CfgSyms[54] = stringToSymbol("Cat");
  CfgSyms[55] = stringToSymbol("DfnOpt");
  CfgSyms[56] = stringToSymbol("Prds");
  CfgSyms[57] = stringToSymbol("Lay");
  CfgSyms[58] = stringToSymbol("Prd");
  CfgSyms[59] = stringToSymbol("Mbrs");
  CfgSyms[60] = stringToSymbol("Mbr");
  CfgSyms[61] = stringToSymbol("styx");

  PrdSyms[0] = stringToSymbol("root");
  PrdSyms[1] = stringToSymbol("nul");
  PrdSyms[2] = stringToSymbol("cfg");
  PrdSyms[3] = stringToSymbol("nil");
  PrdSyms[4] = stringToSymbol("cons");
  PrdSyms[5] = stringToSymbol("defn");
  PrdSyms[6] = stringToSymbol("letC");
  PrdSyms[7] = stringToSymbol("tokC");
  PrdSyms[8] = stringToSymbol("ignC");
  PrdSyms[9] = stringToSymbol("comC");
  PrdSyms[10] = stringToSymbol("ctxC");
  PrdSyms[11] = stringToSymbol("non");
  PrdSyms[12] = stringToSymbol("ignca");
  PrdSyms[13] = stringToSymbol("union");
  PrdSyms[14] = stringToSymbol("diff");
  PrdSyms[15] = stringToSymbol("ign1");
  PrdSyms[16] = stringToSymbol("conc");
  PrdSyms[17] = stringToSymbol("ign1");
  PrdSyms[18] = stringToSymbol("opt");
  PrdSyms[19] = stringToSymbol("star");
  PrdSyms[20] = stringToSymbol("plus");
  PrdSyms[21] = stringToSymbol("ign1");
  PrdSyms[22] = stringToSymbol("ign1");
  PrdSyms[23] = stringToSymbol("range");
  PrdSyms[24] = stringToSymbol("ign2");
  PrdSyms[25] = stringToSymbol("sequ");
  PrdSyms[26] = stringToSymbol("set");
  PrdSyms[27] = stringToSymbol("ident");
  PrdSyms[28] = stringToSymbol("nil");
  PrdSyms[29] = stringToSymbol("cons");
  PrdSyms[30] = stringToSymbol("defn");
  PrdSyms[31] = stringToSymbol("bgnC");
  PrdSyms[32] = stringToSymbol("letC");
  PrdSyms[33] = stringToSymbol("bgnC");
  PrdSyms[34] = stringToSymbol("ign0");
  PrdSyms[35] = stringToSymbol("non");
  PrdSyms[36] = stringToSymbol("errnt");
  PrdSyms[37] = stringToSymbol("nil");
  PrdSyms[38] = stringToSymbol("cons");
  PrdSyms[39] = stringToSymbol("dft");
  PrdSyms[40] = stringToSymbol("rec");
  PrdSyms[41] = stringToSymbol("grp");
  PrdSyms[42] = stringToSymbol("prod");
  PrdSyms[43] = stringToSymbol("nil");
  PrdSyms[44] = stringToSymbol("cons");
  PrdSyms[45] = stringToSymbol("ntm");
  PrdSyms[46] = stringToSymbol("tkm");
  PrdSyms[47] = stringToSymbol("else");
  PrdSyms[48] = stringToSymbol("Start_Source");
}

void styx_quitSymbols()
{
  if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
  if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractHugeType( styx );

AbstractHugeType( styxSource );
AbstractHugeType( styxOptCfg );
AbstractHugeType( styxQlxDfn );
AbstractHugeType( styxQlxCat );
AbstractHugeType( styxQlxOpt );
AbstractHugeType( styxExp  );
AbstractHugeType( styxDfn  );
AbstractHugeType( styxCat  );
AbstractHugeType( styxDfnOpt );
AbstractHugeType( styxLay  );
AbstractHugeType( styxPrd  );
AbstractHugeType( styxMbr  );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Tstyx_Ide(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[2];
}

c_bool Tstyx_Set(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[5];
}

c_bool Tstyx_Seq(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[6];
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool styx_styx(PT_Abs_Term x, styx* x1)
{
  if( PT_Abs_nonterm(x) == CfgSyms[61] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styx)x;
    return True;
  }
  return False;
}

c_bool styx_Source(PT_Abs_Term x, styxSource* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[40] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxSource)x;
    return True;
  }
  return False;
}

c_bool styx_OptCfg(PT_Abs_Term x, styxOptCfg* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[41] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxOptCfg)x;
    return True;
  }
  return False;
}

c_bool styx_QlxDfn(PT_Abs_Term x, styxQlxDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[43] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxQlxDfn)x;
    return True;
  }
  return False;
}

c_bool styx_QlxCat(PT_Abs_Term x, styxQlxCat* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[44] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxQlxCat)x;
    return True;
  }
  return False;
}

c_bool styx_QlxOpt(PT_Abs_Term x, styxQlxOpt* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[45] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxQlxOpt)x;
    return True;
  }
  return False;
}

c_bool styx_Exp(PT_Abs_Term x, styxExp* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[47]
    || PT_Abs_nonterm(x) == CfgSyms[49]
    || PT_Abs_nonterm(x) == CfgSyms[48]
    || PT_Abs_nonterm(x) == CfgSyms[50]
    || PT_Abs_nonterm(x) == CfgSyms[46] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxExp)x;
    return True;
  }
  return False;
}

c_bool styx_Dfn(PT_Abs_Term x, styxDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[52] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxDfn)x;
    return True;
  }
  return False;
}

c_bool styx_Cat(PT_Abs_Term x, styxCat* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[53]
    || PT_Abs_nonterm(x) == CfgSyms[54] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxCat)x;
    return True;
  }
  return False;
}

c_bool styx_DfnOpt(PT_Abs_Term x, styxDfnOpt* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[55] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxDfnOpt)x;
    return True;
  }
  return False;
}

c_bool styx_Lay(PT_Abs_Term x, styxLay* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[57] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxLay)x;
    return True;
  }
  return False;
}

c_bool styx_Prd(PT_Abs_Term x, styxPrd* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[58] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxPrd)x;
    return True;
  }
  return False;
}

c_bool styx_Mbr(PT_Abs_Term x, styxMbr* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[60] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxMbr)x;
    return True;
  }
  return False;
}

/*I--------------------------------- styx --------------------------------- */

c_bool styx_Start_Source(styx x, styxSource* x1)
#define styx_Start_0   styx_Start_Source
{
  assert0( PT_Abs_nonterm(x) == CfgSyms[61], "styx expected" );
  if( PT_Abs_product(x) != PrdSyms[48] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL )
    *x1 = (styxSource)PT_Abs_part(x,0);
  return True;
}

/*I-------------------------------- Source -------------------------------- */

c_bool styxSource_root(styxSource x, GLS_Tok* x1, GLS_Lst(styxQlxDfn)* x2,
                       styxOptCfg* x3)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[40], "Source expected" );
  if( PT_Abs_product(x) != PrdSyms[0] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Lst(styxQlxDfn))PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (styxOptCfg)PT_Abs_part(x,2);
  return True;
}

/*I-------------------------------- OptCfg -------------------------------- */

c_bool styxOptCfg_nul(styxOptCfg x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[41], "OptCfg expected" );
  if( PT_Abs_product(x) != PrdSyms[1] ) return False;
  return True;
}

c_bool styxOptCfg_cfg(styxOptCfg x, GLS_Lst(styxDfn)* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[41], "OptCfg expected" );
  if( PT_Abs_product(x) != PrdSyms[2] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(styxDfn))PT_Abs_part(x,0);
  return True;
}

/*I-------------------------------- QlxDfn -------------------------------- */

c_bool styxQlxDfn_defn(styxQlxDfn x, styxQlxCat* x1, styxQlxOpt* x2,
                       GLS_Tok* x3, styxExp* x4)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "QlxDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[5] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxQlxCat)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (styxQlxOpt)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Tok)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (styxExp)PT_Abs_part(x,3);
  return True;
}

/*I-------------------------------- QlxCat -------------------------------- */

c_bool styxQlxCat_tokC(styxQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[44], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[7] ) return False;
  return True;
}

c_bool styxQlxCat_letC(styxQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[44], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[6] ) return False;
  return True;
}

c_bool styxQlxCat_ctxC(styxQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[44], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[10] ) return False;
  return True;
}

c_bool styxQlxCat_comC(styxQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[44], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[9] ) return False;
  return True;
}

c_bool styxQlxCat_ignC(styxQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[44], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[8] ) return False;
  return True;
}

/*I-------------------------------- QlxOpt -------------------------------- */

c_bool styxQlxOpt_ignca(styxQlxOpt x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[45], "QlxOpt expected" );
  if( PT_Abs_product(x) != PrdSyms[12] ) return False;
  return True;
}

c_bool styxQlxOpt_non(styxQlxOpt x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[45], "QlxOpt expected" );
  if( PT_Abs_product(x) != PrdSyms[11] ) return False;
  return True;
}

/*I--------------------------------- Exp ---------------------------------- */

c_bool styxExp_star(styxExp x, styxExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[19] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxExp)PT_Abs_part(x,0);
  return True;
}

c_bool styxExp_union(styxExp x, styxExp* x1, styxExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[13] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (styxExp)PT_Abs_part(x,1);
  return True;
}

c_bool styxExp_set(styxExp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[26] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool styxExp_opt(styxExp x, styxExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[18] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxExp)PT_Abs_part(x,0);
  return True;
}

c_bool styxExp_diff(styxExp x, styxExp* x1, styxExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[14] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (styxExp)PT_Abs_part(x,1);
  return True;
}

c_bool styxExp_range(styxExp x, styxExp* x1, styxExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[23] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (styxExp)PT_Abs_part(x,1);
  return True;
}

c_bool styxExp_ident(styxExp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[27] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool styxExp_plus(styxExp x, styxExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[20] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxExp)PT_Abs_part(x,0);
  return True;
}

c_bool styxExp_conc(styxExp x, styxExp* x1, styxExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[16] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (styxExp)PT_Abs_part(x,1);
  return True;
}

c_bool styxExp_sequ(styxExp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[49]
        || PT_Abs_nonterm(x) == CfgSyms[48]
        || PT_Abs_nonterm(x) == CfgSyms[50]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[25] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Dfn ---------------------------------- */

c_bool styxDfn_defn(styxDfn x, styxCat* x1, styxDfnOpt* x2,
                    GLS_Tok* x3, GLS_Lst(styxPrd)* x4)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "Dfn expected" );
  if( PT_Abs_product(x) != PrdSyms[30] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxCat)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (styxDfnOpt)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Tok)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (GLS_Lst(styxPrd))PT_Abs_part(x,3);
  return True;
}

/*I--------------------------------- Cat ---------------------------------- */

c_bool styxCat_letC(styxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[53]
        || PT_Abs_nonterm(x) == CfgSyms[54], "Cat expected" );
  if( PT_Abs_product(x) != PrdSyms[32] ) return False;
  return True;
}

c_bool styxCat_bgnC(styxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[53]
        || PT_Abs_nonterm(x) == CfgSyms[54], "Cat expected" );
  if( PT_Abs_product(x) != PrdSyms[31] ) return False;
  return True;
}

/*I-------------------------------- DfnOpt -------------------------------- */

c_bool styxDfnOpt_non(styxDfnOpt x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "DfnOpt expected" );
  if( PT_Abs_product(x) != PrdSyms[35] ) return False;
  return True;
}

c_bool styxDfnOpt_errnt(styxDfnOpt x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "DfnOpt expected" );
  if( PT_Abs_product(x) != PrdSyms[36] ) return False;
  return True;
}

/*I--------------------------------- Lay ---------------------------------- */

c_bool styxLay_grp(styxLay x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[57], "Lay expected" );
  if( PT_Abs_product(x) != PrdSyms[41] ) return False;
  return True;
}

c_bool styxLay_rec(styxLay x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[57], "Lay expected" );
  if( PT_Abs_product(x) != PrdSyms[40] ) return False;
  return True;
}

c_bool styxLay_dft(styxLay x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[57], "Lay expected" );
  if( PT_Abs_product(x) != PrdSyms[39] ) return False;
  return True;
}

/*I--------------------------------- Prd ---------------------------------- */

c_bool styxPrd_prod(styxPrd x, styxLay* x1, GLS_Tok* x2,
                    GLS_Lst(styxMbr)* x3)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[58], "Prd expected" );
  if( PT_Abs_product(x) != PrdSyms[42] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (styxLay)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Tok)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Lst(styxMbr))PT_Abs_part(x,2);
  return True;
}

/*I--------------------------------- Mbr ---------------------------------- */

c_bool styxMbr_ntm(styxMbr x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[60], "Mbr expected" );
  if( PT_Abs_product(x) != PrdSyms[45] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool styxMbr_tkm(styxMbr x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[60], "Mbr expected" );
  if( PT_Abs_product(x) != PrdSyms[46] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool styxMbr_else(styxMbr x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[60], "Mbr expected" );
  if( PT_Abs_product(x) != PrdSyms[47] ) return False;
  return True;
}
