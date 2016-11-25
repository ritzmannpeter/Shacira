/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [symbols.h]                    Type: Symbol                              */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef symbols_INCL
#define symbols_INCL


#include "standard.h"


#ifdef __cplusplus
extern "C" {
#endif


/*  
    This module implements the symbol type for a unique representation of strings
    and the symbol table in which they are stored. One intention is the reduction
    of place- and time-complexity when dealing with many identical strings.

    Specification
    1) forall String s : strcmp(s,symbolToString(stringToSymbol(s))) == 0.
    2) forall Symbol s : equalSymbols(s,stringToSymbol(symbolToString(s)).
    3) equalSymbols is an equality.
*/

/* ------------------------------ The Type -------------------------------- */

AbstractType( symbol ) /* Abstract symbol type */
;

/* ----------------------------- Init & Quit ------------------------------ */

void initSymbols(void);                /* initializes the symbol table      */
void freeSymbols(void);                /* releases the symbol table         */

/* ----------------------------- Conversion ------------------------------- */

symbol stringToSymbol(c_string str); /* converts string 'str' into a symbol */

symbol lstringToSymbol(c_string str)
/* converts ( lower case ) string 'str' into a symbol */
;

symbol ustringToSymbol(c_string str)
/* converts ( upper case ) string 'str' into a symbol */
;

c_string symbolToString(symbol sym)
/* string corresponding to symbol 'sym' */
;

symbol bstringToSymbol(c_bstring bstr)
/* converts binary string 'bstr' into a symbol */
;

c_bstring symbolToBString(symbol sym)
/* binary string corresponding to symbol 'sym' */
;


/* ------------------------------ Predicates ------------------------------ */

c_bool equalSymbols(symbol a, symbol b)
/* whether two symbols 'a' and 'b' are equal */
;

c_bool binarySymbol(symbol s)
/* whether symbol 's' represents a binary string */
;


/* ----------------------------- Debugging -------------------------------- */

void printSymbols(int indent);     /* prints the symbol table to stdout     */
long countSymbols(void);           /* number of symbols in the symbol table */


#ifdef __cplusplus
}
#endif

#endif