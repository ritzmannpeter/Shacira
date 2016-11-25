/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxParseTreeTest.C]   Parse Tree Test                                  */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2005 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */


#include <stdio.h>

#include "StyxParseTree.h"
#include "StyxUtil.h"


using namespace styx;


static void usage()
{
  fprintf(stderr,"\nusage: StyxParseTreeTest OPTIONS Language.ltbl Language.ptbl\n");
  fprintf(stderr,"\nOPTIONS:\n");
  fprintf(stderr,"\n-l                  : enable n character look-ahead");
  fprintf(stderr,"\n-e                  : enable early reduction");
  fprintf(stderr,"\n-a                  : produce an abstract syntax tree");
  fprintf(stderr,"\n-s StartNT          : start symbol to be reduced");
  fprintf(stderr,"\n-f FileToParse      : file to be parsed");
  fprintf(stderr,"\n-c Characterset     : characterset of the file to be parsed (utf8, wchar, unicode)");
  fprintf(stderr,"\n-k CharactersToSkip : characters to be ignored i.e. skipped by the scanner\n");
  fprintf(stderr,"\n-p IncludePath      : enable preprocessing with include path");
}


template <class TC>
static int parse
           (
             CStyxParseTable& ptable, CStyxScanner* scanner, 
             string startnt, bool early, bool ast
           )
{ TStyxTreeParser<TC> p(&ptable,scanner,false,ast);
  if( !p.setParseTable(&ptable) )
  {
    printf("setParseTable failed\n");
    return 1;
  }
  if( !p.setTokenStream(scanner) )
  {
    printf("setTokenStream failed\n");
    return 1;
  }
  if( !p.parse(startnt,early) )
  {
    printf("parse failed\n");
    return 1;
  }
  printf("parse=%s\n",p.getSyntaxErrorCount()==0?"OK":"NOT OK");
  TStyxParseTree<TC>* t = p.extractParseTree();
  if( t ) 
  {
    t->print();
/*
    cout << "\nas string:\n";
    bool unicode = (sizeof(TC) != sizeof(char));
    if( unicode )
      printf("%S\n",t->asString().c_str());
    else
      printf("%s\n",t->asString().c_str());
    TStyxParseTree<TC>* r = TStyxParseTree<TC>::copy(t);
    r->print();
    delete r;
*/
    typename TStyxTree<StyxNode<TC> >::DF_Iter dfpos = t->dfbegin();
    while( ! dfpos.end() )
    {
      TStyxTree<StyxNode<TC> >* r = dfpos.getTerm();
      if( dfpos.getState() == TI_STATE_PRAE )
      {
        if( r ) cout << "PRAE: " << r->getNode().name[0].c_str() << "\n";
      }
      else
      if( dfpos.getState() == TI_STATE_POST )
      {
        if( r ) cout << "POST: " << r->getNode().name[0].c_str() << "\n";
      }
      ++dfpos;
    }
    delete t;
  }
  return 0;
}

int main(int argc, char* argv[])
{ string lexpath, cfgpath, srcpath, startnt, content, cset, incpath; 
  bool lahead = false, early = false, ast = false, preprocess = false;
  set<int> skip;
  int c = 0;
#ifdef _WIN32
  for( int i=1; i < argc; ++i )
  { string arg = argv[i];
    if( arg == "-l" ) lahead = true;
    else
    if( arg == "-e" ) early  = true;
    else
    if( arg == "-a" ) ast    = true;
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
    if( arg == "-s" )
    {
      if( i < argc - 1 && argv[i+1][0] != '-' )
      {
        ++i; startnt = argv[i];
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
      if( lexpath.length() == 0 ) lexpath = arg; 
      else
      {
        cfgpath = arg; 
        break;
      }
    }
  }
  if( lexpath.length() == 0 || cfgpath.length() == 0 )
  {
    usage();
    return 1;
  }
#else
  while ((c = getopt(argc, argv, "f:p:s:c:k:lea")) > 0)
  {
    switch (c)
    {
      case 'l' : // look-ahead
        lahead = true;
        break;
      case 'e' : // early reduction
        early  = true;
        break;
      case 'a' : // abstract syntax tree
        ast    = true;
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
      case 's' :
        if (optarg != NULL)
          startnt = optarg;
        break;
      default  :
        usage();
        return 1;
    }
  }
  if( optind < argc - 1 )
  {
    lexpath = argv[optind];
    cfgpath = argv[optind+1];
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
  CStyxParseTable ptable;
  if( !ptable.loadTableFile(cfgpath) )
  {
    printf("loadTableFile(%s) failed\n",cfgpath.c_str());
    if( cstream ) delete cstream;
    delete scanner;
    return 1;
  }
  int rc = 0;
  if( cstream->unicode() )
  {
    rc = parse<wchar_t>(ptable,scanner,startnt,early,ast);
  }
  else
  {
    rc = parse<char>(ptable,scanner,startnt,early,ast);
  }
  delete cstream;
  delete scanner;
  return rc;
}
