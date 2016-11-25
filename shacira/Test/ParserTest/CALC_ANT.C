/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [calc_ant.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls_abs.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;

void calc_initSymbols()
{
  GLS_init();
  CfgSyms = (symbol*)NewMem(sizeof(symbol)*15);
  PrdSyms = (symbol*)NewMem(sizeof(symbol)*12);

  CfgSyms[0] = stringToSymbol("Tok");
  CfgSyms[1] = stringToSymbol("Int");
  CfgSyms[2] = stringToSymbol("Wrd");
  CfgSyms[3] = stringToSymbol("end");
  CfgSyms[4] = stringToSymbol("+");
  CfgSyms[5] = stringToSymbol("-");
  CfgSyms[6] = stringToSymbol("*");
  CfgSyms[7] = stringToSymbol("/");
  CfgSyms[8] = stringToSymbol("(");
  CfgSyms[9] = stringToSymbol(")");
  CfgSyms[10] = stringToSymbol("Cmd");
  CfgSyms[11] = stringToSymbol("Exp");
  CfgSyms[12] = stringToSymbol("Exp1");
  CfgSyms[13] = stringToSymbol("Exp2");
  CfgSyms[14] = stringToSymbol("calc");

  PrdSyms[0] = stringToSymbol("exp");
  PrdSyms[1] = stringToSymbol("end");
  PrdSyms[2] = stringToSymbol("ign0");
  PrdSyms[3] = stringToSymbol("add");
  PrdSyms[4] = stringToSymbol("sub");
  PrdSyms[5] = stringToSymbol("ign0");
  PrdSyms[6] = stringToSymbol("mlt");
  PrdSyms[7] = stringToSymbol("div");
  PrdSyms[8] = stringToSymbol("neg");
  PrdSyms[9] = stringToSymbol("ign0");
  PrdSyms[10] = stringToSymbol("int");
  PrdSyms[11] = stringToSymbol("Start_Cmd");
}

void calc_quitSymbols()
{
  if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
  if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractHugeType( calc );

AbstractHugeType( calcCmd  );
AbstractHugeType( calcExp  );

/*I--------------------------- Access to Tokens --------------------------- */

bool Tcalc_Int(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[1];
}

/*I--------------------------- Access to Terms ---------------------------- */

bool calc_calc(PT_Abs_Term x, calc* x1)
{
  if( PT_Abs_nonterm(x) == CfgSyms[14] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calc)x;
    return True;
  }
  return False;
}

bool calc_Cmd(PT_Abs_Term x, calcCmd* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[10] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calcCmd)x;
    return True;
  }
  return False;
}

bool calc_Exp(PT_Abs_Term x, calcExp* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[12]
    || PT_Abs_nonterm(x) == CfgSyms[13]
    || PT_Abs_nonterm(x) == CfgSyms[11] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calcExp)x;
    return True;
  }
  return False;
}

/*I--------------------------------- calc --------------------------------- */

bool calc_Start_Cmd(calc x, calcCmd* x1)
#define calc_Start_0   calc_Start_Cmd
{
  assert0( PT_Abs_nonterm(x) == CfgSyms[14], "calc expected" );
  if( PT_Abs_product(x) != PrdSyms[11] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL )
    *x1 = (calcCmd)PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Cmd ---------------------------------- */

bool calcCmd_end(calcCmd x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[10], "Cmd expected" );
  if( PT_Abs_product(x) != PrdSyms[1] ) return False;
  return True;
}

bool calcCmd_exp(calcCmd x, calcExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[10], "Cmd expected" );
  if( PT_Abs_product(x) != PrdSyms[0] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calcExp)PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Exp ---------------------------------- */

bool calcExp_mlt(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[12]
        || PT_Abs_nonterm(x) == CfgSyms[13]
        || PT_Abs_nonterm(x) == CfgSyms[11], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[6] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calcExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (calcExp)PT_Abs_part(x,1);
  return True;
}

bool calcExp_int(calcExp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[12]
        || PT_Abs_nonterm(x) == CfgSyms[13]
        || PT_Abs_nonterm(x) == CfgSyms[11], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[10] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

bool calcExp_neg(calcExp x, calcExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[12]
        || PT_Abs_nonterm(x) == CfgSyms[13]
        || PT_Abs_nonterm(x) == CfgSyms[11], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[8] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calcExp)PT_Abs_part(x,0);
  return True;
}

bool calcExp_sub(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[12]
        || PT_Abs_nonterm(x) == CfgSyms[13]
        || PT_Abs_nonterm(x) == CfgSyms[11], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[4] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calcExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (calcExp)PT_Abs_part(x,1);
  return True;
}

bool calcExp_div(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[12]
        || PT_Abs_nonterm(x) == CfgSyms[13]
        || PT_Abs_nonterm(x) == CfgSyms[11], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[7] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calcExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (calcExp)PT_Abs_part(x,1);
  return True;
}

bool calcExp_add(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[12]
        || PT_Abs_nonterm(x) == CfgSyms[13]
        || PT_Abs_nonterm(x) == CfgSyms[11], "Exp expected" );
  if( PT_Abs_product(x) != PrdSyms[3] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (calcExp)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (calcExp)PT_Abs_part(x,1);
  return True;
}
