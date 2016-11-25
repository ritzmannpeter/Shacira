/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [esty_ant.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls_abs.h"

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

AbstractHugeType( estyx );

AbstractHugeType( estySource );
AbstractHugeType( estyQlxDfn );
AbstractHugeType( estyQlxCat );
AbstractHugeType( estyQlxOpt );
AbstractHugeType( estyExp  );
AbstractHugeType( estyDfn  );
AbstractHugeType( estyCat  );
AbstractHugeType( estyPrd  );
AbstractHugeType( estyMbr  );
AbstractHugeType( estyForm );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Testy_Ide(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[2];
}

c_bool Testy_Set(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[5];
}

c_bool Testy_Seq(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[6];
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool esty_estyx(PT_Abs_Term x, estyx* x1)
{
  if( PT_Abs_nonterm(x) == CfgSyms[50] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyx)x;
    return True;
  }
  return False;
}

c_bool esty_Source(PT_Abs_Term x, estySource* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[31] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estySource)x;
    return True;
  }
  return False;
}

c_bool esty_QlxDfn(PT_Abs_Term x, estyQlxDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[33] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyQlxDfn)x;
    return True;
  }
  return False;
}

c_bool esty_QlxCat(PT_Abs_Term x, estyQlxCat* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[34] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyQlxCat)x;
    return True;
  }
  return False;
}

c_bool esty_QlxOpt(PT_Abs_Term x, estyQlxOpt* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[35] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyQlxOpt)x;
    return True;
  }
  return False;
}

c_bool esty_Exp(PT_Abs_Term x, estyExp* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[36]
    || PT_Abs_nonterm(x) == CfgSyms[40]
    || PT_Abs_nonterm(x) == CfgSyms[39]
    || PT_Abs_nonterm(x) == CfgSyms[38]
    || PT_Abs_nonterm(x) == CfgSyms[37] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyExp)x;
    return True;
  }
  return False;
}

c_bool esty_Dfn(PT_Abs_Term x, estyDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[42] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyDfn)x;
    return True;
  }
  return False;
}

c_bool esty_Cat(PT_Abs_Term x, estyCat* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[43] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyCat)x;
    return True;
  }
  return False;
}

c_bool esty_Prd(PT_Abs_Term x, estyPrd* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[45] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyPrd)x;
    return True;
  }
  return False;
}

c_bool esty_Mbr(PT_Abs_Term x, estyMbr* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[47] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyMbr)x;
    return True;
  }
  return False;
}

c_bool esty_Form(PT_Abs_Term x, estyForm* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[48] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyForm)x;
    return True;
  }
  return False;
}

/*I-------------------------------- estyx --------------------------------- */

c_bool estyx_Start_Source(estyx x, estySource* x1)
#define estyx_Start_0   estyx_Start_Source
{
  assert0( PT_Abs_nonterm(x) == CfgSyms[50], "estyx expected" );
  if( PT_Abs_product(x) != PrdSyms[42] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL )
    *x1 = (estySource)PT_Abs_part(x,0);
  return True;
}

/*I-------------------------------- Source -------------------------------- */

c_bool estySource_root(estySource x, GLS_Tok* x1, GLS_Lst(estyQlxDfn)* x2,
                       GLS_Lst(estyDfn)* x3)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[31], "Source expected" );
  if( PT_Abs_product(x) != PrdSyms[0] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Lst(estyQlxDfn))PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Lst(estyDfn))PT_Abs_part(x,2);
  return True;
}

/*I-------------------------------- QlxDfn -------------------------------- */

c_bool estyQlxDfn_defn(estyQlxDfn x, estyQlxCat* x1, estyQlxOpt* x2,
                       GLS_Tok* x3, estyExp* x4)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[33], "QlxDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[3] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyQlxCat)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (estyQlxOpt)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Tok)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (estyExp)PT_Abs_part(x,3);
  return True;
}

/*I-------------------------------- QlxCat -------------------------------- */

c_bool estyQlxCat_letC(estyQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[34], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[4] ) return False;
  return True;
}

c_bool estyQlxCat_comC(estyQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[34], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[7] ) return False;
  return True;
}

c_bool estyQlxCat_ignC(estyQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[34], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[6] ) return False;
  return True;
}

c_bool estyQlxCat_tokC(estyQlxCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[34], "QlxCat expected" );
  if( PT_Abs_product(x) != PrdSyms[5] ) return False;
  return True;
}

/*I-------------------------------- QlxOpt -------------------------------- */

c_bool estyQlxOpt_non(estyQlxOpt x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[35], "QlxOpt expected" );
  if( PT_Abs_product(x) != PrdSyms[8] ) return False;
  return True;
}

c_bool estyQlxOpt_ignca(estyQlxOpt x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[35], "QlxOpt expected" );
  if( PT_Abs_product(x) != PrdSyms[9] ) return False;
  return True;
}

/*I--------------------------------- Exp ---------------------------------- */

c_bool estyExp_range(estyExp x, estyExp* x1, estyExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[19] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (estyExp)PT_Abs_part(x,1);
  return True;
}

c_bool estyExp_opt(estyExp x, estyExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[15] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyExp)PT_Abs_part(x,0);
  return True;
}

c_bool estyExp_union(estyExp x, estyExp* x1, estyExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[10] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (estyExp)PT_Abs_part(x,1);
  return True;
}

c_bool estyExp_conc(estyExp x, estyExp* x1, estyExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[13] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (estyExp)PT_Abs_part(x,1);
  return True;
}

c_bool estyExp_plus(estyExp x, estyExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[17] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyExp)PT_Abs_part(x,0);
  return True;
}

c_bool estyExp_ident(estyExp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[24] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool estyExp_diff(estyExp x, estyExp* x1, estyExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[11] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (estyExp)PT_Abs_part(x,1);
  return True;
}

c_bool estyExp_sequ(estyExp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[22] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool estyExp_set(estyExp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[23] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool estyExp_star(estyExp x, estyExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[36]
        || PT_Abs_nonterm(x) == CfgSyms[40]
        || PT_Abs_nonterm(x) == CfgSyms[39]
        || PT_Abs_nonterm(x) == CfgSyms[38]
        || PT_Abs_nonterm(x) == CfgSyms[37], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[16] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyExp)PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Dfn ---------------------------------- */

c_bool estyDfn_defn(estyDfn x, estyCat* x1, GLS_Tok* x2,
                    GLS_Lst(estyPrd)* x3)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "Dfn expected" );
  if( PT_Abs_product(x) != PrdSyms[27] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyCat)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Tok)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Lst(estyPrd))PT_Abs_part(x,2);
  return True;
}

/*I--------------------------------- Cat ---------------------------------- */

c_bool estyCat_letC(estyCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "Cat expected" );
  if( PT_Abs_product(x) != PrdSyms[28] ) return False;
  return True;
}

c_bool estyCat_bgnC(estyCat x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "Cat expected" );
  if( PT_Abs_product(x) != PrdSyms[29] ) return False;
  return True;
}

/*I--------------------------------- Prd ---------------------------------- */

c_bool estyPrd_prod(estyPrd x, GLS_Tok* x1, GLS_Lst(estyMbr)* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[45], "Prd expected" );
  if( PT_Abs_product(x) != PrdSyms[32] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Lst(estyMbr))PT_Abs_part(x,1);
  return True;
}

/*I--------------------------------- Mbr ---------------------------------- */

c_bool estyMbr_tkm(estyMbr x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47], "Mbr expected" );
  if( PT_Abs_product(x) != PrdSyms[35] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool estyMbr_ntm(estyMbr x, estyForm* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47], "Mbr expected" );
  if( PT_Abs_product(x) != PrdSyms[36] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyForm)PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Form --------------------------------- */

c_bool estyForm_one(estyForm x, estyForm* x1, GLS_Lst(GLS_Tok)* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[48], "Form expected" );
  if( PT_Abs_product(x) != PrdSyms[38] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (estyForm)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Lst(GLS_Tok))PT_Abs_part(x,1);
  return True;
}

c_bool estyForm_ide(estyForm x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[48], "Form expected" );
  if( PT_Abs_product(x) != PrdSyms[37] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool estyForm_nul(estyForm x, GLS_Lst(GLS_Tok)* x1, estyForm* x2,
                    GLS_Lst(GLS_Tok)* x3, GLS_Lst(GLS_Tok)* x4)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[48], "Form expected" );
  if( PT_Abs_product(x) != PrdSyms[39] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(GLS_Tok))PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (estyForm)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Lst(GLS_Tok))PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (GLS_Lst(GLS_Tok))PT_Abs_part(x,3);
  return True;
}
