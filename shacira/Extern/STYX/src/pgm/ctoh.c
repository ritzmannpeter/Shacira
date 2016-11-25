/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ctoh.c]        Creates an Interface File from a C-Source                */
/*                                                                          */
/* Copyright (c) 1994 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/*       [*.h] files should now look like       */
/*                                              */
/*       Header ...                             */
/*                                              */
/*       #ifndef __MODNAME                      */
/*       #define __MODNAME                      */
/*                                              */
/*       Includes ...                           */
/*                                              */
/*+++    #ifdef __cplusplus                     */
/*+++    extern "C" {                           */
/*+++    #endif                                 */
/*                                              */
/*       Signature ...                          */
/*                                              */
/*+++    #ifdef __cplusplus                     */
/*+++    }                                      */
/*+++    #endif                                 */
/*       #endif  __MODNAME                      */

#include "stdosx.h"
#include "pathes.h"
#include "sink.h"
#include "dicts.h"
#include "line_scn.h"
#include "com_get.h"
#include "hmap.h"
#include "hset.h"
#include "symbols.h"
#include "ctoh_cim.h"
#include "binimg.h"
#include "scn_base.h"
#include "ccnv_lim.h"

static long pgmtim; /* the start time of this program */

static string null_line = "";
static string scan_line = (string)NULL;
static string line = (string)NULL;

static symbol ccls = (symbol)NULL;
static string cfid = (string)NULL;
static string lnam = (string)NULL;
static string hnam = (string)NULL;
static string cnam = (string)NULL;
static string enam = (string)NULL;

static FILE *SysIn  = (FILE*)NULL;
static FILE *SysOut = (FILE*)NULL;
static FILE *SysExp = (FILE*)NULL;
static FILE *SysDoc = (FILE*)NULL;

static long lineno      = 0;     /* current line number           */
static bool Patched     = False; /* c/h patched in header comment */
static bool IncludeSeen = False; /* passed any includes           */
static bool Shift       = False; /* between '{' ... '}'           */
static bool OnOff       = True;  /* 'INTERFACE_ON/OFF'            */
static bool mainSeen    = False; /* 'main' seen                   */

#define       GenExp   CTX_EVAL(string  ,"exp")
#define       GenApi   CTX_EVAL(string  ,"api")
static symbol ApiSym = (symbol)NULL;

#define       CTypConv CTX_EVAL(bool,"ct")
static Scn_T  pScn   = (Scn_T)NULL;

#define       DROOT    CTX_EVAL(string  ,"DROOT")

#define GET_REFERENCE(a,b) (getReference((void**)(a),(void (*)(void**))(b)))
#define PUT_REFERENCE(a,b) (putReference((void*)(a),(void (*)(void*))(b)))

#define LineLength         78
#define CommentMargin      40

#define HTML_DOCTYPE \
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \
        \"http://www.w3.org/TR/REC-html40/Transitional.dtd\">"


bool beginswith(string key)
{
  return strncmp(line,key,strlen(key)) == 0;
}

bool endswith(string key)
{ int len = strlen(line), klen = strlen(key);

  if( len < klen ) return False;
  return strncmp(line+len-klen,key,klen) == 0;
}

void patchhead(void)
{ int fidlen = strlen(cfid), i, len = strlen(line);
  for (i = 0; i < len; i++)
  {
    if (line[i] == '[' && strncmp(cfid,line+i+1,fidlen) == 0)
    { int j, k;
      for( j=fidlen-1; j > 0; --j )
        if( line[i+j] == '.' )
        {
          line[i+j+1] = 'h'; Patched = True; break;
        }
      k = i + fidlen + 1;
      if( line[k] == '(' )
      { string s; int clslen = 0;
        for( k=k+1; k < len; ++k )
          if( line[k] == ')' ) 
            { ++k; break; }
          else
          {
            if( isalpha(line[k]) || line[k] == '_' ) ++clslen;
            else
            {
              fprintf(STDERR,"Warnung: %s bad module name.\n",cfid);
              return;
            }
          }
        s = SubStrCopy(line+i+fidlen+2,clslen);
        ccls = stringToSymbol(s);
        FreeMem(s);
      }
      if( line[k] != ']' )
      {
        fprintf(STDERR,"Warnung: %s missing closing bracket.\n",cfid);
        return;
      }
    }
  }
}

bool c_getline(void)
{
  if( scan_line != NULL ) FreeMem(scan_line);
  if ((scan_line = Line_get(SysIn)) == NULL)
  { 
    line = null_line; return False; 
  }
  else line = scan_line;
  lineno += 1;
  if (!Patched) patchhead();
  if (line[0] == '{') Shift = True;
  if (line[0] == '}') Shift = False;
  mainSeen |= beginswith("main") || beginswith("int main");
  return True;
}

static string convBlock(string szBlock)
/* C-Header-Block-Filter */
{ string      szResult, szTxt;
  Sink        pSnk;
  Scn_Stream  pStream;
  if (strstr(szBlock,"/*NOCONVERSION*/")) 
    return StrCopy(szBlock);
  pSnk = Sink_open();
  pStream = Stream_string(pScn, szBlock);
  Stream_defEofId(pStream, -1);
  Stream_defErrId(pStream,  0);
  Stream_defTokId(pStream, "Ide",   1);
  Stream_defTokId(pStream, "Inc",   2);
  Stream_defTokId(pStream, "Com",   3);
  Stream_defTokId(pStream, "Other", 4);
  for(Stream_next(pStream); Stream_ctid(pStream) >= 0; Stream_next(pStream))
  {
    szTxt = symbolToString(Stream_csym(pStream));
    if (Stream_ctid(pStream) == 1) 
    { 
      if( !strcmp(szTxt,"byte") )   Sink_printf(pSnk,"c_byte");
      else
      if( !strcmp(szTxt,"word") )   Sink_printf(pSnk,"c_word");
      else
      if( !strcmp(szTxt,"string") ) Sink_printf(pSnk,"c_string");
      else
      if( !strcmp(szTxt,"bool") )   Sink_printf(pSnk,"c_bool");
      else
      if( !strcmp(szTxt,"False") )  Sink_printf(pSnk,"C_False");
      else
      if( !strcmp(szTxt,"True") )   Sink_printf(pSnk,"C_True");
      else                          Sink_printf(pSnk,"%s",szTxt);
    }
    else Sink_printf(pSnk,"%s",szTxt);
  }
  szResult = Sink_close(pSnk);
  Stream_close(pStream);
  Stream_free(pStream);
  return szResult;
}

static bool Funpossible;

bool CppFunDef(void)
/* ob 'line' eine Methodendefinition einleitet */
{ int len = strlen(line), i;
  /* assumes isLetter(line[0]) */
  for( i=1; i < len-1; ++i ) 
  {
    if( line[i] == ':' && line[i+1] == ':' ) return( True );
    if( ! ( islower(line[i]) || 
            isupper(line[i]) ||
            isdigit(line[i]) ||
            line[i] == '*'   || 
            line[i] == '&'   || 
            line[i] == '_'   || 
            line[i] == ' '    ) ) return( False );
  }
  return( False );
}

bool BlockStart(void)
/* whether 'line' starts an interface block */
{
  Funpossible = False;
  if (Shift) return False;
  if (!OnOff) return False;
  if (beginswith("ExternalType"))
  {
    strncpy(line,"Abstract",8);
    return True; 
  }
  if (beginswith("ExternalDecl")) 
  {
    strncpy(line,"AbstractType",12);
    return True; 
  }
  //18.10.98 _DLL_EXPORT_ startet einen Interface-Block !
  if( beginswith("_DLL_EXPORT_") ||
      (
        ( islower(line[0]) || isupper(line[0]) )
        && !beginswith("ConcreteType")
        && !beginswith("ConcreteImp")
        && !beginswith("static")
        && !beginswith("struct")
        && !beginswith("union")
        && !beginswith("typedef")
        /* C++ - Rules */
        && !beginswith("class")
        && !beginswith("template")
        && !beginswith("inline")
        && !beginswith("namespace")
        && !beginswith("using")
        && !CppFunDef()
      )
    )
  { 
    //Funpossible = (line[strlen(line)-1] == ')'); 
    Funpossible = True; 
    return True; 
  }
  if (beginswith("#include") && !IncludeSeen)
  { IncludeSeen = True; return True; }
  if (beginswith("/*I-") || beginswith("/*I="))
  { line[2] = ' '; return True; }
  return False;
}

static string replaceDocBlock(string block)
{ MAP(symbol,symbol) m   = MAP_newPrimMap();
  string             res = (string)NULL;
  MAP_dfndom(m,stringToSymbol("<"),stringToSymbol("&lt;"));
  MAP_dfndom(m,stringToSymbol(">"),stringToSymbol("&gt;"));
  MAP_dfndom(m,stringToSymbol("/*NOCONVERSION*/"),stringToSymbol(""));
  res = Line_replace(block,m);
  MAP_freeMap(m);
  return res;
}

void writeDocFun
     (
       FILE* fp_doc, long idx, string funtyp, string funhdr, string funcom
     )
/* writes a function declaration to the current document file */
/*
   idx  = -1 ==> multi line function definition in 'funhdr' or
                 end of single line function definitions
   idx >=  0 ==> single line function definition [idx] in 
                   'funtyp', 'funhdr', 'funcom'
*/
{ string dfuntyp, dfunhdr, dfuncom, t, t1, t2, t3;
  if( idx == 0 || ( idx == -1 && funhdr != (string)NULL ) )
  {
    //if( idx == 0 ) fprintf(fp_doc,"<br>\n");
    fprintf(fp_doc,"<table border=0 cellspacing=20>\n");
  }
  if( funhdr != (string)NULL )
  { 
    dfunhdr = replaceDocBlock(funhdr);
    fprintf(fp_doc,"<tr valign=top>\n");
    fprintf(fp_doc,"<td bgcolor=\"#FFF8DC\" align=left>");
    if( funtyp != (string)NULL )
    {
      dfuntyp = replaceDocBlock(funtyp);
      fprintf(fp_doc,"<pre>%s ",dfuntyp);
      FreeMem(dfuntyp);
    }
    else
      fprintf(fp_doc,"<pre>");
    t1 = Line_withoutCCom(dfunhdr);
    t  = Line_clip(t1);
    if( t1 != dfunhdr ) FreeMem(t1);
    t1 = strstr(t,"#define ");
    if( t1 != (string)NULL ) *t1 = '\0';
    t2 = Line_getCFunNam(t);
    if( t1 != (string)NULL ) *t1 = '#';
    t1 = t;
    if( t2 != (string)NULL )
    {
      t3 = strstr(t1,t2);
      while( t < t3 )
      {
        fprintf(fp_doc,"%c",*t); t += 1;
      }
      fprintf(fp_doc,"<b>%s</b>",t2);
      fprintf(fp_doc,"%s</pre>\n",t3+strlen(t2));
    }
    else
    {
      fprintf(fp_doc,"%s</pre>\n",t1);
    }
    FreeMem(t1); 
    if( t2 != (string)NULL ) FreeMem(t2);
    fprintf(fp_doc,"<td bgcolor=\"#FFF0F5\" align=left>");
    if( funcom != (string)NULL )
    {
      dfuncom = replaceDocBlock(funcom);
      fprintf ( fp_doc,"%s\n",dfuncom);
      FreeMem(dfuncom);
    }
    else
    { 
      t1 = Line_withCComText(dfunhdr);
      if( t1 != (string)NULL ) 
      { Sink snk; PIT  itr;
        snk = Sink_open();
        itr = PIT_make(t1); PIT_sep(itr,"\n");
        while( ( t = PIT_read(itr) ) != NULL )
        { 
          if( *t == '*' )
            fprintf(fp_doc,"%s<br>\n",t+1);
          else
            Sink_printf(snk,"%s<br>\n",t);
        }
        t2 = Sink_close(snk);
        fprintf(fp_doc,"%s",t2);
        PIT_drop(itr);
        FreeMem(t1);
        FreeMem(t2);
      }
      else fprintf(fp_doc,"&nbsp;");
    }
    FreeMem(dfunhdr);
  }
  if( idx == -1 )
  {
    fprintf(fp_doc,"\n");
    fprintf(fp_doc,"</table>\n");
  }
}

void writeDocBlock(FILE* fp_doc, string block, bool forcedDocBlock)
/* writes 'block' to the current document file */
{ string dblock, t1, t2, t3, t;
  bool   flag = False;
  PIT    itr;
  if ( strstr(block,"AbstractType")     == block ||
       strstr(block,"AbstractHugeType") == block  )
  { 
    dblock = replaceDocBlock(block);
    fprintf(fp_doc,"<br>\n");
    fprintf(fp_doc,"<table border=0 cellspacing=10>\n");
    itr = PIT_make(dblock); PIT_sep(itr,"\n");
    while( ( t = PIT_read(itr) ) != NULL )
    { 
      t1 = strstr(t,"("),
      t2 = strrchr(t,')');
      if( t1 != (string)NULL && t2 != (string)NULL && t1 < t2 )
      {
        fprintf(fp_doc,"<TR valign=top>\n");
        fprintf(fp_doc,"<td align=left><b>");
        while( ( t1 += 1 ) < t2 )
        {
          fprintf(fp_doc,"%c",*t1);
        }
        fprintf(fp_doc,"</b>\n");
        fprintf(fp_doc,"<td align=left>");
        t1 = Line_withCComText(t);
        fprintf(fp_doc,"%s\n",t1==(string)NULL?"abstract type":t1);
        if( t1 != (string)NULL ) FreeMem(t1);
        fprintf(fp_doc,"\n");
      }
    }
    PIT_drop(itr);
    fprintf(fp_doc,"</table>\n");
    FreeMem(dblock);
  }
  else
  if (strstr(block,"#include") == block)
  { 
    dblock = replaceDocBlock(block);
    t1 = Line_withoutCCom(dblock);
    itr = PIT_make(t1); PIT_sep(itr,"\n");
    while( ( t = PIT_read(itr) ) != NULL )
    { 
      t2 = strstr(t,"#include");
      if( t2 != (string)NULL )
      {
        t2 = strstr(t2,"\"");
        if( t2 != (string)NULL )
        { Sink snk = Sink_open();
          fprintf(fp_doc,"<br><a href=\"");
          t2 += 1;
          while( *t2 != '.' && *t2 != '\0' )
          {
            Sink_putc(snk,*t2); t2 += 1;
          }
          t3 = Sink_close(snk);
          fprintf(fp_doc,"%s.htm\">#include \"%s.h\"</a>\n",t3,t3);
          FreeMem(t3);
        }
        else 
        { 
          fprintf(fp_doc,"<br>%s\n",t);
        }
      }
      else 
      {
        fprintf(fp_doc,"<br>%s\n",t);
      }
    }
    PIT_drop(itr);
    fprintf(fp_doc,"<br>\n");
    if( t1 != dblock ) FreeMem(t1);
    FreeMem(dblock);
  }
  else
  if (strstr(block,"/* -") == block || 
      (flag=(strstr(block,"/* =") == block)))
  { 
    fprintf
    (
      fp_doc,
      "<br><hr width=\"100%s\" size=%s><h2>%s<b>",
      "%", flag?"4":"2", flag?"<font color=\"#008B8B\">":""
    );
    t1 = block + 3;
    while( *t1 != '\0' && ( *t1 == '-' || *t1 == '=' ) )
      t1 += 1;
    t2 = t1 + strlen(t1);
    while( t2 > t1 && *t2 != '/' )
      t2 -= 1;
    t2 -= 3;
    while( t2 > t1 && ( *t2 == '-' || *t2 == '=' ) )
      t2 -= 1;
    while( t1 <= t2 )
    {
      if( *t1 == '<' )
        fprintf(fp_doc,"&lt;"); 
      else
      if( *t1 == '>' )
        fprintf(fp_doc,"&gt;"); 
      else
        fprintf(fp_doc,"%c",*t1); 
      t1 += 1;
    }
    fprintf(fp_doc,"</b>%s</h2>\n",flag?"</font>":"");
  }
  else
  { 
    if( forcedDocBlock )
    {
      dblock = replaceDocBlock(block);
      fprintf(fp_doc,"<br><pre>%s</pre>\n",dblock);
      FreeMem(dblock);
    }
  }
}

#define MaxFuncs 100
static struct
{
  string typ;
  string fun;
  string com;
  bool   ext;
  int    ltyp;
  int    lfun;
  int    lcom;
}
Func[MaxFuncs];
static int topFunc = 0;
static int ltyp    = 0;
static int lfun    = 0;
static int lcom    = 0;

void flushFuncs(void)
{ int i, xltyp, xlfun, xlcom;
  if (topFunc == 0) return;
  for (i = 0; i < topFunc; i++)
  {
    xltyp = (Func[i].ltyp==-1)?ltyp:Func[i].ltyp;
    xlfun = (Func[i].lfun==-1)?lfun:Func[i].lfun;
    xlcom = (Func[i].lcom==-1)?lcom:Func[i].lcom;
    xlcom = MAX(xlcom,MIN(LineLength-CommentMargin+1,LineLength-xltyp-1-xlfun-2)-6);
    if( Func[i].ext == False )
      fprintf
      (
        SysOut, "%s%*s %s;%*s/* %s%*s */\n",
        Func[i].typ, (int)(xltyp-strlen(Func[i].typ)),"",
        Func[i].fun, (int)(xlfun-strlen(Func[i].fun)+
                     LineLength-xltyp-1-xlfun-1-xlcom-6),"",
        Func[i].com, (int)(xlcom-strlen(Func[i].com)),""
      );
    else
      fprintf
      (
        SysOut,"%s%s;\n\n",
        ( i>0&&Func[i-1].ext==False ) ? "\n" : "", Func[i].fun
      );
    if( SysDoc != (FILE*)NULL )
    {
      writeDocFun(SysDoc,i,Func[i].typ,Func[i].fun,Func[i].com);
    }
    if( Func[i].typ != (string)NULL ) FreeMem(Func[i].typ); FreeMem(Func[i].fun); 
    if( Func[i].com != (string)NULL ) FreeMem(Func[i].com);
  }
  fprintf(SysOut,"\n");
  if( SysDoc != (FILE*)NULL )
  {
    writeDocFun(SysDoc,-1,(string)NULL,(string)NULL,(string)NULL);
  }
  topFunc = 0;
  ltyp    = 0;
  lfun    = 0;
  lcom    = 0;
}

void genFunExport(string CDecl)
{ string nam, t;
  if( strstr(CDecl,"_NO_DLL_EXPORT_") == CDecl )
    return;
  t = strstr(CDecl,"#define");
  if( t != (string)NULL ) *t = '\0';
  nam = Line_getCFunNam(CDecl);
  if( t != (string)NULL ) *t = '#';
  if( nam != (string)NULL )
  {
    fprintf(SysExp,"/EXPORT:%s\n",nam);
    FreeMem(nam);
  }
}

void pushFuncLine(string h, string c)
{ int i, xltyp, xlfun, xlcom;
  string typ, fun;
  if(topFunc >= MaxFuncs) flushFuncs();
  if( GenExp ) genFunExport(h);
  for (i = 0; h[i] != 0 && h[i] != ' ' && h[i] != '('; i++);
  if (h[i] != 0 && h[i] != '(')
  { h[i] = 0; typ = StrCopy(h); i+=1; }
  else
  { i = 0; typ = StrCopy(""); }
  while(h[i]==' ') i+=1;
  fun = StrCopy(h+i);
  FreeMem(h);
  xltyp = strlen(typ);
  xlfun = strlen(fun);
  xlcom = strlen(c);
  if (MAX(xltyp,ltyp)+1 + MAX(xlfun,lfun)+2 + MAX(xlcom,lcom)+6 > LineLength)
  {
    //flushFuncs();
    for( i=topFunc-1; i >= 0; --i )
    {
      if( Func[i].ltyp == -1 )
      {
        Func[i].ltyp = ltyp;
        Func[i].lfun = lfun;
        Func[i].lcom = lcom;
      }
    }
    ltyp    = 0;
    lfun    = 0;
    lcom    = 0;
  }
  ltyp = MAX(xltyp,ltyp);
  lfun = MAX(xlfun,lfun);
  lcom = MAX(xlcom,lcom);
  Func[topFunc].ltyp = -1;
  Func[topFunc].lfun = -1;
  Func[topFunc].lcom = -1;
  Func[topFunc].typ  = typ;
  Func[topFunc].fun  = fun;
  Func[topFunc].com  = c;
  Func[topFunc].ext  = False;
  topFunc += 1;
}

void pushExtFuncLine(string fun)
{ 
  if(topFunc >= MaxFuncs) flushFuncs();
  Func[topFunc].ltyp = -1;
  Func[topFunc].lfun = -1;
  Func[topFunc].lcom = -1;
  Func[topFunc].typ  = (string)NULL;
  Func[topFunc].fun  = StrCopy(fun);
  Func[topFunc].com  = (string)NULL;
  Func[topFunc].ext  = True;
  topFunc += 1;
}

void copyBlock(bool skipFirst, bool DocBlock, bool forcedDocBlock)
{ Sink   snk  = (Sink)NULL, ext = (Sink)NULL; 
  string temp = (string)NULL, s = (string)NULL, t;
  bool expflg = ( !skipFirst && beginswith("_DLL_EXPORT_") ),
       extflg = False;
  if (Funpossible && !skipFirst && (line[strlen(line)-1] == ')')) 
  /* a simple function definition? */
  { int lft, rgh;
    if( strlen(symbolToString(ApiSym)) > 0 && expflg )
    {
      s    = line + strlen("_DLL_EXPORT_");
      temp = Str_printf("_DLL_API_%s %s",symbolToString(ApiSym),s);
    }
    else temp = Str_printf("%s",line);
    if( CTypConv )
    {
      t = convBlock(temp); FreeMem(temp); temp = t;
    }
    if( c_getline() && CTypConv )
    {
      t = convBlock(line); FreeMem(line); scan_line = line = t;
    }
    if
    (
      strstr(temp,"//") != (string)NULL ||
      !(
         line[0] == '{' ||
         (beginswith("/*") && strcmp(line+strlen(line)-2,"*/") == 0)
       ) ||
       ( line[0] != '{' && strlen(temp) + strlen(line) + 2 > LineLength )
    )
    {
      goto Ordinary;
    }
    if(line[0] == '{')
      pushFuncLine(temp,StrCopy(""));
    else
    {
      for (lft = 2; line[lft] == ' '; lft+=1);
      for (rgh = strlen(line)-3; line[rgh] == ' '; rgh-=1);
      if (rgh < lft)
        rgh = lft-1;
      line[rgh+1] = 0;
      pushFuncLine(temp,StrCopy(line+lft));
    }
    while( line[0] != 0 && line[0] != '{') c_getline();
    return;
Ordinary:
    if( GenExp && line[0] != 0 )
    {
      if( line[0] == '{' ) genFunExport(temp);
      else
      {
        ext = Sink_open();
        Sink_printf(ext,"%s\n",temp);
      }
    }
    if (line[0] == 0 || line[0] == '{') 
    {
      t = Str_printf("%s\n",temp);
      if( line[0] == '{' ) 
      {
        pushExtFuncLine(t);
      }
      else
      {
        flushFuncs();
        fprintf(SysOut,"%s",t); 
        if( DocBlock )
          writeDocBlock(SysDoc,t,forcedDocBlock);
      }
      FreeMem(temp); FreeMem(t);
      return;
    }
  }
  /* multiline function headers, macro definitions, ... */
  snk = Sink_open();
  if( temp != (string)NULL )
  {
    Sink_printf(snk,"%s\n",temp);
    FreeMem(temp); 
  }
  if (!skipFirst) Sink_printf(snk,"%s\n",line);
  if( GenExp && Funpossible && !skipFirst &&
      !beginswith("/*") && !beginswith("//") && !beginswith("#") )
  {
    extflg = True;
    if( ext == (Sink)NULL )
      ext = Sink_open();
    Sink_printf(ext,"%s\n",line);
  }
  while(c_getline() && line[0] != 0 && line[0] != '{' )
  {
    if( extflg &=
        ( !beginswith("/*") && !beginswith("//") && !beginswith("#") ))
      Sink_printf(ext,"%s\n",line);
    if (beginswith("ExternalType"))
    {
      strncpy(line,"Abstract",8);
    }
    else
    if (beginswith("ExternalDecl")) 
    {
      strncpy(line,"AbstractType",12);
    }
    Sink_printf(snk,"%s\n",line);
  }
  temp = Sink_close(snk);
  if( GenExp && Funpossible && !skipFirst )
  {
    t = Sink_close(ext);
    if( line[0] == '{' ) genFunExport(t);
    FreeMem(t);
  }
  if( CTypConv )
  {
    t = convBlock(temp); FreeMem(temp); temp = t;
  }
  if( strlen(symbolToString(ApiSym)) > 0 && expflg && s == (string)NULL )
  {
    t = Str_printf
        (
          "_DLL_API_%s %s%s",
          symbolToString(ApiSym),temp + strlen("_DLL_EXPORT_"),
          ( line[0] == '{' ) ? "" : "\n"
        );
  }
  else 
    t = Str_printf("%s%s",temp,( line[0] == '{' ) ? "" : "\n");
  if( line[0] == '{' )
  {
    if( Funpossible && !skipFirst )
      pushExtFuncLine(t);
    else
    {
      flushFuncs();
      fprintf(SysOut,"%s;\n\n",t);
      if( DocBlock )
        writeDocBlock(SysDoc,t,forcedDocBlock);
    }
  }
  else
  {
    flushFuncs();
    fprintf(SysOut,"%s",t);
    if( DocBlock )
      writeDocBlock(SysDoc,t,forcedDocBlock);
  }
  FreeMem(temp); FreeMem(t);
}

void skipDoc(void)
{
  while(c_getline() && strcmp(line,"#endif") != 0) /* skip */;
}

void copyDoc
     (
       string szStartTagOri, string szStartTagNew, string szEndTag
     )
{ string dline, t1, t2;
  bool   pretag = ( strstr(szStartTagOri,"!!") != (string)NULL );
  if( SysDoc != (FILE*)NULL )
  {
    fprintf(SysDoc,"<br>");
    if( pretag ) fprintf(SysDoc,"<pre>");
  }
  if( !strcmp(szStartTagOri,szStartTagNew) )
  {
    fprintf(SysOut,"%s\n",line);
  }
  else
  {
    fprintf(SysOut,"%s",szStartTagNew);
    fprintf(SysOut,"%s\n",line+strlen(szStartTagOri));
  }
  t2 = strstr(line,szEndTag);
  if( SysDoc != (FILE*)NULL )
  {
    dline = pretag?replaceDocBlock(line):StrCopy(line);
    t2 = strstr(dline,szEndTag);
    if( t2 != (string)NULL)
    {
      t1 = dline+strlen(szStartTagOri);
      while( t1 < t2 )
      {
        fprintf(SysDoc,"%c",*t1); t1 += 1;
      }
      fprintf(SysDoc,"\n");
    }
    else
      fprintf(SysDoc,"%s\n",dline+strlen(szStartTagOri));
    FreeMem(dline);
  }
  if( t2 == (string)NULL)
  {
    while(c_getline() )
    {
      fprintf(SysOut,"%s\n",line);
      if( (t2=strstr(line,szEndTag)) != (string)NULL)
      {
        if( SysDoc != (FILE*)NULL )
        { 
          dline = pretag?replaceDocBlock(line):StrCopy(line);
          t1 = dline;
          t2 = strstr(dline,szEndTag);
          while( t1 < t2 )
          {
            fprintf(SysDoc,"%c",*t1); t1 += 1;
          }
          fprintf(SysDoc,"\n");
          FreeMem(dline);
        }
        break;
      }
      else
      if( SysDoc != (FILE*)NULL )
      {
        dline = pretag?replaceDocBlock(line):StrCopy(line);
        fprintf(SysDoc,"%s\n",dline);
        FreeMem(dline);
      }
    }
  }
  fprintf(SysOut,"\n");
  if( SysDoc != (FILE*)NULL )
  {
    if( pretag ) fprintf(SysDoc,"</pre>");
    fprintf(SysDoc,"\n");
  }
}

void copyToI(string szEndTag, bool forcedDocBlock)
{ Sink   pSnk = (Sink)NULL;
  string dline, szIBlock, szCnvIBlock;
  if( CTypConv ) pSnk = Sink_open();
  if( forcedDocBlock )
    fprintf(SysDoc,"<br><pre>\n");
  while(c_getline() && strcmp(line,szEndTag) != 0)
  {
    if( CTypConv ) Sink_printf(pSnk,"%s\n",line);
    else           
    {
      fprintf(SysOut,"%s\n",line);
      if( forcedDocBlock )
      {
        dline = replaceDocBlock(line);
        fprintf(SysDoc,"%s\n",dline);
        FreeMem(dline);
      }
    }
  }
  if( CTypConv )
  {
    szIBlock    = Sink_close(pSnk);
    szCnvIBlock = convBlock(szIBlock);
    fprintf(SysOut,"%s\n",szCnvIBlock);
    if( forcedDocBlock )
    {
      dline = replaceDocBlock(szCnvIBlock);
      fprintf(SysDoc,"%s\n",dline);
      FreeMem(dline);
    }
    FreeMem(szIBlock); FreeMem(szCnvIBlock);
  }
  else fprintf(SysOut,"\n");
  if( forcedDocBlock )
    fprintf(SysDoc,"</pre>\n");
}

void printCLinkageOn(void)
{
  fprintf(SysOut,"\n");
  fprintf(SysOut,"#ifdef __cplusplus\n");
  fprintf(SysOut,"extern \"C\" {\n");
  fprintf(SysOut,"#endif\n");
  fprintf(SysOut,"\n\n");
}

void convertText(void)
{ bool CLinkageFlag = False;
  Patched     = False;
  lineno      = 0;
  IncludeSeen = False;
  Funpossible = False;
  Shift       = False;
  OnOff       = True; /* INTERFACE_ON ! */
  mainSeen    = False;
  if (c_getline()) copyBlock(False,False,False);
  if (!Patched) fprintf(STDERR,"Warning: %s missing header comment.\n",cfid);
  Patched = True;
  fprintf(SysOut,"/* File generated by 'ctoh'. Don't change manually. */\n");
  fprintf(SysOut,"\n");
  fprintf(SysOut,"#ifndef %s_INCL\n",symbolToString(ccls));
  fprintf(SysOut,"#define %s_INCL\n",symbolToString(ccls));
  fprintf(SysOut,"\n\n");
  if( strlen(symbolToString(ApiSym)) > 0 )
  {
    fprintf(SysOut,"#ifndef _DLL_API_%s\n",symbolToString(ApiSym));
    fprintf(SysOut,"#ifdef _DLL_DFN_%s\n",symbolToString(ApiSym));
    fprintf
    (
      SysOut,"#define _DLL_API_%s _DLL_EXPORT_DECL_\n",symbolToString(ApiSym)
    );
    fprintf(SysOut,"#else\n");
    fprintf(SysOut,"#ifndef _NO_DLL_%s\n",symbolToString(ApiSym));
    fprintf(SysOut,"#define _DLL_API_%s _DLL_IMPORT_\n",symbolToString(ApiSym));
    fprintf(SysOut,"#endif\n");
    fprintf(SysOut,"#endif\n");
    fprintf(SysOut,"#endif\n");
    fprintf(SysOut,"\n");
  }
  while (c_getline())
  {
    if( CLinkageFlag == False && IncludeSeen == True )
    {
      printCLinkageOn(); CLinkageFlag = True;
    }
    if(BlockStart())
    {
      if( CLinkageFlag == False && Funpossible == True )
      {
        printCLinkageOn(); CLinkageFlag = True;
      }
      copyBlock(False,(SysDoc!=(FILE*)NULL),False);                 
    }
    else
    if(beginswith("/*!!")) 
    {
      flushFuncs();  
      copyDoc("/*!!","/*  ","*/");      
    }
    else
    if(beginswith("/*!")) 
    {
      flushFuncs();  
      copyDoc("/*!","/* ","*/");      
    }
    else
    if(strcmp(line,"/*INTERFACE*/")             == 0) 
      copyBlock(True,(SysDoc!=(FILE*)NULL),False);   
    else
    if(strcmp(line,"/*DOC_INTERFACE*/")         == 0) 
    {
      copyBlock(True,(SysDoc!=(FILE*)NULL),True);   
    }
    else
    if(strcmp(line,"/*INTERFACE_OFF*/")         == 0) 
    {
      OnOff = False; 
    }
    else
    if(strcmp(line,"/*INTERFACE_ON*/")          == 0) 
    {
      OnOff = True;  
    }
    else
    if(strcmp(line,"/*INTERFACE_GROUP*/")       == 0) 
    {
      flushFuncs();  
    }
    else
    if(strcmp(line,"#ifdef INTERFACE")          == 0) 
    {
      flushFuncs();  
      copyToI("#endif",False);  
    }
    else
    if(strcmp(line,"#ifdef DOC_INTERFACE")      == 0) 
    {
      flushFuncs();  
      copyToI("#endif",(SysDoc!=(FILE*)NULL));  
    }
    else
    if(strcmp(line,"/*INTERFACE_COPY_ON*/")     == 0) 
    {
      flushFuncs();  
      copyToI("/*INTERFACE_COPY_OFF*/",False); 
    }
    else
    if(strcmp(line,"/*DOC_INTERFACE_COPY_ON*/") == 0) 
    {
      flushFuncs();  
      copyToI("/*DOC_INTERFACE_COPY_OFF*/",(SysDoc!=(FILE*)NULL)); 
    }
    else
    if(strcmp(line,"#ifdef DOCUMENT")           == 0) 
    {
      skipDoc();
    }
    else
    if( CLinkageFlag == False && strcmp(line,"/*INTERFACE_LINKAGE_ON*/") == 0 )
    {
      flushFuncs();  
      printCLinkageOn(); CLinkageFlag = True;
    }
  }
  flushFuncs();
  fprintf(SysOut,"\n");
  if( CLinkageFlag == True )
  {
    fprintf(SysOut,"#ifdef __cplusplus\n");
    fprintf(SysOut,"}\n");
    fprintf(SysOut,"#endif\n\n");
  }
  fprintf(SysOut,"#endif\n");
}

#define tnam "____ctoh.___"

ConcreteType( ModuleInfo )
{
  symbol Path; /* only in 'newmap' ( C-Path; Base is dom ) */
  symbol hext;
  symbol scls;
  long   Ctim;
  long   Htim;
  short  prog; /* mainflag */
};

ModuleInfo mi_Copy(ModuleInfo mi)
{ ModuleInfo res = New(ModuleInfo);
  res->Path = mi->Path;
  res->hext = mi->hext;
  res->scls = mi->scls;
  res->Ctim = mi->Ctim;
  res->Htim = mi->Htim;
  res->prog = mi->prog;
  return res;
}

void mi_Free(ModuleInfo mi)
{
  FreeMem(mi);
}

MAPTY                   glotyp;
MAPTY                   clstyp;
MAP(symbol, ModuleInfo) newmap;
MAP(symbol, ModuleInfo) oldmap;
MAP(symbol, HS_Set)     clsmap;
MAP(symbol, long  )     oldtim;
MAP(symbol, long  )     newtim;
int errcnt;

bool validModule(symbol Cpath, symbol BaseSy, long Ctime, long Htime)
{ bool res = False;
  if (MAP_defined(oldmap,BaseSy))
  { ModuleInfo mi = MAP_apply(ModuleInfo,oldmap,BaseSy);
    res  = (mi->Path == Cpath && mi->Ctim == Ctime && mi->Htim == Htime);
    if (res)
    {
      ccls = mi->scls; mainSeen = mi->prog;
    }
    mi_Free(mi);
  }
  return res;
}

void addModule(symbol ModSy, ModuleInfo mi)
{
  if (MAP_defined(newmap,ModSy))
  { ModuleInfo mo = MAP_apply(ModuleInfo,newmap,ModSy);
    fprintf
    (
      STDERR,"Module [%s.c(xx)] both in dictionary '%s' and in '%s'.\n",
      symbolToString(ModSy),
      symbolToString(mi->Path),
      symbolToString(mo->Path)
    );
    mi_Free(mo);
    errcnt += 1;
    MAP_upddom(newmap,ModSy,mi);
  }
  else MAP_dfndom(newmap,ModSy,mi);
}

void PutMi(void)
/* put module info to [$PRJ/ctoh.cth] */
{ symbol fsy; MAPIT itr;
  putBgn("PRJ","ctoh.cth","");
  putHeader("[ctoh.cth] Binary image for 'ctoh'\n","cth",3,0);
  putWord((short)MAP_count(newmap));
  MAP_forItr(fsy,itr,newmap)
  { ModuleInfo mi = MAP_apply(ModuleInfo,newmap,fsy);
    putSymbol(fsy);
    PUT_REFERENCE(mi->Path,putSymbol); 
    PUT_REFERENCE(mi->hext,putSymbol); 
    PUT_REFERENCE(mi->scls,putSymbol); 
    putLong(mi->Ctim);
    putLong(mi->Htim);
    putWord(mi->prog);
    mi_Free(mi);
  }
  putWord((short)MAP_count(newtim));
  MAP_forItr(fsy,itr,newtim)
  { long tim = MAP_apply(long,newtim,fsy);
    putSymbol(fsy);
    putLong(tim);
  }
  putEnd();
}

void GetMi(void)
/* get module info from [$PRJ/ctoh.cth] */
{ short i,size;
  { string tmp = MkPath("PRJ","ctoh.cth","",'p');
    if (!IsPath(tmp)) { FreeMem(tmp); return; } else FreeMem(tmp);
  }
  getBgn("PRJ","ctoh.cth","");
  getHeader("cth",3,0);
  getWord(&size);
  for (i = 0; i < size; i++)
  { symbol fsy; ConcreteImp(ModuleInfo) mi;
    getSymbol(&fsy);
    GET_REFERENCE(&mi.Path,getSymbol);
    GET_REFERENCE(&mi.hext,getSymbol);
    GET_REFERENCE(&mi.scls,getSymbol);
    getLong(&mi.Ctim);
    getLong(&mi.Htim);
    getWord(&mi.prog);
    MAP_dfndom(oldmap,fsy,&mi);
  }
  getWord(&size);
  for (i = 0; i < size; i++)
  { symbol fsy; long tim;
    getSymbol(&fsy);
    getLong(&tim);
    MAP_dfndom(oldtim,fsy,tim);
  }
  getEnd();
}

bool FileEqual(string fna, string fnb)
/* whether files 'fna' and 'fnb' are binary equal */
{ FILE* fa = OpnFile(fna,"rb");
  FILE* fb = OpnFile(fnb,"rb");
  int ca, cb;
  for
  (
    ca = fgetc(fa), cb = fgetc(fb);
    ca != EOF && cb != EOF && ca == cb;
    ca = fgetc(fa), cb = fgetc(fb)
  );
  fclose(fa); fclose(fb);
  return ca == cb;
}

/* ----------------- Handling Multiple Implementations --------------------- */

string normalize_header_line(string line, string cfid, bool *hl)
/* returns a line, normalizing header line if '*hl == True' */
{
  if (!*hl || line == NULL) return line;
  { int i,j,k,m, len = strlen(line), blen = strlen(cfid); string ext;
    for (i = 0; i < len; i++)
    {
      if (strncmp(cfid,line+i,blen) == 0)
      {
        if (line[i+blen] != '(') return line;
        for( j=blen-1; j > 0 && line[i+j] != '.' ; --j );
        ext = SubStrCopy(line+i+j,blen-j);
        for( j=0; line[i+blen+1+j] != 0 && line[i+blen+1+j] != ')'; ++j )
          line[i+j] = line[i+blen+1+j];
        for( k=0; k < strlen(ext); k++)
          line[i+j+k] = ext[k];
        line[i+j+k] = ']';
        for(m = 1; m < j+2; m++)
          line[i+j+k+m] = ' ';
        FreeMem(ext);
        *hl = False;
        return line;
      }
    }
  }
  return line;
}

string Line_get_normal(FILE* f, string cfid, bool *hl)
{
  return normalize_header_line(Line_get(f), cfid, hl);
}

bool FileNormalEqual(string fna, string cna, string fnb, string cnb)
/* whether files 'fna' and 'fnb' are binary equal */
{ FILE* fa = OpnFile(fna,"rt");
  FILE* fb = OpnFile(fnb,"rt");
  string sa, sb; bool ha = True, hb = True; long lna=1,lnb=1;
  bool res;
  for
  (
    sa = Line_get_normal(fa,cna,&ha), sb = Line_get_normal(fb,cnb,&hb);
    sa != NULL && sb != NULL && strcmp(sa,sb) == 0;
    sa = Line_get_normal(fa,cna,&ha), sb = Line_get_normal(fb,cnb,&hb)
  )
  {
    FreeMem(sa); FreeMem(sb); lna+=1; lnb+=1;
  };
  fclose(fa); fclose(fb);
  res = ((sa == sb) || strcmp(sa,sb) == 0);
  if (sa != NULL) FreeMem(sa);
  if (sb != NULL) FreeMem(sb);
  if (!res)
  {
    fprintf(STDERR,"files %s(%ld), %s(%ld) differ.\n",fna,lna,fnb,lnb);
    errcnt += 1;
  }
  return res;
}

void FileNormalize(string fna, string cna, string fnb)
/* normalizes header of file 'fna' */
{ FILE* fa; FILE* fb;
  string sa; bool ha = True;
  if (strcmp(fna,fnb) == 0) return;
  fa = OpnFile(fna,"rt");
  fb = OpnFile(tnam,"wt");
  for
  (
    sa = Line_get_normal(fa,cna,&ha);
    sa != NULL;
    sa = Line_get_normal(fa,cna,&ha)
  )
  {
    fprintf(fb,"%s\n",sa);
    FreeMem(sa);
  };
  fclose(fa); fclose(fb);
  if (IsPath(fnb) && FileEqual(fnb,tnam))
    remove(tnam);
  else
  {
    remove(fnb); rename(tnam,fnb);
    fprintf(STDOUT,"-> %s\n",fnb);
  }
}

void editClass(symbol sclass, symbol BaseSy)
/* adds/updates current class 'sclass' */
{ HS_Set cset;
  if( ! MAP_defined(clsmap,sclass) )
  {
    cset = HS_CREATE_ADTSET(symbol);
    MAP_dfndom(clsmap,sclass,cset);
    MAP_dfndom
    (
      newtim,
      sclass,
      MAP_defined(oldtim,sclass)?MAP_apply(long,oldtim,sclass):0L
    );
  }
  else cset = MAP_apply(HS_Set,clsmap,sclass);
  HS_SET_ELM(BaseSy,cset);
}

void multipleH(bool Force)
/* handles multiple Implementations */
{ MAPIT itr; symbol dom; HMP_Rng rng;
  MAP_forItrAsg(dom,rng,itr,clsmap)
  { HS_Itr hit; symbol elm; long youngest = 0L; bool ok = True;
    symbol hext = (symbol)NULL; symbol firstH = (symbol)NULL; string s1;
    HS_FORALL(elm,hit,rng)
    { ModuleInfo mi = MAP_apply(ModuleInfo,newmap,elm);
      youngest = MAX(youngest,mi->Htim);
      if( hext == (symbol)NULL ) hext = mi->hext;
      else
      {
        if( hext != mi->hext )
        {
          fprintf
          (
            STDERR,"different Header Types for Class '%s'.\n",
            symbolToString(dom)
          );
          errcnt += 1;
        }
      }
      if( firstH == (symbol)NULL ) firstH = (symbol)elm;
      FreeMem(mi);
    }
    s1 = MkPath("HPATH",symbolToString(dom),symbolToString(hext),'e');
    if
    (
      Force                                       ||
      pgmtim        <= youngest                   ||
      !IsPath(s1)                                 ||
      PathMTime(s1) != MAP_apply(long,newtim,dom)
    )
    { string s3=Str_printf("%s%s",symbolToString(firstH),symbolToString(hext));
      string s4=Str_printf("%s%s",symbolToString(dom),symbolToString(hext));
      string s2 = MkPath
                  (
                    "HPATH",symbolToString(firstH),symbolToString(hext),'e'
                  );
      FileNormalize(s2,s3,s1);
      HS_FORALL(elm,hit,rng)
      { string s5 = MkPath
                    (
                      "HPATH",symbolToString(elm),symbolToString(hext),'e'
                    );
        string s6 = Str_printf("%s%s",symbolToString(elm),symbolToString(hext));
        ok &= FileNormalEqual(s1,s4,s5,s6);
        FreeMem(s5); FreeMem(s6);
      }
      FreeMem(s2); FreeMem(s3); FreeMem(s4);
    }
    MAP_upddom(newtim,dom,ok?PathMTime(s1):-1L);
    FreeMem(s1);
  }
}

FILE* BeginDocFile(string Dpath, string BaseName, string Ext)
{ FILE* fp_doc = (FILE*)NULL;
  if( *Dpath != '\0' )
  { string dnam, title, tmp;
    title = Com_GetEx(cnam);
    tmp   = strstr(title,"#");
    if( tmp == (string)NULL )
    {
      dnam = MkPath(Dpath,BaseName,".htm",'d');
      fp_doc = OpnFile(dnam,"w");
      if( fp_doc != (FILE*)NULL )
      {
        fprintf(fp_doc,"%s\n",HTML_DOCTYPE);
        fprintf
        (
          fp_doc, 
          "<html>\n<head>\n<title>[%s.h] %s</title>\n</head>\n<body bgcolor=white>\n",
          BaseName,title
        );
        fprintf
        (
          fp_doc, "<h1><font color=\"#008B8B\">[%s.h] %s</font></h1>\n",
          BaseName,title
        );
      }
      FreeMem(dnam);
    }
    else
    {
      *tmp = '\0';
      if( strlen(title) == 0 )
        title = BaseName;
      dnam = MkPath(Dpath,title,".htm",'d');
      fp_doc = OpnFile(dnam,"w");
      if( fp_doc != (FILE*)NULL )
      {
        fprintf(fp_doc,"%s\n",HTML_DOCTYPE);
        fprintf
        (
          fp_doc, 
          "<html>\n<head>\n<title>[%s.h] %s</title>\n",
          title,tmp+1
        );
        fprintf(fp_doc,"<meta name=\"robots\" content=\"noindex\">\n");
        fprintf(fp_doc,"</head>\n");
        fprintf(fp_doc,"<body bgcolor=white>\n");
        fprintf
        (
          fp_doc, "<h1><font color=\"#008B8B\">[%s.h] %s</font></h1>\n",
          title,tmp+1
        );
        if( strlen(DROOT) > 0 )
          fprintf
          (
            fp_doc, 
            "<h2><font color=\"#008B8B\"><a href=\"%s\">contents</a></font></h2><br>\n",
            DROOT
          );
      }
      FreeMem(dnam);
    }
  }
  return fp_doc;
}

void EndDocFile(FILE* fp_doc)
{
  if( fp_doc != (FILE*)NULL )
  {
    fprintf(fp_doc,"\n</body>\n</html>\n");
    fclose(fp_doc);
  }
}

void htod
     (
       symbol HpathSy, string BaseName, string Ext, string Dpath
     )
{ 
  string Hpath   = symbolToString(HpathSy), dline, t, t1; 
  bool   header  = True,
         comblk  = False,
         pretag  = False;
  Sink   snk     = (Sink)NULL;
  long   lineno  = 0;
  cnam   = MkPath(Hpath,BaseName,Ext,'d');
  SysIn  = OpnFile(cnam,"r");
  SysDoc = BeginDocFile(Dpath,BaseName,Ext);
  while ((line = Line_get(SysIn)) != (string)NULL)
  {
    if( header )
    {
      if( line[0] == '\0' ) header = False;
    }
    else
    if( comblk )
    {
      dline = pretag?replaceDocBlock(line):StrCopy(line);
      if( (t1=strstr(dline,"*/")) != (string)NULL ) 
      {
        t = dline;
        while ( t < t1 )
        {
          Sink_printf(snk,"%c",*t); ++t;
        }
        Sink_printf(snk,"\n");
        t1 = Sink_close(snk);
        fprintf(SysDoc,"%s",t1);
        if( pretag ) fprintf(SysDoc,"</pre>");
        FreeMem(t1);
        comblk = False;
      }
      else Sink_printf(snk,"%s\n",dline);
      FreeMem(dline);
    }
    else
    {
      if( beginswith("/*!") ) 
      {
        pretag = ( beginswith("/*!!") ); 
        dline  = pretag?replaceDocBlock(line):StrCopy(line);
        if( (t1=strstr(dline,"*/")) != (string)NULL ) 
        {
          fprintf(SysDoc,"<p>");
          t = dline + 3 + pretag;
          while ( t < t1 )
          {
            fprintf(SysDoc,"%c",*t); ++t;
          }
        }
        else 
        {
          snk = Sink_open();
          if( pretag ) 
            Sink_printf(snk,"<pre>%s\n",dline+4);
          else
            Sink_printf(snk,"<p>%s\n",dline+3);
          comblk = True;
        }
        FreeMem(dline);
      }
      else
      if( beginswith("#ifndef") && strstr(line,"_INCL") != (string)NULL )
        /* skip */;
      else
      if( beginswith("#define") && strstr(line,"_INCL") != (string)NULL )
        /* skip */;
      else
      if( strstr(line,"/*_INCL*/") != (string)NULL ||
          strstr(line,"//_INCL")   != (string)NULL  )
        /* skip */;
      else
      if( beginswith("/* -")     || beginswith("/* =") ||
          beginswith("#include") || beginswith("AbstractType")  )
      {
        dline = replaceDocBlock(line);
        writeDocBlock(SysDoc, dline, True);
        FreeMem(dline);
      }
      else
      {
        dline = replaceDocBlock(line);
        fprintf(SysDoc,"<pre>%s</pre>",dline);
        FreeMem(dline);
      }
    }
    ++lineno;
    FreeMem(line);
  }
  EndDocFile(SysDoc);
  fclose(SysIn);
  FreeMem(cnam);
}

void ctoh
     (
       symbol CpathSy, string Hpath, string BaseName, string Ext, 
       bool Force, string Dpath
     )
{ string Cpath = symbolToString(CpathSy); string HExt = StrCopy(Ext);
  symbol BaseSy = stringToSymbol(BaseName);
  long Ctime, Htime; ConcreteImp(ModuleInfo) mi;
  ccls    = BaseSy;
  cnam    = MkPath(Cpath,BaseName,Ext,'d');
  HExt[1] = 'h';
  hnam    = MkPath(Hpath,BaseName,HExt,'d');
  cfid    = Str_printf("%s%s",BaseName,Ext);
  lnam    = StrToUpper(StrCopy(BaseName));
  Ctime   = PathMTime(cnam);
  Htime   = IsPath(hnam) ? PathMTime(hnam) : 0L;
  if (validModule(CpathSy,BaseSy,Ctime,Htime) && !Force) goto Done;
  SysDoc  = BeginDocFile(Dpath,BaseName,Ext);
  SysIn   = OpnFile(cnam,"r");
  SysOut  = OpnFile(tnam,"w");
  if( GenExp )
  {
    enam   = MkPath(Hpath,BaseName,".exp",'d');
    SysExp = OpnFile(enam,"w");
  }
  convertText();
  if( GenExp )
  {
    fclose(SysExp);
    FreeMem(enam);
  }
  fclose(SysOut);
  fclose(SysIn);
  EndDocFile(SysDoc);
  if (mainSeen)
  {
    if( ccls != BaseSy )
    {
      fprintf(STDERR,"Program [%s.c(xx)] with multiple Headers.\n",BaseName);
      errcnt += 1;
    }
    remove(tnam);
  }
  else
  {
    if (!Force && Htime != 0 && FileEqual(hnam,tnam)) remove(tnam);
    else
    {
      remove(hnam); rename(tnam,hnam);
      Htime = PathMTime(hnam);
      fprintf(STDOUT,"-> %s%s\n",BaseName,HExt);
    }
  }
Done:
  mi.Path = CpathSy; mi.hext = stringToSymbol(HExt); mi.scls = ccls;
  mi.Ctim = Ctime; mi.Htim = Htime; mi.prog = mainSeen;
  addModule(BaseSy,&mi);
  if( !mainSeen ) editClass(ccls,BaseSy);
  FreeMem(cnam); FreeMem(hnam); FreeMem(cfid); FreeMem(lnam); FreeMem(HExt);
}

void RemoveOldH(void)
/* removes all H-files in [$HPATH] no occuring in [ctoh.cth] */
{
  DII dii; PIT pit; string srcpath;
  pit = PIT_make(CTX_EVAL(string,"HPATH"));
  while( ( srcpath = PIT_read(pit) ) != NULL )
  {
    DII_FORALL(dii,srcpath,"*.h")
    { string base = DII_get_base(dii);
      if( !MAP_defined(newmap,stringToSymbol(base)) &&
          !MAP_defined(clsmap,stringToSymbol(base))  )
      { string tmp = Str_printf("%s/%s.h",srcpath,base);
        printf("-- %s.h\n",base);
        remove(tmp); FreeMem(tmp);
      }
      FreeMem(base);
    }
    DII_FORALL(dii,srcpath,"*.hxx")
    { string base = DII_get_base(dii);
      if( !MAP_defined(newmap,stringToSymbol(base)) &&
          !MAP_defined(clsmap,stringToSymbol(base))  )
      { string tmp = Str_printf("%s/%s.hxx",srcpath,base);
        printf("-- %s.hxx\n",base);
        remove(tmp); FreeMem(tmp);
      }
      FreeMem(base);
    }
  }
  PIT_drop(pit);
}

int main(int argc, string argv[])
{ DII dii; PIT pit; 
  string srcpath, srclib, tmp;
  MAPIT itr; HMP_Dom dom; HMP_Rng rng;
  CTX_init_ctoh(argc,argv);
  bug0(strcmp(CTX_EVAL(string,"PRJ"),""),"Variable PRJ undefiniert");
  initSymbols();
  MAP_init();
  pgmtim = time(NULL);
  errcnt = 0;
  glotyp = MAP_newTyp(primCopy,primFree,primEqual,primHash, mi_Copy,mi_Free);
  clstyp = MAP_newTyp(primCopy,primFree,primEqual,primHash, primCopy,primFree);
  newmap = MAP_newMap( glotyp );
  oldmap = MAP_newMap( glotyp );
  clsmap = MAP_newMap( clstyp );
  oldtim = MAP_newMap( clstyp );
  newtim = MAP_newMap( clstyp );
  GetMi();
  if( CTypConv ) Scn_get_ccnv(&pScn);
  pit = PIT_make(CTX_EVAL(string,"CPATH"));
  while( ( srcpath = PIT_read(pit) ) != NULL )
  { symbol psy;
    ApiSym = stringToSymbol(GenApi);
    tmp    = strstr(srcpath,"~");
    if( tmp != (string)NULL )
    {
      srclib  = srcpath;
      srcpath = tmp + 1;
      *tmp    = '\0';
      ApiSym  = stringToSymbol(srclib);
    }
    psy = stringToSymbol(srcpath);
    DII_FORALL(dii,srcpath,"*.c")
    { string base = DII_get_base(dii);
      ctoh
      (
        psy,
        CTX_EVAL(string,"HPATH"),
        base,
        ".c",
        CTX_EVAL(bool  ,"force"),
        CTX_EVAL(string,"DPATH")
      );
      FreeMem(base);
    }
    DII_FORALL(dii,srcpath,"*.cxx")
    { string base = DII_get_base(dii);
      ctoh
      (
        psy,
        CTX_EVAL(string,"HPATH"),
        base,
        ".cxx",
        CTX_EVAL(bool  ,"force"),
        CTX_EVAL(string,"DPATH")
      );
      FreeMem(base);
    }
    DII_FORALL(dii,srcpath,"*.cpp")
    { string base = DII_get_base(dii);
      ctoh
      (
        psy,
        CTX_EVAL(string,"HPATH"),
        base,
        ".cpp",
        CTX_EVAL(bool  ,"force"),
        CTX_EVAL(string,"DPATH")
      );
      FreeMem(base);
    }
    if( *(CTX_EVAL(string,"DPATH")) != '\0' )
    {
      DII_FORALL(dii,srcpath,"*.h")
      { string base = DII_get_base(dii);
        htod
        (
          psy, base, ".h", CTX_EVAL(string,"DPATH")
        );
        FreeMem(base);
      }
    }
  }
  PIT_drop(pit);
  multipleH(CTX_EVAL(bool,"force"));
  PutMi();
  if( CTypConv ) Scn_free(pScn);
  RemoveOldH();
  MAP_freeMap(newmap);
  MAP_freeMap(oldmap);
  MAP_forItrAsg(dom,rng,itr,clsmap) HS_DROP_SET(rng);
  MAP_freeMap(clsmap);
  MAP_freeMap(oldtim);
  MAP_freeMap(newtim);
  MAP_freeTyp(glotyp);
  MAP_freeTyp(clstyp);
  MAP_quit();
  freeSymbols();
  CTX_quit();
  if (errcnt > 0)
  {
    fprintf(STDERR,"total %d error(s).\n",errcnt);
    STD_ERREXIT;
  }
  BUG_CORE;
  return(0);
}
