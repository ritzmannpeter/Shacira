/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ptm.c]                   Type: Parse Tree / Term                        */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "otab.h"
#include "binimg.h"
#include "list.h"
#include "sink.h"

#include "hmap.h"
#include "cfg_dfn.h"
#include "gstream.h"


/*I============================ Parse Tree ================================ */

/*!!
   [ptm] implements the parse i.e. derivation tree as special term data type. 

   Term representation

     Three forms of term representation are supported by the construction functions.

     C: This is an efficient representation which lacks an explicit list node
        for the childs of a nonterminal node.

     Xaron: This is a Lisp-like representation with an explicit list node
            for the childs of a nonterminal node. ( used by the xaron project )

     ABS: This is a special optimized representation of the abstract parse tree only 
          with all keywords and comments discarded. For a traversal of the tree you 
          must use the abstract variant of the generated function interface.

   Definition of the symbol position

     1. Terminal         : Position of the first terminal character
     2. Nonterminal      : Position of the first terminal character if exists
     3. Empty production : Position of the first character of the next terminal
*/

/*D
    Most of the functions assume that the parse tree parameter has an 
    unique root node without a next node.
*/


/*I------------------------ Types ------------------------------------------- */

AbstractType(PT_Term); /* Abstract parse tree type          */
AbstractType(PT_Itr);  /* Abstract parse tree iterator type */

typedef struct _PTERM {
/* Parse Term */
  symbol  pid; /* Production                  */
  symbol  sid; /* Symbol                      */
  short   stp; /* Symboltyp                   */
  symbol  fil; /* Symbol in File              */
  long    row; /* ... in Line                 */
  long    col; /* ... at Column               */
  StdCPtr val; /* Value or Sub Term ( Parts ) */
               /* Xaron: Value                */
  StdCPtr nxt; /* Next Term                   */
               /* Xaron: Sub Term List        */
} PTERM;

typedef struct _PTITER {
/* Parse Term Iterator */
  short         state; /* Status: PT_PRAE, PT_POST */
  OT_Tab        stack; /* Term Stack               */
                       /* Xaron: Term List Stack   */
  List(PT_Term) root;  /* Xaron: Root Term List    */
} PTITER;
                                                                         
#define PT_XARON_TYP      100

#define PT_T_IMP(t)       ( (PTERM*)(t) )
#define PT_I_IMP(i)       ( (PTITER*)(i) )

#define PT_T_TYP(t)       ( PT_T_IMP(t)->stp )

#define PT_M_PID(t)       ( PT_T_IMP(t)->pid )
#define PT_M_SID(t)       ( PT_T_IMP(t)->sid )
#define PT_M_STP(t)       ( PT_T_TYP(t) < 0                   \
                            ? PT_XARON_TYP + PT_T_IMP(t)->stp \
                            : PT_T_IMP(t)->stp                )

#define PT_P_FIL(t)       ( PT_T_IMP(t)->fil )
#define PT_P_ROW(t)       ( PT_T_IMP(t)->row )
#define PT_P_COL(t)       ( PT_T_IMP(t)->col )

#define PT_T_VAL(t)       ( (symbol)PT_T_IMP(t)->val )
#define PT_T_VAL_PTR(t)   ( (symbol*)(&(PT_T_IMP(t)->val)) )
#define PT_T_SUB(t)       ( (PTERM*)PT_T_IMP(t)->val )
#define PT_T_SUB_PTR(t)   ( (PTERM**)(&(PT_T_IMP(t)->val)) )
#define PT_T_PTR_1(t)     ( PT_T_IMP(t)->val )
#define PT_T_NXT(t)       ( (PTERM*)PT_T_IMP(t)->nxt )
#define PT_T_NXT_PTR(t)   ( (PTERM**)(&(PT_T_IMP(t)->nxt)) )
#define PT_T_LST(t)       ( (List(PT_Term))PT_T_IMP(t)->nxt )
#define PT_T_LST_PTR(t)   ( (List(PT_Term)*)(&(PT_T_IMP(t)->nxt)) )
#define PT_T_PTR_2(t)     ( PT_T_IMP(t)->nxt )

#define PT_I_CST(i)       ( PT_I_IMP(i)->state )
#define PT_I_STK(i)       ( PT_I_IMP(i)->stack )
#define PT_I_TOP(i)       ( PT_I_IMP(i)->root  )

#define PT_BUG_TYP(t,b)        BUG_VEQU((PT_T_TYP(t) >= 0),(b))
#define PT_BUG_TYPES(l,r)      BUG_VEQU((PT_T_TYP(l) < 0),(PT_T_TYP(r) < 0))
#define PT_BUG_CFG(t)          BUG_VEQU(CFG_CFG(PT_M_STP(t)),True)
#define PT_BUG_NTM(t)          BUG_VEQU(CFG_NTM(PT_M_STP(t)),True)
#define PT_BUG_TM(t)           BUG_VEQU(CFG_NTM(PT_M_STP(t)),False)
#define PT_BUG_STM(t) \
  BUG_VEQU(CFG_NTM(PT_M_STP(t))||CFG_CFG(PT_M_STP(t)),False)
#define PT_BUG_POS(t)          BUG_VNEQ(PT_P_FIL(t),(symbol)NULL)
#define PT_BUG_CLS(c)          BUG_VEQU(((c) >= 0),True)
#define PT_BUG_SUB(t,n,f)      BUG_VRNG(n,1,PT_cntST(t,f))
#define PT_BUG_SUB_EX(t,n,f,a) BUG_VRNG(n,1,PT_cntST_ex(t,f,a))
#define PT_BUG_ITER(i)         BUG_VEQU(PT_I_CST(i),PT_PRAE)

/*I----------------------- Construction & Disposing ------------------------- */

static PT_Term PT_newNode
               (
                 symbol cfgsym, symbol prdsym, short symcls
               )
/* creates new parse tree/term node */
{ PTERM* PTree = (PTERM*)NewMem(sizeof(PTERM));
  PT_M_PID(PTree) = prdsym; 
  PT_M_SID(PTree) = cfgsym; 
  PT_T_TYP(PTree) = symcls;
  PT_P_FIL(PTree) = (symbol)NULL; 
  PT_P_ROW(PTree) = -1; 
  PT_P_COL(PTree) = -1;
  PT_T_PTR_1(PTree) = (StdCPtr)NULL;
  PT_T_PTR_2(PTree) = (StdCPtr)NULL;
  return( PTree );
}

PT_Term PT_newTNode(symbol cfgsym, short symcls, symbol value)
/* C: creates a node for 
      token 'cfgsym' of type 'symcls' and 'value'
*/
{ PT_Term res;
  BUG_NULL(cfgsym);
  PT_BUG_CLS(symcls);
  res = PT_newNode(cfgsym,(symbol)NULL,symcls);
  PT_T_PTR_1(res) = value;
  return( res );
}

PT_Term XPT_newTNode(symbol cfgsym, short symcls, symbol value)
/* Xaron: creates a node for 
          token 'cfgsym' of type 'symcls' and 'value'
*/
{ PT_Term res;
  BUG_NULL(cfgsym);
  PT_BUG_CLS(symcls);
  res = PT_newNode(cfgsym,(symbol)NULL,(short)(symcls - PT_XARON_TYP));
  PT_T_PTR_1(res) = value;
  return( res );
}

PT_Term PT_newNtNode(symbol cfgsym, symbol prdsym, PT_Term parts)
/* C: creates a node for nonterminal 'cfgsym',
      production 'prdsym' and child nodes 'parts'
*/
{ PT_Term res;
  BUG_NULL(cfgsym); BUG_NULL(prdsym);
  res = PT_newNode(cfgsym,prdsym,PLR_TYP_NTM);
  PT_T_PTR_1(res) = parts;
  return( res );
}

PT_Term XPT_newNtNode(symbol cfgsym, symbol prdsym, List(PT_Term) parts)
/* Xaron: creates a node for nonterminal 'cfgsym',
          production 'prdsym' and child nodes 'parts'
*/
{ PT_Term res;
  BUG_NULL(cfgsym); BUG_NULL(prdsym);
  res = PT_newNode(cfgsym,prdsym,PLR_TYP_NTM - PT_XARON_TYP);
  PT_T_PTR_2(res) = parts;
  return( res );
}

PT_Term PT_updVal(PT_Term PTree, Any_T value)
/* updates token node 'PTree' with 'value'; returns 'PTree' */
{
  BUG_NULL(PTree); 
  PT_BUG_TM(PTree);
  PT_T_PTR_1(PTree) = value;
  return( PTree );
}

PT_Term PT_updPos(PT_Term PTree, symbol file, long row, long col)
/* updates node 'PTree' with the position 'file', 'row' and 'col';
   returns 'PTree'
*/
{ 
  BUG_NULL(PTree); 
/* wg. ptm_pp
  BUG_NULL(file);
*/
  PT_P_FIL(PTree) = file; PT_P_ROW(PTree) = row; PT_P_COL(PTree) = col;
  return( PTree );
}

PT_Term PT_consT(PT_Term left, PT_Term right) 
/* C: child node concatenation:
      child list = cons('left','right') 
*/
{
  BUG_NULL(left); PT_BUG_TYP(left,True);
  *PT_T_NXT_PTR(left) = PT_T_IMP(right);
  return( left );
}

List(PT_Term) XPT_consT(PT_Term left, List(PT_Term) right) 
/* Xaron: child node concatenation:
          child list = cons('left','right') 
*/
{
  BUG_NULL(left); PT_BUG_TYP(left,False);
  return( cons(left,right) );
}

PT_Term PT_copyPos(PT_Term left, PT_Term right)
/* assigns position of node 'right' to node 'left'; 
   returns 'left' 
*/
{ 
  BUG_NULL(left); BUG_NULL(right);
  PT_P_FIL(left) = PT_P_FIL(right); 
  PT_P_ROW(left) = PT_P_ROW(right); 
  PT_P_COL(left) = PT_P_COL(right);
  return( left );
}

PT_Term PT_copyNode(PT_Term PTree)
/* copies node 'PTree' ( without child nodes ) */
{ PTERM* res;
  BUG_NULL(PTree); 
  res = (PTERM*)NewMem(sizeof(PTERM));
  PT_M_PID(res)   = PT_M_PID(PTree); 
  PT_M_SID(res)   = PT_M_SID(PTree); 
  PT_T_TYP(res)   = PT_T_TYP(PTree);
  PT_T_PTR_1(res) = PT_T_PTR_2(res) = (StdCPtr)NULL;
  if( ! CFG_NTM(PT_M_STP(PTree)) ) PT_T_PTR_1(res) = PT_T_PTR_1(PTree);
  return( PT_copyPos(res,PTree) );
}

void PT_delT(PT_Term PTree)
/* removes parse tree / term 'PTree' */
{
  if( PTree != (PT_Term)NULL ) 
  {
    if( CFG_CFG(PT_M_STP(PTree)) )
    {
      PT_delT(PT_T_SUB(PTree));
    }
    else
    if( CFG_NTM(PT_M_STP(PTree)) )
    { 
      if( PT_T_TYP(PTree) >= 0 )
      { PTERM* ts;
        for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; )
        { PTERM* tn;
          /* tn = PT_T_NXT(ts), da nach Loeschen ts nicht mehr vorhanden ist. */
          tn = PT_T_NXT(ts); PT_delT(ts); ts = tn;
        }
      }
      else
      { List(PT_Term) ts;
        for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts))
          PT_delT(fst(PT_Term,ts));
        freeList(PT_T_LST(PTree),primFree);
      }
    }
    FreeMem( PTree );
  }
}

/*I----------------------- Accessing ---------------------------------------- */

/*!
  <p><b>Recognizer</b> 
*/

/* No Parameter Check */

bool PT_isXaron(PT_Term PTree)
/* whether 'PTree' is a Xaron-konform parse tree / term */
{
  return( PT_T_TYP(PTree) < 0 );
}

bool PT_isNonTerm(PT_Term PTree)
/* whether 'PTree' starts with a nonterminal node */
{
  return( CFG_NTM(PT_M_STP(PTree)) );
}

bool PT_isCFG(PT_Term PTree)
/* whether 'PTree' is an embedded language node */
{
  return( CFG_CFG(PT_M_STP(PTree)) );
}

bool PT_isToken(PT_Term PTree)
/* whether 'PTree' is a token node */
{
  return( CFG_TOK(PT_M_STP(PTree)) );
}

bool PT_isKey(PT_Term PTree)
/* whether 'PTree' is a keyword node */
{
  return( CFG_KEY(PT_M_STP(PTree)) );
}

bool PT_isComment(PT_Term PTree)
/* whether 'PTree' is a comment node */
{
  return( CFG_COM(PT_M_STP(PTree)) );
}

bool PT_hasPos(PT_Term PTree)
/* whether node 'PTree' contains position informations */
{
  return( PT_P_FIL(PTree) != (symbol)NULL );
}

/*!
  <p><b>Selection</b> 
*/

symbol PT_product(PT_Term PTree)    
/* production symbol of node 'PTree'; 
   assertion: PT_isNonTerm(PTree) 
*/
{
  return( PT_M_PID(PTree) );
}

symbol PT_symbol(PT_Term PTree)     
/* symbol of node 'PTree' ( NT,T ) */
{
  return( PT_M_SID(PTree) );
}

short PT_symtyp(PT_Term PTree)     
/* symbol type of node 'PTree' ( NT/T, see [cfg_dfn] ) */
{
  return( PT_M_STP(PTree) );
}

symbol PT_value(PT_Term PTree)   
/* token value of node 'PTree'
   assertion: ! PT_isNonTerm(PTree) && ! PT_isCFG(PTree)
*/
{
  PT_BUG_STM(PTree);
  return( PT_T_VAL(PTree) );
}

PT_Term PT_cfg(PT_Term PTree)   
/* embedded language of node 'PTree'
   assertion: PT_isCFG(PTree)
*/
{
  PT_BUG_CFG(PTree);
  return( PT_T_VAL(PTree) );
}

/*INTERFACE_GROUP*/

symbol PT_file(PT_Term PTree)    
/* position - source file of node 'PTree'
   assertion: PT_hasPos(PTree)
*/
{
/* wg. ptm_pp
  PT_BUG_POS(PTree);
*/
  return( PT_P_FIL(PTree) );
}

long PT_row(PT_Term PTree)
/* position - source line of node 'PTree'
   assertion: PT_hasPos(PTree)
*/
{
/* wg. ptm_pp
  PT_BUG_POS(PTree);
*/
  return( PT_P_ROW(PTree) );
}

long PT_col(PT_Term PTree)
/* position - source column of node 'PTree'
   assertion: PT_hasPos(PTree)
*/
{
/* wg. ptm_pp
  PT_BUG_POS(PTree);
*/
  return( PT_P_COL(PTree) );
}

/*INTERFACE_GROUP*/

PT_Term PT_next(PT_Term PTree)
/* C: next node / rest of child list 'PTree' or NULL */
{
  BUG_NULL(PTree);
  PT_BUG_TYP(PTree,True);
  return( PT_T_NXT(PTree) );
}

PT_Term PT_parts(PT_Term PTree)
/* C: child list ( first node ) of node 'PTree'
      assertion: PT_isNonTerm(PTree)
*/
{
  PT_BUG_TYP(PTree,True); PT_BUG_NTM(PTree);
  return( PT_T_SUB(PTree) );
}

List(PT_Term) XPT_parts(PT_Term PTree)
/* Xaron: child list of node 'PTree'
          assertion: PT_isNonTerm(PTree)
*/
{
  PT_BUG_TYP(PTree,False); PT_BUG_NTM(PTree);
  return( PT_T_LST(PTree) );
}

List(PT_Term)* XPT_parts_ref(PT_Term PTree)
/* Xaron: pointer reference to child list of node 'PTree'
          assertion: PT_isNonTerm(PTree)
*/
{
  PT_BUG_TYP(PTree,False); PT_BUG_NTM(PTree);
  return PT_T_LST_PTR(PTree);
}

/*!
  <p><b>Convenience macros for identifying a certain nonterminal, 
  token or production </b>
*/

/*DOC_INTERFACE*/
#define PT_THISNTM(t,s) ( ( PT_isNonTerm(t) && PT_symbol(t)  == (s) ) ? \
                          True : False )
#define PT_THISTOK(t,s) ( ( PT_isToken(t)   && PT_symbol(t)  == (s) ) ? \
                          True : False )
#define PT_THISPRD(t,p) ( ( PT_isNonTerm(t) && PT_product(t) == (p) ) ? \
                          True : False )

/*I----------------------------- Searching ---------------------------------- */

static bool default_filter_ex(PT_Term PTree, Any_T any)
/* (*any)(PTree) ? */
{
  return (*((bool (*)(PT_Term PTree))any))(PTree);
}

int PT_cntST_ex
    (
      PT_Term PTree, bool (*filter)(PT_Term PTree, Any_T any), Any_T any
    )
/* number of nodes t within child list of node 'PTree' 
   sacrifying condition filter(t,any) = False 
*/
{ int cnt = 0;
  BUG_NULL(PTree); PT_BUG_NTM(PTree);
  if( PT_T_TYP(PTree) >= 0 )
  { PTERM* ts;
    for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
      if( filter == NULL || ! (*filter)(ts,any) ) ++cnt;
  }
  else
  { List(PT_Term) ts;
    for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts))
      if( filter == NULL || ! (*filter)(fst(PT_Term,ts),any) ) ++cnt;
  }
  return( cnt );
}

int PT_cntST(PT_Term PTree, bool (*filter)(PT_Term PTree))
/* number of nodes t within child list of node 'PTree' 
   sacrifying condition filter(t) = False 
*/
{ 
  if( filter == NULL )
    return PT_cntST_ex(PTree,NULL,NULL);
  else
    return PT_cntST_ex(PTree,default_filter_ex,filter);
}

PT_Term PT_nthST_ex
        (
          PT_Term PTree, int nth, 
          bool (*filter)(PT_Term PTree, Any_T any), Any_T any
        )
/* 'nth' node t within child list of node 'PTree' 
   sacrifying condition filter(t,any) = False 
   [nth=1..PT_cntST_ex] 
*/
{ int cnt = 1;
  PT_BUG_SUB_EX(PTree,nth,filter,any);
  if( PT_T_TYP(PTree) >= 0 )
  { PTERM* ts;
    for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
    {
      if( filter == NULL || ! (*filter)(ts,any) )
      {
        if( cnt == nth ) return( ts );
        ++cnt;
      }
    }
  }
  else
  { List(PT_Term) ts;
    for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts))
    {
      if( filter == NULL || ! (*filter)(fst(PT_Term,ts),any) )
      {
        if( cnt == nth ) return( fst(PT_Term,ts) );
        ++cnt;
      }
    }
  }
  C_BUG; return( (PT_Term)NULL );
}

PT_Term PT_nthST(PT_Term PTree, int nth, bool (*filter)(PT_Term PTree))
/* 'nth' node t within child list of node 'PTree' 
   sacrifying condition filter(t) = False 
   [nth=1..PT_cntST] 
*/
{ 
  if( filter == NULL )
    return PT_nthST_ex(PTree,nth,NULL,NULL);
  else
    return PT_nthST_ex(PTree,nth,default_filter_ex,filter);
}

static bool filterNtmOrTok(PT_Term PTree)
/* Type(PTree) not in { NTM, TOK } ? */
{
  return( ! CFG_TOK_NTM(PT_M_STP(PTree)) );
}

static bool filterSymbol(PT_Term PTree, symbol fsymbol)
/* symbol(PTree) != fsymbol ? */
{
  return( PT_M_SID(PTree) != fsymbol );
}

int PT_symbolCnt(PT_Term PTree, symbol cfgsym, bool filter)
/* filter --> number of nodes with symbol 'cfgsym' 
   else   --> number of token and nonterminal nodes
              ( skipping keywords and comments )
   within child list of node 'PTree' 
*/
{
  if( filter )
    return( PT_cntST_ex(PTree,filterSymbol,cfgsym) );
  else return( PT_cntST(PTree,filterNtmOrTok) );
}

PT_Term PT_nthSymbol(PT_Term PTree, symbol cfgsym, int nth, bool filter)
/* filter --> 'nth' node with symbol 'cfgsym' 
   else   --> 'nth' token or nonterminal node
              ( skipping keywords and comments )
   within child list of node 'PTree' [nth=1..PT_symbolCnt] 
*/
{
  if( filter )
    return( PT_nthST_ex(PTree,nth,filterSymbol,cfgsym) );
  else return( PT_nthST(PTree,nth,filterNtmOrTok) );
}

PT_Term PT_r_find
        (
          PT_Term PTree, bool (*pred)(PT_Term PTree, StdCPtr any), StdCPtr any
        )
/* first subterm t of parse tree / term 'PTree' 
   sacrifying condition pred(t,any) ( recursive )
*/
{
  if( PTree != (PT_Term)NULL )
  {
    if( (*pred)(PTree,any) ) return( PTree );
    else 
    {
      if( CFG_NTM(PT_M_STP(PTree)) )
      { PT_Term rt;
        if( PT_T_TYP(PTree) >= 0 )
        { PTERM* ts;
          for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
	    if( ( rt = PT_r_find(ts,pred,any) ) != (PT_Term)NULL )
	      return( rt );
        }
        else
        { List(PT_Term) ts;
          for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts) )
	    if( ( rt = PT_r_find(fst(PT_Term,ts),pred,any) ) != (PT_Term)NULL )
	      return( rt );
        }
      }
    }
  }
  return( (PT_Term)NULL );
}

PT_Term PT_l_find
        (
          PT_Term PTree, bool (*pred)(PT_Term PTree, StdCPtr any), StdCPtr any
        )
/* first subterm t of parse tree / term 'PTree' 
   sacrifying condition pred(t,any) ( non-recursive )
*/
{
  if( PTree != (PT_Term)NULL )
  {
    if( (*pred)(PTree,any) ) return( PTree );
    else 
    {
      if( CFG_NTM(PT_M_STP(PTree)) )
      {
        if( PT_T_TYP(PTree) >= 0 )
        { PTERM* ts;
          for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
            if( (*pred)(ts,any) ) return( ts );
        }
        else
        { List(PT_Term) ts;
          for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts))
            if( (*pred)(fst(PT_Term,ts),any) ) return( fst(PT_Term,ts) ); 
        }
      }
    }
  }
  return( (PT_Term)NULL );
}

/*I-------------------------- Term Iterator --------------------------------- */

/*!
  <p><b>Traversal order</b>
  <p>All nodes will be visited in pre and post order.
*/

/*DOC_INTERFACE*/
#define PT_ROOT   1 // root / start order
#define PT_PRAE   2 // pre order
#define PT_POST   3 // post order

#define PT_EMPTY_ROOT(r)   ( (r) == (List(PT_Term))NULL )
#define PT_TOPELM(iter)    OT_TOP(StdCPtr,PT_I_STK(iter))
#define PT_TOPTERM(iter)   ( PT_EMPTY_ROOT(PT_I_TOP(iter))                 \
                             ? (PT_Term)PT_TOPELM(iter)                    \
                             : fst(PT_Term,(List(PT_Term))PT_TOPELM(iter)) )
#define PT_TOPLIST(iter)   OT_TOP(List(PT_Term),PT_I_STK(iter))

PT_Itr PT_newIT(PT_Term PTree)
/* creates an iterator for parse tree / term 'PTree' */
{ PTITER* it;
  it = (PTITER*)NewMem(sizeof(PTITER));
  OT_NEWSTK(PT_I_STK(it));
  PT_I_CST(it)  = PT_ROOT;
  if( PTree != (PT_Term)NULL && PT_T_TYP(PTree) < 0 )
  {
    PT_I_TOP(it) = cons(PTree,(List(PT_Term))NULL);
    OT_PUSH(PT_I_TOP(it),PT_I_STK(it));
  }
  else
  {
    PT_I_TOP(it) = (List(PT_Term))NULL;
    OT_PUSH(PTree,PT_I_STK(it));
  }
  return( it );
}

void PT_delIT(PT_Itr iter)
/* removes term iterator 'iter' */
{
  BUG_NULL(iter);
  /*XXX*/ BUG_NULL(PT_I_STK(iter));
  OT_DELSTK(PT_I_STK(iter));
  if( ! PT_EMPTY_ROOT(PT_I_TOP(iter)) ) freeList(PT_I_TOP(iter),primFree);
  FreeMem(iter);
}

static List(PT_Term) PT_copyIT_aux(List(PT_Term) lst)
{ List(PT_Term) res = (List(PT_Term))NULL, x;
  ROW(PT_Term) row = OT_CREATE_ADT(PT_Term);
  INT cnt, i;
  for( x = lst; ! empty(x); x = rst(x) )
    OT_PUSH(fst(PT_Term,x),row);
  for( i=0, cnt=OT_CNT(row); i < cnt; ++i )
  {
    res = XPT_consT(OT_TOP(PT_Term,row),res);
    OT_POP(row);
  }
  OT_DEL_T(row);
  return( res );
}

PT_Itr PT_copyIT(PT_Itr iter)
/* copies term iterator 'iter' */
{ PTITER* it;
  BUG_NULL(iter);
  it = (PTITER*)NewMem(sizeof(PTITER));
  PT_I_CST(it) = PT_I_CST(iter);
  PT_I_STK(it) = OT_COPY(PT_I_STK(iter));
  PT_I_TOP(it) = PT_copyIT_aux(PT_I_TOP(iter));
  return (PT_Itr)it;
}

short PT_stateIT(PT_Itr iter)
/* current traversal order of term iterator 'iter'
   ( PT_PRAE / PT_POST ) 
*/
{
  BUG_NULL(iter);
  return( PT_I_CST(iter) );
}

PT_Term PT_termIT(PT_Itr iter)
/* current node of term iterator 'iter' */
{
  BUG_NULL(iter);
  return(PT_TOPTERM(iter));
}

OT_Tab PT_stackIT(PT_Itr iter)
/* current node stack of term iterator 'iter' */
{
  BUG_NULL(iter);
  return( PT_I_STK(iter) );
}

bool PT_df_getIT(PT_Itr iter)
/* next node of term iterator 'iter' 
   in depth first, prae/post order ;
   returns False on end-of-term
*/
{ StdCPtr t;
  BUG_NULL(iter);
  switch( PT_I_CST(iter) )
  {
    case PT_ROOT:
    {
      PT_I_CST(iter) = PT_PRAE;
      if( PT_TOPELM(iter) != (StdCPtr)NULL ) return( True );
      else
      {
        PT_I_CST(iter) = 0; return( False );
      }
    }
    case PT_PRAE:
    { 
      if( PT_EMPTY_ROOT(PT_I_TOP(iter)) 
          ? ( CFG_NTM(PT_M_STP(PT_TOPELM(iter)))                 &&
              ( t = PT_T_SUB(PT_TOPELM(iter)) ) != (StdCPtr)NULL  )
          : ( CFG_NTM(PT_M_STP(fst(PT_Term,PT_TOPLIST(iter))))       &&
              ! empty( t = PT_T_LST(fst(PT_Term,PT_TOPLIST(iter))) )  ) )
        OT_PUSH(t,PT_I_STK(iter));
      else
        PT_I_CST(iter) = PT_POST;
      return( True );
    }
    case PT_POST:
    {
      if( OT_CNTSTK(PT_I_STK(iter)) > 1                               &&
          ( 
            PT_EMPTY_ROOT(PT_I_TOP(iter)) 
            ? ( ( t = PT_T_NXT(PT_TOPELM(iter)) ) != (StdCPtr)NULL  )
            : ( ! empty((List(PT_Term))(t = rst(PT_TOPLIST(iter)))) )
          )                                                            )
      {
        PT_I_CST(iter) = PT_PRAE;
        OT_POP(PT_I_STK(iter));
        OT_PUSH(t,PT_I_STK(iter));
        return( True );
      }
      else
      {
        OT_POP(PT_I_STK(iter));
        if( ! OT_EMPTYSTK(PT_I_STK(iter)) ) return( True );
        else
        {
          PT_I_CST(iter) = 0; return( False );
        }
      }
    }
    default:
    {
      C_BUG; return( False );
    }
  }
}

bool PT_bf_getIT(PT_Itr iter)
/* next node of term iterator 'iter' 
   in breast first, prae/post order; 
   returns False on end-of-term
*/
{ StdCPtr t;
  BUG_NULL(iter);
  switch( PT_I_CST(iter) )
  {
    case PT_ROOT:
    {
      PT_I_CST(iter) = PT_PRAE;
      if( PT_TOPELM(iter) != (StdCPtr)NULL ) 
      {
        OT_P_INS(PT_I_STK(iter),(StdCPtr)NULL,1);
        return( True );
      }
      else
      {
        PT_I_CST(iter) = 0; return( False );
      }
    }
    case PT_PRAE:
    { 
      if( ( t = OT_GET(StdCPtr,PT_I_STK(iter),0) ) == (StdCPtr)NULL )
      {
        PT_I_CST(iter) = PT_POST;
        OT_DEL_E(PT_I_STK(iter),0);
        return( True );
      }
      else t = PT_TOPELM(iter);
      if( PT_EMPTY_ROOT(PT_I_TOP(iter)) 
          ? ( ( t = PT_T_NXT(t) ) != (StdCPtr)NULL                )
          : ( ! empty((List(PT_Term))(t = rst((List(PT_Term))t))) ) ) 
         OT_PUSH(t,PT_I_STK(iter));
      else
      {
        PT_I_CST(iter) = PT_POST;
        if( OT_CNTSTK(PT_I_STK(iter)) > 1 )
        {
          t = OT_GET(StdCPtr,PT_I_STK(iter),0);
          OT_PUSH(t,PT_I_STK(iter));
          OT_DEL_E(PT_I_STK(iter),0);
        }
      }
      return( True );
    }
    case PT_POST:
    {
      if( PT_EMPTY_ROOT(PT_I_TOP(iter)) 
          ? ( CFG_NTM(PT_M_STP(PT_TOPELM(iter)))                 &&
              ( t = PT_T_SUB(PT_TOPELM(iter)) ) != (StdCPtr)NULL  )
          : ( CFG_NTM(PT_M_STP(fst(PT_Term,PT_TOPLIST(iter))))       &&
              ! empty( t = PT_T_LST(fst(PT_Term,PT_TOPLIST(iter))) )  ) )
      {
        PT_I_CST(iter) = PT_PRAE;
        OT_POP(PT_I_STK(iter));
        OT_PUSH(t,PT_I_STK(iter));
        return( True );
      }
      else
      {
        OT_POP(PT_I_STK(iter));
        if( OT_CNTSTK(PT_I_STK(iter)) > 1 )
        {
          t = OT_GET(StdCPtr,PT_I_STK(iter),0);
          OT_PUSH(t,PT_I_STK(iter));
          OT_DEL_E(PT_I_STK(iter),0);
          return( True );
        }
        if( ! OT_EMPTYSTK(PT_I_STK(iter)) ) return( True );
        else
        {
          PT_I_CST(iter) = 0; return( False );
        }
      }
    }
    default:
    {
      C_BUG; return( False );
    }
  }
}

bool PT_filterIT(PT_Itr iter, bool (*get)(PT_Itr iter))
/* next node of term iterator 'iter' in prae/post order 
   sacrifying filter condition get(iter), 
   skipping comments and keywords;
   returns False on end-of-term i.e. notfound
*/
{
  BUG_NULL(get);
  while( (*get)(iter) )
  { PT_Term x = PT_TOPTERM(iter);
    if( PT_I_CST(iter) != PT_ROOT && CFG_TOK_NTM(PT_M_STP(x)) )
      return( True );
  }
  return( False );
}

void PT_skipIT(PT_Itr iter)
/* skips subterms of current node in term iterator 'iter'
   assertion: current traversal order = PT_PRAE
*/
{
  BUG_NULL(iter);
  PT_BUG_ITER(iter);
  PT_I_CST(iter) = PT_POST;
}

/*I---------------------- Convenient iterator macros ------------------------ */

/*!! For - statement with basic iterators. Make sure to 
     free the iterator if you leave the loop via break. 
*/

/*DOC_INTERFACE*/
#define PT_FORALL(it,tr)      for( (it)   = PT_newIT(tr);            \
                                   ( PT_df_getIT(it) )               \
                                   ? True : ( PT_delIT(it), False ); )
#define PT_FORALL_F(it,tr)    for( (it)   = PT_newIT(tr);            \
                                   ( PT_filterIT(it,PT_df_getIT) )   \
                                   ? True : ( PT_delIT(it), False ); )
#define PT_FORALL_BF(it,tr)   for( (it)   = PT_newIT(tr);            \
                                   ( PT_bf_getIT(it) )               \
                                   ? True : ( PT_delIT(it), False ); )
#define PT_FORALL_BF_F(it,tr) for( (it)   = PT_newIT(tr);            \
                                   ( PT_filterIT(it,PT_bf_getIT) )   \
                                   ? True : ( PT_delIT(it), False ); )
#define PT_BREAK(it)          { PT_delIT(it); break; }


/*I----------------------- Hashing & Predicates ----------------------------- */

/*forward*/ bool PT_equal(PT_Term left, PT_Term right);

long PT_hash(PT_Term PTree)             
/* hash value of parse tree / term 'PTree' */
{ PT_Itr it; long res = 0;
  PT_FORALL(it,PTree)
  { PT_Term t = PT_TOPTERM(it);
    if( PT_I_CST(it) == PT_PRAE && ! CFG_COM(PT_M_STP(t)) )
    {
      if( CFG_NTM(PT_M_STP(t)) )
        res = combineOrderedHash(res,primHash(PT_M_PID(t)));
      res = combineOrderedHash(res,primHash(PT_M_SID(t)));
      if( CFG_CFG(PT_M_STP(t)) )
        res = combineOrderedHash(res,PT_hash(PT_T_SUB(t)));
      else
      if( CFG_TOK(PT_M_STP(t)) )
        res = combineOrderedHash(res,primHash(PT_T_VAL(t)));
    }
  }
  return( res );
}

static bool PT_cmpEQ(PT_Term lft, PT_Term rgt)
/* whether nodes 'lft' and 'rgt' are equal */
{
  return
  ( 
    PT_M_PID(lft) == PT_M_PID(rgt)   &&
    PT_M_SID(lft) == PT_M_SID(rgt)   &&
    ( CFG_NTM(PT_M_STP(lft))         || 
      CFG_NTM(PT_M_STP(rgt))         || 
      PT_T_VAL(lft) == PT_T_VAL(rgt) ||
      (
        CFG_CFG(PT_M_STP(lft)) &&
        CFG_CFG(PT_M_STP(rgt)) &&
        PT_equal(PT_T_SUB(lft),PT_T_SUB(rgt))
      ) )
  );
}

static PT_Term PT_eqFilter(PT_Term tlst)
/* C: comment filter */
{
  while( tlst != (PT_Term)NULL && CFG_COM(PT_M_STP(tlst)) )
    tlst = PT_T_NXT(tlst);
  return( tlst );
}

static List(PT_Term) XPT_eqFilter(List(PT_Term) tlst)
/* Xaron: comment filter */
{
  while( ! empty(tlst) && CFG_COM(PT_M_STP(fst(PT_Term,tlst))) ) 
    tlst = rst(tlst);
  return( tlst );
}

static bool CPT_equal(PT_Term left, PT_Term right)
/* C: left = right ? */
{ 
  if( primEqual(left,right) ) return( True );
  if( left != (PT_Term)NULL && right != (PT_Term)NULL )
  {
    if( PT_cmpEQ(left,right) )
    {
      if( CFG_NTM(PT_M_STP(left)) && CFG_NTM(PT_M_STP(right)) )
      { PTERM* tl; PTERM* tr;
        for
        ( 
          tl = (PTERM*)PT_eqFilter(PT_T_SUB(left)), 
          tr = (PTERM*)PT_eqFilter(PT_T_SUB(right)); 
          tl != (PTERM*)NULL && tr != (PTERM*)NULL; 
          tl = (PTERM*)PT_eqFilter(PT_T_NXT(tl)), 
          tr = (PTERM*)PT_eqFilter(PT_T_NXT(tr)) 
        ) 
	    if( ! CPT_equal(tl,tr) ) return( False );
          return( primEqual(tl,tr) );
      }
      else return( CFG_NTM(PT_M_STP(left)) == CFG_NTM(PT_M_STP(right)) );
    }
    else return( False );
  }
  else return( False );
}

static bool XPT_equal(PT_Term left, PT_Term right)
/* Xaron: left = right ? */
{ 
  if( primEqual(left,right) ) return( True );
  if( left != (PT_Term)NULL && right != (PT_Term)NULL )
  {
    if( PT_cmpEQ(left,right) )
    {
      if( CFG_NTM(PT_M_STP(left)) && CFG_NTM(PT_M_STP(right)) )
      { List(PT_Term) tl; List(PT_Term) tr;
        for
        ( 
          tl = XPT_eqFilter(PT_T_SUB(left)), tr = XPT_eqFilter(PT_T_SUB(right));
          ! empty(tl) && ! empty(tr);
          tl = XPT_eqFilter(rst(tl)), tr = XPT_eqFilter(rst(tr)) 
        ) 
	  if( ! XPT_equal(fst(PT_Term,tl),fst(PT_Term,tr)) ) return( False );
        return( primEqual(tl,tr) );
      }
      else return( CFG_NTM(PT_M_STP(left)) == CFG_NTM(PT_M_STP(right)) );
    }
    else return( False );
  }
  else return( False );
}

bool PT_equal(PT_Term left, PT_Term right)
/* term 'left' = term 'right' ? */
{ 
  if( primEqual(left,right) ) return( True );
  if( left != (PT_Term)NULL && right != (PT_Term)NULL )
  {
    PT_BUG_TYPES(left,right);
    return
    ( 
      ( PT_T_TYP(left) >= 0 ) ? CPT_equal(left,right) : XPT_equal(left,right) 
    );
  }
  else return( False );
}

bool PT_subterm(PT_Term left, PT_Term right)
/* term 'left' <= term 'right' ? */
{ PT_Itr it; bool ret = False;
  if( primEqual(left,right) ) return( True );
  if( right == (PT_Term)NULL ) return( False );
  PT_FORALL(it,right)
  { PT_Term t = PT_TOPTERM(it);
    if( PT_I_CST(it) == PT_PRAE && PT_cmpEQ(left,t) )
    {
      if( PT_equal(left,t) )
      {
        ret = True; PT_BREAK(it);
      }
      else PT_I_CST(it) = PT_POST;
    }
  }
  return( ret );
}

/*I---------------------------- Binary Image -------------------------------- */

/*forward*/ void PT_fputT(BinImg_T img, PT_Term PTree);
/*forward*/ void PT_fgetT(BinImg_T img, PT_Term* PTree);

static void PT_fputNode(BinImg_T img, PT_Term PTree)
/* puts node to 'img' */
{
  fputWord(img,PT_T_TYP(PTree));
  fputReference(img,PT_M_SID(PTree),fputSymbol);
  if( CFG_NTM(PT_M_STP(PTree)) ) 
    fputReference(img,PT_M_PID(PTree),fputSymbol);
  if( PT_P_FIL(PTree) != (symbol)NULL ) 
  {
    fputLong(img,PT_P_ROW(PTree)); 
    fputLong(img,PT_P_COL(PTree));
    fputReference(img,PT_P_FIL(PTree),fputSymbol);
  }
  else fputLong(img,-1);
  if( CFG_CFG(PT_M_STP(PTree)) ) 
    PT_fputT(img, PT_T_SUB(PTree));
  else
  if( ! CFG_NTM(PT_M_STP(PTree)) ) 
    fputReference(img,PT_T_VAL(PTree),fputSymbol);
}

static void PT_fgetNode(BinImg_T img, PT_Term* PTree)
/* gets node from 'img' */
{
  *PTree = (PTERM*)NewMem(sizeof(PTERM));  
  fgetWord(img,&PT_T_TYP(*PTree));
  fgetReference(img,&PT_M_SID(*PTree),fgetSymbol);
  if( CFG_NTM(PT_M_STP(*PTree)) ) 
    fgetReference(img,&PT_M_PID(*PTree),fgetSymbol);
  else PT_M_PID(*PTree) = (symbol)NULL;
  fgetLong(img,&PT_P_ROW(*PTree)); 
  if( PT_P_ROW(*PTree) != -1 ) 
  {
    fgetLong(img,&PT_P_COL(*PTree));
    fgetReference(img,&PT_P_FIL(*PTree),fgetSymbol);
  }
  else
  {
    PT_P_COL(*PTree) = -1;
    PT_P_FIL(*PTree) = (symbol)NULL;
  }
  if( CFG_CFG(PT_M_STP(PTree)) ) 
    PT_fgetT(img,(PT_Term*)PT_T_SUB_PTR(*PTree));
  else
  if( ! CFG_NTM(PT_M_STP(*PTree)) ) 
    fgetReference(img,PT_T_VAL_PTR(*PTree),fgetSymbol);
  else
    PT_T_PTR_1(*PTree) = (StdCPtr)NULL;
  PT_T_PTR_2(*PTree) = (StdCPtr)NULL;
}

void PT_fputT(BinImg_T img, PT_Term PTree)
/* unloads parse tree / term 'PTree' 
   to binary image 'img' (reentrant)
*/
{ 
  BUG_NULL(PTree);
  PT_fputNode(img,PTree); 
  if( CFG_NTM(PT_M_STP(PTree)) )
  {
    if( PT_T_TYP(PTree) >= 0 )
    { PTERM* ts;
      fputWord(img,(short)PT_cntST(PTree,(bool (*)(PT_Term PTree))NULL));
      for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
        fputReference(img,ts,PT_fputT);
    }
    else
    { List(PT_Term) ts = PT_T_LST(PTree);
      fputWord(img,(short)length(ts));
      for( ; ! empty(ts); ts = rst(ts) )
        fputReference(img,fst(PT_Term,ts),PT_fputT);
    }
  }
}

void PT_putT(PT_Term PTree)
/* unloads parse tree / term 'PTree' 
   to the current ( previously opened ) image 
*/
{ 
  PT_fputT(BIN_getCurImage(),PTree);
}

void PT_fgetT(BinImg_T img, PT_Term* PTree)
/* loads parse tree / term 'PTree' 
   from binary image 'img' (reentrant)
*/
{ short cnt, i;
  BUG_NULL(PTree);
  PT_fgetNode(img,PTree); 
  if( CFG_NTM(PT_M_STP(*PTree)) )
  { PTERM* ts;
    fgetWord(img,&cnt);
    if( PT_T_TYP(*PTree) >= 0 )
    { PTERM** t;
      t = PT_T_SUB_PTR(*PTree);
      for( i=0; i < cnt; ++i )
      { 
        fgetReference(img,(PT_Term*)(&ts),PT_fgetT);
        *t = ts; t = PT_T_NXT_PTR(ts);
      }
    }
    else
    { List(PT_Term)* t;
      t = PT_T_LST_PTR(*PTree);
      for( i=0; i < cnt; ++i )
      { 
        fgetReference(img,(PT_Term*)(&ts),PT_fgetT);
        *t = cons(ts,*t); t = rst_ref(*t);
      }
    }
  }
}

void PT_getT(PT_Term* PTree)
/* loads parse tree / term 'PTree' 
   from the current ( previously opened ) image 
*/
{
  PT_fgetT(BIN_getCurImage(),PTree);
}

/*I------------------------------- Printing --------------------------------- */

static void PT_prTermHdr(PT_Term PTree)
/* prints parse tree / term */
{
  if( PTree != (PT_Term)NULL )
  {
    NL; 
    fprintf(STDOUT,"Derivation Tree from Source : ");
    fprint_raw
    (
      STDOUT,
      PT_P_FIL(PTree) == (symbol)NULL 
      ? "[non]" : symbolToString(PT_P_FIL(PTree)),
      -1
    );
  }
}

static void PT_prUtf8TermHdr(PT_Term PTree)
/* prints parse tree / term */
{
  if( PTree != (PT_Term)NULL )
  { Sink   snk = Sink_open();
    string s;
    NL; 
    Sink_printf
    (
      snk,"Derivation Tree from Source : %s", 
      PT_P_FIL(PTree) == (symbol)NULL 
      ? "[non]" : symbolToString(PT_P_FIL(PTree))
    );
    s = Sink_close(snk);
    GS_fprint_utf8(STDOUT,s,False);
    FreeMem(s);
  }
}

static void PT_prNodeKeyPos(PT_Term PTree)
/* prints node key and postion */
{ c_string cfgsym = PT_M_SID(PTree) == (symbol)NULL
                    ? "" : symbolToString(PT_M_SID(PTree));
  if( CFG_COM(PT_M_STP(PTree)) ) fprintf(STDOUT,"Comment");
  else
  {
    if( PT_M_PID(PTree) == (symbol)NULL )
    {
      fprintf
      (
        STDOUT,"%s",
        CFG_TOK(PT_M_STP(PTree))?cfgsym:"Keyword"
      );
    }
    else
    {
      fprintf
      (
        STDOUT,"%s.%s",
        cfgsym,symbolToString(PT_M_PID(PTree))
      );
    }
  }
  if( PT_P_FIL(PTree) != (symbol)NULL ) 
    fprintf(STDOUT," (%ld,%ld)",PT_P_ROW(PTree),PT_P_COL(PTree));
}

static void PT_prUtf8NodeKeyPos(PT_Term PTree)
/* prints node key and postion */
{ Sink   snk = Sink_open();
  string s;
  if( CFG_COM(PT_M_STP(PTree)) ) Sink_printf(snk,"Comment");
  else
  {
    if( PT_M_PID(PTree) == (symbol)NULL )
      Sink_printf
      (
        snk,"%s",
        CFG_TOK(PT_M_STP(PTree))?symbolToString(PT_M_SID(PTree)):"Keyword"
      );
    else
      Sink_printf
      (
        snk,"%s.%s",
        symbolToString(PT_M_SID(PTree)),symbolToString(PT_M_PID(PTree))
      );
  }
  if( PT_P_FIL(PTree) != (symbol)NULL ) 
    Sink_printf(snk," (%ld,%ld)",PT_P_ROW(PTree),PT_P_COL(PTree));
  s = Sink_close(snk);
  GS_fprint_utf8(STDOUT,s,False);
  FreeMem(s);
}

static void PT_prTerm(PT_Term PTree, void (*pMbr)(PT_Term PTree), int indent)
/* prints term */
{
  fprintf(STDOUT,"\n%*s",indent,"");
  if( PTree == (PT_Term)NULL ) fprintf(STDOUT,"NULL");
  else 
  if( CFG_CFG(PT_M_STP(PTree)) )
  {
    PT_prTerm(PT_T_VAL(PTree),pMbr,indent);
  }
  else 
  {
    fprintf(STDOUT,"["); /* before group */
    (*pMbr)(PTree);
    if( CFG_NTM(PT_M_STP(PTree)) )
    {
      if( PT_T_TYP(PTree) >= 0 )
      { PTERM* ts;
        for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
          PT_prTerm(ts,pMbr,indent+1);
      }
      else
      { List(PT_Term) ts;
        for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts) )
          PT_prTerm(fst(PT_Term,ts),pMbr,indent+1);
      }
    } 
    fprintf(STDOUT,"]"); /* after group */
  }
}

static void PT_prUtf8Term(PT_Term PTree, void (*pMbr)(PT_Term PTree), int indent)
/* prints term */
{ Sink   snk = Sink_open();
  string s;
  Sink_printf(snk,"\n%*s",indent,"");
  s = Sink_close(snk);
  GS_fprint_utf8(STDOUT,s,False);
  FreeMem(s);
  if( PTree == (PT_Term)NULL )
    GS_fprint_utf8(STDOUT,"NULL",False);
  else 
  if( CFG_CFG(PT_M_STP(PTree)) )
  {
    PT_prUtf8Term(PT_T_VAL(PTree),pMbr,indent);
  }
  else 
  {
    GS_fprint_utf8(STDOUT,"[",False); /* before group */
    (*pMbr)(PTree);
    if( CFG_NTM(PT_M_STP(PTree)) )
    {
      if( PT_T_TYP(PTree) >= 0 )
      { PTERM* ts;
        for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
          PT_prUtf8Term(ts,pMbr,indent+1);
      }
      else
      { List(PT_Term) ts;
        for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts) )
          PT_prUtf8Term(fst(PT_Term,ts),pMbr,indent+1);
      }
    } 
    GS_fprint_utf8(STDOUT,"]",False); /* after group */
  }
}

static void PT_prNode(PT_Term PTree)
/* prints node */
{ 
  PT_prNodeKeyPos(PTree);
  if( ! CFG_NTM(PT_M_STP(PTree)) )
    fprintf(STDOUT," \"%s\"",symbolToString(PT_T_VAL(PTree)));
}

static void PT_prUtf8Node(PT_Term PTree)
/* prints node */
{ 
  PT_prUtf8NodeKeyPos(PTree);
  if( ! CFG_NTM(PT_M_STP(PTree)) )
  {
    GS_fprint_utf8(STDOUT," \"",False);
    GS_fprint_utf8(STDOUT,symbolToString(PT_T_VAL(PTree)),False);
    GS_fprint_utf8(STDOUT,"\"",False);
  }
}

static void PT_prRawUtf8Node(PT_Term PTree)
/* prints node */
{ 
  PT_prNodeKeyPos(PTree);
  if( ! CFG_NTM(PT_M_STP(PTree)) )
  {
    fprintf(STDOUT," \"");
    GS_fprint_utf8(STDOUT,symbolToString(PT_T_VAL(PTree)),True);
    fprintf(STDOUT,"\"");
  }
}

void PT_prind(PT_Term PTree, int ind)
/* prints parse tree / term 'PTree' to stdout 
   ( with indent 'ind' ) 
*/
{
  PT_prTerm(PTree,PT_prNode,ind);
}

void PT_prind_utf8(PT_Term PTree, int ind)
/* prints utf8 parse tree / term 'PTree' to stdout 
   ( with indent 'ind' ) 
*/
{
  PT_prUtf8Term(PTree,PT_prUtf8Node,ind);
}

void PT_prind_rawutf8(PT_Term PTree, int ind)
/* prints utf8 parse tree / term 'PTree' to stdout 
   ( printable ascii or hex, with indent 'ind' ) 
*/
{
  PT_prTerm(PTree,PT_prRawUtf8Node,ind);
}

void PT_print(PT_Term PTree)
/* prints parse tree / term 'PTree' to stdout */
{
  PT_prTermHdr(PTree);
  NL; PT_prind(PTree,0); NL;
}

void PT_print_utf8(PT_Term PTree)
/* prints utf8 parse tree / term 'PTree' to stdout */
{
  PT_prUtf8TermHdr(PTree);
  NL; PT_prind_utf8(PTree,0); NL;
}

void PT_print_rawutf8(PT_Term PTree)
/* prints utf8 parse tree / term 'PTree' to stdout 
   ( printable ascii or hex ) 
*/
{
  PT_prTermHdr(PTree);
  NL; PT_prind_rawutf8(PTree,0); NL;
}

void PT_TermToString(PT_Term PTree)
/* prints value of parse tree / term 'PTree' to stdout */
{
  if( PTree != (PT_Term)NULL )
  {
    if( CFG_CFG(PT_M_STP(PTree)) )
      PT_TermToString(PT_T_VAL(PTree));
    else
    if( ! CFG_NTM(PT_M_STP(PTree)) )
      fprintf(STDOUT," %s",symbolToString(PT_T_VAL(PTree)));
    else
    {
      if( PT_T_TYP(PTree) >= 0 )
      { PTERM* ts;
        for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
          PT_TermToString(ts);
      } 
      else
      { List(PT_Term) ts;
        for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts) )
          PT_TermToString(fst(PT_Term,ts));
      }
    } 
  }
}

void PT_TermToSink(PT_Term PTree, Sink snk)
/* prints value of parse tree / term 'PTree' to sink 'snk' 
   ( without comments )
*/
{
  if( PTree != (PT_Term)NULL )
  {
    if( CFG_CFG(PT_M_STP(PTree)) )
      PT_TermToSink(PT_T_VAL(PTree),snk);
    else
    if( ! CFG_NTM(PT_M_STP(PTree)) )
    {
      if( ! CFG_COM(PT_M_STP(PTree)) )
        Sink_printf(snk," %s",symbolToString(PT_T_VAL(PTree)));
    }
    else
    {
      if( PT_T_TYP(PTree) >= 0 )
      { PTERM* ts;
        for( ts = PT_T_SUB(PTree); ts != (PTERM*)NULL; ts = PT_T_NXT(ts) )
          PT_TermToSink(ts,snk);
      } 
      else
      { List(PT_Term) ts;
        for( ts = PT_T_LST(PTree); ! empty(ts); ts = rst(ts) )
          PT_TermToSink(fst(PT_Term,ts),snk);
      }
    } 
  }
}

/*I----------------------------- Normalizer --------------------------------- */

static PT_Term PT_key_Skip(PT_Term x, ROW(PT_Term) coms)
/* C: skips comments and keywords over 'next' ( comment collection ) */
{
  while(x != (PT_Term)NULL && !PT_isToken(x) && !PT_isNonTerm(x))
  {
    if( PT_isComment(x) ) OT_T_INS(coms,x);
    x = PT_next(x);
  }
  return x;
}

static List(PT_Term) XPT_key_Skip(List(PT_Term) x, ROW(PT_Term) coms)
/* Xaron: skips comments and keywords over 'sub term list' */
/* ( comment collection ) */
{
  while
  (
    !empty(x) && !PT_isToken(fst(PT_Term,x)) && !PT_isNonTerm(fst(PT_Term,x))
  )
  { PT_Term t = fst(PT_Term,x);
    if( PT_isComment(t) ) OT_T_INS(coms,t);
    x = rst(x);
  }
  return( x );
}

PT_Term PT_keycom_Skip(PT_Term x)
/* C: skips comment and keyword nodes in child list 'x';
      returns first token / nonterminal node or NULL
*/
{
  while(x != (PT_Term)NULL && !PT_isToken(x) && !PT_isNonTerm(x))
    x = PT_next(x);
  return x;
}

List(PT_Term) XPT_keycom_Skip(List(PT_Term) x)
/* Xaron: skips comment and keyword nodes in child list 'x';
          returns next token / nonterminal node or NULL
*/
{
  while
  (
    !empty(x) && !PT_isToken(fst(PT_Term,x)) && !PT_isNonTerm(fst(PT_Term,x))
  )
    x = rst(x);
  return( x );
}

PT_Term PT_ignkey_Skip(PT_Term x, ROW(PT_Term) coms)
/* skips 'ign#'-production, comment and keyword nodes 
   in parse tree / term 'x', collecting comment nodes in 'coms';
   returns next token / nonterminal node
*/
{ PT_Term ori = x;
  BUG_NULL(coms);
  while
  ( 
    x != (PT_Term)NULL && PT_isNonTerm(x) && 
    ignProd(symbolToString(PT_product(x))) 
  )
  {
    if( PT_T_TYP(x) >= 0 ) x = PT_key_Skip(PT_T_SUB(x),coms); 
    else
    { List(PT_Term) y = (PT_Term)XPT_key_Skip(PT_T_LST(x),coms);
      x = ( ! empty(y) ) ? fst(PT_Term,y) : (PT_Term)NULL;
    }
  }
  if( x == (PT_Term)NULL || ( !PT_isNonTerm(x) && !PT_isToken(x) ) )
  {
    if (x != (PT_Term)NULL) { PT_prNode(ori); NL; }
    assert0(False,"invalid 'ign'-production");
  }
  return x;
}

PT_Term PT_ign_Skip(PT_Term x)
/* skips 'ign#'-production, comment and keyword nodes 
   in parse tree / term 'x';
   returns next token / nonterminal node
*/
{ PT_Term ori = x;
  while
  ( 
    x != (PT_Term)NULL && PT_isNonTerm(x) && 
    ignProd(symbolToString(PT_product(x))) 
  )
  {
    if( PT_T_TYP(x) >= 0 ) x = PT_keycom_Skip(PT_T_SUB(x)); 
    else
    { List(PT_Term) y = (PT_Term)XPT_keycom_Skip(PT_T_LST(x));
      x = ( ! empty(y) ) ? fst(PT_Term,y) : (PT_Term)NULL;
    }
  }
  if( x == (PT_Term)NULL || ( !PT_isNonTerm(x) && !PT_isToken(x) ) )
  {
    if (x != (PT_Term)NULL) { PT_prNode(ori); NL; }
    assert0(False,"invalid 'ign'-production");
  }
  return x;
}

/*I-------------------------- Xaron Support --------------------------------- */

void PT_references(PT_Term x, StdCPtr (*act)(StdCPtr r))
/* performs 'act' on all pointer and symbol references in node 'x'
   ( garbage collection service for xaron )
*/
{ StdCPtr nxt = PT_T_PTR_2(x), val = PT_T_PTR_1(x);
  symbol  pid = PT_M_PID(x),   sid = PT_M_SID(x), fil = PT_P_FIL(x);
  if( nxt != (StdCPtr)NULL ) PT_T_PTR_2(x) = (*act)(nxt);
  if( val != (StdCPtr)NULL ) PT_T_PTR_1(x) = (*act)(val);
  if( pid != (StdCPtr)NULL ) PT_M_PID(x)   = (*act)(pid);
  if( sid != (StdCPtr)NULL ) PT_M_SID(x)   = (*act)(sid);
  if( fil != (StdCPtr)NULL ) PT_P_FIL(x)   = (*act)(fil);
}

/*I========================== Parse Tree (ABS) ============================== */

/*!!
   The above mentioned special optimzed form of an abstract parse tree can be
   produced with the following - non-reentrant - unload/load-API.
 
         parse tree         --- unload ---> 
                                              binary image 
         parse tree (ABS)  <---  load  --- 
   
*/

/*I------------------------ Types & Macros ---------------------------------- */

AbstractHugeType(PT_Abs_Term); /* Abstract parse tree type [ABS] */

/*DOC_INTERFACE*/
#define PT_Abs_nonterm(X)   ((symbol)(((long __HUGE*)(X))[0]))
#define PT_Abs_token(X)     ((symbol)(((long __HUGE*)(X))[0]))
#define PT_Abs_product(X)   ((symbol)(((long __HUGE*)(X))[1]))
#define PT_Abs_value(X)     ((symbol)(((long __HUGE*)(X))[2]))
#define PT_Abs_part(X,N)    ((PT_Abs_Term)(((long __HUGE*)(X))[2+(N)]))
#define PT_Abs_cfg(X)       ((PT_Abs_Term)(((long __HUGE*)(X))[2+(1)]))

/*DOC_INTERFACE*/
#define PT_Abs_isToken(X)   (PT_Abs_product(X) == (symbol)NULL)
#define PT_Abs_isNonTerm(X) (PT_Abs_product(X) != (symbol)NULL)
#define PT_Abs_isCFG(X) \
  (PT_Abs_product(X) == (symbol)NULL && PT_Abs_value(X) == NULL)

#define PT_MODE_NON      0
#define PT_MODE_PUT      1
#define PT_MODE_GET      2

#define PT_PUT_BUG       BUG_VEQU(ImgMode,PT_MODE_PUT)
#define PT_GET_BUG       BUG_VEQU(ImgMode,PT_MODE_GET)
#define PT_NON_BUG       BUG_VEQU(ImgMode,PT_MODE_NON)
#define PT_SYMREF_BUG(i) BUG_RNG0((i),OT_CNT(AbsSymbol))

static short             ImgMode = PT_MODE_NON;
static ROW(PT_Term)      AbsTerm;
static ROW(long)         AbsSymbol;
static MAP(PT_Term,long) Abs_TermRef;
static MAP(symbol,long)  Abs_SymbolRef;

/*I------------------------- Init & Quit ------------------------------------ */

void PT_putBgn(void)
/* initializes abstract term putting */
{
  PT_NON_BUG;
  ImgMode       = PT_MODE_PUT;
  Abs_TermRef   = MAP_newPrimMap();
  Abs_SymbolRef = MAP_newPrimMap();
  AbsTerm       = OT_CREATE_ADT(PT_Term);
  AbsSymbol     = OT_CREATE_ADT(symbol);
  OT_T_INS(AbsTerm,0);
  OT_T_INS(AbsSymbol,0);
}

void PT_putEnd(void)
/* quits abstract term putting */
{
  MAP_freeMap(Abs_TermRef);
  MAP_freeMap(Abs_SymbolRef);
  OT_DEL_T(AbsTerm);
  OT_DEL_T(AbsSymbol);
  ImgMode = PT_MODE_NON;
}

void PT_getBgn(void)
/* initializes abstract term getting */
{
  PT_NON_BUG;
  ImgMode = PT_MODE_GET;
  AbsSymbol = OT_CREATE_ADT(symbol);
}

void PT_getEnd(void)
/* quits abstract term getting */
{
  OT_DEL_T(AbsSymbol);
  ImgMode = PT_MODE_NON;
}

/*I------------------------------ Put & Get --------------------------------- */

long PT_Symbol_to_Ref(symbol s)
/* reference corresponding to symbol 's' */
{
  if( ! MAP_defined(Abs_SymbolRef,s) ) 
    assert1(False,"missing symbol '%s'",symbolToString(s));
  return MAP_apply(long,Abs_SymbolRef,s);
}

long PT_putSymbol(symbol s)
/* creates a reference for symbol 's' */
{ long idx;
  PT_PUT_BUG; BUG_NULL(s);
  if( ! MAP_defined(Abs_SymbolRef,s) )
  { long len = OT_GET(long,AbsSymbol,0);
    len += strlen(symbolToString(s))+1;
    OT_UPD(long,AbsSymbol,0,len);
    idx = OT_T_INS(AbsSymbol,s);
    MAP_dfndom(Abs_SymbolRef,s,idx);
  }
  else idx = MAP_apply(long,Abs_SymbolRef,s);
  return idx;
}

void PT_putAllSymbols(void)
/* puts all symbol references
   to the current ( previously opened ) binary image
*/
{
  PT_PUT_BUG;
  { long len = OT_GET(long,AbsSymbol,0), 
         cnt = OT_CNT(AbsSymbol), i, l=0;
    byte __HUGE* array = (byte __HUGE*)NewHMem(len);
    for( i=1; i < cnt; ++i )
    { string s = symbolToString(OT_GET(symbol,AbsSymbol,i)); int j;
      for( j=0; j < strlen(s); ++j )
      {
        array[l] = s[j]; ++l;
      }  
      array[l] = '\0'; ++l;
    }
    putHuge((HugeCPtr)array,len); 
    FreeHMem(array);
  }
}

void PT_getAllSymbols(void)
/* gets all symbol references
   from the current ( previously opened ) binary image
*/
{ long len, l=0; byte __HUGE* array;
  PT_GET_BUG;
  getHuge((HugeCPtr*)(&array),&len);
  OT_T_INS(AbsSymbol,len);
  while( l < len )
  { symbol s = stringToSymbol((string)(&array[l]));
    OT_T_INS(AbsSymbol,s);
    l += strlen((string)(&array[l]))+1;
  }
  FreeHMem(array);
}

symbol PT_getSymbol(long RefId)
/* symbol corresponding to reference 'RefId' */
{
  PT_GET_BUG; PT_SYMREF_BUG(RefId);
  return OT_GET(symbol,AbsSymbol,RefId);
}

long PT_Term_to_Ref(PT_Term PTree)
/* abstract term reference corresponding to parse tree 'PTree' 
   ( unload phase )
*/
{
  return MAP_apply(long,Abs_TermRef,PTree);
}

PT_Abs_Term PT_Ref_to_Term(long __HUGE* nodes, long RefId)
/* abstract term in node array 'nodes' 
   corresponding to reference 'RefId' 
   ( load phase )
*/
{
  return (PT_Abs_Term)(nodes+RefId);
}

long PT_putAbsNode(PT_Term PTree)
/* creates an abstract term reference for parse tree 'PTree' */
{ ROW(long) tref; long res;
  PT_PUT_BUG; BUG_NULL(PTree);
  tref = OT_CREATE_ADT(long);
  if( CFG_CFG(PT_M_STP(PTree)) )
  {
    OT_T_INS(tref,PT_putAbsNode(PT_T_VAL(PTree)));
  }
  else
  if( CFG_NTM(PT_M_STP(PTree)) )
  {
    if( PT_T_TYP(PTree) >= 0 )
    { PTERM* ts; 
      for( ts = (PTERM*)PT_keycom_Skip(PT_T_SUB(PTree)); 
           ts != (PTERM*)NULL; ts = (PTERM*)PT_keycom_Skip(PT_T_NXT(ts)) )
        OT_T_INS(tref,PT_putAbsNode(PT_ign_Skip(ts)));
    }
    else
    { List(PT_Term) ts;
      for( ts = XPT_keycom_Skip(PT_T_LST(PTree)); 
           ! empty(ts); ts = XPT_keycom_Skip(rst(ts)) )
        OT_T_INS(tref,PT_putAbsNode(PT_ign_Skip(fst(PT_Term,ts))));
    }
  }
  MAP_dfndom(Abs_TermRef,PTree,res = OT_CNT(AbsTerm));
  OT_T_INS(AbsTerm,-PT_putSymbol(PT_M_SID(PTree)));
  if( CFG_CFG(PT_M_STP(PTree)) ) 
  {
    OT_T_INS(AbsTerm,0);
    OT_T_INS(AbsTerm,0);
    OT_APPEND(AbsTerm,tref);
  }
  else 
  if( CFG_NTM(PT_M_STP(PTree)) ) 
  {
    OT_T_INS(AbsTerm,-PT_putSymbol(PT_M_PID(PTree)));
    OT_APPEND(AbsTerm,tref);
  }
  else 
  {
    OT_T_INS(AbsTerm,0);
    OT_T_INS(AbsTerm,-PT_putSymbol(PT_T_VAL(PTree)));
  }
  OT_DEL_T(tref);
  return res;
}

void PT_putAbsT(void)
/* puts all abstract term references
   to the current ( previously opened ) binary image
*/
{
  PT_PUT_BUG;
  OT_UPD(long,AbsTerm,0,OT_CNT(AbsTerm)-1);
  putHuge((HugeCPtr)OT_TRICKY_objects(AbsTerm),OT_CNT(AbsTerm)*sizeof(long)); 
}

long __HUGE* PT_getAbsT(void)
/* gets all abstract term references
   from the current ( previously opened ) binary image
*/
{ long len; long __HUGE* array;
  PT_GET_BUG;
  getHuge((HugeCPtr*)(&array),&len);
  return array;
}

long __HUGE* PT_patchAbsT(long __HUGE* nodes)
/* patches all abstract term references 
   in node array 'nodes'; returns 'nodes'
*/
{ long len, i;
  PT_GET_BUG; BUG_NULL(nodes);
  len = nodes[0];
  for( i=1; i <= len; ++i )
  { long m = nodes[i];
    if( m < 0 ) nodes[i] = (long)PT_getSymbol(-m);
    else
    {
      if( m > 0 ) nodes[i] = (long)(nodes+m);
    }
  }
  return( nodes );
}

/*I------------------------- Disposing -------------------------------------- */

void PT_delAbsT(long __HUGE* nodes)
/* removes node array 'nodes' with abstract term references */
{
  FreeHMem(nodes);
}

