/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ptm_gen.c]              Parse Term Construction                         */
/*                          - during parse process -                        */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "symbols.h"
#include "scn_base.h"
#include "scn_abs.h"
#include "prs_dfn.h"
#include "prs_abs.h"
#include "ptm.h"

#include "prs.h"
#include "sink.h"
#include "gstream.h"

/*!!
   The module [ptm_gen] provides a high-level parse interface. It implements 
   the construction of the parse tree / term during the parse process. 
   The scan, parse and term construction functions are reentrant which offers 
   the possibility of multiple concurrent parse operations.
*/

/*I------------------------- Types ------------------------------------------ */

AbstractType(PT_Diag); /* Abstract parse term diagnose type */

typedef struct _PTDIAG {
/* Parse Term Diagnose */
  int  ErrorCnt;                /* number of errors       */
  int  WarningCnt;              /* number of warnings     */
  void (*printMsg)(string msg); /* message print function */
} PTDIAG;

AbstractType(PT_Cfg); /* Abstract parse term configuration type */


typedef struct _PTCFG {
/* Parse Term Configuration */
  Abs_T         PlrCfg;     /* Parser Configuration      */
  Abs_T (*getPTCfg)(Abs_T PlrCfg);
                    /* get term generation configuration */
  Abs_T         cStream;    /* Scanner / Stream          */
  SF_scan       nextTok;    /* CB for Stream_next        */
  SF_tok        tokID;      /* CB for Stream_ctid        */
  SF_symbol     tokSym;     /* CB for Stream_csym        */
  SF_symbol     streamSym;  /* CB for Stream_cfil        */
  SF_pos        tokRow;     /* CB for Stream_clin        */
  SF_pos        tokCol;     /* CB for Stream_ccol        */
  SF_flag       unicode;    /* CB for Stream_unicode     */
  symbol*       CfgSyms;    /* Grammar Symbols           */
  symbol*       PrdSyms;    /* Production Symbols        */
  symbol        ErrSym;     /* error symbol              */
  bool          list;       /* ComTree, Tree are lists ? */
  StdCPtr       ComTree;    /* Comment Tree ( List )     */
  StdCPtr       Tree;       /* Derivation Tree ( List )  */
  int           ErrCnt;     /* Syntax Error Count        */ 
  symbol (*convertTok)(symbol tok, symbol val);
                   /* external token conversion function */
  PT_Term (*convertNtm)(PT_Term Tree);
             /* external nonterminal conversion function */
  void (*printMsg)(string msg);
                      /* external message print function */
} PTCFG;


/* external ( static ) message print function */
static void (*printMsg)(string msg) = (void (*)(string msg))NULL;


/*I------------------------ Parsing & Term Construction -------------------- */

static int PT_get(PLR_Pdf Pdf)
/* next token */
{ PTCFG* Cfg = PLR_CFGEXT(PTCFG*,Pdf);
  (*Cfg->nextTok)(Cfg->cStream);
  return( (*Cfg->tokID)(Cfg->cStream) );
}

static int PT_get_ext(AbsPlr_T pconfig)
/* next token (external scanner and parser) */
{ PTCFG* Cfg = (PTCFG*)AP_getExtCfg(pconfig);
  (*Cfg->nextTok)(Cfg->cStream);
  return( (*Cfg->tokID)(Cfg->cStream) );
}

static string PT_curSy(PLR_Pdf Pdf)
/* current token */
{ PTCFG* Cfg = PLR_CFGEXT(PTCFG*,Pdf);
  return symbolToString((*Cfg->tokSym)(Cfg->cStream));
}

static string PT_curSy_ext(AbsPlr_T pconfig)
/* current token (external scanner and parser) */
{ PTCFG* Cfg = (PTCFG*)AP_getExtCfg(pconfig);
  return symbolToString((*Cfg->tokSym)(Cfg->cStream));
}

// PR 27.01.2003 Solange ich die Fehlerbehandlung nicht blicke
long _ErrorRow = -1;
long _ErrorColumn = -1;
static void PT_synError_aux(PTCFG* Cfg)
{ string msg;
// PR 27.01.2003 Solange ich die Fehlerbehandlung nicht blicke
_ErrorRow = (*Cfg->tokRow)(Cfg->cStream);
_ErrorColumn = (*Cfg->tokCol)(Cfg->cStream);
  msg = Str_printf
        (
          "%s(%d,%d) : syntax error (token '%s')\n",
          symbolToString((*Cfg->streamSym)(Cfg->cStream)),
          (*Cfg->tokRow)(Cfg->cStream),
          (*Cfg->tokCol)(Cfg->cStream),
          symbolToString((*Cfg->tokSym)(Cfg->cStream))
        );
  if( Cfg->printMsg != (void (*)(string msg))NULL )
    (*Cfg->printMsg)(msg);
  else 
  if( printMsg != (void (*)(string msg))NULL )
    (*printMsg)(msg);
  else 
  if( !(*Cfg->unicode)(Cfg->cStream) )
    fprintf(STDERR,"%s",msg);
  else
    fprint_raw(STDERR,msg,-1);
  FreeMem(msg);
  ++Cfg->ErrCnt;
}

static void PT_synError(PLR_Pdf Pdf)
/* syntax error */
{ PTCFG* Cfg = PLR_CFGEXT(PTCFG*,Pdf);
  PT_synError_aux(Cfg);
}

static void PT_synError_ext(AbsPlr_T pconfig)
/* syntax error (external scanner and parser) */
{ PTCFG* Cfg = (PTCFG*)AP_getExtCfg(pconfig);
  PT_synError_aux(Cfg);
}

static void PT_debug_aux(PTCFG* Cfg, StdCPtr val)
{ 
  if( !(*Cfg->unicode)(Cfg->cStream) )
  {
    if( ! Cfg->list ) PT_print((PT_Term)val);
    else              PT_print(fst(PT_Term,(List(PT_Term))val));
  }
  else
  {
    if( ! Cfg->list ) PT_print_rawutf8((PT_Term)val);
    else              PT_print_rawutf8(fst(PT_Term,(List(PT_Term))val));
  }
}

static void PT_debug(PLR_Pdf Pdf, StdCPtr val)
/* print parse value 'val' */
{ PTCFG* Cfg = PLR_CFGEXT(PTCFG*,Pdf);
  PT_debug_aux(Cfg,val);
}

static void PT_debug_ext(AbsPlr_T pconfig, StdCPtr val)
/* print parse value 'val' (external scanner and parser) */
{ PTCFG* Cfg = (PTCFG*)AP_getExtCfg(pconfig);
  PT_debug_aux(Cfg,val);
}

static StdCPtr PT_shift_aux
               (
                 PTCFG* Cfg, int symId, 
                 Abs_T parser, int (*symType)(Abs_T parser, int symId)
               )
/* shift value = comment in reverse order combined with ComTree          */
/* shift value = token in reverse order combined with ( Tree = ComTree ) */
/*               - re-initialisation of ComTree                          */
{ short CurTyp = (short)(symId >= 0 ? (*symType)(parser,symId) : PLR_TYP_TOK);
  symbol CurTok = (*Cfg->tokSym)(Cfg->cStream),
         CurSym = symId >= 0 ? Cfg->CfgSyms[symId] : Cfg->ErrSym;
  PT_Term x; 
  if( Cfg->convertTok != (symbol (*)(symbol tok, symbol val))NULL )
    CurTok = (*Cfg->convertTok)(CurSym,CurTok);
  if( ! Cfg->list )
  {
    Cfg->Tree = PT_consT
                (
                  PT_updPos
                  (
                    PT_newTNode(CurSym,CurTyp,CurTok),
                    (*Cfg->streamSym)(Cfg->cStream),
                    (*Cfg->tokRow)(Cfg->cStream),
                    (*Cfg->tokCol)(Cfg->cStream)
                  ),
                  (PT_Term)Cfg->ComTree
                );
    x = (PT_Term)Cfg->Tree;
  }
  else
  {
    Cfg->Tree = XPT_consT
                (
                  PT_updPos
                  (
                    XPT_newTNode(CurSym,CurTyp,CurTok),
                    (*Cfg->streamSym)(Cfg->cStream),
                    (*Cfg->tokRow)(Cfg->cStream),
                    (*Cfg->tokCol)(Cfg->cStream)
                  ),
                  (List(PT_Term))Cfg->ComTree
                );
    x = fst(PT_Term,(List(PT_Term))Cfg->Tree);
  }
  if( PT_isComment(x) ) return( Cfg->ComTree = Cfg->Tree );
  else
  {
    Cfg->ComTree = (StdCPtr)NULL; return( Cfg->Tree );
  }
}

static StdCPtr PT_shift(PLR_Pdf Pdf, int symId)
/* shift handler */
{ PTCFG*  Cfg = PLR_CFGEXT(PTCFG*,Pdf); 
  PLR_Tab Tab = PLR_CfgTab(Pdf);
  return PT_shift_aux(Cfg,symId,Tab,PLR_symType);
}

static StdCPtr PT_shift_ext(AbsPlr_T pconfig, int symId)
/* shift handler (external scanner and parser) */
{ PTCFG*     Cfg     = (PTCFG*)AP_getExtCfg(pconfig);
  Abs_T      parser  = AP_getParser(pconfig);
  PF_symType symType = AP_getFunSymType(pconfig);
  return PT_shift_aux(Cfg,symId,parser,symType);
}

static PT_Term PT_revNodes(PT_Term* TreeRef)
/* C: tree list in reverse order */
{ PT_Term tlst, revtlst, t;
  BUG_NULL(TreeRef);
  tlst    = *TreeRef;
  revtlst = tlst;
  tlst    = PT_next(tlst);
  revtlst = PT_consT(revtlst,(PT_Term)NULL);
  while( tlst != (PT_Term)NULL )
  {
    t = PT_next(tlst); revtlst = PT_consT(tlst,revtlst); tlst = t;
  }
  return( revtlst );
}

static List(PT_Term) XPT_revNodes(List(PT_Term) TreeList)
/* Xaron: tree list in reverse order */
{ List(PT_Term) revtlst = (List(PT_Term))NULL, x;
  for( x = TreeList; ! empty(x); x = rst(x) )
    revtlst = XPT_consT(fst(PT_Term,x),revtlst);
  freeList(TreeList,primFree);
  return( revtlst );
}

static StdCPtr CPT_reduce
               (
                 PTCFG* Cfg, int symcnt, int prodId, bool accept,
                 Abs_T parser, Any_T (*topVal)(Abs_T PlrCfg),
                 int (*prodNT)(Abs_T parser, int prodId)
               )
/* C: reduction value = nonterminal                             */
/*                   parts = token/comment list - reverse order */
/*                   next  = comment list of last token,        */
/*                           if exists ( not accept )           */
/*                   next  = (PT_Term)NULL ( accept )           */
{ long row = (*Cfg->tokRow)(Cfg->cStream), col = (*Cfg->tokRow)(Cfg->cStream); 
  int i; PT_Term parts, next, t, t2;
  next = parts = (PT_Term)NULL;
  if( symcnt > 0 )
  {
    t = t2 = (PT_Term)(*topVal)(Cfg->PlrCfg);
    for( i=1; i < symcnt; ++i )
    {
      for( ; PT_next(t2) != (PT_Term)NULL; t2 = PT_next(t2) )
        ;
      t2 = PT_next(PT_consT(t2,(*topVal)(Cfg->PlrCfg)));
    }
    /* An dieser Stelle sind alle zu reduzierenden Symbole konkateniert, */
    /* t2 steht auf dem letzten Symbol, t auf dem ersten.                */
    row = PT_row(t2);
    col = PT_col(t2);
    if( ( next = PT_next(t2) ) != (PT_Term)NULL  && ! accept )
      PT_consT(t2,(PT_Term)NULL);   
    /* Falls nicht accept, sind die Kommentare des letzten Symbols       */
    /* geklippt und stehen in next.                                      */
    if( accept  && Cfg->ComTree != (StdCPtr)NULL )
    {
      /* Die Kommentare in ComTree ( am Ende der Quelle ) werden im      */
      /* accept-Fall an die Symbole in t gehaengt ( vorne weg wg. Rev )  */
      for( t2 = (PT_Term)Cfg->ComTree; 
           PT_next(t2) != (PT_Term)NULL; t2 = PT_next(t2) )
        ;
      PT_consT(t2,t); t = (PT_Term)Cfg->ComTree; Cfg->ComTree = (StdCPtr)NULL;
    }
    parts = PT_revNodes(&t);
  }
  if( prodId < 0 ) /* PanicMode Error Handling */
  { int symId = ( accept )
                ? (*prodNT)(parser,ABS(prodId)-1)
                : ABS(prodId)-1;
    Cfg->Tree = PT_updPos
                (
                  PT_newNtNode
                  (
                    Cfg->CfgSyms[symId],
                    Cfg->ErrSym,
                    parts
                  ),
                  (*Cfg->streamSym)(Cfg->cStream),row,col
                );
  }
  else
    Cfg->Tree = PT_updPos
                (
                  PT_newNtNode
                  (
                    Cfg->CfgSyms[(*prodNT)(parser,prodId)],
                    Cfg->PrdSyms[prodId],
                    parts
                  ),
                  (*Cfg->streamSym)(Cfg->cStream),row,col
                );
/*
....
  Cfg->Tree = PT_consT((PT_Term)Cfg->Tree,(PT_Term)NULL);
  Cfg->Tree = <Transformation>((PT_Term)Cfg->Tree);
....
*/
  if( Cfg->convertNtm != (PT_Term (*)(PT_Term Tree))NULL )
  {
    Cfg->Tree = PT_consT((PT_Term)Cfg->Tree,(PT_Term)NULL);
    Cfg->Tree = (*Cfg->convertNtm)((PT_Term)Cfg->Tree);
  }
  return( Cfg->Tree = PT_consT((PT_Term)Cfg->Tree,accept?(PT_Term)NULL:next) );
}

static StdCPtr XPT_reduce
               (
                 PTCFG* Cfg, int symcnt, int prodId, bool accept,
                 Abs_T parser, Any_T (*topVal)(Abs_T PlrCfg),
                 int (*prodNT)(Abs_T parser, int prodId)
               )
/* Xaron: reduction value = nonterminal                         */
/*                   parts = token/comment list - reverse order */
/*                   next  = comment list of last token,        */
/*                           if exists ( not accept )           */
/*                   next  = (PT_Term)NULL ( accept )           */
{ long row = (*Cfg->tokRow)(Cfg->cStream), col = (*Cfg->tokCol)(Cfg->cStream); 
  List(PT_Term) parts, next, t, t0; List(PT_Term)* t2; int i;
  next = parts = (List(PT_Term))NULL;
  if( symcnt > 0 )
  {
    t2 = &t0; t = t0 = (List(PT_Term))(*topVal)(Cfg->PlrCfg);
    for( i=1; i < symcnt; ++i )
    { 
      for( ; ! empty(rst(*t2)); t2 = rst_ref(*t2) )
        ;
      *rst_ref(*t2) = (*topVal)(Cfg->PlrCfg);
      t2 = rst_ref(*t2);
    }
    /* An dieser Stelle sind alle zu reduzierenden Symbole konkateniert, */
    /* t2 steht auf dem letzten Symbol, t auf dem ersten.                */
    row = PT_row(fst(PT_Term,*t2));
    col = PT_col(fst(PT_Term,*t2));
    if( ! empty( next = rst(*t2) ) && ! accept )
      *rst_ref(*t2) = (List(PT_Term))NULL;
    /* Falls nicht accept, sind die Kommentare des letzten Symbols       */
    /* geklippt und stehen in next.                                      */
    if( accept  && Cfg->ComTree != (StdCPtr)NULL )
    {
      /* Die Kommentare in ComTree ( am Ende der Quelle ) werden im      */
      /* accept-Fall an die Symbole in t gehaengt ( vorne weg wg. Rev )  */
      for( t2 = (List(PT_Term)*)(&Cfg->ComTree); 
           ! empty(rst(*t2)); t2 = rst_ref(*t2) )
        ;
      *rst_ref(*t2) = t;
      t = (List(PT_Term))Cfg->ComTree;
      Cfg->ComTree = (StdCPtr)NULL;
    }
    parts = XPT_revNodes(t);
  }
  if( prodId < 0 ) /* PanicMode Error Handling */
  { int symId = ( accept )
                ? (*prodNT)(parser,ABS(prodId)-1)
                : ABS(prodId)-1;
    Cfg->Tree = PT_updPos
                (
                  XPT_newNtNode
                  (
                    Cfg->CfgSyms[symId],
                    Cfg->ErrSym,
                    parts
                  ),
                  (*Cfg->streamSym)(Cfg->cStream),row,col
                );
  }
  else
    Cfg->Tree = PT_updPos
                (
                  XPT_newNtNode
                  (
                    Cfg->CfgSyms[(*prodNT)(parser,prodId)],
                    Cfg->PrdSyms[prodId],
                    parts
                  ),
                  (*Cfg->streamSym)(Cfg->cStream),row,col
                );
/*
....
  Cfg->Tree = <Transformation>((PT_Term)Cfg->Tree);
....
*/
  if( Cfg->convertNtm != (PT_Term (*)(PT_Term Tree))NULL )
    Cfg->Tree = (*Cfg->convertNtm)((PT_Term)Cfg->Tree);
  return
  ( 
    Cfg->Tree = XPT_consT((PT_Term)Cfg->Tree,accept?(List(PT_Term))NULL:next) 
  );
}

static StdCPtr PT_reduce(PLR_Pdf Pdf, int symcnt, int prodId, bool accept)
/* reduction value = nonterminal */
{ PTCFG*  Cfg  = PLR_CFGEXT(PTCFG*,Pdf);
  PLR_Tab PTab = PLR_CfgTab(Pdf);
  return
  ( 
    ( ! Cfg->list ) 
    ? CPT_reduce(Cfg,symcnt,prodId,accept,PTab,PLR_topVal,PLR_prodNonTerm) 
    : XPT_reduce(Cfg,symcnt,prodId,accept,PTab,PLR_topVal,PLR_prodNonTerm) 
  );
}

static StdCPtr PT_reduce_ext(AbsPlr_T pconfig, int symcnt, int prodId, bool accept)
/* reduction value = nonterminal */
{ PTCFG*     Cfg    = (PTCFG*)AP_getExtCfg(pconfig);
  Abs_T      parser = AP_getParser(pconfig);
  PIF_topVal topVal = AP_getFunTopVal(pconfig);
  PF_prodNT  prodNT = AP_getFunProdNT(pconfig);
  return
  ( 
    ( ! Cfg->list ) 
    ? CPT_reduce(Cfg,symcnt,prodId,accept,parser,topVal,prodNT) 
    : XPT_reduce(Cfg,symcnt,prodId,accept,parser,topVal,prodNT) 
  );
}

PT_Cfg PT_init(PLR_Tab PTab, Scn_Stream cStream)
/* initializes parse term construction 
   for parse table 'PTab' and scan stream 'cStream';
   creates a configuration
*/
{ int symcnt = PLR_symbolCnt(PTab), 
      tokcnt = PLR_tokenCnt(PTab),
      prdcnt = PLR_prodCnt(PTab), typ, i;
  PLR_Pdf Pdf; PTCFG* Cfg; bool oflg = False;
  BUG_NULL(cStream);
  Cfg             = (PTCFG*)NewMem(sizeof(PTCFG));
  Cfg->cStream    = cStream;
  Cfg->nextTok    = Stream_next;
  Cfg->tokID      = Stream_ctid;
  Cfg->tokSym     = Stream_csym;
  Cfg->streamSym  = Stream_cfil;
  Cfg->tokRow     = Stream_clin;
  Cfg->tokCol     = Stream_ccol; 
  Cfg->unicode    = Stream_unicode;
  Cfg->ErrCnt     = 0;
  Cfg->list       = False;
  Cfg->ErrSym     = stringToSymbol("[error]");
  Cfg->ComTree    = (StdCPtr)NULL;
  Cfg->Tree       = (StdCPtr)NULL;
  Cfg->convertTok = (symbol (*)(symbol tok, symbol val))NULL;
  Cfg->convertNtm = (PT_Term (*)(PT_Term Tree))NULL;
  Cfg->printMsg   = (void (*)(string msg))NULL;
  oflg = (tokcnt > 0 && !strcmp(PLR_symName(PTab,tokcnt-1),PLR_TOK_Other));
  Stream_defEofId(cStream,-1);
  Stream_defErrId(cStream,(short)((oflg==True)?tokcnt-1:-2));
  for( i=0; i < tokcnt-(oflg==True); ++i )
  // assertion: other token is last token
  {
    typ = PLR_symType(PTab,i);
    if( CFG_COM(typ) ) typ = CFG_COM_TO_TERM(typ);
    if( CFG_TOK(typ) ) Stream_defTokId(cStream,PLR_symName(PTab,i),(short)i);
    else               
    if( ! CFG_WCKEY(typ) )
      Stream_defKeyId(cStream,PLR_symName(PTab,i),(short)i);
    else
    { wc_string wckey;
      bug0((wckey = GS_utf8_to_ucs4(PLR_symName(PTab,i)))!=(wc_string)NULL,"");
      Stream_defWCKeyId(cStream,wckey,(short)i);
      FreeMem(wckey);
    }
  }
  Cfg->CfgSyms = (symbol*)NewMem(sizeof(symbol)*symcnt);
  for( i=0; i < symcnt; ++i ) 
    Cfg->CfgSyms[i] = stringToSymbol(PLR_symName(PTab,i));
  Cfg->PrdSyms = (symbol*)NewMem(sizeof(symbol)*prdcnt);
  for( i=0; i < prdcnt; ++i ) 
    Cfg->PrdSyms[i] = stringToSymbol(PLR_prodName(PTab,i));
  Pdf = PLR_createPdf(PTab,Cfg);
  PLR_addGetF(Pdf,PT_get);
  PLR_addCurSyF(Pdf,PT_curSy);
  PLR_addErrF(Pdf,PT_synError);
  PLR_addSftF(Pdf,PT_shift);
  PLR_addRedF(Pdf,PT_reduce);
  PLR_addDbgF(Pdf,PT_debug);
  Cfg->PlrCfg   = Pdf;
  Cfg->getPTCfg = PLR_CfgExt;
  return( (PT_Cfg)Cfg );
}

PT_Cfg PT_init_extscn(PLR_Tab PTab, AbsScn_T sconfig)
/* initializes parse term construction 
   for parse table 'PTab' and external scanner 'sconfig';
   creates a configuration
*/
{ int symcnt = PLR_symbolCnt(PTab), 
      tokcnt = PLR_tokenCnt(PTab),
      prdcnt = PLR_prodCnt(PTab), typ, i;
  PLR_Pdf Pdf; PTCFG* Cfg; bool oflg = False;
  SF_defID defEofID, defErrID; SF_defTxtID defTokID, defKeyID;
  SF_defWCTxtID defWCKeyID;
  Cfg                    = (PTCFG*)NewMem(sizeof(PTCFG));
  assert0(Cfg->cStream   = AS_getScanner(sconfig), "");
  assert0(Cfg->nextTok   = AS_getFunNextTok(sconfig), "");
  assert0(Cfg->tokID     = AS_getFunTokID(sconfig), "");
  assert0(Cfg->tokSym    = AS_getFunTokSym(sconfig), "");
  assert0(Cfg->streamSym = AS_getFunStreamSym(sconfig), "");
  assert0(Cfg->tokRow    = AS_getFunTokRow(sconfig), "");
  assert0(Cfg->tokCol    = AS_getFunTokCol(sconfig), ""); 
  assert0(Cfg->unicode   = AS_getFunUnicode(sconfig), "");
  Cfg->ErrCnt            = 0;
  Cfg->list              = False;
  Cfg->ErrSym            = stringToSymbol("[error]");
  Cfg->ComTree           = (StdCPtr)NULL;
  Cfg->Tree              = (StdCPtr)NULL;
  Cfg->convertTok        = (symbol (*)(symbol tok, symbol val))NULL;
  Cfg->convertNtm        = (PT_Term (*)(PT_Term Tree))NULL;
  Cfg->printMsg          = (void (*)(string msg))NULL;
  oflg = (tokcnt > 0 && !strcmp(PLR_symName(PTab,tokcnt-1),PLR_TOK_Other));
  assert0( defEofID   = AS_getFunDefEofID(sconfig), "");
  assert0( defErrID   = AS_getFunDefErrID(sconfig), "");
  assert0( defTokID   = AS_getFunDefTokID(sconfig), "");
  assert0( defKeyID   = AS_getFunDefKeyID(sconfig), "");
  assert0( defWCKeyID = AS_getFunDefWCKeyID(sconfig), "");
  (*defEofID)(Cfg->cStream,-1);
  (*defErrID)(Cfg->cStream,(short)((oflg==True)?tokcnt-1:-2));
  for( i=0; i < tokcnt-(oflg==True); ++i )
  // assertion: other token is last token
  {
    typ = PLR_symType(PTab,i);
    if( CFG_COM(typ) ) typ = CFG_COM_TO_TERM(typ);
    if( CFG_TOK(typ) ) (*defTokID)(Cfg->cStream,PLR_symName(PTab,i),(short)i);
    else               
    if( ! CFG_WCKEY(typ) )
      (*defKeyID)(Cfg->cStream,PLR_symName(PTab,i),(short)i);
    else
    { wc_string wckey;
      bug0((wckey = GS_utf8_to_ucs4(PLR_symName(PTab,i)))!=(wc_string)NULL,"");
      (*defWCKeyID)(Cfg->cStream,wckey,(short)i);
      FreeMem(wckey);
    }
  }
  Cfg->CfgSyms = (symbol*)NewMem(sizeof(symbol)*symcnt);
  for( i=0; i < symcnt; ++i ) 
    Cfg->CfgSyms[i] = stringToSymbol(PLR_symName(PTab,i));
  Cfg->PrdSyms = (symbol*)NewMem(sizeof(symbol)*prdcnt);
  for( i=0; i < prdcnt; ++i ) 
    Cfg->PrdSyms[i] = stringToSymbol(PLR_prodName(PTab,i));
  Pdf = PLR_createPdf(PTab,Cfg);
  PLR_addGetF(Pdf,PT_get);
  PLR_addCurSyF(Pdf,PT_curSy);
  PLR_addErrF(Pdf,PT_synError);
  PLR_addSftF(Pdf,PT_shift);
  PLR_addRedF(Pdf,PT_reduce);
  PLR_addDbgF(Pdf,PT_debug);
  Cfg->PlrCfg   = Pdf;
  Cfg->getPTCfg = PLR_CfgExt;
  return( (PT_Cfg)Cfg );
}

PT_Cfg PT_init_ext(AbsPlr_T pconfig, AbsScn_T sconfig)
/* initializes parse term construction 
   for external parser 'pconfig' and external scanner 'sconfig';
   creates a configuration
*/
{ int symcnt, tokcnt, prdcnt, typ, i; bool oflg = False;
  PTCFG* Cfg; Abs_T parser;
  PF_cfgsize symCnt, tokCnt, prodCnt; 
  PF_symName symName; PF_symType symType; PF_prodName prodName;
  SF_defID defEofID, defErrID; SF_defTxtID defTokID, defKeyID;
  SF_defWCTxtID defWCKeyID;
  assert0( parser   = AP_getParser(pconfig), "");
  assert0( symCnt   = AP_getFunSymCnt(pconfig), "");
  assert0( tokCnt   = AP_getFunTokCnt(pconfig), "");
  assert0( prodCnt  = AP_getFunProdCnt(pconfig), "");
  assert0( symName  = AP_getFunSymName(pconfig), "");
  assert0( symType  = AP_getFunSymType(pconfig), "");
  assert0( prodName = AP_getFunProdName(pconfig), "");
  /* only check complete specification ... */
  assert0( AP_getFunTopVal(pconfig), "");
  assert0( AP_getFunParse(pconfig), "");
  assert0( AP_getFunProdNT(pconfig), "");
  /* ... only check complete specification */
  symcnt = (*symCnt)(parser); 
  tokcnt = (*tokCnt)(parser);
  prdcnt = (*prodCnt)(parser);
  Cfg                    = (PTCFG*)NewMem(sizeof(PTCFG));
  assert0(Cfg->cStream   = AS_getScanner(sconfig), "");
  assert0(Cfg->nextTok   = AS_getFunNextTok(sconfig), "");
  assert0(Cfg->tokID     = AS_getFunTokID(sconfig), "");
  assert0(Cfg->tokSym    = AS_getFunTokSym(sconfig), "");
  assert0(Cfg->streamSym = AS_getFunStreamSym(sconfig), "");
  assert0(Cfg->tokRow    = AS_getFunTokRow(sconfig), "");
  assert0(Cfg->tokCol    = AS_getFunTokCol(sconfig), ""); 
  assert0(Cfg->unicode   = AS_getFunUnicode(sconfig), "");
  Cfg->ErrCnt            = 0;
  Cfg->list              = False;
  Cfg->ErrSym            = stringToSymbol("[error]");
  Cfg->ComTree           = (StdCPtr)NULL;
  Cfg->Tree              = (StdCPtr)NULL;
  Cfg->convertTok        = (symbol (*)(symbol tok, symbol val))NULL;
  Cfg->convertNtm        = (PT_Term (*)(PT_Term Tree))NULL;
  Cfg->printMsg          = (void (*)(string msg))NULL;
  oflg = (tokcnt > 0 && !strcmp((*symName)(parser,tokcnt-1),PLR_TOK_Other));
  assert0( defEofID   = AS_getFunDefEofID(sconfig), "");
  assert0( defErrID   = AS_getFunDefErrID(sconfig), "");
  assert0( defTokID   = AS_getFunDefTokID(sconfig), "");
  assert0( defKeyID   = AS_getFunDefKeyID(sconfig), "");
  assert0( defWCKeyID = AS_getFunDefWCKeyID(sconfig), "");
  (*defEofID)(Cfg->cStream,-1);
  (*defErrID)(Cfg->cStream,(short)((oflg==True)?tokcnt-1:-2));
  for( i=0; i < tokcnt-(oflg==True); ++i )
  // assertion: other token is last token
  {
    typ = (*symType)(parser,i);
    if( CFG_COM(typ) ) typ = CFG_COM_TO_TERM(typ);
    if( CFG_TOK(typ) ) (*defTokID)(Cfg->cStream,(*symName)(parser,i),(short)i);
    else               
    if( ! CFG_WCKEY(typ) )
      (*defKeyID)(Cfg->cStream,(*symName)(parser,i),(short)i);
    else
    { wc_string wckey;
      bug0((wckey=GS_utf8_to_ucs4((*symName)(parser,i)))!=(wc_string)NULL,"");
      (*defWCKeyID)(Cfg->cStream,wckey,(short)i);
      FreeMem(wckey);
    }
  }
  Cfg->CfgSyms = (symbol*)NewMem(sizeof(symbol)*symcnt);
  for( i=0; i < symcnt; ++i ) 
    Cfg->CfgSyms[i] = stringToSymbol((*symName)(parser,i));
  Cfg->PrdSyms = (symbol*)NewMem(sizeof(symbol)*prdcnt);
  for( i=0; i < prdcnt; ++i ) 
    Cfg->PrdSyms[i] = stringToSymbol((*prodName)(parser,i));
  AP_setExtCfg(pconfig,Cfg);
  AP_setFunNextTok(pconfig,PT_get_ext);
  AP_setFunCurTok(pconfig,PT_curSy_ext);
  AP_setFunError(pconfig,PT_synError_ext);
  AP_setFunShift(pconfig,PT_shift_ext);
  AP_setFunReduce(pconfig,PT_reduce_ext);
  AP_setFunDebug(pconfig,PT_debug_ext);
  Cfg->PlrCfg   = pconfig;
  Cfg->getPTCfg = AP_getExtCfg;
  return( (PT_Cfg)Cfg );
}

void PT_setMsgFun(void (*prMsg)(string msg))
/* defines 'prMsg' as ( static ) default message function
   ( 'msg': single byte character set or UTF-8 )
*/
{
  printMsg = prMsg;
}

void PT_setDiagFun(PT_Cfg PCfg, PT_Diag PDiag)
/* adds diagnose environment 'PDiag' to 
   parse term configuration 'PCfg' 
*/
{ PTCFG*  Cfg  = (PTCFG*)PCfg;
  PTDIAG* Diag = (PTDIAG*)PDiag;
  BUG_NULL(Cfg);
  Cfg->printMsg = Diag->printMsg;
}

void PT_setTokConvFun(PT_Cfg PCfg, symbol convTok(symbol tok, symbol val))
/* adds token value converter 'convTok' to 
   parse term configuration 'PCfg'
   ( user-defined shift-handler ) 
*/
{ PTCFG* Cfg = (PTCFG*)PCfg;
  BUG_NULL(Cfg);
  Cfg->convertTok = convTok;
}

void PT_setNtmConvFun(PT_Cfg PCfg, PT_Term convNtm(PT_Term Tree))
/* adds nonterminal value converter 'convNtm' to 
   parse term configuration 'PCfg'
   ( user-defined reduce-handler; must release each replaced source tree )
*/
{ PTCFG* Cfg = (PTCFG*)PCfg;
  BUG_NULL(Cfg);
  Cfg->convertNtm = convNtm;
}

void PT_quit(PT_Cfg PCfg)
/* terminates parse term construction;
   removes configuration 'PCfg'
*/
{ PTCFG* Cfg = (PTCFG*)PCfg;
  if( Cfg != (PTCFG*)NULL )
  {
    FreeMem(Cfg->CfgSyms);
    FreeMem(Cfg->PrdSyms);
    if( Cfg->getPTCfg == PLR_CfgExt )
      PLR_delPdf((PLR_Pdf)Cfg->PlrCfg);
    FreeMem(Cfg);
  }
}

PT_Term PT_parse(PT_Cfg PCfg, string StartSymbol, bool interprete)
#define PT_PARSE(pcfg,start)      PT_parse((pcfg),(start),False)
#define PT_INTERPRETE(pcfg,start) PT_parse((pcfg),(start),True)
/* parses and constructs parse term of type C ( see [ptm] ) 
   according configuration 'PCfg'; 
   uses 'StartSymbol' as start nonterminal or default if empty
   ( interprete --> early reduction ) 
*/
{ PTCFG* Cfg = (PTCFG*)PCfg;
  BUG_NULL(Cfg); BUG_NULL(StartSymbol);
  Cfg->list    = False;
  Cfg->ComTree = (StdCPtr)NULL;
  Cfg->Tree    = (StdCPtr)NULL;
  if( Cfg->getPTCfg == PLR_CfgExt )
  {
    if( strlen(StartSymbol) ) 
      PLR_parse((PLR_Pdf)Cfg->PlrCfg,StartSymbol,interprete);
    else
    { PLR_Tab Tab = PLR_CfgTab((PLR_Pdf)Cfg->PlrCfg);
      PLR_parse
      (
        (PLR_Pdf)Cfg->PlrCfg,PLR_symName(Tab,PLR_startSymbol(Tab,0)),interprete
      );
    }
  }
  else
  { PIF_parse parse = AP_getFunParse(Cfg->PlrCfg);
    if( strlen(StartSymbol) ) (*parse)(Cfg->PlrCfg,StartSymbol,interprete);
    else
    { Abs_T       parser   = AP_getParser(Cfg->PlrCfg);
      PF_symName  symName  = AP_getFunSymName(Cfg->PlrCfg);
      PF_startSym startSym = AP_getFunStartSym(Cfg->PlrCfg);
      BUG_NULL(startSym);
      (*parse)
      (
        Cfg->PlrCfg,(*symName)(parser,(*startSym)(parser,0)),interprete
      );
    }
  }
  return( (PT_Term)Cfg->Tree );
}

PT_Term XPT_parse(PT_Cfg PCfg, string StartSymbol, bool interprete)
#define XPT_PARSE(pcfg,start)      XPT_parse((pcfg),(start),False)
#define XPT_INTERPRETE(pcfg,start) XPT_parse((pcfg),(start),True)
/* parses and constructs parse term of type Xaron ( see [ptm] ) 
   according configuration 'PCfg'; 
   uses 'StartSymbol' as start nonterminal or default if empty
   ( interprete --> early reduction ) 
*/
{ PTCFG*  Cfg = (PTCFG*)PCfg;
  PT_Term res = (PT_Term)NULL;
  BUG_NULL(StartSymbol);
  Cfg->list    = True;
  Cfg->ComTree = (StdCPtr)NULL;
  Cfg->Tree    = (StdCPtr)NULL;
  if( Cfg->getPTCfg == PLR_CfgExt )
  {
    if( strlen(StartSymbol) )
      PLR_parse((PLR_Pdf)Cfg->PlrCfg,StartSymbol,interprete);
    else
    { PLR_Tab Tab = PLR_CfgTab((PLR_Pdf)Cfg->PlrCfg);
      PLR_parse
      (
        (PLR_Pdf)Cfg->PlrCfg,PLR_symName(Tab,PLR_startSymbol(Tab,0)),interprete
      );
    }
  }
  else
  { PIF_parse parse = AP_getFunParse(Cfg->PlrCfg);
    if( strlen(StartSymbol) ) (*parse)(Cfg->PlrCfg,StartSymbol,interprete);
    else
    { Abs_T       parser   = AP_getParser(Cfg->PlrCfg);
      PF_symName  symName  = AP_getFunSymName(Cfg->PlrCfg);
      PF_startSym startSym = AP_getFunStartSym(Cfg->PlrCfg);
      BUG_NULL(startSym);
      (*parse)
      (
        Cfg->PlrCfg,(*symName)(parser,(*startSym)(parser,0)),interprete
      );
    }
  }
  if( ! empty((List(PT_Term))Cfg->Tree) ) 
  {
    res = fst(PT_Term,(List(PT_Term))Cfg->Tree);
    freeList((List(PT_Term))Cfg->Tree,primFree);
  }
  return( res );
}

int PT_synErrorCnt(PT_Cfg PCfg)
/* number of syntax errors in parse term configuration 'PCfg' */
{ PTCFG* Cfg = (PTCFG*)PCfg;
  BUG_NULL(Cfg);
  return( Cfg->ErrCnt );
}

symbol PT_ErrorSymbol(PT_Cfg PCfg)
/* symbol of error token in parse term configuration 'PCfg' */
{ PTCFG* Cfg = (PTCFG*)PCfg;
  BUG_NULL(Cfg);
  return( Cfg->ErrSym );
}


/*I--------------------------- Semantic Analysis ---------------------------- */

static int ErrorCnt   = 0;
static int WarningCnt = 0;

/* expects single byte or UTF-8 character set */

static void PT_error_aux(PT_Term PTree, PTDIAG* Diag, string lvl, string format, va_list args)
/* sematic error */
{ Sink snk = Sink_open(); string msg;
  if( PTree != (PT_Term)NULL && PT_hasPos(PTree) )
  {
    Sink_printf
    (
      snk,"%s(%d,%d): ", 
      symbolToString(PT_file(PTree)), PT_row(PTree), PT_col(PTree)
    );
  }
  if( strlen(lvl) > 0 )
  {
    Sink_printf(snk,"%s: ",lvl);
  }
  Sink_vprintf(snk, format, args);
  Sink_printf(snk,".\n");
  msg = Sink_close(snk);
  if( Diag != (PTDIAG*)NULL && Diag->printMsg != (void (*)(string msg))NULL )
    (*Diag->printMsg)(msg);
  else
  if( printMsg != (void (*)(string msg))NULL )
    (*printMsg)(msg);
  else fprint_raw(STDERR,msg,-1);
  FreeMem(msg);
}

/*I---------------- ... using the default environment ( static ) ------------ */


void PT_diagnose(PT_Term PTree, string format, ...)
/* prints a test message for parse term node 'PTree'
   according variable format specification 'format' and '...'
*/
{ va_list args; 
  va_start(args,format);
  PT_error_aux(PTree, (PTDIAG*)NULL, "test", format, args);
  va_end(args);
}

void PT_error(PT_Term PTree, string format, ...)
/* increments the number of semantic errors and
   prints an error message for parse term node 'PTree'
   according variable format specification 'format' and '...'
*/
{ va_list args; 
  ErrorCnt += 1;
  va_start(args,format);
  PT_error_aux(PTree, (PTDIAG*)NULL, "error", format, args);
  va_end(args);
}

void PT_warn(PT_Term PTree, string format, ...)
/* increments the number of warnings and
   prints a warning message for parse term node 'PTree'
   according variable format specification 'format' and '...'
*/
{ va_list args; 
  WarningCnt += 1;
  va_start(args,format);
  PT_error_aux(PTree, (PTDIAG*)NULL, "warning", format, args);
  va_end(args);
}

void PT_setErrorCnt(int cnt)
/* resets the number of semantic errors with 'cnt' */
{
  ErrorCnt = cnt;
}

int PT_errorCnt(void)
/* number of semantic errors */
{
  return( ErrorCnt );
}

void PT_setWarningCnt(int cnt)
/* resets the number of warnings with 'cnt' */
{
  WarningCnt = cnt;
}

int PT_warnCnt(void)
/* number of warnings */
{
  return( WarningCnt );
}


/*I---------------- ... using the diagnose environment ( reentrant ) -------- */


PT_Diag PT_diag_init(void (*prMsg)(string msg))
/* creates a diagnose environment 
   using 'prMsg' as message function
   ( 'msg': single byte character set or UTF-8 )
*/
{ PTDIAG* Diag = (PTDIAG*)NewMem(sizeof(PTDIAG));
  Diag->ErrorCnt   = 0;
  Diag->WarningCnt = 0;
  Diag->printMsg   = prMsg;
  return (Diag);
}

void PT_diag_quit(PT_Diag PDiag)
/* removes diagnose environment 'PDiag' */
{
  FreeMem(PDiag);
}

void PT_diag_msg(PT_Term PTree, PT_Diag PDiag, string format, ...)
/* prints a message for parse term node 'PTree'
   according diagnose environment 'PDiag',
   variable format specification 'format' and '...'
*/
{ va_list args; 
  va_start(args,format);
  PT_error_aux(PTree, (PTDIAG*)PDiag, "", format, args);
  va_end(args);
}

void PT_diag_test(PT_Term PTree, PT_Diag PDiag, string format, ...)
/* like PT_diag_msg; prints a test message */
{ va_list args; 
  va_start(args,format);
  PT_error_aux(PTree, (PTDIAG*)PDiag, "test", format, args);
  va_end(args);
}

void PT_diag_err(PT_Term PTree, PT_Diag PDiag, string format, ...)
/* increments the number of semantic errors 
   in diagnose environment 'PDiag' and
   prints an error message for parse term node 'PTree'
   according variable format specification 'format' and '...'
*/
{ va_list args; 
  if( PDiag != (PT_Diag)NULL )
    ((PTDIAG*)PDiag)->ErrorCnt += 1;
  else ErrorCnt += 1;
  va_start(args,format);
  PT_error_aux(PTree, (PTDIAG*)PDiag, "error", format, args);
  va_end(args);
}

void PT_diag_warn(PT_Term PTree, PT_Diag PDiag, string format, ...)
/* increments the number of warnings 
   in diagnose environment 'PDiag' and
   prints a warning message for parse term node 'PTree'
   according variable format specification 'format' and '...'
*/
{ va_list args; 
  if( PDiag != (PT_Diag)NULL )
    ((PTDIAG*)PDiag)->WarningCnt += 1;
  else WarningCnt += 1;
  va_start(args,format);
  PT_error_aux(PTree, (PTDIAG*)PDiag, "warning", format, args);
  va_end(args);
}

void PT_diag_setErrorCnt(PT_Diag PDiag, int cnt)
/* resets the number of semantic errors 
   in diagnose environment 'PDiag' with 'cnt'
*/
{ PTDIAG* Diag = (PTDIAG*)PDiag;
  BUG_NULL(Diag);
  Diag->ErrorCnt = cnt;
}

int PT_diag_errorCnt(PT_Diag PDiag)
/* number of semantic errors in diagnose environment 'PDiag' */
{ PTDIAG* Diag = (PTDIAG*)PDiag;
  BUG_NULL(Diag);
  return( Diag->ErrorCnt );
}

void PT_diag_setWarningCnt(PT_Diag PDiag, int cnt)
/* resets number of warnings 
   in diagnose environment 'PDiag' with 'cnt'
*/
{ PTDIAG* Diag = (PTDIAG*)PDiag;
  BUG_NULL(Diag);
  Diag->WarningCnt = cnt;
}

int PT_diag_warnCnt(PT_Diag PDiag)
/* number of warnings in diagnose environment 'PDiag' */
{ PTDIAG* Diag = (PTDIAG*)PDiag;
  BUG_NULL(Diag);
  return( Diag->WarningCnt );
}

void (*PT_diag_msgFun(PT_Diag PDiag))(string msg)
/* message function in diagnose environment 'PDiag' */
{ PTDIAG* Diag = (PTDIAG*)PDiag;
  BUG_NULL(Diag);
  return( Diag->printMsg );
}


/*I---------------- Accessing configuration ( Xaron support ) --------------- */

Scn_Stream PT_stream(PT_Cfg PCfg)
/* current scan stream in parse term configuration 'PCfg' */
{ PTCFG* Cfg = (PTCFG*)PCfg;
  assert0(Cfg != (PTCFG*)NULL && Cfg->getPTCfg == PLR_CfgExt, "");
  return( Cfg->cStream );
}

PLR_Tab PT_ptab(PT_Cfg PCfg)
/* current parse table in parse term configuration 'PCfg' */
{ PTCFG* Cfg = (PTCFG*)PCfg;
  assert0(Cfg != (PTCFG*)NULL && Cfg->getPTCfg == PLR_CfgExt, "");
  return( PLR_CfgTab((PLR_Pdf)Cfg->PlrCfg) );
}
