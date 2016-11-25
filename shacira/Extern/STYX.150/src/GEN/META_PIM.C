/* [meta_pim.c] Parser table for 'meta'  */



#include "prs.h"

#include "prs_imp.h"


static string meta_SNames[] = {
  "Ide", "Opr", "Comment", ":", "text", 
  "(", ")", "Source", "Parts", "Typ", 
  "Elm", "XParts"
};

static int meta_StartIds[] = {
  7
};

static int meta_TokKind[] = {
  1, 1, 5, 2, 2, 2, 2
};

static int meta_NtClass[] = {
  0, 1, 2, 3, 1
};

static c_bool meta_ErrorNt[] = {
  0, 0, 0, 0, 0
};

static KFGHEAD meta_KfgHead = {
  "meta",
  7, 5, meta_SNames,
  1, meta_StartIds,
  meta_TokKind,
  meta_NtClass,
  meta_ErrorNt
};

static int meta_PSymbols[] = {
  8,
  10, 8,
  3, 0,
  4,
  0, 9, 11,
  5, 8, 6,
  7
};

static int meta_PSymFrms[] = {
  0,
  0, 4,
  0, 4,
  0,
  0, 4, 8,
  0, 4, 10,
  0
};

static KFGPROD meta_KfgProds[] = {
  { "dfn", 0, 7, 1, &meta_PSymbols[0], &meta_PSymFrms[0] },
  { "nil", 0, 8, 0, (int*)NULL, (int*)NULL },
  { "cons", 0, 8, 2, &meta_PSymbols[1], &meta_PSymFrms[1] },
  { "nul", 0, 9, 0, (int*)NULL, (int*)NULL },
  { "dfn", 0, 9, 2, &meta_PSymbols[3], &meta_PSymFrms[3] },
  { "txt", 0, 10, 1, &meta_PSymbols[5], &meta_PSymFrms[5] },
  { "grp", 0, 10, 3, &meta_PSymbols[6], &meta_PSymFrms[6] },
  { "nil", 0, 11, 0, (int*)NULL, (int*)NULL },
  { "ign0", 0, 11, 3, &meta_PSymbols[9], &meta_PSymFrms[9] },
  { "Start_Source", 0, 12, 1, &meta_PSymbols[12], &meta_PSymFrms[12] }
};

static int meta_MstShifts[] = {
  2, 5, -1, -1, -1, 2, 7, 9, 
  -1, -1, 2, -1, 11, -1
};

static int meta_DtlShifts[] = {
  -2, -3, 4, 0, -7, 3, -10, 0, 
  -11, 5, -14, 6
};

static int meta_GoTos[] = {
  0, 2, 8, 10, 14
};

static int meta_GoToDfts[] = {
  18, -1, 19, 1, 23, 6, 27, 11, 
  22, -2, 20, -1, -6, -11, 26, -8
};

static int meta_ActDfts[] = {
  2, 4, 6, 12, 1, 2, 11, 8, 
  3, 5, 2, 7, 11, 9
};


static PARSETAB meta_ParseTab = {
  &meta_KfgHead, 10, meta_KfgProds,
  {
    14, meta_MstShifts, 12, meta_DtlShifts,
    5, meta_GoTos, 16, meta_GoToDfts,
    14, meta_ActDfts, 0, (int*)NULL
  }
};

PLR_Tab PLR_get_meta()
/* simulates a PLR_getTab */
{
  return( PLR_copyTab(&meta_ParseTab) );
}
