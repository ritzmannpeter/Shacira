/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [cfg_dfn.c]       Context Free Grammar: symbol and production types        */
/*                                                                            */
/* Copyright (c) 1993 by Doelle, Manns                                        */
/*----------------------------------------------------------------------------*/

#include "standard.h"

/*I----------------------- Symbol types ------------------------------------- */

/*DOC_INTERFACE_COPY_ON*/

#define PLR_TYP_NTM  0 /* Nonterminal       */
#define PLR_TYP_TOK  1 /* Token             */
#define PLR_TYP_KEY  2 /* Keyword           */
#define PLR_TYP_WKY  3 /* Wide Keyword      */
#define PLR_TYP_CFG  4 /* Language token    */
#define PLR_TYP_COM  5 /* Comment           */

/* Terminal <--> Comment */

#define CFG_TERM_TO_COM(typ) ( (typ) + PLR_TYP_COM )
#define CFG_COM_TO_TERM(typ) ( (typ) - PLR_TYP_COM )

/* Recognizer */

#define CFG_NTM(typ)      ( (typ) == PLR_TYP_NTM )
#define CFG_CFG(typ)      ( (typ) == PLR_TYP_CFG )
#define CFG_TOK(typ)      ( (typ) == PLR_TYP_TOK || (typ) == PLR_TYP_CFG )
#define CFG_KEY(typ)      ( (typ) == PLR_TYP_KEY || (typ) == PLR_TYP_WKY )
#define CFG_WCKEY(typ)    ( (typ) == PLR_TYP_WKY )
#define CFG_COM(typ)      ( (typ) >= PLR_TYP_COM )

#define CFG_TOK_NTM(typ)  ( CFG_TOK(typ)     || CFG_NTM(typ) )
#define CFG_TOK_KEY(typ)  ( CFG_TOK(typ)     || CFG_KEY(typ) )
#define CFG_TERMINAL(typ) ( CFG_TOK_KEY(typ) || \
                            ( CFG_COM(typ) && (typ) != PLR_TYP_COM ) )
/*DOC_INTERFACE_COPY_OFF*/

/*I------------------- Production types: special recognizer ----------------- */

bool nilProd(string prod)
/* production name = "nil" ? */
{
  return( ! strcmp("nil",prod) );
}

bool consProd(string prod)
/* production name = "cons" ? */
{
  return( ! strcmp("cons",prod) );
}

bool ignProd(string prod)
/* production name = "ign#*" ? */
{
  return( strlen(prod) >= 4 && ! strncmp("ign",prod,3) && isdigit(prod[3]) );
}

