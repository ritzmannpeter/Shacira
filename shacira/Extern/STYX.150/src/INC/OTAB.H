/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [otab.h]                 Type: Operational Table                         */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef otab_INCL
#define otab_INCL


#include "standard.h"
#include "prim.h"      /* for primitive types */


#ifdef __cplusplus
extern "C" {
#endif


/* --------------------- Types -------------------------------------------- */

/*  
   This module implements a dynamic array as operational table data type.
   The internal element vector will be automatically resized on element
   insertion and disposal.
*/

AbstractType(OT_Tab);  /* Abstract operational table type */
AbstractType(OT_Obj);  /* Abstract table element type     */
AbstractType(OT_Objs); /* Abstract element vector type    */

#define ROW(type)      OT_Tab

/* ---------------------- Creation and basic access ------------------------- */

OT_Tab OT_create
       (                                         /* function parameter:  */
         OT_Obj (*copy)(OT_Obj obj),             /* copies an element    */
         void (*del)(OT_Obj obj),                /* frees an element     */
         c_bool (*equal)(OT_Obj lobj, OT_Obj robj) /* equality on elements */
       )
#define OT_CREATE(type,cpy,del,equ)                 \
        OT_create                                   \
        (                                           \
          (OT_Obj (*)(OT_Obj obj))             cpy, \
          (void (*)(OT_Obj obj))               del, \
          (c_bool (*)(OT_Obj lobj, OT_Obj robj)) equ  \
        )
#define OT_CREATE_ADT(type) OT_CREATE(type,primCopy,primFree,primEqual)
/** creates an operational table */
;

OT_Tab OT_cfill
       (                                          /* function parameter:    */
         OT_Obj (*copy)(OT_Obj obj),              /* copies an element      */
         void (*del)(OT_Obj obj),                 /* frees an element       */
         c_bool (*equal)(OT_Obj lobj, OT_Obj robj), /* equality on elements   */
         OT_Obj dftval,                           /* default value          */
         INT ntimes                               /* initial element number */
       )
#define OT_CFILL(type,cpy,del,equ,dft,n)            \
        OT_cfill                                    \
        (                                           \
          (OT_Obj (*)(OT_Obj obj))             cpy, \
          (void (*)(OT_Obj obj))               del, \
          (c_bool (*)(OT_Obj lobj, OT_Obj robj)) equ, \
          (OT_Obj)dft,                              \
          (n)                                       \
        )
#define OT_CFILL_ADT(type,d,n) OT_CFILL(type,primCopy,primFree,primEqual,d,n)
#define OT_INJECT_ADT(type,d) OT_CFILL(type,primCopy,primFree,primEqual,d,1)
/** creates and fills an operational table ntimes with the value 'dftval' */
;

void OT_init(OT_Tab tab)
#define OT_INIT OT_init
/* resets / initializes table 'tab' */
;

INT OT_cnt(OT_Tab tab)
#define OT_CNT OT_cnt
/* number of elements in table 'tab' */
;


/* ------------------------- Insert & Update -------------------------------- */

INT OT_t_ins(OT_Tab tab, OT_Obj obj)
#define OT_T_INS(tab,obj) OT_t_ins(tab,(OT_Obj)(obj))
/* inserts 'obj' as last element of table 'tab'
   result = element index
*/
;

INT OT_p_ins(OT_Tab tab, OT_Obj obj, INT nth)
#define OT_P_INS(tab,obj,nth) OT_p_ins(tab,(OT_Obj)(obj),nth)
/* inserts 'obj' as nth element of table 'tab' ( nth >= 1 )
   result = element index
*/
;

INT OT_s_ins
    (
      OT_Tab tab,OT_Obj obj,int (*cmp3)(OT_Obj lobj, OT_Obj robj),c_bool unique
    )
#define OT_S_INS(tab,obj,cmp3)                      \
        OT_s_ins                                    \
        (                                           \
          tab,                                      \
          (OT_Obj)(obj),                            \
          (int (*)(OT_Obj lobj, OT_Obj robj)) cmp3, \
          C_False                                     \
        )
#define OT_S_INS_U(tab,obj,cmp3)                    \
        OT_s_ins                                    \
        (                                           \
          tab,                                      \
          (OT_Obj)(obj),                            \
          (int (*)(OT_Obj lobj, OT_Obj robj)) cmp3, \
          C_True                                      \
        )
/* inserts element 'obj' in table 'tab' ( sorted )
   unique --> no insert if the element exists
   result = element index
*/
;

OT_Obj OT_upd(OT_Tab tab, INT idx, OT_Obj obj)
#define OT_UPD(type,tab,idx,obj) ( (type)OT_upd(tab,(idx),(OT_Obj)(obj)) )
/* updates table element tab[idx] with 'obj' */
;


/* --------------------------- Copy & Append ------------------------------- */

OT_Objs OT_copyV(OT_Tab tab, INT size, StdCPtr (*cfun)(OT_Obj obj))
#define OT_COPY_V(type,tab,sz,fun) \
        ( (type)OT_copyV(tab,(sz),(StdCPtr (*)(OT_Obj obj)) fun) )
/* copies elements of table 'tab' to an array
   assertion: elements of constant size
*/
;

OT_Tab OT_reverse(OT_Tab tab)
#define OT_REVERSE OT_reverse
/* reverses elements in table 'tab' ( not copied ) */
;

OT_Tab OT_copy(OT_Tab tab)
#define OT_COPY OT_copy
/* copies table 'tab' */
;

OT_Tab OT_append(OT_Tab dst, OT_Tab src)
#define OT_APPEND OT_append
/* appends table 'src' to table 'dst'; 'src' won't be removed */
;


/* -------------------------- Get / Sort & Search --------------------------- */

OT_Obj __HUGE* OT_TRICKY_objects(OT_Tab tab)
/* internal element array of table 'tab' ( use with care ! ) */
;

OT_Obj OT_get(OT_Tab tab, INT idx)
#define OT_GET(type,tab,idx)       ( (type)OT_get(tab,(idx)) )
#define OT_GET_I(type,t,it,idx)    OT_GET(type,t,OT_GET(INT,it,(idx)))
#define OT_GET_small(type,tab,idx) ( (type)((long)OT_get(tab,(idx))) )
#define OT_GET_short(tab,idx)      ( (short)((long)OT_get(tab,(idx))) )
/* table element tab[idx] */
;

INT OT_l_find(OT_Tab tab, OT_Obj obj, c_bool (*cmp)(OT_Obj tobj, OT_Obj obj))
#define OT_L_FIND_EQ(tab,obj)  \
        OT_l_find(tab,(OT_Obj)(obj),(c_bool (*)(OT_Obj tobj, OT_Obj Obj))NULL)
#define OT_L_FIND(tab,obj,cmp) \
        OT_l_find(tab,(OT_Obj)(obj),(c_bool (*)(OT_Obj tobj, OT_Obj Obj)) cmp)
/* position of key element 'obj' in table 'tab' or 0 ( linear search ) */
;

OT_Tab OT_sort(OT_Tab tab, int (*cmp3)(OT_Obj lobj, OT_Obj robj))
#define OT_SORT(tab,cmp3) \
        OT_sort(tab,(int (*)(OT_Obj lobj, OT_Obj robj)) cmp3)
/* sorts table 'tab' ( quicksort method )
   result = index table
*/
;

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
;


/* ------------------------------ Delete ------------------------------------ */

void OT_delH(OT_Tab tab)
#define OT_DEL_H OT_delH
/* removes header of table 'tab' */
;

void OT_delT(OT_Tab tab)
#define OT_DEL_T OT_delT
/* removes table 'tab' */
;

void OT_delE(OT_Tab tab, INT idx)
#define OT_DEL_E OT_delE
/* removes table element tab[idx] */
;

void OT_delES(OT_Tab tab, INT idx, INT cnt)
#define OT_DEL_ES OT_delES
/* removes 'cnt' elements from table 'tab' beginning at index 'idx' */
;

void OT_clear(OT_Tab tab)
#define OT_CLEAR OT_clear
/* clears table 'tab'; removes all elements */
;


/* ----------------------------- Printing ----------------------------------- */

void OT_print(OT_Tab tab, void (*pMbr)(OT_Obj obj), int cols, int indent)
#define OT_PRINT(tab,pMbr,cols,ind) \
        OT_print(tab,(void (*)(OT_Obj obj)) pMbr,(cols),(ind))
/* prints table 'tab' to stdout ( unsorted ) */
;

void OT_s_print
     (
       OT_Tab tab, OT_Tab idxtab, void (*pMbr)(OT_Obj obj), int cols, int indent
     )
#define OT_S_PRINT(tab,itab,pMbr,cols,ind) \
        OT_s_print(tab,itab,(void (*)(OT_Obj obj)) pMbr,(cols),(ind))
/* prints table 'tab' to stdout ( sorted ) */
;


/* -------------------- Predicates on tables & Mapping ---------------------- */

c_bool OT_equal(OT_Tab left, OT_Tab right)
#define OT_EQUAL OT_equal
/* left = right ? */
;

StdCPtr OT_map
        (                                         /* function parameter:    */
          int argcnt,                             /* number of arguments    */
          void (*fun)(OT_Obj* objs, StdCPtr any), /* element map function   */
          StdCPtr any,                            /* any additional context */
          OT_Tab tab, ...                         /* operational tables     */
        )
#define OT_MAP_F OT_map
/** executes 'fun' on each element in all tables */
;

c_bool OT_forall
     (                                         /* function parameter:    */
       int argcnt,                             /* number of arguments    */
       c_bool (*fun)(OT_Obj* objs, StdCPtr any), /* element map function   */
       StdCPtr any,                            /* any additional context */
       OT_Tab tab, ...                         /* operational tables     */
     )
#define OT_FORALL_P OT_forall
/** executes 'fun' on each element in all tables;
*  on false execution stops
*/
;

c_bool OT_exists
     (                                         /* function parameter:    */
       int argcnt,                             /* number of arguments    */
       c_bool (*fun)(OT_Obj* objs, StdCPtr any), /* element map function   */
       StdCPtr any,                            /* any additional context */
       OT_Tab tab, ...                         /* operational tables     */
     )
#define OT_EXISTS_P OT_exists
/** executes 'fun' on each element in all tables;
*  on true execution stops
*/
;


/* ------------------- Simulation of a pointer stack ------------------------ */

#define OT_NEWSTK(stk)                  stk = OT_CREATE_ADT(StdCPtr)
#define OT_EMPTYSTK(stk)                ( OT_CNT(stk) ? C_False : C_True )
#define OT_CNTSTK(stk)                  OT_CNT(stk)
#define OT_PUSH(ptr,stk)                OT_T_INS(stk,(OT_Obj)(ptr))
#define OT_POP(stk)                     OT_DEL_E(stk,OT_cnt(stk)-1)
#define OT_TOP(type,stk)                OT_GET(type,stk,OT_cnt(stk)-1)
#define OT_DELSTK(stk)                  OT_DEL_T(stk)


#ifdef __cplusplus
}
#endif

#endif
