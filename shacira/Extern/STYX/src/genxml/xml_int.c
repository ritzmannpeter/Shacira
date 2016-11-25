/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [xml_int.c]                Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

#include "ptm.h"
#include "gls.h"

/*I--------------------- symbol objects - init & quit --------------------- */

static symbol* CfgSyms = (symbol*)NULL;
static symbol* PrdSyms = (symbol*)NULL;
static int initcount_xml = 0;

void xml_initSymbols()
{
  if( initcount_xml == 0 )
  {
    GLS_init();
    assert0(CfgSyms == (symbol*)NULL,"xmlSymbols already initialized");
    CfgSyms = (symbol*)NewMem(sizeof(symbol)*39);
    PrdSyms = (symbol*)NewMem(sizeof(symbol)*39);

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
    CfgSyms[11] = stringToSymbol("Name");
    CfgSyms[12] = stringToSymbol("dtdEmbed");
    CfgSyms[13] = stringToSymbol("DTDStart");
    CfgSyms[14] = stringToSymbol("Literal");
    CfgSyms[15] = stringToSymbol("CharData");
    CfgSyms[16] = stringToSymbol("Empty");
    CfgSyms[17] = stringToSymbol("Comment");
    CfgSyms[18] = stringToSymbol("<");
    CfgSyms[19] = stringToSymbol("/>");
    CfgSyms[20] = stringToSymbol(">");
    CfgSyms[21] = stringToSymbol("</");
    CfgSyms[22] = stringToSymbol("=");
    CfgSyms[23] = stringToSymbol("_other_");
    CfgSyms[24] = stringToSymbol("XDoc");
    CfgSyms[25] = stringToSymbol("MDecl");
    CfgSyms[26] = stringToSymbol("XDecl");
    CfgSyms[27] = stringToSymbol("TDecl");
    CfgSyms[28] = stringToSymbol("White0");
    CfgSyms[29] = stringToSymbol("White");
    CfgSyms[30] = stringToSymbol("EDecl");
    CfgSyms[31] = stringToSymbol("EBody");
    CfgSyms[32] = stringToSymbol("Attrs");
    CfgSyms[33] = stringToSymbol("Attrs0");
    CfgSyms[34] = stringToSymbol("Attr0");
    CfgSyms[35] = stringToSymbol("Attr");
    CfgSyms[36] = stringToSymbol("Content");
    CfgSyms[37] = stringToSymbol("CDecl");
    CfgSyms[38] = stringToSymbol("xml");

    PrdSyms[0] = stringToSymbol("dfn");
    PrdSyms[1] = stringToSymbol("pi");
    PrdSyms[2] = stringToSymbol("spc");
    PrdSyms[3] = stringToSymbol("xcom");
    PrdSyms[4] = stringToSymbol("nul");
    PrdSyms[5] = stringToSymbol("dfn");
    PrdSyms[6] = stringToSymbol("typ");
    PrdSyms[7] = stringToSymbol("spc");
    PrdSyms[8] = stringToSymbol("nul");
    PrdSyms[9] = stringToSymbol("ign0");
    PrdSyms[10] = stringToSymbol("dfn");
    PrdSyms[11] = stringToSymbol("nul");
    PrdSyms[12] = stringToSymbol("dfn");
    PrdSyms[13] = stringToSymbol("cons");
    PrdSyms[14] = stringToSymbol("ign0");
    PrdSyms[15] = stringToSymbol("nil");
    PrdSyms[16] = stringToSymbol("cons");
    PrdSyms[17] = stringToSymbol("spc");
    PrdSyms[18] = stringToSymbol("dfn");
    PrdSyms[19] = stringToSymbol("nil");
    PrdSyms[20] = stringToSymbol("cons");
    PrdSyms[21] = stringToSymbol("elm");
    PrdSyms[22] = stringToSymbol("lit");
    PrdSyms[23] = stringToSymbol("sect");
    PrdSyms[24] = stringToSymbol("data");
    PrdSyms[25] = stringToSymbol("pref");
    PrdSyms[26] = stringToSymbol("eref");
    PrdSyms[27] = stringToSymbol("cref");
    PrdSyms[28] = stringToSymbol("href");
    PrdSyms[29] = stringToSymbol("name");
    PrdSyms[30] = stringToSymbol("nmtk");
    PrdSyms[31] = stringToSymbol("xopr");
    PrdSyms[32] = stringToSymbol("eq");
    PrdSyms[33] = stringToSymbol("etg0");
    PrdSyms[34] = stringToSymbol("etg1");
    PrdSyms[35] = stringToSymbol("ign0");
    PrdSyms[36] = stringToSymbol("else");
    PrdSyms[37] = stringToSymbol("ign1");
    PrdSyms[38] = stringToSymbol("Start_XDoc");
  }
  ++initcount_xml;
}

void xml_quitSymbols()
{
  --initcount_xml;
  if( initcount_xml == 0 )
  {
    assert0(CfgSyms != (symbol*)NULL,"xmlSymbols not initialized");
    if( CfgSyms != (symbol*)NULL ) FreeMem(CfgSyms);
    CfgSyms = (symbol*)NULL;
    if( PrdSyms != (symbol*)NULL ) FreeMem(PrdSyms);
    PrdSyms = (symbol*)NULL;
  }
}

/*I-------------------------- Types & Constants --------------------------- */

AbstractType( xml );

AbstractType( xmlXDoc );
AbstractType( xmlXDecl );
AbstractType( xmlWhite );
AbstractType( xmlEDecl );
AbstractType( xmlEBody );
AbstractType( xmlAttr );
AbstractType( xmlCDecl );

/*I--------------------------- Access to Tokens --------------------------- */

c_bool Txml_DCharRef(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[0]) );
}

c_bool Txml_HCharRef(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[1]) );
}

c_bool Txml_ERef(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[2]) );
}

c_bool Txml_PERef(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[3]) );
}

c_bool Txml_Nmtoken(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[4]) );
}

c_bool Txml_XMLDecl(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[5]) );
}

c_bool Txml_PI(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[6]) );
}

c_bool Txml_CDSect(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[7]) );
}

c_bool Txml_XMLOpr(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[10]) );
}

c_bool Txml_Name(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[11]) );
}

c_bool Txml_dtdEmbed(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[12]) );
}

c_bool Txml_DTDStart(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[13]) );
}

c_bool Txml_Literal(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[14]) );
}

c_bool Txml_CharData(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[15]) );
}

c_bool Txml_Empty(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[16]) );
}

c_bool Txml_Comment(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[17]) );
}

c_bool Txml__other_(GLS_Tok x)
{
  return( PT_THISTOK((PT_Term)x, CfgSyms[23]) );
}

/*I--------------------------- Access to Terms ---------------------------- */

c_bool xml_xml(PT_Term x, xml* x1)
{
  if( PT_THISNTM(x, CfgSyms[38]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (xml)x;
    return True;
  }
  return False;
}

c_bool xml_XDoc(PT_Term x, xmlXDoc* x1)
{
  if(  PT_THISNTM(x, CfgSyms[24]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (xmlXDoc)x;
    return True;
  }
  return False;
}

c_bool xml_XDecl(PT_Term x, xmlXDecl* x1)
{
  if(  PT_THISNTM(x, CfgSyms[26]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (xmlXDecl)x;
    return True;
  }
  return False;
}

c_bool xml_White(PT_Term x, xmlWhite* x1)
{
  if(  PT_THISNTM(x, CfgSyms[28])
    || PT_THISNTM(x, CfgSyms[29]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (xmlWhite)x;
    return True;
  }
  return False;
}

c_bool xml_EDecl(PT_Term x, xmlEDecl* x1)
{
  if(  PT_THISNTM(x, CfgSyms[30]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (xmlEDecl)x;
    return True;
  }
  return False;
}

c_bool xml_EBody(PT_Term x, xmlEBody* x1)
{
  if(  PT_THISNTM(x, CfgSyms[31]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (xmlEBody)x;
    return True;
  }
  return False;
}

c_bool xml_Attr(PT_Term x, xmlAttr* x1)
{
  if(  PT_THISNTM(x, CfgSyms[35])
    || PT_THISNTM(x, CfgSyms[34]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (xmlAttr)x;
    return True;
  }
  return False;
}

c_bool xml_CDecl(PT_Term x, xmlCDecl* x1)
{
  if(  PT_THISNTM(x, CfgSyms[25])
    || PT_THISNTM(x, CfgSyms[37])
    || PT_THISNTM(x, CfgSyms[27]) )
  {
    if( (StdCPtr)x1 != (StdCPtr)NULL ) *x1 = (xmlCDecl)x;
    return True;
  }
  return False;
}

/*I--------------------------------- xml ---------------------------------- */

c_bool xml_Start_XDoc(xml x, xmlXDoc* x1)
#define xml_Start_0   xml_Start_XDoc
{
  assert0( PT_THISNTM((PT_Term)x, CfgSyms[38]), "xml expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[38]) ) return False;
  if( (StdCPtr)x1 != (StdCPtr)NULL )
    *x1 = (xmlXDoc)GLS_ign_Skip(PT_nthSymbol((PT_Term)x, CfgSyms[24], 1, True));
  return True;
}

/*I--------------------------------- XDoc --------------------------------- */

c_bool xmlXDoc_dfn(xmlXDoc x, xmlXDecl* x1, GLS_Lst(xmlCDecl)* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[24]), "XDoc expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[0]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlXDoc)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlXDecl)GLS_ign_Skip(x);
      x = (xmlXDoc)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(xmlCDecl))GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlXDoc,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlXDecl)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlXDoc,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(xmlCDecl))GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- XDecl --------------------------------- */

c_bool xmlXDecl_nul(xmlXDecl x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[26]), "XDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[4]) ) return False;
  return True;
}

c_bool xmlXDecl_dfn(xmlXDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[26]), "XDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[5]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlXDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlXDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- White --------------------------------- */

c_bool xmlWhite_nul(xmlWhite x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[28])
        || PT_THISNTM((PT_Term)x, CfgSyms[29]), "White expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[8]) ) return False;
  return True;
}

c_bool xmlWhite_spc(xmlWhite x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[28])
        || PT_THISNTM((PT_Term)x, CfgSyms[29]), "White expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[7]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlWhite)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlWhite,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- EDecl --------------------------------- */

c_bool xmlEDecl_dfn(xmlEDecl x, GLS_Tok* x1, GLS_Lst(xmlAttr)* x2,
                    xmlEBody* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[30]), "EDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[10]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlEDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (xmlEDecl)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(xmlAttr))GLS_ign_Skip(x);
      x = (xmlEDecl)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (xmlEBody)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlEDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlEDecl,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Lst(xmlAttr))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlEDecl,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (xmlEBody)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- EBody --------------------------------- */

c_bool xmlEBody_dfn(xmlEBody x, GLS_Lst(xmlCDecl)* x1, GLS_Tok* x2,
                    xmlWhite* x3)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[31]), "EBody expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[12]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlEBody)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(xmlCDecl))GLS_ign_Skip(x);
      x = (xmlEBody)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(x);
      x = (xmlEBody)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (xmlWhite)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlEBody,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Lst(xmlCDecl))GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlEBody,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlEBody,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (xmlWhite)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlEBody_nul(xmlEBody x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[31]), "EBody expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[11]) ) return False;
  return True;
}

/*I--------------------------------- Attr --------------------------------- */

c_bool xmlAttr_spc(xmlAttr x, xmlWhite* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[35])
        || PT_THISNTM((PT_Term)x, CfgSyms[34]), "Attr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[17]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlAttr)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlWhite)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlAttr,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlWhite)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlAttr_dfn(xmlAttr x, xmlWhite* x1, GLS_Tok* x2,
                   xmlWhite* x3, xmlWhite* x4,
                   GLS_Tok* x5)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[35])
        || PT_THISNTM((PT_Term)x, CfgSyms[34]), "Attr expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[18]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlAttr)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlWhite)GLS_ign_Skip(x);
      x = (xmlAttr)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(x);
      x = (xmlAttr)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (xmlWhite)GLS_ign_Skip(x);
      x = (xmlAttr)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (xmlWhite)GLS_ign_Skip(x);
      x = (xmlAttr)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x5 != (StdCPtr)NULL )
        *x5 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlAttr,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlWhite)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlAttr,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlAttr,x);
      if( (StdCPtr)x3 != (StdCPtr)NULL )
        *x3 = (xmlWhite)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlAttr,x);
      if( (StdCPtr)x4 != (StdCPtr)NULL )
        *x4 = (xmlWhite)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlAttr,x);
      if( (StdCPtr)x5 != (StdCPtr)NULL )
        *x5 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

/*I-------------------------------- CDecl --------------------------------- */

c_bool xmlCDecl_eref(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[26]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_data(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[24]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_nmtk(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[30]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_cref(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[27]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_sect(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[23]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_xcom(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[3]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_xopr(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[31]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_pref(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[25]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_name(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[29]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_pi(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[1]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_elm(xmlCDecl x, xmlEDecl* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[21]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlEDecl)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlEDecl)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_etg0(xmlCDecl x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[33]) ) return False;
  return True;
}

c_bool xmlCDecl_lit(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[22]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_else(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[36]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_etg1(xmlCDecl x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[34]) ) return False;
  return True;
}

c_bool xmlCDecl_typ(xmlCDecl x, GLS_Tok* x1, GLS_Tok* x2)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[6]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
      x = (xmlCDecl)GLS_keycom_Skip(PT_next(x));
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
      x = XGLS_keycom_Skip(rst(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x2 != (StdCPtr)NULL )
        *x2 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_spc(xmlCDecl x, xmlWhite* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[2]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlWhite)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (xmlWhite)GLS_ign_Skip(y);
    }
  }
  return True;
}

c_bool xmlCDecl_eq(xmlCDecl x)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[32]) ) return False;
  return True;
}

c_bool xmlCDecl_href(xmlCDecl x, GLS_Tok* x1)
{
  assert0(  PT_THISNTM((PT_Term)x, CfgSyms[25])
        || PT_THISNTM((PT_Term)x, CfgSyms[37])
        || PT_THISNTM((PT_Term)x, CfgSyms[27]), "CDecl expected" );
  if( ! PT_THISPRD((PT_Term)x, PrdSyms[28]) ) return False;
  { PT_Term y;
    if( ! PT_isXaron(x) )
    {
      x = (xmlCDecl)GLS_keycom_Skip(PT_parts(x));
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(x);
    }
    else
    {
      x = XGLS_keycom_Skip(XPT_parts(x)); y = fst(xmlCDecl,x);
      if( (StdCPtr)x1 != (StdCPtr)NULL )
        *x1 = (GLS_Tok)GLS_ign_Skip(y);
    }
  }
  return True;
}
