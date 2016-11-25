/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxGrammar.cs]    Styx CFG Type definitions (C#)                       */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2009 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

using System;
using System.Text;
using System.IO;
using System.Collections;


/** @file
    CFG Type definitions and functions
*/

/** @namespace styx
    C# Scanner & parser library and modules
*/

namespace styx
{

  /** @addtogroup StyxLibraryCS
      C# Scanner & parser library
  */
  //@{

  /** @addtogroup StyxGrammar
      CFG Type definitions and functions
  */
  //@{

  /** CFG Type definitions and functions */
  public class StyxGrammar
  {
  
    /** CFG symbol type */
    public enum EStyxCfgSymType
    {
      CFG_TYP_NTM = 0, //!< nonterminal
      CFG_TYP_TOK = 1, //!< token
      CFG_TYP_KEY = 2, //!< keyword
      CFG_TYP_WKY = 3, //!< unicode keyword
      CFG_TYP_CFG = 4, //!< language token
      CFG_TYP_COM = 5  //!< comment
    }
  
    /* Terminal <--> Comment -------------------------------------------------*/
  
    /** @addtogroup SymbolTypeConverter
        Terminal <--> Comment 
    */
    //@{
    
    /** convert terminal type to comment type
        @param type terminal type
        @return comment type
    */
    public static short terminal2comment(short type)
    {
      return (short)(type + (short)EStyxCfgSymType.CFG_TYP_COM);
    }

    /** convert comment type to terminal type
        @param type comment type
        @return terminal type
    */
    public static short comment2terminal(short type)
    {
      return (short)(type - (short)EStyxCfgSymType.CFG_TYP_COM);
    }
  
    //@}
  
    /* Symbol Recognizer -----------------------------------------------------*/

    /** @addtogroup SymbolTypeRecognizer
        Symbol type recognizer
    */
    //@{
    
    /** symbol type = nonterminal ?
        @param type symbol type
        @return true for a nonterminal type
    */
    public static bool isNonterminal(short type)
    {
      return type == (short)EStyxCfgSymType.CFG_TYP_NTM;
    }
  
    /** symbol type = embedded language ?
        @param type symbol type
        @return true for an embedded language type
    */
    public static bool isEmbeddedLanguage(short type)
    {
      return type == (short)EStyxCfgSymType.CFG_TYP_CFG;
    }
  
    /** symbol type = token ?
        @param type symbol type
        @return true for a token type
    */
    public static bool isToken(short type)
    {
      return type == (short)EStyxCfgSymType.CFG_TYP_TOK 
          || type == (short)EStyxCfgSymType.CFG_TYP_CFG;
    }
  
    /** symbol type = keyword ?
        @param type symbol type
        @return true for a keyword type
    */
    public static bool isKeyword(short type)
    {
      return type == (short)EStyxCfgSymType.CFG_TYP_KEY 
          || type == (short)EStyxCfgSymType.CFG_TYP_WKY;
    }
  
    /** symbol type = unicode keyword ?
        @param type symbol type
        @return true for a unicode keyword type
    */
    public static bool isUnicodeKeyword(short type)
    {
      return type == (short)EStyxCfgSymType.CFG_TYP_WKY;
    }
  
    /** symbol type = comment ?
        @param type symbol type
        @return true for a comment type
    */
    public static bool isComment(short type)
    {
      return type >= (short)EStyxCfgSymType.CFG_TYP_COM;
    }
  
    /** symbol type = token or nonterminal ?
        @param type symbol type
        @return true for a token or nonterminal type
    */
    public static bool isTokenNonterminal(short type)
    {
      return isToken(type) || isNonterminal(type);
    }
  
    /** symbol type = token or keyword ?
        @param type symbol type
        @return true for a token or keyword type
    */
    public static bool isTokenKeyword(short type)
    {
      return isToken(type) || isKeyword(type);
    }
  
    /** symbol type = token, keyword or accept symbol ?
        @param type symbol type
        @return true for a terminal type
    */
    public static bool isTerminal(short type)
    {
      return isTokenKeyword(type) ||
             ( isComment(type) && type != (short)EStyxCfgSymType.CFG_TYP_COM );
    }
  
    //@}

  
    /* Production Recognizer -------------------------------------------------*/
  
    /** @addtogroup ProductionRecognizer
        Production types: special recognizer
    */
    //@{
    
    /** production name = "nil" ? 
        @param prod production name
        @return true for a nil production
    */
    public static bool isNilProduction(string prod)
    /* production name = "nil" ? */
    {
      return( "nil" == prod );
    }
    
    /** production name = "cons" ? 
        @param prod production name
        @return true for a cons production
    */
    public static bool isConsProduction(string prod)
    /* production name = "cons" ? */
    {
      return( "cons" == prod );
    }
    
    /** production name = "ign#*" ? 
        @param prod production name
        @return true for an ignore production
    */
    public static bool isIgnProduction(string prod)
    /* production name = "ign#*" ? */
    {
      return( prod.Length >= 4 && "ign" == prod.Substring(0,3) && Char.IsDigit(prod[3]) );
    }
  
    //@}

  }

  //@}

  //@}

}

