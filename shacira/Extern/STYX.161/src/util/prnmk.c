/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [prnmk.c]                a simple make facility                          */
/*                                                                          */
/* Copyright (c) 1993 by Dölle, Manns.                                      */
/* ------------------------------------------------------------------------ */

#include "styconf0.h"

#define HERE printf("%s(%d) : here\n",__FILE__,__LINE__);

#define CMDLEN       30000
#define BUFLEN        1024

#define MaxTargets    100
#define MaxSources    300
#define MaxIncludes   300
#define MaxLibraries  100
#define MaxIncDirs    100
#define MaxLibDirs    100
#define MaxParameters 100
#define MaxCommands   500
#define MaxCmdTypes   100

#define bool   int
#define False  0
#define True   1

typedef char   *string;

static  string fileid = (string)NULL;
static  string rules  = (string)NULL;
static  int    lineno = 0;
static  FILE   *SysIn = (FILE*)NULL;

/* the following variable reflect the state */

static int cnt_targets    = 0;
static int cnt_sources    = 0;
static int cnt_includes   = 0;
static int cnt_libraries  = 0;
static int cnt_incdirs    = 0;
static int cnt_libdirs    = 0;
static int cnt_parameters = 0;
static int cnt_commands   = 0;
static int cnt_cmdtypes   = 0;

static long goal_date; /* minimum date of all goals in rule */
static long need_date; /* maximum date of all needs in rule */

static string targets[MaxTargets];
static string sources[MaxSources];
static string includes[MaxIncludes];
static string libraries[MaxLibraries];
static string incdirs[MaxIncDirs];
static string libdirs[MaxLibDirs];
static string parameters[MaxParameters];
static string commands[MaxCommands];
static string cmdtypes[MaxCmdTypes];

static string fidToMsDos(string s)
{ static char buf[BUFLEN+1]; unsigned int i;
  for (i = 0; i < strlen(s); i++)
    buf[i] = (s[i] == '/' ? '\\' : s[i]);
  buf[i] = 0;
  return buf;
}

static string fidToPath(string s)
{ static char buf[BUFLEN+1]; 
  int i, l = strlen(s);
  strcpy(buf,s);
  for (i=l-1; i >= 0 && buf[i] != '\\' && buf[i] != '/'; i--);
  buf[i] = 0;
  return buf;
}

static string fidToBase(string s)
{ static char buf[BUFLEN+1]; 
  int i, j, l = strlen(s);
  for (i=l-1; i >= 0 && s[i] != '\\' && s[i] != '/'; i--);
  for(j=0,++i; i < l; ++i, ++j )
    buf[j] = s[i];
  buf[j] = 0;
  for (i=strlen(buf)-1; i >= 0 && buf[i] != '.'; i--);
  buf[i] = 0;
  return buf;
}

static string fidToSuffix(string s)
{ static char buf[BUFLEN+1]; 
  int i, j, l = strlen(s);
  for (j=0,i=l-1; i >= 0 && buf[i] != '.'; j++,i--);
    buf[j] = s[i];
  buf[j] = 0;
  return buf;
}

static string expandFid(string s)
{ static char buf[BUFLEN+1];
  char tmp[BUFLEN+1];
  string t = buf;
  int i, j, k=0, l = strlen(s);
  if( l + 1 >= BUFLEN )
  {
    fprintf(stderr,"error: path buffer too small.\n");
    exit(1);
  }
  for (i=0, j=0; i < l; i++)
  {
    if( s[i] != '%' ) 
    {
      t[j] = s[i]; ++j;
    }
    else
    {
      if( t == buf ) 
      {
        t = tmp; tmp[0] = '\0'; k=j; j=0;
      }
      else
      {
        t[j]   = '\0';
        buf[k] = '\0';
        if( getenv(t) != (string)NULL && strlen(getenv(t)) <= BUFLEN )
          strcpy(t,getenv(t));
        else
        {
          fprintf(stderr,"error: environment evaluation for '%s'.\n",t);
          exit(1);
        }
        if( strlen(t) + l + 1 >= BUFLEN )
        {
          fprintf(stderr,"error: path buffer too small.\n");
          exit(1);
        }
        strcat(buf,t);
        j = strlen(buf); k=0;
        t = buf;
      }
    }
  }
  buf[j] = 0;
  return buf;
}

long filetime_x(string path)
{ struct stat statbuf;
  return (stat(path,&statbuf) == 0) ? statbuf.st_mtime : 0L;
}

long filetime(string path)
{ long res = filetime_x(path);
  return res;
}

/* -------------------------- command processing ---------------------------- */

static string CmdCharCat(string cmdbuf, char val)
{ int len = strlen(cmdbuf);
  if( len + 1 >= CMDLEN )
  {
    fprintf(stderr,"error: command buffer too small.\n");
    exit(1);
  }
  cmdbuf[len]   = val;
  cmdbuf[len+1] = '\0';
  return cmdbuf;
}

static string CmdStrCat(string cmdbuf, string val)
{
  if( strlen(cmdbuf) + strlen(val) >= CMDLEN )
  {
    fprintf(stderr,"error: command buffer too small.\n");
    exit(1);
  }
  return strcat(cmdbuf,val);
}

static string getMacroByIndex(int idx)
{ static char buf[BUFLEN+1]; int i, j;
  buf[0] = '\0';
  for( i=j=0; i < cnt_commands; ++i )
  { string cmd = commands[i];
    if( *cmd == 'M' )
    {
      if( j == idx )
      {
        cmd += 1;
        while(*cmd == ' ' && *cmd != '\0') cmd += 1;
        return strcpy(buf,cmd);
      }
      ++j;
    }
  }
  return buf;
}

static string getParameter(string name)
{ static char buf[BUFLEN+1]; int i;
  buf[0] = '\0';
  for( i=0; i < cnt_parameters; ++i )
  { string par = parameters[i];
    if( strstr(par,name) == par )
      return strcpy(buf,par+strlen(name)+1);
  }
  return buf;
}

static string getElement(string* list, int cnt, int idx)
{ static char buf[BUFLEN+1];
  buf[0] = '\0';
  if( idx >= 0 && idx < cnt )
  {
    return strcpy(buf,list[idx]);
  }
  return buf;
}

static int getList(string cmdbuf, string** list, int* cnt)
{
  if( strstr(cmdbuf,"<T>") == cmdbuf )
  {
    *list = targets; *cnt = cnt_targets; return 3;
  }
  else
  if( strstr(cmdbuf,"<S>") == cmdbuf )
  {
    *list = sources; *cnt = cnt_sources; return 3;
  }
  else
  if( strstr(cmdbuf,"<I>") == cmdbuf )
  {
    *list = includes; *cnt = cnt_includes; return 3;
  }
  else
  if( strstr(cmdbuf,"<L>") == cmdbuf )
  {
    *list = libraries; *cnt = cnt_libraries; return 3;
  }
  else
  if( strstr(cmdbuf,"<DI>") == cmdbuf )
  {
    *list = incdirs; *cnt = cnt_incdirs; return 4;
  }
  else
  if( strstr(cmdbuf,"<DL>") == cmdbuf )
  {
    *list = libdirs; *cnt = cnt_libdirs; return 4;
  }
  else
  if( strstr(cmdbuf,"<P>") == cmdbuf )
  {
    *list = parameters; *cnt = cnt_parameters; return 3;
  }
  else return 0;
}

// forward
static int evalStrExp(string cmdbuf, string resbuf); 
static int evalNumExp(string cmdbuf, int* result);
static int evalBoolExp(string cmdbuf, bool* result);

static int evalSpace(string cmdbuf)
// RC = Anzahl verarbeiteter Bytes
{ string s = cmdbuf; int pos = 0;
  while( s[pos] == ' ' || s[pos] == '\n' ) pos += 1;
  return pos;
}

static int skipArg(string cmdbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ string s = cmdbuf, t, v; 
  int pos = -1, tmp = 0;
  t = strstr(s,"<A>");
  if( t != (string)NULL )
  {
    s = t + 3; ++tmp;
    while( True )
    {
      v = strstr(s,"</A>");
      if( v == (string)NULL ) break;
      t = strstr(s,"<A>");
      if( t == (string)NULL || t - v > 0 )
      {
        s = v + 4; --tmp;
        if( tmp == 0 ) // OK
        {
          pos = s - cmdbuf; break;
        }
      }
      else
      {
        s = t + 3; ++tmp;
      }
    }
  }
  return pos;
}

static int evalNumArg(string cmdbuf, int* result)
// RC = Anzahl verarbeiteter Bytes oder -1 
{ char buf[CMDLEN+1]; int pos;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<A>") == cmdbuf )
  { 
    pos = skipArg(cmdbuf);
    if( pos > 0 )
    {
      CmdStrCat(buf, cmdbuf+3);
      buf[pos-7] = '\0';
      if( evalNumExp(buf,result) > 0 ) return pos;
    }
    return -1;
  }
  return 0;
} 

static int evalBoolArg(string cmdbuf, bool* result)
// RC = Anzahl verarbeiteter Bytes oder -1 
{ char buf[CMDLEN+1]; int pos;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<A>") == cmdbuf )
  { 
    pos = skipArg(cmdbuf);
    if( pos > 0 )
    {
      CmdStrCat(buf, cmdbuf+3);
      buf[pos-7] = '\0';
      if( evalBoolExp(buf,result) > 0 ) return pos;
    }
    return -1;
  }
  return 0;
} 

static int evalStrArg(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1 
{ char buf[CMDLEN+1]; int pos;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<A>") == cmdbuf )
  { 
    pos = skipArg(cmdbuf);
    if( pos > 0 )
    {
      CmdStrCat(buf, cmdbuf+3);
      buf[pos-7] = '\0';
      if( evalStrExp(buf,resbuf) > 0 ) return pos;
    }
    return -1;
  }
  return 0;
} 

static int evalFun_read(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; 
  char line[BUFLEN+1];
  string s = cmdbuf; 
  int pos, tmp;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<read>") == cmdbuf )
  { 
    s += 6;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      {
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        if( strstr(s,"</read>") == s )
        { FILE* fp = fopen(buf,"rt");
          if( fp != (FILE*)NULL )
          {
            while( fgets(line,BUFLEN,fp) != (string)NULL )
              CmdStrCat(resbuf, line);
            fclose(fp);
          }
          return 6 + pos + 7;
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_base(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; string s = cmdbuf; 
  int pos, tmp;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<base>") == cmdbuf )
  { 
    s += 6;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      {
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        if( strstr(s,"</base>") == s )
        {
          CmdStrCat(resbuf, fidToBase(buf));
          return 6 + pos + 7;
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_path(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; string s = cmdbuf; 
  int pos, tmp;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<path>") == cmdbuf )
  { 
    s += 6;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      {
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        if( strstr(s,"</path>") == s )
        {
          CmdStrCat(resbuf, fidToPath(buf));
          return 6 + pos + 7;
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_substr(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; string s = cmdbuf; 
  int pos, tmp, p, l;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<substr>") == cmdbuf )
  { 
    s += 8;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      {
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp  = evalNumArg(s,&p);
        if( tmp > 0 && p >= 0 && p < (int)strlen(buf) )
        {
          tmp += evalSpace(s+tmp);
          pos += tmp;
          s   += tmp;
          tmp  = evalNumArg(s,&l);
          if( tmp > 0 && l > 0 && l <= (int)strlen(buf) )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
            if( strstr(s,"</substr>") == s && p + l < (int)strlen(buf) )
            {
              buf[p+l] = '\0';
              CmdStrCat(resbuf, buf+p);
              return 8 + pos + 9;
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_par(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; string s = cmdbuf; 
  int pos, tmp;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<par>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      {
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        if( strstr(s,"</par>") == s )
        {
          strcpy(buf,getParameter(buf));
          if( strlen(buf) > 0 )
          {
            CmdStrCat(resbuf, buf);
            return 5 + pos + 6;
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_idx(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; string s = cmdbuf; 
  int pos, tmp, cnt, i;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<idx>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      { string* list;
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp  = getList(buf,&list,&cnt);
        if( tmp > 0 )
        {
          tmp = evalNumArg(s,&i);
          if( tmp > 0 )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
            if( strstr(s,"</idx>") == s )
            {
              strcpy(buf,getElement(list,cnt,i));
              if( strlen(buf) > 0 )
              {
                CmdStrCat(resbuf, buf);
                return 5 + pos + 6;
              }
            }
          }
        }
        else
        {
          tmp = evalNumArg(s,&i);
          if( tmp > 0 )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
            if( strstr(s,"</idx>") == s && i >= 0 && i < (int)strlen(buf) )
            {
              buf[i+1] = 0;  
              CmdStrCat(resbuf, buf+i);
              return 5 + pos + 6;
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_map(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1], var[BUFLEN+1]; 
  string s = cmdbuf, t = (string)NULL, v = (string)NULL; 
  int pos, tmp, cnt, i;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<map>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      { string* list;
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp = getList(buf,&list,&cnt);
        if( tmp > 0 )
        { 
          buf[0] = '\0';
          tmp    = evalStrArg(s,buf);
          if( tmp > 0 && strlen(buf) <= BUFLEN )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
            strcpy(var,buf);
            buf[0] = '\0';
            tmp    = evalStrArg(s,buf);
            if( tmp > 0 )
            {
              tmp += evalSpace(s+tmp);
              pos += tmp;
              s   += tmp;
              t    = strstr(buf,var);
              if( strstr(s,"</map>") == s && t != (string)NULL )
              {
                v = t + strlen(var); t[0] = 0;
                for( i=0; i < cnt; ++i )
                {
                  CmdStrCat(resbuf, buf);
                  CmdStrCat(resbuf, getElement(list,cnt,i));
                  CmdStrCat(resbuf, v);
                }
                return 5 + pos + 6;
              }
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_readlist(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1], dir[BUFLEN+1], ext[BUFLEN+1]; 
  string s = cmdbuf; 
  int pos, tmp, cnt, i;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<readlist>") == cmdbuf )
  { 
    s += 10;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      { string* list;
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp = getList(buf,&list,&cnt);
        if( tmp > 0 )
        { 
          buf[0] = '\0';
          tmp    = evalStrArg(s,buf);
          if( tmp > 0 && strlen(buf) <= BUFLEN )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
            strcpy(dir,buf);
            buf[0] = '\0';
            tmp    = evalStrArg(s,buf);
            if( tmp > 0 )
            {
              tmp += evalSpace(s+tmp);
              pos += tmp;
              s   += tmp;
              strcpy(ext,buf);
              if( strstr(s,"</readlist>") == s )
              {
                for( i=0; i < cnt; ++i )
                {
                  if( strlen(dir) == 0 && strlen(ext) == 0 )
                    strcpy(buf,getElement(list,cnt,i));
                  else
                  {
                    buf[0] = '\0';
                    if( strlen(dir) > 0 )
                    {
                      strcpy(buf,dir);
                      strcat(buf,"\\");
                    }
                    strcat(buf,fidToBase(getElement(list,cnt,i)));
                    strcat(buf,ext);
                  }
                  { FILE* fp = fopen(buf,"rt");
                    if( fp != (FILE*)NULL )
                    {
                      while( fgets(buf,CMDLEN,fp) != (string)NULL )
                        CmdStrCat(resbuf, buf);
                      fclose(fp);
                    }
                  }
                }
                return 10 + pos + 11;
              }
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_sif(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; string s = cmdbuf; 
  int pos, tmp; bool b;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<sif>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalBoolArg(s,&b);
      if( tmp > 0 )
      { 
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        if( b == False )
        {
          tmp = skipArg(s);
          if( tmp > 0 )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
          }
        }
        if( tmp >= 0 )
        {
          tmp  = evalStrArg(s,buf);
          if( tmp > 0 )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
            if( b == True )
            {
              tmp = skipArg(s);
              if( tmp > 0 )
              {
                tmp += evalSpace(s+tmp);
                pos += tmp;
                s   += tmp;
              }
            }
            if( tmp >= 0 && strstr(s,"</sif>") == s )
            {
              CmdStrCat(resbuf, buf);
              return 5 + pos + 6;
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_nif(string cmdbuf, int* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ string s = cmdbuf; int pos, tmp, n; bool b;
  if( strstr(cmdbuf,"<nif>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalBoolArg(s,&b);
      if( tmp > 0 )
      { 
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        if( b == False )
        {
          tmp = skipArg(s);
          if( tmp > 0 )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
          }
        }
        if( tmp >= 0 )
        {
          tmp  = evalNumArg(s,&n);
          if( tmp > 0 )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
            if( b == True )
            {
              tmp = skipArg(s);
              if( tmp > 0 )
              {
                tmp += evalSpace(s+tmp);
                pos += tmp;
                s   += tmp;
              }
            }
            if( tmp >= 0 && strstr(s,"</nif>") == s )
            {
              *result = n;
              return 5 + pos + 6;
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_len(string cmdbuf, int* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; string s = cmdbuf; 
  int pos, tmp;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<len>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      { string* list;
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp  = getList(buf,&list,result);
        if( tmp > 0 )
        {
          if( strstr(s,"</len>") == s )
            return 5 + pos + 6;
        }
        else
        {
          if( strstr(s,"</len>") )
          {
            *result = strlen(buf);
            return 5 + pos + 6;
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_sub(string cmdbuf, int* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ string s = cmdbuf; int pos, tmp, l, r;
  if( strstr(cmdbuf,"<sub>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalNumArg(s,&l);
      if( tmp > 0 )
      { 
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp  = evalNumArg(s,&r);
        if( tmp > 0 )
        {
          tmp += evalSpace(s+tmp);
          pos += tmp;
          s   += tmp;
          if( strstr(s,"</sub>") == s )
          {
            *result = ( l - r );
            return 5 + pos + 6;
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_add(string cmdbuf, int* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ string s = cmdbuf; int pos, tmp, l, r;
  if( strstr(cmdbuf,"<add>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalNumArg(s,&l);
      if( tmp > 0 )
      { 
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp  = evalNumArg(s,&r);
        if( tmp > 0 )
        {
          tmp += evalSpace(s+tmp);
          pos += tmp;
          s   += tmp;
          if( strstr(s,"</add>") == s )
          {
            *result = ( l + r );
            return 5 + pos + 6;
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_not(string cmdbuf, bool* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ string s = cmdbuf; int pos, tmp; bool b;
  if( strstr(cmdbuf,"<not>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalBoolArg(s,&b);
      if( tmp > 0 )
      { 
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        if( strstr(s,"</not>") == s )
        {
          *result = ( ! b );
          return 5 + pos + 6;
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_or(string cmdbuf, bool* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ string s = cmdbuf; int pos, tmp; bool l, r;
  if( strstr(cmdbuf,"<or>") == cmdbuf )
  { 
    s += 4;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalBoolArg(s,&l);
      if( tmp > 0 )
      { 
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp  = evalBoolArg(s,&r);
        if( tmp > 0 )
        {
          tmp += evalSpace(s+tmp);
          pos += tmp;
          s   += tmp;
          if( strstr(s,"</or>") == s )
          {
            *result = ( l || r );
            return 4 + pos + 5;
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_and(string cmdbuf, bool* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ string s = cmdbuf; int pos, tmp; bool l, r;
  if( strstr(cmdbuf,"<and>") == cmdbuf )
  { 
    s += 5;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalBoolArg(s,&l);
      if( tmp > 0 )
      { 
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp  = evalBoolArg(s,&r);
        if( tmp > 0 )
        {
          tmp += evalSpace(s+tmp);
          pos += tmp;
          s   += tmp;
          if( strstr(s,"</and>") == s )
          {
            *result = ( l && r );
            return 5 + pos + 6;
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_ncmp(string cmdbuf, bool* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; string s = cmdbuf; 
  int pos, tmp, l, r;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<ncmp>") == cmdbuf )
  { 
    s += 6;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      { 
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp  = evalNumArg(s,&l);
        if( tmp > 0 )
        {
          tmp += evalSpace(s+tmp);
          pos += tmp;
          s   += tmp;
          tmp  = evalNumArg(s,&r);
          if( tmp > 0 )
          {
            if( strstr(s,"</ncmp>") == s )
            {
              if( ! strcmp(buf,"=") )
              {
                *result = ( l == r );
                return 6 + pos + 7;
              }
              else
              if( ! strcmp(buf,"<=") )
              {
                *result = ( l <= r );
                return 6 + pos + 7;
              }
              else
              if( ! strcmp(buf,"<") )
              {
                *result = ( l < r );
                return 6 + pos + 7;
              }
              else
              if( ! strcmp(buf,">") )
              {
                *result = ( l > r );
                return 6 + pos + 7;
              }
              else
              if( ! strcmp(buf,">=") )
              {
                *result = ( l >= r );
                return 6 + pos + 7;
              }
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_scmp(string cmdbuf, bool* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1], buf2[CMDLEN+1], opr[BUFLEN+1]; 
  string s = cmdbuf; 
  int pos, tmp;
  buf[0] = buf2[0] = '\0';
  if( strstr(cmdbuf,"<scmp>") == cmdbuf )
  { 
    s += 6;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 && strlen(buf) <= BUFLEN )
      { 
        strcpy(opr,buf);
        tmp    += evalSpace(s+tmp);
        pos    += tmp;
        s      += tmp;
        buf[0]  = '\0';
        tmp     = evalStrArg(s,buf);
        if( tmp > 0 )
        {
          tmp += evalSpace(s+tmp);
          pos += tmp;
          s   += tmp;
          tmp  = evalStrArg(s,buf2);
          if( tmp > 0 )
          {
            if( strstr(s,"</scmp>") == s )
            {
              if( ! strcmp(opr,"=") )
              {
                *result = ( strcmp(buf,buf2) == 0 );
                return 6 + pos + 7;
              }
              else
              if( ! strcmp(opr,"<=") )
              {
                *result = ( strcmp(buf,buf2) <= 0 );
                return 6 + pos + 7;
              }
              else
              if( ! strcmp(opr,"<") )
              {
                *result = ( strcmp(buf,buf2) < 0 );
                return 6 + pos + 7;
              }
              else
              if( ! strcmp(opr,">") )
              {
                *result = ( strcmp(buf,buf2) > 0 );
                return 6 + pos + 7;
              }
              else
              if( ! strcmp(opr,">=") )
              {
                *result = ( strcmp(buf,buf2) >= 0 );
                return 6 + pos + 7;
              }
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalFun_exist(string cmdbuf, bool* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ char buf[CMDLEN+1]; 
  string s = cmdbuf, t; 
  int pos, tmp, cnt, i;
  buf[0] = '\0';
  if( strstr(cmdbuf,"<exist>") == cmdbuf )
  { 
    s += 7;
    if( *s != '\0' )
    {
      pos  = evalSpace(s);
      s   += pos;
      tmp  = evalStrArg(s,buf);
      if( tmp > 0 )
      { string* list;
        tmp += evalSpace(s+tmp);
        pos += tmp;
        s   += tmp;
        tmp = getList(buf,&list,&cnt);
        if( tmp > 0 )
        { 
          buf[0] = '\0';
          tmp    = evalStrArg(s,buf);
          if( tmp > 0 )
          {
            tmp += evalSpace(s+tmp);
            pos += tmp;
            s   += tmp;
            if( strstr(s,"</exist>") == s )
            {
              *result = False;
              for( i=0; i < cnt; ++i )
              {
                t = strstr(getElement(list,cnt,i),buf);
                if( t != (string)NULL ) 
                { 
                  *result = True; break; 
                }
              }
              return 7 + pos + 8;
            }
          }
        }
      }
    }
    return -1;
  }
  return 0;
} 

static int evalStrExp(string cmdbuf, string resbuf)
// RC = Anzahl verarbeiteter Bytes oder -1
{ int pos = 0, tmp = 0; 
  while( cmdbuf[pos] != '\0' )
  {
    tmp = 0;
    if( tmp == 0 &&
        ( tmp = evalFun_base(cmdbuf+pos,resbuf) ) > 0 )   pos += tmp;
    else
    if( tmp == 0 &&
        ( tmp = evalFun_path(cmdbuf+pos,resbuf) ) > 0 )   pos += tmp;
    else
    if( tmp == 0 &&
        ( tmp = evalFun_substr(cmdbuf+pos,resbuf) ) > 0 ) pos += tmp;
    else
    if( tmp == 0 &&
        ( tmp = evalFun_par(cmdbuf+pos,resbuf) ) > 0 )    pos += tmp;
    else
    if( tmp == 0 &&
        ( tmp = evalFun_idx(cmdbuf+pos,resbuf) ) > 0 )    pos += tmp;
    else
    if( tmp == 0 &&
        ( tmp = evalFun_map(cmdbuf+pos,resbuf) ) > 0 )    pos += tmp;
    else
    if( tmp == 0 &&
        ( tmp = evalFun_sif(cmdbuf+pos,resbuf) ) > 0 )    pos += tmp;
    else
    if( tmp == 0 &&
        ( tmp = evalFun_read(cmdbuf+pos,resbuf) ) > 0 )   pos += tmp;
    else
    if( tmp == 0 &&
        ( tmp = evalFun_readlist(cmdbuf+pos,resbuf) ) > 0 ) pos += tmp;
    else
    if( tmp == 0 )
    {
      if( cmdbuf[pos] == '\\' )
      {
        if( cmdbuf[pos+1] == '\\' )
        {
          CmdCharCat(resbuf, '\\'); pos+=2;
        }
        else
        if( cmdbuf[pos+1] == 'n' )
        {
          CmdCharCat(resbuf, '\n'); pos+=2;
        }
        else
        if( cmdbuf[pos+1] == 'r' )
        {
          CmdCharCat(resbuf, '\r'); pos+=2;
        }
        else
        if( cmdbuf[pos+1] == 't' )
        {
          CmdCharCat(resbuf, '\t'); pos+=2;
        }
        else
        {
          CmdCharCat(resbuf, cmdbuf[pos]); ++pos;
        }
      }
      else
      {
        CmdCharCat(resbuf, cmdbuf[pos]); ++pos;
      }
    }
    if( tmp < 0 ) break;
  }
  if( tmp >= 0 ) return pos;
  return -1;
} 

static int evalNumExp(string cmdbuf, int* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ int pos = 0; 
  if( ( pos=evalFun_len(cmdbuf,result) ) > 0 ) return pos;
  else
  if( ( pos=evalFun_sub(cmdbuf,result) ) > 0 ) return pos;
  else
  if( ( pos=evalFun_add(cmdbuf,result) ) > 0 ) return pos;
  else
  if( ( pos=evalFun_nif(cmdbuf,result) ) > 0 ) return pos;
  else
  {
    *result = atoi(cmdbuf);
    return strlen(cmdbuf);
  }
  return -1;
} 

static int evalBoolExp(string cmdbuf, bool* result)
// RC = Anzahl verarbeiteter Bytes oder -1
{ int pos = 0; 
  if( ( pos=evalFun_not(cmdbuf,result) ) > 0 )   return pos;
  else
  if( ( pos=evalFun_and(cmdbuf,result) ) > 0 )   return pos;
  else
  if( ( pos=evalFun_or(cmdbuf,result) ) > 0 )    return pos;
  else
  if( ( pos=evalFun_ncmp(cmdbuf,result) ) > 0 )  return pos;
  else
  if( ( pos=evalFun_scmp(cmdbuf,result) ) > 0 )  return pos;
  else
  if( ( pos=evalFun_exist(cmdbuf,result) ) > 0 ) return pos;
  else
  {
    *result = ( ! strcmp(cmdbuf,"true") );
    return strlen(cmdbuf);
  }
  return -1;
} 

static string evalCommand(string cmdbuf)
{ static char buf[CMDLEN+1]; int pos;
  buf[0] = '\0';
  pos = evalStrExp(cmdbuf,buf);
  if( pos < 0 ) 
  {
    fprintf(stderr,"error: command evaluation:\n<<\n%s>>\n%s\n",cmdbuf,buf);
    buf[0] = '\0';
  }
  return buf;
}

/* -------------------------- macro processing ------------------------------ */

static void initRule(bool bResetCommands)
{ int i;
  for (i = 0; i < cnt_targets; i++)    free(targets[i]);
  for (i = 0; i < cnt_sources; i++)    free(sources[i]);
  for (i = 0; i < cnt_includes; i++)   free(includes[i]);
  for (i = 0; i < cnt_libraries; i++)  free(libraries[i]);
  for (i = 0; i < cnt_incdirs; i++)    free(incdirs[i]);
  for (i = 0; i < cnt_libdirs; i++)    free(libdirs[i]);
  for (i = 0; i < cnt_parameters; i++) free(parameters[i]);
  cnt_targets    = 0;
  cnt_sources    = 0;
  cnt_includes   = 0;
  cnt_libraries  = 0;
  cnt_incdirs    = 0;
  cnt_libdirs    = 0;
  cnt_parameters = 0;
  need_date      = 0L;
  goal_date      = 0x7fffffffL;
  if( bResetCommands )
  {
    for (i = 0; i < cnt_cmdtypes; i++) free(cmdtypes[i]);
    for (i = 0; i < cnt_commands; i++) free(commands[i]);
    cnt_commands = 0;
    cnt_cmdtypes = 0;
  }
}

static void addTarget(string path)
{ long   date;
  string exppath = expandFid(path);
  if (cnt_targets >= MaxTargets)
  {
    fprintf(stderr,"%s(%d): error: too many targets.\n",fileid,lineno);
    exit(1);
  }
  date = filetime(exppath);
  if (date < goal_date)
    goal_date = date;
  targets[cnt_targets] = strdup(exppath);
  cnt_targets += 1;
}

static bool addSource(string path)
{ long   date;
  string exppath = expandFid(path);
  if (cnt_sources >= MaxSources)
  {
    fprintf(stderr,"%s(%d): error: too many sources.\n",fileid,lineno);
    exit(1);
  }
  date = filetime(exppath);
  if (date == 0L)
  {
    fprintf(stderr,"%s(%d): error: missing '%s'.\n",fileid,lineno,exppath);
    return False;
  }
  if (date > need_date)
    need_date = date;
  sources[cnt_sources] = strdup(exppath);
  cnt_sources += 1;
  return True;
}

static void addIncDir(string path)
{ int    i; 
  string exppath = expandFid(path);
  for( i=0; i < cnt_incdirs; ++i )
    if( !strcmp(incdirs[i],exppath) )
      break;
  if( i == cnt_incdirs )
  {
    if (cnt_incdirs >= MaxIncDirs)
    {
      fprintf
      (
        stderr,"%s(%d): error: too many include directories.\n",fileid,lineno
      );
      exit(1);
    }
    incdirs[cnt_incdirs] = strdup(exppath);
    cnt_incdirs += 1;
  }
}

static void addLibDir(string path)
{ int    i; 
  string exppath = expandFid(path);
  for( i=0; i < cnt_libdirs; ++i )
    if( !strcmp(libdirs[i],exppath) )
      break;
  if( i == cnt_libdirs )
  {
    if (cnt_libdirs >= MaxLibDirs)
    {
      fprintf
      (
        stderr,"%s(%d): error: too many library directories.\n",fileid,lineno
      );
      exit(1);
    }
    libdirs[cnt_libdirs] = strdup(exppath);
    cnt_libdirs += 1;
  }
}

static void addDirectory(string path)
{
  addIncDir(path); 
  addLibDir(path);
}

static bool addInclude(string path)
{ long   date;
  string exppath = expandFid(path);
  if (cnt_includes >= MaxIncludes)
  {
    fprintf(stderr,"%s(%d): error: too many includes.\n",fileid,lineno);
    exit(1);
  }
  date = filetime(exppath);
  if (date == 0L)
  {
    fprintf(stderr,"%s(%d): error: missing '%s'.\n",fileid,lineno,exppath);
    return False;
  }
  if (date > need_date)
    need_date = date;
  includes[cnt_includes] = strdup(exppath);
  cnt_includes += 1;
  addIncDir(fidToPath(path));
  return True;
}

static bool addLibrary(string path)
{ long   date;
  string exppath = expandFid(path);
  if (cnt_libraries >= MaxLibraries)
  {
    fprintf(stderr,"%s(%d): error: too many libraries.\n",fileid,lineno);
    exit(1);
  }
  date = filetime(exppath);
  if (date == 0L)
  {
    fprintf(stderr,"%s(%d): error: missing '%s'.\n",fileid,lineno,exppath);
    return False;
  }
  if (date > need_date)
    need_date = date;
  libraries[cnt_libraries] = strdup(exppath);
  cnt_libraries += 1;
  addLibDir(fidToPath(path));
  return True;
}

static void addParameter(string param)
{
  if (cnt_parameters >= MaxParameters)
  {
    fprintf(stderr,"%s(%d): error: too many parameters.\n",fileid,lineno);
    exit(1);
  }
  parameters[cnt_parameters] = strdup(param);
  cnt_parameters += 1;
}

static void addCommand(string action)
{
  if (cnt_commands >= MaxCommands)
  {
    fprintf(stderr,"%s(%d): error: too many commands.\n",fileid,lineno);
    exit(1);
  }
  commands[cnt_commands] = strdup(action);
  cnt_commands += 1;
}

static void addCmdType(string cmdtyp)
{ char buf[BUFLEN+1];
  int  len = strlen(cmdtyp);
  if (cnt_cmdtypes >= MaxCmdTypes)
  {
    fprintf(stderr,"%s(%d): error: too many command types.\n",fileid,lineno);
    exit(1);
  }
  if( len == 0 || cmdtyp[len-1] != ']' )
  {
    fprintf(stderr,"%s(%d): syntax error.\n",fileid,lineno);
    exit(1);
  }
  cmdtyp[len-1] = '\0';
  sprintf(buf,"%s:%ld",cmdtyp,(long)cnt_commands);
  cmdtypes[cnt_cmdtypes] = strdup(buf);
  cnt_cmdtypes += 1;
}

static void printCommand(string cmdfile, string cmdbuf, bool append)
{ string cmd = (string)NULL;
  cmd = evalCommand(cmdbuf);
  if( cmd != (string)NULL && strlen(cmd) > 0 )
  { FILE* fp = fopen(cmdfile,append?"at":"wt");
    if( fp != (FILE*)NULL )
    {
      fprintf(fp,"%s",cmd);
      fclose(fp);
    }
    else
    {
      fprintf(stderr,"can't open file '%s'.\n",cmdfile);
      exit(1);
    }
  }
  cmdbuf[0] = '\0';
}

static void execCommand(string cmdbuf)
{ string cmd = (string)NULL; int res = 0;
  cmd = evalCommand(cmdbuf);
  if( cmd != (string)NULL && strlen(cmd) > 0 )
  {
    res = system(cmd);
    cmdbuf[0] = '\0';
    if (res == 0) return;
    fprintf(stderr,"'prnmk' aborted due to error code (%d).\n",res);
  }
  exit(1);
}

static bool getCommands(string cmdtyp,int* fstidx, int* lstidx)
{
  if( cnt_commands > 0 )
  { string s;
    int    i;
    for( i=0; i < cnt_cmdtypes; ++i )
    {
      s = strstr(cmdtypes[i],cmdtyp);
      if( s == cmdtypes[i] && *(s + strlen(cmdtyp)) == ':' )
      {
        s += strlen(cmdtyp)+1;
        *fstidx = atoi(s);
        if( *fstidx >= 0 && *fstidx < cnt_commands )
        {
          if( i < cnt_cmdtypes - 1 )
          {
            s = strstr(cmdtypes[i+1],":")+1;
            *lstidx = atoi(s);
            if( *lstidx >= *fstidx && *lstidx < cnt_commands )
              return True;
          }
          else
          {
            *lstidx = cnt_commands;
            return True;
          }
        }
        return False;
      }
    }
  }
  return False;
}

static void execCommands(string cmdtyp)
{ char tmpbuf[CMDLEN+1], cmdbuf[CMDLEN+1];
  int fstidx, lstidx, i, l, l1 = 0, l2 = 0;
  if (cnt_targets > 0 && ! getCommands(cmdtyp,&fstidx,&lstidx))
  {
    fprintf(stderr,"%s(%d): syntax error.\n",fileid,lineno);
    exit(1);
  }
  if (goal_date < need_date)
  { 
    fprintf(stdout,"%s %s\n",cmdtyp,fidToBase(targets[0]));
    tmpbuf[0] = '\0'; cmdbuf[0] = '\0';
    for( i=fstidx; i < lstidx; ++i )
    { string cmd = commands[i];
      char   c   = *cmd;
      if( c == '<' || c == '>' || c == '!' )
      { bool append = False;
        cmd += 1; 
        if( c == '>' )
        {
          if( *cmd == '>' )
          {
            append = True; cmd += 1; 
          }
          while(isspace(*cmd) && *cmd != '\0') cmd += 1;
        }
        l2 = strlen(cmd);
        if( l2 > 0 )
        {
          l1 = ( c == '<' )
               ? strlen(tmpbuf) : ( c == '!' ) ? strlen(cmdbuf) : 0;
          l = l1 + l2;
          if( l + 1 > CMDLEN ) // l2 < CMDLEN !
          {
            fprintf(stderr,"error: command buffer too small.\n");
            exit(1);
          }
          switch(c)
          { 
            case '>':
              if( strlen(tmpbuf) == 0 )
                fprintf(stderr,"warning: no command info for '%s'.\n",cmd);
              else printCommand(cmd,tmpbuf,append); // resets buffer !
              break;
            case '<':
              strcat(tmpbuf,cmd);
              if( tmpbuf[l-1] == '\\' ) tmpbuf[l-1] = '\0';
              else                       
              {
                tmpbuf[l+1-1] = '\n'; tmpbuf[l+2-1] = '\0';
              }
              break;
            case '!':
              strcat(cmdbuf,cmd);
              if( cmdbuf[l-1] == '\\' ) cmdbuf[l-1] = '\0';
              else execCommand(cmdbuf); // resets buffer !
              break;
          }
        }
        else
        if( c == '>' )
        {
          fprintf(stderr,"error: empty output file name.\n");
          break;
        }
      }
    }
  }
}

static void nanomake(void)
{ char buf[BUFLEN+1], *arg;
  bool skipRule    = False,
       skipProject = False;
  lineno = 0;
  initRule(True);
  while(fgets(buf,BUFLEN,SysIn) != NULL)
  { int len = strlen(buf);
    lineno += 1;
    while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == ' '))
    {
      len -= 1;
      buf[len] = 0;
    }
    if ( len == 0 ) continue;
    else
    if ( buf[0] == '#') 
    {
      if( rules != (string)NULL && strstr(buf,"# Rule ") == buf )
      {
        skipProject = ( strstr(rules,buf+7) == (string)NULL );
      }
      continue;
    }
    else
    if( skipProject ) continue;
    for (arg = buf+1; *arg != '\0' && *arg == ' '; arg+=1);
    switch(buf[0])
    { bool res;
      case 'T' : addTarget(arg);    
                 break;
      case 'S' : res = ! addSource(arg);    
                 if( ! skipRule ) skipRule = res;
                 break;
      case 'I' : res = ! addInclude(arg);   
                 if( ! skipRule ) skipRule = res;
                 break;
      case 'L' : res = ! addLibrary(arg);   
                 if( ! skipRule ) skipRule = res;
                 break;
      case 'D' : addDirectory(arg); 
                 break;
      case 'P' : addParameter(arg); 
                 break;
      case '[' : addCmdType(arg); 
                 break;
      case ';' : if( ! skipRule ) execCommands(arg);    
                 initRule(False); 
                 skipRule = False;
                 break;
      default  : addCommand(buf);   
                 break;
    }
  }
  if( cnt_targets > 0 )
  {
    fprintf(stderr,"%s(%d): syntax error.\n",fileid,lineno);
    exit(1);
  }
  initRule(True);
}

int main(int argc, string argv[])
{ int i = 0;
  if (argc > 3 || (argc == 2 && !strcmp(argv[1],"-?")))
  {
    fprintf(stderr,"Usage: nmk [Filename] [-r=RulePath]\n");
    fprintf(stderr,"     : default Filename is 'project.nmk'\n");
    fprintf(stderr,"     : all rules are evaluated when missing option '-r'\n");
    exit(1);
  }
  for( i=1; i < argc; ++i )
  {
    if( strstr(argv[i],"-r=") == argv[i] )
      rules = argv[i]+3;
    else
    if( fileid == (string)NULL )
      fileid = argv[i];
  }
  if( fileid == (string)NULL )
    fileid = "project.nmk";
  SysIn = fopen(fileid,"r");
  if (SysIn == (FILE*) NULL)
  {
    fprintf(stderr,"error: '%s' not seen.\n",fileid);
    exit(1);
  }
  nanomake();
  fclose(SysIn);
  return 0;
}
