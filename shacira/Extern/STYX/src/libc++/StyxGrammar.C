/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxGrammar.C]    Styx CFG Type definitions (C++)                       */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2004 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "StyxGrammar.h"


namespace styx
{

  /* Terminal <--> Comment -------------------------------------------------*/

  short terminal2comment(short type)
  {
    return type + CFG_TYP_COM;
  }

  short comment2terminal(short type)
  {
    return type - CFG_TYP_COM;
  }

  /* Symbol Recognizer -----------------------------------------------------*/

  bool isNonterminal(short type)
  {
    return type == CFG_TYP_NTM;
  }

  bool isEmbeddedLanguage(short type)
  {
    return type == CFG_TYP_CFG;
  }

  bool isToken(short type)
  {
    return type == CFG_TYP_TOK || type == CFG_TYP_CFG;
  }

  bool isKeyword(short type)
  {
    return type == CFG_TYP_KEY || type == CFG_TYP_WKY;
  }

  bool isUnicodeKeyword(short type)
  {
    return type == CFG_TYP_WKY;
  }

  bool isComment(short type)
  {
    return type >= CFG_TYP_COM;
  }

  bool isTokenNonterminal(short type)
  {
    return isToken(type) || isNonterminal(type);
  }

  bool isTokenKeyword(short type)
  {
    return isToken(type) || isKeyword(type);
  }

  bool isTerminal(short type)
  {
    return isTokenKeyword(type) ||
           ( isComment(type) && type != CFG_TYP_COM );
  }


  /* Production Recognizer -------------------------------------------------*/

  bool isNilProduction(string prod)
  /* production name = "nil" ? */
  {
    return( "nil" == prod );
  }
  
  bool isConsProduction(string prod)
  /* production name = "cons" ? */
  {
    return( "cons" == prod );
  }
  
  bool isIgnProduction(string prod)
  /* production name = "ign#*" ? */
  {
    return( prod.length() >= 4 && ! strncmp("ign",prod.c_str(),3) && isdigit(prod[3]) );
  }

}

