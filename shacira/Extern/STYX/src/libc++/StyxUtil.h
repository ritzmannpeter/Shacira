/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxUtil.h]   Utility Functions                                         */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2004 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_UTIL_INCL
#define STYX_UTIL_INCL


#include <wctype.h>
#include <string>

/** @file
    Utility functions
*/


namespace styx
{
  using namespace std;

  /** @addtogroup StyxUtil
      Utility functions
  */
  //@{

  /** read single byte file into content
      @param path path of the file to read
      @param content result string (single byte) with the file content
      @return true or false on error
  */
  bool file2text(string path, string& content);
  /** read unicode file into content
      @param path path of the file to read
      @param content result string (unicode) with the file content
      @return true or false on error
  */
  bool file2text(string path, wstring& content);

  //@}

}

#endif
