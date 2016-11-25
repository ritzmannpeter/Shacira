/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxScanner.h]      Styx Scanner Implementation (C++)                   */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2003 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_SCANNER_INCL
#define STYX_SCANNER_INCL


using namespace std;

#include <stdio.h>
#include <wctype.h>
#include <string>
#include <vector>
#include <map>
#include <set>


namespace styx
{

  /* all UCS4 character */
  const unsigned long SCN_CHAR_SET_SIZE = (0xFFFFFFFFu); 

  /* token IDs within a dyck scanner */
  const int SCN_DYCKTOKEN_PREFIX  = 1;
  const int SCN_DYCKTOKEN_SUFFIX  = 2;
  const int SCN_DYCKTOKEN_PATTERN = 3;

  const int SCN_FLG_IgnoreToken = 1;  /* token has to be ignored          */
  const int SCN_FLG_IgnoreCase  = 2;  /* case insensitive token           */
  const int SCN_FLG_EofToken    = 4;  /* eof token in embedded language   */
  const int SCN_FLG_SwitchToken = 8;  /* switch to/from embedded language */
  const int SCN_FLG_CfgToken    = 16; /* embedded language token          */
  const int SCN_FLG_IndentToken = 32; /* (de)indent token                 */

  
  class CStyxStream
  {
  protected:
    string File;
    /* cC_eof = -1 ==> binary, default=0 (text) */
    int    cEof;
  
  public:
    CStyxStream();
    CStyxStream(string Path);
    virtual ~CStyxStream();
  
    virtual int     sgetc();
    virtual bool    eof(int c);
    virtual bool    unicode();
    virtual string& getFile(); 
  };
  
  class CStyxStringStream : public CStyxStream
  {
  protected:
    string   txt;
    long int pos;
  
  public:
    CStyxStringStream();
    CStyxStringStream(string ntxt);
    virtual ~CStyxStringStream();
  
    virtual void    setText(string ntxt);
    virtual string& getText();
    virtual int     sgetc();
  };
  
  class CStyxScanner;
  
  class CStyxScanner
  {
  public:
    typedef basic_string<wchar_t >   wstring;
    typedef unsigned char            byte;
    typedef vector<string>           V_string;
    typedef vector<long  >           V_long;
    typedef vector<short >           V_short;
    typedef vector<byte >            V_byte;
    typedef vector<CStyxScanner>     V_scanner;
    typedef map<short,short>         M_short;
    typedef set<int >                S_int;
    typedef map<short,CStyxScanner*> M_dscanner;
    typedef bool (CStyxScanner::* T_next)();
  
  protected:
    string     Name;     /* lexical language ( or group ) name */
    /* single scanner */
    V_long     StaEdg;   /* [States] -> first edge             */
    V_short    StaFin;   /* [States] -> (-1 or token)          */
    wstring    EdgeC ;   /* [Edges]  -> lower character        */
    V_long     EdgeS ;   /* [Edges]  -> State                  */
    V_string   TokId ;   /* [Tokens] -> string                 */
    V_byte     Flags ;   /* [Tokens] -> ignore token           */
    /* group scanner  */
    V_scanner  GrpScn;   /* group scanners                     */
    M_short    Switch;   /* Token -> Group                     */
    /* dyck token specification */
    V_short    dyckidx;  /* [dyckcnt] -> token index           */
    V_scanner  dyckpat;  /* [dyckcnt] -> dyck scanner          */
    M_dscanner dscanner; /* token -> dyck scanner              */
  
    /* current scan stream */
    CStyxStream* cStream;
    /* token & stream location */
    long         cLine, cCol, nLine, nCol;
    /* Symbol under construction */
    string       buffer;
    wstring      wbuffer;
    int          cC;
    short        cTok, Group;
    S_int        skipC;   /* characters to skip */
    T_next       next;
    
    virtual void setLanguage(string Language);
    virtual void addToken(string Token);
    virtual void addTokenFlags(byte Flag);
    virtual void addFinalState(short Token);
    virtual void addFirstEdge(long FirstEdge);
    virtual void addEdgeState(long State);
    virtual void addEdgeChar(wchar_t Character);
    virtual void addDyckToken(short Token);
    virtual void addDyckScanner(CStyxScanner& Scanner);
    virtual void addSwitchToken(short Token, short Group);
    virtual void addGroupScanner(CStyxScanner& Scanner);
    
    virtual bool nextToken_default();
    virtual bool nextToken_dyck();
  
    virtual bool switchGroup(short Group);
    virtual long currentLength();
    virtual void beginToken();
    virtual bool endToken();
    virtual void addCharacter(int c);
    virtual void skipCharacter();
    virtual void getCharacter();
  
    virtual bool loadTableLine
                 (
                   string& line, CStyxScanner*& cScanner, 
                   string& object, short& tokidx
                 );
  
  public:
    CStyxScanner();
    CStyxScanner(string Language);
    virtual ~CStyxScanner();
  
    virtual string& getLanguage();
    virtual short   getTokens();
    virtual string& getNthToken(short Nth);
  
    virtual bool    loadTableFile(string Path);
    virtual bool    loadTableString(string Table);
    virtual bool    scanStream(CStyxStream* Stream, S_int& SkipTokens);
    virtual bool    nextToken();
    virtual bool    eos();
    virtual bool    currentToken(string& Token, string& Value);
    virtual bool    currentToken(string& Token, wstring& Value);
    virtual long    getLine(); 
    virtual long    getCol(); 
    virtual string& getFile(); 
  };
  
}

#endif
