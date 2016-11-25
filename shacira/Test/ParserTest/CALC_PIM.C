/* [calc_pim.c] Parser table for 'calc'  */



#include "prs.h"

#include "prs_imp.h"


static string calc_SNames[] = {
  "Tok", "Int", "Wrd", "end", "+", 
  "-", "*", "/", "(", ")", 
  "Cmd", "Exp", "Exp1", "Exp2"
};

static int calc_StartIds[] = {
  10
};

static int calc_TokKind[] = {
  1, 1, 1, 2, 2, 2, 2, 2, 
  2, 2
};

static int calc_NtClass[] = {
  0, 1, 1, 1
};

static bool calc_ErrorNt[] = {
  0, 0, 0, 0
};

static KFGHEAD calc_KfgHead = {
  "calc",
  10, 4, calc_SNames,
  1, calc_StartIds,
  calc_TokKind,
  calc_NtClass,
  calc_ErrorNt
};

static int calc_PSymbols[] = {
  11,
  3,
  12,
  11, 4, 12,
  11, 5, 12,
  13,
  12, 6, 13,
  12, 7, 13,
  5, 13,
  8, 11, 9,
  1,
  10
};

static int calc_PSymFrms[] = {
  0,
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
  { "exp", 0, 10, 1, &calc_PSymbols[0], &calc_PSymFrms[0] },
  { "end", 0, 10, 1, &calc_PSymbols[1], &calc_PSymFrms[1] },
  { "ign0", 0, 11, 1, &calc_PSymbols[2], &calc_PSymFrms[2] },
  { "add", 0, 11, 3, &calc_PSymbols[3], &calc_PSymFrms[3] },
  { "sub", 0, 11, 3, &calc_PSymbols[6], &calc_PSymFrms[6] },
  { "ign0", 0, 12, 1, &calc_PSymbols[9], &calc_PSymFrms[9] },
  { "mlt", 0, 12, 3, &calc_PSymbols[10], &calc_PSymFrms[10] },
  { "div", 0, 12, 3, &calc_PSymbols[13], &calc_PSymFrms[13] },
  { "neg", 0, 13, 2, &calc_PSymbols[16], &calc_PSymFrms[16] },
  { "ign0", 0, 13, 3, &calc_PSymbols[18], &calc_PSymFrms[18] },
  { "int", 0, 13, 1, &calc_PSymbols[21], &calc_PSymFrms[21] },
  { "Start_Cmd", 0, 14, 1, &calc_PSymbols[22], &calc_PSymFrms[22] }
};

static int calc_MstShifts[] = {
  4, -1, -1, 11, 11, -1, 16, 20, 
  -1, -1, 25, 11, 11, 11, 11, -1, 
  20, 20, -1, -1
};

static int calc_DtlShifts[] = {
  -2, -3, -4, -5, 8, 5, 3, 1, 
  -2, -4, -5, 8, 5, 1, -12, -13, 
  5, 4, -14, -15, 7, 6, -12, -13, 
  -16, 9, 5, 4
};

static int calc_GoTos[] = {
  0, 2, 6, 13
};

static int calc_GoToDfts[] = {
  26, -1, 27, 1, 31, 5, 28, 1, 
  5, 37, 12, 38, 13, 29, 1, 5, 
  12, 13, 30, 4, 39, 14, 40, 15
};

static int calc_ActDfts[] = {
  13, 11, 2, 13, 13, 14, 1, 3, 
  6, 9, 13, 13, 13, 13, 13, 10, 
  4, 5, 7, 8
};


static PARSETAB calc_ParseTab = {
  &calc_KfgHead, 12, calc_KfgProds,
  {
    20, calc_MstShifts, 28, calc_DtlShifts,
    4, calc_GoTos, 24, calc_GoToDfts,
    20, calc_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_calc()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&calc_ParseTab) );
}
