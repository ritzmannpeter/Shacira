/* [calc_pim.c] Parser table for 'calc'  */



#include "prs.h"

#include "prs_imp.h"


static string calc_SNames[] = {
  "Tok", "Int", "Wrd", "+", "-", 
  "*", "/", "(", ")", "Command", 
  "Exp", "Exp1", "Exp2"
};

static int calc_StartIds[] = {
  9
};

static int calc_TokKind[] = {
  1, 1, 1, 2, 2, 2, 2, 2, 
  2
};

static int calc_NtClass[] = {
  0, 1, 1, 1
};

static c_bool calc_ErrorNt[] = {
  0, 0, 0, 0
};

static KFGHEAD calc_KfgHead = {
  "calc",
  9, 4, calc_SNames,
  1, calc_StartIds,
  calc_TokKind,
  calc_NtClass,
  calc_ErrorNt
};

static int calc_PSymbols[] = {
  10,
  11,
  10, 3, 11,
  10, 4, 11,
  12,
  11, 5, 12,
  11, 6, 12,
  4, 12,
  7, 10, 8,
  1,
  9
};

static int calc_PSymFrms[] = {
  0,
  0,
  0, 5, 9,
  0, 5, 9,
  0,
  0, 5, 9,
  0, 5, 9,
  0, 4,
  0, 4, 8,
  0,
  0
};

static KFGPROD calc_KfgProds[] = {
  { "exp", 0, 9, 1, &calc_PSymbols[0], &calc_PSymFrms[0] },
  { "non", 0, 9, 0, (int*)NULL, (int*)NULL },
  { "ign0", 0, 10, 1, &calc_PSymbols[1], &calc_PSymFrms[1] },
  { "add", 0, 10, 3, &calc_PSymbols[2], &calc_PSymFrms[2] },
  { "sub", 0, 10, 3, &calc_PSymbols[5], &calc_PSymFrms[5] },
  { "ign0", 0, 11, 1, &calc_PSymbols[8], &calc_PSymFrms[8] },
  { "mlt", 0, 11, 3, &calc_PSymbols[9], &calc_PSymFrms[9] },
  { "div", 0, 11, 3, &calc_PSymbols[12], &calc_PSymFrms[12] },
  { "neg", 0, 12, 2, &calc_PSymbols[15], &calc_PSymFrms[15] },
  { "ign0", 0, 12, 3, &calc_PSymbols[17], &calc_PSymFrms[17] },
  { "int", 0, 12, 1, &calc_PSymbols[20], &calc_PSymFrms[20] },
  { "Start_Command", 0, 13, 1, &calc_PSymbols[21], &calc_PSymFrms[21] }
};

static int calc_MstShifts[] = {
  3, -1, 3, 3, -1, 8, 12, -1, 
  -1, 17, 3, 3, 3, 3, -1, 12, 
  12, -1, -1
};

static int calc_DtlShifts[] = {
  -2, -3, -4, 7, 4, 1, -11, -12, 
  4, 3, -13, -14, 6, 5, -11, -12, 
  -15, 8, 4, 3
};

static int calc_GoTos[] = {
  0, 2, 6, 13
};

static int calc_GoToDfts[] = {
  24, -1, 25, 1, 29, 4, 26, 1, 
  4, 35, 11, 36, 12, 27, 1, 4, 
  11, 12, 28, 3, 37, 13, 38, 14
};

static int calc_ActDfts[] = {
  2, 11, 13, 13, 14, 1, 3, 6, 
  9, 13, 13, 13, 13, 13, 10, 4, 
  5, 7, 8
};


static PARSETAB calc_ParseTab = {
  &calc_KfgHead, 12, calc_KfgProds,
  {
    19, calc_MstShifts, 20, calc_DtlShifts,
    4, calc_GoTos, 24, calc_GoToDfts,
    19, calc_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_calc()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&calc_ParseTab) );
}
