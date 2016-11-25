/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxScanner.C]      Styx Scanner Implementation (C++)                   */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2003 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include <stdio.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

#include "StyxScanner.h"
#include "StyxString.h"


namespace styx
{
#ifdef _WIN32
#define snprintf _snprintf
#endif

  static short i32HighValue(long v)
  {
    return (short)(((long)(v)) >> 16);
  }

  static short i32LowValue(long v)
  {
    return (short)(((long)(v)) & 0xFFFFL);
  }

  static long i32Value(short h, short l)
  {
    return   ((((long)(h)) << 16) & 0xFFFF0000L) 
           | (((long)(l)) & 0x0000FFFFL);
  }

  
  /* Scan stream ------------------------------------------------------------ */
  
  CStyxStream::CStyxStream(string Path)
  { 
    if( Path.length() > 0 )
    { char* p = strrchr((char*)Path.c_str(),'/');
      if( p == NULL )
        p = strrchr((char*)Path.c_str(),'\\');
      if( p != NULL )
        File = p + 1;
      else
        File = Path;
    }
    cEof = 0;
  }
  
  CStyxStream::~CStyxStream()
  {
  }
  
  void CStyxStream::error(string Text)
  {
    fprintf(stderr,"%s\n",Text.c_str());
  }
  
  bool CStyxStream::eof(int c)
  {
    return c <= cEof;
  }
  
  string& CStyxStream::getFile() 
  {
    return File;
  }

  void CStyxStream::setFile(string id)
  {
    File = id;
  }

  
  /* Scanner ---------------------------------------------------------------- */
    
  void CStyxScanner::setLanguage(string Language)
  {
    Name = Language;
  }
    
  void CStyxScanner::addToken(string Token)
  {
    TokId.push_back(Token);
  }
  
  bool CStyxScanner::addTokenFlags(byte Flag)
  {
    Flags.push_back(Flag);
    bool result = (Flag&SCN_FLG_IndentToken) == false &&
                  (Flag&SCN_FLG_CfgToken)    == false &&
                  (Flag&SCN_FLG_EofToken)    == false &&
                  (Flag&SCN_FLG_SwitchToken) == false;
    if( !result )
      error("unsupported token flags");
    return result;
  }
  
  void CStyxScanner::addFinalState(short Token)
  {
    StaFin.push_back(Token);
  }
  
  void CStyxScanner::addFirstEdge(long FirstEdge)
  {
    StaEdg.push_back(FirstEdge);
  }
  
  void CStyxScanner::addEdgeState(long State)
  {
    EdgeS.push_back(State);
  }
  
  void CStyxScanner::addEdgeChar(wchar_t Character)
  {
    EdgeC += Character;
  }
  
  void CStyxScanner::addDyckToken(short Token)
  {
    dyckidx.push_back(Token);
  }
  
  void CStyxScanner::addDyckScanner(const CStyxScanner& Scanner)
  {
    dyckpat.push_back(Scanner);
  }
  
  void CStyxScanner::addDyckScanner()
  {
    dyckpat.push_back(CStyxScanner());
  }
  
  void CStyxScanner::addSwitchToken(short Token, short Group)
  {
    Switch[Token] = Group;
  }
  
  void CStyxScanner::addGroupScanner(const CStyxScanner& Scanner)
  {
    GrpScn.push_back(Scanner);
  }
  
  void CStyxScanner::addGroupScanner()
  {
    GrpScn.push_back(CStyxScanner());
  }
  
  CStyxScanner* CStyxScanner::currentGroupScanner()
  {
    return GrpScn.size() > 0
           ? &GrpScn[GrpScn.size()-1] : this;
  }
  
  CStyxScanner* CStyxScanner::currentDyckScanner()
  { CStyxScanner* curgrp = currentGroupScanner();
    return curgrp->dyckpat.size() > 0
           ? &curgrp->dyckpat[curgrp->dyckpat.size()-1] : NULL;
  }
  
  bool CStyxScanner::switchGroup(short Group, bool asgflg)
  { 
    if( !asgflg )
    {
      if( Group == -1 )
      {
        if (cTok < 0 || !(Flags[cTok]&SCN_FLG_GroupStack) ||
            GroupStack.size() <= 0) 
        {
          error("group switch failed");
          return false;
        }
        Group = GroupStack[GroupStack.size()-1];
        GroupStack.pop_back();
      }
      else
      if( Flags[cTok]&SCN_FLG_GroupStack )
      {
        GroupStack.push_back(this->Group);
      }
    }
    if( this->Group != Group )
    { 
      this->Group = Group;
      StaEdg      = GrpScn[Group].StaEdg;
      StaFin      = GrpScn[Group].StaFin;
      EdgeC       = GrpScn[Group].EdgeC;
      EdgeS       = GrpScn[Group].EdgeS;
      Flags       = GrpScn[Group].Flags;
      dscanner.clear();
      for( size_t i=0; i < GrpScn[Group].dyckidx.size(); ++i )
      {
        dscanner[GrpScn[Group].dyckidx[i]] = &GrpScn[Group].dyckpat[i];
      }
    }
    return true;
  }
  
  bool CStyxScanner::initPatternSymbol(string p, bool seq, string& result)
  { size_t len = p.length();
    result = "";
    if( len > 0 && len % 3 != 0 )
    {
      error("invalid start pattern or quotient token ID");
      return false;
    }
    for( size_t i=0; i < len; i+=3 )
    { unsigned char buf[4]; int c1, c2;
      buf[0] = p[i];
      buf[1] = p[i+1];
      buf[2] = p[i+2];
      buf[3] = '\0';
      c1 = atoi((char*)buf);
      if( i == 0 )
      {
        if( seq )
        {
          if( ((char)c1) != '"' && ((char)c1) != '\'' )
          {
            error("invalid quotient token ID");
            return false;
          }
        }
        else
        {
          if( c1 != 0 )
          {
            error("invalid pattern token ID");
            return false;
          }
          continue;
        }
      }
      result += (char)c1;
      if( p[i+3] == '.' )
      {
        if( i+9 >= len )
        {
          error("invalid start pattern or quotient token ID");
          return false;
        }
        i += 6;
        buf[0] = p[i];
        buf[1] = p[i+1];
        buf[2] = p[i+2];
        buf[3] = '\0';
        c2 = atoi((char*)buf);
        while( ++c1 <= c2 )
        {
          result += (char)c1;
        }
      }
    }
    if( !seq && result.length() == 0 )
    {
      error("missing pattern characters");
      return false;
    }
    return true;
  }
  
  bool CStyxScanner::initPatternMap(string p, long idx, bool pat)
  { string patsym;
    if( pat )
    { size_t pos = p.find_first_of(SCN_SEP_TOK_ID_PATTERN);
      if( pos != string::npos )
      { string p1, p2;
        p1 = p.substr(0,pos);
        p2 = p.substr(pos+1);
        if( cPatMap.find(idx) == cPatMap.end() )
        {
          if( ! initPatternSymbol(p1,false,patsym) )
            return false;
          cPatMap[idx] = patsym;
        }
        if( cQPatMap.find(idx) == cQPatMap.end() )
        {
          if( ! initPatternSymbol(p2,true,patsym) )
            return false;
          cQPatMap[idx] = patsym;
        }
      }
      else
      {
        if( !strncmp(p.c_str(),"000",3) )
        {
          if( cPatMap.find(idx) == cPatMap.end() )
          {
            if( ! initPatternSymbol(p,false,patsym) )
              return false;
            cPatMap[idx] = patsym;
          }
        }
        else
        {
          if( cQPatMap.find(idx) == cQPatMap.end() )
          {
            if( ! initPatternSymbol(p,true,patsym) )
              return false;
            cQPatMap[idx] = patsym;
          }
        }
      }
    }
    else
    { 
      if( cQPatMap.find(idx) == cQPatMap.end() )
      {
        if( ! initPatternSymbol(p,true,patsym) )
          return false;
        cQPatMap[idx] = patsym;
      }
    }
    return true;
  }
  
  bool CStyxScanner::initPattern()
  /* collect patterns of quotient and pattern tokens */
  { 
    if( GrpScn.size() > 0 )
    {
      for( size_t i=0; i < GrpScn.size(); ++i )
      {
        for( size_t j=0; j < GrpScn[i].TokId.size(); j++)
        { 
          string tokid = GrpScn[i].TokId[j];
          size_t pos   = tokid.find_first_of(SCN_SEP_TOK_ID_PATTERN);
          if( pos != string::npos )
          { 
            bool ok = initPatternMap
                      (
                        tokid.substr(pos+1), i32Value((short)i,(short)j),
                        (GrpScn[i].Flags[j]&SCN_FLG_PatternToken)!=0 
                      );
            if( !ok ) return false;
          }
        }
      }
    }
    else
    {
      for (size_t j=0; j < TokId.size(); j++)
      { string tokid = TokId[j];
        size_t pos   = tokid.find_first_of(SCN_SEP_TOK_ID_PATTERN);
        if( pos != string::npos )
        { bool ok = initPatternMap
                    (
                      tokid.substr(pos+1), i32Value(-1,(short)j),
                      (Flags[j]&SCN_FLG_PatternToken)!=0
                    );
          if( !ok ) return false;
        }
      }
    }
    return true;
  }
  
  long CStyxScanner::currentLength()
  {
    if( cStream->unicode() )
      return (long)wbuffer.length();
    else
      return (long)buffer.length();
  }
  
  void CStyxScanner::beginToken()
  {
    cCol = nCol; cLine = nLine;
    wbuffer.erase();
    buffer.erase();
  }
  
  bool CStyxScanner::endToken()
  {
    if( cStream->unicode() )
    {
      if (cTok >= 0 && (Flags[cTok]&SCN_FLG_IgnoreCase)) 
      {
        for( size_t i=0; i < wbuffer.length(); ++i )
        {
          if( iswupper(wbuffer[i]) ) wbuffer[i] = towlower(wbuffer[i]);
        }
      }
    }
    else
    {
  //printf("TOKEN-BUFFER=%s\n",buffer.c_str());
      if (cTok >= 0 && (Flags[cTok]&SCN_FLG_IgnoreCase)) 
      {
        for( size_t i=0; i < buffer.length(); ++i )
        {
          if( isupper(buffer[i]) ) buffer[i] = tolower(buffer[i]);
        }
      }
    }
    if( cTok == -1 ) /* EOF */
    {
      if( pstreams.size() > 0 )
      {
        if( cStream ) delete cStream; 
        cStream = pstreams[pstreams.size()-1].Stream;
        nLine   = pstreams[pstreams.size()-1].Line;
        nCol    = pstreams[pstreams.size()-1].Column;
        bbuffer = pstreams[pstreams.size()-1].Backbuffer;
        cC      = pstreams[pstreams.size()-1].curChar;
        pstreams.pop_back();
        return nextToken();
      }
    }
    else
    if( cTok > 0 )
    {
      if( cQPatMap.size() > 0 && !endQuotient() ) 
        return false;
      if( cTok > 0 && (Flags[cTok]&SCN_FLG_PatternToken) && !endPattern() )
        return false;
      if( cTok > 0 && preprocess )
      { CStyxStream* PStream = cStream;
        string Token;
        if( cStream->unicode() )
        { wstring Value;
          if( !currentToken(Token,Value) ) 
            return false;
//cout << "preprocess " << Token.c_str() << "\n";
          if( !preprocessToken(PStream,Token,Value) ) 
          {
            error("preprocessing failed");
            return false;
          }
          if( PStream == cStream ) wbuffer = Value;
//cout << "preprocess2 " << Token.c_str() << "\n";
        }
        else
        { string Value;
          if( !currentToken(Token,Value) ) 
            return false;
//cout << "preprocess " << Token.c_str() << "\n";
          if( !preprocessToken(PStream,Token,Value) ) 
          {
            error("preprocessing failed");
            return false;
          }
          if( PStream == cStream ) buffer = Value;
//cout << "preprocess2 " << Token.c_str() << "\n";
        }
        if( PStream != cStream )
        {
          if( PStream != 0 )
          { StyxStreamPos curStreamPos;
            curStreamPos.Stream     = cStream;
            curStreamPos.Line       = nLine;
            curStreamPos.Column     = nCol;
            curStreamPos.Backbuffer = bbuffer;
            curStreamPos.curChar    = cC;
            pstreams.push_back(curStreamPos);
            cStream = PStream;
            cC = cStream->sgetc();
            nLine = nCol = 1;
            bbuffer.clear();
//cout << "preprocess3 " << PStream->getFile().c_str() << "\n";
          }
          return nextToken();
        }
//cout << "preprocess4 " << "\n";
      }
    }
    return true;
  }
  
  bool CStyxScanner::endPattern()
  { long idx = -1;
    if( GrpScn.size() > 0 )
      idx = i32Value(this->Group,cTok);
    else
      idx = i32Value(-1,cTok);
    if( cPatSym.length() == 0 && cPatMap.find(idx) != cPatMap.end() )
    { /* start pattern token */
      cPatTok = cTok;
      if( GrpScn.size() > 0 )
        cPatGrp = Group;
      /* get pattern set */
      string pat = cPatMap[idx];
      /* get pattern */
      if( !cStream->unicode() )
      { size_t i;
        for( i=0; i < buffer.length(); ++i )
          if( strchr(pat.c_str(),buffer[i]) != NULL )
            break;
        for( ; i < buffer.length(); ++i )
          if( strchr(pat.c_str(),buffer[i]) != NULL )
            cPatSym += buffer[i];
          else break;
      }
      else
      { char c; size_t i;
        for( i=0; i < wbuffer.length(); ++i )
        { 
          c = (char)wbuffer[i];
          if( ((wchar_t)c) == wbuffer[i] &&
              strchr(pat.c_str(),c) != NULL )
            break;
        }
        for( ; i < wbuffer.length(); ++i )
        {
          c = (char)wbuffer[i];
          if( ((wchar_t)c) == wbuffer[i] &&
              strchr(pat.c_str(),c) != NULL )
            cPatSym += c;
          else break;
        }
      }
      if( cPatSym.length() == 0 )
        cTok = 0; /* error */
    }
    else
    if( cPatSym.length() > 0 && cPatMap.find(idx) == cPatMap.end() )
    { /* end pattern token, try to match pattern */
      if( !cStream->unicode() )
      {
        if( buffer.find(cPatSym) != string::npos )
        { /* pattern found */
          cTok = cPatTok; cPatSym = "";
          if( GrpScn.size() > 0 && !switchGroup(cPatGrp,true) )
            return false;
        }
      }
      else /* multibyte mode */
      { size_t i, j, k;
        for( i=0; i < wbuffer.length(); ++i )
        { char c = (char)wbuffer[i];
          if( ((wchar_t)c) == wbuffer[i] && c == cPatSym[0] )
          { bool flg = true;
            for( k=1, j=i+1; 
                 k < cPatSym.length() && j < wbuffer.length(); ++j, ++k )
            {
              c = (char)wbuffer[j];
              if( ((wchar_t)c) != wbuffer[j] || c != cPatSym[k] ) 
              {
                if( flg && c != cPatSym[0] ) i=j;
                break;
              }
              else
              if( flg && c != cPatSym[0] ) i=j;
              else flg = false;
            }
            if( cPatSym.length() == k ) /* pattern found */
            {
              cTok = cPatTok; cPatSym = "";
              if( GrpScn.size() > 0 && !switchGroup(cPatGrp,true) )
                return false;
              break;
            }
          }
        }
      }
    }
    else cTok = 0; /* error */
    return true;
  }
  
  bool CStyxScanner::endQuotient()
  { long idx = -1;
    if( GrpScn.size() > 0 )
      idx = i32Value(this->Group,cTok);
    else
      idx = i32Value(-1,cTok);
    if( cQPatMap.find(idx) != cQPatMap.end() )
    {
      /* get quotient pattern */
      string pat = cQPatMap[idx];
      long   len = ((long)pat.length())-1;
      /* push back quotient */
      if( len > 0 )
      {
        if( !cStream->unicode() )
        { 
          if( pat[0] == '"' ) /* sequence */
          {
            if( ((long)buffer.length()) <= len || 
                //strncmp(buffer.c_str()+buffer.length()-len,pat.c_str()+1,len) )
                buffer.find(pat.c_str()+1,buffer.length()-len) == string::npos )
              cTok = 0; /* error; = --> endless recursion */
            else
              backbufQuotient(((long)buffer.length())-len);
          }
          else
          { long i;
            for( i=((long)buffer.length())-1; i >= 0; --i )
            {
              if( strchr(pat.c_str()+1,buffer[i]) == NULL )
                break;
            }
            if( i < 0 ) cTok = 0; /* error: endless recursion */
            else
            if( i < ((long)buffer.length())-1 )
              backbufQuotient(i+1);
          }
        }
        else
        {
          if( pat[0] == '"' ) /* sequence */
          {
            if( ((long)wbuffer.length()) <= len )
              cTok = 0; /* error; = --> endless recursion */
            else
            { long i, j;
              for( i=((long)wbuffer.length())-1, j=len-1; 
                   j >= 1 && i >= 0; --i, --j )
              {
                if( wbuffer[i] != ((wchar_t)pat[j]) )
                  break;
              }
              if( j >= 1 ) cTok = 0; /* error */
              else
                backbufQuotient(((long)wbuffer.length())-len);
            }
          }
          else
          { long i;
            for( i=((long)wbuffer.length())-1; i >= 0; --i )
            { char c = (char)wbuffer[i];
              if( ((wchar_t)c) != wbuffer[i] || strchr(pat.c_str()+1,c) == NULL )
                break;
            }
            if( i < 0 ) cTok = 0; /* error: endless recursion */
            else
            if( i < ((long)buffer.length())-1 )
              backbufQuotient(i+1);
          }
        }
      }
    }
    return true;
  }
  
  void CStyxScanner::getCharacter()
  {
    addCharacter(cC);
    if (cC == (cStream->unicode() ? (int)L'\n' : (int)'\n'))
    { nLine += 1; nCol = 1; }
    else
    { nCol += 1; }
    if( bbuffer.size() > 0 )
    {
      cC = (int)bbuffer[bbuffer.size()-1];
      bbuffer.pop_back();
    }
    else
    {
      cC = cStream->sgetc();
      if( !skipC.empty() ) skipCharacter();
    }
  }
  
  void CStyxScanner::skipCharacter()
  {
    while( skipC.find(cC) != skipC.end() )
    {
      if (cC == (cStream->unicode() ? (int)L'\n' : (int)'\n'))
      { nLine += 1; nCol = 1; }
      else
      { nCol += 1; }
      cC = cStream->sgetc();
    }
  }
  
  void CStyxScanner::addCharacter(int c)
  {
    if( cStream->unicode() )
      wbuffer += (wchar_t)c;
    else
      buffer += (char)c;
  }
  
  void CStyxScanner::backbufLookahead
              (
                long cBackLen, long nBackLin, long nBackCol
              )
  /* buffer character look-ahead */
  { long i;
    bbuffer.push_back(cC);
    if( !cStream->unicode() )
    {
      for( i=((long)buffer.length())-1; i > cBackLen; --i )
        bbuffer.push_back(buffer[i]);
      cC = (int)buffer[i];
      buffer.erase(i);
    }
    else
    {
      for( i=((long)wbuffer.length())-1; i > cBackLen; --i )
        bbuffer.push_back(wbuffer[i]);
      cC = (int)wbuffer[i];
      wbuffer.erase(i);
    }
    nLine = nBackLin; nCol = nBackCol;
  }
  
  void CStyxScanner::backbufQuotient(long cBackLen)
  /* buffer token quotient */
  { long i;
    bbuffer.push_back(cC);
    if( !cStream->unicode() )
    {
      for( i=((long)buffer.length())-1; i > cBackLen; --i )
        bbuffer.push_back(buffer[i]);
      cC = (int)buffer[i];
      buffer.erase(i);
    }
    else
    {
      for( i=((long)wbuffer.length())-1; i > cBackLen; --i )
        bbuffer.push_back(wbuffer[i]);
      cC = (int)wbuffer[i];
      wbuffer.erase(i);
    }
    for( i=0, nLine=cLine, nCol=cCol; i < cBackLen; ++i )
    {
      if( !cStream->unicode() )
      {
        if( buffer[i] == '\n' )
        { nLine += 1; nCol = 1; }
        else
        { nCol += 1; }
      }
      else
      {
        if( wbuffer[i] == L'\n' )
        { nLine += 1; nCol = 1; }
        else
        { nCol += 1; }
      }
    }
  }
  
  
  bool CStyxScanner::nextToken_dyck()
  { int state = 0, cnt = 1; long cLen = currentLength(); 
    short dTok = cTok;
    CStyxScanner& dyck = *dscanner[cTok];
  LOOP:
    cLen    = currentLength();
    cTok = -1; /* -1 == ETX */
    if ( !cStream->eof(cC) )
    { register wchar_t* i; 
      wchar_t* s = (wchar_t*)dyck.EdgeC.data();
      state = 0;
      for (i = &s[dyck.StaEdg[state]]; *i++ > cC; );
      state = dyck.EdgeS[i-s-1]-1;
      while (state >= 0)
      {
        cTok = dyck.StaFin[state]; getCharacter();
        if ( cStream->eof(cC) )
          break;
        for (i = &s[dyck.StaEdg[state]]; *i++ > cC; );
        state = dyck.EdgeS[i-s-1]-1;
      }
      if((currentLength() - cLen) == 0 && !cStream->eof(cC)) 
      { getCharacter(); cTok = 0; }
    }
    if( cTok > 0 || ( cTok == 0 && dyck.TokId.size() == 3 ) )
    {
      if( cTok == SCN_DYCKTOKEN_PREFIX ) ++cnt;
      else
      if( cTok == SCN_DYCKTOKEN_SUFFIX ) --cnt;
      if( cnt == 0 ) cTok = dTok;
      else goto LOOP;
    }
    return true;
  }
  
  bool CStyxScanner::nextToken_default()
  { int state = 0;
    beginToken(); 
    if( GrpScn.size() > 0 && cTok >= 0 && 
        cTok == cPatTok && Group == cPatGrp && cPatSym.length() == 0 )
    { /* end pattern token switch already done */
      cPatGrp = -1; cPatTok = -1;
    }
    else
    if( GrpScn.size() > 0 && cTok >= 0 && 
        (GrpScn[Group].Switch[cTok] >= 0 || (Flags[cTok]&SCN_FLG_GroupStack)) &&
        !switchGroup(GrpScn[Group].Switch[cTok],false) )
      return false;
  LOOP:
    /* '\0' (string) and -1 (file,buffer) is treated as EOF. */
    cTok = -1; /* -1 == ETX */
    if ( !cStream->eof(cC) )
    { register wchar_t* i; 
      wchar_t* s = (wchar_t*)EdgeC.data();
      // handle character look-ahead ...
      long  cBackLen = -1, nBackLin = -1, nBackCol = -1;
      short cBackTok = -1;
      // ... handle character look-ahead
      state = 0;
      for (i = &s[StaEdg[state]]; *i++ > (wchar_t)cC; );
      state = EdgeS[i-s-1]-1;
      while (state >= 0)
      {
        /* n character look-ahead:
           jeweils den größten Endzustand merken, zusammen mit Tokenlänge.
           nach der schleife, 
           1) wert oder fehler 
           2) fehler mit vorangegangenem Wert --> 
              zurücksetzen auf ende wertposition via backbuffer und fortsetzen
        */
        cTok = StaFin[state]; getCharacter();
        // handle character look-ahead ...
        if( lookahead && cTok > 0 )
        {
          cBackLen = currentLength(); 
          nBackLin = nLine; nBackCol = nCol;
          cBackTok = cTok;
        }
        // ... handle character look-ahead
        if ( cStream->eof(cC) )
        {
          break;
        }
        for (i = &s[StaEdg[state]]; *i++ > (wchar_t)cC; );
        state = EdgeS[i-s-1]-1;
      }
      // handle character look-ahead ...
      if( lookahead && cTok == 0 && cBackTok > 0 )
      {
        cTok = cBackTok; backbufLookahead(cBackLen,nBackLin,nBackCol);
      }
      // ... handle character look-ahead
      if( currentLength() == 0 && !cStream->eof(cC) )
      { getCharacter(); cTok = 0; }
      // process dyck token ...
      if( dscanner.find(cTok) != dscanner.end() && 
          !nextToken_dyck() )
        return false;
      // ... process dyck token
      if( (Flags[cTok]&SCN_FLG_IgnoreToken) )
      { beginToken(); 
        if( GrpScn.size() > 0 && cTok >= 0 && 
            (GrpScn[Group].Switch[cTok] >= 0 || 
              (Flags[cTok]&SCN_FLG_GroupStack)) &&
            !switchGroup(GrpScn[Group].Switch[cTok],false) )
          return false;
        goto LOOP; 
      }
    }
    return endToken();
  }
  
  
  CStyxScanner::CStyxScanner(bool lahead, bool process)
  {
    lookahead  = lahead;
    preprocess = process;
    reset();
  }
  
  CStyxScanner::~CStyxScanner()
  {
    deleteStreams();
  }
  
  void CStyxScanner::deleteStreams()
  {
    if( pstreams.size() > 0 )
    {
      if( cStream ) delete cStream;
      for( size_t i=1; i < pstreams.size(); ++i )
      {
        if( pstreams[i].Stream ) delete pstreams[i].Stream;
      } 
      pstreams.clear();
    }
    cStream = 0;
  }
  
  void CStyxScanner::reset()
  {
    initok  = false;
    Name    = "";
    deleteStreams();
    cC      = cTok = Group = -1;
    cLine   = cCol = nLine = nCol = 1;
    next    = &CStyxScanner::nextToken_default;
    cPatTok = cPatGrp = -1;
    StaEdg.clear();
    StaFin.clear();
    EdgeC.clear();
    EdgeS.clear();
    TokId.clear();
    Flags.clear();
    GrpScn.clear();
    Switch.clear();
    GroupStack.clear();
    dyckidx.clear();
    dyckpat.clear();
    dscanner.clear();
    cPatMap.clear();
    cQPatMap.clear();
    bbuffer.clear();
    wbuffer.erase();
    buffer.erase();
  }
  
  bool CStyxScanner::LookaheadEnabled()
  {
    return lookahead;
  }
  
  bool CStyxScanner::PreprocessEnabled()
  {
    return preprocess;
  }
  
  string CStyxScanner::getLanguage()
  {
    if( !initok ) return "";
    return Name;
  }
  
  short CStyxScanner::getGroups()
  {
    if( !initok ) return -1;
    return (short)GrpScn.size();
  }
  
  short CStyxScanner::getTokens(short GrpIdx)
  {
    if( !initok ) return -1;
    if( GrpIdx == -1 )
      return (short)TokId.size();
    else
      return GrpIdx >= 0 && ((size_t)GrpIdx) < GrpScn.size()
             ? (short)GrpScn[GrpIdx].TokId.size() : -1;
  }
  
  string CStyxScanner::getGroupID(short GrpIdx)
  {
    if( !initok ) return "";
    return GrpIdx >= 0 && ((size_t)GrpIdx) < GrpScn.size()
           ? GrpScn[GrpIdx].Name : "";
  }
  
  string CStyxScanner::getTokenID(short TokIdx, short GrpIdx)
  {
    if( !initok ) return "";
    if( GrpIdx == -1 )
      return TokIdx >= 0 && ((size_t)TokIdx) < TokId.size()
             ? TokId[TokIdx] : "";
    else
      return GrpIdx >= 0 && ((size_t)GrpIdx) < GrpScn.size() &&
             TokIdx >= 0 && ((size_t)TokIdx) < GrpScn[GrpIdx].TokId.size()
             ? GrpScn[GrpIdx].TokId[TokIdx] : "";
  }
  
  bool CStyxScanner::loadTableLine
       (
         string& line, CStyxScanner*& cScanner, 
         string& object, short& tokidx
       )
  {
    if( line.length() > 0 && line[0] != '#' )
    { char* n = strstr((char*)line.c_str(),"Name=");
      if( n != NULL )
      {
        cScanner->setLanguage(n+strlen("Name="));
      }
      else
      if( line == "Group" )
      {
        //GrpScn.push_back(CStyxScanner());
        //cScanner = &GrpScn[GrpScn.size()-1];
        addGroupScanner();
        cScanner = currentGroupScanner();
      }
      else
      if( line == "Dyck" )
      {
        //dyckpat.push_back(CStyxScanner());
        //cScanner = &dyckpat[dyckpat.size()-1];
        cScanner->addDyckScanner();
        cScanner = currentDyckScanner();
      }
      else
      if( line == "Language" )
      {
        cScanner = this;
      }
      else
      if( line[0] != '-' && !isdigit(line[0]) && !isspace(line[0]) )
      {
        object = line;
        tokidx = 0;
      }
      else
      if( isspace(line[0]) )
      {
        cScanner->addToken(line.c_str()+1);
      }
      else
      if( line[0] == '-' || isdigit(line[0]) )
      { long int v = atol(line.c_str());
        if( object == "StaEdg" )
        {
          cScanner->addFirstEdge((long)v);
        }
        else
        if( object == "StaFin" )
        {
          cScanner->addFinalState((short)v);
        }
        else
        if( object == "EdgeC" )
        {
          cScanner->addEdgeChar((wchar_t)v);
        }
        else
        if( object == "EdgeS" )
        {
          cScanner->addEdgeState((long)v);
        }
        else
        if( object == "Flags" )
        {
          if( !cScanner->addTokenFlags((byte)v) )
          {
            return false;
          }
        }
        else
        if( object == "Switch" )
        {
          cScanner->addSwitchToken(tokidx,(short)v);
          tokidx++;
        }
        else
        if( object == "DyckToken" )
        {
          cScanner = currentGroupScanner();
          cScanner->addDyckToken((short)v);
        }
      }
    }
    line = "";
    return true;
  }
  
  bool CStyxScanner::checkLoad()
  {
    bool result = GrpScn.size() > 0 ||
                  StaFin.size() > 0 && StaEdg.size() > 0 && 
                  EdgeS.size() > 0 && EdgeC.length() > 0 &&
                  TokId.size() > 0 && TokId.size() == Flags.size();
    if( !result ) error("invalid scanner table format");
    return result;
  }
  
  bool CStyxScanner::loadTableFile(string Path)
  { 
    reset();
    ifstream is(Path.c_str()); char c;
    if( !is ) 
    {
      error(string("couldn't open '") + Path + string("'"));
      return false;
    }
    string line, object; 
    CStyxScanner* cScanner = this;
    short tokidx = 0;
    while( is.get(c) )
    {
      if( c == '\n' )
      {
        if( !loadTableLine(line,cScanner,object,tokidx) )
          return false;
      }
      else line += c;
    }
    initok = checkLoad() && initPattern();
    return initok;
  }
  
  bool CStyxScanner::loadTableString(string Table)
  { 
    reset();
    string line, object; char c;
    CStyxScanner* cScanner = this;
    short tokidx = 0;
    for( size_t i=0; i < Table.length(); ++i )
    {
      c = Table[i];
      if( c == '\n' )
      {
        if( !loadTableLine(line,cScanner,object,tokidx) )
          return false;
      }
      else line += c;
    }
    initok = checkLoad() && initPattern();
    return initok;
  }
  
  bool CStyxScanner::scanStream(CStyxStream* Stream, const S_int& SkipCharacters)
  { 
    if( !initok ) return false;
    cStream = Stream;
    if( cStream == 0 || !cStream->valid() )
    {
      error("invalid stream");
      return false;
    }
    skipC   = SkipCharacters;
    next    = &CStyxScanner::nextToken_default;
    if( GrpScn.size() > 0 )
    {
      Group   = 0;
      StaEdg  = GrpScn[0].StaEdg;
      StaFin  = GrpScn[0].StaFin;
      EdgeC   = GrpScn[0].EdgeC;
      EdgeS   = GrpScn[0].EdgeS;
      Flags   = GrpScn[0].Flags;
      for( size_t i=0; i < GrpScn[0].dyckidx.size(); ++i )
      {
        dscanner[GrpScn[Group].dyckidx[i]] = &GrpScn[Group].dyckpat[i];
      }
    }
    else 
    {
      Group   = -1;
      for( size_t i=0; i < dyckidx.size(); ++i )
      {
        dscanner[dyckidx[i]] = &dyckpat[i];
      }
    }
    cC      = cStream->sgetc();
    nLine   = 1;
    nCol    = 1;
    cTok    = 0;
    cPatTok = cPatGrp = -1;
    cPatSym = "";
    bbuffer.clear();
    return initialized();
  }
  
  bool CStyxScanner::eos()
  {
    return (cTok == -1); 
  }
  
  bool CStyxScanner::unicode() 
  {
    return cStream ? cStream->unicode() : false;
  }
  
  bool CStyxScanner::nextToken()
  {
    return initok && cStream && (this->*next)() 
           ? true : ( deleteStreams(), false );
  }
  
  bool CStyxScanner::currentToken(string& Token, string& Value)
  {
    if( initok && cStream && !cStream->unicode() )
    {
      if (cTok == -1) 
      {
        Token = "[EOF]";
        return true;
      }
      else
      if( GrpScn.size() > 0 )
      {
        Token = GrpScn[Group].TokId[cTok];
      }
      else
      {
        Token = TokId[cTok];
      }
      Value = buffer;
      return true;
    }
    return false;
  }
  
  bool CStyxScanner::currentToken(string& Token, wstring& Value)
  {
    if( initok && cStream && cStream->unicode() )
    {
      if (cTok == -1)
      {
        Token = "[EOF]";
        return true;
      }
      else
      if( GrpScn.size() > 0 )
      {
        Token = GrpScn[Group].TokId[cTok];
      }
      else
      {
        Token = TokId[cTok];
      }
      Value = wbuffer;
      return true;
    }
    return false;
  }
  
  bool CStyxScanner::preprocessToken
       (
         CStyxStream*& PStream, const string& Token, string& Value
       )
  {
    return true;
  }
  
  bool CStyxScanner::preprocessToken
       (
         CStyxStream*& PStream, const string& Token, wstring& Value
       )
  {
    return true;
  }
  
  bool CStyxScanner::ignoreCase()
  {
    if( !initok ) return false;
    return (cTok >= 0 && (Flags[cTok]&SCN_FLG_IgnoreCase)); 
  }
  
  long CStyxScanner::getLine()
  {
    return cLine;
  }
  
  long CStyxScanner::getCol() 
  {
    return cCol;
  }
  
  string CStyxScanner::getFile() 
  {
    return cStream ? cStream->getFile() : "";
  }
  
  const CStyxStream* CStyxScanner::getStream() 
  {
    return cStream;
  }
  
  string CStyxScanner::externalTokenID(const string& Token) 
  { size_t pos = Token.find_first_of(SCN_SEP_TOK_ID_PATTERN);
    if( pos == string::npos )
      return Token;
    else
      return Token.substr(0,pos); 
  }
  
  void CStyxScanner::error(string Text)
  {
    fprintf(stderr,"%s\n",Text.c_str());
  }
  
  bool CStyxScanner::initialized()
  {
    return initok && cStream && cStream->valid();
  }
  

  /* Scanner with standard Styx compliant preprocessing facility ------------ */
  
  /** default macro token identifiers, macro keywords 
      as well as the default include path and characterset
  */
  static const char* MacParDefaults[] =
  {
    "Ide",        ///< token identifier   
                  ///< (us-ascii or ignore case !!!)

    "MacDfn",     ///< token define macro 
    "MacSep",     ///< token parameter separator (in macro calls)
    "MacInc",     ///< token include
    "MacCond",    ///< token condition
    "MacDel",     ///< token undefine macro

    "#macro",     ///< initial keyword define macro
    "#end",       ///< final keyword define macro, condition
    "#ifdef",     ///< initial keyword ifdef condition
    "#ifndef",    ///< initial keyword ifndef condition
    "#else",      ///< initial keyword else condition
    "#include",   ///< initial keyword include
    "#undefine",  ///< initial keyword undefine macro

    "PATH",       ///< include path
    ""            ///< include characterset
  };
  

  CStyxPScanner::CStyxPScanner(bool lahead, bool igncase)
  : CStyxScanner(lahead,true)
  {
    MacIgnCase = igncase;
    CurSep     = 0; // space separator
    for( int i=0; i < IDX_PAR_END; ++i )
    {
      Parameters[i] = MacParDefaults[i];
    }
  }
  
  CStyxPScanner::~CStyxPScanner()
  {
  }

  void CStyxPScanner::setStreamID(CStyxStream* PStream)
  {
    if( PStream )
    { string id = getFile();
      id += "(";
      char buf[80+1];
      snprintf(buf,80,"%ld",getLine());
      id += buf;
      id += ",";
      snprintf(buf,80,"%ld",getCol());
      id += buf;
      id += ")#";
      id += PStream->getFile();
      PStream->setFile(id);
    }
  }

  CStyxStream* CStyxPScanner::createMacroStream
               (
                 const string& id, const string& Text
               )
  { CStyxStream* PStream = 0;
    if( unicode() )
    { wstring wtext = multibyte2unicode(Text);
      PStream = new TStyxStringStreamU(wtext,id);
    }
    else
      PStream = new TStyxStringStreamS(Text,id);
    setStreamID(PStream);
    return PStream;
  }

  CStyxStream* CStyxPScanner::createFileStream(const string& Path)
  { CStyxStream* PStream = 0;
    if( unicode() )
    {
      if( Parameters[IDX_INC_CSET] == "utf8" )
      { string content; wstring wcontent; 
        ifstream is(Path.c_str()); char c;
        if( !is )
        {
          error(string("couldn't open '") + Path + string("'"));
          return 0;
        }
        content.reserve(1000);
        while( is.get(c) ) content += c;
        wcontent = multibyte2unicode(content);
        PStream = new TStyxStringStreamU(wcontent,Path);
      }
      else
        PStream = new TStyxFileStreamU(Path);
    }
    else
      PStream = new TStyxFileStreamS(Path);
    setStreamID(PStream);
    return PStream;
  }

  string CStyxPScanner::makePath
         (
           const string& dir, const string& file, string sep
         )
  {
    if( dir.length() > 0 )
    {
      if( dir[dir.length()-1] == '/' ||
          dir[dir.length()-1] == '\\' )
      {
//cout << (dir+file).c_str() << "\n";
        return dir + file;
      }
      else
      if( sep.length() == 1 )
      {
//cout << (dir + (( sep[0] == ':' ) ? "/" : "\\") + file).c_str() << "\n";
        return dir + (( sep[0] == ':' ) ? "/" : "\\") + file;
      }
      else
      if( dir.find('\\') == string::npos )
      {
//cout << (dir+"/"+file).c_str() << "\n";
        return dir + "/" + file;
      }
      else
      {
//cout << (dir+"\\"+file).c_str() << "\n";
        return dir + "\\" + file;
      }
    }
    return file;
  }

  CStyxStream* CStyxPScanner::evalInclude(const string& Value)
  { string& k = Parameters[IDX_KEY_INC];
    size_t pos = Value.find(k);
    if( pos == 0 )
    {
      pos += k.length();
      while( pos < Value.length() && isspace(Value[pos]) )
        ++pos;
      if( pos >= Value.length() )
      {
        error("missing include file");
        return 0;
      }
      string  f = Value.substr(pos);
      string& p = Parameters[IDX_INC_PATH];
      struct stat buf;
      if( stat(f.c_str(),&buf) == 0 )
        return createFileStream(f);
      else
      if( p.length() > 0 )
      { char* e = getenv(p.c_str());
        if( e != (char*)NULL ) p = e;
        string s = ";:", d, fp;
        pos = p.find_first_of(s);
        if( pos != string::npos )
        {
          if( p[pos] == ';' ) s = ";";
          else
          if( pos < p.length()-1 && p[pos+1] == '\\' )
            s = ";";
          else s = ":";
        }
        while( pos != string::npos )
        { 
          d = p.substr(0,pos);
          if( d.length() > 0 )
          {
            fp = makePath(d,f,s);
            if( fp.length() > 0 && stat(fp.c_str(),&buf) == 0 )
              return createFileStream(fp);
          }
          p = p.substr(pos+1);
          pos = p.find(s);
        }
        if( p.length() > 0 )
        {
          fp = makePath(p,f,s);
          if( fp.length() > 0 && stat(fp.c_str(),&buf) == 0 )
            return createFileStream(fp);
        }
      }
      error("'" + f + "' not found");
    }
    else error("unknown include keyword");
    return 0;
  }
  
  bool CStyxPScanner::evalCondition(const string& Value)
  { string& t = Parameters[IDX_KEY_IFDEF];
    size_t pos = Value.find(t);
    string id; id.reserve(80);
    if( pos == 0 )
    {
      pos += t.length();
      while( pos < Value.length() && isspace(Value[pos]) )
        ++pos;
      while( pos < Value.length() && !isspace(Value[pos]) )
      {
        id += MacIgnCase ? tolower(Value[pos]) : Value[pos];
        ++pos;
      }
      return MacDefines.find(id) != MacDefines.end();
    }
    string& f = Parameters[IDX_KEY_IFNDEF];
    pos = Value.find(f);
    if( pos == 0 )
    {
      pos += f.length();
      while( pos < Value.length() && isspace(Value[pos]) )
        ++pos;
      while( pos < Value.length() && !isspace(Value[pos]) )
      {
        id += MacIgnCase ? tolower(Value[pos]) : Value[pos];
        ++pos;
      }
      return MacDefines.find(id) == MacDefines.end();
    }
    error("unknown condition keyword");
    return false;
  }

  bool CStyxPScanner::preprocessCondition
       (
         CStyxStream*& PStream, const string& Token, const string& Value
       )
  {
    if( Parameters[IDX_KEY_END] == Value )
    {
      if( CondStack.size() == 0 )
      {
        error("unexpected end condition");
        return false;
      }
      CondStack.pop_back();
    }
    else
    if( Parameters[IDX_KEY_ELSE] == Value )
    {
      if( CondStack.size() == 0 )
      {
        error("unexpected else condition");
        return false;
      }
      if( CondStack[CondStack.size()-1] )
        CondStack[CondStack.size()-1] = false;
      else
      if( CondStack.size() == 1 ||
          CondStack[CondStack.size()-2] )
        CondStack[CondStack.size()-1] = true;
    }
    else
    if( CondStack.size() == 0 || CondStack[CondStack.size()-1] )
    {
      // eval condition
      CondStack.push_back(evalCondition(Value));
    }
    else 
    {
      CondStack.push_back(false);
    }
    PStream = 0;
    return true;
  }

  bool CStyxPScanner::evalUndefine(const string& Value)
  { string& u = Parameters[IDX_KEY_UNDEF];
    size_t pos = Value.find(u);
    if( pos == 0 )
    { string id; id.reserve(80);
      pos += u.length();
      while( pos < Value.length() && isspace(Value[pos]) )
        ++pos;
      while( pos < Value.length() && !isspace(Value[pos]) )
      {
        id += MacIgnCase ? tolower(Value[pos]) : Value[pos];
        ++pos;
      }
      MacDefines.erase(id);
      return true;
    }
    error("unknown undefine keyword");
    return false;
  }

  bool CStyxPScanner::evalDefine(const string& Value)
  { string& d = Parameters[IDX_KEY_START];
    size_t pos = Value.find(d);
    if( pos == 0 )
    { string id; V_string pars;
      id.reserve(80);
      pos += d.length();
      while( pos < Value.length() && isspace(Value[pos]) )
        ++pos;
      while( pos < Value.length() && !isspace(Value[pos]) &&
             Value[pos] != '(' && Value[pos] != '=' )
      {
        id += MacIgnCase ? tolower(Value[pos]) : Value[pos];
        ++pos;
      }
      while( pos < Value.length() && isspace(Value[pos]) )
        ++pos;
      if( pos < Value.length() )
      { string v = Value.substr(pos+1);
        if( Value[pos] == '(' )
        { 
          pos = v.find_first_of(",)");
          while( pos != string::npos )
          { string p; p.reserve(80);
            for( size_t i=0; i < pos; ++i )
              if( !isspace(v[i]) ) p += v[i];
            if( p.length() == 0 )
            {
              error("missing formal macro parameter");
              return false;
            }
            pars.push_back(p);
            if( v[pos] == ')' ) break;
            v   = v.substr(pos+1);
            pos = v.find_first_of(",)");
          }
          if( pos >= v.length() || v[pos] != ')' )
          {
            error("unexpected macro parameter syntax");
            return false;
          }
          pos = v.find("=",pos+1);
          if( pos != string::npos )
            v = v.substr(pos+1);
          else v = "";
        }
        if( v.length() > 0 )
        {
          pos = v.find(Parameters[IDX_KEY_END]);
          if( pos == string::npos )
          {
            error("unexpected end of macro definition");
            return false;
          }
          pars.push_back(v.substr(0,pos));
        }
      }
//cout << "define " << id.c_str() << "\n";
//for( size_t i=0; i < pars.size(); ++i )
//cout << "parameter " << i << pars[i].c_str() << "\n";

      MacDefines[id] = pars;
      return true;
    }
    error("unknown define keyword");
    return false;
  }

  string CStyxPScanner::applyMacro
         (
           const V_string& Definition, const V_string& Parameters
         )
  { const string& text = Definition[Definition.size()-1]; 
    string res; res.reserve(1000);
    for( size_t i=0, j=0; i < text.length(); )
    { 
      for( j=0; j < Definition.size()-1; ++j )
      { size_t pos = text.find(Definition[j],i);
        if( pos == i ) break;
      }
      if( j < Definition.size()-1 )
      {
        res += Parameters[j+1];
        i += Definition[j].length();
      }
      else 
      {
        res += text[i]; ++i;
      }
    }
    return res;
  }

  string CStyxPScanner::evalMacroParameter(const string& Value, string& id)
  { V_string& macexp = MacStack[MacStack.size()-1];
    id = macexp[0];
    macexp.push_back(Value);
    V_string& macdfn = MacDefines[id];
    if( macdfn.size() == macexp.size() )
    { string text = applyMacro(macdfn,macexp);
      MacStack.pop_back();
      if( MacStack.size() == 0 ) return text;
      return evalMacroParameter(text,id);
    }
    return "";
  }

  string CStyxPScanner::evalMacroCall(const string& Value, string& id)
  { V_string& macdfn = MacDefines[Value];
    V_string call;
    id = Value;
//cout << "eval call " << id.c_str() << "\n";
    if( MacStack.size() == 0 )
    {
      if( macdfn.size() == 0 ) return "";
      if( macdfn.size() == 1 ) return macdfn[0];
      call.push_back(Value);
      MacStack.push_back(call);
      return "";
    }
    string par;
    if( macdfn.size() == 0 ) return evalMacroParameter(par,id);
    if( macdfn.size() == 1 ) return evalMacroParameter(macdfn[0],id);
    call.push_back(Value);
    MacStack.push_back(call);
    return "";
  }

  bool CStyxPScanner::partialParameter(const string& Value)
  {
    return CurSep != 0 && 
           ( Value.length() != 1 || ((int)Value[0]) != CurSep );
  }

  void CStyxPScanner::setSeparator(const string& Value)
  {
    if( Value.length() >= 2 && !isspace(Value[1]) )
      CurSep = (int)Value[1];
    else CurSep = 0;
  }
  
  bool CStyxPScanner::preprocessToken
       (
         CStyxStream*& PStream, const string& Token, string& Value
       )
  {
    if( Parameters[IDX_MAC_COND] == Token )
    {
      return preprocessCondition(PStream,Token,Value);
    }
    if( CondStack.size() > 0 && !CondStack[CondStack.size()-1] )
    {
      PStream = 0; return true;
    }
    if( Parameters[IDX_MAC_INC] == Token )
    {
      PStream = evalInclude(Value);
      return PStream != 0;
    }
    if( Parameters[IDX_MAC_DFN] == Token )
    {
      PStream = 0;
      return evalDefine(Value);
    }
    if( Parameters[IDX_MAC_DEL] == Token )
    {
      PStream = 0;
      return evalUndefine(Value);
    }
    bool ide = ( Parameters[IDX_TOK_IDE] == Token );
    string id, text;
    if( ide )
    {
      if( MacIgnCase ) 
      {
        id = Value; id = string2lower(id);
      }
      else
      if( ignoreCase() )
      {
        error("case ignore mismatch between macros and identifier token");
        return false;
      }
    }
    if( ide && 
        MacDefines.find(id.length()>0?id:Value) != MacDefines.end() )
    { string sid;
      text = evalMacroCall(id.length()>0?id:Value,sid);
      if( text.length() > 0 )
      {
        PStream = createMacroStream(sid,text);
        return PStream != 0;
      }
      PStream = 0; return true;
    }
    if( Parameters[IDX_MAC_SEP] == Token )
    {
      setSeparator(Value);
      if( MacStack.size() > 0 && CurSep == 0 && CurPar.length() > 0 )
      { 
        text = evalMacroParameter(CurPar,id="");
        CurPar = "";
        if( text.length() > 0 )
        {
          PStream = createMacroStream(id,text);
          return PStream != 0;
        }
      }
      PStream = 0; return true;
    }
    if( MacStack.size() > 0 )
    {
      if( CurSep == 0 && CurPar.length() == 0 )
      { 
        text = evalMacroParameter(Value,id="");
        if( text.length() > 0 )
        {
          PStream = createMacroStream(id,text);
          return PStream != 0;
        }
        PStream = 0; return true;
      }
      if( partialParameter(Value) )
      {
        CurPar += Value; PStream = 0; return true;
      }
      text = evalMacroParameter(CurPar,id="");
      CurPar = "";
      if( text.length() > 0 )
      {
        PStream = createMacroStream(id,text);
        return PStream != 0;
      }
      PStream = 0; return true;
    }
    return true;
  }
  
  bool CStyxPScanner::preprocessToken
       (
         CStyxStream*& PStream, const string& Token, wstring& Value
       )
  { string mbval, umbval;
    if( Value.length() > 0 )
    {
      mbval = umbval = unicode2multibyte(Value);
      if( mbval.length() < Value.length() )
      {
        error("unicode --> multibyte conversion failed");
        return false;
      }
    }
    bool res = preprocessToken(PStream,Token,umbval);
    if( ! res ) return false;
    if( umbval.length() == 0 ) Value.erase();
    else
    if( umbval != mbval )
    {
      Value = multibyte2unicode(umbval);
      if( Value.length() == 0 )
      {
        error("multibyte --> unicode conversion failed");
        return false;
      }
    }
    return true;
  }

  void CStyxPScanner::setParameters(const M_pardfn& parmap)
  { M_pardfn::const_iterator pos = parmap.begin();
    for( ; pos != parmap.end(); ++pos )
    {
      if( Parameters.find((*pos).first) != Parameters.end() )
      {
        Parameters[(*pos).first] = (*pos).second;
      }
    }
  }

  string CStyxPScanner::getParameter(short paridx)
  { M_pardfn::iterator pos = Parameters.find(paridx);
    if( pos != Parameters.end() )
      return (*pos).second;
    return "";
  }

}
