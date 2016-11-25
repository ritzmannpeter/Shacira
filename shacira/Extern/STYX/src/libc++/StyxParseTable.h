/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxParseTable.h]   Styx Parse Table Implementation (C++)               */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2005 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_PARSETABLE_INCL
#define STYX_PARSETABLE_INCL


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "StyxString.h"
#include "StyxGrammar.h"
#include "StyxParser.h"

/** @file
    Styx parse table
*/


namespace styx
{
  using namespace std;

  /** @addtogroup StyxLibraryCPP
      C++ Scanner & parser library
  */
  //@{

  /** @addtogroup StyxParseTable
      Styx parse table
  */
  //@{


  /* Parse Table ---------------------------------------------------------- */

  /// production 
  struct StyxProduction
  {
    typedef vector<long > V_long;

    string   PName;   ///< production name
    short    Method;  ///< production layout hint
                      ///< @link CStyxParseTable#EStyxProdLayout (--\> definition) @endlink
    long     NtId;    ///< production nonterminal ( left side )
    V_long   Symbols; ///< production symbols ( tokens incl. keywords, nonterminals )
    V_long   SymFrms; ///< production symbol layout hints
  };

  /// parse table
  class CStyxParseTable : public CStyxParseTableApi
  {
  public:

    /** production layout hint
        @anchor ref-productionlayout
    */
    enum EStyxProdLayout
    {
      PLR_PRD_DFT = 0, ///< default   production 
      PLR_PRD_REC = 1, ///< recursive production
      PLR_PRD_GRP = 2, ///< group     production
      PLR_PRD_NON = 3  ///< ... end of definition
    };

  public:
    typedef pair<long, long >       plong;
    typedef vector<plong >          V_plong;

  protected:
    typedef vector<string>          V_string;
    typedef vector<long  >          V_long;
    typedef vector<short >          V_short;
    typedef vector<bool  >          V_bool;
    typedef vector<StyxProduction > V_styxprod;

  protected:
    bool       initok;   ///< parse table import result
    string     Name;     ///< language short name
    long       TkCnt;    ///< number of tokens incl. keywords 
    long       NtCnt;    ///< number of nonterminals 
    V_string   SNames;   ///< external token and nonterminal names
                         ///< \n [tokens + nonterminals] --\> symbol names
    V_long     StartIds; ///< start symbol indexes
                         ///< (1.index: CFG start symbol)
    V_short    TokKind;  ///< token types
                         ///< @link #EStyxCfgSymType (--\> definition) @endlink
    V_long     NtClass;  ///< nonterminal classes
                         ///< \n [nonterminals] --\> nonterminal (class) indexes
    V_bool     ErrorNt;  ///< [nonterminals] --\> restart parsing ?
    V_styxprod Products; ///< productions
    V_long     MstShift; ///< master shift table
                         ///< \n [states] --\> -1 or DtlShift index of the first token
    V_long     DtlShift; ///< detail shift table
                         ///< \n [shift states] --\> 
                         ///<    ( - first follow state index+1, , - last follow state index+1,
                         ///<      last token index, , first token index )
    V_long     GoTo;     ///< master goto table 
                         ///< \n [nonterminals] --\> -1 or GoToDft index of the first follow state
    V_long     GoToDft;  ///< detail goto table   
                         ///< \n [state nonterminals] --\> 
                         ///< \n ( default follow state index+1+states { - from state index+1 } )
                         ///< \n or
                         ///< \n { follow state index+1+states { from state index+1 } }
    V_long     ActDft;   ///< default action table
                         ///< \n [states] --\> default action (accept,reduce,error) or
                         ///<    negative ActExp index to the first action
    V_long     ActExp;   ///< look-ahead based action table 
                         ///< \n [states with look-ahead based actions] --\> rotational +/-
                         ///<    { offset+accept or reduce action { look-ahead token index+1 } }

  protected:
                 /// reset parse table
    virtual void reset();
                 /// (report) parse table error
                 /// @param Text error message
    virtual void error(string Text); 

    /** @name ImportParseTable
        parse table import and validation
    */
    //@{
                 /// set language name
                 /// @param Language language name
    virtual void setLanguage(string Language);
                 /// set number of tokens incl. keywords
                 /// @param TCount number of tokens incl. keywords
    virtual void setTokenCount(long TCount);
                 /// set number of nonterminals
                 /// @param NCount number of nonterminals
    virtual void setNonterminalCount(long NCount);
                 /// add token or nonterminal name
                 /// ( order: tokens, nonterminals )
                 /// @param SName external token or nonterminal name
    virtual void addCfgSymbol(string SName);
                 /// add start symbol
                 /// @param SNSymbol start symbol symbol \>= 0
    virtual void addStartSymbol(long SNSymbol);
                 /// add token type
                 /// @param TType
                 ///< @link #EStyxCfgSymType (--\> definition) @endlink
                 /// @return true or false on error
    virtual bool addTokenType(short TType);
                 /// add nonterminal class
                 /// @param NIndex nonterminal index \>= 0
    virtual void addNonterminalClass(long NIndex);
                 /// add a restart parsing hint for a nonterminal
                 /// @param Reparse restart parsing ?
    virtual void addErrorNonterminal(bool Reparse);
                 /// add a new uninitialized production
                 /// @param Production the new production
    virtual void addProduction(const StyxProduction& Production);
                 /// set the name of the current production
                 /// @param PName production name
                 /// @return true or false on error
    virtual bool setProductionName(string PName);
                 /// set the layout hint of the current production
                 /// @param PMethod production layout hint
                 ///< @link CStyxParseTable#EStyxProdLayout (--\> definition) @endlink
                 /// @return true or false on error
    virtual bool setProductionMethod(short PMethod);
                 /// set the nonterminal of the current production
                 /// @param PNSymbol nonterminal symbol \>= 0
                 /// @return true or false on error
    virtual bool setProductionNonterminal(long PNSymbol);
                 /// add a member (token incl. keyword, nonterminal) 
                 /// to the current production
                 /// @param PMSymbol member symbol \>= 0
                 /// @return true or false on error
    virtual bool addProductionSymbol(long PMSymbol);
                 /// add a member layout hint to the current production
                 /// @param PMLayout member layout hint
                 /// @return true or false on error
    virtual bool addProductionLayout(long PMLayout);

                 /// add master shift value
                 /** @param Entry 
                     @link CStyxParseTable#MstShift master shift value @endlink 
                 */
    virtual void addMstShiftEntry(long Entry);
                 /// add detail shift value
                 /** @param Entry 
                     @link CStyxParseTable#DtlShift detail shift value @endlink 
                 */
    virtual void addDtlShiftEntry(long Entry);
                 /// add master goto value
                 /** @param Entry 
                     @link CStyxParseTable#GoTo master goto value @endlink 
                 */
    virtual void addGoToEntry(long Entry);
                 /// add detail goto value
                 /** @param Entry 
                     @link CStyxParseTable#GoToDft detail goto value @endlink 
                 */
    virtual void addGoToDftEntry(long Entry);
                 /// add default action value
                 /** @param Entry 
                     @link CStyxParseTable#ActDft default action value @endlink 
                 */
    virtual void addActDftEntry(long Entry);
                 /// add look-ahead based action value
                 /** @param Entry 
                     @link CStyxParseTable#ActExp look-ahead based action value @endlink 
                 */
    virtual void addActExpEntry(long Entry);

                 /// import next parse table line
                 /// @param line [update] current source line
                 /// @param object [result] current resource identifier
                 /// @return true or false on error
    virtual bool loadTableLine(string& line, string& object);
                 /// check parse table
                 /// @return true for a valid parse table
    virtual bool checkLoad();
    //@}

                 /// get action offset 
                 /// @return action offset \>= 0 or -1
    virtual long getActionOffset(); 

  public:
    /// The constructor creates an uninitialized parse table.
    CStyxParseTable();
    virtual ~CStyxParseTable();
  
    /** @name AbstractParseTableAPI
        abstract parse table interface
    */
    //@{
                    // parse table is initialized ?
    virtual bool    initialized();

                    // get language
    virtual string  getLanguage();

                    // get number of tokens
    virtual long    getTokenCount();
                    // get number of nonterminals
    virtual long    getNonterminalCount();
                    // get number of symbols 
                    // (tokens, nonterminals, start symbols)
    virtual long    getSymbolCount();
                    // get number of start symbols
    virtual long    getStartSymbolCount();
                    // get number of terminals (tokens, accept token)
    virtual long    getTerminalCount();
                    // get number of meta symbols (nonterminals, start symbols)
    virtual long    getMetaSymbolCount();

                    // token index --> terminal index >= 0 or -1 (error)
                    // token index >= 0 or EOF = -1 or error = -2
                    // (SNIndex = current start symbol index)
    virtual long    TokenIndex2TerminalIndex(long TKIndex, long SNIndex);

                    // accept terminal ?
                    // terminal index >= 0 or -1 (error) 
    virtual bool    isAcceptTerminal(long TIndex);
                    // terminal index --> symbol
                    // terminal index >= 0 or -1 (error) 
    virtual long    TerminalIndex2Symbol(long TIndex);
                    // terminal symbol --> index
    virtual long    TerminalSymbol2Index(long TSymbol);

                    // start symbol index --> symbol
    virtual long    StartIndex2Symbol(long SNIndex);
                    // start symbol symbol --> index
    virtual long    StartSymbol2Index(long SNSymbol);
                    // start symbol name --> index
    virtual long    StartName2Index(string StartSymbolName="");

                    // nonterminal index --> symbol
    virtual long    NonterminalIndex2Symbol(long NIndex);
                    // nonterminal symbol --> index
    virtual long    NonterminalSymbol2Index(long NSymbol);
                    // error (recovery) nonterminal ?
    virtual bool    isErrorNonterminal(long NIndex);

                    // nonterminal ?
    virtual bool    isNonterminal(long Symbol);
                    // regular token class ?
    virtual bool    isToken(long Symbol);
                    // comment token ?
    virtual bool    isComment(long Symbol);
                    // (single byte or unicode) keword ?
    virtual bool    isKeyword(long Symbol);
                    // get symbol name
    virtual string  getSymbolName(long Symbol);

                    // get number of productions
    virtual long    getProductionCount();
                    // get production name
    virtual string  getProductionName(long PIndex);
                    // get production nonterminal
    virtual long    getProductionNonterminal(long PIndex);
                    // get number of production member symbols
    virtual long    getProductionSymbolCount(long PIndex);
                    // get production member symbol
    virtual long    getProductionSymbol(long PIndex, long PMIndex);

                    // get number of states
    virtual long    getStateCount();
                    // get error action
    virtual long    getErrorAction();
                    // get accept action
    virtual long    getAcceptAction();
                    // get shift follow state for state and terminal index
    virtual long    getShiftState(long STIndex, long TIndex); 
                    // get goto follow state for state and nonterminal index
    virtual long    getGoToState(long STIndex, long NIndex); 
                    // get reduce action for state and terminal index
    virtual long    getReduceAction(long STIndex, long TIndex); 
                    // try early action for state index,
                    // returns true if a default action exists
    virtual bool    tryEarlyAction(long STIndex, long& Action); 
                    // reduce action = error ?
    virtual bool    isErrorAction(long Action);
                    // reduce action = accept ?
    virtual bool    isAcceptAction(long Action);
                    // reduce action --> production 
                    // (SNIndex = current start symbol index)
    virtual long    Action2Production(long Action, long SNIndex);
    //@}

    /** @name StyxParseTableAPI
        Styx parse table interface
    */
    //@{
                    /// import parse table from file 
                    /// @param Path path to the exported parse table 
                    /// @return true --> initialized parse table or false on error
    virtual bool    loadTableFile(string Path);
                    /// import parse table from string 
                    /// @param Table exported parse table 
                    /// @return true --> initialized parse table or false on error
    virtual bool    loadTableString(string Table);

                    /// nonterminal index --\> class
                    /// @param NIndex nonterminal index \>= 0
                    /// @return nonterminal class (index) \>= 0 or -1 
    virtual long    NonterminalIndex2Class(long NIndex);

                    /// get symbol type
                    /// @param Symbol CFG symbol \>= 0
                    /// @return symbol type or -1
                    /// @link #EStyxCfgSymType (--\> definition) @endlink
    virtual short   getSymbolType(long Symbol);
                    /// unicode keword ?
                    /// @param Symbol CFG symbol \>= 0
                    /// @return true for a unicode keyword
    virtual bool    isUnicodeKeyword(long Symbol);

                    /// get production layout hint
                    /// @param PIndex production index \>= 0
                    /// @return production layout hint or -1
                    /// @link CStyxParseTable#EStyxProdLayout (--\> definition) @endlink
    virtual short   getProductionMethod(long PIndex);
                    /// get production member layout hint
                    /// @param PIndex production index \>= 0
                    /// @param PMIndex production member index \>= 0
                    /// @return production member layout hint or -1
    virtual long    getProductionLayout(long PIndex, long PMIndex);

                    /// get number of master shift values
                    /// @return number of master shift values or -1
    virtual long    getMstShiftCount();
                    /// get master shift value
                    /** @param Index 
                        @link CStyxParseTable#MstShift master shift table @endlink 
                        respectively state index \>= 0
                    */
                    /// @return master shift value or -1
    virtual long    getMstShiftEntry(long Index);
                    /// get number of detail shift values
                    /// @return number of detail shift values or -1
    virtual long    getDtlShiftCount();
                    /// get detail shift value
                    /** @param Index 
                        @link CStyxParseTable#DtlShift detail shift table @endlink 
                        index \>= 0
                    */
                    /// @return detail shift value or -1
    virtual long    getDtlShiftEntry(long Index);
                    /// get number of master goto values
                    /// @return number of master goto values or -1
    virtual long    getGoToCount();
                    /// get master goto value
                    /** @param Index 
                        @link CStyxParseTable#GoTo goto master table @endlink 
                        respectively nonterminal index \>= 0
                    */
                    /// @return goto master value or -1
    virtual long    getGoToEntry(long Index);
                    /// get number of detail goto values
                    /// @return number of detail goto values or -1
    virtual long    getGoToDftCount();
                    /// get detail goto value
                    /** @param Index 
                        @link CStyxParseTable#GoToDft goto detail table @endlink 
                        index \>= 0
                    */
                    /// @return goto detail value or -1
    virtual long    getGoToDftEntry(long Index);
                    /// get number of default action values
                    /// @return number of default action values or -1
    virtual long    getActDftCount();
                    /// get default action value
                    /** @param Index 
                        @link CStyxParseTable#ActDft default action table @endlink 
                        respectively state index \>= 0
                    */
                    /// @return default action value or -1
    virtual long    getActDftEntry(long Index);
                    /// get number of look-ahead based action values
                    /// @return number of look-ahead based action values or -1
    virtual long    getActExpCount();
                    /// get look-ahead based action value
                    /** @param Index 
                        @link CStyxParseTable#ActExp look-ahead based action table @endlink 
                        index \>= 0
                    */
                    /// @return look-ahead based action value or -1
    virtual long    getActExpEntry(long Index);

                    /// get shift values 
                    /// { token, follow state } for a state
                    /// @param STIndex state index \>= 0
                    /// @param Values [result] shift values
                    /// @return true or false on error
    virtual bool    getShiftValues(long STIndex, V_plong& Values);
                    /// get goto values 
                    /// { follow state, from state } for a nonterminal
                    /// @param NIndex nonterminal index \>= 0
                    /// @param Values [result] goto values
                    /// @return true or false on error
    virtual bool    getGoToValues(long NIndex, V_plong& Values);
                    /// get action values 
                    /// { error=-2|accept=-1|production, terminal|-1 } for a state
                    /// @param STIndex state index \>= 0
                    /// @param Values [result] action values
                    /// @return true or false on error
    virtual bool    getActionValues(long STIndex, V_plong& Values);
    //@}

  };

  //@}

  //@}

}


#endif
