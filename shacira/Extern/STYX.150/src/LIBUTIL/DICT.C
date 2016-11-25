/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [dict.c]                    Type: Dictionary                             */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

#include "pathes.h"

/*!!
   [dict] provides platform-independant access to directories and their entries.
   Supported platforms are Unix and Windows.
*/

/* ---------------- Common Types, Constants & Globals --------------------- */

/*I---------------------- Types ------------------------------------------- */

AbstractType(Dir);    /* Abstract directory type       */
AbstractType(Dentry); /* Abstract directory entry type */

#define DICT_D_IMP(d) ((Dir_IMP)(d))
#define DICT_E_IMP(e) ((Dir_IMP)(e))

/*INTERFACE_OFF*/

/* ---------------------- Types and Constants ----------------------------- */

#if defined( _MSDOS ) && ! defined( _WIN32 )

#include <dos.h>

ConcreteType(Dir_IMP)
{
  bool first;
  string PathName;
  struct _find_t alpha;
};

/* -------------------------- Access Directory ---------------------------- */

static string setquery(string PathName)
/* "setzen" der Query */
{ string Query;

  if( strlen(PathName) > 0 )
  {
    Query = (string)NewMem(strlen(PathName)+4+1);
    strcpy(Query,PathName);
    strcat(Query,"\\*.*");
  }
  else
    Query = StrCopy("*.*");
  return( Query );
}

Dir Dir_open(string PathName)
{ Dir_IMP dosdir;

  BUG_NULL(PathName);
  dosdir = New(Dir_IMP);
  dosdir->first = True;
  dosdir->PathName = StrCopy(PathName);
  return( (Dir)dosdir );
}

Dentry Dir_read(Dir Directory)
{ string Query;
  int ret;

  BUG_NULL(Directory);
  if( DICT_D_IMP(Directory)->first )
  {
    Query = setquery(DICT_D_IMP(Directory)->PathName);
    ret = _dos_findfirst(Query,0,&DICT_D_IMP(Directory)->alpha);
    FreeMem(Query);
    DICT_D_IMP(Directory)->first = False;
  }
  else
    ret = _dos_findnext(&DICT_D_IMP(Directory)->alpha);
  return( ( ret != 0 ) ? (Dentry)NULL : (Dentry)Directory );
}

/* --------------------- Access Directory Entry --------------------------- */

string Dentry_name(Dentry Entry)
{
  BUG_NULL(Entry);
  return( DICT_E_IMP(Entry)->alpha.name );
}

#else
#ifdef _WIN32

ConcreteType(Dir_IMP)
{
  bool first;
  string PathName;
  struct _finddata_t alpha;
  long hdl;
};

/* -------------------------- Access Directory ---------------------------- */

static string setquery(string PathName)
/* "setzen" der Query */
{ string Query,s;
  if( strcmp(PathName,"\\") == 0 || strcmp(PathName,"/") == 0 )
  {
    Query = StrCopy("/*");
  }
  else
  if( strlen(PathName) > 0 )
  {
    Query = (string)NewMem(strlen(PathName)+4+1);
    strcpy(Query,PathName);
    strcat(Query,"/*"); /* FIXME: we mean *all* files. */
  }
  else
    Query = StrCopy("*"); /* FIXME: we mean *all* files. */
  for (s = Query; *s; s++) if (*s == '/') *s = '\\';
  return( Query );
}

Dir Dir_open(string PathName)
{ Dir_IMP dosdir;

  BUG_NULL(PathName);
  dosdir = New(Dir_IMP);
  dosdir->first = True;
  dosdir->PathName = StrCopy(PathName);
  return( (Dir)dosdir );
}

Dentry Dir_read(Dir Directory)
{ string Query;
  int ret;

  BUG_NULL(Directory);
  if( DICT_D_IMP(Directory)->first )
  {
    Query = setquery(DICT_D_IMP(Directory)->PathName);
    DICT_D_IMP(Directory)->hdl 
      = _findfirst(Query,&DICT_D_IMP(Directory)->alpha);
    FreeMem(Query);
    DICT_D_IMP(Directory)->first = False;
    ret = DICT_D_IMP(Directory)->hdl == -1 ? -1 : 0;
  }
  else
    ret = _findnext
          ( DICT_D_IMP(Directory)->hdl,
            &DICT_D_IMP(Directory)->alpha );
  return( ( ret == -1 ) ? (Dentry)NULL : (Dentry)Directory );
}

/* --------------------- Access Directory Entry --------------------------- */

string Dentry_name(Dentry Entry)
{
  BUG_NULL(Entry);
  return( DICT_E_IMP(Entry)->alpha.name );
}

#else

/*INTERFACE_ON*/

ConcreteType(Dir_IMP)
{
  string PathName;
  DIR* dirp;
  struct dirent* dp;
};

/*I-------------------------- Directory access ---------------------------- */

Dir Dir_open(string PathName)
/* open directory 'PathName' */
{ Dir_IMP unixdir = (Dir_IMP)NULL; DIR* dirp;

  BUG_NULL(PathName);
  if( ( dirp = opendir(PathName) ) != NULL )
  {
    unixdir = New(Dir_IMP);
    unixdir->PathName = StrCopy(PathName);
    unixdir->dirp = dirp;
  }
  return( (Dir)unixdir );
}

Dentry Dir_read(Dir Directory)
/* next directory entry */
{
  BUG_NULL(Directory);
  DICT_D_IMP(Directory)->dp = readdir(DICT_D_IMP(Directory)->dirp);
  return( ( DICT_D_IMP(Directory)->dp == NULL ) ?
          (Dentry)NULL : (Dentry)Directory );
}

/* --------------------- Access Directory Entry --------------------------- */

string Dentry_name(Dentry Entry)
/* name of 'Entry' */
{
  BUG_NULL(Entry);
  return( DICT_E_IMP(Entry)->dp->d_name );
}

#endif
#endif

/* ------------------------ Common Interface Functions -------------------- */

Dir Dentry_open(Dentry Entry)
/* open 'Entry' */
{ Dir d; string basename = Dentry_name(Entry); string path;

  bug0(! strcmp(basename,".") || ! strcmp(basename,".."),"");
  path = MkPath(DICT_E_IMP(Entry)->PathName,basename,"",'d');
  d = Dir_open(path); 
  FreeMem( path ); return( d );
}

string Dentry_path(Dentry Entry)
/* full path of 'Entry'; allocs memory */
{ 
  return( MkPath(DICT_E_IMP(Entry)->PathName,Dentry_name(Entry),"",'d') );
}

bool Dentry_isDir(Dentry Entry)
/* 'Entry' = directory ? */
{ string basename = Dentry_name(Entry); string path; bool res;

  if( ! strcmp(basename,".") || ! strcmp(basename,"..") ) return( True );
  path = MkPath(DICT_E_IMP(Entry)->PathName,basename,"",'d');
  res = IsDirPath(path);
  FreeMem( path ); return( res );
}

bool Dentry_isFile(Dentry Entry)
/* 'Entry' = regular file ? */
{ string basename = Dentry_name(Entry); string path; bool res;

  if( ! strcmp(basename,".") || ! strcmp(basename,"..") ) return( False );
  path = MkPath(DICT_E_IMP(Entry)->PathName,basename,"",'d');
  res = IsRegPath(path);
  FreeMem( path ); return( res );
}

bool Dentry_isCDev(Dentry Entry)
/* 'Entry' = character device ? */
{ string basename = Dentry_name(Entry); string path; bool res;

  if( ! strcmp(basename,".") || ! strcmp(basename,"..") ) return( False );
  path = MkPath(DICT_E_IMP(Entry)->PathName,basename,"",'d');
  res = IsCDevPath(path);
  FreeMem( path ); return( res );
}

bool Dentry_isBDev(Dentry Entry)
/* 'Entry' = block device ? */
{ string basename = Dentry_name(Entry); string path; bool res;

  if( ! strcmp(basename,".") || ! strcmp(basename,"..") ) return( False );
  path = MkPath(DICT_E_IMP(Entry)->PathName,basename,"",'d');
  res = IsBDevPath(path);
  FreeMem( path ); return( res );
}

bool Dentry_isFifo(Dentry Entry)
/* 'Entry' = FIFO ? */
{ string basename = Dentry_name(Entry); string path; bool res;

  if( ! strcmp(basename,".") || ! strcmp(basename,"..") ) return( False );
  path = MkPath(DICT_E_IMP(Entry)->PathName,basename,"",'d');
  res = IsFifoPath(path);
  FreeMem( path ); return( res );
}

string Dir_name(Dir Directory)
/* name of 'Directory' */
{
  BUG_NULL(Directory);
  return( DICT_D_IMP(Directory)->PathName );
}

void Dir_close(Dir Directory)
/* close 'Directory' */
{
  BUG_NULL(Directory);
  FreeMem(DICT_D_IMP(Directory)->PathName);
#ifdef _WIN32
  _findclose(DICT_D_IMP(Directory)->hdl);
#endif
  FreeMem(Directory);
}
