/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [list.c]                       Type: List                                */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"


/*I---------------------------- The Type --------------------------------- */

/*!!
   This module implements a functional,i.e. LISP-like list data type.
*/

/*INTERFACE*/
#define List(Abs_T) list

AbstractType(List(Abs_T)); /* Abstract list type */

ConcreteType(List_IMP)
{
  Abs_T       fst;
  List(Abs_T) rst;
};

#define IMP(x) ((List_IMP)(x))


/*I---------------------------- Operations and predicates ---------------- */

bool empty(List(Abs_T) x)
/* whether list 'x' is empty */
{
  return x == (List(Abs_T)) NULL;
}

Abs_T list_fst(List(Abs_T) x)
#define fst(TYPE, LIST) ((TYPE) list_fst(LIST))
/* first member of list 'x' */
{
  assert0(!empty(x),"fst: on empty");
  return IMP(x)->fst;
}

List(Abs_T) rst(List(Abs_T) x)
/* rest of list 'x' */
{
  assert0(!empty(x),"rst: on empty");
  return (Abs_T) IMP(x)->rst;
}

List(Abs_T) cons(Abs_T fst, List(Abs_T) rst)
/* list constructor */
{ List_IMP res = New(List_IMP);
  res->fst = fst;
  res->rst = rst;
  return (List(Abs_T))res;
}

List(Abs_T) *rst_ref(List(Abs_T) x)
/* pointer to rest(x); use with care! */
{
  assert0(!empty(x),"");
  return &IMP(x)->rst;
}

Abs_T *fst_ref(List(Abs_T) x)
/* pointer to first(x); use with care! */
{
  assert0(!empty(x),"");
  return &IMP(x)->fst;
}

int length(List(Abs_T) x)
/* length of list 'x' */
{ int len;
  for (len = 0; !empty(x); x = rst(x)) len += 1;
  return len;
}

void pList(List(Abs_T) x, int Indent, void (*pMember)(Abs_T x))
/* prints list 'x' to stdout */
{ int i;
  fprintf(STDOUT,"[");
  if (Indent >= 0 && !empty(x)) TAB(Indent);
  for (i = 0; !empty(x); x = rst(x), i +=1 )
  {
    (*pMember)(fst(Abs_T,x));
    if (!empty(rst(x)))
      if (Indent >= 0 || (i+1) % 4 == 0)
      { fprintf(STDOUT,","); TAB((Indent>=0?Indent:7)); }
      else
        fprintf(STDOUT,", ");
      else
        if (Indent >= 0) TAB(Indent);
  }
  fprintf(STDOUT,"]");
}

void pListEx
     (
       List(Abs_T) x, int Indent, 
       void (*pMember)(Abs_T x, StdCPtr any), StdCPtr any
     )
/* prints list 'x' to stdout;
   uses 'any' as member context
*/
{ int i;
  fprintf(STDOUT,"[");
  if (Indent >= 0 && !empty(x)) TAB(Indent);
  for (i = 0; !empty(x); x = rst(x), i +=1 )
  {
    (*pMember)(fst(Abs_T,x),any);
    if (!empty(rst(x)))
      if (Indent >= 0 || (i+1) % 4 == 0)
      { fprintf(STDOUT,","); TAB((Indent>=0?Indent:7)); }
      else
        fprintf(STDOUT,", ");
      else
        if (Indent >= 0) TAB(Indent);
  }
  fprintf(STDOUT,"]");
}

void freeList(List(Abs_T) x, void (*freeMember)(Abs_T x))
/* frees list 'x' */
{
  if (!empty(x))
  { freeList(rst(x),freeMember); (*freeMember)(fst(Abs_T,x)); FreeMem(x); }
}
