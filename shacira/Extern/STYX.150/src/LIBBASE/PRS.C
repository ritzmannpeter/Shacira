/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [prs.c]                      LALR(1) Parser                              */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "prs_io.h" /* to complete the interface */

#include "prs_imp.h"
#include "otab.h"

/*!
   <p>This module [prs] does the actual - low level - parsing based on a given 
   STYX-konform parse table definition. ( see <a href="prs_gen.htm">[prs_gen]</a> )
   <p>The parser is reentrant and allows multiple parse operations at a time. 
   <p>A second facility refers to its flexible configuration which for example
      allows the use of another scanner than provided by the STYX system.
   <br>
   <p>Within the STYX system the parse interface will only be used by the higher 
   level parse and term construction module <a href="ptm_gen.htm">[ptm_gen]</a>.
   <br>
   <p>Beside that the module offers access to the parse table definition.
   <br>
   <p>The parser handles syntax errors as described below:
   <p>On activated early reduction mode and in the case none of the nonterminals
      are specified as resumption points the parse process will stop.
   <p>Otherwise a variant of the panic-mode error recovery method which only tracks 
      the specified nonterminals will be applied.
   <br>
*/

/* ========================= Types & Constants ============================== */

/*I------------------------------ Types ------------------------------------- */

AbstractType(PLR_Pdf); /* Abstract parser type */

typedef struct _PARSER {
/* Parser */
  StdCPtr   extCfg;                                     /* ext. Configuration */
  PARSETAB* Tab;                                        /* Parse Table        */
  int       (*get)(PLR_Pdf Pdf);                        /* next Token         */
  string    (*curSy)(PLR_Pdf Pdf);                      /* current Token Name */
  StdCPtr   (*redVal)(PLR_Pdf Pdf,int symcnt,int prodId,bool accept); 
                                                        /* Reduce             */
  StdCPtr   (*shiftVal)(PLR_Pdf Pdf, int symbol);       /* Shift              */
  void      (*error)(PLR_Pdf Pdf);                      /* Error              */
  void      (*debug)(PLR_Pdf Pdf,StdCPtr val);          /* Print Stack Value  */
  int       startidx;                                   /* Startsymbol Index  */
  OT_Tab    StackS;                                     /* State Stack        */
  OT_Tab    StackV;                                     /* Value Stack        */
  /* early reduction */
  int       curtok;                                     /* current Token      */
  c_bool    fsttok;                                     /* first Token        */
  c_bool    nxttok;                                     /* next Token         */
  /* Panic Mode Error Handling ( Terminal Arrays )              */
  /* Skip: T --> { 1 .. OT_CNT(StackS) } X NT  U  { undefined } */ 
  long*     skip_tk;                                    /* Skip TK Array      */
  OT_Tab    skip_state;                                 /* Skip State Array   */
  OT_Tab    skip_nt;                                    /* Skip NT Array      */
} PARSER;

/* ---------------------------- Constants ----------------------------------- */

#define PLR_P_IMP(Pdf)    ( (PARSER*)(Pdf) )

/* synchron to prs_gen.c ... */

#define PLR_TERMCNT       ( Pdf->Tab->Kfg->TkCnt + Pdf->Tab->Kfg->StartCnt )
#define PLR_NONTERMCNT    ( Pdf->Tab->Kfg->NtCnt + Pdf->Tab->Kfg->StartCnt )
#define PLR_SYMCNT        ( Pdf->Tab->Kfg->TkCnt + Pdf->Tab->Kfg->NtCnt )
#define PLR_PRODCNT       ( Pdf->Tab->ProdCnt )
#define PLR_STATECNT      ( Pdf->Tab->tabs.MstShiftCnt )
#define PLR_NTIDX(nt)     ( ( nt ) - Pdf->Tab->Kfg->TkCnt )
#define PLR_ACCEPTTK      ( Pdf->Tab->Kfg->TkCnt + Pdf->startidx )    
#define PLR_PRSYMCNT(p)   ( Pdf->Tab->Prod[p].symcnt )
#define PLR_PRNONTERM(p)  ( Pdf->Tab->Prod[p].id )
#define PLR_MSHIFTCNT     ( Pdf->Tab->tabs.MstShiftCnt )
#define PLR_MSHIFT        ( Pdf->Tab->tabs.MstShift )
#define PLR_DSHIFTCNT     ( Pdf->Tab->tabs.DtlShiftCnt )
#define PLR_DSHIFT        ( Pdf->Tab->tabs.DtlShift )
#define PLR_GOTOCNT       ( Pdf->Tab->tabs.GoToCnt )
#define PLR_GOTO          ( Pdf->Tab->tabs.GoTo )
#define PLR_GOTODCNT      ( Pdf->Tab->tabs.GoToDftCnt )
#define PLR_GOTOD         ( Pdf->Tab->tabs.GoToDft )
#define PLR_ACTDCNT       ( Pdf->Tab->tabs.ActDftCnt )
#define PLR_ACTD          ( Pdf->Tab->tabs.ActDft )
#define PLR_ACTECNT       ( Pdf->Tab->tabs.ActExpCnt )
#define PLR_ACTE          ( Pdf->Tab->tabs.ActExp )

#define PLR_SHIFT_ERROR   -1
#define PLR_SHIFT_NONE    -2
#define PLR_GOTO_ERROR    -1
#define PLR_ACT_ERROR     ( PLR_PRODCNT + 1 )
#define PLR_ACT_ACCEPT    ( PLR_PRODCNT + 2 )
#define PLR_PROD_OFFSET   ( PLR_PRODCNT + PLR_TERMCNT )

#define BUG_PLR_INIT(l,r) BUG_VEQU((l),(r))
#define BUG_PLR_SYMBOL(s) BUG_RNG0(s,PLR_T_IMP(PTab)->Kfg->TkCnt + \
                                     PLR_T_IMP(PTab)->Kfg->NtCnt + \
                                     PLR_T_IMP(PTab)->Kfg->StartCnt)
#define BUG_PLR_START(s)  BUG_RNG0(s,PLR_T_IMP(PTab)->Kfg->StartCnt)
#define BUG_PLR_NTM(n)    BUG_RNG0(n,PLR_T_IMP(PTab)->Kfg->NtCnt)
#define BUG_PLR_PROD(p)   BUG_RNG0(p,PLR_T_IMP(PTab)->ProdCnt)
#define BUG_PLR_PSYM(p,s) BUG_RNG0(s,PLR_T_IMP(PTab)->Prod[p].symcnt)

/* .... synchron to prs_gen.c */

#define TOPS(s)           OT_TOP(int,s)
#define TOPV(s)           OT_TOP(StdCPtr,s)

#define PLR_SKIP_ERRMSG   3

/* ========================= Parsing Process ================================ */

/* KEINE Ueberpruefung ... */

static int startIdx(PARSER* Pdf, string StartSymbol)
/* index of 'StartSymbol' */
{ int startidx = -1, idx, i;

  for( i=0; i < PLR_T_IMP(Pdf->Tab)->Kfg->StartCnt; ++i )
  {
    idx = PLR_T_IMP(Pdf->Tab)->Kfg->StartIds[i];
    if( ! strcmp(PLR_T_IMP(Pdf->Tab)->Kfg->SNames[idx],StartSymbol) )
    {
      startidx = i; break;
    }
  }
  bug1( startidx > -1, "'%s' must be a valid start nonterminal", StartSymbol );
  return( startidx );
}

static int acceptToken(PARSER* Pdf, string StartSymbol)
/* AcceptToken ID belonging to 'StartSymbol' */
{
  return Pdf->Tab->Kfg->TkCnt + startIdx(Pdf,StartSymbol);    
}

static int initParsing(PARSER* Pdf, string StartSymbol)
/* initializes parsing process, first state */
{ int startidx = startIdx(Pdf,StartSymbol);

  if( Pdf->startidx == -1 )
  {
    OT_NEWSTK(Pdf->StackS);
    OT_NEWSTK(Pdf->StackV);
    OT_PUSH((Pdf->startidx = startidx),Pdf->StackS);
  }
  else BUG_PLR_INIT(Pdf->startidx,startidx);
  return( TOPS(Pdf->StackS) );
}

static void quitParsing(PARSER* Pdf)
/* quits parsing process */
{
  OT_DELSTK(Pdf->StackS);
  OT_DELSTK(Pdf->StackV);
  Pdf->StackS   = (OT_Tab)NULL;
  Pdf->StackV   = (OT_Tab)NULL;
  Pdf->startidx = -1;
}

static void popStates(PARSER* Pdf, int cnt)
/* delete 'cnt' states from stack */
{ int i;

  for( i=0; i < cnt; ++i ) OT_POP(Pdf->StackS);
}

static void printState(StdCPtr state)
{
  fprintf(STDOUT,"%d",(int)state);
}

#define PRINT_STATES(s) OT_PRINT(s,printState,1,1)

static void printConfig(PARSER* Pdf, int cState, string cTok, int TokId)
/* debug parse state */
{ long i;

  fprintf(STDOUT,"State %d, Token %s ( %d )",cState,cTok,TokId); NL;
  PRINT_STATES(Pdf->StackS); NL;
  fprintf(STDOUT,"Values :"); NL;
  for( i=0; i < OT_CNT(Pdf->StackV); ++i )
  {
    NL; fprintf(STDOUT,"%ld :",i); NL;
    (*Pdf->debug)(Pdf,OT_GET(StdCPtr,Pdf->StackV,i));
  }
  fprintf(STDOUT,"!"); NL;
}

static int parseSAct(PARSER* Pdf, int cState, int cTok)
/* shift */
{ int i, j;

  if( cTok >= 0 && cTok < Pdf->Tab->Kfg->TkCnt && 
      CFG_COM(Pdf->Tab->Kfg->TokKind[cTok])     ) return( PLR_SHIFT_NONE );
  if( PLR_MSHIFT[cState] == PLR_SHIFT_ERROR )     return( PLR_SHIFT_ERROR );
  for( i = PLR_MSHIFT[cState], j = i-1; 
       PLR_DSHIFT[i] >= 0 && i < PLR_DSHIFTCNT; ++i, --j )
    if( PLR_DSHIFT[i] == cTok ) return( ABS(PLR_DSHIFT[j]) - 1 );
  return( PLR_SHIFT_ERROR );
}

static int parseRAct(PARSER* Pdf, int cState, int cTok)
/* reduce */
{ int entry = PLR_ACTD[cState];

  if( entry >= 1 ) return( entry );
  else
  { int i       = ABS(entry), 
        e_first = PLR_ACTE[i], 
        act     = PLR_ACT_ERROR, e_entry;

    for( ; EQSIGN(e_first,PLR_ACTE[i]) && i < PLR_ACTECNT; ++i )
    {
      if( ( e_entry = ABS(PLR_ACTE[i]) ) > PLR_PROD_OFFSET )
        act = e_entry - PLR_PROD_OFFSET;
      else
      {
        if( e_entry - 1 == cTok ) return( act );
      }  
    }
    return( PLR_ACT_ERROR );
  }
}

static int parseGoTo(PARSER* Pdf, int pId)
/* goto during parsing */
{ int lastidx = ( pId < PLR_GOTOCNT - 1 ) ? PLR_GOTO[pId+1] : PLR_GOTODCNT,
      cState  = TOPS(Pdf->StackS), 
      state   = PLR_GOTO_ERROR, entry, i;

  for( i = PLR_GOTO[pId]; i < lastidx; ++i )
  {
    if( ( entry = PLR_GOTOD[i] ) > PLR_STATECNT )
      state = entry - PLR_STATECNT - 1;
    else
    {
      /* entry = 0 shouldn't occur ( unreacheable NT ) */
      if( entry <= 0 || entry - 1 == cState ) return( state );
    }  
  }
  return( PLR_GOTO_ERROR );
}

static int panicGoTo(PARSER* Pdf, int cState, int pId)
/* goto during panic mode error handling */
{ int lastidx = ( pId < PLR_GOTOCNT - 1 ) ? PLR_GOTO[pId+1] : PLR_GOTODCNT,
      state   = PLR_GOTO_ERROR, entry, i;

  for( i = PLR_GOTO[pId]; i < lastidx; ++i )
  {
    if( ( entry = PLR_GOTOD[i] ) > PLR_STATECNT )
      state = entry - PLR_STATECNT - 1;
    else
    {
      if( ABS(entry) - 1 == cState ) return( state );
    }  
  }
  return( PLR_GOTO_ERROR );
}

static bool praeReduction(PARSER* Pdf, int* cState)
/* while '*cState' has no follow states with a terminal symbol and exact    */
/* one reduction possibility the reduction and goto operation will be done. */
/* Result: False ( continue parsing ) / True ( accept )                     */
{ StdCPtr val; int res, prod;

  while( PLR_MSHIFT[*cState] == PLR_SHIFT_ERROR && 
         ( res = PLR_ACTD[*cState] ) >= 1       &&
         res != PLR_ACT_ERROR                    )
  {
    if( res <= PLR_PRODCNT )
    {
      val     = (*Pdf->redVal)(Pdf,PLR_PRSYMCNT(res-1),res-1,False);
      popStates(Pdf,PLR_PRSYMCNT(res-1));
      *cState = parseGoTo(Pdf,PLR_NTIDX(PLR_PRNONTERM(res-1)));
      BUG_VNEQ(*cState,PLR_GOTO_ERROR);
      OT_PUSH(*cState,Pdf->StackS); OT_PUSH(val,Pdf->StackV);
    }
    else
    {
      prod = PLR_PRODCNT - Pdf->Tab->Kfg->StartCnt + Pdf->startidx;
      (*Pdf->redVal)(Pdf,PLR_PRSYMCNT(prod),prod,True);
      quitParsing(Pdf); return( True );
    }
  }
  return( False );
}

/* --- PanicMode Error Handling: Skip Tables --- */

/*D
  PanicMode Error Handling

  Skip Tables:
  - skip_tk[TkCnt] 
      contains the start index of (state,nt)-tuples or -1 ( undefined ) 
      for each token
  - skip_nt, skip_state 
      contains the corresponding (state,nt)-tuples for all tokens
  - forall token t
      forall tuples (state,nt):
        nt = error nt &&
        ( s^ = GoTo[stack(state),nt] ) != error && ShiftAction[s^,t] != error 
*/

static void quitSkipTables(PARSER* Pdf)
/* quits skip tables */
{ 
  FreeMem(Pdf->skip_tk);
  OT_DEL_T(Pdf->skip_nt);
  OT_DEL_T(Pdf->skip_state);
}

static bool initSkipTables(PARSER* Pdf)
/* initializes skip tables */
{ long cnt  = PLR_TERMCNT, scnt = OT_CNT(Pdf->StackS),
       ncnt = PLR_NONTERMCNT, i, j, k;
  Pdf->skip_tk    = (long*)NewMem(sizeof(long)*cnt);
  Pdf->skip_nt    = OT_CREATE_ADT(int);
  Pdf->skip_state = OT_CREATE_ADT(int);
  for( i=0; i < cnt; ++i ) Pdf->skip_tk[i] = -1L;
  for( i=scnt-1; i >= 0; --i )
    for( j=0; j < ncnt; ++j ) 
      if( PLR_T_IMP(Pdf->Tab)->Kfg->ErrorNt[(int)j] )
      { int s = panicGoTo(Pdf,OT_GET(int,Pdf->StackS,i),(int)j);
        if( s != PLR_GOTO_ERROR )
          for( k=0; k < cnt; ++k )
          { int p1 = parseSAct(Pdf,s,(int)k);
            if( p1 != PLR_SHIFT_ERROR && p1 != PLR_SHIFT_NONE &&
                Pdf->skip_tk[k] == -1L )
            { long idx = OT_T_INS(Pdf->skip_nt,j);
              OT_T_INS(Pdf->skip_state,i);
              Pdf->skip_tk[k] = idx;
            }
          }
      }
  if( OT_CNT(Pdf->skip_state) > 0 )
    return True;
  else
  {
    quitSkipTables(Pdf);
    return False;
  }
}

/*I============================ Parse interface ============================= */

/* weitgehend OHNE Ueberpruefung ... */

/*I---------------------------- Configuration ------------------------------- */

PLR_Pdf PLR_createPdf(PLR_Tab PTab, StdCPtr extCfg)
/* creates a parser for table 'PTab' and external configuration 'extCfg' */
{ PARSER* Parser;

  BUG_NULL(PTab); //optional! BUG_NULL(extCfg);
  Parser           = (PARSER*)NewMem(sizeof(PARSER));
  Parser->Tab      = (PARSETAB*)PTab;
  Parser->extCfg   = extCfg;
  Parser->startidx = -1;
  Parser->curtok   = -1;
  Parser->fsttok   = C_True;
  Parser->nxttok   = C_True;
  Parser->StackS   = (OT_Tab)NULL;
  Parser->StackV   = (OT_Tab)NULL;
  return( Parser );
}

void PLR_addGetF(PLR_Pdf Parser, int (*getToken)(PLR_Pdf Parser))
/* adds next token function 'getToken' to 'Parser' */
{
  BUG_NULL(Parser); BUG_NULL(getToken);
  PLR_P_IMP(Parser)->get = getToken;
}

void PLR_addCurSyF(PLR_Pdf Parser, string (*getCurSy)(PLR_Pdf Parser))
/* adds current token name debug function 'getCurSy' to 'Parser' */
{
  BUG_NULL(Parser); BUG_NULL(getCurSy);
  PLR_P_IMP(Parser)->curSy = getCurSy;
}

void PLR_addRedF
     (
       PLR_Pdf Parser, 
       StdCPtr (*redVal)(PLR_Pdf Parser, int symcnt, int prodId, bool accept)
     )
/* adds reduction function 'redVal' to 'Parser' */
{
  BUG_NULL(Parser); BUG_NULL(redVal);
  PLR_P_IMP(Parser)->redVal = redVal;
}

void PLR_addSftF
     (
       PLR_Pdf Parser, StdCPtr (*shiftVal)(PLR_Pdf Parser, int symbol)
     )
/* adds shift function 'shiftVal' to 'Parser' */
{
  BUG_NULL(Parser); BUG_NULL(shiftVal);
  PLR_P_IMP(Parser)->shiftVal = shiftVal;
}

void PLR_addErrF(PLR_Pdf Parser, void (*error)(PLR_Pdf Parser))
/* adds error function 'error' to 'Parser' */
{
  BUG_NULL(Parser); BUG_NULL(error);
  PLR_P_IMP(Parser)->error = error;
}

void PLR_addDbgF(PLR_Pdf Parser, void (*debug)(PLR_Pdf Parser, StdCPtr val))
/* adds debug function 'debug' to 'Parser' */
{
  BUG_NULL(Parser); BUG_NULL(debug);
  PLR_P_IMP(Parser)->debug = debug;
}

void PLR_delPdf(PLR_Pdf Parser)
/* removes 'Parser' */
{
  BUG_NULL(Parser);
  FreeMem(Parser);
}

StdCPtr PLR_CfgExt(PLR_Pdf Parser)
#define PLR_CFGEXT(type,pdf) ((type)PLR_CfgExt(pdf))
/* external configuration of 'Parser' */
{
  BUG_NULL(Parser);
  return( PLR_P_IMP(Parser)->extCfg );
}

PLR_Tab PLR_CfgTab(PLR_Pdf Parser)
/* parse table of 'Parser' */
{
  BUG_NULL(Parser);
  return( PLR_P_IMP(Parser)->Tab );
}

/*I---------------------- Parsing ------------------------------------------- */

bool PLR_parse(PLR_Pdf Parser, string StartSymbol, bool interprete)
/* does the parsing for start nonterminal 'StartSymbol' 
   interprete --> early reduction
*/
{ PARSER* Pdf = PLR_P_IMP(Parser); StdCPtr val; 
  int cTok, cState, ret, errcnt=0, tokcnt=0; 
  bool doParse = True, retval = True;
  BUG_NULL(Pdf);
  if( interprete && Pdf->nxttok == C_False )
  {
    cTok = Pdf->curtok; 
  }
  else 
  {
    Pdf->curtok = cTok = (*Pdf->get)(Pdf); 
  }
  ++tokcnt;
  if( interprete && Pdf->fsttok == C_False && Pdf->curtok == -1 )
  {
    return( retval );
  }
  cState = initParsing(Pdf,StartSymbol); 
  while( doParse == True )
  {
    if( cTok == -1 ) cTok = PLR_ACCEPTTK;
//printConfig(Pdf,cState,(*Pdf->curSy)(Pdf),cTok); 
    if( ( ret = parseSAct(Pdf,cState,cTok) ) != PLR_SHIFT_ERROR )
    {
      val = (*Pdf->shiftVal)(Pdf,cTok);
      if( ret != PLR_SHIFT_NONE )
      {
        cState = ret; OT_PUSH(cState,Pdf->StackS); OT_PUSH(val,Pdf->StackV); 
        if( interprete && praeReduction(Pdf,&cState) ) 
        {
          Pdf->fsttok = C_False; 
          Pdf->nxttok = C_True; 
          return( retval );
        }
      }
      Pdf->curtok = cTok = (*Pdf->get)(Pdf); ++tokcnt;
    }
    else
    {
      ret = parseRAct(Pdf,cState,cTok);
      if( ret <= PLR_PRODCNT )
      {
        val    = (*Pdf->redVal)(Pdf,PLR_PRSYMCNT(ret-1),ret-1,False);
        popStates(Pdf,PLR_PRSYMCNT(ret-1));
        cState = parseGoTo(Pdf,PLR_NTIDX(PLR_PRNONTERM(ret-1)));
        BUG_VNEQ(cState,PLR_GOTO_ERROR);
        OT_PUSH(cState,Pdf->StackS); OT_PUSH(val,Pdf->StackV);
        if( interprete && praeReduction(Pdf,&cState) ) 
        {
          Pdf->fsttok = C_False; 
          Pdf->nxttok = C_False; 
          return( retval );
        }
      }
      else
      {
        if( ret == PLR_ACT_ACCEPT && cTok == PLR_ACCEPTTK )
        {
          ret = PLR_PRODCNT - Pdf->Tab->Kfg->StartCnt + Pdf->startidx;
          if( retval == True || PLR_PRSYMCNT(ret) == OT_CNT(Pdf->StackV) )
          {
            (*Pdf->redVal)(Pdf,PLR_PRSYMCNT(ret),ret,True);
          }
          else
          {
/*XXX
fprintf(STDERR,"STK-CNT=%ld,SYM-CNT=%ld\n",OT_CNT(Pdf->StackV),PLR_PRSYMCNT(ret));
 {long i;
  for(i=0; i<OT_CNT(Pdf->StackV); ++i)
  {
    fprintf(STDERR,"SYM=%s\n",
      symbolToString(PT_symbol(OT_GET(symbol,Pdf->StackV,i))));
    if( PT_isNonTerm(OT_GET(symbol,Pdf->StackV,i)) )
      fprintf(STDERR,"PRD=%s\n\n",
        symbolToString(PT_product(OT_GET(symbol,Pdf->StackV,i))));
  }
 }
*/
            ret = -(ret+1);
            (*Pdf->redVal)(Pdf,OT_CNT(Pdf->StackV),ret,True);
          }
          quitParsing(Pdf); 
          Pdf->fsttok = C_False; 
          Pdf->nxttok = C_False; 
          return( retval );
        }
        else
/*ALT
        {
// printConfig(Pdf,cState,(*Pdf->curSy)(Pdf),cTok);
          (*Pdf->error)(Pdf); 
          ret = -( PLR_PRODCNT - Pdf->Tab->Kfg->StartCnt + Pdf->startidx + 1 );
          (*Pdf->redVal)(Pdf,OT_CNT(Pdf->StackV),ret,True);
          quitParsing(Pdf); return( retval = False );
        }
*/
/*NEU*/
        { int p, s, n;
// printConfig(Pdf,cState,(*Pdf->curSy)(Pdf),cTok);
          retval = False;
          if( tokcnt >= errcnt )
          {
            (*Pdf->error)(Pdf); errcnt = tokcnt + PLR_SKIP_ERRMSG;
          }
          if( !interprete && initSkipTables(Pdf) )
          {
            assert0(cTok != -1,"");
            while( cTok != PLR_ACCEPTTK && ( cTok < 0 || Pdf->skip_tk[cTok] == -1L ) )
            {
              val = (*Pdf->shiftVal)(Pdf,cTok);
              if( cTok < 0 || ! CFG_COM(Pdf->Tab->Kfg->TokKind[cTok]) )
                OT_PUSH(val,Pdf->StackV);
              cTok = (*Pdf->get)(Pdf); 
              if( cTok == -1 ) cTok = PLR_ACCEPTTK;
            }
            if( cTok != PLR_ACCEPTTK )
            {
              s = OT_GET(int,Pdf->skip_state,Pdf->skip_tk[cTok]);
              n = OT_GET(int,Pdf->skip_nt,Pdf->skip_tk[cTok]);
            }
            quitSkipTables(Pdf);
          }
          else cTok = PLR_ACCEPTTK; // quit parsing on first error
          if( cTok != PLR_ACCEPTTK )
          {
            p   = -(Pdf->Tab->Kfg->TkCnt+n+1);
            val = (*Pdf->redVal)(Pdf,OT_CNT(Pdf->StackV)-(s+1),p,False);
            popStates(Pdf,(int)(OT_CNT(Pdf->StackS)-(s+1)));
            cState = parseGoTo(Pdf,n);
            BUG_VNEQ(cState,PLR_GOTO_ERROR);
            OT_PUSH(cState,Pdf->StackS); OT_PUSH(val,Pdf->StackV);
            assert0( OT_CNT(Pdf->StackS) == OT_CNT(Pdf->StackV),"");
          }
          else
          {
            p = -(PLR_PRODCNT-Pdf->Tab->Kfg->StartCnt+Pdf->startidx+1);
            (*Pdf->redVal)(Pdf,OT_CNT(Pdf->StackV),p,True);
            quitParsing(Pdf); return( retval );
          }
        }
/**/
      }
    }
  }
  BUG; return( False );
}

StdCPtr PLR_topVal(PLR_Pdf Parser)
/* pops and returns the top stack value of 'Parser' */
{ PARSER* Pdf = PLR_P_IMP(Parser); StdCPtr val; 

  BUG_NULL(Pdf);
  val = TOPV(Pdf->StackV); OT_POP(Pdf->StackV);
  return( val );
}

/*I========================= Parse table interface ========================== */

/* weitgehend OHNE Ueberpruefung ... */

/*I--------------------------- Copy & Delete -------------------------------- */

PLR_Tab PLR_copyTab(PLR_Tab PTab)
/* copies parse table 'PTab' */
{ PARSETAB* tab; int symcnt = 0, i;

  BUG_NULL(PTab);
  tab = (PARSETAB*)NewMem(sizeof(PARSETAB));

  /* Kopfdaten */
  tab->Kfg               = (KFGHEAD*)NewMem(sizeof(KFGHEAD));
  tab->Kfg->language     = StrCopy(PLR_T_IMP(PTab)->Kfg->language);
  symcnt += ( tab->Kfg->TkCnt = PLR_T_IMP(PTab)->Kfg->TkCnt );
  symcnt += ( tab->Kfg->NtCnt = PLR_T_IMP(PTab)->Kfg->NtCnt );
  tab->Kfg->SNames       = 
    (string*)NewMem(sizeof(string)*(tab->Kfg->TkCnt+tab->Kfg->NtCnt));
  for( i=0; i < tab->Kfg->TkCnt+tab->Kfg->NtCnt; ++i )
    tab->Kfg->SNames[i]  = StrCopy(PLR_T_IMP(PTab)->Kfg->SNames[i]);
  symcnt += ( tab->Kfg->StartCnt = PLR_T_IMP(PTab)->Kfg->StartCnt );
  tab->Kfg->StartIds     = (int*)
    BytCopy(PLR_T_IMP(PTab)->Kfg->StartIds,sizeof(int)*tab->Kfg->StartCnt);
  if( tab->Kfg->TkCnt )
    tab->Kfg->TokKind    = (int*)
      BytCopy(PLR_T_IMP(PTab)->Kfg->TokKind,sizeof(int)*tab->Kfg->TkCnt);
  else tab->Kfg->TokKind = (int*)NULL;
  tab->Kfg->NtClass      = (int*)
    BytCopy(PLR_T_IMP(PTab)->Kfg->NtClass,sizeof(int)*(tab->Kfg->NtCnt));
  tab->Kfg->ErrorNt      = (bool*)
    BytCopy(PLR_T_IMP(PTab)->Kfg->ErrorNt,sizeof(bool)*(tab->Kfg->NtCnt));

  /* Produktionen */
  tab->ProdCnt = PLR_T_IMP(PTab)->ProdCnt;
  tab->Prod    = (KFGPROD*)NewMem(sizeof(KFGPROD)*tab->ProdCnt);
  for( i=0; i < tab->ProdCnt; ++i )
  {
    tab->Prod[i].pname        = StrCopy(PLR_T_IMP(PTab)->Prod[i].pname);
    tab->Prod[i].method       = PLR_T_IMP(PTab)->Prod[i].method;
    tab->Prod[i].id           = PLR_T_IMP(PTab)->Prod[i].id;
    tab->Prod[i].symcnt       = PLR_T_IMP(PTab)->Prod[i].symcnt;
    if( tab->Prod[i].symcnt )
    {
      tab->Prod[i].symbols    = (int*)
        BytCopy
        (
          PLR_T_IMP(PTab)->Prod[i].symbols,sizeof(int)*tab->Prod[i].symcnt
        );
      tab->Prod[i].symfrms    = (int*)
        BytCopy
        (
          PLR_T_IMP(PTab)->Prod[i].symfrms,sizeof(int)*tab->Prod[i].symcnt
        );
    }
    else tab->Prod[i].symbols = tab->Prod[i].symfrms = (int*)NULL;
  }

  /* Parse-Tabellen */
  tab->tabs.MstShiftCnt   = PLR_T_IMP(PTab)->tabs.MstShiftCnt;
  tab->tabs.MstShift      = (int*)
    BytCopy(PLR_T_IMP(PTab)->tabs.MstShift,sizeof(int)*tab->tabs.MstShiftCnt);
  tab->tabs.DtlShiftCnt   = PLR_T_IMP(PTab)->tabs.DtlShiftCnt;
  if( tab->tabs.DtlShiftCnt )
    tab->tabs.DtlShift    = (int*)
      BytCopy(PLR_T_IMP(PTab)->tabs.DtlShift,sizeof(int)*tab->tabs.DtlShiftCnt);
  else tab->tabs.DtlShift = (int*)NULL;
  tab->tabs.GoToCnt       = PLR_T_IMP(PTab)->tabs.GoToCnt;
  tab->tabs.GoTo          = (int*)
    BytCopy(PLR_T_IMP(PTab)->tabs.GoTo,sizeof(int)*tab->tabs.GoToCnt);
  tab->tabs.GoToDftCnt    = PLR_T_IMP(PTab)->tabs.GoToDftCnt;
  tab->tabs.GoToDft       = (int*)
    BytCopy(PLR_T_IMP(PTab)->tabs.GoToDft,sizeof(int)*tab->tabs.GoToDftCnt);
  tab->tabs.ActDftCnt     = PLR_T_IMP(PTab)->tabs.ActDftCnt;
  tab->tabs.ActDft        = (int*)
    BytCopy(PLR_T_IMP(PTab)->tabs.ActDft,sizeof(int)*tab->tabs.ActDftCnt);
  tab->tabs.ActExpCnt     = PLR_T_IMP(PTab)->tabs.ActExpCnt;
  if( tab->tabs.ActExpCnt )
    tab->tabs.ActExp      = (int*)
      BytCopy(PLR_T_IMP(PTab)->tabs.ActExp,sizeof(int)*tab->tabs.ActExpCnt);
  else tab->tabs.ActExp   = (int*)NULL;

  return( tab );
}

void PLR_delTab(PLR_Tab PTab)
/* removes parse table 'PTab' */
{ int symcnt, i;

  BUG_NULL(PTab);
  FreeMem(PLR_T_IMP(PTab)->Kfg->language);
  symcnt = PLR_T_IMP(PTab)->Kfg->TkCnt + PLR_T_IMP(PTab)->Kfg->NtCnt;
  for( i=0; i < symcnt; ++i ) 
    FreeMem(PLR_T_IMP(PTab)->Kfg->SNames[i]);
  FreeMem(PLR_T_IMP(PTab)->Kfg->SNames);
  FreeMem(PLR_T_IMP(PTab)->Kfg->StartIds);
  if( PLR_T_IMP(PTab)->Kfg->TkCnt )
    FreeMem(PLR_T_IMP(PTab)->Kfg->TokKind);
  FreeMem(PLR_T_IMP(PTab)->Kfg->NtClass);
  FreeMem(PLR_T_IMP(PTab)->Kfg->ErrorNt);
  FreeMem(PLR_T_IMP(PTab)->Kfg);
  for( i=0; i < PLR_T_IMP(PTab)->ProdCnt; ++i )
  {
    if( PLR_T_IMP(PTab)->Prod[i].symcnt )
    {
      FreeMem(PLR_T_IMP(PTab)->Prod[i].symbols);
      FreeMem(PLR_T_IMP(PTab)->Prod[i].symfrms);
    }
    FreeMem(PLR_T_IMP(PTab)->Prod[i].pname);
  }
  FreeMem(PLR_T_IMP(PTab)->Prod);
  FreeMem(PLR_T_IMP(PTab)->tabs.MstShift);
  if( PLR_T_IMP(PTab)->tabs.DtlShiftCnt )
    FreeMem(PLR_T_IMP(PTab)->tabs.DtlShift);
  FreeMem(PLR_T_IMP(PTab)->tabs.GoTo);
  FreeMem(PLR_T_IMP(PTab)->tabs.GoToDft);
  FreeMem(PLR_T_IMP(PTab)->tabs.ActDft);
  if( PLR_T_IMP(PTab)->tabs.ActExpCnt )
    FreeMem(PLR_T_IMP(PTab)->tabs.ActExp);
  FreeMem(PTab);
}

/*I--------------------------- Accessing ------------------------------------ */

string PLR_language(PLR_Tab PTab)
/* language name of parse table 'PTab' */
{
  BUG_NULL(PTab);
  return( PLR_T_IMP(PTab)->Kfg->language );
}

int PLR_tokenCnt(PLR_Tab PTab)
/* number of tokens of parse table 'PTab' */
{
  BUG_NULL(PTab);
  return( PLR_T_IMP(PTab)->Kfg->TkCnt );
}

int PLR_nontermCnt(PLR_Tab PTab)
/* number of nonterminals of parse table 'PTab' */
{
  BUG_NULL(PTab);
  return( PLR_T_IMP(PTab)->Kfg->NtCnt );
}

int PLR_startCnt(PLR_Tab PTab)
/* number of startsymbols of parse table 'PTab' */
{
  BUG_NULL(PTab);
  return( PLR_T_IMP(PTab)->Kfg->StartCnt );
}

int PLR_symbolCnt(PLR_Tab PTab)
/* number of symbols of parse table 'PTab' */
{
  BUG_NULL(PTab);
  return
  ( 
    PLR_T_IMP(PTab)->Kfg->TkCnt    +
    PLR_T_IMP(PTab)->Kfg->NtCnt    +
    PLR_T_IMP(PTab)->Kfg->StartCnt 
  );
}

/*! 
  <p><b>Nonterminal conversion macros</b>
*/

/*DOC_INTERFACE*/
/* Nonterminal index to symbol */
#define PLR_NTI_TO_NTS(t,i)   (PLR_tokenCnt(t)+(i))
/* Nonterminal symbol to index */
#define PLR_NTS_TO_NTI(t,s)   ((s)-PLR_tokenCnt(t))
/* Nonterminal symbol to class */
#define PLR_NTS_TO_NTC(t,s)   PLR_ntClass((t), \
                                PLR_ntClassId((t),PLR_NTS_TO_NTI(t,s)))

int PLR_startSymbol(PLR_Tab PTab, int startId)
/* startsymbol 'startId' of parse table 'PTab'
   [startId=0..StartCnt-1] --> [0..SymbolCnt-1]
*/
{
  BUG_NULL(PTab);
  BUG_PLR_START(startId);
  return( PLR_T_IMP(PTab)->Kfg->StartIds[startId] );
}

bool PLR_isErrorNt(PLR_Tab PTab, int ntId)
/* whether 'ntId' is an error nonterminal of parse table 'PTab'
   [ntId=0..NtCnt-1] 
*/
{
  BUG_NULL(PTab);
  BUG_PLR_NTM(ntId);
  return( PLR_T_IMP(PTab)->Kfg->ErrorNt[ntId] );
}

int PLR_ntClassId(PLR_Tab PTab, int ntId)
/* class index of nonterminal 'ntId' of parse table 'PTab'
   [ntId=0..NtCnt-1] --> [0..NtCnt-1]
*/
{
  BUG_NULL(PTab);
  BUG_PLR_NTM(ntId);
  return( PLR_T_IMP(PTab)->Kfg->NtClass[ntId] );
}

int PLR_ntClass(PLR_Tab PTab, int ntClsId)
/* class symbol of nonterminal 'ntId' of parse table 'PTab'
   [ntClsId=0..NtCnt-1] --> [0..SymbolCnt-1]
*/
{
  BUG_NULL(PTab);
  BUG_PLR_NTM(ntClsId);
  return
  ( 
    PLR_T_IMP(PTab)->Kfg->TkCnt + PLR_T_IMP(PTab)->Kfg->NtClass[ntClsId] 
  );
}

int PLR_symType(PLR_Tab PTab, int symId)
/* type of symbol 'symId' of parse table 'PTab' [symId=0..SymbolCnt-1] */ 
{
  BUG_NULL(PTab);
  BUG_PLR_SYMBOL(symId);
  if( symId >= PLR_T_IMP(PTab)->Kfg->TkCnt )
    return( PLR_TYP_NTM );
  else
    return( PLR_T_IMP(PTab)->Kfg->TokKind[symId] );
}

string PLR_symName(PLR_Tab PTab, int symId)
/* name of symbol 'symId' of parse table 'PTab' [symId=0..SymbolCnt-1] */ 
{
  BUG_NULL(PTab);
  BUG_PLR_SYMBOL(symId);
  return
  ( 
    ( symId < PLR_T_IMP(PTab)->Kfg->TkCnt + PLR_T_IMP(PTab)->Kfg->NtCnt ) ? 
    PLR_T_IMP(PTab)->Kfg->SNames[symId] : PLR_T_IMP(PTab)->Kfg->language 
  );
}

int PLR_prodCnt(PLR_Tab PTab)
/* number of productions of parse table 'PTab' */
{
  BUG_NULL(PTab);
  return( PLR_T_IMP(PTab)->ProdCnt );
}

int PLR_prodNonTerm(PLR_Tab PTab, int prodId)
/* nonterminal of production 'prodId' of parse table 'PTab'
   [prodId=0..PCnt-1] --> [0..SymbolCnt-1]
*/
{
  BUG_NULL(PTab);
  BUG_PLR_PROD(prodId);
  return( PLR_T_IMP(PTab)->Prod[prodId].id );
}

int PLR_prodMethod(PLR_Tab PTab, int prodId)
/* unused */
{
  BUG_NULL(PTab);
  BUG_PLR_PROD(prodId);
  return( PLR_T_IMP(PTab)->Prod[prodId].method );
}

int PLR_prodSymCnt(PLR_Tab PTab, int prodId)
/* number of members of production 'prodId'
   of parse table 'PTab' [prodId=0..PCnt-1]
*/
{
  BUG_NULL(PTab);
  BUG_PLR_PROD(prodId);
  return( PLR_T_IMP(PTab)->Prod[prodId].symcnt );
}

int PLR_prodSymbol(PLR_Tab PTab, int prodId, int psymId)
/* symbol of production 'prodId' and member 'psymId' 
   of parse table 'PTab'
   [prodId=0..PCnt-1,psymId=0..PSCnt-1] --> [0..SymbolCnt-1]
*/
{
  BUG_NULL(PTab);
  BUG_PLR_PROD(prodId); BUG_PLR_PSYM(prodId,psymId);
  return( PLR_T_IMP(PTab)->Prod[prodId].symbols[psymId] );
}

int PLR_prodSymFrm(PLR_Tab PTab, int prodId, int psymId)
/* layout info for production 'prodId' and member 'psymId' 
   of parse table 'PTab'
   [prodId=0..PCnt-1,psymId=0..PSCnt-1] --> 
   [negative(-->NL)] column position
*/
{
  BUG_NULL(PTab);
  BUG_PLR_PROD(prodId); BUG_PLR_PSYM(prodId,psymId);
  return( PLR_T_IMP(PTab)->Prod[prodId].symfrms[psymId] );
}

string PLR_prodName(PLR_Tab PTab, int prodId)
/* name of production 'prodId' of parse table 'PTab'
   [prodId=0..PCnt-1] 
*/
{
  BUG_NULL(PTab);
  BUG_PLR_PROD(prodId);
  return( PLR_T_IMP(PTab)->Prod[prodId].pname );
}
