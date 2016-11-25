/* [esty_pim.c] Parser table for 'estyx'  */



#include "prs.h"

#include "prs_imp.h"


static string estyx_SNames[] = {
  "Parenthesis", "Comment", "Ide", "Nat", "Opr", 
  "Set", "Seq", "Language", "Regular", "Grammar", 
  "Context", "Free", "=", "let", "tok", 
  "ign", "com", "[", "ica", "]", 
  "|", "-", "{", "}", "+", 
  "..", "(", ")", "start", ":", 
  "...", "Source", "QlxDfns", "QlxDfn", "QlxCat", 
  "QlxOpt", "Exp", "Exp1", "Exp2", "Exp3", 
  "Exp4", "Dfns", "Dfn", "Cat", "Prds", 
  "Prd", "Mbrs", "Mbr", "Form", "Toks"
};

static int estyx_StartIds[] = {
  31
};

static int estyx_TokKind[] = {
  1, 5, 1, 1, 1, 1, 1, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2
};

static int estyx_NtClass[] = {
  0, 1, 2, 3, 4, 5, 5, 5, 
  5, 5, 10, 11, 12, 13, 14, 15, 
  16, 17, 18
};

static c_bool estyx_ErrorNt[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0
};

static KFGHEAD estyx_KfgHead = {
  "estyx",
  31, 19, estyx_SNames,
  1, estyx_StartIds,
  estyx_TokKind,
  estyx_NtClass,
  estyx_ErrorNt
};

static int estyx_PSymbols[] = {
  7, 2, 8, 9, 32, 10, 11, 9, 
  41,
  33, 32,
  34, 35, 2, 12, 36,
  13,
  14,
  15,
  16,
  17, 18, 19,
  36, 20, 37,
  36, 21, 37,
  37,
  37, 38,
  38,
  17, 36, 19,
  22, 36, 23,
  39, 24,
  39,
  40, 25, 40,
  26, 36, 27,
  40,
  6,
  5,
  2,
  42, 41,
  43, 2, 44,
  13,
  28,
  45, 44,
  29, 2, 29, 46,
  47, 46,
  6,
  48,
  2,
  26, 48, 49, 30, 27,
  17, 49, 48, 49, 30, 49, 19,
  6, 49,
  31
};

static int estyx_PSymFrms[] = {
  0, 11, 0, 10, 20, 0, 10, 17, 
  27,
  0, 7,
  0, 7, 14, 18, 22,
  0,
  0,
  0,
  0,
  0, 4, 10,
  0, 4, 8,
  0, 4, 8,
  0,
  0, 5,
  0,
  0, 4, 8,
  0, 4, 8,
  0, 5,
  0,
  0, 5, 10,
  0, 4, 8,
  0,
  0,
  0,
  0,
  0, 4,
  0, 4, 8,
  0,
  0,
  0, 4,
  0, 4, 8, 12,
  0, 4,
  0,
  0,
  0,
  0, 9, 14, 19, 30,
  0, 4, 9, 14, 19, 25, 30,
  0, 4,
  0
};

static KFGPROD estyx_KfgProds[] = {
  { "root", 0, 31, 9, &estyx_PSymbols[0], &estyx_PSymFrms[0] },
  { "nil", 0, 32, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 32, 2, &estyx_PSymbols[9], &estyx_PSymFrms[9] },
  { "defn", 0, 33, 5, &estyx_PSymbols[11], &estyx_PSymFrms[11] },
  { "letC", 0, 34, 1, &estyx_PSymbols[16], &estyx_PSymFrms[16] },
  { "tokC", 0, 34, 1, &estyx_PSymbols[17], &estyx_PSymFrms[17] },
  { "ignC", 0, 34, 1, &estyx_PSymbols[18], &estyx_PSymFrms[18] },
  { "comC", 0, 34, 1, &estyx_PSymbols[19], &estyx_PSymFrms[19] },
  { "non", 0, 35, 0, (int*)NULL, (int*)NULL },
  { "ignca", 0, 35, 3, &estyx_PSymbols[20], &estyx_PSymFrms[20] },
  { "union", 0, 36, 3, &estyx_PSymbols[23], &estyx_PSymFrms[23] },
  { "diff", 0, 36, 3, &estyx_PSymbols[26], &estyx_PSymFrms[26] },
  { "ign1", 0, 36, 1, &estyx_PSymbols[29], &estyx_PSymFrms[29] },
  { "conc", 0, 37, 2, &estyx_PSymbols[30], &estyx_PSymFrms[30] },
  { "ign1", 0, 37, 1, &estyx_PSymbols[32], &estyx_PSymFrms[32] },
  { "opt", 0, 38, 3, &estyx_PSymbols[33], &estyx_PSymFrms[33] },
  { "star", 0, 38, 3, &estyx_PSymbols[36], &estyx_PSymFrms[36] },
  { "plus", 0, 38, 2, &estyx_PSymbols[39], &estyx_PSymFrms[39] },
  { "ign1", 0, 38, 1, &estyx_PSymbols[41], &estyx_PSymFrms[41] },
  { "range", 0, 39, 3, &estyx_PSymbols[42], &estyx_PSymFrms[42] },
  { "ign2", 0, 39, 3, &estyx_PSymbols[45], &estyx_PSymFrms[45] },
  { "ign1", 0, 39, 1, &estyx_PSymbols[48], &estyx_PSymFrms[48] },
  { "sequ", 0, 40, 1, &estyx_PSymbols[49], &estyx_PSymFrms[49] },
  { "set", 0, 40, 1, &estyx_PSymbols[50], &estyx_PSymFrms[50] },
  { "ident", 0, 40, 1, &estyx_PSymbols[51], &estyx_PSymFrms[51] },
  { "nil", 0, 41, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 41, 2, &estyx_PSymbols[52], &estyx_PSymFrms[52] },
  { "defn", 0, 42, 3, &estyx_PSymbols[54], &estyx_PSymFrms[54] },
  { "letC", 0, 43, 1, &estyx_PSymbols[57], &estyx_PSymFrms[57] },
  { "bgnC", 0, 43, 1, &estyx_PSymbols[58], &estyx_PSymFrms[58] },
  { "nil", 0, 44, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 44, 2, &estyx_PSymbols[59], &estyx_PSymFrms[59] },
  { "prod", 0, 45, 4, &estyx_PSymbols[61], &estyx_PSymFrms[61] },
  { "nil", 0, 46, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 46, 2, &estyx_PSymbols[65], &estyx_PSymFrms[65] },
  { "tkm", 0, 47, 1, &estyx_PSymbols[67], &estyx_PSymFrms[67] },
  { "ntm", 0, 47, 1, &estyx_PSymbols[68], &estyx_PSymFrms[68] },
  { "ide", 0, 48, 1, &estyx_PSymbols[69], &estyx_PSymFrms[69] },
  { "one", 0, 48, 5, &estyx_PSymbols[70], &estyx_PSymFrms[70] },
  { "nul", 0, 48, 7, &estyx_PSymbols[75], &estyx_PSymFrms[75] },
  { "nil", 0, 49, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 49, 2, &estyx_PSymbols[82], &estyx_PSymFrms[82] },
  { "Start_Source", 0, 50, 1, &estyx_PSymbols[84], &estyx_PSymFrms[84] }
};

static int estyx_MstShifts[] = {
  1, 3, -1, 5, 7, 12, -1, -1, 
  -1, -1, 17, 12, 19, 21, -1, 23, 
  25, 27, 29, 31, 34, -1, 42, -1, 
  -1, -1, 34, 49, -1, -1, -1, 42, 
  42, 42, 52, 42, -1, 55, 57, -1, 
  59, 63, 69, 75, 42, 42, -1, -1, 
  81, 85, -1, 59, -1, -1, -1, 42, 
  42, -1, 87, -1, 92, -1, -1, 97, 
  101, -1, 92, -1, 97, 101, 97, -1, 
  -1, 97, 105, 107, 109, 97, -1, 111, 
  -1
};

static int estyx_DtlShifts[] = {
  -2, 7, -4, 2, -5, 8, -6, 9, 
  -7, -8, -9, -10, 16, 15, 14, 13, 
  -14, 10, -16, 17, -18, 11, -19, 18, 
  -20, 2, -21, 9, -22, 19, -23, 12, 
  -24, -25, 28, 13, -29, -30, -31, -32, 
  -33, -34, 26, 22, 17, 6, 5, 2, 
  -41, 2, -45, -46, 21, 20, -48, 24, 
  -49, 25, -50, 29, -45, -46, -53, 19, 
  21, 20, -45, -46, -54, 23, 21, 20, 
  -45, -46, -55, 27, 21, 20, -29, -30, 
  -31, 6, 5, 2, -59, 2, -61, 29, 
  -62, -63, -64, -65, 26, 17, 6, 2, 
  -69, 6, -62, -64, -65, 26, 17, 2, 
  -77, 30, -78, 30, -79, 27, -81, 19
};

static int estyx_GoTos[] = {
  0, 2, 6, 9, 12, 14, 22, 31, 
  42, 52, 64, 68, 71, 74, 78, 81, 
  85, 88, 95
};

static int estyx_GoToDfts[] = {
  84, -1, 92, 6, 96, 12, 93, -6, 
  -12, 94, -6, -12, 98, -13, 116, 23, 
  123, 32, 124, 33, 125, 34, 117, 23, 
  32, 33, 34, 137, 45, 138, 46, 118, 
  23, 32, 33, 34, 45, 46, 128, 36, 
  56, 57, 119, -23, -32, -33, -34, -36, 
  -45, -46, -56, -57, 120, 23, 32, 33, 
  34, 36, 45, 46, 56, 57, 139, 49, 
  107, 21, 121, 27, 108, -21, -27, 109, 
  -21, -27, 132, 41, 141, 52, 133, -41, 
  -52, 147, 61, 153, 67, 148, -61, -67, 
  149, 61, 67, 152, 65, 155, 70, 151, 
  64, 154, 69, 156, 71, 157, 74, 161, 
  78
};

static int estyx_ActDfts[] = {
  44, 44, 45, 44, 44, 2, 5, 6, 
  7, 8, 44, 2, 9, 44, 3, 44, 
  44, 44, 44, 44, 26, 10, 44, 29, 
  30, 1, 26, 44, 25, 24, 23, 44, 
  44, 44, 4, 13, 15, 19, 22, 27, 
  31, 44, 44, 44, 44, 44, 14, 18, 
  44, 44, 28, 31, 16, 17, 21, 11, 
  12, 20, 44, 32, 34, 38, 36, 41, 
  44, 33, 34, 37, 41, 44, 41, 35, 
  42, 41, 44, 44, 44, 41, 39, 44, 
  40
};


static PARSETAB estyx_ParseTab = {
  &estyx_KfgHead, 43, estyx_KfgProds,
  {
    81, estyx_MstShifts, 112, estyx_DtlShifts,
    19, estyx_GoTos, 105, estyx_GoToDfts,
    81, estyx_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_estyx()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&estyx_ParseTab) );
}
