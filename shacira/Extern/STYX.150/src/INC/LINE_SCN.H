/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [line_scn.h]              Source Line Scanner                            */
/*                         & simple AWK Functionality                       */
/*                                                                          */
/* Copyright (c) 1994 by Lars D\olle, Heike Manns                           */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef line_scn_INCL
#define line_scn_INCL


/*  

  [line_scn] contains a set of functions for source analysis.

  1. The primitive

  |      string Line_get(FILE *SysIn)

  reads the next line from the source file 'SysIn' and returns it as a string.

  '\x1a' (DOS) and '(-1)' (UNIX) are recognized as end of file.
  The end of line characters '\n' eg. '\r\n' and trailing spaces will be removed.

  2. Further this module provides a simple AWK-mechanism.

  3. The primitive

  |      string Line_getCFunNam(string CDecl)

	 extracts the function name from a C-deklaration/definition.

  4. The primitive

  |      string Line_replace(string txt, MAP(symbol,symbol) ReplaceRules)

 supports simple text replacement. Each occurance of a key in the given text will
 be replaced by the associated value.

  5. The following functions support the removement/extraction of HTML/XML-tags,
     C-comments and spaces in a given text.

  |      string Line_withTag(string txt)
  |      string Line_withoutTag(string txt)
  |      string Line_withCCom(string txt)
  |      string Line_withCComText(string txt)
  |      string Line_withoutCCom(string txt)
  |      string Line_withoutWhite(string txt)
  |      string Line_clip[L|R](string txt)

  6. Finally this module defines a set of functions for URI-Creation/Evaluation. ( RFC 2396 )

*/

#include "standard.h"
#include "symbols.h"
#include "hmap.h"
#include "otab.h"


#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------- Single line scanner ------------------------- */

c_string Line_get(FILE *SysIn)
/* get a single line or NULL; allocs memory
   All '\r', final '\n', trailing spaces and tabs
   are removed and other tabs expanded.
   Both (-1) and (0x1a) are treated as EOF-character.
*/
;


/* ------------------------ Split line & AWK -------------------------------- */

AbstractType( AWK ); /* Abstract AWK type */

ROW(c_string) StrToWords(c_string s)
/* get a row with all the words of line 's' */
;

void AWK_defKey(AWK awk, c_string key, void (*act)(ROW(c_string) wrd))
/* adds a line key / action pair to 'awk' */
;

AWK AWK_new(c_string Comment)
/* creates an AWK structure
   parameter: comment key
*/
;

void AWK_free(AWK awk);                /* frees 'awk'                       */

void AWK_apply(AWK awk, c_string FileName)
/* evaluates 'FileName' according to the rules in 'awk' */
;


/* -------------------------- Text substitution --------------------------- */

c_string Line_clipR(c_string txt)
/* removes trailing white space; allocs memory */
;

c_string Line_clipL(c_string txt)
/* removes leading white space; allocs memory */
;

c_string Line_clip(c_string txt)
/* removes trailing and leading white space; allocs memory */
;

c_string Line_withoutWhite(c_string txt)
/* removes white space; allocs memory */
;

c_string Line_withTok
       (
         c_string txt,
         void (*getNextTokPos)(c_string s, c_string* ta, c_string* te)
       )
/* get token text only or NULL; allocs memory */
;

c_string Line_withoutTok
       (
         c_string txt,
         void (*getNextTokPos)(c_string s, c_string* ta, c_string* te)
       )
/* get text without token or NULL; allocs memory */
;

c_string Line_withoutTag(c_string txt)
/* get text without HTML/XML-tags or NULL; allocs memory */
;

c_string Line_withCCom(c_string txt)
/* get C-comment only or NULL; allocs memory */
;

c_string Line_withCComText(c_string txt)
/* get C-comment text only or NULL; allocs memory */
;

c_string Line_withoutCCom(c_string txt)
/* get text without C-comment or NULL; allocs memory */
;

c_string Line_getCFunNam(c_string CDecl)
/* extracts C-function name or NULL; allocs memory
   assertion: no comments in between 'CDecl'
   evaluation from right to left:
     ... <Space> <ID> <Space> ( <Parameter> )
   | ... ( ... <ID> ... ) ...\<ID> ( <Parameter> )
*/
;

c_string Line_replace(c_string txt, MAP(symbol,symbol) ReplaceRules)
/* replaces 'txt' according 'ReplaceRules'; allocs memory
   assertion: disjunct keys
*/
;


/* -------------------------- URI Generation & Evaluation ----------------- */

#define URI_SCHEME    0
#define URI_AUTHORITY 1
#define URI_PATH      2
#define URI_QUERY     3
#define URI_FRACTION  4

c_bool URI_hasFileScheme(MAP(long,symbol) parts)
/* whether URI has a file scheme */
;

void URI_setFileScheme(MAP(long,symbol) parts)
/* set URI scheme to file scheme */
;

c_bool URI_hasAuthority(MAP(long,symbol) parts)
/* whether URI has a non-empty authority */
;

c_bool URI_hasFraction(MAP(long,symbol) parts)
/* whether URI has a non-empty fraction */
;

void URI_setDftFraction(c_string dftfraction, MAP(long,symbol) parts)
/* set URI fraction to default fraction 'dftfraction', if non-defined */
;

c_string URI_getFraction(MAP(long,symbol) parts)
/* get URI fraction or NULL */
;

c_string URI_getPath(MAP(long,symbol) parts); /* get URI path or NULL       */

void URI_setPath(c_string path, MAP(long,symbol) parts)
/* set URI path to 'path' */
;

int URI_EscToAscChar(c_string uri_part)
/* get ascii value of escaped character or -1 */
;

c_bool URI_isLocalFile(MAP(long,symbol) parts)
/* whether URI references a local file */
;

c_bool URI_isTreeLocalFile(c_string abspath, MAP(long,symbol) parts)
/* whether URI refernces a file within the local tree 'abspath' */
/* True <-->
   (empty or file scheme) and empty authority and path located in tree
*/
;

void URI_desParts(c_string txt, MAP(long,symbol) parts)
/* destructs URI 'txt' to its components in 'parts' */
;

c_string URI_consParts(MAP(long,symbol) parts, c_bool localURI)
/* constructs URI from its components in 'parts'; allocs memory */
;

void URI_RelToAbs
     (
       c_string rel, c_string base, c_string doc, MAP(long,symbol) abs_parts
     )
/* destructs relative URI 'rel' to its absolute components in 'parts' */
;



#ifdef __cplusplus
}
#endif

#endif
