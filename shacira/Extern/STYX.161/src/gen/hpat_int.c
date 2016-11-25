/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [hpat_int.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;
static int initcount_hpat = 0;

void hpat_initSymbols()
{
  if( initcount_hpat == 0 )
  {
    GLS_init();
    assert0(CfgSyms == (symbol*)NULL,"hpatSymbols already initialized");
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
  ++initcount_hpat;
}

void hpat_quitSymbols()
{
  --initcount_hpat;
  if( initcount_hpat == 0 )
  {
    assert0(CfgSyms != (symbol*)NULL,"hpatSymbols not initialized");
    if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
    CfgSyms = (symbol*)NULL;
    if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
    PrdSyms = (symbol*)NULL;
  }
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractType( hpat );

AbstractType( hpatHPatDoc );
AbstractType( hpatContent );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Thpat_PatBgn(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[0]) );
}

c_bool Thpat_PatEnd(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[1]) );
}

c_bool Thpat_PatRef(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[2]) );
}

c_bool Thpat__other_(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[3]) );
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool hpat_hpat(PT_Term x, hpat* x1)
{
  if( PT_THISNTM(x, CfgSyms[7]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (hpat)x;
    return True;
  }
  return False;
}

c_bool hpat_HPatDoc(PT_Term x, hpatHPatDoc* x1)
{
  if(  PT_THISNTM(x, CfgSyms[4]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (hpatHPatDoc)x;
    return True;
  }
  return False;
}

c_bool hpat_Content(PT_Term x, hpatContent* x1)
{
  if(  PT_THISNTM(x, CfgSyms[6]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (hpatContent)x;
    return True;
  }
  return False;
}

/*I--------------------------------- hpat --------------------------------- */

c_bool hpat_Start_HPatDoc(hpat x, hpatHPatDoc* x1)
#define hpat_Start_0   hpat_Start_HPatDoc
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[7]), "hpat expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[6]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (hpatHPatDoc)GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[4], 1, True));
  return True;
}

/*I------------------------------- HPatDoc -------------------------------- */

c_bool hpatHPatDoc_dfn(hpatHPatDoc x, GLS_Lst(hpatContent)* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[4]), "HPatDoc expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[0]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (hpatHPatDoc)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(hpatContent))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(hpatHPatDoc,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(hpatContent))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I------------------------------- Content -------------------------------- */

c_bool hpatContent_pat(hpatContent x, GLS_Tok* x1, GLS_Lst(hpatContent)* x2,
                       GLS_Tok* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[6]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[5]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (hpatContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (hpatContent)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(hpatContent))GLS_ign_Skip(x);
      x = (hpatContent)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(hpatContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(hpatContent,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(hpatContent))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(hpatContent,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool hpatContent_else(hpatContent x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[6]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[4]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (hpatContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(hpatContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool hpatContent_ref(hpatContent x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[6]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[3]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (hpatContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(hpatContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}
