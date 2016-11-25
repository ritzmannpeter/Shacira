/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [literal.c]             Literal Conversion                               */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

#include "sink.h"

/*I--------------------- String to C-Literal ---------------------------- */

string LIT_c_str_lit(string s)
/* converts string 's' to a C-Literal; allocs memory 
   ( single byte character set or UTF-8 )
*/
{ Sink res = Sink_open();
  Sink_putc(res,'"');
  for (; *s != 0; s += 1)
    switch(*s)
    {
      case '\"' :
      case '\\' : Sink_putc(res,'\\'); Sink_putc(res, *s); break;
      case '\r' : Sink_putc(res,'\\'); Sink_putc(res,'r'); break;
      case '\n' : Sink_putc(res,'\\'); Sink_putc(res,'n'); break;
      case '\f' : Sink_putc(res,'\\'); Sink_putc(res,'f'); break;
      case '\t' : Sink_putc(res,'\\'); Sink_putc(res,'t'); break;
      default   : if (isascii(*s) && isprint(*s))
                    Sink_putc(res,*s);
                  else
                  {
                    Sink_printf(res,"\\%03o",(*s)&0xff); /* */
                    /* the hexadecimal notation doesn't work with each compiler 
                    Sink_printf(res,"\\x%02x",*s);
                    */
                  }
    };
  Sink_putc(res,'"');
  return Sink_close(res);
}

string LIT_c_char_lit(char c)
/* converts character 'c' to a C-Literal; allocs memory 
   ( single byte character set or UTF-8 )
*/
{ Sink res = Sink_open();
  Sink_putc(res,'\'');
  switch(c)
  {
    case '\'' :
    case '\\' : Sink_putc(res,'\\'); Sink_putc(res, c);  break;
    case '\r' : Sink_putc(res,'\\'); Sink_putc(res,'r'); break;
    case '\n' : Sink_putc(res,'\\'); Sink_putc(res,'n'); break;
    case '\f' : Sink_putc(res,'\\'); Sink_putc(res,'f'); break;
    case '\t' : Sink_putc(res,'\\'); Sink_putc(res,'t'); break;
    default   : if (isascii(c) && isprint(c))
                  Sink_putc(res,c);
                else
                  Sink_printf(res,"\\%03o",(c)&0xff); /* s.o. */
  };
  Sink_putc(res,'\'');
  return Sink_close(res);
}

/*I--------------------- STYX-Literal to string ------------------------- */

static int hex1(int h)
{
  return INRANGE('0',h,'9') ? h-'0' : h-'a'+10;
}

static int hex2(int h1, int h2)
{
  return (hex1(h1) << 4) + hex1(h2);
}

int LIT_hex2_char(int h1, int h2)
/* constructs a single byte character from the hex values 'h1' and 'h2' */
{
  return hex2(h1,h2);
}

int LIT_hex_val(int h, int p)
/* 
   constructs a unicode character from up to 8 hex values;
   has to be called for each hex value and the result added to get the final code
   h = hex digit, p = position [ 0 .. 7 ]
*/
{
  return hex1(h) << (4 * p);
}

wc_string LIT_styx_lit_str(long *len, string s, c_bool* ucs4)
/* converts STYX literal 's' to a string; allocs memory 
   ( 'ucs4' --> unicode character found in literal )
*/
{ long      i, j, wc, loc = 0, slen = strlen(s); 
  wc_string tstring = (wc_string)NewMem((slen+1)*sizeof(wc_char));
  *ucs4 = False;
  for (i = 1; i < slen-1; i++) /* " Char1 Char2 ... " */
  if (s[i] == '\\')
    switch(s[i+1])
    {
      case '\'' : tstring[loc] = WCHAR_LITERAL('\''); loc += 1; i += 1; break;
      case '\"' : tstring[loc] = WCHAR_LITERAL('\"'); loc += 1; i += 1; break;
      case '`'  : tstring[loc] = WCHAR_LITERAL('`');  loc += 1; i += 1; break;
      case '\\' : tstring[loc] = WCHAR_LITERAL('\\'); loc += 1; i += 1; break;
      case 'p'  : tstring[loc] = WCHAR_LITERAL('\f'); loc += 1; i += 1; break;
      case 'r'  : tstring[loc] = WCHAR_LITERAL('\r'); loc += 1; i += 1; break;
      case 'n'  : tstring[loc] = WCHAR_LITERAL('\n'); loc += 1; i += 1; break;
      case 't'  : tstring[loc] = WCHAR_LITERAL('\t'); loc += 1; i += 1; break;
      case 'x'  :
      case 'X'  :
        { 
          for( i += 1, wc=0, j=7; j >= 0; --j )
          {
            ++i; wc += LIT_hex_val(s[i],j);
          }
          tstring[loc] = (wc_char)wc; loc += 1; *ucs4 = True;
        }
        break;
      default   : tstring[loc] = (wc_char)hex2(s[i+1],s[i+2]); loc += 1; i += 2; break;
    }
  else
  { 
    tstring[loc] = s[i]; loc += 1; 
  }
  *len = loc; tstring[loc] = WCHAR_LITERAL('\0');
  return( tstring );
}
