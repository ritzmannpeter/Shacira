/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [binset.c]                  Type: Binary Set                             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

/*I--------------------- Types and macros --------------------------------- */

/*!
   The elements in a binary set M with card(M) = N are represented by the numbers 0 .. N-1.
*/

AbstractType(BS_Set);           /* Abstract binary set type */

/*! <b>Element, row and column index</b> */
/*DOC_INTERFACE*/
#define BS_RELEL(l,r,maxC)      ( ( ( ( l ) - 1 ) * ( maxC ) ) + ( r ) )
                                /* r = SetElement 1 .. maxC */
                                /* l = SetElement 1 ..      */
#define BS_RIDX(v,maxC)         ( ( ( v ) - 1 ) / ( maxC ) + 1 )
#define BS_CIDX(v,maxC)         ( ( ( v ) - 1 ) % ( maxC ) + 1 )


typedef struct _BSET {
/* Strukturtyp fuer ( binaere ) Sets */
  INT card;
  char* bytes;
} BSET;

#define BS__ADT(set)            ( (BS_Set)(set) )
#define BS__IMP(set)            ( (BSET*)(set) )
#define BS__CARD(set)           ( (BS__IMP(set))->card )
#define BS__BYTES(set)          ( (BS__IMP(set))->bytes )
#define BS__BYTE(set,idx)       ( (BS__IMP(set))->bytes[idx] )

#define BUG_BS__SCMP(lft,rgt)   BUG_VEQU( BS__CARD(lft), BS__CARD(rgt) )
#define BUG_BS__GREL(rel,crd)   BUG_VEQU( (!(crd) && !BS__CARD(rel)) ||        \
                                          ((crd) && BS__CARD(rel)%(crd) == 0), \
                                          True )
#define BUG_BS__GMAT(rel,crd)   BUG_VEQU( BS__CARD(rel),(crd)*(crd) )
#define BUG_BS__GROW(l,rel,set) BUG_RNG1( (l),                   \
                                          ( BS__CARD(set) == 0 ) \
                                          ? 0 : BS__CARD(rel) / BS__CARD(set) )
/* BUG_BS__GROW produces an error, if cardinality of 'set' is 0 */ 
#define BUG_BS__CARD(crd)       BUG_VMIN( (crd), -1 )
#define BUG_BS__ELEM(el,crd)    BUG_RNG0( (el), (crd) )

/*I------------------------------- Basics --------------------------------- */

#define MASKE(e)      ( 1 << ( ( e ) % 8 ) )

static INT SetBytes(INT card)
{
  BUG_BS__CARD(card);
  return( ( card + 7 ) / 8 );
}

static INT SetByte(INT element, INT card)
{
  BUG_BS__ELEM(element,card);
  return( element >> 3 ); /* <==> element / 8 */
}

BS_Set BS_init(BS_Set set)
/* initializes set */
{
  INT i;

  BUG_NULL(set);
  for( i=0; i < SetBytes(BS__CARD(set)); ++i ) 
    BS__BYTE(set,i) = 0;
  return( set );
}

BS_Set BS_create(INT card)
/* creates a binary set */
{
  BSET* set = (BSET*)NewMem(sizeof(BSET));

  BS__BYTES(set) = (char*)NewMem(SetBytes(card));
  BS__CARD(set) = card;
  return( BS_init(BS__ADT(set)) );
}

INT BS_card(BS_Set set)
/* cardinality of set */
{
  BUG_NULL(set);
  return( BS__CARD(set) );
}

void BS_delS(BS_Set set)
/* deletes set */
{
  BUG_NULL(set);
  FreeMem( BS__BYTES(set) );
  FreeMem( set );
}

/*I----------------- Operations and predicates on one set ----------------- */

INT BS_setE(INT element, BS_Set set)
/* adds element to set */
{
  BUG_NULL(set);
  BS__BYTE(set,SetByte(element,BS__CARD(set))) |= MASKE(element);
  return( element );
}

void BS_delE(INT element, BS_Set set)
/* deletes element from set */
{
  BUG_NULL(set);
  BS__BYTE(set,SetByte(element,BS__CARD(set))) &= ~(MASKE(element));
}

bool BS_member(INT element, BS_Set set)
/* element in set ? */
{
  BUG_NULL(set);
  return
  ( 
    ( element < BS__CARD(set) ) 
    ? BS__BYTE(set,SetByte(element,BS__CARD(set))) & MASKE(element) : False
  );
}

bool BS_empty(BS_Set set)
/* empty set ? */
{
  INT i;

  BUG_NULL(set);
  for( i=0; i < SetBytes(BS__CARD(set)); ++i )
    if( BS__BYTE(set,i) | 0x00 )
      return( False );
  return( True );
}

INT BS_cnt(BS_Set set)
/* number of elements in set */
{
  INT cnt = 0;
  INT i;

  BUG_NULL(set);
  for( i=0; i < BS__CARD(set); ++i )
    if( BS_member(i,set) )
      ++cnt;
  return( cnt );
}

/*I---------------- Operations and predicates on two sets ----------------- */

bool BS_equal(BS_Set left, BS_Set right)
/* left = right ? */
{
  INT i;

  BUG_NULL(left);
  BUG_NULL(right);
  BUG_BS__SCMP(left,right);
  for( i=0; i < SetBytes(BS__CARD(left)); ++i )
    if( BS__BYTE(left,i) != BS__BYTE(right,i) )
      return( False );
  return( True );
}

bool BS_subset(BS_Set left, BS_Set right)
/* left <= right ? */
{
  INT i;

  BUG_NULL(left);
  BUG_NULL(right);
  BUG_BS__SCMP(left,right);
  for( i=0; i < SetBytes(BS__CARD(left)); ++i )
    if( BS__BYTE(left,i) & ~BS__BYTE(right,i) )
      return( False );
  return( True );
}

BS_Set BS_copy(BS_Set dst, BS_Set src)
/* copies src to dst */
{
  INT i;

  BUG_NULL(dst);
  BUG_NULL(src);
  BUG_BS__SCMP(dst,src);
  for( i=0; i < SetBytes(BS__CARD(dst)); ++i )
    BS__BYTE(dst,i) = BS__BYTE(src,i);
  return( dst );
}

BS_Set BS_union(BS_Set dst, BS_Set left, BS_Set right)
/* dst = left U right */
{
  INT i;

  BUG_NULL(dst);
  BUG_NULL(left);
  BUG_NULL(right);
  BUG_BS__SCMP(left,right);
  BUG_BS__SCMP(dst,left);
  for( i=0; i < SetBytes(BS__CARD(dst)); ++i )
    BS__BYTE(dst,i) = BS__BYTE(left,i) | BS__BYTE(right,i);
  return( dst );
}

BS_Set BS_minus(BS_Set dst, BS_Set left, BS_Set right)
/* dst = left - right */
{
  INT i;

  BUG_NULL(dst);
  BUG_NULL(left);
  BUG_NULL(right);
  BUG_BS__SCMP(left,right);
  BUG_BS__SCMP(dst,left);
  for( i=0; i < SetBytes(BS__CARD(dst)); ++i )
    BS__BYTE(dst,i) = BS__BYTE(left,i) & ~BS__BYTE(right,i);
  return( dst );
}

BS_Set BS_inter(BS_Set dst, BS_Set left, BS_Set right)
/* dst = left & right */
{
  INT i;

  BUG_NULL(dst);
  BUG_NULL(left);
  BUG_NULL(right);
  BUG_BS__SCMP(left,right);
  BUG_BS__SCMP(dst,left);
  for( i=0; i < SetBytes(BS__CARD(dst)); ++i )
    BS__BYTE(dst,i) = BS__BYTE(left,i) & BS__BYTE(right,i);
  return( dst );
}

/*I------------------------ Binary graph ---------------------------------- */

INT BS_setGE(BS_Set rel, INT SetCard, INT from, INT to)
/* adds a vertice, requires initialized rel */
{
  BUG_NULL(rel);
  BUG_BS__GREL(rel,SetCard);
  return( BS_setE(BS_RELEL(from,to,SetCard)-1,rel) );
}

BS_Set BS_setG(BS_Set rel, INT SetCard, bool (*isRel)(INT from, INT to))
/* adds vertices, requires initialized rel */
{
  INT i;

  BUG_NULL(rel);
  BUG_BS__GREL(rel,SetCard);
  BUG_NULL(isRel);
  for( i=1; i <= BS__CARD(rel); ++i )
    if( (*isRel)(BS_RIDX(i,SetCard)-1,BS_CIDX(i,SetCard)-1) )
      BS_setE(i-1,rel);
  return( rel );
}

BS_Set BS_copyR(BS_Set rel, BS_Set set, INT row, bool toGraph)
/* copies set to rel[row] (toGraph = True), rel[row] to set (toGraph = False) */
{
  INT i;

  BUG_NULL(rel);
  BUG_NULL(set);
  BUG_BS__GREL(rel,BS__CARD(set));
  BUG_BS__GROW(row,rel,set);
  if( toGraph )
  {
    for( i=0; i < BS__CARD(set); ++i )
      if( BS_member(i,set) )
        BS_setE(BS_RELEL(row,i+1,BS__CARD(set))-1,rel);
    return( rel );
  }
  else
  {
    for( i=0; i < BS__CARD(set); ++i )
      if( BS_member(BS_RELEL(row,i+1,BS__CARD(set))-1,rel) )
        BS_setE(i,set);
    return( set );
  }
}

INT BS_findR(BS_Set rel, BS_Set set)
/* searches row with rel[row] = set, returns
   row = 1 .. ( BS__CARD(rel) / BS__CARD(set) ) oder 0 
*/
{
  BS_Set TmpSet;
  INT MaxRow, i;

  BUG_NULL(rel);
  BUG_NULL(set);
  BUG_BS__GREL(rel,BS__CARD(set));
  TmpSet = BS_create(BS__CARD(set));
  MaxRow = ( BS__CARD(set) == 0 ) ? 0 : BS__CARD(rel) / BS__CARD(set);
  for( i=1; i <= MaxRow; ++i )
  {
    if( i > 1 )
      BS_init(TmpSet);
    BS_copyR(rel,TmpSet,i,False);
    if( BS_equal(set,TmpSet) )
      break;
  }
  BS_delS(TmpSet);
  return( ( i > MaxRow ) ? 0 : i );
}

/*! <br><b>The following functions require binary relations over a single domain.</b><br> */

BS_Set BS_trans(BS_Set rel, INT SetCard)
/* reverse relation / transponent matrix rel' */
{
  INT i;

  BUG_NULL(rel);
  BUG_BS__GMAT(rel,SetCard);
  for( i=1; i <= SetCard; ++i )
  {
    INT j;

    for( j=i+1; j <= SetCard; ++j )
    {
      INT element = BS_RELEL(j,i,SetCard) - 1;
      INT Telement = BS_RELEL(i,j,SetCard) - 1;

      if( BS_member(element,rel) && ! BS_member(Telement,rel) )
      {
        BS_delE(element,rel);
        BS_setE(Telement,rel);
      }
      else
      {
        if( BS_member(Telement,rel) && ! BS_member(element,rel) )
        {
          BS_delE(Telement,rel);
          BS_setE(element,rel);
        }
      }
    }
  }
  return( rel );
}

BS_Set BS_rclosure(BS_Set dst, BS_Set rel, INT SetCard)
/* reflexive closure dst = rel U id */
{
  INT i;

  BUG_NULL(dst);
  BUG_NULL(rel);
  BUG_BS__SCMP(dst,rel);
  BUG_BS__GMAT(dst,SetCard);
  BUG_BS__GMAT(rel,SetCard);
  BS_copy(dst,rel);
  for( i=1; i <= SetCard; ++i ) /* reflexive Huelle */
    BS_setE(BS_RELEL(i,i,SetCard)-1,dst);
  return( dst );
}

BS_Set BS_sclosure(BS_Set dst, BS_Set rel, INT SetCard)
/* symmetric closure dst = rel U rel' */
{ INT i, j;

  BUG_NULL(dst);
  BUG_NULL(rel);
  BUG_BS__SCMP(dst,rel);
  BUG_BS__GMAT(dst,SetCard);
  BUG_BS__GMAT(rel,SetCard);
  BS_copy(dst,rel);
  for( i=1; i <= SetCard; ++i ) /* symmetrische Huelle */
  {
    for( j=i+1; j <= SetCard; ++j )
    {
      INT element = BS_RELEL(j,i,SetCard) - 1;
      INT Telement = BS_RELEL(i,j,SetCard) - 1;

      if( BS_member(element,dst) )
        BS_setE(Telement,dst);
      if( BS_member(Telement,dst) )
        BS_setE(element,dst);
    }
  }
  return( dst );
}

/*INTERFACE_OFF*/
/* (Warshall) transitive closure dst = rel+ --- OLD VERSION 
BS_Set BS_iclosure(BS_Set dst, BS_Set rel, INT SetCard)
{
  BS_Set* h;
  INT i, j, k;

  BUG_NULL(dst);
  BUG_NULL(rel);
  BUG_BS__SCMP(dst,rel);
  BUG_BS__GMAT(dst,SetCard);
  BUG_BS__GMAT(rel,SetCard);
  h = (BS_Set*)NewMem(sizeof(BS_Set) * (SetCard+1));
  for( i=0; i <= SetCard; ++i )
    h[i] = BS_create(BS__CARD(rel));
  BS_copy(h[0],rel);
  for( k=1; k <= SetCard; ++k )
    for( i=1; i <= SetCard; ++i )
      for( j=1; j <= SetCard; ++j )
        if( BS_member(BS_RELEL(i,j,SetCard)-1,h[k-1]) ||
            BS_member(BS_RELEL(i,k,SetCard)-1,h[k-1]) &&
            BS_member(BS_RELEL(k,j,SetCard)-1,h[k-1]) )
          BS_setE(BS_RELEL(i,j,SetCard)-1,h[k]);
  BS_copy(dst,h[SetCard]);
  for( i=0; i <= SetCard; ++i )
    BS_delS(h[i]);
  FreeMem(h);
  return( dst );
}
*/
/*INTERFACE_ON*/

BS_Set BS_iclosure(BS_Set dst, BS_Set rel, INT SetCard)
/* (Warshall in N*N-Platz, vgl. Mehlhorn) transitive closure dst = rel+ */
{
  INT i, j, k;

  BUG_NULL(dst);
  BUG_NULL(rel);
  BUG_BS__SCMP(dst,rel);
  BUG_BS__GMAT(dst,SetCard);
  BUG_BS__GMAT(rel,SetCard);
  BS_copy(dst,rel);
  for( k=1; k <= SetCard; ++k ) /* transitive Huelle */
  {
    for( i=1; i <= SetCard; ++i )
    {
      if( i != k )
      {
        for( j=1; j <= SetCard; ++j )
        {
          if( j != k )
          {
            if( BS_member(BS_RELEL(i,k,SetCard)-1,dst) &&
                BS_member(BS_RELEL(k,j,SetCard)-1,dst)  )
              BS_setE(BS_RELEL(i,j,SetCard)-1,dst);
          }
        }
      }
    }
  }
  return( dst );
}

BS_Set BS_closure(BS_Set dst, BS_Set rel, INT SetCard)
/* (Warshall) transitive, reflexive closure dst = rel* */
{
  return( BS_iclosure(dst,BS_rclosure(dst,rel,SetCard),SetCard) );
}

BS_Set BS_eclosure(BS_Set dst, BS_Set rel, INT SetCard)
/* equivalence relation dst = (rel U rel')* */
{ 
  return( BS_closure(dst,BS_sclosure(dst,rel,SetCard),SetCard) );
}

BS_Set BS_kern(BS_Set dst, BS_Set rel, INT SetCard)
/* kernel dst = rel\square(rel), requires rel = strict order */
{ BS_Set h;
  INT i, j, k;

  BUG_NULL(dst);
  BUG_NULL(rel);
  BUG_BS__SCMP(dst,rel);
  BUG_BS__GMAT(dst,SetCard);
  BUG_BS__GMAT(rel,SetCard);
  h = BS_create(SetCard * SetCard);
  for( i=1; i <= SetCard; ++i ) /* Folgerungen */
    for( j=1; j <= SetCard; ++j )
      for( k=1; k <= SetCard; ++k )
        if( BS_member(BS_RELEL(i,k,SetCard)-1,rel) &&
            BS_member(BS_RELEL(k,j,SetCard)-1,rel) )
          BS_setE(BS_RELEL(i,j,SetCard)-1,h);
  BS_minus(dst,rel,h); /* Kern */
  BS_delS(h);
  return( dst );
}
