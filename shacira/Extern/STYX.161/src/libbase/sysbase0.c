/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [sysbase0.c]                Standard Definitions ( Part 0 )                */
/*                                                                            */
/* Copyright (c) 1993 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

#include "styconf0.h"
#include "syscbhdl.h"

/*I---------------------- Global Types -------------------------------------- */

/*DOC_INTERFACE*/
#ifdef _MSDOS
typedef long     INT;
typedef long     LONG_INT;
#define __FAR    __far
#define __HUGE   __huge
typedef void     __HUGE *HugeCPtr;
#else
typedef int      INT;
typedef long     int LONG_INT;
#define __FAR
#define __HUGE
#define HugeCPtr StdCPtr
#define NewHMem  NewMem
#define FreeHMem FreeMem
#endif

/*DOC_INTERFACE*/
typedef void *StdCPtr;

/*DOC_INTERFACE*/
#if !defined( __GNUC__ )
typedef signed char      c_int8;
typedef signed short     c_int16;
typedef signed long      c_int32;
typedef unsigned char    c_uint8;
typedef unsigned short   c_uint16;
typedef unsigned long    c_uint32;
#if defined(STYX_CONFIG_OSMS) && defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64
#define STYX_CONFIG_TINT64
typedef signed   __int64 c_int64;
typedef unsigned __int64 c_uint64;
#else
#if sizeof(int) >= 8
#define STYX_CONFIG_TINT64
typedef signed   int     c_int64;
typedef unsigned int     c_uint64;
#endif 
#endif 
#else /*__GNUC__*/
#define STYX_CONFIG_TINT64
typedef int8_t           c_int8;
typedef int16_t          c_int16;
typedef int32_t          c_int32;
typedef int64_t          c_int64;
typedef u_int8_t         c_uint8;
typedef u_int16_t        c_uint16;
typedef u_int32_t        c_uint32;
typedef u_int64_t        c_uint64;
#endif

/*INTERFACE*/
#define ConcreteImp(Name)  struct Name##_imp
#define ConcreteDecl(Name) typedef ConcreteImp(Name) *Name
#define ConcreteType(Name) typedef ConcreteImp(Name) *Name; ConcreteImp(Name)
#define SizeOf(Name)       sizeof(ConcreteImp(Name))

/*INTERFACE*/
#define ExternalType(TYPENAME) ConcreteType(TYPENAME)
#define ExternalDecl(TYPENAME) ConcreteDecl(TYPENAME)

/*DOC_INTERFACE*/
#define AbstractType(TYPENAME) typedef StdCPtr TYPENAME

/*DOC_INTERFACE*/
#define AbstractHugeType( TYPENAME ) \
typedef HugeCPtr TYPENAME

/*INTERFACE*/
#define Tupel( TYPENAME ) \
struct TYPENAME

/*DOC_INTERFACE*/
AbstractType( Abs_T );
AbstractType( Any_T );

/*INTERFACE*/
#define ABS_CAST(t,a) ((t)(long)(a))
#define intCAST(a) ABS_CAST(int,a)

/*INTERFACE*/
/*NOCONVERSION*/
typedef unsigned char  c_byte;
typedef unsigned short c_word;
#ifndef __cplusplus
typedef c_byte byte;
typedef c_word word;
#endif

/*DOC_INTERFACE*/
/*NOCONVERSION*/
#define c_bool  int
#define C_False 0
#define C_True  1
#ifndef __cplusplus
#define bool  c_bool
#define False C_False
#define True  C_True
#endif

/*DOC_INTERFACE*/
/*NOCONVERSION*/
typedef c_byte           *c_bstring; /* sizeof(long) Bytes Len, Len Bytes */
typedef char             *c_string;
#ifndef __cplusplus
typedef c_string          string;
#endif
#if defined(WEOF)
typedef wint_t            wc_int;
typedef wchar_t           wc_char;
typedef wchar_t          *wc_string;
#define WCHAR_LITERAL(c) L##c
#else
typedef unsigned long     wc_int;
typedef unsigned long     wc_char;
typedef unsigned long    *wc_string;
#define WCHAR_LITERAL(c) ((unsigned long)c)
#endif

/*INTERFACE*/
#define OBJ_REF(obj)    ( &(obj) )
#define REF_OBJ(objref) ( *(objref) )
#define _               (NULL)

/*INTERFACE*/
#define STD_BUFFLEN 512
#define ERR_BUFFLEN 4096

/*INTERFACE*/
#define _NO_DLL_EXPORT_
#if defined( _MSDOS ) || defined( _WIN32 )
#define _DLL_EXPORT_DECL_   extern __declspec( dllexport )
#define _DLL_EXPORT_        __declspec( dllexport )
#define _DLL_IMPORT_        __declspec( dllimport )
#define _C_DECL_            __cdecl
#else
#define _DLL_EXPORT_DECL_   extern
#define _DLL_EXPORT_ 
#define _DLL_IMPORT_   
#define _C_DECL_ 
#endif

/*I-------------------- CommandLine I/O & Exception ------------------------- */

static PHDL_TRAP     hdl_trap     = (PHDL_TRAP)NULL;
static PHDL_ABORT    hdl_abort    = (PHDL_ABORT)NULL;
static PHDL_FREEMEM  hdl_freemem  = (PHDL_FREEMEM)NULL;

#define IS_ABORT_HDL  ( hdl_abort != (PHDL_ABORT)NULL )
#define IS_TRAP_HDL   ( hdl_trap  != (PHDL_TRAP)NULL  )

static FILE* fp_stdout = (FILE*)NULL;
static FILE* fp_stderr = (FILE*)NULL;

FILE* StdOutFile(void)
#define STDOUT StdOutFile()
/* stdout */
{
  return fp_stdout==(FILE*)NULL?stdout:fp_stdout;
}

FILE* StdErrFile(void)
#define STDERR StdErrFile()
/* stderr */
{
  return fp_stderr==(FILE*)NULL?stderr:fp_stderr;
}

void fprint_raw(FILE* fp, c_string s, size_t size)
/* prints string 's' in a printable form to file 'fp'
   'size' >= 0: number of characters to print
*/
{ size_t l, i;
  if( fp != (FILE*)NULL && s != (c_string)NULL )
  {
    l = (((int)size)>=0) ? size : strlen(s);
    for( i=0; i < l && s[i] != '\0'; ++i )
    {
      if( !iscntrl(s[i]) || isspace(s[i]) )
        fprintf(fp,"%c",s[i]);
      else
        fprintf(fp,"%02x",s[i]);
    }
  }
}

void prMsg_stdout(c_string s)
/* prints string 's' in a printable form to stdout */
{
  if( s != (c_string)NULL ) fprint_raw(STDOUT,s,-1);
}

void prMsg_stderr(c_string s)
/* prints string 's' in a printable form to stderr */
{
  if( s != (c_string)NULL ) fprint_raw(STDERR,s,-1);
}

void AbortApp(c_string errmsg)
#define STD_ERREXIT AbortApp("")
/* aborts application with error message 'errmsg' */
{
  if( ! IS_ABORT_HDL ) fprintf(STDERR,"%s",errmsg);
  if( fp_stdout != (FILE*)NULL && fp_stdout != stdout ) fflush(fp_stdout);
  if( fp_stderr != (FILE*)NULL && fp_stderr != stderr ) fflush(fp_stderr);
  if( IS_ABORT_HDL ) (*hdl_abort)(errmsg);
  else exit(1);
}

PHDL_TRAP getTrapHdl(void)
/* gets the trap handler */
{
  return hdl_trap;
}

void setTrapHdl(PHDL_TRAP h_trap)
/* sets a trap handler 
   ( xaron error callback ) 
*/
{
  if( h_trap == (PHDL_TRAP)NULL )
  {
    fprintf(STDERR,"initializing of trap handler failed.\n");
    STD_ERREXIT;
  }
  hdl_trap = h_trap;
}

PHDL_ABORT getErrExitHdl(void)
/* gets the abort handler */
{
  return hdl_abort;
}

void setErrExitHdl(PHDL_ABORT h_abort)
/* sets an abort handler */
{
  if( h_abort == (PHDL_ABORT)NULL )
  {
    fprintf(STDERR,"initializing of abort handler failed.\n");
    STD_ERREXIT;
  }
  hdl_abort = h_abort;
}

PHDL_FREEMEM getFreeMemHdl(void)
/* gets the handler to organize free memory from heap */
{
  return hdl_freemem;
}

void setFreeMemHdl(PHDL_FREEMEM h_freemem)
/* sets a handler to organize free memory from heap */
{
  if( h_freemem == (PHDL_FREEMEM)NULL )
  {
    fprintf(STDERR,"initializing of free memory handler failed.\n");
    STD_ERREXIT;
  }
  hdl_freemem = h_freemem;
}

void initStdFiles(FILE* out, FILE* err)
/* overwrites stdout, stderr */
{
  if( out == (FILE*)NULL || err == (FILE*)NULL ) 
  {
    fprintf(STDERR,"initializing of standard I/O files failed.\n");
    STD_ERREXIT;
  }
  fp_stdout = out; fp_stderr = err;
}

void quitStdFiles(void)
/* resets stdout, stderr */
{
  fp_stdout = stdout; fp_stderr = stderr;
}

/*I-------------------- Thread/Process Synchronisation ---------------------- */

#if defined( _MSDOS ) || defined( _WIN32 )

StdCPtr initSem(string id, int maxcnt, int initcnt)
/* creates or opens semaphore 'id [NULL]' to synchronize 
   a maximum of 'maxcnt' concurrent threads
   with an initial value of 'initcnt'
   RC: semaphore or NULL
   non-MS: 'id', 'maxcnt' not used
*/
{ SECURITY_ATTRIBUTES recSecurityAttr;
  recSecurityAttr.nLength              = sizeof(SECURITY_ATTRIBUTES);
  recSecurityAttr.lpSecurityDescriptor = NULL;
  recSecurityAttr.bInheritHandle       = TRUE;
  return CreateSemaphore(&recSecurityAttr,initcnt,maxcnt,id);
}

bool quitSem(StdCPtr sem)
/* closes and - on OK - destroys semaphore 'sem'
   RC: True=OK
*/
{
  return CloseHandle((HANDLE)sem) == TRUE ? True : False;
}

int waitSem(StdCPtr sem)
/*
   waits and enters critical section 'sem' ( blocking )
   RC: 1=OK, 0=occupied, -1=error
*/
{ int rc = WaitForSingleObject((HANDLE)sem,INFINITE);
  return rc == WAIT_FAILED ? -1 : rc == WAIT_OBJECT_0 ? 1 : 0;
}

int trySem(StdCPtr sem)
/*
   tries to enter critical section 'sem' ( non-blocking )
   RC: 1=OK, 0=occupied, -1=error
*/
{ int rc = WaitForSingleObject((HANDLE)sem,10/*milliseconds*/);
  return rc == WAIT_FAILED ? -1 : rc == WAIT_OBJECT_0 ? 1 : 0;
}

bool postSem(StdCPtr sem, int cnt)
/*
   leaves critical section 'sem' and releases 'cnt' resources
   RC: True=OK
   non-MS: 'cnt' not used (=1)
*/
{ 
  return ReleaseSemaphore((HANDLE)sem,cnt,NULL) == TRUE ? True : False;
}


#else
#if !defined(MSDOS) && ( !defined(HAVE_CONFIG_H) || defined(HAVE_LIBRT) && defined(HAVE_SEMAPHORE_H) )

  StdCPtr initSem(string id, int maxcnt, int initcnt)
  { sem_t* sem = (sem_t*)malloc(sizeof(sem_t)); 
    int    rc  = sem_init(sem,0/*process-local*/,initcnt);
    if( rc == 0 ) return sem;
    else
    {
      free(sem); return (sem_t*)NULL;
    }
  }
  
  bool quitSem(StdCPtr sem)
  { 
    if( sem != (StdCPtr)NULL )
    { int rc = sem_destroy(sem);
      if( rc == 0 )
      {
        free(sem); return True;
      }
    }
    return False;
  }
  
  int waitSem(StdCPtr sem)
  { int rc = sem_wait((sem_t*)sem); 
    // rc = 0 (always)
    return (rc=1);
  }
  
  int trySem(StdCPtr sem)
  { int rc = sem_trywait((sem_t*)sem); 
    if( rc == 0 ) return 1;
    else return 0;
  }
  
  bool postSem(StdCPtr sem, int cnt)
  { int rc = sem_post((sem_t*)sem); 
    return rc==0?True:False;
  }


#else
/* DOS-GNU-CC, no semaphore support via 'semaphore' */

  StdCPtr initSem(string id, int maxcnt, int initcnt)
  { 
    return (StdCPtr)NULL;
  }
  
  bool quitSem(StdCPtr sem)
  { 
    return True;
  }
  
  int waitSem(StdCPtr sem)
  { 
    return 1;
  }
  
  int trySem(StdCPtr sem)
  { 
    return 1;
  }
  
  bool postSem(StdCPtr sem, int cnt)
  { 
    return True;
  }


#endif

#endif

/*I-------------------- Error Handling -------------------------------------- */

/*DOC_INTERFACE*/
typedef void (*PF_ERROR)(bool cond, string format, ...);

void ForceCore(void)
/* since we didn't find an appropriate function in the c-lib */
{
  static int dummy;
  dummy = dummy/dummy; /* just fooling the optimizing compiler ... */
}

static StdCPtr tass_sem  = (StdCPtr)NULL;
static string  tass_file = (string)NULL;
static string  tass_kind = (string)NULL;
static int     tass_line = 0;

static void tass1(bool cond, string format, ...) 
{ va_list args; 
  char    varbuf[ERR_BUFFLEN/2+1],
          errbuf[ERR_BUFFLEN+1];
  va_start(args,format);
  if( ! cond )
  {
    if( tass_sem == (StdCPtr)NULL || trySem(tass_sem) == 1 )
    {
      sprintf(errbuf,"\n%s : ", tass_kind);
      if( tass_sem != (StdCPtr)NULL ) postSem(tass_sem,1);
    }
#if ( defined( _MSDOS ) || defined( _WIN32 ) ) && !defined( HAVE_VSNPRINTF )
    vsprintf(varbuf,format,args);
#else
    vsnprintf(varbuf,ERR_BUFFLEN/2,format,args);
#endif
    va_end(args);
    strcat(errbuf,varbuf);
    if( tass_sem == (StdCPtr)NULL || trySem(tass_sem) == 1 )
    {
      if( strlen(tass_file) > ERR_BUFFLEN/4 )
      { char c = tass_file[ERR_BUFFLEN/4];
        tass_file[ERR_BUFFLEN/4] = '\0';
        sprintf(varbuf,".\nSee line %d of file \"%s\".\n", tass_line, tass_file);
        tass_file[ERR_BUFFLEN/4] = c;
      }
      else
        sprintf(varbuf,".\nSee line %d of file \"%s\".\n", tass_line, tass_file);
      if( tass_sem != (StdCPtr)NULL ) postSem(tass_sem,1);
    }
    strcat(errbuf,varbuf);
    if( IS_ABORT_HDL ) AbortApp(errbuf);
    else
    { 
      //fprintf(STDERR,"%s",errbuf);
      fprint_raw(STDERR,errbuf,ERR_BUFFLEN);
      if( getenv("FORCECORE") != NULL ) ForceCore();
      if( IS_TRAP_HDL ) (*hdl_trap)(errbuf);
      else STD_ERREXIT;
    }
  }
  va_end(args);
}

PF_ERROR _AssCheck(string kind, string file, int line)
/* saves assertion type, source position and 
   returns assert function
*/
{
  if( tass_sem == (StdCPtr)NULL || trySem(tass_sem) == 1 )
  {
    tass_kind = kind;
    tass_file = file;
    tass_line = line;
    if( tass_sem != (StdCPtr)NULL ) postSem(tass_sem,1);
  }
  return (PF_ERROR)tass1;
}

/*DOC_INTERFACE*/
#define c_assert (*(_AssCheck("Restriction error",__FILE__,__LINE__)))
#define c_bug    (*(_AssCheck("Internal error",   __FILE__,__LINE__)))
#define C_BUG    c_bug(False,"")
#ifndef __cplusplus
#define assert   c_assert
#define bug      c_bug
#define BUG      C_BUG
#endif

/*INTERFACE*/
#define assert0(cond,txt)     ((!(cond)) ? (c_assert(False,(txt)),0):0)
#define assert1(cond,txt,a1)  ((!(cond)) ? (c_assert(False,(txt),(a1)),0):0)
#define assert2(cond,txt,a,b) ((!(cond)) ? (c_assert(False,(txt),(a),(b)),0):0)
#define bug0(cond,txt)        ((!(cond)) ? (c_bug(False,(txt)),0):0)
#define bug1(cond,txt,a1)     ((!(cond)) ? (c_bug(False,(txt),(a1)),0):0)
#define bug2(cond,txt,a,b)    ((!(cond)) ? (c_bug(False,(txt),(a),(b)),0):0)
#define BUG_NULL(obj)         bug0( (StdCPtr)(obj) != (StdCPtr)NULL, \
                                    "Null Object" )
#define BUG_VRNG(val,min,max) bug0( (val) >= (min) && (val) <= (max), \
                                    "Value out of Range" )
#define BUG_RNG0(val,max)     BUG_VRNG((val),0,(max)-1)
#define BUG_RNG1(val,max)     BUG_VRNG((val),1,(max))
#define BUG_VMIN(val,min)     bug0( (val) > (min), "Value below Minimum" )
#define BUG_VEQU(lft,rgt)     bug0( (lft) == (rgt), "Values not equal" )
#define BUG_VNEQ(lft,rgt)     bug0( (lft) != (rgt), "Values equal" )
#define BUG_MOD0(lft,rgt)     bug0( (rgt) > 0 && ! ( (lft) % (rgt) ), \
                                    "Non Zero Modulo" )

/*!!
   Usage of the macros 'assert', 'bug':
   assert | bug ( condition, which has to be true,
                  message format string ( see printf ),
                  any further parameter, according to the above format string );
*/

/*I---------------------------- System-Init & Quit -------------------------- */

void sysbase_init(void)
/* initializes module ( for thread-savety ) */
{
  tass_sem = initSem((string)NULL , 1, 1);
}

void sysbase_quit(void)
/* terminates module ( for thread-savety ) */
{
  quitSem(tass_sem);
}

StdCPtr sysbase_sem(void)
/* system semaphore ( for thread-savety ) */
{
  return tass_sem;
}

/*I---------------------------- Global Macros ------------------------------- */

/*INTERFACE*/
#define I32_HIGHVAL(v)    ( (short)(((long)(v)) >> 16) )
#define I32_LOWVAL(v)     ( (short)(((long)(v)) & 0xFFFFL) )
#define SET_I32_VAL(h,l)  ( ((((long)(h)) << 16) & 0xFFFF0000L) | \
                            (((long)(l)) & 0x0000FFFFL) )


/*DOC_INTERFACE*/
#define STR_EMPTY(s)      ( (s) == (string)NULL || *(s) == '\0' )
#define INRANGE(a,x,b)    ( ( (a) <= (x) ) && ( (x) <= (b) ) )
#define ABS(x)            ( (x) < 0 ? - (x) : (x) )
#define MAX(a,b)          ( (a) < (b) ? (b) : (a) )
#define MIN(a,b)          ( (a) < (b) ? ( a ) : (b) )
#define EQSIGN(a,b)       ( ( ( (a) <= 0 ) && ( (b) <= 0 ) ) || \
                            ( ( (a) >= 0 ) && ( (b) >= 0 ) ) )

/*INTERFACE*/
#define FTAB(F,N)    fprintf(F,"\n%*s",N,"")
#define FNLIND(F)    FTAB(F,indent)
#define FNL(F)       fprintf(F,"\n")
#define TAB(N)       FTAB(STDOUT,N)
#define NLIND        TAB(indent)
#define NL           FNL(STDOUT)
#define FPCHR(F,C)   fprintf(F,"%c",C)
#define PCHR(C)      FPCHR(STDOUT,C)
#define FPNLSNL(F,S) fprintf(F,"\n%s\n",S)
#define PNLSNL(F,S)  FPNLSNL(STDOUT,S)
#define HERE         fprintf(STDOUT,"File: %s, Line: %d\n",__FILE__,__LINE__)

