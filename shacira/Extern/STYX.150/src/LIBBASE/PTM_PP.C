/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ptm_pp.c]          Parse Tree Transformation & Pretty Printing          */
/*                                                                          */
/* Copyright (c) 1995 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/*FIXME: layout, unicode support for pretty printer */

#include "ptm.h"
#include "prs.h"

#include "cfg_dfn.h"
#include "prs_dfn.h"
#include "hmap.h"
#include "hset.h"
#include "pathes.h"
#include "gstream.h"

/*!!
   The module [ptm_pp] supports some means for source-source-transformations.

   1) It performs a tree-to-tree transformation based on the corresponding 
      grammar specifications. It handles comments, too.

      source tree based on CFG 1
      specification of CFG 2
      -------------------------------------------->  concrete target tree
      abstraction(CFG 1)   = abstraction(CFG 2)      based on CFG 2
      regexp(token(CFG 1)) = regexp(token(CFG 2))

   2) It provides the pretty printing of parse trees. This is usefull after
      a transformation, because the target tree doesn't contain any position
      information.

   Note:
   This module is still under construction. The main thing todo refer to the
   layout results which are some times broken.

   Using the reentrant interface functions you can perform multiple
   transformations at a time.
*/

/*I---------------------------- Macros ------------------------------------- */

/*! 
  <p><b>Token separation types</b>
*/

/*DOC_INTERFACE*/
#define PTP_SEP_NON 0 // none
#define PTP_SEP_SPC 1 // space
#define PTP_SEP_IND 2 // indent
#define PTP_SEP_ROW 3 // row

#define PTP_MAX_COL 78
#define PTP_TAB_LEN 1

#define ROWS(l)     ( (short)(((unsigned long)(l)) >> 16) )
#define COLS(l)     ( (short)(((unsigned long)(l)) & 0xFFFF) )

ExternalType(PTP_T) /* Abstract transformation and pp type */
{
  /* transformation */

  symbol language;  /* target language            */
  c_bool utf8;      /* utf8 source character set  */
  c_bool wprint;    /* pp output (if utf8)        */

  MAPTY  mtyp0;     /* type 'visited'             */
  MAPTY  mtyp2;     /* type 'ntmmap'              */
  MAP(symbol,_)                         visited; 
                    /* visited production symbol  */
  MAP(symbol,ROW(ROW(symbol)))          ntmmap;  
                    /* NT |-> PRD |-> PRDSYMBOLS  */
  MAP(symbol,symbol (*)(symbol,symbol)) cnvmap;  
                    /* TK |-> conversion          */

  /* for diagnosis, see 'PTP_nt_transform' and 'PTP_transform' */
  int    last_lin;
  int    last_col;
  symbol last_nt;
  symbol last_prod;

  /* pretty printing */

  symbol  outfile;   /* output filename            */

  MAPTY   mtyp1;     /* type 'tkmmap', 'frmmap'    */
  MAP(symbol,MAP(symbol,ROW(int))) frmmap; 
                                  /* NT |-> PRD |-> PRDSYM |-> SYMFRM */
  MAP(symbol,MAP(symbol,int))      tkmmap;
               /* TK |-> { TK } -- Token, which need not be seperated */

  int     linlen;    /* row length                 */
  bool    nlflg;     /* flag 'row increment'       */
  bool    tosync;    /* flag 'token column'        */
  PT_Itr  lookahead; /* term iterator 'next token' */
  PT_Term currtok;   /* current token              */
};

/* static context for non-reentrant transformation & pp interface functions */
static ConcreteImp(PTP_T) curctx =
{
  (symbol)NULL, C_False, C_False, 
  (MAPTY)NULL, (MAPTY)NULL, (MAP(_,_))NULL, (MAP(_,_))NULL, (MAP(_,_))NULL,
  0, 0, (symbol)NULL, (symbol)NULL,
  (symbol)NULL, 
  (MAPTY)NULL, (MAP(_,_))NULL, (MAP(_,_))NULL,
  PTP_MAX_COL, C_False, C_True, (PT_Itr)NULL, (PT_Term)NULL
};
static PTP_T pcurctx = &curctx;


/*I---------------------------- Init & Quit -------------------------------- */

static void PTP_init_aux(PTP_T ctx, PLR_Tab tab)
{ int pcnt = PLR_prodCnt(tab), scnt, i, j, n, f;
  ctx->outfile  = stringToSymbol("");
  ctx->language = stringToSymbol(PLR_language(tab));
  ctx->mtyp0 = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  ctx->mtyp1 = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,HMP_freeMap);
  ctx->mtyp2 = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,OT_delT);
  ctx->visited = MAP_newMap(ctx->mtyp0);
  ctx->cnvmap  = MAP_newMap(ctx->mtyp0);
  ctx->frmmap  = MAP_newMap(ctx->mtyp1);
  ctx->ntmmap  = MAP_newMap(ctx->mtyp2);
  ctx->tkmmap  = MAP_newMap(ctx->mtyp1);
  for( i=0; i < pcnt; ++i )
  { symbol s1, s2; 
    MAP(symbol,ROW(int)) m; ROW(_) t, t2, t3;
    n    = PLR_prodNonTerm(tab,i);
    scnt = PLR_prodSymCnt(tab,i);
    s1 = stringToSymbol(PLR_symName(tab,n));
    s2 = stringToSymbol(PLR_prodName(tab,i));
    if( ! MAP_defined(ctx->frmmap,s1) )
    {
      m = MAP_newMap(ctx->mtyp2);
      t = OT_CREATE(ROW(ROW(symbol)),primCopy,OT_delT,primEqual);
      MAP_dfndom(ctx->frmmap,s1,m);
      MAP_dfndom(ctx->ntmmap,s1,t);
    }
    else 
    {
      m = MAP_apply(MAP(symbol,ROW(int)),ctx->frmmap,s1);
      t = MAP_apply(ROW(ROW(symbol)),ctx->ntmmap,s1);
    }
    t2 = OT_CREATE_ADT(int);
    t3 = OT_CREATE_ADT(symbol);
    MAP_dfndom(m,s2,t2);
    OT_T_INS(t2,PLR_prodMethod(tab,i));
    OT_T_INS(t,t3);
    OT_T_INS(t3,s2);
    for( j=0; j < scnt; ++j )
    { int ps = PLR_prodSymbol(tab,i,j);
      OT_T_INS(t3,stringToSymbol(PLR_symName(tab,ps)));
      OT_T_INS(t3,PLR_symType(tab,ps));
      f = PLR_prodSymFrm(tab,i,j); OT_T_INS(t2,f);
    }
  }
}

void PTP_init(PLR_Tab tab)
/* initializes transformation and pretty printing 
   based on parse table 'tab' as target grammar specification
*/
{ 
  PTP_init_aux(pcurctx,tab);
}

PTP_T PTP_init_reentrant(PLR_Tab tab)
/* reentrant version of PTP_init */
{ PTP_T ctx = New(PTP_T);
  PTP_init_aux(ctx,tab);
  ctx->linlen = PTP_MAX_COL;
  ctx->utf8   = C_False;
  ctx->wprint = C_False;
  return ctx;
}

static void PTP_quit_aux(PTP_T ctx)
{
  MAP_freeMap(ctx->visited);
  MAP_freeMap(ctx->cnvmap);
  MAP_freeMap(ctx->frmmap);
  MAP_freeMap(ctx->ntmmap);
  MAP_freeMap(ctx->tkmmap);
  MAP_freeTyp(ctx->mtyp2);
  MAP_freeTyp(ctx->mtyp1);
  MAP_freeTyp(ctx->mtyp0);
}

void PTP_quit(void)
/* terminates transformation and pretty printing */
{
  PTP_quit_aux(pcurctx);
}

void PTP_quit_reentrant(PTP_T ctx)
/* reentrant version of PTP_quit; consumes 'ctx' */
{
  BUG_NULL(ctx);
  PTP_quit_aux(ctx);
  FreeMem(ctx);
}

void PTP_set_line(int len)
/* set 'len' as line length for pretty printing */
{
  assert0((pcurctx->linlen = len) > 0,"length <= 0");
}

void PTP_set_line_reentrant(PTP_T ctx, int len)
/* reentrant version of PTP_set_line */
{
  BUG_NULL(ctx);
  assert0((ctx->linlen = len) > 0,"length <= 0");
}

static void PTP_tok_sep_aux(PTP_T ctx, symbol t_lft, symbol t_rgt, int sep)
{ MAP(symbol,int) map;
  BUG_NULL(ctx->tkmmap);
  assert(sep >= PTP_SEP_NON && sep <= PTP_SEP_ROW,"invalid seperator");
  if( ! MAP_defined(ctx->tkmmap,t_lft) )
  {
    map = MAP_newMap(ctx->mtyp0);
    MAP_dfndom(ctx->tkmmap,t_lft,map);
  }
  else map = MAP_apply(MAP(symbol,map),ctx->tkmmap,t_lft);
  MAP_ovrdom(map,t_rgt,sep);
}

void PTP_tok_sep(symbol t_lft, symbol t_rgt, int sep)
/* specifies the kind of seperation ( 'sep' )
   between the token 't_rgt' and 't_lft'; 
   replaces a previously defined seperation
*/
{
  PTP_tok_sep_aux(pcurctx,t_lft,t_rgt,sep);
}

void PTP_tok_sep_reentrant(PTP_T ctx, symbol t_lft, symbol t_rgt, int sep)
/* reentrant version of PTP_tok_sep */
{
  BUG_NULL(ctx);
  PTP_tok_sep_aux(ctx,t_lft,t_rgt,sep);
}

void PTP_tok_conv(symbol t_id, symbol (*conv)(symbol t_id, symbol t_src))
/* specifies a conversion 'conv' for token 't_id';
   replaces a previously defined conversion
   't_id' = NULL --> apply 'conv' to all tokens
*/
{
  BUG_NULL(pcurctx->cnvmap);
  MAP_dfndom(pcurctx->cnvmap,t_id,conv);
}

void PTP_tok_conv_reentrant
     (
       PTP_T ctx, symbol t_id, symbol (*conv)(symbol t_id, symbol t_src)
     )
/* reentrant version of PTP_tok_conv */
{
  BUG_NULL(ctx);
  BUG_NULL(ctx->cnvmap);
  MAP_dfndom(ctx->cnvmap,t_id,conv);
}

void PTP_tok_cset(c_bool utf8, c_bool wprint)
/* specifies source character set (single/multi-byte) and 
   pp output (on multi-byte source character set) 
*/
{
  pcurctx->utf8   = utf8;
  pcurctx->wprint = wprint;
}

void PTP_tok_cset_reentrant(PTP_T ctx, c_bool utf8, c_bool wprint)
/* reentrant version of PTP_tok_cset */
{
  BUG_NULL(ctx);
  ctx->utf8   = utf8;
  ctx->wprint = wprint;
}

/*I------------------------- Term Pretty Printer --------------------------- */

/* ------------------------- Pass 1: Symbol Positions ---------------------- */

static void PTP_swap(StdCPtr* a, StdCPtr* b)
{ StdCPtr h = *a;
  *a = *b; *b = h;
}

static unsigned long PTP_toklen(short row, short col)
{ unsigned long l, r, c;
  r = ((unsigned long)row) << 16;
  r = r & 0xFFFF0000;
  c = ((unsigned long)col) & 0x0000FFFF;
  l = r | c;
  return l;
}

static unsigned long PTP_vallen(PTP_T ctx, string v)
{ wc_string ws = (wc_string)NULL;
  short     tr = 0, tc = 0;
  size_t    l  = strlen(v), i;
  if( ctx->utf8 && ctx->wprint )
  {
    ws = GS_utf8_to_ucs4(v);
    if( ws != (wc_string)NULL )
    {
      l = WCStrLen(ws);
      for( i=0; i < l; ++i )
      {
        if( ws[i] == WCHAR_LITERAL('\n') ) 
        { 
          ++tr; tc = 0; 
        }
        else 
        if( ws[i] == WCHAR_LITERAL('\t') ) 
        { 
          tc += PTP_TAB_LEN; 
        }
        else ++tc;
      }
      FreeMem(ws);
    }
  }
  else
  {
    for( i=0; i < l; ++i )
    {
      if( v[i] == '\n' ) 
      { 
        ++tr; tc = 0; 
      }
      else 
      if( v[i] == '\t' ) { tc += PTP_TAB_LEN; }
      else 
      {
        ++tc;
        if( ctx->utf8 && 
            !( isascii(v[i]) && ( isprint(v[i]) || isspace(v[i]) ) ) )
        {
          ++tc;
        }
      }
    }
  }
  return PTP_toklen(tr,tc);
}

static unsigned long PTP_add_len
                     (
                       PTP_T ctx, 
                       unsigned long l1, unsigned long ls, unsigned long l2
                     )
{ short r, c;
  r = ROWS(l1) + ROWS(ls) + ROWS(l2);
  c = COLS(l1) + COLS(ls) + COLS(l2);
  if( c >= ctx->linlen )
  {
    ++r; c = COLS(l2);
  }
/*XXX
  else c += ( COLS(l1) > 0 && COLS(l2) > 0 );
*/
  return PTP_toklen(r,c);
}

static void PTP_setNextTok(PT_Itr itr)
{ int state = PT_stateIT(itr);
  if( state == PT_ROOT || state == PT_PRAE || state == PT_POST )
  {
    while( PT_df_getIT(itr) )
    { 
      if( PT_stateIT(itr) == PT_PRAE && ! PT_isNonTerm(PT_termIT(itr)) )
        break;
    }
  }
}

static PT_Term PTP_getNextTok(PT_Itr itr)
{ int state = PT_stateIT(itr);
  return ( state == PT_ROOT || state == PT_PRAE || state == PT_POST )
         ? PT_termIT(itr) : (PT_Term)NULL;
}

static short PTP_toksep(PTP_T ctx, PT_Term l, PT_Term r)
{ short res = PTP_SEP_NON;
  if( l != (PT_Term)NULL  && r != (PT_Term)NULL ) 
  { 
    res = PT_isComment(l) ? PTP_SEP_IND : PTP_SEP_SPC;
    if( MAP_defined(ctx->tkmmap,PT_symbol(l)) )
    { MAP(symbol,int) map = 
        MAP_apply(MAP(symbol,int),ctx->tkmmap,PT_symbol(l));
      if( MAP_defined(map,PT_symbol(r)) )
        res = MAP_apply(int,map,PT_symbol(r));
    }
  }
  return res;
}

static short PTP_colsep(PTP_T ctx, short row, short col)
{ PT_Term nexttok = PTP_getNextTok(ctx->lookahead);
  short sep = PTP_toksep(ctx,ctx->currtok,nexttok); 
  return (short)( 
           sep >= PTP_SEP_SPC          && 
           row == PT_row(ctx->currtok) && 
           col <  PT_col(ctx->currtok) + 
                  COLS((unsigned long)PT_file(ctx->currtok)) + sep
         );
}

static void PTP_tokpos
            (
              PTP_T ctx, PT_Term t, long* row, long* col, short ind
            )
{ string v = symbolToString(PT_value(t));
  unsigned long tl = PTP_vallen(ctx,v);
  long r = *row, c = *col; 
  if( COLS(tl) + c >= ctx->linlen )
  {
    r += ( ! ctx->nlflg ); 
    c = (( COLS(tl) + ind >= ctx->linlen ) ? 0 : ind);
  }
  PT_updPos(t,(symbol)tl,r,c);
  *row = r + ROWS(tl); *col = c + COLS(tl);
}

static void PTP_updpos(PTP_T ctx, PT_Term tree, long row, long* col)
{ 
  if( tree != (PT_Term)NULL )
  { 
    if( ctx->tosync )
    {
      *col = *col + PTP_colsep(ctx,(short)row,(short)(*col));
      ctx->tosync = False;
    }
    PT_updPos(tree,PT_file(tree),row,*col);
    if( PT_isNonTerm(tree) )
    {
      if( ! PT_isXaron(tree) )
      { PT_Term ts; 
        for( ts = PT_parts(tree); ts != (PT_Term)NULL; ts = PT_next(ts) )
          PTP_updpos(ctx,ts,row,col);
      }
      else
      { List(PT_Term) ts;
        for( ts = XPT_parts(tree); ! empty(ts); ts = rst(ts))
          PTP_updpos(ctx,fst(PT_Term,ts),row,col);
      }
    }
    else 
    {
      ctx->currtok = tree;
      PTP_setNextTok(ctx->lookahead);
      *col = *col + COLS((unsigned long)PT_file(tree));
      ctx->tosync = True;
    }
  }
}

static unsigned long PTP_cfgsep(PT_Term t, ROW(int) ps, long* idx)
{ short row = 0, col = 0;
  if( ! PT_isComment(t) && ps != (ROW(int))NULL && OT_CNT(ps) > 1 )
  { 
    if( *idx > 1 ) 
    { int f; 
      f = OT_GET(int,ps,*idx);
      if( f <= 0 ) 
      {
        row = 1; 
        col = ABS(f);
      }
    }
    *idx = *idx + 1;
  }
  return PTP_toklen(row,col);
}

static void PTP_sync_to_cfg
            (
              PTP_T ctx, unsigned long sl, 
              long* row, long* col, short* ind
            )
{
  if( ROWS(sl) )
  {
    if( ! ctx->nlflg )
    {
      *row  = *row + 1; 
      ctx->nlflg = True;
    }
    *col = *ind = *ind + COLS(sl);
  }
}

static unsigned long PTP_sync_to_tok
                     (
                       PTP_T ctx, unsigned long sl, short sep,
                       long* row, long* col, short* ind
                     )
{ /* res = seperation between current and next token */
  unsigned long res = 0L; 
  if( sep == PTP_SEP_IND || sep == PTP_SEP_ROW )
  { long r = 1 + ( sep == PTP_SEP_ROW );
    *row  = *row + r; 
    if( ROWS(sl) > 0 )
    {
      *col = *ind = *ind + COLS(sl);
    }
    else *col = *ind;
    ctx->nlflg = True;
    res = PTP_toklen((short)r,0); 
  }
  else
  {
    if( ROWS(sl) > 0 )
    {
      *row = *row + 1; 
      *col = *ind = *ind + COLS(sl);
      ctx->nlflg = True;
    }
    else 
    { long c = ( sep == PTP_SEP_SPC );
      *col = *col + c;
      res = PTP_toklen(0,(short)c); 
    }
  }
  return res;
}

static unsigned long PTP_pass1_aux
                     (
                       PTP_T ctx, PT_Term t, ROW(int) ps, long* idx, 
                       long* row, long* col, short* ind
                     )
{ unsigned long sl = PTP_cfgsep(t,ps,idx), res = 0L;
  PT_Term nexttok = PTP_getNextTok(ctx->lookahead);
  short sep = PTP_toksep(ctx,ctx->currtok,nexttok); 
  if( ctx->tosync )
  {
    res = PTP_sync_to_tok(ctx,sl,sep,row,col,ind);
    ctx->tosync = False;
  }
  else PTP_sync_to_cfg(ctx,sl,row,col,ind);
  if( ! PT_isNonTerm(t) )
  {
    assert0
	(
	  PTP_colsep(ctx,(short)(*row),(short)(*col)) == 0,"missing token seperator"
	);
    PTP_tokpos(ctx,t,row,col,*ind);
    ctx->currtok = t;
    PTP_setNextTok(ctx->lookahead);
    ctx->tosync = True;
    ctx->nlflg = False;
  }
  return res;
}

static void PTP_pass1
            (
              PTP_T ctx, PT_Term tree, long* row, long* col, short ind
            )
{ 
  if( tree != (PT_Term)NULL )
  {
    if( PT_isNonTerm(tree) )
    { symbol p = PT_product(tree), n = PT_symbol(tree); 
      short pi; long r = *row, c = *col, i = 1L; 
      unsigned long tl = 0L, tl_aux; bool nl = ctx->nlflg; 
      ROW(int) ps = (ROW(int))NULL;
      PT_Itr it = PT_copyIT(ctx->lookahead);
      PT_Term ct = ctx->currtok;
      if( MAP_defined(ctx->frmmap,n) )
      { MAP(symbol,ROW(int)) m = MAP_apply(MAP(symbol,ROW(int)),ctx->frmmap,n);
        ps = MAP_apply(ROW(int),m,p);
        if( OT_GET(int,ps,0) == PLR_PRD_GRP ) ++r;
      }
      if( ! PT_isXaron(tree) )
      { PT_Term ts;
        for( ts = PT_parts(tree); ts != (PT_Term)NULL; ts = PT_next(ts) )
        {
          pi = (short)(*col);
          tl_aux = PTP_pass1_aux(ctx,ts,ps,&i,&r,&c,&pi);
          PTP_pass1(ctx,ts,&r,&c,pi);
          tl = PTP_add_len(ctx,tl,tl_aux,(unsigned long)PT_file(ts));
        }
        if( ps != (ROW(int))NULL            && 
            OT_GET(int,ps,0) == PLR_PRD_REC && 
            ROWS(tl) == 0                   &&
            COLS(tl) + *col < ctx->linlen    )
        { 
          c = *col; r = *row;
          PTP_swap((StdCPtr*)(&ctx->lookahead),(StdCPtr*)(&it)); 
          PTP_swap((StdCPtr*)(&ctx->currtok),(StdCPtr*)(&ct)); 
          PTP_swap((StdCPtr*)(&ctx->nlflg),(StdCPtr*)(&nl));
          for( ts = PT_parts(tree); ts != (PT_Term)NULL; ts = PT_next(ts) )
            PTP_updpos(ctx,ts,r,&c);
          PTP_swap((StdCPtr*)(&it),(StdCPtr*)(&ctx->lookahead)); 
          PTP_swap((StdCPtr*)(&ct),(StdCPtr*)(&ctx->currtok)); 
          ctx->nlflg = False;
        }
      }
      else
      { List(PT_Term) ts; PT_Term t;
        for( ts = XPT_parts(tree); ! empty(ts); ts = rst(ts))
        { 
          pi = (short)(*col);
          t = fst(PT_Term,ts);
          tl_aux = PTP_pass1_aux(ctx,t,ps,&i,&r,&c,&pi);
          PTP_pass1(ctx,t,&r,&c,pi);
          tl = PTP_add_len(ctx,tl,tl_aux,(unsigned long)PT_file(t));
        }
        if( ps != (ROW(int))NULL            && 
            OT_GET(int,ps,0) == PLR_PRD_REC && 
            ROWS(tl) == 0                   &&
            COLS(tl) + *col < ctx->linlen    )
        {
          c = *col; r = *row;
          PTP_swap((StdCPtr*)(&ctx->lookahead),(StdCPtr*)(&it)); 
          PTP_swap((StdCPtr*)(&ctx->currtok),(StdCPtr*)(&ct)); 
          PTP_swap((StdCPtr*)(&ctx->nlflg),(StdCPtr*)(&nl));
          for( ts = XPT_parts(tree); ! empty(ts); ts = rst(ts))
            PTP_updpos(ctx,fst(PT_Term,ts),r,&c);
          PTP_swap((StdCPtr*)(&it),(StdCPtr*)(&ctx->lookahead)); 
          PTP_swap((StdCPtr*)(&ct),(StdCPtr*)(&ctx->currtok)); 
          ctx->nlflg = False;
        }
      }
      PT_updPos(tree,(symbol)tl,*row,*col);
      *row = r; *col = c;
      PT_delIT(it);
    }
  }
}

/* ------------------------- Pass 2: Pretty Printing ----------------------- */

static void PTP_pass3(PTP_T ctx, PT_Term tree, FILE* fp, long* row, long* col)
{
  if( tree != (PT_Term)NULL )
  {
    PT_updPos(tree,ctx->outfile,PT_row(tree),PT_col(tree));
    if( PT_isNonTerm(tree) )
    {
      if( ! PT_isXaron(tree) )
      { PT_Term ts;
        for( ts = PT_parts(tree); ts != (PT_Term)NULL; ts = PT_next(ts) )
        {
          PTP_pass3(ctx,ts,fp,row,col);
        }
      }
      else
      { List(PT_Term) ts; PT_Term t;
        for( ts = XPT_parts(tree); ! empty(ts); ts = rst(ts))
        { 
          t = fst(PT_Term,ts);
          PTP_pass3(ctx,t,fp,row,col);
        }
      }
    }
    else
    { wc_string ws = (wc_string)NULL;
      string    v  = symbolToString(PT_value(tree));
      size_t    l  = strlen(v), i;
      long      r  = PT_row(tree), 
                c  = PT_col(tree), 
                tr = *row, 
                tc = ( tr < r ) ? 0 : *col; 
      assert
      ( 
        r >= tr && c >= tc,
        "wrong positions: %ld >= %ld, %ld >= %ld",r,tr,c,tc
      );
      while( tr < r ) 
      { 
        if( ctx->utf8 && ctx->wprint )
          printf("%ld",WCHAR_LITERAL('\n'));
        else printf("\n");
        ++tr; 
      }
      while( tc < c ) 
      { 
        if( ctx->utf8 && ctx->wprint )
          printf("%ld",WCHAR_LITERAL(' '));
        else printf(" ");
        ++tc; 
      }
      tr = tc = 0;
      if( ctx->utf8 && ctx->wprint )
      {
        if( ( ws = GS_utf8_to_ucs4(v) ) != (wc_string)NULL )
        {
          l = WCStrLen(ws);
          for( i=0; i < l; ++i )
          {
            if( ws[i] == '\n' ) 
            { 
              printf("%ld",WCHAR_LITERAL('\n'));
              ++tr; tc = 0; 
            }
            else 
            if( ws[i] == WCHAR_LITERAL('\t') ) 
            { 
              fprintf
              (
                fp,"%ld%ld%ld%ld",
                WCHAR_LITERAL(' '), WCHAR_LITERAL(' '),
                WCHAR_LITERAL(' '), WCHAR_LITERAL(' ')
              );
              tc += PTP_TAB_LEN; 
            }
            else 
            { 
              printf("%ld",ws[i]); 
              ++tc; 
            }
          }
        }
      }
      else
      {
        for( i=0; i < l; ++i )
        {
          if( v[i] == '\n' ) 
          { 
            printf("\n"); ++tr; tc = 0; 
          }
          else 
          if( v[i] == '\t' ) 
          { 
            printf("    "); tc += PTP_TAB_LEN; 
          }
          else 
          { 
            if( !ctx->utf8 || 
                ( isascii(v[i]) && ( isprint(v[i]) || isspace(v[i]) ) ) )
              printf("%c",v[i]); 
            else
              printf("%02x",v[i]); 
            ++tc; 
          }
        }
      }
      *row = r + tr; *col = c + tc;
    }
  }
}

static void PTP_pp_aux(PTP_T ctx, PT_Term tree, FILE* fp)
{ long row = 0, col = 0;
  ctx->lookahead = PT_newIT(tree);
  PTP_setNextTok(ctx->lookahead);
  ctx->currtok   = (PT_Term)NULL;
  ctx->nlflg     = False;
  ctx->tosync    = True;
  PTP_pass1(ctx,tree,&row,&col,0);
  PT_delIT(ctx->lookahead);
/*XXX
fprintf(STDOUT,"LINELEN %d\n",linlen);
PT_prind(tree,0);
fprintf(STDOUT,"\n");
*/
  row = col = 0;
  PTP_pass3(ctx,tree,fp,&row,&col);
}

void PTP_pp(PT_Term tree, FILE* fp)
/* performs pretty printing on parse term 'tree' 
   ( output to file 'fp' )
*/
{ 
  PTP_pp_aux(pcurctx,tree,fp);
}

void PTP_pp_reentrant(PTP_T ctx, PT_Term tree, FILE* fp)
/* rrentrant version of PTP_pp */
{ 
  BUG_NULL(ctx);
  PTP_pp_aux(ctx,tree,fp);
}

/*I------------------------- Tree Transformation --------------------------- */

static PT_Term PTP_nt_transform(PTP_T ctx, PT_Term tree, symbol nt); /*forward*/

static List(PT_Term) XPTP_parts_transform
                     (
                       PTP_T ctx, List(PT_Term) parts, 
                       ROW(symbol) psrow, long idx, bool* ok
                     )
/* abstract src parts, dst members |--> concrete dst parts ( Xaron-Typ ) */
{ List(PT_Term) res; PT_Term t = (PT_Term)NULL, v = (PT_Term)NULL; 
  long cnt = OT_CNT(psrow), i;
  symbol psym; short ptyp;
  if( cnt > idx + 1 )
  { 
    psym = OT_GET(symbol,psrow,idx);
    ptyp = OT_GET_short(psrow,idx+1);
    if( CFG_KEY(ptyp) )
    {
      res = XPTP_parts_transform(ctx,parts,psrow,idx+2,ok);
      return (*ok)?XPT_consT(XPT_newTNode(psym,ptyp,psym),res):res;
    }
  }
  if( ! empty(parts) )
  { 
    t = fst(PT_Term,parts);
    if( PT_isKey(t) )
      return XPTP_parts_transform(ctx,rst(parts),psrow,idx,ok);
    else
    if( PT_isComment(t) )
    {
      res = XPTP_parts_transform(ctx,rst(parts),psrow,idx,ok);
      return (*ok)?XPT_consT(PT_copyNode(t),res):res;
    }
  }
  if( cnt > idx + 1 )
  { 
    psym = OT_GET(symbol,psrow,idx);
    ptyp = OT_GET_short(psrow,idx+1);
    if( CFG_TOK(ptyp) )
    {
      if( empty(parts) || ptyp != PT_symtyp(t) || PT_symbol(t) != psym )
      {
        *ok = False; return (List(PT_Term))NULL;
      }
      res = XPTP_parts_transform(ctx,rst(parts),psrow,idx+2,ok);
      if(*ok)
      {
        v = PT_copyNode(t);
        if( MAP_defined(ctx->cnvmap,psym) || MAP_defined(ctx->cnvmap,NULL) )
          PT_updVal
          (
            v,
            (*MAP_apply(symbol (*)(symbol,symbol),ctx->cnvmap,psym))
            (psym,PT_value(v))
          );
        return XPT_consT(v,res);
      }
      else return res;
    }
    else
    {
      assert0( CFG_NTM(ptyp), "" );
      if( empty(parts) || ptyp != PT_symtyp(t) )
      {
        *ok = False; return (List(PT_Term))NULL;
      }
      else
      { ROW(PT_Term) coms = OT_CREATE_ADT(PT_Term);
        t = PT_ignkey_Skip(t,coms);
        t = PTP_nt_transform(ctx,t,psym);
        if( t == (PT_Term)NULL )
        {
          *ok = False; OT_DEL_T(coms); return (List(PT_Term))NULL;
        }
        res = XPTP_parts_transform(ctx,rst(parts),psrow,idx+2,ok);
        if( ! (*ok) )
        {
          PT_delT(t); OT_DEL_T(coms); return res;
        }
        res = XPT_consT(t,res);
        for( i=OT_CNT(coms)-1; i >= 0; --i )
        {
          v = PT_copyNode(OT_GET(PT_Term,coms,i));
          if( MAP_defined(ctx->cnvmap,PT_symbol(v)) || 
              MAP_defined(ctx->cnvmap,NULL)          )
            PT_updVal
            (
              v,
              (*MAP_apply(symbol (*)(symbol,symbol),ctx->cnvmap,PT_symbol(v)))
              (PT_symbol(v),PT_value(v))
            );
          res = XPT_consT(v,res);
        }
        OT_DEL_T(coms);
        return res;
      }
    }
  }
  else
  {
    if( ! empty(parts) ) *ok = False;
    return (List(PT_Term))NULL;
  }
}

static PT_Term PTP_parts_transform
               (
                 PTP_T ctx, PT_Term parts, 
                 ROW(symbol) psrow, long idx, bool* ok
               )
/* abstract src parts, dst members |--> concrete dst parts */
{ PT_Term t, res; 
  long cnt = OT_CNT(psrow), i;
  symbol psym; short ptyp;
  if( cnt > idx + 1 )
  { 
    psym = OT_GET(symbol,psrow,idx);
    ptyp = OT_GET_short(psrow,idx+1);
    if( CFG_KEY(ptyp) )
    {
      res = PTP_parts_transform(ctx,parts,psrow,idx+2,ok);
      return (*ok)?PT_consT(PT_newTNode(psym,ptyp,psym),res):res;
    }
  }
  if( parts != (PT_Term)NULL )
  { 
    if( PT_isKey(parts) )
      return PTP_parts_transform(ctx,PT_next(parts),psrow,idx,ok);
    else
    if( PT_isComment(parts) )
    {
      res = PTP_parts_transform(ctx,PT_next(parts),psrow,idx,ok);
      return (*ok)?PT_consT(PT_copyNode(parts),res):res;
    }
  }
  if( cnt > idx + 1 )
  { 
    psym = OT_GET(symbol,psrow,idx);
    ptyp = OT_GET_short(psrow,idx+1);
    if( CFG_TOK(ptyp) )
    {
      if( parts == (PT_Term)NULL   || 
          ptyp != PT_symtyp(parts) || 
          PT_symbol(parts) != psym  )
      {
        *ok = False; return (PT_Term)NULL;
      }
      res = PTP_parts_transform(ctx,PT_next(parts),psrow,idx+2,ok);
      if(*ok)
      {
        t = PT_copyNode(parts);
        if( MAP_defined(ctx->cnvmap,psym) || MAP_defined(ctx->cnvmap,NULL) )
          PT_updVal
          (
            t,
            (*MAP_apply(symbol (*)(symbol,symbol),ctx->cnvmap,psym))
            (psym,PT_value(t))
          );
        return PT_consT(t,res);
      }
      else return res;
    }
    else
    {
      assert0( CFG_NTM(ptyp), "" );
      if( parts == (PT_Term)NULL || ptyp != PT_symtyp(parts) )
      {
        *ok = False; return (PT_Term)NULL;
      }
      else
      { ROW(PT_Term) coms = OT_CREATE_ADT(PT_Term);
        t = PT_ignkey_Skip(parts,coms);
        t = PTP_nt_transform(ctx,t,psym);
        if( t == (PT_Term)NULL )
        {
          *ok = False; OT_DEL_T(coms); return (PT_Term)NULL;
        }
        res = PTP_parts_transform(ctx,PT_next(parts),psrow,idx+2,ok);
        if( ! (*ok) )
        {
          PT_delT(t); OT_DEL_T(coms); return res;
        }
        res = PT_consT(t,res);
        for( i=OT_CNT(coms)-1; i >= 0; --i )
        {
          t = PT_copyNode(OT_GET(PT_Term,coms,i));
          if( MAP_defined(ctx->cnvmap,PT_symbol(t)) ||
              MAP_defined(ctx->cnvmap,NULL)          )
            PT_updVal
            (
              t,
              (*MAP_apply(symbol (*)(symbol,symbol),ctx->cnvmap,PT_symbol(t)))
              (PT_symbol(t),PT_value(t))
            );
          res = PT_consT(t,res);
        }
        OT_DEL_T(coms);
        return res;
      }
    }
  }
  else
  {
    if( parts != (PT_Term)NULL ) *ok = False;
    return (PT_Term)NULL;
  }
}

static void PTP_move_visited(MAP(symbol,_) dst, MAP(symbol,_) src)
{ HMP_Dom dom; HMP_Itr itr;
  MAP_rmvall(dst);
  MAP_forItr(dom,itr,src) MAP_dfndom(dst,dom,_);
  MAP_rmvall(src);
}

static PT_Term PTP_nt_transform(PTP_T ctx, PT_Term tree, symbol nt)
/* abstract src tree, dst nt |--> concrete dst tree */
{ 
  if (ctx->last_lin < PT_row(tree) || 
      (ctx->last_lin == PT_row(tree) && ctx->last_col < PT_col(tree)))
  {
    ctx->last_lin  = PT_row(tree);
    ctx->last_col  = PT_col(tree);
    ctx->last_nt   = nt;
    ctx->last_prod = PT_product(tree);
  }
  if( tree != (PT_Term)NULL )
  { ROW(ROW(symbol)) prow; symbol a_prod, c_prod; 
    long cnt, cnt2, i, j; bool xflg = PT_isXaron(tree);
    assert0( PT_isNonTerm(tree) && MAP_defined(ctx->ntmmap,nt), "" );
    a_prod = PT_product(tree); 
    prow   = MAP_apply(ROW(ROW(symbol)),ctx->ntmmap,nt);
    cnt    = OT_CNT(prow);
    for( i=0; i < cnt; ++i )
    { ROW(symbol) psrow = OT_GET(ROW(symbol),prow,i); 
      StdCPtr     parts = (StdCPtr)NULL; 
      assert0( ( cnt2 = OT_CNT(psrow) ) > 0, "" );
      c_prod = OT_GET(symbol,psrow,0);
      if( a_prod == c_prod )
      { MAP(symbol,_) l_visited = MAP_newMap(ctx->mtyp0);
        bool ok = True;
        PTP_move_visited(l_visited,ctx->visited);
        parts = xflg ? XPTP_parts_transform(ctx,XPT_parts(tree),psrow,1,&ok)
                     : PTP_parts_transform(ctx,PT_parts(tree),psrow,1,&ok);
        if( ok ) 
        {
          MAP_rmvall(ctx->visited); MAP_freeMap(l_visited);
          return xflg ? XPT_newNtNode(nt,c_prod,(List(PT_Term))parts)
                      : PT_newNtNode(nt,c_prod,(PT_Term)parts);
        }
        else
        {
          PTP_move_visited(ctx->visited,l_visited); MAP_freeMap(l_visited);
        }
      }
      else
      if( ignProd(symbolToString(c_prod)) ) 
      { 
        for( j=cnt2-2; j >= 1; j -= 2 ) 
        { symbol psym = OT_GET(symbol,psrow,j);
          short  ptyp = OT_GET_short(psrow,j+1);
          if( CFG_KEY(ptyp) )
            parts = xflg
              ? XPT_consT(XPT_newTNode(psym,ptyp,psym),(List(PT_Term))parts)
              : PT_consT(PT_newTNode(psym,ptyp,psym),(PT_Term)parts);
          else
          { PT_Term res, ts, tn;
            if( MAP_defined(ctx->visited,psym) ) res = (PT_Term)NULL;
            else
            {
              MAP_dfndom(ctx->visited,psym,_);
              res = PTP_nt_transform(ctx,tree,psym);
            }
            if( res != (PT_Term)NULL ) 
              parts = xflg ? XPT_consT(res,(List(PT_Term))parts)
                           : PT_consT(res,(PT_Term)parts);
            else
            {
              if( xflg ) freeList((List(PT_Term))parts,PT_delT); 
              else       
              { 
                for( ts = (PT_Term)parts; ts != (PT_Term)NULL; )
                {
                  tn = PT_next(ts); PT_delT(ts); ts = tn;
                }
              }
              j = cnt; break;
            }
          }
        }
        if( j < 1 ) 
        {
          return xflg ? XPT_newNtNode(nt,c_prod,(List(PT_Term))parts)
                      : PT_newNtNode(nt,c_prod,(PT_Term)parts);
        }
      }
    }
  }
  return (PT_Term)NULL;
}

PT_Term PTP_nt_transform_aux(PT_Term tree, symbol nt)
/* performs tree-to-tree transformation on source 'tree';
   uses 'nt' as startsymbol
*/
{ PT_Term res = PTP_nt_transform(pcurctx,tree,nt);
  if (res == (PT_Term)NULL)
    fprintf(stderr,"Transformation failed near (%d,%d) for goal '%s:%s:'\n",
            pcurctx->last_lin,pcurctx->last_col,
            symbolToString(pcurctx->last_nt),
            symbolToString(pcurctx->last_prod));
  return res;
}

PT_Term PTP_nt_transform_aux_reentrant
        (
          PTP_T ctx, PT_Term tree, symbol nt
        )
/* reentrant version of PTP_nt_transform_aux */
{ PT_Term res;
  BUG_NULL(ctx);
  res = PTP_nt_transform(ctx,tree,nt);
  if (res == (PT_Term)NULL)
    fprintf(stderr,"Transformation failed near (%d,%d) for goal '%s:%s:'\n",
            ctx->last_lin,ctx->last_col,
            symbolToString(ctx->last_nt),
            symbolToString(ctx->last_prod));
  return res;
}

PT_Term PTP_transform(PT_Term tree)
/* performs tree-to-tree transformation on source 'tree' */
{
  return PTP_nt_transform_aux(tree,pcurctx->language);
}

PT_Term PTP_transform_reentrant(PTP_T ctx, PT_Term tree)
/* reentrant version of PTP_transform */
{
  BUG_NULL(ctx);
  return PTP_nt_transform_aux_reentrant(ctx,tree,ctx->language);
}
