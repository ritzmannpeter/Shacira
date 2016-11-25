/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxParseTable.h]   Styx Parse Table Implementation (C++)               */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2005 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "StyxParseTable.h"


namespace styx
{

  static bool equalSign(long l, long r)
  {
    return ( l <= 0 && r <= 0 ) ||
           ( l >= 0 && r >= 0 );
  }

  /* Parse Table ------------------------------------------------------------- */
  
  CStyxParseTable::CStyxParseTable() : CStyxParseTableApi()
  {
    reset();
  }
  
  CStyxParseTable::~CStyxParseTable()
  {
  }
  
  void CStyxParseTable::reset()
  {
    initok = false;
    Name   = "";
    TkCnt  = NtCnt = -1;
    SNames.clear();
    StartIds.clear();
    TokKind.clear();
    NtClass.clear();
    ErrorNt.clear();
    Products.clear();
    MstShift.clear();
    DtlShift.clear();
    GoTo.clear();
    GoToDft.clear();
    ActDft.clear();
    ActExp.clear();
  }
  
  void CStyxParseTable::setLanguage(string Language)
  {
    Name = Language;
  }
  
  void CStyxParseTable::setTokenCount(long TCount)
  {
    TkCnt = TCount;
  }
  
  void CStyxParseTable::setNonterminalCount(long NCount)
  {
    NtCnt = NCount;
  }
  
  void CStyxParseTable::addCfgSymbol(string SName)
  {
    SNames.push_back(SName);
  }
  
  void CStyxParseTable::addStartSymbol(long SNSymbol)
  {
    StartIds.push_back(SNSymbol);
  }
  
  bool CStyxParseTable::addTokenType(short TType)
  {
    TokKind.push_back(TType);
    if( styx::isEmbeddedLanguage(TType) )
    {
      error("unsupported embedded language type");
      return false;
    }
    return true;
  }
  
  void CStyxParseTable::addNonterminalClass(long NIndex)
  {
    NtClass.push_back(NIndex);
  }
  
  void CStyxParseTable::addErrorNonterminal(bool Reparse)
  {
    ErrorNt.push_back(Reparse);
  }
  
  void CStyxParseTable::addProduction(const StyxProduction& Production)
  {
    Products.push_back(Production);
  }
  
  void CStyxParseTable::addMstShiftEntry(long Entry)
  {
    MstShift.push_back(Entry);
  }
  
  void CStyxParseTable::addDtlShiftEntry(long Entry)
  {
    DtlShift.push_back(Entry);
  }
  
  void CStyxParseTable::addGoToEntry(long Entry)
  {
    GoTo.push_back(Entry);
  }
  
  void CStyxParseTable::addGoToDftEntry(long Entry)
  {
    GoToDft.push_back(Entry);
  }
  
  void CStyxParseTable::addActDftEntry(long Entry)
  {
    ActDft.push_back(Entry);
  }
  
  void CStyxParseTable::addActExpEntry(long Entry)
  {
    ActExp.push_back(Entry);
  }
  
  bool CStyxParseTable::setProductionName(string PName)
  {
    if( Products.size() == 0 ) return false;
    Products[Products.size()-1].PName = PName;
    return true;
  }
  
  bool CStyxParseTable::setProductionMethod(short PMethod)
  {
    if( Products.size() == 0 ) return false;
    Products[Products.size()-1].Method = PMethod;
    return true;
  }
  
  bool CStyxParseTable::setProductionNonterminal(long PNSymbol)
  {
    if( Products.size() == 0 ) return false;
    Products[Products.size()-1].NtId = PNSymbol;
    return true;
  }
  
  bool CStyxParseTable::addProductionSymbol(long PMSymbol)
  {
    if( Products.size() == 0 ) return false;
    Products[Products.size()-1].Symbols.push_back(PMSymbol);
    return true;
  }
  
  bool CStyxParseTable::addProductionLayout(long PMLayout)
  {
    if( Products.size() == 0 ) return false;
    Products[Products.size()-1].SymFrms.push_back(PMLayout);
    return true;
  }
  
  bool CStyxParseTable::loadTableLine
       (
         string& line, string& object
       )
  {
    if( line.length() > 0 && line[0] != '#' )
    { char* n = strstr((char*)line.c_str(),"Name=");
      if( n != NULL )
      {
        setLanguage(n+strlen("Name="));
      }
      else
      if( ( n = strstr((char*)line.c_str(),"TkCnt=") ) != NULL )
      {
        setTokenCount(atol(n+strlen("TkCnt=")));
      }
      else
      if( ( n = strstr((char*)line.c_str(),"NtCnt=") ) != NULL )
      {
        setNonterminalCount(atol(n+strlen("NtCnt=")));
      }
      else
      if( ( n = strstr((char*)line.c_str(),"pname=") ) != NULL )
      {
        if( !setProductionName(n+strlen("pname=")) ) 
        {
          error(string("invalid: ") + line);
          return false;
        }
      }
      else
      if( ( n = strstr((char*)line.c_str(),"method=") ) != NULL )
      {
        if( !setProductionMethod((short)atoi(n+strlen("method="))) ) 
        {
          error(string("invalid: ") + line);
          return false;
        }
      }
      else
      if( ( n = strstr((char*)line.c_str(),"id=") ) != NULL )
      {
        if( !setProductionNonterminal(atol(n+strlen("id="))) ) 
        {
          error(string("invalid: ") + line);
          return false;
        }
      }
      else
      if( line[0] != '-' && !isdigit(line[0]) && !isspace(line[0]) )
      {
        object = line;
        if( object == "KFGPROD" )
        { StyxProduction p;
          addProduction(p);
        }
      }
      else
      if( isspace(line[0]) )
      {
        addCfgSymbol(line.c_str()+1);
      }
      else
      if( line[0] == '-' || isdigit(line[0]) )
      { long v = atol(line.c_str());
        if( object == "StartIds" )
        {
          addStartSymbol(v);
        }
        else
        if( object == "TokKind" )
        {
          if( !addTokenType((short)v) )
          {
            return false;
          }
        }
        else
        if( object == "NtClass" )
        {
          addNonterminalClass(v);
        }
        else
        if( object == "ErrorNt" )
        {
          addErrorNonterminal(v!=0);
        }
        else
        if( object == "symbols" )
        {
          if( !addProductionSymbol(v) )
          {
            error(string("invalid symbols object: ") + line);
            return false;
          }
        }
        else
        if( object == "symfrms" )
        {
          if( !addProductionLayout(v) )
          {
            error(string("invalid symfrms object: ") + line);
            return false;
          }
        }
        else
        if( object == "MstShift" )
        {
          addMstShiftEntry(v);
        }
        else
        if( object == "DtlShift" )
        {
          addDtlShiftEntry(v);
        }
        else
        if( object == "GoTo" )
        {
          addGoToEntry(v);
        }
        else
        if( object == "GoToDft" )
        {
          addGoToDftEntry(v);
        }
        else
        if( object == "ActDft" )
        {
          addActDftEntry(v);
        }
        else
        if( object == "ActExp" )
        {
          addActExpEntry(v);
        }
      }
    }
    line = "";
    return true;
  }
  
  bool CStyxParseTable::checkLoad()
  { 
    bool result = (size_t)(TkCnt + NtCnt) == SNames.size() &&
                  StartIds.size() <= (size_t)NtCnt         && 
                  TokKind.size() == (size_t)TkCnt          &&
                  NtClass.size() == (size_t)NtCnt          &&
                  ErrorNt.size() == (size_t)NtCnt          &&
                  Products.size() >= (size_t)NtCnt         && 
                  MstShift.size() == ActDft.size()         &&
                  GoTo.size() == (size_t)NtCnt;
    if( !result ) error("invalid parse table format");
    return result;
  }
  
  bool CStyxParseTable::loadTableFile(string Path)
  { 
    reset();
    ifstream is(Path.c_str()); char c;
    if( !is ) 
    {
      error(string("couldn't open '") + Path + string("'"));
      return false;
    }
    string line, object; 
    while( is.get(c) )
    {
      if( c == '\n' )
      {
        if( line.length() == 1 && isspace(line[0]) ) // keyword '\n'
          line += c;
        else
        if( !loadTableLine(line,object) )
          return false;
      }
      else line += c;
    }
    initok = checkLoad();
    return initok;
  }
  
  bool CStyxParseTable::loadTableString(string Table)
  { 
    reset();
    char c; string line, object; 
    for( size_t i=0; i < Table.length(); ++i )
    {
      c = Table[i];
      if( c == '\n' )
      {
        if( line.length() == 1 && isspace(line[0]) ) // keyword '\n'
          line += c;
        else
        if( !loadTableLine(line,object) )
          return false;
      }
      else line += c;
    }
    initok = checkLoad();
    return initok;
  }
  
  string CStyxParseTable::getLanguage()
  {
    if( !initok ) return "";
    return Name;
  }
  
  long CStyxParseTable::getTokenCount()
  {
    if( !initok ) return -1;
    return TkCnt;
  }
  
  long CStyxParseTable::getNonterminalCount()
  {
    if( !initok ) return -1;
    return NtCnt;
  }
  
  long CStyxParseTable::getSymbolCount()
  {
    if( !initok ) return -1;
    return (long)(SNames.size() + StartIds.size());
  }
  
  long CStyxParseTable::getTerminalCount()
  {
    if( !initok ) return -1;
    return TkCnt + (long)StartIds.size();
  }
  
  long CStyxParseTable::getMetaSymbolCount()
  {
    if( !initok ) return -1;
    return NtCnt + (long)StartIds.size();
  }
  
  long CStyxParseTable::getStartSymbolCount()
  {
    if( !initok ) return -1;
    return (long)StartIds.size();
  }
  
  long CStyxParseTable::TokenIndex2TerminalIndex(long TKIndex, long SNIndex)
  {
    if( !initok || TKIndex < -1 ) return -1;
    if( TKIndex == -1 ) return TkCnt + SNIndex;
    else                return TKIndex;
  }
  
  bool CStyxParseTable::isAcceptTerminal(long TIndex)
  {
    if( !initok ) return false;
    return TIndex >= TkCnt;
  }
  
  long CStyxParseTable::TerminalIndex2Symbol(long TIndex)
  {
    if( !initok ) return -1;
    if( TIndex >= 0 && TIndex < TkCnt ) return TIndex;
    else
    { long sidx = TIndex - TkCnt;
      if( sidx >= 0 && ((size_t)sidx) < StartIds.size() )
        return StartIds[sidx];
    }
    return -1;
  }
  
  long CStyxParseTable::TerminalSymbol2Index(long TSymbol)
  {
    if( !initok ) return -1;
    if( TSymbol >= 0 && TSymbol < TkCnt ) return TSymbol;
    else
    { long sidx = StartSymbol2Index(TSymbol);
      if( sidx >= 0 ) return TkCnt + sidx;
    }
    return -1;
  }
  
  long CStyxParseTable::StartIndex2Symbol(long SNIndex)
  {
    if( !initok ) return -1;
    if( SNIndex >= 0 && ((size_t)SNIndex) < StartIds.size() )
      return StartIds[SNIndex];
    return -1;
  }
  
  long CStyxParseTable::StartSymbol2Index(long SNSymbol)
  {
    if( !initok ) return -1;
    for( size_t i=0; i < StartIds.size(); ++i )
      if( StartIds[i] == SNSymbol )
        return (long)i;
    return -1;
  }
  
  long CStyxParseTable::StartName2Index(string StartSymbolName)
  {
    if( !initok ) return -1;
    if( StartSymbolName.length() == 0 )
    {
      if( StartIds.size() > 0 )
        return 0;
      return -1;
    }
    for( size_t i=0; i < StartIds.size(); ++i )
    {
      if( getSymbolName(StartIds[i]) == StartSymbolName )
        return (long)i;
    }
    return -1;
  }
  
  long CStyxParseTable::NonterminalIndex2Class(long NIndex)
  {
    if( !initok ) return -1;
    if( NIndex >= 0 && NIndex < NtCnt )
      return NtClass[NIndex];
    else
    if( NIndex >= NtCnt ) return NIndex;
    return -1;
  }
  
  long CStyxParseTable::NonterminalIndex2Symbol(long NIndex)
  {
    if( !initok ) return -1;
    return NIndex + TkCnt;
  }
  
  long CStyxParseTable::NonterminalSymbol2Index(long NSymbol)
  {
    if( !initok ) return -1;
    return NSymbol - TkCnt;
  }
  
  bool CStyxParseTable::isErrorNonterminal(long NIndex)
  {
    if( !initok ) return false;
    if( NIndex >= 0 && NIndex < NtCnt )
      return ErrorNt[NIndex];
    return false;
  }
  
  short CStyxParseTable::getSymbolType(long Symbol)
  {
    if( !initok ) return -1;
    if( Symbol >= 0 && Symbol < getSymbolCount() )
    {
      if( Symbol >= TkCnt )
        return CFG_TYP_NTM;
      else
        return TokKind[Symbol];
    }
    return -1;
  }
  
  bool CStyxParseTable::isNonterminal(long Symbol)
  {
    if( !initok ) return false;
    return styx::isNonterminal(getSymbolType(Symbol));
  }
  
  bool CStyxParseTable::isToken(long Symbol)
  {
    if( !initok ) return false;
    return styx::isToken(getSymbolType(Symbol));
  }
  
  bool CStyxParseTable::isComment(long Symbol)
  {
    if( !initok ) return false;
    return styx::isComment(getSymbolType(Symbol));
  }
  
  bool CStyxParseTable::isKeyword(long Symbol)
  {
    if( !initok ) return false;
    return styx::isKeyword(getSymbolType(Symbol));
  }
  
  bool CStyxParseTable::isUnicodeKeyword(long Symbol)
  {
    if( !initok ) return false;
    return styx::isUnicodeKeyword(getSymbolType(Symbol));
  }
  
  string CStyxParseTable::getSymbolName(long Symbol)
  {
    if( !initok ) return "";
    if( Symbol >= 0 && Symbol < getSymbolCount() )
    {
      if( Symbol < TkCnt + NtCnt )
        return SNames[Symbol];
      else
        return Name;
    }
    return "";
  }
  
  long CStyxParseTable::getProductionCount()
  {
    if( !initok ) return -1;
    return (long)Products.size();
  }
  
  string CStyxParseTable::getProductionName(long PIndex)
  {
    if( !initok ) return "";
    if( PIndex >= 0 && ((size_t)PIndex) < Products.size() )
    {
      return Products[PIndex].PName;
    }
    return "";
  }
  
  long CStyxParseTable::getProductionNonterminal(long PIndex)
  {
    if( !initok ) return -1;
    if( PIndex >= 0 && ((size_t)PIndex) < Products.size() )
    {
      return Products[PIndex].NtId;
    }
    return -1;
  }
  
  short CStyxParseTable::getProductionMethod(long PIndex)
  {
    if( !initok ) return -1;
    if( PIndex >= 0 && ((size_t)PIndex) < Products.size() )
    {
      return Products[PIndex].Method;
    }
    return -1;
  }
  
  long CStyxParseTable::getProductionSymbolCount(long PIndex)
  {
    if( !initok ) return -1;
    if( PIndex >= 0 && ((size_t)PIndex) < Products.size() )
    {
      return (long)Products[PIndex].Symbols.size();
    }
    return -1;
  }
  
  long CStyxParseTable::getProductionSymbol(long PIndex, long PMIndex)
  {
    if( !initok ) return -1;
    if( PIndex >= 0 && ((size_t)PIndex) < Products.size() &&
        PMIndex >= 0 && ((size_t)PMIndex) < Products[PIndex].Symbols.size() )
    {
      return Products[PIndex].Symbols[PMIndex];
    }
    return -1;
  }
  
  long CStyxParseTable::getProductionLayout(long PIndex, long PMIndex)
  {
    if( !initok ) return -1;
    if( PIndex >= 0 && ((size_t)PIndex) < Products.size() &&
        PMIndex >= 0 && ((size_t)PMIndex) < Products[PIndex].SymFrms.size() )
    {
      return Products[PIndex].SymFrms[PMIndex];
    }
    return -1;
  }
  
  long CStyxParseTable::getMstShiftCount()
  {
    if( !initok ) return -1;
    return (long)MstShift.size();
  }
  
  long CStyxParseTable::getMstShiftEntry(long Index)
  {
    if( !initok ) return -1;
    if( Index >= 0 && ((size_t)Index) < MstShift.size() )
    {
      return (long)MstShift[Index];
    }
    return -1;
  }
  
  long CStyxParseTable::getDtlShiftCount()
  {
    if( !initok ) return -1;
    return (long)DtlShift.size();
  }
  
  long CStyxParseTable::getDtlShiftEntry(long Index)
  {
    if( !initok ) return -1;
    if( Index >= 0 && ((size_t)Index) < DtlShift.size() )
    {
      return (long)DtlShift[Index];
    }
    return -1;
  }
  
  long CStyxParseTable::getGoToCount()
  {
    if( !initok ) return -1;
    return (long)GoTo.size();
  }
  
  long CStyxParseTable::getGoToEntry(long Index)
  {
    if( !initok ) return -1;
    if( Index >= 0 && ((size_t)Index) < GoTo.size() )
    {
      return (long)GoTo[Index];
    }
    return -1;
  }
  
  long CStyxParseTable::getGoToDftCount()
  {
    if( !initok ) return -1;
    return (long)GoToDft.size();
  }
  
  long CStyxParseTable::getGoToDftEntry(long Index)
  {
    if( !initok ) return -1;
    if( Index >= 0 && ((size_t)Index) < GoToDft.size() )
    {
      return (long)GoToDft[Index];
    }
    return -1;
  }
  
  long CStyxParseTable::getActDftCount()
  {
    if( !initok ) return -1;
    return (long)ActDft.size();
  }
  
  long CStyxParseTable::getActDftEntry(long Index)
  {
    if( !initok ) return -1;
    if( Index >= 0 && ((size_t)Index) < ActDft.size() )
    {
      return (long)ActDft[Index];
    }
    return -1;
  }
  
  long CStyxParseTable::getActExpCount()
  {
    if( !initok ) return -1;
    return (long)ActExp.size();
  }
  
  long CStyxParseTable::getActExpEntry(long Index)
  {
    if( !initok ) return -1;
    if( Index >= 0 && ((size_t)Index) < ActExp.size() )
    {
      return (long)ActExp[Index];
    }
    return -1;
  }
  
  long CStyxParseTable::getStateCount()
  {
    if( !initok ) return -1;
    return (long)MstShift.size();
  }
  
  bool CStyxParseTable::getShiftValues(long STIndex, V_plong& Values)
  { 
    Values.clear();
    if( initok && STIndex >= 0 && ((size_t)STIndex) < MstShift.size() )
    {
      if( MstShift[STIndex] >= 0 )
      {
        for( long i = MstShift[STIndex], j = i-1; 
             i < ((long)DtlShift.size()) && DtlShift[i] >= 0; ++i, --j )
        { long  token = DtlShift[i],
                state = abs(DtlShift[j])-1;
          plong p(token,state);
          Values.push_back(p);
        }
      }
      return true;
    }
    return false;
  }
  
  bool CStyxParseTable::getGoToValues(long NIndex, V_plong& Values)
  {
    Values.clear();
    if( initok && NIndex >= 0 && NIndex < NtCnt )
    { long lastidx = ((size_t)NIndex) < GoTo.size()-1 
                     ? GoTo[NIndex+1] : ((long)GoToDft.size()), 
                     fstate = -1;
      if( GoTo[NIndex] >= 0 )
      {
        for( long i = GoTo[NIndex]; i < lastidx; ++i )
        { long state = GoToDft[i];
          if( ((size_t)state) > MstShift.size() )
          {
            fstate = state - ((long)MstShift.size()) - 1;
          }
          else
          if( fstate >= 0 && state != 0 ) /* reachable nonterminal */
          {
            state = abs(state) - 1;
            plong p(fstate,state);
            Values.push_back(p);
          }
        }
      }
      return true;
    }
    return false;
  }
  
  bool CStyxParseTable::getActionValues(long STIndex, V_plong& Values)
  {
    Values.clear();
    if( initok && STIndex >= 0 && ((size_t)STIndex) < MstShift.size() )
    { long entry      = (long)ActDft[STIndex], 
           prodcnt    = (long)Products.size(),
           prodoffset = prodcnt + TkCnt + ((long)StartIds.size());
      if( entry >= 1 )
      {
        if( entry == prodcnt + 1 )
        { long  vaction = -2,
                vtoken  = -1;
          plong p(vaction,vtoken);
          Values.push_back(p);
        }
        else
        if( entry == prodcnt + 2 )
        { long  vaction = -1,
                vtoken  = -1;
          plong p(vaction,vtoken);
          Values.push_back(p);
        }
        else
        if( entry <= prodcnt )
        { long  vaction = entry-1,
                vtoken  = -1;
          plong p(vaction,vtoken);
          Values.push_back(p);
        }
      }
      else
      { long i       = abs(entry),
             e_first = ActExp[i],
             action  = -2;
        for( ; ((size_t)i) < ActExp.size() && equalSign(e_first,ActExp[i]); ++i )
        { long e_entry = abs(ActExp[i]);
          if( e_entry > prodoffset )
          {
            action = e_entry - prodoffset;
          }
          else
          {
            if( action == prodcnt + 2 )
            { long  vaction = -1,
                    vtoken  = e_entry-1;
              plong p(vaction,vtoken);
              Values.push_back(p);
            }
            else
            if( action <= prodcnt )
            { long  vaction = action-1,
                    vtoken  = e_entry-1;
              plong p(vaction,vtoken);
              Values.push_back(p);
            }
          }
        }
      }
      return true;
    }
    return false;
  }
  
  long CStyxParseTable::getErrorAction()
  {
    if( !initok ) return -1;
    return (long)Products.size() + 1;
  }
  
  long CStyxParseTable::getAcceptAction()
  {
    if( !initok ) return -1;
    return (long)Products.size() + 2;
  }
  
  long CStyxParseTable::getActionOffset()
  {
    if( !initok ) return -1;
    return (long)Products.size() + getTerminalCount();
  }
  
  long CStyxParseTable::getShiftState(long STIndex, long TIndex) 
  {
    if( !initok || STIndex < 0 || STIndex >= ((long)MstShift.size()) )
      return PLR_SHIFT_ERROR;
    if( TIndex >= 0 && TIndex < TkCnt && styx::isComment(TokKind[TIndex]) )
      return PLR_SHIFT_NONE;
    if( MstShift[STIndex] == PLR_SHIFT_ERROR )
      return PLR_SHIFT_ERROR;
    for( long i = MstShift[STIndex], j = i-1; 
         i < ((long)DtlShift.size()) && DtlShift[i] >= 0; ++i, --j )
    {
      if( DtlShift[i] == TIndex )
        return abs(DtlShift[j]) - 1;
    }
    return PLR_SHIFT_ERROR;
  }
  
  long CStyxParseTable::getGoToState(long STIndex, long NIndex) 
  {
    if( !initok || 
        STIndex < 0 || STIndex >= ((long)MstShift.size()) ||
        NIndex < 0 || NIndex >= NtCnt ) 
      return PLR_GOTO_ERROR;
    long lastidx = ( NIndex < ((long)GoTo.size()) - 1 ) 
                   ? GoTo[NIndex+1] 
                   : (long)GoToDft.size(),
         fstate  = PLR_GOTO_ERROR;
    for( long i = GoTo[NIndex]; i < lastidx; ++i )
    { long entry = GoToDft[i];
      if( entry > ((long)MstShift.size()) )
        fstate = entry - ((long)MstShift.size()) - 1;
      else
      {
        if( abs(entry) - 1 == STIndex ) return( fstate );
      }  
    }
    return PLR_GOTO_ERROR;
  }
  
  long CStyxParseTable::getReduceAction(long STIndex, long TIndex) 
  {
    if( !initok || STIndex < 0 || STIndex >= ((long)MstShift.size()) )
      return -1;
    long entry = ActDft[STIndex];
    if( entry >= 1 ) return entry;
    else
    { long i       = abs(entry), 
           e_first = ActExp[i], 
           action  = getErrorAction();
      for( ; i < ((long)ActExp.size()) && equalSign(e_first,ActExp[i]); ++i )
      { long e_entry = abs(ActExp[i]);
        if( e_entry > getActionOffset() )
          action = e_entry - getActionOffset();
        else
        {
          if( e_entry - 1 == TIndex ) return action;
        }  
      }
      return getErrorAction();
    }
  }
  
  bool CStyxParseTable::tryEarlyAction(long STIndex, long& Action) 
  {
    if( !initok || STIndex < 0 || STIndex >= ((long)MstShift.size()) )
      return false;
    if( MstShift[STIndex] != PLR_SHIFT_ERROR )
      return false;
    Action = ActDft[STIndex];
    return Action >= 1 && !isErrorAction(Action);
  }
  
  bool CStyxParseTable::isErrorAction(long Action)
  {
    if( !initok ) return false;
    //return ((long)Products.size()) + 1 == Action;
    return Action == -1 || ((long)Products.size()) + 1 == Action;
  }
  
  bool CStyxParseTable::isAcceptAction(long Action)
  {
    if( !initok ) return false;
    return ((long)Products.size()) + 2 == Action;
  }
  
  long CStyxParseTable::Action2Production(long Action, long SNIndex)
  {
    if( !initok ) return -1;
    if( Action <= ((long)Products.size()) )
    {
      return Action - 1;
    }
    else
    if( Action == ((long)Products.size()) + 2 )
    {
      return   ((long)Products.size())
             - ((long)StartIds.size())
             + SNIndex;
    }
    return -1;
  }
  
  void CStyxParseTable::error(string Text)
  {
    fprintf(stderr,"%s\n",Text.c_str());
  }
  
  bool CStyxParseTable::initialized()
  {
    return initok;
  }
  
}
