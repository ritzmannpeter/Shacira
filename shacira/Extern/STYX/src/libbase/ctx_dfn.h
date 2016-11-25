/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ctx_dfn.h]                  Type: Program Context                       */
/*                                                                          */
/* Copyright (c) 1993 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef CTX_DFN_INCL
#define CTX_DFN_INCL

#include "standard.h"

AbstractType( CTX_T ); /* Abstract program context type */

/* --------------- Category of context variables --------------------------- */

#define CTX_ARG      1
#define CTX_OPT      2
#define CTX_ENV      3

/* --------------- Types of context variables ------------------------------ */

#define CTX_FLAG     1
#define CTX_INT      2
#define CTX_PATH     3
#define CTX_STRING   4
#define CTX_NAME     5

#define CTX_VARG     "vargs"

#endif //_INCL
