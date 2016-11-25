/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [esty_int.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;

void esty_initSymbols()
{
  GLS_init();
  CfgSyms = (symbol*)NewMem(sizeof(symbol)*51);
  PrdSyms = (symbol*)NewMem(sizeof(symbol)*43);

  CfgSyms[0] = stringToSymbol("Parenthesis");
  CfgSyms[1] = stringToSymbol("Comment");
  CfgSyms[2] = stringToSymbol("Ide");
  CfgSyms[3] = stringToSymbol("Nat");
  CfgSyms[4] = stringToSymbol("Opr");
  CfgSyms[5] = stringToSymbol("Set");
  CfgSyms[6] = stringToSymbol("Seq");
  CfgSyms[7] = stringToSymbol("Language");
  CfgSyms[8] = stringToSymbol("Regular");
  CfgSyms[9] = stringToSymbol("Grammar");
  CfgSyms[10] = stringToSymbol("Context");
  CfgSyms[11] = stringToSymbol("Free");
  CfgSyms[12] = stringToSymbol("=");
  CfgSyms[13] = stringToSymbol("let");
  CfgSyms[14] = stringToSymbol("tok");
  CfgSyms[15] = stringToSymbol("ign");
  CfgSyms[16] = stringToSymbol("com");
  CfgSyms[17] = stringToSymbol("[");
  CfgSyms[18] = stringToSymbol("ica");
  CfgSyms[19] = stringToSymbol("]");
  CfgSyms[20] = stringToSymbol("|");
  CfgSyms[21] = stringToSymbol("-");
  CfgSyms[22] = stringToSymbol("{");
  CfgSyms[23] = stringToSymbol("}");
  CfgSyms[24] = stringToSymbol("+");
  CfgSyms[25] = stringToSymbol("..");
  CfgSyms[26] = stringToSymbol("(");
  CfgSyms[27] = stringToSymbol(")");
  CfgSyms[28] = stringToSymbol("start");
  CfgSyms[29] = stringToSymbol(":");
  CfgSyms[30] = stringToSymbol("...");
  CfgSyms[31] = stringToSymbol("Source");
  CfgSyms[32] = stringToSymbol("QlxDfns");
  CfgSyms[33] = stringToSymbol("QlxDfn");
  CfgSyms[34] = stringToSymbol("QlxCat");
  CfgSyms[35] = stringToSymbol("QlxOpt");
  CfgSyms[36] = stringToSymbol("Exp");
  CfgSyms[37] = stringToSymbol("Exp1");
  CfgSyms[38] = stringToSymbol("Exp2");
  CfgSyms[39] = stringToSymbol("Exp3");
  CfgSyms[40] = stringToSymbol("Exp4");
  CfgSyms[41] = stringToSymbol("Dfns");
  CfgSyms[42] = stringToSymbol("Dfn");
  CfgSyms[43] = stringToSymbol("Cat");
  CfgSyms[44] = stringToSymbol("Prds");
  CfgSyms[45] = stringToSymbol("Prd");
  CfgSyms[46] = stringToSymbol("Mbrs");
  CfgSyms[47] = stringToSymbol("Mbr");
  CfgSyms[48] = stringToSymbol("Form");
  CfgSyms[49] = stringToSymbol("Toks");
  CfgSyms[50] = stringToSymbol("estyx");

  PrdSyms[0] = stringToSymbol("root");
  PrdSyms[1] = stringToSymbol("nil");
  PrdSyms[2] = stringToSymbol("cons");
  PrdSyms[3] = stringToSymbol("defn");
  PrdSyms[4] = stringToSymbol("letC");
  PrdSyms[5] = stringToSymbol("tokC");
  PrdSyms[6] = stringToSymbol("ignC");
  PrdSyms[7] = stringToSymbol("comC");
  PrdSyms[8] = stringToSymbol("non");
  PrdSyms[9] = stringToSymbol("ignca");
  PrdSyms[10] = stringToSymbol("union");
  PrdSyms[11] = stringToSymbol("diff");
  PrdSyms[12] = stringToSymbol("ign1");
  PrdSyms[13] = stringToSymbol("conc");
  PrdSyms[14] = stringToSymbol("ign1");
  PrdSyms[15] = stringToSymbol("opt");
  PrdSyms[16] = stringToSymbol("star");
  PrdSyms[17] = stringToSymbol("plus");
  PrdSyms[18] = stringToSymbol("ign1");
  PrdSyms[19] = stringToSymbol("range");
  PrdSyms[20] = stringToSymbol("ign2");
  PrdSyms[21] = stringToSymbol("ign1");
  PrdSyms[22] = stringToSymbol("sequ");
  PrdSyms[23] = stringToSymbol("set");
  PrdSyms[24] = stringToSymbol("ident");
  PrdSyms[25] = stringToSymbol("nil");
  PrdSyms[26] = stringToSymbol("cons");
  PrdSyms[27] = stringToSymbol("defn");
  PrdSyms[28] = stringToSymbol("letC");
  PrdSyms[29] = stringToSymbol("bgnC");
  PrdSyms[30] = stringToSymbol("nil");
  PrdSyms[31] = stringToSymbol("cons");
  PrdSyms[32] = stringToSymbol("prod");
  PrdSyms[33] = stringToSymbol("nil");
  PrdSyms[34] = stringToSymbol("cons");
  PrdSyms[35] = stringToSymbol("tkm");
  PrdSyms[36] = stringToSymbol("ntm");
  PrdSyms[37] = stringToSymbol("ide");
  PrdSyms[38] = stringToSymbol("one");
  PrdSyms[39] = stringToSymbol("nul");
  PrdSyms[40] = stringToSymbol("nil");
  PrdSyms[41] = stringToSymbol("cons");
  PrdSyms[42] = stringToSymbol("Start_Source");
}

void esty_quitSymbols()
{
  if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
  if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractType( estyx );

AbstractType( estySource );
AbstractType( estyQlxDfn );
AbstractType( estyQlxCat );
AbstractType( estyQlxOpt );
AbstractType( estyExp  );
AbstractType( estyDfn  );
AbstractType( estyCat  );
AbstractType( estyPrd  );
AbstractType( estyMbr  );
AbstractType( estyForm );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Testy_Ide(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[2]) );
}

c_bool Testy_Set(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[5]) );
}

c_bool Testy_Seq(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[6]) );
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool esty_estyx(PT_Term x, estyx* x1)
{
  if( PT_THISNTM(x, CfgSyms[50]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyx)x;
    return True;
  }
  return False;
}

c_bool esty_Source(PT_Term x, estySource* x1)
{
  if(  PT_THISNTM(x, CfgSyms[31]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estySource)x;
    return True;
  }
  return False;
}

c_bool esty_QlxDfn(PT_Term x, estyQlxDfn* x1)
{
  if(  PT_THISNTM(x, CfgSyms[33]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyQlxDfn)x;
    return True;
  }
  return False;
}

c_bool esty_QlxCat(PT_Term x, estyQlxCat* x1)
{
  if(  PT_THISNTM(x, CfgSyms[34]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyQlxCat)x;
    return True;
  }
  return False;
}

c_bool esty_QlxOpt(PT_Term x, estyQlxOpt* x1)
{
  if(  PT_THISNTM(x, CfgSyms[35]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyQlxOpt)x;
    return True;
  }
  return False;
}

c_bool esty_Exp(PT_Term x, estyExp* x1)
{
  if(  PT_THISNTM(x, CfgSyms[36])
    || PT_THISNTM(x, CfgSyms[40])
    || PT_THISNTM(x, CfgSyms[39])
    || PT_THISNTM(x, CfgSyms[38])
    || PT_THISNTM(x, CfgSyms[37]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyExp)x;
    return True;
  }
  return False;
}

c_bool esty_Dfn(PT_Term x, estyDfn* x1)
{
  if(  PT_THISNTM(x, CfgSyms[42]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyDfn)x;
    return True;
  }
  return False;
}

c_bool esty_Cat(PT_Term x, estyCat* x1)
{
  if(  PT_THISNTM(x, CfgSyms[43]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyCat)x;
    return True;
  }
  return False;
}

c_bool esty_Prd(PT_Term x, estyPrd* x1)
{
  if(  PT_THISNTM(x, CfgSyms[45]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyPrd)x;
    return True;
  }
  return False;
}

c_bool esty_Mbr(PT_Term x, estyMbr* x1)
{
  if(  PT_THISNTM(x, CfgSyms[47]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyMbr)x;
    return True;
  }
  return False;
}

c_bool esty_Form(PT_Term x, estyForm* x1)
{
  if(  PT_THISNTM(x, CfgSyms[48]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (estyForm)x;
    return True;
  }
  return False;
}

/*I-------------------------------- estyx --------------------------------- */

c_bool estyx_Start_Source(estyx x, estySource* x1)
#define estyx_Start_0   estyx_Start_Source
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[50]), "estyx expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[42]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (estySource)GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[31], 1, True));
  return True;
}

/*I-------------------------------- Source -------------------------------- */

c_bool estySource_root(estySource x, GLS_Tok* x1, GLS_Lst(estyQlxDfn)* x2,
                       GLS_Lst(estyDfn)* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[31]), "Source expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[0]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estySource)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (estySource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(estyQlxDfn))GLS_ign_Skip(x);
      x = (estySource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(estyDfn))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estySource,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estySource,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(estyQlxDfn))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estySource,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(estyDfn))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- QlxDfn -------------------------------- */

c_bool estyQlxDfn_defn(estyQlxDfn x, estyQlxCat* x1, estyQlxOpt* x2,
                       GLS_Tok* x3, estyExp* x4)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[33]), "QlxDfn expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[3]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyQlxDfn)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyQlxCat)GLS_ign_Skip(x);
      x = (estyQlxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyQlxOpt)GLS_ign_Skip(x);
      x = (estyQlxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Tok)GLS_ign_Skip(x);
      x = (estyQlxDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (estyExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyQlxDfn,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyQlxCat)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyQlxDfn,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyQlxOpt)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyQlxDfn,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyQlxDfn,x);
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (estyExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- QlxCat -------------------------------- */

c_bool estyQlxCat_letC(estyQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[34]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[4]) ) return False;
  return True;
}

c_bool estyQlxCat_comC(estyQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[34]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[7]) ) return False;
  return True;
}

c_bool estyQlxCat_ignC(estyQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[34]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[6]) ) return False;
  return True;
}

c_bool estyQlxCat_tokC(estyQlxCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[34]), "QlxCat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[5]) ) return False;
  return True;
}

/*I-------------------------------- QlxOpt -------------------------------- */

c_bool estyQlxOpt_non(estyQlxOpt x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[35]), "QlxOpt expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[8]) ) return False;
  return True;
}

c_bool estyQlxOpt_ignca(estyQlxOpt x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[35]), "QlxOpt expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[9]) ) return False;
  return True;
}

/*I--------------------------------- Exp ---------------------------------- */

c_bool estyExp_range(estyExp x, estyExp* x1, estyExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[19]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(x);
      x = (estyExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_opt(estyExp x, estyExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[15]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_union(estyExp x, estyExp* x1, estyExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[10]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(x);
      x = (estyExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_conc(estyExp x, estyExp* x1, estyExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[13]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(x);
      x = (estyExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_plus(estyExp x, estyExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[17]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_ident(estyExp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[24]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_diff(estyExp x, estyExp* x1, estyExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[11]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(x);
      x = (estyExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_sequ(estyExp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[22]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_set(estyExp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[23]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyExp_star(estyExp x, estyExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[36])
        || PT_THISNTM((PT_Term)x, CfgSyms[40])
        || PT_THISNTM((PT_Term)x, CfgSyms[39])
        || PT_THISNTM((PT_Term)x, CfgSyms[38])
        || PT_THISNTM((PT_Term)x, CfgSyms[37]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[16]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Dfn ---------------------------------- */

c_bool estyDfn_defn(estyDfn x, estyCat* x1, GLS_Tok* x2,
                    GLS_Lst(estyPrd)* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[42]), "Dfn expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[27]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyDfn)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyCat)GLS_ign_Skip(x);
      x = (estyDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(x);
      x = (estyDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(estyPrd))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyDfn,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyCat)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyDfn,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyDfn,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(estyPrd))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Cat ---------------------------------- */

c_bool estyCat_letC(estyCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Cat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[28]) ) return False;
  return True;
}

c_bool estyCat_bgnC(estyCat x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Cat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[29]) ) return False;
  return True;
}

/*I--------------------------------- Prd ---------------------------------- */

c_bool estyPrd_prod(estyPrd x, GLS_Tok* x1, GLS_Lst(estyMbr)* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[45]), "Prd expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[32]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyPrd)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (estyPrd)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(estyMbr))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyPrd,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyPrd,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(estyMbr))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Mbr ---------------------------------- */

c_bool estyMbr_tkm(estyMbr x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[47]), "Mbr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[35]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyMbr)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyMbr,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyMbr_ntm(estyMbr x, estyForm* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[47]), "Mbr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[36]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyMbr)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyForm)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyMbr,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyForm)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Form --------------------------------- */

c_bool estyForm_one(estyForm x, estyForm* x1, GLS_Lst(GLS_Tok)* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[48]), "Form expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[38]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyForm)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyForm)GLS_ign_Skip(x);
      x = (estyForm)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyForm,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (estyForm)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyForm,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyForm_ide(estyForm x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[48]), "Form expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[37]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyForm)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyForm,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool estyForm_nul(estyForm x, GLS_Lst(GLS_Tok)* x1, estyForm* x2,
                    GLS_Lst(GLS_Tok)* x3, GLS_Lst(GLS_Tok)* x4)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[48]), "Form expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[39]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (estyForm)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(x);
      x = (estyForm)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyForm)GLS_ign_Skip(x);
      x = (estyForm)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(x);
      x = (estyForm)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(estyForm,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyForm,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (estyForm)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyForm,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(estyForm,x);
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(y);
    }
  }
  return True;
}
