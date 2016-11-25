/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxI18NLit.C]      Charset Conversion & Literals Implementation (C++)  */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2003 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include <iconv.h>
#include <string.h>
#include <errno.h>
#include "StyxI18NLit.h"


namespace styx
{

  CStyxCharConv::CStyxCharConv()
  {
    s_endian = 0;
    t_endian = 0;
    icd      = 0;
  }
  
  CStyxCharConv::CStyxCharConv(string cs_src, string cs_dst)
  {
    init(cs_src,cs_dst);
  }
  
  CStyxCharConv::~CStyxCharConv()
  {
    quit();
  }
  
  
  bool CStyxCharConv::init(string cs_src, string cs_dst)
  { 
    quit();
    iconv_t cd = iconv_open(cs_dst.c_str(),cs_src.c_str());
    if( cd == (iconv_t)-1 ) // error
    { char buf[1024+1];
      errmsg = strerror_r(errno,buf,1024);
      return false;
    }
    else
    {
      icd      = cd;
      ics_dst  = cs_dst;
      ics_src  = cs_src;
      s_endian = 0;
      t_endian = 0;
      if( cs_src == CS_ID_WCHAR )
      {
        for( size_t i=0, j=0; i < sizeof(wchar_t); ++i, j+=8 )
        {
          s_endian |= ((wchar_t)i+1) << j;
        }
      }
      if( cs_dst == CS_ID_WCHAR )
      {
        for( size_t i=0, j=0; i < sizeof(wchar_t); ++i, j+=8 )
        {
          t_endian |= ((wchar_t)i+1) << j;
        }
      }
    }
    return true;
  }
  
  bool CStyxCharConv::quit()
  {
    if( icd ) 
    {
      iconv_close((iconv_t)icd);
      icd = 0;
    }
    return true;
  }
  
  string& CStyxCharConv::getError()
  {
    return errmsg;
  }
  
  wchar_t* CStyxCharConv::ucs42intern(wchar_t* ws, size_t size /*bytes*/, wchar_t endian)
  {
    // assertion: size % wchar_size = 0 !
    if( endian != 0 )
    { char*  s = (char*)ws;
      char   buf[80+1];
      size_t i, j, k;
      for( i=0; i < size; i+=sizeof(wchar_t) )
      {
        for( j=0, k=sizeof(wchar_t)-1; j < sizeof(wchar_t); ++j, --k )
        {
          buf[j] = s[i+((char*)&endian)[k]-1];
        }
        memcpy(&s[i],buf,sizeof(wchar_t));
      }
    }
    return ws;
  }
  
  wchar_t* CStyxCharConv::intern2ucs4(wchar_t* ws, size_t size /*bytes*/, wchar_t endian)
  {
    // assertion: size % wchar_size = 0 !
    if( endian != 0 )
    { char*  s = (char*)ws;
      char   buf[80+1];
      size_t i, j, k;
      for( i=0; i < size; i+=sizeof(wchar_t) )
      {
        for( j=0, k=sizeof(wchar_t)-1; j < sizeof(wchar_t); ++j, --k )
        {
          buf[((char*)&endian)[k]-1] = s[i+j];
        }
        memcpy(&s[i],buf,sizeof(wchar_t));
      }
    }
    return ws;
  }
  
  
  int CStyxCharConv::convert(const string& src, size_t size, string& dst)
  { int rc = -2; char buf[1024+1];
    errmsg = "";
    if( icd > 0 )
    { size_t isize = size,
             osize = isize*6,
             oleft = osize; 
      char   in[isize],
          *  iptr  = in,
             out[osize],
          *  optr  = out;
      memset(in,0,isize); memset(out,0,osize);
      //memcpy(in,src.data(),isize);
      memcpy(in,src.c_str(),isize);
      if( s_endian != 0 && (isize % sizeof(wchar_t)) != 0 )
      {
        dst    = src;
        errmsg = "illegal size";
        return -1;
      }
      else
      if( s_endian != 0 )
      {
        ucs42intern((wchar_t*)in,isize,s_endian);
      }
      rc = iconv((iconv_t)icd,&iptr,&isize,&optr,&oleft);
      if( rc >= 0 )
      { 
        osize -= oleft; // number of used bytes
        if( t_endian != 0 )
        {
          intern2ucs4((wchar_t*)out,osize,t_endian);
        }
        //dst = string(out,osize);
        dst = out;
  //cout << "RC=" << rc << ",ISIZE=" << isize << ",IN=" << in << ",OUT=" << out << ",DST=" << dst.c_str() << "\n";
        return rc==0?size:rc;
      }
      else
      if( rc == -1 && errno == EINVAL )
      {
        errmsg = strerror_r(errno,buf,1024);
      }
      else
      {
        errmsg = strerror_r(errno,buf,1024);
        rc = -2;
      }
    }
    else errmsg = "iconv not initialized";
    dst = src;
    return rc;
  }

}
