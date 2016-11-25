/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [term.c]                       Type: Term                                */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "otab.h"

/*I------------------------ Types and Constants ----------------------------- */

/*INTERFACE*/
/* Most of the Functions assume, that the Term Parameter has a */
/* unique Root Node, which has no 'next'-Node.                 */

AbstractType(DT_Term); /* Abstract Term         Type */
AbstractType(DT_Mode); /* Abstract TermType     Type */
AbstractType(DT_Val);  /* Abstract TermValue    Type */
AbstractType(DT_Pos);  /* Abstract TermPosition Type */
AbstractType(DT_Itr);  /* Abstract TermIterator Type */

typedef union _TERMVAL {
/* Term Value */
  DT_Val val;          /* Value                         */
  struct _TERM* parts; /* Sub Derivation Tree ( Term )  */
} TERMVAL;

typedef struct _TERM {
/* Derivation Tree ( Term ) */
  bool isTerm;         /* Term has Subterm              */
  DT_Mode mode;        /* Term Type/Id                  */
  struct _TERM* next;  /* Next Derivation Tree ( Term ) */
  DT_Pos pos;          /* Term Value Position           */
  TERMVAL tval;        /* Term Value                    */
} TERM;

typedef struct _TITER {
/* Term Iterator */
  short state;         /* Status: DT_PRAE, DT_POST      */
  OT_Tab stack;        /* Term Stack - Traversal        */
} TITER;
                                                                         
#define DT_T_IMP(t)       ( (TERM*)(t) )
#define DT_I_IMP(i)       ( (TITER*)(i) )

#define DT_BUG_VAL(t)     ( BUG_VEQU(DT_T_IMP(t)->isTerm,False) )
#define DT_BUG_TERM(t)    ( BUG_VEQU(DT_T_IMP(t)->isTerm,True) )
#define DT_BUG_SUB(t,n,f) ( BUG_VRNG(n,1,DT_cntST(t,f)) )
#define DT_BUG_ITER(i)    ( BUG_VEQU(DT_I_IMP(i)->state,DT_PRAE) )

/*I----------------------- Construct and Delete ----------------------------- */

/*INTERFACE*/
/* without New & Copy */

static TERM* createNode
             (
               bool isTerm, DT_Mode mode, TERM* term, DT_Val value, DT_Pos pos
             )
/* creates term node ( value term or term with subterm ) */
{ TERM* t;

  BUG_NULL(mode);
  t = (TERM*)NewMem(sizeof(TERM));
  t->isTerm = isTerm;
  t->mode = mode;
  t->next = (TERM*)NULL;
  t->pos = pos;
  if( isTerm ) t->tval.parts = term;
  else         t->tval.val   = value;
  return( t );
}

DT_Term DT_createV(DT_Mode mode, DT_Val value, DT_Pos pos)
/* creates value term */
{
  BUG_NULL(value);
  return( createNode(False,mode,(TERM*)NULL,value,pos) );
}

DT_Term DT_createT(DT_Mode mode, DT_Term term, DT_Pos pos)
/* creates term with subterm */
{
  return( createNode(True,mode,DT_T_IMP(term),(DT_Val)NULL,pos) );
}

DT_Pos DT_updPos(DT_Term term, DT_Pos pos)
/* updates position, returns old position */
{ DT_Pos old;

  BUG_NULL(term);
  old = DT_T_IMP(term)->pos;
  DT_T_IMP(term)->pos = pos;
  return( old );
}

DT_Term DT_consT(DT_Term left, DT_Term right)
/* concats left and right */
{
  BUG_NULL(left);
  DT_T_IMP(left)->next = DT_T_IMP(right);
  return( left );
}
                                                            
void DT_delT(DT_Term term, void (*del_term)(DT_Term term))
/* deletes term ( del_term only deletes term attributes ) */
{
  if( term != (DT_Term)NULL ) 
  {
    if( DT_T_IMP(term)->isTerm )
    { TERM* ts;

      for( ts = DT_T_IMP(term)->tval.parts; ts != (TERM*)NULL; )
      { TERM* tn;

        /* tn = ts->next, da nach Loeschen ts nicht mehr vorhanden ist. */
        tn = ts->next; DT_delT(ts,del_term); ts = tn;
      }
    }
    if( (StdCPtr)del_term != (StdCPtr)NULL ) (*del_term)(term);
    FreeMem( term );
  }
}

/*I----------------------- Access / Information ----------------------------- */

bool DT_isTerm(DT_Term term)
/* term has subterm ? */
{
  BUG_NULL(term);
  return( DT_T_IMP(term)->isTerm );
}

DT_Mode DT_mode(DT_Term term)
/* term type ( mode ) */
{
  BUG_NULL(term);
  return( DT_T_IMP(term)->mode );
}

DT_Val DT_val(DT_Term term)
/* term value ( ! DT_isTerm(term) ) */
{
  BUG_NULL(term);
  DT_BUG_VAL(term);
  return( DT_T_IMP(term)->tval.val );
}

DT_Pos DT_pos(DT_Term term)
/* term value position */
{
  BUG_NULL(term);
  return( DT_T_IMP(term)->pos );
}

DT_Term DT_next(DT_Term term)
/* next ( right ) term */
{
  BUG_NULL(term);
  return( DT_T_IMP(term)->next );
}

DT_Term DT_parts(DT_Term term)
/* left subterm ( DT_isTerm(term) ) */
{
  BUG_NULL(term);
  DT_BUG_TERM(term);
  return( DT_T_IMP(term)->tval.parts );
}

/*I----------------------------- Get and Search ----------------------------- */

int DT_cntST(DT_Term term, bool (*filter)(DT_Term term))
/* number of subterms t with filter(t) = False */
{ TERM* ts; int cnt = 0;

  BUG_NULL(term);
  DT_BUG_TERM(term);
  for( ts = DT_T_IMP(term)->tval.parts; ts != (TERM*)NULL; ts = ts->next )
    if( filter == NULL || ! (*filter)(ts) ) ++cnt;
  return( cnt );
}

DT_Term DT_nthST(DT_Term term, int nth, bool (*filter)(DT_Term term))
/* nth subterm t with filter(t) = False [1..DT_cntST(term)] */
{ TERM* ts; int cnt = 1;

  DT_BUG_SUB(term,nth,filter);
  for( ts = DT_T_IMP(term)->tval.parts; ts != (TERM*)NULL; ts = ts->next )
  {
    if( filter == NULL || ! (*filter)(ts) )
    {
      if( cnt == nth ) return( ts );
      ++cnt;
    }
  }
  BUG; return( (DT_Term)NULL );
}

DT_Term DT_r_findT
        (
          DT_Term term, bool (*pred)(DT_Term term, StdCPtr any), StdCPtr any
        )
/* subterm t with (*pred)(t,any) = True ( recursive ) */
{
  if( DT_T_IMP(term) != (TERM*)NULL )
  {
    if( (*pred)(term,any) ) return( DT_T_IMP(term) );
    else 
    {
      if( DT_T_IMP(term)->isTerm )
      { TERM* ts; TERM* rt;

        for( ts = DT_T_IMP(term)->tval.parts; ts != (TERM*)NULL; ts = ts->next )
	  if( ( rt = (TERM*)DT_r_findT(ts,pred,any) ) != (TERM*)NULL )
	    return( rt ); /* Term gefunden, Abbruch der Suche */
      }
    }
  }
  return( (TERM*)NULL );
}

DT_Term DT_l_findT
        (
          DT_Term term, bool (*pred)(DT_Term term, StdCPtr any), StdCPtr any
        )
/* subterm t with (*pred)(t,any) = True ( not recursive ) */
{
  if( DT_T_IMP(term) != (TERM*)NULL )
  {
    if( (*pred)(term,any) ) return( DT_T_IMP(term) );
    else 
    {
      if( DT_T_IMP(term)->isTerm )
      { TERM* ts;

        for( ts = DT_T_IMP(term)->tval.parts; ts != (TERM*)NULL; ts = ts->next )
          if( (*pred)(ts,any) )
            return( ts ); /* Term gefunden, Abbruch der Suche */
      }
    }
  }
  return( (TERM*)NULL );
}

/*I-------------------------- Term Iterator --------------------------------- */

/*INTERFACE*/
#define DT_ROOT           0
#define DT_PRAE           1
#define DT_POST           2

DT_Itr DT_createIT(DT_Term term)
/* creates term iterator */
{ TITER* it;

  BUG_NULL(term);
  it = (TITER*)NewMem(sizeof(TITER));
  it->state = DT_ROOT;
  OT_NEWSTK(it->stack);
  OT_PUSH(term,it->stack);
  return( it );
}

bool DT_getIT(DT_Itr iter)
/* next term in prae/post order */
{ TERM* t;

  BUG_NULL(iter);
  switch( DT_I_IMP(iter)->state )
  {
    case DT_ROOT:
    {
      DT_I_IMP(iter)->state = DT_PRAE;
      return( OT_TOP(TERM*,DT_I_IMP(iter)->stack) != (TERM*)NULL );
    }
    case DT_PRAE:
    {
      if( DT_isTerm(OT_TOP(TERM*,DT_I_IMP(iter)->stack)) &&
          (t=(TERM*)DT_parts(OT_TOP(TERM*,DT_I_IMP(iter)->stack)))!=(TERM*)NULL)
        OT_PUSH(t,DT_I_IMP(iter)->stack);
      else
        DT_I_IMP(iter)->state = DT_POST;
      return( True );
    }
    case DT_POST:
    {
      if( OT_CNTSTK(DT_I_IMP(iter)->stack) > 1 &&
          (t=(TERM*)DT_next(OT_TOP(TERM*,DT_I_IMP(iter)->stack)))!=(TERM*)NULL)
      {
        DT_I_IMP(iter)->state = DT_PRAE;
        OT_POP(DT_I_IMP(iter)->stack);
        OT_PUSH(t,DT_I_IMP(iter)->stack);
        return( True );
      }
      else
      {
        OT_POP(DT_I_IMP(iter)->stack);
        return( ! OT_EMPTYSTK(DT_I_IMP(iter)->stack) );
      }
    }
    default:
    {
      BUG; return( False );
    }
  }
}

void DT_skipIT(DT_Itr iter)
/* skips subterms */
{
  BUG_NULL(iter);
  DT_BUG_ITER(iter);
  DT_I_IMP(iter)->state = DT_POST;
}

short DT_stateIT(DT_Itr iter)
/* current status ( DT_PRAE / DT_POST ) */
{
  BUG_NULL(iter);
  return( DT_I_IMP(iter)->state );
}

DT_Term DT_termIT(DT_Itr iter)
/* current term */
{
  BUG_NULL(iter);
  return( OT_TOP(TERM*,DT_I_IMP(iter)->stack) );
}

OT_Tab DT_stackIT(DT_Itr iter)
/* current iterator stack */
{
  BUG_NULL(iter);
  return( DT_I_IMP(iter)->stack );
}

void DT_delIT(DT_Itr iter)
/* deletes term iterator */
{
  BUG_NULL(iter);
  OT_DELSTK(DT_I_IMP(iter)->stack);
  FreeMem(iter);
}

/*INTERFACE*/
#define DT_FORALL(it,tr)  for( (it) = DT_createIT(tr); \
                               DT_getIT(it) ? True : ( DT_delIT(it), False ); )
#define DT_BREAK(it)      { DT_delIT(it); break; }

/*I-------------------------- Term Predicates ------------------------------- */

static DT_Term nofilter(DT_Term term)
/* dummy filter for DT_equalT */
{
  return( term );
}

bool DT_equalT
     (
       DT_Term left, DT_Term right,
       bool (*cmpEQ)(DT_Term left, DT_Term right),
       DT_Term (*filter)(DT_Term term)
     )
/* left = right ? */
{ DT_Term (*flt)(DT_Term term) = ( (StdCPtr)filter == (StdCPtr)NULL ) 
                                 ? nofilter : filter;

  if( primEqual(left,right) ) return( True );
  if( left != (DT_Term)NULL && right != (DT_Term)NULL )
  {
    if( (*cmpEQ)(left,right) )
    {
      if( DT_T_IMP(left)->isTerm && DT_T_IMP(right)->isTerm )
      { TERM* tl; TERM* tr;

        for
        ( 
          tl = (TERM*)(*flt)(DT_T_IMP(left)->tval.parts), 
          tr = (TERM*)(*flt)(DT_T_IMP(right)->tval.parts); 
          tl != (TERM*)NULL && tr != (TERM*)NULL; 
          tl = (TERM*)(*flt)(tl->next), tr = (TERM*)(*flt)(tr->next) 
        ) 
	  if( ! DT_equalT(tl,tr,cmpEQ,filter) ) return( False );
        return( primEqual(tl,tr) );
      }
      else return( DT_T_IMP(left)->isTerm == DT_T_IMP(right)->isTerm );
    }
    else return( False );
  }
  else return( primEqual(left,right) );
}

bool DT_subT
     (
       DT_Term left, DT_Term right,
       bool (*cmpEQ)(DT_Term left, DT_Term right),
       DT_Term (*filter)(DT_Term term)
     )
/* left <= right ? */
{ DT_Itr it; bool ret = False;

  BUG_NULL(cmpEQ);
  if( primEqual(left,right) ) return( True );
  if( right == (DT_Term)NULL ) return( False );
  DT_FORALL(it,right)
  {
    if( DT_stateIT(it) == DT_PRAE && (*cmpEQ)(left,DT_termIT(it)) )
    {
      if( DT_equalT(left,DT_termIT(it),cmpEQ,filter) )
      {
        ret = True; DT_BREAK(it);
      }
      else DT_skipIT(it);
    }
  }
  return( ret );
}

/*I---------------------------- Printing ------------------------------------ */

void DT_printT(DT_Term term, void (*pMember)(DT_Term term), int indent)
/* prints term */
{
  fprintf(STDOUT,"\n%*s",indent,"");
  if( DT_T_IMP(term) == (TERM*)NULL ) fprintf(STDOUT,"NULL");
  else 
  {
    fprintf(STDOUT,"["); /* before group */
    (*pMember)(term);
    if( DT_T_IMP(term)->isTerm )
    { TERM* ts;

      for( ts = DT_T_IMP(term)->tval.parts; ts != (TERM*)NULL; ts = ts->next )
        DT_printT(ts,pMember,indent+1);
    } 
    fprintf(STDOUT,"]"); /* after group */
  }
}
