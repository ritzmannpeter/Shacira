/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxString.h] UTF-8 <--> UCS-4 String Conversion Implementation (C++)   */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2003 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_STRING_INCL
#define STYX_STRING_INCL


#include <wctype.h>
#include <string.h>
#include <stdlib.h>
#include <string>

/** @file
    UTF-8 <--> Unicode (UCS-4) and other string conversions 
*/

namespace styx
{
  using namespace std;

  /** @addtogroup StyxLibraryCPP
      C++ Scanner & parser library
  */
  //@{

  /** @addtogroup StyxString
      UTF-8 <--> Unicode (UCS-4) and other string conversions 
  */
  //@{

  /** copy string to lower case string 
      @param s input string ( multibyte )
      @result lower case string ( multibyte )
  */
  string                string2lower(string s);

  /** copy wstring to lower case wstring 
      @param s input string ( unicode )
      @result lower case string ( unicode )
  */
  basic_string<wchar_t> string2lower(wstring s);

  /** copy string to wstring 
      @param s input string ( multibyte )
      @result input string ( unicode )
  */
  basic_string<wchar_t> string2wstring(const string& s);

  /** UTF-8 string --> unicode (UCS-4) string 
      @param s input string ( multibyte )
      @result converted string ( unicode )
  */
  basic_string<wchar_t> multibyte2unicode(const string& s);
  
  /** unicode (UCS-4) string --> UTF-8 string 
      @param s input string ( unicode )
      @result converted string ( multibyte )
  */
  string                unicode2multibyte(const wstring& s);

  //@}

  //@}
}

#endif
