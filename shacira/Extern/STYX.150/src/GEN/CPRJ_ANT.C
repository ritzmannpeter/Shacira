/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [cprj_ant.c]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls_abs.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;

void cprj_initSymbols()
{
  GLS_init();
  CfgSyms = (symbol*)NewMem(sizeof(symbol)*60);
  PrdSyms = (symbol*)NewMem(sizeof(symbol)*59);

  CfgSyms[0] = stringToSymbol("Name");
  CfgSyms[1] = stringToSymbol("Opr");
  CfgSyms[2] = stringToSymbol("Val");
  CfgSyms[3] = stringToSymbol("Comment");
  CfgSyms[4] = stringToSymbol("MacInc");
  CfgSyms[5] = stringToSymbol("MMacDfn");
  CfgSyms[6] = stringToSymbol("MacSep");
  CfgSyms[7] = stringToSymbol("MacCond");
  CfgSyms[8] = stringToSymbol(".eq.");
  CfgSyms[9] = stringToSymbol(".le.");
  CfgSyms[10] = stringToSymbol(".lt.");
  CfgSyms[11] = stringToSymbol(".ge.");
  CfgSyms[12] = stringToSymbol(".gt.");
  CfgSyms[13] = stringToSymbol(".ne.");
  CfgSyms[14] = stringToSymbol("?");
  CfgSyms[15] = stringToSymbol(":");
  CfgSyms[16] = stringToSymbol("use");
  CfgSyms[17] = stringToSymbol("Macro");
  CfgSyms[18] = stringToSymbol("Type");
  CfgSyms[19] = stringToSymbol("exec");
  CfgSyms[20] = stringToSymbol("Rule");
  CfgSyms[21] = stringToSymbol("build");
  CfgSyms[22] = stringToSymbol("from");
  CfgSyms[23] = stringToSymbol("!");
  CfgSyms[24] = stringToSymbol("-");
  CfgSyms[25] = stringToSymbol("TPrefix");
  CfgSyms[26] = stringToSymbol("SPrefix");
  CfgSyms[27] = stringToSymbol("by");
  CfgSyms[28] = stringToSymbol("Command");
  CfgSyms[29] = stringToSymbol("Root");
  CfgSyms[30] = stringToSymbol("Source");
  CfgSyms[31] = stringToSymbol("Directory");
  CfgSyms[32] = stringToSymbol("RegExp");
  CfgSyms[33] = stringToSymbol("recursive");
  CfgSyms[34] = stringToSymbol("Project");
  CfgSyms[35] = stringToSymbol("Targets");
  CfgSyms[36] = stringToSymbol("Objects");
  CfgSyms[37] = stringToSymbol("Externals");
  CfgSyms[38] = stringToSymbol("Optional");
  CfgSyms[39] = stringToSymbol("Libraries");
  CfgSyms[40] = stringToSymbol("Parameter");
  CfgSyms[41] = stringToSymbol("Repository");
  CfgSyms[42] = stringToSymbol("ProjectDfn");
  CfgSyms[43] = stringToSymbol("RelOp");
  CfgSyms[44] = stringToSymbol("MacDfn");
  CfgSyms[45] = stringToSymbol("Project");
  CfgSyms[46] = stringToSymbol("Project1");
  CfgSyms[47] = stringToSymbol("Project2");
  CfgSyms[48] = stringToSymbol("RuleAttr");
  CfgSyms[49] = stringToSymbol("OptTPrefix");
  CfgSyms[50] = stringToSymbol("OptSPrefix");
  CfgSyms[51] = stringToSymbol("DstDfn");
  CfgSyms[52] = stringToSymbol("DstName");
  CfgSyms[53] = stringToSymbol("RegExp");
  CfgSyms[54] = stringToSymbol("SrcAttr");
  CfgSyms[55] = stringToSymbol("SrcDfn");
  CfgSyms[56] = stringToSymbol("TypDfn");
  CfgSyms[57] = stringToSymbol("Project0");
  CfgSyms[58] = stringToSymbol("Project3");
  CfgSyms[59] = stringToSymbol("cprj");

  PrdSyms[0] = stringToSymbol("root");
  PrdSyms[1] = stringToSymbol("eq");
  PrdSyms[2] = stringToSymbol("le");
  PrdSyms[3] = stringToSymbol("lt");
  PrdSyms[4] = stringToSymbol("ge");
  PrdSyms[5] = stringToSymbol("gt");
  PrdSyms[6] = stringToSymbol("ne");
  PrdSyms[7] = stringToSymbol("val");
  PrdSyms[8] = stringToSymbol("cond");
  PrdSyms[9] = stringToSymbol("inc");
  PrdSyms[10] = stringToSymbol("mac");
  PrdSyms[11] = stringToSymbol("typ");
  PrdSyms[12] = stringToSymbol("exec");
  PrdSyms[13] = stringToSymbol("rule");
  PrdSyms[14] = stringToSymbol("ign0");
  PrdSyms[15] = stringToSymbol("inc");
  PrdSyms[16] = stringToSymbol("ign0");
  PrdSyms[17] = stringToSymbol("nul");
  PrdSyms[18] = stringToSymbol("nul");
  PrdSyms[19] = stringToSymbol("exe");
  PrdSyms[20] = stringToSymbol("ex2");
  PrdSyms[21] = stringToSymbol("nul");
  PrdSyms[22] = stringToSymbol("pre");
  PrdSyms[23] = stringToSymbol("nul");
  PrdSyms[24] = stringToSymbol("pre");
  PrdSyms[25] = stringToSymbol("ext");
  PrdSyms[26] = stringToSymbol("int");
  PrdSyms[27] = stringToSymbol("root");
  PrdSyms[28] = stringToSymbol("src");
  PrdSyms[29] = stringToSymbol("dir");
  PrdSyms[30] = stringToSymbol("nam");
  PrdSyms[31] = stringToSymbol("nul");
  PrdSyms[32] = stringToSymbol("exp");
  PrdSyms[33] = stringToSymbol("exp");
  PrdSyms[34] = stringToSymbol("rexp");
  PrdSyms[35] = stringToSymbol("dfn");
  PrdSyms[36] = stringToSymbol("one");
  PrdSyms[37] = stringToSymbol("two");
  PrdSyms[38] = stringToSymbol("dprj");
  PrdSyms[39] = stringToSymbol("ddst");
  PrdSyms[40] = stringToSymbol("dobj");
  PrdSyms[41] = stringToSymbol("ext");
  PrdSyms[42] = stringToSymbol("oext");
  PrdSyms[43] = stringToSymbol("lib");
  PrdSyms[44] = stringToSymbol("cmd");
  PrdSyms[45] = stringToSymbol("par");
  PrdSyms[46] = stringToSymbol("res");
  PrdSyms[47] = stringToSymbol("ign0");
  PrdSyms[48] = stringToSymbol("dprj");
  PrdSyms[49] = stringToSymbol("ddst");
  PrdSyms[50] = stringToSymbol("dobj");
  PrdSyms[51] = stringToSymbol("ext");
  PrdSyms[52] = stringToSymbol("oext");
  PrdSyms[53] = stringToSymbol("lib");
  PrdSyms[54] = stringToSymbol("cmd");
  PrdSyms[55] = stringToSymbol("par");
  PrdSyms[56] = stringToSymbol("res");
  PrdSyms[57] = stringToSymbol("ign0");
  PrdSyms[58] = stringToSymbol("Start_ProjectDfn");
}

void cprj_quitSymbols()
{
  if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
  if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractHugeType( cprj );

AbstractHugeType( cprjProjectDfn );
AbstractHugeType( cprjRelOp );
AbstractHugeType( cprjMacDfn );
AbstractHugeType( cprjProject );
AbstractHugeType( cprjRuleAttr );
AbstractHugeType( cprjOptTPrefix );
AbstractHugeType( cprjOptSPrefix );
AbstractHugeType( cprjDstDfn );
AbstractHugeType( cprjDstName );
AbstractHugeType( cprjRegExp );
AbstractHugeType( cprjSrcAttr );
AbstractHugeType( cprjSrcDfn );
AbstractHugeType( cprjTypDfn );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Tcprj_Name(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[0];
}

c_bool Tcprj_Val(GLS_Tok x)
{
  return PT_Abs_token(x) == CfgSyms[2];
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool cprj_cprj(PT_Abs_Term x, cprj* x1)
{
  if( PT_Abs_nonterm(x) == CfgSyms[59] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprj)x;
    return True;
  }
  return False;
}

c_bool cprj_ProjectDfn(PT_Abs_Term x, cprjProjectDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[42] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjProjectDfn)x;
    return True;
  }
  return False;
}

c_bool cprj_RelOp(PT_Abs_Term x, cprjRelOp* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[43] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjRelOp)x;
    return True;
  }
  return False;
}

c_bool cprj_MacDfn(PT_Abs_Term x, cprjMacDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[44] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjMacDfn)x;
    return True;
  }
  return False;
}

c_bool cprj_Project(PT_Abs_Term x, cprjProject* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[47]
    || PT_Abs_nonterm(x) == CfgSyms[57]
    || PT_Abs_nonterm(x) == CfgSyms[45]
    || PT_Abs_nonterm(x) == CfgSyms[58]
    || PT_Abs_nonterm(x) == CfgSyms[46] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjProject)x;
    return True;
  }
  return False;
}

c_bool cprj_RuleAttr(PT_Abs_Term x, cprjRuleAttr* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[48] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjRuleAttr)x;
    return True;
  }
  return False;
}

c_bool cprj_OptTPrefix(PT_Abs_Term x, cprjOptTPrefix* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[49] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjOptTPrefix)x;
    return True;
  }
  return False;
}

c_bool cprj_OptSPrefix(PT_Abs_Term x, cprjOptSPrefix* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[50] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjOptSPrefix)x;
    return True;
  }
  return False;
}

c_bool cprj_DstDfn(PT_Abs_Term x, cprjDstDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[51] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjDstDfn)x;
    return True;
  }
  return False;
}

c_bool cprj_DstName(PT_Abs_Term x, cprjDstName* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[52] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjDstName)x;
    return True;
  }
  return False;
}

c_bool cprj_RegExp(PT_Abs_Term x, cprjRegExp* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[53] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjRegExp)x;
    return True;
  }
  return False;
}

c_bool cprj_SrcAttr(PT_Abs_Term x, cprjSrcAttr* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[54] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjSrcAttr)x;
    return True;
  }
  return False;
}

c_bool cprj_SrcDfn(PT_Abs_Term x, cprjSrcDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[55] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjSrcDfn)x;
    return True;
  }
  return False;
}

c_bool cprj_TypDfn(PT_Abs_Term x, cprjTypDfn* x1)
{
  if(  PT_Abs_nonterm(x) == CfgSyms[56] )
  {
    if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjTypDfn)x;
    return True;
  }
  return False;
}

/*I--------------------------------- cprj --------------------------------- */

c_bool cprj_Start_ProjectDfn(cprj x, cprjProjectDfn* x1)
#define cprj_Start_0   cprj_Start_ProjectDfn
{
  assert0( PT_Abs_nonterm(x) == CfgSyms[59], "cprj expected" );
  if( PT_Abs_product(x) != PrdSyms[58] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL )
    *x1 = (cprjProjectDfn)PT_Abs_part(x,0);
  return True;
}

/*I------------------------------ ProjectDfn ------------------------------ */

c_bool cprjProjectDfn_root(cprjProjectDfn x, cprjProject* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[42], "ProjectDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[0] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjProject)PT_Abs_part(x,0);
  return True;
}

/*I-------------------------------- RelOp --------------------------------- */

c_bool cprjRelOp_le(cprjRelOp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "RelOp expected" );
  if( PT_Abs_product(x) != PrdSyms[2] ) return False;
  return True;
}

c_bool cprjRelOp_eq(cprjRelOp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "RelOp expected" );
  if( PT_Abs_product(x) != PrdSyms[1] ) return False;
  return True;
}

c_bool cprjRelOp_ne(cprjRelOp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "RelOp expected" );
  if( PT_Abs_product(x) != PrdSyms[6] ) return False;
  return True;
}

c_bool cprjRelOp_gt(cprjRelOp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "RelOp expected" );
  if( PT_Abs_product(x) != PrdSyms[5] ) return False;
  return True;
}

c_bool cprjRelOp_ge(cprjRelOp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "RelOp expected" );
  if( PT_Abs_product(x) != PrdSyms[4] ) return False;
  return True;
}

c_bool cprjRelOp_lt(cprjRelOp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[43], "RelOp expected" );
  if( PT_Abs_product(x) != PrdSyms[3] ) return False;
  return True;
}

/*I-------------------------------- MacDfn -------------------------------- */

c_bool cprjMacDfn_cond(cprjMacDfn x, GLS_Tok* x1, cprjRelOp* x2,
                       GLS_Tok* x3, GLS_Tok* x4,
                       GLS_Tok* x5)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[44], "MacDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[8] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjRelOp)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Tok)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (GLS_Tok)PT_Abs_part(x,3);
  if( (HugeCPtr)x5 != (HugeCPtr)NULL ) *x5 = (GLS_Tok)PT_Abs_part(x,4);
  return True;
}

c_bool cprjMacDfn_val(cprjMacDfn x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[44], "MacDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[7] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

/*I------------------------------- Project -------------------------------- */

c_bool cprjProject_dprj(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[38] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_exec(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[12] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_oext(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[42] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_mac(cprjProject x, GLS_Tok* x1, cprjMacDfn* x2,
                       cprjProject* x3)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[10] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjMacDfn)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (cprjProject)PT_Abs_part(x,2);
  return True;
}

c_bool cprjProject_cmd(cprjProject x, GLS_Tok* x1, GLS_Tok* x2,
                       cprjProject* x3)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[44] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Tok)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (cprjProject)PT_Abs_part(x,2);
  return True;
}

c_bool cprjProject_res(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[46] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_lib(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[43] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_typ(cprjProject x, cprjTypDfn* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[11] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjTypDfn)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_inc(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[9] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_par(cprjProject x, GLS_Tok* x1, GLS_Tok* x2,
                       GLS_Tok* x3, cprjProject* x4)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[45] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Tok)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (GLS_Tok)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (cprjProject)PT_Abs_part(x,3);
  return True;
}

c_bool cprjProject_ddst(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[39] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_ext(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[41] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

c_bool cprjProject_nul(cprjProject x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[17] ) return False;
  return True;
}

c_bool cprjProject_rule(cprjProject x, GLS_Tok* x1, cprjRuleAttr* x2,
                        cprjDstDfn* x3, cprjProject* x4,
                        GLS_Tok* x5, cprjSrcDfn* x6,
                        cprjProject* x7)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[13] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjRuleAttr)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (cprjDstDfn)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (cprjProject)PT_Abs_part(x,3);
  if( (HugeCPtr)x5 != (HugeCPtr)NULL ) *x5 = (GLS_Tok)PT_Abs_part(x,4);
  if( (HugeCPtr)x6 != (HugeCPtr)NULL ) *x6 = (cprjSrcDfn)PT_Abs_part(x,5);
  if( (HugeCPtr)x7 != (HugeCPtr)NULL ) *x7 = (cprjProject)PT_Abs_part(x,6);
  return True;
}

c_bool cprjProject_dobj(cprjProject x, GLS_Tok* x1, cprjProject* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[47]
        || PT_Abs_nonterm(x) == CfgSyms[57]
        || PT_Abs_nonterm(x) == CfgSyms[45]
        || PT_Abs_nonterm(x) == CfgSyms[58]
        || PT_Abs_nonterm(x) == CfgSyms[46], "Project expected" );
  if( PT_Abs_product(x) != PrdSyms[40] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjProject)PT_Abs_part(x,1);
  return True;
}

/*I------------------------------- RuleAttr ------------------------------- */

c_bool cprjRuleAttr_ex2(cprjRuleAttr x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[48], "RuleAttr expected" );
  if( PT_Abs_product(x) != PrdSyms[20] ) return False;
  return True;
}

c_bool cprjRuleAttr_nul(cprjRuleAttr x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[48], "RuleAttr expected" );
  if( PT_Abs_product(x) != PrdSyms[18] ) return False;
  return True;
}

c_bool cprjRuleAttr_exe(cprjRuleAttr x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[48], "RuleAttr expected" );
  if( PT_Abs_product(x) != PrdSyms[19] ) return False;
  return True;
}

/*I------------------------------ OptTPrefix ------------------------------ */

c_bool cprjOptTPrefix_nul(cprjOptTPrefix x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[49], "OptTPrefix expected" );
  if( PT_Abs_product(x) != PrdSyms[21] ) return False;
  return True;
}

c_bool cprjOptTPrefix_pre(cprjOptTPrefix x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[49], "OptTPrefix expected" );
  if( PT_Abs_product(x) != PrdSyms[22] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

/*I------------------------------ OptSPrefix ------------------------------ */

c_bool cprjOptSPrefix_pre(cprjOptSPrefix x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[50], "OptSPrefix expected" );
  if( PT_Abs_product(x) != PrdSyms[24] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool cprjOptSPrefix_nul(cprjOptSPrefix x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[50], "OptSPrefix expected" );
  if( PT_Abs_product(x) != PrdSyms[23] ) return False;
  return True;
}

/*I-------------------------------- DstDfn -------------------------------- */

c_bool cprjDstDfn_int(cprjDstDfn x, GLS_Tok* x1, cprjDstName* x2,
                      cprjOptTPrefix* x3, cprjOptSPrefix* x4)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[51], "DstDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[26] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjDstName)PT_Abs_part(x,1);
  if( (HugeCPtr)x3 != (HugeCPtr)NULL ) *x3 = (cprjOptTPrefix)PT_Abs_part(x,2);
  if( (HugeCPtr)x4 != (HugeCPtr)NULL ) *x4 = (cprjOptSPrefix)PT_Abs_part(x,3);
  return True;
}

c_bool cprjDstDfn_ext(cprjDstDfn x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[51], "DstDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[25] ) return False;
  return True;
}

/*I------------------------------- DstName -------------------------------- */

c_bool cprjDstName_nam(cprjDstName x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "DstName expected" );
  if( PT_Abs_product(x) != PrdSyms[30] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool cprjDstName_root(cprjDstName x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "DstName expected" );
  if( PT_Abs_product(x) != PrdSyms[27] ) return False;
  return True;
}

c_bool cprjDstName_src(cprjDstName x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "DstName expected" );
  if( PT_Abs_product(x) != PrdSyms[28] ) return False;
  return True;
}

c_bool cprjDstName_dir(cprjDstName x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[52], "DstName expected" );
  if( PT_Abs_product(x) != PrdSyms[29] ) return False;
  return True;
}

/*I-------------------------------- RegExp -------------------------------- */

c_bool cprjRegExp_exp(cprjRegExp x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[53], "RegExp expected" );
  if( PT_Abs_product(x) != PrdSyms[32] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}

c_bool cprjRegExp_nul(cprjRegExp x)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[53], "RegExp expected" );
  if( PT_Abs_product(x) != PrdSyms[31] ) return False;
  return True;
}

/*I------------------------------- SrcAttr -------------------------------- */

c_bool cprjSrcAttr_exp(cprjSrcAttr x, cprjRegExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[54], "SrcAttr expected" );
  if( PT_Abs_product(x) != PrdSyms[33] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjRegExp)PT_Abs_part(x,0);
  return True;
}

c_bool cprjSrcAttr_rexp(cprjSrcAttr x, cprjRegExp* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[54], "SrcAttr expected" );
  if( PT_Abs_product(x) != PrdSyms[34] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (cprjRegExp)PT_Abs_part(x,0);
  return True;
}

/*I-------------------------------- SrcDfn -------------------------------- */

c_bool cprjSrcDfn_dfn(cprjSrcDfn x, GLS_Tok* x1, cprjSrcAttr* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[55], "SrcDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[35] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (cprjSrcAttr)PT_Abs_part(x,1);
  return True;
}

/*I-------------------------------- TypDfn -------------------------------- */

c_bool cprjTypDfn_two(cprjTypDfn x, GLS_Tok* x1, GLS_Tok* x2)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[56], "TypDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[37] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  if( (HugeCPtr)x2 != (HugeCPtr)NULL ) *x2 = (GLS_Tok)PT_Abs_part(x,1);
  return True;
}

c_bool cprjTypDfn_one(cprjTypDfn x, GLS_Tok* x1)
{
  assert0(  PT_Abs_nonterm(x) == CfgSyms[56], "TypDfn expected" );
  if( PT_Abs_product(x) != PrdSyms[36] ) return False;
  if( (HugeCPtr)x1 != (HugeCPtr)NULL ) *x1 = (GLS_Tok)PT_Abs_part(x,0);
  return True;
}
