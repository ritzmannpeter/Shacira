/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxI18NLit.h]      Charset Conversion & Literals Implementation (C++)  */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2003 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#ifndef STYX_I18NLIT_INCL
#define STYX_I18NLIT_INCL


using namespace std;

#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <wctype.h>
#include <iconv.h>
#include <string>
#include <vector>
#include <map>

namespace styx
{

#define CS_ID_WCHAR   "UCS-4"
#define CS_ID_MBYTE   "UTF-8"
#define CS_ID_LATIN1  "LATIN1"


class CStyxCharConv
{
protected:
  typedef basic_string<wchar_t > wstring;

  void*   icd;
  wchar_t s_endian;
  wchar_t t_endian;
  string  ics_src;
  string  ics_dst;
  string  errmsg;

  virtual wchar_t* ucs42intern(wchar_t* ws, size_t size /*bytes*/, wchar_t endian);

  virtual wchar_t* intern2ucs4(wchar_t* ws, size_t size /*bytes*/, wchar_t endian);

public:
  CStyxCharConv();
  CStyxCharConv(string cs_src, string cs_dst);
  virtual ~CStyxCharConv();

  virtual string& getError();

  virtual bool init(string cs_src, string cs_dst);
  virtual bool quit();

  /* character set conversion of 'src[size]' to 'dst'
     RC: >=0 on O.K. ( number of conversions / characters ) 
       | =-1 on possible incomplete input 
       | =-2 on error
  */
  virtual int  convert(string& src, size_t size, string& dst);
};

}

#endif
