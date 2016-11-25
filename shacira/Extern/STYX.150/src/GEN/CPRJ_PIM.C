/* [cprj_pim.c] Parser table for 'cprj'  */



#include "prs.h"

#include "prs_imp.h"


static string cprj_SNames[] = {
  "Name", "Opr", "Val", "Comment", "MacInc", 
  "MMacDfn", "MacSep", "MacCond", ".eq.", ".le.", 
  ".lt.", ".ge.", ".gt.", ".ne.", "?", 
  ":", "use", "Macro", "Type", "exec", 
  "Rule", "build", "from", "!", "-", 
  "TPrefix", "SPrefix", "by", "Command", "Root", 
  "Source", "Directory", "RegExp", "recursive", "Project", 
  "Targets", "Objects", "Externals", "Optional", "Libraries", 
  "Parameter", "Repository", "ProjectDfn", "RelOp", "MacDfn", 
  "Project", "Project1", "Project2", "RuleAttr", "OptTPrefix", 
  "OptSPrefix", "DstDfn", "DstName", "RegExp", "SrcAttr", 
  "SrcDfn", "TypDfn", "Project0", "Project3"
};

static int cprj_StartIds[] = {
  42
};

static int cprj_TokKind[] = {
  1, 1, 1, 5, 1, 1, 1, 1, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 2, 2, 2, 2, 2, 
  2, 2
};

static int cprj_NtClass[] = {
  0, 1, 2, 3, 3, 3, 6, 7, 
  8, 9, 10, 11, 12, 13, 14, 3, 
  3
};

static c_bool cprj_ErrorNt[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0
};

static KFGHEAD cprj_KfgHead = {
  "cprj",
  42, 17, cprj_SNames,
  1, cprj_StartIds,
  cprj_TokKind,
  cprj_NtClass,
  cprj_ErrorNt
};

static int cprj_PSymbols[] = {
  45,
  8,
  9,
  10,
  11,
  12,
  13,
  2,
  0, 43, 0, 14, 2, 15, 2,
  16, 0, 45,
  17, 0, 44, 45,
  18, 56, 45,
  19, 2, 45,
  20, 0, 21, 48, 51, 46, 22, 0, 
  55, 45,
  58,
  16, 0, 47,
  57,
  23,
  23, 24,
  25, 0,
  26, 0,
  27, 28,
  0, 52, 49, 50,
  27, 29,
  27, 30,
  27, 31,
  0,
  32, 2,
  53,
  33, 53,
  0, 54,
  0,
  0, 0,
  34, 0, 57,
  35, 0, 57,
  36, 0, 57,
  37, 0, 57,
  38, 37, 0, 57,
  39, 0, 57,
  28, 0, 2, 57,
  40, 0, 0, 2, 57,
  41, 0, 57,
  47,
  34, 0, 45,
  35, 0, 45,
  36, 0, 45,
  37, 0, 45,
  38, 37, 0, 45,
  39, 0, 45,
  28, 0, 2, 45,
  40, 0, 0, 2, 45,
  41, 0, 45,
  47,
  42
};

static int cprj_PSymFrms[] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0, 5, 11, 16, 20, 24, 28,
  0, 6, 11,
  0, 8, 13, 20,
  0, 7, 14,
  0, 7, 11,
  0, 7, 0, 8, 17, 0, 0, 7, 
  12, 0,
  0,
  0, 6, 11,
  0,
  0,
  0, 4,
  0, 10,
  0, 10,
  0, 5,
  0, 5, 13, 24,
  0, 5,
  0, 5,
  0, 5,
  0,
  0, 9,
  0,
  0, 12,
  0, 5,
  0,
  0, 5,
  0, 10, 15,
  0, 10, 15,
  0, 10, 15,
  0, 0, 5,
  0, 11, 0, 5,
  0, 12, 17,
  0, 10, 15, 19,
  0, 12, 17, 22, 0,
  0, 13, 18,
  0,
  0, 10, 15,
  0, 10, 15,
  0, 10, 15,
  0, 12, 17,
  0, 11, 23, 28,
  0, 12, 17,
  0, 10, 15, 19,
  0, 12, 17, 22, 26,
  0, 13, 18,
  0,
  0
};

static KFGPROD cprj_KfgProds[] = {
  { "root", 0, 42, 1, &cprj_PSymbols[0], &cprj_PSymFrms[0] },
  { "eq", 0, 43, 1, &cprj_PSymbols[1], &cprj_PSymFrms[1] },
  { "le", 0, 43, 1, &cprj_PSymbols[2], &cprj_PSymFrms[2] },
  { "lt", 0, 43, 1, &cprj_PSymbols[3], &cprj_PSymFrms[3] },
  { "ge", 0, 43, 1, &cprj_PSymbols[4], &cprj_PSymFrms[4] },
  { "gt", 0, 43, 1, &cprj_PSymbols[5], &cprj_PSymFrms[5] },
  { "ne", 0, 43, 1, &cprj_PSymbols[6], &cprj_PSymFrms[6] },
  { "val", 0, 44, 1, &cprj_PSymbols[7], &cprj_PSymFrms[7] },
  { "cond", 0, 44, 7, &cprj_PSymbols[8], &cprj_PSymFrms[8] },
  { "inc", 0, 45, 3, &cprj_PSymbols[15], &cprj_PSymFrms[15] },
  { "mac", 0, 45, 4, &cprj_PSymbols[18], &cprj_PSymFrms[18] },
  { "typ", 0, 45, 3, &cprj_PSymbols[22], &cprj_PSymFrms[22] },
  { "exec", 0, 45, 3, &cprj_PSymbols[25], &cprj_PSymFrms[25] },
  { "rule", 0, 45, 10, &cprj_PSymbols[28], &cprj_PSymFrms[28] },
  { "ign0", 0, 45, 1, &cprj_PSymbols[38], &cprj_PSymFrms[38] },
  { "inc", 0, 46, 3, &cprj_PSymbols[39], &cprj_PSymFrms[39] },
  { "ign0", 0, 46, 1, &cprj_PSymbols[42], &cprj_PSymFrms[42] },
  { "nul", 0, 47, 0, (int*)NULL, (int*)NULL },
  { "nul", 0, 48, 0, (int*)NULL, (int*)NULL },
  { "exe", 0, 48, 1, &cprj_PSymbols[43], &cprj_PSymFrms[43] },
  { "ex2", 0, 48, 2, &cprj_PSymbols[44], &cprj_PSymFrms[44] },
  { "nul", 0, 49, 0, (int*)NULL, (int*)NULL },
  { "pre", 0, 49, 2, &cprj_PSymbols[46], &cprj_PSymFrms[46] },
  { "nul", 0, 50, 0, (int*)NULL, (int*)NULL },
  { "pre", 0, 50, 2, &cprj_PSymbols[48], &cprj_PSymFrms[48] },
  { "ext", 0, 51, 2, &cprj_PSymbols[50], &cprj_PSymFrms[50] },
  { "int", 0, 51, 4, &cprj_PSymbols[52], &cprj_PSymFrms[52] },
  { "root", 0, 52, 2, &cprj_PSymbols[56], &cprj_PSymFrms[56] },
  { "src", 0, 52, 2, &cprj_PSymbols[58], &cprj_PSymFrms[58] },
  { "dir", 0, 52, 2, &cprj_PSymbols[60], &cprj_PSymFrms[60] },
  { "nam", 0, 52, 1, &cprj_PSymbols[62], &cprj_PSymFrms[62] },
  { "nul", 0, 53, 0, (int*)NULL, (int*)NULL },
  { "exp", 0, 53, 2, &cprj_PSymbols[63], &cprj_PSymFrms[63] },
  { "exp", 0, 54, 1, &cprj_PSymbols[65], &cprj_PSymFrms[65] },
  { "rexp", 0, 54, 2, &cprj_PSymbols[66], &cprj_PSymFrms[66] },
  { "dfn", 0, 55, 2, &cprj_PSymbols[68], &cprj_PSymFrms[68] },
  { "one", 0, 56, 1, &cprj_PSymbols[70], &cprj_PSymFrms[70] },
  { "two", 0, 56, 2, &cprj_PSymbols[71], &cprj_PSymFrms[71] },
  { "dprj", 0, 57, 3, &cprj_PSymbols[73], &cprj_PSymFrms[73] },
  { "ddst", 0, 57, 3, &cprj_PSymbols[76], &cprj_PSymFrms[76] },
  { "dobj", 0, 57, 3, &cprj_PSymbols[79], &cprj_PSymFrms[79] },
  { "ext", 0, 57, 3, &cprj_PSymbols[82], &cprj_PSymFrms[82] },
  { "oext", 0, 57, 4, &cprj_PSymbols[85], &cprj_PSymFrms[85] },
  { "lib", 0, 57, 3, &cprj_PSymbols[89], &cprj_PSymFrms[89] },
  { "cmd", 0, 57, 4, &cprj_PSymbols[92], &cprj_PSymFrms[92] },
  { "par", 0, 57, 5, &cprj_PSymbols[96], &cprj_PSymFrms[96] },
  { "res", 0, 57, 3, &cprj_PSymbols[101], &cprj_PSymFrms[101] },
  { "ign0", 0, 57, 1, &cprj_PSymbols[104], &cprj_PSymFrms[104] },
  { "dprj", 0, 58, 3, &cprj_PSymbols[105], &cprj_PSymFrms[105] },
  { "ddst", 0, 58, 3, &cprj_PSymbols[108], &cprj_PSymFrms[108] },
  { "dobj", 0, 58, 3, &cprj_PSymbols[111], &cprj_PSymFrms[111] },
  { "ext", 0, 58, 3, &cprj_PSymbols[114], &cprj_PSymFrms[114] },
  { "oext", 0, 58, 4, &cprj_PSymbols[117], &cprj_PSymFrms[117] },
  { "lib", 0, 58, 3, &cprj_PSymbols[121], &cprj_PSymFrms[121] },
  { "cmd", 0, 58, 4, &cprj_PSymbols[124], &cprj_PSymFrms[124] },
  { "par", 0, 58, 5, &cprj_PSymbols[128], &cprj_PSymFrms[128] },
  { "res", 0, 58, 3, &cprj_PSymbols[133], &cprj_PSymFrms[133] },
  { "ign0", 0, 58, 1, &cprj_PSymbols[136], &cprj_PSymFrms[136] },
  { "Start_ProjectDfn", 0, 59, 1, &cprj_PSymbols[137], &cprj_PSymFrms[137] }
};

static int cprj_MstShifts[] = {
  14, 29, 31, 33, 35, 37, 39, 41, 
  43, 45, 47, 49, 51, 53, 55, -1, 
  -1, -1, -1, 14, 58, 61, 14, 14, 
  63, 65, 14, 14, 14, 14, 67, 14, 
  69, 14, -1, 76, -1, 14, -1, -1, 
  -1, 83, 14, -1, -1, -1, -1, 14, 
  -1, 85, -1, -1, -1, -1, -1, -1, 
  -1, 87, -1, 89, 92, -1, -1, 14, 
  95, -1, 98, 101, 112, -1, 123, -1, 
  127, 131, -1, 133, 135, 137, 139, 141, 
  143, 145, 147, 149, 151, 153, -1, -1, 
  155, -1, -1, -1, 157, 159, -1, 161, 
  171, 171, 171, 171, 181, 171, 183, 171, 
  185, 187, -1, 189, -1, -1, 171, -1, 
  -1, -1, -1, 171, -1, 191, -1, 193, 
  -1, -1, -1, -1, 171, 196, 14, -1, 
  199, 201, -1, -1, -1, -1, -1
};

static int cprj_DtlShifts[] = {
  -2, -3, -4, -5, -6, -7, -8, -9, 
  -10, -11, -12, -13, -14, -15, 41, 40, 
  39, 38, 37, 36, 35, 34, 28, 20, 
  19, 18, 17, 16, -20, 0, -21, 0, 
  -22, 0, -24, 2, -25, 0, -26, 0, 
  -27, 0, -28, 0, -29, 0, -30, 0, 
  -31, 37, -32, 0, -33, 0, -34, 0, 
  -36, -37, 2, 0, -39, 0, -42, 21, 
  -43, 2, -48, 0, -50, 0, -52, -53, 
  -54, -55, -56, -57, 13, 12, 11, 10, 
  9, 8, -60, 23, -64, 2, -65, 0, 
  -66, 24, -67, -68, 27, 0, -71, 14, 
  -72, -73, 27, 0, -75, 28, -76, -77, 
  -78, -79, -80, -81, -82, -83, -84, -85, 
  41, 40, 39, 38, 37, 36, 35, 34, 
  28, 16, -89, 2, -90, -91, -92, 31, 
  30, 29, -93, 25, -95, 0, -96, 0, 
  -97, 0, -98, 0, -99, 0, -100, 0, 
  -101, 37, -102, 0, -103, 0, -104, 0, 
  -105, 22, -106, 15, -107, 0, -108, 26, 
  -111, 2, -77, -78, -79, -80, -81, -82, 
  -83, -84, -85, 41, 40, 39, 38, 37, 
  36, 35, 34, 28, -116, 0, -118, 0, 
  -120, 0, -121, 2, -122, 0, -125, 2, 
  -126, 0, -129, -130, 33, 32, -134, 2, 
  -129, 32
};

static int cprj_GoTos[] = {
  0, 2, 4, 6, 36, 38, 67, 69, 
  71, 73, 75, 77, 81, 83, 85, 87, 
  107
};

static int cprj_GoToDfts[] = {
  151, -1, 193, -36, 173, -21, 152, 1, 
  170, 20, 175, 23, 176, 24, 179, 27, 
  180, 28, 181, 29, 182, 30, 184, 32, 
  186, 34, 194, 38, 197, 43, 198, 48, 
  205, 64, 268, 127, 221, -69, 153, 1, 
  20, 23, 24, 27, 28, 29, 30, 32, 
  34, 38, 43, 48, 64, 127, 222, 69, 
  97, 98, 99, 100, 102, 104, 111, 116, 
  125, 245, 95, 196, -42, 229, -74, 244, 
  -94, 204, -61, 209, -67, 266, 126, 270, 
  130, 267, -126, 262, -120, 158, -4, 223, 
  69, 247, 97, 248, 98, 249, 99, 250, 
  100, 252, 102, 254, 104, 258, 111, 259, 
  116, 263, 125, 154, -1, -20, -23, -24, 
  -27, -28, -29, -30, -32, -34, -38, -43, 
  -48, -64, -127
};

static int cprj_ActDfts[] = {
  18, 60, 60, 60, 60, 60, 60, 60, 
  60, 60, 60, 60, 60, 60, 60, 61, 
  1, 58, 15, 18, 60, 37, 18, 18, 
  60, 60, 18, 18, 18, 18, 60, 18, 
  60, 18, 10, 60, 8, 18, 38, 12, 
  13, 19, 18, 49, 50, 51, 52, 18, 
  54, 60, 57, 2, 3, 4, 5, 6, 
  7, 60, 11, 20, 60, 55, 53, 18, 
  60, 21, 60, 60, 18, 56, 60, 31, 
  60, 22, 26, 60, 60, 60, 60, 60, 
  60, 60, 60, 60, 60, 60, 48, 17, 
  60, 28, 29, 30, 60, 24, 18, 60, 
  18, 18, 18, 18, 60, 18, 60, 18, 
  60, 60, 23, 60, 27, 16, 18, 39, 
  40, 41, 42, 18, 44, 60, 47, 60, 
  9, 25, 45, 43, 18, 32, 18, 46, 
  60, 32, 34, 36, 14, 33, 35
};


static PARSETAB cprj_ParseTab = {
  &cprj_KfgHead, 59, cprj_KfgProds,
  {
    135, cprj_MstShifts, 202, cprj_DtlShifts,
    17, cprj_GoTos, 123, cprj_GoToDfts,
    135, cprj_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_cprj()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&cprj_ParseTab) );
}
