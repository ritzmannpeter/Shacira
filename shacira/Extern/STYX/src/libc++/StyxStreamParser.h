/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxStreamParser.h]   Styx Stream Parser Implementation (C++)           */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2005 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_STREAMPARSER_INCL
#define STYX_STREAMPARSER_INCL


#include <wctype.h>
#include <string>
#include <vector>
#include <map>

#include "StyxString.h"
#include "StyxGrammar.h"
#include "StyxScanner.h"
#include "StyxParseTable.h"

/** @file
    Abstract Styx stream parser
*/


namespace styx
{
  using namespace std;

  /** @addtogroup StyxLibraryCPP
      C++ Scanner & parser library
  */
  //@{

  /** @addtogroup StyxStreamParser
      Abstract Styx stream parser
  */
  //@{

  const char* PLR_TOK_Other  = "_other_"; ///< other token
  const char* PLR_TOK_Error  = "[other]"; ///< error token
  const char* PLR_TOK_Accept = "[EOF]";   ///< accept token

  /* Parser declaration --------------------------------------------------- */

  /// abstract stream parser template
  template <class TC /* token character type */, class SV /* stack value type */> 
  class TStyxStreamParser : public TStyxParser<basic_string<TC>,SV>
  {
  protected:
    typedef basic_string<TC >      tstring;
    typedef StyxToken<tstring >    T_Token;
    typedef map<string,long>       M_string2long;
    typedef map<tstring,long>      M_tstring2long;
    typedef map<wstring,long>      M_wstring2long;

  protected:
    CStyxScanner*       Scanner;     ///< Styx scanner (token stream)
    M_string2long       TokenMap;    ///< external token name --\> token symbol
    M_tstring2long      KeywordMap;  ///< keyword             --\> token symbol
    M_tstring2long      NormKeyMap;  ///< normalized keyword  --\> token symbol

  protected:
                 /// internal token name --> external token name, index
                 /// @param tok [update] internal (--\> external) token name
                 /// @param idx [result] token index \>= 0 
                 /// or -1 (accept token) or -2 (error/other token)
                 /// @result true or false on error
    virtual bool getTokenIndex(string& tok, long& idx); 
                 // get next token (success=true)
    virtual bool get(T_Token& Token);
                 // syntax error
    virtual void error(const T_Token& Token);
                 // internal parser error
    virtual void error(string Text);
                 // reset parser (success=true)
    virtual bool reset();

  public:
    /// The constructor creates and initializes the stream parser.
    /// @param PTable Styx parse table
    /// @param TStream Styx scanner
    TStyxStreamParser(CStyxParseTable* PTable = 0, CStyxScanner* TStream = 0);
    virtual ~TStyxStreamParser();

                 /// set token stream and
                 /// re-init (--> reset) parser, if necessary
                 /// @param TStream token stream (Styx scanner)
                 /// @result true or false on error
    virtual bool setTokenStream(CStyxScanner* TStream);
                          /// get token stream
                          /// @return token stream (Styx scanner)
    virtual CStyxScanner* getTokenStream();
  };

  /// abstract single byte stream parser template
  template<class SV> class TStyxStreamParserS : public TStyxStreamParser<char,SV>
  {
  public:
    /// The constructor creates and initializes the parser.
    /// @param PTable Styx parse table
    /// @param TStream Styx scanner
    TStyxStreamParserS(CStyxParseTable* PTable = 0, CStyxScanner* TStream = 0)
    : TStyxStreamParser<char,SV>(PTable,TStream)
    {}
    virtual ~TStyxStreamParserS() {}
  };

  /// abstract unicode stream parser template
  template<class SV> class TStyxStreamParserU : public TStyxStreamParser<wchar_t,SV>
  {
  public:
    /// The constructor creates and initializes the parser.
    /// @param PTable Styx parse table
    /// @param TStream Styx scanner
    TStyxStreamParserU(CStyxParseTable* PTable = 0, CStyxScanner* TStream = 0)
    : TStyxStreamParser<wchar_t,SV>(PTable,TStream)
    {}
    virtual ~TStyxStreamParserU() {}
  };


  /* Parser implementation ------------------------------------------------ */
  
  template <class TC, class SV> 
  TStyxStreamParser<TC,SV>::TStyxStreamParser(CStyxParseTable* PTable, CStyxScanner* TStream)
  : TStyxParser<tstring,SV>(PTable)
  {
    Scanner = TStream;
    this->initok = reset();
  }
  
  template <class TC, class SV> 
  TStyxStreamParser<TC,SV>::~TStyxStreamParser()
  {
  }
  
  template <class TC, class SV> 
  bool TStyxStreamParser<TC,SV>::reset()
  { 
    this->initok = TStyxParser<tstring,SV>::reset();
    TokenMap.clear();
    KeywordMap.clear();
    NormKeyMap.clear();
    bool unicode = ( sizeof(TC) != sizeof(char) );
    this->initok &= Scanner == 0 || 
                    ( Scanner->initialized() && unicode == Scanner->unicode() );
    if( !this->initok ) return false;
    for( size_t i = 0, cnt = this->ParseTable->getTokenCount(); i < cnt; ++i )
    { long  tidx = this->ParseTable->TokenIndex2TerminalIndex((long)i,this->StartIndex),
            tsym = this->ParseTable->TerminalIndex2Symbol(tidx);
      short type = ((CStyxParseTable*)this->ParseTable)->getSymbolType(tsym);
      if( !isKeyword(type) )
      {
//cout << "Token: " << tidx << ":" << this->ParseTable->getSymbolName(tsym).c_str() << "\n";
        TokenMap[this->ParseTable->getSymbolName(tsym)] = tidx;
      }
      else
      if( unicode )
      { wstring key = multibyte2unicode(this->ParseTable->getSymbolName(tsym));
        M_wstring2long* kmap = (M_wstring2long*)&KeywordMap, 
                      *nkmap = (M_wstring2long*)&NormKeyMap;
        (*kmap)[key] = tidx;
        (*nkmap)[string2lower(key)] = tidx;
      }
      else
      if( !isUnicodeKeyword(type) )
      { M_string2long* kmap = (M_string2long*)&KeywordMap, 
                     *nkmap = (M_string2long*)&NormKeyMap;
//cout << "Keyword: " << tidx << ":" << this->ParseTable->getSymbolName(tsym).c_str() << "\n";
        (*kmap)[this->ParseTable->getSymbolName(tsym)] = tidx;
        (*nkmap)[string2lower(this->ParseTable->getSymbolName(tsym))] = tidx;
      }
  /*
      else 
      {
        this->initok = false; return false;
      }
  */
    }
    TokenMap[PLR_TOK_Accept] = -1;
    if( TokenMap.find(PLR_TOK_Other) != TokenMap.end() )
    {
      TokenMap[PLR_TOK_Error] = TokenMap[PLR_TOK_Other];
    }
    else
    {
      TokenMap[PLR_TOK_Error] = -2;
      TokenMap[PLR_TOK_Other] = -2;
    }
    return this->initok;
  }
  
  template <class TC, class SV> 
  bool TStyxStreamParser<TC,SV>::getTokenIndex(string& tok, long& idx)
  { M_string2long::iterator pos = TokenMap.find(tok);
    pos = TokenMap.find(tok);
    if( pos != TokenMap.end() )
      idx = (*pos).second;
    else
    {
      tok = Scanner->externalTokenID(tok);
      pos = TokenMap.find(tok);
      if( pos != TokenMap.end() )
        idx = (*pos).second;
      else
      {
         error(string("invalid tokenID '")+tok+string("'"));
         return false;
      }
    }
    return true;
  }
  
  template <class TC, class SV> 
  bool TStyxStreamParser<TC,SV>::get(T_Token& Token)
  {
    if( this->initok && Scanner && this->ParseTable )
    { string  tok; 
      tstring val;
      if( !Scanner->nextToken() || !Scanner->currentToken(tok,val) )
      {
        error("get next token failed");
        return false;
      }
      Token.File   = Scanner->getFile();
      Token.Line   = Scanner->getLine();
      Token.Column = Scanner->getCol();
      Token.Value  = val;
      if( Scanner->ignoreCase() )
      { typename M_tstring2long::iterator pos = NormKeyMap.find(val);
        if( pos == NormKeyMap.end() )
        {
          if( !getTokenIndex(tok,Token.Index) )
            return false;
        }
        else Token.Index = (*pos).second;
      }
      else
      { typename M_tstring2long::iterator pos = KeywordMap.find(val);
        if( pos == KeywordMap.end() )
        {
          if( !getTokenIndex(tok,Token.Index) )
            return false;
        }
        else Token.Index = (*pos).second;
      }
      if( Token.Index == -1 ) 
        Token.Index = this->ParseTable->TokenIndex2TerminalIndex(-1,this->StartIndex);
      if( Token.Index == -2 ) Token.Index = -1;
      return true;
    }
    if( Scanner == 0 ) error("invalid token stream");
    return false;
  }
  
  template <class TV, class SV> 
  void TStyxStreamParser<TV,SV>::error(string Text)
  {
    fprintf(stderr,"%s\n",Text.c_str());
  }
  
  template <class TC, class SV> 
  void TStyxStreamParser<TC,SV>::error(const T_Token& Token)
  { bool unicode = ( sizeof(TC) != sizeof(char) );
    cerr << Token.File << "(" << Token.Line << "," << Token.Column 
         << ") : syntax error (token '";
    if( !unicode )
      fprintf(stderr,"%s",(char*)Token.Value.c_str());
    else
      fprintf(stderr,"%S",(wchar_t*)Token.Value.c_str());
    cerr << "')\n";
  }
  
  template <class TC, class SV> 
  bool TStyxStreamParser<TC,SV>::setTokenStream(CStyxScanner* TStream)
  {
    Scanner = TStream;
    if( !this->initok )
    {
      this->initok = reset();
      if( this->initok ) return true;
    }
    bool unicode = ( sizeof(TC) != sizeof(char) );
    bool result  = Scanner == 0 || 
                   ( Scanner->initialized() && unicode == Scanner->unicode() );
    this->initok &= result;
    if( !result ) error("invalid token stream");
    return result;
  }
  
  template <class TV, class SV> 
  CStyxScanner* TStyxStreamParser<TV,SV>::getTokenStream()
  {
    return Scanner;
  }

  //@}

  //@}
  
}

#endif
