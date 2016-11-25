/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxScannerTest.cs]    Scanner Test                                     */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2009 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */


using System;
using System.Text;
using System.IO;
using System.Collections;
using styx;



public class StyxScannerTest
{

  static void usage()
  {
    Console.Error.WriteLine("\nusage: StyxScannerTest OPTIONS Language.ltbl\n");
    Console.Error.WriteLine("\nOPTIONS:\n");
    Console.Error.WriteLine("\n-l                  : enable n character look-ahead");
    Console.Error.WriteLine("\n-f FileToScan       : file to be scanned");
    Console.Error.WriteLine("\n-c Characterset     : characterset of the file to be scanned (utf8, wchar, unicode)");
    Console.Error.WriteLine("\n-k CharactersToSkip : characters to be ignored i.e. skipped by the scanner\n");
    Console.Error.WriteLine("\n-p IncludePath      : enable preprocessing with include path");
  }
  
  static bool scan(ref CStyxScanner scanner)
  { string token = "", tid = "";
    short  gcnt = scanner.getGroups();
    int    tlen = 0;
    if( gcnt <= 0 )
    {
      for( short tcnt=scanner.getTokens(), i=0; i < tcnt; ++i )
      { 
        token=scanner.getTokenID(i,-1);
        tid  = scanner.externalTokenID(ref token);
        tlen = Math.Max(tlen,tid.Length);
      }
    }
    else
    {
      for( short i=0; i < gcnt; ++i )
      {
        for( short tcnt=scanner.getTokens(i), j=0; j < tcnt; ++j )
        {
          token=scanner.getTokenID(j,i);
          tid  = scanner.externalTokenID(ref token);
          tlen = Math.Max(tlen,tid.Length);
        }
      }
    }
    bool ok = true;
    while( (ok=scanner.nextToken()) )
    { 
      string Value = "";
      if( scanner.currentToken(ref token,ref Value) )
      {
        tid = scanner.externalTokenID(ref token);
/*
        Console.WriteLine
        (
          "LINE=" + scanner.getLine() + ", COL=" + scanner.getCol() +
          ", TOK=" + tid + ", VAL=" + Value + "\n"
        );
*/
        Console.WriteLine
        (
          "LINE={0,6:d}, COL={1,5:d}, TOK={2}, VAL={3}",
          scanner.getLine(),scanner.getCol(),tid.PadRight(tlen),Value
        );
      }
      else
      {
        Console.Error.WriteLine("currentToken failed\n");
        break;
      }
      if( scanner.eos() ) break;
    }
    if( !ok ) Console.Error.WriteLine("nextToken failed\n");
    return ok;
  }
  
  public static int Main(string[] args)
  { 
    string lexpath = "", srcpath = "", content = "", cset = "", incpath = ""; 
    bool lahead = false, preprocess = false;
    Hashtable/*uint,null*/ skip = new Hashtable();
    int c = 0;
    for( int i=0; i < args.Length; ++i )
    { 
      string arg = args[i];
      if( arg == "-l" ) lahead = true;
      else
      if( arg == "-f" )
      {
        if( i < args.Length - 1 && args[i+1][0] != '-' )
        {
          ++i; srcpath = args[i];
        }
      }
      else
      if( arg == "-p" )
      {
        preprocess = true;
        if( i < args.Length - 1 && args[i+1][0] != '-' )
        {
          ++i; incpath = args[i];
        }
      }
      else
      if( arg == "-c" )
      {
        if( i < args.Length - 1 && args[i+1][0] != '-' )
        {
          ++i; cset = args[i];
        }
      }
      else
      if( arg == "-k" )
      {
        if( i < args.Length - 1 && args[i+1][0] != '-' )
        {
          ++i; 
          int len = args[i].Length;
          for( int j=0; j < len; ++j )
          {
            uint sc = Convert.ToUInt32(args[i][j]);
            skip[sc] = null;
          }
        }
      }
      else
      if( arg[0] == '-' )
      {
        StyxScannerTest.usage();
        return 1;
      }
      else
      {
        lexpath = arg; 
        break;
      }
    }
    if( lexpath.Length == 0 )
    {
      StyxScannerTest.usage();
      return 1;
    }
    CStyxScanner scanner = null;
    if( preprocess )
    {
      scanner = new CStyxPScanner(lahead,true);
      if( scanner != null )
      { 
        Hashtable/*short,string*/ parmap = new Hashtable();
        if( incpath.Length > 0 )
          parmap[(short)CStyxPScanner.EStyxParIndex.IDX_INC_PATH] = incpath;
        parmap[(short)CStyxPScanner.EStyxParIndex.IDX_INC_CSET] = cset;
        ((CStyxPScanner)scanner).setParameters(ref parmap);
      }
    }
    else scanner = new CStyxScanner(lahead,false);
    if( scanner == null || !scanner.loadTableFile(lexpath) )
    {
      Console.Error.WriteLine("loadTableFile(" + lexpath + ") failed\n");
      return 1;
    }
    CStyxStream cstream = null;
    if( srcpath.Length > 0 )
    { 
      cstream = new CStyxFileStream(srcpath,"");
    }
    else
    {
      srcpath = "<stdin>";
      while( (c=Console.In.Read()) != -1 ) content += c;
      cstream = new CStyxStringStream(content,srcpath);
    }
    if( cstream == null || !scanner.scanStream(ref cstream,ref skip) )
    {
      Console.Error.WriteLine("scanStream failed\n");
      return 1;
    }
    int rc = StyxScannerTest.scan(ref scanner) ? 0 : 1;
    return rc;
  }

}
