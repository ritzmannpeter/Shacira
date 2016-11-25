/* [cmd_pim.c] Parser table for 'cmd'  */



#include "prs.h"

#include "prs_imp.h"


static string cmd_SNames[] = {
  "Parenthesis", "Ide", "Int", "Flo", "Opr", 
  "Set", "Seq", "Pth", "Doc", "Dol", 
  "MacInc", "MacDfn", "MacSep", "MacCond", "Comment", 
  "Program", "Arguments", "Options", "Environment", ":", 
  "=", "true", "false", "<", ">", 
  ";", "$", "/", ".", "..", 
  "_", "flag", "int", "real", "string", 
  "name", "path", "Source", "Dfns", "Dfn", 
  "OptVal", "OptDoc", "Val", "PLst1", "PLst0", 
  "Path", "Root1", "Root2", "RelPa0", "RelP1", 
  "RelP0", "OptDrv", "Pid", "Fid1", "Fid0", 
  "Typ"
};

static int cmd_StartIds[] = {
  37
};

static int cmd_TokKind[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 5, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2
};

static int cmd_NtClass[] = {
  0, 1, 2, 3, 4, 5, 7, 7, 
  8, 8, 8, 13, 13, 13, 14, 15, 
  17, 17, 18
};

static c_bool cmd_ErrorNt[] = {
  1, 1, 1, 1, 1, 1, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0
};

static KFGHEAD cmd_KfgHead = {
  "cmd",
  37, 19, cmd_SNames,
  1, cmd_StartIds,
  cmd_TokKind,
  cmd_NtClass,
  cmd_ErrorNt
};

static int cmd_PSymbols[] = {
  15, 53, 9, 8, 16, 38, 41, 17, 
  38, 41, 18, 38, 41,
  39, 38,
  1, 19, 55, 40, 9,
  20, 42,
  8,
  21,
  22,
  2,
  3,
  6,
  1,
  23, 43, 24,
  45, 44,
  25, 45, 44,
  46,
  47,
  49,
  26, 1, 27, 49,
  51, 27, 48,
  51, 27, 49,
  52, 50,
  27, 52, 50,
  1, 19,
  28,
  29,
  53,
  53, 28, 1,
  1, 54,
  30, 1, 54,
  31,
  32,
  33,
  34,
  35,
  36,
  37
};

static int cmd_PSymFrms[] = {
  0, 10, 15, 19, 0, -3, 8, 0, 
  -3, 8, 0, -3, 8,
  0, 0,
  0, 4, 8, 12, 19,
  0, 4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0, 4, 10,
  0, 5,
  0, 4, 9,
  0,
  0,
  0,
  0, 4, 8, 12,
  0, 7, 11,
  0, 7, 11,
  0, 4,
  0, 4, 8,
  0, 4,
  0,
  0,
  0,
  0, 5, 9,
  0, 4,
  0, 4, 8,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

static KFGPROD cmd_KfgProds[] = {
  { "root", 0, 37, 13, &cmd_PSymbols[0], &cmd_PSymFrms[0] },
  { "nil", 0, 38, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 38, 2, &cmd_PSymbols[13], &cmd_PSymFrms[13] },
  { "defn", 0, 39, 5, &cmd_PSymbols[15], &cmd_PSymFrms[15] },
  { "non", 0, 40, 0, (int*)NULL, (int*)NULL },
  { "val", 0, 40, 2, &cmd_PSymbols[20], &cmd_PSymFrms[20] },
  { "non", 0, 41, 0, (int*)NULL, (int*)NULL },
  { "doc", 0, 41, 1, &cmd_PSymbols[22], &cmd_PSymFrms[22] },
  { "true", 0, 42, 1, &cmd_PSymbols[23], &cmd_PSymFrms[23] },
  { "false", 0, 42, 1, &cmd_PSymbols[24], &cmd_PSymFrms[24] },
  { "int", 0, 42, 1, &cmd_PSymbols[25], &cmd_PSymFrms[25] },
  { "real", 0, 42, 1, &cmd_PSymbols[26], &cmd_PSymFrms[26] },
  { "str", 0, 42, 1, &cmd_PSymbols[27], &cmd_PSymFrms[27] },
  { "name", 0, 42, 1, &cmd_PSymbols[28], &cmd_PSymFrms[28] },
  { "path", 0, 42, 3, &cmd_PSymbols[29], &cmd_PSymFrms[29] },
  { "cons", 0, 43, 2, &cmd_PSymbols[32], &cmd_PSymFrms[32] },
  { "nil", 0, 44, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 44, 3, &cmd_PSymbols[34], &cmd_PSymFrms[34] },
  { "ign1", 0, 45, 1, &cmd_PSymbols[37], &cmd_PSymFrms[37] },
  { "ign2", 0, 45, 1, &cmd_PSymbols[38], &cmd_PSymFrms[38] },
  { "rel", 0, 45, 1, &cmd_PSymbols[39], &cmd_PSymFrms[39] },
  { "env", 0, 45, 4, &cmd_PSymbols[40], &cmd_PSymFrms[40] },
  { "abs", 0, 46, 3, &cmd_PSymbols[44], &cmd_PSymFrms[44] },
  { "abs", 0, 47, 3, &cmd_PSymbols[47], &cmd_PSymFrms[47] },
  { "nil", 0, 48, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 49, 2, &cmd_PSymbols[50], &cmd_PSymFrms[50] },
  { "nil", 0, 50, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 50, 3, &cmd_PSymbols[52], &cmd_PSymFrms[52] },
  { "non", 0, 51, 0, (int*)NULL, (int*)NULL },
  { "drive", 0, 51, 2, &cmd_PSymbols[55], &cmd_PSymFrms[55] },
  { "curr", 0, 52, 1, &cmd_PSymbols[57], &cmd_PSymFrms[57] },
  { "prev", 0, 52, 1, &cmd_PSymbols[58], &cmd_PSymFrms[58] },
  { "name", 0, 52, 1, &cmd_PSymbols[59], &cmd_PSymFrms[59] },
  { "ext", 0, 52, 3, &cmd_PSymbols[60], &cmd_PSymFrms[60] },
  { "cons", 0, 53, 2, &cmd_PSymbols[63], &cmd_PSymFrms[63] },
  { "nil", 0, 54, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 54, 3, &cmd_PSymbols[65], &cmd_PSymFrms[65] },
  { "flag", 0, 55, 1, &cmd_PSymbols[68], &cmd_PSymFrms[68] },
  { "int", 0, 55, 1, &cmd_PSymbols[69], &cmd_PSymFrms[69] },
  { "real", 0, 55, 1, &cmd_PSymbols[70], &cmd_PSymFrms[70] },
  { "str", 0, 55, 1, &cmd_PSymbols[71], &cmd_PSymFrms[71] },
  { "name", 0, 55, 1, &cmd_PSymbols[72], &cmd_PSymFrms[72] },
  { "path", 0, 55, 1, &cmd_PSymbols[73], &cmd_PSymFrms[73] },
  { "Start_Source", 0, 56, 1, &cmd_PSymbols[74], &cmd_PSymFrms[74] }
};

static int cmd_MstShifts[] = {
  1, 3, -1, 5, 7, 9, -1, 11, 
  5, 13, -1, 15, 17, 19, 15, 26, 
  -1, 33, -1, -1, -1, -1, -1, -1, 
  -1, 35, 15, 43, 51, 19, -1, -1, 
  -1, -1, -1, -1, 56, -1, -1, 61, 
  64, 67, -1, -1, 69, 71, -1, -1, 
  -1, 73, 75, 77, 15, -1, 79, -1, 
  56, -1, 83, 83, -1, 87, 19, 83, 
  71, -1, -1, 75, -1, -1, -1, -1, 
  -1
};

static int cmd_DtlShifts[] = {
  -2, 15, -4, 1, -6, 30, -8, 9, 
  -9, 1, -10, 8, -12, 16, -13, 1, 
  -16, 19, -17, 8, -20, -21, -22, -23, 
  -24, -25, 36, 35, 34, 33, 32, 31, 
  -27, 17, -28, 20, -31, -32, -33, -34, 
  -35, -36, -37, 23, 22, 21, 6, 3, 
  2, 1, -39, 9, -41, -42, -43, -44, 
  29, 28, 26, 1, -53, 18, -6, -54, 
  19, 30, -55, 1, -56, 24, -57, 25, 
  -59, 27, -60, 27, -62, 28, -64, 27, 
  -4, -43, -44, 29, 28, 1, -69, 1
};

static int cmd_GoTos[] = {
  0, 2, 10, 15, 17, 23, 25, 27, 
  31, 35, 38, 41, 43, 50, 54, 57, 
  64, 72, 77
};

static int cmd_GoToDfts[] = {
  76, -1, 87, 12, 92, 15, 103, 27, 
  136, 53, 88, -12, -15, -27, -53, 102, 
  -26, 91, 14, 113, 30, 143, 63, 111, 
  -28, 118, -37, 131, 46, 145, 65, 119, 
  37, 138, 57, 120, -37, -57, 121, -37, 
  -57, 139, -59, 122, 37, 57, 140, 59, 
  144, 64, 134, 51, 146, 68, 123, -37, 
  -57, 124, 37, 57, 59, 64, 141, 60, 
  78, 2, 125, 37, 57, 59, 60, 64, 
  80, 4, 41, 84, 9, 99, -16
};

static int cmd_ActDfts[] = {
  45, 45, 46, 36, 45, 45, 35, 45, 
  36, 45, 37, 2, 45, 7, 2, 45, 
  8, 45, 3, 38, 39, 40, 41, 42, 
  43, 5, 2, 45, 45, 7, 14, 11, 
  12, 13, 9, 10, 29, 6, 4, 45, 
  36, 45, 31, 32, 45, 17, 19, 20, 
  21, 45, 27, 33, 2, 30, 45, 15, 
  29, 16, 25, 45, 26, 45, 7, 45, 
  17, 23, 24, 27, 34, 1, 22, 18, 
  28
};


static PARSETAB cmd_ParseTab = {
  &cmd_KfgHead, 44, cmd_KfgProds,
  {
    73, cmd_MstShifts, 88, cmd_DtlShifts,
    19, cmd_GoTos, 79, cmd_GoToDfts,
    73, cmd_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_cmd()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&cmd_ParseTab) );
}
