/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxScannerTest.C]     Scanner Test                                     */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2004 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */


#include <stdio.h>

#include "StyxStreamParser.h"
#include "StyxUtil.h"


using namespace std;
using namespace styx;


static void usage()
{
  fprintf(stderr,"\nusage: StyxScannerTest OPTIONS Language.ltbl\n");
  fprintf(stderr,"\nOPTIONS:\n");
  fprintf(stderr,"\n-l                  : enable n character look-ahead");
  fprintf(stderr,"\n-f FileToScan       : file to be scanned");
  fprintf(stderr,"\n-c Characterset     : characterset of the file to be scanned (utf8, wchar, unicode)");
  fprintf(stderr,"\n-k CharactersToSkip : characters to be ignored i.e. skipped by the scanner\n");
  fprintf(stderr,"\n-p IncludePath      : enable preprocessing with include path");
}

template<class TC>
static bool scan(CStyxScanner* scanner)
{ string token, tid;
  short  gcnt = scanner->getGroups();
  size_t tlen = 0;
  if( gcnt <= 0 )
  {
    for( short tcnt=scanner->getTokens(), i=0; i < tcnt; ++i )
    { 
      tid  = scanner->externalTokenID(token=scanner->getTokenID(i,-1));
      tlen = max(tlen,tid.length());
    }
  }
  else
  {
    for( short i=0; i < gcnt; ++i )
      for( short tcnt=scanner->getTokens(i), j=0; j < tcnt; ++j )
      {
        tid  = scanner->externalTokenID(token=scanner->getTokenID(j,i));
        tlen = max(tlen,tid.length());
      }
  }
  bool ok = true;
  while( (ok=scanner->nextToken()) )
  { basic_string<TC> value;
    bool unicode = (sizeof(TC) != sizeof(char));
    if( scanner->currentToken(token,value) )
    {
      tid = scanner->externalTokenID(token);
      printf
      (
        "LINE=%06ld, COL=%05ld, TOK=%-*s,",
        scanner->getLine(), scanner->getCol(),(int)tlen, tid.c_str()
      );
      if( unicode )
      { 
        printf(" VAL=%S\n",(wchar_t*)value.c_str());
      }
      else
      { 
        printf(" VAL=%s\n",(char*)value.c_str());
      }
    }
    else
    {
      printf("currentToken failed\n");
      break;
    }
    if( scanner->eos() ) break;
  }
  if( !ok ) printf("nextToken failed\n");
  return ok;
}

int main(int argc, char* argv[])
{ string lexpath, srcpath, content, cset, incpath; 
  bool lahead = false, preprocess = false;
  set<int> skip;
  int c = 0;
#ifdef _WIN32
  for( int i=1; i < argc; ++i )
  { string arg = argv[i];
    if( arg == "-l" ) lahead = true;
    else
    if( arg == "-f" )
    {
      if( i < argc - 1 && argv[i+1][0] != '-' )
      {
        ++i; srcpath = argv[i];
      }
    }
    else
    if( arg == "-p" )
    {
      preprocess = true;
      if( i < argc - 1 && argv[i+1][0] != '-' )
      {
        ++i; incpath = argv[i];
      }
    }
    else
    if( arg == "-c" )
    {
      if( i < argc - 1 && argv[i+1][0] != '-' )
      {
        ++i; cset = argv[i];
      }
    }
    else
    if( arg == "-k" )
    {
      if( i < argc - 1 && argv[i+1][0] != '-' )
      {
        ++i; 
        size_t len=strlen(argv[i]);
        for( size_t j=0; j < len; ++j )
          skip.insert((int)argv[i][j]);
      }
    }
    else
    if( arg[0] == '-' )
    {
      usage();
      return 1;
    }
    else
    {
      lexpath = arg; 
      break;
    }
  }
  if( lexpath.length() == 0 )
  {
    usage();
    return 1;
  }
#else
  while ((c = getopt(argc, argv, "f:p:c:k:l")) > 0)
  {
    switch (c)
    {
      case 'l' : // look-ahead
        lahead = true;
        break;
      case 'f' :
        if (optarg != NULL)
          srcpath = optarg;
        break;
      case 'p' :
        preprocess = true;
        if (optarg != NULL)
          incpath = optarg;
        break;
      case 'c' :
        if (optarg != NULL)
          cset = optarg;
        break;
      case 'k' :
        if (optarg != NULL)
        {
          for( int len = strlen(optarg), i=0; i < len; ++i )
            skip.insert((int)optarg[i]);
        }
        break;
      default  :
        usage();
        return 1;
    }
  }
  if( optind < argc )
  {
    lexpath = argv[optind];
  }
  else
  {
    usage();
    return 1;
  }
#endif
  CStyxScanner* scanner = 0;
  if( preprocess )
  {
    scanner = new CStyxPScanner(lahead);
    if( scanner != 0 )
    { CStyxPScanner::M_pardfn parmap;
      if( incpath.length() > 0 )
        parmap[CStyxPScanner::IDX_INC_PATH] = incpath;
      parmap[CStyxPScanner::IDX_INC_CSET] = cset;
      ((CStyxPScanner*)scanner)->setParameters(parmap);
    }
  }
  else scanner = new CStyxScanner(lahead);
  if( scanner == 0 || !scanner->loadTableFile(lexpath) )
  {
    printf("loadTableFile(%s) failed\n",lexpath.c_str());
    if( scanner ) delete scanner;
    return 1;
  }
  CStyxStream* cstream = 0;
  if( srcpath.length() > 0 )
  { 
    if( cset.length() > 0 && cset == "utf8" )
    {
      if( !file2text(srcpath,content) ) 
      {
        delete scanner;
        return 1;
      }
      wstring wcontent = styx::multibyte2unicode(content);
      cstream = new TStyxStringStreamU(wcontent,srcpath);
    }
    else
    if( cset.length() > 0 && (cset == "wchar" || cset == "unicode" ) )
      cstream = new TStyxFileStreamU(srcpath);
    else cstream = new TStyxFileStreamS(srcpath);
  }
  else
  {
    srcpath = "<stdin>";
    while( (c=getc(stdin)) != EOF ) content += c;
    cstream = new TStyxStringStreamS(content,srcpath);
  }
  if( !cstream || !scanner->scanStream(cstream,skip) )
  {
    printf("scanStream failed\n");
    if( cstream ) delete cstream;
    delete scanner;
    return 1;
  }
  int rc = 0;
  if( !cstream->unicode() )
  {
    rc = !scan<char>(scanner);
  }
  else
  {
    rc = !scan<wchar_t>(scanner);
  }
  delete cstream;
  delete scanner;
  return rc;
}
