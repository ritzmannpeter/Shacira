/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [hmap.h]                   Type: Finite Map                              */
/*             Endliche Abbildungen mittels dynamischen Hashing             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef hmap_INCL
#define hmap_INCL


#include "standard.h"
#include "prim.h"


#ifdef __cplusplus
extern "C" {
#endif


/*  
   [hmap] implements finite maps based on dynamic hashing.
*/

/* ------------------------- Types and macros ------------------------------ */

AbstractType( HMP_Dom );                   /* Abstract domain type of maps  */
AbstractType( HMP_Rng );                   /* Abstract range type of maps   */

#define MAP(Alpha,Beta)   HMP_Map          /* Polymorphic MAP - Type        */
#define MAPIT             HMP_Itr          /* Polymorphic ITR - Type        */
#define MAPTY             HMP_Typ          /* Polymorphic meta-type of MAPs */

AbstractType( HMP_Typ )                    /* Abstract meta-type of maps    */
/* "Klasse" der Abbildungen */
;

ConcreteType( HMP_Ent )
/* interner Typ; Kette der Defintionen mit gleichem Hash-Wert */
;

typedef HMP_Ent __HUGE *HMP_Tab; /* interner Typ; das hash-array */

AbstractType( HMP_Map )                    /* Abstract type of maps          */
;

/* ------------------------- Meta type of hash maps ------------------------ */

HMP_Typ HMP_newTyp
        (                                          /* function parameter:    */
          HMP_Dom (*domcpy)(HMP_Dom a),            /* copies a domain        */
          void    (*domfre)(HMP_Dom a),            /* frees  a domain        */
          c_bool    (*domequ)(HMP_Dom a, HMP_Dom b), /* equality on domains    */
          long    (*domhsh)(HMP_Dom a),            /* hash value of domain   */
          HMP_Rng (*rngcpy)(HMP_Rng a),            /* copies a range         */
          void    (*rngfre)(HMP_Rng a)             /* frees  a range         */
        )
#define MAP_newTyp(dc, df, de, dh, rc, rf)                 \
        HMP_newTyp(                                        \
                    (HMP_Dom (*)(HMP_Dom a))           dc, \
                    (void    (*)(HMP_Dom a))           df, \
                    (c_bool    (*)(HMP_Dom a,HMP_Dom b)) de, \
                    (long    (*)(HMP_Dom a))           dh, \
                    (HMP_Rng (*)(HMP_Rng a))           rc, \
                    (void    (*)(HMP_Rng a))           rf  \
                  )
/** defines a new hash type */
;

void HMP_freeTyp( HMP_Typ t )
#define MAP_freeTyp HMP_freeTyp
/* frees hash type 't' */
;

HMP_Dom (*HMP_domcpy(HMP_Typ t))(HMP_Dom a)
#define MAP_domcpy(Alpha,t) ((Alpha (*)(Alpha a))          HMP_domcpy(t))
/* get domain copy function of hash type 't' */
;

void (*HMP_domfre(HMP_Typ t))(HMP_Dom a)
#define MAP_domfre(Alpha,t) ((void  (*)(Alpha a))          HMP_domfre(t))
/* get domain free function of hash type 't' */
;

c_bool (*HMP_domequ(HMP_Typ t))(HMP_Dom a, HMP_Dom b)
#define MAP_domequ(Alpha,t) ((c_bool  (*)(Alpha a, Alpha b)) HMP_domequ(t))
/* get domain equal function of hash type 't' */
;

long (*HMP_domhsh(HMP_Typ t))(HMP_Dom a)
#define MAP_domhsh(Alpha,t) ((long  (*)(Alpha a))          HMP_domhsh(t))
/* get domain hash function of hash type 't' */
;

HMP_Rng (*HMP_rngcpy(HMP_Typ t))(HMP_Rng a)
#define MAP_rngcpy(Beta ,t) ((Beta  (*)(Beta  a))          HMP_rngcpy(t))
/* get range copy function of hash type 't' */
;

void (*HMP_rngfre(HMP_Typ t))(HMP_Rng a)
#define MAP_rngfre(Beta ,t) ((void  (*)(Beta  a))          HMP_rngfre(t))
/* get range free function of hash type 't' */
;


/* =============================== Hash Maps ============================== */

/* -------------------------- Creating & Disposing ------------------------ */

HMP_Map HMP_newMap( HMP_Typ t )
#define MAP_newMap  HMP_newMap
/* creates a new empty map */
;

void HMP_freeMap(HMP_Map m)
#define MAP_freeMap HMP_freeMap
/* removes map 'm' from storage
   all references to 'm' are invalidated!
*/
;


/* ------------------------------- Accessing ------------------------------ */

HMP_Typ HMP_MapTyp(HMP_Map m)
#define MAP_MapTyp HMP_MapTyp
/* get meta-type of map 'm' */
;

long HMP_count(HMP_Map m)
#define MAP_count HMP_count
/* number of domain values on which map 'm' is defined
   HMP_count(m) == | { d in HMP_Dom | HMP_defined(m,d) } |
*/
;

c_bool HMP_emptyMap(HMP_Map m)
#define MAP_emptyMap HMP_emptyMap
/* whether map 'm' is empty
   HMP_emptyMap(m) == (HMP_count(m) == 0)
*/
;

c_bool HMP_defined(/* con */ HMP_Map m, /* con */ HMP_Dom d)
#define MAP_defined(m,d) HMP_defined(m,(HMP_Dom)(d))
/* whether domain 'd' is defined in map 'm' */
;

HMP_Rng HMP_apply(/* con */ HMP_Map m, /* con */ HMP_Dom d)
#define MAP_apply(Beta,m,d)       ((Beta)HMP_apply(m,(HMP_Dom)(d)))
#define MAP_apply_small(Beta,m,d) ((Beta)((long)HMP_apply(m,(HMP_Dom)(d))))
#define MAP_apply_short(m,d)      ((short)((long)HMP_apply(m,(HMP_Dom)(d))))
/* get range of domain 'd' in map 'm'
   raises execption if not HMP_defined(m,d)
*/
;


/* ------------------------------ Modifying ------------------------------- */

void HMP_ovrdom(/* var */ HMP_Map m, /* con */ HMP_Dom d, /* con */ HMP_Rng r)
#define MAP_ovrdom(m,d,r) HMP_ovrdom(m,(HMP_Dom)(d),(HMP_Rng)(r))
/* defines pair ( 'd', 'r' ) or updates range of domain 'd' in map 'm'
   m := m \ { (d, r) }
*/
;

void HMP_dfndom(/* var */ HMP_Map m, /* con */ HMP_Dom d, /* con */ HMP_Rng r)
#define MAP_dfndom(m,d,r) HMP_dfndom(m,(HMP_Dom)(d),(HMP_Rng)(r))
#define MAP_define        MAP_dfndom
/* defines pair ( 'd', 'r' ) in map'm'
   m := m U { (d, r) }; raises exception if HMP_defined(m,d)
*/
;

void HMP_upddom(/* var */ HMP_Map m, /* con */ HMP_Dom d, /* con */ HMP_Rng r)
#define MAP_upddom(m,d,r) HMP_upddom(m,(HMP_Dom)(d),(HMP_Rng)(r))
#define MAP_update        MAP_upddom
/* updates range of domain 'd' in map 'm'
   m := m \ { (d, r) }; raises exception if not HMP_defined(m,d)
*/
;

void HMP_rmvdom(/* con */ HMP_Map m, /* con */ HMP_Dom d)
#define MAP_rmvdom(m,d) HMP_rmvdom(m,(HMP_Dom)(d))
#define MAP_remove      MAP_rmvdom
/* removes domain 'd' from map 'm'
   makes m(d) be undefined; raises exception if not HMP_defined(m,d)
*/
;

void HMP_rmvall(/* var */ HMP_Map m)
#define MAP_rmvall HMP_rmvall
/* clears map 'm'
   makes m(d) be undefined for all d
*/
;


/* --------------------- Basic hash set iterator -------------------------- */

/*   Do not modify the content of an hash set
     while using a basic iterator on this set.
*/

AbstractType( HMP_Itr  )              /* Abstract type of iterators on maps */
;

/* ------------------------- Creating & Disposing ------------------------- */

HMP_Itr HMP_newItr(HMP_Map m)
#define MAP_newItr HMP_newItr
/* creates an iterator on hash set 'm' */
;

void HMP_freeItr(HMP_Itr i)
#define MAP_freeItr HMP_freeItr
/* removes iterator 'i' */
;


/* ------------------------ Accessing & Modifiying ------------------------ */

c_bool HMP_emptyItr(HMP_Itr i)
#define MAP_emptyItr HMP_emptyItr
/* whether iterator 'i' is empty */
;

void HMP_getItr(HMP_Itr i, HMP_Dom *d)
#define MAP_getItr(i,d) HMP_getItr(i,(HMP_Dom *) d)
/* get the next domain from iterator 'i' into 'd'
   raises exception if 'HMP_emptyItr(i)'
*/
;

void HMP_getItrAsg(HMP_Itr i, HMP_Dom *d, HMP_Rng *r)
#define MAP_getItrAsg(i,d,r) HMP_getItrAsg(i,(HMP_Dom *)(d),(HMP_Rng *)(r))
/* get the next pair ( domain, range ) from iterator 'i' into 'd' and 'r'
   raises exception if 'HMP_emptyItr(i)'
*/
;


/* ---------------------- Convenient iterator macros ----------------------- */

/*   For - statement with basic iterators. Make sure to
     free the iterator if you leave the loop via break.
*/

#define MAP_forItr(DomVar,ItrVar,MapExpr)           \
        for (ItrVar = MAP_newItr(MapExpr);          \
             MAP_emptyItr(ItrVar)                   \
             ? (MAP_freeItr(ItrVar),         C_False) \
             : (MAP_getItr(ItrVar, &DomVar), C_True );\
            )

#define MAP_forItrAsg(DomVar,RngVar,ItrVar,MapExpr)             \
        for (ItrVar = MAP_newItr(MapExpr);                      \
             MAP_emptyItr(ItrVar)                               \
             ? (MAP_freeItr(ItrVar),         C_False)             \
             : (MAP_getItrAsg(ItrVar, &DomVar, &RngVar), C_True );\
            )

/* ------------------------------- Printing ------------------------------- */

void HMP_fprintMap
     (
       FILE     *f,
       HMP_Map   m,
       int       indent,
       void    (*fprintPair)(FILE *f, HMP_Dom d, HMP_Rng r, int indent)
     )
#define MAP_fprintMap HMP_fprintMap
/* prints map 'm' to file 'f' */
;

void HMP_printMap
     (
       HMP_Map  m,
       int      indent,
       void    (*printPair)(HMP_Dom d, HMP_Rng r, int indent)
     )
#define MAP_printMap HMP_printMap
/* prints map 'm' to 'stdout' */
;


/* ------------------- Debugging & Profiling ------------------------------ */

void HMP_technicalView
     (
       HMP_Map m,
       int     indent,
       void  (*printPair)(HMP_Dom d, HMP_Rng r, int indent)
     )
/* For visual inspection and debugging purposes */
;


/* ---------------------------- Primitive Maps ---------------------------- */

/*  
   Primitive maps have an implicit meta-type which treats the
   domain and range values as anonymous pointer.
   The domain / range copy function return the element itself.
   The domain / range free function do nothing.
   The domain equal function performs a simple '==' operation.
   The domain hash function simply hashes the domain ( pointer ) value.
*/

void MAP_init(void);              /* inits this module ( create meta-type ) */
void MAP_quit(void);              /* quits this module ( free meta-type )   */
 MAP(_,_) MAP_newPrimMap(void);        /* creates a primitive map           */

c_bool MAP_prim_equal(MAP(_,_) a, MAP(_,_) b)
/* whether the primitive maps 'a' and 'b' are equal */
;

 MAP(_,_) MAP_prim_copy(MAP(_,_) a);   /* copies the primitive map 'a'      */


#ifdef __cplusplus
}
#endif

#endif
