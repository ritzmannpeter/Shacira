/* [cmd_pim.c] Parser table for 'cmd'  */



#include "prs.h"

#include "prs_imp.h"


static string cmd_SNames[] = {
  "Parenthesis", "Ide", "Int", "Flo", "Opr", 
  "Set", "Seq", "Pth", "Doc", "Dol", 
  "MacInc", "MacDel", "MacDfn", "MacSep", "MacCond", 
  "Comment", "Program", "Arguments", "Options", "Environment", 
  ":", "=", "true", "false", "<", 
  ">", ";", "$", "/", ".", 
  "..", "_", "flag", "int", "real", 
  "string", "name", "path", "Source", "Dfns", 
  "Dfn", "OptVal", "OptDoc", "Val", "PLst1", 
  "PLst0", "Path", "Root1", "Root2", "RelPa0", 
  "RelP1", "RelP0", "OptDrv", "Pid", "Fid1", 
  "Fid0", "Typ"
};

static int cmd_StartIds[] = {
  38
};

static int cmd_TokKind[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 6, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2
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
  38, 19, cmd_SNames,
  1, cmd_StartIds,
  cmd_TokKind,
  cmd_NtClass,
  cmd_ErrorNt
};

static int cmd_PSymbols[] = {
  16, 54, 9, 8, 17, 39, 42, 18, 
  39, 42, 19, 39, 42,
  40, 39,
  1, 20, 56, 41, 9,
  21, 43,
  8,
  22,
  23,
  2,
  3,
  6,
  1,
  24, 44, 25,
  46, 45,
  26, 46, 45,
  47,
  48,
  50,
  27, 1, 28, 50,
  52, 28, 49,
  52, 28, 50,
  53, 51,
  28, 53, 51,
  1, 20,
  29,
  30,
  54,
  54, 29, 1,
  1, 55,
  31, 1, 55,
  32,
  33,
  34,
  35,
  36,
  37,
  38
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
  { "root", 0, 38, 13, &cmd_PSymbols[0], &cmd_PSymFrms[0] },
  { "nil", 0, 39, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 39, 2, &cmd_PSymbols[13], &cmd_PSymFrms[13] },
  { "defn", 0, 40, 5, &cmd_PSymbols[15], &cmd_PSymFrms[15] },
  { "non", 0, 41, 0, (int*)NULL, (int*)NULL },
  { "val", 0, 41, 2, &cmd_PSymbols[20], &cmd_PSymFrms[20] },
  { "non", 0, 42, 0, (int*)NULL, (int*)NULL },
  { "doc", 0, 42, 1, &cmd_PSymbols[22], &cmd_PSymFrms[22] },
  { "true", 0, 43, 1, &cmd_PSymbols[23], &cmd_PSymFrms[23] },
  { "false", 0, 43, 1, &cmd_PSymbols[24], &cmd_PSymFrms[24] },
  { "int", 0, 43, 1, &cmd_PSymbols[25], &cmd_PSymFrms[25] },
  { "real", 0, 43, 1, &cmd_PSymbols[26], &cmd_PSymFrms[26] },
  { "str", 0, 43, 1, &cmd_PSymbols[27], &cmd_PSymFrms[27] },
  { "name", 0, 43, 1, &cmd_PSymbols[28], &cmd_PSymFrms[28] },
  { "path", 0, 43, 3, &cmd_PSymbols[29], &cmd_PSymFrms[29] },
  { "cons", 0, 44, 2, &cmd_PSymbols[32], &cmd_PSymFrms[32] },
  { "nil", 0, 45, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 45, 3, &cmd_PSymbols[34], &cmd_PSymFrms[34] },
  { "ign1", 0, 46, 1, &cmd_PSymbols[37], &cmd_PSymFrms[37] },
  { "ign2", 0, 46, 1, &cmd_PSymbols[38], &cmd_PSymFrms[38] },
  { "rel", 0, 46, 1, &cmd_PSymbols[39], &cmd_PSymFrms[39] },
  { "env", 0, 46, 4, &cmd_PSymbols[40], &cmd_PSymFrms[40] },
  { "abs", 0, 47, 3, &cmd_PSymbols[44], &cmd_PSymFrms[44] },
  { "abs", 0, 48, 3, &cmd_PSymbols[47], &cmd_PSymFrms[47] },
  { "nil", 0, 49, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 50, 2, &cmd_PSymbols[50], &cmd_PSymFrms[50] },
  { "nil", 0, 51, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 51, 3, &cmd_PSymbols[52], &cmd_PSymFrms[52] },
  { "non", 0, 52, 0, (int*)NULL, (int*)NULL },
  { "drive", 0, 52, 2, &cmd_PSymbols[55], &cmd_PSymFrms[55] },
  { "curr", 0, 53, 1, &cmd_PSymbols[57], &cmd_PSymFrms[57] },
  { "prev", 0, 53, 1, &cmd_PSymbols[58], &cmd_PSymFrms[58] },
  { "name", 0, 53, 1, &cmd_PSymbols[59], &cmd_PSymFrms[59] },
  { "ext", 0, 53, 3, &cmd_PSymbols[60], &cmd_PSymFrms[60] },
  { "cons", 0, 54, 2, &cmd_PSymbols[63], &cmd_PSymFrms[63] },
  { "nil", 0, 55, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 55, 3, &cmd_PSymbols[65], &cmd_PSymFrms[65] },
  { "flag", 0, 56, 1, &cmd_PSymbols[68], &cmd_PSymFrms[68] },
  { "int", 0, 56, 1, &cmd_PSymbols[69], &cmd_PSymFrms[69] },
  { "real", 0, 56, 1, &cmd_PSymbols[70], &cmd_PSymFrms[70] },
  { "str", 0, 56, 1, &cmd_PSymbols[71], &cmd_PSymFrms[71] },
  { "name", 0, 56, 1, &cmd_PSymbols[72], &cmd_PSymFrms[72] },
  { "path", 0, 56, 1, &cmd_PSymbols[73], &cmd_PSymFrms[73] },
  { "Start_Source", 0, 57, 1, &cmd_PSymbols[74], &cmd_PSymFrms[74] }
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
  -2, 16, -4, 1, -6, 31, -8, 9, 
  -9, 1, -10, 8, -12, 17, -13, 1, 
  -16, 20, -17, 8, -20, -21, -22, -23, 
  -24, -25, 37, 36, 35, 34, 33, 32, 
  -27, 18, -28, 21, -31, -32, -33, -34, 
  -35, -36, -37, 24, 23, 22, 6, 3, 
  2, 1, -39, 9, -41, -42, -43, -44, 
  30, 29, 27, 1, -53, 19, -6, -54, 
  20, 31, -55, 1, -56, 25, -57, 26, 
  -59, 28, -60, 28, -62, 29, -64, 28, 
  -4, -43, -44, 30, 29, 1, -69, 1
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
