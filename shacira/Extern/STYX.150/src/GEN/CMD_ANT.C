/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [cmd_ant.c]                Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls_abs.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;

void cmd_initSymbols()
{
  GLS_init();
  CfgSyms = (symbol*)NewMem(sizeof(symbol)*57);
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
  CfgSyms[11] = stringToSymbol("MacDfn");
  CfgSyms[12] = stringToSymbol("MacSep");
  CfgSyms[13] = stringToSymbol("MacCond");
  CfgSyms[14] = stringToSymbol("Comment");
  CfgSyms[15] = stringToSymbol("Program");
  CfgSyms[16] = stringToSymbol("Arguments");
  CfgSyms[17] = stringToSymbol("Options");
  CfgSyms[18] = stringToSymbol("Environment");
  CfgSyms[19] = stringToSymbol(":");
  CfgSyms[20] = stringToSymbol("=");
  CfgSyms[21] = stringToSymbol("true");
  CfgSyms[22] = stringToSymbol("false");
  CfgSyms[23] = stringToSymbol("<");
  CfgSyms[24] = stringToSymbol(">");
  CfgSyms[25] = stringToSymbol(";");
  CfgSyms[26] = stringToSymbol("$");
  CfgSyms[27] = stringToSymbol("/");
  CfgSyms[28] = stringToSymbol(".");
  CfgSyms[29] = stringToSymbol("..");
  CfgSyms[30] = stringToSymbol("_");
  CfgSyms[31] = stringToSymbol("flag");
  CfgSyms[32] = stringToSymbol("int");
  CfgSyms[33] = stringToSymbol("real");
  CfgSyms[34] = stringToSymbol("string");
  CfgSyms[35] = stringToSymbol("name");
  CfgSyms[36] = stringToSymbol("path");
  CfgSyms[37] = stringToSymbol("Source");
  CfgSyms[38] = stringToSymbol("Dfns");
  CfgSyms[39] = stringToSymbol("Dfn");
  CfgSyms[40] = stringToSymbol("OptVal");
  CfgSyms[41] = stringToSymbol("OptDoc");
  CfgSyms[42] = stringToSymbol("Val");
  CfgSyms[43] = stringToSymbol("PLst1");
  CfgSyms[44] = stringToSymbol("PLst0");
  CfgSyms[45] = stringToSymbol("Path");
  CfgSyms[46] = stringToSymbol("Root1");
  CfgSyms[47] = stringToSymbol("Root2");
  CfgSyms[48] = stringToSymbol("RelPa0");
  CfgSyms[49] = stringToSymbol("RelP1");
  CfgSyms[50] = stringToSymbol("RelP0");
  CfgSyms[51] = stringToSymbol("OptDrv");
  CfgSyms[52] = stringToSymbol("Pid");
  CfgSyms[53] = stringToSymbol("Fid1");
  CfgSyms[54] = stringToSymbol("Fid0");
  CfgSyms[55] = stringToSymbol("Typ");
  CfgSyms[56] = stringToSymbol("cmd");

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

void cmd_quitSymbols()
{
  if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
  if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractHugeType( cmd );

AbstractHugeType( cmdSource );
AbstractHugeType( cmdDfn );
AbstractHugeType( cmdOptVal );
AbstractHugeType( cmdOptDoc );
AbstractHugeType( cmdVal );
AbstractHugeType( cmdPath );
AbstractHugeType( cmdOptDrv );
AbstractHugeType( cmdPid );
AbstractHugeType( cmdTyp );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Tcmd_Ide(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[1];
}

c_bool Tcmd_Int(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[2];
}

c_bool Tcmd_Flo(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[3];
}

c_bool Tcmd_Seq(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[6];
}

c_bool Tcmd_Doc(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[8];
}

c_bool Tcmd_Dol(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[9];
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool cmd_cmd(PT_Abs_Term x, cmd* x1)
{
  if( PT_Abs_nonterm(x) == CfgSyms[56] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmd)x;
    return True;
  }
  return False;
}

c_bool cmd_Source(PT_Abs_Term x, cmdSource* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[37] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdSource)x;
    return True;
  }
  return False;
}

c_bool cmd_Dfn(PT_Abs_Term x, cmdDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[39] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdDfn)x;
    return True;
  }
  return False;
}

c_bool cmd_OptVal(PT_Abs_Term x, cmdOptVal* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[40] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdOptVal)x;
    return True;
  }
  return False;
}

c_bool cmd_OptDoc(PT_Abs_Term x, cmdOptDoc* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[41] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdOptDoc)x;
    return True;
  }
  return False;
}

c_bool cmd_Val(PT_Abs_Term x, cmdVal* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[42] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdVal)x;
    return True;
  }
  return False;
}

c_bool cmd_Path(PT_Abs_Term x, cmdPath* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[45]
    || PT_Abs_nonterm(x) == CfgSyms[46]
    || PT_Abs_nonterm(x) == CfgSyms[47] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdPath)x;
    return True;
  }
  return False;
}

c_bool cmd_OptDrv(PT_Abs_Term x, cmdOptDrv* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[51] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdOptDrv)x;
    return True;
  }
  return False;
}

c_bool cmd_Pid(PT_Abs_Term x, cmdPid* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[52] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdPid)x;
    return True;
  }
  return False;
}

c_bool cmd_Typ(PT_Abs_Term x, cmdTyp* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[55] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdTyp)x;
    return True;
  }
  return False;
}

/*I--------------------------------- cmd ---------------------------------- */

c_bool cmd_Start_Source(cmd x, cmdSource* x1)
#define cmd_Start_0   cmd_Start_Source
{
  assert0( PT_Abs_nonterm(x) == CfgSyms[56], "cmd expected" );
  if( PT_Abs_product(x) != PrdSyms[43] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL )
    *x1 = (cmdSource)PT_Abs_part(x,0);
  return True;
}

/*I-------------------------------- Source -------------------------------- */

c_bool cmdSource_root(cmdSource x, GLS_Lst(GLS_Tok)* x1, GLS_Tok* x2,
                      GLS_Tok* x3, GLS_Lst(cmdDfn)* x4,
                      cmdOptDoc* x5, GLS_Lst(cmdDfn)* x6,
                      cmdOptDoc* x7, GLS_Lst(cmdDfn)* x8,
                      cmdOptDoc* x9)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[37], "Source expected" );
  if( PT_Abs_product(x) != PrdSyms[0] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(GLS_Tok))PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Tok)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Tok)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (GLS_Lst(cmdDfn))PT_Abs_part(x,3);
  if( (HugeCPtr)x5 != (HugeCPtr)NULL ) *x5 = (cmdOptDoc)PT_Abs_part(x,4);
  if( (HugeCPtr)x6 != (HugeCPtr)NULL ) *x6 = (GLS_Lst(cmdDfn))PT_Abs_part(x,5);
  if( (HugeCPtr)x7 != (HugeCPtr)NULL ) *x7 = (cmdOptDoc)PT_Abs_part(x,6);
  if( (HugeCPtr)x8 != (HugeCPtr)NULL ) *x8 = (GLS_Lst(cmdDfn))PT_Abs_part(x,7);
  if( (HugeCPtr)x9 != (HugeCPtr)NULL ) *x9 = (cmdOptDoc)PT_Abs_part(x,8);
  return True;
}

/*I--------------------------------- Dfn ---------------------------------- */

c_bool cmdDfn_defn(cmdDfn x, GLS_Tok* x1, cmdTyp* x2,
                   cmdOptVal* x3, GLS_Tok* x4)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[39], "Dfn expected" );
  if( PT_Abs_product(x) != PrdSyms[3] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cmdTyp)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (cmdOptVal)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (GLS_Tok)PT_Abs_part(x,3);
  return True;
}

/*I-------------------------------- OptVal -------------------------------- */

c_bool cmdOptVal_non(cmdOptVal x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[40], "OptVal expected" );
  if( PT_Abs_product(x) != PrdSyms[4] ) return False;
  return True;
}

c_bool cmdOptVal_val(cmdOptVal x, cmdVal* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[40], "OptVal expected" );
  if( PT_Abs_product(x) != PrdSyms[5] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdVal)PT_Abs_part(x,0);
  return True;
}

/*I-------------------------------- OptDoc -------------------------------- */

c_bool cmdOptDoc_non(cmdOptDoc x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[41], "OptDoc expected" );
  if( PT_Abs_product(x) != PrdSyms[6] ) return False;
  return True;
}

c_bool cmdOptDoc_doc(cmdOptDoc x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[41], "OptDoc expected" );
  if( PT_Abs_product(x) != PrdSyms[7] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Val ---------------------------------- */

c_bool cmdVal_false(cmdVal x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "Val expected" );
  if( PT_Abs_product(x) != PrdSyms[9] ) return False;
  return True;
}

c_bool cmdVal_str(cmdVal x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "Val expected" );
  if( PT_Abs_product(x) != PrdSyms[12] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool cmdVal_int(cmdVal x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "Val expected" );
  if( PT_Abs_product(x) != PrdSyms[10] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool cmdVal_true(cmdVal x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "Val expected" );
  if( PT_Abs_product(x) != PrdSyms[8] ) return False;
  return True;
}

c_bool cmdVal_name(cmdVal x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "Val expected" );
  if( PT_Abs_product(x) != PrdSyms[13] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool cmdVal_real(cmdVal x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "Val expected" );
  if( PT_Abs_product(x) != PrdSyms[11] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool cmdVal_path(cmdVal x, GLS_Lst(cmdPath)* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "Val expected" );
  if( PT_Abs_product(x) != PrdSyms[14] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(cmdPath))PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Path --------------------------------- */

c_bool cmdPath_rel(cmdPath x, GLS_Lst(cmdPid)* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[46]
        || PT_Abs_nonterm(x) == CfgSyms[47], "Path expected" );
  if( PT_Abs_product(x) != PrdSyms[20] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(cmdPid))PT_Abs_part(x,0);
  return True;
}

c_bool cmdPath_env(cmdPath x, GLS_Tok* x1, GLS_Lst(cmdPid)* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[46]
        || PT_Abs_nonterm(x) == CfgSyms[47], "Path expected" );
  if( PT_Abs_product(x) != PrdSyms[21] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Lst(cmdPid))PT_Abs_part(x,1);
  return True;
}

c_bool cmdPath_abs(cmdPath x, cmdOptDrv* x1, GLS_Lst(cmdPid)* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[46]
        || PT_Abs_nonterm(x) == CfgSyms[47], "Path expected" );
  if( PT_Abs_product(x) != PrdSyms[22] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cmdOptDrv)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Lst(cmdPid))PT_Abs_part(x,1);
  return True;
}

/*I-------------------------------- OptDrv -------------------------------- */

c_bool cmdOptDrv_non(cmdOptDrv x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[51], "OptDrv expected" );
  if( PT_Abs_product(x) != PrdSyms[28] ) return False;
  return True;
}

c_bool cmdOptDrv_drive(cmdOptDrv x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[51], "OptDrv expected" );
  if( PT_Abs_product(x) != PrdSyms[29] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Pid ---------------------------------- */

c_bool cmdPid_curr(cmdPid x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "Pid expected" );
  if( PT_Abs_product(x) != PrdSyms[30] ) return False;
  return True;
}

c_bool cmdPid_ext(cmdPid x, GLS_Lst(GLS_Tok)* x1, GLS_Tok* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "Pid expected" );
  if( PT_Abs_product(x) != PrdSyms[33] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(GLS_Tok))PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Tok)PT_Abs_part(x,1);
  return True;
}

c_bool cmdPid_prev(cmdPid x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "Pid expected" );
  if( PT_Abs_product(x) != PrdSyms[31] ) return False;
  return True;
}

c_bool cmdPid_name(cmdPid x, GLS_Lst(GLS_Tok)* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "Pid expected" );
  if( PT_Abs_product(x) != PrdSyms[32] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Lst(GLS_Tok))PT_Abs_part(x,0);
  return True;
}

/*I--------------------------------- Typ ---------------------------------- */

c_bool cmdTyp_real(cmdTyp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "Typ expected" );
  if( PT_Abs_product(x) != PrdSyms[39] ) return False;
  return True;
}

c_bool cmdTyp_int(cmdTyp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "Typ expected" );
  if( PT_Abs_product(x) != PrdSyms[38] ) return False;
  return True;
}

c_bool cmdTyp_path(cmdTyp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "Typ expected" );
  if( PT_Abs_product(x) != PrdSyms[42] ) return False;
  return True;
}

c_bool cmdTyp_name(cmdTyp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "Typ expected" );
  if( PT_Abs_product(x) != PrdSyms[41] ) return False;
  return True;
}

c_bool cmdTyp_flag(cmdTyp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "Typ expected" );
  if( PT_Abs_product(x) != PrdSyms[37] ) return False;
  return True;
}

c_bool cmdTyp_str(cmdTyp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "Typ expected" );
  if( PT_Abs_product(x) != PrdSyms[40] ) return False;
  return True;
}
