/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [prs_gen.c]              LALR(1) Parser Generator                        */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "prs_dfn.h"

/*!
  <p>The module [prs_gen] performs two main tasks.

  <p>1) A set of functions will be used to dynamically create a BNF-like context
        free grammar definition. ( reentrant )
        <br>It is possible to define multiple startsymbols and comment tokens.

  <p>2) The latter function create the corresponding parse table and nonterminal 
        classes. 
        The parse table is the input for the <a href="prs.htm">parse function</a>.
        <br>This creation process is not reentrant. You must synchronize the access
        to the function within threads.     
*/

/*!!
  The following rules define the abstract syntax. On this base the nonterminal
  classes are created.

  A) well-formed productions:
  1. let X :nil  :            <0 members>
  2. let X :cons : Y Z        <2 members: Y = member && Z = nonterminal>
  3. let X :ign#*: Y          <1 nonterminal>
  4. let X :name : X1 .. Xn   <n >= 0 && name =/= { ign1, nil, cons }>

  B) construction of the token/nonterminal classes:
  1. X <=> X                          reflexiv 
  2. X <=> Y --> Y <=> X              symmetric
  3. X <=> Y && Y <=> Z --> X <=> Z   transitiv
  4. let X :ign1: Y   --> X <=> Y
  5. let X :cons: Y Z --> X <=> Z  
  6. X <=> Y && let X :idx: X1 .. Xn && let Y :idy: Y1 .. Ym && idx = idy
     --> n = m && forall i, 1 <= i <= n: Type(Xi) = Type(Yi) && Xi <=> Yi,
                                         where Type(Z) = { token, nonterminal }
  7. all tokens are equivalent.

  C) token/nonterminal classes:
     [X] = { Y | Y <=> X }
     class representants:
     - tokens:       "Tok"
     - startsymbols: language name
     - nonterminals: less nonterminal name according the lexical order

  D) correctness:
  1. X <=> Y --> Type(X) = Type(Y), where Type(Z) = { token, nonterminal }
  2. let X^ :id: a && let X^ :id: b --> a <=> b
  3. let X^ :nil: a || let X^ :cons: b
     --> not exists P: P = let X^ :id: c && id =/= { ign1, nil, cons }
  [ 1,2: checked during construction ]

  E) abstract context free grammar:
     NT |--> NT^
     T  |--> T^ ( NT^ T^ are the class representants )

     for all "normal" productions there will be one interface function 
     of type 'bool' which returns whether the argument term represents 
     a production of this kind and in the positive case all required members.
*/

/*D
  Aenderungen fuer einen reflexiven Parser

   Nonterminals waeren zugleich Terminals.
   1) Die First-Sets der Nonterminals muessten um die jeweilige
      Nonterminal-Huelle erweitert werden.
   2) Nonterminals werden moegliche Lookaheads.
      ( Set[KFGSYMCNT+STARTCNT] )
   3) Die GoTo-Tabellen entfallen, und die Shift/Reduktions-Tabellen
      beziehen sich auch auf Nonterminals.
*/

#include "olist.h"
#include "otab.h"
#include "binset.h"
#include "prs_imp.h"

/*==================== Types / Constants / Globals ===========================*/

/*I------------------------------ Types ------------------------------------- */

AbstractType(PLR_Cfg); /* Abstract context free grammar type */

typedef struct _PSDFN {
/* production symbol ( definition interface ) */
  bool istoken; /* symbol is a token */
  int  symbol;  /* symbol            */
  long sRow;    /* line position     */
  long sCol;    /* col position      */
} PSDFN;

typedef struct _PRDFN {
/* production ( definition interface ) */
  string pname;   /* production       */
  int    method;  /* reduction method */
  int    pid;     /* nonterminal      */
  OT_Tab psymbol; /* symbols          */
} PRDFN;

typedef struct _KFGDFN {
/* context free grammar ( definition interface ) */
  string language; /* language            */
  OT_Tab Token;    /* token               */
  OT_Tab TkIdx;    /* token indexes       */
  OT_Tab NtIdx;    /* nonterminal indexes */
  OT_Tab NonTerm;  /* nonterminals        */
  OT_Tab StartNt;  /* startsymbols        */
  OT_Tab TokKind;  /* token kind          */
  OT_Tab ErrorNt;  /* error recovery nt's */
  OT_Tab Prod;     /* productions         */
} KFGDFN;

typedef struct _KFGNT {
/* nonterminal */
  int    altcnt; /* productions                      */
  int    fstalt; /* first produktion                 */
  OT_Tab states; /* occurrence in StateTab as symbol */
  BS_Set first;  /* FIRST set                        */
} KFGNT;

typedef struct _PSTATE {
/* parser state */
  int    symbol; /* with symbol marked vertice or -1 ( start state ) */
  OL_Lst states; /* follow states                                    */
  OL_Lst kern;   /* kernel elements                                  */
  OT_Tab looks;  /* lookaheads                                       */
} PSTATE;

/*D
   Darstellung der Kernelemente

   Ein (Kern-)Element wird durch einen Index in eine
   vektorisierte Matrix [ProdCnt, MaxSymCnt+1] dargestellt,
   wobei die 1. Dimension die Nr. der Produktion und
   die 2. Dimension die Punkt-Position angibt.
   ( Position vor dem durch die 2. Dimension numerierten
     Symbol oder MaxSymCnt+1 zur Kennzeichnung einer
     Reduktionsproduktion )
*/

typedef struct _PrsGen_T {
  bool     profile;      /* Profile Printing                    */
  int      ProdCnt;      /* Anzahl der Grammatik-Produktionen   */
  int      MaxSymCnt;    /* max. Anzahl Produktionssymbole      */
  int      MaxSymNamLen; /* max. Laenge der Symbol Namen        */
  int      conflictCnt;  /* Anzahl Konflikte                    */
  
  OT_Tab*  NtEquiv;      /* Equivalence Tables of Nonterminals  */
      
  KFGHEAD* Kfg;          /* Grammatik-Kopfdaten                 */
  KFGNT*   NonTermTab;   /* Nonterminals der Grammatik          */
  KFGPROD* ProdTab;      /* Produktionen der Grammatik          */
  OT_Tab   GoToKern;     /* Kerne der Folgezustaende            */
                         /* ( Tabelle von Kernelement-Listen )  */
  OT_Tab   KernTab;      /* Indizes Kernelemente                */
  OT_Tab   StateTab;     /* Parser-Zustaende                    */
  BS_Set   LambdaSet;    /* LAMBDA-Set { Nt *=> lambda }        */
  BS_Set   TokenSet;     /* FIRST-Set of current Symbol-List    */
  BS_Set   NonTermSet;   /* Set for marking Nonterminals        */
  BS_Set   NtRelSet;     /* Nt-LALR(0)-Huelle                   */
  BS_Set   StateSet;     /* Set for Propagation of Lookaheads   */
  BS_Set*  PLaheads;     /* Lookahead-Sets fuer die aktuellen   */
                         /* Huellen-Elemente                    */
  void (*prMsg)(c_string msg); /* external message function     */
} PrsGen_T;


/* ------------------------ Constants and Globals --------------------------- */

/*  NOTE:
 *  Most of the following macros expect a variable named 'PrsGen', 
 *  which points to the current generation structure.
*/

#define MAX_OBJECTS       10000

#define MAX_PR_ICOLS      10
#define MAX_PR_SCOLS      5

#define PLR_C_IMP(cfg)    ( (KFGDFN*)(cfg) )

#define NTIDX(nt)         ( ( nt ) - PrsGen->Kfg->TkCnt )
#define NTSYMBOL(idx)     ( ( idx ) + PrsGen->Kfg->TkCnt )
#define NTCLASS(idx)      ( PrsGen->Kfg->NtClass[idx] )
#define NTEQUIV(idx)      ( PrsGen->NtEquiv[idx] )
#define FIRSTNTPROD(nt)   ( PrsGen->NonTermTab[NTIDX(nt)].fstalt )
#define LASTNTPROD(nt)    ( FIRSTNTPROD(nt) + PrsGen->NonTermTab[NTIDX(nt)].altcnt - 1 )
#define FIRSTSET(nt)      ( PrsGen->NonTermTab[NTIDX(nt)].first )
#define NONTERMCNT        ( PrsGen->Kfg->NtCnt + PrsGen->Kfg->StartCnt )
#define TERMCNT           ( PrsGen->Kfg->TkCnt + PrsGen->Kfg->StartCnt )
#define KFGSYMCNT         ( PrsGen->Kfg->TkCnt + PrsGen->Kfg->NtCnt )
#define ACCEPTTK(i)       ( ( i ) + PrsGen->Kfg->TkCnt )
#define TKACCEPT(tk)      ( ( tk ) - PrsGen->Kfg->TkCnt )
#define NTACCEPT(nt)      ( ( nt ) - PrsGen->Kfg->NtCnt )

#define KERNMATRIX        ( PrsGen->ProdCnt * ( PrsGen->MaxSymCnt + 1 ) )
#define KERNELEMENT(li,r) ( ( ( li ) * ( PrsGen->MaxSymCnt + 1 ) ) + ( r ) )
                          /* li = Prod.index   0 .. ProdCnt-1   */
                          /* r  = Pkt.position 1 .. MaxSymCnt+1 */
#define PRODUCTION(e)     ( (OT_GET(unsigned long,PrsGen->KernTab,(e)-1)) >> 16 )
#define POSITION(e)       ( (OT_GET(unsigned long,PrsGen->KernTab,(e)-1)) & 0xFFFF )

#define NEW_PSYMTAB       OT_CREATE(PSDFN,cpyPsym,delPsym,primEqual)
#define INS_PSYM(p,t)     OT_T_INS(t,p)
#define GET_PSYM(t,i)     OT_GET(PSDFN*,t,i)

#define NEW_PRODTAB       OT_CREATE(PSDFN,cpyProd,delProd,primEqual)
#define INS_PROD(p,t)     OT_T_INS(t,p)
#define GET_PROD(t,i)     OT_GET(PRDFN*,t,i)
#define SRT_PRODS(t)      OT_SORT(t,cmpProd)
#define FND_PROD(t,ti,k)  OT_B_FIND(t,ti,(k),cmpProd)

#define NEW_STATETAB      OT_CREATE(PSTATE,cpyState,delState,primEqual)
#define INS_STATE(s,t)    OT_T_INS(t,s)
#define GET_STATE(t,i)    OT_GET(PSTATE*,t,i)

#define NEW_KLISTTAB      OT_CREATE(OL_Lst,primCopy,OL_delL,OL_equal)
#define INS_KLIST(l,t)    OT_T_INS(t,l)
#define GET_KLIST(t,i)    OT_GET(OL_Lst,t,i)

#define NEW_LOOKTAB       OT_CREATE(BS_Set,primCopy,delLook,BS_equal)
#define INS_LOOK(l,t)     OT_T_INS(t,l)
#define INSN_LOOK(l,t,n)  OT_P_INS(t,l,n)
#define GET_LOOK(t,i)     OT_GET(BS_Set,t,i)

#define NEW_INTTAB        OT_CREATE_ADT(int)
#define INS_INTTE(e,t)    OT_T_INS(t,e)
#define UPD_INTTE(e,t,i)  OT_UPD(int,t,i,e)
#define GET_INTTE(t,i)    OT_GET(int,t,i)
#define INTTE_ARRAY(t)    OT_COPY_V(int*,t,sizeof(int),cpyInt)

#define NEW_STRTAB        OT_CREATE(string,StrCopy,FreeMem,strEqual)
#define INS_STRTE(e,t)    OT_T_INS(t,e)
#define GET_STRTE(t,i)    OT_GET(string,t,i)
#define SRT_STRTES(t)     OT_SORT(t,cmpStr)
#define FND_STRTE(t,ti,k) OT_B_FIND(t,ti,(k),strcmp)

#define NEW_INTLIST       OL_CREATE_ADT(INT)
#define INSC_INTLE(e,l)   OL_C_INS(INT,l,e)
#define INST_INTLE(e,l)   OL_T_INS(INT,l,e)
#define INSS_INTLE(e,l)   OL_S_INS(INT,l,e,primLessEqual)
#define FND_INTLE(e,l)    OL_FIND(l,e,primGreatEqual)
#define FST_INTLE(l)      OL_FIRST(INT,l)
#define NXT_INTLE(l)      OL_NEXT(INT,l)
#define CURR_INTLE(l)     OL_CURR(INT,l)
#define PRT_INTLES(l,n)   OL_PRINT_EX(l,printINTObj,PrsGen,MAX_PR_ICOLS,(n))

#define ACT_ERROR         ( PrsGen->ProdCnt + 1 )
#define ACT_ACCEPT        ( PrsGen->ProdCnt + 2 )
#define PROD_OFFSET       ( PrsGen->ProdCnt + TERMCNT )

#define PROD_NORMAL       -3
#define PROD_FALSE        -2
#define PROD_NIL          -1


static int indent = 2; /* read-only access */


/*============================= Auxiliary ====================================*/

/* Parameter Check: CALL Function */

static int cmpStr(OT_Obj left, OT_Obj right)
/* left key - right key */
{
  return( strcmp((string)left,(string)right) );
}

static OT_Obj cpyTObj(OT_Obj obj, int size)
/* copy obj */
{
  return( (OT_Obj)BytCopy(obj,size) );
}

static OT_Obj cpyPsym(OT_Obj psym)
/* copy production symbol */
{
  return( cpyTObj(psym,sizeof(PSDFN)) );
}

static OT_Obj cpyProd(OT_Obj prod)
/* copy production */
{
  return( cpyTObj(prod,sizeof(PRDFN)) );
}

static OT_Obj cpyState(OT_Obj state)
/* copy state */
{
  return( cpyTObj(state,sizeof(PSTATE)) );
}

static int cmpProd(OT_Obj left, OT_Obj right)
/* left key - right key */
{
  return( ((PRDFN*)left)->pid - ((PRDFN*)right)->pid );
}

static int* cpyInt(OT_Obj obj)
/* copy an int object */
{ int* ptr = (int*)NewMem(sizeof(int));

  *ptr = (int)obj; return( ptr );
}

static bool addNewMembers(BS_Set dst, BS_Set left, BS_Set right)
/* ! ( right <= left ) ==> dst = left + right */
{
  if( ! BS_subset(right,left) )
  {
    BS_union(dst,left,right); return( True );
  }
  return( False );
}

static INT nextProdElement(PrsGen_T* PrsGen, INT element)
/* naechstes Kernelement ( innerhalb einer Produktion ) */
{ int idx = PRODUCTION(element) - 1, pos = POSITION(element);
  return
  ( 
    ( pos < PrsGen->ProdTab[idx].symcnt ) 
    ? KERNELEMENT(idx,pos+1)
    : KERNELEMENT(idx,PrsGen->MaxSymCnt+1) 
  );
}

static INT prevProdElement(PrsGen_T* PrsGen, INT element)
/* vorhergehendes Kernelement ( innerhalb einer Produktion ) */
{ int idx = PRODUCTION(element) - 1, pos = POSITION(element);
  return
  (
    ( pos == PrsGen->MaxSymCnt+1 )
    ? KERNELEMENT(idx,PrsGen->ProdTab[idx].symcnt)
    : KERNELEMENT(idx,pos-1) 
  );
}

static int symType(PrsGen_T* PrsGen, int SymId)
/* Type(SymId) */
{
  return
  ( 
    ( SymId >= PrsGen->Kfg->TkCnt ) 
    ? PLR_TYP_NTM : PrsGen->Kfg->TokKind[SymId] 
  );
}

static bool isToken(PrsGen_T* PrsGen, int SymId)
/* SymId ist ein "User"-Token */
{
  return( ( SymId >= 0 && SymId < PrsGen->Kfg->TkCnt ) ? True : False );
}

static bool isNonTerm(PrsGen_T* PrsGen, int SymId)
/* SymId ist ein "User"-Nonterminal */
{
  return( ( SymId >= PrsGen->Kfg->TkCnt && SymId < KFGSYMCNT ) ? True : False );
}

static int cntProdMembers(PrsGen_T* PrsGen, KFGPROD* prod)
/* number of tokens and nonterminals of 'prod' */
{ int cnt, typ, i;
  for( cnt=0, i=0; i < prod->symcnt; ++i )
  {
    typ  = symType(PrsGen,prod->symbols[i]);
    cnt += CFG_TOK_NTM(typ);
  }
  return( cnt );
}

static int nextProdMember(PrsGen_T* PrsGen, KFGPROD* prod, int startidx)
/* next token/nonterminal of 'prod' */
{ int typ, i;
  for( i=startidx; i < prod->symcnt; ++i )
  {
    typ = symType(PrsGen,prod->symbols[i]);
    if( CFG_TOK_NTM(typ) ) return( i );
  }
  return( prod->symcnt );
}

static void forallNtClasses
            (
              PrsGen_T* PrsGen, void (*act)(PrsGen_T* PrsGen, int ntclass)
            )
/* performs 'act' on all nonterminal classes */
{ int i;
  for( i=0; i < PrsGen->Kfg->NtCnt; ++i ) 
    if( i == NTCLASS(i) ) (*act)(PrsGen,i);
}

static void forallEquivNts
            (
              PrsGen_T* PrsGen, int ntclass, 
              void (*act)(PrsGen_T* PrsGen,int ntidx, int data), int data
            )
/* performs 'act' on all equivalent nonterminals of 'ntclass' */
{ int cnt = OT_CNT(NTEQUIV(ntclass)), i;
  for( i=0; i < cnt; ++i ) 
    (*act)(PrsGen,OT_GET(int,NTEQUIV(ntclass),i),data);
}

/*====================== Creation of the Parse Tables ========================*/

/* Parameter Check: CALL Function */

/* ------------------------ Nonterminal Classes ----------------------------- */

static int wellProd(PrsGen_T* PrsGen, KFGPROD* prod)
/* whether 'prod' is well-formed */
{ int res = PROD_FALSE, typ, cnt, i;
  if( nilProd(prod->pname) )
  {
    if( cntProdMembers(PrsGen,prod) ) return( PROD_FALSE );
    else                              return( PROD_NIL );
  }
  else
  {
    if( consProd(prod->pname) )
    {
      for( cnt=0, i=0; i < prod->symcnt; ++i )
      {
        typ  = symType(PrsGen,prod->symbols[i]);
        cnt += CFG_TOK_NTM(typ);
        if( cnt == 2 && CFG_NTM(typ) ) res = prod->symbols[i];
      }
      if( cnt != 2 ) return( PROD_FALSE );
      else           return( res );
    }
    else
    {
      if( ignProd(prod->pname) )
      {
        for( cnt=0, i=0; i < prod->symcnt; ++i )
        {
          typ  = symType(PrsGen,prod->symbols[i]);
          cnt += CFG_TOK_NTM(typ);
          if( cnt == 1 && CFG_NTM(typ) ) res = prod->symbols[i];
        }
        if( cnt != 1 ) return( PROD_FALSE );
        else           return( res );
      }
      else return( PROD_NORMAL );
    }
  }
}

static void checkListProds(PrsGen_T* PrsGen, int ntclass)
/* checks condition 3 for 'ntclass' */
{ bool isList = False; bool isOther = False;
  int cnt = OT_CNT(NTEQUIV(ntclass)), i; 
  for( i=0; i < cnt; ++i )
  { int nti = OT_GET(int,NTEQUIV(ntclass),i), j;
    for( j =  FIRSTNTPROD(NTSYMBOL(nti)); j <= LASTNTPROD(NTSYMBOL(nti)); ++j )
    { KFGPROD* prod = &PrsGen->ProdTab[j];
      if( nilProd(prod->pname) || consProd(prod->pname) ) isList = True;
      else
        if( ! ignProd(prod->pname) ) isOther = True;
      bug1
      ( 
        ! ( isList && isOther ), 
        "[%s] consists of list/non list productions",
        PrsGen->Kfg->SNames[prod->id]
      );
    }
  }
}

static void changeNtClass(PrsGen_T* PrsGen, int ntidx, int newClass)
/* Class(ntidx) = newClass */
{
  NTCLASS(ntidx) = newClass;
}

static bool setEquivNts(PrsGen_T* PrsGen, int ntidx1, int ntidx2)
/* sets nonterminals 'ntidx1' and 'ntidx2' equivalent */
{ int ntc1 = NTCLASS(ntidx1), ntc2 = NTCLASS(ntidx2);
  if( ntc1 == ntc2 ) return( False );
  else
  { 
    if( strcmp(PrsGen->Kfg->SNames[NTSYMBOL(ntc2)],
               PrsGen->Kfg->SNames[NTSYMBOL(ntc1)]) < 0 )
    {
      forallEquivNts(PrsGen,ntc1,changeNtClass,ntc2);
      OT_APPEND(NTEQUIV(ntc2),NTEQUIV(ntc1));
      OT_DEL_T(NTEQUIV(ntc1));
    }
    else
    {
      forallEquivNts(PrsGen,ntc2,changeNtClass,ntc1);
      OT_APPEND(NTEQUIV(ntc1),NTEQUIV(ntc2));
      OT_DEL_T(NTEQUIV(ntc2));
    }
    return( True );
  }
}

static bool setEquivProdNts(PrsGen_T* PrsGen, int ntidx1, int ntidx2)
/* determines equivalent production nonterminals of 'ntidx1' and 'ntidx2' */
{ bool change = False;
  if( NTCLASS(ntidx1) == NTCLASS(ntidx2) )
  { int i, j;
    for( i =  FIRSTNTPROD(NTSYMBOL(ntidx1)); 
         i <= LASTNTPROD(NTSYMBOL(ntidx1)); ++i )
    {
        for( j =  FIRSTNTPROD(NTSYMBOL(ntidx2)); 
             j <= LASTNTPROD(NTSYMBOL(ntidx2)); ++j )
        { KFGPROD pi = PrsGen->ProdTab[i], pj = PrsGen->ProdTab[j];
          if( ! strcmp(pi.pname,pj.pname) ) 
          { int k = nextProdMember(PrsGen,&pi,0), 
                l = nextProdMember(PrsGen,&pj,0);
            bug
            ( 
              cntProdMembers(PrsGen,&pi) == cntProdMembers(PrsGen,&pj),
              "symbols of productions '%s::%s', '%s::%s' not equivalent", 
              PrsGen->Kfg->SNames[pi.id],pi.pname,
              PrsGen->Kfg->SNames[pj.id],pj.pname
            );
            while( k < pi.symcnt && l < pj.symcnt )
            { int ksym = pi.symbols[k], lsym = pj.symbols[l], typ; 
              bug
              ( 
                ( typ = symType(PrsGen,ksym) ) == symType(PrsGen,lsym),
                "token/nonterminal conflict in productions '%s::%s', '%s::%s'", 
                PrsGen->Kfg->SNames[pi.id],pi.pname,
                PrsGen->Kfg->SNames[pj.id],pj.pname
              );
              if( CFG_NTM(typ) && setEquivNts(PrsGen,NTIDX(ksym),NTIDX(lsym)) ) 
                change = True;
              k = nextProdMember(PrsGen,&pi,k+1); 
              l = nextProdMember(PrsGen,&pj,l+1);
            }
          }
        }
    }
  }
  return( change );
}

static bool pass1NtPartition(PrsGen_T* PrsGen, KFGPROD* prod)
/* changes the nonterminal partition according 'prod' */
{ int res;
  switch( res = wellProd(PrsGen,prod) )
  {
    case PROD_NORMAL:
    case PROD_NIL:
      return( False );
    case PROD_FALSE:
      bug
      (
        False,"production '%s::%s' not well-formed",
        PrsGen->Kfg->SNames[prod->id],prod->pname
      ); 
      return( False );
    default:
      return( setEquivNts(PrsGen,NTIDX(prod->id),NTIDX(res)) );
  }
}

static void pass2NtPartition(PrsGen_T* PrsGen)
/* completes & checks the definition of the nonterminal partition */
{ bool change = True;
  while( change )
  { int i;
    change = False;
    for( i=0; i < PrsGen->Kfg->NtCnt; ++i ) 
    { OT_Tab cls; int cnt, j, k;
      if( i == NTCLASS(i) && ( cnt = OT_CNT(cls = NTEQUIV(i)) ) > 1 )
        for( j=0; j < cnt; ++j ) for( k=j+1; k < cnt; ++k )
          if( setEquivProdNts(PrsGen,OT_GET(int,cls,j),OT_GET(int,cls,k)) )
            change = True;
    }
  }
  forallNtClasses(PrsGen,checkListProds);
}

/* ------------------------ Release Globals --------------------------------- */

static void delEquivNts(PrsGen_T* PrsGen, int ntclass)
/* deletes the equivalence table of 'ntclass' */
{
  OT_DEL_T(NTEQUIV(ntclass));
}

static void delLook(StdCPtr SetEl)
/* Loeschen eines Lookahead-Sets */
{
  BS_delS((BS_Set)SetEl);
}

static void delPsym(StdCPtr PsymEl)
/* Loeschen eines Produktionssymbol */
{
  FreeMem((PSDFN*)PsymEl);
}

static void delProd(StdCPtr ProdEl)
/* Loeschen einer Produktion */
{
  FreeMem(((PRDFN*)ProdEl)->pname);
  OT_DEL_T(((PRDFN*)ProdEl)->psymbol);
  FreeMem((PRDFN*)ProdEl);
}

static void delState(StdCPtr StateEl)
/* Loeschen eines Parserzustands */
{
  OL_DEL_L(((PSTATE*)StateEl)->states);
  OL_DEL_L(((PSTATE*)StateEl)->kern);
  OT_DEL_T(((PSTATE*)StateEl)->looks);
  FreeMem((PSTATE*)StateEl);
}

static void delCreateGlobals(PrsGen_T* PrsGen)
/* Loeschen nicht mehr benoetigter Grammatik-Objekte */
{ int i;

  forallNtClasses(PrsGen, delEquivNts);
  FreeMem(PrsGen->NtEquiv);
  BS_delS(PrsGen->LambdaSet);
  BS_delS(PrsGen->TokenSet);
  BS_delS(PrsGen->NonTermSet);
  BS_delS(PrsGen->NtRelSet);
  BS_delS(PrsGen->StateSet);
  for( i=0; i < NONTERMCNT; ++i ) 
    BS_delS(PrsGen->NonTermTab[i].first);
  for( i=0; i < NONTERMCNT; ++i ) 
    OT_DEL_T(PrsGen->NonTermTab[i].states);
  FreeMem(PrsGen->NonTermTab);
  OT_DEL_T(PrsGen->KernTab);
  OT_DEL_T(PrsGen->GoToKern);
  OT_DEL_T(PrsGen->StateTab);
}

/* ----------------------- Grammar Description ------------------------------ */

static void setKfgGlobals(PrsGen_T* PrsGen, PLR_Cfg Cfg)
/* Initialisierung der globalen Variablen/Grammatik-Kopfdaten */
/* ( inhaltliche Pruefung bei der Grammatik-Definition )      */
{ int i;

  BUG_RNG0(OT_CNT(PLR_C_IMP(Cfg)->Token),MAX_OBJECTS);
  BUG_RNG1(OT_CNT(PLR_C_IMP(Cfg)->NonTerm),MAX_OBJECTS);
  BUG_RNG1(OT_CNT(PLR_C_IMP(Cfg)->StartNt),MAX_OBJECTS);
  PrsGen->MaxSymNamLen  = 0;
  PrsGen->Kfg           = (KFGHEAD*)NewMem(sizeof(KFGHEAD));
  PrsGen->Kfg->language = StrCopy(PLR_C_IMP(Cfg)->language);
  PrsGen->Kfg->TkCnt    = (int)OT_CNT(PLR_C_IMP(Cfg)->Token);
  PrsGen->Kfg->NtCnt    = (int)OT_CNT(PLR_C_IMP(Cfg)->NonTerm);
  PrsGen->Kfg->StartCnt = (int)OT_CNT(PLR_C_IMP(Cfg)->StartNt);
  BUG_RNG1(KFGSYMCNT+PrsGen->Kfg->StartCnt,MAX_OBJECTS);
  PrsGen->Kfg->SNames   = (string*)NewMem(sizeof(string)*KFGSYMCNT);
  for( i=0; i < PrsGen->Kfg->TkCnt; ++i )
  {
    PrsGen->Kfg->SNames[i] = StrCopy(GET_STRTE(PLR_C_IMP(Cfg)->Token,i));
    PrsGen->MaxSymNamLen = MAX(PrsGen->MaxSymNamLen,strlen(PrsGen->Kfg->SNames[i]));
  }
  for( i = PrsGen->Kfg->TkCnt; i < KFGSYMCNT; ++i )
  {
    PrsGen->Kfg->SNames[i] = 
      StrCopy(GET_STRTE(PLR_C_IMP(Cfg)->NonTerm,i-PrsGen->Kfg->TkCnt));
    PrsGen->MaxSymNamLen = MAX(PrsGen->MaxSymNamLen,strlen(PrsGen->Kfg->SNames[i]));
  }
  PrsGen->Kfg->StartIds = INTTE_ARRAY(PLR_C_IMP(Cfg)->StartNt);
  for( i=0; i < PrsGen->Kfg->StartCnt; ++i ) 
    PrsGen->Kfg->StartIds[i] += PrsGen->Kfg->TkCnt;
  PrsGen->Kfg->TokKind  = INTTE_ARRAY(PLR_C_IMP(Cfg)->TokKind);
  PrsGen->NtEquiv       = (OT_Tab*)NewMem(sizeof(OT_Tab)*PrsGen->Kfg->NtCnt);
  PrsGen->Kfg->NtClass  = (int*)NewMem(sizeof(int)*PrsGen->Kfg->NtCnt);
  PrsGen->Kfg->ErrorNt  = (bool*)NewMem(sizeof(bool)*PrsGen->Kfg->NtCnt);
  for( i=0; i < PrsGen->Kfg->NtCnt; ++ i ) 
  {
    NTCLASS(i)      = i; 
    NTEQUIV(i)      = OT_CREATE_ADT(int);
    OT_T_INS(NTEQUIV(i),i);
    PrsGen->Kfg->ErrorNt[i] = OT_GET(bool,PLR_C_IMP(Cfg)->ErrorNt,i);
  }
  PrsGen->LambdaSet     = BS_create(NONTERMCNT);
  PrsGen->NonTermSet    = BS_create(NONTERMCNT);
  PrsGen->NtRelSet      = BS_create(NONTERMCNT * NONTERMCNT);
  PrsGen->TokenSet      = BS_create(TERMCNT);
  PrsGen->StateTab      = NEW_STATETAB;
  PrsGen->KernTab       = OT_CREATE_ADT(unsigned long);
  PrsGen->GoToKern      = NEW_KLISTTAB;
  for( i=0; i < KFGSYMCNT; ++ i )
  { OL_Lst lst = NEW_INTLIST;

    INS_KLIST(lst,PrsGen->GoToKern);
  }
}

static void fillProdTabs(PrsGen_T* PrsGen, PLR_Cfg Cfg)
/* Initialisierung der Grammatik-Produktionsdaten, Nonterminal Partition */
{ OT_Tab PIdx; int i, j; bool change = False;

  BUG_RNG1(OT_CNT(PLR_C_IMP(Cfg)->Prod),MAX_OBJECTS);
  PrsGen->ProdCnt    = (int)OT_CNT(PLR_C_IMP(Cfg)->Prod)+PrsGen->Kfg->StartCnt;
  PIdx               = SRT_PRODS(PLR_C_IMP(Cfg)->Prod);
  PrsGen->NonTermTab = (KFGNT*)NewMem(NONTERMCNT*sizeof(KFGNT));
  for( i=0; i < NONTERMCNT; ++i )
  {
    if( i < PrsGen->Kfg->NtCnt )
    { PRDFN pkey; int pos;

      pkey.pid = i;
      BUG_VMIN(( pos = (int)FND_PROD(PLR_C_IMP(Cfg)->Prod,PIdx,&pkey) ),0);
      PrsGen->NonTermTab[i].altcnt = 0;
      PrsGen->NonTermTab[i].fstalt = pos - 1;
      for( j = pos - 1; j < (int)OT_CNT(PLR_C_IMP(Cfg)->Prod); ++j )
        if( GET_PROD(PLR_C_IMP(Cfg)->Prod,GET_INTTE(PIdx,j))->pid == i )
          PrsGen->NonTermTab[i].altcnt += 1;
        else break;
      BUG_VMIN(PrsGen->NonTermTab[i].altcnt,0);
    }
    else
    {
      PrsGen->NonTermTab[i].altcnt = 1;
      PrsGen->NonTermTab[i].fstalt = 
        (int)OT_CNT(PLR_C_IMP(Cfg)->Prod) + (i-PrsGen->Kfg->NtCnt);
    }
    PrsGen->NonTermTab[i].states = NEW_INTTAB;
    PrsGen->NonTermTab[i].first  = BS_create(TERMCNT);
  }
  PrsGen->ProdTab   = (KFGPROD*)NewMem(PrsGen->ProdCnt*sizeof(KFGPROD));
  PrsGen->MaxSymCnt = 1;
  for( i=0; i < PrsGen->ProdCnt; ++i )
  {
    if( i < OT_CNT(PLR_C_IMP(Cfg)->Prod) )
    { PRDFN* prod = GET_PROD(PLR_C_IMP(Cfg)->Prod,GET_INTTE(PIdx,i));

      BUG_RNG0(OT_CNT(prod->psymbol),MAX_OBJECTS);
      PrsGen->ProdTab[i].pname  = StrCopy(prod->pname);
      PrsGen->ProdTab[i].id     = PrsGen->Kfg->TkCnt + prod->pid;
      PrsGen->ProdTab[i].method = prod->method;
      PrsGen->ProdTab[i].symcnt = (int)OT_CNT(prod->psymbol);
      PrsGen->MaxSymCnt = ( PrsGen->ProdTab[i].symcnt > PrsGen->MaxSymCnt ) ?
                          PrsGen->ProdTab[i].symcnt : PrsGen->MaxSymCnt;
      if( PrsGen->ProdTab[i].symcnt )
      { long r0 = GET_PSYM(prod->psymbol,0)->sRow,
             c0 = GET_PSYM(prod->psymbol,0)->sCol;
        PrsGen->ProdTab[i].symbols = 
          (int*)NewMem(PrsGen->ProdTab[i].symcnt*sizeof(int));
        PrsGen->ProdTab[i].symfrms = 
          (int*)NewMem(PrsGen->ProdTab[i].symcnt*sizeof(int));
        for( j=0; j < PrsGen->ProdTab[i].symcnt; ++j )
        {
          PrsGen->ProdTab[i].symbols[j] = GET_PSYM(prod->psymbol,j)->symbol;
          if( ! GET_PSYM(prod->psymbol,j)->istoken )
            PrsGen->ProdTab[i].symbols[j] += PrsGen->Kfg->TkCnt;
          if( j > 0 )
          { long cr = GET_PSYM(prod->psymbol,j)->sRow   - r0,
                 cc = GET_PSYM(prod->psymbol,j)->sCol   - c0,
                 pr = GET_PSYM(prod->psymbol,j-1)->sRow - r0;
            PrsGen->ProdTab[i].symfrms[j] = (int)(( cr > pr ) ? -cc : cc);
          }
          else PrsGen->ProdTab[i].symfrms[j] = 0;
        }
      }
      else PrsGen->ProdTab[i].symbols = PrsGen->ProdTab[i].symfrms = (int*)NULL;
      if( pass1NtPartition(PrsGen,&PrsGen->ProdTab[i]) ) change = True;
    }
    else
    { string StNt;
      PrsGen->ProdTab[i].symbols    = (int*)NewMem(sizeof(int));
      PrsGen->ProdTab[i].symfrms    = (int*)NewMem(sizeof(int));
      PrsGen->ProdTab[i].id         = KFGSYMCNT + (i-(int)OT_CNT(PLR_C_IMP(Cfg)->Prod));
      PrsGen->ProdTab[i].method     = PLR_PRD_DFT;
      PrsGen->ProdTab[i].symcnt     = 1;
      PrsGen->ProdTab[i].symbols[0] = 
        PrsGen->Kfg->StartIds[i-(int)OT_CNT(PLR_C_IMP(Cfg)->Prod)];
      StNt                          = PrsGen->Kfg->SNames[PrsGen->ProdTab[i].symbols[0]];
      PrsGen->ProdTab[i].pname      = (string)NewMem(7+strlen(StNt));
      sprintf(PrsGen->ProdTab[i].pname,"Start_%s",StNt);
      PrsGen->ProdTab[i].symfrms[0] = 0;
    }
  }
  OT_DEL_T(PIdx);
  if( change ) pass2NtPartition(PrsGen);
}

static void fillKernTab(PrsGen_T* PrsGen)
/* Bestimmung der Kernelement-Indizes */
{ unsigned long row, col, key; int i, j;

  for( i=1; i <= PrsGen->ProdCnt; ++i )
  {
    row = ((unsigned long)i) << 16;
    row = row & 0xFFFF0000;
    for( j=1; j <= PrsGen->MaxSymCnt + 1; ++j )
    {
      col = j & 0x0000FFFF;
      key = row | col;
      OT_T_INS(PrsGen->KernTab,key);
    }
  }
}

/* ------------------------ First and Lambda Sets --------------------------- */

static bool FirstSetForSymbols(PrsGen_T* PrsGen, int SymCnt, int* Symbols)
/* Bestimmung der FIRST-Elemente fuer eine Liste von Grammatik-Symbolen */
/* ( Initialisierung des TokenSet ausserhalb ! )                        */
{ bool LambdaInAll = True; int i;

  for( i=0; i < SymCnt; ++i )
  {
    if( isToken(PrsGen,Symbols[i]) )
    {
      BS_setE(Symbols[i],PrsGen->TokenSet);
      LambdaInAll = False; break;
    }
    else
    {
      BS_union(PrsGen->TokenSet,PrsGen->TokenSet,FIRSTSET(Symbols[i]));
      if( ! BS_member( NTIDX(Symbols[i]),PrsGen->LambdaSet) )
      {
        LambdaInAll = False; break;
      }
    }
  }
  return( LambdaInAll );
}

static void fillFirstSets(PrsGen_T* PrsGen)
/* Bestimmung der FIRST-Elemente fuer alle Nonterminals */
{ bool newElements = True; int i;

  /* FIRST-Elemente fuer die Nonterminals ( Huelle ) */
  while( newElements )
  {
    newElements = False;
    for( i = 0; i < PrsGen->ProdCnt; ++i )
    {
      BS_init(PrsGen->TokenSet);
      if( PrsGen->ProdTab[i].symcnt )
      {
        FirstSetForSymbols
        (
          PrsGen,PrsGen->ProdTab[i].symcnt,PrsGen->ProdTab[i].symbols
        );
        newElements |= 
          addNewMembers
          ( 
            FIRSTSET(PrsGen->ProdTab[i].id),
            FIRSTSET(PrsGen->ProdTab[i].id),PrsGen->TokenSet
          );
      }
    }
  }
  /* FIRST-Elemente fuer die Startsymbole */
  for( i = KFGSYMCNT; i < NTSYMBOL(NONTERMCNT); ++i )
  { int id = PrsGen->Kfg->StartIds[i-KFGSYMCNT];

    if( BS_member(NTIDX(id),PrsGen->LambdaSet) ) 
      BS_setE(NTACCEPT(i),FIRSTSET(i));
  }
}

static void fillLambdaSet(PrsGen_T* PrsGen)
/* Bestimmung aller Nonterminals, aus denen lambda ableitbar ist */
{ BS_Set NonLambdaProds = BS_create(PrsGen->ProdCnt); 
  bool newElements = False; int i;

  for( i=0; i < PrsGen->ProdCnt; ++i )
  {
    if( ! PrsGen->ProdTab[i].symcnt )
    {
      BS_setE(NTIDX(PrsGen->ProdTab[i].id),PrsGen->LambdaSet); 
      newElements = True;
    }
  }
  while( newElements )
  {
    newElements = False;
    for( i=0; i < PrsGen->ProdCnt; ++i )
    {
      if( ! BS_member(NTIDX(PrsGen->ProdTab[i].id),PrsGen->LambdaSet) &&
          ! BS_member(i,NonLambdaProds)                                )
      { int j;

        for( j=0; j < PrsGen->ProdTab[i].symcnt; ++j )
        {
          if( isToken(PrsGen,PrsGen->ProdTab[i].symbols[j]) )
          {
            BS_setE(i,NonLambdaProds); break;
          }
          else
            if( ! BS_member(NTIDX(PrsGen->ProdTab[i].symbols[j]),PrsGen->LambdaSet) ) 
              break;
        }
        if( j == PrsGen->ProdTab[i].symcnt )
        {
          BS_setE(NTIDX(PrsGen->ProdTab[i].id),PrsGen->LambdaSet); 
          newElements = True;
        }
      }
    }
  }
  BS_delS(NonLambdaProds);
}

/* ----------------------------- State Table -------------------------------- */

/* ------------------------- LALR(0) Elements ------------------------------- */

static void fillNtRelSet(PrsGen_T* PrsGen)
/* Bestimmung der Nonterminal-Relation und deren Huelle */
{ int i;

  for( i=0; i < PrsGen->ProdCnt; ++i )
    if( PrsGen->ProdTab[i].symcnt && 
        isNonTerm(PrsGen,PrsGen->ProdTab[i].symbols[0]) )
      BS_setGE
      (
        PrsGen->NtRelSet,NONTERMCNT,
        NTIDX(PrsGen->ProdTab[i].id)+1, 
        NTIDX(PrsGen->ProdTab[i].symbols[0])+1
      );
  BS_closure(PrsGen->NtRelSet,PrsGen->NtRelSet,NONTERMCNT);
}

static void Huelle(PrsGen_T* PrsGen, PSTATE* state)
/* LALR(0)-Huelle einer Menge von Kernelementen */
{ INT i;

  BS_init(PrsGen->NonTermSet);
  for( i=0; i < OL_CNT(state->kern); ++i )
  { INT curr = ( ! i ) ? FST_INTLE(state->kern) : NXT_INTLE(state->kern);
    int idx = PRODUCTION(curr) - 1, pos = POSITION(curr) - 1;

    if( pos != PrsGen->MaxSymCnt && 
        isNonTerm(PrsGen,PrsGen->ProdTab[idx].symbols[pos]) )
    { int row = NTIDX(PrsGen->ProdTab[idx].symbols[pos])+1, j;

      for( j=1; j <= NONTERMCNT; ++j )
        if( BS_member(BS_RELEL(row,j,NONTERMCNT)-1,PrsGen->NtRelSet) )
          BS_setE(j-1,PrsGen->NonTermSet);
    }
  }
}

static void Sprung(PrsGen_T* PrsGen, OL_Lst Von)
/* Tabelle der Liste von Folge-LALR(0)-Kernen, */
/* ausgehend von den Kernelementen in Von und  */
/* den Huellenelementen in NonTermSet          */
{ OL_Lst Nach; INT i, j;

  for( i=0; i < OL_CNT(Von); ++i )
  { INT curr = ( ! i ) ? FST_INTLE(Von) : NXT_INTLE(Von);
    int idx = PRODUCTION(curr) - 1, pos = POSITION(curr) - 1;

    if( pos != PrsGen->MaxSymCnt )
    {
      Nach = GET_KLIST(PrsGen->GoToKern,PrsGen->ProdTab[idx].symbols[pos]);
      INSS_INTLE(nextProdElement(PrsGen,curr),Nach);
    }
  }
  for( i=0; i < NONTERMCNT; ++i )
  {
    if( BS_member(i,PrsGen->NonTermSet) )
    {
      for( j = FIRSTNTPROD(NTSYMBOL(i)); j <= LASTNTPROD(NTSYMBOL(i)); ++j )
      {
        if( PrsGen->ProdTab[j].symcnt )
        {
          Nach = GET_KLIST(PrsGen->GoToKern,PrsGen->ProdTab[j].symbols[0]);
          INSS_INTLE(nextProdElement(PrsGen,KERNELEMENT(j,1)),Nach);
        }
      }
    }
  }
}

static void setLambdaProdElements(PrsGen_T* PrsGen, PSTATE* curr)
/* Hinzufuegen der Lambdaproduktionen zu den LALR(0)-Elementen in curr */
{ int i, j;

  for( i=0; i < NONTERMCNT; ++i )
  {
    if( BS_member(i,PrsGen->NonTermSet) )
    {
      for( j = FIRSTNTPROD(NTSYMBOL(i)); j <= LASTNTPROD(NTSYMBOL(i)); ++j )
      {
        if( ! PrsGen->ProdTab[j].symcnt )
        { INT element = KERNELEMENT(j,PrsGen->MaxSymCnt+1),
              pos     = FND_INTLE(element,curr->kern);

          if( ! pos || element != CURR_INTLE(curr->kern) )
          { BS_Set lahead = BS_create(TERMCNT);

            if( ! pos )
            {
              INST_INTLE(element,curr->kern); INS_LOOK(lahead,curr->looks);
            }
            else
            {
              INSC_INTLE(element,curr->kern); INSN_LOOK(lahead,curr->looks,pos);
            }
          }
        }
      }
    }
  }
}

static void setInitialStates(PrsGen_T* PrsGen)
/* Bestimmung der Startzustaende */
{ PSTATE newState; int i;

  for( i=0; i < PrsGen->Kfg->StartCnt; ++i )
  { INT element = KERNELEMENT(PrsGen->ProdCnt-PrsGen->Kfg->StartCnt+i,1);
    BS_Set lahead = BS_create(TERMCNT);

    newState.symbol = -1;
    newState.looks  = NEW_LOOKTAB;
    BS_setE(ACCEPTTK(i),lahead);
    INS_LOOK(lahead, newState.looks);
    newState.kern   = NEW_INTLIST;
    newState.states = NEW_INTLIST;
    INST_INTLE(element, newState.kern);
    INS_STATE(&newState,PrsGen->StateTab);
  }
}

static bool existsFollowState(PrsGen_T* PrsGen, PSTATE* curr, OL_Lst newKLst)
/* Der Parserzustand ( LALR(0)-Kernelement-Menge ) ist bereits vorhanden */
{ INT i;

  for( i=0; i < OT_CNT(PrsGen->StateTab); ++i )
  {
    if( OL_EQUAL(GET_STATE(PrsGen->StateTab,i)->kern,newKLst) )
    { INT pos = FND_INTLE(i,curr->states);

      if( ! pos ) INST_INTLE(i,curr->states);
      else
      {
        if( i != CURR_INTLE(curr->states) ) INSC_INTLE(i,curr->states);
      }
      return( True );
    }
  }
  return( False );
}

static void setStates(PrsGen_T* PrsGen)
/* Bestimmung der Parserzustaende und der Mengen von LALR(0)-Kernelementen */
{ PSTATE* curr; PSTATE newState; INT i; int j;

  setInitialStates(PrsGen);
  for( i=0; i < OT_CNT(PrsGen->StateTab); ++i )
  {
    curr = GET_STATE(PrsGen->StateTab,i);
    Huelle(PrsGen,curr); Sprung(PrsGen,curr->kern);
    for( j=0; j < KFGSYMCNT; ++j )
    {
      if( OL_CNT(GET_KLIST(PrsGen->GoToKern,j)) )
      {
        if( ! existsFollowState(PrsGen,curr,GET_KLIST(PrsGen->GoToKern,j)) )
        { INT StateId, k;

          newState.symbol = j;
          newState.looks  = NEW_LOOKTAB;
          newState.states = NEW_INTLIST;
          newState.kern   = NEW_INTLIST;
          OL_COPY_L(newState.kern,GET_KLIST(PrsGen->GoToKern,j));
          OL_INIT(GET_KLIST(PrsGen->GoToKern,j));
          for( k=0; k < OL_CNT(newState.kern); ++k )
          { BS_Set lahead = BS_create(TERMCNT);

            INS_LOOK(lahead,newState.looks);
          }
          INS_STATE(&newState,PrsGen->StateTab);
          StateId = OT_CNT(PrsGen->StateTab) - 1;
          INST_INTLE(StateId,curr->states);
          if( isNonTerm(PrsGen,j) ) 
            INS_INTTE((int)StateId,PrsGen->NonTermTab[NTIDX(j)].states);
        }
        else OL_CLEAR(GET_KLIST(PrsGen->GoToKern,j));
      }
    }
  }
  for( i=0; i < OT_CNT(PrsGen->StateTab); ++i )
  {
    curr = GET_STATE(PrsGen->StateTab,i);
    Huelle(PrsGen,curr); setLambdaProdElements(PrsGen,curr);
  }
}

/* ------------------------- LALR(1) Elements ------------------------------- */

static void createProdLaheads(PrsGen_T* PrsGen)
/* Erzeugen der Lookahead-Sets der Huellen-Elemente ( Produktionen ) */
{ int i;

  PrsGen->PLaheads = (BS_Set*)NewMem(sizeof(BS_Set)*PrsGen->ProdCnt);
  for( i=0; i < PrsGen->ProdCnt; ++i ) 
    PrsGen->PLaheads[i] = BS_create(TERMCNT);
}

static void initProdLaheads(PrsGen_T* PrsGen)
/* ( Re- ) Initialisierung der aktuellen Lookahead-Sets der Huellen-Elemente */
{ int i;

  for( i=0; i < PrsGen->ProdCnt; ++i ) BS_init(PrsGen->PLaheads[i]);
}

static void delProdLaheads(PrsGen_T* PrsGen)
/* Loeschen der Lookahead-Sets der Huellen-Elemente */
{ int i;

  for( i=0; i < PrsGen->ProdCnt; ++i ) BS_delS(PrsGen->PLaheads[i]);
  FreeMem(PrsGen->PLaheads);
}

static void LaheadHuelle(PrsGen_T* PrsGen, INT element, BS_Set lahead)
/* Lookahead-Huelle fuer das Kernelement element */
{ int idx = PRODUCTION(element) - 1, pos = POSITION(element) - 1;
  bool newElements = True;

  if( pos != PrsGen->MaxSymCnt && 
      isNonTerm(PrsGen,PrsGen->ProdTab[idx].symbols[pos]) )
  /* Fuer ein Reduktionselement sind die zulaessigen Folgesymbole */
  /* bereits vollstaendig bestimmt.                               */
  /* Nur ein "Nonterminal"-Kernelement kann fuer die - indirekt - */
  /* zu diesem Nonterminal gehoerenden Reduktionselemente         */
  /* zulaessige Folgesymbole liefern.                             */
  { int i, j;

    BS_init(PrsGen->TokenSet);
    if( pos + 1 < PrsGen->ProdTab[idx].symcnt )
    {
      if( FirstSetForSymbols
          (PrsGen,PrsGen->ProdTab[idx].symcnt-(pos+1),
           &PrsGen->ProdTab[idx].symbols[pos+1]) )
        BS_union(PrsGen->TokenSet,PrsGen->TokenSet,lahead);
    }
    else BS_union(PrsGen->TokenSet,PrsGen->TokenSet,lahead);
    for( i = 0; i < NONTERMCNT; ++i )
      if( BS_member(i,PrsGen->NonTermSet) && 
          NTSYMBOL(i) == PrsGen->ProdTab[idx].symbols[pos] )
        for( j = FIRSTNTPROD(NTSYMBOL(i)); j <= LASTNTPROD(NTSYMBOL(i)); ++j )
          BS_union(PrsGen->PLaheads[j],PrsGen->PLaheads[j],PrsGen->TokenSet);

    /* Vervollstaendigung der Lookahead-Huelle fuer das aktuelle Kernelement */
    while( newElements )
    {
      newElements = False;
      for( i=0; i < PrsGen->ProdCnt; ++i )
      {
        if( ! BS_empty(PrsGen->PLaheads[i]) && PrsGen->ProdTab[i].symcnt )
        {
          BS_init(PrsGen->TokenSet);
          if( PrsGen->ProdTab[i].symcnt > 1 )
          {
            if( FirstSetForSymbols
                (PrsGen,PrsGen->ProdTab[i].symcnt-1,
                 &PrsGen->ProdTab[i].symbols[1]) )
              BS_union(PrsGen->TokenSet,PrsGen->TokenSet,PrsGen->PLaheads[i]);
          }
          else BS_union(PrsGen->TokenSet,PrsGen->TokenSet,PrsGen->PLaheads[i]);
          for( j=0; j < PrsGen->ProdCnt; ++j )
            if( PrsGen->ProdTab[i].symbols[0] == PrsGen->ProdTab[j].id &&
                addNewMembers(PrsGen->PLaheads[j],PrsGen->PLaheads[j],PrsGen->TokenSet) )
              newElements = True;
        }
      }
    }
  }
}

static bool setFollowLaheads(PrsGen_T* PrsGen, PSTATE* curr)
/* Bestimmung der Lookahead-Elemente fuer jeden Folgezustand von curr */
{ bool newElements = False; INT i;

  for( i=0; i < OL_CNT(curr->kern); ++i )
  { INT element = ( ! i ) ? FST_INTLE(curr->kern) : NXT_INTLE(curr->kern);
    BS_Set lahead = GET_LOOK(curr->looks,i);

    if( POSITION(element) != PrsGen->MaxSymCnt+1 )
    { OL_Lst readLst = NEW_INTLIST; INT j;

      element = nextProdElement(PrsGen,element);
      for( j=0; j < OL_CNT(curr->states); ++j )
      { INT FState = ( ! j ) ? 
                     FST_INTLE(curr->states) : NXT_INTLE(curr->states);
        PSTATE* follow = GET_STATE(PrsGen->StateTab,FState);
        BS_Set FSet; INT pos, k;

        OL_COPY_L(readLst,follow->kern);
        pos = FND_INTLE(element,readLst);
        if( pos && element == CURR_INTLE(readLst) )
        {
          FSet = GET_LOOK(follow->looks,pos-1);
          if( addNewMembers(FSet,FSet,lahead) )
          {
            BS_setE(FState,PrsGen->StateSet); newElements = True;
          }
        }
        for( k=0; k < OL_CNT(readLst); ++k )
        { INT FElement = ( ! k ) ? FST_INTLE(readLst) : NXT_INTLE(readLst);
          int idx = PRODUCTION(FElement) - 1;

          if( PrsGen->ProdTab[idx].symcnt )
          { INT prevE = prevProdElement(PrsGen,FElement);

            if( ! BS_empty(PrsGen->PLaheads[idx]) && POSITION(prevE) == 1 &&
                PrsGen->ProdTab[idx].symbols[0] == follow->symbol          )
            {
              FSet = GET_LOOK(follow->looks,k);
              if( addNewMembers(FSet,FSet,PrsGen->PLaheads[idx]) )
              {
                BS_setE(FState,PrsGen->StateSet); newElements = True;
              }
            }
          }
        }
      }
      OL_DEL_C(readLst);
    }
  }
  return( newElements );
}

static void setLambdaProdLaheads(PrsGen_T* PrsGen, PSTATE* curr)
/* Bestimmung der Lookahead-Elemente fuer die Lambdaproduktionen in curr */
{ int i;

  for( i=0; i < PrsGen->ProdCnt; ++i )
  {
    if( ! PrsGen->ProdTab[i].symcnt && ! BS_empty(PrsGen->PLaheads[i]) )
    { INT element = KERNELEMENT(i,PrsGen->MaxSymCnt+1),
          pos     = FND_INTLE(element,curr->kern);

      if( pos && element == CURR_INTLE(curr->kern) )
      { BS_Set lahead = GET_LOOK(curr->looks,pos-1);

        addNewMembers(lahead,lahead,PrsGen->PLaheads[i]);
      }
    }
  }
}

static bool setLaheads(PrsGen_T* PrsGen, PSTATE* curr)
/* Bestimmung der von curr spontan generierten und sich */
/* ausbreitenden Lookahead-Elemente                     */
{ INT i;

  Huelle(PrsGen,curr); initProdLaheads(PrsGen);
  for( i=0; i < OL_CNT(curr->kern); ++i )
  { INT element = ( ! i ) ? FST_INTLE(curr->kern) : NXT_INTLE(curr->kern);

    LaheadHuelle(PrsGen,element,GET_LOOK(curr->looks,i));
  }
  setLambdaProdLaheads(PrsGen,curr);
  return( setFollowLaheads(PrsGen,curr) );
}

static void fillStateTab(PrsGen_T* PrsGen)
/* Bestimmung der Parserzustaende und der Mengen von LALR(1)-Kernelementen */
{ bool newElements = True; INT i;
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stderr;

  if( PrsGen->profile ) 
    (*prMsg)("creating LALR(0)-Elements ...\n");
  setStates(PrsGen);
  BUG_RNG1(OT_CNT(PrsGen->StateTab),MAX_OBJECTS);
  if( PrsGen->profile ) 
    (*prMsg)("creating LALR(1)-Elements ...\n");
  PrsGen->StateSet = BS_create(OT_CNT(PrsGen->StateTab));
  createProdLaheads(PrsGen);
  for( i=0; i < PrsGen->Kfg->StartCnt; ++i ) 
    BS_setE(i,PrsGen->StateSet);
  while( newElements )
  {
    newElements = False;
    for( i=0; i < OT_CNT(PrsGen->StateTab); ++i )
    {
      if( BS_member(i,PrsGen->StateSet) )
      {
        BS_delE(i,PrsGen->StateSet);
        if( setLaheads(PrsGen,GET_STATE(PrsGen->StateTab,i)) ) 
          newElements = True;
      }
    }
  }
  delProdLaheads(PrsGen);
}

/* --------------------------- Parse Tables --------------------------------- */

static INT setStateShifts(PrsGen_T* PrsGen, INT idx, OT_Tab shifts)
/* Shift-FolgeZustaende fuer 'StateTab[idx]' */
{ OL_Lst StateLst; INT State, i;

  StateLst = GET_STATE(PrsGen->StateTab,idx)->states;
  for( i=0; i < OL_CNT(StateLst); ++i )
  {
    State = ( ! i ) ? FST_INTLE(StateLst) : NXT_INTLE(StateLst);
    if( isToken( PrsGen, GET_STATE(PrsGen->StateTab,State)->symbol ) )
      INS_INTTE((-(State+1)),shifts);
  }
  return( OT_CNT(shifts) );
}

static INT findStateShifts
           (
             OT_Tab shifts, OT_Tab MstShift, OT_Tab DtlShift
           )
/* finden des Zustands mit identischen Shift-FolgeZustaenden ( oder -1 ) */
{ INT cnt = OT_CNT(MstShift), i, j, k;
  
  for( i=0; i < cnt; ++i )
  { int dcnt = 0;

    if( ( k = j = ( GET_INTTE(MstShift,i) - 1 ) ) >= 0 )
    {
      for( ; j >= 0; --j )
        if( GET_INTTE(DtlShift,j) < 0 ) ++dcnt;
        else                            break;
      if( ( j = OT_CNT(shifts) ) == dcnt )
      { bool equality = True;

        for( j -= 1; j >= 0; --j, --k )
          if( GET_INTTE(DtlShift,k) != GET_INTTE(shifts,j) )
          {
            equality = False; break;
          }
        if( equality ) return( i );
      }
    }
  }
  return( -1 );
}

static void fillShiftTabs(PrsGen_T* PrsGen, OT_Tab MstShift, OT_Tab DtlShift)
/* Bestimmung der Shift-Tabellen                                            */
/* MstShift : 1 Eintrag / Zustand --- DtlShift-Index des 1. Symbols oder -1 */
/* DtlShift : Liste von Eintraegen fuer jeden Zustand mit Shift-Aktionen    */
/*            ( -(StateIdx1+1), ..., -(StateIdxN+1) ,TokenN, ..., Token1 )  */
{ OT_Tab cshifts = NEW_INTTAB; INT cnt, i, j;

  for( i=0; i < OT_CNT(PrsGen->StateTab); ++i )
  { int lalrel = -1;

    if( ! ( cnt = setStateShifts(PrsGen,i,cshifts) ) ) /* keine Shift-Folgezustaende */
      INS_INTTE(lalrel,MstShift);
    else
    { INT idx = findStateShifts(cshifts,MstShift,DtlShift);

      if( idx >= 0 ) /* vorhandene Shift-Folgezustaende */
        INS_INTTE(GET_INTTE(MstShift,idx),MstShift);
      else /* neue Shift-Folgezustaende */
      { 
        lalrel = (int)(OT_CNT(DtlShift) + cnt); INS_INTTE(lalrel,MstShift);
        for( j=0; j < cnt; ++j ) INS_INTTE(GET_INTTE(cshifts,j),DtlShift);
        for( j=cnt-1; j >= 0; --j )
        {
          lalrel = GET_STATE(PrsGen->StateTab,ABS((GET_INTTE(cshifts,j)+1)))->symbol;
          INS_INTTE(lalrel,DtlShift);
        }
      }
    }
    OT_CLEAR(cshifts);
  }
  OT_DEL_T(cshifts);
}

static void setStateGoTos(PrsGen_T* PrsGen, INT idx, OT_Tab GoToDft, bool sign)
/* GoTo-QuellZustaende fuer Zielzustand 'StateTab[idx]' */
{ OL_Lst StateLst; INT State, cnt = OT_CNT(PrsGen->StateTab), i, j;

  for( i=0; i < cnt; ++i )
  {
    StateLst = GET_STATE(PrsGen->StateTab,i)->states;
    for( j=0; j < OL_CNT(StateLst); ++j )
    {
      State = ( ! j ) ? FST_INTLE(StateLst) : NXT_INTLE(StateLst);
      if( State == idx ) 
        INS_INTTE(sign?(int)(-(i+1)):(int)(i+1),GoToDft);
    }
  }
}

static void fillGoToTabs(PrsGen_T* PrsGen, OT_Tab GoTo, OT_Tab GoToDft)
/* Bestimmung der Sprungtabellen                                              */
/* GoTo    : 1 Eintrag / Nonterminal -- Index des 1. GoToDft-Eintrags         */
/* GoToDft : Folge von Eintraegen der Art                                     */
/* (old)     'toStateIdx+1+StateCnt, [ fromStateIdx+1 ... | 0 ( Default ) ]'  */
/* (new)     'toStateIdx+1+StateCnt, [ [- (Default) ] (fromStateIdx+1) ... ]' */
{ int  lalrel, i;
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stderr;

  for( i=0; i < NONTERMCNT && isNonTerm(PrsGen,NTSYMBOL(i)); ++i )
  { INT cnt = OT_CNT(PrsGen->NonTermTab[i].states), j;

    INS_INTTE((int)OT_CNT(GoToDft),GoTo);
    if( cnt <= 1 )
    {
      if( cnt == 1 ) /* unique StateSymbol */
      {
        lalrel = (int)(OT_CNT(PrsGen->StateTab)+
                       GET_INTTE(PrsGen->NonTermTab[i].states,0)+1); 
        INS_INTTE(lalrel,GoToDft); 
        setStateGoTos
        (
          PrsGen,GET_INTTE(PrsGen->NonTermTab[i].states,0),GoToDft,True
        );
      }
      else /* unreacheable NonTerminal */
      {
        (*prMsg)("Warning: unreacheable Nonterminal '");
        (*prMsg)(PrsGen->Kfg->SNames[NTSYMBOL(i)]);
        (*prMsg)("'\n");
        INS_INTTE(0,GoToDft);
      }
    }
    else /* more than one State with StateSymbol */
    { 
      for( j=0; j < cnt; ++j )
      { 
        lalrel = (int)(OT_CNT(PrsGen->StateTab)+
                       GET_INTTE(PrsGen->NonTermTab[i].states,j)+1); 
        INS_INTTE(lalrel,GoToDft);
        setStateGoTos
        (
          PrsGen,GET_INTTE(PrsGen->NonTermTab[i].states,j),GoToDft,False
        );
      }
    }
  }
}

static int nextRedElement
           (
             PrsGen_T* PrsGen, PSTATE* state, int* RedElement, int idx
           )
/* Position der/s ersten/naechsten Reduktionselements des Zustands oder 0 */
/* RedElement enthaelt nach Aufruf das Reduktionselement ( ProdIdx + 1 )  */
{ INT i;

  for( i=idx; i < OL_CNT(state->kern); ++i )
  { INT element = ( ! i ) ? FST_INTLE(state->kern) : NXT_INTLE(state->kern);

    if( POSITION(element) == PrsGen->MaxSymCnt + 1 )
      return( ( *RedElement = PRODUCTION(element) ), (int)(i+1) );
  }
  return( 0 );
}

static int RedAction(PrsGen_T* PrsGen, int RedElement)
/* Reduktionselement ( Index der Produktion + 1 ) oder ACT_ACCEPT */
{
  return ( isNonTerm(PrsGen,PrsGen->ProdTab[RedElement-1].id) ) 
         ? RedElement : ACT_ACCEPT;
}

static void fillActExpLst
            (
              PrsGen_T* PrsGen, OT_Tab ActExp, int RedElement, 
              BS_Set lahead, bool negFlg
            )
/* Bestimmung der Ausnahme-Aktionen fuer das Reduktionselement */
/* Alternierende +/- Folge von Eintraegen der Art              */
/* 'PROD_OFFSET + Red.Nr ( >= 1 ), Token ( >= 1 ) ...' fuer    */
/* jeden Zustand mit mehreren Reduktionselementen              */
{ int lalrel = RedAction(PrsGen,RedElement),
      i      = ( lalrel != ACT_ACCEPT ) ? 0 : PrsGen->Kfg->TkCnt;

  lalrel += PROD_OFFSET;
  lalrel  = ( negFlg ) ? -lalrel : lalrel; INS_INTTE(lalrel,ActExp);
  for( ; i < TERMCNT; ++i )
  {
    if( BS_member(i,lahead) )
    {
      lalrel = ( negFlg ) ? -(i+1) : i+1; INS_INTTE(lalrel,ActExp);
    }
  }
}

static void fillActTabs(PrsGen_T* PrsGen, OT_Tab ActDft, OT_Tab ActExp)
/* Bestimmung der Default/Ausnahme-Aktionstabellen                          */
/* ActDft : 1 Eintrag / Zustand -- ACT_ACCEPT, ACT_ERROR, Red.Nr ( >= 1 ),  */
/*                                 negativer Index des 1. ActExp-Eintrags   */
/* ActExp : siehe fillActExpLst                                             */
{ INT i;

  for( i=0; i < OT_CNT(PrsGen->StateTab); ++i )
  { PSTATE* curr = GET_STATE(PrsGen->StateTab,i);
    int lalrel = ACT_ERROR, FstRedElement, RedElement, pos;
    int FstPos = nextRedElement(PrsGen,curr,&FstRedElement,0);

    if( ! FstPos ) /* Default-Aktion: ACT_ERROR */
      INS_INTTE(lalrel,ActDft);
    else
    {
      pos = nextRedElement(PrsGen,curr,&RedElement,FstPos);
      if( ! pos ) /* Default-Aktion: ACT_ACCEPT/Reduktion */
      { /* veraenderte Bedingung fuer Fehlerbehandlung */
        lalrel = RedAction(PrsGen,FstRedElement); 
        INS_INTTE(lalrel,ActDft);
      }
      else /* Ausnahme-Aktionen: ACT_ACCEPT/Reduktion */
      { bool negFlg = ( ! OT_CNT(ActExp) || 
                        GET_INTTE(ActExp,OT_CNT(ActExp)-1) < 0 )
                      ? False : True;

        lalrel = (int)(-OT_CNT(ActExp)); INS_INTTE(lalrel,ActDft);
        fillActExpLst
        (
          PrsGen,ActExp,FstRedElement,GET_LOOK(curr->looks,FstPos-1),negFlg
        );
        while( pos > 0 )
        {
          fillActExpLst
          (
            PrsGen,ActExp,RedElement,GET_LOOK(curr->looks,pos-1),negFlg
          );
          pos = nextRedElement(PrsGen,curr,&RedElement,pos);
        }
      }
    }
  }
}

static PLR_Tab fillParseTab(PrsGen_T* PrsGen)
/* Bestimmung der Analyse-Tabellen der Grammatik */
{ PARSETAB* PTab  = (PARSETAB*)NewMem(sizeof(PARSETAB));
  OT_Tab MstShift = NEW_INTTAB;
  OT_Tab DtlShift = NEW_INTTAB;
  OT_Tab GoTo     = NEW_INTTAB;
  OT_Tab GoToDft  = NEW_INTTAB;
  OT_Tab ActDft   = NEW_INTTAB;
  OT_Tab ActExp   = NEW_INTTAB;

  PTab->Kfg     = PrsGen->Kfg;
  PTab->ProdCnt = PrsGen->ProdCnt;
  PTab->Prod    = PrsGen->ProdTab;

  fillShiftTabs(PrsGen,MstShift,DtlShift);
  BUG_VMIN(PTab->tabs.MstShiftCnt = (int)OT_CNT(MstShift),0);
  PTab->tabs.MstShift    = INTTE_ARRAY(MstShift);
  OT_DEL_T(MstShift);
  PTab->tabs.DtlShiftCnt = (int)OT_CNT(DtlShift);
  PTab->tabs.DtlShift    = INTTE_ARRAY(DtlShift);
  OT_DEL_T(DtlShift);

  fillGoToTabs(PrsGen,GoTo,GoToDft);
  BUG_VMIN(PTab->tabs.GoToCnt = (int)OT_CNT(GoTo),0);
  PTab->tabs.GoTo       = INTTE_ARRAY(GoTo);
  OT_DEL_T(GoTo);
  BUG_VMIN(PTab->tabs.GoToDftCnt = (int)OT_CNT(GoToDft),0);
  PTab->tabs.GoToDft    = INTTE_ARRAY(GoToDft);
  OT_DEL_T(GoToDft);

  fillActTabs(PrsGen,ActDft,ActExp);
  BUG_VMIN(PTab->tabs.ActDftCnt = (int)OT_CNT(ActDft),0);
  PTab->tabs.ActDft    = INTTE_ARRAY(ActDft);
  OT_DEL_T(ActDft);
  PTab->tabs.ActExpCnt = (int)OT_CNT(ActExp);
  PTab->tabs.ActExp    = INTTE_ARRAY(ActExp);
  OT_DEL_T(ActExp);

  return( PTab );
}

/* ---------------------------- Printing ------------------------------------ */

static void printINTObj(StdCPtr obj, Any_T any, int nl, c_bool last)
/* prints an INT-object */
{ PrsGen_T* PrsGen = (PrsGen_T*)any;
  char      buf[STD_BUFFLEN+1];
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stdout;
  if( nl > 0 )
  {
    sprintf(buf,"\n%*s",nl,"");
    (*prMsg)(buf);
  }
  sprintf(buf,"%ld%s",(long)obj,(last?"":", "));
  (*prMsg)(buf);
}

static void printTokSet(PrsGen_T* PrsGen, BS_Set s)
/* prints a token set */
{ int i;
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stdout;

  (*prMsg)("{");
  for( i=0; i < TERMCNT; ++i )
    if( BS_member(i,s) )
    {
      (*prMsg)(" \"");
      if( i < PrsGen->Kfg->TkCnt )
        (*prMsg)(PrsGen->Kfg->SNames[i]);
      else
        (*prMsg)("Accept");
      (*prMsg)("\" ");
    }
  (*prMsg)("}");
}

static void printFirstNtSets(PrsGen_T* PrsGen)
/* prints first sets */
{ int i;
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stdout;

  (*prMsg)("\n--- First Sets ---\n\n"); 
  for( i=0; i < NONTERMCNT; ++i )
  {
    (*prMsg)("First "); 
    (*prMsg)((i<PrsGen->Kfg->NtCnt)?PrsGen->Kfg->SNames[NTSYMBOL(i)]:"Start"); 
    (*prMsg)(BS_member(i,PrsGen->LambdaSet) ? "(lambda)" : ""); 
    (*prMsg)(" = "); 
    printTokSet(PrsGen,FIRSTSET(NTSYMBOL(i))); 
    (*prMsg)("\n"); 
  }
}

static void ShiftConflicts
            (
              PrsGen_T* PrsGen,BS_Set cl,OL_Lst states,bool printing
            )
/* prints shift-reduce conflicts for current kern element */
{ bool flag = False; INT i;
  char buf[STD_BUFFLEN+1];
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stdout;

  for( i=0; i < OL_CNT(states); ++i )
  { INT fs = ( ! i ) ? FST_INTLE(states) : NXT_INTLE(states);
    int symbol = GET_STATE(PrsGen->StateTab,fs)->symbol;

    if( isToken(PrsGen,symbol) && BS_member(symbol,cl) )
    {
      if( printing )
      {
        sprintf(buf,"\n%*sShift-Reduce-Konflikt mit Shift '",indent,"");
        (*prMsg)(buf);
        (*prMsg)(PrsGen->Kfg->SNames[symbol]);
        sprintf(buf,"' zu Zustand: %ld", (long)fs);
        (*prMsg)(buf);
        flag = True;
      }
      ++PrsGen->conflictCnt;
    }
  }
  if( flag ) (*prMsg)("\n"); 
}

static void RedConflicts
            (
              PrsGen_T* PrsGen,int clidx,BS_Set cl,
              OT_Tab looks,OL_Lst readLst,bool printing
            )
/* prints reduce-reduce conflicts for current kern element */
{ bool flag = False; INT i;
  char buf[STD_BUFFLEN+1];
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stdout;

  for( i = clidx + 1; i < OL_CNT(readLst); ++i )
  { INT fk = NXT_INTLE(readLst); int pos = POSITION(fk);

    if( pos == PrsGen->MaxSymCnt + 1 &&
        ! BS_empty(BS_inter(PrsGen->TokenSet,cl,GET_LOOK(looks,i))) )
    {
      if( printing )
      { int idx = PRODUCTION(fk) - 1, id = PrsGen->ProdTab[idx].id; 
        char c = ' ';

        if( id >= KFGSYMCNT )
        {
          id = PrsGen->Kfg->StartIds[id-KFGSYMCNT]; c  = '\'';
        }
        sprintf(buf,"\n%*sReduce-Reduce-Konflikt mit Element: ",indent,"");
        (*prMsg)(buf);
        (*prMsg)(PrsGen->Kfg->SNames[id]);
        sprintf(buf,"%c ( %3d )", c, pos);
        (*prMsg)(buf);
        flag = True;
      }
      ++PrsGen->conflictCnt;
    }
  }
  if( flag ) (*prMsg)("\n"); 
}

static void printStateTab(PrsGen_T* PrsGen)
/* prints state table and conflicts */
{ OL_Lst readLst = NEW_INTLIST; INT i, k; int cnt;
  char   buf[STD_BUFFLEN+1];
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stdout;

  (*prMsg)("\n--- State Table and Conflicts ---\n\n");
  for( i=0; i < OT_CNT(PrsGen->StateTab); ++i )
  { PSTATE* curr = GET_STATE(PrsGen->StateTab,i);

    sprintf(buf,"State: %3d / Symbol: ", (int)i);
    (*prMsg)(buf);
    if( curr->symbol == -1 ) (*prMsg)("None");
    else 
      (*prMsg)(PrsGen->Kfg->SNames[curr->symbol]);
    sprintf(buf,"\n\n%*sFollow States:",indent,"");
    (*prMsg)(buf);
    PRT_INTLES(curr->states,indent+2);
    sprintf(buf,"\n\n%*sLALR(1) - Elements:",indent,"");
    (*prMsg)(buf);
    for( k=0; k < OL_CNT(curr->kern); ++k )
    { INT ck = ( ! k ) ? FST_INTLE(curr->kern) : NXT_INTLE(curr->kern);
      int idx = PRODUCTION(ck) - 1, 
          pos = POSITION(ck), 
          id  = PrsGen->ProdTab[idx].id, j;
      BS_Set cl = GET_LOOK(curr->looks,k); char c = ' ';

      OL_COPY_L(readLst,curr->kern);
      if( id >= KFGSYMCNT )
      {
        id = PrsGen->Kfg->StartIds[id-KFGSYMCNT]; c = '\'';
      }
      sprintf(buf,"\n%*s",indent+2,"");
      (*prMsg)(buf);
      (*prMsg)(PrsGen->Kfg->SNames[id]);
      sprintf(buf,"%c ( %3d ) :: ",c,pos);
      (*prMsg)(buf);
      if( c != '\'' )
      { int fstcol = indent + 2 + strlen(PrsGen->Kfg->SNames[id]) + 13;

        for( j=0; j < PrsGen->ProdTab[idx].symcnt; ++j )
        {
          if( ! ( j % MAX_PR_SCOLS ) && j ) TAB(fstcol);
          if( pos == j+1 ) fprintf(STDOUT,"^ ");
          (*prMsg)(PrsGen->Kfg->SNames[PrsGen->ProdTab[idx].symbols[j]]);
          (*prMsg)(" ");
        }
        if( pos == PrsGen->MaxSymCnt + 1 ) (*prMsg)("^");
      }
      else
      {
        if( pos == 1 ) (*prMsg)("^ ");
        (*prMsg)(PrsGen->Kfg->SNames[id]);
        (*prMsg)(" ");
        if( pos == PrsGen->MaxSymCnt + 1 ) (*prMsg)("^");
      }
      sprintf(buf,"\n%*sLookaheads: ",indent+2,"");
      (*prMsg)(buf);
      for( j=0, cnt=0; j < TERMCNT; ++j )
      {
        if( BS_member(j,cl) )
        {
          if( ! ( cnt % MAX_PR_SCOLS ) && cnt ) 
          {
            sprintf(buf,"\n%*s",indent+14,"");
            (*prMsg)(buf);
          }
          if( j < PrsGen->Kfg->TkCnt ) 
          {
            (*prMsg)(PrsGen->Kfg->SNames[j]);
            (*prMsg)(" ");
          }
          else 
          {
            sprintf(buf,"Accept[%d] ",TKACCEPT(j));
            (*prMsg)(buf);
          }
          ++cnt;
        }
      }
      (*prMsg)("\n");
      if( pos == PrsGen->MaxSymCnt + 1 )
      {
        RedConflicts(PrsGen,(int)k,cl,curr->looks,readLst,True);
        ShiftConflicts(PrsGen,cl,curr->states,True);
      }
    }
    (*prMsg)("\n");
  }
  OL_DEL_C(readLst);
}

static void countConflicts(PrsGen_T* PrsGen)
/* counts conflicts */
{ OL_Lst readLst = NEW_INTLIST; INT i, k;

  for( i=0; i < OT_CNT(PrsGen->StateTab); ++i )
  { PSTATE* curr = GET_STATE(PrsGen->StateTab,i);

    for( k=0; k < OL_CNT(curr->kern); ++k )
    { INT ck = ( ! k ) ? FST_INTLE(curr->kern) : NXT_INTLE(curr->kern);
      int pos = POSITION(ck); BS_Set cl = GET_LOOK(curr->looks,k);

      OL_COPY_L(readLst,curr->kern);
      if( pos == PrsGen->MaxSymCnt + 1 )
      {
        RedConflicts(PrsGen,(int)k,cl,curr->looks,readLst,False);
        ShiftConflicts(PrsGen,cl,curr->states,False);
      }
    }
  }
  OL_DEL_C(readLst);
}

static void printNtClasses(PrsGen_T* PrsGen)
/* prints nonterminal classes */
{ int      i;
  c_string buf = (c_string)NewMem(2*PrsGen->MaxSymNamLen+80+1);
  void (*prMsg)(c_string msg) = PrsGen->prMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stdout;
  (*prMsg)("\n--- Nonterminal Classes ---\n\n");
  for( i=0; i < PrsGen->Kfg->NtCnt; ++i )
  {
    sprintf
    (
      buf,"%*s |--> %s\n",
      PrsGen->MaxSymNamLen,PrsGen->Kfg->SNames[NTSYMBOL(i)],
      PrsGen->Kfg->SNames[NTSYMBOL(NTCLASS(i))]
    );
    (*prMsg)(buf);
  }
  FreeMem(buf);
}

/*====================== Parser Generator Interface ==========================*/

/*I----------------------- Grammar definition ------------------------------- */

PLR_Cfg PLR_createCfg(string Language)
/* creates a context free grammar definition named 'Language' */
{ KFGDFN* cfg;

  BUG_NULL(Language);
  cfg           = (KFGDFN*)NewMem(sizeof(KFGDFN));
  cfg->language = StrCopy(Language);
  cfg->Token    = NEW_STRTAB;
  cfg->TkIdx    = (OT_Tab)NULL;
  cfg->NonTerm  = NEW_STRTAB;
  cfg->NtIdx    = (OT_Tab)NULL;
  cfg->StartNt  = NEW_INTTAB;
  cfg->TokKind  = NEW_INTTAB;
  cfg->ErrorNt  = OT_CREATE_ADT(bool);
  cfg->Prod     = NEW_PRODTAB;
  return( cfg );
}

int PLR_addTK(PLR_Cfg Cfg, string Token, int kind)
/* adds token 'Token' of type 'kind' 
   ( token or keyword, see [cfg_dfn] )
   to definition 'Cfg' 
*/
{
  BUG_NULL(Cfg); BUG_NULL(Token);
  BUG_VEQU(PLR_C_IMP(Cfg)->TkIdx,(OT_Tab)NULL);
  BUG_VEQU(CFG_TERMINAL(kind),True);
  INS_INTTE(kind,PLR_C_IMP(Cfg)->TokKind);
  return( (int)INS_STRTE(Token,PLR_C_IMP(Cfg)->Token) );
}

int PLR_addNT(PLR_Cfg Cfg, string NonTerm, bool catchError)
/* adds nonterminal 'NonTerm' to definition 'Cfg' 
   catchError --> use 'NonTerm' as reparse point
*/
{
  BUG_NULL(Cfg); BUG_NULL(NonTerm);
  BUG_VEQU(PLR_C_IMP(Cfg)->NtIdx,(OT_Tab)NULL);
  OT_PUSH(catchError,PLR_C_IMP(Cfg)->ErrorNt);
  return( (int)INS_STRTE(NonTerm,PLR_C_IMP(Cfg)->NonTerm) );
}

void PLR_endSD(PLR_Cfg Cfg)
/* symbol definition end; 
   completes token and nonterminal definition
*/
{
  BUG_NULL(Cfg);
  BUG_RNG0(OT_CNT(PLR_C_IMP(Cfg)->Token),MAX_OBJECTS);
  BUG_RNG1(OT_CNT(PLR_C_IMP(Cfg)->NonTerm),MAX_OBJECTS);
  PLR_C_IMP(Cfg)->TkIdx = SRT_STRTES(PLR_C_IMP(Cfg)->Token);
  PLR_C_IMP(Cfg)->NtIdx = SRT_STRTES(PLR_C_IMP(Cfg)->NonTerm);
}

int PLR_addSN(PLR_Cfg Cfg, string StartNt)
/* adds startsymbol 'StartNt' to definition 'Cfg' */
{ INT nt;

  BUG_NULL(Cfg); BUG_NULL(StartNt);
  BUG_VNEQ(PLR_C_IMP(Cfg)->NtIdx,(OT_Tab)NULL);
  nt = FND_STRTE(PLR_C_IMP(Cfg)->NonTerm,PLR_C_IMP(Cfg)->NtIdx,StartNt);
  BUG_VMIN(nt,0);
  nt = GET_INTTE(PLR_C_IMP(Cfg)->NtIdx,nt-1);
  return( (int)INS_INTTE((int)nt,PLR_C_IMP(Cfg)->StartNt) );
}

int PLR_addST(PLR_Cfg Cfg, string SpecTk)
/* marks 'SpecTk' as special comment token */
{ INT tk; int kind;

  BUG_NULL(Cfg); BUG_NULL(SpecTk);
  BUG_VNEQ(PLR_C_IMP(Cfg)->TkIdx,(OT_Tab)NULL);
  tk   = FND_STRTE(PLR_C_IMP(Cfg)->Token,PLR_C_IMP(Cfg)->TkIdx,SpecTk);
  BUG_VMIN(tk,0);
  tk   = GET_INTTE(PLR_C_IMP(Cfg)->TkIdx,tk-1);
  kind = CFG_TERM_TO_COM(GET_INTTE(PLR_C_IMP(Cfg)->TokKind,tk));
  UPD_INTTE(kind,PLR_C_IMP(Cfg)->TokKind,tk);
  return tk;
}

int PLR_addPR(PLR_Cfg Cfg, string PName, int Method, string NonTerm)
/* adds production 'NonTerm'::'PName' with layout hint 'Method' 
   ( default=0, see [prs_dfn] ) to definition 'Cfg' 
*/
{ PRDFN prod;

  BUG_NULL(Cfg); BUG_NULL(PName); BUG_NULL(NonTerm);
  BUG_RNG0(Method,PLR_PRD_NON);
  BUG_VNEQ(PLR_C_IMP(Cfg)->NtIdx,(OT_Tab)NULL);
  prod.pname   = StrCopy(PName);
  prod.method  = Method;
  prod.pid     = 
    (int)FND_STRTE(PLR_C_IMP(Cfg)->NonTerm,PLR_C_IMP(Cfg)->NtIdx,NonTerm);
  BUG_VMIN(prod.pid,0);
  prod.pid     = GET_INTTE(PLR_C_IMP(Cfg)->NtIdx,prod.pid-1);
  prod.psymbol = NEW_PSYMTAB;
  return( (int)INS_PROD(&prod,PLR_C_IMP(Cfg)->Prod) );
}

int PLR_addPT(PLR_Cfg Cfg, string Token, long sRow, long sCol)
/* adds token 'Token' to current production of definition 'Cfg'; 
   The symbol position 'sRow', 'sCol' is used as layout hint.
*/
{ PSDFN psym; INT idx;

  BUG_NULL(Cfg); BUG_NULL(Token);
  idx          = OT_CNT(PLR_C_IMP(Cfg)->Prod) - 1;
  BUG_VMIN(idx,-1);
  psym.symbol  = 
    (int)FND_STRTE(PLR_C_IMP(Cfg)->Token,PLR_C_IMP(Cfg)->TkIdx,Token);
  BUG_VMIN(psym.symbol,0);
  psym.symbol  = GET_INTTE(PLR_C_IMP(Cfg)->TkIdx,psym.symbol-1);
  psym.istoken = True;
  psym.sRow    = sRow;
  psym.sCol    = sCol;
  return( (int)INS_PSYM(&psym,GET_PROD(PLR_C_IMP(Cfg)->Prod,idx)->psymbol) );
}

int PLR_addPN(PLR_Cfg Cfg, string NonTerm, long sRow, long sCol)
/* adds nonterminal 'NonTerm' to current production of definition 'Cfg'; 
   The symbol position 'sRow', 'sCol' is used as layout hint.
*/
{ PSDFN psym; INT idx;

  BUG_NULL(Cfg); BUG_NULL(NonTerm);
  idx          = OT_CNT(PLR_C_IMP(Cfg)->Prod) - 1;
  BUG_VMIN(idx,-1);
  psym.symbol  =
    (int)FND_STRTE(PLR_C_IMP(Cfg)->NonTerm,PLR_C_IMP(Cfg)->NtIdx,NonTerm);
  BUG_VMIN(psym.symbol,0);
  psym.symbol  = GET_INTTE(PLR_C_IMP(Cfg)->NtIdx,psym.symbol-1);
  psym.istoken = False;
  psym.sRow    = sRow;
  psym.sCol    = sCol;
  return( (int)INS_PSYM(&psym,GET_PROD(PLR_C_IMP(Cfg)->Prod,idx)->psymbol) );
}

void PLR_delCfg(PLR_Cfg Cfg)
/* removes grammar definition 'Cfg' */
{
  BUG_NULL(Cfg);
  FreeMem(PLR_C_IMP(Cfg)->language);
  OT_DEL_T(PLR_C_IMP(Cfg)->Token);
  OT_DEL_T(PLR_C_IMP(Cfg)->TkIdx);
  OT_DEL_T(PLR_C_IMP(Cfg)->NonTerm);
  OT_DEL_T(PLR_C_IMP(Cfg)->NtIdx);
  OT_DEL_T(PLR_C_IMP(Cfg)->StartNt);
  OT_DEL_T(PLR_C_IMP(Cfg)->TokKind);
  OT_DEL_T(PLR_C_IMP(Cfg)->ErrorNt);
  OT_DEL_T(PLR_C_IMP(Cfg)->Prod);
  FreeMem(Cfg);
}

/*I--------------------- Parse table creation ------------------------------- */

static PLR_Tab PLR_createTab_aux
               (
                 PLR_Cfg Cfg, 
                 void (*prExtMsg)(c_string msg), bool verbose, bool diagnose
               )
{ PLR_Tab  PTab = (PLR_Tab)NULL;
  PrsGen_T PrsGen;
  char     buf[STD_BUFFLEN+1];
  void (*prMsg)(c_string msg) = prExtMsg;
  if( prMsg == (void (*)(c_string msg))NULL ) prMsg = prMsg_stderr;

  BUG_NULL(Cfg);
  PrsGen.prMsg       = prExtMsg;
  PrsGen.profile     = verbose;
  PrsGen.conflictCnt = 0;
  if( PrsGen.profile ) (*prMsg)("begin parse table creation ...\n");
  if( PrsGen.profile ) (*prMsg)("reading grammar information ...\n");
  setKfgGlobals(&PrsGen,Cfg);
  fillProdTabs(&PrsGen,Cfg);
  if( PrsGen.profile ) (*prMsg)("creating element keys ...\n");
  fillKernTab(&PrsGen);
  if( PrsGen.profile ) (*prMsg)("creating lambda set ...\n");
  fillLambdaSet(&PrsGen);
  if( PrsGen.profile ) (*prMsg)("creating nonterminal relation ...\n");
  fillNtRelSet(&PrsGen);
  if( PrsGen.profile ) (*prMsg)("creating first sets ...\n");
  fillFirstSets(&PrsGen);
  if( PrsGen.profile ) (*prMsg)("creating states ...\n");
  fillStateTab(&PrsGen);
  if( PrsGen.profile ) (*prMsg)("creating parse tables ...\n");
  PTab = fillParseTab(&PrsGen);
  if( diagnose )
  {
    (*prMsg)("printing statistics ...\n");
    printFirstNtSets(&PrsGen);
    printStateTab(&PrsGen);
    printNtClasses(&PrsGen);
  }
  else countConflicts(&PrsGen);
  if( PrsGen.conflictCnt )
  {
    sprintf(buf,"%d conflicts. Use -diagnose !\n",PrsGen.conflictCnt);
    (*prMsg)(buf);
  }
  if( PrsGen.profile ) (*prMsg)("deleting ...\n");
  delCreateGlobals(&PrsGen);
  if( PrsGen.profile ) (*prMsg)("end parse table creation ...\n");

  return( PTab );
}

PLR_Tab PLR_createTab(PLR_Cfg Cfg, bool verbose, bool diagnose)
/* creates the corresponding parse table for definition 'Cfg'
   'verbose'  --> entertainment
   'diagnose' --> print conflict / result informations
*/
{ 
  return PLR_createTab_aux(Cfg,(void (*)(c_string msg))NULL,verbose,diagnose);
}

PLR_Tab PLR_createTab_ex
        (
          PLR_Cfg Cfg, void (*prMsg)(c_string msg), bool verbose, bool diagnose
        )
/* like PLR_createTab; 
   uses 'prMsg' as print function
*/
{ 
  return PLR_createTab_aux(Cfg,prMsg,verbose,diagnose);
}
