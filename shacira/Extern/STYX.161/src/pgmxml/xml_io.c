/* ------------------------------------------------------------------------- */
/*                                                                           */
/* [xml_io.c]             curl Wrapper                                       */
/*                  - fetch files identified by an URL -                     */
/*                                                                           */
/* Copyright (c) 2003 by D\olle, Manns.                                      */
/* ------------------------------------------------------------------------- */

#include "standard.h"
#include "xml_dfn.h"
#include "gstream.h"

#include "pathes.h"
#include <curl/curl.h>


/*!!
   The module [xml_io] uses the library libcurl to fetch files identified 
   by an URL.
*/

/*I---------------------------- Init & Quit --------------------------------- */

c_bool XML_io_init()
/* init URL-based I/O; to be called once during application setup */
{ 

#if defined( _MSDOS ) || defined( _WIN32 )
  return curl_global_init(CURL_GLOBAL_SSL|CURL_GLOBAL_WIN32) == 0;
#else
  return curl_global_init(CURL_GLOBAL_SSL) == 0;
#endif
}

void XML_io_quit()
/* quit URL-based I/O; to be called once during application cleanup */
{
  curl_global_cleanup();
}

/*I----------------------------- Creation & Disposal ------------------------- */

UrlHdl_T XML_io_create_handle()
/* create a new handle to access URL-based resources;
   RC: handle or NULL
*/
{
  return (UrlHdl_T)curl_easy_init(); 
}

void XML_io_drop_handle(UrlHdl_T hdl)
/* drop handle 'hdl' */
{
  if( hdl != (UrlHdl_T)NULL )
    curl_easy_cleanup((CURL*)hdl); 
}

/*I----------------------------- URL Access ---------------------------------- */

static size_t XML_io_download_cb
              (
                StdCPtr data, size_t blk, size_t cnt, StdCPtr stream
              )
{ GS_putb_T pfnPutByte = GS_fun_putb((GStream_T)stream);
  if( pfnPutByte != (GS_putb_T)NULL )
  { 
    return (size_t)(*pfnPutByte)(stream,(c_byte*)data,(int)(blk*cnt));
  }
  return (size_t)-1;
}

static void XML_io_error(c_string msg)
{
  if( msg != (c_string)NULL )
    fprintf(stderr,"%s\n",msg);
}

c_bool XML_io_download
       (
         UrlHdl_T hdl, c_string url, c_string auth, 
         GStream_T stream, void (*prMsg)(c_string msg)
       )
/* download resource 'url' and put it to 'stream';
   optionally, use 'auth' (format: user:passwd) for authorisation 
   and 'prMsg' as error callback
*/
{ char errbuf[CURL_ERROR_SIZE+1];
  void (*error)(c_string msg) = ( prMsg != NULL ) ? prMsg : XML_io_error;
  int  rc = 0;
  BUG_NULL(hdl); BUG_NULL(url); BUG_NULL(stream);
  errbuf[0] = '\0';
  rc = curl_easy_setopt((CURL*)hdl,CURLOPT_FILE,stream);
  if( rc == 0 )
    rc = curl_easy_setopt((CURL*)hdl,CURLOPT_WRITEFUNCTION,XML_io_download_cb);
  if( rc == 0 )
    rc = curl_easy_setopt((CURL*)hdl,CURLOPT_URL,url);
  if( rc == 0 && !STR_EMPTY(auth) )
    rc = curl_easy_setopt((CURL*)hdl,CURLOPT_USERPWD,auth);
  if( rc == 0 )
    rc = curl_easy_setopt((CURL*)hdl,CURLOPT_ERRORBUFFER,errbuf);
  if( rc != 0 )
  {
    (*error)("download failed");
    return C_False;
  }
  else
  {
    rc = curl_easy_perform((CURL*)hdl);
    return rc == 0;
  }
}
