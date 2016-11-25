/* [styx_pim.c] Parser table for 'styx'  */



#include "prs.h"

#include "prs_imp.h"


static string styx_SNames[] = {
  "Parenthesis", "Comment", "Ide", "Nat", "Opr", 
  "Set", "Seq", "MacInc", "MacDel", "MacDfn", 
  "MacSep", "MacCond", "Language", "Context", "Free", 
  "Grammar", "Regular", "=", "InGroup", "ExGroup", 
  "let", "tok", "ign", "com", "lan", 
  "ind", ":", "!", "[", "ica", 
  "]", "<", ">", "|", "-", 
  "{", "}", "+", "..", "(", 
  ")", "xtop", "start", "err", "?", 
  "other", "Source", "OptCfg", "QlxDfns0", "QlxDfns", 
  "QlxDfn", "QlxCat", "QlxGrp", "QlxGrp0", "QlxGrp1", 
  "QlxOpt", "ExpDyck", "Exp0", "Exp", "Exp1", 
  "Exp2", "Exp3", "Exp4", "Dfns", "Dfn", 
  "Cat0", "Cat", "DfnOpt", "Prds", "Lay", 
  "Prd", "Mbrs", "Mbr"
};

static int styx_StartIds[] = {
  46
};

static int styx_TokKind[] = {
  1, 6, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2
};

static int styx_NtClass[] = {
  0, 1, 3, 3, 4, 5, 6, 6, 
  6, 9, 12, 12, 12, 12, 12, 12, 
  12, 17, 18, 20, 20, 21, 22, 23, 
  24, 25, 26
};

static c_bool styx_ErrorNt[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0
};

static KFGHEAD styx_KfgHead = {
  "styx",
  46, 27, styx_SNames,
  1, styx_StartIds,
  styx_TokKind,
  styx_NtClass,
  styx_ErrorNt
};

static int styx_PSymbols[] = {
  12, 2, 48, 47,
  13, 14, 15, 63,
  16, 15, 49,
  50, 49,
  51, 55, 53, 2, 54, 17, 56,
  18, 2,
  19, 2,
  20,
  21,
  22,
  23,
  24,
  25,
  26, 2, 26,
  52,
  27, 2,
  27,
  52,
  28, 29, 30,
  31, 58, 32, 57, 31, 58, 32,
  58,
  58,
  58, 33, 59,
  58, 34, 59,
  59,
  59, 60,
  60,
  28, 58, 30,
  35, 58, 36,
  61, 37,
  61,
  62,
  62, 38, 62,
  39, 58, 40,
  6,
  5,
  2,
  64, 63,
  66, 67, 2, 68,
  41,
  20,
  42,
  65,
  28, 43, 30,
  70, 68,
  26,
  44,
  27,
  69, 2, 26, 71,
  72, 71,
  2,
  6,
  28, 45, 30,
  46
};

static int styx_PSymFrms[] = {
  0, 11, 0, 0,
  0, 10, 17, -2,
  0, 10, -2,
  0, 0,
  0, 7, 14, 22, 26, 34, 38,
  0, 10,
  0, 10,
  0,
  0,
  0,
  0,
  0,
  0,
  0, 4, 8,
  0,
  0, 5,
  0,
  0,
  0, 4, 10,
  0, 4, 8, 12, 17, 21, 25,
  0,
  0,
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
  { "root", 0, 46, 4, &styx_PSymbols[0], &styx_PSymFrms[0] },
  { "nul", 0, 47, 0, (int*)NULL, (int*)NULL },
  { "cfg", 0, 47, 4, &styx_PSymbols[4], &styx_PSymFrms[4] },
  { "nil", 0, 48, 0, (int*)NULL, (int*)NULL },
  { "ign0", 0, 48, 3, &styx_PSymbols[8], &styx_PSymFrms[8] },
  { "nil", 0, 49, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 49, 2, &styx_PSymbols[11], &styx_PSymFrms[11] },
  { "defn", 2, 50, 7, &styx_PSymbols[13], &styx_PSymFrms[13] },
  { "igrp", 2, 50, 2, &styx_PSymbols[20], &styx_PSymFrms[20] },
  { "xgrp", 2, 50, 2, &styx_PSymbols[22], &styx_PSymFrms[22] },
  { "letC", 0, 51, 1, &styx_PSymbols[24], &styx_PSymFrms[24] },
  { "tokC", 0, 51, 1, &styx_PSymbols[25], &styx_PSymFrms[25] },
  { "ignC", 0, 51, 1, &styx_PSymbols[26], &styx_PSymFrms[26] },
  { "comC", 0, 51, 1, &styx_PSymbols[27], &styx_PSymFrms[27] },
  { "lanC", 0, 51, 1, &styx_PSymbols[28], &styx_PSymFrms[28] },
  { "indC", 0, 51, 1, &styx_PSymbols[29], &styx_PSymFrms[29] },
  { "non", 0, 52, 0, (int*)NULL, (int*)NULL },
  { "grp", 0, 53, 3, &styx_PSymbols[30], &styx_PSymFrms[30] },
  { "ign0", 0, 53, 1, &styx_PSymbols[33], &styx_PSymFrms[33] },
  { "grp", 0, 54, 2, &styx_PSymbols[34], &styx_PSymFrms[34] },
  { "igrp", 0, 54, 1, &styx_PSymbols[36], &styx_PSymFrms[36] },
  { "ign0", 0, 54, 1, &styx_PSymbols[37], &styx_PSymFrms[37] },
  { "non", 0, 55, 0, (int*)NULL, (int*)NULL },
  { "ignca", 0, 55, 3, &styx_PSymbols[38], &styx_PSymFrms[38] },
  { "dyck", 0, 56, 7, &styx_PSymbols[41], &styx_PSymFrms[41] },
  { "ign0", 0, 56, 1, &styx_PSymbols[48], &styx_PSymFrms[48] },
  { "nul", 0, 57, 0, (int*)NULL, (int*)NULL },
  { "ign0", 0, 57, 1, &styx_PSymbols[49], &styx_PSymFrms[49] },
  { "union", 0, 58, 3, &styx_PSymbols[50], &styx_PSymFrms[50] },
  { "diff", 0, 58, 3, &styx_PSymbols[53], &styx_PSymFrms[53] },
  { "ign1", 0, 58, 1, &styx_PSymbols[56], &styx_PSymFrms[56] },
  { "conc", 0, 59, 2, &styx_PSymbols[57], &styx_PSymFrms[57] },
  { "ign1", 0, 59, 1, &styx_PSymbols[59], &styx_PSymFrms[59] },
  { "opt", 0, 60, 3, &styx_PSymbols[60], &styx_PSymFrms[60] },
  { "star", 0, 60, 3, &styx_PSymbols[63], &styx_PSymFrms[63] },
  { "plus", 0, 60, 2, &styx_PSymbols[66], &styx_PSymFrms[66] },
  { "ign1", 0, 60, 1, &styx_PSymbols[68], &styx_PSymFrms[68] },
  { "ign1", 0, 61, 1, &styx_PSymbols[69], &styx_PSymFrms[69] },
  { "range", 0, 61, 3, &styx_PSymbols[70], &styx_PSymFrms[70] },
  { "ign2", 0, 61, 3, &styx_PSymbols[73], &styx_PSymFrms[73] },
  { "sequ", 0, 62, 1, &styx_PSymbols[76], &styx_PSymFrms[76] },
  { "set", 0, 62, 1, &styx_PSymbols[77], &styx_PSymFrms[77] },
  { "ident", 0, 62, 1, &styx_PSymbols[78], &styx_PSymFrms[78] },
  { "nil", 0, 63, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 63, 2, &styx_PSymbols[79], &styx_PSymFrms[79] },
  { "defn", 2, 64, 4, &styx_PSymbols[81], &styx_PSymFrms[81] },
  { "bgnC", 0, 65, 1, &styx_PSymbols[85], &styx_PSymFrms[85] },
  { "letC", 0, 66, 1, &styx_PSymbols[86], &styx_PSymFrms[86] },
  { "bgnC", 0, 66, 1, &styx_PSymbols[87], &styx_PSymFrms[87] },
  { "ign0", 0, 66, 1, &styx_PSymbols[88], &styx_PSymFrms[88] },
  { "non", 0, 67, 0, (int*)NULL, (int*)NULL },
  { "errnt", 0, 67, 3, &styx_PSymbols[89], &styx_PSymFrms[89] },
  { "nil", 0, 68, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 68, 2, &styx_PSymbols[92], &styx_PSymFrms[92] },
  { "dft", 0, 69, 1, &styx_PSymbols[94], &styx_PSymFrms[94] },
  { "rec", 0, 69, 1, &styx_PSymbols[95], &styx_PSymFrms[95] },
  { "grp", 0, 69, 1, &styx_PSymbols[96], &styx_PSymFrms[96] },
  { "prod", 1, 70, 4, &styx_PSymbols[97], &styx_PSymFrms[97] },
  { "nil", 0, 71, 0, (int*)NULL, (int*)NULL },
  { "cons", 1, 71, 2, &styx_PSymbols[101], &styx_PSymFrms[101] },
  { "ntm", 0, 72, 1, &styx_PSymbols[103], &styx_PSymFrms[103] },
  { "tkm", 0, 72, 1, &styx_PSymbols[104], &styx_PSymFrms[104] },
  { "else", 0, 72, 3, &styx_PSymbols[105], &styx_PSymFrms[105] },
  { "Start_Source", 0, 73, 1, &styx_PSymbols[108], &styx_PSymFrms[108] }
};

static int styx_MstShifts[] = {
  1, 3, -1, 5, 7, 9, 18, 27, 
  -1, 29, 31, -1, -1, -1, -1, -1, 
  -1, -1, 18, 33, 35, -1, -1, -1, 
  37, 39, 43, 47, 49, -1, 51, -1, 
  -1, -1, -1, 43, -1, 53, -1, 55, 
  57, -1, 59, 61, -1, 63, -1, 65, 
  67, 71, -1, 81, -1, -1, -1, -1, 
  -1, 89, 71, -1, -1, -1, 96, 96, 
  96, 96, -1, 104, 96, -1, 107, 109, 
  111, -1, 115, 121, 127, 133, 96, 96, 
  -1, -1, 139, 145, -1, 96, -1, -1, 
  96, 96, -1, -1, -1, 149, -1, 145, 
  151, 104, 153, -1, 96, -1, 157, -1
};

static int styx_DtlShifts[] = {
  -2, 12, -4, 2, -5, 16, -7, 15, 
  -8, 13, -10, -11, -12, -13, -14, -15, 
  -16, -17, 25, 24, 23, 22, 21, 20, 
  19, 18, -21, 14, -22, 2, -23, 2, 
  -25, 28, -27, 15, -28, 29, -29, 26, 
  -32, -33, -34, 42, 41, 20, -39, 30, 
  -40, 2, -41, 2, -43, 28, -45, 26, 
  -46, 27, -49, 43, -50, 2, -51, 2, 
  -52, 17, -53, 30, -54, -55, -56, 44, 
  27, 26, -60, -61, -62, -63, -64, -65, 
  -66, 39, 35, 31, 28, 6, 5, 2, 
  -73, 2, -60, -61, -62, -63, -65, -66, 
  39, 35, 28, 6, 5, 2, -79, -80, 
  34, 33, -82, 37, -83, 38, -84, 26, 
  -79, -80, -85, 30, 34, 33, -79, -80, 
  -86, 32, 34, 33, -79, -80, -87, 36, 
  34, 33, -79, -80, -88, 40, 34, 33, 
  -60, -61, -62, 6, 5, 2, -92, -93, 
  -94, 28, 6, 2, -99, 45, -101, 31, 
  -102, 30, -79, -80, -104, 32, 34, 33
};

static int styx_GoTos[] = {
  0, 2, 4, 6, 10, 13, 16, 20, 
  22, 24, 26, 28, 30, 44, 56, 70, 
  83, 98, 102, 105, 108, 111, 113, 117, 
  120, 123, 127
};

static int styx_GoToDfts[] = {
  107, -1, 113, -6, 110, -4, 122, 7, 
  128, 19, 123, -7, -19, 124, -7, -19, 
  134, 26, 151, 41, 135, -26, 152, -41, 
  130, -20, 171, -52, 201, -86, 172, 52, 
  179, 63, 180, 64, 181, 65, 182, 66, 
  202, 86, 207, 101, 173, 52, 63, 64, 
  65, 66, 86, 101, 193, 79, 194, 80, 
  174, 52, 63, 64, 65, 66, 79, 80, 
  86, 101, 185, 69, 89, 90, 175, -52, 
  -63, -64, -65, -66, -69, -79, -80, -86, 
  -89, -90, -101, 176, 52, 63, 64, 65, 
  66, 69, 79, 80, 86, 89, 90, 101, 
  195, 83, 139, 27, 146, 36, 140, -27, 
  -36, 141, -27, -36, 142, -27, -36, 148, 
  -38, 161, 50, 178, 59, 162, -50, -59, 
  163, -50, -59, 199, 84, 204, 96, 200, 
  -84, -96
};

static int styx_ActDfts[] = {
  65, 65, 66, 4, 65, 2, 6, 65, 
  1, 65, 65, 11, 12, 13, 14, 15, 
  16, 5, 6, 23, 65, 9, 10, 7, 
  65, 17, 44, 65, 65, 19, 65, 48, 
  47, 49, 3, 44, 50, 51, 24, 65, 
  17, 45, 65, 65, 18, 21, 22, 65, 
  65, 53, 20, 65, 52, 55, 57, 56, 
  46, 65, 53, 43, 42, 41, 65, 65, 
  65, 65, 8, 26, 31, 33, 37, 38, 
  65, 54, 65, 65, 65, 65, 65, 65, 
  32, 36, 65, 59, 34, 27, 35, 40, 
  29, 30, 39, 61, 62, 65, 58, 59, 
  65, 28, 65, 60, 65, 63, 65, 25
};


static PARSETAB styx_ParseTab = {
  &styx_KfgHead, 64, styx_KfgProds,
  {
    104, styx_MstShifts, 160, styx_DtlShifts,
    27, styx_GoTos, 130, styx_GoToDfts,
    104, styx_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_styx()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&styx_ParseTab) );
}
