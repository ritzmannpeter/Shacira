/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [scn_base.c]           Basic Token Separation                            */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* TODO                                                                     */
/*                                                                          */
/* - Add a Scn_usageEof together with a character set size                  */
/* - cdefeof --> cdeftok                                                    */

#include "symbols.h"
#include "scn_io.h"

#include "scn_imp.h"
#include "pathes.h"
#include "sink.h"
#include "hmap.h"
#include "otab.h"
#include "gstream.h"

/*!
  <p>The module [scn_base] implements the scan stream interface based on a given
  STYX-konform scanner definition. ( see <a href="scn_gen.htm">[scn_gen]</a> )
  <p>The scan stream is reentrant and allows multiple scan operations at a time. 
  <br>
*/

/*I------------------------ Macros ---------------------------------------- */

/*!
  <p><b>Token definition flags</b> 
  ( see <a href="scn_gen.htm">Scn_dfnToken</a> )
*/

/*DOC_INTERFACE*/
#define SCN_FLG_IgnoreToken 1  /* token has to be ignored          */
#define SCN_FLG_IgnoreCase  2  /* case insensitive token           */
#define SCN_FLG_EofToken    4  /* eof token in embedded language   */
#define SCN_FLG_SwitchToken 8  /* switch to/from embedded language */
#define SCN_FLG_CfgToken    16 /* embedded language token          */
#define SCN_FLG_IndentToken 32 /* (de)indent token                 */

/*!
  <p><b>Token preprocessing result values</b>
*/

/*DOC_INTERFACE*/
#define SCN_FLG_RescanNone     0
#define SCN_FLG_RescanString   1
#define SCN_FLG_RescanBString  2
#define SCN_FLG_RescanFile     3
#define SCN_FLG_RescanBFile    4
#define SCN_FLG_RescanExtFile  5
#define SCN_FLG_RescanExtBFile 6
#define SCN_FLG_RescanChar     7
#define SCN_FLG_RescanChrItr   8
#define SCN_FLG_RescanBChrItr  9

/*I------------------------- Stream of tokens ----------------------------- */

#define MAX_TOK_LEN 10000

AbstractType( Scn_Stream );     /* Stream onto a scanner                 */

ExternalType( Scn_Stream_Itr )  /* Character iterator onto a scan stream */
{
  void     *cFile;                  /* open character stream object      */
  int      (*cGetc )(StdCPtr file); /* get next character                */
                                    /* set stream position               */
  LONG_INT (*fSeek )(StdCPtr file, long offset, int origin);
  void     (*cClose)(StdCPtr file); /* close stream object               */
  string   (*wc2mb )(wc_string wc); /* wide char to multibyte conversion */
                                    /* ( UCS4 --> UTF-8 )                */
  symbol   cFil;                    /* stream identifier                 */
};

/*!!
   Type of token preprocessing function
   RC = SCN_FLG_RescanChrItr   & valid cMacVal --> rescan character iterator cMacVal
                                                   ( frees character iterator )
   RC = SCN_FLG_RescanBChrItr  & valid cMacVal --> rescan binary char iterator cMacVal
                                                   ( frees character iterator )
   RC = SCN_FLG_RescanString   & valid cMacVal --> rescan string cMacVal
   RC = SCN_FLG_RescanBString  & valid cMacVal --> rescan binary string cMacVal
   RC = SCN_FLG_RescanBFile    & valid cMacVal --> rescan binary file cMacVal
   RC = SCN_FLG_RescanExtFile  & valid cMacVal --> rescan file cMacVal,
                                                   with main stream read function
   RC = SCN_FLG_RescanExtBFile & valid cMacVal --> rescan binary file cMacVal,
                                                   with main stream read function
   RC = SCN_FLG_RescanChar     & valid cMacVal --> rescan character cMacVal 
                                                   ( single byte or ucs4 )
   RC = SCN_FLG_RescanNone     & valid cMacVal --> replace cTokVal with cMacVal 
                                                   ( single byte or utf-8 )
   ELSE                                        --> ignore cTokVal
*/
/*DOC_INTERFACE*/
typedef int (*Scn_PreMacFun)
            (
              Scn_Stream pStream, string cTokNam, 
              string cTokVal, symbol* cMacVal
            );


/*!
   Type of the embedded language token constructor
*/
/*DOC_INTERFACE*/
typedef Any_T (*Scn_eTerm)
              (
                Abs_T CurPTCfg, c_string language, c_string StartSymbol
              );


/*!
   Type of the embedded language accept token recognizer
*/
/*DOC_INTERFACE*/
typedef c_bool (*Scn_eAccept)(Abs_T CurPTCfg);


ConcreteType( Scn_Stream_IMP )
{
  /* Character Iterator */
  void     *cFile;
  int       (*cGetc )(StdCPtr file);
  LONG_INT  (*fSeek )(StdCPtr file, long offset, int origin);
  void      (*cClose)(StdCPtr file);
  string    (*wc2mb )(wc_string wc); /* text mode only */
  /* Location Tracking */
  long       cCol,  nCol;
  long       cLin,  nLin;
  symbol     cFil;
  /* Symbol under construction */
  /* cC_eof = -1 ==> binary, default=0 (text) */
  int        cC, cC_sav, cC_eof;
  string     cBuf /*[cBufLen]*/;
  wc_string  cWBuf/*[cBufLen]*/;
  long       cLen,  cBufLen;
  MAP(int,_) cCSkip;   /* characters to skip */
  /* Scanner */
  scn_t      cScanner; /* Following variables are unpacked from cScanner */
  short      Group;    /* Group index or -1                              */
  long      *cStaEdg;  /* Note that this array will be offset in Scn_bgn */
  short     *cStaFin;
  wc_char   *cEdgeC;
  long      *cEdgeS;
  byte      *cFlags;
  MAP(short,scn_t) cDyckScanner; /* dyck scanner */
  /* token and symbol */
  short      cTok;
  symbol     cSym;
  symbol     cMacSym;
  /* (de)indent token */
  ROW(long)  cIndentStack;
  symbol     cIndentSym;
  symbol     cDedentSym;
  /* screener */
  short               cdefeof;   /* the tid for EOF                          */
  short              *cdeftok;   /* the tid for Token[i]                     */
  MAP(symbol,short)   cdefptok;  /* the tid for parser tokens                */
  MAP(symbol,short)   cdefkey;   /* the tid for keywords                     */
  MAPTY               keyty;     /* the typ of tid for keywords              */
  void (*nexttok)(Scn_Stream t); /* separate next token                      */
  Scn_PreMacFun       cPreMac;   /* macro pre-processing function            */
  ROW(Scn_Stream)     cStreams;  /* substreams for macro pre-processing      */
  Scn_eTerm           eTerm;     /* embedded language token constructor      */
  Scn_eAccept         eAccept;   /* emb. language accept token recognizer    */
  Abs_T               CurPTCfg;  /* current parse term configuration         */
  long                cOtherLen; /* other token length in buffer or -1       */
                                 /* ( text mode only )                       */
  short               cTok_sav;  /* first non other token ID                 */
                                 /* embedded language token ID               */
                                 /* embedded language follow token ID        */
  long                cCol_sav;  /* start column of 'cTok_sav'               */
  long                cLin_sav;  /* start line of 'cTok_sav'                 */
  string              cBuf_sav;  /* buffer for first non other token         */
  wc_string           cWBuf_sav; /* wide buffer for first non other token    */
  symbol              cSym_sav;  /* embedded language (follow) token         */
  ROW(Any_T)          cEmbeds;   /* embedded language stack(lin,col,sym,tok) */
  MAP(Any_T,Any_T)    ctxmap;    /* stream context: id |--> value            */
};


/* ------------------- Character Iteration & Collection ------------------- */
/*                                                                          */
/* The characters read in from the source iterator are collected to make up */
/* a string into the dynamically resized buffer 'cStr'. Since we double the */
/* size of the array whenever it becomes too small, the sum of all it's     */
/* sizes forms a geometric row. Thus we can guarantee, that the final size  */
/* of the buffer will be less than twice the size of the largest symbol and */
/* that the total amount of storage claimed and released during the         */
/* increasing operations will also be less than twice the size of the       */
/* largest symbol.                                                          */
/*                                                                          */
/* Additionally, we start with a buffer size larger than a standart line.   */
/* Thus, resizing becomes only nessesarry if scanning a text with tokens    */
/* longer than one line                                                     */
/*                                                                          */
/* ------------------------------------------------------------------------ */

static void Tok_new(Scn_Stream_IMP s)
/* initializes the character buffer */
{
  s->cBufLen = 128; /* Must be > 0. We choose it longer than a typical line. */
  s->cWBuf   = (wc_string)NULL;
  if( s->wc2mb == (string (*)(wc_string wc))NULL )
    s->cBuf  = (string) NewMem(s->cBufLen);
  else
    s->cWBuf = (wc_string) NewMem(sizeof(wc_char)*s->cBufLen);
}

static void Tok_free(Scn_Stream_IMP s)
/* frees the character buffer */
{
  if( s->cBuf != (string)NULL )
    FreeMem(s->cBuf);
  if( s->cWBuf != (wc_string)NULL )
    FreeMem(s->cWBuf);
}

static void TokOther_bgn(Scn_Stream_IMP s)
/* start to buffer next other token */
{
  s->cOtherLen = s->cLen; 
  s->cTok_sav  = s->cTok;
  s->cCol_sav  = s->nCol;
  s->cLin_sav  = s->nLin;
  s->cMacSym   = (symbol)NULL;
}

static void Tok_bgn(Scn_Stream_IMP s)
/* start to buffer a new token */
{
  s->cLen = 0; s->cCol = s->nCol; s->cLin = s->nLin;
  s->cMacSym = (symbol)NULL;
}

static void Tok_add(Scn_Stream_IMP s, int c)
/* buffer char c */
{ if (s->cLen >= s->cBufLen)
  /* The buffer must be resized */
  { 
    assert1
    (
      2 * s->cBufLen >= 0,"'%s': scanner buffer overflow",symbolToString(s->cFil)
    );
    if( s->wc2mb == (string (*)(wc_string wc))NULL )
    { int i; string nBuf = (string) NewMem(2 * s->cBufLen);
      for (i = 0; i < s->cLen; i++)
        nBuf[i] = s->cBuf[i];
      FreeMem(s->cBuf); s->cBuf = nBuf; s->cBufLen *= 2;
    }
    else
    { int i; wc_string nBuf = (wc_string) NewMem(sizeof(wc_char) * 2 * s->cBufLen);
      for (i = 0; i < s->cLen; i++)
        nBuf[i] = s->cWBuf[i];
      FreeMem(s->cWBuf); s->cWBuf = nBuf; s->cBufLen *= 2;
    }
  }
  if( s->wc2mb == (string (*)(wc_string wc))NULL )
    s->cBuf[s->cLen] = (byte)c; 
  else s->cWBuf[s->cLen] = (wc_char)c; 
  s->cLen += 1;
}

static void Tok_skip(Scn_Stream_IMP s)
/* skip current cC ==> track position, get next cC */
{
  while( MAP_defined(s->cCSkip,s->cC) )
  {
    if (s->cC == (( s->wc2mb == (string (*)(wc_string wc))NULL ) 
        ? (int)'\n' : WCHAR_LITERAL('\n')))
    { s->nLin += 1; s->nCol = 1; }
    else
    { s->nCol += 1; }
    s->cC = (*(s->cGetc))(s->cFile);
  }
}

static void Tok_get(Scn_Stream_IMP s)
/* buffer cC, track position, get next cC */
{
  Tok_add(s,s->cC);
  if (s->cC == (( s->wc2mb == (string (*)(wc_string wc))NULL ) 
      ? (int)'\n' : WCHAR_LITERAL('\n')))
  { s->nLin += 1; s->nCol = 1; }
  else
  { s->nCol += 1; }
  if( s->cC_sav >= 0 )
  {
    s->cC     = s->cC_sav;
    s->cC_sav = -1;
  }
  else 
  {
    s->cC = (*(s->cGetc))(s->cFile);
    if( s->cCSkip != (MAP(int,_))NULL )
      Tok_skip(s);
  }
}

/*I------------------- Accessing scanner definition ----------------------- */

string Scn_id(Scn_T scn)
/* name of the scanner (group) 'scn'; allocs memory 
*/
{
  return StrCopy(Scn_IMP(scn)->Name);
}

short Scn_check_Token(Scn_T scn, string s)
/* whether string 's' is a token in scanner 'scn';
   result = token number ( > 0 ) or 0
   assertion: Scn_groups(scn) = 0
*/
{ int state = 0, tok = -1, len = 0; scn_t si = Scn_IMP(scn); register wc_char *i;
  bug0(si->Groups == 0,"invalid scanner group");
  if (s[len] == 0) return 0;
  for (i = &si->EdgeC[si->StaEdg[state]]; *i++ > (wc_char)s[len]; );
  state = si->EdgeS[(i-(si->EdgeC))-1]-1;
  while (state >= 0)
  { len += 1; tok  = si->StaFin[state]; if (s[len] == 0) break;
    for (i = &si->EdgeC[si->StaEdg[state]]; *i++ > (wc_char)s[len]; );
    state = si->EdgeS[(i-(si->EdgeC))-1]-1;
  }
  return (s[len]!=0 || tok<= 0 || (si->Flags[tok]&SCN_FLG_IgnoreToken))? 0:tok;
}

short Scn_check_WCToken(Scn_T scn, wc_string s)
/* whether wide string 's' is a token in scanner 'scn';
   result = token number ( > 0 ) or 0
   assertion: Scn_groups(scn) = 0
*/
{ int state = 0, tok = -1, len = 0; scn_t si = Scn_IMP(scn); register wc_char *i;
  bug0(si->Groups == 0,"invalid scanner group");
  if (s[len] == 0) return 0;
  for (i = &si->EdgeC[si->StaEdg[state]]; *i++ > s[len]; );
  state = si->EdgeS[(i-(si->EdgeC))-1]-1;
  while (state >= 0)
  { len += 1; tok  = si->StaFin[state]; if (s[len] == 0) break;
    for (i = &si->EdgeC[si->StaEdg[state]]; *i++ > s[len]; );
    state = si->EdgeS[(i-(si->EdgeC))-1]-1;
  }
  return (s[len]!=0 || tok<= 0 || (si->Flags[tok]&SCN_FLG_IgnoreToken))? 0:tok;
}

int Scn_tokens(Scn_T scn)
/* number of tokens defined in scanner ( group ) 'scn' */
{
  return Scn_IMP(scn)->Tokens;
}

string Scn_tokid(Scn_T scn, int i)
/* name of the i-th token definied in scanner 'scn'; allocs memory 
   assertion: Scn_groups(scn) = 0
*/
{
  bug0
  (
    Scn_IMP(scn)->Groups == 0 && 
    0 <= i && i < Scn_IMP(scn)->Tokens,"invalid range"
  );
  return StrCopy(Scn_IMP(scn)->TokId[i]);
}

byte Scn_tokFlags(Scn_T scn, int i)
/* flags of the i-th token definied in scanner 'scn'
   assertion: Scn_groups(scn) = 0
*/
{
  bug0
  (
    Scn_IMP(scn)->Groups == 0 && 
    0 <= i && i < Scn_IMP(scn)->Tokens,"invalid range"
  );
  return Scn_IMP(scn)->Flags[i];
}

int Scn_dycks(Scn_T scn)
/* number of dyck token defined in scanner ( group ) 'scn' */
{
  return Scn_IMP(scn)->dyckcnt;
}

Scn_T Scn_dyck(Scn_T scn, int i)
/* i-th dyck scanner definied in scanner group 'scn'
   assertion: Scn_dycks(scn) > 0
*/
{
  bug0(0 <= i && i < Scn_IMP(scn)->dyckcnt,"invalid range");
  return Scn_IMP(scn)->dyckpat[i];
}

int Scn_dycktoken(Scn_T scn, int i)
/* i-th dyck token definied in scanner group 'scn'
   assertion: Scn_dycks(scn) > 0
*/
{
  bug0(0 <= i && i < Scn_IMP(scn)->dyckcnt,"invalid range");
  return Scn_IMP(scn)->dyckidx[i];
}

int Scn_groups(Scn_T scn)
/* number of groups defined in scanner ( group ) 'scn' */
{
  return Scn_IMP(scn)->Groups;
}

Scn_T Scn_group(Scn_T scn, int i)
/* i-th scanner definied in scanner group 'scn'
   assertion: Scn_groups(scn) > 0
*/
{
  bug0(0 <= i && i < Scn_IMP(scn)->Groups,"invalid range");
  return Scn_IMP(scn)->GrpScn[i];
}

int Scn_SwitchGroup(Scn_T scn, int i)
/* switch group of the i-th token definied in scanner group 'scn' or -1
   assertion: Scn_groups(scn) = 0
*/
{
  bug0
  (
    Scn_IMP(scn)->Groups == 0 && 
    0 <= i && i < Scn_IMP(scn)->Tokens,"invalid range"
  );
  return Scn_IMP(scn)->Switch[i];
}

long Scn_check_GroupToken(Scn_T scn, string s)
/* whether string 's' is a token in scanner group 'scn';
   result: high = group index , low = token number ( > 0 ) or 0
   assertion: Scn_groups(scn) > 0
*/
{ scn_t si = Scn_IMP(scn); long res = 0; int i;
  bug0(si->Groups > 0,"invalid scanner");
  for( i=0; i < si->Groups; ++i )
  { short tok = Scn_check_Token(si->GrpScn[i],s);
    if( tok > 0 )
    {
      res = SET_I32_VAL(i,tok); break;
    }
  }
  return res;
}

long Scn_check_GroupWCToken(Scn_T scn, wc_string s)
/* whether wide string 's' is a token in scanner group 'scn';
   result: high = group index , low = token number ( > 0 ) or 0
   assertion: Scn_groups(scn) > 0
*/
{ scn_t si = Scn_IMP(scn); long res = 0; int i;
  bug0(si->Groups > 0,"invalid scanner");
  for( i=0; i < si->Groups; ++i )
  { short tok = Scn_check_WCToken(si->GrpScn[i],s);
    if( tok > 0 )
    {
      res = SET_I32_VAL(i,tok); break;
    }
  }
  return res;
}

/*I------------------- Character iterator definition ---------------------- */

static Scn_Stream_Itr Stream_Itr_init
                      (
                        Scn_Stream_Itr itr,
                        int      f_getc (StdCPtr file), 
                        void     f_close(StdCPtr file),
                        string   f_wc2mb(wc_string wc),
                        LONG_INT f_seek (StdCPtr file, long offset, int origin),
                        StdCPtr  file,
                        string   fileid
                      )
/* initializes character iterator 'itr' 
   onto the open character source 'file'
   ( parameter --> see Stream_Itr_new )
*/
{ 
  assert0(itr != (Scn_Stream_Itr)NULL, "");
  itr->cFile  = file;
  itr->cGetc  = f_getc;
  itr->fSeek  = f_seek;
  itr->cClose = f_close;
  itr->wc2mb  = f_wc2mb;
  itr->cFil   = stringToSymbol(fileid);
  return itr;
}

Scn_Stream_Itr Stream_Itr_new
               (
                 int      f_getc (StdCPtr file), 
                 void     f_close(StdCPtr file),
                 string   f_wc2mb(wc_string wc),
                 LONG_INT f_seek (StdCPtr file, long offset, int origin),
                 StdCPtr  file,
                 string   fileid
               )
/* creates and initializes a character iterator 
   onto the open character source 'file' 
   'f_getc' : next character 
   'f_close': closes character source 
   'f_wc2mb': converts wide to multibyte character
   'f_seek' : positions character source 
   'fileid' : character source identifier
*/
{ Scn_Stream_Itr itr = New(Scn_Stream_Itr);
  return Stream_Itr_init(itr,f_getc,f_close,f_wc2mb,f_seek,file,fileid);
}

void Stream_Itr_free(Scn_Stream_Itr itr)
/* frees character iterator 'itr' */
{ 
  FreeMem(itr);
}

/*I------------------------ Scan stream definition ------------------------ */

/*forward*/
static Scn_Stream Stream_current(Scn_Stream t);
static void Stream_next_default(Scn_Stream t);
static void Stream_next_dedent(Scn_Stream t);


static void Stream_switch_group(Scn_Stream t, short g)
/* switch to scanner group 'g' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t),
                 x = (Scn_Stream_IMP)t;
  int            i;
  if( s->Group != g )
  {
    x->Group   = s->Group   = g;
    x->cStaEdg = s->cStaEdg = s->cScanner->GrpScn[g]->StaEdg;
    x->cStaFin = s->cStaFin = s->cScanner->GrpScn[g]->StaFin;
    x->cEdgeC  = s->cEdgeC  = s->cScanner->GrpScn[g]->EdgeC;
    x->cEdgeS  = s->cEdgeS  = s->cScanner->GrpScn[g]->EdgeS;
    x->cFlags  = s->cFlags  = s->cScanner->GrpScn[g]->Flags;
    MAP_rmvall(x->cDyckScanner);
    for( i=0; i < s->cScanner->GrpScn[g]->dyckcnt; ++i )
    {
      MAP_ovrdom
      (
        x->cDyckScanner,(long)s->cScanner->GrpScn[g]->dyckidx[i],
        s->cScanner->GrpScn[g]->dyckpat[i]
      );
    }
    if( MAP_defined(x->cdefptok,(symbol)NULL) )
      x->cdeftok[0] = MAP_apply_short(x->cdefptok,(symbol)NULL);
    else
      x->cdeftok[0] = 0;
    for (i = 1; i < s->cScanner->GrpScn[g]->Tokens; i++)
    { symbol sym = stringToSymbol(s->cScanner->GrpScn[g]->TokId[i]);
      if( MAP_defined(x->cdefptok,sym) )
        x->cdeftok[i] = MAP_apply_short(x->cdefptok,sym);
      else /* group tokens need to be externally defined !!! */
      if( MAP_defined(x->cdefptok,(symbol)NULL) )
        x->cdeftok[i] = MAP_apply_short(x->cdefptok,(symbol)NULL);
      else
        x->cdeftok[i] = i; /* ambiguous, you have to use token names */
    }
  }
}

Scn_Stream Stream_bgn(Scn_T scn, Scn_Stream_Itr itr)
/* creates and initializes a scan stream 
   onto scanner 'scn' and character iterator 'itr'
*/
{ Scn_Stream_IMP s = New(Scn_Stream_IMP);
  int            cnt = 0, i;
  s->cGetc        = itr->cGetc;
  s->fSeek        = itr->fSeek;
  s->cClose       = itr->cClose;
  s->wc2mb        = itr->wc2mb;
  s->cFile        = itr->cFile;
  s->cScanner     = Scn_IMP(scn);
  s->keyty        = 
    MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  s->cDyckScanner = MAP_newMap(s->keyty);
  if( s->cScanner->Groups > 0 )
  {
    s->Group    = 0;
    s->cStaEdg  = s->cScanner->GrpScn[0]->StaEdg;
    s->cStaFin  = s->cScanner->GrpScn[0]->StaFin;
    s->cEdgeC   = s->cScanner->GrpScn[0]->EdgeC;
    s->cEdgeS   = s->cScanner->GrpScn[0]->EdgeS;
    s->cFlags   = s->cScanner->GrpScn[0]->Flags;
    for( i=0; i < s->cScanner->GrpScn[0]->dyckcnt; ++i )
    {
      MAP_ovrdom
      (
        s->cDyckScanner,(long)s->cScanner->GrpScn[0]->dyckidx[i],
        s->cScanner->GrpScn[0]->dyckpat[i]
      );
    }
  }
  else 
  {
    s->Group    = -1;
    s->cStaEdg  = s->cScanner->StaEdg;
    s->cStaFin  = s->cScanner->StaFin;
    s->cEdgeC   = s->cScanner->EdgeC;
    s->cEdgeS   = s->cScanner->EdgeS;
    s->cFlags   = s->cScanner->Flags;
    for( i=0; i < s->cScanner->dyckcnt; ++i )
    {
      MAP_ovrdom
      (
        s->cDyckScanner,(long)s->cScanner->dyckidx[i], s->cScanner->dyckpat[i]
      );
    }
  }
  s->cC_eof   = 0; // default-eof-offset ( non-binary mode )
  s->cC_sav   = -1;
  s->cC       = (*(s->cGetc))(s->cFile);
  //s->cC       = MAX(0,s->cC);
  s->cCSkip   = (MAP(int,_))NULL;
  Tok_new(s);
  s->cFil     = itr->cFil;
  s->nLin     = 1;
  s->nCol     = 1;
  s->cTok     = 0;
  s->cdefeof  = -1;
  s->cdefkey  = MAP_newMap(s->keyty);
  if( s->cScanner->Groups > 0 )
  {
    s->cdefptok = MAP_newMap(s->keyty);
    for( i=0; i < s->cScanner->Groups; ++i )
      cnt = MAX(cnt,s->cScanner->GrpScn[i]->Tokens);
    s->cdeftok  = (short*)NewMem(sizeof(short)*cnt);
    for (i = 0; i < s->cScanner->GrpScn[s->Group]->Tokens; i++)
      s->cdeftok[i] = i;
  }
  else
  {
    s->cdeftok  = (short*)NewMem(sizeof(short)*s->cScanner->Tokens);
    for (i = 0; i < s->cScanner->Tokens; i++)
      s->cdeftok[i] = i;
    s->cdefptok = (MAP(symbol,short))NULL;
  }
  s->cPreMac      = (Scn_PreMacFun)NULL;
  s->cStreams     = (ROW(Scn_Stream))NULL;
  s->CurPTCfg     = (Abs_T)NULL;
  s->eTerm        = (Scn_eTerm)NULL;
  s->eAccept      = (Scn_eAccept)NULL;
  s->nexttok      = Stream_next_default;
  s->ctxmap       = MAP_newMap(s->keyty);
  s->cOtherLen    = s->cCol_sav = s->cLin_sav = -1;
  s->cTok_sav     = (short)-1;
  s->cBuf_sav     = (string)NULL;
  s->cWBuf_sav    = (wc_string)NULL;
  s->cSym         = (symbol)NULL;
  s->cSym_sav     = (symbol)NULL;
  s->cEmbeds      = (ROW(Any_T))NULL;
  s->cIndentStack = (ROW(int))NULL;
  s->cIndentSym   = (symbol)NULL;
  s->cDedentSym   = (symbol)NULL;
  return (Scn_Stream) s;
}

void Stream_close(Scn_Stream t)
/* closes character source i.e. file of scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  if( s->cClose != NULL ) (*s->cClose)(s->cFile);
}

void Stream_free(Scn_Stream t)
/* frees scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  Tok_free(s); FreeMem(s->cdeftok);
  if( s->cCSkip != (MAP(int,_))NULL ) 
    MAP_freeMap(s->cCSkip);
  if( s->cdefptok != (MAP(symbol,short))NULL ) 
    MAP_freeMap(s->cdefptok);
  MAP_freeMap(s->cdefkey);
  MAP_freeMap(s->ctxmap);
  MAP_freeMap(s->cDyckScanner);
  MAP_freeTyp(s->keyty);
  if( s->cStreams != (ROW(Scn_Stream))NULL )
  { long cnt = OT_CNT(s->cStreams), i;
    for( i=0; i < cnt; ++i )
    { Scn_Stream x = OT_GET(Scn_Stream,s->cStreams,i);
      Stream_close(x);
      Stream_free(x);
    }
    OT_DEL_T(s->cStreams);
  }
  if( s->cEmbeds != (ROW(Any_T))NULL )
    OT_DEL_T(s->cEmbeds);
  if( s->cIndentStack != (ROW(int))NULL )
    OT_DEL_T(s->cIndentStack);
  FreeMem(s);
}

void Stream_reset(Scn_Stream t)
/* re-initializes scan process in current scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  s->cC     = (*(s->cGetc))(s->cFile);
  //s->cC     = MAX(0,s->cC);
  s->cC_sav = -1;
  s->nLin   = 1;
  s->nCol   = 1;
  s->cTok   = 0;
}

void Stream_premac_set(Scn_Stream t, Scn_PreMacFun cPreMac)
/* adds 'cPreMac' to scan stream 't'
   for token preprocessing & macro expansion 
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  assert0(s->cPreMac == (Scn_PreMacFun)NULL,"preprocessor already defined");
  s->cPreMac  = cPreMac;
  s->cStreams = OT_CREATE_ADT(Scn_Stream);
}

void Stream_eterm_set
     (
       Scn_Stream t, Abs_T CurPTCfg, Scn_eTerm eTerm, Scn_eAccept eAccept
     )
/* adds 'eTerm', 'eAccept' and 'CurPTCfg' to scan stream 't' 
   for embedded language token construction
   ( deactivates other token concatenation )
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  s->CurPTCfg  = CurPTCfg;
  s->eTerm     = eTerm;
  s->eAccept   = eAccept;
  s->cOtherLen = -1;
}

void Stream_add_ctxval(Scn_Stream t, Any_T id, Any_T val)
/* adds the context pair 'id' |--> 'val' to scan stream 't';
   updates existing entries
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  MAP_ovrdom(s->ctxmap,id,val);
}

void Stream_concat_other(Scn_Stream t)
/* activates other token concatenation in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  /* non-binary mode and no embedded language token */
  if( s->cC_eof == 0 && s->eTerm == (Scn_eTerm)NULL )
    s->cOtherLen = 0;
}

void Stream_skip_character(Scn_Stream t, int cC)
/* skips character 'cC' ( but tracks position ) */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  assert1( cC > 0,"illegal skip character %ld",cC);
  if( s->cCSkip == (MAP(int,_))NULL )
    s->cCSkip = MAP_newMap(s->keyty);
  MAP_ovrdom(s->cCSkip,cC,NULL);
  Tok_skip(s);
}

/* ---------------------- Scan creation onto a file ----------------------- */

void Stream_binmode_set(Scn_Stream t)
/* activates binary mode in scan stream 't' 
   ( deactivates other token concatenation )
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  assert0
  (
    s->wc2mb == (string (*)(wc_string wc))NULL,
    "binary and unicode mode not allowed"
  );
  s->cC_eof = -1;
  //s->cOtherLen = 0;
  s->cOtherLen = -1;
}

static LONG_INT scn_file_fseek(StdCPtr file, long offset, int origin)
/* fseek and ftell on a scan stream or file */
{
  if( file != (StdCPtr)NULL )
  { LONG_INT npos = -1, rc;
    rc = fseek((FILE*)file,offset,origin);
    if( rc == 0 )
    {
      npos = ftell((FILE*)file);
      if( npos >= 0 ) 
      {
        return npos;
      }
    }
  }
  return -1;
}

Scn_Stream Stream_line
           (
             Scn_T scn, StdCPtr line, int (*cGet)(StdCPtr line), string id
           )
#define STREAM_STDIN(scn) \
	Stream_line(scn,stdin,(int (*)(StdCPtr f))fgetc,"<stdin>")
/* creates a scan stream 
   onto scanner 'scn' and character stream 'line' 
   'cGet': next character
   'id'  : character stream identifier
*/
{ ConcreteImp(Scn_Stream_Itr) itr;
  Scn_Stream                  res;
  Stream_Itr_init
  (
    &itr,
    (int    (*)(StdCPtr))  cGet,
    (void   (*)(StdCPtr))  NULL,
    (string (*)(wc_string))NULL,
    scn_file_fseek,
    line,
    id
  );
  res = Stream_bgn(scn,&itr);
  return res;
}

Scn_Stream Stream_file(Scn_T scn, string EnvVar, string FileName, string Ext)
/* creates a scan stream 
   onto scanner 'scn' and file [$'EnvVar'/]'FileName''Ext' 
*/
{ ConcreteImp(Scn_Stream_Itr) itr;
  string                      fil = MkPath(EnvVar,FileName,Ext,'p');
  FILE*                       f   = OpnFile(fil,"rb");
  Scn_Stream                  res;
  Stream_Itr_init
  (
    &itr,
    (int    (*)(StdCPtr))  fgetc,
    (void   (*)(StdCPtr))  fclose,
    (string (*)(wc_string))NULL,
    scn_file_fseek,
    f,
    fil
  );
  res = Stream_bgn(scn,&itr);
  FreeMem(fil);
  return res;
}

Scn_Stream Stream_extfile
           (
             Scn_T scn, string EnvVar, string FileName, string Ext,
             int (*cGet)(FILE* f)
           )
/* creates a scan stream 
   onto scanner 'scn' and file [$'EnvVar'/]'FileName''Ext' 
   with external next character function 'cGet'
*/
{ ConcreteImp(Scn_Stream_Itr) itr;
  string                      fil = MkPath(EnvVar,FileName,Ext,'p');
  FILE*                       f   = OpnFile(fil,"rb");
  Scn_Stream                  res;
  Stream_Itr_init
  (
    &itr,
    (int    (*)(StdCPtr))  cGet,
    (void   (*)(StdCPtr))  fclose,
    (string (*)(wc_string))NULL,
    scn_file_fseek,
    f,
    fil
  );
  res = Stream_bgn(scn,&itr);
  FreeMem(fil);
  return res;
}

/* --------------------- Scan creation onto a byte array ------------------ */

ConcreteType( scn_buffer )
{
  byte*    buffer;
  LONG_INT len;
  LONG_INT cpos;
};

static LONG_INT scn_buffer_fseek(scn_buffer t, long offset, int origin)
/* fseek routine for byte array scanning 
   ( position may vary between 0 and EOB ) 
*/
{ LONG_INT npos = -1;
  switch(origin)
  { 
    case SEEK_SET:
      npos = offset;
      break;
    case SEEK_END:
      npos = t->len + offset;
      break;
    case SEEK_CUR:
      npos = t->cpos + offset;
      break;
    default:
      npos = -1;
      break;
  }
  if( npos >= 0 && npos <= t->len )
  {
    t->cpos = npos;
    return npos;
  }
  else return -1;
}

static int scn_buffer_getc(scn_buffer t)
/* getc routine for buffer scanning */
{
  if( t->cpos >= t->len )
    return -1;
  else
    return (t->buffer[t->cpos++])&0xff;
}

static void scn_buffer_close(scn_buffer t)
/* close routine for buffer scanning */
{
  FreeMem(t->buffer); FreeMem(t);
}

Scn_Stream Stream_bstring(Scn_T scn, c_bstring bstr)
/* creates a scan stream onto scanner 'scn' and binary string 'bstr' */
{ ConcreteImp(Scn_Stream_Itr) itr;
  scn_buffer                  t;
  Scn_Stream                  res;
  t = New(scn_buffer);
  memcpy(&t->len,bstr,sizeof(long));
  t->buffer = BytCopy(bstr+sizeof(long),t->len);
  t->cpos = 0;
  Stream_Itr_init
  (
    &itr,
    (int      (*)(StdCPtr))          scn_buffer_getc,
    (void     (*)(StdCPtr))          scn_buffer_close,
    (string   (*)(wc_string))        NULL,
    (LONG_INT (*)(StdCPtr,long,int)) scn_buffer_fseek,
    t,
    "<BString>"
  );
  res = Stream_bgn(scn,&itr);
  ((Scn_Stream_IMP)res)->cC_eof = -1;
  return res;
}

void Stream_bstring_set(Scn_Stream stream, c_bstring bstr)
/* re-initializes scan stream 'stream' with binary string 'bstr' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)stream;
  scn_buffer     t = (scn_buffer)(s->cFile);
  FreeMem(t->buffer);
  memcpy(&t->len,bstr,sizeof(long));
  t->buffer = BytCopy(bstr+sizeof(long),t->len);
  t->cpos   = 0;
  s->cC     = (*(s->cGetc))(s->cFile);
  s->cC_sav = -1;
  s->nLin   = 1;
  s->nCol   = 1;
  s->cTok   = 0;
}

/* --------------------- Scan creation onto a string ---------------------- */

ConcreteType( scn_text )
{
  string   text;
  LONG_INT cpos;
};

static LONG_INT scn_text_fseek(scn_text t, long offset, int origin)
/* fseek routine for string scanning ( position may vary between 0 and EOS ) */
{ LONG_INT npos = -1,
           len  = strlen(t->text);
  switch(origin)
  { 
    case SEEK_SET:
      npos = offset;
      break;
    case SEEK_END:
      npos = len + offset;
      break;
    case SEEK_CUR:
      npos = t->cpos + offset;
      break;
    default:
      npos = -1;
      break;
  }
  if( npos >= 0 && npos <= len )
  {
    t->cpos = npos;
    return npos;
  }
  else return -1;
}

static int scn_text_getc(scn_text t)
/* getc routine for string scanning */
{
  return (t->text[t->cpos++])&0xff;
}

static void scn_text_close(scn_text t)
/* close routine for string scanning */
{
  FreeMem(t->text); FreeMem(t);
}

Scn_Stream Stream_string(Scn_T scn, string Text)
/* creates a scan stream onto scanner 'scn' and string 'Text' */
{ ConcreteImp(Scn_Stream_Itr) itr;
  scn_text                    t;
  Scn_Stream                  res;
  t = New(scn_text);
  t->text = StrCopy(Text);
  t->cpos = 0;
  Stream_Itr_init
  (
    &itr,
    (int      (*)(StdCPtr))          scn_text_getc,
    (void     (*)(StdCPtr))          scn_text_close,
    (string   (*)(wc_string))        NULL,
    (LONG_INT (*)(StdCPtr,long,int)) scn_text_fseek,
    t,
    "<String>"
  );
  res = Stream_bgn(scn,&itr);
  return res;
}

void Stream_string_set(Scn_Stream stream, string Text)
/* re-initializes scan stream 'stream' with string 'Text' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)stream;
  scn_text       t = (scn_text)(s->cFile);
  FreeMem(t->text);
  t->text   = StrCopy(Text);
  t->cpos   = 0;
  s->cC     = (*(s->cGetc))(s->cFile);
  //s->cC     = MAX(0,s->cC);
  s->cC_sav = -1;
  s->nLin   = 1;
  s->nCol   = 1;
  s->cTok   = 0;
}

void Stream_string_insert(Scn_Stream stream, string Text)
/* inserts string 'Text' at current position in scan stream 'stream' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)stream;
  scn_text       t = (scn_text)(s->cFile);
  string         x = (string)NewMem(strlen(t->text)+strlen(Text)+1);
  strncpy(x,t->text,t->cpos);
  strcat(x,Text);
  strcat(x,t->text+t->cpos);
  FreeMem(t->text);
  t->text = x;
}

/*I------------------------ Defining token numbers ------------------------ */

static Scn_Stream Stream_current(Scn_Stream t); /*forward*/

void Stream_defEofId(Scn_Stream t, short tid)
/* defines 'tid' as EOF token number in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  s->cdefeof = tid;
}

void Stream_defErrId(Scn_Stream t, short tid)
/* defines 'tid' as error token number in scan stream 't' */
{ int i; Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  if( s->cScanner->Groups == 0 )
  {
    for (i=0; i < s->cScanner->Tokens; i++)
      s->cdeftok[i] = tid;
  }
  else
  {
    for (i=0; i < s->cScanner->GrpScn[s->Group]->Tokens; i++)
      s->cdeftok[i] = tid;
    MAP_ovrdom(s->cdefptok,(symbol)NULL,(long)tid);
  }
}

void Stream_defTokId(Scn_Stream t, string Name, short tid)
/* defines 'tid' as number for token 'Name' in scan stream 't' */
{ int cnt, i, j; Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  if( s->cScanner->Groups == 0 )
  {
    for (i = 1; i < s->cScanner->Tokens; i++)
      if (!strcmp(Name,s->cScanner->TokId[i]))
      {
        s->cdeftok[i] = tid;
        return;
      }
  }
  else
  { Scn_Stream_IMP x = (Scn_Stream_IMP)Stream_current(t);
    if( x->cEmbeds == (ROW(Any_T))NULL || x->Group < 0 )
    {
      i = 0; cnt = s->cScanner->Groups;
    }
    else
    {
      i = x->Group; cnt = x->Group + 1;
    }
    for ( ; i < cnt; i++)
      for (j = 1; j < s->cScanner->GrpScn[i]->Tokens; j++)
        if (!strcmp(Name,s->cScanner->GrpScn[i]->TokId[j]))
        {
          MAP_ovrdom(s->cdefptok,stringToSymbol(Name),(long)tid);
          if( s->Group == i ) s->cdeftok[j] = tid;
          return;
        }
  }
  bug2(False,"\'Scn_defTokId(\"%s\",%d)\': Token not seen",Name,tid);
}

static void setIndTokKey(Scn_Stream t, symbol keysym)
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  long           klen, dlen, ilen;
  if( s->cIndentSym == (symbol)NULL && s->cDedentSym == (symbol)NULL )
    s->cDedentSym = keysym;
  else
  if( keysym != s->cDedentSym && keysym != s->cIndentSym )
  {
    if( s->cIndentSym == (symbol)NULL )
    {
      if( keysym != s->cDedentSym )
      {
        klen = strlen(symbolToString(keysym));
        dlen = strlen(symbolToString(s->cDedentSym));
        if( klen < dlen )
        {
          s->cIndentSym = s->cDedentSym;
          s->cDedentSym = keysym;
        }
        else
        {
          s->cIndentSym = keysym;
        }
        s->cIndentStack = OT_CREATE_ADT(long);
        OT_PUSH(0,s->cIndentStack);
      }
    }
    else
    {
      assert0
      (
        s->cIndentSym != (symbol)NULL && s->cDedentSym != (symbol)NULL,""
      );
      klen = strlen(symbolToString(keysym));
      dlen = strlen(symbolToString(s->cDedentSym));
      ilen = strlen(symbolToString(s->cIndentSym));
      if( klen < dlen )
      {
        s->cIndentSym = s->cDedentSym;
        s->cDedentSym = keysym;
      }
      else
      if( klen < ilen )
      {
        s->cIndentSym = keysym;
      }
    }
  }
}

void Stream_defKeyId(Scn_Stream t, string Text, short tid)
/* defines 'tid' as number for keyword 'Text' in scan stream 't' */
{ Scn_Stream_IMP s      = (Scn_Stream_IMP)t;
  string         normal = StrCopy(Text);
  symbol         keysym;
  int            tok    = 0, cnt, i;
  if( s->cScanner->Groups == 0 )
  {
    tok = Scn_check_Token(s->cScanner,Text);
    bug2(tok,"Scn_defKeyId(\"%s\",%d): not a token",Text,tid);
    if (s->cFlags[tok]&SCN_FLG_IgnoreCase) StrToLower(normal);
    keysym = stringToSymbol(normal);
    MAP_dfndom(s->cdefkey,keysym,(long)tid);
    if (s->cFlags[tok]&SCN_FLG_IndentToken)
    {
      setIndTokKey(t,keysym);
    }
  }
  else
  { Scn_Stream_IMP x = (Scn_Stream_IMP)Stream_current(t);
    if( x->cEmbeds == (ROW(Any_T))NULL || x->Group < 0 )
    {
      i = 0; cnt = s->cScanner->Groups;
    }
    else
    {
      i = x->Group; cnt = x->Group + 1;
    }
    for ( ; i < cnt; i++)
    {
      tok = Scn_check_Token(s->cScanner->GrpScn[i],Text);
      if( tok > 0 )
      {
        if (s->cScanner->GrpScn[i]->Flags[tok]&SCN_FLG_IgnoreCase) 
          StrToLower(normal);
        keysym = stringToSymbol(normal);
        MAP_ovrdom(s->cdefkey,keysym,(long)tid);
        if (s->cScanner->GrpScn[i]->Flags[tok]&SCN_FLG_IndentToken) 
          setIndTokKey(t,keysym);
        break;
      }
    }
    bug2(tok,"Scn_defKeyId(\"%s\",%d): not a token",Text,tid);
  }
  FreeMem(normal);
}

void Stream_defWCKeyId(Scn_Stream t, wc_string Text, short tid)
/* defines 'tid' as number for wide keyword 'Text' in scan stream 't' */
{ Scn_Stream_IMP s        = (Scn_Stream_IMP)t;
  wc_string      normal   = WCStrCopy(Text);
  string         mbnormal = (string)NULL;
  symbol         keysym;
  int            tok      = 0, cnt, i;
  assert0
  ( 
    s->wc2mb != (string (*)(wc_string wc))NULL, 
    "missing wide-to-multibyte character conversion function"
  );
  if( s->cScanner->Groups == 0 )
  {
    tok = Scn_check_WCToken(s->cScanner,Text);
    if( tok > 0 )
    {
      if (s->cFlags[tok]&SCN_FLG_IgnoreCase) WCStrToLower(normal);
      bug0((mbnormal = (*s->wc2mb)(normal))!=(string)NULL,"");
      keysym = stringToSymbol(mbnormal);
      MAP_dfndom(s->cdefkey,keysym,(long)tid);
      if (s->cFlags[tok]&SCN_FLG_IndentToken)
        setIndTokKey(t,keysym);
    }
  }
  else
  { Scn_Stream_IMP x = (Scn_Stream_IMP)Stream_current(t);
    if( x->cEmbeds == (ROW(Any_T))NULL || x->Group < 0 )
    {
      i = 0; cnt = s->cScanner->Groups;
    }
    else
    {
      i = x->Group; cnt = x->Group + 1;
    }
    for ( ; i < cnt; i++)
    {
      tok = Scn_check_WCToken(s->cScanner->GrpScn[i],Text);
      if( tok > 0 )
      {
        if (s->cScanner->GrpScn[i]->Flags[tok]&SCN_FLG_IgnoreCase) 
          WCStrToLower(normal);
        bug0((mbnormal = (*s->wc2mb)(normal))!=(string)NULL,"");
        keysym = stringToSymbol(mbnormal);
        MAP_ovrdom(s->cdefkey,keysym,(long)tid);
        if (s->cScanner->GrpScn[i]->Flags[tok]&SCN_FLG_IndentToken) 
          setIndTokKey(t,keysym);
      }
    }
  }
  if( !tok )
  { symbol mbkey = (symbol)NULL;
    mbnormal = (*s->wc2mb)(Text);
    if( mbnormal != (string)NULL ) 
      mbkey = stringToSymbol(mbnormal);
    else
      mbkey = stringToSymbol("");
    bug2
    (
      False,"Scn_defKeyId(\"%s\",%d): not a token",symbolToString(mbkey),tid
    );
  }
  FreeMem(normal); FreeMem(mbnormal);
}

/*I------------------------ Scan stream operations ------------------------ */

static void Stream_next_eterm(Scn_Stream t); /*forward*/

static Scn_Stream Stream_current(Scn_Stream t)
/* current expansion stream */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  return ( s->cStreams != (ROW(Scn_Stream))NULL && OT_CNT(s->cStreams) > 0 )
         ? OT_TOP(Scn_Stream,s->cStreams)
         : t;
}

static symbol tokenToSymbol(Scn_Stream_IMP s)
/* convert (wide) token buffer to symbol */
{ symbol toksym;
  if( s->wc2mb == (string (*)(wc_string wc))NULL )
  {
    if( s->cC_eof == 0 ) /* text mode */
      return stringToSymbol(s->cBuf);
    else /* binary mode */
    { c_bstring bstr = BytToBStrCopy(s->cBuf,s->cLen);
      toksym = bstringToSymbol(bstr);
      FreeMem(bstr);
      return toksym;
    }
  }
  else /* wide character mode */
  { string mbs;
    /* conversion, if necessary */
    bug0((mbs = (*s->wc2mb)(s->cWBuf))!=(string)NULL,"");
    toksym = stringToSymbol(mbs);
    FreeMem(mbs);
    return toksym;
  }
}

static void Tok_premac(Scn_Stream_IMP t)
/* preprocess token, handle expansion & pass token in buffer to symbol table */
{ Scn_Stream_IMP s   = (Scn_Stream_IMP)Stream_current(t);
  scn_t          scn = ( t->cScanner->Groups == 0 )
                       ? t->cScanner : t->cScanner->GrpScn[t->Group];
  symbol         txt = (symbol)NULL;
  int            rescan;
  if( s->wc2mb == (string (*)(wc_string wc))NULL )
    rescan = (*t->cPreMac)(t,scn->TokId[s->cTok],s->cBuf,&txt);
  else
  {
    bug0((s->cBuf = (*s->wc2mb)(s->cWBuf))!=(string)NULL,"");
    rescan  = (*t->cPreMac)(t,scn->TokId[s->cTok],s->cBuf,&txt);
    FreeMem(s->cBuf); s->cBuf = (string)NULL;
  }
  if( rescan == SCN_FLG_RescanChar )
  {
    s->cC_sav = s->cC;
    s->cC     = intCAST(txt);
    (*t->nexttok)(t);
  }
  else
  if( txt != (symbol)NULL ) 
  { 
    if( rescan != SCN_FLG_RescanNone )
    { Scn_Stream_IMP x   = (Scn_Stream_IMP)NULL;
      string         fid = symbolToString(s->cFil), 
                     f   = (string)NULL;
      if( rescan == SCN_FLG_RescanString )
      { 
        x = (Scn_Stream_IMP)Stream_string(t->cScanner,symbolToString(txt));
        if( s->cC_eof == 0 )
        {
          f = (string)NewMem(strlen(fid)+strlen(s->cBuf)+80+1);
          sprintf(f,"%s(%ld,%ld)#%s", fid,s->cLin,s->cCol,s->cBuf);
        }
        else
        { c_string hstr = BytToHStrCopy(s->cBuf,s->cLen);
          f = (string)NewMem(strlen(fid)+strlen(hstr)+80+1);
          sprintf(f,"%s(%ld,%ld)#%s", fid,s->cLin,s->cCol,hstr);
          FreeMem(hstr);
        }
      }
      else
      if( rescan == SCN_FLG_RescanBString )
      { 
        x = (Scn_Stream_IMP)Stream_bstring(t->cScanner,symbolToBString(txt));
        if( s->cC_eof == 0 )
        {
          f = (string)NewMem(strlen(fid)+strlen(s->cBuf)+80+1);
          sprintf(f,"%s(%ld,%ld)#%s", fid,s->cLin,s->cCol,s->cBuf);
        }
        else
        { c_string hstr = BytToHStrCopy(s->cBuf,s->cLen);
          f = (string)NewMem(strlen(fid)+strlen(hstr)+80+1);
          sprintf(f,"%s(%ld,%ld)#%s", fid,s->cLin,s->cCol,hstr);
          FreeMem(hstr);
        }
      }
      else
      if( rescan == SCN_FLG_RescanFile || rescan == SCN_FLG_RescanBFile  )
      {  
        x = (Scn_Stream_IMP)Stream_file(t->cScanner,"",symbolToString(txt),"");
        if( rescan == SCN_FLG_RescanBFile ) x->cC_eof = -1;
        f = (string)NewMem(strlen(fid)+strlen(symbolToString(x->cFil))+80+1);
        sprintf
        (
          f,"%s(%ld,%ld)#%s",fid,
          s->cLin,s->cCol,symbolToString(x->cFil)
        );
      }
      else
      if( rescan == SCN_FLG_RescanExtFile || rescan == SCN_FLG_RescanExtBFile )
      { 
        x = (Scn_Stream_IMP)
            Stream_extfile
            (
              t->cScanner,"",symbolToString(txt),"",(int (*)(FILE* f))t->cGetc
            );
        if( rescan == SCN_FLG_RescanExtBFile ) x->cC_eof = -1;
        f = (string)NewMem(strlen(fid)+strlen(symbolToString(x->cFil))+80+1);
        sprintf
        (
          f,"%s(%ld,%ld)#%s",fid,
          s->cLin,s->cCol,symbolToString(x->cFil)
        );
      }
      else
      if( rescan == SCN_FLG_RescanChrItr || rescan == SCN_FLG_RescanBChrItr )
      { 
        x = (Scn_Stream_IMP)Stream_bgn(t->cScanner,(Scn_Stream_Itr)txt);
        if( rescan == SCN_FLG_RescanBChrItr ) 
        {
          assert0
          (
            x->wc2mb == (string (*)(wc_string wc))NULL,
            "binary and unicode mode not allowed"
          );
          x->cC_eof = -1;
        }
        f = (string)NewMem(strlen(fid)+strlen(symbolToString(x->cFil))+80+1);
        sprintf
        (
          f,"%s(%ld,%ld)#%s",fid,
          s->cLin,s->cCol,symbolToString(x->cFil)
        );
        Stream_Itr_free((Scn_Stream_Itr)txt);
      }
      else C_BUG;
      x->cFil = stringToSymbol(f);
      if( x->cC_eof == 0 && s->cOtherLen >= 0 ) 
        x->cOtherLen = 0;
      FreeMem(f);
      OT_PUSH(x,t->cStreams);
      if( t->cScanner->Groups > 0 ) // set current group context
        Stream_switch_group(t,t->Group);
      (*t->nexttok)(t);
    }
    else /* replace token value */
    {
      s->cMacSym = txt;
      s->cSym    = tokenToSymbol(s);
    }
  }
  else /* ignore token */
    (*t->nexttok)(t); 
}

static void TokOther_end(Scn_Stream_IMP t)
/* pass other token in buffer to symbol table */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  short          tmp;
  if( s->wc2mb == (string (*)(wc_string wc))NULL )
  {
    s->cBuf_sav = StrCopy(s->cBuf+s->cOtherLen);
    *(s->cBuf+s->cOtherLen) = '\0';
    s->cSym = stringToSymbol(s->cBuf);
  }
  else
  {
    s->cWBuf_sav = WCStrCopy(s->cWBuf+s->cOtherLen);
    *(s->cBuf+s->cOtherLen) = WCHAR_LITERAL('\0');
    s->cSym = tokenToSymbol(s);
  }
  tmp = s->cTok; s->cTok = s->cTok_sav; s->cTok_sav = tmp;
  s->cOtherLen = 0;
}

/*20030209*/
static void Tok_eterm_end(Scn_Stream_IMP t)
/* pass token in buffer to symbol table */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  if( s->cC_eof == 0 && s->wc2mb == (string (*)(wc_string wc))NULL )
  { /* text mode */
    s->cLen = 0; Tok_add(s,(int)'\0');
  }
  else
  if( s->wc2mb != (string (*)(wc_string wc))NULL )
  { /* wide character mode */
    s->cLen = 0; Tok_add(s,WCHAR_LITERAL('\0'));
  }
  s->cMacSym = (symbol)NULL;
}

static void Tok_end(Scn_Stream_IMP t)
/* pass token in buffer to symbol table */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  if( s->cC_eof == 0 && s->wc2mb == (string (*)(wc_string wc))NULL )
  { /* text mode */
    Tok_add(s,(int)'\0');
    if (s->cTok >= 0 && (s->cFlags[s->cTok]&SCN_FLG_IgnoreCase)) 
      StrToLower(s->cBuf);
  }
  else
  if( s->wc2mb != (string (*)(wc_string wc))NULL )
  { /* wide character mode */
    Tok_add(s,WCHAR_LITERAL('\0'));
    if (s->cTok >= 0 && (s->cFlags[s->cTok]&SCN_FLG_IgnoreCase)) 
      WCStrToLower(s->cWBuf);
  }
  /* process (de)indent token */
  if ( s->cTok > 0 && 
      (s->cFlags[s->cTok]&SCN_FLG_IndentToken) &&
      t->cIndentStack != (ROW(long))NULL )
  { long top_indval, cur_indval;
    s->cSym    = tokenToSymbol(s);
    top_indval = OT_TOP(long,t->cIndentStack);
    cur_indval = strlen(symbolToString(s->cSym)) - 
                 strlen(symbolToString(s->cDedentSym));
    if( cur_indval > top_indval )
    {
      OT_PUSH(cur_indval, t->cIndentStack);
      s->cMacSym = t->cIndentSym;
    }
    else
    if( cur_indval < top_indval )
    {
      OT_POP(t->cIndentStack);
      s->cMacSym = t->cDedentSym;
      if( cur_indval < OT_TOP(long,t->cIndentStack) )
      {
        t->nexttok = Stream_next_dedent;
      }
    }
    else /* has to be ignored later */
    {
      s->cMacSym = (symbol)NULL;
    }
  }
  else /* pre-process macro */
  if (s->cTok != 0) /* no Error */
  { 
    if( s->cOtherLen > 0 ) /* concatenated other token */
      TokOther_end(t);
    else
    if (s->cTok == -1) /* EOF */
    { 
      if( s == t ) /* EOF Top Level */
        s->cSym = tokenToSymbol(s);
      else /* EOF Sub Level */
      { 
        Stream_close(s);
        Stream_free(s);
        OT_POP(t->cStreams);
        (*t->nexttok)(t);
      } 
    }
    else /* Keyword or Token */
    {
      if( t->cPreMac != (Scn_PreMacFun)NULL ) 
        Tok_premac(t); /* preprocess token */
      else s->cSym = tokenToSymbol(s);
    }
  }
  else 
  {
    if( s->cOtherLen <= 0 ) 
      s->cSym = tokenToSymbol(s);
    else /* concatenated other token */
      TokOther_end(t);
  }
}

static void StreamOther_next(Scn_Stream t)
/* Restore first non other token. */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  if( s->wc2mb == (string (*)(wc_string wc))NULL )
  {
    strcpy(s->cBuf,s->cBuf_sav);
    FreeMem(s->cBuf_sav); s->cBuf_sav = (string)NULL;
    s->cLen = strlen(s->cBuf);
  }
  else
  { size_t len = WCStrLen(s->cWBuf_sav);
    memcpy(s->cWBuf,s->cWBuf_sav,len+1);
    FreeMem(s->cWBuf_sav); s->cWBuf_sav = (wc_string)NULL;
    s->cLen = len;
  }
  s->cSym      = tokenToSymbol(s);
  s->cTok      = s->cTok_sav;
  s->cCol      = s->cCol_sav;
  s->cLin      = s->cLin_sav;
  s->cTok_sav  = (short)-1;
  s->cCol_sav  = s->cLin_sav = -1;
  s->cOtherLen = 0;
  if(s->cTok >= 0 && (s->cFlags[s->cTok]&SCN_FLG_IgnoreToken))
    (*((Scn_Stream_IMP)t)->nexttok)(t);
  else Tok_end((Scn_Stream_IMP)t);
}

static void Stream_next_eof(Scn_Stream t)
/* separates the embedded language eof token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  s->cTok = -1; 
  s->cSym = stringToSymbol("");
}

static void Stream_next_tryeof(Scn_Stream t)
/* checks if the embedded langugae parser accepts the eof token:
   yes --> separates the embedded language eof token in scan stream 't' 
   no  --> coninues embedded language parsing
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t),
                 x = (Scn_Stream_IMP)t;
  if( x->eAccept == (Scn_eAccept)NULL || (*x->eAccept)(x->CurPTCfg) )
  {
    s->cTok    = -1; 
    s->cSym    = stringToSymbol("");
    /*20030209 ...*/
    OT_POP(x->cEmbeds); OT_POP(x->cEmbeds); 
    OT_POP(x->cEmbeds); OT_POP(x->cEmbeds);
    /**/
    x->nexttok = Stream_next_eof;
  }
  else
  {
      s->cTok = (short)OT_TOP(long,x->cEmbeds); OT_POP(x->cEmbeds);
      s->cSym = OT_TOP(symbol,x->cEmbeds);      OT_POP(x->cEmbeds);
      OT_POP(x->cEmbeds);
      OT_POP(x->cEmbeds);
      x->nexttok = Stream_next_default;
      Stream_next_default(t);
  }
}

static void Stream_next_dyck(Scn_Stream t)
/* separates the next dyck token in scan stream 't'; 
   That's the default operation. 
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t),
                 x = (Scn_Stream_IMP)t;
  int state, cnt = 1; long cLen = s->cLen; short cTok = s->cTok;
  scn_t dyck = MAP_apply(scn_t,x->cDyckScanner,(long)s->cTok);
  long    *cStaEdg = s->cStaEdg; 
  short   *cStaFin = s->cStaFin; 
  wc_char *cEdgeC  = s->cEdgeC;  
  long    *cEdgeS  = s->cEdgeS;  
  byte    *cFlags  = s->cFlags;  
  s->cStaEdg = dyck->StaEdg;
  s->cStaFin = dyck->StaFin;
  s->cEdgeC  = dyck->EdgeC;
  s->cEdgeS  = dyck->EdgeS;
  s->cFlags  = dyck->Flags;
LOOP:
  cLen    = s->cLen;
  s->cTok = -1; /* -1 == ETX */
  if (s->cC > s->cC_eof) /* '\0' (string) and -1 (file,buffer) is treated as EOF. */
  { register wc_char *i;
    state = 0;
    for (i = &s->cEdgeC[s->cStaEdg[state]]; *i++ > s->cC; );
    state = s->cEdgeS[i-s->cEdgeC-1]-1;
    while (state >= 0)
    {
      /* n character lookahead:
         jeweils den größten Endzustand merken, zusammen mit Tokenlänge.
         nach der schleife, 
         1) wert oder fehler 
         2) fehler mit vorangegangenem Wert --> 
            zurücksetzen auf ende wertposition via backbuffer und fortsetzen
      */
      s->cTok = s->cStaFin[state]; Tok_get(s);
      if (s->cC <= s->cC_eof) /* '\0' (string) and -1 (file,buffer) is treated as EOF. */
        break;
      for (i = &s->cEdgeC[s->cStaEdg[state]]; *i++ > s->cC; );
      state = s->cEdgeS[i-s->cEdgeC-1]-1;
    }
    if((s->cLen - cLen) == 0 && s->cC > s->cC_eof) { Tok_get(s); s->cTok = 0; }
  }
  if( s->cTok > 0 || ( s->cTok == 0 && dyck->Tokens == 3 ) )
  {
    if( s->cTok == SCN_DYCKTOKEN_PREFIX ) ++cnt;
    else
    if( s->cTok == SCN_DYCKTOKEN_SUFFIX ) --cnt;
    if( cnt == 0 ) s->cTok = cTok;
    else goto LOOP;
  }
  s->cStaEdg  = cStaEdg;
  s->cStaFin  = cStaFin;
  s->cEdgeC   = cEdgeC;
  s->cEdgeS   = cEdgeS;
  s->cFlags   = cFlags;
}

static void Stream_switch_eterm(Scn_Stream t)
/* prepares embedded language token switch in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  if( s->cTok >= 0 && (s->cFlags[s->cTok]&SCN_FLG_SwitchToken) && 
      !(s->cFlags[s->cTok]&SCN_FLG_EofToken) )
  {
    if( ((Scn_Stream_IMP)t)->cEmbeds == (ROW(Any_T))NULL )
      ((Scn_Stream_IMP)t)->cEmbeds = OT_CREATE_ADT(Any_T);
    ((Scn_Stream_IMP)t)->nexttok = Stream_next_eterm;
  }
  else
  if( s->cTok >= 0 && (s->cFlags[s->cTok]&SCN_FLG_EofToken) )
  {
    OT_PUSH(s->cLin,((Scn_Stream_IMP)t)->cEmbeds);
    OT_PUSH(s->cCol,((Scn_Stream_IMP)t)->cEmbeds);
    OT_PUSH(s->cSym,((Scn_Stream_IMP)t)->cEmbeds);
    OT_PUSH((long)s->cTok,((Scn_Stream_IMP)t)->cEmbeds);
    if( (s->cFlags[s->cTok]&SCN_FLG_SwitchToken) )
    {
      s->cTok = -1; s->cSym = stringToSymbol("");
      ((Scn_Stream_IMP)t)->nexttok = Stream_next_eof;
    }
    else ((Scn_Stream_IMP)t)->nexttok = Stream_next_tryeof;
  }
}

static void Stream_next_dedent(Scn_Stream t)
/* separates the dedent token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t),
                 x = (Scn_Stream_IMP)t;
  long cur_indval = strlen(symbolToString(s->cSym)) -
                    strlen(symbolToString(s->cDedentSym)), 
                    top_indval;
  OT_POP(x->cIndentStack);
  if( cur_indval >= (top_indval=OT_TOP(long,x->cIndentStack)) )
  {
    if( cur_indval > top_indval ) /* error */
      s->cMacSym = (symbol)NULL;
    x->nexttok = Stream_next_default;
    if( x->Group >= 0 )
    { 
      Stream_switch_eterm(t);
    }
  }
  /* kein Tok_end bei dedent tokens */
}

static void Stream_next_default(Scn_Stream t)
/* separates the next token in scan stream 't'; 
   That's the default operation. 
*/
{ int state; Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t),
                            x = (Scn_Stream_IMP)t;
  if( (s->wc2mb == (string (*)(wc_string wc))NULL && s->cBuf_sav  != (string)NULL)    ||
      (s->wc2mb != (string (*)(wc_string wc))NULL && s->cWBuf_sav != (wc_string)NULL)  )
  { StreamOther_next(t); return; }
  Tok_bgn(s); 
  if( s->cScanner->Groups > 0 && s->cTok >= 0 && 
      s->cScanner->GrpScn[s->Group]->Switch[s->cTok] >= 0 ) 
    Stream_switch_group(t,s->cScanner->GrpScn[s->Group]->Switch[s->cTok]);
LOOP:
  /* '\0' (string) and -1 (file,buffer) is treated as EOF. */
  s->cTok = -1; /* -1 == ETX */
  if (s->cC > s->cC_eof) 
  { register wc_char *i;
    state = 0;
    for (i = &s->cEdgeC[s->cStaEdg[state]]; *i++ > s->cC; );
    state = s->cEdgeS[i-s->cEdgeC-1]-1;
    while (state >= 0)
    {
      /* n character lookahead:
         jeweils den größten Endzustand merken, zusammen mit Tokenlänge.
         nach der schleife, 
         1) wert oder fehler 
         2) fehler mit vorangegangenem Wert --> 
            zurücksetzen auf ende wertposition via backbuffer und fortsetzen
      */
      s->cTok = s->cStaFin[state]; Tok_get(s);
      if (s->cC <= s->cC_eof)
        break;
      for (i = &s->cEdgeC[s->cStaEdg[state]]; *i++ > s->cC; );
      state = s->cEdgeS[i-s->cEdgeC-1]-1;
    }
    //if(s->cLen == 0 && s->cC > 0) { Tok_get(s); s->cTok = 0; }
    if(((s->cOtherLen <= 0 && s->cLen == 0) || 
        (s->cOtherLen > 0 && s->cOtherLen == s->cLen)) && s->cC > s->cC_eof) 
    { Tok_get(s); s->cTok = 0; }
    // process dyck token ...
    if( MAP_defined(x->cDyckScanner,(long)s->cTok) )
      Stream_next_dyck(t);
    // ... process dyck token
    if((s->cFlags[s->cTok]&SCN_FLG_IgnoreToken) && s->cOtherLen <= 0) 
    { Tok_bgn(s); 
      if( s->cScanner->Groups > 0 && s->cTok >= 0 && 
          s->cScanner->GrpScn[s->Group]->Switch[s->cTok] >= 0 ) 
        Stream_switch_group(t,s->cScanner->GrpScn[s->Group]->Switch[s->cTok]);
      goto LOOP; 
    }
    else
    if( s->cOtherLen >= 0 && s->cTok == 0 && s->cOtherLen < MAX_TOK_LEN ) 
    { TokOther_bgn(s); 
      if( s->cScanner->Groups > 0 && s->cTok >= 0 && 
          s->cScanner->GrpScn[s->Group]->Switch[s->cTok] >= 0 ) 
        Stream_switch_group(t,s->cScanner->GrpScn[s->Group]->Switch[s->cTok]);
      goto LOOP; 
    }
  }
  Tok_end((Scn_Stream_IMP)t);
  if( x->Group >= 0 && x->nexttok != Stream_next_dedent )
  { 
    Stream_switch_eterm(t);
  }
  /* ignore (de)indent token on same position */
  if( x->cIndentStack != (ROW(long))NULL &&
      x->nexttok != Stream_next_dedent    )
  { 
    s = (Scn_Stream_IMP)Stream_current(t);
    if( s->cTok >= 0 && (s->cFlags[s->cTok]&SCN_FLG_IndentToken) &&
        s->cMacSym == (symbol)NULL )
      (*x->nexttok)(t);
  }
}

static void Stream_next_follow(Scn_Stream t)
/* separates the embedded language follow token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  s->cTok = s->cTok_sav; 
  s->cSym = s->cSym_sav; 
  s->cLin = s->cLin_sav; 
  s->cCol = s->cCol_sav;
  ((Scn_Stream_IMP)t)->nexttok = Stream_next_default;
  /* Tok_end bei follow tokens bereits erfolgt */
}

static void Stream_next_eterm(Scn_Stream t)
/* separates the next embedded language token in scan stream 't' */
{ Scn_Stream_IMP s   = (Scn_Stream_IMP)Stream_current(t),
                 x   = (Scn_Stream_IMP)t;
  Any_T          res = (Any_T)NULL;
  c_string       followtok = (c_string)NULL, cfgtok, cfg, start, pos;
  short          tid = -1, gid = -1;
  long           col = 0,  lin = 0, i;
  assert0
  ( 
    x->eTerm != (Scn_eTerm)NULL &&
    s->cScanner->Groups > 0 && s->cTok >= 0 && 
    s->cScanner->GrpScn[s->Group]->Switch[s->cTok] >= 0, ""
  );
  gid = s->Group; 
  Stream_switch_group(t,s->cScanner->GrpScn[s->Group]->Switch[s->cTok]);
  cfgtok = (c_string)NewMem(strlen(s->cScanner->GrpScn[s->Group]->Name)+1);
  assert0(pos = strstr(s->cScanner->GrpScn[s->Group]->Name,"_"), "");
  *pos = '\0'; pos += 1;
  sprintf(cfgtok,"%s%s",s->cScanner->GrpScn[s->Group]->Name,pos);
  cfg = StrCopy(s->cScanner->GrpScn[s->Group]->Name);
  start = StrCopy(pos);
  pos -= 1; *pos = '_'; 
  for( i=0; i < s->cScanner->GrpScn[gid]->Tokens; ++i )
  {
    if( !strcmp(cfgtok,s->cScanner->GrpScn[gid]->TokId[i]) )
    {
      tid = (short)i; col = s->nCol; lin = s->nLin;
      break;
    }
  }
  assert0( tid >= 0, "" );
  x->nexttok = Stream_next_default;
  { int cnt = 0; short cdefeof = x->cdefeof;
    short* cdeftok = (short*)NULL;
    MAP(symbol,short) cdefptok = MAP_copy(x->cdefptok),
                      cdefkey  = MAP_copy(x->cdefkey);
    for( i=0; i < s->cScanner->Groups; ++i )
      cnt = MAX(cnt,s->cScanner->GrpScn[i]->Tokens);
    cdeftok = (short*)NewMem(sizeof(short)*cnt);
    for( i=0; i < cnt; ++i )
      cdeftok[i] = x->cdeftok[i];
    res = (*x->eTerm)(x->CurPTCfg,cfg,start);
    x->cdefeof = cdefeof;
    FreeMem(x->cdeftok); x->cdeftok = cdeftok;
    MAP_freeMap(x->cdefptok); x->cdefptok = cdefptok;
    MAP_freeMap(x->cdefkey);  x->cdefkey  = cdefkey;
  }
  s = (Scn_Stream_IMP)Stream_current(t);
  x->nexttok = Stream_next_default;
  Tok_eterm_end(x);
  if( OT_CNT(x->cEmbeds) > 0 )
  {
    s->cTok_sav = (short)OT_TOP(long,x->cEmbeds); OT_POP(x->cEmbeds);
    s->cSym_sav = OT_TOP(symbol,x->cEmbeds);      OT_POP(x->cEmbeds);
    s->cCol_sav = OT_TOP(long,x->cEmbeds);        OT_POP(x->cEmbeds);
    s->cLin_sav = OT_TOP(long,x->cEmbeds);        OT_POP(x->cEmbeds);
    if( s->cTok_sav >= 0 && (s->cFlags[s->cTok_sav]&SCN_FLG_SwitchToken) && 
        (s->cFlags[s->cTok_sav]&SCN_FLG_EofToken) )
    {
      followtok  = s->cScanner->GrpScn[s->Group]->TokId[s->cTok_sav];
      x->nexttok = Stream_next_follow;
    }
  }
  else
  if( s->cTok >= 0 && !(s->cFlags[s->cTok]&SCN_FLG_EofToken) ) /*error*/
    x->nexttok = Stream_next_eof;
  s->cTok = tid; s->cSym = res; s->cLin = lin; s->cCol = col;
  Stream_switch_group(t,gid);
  if( followtok != (c_string)NULL )
  {
    for( i=0; i < s->cScanner->GrpScn[gid]->Tokens; ++i )
    {
      if( !strcmp(followtok,s->cScanner->GrpScn[gid]->TokId[i]) )
      {
        s->cTok_sav = (short)i;
        break;
      }
    }
  }
  FreeMem(cfgtok); FreeMem(cfg); FreeMem(start);
  /* kein Tok_end bei embedded language tokens */
}

void Stream_next(Scn_Stream t)
/* separates the next token in scan stream 't'; 
   That's the workhorse operation. 
*/
{ Scn_Stream_IMP x = (Scn_Stream_IMP)t;
  (*x->nexttok)(t);
}

/*I------------------- Accessing current token ---------------------------- */

symbol Stream_csym(Scn_Stream t)
/* symbol of the current token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t),
                 x = (Scn_Stream_IMP)t;
  if (s->cTok > 0 && 
      (s->cFlags[s->cTok]&SCN_FLG_IndentToken) &&
      x->cIndentStack != (ROW(long))NULL )
    return s->cSym;
  else
    return s->cMacSym!=(symbol)NULL?s->cMacSym:s->cSym;
}

short Stream_ctid(Scn_Stream t)
/* token number of the current token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t),
                 x = (Scn_Stream_IMP)t;
  if (s->cTok == -1) return x->cdefeof;
  if (s->cTok ==  0) return x->cdeftok[0];
  if ( s->cTok > 0 && 
      (s->cFlags[s->cTok]&SCN_FLG_IndentToken) &&
      x->cIndentStack != (ROW(long))NULL )
  { 
    if( MAP_defined(x->cdefkey,s->cMacSym) )
      return MAP_apply_short(x->cdefkey,s->cMacSym);
    else /*error*/
      return x->cdeftok[0];
  }
  else
    return MAP_defined(x->cdefkey,s->cSym)
           ? MAP_apply_short(x->cdefkey,s->cSym)
           : x->cdeftok[s->cTok];
}

c_string Stream_ctnam(Scn_Stream t)
/* name of the current token in scan stream 't' or NULL (EOF) */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  if (s->cTok == -1) return NULL;
  else
  if( s->cScanner->Groups > 0 )
    return s->cScanner->GrpScn[s->Group]->TokId[s->cTok];
  else
    return s->cScanner->TokId[s->cTok];
}

c_bool Stream_cica(Scn_Stream t)
/* whether the current token in scan stream 't' 
   has the attribute 'ignore case' 
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return (s->cTok >= 0 && (s->cFlags[s->cTok]&SCN_FLG_IgnoreCase));
}

string Stream_cbuf(Scn_Stream t)
/* string of the current token in scan stream 't' or NULL 
   ( not valid for an embedded language token )
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cBuf;
}

wc_string Stream_wcbuf(Scn_Stream t)
/* wide string of the current token in scan stream 't' or NULL 
   ( not valid for an embedded language token )
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cWBuf;
}

long Stream_clen(Scn_Stream t)
/* length of the current token in scan stream 't' 
   ( not valid for an embedded language and the follow token )
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cLen;
}

symbol Stream_cfil(Scn_Stream t)
/* source identifier of the current token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cFil;
}

long  Stream_clin(Scn_Stream t)
/* first line number of the current token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cLin;
}

long  Stream_ccol(Scn_Stream t)
/* first column number of the current token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cCol;
}

/*I------------------- Accessing scan stream definition ------------------- */

Scn_T Stream_scn(Scn_Stream t)
/* scanner definition of scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  return s->cScanner;
}

Scn_PreMacFun Stream_premac(Scn_Stream t)
/* preprocessor of scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  return s->cPreMac;
}

Scn_eTerm Stream_etermFun(Scn_Stream t)
/* embedded language token constructor of scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  return s->eTerm;
}

Scn_eAccept Stream_etermEof(Scn_Stream t)
/* embedded language accept token recognizer of scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  return s->eAccept;
}

Abs_T Stream_etermCfg(Scn_Stream t)
/* current parse term configuration of scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  return s->eTerm;
}

c_bool Stream_binmode(Scn_Stream t)
/* whether current scan stream 't' has binary mode */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return ( s->cC_eof < 0 );
}

c_bool Stream_unicode(Scn_Stream t)
/* whether current scan stream 't' is unicode-based */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return ( s->wc2mb != (string (*)(wc_string wc))NULL );
}

StdCPtr Stream_cstream(Scn_Stream t)
/* character stream of current scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cFile;
}

Any_T Stream_get_ctxval(Scn_Stream t, Any_T id)
/* value of context variable 'id' in scan stream 't' or NULL */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  if( MAP_defined(s->ctxmap,id) )
    return MAP_apply(Any_T,s->ctxmap,id);
  else return (Any_T)NULL;
}
