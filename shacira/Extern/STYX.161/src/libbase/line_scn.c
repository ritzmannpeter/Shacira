/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [line_scn.c]              Source Line Scanner                            */
/*                         & simple AWK Functionality                       */
/*                                                                          */
/* Copyright (c) 1994 by Lars D\olle, Heike Manns                           */
/* ------------------------------------------------------------------------ */

/*!!

  [line_scn] contains a set of functions for source analysis.

  1. The primitive

  |      string Line_get(FILE *SysIn)

  reads the next line from the source file 'SysIn' and returns it as a string.

  '\x1a' (DOS) and '(-1)' (UNIX) are recognized as end of file.
  The end of line characters '\n' eg. '\r\n' and trailing spaces will be removed.

  2. Further this module provides a simple AWK-mechanism.

  3. The primitive 

  |      string Line_getCFunNam(string CDecl)
  
	 extracts the function name from a C-deklaration/definition.

  4. The primitive

  |      string Line_replace(string txt, MAP(symbol,symbol) ReplaceRules)

 supports simple text replacement. Each occurance of a key in the given text will
 be replaced by the associated value.

  5. The following functions support the removement/extraction of HTML/XML-tags, 
     C-comments and spaces in a given text.

  |      string Line_withTag(string txt)
  |      string Line_withoutTag(string txt)
  |      string Line_withCCom(string txt)
  |      string Line_withCComText(string txt)
  |      string Line_withoutCCom(string txt)
  |      string Line_withoutWhite(string txt)
  |      string Line_clip[L|R](string txt)

  6. Finally this module defines a set of functions for URI-Creation/Evaluation. ( RFC 2396 )

*/

#include "standard.h"
#include "symbols.h"
#include "hmap.h"
#include "otab.h"

#include "literal.h"
#include "pathes.h"
#include "sink.h"

/*I-------------------------- Single line scanner ------------------------- */

static void addChar(string *Line_lin, long *Line_len, long *Line_top, char cc)
{ long i;
  if (*Line_top >= *Line_len)
  { string NewLine = (string)NewMem(2 * (*Line_len));
    for (i = 0; i < *Line_len; i++)
      NewLine[i] = (*Line_lin)[i];
    FreeMem(*Line_lin);
    *Line_len *= 2;
    *Line_lin  = NewLine;
  }
  (*Line_lin)[*Line_top] = cc;
  (*Line_top) += 1;
}

string Line_get(FILE *SysIn)
/* get a single line or NULL; allocs memory
   All '\r', final '\n', trailing spaces and tabs 
   are removed and other tabs expanded.
   Both (-1) and (0x1a) are treated as EOF-character.
*/
{ int cc; long i; string res;
  long   Line_top = 0;
  long   Line_len = 100;
  string Line_lin = (string)NewMem(Line_len);
  if (feof(SysIn))
  {
    FreeMem(Line_lin); return NULL;
  }
  for (cc = fgetc(SysIn);
       cc != EOF && cc != '\n' && cc != 0x1a;
       cc = fgetc(SysIn))
    addChar(&Line_lin,&Line_len,&Line_top, (char)cc);
  if (Line_top == 0 && (cc == EOF || cc == 0x1a))
  {
    FreeMem(Line_lin); return NULL;
  }
  while
  (
    Line_top > 0 &&
    (
      Line_lin[Line_top-1]== '\f' ||
      Line_lin[Line_top-1]== '\r' ||
      Line_lin[Line_top-1]== ' '
    )
  )
    Line_top -= 1;
  res = (string)NewMem(Line_top+1);
  for (i = 0; i < Line_top; i++)
    res[i] = Line_lin[i];
  res[Line_top] = '\0';
  FreeMem(Line_lin);
  return res;
}

/*I------------------------ Split line & AWK -------------------------------- */

AbstractType( AWK ); /* Abstract AWK type */

ROW(string) StrToWords(string s)
/* get a row with all the words of line 's' */
{ ROW(string) res = OT_CREATE(string,primCopy,FreeMem,primEqual);
  string bgn;
  for (; *s==' '; s+= 1);
  bgn = s;
  while( *bgn )
  {
    for (; *s && *s!=' '; s+= 1);
    if (s != bgn)
    {
      OT_PUSH(SubStrCopy(bgn,s-bgn),res);
      for (; *s==' '; s+= 1);
      bgn = s;
    }
  }
  return res;
}

static void Awk_comment(ROW(string) Words)
{
}

void AWK_defKey(AWK awk, string key, void (*act)(ROW(string) wrd))
/* adds a line key / action pair to 'awk' */
{
  MAP_dfndom((MAP(_,_))awk,stringToSymbol(key),act);
}

AWK AWK_new(string Comment)
/* creates an AWK structure 
   parameter: comment key 
*/
{
  MAPTY awkty = MAP_newTyp
                (
                  primCopy,primFree,primEqual,primHash, primCopy,primFree
                );
  MAP(symbol,void(*)())AWK_Cmds = MAP_newMap( awkty );
  AWK_defKey(AWK_Cmds,Comment,Awk_comment);
  return AWK_Cmds;
}

void AWK_free(AWK awk)
/* frees 'awk' */
{ MAPTY ty = MAP_MapTyp(awk);
  MAP_freeMap(awk);
  MAP_freeTyp(ty);
}

void AWK_apply(AWK awk, string FileName)
/* evaluates 'FileName' according to the rules in 'awk' */
{ FILE *SysIn = OpnFile(FileName,"rt");
  MAP(string,void(*)()) AWK_Cmd = (MAP(_,_))awk;
  string lin; int lineno = 1;
  for (lin = Line_get(SysIn); lin != NULL; lin = Line_get(SysIn), lineno+=1)
  { ROW(string) parts = StrToWords(lin);
    if (OT_CNT(parts) > 0)
    { symbol cmd = stringToSymbol(OT_GET(string,parts,0));
      if (MAP_defined(AWK_Cmd,cmd))
        MAP_apply(void(*)(ROW(string)),AWK_Cmd,cmd)(parts);
      else
        fprintf(stderr,"error: %s(%d) : undecodable: >%s<\n",FileName,lineno,lin);
    }
    OT_DEL_T(parts);
    FreeMem(lin);
  }
  fclose(SysIn);
}

/*I-------------------------- Text substitution --------------------------- */

static void getNextCComPos(string txt, string* ta, string* te)
/* start, end+1 position of the next C-comment or NULL */
{ string t1, t2;
  long   l = strlen(txt);
  *ta = *te = (string)NULL;
  t1 = strstr(txt,"//");
  t2 = strstr(txt,"/*");
  if( t2 == (string)NULL ) t2 = t1;
  if( t1 == (string)NULL ) t1 = t2;
  t1 = MIN(t1,t2);
  if( t1 != (string)NULL )
  {
    *ta = t1;
    t2  = strstr(t1+2,( t1[1] == '/' )?"\n":"*/");
    if( t2 == (string)NULL ) *te = txt + l;
    else
      *te = t2 + 1 + ( t1[1] == '*' ); 
  }
}

static void getNextCComTextPos(string txt, string* ta, string* te)
/* start, end+1 position of the next C-comment without delimiters or NULL */
{ string t1, t2;
  long   l = strlen(txt);
  *ta = *te = (string)NULL;
  t1 = strstr(txt,"//");
  t2 = strstr(txt,"/*");
  if( t2 == (string)NULL ) t2 = t1;
  if( t1 == (string)NULL ) t1 = t2;
  t1 = MIN(t1,t2);
  if( t1 != (string)NULL )
  {
    *ta = t1+2;
    t2  = strstr(t1+2,( t1[1] == '/' )?"\n":"*/");
    if( t2 == (string)NULL ) *te = txt + l;
    else
      *te = t2 + ( t1[1] == '/' ); 
  }
}

static void getNextTagPos(string txt, string* ta, string* te)
/* start, end+1 position of the next tag or NULL */
{ string t1, t2;
  *ta = *te = (string)NULL;
  t1 = strstr(txt,"<");
  if( t1 != (string)NULL )
  {
    t2 = strstr(t1+1,">");
    if( t2 != (string)NULL )
    {
      *ta = t1; *te = t2 + 1; 
    }
  }
}

string Line_clipR(string txt)
/* removes trailing white space; allocs memory */
{ string s = txt, r;
  long   l;
  l = strlen(s)-1;
  while( l >= 0 && 
         (s[l] == ' ' || s[l] == '\t' || s[l] == '\n' || s[l] == '\r') ) --l;
  r = SubStrCopy(s,l+1);
  return r;
}

string Line_clipL(string txt)
/* removes leading white space; allocs memory */
{ string s = txt, r;
  long   l;
  while( *s == ' ' || *s == '\t' || *s == '\n' || *s == '\r' ) ++s;
  l = strlen(s)-1;
  r = SubStrCopy(s,l+1);
  return r;
}

string Line_clip(string txt)
/* removes trailing and leading white space; allocs memory */
{ string s = txt, r;
  long   l;
  while( *s == ' ' || *s == '\t' || *s == '\n' || *s == '\r' ) ++s;
  l = strlen(s)-1;
  while( l >= 0 && 
         (s[l] == ' ' || s[l] == '\t' || s[l] == '\n' || s[l] == '\r') ) --l;
  r = SubStrCopy(s,l+1);
  return r;
}

string Line_withoutWhite(string txt)
/* removes white space; allocs memory */
{ long   l = strlen(txt), i;
  string s = NewMem(l+1), 
         t = s;
  for( i=0; i < l; ++i )
    if( txt[i] != ' ' && txt[i] != '\t' && txt[i] != '\n' && txt[i] != '\r' ) 
    {
      *t = txt[i]; t++;
    }
  *t = '\0';  
  return s;
}

string Line_withTok
       (
         string txt, 
         void (*getNextTokPos)(string s, string* ta, string* te)
       )
/* get token text only or NULL; allocs memory */
{ string t = txt, t1, t2;
  getNextTokPos(t,&t1,&t2);
  if( t1 == (string)NULL ) return (string)NULL;
  else
  { long   l = strlen(t), p = 0;
    string r = (string)NewMem(l+1), n = t1;
    while( t1 != (string)NULL )
    {
      if( n != (string)NULL && n < t1 )
      {
        *(r+p) = '\n'; ++p;
      }
      strncpy(r+p,t1,t2-t1);
      p    += t2-t1;
      r[p]  = '\0';
      t     = t2; 
      n     = strstr(t,"\n");
      (*getNextTokPos)(t,&t1,&t2);
    }
    return r;
  }
}

string Line_withoutTok
       (
         string txt, 
         void (*getNextTokPos)(string s, string* ta, string* te)
       )
/* get text without token or NULL; allocs memory */
{ string t = txt, t1, t2;
  getNextTokPos(t,&t1,&t2);
  if( t1 == (string)NULL ) return txt;
  else
  { long   l = strlen(t), p = 0;
    string r = (string)NewMem(l+1);
    while( t1 != (string)NULL )
    {
      strncpy(r+p,t,t1-t);
      p    += t1-t;
      r[p]  = '\0';
      t     = t2; 
      (*getNextTokPos)(t,&t1,&t2);
    }
    strcat(r,t);
    return r;
  }
}

string Line_withoutTag(string txt)
/* get text without HTML/XML-tags or NULL; allocs memory */
{
  return Line_withoutTok(txt,getNextTagPos);
}

string Line_withCCom(string txt)
/* get C-comment only or NULL; allocs memory */
{
  return Line_withTok(txt,getNextCComPos);
}

string Line_withCComText(string txt)
/* get C-comment text only or NULL; allocs memory */
{
  return Line_withTok(txt,getNextCComTextPos);
}

string Line_withoutCCom(string txt)
/* get text without C-comment or NULL; allocs memory */
{
  return Line_withoutTok(txt,getNextCComPos);
}

string Line_getCFunNam(string CDecl) 
/* extracts C-function name or NULL; allocs memory
   assertion: no comments in between 'CDecl'
   evaluation from right to left: 
     ... <Space> <ID> <Space> ( <Parameter> ) 
   | ... ( ... <ID> ... ) ...\<ID> ( <Parameter> )
*/
{ string n = (string)NULL, t = (string)NULL, decl, s;
  long   l, i, j, k = 0, c0 = 0, c1 = 0, c2 = 0;
  if( CDecl != (string)NULL )
  {
    decl = Line_withoutCCom(CDecl);
    l    = strlen(decl) - 1;
    i    = l;
    s    = decl + l;
    while( i > c0 && *s != ')' )
    {
      s--; --i;
    }
    if( *s == ')' ) 
    {
      for( ; i >= c0; --i, s-- )
      {
        switch( *s )
        {
          case ')': 
            if( c1 == 0 ) ++c2;
            ++c1; 
            break;
          case '(': 
            --c1; 
            if( c2 > 1 && c1 == 1 && k == 0 && c0 == 0 ) 
            {
              t = s; k = i;
            }
            else
            if( c2 > 1 && c1 == 0 && k > 0 && c0 == 0 )
            {
              c0 = i+1; i = k; s = t;
            }
            break;
          default :
          {
            if( c1 == 0 )
            {
              if( isalnum(*s) || *s == '_' ) 
              {
                t = s - 1; --i;
                //while( i > 0 && ( isalnum(*t) || *t == '_' ) )
                while( i >= c0 && ( isalnum(*t) || *t == '_' ) )
                {
                  t--; --i;
                }
                if( ! ( isalnum(*t) || *t == '_' ) ) t++;
                n = (string)NewMem(l+1);
                for( j=0; t <= s; ++j, t++ ) n[j] = *t;
                n[j] = '\0';
                if( decl != CDecl ) FreeMem(decl);
                return n;
              }
            }
          }
        }
      }
    }
    if( decl != CDecl ) FreeMem(decl);
  }
  return n;
}

static string findNextKey
              (
                string s, MAP(symbol,symbol) ReplaceRules, symbol* key
              ) 
/* search next key */
{ string res = (string)NULL, t;
  symbol k;
  MAPIT  it;
  *key = (symbol)NULL;
  MAP_forItr(k,it,ReplaceRules)
  {
    t = strstr(s,symbolToString(k));
    if( t != (string)NULL && ( res == (string)NULL || t < res ) ) 
    {
      res = t; *key = k;
    }
  }
  return res;
}

string Line_replace(string txt, MAP(symbol,symbol) ReplaceRules)
/* replaces 'txt' according 'ReplaceRules'; allocs memory 
   assertion: disjunct keys
*/
{ string s   = txt, t;
  Sink   snk = Sink_open();
  symbol key;
  while( True )
  {
    t = findNextKey(s,ReplaceRules,&key);
    if( t != (string)NULL )
    {
      while( s < t )
      {
        Sink_printf(snk,"%c",*s); ++s;
      }
      Sink_printf(snk,"%s",symbolToString(MAP_apply(symbol,ReplaceRules,key)));
      s += strlen(symbolToString(key));
    }
    else
    {
      Sink_printf(snk,"%s",s); break;
    }
  }
  return Sink_close(snk);
}

/*I-------------------------- URI Generation & Evaluation ----------------- */

/*DOC_INTERFACE*/
#define URI_SCHEME    0
#define URI_AUTHORITY 1
#define URI_PATH      2
#define URI_QUERY     3
#define URI_FRACTION  4


static string setURIPart(string uri, long idx, long key, MAP(long,symbol) parts)
{ string part = SubStrCopy(uri,idx);
  if( key == URI_SCHEME ) 
    MAP_dfndom(parts,key,lstringToSymbol(part));
  else MAP_dfndom(parts,key,stringToSymbol(part));
  FreeMem(part);
  return uri+idx;
}

bool URI_hasFileScheme(MAP(long,symbol) parts)
/* whether URI has a file scheme */
{
  if( MAP_defined(parts,URI_SCHEME) )
  { string scheme = symbolToString(MAP_apply(symbol,parts,URI_SCHEME));
    return !strcmp(scheme,"file:");
  }
  return False;
}

void URI_setFileScheme(MAP(long,symbol) parts)
/* set URI scheme to file scheme */
{
  if( ! URI_hasFileScheme(parts) )
  {
    MAP_ovrdom(parts,URI_SCHEME,stringToSymbol("file:"));
  }
}

bool URI_hasAuthority(MAP(long,symbol) parts)
/* whether URI has a non-empty authority */
{
  if( MAP_defined(parts,URI_AUTHORITY) )
  { string authority = symbolToString(MAP_apply(symbol,parts,URI_AUTHORITY));
    if( strlen(authority) > 2 ) return True;
  }
  return False;
}

bool URI_hasFraction(MAP(long,symbol) parts)
/* whether URI has a non-empty fraction */
{
  if( MAP_defined(parts,URI_FRACTION) )
  { string fraction = symbolToString(MAP_apply(symbol,parts,URI_FRACTION));
    return strlen(fraction) > 1;
  }
  return False;
}

void URI_setDftFraction(string dftfraction, MAP(long,symbol) parts)
/* set URI fraction to default fraction 'dftfraction', if non-defined */
{
  if( ! URI_hasFraction(parts) )
  {
    MAP_ovrdom(parts,URI_FRACTION,stringToSymbol(dftfraction));
  }
}

string URI_getFraction(MAP(long,symbol) parts)
/* get URI fraction or NULL */
{
  if( MAP_defined(parts,URI_FRACTION) )
    return symbolToString(MAP_apply(symbol,parts,URI_FRACTION));
  return (string)NULL;
}

string URI_getPath(MAP(long,symbol) parts)
/* get URI path or NULL */
{
  if( MAP_defined(parts,URI_PATH) )
    return symbolToString(MAP_apply(symbol,parts,URI_PATH));
  return (string)NULL;
}

void URI_setPath(string path, MAP(long,symbol) parts)
/* set URI path to 'path' */
{
  MAP_ovrdom(parts,URI_PATH,stringToSymbol(path));
}

int URI_EscToAscChar(string uri_part)
/* get ascii value of escaped character or -1 */
{
  if( strlen(uri_part) >= 3 && 
      uri_part[0] == '%' && isxdigit(uri_part[1]) && isxdigit(uri_part[2]) )
  { int c = LIT_hex2_char(uri_part[1],uri_part[2]); 
    return c;
  }
  else return -1;
}

bool URI_isLocalFile(MAP(long,symbol) parts) 
/* whether URI references a local file */
{
  return ( ! MAP_defined(parts,URI_SCHEME) || URI_hasFileScheme(parts) ) &&
         ! URI_hasAuthority(parts);
}

bool URI_isTreeLocalFile(string abspath, MAP(long,symbol) parts) 
/* whether URI references a file within the local tree 'abspath' */
/* True <-->
   (empty or file scheme) and empty authority and path located in tree
*/
{
  if( ! URI_isLocalFile(parts) ) return False;
  else
  if( ! MAP_defined(parts,URI_PATH) ) return True;
  else
  { string p1, p2;
    char   d1 = '\0', d2 = '\0';
    p2 = symbolToString(MAP_apply(symbol,parts,URI_PATH));
    if( ! AbsolutePathSep(p2) ) return True;
    if( PathIgnCase() )
    {
      p1 = symbolToString(ustringToSymbol(abspath));
      p2 = symbolToString(ustringToSymbol(p2));
    }
    else p1 = symbolToString(stringToSymbol(abspath));
    if( strlen(p1) >= 2 && isalpha(p1[0]) && p1[1] == ':' )
    {
      d1 = p1[0]; p1 += 2; p1 += AbsolutePathSep(p1);
    }
    if( strlen(p2) >= 3 && isalpha(p2[1]) && ( p2[2] == ':' || p2[2] == '|' ) )
    {
      d2 = p2[1]; p2 += 3; p2 += AbsolutePathSep(p2);
    }
    if( d1 != d2 ) return False;
    else
    { int c;
      while( *p1 != '\0' )
      {
        if( *p2 == ';' ) // remove parameters from uri-abspath
          while( *p2 != '/' && *p2 != '\0' ) ++p2;
        if( *p2 == '\0' ) return False;
        c = URI_EscToAscChar(p2);
        if( c >= 0 && ( (int)*p1 == c || 
            ( AbsolutePathSep(p1) && AbsolutePathSep((string)&c) ) ) )
        {
          ++p1; p2 += 3;
        }
        else
        if( c<0 && (*p1 == *p2 || ( AbsolutePathSep(p1) && AbsolutePathSep(p2)) ) )
        {
          ++p1; ++p2;
        }
        else return False;
      }
      return True;
    }
  }
}

void URI_desParts(string txt, MAP(long,symbol) parts)
/* destructs URI 'txt' to its components in 'parts' */
{ long   len = strlen(txt), idx = -1, key;
  string uri = Line_withoutWhite(txt),
         s   = uri, t;
  // empty URI
  if( len == 0 ) { FreeMem(uri); return; }
  // non-empty URI
  idx = strcspn(s,":?#/");
  if( idx >= 0 && idx < len )
  {
    if( s[idx] == ':' ) // scheme [, rel/net/abs path [, query [, fraction] ] ]
    {
      s = setURIPart(s,idx+1,URI_SCHEME,parts);
      if( s[0] == '/' || s[0] == '?' || s[0] == '#' )
        URI_desParts(s,parts);
      else // opaque
      {
        idx = strcspn(s,"#");
        if( idx >= 0 && idx < strlen(s) )
        {   
          s = setURIPart(s,idx,URI_PATH,parts);
          MAP_dfndom(parts,URI_FRACTION,stringToSymbol(s));
        }
        else MAP_dfndom(parts,URI_PATH,stringToSymbol(s));
      }
    }
    else
    if( s[idx] == '/' ) // rel/net/abs path [, query [, fraction] ]
    {
      key = URI_PATH;
      if( idx == 0 && s[idx+1] == '/' ) // net path
      {
        t   = s+2;
        idx = strcspn(t,"?#/");
        if( idx >= 0 && idx < strlen(t) && t[idx] == '/' )
          s = setURIPart(s,idx+2,URI_AUTHORITY,parts);
        else key = URI_AUTHORITY;
      }
      idx = strcspn(s,"?#");
      if( idx >= 0 && idx < strlen(s) )
      {   
        s = setURIPart(s,idx,key,parts);
        URI_desParts(s,parts);
      }
      else MAP_dfndom(parts,key,stringToSymbol(s));
    }
    else
    if( s[idx] == '?' ) // rel path, query [, fraction] 
    {
      if( idx > 0 ) s = setURIPart(s,idx,URI_PATH,parts);
      idx = strcspn(s,"#");
      if( idx >= 0 && idx < strlen(s) )
      {
        s = setURIPart(s,idx,URI_QUERY,parts);
        MAP_dfndom(parts,URI_FRACTION,stringToSymbol(s));
      }
      else MAP_dfndom(parts,URI_QUERY,stringToSymbol(s));
    }
    else
    if( s[idx] == '#' ) // rel path, fraction 
    {
      if( idx > 0 ) s = setURIPart(s,idx,URI_PATH,parts);
      MAP_dfndom(parts,URI_FRACTION,stringToSymbol(s));
    }
  }
  else // rel path 
    MAP_dfndom(parts,URI_PATH,stringToSymbol(s));
  FreeMem(uri);
}

string URI_consParts(MAP(long,symbol) parts, bool localURI)
/* constructs URI from its components in 'parts'; allocs memory */
{ Sink   snk = Sink_open();
  string uri;
  if( !localURI && MAP_defined(parts,URI_SCHEME) )
    Sink_printf(snk,"%s",symbolToString(MAP_apply(symbol,parts,URI_SCHEME)));
  if( !localURI && MAP_defined(parts,URI_AUTHORITY) )
    Sink_printf(snk,"%s",symbolToString(MAP_apply(symbol,parts,URI_AUTHORITY)));
  if( MAP_defined(parts,URI_PATH) )
    Sink_printf(snk,"%s",symbolToString(MAP_apply(symbol,parts,URI_PATH)));
  if( MAP_defined(parts,URI_QUERY) )
    Sink_printf(snk,"%s",symbolToString(MAP_apply(symbol,parts,URI_QUERY)));
  if( MAP_defined(parts,URI_FRACTION) )
    Sink_printf(snk,"%s",symbolToString(MAP_apply(symbol,parts,URI_FRACTION)));
  uri = Sink_close(snk);
  return uri;
}

void URI_RelToAbs
     (
       string rel, string base, string doc, MAP(long,symbol) abs_parts
     )
/* destructs relative URI 'rel' to its absolute components in 'parts' */
{ string path = (string)NULL, rel_path, t;
  // 5.2.1
  URI_desParts(rel,abs_parts);
  if( ! MAP_defined(abs_parts,URI_SCHEME)    &&
      ! MAP_defined(abs_parts,URI_AUTHORITY) &&
      ! MAP_defined(abs_parts,URI_PATH)      &&
      ! MAP_defined(abs_parts,URI_QUERY)     &&
      ! STR_EMPTY(doc)                        ) // 5.2.2
  { symbol frag = (symbol)NULL; 
    if( MAP_defined(abs_parts,URI_FRACTION) )
    {
      frag = MAP_apply(symbol,abs_parts,URI_FRACTION);
      MAP_rmvdom(abs_parts,URI_FRACTION);
    }
    URI_desParts(doc,abs_parts);
    if( frag != (symbol)NULL ) MAP_ovrdom(abs_parts,URI_FRACTION,frag);
  }
  else
  if( ! MAP_defined(abs_parts,URI_SCHEME) && !STR_EMPTY(base) ) // 5.2.3 ff
  { MAP(long,symbol) base_parts = MAP_newMap(MAP_MapTyp(abs_parts));
    URI_desParts(base,base_parts);
    if( MAP_defined(base_parts,URI_SCHEME) ) // 5.2.3
      MAP_dfndom(abs_parts,URI_SCHEME,MAP_apply(symbol,base_parts,URI_SCHEME));
    if( ! MAP_defined(abs_parts,URI_AUTHORITY) &&
          MAP_defined(base_parts,URI_AUTHORITY) ) // 5.2.4
      MAP_dfndom
      (
        abs_parts,URI_AUTHORITY,MAP_apply(symbol,base_parts,URI_AUTHORITY)
      );
    if( MAP_defined(abs_parts,URI_PATH) ) // 5.2.5/6
    { 
      rel_path = symbolToString(MAP_apply(symbol,abs_parts,URI_PATH));
      if( *rel_path != '/' )
      { Sink snk = Sink_open();
        ROW(symbol) path_segs = OT_CREATE_ADT(symbol);
        long cnt, i;
        PIT  itr;
        if( MAP_defined(base_parts,URI_PATH) )
          path = symbolToString(MAP_apply(symbol,base_parts,URI_PATH));
        if( path != (string)NULL )
        {
          t = strrchr(path,'/');
          if( t != (string)NULL ) 
          {
            *t = '\0'; Sink_printf(snk,"%s/",path); *t = '/';
          }
        }
        Sink_printf(snk,"%s",rel_path);
        path = Sink_close(snk);
        itr  = PIT_make(path); PIT_sep(itr,"/");
        while( ( t = PIT_read(itr) ) != NULL )
          if( strcmp(t,".") ) OT_PUSH(stringToSymbol(t),path_segs);
        PIT_drop(itr);
        FreeMem(path);
        for( i=0; i < OT_CNT(path_segs); ++i )
        {
          t = symbolToString(OT_GET(symbol,path_segs,i));
          if( !strcmp(t,"..") && i > 0 &&
              strcmp(symbolToString(OT_GET(symbol,path_segs,i-1)),"..") )
          {
            OT_DEL_ES(path_segs,i-1,2); i=-1;
          }
        }
        snk = Sink_open();
        cnt = OT_CNT(path_segs);
        for( i=0; i < cnt; ++i )
          Sink_printf
          (
            snk,"%s%s",i>0?"/":"",symbolToString(OT_GET(symbol,path_segs,i))
          );
        path = Sink_close(snk);
        MAP_ovrdom(abs_parts,URI_PATH,stringToSymbol(path));
        FreeMem(path);
        OT_DEL_T(path_segs);
      }
    }
    MAP_freeMap(base_parts);
  }
}

