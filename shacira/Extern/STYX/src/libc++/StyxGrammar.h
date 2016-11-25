/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxGrammar.h]    Styx CFG Type definitions (C++)                       */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2004 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_GRAMMAR_INCL
#define STYX_GRAMMAR_INCL

#include <string.h>
#include <string>

/** @file
    CFG Type definitions and functions
*/

/** @namespace styx
    C++ Scanner & parser library and modules
*/
namespace styx
{
  using namespace std;

  /** @addtogroup StyxLibraryCPP
      C++ Scanner & parser library
  */
  //@{

  /** @addtogroup StyxGrammar
      CFG Type definitions and functions
  */
  //@{

  /** CFG symbol type */
  enum EStyxCfgSymType
  {
    CFG_TYP_NTM = 0, ///< nonterminal
    CFG_TYP_TOK = 1, ///< token
    CFG_TYP_KEY = 2, ///< keyword
    CFG_TYP_WKY = 3, ///< unicode keyword
    CFG_TYP_CFG = 4, ///< language token
    CFG_TYP_COM = 5  ///< comment
  };
  
  /** @addtogroup SymbolTypeConverter
      Terminal <--> Comment 
  */
  //@{
  
  /** convert terminal type to comment type
      @param type terminal type
      @return comment type
  */
  short terminal2comment(short type);
  /** convert comment type to terminal type
      @param type comment type
      @return terminal type
  */
  short comment2terminal(short type);
  
  //@}


  /** @addtogroup SymbolTypeRecognizer
      Symbol type recognizer
  */
  //@{
  
  /** symbol type = nonterminal ?
      @param type symbol type
      @return true for a nonterminal type
  */
  bool isNonterminal(short type);
  /** symbol type = embedded language ?
      @param type symbol type
      @return true for an embedded language type
  */
  bool isEmbeddedLanguage(short type);
  /** symbol type = token ?
      @param type symbol type
      @return true for a token type
  */
  bool isToken(short type);
  /** symbol type = keyword ?
      @param type symbol type
      @return true for a keyword type
  */
  bool isKeyword(short type);
  /** symbol type = unicode keyword ?
      @param type symbol type
      @return true for a unicode keyword type
  */
  bool isUnicodeKeyword(short type);
  /** symbol type = comment ?
      @param type symbol type
      @return true for a comment type
  */
  bool isComment(short type);
  
  /** symbol type = token or nonterminal ?
      @param type symbol type
      @return true for a token or nonterminal type
  */
  bool isTokenNonterminal(short type);
  /** symbol type = token or keyword ?
      @param type symbol type
      @return true for a token or keyword type
  */
  bool isTokenKeyword(short type);
  /** symbol type = token, keyword or accept symbol ?
      @param type symbol type
      @return true for a terminal type
  */
  bool isTerminal(short type);
  
  //@}
  
  
  /** @addtogroup ProductionRecognizer
      Production types: special recognizer
  */
  //@{
  
  /** production name = "nil" ? 
      @param prod production name
      @return true for a nil production
  */
  bool isNilProduction(string prod);
  
  /** production name = "cons" ? 
      @param prod production name
      @return true for a cons production
  */
  bool isConsProduction(string prod);
  
  /** production name = "ign#*" ? 
      @param prod production name
      @return true for an ignore production
  */
  bool isIgnProduction(string prod);

  //@}

  //@}

  //@}
}

#endif
