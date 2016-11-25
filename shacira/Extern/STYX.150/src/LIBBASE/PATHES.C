/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [pathes.c]      Path Iterator / File Access & I/O Handling                 */
/*                                                                            */
/* Copyright (c) 1993 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

#include "standard.h"

#include "sink.h"
#include "ctx_app.h"

/*I----------------------- Types -------------------------------------------- */

AbstractType(PIT); /* Abstract tokenizer / path iterator type */

ConcreteType(PIT_IMP)
{
  string PathList;
  string sep;
  string tok;
  string pos;
  string end;
};

#if defined( MSDOS ) || defined( _WIN32 )
  static string dsep = "\\";
  static string psep = ";";
#else
  static string dsep = "/";
  static string psep = ":";
#endif

#define DIR_SEP  dsep
#define PATH_SEP psep

/*I------------------- Tokenizer / Path iterator ---------------------------- */

PIT PIT_make(string PathList)
/* creates a tokenizer / path iterator from 'PathList' */
{ PIT_IMP pit = (PIT_IMP)NULL;
  if( ! STR_EMPTY(PathList) )
  {
    pit           = New(PIT_IMP);
    pit->PathList = StrCopy(PathList);
    pit->sep      = StrCopy(PATH_SEP);
    pit->tok      = pit->PathList;
    pit->pos      = pit->PathList;
    pit->end      = pit->PathList + strlen(pit->PathList);
  }
  return( (PIT)pit );
}

void PIT_sep(PIT Piter,string sep)
/* defines 'sep' as token separator for iterator 'Piter' */
{ PIT_IMP pit = (PIT_IMP)Piter;
  if( pit != (PIT_IMP)NULL ) 
  {
    FreeMem(pit->sep); pit->sep = StrCopy(sep);
  }
}

string PIT_read(PIT Piter)
/* next token / path in iterator 'Piter' */
{ PIT_IMP pit = (PIT_IMP)Piter;
  if( pit == (PIT_IMP)NULL ) return( (string)NULL );
  else
  if( pit->pos == pit->end ) return( (string)NULL );
  else
  {
    if( pit->pos > pit->PathList ||
        ( pit->pos == pit->PathList && *pit->pos == '\0' ) )
    {
      *pit->pos = *pit->sep;
      pit->tok  = pit->pos + strlen(pit->sep);
    }
    pit->pos = strstr(pit->tok,pit->sep);
    if( pit->pos == (string)NULL ) 
      pit->pos = pit->end;
    else
      *pit->pos = '\0';
    return pit->tok;
  }
}

void PIT_drop(PIT Piter)
/* drops tokenizer / path iterator 'Piter' */
{ PIT_IMP pit = (PIT_IMP)Piter;
  if( pit != (PIT_IMP)NULL )
  {
    FreeMem(pit->PathList);
    FreeMem(pit->sep);
    FreeMem(pit);
  }
}

/*I-------------------- File access / information -------------------------- */

string DirSep(void)
/* directory separator ( constant ) */
{
  return( DIR_SEP );
}

string PathSep(void)
/* path separator ( constant ) */
{
  return( PATH_SEP );
}

bool AbsolutePathSep(string file)
/* whether 'file' starts with a path separator */
{
  return( ! strncmp(file,"\\",1) || ! strncmp(file,"/",1) );
}

bool AbsolutPath(string file)
/* whether 'file' is an absolut path */
{
  if( STR_EMPTY(file) ) return( False );
  else
  { 
#if defined( MSDOS ) || defined( _WIN32 )
    if( strlen(file) >= 2 && isalpha(file[0]) && file[1] == ':' ) 
      return( True );
#endif
    return( ! strncmp(file,"\\",1) || ! strncmp(file,"/",1) );
  }
}

bool PathIgnCase(void)
/* whether pathes are case insensitive */
{
#if defined( MSDOS ) || defined( _WIN32 )
  return True;
#else
  return False;
#endif
}

string FileLName(string file)
/* filename of path 'file'; allocs memory */
{ int i,len = strlen(file); 
  for (i = len; i >= 0; i--) 
    if (file[i] == '\\' || file[i] == '/')
    {
      return StrCopy(file+i+1);
    }
  return StrCopy(file);
}

string FilePrefix(string file)
/* directory prefix of path 'file'; allocs memory */
{ int i,len = strlen(file); string buf = (string)NewMem(len+1);
  for (i = len; i >= 0; i--) 
    if (file[i] == '\\' || file[i] == '/')
    { int nlen = i;
      strncpy(buf,file,nlen); buf[nlen] = '\0';
      return buf;
    }
  return strcpy(buf,"");
}

string FileSuffix(string file)
/* suffix of path 'file'; allocs memory */
{ int i,len = strlen(file); string buf = (string)NewMem(len+1);
  for (i = len; i >= 0; i--) 
    if (file[i] == '.') 
    { int nlen = len-i;
      strncpy(buf,file+i,nlen); buf[nlen] = '\0';
      return buf;
    }
  return strcpy(buf,"");
}

string BaseFile(string file)
/* basename of path 'file'; allocs memory */
{ int i,len = strlen(file); string buf = (string)NewMem(len+1);
  for (i = len; i >= 0; i--) 
  {
    if (file[i] == '\\' || file[i] == '/') break;
    if (file[i] == '.') { len = i; break; }
  }
  for (i = len; i >= 0; i--) 
  {
    if (file[i] == '\\' || file[i] == '/')
    { int nlen = len-i-1;
      strncpy(buf,file+i+1,nlen); buf[nlen] = '\0';
      return buf;
    }
  }
  strncpy(buf,file,len); buf[len] = '\0';
  return buf;
}

static string PathSink(string pre, string direnv, string basename, string ext)
/* full path name ( no paramter check, auxiliary for 'MkPath' ) */
{
  return
  ( 
    Str_printf
    ("%s%s%s%s%s",pre,direnv,DIR_SEP,basename,( STR_EMPTY(ext) ) ? "" : ext) 
  );
}

bool IsPath(string path)
/* whether 'path' is a regular file, directory, ... */
{ struct stat buf;
  return( stat(path,&buf) == 0 );
}

bool IsDirEntry(string file, string dir)
/* whether 'file' is an entry of directory 'dir' */
{ string path = Str_printf("%s%s%s",dir,DIR_SEP,file);
  bool   res  = IsPath(path);
  FreeMem(path);
  return res;
}

string GetEnvCtx(string env)
/* value of context or environment variable or NULL */
{ c_bool bCtx = ( CTX_ctx_val() != (CTX_T)NULL && CTX_INDEX(env) >= 0 );
  if( ! bCtx ) 
    return getenv(env);
  else 
    return CTX_EVAL(string,env);
}

string MkPath(string direnv, string basename, string ext, char opt)
/* path = cons(env,dir_separation,basename,ext); allocs memory. Note:                   
                  opt = 'd'                     --> env = direnv        
   direnv  = "" & opt = 'c' & relative basename --> env = dirname(cwd) 
   direnv != "" & opt = '$'                     --> env = $direnv     
   direnv != "" & opt = 'e'                     --> env = getenv(direnv)
   direnv != "" & opt = 'p'                     --> env = findPath in  
                                                          getenv(direnv)
*/
{ char pbuf[STD_BUFFLEN+1]; string env = (string)NULL;
  BUG_NULL(basename);
  if( opt != 'd' && opt != '$' && opt != 'e' && opt != 'p' && opt != 'c' ) BUG;
  if ( ! STR_EMPTY(direnv) ) 
  {
    switch(opt)
    {
      case 'd':
        return( PathSink("",direnv,basename,ext) );
      case '$': 
        return( PathSink("$",direnv,basename,ext) );
      default : 
      { c_bool bCtx = ( CTX_ctx_val() != (CTX_T)NULL  && 
                        CTX_INDEX(direnv) >= 0         );
        if( ! bCtx ) env = getenv(direnv);
        else         env = CTX_EVAL(string,direnv);
        if( ! STR_EMPTY(env) )
        {
          if( opt == 'e' ) return( PathSink("",env,basename,ext) );
          else /* opt = 'p' */
          { PIT pit = PIT_make(env); string cp; string p;

            while( ( cp = PIT_read(pit) ) != NULL )
            {
              p = PathSink("",cp,basename,ext);
              if( IsPath(p) )
              {
                PIT_drop(pit); return( p );
              }
              else FreeMem(p);
            }
            PIT_drop(pit);
          }
        }
      }
    }
  }
  else
  {
    if( opt == 'c' && ! AbsolutPath(basename) )
    {
      assert0
      ( 
        getcwd(pbuf,STD_BUFFLEN+1) != 0, "directory '.' couldn't be accessed"
      );
      return( PathSink("",pbuf,basename,ext) );
    }
  }
  return( Str_printf("%s%s",basename,( STR_EMPTY(ext) ) ? "" : ext) );
}

static unsigned short filetype(string path)
/* Mode of regular Path 'path' */
{ struct stat buf;
  assert1(stat(path,&buf) == 0,"file information for '%s' not available",path);
  return buf.st_mode;
}

long PathMTime(string path)
/* file modification time of 'path' */
{ struct stat buf;
  assert1(stat(path,&buf) == 0,"file information for '%s' not available",path);
  return buf.st_mtime;
}

long Path_FileSize(string path)
/* the file size of 'path' */
{ struct stat buf;
  assert1(stat(path,&buf) == 0,"file information for '%s' not available",path);
  return buf.st_size;
}

#if defined( _MSDOS ) || defined( _WIN32 )
/*INTERFACE_OFF*/

bool IsDirPath(string path)
/* path = directory ? */
{
  return( (filetype(path) & S_IFMT) == S_IFDIR );
}

bool IsRegPath(string path)
/* path = regular file ? */
{
  return( (filetype(path) & S_IFMT) == S_IFREG );
}

bool IsCDevPath(string path)
/* path = character device ? */
{
  return( (filetype(path) & S_IFMT) == S_IFCHR );
}

bool IsBDevPath(string path)
/* path = block device ? */
{
  return( False );
}

bool IsFifoPath(string path)
/* path = FIFO ? */
{
  return( False );
}

#else
/*INTERFACE_ON*/

bool IsDirPath(string path)
/* path = directory ? */
{
  return( S_ISDIR(filetype(path)) );
}

bool IsRegPath(string path)
/* path = regular file ? */
{
  return( S_ISREG(filetype(path)) );
}

bool IsCDevPath(string path)
/* path = character device ? */
{
  return( S_ISCHR(filetype(path)) );
}

bool IsBDevPath(string path)
/* path = block device ? */
{
  return( S_ISBLK(filetype(path)) );
}

bool IsFifoPath(string path)
/* path = FIFO ? */
{
  return( S_ISFIFO(filetype(path)) );
}

#endif

/*I-------------------------- File I/O handling ----------------------------- */

FILE* TryOpnFile(string path, string access)
/* tries to open 'path' in mode 'access' ( MSDOS convention 'w|r[+]t|b' ) */
{ char accmode[4]; FILE* fp;
  BUG_NULL(path); BUG_NULL(access);
  bug0(strlen(access) < 4, "wrong access");
  strcpy(accmode,access);
#if !defined( MSDOS ) && !defined( _WIN32 )
  accmode[1] = '\0';
#endif
  fp = fopen(path,accmode);
  return( fp );
}

FILE* OpnFile(string path, string access)
/* opens 'path' in mode 'access' ( MSDOS convention 'w|r[+]t|b' ); 
   raises exception 
*/
{ FILE* fp = TryOpnFile(path,access);
  assert1( fp != (FILE*)NULL, "file %s couldn't be opened",path);
  return( fp );
}

FILE* TryOpenPath(string env, string file, string ext, string acc)
/* tries to open Path(env,file,ext) in mode 'acc' 
   ( MSDOS convention 'w|r[+]t|b' ) 
*/
{ FILE* fp; string p;
  p  = MkPath(env,file,ext,(char)(( *acc == 'w' ) ? 'e' : 'p'));
  fp = TryOpnFile(p,acc);
  FreeMem(p); return( fp );
}

FILE* OpenPath(string env, string file, string ext, string acc)
/* opens Path(env,file,ext) in mode 'acc' 
   ( MSDOS convention 'w|r[+]t|b' ); raises exception 
*/
{ FILE* fp; string p;
  p  = MkPath(env,file,ext,(char)(( *acc == 'w' ) ? 'e' : 'p'));
  fp = OpnFile(p,acc);
  FreeMem(p); return( fp );
}
