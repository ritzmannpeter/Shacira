/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [styx_int.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;
static int initcount_styx = 0;

void styx_initSymbols()
{
  if( initcount_styx == 0 )
  {
    GLS_init();
    assert0(CfgSyms == (symbol*)NULL,"styxSymbols already initialized");
    CfgSyms = (symbol*)NewMem(sizeof(symbol)*74);
    PrdSyms = (symbol*)NewMem(sizeof(symbol)*64);

    CfgSyms[0] = stringToSymbol("Parenthesis");
    CfgSyms[1] = stringToSymbol("Comment");
    CfgSyms[2] = stringToSymbol("Ide");
    CfgSyms[3] = stringToSymbol("Nat");
    CfgSyms[4] = stringToSymbol("Opr");
    CfgSyms[5] = stringToSymbol("Set");
    CfgSyms[6] = stringToSymbol("Seq");
    CfgSyms[7] = stringToSymbol("MacInc");
    CfgSyms[8] = stringToSymbol("MacDel");
    CfgSyms[9] = stringToSymbol("MacDfn");
    CfgSyms[10] = stringToSymbol("MacSep");
    CfgSyms[11] = stringToSymbol("MacCond");
    CfgSyms[12] = stringToSymbol("Language");
    CfgSyms[13] = stringToSymbol("Context");
    CfgSyms[14] = stringToSymbol("Free");
    CfgSyms[15] = stringToSymbol("Grammar");
    CfgSyms[16] = stringToSymbol("Regular");
    CfgSyms[17] = stringToSymbol("=");
    CfgSyms[18] = stringToSymbol("InGroup");
    CfgSyms[19] = stringToSymbol("ExGroup");
    CfgSyms[20] = stringToSymbol("let");
    CfgSyms[21] = stringToSymbol("tok");
    CfgSyms[22] = stringToSymbol("ign");
    CfgSyms[23] = stringToSymbol("com");
    CfgSyms[24] = stringToSymbol("lan");
    CfgSyms[25] = stringToSymbol("ind");
    CfgSyms[26] = stringToSymbol(":");
    CfgSyms[27] = stringToSymbol("!");
    CfgSyms[28] = stringToSymbol("[");
    CfgSyms[29] = stringToSymbol("ica");
    CfgSyms[30] = stringToSymbol("]");
    CfgSyms[31] = stringToSymbol("<");
    CfgSyms[32] = stringToSymbol(">");
    CfgSyms[33] = stringToSymbol("|");
    CfgSyms[34] = stringToSymbol("-");
    CfgSyms[35] = stringToSymbol("{");
    CfgSyms[36] = stringToSymbol("}");
    CfgSyms[37] = stringToSymbol("+");
    CfgSyms[38] = stringToSymbol("..");
    CfgSyms[39] = stringToSymbol("(");
    CfgSyms[40] = stringToSymbol(")");
    CfgSyms[41] = stringToSymbol("xtop");
    CfgSyms[42] = stringToSymbol("start");
    CfgSyms[43] = stringToSymbol("err");
    CfgSyms[44] = stringToSymbol("?");
    CfgSyms[45] = stringToSymbol("other");
    CfgSyms[46] = stringToSymbol("Source");
    CfgSyms[47] = stringToSymbol("OptCfg");
    CfgSyms[48] = stringToSymbol("QlxDfns0");
    CfgSyms[49] = stringToSymbol("QlxDfns");
    CfgSyms[50] = stringToSymbol("QlxDfn");
    CfgSyms[51] = stringToSymbol("QlxCat");
    CfgSyms[52] = stringToSymbol("QlxGrp");
    CfgSyms[53] = stringToSymbol("QlxGrp0");
    CfgSyms[54] = stringToSymbol("QlxGrp1");
    CfgSyms[55] = stringToSymbol("QlxOpt");
    CfgSyms[56] = stringToSymbol("ExpDyck");
    CfgSyms[57] = stringToSymbol("Exp0");
    CfgSyms[58] = stringToSymbol("Exp");
    CfgSyms[59] = stringToSymbol("Exp1");
    CfgSyms[60] = stringToSymbol("Exp2");
    CfgSyms[61] = stringToSymbol("Exp3");
    CfgSyms[62] = stringToSymbol("Exp4");
    CfgSyms[63] = stringToSymbol("Dfns");
    CfgSyms[64] = stringToSymbol("Dfn");
    CfgSyms[65] = stringToSymbol("Cat0");
    CfgSyms[66] = stringToSymbol("Cat");
    CfgSyms[67] = stringToSymbol("DfnOpt");
    CfgSyms[68] = stringToSymbol("Prds");
    CfgSyms[69] = stringToSymbol("Lay");
    CfgSyms[70] = stringToSymbol("Prd");
    CfgSyms[71] = stringToSymbol("Mbrs");
    CfgSyms[72] = stringToSymbol("Mbr");
    CfgSyms[73] = stringToSymbol("styx");

    PrdSyms[0] = stringToSymbol("root");
    PrdSyms[1] = stringToSymbol("nul");
    PrdSyms[2] = stringToSymbol("cfg");
    PrdSyms[3] = stringToSymbol("nil");
    PrdSyms[4] = stringToSymbol("ign0");
    PrdSyms[5] = stringToSymbol("nil");
    PrdSyms[6] = stringToSymbol("cons");
    PrdSyms[7] = stringToSymbol("defn");
    PrdSyms[8] = stringToSymbol("igrp");
    PrdSyms[9] = stringToSymbol("xgrp");
    PrdSyms[10] = stringToSymbol("letC");
    PrdSyms[11] = stringToSymbol("tokC");
    PrdSyms[12] = stringToSymbol("ignC");
    PrdSyms[13] = stringToSymbol("comC");
    PrdSyms[14] = stringToSymbol("lanC");
    PrdSyms[15] = stringToSymbol("indC");
    PrdSyms[16] = stringToSymbol("non");
    PrdSyms[17] = stringToSymbol("grp");
    PrdSyms[18] = stringToSymbol("ign0");
    PrdSyms[19] = stringToSymbol("grp");
    PrdSyms[20] = stringToSymbol("igrp");
    PrdSyms[21] = stringToSymbol("ign0");
    PrdSyms[22] = stringToSymbol("non");
    PrdSyms[23] = stringToSymbol("ignca");
    PrdSyms[24] = stringToSymbol("dyck");
    PrdSyms[25] = stringToSymbol("ign0");
    PrdSyms[26] = stringToSymbol("nul");
    PrdSyms[27] = stringToSymbol("ign0");
    PrdSyms[28] = stringToSymbol("union");
    PrdSyms[29] = stringToSymbol("diff");
    PrdSyms[30] = stringToSymbol("ign1");
    PrdSyms[31] = stringToSymbol("conc");
    PrdSyms[32] = stringToSymbol("ign1");
    PrdSyms[33] = stringToSymbol("opt");
    PrdSyms[34] = stringToSymbol("star");
    PrdSyms[35] = stringToSymbol("plus");
    PrdSyms[36] = stringToSymbol("ign1");
    PrdSyms[37] = stringToSymbol("ign1");
    PrdSyms[38] = stringToSymbol("range");
    PrdSyms[39] = stringToSymbol("ign2");
    PrdSyms[40] = stringToSymbol("sequ");
    PrdSyms[41] = stringToSymbol("set");
    PrdSyms[42] = stringToSymbol("ident");
    PrdSyms[43] = stringToSymbol("nil");
    PrdSyms[44] = stringToSymbol("cons");
    PrdSyms[45] = stringToSymbol("defn");
    PrdSyms[46] = stringToSymbol("bgnC");
    PrdSyms[47] = stringToSymbol("letC");
    PrdSyms[48] = stringToSymbol("bgnC");
    PrdSyms[49] = stringToSymbol("ign0");
    PrdSyms[50] = stringToSymbol("non");
    PrdSyms[51] = stringToSymbol("errnt");
    PrdSyms[52] = stringToSymbol("nil");
    PrdSyms[53] = stringToSymbol("cons");
    PrdSyms[54] = stringToSymbol("dft");
    PrdSyms[55] = stringToSymbol("rec");
    PrdSyms[56] = stringToSymbol("grp");
    PrdSyms[57] = stringToSymbol("prod");
    PrdSyms[58] = stringToSymbol("nil");
    PrdSyms[59] = stringToSymbol("cons");
    PrdSyms[60] = stringToSymbol("ntm");
    PrdSyms[61] = stringToSymbol("tkm");
    PrdSyms[62] = stringToSymbol("else");
    PrdSyms[63] = stringToSymbol("Start_Source");
  }
  ++initcount_styx;
}

void styx_quitSymbols()
{
  --initcount_styx;
  if( initcount_styx == 0 )
  {
    assert0(CfgSyms != (symbol*)NULL,"styxSymbols not initialized");
    if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
    CfgSyms = (symbol*)NULL;
    if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
    PrdSyms = (symbol*)NULL;
  }
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractType( styx );

AbstractType( styxSource );
AbstractType( styxOptCfg );
AbstractType( styxQlxDfn );
AbstractType( styxQlxCat );
AbstractType( styxQlxGrp );
AbstractType( styxQlxOpt );
AbstractType( styxExp  );
AbstractType( styxDfn  );
AbstractType( styxCat  );
AbstractType( styxDfnOpt );
AbstractType( styxLay  );
AbstractType( styxPrd  );
AbstractType( styxMbr  );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Tstyx_Ide(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[2]) );
}

c_bool Tstyx_Set(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[5]) );
}

c_bool Tstyx_Seq(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[6]) );
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool styx_styx(PT_Term x, styx* x1)
{
  if( PT_THISNTM(x, CfgSyms[73]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styx)x;
    return True;
  }
  return False;
}

c_bool styx_Source(PT_Term x, styxSource* x1)
{
  if(  PT_THISNTM(x, CfgSyms[46]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxSource)x;
    return True;
  }
  return False;
}

c_bool styx_OptCfg(PT_Term x, styxOptCfg* x1)
{
  if(  PT_THISNTM(x, CfgSyms[47]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxOptCfg)x;
    return True;
  }
  return False;
}

c_bool styx_QlxDfn(PT_Term x, styxQlxDfn* x1)
{
  if(  PT_THISNTM(x, CfgSyms[50]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxQlxDfn)x;
    return True;
  }
  return False;
}

c_bool styx_QlxCat(PT_Term x, styxQlxCat* x1)
{
  if(  PT_THISNTM(x, CfgSyms[51]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxQlxCat)x;
    return True;
  }
  return False;
}

c_bool styx_QlxGrp(PT_Term x, styxQlxGrp* x1)
{
  if(  PT_THISNTM(x, CfgSyms[54])
    || PT_THISNTM(x, CfgSyms[53])
    || PT_THISNTM(x, CfgSyms[52]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxQlxGrp)x;
    return True;
  }
  return False;
}

c_bool styx_QlxOpt(PT_Term x, styxQlxOpt* x1)
{
  if(  PT_THISNTM(x, CfgSyms[55]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxQlxOpt)x;
    return True;
  }
  return False;
}

c_bool styx_Exp(PT_Term x, styxExp* x1)
{
  if(  PT_THISNTM(x, CfgSyms[58])
    || PT_THISNTM(x, CfgSyms[62])
    || PT_THISNTM(x, CfgSyms[61])
    || PT_THISNTM(x, CfgSyms[57])
    || PT_THISNTM(x, CfgSyms[59])
    || PT_THISNTM(x, CfgSyms[60])
    || PT_THISNTM(x, CfgSyms[56]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxExp)x;
    return True;
  }
  return False;
}

c_bool styx_Dfn(PT_Term x, styxDfn* x1)
{
  if(  PT_THISNTM(x, CfgSyms[64]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxDfn)x;
    return True;
  }
  return False;
}

c_bool styx_Cat(PT_Term x, styxCat* x1)
{
  if(  PT_THISNTM(x, CfgSyms[66])
    || PT_THISNTM(x, CfgSyms[65]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxCat)x;
    return True;
  }
  return False;
}

c_bool styx_DfnOpt(PT_Term x, styxDfnOpt* x1)
{
  if(  PT_THISNTM(x, CfgSyms[67]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxDfnOpt)x;
    return True;
  }
  return False;
}

c_bool styx_Lay(PT_Term x, styxLay* x1)
{
  if(  PT_THISNTM(x, CfgSyms[69]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxLay)x;
    return True;
  }
  return False;
}

c_bool styx_Prd(PT_Term x, styxPrd* x1)
{
  if(  PT_THISNTM(x, CfgSyms[70]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxPrd)x;
    return True;
  }
  return False;
}

c_bool styx_Mbr(PT_Term x, styxMbr* x1)
{
  if(  PT_THISNTM(x, CfgSyms[72]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (styxMbr)x;
    return True;
  }
  return False;
}

/*I--------------------------------- styx --------------------------------- */

c_bool styx_Start_Source(styx x, styxSource* x1)
#define styx_Start_0   styx_Start_Source
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[73]), "styx expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[63]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (styxSource)GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[46], 1, True));
  return True;
}

/*I-------------------------------- Source -------------------------------- */

c_bool styxSource_root(styxSource x, GLS_Tok* x1, GLS_Lst(styxQlxDfn)* x2,
                       styxOptCfg* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[46]), "Source expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[0]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxSource)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (styxSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(styxQlxDfn))GLS_ign_Skip(x);
      x = (styxSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (styxOptCfg)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxSource,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxSource,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(styxQlxDfn))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxSource,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (styxOptCfg)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- OptCfg -------------------------------- */

c_bool styxOptCfg_nul(styxOptCfg x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[47]), "OptCfg expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[1]) ) return False;
  return True;
}

c_bool styxOptCfg_cfg(styxOptCfg x, GLS_Lst(styxDfn)* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[47]), "OptCfg expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[2]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxOptCfg)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(styxDfn))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxOptCfg,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(styxDfn))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- QlxDfn -------------------------------- */

c_bool styxQlxDfn_xgrp(styxQlxDfn x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[50]), "QlxDfn expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[9]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxQlxDfn)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxQlxDfn,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxQlxDfn_igrp(styxQlxDfn x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[50]), "QlxDfn expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[8]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxQlxDfn)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxQlxDfn,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxQlxDfn_defn(styxQlxDfn x, styxQlxCat* x1, styxQlxOpt* x2,
                       styxQlxGrp* x3, GLS_Tok* x4,
                       styxQlxGrp* x5, styxExp* x6)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[50]), "QlxDfn expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[7]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxQlxDfn)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxQlxCat)GLS_ign_Skip(x);
      x = (styxQlxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxQlxOpt)GLS_ign_Skip(x);
      x = (styxQlxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (styxQlxGrp)GLS_ign_Skip(x);
      x = (styxQlxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Tok)GLS_ign_Skip(x);
      x = (styxQlxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x5 != (StdCPtr)NULL )
        *x5 = (styxQlxGrp)GLS_ign_Skip(x);
      x = (styxQlxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x6 != (StdCPtr)NULL )
        *x6 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxQlxDfn,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxQlxCat)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxQlxDfn,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxQlxOpt)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxQlxDfn,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (styxQlxGrp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxQlxDfn,x);
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxQlxDfn,x);
      if( (StdCPtr)x5 != (StdCPtr)NULL )
        *x5 = (styxQlxGrp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxQlxDfn,x);
      if( (StdCPtr)x6 != (StdCPtr)NULL )
        *x6 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- QlxCat -------------------------------- */

c_bool styxQlxCat_letC(styxQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[51]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[10]) ) return False;
  return True;
}

c_bool styxQlxCat_indC(styxQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[51]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[15]) ) return False;
  return True;
}

c_bool styxQlxCat_ignC(styxQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[51]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[12]) ) return False;
  return True;
}

c_bool styxQlxCat_comC(styxQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[51]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[13]) ) return False;
  return True;
}

c_bool styxQlxCat_lanC(styxQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[51]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[14]) ) return False;
  return True;
}

c_bool styxQlxCat_tokC(styxQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[51]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[11]) ) return False;
  return True;
}

/*I-------------------------------- QlxGrp -------------------------------- */

c_bool styxQlxGrp_non(styxQlxGrp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[54])
        || PT_THISNTM((PT_Term)x, CfgSyms[53])
        || PT_THISNTM((PT_Term)x, CfgSyms[52]), "QlxGrp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[16]) ) return False;
  return True;
}

c_bool styxQlxGrp_igrp(styxQlxGrp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[54])
        || PT_THISNTM((PT_Term)x, CfgSyms[53])
        || PT_THISNTM((PT_Term)x, CfgSyms[52]), "QlxGrp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[20]) ) return False;
  return True;
}

c_bool styxQlxGrp_grp(styxQlxGrp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[54])
        || PT_THISNTM((PT_Term)x, CfgSyms[53])
        || PT_THISNTM((PT_Term)x, CfgSyms[52]), "QlxGrp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[17]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxQlxGrp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxQlxGrp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- QlxOpt -------------------------------- */

c_bool styxQlxOpt_ignca(styxQlxOpt x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[55]), "QlxOpt expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[23]) ) return False;
  return True;
}

c_bool styxQlxOpt_non(styxQlxOpt x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[55]), "QlxOpt expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[22]) ) return False;
  return True;
}

/*I--------------------------------- Exp ---------------------------------- */

c_bool styxExp_dyck(styxExp x, styxExp* x1, styxExp* x2,
                    styxExp* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[24]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(x);
      x = (styxExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(x);
      x = (styxExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxExp,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_nul(styxExp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[26]) ) return False;
  return True;
}

c_bool styxExp_opt(styxExp x, styxExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[33]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_set(styxExp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[41]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_conc(styxExp x, styxExp* x1, styxExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[31]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(x);
      x = (styxExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_sequ(styxExp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[40]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_star(styxExp x, styxExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[34]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_range(styxExp x, styxExp* x1, styxExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[38]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(x);
      x = (styxExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_ident(styxExp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[42]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_union(styxExp x, styxExp* x1, styxExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[28]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(x);
      x = (styxExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_diff(styxExp x, styxExp* x1, styxExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[29]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(x);
      x = (styxExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxExp_plus(styxExp x, styxExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[57])
        || PT_THISNTM((PT_Term)x, CfgSyms[59])
        || PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[56]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[35]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Dfn ---------------------------------- */

c_bool styxDfn_defn(styxDfn x, styxCat* x1, styxDfnOpt* x2,
                    GLS_Tok* x3, GLS_Lst(styxPrd)* x4)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[64]), "Dfn expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[45]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxDfn)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxCat)GLS_ign_Skip(x);
      x = (styxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxDfnOpt)GLS_ign_Skip(x);
      x = (styxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Tok)GLS_ign_Skip(x);
      x = (styxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Lst(styxPrd))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxDfn,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxCat)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxDfn,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (styxDfnOpt)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxDfn,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxDfn,x);
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Lst(styxPrd))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Cat ---------------------------------- */

c_bool styxCat_bgnC(styxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[66])
        || PT_THISNTM((PT_Term)x, CfgSyms[65]), "Cat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[46]) ) return False;
  return True;
}

c_bool styxCat_letC(styxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[66])
        || PT_THISNTM((PT_Term)x, CfgSyms[65]), "Cat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[47]) ) return False;
  return True;
}

/*I-------------------------------- DfnOpt -------------------------------- */

c_bool styxDfnOpt_non(styxDfnOpt x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[67]), "DfnOpt expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[50]) ) return False;
  return True;
}

c_bool styxDfnOpt_errnt(styxDfnOpt x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[67]), "DfnOpt expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[51]) ) return False;
  return True;
}

/*I--------------------------------- Lay ---------------------------------- */

c_bool styxLay_dft(styxLay x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[69]), "Lay expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[54]) ) return False;
  return True;
}

c_bool styxLay_rec(styxLay x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[69]), "Lay expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[55]) ) return False;
  return True;
}

c_bool styxLay_grp(styxLay x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[69]), "Lay expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[56]) ) return False;
  return True;
}

/*I--------------------------------- Prd ---------------------------------- */

c_bool styxPrd_prod(styxPrd x, styxLay* x1, GLS_Tok* x2,
                    GLS_Lst(styxMbr)* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[70]), "Prd expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[57]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxPrd)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxLay)GLS_ign_Skip(x);
      x = (styxPrd)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(x);
      x = (styxPrd)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(styxMbr))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxPrd,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (styxLay)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxPrd,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(styxPrd,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(styxMbr))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Mbr ---------------------------------- */

c_bool styxMbr_else(styxMbr x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[72]), "Mbr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[62]) ) return False;
  return True;
}

c_bool styxMbr_ntm(styxMbr x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[72]), "Mbr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[60]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxMbr)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxMbr,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool styxMbr_tkm(styxMbr x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[72]), "Mbr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[61]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (styxMbr)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(styxMbr,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}
