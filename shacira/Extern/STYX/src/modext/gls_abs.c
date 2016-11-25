/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [gls_abs.c]               Generic Language Support                       */
/*                                                                          */
/* Copyright (c) 1994 by Lars D\olle, Heike Manns                           */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "ptm.h"


/*!!
   [gls_abs] provides a generic interface for the token and nonterminal lists
   of the abstract derivation trees ( optimized representation ABS, see [ptm] ) 
   in the generated grammar-specific interface modules ( <Language>_ant.c ).

   Note: This module [gls_abs] can't be linked with the standard module for
         generic language support [gls].
*/

/*I------------------------------ Types ----------------------------------- */

/*INTERFACE*/
#define GLS_Lst(A) GList_T
AbstractHugeType( GLS_Lst(A) ); // Abstract term list type

AbstractHugeType( GLS_Tok );    // Abstract token type

static symbol Nil_sym;
static symbol Cons_sym;

/*I--------------------------- Init --------------------------------------- */

void GLS_init(void)
/* module initialisation */
{
  Nil_sym  = stringToSymbol("nil");
  Cons_sym = stringToSymbol("cons");
}

/*I-------------------------- Token Services ------------------------------ */

symbol GLS_Tok_symbol(GLS_Tok x)
/* the symbol of token 'x' */
{
  assert0( PT_Abs_isToken(x) && !PT_Abs_isCFG(x), "token expected");
  return PT_Abs_value((PT_Abs_Term)x);
}

PT_Abs_Term GLS_Tok_cfg(GLS_Tok x)
/* the embedded language of token 'x' */
{
  assert0( PT_Abs_isCFG(x), "embedded language expected");
  return (PT_Abs_Term)PT_Abs_cfg((PT_Abs_Term)x);
}

string GLS_Tok_string(GLS_Tok x)
/* the string value of token 'x' */
{
  assert0( PT_Abs_isToken(x) && !PT_Abs_isCFG(x), "token expected");
  return symbolToString(PT_Abs_value((PT_Abs_Term)x));
}

bool GLS_Term_Tok(PT_Abs_Term x, GLS_Tok *t)
/* Term to token selector */
{
  if (PT_Abs_isToken(x))
  {
    if (t != (GLS_Tok)NULL) *t = (GLS_Tok)x; return True;
  }
  return False;
}

/*I--------------------------- List Service ------------------------------- */

bool GLS_Term_Lst(PT_Abs_Term x, GLS_Lst(PT_Abs_Term) *lst)
/* Term to GLS_Lst selector */
{
  if ( PT_Abs_isNonTerm(x)
    && ( PT_Abs_product(x) == Nil_sym
      || PT_Abs_product(x) == Cons_sym ) )
  {
    if (lst != (GLS_Tok)NULL) *lst = (GLS_Lst(PT_Abs_Term))x; return True;
  }
  return False;
}

bool GLS_Lst_nil(GLS_Lst(PT_Abs_Term) x)
#define GLS_EMPTY(term) ( GLS_Lst_nil((PT_Abs_Term)(term)) )
/* nil - selector */
{
  return PT_Abs_isNonTerm(x) && PT_Abs_product(x) == Nil_sym;
}

bool GLS_Lst_cons
(
  GLS_Lst(PT_Abs_Term) x, 
  PT_Abs_Term* fst, 
  GLS_Lst(PT_Abs_Term)* rst
)
/* cons - selector */
{ 
  if ( !PT_Abs_isNonTerm(x) || PT_Abs_product(x) != Cons_sym) return False;
  if( (StdCPtr)fst != (StdCPtr)NULL ) *fst = PT_Abs_part(x,0);
  if( (StdCPtr)rst != (StdCPtr)NULL ) *rst = PT_Abs_part(x,1);
  return True;
}

PT_Abs_Term GLS_Lst_first(GLS_Lst(PT_Abs_Term) x)
#define GLS_FIRST(type,term) ( (type)GLS_Lst_first((GLS_Lst(PT_Abs_Term))(term)) )
/* first element in list 'x' */
{ PT_Abs_Term res;
  assert0( GLS_Lst_cons(x,&res,_), "'cons' expected");
  return res;
}

PT_Abs_Term GLS_Lst_rest(GLS_Lst(PT_Abs_Term) x)
#define GLS_REST(type,term) \
        ( (GLS_Lst(type))GLS_Lst_rest((GLS_Lst(PT_Abs_Term))(term)) )
/* remaining elements in list 'x' */
{ PT_Abs_Term res;
  assert0( GLS_Lst_cons(x,_,&res), "'cons' expected");
  return res;
}

int GLS_Lst_length(GLS_Lst(PT_Abs_Term) x)
#define GLS_LENGTH(term) ( GLS_Lst_length((GLS_Lst(PT_Abs_Term))(term)) )
/* length of list 'x' */
{ int i;
  for( i=0; GLS_Lst_cons(x,_,&x); i++);
  return i;
}

PT_Abs_Term GLS_Lst_nth(GLS_Lst(PT_Abs_Term) x, int nth)
#define GLS_NTH(type,term,nth) ((type)GLS_Lst_nth((GLS_Lst(PT_Abs_Term))(term),nth))
/* nth element in list 'x' ( nth >= 1 ) */
{ PT_Abs_Term res;
  for( ; GLS_Lst_cons(x,&res,&x); nth-- ) if( nth == 1 ) return res;
  C_BUG; return( (PT_Abs_Term)NULL );
}

/*I---------------------- Convenient iterator macros ----------------------- */

/*DOC_INTERFACE_COPY_ON*/
#define GLS_FORALL(it,li)      for( (it) = ((PT_Abs_Term)(li));  \
                                   ! GLS_EMPTY(it);          \
                                   it = GLS_REST(PT_Abs_Term,it) )
#define GLS_FORALLI(it,li,c)   for( c=0, (it) = ((PT_Abs_Term)(li));  \
                                   ! GLS_EMPTY(it);               \
                                   ++c, it = GLS_REST(PT_Abs_Term,it) )
/*DOC_INTERFACE_COPY_OFF*/
