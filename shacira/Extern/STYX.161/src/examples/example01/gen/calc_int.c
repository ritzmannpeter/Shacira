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
static int initcount_calc = 0;

void calc_initSymbols()
{
  if( initcount_calc == 0 )
  {
    GLS_init();
    assert0(CfgSyms == (symbol*)NULL,"calcSymbols already initialized");
    CfgSyms = (symbol*)NewMem(sizeof(symbol)*14);
    PrdSyms = (symbol*)NewMem(sizeof(symbol)*12);

    CfgSyms[0] = stringToSymbol("Tok");
    CfgSyms[1] = stringToSymbol("Int");
    CfgSyms[2] = stringToSymbol("Wrd");
    CfgSyms[3] = stringToSymbol("+");
    CfgSyms[4] = stringToSymbol("-");
    CfgSyms[5] = stringToSymbol("*");
    CfgSyms[6] = stringToSymbol("/");
    CfgSyms[7] = stringToSymbol("(");
    CfgSyms[8] = stringToSymbol(")");
    CfgSyms[9] = stringToSymbol("Command");
    CfgSyms[10] = stringToSymbol("Exp");
    CfgSyms[11] = stringToSymbol("Exp1");
    CfgSyms[12] = stringToSymbol("Exp2");
    CfgSyms[13] = stringToSymbol("calc");

    PrdSyms[0] = stringToSymbol("exp");
    PrdSyms[1] = stringToSymbol("non");
    PrdSyms[2] = stringToSymbol("ign0");
    PrdSyms[3] = stringToSymbol("add");
    PrdSyms[4] = stringToSymbol("sub");
    PrdSyms[5] = stringToSymbol("ign0");
    PrdSyms[6] = stringToSymbol("mlt");
    PrdSyms[7] = stringToSymbol("div");
    PrdSyms[8] = stringToSymbol("neg");
    PrdSyms[9] = stringToSymbol("ign0");
    PrdSyms[10] = stringToSymbol("int");
    PrdSyms[11] = stringToSymbol("Start_Command");
  }
  ++initcount_calc;
}

void calc_quitSymbols()
{
  --initcount_calc;
  if( initcount_calc == 0 )
  {
    assert0(CfgSyms != (symbol*)NULL,"calcSymbols not initialized");
    if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
    CfgSyms = (symbol*)NULL;
    if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
    PrdSyms = (symbol*)NULL;
  }
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractType( calc );

AbstractType( calcCommand );
AbstractType( calcExp  );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Tcalc_Int(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[1]) );
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool calc_calc(PT_Term x, calc* x1)
{
  if( PT_THISNTM(x, CfgSyms[13]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (calc)x;
    return True;
  }
  return False;
}

c_bool calc_Command(PT_Term x, calcCommand* x1)
{
  if(  PT_THISNTM(x, CfgSyms[9]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (calcCommand)x;
    return True;
  }
  return False;
}

c_bool calc_Exp(PT_Term x, calcExp* x1)
{
  if(  PT_THISNTM(x, CfgSyms[12])
    || PT_THISNTM(x, CfgSyms[11])
    || PT_THISNTM(x, CfgSyms[10]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (calcExp)x;
    return True;
  }
  return False;
}

/*I--------------------------------- calc --------------------------------- */

c_bool calc_Start_Command(calc x, calcCommand* x1)
#define calc_Start_0   calc_Start_Command
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[13]), "calc expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[11]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (calcCommand)GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[9], 1, True));
  return True;
}

/*I------------------------------- Command -------------------------------- */

c_bool calcCommand_non(calcCommand x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[9]), "Command expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[1]) ) return False;
  return True;
}

c_bool calcCommand_exp(calcCommand x, calcExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[9]), "Command expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[0]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (calcCommand)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(calcCommand,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (calcExp)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Exp ---------------------------------- */

c_bool calcExp_mlt(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[11])
        || PT_THISNTM((PT_Term)x, CfgSyms[10]), "Exp expected" );
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

c_bool calcExp_int(calcExp x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[11])
        || PT_THISNTM((PT_Term)x, CfgSyms[10]), "Exp expected" );
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

c_bool calcExp_neg(calcExp x, calcExp* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[11])
        || PT_THISNTM((PT_Term)x, CfgSyms[10]), "Exp expected" );
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

c_bool calcExp_sub(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[11])
        || PT_THISNTM((PT_Term)x, CfgSyms[10]), "Exp expected" );
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

c_bool calcExp_div(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[11])
        || PT_THISNTM((PT_Term)x, CfgSyms[10]), "Exp expected" );
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

c_bool calcExp_add(calcExp x, calcExp* x1, calcExp* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[12])
        || PT_THISNTM((PT_Term)x, CfgSyms[11])
        || PT_THISNTM((PT_Term)x, CfgSyms[10]), "Exp expected" );
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
