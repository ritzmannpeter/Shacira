/* [xml_pim.c] Parser table for 'xml'  */



#include "prs.h"

#include "prs_imp.h"


static string xml_SNames[] = {
  "DCharRef", "HCharRef", "ERef", "PERef", "Nmtoken", 
  "XMLDecl", "PI", "CDSect", "ElmStart", "TagEnd", 
  "XMLOpr", "Name", "dtdEmbed", "DTDStart", "Literal", 
  "CharData", "Empty", "Comment", "<", "/>", 
  ">", "</", "=", "_other_", "XDoc", 
  "MDecl", "XDecl", "TDecl", "White0", "White", 
  "EDecl", "EBody", "Attrs", "Attrs0", "Attr0", 
  "Attr", "Content", "CDecl"
};

static int xml_StartIds[] = {
  24
};

static int xml_TokKind[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 4, 1, 1, 1, 
  1, 1, 2, 2, 2, 2, 2, 1
};

static int xml_NtClass[] = {
  0, 13, 2, 13, 5, 5, 6, 7, 
  8, 8, 11, 11, 12, 13
};

static c_bool xml_ErrorNt[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0
};

static KFGHEAD xml_KfgHead = {
  "xml",
  24, 14, xml_SNames,
  1, xml_StartIds,
  xml_TokKind,
  xml_NtClass,
  xml_ErrorNt
};

static int xml_PSymbols[] = {
  26, 36,
  6,
  28,
  17,
  5,
  13, 12,
  16,
  28,
  18, 11, 32, 31,
  19,
  20, 36, 21, 11, 29, 20,
  35, 32,
  33,
  34, 33,
  28,
  28, 11, 29, 22, 29, 14,
  37, 36,
  30,
  14,
  7,
  15,
  3,
  2,
  0,
  1,
  11,
  4,
  10,
  22,
  20,
  19,
  25,
  23,
  27,
  24
};

static int xml_PSymFrms[] = {
  0, 6,
  0,
  0,
  0,
  0,
  0, 9,
  0,
  0,
  0, 4, 9, 15,
  0,
  0, 4, 12, 17, 22, 28,
  0, 5,
  0,
  0, 6,
  0,
  0, 7, 12, 18, 22, 28,
  0, 6,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

static KFGPROD xml_KfgProds[] = {
  { "dfn", 0, 24, 2, &xml_PSymbols[0], &xml_PSymFrms[0] },
  { "pi", 0, 25, 1, &xml_PSymbols[2], &xml_PSymFrms[2] },
  { "spc", 0, 25, 1, &xml_PSymbols[3], &xml_PSymFrms[3] },
  { "xcom", 0, 25, 1, &xml_PSymbols[4], &xml_PSymFrms[4] },
  { "nul", 0, 26, 0, (int*)NULL, (int*)NULL },
  { "dfn", 0, 26, 1, &xml_PSymbols[5], &xml_PSymFrms[5] },
  { "typ", 0, 27, 2, &xml_PSymbols[6], &xml_PSymFrms[6] },
  { "spc", 0, 28, 1, &xml_PSymbols[8], &xml_PSymFrms[8] },
  { "nul", 0, 29, 0, (int*)NULL, (int*)NULL },
  { "ign0", 0, 29, 1, &xml_PSymbols[9], &xml_PSymFrms[9] },
  { "dfn", 0, 30, 4, &xml_PSymbols[10], &xml_PSymFrms[10] },
  { "nul", 0, 31, 1, &xml_PSymbols[14], &xml_PSymFrms[14] },
  { "dfn", 0, 31, 6, &xml_PSymbols[15], &xml_PSymFrms[15] },
  { "cons", 0, 32, 2, &xml_PSymbols[21], &xml_PSymFrms[21] },
  { "ign0", 0, 32, 1, &xml_PSymbols[23], &xml_PSymFrms[23] },
  { "nil", 0, 33, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 33, 2, &xml_PSymbols[24], &xml_PSymFrms[24] },
  { "spc", 0, 34, 1, &xml_PSymbols[26], &xml_PSymFrms[26] },
  { "dfn", 0, 35, 6, &xml_PSymbols[27], &xml_PSymFrms[27] },
  { "nil", 0, 36, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 36, 2, &xml_PSymbols[33], &xml_PSymFrms[33] },
  { "elm", 0, 37, 1, &xml_PSymbols[35], &xml_PSymFrms[35] },
  { "lit", 0, 37, 1, &xml_PSymbols[36], &xml_PSymFrms[36] },
  { "sect", 0, 37, 1, &xml_PSymbols[37], &xml_PSymFrms[37] },
  { "data", 0, 37, 1, &xml_PSymbols[38], &xml_PSymFrms[38] },
  { "pref", 0, 37, 1, &xml_PSymbols[39], &xml_PSymFrms[39] },
  { "eref", 0, 37, 1, &xml_PSymbols[40], &xml_PSymFrms[40] },
  { "cref", 0, 37, 1, &xml_PSymbols[41], &xml_PSymFrms[41] },
  { "href", 0, 37, 1, &xml_PSymbols[42], &xml_PSymFrms[42] },
  { "name", 0, 37, 1, &xml_PSymbols[43], &xml_PSymFrms[43] },
  { "nmtk", 0, 37, 1, &xml_PSymbols[44], &xml_PSymFrms[44] },
  { "xopr", 0, 37, 1, &xml_PSymbols[45], &xml_PSymFrms[45] },
  { "eq", 0, 37, 1, &xml_PSymbols[46], &xml_PSymFrms[46] },
  { "etg0", 0, 37, 1, &xml_PSymbols[47], &xml_PSymFrms[47] },
  { "etg1", 0, 37, 1, &xml_PSymbols[48], &xml_PSymFrms[48] },
  { "ign0", 0, 37, 1, &xml_PSymbols[49], &xml_PSymFrms[49] },
  { "else", 0, 37, 1, &xml_PSymbols[50], &xml_PSymFrms[50] },
  { "ign1", 0, 37, 1, &xml_PSymbols[51], &xml_PSymFrms[51] },
  { "Start_XDoc", 0, 38, 1, &xml_PSymbols[52], &xml_PSymFrms[52] }
};

static int xml_MstShifts[] = {
  1, -1, -1, 21, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 41, -1, -1, 
  -1, -1, 43, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, 21, -1, 45, -1, 
  47, 50, -1, 45, 45, 45, -1, 21, 
  -1, -1, -1, -1, -1, 53, 55, 45, 
  57, 59, 45, -1, 61, -1
};

static int xml_DtlShifts[] = {
  -2, 5, -5, -6, -7, -8, -9, -10, 
  -11, -12, -13, -14, -15, -16, -17, -18, 
  -19, -20, -21, -22, -23, 23, 22, 20, 
  19, 18, 17, 16, 15, 14, 13, 11, 
  10, 7, 6, 4, 3, 2, 1, 0, 
  -30, 12, -31, 11, -17, 16, -38, 11, 
  -39, -40, 20, 19, -48, 22, -49, 21, 
  -51, 11, -52, 14, -54, 20
};

static int xml_GoTos[] = {
  0, 2, 6, 8, 12, 25, 31, 35, 
  37, 41, 46, 50, 53, 59
};

static int xml_GoToDfts[] = {
  57, -1, 78, -4, -29, -40, 58, -1, 
  79, -4, -29, -40, 80, 4, 29, 40, 
  87, 31, 37, 96, 36, 99, 38, 48, 
  51, 100, 38, 104, 48, 107, 51, 81, 
  -4, -29, -40, 95, -34, 88, 31, 98, 
  37, 89, 31, 37, 97, 36, 90, -31, 
  -36, -37, 91, -31, -37, 82, 4, 86, 
  29, 101, 40, 83, -4, -29, -40
};

static int xml_ActDfts[] = {
  5, 6, 41, 20, 28, 29, 27, 26, 
  31, 2, 24, 32, 30, 40, 23, 25, 
  8, 4, 40, 35, 34, 33, 37, 36, 
  38, 3, 22, 1, 20, 7, 16, 21, 
  18, 40, 15, 16, 16, 9, 12, 20, 
  11, 18, 17, 14, 10, 40, 40, 9, 
  40, 40, 9, 19, 40, 13
};


static PARSETAB xml_ParseTab = {
  &xml_KfgHead, 39, xml_KfgProds,
  {
    54, xml_MstShifts, 62, xml_DtlShifts,
    14, xml_GoTos, 63, xml_GoToDfts,
    54, xml_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_xml()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&xml_ParseTab) );
}
