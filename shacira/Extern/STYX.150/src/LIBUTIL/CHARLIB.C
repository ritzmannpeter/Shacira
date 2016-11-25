/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [charlib.c]          Basic Character ( Set ) & String Library              */
/*                                                                            */
/* Copyright (c) 1995 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

#include "standard.h"

#if defined( _WIN32 )
#include <windows.h>
#include <winuser.h>
#endif

/* Die Datei ist selber einer Konversion unterzogen worden und entsprechend   */
/* lag hier alles auf dem RÅcken: ~^∞$ı (Lars D:lle)                          */

/*INTERFACE*/
#define ibmpc_a_uml 132
#define ibmpc_A_uml 142
#define ibmpc_o_uml 148
#define ibmpc_O_uml 153
#define ibmpc_u_uml 129
#define ibmpc_U_uml 154
#define ibmpc_sz    225

/*INTERFACE*/
#define latin_a_uml 228
#define latin_A_uml 196
#define latin_o_uml 246
#define latin_O_uml 214
#define latin_u_uml 252
#define latin_U_uml 220
#define latin_sz    223

/*I---------------------- ( German ) Character types ------------------------ */

bool ger_islower(char c)
/* german islower */
{
  switch(c)
  {
    case ibmpc_a_uml: 
    case ibmpc_o_uml:
    case ibmpc_u_uml:
    case ibmpc_sz: return True;
    case ibmpc_A_uml:
    case ibmpc_O_uml:
    case ibmpc_U_uml: return False;
    default : return islower(c);
  }
}

char ger_tolower(char c)
/* german tolower */
{
  switch(c)
  {
    case ibmpc_a_uml: 
    case ibmpc_o_uml:
    case ibmpc_u_uml:
    case ibmpc_sz: return c;
    case ibmpc_A_uml: return (char)ibmpc_a_uml;
    case ibmpc_O_uml: return (char)ibmpc_o_uml;
    case ibmpc_U_uml: return (char)ibmpc_u_uml;
    default : return isupper(c)?tolower(c):c;
  }
}

bool ger_isupper(char c)
/* german isupper */
{
  switch(c)
  {
    case ibmpc_a_uml: 
    case ibmpc_o_uml:
    case ibmpc_u_uml:
    case ibmpc_sz: return False;
    case ibmpc_A_uml:
    case ibmpc_O_uml:
    case ibmpc_U_uml: return True;
    default : return isupper(c);
  }
}

char ger_toupper(char c)
/* german toupper */
{
  switch(c)
  {
    case ibmpc_sz:
    case ibmpc_A_uml:
    case ibmpc_O_uml:
    case ibmpc_U_uml: return c;
    case ibmpc_a_uml: return (char)ibmpc_A_uml;
    case ibmpc_o_uml: return (char)ibmpc_O_uml;
    case ibmpc_u_uml: return (char)ibmpc_U_uml;
    default : return islower(c)?toupper(c):c;
  }
}

bool ger_isprint(char c)
/* german isprint */
{
  switch(c)
  {
    case ibmpc_a_uml: 
    case ibmpc_o_uml:
    case ibmpc_u_uml:
    case ibmpc_sz:
    case ibmpc_A_uml:
    case ibmpc_O_uml:
    case ibmpc_U_uml: return True;
    default : 
      /* isprint doesn't work */
      //if( c <= 126 && c >= 32 ) return True; 
      if( isascii(c) && isprint(c) ) return True;
      else return ! iscntrl(c);
  }
}

static bool ger_char(char c)
/* whether 'c' is a special german character */
{
  return 
  ( 
    c == ibmpc_a_uml || c == ibmpc_o_uml || 
    c == ibmpc_u_uml || c == ibmpc_sz    || 
    c == ibmpc_A_uml || c == ibmpc_O_uml || c == ibmpc_U_uml 
  ) ? True : False;
}

int ger_charcmp(char l, char r)
/* l - r ( german ) */
{ bool gl = ger_char(l), gr = ger_char(r);
  if( ! gl && ! gr ) return( l - r );
  if( ! ( gl && gr ) )
  { char ll, rr; int res = 0;
    /* res = -1 --> ll < rr */
    if( gl ) { ll = l; rr = r; }
    else     { ll = r; rr = l; }
    switch(ll)
    {
      case ibmpc_a_uml: res = ( rr <= 'a' ) ? 1 : -1; break;
      case ibmpc_o_uml: res = ( rr <= 'o' ) ? 1 : -1; break;
      case ibmpc_u_uml: res = ( rr <= 'u' ) ? 1 : -1; break;
      case ibmpc_sz: res = ( rr <= 's' ) ? 1 : -1; break;
      case ibmpc_A_uml: res = ( rr <= 'A' ) ? 1 : -1; break;
      case ibmpc_O_uml: res = ( rr <= 'O' ) ? 1 : -1; break;
      case ibmpc_U_uml: res = ( rr <= 'U' ) ? 1 : -1; break;
      default : BUG;
    }
    return( ( ll == l ) ? res : res - 2 );
  }
  else
  { bool ugr;
    if( l == r ) return( 0 );
    ugr = ( r == ibmpc_A_uml || r == ibmpc_O_uml || r == ibmpc_U_uml );
    switch(l)
    { 
      case ibmpc_a_uml: return( ( ugr ) ? 1 : -1 );
      case ibmpc_o_uml: return( ( ugr || r == ibmpc_a_uml ) ? 1 : -1 );
      case ibmpc_sz: 
        return( ( ugr || r == ibmpc_a_uml || r == ibmpc_o_uml ) ? 1 : -1 );
      case ibmpc_u_uml: 
        return
        ( 
          ( ugr || r == ibmpc_a_uml || r == ibmpc_o_uml || r == ibmpc_sz ) 
          ? 1 : -1 
        ); 
      case ibmpc_A_uml: return( -1 );
      case ibmpc_O_uml: return( ( r == ibmpc_A_uml ) ? 1 : -1 );
      case ibmpc_U_uml: 
        return( ( r == ibmpc_A_uml || r == ibmpc_O_uml ) ? 1 : -1 );
      default : BUG;
    }
  }
  return 0; /*dummy*/
}

/*I------------------------- Character conversion --------------------------- */

char umlaut_ascii_to_eascii(char c)
/* us ascii --> extended/OEM ascii */
{
  switch(c)
  {
    case '{' : return (char)ibmpc_a_uml;
    case '|' : return (char)ibmpc_o_uml;
    case '}' : return (char)ibmpc_u_uml;
    case '~' : return (char)ibmpc_sz;
    case '[' : return (char)ibmpc_A_uml;
    case '\\': return (char)ibmpc_O_uml;
    case ']' : return (char)ibmpc_U_uml;
    default  : return c;
  }
}

char umlaut_eascii_to_ascii(char c)
/* extended/OEM ascii --> us ascii */
{
  switch(c)
  {
    case ibmpc_a_uml : return '{';
    case ibmpc_o_uml : return '|';
    case ibmpc_u_uml : return '}';
    case ibmpc_sz : return '~';
    case ibmpc_A_uml : return '[';
    case ibmpc_O_uml : return '\\';
    case ibmpc_U_uml : return ']';
    default  : return c;
  }
}

char umlaut_eascii_to_ansi(char c)
/* extended/OEM ascii --> ansi */
{ 
#if defined( _WIN32 )
  char src[2];
  char dst[2];
  sprintf(src,"%c",c);
  return OemToChar(src,dst) == TRUE ? dst[0] : c;
#else
  switch(c)
  {
    case ibmpc_a_uml : return (char)latin_a_uml;
    case ibmpc_o_uml : return (char)latin_o_uml;
    case ibmpc_u_uml : return (char)latin_u_uml;
    case ibmpc_sz    : return (char)latin_sz;
    case ibmpc_A_uml : return (char)latin_A_uml;
    case ibmpc_O_uml : return (char)latin_O_uml;
    case ibmpc_U_uml : return (char)latin_U_uml;
    default          : return c;
  }
#endif
}

char umlaut_ansi_to_eascii(char c)
/* ansi --> extended/OEM ascii */
{ 
#if defined( _WIN32 )
  char src[2];
  char dst[2];
  sprintf(src,"%c",c);
  return CharToOem(src,dst) == TRUE ? dst[0] : c;
#else
  switch((unsigned char)c)
  {
    case latin_a_uml : return (char)ibmpc_a_uml;
    case latin_o_uml : return (char)ibmpc_o_uml;
    case latin_u_uml : return (char)ibmpc_u_uml;
    case latin_sz    : return (char)ibmpc_sz;
    case latin_A_uml : return (char)ibmpc_A_uml;
    case latin_O_uml : return (char)ibmpc_O_uml;
    case latin_U_uml : return (char)ibmpc_U_uml;
    default          : return c;
  }
#endif
}

/*I--------------------------- String match --------------------------------- */

bool Str_matches(string str, string pat)
/* whether 'str' matches 'pat' 
   meta characters: '*', '?'
*/
{
  if (STR_EMPTY(pat)) return STR_EMPTY(str);
  switch (pat[0])
  {
    case '*' : { int i;
                 for (i = 0; True; i++)
                 {
                   /* str matches pat+1 */
                   if (Str_matches(str+i,pat+1)) return True;
                   /* str does not match pat+1 */
                   if (STR_EMPTY(str+i)) return False;
                 }
               }
    case '?' : if (STR_EMPTY(str))   return False;
               return Str_matches(str+1,pat+1);
    default  : if (STR_EMPTY(str))   return False;
               if (pat[0] != str[0]) return False;
               return Str_matches(str+1,pat+1);
  }
}

