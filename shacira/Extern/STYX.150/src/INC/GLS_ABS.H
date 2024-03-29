/* ---------------------------------------------------------------------- */
/*                                                                        */
/* [gls_abs.h]               Generic Language Support                     */
/*                                                                        */
/* Copyright (c) 1994 by Lars D\olle, Heike Manns                         */
/* ---------------------------------------------------------------------- */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef gls_abs_INCL
#define gls_abs_INCL


#include "standard.h"
#include "ptm.h"


#ifdef __cplusplus
extern "C" {
#endif


/*  
   [gls_abs] provides a generic interface for the token and nonterminal lists
   of the abstract derivation trees ( optimized representation ABS, see [ptm] )
   in the generated grammar-specific interface modules ( <Language>_ant.c ).

   Note: This module [gls_abs] can't be linked with the standard module for
         generic language support [gls].
*/

/* ------------------------------ Types ----------------------------------- */

#define GLS_Lst(A) GList_T
AbstractHugeType( GLS_Lst(A) ); // Abstract term list type

AbstractHugeType( GLS_Tok );    // Abstract token type

/* --------------------------- Init -------------------------------------- */

void GLS_init(void);                   /* module initialisation             */

/* -------------------------- Token Services ------------------------------ */

symbol   GLS_Tok_symbol(GLS_Tok x);    /* the symbol of token 'x'           */
c_string GLS_Tok_string(GLS_Tok x);    /* the string value of token 'x'     */
c_bool GLS_Term_Tok(PT_Abs_Term x, GLS_Tok *t); /* Term to token selector   */

/* --------------------------- List Service ------------------------------- */

c_bool GLS_Term_Lst(PT_Abs_Term x, GLS_Lst(PT_Abs_Term) *lst)
/* Term to GLS_Lst selector */
;

c_bool GLS_Lst_nil(GLS_Lst(PT_Abs_Term) x)
#define GLS_EMPTY(term) ( GLS_Lst_nil((PT_Abs_Term)(term)) )
/* nil - selector */
;

c_bool GLS_Lst_cons
(
  GLS_Lst(PT_Abs_Term) x,
  PT_Abs_Term* fst,
  GLS_Lst(PT_Abs_Term)* rst
)
/* cons - selector */
;

PT_Abs_Term GLS_Lst_first(GLS_Lst(PT_Abs_Term) x)
#define GLS_FIRST(type,term) ( (type)GLS_Lst_first((GLS_Lst(PT_Abs_Term))(term)) )
/* first element in list 'x' */
;

PT_Abs_Term GLS_Lst_rest(GLS_Lst(PT_Abs_Term) x)
#define GLS_REST(type,term) \
        ( (GLS_Lst(type))GLS_Lst_rest((GLS_Lst(PT_Abs_Term))(term)) )
/* remaining elements in list 'x' */
;

int GLS_Lst_length(GLS_Lst(PT_Abs_Term) x)
#define GLS_LENGTH(term) ( GLS_Lst_length((GLS_Lst(PT_Abs_Term))(term)) )
/* length of list 'x' */
;

PT_Abs_Term GLS_Lst_nth(GLS_Lst(PT_Abs_Term) x, int nth)
#define GLS_NTH(type,term,nth) ((type)GLS_Lst_nth((GLS_Lst(PT_Abs_Term))(term),nth))
/* nth element in list 'x' ( nth >= 1 ) */
;


/* ---------------------- Convenient iterator macros ----------------------- */

#define GLS_FORALL(it,li)      for( (it) = ((PT_Abs_Term)(li));  \
                                   ! GLS_EMPTY(it);          \
                                   it = GLS_REST(PT_Abs_Term,it) )
#define GLS_FORALLI(it,li,c)   for( c=0, (it) = ((PT_Abs_Term)(li));  \
                                   ! GLS_EMPTY(it);               \
                                   ++c, it = GLS_REST(PT_Abs_Term,it) )


#ifdef __cplusplus
}
#endif

#endif
