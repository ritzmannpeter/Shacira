/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [prs_imp.h]       LALR(1) Parser/Generator: implementation types           */
/*                                                                            */
/* Copyright (c) 1993 by Doelle, Manns                                        */
/*----------------------------------------------------------------------------*/

#ifndef PRS_IMP_INCL
#define PRS_IMP_INCL

#include "standard.h"

/*
  Implementation of grammar symbols

  Each grammar symbol is numbered uniquely in the following order:
    token, nonterminal - starting with 0.
  The first startsymbol refers to the whole grammar.
*/

typedef struct _KFGHEAD {
/* Grammar header */
  c_string  language; /* Language short name                   */
                      /* ( Prefix for code generation )        */
  int       TkCnt;    /* Number of tokens                      */
  int       NtCnt;    /* Number of nonterminals                */
  c_string* SNames;   /* Token and nonterminal names           */
  int       StartCnt; /* Number of startsymbols                */
  int*      StartIds; /* Indexes of startsymbols               */
                      /* ( 1. index : CFG startsymbol )        */
  int*      TokKind;  /* Token types                           */
  int*      NtClass;  /* Nonterminal Classes ( Indexes )       */
  c_bool*   ErrorNt;  /* ErrorNt[NTIndex] --> Reparse Point    */
} KFGHEAD;

typedef struct _KFGPROD {
/* Production */
  c_string pname;   /* Production name                            */
  int      method;  /* Production layout hint                     */
  int      id;      /* Nonterminal ( left production side )       */
  int      symcnt;  /* Number of production symbols               */
  int*     symbols; /* Production symbols ( Token, Nonterminals ) */
  int*     symfrms; /* Production symbol layout hints             */
                    /* ( != 0 ==> new line )                      */
} KFGPROD;

typedef struct _LALR_1 {
/* LALR(1) syntax analysis tables */
  int  MstShiftCnt; /* Number of MstShift's  */
  int* MstShift;    /* Master shift table    */
  int  DtlShiftCnt; /* Number of DtlShift's  */
  int* DtlShift;    /* Detail shift table    */
  int  GoToCnt;     /* Number of GoTo's      */
  int* GoTo;        /* GoTo table            */
  int  GoToDftCnt;  /* Number of GoToDft's   */
  int* GoToDft;     /* Default GoTo table    */
  int  ActDftCnt;   /* Number of ActDft's    */
  int* ActDft;      /* Default action table  */
  int  ActExpCnt;   /* Number of ActExp's    */
  int* ActExp;      /* Execpetion table      */
} LALR_1;

typedef struct _PARSETAB {
/* Parse table */
  KFGHEAD* Kfg;     /* Grammar header                        */
  int      ProdCnt; /* Number of nonterminals                */
                    /* with productions, used for reductions */
  KFGPROD* Prod;    /* Productions                           */
  LALR_1   tabs;    /* LALR(1) syntax analysis tables        */
} PARSETAB;

#define PLR_T_IMP(ptab) ( (PARSETAB*)(ptab) )

#endif
