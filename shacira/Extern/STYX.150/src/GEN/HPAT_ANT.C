/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [hpat_ant.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls_abs.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;

void hpat_initSymbols()
{
  GLS_init();
  CfgSyms = (symbol*)NewMem(sizeof(symbol)*8);
  PrdSyms = (symbol*)NewMem(sizeof(symbol)*7);

  CfgSyms[0] = stringToSymbol("PatBgn");
  CfgSyms[1] = stringToSymbol("PatEnd");
  CfgSyms[2] = stringToSymbol("PatRef");
  CfgSyms[3] = stringToSymbol("_other_");
  CfgSyms[4] = stringToSymbol("HPatDoc");
  CfgSyms[5] = stringToSymbol("Contents");
  CfgSyms[6] = stringToSymbol("Content");
  CfgSyms[7] = stringToSymbol("hpat");

  PrdSyms[0] = stringToSymbol("dfn");
  PrdSyms[1] = stringToSymbol("nil");
  PrdSyms[2] = stringToSymbol("cons");
  PrdSyms[3] = stringToSymbol("ref");
  PrdSyms[4] = stringToSymbol("else");
  PrdSyms[5] = stringToSymbol("pat");
  PrdSyms[6] = stringToSymbol("Start_HPatDoc");
}

void hpat_quitSymbols()
{
  if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
  if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractHugeType( hpat );

AbstractHugeType( hpatHPatDoc );
AbstractHugeType( hpatContent );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Thpat_PatBgn(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[0];
}

c_bool Thpat_PatEnd(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[1];
}

c_bool Thpat_PatRef(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[2];
}

c_bool Thpat__other_(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[3];
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool hpat_hpat(PT_Abs_Term x, hpat* x1)
{
  if( PT_Abs_nonterm(x) == CfgSyms[7] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (hpat)x;
    return True;
  }
  return False;
}

c_bool hpat_HPatDoc(PT_Abs_Term x, hpatHPatDoc* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[4] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (hpatHPatDoc)x;
    return True;
  }
  return False;
}

c_bool hpat_Content(PT_Abs_Term x, hpatContent* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[6] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (hpatContent)x;
    return True;
  }
  return False;
}

/*I--------------------------------- hpat --------------------------------- */

c_bool hpat_Start_HPatDoc(hpat x, hpatHPatDoc* x1)
#define hpat_Start_0   hpat_Start_HPatDoc
{
  assert0( PT_Abs_nonterm(x) == CfgSyms[7], "hpat expected" );
  if( PT_Abs_product(x) != PrdSyms[6] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL )
    *x1 = (hpatHPatDoc)PT_Abs_part(x,0);
  return True;
}

/*I------------------------------- HPatDoc -------------------------------- */

c_bool hpatHPatDoc_dfn(hpatHPatDoc x, GLS_Lst(hpatContent)* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[4], "HPatDoc expected" );
  if( PT_Abs_product(x) != PrdSyms[0] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(hpatContent))PT_Abs_part(x,0);
  return True;
}

/*I------------------------------- Content -------------------------------- */

c_bool hpatContent_pat(hpatContent x, GLS_Tok* x1, GLS_Lst(hpatContent)* x2,
                       GLS_Tok* x3)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[6], "Content expected" );
  if( PT_Abs_product(x) != PrdSyms[5] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Lst(hpatContent))PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Tok)PT_Abs_part(x,2);
  return True;
}

c_bool hpatContent_else(hpatContent x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[6], "Content expected" );
  if( PT_Abs_product(x) != PrdSyms[4] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool hpatContent_ref(hpatContent x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[6], "Content expected" );
  if( PT_Abs_product(x) != PrdSyms[3] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}
