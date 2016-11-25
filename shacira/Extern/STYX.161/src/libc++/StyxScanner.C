/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxScanner.C]      Styx Scanner Implementation (C++)                   */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2003 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */


#include "StyxScanner.h"
#include <iostream>
#include <fstream>

using namespace styx;


CStyxStream::CStyxStream()
{
  cEof = 0;
}

CStyxStream::CStyxStream(string Path)
{ char* p = strrchr(Path.c_str(),'/');
  if( p == NULL )
    p = strrchr(Path.c_str(),'\\');
  if( p != NULL )
    File = p + 1;
  else
    File = Path;
  cEof = 0;
}

CStyxStream::~CStyxStream()
{
}

int CStyxStream::sgetc()
{
  return 0;
}

bool CStyxStream::eof(int c)
{
  return c <= cEof;
}

bool CStyxStream::unicode()
{
  return false;
}

string& CStyxStream::getFile() 
{
  return File;
}


CStyxStringStream::CStyxStringStream()
: CStyxStream("")
{
  this->txt = "";
  pos       = (long int)0L;
}

CStyxStringStream::CStyxStringStream(string ntxt)
: CStyxStream("")
{
  this->txt = ntxt.c_str();
  pos       = (long int)0L;
}

CStyxStringStream::~CStyxStringStream()
{
}

string& CStyxStringStream::getText()
{
  return txt;
}

void CStyxStringStream::setText(string ntxt)
{
  this->txt = ntxt.c_str();
  pos       = (long int)0L;
//printf("STREAM-TEXT=%s\n",this->txt.c_str());
}

int CStyxStringStream::sgetc()
{
  if( pos >= (long int)txt.length() )
    return 0;
  return (int)((txt[pos++])&0xff);
}

  
void CStyxScanner::setLanguage(string Language)
{
  Name = Language;
}
  
void CStyxScanner::addToken(string Token)
{
  TokId.push_back(Token);
}

void CStyxScanner::addTokenFlags(byte Flag)
{
  Flags.push_back(Flag);
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

void CStyxScanner::addDyckScanner(CStyxScanner& Scanner)
{
  dyckpat.push_back(Scanner);
}

void CStyxScanner::addSwitchToken(short Token, short Group)
{
  Switch[Token] = Group;
}

void CStyxScanner::addGroupScanner(CStyxScanner& Scanner)
{
  GrpScn.push_back(Scanner);
}

bool CStyxScanner::switchGroup(short Group)
{ 
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
  if( cStream->unicode() )
    wbuffer.erase();
  else
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
  return true;
}

void CStyxScanner::getCharacter()
{
  addCharacter(cC);
  if (cC == (cStream->unicode() ? (int)L'\n' : (int)'\n'))
  { nLine += 1; nCol = 1; }
  else
  { nCol += 1; }
  cC = cStream->sgetc();
  if( !skipC.empty() ) skipCharacter();
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
      GrpScn[Group].Switch[cTok] >= 0 && 
      !switchGroup(GrpScn[Group].Switch[cTok]) )
    return false;
LOOP:
  /* '\0' (string) and -1 (file,buffer) is treated as EOF. */
  cTok = -1; /* -1 == ETX */
  if ( !cStream->eof(cC) )
  { register wchar_t* i; 
    wchar_t* s = (wchar_t*)EdgeC.data();
    state = 0;
    for (i = &s[StaEdg[state]]; *i++ > (wchar_t)cC; );
    state = EdgeS[i-s-1]-1;
    while (state >= 0)
    {
      /* n character lookahead:
         jeweils den größten Endzustand merken, zusammen mit Tokenlänge.
         nach der schleife, 
         1) wert oder fehler 
         2) fehler mit vorangegangenem Wert --> 
            zurücksetzen auf ende wertposition via backbuffer und fortsetzen
      */
      cTok = StaFin[state]; getCharacter();
      if ( cStream->eof(cC) )
      {
        break;
      }
      for (i = &s[StaEdg[state]]; *i++ > (wchar_t)cC; );
      state = EdgeS[i-s-1]-1;
    }
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
          GrpScn[Group].Switch[cTok] >= 0 && 
          !switchGroup(GrpScn[Group].Switch[cTok]) )
        return false;
      goto LOOP; 
    }
  }
  return endToken();
}


CStyxScanner::CStyxScanner()
{
  cStream = 0;
  cC      = cTok = Group = -1;
  cLine   = cCol = nLine = nCol = 1;
  next    = &CStyxScanner::nextToken_default;
}

CStyxScanner::CStyxScanner(string Language)
{
  Name    = Language; 
  cStream = 0;
  cC      = cTok = Group = -1;
  cLine   = cCol = nLine = nCol = 1;
  next    = &CStyxScanner::nextToken_default;
}

CStyxScanner::~CStyxScanner()
{
}

string& CStyxScanner::getLanguage()
{
  return Name;
}

short CStyxScanner::getTokens()
{
  return (short)TokId.size();
}

string& CStyxScanner::getNthToken(short Nth)
{
  return TokId.size() >= 1 && TokId.size() <= (size_t)Nth 
         ? TokId[Nth-1] : Name;
}

bool CStyxScanner::loadTableLine
     (
       string& line, CStyxScanner*& cScanner, 
       string& object, short& tokidx
     )
{
  if( line.length() > 0 && line[0] != '#' )
  { char* n = strstr(line.c_str(),"Name=");
    if( n != NULL )
    {
      cScanner->setLanguage(n+strlen("Name="));
    }
    else
    if( line == "Group" )
    {
      GrpScn.push_back(CStyxScanner());
      cScanner = &GrpScn[GrpScn.size()-1];
    }
    else
    if( line == "Dyck" )
    {
      dyckpat.push_back(CStyxScanner());
      cScanner = &dyckpat[dyckpat.size()-1];
    }
    else
    if( line == "Language" )
    {
      cScanner = this;
    }
    else
    if( !isdigit(line[0]) && !isspace(line[0]) )
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
    if( isdigit(line[0]) )
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
        cScanner->addTokenFlags((byte)v);
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
        cScanner->addDyckToken((short)v);
      }
    }
  }
  line = "";
  return true;
}

bool CStyxScanner::loadTableFile(string Path)
{ ifstream is(Path.c_str()); char c;
  if( !is ) 
  {
    fprintf(stderr,"couldn't open '%s'\n",Path.c_str());
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
  return GrpScn.size() > 0 ||
         StaFin.size() > 0 && StaEdg.size() > 0 && 
         EdgeS.size() > 0 && EdgeC.length() > 0 &&
         TokId.size() > 0 && Flags.size() == Flags.size();
}

bool CStyxScanner::loadTableString(string Table)
{ char c;
  string line, object; 
  CStyxScanner* cScanner = this;
  short tokidx = 0;
  for( size_t i=0; i < Table.size(); ++i )
  {
    c = Table[i];
    if( c == '\n' )
    {
      if( !loadTableLine(line,cScanner,object,tokidx) )
        return false;
    }
    else line += c;
  }
  return GrpScn.size() > 0 ||
         StaFin.size() > 0 && StaEdg.size() > 0 && 
         EdgeS.size() > 0 && EdgeC.length() > 0 &&
         TokId.size() > 0 && Flags.size() == Flags.size();
}

bool CStyxScanner::scanStream(CStyxStream* Stream, S_int& SkipTokens)
{ 
  next    = &CStyxScanner::nextToken_default;
  cStream = Stream;
  skipC   = SkipTokens;
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
  return true;
}

bool CStyxScanner::eos()
{
  return (cTok == -1); 
}

bool    CStyxScanner::nextToken()
{
  return cStream && (this->*next)() 
         ? true : ( cStream = 0, false );
}

bool CStyxScanner::currentToken(string& Token, string& Value)
{
  if( cStream && !cStream->unicode() )
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
  if( cStream && cStream->unicode() )
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

long CStyxScanner::getLine()
{
  return cLine;
}

long CStyxScanner::getCol() 
{
  return cCol;
}

string& CStyxScanner::getFile() 
{
  return cStream ? cStream->getFile() : Name;
}
