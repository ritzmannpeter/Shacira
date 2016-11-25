/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [StyxString.C] UTF-8 <--> UCS-4 String Conversion Implementation (C++)   */
/*                                                                          */
/*                This file belongs to the Styx Scanner & parser generator. */
/*                                                                          */
/* Copyright (c) 2003 by Doelle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "StyxString.h"


namespace styx
{

  typedef unsigned char byte;
  
  /*
     UCS-4 range (hex.)           UTF-8 octet sequence (binary)
     0000 0000-0000 007F   0xxxxxxx
     0000 0080-0000 07FF   110xxxxx 10xxxxxx
     0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
  
     0001 0000-001F FFFF   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
     0020 0000-03FF FFFF   111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
     0400 0000-7FFF FFFF   1111110x 10xxxxxx ... 10xxxxxx
  */
  
  static const int MAX_UTF8_BYTES = 6;
  
  struct StyxUtf8
  {
    /* UCS4 character range */
    unsigned long ucs4_lwr; 
    unsigned long ucs4_upr; 
    byte          first_utf8_byte; // initial bits
    int           first_utf8_bit;  // 7  .. 0
    int           first_ucs4_bit;  // 31 .. 0
  };
  
  static const StyxUtf8 UCS4_PARTITION[MAX_UTF8_BYTES] =
  {
    { 0x00000000, 0x0000007F, 0x00, 6, 6  },
    { 0x00000080, 0x000007FF, 0xC0, 4, 10 },
    { 0x00000800, 0x0000FFFF, 0xE0, 3, 15 },
    { 0x00010000, 0x001FFFFF, 0xF0, 2, 20 },
    { 0x00200000, 0x03FFFFFF, 0xF8, 1, 25 },
    { 0x04000000, 0x7FFFFFFF, 0xFC, 0, 31 }
  };
  
  
  static int ucs4_to_utf8(const wstring& in, string& out)
  /* ucs4 --> utf-8 ( RFC 2279 ) 
     'out': utf-8 representation of 'in' 
     RC: >=0 on O.K. ( number of written bytes ) 
       | =-1 on possible incomplete input 
       | =-2 on error
  */
  { size_t len = in.length(), ucs4_bit, utf8_bit, i;
    int    ucs4_idx, j, k;
    out = "";
    for( i=0; i < len; ++i )
    { wint_t wc = (wint_t)in[i];
      for( ucs4_idx = -1, j=0; j < MAX_UTF8_BYTES; ++j )
      {
        if( wc >= UCS4_PARTITION[j].ucs4_lwr &&
            wc <= UCS4_PARTITION[j].ucs4_upr  )
        {
          ucs4_idx = j; 
          break;
        }
      }
      if( ucs4_idx == -1 ) return -2;
      else
      if( ucs4_idx == 0 )
      {
        out += (byte)wc;
      }
      else
      {
        for( ucs4_bit = UCS4_PARTITION[ucs4_idx].first_ucs4_bit, j=0; 
             j <= ucs4_idx; ++j )
        {
          if( j > 0 )
          {
            out      += (char)0x80;
            utf8_bit  = 5;
          }
          else
          {
            out      += UCS4_PARTITION[ucs4_idx].first_utf8_byte;
            utf8_bit  = UCS4_PARTITION[ucs4_idx].first_utf8_bit;
          }
          size_t utf8_idx = out.length() - 1;
          for( k=(int)utf8_bit; k >= 0; k--, --ucs4_bit )
          { 
            if( wc & (1<<ucs4_bit) )
              out[utf8_idx] |= (1<<k);
          }
        }
      }
    }
    if( i < len ) return -2;
    return (int)out.length();
  }
  
  static int utf8_to_ucs4(const string& in, wstring& out)
  /* utf-8 --> ucs4 ( RFC 2279 )
     'out': ucs4 representation of 'in'
     RC: >=0 on O.K. ( number of written wide characters ) 
       | =-1 on possible incomplete input 
       | =-2 on error
  */
  { size_t len = in.length(), 
           ucs4_bit, utf8_bit, i;
    int    utf8_idx, j, k;
    for( i=0; i < len; )
    { 
      for( utf8_idx = -1, j=0; j < MAX_UTF8_BYTES; ++j )
      {
        if( in[i] >= UCS4_PARTITION[j].first_utf8_byte &&
            ( j == MAX_UTF8_BYTES - 1 || in[i] < UCS4_PARTITION[j+1].first_utf8_byte ) )
        {
          utf8_idx = j; break;
        }
      }
      if( utf8_idx == -1 ) return -2;
      else
      if( utf8_idx == 0 )
      {
        out += (wchar_t)in[i++];
      }
      else
      { wint_t wc = 0L;
        for( ucs4_bit = UCS4_PARTITION[utf8_idx].first_ucs4_bit, j=0; 
             j <= utf8_idx && i < len; ++j, ++i )
        {
          utf8_bit = (j>0)?5:UCS4_PARTITION[utf8_idx].first_utf8_bit;
          for( k=(int)utf8_bit; k >= 0; --k, --ucs4_bit )
          {
            if( in[i] & (1<<k) )
              wc |= (1<<ucs4_bit);
          }
        }
        if( j <= utf8_idx ) return -1;
        out += (wchar_t)wc;
      }
    }
    if( i < len ) return -2;
    return (int)out.length();
  }
  
  
  string string2lower(string s)
  {
    for( size_t len = s.length(), i=0; i < len; ++i )
      if( isupper(s[i]) ) s[i] = tolower(s[i]);
    return s;
  }

  wstring string2lower(wstring s)
  {
    for( size_t len = s.length(), i=0; i < len; ++i )
      if( iswupper(s[i]) ) s[i] = towlower(s[i]);
    return s;
  }

  wstring string2wstring(const string& s)
  { wstring result;
    result.reserve(s.length()+1);
    for( size_t i=0; i < s.length(); ++i )
    {
      result += (wchar_t)s[i];
    }
    return result;
  }
  
  wstring multibyte2unicode(const string& s)
  { wstring result;
    int rc = utf8_to_ucs4(s,result);
    if( rc >= 0 ) return result;
    return wstring();
  }
  
  string unicode2multibyte(const wstring& s)
  { string result;
    int rc = ucs4_to_utf8(s,result);
    if( rc >= 0 ) return result;
    return string();
  }

}
