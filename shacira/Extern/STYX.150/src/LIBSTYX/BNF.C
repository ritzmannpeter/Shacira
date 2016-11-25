/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [bnf.c]                      Type: BNF                                   */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "prs_dfn.h"

#include "prs.h"

/*!!
   [bnf] implements a more abstract interface to the more technical definition
   of a context free grammar, provided by the above parse module [prs].
*/

/*I---------------------- Types --------------------------------------------- */

AbstractType(BNF_BNF); /* Abstract BNF type               */
AbstractType(BNF_NTM); /* Abstract nonterminal type       */
AbstractType(BNF_TOK); /* Abstract token type             */
AbstractType(BNF_KEY); /* Abstract keyword type           */
AbstractType(BNF_PRD); /* Abstract production type        */
AbstractType(BNF_MBR); /* Abstract production symbol type */

typedef struct _BNFTAB {
/* BNF-Srachbeschreibung */
  PLR_Tab PTab;   /* Parse-Tabelle mit KFG-Informationen        */
  int TokCnt;     /* Anzahl Terminalsymbole vom Typ PLR_TYP_TOK */
  int* Tok;       /* Token                                      */
  int KeyCnt;     /* Anzahl Terminalsymbole vom Typ PLR_TYP_KEY */
  int* Key;       /* Keys                                       */
  int* FstNtProd; /* 1. Produktion jedes Nonterminals           */
  int* NtProdCnt; /* Anzahl der Produktionen jedes Nonterminals */
} BNFTAB;

#define BNF_B_IMP(bnf)           ( (BNFTAB*)(bnf) )
#define BNF_N_IMP(ntm)           ( (int)(ntm) )
#define BNF_T_IMP(tok)           ( (int)(tok) )
#define BNF_K_IMP(key)           ( (int)(key) )
#define BNF_M_IMP(mbr)           ( (int)(mbr) )
#define BNF_P_IMP(prd)           ( (int)(prd) )

#define BNF_PTAB(bnf)            ( BNF_B_IMP(bnf)->PTab )
#define BNF_TCNT(bnf)            ( BNF_B_IMP(bnf)->TokCnt )
#define BNF_TSYMS(bnf)           ( BNF_B_IMP(bnf)->Tok )
#define BNF_TSYM(bnf,idx)        ( BNF_B_IMP(bnf)->Tok[idx] )
#define BNF_KCNT(bnf)            ( BNF_B_IMP(bnf)->KeyCnt )
#define BNF_KSYMS(bnf)           ( BNF_B_IMP(bnf)->Key )
#define BNF_KSYM(bnf,idx)        ( BNF_B_IMP(bnf)->Key[idx] )
#define BNF_PCNTS(bnf)           ( BNF_B_IMP(bnf)->NtProdCnt )
#define BNF_PCNT(bnf,idx)        ( BNF_B_IMP(bnf)->NtProdCnt[idx] )
#define BNF_FSTPS(bnf)           ( BNF_B_IMP(bnf)->FstNtProd )
#define BNF_FSTP(bnf,idx)        ( BNF_B_IMP(bnf)->FstNtProd[idx] )

#define BUG_BNF_START(bnf,nth)   BUG_RNG1(nth,BNF_startCnt(bnf))
#define BUG_BNF_NTM(bnf,nth)     BUG_RNG1(nth,BNF_ntCnt(bnf))
#define BUG_BNF_PRD(bnf,nt,nth)  BUG_RNG1(nth,BNF_ntProdCnt(bnf,nt))
#define BUG_BNF_CLS(cls)         BUG_VEQU(cls,True)
#define BUG_BNF_TOK(bnf,nth)     BUG_RNG1(nth,BNF_tokCnt(bnf))
#define BUG_BNF_KEY(bnf,nth)     BUG_RNG1(nth,BNF_keyCnt(bnf))

/*I--------------------------- Create & Delete ------------------------------ */

BNF_BNF BNF_create(PLR_Tab PTab)
/* creates a BNF-view from the parse table 'PTab' */
{ BNFTAB* Bnf; int i, j, k;

  BUG_NULL(PTab);
  Bnf            = (BNFTAB*)NewMem(sizeof(BNFTAB));
  BNF_PCNTS(Bnf) = 
    (int*)NewMem(sizeof(int) * ( PLR_nontermCnt(PTab) + PLR_startCnt(PTab) ));
  BNF_FSTPS(Bnf) = 
    (int*)NewMem(sizeof(int) * ( PLR_nontermCnt(PTab) + PLR_startCnt(PTab) ));
  BNF_PTAB(Bnf)  = PTab;
  for( BNF_KCNT(Bnf)=0, BNF_TCNT(Bnf)=0, i=0; i < PLR_tokenCnt(PTab); ++i )
  {
    if( CFG_TOK(PLR_symType(PTab,i)) ) ++BNF_TCNT(Bnf);
    if( CFG_KEY(PLR_symType(PTab,i)) ) ++BNF_KCNT(Bnf);
  }
  BNF_TSYMS(Bnf) = (int*)NewMem(sizeof(int)*BNF_TCNT(Bnf));
  BNF_KSYMS(Bnf) = (int*)NewMem(sizeof(int)*BNF_KCNT(Bnf));
  for( i=0, j=0, k=0; i < PLR_tokenCnt(PTab); ++i )
  {
    if( CFG_TOK(PLR_symType(PTab,i)) )
    {
      BNF_TSYM(Bnf,j) = i; ++j;
    }  
    if( CFG_KEY(PLR_symType(PTab,i)) )
    {
      BNF_KSYM(Bnf,k) = i; ++k;
    }  
  }
  for( i=0; i < PLR_nontermCnt(PTab) + PLR_startCnt(PTab); ++i )
  {
    BNF_PCNT(Bnf,i) = 0;
    BNF_FSTP(Bnf,i) = -1;
  }
  for( i=0; i < PLR_prodCnt(PTab); ++i )
    ++BNF_PCNT(Bnf,PLR_prodNonTerm(PTab,i) - PLR_tokenCnt(PTab));
  for( i=0; i < PLR_prodCnt(PTab); ++i )
  { int idx = PLR_prodNonTerm(PTab,i) - PLR_tokenCnt(PTab);

    if( BNF_FSTP(Bnf,idx) == -1 ) BNF_FSTP(Bnf,idx) = i;
  }
  return( Bnf );
}

void BNF_delBNF(BNF_BNF Bnf)
/* deletes BNF-view 'Bnf' */
{
  BUG_NULL(Bnf);
  FreeMem(BNF_PCNTS(Bnf));
  FreeMem(BNF_FSTPS(Bnf));
  FreeMem(BNF_TSYMS(Bnf));
  FreeMem(BNF_KSYMS(Bnf));
  FreeMem(Bnf);
}

/*I---------------------------- Access to BNF-view -------------------------- */

/*I------------------------ Language and startsymbols ----------------------- */

string BNF_language(BNF_BNF Bnf)
/* Language name */
{
  BUG_NULL(Bnf);
  return( PLR_language(BNF_PTAB(Bnf)) );
}

int BNF_startCnt(BNF_BNF Bnf)
/* Number of startsymbols */
{
  BUG_NULL(Bnf);
  return( PLR_startCnt(BNF_PTAB(Bnf)) );
}

BNF_NTM BNF_startNth(BNF_BNF Bnf, int Nth)
/* Nth startsymbol ( Nth >= 1 ) */
{
  BUG_BNF_START(Bnf,Nth);
  return
  ( 
    (BNF_NTM)(PLR_tokenCnt(BNF_PTAB(Bnf))+PLR_nontermCnt(BNF_PTAB(Bnf))+Nth-1) 
  );
}

/*I---------------------------- Nonterminals -------------------------------- */

int BNF_ntCnt(BNF_BNF Bnf)
/* Number of nonterminals */
{
  BUG_NULL(Bnf);
  return( PLR_nontermCnt(BNF_PTAB(Bnf)) );
}

BNF_NTM BNF_ntNth(BNF_BNF Bnf, int Nth)
/* Nth nonterminal ( Nth >= 1 ) */
{
  BUG_BNF_NTM(Bnf,Nth);
  return( (BNF_NTM)(PLR_tokenCnt(BNF_PTAB(Bnf)) + Nth - 1) );
}

int BNF_ntIntern(BNF_BNF Bnf, BNF_NTM Nt)
/* Nonterminal to symbol id */
{
  return( BNF_N_IMP(Nt) );
}

string BNF_ntName(BNF_BNF Bnf, BNF_NTM Nt)
/* Nonterminal to name */
{
  BUG_NULL(Bnf);
  return( PLR_symName(BNF_PTAB(Bnf),BNF_ntIntern(Bnf,Nt)) );
}

BNF_NTM BNF_ntId(BNF_BNF Bnf, string NtName)
/* Name to nonterminal */
{ BNF_NTM Nt; int i;
  
  for( i=1; i <= BNF_ntCnt(Bnf); ++i )
    if( ! strcmp(NtName,BNF_ntName(Bnf,( Nt=BNF_ntNth(Bnf,i) ))) ) return( Nt );
  BUG; return( (BNF_NTM)NULL );
}

BNF_NTM BNF_internNt(BNF_BNF Bnf, int symbol)
/* Symbol id to nonterminal */
{
  return( (BNF_NTM)symbol );
}

/*I---------------------------- Productions --------------------------------- */

int BNF_ntProdCnt(BNF_BNF Bnf, BNF_NTM Nt)
/* Number of productions */
{
  BUG_NULL(Bnf);
  return( BNF_PCNT(Bnf,BNF_ntIntern(Bnf,Nt)-PLR_tokenCnt(BNF_PTAB(Bnf))) );
}

BNF_PRD BNF_ntProdNth(BNF_BNF Bnf, BNF_NTM Nt, int Nth)
/* Nth production ( Nth >= 1 ) */
{ int firstProd;

  BUG_BNF_PRD(Bnf,Nt,Nth);
  firstProd = BNF_FSTP(Bnf,BNF_ntIntern(Bnf,Nt)-PLR_tokenCnt(BNF_PTAB(Bnf)));
  return( (BNF_PRD)(firstProd + Nth - 1) );
}

int BNF_prodIntern(BNF_BNF Bnf, BNF_PRD Prd)
/* Production to id */
{
  return( BNF_P_IMP(Prd) );
}

string BNF_prodName(BNF_BNF Bnf, BNF_PRD Prd)
/* Production to name */
{
  BUG_NULL(Bnf);
  return( PLR_prodName(BNF_PTAB(Bnf),BNF_prodIntern(Bnf,Prd)) );
}

BNF_PRD BNF_ntProdId(BNF_BNF Bnf, BNF_NTM Nt, string ProdName)
/* Name to production */
{ int firstProd =
      BNF_FSTP(Bnf,BNF_ntIntern(Bnf,Nt)-PLR_tokenCnt(BNF_PTAB(Bnf))),
      cnt       = BNF_ntProdCnt(Bnf,Nt), i; BNF_PRD Prd;

  for( i=0; i < cnt; ++i )
  {
    Prd = (BNF_PRD)(firstProd + i);
    if( ! strcmp(BNF_prodName(Bnf,Prd),ProdName) ) return( Prd );
  }
  BUG; return( (BNF_PRD)NULL );
}

BNF_NTM BNF_prodNtId(BNF_BNF Bnf, BNF_PRD Prd)
/* Production nonterminal */
{
  BUG_NULL(Bnf);
  return( (BNF_NTM)PLR_prodNonTerm(BNF_PTAB(Bnf),BNF_prodIntern(Bnf,Prd)) );
}

BNF_PRD BNF_internProd(BNF_BNF Bnf, int symbol)
/* Id to production */
{
  return( (BNF_PRD)symbol );
}

/*I------------------------ Production symbols ------------------------------ */

int BNF_prodMbrCnt(BNF_BNF Bnf, BNF_PRD Prd)
/* Number of production symbols */
{
  BUG_NULL(Bnf);
  return( PLR_prodSymCnt(BNF_PTAB(Bnf),BNF_prodIntern(Bnf,Prd)) );
}

BNF_MBR BNF_prodMbrNth(BNF_BNF Bnf, BNF_PRD Prd, int Nth)
/* Nth production symbol ( Nth >= 1 ) */
{
  BUG_NULL(Bnf);
  return
  ( 
    (BNF_MBR)PLR_prodSymbol(BNF_PTAB(Bnf),BNF_prodIntern(Bnf,Prd),Nth-1) 
  );
}

bool BNF_isMbrNtm(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol is nonterminal ? */
{
  BUG_NULL(Bnf);
  return( CFG_NTM(PLR_symType(BNF_PTAB(Bnf),BNF_M_IMP(Mbr))) );
}

bool BNF_isMbrTok(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol is token ? */
{
  BUG_NULL(Bnf);
  return( CFG_TOK(PLR_symType(BNF_PTAB(Bnf),BNF_M_IMP(Mbr))) );
}

bool BNF_isMbrKey(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol is keyword ? */
{
  BUG_NULL(Bnf);
  return( CFG_KEY(PLR_symType(BNF_PTAB(Bnf),BNF_M_IMP(Mbr))) );
}

BNF_NTM BNF_MbrNtm(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol to nonterminal */
{
  BUG_BNF_CLS(BNF_isMbrNtm(Bnf,Mbr));
  return( (BNF_NTM)Mbr );
}

BNF_TOK BNF_MbrTok(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol to token */
{
  BUG_BNF_CLS(BNF_isMbrTok(Bnf,Mbr));
  return( (BNF_TOK)Mbr );
}

BNF_KEY BNF_MbrKey(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol to keyword */
{
  BUG_BNF_CLS(BNF_isMbrKey(Bnf,Mbr));
  return( (BNF_KEY)Mbr );
}

/*I-------------------------------- Tokens ---------------------------------- */

int BNF_tokCnt(BNF_BNF Bnf)
/* Number of tokens */
{
  BUG_NULL(Bnf);
  return( BNF_TCNT(Bnf) );
}

BNF_TOK BNF_tokNth(BNF_BNF Bnf, int Nth)
/* Nth token ( Nth >= 1 ) */
{
  BUG_BNF_TOK(Bnf,Nth);
  return( (BNF_TOK)BNF_TSYM(Bnf,Nth-1) );
}

int BNF_tokIntern(BNF_BNF Bnf, BNF_TOK Tok)
/* Token to symbol id */
{
  return( BNF_T_IMP(Tok) );
}

string BNF_tokName(BNF_BNF Bnf, BNF_TOK Tok)
/* Token to name */
{
  BUG_NULL(Bnf);
  return( PLR_symName(BNF_PTAB(Bnf),BNF_tokIntern(Bnf,Tok)) );
}

BNF_TOK BNF_tokId(BNF_BNF Bnf, string TokName)
/* Name to token */
{ BNF_TOK Tok; int i;
  
  for( i=1; i <= BNF_tokCnt(Bnf); ++i )
    if( ! strcmp(TokName,BNF_tokName(Bnf,( Tok=BNF_tokNth(Bnf,i) ))) )
      return( Tok );
  BUG; return( (BNF_TOK)NULL );
}

BNF_TOK BNF_internTok(BNF_BNF Bnf, int symbol)
/* Symbol id to token */
{
  return( (BNF_TOK)symbol );
}

/*I------------------------------- Keywords --------------------------------- */

int BNF_keyCnt(BNF_BNF Bnf)
/* Number of keywords */
{
  BUG_NULL(Bnf);
  return( BNF_KCNT(Bnf) );
}

BNF_KEY BNF_keyNth(BNF_BNF Bnf, int Nth)
/* Nth keyword ( Nth >= 1 ) */
{
  BUG_BNF_KEY(Bnf,Nth);
  return( (BNF_KEY)BNF_KSYM(Bnf,Nth-1) );
}

int BNF_keyIntern(BNF_BNF Bnf, BNF_KEY Key)
/* Keyword to symbol id */
{
  return( BNF_K_IMP(Key) );
}

string BNF_keyName(BNF_BNF Bnf, BNF_KEY Key)
/* Keyword to name */
{
  BUG_NULL(Bnf);
  return( PLR_symName(BNF_PTAB(Bnf),BNF_keyIntern(Bnf,Key)) );
}

BNF_KEY BNF_keyId(BNF_BNF Bnf, string KeyName)
/* Name to keyword */
{ BNF_KEY Key; int i;
  
  for( i=1; i <= BNF_keyCnt(Bnf); ++i )
    if( ! strcmp(KeyName,BNF_keyName(Bnf,( Key=BNF_keyNth(Bnf,i) ))) )
      return( Key );
  BUG; return( (BNF_KEY)NULL );
}

BNF_KEY BNF_internKey(BNF_BNF Bnf, int symbol)
/* Symbol id to keyword */
{
  return( (BNF_KEY)symbol );
}
