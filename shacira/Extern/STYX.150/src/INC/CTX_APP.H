/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ctx_app.h]          Current Program Context                             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef ctx_app_INCL
#define ctx_app_INCL


#include "ctx_dfn.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -------------------- current context: Set & Get ------------------------ */

CTX_T CTX_ctx_val(void);               /* the current context               */
void  CTX_ctx_set(CTX_T ctx);          /* make 'ctx' the current context    */

/* --------------------- current context: Eval ---------------------------- */

/*  The following functions define the program interface to their context variables.
*/

Abs_T CTX_eval(c_string Name, c_bool Index)
#define CTX_EVAL(typ,name)  ((typ)(CTX_eval(name,C_False)))
#define CTX_INDEX(name)     ((long)(CTX_eval(name,C_True)))
/* 'Index'   --> finds index of 'Name' in context; (-1) if missing
   otherwise --> finds value of 'Name' in context; the program aborts if missing
*/
;

int CTX_argcnt(void);                  /* number of variable arguments      */

Abs_T CTX_argval(int idx)
#define CTX_ARGVAL(typ,idx) ((typ)(CTX_argval(idx)))
/* variable argument, indexed by 'idx' */
;



#ifdef __cplusplus
}
#endif

#endif
