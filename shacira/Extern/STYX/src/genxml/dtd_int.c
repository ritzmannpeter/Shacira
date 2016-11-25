/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [dtd_int.c]                Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;
static int initcount_dtd = 0;

void dtd_initSymbols()
{
  if( initcount_dtd == 0 )
  {
    GLS_init();
    assert0(CfgSyms == (symbol*)NULL,"dtdSymbols already initialized");
    CfgSyms = (symbol*)NewMem(sizeof(symbol)*100);
    PrdSyms = (symbol*)NewMem(sizeof(symbol)*112);

    CfgSyms[0] = stringToSymbol("DCharRef");
    CfgSyms[1] = stringToSymbol("HCharRef");
    CfgSyms[2] = stringToSymbol("ERef");
    CfgSyms[3] = stringToSymbol("PERef");
    CfgSyms[4] = stringToSymbol("Nmtoken");
    CfgSyms[5] = stringToSymbol("XMLDecl");
    CfgSyms[6] = stringToSymbol("PI");
    CfgSyms[7] = stringToSymbol("CDSect");
    CfgSyms[8] = stringToSymbol("ElmStart");
    CfgSyms[9] = stringToSymbol("TagEnd");
    CfgSyms[10] = stringToSymbol("XMLOpr");
    CfgSyms[11] = stringToSymbol("Keyset");
    CfgSyms[12] = stringToSymbol("Name");
    CfgSyms[13] = stringToSymbol("Literal");
    CfgSyms[14] = stringToSymbol("DTDStart");
    CfgSyms[15] = stringToSymbol("IgnSect");
    CfgSyms[16] = stringToSymbol("Comment");
    CfgSyms[17] = stringToSymbol(">");
    CfgSyms[18] = stringToSymbol("system");
    CfgSyms[19] = stringToSymbol("public");
    CfgSyms[20] = stringToSymbol("[");
    CfgSyms[21] = stringToSymbol("]");
    CfgSyms[22] = stringToSymbol("<!");
    CfgSyms[23] = stringToSymbol("element");
    CfgSyms[24] = stringToSymbol("entity");
    CfgSyms[25] = stringToSymbol("attlist");
    CfgSyms[26] = stringToSymbol("notation");
    CfgSyms[27] = stringToSymbol("<![");
    CfgSyms[28] = stringToSymbol("include");
    CfgSyms[29] = stringToSymbol("]]>");
    CfgSyms[30] = stringToSymbol("cdata");
    CfgSyms[31] = stringToSymbol("id");
    CfgSyms[32] = stringToSymbol("idref");
    CfgSyms[33] = stringToSymbol("idrefs");
    CfgSyms[34] = stringToSymbol("entities");
    CfgSyms[35] = stringToSymbol("nmtoken");
    CfgSyms[36] = stringToSymbol("nmtokens");
    CfgSyms[37] = stringToSymbol("(");
    CfgSyms[38] = stringToSymbol(")");
    CfgSyms[39] = stringToSymbol("#");
    CfgSyms[40] = stringToSymbol("required");
    CfgSyms[41] = stringToSymbol("implied");
    CfgSyms[42] = stringToSymbol("fixed");
    CfgSyms[43] = stringToSymbol("%");
    CfgSyms[44] = stringToSymbol("empty");
    CfgSyms[45] = stringToSymbol("any");
    CfgSyms[46] = stringToSymbol(")*");
    CfgSyms[47] = stringToSymbol("|");
    CfgSyms[48] = stringToSymbol("pcdata");
    CfgSyms[49] = stringToSymbol(",");
    CfgSyms[50] = stringToSymbol("?");
    CfgSyms[51] = stringToSymbol("*");
    CfgSyms[52] = stringToSymbol("+");
    CfgSyms[53] = stringToSymbol("ndata");
    CfgSyms[54] = stringToSymbol("Root");
    CfgSyms[55] = stringToSymbol("Embed");
    CfgSyms[56] = stringToSymbol("Extern");
    CfgSyms[57] = stringToSymbol("XDecl");
    CfgSyms[58] = stringToSymbol("ExtID0");
    CfgSyms[59] = stringToSymbol("ExtID3");
    CfgSyms[60] = stringToSymbol("ExtID1");
    CfgSyms[61] = stringToSymbol("ExtID");
    CfgSyms[62] = stringToSymbol("ExtID2");
    CfgSyms[63] = stringToSymbol("XLiteral0");
    CfgSyms[64] = stringToSymbol("XLiteral");
    CfgSyms[65] = stringToSymbol("Decls");
    CfgSyms[66] = stringToSymbol("Decls0");
    CfgSyms[67] = stringToSymbol("Decls1");
    CfgSyms[68] = stringToSymbol("Decl");
    CfgSyms[69] = stringToSymbol("Decl1");
    CfgSyms[70] = stringToSymbol("Cond");
    CfgSyms[71] = stringToSymbol("Attributes");
    CfgSyms[72] = stringToSymbol("Attribute");
    CfgSyms[73] = stringToSymbol("AType0");
    CfgSyms[74] = stringToSymbol("AType");
    CfgSyms[75] = stringToSymbol("ADefault");
    CfgSyms[76] = stringToSymbol("Fixed");
    CfgSyms[77] = stringToSymbol("Entity");
    CfgSyms[78] = stringToSymbol("EntityVal");
    CfgSyms[79] = stringToSymbol("NData");
    CfgSyms[80] = stringToSymbol("Content");
    CfgSyms[81] = stringToSymbol("Mixed");
    CfgSyms[82] = stringToSymbol("XNames0");
    CfgSyms[83] = stringToSymbol("XNames2");
    CfgSyms[84] = stringToSymbol("XNames1");
    CfgSyms[85] = stringToSymbol("XNames");
    CfgSyms[86] = stringToSymbol("XName0");
    CfgSyms[87] = stringToSymbol("RExp");
    CfgSyms[88] = stringToSymbol("RExp0");
    CfgSyms[89] = stringToSymbol("RExp1");
    CfgSyms[90] = stringToSymbol("ROpr1");
    CfgSyms[91] = stringToSymbol("ROpr0");
    CfgSyms[92] = stringToSymbol("ROpr");
    CfgSyms[93] = stringToSymbol("XName2");
    CfgSyms[94] = stringToSymbol("XName");
    CfgSyms[95] = stringToSymbol("XName1");
    CfgSyms[96] = stringToSymbol("XName3");
    CfgSyms[97] = stringToSymbol("XName4");
    CfgSyms[98] = stringToSymbol("dtd");
    CfgSyms[99] = stringToSymbol("dtd");

    PrdSyms[0] = stringToSymbol("tdoc");
    PrdSyms[1] = stringToSymbol("text");
    PrdSyms[2] = stringToSymbol("dfn");
    PrdSyms[3] = stringToSymbol("dfn");
    PrdSyms[4] = stringToSymbol("nul");
    PrdSyms[5] = stringToSymbol("dfn");
    PrdSyms[6] = stringToSymbol("nul");
    PrdSyms[7] = stringToSymbol("ign0");
    PrdSyms[8] = stringToSymbol("pref");
    PrdSyms[9] = stringToSymbol("sys");
    PrdSyms[10] = stringToSymbol("pub");
    PrdSyms[11] = stringToSymbol("ign0");
    PrdSyms[12] = stringToSymbol("ign1");
    PrdSyms[13] = stringToSymbol("pub");
    PrdSyms[14] = stringToSymbol("ign0");
    PrdSyms[15] = stringToSymbol("nul");
    PrdSyms[16] = stringToSymbol("ign0");
    PrdSyms[17] = stringToSymbol("pref");
    PrdSyms[18] = stringToSymbol("lit");
    PrdSyms[19] = stringToSymbol("nil");
    PrdSyms[20] = stringToSymbol("ign0");
    PrdSyms[21] = stringToSymbol("nil");
    PrdSyms[22] = stringToSymbol("cons");
    PrdSyms[23] = stringToSymbol("nil");
    PrdSyms[24] = stringToSymbol("cons");
    PrdSyms[25] = stringToSymbol("pref");
    PrdSyms[26] = stringToSymbol("pi");
    PrdSyms[27] = stringToSymbol("elm");
    PrdSyms[28] = stringToSymbol("ent");
    PrdSyms[29] = stringToSymbol("attr");
    PrdSyms[30] = stringToSymbol("note");
    PrdSyms[31] = stringToSymbol("cond");
    PrdSyms[32] = stringToSymbol("ign0");
    PrdSyms[33] = stringToSymbol("cign");
    PrdSyms[34] = stringToSymbol("cinc");
    PrdSyms[35] = stringToSymbol("ccnd");
    PrdSyms[36] = stringToSymbol("nil");
    PrdSyms[37] = stringToSymbol("cons");
    PrdSyms[38] = stringToSymbol("nam");
    PrdSyms[39] = stringToSymbol("typ");
    PrdSyms[40] = stringToSymbol("dft");
    PrdSyms[41] = stringToSymbol("str");
    PrdSyms[42] = stringToSymbol("id");
    PrdSyms[43] = stringToSymbol("ref");
    PrdSyms[44] = stringToSymbol("refs");
    PrdSyms[45] = stringToSymbol("ent");
    PrdSyms[46] = stringToSymbol("ents");
    PrdSyms[47] = stringToSymbol("nmt");
    PrdSyms[48] = stringToSymbol("nmts");
    PrdSyms[49] = stringToSymbol("ntyp");
    PrdSyms[50] = stringToSymbol("etyp");
    PrdSyms[51] = stringToSymbol("ign0");
    PrdSyms[52] = stringToSymbol("req");
    PrdSyms[53] = stringToSymbol("imp");
    PrdSyms[54] = stringToSymbol("fix");
    PrdSyms[55] = stringToSymbol("nul");
    PrdSyms[56] = stringToSymbol("fix");
    PrdSyms[57] = stringToSymbol("pent");
    PrdSyms[58] = stringToSymbol("gent");
    PrdSyms[59] = stringToSymbol("ient");
    PrdSyms[60] = stringToSymbol("eent");
    PrdSyms[61] = stringToSymbol("nul");
    PrdSyms[62] = stringToSymbol("dfn");
    PrdSyms[63] = stringToSymbol("pref");
    PrdSyms[64] = stringToSymbol("none");
    PrdSyms[65] = stringToSymbol("any");
    PrdSyms[66] = stringToSymbol("mix");
    PrdSyms[67] = stringToSymbol("ign0");
    PrdSyms[68] = stringToSymbol("ign0");
    PrdSyms[69] = stringToSymbol("cons");
    PrdSyms[70] = stringToSymbol("nil");
    PrdSyms[71] = stringToSymbol("cons");
    PrdSyms[72] = stringToSymbol("cons");
    PrdSyms[73] = stringToSymbol("nil");
    PrdSyms[74] = stringToSymbol("cons");
    PrdSyms[75] = stringToSymbol("pdat");
    PrdSyms[76] = stringToSymbol("rexp");
    PrdSyms[77] = stringToSymbol("alt");
    PrdSyms[78] = stringToSymbol("seq");
    PrdSyms[79] = stringToSymbol("ign0");
    PrdSyms[80] = stringToSymbol("nam");
    PrdSyms[81] = stringToSymbol("ign0");
    PrdSyms[82] = stringToSymbol("star");
    PrdSyms[83] = stringToSymbol("ign0");
    PrdSyms[84] = stringToSymbol("nul");
    PrdSyms[85] = stringToSymbol("ign0");
    PrdSyms[86] = stringToSymbol("qry");
    PrdSyms[87] = stringToSymbol("star");
    PrdSyms[88] = stringToSymbol("plus");
    PrdSyms[89] = stringToSymbol("alst");
    PrdSyms[90] = stringToSymbol("elm");
    PrdSyms[91] = stringToSymbol("inc");
    PrdSyms[92] = stringToSymbol("req");
    PrdSyms[93] = stringToSymbol("fix");
    PrdSyms[94] = stringToSymbol("impl");
    PrdSyms[95] = stringToSymbol("pub");
    PrdSyms[96] = stringToSymbol("sys");
    PrdSyms[97] = stringToSymbol("none");
    PrdSyms[98] = stringToSymbol("any");
    PrdSyms[99] = stringToSymbol("pdat");
    PrdSyms[100] = stringToSymbol("ktyp");
    PrdSyms[101] = stringToSymbol("ign0");
    PrdSyms[102] = stringToSymbol("ide");
    PrdSyms[103] = stringToSymbol("nmtk");
    PrdSyms[104] = stringToSymbol("key");
    PrdSyms[105] = stringToSymbol("ign0");
    PrdSyms[106] = stringToSymbol("ign1");
    PrdSyms[107] = stringToSymbol("pref");
    PrdSyms[108] = stringToSymbol("ign0");
    PrdSyms[109] = stringToSymbol("ndat");
    PrdSyms[110] = stringToSymbol("Start_Root");
    PrdSyms[111] = stringToSymbol("Start_Embed");
  }
  ++initcount_dtd;
}

void dtd_quitSymbols()
{
  --initcount_dtd;
  if( initcount_dtd == 0 )
  {
    assert0(CfgSyms != (symbol*)NULL,"dtdSymbols not initialized");
    if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
    CfgSyms = (symbol*)NULL;
    if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
    PrdSyms = (symbol*)NULL;
  }
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractType( dtd );

AbstractType( dtdRoot );
AbstractType( dtdEmbed );
AbstractType( dtdExtern );
AbstractType( dtdXDecl );
AbstractType( dtdExtID );
AbstractType( dtdXLiteral );
AbstractType( dtdDecl );
AbstractType( dtdCond );
AbstractType( dtdAttribute );
AbstractType( dtdAType );
AbstractType( dtdADefault );
AbstractType( dtdFixed );
AbstractType( dtdEntity );
AbstractType( dtdEntityVal );
AbstractType( dtdNData );
AbstractType( dtdContent );
AbstractType( dtdROpr );
AbstractType( dtdXName );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Tdtd_PERef(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[3]) );
}

c_bool Tdtd_Nmtoken(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[4]) );
}

c_bool Tdtd_XMLDecl(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[5]) );
}

c_bool Tdtd_PI(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[6]) );
}

c_bool Tdtd_Keyset(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[11]) );
}

c_bool Tdtd_Name(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[12]) );
}

c_bool Tdtd_Literal(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[13]) );
}

c_bool Tdtd_DTDStart(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[14]) );
}

c_bool Tdtd_IgnSect(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[15]) );
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool dtd_dtd(PT_Term x, dtd* x1)
{
  if( PT_THISNTM(x, CfgSyms[98]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtd)x;
    return True;
  }
  return False;
}

c_bool dtd_Root(PT_Term x, dtdRoot* x1)
{
  if(  PT_THISNTM(x, CfgSyms[54]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdRoot)x;
    return True;
  }
  return False;
}

c_bool dtd_Embed(PT_Term x, dtdEmbed* x1)
{
  if(  PT_THISNTM(x, CfgSyms[55]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdEmbed)x;
    return True;
  }
  return False;
}

c_bool dtd_Extern(PT_Term x, dtdExtern* x1)
{
  if(  PT_THISNTM(x, CfgSyms[56]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdExtern)x;
    return True;
  }
  return False;
}

c_bool dtd_XDecl(PT_Term x, dtdXDecl* x1)
{
  if(  PT_THISNTM(x, CfgSyms[57]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdXDecl)x;
    return True;
  }
  return False;
}

c_bool dtd_ExtID(PT_Term x, dtdExtID* x1)
{
  if(  PT_THISNTM(x, CfgSyms[60])
    || PT_THISNTM(x, CfgSyms[61])
    || PT_THISNTM(x, CfgSyms[58])
    || PT_THISNTM(x, CfgSyms[62])
    || PT_THISNTM(x, CfgSyms[59]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdExtID)x;
    return True;
  }
  return False;
}

c_bool dtd_XLiteral(PT_Term x, dtdXLiteral* x1)
{
  if(  PT_THISNTM(x, CfgSyms[64])
    || PT_THISNTM(x, CfgSyms[63]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdXLiteral)x;
    return True;
  }
  return False;
}

c_bool dtd_Decl(PT_Term x, dtdDecl* x1)
{
  if(  PT_THISNTM(x, CfgSyms[68])
    || PT_THISNTM(x, CfgSyms[69]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdDecl)x;
    return True;
  }
  return False;
}

c_bool dtd_Cond(PT_Term x, dtdCond* x1)
{
  if(  PT_THISNTM(x, CfgSyms[70]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdCond)x;
    return True;
  }
  return False;
}

c_bool dtd_Attribute(PT_Term x, dtdAttribute* x1)
{
  if(  PT_THISNTM(x, CfgSyms[72]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdAttribute)x;
    return True;
  }
  return False;
}

c_bool dtd_AType(PT_Term x, dtdAType* x1)
{
  if(  PT_THISNTM(x, CfgSyms[74])
    || PT_THISNTM(x, CfgSyms[73]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdAType)x;
    return True;
  }
  return False;
}

c_bool dtd_ADefault(PT_Term x, dtdADefault* x1)
{
  if(  PT_THISNTM(x, CfgSyms[75]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdADefault)x;
    return True;
  }
  return False;
}

c_bool dtd_Fixed(PT_Term x, dtdFixed* x1)
{
  if(  PT_THISNTM(x, CfgSyms[76]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdFixed)x;
    return True;
  }
  return False;
}

c_bool dtd_Entity(PT_Term x, dtdEntity* x1)
{
  if(  PT_THISNTM(x, CfgSyms[77]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdEntity)x;
    return True;
  }
  return False;
}

c_bool dtd_EntityVal(PT_Term x, dtdEntityVal* x1)
{
  if(  PT_THISNTM(x, CfgSyms[78]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdEntityVal)x;
    return True;
  }
  return False;
}

c_bool dtd_NData(PT_Term x, dtdNData* x1)
{
  if(  PT_THISNTM(x, CfgSyms[79]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdNData)x;
    return True;
  }
  return False;
}

c_bool dtd_Content(PT_Term x, dtdContent* x1)
{
  if(  PT_THISNTM(x, CfgSyms[88])
    || PT_THISNTM(x, CfgSyms[89])
    || PT_THISNTM(x, CfgSyms[80])
    || PT_THISNTM(x, CfgSyms[87]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdContent)x;
    return True;
  }
  return False;
}

c_bool dtd_ROpr(PT_Term x, dtdROpr* x1)
{
  if(  PT_THISNTM(x, CfgSyms[91])
    || PT_THISNTM(x, CfgSyms[92])
    || PT_THISNTM(x, CfgSyms[90]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdROpr)x;
    return True;
  }
  return False;
}

c_bool dtd_XName(PT_Term x, dtdXName* x1)
{
  if(  PT_THISNTM(x, CfgSyms[86])
    || PT_THISNTM(x, CfgSyms[95])
    || PT_THISNTM(x, CfgSyms[93])
    || PT_THISNTM(x, CfgSyms[96])
    || PT_THISNTM(x, CfgSyms[97])
    || PT_THISNTM(x, CfgSyms[94]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (dtdXName)x;
    return True;
  }
  return False;
}

/*I--------------------------------- dtd ---------------------------------- */

c_bool dtd_Start_Root(dtd x, dtdRoot* x1)
#define dtd_Start_0   dtd_Start_Root
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[98]), "dtd expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[110]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (dtdRoot)GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[54], 1, True));
  return True;
}

c_bool dtd_Start_Embed(dtd x, dtdEmbed* x1)
#define dtd_Start_1   dtd_Start_Embed
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[99]), "dtd expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[111]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (dtdEmbed)GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[55], 1, True));
  return True;
}

/*I--------------------------------- Root --------------------------------- */

c_bool dtdRoot_text(dtdRoot x, dtdExtern* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[54]), "Root expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[1]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdRoot)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdExtern)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdRoot,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdExtern)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdRoot_tdoc(dtdRoot x, GLS_Tok* x1, dtdEmbed* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[54]), "Root expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[0]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdRoot)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (dtdRoot)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdEmbed)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdRoot,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdRoot,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdEmbed)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- Embed --------------------------------- */

c_bool dtdEmbed_dfn(dtdEmbed x, dtdXName* x1, dtdExtID* x2,
                    GLS_Lst(dtdDecl)* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[55]), "Embed expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[2]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdEmbed)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
      x = (dtdEmbed)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdExtID)GLS_ign_Skip(x);
      x = (dtdEmbed)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(dtdDecl))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdEmbed,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdEmbed,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdExtID)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdEmbed,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (GLS_Lst(dtdDecl))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- Extern -------------------------------- */

c_bool dtdExtern_dfn(dtdExtern x, dtdXDecl* x1, GLS_Lst(dtdDecl)* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[56]), "Extern expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[3]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdExtern)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXDecl)GLS_ign_Skip(x);
      x = (dtdExtern)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(dtdDecl))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdExtern,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXDecl)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdExtern,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(dtdDecl))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- XDecl --------------------------------- */

c_bool dtdXDecl_nul(dtdXDecl x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[57]), "XDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[4]) ) return False;
  return True;
}

c_bool dtdXDecl_dfn(dtdXDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[57]), "XDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[5]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdXDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdXDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- ExtID --------------------------------- */

c_bool dtdExtID_pref(dtdExtID x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[59]), "ExtID expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[8]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdExtID)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdExtID,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdExtID_nul(dtdExtID x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[59]), "ExtID expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[6]) ) return False;
  return True;
}

c_bool dtdExtID_pub(dtdExtID x, dtdXLiteral* x1, dtdXLiteral* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[59]), "ExtID expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[10]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdExtID)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXLiteral)GLS_ign_Skip(x);
      x = (dtdExtID)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdXLiteral)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdExtID,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXLiteral)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdExtID,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdXLiteral)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdExtID_sys(dtdExtID x, dtdXLiteral* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[60])
        || PT_THISNTM((PT_Term)x, CfgSyms[61])
        || PT_THISNTM((PT_Term)x, CfgSyms[58])
        || PT_THISNTM((PT_Term)x, CfgSyms[62])
        || PT_THISNTM((PT_Term)x, CfgSyms[59]), "ExtID expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[9]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdExtID)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXLiteral)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdExtID,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXLiteral)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I------------------------------- XLiteral ------------------------------- */

c_bool dtdXLiteral_pref(dtdXLiteral x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[64])
        || PT_THISNTM((PT_Term)x, CfgSyms[63]), "XLiteral expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[17]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdXLiteral)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdXLiteral,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdXLiteral_lit(dtdXLiteral x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[64])
        || PT_THISNTM((PT_Term)x, CfgSyms[63]), "XLiteral expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[18]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdXLiteral)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdXLiteral,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdXLiteral_nul(dtdXLiteral x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[64])
        || PT_THISNTM((PT_Term)x, CfgSyms[63]), "XLiteral expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[15]) ) return False;
  return True;
}

/*I--------------------------------- Decl --------------------------------- */

c_bool dtdDecl_pref(dtdDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[68])
        || PT_THISNTM((PT_Term)x, CfgSyms[69]), "Decl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[25]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdDecl_attr(dtdDecl x, dtdXName* x1, GLS_Lst(dtdAttribute)* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[68])
        || PT_THISNTM((PT_Term)x, CfgSyms[69]), "Decl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[29]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
      x = (dtdDecl)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(dtdAttribute))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(dtdAttribute))GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdDecl_ent(dtdDecl x, dtdEntity* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[68])
        || PT_THISNTM((PT_Term)x, CfgSyms[69]), "Decl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[28]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdEntity)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdEntity)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdDecl_pi(dtdDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[68])
        || PT_THISNTM((PT_Term)x, CfgSyms[69]), "Decl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[26]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdDecl_note(dtdDecl x, dtdXName* x1, dtdExtID* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[68])
        || PT_THISNTM((PT_Term)x, CfgSyms[69]), "Decl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[30]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
      x = (dtdDecl)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdExtID)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdExtID)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdDecl_elm(dtdDecl x, dtdXName* x1, dtdContent* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[68])
        || PT_THISNTM((PT_Term)x, CfgSyms[69]), "Decl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[27]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
      x = (dtdDecl)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdContent)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdContent)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdDecl_cond(dtdDecl x, dtdCond* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[68])
        || PT_THISNTM((PT_Term)x, CfgSyms[69]), "Decl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[31]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdCond)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdCond)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- Cond --------------------------------- */

c_bool dtdCond_cinc(dtdCond x, dtdExtern* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[70]), "Cond expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[34]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdCond)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdExtern)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdCond,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdExtern)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdCond_cign(dtdCond x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[70]), "Cond expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[33]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdCond)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdCond,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdCond_ccnd(dtdCond x, GLS_Tok* x1, dtdExtern* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[70]), "Cond expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[35]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdCond)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (dtdCond)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdExtern)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdCond,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdCond,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdExtern)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I------------------------------ Attribute ------------------------------- */

c_bool dtdAttribute_nam(dtdAttribute x, dtdXName* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[72]), "Attribute expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[38]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdAttribute)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdAttribute,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdAttribute_dft(dtdAttribute x, dtdADefault* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[72]), "Attribute expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[40]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdAttribute)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdADefault)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdAttribute,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdADefault)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdAttribute_typ(dtdAttribute x, dtdAType* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[72]), "Attribute expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[39]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdAttribute)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdAType)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdAttribute,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdAType)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- AType --------------------------------- */

c_bool dtdAType_refs(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[44]) ) return False;
  return True;
}

c_bool dtdAType_nmts(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[48]) ) return False;
  return True;
}

c_bool dtdAType_str(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[41]) ) return False;
  return True;
}

c_bool dtdAType_ents(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[46]) ) return False;
  return True;
}

c_bool dtdAType_etyp(dtdAType x, GLS_Lst(dtdXName)* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[50]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdAType)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(dtdXName))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdAType,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(dtdXName))GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdAType_ref(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[43]) ) return False;
  return True;
}

c_bool dtdAType_nmt(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[47]) ) return False;
  return True;
}

c_bool dtdAType_ntyp(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[49]) ) return False;
  return True;
}

c_bool dtdAType_id(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[42]) ) return False;
  return True;
}

c_bool dtdAType_ent(dtdAType x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[74])
        || PT_THISNTM((PT_Term)x, CfgSyms[73]), "AType expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[45]) ) return False;
  return True;
}

/*I------------------------------- ADefault ------------------------------- */

c_bool dtdADefault_fix(dtdADefault x, dtdFixed* x1, GLS_Tok* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[75]), "ADefault expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[54]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdADefault)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdFixed)GLS_ign_Skip(x);
      x = (dtdADefault)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdADefault,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdFixed)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdADefault,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdADefault_imp(dtdADefault x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[75]), "ADefault expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[53]) ) return False;
  return True;
}

c_bool dtdADefault_req(dtdADefault x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[75]), "ADefault expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[52]) ) return False;
  return True;
}

/*I-------------------------------- Fixed --------------------------------- */

c_bool dtdFixed_nul(dtdFixed x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[76]), "Fixed expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[55]) ) return False;
  return True;
}

c_bool dtdFixed_fix(dtdFixed x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[76]), "Fixed expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[56]) ) return False;
  return True;
}

/*I-------------------------------- Entity -------------------------------- */

c_bool dtdEntity_pent(dtdEntity x, dtdXName* x1, dtdEntityVal* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[77]), "Entity expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[57]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdEntity)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
      x = (dtdEntity)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdEntityVal)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdEntity,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdEntity,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdEntityVal)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdEntity_gent(dtdEntity x, dtdXName* x1, dtdEntityVal* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[77]), "Entity expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[58]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdEntity)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
      x = (dtdEntity)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdEntityVal)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdEntity,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdEntity,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdEntityVal)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I------------------------------ EntityVal ------------------------------- */

c_bool dtdEntityVal_ient(dtdEntityVal x, dtdXLiteral* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[78]), "EntityVal expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[59]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdEntityVal)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXLiteral)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdEntityVal,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXLiteral)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdEntityVal_eent(dtdEntityVal x, dtdExtID* x1, dtdNData* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[78]), "EntityVal expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[60]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdEntityVal)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdExtID)GLS_ign_Skip(x);
      x = (dtdEntityVal)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdNData)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdEntityVal,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdExtID)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdEntityVal,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdNData)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- NData --------------------------------- */

c_bool dtdNData_nul(dtdNData x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[79]), "NData expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[61]) ) return False;
  return True;
}

c_bool dtdNData_dfn(dtdNData x, dtdXName* x1, dtdXName* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[79]), "NData expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[62]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdNData)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
      x = (dtdNData)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdXName)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdNData,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdNData,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdXName)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I------------------------------- Content -------------------------------- */

c_bool dtdContent_alt(dtdContent x, dtdContent* x1, dtdContent* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[88])
        || PT_THISNTM((PT_Term)x, CfgSyms[89])
        || PT_THISNTM((PT_Term)x, CfgSyms[80])
        || PT_THISNTM((PT_Term)x, CfgSyms[87]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[77]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdContent)GLS_ign_Skip(x);
      x = (dtdContent)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdContent)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdContent)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdContent)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdContent_none(dtdContent x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[88])
        || PT_THISNTM((PT_Term)x, CfgSyms[89])
        || PT_THISNTM((PT_Term)x, CfgSyms[80])
        || PT_THISNTM((PT_Term)x, CfgSyms[87]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[64]) ) return False;
  return True;
}

c_bool dtdContent_mix(dtdContent x, GLS_Lst(dtdXName)* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[88])
        || PT_THISNTM((PT_Term)x, CfgSyms[89])
        || PT_THISNTM((PT_Term)x, CfgSyms[80])
        || PT_THISNTM((PT_Term)x, CfgSyms[87]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[66]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(dtdXName))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(dtdXName))GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdContent_any(dtdContent x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[88])
        || PT_THISNTM((PT_Term)x, CfgSyms[89])
        || PT_THISNTM((PT_Term)x, CfgSyms[80])
        || PT_THISNTM((PT_Term)x, CfgSyms[87]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[65]) ) return False;
  return True;
}

c_bool dtdContent_seq(dtdContent x, dtdContent* x1, dtdContent* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[88])
        || PT_THISNTM((PT_Term)x, CfgSyms[89])
        || PT_THISNTM((PT_Term)x, CfgSyms[80])
        || PT_THISNTM((PT_Term)x, CfgSyms[87]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[78]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdContent)GLS_ign_Skip(x);
      x = (dtdContent)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdContent)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdContent)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdContent)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdContent_nam(dtdContent x, dtdXName* x1, dtdROpr* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[88])
        || PT_THISNTM((PT_Term)x, CfgSyms[89])
        || PT_THISNTM((PT_Term)x, CfgSyms[80])
        || PT_THISNTM((PT_Term)x, CfgSyms[87]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[80]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(x);
      x = (dtdContent)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdROpr)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdXName)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdROpr)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdContent_rexp(dtdContent x, dtdContent* x1, dtdROpr* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[88])
        || PT_THISNTM((PT_Term)x, CfgSyms[89])
        || PT_THISNTM((PT_Term)x, CfgSyms[80])
        || PT_THISNTM((PT_Term)x, CfgSyms[87]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[76]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdContent)GLS_ign_Skip(x);
      x = (dtdContent)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdROpr)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdContent)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (dtdROpr)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdContent_pref(dtdContent x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[88])
        || PT_THISNTM((PT_Term)x, CfgSyms[89])
        || PT_THISNTM((PT_Term)x, CfgSyms[80])
        || PT_THISNTM((PT_Term)x, CfgSyms[87]), "Content expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[63]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdContent)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdContent,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I--------------------------------- ROpr --------------------------------- */

c_bool dtdROpr_nul(dtdROpr x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[91])
        || PT_THISNTM((PT_Term)x, CfgSyms[92])
        || PT_THISNTM((PT_Term)x, CfgSyms[90]), "ROpr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[84]) ) return False;
  return True;
}

c_bool dtdROpr_plus(dtdROpr x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[91])
        || PT_THISNTM((PT_Term)x, CfgSyms[92])
        || PT_THISNTM((PT_Term)x, CfgSyms[90]), "ROpr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[88]) ) return False;
  return True;
}

c_bool dtdROpr_star(dtdROpr x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[91])
        || PT_THISNTM((PT_Term)x, CfgSyms[92])
        || PT_THISNTM((PT_Term)x, CfgSyms[90]), "ROpr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[82]) ) return False;
  return True;
}

c_bool dtdROpr_qry(dtdROpr x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[91])
        || PT_THISNTM((PT_Term)x, CfgSyms[92])
        || PT_THISNTM((PT_Term)x, CfgSyms[90]), "ROpr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[86]) ) return False;
  return True;
}

/*I-------------------------------- XName --------------------------------- */

c_bool dtdXName_elm(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[90]) ) return False;
  return True;
}

c_bool dtdXName_req(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[92]) ) return False;
  return True;
}

c_bool dtdXName_key(dtdXName x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[104]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdXName)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdXName,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdXName_alst(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[89]) ) return False;
  return True;
}

c_bool dtdXName_pref(dtdXName x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[107]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdXName)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdXName,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdXName_fix(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[93]) ) return False;
  return True;
}

c_bool dtdXName_inc(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[91]) ) return False;
  return True;
}

c_bool dtdXName_ndat(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[109]) ) return False;
  return True;
}

c_bool dtdXName_pub(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[95]) ) return False;
  return True;
}

c_bool dtdXName_nmtk(dtdXName x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[103]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdXName)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdXName,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdXName_none(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[97]) ) return False;
  return True;
}

c_bool dtdXName_pdat(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[75]) ) return False;
  return True;
}

c_bool dtdXName_ide(dtdXName x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[102]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdXName)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdXName,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdXName_any(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[98]) ) return False;
  return True;
}

c_bool dtdXName_impl(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[94]) ) return False;
  return True;
}

c_bool dtdXName_ktyp(dtdXName x, dtdAType* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[100]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (dtdXName)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdAType)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(dtdXName,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (dtdAType)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool dtdXName_sys(dtdXName x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[86])
        || PT_THISNTM((PT_Term)x, CfgSyms[95])
        || PT_THISNTM((PT_Term)x, CfgSyms[93])
        || PT_THISNTM((PT_Term)x, CfgSyms[96])
        || PT_THISNTM((PT_Term)x, CfgSyms[97])
        || PT_THISNTM((PT_Term)x, CfgSyms[94]), "XName expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[96]) ) return False;
  return True;
}
