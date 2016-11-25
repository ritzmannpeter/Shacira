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


#include <wctype.h>
#include <string>


/** @file
    Characterset conversion, based on the iconv library
*/

namespace styx
{
  using namespace std;

  /** @addtogroup StyxI18NLit
      Characterset conversion, based on the iconv library
  */
  //@{

  const char* CS_ID_WCHAR  = "UCS-4";  ///< UCS-4 characterset identifier
  const char* CS_ID_MBYTE  = "UTF-8";  ///< UTF-8 characterset identifier
  const char* CS_ID_LATIN1 = "LATIN1"; ///< Latin1 characterset identifier
  
  /// Characterset conversion, based on the iconv library
  class CStyxCharConv
  {
  protected:
    void*   icd;      ///< iconv-handle
    wchar_t s_endian; ///< ics_src = UCS-4 --\> byte order or 0
    wchar_t t_endian; ///< ics_dst = UCS-4 --\> byte order or 0
    string  ics_src;  ///< source characterset
    string  ics_dst;  ///< target characterset
    string  errmsg;   ///< conversion error or ""
  
    /// endian conversion UCS-4 --\> (iconv) INTERNAL
    /// @param ws [update] UCS-4 character buffer
    /// @param size buffer size in bytes
    /// @param endian UCS-4 byte order
    /// @return the converted character buffer
    virtual wchar_t* ucs42intern(wchar_t* ws, size_t size /*bytes*/, wchar_t endian);
  
    /// endian conversion (iconv) INTERNAL --\> UCS-4
    /// @param ws [update] (iconv) INTERNAL character buffer
    /// @param size buffer size in bytes
    /// @param endian UCS-4 byte order
    /// @return the converted character buffer
    virtual wchar_t* intern2ucs4(wchar_t* ws, size_t size /*bytes*/, wchar_t endian);
  
  public:
    /// The constructor creates an uninitialized conversion object.
    CStyxCharConv();
    /// The constructor creates an initialized conversion object.
    /// @param cs_src source characterset
    /// @param cs_dst target characterset
    CStyxCharConv(string cs_src, string cs_dst);
    virtual ~CStyxCharConv();
  
    /// get conversion error
    /// @return conversion error or ""
    virtual string& getError();
  
    /// re-initialize conversion
    /// @param cs_src source characterset
    /// @param cs_dst target characterset
    /// @return true or false on error
    virtual bool init(string cs_src, string cs_dst);
    /// release current conversion context
    /// @return true or false on error
    virtual bool quit();
  
    /// characterset conversion of 'src[size]' to 'dst'
    /// @param src input string
    /// @param size input string size in bytes
    /// @param dst [result] the converted string
    /// @return number of conversions / characters \>= 0
    /// or -1 for a possible incomplete input
    /// or -2 on error
    virtual int  convert(const string& src, size_t size, string& dst);
  };

  //@}

}

#endif
