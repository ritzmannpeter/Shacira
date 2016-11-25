/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ctx_app.c]          Current Program Context                             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "ctx_dfn.h"

#include "ctx_imp.h"

/* ------------------------- Globals & Constants -------------------------- */

static CTX_T curr_ctx = (CTX_T)NULL;
static int   varg_idx;

/*I-------------------- current context: Set & Get ------------------------ */

CTX_T CTX_ctx_val(void)
/* the current context */
{
  return curr_ctx;
}

void CTX_ctx_set(CTX_T ctx)
/* make 'ctx' the current context */
{ int cnt;
  BUG_NULL(curr_ctx = ctx);
  cnt = CTX_T_IMP(curr_ctx)->cnt;
  varg_idx = (cnt && strcmp(CTX_T_IMP(curr_ctx)->tbl[cnt-1].ide,CTX_VARG) == 0)
             ? cnt - 1 : ( ! cnt ) ? -1 : cnt;
}

/*I--------------------- current context: Eval ---------------------------- */

/*! The following functions define the program interface to their context variables. 
*/

Abs_T CTX_eval(string Name, bool Index)
#define CTX_EVAL(typ,name)  ((typ)(CTX_eval(name,C_False)))
#define CTX_INDEX(name)     ((long)(CTX_eval(name,C_True)))
/* 'Index'   --> finds index of 'Name' in context; (-1) if missing 
   otherwise --> finds value of 'Name' in context; the program aborts if missing
*/
{ int idx;
  BUG_NULL(curr_ctx);
  for (idx = 0; idx < varg_idx; idx++)
    if (strcmp(CTX_T_IMP(curr_ctx)->tbl[idx].ide,Name) == 0)
      return Index ? (Abs_T)idx : CTX_T_IMP(curr_ctx)->tbl[idx].val;
  bug1(Index, "Kontext-Variable '%s' unbekannt",Name);
  return (Abs_T) -1; /* not found */
}

int CTX_argcnt(void)
/* number of variable arguments */
{ 
  BUG_NULL(curr_ctx);
  if (varg_idx >= 0 && varg_idx < CTX_T_IMP(curr_ctx)->cnt)
    return (int)((Abs_T*)(CTX_T_IMP(curr_ctx)->tbl[varg_idx].val))[0];
  return 0;
}

Abs_T CTX_argval(int idx)
#define CTX_ARGVAL(typ,idx) ((typ)(CTX_argval(idx)))
/* variable argument, indexed by 'idx' */
{ 
  BUG_NULL(curr_ctx);
  if( varg_idx < 0                                                        ||
      varg_idx == CTX_T_IMP(curr_ctx)->cnt                                ||
      idx < 0                                                             || 
      idx >= (int)((StdCPtr*)(CTX_T_IMP(curr_ctx)->tbl[varg_idx].val))[0]  )
  {
    bug(False,"argval(%d) exist nicht",idx); return (Abs_T)NULL;
  }
  return ((Abs_T*)(CTX_T_IMP(curr_ctx)->tbl[varg_idx].val))[1+idx];
}
