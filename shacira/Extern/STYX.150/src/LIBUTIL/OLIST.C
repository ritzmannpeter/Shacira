/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [olist.c]                  Type: Operational List                        */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "prim.h"      /* for primitive types */

/*I------------------------- Types ---------------------------------------- */

/*!!
   This module implements an operational, double linked list data type.
   In distinction from functional lists operational lists consist of
   a header and the double linked elements. 
   Beside element type information the header contains references to the
   first, last and current element.
*/

AbstractType(OL_Lst); /* Abstract operational list type */
AbstractType(OL_Obj); /* Abstract list element type     */

typedef StdCPtr OlObj; /* Implementation Type: List Entry */

typedef struct _OLIST { 
/* Implementation Type: List Node */
    OlObj object;
    struct _OLIST* next;
    struct _OLIST* prev;
} OLIST;                      

typedef struct _LHEAD { 
/* Implementation Type: Operational List */
    OL_Obj (*copy)(OL_Obj obj);
    void (*del)(OL_Obj obj);
    bool (*equal)(OL_Obj lobj, OL_Obj robj);
    OLIST* first;
    OLIST* curr;         
    OLIST* last;         
    INT cnt;
} LHEAD;

#define OL__IMP(lst)           ( (LHEAD*)(lst) )
#define OL__COPY(lst)          ( (OL__IMP(lst))->copy )
#define OL__DELETE(lst)        ( (OL__IMP(lst))->del )
#define OL__EQUAL(lst)         ( (OL__IMP(lst))->equal )
#define OL__CNT(lst)           ( (OL__IMP(lst))->cnt )
#define OL__FIRST(lst)         ( (OL__IMP(lst))->first )
#define OL__CURR(lst)          ( (OL__IMP(lst))->curr )
#define OL__LAST(lst)          ( (OL__IMP(lst))->last )
#define OL__OBJECT(node)       ( (node)->object )
#define OL__NEXT(node)         ( (node)->next )
#define OL__PREV(node)         ( (node)->prev )

#define BUG_OL__NILL(lst)      BUG_VMIN( OL__CNT(lst), 0 )
#define BUG_OL__ACNT(cnt)      BUG_VMIN( (cnt), 2 )
#define BUG_OL__LCNT(lft,rgt)  BUG_VEQU( (lft), (rgt) )
#define BUG_OL__LTYP(lft,rgt)  BUG_VEQU( OL__COPY(lft), OL__COPY(rgt) ); \
                               BUG_VEQU( OL__DELETE(lft), OL__DELETE(rgt) ); \
                               BUG_VEQU( OL__EQUAL(lft), OL__EQUAL(rgt) )
#define BUG_OL__FORM(cls,ind)  BUG_VMIN( (cls) + (ind), 1 )

/*I---------------------- Creation and basic access ------------------------- */

static void initLst(OL_Lst objlist)
/* initializes objlist ( Parameter Check: CALL Function ) */
{
  OL__CNT(objlist)   = 0;
  OL__FIRST(objlist) = (OLIST*)NULL;
  OL__CURR(objlist)  = (OLIST*)NULL;
  OL__LAST(objlist)  = (OLIST*)NULL;
}

OL_Lst OL_create
       (                                         /* function parameter:  */
         OL_Obj (*copy)(OL_Obj obj),             /* copies an element    */
         void (*del)(OL_Obj obj),                /* frees an element     */
         bool (*equal)(OL_Obj lobj, OL_Obj robj) /* equality on elements */
       )
#define OL_CREATE(type,cpy,del,equ)                \
        OL_create                                  \
        (                                          \
          (OL_Obj (*)(OL_Obj obj))           cpy,  \
          (void (*)(OL_Obj obj))             del,  \
          (bool (*)(OL_Obj lobj, OL_Obj robj)) equ \
        )
#define OL_CREATE_ADT(type) OL_CREATE(type,primCopy,primFree,primEqual)
/** creates an operational list */
{ LHEAD* lst;
 
  BUG_NULL(copy); BUG_NULL(del); BUG_NULL(equal);
  lst             = (LHEAD*)NewMem(sizeof(LHEAD));
  OL__COPY(lst)   = copy;
  OL__DELETE(lst) = del;
  OL__EQUAL(lst)  = equal;
  initLst(lst);
  return( lst );
}

void OL_init(OL_Lst objlist)
#define OL_INIT OL_init
/* resets / initializes list 'objlist' */
{
  BUG_NULL(objlist);
  initLst(objlist);
}

INT OL_cnt(OL_Lst objlist)
#define OL_CNT OL_cnt
/* number of elements in list 'objlist' */
{
  BUG_NULL(objlist);
  return( OL__CNT(objlist) );
}

/*I--------------------- List copy as reading cursor ------------------------ */

OL_Lst OL_copyL(OL_Lst dst, OL_Lst src)
#define OL_COPY_L OL_copyL
/* copies list 'src';
   fills list 'dst' with references to elements in 'src' 
*/
{
  BUG_NULL(dst); BUG_NULL(src);
  OL__COPY(dst)   = OL__COPY(src);
  OL__DELETE(dst) = OL__DELETE(src);
  OL__EQUAL(dst)  = OL__EQUAL(src);
  OL__CNT(dst)    = OL__CNT(src);
  OL__FIRST(dst)  = OL__FIRST(src);
  OL__CURR(dst)   = OL__CURR(src);
  OL__LAST(dst)   = OL__LAST(src);
  return( dst );
}

void OL_delC(OL_Lst objlist)
#define OL_DEL_C OL_delC
/* removes list 'objlist' only - without elements */
{
  BUG_NULL(objlist);
  FreeMem( objlist );
}

/*I--------------------------- Get & Search --------------------------------- */

OL_Obj OL_first(OL_Lst objlist) 
#define OL_FIRST(type,lst) ( (type)OL_first(lst) )
/* first element of list 'objlist' */
{ OL_Lst lptr = objlist;

  BUG_NULL(objlist);
  OL__CURR(lptr) = OL__FIRST(lptr);
  if( OL__CNT(objlist) ) return( OL__OBJECT(OL__CURR(lptr)) );
  return( (OL_Obj)NULL );
}

OL_Obj OL_last(OL_Lst objlist) 
#define OL_LAST(type,lst) ( (type)OL_last(lst) )
/* last element of list 'objlist' */
{ OL_Lst lptr = objlist;

  BUG_NULL(objlist);
  OL__CURR(lptr) = OL__LAST(lptr);
  if( OL__CNT(objlist) ) return( OL__OBJECT(OL__CURR(lptr)) );
  return( (OL_Obj)NULL );
}

OL_Obj OL_next(OL_Lst objlist) 
#define OL_NEXT(type,lst) ( (type)OL_next(lst) )
/* next element of list 'objlist' */
{ OL_Lst lptr = objlist;
                      
  BUG_NULL(objlist);
  BUG_OL__NILL(objlist);
  return
  ( 
    ( OL__CURR(lptr) == (OLIST*)NULL ) 
    ? OL__OBJECT( OL__CURR(lptr) = OL__FIRST(lptr) ) 
    : ( ( OL__CURR(lptr) = OL__NEXT(OL__CURR(lptr)) ) != (OLIST*)NULL ) 
      ? OL__OBJECT(OL__CURR(lptr)) : (OL_Obj)NULL 
  );
}

OL_Obj OL_prev(OL_Lst objlist) 
#define OL_PREV(type,lst) ( (type)OL_prev(lst) )
/* previous element of list 'objlist' */
{ OL_Lst lptr = objlist;
                      
  BUG_NULL(objlist);
  BUG_OL__NILL(objlist);
  return
  ( 
    ( OL__CURR(lptr) == (OLIST*)NULL ) 
    ? OL__OBJECT( OL__CURR(lptr) = OL__LAST(lptr) ) 
    : ( ( OL__CURR(lptr) = OL__PREV(OL__CURR(lptr)) ) != (OLIST*)NULL ) 
      ? OL__OBJECT(OL__CURR(lptr)) : (OL_Obj)NULL 
  );
}
                           
OL_Obj OL_curr(OL_Lst objlist)
#define OL_CURR(type,lst) ( (type)OL_curr(lst) )
/* current element of list 'objlist' */
{ OL_Lst lptr = objlist;
                      
  BUG_NULL(objlist);
  return
  ( 
    ( OL__CURR(lptr) != (OLIST*)NULL ) 
    ? OL__OBJECT(OL__CURR(lptr)) : (OL_Obj)NULL 
  );
}

INT OL_find(OL_Lst objlist, OL_Obj obj, bool (*cmp)(OL_Obj lobj, OL_Obj obj))
#define OL_FIND_EQ(lst,obj)  \
        OL_find(lst,(OL_Obj)(obj),(bool (*)(OL_Obj lobj, OL_Obj Obj))NULL)
#define OL_FIND(lst,obj,cmp) \
        OL_find(lst,(OL_Obj)(obj),(bool (*)(OL_Obj lobj, OL_Obj Obj)) cmp)
/* position of key element 'obj' in list 'objlist' or 0 ( linear search ) */
{ bool (*cfun)(OL_Obj lobj, OL_Obj obj); OL_Obj lstobj; INT i;

  BUG_NULL(objlist);
  cfun = ( cmp == (bool (*)(OL_Obj lobj,OL_Obj obj))NULL ) ? 
         OL__EQUAL(objlist) : cmp;
  for( i=0; i < OL__CNT(objlist); ++i )
  {
    lstobj = ( ! i ) ? OL_first(objlist) : OL_next(objlist);
    if( (*cfun)(lstobj,obj) ) return( i+1 );
  }
  return( 0 );
}

/*I--------------------------- Insert & Update ------------------------------ */

static OLIST* createLstNode(OL_Obj newobj)
/* creates list node for newobj */
{ OLIST* nptr;

  nptr             = (OLIST*)NewMem(sizeof(OLIST));
  OL__OBJECT(nptr) = newobj;
  return( nptr );
}

static OL_Obj insHeadObj(OL_Lst objlist, OL_Obj newobj)
/* inserts newobj as first entry in objlist */
{ OLIST* nptr;

  BUG_NULL(objlist);
  nptr           = createLstNode(newobj);
  OL__NEXT(nptr) = OL__FIRST(objlist);
  OL__PREV(nptr) = (OLIST*)NULL;
  if( OL__FIRST(objlist) == (OLIST*)NULL ) OL__LAST(objlist)            = nptr;
  else                                     OL__PREV(OL__FIRST(objlist)) = nptr;
  ++OL__CNT(objlist);
  return( OL__OBJECT( OL__FIRST(objlist) = OL__CURR(objlist) = nptr ) );
}

static OL_Obj insTailObj(OL_Lst objlist, OL_Obj newobj)
/* inserts newobj as last entry in objlist */
{
  BUG_NULL(objlist);
  if( OL__LAST(objlist) != (OLIST*)NULL )
  { OLIST* nptr = createLstNode(newobj);

    OL__NEXT(nptr)    = (OLIST*)NULL;
    OL__PREV(nptr)    = OL__LAST(objlist);
    OL__LAST(objlist) = OL__NEXT(OL__LAST(objlist)) = nptr;
    ++OL__CNT(objlist);
    return( OL__OBJECT(OL__CURR(objlist) = nptr) );
  }
  else
    return( insHeadObj(objlist,newobj) );
}

static OL_Obj insCurrObj(OL_Lst objlist, OL_Obj newobj)
/* inserts newobj before current entry in objlist */
/* ( or as last, if OL__CURR(objlist) == NULL )   */
{
  BUG_NULL(objlist);
  if( OL__CURR(objlist) != (OLIST*)NULL )
  { OLIST* nptr = createLstNode(newobj);

    if( ( OL__PREV(nptr) = OL__PREV(OL__CURR(objlist)) ) != (OLIST*)NULL )
      OL__NEXT(OL__PREV(nptr)) = nptr;
    else
      OL__FIRST(objlist) = nptr;
    OL__NEXT(nptr)              = OL__CURR(objlist);
    OL__PREV(OL__CURR(objlist)) = nptr;
    ++OL__CNT(objlist);
    return( OL__OBJECT(OL__CURR(objlist) = nptr) );
  }
  else
    return( insTailObj(objlist,newobj) );
}

static OL_Obj insSortObj
              (
                OL_Lst objlist, OL_Obj newobj,
                bool (*cmpLE)(OL_Obj obj_a,OL_Obj obj_b)
              )
/* inserts newobj in objlist ( sorted )          */
/* (*cmpLE)(left,right) = True ==> left <= right */
{
  BUG_NULL(objlist); BUG_NULL(cmpLE);
  if( OL__FIRST(objlist) != (OLIST*)NULL )
  { OLIST* lptr = ( OL__CURR(objlist) != (OLIST*)NULL && 
                    (*cmpLE)(OL__OBJECT(OL__CURR(objlist)),newobj) ) ?
                  OL__CURR(objlist) : OL__FIRST(objlist);

    while( lptr != (OLIST*)NULL && (*cmpLE)(OL__OBJECT(lptr),newobj) ) 
      lptr = OL__NEXT(lptr);
    if( lptr == (OLIST*)NULL ) return( insTailObj(objlist,newobj) );
    else
    { OLIST* nptr = createLstNode(newobj);

      if( ( OL__PREV(nptr) = OL__PREV(lptr) ) != (OLIST*)NULL )
        OL__NEXT(OL__PREV(nptr)) = nptr;
      else
        OL__FIRST(objlist) = nptr;
      OL__NEXT(nptr) = lptr;
      OL__PREV(lptr) = nptr;
      ++OL__CNT(objlist);
      return( OL__OBJECT(OL__CURR(objlist) = nptr) );
    }
  }
  else return( insHeadObj(objlist,newobj) );
}

OL_Obj OL_h_ins(OL_Lst objlist, OL_Obj newobj)
#define OL_H_INS(type,lst,obj) ( (type)OL_h_ins(lst,(OL_Obj)(obj)) )
/* inserts 'newobj' as first element in list 'objlist' */
{
  return( insHeadObj(objlist,(*OL__COPY(objlist))(newobj)) );
}

OL_Obj OL_t_ins(OL_Lst objlist, OL_Obj newobj)
#define OL_T_INS(type,lst,obj) ( (type)OL_t_ins(lst,(OL_Obj)(obj)) )
/* inserts 'newobj' as last element in list 'objlist' */
{
  return( insTailObj(objlist,(*OL__COPY(objlist))(newobj)) );
}

OL_Obj OL_c_ins(OL_Lst objlist, OL_Obj newobj)
#define OL_C_INS(type,lst,obj) ( (type)OL_c_ins(lst,(OL_Obj)(obj)) )
/* inserts 'newobj' before current element in list 'objlist' 
   ( or as last element, if 'objlist' is empty )   
*/
{
  return( insCurrObj(objlist,(*OL__COPY(objlist))(newobj)) );
}

OL_Obj OL_s_ins(OL_Lst objlist, OL_Obj newobj,
                bool (*cmpLE)(OL_Obj lobj, OL_Obj newobj))
#define OL_S_INS(type,lst,obj,cmpLE)                                       \
        (                                                                  \
          (type)OL_s_ins                                                   \
          (lst,(OL_Obj)(obj),(bool (*)(OL_Obj lobj, OL_Obj newobj)) cmpLE) \
        )
/* inserts element 'newobj' in list 'objlist' ( sorted ) */
{
  return( insSortObj(objlist,(*OL__COPY(objlist))(newobj),cmpLE) );
}

OL_Obj OL_upd(OL_Lst objlist, OL_Obj newobj)
#define OL_UPD(type,lst,obj) ( (type)OL_upd(lst,(OL_Obj)(obj)) )
/* updates current element in list 'objlist' with 'newobj' */
{
  BUG_NULL(objlist);
  BUG_NULL(OL__CURR(objlist));
  (*OL__DELETE(objlist))(OL__OBJECT(OL__CURR(objlist)));
  OL__OBJECT(OL__CURR(objlist)) = newobj;
  return( newobj );
}

/*I----------------------------- Copy & Append ------------------------------ */

OL_Lst OL_copy(OL_Lst objlist)
#define OL_COPY OL_copy
/* copies list 'objlist' */
{ LHEAD* res; INT i;
  BUG_NULL(objlist);
  res             = (LHEAD*)NewMem(sizeof(LHEAD));
  OL__COPY(res)   = OL__COPY(objlist);
  OL__DELETE(res) = OL__DELETE(objlist);
  OL__EQUAL(res)  = OL__EQUAL(objlist);
  initLst(res);
  for( i=0; i < OL__CNT(objlist); ++i )
    if( ! i ) insTailObj(res,(*OL__COPY(objlist))(OL_first(objlist)));
    else      insTailObj(res,(*OL__COPY(objlist))(OL_next(objlist)));
  return( res );
}

OL_Lst OL_append(OL_Lst dst, OL_Lst src)
#define OL_APPEND OL_append
/* appends list 'src' to list 'dst'; 'src' won't be removed */
{ INT cnt, i;
  BUG_NULL(dst); BUG_NULL(src);
  BUG_OL__LTYP(dst,src);
  cnt = OL__CNT(src);
  for( i=0; i < cnt; ++i )
    if( ! i ) insTailObj(dst,(*OL__COPY(src))(OL_first(src)));
    else      insTailObj(dst,(*OL__COPY(src))(OL_next(src)));
  return( dst );
}

/*I------------------------------ Delete ------------------------------------ */

void OL_clear(OL_Lst objlist)
#define OL_CLEAR OL_clear
/* clears list 'objlist'; removes all elements */
{ OLIST* lptr;

  BUG_NULL(objlist);
  lptr = OL__FIRST(objlist);
  while( lptr != (OLIST*)NULL ) 
  { OLIST* actptr = lptr;

    lptr = OL__NEXT(lptr);
    (*OL__DELETE(objlist))( OL__OBJECT(actptr) );        
    FreeMem( actptr );
  }             
  OL_init(objlist);
}

void OL_delL(OL_Lst objlist)
#define OL_DEL_L OL_delL
/* removes list 'objlist */
{
  OL_clear(objlist);
  FreeMem( objlist );
}

void OL_delE(OL_Lst objlist)
#define OL_DEL_E OL_delE
/* removes current element in list 'objlist' */
{ OLIST* curr;

  BUG_NULL(objlist); BUG_NULL(curr = OL__CURR(objlist));
  (*OL__DELETE(objlist))( OL__OBJECT(curr) );        
  if( OL__PREV(curr) != (OLIST*)NULL )
  {
    OL__NEXT(OL__PREV(curr)) = OL__NEXT(curr);
    if( OL__NEXT(curr) != (OLIST*)NULL )
      OL__CURR(objlist) = OL__PREV(OL__NEXT(curr)) = OL__PREV(curr);
    else OL__LAST(objlist) = OL__CURR(objlist) = OL__PREV(curr);
  }
  else
  {
    if( OL__NEXT(curr) != (OLIST*)NULL )
    {
      OL__PREV(OL__NEXT(curr)) = (OLIST*)NULL;
      OL__FIRST(objlist) = OL__CURR(objlist) = OL__NEXT(curr);
    }
    else OL_init(objlist);
  }
  FreeMem(curr);
  if( OL__CNT(objlist) ) --OL__CNT(objlist);
}

/*I----------------------------- Printing ----------------------------------- */

void OL_print(OL_Lst objlist, void (*pMbr)(OL_Obj obj), int cols, int indent)
#define OL_PRINT(lst,pMbr,cols,ind) \
        OL_print(lst,(void (*)(OL_Obj obj)) pMbr,(cols),(ind))
/* prints list 'objlist' to stdout */
{ INT i;

  BUG_NULL(objlist); BUG_NULL(pMbr);
  BUG_OL__FORM(cols,indent);
  for( i=0; i < OL__CNT(objlist); ++i )
  {
    OL_Obj obj = ( ! i ) ? OL_first(objlist) : OL_next(objlist);
    if( ! ( i % cols ) ) NLIND;
    (*pMbr)(obj);
    if( i < OL__CNT(objlist) - 1 ) fprintf(STDOUT,", ");
  }
}

void OL_print_ex
     (
       OL_Lst objlist, 
       void (*pMbr)(OL_Obj obj,Any_T any,int nl,c_bool last), 
       Any_T any, int cols, int indent
     )
#define OL_PRINT_EX(lst,pMbr,any,cols,ind) \
        OL_print_ex(lst, \
                    (void (*)(OL_Obj o,Any_T any,int nl,c_bool last))pMbr, \
                    (any),(cols),(ind))
/* prints list 'objlist' to stdout */
{ INT i;

  BUG_NULL(objlist); BUG_NULL(pMbr);
  BUG_OL__FORM(cols,indent);
  for( i=0; i < OL__CNT(objlist); ++i )
  {
    OL_Obj obj = ( ! i ) ? OL_first(objlist) : OL_next(objlist);
    (*pMbr)(obj,any,(!(i%cols)?indent:0),!(i < OL__CNT(objlist) - 1));
  }
}

/*I---------------------- Predicates on lists & Mapping --------------------- */

bool OL_equal(OL_Lst left,OL_Lst right)
#define OL_EQUAL OL_equal
/* left = right ? */
{
  BUG_NULL(left); BUG_NULL(right);
  BUG_OL__LTYP(left,right);
  if( left == right ) return( True );
  if( OL__CNT(left) != OL__CNT(right) ) return( False );
  else 
  { INT i;

    for( i=0; i < OL__CNT(left); ++i )
    {
      OL_Obj l = ( ! i ) ? OL_first(left)  : OL_next(left);
      OL_Obj r = ( ! i ) ? OL_first(right) : OL_next(right);

      if( ! (*OL__EQUAL(left))(l,r) ) return( False );
    } 
    return( True );
  }
}

StdCPtr OL_map
        (                                         /* function parameter:    */
          int argcnt,                             /* number of arguments    */
          void (*fun)(OL_Obj* objs, StdCPtr any), /* element map function   */
          StdCPtr any,                            /* any additional context */
          OL_Lst objlist, ...                     /* operational lists      */
        )
#define OL_MAP_F OL_map
/** executes 'fun' on each element in all lists */ 
{ va_list args; StdCPtr* arglst; OL_Obj* objs; INT i, j;
  
  VA_START(args,argcnt); arglst = GetArgLst(args); va_end(args);
  BUG_OL__ACNT(argcnt);
  if( argcnt > 3 ) for( i = 3; i+1 <= argcnt; ++i )
    BUG_OL__LCNT(OL__CNT(arglst[i]),OL__CNT(arglst[i+1]));
  objs = (OL_Obj*)NewMem(sizeof(OL_Obj)*(argcnt-2));
  for( i=0; i < OL__CNT(arglst[3]); ++i )
  {
    for( j = 3; j <= argcnt; ++j )
      objs[j-3] = ( ! i ) ? OL_first(arglst[j]) : OL_next(arglst[j]);
    (*fun)(objs,any);
  }
  FreeMem( objs ); FreeMem(arglst);
  return( any );
}

bool OL_forall
     (                                         /* function parameter:    */
       int argcnt,                             /* number of arguments    */
       bool (*fun)(OL_Obj* objs, StdCPtr any), /* element map function   */
       StdCPtr any,                            /* any additional context */
       OL_Lst objlist, ...                     /* operational lists      */
     )
#define OL_FORALL_P OL_forall
/** executes 'fun' on each element in all lists; 
*   on false execution stops
*/ 
{ va_list args; StdCPtr* arglst; OL_Obj* objs; bool flag = True; INT i, j;
  
  VA_START(args,argcnt); arglst = GetArgLst(args); va_end(args);
  BUG_OL__ACNT(argcnt);
  if( argcnt > 3 ) for( i = 3; i+1 <= argcnt; ++i )
    BUG_OL__LCNT(OL__CNT(arglst[i]),OL__CNT(arglst[i+1]));
  objs = (OL_Obj*)NewMem(sizeof(OL_Obj)*(argcnt-2));
  for( i=0; i < OL__CNT(arglst[3]); ++i )
  {
    for( j = 3; j <= argcnt; ++j )
      objs[j-3] = ( ! i ) ? OL_first(arglst[j]) : OL_next(arglst[j]);
    if( ! (*fun)(objs,any) )
    {
      flag = False; break;
    }
  }
  FreeMem( objs ); FreeMem(arglst);
  return( flag );
}

bool OL_exists
     (                                         /* function parameter:    */
       int argcnt,                             /* number of arguments    */
       bool (*fun)(OL_Obj* objs, StdCPtr any), /* element map function   */
       StdCPtr any,                            /* any additional context */
       OL_Lst objlist, ...                     /* operational lists      */
     )
#define OL_EXISTS_P OL_exists
/** executes 'fun' on each element in all lists; 
*   on true execution stops
*/ 
{ va_list args; StdCPtr* arglst; OL_Obj* objs; bool flag = False; INT i, j;
  
  VA_START(args,argcnt); arglst = GetArgLst(args); va_end(args);
  BUG_OL__ACNT(argcnt);
  if( argcnt > 3 ) for( i = 3; i+1 <= argcnt; ++i )
    BUG_OL__LCNT(OL__CNT(arglst[i]),OL__CNT(arglst[i+1]));
  objs = (OL_Obj*)NewMem(sizeof(OL_Obj)*(argcnt-2));
  for( i=0; i < OL__CNT(arglst[3]); ++i )
  {
    for( j = 3; j <= argcnt; ++j )
      objs[j-3] = ( ! i ) ? OL_first(arglst[j]) : OL_next(arglst[j]);
    if( (*fun)(objs,any) )
    {
      flag = True; break;
    }
  }
  FreeMem( objs ); FreeMem(arglst);
  return( flag );
}
