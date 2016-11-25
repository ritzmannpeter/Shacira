/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [otab.c]                 Type: Operational Table                         */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "prim.h"      /* for primitive types */

/*I--------------------- Types -------------------------------------------- */

/*!!
   This module implements a dynamic array as operational table data type.
   The internal element vector will be automatically resized on element 
   insertion and disposal.
*/


AbstractType(OT_Tab);  /* Abstract operational table type */
AbstractType(OT_Obj);  /* Abstract table element type     */
AbstractType(OT_Objs); /* Abstract element vector type    */

/*DOC_INTERFACE*/
#define ROW(type)      OT_Tab

typedef StdCPtr OtObj;          /* Implementation Type: Table Entry  */
typedef INT OtIdx;              /* Implementation Type: Table Index  */
typedef OtObj __HUGE* OtObjVec; /* Implementation Type: Table Vector */

typedef struct _OTAB {
/* Implementation Type: Operational Table */
  OT_Obj (*copy)(OT_Obj obj);
  void (*del)(OT_Obj obj);
  bool (*equal)(OT_Obj lobj, OT_Obj robj);
  INT size;
  INT cnt;
  OtObjVec objects;
} OTAB;

#define OVEC__ELEMENT(vec,idx) ( (vec)[idx] )
#define OT__IMP(tab)           ( (OTAB*)(tab) )
#define OT__COPY(tab)          ( (OT__IMP(tab))->copy )
#define OT__DELETE(tab)        ( (OT__IMP(tab))->del )
#define OT__EQUAL(tab)         ( (OT__IMP(tab))->equal )
#define OT__CNT(tab)           ( (OT__IMP(tab))->cnt )
#define OT__SIZE(tab)          ( (OT__IMP(tab))->size )
#define OT__OBJECTS(tab)       ( (OT__IMP(tab))->objects )
#define OT__OBJECT(tab,idx)    ( (OT__IMP(tab))->objects[idx] )

#define BUG_OT__NEG(cnt)       BUG_VMIN( (cnt), -1 )
#define BUG_OT__FIDX(tab,idx)  BUG_RNG0( (idx), OT__CNT(tab) )
#define BUG_OT__IIDX(tab,idx)  BUG_VRNG( (idx), -1, OT__CNT(tab) )
#define BUG_OT__OBSZ(sz)       BUG_VMIN( (sz), 0 )
#define BUG_OT__IPOS(nth)      BUG_VMIN( (nth), 0 )
#define BUG_OT__ACNT(cnt)      BUG_VMIN( (cnt), 2 )
#define BUG_OT__TCNT(lft,rgt)  BUG_VEQU( (lft), (rgt) )
#define BUG_OT__TTYP(lft,rgt)  BUG_VEQU( OT__COPY(lft), OT__COPY(rgt) );     \
                               BUG_VEQU( OT__DELETE(lft), OT__DELETE(rgt) ); \
                               BUG_VEQU( OT__EQUAL(lft), OT__EQUAL(rgt) )
#define BUG_OT__FORM(cls,ind)  BUG_VMIN( (cls) + (ind), 1 )

/*I---------------------- Creation and basic access ------------------------- */

static void initTab(OT_Tab tab)
/* initializes tab ( Parameter Check: CALL Function ) */
{
  OT__OBJECTS(tab) = (OtObjVec)NULL;
  OT__SIZE(tab)    = 0;
  OT__CNT(tab)     = 0;
}

OT_Tab OT_create
       (                                         /* function parameter:  */
         OT_Obj (*copy)(OT_Obj obj),             /* copies an element    */
         void (*del)(OT_Obj obj),                /* frees an element     */
         bool (*equal)(OT_Obj lobj, OT_Obj robj) /* equality on elements */
       )
#define OT_CREATE(type,cpy,del,equ)                 \
        OT_create                                   \
        (                                           \
          (OT_Obj (*)(OT_Obj obj))             cpy, \
          (void (*)(OT_Obj obj))               del, \
          (bool (*)(OT_Obj lobj, OT_Obj robj)) equ  \
        )
#define OT_CREATE_ADT(type) OT_CREATE(type,primCopy,primFree,primEqual)
/** creates an operational table */
{ OTAB* tab;

  BUG_NULL(copy); BUG_NULL(del); BUG_NULL(equal);
  tab             = (OTAB*)NewMem(sizeof(OTAB));
  OT__COPY(tab)   = copy;
  OT__DELETE(tab) = del;
  OT__EQUAL(tab)  = equal;
  initTab(tab);
  return( tab );
}

OT_Tab OT_cfill
       (                                          /* function parameter:    */
         OT_Obj (*copy)(OT_Obj obj),              /* copies an element      */
         void (*del)(OT_Obj obj),                 /* frees an element       */
         bool (*equal)(OT_Obj lobj, OT_Obj robj), /* equality on elements   */
         OT_Obj dftval,                           /* default value          */
         INT ntimes                               /* initial element number */
       )
#define OT_CFILL(type,cpy,del,equ,dft,n)            \
        OT_cfill                                    \
        (                                           \
          (OT_Obj (*)(OT_Obj obj))             cpy, \
          (void (*)(OT_Obj obj))               del, \
          (bool (*)(OT_Obj lobj, OT_Obj robj)) equ, \
          (OT_Obj)dft,                              \
          (n)                                       \
        )
#define OT_CFILL_ADT(type,d,n) OT_CFILL(type,primCopy,primFree,primEqual,d,n)
#define OT_INJECT_ADT(type,d) OT_CFILL(type,primCopy,primFree,primEqual,d,1)
/** creates and fills an operational table ntimes with the value 'dftval' */
{ OTAB* tab; INT i;

  BUG_NULL(copy); BUG_NULL(del); BUG_NULL(equal);
  BUG_OT__NEG(ntimes);
  tab              = (OTAB*)NewMem(sizeof(OTAB));
  OT__COPY(tab)    = copy;
  OT__DELETE(tab)  = del;
  OT__EQUAL(tab)   = equal;
  OT__SIZE(tab)    = ntimes;
  OT__CNT(tab)     = ntimes;
  OT__OBJECTS(tab) = ( ntimes ) ?
                     (OtObjVec)NewHMem(ntimes*sizeof(OtObj)) : (OtObjVec)NULL;
  for( i=0; i < ntimes; ++i )
    OT__OBJECT(tab,i) = (OT_Obj)((*OT__COPY(tab))(dftval));
  return( tab );
}

void OT_init(OT_Tab tab)
#define OT_INIT OT_init
/* resets / initializes table 'tab' */
{
  BUG_NULL(tab);
  initTab(tab);
}

INT OT_cnt(OT_Tab tab)
#define OT_CNT OT_cnt
/* number of elements in table 'tab' */
{
  BUG_NULL(tab);
  return( OT__CNT(tab) );
}

/*I------------------------- Insert & Update -------------------------------- */

static void resizeTab(OT_Tab tab)
/* resizes tab ( Parameter Check: CALL Function ) */
{ OtObjVec objects = OT__OBJECTS(tab);

  OT__SIZE(tab)    = ( ! OT__CNT(tab) ) ? 2 : OT__CNT(tab) * 2;
  OT__OBJECTS(tab) = (OtObjVec)NewHMem(OT__SIZE(tab)*sizeof(OtObj));
  if( objects != (OtObjVec)NULL )
  { INT i;

    for( i=0; i < OT__SIZE(tab); ++i )
      OT__OBJECT(tab,i) = ( i < OT__CNT(tab) ) ?
                          OVEC__ELEMENT(objects,i) : (OtObj)NULL;
    FreeHMem( objects );
  }
}

static void moveObjsUp(OT_Tab tab, INT FstIdx)
/* moves entries with index >= FstIdx up ( Parameter Check: CALL Function ) */
{ INT i;

  for( i = OT__CNT(tab) - 1; i >= FstIdx; --i )
    OT__OBJECT(tab,i+1) = OT__OBJECT(tab,i);
  OT__OBJECT(tab,FstIdx) = (OtObj)NULL;
}

static INT insTabObj(OT_Tab tab, OT_Obj obj, INT idx)
/* ( postional ) insert of obj in tab ( Parameter Check: CALL Function ) */
{
  BUG_OT__IIDX(tab,idx);
  if( idx == -1 )                     idx = OT__CNT(tab);
  if( OT__SIZE(tab) == OT__CNT(tab) ) resizeTab(tab);
  if( idx < OT__CNT(tab) )            moveObjsUp(tab,idx);
  OT__OBJECT(tab,idx) = obj;
  ++OT__CNT(tab);
  return( idx );
}

INT OT_t_ins(OT_Tab tab, OT_Obj obj)
#define OT_T_INS(tab,obj) OT_t_ins(tab,(OT_Obj)(obj))
/* inserts 'obj' as last element of table 'tab' 
   result = element index
*/
{
  BUG_NULL(tab);
  return( insTabObj(tab,(OT_Obj)((*OT__COPY(tab))(obj)),-1) );
}

INT OT_p_ins(OT_Tab tab, OT_Obj obj, INT nth)
#define OT_P_INS(tab,obj,nth) OT_p_ins(tab,(OT_Obj)(obj),nth)
/* inserts 'obj' as nth element of table 'tab' ( nth >= 1 )
   result = element index
*/
{
  BUG_NULL(tab);
  BUG_OT__IPOS(nth);
  return( insTabObj(tab,(OT_Obj)((*OT__COPY(tab))(obj)),nth-1) );
}

INT OT_s_ins
    (
      OT_Tab tab,OT_Obj obj,int (*cmp3)(OT_Obj lobj, OT_Obj robj),bool unique
    )
#define OT_S_INS(tab,obj,cmp3)                      \
        OT_s_ins                                    \
        (                                           \
          tab,                                      \
          (OT_Obj)(obj),                            \
          (int (*)(OT_Obj lobj, OT_Obj robj)) cmp3, \
          False                                     \
        )
#define OT_S_INS_U(tab,obj,cmp3)                    \
        OT_s_ins                                    \
        (                                           \
          tab,                                      \
          (OT_Obj)(obj),                            \
          (int (*)(OT_Obj lobj, OT_Obj robj)) cmp3, \
          True                                      \
        )
/* inserts element 'obj' in table 'tab' ( sorted )
   unique --> no insert if the element exists
   result = element index
*/
{ INT left, right, center, res;

  BUG_NULL(tab); BUG_NULL(cmp3);
  if( ! OT__CNT(tab) )
    return( insTabObj(tab,(OT_Obj)((*OT__COPY(tab))(obj)),-1) );
  left  = 0;
  right = OT__CNT(tab);
  while( left < right )
  {
    center = ( left + right ) >> 1; /* <==> / 2 */
    if( (*cmp3)(OT__OBJECT(tab,center),obj) < 0 ) left  = center + 1;
    else                                          right = center;
  }
  if( left == OT__CNT(tab) )
    return( insTabObj(tab,(OT_Obj)((*OT__COPY(tab))(obj)),-1) );
  res = (*cmp3)(OT__OBJECT(tab,left),obj);
  if( ! res )
    return
    ( 
      ( unique ) ? left : insTabObj(tab,(OT_Obj)((*OT__COPY(tab))(obj)),left) 
    );
  else
    return
    ( 
      ( res < 0 )
      ? insTabObj(tab,(OT_Obj)((*OT__COPY(tab))(obj)),left+1)
      : insTabObj(tab,(OT_Obj)((*OT__COPY(tab))(obj)),left) 
    );
}

OT_Obj OT_upd(OT_Tab tab, INT idx, OT_Obj obj)
#define OT_UPD(type,tab,idx,obj) ( (type)OT_upd(tab,(idx),(OT_Obj)(obj)) )
/* updates table element tab[idx] with 'obj' */
{
  BUG_NULL(tab);
  BUG_OT__FIDX(tab,idx);
  (*OT__DELETE(tab))( OT__OBJECT(tab,idx) );
  OT__OBJECT(tab,idx) = (OT_Obj)((*OT__COPY(tab))(obj));
  return( obj );
}

/*I--------------------------- Copy & Append ------------------------------- */

OT_Objs OT_copyV(OT_Tab tab, INT size, StdCPtr (*cfun)(OT_Obj obj))
#define OT_COPY_V(type,tab,sz,fun) \
        ( (type)OT_copyV(tab,(sz),(StdCPtr (*)(OT_Obj obj)) fun) )
/* copies elements of table 'tab' to an array 
   assertion: elements of constant size
*/
{ byte* array = (byte*)NULL; byte* obj; INT idx, i, j;
#ifdef _MSDOS
  assert0(OT__CNT(tab) <= 16000L, "");
#endif
  BUG_NULL(tab); BUG_NULL(cfun);
  BUG_OT__OBSZ(size);
  if( OT__CNT(tab) )
  {
    array = (byte*)NewMem(size*OT__CNT(tab));
    for( i=0, idx=0; i < OT__CNT(tab); ++i, idx = i*size )
    {
      obj = (byte*)((*cfun)(OT__OBJECT(tab,i)));
      for( j=0; j < size; ++j ) array[idx+j] = obj[j];
      FreeMem(obj);
    }
  }
  return( (OT_Objs)array );
}

OT_Tab OT_reverse(OT_Tab tab)
#define OT_REVERSE OT_reverse
/* reverses elements in table 'tab' ( not copied ) */
{ INT i, n; OT_Obj tmp;
  BUG_NULL(tab);
  n = OT__CNT(tab);
  for( i=0; i < n/2; ++i )
  {
    tmp = OT__OBJECT(tab,i);
    OT__OBJECT(tab,i) = OT__OBJECT(tab,n-i-1);
    OT__OBJECT(tab,n-i-1) = tmp;
  }
  return( tab );
}

OT_Tab OT_copy(OT_Tab tab)
#define OT_COPY OT_copy
/* copies table 'tab' */
{ OTAB* res; INT i;
  BUG_NULL(tab);
  res             = (OTAB*)NewMem(sizeof(OTAB));
  OT__COPY(res)   = OT__COPY(tab);
  OT__DELETE(res) = OT__DELETE(tab);
  OT__EQUAL(res)  = OT__EQUAL(tab);
  initTab(res);
  for( i=0; i < OT__CNT(tab); ++i )
    insTabObj(res,(OT_Obj)((*OT__COPY(tab))(OT__OBJECT(tab,i))),-1);
  return( res );
}

OT_Tab OT_append(OT_Tab dst, OT_Tab src)
#define OT_APPEND OT_append
/* appends table 'src' to table 'dst'; 'src' won't be removed */
{ INT cnt, i;
  BUG_NULL(dst); BUG_NULL(src);
  BUG_OT__TTYP(dst,src);
  cnt = OT__CNT(src);
  for( i=0; i < cnt; ++i )
    insTabObj(dst,(OT_Obj)((*OT__COPY(dst))(OT__OBJECT(src,i))),-1);
  return( dst );
}

/*I-------------------------- Get / Sort & Search --------------------------- */

OT_Obj __HUGE* OT_TRICKY_objects(OT_Tab tab)
/* internal element array of table 'tab' ( use with care ! ) */
{
  return (OT_Obj __HUGE*)OT__OBJECTS(tab);
}

OT_Obj OT_get(OT_Tab tab, INT idx)
#define OT_GET(type,tab,idx)       ( (type)OT_get(tab,(idx)) )
#define OT_GET_I(type,t,it,idx)    OT_GET(type,t,OT_GET(INT,it,(idx)))
#define OT_GET_small(type,tab,idx) ( (type)((long)OT_get(tab,(idx))) )
#define OT_GET_short(tab,idx)      ( (short)((long)OT_get(tab,(idx))) )
/* table element tab[idx] */
{
  BUG_NULL(tab);
  BUG_OT__FIDX(tab,idx);
  return( OT__OBJECT(tab,idx) );
}

INT OT_l_find(OT_Tab tab, OT_Obj obj, bool (*cmp)(OT_Obj tobj, OT_Obj obj))
#define OT_L_FIND_EQ(tab,obj)  \
        OT_l_find(tab,(OT_Obj)(obj),(bool (*)(OT_Obj tobj, OT_Obj Obj))NULL)
#define OT_L_FIND(tab,obj,cmp) \
        OT_l_find(tab,(OT_Obj)(obj),(bool (*)(OT_Obj tobj, OT_Obj Obj)) cmp)
/* position of key element 'obj' in table 'tab' or 0 ( linear search ) */
{ bool (*cfun)(OT_Obj tobj, OT_Obj obj); INT i;

  BUG_NULL(tab);
  cfun = ( cmp == (bool (*)(OT_Obj tobj,OT_Obj obj))NULL ) 
         ? OT__EQUAL(tab) : cmp;
  for( i=0; i < OT__CNT(tab); ++i )
    if( (*cfun)(OT__OBJECT(tab,i),obj) ) return( i + 1 );
  return( 0 );
}


static INT OT_lex(INT a, INT b)
{
/*
  return a?a:b;
*/
  if( a != 0 ) return a;
  else         return b;
}

static void sortTab
            (
              OT_Tab tab, OtObjVec idxvec, INT rows,
              int (*cmp3)(OT_Obj lobj, OT_Obj robj)
            )
/* sorts tab according 'quicksort' method ( Parameter Check: CALL Function ) */
{ OT_Obj center; OT_Obj tmp; INT left, right, centeri;

  while( rows > 1 )
  {
    center  = OT__OBJECT(tab,(OtIdx)OVEC__ELEMENT(idxvec,rows / 2));
    centeri = (OtIdx)OVEC__ELEMENT(idxvec,rows / 2);
    left    = 0;
    right   = rows - 1;
    while( left <= right )
    {
      while
      ( 
        OT_lex
        (
          (*cmp3)(OT__OBJECT(tab,(OtIdx)OVEC__ELEMENT(idxvec,left)),center),
          ((OtIdx)OVEC__ELEMENT(idxvec,left))-centeri
        ) < 0 
      ) ++left;
      while
      ( 
        OT_lex
        (
          (*cmp3)(OT__OBJECT(tab,(OtIdx)OVEC__ELEMENT(idxvec,right)),center),
          ((OtIdx)OVEC__ELEMENT(idxvec,right))-centeri
        ) > 0 
      ) --right;
      if( left <= right )
      {
        tmp                         = OVEC__ELEMENT(idxvec,left);
        OVEC__ELEMENT(idxvec,left)  = OVEC__ELEMENT(idxvec,right);
        OVEC__ELEMENT(idxvec,right) = tmp;
        ++left; --right;
      }
    }
    if( left < rows / 2 )
    { 
      sortTab(tab,idxvec,right + 1,cmp3);
      idxvec = OBJ_REF(OVEC__ELEMENT(idxvec,left));
      rows  -= left;
    }
    else
    {
      sortTab(tab,OBJ_REF(OVEC__ELEMENT(idxvec,left)),rows - left,cmp3);
      rows = right + 1;
    }
  }
}

OT_Tab OT_sort(OT_Tab tab, int (*cmp3)(OT_Obj lobj, OT_Obj robj))
#define OT_SORT(tab,cmp3) \
        OT_sort(tab,(int (*)(OT_Obj lobj, OT_Obj robj)) cmp3)
/* sorts table 'tab' ( quicksort method )
   result = index table
*/
{ OT_Tab idxtab; INT i;

  BUG_NULL(tab); BUG_NULL(cmp3);
  idxtab = OT_create(primCopy,primFree,primEqual);
  if( OT__CNT(tab) )
  {
    for( i=0; i < OT__CNT(tab); ++i ) OT_t_ins(idxtab,(OT_Obj)i);
    sortTab(tab,OT__OBJECTS(idxtab),OT__CNT(tab),cmp3);
  }
  return( idxtab );
}

INT OT_b_find
    (
      OT_Tab tab,OT_Tab idxtab,OT_Obj obj,int (*cmp3)(OT_Obj lobj, OT_Obj robj)
    )
#define OT_B_FIND_NI(tab,obj,cmp3)                 \
        OT_b_find                                  \
        (                                          \
          tab,(OT_Tab)NULL,(OT_Obj)(obj),          \
          (int (*)(OT_Obj lobj, OT_Obj robj)) cmp3 \
        )
#define OT_B_FIND(tab,itab,obj,cmp3)                                       \
        OT_b_find                                                          \
        (                                                                  \
          tab,itab,(OT_Obj)(obj),(int (*)(OT_Obj lobj, OT_Obj robj)) cmp3  \
        )
/* position of key element 'obj' in table 'tab' or 0 ( binary search ) 
   Optional the index table 'idxtab' specifies the sort order.
*/
{ INT left, right, center, res;

  BUG_NULL(tab); BUG_NULL(cmp3);
  if( idxtab != (OT_Tab)NULL ) BUG_OT__TCNT(OT__CNT(tab),OT__CNT(idxtab));
  if( ! OT__CNT(tab) ) return( 0 );
  left  = 0;
  right = OT__CNT(tab);
  while( left < right )
  {
    center = ( left + right ) >> 1; /* <==> / 2 */
    res = ( idxtab != (OT_Tab)NULL )
          ? (*cmp3)(OT__OBJECT(tab,(OtIdx)OT__OBJECT(idxtab,center)),obj)
          : (*cmp3)(OT__OBJECT(tab,center),obj);
    if( res < 0 ) left  = center + 1;
    else          right = center;
  }
  if( left == OT__CNT(tab) ) return( 0 );
  res = ( idxtab != (OT_Tab)NULL )
        ? (*cmp3)(OT__OBJECT(tab,(OtIdx)OT__OBJECT(idxtab,left)),obj)
        : (*cmp3)(OT__OBJECT(tab,left),obj);
  return( ( res ) ? 0 : left + 1 );
}

/*I------------------------------ Delete ------------------------------------ */

static void delTabObjs(OT_Tab tab)
/* deletes tab vector and entries ( Parameter Check: CALL Function ) */
{ INT i;

  for( i=0; i < OT__CNT(tab); ++i ) (*OT__DELETE(tab))( OT__OBJECT(tab,i) );
  if( OT__OBJECTS(tab) != (OtObjVec)NULL ) FreeHMem( OT__OBJECTS(tab) );
}

void OT_delH(OT_Tab tab)
#define OT_DEL_H OT_delH
/* removes header of table 'tab' */
{
  BUG_NULL(tab);
  if( OT__OBJECTS(tab) != (OtObjVec)NULL ) FreeHMem( OT__OBJECTS(tab) );
  FreeMem( tab );
}

void OT_delT(OT_Tab tab)
#define OT_DEL_T OT_delT
/* removes table 'tab' */
{
  BUG_NULL(tab);
  delTabObjs(tab);
  FreeMem( tab );
}

static void moveObjsDown(OT_Tab tab, INT FstIdx, INT NrElements)
/* moves entries with index > FstIdx down ( Parameter Check: CALL Function ) */
{ INT i;

  for( i = FstIdx; i < OT__CNT(tab) - NrElements; ++i )
    OT__OBJECT(tab,i) = OT__OBJECT(tab,i+NrElements);
  for (i = OT__CNT(tab)-NrElements; i < OT__CNT(tab); i++)
    OT__OBJECT(tab,i) = (OtObj)NULL;
}

static void compressTab(OT_Tab tab, INT idx, INT cnt)
/* compresses tab, overwrites empty entries */
/* ( Parameter Check: CALL Function )       */
{
  if( idx < OT__CNT(tab) - 1 ) moveObjsDown(tab,idx,cnt);
  OT__CNT(tab) -= cnt;
  if( OT__CNT(tab) <= 0 )
  {
    if( OT__OBJECTS(tab) != (OtObjVec)NULL ) FreeHMem( OT__OBJECTS(tab) );
    OT_init(tab);
  }
  else
  {
    if( OT__SIZE(tab) >= ( OT__CNT(tab) << 2 ) ) resizeTab(tab);
  }
}

void OT_delE(OT_Tab tab, INT idx)
#define OT_DEL_E OT_delE
/* removes table element tab[idx] */
{
  BUG_NULL(tab);
  BUG_OT__FIDX(tab,idx);
  (*OT__DELETE(tab))( OT__OBJECT(tab,idx) );
  compressTab(tab,idx,1);
}

void OT_delES(OT_Tab tab, INT idx, INT cnt)
#define OT_DEL_ES OT_delES
/* removes 'cnt' elements from table 'tab' beginning at index 'idx' */
{ INT i;
  BUG_NULL(tab);
  if (cnt <= 0) return;
  BUG_OT__FIDX(tab,idx);
  BUG_OT__FIDX(tab,idx+cnt-1);
  for (i = 0; i < cnt; i++)
    (*OT__DELETE(tab))( OT__OBJECT(tab,idx+i) );
  compressTab(tab,idx,cnt);
}

void OT_clear(OT_Tab tab)
#define OT_CLEAR OT_clear
/* clears table 'tab'; removes all elements */
{
  BUG_NULL(tab);
  delTabObjs(tab);
  OT_init(tab);
}

/*I----------------------------- Printing ----------------------------------- */

static void printTab
            (
              OT_Tab tab, OT_Tab idxtab,
              void (*pMbr)(OT_Obj), int cols, int indent
            )
/* prints tab ( Parameter Check: CALL Function ) */
{ INT i;

  for( i=0; i < OT__CNT(tab); ++i )
  {
    if( ! ( i % cols ) ) NLIND;
    if( (StdCPtr)idxtab != (StdCPtr)NULL )
      (*pMbr)( OT__OBJECT(tab,(OtIdx)OT__OBJECT(idxtab,i)) );
    else
      (*pMbr)( OT__OBJECT(tab,i) );
    if( i < OT__CNT(tab) - 1 ) fprintf(STDOUT,", ");
  }
}

void OT_print(OT_Tab tab, void (*pMbr)(OT_Obj obj), int cols, int indent)
#define OT_PRINT(tab,pMbr,cols,ind) \
        OT_print(tab,(void (*)(OT_Obj obj)) pMbr,(cols),(ind))
/* prints table 'tab' to stdout ( unsorted ) */
{
  BUG_NULL(tab); BUG_NULL(pMbr);
  BUG_OT__FORM(cols,indent);
  printTab(tab,(StdCPtr)NULL,pMbr,cols,indent);
}

void OT_s_print
     (
       OT_Tab tab, OT_Tab idxtab, void (*pMbr)(OT_Obj obj), int cols, int indent
     )
#define OT_S_PRINT(tab,itab,pMbr,cols,ind) \
        OT_s_print(tab,itab,(void (*)(OT_Obj obj)) pMbr,(cols),(ind))
/* prints table 'tab' to stdout ( sorted ) */
{
  BUG_NULL(tab); BUG_NULL(idxtab); BUG_NULL(pMbr);
  BUG_OT__TCNT(OT__CNT(tab),OT__CNT(idxtab));
  BUG_OT__FORM(cols,indent);
  printTab(tab,idxtab,pMbr,cols,indent);
}

/*I-------------------- Predicates on tables & Mapping ---------------------- */

bool OT_equal(OT_Tab left, OT_Tab right)
#define OT_EQUAL OT_equal
/* left = right ? */
{
  BUG_NULL(left); BUG_NULL(right);
  BUG_OT__TTYP(left,right);
  if( left == right ) return( True );
  if( OT__CNT(left) != OT__CNT(right) ) return( False );
  else
  { INT i;

    for( i=0; i < OT__CNT(left); ++i )
      if( ! (*OT__EQUAL(left))(OT__OBJECT(left,i),OT__OBJECT(right,i)) )
        return( False );
    return( True );
  }
}

StdCPtr OT_map
        (                                         /* function parameter:    */
          int argcnt,                             /* number of arguments    */
          void (*fun)(OT_Obj* objs, StdCPtr any), /* element map function   */
          StdCPtr any,                            /* any additional context */
          OT_Tab tab, ...                         /* operational tables     */
        )
#define OT_MAP_F OT_map
/** executes 'fun' on each element in all tables */
{ va_list args; StdCPtr* arglst; OT_Obj* objs; INT i, j;

  VA_START(args,argcnt); arglst = GetArgLst(args); va_end(args);
  BUG_OT__ACNT(argcnt);
  if( argcnt > 3 ) for( i = 3; i+1 <= argcnt; ++i )
    BUG_OT__TCNT(OT__CNT(arglst[i]),OT__CNT(arglst[i+1]));
  objs = (OT_Obj*)NewMem(sizeof(OT_Obj)*(argcnt-2));
  for( i=0; i < OT__CNT(arglst[3]); ++i )
  {
    for( j = 3; j <= argcnt; ++j ) objs[j-3] = OT__OBJECT(arglst[j],i);
    (*fun)(objs,any);
  }
  FreeMem( objs ); FreeMem(arglst);
  return( any );
}

bool OT_forall
     (                                         /* function parameter:    */
       int argcnt,                             /* number of arguments    */
       bool (*fun)(OT_Obj* objs, StdCPtr any), /* element map function   */
       StdCPtr any,                            /* any additional context */
       OT_Tab tab, ...                         /* operational tables     */
     )
#define OT_FORALL_P OT_forall
/** executes 'fun' on each element in all tables;
*  on false execution stops
*/
{ va_list args; StdCPtr* arglst; OT_Obj* objs; bool flag = True; INT i, j;

  VA_START(args,argcnt); arglst = GetArgLst(args); va_end(args);
  BUG_OT__ACNT(argcnt);
  if( argcnt > 3 ) for( i = 3; i+1 <= argcnt; ++i )
    BUG_OT__TCNT(OT__CNT(arglst[i]),OT__CNT(arglst[i+1]));
  objs = (OT_Obj*)NewMem(sizeof(OT_Obj)*(argcnt-2));
  for( i=0; i < OT__CNT(arglst[3]); ++i )
  {
    for( j = 3; j <= argcnt; ++j ) objs[j-3] = OT__OBJECT(arglst[j],i);
    if( ! (*fun)(objs,any) )
    {
      flag = False; break;
    }
  }
  FreeMem( objs ); FreeMem(arglst);
  return( flag );
}

bool OT_exists
     (                                         /* function parameter:    */
       int argcnt,                             /* number of arguments    */
       bool (*fun)(OT_Obj* objs, StdCPtr any), /* element map function   */
       StdCPtr any,                            /* any additional context */
       OT_Tab tab, ...                         /* operational tables     */
     )
#define OT_EXISTS_P OT_exists
/** executes 'fun' on each element in all tables;
*  on true execution stops
*/
{ va_list args; StdCPtr* arglst; OT_Obj* objs; bool flag = False; INT i, j;

  VA_START(args,argcnt); arglst = GetArgLst(args); va_end(args);
  BUG_OT__ACNT(argcnt);
  if( argcnt > 3 ) for( i = 3; i+1 <= argcnt; ++i )
    BUG_OT__TCNT(OT__CNT(arglst[i]),OT__CNT(arglst[i+1]));
  objs = (OT_Obj*)NewMem(sizeof(OT_Obj)*(argcnt-2));
  for( i=0; i < OT__CNT(arglst[3]); ++i )
  {
    for( j = 3; j <= argcnt; ++j ) objs[j-3] = OT__OBJECT(arglst[j],i);
    if( (*fun)(objs,any) )
    {
      flag = True; break;
    }
  }
  FreeMem( objs ); FreeMem(arglst);
  return( flag );
}

/*I------------------- Simulation of a pointer stack ------------------------ */

/*DOC_INTERFACE*/
#define OT_NEWSTK(stk)                  stk = OT_CREATE_ADT(StdCPtr)
#define OT_EMPTYSTK(stk)                ( OT_CNT(stk) ? False : True )
#define OT_CNTSTK(stk)                  OT_CNT(stk)
#define OT_PUSH(ptr,stk)                OT_T_INS(stk,(OT_Obj)(ptr))
#define OT_POP(stk)                     OT_DEL_E(stk,OT_cnt(stk)-1)
#define OT_TOP(type,stk)                OT_GET(type,stk,OT_cnt(stk)-1)
#define OT_DELSTK(stk)                  OT_DEL_T(stk)
