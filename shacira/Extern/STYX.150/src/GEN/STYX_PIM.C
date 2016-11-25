/* [styx_pim.c] Parser table for 'styx'  */



#include "prs.h"

#include "prs_imp.h"


static string styx_SNames[] = {
  "Parenthesis", "Comment", "Ide", "Nat", "Opr", 
  "Set", "Seq", "MacInc", "MacDfn", "MacSep", 
  "MacCond", "Language", "Regular", "Grammar", "Context", 
  "Free", "=", "let", "tok", "ign", 
  "com", "lan", "[", "ica", "]", 
  "|", "-", "{", "}", "+", 
  "..", "(", ")", "xtop", "start", 
  "err", ":", "?", "!", "other", 
  "Source", "OptCfg", "QlxDfns", "QlxDfn", "QlxCat", 
  "QlxOpt", "Exp", "Exp1", "Exp2", "Exp3", 
  "Exp4", "Dfns", "Dfn", "Cat0", "Cat", 
  "DfnOpt", "Prds", "Lay", "Prd", "Mbrs", 
  "Mbr"
};

static int styx_StartIds[] = {
  40
};

static int styx_TokKind[] = {
  1, 5, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2
};

static int styx_NtClass[] = {
  0, 1, 2, 3, 4, 5, 6, 6, 
  6, 6, 6, 11, 12, 14, 14, 15, 
  16, 17, 18, 19, 20
};

static c_bool styx_ErrorNt[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0
};

static KFGHEAD styx_KfgHead = {
  "styx",
  40, 21, styx_SNames,
  1, styx_StartIds,
  styx_TokKind,
  styx_NtClass,
  styx_ErrorNt
};

static int styx_PSymbols[] = {
  11, 2, 12, 13, 42, 41,
  14, 15, 13, 51,
  43, 42,
  44, 45, 2, 16, 46,
  17,
  18,
  19,
  20,
  21,
  22, 23, 24,
  46, 25, 47,
  46, 26, 47,
  47,
  47, 48,
  48,
  22, 46, 24,
  27, 46, 28,
  49, 29,
  49,
  50,
  50, 30, 50,
  31, 46, 32,
  6,
  5,
  2,
  52, 51,
  54, 55, 2, 56,
  33,
  17,
  34,
  53,
  22, 35, 24,
  58, 56,
  36,
  37,
  38,
  57, 2, 36, 59,
  60, 59,
  2,
  6,
  22, 39, 24,
  40
};

static int styx_PSymFrms[] = {
  0, 11, 0, 10, -2, 0,
  0, 10, 17, -2,
  0, 0,
  0, 7, 14, 18, 22,
  0,
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
  0,
  0, 5, 10,
  0, 4, 8,
  0,
  0,
  0,
  0, 0,
  0, 4, 11, 0,
  0,
  0,
  0,
  0,
  0, 4, 10,
  0, 0,
  0,
  0,
  0,
  0, 4, 8, -2,
  0, 0,
  0,
  0,
  0, 4, 12,
  0
};

static KFGPROD styx_KfgProds[] = {
  { "root", 0, 40, 6, &styx_PSymbols[0], &styx_PSymFrms[0] },
  { "nul", 0, 41, 0, (int*)NULL, (int*)NULL },
  { "cfg", 0, 41, 4, &styx_PSymbols[6], &styx_PSymFrms[6] },
  { "nil", 0, 42, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 42, 2, &styx_PSymbols[10], &styx_PSymFrms[10] },
  { "defn", 2, 43, 5, &styx_PSymbols[12], &styx_PSymFrms[12] },
  { "letC", 0, 44, 1, &styx_PSymbols[17], &styx_PSymFrms[17] },
  { "tokC", 0, 44, 1, &styx_PSymbols[18], &styx_PSymFrms[18] },
  { "ignC", 0, 44, 1, &styx_PSymbols[19], &styx_PSymFrms[19] },
  { "comC", 0, 44, 1, &styx_PSymbols[20], &styx_PSymFrms[20] },
  { "ctxC", 0, 44, 1, &styx_PSymbols[21], &styx_PSymFrms[21] },
  { "non", 0, 45, 0, (int*)NULL, (int*)NULL },
  { "ignca", 0, 45, 3, &styx_PSymbols[22], &styx_PSymFrms[22] },
  { "union", 0, 46, 3, &styx_PSymbols[25], &styx_PSymFrms[25] },
  { "diff", 0, 46, 3, &styx_PSymbols[28], &styx_PSymFrms[28] },
  { "ign1", 0, 46, 1, &styx_PSymbols[31], &styx_PSymFrms[31] },
  { "conc", 0, 47, 2, &styx_PSymbols[32], &styx_PSymFrms[32] },
  { "ign1", 0, 47, 1, &styx_PSymbols[34], &styx_PSymFrms[34] },
  { "opt", 0, 48, 3, &styx_PSymbols[35], &styx_PSymFrms[35] },
  { "star", 0, 48, 3, &styx_PSymbols[38], &styx_PSymFrms[38] },
  { "plus", 0, 48, 2, &styx_PSymbols[41], &styx_PSymFrms[41] },
  { "ign1", 0, 48, 1, &styx_PSymbols[43], &styx_PSymFrms[43] },
  { "ign1", 0, 49, 1, &styx_PSymbols[44], &styx_PSymFrms[44] },
  { "range", 0, 49, 3, &styx_PSymbols[45], &styx_PSymFrms[45] },
  { "ign2", 0, 49, 3, &styx_PSymbols[48], &styx_PSymFrms[48] },
  { "sequ", 0, 50, 1, &styx_PSymbols[51], &styx_PSymFrms[51] },
  { "set", 0, 50, 1, &styx_PSymbols[52], &styx_PSymFrms[52] },
  { "ident", 0, 50, 1, &styx_PSymbols[53], &styx_PSymFrms[53] },
  { "nil", 0, 51, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 51, 2, &styx_PSymbols[54], &styx_PSymFrms[54] },
  { "defn", 2, 52, 4, &styx_PSymbols[56], &styx_PSymFrms[56] },
  { "bgnC", 0, 53, 1, &styx_PSymbols[60], &styx_PSymFrms[60] },
  { "letC", 0, 54, 1, &styx_PSymbols[61], &styx_PSymFrms[61] },
  { "bgnC", 0, 54, 1, &styx_PSymbols[62], &styx_PSymFrms[62] },
  { "ign0", 0, 54, 1, &styx_PSymbols[63], &styx_PSymFrms[63] },
  { "non", 0, 55, 0, (int*)NULL, (int*)NULL },
  { "errnt", 0, 55, 3, &styx_PSymbols[64], &styx_PSymFrms[64] },
  { "nil", 0, 56, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 56, 2, &styx_PSymbols[67], &styx_PSymFrms[67] },
  { "dft", 0, 57, 1, &styx_PSymbols[69], &styx_PSymFrms[69] },
  { "rec", 0, 57, 1, &styx_PSymbols[70], &styx_PSymFrms[70] },
  { "grp", 0, 57, 1, &styx_PSymbols[71], &styx_PSymFrms[71] },
  { "prod", 1, 58, 4, &styx_PSymbols[72], &styx_PSymFrms[72] },
  { "nil", 0, 59, 0, (int*)NULL, (int*)NULL },
  { "cons", 1, 59, 2, &styx_PSymbols[76], &styx_PSymFrms[76] },
  { "ntm", 0, 60, 1, &styx_PSymbols[78], &styx_PSymFrms[78] },
  { "tkm", 0, 60, 1, &styx_PSymbols[79], &styx_PSymFrms[79] },
  { "else", 0, 60, 3, &styx_PSymbols[80], &styx_PSymFrms[80] },
  { "Start_Source", 0, 61, 1, &styx_PSymbols[83], &styx_PSymFrms[83] }
};

static int styx_MstShifts[] = {
  1, 3, -1, 5, 7, 13, -1, -1, 
  -1, -1, -1, 19, 13, 21, 23, -1, 
  -1, 25, 27, 29, 31, 33, 37, -1, 
  46, -1, -1, -1, -1, 37, -1, 53, 
  -1, -1, -1, 46, 46, 46, 56, 46, 
  -1, 59, 61, -1, 63, 65, 69, 75, 
  81, 46, 46, -1, -1, 87, 91, 95, 
  -1, -1, -1, 46, 46, -1, -1, -1, 
  -1, -1, -1, 99, 95, 101, -1, 105, 
  -1, -1, 109, -1, 105, 111, -1, -1
};

static int styx_DtlShifts[] = {
  -2, 11, -4, 2, -5, 12, -6, 13, 
  -7, -8, -9, -10, -11, 21, 20, 19, 
  18, 17, -15, 14, -18, 22, -20, 15, 
  -21, 23, -22, 2, -23, 13, -24, 24, 
  -25, 16, -26, -27, -28, 34, 33, 17, 
  -33, -34, -35, -36, -37, -38, 31, 27, 
  22, 6, 5, 2, -45, 22, -50, -51, 
  26, 25, -53, 29, -54, 30, -55, 35, 
  -56, 2, -50, -51, -57, 24, 26, 25, 
  -50, -51, -58, 28, 26, 25, -50, -51, 
  -59, 32, 26, 25, -33, -34, -35, 6, 
  5, 2, -63, 24, -64, -65, -66, 38, 
  37, 36, -70, 2, -72, 36, -73, -74, 
  -75, 22, 6, 2, -78, 39, -80, 24
};

static int styx_GoTos[] = {
  0, 2, 4, 8, 11, 14, 16, 24, 
  33, 44, 54, 66, 70, 73, 76, 79, 
  81, 85, 88, 91, 95
};

static int styx_GoToDfts[] = {
  83, -1, 96, -12, 92, 6, 97, 13, 
  93, -6, -13, 94, -6, -13, 99, -14, 
  119, 25, 127, 36, 128, 37, 129, 38, 
  120, 25, 36, 37, 38, 140, 50, 141, 
  51, 121, 25, 36, 37, 38, 50, 51, 
  132, 40, 60, 61, 122, -25, -36, -37, 
  -38, -40, -50, -51, -60, -61, 123, 25, 
  36, 37, 38, 40, 50, 51, 60, 61, 
  142, 54, 109, 23, 124, 30, 110, -23, 
  -30, 111, -23, -30, 112, -23, -30, 126, 
  -32, 147, 56, 151, 69, 148, -56, -69, 
  149, -56, -69, 156, 72, 159, 77, 157, 
  -72, -77
};

static int styx_ActDfts[] = {
  50, 50, 51, 50, 50, 4, 7, 8, 
  9, 10, 11, 2, 4, 12, 50, 1, 
  5, 50, 50, 50, 50, 50, 29, 13, 
  50, 33, 32, 34, 3, 29, 35, 36, 
  28, 27, 26, 50, 50, 50, 6, 16, 
  18, 22, 23, 30, 50, 50, 50, 50, 
  50, 50, 50, 17, 21, 50, 50, 38, 
  19, 20, 25, 14, 15, 24, 37, 40, 
  41, 42, 31, 50, 38, 50, 39, 44, 
  46, 47, 50, 43, 44, 50, 45, 48
};


static PARSETAB styx_ParseTab = {
  &styx_KfgHead, 49, styx_KfgProds,
  {
    80, styx_MstShifts, 112, styx_DtlShifts,
    21, styx_GoTos, 98, styx_GoToDfts,
    80, styx_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_styx()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&styx_ParseTab) );
}
