/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxParser.h]   Styx Parser Implementation (C++)                        */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2005 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_PARSER_INCL
#define STYX_PARSER_INCL


#include <wctype.h>
#include <string>
#include <vector>

/** @file
    Abstract parse table interface and parser 
*/


namespace styx
{
  using namespace std;

  /** @addtogroup StyxLibraryCPP
      C++ Scanner & parser library
  */
  //@{

  /** @addtogroup StyxParser
      Abstract parse table interface and parser 
  */
  //@{

  /** parser action (error) codes */
  enum EStyxParseAction
  {
    PLR_SHIFT_ERROR = -1, ///< shift error
    PLR_SHIFT_NONE  = -2, ///< no shift (comment)
    PLR_GOTO_ERROR  = -1  ///< goto error
  };

  /* Parse table Interface -------------------------------------------------- */

  /** @addtogroup AbstractParseTableAPI
      Abstract parse table interface 
  */
  //@{

  /** abstract parse table interface */
  class CStyxParseTableApi
  {
  public:
    /// The constructor creates an uninitialized parse table.
    CStyxParseTableApi() {}
    virtual ~CStyxParseTableApi() {}

                    /// parse table is initialized ?
                    /// @return true for an initialized parse table
    virtual bool    initialized() = 0;

                    /// get language
                    /// @return language name or ""
    virtual string  getLanguage() = 0;

                    /// get number of tokens
                    /// @return number of tokens or -1 
    virtual long    getTokenCount() = 0;
                    /// get number of nonterminals
                    /// @return number of nonterminals or -1 
    virtual long    getNonterminalCount() = 0;
                    /// get number of symbols 
                    /// (tokens incl. keywords, nonterminals, start symbols)
                    /// @return number of symbols or -1 
    virtual long    getSymbolCount() = 0;
                    /// get number of start symbols
                    /// @return number of start symbols or -1 
    virtual long    getStartSymbolCount() = 0;
                    /// get number of terminals 
                    /// (tokens incl. keywords, accept tokens)
                    /// @return number of terminals or -1 
    virtual long    getTerminalCount() = 0;
                    /// get number of meta symbols 
                    /// (nonterminals, start symbols)
                    /// @return number of meta symbols or -1 
    virtual long    getMetaSymbolCount() = 0;

                    /// token index --> terminal index
                    /// @param TKIndex token index \>= 0 or EOF = -1 or error \< -1
                    /// @param SNIndex current start symbol index
                    /// @return terminal index \>= 0 or -1
    virtual long    TokenIndex2TerminalIndex(long TKIndex, long SNIndex) = 0;

                    /// accept terminal ?
                    /// @param TIndex terminal index \>= 0
                    /// @return true for an accept terminal
    virtual bool    isAcceptTerminal(long TIndex) = 0;
                    /// terminal index --> symbol
                    /// @param TIndex terminal index \>= 0
                    /// @return terminal symbol \>= 0 or -1 
    virtual long    TerminalIndex2Symbol(long TIndex) = 0;
                    /// terminal symbol --> index
                    /// @param TSymbol terminal symbol \>= 0
                    /// @return terminal index \>= 0 or -1 
    virtual long    TerminalSymbol2Index(long TSymbol) = 0;

                    /// start symbol index --> symbol
                    /// @param SNIndex start symbol index \>= 0
                    /// @return start symbol \>= 0 or -1 
    virtual long    StartIndex2Symbol(long SNIndex) = 0;
                    /// start symbol symbol --> index
                    /// @param SNSymbol start symbol \>= 0
                    /// @return start symbol index \>= 0 or -1 
    virtual long    StartSymbol2Index(long SNSymbol) = 0;
                    /// start symbol name --> index
                    /// @param StartSymbolName start symbol name or "" (first start symbol)
                    /// @return start symbol index \>= 0 or -1 
    virtual long    StartName2Index(string StartSymbolName="") = 0;

                    /// nonterminal index --> symbol
                    /// @param NIndex nonterminal index \>= 0
                    /// @return nonterminal symbol \>= 0 or -1 
    virtual long    NonterminalIndex2Symbol(long NIndex) = 0;
                    /// nonterminal symbol --> index
                    /// @param NSymbol nonterminal symbol \>= 0
                    /// @return nonterminal index \>= 0 or -1 
    virtual long    NonterminalSymbol2Index(long NSymbol) = 0;
                    /// error (recovery) nonterminal ?
                    /// @param NIndex nonterminal index \>= 0
                    /// @return true for an error (recovery) nonterminal
    virtual bool    isErrorNonterminal(long NIndex) = 0;

                    /// nonterminal ?
                    /// @param Symbol CFG symbol \>= 0
                    /// @return true for a nonterminal
    virtual bool    isNonterminal(long Symbol) = 0;
                    /// regular token class ?
                    /// @param Symbol CFG symbol \>= 0
                    /// @return true for a regular token class
    virtual bool    isToken(long Symbol) = 0;
                    /// comment token ?
                    /// @param Symbol CFG symbol \>= 0
                    /// @return true for a comment token
    virtual bool    isComment(long Symbol) = 0;
                    /// keword ?
                    /// @param Symbol CFG symbol \>= 0
                    /// @return true for a keyword
    virtual bool    isKeyword(long Symbol) = 0;
                    /// get symbol name
                    /// @param Symbol CFG symbol \>= 0
                    /// @return symbol name or ""
    virtual string  getSymbolName(long Symbol) = 0;

                    /// get number of productions
                    /// @return number of productions or -1 
    virtual long    getProductionCount() = 0;
                    /// get production name
                    /// @param PIndex production index \>= 0
                    /// @return production name or ""
    virtual string  getProductionName(long PIndex) = 0;
                    /// get production nonterminal
                    /// @param PIndex production index \>= 0
                    /// @return nonterminal symbol \>= 0 or -1 
    virtual long    getProductionNonterminal(long PIndex) = 0;
                    /// get number of production member symbols
                    /// @param PIndex production index \>= 0
                    /// @return number of member symbols or -1 
    virtual long    getProductionSymbolCount(long PIndex) = 0;
                    /// get production member symbol
                    /// @param PIndex production index \>= 0
                    /// @param PMIndex production member index \>= 0
                    /// @return member symbol \>= 0 or -1 
    virtual long    getProductionSymbol(long PIndex, long PMIndex) = 0;

                    /// get number of states
                    /// @return number of states or -1 
    virtual long    getStateCount() = 0;
                    /// get error action
                    /// @return error action >= 0 or -1 
    virtual long    getErrorAction() = 0;
                    /// get accept action
                    /// @return accept action >= 0 or -1 
    virtual long    getAcceptAction() = 0;
                    /// get shift follow state for state and terminal index
                    /// @param STIndex current state index \>= 0
                    /// @param TIndex current terminal index \>= 0
                    /// @return follow state index \>= 0 or
                    /// PLR_SHIFT_NONE for a comment token or
                    /// PLR_SHIFT_ERROR
    virtual long    getShiftState(long STIndex, long TIndex) = 0; 
                    /// get goto follow state for state and nonterminal index
                    /// @param STIndex current state index \>= 0
                    /// @param NIndex current nonterminal index \>= 0
                    /// @return follow state index \>= 0 or PLR_GOTO_ERROR
    virtual long    getGoToState(long STIndex, long NIndex) = 0; 
                    /// get reduce action for state and terminal index
                    /// @param STIndex current state index \>= 0
                    /// @param TIndex current terminal index \>= 0
                    /// @return reduce action \>= 0
    virtual long    getReduceAction(long STIndex, long TIndex) = 0; 
                    /// try early action for state index
                    /// @param STIndex current state index \>= 0
                    /// @param Action [result] reduce action \>= 0
                    /// @return true if a default action exists
    virtual bool    tryEarlyAction(long STIndex, long& Action) = 0; 
                    /// reduce action = error ?
                    /// @param Action reduce action \>= 0
                    /// @return true if action = error
    virtual bool    isErrorAction(long Action) = 0;
                    /// reduce action = accept ?
                    /// @param Action reduce action \>= 0
                    /// @return true if action = accept
    virtual bool    isAcceptAction(long Action) = 0;
                    /// reduce action --> production 
                    /// @param Action reduce action \>= 0
                    /// @param SNIndex current start symbol index \>= 0
                    /// @return production index \>= 0 or -1 
    virtual long    Action2Production(long Action, long SNIndex) = 0;

  };

  //@}

  /* Parser declaration ----------------------------------------------------- */

  /** @addtogroup AbstractParser
      Abstract lalr(1) parser 
  */
  //@{

  /** type of scanned terminal */
  template <class TV /* token value type */> struct StyxToken
  {
    long   Index;   ///< terminal index >= 0 or error terminal
    TV     Value;   ///< token value
    string File;    ///< token file 
    long   Line;    ///< token line  
    long   Column;  ///< token column 
  };

  /** abstract lalr(1) parser template */
  template <class TV /* token value type */, class SV /* stack value type */> 
  class TStyxParser
  {
  public:
    /** number of error messages to skip after the last reported */
    static const int PLR_SKIP_ERRMSG = 3; 

  protected:
    typedef vector<long >    V_long;
    typedef vector<SV* >     V_value;
    typedef StyxToken<TV>    T_Token;

  protected: /** must be set appropiate in derived classes */
    bool                initok;

  protected:
    CStyxParseTableApi* ParseTable; ///< parse table
    long                StartIndex; ///< start symbol index
    V_long              StateStack; ///< state stack
    V_value             ValueStack; ///< value stack 

    /** @name EarlyReductionAttributes 
        attributes related to early reduction 
    */
    //@{
    T_Token          curToken;      ///< current token
    bool             firstToken;    ///< first token (respectively parse) ?
    bool             nextToken;     ///< (read) next token ? 
    //@}

    /** @name ErrorHandlingAttributes 
        attributes related to (panic mode) error handling
    */
    /* Skip: T --> { 1 .. StateStack } X NT  U  { undefined } */ 
    //@{
    V_long           skipTokens;         ///< skip token array
    V_long           skipStates;         ///< skip state array
    V_long           skipNonterminals;   ///< skip nonterminal array
    long             SyntaxErrorCount;   ///< number of syntax errors
    //@}

  protected:
                 /// init parse process 
                 /// @param StartSymbolName start symbol name
                 /// @param State [result] current state index \>= 0
                 /// @return true or false on error
    virtual bool initParse(string StartSymbolName, long& State);
                 /// quit parse process
                 /// @param reset
                 /// = true --\> reset parse process
                 /// else   --\> keep last token (early reduction)
    virtual void quitParse(bool reset=false);
                 /// reset parser
                 /// @return true or false on error
    virtual bool reset();
                 /// remove (temporary) values 
                 /// @param reset
                 /// = true --\> release all values
    virtual void removeValues(bool reset);

                 /// init skip tables 
                 /// @return true --\> try error recovery 
    virtual bool initSkipTables();
                 /// release skip tables
    virtual void quitSkipTables();

                 /// pop n states
                 /// @param n number of states
    virtual void popStates(long n); 
                 /// get & pop the top n values
                 /// @param n number of values
                 /// @param Values [result] values
    virtual bool topValues(long n, V_value& Values);           

                 /// try early reduction 
                 /// @param State [changeable] current state index \>= 0
                 /// @param accept [result]
                 /// = true --\> finish parse process
                 /// @return true or false on error
    virtual bool earlyReduction(long& State, bool& accept); 
                 /// get goto follow state for top state and nonterminal index
                 /// @param NIndex nonterminal index \>= 0
                 /// @return follow state index \>= 0 or PLR_GOTO_ERROR
    virtual long getGoToState(long NIndex);

                 /// (report) internal parser error
                 /// @param Text error message
    virtual void error(string Text);

  protected:
    /** @name AbstractParserMethods
        abstract methods, must be overloaded in derived classes
    */
    //@{
                 /// get next token
                 /// @param Token [result] next token
                 /// @return true or false on error
    virtual bool get(T_Token& Token) = 0;
                 /// shift token
                 /// @param Token current token
                 /// @param Value [result] new stack value
                 /// @return true or false on error
    virtual bool shift(const T_Token& Token, SV*& Value) = 0;   
                 /// reduce production
                 /// @param Index 
                 /// accept || !error --\> Index=production
                 /// else             --\> Index=nonterminal
                 /// @param Values reduction values
                 /// @param accept = true --\> reduce start production
                 /// @param error = true --\> syntax error
                 /// @param Value [result] new stack value
                 /// @return true or false on error
    virtual bool reduce
                 (
                   long Index, V_value& Values, 
                   bool accept, bool error, SV*& Value
                 ) = 0; 
                 /// (report) syntax error
                 /// @param Token current token
    virtual void error(const T_Token& Token) = 0;
    //@}

  public:
    /// The constructor creates and initializes the parser.
    /// @param PTable parse table
    TStyxParser(CStyxParseTableApi* PTable = 0);
    virtual ~TStyxParser();

                 /// set parse table and
                 /// re-init (--> reset) parser
                 /// @param PTable parse table
                 /// @return true or false on error
    virtual bool setParseTable(CStyxParseTableApi* PTable);
                                /// get parse table
                                /// @return parse table
    virtual CStyxParseTableApi* getParseTable(); 

                 /// parse process 
                 /// @param StartSymbolName start symbol name or "" (first start symbol)
                 /// @param early try early reduction
                 /// @return true for a regular parse process (even in the case of syntax errors) 
                 /// or false on (internal) error
    virtual bool parse(string StartSymbolName="", bool early=false);

                 /// get number of syntax errors
                 /// @return number of syntax errors
    virtual long getSyntaxErrorCount();
  };

  /* Parser implementation -------------------------------------------------- */
  
  template <class TV, class SV>
  TStyxParser<TV,SV>::TStyxParser(CStyxParseTableApi* PTable)
  {
    ParseTable = PTable;
    initok = reset();
  }
  
  template <class TV, class SV>
  TStyxParser<TV,SV>::~TStyxParser()
  {
    removeValues(true);
  }
  
  template <class TV, class SV> 
  bool TStyxParser<TV,SV>::reset()
  {
    initok           = ParseTable && ParseTable->initialized();
    SyntaxErrorCount = 0;
    StartIndex       = -1;
    curToken.Index   = -1;
    firstToken       = nextToken = true;
    removeValues(true);
    StateStack.clear();
    skipTokens.clear();
    skipStates.clear();
    skipNonterminals.clear();
    return initok;
  }
  
  template <class TV, class SV> 
  void TStyxParser<TV,SV>::error(string Text)
  {
    fprintf(stderr,"%s\n",Text.c_str());
  }
  
  template <class TV, class SV> 
  bool TStyxParser<TV,SV>::initParse(string StartSymbolName, long& State)
  {
    State = -1;
    SyntaxErrorCount = 0;
    if( initok && ParseTable )
    { long startidx = ParseTable->StartName2Index(StartSymbolName);
      if( StartIndex == -1 )
      {
        removeValues(true);
        StateStack.clear();
        StateStack.push_back(StartIndex=startidx);
      }
      else 
      {
        if( StartIndex != startidx || StateStack.size() == 0 )
          return false;
      }
      State = StateStack[StateStack.size()-1];
      return true;
    }
    return false;
  }
  
  template <class TV, class SV> 
  void TStyxParser<TV,SV>::quitParse(bool reset)
  {
    StartIndex = -1;
    if( reset )
    {
      curToken.Index = -1;
      firstToken     = nextToken = true;
    }
    removeValues(false);
    StateStack.clear();
  }
  
  template <class TV, class SV> 
  bool TStyxParser<TV,SV>::initSkipTables()
  {
    if( initok && ParseTable )
    { long tcnt = ParseTable->getTerminalCount(), 
           scnt = (long)StateStack.size(),
           ncnt = ParseTable->getNonterminalCount();
      for( long i=0; i < tcnt; ++i )
        skipTokens.push_back(-1);
      for( long i=scnt-1; i >= 0; --i )
      {
        for( long j=0; j < ncnt; ++j ) 
        {
          if( ParseTable->isErrorNonterminal(j) )
          { long s = ParseTable->getGoToState(StateStack[i],j);
            if( s != PLR_GOTO_ERROR )
            {
              for( long k=0; k < tcnt; ++k )
              { long p1 = ParseTable->getShiftState(s,k);
                if( p1 != PLR_SHIFT_ERROR && 
                    p1 != PLR_SHIFT_NONE  &&
                    skipTokens[k] == -1L )
                {
                  skipNonterminals.push_back(j);
                  skipStates.push_back(i);
                  skipTokens[k] = (long)skipNonterminals.size()-1;
                }
              }
            }
          }
        }
      }
      if( skipStates.size() > 0 ) return true;
    }
    quitSkipTables();
    return false;
  }
  
  template <class TV, class SV> 
  void TStyxParser<TV,SV>::quitSkipTables()
  {
    skipTokens.clear();
    skipStates.clear();
    skipNonterminals.clear();
  }
  
  template <class TV, class SV> 
  void TStyxParser<TV,SV>::popStates(long n)
  {
    if( ((size_t)n) >= StateStack.size() )
      StateStack.clear();
    else
      for( long i=0; i < n; ++i )
        StateStack.pop_back();
  }
  
  template <class TV, class SV> 
  void TStyxParser<TV,SV>::removeValues(bool reset)
  {
    ValueStack.clear();
  }
  
  template <class TV, class SV> 
  bool TStyxParser<TV,SV>::topValues(long n, V_value& Values)
  {
    if( n < 0 || ((size_t)n) > ValueStack.size() )
      return false;
    for( long cnt = ((long)ValueStack.size()), i=cnt-n; i < cnt; ++i )
    {
      Values.push_back(ValueStack[i]);
    }
    for( long i=0; i < n; ++i )
    {
      ValueStack.pop_back();
    }
    return true;
  }
  
  template <class TV, class SV> 
  bool TStyxParser<TV,SV>::earlyReduction(long& State, bool& accept)
  {
    accept = false;
    if( initok && ParseTable )
    { long res = ParseTable->getErrorAction();
      while( ParseTable->tryEarlyAction(State,res) )
      { V_value Values; SV* val = 0;
        if( !ParseTable->isAcceptAction(res) )
        { long prod = ParseTable->Action2Production(res,StartIndex),
               scnt = ParseTable->getProductionSymbolCount(prod);
          if( !topValues(scnt,Values) ) return false;
          if( !reduce(prod,Values,false,false,val) ) return false;
          popStates(scnt);
          long nidx = ParseTable->NonterminalSymbol2Index
                      (
                        ParseTable->getProductionNonterminal(prod)
                      );
          State = getGoToState(nidx);
          StateStack.push_back(State); ValueStack.push_back(val);
          if( State == PLR_GOTO_ERROR ) return false;
        }
        else
        { long prod = ParseTable->Action2Production(res,StartIndex),
               scnt = ParseTable->getProductionSymbolCount(prod);
          if( !topValues(scnt,Values) ) return false;
          if( !reduce(prod,Values,true,false,val) ) return false;
          accept = true; return true;
        }
      }
      return true;
    }
    return false;
  }
  
  template <class TV, class SV> 
  long TStyxParser<TV,SV>::getGoToState(long NIndex)
  {
    if( initok && ParseTable && StateStack.size() > 0 )
    { 
      return ParseTable->getGoToState(StateStack[StateStack.size()-1],NIndex); 
    }
    return PLR_GOTO_ERROR;
  }
  
  
  template <class TV, class SV> 
  bool TStyxParser<TV,SV>::setParseTable(CStyxParseTableApi* PTable)
  {
    ParseTable = PTable;
    initok = reset();
    if( !initok ) error("reset failed");
    return initok;
  }
  
  template <class TV, class SV> 
  long TStyxParser<TV,SV>::getSyntaxErrorCount()
  {
    return SyntaxErrorCount;
  }
  
  template <class TV, class SV> 
  CStyxParseTableApi* TStyxParser<TV,SV>::getParseTable()
  {
    return ParseTable;
  }
  
  template <class TV, class SV> 
  bool TStyxParser<TV,SV>::parse(string StartSymbolName, bool early)
  {
    if( initok && ParseTable )
    { long cTok = -1, cState = -1, errcnt=0, tokcnt=0; 
      SyntaxErrorCount = 0;
      if( !early || nextToken )
      {
        if( !get(curToken) ) 
        { quitParse(true); return false; }
      }
      cTok = curToken.Index; ++tokcnt;
      if( early && !firstToken && ParseTable->isAcceptTerminal(curToken.Index) )
      {
        quitParse(true); return true;
      }
      if( !initParse(StartSymbolName,cState) )
      { quitParse(true); return false; }
      while( true )
      {
        long action = ParseTable->getShiftState(cState,cTok);
        if( action != PLR_SHIFT_ERROR )
        { SV* val = 0;
          if( !shift(curToken,val) )
          { quitParse(true); return false; }
          if( action != PLR_SHIFT_NONE )
          {
            cState = action;
            StateStack.push_back(cState); ValueStack.push_back(val);
            if( early )
            { bool accept = false;
              if( !earlyReduction(cState,accept) )
              { quitParse(true); return false; }
              if( accept ) 
              {
                firstToken = false; nextToken = true; 
                quitParse(); return true;
              }
            }
          }
          if( !get(curToken) ) 
          { quitParse(true); return false; }
          cTok = curToken.Index; ++tokcnt;
        }
        else
        { 
          action = ParseTable->getReduceAction(cState,cTok);
          long redsym = ParseTable->Action2Production(action,StartIndex);
          if( !ParseTable->isErrorAction(action) &&
              !ParseTable->isAcceptAction(action) )
          { long scnt = ParseTable->getProductionSymbolCount(redsym);
            V_value Values; SV* val = 0;
            if( !topValues(scnt,Values) )
            { quitParse(true); return false; }
            if( !reduce(redsym,Values,false,false,val) )
            { quitParse(true); return false; }
            popStates(scnt);
            long nidx = ParseTable->NonterminalSymbol2Index
                        (
                          ParseTable->getProductionNonterminal(redsym)
                        );
            cState = getGoToState(nidx);
            StateStack.push_back(cState); ValueStack.push_back(val);
            if( cState == PLR_GOTO_ERROR )
            { quitParse(true); return false; }
            if( early )
            { bool accept = false;
              if( !earlyReduction(cState,accept) )
              { quitParse(true); return false; }
              if( accept ) 
              {
                firstToken = nextToken = false; 
                quitParse(); return true;
              }
            }
          }
          else
          {
            if( ParseTable->isAcceptAction(action) &&
                ParseTable->isAcceptTerminal(cTok) )
            { long scnt = ParseTable->getProductionSymbolCount(redsym);
              V_value Values; SV* val = 0;
              if( !topValues(scnt,Values) )
              { quitParse(true); return false; }
              if( SyntaxErrorCount == 0 || scnt == ((long)ValueStack.size()) )
              { 
                if( !reduce(redsym,Values,true,false,val) )
                { quitParse(true); return false; }
              }
              else
              { 
                if( !reduce(redsym,Values,true,true,val) )
                { quitParse(true); return false; }
              }
              firstToken = nextToken = false;
              quitParse(); return true;
            }
            else
    /*ALT
            { V_value Values; SV* val = 0;
              ++SyntaxErrorCount; error(curToken);
              if( !topValues((long)ValueStack.size(),Values) )
              { quitParse(true); return false; }
              if( !reduce(redsym,Values,true,true,val) )
              { quitParse(true); return false; }
              quitParse(true); return true;
            }
    */
    /*NEU*/
            { long p = -1, s = -1, n = -1;
              ++SyntaxErrorCount; 
              if( tokcnt >= errcnt )
              {
                error(curToken); errcnt = tokcnt + PLR_SKIP_ERRMSG;
              }
              if( !early && initSkipTables() )
              {
                while( !ParseTable->isAcceptTerminal(cTok) && 
                       ( cTok < 0 || skipTokens[cTok] == -1L ) )
                { SV* val = 0;
                  if( !shift(curToken,val) )
                  { quitParse(true); return false; }
                  if( cTok < 0 ) 
                    ValueStack.push_back(val);
                  else
                  { long tsym = ParseTable->TerminalIndex2Symbol(cTok);
                    if( ! ParseTable->isComment(tsym) )
                      ValueStack.push_back(val);
                  }
                  if( !get(curToken) ) 
                  { quitParse(true); return false; }
                  cTok = curToken.Index; // cTok < 0 --> continue
                }
                if( cTok < 0 ) /* assertion: cTok >= 0 */
                { quitParse(true); return false; }
                if( !ParseTable->isAcceptTerminal(cTok) )
                {
                  s = skipStates[skipTokens[cTok]];
                  n = skipNonterminals[skipTokens[cTok]];
                }
                quitSkipTables();
              }
              else // quit parsing on first error
                cTok = ParseTable->TokenIndex2TerminalIndex(-1,StartIndex); 
              if( !ParseTable->isAcceptTerminal(cTok) )
              { long vcnt = ((long)ValueStack.size())-(s+1),
                     scnt = ((long)StateStack.size())-(s+1);
                V_value Values; SV* val = 0;
                if( !topValues(vcnt,Values) )
                { quitParse(true); return false; }
                if( !reduce(n,Values,false,true,val) )
                { quitParse(true); return false; }
                popStates(scnt);
                cState = getGoToState(n);
                StateStack.push_back(cState); ValueStack.push_back(val);
                if( cState == PLR_GOTO_ERROR || 
                    ValueStack.size() != StateStack.size() )
                { quitParse(true); return false; }
              }
              else
              { V_value Values; SV* val = 0;
                if( !topValues((long)ValueStack.size(),Values) )
                { quitParse(true); return false; }
                p = ParseTable->Action2Production
                    (
                      ParseTable->getAcceptAction(),StartIndex  
                    );
                if( !reduce(p,Values,true,true,val) )
                { quitParse(true); return false; }
                quitParse(true); return true;
              }
            }
    /**/
          }
        }
      }
    }
    error("parser not initialized");
    return false;
  }

  //@}

  //@}

  //@}

}

#endif
