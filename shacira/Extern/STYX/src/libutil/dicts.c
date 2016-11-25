/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [dicts.c]               Type: Dictionary Iterator                        */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

#include "dict.h"
#include "otab.h"

#include "charlib.h"


/*I---------------------- The Type ----------------------------------------- */

/*!!
   The dictionary iterator provides sequentiell, platform-independant access to
   a specified part of the file system.
   Supported platforms are Unix and Windows.
*/

AbstractType(DII); /* Abstract dictionary iterator type */

ConcreteType(DII_IMP)
{
  OT_Tab DirTab;
  Dir    Directory;
  string Pattern;
  Dentry Entry;
  bool   skip;
};

/* ---------------------- Auxiliary Functions ------------------------------ */

static bool lower_matches(string str, string pat)
{
#if defined( MSDOS ) || defined(_WIN32)
  StrToLower(str);
#endif
  return Str_matches(str,pat);
}

static void nextEntry(DII dii)
/* next dictionary entry ( non recursive ) */
{ DII_IMP d = (DII_IMP) dii;
  for
  (
    d->Entry = Dir_read(d->Directory);
    d->Entry != (Dentry)NULL && 
    ! lower_matches(Dentry_name(d->Entry),d->Pattern);
    d->Entry = Dir_read(d->Directory)
  );
}

static void nextEntryR(DII dii)
/* next dictionary entry ( recursive ) */
{ DII_IMP d = (DII_IMP) dii; static INT pos = 1; bool found = False;
  while( ! found )
  {
    if( ( d->Entry = Dir_read(d->Directory) ) != (Dentry)NULL )
    {
      if( strcmp(Dentry_name(d->Entry),"..")  &&
          strcmp(Dentry_name(d->Entry),".")   &&
          Dentry_isDir(d->Entry)               ) 
        pos = OT_P_INS(d->DirTab,Dentry_path(d->Entry),pos) + 2;
      found = lower_matches(Dentry_name(d->Entry),d->Pattern);
    }
    else
    { Dir directory = (Dir)NULL; string path;
      while
      ( 
        OT_CNT(d->DirTab) > 0 &&
        ( directory = Dir_open(path = OT_GET(string,d->DirTab,0)) ) == (Dir)NULL
      )
      {
        OT_DEL_E(d->DirTab,0);
        if( ! d->skip ) 
          bug1(False,"directory '%s' couldn't be opended",path);
        else
          fprintf(STDERR,"directory '%s' couldn't be opended",path);
      }
      Dir_close(d->Directory);
      if( ( d->Directory = directory ) != (Dir)NULL )
      {
        OT_DEL_E(d->DirTab,0); pos = 1;
      }
      else found = True;
    }
  }
}

/*I--------------------------- Create & Drop -------------------------------- */

DII DII_make
    (
      string PathName, string Pattern, 
      bool recursive, bool skipErr
    )
/* creates a ['recursive'] dictionary iterator for 
   directory 'PathName' and file 'Pattern'
   'skipErr' --> error message on open failure, otherwise the program aborts
*/
{ DII_IMP dii = (DII_IMP)NULL; Dir directory = Dir_open(PathName);
  if( directory != (Dir)NULL )
  {
    dii = New(DII_IMP);
    dii->Directory = directory;
    dii->Entry     = (Dentry)NULL;
    dii->Pattern   = StrCopy(Pattern);
    dii->skip      = skipErr;
    if( recursive )
    {
      dii->DirTab = OT_CREATE(string,primCopy,FreeMem,strEqual);
      nextEntryR((DII) dii);
    }
    else
    {
      dii->DirTab = (OT_Tab)NULL;
      nextEntry((DII) dii);
    }
  }
  else
  {
    if( ! skipErr ) 
      bug1(False,"directory '%s' couldn't be opended",PathName);
    else            
      fprintf(STDERR,"directory '%s' couldn't be opended",PathName);
  }
  return (DII) dii;
}

void DII_drop(DII dii)
/* drops dictionary iterator 'dii' */
{ DII_IMP d = (DII_IMP) dii;
  if( d != (DII_IMP)NULL )
  {
    if( d->Directory != (Dir)NULL ) Dir_close(d->Directory);
    FreeMem(d->Pattern);
    if( d->DirTab != (OT_Tab)NULL ) OT_DEL_T(d->DirTab);
    FreeMem(d);
  }
}

/*I------------------------- Dictionary iterator access -------------------- */

bool DII_empty(DII dii)
/* empty dictionary iterator ? */
{ DII_IMP d = (DII_IMP) dii;
  return
  ( 
    d == (DII_IMP)NULL || d->Directory == (Dir)NULL ||
    ( d->Entry == (Dentry)NULL && 
      ( d->DirTab == (OT_Tab)NULL || ! OT_CNT(d->DirTab) ) )
  );
}

void DII_next(DII dii)
/* next dictionary entry */
{ DII_IMP d = (DII_IMP) dii;
  if( d->DirTab != (OT_Tab)NULL ) nextEntryR(dii);
  else                            nextEntry(dii);
}

bool DII_isFile(DII dii)
/* dictionary entry = file ? */
{
  return( Dentry_isFile(((DII_IMP)dii)->Entry) );
}

bool DII_isDir(DII dii)
/* dictionary entry = directory ? */
{
  return( Dentry_isDir(((DII_IMP)dii)->Entry) );
}

bool DII_isCDev(DII dii)
/* dictionary entry = character device ? */
{
  return( Dentry_isCDev(((DII_IMP)dii)->Entry) );
}

bool DII_isBDev(DII dii)
/* dictionary entry = block device ? */
{
  return( Dentry_isBDev(((DII_IMP)dii)->Entry) );
}

bool DII_isFifo(DII dii)
/* dictionary entry = FIFO ? */
{
  return( Dentry_isFifo(((DII_IMP)dii)->Entry) );
}

string DII_get_file(DII dii)
/* filename of dictionary entry; allocs memory */
{
  return StrCopy(Dentry_name(((DII_IMP)dii)->Entry));
}

string DII_get_base(DII dii)
/* basename of dictionary entry; allocs memory */
{ int    i;
  string s   = Dentry_name(((DII_IMP)dii)->Entry);
  int    len = strlen(s);
  for (i = len-1; i >= 0 && s[i] != '.'; i--);
  return SubStrCopy(s,s[i]=='.'?i:len);
}

string DII_get_ext(DII dii)
/* extension of dictionary entry; allocs memory */
{ int    i;
  string s   = Dentry_name(((DII_IMP)dii)->Entry);
  int    len = strlen(s);
  for (i = len-1; i >= 0 && s[i] != '.'; i--);
  return SubStrCopy(s+i,s[i]=='.'?len-i:0);
}

string DII_get_path(DII dii)
/* path of dictionary entry; allocs memory */
{
  return StrCopy(Dir_name(((DII_IMP)dii)->Directory));
}

/*I---------------------- Convenient iterator macros ----------------------- */

/*DOC_INTERFACE_COPY_ON*/
#define DII_FORALL(dii,Path,Pattern)           \
for (dii = DII_make(Path,Pattern,False,False); \
DII_empty(dii)?DII_drop(dii),False:True; DII_next(dii))

#define DII_FORALL_R(dii,Path,Pattern)        \
for (dii = DII_make(Path,Pattern,True,False); \
DII_empty(dii)?DII_drop(dii),False:True; DII_next(dii))

#define DII_SFORALL(dii,Path,Pattern)         \
for (dii = DII_make(Path,Pattern,False,True); \
DII_empty(dii)?DII_drop(dii),False:True; DII_next(dii))

#define DII_SFORALL_R(dii,Path,Pattern)      \
for (dii = DII_make(Path,Pattern,True,True); \
DII_empty(dii)?DII_drop(dii),False:True; DII_next(dii))
/*DOC_INTERFACE_COPY_OFF*/
