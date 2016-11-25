/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [gstream.c]         Generic Character ( Set ) & Stream Library             */
/*                                                                            */
/* Copyright (c) 1999 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

#include "standard.h"

#if defined( _MSDOS ) || defined( _WIN32 )
#include <winnls.h>
#endif

/*!!
   [gstream] supports the conversion of strings from one character set to another.
   Beside that it provides a generic stream library which is able to handle different
   character sets.
   Supported platforms are Unix and Windows.
*/

/*I-------------------------- Types and macros ------------------------------ */

/*! <b>Default multibyte and wide character sets</b> */
/*DOC_INTERFACE*/
#if defined( _MSDOS ) || defined( _WIN32 )
#define CS_ID_WCHAR   "1200"
#else
#define CS_ID_WCHAR   "UCS-4"
#endif
#define CS_ID_MBYTE   "UTF-8"


ExternalDecl(CSConv_T);  // Character set conversion type
ExternalDecl(GStream_T); // Generic stream type 

/*! <b>Types of generic stream functions</b> */
/*DOC_INTERFACE*/
// read byte vector function (RC>=0 <==> bytes read, RC=-1 <==> error)
typedef int (*GS_getb_T)(GStream_T gstream, c_byte* b, int cnt); 
// put byte vector function (RC>=0 <==> bytes written, RC=-1 <==> error)
typedef int (*GS_putb_T)(GStream_T gstream, c_byte* b, int cnt); 
// fseek function
// (RC = new byte position = origin + offset <==> OK, RC=-1 <==> error)
typedef LONG_INT (*GS_seek_T)(GStream_T gstream, long offset, int origin);
// close and free function
typedef void (*GS_destruct_T)(GStream_T gstream);


ConcreteImp(CSConv_T)  // character set conversion type (implementation)
{
  c_string cs_src; // source character set
  c_string cs_dst; // target character set
  StdCPtr  cscd;   // character set conversion description 
};

ConcreteImp(GStream_T)  // generic stream type (implementation)
{
  StdCPtr  gsd;     // generic stream descriptor
  LONG_INT gsd_len; // stream len in bytes
  LONG_INT gsd_pos; // current stream position in bytes
  CSConv_T csci;    // read conversion information
  CSConv_T csco;    // write conversion information
  // read byte vector function (RC>=0 <==> bytes read, RC=-1 <==> error)
  int (*getb)(GStream_T gstream, c_byte* b, int cnt); 
  // put byte vector function (RC>=0 <==> bytes written, RC=-1 <==> error)
  int (*putb)(GStream_T gstream, c_byte* b, int cnt); 
  // fseek function
  // (RC = new byte position = origin + offset <==> OK, RC=-1 <==> error)
  LONG_INT (*seek)(GStream_T gstream, long offset, int origin);
  // close and free function
  void (*destruct)(GStream_T gstream);
};

/*
   UCS-4 range (hex.)           UTF-8 octet sequence (binary)
   0000 0000-0000 007F   0xxxxxxx
   0000 0080-0000 07FF   110xxxxx 10xxxxxx
   0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx

   0001 0000-001F FFFF   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
   0020 0000-03FF FFFF   111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
   0400 0000-7FFF FFFF   1111110x 10xxxxxx ... 10xxxxxx
*/


#define MAX_UTF8_BYTES 6

ConcreteType(CSConv_UTF8_T)
{
  /* UCS4 character range */
  unsigned long ucs4_lwr; 
  unsigned long ucs4_upr; 
  byte   first_utf8_byte; // initial bits
  int    first_utf8_bit;  // 7  .. 0
  int    first_ucs4_bit;  // 31 .. 0
};

static ConcreteImp(CSConv_UTF8_T) ucs4_partition[MAX_UTF8_BYTES] =
{
  { 0x00000000, 0x0000007F, 0x00, 6, 6  },
  { 0x00000080, 0x000007FF, 0xC0, 4, 10 },
  { 0x00000800, 0x0000FFFF, 0xE0, 3, 15 },
  { 0x00010000, 0x001FFFFF, 0xF0, 2, 20 },
  { 0x00200000, 0x03FFFFFF, 0xF8, 1, 25 },
  { 0x04000000, 0x7FFFFFFF, 0xFC, 0, 31 }
};


/*I---------------- Multibyte and wide character set support ---------------- */

int GS_csconv_ucs4_utf8
    (
      wc_string in, size_t insize, 
      c_string out, size_t outsize
    )
/* ucs4 --> utf-8 ( RFC 2279 ) 
   'insize' contains the number of wide characters in 'in', L'\0' inclusive.
   'outsize' contains the number of bytes in 'out', '\0' inclusive.
   'out': utf-8 representation of 'in' or NULL 
   RC: >=0 on O.K. ( number of written bytes ) 
     | =-1 on possible incomplete input 
     | =-2 on error
*/
{ size_t len = insize, 
         utf8_idx, ucs4_bit, utf8_bit, i, j;
  int    ucs4_idx, k;
  for( utf8_idx = 0, i=0; utf8_idx < outsize && i < len; ++i )
  { wc_int wc = (wc_int)in[i];
    for( ucs4_idx = -1, j=0; j < MAX_UTF8_BYTES; ++j )
    {
      if( wc >= ucs4_partition[j].ucs4_lwr &&
          wc <= ucs4_partition[j].ucs4_upr  )
      {
        ucs4_idx = j; 
        break;
      }
    }
    if( ucs4_idx == -1 ) return -2;
    else
    if( ucs4_idx == 0 )
    {
      out[utf8_idx++] = (byte)wc;
    }
    else
    {
      for( ucs4_bit = ucs4_partition[ucs4_idx].first_ucs4_bit, j=0; 
           j <= ucs4_idx && utf8_idx < outsize; ++j, ++utf8_idx )
      {
        if( j > 0 )
        {
          out[utf8_idx] = (char)0x80;
          utf8_bit      = 5;
        }
        else
        {
          out[utf8_idx] = ucs4_partition[ucs4_idx].first_utf8_byte;
          utf8_bit      = ucs4_partition[ucs4_idx].first_utf8_bit;
        }
        for( k=utf8_bit; k >= 0; k--, --ucs4_bit )
        {
          if( wc & (1<<ucs4_bit) )
            out[utf8_idx] |= (1<<k);
        }
      }
    }
  }
  if( i < len ) return -2;
  //else out[utf8_idx] = '\0';
  return utf8_idx;
}

int GS_csconv_utf8_ucs4
    (
      c_string in, size_t insize, 
      wc_string out, size_t outsize
    )
/* utf-8 --> ucs4 ( RFC 2279 )
   'insize' contains the number of bytes in 'in', '\0' inclusive.
   'outsize' contains the number of wide characters in 'out', L'\0' inclusive.
   'out': ucs4 representation of 'in' or NULL 
   RC: >=0 on O.K. ( number of written wide characters ) 
     | =-1 on possible incomplete input 
     | =-2 on error
*/
{ size_t len = insize, 
         ucs4_idx, ucs4_bit, utf8_bit, i, j;
  int    utf8_idx, k;
  for( ucs4_idx = 0, i=0; ucs4_idx < outsize && i < len; )
  { 
    for( utf8_idx = -1, j=0; j < MAX_UTF8_BYTES; ++j )
    {
      if( in[i] >= ucs4_partition[j].first_utf8_byte &&
          ( j == MAX_UTF8_BYTES - 1 || in[i] < ucs4_partition[j+1].first_utf8_byte ) )
      {
        utf8_idx = j; break;
      }
    }
    if( utf8_idx == -1 ) return -2;
    else
    if( utf8_idx == 0 )
    {
      out[ucs4_idx++] = (wc_char)in[i++];
    }
    else
    { wc_int wc = 0L;
      for( ucs4_bit = ucs4_partition[utf8_idx].first_ucs4_bit, j=0; 
           j <= utf8_idx && i < len; ++j, ++i )
      {
        utf8_bit = (j>0)?5:ucs4_partition[utf8_idx].first_utf8_bit;
        for( k=utf8_bit; k >= 0; --k, --ucs4_bit )
        {
          if( in[i] & (1<<k) )
            wc |= (1<<ucs4_bit);
        }
      }
      if( j <= utf8_idx ) return -1;
      out[ucs4_idx++] = (wc_char)wc;
    }
  }
  if( i < len ) return -2;
  //else out[ucs4_idx] = WCHAR_LITERAL('\0');
  return ucs4_idx;
}

c_string GS_ucs4_to_utf8(wc_string in)
/* ucs4 --> utf-8 ( RFC 2279 ) 
   RC: utf-8 representation of 'in' or NULL; allocs memory 
*/
{ size_t   len     = WCStrLen(in), 
           outsize = 1, i, j;
  int      ucs4_idx, res;
  c_string out     = (c_string)NULL; 
  for( i=0; i < len; ++i )
  { wc_int wc = (wc_int)in[i];
    for( ucs4_idx = -1, j=0; j < MAX_UTF8_BYTES; ++j )
    {
      if( wc >= ucs4_partition[j].ucs4_lwr &&
          wc <= ucs4_partition[j].ucs4_upr  )
      {
        ucs4_idx = j; break;
      }
    }
    if( ucs4_idx == -1 ) return (c_string)NULL;
    else outsize += ucs4_idx + 1;
  }
  out = NewMem(outsize);
  res = GS_csconv_ucs4_utf8(in,len+1,out,outsize);
  if( res >= 0 ) return out;
  else
  {
    FreeMem(out); return (c_string)NULL;
  }
}

wc_string GS_utf8_to_ucs4(c_string in)
/* utf-8 --> ucs4 ( RFC 2279 )
   RC: ucs4 representation of 'in' or NULL; allocs memory 
*/
{ size_t   len     = strlen(in), 
           outsize = 1, i, j;
  int      utf8_idx, res;
  wc_string out    = (wc_string)NULL; 
  for( i=0; i < len; )
  { 
    for( utf8_idx = -1, j=0; j < MAX_UTF8_BYTES; ++j )
    {
      if( in[i] >= ucs4_partition[j].first_utf8_byte &&
          ( j == MAX_UTF8_BYTES - 1 || in[i] < ucs4_partition[j+1].first_utf8_byte ) )
      {
        utf8_idx = j; break;
      }
    }
    if( utf8_idx == -1 ) return (wc_string)NULL;
    else 
    {
      outsize += 1;
      i += utf8_idx + 1;
    }
  }
  out = NewMem(outsize*sizeof(wc_char));
  res = GS_csconv_utf8_ucs4(in,len+1,out,outsize);
  if( res >= 0 ) return out;
  else
  {
    FreeMem(out); return (wc_string)NULL;
  }
}


void GS_fprint_utf8(FILE* fp, c_string s, c_bool raw)
/* print utf-8 string 's' to file 'fp'
   raw --> printable ascii or hex
*/
{ wc_string ws;
  size_t    len, i;
#if defined(WEOF)
  if( ! raw )
  {
    ws = GS_utf8_to_ucs4(s);
    if( ws != (wc_string)NULL )
    {
      fprintf(fp,"%S",ws);
      FreeMem(ws);
    }
    return;
  }
#endif
  len = strlen(s);
  for( i=0; i < len; ++i )
  {
    if( isascii(s[i]) && ( isprint(s[i]) || isspace(s[i]) ) )
      fprintf(fp,"%c",s[i]);
    else
      fprintf(fp,"%02x",s[i]);
  }
}

void GS_fprint_ucs4(FILE* fp, wc_string ws, c_bool raw)
/* print ucs4 string 'ws' to file 'fp' 
   raw --> printable ascii or hex
*/
{ size_t len, i;
#if defined(WEOF)
  if( ! raw )
  {
    fprintf(fp,"%S",ws);
    return;
  }
#endif
  len = WCStrLen(ws);
  for( i=0; i < len; ++i )
  { byte b = (byte)ws[i];
    if( ((wc_char)b) == ws[i] )
    {
      if( isascii(b) && ( isprint(b) || isspace(b) ) )
        fprintf(fp,"%c",b);
      else
        fprintf(fp,"%02x",b);
    }
    else 
      fprintf(fp,"%08lx",ws[i]);
  }
}


#if defined( _MSDOS ) || defined( _WIN32 )

  CSConv_T GS_csconv_new(c_string ct, c_string cs)
  {
    if( ct != (c_string)NULL && cs != (c_string)NULL )
    { long   cscp = atol(cs), 
             ctcp = atol(ct);
      CPINFO cscpi, ctcpi;
      if( (!strcmp(cs,CS_ID_MBYTE) || 
           !strcmp(cs,CS_ID_WCHAR) || 
           GetCPInfo(cscp,&cscpi) == TRUE ) && 
          (!strcmp(ct,CS_ID_MBYTE) || 
           !strcmp(ct,CS_ID_WCHAR) || 
           GetCPInfo(ctcp,&ctcpi) == TRUE )  ) // O.K.
      { CSConv_T csci = New(CSConv_T);
        csci->cs_src = StrCopy(cs);
        csci->cs_dst = StrCopy(ct);
        csci->cscd   = (StdCPtr)NULL;
        return csci;
      }
    }
    return (CSConv_T)NULL;
  }

  void GS_csconv_free(CSConv_T csci)
  {
    if( csci != (CSConv_T)NULL )
    {
      FreeMem(csci->cs_src);
      FreeMem(csci->cs_dst);
      FreeMem(csci);
    }
  }

  int GS_csconv_string
      (
        CSConv_T csci, c_string in, int insize, c_string out, int* outsize
      )
  { 
    if( csci     != (CSConv_T)NULL &&
        in       != (c_string)NULL &&
        out      != (c_string)NULL &&
        outsize  != (int*)NULL     && 
        *outsize > 0               &&
        insize   > 0                )
    { c_string cs   = csci->cs_src,
               ct   = csci->cs_dst;
      long     cscp = atol(cs), 
               ctcp = atol(ct);
      CPINFO   cscpi, ctcpi;
      if( !strcmp(ct,CS_ID_MBYTE) && !strcmp(cs,CS_ID_WCHAR) )
      { c_bool more = insize % sizeof(wc_char) > 0;
        if( more ) return -1;
        else 
        { int rc = GS_csconv_ucs4_utf8
                   (
                     (wc_string)in, insize / sizeof(wc_char), out, *outsize
                   );
          if( rc >= 0 )
          {
            *outsize = rc; rc = insize / sizeof(wc_char);
          }
          return rc;
        }
      }
      else
      if( !strcmp(cs,CS_ID_MBYTE) && !strcmp(ct,CS_ID_WCHAR) )
      { int rc = GS_csconv_utf8_ucs4
                 (
                   in, insize, (wc_string)out, *outsize / sizeof(wc_char)
                 );
        if( rc >= 0 ) *outsize = rc * sizeof(wc_char);
        return rc;
      }
      else
      if( !strcmp(csci->cs_src,CS_ID_WCHAR) && 
          !strcmp(csci->cs_dst,CS_ID_WCHAR)  )
      { c_bool more = insize % sizeof(wc_char) > 0;
        if( more ) return -1;
        else
        if( insize <= *outsize )
        {
          memcpy(out,in,insize);
          *outsize = insize;
          return insize / sizeof(wc_char);
        }
      }
      else
      if( !strcmp(csci->cs_src,CS_ID_WCHAR) && 
          GetCPInfo(ctcp,&ctcpi) == TRUE     )
      { int    wcsize = insize / sizeof(wc_char);
        c_bool more   = insize % sizeof(wc_char) > 0;
        if( more ) return -1;
        else
        { int rc = WideCharToMultiByte
                   (
                     ctcp,0,(LPCWSTR)in,wcsize,out,*outsize,NULL,NULL
                   );
          if( rc > 0 ) 
          {
            *outsize = rc; return wcsize;
          }
        }
      }
      else
      if( !strcmp(csci->cs_dst,CS_ID_WCHAR) &&
          GetCPInfo(cscp,&cscpi) == TRUE     )
      { int wcsize = *outsize / sizeof(wc_char),
            rc     = MultiByteToWideChar
                     (
                       cscp,MB_ERR_INVALID_CHARS,in,insize,(LPWSTR)out,wcsize
                     );
        if( rc > 0 ) 
        {
          *outsize = rc * sizeof(wc_char); return rc;
        }
        else
        if( GetLastError() != ERROR_INSUFFICIENT_BUFFER && 
            insize < cscpi.MaxCharSize                   ) 
          return -1;
      }
      else
      if( GetCPInfo(cscp,&cscpi) == TRUE && GetCPInfo(ctcp,&ctcpi) == TRUE )
      { wc_char* buf = (wc_char*)NULL;
        int      rc1 = MultiByteToWideChar
                       (
                         cscp,MB_ERR_INVALID_CHARS,in,insize,buf,0
                       ), rc2;
        if( rc1 > 0 ) 
        {
          buf = (wc_char*)NewMem(sizeof(wc_char)*rc1);
          rc2 = MultiByteToWideChar
                (
                  cscp,MB_ERR_INVALID_CHARS,in,insize,buf,rc1
                );
          if( rc2 > 0 ) 
          {
            rc2 = WideCharToMultiByte(ctcp,0,buf,rc1,out,*outsize,NULL,NULL);
            if( rc2 > 0 ) 
            {
              *outsize = rc2; return rc1;
            }
          }
          FreeMem(buf);
        }
        else
        if( insize < cscpi.MaxCharSize ) return -1;
      }
    }
    return -2;
  }


#else
#if !defined(MSDOS) && ( !defined(HAVE_CONFIG_H) || defined(HAVE_ICONV_H) )

ConcreteType(CDIConv_T) // ICONV conversion description type
{
  StdCPtr cd;       // ICONV conversion description 
  wc_char s_endian; // current source big endian byte order
  wc_char t_endian; // current target big endian byte order
};

CSConv_T GS_csconv_new(c_string ct, c_string cs)
/* create new character set conversion description ( RC=NULL on error ) */
{ 
  if( ct != (c_string)NULL && cs != (c_string)NULL )
  { iconv_t cd = iconv_open(ct,cs);
    if( cd != (iconv_t)-1 ) // O.K.
    { CSConv_T  csci     = New(CSConv_T);
      CDIConv_T cd_iconv = New(CDIConv_T);
      int       i, j;
      cd_iconv->cd       = cd;
      /*
      cd_iconv->s_endian = !strcmp(cs,CS_ID_WCHAR)?0x04030201:0;
      cd_iconv->t_endian = !strcmp(ct,CS_ID_WCHAR)?0x04030201:0;
      */
      cd_iconv->s_endian = 0;
      cd_iconv->t_endian = 0;
      if( !strcmp(cs,CS_ID_WCHAR) )
        for( i=0, j=0; i < sizeof(wc_char); ++i, j+=8 )
          cd_iconv->s_endian |= ((wc_char)i+1) << j;
      if( !strcmp(ct,CS_ID_WCHAR) )
        for( i=0, j=0; i < sizeof(wc_char); ++i, j+=8 )
          cd_iconv->t_endian |= ((wc_char)i+1) << j;
      csci->cs_src       = StrCopy(cs);
      csci->cs_dst       = StrCopy(ct);
      csci->cscd         = cd_iconv;
      return csci;
    }
  }
  return (CSConv_T)NULL;
}

void GS_csconv_free(CSConv_T csci)
/* free character set conversion description */
{
  if( csci != (CSConv_T)NULL )
  {
    iconv_close((iconv_t)((CDIConv_T)(csci->cscd))->cd);
    FreeMem(csci->cscd);
    FreeMem(csci->cs_src);
    FreeMem(csci->cs_dst);
    FreeMem(csci);
  }
}

static wc_string GS_ucs4_to_ucs4_intern(wc_string ws, int size /*bytes*/, wc_char endian)
// ucs4 intern <==> ucs4 in big endian order
{
  // assertion: size % wchar_size = 0 !
  if( endian != 0 )
  { c_string s = (c_string)ws;
    char     buf[STD_BUFFLEN];
    int      i, j, k;
    for( i=0; i < size; i+=sizeof(wc_char) )
    {
      for( j=0, k=sizeof(wc_char)-1; j < sizeof(wc_char); ++j, --k )
      {
        buf[j] = s[i+((c_string)&endian)[k]-1];
      }
      memcpy(&s[i],buf,sizeof(wc_char));
    }
  }
  return ws;
}

static wc_string GS_ucs4_intern_to_ucs4(wc_string ws, int size /*bytes*/, wc_char endian)
// ucs4 intern <==> ucs4 in big endian order
{
  // assertion: size % wchar_size = 0 !
  if( endian != 0 )
  { c_string s = (c_string)ws;
    char     buf[STD_BUFFLEN];
    int      i, j, k;
    for( i=0; i < size; i+=sizeof(wc_char) )
    {
      for( j=0, k=sizeof(wc_char)-1; j < sizeof(wc_char); ++j, --k )
      {
        buf[((c_string)&endian)[k]-1] = s[i+j];
      }
      memcpy(&s[i],buf,sizeof(wc_char));
    }
  }
  return ws;
}

int GS_csconv_string
    (
      CSConv_T csci, c_string in, int insize, 
      c_string out, int* outsize
    )
/* character set conversion of 'in' to 'out'
   'outsize' contains the number of bytes in 'out'.
   'in' and 'out' must be a valid character buffers with size > 0.
   RC: >=0 on O.K. ( number of conversions / characters ) 
     | =-1 on possible incomplete input 
     | =-2 on error
*/
{ 
  if( csci     != (CSConv_T)NULL &&
      in       != (c_string)NULL &&
      out      != (c_string)NULL &&
      outsize  != (int*)NULL     && 
      *outsize > 0               &&
      insize   > 0                )
  { size_t   osize = *outsize, 
             isize = insize; 
    int      rc;
    c_string optr  = out,
             iptr  = in,
             tmp   = (c_string)NULL;
    if( ((CDIConv_T)csci->cscd)->s_endian != 0 && (isize % sizeof(wc_char)) != 0 )
      return -1;
    else
    if( ((CDIConv_T)csci->cscd)->s_endian != 0 )
    {
      iptr = (c_string)BytCopy(in, isize);
/* 
 { int i;
 printf("\nI-VOR");
 for( i=0; i < isize; ++i )
   printf(" %d", iptr[i]);
 printf("\n");
*/
      tmp  = (c_string)GS_ucs4_to_ucs4_intern((wc_string)iptr,isize,((CDIConv_T)csci->cscd)->s_endian);
/* 
 printf("\nI-NACH");
 for( i=0; i < isize; ++i )
   printf(" %d", iptr[i]);
 printf("\n"); }
*/
    }
    //rc = iconv((iconv_t)((CDIConv_T)csci->cscd)->cd,(const char**)&iptr,&isize,&optr,&osize);
    rc = iconv((iconv_t)((CDIConv_T)csci->cscd)->cd,&iptr,&isize,&optr,&osize);
    /*FIXME: comment above*/
    if( tmp != (c_string)NULL ) FreeMem(tmp);
    if( rc >= 0 )
    { 
      *outsize -= osize; // number of used bytes
/* 
 { int i;
 printf("\nVOR");
 for( i=0; i < *outsize; ++i )
   printf(" %d", out[i]);
 printf("\n"); }
*/
      if( ((CDIConv_T)csci->cscd)->t_endian != 0 )
        GS_ucs4_intern_to_ucs4((wc_string)out,*outsize,((CDIConv_T)csci->cscd)->t_endian);
/* 
 { int i;
 printf("\nNACH");
 for( i=0; i < *outsize; ++i )
   printf(" %d", out[i]);
 printf("\n"); }
*/
      return rc==0?insize:rc;
    }
    else
    if( rc == -1 && errno == EINVAL )
    {
      return rc;
    }
/**/printf("ICONV-ERR=%s\n",errno == EBADF ? "EBADF" : errno == E2BIG ? "E2BIG" : "EILSEQ");
  }
  return -2;
}


#else
/* DOS-GNU-CC, no extended character set support via 'iconv' */

  CSConv_T GS_csconv_new(c_string ct, c_string cs)
  { 
    if( ct != (c_string)NULL && cs != (c_string)NULL )
    {
      if( GetCPInfo(cscp,&cscpi) == TRUE && GetCPInfo(ctcp,&ctcpi) == TRUE ) // O.K.
      { CSConv_T csci = New(CSConv_T);
        csci->cs_src = StrCopy(cs);
        csci->cs_dst = StrCopy(ct);
        csci->cscd   = (StdCPtr)NULL;
        return csci;
      }
    }
    return (CSConv_T)NULL;
  }

  void GS_csconv_free(CSConv_T csci)
  {
    if( csci != (CSConv_T)NULL )
    {
      FreeMem(csci->cs_src);
      FreeMem(csci->cs_dst);
      FreeMem(csci);
    }
  }

  int GS_csconv_string
      (
        CSConv_T csci, c_string in, int insize, c_string out, int* outsize
      )
  { 
    if( csci     != (CSConv_T)NULL &&
        in       != (c_string)NULL &&
        out      != (c_string)NULL &&
        outsize  != (int*)NULL     && 
        *outsize > 0               &&
        insize   > 0                )
    { 
      if( !strcmp(ct,CS_ID_MBYTE) && !strcmp(cs,CS_ID_WCHAR) )
      { c_bool more = insize % sizeof(wc_char) > 0;
        if( more ) return -1;
        else 
        { int rc = GS_csconv_ucs4_utf8((wc_string)in, insize / sizeof(wc_char), out, *outsize);
          if( rc >= 0 )
          {
            *outsize = rc; rc = insize / sizeof(wc_char);
          }
          return rc;
        }
      }
      else
      if( !strcmp(cs,CS_ID_MBYTE) && !strcmp(ct,CS_ID_WCHAR) )
      { int rc = GS_csconv_utf8_ucs4(in, insize, (wc_string)out, *outsize / sizeof(wc_char));
        if( rc >= 0 )
          *outsize = rc * sizeof(wc_char);
        return rc;
      }
      else
      if( insize <= *outsize )
      {
        memcpy(out,in,insize);
        *outsize = insize;
        return insize;
      }
    }
    return -2;
  }

#endif
#endif


/*I------------------------- Generic stream support ------------------------- */

static int GS_getbytes_from_file(GStream_T gstream, c_byte* b, int cnt)
/* read 'cnt' bytes from file stream 'gstream'
   RC: >=0 bytes read ( RC < 'cnt' <==> EOF ) | =-1 on error
*/
{ 
  if( gstream != (GStream_T)NULL && b != (c_byte*)NULL && cnt >= 0  )
  { int rc = fread(b,1,cnt,(FILE*)gstream->gsd);
    if( ! ferror((FILE*)gstream->gsd) ) 
    {
      gstream->gsd_pos += rc;
      return rc;
    }
  }
  return -1;
}

static int GS_putbytes_to_file(GStream_T gstream, c_byte* b, int cnt)
/* write 'cnt' bytes to file stream 'gstream'
   RC: >=0 bytes written | =-1 on error
*/
{ 
  if( gstream != (GStream_T)NULL && b != (c_byte*)NULL && cnt >= 0  )
  { int rc = fwrite(b,1,cnt,(FILE*)gstream->gsd);
    if( ! ferror((FILE*)gstream->gsd) ) return rc;
  }
  return -1;
}

static LONG_INT GS_seek_file(GStream_T gstream, long offset, int origin)
/* position file stream 'gstream' 
   RC: = new byte position on O.K. | =-1 on error
*/
{
  if( gstream != (GStream_T)NULL )
  { LONG_INT npos = -1, rc;
    rc = fseek((FILE*)gstream->gsd,offset,origin);
    if( rc == 0 )
    {
      npos = ftell((FILE*)gstream->gsd);
      if( npos >= 0 ) 
      {
        gstream->gsd_pos = npos;
        return npos;
      }
    }
  }
  return -1;
}

void GS_stream_file_free(GStream_T gstream)
/* free file stream 'gstream' */
{
  if( gstream != (GStream_T)NULL )
  {
    GS_csconv_free(gstream->csci);
    GS_csconv_free(gstream->csco);
    FreeMem(gstream);
  }
} 

void GS_stream_file_destruct(GStream_T gstream)
/* close and free file stream 'gstream' */
{
  if( gstream != (GStream_T)NULL )
  {
    fclose((FILE*)gstream->gsd);
    GS_csconv_free(gstream->csci);
    GS_csconv_free(gstream->csco);
    FreeMem(gstream);
  }
} 

GStream_T GS_stream_file_new
          (
            FILE* fp, c_string cs, c_bool close
          )
/* create new generic stream on a file opened for binary I/O 
   'cs'   : character set name ( UCS4, UTF-8, MS:CodePage / GNU:iconv-based )
   'close': true <--> close file on stream destruction
   RC: stream on O.K. | NULL on error 
*/
{ 
  if( fp != (FILE*)NULL )
  { CSConv_T csci = GS_csconv_new(CS_ID_WCHAR,cs),
             csco = GS_csconv_new(cs,CS_ID_WCHAR);
    if( csci != (CSConv_T)NULL && csco != (CSConv_T)NULL ) // O.K.
    { GStream_T gstream = New(GStream_T);
      gstream->gsd      = fp;
      gstream->gsd_len  = -1;
      gstream->gsd_pos  = 0;    // relative file position 
      gstream->csci     = csci;
      gstream->csco     = csco;
      gstream->getb     = GS_getbytes_from_file;
      gstream->putb     = GS_putbytes_to_file;
      gstream->seek     = GS_seek_file;
      gstream->destruct = close?GS_stream_file_destruct:GS_stream_file_free;
      return gstream;
    }
    if( csci != (CSConv_T)NULL ) GS_csconv_free(csci);
    if( csco != (CSConv_T)NULL ) GS_csconv_free(csco);
  }
  return (GStream_T)NULL;
} 

static int GS_getbytes_from_string(GStream_T gstream, c_byte* b, int cnt)
/* read 'cnt' bytes from string stream 'gstream'
   RC: >=0 bytes read ( RC < 'cnt' <==> EOF ) | =-1 on error
*/
{ 
  if( gstream != (GStream_T)NULL && b != (c_byte*)NULL && cnt >= 0  )
  { unsigned int bytesleft = gstream->gsd_len - gstream->gsd_pos; 
    memcpy(b,((c_string)gstream->gsd)+gstream->gsd_pos,MIN(bytesleft,cnt));
    gstream->gsd_pos += MIN(bytesleft,cnt);
    return MIN(bytesleft,cnt);
  }
  return -1;
}

static int GS_putbytes_to_string(GStream_T gstream, c_byte* b, int cnt)
/* write 'cnt' bytes to string stream 'gstream'
   RC: >=0 bytes written | =-1 on error
*/
{ 
  if( gstream != (GStream_T)NULL && b != (c_byte*)NULL && cnt >= 0  )
  { unsigned int bytesleft = gstream->gsd_len - gstream->gsd_pos, tmp; 
    if( bytesleft < cnt )
    { c_string s;
      s   = (c_string)NULL;
      tmp = gstream->gsd_len;
      gstream->gsd_len += MAX(gstream->gsd_len+cnt,gstream->gsd_len<<1);
#if !defined(HAVE_CONFIG_H) || defined(HAVE_REALLOC)
      gstream->gsd = ResizeMem(gstream->gsd,gstream->gsd_len);
#else
      s = (c_string)NewMem(gstream->gsd_len);
      memcpy(s,gstream->gsd,tmp);
      FreeMem(gstream->gsd);
      gstream->gsd = s;
#endif
    }
    memcpy(((c_string)gstream->gsd)+gstream->gsd_pos,b,cnt);
    gstream->gsd_pos += cnt;
    return cnt;
  }
  return -1;
}

static LONG_INT GS_seek_string(GStream_T gstream, long offset, int origin)
/* position file stream 'gstream' ( position may vary between 0 and EOS ) 
   RC: = new byte position on O.K. | =-1 on error
*/
{ LONG_INT npos = -1;
  if( gstream != (GStream_T)NULL )
  {
    switch(origin)
    {
      case SEEK_SET:
        npos = offset;
        break;
      case SEEK_END:
        npos = gstream->gsd_len + offset;
        break;
      case SEEK_CUR:
        npos = gstream->gsd_pos + offset;
        break;
      default:
        npos = -1;
        break;
    }
  }
  if( npos >= 0 && npos <= gstream->gsd_len )
  {
    gstream->gsd_pos = npos;
    return npos;
  }
  else return -1;
}

void GS_stream_string_free(GStream_T gstream)
/* free string stream 'gstream' */
{
  if( gstream != (GStream_T)NULL )
  {
    FreeMem(gstream->gsd);
    GS_csconv_free(gstream->csci);
    GS_csconv_free(gstream->csco);
    FreeMem(gstream);
  }
} 

GStream_T GS_stream_string_new
          (
            c_string s, unsigned int len, c_string cs
          )
/* create new generic stream on a string buffer
   'len': string size in bytes, inclusive terminating bytes
   'cs' : character set name ( UCS4, UTF-8, MS:CodePage / GNU:iconv-based )
   RC: stream on O.K. | NULL on error 
   Note: During write operations when reaching the end of the buffer
         's' will be deleted and recreated.
*/
{ 
  if( s != (c_string)NULL && len >= 0 )
  { CSConv_T csci = GS_csconv_new(CS_ID_WCHAR,cs),
             csco = GS_csconv_new(cs,CS_ID_WCHAR);
    if( csci != (CSConv_T)NULL && csco != (CSConv_T)NULL ) // O.K.
    { GStream_T gstream = New(GStream_T);
      gstream->gsd      = NewMem(len);
      memcpy(gstream->gsd,s,len);
      gstream->gsd_len  = len;
      gstream->gsd_pos  = 0;
      gstream->csci     = csci;
      gstream->csco     = csco;
      gstream->getb     = GS_getbytes_from_string;
      gstream->putb     = GS_putbytes_to_string;
      gstream->seek     = GS_seek_string;
      gstream->destruct = GS_stream_string_free;
      return gstream;
    }
    if( csci != (CSConv_T)NULL ) GS_csconv_free(csci);
    if( csco != (CSConv_T)NULL ) GS_csconv_free(csco);
  }
  return (GStream_T)NULL;
} 

c_bool GS_stream_string_set
       (
         GStream_T gstream, c_string s, unsigned int len
       )
/* reset the string buffer of generic stream 'gstream'
   'len': string size in bytes, inclusive terminating bytes
   RC: True = O.K.
   Note: The character set of 's' and 'gstream' must be the same.
*/
{ 
  if( gstream != (GStream_T)NULL && s != (c_string)NULL && len >= 0 )
  { 
    FreeMem(gstream->gsd);
    gstream->gsd     = NewMem(len);
    memcpy(gstream->gsd,s,len);
    gstream->gsd_len = len;
    gstream->gsd_pos = 0;
    return C_True;
  }
  return C_False;
} 

c_bool GS_stream_string_insert
       (
         GStream_T gstream, c_string s, unsigned int len
       )
/* insert 's' into the string buffer of generic stream 'gstream'
   'len': string size in bytes, exclusive terminating bytes
   RC: True = O.K.
   Note: The character set of 's' and 'gstream' must be the same.
*/
{ 
  if( gstream != (GStream_T)NULL && s != (c_string)NULL && len >= 0 )
  { unsigned int bytesleft = gstream->gsd_len-gstream->gsd_pos;
    c_byte* b = (c_byte*)NewMem(bytesleft+1);
    memcpy(b,((c_string)gstream->gsd)+gstream->gsd_pos,bytesleft);
    if( GS_putbytes_to_string(gstream,s,len) >= len &&
        GS_putbytes_to_string(gstream,b,bytesleft) >= bytesleft )
    {
      FreeMem(b); return C_True;
    }
    FreeMem(b);
  }
  return C_False;
} 

int GS_stream_get_wcval(GStream_T gstream, wc_int* wc)
/* get wide character 'wc' from 'gstream' 
   RC: =1 on O.K. | =0 on O.K. and EOF | =-1 on error
*/
{ 
  if( gstream != (GStream_T)NULL )
  { c_byte  b;
    wc_char wcbuf[1+1];
    char    mbbuf[STD_BUFFLEN+1];
    int     rc    = (*gstream->getb)(gstream,&b,1), 
            isize = 0, 
            osize = 2*sizeof(wc_char), 
            rcc   = 0; 
//printf("RC=%d\n",rc);
    while( rc > 0 )
    {
      mbbuf[isize] = b;
      assert0(++isize < STD_BUFFLEN,"buffer overflow");
//printf("ISIZE=%d,OSIZE=%d\n",isize,osize);
      rcc = GS_csconv_string(gstream->csci,mbbuf,isize,(c_string)wcbuf,&osize);
//printf("RCC=%d\n",rcc);
      if( rcc == -1 ) rc = (*gstream->getb)(gstream,&b,1);
      else break;
    }
    if( ( rc == 0 && rcc == 0 ) || ( rc > 0 && rcc > 0  ) ) // no error
    {
      if( rc == 0 ) // EOF
      {
        *wc = WCHAR_LITERAL('\0'); return rc;
      }
      else // O.K.
      {
//printf("WCBUF=%08lx\n",wcbuf[0]);
        *wc = (int)wcbuf[0]; return 1;
      }
    }
  }
  return -1;
}

int GS_stream_get_wcrc(GStream_T gstream)
/* get wide character from 'gstream' 
   RC: >=0 as wide character or =-1 on EOF | =-2 on error
*/
{ int    rc;
  wc_int val;
  rc = GS_stream_get_wcval(gstream,&val);
  if( rc == -1 ) rc = -2;       /* error          */
  if( rc == 0  ) rc = -1;       /* EOF            */
  else           rc = (int)val; /* wide character */
  return rc;
}

int GS_stream_put_wcval(GStream_T gstream, wc_int wc)
/* put wide character 'wc' to 'gstream'
   RC: >=0 on O.K. | =-1 on error
*/
{
  if( gstream != (GStream_T)NULL )
  { wc_char wcbuf[1];
    char   mbbuf[STD_BUFFLEN+1];
    int    rc    = 0,
           isize = sizeof(wc_char), 
           osize = STD_BUFFLEN; 
    wcbuf[0] = (wc_char)wc;
    rc = GS_csconv_string(gstream->csco,(c_string)wcbuf,isize,mbbuf,&osize);
    if( rc > 0 )
    {
      rc = (*gstream->putb)(gstream,(c_byte*)mbbuf,osize);
      return rc;
    }
  }
  return -1;
}

int GS_stream_bytepos(GStream_T gstream, unsigned int* pos)
/* get ( relative ) stream position in bytes
   RC: =0 on O.K. | =-1 on error
*/
{
  if( gstream != (GStream_T)NULL && pos != (unsigned int*)NULL )
  {
    *pos =  gstream->gsd_pos;
    return 0;
  }
  return -1;
}

GS_getb_T GS_fun_getb(GStream_T gstream)
/* get byte function of 'gstream' or NULL */
{
  if( gstream != (GStream_T)NULL )
    return gstream->getb;
  else return (GS_getb_T)NULL;
}

GS_putb_T GS_fun_putb(GStream_T gstream)
/* put byte function of 'gstream' or NULL */
{
  if( gstream != (GStream_T)NULL )
    return gstream->putb;
  else return (GS_putb_T)NULL;
}

GS_seek_T GS_fun_seek(GStream_T gstream)
/* position function of 'gstream' or NULL */
{
  if( gstream != (GStream_T)NULL )
    return gstream->seek;
  else return (GS_seek_T)NULL;
}

GS_destruct_T GS_fun_destruct(GStream_T gstream)
/* close and free function of 'gstream' or NULL */
{
  if( gstream != (GStream_T)NULL )
    return gstream->destruct;
  else return (GS_destruct_T)NULL;
}
