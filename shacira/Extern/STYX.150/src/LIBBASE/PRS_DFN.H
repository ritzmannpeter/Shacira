/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [prs_dfn.h]      LALR(1) parser/generator definitions                      */
/*                                                                            */
/* Copyright (c) 1993 by Doelle, Manns                                        */
/*----------------------------------------------------------------------------*/

#ifndef PRS_DFN_INCL
#define PRS_DFN_INCL

#include "standard.h"
#include "cfg_dfn.h"

AbstractType(PLR_Tab); /* Abstract parse table type */

#define PLR_TOK_Other "_other_" /* parser representation of SCN_TOK_Other */

#define PLR_PRD_DFT  0 /* default   production  */
#define PLR_PRD_REC  1 /* recursive production  */
#define PLR_PRD_GRP  2 /* group     production  */
#define PLR_PRD_NON  3 /* ... end of definition */

#endif //_INCL
