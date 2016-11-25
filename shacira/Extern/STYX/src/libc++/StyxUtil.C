/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxUtil.C]   Utility Functions                                         */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2004 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include <iostream>
#include <fstream>

#include "StyxUtil.h"

namespace styx
{

  bool file2text(string path, string& content)
  {
    if( path.length() > 0 )
    { ifstream is(path.c_str());
      if( !is )
      {
        printf("couldn't open '%s'\n",path.c_str());
      }
      else
      { char c;
        while( is.get(c) ) content += c;
        return true;
      }
    }
    else
    {
      printf("missing path\n");
    }
    return false;
  }

  bool file2text(string path, wstring& content)
  {
    if( path.length() > 0 )
    { 
      basic_ifstream<wchar_t,char_traits<wchar_t> > is(path.c_str());
      if( !is )
      {
        printf("couldn't open '%s'\n",path.c_str());
      }
      else
      { wchar_t c;
        while( is.get(c) ) content += c;
        return true;
      }
    }
    else
    {
      printf("missing path\n");
    }
    return false;
  }
  
}
