/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [com.c]            ultimative Dokumentations-Utility                       */
/*                                                                            */
/* Copyright (c) 1993 by D\olle, Manns.                                       */
/*----------------------------------------------------------------------------*/

#define USAGE "\
   Argument : [-r] Datei/Verzeichnisname(n)                             \n\
   In den ersten 2000 Zeichen der Quelle wird nach [Dateiname] gesucht. \n\
   Alle folgenden Zeichen bis zum Zeilenende oder '  ' bilden dann      \n\
   den gesuchten Kommentar.                                             \n\
   Ausgabe / Datei : 'Dateiname : Kommentar'\n"


#include "stdosx.h"
#include "pathes.h"
#include "dicts.h"
#include "sink.h"
#include "com_get.h"

#include "com_cim.h"

/* MSDOS-Limit */
#define MAX_FILELEN 12

#define recflg CTX_EVAL(bool,"r") 

void print_comfile(string path, string basename)
{ string com = Com_Get(path);
  if( MAX_FILELEN >= strlen(basename) )
    fprintf(stdout,"%*s : %s\n",MAX_FILELEN,basename,com);
  else
    fprintf(stdout,"%s : %s\n",basename,com);
}

void print_comdir(string path, string pat, bool recursive)
{ DII dii; string name; string odirname = path;
  fprintf(stdout,"\nVerzeichnis : %s\n\n",path);
  if( recursive )
  {
    DII_SFORALL_R(dii,path,pat)
    { string basename = DII_get_file(dii);
      string dirname  = DII_get_path(dii);
      if( strcmp(dirname,odirname) )
      {
        fprintf(stdout,"\nVerzeichnis : %s\n\n",dirname);
        if( odirname != path ) FreeMem(odirname);
        odirname = dirname;
      }
      else FreeMem(dirname);
      if( IsRegPath(name = MkPath(odirname,basename,"",'d')) )
        print_comfile(name,basename);
      FreeMem(basename); FreeMem(name);
    }
    if( odirname != path ) FreeMem(odirname);
  }
  else
    DII_SFORALL(dii,path,pat)
    { string basename = DII_get_file(dii);
      if( IsRegPath(name = MkPath(path,basename,"",'d')) )
        print_comfile(name,basename);
      FreeMem(basename); FreeMem(name);
    }
}

static bool isPattern(string suffix)
{ int len = strlen(suffix), i;
  for( i=0; i < len; ++i )
    if( suffix[i] == '*' || suffix[i] == '?' ) return True;
  return False;
}

int main(int argc, string argv[])
{ char cwdbuf[STD_BUFFLEN+1]; int cnt, i;
  CTX_init_com(argc, argv);
  if( ( cnt = CTX_argcnt() ) == 0 ) 
  {
    assert0(getcwd(cwdbuf,STD_BUFFLEN+1),"directory '.' couldn't be accessed");
    print_comdir(cwdbuf,"*",recflg);
  }
  else
  { string name, pat, base, pre, suf; bool ispat = False;
    for( i = 0; i < cnt; ++i )
    {
      name  = MkPath("",CTX_ARGVAL(string,i),"",'c');
      pre   = FilePrefix(name);
      suf   = FileSuffix(name);
      base  = BaseFile(name);
      pat   = Str_printf("%s%s",base,suf);
      ispat = isPattern(pat);
      if( ! ( ispat || IsPath(name) ) )
      {
        fprintf(stderr,"%s: nicht gefunden\n",name);
      }
      else
      {
        if( ispat ) print_comdir(pre,pat,recflg);
        else
        {
          if( IsRegPath(name) ) print_comfile(name,pat);
          if( IsDirPath(name) ) print_comdir(name,"*",recflg);
        }
      }
      FreeMem(name); FreeMem(pre); FreeMem(suf); FreeMem(base); FreeMem(pat);
    }
  }
  CTX_quit();
  BUG_CORE;
  return(0);
}

