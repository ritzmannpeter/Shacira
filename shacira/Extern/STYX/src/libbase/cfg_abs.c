/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [cfg_abs.c]           Abstract Context Free Grammar                        */
/*                                                                            */
/* Copyright (c) 1993 by Doelle, Manns                                        */
/*----------------------------------------------------------------------------*/

#include "standard.h"
#include "hset.h"
#include "prs.h"

/*!
   <p>[cfg_abs] provides functions that derives the nonterminal and production classes 
   which constitutes the abstract context free grammar from a given parse table.

   <p>For further documentation of the definition of an abstract context free grammar 
   follow the reference to module <a href="prs_gen.htm">[prs_gen]</a>.<br><br>
*/

#include "binset.h"

/*I------------------------------- Macros ------------------------------------ */

/*!
   Properties of nonterminals and their classes
*/
/*DOC_INTERFACE*/
#define ACFG_NTTYP_LIST     1
#define ACFG_NTTYP_CLASS    2
#define ACFG_NTTYP_OPT      4
#define ACFG_NTTYP_NIL      8
#define ACFG_NTTYP_RECTYP   16
#define ACFG_NTTYP_REF0     32
#define ACFG_NTTYP_REF1     64
#define ACFG_NTTYP_START    128
#define ACFG_NTTYP_PRIM     256
#define ACFG_NTTYP_PRIMC    512
#define ACFG_NTTYP_EMPTY    1024
#define ACFG_NTTYP_RECREF   2048
#define ACFG_NTTYP_CONSREF  4096
#define ACFG_HAS_NTTYP(v,t) ( (((int)(v)) & ((int)(t))) > 0 )

/*I------------------------------- API --------------------------------------- */

bool acfg_init
     (
       PLR_Tab PTab, int** aPol, HS_Set** aNtm, HS_Set** aPrd, bool errmsg
     )
/* creates & fills 'aPol', 'aNtm', 'aPrd' from parse table 'PTab'
   'aPol' :- polymorph 'cons' classes
   'aNtm' :- nonterminal partition
   'aPrd' :- nonterminal class productions 
*/
{ bool ok = True; int cnt, i;
  *aPol = (int*)NewMem(PLR_nontermCnt(PTab)*sizeof(int));
  *aNtm = (HS_Set*)NewMem(PLR_nontermCnt(PTab)*sizeof(HS_Set));
  *aPrd = (HS_Set*)NewMem(PLR_nontermCnt(PTab)*sizeof(HS_Set));
  for (i = 0; i < PLR_nontermCnt(PTab); i++)
  {
    (*aPol)[i] = -1; (*aNtm)[i] = (HS_Set)NULL; (*aPrd)[i] = (HS_Set)NULL;
  }
  for (i = 0; i < PLR_nontermCnt(PTab); i++)
  { int clsidx = PLR_ntClassId(PTab,i);
    if( (*aNtm)[clsidx] == (HS_Set)NULL ) 
      (*aNtm)[clsidx] = HS_CREATE_ADTSET(int);
    HS_SET_ELM(PLR_tokenCnt(PTab)+i,(*aNtm)[clsidx]);
  }
  cnt = PLR_prodCnt(PTab) - PLR_startCnt(PTab);
  for (i = 0; i < cnt; i++) 
  { int clsidx = PLR_ntClassId(PTab,PLR_prodNonTerm(PTab,i)-PLR_tokenCnt(PTab));
    HS_Itr itr; HS_Elm elm;
    if( consProd(PLR_prodName(PTab,i)) )
    { int cnt = PLR_prodSymCnt(PTab,i), j;
      for( j=0; j < cnt; ++j )
      { int sym = PLR_prodSymbol(PTab,i,j), typ = PLR_symType(PTab,sym);
        if( CFG_TOK_NTM(typ) )
        {
          (*aPol)[clsidx] = ( CFG_NTM(typ) ) 
                            ? PLR_ntClassId(PTab,sym-PLR_tokenCnt(PTab)) 
                            : ( (*aPol)[clsidx] == -1       || 
                                (*aPol)[clsidx] == -(sym+2)  )
                              ? -(sym+2) : -(PLR_tokenCnt(PTab)+2);
          break;
        }
      }
    }
    if( ! nilProd(PLR_prodName(PTab,i))  && 
        ! consProd(PLR_prodName(PTab,i)) && 
        ! ignProd(PLR_prodName(PTab,i))   )
    {
      if( (*aPrd)[clsidx] == (HS_Set)NULL ) 
      {
        (*aPrd)[clsidx] = HS_CREATE_ADTSET(int);
        HS_SET_ELM(i,(*aPrd)[clsidx]);
      }
      else
      { bool exists = False;
        HS_FORALL(elm,itr,(*aPrd)[clsidx])
          if( ! strcmp(PLR_prodName(PTab,i),PLR_prodName(PTab,intCAST(elm))) )
            exists = True;
        if( ! exists ) HS_SET_ELM(i,(*aPrd)[clsidx]);
      }
    }
  }
  for (i = 0; i < PLR_nontermCnt(PTab); i++)
    if( PLR_ntClassId(PTab,i) == i                     && 
        (*aPol)[i] == -1 && (*aPrd)[i] == (HS_Set)NULL  )
    {
      ok = False;
      if( errmsg )
        fprintf
        (
          STDERR,"error : '%s' - nil without cons production",
          PLR_symName(PTab,PLR_tokenCnt(PTab)+i)
        );
    }
  return ok;
}

static bool SetOptNT(PLR_Tab PTab, int ntidx, HS_Set*aPrd, int* aPol)
{ HS_Itr itr;
  int    pidx, scnt, sym;
  HS_FORALL(pidx,itr,aPrd[ntidx])
  {
    scnt = PLR_prodSymCnt(PTab,pidx);
    if( scnt == 0 && ! nilProd(PLR_prodName(PTab,pidx)) )
    {
      aPol[ntidx] |= ACFG_NTTYP_OPT;
      HS_dropItr(itr); return True;
    }
    else
    if( scnt == 1 && ignProd(PLR_prodName(PTab,pidx)) )
    {
      sym = PLR_prodSymbol(PTab,pidx,0); 
      if( ACFG_HAS_NTTYP(aPol[sym-PLR_tokenCnt(PTab)],ACFG_NTTYP_OPT) ||
          SetOptNT(PTab,sym-PLR_tokenCnt(PTab),aPrd,aPol)              )
      {
        aPol[ntidx] |= ACFG_NTTYP_OPT;
        HS_dropItr(itr); return True;
      }
    }
  }
  return False;
}

static bool SetEmptyNT(PLR_Tab PTab, int ntidx, HS_Set*aPrd, int* aPol)
{ HS_Itr itr;
  int    pidx, scnt, sym, typ;
  HS_FORALL(pidx,itr,aPrd[ntidx])
  {
    scnt = PLR_prodSymCnt(PTab,pidx);
    if( scnt > 1 )
    {
      HS_dropItr(itr); return False;
    }
    else
    if( scnt == 1 )
    { 
      sym = PLR_prodSymbol(PTab,pidx,0); 
      typ = PLR_symType(PTab,sym);
      if( ! CFG_NTM(typ) || 
          ( ! ACFG_HAS_NTTYP(aPol[sym-PLR_tokenCnt(PTab)],ACFG_NTTYP_EMPTY) &&
            ( ! ignProd(PLR_prodName(PTab,pidx))                         ||
              ! SetEmptyNT(PTab,sym-PLR_tokenCnt(PTab),aPrd,aPol)         ) ) )
      {
        HS_dropItr(itr); return False;
      }
    }
  }
  aPol[ntidx] |= ACFG_NTTYP_EMPTY;
  return True;
}

static bool SetSimpleNT(PLR_Tab PTab, int ntidx, HS_Set*aPrd, int*aPol)
{ HS_Itr itr;
  int    pidx, scnt, sym, typ, i;
  HS_FORALL(pidx,itr,aPrd[ntidx])
  {
    scnt = PLR_prodSymCnt(PTab,pidx);
    for( i=0; i < scnt; ++i )
    { 
      sym = PLR_prodSymbol(PTab,pidx,i); 
      typ = PLR_symType(PTab,sym);
      if( CFG_NTM(typ)                                                   && 
          ! ACFG_HAS_NTTYP(aPol[sym-PLR_tokenCnt(PTab)],ACFG_NTTYP_PRIM) &&
          ( ! ignProd(PLR_prodName(PTab,pidx))                        ||
            ! SetSimpleNT(PTab,sym-PLR_tokenCnt(PTab),aPrd,aPol)       )  )
      {
        HS_dropItr(itr); return False;
      }
    }
  }
  aPol[ntidx] |= ACFG_NTTYP_PRIM;
  return True;
}

static int SingleExtClassRef(PLR_Tab PTab, HS_Set Cls, HS_Set* aRef)
{ HS_Itr itr1, itr2;
  int    res = -1, ntidx, pidx, pntidx;
  HS_FORALL(ntidx,itr1,Cls)
  {
    HS_FORALL(pidx,itr2,aRef[ntidx])
    { 
      pntidx = PLR_prodNonTerm(PTab,pidx)-PLR_tokenCnt(PTab);
      if( PLR_ntClassId(PTab,pntidx) != PLR_ntClassId(PTab,ntidx) )
      {
        if( res == -1 || res == ntidx ) res = ntidx;
        else
        {
          HS_dropItr(itr2); HS_dropItr(itr1); return -1;
        }
      }
    }
  }
  return res;
}

bool acfg_init_doc
     (
       PLR_Tab PTab, int** aPol, HS_Set** aNtm, HS_Set** aPrd
     )
/* creates & fills 'aPol', 'aNtm', 'aPrd' from parse table 'PTab',
   as needed for the generation of a refernce document
   'aPol' :- nonterminal/class types/properties
   'aNtm' :- nonterminal partition
   'aPrd' :- nonterminal productions
*/
{ bool    ok      = True; 
  int     ntcnt   = PLR_nontermCnt(PTab), 
          pcnt    = PLR_prodCnt(PTab) - PLR_startCnt(PTab), i, j;
  HS_Set* aRef    = (HS_Set*)NewMem(ntcnt*sizeof(HS_Set));
  BS_Set  ntrel   = BS_create(ntcnt * ntcnt);
  *aPol = (int*)NewMem(ntcnt*sizeof(int));
  *aNtm = (HS_Set*)NewMem(ntcnt*sizeof(HS_Set));
  *aPrd = (HS_Set*)NewMem(ntcnt*sizeof(HS_Set));
  for (i = 0; i < ntcnt; i++)
  {
    (*aPol)[i] = 0; 
    (*aNtm)[i] = (HS_Set)NULL;
    (*aPrd)[i] = HS_CREATE_ADTSET(int);
    aRef[i]    = HS_CREATE_ADTSET(int);
  }
  for (i = 0; i < ntcnt; i++)
  { int clsidx = PLR_ntClassId(PTab,i);
    if( (*aNtm)[clsidx] == (HS_Set)NULL ) 
      (*aNtm)[clsidx] = HS_CREATE_ADTSET(int);
    HS_SET_ELM(i,(*aNtm)[clsidx]);
  }
  for (i = 0; i < pcnt; i++) 
  { int ntidx  = PLR_prodNonTerm(PTab,i)-PLR_tokenCnt(PTab),
        clsidx = PLR_ntClassId(PTab,ntidx),
        scnt   = PLR_prodSymCnt(PTab,i);
    HS_SET_ELM(i,(*aPrd)[ntidx]);
    for( j=0; j < scnt; ++j )
    { int sym = PLR_prodSymbol(PTab,i,j), typ = PLR_symType(PTab,sym);
      if( CFG_NTM(typ) ) 
      {
        HS_SET_ELM(i,aRef[sym-PLR_tokenCnt(PTab)]);
        if( ntidx == sym-PLR_tokenCnt(PTab) )
        {
          (*aPol)[ntidx] |= ACFG_NTTYP_RECTYP;
          if( ignProd(PLR_prodName(PTab,i)) && scnt > 1 )
            BS_setGE(ntrel,ntcnt,ntidx+1,ntidx+1);
          else
          if( consProd(PLR_prodName(PTab,i)) )
          {
            if( ! ACFG_HAS_NTTYP((*aPol)[ntidx],ACFG_NTTYP_CONSREF) &&
                ( j == 0 || j == scnt - 1 ) )
              (*aPol)[ntidx] |= ACFG_NTTYP_CONSREF;
            else BS_setGE(ntrel,ntcnt,ntidx+1,ntidx+1);
          }
        }
        else BS_setGE(ntrel,ntcnt,ntidx+1,sym-PLR_tokenCnt(PTab)+1);
      }
    }
    if( nilProd(PLR_prodName(PTab,i)) || consProd(PLR_prodName(PTab,i)) )
      (*aPol)[clsidx] |= ACFG_NTTYP_LIST;
    if( scnt == 0 && nilProd(PLR_prodName(PTab,i)) )
      (*aPol)[ntidx] |= ACFG_NTTYP_NIL;
  }
  BS_iclosure(ntrel,ntrel,ntcnt);
  for (i = 0; i < ntcnt; i++)
  {
    SetSimpleNT(PTab,i,(*aPrd),(*aPol));
    SetEmptyNT(PTab,i,(*aPrd),(*aPol));
    SetOptNT(PTab,i,(*aPrd),(*aPol));
    if( BS_member(BS_RELEL(i+1,i+1,ntcnt)-1,ntrel) )
      (*aPol)[i] |= ACFG_NTTYP_RECREF;
    if( HS_CARD(aRef[i]) == 0 ) (*aPol)[i] |= ACFG_NTTYP_REF0;
    if( HS_CARD(aRef[i]) == 1 ) (*aPol)[i] |= ACFG_NTTYP_REF1;
  }
  for (i = 0; i < ntcnt; i++)
  { int clsidx = PLR_ntClassId(PTab,i), ntidx;
    if( i == clsidx &&
        ( ntidx = SingleExtClassRef(PTab,(*aNtm)[clsidx],aRef) ) >= 0 )
    { HS_Itr itr;
      bool   bSimple = True;
      (*aPol)[clsidx] |= ACFG_NTTYP_CLASS;
      HS_FORALL(j,itr,(*aNtm)[clsidx])
      {
        if( ACFG_HAS_NTTYP((*aPol)[j],ACFG_NTTYP_OPT) )
          (*aPol)[clsidx] |= ACFG_NTTYP_OPT;
        if( ACFG_HAS_NTTYP((*aPol)[j],ACFG_NTTYP_RECTYP) )
          (*aPol)[clsidx] |= ACFG_NTTYP_RECTYP;
        bSimple &= ACFG_HAS_NTTYP((*aPol)[j],ACFG_NTTYP_PRIM);
      }
      if( bSimple ) (*aPol)[clsidx] |= ACFG_NTTYP_PRIMC;
    }
  }
  for (i = 0; i < PLR_startCnt(PTab); i++) 
  { int ntidx = PLR_startSymbol(PTab,i) - PLR_tokenCnt(PTab);
    (*aPol)[ntidx] |= ACFG_NTTYP_START;
  }
  for (i = 0; i < ntcnt; i++)
    if( aRef[i] != (HS_Set)NULL ) HS_DROP_SET(aRef[i]);
  FreeMem(aRef);
  BS_delS(ntrel);
  return ok;
}

void acfg_quit(PLR_Tab PTab,int* aPol, HS_Set* aNtm, HS_Set* aPrd)
/* deletes 'aPol', 'aNtm' and 'aPrd'
   ( originally created from parse table 'PTab' )
 */
{ int i;
  for (i = 0; i < PLR_nontermCnt(PTab); i++)
  {
    if( aNtm[i] != (HS_Set)NULL ) HS_DROP_SET(aNtm[i]);
    if( aPrd[i] != (HS_Set)NULL ) HS_DROP_SET(aPrd[i]);
  }
  FreeMem(aPol);
  FreeMem(aNtm);
  FreeMem(aPrd);
}

