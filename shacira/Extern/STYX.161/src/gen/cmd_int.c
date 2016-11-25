/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [cmd_int.c]                Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;
static int initcount_cmd = 0;

void cmd_initSymbols()
{
  if( initcount_cmd == 0 )
  {
    GLS_init();
    assert0(CfgSyms == (symbol*)NULL,"cmdSymbols already initialized");
    CfgSyms = (symbol*)NewMem(sizeof(symbol)*58);
    PrdSyms = (symbol*)NewMem(sizeof(symbol)*44);

    CfgSyms[0] = stringToSymbol("Parenthesis");
    CfgSyms[1] = stringToSymbol("Ide");
    CfgSyms[2] = stringToSymbol("Int");
    CfgSyms[3] = stringToSymbol("Flo");
    CfgSyms[4] = stringToSymbol("Opr");
    CfgSyms[5] = stringToSymbol("Set");
    CfgSyms[6] = stringToSymbol("Seq");
    CfgSyms[7] = stringToSymbol("Pth");
    CfgSyms[8] = stringToSymbol("Doc");
    CfgSyms[9] = stringToSymbol("Dol");
    CfgSyms[10] = stringToSymbol("MacInc");
    CfgSyms[11] = stringToSymbol("MacDel");
    CfgSyms[12] = stringToSymbol("MacDfn");
    CfgSyms[13] = stringToSymbol("MacSep");
    CfgSyms[14] = stringToSymbol("MacCond");
    CfgSyms[15] = stringToSymbol("Comment");
    CfgSyms[16] = stringToSymbol("Program");
    CfgSyms[17] = stringToSymbol("Arguments");
    CfgSyms[18] = stringToSymbol("Options");
    CfgSyms[19] = stringToSymbol("Environment");
    CfgSyms[20] = stringToSymbol(":");
    CfgSyms[21] = stringToSymbol("=");
    CfgSyms[22] = stringToSymbol("true");
    CfgSyms[23] = stringToSymbol("false");
    CfgSyms[24] = stringToSymbol("<");
    CfgSyms[25] = stringToSymbol(">");
    CfgSyms[26] = stringToSymbol(";");
    CfgSyms[27] = stringToSymbol("$");
    CfgSyms[28] = stringToSymbol("/");
    CfgSyms[29] = stringToSymbol(".");
    CfgSyms[30] = stringToSymbol("..");
    CfgSyms[31] = stringToSymbol("_");
    CfgSyms[32] = stringToSymbol("flag");
    CfgSyms[33] = stringToSymbol("int");
    CfgSyms[34] = stringToSymbol("real");
    CfgSyms[35] = stringToSymbol("string");
    CfgSyms[36] = stringToSymbol("name");
    CfgSyms[37] = stringToSymbol("path");
    CfgSyms[38] = stringToSymbol("Source");
    CfgSyms[39] = stringToSymbol("Dfns");
    CfgSyms[40] = stringToSymbol("Dfn");
    CfgSyms[41] = stringToSymbol("OptVal");
    CfgSyms[42] = stringToSymbol("OptDoc");
    CfgSyms[43] = stringToSymbol("Val");
    CfgSyms[44] = stringToSymbol("PLst1");
    CfgSyms[45] = stringToSymbol("PLst0");
    CfgSyms[46] = stringToSymbol("Path");
    CfgSyms[47] = stringToSymbol("Root1");
    CfgSyms[48] = stringToSymbol("Root2");
    CfgSyms[49] = stringToSymbol("RelPa0");
    CfgSyms[50] = stringToSymbol("RelP1");
    CfgSyms[51] = stringToSymbol("RelP0");
    CfgSyms[52] = stringToSymbol("OptDrv");
    CfgSyms[53] = stringToSymbol("Pid");
    CfgSyms[54] = stringToSymbol("Fid1");
    CfgSyms[55] = stringToSymbol("Fid0");
    CfgSyms[56] = stringToSymbol("Typ");
    CfgSyms[57] = stringToSymbol("cmd");

    PrdSyms[0] = stringToSymbol("root");
    PrdSyms[1] = stringToSymbol("nil");
    PrdSyms[2] = stringToSymbol("cons");
    PrdSyms[3] = stringToSymbol("defn");
    PrdSyms[4] = stringToSymbol("non");
    PrdSyms[5] = stringToSymbol("val");
    PrdSyms[6] = stringToSymbol("non");
    PrdSyms[7] = stringToSymbol("doc");
    PrdSyms[8] = stringToSymbol("true");
    PrdSyms[9] = stringToSymbol("false");
    PrdSyms[10] = stringToSymbol("int");
    PrdSyms[11] = stringToSymbol("real");
    PrdSyms[12] = stringToSymbol("str");
    PrdSyms[13] = stringToSymbol("name");
    PrdSyms[14] = stringToSymbol("path");
    PrdSyms[15] = stringToSymbol("cons");
    PrdSyms[16] = stringToSymbol("nil");
    PrdSyms[17] = stringToSymbol("cons");
    PrdSyms[18] = stringToSymbol("ign1");
    PrdSyms[19] = stringToSymbol("ign2");
    PrdSyms[20] = stringToSymbol("rel");
    PrdSyms[21] = stringToSymbol("env");
    PrdSyms[22] = stringToSymbol("abs");
    PrdSyms[23] = stringToSymbol("abs");
    PrdSyms[24] = stringToSymbol("nil");
    PrdSyms[25] = stringToSymbol("cons");
    PrdSyms[26] = stringToSymbol("nil");
    PrdSyms[27] = stringToSymbol("cons");
    PrdSyms[28] = stringToSymbol("non");
    PrdSyms[29] = stringToSymbol("drive");
    PrdSyms[30] = stringToSymbol("curr");
    PrdSyms[31] = stringToSymbol("prev");
    PrdSyms[32] = stringToSymbol("name");
    PrdSyms[33] = stringToSymbol("ext");
    PrdSyms[34] = stringToSymbol("cons");
    PrdSyms[35] = stringToSymbol("nil");
    PrdSyms[36] = stringToSymbol("cons");
    PrdSyms[37] = stringToSymbol("flag");
    PrdSyms[38] = stringToSymbol("int");
    PrdSyms[39] = stringToSymbol("real");
    PrdSyms[40] = stringToSymbol("str");
    PrdSyms[41] = stringToSymbol("name");
    PrdSyms[42] = stringToSymbol("path");
    PrdSyms[43] = stringToSymbol("Start_Source");
  }
  ++initcount_cmd;
}

void cmd_quitSymbols()
{
  --initcount_cmd;
  if( initcount_cmd == 0 )
  {
    assert0(CfgSyms != (symbol*)NULL,"cmdSymbols not initialized");
    if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
    CfgSyms = (symbol*)NULL;
    if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
    PrdSyms = (symbol*)NULL;
  }
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractType( cmd );

AbstractType( cmdSource );
AbstractType( cmdDfn );
AbstractType( cmdOptVal );
AbstractType( cmdOptDoc );
AbstractType( cmdVal );
AbstractType( cmdPath );
AbstractType( cmdOptDrv );
AbstractType( cmdPid );
AbstractType( cmdTyp );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Tcmd_Ide(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[1]) );
}

c_bool Tcmd_Int(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[2]) );
}

c_bool Tcmd_Flo(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[3]) );
}

c_bool Tcmd_Seq(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[6]) );
}

c_bool Tcmd_Doc(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[8]) );
}

c_bool Tcmd_Dol(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[9]) );
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool cmd_cmd(PT_Term x, cmd* x1)
{
  if( PT_THISNTM(x, CfgSyms[57]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmd)x;
    return True;
  }
  return False;
}

c_bool cmd_Source(PT_Term x, cmdSource* x1)
{
  if(  PT_THISNTM(x, CfgSyms[38]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdSource)x;
    return True;
  }
  return False;
}

c_bool cmd_Dfn(PT_Term x, cmdDfn* x1)
{
  if(  PT_THISNTM(x, CfgSyms[40]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdDfn)x;
    return True;
  }
  return False;
}

c_bool cmd_OptVal(PT_Term x, cmdOptVal* x1)
{
  if(  PT_THISNTM(x, CfgSyms[41]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdOptVal)x;
    return True;
  }
  return False;
}

c_bool cmd_OptDoc(PT_Term x, cmdOptDoc* x1)
{
  if(  PT_THISNTM(x, CfgSyms[42]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdOptDoc)x;
    return True;
  }
  return False;
}

c_bool cmd_Val(PT_Term x, cmdVal* x1)
{
  if(  PT_THISNTM(x, CfgSyms[43]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdVal)x;
    return True;
  }
  return False;
}

c_bool cmd_Path(PT_Term x, cmdPath* x1)
{
  if(  PT_THISNTM(x, CfgSyms[46])
    || PT_THISNTM(x, CfgSyms[47])
    || PT_THISNTM(x, CfgSyms[48]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdPath)x;
    return True;
  }
  return False;
}

c_bool cmd_OptDrv(PT_Term x, cmdOptDrv* x1)
{
  if(  PT_THISNTM(x, CfgSyms[52]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdOptDrv)x;
    return True;
  }
  return False;
}

c_bool cmd_Pid(PT_Term x, cmdPid* x1)
{
  if(  PT_THISNTM(x, CfgSyms[53]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdPid)x;
    return True;
  }
  return False;
}

c_bool cmd_Typ(PT_Term x, cmdTyp* x1)
{
  if(  PT_THISNTM(x, CfgSyms[56]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (cmdTyp)x;
    return True;
  }
  return False;
}

/*I--------------------------------- cmd ---------------------------------- */

c_bool cmd_Start_Source(cmd x, cmdSource* x1)
#define cmd_Start_0   cmd_Start_Source
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[57]), "cmd expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[43]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (cmdSource)GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[38], 1, True));
  return True;
}

/*I-------------------------------- Source -------------------------------- */

c_bool cmdSource_root(cmdSource x, GLS_Lst(GLS_Tok)* x1, GLS_Tok* x2,
                      GLS_Tok* x3, GLS_Lst(cmdDfn)* x4,
                      cmdOptDoc* x5, GLS_Lst(cmdDfn)* x6,
                      cmdOptDoc* x7, GLS_Lst(cmdDfn)* x8,
                      cmdOptDoc* x9)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[38]), "Source expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[0]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdSource)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(x);
      x = (cmdSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(x);
      x = (cmdSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Tok)GLS_ign_Skip(x);
      x = (cmdSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Lst(cmdDfn))GLS_ign_Skip(x);
      x = (cmdSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x5 != (StdCPtr)NULL )
        *x5 = (cmdOptDoc)GLS_ign_Skip(x);
      x = (cmdSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x6 != (StdCPtr)NULL )
        *x6 = (GLS_Lst(cmdDfn))GLS_ign_Skip(x);
      x = (cmdSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x7 != (StdCPtr)NULL )
        *x7 = (cmdOptDoc)GLS_ign_Skip(x);
      x = (cmdSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x8 != (StdCPtr)NULL )
        *x8 = (GLS_Lst(cmdDfn))GLS_ign_Skip(x);
      x = (cmdSource)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x9 != (StdCPtr)NULL )
        *x9 = (cmdOptDoc)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Lst(cmdDfn))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x5 != (StdCPtr)NULL )
        *x5 = (cmdOptDoc)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x6 != (StdCPtr)NULL )
        *x6 = (GLS_Lst(cmdDfn))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x7 != (StdCPtr)NULL )
        *x7 = (cmdOptDoc)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x8 != (StdCPtr)NULL )
        *x8 = (GLS_Lst(cmdDfn))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdSource,x);
      if( (StdCPtr)x9 != (StdCPtr)NULL )
        *x9 = (cmdOptDoc)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Dfn ---------------------------------- */

c_bool cmdDfn_defn(cmdDfn x, GLS_Tok* x1, cmdTyp* x2,
                   cmdOptVal* x3, GLS_Tok* x4)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[40]), "Dfn expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[3]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdDfn)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (cmdDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (cmdTyp)GLS_ign_Skip(x);
      x = (cmdDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (cmdOptVal)GLS_ign_Skip(x);
      x = (cmdDfn)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdDfn,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdDfn,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (cmdTyp)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdDfn,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (cmdOptVal)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdDfn,x);
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- OptVal -------------------------------- */

c_bool cmdOptVal_non(cmdOptVal x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[41]), "OptVal expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[4]) ) return False;
  return True;
}

c_bool cmdOptVal_val(cmdOptVal x, cmdVal* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[41]), "OptVal expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[5]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdOptVal)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (cmdVal)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdOptVal,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (cmdVal)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- OptDoc -------------------------------- */

c_bool cmdOptDoc_non(cmdOptDoc x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[42]), "OptDoc expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[6]) ) return False;
  return True;
}

c_bool cmdOptDoc_doc(cmdOptDoc x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[42]), "OptDoc expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[7]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdOptDoc)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdOptDoc,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Val ---------------------------------- */

c_bool cmdVal_false(cmdVal x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Val expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[9]) ) return False;
  return True;
}

c_bool cmdVal_str(cmdVal x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Val expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[12]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdVal)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdVal,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool cmdVal_int(cmdVal x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Val expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[10]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdVal)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdVal,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool cmdVal_true(cmdVal x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Val expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[8]) ) return False;
  return True;
}

c_bool cmdVal_name(cmdVal x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Val expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[13]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdVal)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdVal,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool cmdVal_real(cmdVal x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Val expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[11]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdVal)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdVal,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool cmdVal_path(cmdVal x, GLS_Lst(cmdPath)* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[43]), "Val expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[14]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdVal)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(cmdPath))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdVal,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(cmdPath))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Path --------------------------------- */

c_bool cmdPath_rel(cmdPath x, GLS_Lst(cmdPid)* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[46])
        || PT_THISNTM((PT_Term)x, CfgSyms[47])
        || PT_THISNTM((PT_Term)x, CfgSyms[48]), "Path expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[20]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdPath)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(cmdPid))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdPath,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(cmdPid))GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool cmdPath_env(cmdPath x, GLS_Tok* x1, GLS_Lst(cmdPid)* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[46])
        || PT_THISNTM((PT_Term)x, CfgSyms[47])
        || PT_THISNTM((PT_Term)x, CfgSyms[48]), "Path expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[21]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdPath)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (cmdPath)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(cmdPid))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdPath,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdPath,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(cmdPid))GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool cmdPath_abs(cmdPath x, cmdOptDrv* x1, GLS_Lst(cmdPid)* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[46])
        || PT_THISNTM((PT_Term)x, CfgSyms[47])
        || PT_THISNTM((PT_Term)x, CfgSyms[48]), "Path expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[22]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdPath)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (cmdOptDrv)GLS_ign_Skip(x);
      x = (cmdPath)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(cmdPid))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdPath,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (cmdOptDrv)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdPath,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(cmdPid))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- OptDrv -------------------------------- */

c_bool cmdOptDrv_non(cmdOptDrv x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[52]), "OptDrv expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[28]) ) return False;
  return True;
}

c_bool cmdOptDrv_drive(cmdOptDrv x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[52]), "OptDrv expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[29]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdOptDrv)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdOptDrv,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Pid ---------------------------------- */

c_bool cmdPid_curr(cmdPid x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[53]), "Pid expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[30]) ) return False;
  return True;
}

c_bool cmdPid_ext(cmdPid x, GLS_Lst(GLS_Tok)* x1, GLS_Tok* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[53]), "Pid expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[33]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdPid)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(x);
      x = (cmdPid)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdPid,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(cmdPid,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool cmdPid_prev(cmdPid x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[53]), "Pid expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[31]) ) return False;
  return True;
}

c_bool cmdPid_name(cmdPid x, GLS_Lst(GLS_Tok)* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[53]), "Pid expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[32]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (cmdPid)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(cmdPid,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(GLS_Tok))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Typ ---------------------------------- */

c_bool cmdTyp_real(cmdTyp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[56]), "Typ expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[39]) ) return False;
  return True;
}

c_bool cmdTyp_int(cmdTyp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[56]), "Typ expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[38]) ) return False;
  return True;
}

c_bool cmdTyp_path(cmdTyp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[56]), "Typ expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[42]) ) return False;
  return True;
}

c_bool cmdTyp_name(cmdTyp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[56]), "Typ expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[41]) ) return False;
  return True;
}

c_bool cmdTyp_flag(cmdTyp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[56]), "Typ expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[37]) ) return False;
  return True;
}

c_bool cmdTyp_str(cmdTyp x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[56]), "Typ expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[40]) ) return False;
  return True;
}
