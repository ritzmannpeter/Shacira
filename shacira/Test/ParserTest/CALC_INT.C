/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [calc_int.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls.h"

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

AbstractType( calc );

AbstractType( calcCmd  );
AbstractType( calcExp  );

/*I--------------------------- Access to Tokens --------------------------- */

bool Tcalc_Int(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[1]) );
}

/*I--------------------------- Access to Terms ---------------------------- */

bool calc_calc(PT_Term x, calc* x1)
{
  if( PT_THISNTM(x, CfgSyms[14]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (calc)x;
    return True;
  }
  return False;
}

bool calc_Cmd(PT_Term x, calcCmd* x1)
{
  if(  PT_THISNTM(x, CfgSyms[10]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (calcCmd)x;
    return True;
  }
  return False;
}

bool calc_Exp(PT_Term x, calcExp* x1)
{
  if(  PT_THISNTM(x, CfgSyms[12])
    || PT_THISNTM(x, CfgSyms[13])
    || PT_THISNTM(x, CfgSyms[11]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (calcExp)x;
    return True;
  }
  return False;
}

/*I--------------------------------- calc --------------------------------- */

bool calc_Start_Cmd(calc x, calcCmd* x1)
#define calc_Start_0   calc_Start_Cmd
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[14]), "calc expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[11]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (calcCmd)PT_nthSymbol((PT_Term)x, CfgSyms[10], 1, True);
  return True;
}

/*I--------------------------------- Cmd ---------------------------------- */

bool calcCmd_end(calcCmd x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[10]), "Cmd expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[1]) ) return False;
  return True;
}

bool calcCmd_exp(calcCmd x, calcExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[10]), "Cmd expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[0]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (calcCmd)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(calcCmd,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Exp ---------------------------------- */

bool calcExp_mlt(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[13])
        || PT_THISNTM((PT_Term)x, CfgSyms[11]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[6]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (calcExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(x);
      x = (calcExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (calcExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(calcExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(calcExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (calcExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

bool calcExp_int(calcExp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[13])
        || PT_THISNTM((PT_Term)x, CfgSyms[11]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[10]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (calcExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(calcExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

bool calcExp_neg(calcExp x, calcExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[13])
        || PT_THISNTM((PT_Term)x, CfgSyms[11]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[8]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (calcExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(calcExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

bool calcExp_sub(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[13])
        || PT_THISNTM((PT_Term)x, CfgSyms[11]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[4]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (calcExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(x);
      x = (calcExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (calcExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(calcExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(calcExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (calcExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

bool calcExp_div(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[13])
        || PT_THISNTM((PT_Term)x, CfgSyms[11]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[7]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (calcExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(x);
      x = (calcExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (calcExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(calcExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(calcExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (calcExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

bool calcExp_add(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[13])
        || PT_THISNTM((PT_Term)x, CfgSyms[11]), "Exp expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[3]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (calcExp)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(x);
      x = (calcExp)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (calcExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(calcExp,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(calcExp,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (calcExp)GLS_ign_Skip(y);
    }
  }
  return True;
}
