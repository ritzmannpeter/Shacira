/* [hpat_pim.c] Parser table for 'hpat'  */



#include "prs.h"

#include "prs_imp.h"


static string hpat_SNames[] = {
  "PatBgn", "PatEnd", "PatRef", "_other_", "HPatDoc", 
  "Contents", "Content"
};

static int hpat_StartIds[] = {
  4
};

static int hpat_TokKind[] = {
  1, 1, 1, 1
};

static int hpat_NtClass[] = {
  0, 1, 2
};

static c_bool hpat_ErrorNt[] = {
  0, 0, 0
};

static KFGHEAD hpat_KfgHead = {
  "hpat",
  4, 3, hpat_SNames,
  1, hpat_StartIds,
  hpat_TokKind,
  hpat_NtClass,
  hpat_ErrorNt
};

static int hpat_PSymbols[] = {
  5,
  6, 5,
  2,
  3,
  0, 5, 1,
  4
};

static int hpat_PSymFrms[] = {
  0,
  0, 8,
  0,
  0,
  0, 7, 16,
  0
};

static KFGPROD hpat_KfgProds[] = {
  { "dfn", 0, 4, 1, &hpat_PSymbols[0], &hpat_PSymFrms[0] },
  { "nil", 0, 5, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 5, 2, &hpat_PSymbols[1], &hpat_PSymFrms[1] },
  { "ref", 0, 6, 1, &hpat_PSymbols[3], &hpat_PSymFrms[3] },
  { "else", 0, 6, 1, &hpat_PSymbols[4], &hpat_PSymFrms[4] },
  { "pat", 0, 6, 3, &hpat_PSymbols[5], &hpat_PSymFrms[5] },
  { "Start_HPatDoc", 0, 7, 1, &hpat_PSymbols[8], &hpat_PSymFrms[8] }
};

static int hpat_MstShifts[] = {
  3, 3, -1, -1, -1, -1, 3, 7, 
  -1, -1
};

static int hpat_DtlShifts[] = {
  -2, -3, -4, 3, 2, 0, -10, 1
};

static int hpat_GoTos[] = {
  0, 2, 8
};

static int hpat_GoToDfts[] = {
  15, -1, 16, 1, 18, 2, 19, 7, 
  17, -1, -2, -7
};

static int hpat_ActDfts[] = {
  2, 2, 4, 5, 9, 1, 2, 8, 
  3, 6
};


static PARSETAB hpat_ParseTab = {
  &hpat_KfgHead, 7, hpat_KfgProds,
  {
    10, hpat_MstShifts, 8, hpat_DtlShifts,
    3, hpat_GoTos, 12, hpat_GoToDfts,
    10, hpat_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_hpat()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&hpat_ParseTab) );
}
