/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [hset.c]                 Type: Hash Set/Relation                           */
/*                                                                            */
/* Copyright (c) 1993 by D\olle, Manns                                        */
/*----------------------------------------------------------------------------*/

#include "standard.h"
#include "prim.h"      /* for primitive types */

#include "hmap.h"
#include "otab.h"
#include "binset.h"


/*!!
   [hset] implements sets and relations based on finite maps.
*/

/*INTERFACE*/
/* There is no Copy Semantic for Domain Values !          */
/* A Set Operation on a special binary Relations leads to */
/* an ordinary binary Relation.                           */

/*I------------------------------ Types ------------------------------------- */

AbstractType(HS_Set); /* Abstract set/relation type           */
AbstractType(HS_Elm); /* Abstract set/relation element type   */
AbstractType(HS_Dom); /* Abstract tuple component type        */
AbstractType(HS_Itr); /* Abstract set/relation iterator type  */

typedef struct _HS_SET { /* Set Type                          */
  MAP(HS_Elm,NULL) map;  /* Set Hash Map                      */
} HS_SET;

typedef struct _HS_NREL { /* Rel Type                         */
  StdCPtr* tpltyp;      /* Type of Rel Tuple                  */
  MAP(HS_Elm,NULL) map; /* Rel Hash Map                       */
} HS_NREL;

typedef struct _HS_BREL { /* BinRel Type                      */
  StdCPtr* tpltyp;     /* Type of Rel Tuple                   */
  HS_Dom* classes;     /* class representants or NULL         */
  OT_Tab maps;         /* Table of BinRel Hash Maps           */
                       /* [ MAP(HS_Elm,NULL) ]                */
  MAP(HS_Dom,int) map; /* BinRel Hash Maps Reference Hash Map */
} HS_BREL;

typedef union _HS_UNION { /* Set/Rel/BinSet Type              */
  HS_SET  set;          /* Set                                */
  HS_NREL nrel;         /* Rel                                */
  HS_BREL brel;         /* BinRel                             */
} HS_UNION;

typedef struct _HSSET { /* Set/Rel Type                        */
  short settyp; /* Type of Set/Rel                             */
  HS_UNION set; /* Set/Rel                                     */
} HSSET;

typedef struct _HSITR { /* Iterator Type                       */
  INT bridx;    /* BinRel Hash Map Index or -1                 */
  MAPIT mapitr; /* MAP-Iterator                                */
  HS_Set set;   /* Set/Rel for Iteration                       */
} HSITR;

/*DOC_INTERFACE*/
#define SET(type)   HS_Set   /* Polymorphic SET - Type */

/* ------------------------ Constants and Globals --------------------------- */

/* Types of Sets and Relations */

#define HS_T_SET              0
#define HS_T_NREL             1
#define HS_T_BREL             2
#define HS_T_RCLOSURE         3
#define HS_T_SCLOSURE         4
#define HS_T_RSCLOSURE        5
#define HS_T_CLOSURE          6
#define HS_T_ICLOSURE         7
#define HS_T_ECLOSURE         8
#define HS_T_CLASS            9

static string Property[10] =
{ /* reflexive, symmetric, transitive, equivalence */
  "0000", "0000", "0000", "r000", "0s00", "rs00", "r0t0", "00t0", "rste", "rste"
};

/* avoid copies of tuples while iterating on rels */

static bool TupleAlloc = True; /* only False while iterating on rels */

static bool setTplAlc(bool OnOff)
{
  return( TupleAlloc = OnOff );
}

#define HS__MAPITR(DomVar,ItrVar,MapExpr)                                    \
        for                                                                  \
        (                                                                    \
          ItrVar = MAP_newItr(MapExpr);                                      \
          MAP_emptyItr(ItrVar)                                               \
          ? (MAP_freeItr(ItrVar),                                    False)  \
          : (setTplAlc(False), MAP_getItr(ItrVar,&DomVar), setTplAlc(True)); \
        )

/* Kind of iterate Actions, used by Function 'itractBRMaps' */

#define HS_ACT_OVR            0
#define HS_ACT_RMV            1
#define HS_ACT_DFN            2

/* Access Macros */

#define HS__IMP(set)          ( (HSSET*)(set) )
#define HS__ADT(set)          ( (HS_Set)(set) )

#define HS__ITR_IMP(itr)      ( (HSITR*)(itr) )
#define HS__ITR_ADT(itr)      ( (HS_Itr)(itr) )

/* Im folgenden hat der Parameter n die Bedeutung Nth >= 1, */
/* waehrend i die Bedeutung idx > 0 hat                     */

#define HS__TYP_LEN(typ)      ( intCAST(*(typ)) + 1 )
#define HS__TYP_ARITY(typ)    ( intCAST(*(typ)) >> 1 )
#define HS__TYP_EADR(typ,n)   ( (typ)[((n)<<1)-1] )
#define HS__TYP_HADR(typ,n)   ( (typ)[(n)<<1] )
#define HS__TYP_EQUAL(typ,n)  ( (bool (*)(HS_Dom l,HS_Dom r))(typ)[((n)<<1)-1] )
#define HS__TYP_HASH(typ,n)   ( (long (*)(HS_Dom dom))(typ)[(n)<<1] )
#define HS__TYP_COL(typ,i)    ( (typ)[i] )

#define HS__TPL_TYP(tpl)      ( getTplTyp((HS_Set)((StdCPtr*)(tpl))[0]) )
#define HS__TPL_ARITY(tpl)    ( HS__TYP_ARITY(HS__TPL_TYP(tpl)) )
#define HS__TPL_DOM(tpl,n)    ( ((HS_Dom*)(tpl))[n] )
#define HS__TPL_COL(tpl,i)    ( ((StdCPtr*)(tpl))[i] )

#define HS__ITR_SET(itr)      ( HS__ITR_IMP(itr)->set )
#define HS__ITR_ITR(itr)      ( HS__ITR_IMP(itr)->mapitr )
#define HS__ITR_IDX(itr)      ( HS__ITR_IMP(itr)->bridx )

#define HS__SETTYP(set)       ( HS__IMP(set)->settyp )

#define HS__SMAP(Set)         ( HS__IMP(Set)->set.set.map )

#define HS__EQUAL(Set)        MAP_domequ(HS_Elm,MAP_MapTyp(HS__SMAP(Set)))
#define HS__HASH(Set)         MAP_domhsh(HS_Elm,MAP_MapTyp(HS__SMAP(Set)))

/*
#define HS__EQUAL(Set)        HMP_domequ(MAP_MapTyp(HS__SMAP(Set)))
#define HS__HASH(Set)         HMP_domhsh(MAP_MapTyp(HS__SMAP(Set)))
 does work with TURBOC 1.0
*/

#define HS__NRTYP(Nrel)       ( HS__IMP(Nrel)->set.nrel.tpltyp )
#define HS__NRMAP(Nrel)       ( HS__IMP(Nrel)->set.nrel.map )

#define HS__BRTYP(Brel)       ( HS__IMP(Brel)->set.brel.tpltyp )
#define HS__REF_BRMAPS(Brel)  ( HS__IMP(Brel)->set.brel.map )
#define HS__BRMAPS(Brel)      ( HS__IMP(Brel)->set.brel.maps )
#define HS__BRMAP(brel,i)     OT_GET(MAP(HS_Elm,NULL),HS__BRMAPS(brel),i)
#define HS__BRMAP_IDX(br,d)   MAP_apply(int,HS__REF_BRMAPS(br),d)
#define HS__BRMAP_NFD(br,d)   HS__BRMAP(br,ngetBRMap(br,d,True))
#define HS__BRMAP_OFD(br,d)   HS__BRMAP(br,HS__BRMAP_IDX(br,d))
#define HS__BRMAP_NFT(br,t,n) HS__BRMAP(br,ngetBRMap(br,HS__TPL_DOM(t,n),True))
#define HS__BRMAP_OFT(br,t,n) HS__BRMAP(br,HS__BRMAP_IDX(br,HS__TPL_DOM(t,n)))
#define HS__CLASSES(Brel)     ( HS__IMP(Brel)->set.brel.classes )
#define HS__CLASS(Brel,i)     ( HS__IMP(Brel)->set.brel.classes[i] )
#define HS__MINCLS(fp,d1,d2)  ( ( (*fp)(d1,d2) <= 0 ) ? d1 : d2 )

/* Error Macros */

#define BUG_HS_ARGCNT(c,m)    BUG_VMIN(c,m)
#define BUG_HS_SETTYP(l,r)    BUG_VEQU(compatibleTypes(l,r),True)

#define BUG_HS_REL(rel)       BUG_VNEQ(HS__SETTYP(rel),HS_T_SET)
#define BUG_HS_RELARGCNT(cnt) BUG_VEQU(((cnt) % 2) == 0 && (cnt) >= 4,True)
#define BUG_HS_RELIDX(rel,n)  BUG_RNG1(n,HS__TYP_ARITY(getTplTyp(rel)))
#define BUG_HS_TPLARITY(r,c)  BUG_VEQU(HS__TYP_ARITY(getTplTyp(r)),c)
#define BUG_HS_TPLIDX(tpl,n)  BUG_RNG1(n,HS__TPL_ARITY(tpl))
#define BUG_HS_JOIN(l,r,cols) BUG_VEQU(compatibleJoinCols(l,r,cols),True);

#define BUG_HS_ECLOSURE(brel) BUG_VEQU(equivalenceType(HS__SETTYP(brel)),True)
#define BUG_HS_CLASS(brel)    BUG_VEQU(HS__SETTYP(brel),HS_T_CLASS)
#define BUG_HS_ICLOSURE(brel) BUG_VEQU(HS__SETTYP(brel),HS_T_ICLOSURE)
#define BUG_HS_SDBREL(brel)   BUG_VEQU(singleDomBRel(brel),True)
#define BUG_HS_SDBRS(br,s)    BUG_VEQU(singleDomBRelSet(br,s),True)
#define BUG_HS_COMPOSE(d,l,r) BUG_VEQU(compatibleComposeSets(d,l,r),True);

/*========================= Auxiliary Functions ==============================*/

/*------------------- check, access & type primitives ------------------------*/

static MAP(HS_Elm,NULL) getSRMap(HS_Set set)
/* value map of set ( expects set type HS_T_SET or HS_T_NREL ) */
{
  return( ( HS__SETTYP(set) == HS_T_SET ) ? HS__SMAP(set) : HS__NRMAP(set) );
}

static StdCPtr* getTplTyp(HS_Set rel)
/* tuple type of rel ( expects relation, produces error on set ) */
{
  return
  (
    ( HS__SETTYP(rel) >= HS_T_BREL )
    ? HS__IMP(rel)->set.brel.tpltyp
    : ( HS__SETTYP(rel) == HS_T_NREL )
      ? HS__IMP(rel)->set.nrel.tpltyp : ( C_BUG, (StdCPtr*)NULL )
  );
}

static StdCPtr* newTplTyp(int arity)
/* creates a new type according arity */
{ StdCPtr* typ = (StdCPtr*)NewMem(sizeof(StdCPtr) * ( 2 * arity + 1 ));

  typ[0] = ABS_CAST(StdCPtr,2 * arity);
  return( typ );
}

static StdCPtr* copyTplTyp(StdCPtr* typ)
/* copies type ( expects tuple type ) */
{
   return( (StdCPtr*)BytCopy(typ,sizeof(StdCPtr) * HS__TYP_LEN(typ)) );
}

static StdCPtr* joinTplTyp(StdCPtr* l, StdCPtr* r)
/* creates a new type according l and r ( expects tuple types ) */
{ int argcnt = ( HS__TYP_ARITY(l) + HS__TYP_ARITY(r) ) * 2, i, j;
  StdCPtr* typ = (StdCPtr*)NewMem(sizeof(StdCPtr) * ( argcnt + 1 ));

  HS__TYP_COL(typ,0) = ABS_CAST(StdCPtr,argcnt);
  for( i=1; i <  HS__TYP_LEN(l); ++i ) HS__TYP_COL(typ,i) = HS__TYP_COL(l,i);
  for( j=1; i <= argcnt;    ++i, ++j ) HS__TYP_COL(typ,i) = HS__TYP_COL(r,j);
  return( typ );
}

static bool TplEqual(HS_Elm l, HS_Elm r);
static long TplHash(HS_Elm elm);

static void setNthDomTyp(StdCPtr* typ, int Nth, HS_Set set)
/* sets Nth domain type according set ( Parameter Check: CALL Function ) */
{
  if( HS__SETTYP(set) == HS_T_SET )
  {
    HS__TYP_EADR(typ,Nth) = HS__EQUAL(set);
    HS__TYP_HADR(typ,Nth) = HS__HASH(set);
  }
  else
  {
    HS__TYP_EADR(typ,Nth) = TplEqual;
    HS__TYP_HADR(typ,Nth) = TplHash;
  }
}

static bool TplTypEqual(StdCPtr* l, StdCPtr* r)
/* equal tuple types ( expects tuple types ) */
{ int cnt_l = HS__TYP_LEN(l), cnt_r = HS__TYP_LEN(r), i;

  if( cnt_l == cnt_r )
  {
    for( i=1; i < cnt_l; ++i ) 
      if( HS__TYP_COL(l,i) != HS__TYP_COL(r,i) ) return( False );
    return( True );
  }
  return( False );
}

static bool compatibleTypes(HS_Set l, HS_Set r)
/* whether the Types of the Sets/Rels l and r are compatible */
/* ( Parameter Check: CALL Function )                        */
{
  switch( HS__SETTYP(l) )
  {
    case HS_T_SET:
      return
      ( 
        ( HS__SETTYP(r) == HS_T_SET     &&
          HS__EQUAL(l)  == HS__EQUAL(r) &&
          HS__HASH(l)   == HS__HASH(r)   ) ? True : False
      );
    case HS_T_NREL:
      return
      ( 
        ( HS__SETTYP(r) == HS_T_NREL && TplTypEqual(getTplTyp(l),getTplTyp(r)) )
        ? True : False
      );
    default:
      return
      ( 
        ( TplTypEqual(getTplTyp(l),getTplTyp(r)) ) ? True : False
      );
  }
}

static bool compatibleJoinCols(HS_Set l, HS_Set r, StdCPtr* cols)
/* whether the Columns in cols are compatible with the Sets/Rels l and r */
/* ( Parameter Check: CALL Function )                                    */
{ StdCPtr* ltyp = getTplTyp(l); StdCPtr* rtyp = getTplTyp(r); 
  int cnt = intCAST(cols[0]), i, j;

  for( i=1, j=2; i < cnt; i+=2, j+=2 )
    if( intCAST(cols[i]) < 1 || intCAST(cols[i]) > HS__TYP_ARITY(ltyp)               ||
        intCAST(cols[j]) < 1 || intCAST(cols[j]) > HS__TYP_ARITY(rtyp)               || 
        HS__TYP_EQUAL(ltyp,intCAST(cols[i])) != HS__TYP_EQUAL(rtyp,intCAST(cols[j])) ||
        HS__TYP_HASH(ltyp,intCAST(cols[i]))  != HS__TYP_HASH(rtyp,intCAST(cols[j]))   )
      return( False );
  return( True );
}

static bool reflexiveType(int typ)
/* whether typ is reflexive */
{
  return( ( typ >= 0 ) ? *Property[typ] == 'r' : ( C_BUG, False ) );
}

static bool symmetricType(int typ)
/* whether typ is symmetric */
{
  return( ( typ >= 0 ) ? *(Property[typ]+1) == 's' : ( C_BUG, False ) );
}

static bool transitiveType(int typ)
/* whether typ is transitive */
{
  return( ( typ >= 0 ) ? *(Property[typ]+2) == 't' : ( C_BUG, False ) );
}

static bool equivalenceType(int typ)
/* whether typ is equivalent */
{
  return( ( typ >= 0 ) ? *(Property[typ]+3) == 'e' : ( C_BUG, False ) );
}

static bool singleDomBRel(HS_Set brel)
/* whether brel is a binary relation over a single domain */
/* ( Parameter Check: CALL Function )                     */
{ StdCPtr* typ = getTplTyp(brel);

  return
  ( 
    ( HS__SETTYP(brel) >= HS_T_BREL                &&
      HS__TYP_EQUAL(typ,1) == HS__TYP_EQUAL(typ,2) &&
      HS__TYP_HASH(typ,1)  == HS__TYP_HASH(typ,2)   ) ? True : False
  );
}

static bool singleDomBRelSet(HS_Set brel, HS_Set set)
/* whether brel is a binary relation over a single domain     */
/* with type according set ( Parameter Check: CALL Function ) */
{ StdCPtr* typ = getTplTyp(brel);
  
  return
  (
    ( singleDomBRel(brel)                    &&
      HS__SETTYP(set) == HS_T_SET            &&
      HS__TYP_EQUAL(typ,1) == HS__EQUAL(set) &&
      HS__TYP_HASH(typ,1)  == HS__HASH(set)   ) ? True : False
  );
}

static bool compatibleComposeSets(HS_Set dst, HS_Set left, HS_Set right)
/* whether sets could be composed ( Parameter Check: CALL Function ) */
{
  if( HS__SETTYP(dst)   >= HS_T_BREL &&
      HS__SETTYP(left)  >= HS_T_BREL &&
      HS__SETTYP(right) >= HS_T_BREL  )
  { StdCPtr* dtyp = getTplTyp(dst); StdCPtr* ltyp = getTplTyp(left);
    StdCPtr* rtyp = getTplTyp(right);

    if( HS__TYP_EQUAL(dtyp,1) == HS__TYP_EQUAL(ltyp,1) &&
        HS__TYP_HASH(dtyp,1)  == HS__TYP_HASH(ltyp,1)  &&
        HS__TYP_EQUAL(dtyp,2) == HS__TYP_EQUAL(rtyp,2) &&
        HS__TYP_HASH(dtyp,2)  == HS__TYP_HASH(rtyp,2)  &&
        HS__TYP_EQUAL(ltyp,2) == HS__TYP_EQUAL(rtyp,1) &&
        HS__TYP_HASH(ltyp,2)  == HS__TYP_HASH(rtyp,1)   ) return( True );
  }
  return( False );
}

/*--------------------------- tuple primitives -------------------------------*/

static HS_Elm newTpl(int arity)
/* creates a new tuple according arity */
{
  return( (HS_Elm)NewMem(sizeof(StdCPtr) * ( arity + 1 )) );
}

static HS_Elm copyTpl(HS_Elm tpl)
/* copies tpl ( expects tuple ) */
{
   if( TupleAlloc )
     return( (HS_Elm)BytCopy(tpl,sizeof(StdCPtr) * (HS__TPL_ARITY(tpl) + 1)) );
   else
     return( tpl );
}

static bool DomRngEqual(HS_Elm tpl, StdCPtr* domvals, bool domain)
/* equal domains/ranges, using dom functions      */
/* ( expects tuple and compatible domain values ) */
{ StdCPtr* typ = HS__TPL_TYP(tpl);
  int arity = HS__TYP_ARITY(typ), cols = intCAST(domvals[0]),
      fst = ( domain ) ? 1 : arity - cols + 1, lst = fst + cols - 1, i, j;
  
  for( i=fst, j=1; i <= lst; ++i, ++j )
  { bool (*equal)(HS_Dom l,HS_Dom r) = HS__TYP_EQUAL(typ,i);

    if( ! (*equal)(HS__TPL_DOM(tpl,i),(HS_Dom)domvals[j]) ) return( False );
  }
  return( True );
}

static bool JoinColEqual(HS_Elm l, HS_Elm r, StdCPtr* cols)
/* equal join columns ( expects compatible join tuples and columns ) */
{ StdCPtr* ltyp = HS__TPL_TYP(l); int cnt = intCAST(cols[0]), i, j;

  for( i=1, j=2; i < cnt; i+=2, j+=2 )
  { bool (*equal)(HS_Dom l,HS_Dom r) = HS__TYP_EQUAL(ltyp,intCAST(cols[i]));

    if( ! (*equal)(HS__TPL_DOM(l,intCAST(cols[i])),HS__TPL_DOM(r,intCAST(cols[j]))) ) 
      return( False );
  }
  return( True );
}

static bool TplEqual(HS_Elm l, HS_Elm r)
/* equal tuples, using dom functions ( expects tuples with equal types ) */
{ StdCPtr* typ = HS__TPL_TYP(l); int cnt = HS__TYP_ARITY(typ), i;
  
  for( i=1; i <= cnt; ++i )
  { bool (*equal)(HS_Dom l,HS_Dom r) = HS__TYP_EQUAL(typ,i);

    if( ! (*equal)(HS__TPL_DOM(l,i),HS__TPL_DOM(r,i)) ) return( False );
  }
  return( True );
}

static long TplHash(HS_Elm tpl)
/* tuple hash value, using dom functions ( expects tuple ) */
{ StdCPtr* typ = HS__TPL_TYP(tpl); long res = 0; 
  int cnt = HS__TYP_ARITY(typ), i;
  
  for( i=1; i <= cnt; ++i )
  { long (*hash)(HS_Dom dom) = HS__TYP_HASH(typ,i);

    res = combineOrderedHash(res,(*hash)(HS__TPL_DOM(tpl,i)));
  }
  return( res );
}

static HS_Elm copyTplElms(HS_Elm dst, HS_Elm src, bool reverse)
/* copies tuple cols, reverse = True: in reverse Order */
/* ( Parameter Check: CALL Function )                  */
{ int cnt = HS__TPL_ARITY(src), i, j;
  
  if( reverse )
    for( i=cnt, j=1; i >= 1; --i, ++j )
      HS__TPL_DOM(dst,j) = HS__TPL_DOM(src,i);
  else
    for( i=1; i <= cnt; ++i )
      HS__TPL_DOM(dst,i) = HS__TPL_DOM(src,i);
  return( dst );
}

/*------------------- equivalence class primitives ---------------------------*/

static void delClasses(HS_Set brel)
/* deletes the vector for dom classes ( expects binary relation ) */
{
  if( HS__CLASSES(brel) != (HS_Dom*)NULL ) 
  {
    FreeMem(HS__CLASSES(brel)); HS__CLASSES(brel) = (HS_Dom*)NULL;
  }
}

static bool mbrBTpl(HS_Set brel, HS_Dom c1, HS_Dom c2);

static BS_Set newClasses(HS_Set brel)
/* initializes dom class vector and marks classes of cardinality 1 */
/* ( expects binary relation )                                     */
{ INT cnt = OT_CNT(HS__BRMAPS(brel)); BS_Set mark = BS_create(cnt);
  MAPIT itr; HS_Dom dom; 

  delClasses(brel);
  HS__CLASSES(brel) = (HS_Dom*)NewMem(sizeof(HS_Dom) * cnt);
  HS__MAPITR(dom,itr,HS__REF_BRMAPS(brel)) 
  { INT mapidx = HS__BRMAP_IDX(brel,dom);

    HS__CLASS(brel,mapidx) = dom;
    if( MAP_count(HS__BRMAP(brel,mapidx)) == 1 && mbrBTpl(brel,dom,dom) )
      BS_setE(mapidx,mark);
  }
  return( mark );
}

static HS_Dom* copyClasses(HS_Set dst, HS_Set src)
/* copies dom class vector ( expects equal binary relations ) */
{
  delClasses(dst);
  return
  (
    HS__CLASSES(dst) =
    (HS_Dom*)BytCopy(HS__CLASSES(src),sizeof(HS_Dom) * OT_CNT(HS__BRMAPS(src)))
  );
}

static void joinClasses
            (
              HS_Set brel, HS_Dom l, HS_Dom r, int (*compare)(HS_Dom l,HS_Dom r)
            )
/* determines the new class representant for l and r */
/* ( Parameter Check: CALL Function )                */
{ INT ri = HS__BRMAP_IDX(brel,r), li = HS__BRMAP_IDX(brel,l);
  HS_Dom dom = ( HS__CLASS(brel,li) == HS__CLASS(brel,ri) )
               ? HS__CLASS(brel,li)
               : HS__MINCLS(compare,HS__CLASS(brel,li),HS__CLASS(brel,ri));

  HS__CLASS(brel,li) = HS__CLASS(brel,ri) =
    ( l == dom || r == dom )
    ? HS__MINCLS(compare,l,r)
    : HS__MINCLS(compare,dom,HS__MINCLS(compare,l,r));
}

static HS_Dom* setClasses(HS_Set brel, int (*compare)(HS_Dom l, HS_Dom r))
/* creates, sets dom class vector                                     */
/* ( expects equivalence relation !, Parameter Check: CALL Function ) */
{ BS_Set mark = newClasses(brel); INT cnt = BS_card(mark), i;

  for( i=0; i < cnt; ++i )
    if( ! BS_member(i,mark) )
    { MAPIT itr; HS_Elm elm;
  
      HS__MAPITR(elm,itr,HS__BRMAP(brel,i))
        if( HS__TPL_DOM(elm,1) != HS__TPL_DOM(elm,2) )
          joinClasses(brel,HS__TPL_DOM(elm,1),HS__TPL_DOM(elm,2),compare);
    }
  BS_delS(mark);
  return( HS__CLASSES(brel) );
}

/*--------------------------- map primitives ---------------------------------*/

static void ovrdomExtElm(HS_Elm elm,MAP(HS_Elm,NULL) map,HS_Set dst,HS_Set src)
/* MAP_ovrdom with type setting ( Parameter Check: CALL Function ) */
{
  if( HS__SETTYP(dst) != HS_T_SET )
  {
    HS__TPL_COL(elm,0) = dst; 
    MAP_ovrdom(map,elm,NULL); 
    HS__TPL_COL(elm,0) = src;
  }
  else MAP_ovrdom(map,elm,NULL);
}

static void dfndomExtElm(HS_Elm elm,MAP(HS_Elm,NULL) map,HS_Set dst,HS_Set src)
/* MAP_dfndom with type setting ( Parameter Check: CALL Function ) */
{
  if( HS__SETTYP(dst) != HS_T_SET )
  {
    HS__TPL_COL(elm,0) = dst; 
    MAP_dfndom(map,elm,NULL); 
    HS__TPL_COL(elm,0) = src;
  }
  else MAP_dfndom(map,elm,NULL);
}

/*--------------------- binary relation primitives ---------------------------*/

static INT ngetBRMap(HS_Set brel, HS_Dom dom, bool newMap)
/* returns map for dom, if exists, else creates new map for dom,       */
/* if newMap = True, else return -1 ( Parameter Check: CALL Function ) */
{ INT mapidx = -1;

  if( MAP_defined(HS__REF_BRMAPS(brel),dom) ) return( HS__BRMAP_IDX(brel,dom) );
  else
  {
    if( newMap )
    {
      mapidx =
        ( ! OT_CNT(HS__BRMAPS(brel)) )
        ? OT_T_INS
          (
            HS__BRMAPS(brel),
            MAP_newMap
            (MAP_newTyp(copyTpl,FreeMem,TplEqual,TplHash,primCopy,primFree))
          )
        : OT_T_INS(HS__BRMAPS(brel),MAP_newMap(MAP_MapTyp(HS__BRMAP(brel,0)))); 
  
      MAP_dfndom(HS__REF_BRMAPS(brel),dom,mapidx);
    }
    return( mapidx );
  }
}

static void delBRMap(HS_Set brel, HS_Dom dom, bool emptyMap)
/* deletes the map for dom, if exists ( and empty on emptyMap = True ) */
/* ( Parameter Check: CALL Function )                                  */
{ INT mapidx = ngetBRMap(brel,dom,False);

  if( mapidx >= 0 && ( ! emptyMap || MAP_emptyMap(HS__BRMAP(brel,mapidx)) ) )
  {
    OT_DEL_E(HS__BRMAPS(brel),mapidx);
    MAP_rmvdom(HS__REF_BRMAPS(brel),dom);
  }
}

static void itractBRMaps(HS_Set dst, HS_Set src, HS_Dom dom, int action)
/* iterates on Map(src,dom) and performs action on Map(dst,dom) */
/* ( dst != src !!!, Parameter Check: CALL Function )           */
{ MAPIT itr; HS_Elm elm; INT si = ngetBRMap(src,dom,False); 

  if( si >= 0 )
  { INT di = ngetBRMap(dst,dom,( action == HS_ACT_OVR ));

    if( di >= 0 ) HS__MAPITR(elm,itr,HS__BRMAP(src,si)) 
    {
      if( action == HS_ACT_OVR ) ovrdomExtElm(elm,HS__BRMAP(dst,di),dst,src);
      else
      {
        if( action == HS_ACT_RMV && MAP_defined(HS__BRMAP(dst,di),elm) )
          MAP_rmvdom(HS__BRMAP(dst,di),elm);
        else
        {
          if( action == HS_ACT_DFN && ! MAP_defined(HS__BRMAP(dst,di),elm) )
            dfndomExtElm(elm,HS__BRMAP(dst,di),dst,src);
        }
      }
    }
  }
}

static void setBTpl(HS_Set brel, HS_Dom c1, HS_Dom c2)
/* brel = brel U { (c1,c2) } ( Parameter Check: CALL Function ) */
{ StdCPtr elm[3];

  HS__TPL_COL(elm,0) = (StdCPtr)brel; 
  HS__TPL_COL(elm,1) = c1; HS__TPL_COL(elm,2) = c2;
  if( ! MAP_defined(HS__BRMAP_NFD(brel,c1),elm) )
    MAP_dfndom(HS__BRMAP_OFD(brel,c1),elm,NULL);
}

static bool mbrBTpl(HS_Set brel, HS_Dom c1, HS_Dom c2)
/* True: (c1,c2) in brel ( Parameter Check: CALL Function ) */
{ StdCPtr elm[3];

  HS__TPL_COL(elm,0) = (StdCPtr)brel; 
  HS__TPL_COL(elm,1) = c1; HS__TPL_COL(elm,2) = c2;
  if( MAP_defined(HS__REF_BRMAPS(brel),c1) &&
      MAP_defined(HS__BRMAP_OFD(brel,c1),elm) ) return( True );
  return( False );
}

static bool subBRel(HS_Set l, HS_Set r, bool equal)
/* l-Maps <= r-Maps, equal = True --> equality */
/* ( Parameter Check: CALL Function )          */
{ MAPIT itr; HS_Elm elm; HS_Dom dom;

  if( equal && MAP_count(HS__REF_BRMAPS(l)) != MAP_count(HS__REF_BRMAPS(r)) )
    return( False );
  HS__MAPITR(dom,itr,HS__REF_BRMAPS(l))
  { MAPIT t; INT lidx = HS__BRMAP_IDX(l,dom), ridx = ngetBRMap(r,dom,False);

    if( ridx >= 0 )
    { 
      if( equal && 
          MAP_count(HS__BRMAP(l,lidx)) != MAP_count(HS__BRMAP(r,ridx)) )
      { 
        MAP_freeItr(itr); return( False ); 
      }
      HS__MAPITR(elm,t,HS__BRMAP(l,lidx))
        if( ! MAP_defined(HS__BRMAP(r,ridx),elm) )
        { 
          MAP_freeItr(t); MAP_freeItr(itr); return( False ); 
        }
    }
    else { MAP_freeItr(itr); return( False ); }
  }
  return( True );
}

static HS_Set domrngBRel(HS_Set dst, HS_Set rel, HS_Dom domval, bool domain)
/* domain = True: Range(rel,domval), domain = False: Domain(rel,domval) */
/* ( expects compatible relations and domain values )                   */
{ MAPIT itr; HS_Elm elm;

  if( domain )
  {
    if( MAP_defined(HS__REF_BRMAPS(rel),domval) )
      HS__MAPITR(elm,itr,HS__BRMAP_OFD(rel,domval))
        MAP_ovrdom(HS__SMAP(dst),(HS_Elm)HS__TPL_DOM(elm,2),NULL);
  }
  else
  { StdCPtr elm[3];

    HS__TPL_COL(elm,0) = (StdCPtr)rel; HS__TPL_COL(elm,2) = domval;
    HS__MAPITR(HS__TPL_DOM(elm,1),itr,HS__REF_BRMAPS(rel))
      if( MAP_defined(HS__BRMAP_OFT(rel,elm,1),elm) )
        MAP_ovrdom(HS__SMAP(dst),(HS_Elm)HS__TPL_DOM(elm,1),NULL);
  }
  return( dst );
}

/*------------------------ set & relation primitives -------------------------*/

static bool emptySetRel(HS_Set set)              
/* True: set is empty ( Parameter Check: CALL Function ) */
{
  return
  ( 
    ( HS__SETTYP(set) < HS_T_BREL ) ? 
    MAP_emptyMap(getSRMap(set)) : MAP_emptyMap(HS__REF_BRMAPS(set)) 
  );
}

static HS_Set createTypedSet 
       (
         bool (*equal)(HS_Elm l, HS_Elm r), long (*hash)(HS_Elm elm)
       )
/* creates an empty set ( Parameter Check: CALL Function ) */
{ HSSET* set;

  set = (HSSET*)NewMem(sizeof(HSSET));
  HS__SETTYP(set) = HS_T_SET;
  HS__SMAP(set)   = 
    MAP_newMap(MAP_newTyp(primCopy,primFree,equal,hash,primCopy,primFree));
  return( HS__ADT(set) );
}

static HS_Set createTypedRel(StdCPtr* arglst)
/* creates an empty rel of type arglst ( Parameter Check: CALL Function ) */
{ HSSET* rel; MAPTY rmaptyp; int cnt;

  BUG_HS_RELARGCNT(cnt = intCAST(arglst[0]));
  rel = (HSSET*)NewMem(sizeof(HSSET));
  HS__SETTYP(rel) = ( cnt > 4 ) ? HS_T_NREL : HS_T_BREL;
  if( HS__SETTYP(rel) == HS_T_NREL ) HS__NRTYP(rel) = arglst;
  else                               HS__BRTYP(rel) = arglst;
  if( HS__SETTYP(rel) == HS_T_NREL )
  {
    rmaptyp = MAP_newTyp(copyTpl,FreeMem,TplEqual,TplHash,primCopy,primFree);
    HS__NRMAP(rel) = MAP_newMap(rmaptyp);
  }
  else
  { 
    rmaptyp = MAP_newTyp
              (
                primCopy, primFree, 
                HS__TYP_EQUAL(arglst,1), HS__TYP_HASH(arglst,1), 
                primCopy, primFree
              );
    HS__REF_BRMAPS(rel) = MAP_newMap(rmaptyp);
    HS__BRMAPS(rel) = OT_CREATE
                      (
                        MAP(HS_Elm,NULL),primCopy,MAP_freeMap,primEqual
                      );
    HS__CLASSES(rel) = (HS_Dom*)NULL;
  }
  return( HS__ADT(rel) );
}

static HS_Set createTypedSetRel(HS_Set set)
/* creates an empty set/rel with same type as set */
/* ( Parameter Check: CALL Function )             */
{ 
  return( 
          ( HS__SETTYP(set) == HS_T_SET )
          ? createTypedSet(HS__EQUAL(set),HS__HASH(set))
          : createTypedRel(copyTplTyp(getTplTyp(set)))
        );
}

static HS_Set createTypedDomRng(StdCPtr* typ, int cols)
/* creates an empty set/rel with same type as Range(typ,cols), */
/* if cols > 0, or as Domain(typ,cols), if cols < 0            */
/* ( Parameter Check: CALL Function )                          */
{ int arity = HS__TYP_ARITY(typ), cnt = ABS(cols);

  BUG_HS_ARGCNT(arity - cnt,0);
  if( HS__TYP_ARITY(typ) == cnt + 1 )
  {
    return
    ( 
      ( cols > 0 )
      ? createTypedSet( HS__TYP_EQUAL(typ,arity),HS__TYP_HASH(typ,arity) )
      : createTypedSet( HS__TYP_EQUAL(typ,1),HS__TYP_HASH(typ,1) )
    );
  }
  else
  { StdCPtr* rngtyp = newTplTyp(arity - cnt);
    int fst = ( cols > 0 ) ? cnt + 1 : 1, lst = fst + arity - cnt - 1, idx, i;

    for( i = fst, idx = 1; i <= lst; ++i, idx += 2 )
    {
      rngtyp[idx] = HS__TYP_EQUAL(typ,i); rngtyp[idx+1] = HS__TYP_HASH(typ,i);
    }
    return( createTypedRel(rngtyp) );
  }
}

static void dropSetRel(HS_Set set)
/* deletes set */
{ MAPTY maptyp = (MAPTY)NULL;

  if( HS__SETTYP(set) >= HS_T_NREL ) FreeMem(getTplTyp(set));
  if( HS__SETTYP(set) < HS_T_BREL )
  { MAP(HS_Elm,NULL) map = getSRMap(set);

    maptyp = MAP_MapTyp(map); MAP_freeMap(map);
  }
  else
  {
    if( OT_CNT(HS__BRMAPS(set)) > 0 ) maptyp = MAP_MapTyp(HS__BRMAP(set,0));
    OT_DEL_T(HS__BRMAPS(set));
    if( maptyp != (MAPTY)NULL ) MAP_freeTyp(maptyp);
    maptyp = MAP_MapTyp(HS__REF_BRMAPS(set)); MAP_freeMap(HS__REF_BRMAPS(set));
    delClasses(set);
  }
  MAP_freeTyp(maptyp);
  FreeMem(set);
}

static HS_Set clearSetRel(HS_Set set)
/* deletes elements ( Parameter Check: CALL Function ) */
{
  if( ! emptySetRel(set) )
  {
    if( HS__SETTYP(set) < HS_T_BREL ) MAP_rmvall(getSRMap(set));
    else
    { MAPTY rmaptyp = ( OT_CNT(HS__BRMAPS(set)) > 0 ) ?
                      MAP_MapTyp(HS__BRMAP(set,0)) : (MAPTY)NULL;
  
      HS__SETTYP(set) = HS_T_BREL;
      OT_CLEAR(HS__BRMAPS(set));
      if( rmaptyp != (MAPTY)NULL ) MAP_freeTyp(rmaptyp);
      MAP_rmvall(HS__REF_BRMAPS(set));
      delClasses(set);
    }
  }
  return( set );
}

static HS_Set copySetRelElms(HS_Set dst, HS_Set src, bool move)
/* copies the elements from src to dst                   */
/* ( dst != src !!!, expects compatible sets/relations ) */
{ MAPIT itr; HS_Elm elm; HS_Dom dom;
 
  if( ! emptySetRel(dst) ) clearSetRel(dst);
  if( HS__SETTYP(dst) < HS_T_BREL ) 
    HS__MAPITR(elm,itr,getSRMap(src)) 
      ovrdomExtElm(elm,getSRMap(dst),dst,src);
  else
    HS__MAPITR(dom,itr,HS__REF_BRMAPS(src))
      itractBRMaps(dst,src,dom,HS_ACT_OVR);
  if( move ) dropSetRel(src);
  return( dst );
}

static void setElm(HS_Elm elm, HS_Set set)
/* set = set U { elm } ( Parameter Check: CALL Function ) */
{
  if( HS__SETTYP(set) < HS_T_BREL ) MAP_ovrdom(getSRMap(set),elm,NULL);
  else
  {
    if( ! MAP_defined(HS__BRMAP_NFT(set,elm,1),elm) )
    {
      HS__SETTYP(set) = HS_T_BREL;
      MAP_dfndom(HS__BRMAP_OFT(set,elm,1),elm,NULL);
    }
  }
}

static void setExtElm(HS_Elm elm, HS_Set dst, HS_Set src)
/* dst = dst U { elm } with type setting ( Parameter Check: CALL Function ) */
{
  if( HS__SETTYP(dst) != HS_T_SET )
  {
    HS__TPL_COL(elm,0) = dst; setElm(elm,dst); HS__TPL_COL(elm,0) = src;
  }
  else setElm(elm,dst);
}

static void delElm(HS_Elm elm, HS_Set set)    
/* set = set \ { elm } ( Parameter Check: CALL Function ) */
{
  if( HS__SETTYP(set) < HS_T_BREL ) 
  { MAP(HS_Elm,NULL) map = getSRMap(set);

    if( MAP_defined(map,elm) ) MAP_rmvdom(map,elm);
  }
  else
  { HS_Dom dom = HS__TPL_DOM(elm,1); INT mapidx = ngetBRMap(set,dom,False);

    if( mapidx >= 0 && MAP_defined(HS__BRMAP(set,mapidx),elm) )
    {
      HS__SETTYP(set) = HS_T_BREL;
      MAP_rmvdom(HS__BRMAP(set,mapidx),elm);
      delBRMap(set,dom,True);
    }
  }
}

static bool mbrElm(HS_Elm elm, HS_Set set)    
/* True: elm in set ( Parameter Check: CALL Function ) */
{
  if( HS__SETTYP(set) < HS_T_BREL ) return( MAP_defined(getSRMap(set),elm) );
  else
  { HS_Dom dom = HS__TPL_DOM(elm,1);

    if( MAP_defined(HS__REF_BRMAPS(set),dom) )
      return( MAP_defined(HS__BRMAP(set,HS__BRMAP_IDX(set,dom)),elm) );
    else return( False );
  }
}

static HS_Set projectDomRng(HS_Set rel, StdCPtr* domvals, bool domain)
/* domain = True : Range(rel,domvals), else: Domain(rel,domvals) */
/* ( expects relation and compatible domain values )             */
{ StdCPtr* typ = getTplTyp(rel); HS_Set dst;
  int cols = intCAST(domvals[0]), arity = HS__TYP_ARITY(typ);

  dst = createTypedDomRng(typ,( domain ) ? cols : -cols);
  if( HS__SETTYP(rel) == HS_T_NREL )
  { MAPIT itr; HS_Elm elm; int idx;

    if( HS__SETTYP(dst) == HS_T_SET ) idx = ( domain ) ? arity : 1;
    else                              idx = ( domain ) ? cols  : 0;
    HS__MAPITR(elm,itr,HS__NRMAP(rel)) if( DomRngEqual(elm,domvals,domain) )
    { 
      if( HS__SETTYP(dst) > HS_T_SET )
      { StdCPtr tmp = HS__TPL_COL(elm,idx); 
        HS_Elm part = (HS_Elm)&HS__TPL_COL(elm,idx);

        HS__TPL_COL(elm,idx) = dst; 
        setElm(part,dst);
        HS__TPL_COL(elm,idx) = tmp;
      }
      else setElm((HS_Elm)HS__TPL_DOM(elm,idx),dst);
    }
  }
  else domrngBRel(dst,rel,(HS_Dom)domvals[1],domain);
  return( dst );
}

/*------------------ special binary relation primitives ----------------------*/

static HS_Set rclosure(HS_Set dst, HS_Set set) 
/* dst += ReflexiveHuelle(dst) ( Parameter Check: CALL Function ) */
{ MAPIT itr; HS_Elm elm; HS_Dom dom;

    if( ! emptySetRel(dst) )
    { INT cnt = OT_CNT(HS__BRMAPS(dst)), i;

      HS__MAPITR(dom,itr,HS__REF_BRMAPS(dst)) setBTpl(dst,dom,dom);
      for( i=0; i < cnt; ++i )
        HS__MAPITR(elm,itr,HS__BRMAP(dst,i))
          if( ! MAP_defined(HS__REF_BRMAPS(dst),HS__TPL_DOM(elm,2)) ||
              i != HS__BRMAP_IDX(dst,HS__TPL_DOM(elm,2))             )
            setBTpl(dst,HS__TPL_DOM(elm,2),HS__TPL_DOM(elm,2));
    }
    if( set != (HS_Set)NULL )
      HS__MAPITR(elm,itr,HS__SMAP(set)) setBTpl(dst,(HS_Dom)elm,(HS_Dom)elm);
  return( dst );
}

static HS_Set sclosure(HS_Set dst)             
/* dst += SymmetrischeHuelle(dst) ( Parameter Check: CALL Function ) */
{ MAPIT itr; HS_Elm elm; INT cnt = OT_CNT(HS__BRMAPS(dst)), i;

  for( i=0; i < cnt; ++i )
    HS__MAPITR(elm,itr,HS__BRMAP(dst,i))
      if( ! MAP_defined(HS__REF_BRMAPS(dst),HS__TPL_DOM(elm,2)) ||
          i != HS__BRMAP_IDX(dst,HS__TPL_DOM(elm,2))             )
        setBTpl(dst,HS__TPL_DOM(elm,2),HS__TPL_DOM(elm,1));
  return( dst );
}

static HS_Set tclosure(HS_Set dst)  
/* dst += TransitiveHuelle(dst) ( Parameter Check: CALL Function ) */
{ BS_Set mark = newClasses(dst); INT cnt = BS_card(mark), i, j, k;
  
  /* Warshall in N*N-Platz, vgl. Mehlhorn */
  for( i=0; i < cnt; ++i )
    if( ! BS_member(i,mark) )
      for( j=0; j < cnt; ++j )
        if( j != i && ! BS_member(j,mark) )
          for( k=0; k < cnt; ++k )
            if( k != i )
            {
              if( mbrBTpl(dst,HS__CLASS(dst,j),HS__CLASS(dst,i)) &&
                  mbrBTpl(dst,HS__CLASS(dst,i),HS__CLASS(dst,k))  )
                setBTpl(dst,HS__CLASS(dst,j),HS__CLASS(dst,k));
            }
  BS_delS(mark);
  return( dst );
}

static void Class(HS_Set dst, HS_Dom dom, OT_Tab domclass, BS_Set mark)
/* { dom' | dom' in [dom] } ( Parameter Check: CALL Function ) */
{ MAPIT itr; HS_Elm elm; INT domidx = HS__BRMAP_IDX(dst,dom);

  BS_setE(domidx,mark);
  OT_T_INS(domclass,dom); 
  HS__MAPITR(elm,itr,HS__BRMAP(dst,domidx)) 
    if( ! BS_member(HS__BRMAP_IDX(dst,HS__TPL_DOM(elm,2)),mark) ) 
      Class(dst,HS__TPL_DOM(elm,2),domclass,mark);
}

static HS_Set partition(HS_Set dst, int (*compare)(HS_Dom l, HS_Dom r))  
/* dst += AequivalenzHuelle(dst), sets all class representants      */
/* ( expects symmetric relation !, Parameter Check: CALL Function ) */
{ BS_Set mark = newClasses(dst); OT_Tab domclass = OT_CREATE_ADT(HS_Dom);
  INT cnt = BS_card(mark), i, j, k; 

  /* transitive closure of undirected graphs, Mehlhorn S. 180-181 */
  for( i=0; i < cnt; ++i )
    if( ! BS_member(i,mark) ) 
    {
      Class(dst,HS__CLASS(dst,i),domclass,mark);
      for( j=1; j < OT_CNT(domclass); ++j )
      { HS_Dom dom = OT_GET(HS_Dom,domclass,j);

        for( k=j-1; k >= 0; --k )
        { HS_Dom rng = OT_GET(HS_Dom,domclass,k);

          if( compare != (int (*)(HS_Dom l, HS_Dom r))NULL )
            joinClasses(dst,dom,rng,compare);
          setBTpl(dst,dom,rng); setBTpl(dst,rng,dom);
        }
      }
      OT_CLEAR(domclass);
    }
  OT_DEL_T(domclass); BS_delS(mark);
  return( dst );
}

static HS_Set conclusion(HS_Set dst, HS_Set brel)
/* dst = conclusion(brel) / dst = brel * brel <= brel        */
/* ( dst must be empty !!!, Parameter Check: CALL Function ) */
{ MAPIT itr; HS_Elm elm; INT cnt = OT_CNT(HS__BRMAPS(brel)), i;

  /* { e in brel | E e1,e2 in brel: e1[2]=e2[1], e1[1]=e[1], e2[2]=e[2] } */
  for( i=0; i < cnt; ++i )
  { 
    HS__MAPITR(elm,itr,HS__BRMAP(brel,i))
    { MAPIT t; HS_Elm e;

      HS__MAPITR(e,t,HS__BRMAP(brel,i)) 
        if( elm != e && mbrBTpl(brel,HS__TPL_DOM(e,2),HS__TPL_DOM(elm,2)) )
        {
          setExtElm(elm,dst,brel);
          MAP_freeItr(t); break;
        }
    }
  }
  return( dst );
}

/*========================= Interface Functions ==============================*/

/*I-------------------------- Set/Relation Iterator ------------------------- */

/*! No changes are allowed on the underlaying set/relation while iterating ! */

HS_Itr HS_createItr(HS_Set set)        
#define HS_CREATE_ITR HS_createItr
/* creates an iterator on set/relation 'set' */
{ HSITR* itr;

  BUG_NULL(set);
  itr = (HSITR*)NewMem(sizeof(HSITR));
  HS__ITR_SET(itr) = set;
  if( HS__SETTYP(set) < HS_T_BREL )
  {
    HS__ITR_IDX(itr) = -1;
    HS__ITR_ITR(itr) = MAP_newItr(getSRMap(set));
  }
  else
  {
    HS__ITR_IDX(itr) = 0;
    HS__ITR_ITR(itr) = ( OT_CNT(HS__BRMAPS(set)) ) ? 
                       MAP_newItr(HS__BRMAP(set,0)) : (MAPIT)NULL;
  }
  return( HS__ITR_ADT(itr) );
}

void HS_dropItr(HS_Itr itr)            
#define HS_DROP_ITR HS_dropItr
/* removes iterator 'itr' */
{
  BUG_NULL(itr);
  if( HS__ITR_ITR(itr) != (MAPIT)NULL ) MAP_freeItr(HS__ITR_ITR(itr));
  FreeMem(itr);
}

bool HS_emptyItr(HS_Itr itr)           
#define HS_EMPTY_ITR HS_emptyItr
/* whether iterator 'itr' is empty */
{
  BUG_NULL(itr);
  if( HS__SETTYP(HS__ITR_SET(itr)) < HS_T_BREL ) 
    return( MAP_emptyItr(HS__ITR_ITR(itr)) );
  else
  {
    return
    ( 
      ( HS__ITR_ITR(itr) == (MAPIT)NULL ) 
      ? True
      : ( HS__ITR_IDX(itr) < OT_CNT(HS__BRMAPS(HS__ITR_SET(itr))) - 1 )
        ? False
        : MAP_emptyItr(HS__ITR_ITR(itr))
    );
  }
}

void HS_get(HS_Itr itr, HS_Elm* elm)
#define HS_GET(itr,pElm) HS_get(itr,(HS_Elm*)(pElm))
/* get the next element from iterator 'itr' into 'elm' */
{
  BUG_NULL(itr); BUG_NULL(elm);
  TupleAlloc = False;
  if( HS__SETTYP(HS__ITR_SET(itr)) < HS_T_BREL ) 
    MAP_getItr(HS__ITR_ITR(itr),elm);
  else
  {
    BUG_NULL(HS__ITR_ITR(itr));
    if( MAP_emptyItr(HS__ITR_ITR(itr)) )
    {
      MAP_freeItr(HS__ITR_ITR(itr));
      HS__ITR_IDX(itr) += 1;
      HS__ITR_ITR(itr) = 
        MAP_newItr(HS__BRMAP(HS__ITR_SET(itr),HS__ITR_IDX(itr)));
    }
    MAP_getItr(HS__ITR_ITR(itr),elm);
  }
  TupleAlloc = True;
}

/*! <p><b>iterator macro for convenience</b> */

/*DOC_INTERFACE*/
#define HS_FORALL(elm,itr,set) for                            \
                               (                              \
                                 itr = HS_CREATE_ITR(set);    \
                                 HS_EMPTY_ITR(itr)            \
                                 ? (HS_DROP_ITR(itr), False)  \
                                 : (HS_GET(itr, ((StdCPtr)&elm)), True); \
                               )

/*I======================= Sets & Relations ================================= */

/*I------------------------- Creation of sets ------------------------------- */

HS_Set HS_createSet 
       (                                    /* function parameter:       */
         bool (*equal)(HS_Elm l, HS_Elm r), /* equality on set elements  */
         long (*hash)(HS_Elm elm)           /* hash value of set element */
       )
#define HS_CREATE_SET(type,equ,hsh)                                       \
        HS_createSet                                                      \
        (                                                                 \
          (bool (*)(HS_Elm l, HS_Elm r))(equ),(long (*)(HS_Elm elm))(hsh) \
        )
#define HS_CREATE_ADTSET(type) HS_CREATE_SET(type,primEqual,primHash)
/** creates a new set */
{
  BUG_NULL(equal); BUG_NULL(hash);
  return( createTypedSet(equal,hash) );
}

/*I---------------------- Basics for sets and relations --------------------- */

void HS_dropSet(HS_Set set)
#define HS_DROP_SET HS_dropSet
/* removes set/relation 'set' */
{ 
  BUG_NULL(set);
  dropSetRel(set);
}

HS_Set HS_clear(HS_Set set)
#define HS_CLEAR HS_clear
/* clears set/relation 'set'; removes all elements */
{
  BUG_NULL(set);
  return( clearSetRel(set) );
}

HS_Set HS_copy(HS_Set set)
#define HS_COPY HS_copy
/* copies set/relation 'set' */
{ HS_Set dst;

  BUG_NULL(set);
  dst = copySetRelElms((dst = createTypedSetRel(set)),set,False);
  if( HS__SETTYP(set) > HS_T_BREL )
  { 
    HS__SETTYP(dst) = HS__SETTYP(set);
    if( HS__SETTYP(dst) == HS_T_CLASS ) copyClasses(dst,set);
  }
  return( HS__ADT(dst) );
}

/*I-------------- Operations and predicates on one set/relation ------------- */

long HS_card(HS_Set set)
#define HS_CARD HS_card
/* cardinality of set/relation 'set' */
{
  BUG_NULL(set);
  if( HS__SETTYP(set) < HS_T_BREL ) return( MAP_count(getSRMap(set)) );
  else
  { long cnt = OT_CNT(HS__BRMAPS(set)), card = 0, i;

    for( i=0; i < cnt; ++i ) card += MAP_count(HS__BRMAP(set,i));
    return( card );
  }
}

bool HS_emptySet(HS_Set set)              
#define HS_EMPTY_SET HS_emptySet
/* whether set/relation 'set' is empty */
{
  BUG_NULL(set);
  return( emptySetRel(set) );
}

/*!! 
   The following functions can also be applied to relations.
   In this case the element represents a tuple.                   
*/

void HS_setElm(HS_Elm elm, HS_Set set)
#define HS_SET_ELM(elm,set) HS_setElm(ABS_CAST(HS_Elm,elm),set)
/* set = set U { elm } */
{
  BUG_NULL(set);
  if( HS__SETTYP(set) >= HS_T_NREL )
  {
    BUG_NULL(elm);
    if( set == (HS_Set)HS__TPL_COL(elm,0) ) setElm(elm,set);
    else
    { 
      BUG_HS_SETTYP(set,(HS_Set)HS__TPL_COL(elm,0));
      setExtElm(elm,set,(HS_Set)HS__TPL_COL(elm,0));
    }
  }
  else setElm(elm,set);
}

void HS_delElm(HS_Elm elm, HS_Set set)    
#define HS_DEL_ELM(elm,set) HS_delElm((HS_Elm)(elm),set)
/* set = set \ { elm } */
{
  BUG_NULL(set);
  if( HS__SETTYP(set) >= HS_T_NREL )
  {
    BUG_NULL(elm);
    if( set == (HS_Set)HS__TPL_COL(elm,0) ) delElm(elm,set);
    else
    { 
      BUG_HS_SETTYP(set,(HS_Set)HS__TPL_COL(elm,0));
      delElm(elm,set);
    }
  }
  else delElm(elm,set);
}

bool HS_mbrElm(HS_Elm elm, HS_Set set)    
#define HS_MBR_ELM(elm,set) HS_mbrElm((HS_Elm)(elm),set)
/* whether 'elm' is a member of set/relation 'set' */
{
  BUG_NULL(set);
  if( HS__SETTYP(set) >= HS_T_NREL )
  {
    BUG_NULL(elm);
    if( set == (HS_Set)HS__TPL_COL(elm,0) ) return( mbrElm(elm,set) );
    else
    { 
      BUG_HS_SETTYP(set,(HS_Set)HS__TPL_COL(elm,0));
      return( mbrElm(elm,set) );
    }
  }
  else return( mbrElm(elm,set) );
}

HS_Set HS_part(HS_Set set, bool (*wherepart)(HS_Elm elm))
#define HS_PART(set,where) HS_part(set,(bool (*)(HS_Elm elm))(where))
/* result = { e in set | wherepart(e) } */
{ HS_Set dst; MAPIT itr; HS_Elm elm;

  BUG_NULL(set); BUG_NULL(wherepart);
  dst = createTypedSetRel(set);
  if( HS__SETTYP(set) < HS_T_BREL )
  { MAP(HS_Elm,NULL) map = getSRMap(set);

    HS__MAPITR(elm,itr,map) 
      if( (*wherepart)(elm) ) setExtElm(elm,dst,set);
  }
  else
  { INT cnt = OT_CNT(HS__BRMAPS(set)), i;

    for( i=0; i < cnt; ++i )
      HS__MAPITR(elm,itr,HS__BRMAP(set,i)) 
        if( (*wherepart)(elm) ) setExtElm(elm,dst,set);
  }
  return( dst );
}

/*I------------- Operations and predicates on two sets/relations ------------ */

/*! <p>The predicate functions expects equal types ! */

bool HS_equal(HS_Set l, HS_Set r)
#define HS_EQUAL HS_equal
/* l = r ? */
{ MAPIT itr; HS_Elm elm;

  BUG_NULL(l); BUG_NULL(r); BUG_HS_SETTYP(l,r);
  if( l == r ) return( True );
  if( HS__SETTYP(l) < HS_T_BREL ) 
  {
    if( MAP_count(getSRMap(l)) == MAP_count(getSRMap(r)) )
    {
      HS__MAPITR(elm,itr,getSRMap(l))
        if( ! MAP_defined(getSRMap(r),elm) )
        { 
          MAP_freeItr(itr); return( False ); 
        }
      return( True );
    }
    else return( False );
  }
  else return( subBRel(l,r,True) );
}

bool HS_subset(HS_Set l, HS_Set r)              
#define HS_SUBSET HS_subset
/* l <= r ? */
{ MAPIT itr; HS_Elm elm;

  BUG_NULL(l); BUG_NULL(r); BUG_HS_SETTYP(l,r);
  if( l == r ) return( True );
  if( HS__SETTYP(l) < HS_T_BREL ) 
  {
    HS__MAPITR(elm,itr,getSRMap(l))
      if( ! MAP_defined(getSRMap(r),elm) )
      { 
        MAP_freeItr(itr); return( False ); 
      }
    return( True );
  }
  else return( subBRel(l,r,False) );
}

HS_Set HS_union(HS_Set dst, HS_Set l, HS_Set r) 
#define HS_UNION HS_union
/* dst = l U r */
{ MAPIT itr; HS_Elm elm; HS_Dom dom;

  BUG_NULL(dst); BUG_NULL(l); BUG_NULL(r);
  BUG_HS_SETTYP(dst,r); BUG_HS_SETTYP(l,r);
  if( dst == l && l == r ) return( dst );
  if( dst != l && dst != r && ! emptySetRel(dst) ) clearSetRel(dst);
  if( HS__SETTYP(dst) < HS_T_BREL ) 
  {
    if( dst != l )
      HS__MAPITR(elm,itr,getSRMap(l)) ovrdomExtElm(elm,getSRMap(dst),dst,l);
    if( dst != r )
      HS__MAPITR(elm,itr,getSRMap(r)) ovrdomExtElm(elm,getSRMap(dst),dst,r);
  }
  else
  {
    HS__SETTYP(dst) = HS_T_BREL;
    if( dst != l )
      HS__MAPITR(dom,itr,HS__REF_BRMAPS(l)) itractBRMaps(dst,l,dom,HS_ACT_OVR);
    if( dst != r )
      HS__MAPITR(dom,itr,HS__REF_BRMAPS(r)) itractBRMaps(dst,r,dom,HS_ACT_OVR);
  }
  return( dst );
}

HS_Set HS_minus(HS_Set dst, HS_Set l, HS_Set r) 
#define HS_MINUS HS_minus
/* dst = l \ r */
{ MAPIT itr; HS_Elm elm; HS_Dom dom; HS_Set tmp;

  BUG_NULL(dst); BUG_NULL(l); BUG_NULL(r);
  BUG_HS_SETTYP(dst,r); BUG_HS_SETTYP(l,r);
  if( l == r ) return ( clearSetRel(dst) );
  tmp = ( dst != l && dst != r ) ? clearSetRel(dst) : createTypedSetRel(dst);
  if( HS__SETTYP(dst) < HS_T_BREL ) 
  {
    HS__MAPITR(elm,itr,getSRMap(l)) 
      if( ! MAP_defined(getSRMap(r),elm) ) 
        ovrdomExtElm(elm,getSRMap(tmp),tmp,l);
  }
  else 
  {
    HS__MAPITR(dom,itr,HS__REF_BRMAPS(l))
    { MAPIT t; INT li = HS__BRMAP_IDX(l,dom), ri = ngetBRMap(r,dom,False);

      if( ri == -1 ) itractBRMaps(tmp,l,dom,HS_ACT_OVR);
      else
      {
        HS__MAPITR(elm,t,HS__BRMAP(l,li)) 
          if( ! MAP_defined(HS__BRMAP(r,ri),elm) )
            ovrdomExtElm(elm,HS__BRMAP_NFD(tmp,dom),tmp,l);
      }
    }
  }
  return( ( tmp != dst ) ? copySetRelElms(dst,tmp,True) : dst );
}

HS_Set HS_inter(HS_Set dst, HS_Set l, HS_Set r) 
#define HS_INTER HS_inter
/* dst = l & r */
{ MAPIT itr; HS_Elm elm; HS_Dom dom; HS_Set tmp;

  BUG_NULL(dst); BUG_NULL(l); BUG_NULL(r);
  BUG_HS_SETTYP(dst,r); BUG_HS_SETTYP(l,r);
  if( dst == l && l == r ) return( dst );
  tmp = ( dst != l && dst != r ) ? clearSetRel(dst) : createTypedSetRel(dst);
  if( HS__SETTYP(dst) < HS_T_BREL ) 
  {
    HS__MAPITR(elm,itr,getSRMap(l)) 
      if( MAP_defined(getSRMap(r),elm) ) ovrdomExtElm(elm,getSRMap(tmp),tmp,l);
  }
  else
  {
    HS__MAPITR(dom,itr,HS__REF_BRMAPS(l))
    { MAPIT t; INT li = HS__BRMAP_IDX(l,dom), ri = ngetBRMap(r,dom,False);

      if( ri >= 0 )
      {
        HS__MAPITR(elm,t,HS__BRMAP(l,li)) 
          if( MAP_defined(HS__BRMAP(r,ri),elm) )
            ovrdomExtElm(elm,HS__BRMAP_NFD(tmp,dom),tmp,l);
      }
    }
  }
  return( ( tmp != dst ) ? copySetRelElms(dst,tmp,True) : dst );
}

HS_Set HS_product(HS_Set l, HS_Set r, bool plane)           
#define HS_PRODUCT HS_product
/* result = l X r ( plane --> no tuple hierarchy ) */
{ StdCPtr* typ; HS_Set dst; HS_Itr i1; HS_Itr i2; HS_Elm e1; HS_Elm e2;

  BUG_NULL(l); BUG_NULL(r);
  if( ! plane || ( HS__SETTYP(l) == HS_T_SET && HS__SETTYP(r) == HS_T_SET ) )
  {
    typ = newTplTyp(2); setNthDomTyp(typ,1,l); setNthDomTyp(typ,2,r);
    dst = createTypedRel(typ);
    HS_FORALL(e1,i1,l) HS_FORALL(e2,i2,r) setBTpl(dst,(HS_Dom)e1,(HS_Dom)e2);
    if( l == r ) HS__SETTYP(dst) = HS_T_ECLOSURE;
  }
  else
  { StdCPtr styp[3]; HS_Elm tpl;
    HS_Set s = ( HS__SETTYP(l) == HS_T_SET ) 
               ? l : ( HS__SETTYP(r) == HS_T_SET ) 
                     ? r : (HS_Set)NULL;

    if( s != (HS_Set)NULL )
    {
      styp[0] = (StdCPtr)2; styp[1] = HS__EQUAL(s); styp[2] = HS__HASH(s);
      if( l == s ) typ = joinTplTyp(styp,getTplTyp(r));
      else         typ = joinTplTyp(getTplTyp(l),styp); 
      dst = createTypedRel(typ);
      tpl = newTpl(HS__TYP_ARITY(typ)); HS__TPL_COL(tpl,0) = (StdCPtr)dst;
      HS_FORALL(e1,i1,l) HS_FORALL(e2,i2,r) 
      {
        if( l == s )
        {
          HS__TPL_COL(tpl,1) = (StdCPtr)e1;
          copyTplElms((HS_Elm)(&HS__TPL_COL(tpl,1)),e2,False);
        }
        else
        {
          copyTplElms(tpl,e1,False); 
          HS__TPL_COL(tpl,HS__TYP_ARITY(typ)) = (StdCPtr)e2;
        }
        setElm(tpl,dst);
      }
    }
    else
    { StdCPtr* ltyp = getTplTyp(l);

      dst = createTypedRel(typ = joinTplTyp(ltyp,getTplTyp(r)));
      tpl = newTpl(HS__TYP_ARITY(typ)); HS__TPL_COL(tpl,0) = (StdCPtr)dst;
      HS_FORALL(e1,i1,l) HS_FORALL(e2,i2,r) 
      {
        copyTplElms(tpl,e1,False); 
        copyTplElms((HS_Elm)(&HS__TPL_COL(tpl,HS__TYP_ARITY(ltyp))),e2,False);
        setElm(tpl,dst);
      }
    }
    FreeMem(tpl);
  }
  return( dst );
}

/*I------------------------- Creation of relations -------------------------- */

HS_Set HS_createRel
       (                                    /* function parameter:                    */
         int argcnt,                        /* tuple arity; number of following pairs */
         bool (*equal)(HS_Dom l, HS_Dom r), /* equality on tuple components           */
         long (*hash)(HS_Dom d), ...        /* hash value of tuple component          */
       )
#define HS_CREATE_REL_2(t1,e1,h1,t2,e2,h2)    \
        HS_createRel                          \
        (                                     \
          4,                                  \
          (bool (*)(HS_Dom l, HS_Dom r))(e1), \
          (long (*)(HS_Dom d))(h1),           \
          (bool (*)(HS_Dom l, HS_Dom r))(e2), \
          (long (*)(HS_Dom d))(h2)            \
        )
#define HS_CREATE_ADTREL_2(t1,t2) \
        HS_CREATE_REL_2(t1,primEqual,primHash,t2,primEqual,primHash)
/** creates a new relation */
{ va_list args; StdCPtr* arglst;

  va_start(args,hash); 
  arglst = MakeArgLst(args,3,argcnt,equal,hash); 
  va_end(args);
  return( createTypedRel(arglst) );
}

/*I------------------------- Basics for relations --------------------------- */

int HS_arity(HS_Elm tpl)
#define HS_ARITY HS_arity
/* number of tuple components */
{
  BUG_NULL(tpl);
  return( HS__TPL_ARITY(tpl) );
}

HS_Dom HS_tplcol(HS_Elm tpl, int Nth)
#define HS_TPLCOL(typ,t,n) ((typ)HS_tplcol(t,n))
/* Nth tuple component ( Nth >= 1 ) */
{
  BUG_NULL(tpl); BUG_HS_TPLIDX(tpl,Nth);
  return( HS__TPL_DOM(tpl,Nth) );
}

/*I--------------- Operations and predicates on one relation ---------------- */

void HS_setTpl(int argcnt, HS_Set rel, HS_Dom dom, ...) 
#define HS_SETTPL_2(d1,d2,rel) HS_setTpl(3,rel,(HS_Dom)(d1),(HS_Dom)(d2))
/* rel = rel U { (dom,...) } */
{ va_list args; StdCPtr* arglst;

  BUG_NULL(rel); BUG_HS_TPLARITY(rel,argcnt-1);
  va_start(args,dom); 
  arglst = MakeArgLst(args,3,argcnt,rel,dom); 
  va_end(args);
  setElm((HS_Elm)&arglst[1],rel);
  FreeMem(arglst);
}

void HS_delTpl(int argcnt, HS_Set rel, HS_Dom dom, ...) 
#define HS_DELTPL_2(d1,d2,rel) HS_delTpl(3,rel,(HS_Dom)(d1),(HS_Dom)(d2))
/* rel = rel \ { (dom,...) } */
{ va_list args; StdCPtr* arglst;

  BUG_NULL(rel); BUG_HS_TPLARITY(rel,argcnt-1);
  va_start(args,dom); 
  arglst = MakeArgLst(args,3,argcnt,rel,dom); 
  va_end(args);
  delElm((HS_Elm)&arglst[1],rel);
  FreeMem(arglst);
}

bool HS_mbrTpl
     ( 
       int argcnt, HS_Set rel, HS_Dom dom, ...
     ) 
#define HS_MBRTPL_2(d1,d2,rel) HS_mbrTpl(3,rel,(HS_Dom)(d1),(HS_Dom)(d2))
/* whether (dom,...) is a member of relation 'rel' */
{ va_list args; StdCPtr* arglst; bool res;

  BUG_NULL(rel); BUG_HS_TPLARITY(rel,argcnt-1);
  va_start(args,dom); 
  arglst = MakeArgLst(args,3,argcnt,rel,dom); 
  va_end(args);
  res = mbrElm((HS_Elm)&arglst[1],rel);
  FreeMem(arglst);
  return( res );
}

HS_Set HS_project(HS_Set rel, int Nth)       
#define HS_PROJECT HS_project
/* result = rel.Nth column ( Nth >= 1 ) */
{ HS_Set dst; MAPIT itr; HS_Elm elm;

  BUG_NULL(rel); BUG_HS_RELIDX(rel,Nth);
  dst = createTypedSet
        (
          HS__TYP_EQUAL(getTplTyp(rel),Nth),HS__TYP_HASH(getTplTyp(rel),Nth)
        );
  if( HS__SETTYP(rel) == HS_T_NREL )
    HS__MAPITR(elm,itr,HS__NRMAP(rel)) 
      MAP_ovrdom(HS__SMAP(dst),(HS_Elm)HS__TPL_DOM(elm,Nth),NULL);
  else
  { INT cnt = OT_CNT(HS__BRMAPS(rel)), i;

    for( i=0; i < cnt; ++i )
      HS__MAPITR(elm,itr,HS__BRMAP(rel,i)) 
        MAP_ovrdom(HS__SMAP(dst),(HS_Elm)HS__TPL_DOM(elm,Nth),NULL);
  }
  return( dst );
}

HS_Set HS_range
       ( 
         int argcnt, HS_Set rel, HS_Dom dom, ...
       ) 
#define HS_RANGE_1(d,rel) HS_range(2,rel,(HS_Dom)(d))
/* result = Range((dom,...)) */
{ va_list args; StdCPtr* arglst; HS_Set dst;

  BUG_NULL(rel); BUG_HS_ARGCNT(argcnt,1); 
  va_start(args,dom); 
  arglst = MakeArgLst(args,3,argcnt,rel,dom); 
  va_end(args);
  arglst[1] = ABS_CAST(StdCPtr,(argcnt-1));
  dst = projectDomRng(rel,&arglst[1],True);
  FreeMem(arglst);
  return( dst );
}

HS_Set HS_domain
       ( 
         int argcnt, HS_Set rel, HS_Dom rng, ...
       ) 
#define HS_DOMAIN_1(r,rel) HS_domain(2,rel,(HS_Dom)(r))   
/* result = Domain((rng,...)) */
{ va_list args; StdCPtr* arglst; HS_Set dst;

  BUG_NULL(rel); BUG_HS_ARGCNT(argcnt,1); 
  va_start(args,rng); 
  arglst = MakeArgLst(args,3,argcnt,rel,rng); 
  va_end(args);
  arglst[1] = ABS_CAST(StdCPtr,(argcnt-1));
  dst = projectDomRng(rel,&arglst[1],False);
  FreeMem(arglst);
  return( dst );
}

HS_Set HS_trans(HS_Set rel)      
#define HS_TRANS HS_trans
/* R' (reverse elements) */
{ MAPIT itr; HS_Set dst; HS_Elm elm; HS_Elm tpl; 
  StdCPtr* typ; StdCPtr* reltyp; int arity, i, j;

  BUG_NULL(rel); BUG_HS_REL(rel);
  typ = newTplTyp(arity = HS__TYP_ARITY(reltyp = getTplTyp(rel))); 
  for( i=1, j=arity; i <= arity; ++i, --j )
  {
    HS__TYP_EADR(typ,j) = HS__TYP_EQUAL(reltyp,i);
    HS__TYP_HADR(typ,j) = HS__TYP_HASH(reltyp,i);
  }
  dst = createTypedRel(typ);
  tpl = newTpl(arity); HS__TPL_COL(tpl,0) = (StdCPtr)dst;
  if( HS__SETTYP(rel) == HS_T_NREL )
    HS__MAPITR(elm,itr,HS__NRMAP(rel)) setElm(copyTplElms(tpl,elm,True),dst);
  else
  { MAPIT t; HS_Dom dom;

    HS__MAPITR(dom,itr,HS__REF_BRMAPS(rel))
      HS__MAPITR(elm,t,HS__BRMAP_OFD(rel,dom))
        setElm(copyTplElms(tpl,elm,True),dst);
  }
  FreeMem(tpl);
  return( dst );
}

/*!! 
   The following functions can be applied only to binary relations 
   over a single domain ! 
*/

HS_Set HS_rclosure(HS_Set dst, HS_Set rel, HS_Set set) 
#define HS_IR_RCLOSURE     HS_rclosure
#define HS_R_RCLOSURE(d,r) HS_rclosure(d,r,(HS_Set)NULL)
/* dst = R + Id ( relation 'rel', domain 'set' ) */
{ int rtyp;

  BUG_NULL(dst); BUG_NULL(rel); BUG_HS_SETTYP(dst,rel); 
  if( set != (HS_Set)NULL ) BUG_HS_SDBRS(rel,set);
  else                      BUG_HS_SDBREL(rel);
  rtyp = HS__SETTYP(rel);
  if( rel != dst ) copySetRelElms(dst,rel,False);
  if( set != (HS_Set)NULL || ! reflexiveType(rtyp) )
  {
    rclosure(dst,set);
    HS__SETTYP(dst) = ( symmetricType(rtyp) && transitiveType(rtyp) ) 
                      ? HS_T_ECLOSURE
                      : ( symmetricType(rtyp) ) 
                        ? HS_T_RSCLOSURE 
                        : ( transitiveType(rtyp ) )
                          ? HS_T_CLOSURE : HS_T_RCLOSURE;
  }
  else HS__SETTYP(dst) = rtyp;
  return( dst );
}

HS_Set HS_sclosure(HS_Set dst, HS_Set rel)             
#define HS_SCLOSURE HS_sclosure
/* dst = R + R' */
{ int rtyp;

  BUG_NULL(dst); BUG_NULL(rel);
  BUG_HS_SETTYP(dst,rel); BUG_HS_SDBREL(rel);
  rtyp = HS__SETTYP(rel);
  if( rel != dst ) copySetRelElms(dst,rel,False);
  if( ! symmetricType(rtyp) )
  {
    sclosure(dst);
    HS__SETTYP(dst) = ( reflexiveType(rtyp) ) ? HS_T_RSCLOSURE : HS_T_SCLOSURE;
  }
  else HS__SETTYP(dst) = rtyp;
  return( dst );
}

HS_Set HS_closure(HS_Set dst, HS_Set rel, HS_Set set)  
#define HS_IR_CLOSURE     HS_closure
#define HS_R_CLOSURE(d,r) HS_closure(d,r,(HS_Set)NULL)
/* dst = R* ( relation 'rel', domain 'set' ) */
{ int rtyp;

  BUG_NULL(dst); BUG_NULL(rel); BUG_HS_SETTYP(dst,rel);
  if( set != (HS_Set)NULL ) BUG_HS_SDBRS(rel,set);
  else                      BUG_HS_SDBREL(rel);
  rtyp = HS__SETTYP(rel);
  if( rel != dst ) copySetRelElms(dst,rel,False);
  if( set != (HS_Set)NULL || ! symmetricType(rtyp) ) rclosure(dst,set);
  if( ! transitiveType(rtyp) )
  {
    if( symmetricType(rtyp) )
    {
      partition(dst,(int (*)(HS_Dom l, HS_Dom r))NULL);
      HS__SETTYP(dst) = HS_T_ECLOSURE;
    }
    else
    {
      tclosure(dst); HS__SETTYP(dst) = HS_T_CLOSURE;
    }
  }
  else HS__SETTYP(dst) = rtyp; 
  return( dst );
}

HS_Set HS_iclosure(HS_Set dst, HS_Set rel)             
#define HS_ICLOSURE HS_iclosure
/* dst = R+ */
{ int rtyp;

  BUG_NULL(dst); BUG_NULL(rel);
  BUG_HS_SETTYP(dst,rel); BUG_HS_SDBREL(rel);
  rtyp = HS__SETTYP(rel);
  if( rel != dst ) copySetRelElms(dst,rel,False);
  if( ! transitiveType(rtyp) ) 
  {
    if( symmetricType(rtyp) )
    {
      partition(dst,(int (*)(HS_Dom l, HS_Dom r))NULL);
      HS__SETTYP(dst) = HS_T_ECLOSURE;
    }
    else
    {
      tclosure(dst);
      HS__SETTYP(dst) = ( reflexiveType(rtyp) ) ? HS_T_CLOSURE : HS_T_ICLOSURE;
    }
  }
  else HS__SETTYP(dst) = rtyp; 
  return( dst );
}

HS_Set HS_eclosure
       (
         HS_Set dst, HS_Set rel, HS_Set set, int (*compare)(HS_Dom l, HS_Dom r)
       )
#define HS_IR_ECLOSURE       HS_eclosure
#define HS_R_ECLOSURE(d,r,c) HS_eclosure(d,r,(HS_Set)NULL,c)
/* dst = (R + R')* ( relation 'rel', domain 'set' and 'compare' ) */
{ int rtyp;

  BUG_NULL(dst); BUG_NULL(rel); BUG_HS_SETTYP(dst,rel);
  if( set != (HS_Set)NULL ) BUG_HS_SDBRS(rel,set);
  else                      BUG_HS_SDBREL(rel);
  rtyp = HS__SETTYP(rel);
  if( rel != dst ) copySetRelElms(dst,rel,False);
  if( set != (HS_Set)NULL ) rclosure(dst,set);
  if( ! equivalenceType(rtyp) ) 
  {
    if( ! symmetricType(rtyp) ) sclosure(dst); 
    partition(dst,compare);
  }
  else 
  {
    if( compare != (int (*)(HS_Dom l, HS_Dom r))NULL ) setClasses(dst,compare);
  }
  HS__SETTYP(dst) = ( compare != (int (*)(HS_Dom l, HS_Dom r))NULL )
                    ? HS_T_CLASS : HS_T_ECLOSURE;
  return( dst );
}

void HS_quotient(HS_Set eclosure,int (*compare)(HS_Dom l, HS_Dom r))
#define HS_QUOTIENT(ecl,cmp) \
        HS_quotient(ecl,(int (*)(HS_Dom l, HS_Dom r))(cmp))
/* re-sets class representants [eclosure] of partition 'eclosure' */
{
  BUG_NULL(eclosure); BUG_NULL(compare);
  BUG_HS_ECLOSURE(eclosure);
  setClasses(eclosure,compare);
  HS__SETTYP(eclosure) = HS_T_CLASS;
}

HS_Dom HS_class(HS_Dom dom, HS_Set eclosure)
#define HS_CLASS(typ,dom,ecl) ((typ)HS_class((HS_Dom)(dom),ecl))
/* get class representant [dom] of domain 'dom' in partition 'eclosure' */
{
  BUG_NULL(eclosure); BUG_HS_CLASS(eclosure);
  return( HS__CLASS(eclosure,HS__BRMAP_IDX(eclosure,dom)) );
}

HS_Set HS_kern(HS_Set dst, HS_Set iclosure)
#define HS_KERN HS_kern
/* dst = R+ \ square(R+) */
{ HS_Set tmp; MAPIT itr; HS_Dom dom;

  BUG_NULL(dst); BUG_NULL(iclosure);
  BUG_HS_SETTYP(dst,iclosure);
/*
  BUG_HS_ICLOSURE(iclosure);
*/
  tmp = createTypedSetRel(dst);
  conclusion(tmp,iclosure);
  if( dst == iclosure )
    HS__MAPITR(dom,itr,HS__REF_BRMAPS(tmp))
      itractBRMaps(dst,tmp,dom,HS_ACT_RMV);
  else
  { MAPIT t; HS_Elm elm;

    clearSetRel(dst);
    HS__MAPITR(dom,itr,HS__REF_BRMAPS(iclosure))
      HS__MAPITR(elm,t,HS__BRMAP_OFD(iclosure,dom))
        if( ! mbrElm(elm,tmp) ) setExtElm(elm,dst,iclosure);
  }
  dropSetRel(tmp);
  return( dst );
}

HS_Set HS_conclusion(HS_Set dst, HS_Set rel)
#define HS_CONCLUSION HS_conclusion
/* dst = square(R) */
{ HS_Set tmp;

  BUG_NULL(dst); BUG_NULL(rel);
  BUG_HS_SETTYP(dst,rel); BUG_HS_SDBREL(rel);
  tmp = ( dst != rel ) ? clearSetRel(dst) : createTypedSetRel(dst);
  conclusion(tmp,rel);
  return( ( tmp != dst ) ? copySetRelElms(dst,tmp,True) : dst );
}

/*I--------------- Operations and predicates on two relations --------------- */

HS_Set HS_join
       ( 
         int argcnt, HS_Set l, HS_Set r, /* ( long cl, long cr ) */ ...
       )
#define HS_JOIN(l,r)         HS_join(2,l,r)
#define HS_JOIN_1(l,r,cl,cr) HS_join(4,l,r,(long)(cl),(long)(cr))
/** joins two relations, using columns ( cl, cr ),... */
{ va_list args; StdCPtr* arglst; StdCPtr* typ; StdCPtr* ltyp;
  HS_Set dst; HS_Itr i1; HS_Itr i2; HS_Elm tpl; HS_Elm e1; HS_Elm e2;

  BUG_NULL(l); BUG_NULL(r);
  BUG_HS_ARGCNT(argcnt,1); BUG_HS_REL(l); BUG_HS_REL(r);
  va_start(args,r); 
  arglst = MakeArgLst(args,3,argcnt,l,r); 
  va_end(args);
  arglst[2] = ABS_CAST(StdCPtr,(argcnt-2));
  BUG_HS_JOIN(l,r,&arglst[2]);
  dst = createTypedRel((typ = joinTplTyp((ltyp = getTplTyp(l)),getTplTyp(r))));
  tpl = newTpl(HS__TYP_ARITY(typ)); HS__TPL_COL(tpl,0) = (StdCPtr)dst;
  HS_FORALL(e1,i1,l) HS_FORALL(e2,i2,r) 
    if( JoinColEqual(e1,e2,&arglst[2]) )
    {
      copyTplElms(tpl,e1,False); 
      copyTplElms((HS_Elm)(&HS__TPL_COL(tpl,HS__TYP_ARITY(ltyp))),e2,False);
      setElm(tpl,dst);
    }
  FreeMem(arglst); FreeMem(tpl);
  return( dst );
}

/*!! 
   The following functions can be applied only to binary relations !
*/

HS_Set HS_compose(HS_Set dst, HS_Set l, HS_Set r)  
#define HS_COMPOSE HS_compose
/* dst = l * r ( special binary relation --> binary relation ) */
{ HS_Set tmp; MAPIT itr; HS_Elm elm; INT cnt = OT_CNT(HS__BRMAPS(l)), i;

  BUG_NULL(dst); BUG_NULL(l); BUG_NULL(r);
  BUG_HS_COMPOSE(dst,l,r);
  tmp = ( dst != l && dst != r ) ? clearSetRel(dst) : createTypedSetRel(dst);
  /* { e | E e1 in l,e2 in r: e1[2]=e2[1], e1[1]=e[1], e2[2]=e[2] } */
  for( i=0; i < cnt; ++i )
  { 
    HS__MAPITR(elm,itr,HS__BRMAP(l,i))
    { MAPIT t; HS_Elm e;

      if( MAP_defined(HS__REF_BRMAPS(r),HS__TPL_DOM(elm,2)) )
        HS__MAPITR(e,t,HS__BRMAP_OFT(r,elm,2)) 
          setBTpl(tmp,HS__TPL_DOM(elm,1),HS__TPL_DOM(e,2));
    }
  }
  return( ( tmp != dst ) ? copySetRelElms(dst,tmp,True) : dst );
}

/*I---------------------------- Printing ------------------------------------ */

void HS_fprint                          
     (
       FILE* file,
       HS_Set set,
       int indent,
       void (*fpMember)(FILE *file, HS_Elm elm)
     )
#define HS_PRINT(set,ind,pMbr) \
        HS_fprint(STDOUT,set,(ind),(void (*)(FILE *file, HS_Elm elm))(pMbr))
/* prints set/relation 'set' to 'file' */
{ HS_Itr itr; HS_Elm elm; bool first = True;

  BUG_NULL(file); BUG_NULL(set); BUG_NULL(fpMember);
  HS_FORALL(elm,itr,set) 
  {
    if( first ) first = False;
    else        FPCHR(file,','); FNLIND(file);
    (*fpMember)(file,elm);
  }
}
