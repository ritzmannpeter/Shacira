/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [sysbase1.c]                Standard Definitions ( Part 1 )                */
/*                                                                            */
/* Copyright (c) 1993 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

#include "sysbase0.h"

#include "mem_base.h"

/*I----------------- Byte/String & VarArg Handling -------------------------- */

/*INTERFACE*/
#define CORE            fprintf(STDOUT,"Objects = %ld\n", ObjCount())
#define BUG_CORE        bug1(ObjCount() == 0,"%ld objects",ObjCount())
#define BUG_CORE_EX(c)  bug1(ObjCount()+(c) == 0,"%ld objects",ObjCount()+(c))
#define New(TYPE)       (TYPE)NewMem(SizeOf(TYPE))

StdCPtr BytCopy(StdCPtr bytes, long len)
/* copies 'len' bytes of byte array 'bytes';
   allocs memory
*/
{ byte *res, *byt = (byte *)bytes; long  i;
  res = (byte*)NewMem(len);
  for(i = 0; i < len; i++)
    res[i] = byt[i];
  return (StdCPtr) res;
}

c_bstring BytToBStrCopy(StdCPtr bytes, long len)
/* constructs a binary string 
   from 'len' bytes of byte array 'bytes';
   allocs memory
*/
{ c_bstring res; 
  res = (c_bstring)NewMem(len+sizeof(long));
  memcpy(res,&len,sizeof(long));
  memcpy(res+sizeof(long),bytes,len);
  return res;
}

c_string BytToHStrCopy(StdCPtr bytes, long len)
/* creates a hex string from 'len' bytes of byte array 'bytes';
   allocs memory
*/
{ c_string res; 
  long hlen = len * 2, i, j;
  res = (c_string)NewMem(hlen+1);
  for( i=j=0; i < len; ++i, j+=2 )
    sprintf(res+j,"%02x",((byte*)bytes)[i]);
  res[hlen] = '\0';
  return res;
}

c_string BStrToHStrCopy(c_bstring bstr)
/* creates a hex string from binary string 'bstr';
   allocs memory
*/
{ c_string res; 
  long blen, hlen, i, j;
  memcpy(&blen,bstr,sizeof(long));
  hlen = blen * 2;
  res = (c_string)NewMem(hlen+1);
  blen += sizeof(long);
  for( i=sizeof(long), j=0; i < blen; ++i, j+=2 )
    sprintf(res+j,"%02x",bstr[i]);
  res[hlen] = '\0';
  return res;
}

bool IsSpaceStr(string s)
/* whether string 's' is empty or 
   only contains space characters 
*/
{ 
  if( STR_EMPTY(s) ) return True;
  else
  {
    while( isspace(*s++) ) 
      ;
    return *s == '\0';
  }
}

size_t WCStrLen(wc_string ws)
/* number of wide characters in string 'ws'
   ( without the termination character )
*/
{ size_t len = 0, i = 0;
  while( ws[i] != WCHAR_LITERAL('\0') ) 
  {
    ++len; ++i;
  }
  return len;
}

wc_string SubWCStrCopy(wc_string str, long len)
/* copies 'len' wide characters of string 'str';
   appends 0, allocs memory
*/
{ wc_string res;
  res = (wc_string)BytCopy(str,(len+1)*sizeof(wc_char));
  res[len] = WCHAR_LITERAL('\0');
  return res;
}

wc_string WCStrCopy(wc_string Str)
/* copies wide character string 'Str'; allocs memory */
{
  return SubWCStrCopy(Str,WCStrLen(Str));
}

string WCToStrCopy(wc_string wc)
/* copies wide character string 'wc' into a string;
   without conversion, allocs memory 
*/
{ size_t len = WCStrLen(wc), i;
  string res = (string)NewMem(len+1);
  for( i=0; i < len; ++i )
    res[i] = (byte)wc[i];
  res[i] = '\0';
  return res;
}

wc_string WCStrToLower(wc_string st)
/* converts all letters in wide character string 'st' to lower case */
{ wc_string s;
#if defined(iswupper) && defined(towlower)
  for(s=st;*s;s++) if( iswupper(*s) ) *s = towlower(*s);
#else
  for(s=st;*s;s++) if( (wc_char)((byte)(*s)) == (*s) && isupper(*s) ) *s = tolower(*s);
#endif
  return st;
}

wc_string WCStrToUpper(wc_string st)
/* converts all letters in wide character string 'st' to upper case */
{ wc_string s;
#if defined(iswlower) && defined(towupper)
  for(s=st;*s;s++) if( iswlower(*s) ) *s = towupper(*s);
#else
  for(s=st;*s;s++) if( (wc_char)((byte)(*s)) == (*s) && islower(*s) ) *s = toupper(*s);
#endif
  return st;
}

string SubStrCopy(string str, long len)
/* copies 'len' characters of string 'str';
   appends 0, allocs memory
*/
{ string res;
  res = (string)BytCopy(str,len+1);
  res[len] = '\0';
  return res;
}

string StrCopy(string Str)
/* copies string 'Str'; allocs memory */
{
  return SubStrCopy(Str,strlen(Str));
}

string StrToLower(string st)
/* converts all letters in string 'st' to lower case */
{ string s;
  for(s=st;*s;s++) if( isupper(*s) ) *s = tolower(*s);
  return st;
}

string StrToUpper(string st)
/* converts all letters in string 'st' to upper case */
{ string s;
  for(s=st;*s;s++) if( islower(*s) ) *s = toupper(*s);
  return st;
}

Any_T* MakeArgLst(va_list args, int fixed_cnt, ...)
/* MakeArgLst is a portable replacement for GetArgLst coping with the
 * idiosyncracies of different va_list implementations. Since there is
 * no portable way to pass a va_list (caller's variable arguments)
 * through '...', it has to be moved before the caller's fixed args.
 * fixed_cnt is the count of the caller's fixed arguments.
 *
 * Sample usage:
 *   variadic_func(int argcnt, TYPEA a, TYPEB b, TYPEC c, ...)
 *   {
 *     va_list va;
 *     Any_T *argl;
 *     va_start(va,c); // Must use the *last* fixed argument here
 *     argl = MakeArgLst(va, 4, argcnt, a, b, c);
 *     va_end(va);
 *     // make use of argl
 *     FreeMem(argl);
 *   }
 *
 * For an in depth discussion of variadic functions including
 * portability, see libc.info Node: Variadic Functions. 
*/
{
  va_list fixed_args;
  int argcnt, i;
  Any_T* arglst;
  va_start(fixed_args, fixed_cnt);
  argcnt = va_arg(fixed_args, int);
  arglst = (Any_T*)NewMem((argcnt+1)*sizeof(Any_T));
  arglst[0] = ABS_CAST(Any_T,argcnt);
  for (i=1; i < fixed_cnt; ++i)
    arglst[i] = va_arg(fixed_args,Any_T);
  va_end(fixed_args);
  for (; i <= argcnt; ++i)
    arglst[i] = va_arg(args,Any_T);
  return arglst;
}

/*I------------- Workaround for missing C library functions ----------------- */

c_string strstr_aux(c_string s1, c_string s2)
/* workaround for 'strstr' */
{ c_string res = (c_string)NULL, s = s1;
  if( s1 != (c_string)NULL || s2 != (c_string)NULL )
  { int l2 = strlen(s2);
    while( *s != '\0' )
    {
      if( !strncmp(s,s2,l2) )
      {
        res = s; break;
      }
      else s += 1;
    }
  }
  return res;
}

c_string strchr_aux(c_string s, int c)
/* workaround for 'strchr' */
{ c_string res = (c_string)NULL, t = s;
  if( s != (c_string)NULL )
  {
    while( *t != '\0' )
    { 
      if( (int)(*t) == c )
      {
        res = t; break;
      }
      else t += 1;
    }
  }
  return res;
}

c_string strrchr_aux(c_string s, int c)
/* workaround for 'strrchr' */
{ c_string res = (c_string)NULL, t;
  if( s != (c_string)NULL )
  { int l = strlen(s);
    t = s + l;
    while( l >= 0 )
    { 
      if( (int)(*t) == c )
      {
        res = t; break;
      }
      else
      {
        t -= 1; l -= 1;
      }
    }
  }
  return res;
}

int strcspn_aux(c_string s, c_string reject)
/* workaround for 'strcspn' */
{ int res = 0, l , i;
  c_string t = s;
  if( s != (c_string)NULL && reject != (c_string)NULL )
  { 
    l = strlen(reject);
    while( *t != '\0' )
    {
      for( i=0; i < l; ++i )
        if( reject[i] == *t ) return res;
      ++res; t += 1;
    }
  }
  return res;
}

StdCPtr memcpy_aux(StdCPtr dst, StdCPtr src, int n)
/* workaround for 'memcpy' */
{ 
  if( dst != (StdCPtr)NULL && src != (StdCPtr)NULL && n >= 0 )
  { int i;
    for( i=0; i < n; ++i ) ((byte*)dst)[i] = ((byte*)src)[i];
  }
  return dst;
}

int memcmp_aux(StdCPtr dst, StdCPtr src, int n)
/* workaround for 'memcmp' */
{ 
  if( dst != (StdCPtr)NULL && src != (StdCPtr)NULL && n >= 0 )
  { int i;
    for( i=0; i < n; ++i ) 
      if( ((byte*)dst)[i] < ((byte*)src)[i] )
        return -1;
      else
      if( ((byte*)dst)[i] > ((byte*)src)[i] )
        return 1;
    return 0;
  }
  else return (byte*)dst - (byte*)src;
}

c_string getcwd_aux(c_string buffer, int bufsize)
/* workaround for 'getcwd'; evaluates $PWD */
{ c_string pwd = getenv("PWD");
  if( pwd != (c_string)NULL && strlen(pwd) < bufsize )
  {
    strcpy(buffer,pwd); return buffer;
  }
  else return (c_string)NULL;
}

/*I-------------------------- System Error ---------------------------------- */

#if defined( _MSDOS ) || defined( _WIN32 )

string GetSystemError(void)
/* system error message; allocs memory */
{ long    rc;
  StdCPtr buf = (StdCPtr)NULL;
  string  txt;
  rc = FormatMessage
       (
         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
         NULL,
         GetLastError(),
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default Language
         (LPTSTR)&buf,
         0,
         NULL
       );
  if( rc == 0 ) txt = StrCopy("");
  else          txt = StrCopy((string)buf);
  if( buf != (StdCPtr)NULL ) LocalFree(buf);
  return txt;
}

string GetSystemError_noalloc(string buffer, int bufsize)
/* system error message */
{ long rc;
  if( buffer != (string)NULL )
  {
    rc = FormatMessage
         (
           FORMAT_MESSAGE_FROM_SYSTEM,
           NULL,
           GetLastError(),
           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default Language
           (LPTSTR)buffer,
           bufsize,
           NULL
         );
    if( rc == 0 ) *buffer = '\0';
  }
  return buffer;
}

#else

  string GetSystemError_noalloc(string buffer, int bufsize)
  { 
    if( buffer != (string)NULL )
    { int    e = errno;
      string t = strerror(e);
      if( t == (string)NULL ) *buffer = '\0';
      else                    
      {
        strncpy(buffer,t,bufsize); buffer[bufsize] = '\0';
      }
    }
    return buffer;
  }

#endif

/*I-------------------------- Program Execution ----------------------------- */

/*DOC_INTERFACE*/
#define STD_CMD_NOWAIT     0
#define STD_CMD_WAIT_INIT  1
#define STD_CMD_WAIT       2

#if defined( _WIN32 )

  int runprg(string cmd, int cmdflg) // Win32
  /* exec program */
  { STARTUPINFO         StartInfo;
    PROCESS_INFORMATION ProcessInfo;
    long                ExitVal = 0, tmp;
    GetStartupInfo(&StartInfo);
    if( CreateProcess
        (
          NULL,cmd,
          NULL,NULL,FALSE,CREATE_NEW_PROCESS_GROUP,NULL,NULL,
          &StartInfo,&ProcessInfo
        ) == FALSE )
      ExitVal = GetLastError();
    else
    if( cmdflg == STD_CMD_WAIT )
    {
      tmp = WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
      if( tmp == WAIT_FAILED )
        ExitVal = GetLastError();
      else
      if( GetExitCodeProcess(ProcessInfo.hProcess,&ExitVal) == FALSE )
        ExitVal = GetLastError();
    }
    else
    if( cmdflg == STD_CMD_WAIT_INIT )
    {
      if( WaitForInputIdle(ProcessInfo.hProcess,INFINITE/*msec*/) != 0 )
        ExitVal = GetLastError();
    }
    return (int)ExitVal;
  }

#else
#if defined( _MSDOS )

  int runprg(string cmd, int cmdflg) // Windows 3.x
  /* exec program */
  { 
    if( cmdflg != STD_CMD_WAIT )
      return WinExec(cmd,SW_SHOW);
    else
      return system(cmd);
  }

#else
#if defined( MSDOS ) // Dos-GNU

  int runprg(string cmd, int cmdflg)
  /* exec program */
  { 
    return system(cmd);
  }

#else // Unix, Linux

int runprg(string cmd, int cmdflg) 
/* executes program 'cmd' 
   cmdflg=STD_CMD_NOWAIT    --> asynchron, non-blocking
   cmdflg=STD_CMD_WAIT_INIT --> waits for initialisation
   cmdflg=STD_CMD_WAIT      --> synchron, blocking
*/
{ 
  if( cmdflg == STD_CMD_WAIT )
    return system(cmd);
  else
  { string x = NewMem(strlen(cmd)+2+1);
    strcpy(x,cmd);
    strcat(x," &");
    return system(x);
  }
}

#endif

#endif

#endif

/*I----------------- DLL & dynamic Function Call Support -------------------- */

/*DOC_INTERFACE*/
typedef StdCPtr (*PCFUN)();

StdCPtr apply_fun_portable(PCFUN f, int cnt, StdCPtr* args)
/* portable dynamic call of C-function 'f' 
   with 'cnt' parameters in 'args'
   ( upto 9 parameters )
*/
{
  switch (cnt)
  {
    case 0: return f();
    case 1: return f(args[0]);
    case 2: return f(args[0],args[1]);
    case 3: return f(args[0],args[1],args[2]);
    case 4: return f(args[0],args[1],args[2],args[3]);
    case 5: return f(args[0],args[1],args[2],args[3],args[4]);
    case 6: return f(args[0],args[1],args[2],args[3],args[4],args[5]);
    case 7: return f(args[0],args[1],args[2],args[3],args[4],args[5],args[6]);
    case 8: return f(args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7]);
    case 9: return f(args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8]);
    default: 
      C_BUG; return NULL;
  }
}

#if defined( _MSDOS ) || defined( _WIN32 )
#define PUSH_FUN_ARG(arg) __asm mov eax, arg \
                          __asm push eax 
#define CALL_FUN(f)       __asm call f
         
StdCPtr apply_fun(PCFUN f, int cnt, StdCPtr* args)
/* dynamic call of C-function 'f' 
   with 'cnt' parameters in 'args' 
   ( restricted to intel )
*/
{ int i; StdCPtr arg;
  for( i=cnt-1; i >= 0; --i )
  {
    arg = args[i];
    PUSH_FUN_ARG(arg);
  }
  /*return*/ CALL_FUN(f); /* note that return is implied here. */
}

#else
#if !defined( MSDOS ) && defined ( __GNUC__ ) && #cpu (i386)
#define PUSH_FUN_ARG(arg) __asm__ volatile ( "pushl %0" : : "r" (arg) )
#define CALL_FUN(f)       __asm__ volatile ( "call *%0" : : "r" (f) )

  StdCPtr apply_fun(PCFUN f, int cnt, StdCPtr* args)
  { int i; StdCPtr arg;
    for( i=cnt-1; i >= 0; --i )
    {
      arg = args[i];
      PUSH_FUN_ARG(arg);
    }
    return (*f)(/*args*/);
    /*return CALL_FUN(f); note that return is implied here. */
  }

#else
/* non-intel-cpu || DOS-GNU-CC */
#define apply_fun apply_fun_portable

#endif

#endif

AbstractType( DL_Hdl ); /* Abstract handle type */

/*DOC_INTERFACE*/
#define DL_LOAD_LAZY    0

/*DOC_INTERFACE*/
#if !defined(STYX_CONFIG_OSMS) && (!defined(HAVE_CONFIG_H) || (defined(HAVE_LIBDL) && defined(HAVE_DLFCN_H)))
#define DL_LAZY         RTLD_LAZY
#define DL_NOW          RTLD_NOW
#define DL_BINDING_MASK RTLD_BINDING_MASK
#define DL_GLOBAL       RTLD_GLOBAL
#define DL_LOCAL        RTLD_LOCAL
#else
#define DL_LAZY         0
#define DL_NOW          0
#define DL_BINDING_MASK 0
#define DL_GLOBAL       0
#define DL_LOCAL        0
#endif

#if defined( _MSDOS ) || defined( _WIN32 )

  DL_Hdl DL_open(string dlname, int flag)
  { HMODULE dll = LoadLibrary((LPCTSTR)dlname);
    return (DL_Hdl)dll;
  }

  int DL_close(DL_Hdl dlhdl)
  { 
    if( FreeLibrary((HMODULE)dlhdl) == TRUE ) return 0;
    else return 1;
  }

  StdCPtr DL_symbol(DL_Hdl dlhdl, string symname)
  /* ReturnType: FARPROC */
  { FARPROC res = GetProcAddress((HMODULE)dlhdl,(LPCTSTR)symname);
    return (StdCPtr)res;
  }

  string DL_error(void)
  {
    return GetSystemError();
  }

  string DL_error_noalloc(string buffer, int bufsize)
  { 
    return GetSystemError_noalloc(buffer,bufsize);
  }

#else
#if !defined(MSDOS) && ( !defined(HAVE_CONFIG_H) || ( defined(HAVE_LIBDL) && defined(HAVE_DLFCN_H) ) )

DL_Hdl DL_open(string dlname, int flag)
/* loads dll 'dlname' in mode 'flag' ( ERROR: NULL )
   LINUX: flag=RTLD_LAZY|RTLD_NOW|-1=RTLD_NOW, MS: not used     
*/
{ DL_Hdl dl = (DL_Hdl)dlopen(dlname,flag<0?RTLD_NOW:flag);
  return dl;
}

int DL_close(DL_Hdl dlhdl)
/* detaches dll 'dlhdl' ( SUCCESS: 0, ERROR: > 0 ) */
{
  return dlclose(dlhdl);
}

StdCPtr DL_symbol(DL_Hdl dlhdl, string symname)
/* address of symbol 'symname' within dll 'dlhdl' ( ERROR: NULL )
   LINUX: function|data, MS: function
*/
{
  return dlsym(dlhdl,symname);
}

string DL_error(void)
/* dll load error; allocs memory */
{ 
#if !defined(HAVE_CONFIG_H) || defined(HAVE_DLERROR)
  string t = dlerror();
#else
  string t = GetSystemError();
#endif
  return StrCopy(t==(string)NULL?"":t); //t?t:""; 
}

string DL_error_noalloc(string buffer, int bufsize)
/* dll load error */
{ 
  if( buffer != (string)NULL )
  { 
#if !defined(HAVE_CONFIG_H) || defined(HAVE_DLERROR)
    string t = dlerror();
#else
    string t = GetSystemError();
#endif
    if( t == (string)NULL ) *buffer = '\0';
    else
    {
      strncpy(buffer,t,bufsize); buffer[bufsize] = '\0';
    }
  }
  return buffer;
}

#else
/* DOS-GNU-CC, no ELF */

  DL_Hdl DL_open(string dlname, int flag)
  { 
    return (DL_Hdl)NULL;
  }

  int DL_close(DL_Hdl dlhdl)
  {
    return 1;
  }

  StdCPtr DL_symbol(DL_Hdl dlhdl, string symname)
  {
    return NULL;
  }

  string DL_error(void)
  {
    return GetSystemError();
  }

  string DL_error_noalloc(string buffer, int bufsize)
  {
    return GetSystemError_noalloc(buffer,bufsize);
  }

#endif

#endif

/*I---------------------- Network Support ----------------------------------- */

#if defined( _MSDOS ) || defined( _WIN32 )

string UserName(void)
/* login name; allocs memory */
{ char buf[1000]; long dmy=999;
  GetUserName(buf,&dmy);
  return StrCopy(StrToLower(buf));
}

#else
#if !defined( MSDOS )

  string UserName(void)
  { string u = getenv("LOGNAME");
    return StrCopy(u!=(string)NULL?u:"");
  }

#else
/* DOS-GNU-CC */

  string UserName(void)
  { string u = getenv("USER");
    return StrCopy(u!=(string)NULL?u:"");
  }

#endif

#endif
