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
#define SCN_FLG_IgnoreToken 1
#define SCN_FLG_IgnoreCase  2

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

/* Following local variables support the scanning operations.               */
/* If multiple scanners are needed, these variables could be packed into    */
/* a structure to reflect different states.                                 */

#define MAX_TOK_LEN 10000

AbstractType( Scn_Stream );     /* Stream onto a scanner                 */

ExternalType( Scn_Stream_Itr )  /* Character iterator onto a scan stream */
{
  void    *cFile;                 /* open character stream object           */
  int    (*cGetc )(StdCPtr file); /* get next character                     */
                                  /* set stream position                    */
  int    (*fSeek )(StdCPtr file, long offset, int origin);
  void   (*cClose)(StdCPtr file); /* close stream object                    */
  string (*wc2mb )(wc_string wc); /* wide character to multibyte conversion */
                                  /* ( UCS4 --> UTF-8 )                     */
  symbol cFil;                    /* stream identifier                      */
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

ConcreteType( Scn_Stream_IMP )
{
  /* Character Iterator */
  void    *cFile;
  int    (*cGetc )(StdCPtr file);
  int    (*fSeek )(StdCPtr file, long offset, int origin);
  void   (*cClose)(StdCPtr file);
  string (*wc2mb )(wc_string wc); /* text mode only */
  /* Location Tracking */
  long  cCol,  nCol;
  long  cLin,  nLin;
  symbol cFil;
  /* Symbol under construction */
  /* cC_eof = -1 ==> binary, default=0 (text) */
  int       cC, cC_sav, cC_eof;
  string    cBuf /*[cBufLen]*/;
  wc_string cWBuf/*[cBufLen]*/;
  long      cLen,  cBufLen;
  /* Scanner */
  scn_t    cScanner;   /* Following variables are unpacked from cScanner */
  short   *cStaEdg;    /* Note that this array will be offset in Scn_bgn */
  short   *cStaFin;
  wc_char *cEdgeC;
  short   *cEdgeS;
  byte    *cFlags;
  /* token and symbol */
  short  cTok;
  symbol cSym;
  symbol cMacSym;
  /* screener */
  short               cdefeof;    /* the tid for EOF                     */
  short              *cdeftok;    /* the tid for Token[i]                */
  MAP(symbol,short)   cdefkey;    /* the tid for keywords                */
  MAPTY               keyty;      /* the typ of tid for keywords         */
  Scn_PreMacFun       cPreMac;    /* macro pre-processing function       */
  ROW(Scn_Stream)     cStreams;   /* substreams for macro pre-processing */
  MAP(Any_T,Any_T)    ctxmap;     /* stream context: id |--> value       */
  /* other token concatenation ( text mode only ) */
  long                cOtherLen;  /* other token length in buffer or -1  */
                                  /* first non other token:              */
  short               cTok_sav;   /* token                               */
  long                cCol_sav;   /* start column                        */
  long                cLin_sav;   /* start line                          */
  string              cBuf_sav;   /* buffer                              */
  wc_string           cWBuf_sav;  /* wide buffer                         */
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

static void Tok_get(Scn_Stream_IMP s)
/* buffer cC, track position, get next cC */
{
  Tok_add(s,s->cC);
  if (s->cC == (( s->wc2mb == (string (*)(wc_string wc))NULL ) ? (int)'\n' : WCHAR_LITERAL('\n')))
  { s->nLin += 1; s->nCol = 1; }
  else
  { s->nCol += 1; }
  if( s->cC_sav >= 0 )
  {
    s->cC     = s->cC_sav;
    s->cC_sav = -1;
  }
  else 
    s->cC = (*(s->cGetc))(s->cFile);
}

/*I------------------- Accessing scanner definition ----------------------- */

short Scn_check_Token(Scn_T scn, string s)
/* whether string 's' is a token in scanner 'scn';
   result = token number ( > 0 ) or 0
*/
{ int state = 0, tok = -1, len = 0; scn_t si = Scn_IMP(scn); register wc_char *i;
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
*/
{ int state = 0, tok = -1, len = 0; scn_t si = Scn_IMP(scn); register wc_char *i;
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
/* number of tokens defined in scanner 'scn' */
{
  return Scn_IMP(scn)->Tokens;
}

string Scn_tokid(Scn_T scn, int i)
/* name of the i-th token definied in scanner 'scn'; allocs memory */
{
  bug0(0 <= i && i < Scn_IMP(scn)->Tokens,"invalid range");
  return StrCopy(Scn_IMP(scn)->TokId[i]);
}

byte Scn_tokFlags(Scn_T scn, int i)
/* flags of the i-th token definied in scanner 'scn' */
{
  bug0(0 <= i && i < Scn_IMP(scn)->Tokens,"invalid range");
  return Scn_IMP(scn)->Flags[i];
}

/*I------------------- Character iterator definition ---------------------- */

static Scn_Stream_Itr Stream_Itr_init
                      (
                        Scn_Stream_Itr itr,
                        int     f_getc (StdCPtr file), 
                        void    f_close(StdCPtr file),
                        string  f_wc2mb(wc_string wc),
                        int     f_seek (StdCPtr file, long offset, int origin),
                        StdCPtr file,
                        string  fileid
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
                 int     f_getc (StdCPtr file), 
                 void    f_close(StdCPtr file),
                 string  f_wc2mb(wc_string wc),
                 int     f_seek (StdCPtr file, long offset, int origin),
                 StdCPtr file,
                 string  fileid
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

Scn_Stream Stream_bgn(Scn_T scn, Scn_Stream_Itr itr)
/* creates and initializes a scan stream 
   onto scanner 'scn' and character iterator 'itr'
*/
{ Scn_Stream_IMP     s   = New(Scn_Stream_IMP);
  int                i;
  s->cGetc    = itr->cGetc;
  s->fSeek    = itr->fSeek;
  s->cClose   = itr->cClose;
  s->wc2mb    = itr->wc2mb;
  s->cFile    = itr->cFile;
  s->cScanner = Scn_IMP(scn);
  s->cStaEdg  = s->cScanner->StaEdg;
  s->cStaFin  = s->cScanner->StaFin;
  s->cEdgeC   = s->cScanner->EdgeC;
  s->cEdgeS   = s->cScanner->EdgeS;
  s->cFlags   = s->cScanner->Flags;
  s->cC_eof   = 0; // default-eof-offset ( non-binary mode )
  s->cC_sav   = -1;
  s->cC       = (*(s->cGetc))(s->cFile);
  //s->cC       = MAX(0,s->cC);
  Tok_new(s);
  s->nLin     = 1;
  s->nCol     = 1;
  s->cTok     = 0;
  s->cdefeof  = -1;
  s->cdeftok  = (short*)NewMem(sizeof(short)*s->cScanner->Tokens);
  s->cFil     = itr->cFil;
  for (i = 0; i < s->cScanner->Tokens; i++)
    s->cdeftok[i] = i;
  s->keyty = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  s->cdefkey   = MAP_newMap(s->keyty);
  s->cPreMac   = (Scn_PreMacFun)NULL;
  s->cStreams  = (ROW(Scn_Stream))NULL;
  s->ctxmap    = MAP_newMap(s->keyty);
  s->cOtherLen = s->cCol_sav = s->cLin_sav = -1;
  s->cTok_sav  = (short)-1;
  s->cBuf_sav  = (string)NULL;
  s->cWBuf_sav = (wc_string)NULL;
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
  MAP_freeMap(s->cdefkey);
  MAP_freeMap(s->ctxmap);
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
  FreeMem(s);
}

void Stream_premac_set(Scn_Stream t, Scn_PreMacFun cPreMac)
/* adds 'cPreMac' to scan stream 't'
   for token preprocessing & macro expansion 
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  assert0(s->cPreMac == (Scn_PreMacFun)NULL,"preprocessor allready defined");
  s->cPreMac  = cPreMac;
  s->cStreams = OT_CREATE_ADT(Scn_Stream);
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
  if( s->cC_eof == 0 ) /* non-binary mode */
    s->cOtherLen = 0;
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
  s->cOtherLen = 0;
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
    (int    (*)(StdCPtr))          cGet,
    (void   (*)(StdCPtr))          NULL,
    (string (*)(wc_string))        NULL,
    (int    (*)(StdCPtr,long,int)) fseek,
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
    (int    (*)(StdCPtr))          fgetc,
    (void   (*)(StdCPtr))          fclose,
    (string (*)(wc_string))        NULL,
    (int    (*)(StdCPtr,long,int)) fseek,
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
    (int    (*)(StdCPtr))          cGet,
    (void   (*)(StdCPtr))          fclose,
    (string (*)(wc_string))        NULL,
    (int    (*)(StdCPtr,long,int)) fseek,
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
  byte* buffer;
  long  len;
  long  cpos;
};

static int scn_buffer_fseek(scn_buffer t, long offset, int origin)
/* fseek routine for byte array scanning 
   ( position may vary between 0 and EOB ) 
*/
{ long npos = -1;
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
    return 0;
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
    (int    (*)(StdCPtr))          scn_buffer_getc,
    (void   (*)(StdCPtr))          scn_buffer_close,
    (string (*)(wc_string))        NULL,
    (int    (*)(StdCPtr,long,int)) scn_buffer_fseek,
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
  string text;
  long   cpos;
};

static int scn_text_fseek(scn_text t, long offset, int origin)
/* fseek routine for string scanning ( position may vary between 0 and EOS ) */
{ long npos = -1,
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
    return 0;
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
    (int    (*)(StdCPtr))          scn_text_getc,
    (void   (*)(StdCPtr))          scn_text_close,
    (string (*)(wc_string))        NULL,
    (int    (*)(StdCPtr,long,int)) scn_text_fseek,
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

void Stream_defEofId(Scn_Stream t, short tid)
/* defines 'tid' as EOF token number in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  s->cdefeof = tid;
}

void Stream_defErrId(Scn_Stream t, short tid)
/* defines 'tid' as error token number in scan stream 't' */
{ int i; Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  for (i=0; i < s->cScanner->Tokens; i++)
    s->cdeftok[i] = tid;
}

void Stream_defTokId(Scn_Stream t, string Name, short tid)
/* defines 'tid' as number for token 'Name' in scan stream 't' */
{ int i; Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  for (i = 1; i < s->cScanner->Tokens; i++)
    if (!strcmp(Name,s->cScanner->TokId[i]))
    {
      s->cdeftok[i] = tid;
      return;
    }
  bug(False,"\'Scn_defTokId(\"%s\",%d)\': Token not seen",Name,tid);
}

void Stream_defKeyId(Scn_Stream t, string Text, short tid)
/* defines 'tid' as number for keyword 'Text' in scan stream 't' */
{ string         normal = StrCopy(Text);
  Scn_Stream_IMP s      = (Scn_Stream_IMP)t;
  int            tok    = Scn_check_Token(s->cScanner,Text);
  bug(tok,"Scn_defKeyId(\"%s\",%d): not a token",Text,tid);
  if (s->cFlags[tok]&SCN_FLG_IgnoreCase) StrToLower(normal);
  MAP_dfndom(s->cdefkey,stringToSymbol(normal),(long)tid);
  FreeMem(normal);
}

void Stream_defWCKeyId(Scn_Stream t, wc_string Text, short tid)
/* defines 'tid' as number for wide keyword 'Text' in scan stream 't' */
{ wc_string      normal = WCStrCopy(Text);
  string         mbnormal;
  Scn_Stream_IMP s      = (Scn_Stream_IMP)t;
  int            tok;
  assert0
  ( 
    s->wc2mb != (string (*)(wc_string wc))NULL, 
    "missing wide-to-multibyte character conversion function"
  );
  tok = Scn_check_WCToken(s->cScanner,Text);
  if( !tok )
  { symbol mbkey = (symbol)NULL;
    mbnormal = (*s->wc2mb)(Text);
    if( mbnormal != (string)NULL ) 
      mbkey = stringToSymbol(mbnormal);
    else
      mbkey = stringToSymbol("");
    bug
    (
      False,"Scn_defKeyId(\"%s\",%d): not a token",symbolToString(mbkey),tid
    );
  }
  else
  {
    if (s->cFlags[tok]&SCN_FLG_IgnoreCase) WCStrToLower(normal);
    bug0((mbnormal = (*s->wc2mb)(normal))!=(string)NULL,"");
    MAP_dfndom(s->cdefkey,stringToSymbol(mbnormal),(long)tid);
  }
  FreeMem(normal); FreeMem(mbnormal);
}

/*I------------------------ Scan stream operations ------------------------ */

/*forward*/ void Stream_next(Scn_Stream t);

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
  { 
    string mbs;
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
  symbol         txt = (symbol)NULL;
  int            rescan;
  if( s->wc2mb == (string (*)(wc_string wc))NULL )
    rescan = (*t->cPreMac)(t,t->cScanner->TokId[s->cTok],s->cBuf,&txt);
  else
  {
    bug0((s->cBuf = (*s->wc2mb)(s->cWBuf))!=(string)NULL,"");
    rescan  = (*t->cPreMac)(t,t->cScanner->TokId[s->cTok],s->cBuf,&txt);
    FreeMem(s->cBuf); s->cBuf = (string)NULL;
  }
  if( rescan == SCN_FLG_RescanChar )
  {
    s->cC_sav = s->cC;
    s->cC     = (int)txt;
    Stream_next(t);
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
      else BUG;
      x->cFil = stringToSymbol(f);
      if( x->cC_eof == 0 && s->cOtherLen >= 0 ) 
        x->cOtherLen = 0;
      FreeMem(f);
      OT_PUSH(x,t->cStreams);
      Stream_next(t);
    }
    else /* replace token value */
    {
      s->cMacSym = txt;
      s->cSym    = tokenToSymbol(s);
    }
  }
  else /* ignore token */
    Stream_next(t); 
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

static void Tok_end(Scn_Stream_IMP t)
/* pass token in buffer to symbol table */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  if( s->cC_eof == 0 && s->wc2mb == (string (*)(wc_string wc))NULL )
  { /* text mode */
    Tok_add(s,(int)'\0');
    if (s->cFlags[s->cTok]&SCN_FLG_IgnoreCase) StrToLower(s->cBuf);
  }
  else
  if( s->wc2mb != (string (*)(wc_string wc))NULL )
  { /* wide character mode */
    Tok_add(s,WCHAR_LITERAL('\0'));
    if (s->cFlags[s->cTok]&SCN_FLG_IgnoreCase) WCStrToLower(s->cWBuf);
  }
  /* pre-process macro */
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
        Stream_next(t);
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
  if(s->cFlags[s->cTok]&SCN_FLG_IgnoreToken)
    Stream_next(t);
  else Tok_end((Scn_Stream_IMP)t);
}

void Stream_next(Scn_Stream t)
/* separates the next token in scan stream 't'; 
   That's the workhorse operation. 
*/
{ int state; Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  if( (s->wc2mb == (string (*)(wc_string wc))NULL && s->cBuf_sav  != (string)NULL)    ||
      (s->wc2mb != (string (*)(wc_string wc))NULL && s->cWBuf_sav != (wc_string)NULL)  )
  { StreamOther_next(t); return; }
  Tok_bgn(s); 
LOOP:
  s->cTok = -1; /* -1 == ETX */
  if (s->cC > s->cC_eof) /* '\0' (string) and -1 (file,buffer) is treated as EOF. */
  { register wc_char *i;
    state = 0;
    for (i = &s->cEdgeC[s->cStaEdg[state]]; *i++ > s->cC; );
    state = s->cEdgeS[i-s->cEdgeC-1]-1;
    while (state >= 0)
    {
      s->cTok  = s->cStaFin[state]; Tok_get(s);
      if (s->cC <= s->cC_eof) /* '\0' (string) and -1 (file,buffer) is treated as EOF. */
        break;
      for (i = &s->cEdgeC[s->cStaEdg[state]]; *i++ > s->cC; );
      state = s->cEdgeS[i-s->cEdgeC-1]-1;
    }
    //if(s->cLen == 0 && s->cC > 0) { Tok_get(s); s->cTok = 0; }
    if(((s->cOtherLen <= 0 && s->cLen == 0) || 
        (s->cOtherLen > 0 && s->cOtherLen == s->cLen)) && s->cC > s->cC_eof) 
    { Tok_get(s); s->cTok = 0; }
    if((s->cFlags[s->cTok]&SCN_FLG_IgnoreToken) && s->cOtherLen <= 0) 
    { Tok_bgn(s); goto LOOP; }
    else
    if( s->cOtherLen >= 0 && s->cTok == 0 && s->cOtherLen < MAX_TOK_LEN ) 
    { TokOther_bgn(s); goto LOOP; }
  }
  Tok_end((Scn_Stream_IMP)t);
}

/*I------------------- Accessing current token ---------------------------- */

short Stream_ctid(Scn_Stream t)
/* token number of the current token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t),
                 x = (Scn_Stream_IMP)t;
  if (s->cTok == -1) return x->cdefeof;
  if (s->cTok ==  0) return x->cdeftok[0];
  return MAP_defined(x->cdefkey,s->cSym)
         ? MAP_apply_short(x->cdefkey,s->cSym)
         : x->cdeftok[s->cTok];
}

c_bool Stream_cica(Scn_Stream t)
/* whether the current token in scan stream 't' 
   has the attribute 'ignore case' 
*/
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return (s->cFlags[s->cTok]&SCN_FLG_IgnoreCase);
}

symbol Stream_csym(Scn_Stream t)
/* symbol of the current token in scan stream 't' */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cMacSym!=(symbol)NULL?s->cMacSym:s->cSym;
}

string Stream_cbuf(Scn_Stream t)
/* string of the current token in scan stream 't' or NULL */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cBuf;
}

wc_string Stream_wcbuf(Scn_Stream t)
/* wide string of the current token in scan stream 't' or NULL */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)Stream_current(t);
  return s->cWBuf;
}

long Stream_clen(Scn_Stream t)
/* length of the current token in scan stream 't' */
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

Any_T Stream_get_ctxval(Scn_Stream t, Any_T id)
/* value of context variable 'id' in scan stream 't' or NULL */
{ Scn_Stream_IMP s = (Scn_Stream_IMP)t;
  if( MAP_defined(s->ctxmap,id) )
    return MAP_apply(Any_T,s->ctxmap,id);
  else return (Any_T)NULL;
}
