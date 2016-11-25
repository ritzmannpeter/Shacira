/* ---------------------------------------------------------------------- */
/*                                                                        */
/* [gls.c]               Generic Language Support                         */
/*                                                                        */
/* Copyright (c) 1994 by Lars D\olle, Heike Manns                         */
/* ---------------------------------------------------------------------- */

#include "standard.h"
#include "ptm.h"

/*!!
   [gls] provides a generic interface for the token and nonterminal lists of
   the abstract derivation trees in the generated grammar-specific interface
   modules ( <Language>_int.c ).
*/

/*I------------------------------ Types ----------------------------------- */

/*INTERFACE*/
#define GLS_Lst(A) GList_T

AbstractType( GLS_Lst(A) ); // Abstract term list type
AbstractType( GLS_Tok );    // Abstract token type

static symbol Nil_sym;
static symbol Cons_sym;
static symbol List_sym;

/*I------------------------------ Init ----------------------------------- */

void GLS_init(void)
/* module initialisation */
{
  Nil_sym  = stringToSymbol("nil");
  Cons_sym = stringToSymbol("cons");
  List_sym = stringToSymbol("GLS_Lst(X)");
}

/*I--------------------------- Normalizer --------------------------------- */

/*!
  <p> <b>... to skip comments, keywords and ignore-nodes </b>
      <br>moved to <a href="ptm.htm">[ptm]</a>
*/
/*DOC_INTERFACE*/
#define XGLS_keycom_Skip XPT_keycom_Skip
#define GLS_keycom_Skip  PT_keycom_Skip
#define GLS_ign_Skip     PT_ign_Skip

/*I-------------------------- Token services ------------------------------ */

PT_Term GLS_Tok_cfg(GLS_Tok x)
/* the embedded lanuage of token 'x' */
{
  return PT_cfg((PT_Term)x);
}

symbol GLS_Tok_symbol(GLS_Tok x)
/* the symbol of token 'x' */
{
  return PT_value((PT_Term)x);
}

string GLS_Tok_string(GLS_Tok x)
/* the string value of token 'x' */
{
  return symbolToString(PT_value((PT_Term)x));
}

bool GLS_Term_Tok(PT_Term x, GLS_Tok *t)
/* Term to token selector */
{
  if (PT_isToken(x))
  {
    if (t != (GLS_Tok)NULL) *t = (GLS_Tok)x; return True;
  }
  return False;
}

/*I--------------------------- List Construction -------------------------- */

PT_Term GLS_Lst_nil_mk(void)
/* nil production */
{ 
  return PT_newNtNode(List_sym,Nil_sym,(PT_Term)NULL);
}

PT_Term GLS_Lst_cons_mk(PT_Term a, PT_Term b)
/* cons production */
{ 
  return PT_newNtNode(List_sym,Cons_sym,PT_consT(a,b));
}

PT_Term XGLS_Lst_nil_mk(void)
/* nil production (xaron) */
{ 
  return XPT_newNtNode(List_sym,Nil_sym,(List(PT_Term))NULL);
}

PT_Term XGLS_Lst_cons_mk(PT_Term a, GLS_Lst(PT_Term) *b)
/* cons production (xaron ALT? Speculate?) */
{ 
  return XPT_newNtNode(List_sym,Cons_sym,XPT_consT(a,b)); // Version VOR Einführung der List Knoten
}

PT_Term X4GLS_Lst_cons_mk(PT_Term a, GLS_Lst(PT_Term) *b)
/* cons production (xaron) */
{ 
  return XPT_newNtNode(List_sym,Cons_sym,cons(a,cons(b,NULL)));
}

/*I--------------------------- List service ------------------------------- */

bool GLS_Term_Lst(PT_Term x, GLS_Lst(PT_Term) *lst)
/* Term to GLS_Lst selector */
{
  if ( PT_isNonTerm(x)
    && ( PT_product(x) == Nil_sym
      || PT_product(x) == Cons_sym ) )
  {
    if (lst != (GLS_Tok)NULL) *lst = (GLS_Lst(PT_Term))x; return True;
  }
  return False;
}

bool GLS_Lst_nil(GLS_Lst(PT_Term) x)
#define GLS_EMPTY(term) ( GLS_Lst_nil((PT_Term)(term)) )
/* nil - selector */
{
  return PT_isNonTerm(x) && PT_product(x) == Nil_sym;
}

bool GLS_Lst_cons(GLS_Lst(PT_Term) x, PT_Term* fst_t, GLS_Lst(PT_Term)* rst_t)
/* cons - selector */
{ 
  if ( !PT_isNonTerm(x) || PT_product(x) != Cons_sym) return False;
  if( ! PT_isXaron(x) )
  {
    x = GLS_keycom_Skip(PT_parts(x));
    if( (StdCPtr)fst_t != (StdCPtr)NULL )
      *fst_t = GLS_ign_Skip(x);
    x = GLS_keycom_Skip(PT_next(x));
    if( (StdCPtr)rst_t != (StdCPtr)NULL )
      *rst_t = GLS_ign_Skip(x);
  }
  else
  { 
    x = XGLS_keycom_Skip(XPT_parts(x));
    if( (StdCPtr)fst_t != (StdCPtr)NULL )
      *fst_t = GLS_ign_Skip(fst(PT_Term,x));
    x = XGLS_keycom_Skip(rst(x));
    if( (StdCPtr)rst_t != (StdCPtr)NULL )
      *rst_t = GLS_ign_Skip(fst(PT_Term,x));
  }
  return True;
}

PT_Term GLS_Lst_first(GLS_Lst(PT_Term) x)
#define GLS_FIRST(type,term) ( (type)GLS_Lst_first((GLS_Lst(PT_Term))(term)) )
/* first element in list 'x' */
{ PT_Term res;
  assert0( GLS_Lst_cons(x,&res,_), "'cons' expected");
  return res;
}

PT_Term GLS_Lst_rest(GLS_Lst(PT_Term) x)
#define GLS_REST(type,term) \
        ( (GLS_Lst(type))GLS_Lst_rest((GLS_Lst(PT_Term))(term)) )
/* remaining elements in list 'x' */
{ PT_Term res;
  assert0( GLS_Lst_cons(x,_,&res), "'cons' expected");
  return res;
}

int GLS_Lst_length(GLS_Lst(PT_Term) x)
#define GLS_LENGTH(term) ( GLS_Lst_length((GLS_Lst(PT_Term))(term)) )
/* length of list 'x' */
{ int i;
  for( i=0; GLS_Lst_cons(x,_,&x); i++);
  return i;
}

PT_Term GLS_Lst_nth(GLS_Lst(PT_Term) x, int nth)
#define GLS_NTH(type,term,nth) ((type)GLS_Lst_nth((GLS_Lst(PT_Term))(term),nth))
/* nth element in list 'x' ( nth >= 1 ) */
{ PT_Term res;
  for( ; GLS_Lst_cons(x,&res,&x); nth-- ) if( nth == 1 ) return res;
  C_BUG; return( (PT_Term)NULL );
}

/*I---------------------- Convenient iterator macros ----------------------- */

/*DOC_INTERFACE_COPY_ON*/
#define GLS_FORALL(it,li)      for( (it) = ((PT_Term)(li));  \
                                   ! GLS_EMPTY(it);          \
                                   it = GLS_REST(PT_Term,it) )

#define GLS_FORALLI(it,li,c)   for( c=0, (it) = ((PT_Term)(li));  \
                                   ! GLS_EMPTY(it);               \
                                   ++c, it = GLS_REST(PT_Term,it) )
/*DOC_INTERFACE_COPY_OFF*/
