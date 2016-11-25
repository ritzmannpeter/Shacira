/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [meta_ant.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls_abs.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;

void meta_initSymbols()
{
  GLS_init();
  CfgSyms = (symbol*)NewMem(sizeof(symbol)*13);
  PrdSyms = (symbol*)NewMem(sizeof(symbol)*10);

  CfgSyms[0] = stringToSymbol("Ide");
  CfgSyms[1] = stringToSymbol("Opr");
  CfgSyms[2] = stringToSymbol("Comment");
  CfgSyms[3] = stringToSymbol(":");
  CfgSyms[4] = stringToSymbol("text");
  CfgSyms[5] = stringToSymbol("(");
  CfgSyms[6] = stringToSymbol(")");
  CfgSyms[7] = stringToSymbol("Source");
  CfgSyms[8] = stringToSymbol("Parts");
  CfgSyms[9] = stringToSymbol("Typ");
  CfgSyms[10] = stringToSymbol("Elm");
  CfgSyms[11] = stringToSymbol("XParts");
  CfgSyms[12] = stringToSymbol("meta");

  PrdSyms[0] = stringToSymbol("dfn");
  PrdSyms[1] = stringToSymbol("nil");
  PrdSyms[2] = stringToSymbol("cons");
  PrdSyms[3] = stringToSymbol("nul");
  PrdSyms[4] = stringToSymbol("dfn");
  PrdSyms[5] = stringToSymbol("txt");
  PrdSyms[6] = stringToSymbol("grp");
  PrdSyms[7] = stringToSymbol("nil");
  PrdSyms[8] = stringToSymbol("ign0");
  PrdSyms[9] = stringToSymbol("Start_Source");
}

void meta_quitSymbols()
{
  if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
  if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractHugeType( meta );

AbstractHugeType( metaSource );
AbstractHugeType( metaTyp  );
AbstractHugeType( metaElm  );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Tmeta_Ide(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[0];
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool meta_meta(PT_Abs_Term x, meta* x1)
{
  if( PT_Abs_nonterm(x) == CfgSyms[12] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (meta)x;
    return True;
  }
  return False;
}

c_bool meta_Source(PT_Abs_Term x, metaSource* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[7] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (metaSource)x;
    return True;
  }
  return False;
}

c_bool meta_Typ(PT_Abs_Term x, metaTyp* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[9] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (metaTyp)x;
    return True;
  }
  return False;
}

c_bool meta_Elm(PT_Abs_Term x, metaElm* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[10] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (metaElm)x;
    return True;
  }
  return False;
}

/*I--------------------------------- meta --------------------------------- */

c_bool meta_Start_Source(meta x, metaSource* x1)
#define meta_Start_0   meta_Start_Source
{
  assert0( PT_Abs_nonterm(x) == CfgSyms[12], "meta expected" );
  if( PT_Abs_product(x) != PrdSyms[9] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL )
    *x1 = (metaSource)PT_Abs_part(x,0);
  return True;
}

/*I-------------------------------- Source -------------------------------- */

c_bool metaSource_dfn(metaSource x, GLS_Lst(metaElm)* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[7], "Source expected" );
  if( PT_Abs_product(x) != PrdSyms[0] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(metaElm))PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Typ ---------------------------------- */

c_bool metaTyp_dfn(metaTyp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[9], "Typ expected" );
  if( PT_Abs_product(x) != PrdSyms[4] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool metaTyp_nul(metaTyp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[9], "Typ expected" );
  if( PT_Abs_product(x) != PrdSyms[3] ) return False;
  return True;
}

/*I--------------------------------- Elm ---------------------------------- */

c_bool metaElm_grp(metaElm x, GLS_Tok* x1, metaTyp* x2,
                   GLS_Lst(metaElm)* x3)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[10], "Elm expected" );
  if( PT_Abs_product(x) != PrdSyms[6] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (metaTyp)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Lst(metaElm))PT_Abs_part(x,2);
  return True;
}

c_bool metaElm_txt(metaElm x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[10], "Elm expected" );
  if( PT_Abs_product(x) != PrdSyms[5] ) return False;
  return True;
}
